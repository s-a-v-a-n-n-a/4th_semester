#ifndef INTERCEPTED_INT
#define INTERCEPTED_INT

#include <cstdio>
#include "Int_container.hpp"

class Intercepted_int
{
private:
    int num;

    mutable size_t assignment_cnt;
    mutable size_t comparison_cnt;

    Int_container *parent;
    Intercepted_int *address;

public:
    Intercepted_int()
    : num(0), assignment_cnt(0), comparison_cnt(0), address(this) {}
    
    Intercepted_int(int arg_num)
    : num(arg_num), assignment_cnt(1), comparison_cnt(0), address(this) {}

    int get_num() const { return num; }
    size_t get_assignment_cnt() const { return assignment_cnt; }
    size_t get_comparison_cnt() const { return comparison_cnt; }
    
    const Intercepted_int& operator=(const Intercepted_int& other) 
    { 
        num = other.get_num();
        assignment_cnt++;
        comparison_cnt += other.get_comparison_cnt();
        
        if (address != this)
            parent->signal(Int_signal::ASSIGN, *this, other);
        
        return *this; 
    } 

    const Intercepted_int& operator=(const int& other) 
    { 
        num = other;
        assignment_cnt++;

        return *this; 
    } 

	const Intercepted_int& operator+=(const Intercepted_int &other) 
    { 
        num += other.get_num();

        if (address != this)
            parent->signal(Int_signal::ASSIGN_ADD, *this, other);

        return *this; 
    }

	const Intercepted_int& operator-=(const Intercepted_int &other) 
    { 
        // comparison_cnt++;
        
        num -= other.get_num();

        if (address != this)
            parent->signal(Int_signal::ASSIGN_SUB, *this, other);

        return *this; 
    } 
	
    const Intercepted_int& operator*=(const Intercepted_int &other) 
    { 
        num *= other.get_num(); 

        if (address != this)
            parent->signal(Int_signal::ASSIGN_MUL, *this, other);

        return *this;
    }
	
    const Intercepted_int& operator/=(const Intercepted_int &other) 
	{ 
		if (other.get_num() == 0) 
		{
			return *this; 
		}

		num /= other.get_num(); 

        if (address != this)
            parent->signal(Int_signal::ASSIGN_DIV, *this, other);

		return *this; 
	} 
	
	const Intercepted_int operator+(const Intercepted_int &other) const 
    { 
        if (address != this)
            parent->signal(Int_signal::ADD, *this, other);

        return { num + other.get_num() }; 
    } 
	const Intercepted_int operator-(const Intercepted_int &other) const 
    { 
        // comparison_cnt++;
        if (address != this)
            parent->signal(Int_signal::ASSIGN_SUB, *this, other);

        return { num - other.get_num() }; 
    }
	const Intercepted_int operator*(const Intercepted_int &other) const 
    { 
        if (address != this)
            parent->signal(Int_signal::ASSIGN_MUL, *this, other);
        
        return { num * other.get_num() }; 
    }

	const Intercepted_int operator/(const Intercepted_int &other) const 
	{
		if (other.get_num() == 0) 
		{
			return Intercepted_int(*this); 
		}

		if (address != this)
            parent->signal(Int_signal::ASSIGN_DIV, *this, other);
        
        return { num / other.get_num() };
	}

	bool operator==(const Intercepted_int &other) const
    { 
        comparison_cnt++;
        
        if (address != this)
            parent->signal(Int_signal::EQ, *this, other);
        
        if (num == other.get_num()) 
            return true; 
        return false; 
    }

	bool operator!=(const Intercepted_int &other) const
    { 
        comparison_cnt++;
        
        if (address != this)
            parent->signal(Int_signal::NOT_EQ, *this, other);
        
        if (num != other.get_num()) 
            return true; 
        return false; 
    }
	
    bool operator<(const Intercepted_int &other) const
    {
        comparison_cnt++;
        
        if (address != this)
            parent->signal(Int_signal::LESS, *this, other);
        
        if (num < other.get_num()) 
            return true; 
        return false; 
    }

    bool operator>(const Intercepted_int &other) const
    {
        comparison_cnt++;
        
        if (address != this)
            parent->signal(Int_signal::MORE, *this, other);
        
        if (num > other.get_num()) 
            return true; 
        return false; 
    }

    bool operator<=(const Intercepted_int &other) const
    {
        comparison_cnt++;
        
        if (address != this)
            parent->signal(Int_signal::LESS_EQ, *this, other);
        
        if (num <= other.get_num()) 
            return true; 
        return false; 
    }

    bool operator>=(const Intercepted_int &other) const
    {
        comparison_cnt++;
        
        if (address != this)
            parent->signal(Int_signal::MORE_EQ, *this, other);

        if (num >= other.get_num()) 
            return true; 
        return false; 
    }
};

#endif // INTERCEPTED_INT
