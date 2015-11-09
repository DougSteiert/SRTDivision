#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

using namespace std;
#include <iostream>
#include <deque>

void normalize(deque<int>& notNormalized, int& numberMoves);
void adjustDividend(deque<int>& dividend, int& numberMoves);
void divisorComplement(deque<int>& divisor, int& negative, int& calculationTime);
void subtractDivisor(deque<int>& dividend, deque<int> divisor, int& carry);
void positiveResult(deque<int>& dividend, int& numberShifts, int shiftLimit, int& calculationTime);
void negativeResult(deque<int>& dividend, int& numberShifts, int shiftLimit, deque<int>& normalDivisor, int& carry, int& calculationTime);
void initialShift(deque<int>& dividend, int& numberShifts, int& calculationTime);

#include "functions.cpp"
#endif // FUNCTIONS_H_INCLUDED
