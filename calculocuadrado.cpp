#include <iostream>

double square(double x) // square a double precision floating-point number
{
    return x * x;
}

void print_square(double x)
{
    std::cout << "The square of " << x << " is: " << square(x) << '\n';
}

int main()
{
    print_square(1.234); // print: the square of 1.234 is 1.52276
    print_square(5.555); // print: the square of 5.555 is 30.858
}