#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 10000

char stack[MAX];
int top = -1;

char* revstr(char *str1)  
{  
    int i, len, temp;  
    len = strlen(str1);
      
    for (i = 0; i < len/2; i++)  
    {  
        temp = str1[i];  
        str1[i] = str1[len - i - 1];  
        str1[len - i - 1] = temp;  
    }  

    return str1;
}  

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

char* postfixToPrefixConvert(char postfix[])
{
    char buffer, var;
    char c[MAX];
    static char* result;
    int i, j = 0;
    int length = strlen(postfix);

    for (i = length - 1; i >= 0; i--)
    {
        if(operatorCheck(postfix[i]) == true)
        {
            push(postfix[i]);
        }
        else if (isalpha(postfix[i]) ||isdigit(postfix[i]))
        {
            c[j++] = postfix[i];
            while (top >=0 && stack[top] == '#') 
            {
                buffer = pop();
                c[j++] = pop();
            }
            push('#');
            
        }
        else
        {
            printf("Invalid expression");
        }
    }

    c[j] = '\0';

    return revstr(c);
    
}

int main()
{
    char postfix[MAX];
    char* prefix;

    scanf("%s", postfix);
    prefix = postfixToPrefixConvert(postfix);

    printf("%s", prefix);

    return 0;
}
