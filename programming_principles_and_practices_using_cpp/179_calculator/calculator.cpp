#include "std_lib_facilities.h"

int main()
{
    cout << "Please enter expression (we can handle + and -): ";
    int lval = 0;
    int rval;
    char op;
    int res;

    // read something like 1 + 3
    cin >> lval >> op >> rval;

    if(op == '+')
        res = lval + rval; // adition
    else if(op == '-')
        res = lval - rval; // subtraction

    cout << "Result: " << res << '\n';
    keep_window_open();
    return 0;
}