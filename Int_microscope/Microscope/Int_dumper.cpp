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

Int_dumper *Int_dumper::dumper = nullptr;
Dumper_destroyer Int_dumper::destroyer;

Int_dumper::Int_dumper()
: Int_signal_receiver(), functions_in(0), max_tmp_vars_amount(0)
{
    dump = new HTML_dump(DUMP_FILE);
    dump->dump("<!DOCTYPE html><head><link rel=\"stylesheet\" href=\"style.css\"></head>");
    dump->open_tag(PREFIX, 0);

    // dumper = this;
}

Int_dumper::~Int_dumper() 
{
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

std::string Int_dumper::restore_history(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    std::string result;
    if (sender.get_id() == other.get_id())
    {
        printf("Return(\n");
        return result;
    }
    
    long long next_idx = other.get_history_length();
    // Intercepted_int &next;

    printf("Here\n");

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

void Int_dumper::signal(Int_signal signal_type, const Intercepted_int &sender)
{
    Operation *op = new Operation(signal_type, sender, sender);
    history.push_back(op);

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
