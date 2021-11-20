#include "SignedOperations.h"
#include <climits>

//Determins if the unsigned additon can happen without overflow
bool  SignedOperations::Addition(signed int a, signed int b) noexcept
{
    bool result = true;
    if (((b > 0) && (a > (INT_MAX - b))) ||
        ((b < 0) && (a < (INT_MIN - b))))//if overflow happens
    {
        result = false;
    }
    return result;
}
//Determins if the unsigned subtraction can happen without overflow
bool  SignedOperations::Substraction(signed int a, signed int b) noexcept
{
    bool result = true;
    if ((b > 0 && a < INT_MIN + b) ||
        (b < 0 && a > INT_MAX + b)) {
        result = false;
    }  
    return result;
}
//Determins if the unsigned Division can happen without overflow
bool  SignedOperations::Division(signed int a, signed int b) noexcept
{
    bool result = true;
    if ((b == 0) || ((a == INT_MIN) && (b == -1)))
    {
        result = false;
    }
    if ((a==0) || (( b == INT_MIN) && (a == -1)))
    {
        result = false;
    }
    return result;
}
//Determins if the unsigned mulipication can happen without overflow
bool  SignedOperations::Mulplication(signed int a, signed int b) noexcept
{
    bool result = true;
    if (a > 0) { 
        if (b > 0) {  
            if (a > (INT_MAX / b)) {
                result = false;
            }
        }
        else { 
            if (b < (INT_MIN / a)) {
                result = false;
            }
        } 
    }
    else { 
        if (b > 0) { 
            if (a < (INT_MIN / b)) {
                result = false;
            }
        }
        else { 
            if ((a != 0) && (b < (INT_MAX / a))) {
                result = false;
            }
        } 
    } 
    return result;
}
