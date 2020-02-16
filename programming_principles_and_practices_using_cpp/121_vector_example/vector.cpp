#include "std_lib_facilities.h"

// read some temperature into a vector
int main()
{
    vector<double> temps;           // temperatures
    for(double temp; cin >> temp;)  // read into temp
    {
        temps.push_back(temp);      // put temp into vector
    }

    // compute mean temperature
    double sum = 0;
    for(double x : temps) sum += x;
    cout << "Average temperature: " << sum/temps.size() << '\n';

    // compute median temperature
    sort(temps);        // sort temperatures
    cout << "Median temperature: " << temps[temps.size()/2] << '\n';
}