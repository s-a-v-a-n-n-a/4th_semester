#ifndef INTERCEPTED_INT
#define INTERCEPTED_INT

#include <cstdio>
#include <cstring>

class Int_signal_receiver;

class Intercepted_int
{
private:
    int num;

    mutable size_t assignment_cnt;
    mutable size_t comparison_cnt;

    Int_signal_receiver *parent;
    Intercepted_int *address;

    char *name;
    
    static size_t max_id;
    size_t id;

public:
    Intercepted_int();
    Intercepted_int(int arg_num);

    ~Intercepted_int();

    size_t get_id() const { return id; }
    char *get_name() { return name; }
    int get_num() const { return num; }
    size_t get_assignment_cnt() const { return assignment_cnt; }
    size_t get_comparison_cnt() const { return comparison_cnt; }

    void set_id(size_t arg_id) { id = arg_id; }
    void set_name(const char *arg_name);
    void set_parent(Int_signal_receiver *arg_contact) { parent = arg_contact; }
    
    const Intercepted_int& operator=(const Intercepted_int& other);
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

#endif // INTERCEPTED_INT
