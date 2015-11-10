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
    int calculationTime = 0;

    //Open up the filestream that contains the data.
    fin.open("data.txt");

    fin >> temporaryVal;

    //Assume first value is dividend.
    for(int i = 0; i < temporaryVal.length(); i++)
    {
        dividend.push_back((temporaryVal.at(i)-'0'));
    }

    //Reset the current input stream in order to grab a new one.
    temporaryVal.clear();
    fin >> temporaryVal;
    for(int i = 0; i < temporaryVal.length(); i++)
    {
        divisor.push_back((temporaryVal.at(i)-'0'));
    }

    fin.close();

    normalize(divisor, numberMoves);
    normalDivisor = divisor;
    adjustDividend(dividend, numberMoves);
    divisorComplement(divisor, negativeValue, calculationTime);
    shiftLimit = divisor.size() + 1;
    initialShift(dividend, numberShifts, calculationTime);

    while(numberShifts < shiftLimit)
    {
        subtractDivisor(dividend, divisor, carry);
        if(carry == 1)
        {
            carry = 0;
            positiveResult(dividend, numberShifts, shiftLimit, calculationTime);
        }
        else
        {
            carry = 0;
            negativeResult(dividend, numberShifts, shiftLimit, normalDivisor, carry, calculationTime);
            if(numberShifts == shiftLimit && carry == 1)
            {
                carry = 0;
                dividend.pop_back();
                dividend.push_front(1);
                subtractDivisor(dividend, normalDivisor, carry);
            }
            carry = 0;
        }

    }
    cout << "Calculation time: " << calculationTime << "t" << endl;
    for(int i = 0; i < dividend.size(); i++)
       cout << dividend[i];

    return 0;
}
