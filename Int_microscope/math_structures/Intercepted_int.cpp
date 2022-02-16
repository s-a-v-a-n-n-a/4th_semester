#include "Intercepted_int.hpp"
#include "Int_signal_receiver.hpp"

#include "../Microscope/Int_dumper.hpp"

size_t Intercepted_int::max_id = 0;

Intercepted_int::Intercepted_int()
: num(0), assignment_cnt(0), comparison_cnt(0), address(this), name(nullptr), parent(Int_dumper::get_dumper()) 
{
    id = max_id++;
}

Intercepted_int::Intercepted_int(int arg_num)
: num(arg_num), assignment_cnt(1), comparison_cnt(0), address(this), name(nullptr), parent(Int_dumper::get_dumper()) 
{
    id = max_id++;

    Int_signal signal = Int_signal::CONSTRUCT;
    report(false, signal);
    // if (parent) 
    //     parent->signal(signal, *this);
    // memorize(*this, signal);
}

Intercepted_int::Intercepted_int(const Intercepted_int &other)
: num(other.get_num()), assignment_cnt(1), comparison_cnt(0), address(this), name(nullptr), parent(Int_dumper::get_dumper()) 
{
    id = max_id++;

    Int_signal signal = Int_signal::COPY;
    report(false, signal, &other); // не передаю other

    // if (parent) 
    //     parent->signal(signal, *this);
    // memorize(*this, signal);
}

Intercepted_int::Intercepted_int(int arg_num, const char *arg_name)
: num(arg_num), assignment_cnt(1), comparison_cnt(0), address(this), name(nullptr), parent(Int_dumper::get_dumper())
{
    id = max_id++;

    // size_t name_len = strlen(arg_name);
    // printf("new var length %zu\n", name_len);
    // name = new char[name_len + 1];
    // strncpy(name, arg_name, name_len);
    // name[name_len] = '\0';
    set_name(arg_name);

    Int_signal signal = Int_signal::CONSTRUCT;
    report(false, signal);
    
    // if (parent) 
    //     parent->signal(Int_signal::CONSTRUCT, *this);
    // memorize(*this, signal);
}


Intercepted_int::~Intercepted_int()
{        
    Int_signal signal = Int_signal::DESTRUCT;
    report(false, signal);

    // if (parent) 
    //     parent->signal(Int_signal::DESTRUCT, *this);

    if (name)
        delete [] name;
    clear_history();
}

void Intercepted_int::set_name(const char *arg_name) const
{
    size_t name_len = strlen(arg_name);

    name = new char[name_len + 1];
    strncpy(name, arg_name, name_len);
    name[name_len] = '\0';
}

void Intercepted_int::memorize(const Intercepted_int &other, Int_signal op) const
{
    Event *event = new Event(other, op, other.get_history_length() - 1); 
    local_history.push_back(event); 
}

void Intercepted_int::report(bool binary, Int_signal op, Intercepted_int const *other) const
{
    if (parent)
    {
        if (binary || other)
        {
            parent->signal(op, *this, *other);
            memorize(*other, op);
        }
        else
        {
            parent->signal(op, *this);
            memorize(*this, op);
        }
    }
    
}

void Intercepted_int::clear_history()
{
    size_t history_size = local_history.size();

    for (long long i = history_size - 1; i >= 0; --i)
    {
        delete local_history[i];
    }
}

const Intercepted_int& Intercepted_int::operator=(const Intercepted_int& other) 
{ 
    assignment_cnt++;
    comparison_cnt += other.get_comparison_cnt();
    
    num = other.get_num();

    Int_signal signal = Int_signal::ASSIGN;
    report(true, signal, &other);
    
    // if (parent) 
    //     parent->signal(Int_signal::ASSIGN, *this, other);
    
    return *this; 
} 

const Intercepted_int& Intercepted_int::operator=(const int& other) 
{ 
    num = other;
    assignment_cnt++;

    return *this; 
} 

const Intercepted_int& Intercepted_int::operator+=(const Intercepted_int &other) 
{ 
    num += other.get_num();

    Int_signal signal = Int_signal::ASSIGN_ADD;
    report(true, signal, &other);
    // if (parent)
    //     parent->signal(Int_signal::ASSIGN_ADD, *this, other);

    return *this; 
}

const Intercepted_int& Intercepted_int::operator-=(const Intercepted_int &other) 
{ 
    // comparison_cnt++;
    
    num -= other.get_num();

    Int_signal signal = Int_signal::ASSIGN_SUB;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::ASSIGN_SUB, *this, other);

    return *this; 
} 

