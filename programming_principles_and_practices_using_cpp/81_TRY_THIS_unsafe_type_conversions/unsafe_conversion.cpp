#include "std_lib_facilities.h"

int main()
{
    double d = 0;

    while(cin >> d)     // repeat the statements below
    {                   // as long as we type in numbers
        int i = d;      // try to squeeze a double into an int
        char c = i;      // try to squeeze an int into a char
        int i2 = c;     // get the integer value of the character

        cout << "original double d== " << d << '\n' // the original double
        << "converted integer i== " << i << '\n'      // converted to int
        << "int value of char c== " << i2 << '\n'      // converted to int 
        << "the actual char c== " << c << '\n';        // the char
    }
}