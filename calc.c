#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
        float num1=0, num2=0;
        char oper;
        num1 = atof(argv[1]);
        num2 = atof(argv[3]);
        oper = *argv[2];

        printf("%.2f %c %.2f = ", num1,oper,num2);

        switch( oper )
        {
            case '+':
                    printf("%.2f\n\n", num1 + num2);
                    break;

            case '-':
                    printf("%.2f\n\n", num1 - num2);
                    break;

            case '*':
                    printf("%.2f\n\n", num1 * num2);
                    break;

            case '/':
                    if(num2 != 0)
                        printf("%.2f\n\n", num1 / num2);
                    else
                        printf("There is no division by 0\n\n");
                    break;

            case '%':
                    printf("%d\n\n", (int)num1 % (int)num2);
                    break;
    }
}
