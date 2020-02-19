/*
    Simple calculator

    Originally pirated by:
    Vadim Dück 2020, all rights reserved

    This program implements a basic expression calculator.
    Input from cin; output to cout.

    The grammar for input is:

    Calculation:
        Print
        Quit
        Statement
        Calculation Statement    

    Print:          Quit:
        ;               q

 

    Statement:
        Declaration
        Expression

    Declaration:
        "let" Name "=" Expression

    Expression:
        Term
        Expression + Term
        Expression - Term

    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary

    Primary:
        Number
        ( Expression )
        - Primary
        + Primary

    Number:
        floating-point-literal


        Input comes from cin through the Token_stream called ts.
*/

#include "std_lib_facilities.h"

//------------------------------------------------------------------------------
// variables and names
const string prompt = "> "; // used to indicate the program is waiting for input
const string result = "= "; // used to indicate that what follows is a result
const char number = '8';    // t.kind == number means that t is a number token
const char quit = 'q';      // t.kind == quit means that t is a quit token
const char print = ';';     // t.kind == print means that t is a print token

//------------------------------------------------------------------------------
// prototypes
double expression(); // declaration so that primary() can call expression()
//------------------------------------------------------------------------------
class Token
{
public:
    char kind;    // what kind of token
    double value; // for numbers: a value
    Token(char ch) : kind(ch), value(0) {}
    Token(char ch, double val) : kind(ch), value(val) {}
};

//------------------------------------------------------------------------------
class Token_stream
{
public:
    Token_stream();        // make a Token_stream that reads from cin
    Token get();           // get a Token (get() is defined elsewhere)
    void putback(Token t); // put a Token back
    void ignore(char c);   // discard characters up to and including a c
private:
    bool full;    // is there a Token in the buffer?
    Token buffer; // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------
// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    : full(false), buffer(0) // no Token in buffer
{
}

//------------------------------------------------------------------------------
// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");
    buffer = t;  // copy t to buffer
    full = true; // buffer is now full
}

//------------------------------------------------------------------------------
Token Token_stream::get()
{
    if (full)
    { // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch; // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch)
    {
    case print:
    case quit:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
        return Token(ch); // let each character represent itself
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        cin.putback(ch); // put digit back into the input stream
        double val;
        cin >> val;                // read a floating-point number
        return Token(number, val); //  represent "a number"
    }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------
// c represents the kind of Token
void Token_stream::ignore(char c)
{
    // first look in buffer
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    // now search input:
    char ch = 0;
    while (cin >> ch)
        if (ch == c)
            return;
}

//------------------------------------------------------------------------------
class Variable
{
public:
    string name;
    double value;
};

//------------------------------------------------------------------------------
Token_stream ts; // provides get() and putback()
vector<Variable> var_table;

//------------------------------------------------------------------------------
// return the value of the Variable named s
double get_value(string s)
{
    for (const Variable &v : var_table)
    {
        if (v.name == s)
            return v.value;
    }
    error("get: undefined variable ", s);
}

//------------------------------------------------------------------------------
void set_value(string s, double d)
{
    for (Variable &v : var_table)
    {
        if (v.name == s)
        {
            v.value = d;
            return;
        }
    }
    error("set: undefined variable ", s);
}

//------------------------------------------------------------------------------
// TODO: explain function!
bool is_declared(string var)
{
    // TODO: implement
    return false;
}

//------------------------------------------------------------------------------
// TODO: explain function!
double define_name(string var, double val)
{
    // TODO: implement
    return 0.0;
}
//------------------------------------------------------------------------------
// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    { // handle '(' expression ')'
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
            error("')' expected");
        return d;
    }
    case number:
        return t.value; // return the number's value
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------
// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get(); // get the next token from token stream

    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0)
                error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            int i1 = narrow_cast<int>(left);
            int i2 = narrow_cast<int>(primary());
            if (i2 == 0)
                error("%: divide by zero");
            left = i1 % i2;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t); // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------
// deal with + and -
double expression()
{
    double left = term(); // read and evaluate a Term
    Token t = ts.get();   // get the next token from token stream

    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term(); // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term(); // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t); // put t back into the token stream
            return left;   // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------
// TODO: explain this function
double declaration()
{
    // TODO: implement
    return 0.0;
}
//------------------------------------------------------------------------------
// defines whether calculate() has to deal with declaration() or expression()
double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}
//------------------------------------------------------------------------------
// prepare the programm for the next calculation after a crash
void clean_up_mess()
{
    ts.ignore(print);
}
//------------------------------------------------------------------------------
// expression evaluation loop function
void calculate()
{
    while (cin)
        try
        {
            cout << prompt;
            Token t = ts.get();

            //discard all prints
            while (t.kind == print)
                t = ts.get();

            // quit
            if (t.kind == quit)
            {
                return;
            }
            ts.putback(t);
            cout << result << statement() << endl;
        }
        catch (const std::exception &e)
        {
            cerr << e.what() << endl; // write error message
            clean_up_mess();
        }
}

//------------------------------------------------------------------------------
int main() try
{
    calculate();
    keep_window_open();
    return 0;
}
catch (runtime_error &e)
{
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return 1;
}
catch (...)
{
    cerr << "exception \n";
    keep_window_open("~~");
    return 2;
}

//------------------------------------------------------------------------------