#include "std_lib_facilities.h"

// simple dictionary: list of sorted words
int main()
{
    string disliked_word = "vadim";
    vector<string> words;

    cout << "***** Dictionary program *****" << '\n';
    cout << "Please type in some words separated by spaces." << "\n\n";

    // read whitespace-separated words
    for(string temp; cin>>temp;)
        words.push_back(temp);  // push into vector
    cout << "Number of words: " << words.size() << '\n';

    // sort the words
    sort(words);

    for(int i = 0; i < words.size(); ++i)
    {
        if((i == 0 || words[i-1] != words[i]) && disliked_word != words[i])    // is this a new word?
            cout << words[i] << '\n';
    }
}