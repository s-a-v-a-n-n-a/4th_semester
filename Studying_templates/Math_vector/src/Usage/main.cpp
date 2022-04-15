#include "../Math_vector/Math_vector.hpp"

int main()
{
    Math_vector<int, 4> first{1, 2, 3, 4};
    Math_vector<int, 4> second{2, 2, 2, 2};

    printf("%d\n", first.dot(second));
    
    return 0;
}