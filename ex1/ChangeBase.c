#include <stdio.h>

const int INVALID_REPRESENTATION = -1;
/**
 * power function returns a^b
 * @param a - first integer
 * @param b - power integer
 * @return  - a^b
 */
int pow(int a, int b){
    int result = 1;

    do{
        //bitwise and b&1 == true means that b's least significant bit is 1(b is odd number)
        if(b&1){
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
int toDecimal(int base, int number){

    printf("%d\n", number);
    int sum = 0;
    int counter = 0;
    int digit;
    do{
        digit = number % 10;
        if(digit >= base){
            return INVALID_REPRESENTATION;
        }
        sum += digit*pow(base,counter);
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
int decimalToBase(int base, int number){

    int numberInBase = 0;
    int remainder;
    int counter = 0;
    do{
        remainder = number % base;
        number /= base;
        numberInBase += remainder * pow(10,counter);
        counter++;
    }while(number!=0);
    return numberInBase;
}

int main() {
    int fromBase,toBase,number;
    scanf("%d %d %d", &fromBase, &toBase, &number );
    int result = decimalToBase(toBase,toDecimal(fromBase,number));
    if(result == INVALID_REPRESENTATION){
        printf("");
    }
    else{
        printf("%d", result);
    }
    return 0;
}