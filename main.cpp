// Doug Steiert
// CS 5803 SRT Division Simulation

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "functions.h"
using namespace std;

int main()
{
    ifstream fin;
    vector<int> dividend, divisor;
    string temporaryVal;

    fin.open("data.txt");

    fin >> temporaryVal;
    //Assume first value is dividend.
    for(int i = 0; i < temporaryVal.length(); i++)
    {
        dividend.push_back((temporaryVal.at(i)-'0'));
    }
    for(int i = 0; i < dividend.size(); i++)
        cout << dividend[i];
    cout << endl;

    temporaryVal.clear();
    fin >> temporaryVal;
    for(int i = 0; i < temporaryVal.length(); i++)
    {
        divisor.push_back((temporaryVal.at(i)-'0'));
    }
    for(int i = 0; i < divisor.size(); i++)
        cout << divisor[i];
    cout << endl;

    fin.close();

    int repeat = 0;
    int halfOfDividend = (dividend.size()/2) - 1;
    while(repeat < dividend.size())
    {

    }

    return 0;
}
