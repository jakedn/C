/*File:ChangeBase
 *Author:jakedn
 *
 * the algorithm that is used here is we convert the number
 * we get as input from the input base to decimal and then from
 * decimal to the desired base representation. the conversion to decimal
 * is done by taking each digit and multyplying it by 10^d where d is
 * the digits place in the orginal number(starting from 0), this is done in toDecimal
 * then we divide the decimal number by the desired base and make the remainder the next digit
 * in our new representation, this is done in decimalToBase.
 * pow takes O(log(b)) time
 * toDecimal takes O(log10(number)*log(log10(number))) which is bounded by O(log(number)^2)
 * thats because it does O(log10(number) iterations and each iteration takes
 * O(log(counter)) and counter <= log10(number) at all times
 * decimalToBase takes  O(logb(number)*log(logb(number))) where b is the base input,
 * the explanation for this is like in toDecimal and this is bounded by O(log(number)^2)
 * in total we see that our algorithm works in polynomial time according to the amount of digits
 * (log(number) is bounded by C*log10(number) and is like the amount of digits)
 */


#include <stdio.h>

#define INVALID_ERROR_MESSAGE "invalid!!"
#define INVALID_REPRESENTATION -1

/**
 * power function returns a^b
 * @param a - first integer
 * @param b - power integer
 * @return  - a^b
 */
int power(int a, int b)
{
    int result = 1;

    do
    {
        //bitwise and b&1 == true means that b's least significant bit is 1(b is odd number)
        if(b & 1)
        {
            result *= a;
            b--;
        }
        a *= a;     //now b is even so we can times a by itself and divide b by 2
        b /= 2;     //because a^b=(a*a)^(b/2) and we dont lose information about b because b is even

    }while(b != 0);
    return result;
}

/**
 * changes a number in a given representation to decimal representation.
 * @param base - basis of the number given to this function.
 * @param number -the given number represented in basis basis.
 * @return - the given number in base 10 representation.
 */
int toDecimal(int base, int number)
{

    int sum = 0;
    int counter = 0;
    int digit;
    do
    {
        digit = number % 10;
        if(digit >= base)
        {
            return INVALID_REPRESENTATION;
        }
        sum += digit * power(base, counter);
        counter++;
        number /= 10;
    }while(number != 0);
    return sum;
}

/**
 * changes a number in decimal representation to a given representation.
 * @param base - the base that we want to be represented
 * @param number- our given number
 * @return- the number in base representation.
 */
int decimalToBase(int base, int number)
{
    int numberInBase = 0;
    int remainder;
    int counter = 0;
    do
    {
        remainder = number % base;
        number /= base;
        numberInBase += remainder * power(10, counter);
        counter++;
    }while(number != 0);
    return numberInBase;
}

int main()
{
    int fromBase, toBase, number;
    //here we can use scanf due to the "promise" of "good" input in the testers
    scanf("%d %d %d", &fromBase, &toBase, &number);
    int result = decimalToBase(toBase, toDecimal(fromBase, number));
    if(result == INVALID_REPRESENTATION)
    {
        fprintf(stderr, "%s\n", INVALID_ERROR_MESSAGE);
        return INVALID_REPRESENTATION;
    }
    else
    {
        printf("%d\n", result);
    }
    return 0;
}