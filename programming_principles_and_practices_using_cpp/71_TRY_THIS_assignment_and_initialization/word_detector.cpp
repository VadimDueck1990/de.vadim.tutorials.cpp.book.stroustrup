#include "std_lib_facilities.h"

int main()
{
    string previous = ""; // previous word; initialized to "not a word"
    string current;       // current word

    // read a stream of words
    while(cin >> current)
    {
        if (previous == current) //check if the word is the same as last
        {
            cout << "repeated word: " << current << '\n';
        }
        previous = current;
    }  
}