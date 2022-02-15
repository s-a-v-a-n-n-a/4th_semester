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
    "=",
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

    std::string message;
    for (size_t i = 0; i < functions_in; ++i)
        message += TAB;

    char sender_address[256] = "";
    memset(sender_address, '\0', 256);
    sprintf(sender_address, "%p", (&sender));

    message += Signal_names[(int)signal_type] + ": " + op->get_sender_name() + " = " + std::to_string(sender.get_num()) + " | " + sender_address + " |\n";
    
    dump_message(message, signal_type);
}

void Int_dumper::signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    Operation *op = new Operation(signal_type, sender, other);
    history.push_back(op);
    
    std::string message;
    for (size_t i = 0; i < functions_in; ++i)
        message += TAB;
    
    char sender_address[256] = "";
    memset(sender_address, '\0', 256);
    sprintf(sender_address, "%p", (&sender));

    char other_address[256] = "";
    memset(other_address, '\0', 256);
    sprintf(other_address, "%p", (&other));
    
    message += "(";
    message += op->get_sender_name();
    message += " = " + std::to_string(sender.get_num()) + " | " + sender_address + " |) " + Signal_names[(int)signal_type] + " (" + op->get_other_name() + " = " + std::to_string(other.get_num()) + " | " + other_address + " |)\n";
    
    dump_message(message, signal_type);
}

void Int_dumper::decrease_functions_in(const char *func_name)
{
   --functions_in;

   std::string message;
    for (size_t i = 0; i < functions_in; ++i)
        message += TAB;
    message += ARROW_PARTS[1];
    // message += "Step out of function";
    message += func_name;
    message += '\n';

    dump_text(message);
}

void Int_dumper::increase_functions_in(const char *func_name)
{
    std::string message;
    for (size_t i = 0; i < functions_in; ++i)
        message += TAB;
    message += ARROW_PARTS[0];
    // message += "Step in function\n";
    dump_text(message);

    //"bgcolor"
    // message = "Step in function";
    message = func_name;
    message += '\n';
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
