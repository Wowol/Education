#include <stdio.h>
#include <string.h>

#define MAXWORDLENGTH 20000

#define BITSPERCHAR 5

#define BLOCKSIZE 16

int code[27];

void swap(int a, int b, char *tab)
{
    char c;
    c = tab[a];
    tab[a] = tab[b];
    tab[b] = c;
}

int binaryToDecimal(char *number, int startIndex)
{
    int result = 0;

    for (int x = startIndex; x % BITSPERCHAR != 0 || x == startIndex; x++)
    {
        result += number[x] - '0';
        result *= 2;
    }
    result /= 2;

    return result;
}

void decimalToBinary(int n, char *result, int sequenceNumber)
{
    char temp[BLOCKSIZE];

    int x = 0;
    for (; n > 0; x++)
    {
        temp[x] = n % 2 + '0';
        n /= 2;
    }

    while (x % BLOCKSIZE != 0 || x == 0)
    {
        temp[x++] = '0';
    }

    for (int y = 0; y < x / 2; y++)
    {
        swap(x - y - 1, y, temp);
    }

    for (int x = 0; x < BLOCKSIZE; x++)
    {
        result[sequenceNumber * BLOCKSIZE + x] = temp[x];
    }
}

void getWordFromNumbes(int numbers[], int wordLength, char word[])
{
    for (int x = 0; x < wordLength; x++)
    {
        for (int y = 0; y < 27; y++)
        {
            if (numbers[x] == code[y])
            {
                word[x] = y + 65;
                if (word[x] == '[')
                {
                    word[x] = '.';
                }

                break;
            }
        }
    }
}

void doDecode(int numbers[], int wordLength)
{
    char result[MAXWORDLENGTH];
    for (int x = 0; BLOCKSIZE * x < wordLength * BITSPERCHAR; x++)
    {
        decimalToBinary(numbers[x], result, x);
    }

    int resultNumbers[MAXWORDLENGTH];
    for (int x = 0; x < wordLength; x++)
    {
        resultNumbers[x] = binaryToDecimal(result, x * BITSPERCHAR);
    }

    char word[MAXWORDLENGTH];
    getWordFromNumbes(resultNumbers, wordLength, word);
    word[wordLength] = '\0';

    printf("%s\n", word);
}

void inputCode()
{
    for (int x = 0; x < 27; x++)
    {
        int c;
        scanf("%i", &c);
        code[x] = c;
    }
}

void doForOne()
{
    int numbers[MAXWORDLENGTH];    
    char nicNieZnaczacyNapisBoToJestJ2ITak[42];
    int bitCounter;
    int wordLength;

    scanf("%s %d %d", &nicNieZnaczacyNapisBoToJestJ2ITak, &wordLength, &bitCounter);
   //scanf("%d %d", &wordLength, &bitCounter);
    int currentBitCounter = 0;
    int x = 0;

    for (; BLOCKSIZE * x < wordLength * BITSPERCHAR; x++)
    {
        scanf("%d", &numbers[x]);
        currentBitCounter += __builtin_popcount(numbers[x]);
    }

    if (currentBitCounter != bitCounter)
    {
        printf("BLAD KONTROLI\n");
        return;
    }

    doDecode(numbers, wordLength);
}

void doIt()
{
    inputCode();
    int n;
    scanf("%i", &n);
    for (int x = 0; x < n; x++)
    {
        doForOne();
    }
}

int main()
{
    int z;
    scanf("%i", &z);
    while (z--)
    {
        doIt();
    }
}