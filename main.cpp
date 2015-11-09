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
    cout << "The normalized divisor is: ";
    for(int i = 0; i < divisor.size(); i++)
        cout << divisor[i];
    cout << endl;
    adjustDividend(dividend, numberMoves);
    cout << "The adjusted dividend is: ";
    for(int i = 0; i < dividend.size(); i++)
        cout << dividend[i];
    cout << endl;
    divisorComplement(divisor, negativeValue, calculationTime);
    cout << "The 2's complement of the divisor is: ";
    for(int i = 0; i < divisor.size(); i++)
        cout << divisor[i];

    cout << endl;

    shiftLimit = divisor.size() + 1;
    initialShift(dividend, numberShifts, calculationTime);
    cout << "The dividend after shift of 0's is: ";
    for(int i = 0; i < dividend.size(); i++)
        cout << dividend[i];
    cout << endl << endl;
    cout << divisor.size() << endl;
    while(numberShifts < shiftLimit)
    {
        cout << "The current dividend is: ";
        for(int i = 0; i < dividend.size(); i++)
            cout << dividend[i];
        cout << endl << "The current divisor is: ";
        for(int i = 0; i < divisor.size(); i++)
            cout << divisor[i];
        cout << endl;
        cout << numberShifts << endl;
        subtractDivisor(dividend, divisor, carry);
        cout << "The carry is: " << carry << endl << endl;
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
