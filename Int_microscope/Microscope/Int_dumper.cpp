#include "Int_dumper.hpp"

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

Int_dumper *Int_dumper::dumper = nullptr;
Dumper_destroyer Int_dumper::destroyer;

Int_dumper::Int_dumper()
: Int_signal_receiver(), functions_in(0), max_tmp_vars_amount(0)
{
    dump = new HTML_dump(DUMP_FILE);
    dump->dump("<!DOCTYPE html><head><link rel=\"stylesheet\" href=\"style.css\"></head>");
    dump->open_tag(PREFIX, 0);

    dot = new Dot_dump("Dot_dump.txt");

    // dumper = this;
}

Int_dumper::~Int_dumper() 
{
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
        result = "struct_" + std::to_string(op->get_other_id()) + "_" + std::to_string(op->get_other_id()) + "_" + Signal_official_names[(int)op->get_signal()];
    }

    return result;
}

void Int_dumper::visual_dump(Int_signal signal_type, Operation *op)
{
    // std::string label = "";
    
    // dot->create_box(box_name.c_str(), label.c_str(), arrow_type);
    long long last_op = history.size() - 1;
    assert(last_op >= 0);
    
    std::string struct_name = "";
    std::string box_name = "";
    std::string label = "";
    if (history[last_op]->get_signal() == Int_signal::CONSTRUCT || history[last_op]->get_signal() == Int_signal::COPY || history[last_op]->get_signal() == Int_signal::MOVE || history[last_op]->get_signal() == Int_signal::DESTRUCT)
    {
        box_name = "record";
        struct_name = create_name(history[last_op]);// "struct_" + std::to_string(history[last_op]->get_sender_id()) + "_" + Signal_official_names[(int)history[last_op]->get_signal()];
        
        char sender_address[256] = "";
        memset(sender_address, 0, 256);
        sprintf(sender_address, "%p", history[last_op]->get_sender_address());
        label = "{" + Signal_official_names[(int)history[last_op]->get_signal()] + "|{" + std::to_string(history[last_op]->get_sender_value()) + "|" + history[last_op]->get_sender_name() + "}|" + sender_address + "}";
    
        dot->create_box(struct_name.c_str(), label.c_str(), BOX_COLORS[(int)history[last_op]->get_signal()], box_name.c_str());

        if (required.size() && required[required.size() - 1] == signal_type && last_op > 0)
        {
            std::string sender = create_name(history[last_op - 1]);
            dot->create_arrow(sender.c_str(), struct_name.c_str(), "solid");
        }
        else if (last_op > 0)
        {
            std::string sender = create_name(history[last_op - 1]);
            dot->create_arrow(sender.c_str(), struct_name.c_str(), "invis");
        }
        
        if (history[last_op]->get_signal() != Int_signal::DESTRUCT)
        {
            std::string to = "struct_" + std::to_string(history[last_op]->get_sender_id()) + "_" + Signal_official_names[(int)Int_signal::DESTRUCT]; 
            dot->create_arrow(struct_name.c_str(), to.c_str(), "dashed");
        }
        
        size_t id = history[last_op]->get_sender_id();
        if (history[last_op]->get_signal() != Int_signal::DESTRUCT && last_change_op.size() > id)
        {
            std::string sender = create_name(history[last_change_op[id]]);
            dot->create_arrow(sender.c_str(), struct_name.c_str(), "solid");
        }
    }
    else
    {
        box_name = "hexagon";
        struct_name = create_name(history[last_op]);// "struct_" + std::to_string(history[last_op]->get_sender_id()) + "_" + std::to_string(history[last_op]->get_other_name()) + "_" + Signal_official_names[(int)history[last_op]->get_signal()];

        label = Signal_official_names[(int)history[last_op]->get_signal()];

        dot->create_box(struct_name.c_str(), label.c_str(), BOX_COLORS[(int)history[last_op]->get_signal()], box_name.c_str());
        
        std::string sender = create_name(history[last_change_op[history[last_op]->get_sender_id()]]);
        std::string other = create_name(history[last_change_op[history[last_op]->get_other_id()]]);
        dot->create_arrow(sender.c_str(), struct_name.c_str(), "solid");
        dot->create_arrow(other.c_str(), struct_name.c_str(), "solid");
    }

    // if (required.size() && required[required.size() - 1] == signal_type && last_op > 0)
    // {
    //     std::string sender = create_name(history[last_op - 1]);
    //     dot->create_arrow(sender.c_str(), struct_name.c_str(), "invis");
    // }

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

std::string Int_dumper::restore_history(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    std::string result;
    if (sender.get_id() == other.get_id())
    {
        return result;
    }
    
    long long next_idx = other.get_history_length();
    // Intercepted_int &next;

    result = sender.get_name();
    result += " " + Signal_names[(int)signal_type] + " ";

    Intercepted_int const *next = &(other.get_event(next_idx)->other);
    while(next_idx != -1)
    {
        if (other.get_event(next_idx)->op != Int_signal::COPY)
        {
            printf("%lld: %s\n", next_idx, other.get_event(next_idx)->other.get_name());
            result += other.get_event(next_idx)->other.get_name() + Signal_names[(int)other.get_event(next_idx)->op];
        }

        next = &(other.get_event(next_idx)->other);
        next_idx = next->get_history_length();
    }

    printf("%s\n", result.c_str());

    return result;
}

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
        
        message += "[(";
        message += op->get_sender_name();
        message += " = " + std::to_string(op->get_sender_value()) + " | " + sender_address + ") ";
        
        message += Signal_names[(int)op->get_signal()];
        
        message += " (";
        message += op->get_other_name();
        message += " = " + std::to_string(op->get_other_value()) + " | " + other_address + ")]"; // + "\n"
    }
    else
    {
        message += Signal_names[(int)op->get_signal()] + ": ";
        message += "[";
        message += op->get_sender_name();
        message += " = " + std::to_string(op->get_sender_value()) + " | " + sender_address + "]"; //  + "\n"
    }

    dump_message(message, op->get_signal());
}

/*
void Int_dumper::create_
*/

void Int_dumper::signal(Int_signal signal_type, const Intercepted_int &sender)
{
    Operation *op = new Operation(signal_type, sender, sender);
    history.push_back(op);

    visual_dump(signal_type, op);

    // create_box(op);
    /*  
     * Тут если конструктор - проводим стрелочку в ещё не существующую struct_#id_dtor
     * Соответственно у них имена struct_#id_ctor и struct_#id_dtor
     * Стрелки можно проставить в конце циклом по max_id (?)
     * 
     * Если, скажем, плюс, туда тоже стрелочку отправляем
     * Создаём ноду плюса - имя будет struct_#id1_#id2_plus
     * Из него стрелку проводим в следующий после op элемент вектора
     * Видимо, их будем нумеровать
    */

    if (required.size() && required[required.size() - 1] == signal_type)
    {
        send_message(false, op);
        
        std::string message = " FROM ";
        dump_text(message);
        
        bool required_binary = history[history.size() - 2]->get_other_name() ? true : false;
        send_message(required_binary, history[history.size() - 2], true);
        reset_required();
    }
    else
        send_message(false, op);
}

void Int_dumper::signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    Operation *op = new Operation(signal_type, sender, other);
    history.push_back(op);
    
    visual_dump(signal_type, op);
    
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
        reset_required();
    }
    else
    {
        send_message(true, op);
    }
}

void Int_dumper::decrease_functions_in(const char *func_name)
{
    --functions_in;

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
