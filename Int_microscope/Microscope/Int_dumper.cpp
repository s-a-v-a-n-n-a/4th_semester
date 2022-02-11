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
    ">",
    ">=",
    "<",
    "<=",
    "==",
    "!="
};

Int_dumper *Int_dumper::dumper = nullptr;
Dumper_destroyer Int_dumper::destroyer;

Int_dumper::Int_dumper()
: Int_signal_receiver(), functions_in(0), max_tmp_vars_amount(0)
{
    dumper = this;
}

Int_dumper::~Int_dumper() {}

Int_dumper *Int_dumper::get_dumper()
{
	if (dumper == nullptr)
	{
		new Int_dumper();
		destroyer.initialize(dumper);
	}

	return dumper;
}

void Int_dumper::signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    static long int doing = 0;

    const char* mode = nullptr;
    if (!doing)
        mode = "wb";
    else
        mode = "ab";
    FILE* log = fopen(DUMP_FILE, mode);
    
    std::string message = "Operation " + Signal_names[(int)signal_type] + " on int " + std::to_string(sender.get_num()) + " by address " + std::to_string((int)(&sender)) + " with int " + std::to_string(other.get_num()) + " by address " + std::to_string((int)(&other));
    
    for (size_t i = 0; i < functions_in; ++i)
        fprintf(log, "%s", TAB);
    fprintf(log, "%s<%s>", PREFIX, FONT);
    for (int i = 0; i < font_params_amount; ++i)
    {
        if (FONT_PARAMS[i])
            fprintf(log, "%s=%s ", FONT_PARAM_NAMES[i], FONT_PARAMS[i][(int)signal_type]);
    }
    fprintf(log, "\b>%s</%s>\n", message, FONT);

    fclose(log);

    ++doing;
}

void Int_dumper::decrease_functions_in()
{
    --functions_in;
}

void Int_dumper::increase_functions_in()
{
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
