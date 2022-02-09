#ifndef INTERCEPTED_INT
#define INTERCEPTED_INT

#include <cstdio>

class Int_signal_receiver;

class Intercepted_int
{
private:
    int num;

    mutable size_t assignment_cnt;
    mutable size_t comparison_cnt;

    Int_signal_receiver *parent;
    Intercepted_int *address;

    static size_t max_id;
    size_t id;

public:
    Intercepted_int();
    Intercepted_int(int arg_num);

    size_t get_id() const { return id; }
    void set_id(size_t arg_id) { id = arg_id; }
    
    int get_num() const { return num; }
    size_t get_assignment_cnt() const { return assignment_cnt; }
    size_t get_comparison_cnt() const { return comparison_cnt; }

    void set_comparison_cnt(const size_t arg_comparison_cnt) { comparison_cnt = arg_comparison_cnt; }
    void set_assignment_cnt(const size_t arg_assignment_cnt) { assignment_cnt = arg_assignment_cnt; }

    void set_parent(Int_signal_receiver *arg_contact) { parent = arg_contact; }
    
    const Intercepted_int& operator=(const Intercepted_int& other);
    const Intercepted_int& operator=(const int &other);

    // const Intercepted_int& operator+=(const Intercepted_int &other);
    // const Intercepted_int& operator-=(const Intercepted_int &other);
	// const Intercepted_int& operator*=(const Intercepted_int &other);
	// const Intercepted_int& operator/=(const Intercepted_int &other);
	// const Intercepted_int operator+(const Intercepted_int &other) const;
	// const Intercepted_int operator-(const Intercepted_int &other) const;
	// const Intercepted_int operator*(const Intercepted_int &other) const;
    // const Intercepted_int operator/(const Intercepted_int &other) const;

	// bool operator==(const Intercepted_int &other) const;
    // bool operator!=(const Intercepted_int &other) const;
	bool operator<(const Intercepted_int &other) const;
    bool operator>(const Intercepted_int &other) const;
    // bool operator<=(const Intercepted_int &other) const;
    // bool operator>=(const Intercepted_int &other) const;
};

#endif // INTERCEPTED_INT
