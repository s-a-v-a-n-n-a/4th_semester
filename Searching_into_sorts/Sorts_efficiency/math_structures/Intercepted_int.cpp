#include "Intercepted_int.hpp"
// #include "Int_signal_receiver.hpp"

Intercepted_int::Intercepted_int()
: num(0), assignment_cnt(0), comparison_cnt(0), parent(nullptr) {}

Intercepted_int::Intercepted_int(int arg_num)
: num(arg_num), assignment_cnt(1), comparison_cnt(0), parent(nullptr) {}

const Intercepted_int& Intercepted_int::operator=(const Intercepted_int& other) 
{ 
    num = other.get_num();
    assignment_cnt++;
    comparison_cnt += other.get_comparison_cnt();
    
    return *this; 
} 

const Intercepted_int& Intercepted_int::operator=(const int& other) 
{ 
    num = other;
    assignment_cnt++;

    return *this; 
} 

// const Intercepted_int& Intercepted_int::operator+=(const Intercepted_int &other) 
// { 
//     num += other.get_num();
//     return *this; 
// }

// const Intercepted_int& Intercepted_int::operator-=(const Intercepted_int &other) 
// { 
//     // comparison_cnt++;
    
//     num -= other.get_num();
//     return *this; 
// } 

// const Intercepted_int& Intercepted_int::operator*=(const Intercepted_int &other) 
// { 
//     num *= other.get_num(); 
//     return *this;
// }

// const Intercepted_int& Intercepted_int::operator/=(const Intercepted_int &other) 
// { 
//     if (other.get_num() == 0) 
//     {
//         return *this; 
//     }

//     num /= other.get_num(); 
//     return *this; 
// } 

// const Intercepted_int Intercepted_int::operator+(const Intercepted_int &other) const 
// { 
//     return { num + other.get_num() }; 
// } 
// const Intercepted_int Intercepted_int::operator-(const Intercepted_int &other) const 
// { 
//     // comparison_cnt++;
//     return { num - other.get_num() }; 
// }
// const Intercepted_int Intercepted_int::operator*(const Intercepted_int &other) const 
// { 
//     return { num * other.get_num() }; 
// }

// const Intercepted_int Intercepted_int::operator/(const Intercepted_int &other) const 
// {
//     if (other.get_num() == 0) 
//     {
//         return Intercepted_int(*this); 
//     }

//     return { num / other.get_num() };
// }

bool Intercepted_int::operator==(const Intercepted_int &other) const
{ 
    comparison_cnt++;
    
    if (num == other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator!=(const Intercepted_int &other) const
{ 
    comparison_cnt++;
    
    if (num != other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator<(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    if (num < other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator>(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    if (num > other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator<=(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    if (num <= other.get_num()) 
        return true; 
    return false; 
}

bool Intercepted_int::operator>=(const Intercepted_int &other) const
{
    comparison_cnt++;
    
    if (num >= other.get_num()) 
        return true; 
    return false; 
}