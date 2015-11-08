// Doug Steiert
// CS 5803 SRT Division Simulation

#include <iostream>
#include <cmath>
#include <fstream>
#include <deque>
#include "functions.h"
using namespace std;

int main()
{
    ifstream fin;
    deque<int> dividend, divisor, normalDivisor;
    string temporaryVal;
    int numberMoves = 0;
    int carry = 0;
    int negativeValue = 0;
    int numberShifts = 0;
    int shiftLimit = 0;

    fin.open("data.txt");

    fin >> temporaryVal;
    //Assume first value is dividend.
    for(int i = 0; i < temporaryVal.length(); i++)
    {
        dividend.push_back((temporaryVal.at(i)-'0'));
    }
    /*for(int i = 0; i < dividend.size(); i++)
        cout << dividend[i];
    cout << endl;*/

    //Reset the current input stream in order to grab a new one.
    temporaryVal.clear();
    fin >> temporaryVal;
    for(int i = 0; i < temporaryVal.length(); i++)
    {
        divisor.push_back((temporaryVal.at(i)-'0'));
    }
    /*for(int i = 0; i < divisor.size(); i++)
        cout << divisor[i];
    cout << endl;*/

    fin.close();

    normalize(divisor, numberMoves);
    normalDivisor = divisor;
    /*for(int i = 0; i < divisor.size(); i++)
        cout << divisor[i];
    cout << endl;*/
    adjustDividend(dividend, numberMoves);
    divisorComplement(divisor, negativeValue);
    /*for(int i = 0; i < divisor.size(); i++)
        cout << divisor[i];*/

    shiftLimit = divisor.size() + 1;
    while(numberShifts <= shiftLimit)
    {
        subtractDivisor(dividend, divisor, numberShifts, negativeValue, shiftLimit, normalDivisor);
        cout << numberShifts << endl;
    }
    for(int i = 0; i < dividend.size(); i++)
       cout << dividend[0];

    return 0;
}
