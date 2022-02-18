#ifndef OPERATIONS_HISTORY_HPP
#define OPERATIONS_HISTORY_HPP

#include <cstring>

#include "../math_structures/Intercepted_int.hpp"
#include "../math_structures/Int_signal_types.hpp"

#include "Dump_messages.hpp"

class Operation
{
private:
    Int_signal op;

    char *sender_name;
    const Intercepted_int *sender_address;
    size_t sender_id;
    int sender_value;

    char *other_name;
    const Intercepted_int *other_address;
    size_t other_id;
    int other_value;

    static size_t max_tmp_id;

public:
    Operation(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other);
    ~Operation();

    void set_sender_name(const char *name);
    void set_other_name(const char *name);

    void create_sender_name();
    void create_other_name();

    Int_signal get_signal() const { return op; }

    char *get_sender_name() const { return sender_name; }
    char *get_other_name() const { return other_name; }

    const Intercepted_int *get_sender_address() const { return sender_address; }
    const Intercepted_int *get_other_address() const { return other_address; }

    int get_sender_value() const { return sender_value; }
    int get_other_value() const { return other_value; }

    size_t get_sender_id() const { return sender_id; }
    size_t get_other_id() const { return other_id; }
};

#endif // OPERATIONS_HISTORY_HPP
