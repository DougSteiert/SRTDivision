// This normalizes the divisor before taking the 2's complement.
void normalize(deque<int>& notNormalized, int& numberMoves)
{
    //While the first bit is 0, pop it and insert a 0 at the end.
    while(notNormalized[0] == 0)
    {
       notNormalized.pop_front();
       notNormalized.push_back(0);
       numberMoves++;
    }
}

// This adjusts the dividend the number of times that the divisor
// had to be shifted in order to normalize it.
void adjustDividend(deque<int>& dividend, int& numberMoves)
{
    //For as many times are the divisor shifted to normalize, shift the dividend.
    while(numberMoves != 0)
    {
        dividend.pop_front();
        dividend.push_back(0);
        numberMoves--;
    }
}

// This does the 2's complement of the divisor.
void divisorComplement(deque<int>& divisor, int& negative, int& calculationTime)
{
    //Flip all the bits of the divisor.
    for(int i = 0; i < divisor.size(); i++)
    {
        if(divisor[i] == 0)
            divisor[i] = 1;
        else
            divisor[i] = 0;
    }

    //Add 1 to the divisor to finish the 2's complement, which may flip bits back and forth.
    int carry = 1;
    for(int j = divisor.size()-1; j >= 0; j--)
    {
        if(divisor[j] == 1 && carry == 1)
        {
            divisor[j] = 0;
            carry = 1;
        }
        else if(divisor[j] == 1 && carry == 0)
        {
            divisor[j] = 1;
            carry = 0;
        }
        else if(divisor[j] == 0 && carry == 1)
        {
            divisor[j] = 1;
            carry = 0;
        }
        else if(divisor[j] == 0 && carry == 0)
        {
            divisor[j] = 0;
            carry = 0;
        }
    }
    //The negative value to ensure the 2's complement is made 1.
    negative = 1;
    //Calculation time is incremented the length of the divisor.
    calculationTime = calculationTime + divisor.size();
}

//Performs the initial shifting of 0's on the dividend.
void initialShift(deque<int>& dividend, int& numberShifts, int& calculationTime)
{
    //While there are 0's in the front, pop them and insert a 0 on the end.
    //Each shift (pop) done is 3t, so update the calculation time.
    while(dividend[0] == 0)
    {
        dividend.pop_front();
        numberShifts++;
        calculationTime = calculationTime + 3;
        dividend.push_back(0);
    }
}

//If the subtraction of the divisor and dividend is positive, go to this function.
void positiveResult(deque<int>& dividend, int& numberShifts, int shiftLimit, int& calculationTime)
{
    //Check to make sure we are not going to shift more than the desired amount of times.
    if(numberShifts == shiftLimit)
        return;

    //Just a double check to make sure shifts are less than the limit.
    //If so, pop the front and insert a 1 at the end. Increment shifts each time.
    //Calculation time is updated 3t each shift.
    if(numberShifts < shiftLimit)
    {
        dividend.pop_front();
        numberShifts++;
        calculationTime = calculationTime + 3;
        dividend.push_back(1);
    }

    //As long as the shifts are less than the limit and the dividend front is 0, pop the dividend
    //and insert a 0 at the end. This is part of the occurring shifting of 0's at the end of subtractions.
    //Calculation time is again incremented 3t each shift.
    while(numberShifts < shiftLimit && dividend[0] == 0)
    {
        dividend.pop_front();
        numberShifts++;
        calculationTime = calculationTime + 3;
        dividend.push_back(0);
    }
}

//If the subtraction of the divisor and dividend is negative, go to this function.
void negativeResult(deque<int>& dividend, int& numberShifts, int shiftLimit, deque<int>& normalDivisor, int& carry, int& calculationTime)
{
    //Check to make sure we are not going to shift more than the desired amount of times.
    if(numberShifts == shiftLimit)
        return;

    //Another check to make sure the shifts done is less than the limit. If so, shift of the front once
    //and insert a 0 at the end.
    //Calculation time is incremented 3t each shift.
    if(numberShifts < shiftLimit)
    {
        dividend.pop_front();
        numberShifts++;
        calculationTime = calculationTime + 3;
        dividend.push_back(0);
    }

    //Check to make sure we are not going to shift more than the desired amount of times.
    if(numberShifts == shiftLimit)
        return;

    //While the shifts are less than the limit and the dividend front is 1, shift over all the 1's.
    //This is a consequence of a negative result. Insert 1';s on the end, though.
    //Calculation time is again updated 3t for each shift.
    while(numberShifts < shiftLimit && dividend[0] == 1)
    {
        dividend.pop_front();
        numberShifts++;
        calculationTime = calculationTime + 3;
        dividend.push_back(1);
    }

    //Check to make sure we are not going to shift more than the desired amount of times.
    if(numberShifts == shiftLimit)
        return;

    //This function is called again as part of a negative result. Instead, though, you subtract the normalized
    //divisor from the dividend, not the 2's complement, normalized divisor.
    //Also, there are checks with the carry to decide on what to do next: if positive result or if negative result.
    //Recursion is deeply embedded within this function.
    subtractDivisor(dividend, normalDivisor, carry);
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

// This function will subtract the divisor from the dividend.
void subtractDivisor(deque<int>& dividend, deque<int> divisor, int& carry)
{
    int halfOfDividend = (dividend.size()/2);
    for(int i = (halfOfDividend -1); i >= 0; i--)
    {
        if(dividend[i] == 1 && divisor[i] == 1 && carry == 0)
        {
            dividend[i] = 0;
            carry = 1;
        }
        else if(dividend[i] == 1 && divisor[i] == 1 && carry == 1)
        {
            dividend[i] = 1;
            carry = 1;
        }
        else if(dividend[i] == 1 && divisor[i] == 0 && carry == 0)
        {
            dividend[i] = 1;
            carry = 0;
        }
        else if(dividend[i] == 1 && divisor[i] == 0 && carry == 1)
        {
            dividend[i] = 0;
            carry = 1;
        }
        else if(dividend[i] == 0 && divisor[i] == 1 && carry == 0)
        {
            dividend[i] = 1;
            carry = 0;
        }
        else if(dividend[i] == 0 && divisor[i] == 1 && carry == 1)
        {
            dividend[i] = 0;
            carry = 1;
        }
        else if(dividend[i] == 0 && divisor[i] == 0 && carry == 0)
        {
            dividend[i] = 0;
            carry = 0;
        }
        else if(dividend[i] == 0 && divisor[i] == 0 && carry == 1)
        {
            dividend[i] = 1;
            carry = 0;
        }
    }
}
