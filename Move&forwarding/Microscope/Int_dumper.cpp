#include "Int_dumper.hpp"

#include "../help_utils/String_ext.hpp"

const std::string Signal_names[] = 
{
    "+",
    "+=",
    "prefix increment",
    "postfix increment",
    "-",
    "-=",
    "prefix decrement",
    "postfix decrement",
    "*",
    "*=",
    "/",
    "/=",
    " COPY= ",
    " MOVE= ",
    "<<< C O P Y >>>",
    ">",
    ">=",
    "<",
    "<=",
    "==",
    "!=",
    "MOVE",
    "CTOR",
    "DTOR"
};

const std::string Signal_official_names[] = 
{
    "plus",
    "plus_ass",
    "prefix_increment",
    "postfix_increment",
    "sub",
    "sub_ass",
    "prefix_decrement",
    "postfix_decrement",
    "mul",
    "mul_ass",
    "div",
    "div_ass",
    "COPY_ass",
    "MOVE_ass",
    "COPY",
    "more",
    "more_eq",
    "less",
    "less_eq",
    "eq",
    "not_eq",
    "MOVE",
    "CTOR",
    "DTOR"
};

const bool Binary[] = 
{
    true,
    true,
    false,
    false,
    true,
    true,
    false,
    false,
    true,
    true,
    true,
    true,
    true,
    true,
    false,
    true,
    true,
    true,
    true,
    true,
    true,
    false,
    false,
    false
};

const bool Changable[] = 
{
    false,
    true,
    true,
    true,
    false,
    true, // sub_Ass
    true,
    true,
    false, // mul
    true,
    false, 
    true, // div_ass
    true,
    true,
    true,
    false,
    false,
    false,
    false,
    false,
    false,
    true,
    true,
    true
};

Int_dumper *Int_dumper::dumper = nullptr;
Dumper_destroyer Int_dumper::destroyer;

Int_dumper::Int_dumper()
: Int_signal_receiver(), copy_amount(0), move_amount(0), functions_in(0), max_func_id(0)
{
    dump = new HTML_dump(DUMP_FILE);
    dump->dump("<!DOCTYPE html><head><link rel=\"stylesheet\" href=\"style.css\"></head>");
    dump->open_tag(PREFIX, 0);

    dot = new Dot_dump("Dot_dump.txt");

    // dumper = this;
}

Int_dumper::~Int_dumper() 
{
    std::string message = "\n\nCopies amount = " + std::to_string(copy_amount) + ", Moves amount = " + std::to_string(move_amount) + ".";
    dump_text(message);
    
    delete dot;
    delete dump;
}

Int_dumper *Int_dumper::get_dumper()
{
	if (dumper == nullptr)
	{
		dumper = new Int_dumper();
		destroyer.initialize(dumper);
	}

	return dumper;
}

std::string create_name(Operation *op)
{
    std::string result = "";
    
    if (op->get_signal() == Int_signal::CONSTRUCT || op->get_signal() == Int_signal::COPY || op->get_signal() == Int_signal::MOVE || op->get_signal() == Int_signal::DESTRUCT)
    {
        result = "struct_" + std::to_string(op->get_sender_id()) + "_" + Signal_official_names[(int)op->get_signal()];
    }
    else
    {
        result = "struct_" + std::to_string(op->get_sender_id()) + "_" + std::to_string(op->get_other_id()) + "_" + Signal_official_names[(int)op->get_signal()];
    }

    return result;
}

std::string create_label(Operation *op)
{
    std::string result = "";
    
    if (op->get_signal() == Int_signal::CONSTRUCT || op->get_signal() == Int_signal::COPY || op->get_signal() == Int_signal::MOVE || op->get_signal() == Int_signal::DESTRUCT)
    {
        char sender_address[256] = "";
        memset(sender_address, 0, 256);
        sprintf(sender_address, "%p", op->get_sender_address());
        result = "{" + Signal_official_names[(int)op->get_signal()] + "|{" + std::to_string(op->get_sender_value()) + "|" + op->get_sender_name() + "|" + "id: " + std::to_string(op->get_sender_id()) + "}|" + "hist: " + op->get_sender_history() + "|" + sender_address + "}";
    }
    else
    {
        result = (op->get_sender_history().empty() ? op->get_sender_name() + Signal_names[(int)op->get_signal()] + (op->get_other_history().empty() ? op->get_other_name() : op->get_other_history()) : op->get_sender_history());
    }

    return result;
}

