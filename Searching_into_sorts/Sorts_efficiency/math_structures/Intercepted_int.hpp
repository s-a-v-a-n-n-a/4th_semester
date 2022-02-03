#ifndef INTERCEPTED_INT
#define INTERCEPTED_INT

#include <cstdio>

class Intercepted_int
{
private:
    int num;

    mutable size_t assignment_cnt;
    mutable size_t comparison_cnt;

public:
    Intercepted_int()
    : num(0), assignment_cnt(0), comparison_cnt(0) {}
    
    Intercepted_int(int arg_num)
    : num(arg_num), assignment_cnt(1), comparison_cnt(0) {}

    int get_num() const { return num; }
    size_t get_assignment_cnt() const { return assignment_cnt; }
    size_t get_comparison_cnt() const { return comparison_cnt; }
    
    const Intercepted_int& operator=(const Intercepted_int& other) 
    { 
        num = other.get_num();
        assignment_cnt++;
        comparison_cnt += other.get_comparison_cnt();
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
        return *this; 
    }
	const Intercepted_int& operator-=(const Intercepted_int &other) 
    { 
        // comparison_cnt++;
        
        num -= other.get_num();
        return *this; 
    } 
	
    const Intercepted_int& operator*=(const Intercepted_int &other) 
    { 
        num *= other.get_num(); 
        return *this;
    }
	
    const Intercepted_int& operator/=(const Intercepted_int &other) 
	{ 
		if (other.get_num() == 0) 
		{
			return *this; 
		}

		num /= other.get_num(); 
		return *this; 
	} 
	
	const Intercepted_int operator+(const Intercepted_int &other) const 
    { 
        return { num + other.get_num() }; 
    } 
	const Intercepted_int operator-(const Intercepted_int &other) const 
    { 
        // comparison_cnt++;
        
        return { num - other.get_num() }; 
    }
	const Intercepted_int operator*(const Intercepted_int &other) const 
    { 
        return { num * other.get_num() }; 
    }

	const Intercepted_int operator/(const Intercepted_int &other) const 
	{
		if (other.get_num() == 0) 
		{
			return Intercepted_int(*this); 
		}

		return { num / other.get_num() };
	}

	bool operator==(const Intercepted_int &other) const
    { 
        comparison_cnt++;
        
        if (num == other.get_num()) 
            return true; 
        return false; 
    }

	bool operator!=(const Intercepted_int &other) const
    { 
        comparison_cnt++;
        
        if (num != other.get_num()) 
            return true; 
        return false; 
    }
	
    bool operator<(const Intercepted_int &other) const
    {
        comparison_cnt++;
        
        if (num < other.get_num()) 
            return true; 
        return false; 
    }

    bool operator>(const Intercepted_int &other) const
    {
        comparison_cnt++;
        
        if (num > other.get_num()) 
            return true; 
        return false; 
    }

    bool operator<=(const Intercepted_int &other) const
    {
        comparison_cnt++;
        
        if (num <= other.get_num()) 
            return true; 
        return false; 
    }

    bool operator>=(const Intercepted_int &other) const
    {
        comparison_cnt++;
        
        if (num >= other.get_num()) 
            return true; 
        return false; 
    }
};

#endif // INTERCEPTED_INT
