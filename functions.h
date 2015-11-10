#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

using namespace std;
#include <iostream>
#include <deque>

//Pre: a deque of any integers that represents an unnormalized, binary number and the number of moves
//to store how many times the number was shifted.
//Post: the deque that was passed in by reference has its values updated to reflect a
//normalized, binary number (remove the 0's), and the number of moves is updated with how many
//shifts were done.
void normalize(deque<int>& notNormalized, int& numberMoves);

//Pre: a deque of integers that represents a binary number and the number of moves it took to normalize
//the previous deque.
//Post: the deque is updated and its values have been shifted to the left as many times as the number
//of moves, and 0's were inserted at the end.
void adjustDividend(deque<int>& dividend, int& numberMoves);

//Pre: a deque of integers that represents the divisor, an integer to represent the negative value, and calculation time
//to represent the delta t time it took.
//Post: the divisor is updated to be the 2's complement of what it was - bits were flipped and 1 was added. The
//negative value was set to 1, which represents the negative in the very front for 2's complement. Calculation time
//was incremented according to the 2's complement time, given in the project description.
void divisorComplement(deque<int>& divisor, int& negative, int& calculationTime);

//Pre: two deque's, one is the dividend the other is the divisor, and the carry are passed in.
//Post: the divisor is not updated at all, it was just used to represent the subtraction. The dividend is
//updated to reflect adding a bit in the divisor with a bit in the dividend along with the carry. The carry
//is also updated at the end of this function, if there is a carry to the add with the negative value.
void subtractDivisor(deque<int>& dividend, deque<int> divisor, int& carry);

//Pre: a deque of integers (the dividend), the number of shifts performed so far, the shift limit (which is the
//is the max shifts allowed), and the calculation time are passed in.
//Post: the dividend is updated in respect to what is done after subtraction and the result is positive (shift left, insert a 1).
//As long as the number of shifts are less than or equal to the shift limit, this is performed and then the number of shifts is
//updated. Calculation time is also incremented to reflect the shifting.
void positiveResult(deque<int>& dividend, int& numberShifts, int shiftLimit, int& calculationTime);

//Pre: a deque of integers (the dividend), the number of shifts performed so far, the shift limit (which is the
//is the max shifts allowed), the normalized divisor binary representation, the carry, and the calculation time are passed in.
//Post: the dividend is updated in respect to what is done after subtraction and the result is negative (shift left, insert a 0
//and then add the normalized divisor instead of subtracting the normalized, 2's complement).
//As long as the number of shifts are less than or equal to the shift limit, this is performed and then the number of shifts is
//updated. Calculation time is also incremented to reflect the shifting. The carry is updated to whatever value it may come out to,
//and it is also used in the subtraction calls.
void negativeResult(deque<int>& dividend, int& numberShifts, int shiftLimit, deque<int>& normalDivisor, int& carry, int& calculationTime);

//Pre: a deque of integers that represents the dividend, the number of shifts performed so far, and the calculation time are
//passed in.
//Post: the initial shifting of 0's is performed on the dividend, that is, all 0's are popped and pushed into the back before the first
//subtraction is done. The number of shifts are also updated to account for this shifting. Lastly, the calculation time is updated per shift
//performed.
void initialShift(deque<int>& dividend, int& numberShifts, int& calculationTime);

#include "functions.cpp"
#endif // FUNCTIONS_H_INCLUDED
