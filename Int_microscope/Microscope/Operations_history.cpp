#include "Operations_history.hpp"

size_t Operation::max_tmp_id = 0; 

Operation::Operation(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
: op(signal_type), 
  sender_id(sender.get_id()), 
  sender_value(sender.get_num()), 
  other_id(other.get_id()), 
  other_value(other.get_num())
{
    if (sender.get_name())
    {
    	set_sender_name(sender.get_name());
    }
	else
	{
		create_sender_name();
		sender.set_name(sender_name);
	}
    
	if (&sender != &other)
	{
		if (other.get_name())
		{
			set_other_name(other.get_name());
		}
		else
		{
			create_other_name();
			other.set_name(sender_name);
		}
	}

    sender_address = &sender;
    other_address = &other;
}

void Operation::set_sender_name(const char *name)
{
	size_t sender_name_len = strlen(name);
	sender_name = new char[sender_name_len + 1];
	strncpy(sender_name, name, sender_name_len);
	sender_name[sender_name_len] = '\0';
}

void Operation::set_other_name(const char *name)
{
	size_t other_name_len = strlen(name);
	other_name = new char[other_name_len + 1];
	strncpy(other_name, name, other_name_len);
	other_name[other_name_len] = '\0';
}


void Operation::create_sender_name()
{
	std::string tmps_name = TMP_VAR + std::to_string(max_tmp_id++);
	set_sender_name(tmps_name.c_str());
}

void Operation::create_other_name()
{
	std::string tmps_name = TMP_VAR + std::to_string(max_tmp_id++);
	set_other_name(tmps_name.c_str());
}


Operation::~Operation()
{
    delete [] sender_name;
    delete [] other_name;
}
