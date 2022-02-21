#ifndef INTERCEPTED_INT
#define INTERCEPTED_INT

#include <cstdio>
#include <cstring>
#include <vector>

// #define MEMORISE(op); \
//         Event *event = new Event(other, op); \
//         local_history.push_back(event); \

class Int_signal_receiver;
enum class Int_signal;

class Intercepted_int;

struct Event;

class Intercepted_int
{
private:
    int num;

    mutable size_t assignment_cnt;
    mutable size_t comparison_cnt;

    Int_signal_receiver *parent;
    Intercepted_int *address;

    mutable char *name;
    
    static size_t max_id;
    size_t id;

    mutable std::vector<Event*> local_history;

public:
    Intercepted_int();
    Intercepted_int(int arg_num);
    Intercepted_int(const Intercepted_int &other);
    Intercepted_int(Intercepted_int &&other);
    Intercepted_int(int arg_num, const char *arg_name);

    ~Intercepted_int();

    size_t get_id() const { return id; }
    char *get_name() const { return name; }
    int get_num() const { return num; }
    size_t get_assignment_cnt() const { return assignment_cnt; }
    size_t get_comparison_cnt() const { return comparison_cnt; }

    size_t get_history_length() const { return local_history.size(); }
    Event *get_event(const size_t idx) const { return local_history[idx]; }
    std::vector<Event*> &get_history() { return local_history; }

    void set_id(size_t arg_id) { id = arg_id; }
    void set_name(const char *arg_name) const;
    void set_parent(Int_signal_receiver *arg_contact) { parent = arg_contact; }

    void memorize(const Intercepted_int &other, Int_signal op) const;
    void report(bool binary, Int_signal op, Intercepted_int const *other = nullptr) const;

    void clear_history();
    
    const Intercepted_int& operator=(const Intercepted_int &other);
    const Intercepted_int& operator=(Intercepted_int &&other);
    const Intercepted_int& operator=(const int &other);

    const Intercepted_int& operator+=(const Intercepted_int &other);
    const Intercepted_int& operator-=(const Intercepted_int &other);
	const Intercepted_int& operator*=(const Intercepted_int &other);
	const Intercepted_int& operator/=(const Intercepted_int &other);
	const Intercepted_int operator+(const Intercepted_int &other) const;
	const Intercepted_int operator-(const Intercepted_int &other) const;
	const Intercepted_int operator*(const Intercepted_int &other) const;
    const Intercepted_int operator/(const Intercepted_int &other) const;

    const Intercepted_int operator++(int);
    const Intercepted_int& operator++();
    const Intercepted_int operator--(int);
    const Intercepted_int& operator--();

	bool operator==(const Intercepted_int &other) const;
    bool operator!=(const Intercepted_int &other) const;
	bool operator<(const Intercepted_int &other) const;
    bool operator>(const Intercepted_int &other) const;
    bool operator<=(const Intercepted_int &other) const;
    bool operator>=(const Intercepted_int &other) const;
};

struct Event
{
    const Intercepted_int &other;
    Int_signal op;

    long long other_prev_op_idx;

    Event(const Intercepted_int &arg_other, Int_signal arg_op, long long arg_other_prev_op_idx);
};

#endif // INTERCEPTED_INT
