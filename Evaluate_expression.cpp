#include <iostream>
#include "../My_Library/Dynamic_Stack.hpp"
#include <cmath>
#include "../My_Library/Utility.h"

float Arithmatic_Operation(float operand1, char operation, float operand2);
void Calculate(STACK<float>* operand, STACK<char>* operation);

int main(void)
{
    STACK<float> operand;
    STACK<char> operation;

    char expression[] = {"-321.99*12.1/(-5.9+8.3)^3-7.999"};

    float number_buffer = 0;
    int fraction_index = 0;
    int is_negative = 1;

    for(int i = 0; expression[i] != '\0'; i++){
        if(expression[i] == '.'){
            fraction_index = i;
            continue;
        }
        if((i == 0 && expression[i] == '-') or (expression[i] == '-' && expression[i-1] == '(')){
            is_negative = -1;
            continue;
        }
        if(is_number(expression[i])){
            // number creation part
            if(fraction_index == 0) number_buffer = number_buffer * 10 + (int)expression[i] - '0';
            else number_buffer = number_buffer + ((int)expression[i] - '0')/pow(10, i - fraction_index);

            continue;
        }
        // push the number in number_buffer to operand stack
        if(!(expression[i] == '.' || expression[i] == '(' || expression[i - 1] == ')')){
            operand.push(number_buffer * is_negative);
            number_buffer = 0; fraction_index = 0; is_negative = 1;
        }

        if(expression[i] == ')'){
            while(operation.current() != '(') Calculate(&operand, &operation);
            operation.pop();
        }
        else if(operation.is_empty() || operation_priority(expression[i]) > operation_priority(operation.current()) || operation.current() == '('){
            operation.push(expression[i]);
        }
        else if(operation_priority(expression[i]) <= operation_priority(operation.current())){
            while(!operation.is_empty() && operation_priority(expression[i]) <= operation_priority(operation.current()) && operation.current() != '(')
                Calculate(&operand, &operation);

            operation.push(expression[i]);
        }
    }
    operand.push(number_buffer);

    while(!operation.is_empty()){// push remaining operation in operation stack in operand stack
        Calculate(&operand, &operation);
    }
    operand.display();
    operation.display();
    return 0;
}

void Calculate(STACK<float>* operand, STACK<char>* operation){
    float operand1 = operand->pop();
    char operation_type = operation->pop();
    float operand2 = 0;

    operand2 = operand->pop();
    operand->push(Arithmatic_Operation(operand1, operation_type, operand2));
}

float Arithmatic_Operation(float operand2, char operation, float operand1 = 0)
{
    switch(operation){
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        case '^':
            return std::pow(operand1, operand2);
        default:
            std::cout << "Operation: " << operation << "\n";
            throw std::runtime_error("Invalid Operation");
    }
}