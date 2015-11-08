#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

using namespace std;
#include <iostream>
#include <deque>

void normalize(deque<int>& notNormalized, int& numberMoves);
void adjustDividend(deque<int>& dividend, int& numberMoves);
void divisorComplement(deque<int>& divisor, int& negative);
void subtractDivisor(deque<int>& dividend, deque<int> divisor, int& carry);
void positiveResult(deque<int>& dividend, int& numberShifts, int shiftLimit);
void negativeResult(deque<int>& dividend, int& numberShifts, int shiftLimit);

#include "functions.cpp"
#endif // FUNCTIONS_H_INCLUDED
