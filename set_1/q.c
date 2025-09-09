// infix to postfix
// precedence order: (), /, *, +, -
// number should be only single digit
// operators are /, *, +, -

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack_char.c"
#include "stack_int.c"
#define LEN 101

char *infix_to_postfix_expr(char *, int);
int precedence(char);
int evaluate_postfix(char *);

int main(int argc, char *argv[]){
    char *ans;
    int sum_value;

    if(argc == 1){
        char arr[LEN];

        printf("Enter the equation: ");
        gets(arr);

        ans = infix_to_postfix_expr(arr, strlen(arr));
        sum_value = evaluate_postfix(ans);

        printf("postfix expression = %s\n", ans);
        printf("%s = %d\n", arr, sum_value);
    }
    else{
        ans = infix_to_postfix_expr(argv[1], strlen(argv[1]));
        sum_value = evaluate_postfix(ans);

        printf("postfix expression = %s\n", ans);
        printf("%s = %d\n", argv[1], sum_value);
    }

    return 0;
}

char *infix_to_postfix_expr(char *arr, int len){
    char *postfix = (char *)malloc(sizeof(char) * 101);
    int postfix_len = 0;

    for(int i=0; i<len; i++){
        if(arr[i] == ' ') continue;
        else if(isalnum(arr[i])) postfix[postfix_len++] = arr[i]; 
        else if(arr[i] == '(') push(arr[i]);
        else if(arr[i] == ')'){
            while(is_empty() == false && top() != '('){
                postfix[postfix_len++] = top();
                pop();
            }
            pop();
        }
        else{
            while(is_empty() == false && precedence(arr[i]) <= precedence(top())){
                postfix[postfix_len++] = top();
                pop();
            }
            push(arr[i]);
        }
    }

    while(is_empty() == false){
        postfix[postfix_len++] = top();
        pop();
    }

    postfix[postfix_len++] = '\0';

    return postfix;
}

int precedence(char op){
    if(op == '/' || op == '*') return 2;
    else if(op == '+' || op == '-') return 1;
    else return -1;
}

int evaluate_postfix(char *exp){
    int op1, op2;

    for(int i=0; exp[i] != '\0'; i++){
        char ch = exp[i];

        if(isdigit(ch)){
            // Convert char digit to int and push
            push_i(ch - '0');
        }
        else{
            // Operator → pop two operands
            op2 = top_i();
            pop_i();
            op1 = top_i();
            pop_i();

            switch(ch){
                case '+': push_i(op1 + op2); break;
                case '-': push_i(op1 - op2); break;
                case '*': push_i(op1 * op2); break;
                case '/': push_i(op1 / op2); break;
                default:
                    printf("Invalid operator: %c\n", ch);
                    exit(1);
            }
        }
    }

    int sum = top_i();
    pop_i();

    return sum;
}