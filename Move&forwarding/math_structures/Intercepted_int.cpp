#include "Intercepted_int.hpp"
#include "Int_signal_receiver.hpp"

#include "../Microscope/Int_dumper.hpp"

size_t Intercepted_int::max_id = 0;

Intercepted_int::Intercepted_int()
: num(0), assignment_cnt(0), comparison_cnt(0), address(this), name(nullptr), parent(Int_dumper::get_dumper()) 
{
    id = max_id++;

    last_op = Int_signal::CONSTRUCT;
}

Intercepted_int::Intercepted_int(int arg_num)
: num(arg_num), assignment_cnt(1), comparison_cnt(0), address(this), name(nullptr), parent(Int_dumper::get_dumper()) 
{
    id = max_id++;

    Int_signal signal = Int_signal::CONSTRUCT;
    report(false, signal);

    last_op = signal;
}

Intercepted_int::Intercepted_int(const Intercepted_int &other)
: num(other.get_num()), assignment_cnt(1), comparison_cnt(0), address(this), name(nullptr), parent(Int_dumper::get_dumper()) 
{
    id = max_id++;

    if (!other.get_history().empty())
        history += "COPY(" + other.get_history() + ")";
    else
    {
        history += "COPY("; 
        history += other.get_name();
        history += ")";
    }

    Int_signal signal = Int_signal::COPY;
    report(false, signal, &other); // не передаю other

    last_op = signal;
    change_with = other.get_id();

    clear_history();
}

#ifdef MOVE_ON
Intercepted_int::Intercepted_int(Intercepted_int &&other)
: num(other.get_num()), assignment_cnt(1), comparison_cnt(0), address(this), name(nullptr), parent(other.parent) 
{
    id = max_id++;

    if (!other.get_history().empty())
        history += "MOVE(" + other.get_history() + ")";
    else
    {
        history += "MOVE(";
        history += other.get_name();
        history += ")";
    }
    
    Int_signal signal = Int_signal::MOVE;
    report(false, signal, &other); // не передаю other

    last_op = signal;
    change_with = other.get_id();

    // Опустошаем объект, из которого перемещали 
    other.num = 0;

    clear_history();
}
#endif

Intercepted_int::Intercepted_int(int arg_num, const char *arg_name)
: num(arg_num), assignment_cnt(1), comparison_cnt(0), address(this), name(nullptr), parent(Int_dumper::get_dumper())
{
    id = max_id++;

    set_name(arg_name);

    history += "CTOR(";
    history += name;
    history += ")";
    
    Int_signal signal = Int_signal::CONSTRUCT;
    report(false, signal);

    last_op = signal;

    history.clear();
}


Intercepted_int::~Intercepted_int()
{        
    history += "DTOR(";
    history += name;
    history += ")";
    
    Int_signal signal = Int_signal::DESTRUCT;
    report(false, signal);

    if (name)
        delete [] name;
    // clear_local_history();
}

void Intercepted_int::set_name(const char *arg_name) const
{
    size_t name_len = strlen(arg_name);

    name = new char[name_len + 1];
    strncpy(name, arg_name, name_len);
    name[name_len] = '\0';
}

void Intercepted_int::set_history(std::string suggestion)
{
    history = suggestion;
}

void Intercepted_int::clear_history()
{
    history.clear();
}


// void Intercepted_int::memorize(const Intercepted_int &other, Int_signal op) const
// {
//     Event *event = new Event(other, op, other.get_history_length() - 1); 
//     local_history.push_back(event); 
// }

void Intercepted_int::report(bool binary, Int_signal op, Intercepted_int const *other) const
{
    if (parent)
    {
        if (binary || other)
        {
            parent->signal(op, *this, *other);
            // memorize(*other, op);
        }
        else
        {
            parent->signal(op, *this);
            // memorize(*this, op);
        }
    }
    
}

// void Intercepted_int::clear_local_history()
// {
//     size_t history_size = local_history.size();

//     for (long long i = history_size - 1; i >= 0; --i)
//     {
//         delete local_history[i];
//     }
// }

const Intercepted_int& Intercepted_int::operator=(const Intercepted_int& other) 
{ 
    assignment_cnt++;
    comparison_cnt += other.get_comparison_cnt();
    
    num = other.get_num();

    history = name;
    history += " COPY= " + (other.get_history().empty() ? other.get_name() : other.get_history());

    Int_signal signal = Int_signal::ASSIGN_COPY;
    report(true, signal, &other);

    last_op = signal;
    change_with = other.get_id();
    
    clear_history();

    return *this; 
} 

#ifdef MOVE_ON
const Intercepted_int& Intercepted_int::operator=(Intercepted_int &&other)
{
    assignment_cnt++;
    comparison_cnt += other.get_comparison_cnt();
    
    num = other.get_num();
    // delete [] name;
    // set_name(other.name);
    history = name;
    history += " MOVE= " + (other.get_history().empty() ? other.get_name() : other.get_history());

    Int_signal signal = Int_signal::ASSIGN_MOVE;
    report(true, signal, &other);

    last_op = signal;
    change_with = other.get_id();

    // Опустошаем объект, из которого перемещали 
    other.num = 0;

    clear_history();
    
    return *this; 
}
#endif

