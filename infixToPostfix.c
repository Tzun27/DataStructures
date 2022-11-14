#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 10000

char stack[MAX];
int top = -1;

void push(char c)
{
    if (top >= (MAX - 1))
    {
        printf("Stack Overflow");
    }
    else
    {
        top += 1;
        stack[top] = c;
    }
}

char pop()
{
    char c;

    if (top < 0)
    {
        printf("Stack underflow");
        getchar();
        exit(1);
    }
    else
    {
        c = stack[top];
        top -= 1;
        return c;
    }
}

bool operatorCheck(char symbol)
{
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^')
        return true;

    else
        return false;
}

int precedence(char symbol)
{
    if (symbol == '^')
    {
        return 3;
    }
    else if (symbol == '*' || symbol == '/')
    {
        return 2;
    }
    else if (symbol == '*' || symbol == '/')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void infixToPostfixConvert(char infix[], char postfix[])
{
    int i, j;
    char var, c;

    i = 0;
    j = 0;
    var = infix[i];

    push('(');
    strcat(infix, ")");

    while (var != '\0')
    {
        if (var == '(')
        {
            push(var);
        }
        else if (isdigit(var) || isalpha(var))
        {
            postfix[j] = var;
            j++;
        }
        else if (operatorCheck(var) == true)
        {
            c = pop();
            while (operatorCheck(c) && precedence(var) <= precedence(c))
            {
                postfix[j] = c;
                j++;
                c = pop();
            }
            push(c);
            push(var);
        }
        else if (var == ')')
        {
            c = pop();
            while (c != '(')
            {
                postfix[j] = c;
                j++;
                c = pop();
            }
        }
        else
        {
            printf("Invalid expression");
            exit(1);
        }

        i++;
        var = infix[i];
    }

    if (top > 0)
        printf("Invalid expression");

}

int main()
{
    // transform infix to postfix
    char infix[MAX], postfix[MAX];
    
    scanf("%s", infix);

    infixToPostfixConvert(infix, postfix);
    printf("%s", postfix);
    return 0;
}
