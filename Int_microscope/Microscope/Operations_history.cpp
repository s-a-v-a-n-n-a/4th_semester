#include "Operations_history.hpp"

size_t Operation::max_tmp_id = 0; 

Operation::Operation(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
: op(signal_type), 
  sender_id(sender.get_id()), 
  sender_value(sender.get_num()), 
  other_id(other.get_id()), 
  other_value(other.get_num())
{
    printf("before strlen\n");
    if (sender.get_name())
    {
    	printf("%s\n", sender.get_name());
		size_t sender_name_len = strlen(sender.get_name());
		sender_name = new char[sender_name_len + 1];
		strncpy(sender_name, sender.get_name(), sender_name_len);
		sender_name[sender_name_len] = '\0';
    }
	else
	{
		std::string tmps_name = TMP_VAR + std::to_string(max_tmp_id++);
		size_t tmp_name_len = strlen(tmps_name.c_str());
		sender_name = new char[tmp_name_len + 1];
		strncpy(sender_name, tmps_name.c_str(), tmp_name_len);
		sender_name[tmp_name_len] = '\0';

		sender.set_name(sender_name);
	}
    printf("between strlens\n");
	if (&sender != &other)
	{
		if (other.get_name())
		{
			size_t other_name_len = strlen(other.get_name());
			other_name = new char[other_name_len + 1];
			strncpy(other_name, other.get_name(), other_name_len);
			other_name[other_name_len] = '\0';
		}
		else
		{
			std::string tmps_name = TMP_VAR + std::to_string(max_tmp_id++);
			size_t tmp_name_len = strlen(tmps_name.c_str());
			other_name = new char[tmp_name_len + 1];
			strncpy(other_name, tmps_name.c_str(), tmp_name_len);
			other_name[tmp_name_len] = '\0';

			other.set_name(sender_name);
		}
	}
    printf("after strlen\n");

    sender_address = &sender;
    other_address = &other;
}

Operation::~Operation()
{
    delete [] sender_name;
    delete [] other_name;
}
