#include <stdio.h>
//#include <math.h>


int pow(int a, int b){
    int result = 1;

    do{
        if(b&1){
            result *= a;
            b--;
        }
        if(b!=0){
            a *= a;
            b /= 2;
        }
    }while(b != 0);
    return result;
}

///**
// *
// * @param digit - the wanted digit counting from 0 (the least sinificant digit)
// * @param number- the number we are takign a digit from.
// * @return - the required digit
// */
//int getDigit(int digit, int number){
//
//    number /= pow(10,digit);
//    number %= 10;
//    return number;
//}

/**
 *
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
            return -1;  //returning error code -1
        }
        sum += digit*pow(base,counter);
        counter++;
        number /= 10;
    }while(number != 0);
    return sum;
}

/**
 *
 * @param base
 * @param number
 * @return
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
    printf("%d", decimalToBase(toBase,toDecimal(fromBase,number)));
    return 0;
}