void Int_dumper::update_history()
{
    long long last_op = history.size() - 1;
    assert(last_op >= 0);
    
    size_t id = history[last_op]->get_sender_id();
    
    switch(history[last_op]->get_signal())
    {
        case Int_signal::ASSIGN_ADD:
        case Int_signal::ASSIGN_SUB:
        case Int_signal::ASSIGN_MUL:
        case Int_signal::ASSIGN_DIV:
        case Int_signal::ASSIGN_COPY:
        case Int_signal::ASSIGN_MOVE:
        case Int_signal::COPY:
        case Int_signal::MOVE:
        case Int_signal::CONSTRUCT:
            if (last_change_op.size() <= id)
                last_change_op.push_back(last_op);
            else
                last_change_op[id] = last_op;
            break;
        
        default:
            break;
    }
}

void Int_dumper::make_connections(const Intercepted_int &sender, std::string &current_struct)
{
    long long last_op = history.size() - 1;
    assert(last_op >= 0);

    Int_signal signal_type = history[last_op]->get_signal();
    
    if (!Binary[(int)signal_type]) // == Int_signal::CONSTRUCT || history[last_op]->get_signal() == Int_signal::COPY || history[last_op]->get_signal() == Int_signal::MOVE || history[last_op]->get_signal() == Int_signal::DESTRUCT)
    {
        if (required.size() && required[required.size() - 1] == signal_type && last_op > 0)
        {
            std::string sender = create_name(history[last_op - 1]);
            dot->create_arrow(sender.c_str(), current_struct.c_str(), "solid");
        }
        
        // Стрелка от прошлой операции к текущей
        else if (last_op > 0)
        {
            std::string sender = create_name(history[last_op - 1]);
            dot->create_arrow(sender.c_str(), current_struct.c_str(), "invis");
        }
        
        // Стрелка в деструктор
        if (history[last_op]->get_signal() != Int_signal::DESTRUCT)
        {
            std::string to = "struct_" + std::to_string(history[last_op]->get_sender_id()) + "_" + Signal_official_names[(int)Int_signal::DESTRUCT]; 
            dot->create_arrow(current_struct.c_str(), to.c_str(), "dashed");
        }
        
        size_t id = history[last_op]->get_sender_id();
        if (history[last_op]->get_signal() != Int_signal::DESTRUCT && last_change_op.size() > id)
        {
            std::string sender = create_name(history[last_change_op[id]]);
            dot->create_arrow(sender.c_str(), current_struct.c_str(), "solid");
        }
    }
    else
    {
        // Стрелки бинарных операций
        std::string sender = create_name(history[last_change_op[history[last_op]->get_sender_id()]]);
        std::string other = create_name(history[last_change_op[history[last_op]->get_other_id()]]);
        dot->create_arrow(sender.c_str(), current_struct.c_str(), "solid");
        dot->create_arrow(other.c_str(), current_struct.c_str(), "solid");
    }

    // Логическая стрелка изменения переменной 
    if (signal_type != Int_signal::CONSTRUCT && signal_type != Int_signal::COPY && signal_type != Int_signal::MOVE && Changable[(int)signal_type])
    {
        std::string from = "struct_";
        Int_signal last_change_signal = sender.get_last_change();
        // if (!(last_change_signal == Int_signal::CONSTRUCT || last_change_signal == Int_signal::COPY || last_change_signal == Int_signal::MOVE))
        // {
        if (!(signal_type == Int_signal::DESTRUCT && (last_change_signal == Int_signal::CONSTRUCT || last_change_signal == Int_signal::COPY || last_change_signal == Int_signal::MOVE)))
        {
            if (last_change_signal == Int_signal::ASSIGN_COPY || last_change_signal == Int_signal::ASSIGN_MOVE) // Binary[(int)last_change_signal]
                from += std::to_string(history[last_op]->get_sender_id()) + "_" + std::to_string(sender.get_influencer_id()) + "_" + Signal_official_names[(int)last_change_signal]; 
            else if (last_change_signal == Int_signal::COPY || last_change_signal == Int_signal::MOVE || last_change_signal == Int_signal::CONSTRUCT)
                from += std::to_string(history[last_op]->get_sender_id()) + "_" + Signal_official_names[(int)last_change_signal];
            dot->create_arrow(from.c_str(), current_struct.c_str(), "solid", "\"#da3131\""); // 
        }
    }
}

