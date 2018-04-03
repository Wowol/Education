#include <stdio.h>
#include <string.h>

#define MAXWORDLENGTH 3005

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

    for (int x = startIndex; x % BLOCKSIZE != 0 || x == startIndex; x++)
    {
        result += number[x] - '0';
        result *= 2;
    }
    result /= 2;

    return result;
}

void decimalToBinary(int n, char *result, int charNumber)
{
    int beginIterator = charNumber * BITSPERCHAR;

    int x = beginIterator;
    for (; n > 0; x++)
    {
        result[x] = n % 2 + '0';
        n /= 2;
    }

    while (x % BITSPERCHAR != 0 || x == beginIterator)
    {
        result[x++] = '0';
    }

    for (int y = beginIterator; y < (x-beginIterator) / 2 + beginIterator; y++)
    {
        swap(x - y - 1 + beginIterator, y, result);
    }
}

int bitCounter(char *result, int length)
{
    int count = 0;
    for (int x=0; x<=length; x++)
    {
        if (result[x] == '1')
        {
            count++;
        }
    }

    return count;
}

void doCode(char word[])
{
    char result[BITSPERCHAR * MAXWORDLENGTH];
    for (int x = 0; x < strlen(word); x++)
    {
        int charValue = word[x] - 65;
        int codeValue = word[x] == '.' ? code[26] : code[charValue];
        decimalToBinary(codeValue, result, x);
    }

    int length = strlen(word) * BITSPERCHAR - 1;
    for (int x = strlen(word) * BITSPERCHAR; x % BLOCKSIZE != 0; x++)
    {
        result[x] = '0';
        length = x;
    }

    printf("%d %d ", strlen(word), bitCounter(result, length));

    for (int x = 0; x < strlen(word) * BITSPERCHAR; x += BLOCKSIZE)
    {
        int hash = binaryToDecimal(result, x);
        printf("%i ", hash);
    }
    printf("\n");
}

void doIt()
{
    for (int x = 0; x < 27; x++)
    {
        int c;
        scanf("%i", &c);
        code[x] = c;
    }

    int n;
    scanf("%i", &n);
    for (int x = 0; x < n; x++)
    {
        char nicNieZnaczacyNapisBoToJestJ1ITak[42];
        char word[MAXWORDLENGTH];
        scanf("%s %s", nicNieZnaczacyNapisBoToJestJ1ITak, word);
        doCode(word);
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