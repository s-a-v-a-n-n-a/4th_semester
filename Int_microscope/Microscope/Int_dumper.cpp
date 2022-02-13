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
    "CONSTRUCTION",
    "DESTRUCTION"
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

    std::string message;
    for (size_t i = 0; i < functions_in; ++i)
        message += TAB;

    char sender_address[256] = "";
    memset(sender_address, '\0', 256);
    sprintf(sender_address, "%p", (&sender));

    message += "Happend " + Signal_names[(int)signal_type] + " with " + op->get_sender_name() + " which is int " + std::to_string(sender.get_num()) + " by address " + sender_address + "\n";
    
    dump_message(message, signal_type);
}

void Int_dumper::signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    Operation *op = new Operation(signal_type, sender, other);
    history.push_back(op);
    
    // static long int doing = 0;

    
    // const char* mode = nullptr;
    // if (!doing)
    //     mode = "wb";
    // else
    //     mode = "ab";
    // FILE* log = fopen(DUMP_FILE, mode);
    
    std::string message;
    for (size_t i = 0; i < functions_in; ++i)
        message += TAB;
    
    char sender_address[256] = "";
    memset(sender_address, '\0', 256);
    sprintf(sender_address, "%p", (&sender));

    char other_address[256] = "";
    memset(other_address, '\0', 256);
    sprintf(other_address, "%p", (&other));
    
    message += "Operation " + Signal_names[(int)signal_type] + " on " + op->get_sender_name() + " which is int " + std::to_string(sender.get_num()) + " by address " + sender_address + " with " + op->get_other_name() + " which is " + std::to_string(other.get_num()) + " by address " + other_address + "\n";
    
    dump_message(message, signal_type);

    // for (size_t i = 0; i < functions_in; ++i)
    //     fprintf(log, "%s", TAB);
    // fprintf(log, "%s<%s>", PREFIX, FONT);
    // for (int i = 0; i < font_params_amount; ++i)
    // {
    //     if (FONT_PARAMS[i])
    //         fprintf(log, "%s=%s ", FONT_PARAM_NAMES[i], FONT_PARAMS[i][(int)signal_type]);
    // }
    // fprintf(log, "\b>%s</%s>\n", message, FONT);

    // fclose(log);

    // ++doing;
}

void Int_dumper::decrease_functions_in()
{
   --functions_in;

   std::string message;
    for (size_t i = 0; i < functions_in; ++i)
        message += TAB;
    message += ARROW_PARTS[1];
    message += "Step out of function\n";

    dump_text(message);
}

void Int_dumper::increase_functions_in()
{
    std::string message;
    for (size_t i = 0; i < functions_in; ++i)
        message += TAB;
    message += ARROW_PARTS[0];
    // message += "Step in function\n";
    dump_text(message);

    //"bgcolor"
    message = "Step in function\n";
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

Spy::Spy()
{
    Int_dumper::get_dumper()->increase_functions_in();
}

Spy::~Spy()
{
    Int_dumper::get_dumper()->decrease_functions_in();
}
