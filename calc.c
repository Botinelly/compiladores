#include <stdio.h>
#include <ctype.h>
#include <string.h>

// main stack
char stack[256];
int top = -1;

// push a element to stack
void push(char i){
    stack[++top] = i;
}

// treats the operators and marker to the end of postfix
int symbol(char element)
{
    switch(element){
        case '#':
            return 0;
        case '(':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
    }
}

// calculates the expression in postfixed mode
int calculator(char *postfix)
{
    char ch;
    int i = 0;
    float a, b;
    
    while((ch = postfix[i++]) != 0)
    {
        if(isdigit(ch))
        {
            push(ch-'0');
        }
        else{
            a = stack[top--];
            b = stack[top--];
            switch(ch){
                case '+':
                    push(a + b);
                    break;
                case '-':
                    push(a - b);
                    break;
                case '*':
                    push(a * b);
                    break;
                case '/':
                    push(a / b);
                    break;
            }
        }
    }
    return stack[top];
}

// converts infixed expressions to postfixed
void to_RPN(char *infix, char *postfix)
{
    char ch, element;
    int i = 0, k = 0;
    
    // marker
    push('#');

    while((ch = infix[i++]) != '\0')
    {
        if(ch == '(')
        {
            push(ch);
        }
        else if (isalnum(ch))
        {
            postfix[k++] = ch;
        }
        else if (ch == ')')
        {
            while(stack[top] != '(')
            {
                postfix[k++] = stack[top--];
            }
            element = stack[top--];
        } else 
        {
            while(symbol(stack[top]) >= symbol(ch))
            {
                postfix[k++] = stack[top--];
            }
            push(ch);
        }
    }
    // while not at end of expression
    while (stack[top] != '#')
    {
        postfix[k++] = stack[top--];
    }
    postfix[k] = 0;
}


int main(int argc, char** argv)
{
    char input[80], postf[80];

    if(argc == 1)
    {
        while(fgets(input, sizeof(input), stdin) != NULL)
        {
            // removes the \n from the entry
            input[strlen(input) - 1] = 0;
            to_RPN(input, postf);
            printf("%s=%d\n", input, calculator(postf));
        }
    }
    else
    {
        strcpy(input, argv[1]);
        to_RPN(input, postf);
        printf("%s=%d\n", input, calculator(postf));
    }
}
