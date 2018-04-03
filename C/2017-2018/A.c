#include <stdio.h>
#include <stdlib.h>

void program()
{
    int n;
    scanf("%i", &n);
    int pierwsza = 1;
    for (int x=2; x<=sqrt(n); x++)
    {
        if (n%x == 0)
        {
            pierwsza = 0;
            break;
        }
    }
    if (pierwsza)
    {
        printf("%i jest pierwsza\n", n);
    }
    else
    {
        printf("%i jest zlozona\n", n);
    }
    return 0;

}

int main()
{
    int n = 0;
    scanf("%i", &n);
    while (n--)
    {
        program();
    }
}
