#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 515

long long tab[MAX];

long long currentIndex = 0;
long long endProgram = 0;
long long ac = 0;
long long outputNumberCount = 0;

typedef struct
{
    char operation[10];
    char addressType;
    long long number;
} command;

long long operationToNumber(char operation[10])
{
    if (!strcmp(operation, "NULL"))
        return 0;
    else if (!strcmp(operation, "STOP"))
        return 1;
    else if (!strcmp(operation, "LOAD"))
        return 2;
    else if (!strcmp(operation, "STORE"))
        return 3;
    else if (!strcmp(operation, "JUMP"))
        return 4;
    else if (!strcmp(operation, "JNEG"))
        return 5;
    else if (!strcmp(operation, "JZERO"))
        return 6;
    else if (!strcmp(operation, "ADD"))
        return 8;
    else if (!strcmp(operation, "SUB"))
        return 9;
    else if (!strcmp(operation, "SHL"))
        return 10;
    else if (!strcmp(operation, "SHR"))
        return 11;
    else if (!strcmp(operation, "AND"))
        return 12;
    else if (!strcmp(operation, "OR"))
        return 13;
    else if (!strcmp(operation, "NOT"))
        return 14;
    return -1;
}

long long addressTypeToNumber(char addresType)
{
    if (addresType == '.')
        return 0;
    else if (addresType == '@')
        return 1;
    else if (addresType == '*')
        return 2;
    else if (addresType == '+')
        return 3;
    return 0;
}

char *numberToOperation(long long number)
{
    switch (number)
    {
    case 0:
        return "NULL";
    case 1:
        return "STOP";
    case 2:
        return "LOAD";
    case 3:
        return "STORE";
    case 4:
        return "JUMP";
    case 5:
        return "JNEG";
    case 6:
        return "JZERO";
    case 8:
        return "ADD";
    case 9:
        return "SUB";
    case 10:
        return "SHL";
    case 11:
        return "SHR";
    case 12:
        return "AND";
    case 13:
        return "OR";
    case 14:
        return "NOT";
    default:
        return "NULL";
    }
}

char numberToAddressType(long long number)
{
    switch (number)
    {
    case 0:
        return '.';
    case 1:
        return '@';
    case 2:
        return '*';
    case 3:
        return '+';
    default:
        return '.';
    }
}

long long convertCommandToNumber(command c)
{
    long long number = operationToNumber(c.operation);
    number = number << 11;
    long long addressTypeNumber = addressTypeToNumber(c.addressType);
    addressTypeNumber = addressTypeNumber << 9;
    number += addressTypeNumber;
    number += abs(c.number);
    if (c.number < 0)
    {
        number += (1 << 15);
    }
    return number;
}

command convertNumberToCommand(long long number)
{
    command c;
    c.number = number & 511;
    long long addressTypeNumber = number >> 9;
    addressTypeNumber = addressTypeNumber & 3;
    c.addressType = numberToAddressType(addressTypeNumber);
    long long operationNumber = number >> 11;
    operationNumber = operationNumber & 15;
    strcpy(c.operation, numberToOperation(operationNumber));
    long long isNegative = (number >> 15);
    if (isNegative)
    {
        c.number *= -1;
    }
    return c;
}

void input()
{
    long long n;
    scanf("%lld %lld", &n, &outputNumberCount);
    for (long long x = 0; x < n; x++)
    {
        command inputCommand;
        long long index;
        scanf("%lld:", &index);

        char tempOperationIsStringOrInt[10];
        long long intValueOfFirstThing;

        scanf("%s ", &tempOperationIsStringOrInt);
        if (operationToNumber(tempOperationIsStringOrInt) == -1)
        {
            intValueOfFirstThing = atoi(tempOperationIsStringOrInt);
            tab[index] = intValueOfFirstThing;
        }
        else
        {
            strcpy(inputCommand.operation, tempOperationIsStringOrInt);
            scanf("%c %lld", &inputCommand.addressType, &inputCommand.number);
            tab[index] = convertCommandToNumber(inputCommand);
        }


    }
}

long long getNumberFromAddressType(command c)
{
    switch (c.addressType)
    {
        case '.': return c.number;
        case '@': return tab[c.number];
        case '*': return tab[tab[c.number]];
        case '+': return tab[ac+c.number];
        default: return c.number;
    }
}

void doCommand(command c)
{
    if (!strcmp(c.operation, "NULL"))
    {
        return;
    }
    if (!strcmp(c.operation, "STOP"))
    {
        endProgram = 1;
        return;
    }

    if (!strcmp(c.operation, "LOAD"))
    {
        ac = getNumberFromAddressType(c);
        return;
    }

    if (!strcmp(c.operation, "STORE"))
    {
        tab[getNumberFromAddressType(c)] = ac;
        return;
    }

    if (!strcmp(c.operation, "JUMP"))
    {
        currentIndex = getNumberFromAddressType(c);
        return;
    }

    if (!strcmp(c.operation, "JNEG"))
    {
        if (ac < 0)
        {
            currentIndex = getNumberFromAddressType(c);
        }
        return;
    }

    if (!strcmp(c.operation, "JZERO"))
    {
        if (ac == 0)
        {
            currentIndex = getNumberFromAddressType(c);
        }
        return;
    }

    if (!strcmp(c.operation, "ADD"))
    {
        ac += getNumberFromAddressType(c);
        return;
    }

    if (!strcmp(c.operation, "SUB"))
    {
        ac -= getNumberFromAddressType(c);
        return;
    }

    if (!strcmp(c.operation, "AND"))
    {
        ac &= getNumberFromAddressType(c);
        return;
    }

    if (!strcmp(c.operation, "OR"))
    {
        ac |= getNumberFromAddressType(c);
        return;
    }

    if (!strcmp(c.operation, "NOT"))
    {
        ac = ~ac;
        return;
    }

    if (!strcmp(c.operation, "SHL"))
    {
        ac = ac << getNumberFromAddressType(c);
        return;
    }

    if (!strcmp(c.operation, "SHR"))
    {
        ac = ac >> getNumberFromAddressType(c);
        return;
    }
}

void output()
{
    for (long long x=0; x<outputNumberCount; x++)
    {
        long long indexToOutput;
        scanf("%lld", &indexToOutput);
        printf("%lld ", tab[indexToOutput]);
    }
    printf("\n");
}

void doIt()
{
    currentIndex = 0;
    endProgram = 0;
    ac = 0;
    input();

    while (!endProgram)
    {
        long long current = currentIndex;
        doCommand(convertNumberToCommand(tab[current]));
        if (currentIndex == current)
        {
            currentIndex++;
        }
    }

    output();
}

int main()
{
    long long z;
    scanf("%lld", &z);
    while (z--)
    {
        for (int x=0; x<MAX; x++)
        {
            tab[x] = 0;
        }
        doIt();
    }
}
