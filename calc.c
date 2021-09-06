#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define SIZE 100

char stack[SIZE];
int top = -1;

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
	if(symbol == '^')
	{
		return(3);
	}
	else if(symbol == '*' || symbol == '/')
	{
		return(2);
	}
	else if(symbol == '+' || symbol == '-')
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

	push('(');                             
	strcat(infix_exp,")");                 

	i=0;
	j=0;
	item=infix_exp[i];

	while(item != '\0')
	{
		if(item == '(')
		{
			push(item);
		}
		else if( isdigit(item) || isalpha(item))
		{
			postfix_exp[j] = item;
			j++;
		}
		else if(is_operator(item) == 1)
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
