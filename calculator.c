#include<stdio.h>
int main(){
    int num1,num2, result;
    char operation;
    printf("BASIC CALCULATOR\n");
    printf("Enter first number: ");
    scanf("%f", &num1);
    printf("Enter second number ");
    scanf("%f", &num2);
    printf("\nselect Operation: ");
    printf("+ : Addition\n");
    printf("- : Subtraction\n");
    printf("* : Multiplication");
    printf("/ : Division");
    printf("Enter operation");
    scanf("%c", &operation);
    switch(operation){
        case '+' : 
        result = num1 + num2;
        printf("Result = %.2f\n", result);
        break;
        case '-' : 
        result = num1- num2;
        printf("Result = %2f\n", result);
        break;
        case '*' :
        result = num1*num2;
        printf("Result = %.2f\n", result);
        break;
        case '/' :
        if(num2 == 0){
            printf("Error: Division by zero is not allowed.\n");
        } else{
            result = num1/num2;
            printf("Result = %.2f\n", result);
        }
        default :
        printf("invalid operation\n");
    }
    return 0;
}