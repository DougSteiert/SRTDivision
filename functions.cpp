// This normalizes the divisor before taking the 2's complement.
void normalize(deque<int>& notNormalized, int& numberMoves)
{
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
    for(int i = 0; i < divisor.size(); i++)
    {
        if(divisor[i] == 0)
            divisor[i] = 1;
        else
            divisor[i] = 0;
    }
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
    negative = 1;
    calculationTime = calculationTime + divisor.size();
}

void initialShift(deque<int>& dividend, int& numberShifts, int& calculationTime)
{
    while(dividend[0] == 0)
    {
        dividend.pop_front();
        numberShifts++;
        calculationTime = calculationTime + 3;
        dividend.push_back(0);
    }
}

void positiveResult(deque<int>& dividend, int& numberShifts, int shiftLimit, int& calculationTime)
{
    //Check to make sure we are not going to shift more than the desired amount of times.
    if(numberShifts == shiftLimit)
        return;

    if(numberShifts < shiftLimit)
    {
        dividend.pop_front();
        numberShifts++;
        calculationTime = calculationTime + 3;
        dividend.push_back(1);
    }

    while(numberShifts < shiftLimit && dividend[0] == 0)
    {
        dividend.pop_front();
        numberShifts++;
        calculationTime = calculationTime + 3;
        dividend.push_back(0);
    }
}

void negativeResult(deque<int>& dividend, int& numberShifts, int shiftLimit, deque<int>& normalDivisor, int& carry, int& calculationTime)
{
    //Check to make sure we are not going to shift more than the desired amount of times.
    if(numberShifts == shiftLimit)
        return;

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
