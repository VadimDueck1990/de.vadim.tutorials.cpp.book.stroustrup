#include "std_lib_facilities.h"

int main()
{
    cout << "Please enter your first name, second name and age\n";
    string first;
    string second;
    double age_in_years;
    double age_in_months;
    cin >> first >> second >> age_in_years; // read two strings
    age_in_months = age_in_years * 12;      // calculate the age in months
    cout << "Hello, " << first << " " << second << "(age " << age_in_months <<" months)\n";
    keep_window_open();
}