void Int_dumper::visual_dump(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    long long last_op = history.size() - 1;
    assert(last_op >= 0);
    
    std::string struct_name = "";
    std::string box_name = "";
    std::string label = "";
    
    if (!Binary[(int)history[last_op]->get_signal()]) 
        box_name = "record";
    else 
        box_name = "doubleoctagon";

    struct_name = create_name(history[last_op]);
    label = create_label(history[last_op]);

    dot->create_box(struct_name.c_str(), label.c_str(), BOX_COLORS[(int)history[last_op]->get_signal()], box_name.c_str());

    make_connections(sender, struct_name);

    update_history();
}

// std::string Int_dumper::restore_history(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
// {
//     std::string result;
//     if (sender.get_id() == other.get_id())
//     {
//         return result;
//     }
    
//     long long next_idx = other.get_history_length();

//     result = char_converter(sender.get_name()) + " " + Signal_names[(int)signal_type] + " ";

//     Intercepted_int const *next = &(other.get_event(next_idx)->other);
//     while(next_idx != -1)
//     {
//         if (other.get_event(next_idx)->op != Int_signal::COPY)
//         {
//             printf("%lld: %s\n", next_idx, other.get_event(next_idx)->other.get_name());
//             result += other.get_event(next_idx)->other.get_name() + Signal_names[(int)other.get_event(next_idx)->op];
//         }

//         next = &(other.get_event(next_idx)->other);
//         next_idx = next->get_history_length();
//     }

//     // printf("%s\n", result.c_str());

//     return result;
// }

void Int_dumper::dump_message(std::string message, Int_signal signal_type)
{
    dump->open_tag(FONT, font_params_amount, FONT_PARAM_NAMES[0], FONT_PARAMS[0][(int)signal_type]);
    dump->dump(message);
    dump->close_tag(FONT);
}

void Int_dumper::dump_text(std::string text)
{
    dump->dump(text);
}

void Int_dumper::reset_required()
{
    required.clear();
}

void Int_dumper::send_message(bool binary, Operation *op, bool ending)
{
    std::string message = "";
    if (!ending)
        message += '\n';
    
    for (size_t i = 0; i < functions_in; ++i)
        message += TAB;
    
    char sender_address[256] = "";
    memset(sender_address, '\0', 256);
    sprintf(sender_address, "%p", (op->get_sender_address()));

    if (binary) 
    {
        char other_address[256] = "";
        memset(other_address, '\0', 256);
        sprintf(other_address, "%p", (op->get_other_address()));
        
        message += "[(" + char_converter(op->get_sender_name()) + " = " + std::to_string(op->get_sender_value()) + " | " + sender_address + ") " + Signal_names[(int)op->get_signal()] + " (" + char_converter(op->get_other_name()) + " = " + std::to_string(op->get_other_value()) + " | " + other_address + ")]"; // + "\n"
    }
    else
    {
        message += Signal_names[(int)op->get_signal()] + ": [" + char_converter(op->get_sender_name()) + " = " + std::to_string(op->get_sender_value()) + " | " + sender_address + "]"; //  + "\n"
    }

    dump_message(message, op->get_signal());
}

