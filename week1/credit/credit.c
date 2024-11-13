// CS50x Week 1 pset - determines type of credit card if valid

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int digitSum(int n);

int main(void)
{
    // Prompt user for input
    long cardNum = get_long("Number: ");

    // TODO: Validation 1: checksum with Luhn's algorithm
    long temp = cardNum;
    int evenSum = 0;
    int oddSum = 0;
    int i = 0;
    do
    {
        int digit = temp % 10;
        temp /= 10;
        if (i % 2 == 0)
        {
            evenSum += digit;
        }
        else
        {
            oddSum += digitSum(digit * 2);
        }
        i++;
    }
    while (temp > 0);

    // Exit if checksum failed
    if ((evenSum + oddSum) % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Get # of digits
    int digitNo = 0;
    long num = cardNum;
    do
    {
        num /= 10;
        digitNo++;
    }
    while (num > 0);

    // Get first two digits of card number
    int firstTwo = cardNum / pow(10, digitNo - 2);
    
    // Validation 2: check for validity and card type
    if (digitNo == 15 && (firstTwo == 34 || firstTwo == 37))
    {
        printf("AMEX\n");
    }
    else if (digitNo == 16 && (firstTwo > 50 && firstTwo < 56))
    {
        printf("MASTERCARD\n");
    }
    else if ((digitNo == 13 || digitNo == 16) && (firstTwo > 39 && firstTwo < 50))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Sum together every digit in an int
int digitSum(int n)
{
    int temp = n;
    int sum = 0;
    do
    {
        int d = temp % 10;
        temp /= 10;
        sum += d;
    }
    while (temp > 0);

    return sum;
}