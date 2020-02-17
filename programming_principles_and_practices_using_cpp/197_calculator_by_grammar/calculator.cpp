#include "std_lib_facilities.h"
/**
 * To implement the calculator, we need four functions:
 * one to read tokens plus one for each rule of our grammar
 */

//--------------------------------------------------------------------------

class Token // a very simple user-defined type
{
public:
    char kind;      // what kind of token
    double value;   // for numbers: a value
    Token(char ch)  // make a Token from a char
        :kind(ch), value(0) {}
    Token(char ch, double val)   // make a Token from a char and a double
        :kind(ch), value(val) {}
};

//--------------------------------------------------------------------------

Token get_token()    // read a token from cin
{
    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    //not yet   case ';':    // for "print"
    //not yet   case 'q':    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/': 
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        {    
            cin.putback(ch);         // put digit back into the input stream
            double val;
            cin >> val;              // read a floating-point number
            return Token('8',val);   // let '8' represent "a number"
        }
    default:
        error("Bad token");
    }
}

//--------------------------------------------------------------------------

// functions to match the grammar rules:
double expression(); // deal with + and -
double term();       // deal with *, / and %
double primary();    // deal with numbers and parentheses

//--------------------------------------------------------------------------

int main()
try {
    while (cin)
        cout << expression() << '\n';
    keep_window_open("~0");
}
catch (exception& e) {
    cerr << e.what() << endl;
    keep_window_open ("~1");
    return 1;
}
catch (...) {
    cerr << "exception \n";
    keep_window_open ("~2");
    return 2;
}

//--------------------------------------------------------------------------

/**
 * The grammar for expression looks like this:
 * Expression:
 *      Term
 *      Expression '+' Term
 *      Expression '-' Term 
 */
double expression()
{
    double left = term();  // read and evaluate a Term
    Token t = get_token(); // get the next token

    while (true)
    {
        // see which kind of token it is
        switch (t.kind)
        {
        case '+':
            left += term(); // evaluate Term and add
            t = get_token();
            break;
        case '-':
            left -= term(); // evaluate Term and subtract
            t = get_token();
            break;
        default:
            // finally: no more + and -; return the answer
            return left;
        }
    }
}

//--------------------------------------------------------------------------

/**
 * The grammar rule for Term looks like this:
 * Term:
 *      Primary
 *      Term '*' Primary
 *      Term '/' Primary
 *      Term '%' Primary
 */
double term()
{
    double left = primary(); // read and evaluate a Primary
    Token t = get_token();   // get the next token

    while (true)
    {
        // see which kind of token it is
        switch (t.kind)
        {
        case '*':
            left *= primary(); // evaluate primary and multiply
            t = get_token();
            break;
        case '/':
        {
            double d = primary(); // evaluate primary
            if (d == 0)
                error("divide by zero");
            left /= d; //  and divide
            t = get_token();
            break;
        }
        default:
            // finally: no more * and /; return the answer
            return left;
        }
    }
}

//--------------------------------------------------------------------------

/**
 * The grammar rule for Primary looks like this:
 * Primary:
 *      Number
 *      '(' Expression ')'
 */
double primary()
{
    Token t = get_token();
    switch (t.kind)
    {
    case '(': // handle expression
    {
        double d = expression(); // evaluate expression
        t = get_token();
        if (t.kind != ')')
            error("')' expected");
        return d;
    }
    case '8':           // we use '8' to represent a number
        return t.value; // return the numbers value
    default:
        error("primary expected");
    }
}