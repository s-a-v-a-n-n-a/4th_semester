#include "Intercepted_int.hpp"
#include "Int_signal_receiver.hpp"

size_t Intercepted_int::max_id = 0;

Intercepted_int::Intercepted_int()
: num(0), assignment_cnt(0), comparison_cnt(0), address(this), name(nullptr), parent(nullptr) 
{
    id = max_id++;
}

Intercepted_int::Intercepted_int(int arg_num)
: num(arg_num), assignment_cnt(1), comparison_cnt(0), address(this), parent(nullptr) 
{
    id = max_id++;
}

Intercepted_int::~Intercepted_int()
{
    if (name)
        delete [] name;
}

void Intercepted_int::set_name(const char *arg_name)
{
    size_t name_len = strlen(arg_name);

    name = new char[name_len];
    strncpy(name, arg_name, name_len);
}

const Intercepted_int& Intercepted_int::operator=(const Intercepted_int& other) 
{ 
    assignment_cnt++;
    comparison_cnt += other.get_comparison_cnt();
    
    if (parent) 
        parent->signal(Int_signal::COPY, *this, other);

    num = other.get_num();
    id = other.get_id();
    
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

    if (parent)
        parent->signal(Int_signal::ASSIGN_ADD, *this, other);

    return *this; 
}

const Intercepted_int& Intercepted_int::operator-=(const Intercepted_int &other) 
{ 
    // comparison_cnt++;
    
    num -= other.get_num();

    if (parent)
        parent->signal(Int_signal::ASSIGN_SUB, *this, other);

    return *this; 
} 

const Intercepted_int& Intercepted_int::operator*=(const Intercepted_int &other) 
{ 
    num *= other.get_num(); 

    if (parent)
        parent->signal(Int_signal::ASSIGN_MUL, *this, other);

    return *this;
}

const Intercepted_int& Intercepted_int::operator/=(const Intercepted_int &other) 
{ 
    if (other.get_num() == 0) 
    {
        return *this; 
    }

    num /= other.get_num(); 

    if (parent)
        parent->signal(Int_signal::ASSIGN_DIV, *this, other);

    return *this; 
} 

const Intercepted_int Intercepted_int::operator+(const Intercepted_int &other) const 
{ 
    if (parent)
        parent->signal(Int_signal::ADD, *this, other);

    return { num + other.get_num() }; 
} 
const Intercepted_int Intercepted_int::operator-(const Intercepted_int &other) const 
{ 
    // comparison_cnt++;
    if (parent)
        parent->signal(Int_signal::ASSIGN_SUB, *this, other);

    return { num - other.get_num() }; 
}
const Intercepted_int Intercepted_int::operator*(const Intercepted_int &other) const 
{ 
    if (parent)
        parent->signal(Int_signal::ASSIGN_MUL, *this, other);
    
    return { num * other.get_num() }; 
}

const Intercepted_int Intercepted_int::operator/(const Intercepted_int &other) const 
{
    if (other.get_num() == 0) 
    {
        return Intercepted_int(*this); 
    }

    if (parent)
        parent->signal(Int_signal::ASSIGN_DIV, *this, other);
    
    return { num / other.get_num() };
}

const Intercepted_int Intercepted_int::operator++(int)
{
    Intercepted_int old = *this;
    
    num++;
    
    if (parent)
        parent->signal(Int_signal::PREF_INC, *this, *this);

    return old;
}

const Intercepted_int& Intercepted_int::operator++()
{
    ++num;
    
    if (parent)
        parent->signal(Int_signal::POST_INC, *this, *this);

    return *this;
}

const Intercepted_int Intercepted_int::operator--(int)
{
    Intercepted_int old = *this;
    
    num--;
    
    if (parent)
        parent->signal(Int_signal::POST_DEC, *this, *this);

    return old;
}

const Intercepted_int& Intercepted_int::operator--()
{
    --num;
    
    if (parent)
        parent->signal(Int_signal::PREF_DEC, *this, *this);

    return *this;
}


bool Intercepted_int::operator==(const Intercepted_int &other) const
{ 
    comparison_cnt++;
    
    if (parent)
        parent->signal(Int_signal::EQ, *this, other);
    
    if (num == other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator!=(const Intercepted_int &other) const
{ 
    comparison_cnt++;
    
    if (parent)
        parent->signal(Int_signal::NOT_EQ, *this, other);
    
    if (num != other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator<(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    if (parent)
        parent->signal(Int_signal::LESS, *this, other);
    
    return num < other.get_num(); 
}

bool Intercepted_int::operator>(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    if (parent)
        parent->signal(Int_signal::MORE, *this, other);
    
    if (num > other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator<=(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    if (parent)
        parent->signal(Int_signal::LESS_EQ, *this, other);
    
    if (num <= other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator>=(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    if (parent)
        parent->signal(Int_signal::MORE_EQ, *this, other);

    if (num >= other.get_num()) 
        return true; 
    return false; 
}