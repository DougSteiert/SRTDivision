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
    string temporaryVal, fileName;
    int numberMoves = 0;
    int carry = 0;
    int negativeValue = 0;
    int numberShifts = 0;
    int shiftLimit = 0;
    int calculationTime = 0;

    //Open up the filestream that contains the data.
    cout << "Please enter the file name you wish to access data from: ";
    cin >> fileName;
    cout << endl;
    fin.open(fileName);

    //Checks to see if the file can be opened, if not an error message is
    //displayed.
    if(fin)
    {
        //Iterates through all pairs of dividend and divisor that are in the
        //file.
        while(fin >> temporaryVal)
        {
            //Empty the deques and reset other values for the next use.
            dividend.clear();
            divisor.clear();
            int numberMoves = 0;
            int carry = 0;
            int negativeValue = 0;
            int numberShifts = 0;
            int shiftLimit = 0;
            int calculationTime = 0;

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

            temporaryVal.clear();

            cout << "The dividend is: ";
            for(int i = 0; i < dividend.size(); i ++)
                cout << dividend[i];
            cout << endl << "The divisor is: ";
            for(int i = 0; i < divisor.size(); i++)
                cout << divisor[i];
            cout << endl;

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
                    positiveResult(dividend, numberShifts, shiftLimit,
                                    calculationTime);
                }
                else
                {
                    carry = 0;
                    negativeResult(dividend, numberShifts, shiftLimit,
                                   normalDivisor,carry, calculationTime);
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
            cout << "The total number of shifts performed was: " <<
                numberShifts << endl;
            cout << "The calculation time in delta t was: " << calculationTime
                << "t" << endl;
            cout << "The final remainder was: ";
            for(int i = 0; i < ((dividend.size()/2)); i++)
               cout << dividend[i];
            cout << endl << "The final quotient was: ";
            for(int i = (dividend.size()/2); i < dividend.size(); i++)
                cout << dividend[i];
            cout << endl << endl;
        }
    }
    else
    {
        cout << "That file was not able to open." << endl;
    }

    fin.close();

    return 0;
}