const Intercepted_int& Intercepted_int::operator=(const int& other) 
{ 
    num = other;
    assignment_cnt++;

    return *this; 
} 

const Intercepted_int& Intercepted_int::operator+=(const Intercepted_int &other) 
{ 
    num += other.get_num();

    history += name;
    history += " += " + (other.get_history().empty() ? other.get_name() : other.get_history());

    Int_signal signal = Int_signal::ASSIGN_ADD;
    report(true, signal, &other);

    last_op = signal;
    change_with = other.get_id();

    clear_history();

    return *this; 
}

const Intercepted_int& Intercepted_int::operator-=(const Intercepted_int &other) 
{ 
    // comparison_cnt++;
    
    num -= other.get_num();
    
    history += name;
    history += " -= " + (other.get_history().empty() ? other.get_name() : other.get_history());
    
    Int_signal signal = Int_signal::ASSIGN_SUB;
    report(true, signal, &other);

    last_op = signal;
    change_with = other.get_id();

    clear_history();

    return *this; 
} 

const Intercepted_int& Intercepted_int::operator*=(const Intercepted_int &other) 
{ 
    num *= other.get_num(); 

    history += name;
    history += " *= " + (other.get_history().empty() ? other.get_name() : other.get_history());

    Int_signal signal = Int_signal::ASSIGN_MUL;
    report(true, signal, &other);

    last_op = signal;
    change_with = other.get_id();

    clear_history();

    return *this;
}

const Intercepted_int& Intercepted_int::operator/=(const Intercepted_int &other) 
{ 
    if (other.get_num() == 0) 
    {
        return *this; 
    }

    num /= other.get_num(); 

    history += name;
    history += " /= " + (other.get_history().empty() ? other.get_name() : other.get_history());

    Int_signal signal = Int_signal::ASSIGN_DIV;
    report(true, signal, &other);

    last_op = signal;
    change_with = other.get_id();

    clear_history();

    return *this; 
} 

const Intercepted_int Intercepted_int::operator+(const Intercepted_int &other) const 
{ 
    Int_signal signal = Int_signal::ADD;
    report(true, signal, &other);

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
    
    return { num / other.get_num() };
}

const Intercepted_int Intercepted_int::operator++(int)
{
    Intercepted_int old = *this;
    
    num++;

    if (history.empty())
    {
        history = name;
        history += "++";
    }
    else
        history = "(" + history + ")++";
    
    Int_signal signal = Int_signal::POST_INC;
    report(false, signal);

    last_op = signal;

    clear_history();

    return old;
}

const Intercepted_int& Intercepted_int::operator++()
{
    ++num;

    
    if (history.empty())
    {
        history = "++";
        history += name;
        // history += "++";
    }
    else
        history = "++(" + history + ")";
    
    Int_signal signal = Int_signal::PREF_INC;
    report(false, signal);

    last_op = signal;

    clear_history();

    return *this;
}

const Intercepted_int Intercepted_int::operator--(int)
{
    Intercepted_int old = *this;
    
    num--;

    if (history.empty())
    {
        history = name;
        history += "--";
    }
    else
        history = "(" + history + ")--";
    
    Int_signal signal = Int_signal::POST_DEC;
    report(false, signal);

    last_op = signal;

    clear_history();

    return old;
}

const Intercepted_int& Intercepted_int::operator--()
{
    --num;

    if (history.empty())
    {
        history = "--";
        history += name;
        // history += "++";
    }
    else
        history = "--(" + history + ")";
    
    Int_signal signal = Int_signal::PREF_DEC;
    report(false, signal);

    last_op = signal;

    clear_history();

    return *this;
}


bool Intercepted_int::operator==(const Intercepted_int &other) const
{ 
    comparison_cnt++;
    
    Int_signal signal = Int_signal::EQ;
    report(true, signal, &other);
    
    if (num == other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator!=(const Intercepted_int &other) const
{ 
    comparison_cnt++;
    
    Int_signal signal = Int_signal::NOT_EQ;
    report(true, signal, &other);
    
    if (num != other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator<(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    Int_signal signal = Int_signal::LESS;
    report(true, signal, &other);
    
    return num < other.get_num(); 
}

bool Intercepted_int::operator>(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    Int_signal signal = Int_signal::MORE;
    report(true, signal, &other);
    
    if (num > other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator<=(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    Int_signal signal = Int_signal::LESS_EQ;
    report(true, signal, &other);
    
    if (num <= other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator>=(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    Int_signal signal = Int_signal::MORE_EQ;
    report(true, signal, &other);

    if (num >= other.get_num()) 
        return true; 
    return false; 
}

// Event::Event(const Intercepted_int &arg_other, Int_signal arg_op, long long arg_other_prev_op_idx)
// : other(arg_other), op(arg_op), other_prev_op_idx(arg_other_prev_op_idx) 
// {
//     if (arg_other_prev_op_idx >= 0 && 
//     ((other.get_event(arg_other_prev_op_idx)->op == Int_signal::CONSTRUCT) || (other.get_event(arg_other_prev_op_idx)->op == Int_signal::ASSIGN_COPY)))
//     {
//         other_prev_op_idx = -1;
//     }
// }
