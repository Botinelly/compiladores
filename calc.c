/* This program converts infix expression to postfix expression.
 * This program assume that there are Five operators: (*, /, +, -,^) 
	in infix expression and operands can be of single-digit only.
 * This program will not work for fractional numbers.
 * Further this program does not check whether infix expression is 
 valid or not in terms of number of operators and operands.*/

#include<stdio.h>
#include<stdlib.h>      /* for exit() */
#include<ctype.h>     /* for isdigit(char ) */
#include<string.h>

#define SIZE 100

char stack[SIZE];
int top = -1;

/* define push operation */

void push(char item)
{
    top = top+1;
    stack[top] = item;
}

char pop()
{
	char item ;
	item = stack[top];
	top = top-1;
	return(item);
}

int is_operator(char symbol)
{
	if(symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-')
	{
		return 1;
	}
	else
	{
	    return 0;
	}
}

int precedence(char symbol)
{
	if(symbol == '^')/* exponent operator, highest precedence*/
	{
		return(3);
	}
	else if(symbol == '*' || symbol == '/')
	{
		return(2);
	}
	else if(symbol == '+' || symbol == '-')          /* lowest precedence */
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

void InfixToPostfix(char infix_exp[], char postfix_exp[])
{ 
	int i, j;
	char item;
	char x;

	push('(');                               /* push '(' onto stack */
	strcat(infix_exp,")");                  /* add ')' to infix expression */

	i=0;
	j=0;
	item=infix_exp[i];         /* initialize before loop*/

	while(item != '\0')        /* run loop till end of infix expression */
	{
		if(item == '(')
		{
			push(item);
		}
		else if( isdigit(item) || isalpha(item))
		{
			postfix_exp[j] = item;              /* add operand symbol to postfix expr */
			j++;
		}
		else if(is_operator(item) == 1)        /* means symbol is operator */
		{
			x=pop();
			while(is_operator(x) == 1 && precedence(x)>= precedence(item))
			{
				postfix_exp[j] = x;
				j++;
				x = pop();
			}
			push(x);

			push(item);
		}
		else if(item == ')')
		{
			x = pop();
			while(x != '(')
			{
				postfix_exp[j] = x;
				j++;
				x = pop();
			}
		}
		else
		{ 
			printf("\nInvalid infix Expression.\n");
			getchar();
			exit(1);
		}
		i++;


		item = infix_exp[i];
	}
	postfix_exp[j] = '\0';
	
}

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


int main(int argc, char *argv[])
{
    char input[80], postf[80];
    if(argc == 1)
    {
        while(fgets(input, sizeof(input), stdin) != NULL)
        {
            // removes the \n from the entry
            input[strlen(input) - 1] = 0;
            InfixToPostfix(input, postf);
            printf("%s=%d\n", input, calculator(postf));
        }
    }
    else
    {
        strcpy(input, argv[1]);
        InfixToPostfix(input, postf);
        printf("%s=%d\n", input, calculator(postf));
    }
	return 0;
}