void Int_dumper::copy_move_detect(Int_signal signal_type)
{
    switch(signal_type)
    {
    case Int_signal::ASSIGN_COPY:
    case Int_signal::COPY:
        copy_amount++;
        break;
    case Int_signal::ASSIGN_MOVE:
    case Int_signal::MOVE:
        move_amount++;
    default:
        break;
    }
}

void Int_dumper::signal(Int_signal signal_type, const Intercepted_int &sender)
{
    Operation *op = new Operation(signal_type, sender, sender);
    history.push_back(op);

    copy_move_detect(signal_type);
    
    bool reset = false;

    send_message(false, op);
    if (required.size() && required[required.size() - 1] == signal_type)
    {
        std::string message = " FROM ";
        dump_text(message);
        
        bool required_binary = history[history.size() - 2]->get_other_name() ? true : false;
        send_message(required_binary, history[history.size() - 2], true);
        
        Operation *last = history[history.size() - 2];
        op->set_sender_history((last->get_sender_history().empty() ? last->get_sender_name() : last->get_sender_history()) + Signal_names[(int)last->get_signal()] + (last->get_other_history().empty() ? last->get_other_name() : last->get_other_history()));
        reset = true;  
    }

    visual_dump(signal_type, sender, sender);
    if (reset)
        reset_required();
}

void Int_dumper::signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    Operation *op = new Operation(signal_type, sender, other);
    history.push_back(op);
    
    copy_move_detect(signal_type);
    
    bool reset = false;
    
    if (signal_type == Int_signal::ADD || signal_type == Int_signal::SUB || signal_type == Int_signal::MUL || signal_type == Int_signal::DIV) // && signal_type != Int_signal::ASSIGN_COPY && signal_type != Int_signal::ASSIGN_MOVE)
    {
        required.push_back(Int_signal::CONSTRUCT); // Почему только CONSTRUCT
        // Потому что
    }
    else if (required.size() && required[required.size() - 1] == signal_type)
    {
        send_message(true, op);
        
        std::string message = " FROM ";
        dump_text(message);
        
        bool required_binary = history[history.size() - 2]->get_other_name() ? true : false;
        send_message(required_binary, history[history.size() - 2], true);

        Operation *last = history[history.size() - 2];
        op->set_sender_history((last->get_sender_history().empty() ? last->get_sender_name() : last->get_sender_history()) + Signal_names[(int)last->get_signal()] + (last->get_other_history().empty() ? last->get_other_name() : last->get_other_history()));
        reset = true;
    }
    else
    {
        send_message(true, op);
    } 

    visual_dump(signal_type, sender, other);
    if (reset)
        reset_required();
}

void Int_dumper::decrease_functions_in(const char *func_name)
{
    --functions_in;
    dot->close_cluster();

    std::string message;
    message += '\n';
    for (size_t i = 0; i < functions_in; ++i)
        message += TAB;
    message += ARROW_PARTS[1];
    message += func_name;

    dump_text(message);
}

void Int_dumper::increase_functions_in(const char *func_name)
{
    std::string message;
    message += '\n';
    for (size_t i = 0; i < functions_in; ++i)
        message += TAB;
    message += ARROW_PARTS[0];
    dump_text(message);

    //"bgcolor"
    message = func_name;
    dump->open_tag("span", 0);
    dump->dump(message);
    dump->close_tag("span");
    
    ++functions_in;

    dot->open_cluster(max_func_id++, message.c_str());
}


Dumper_destroyer::~Dumper_destroyer() 
{ 
	delete dumper; 
}

void Dumper_destroyer::initialize(Int_dumper *par_dumper) 
{ 
	dumper = par_dumper; 
}


Spy::Spy(const char *func_name)
: func(nullptr)
{
    size_t func_name_len = strlen(func_name);
    func = new char[func_name_len + 1];
    strncpy(func, func_name, func_name_len);
    func[func_name_len] = '\0';
    
    Int_dumper::get_dumper()->increase_functions_in(func);
}

Spy::~Spy()
{
    Int_dumper::get_dumper()->decrease_functions_in(func);

    delete [] func;
}
