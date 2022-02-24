#ifndef INT_DUMPER_HPP
#define INT_DUMPER_HPP

#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cassert>

#include "../math_structures/Int_signal_receiver.hpp"
#include "Operations_history.hpp"
#include "Dump_messages.hpp"
#include "Dot_dump.hpp"

extern const std::string Signal_names[];

#define VAR(name, value) \
        Intercepted_int name(value, #name);
        // name.set_name((std::string(#name) + std::string("\0")).c_str()); 

#define FUNC(func) \
        Int_dumper::get_dumper()->increase_funcsions_in(); \
        FILE* log = fopen(DUMP_FILE, "ab"); \
        for (size_t i = 0; i < Int_dumper::get_dumper()->get_functions_in(); ++i) \
            fprintf(log, "%s", TAB); \
        fprintf(log, "%s\n", ARROW_PARTS[0]); \
        for (size_t i = 0; i < Int_dumper::get_dumper()->get_functions_in(); ++i) \
            fprintf(log, "%s", TAB); \
        fprintf(log, "%s%s\n", ARROW_PARTS[1], #func); \
        fclose(log);

class Int_dumper;

class Dumper_destroyer
{
private:
	Int_dumper *dumper;

public:
	~Dumper_destroyer();

	void initialize(Int_dumper *arg_dumper);
};

class Int_dumper : public Int_signal_receiver
{
private:
    static Int_dumper *dumper;
	static Dumper_destroyer destroyer;

    std::vector<Operation*> history;
    HTML_dump *dump;
    Dot_dump *dot;

    size_t copy_amount;
    size_t move_amount;
     
    long long functions_in;
    size_t max_func_id;

    std::vector<Int_signal> required;
    std::vector<size_t> last_change_op; // индекс - это id переменной, значение - индекс в истории


protected:
	Int_dumper();
	friend class Dumper_destroyer;

public:
    static Int_dumper *get_dumper();
    ~Int_dumper();

    long long get_functions_in() { return functions_in; }

    void decrease_functions_in(const char *func_name);
    void increase_functions_in(const char *func_name);

    // std::string restore_history(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other);

    void visual_dump(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other);
    void make_connections(const Intercepted_int &sender, std::string &current_struct);
    
    void send_message(bool binary, Operation *op, bool no_end = false);
    
    void dump_message(std::string message, Int_signal signal_type);
    void dump_text(std::string text);

    void update_history();
    void reset_required();

    void copy_move_detect(Int_signal signal_type);

    void signal(Int_signal signal_type, const Intercepted_int &sender) override;
    void signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other) override;
};

class Spy
{
private:
    char *func;

public:
    Spy(const char *func_name);
    ~Spy();
};

#endif // INT_DUMPER_HPP