const Intercepted_int& Intercepted_int::operator*=(const Intercepted_int &other) 
{ 
    num *= other.get_num(); 

    Int_signal signal = Int_signal::ASSIGN_MUL;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::ASSIGN_MUL, *this, other);

    return *this;
}

const Intercepted_int& Intercepted_int::operator/=(const Intercepted_int &other) 
{ 
    if (other.get_num() == 0) 
    {
        return *this; 
    }

    num /= other.get_num(); 

    Int_signal signal = Int_signal::ASSIGN_DIV;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::ASSIGN_DIV, *this, other);

    return *this; 
} 

const Intercepted_int Intercepted_int::operator+(const Intercepted_int &other) const 
{ 
    Int_signal signal = Int_signal::ADD;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::ADD, *this, other);

    return { num + other.get_num() }; 
} 
const Intercepted_int Intercepted_int::operator-(const Intercepted_int &other) const 
{ 
    // comparison_cnt++;
    Int_signal signal = Int_signal::SUB;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::SUB, *this, other);

    return { num - other.get_num() }; 
}
const Intercepted_int Intercepted_int::operator*(const Intercepted_int &other) const 
{ 
    Int_signal signal = Int_signal::MUL;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::MUL, *this, other);
    
    return { num * other.get_num() }; 
}

const Intercepted_int Intercepted_int::operator/(const Intercepted_int &other) const 
{
    // if (other.get_num() == 0) 
    // {
    //     return other;
    // }

    Int_signal signal = Int_signal::DIV;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::DIV, *this, other);
    
    return { num / other.get_num() };
}

const Intercepted_int Intercepted_int::operator++(int)
{
    Intercepted_int old = *this;
    
    num++;
    
    Int_signal signal = Int_signal::PREF_INC;
    report(false, signal);
    
    // if (parent)
    //     parent->signal(Int_signal::PREF_INC, *this, *this);

    return old;
}

const Intercepted_int& Intercepted_int::operator++()
{
    ++num;
    
    Int_signal signal = Int_signal::POST_INC;
    report(false, signal);
    
    // if (parent)
    //     parent->signal(Int_signal::POST_INC, *this, *this);

    return *this;
}

const Intercepted_int Intercepted_int::operator--(int)
{
    Intercepted_int old = *this;
    
    num--;
    
    Int_signal signal = Int_signal::POST_DEC;
    report(false, signal);
    
    // if (parent)
    //     parent->signal(Int_signal::POST_DEC, *this, *this);

    return old;
}

const Intercepted_int& Intercepted_int::operator--()
{
    --num;
    
    Int_signal signal = Int_signal::PREF_DEC;
    report(false, signal);
    
    // if (parent)
    //     parent->signal(Int_signal::PREF_DEC, *this, *this);

    return *this;
}


bool Intercepted_int::operator==(const Intercepted_int &other) const
{ 
    comparison_cnt++;
    
    Int_signal signal = Int_signal::EQ;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::EQ, *this, other);
    
    if (num == other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator!=(const Intercepted_int &other) const
{ 
    comparison_cnt++;
    
    Int_signal signal = Int_signal::NOT_EQ;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::NOT_EQ, *this, other);
    
    if (num != other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator<(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    Int_signal signal = Int_signal::LESS;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::LESS, *this, other);
    
    return num < other.get_num(); 
}

bool Intercepted_int::operator>(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    Int_signal signal = Int_signal::MORE;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::MORE, *this, other);
    
    if (num > other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator<=(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    Int_signal signal = Int_signal::LESS_EQ;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::LESS_EQ, *this, other);
    
    if (num <= other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator>=(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    Int_signal signal = Int_signal::MORE_EQ;
    report(true, signal, &other);
    
    // if (parent)
    //     parent->signal(Int_signal::MORE_EQ, *this, other);

    if (num >= other.get_num()) 
        return true; 
    return false; 
}

Event::Event(const Intercepted_int &arg_other, Int_signal arg_op, long long arg_other_prev_op_idx)
: other(arg_other), op(arg_op), other_prev_op_idx(arg_other_prev_op_idx) 
{
    if (arg_other_prev_op_idx >= 0 && 
    ((other.get_event(arg_other_prev_op_idx)->op == Int_signal::CONSTRUCT) || (other.get_event(arg_other_prev_op_idx)->op == Int_signal::ASSIGN)))
    {
        other_prev_op_idx = -1;
    }
}
