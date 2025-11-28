// program that determines the validity of a credit card and if it is AMEX, Visa, or Mastercard

#include <stdio.h>
#include <math.h>
 
// prototypes
long long cardDetails(void);
int checkLength(long long card);
int checkSum(long long card, int length);
char initialDigits(long long card, int length);

// main implementation
int main(void)
{
    long long card = cardDetails();
    int length = checkLength(card);
    int sum = checkSum(card, length);
    char digits = initialDigits(card, length);
    
    if (sum % 10 == 0)
    {
        if (length == 15 && digits == 'A')
        {
            printf("AMEX!\n");
        }
        else if ((length == 13 || length == 16) && digits == 'V')
        {
            printf("VISA!\n");
        }
        else if (length == 16 && digits == 'V')
        {
            printf("MASTERCARD!\n");
        }
        else
        {
            printf("INVALID!!!\n");
        }
    }
    return 0;
}

// validate if the user actually put in a credit card number
long long cardDetails(void)
{
    long long card;
    do
    {
        printf("Enter a valid credit card number:\n");
        scanf("%lld", &card);
    } 
    while (card < 0);

    return card;
}

// validate the length of the credit card number
int checkLength(long long card)
{
    int length = 0;
    while(card > 0)
    {
        card = card / 10;
        length++;
    }
    return length;
}

// implementing luhn's algorithm
int checkSum(long long card, int length)
{
    int card_array[20];
    int value1 = 0; 
    int value2 = 0;
    int sum1 = 0;
    int sum2 = 0;
    
    for(int i = 0; i < length; i++)
    {
        //store the card number digits in reverse
        card_array[i] = card % 10;
        card = card / 10;
    }

    // for every number starting from second from last and multiplying it with 2
    for(int i = 1; i < length; i += 2)
    {
        value1 = card_array[i]*2;
        if (value1 / 10 > 0)
        {
            sum1 = sum1 + (value1 % 10);
            value1 = value1 / 10;
            sum1 = sum1 + value1;
        }
            else
        {
            sum1 = sum1 + value1;
        }
    }

    // for every number other than the ones above
    for(int j = 0; j < length; j += 2)
    {
        value2 = card_array[j];
        sum2 = sum2 + value2;
    }
    int sum = sum1 + sum2;
    return sum;
}

char initialDigits(long long card, int length)
{
    int firstDigit = card / pow(10, length-1);
    int firstTwoDigits = card / pow(10, length-2);

    if (firstDigit == 4)
    {
        return 'V';
    }
    else if (firstTwoDigits == 34 || firstTwoDigits == 37)
    {
        return 'A';
    }
    else if (firstTwoDigits == 51 || firstTwoDigits == 52 || firstTwoDigits == 53 || firstTwoDigits == 54 || firstTwoDigits == 55)
    {
        return 'M';
    }
    else
    {
        return 'I';
    }
}