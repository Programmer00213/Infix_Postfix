#include<iostream>
#include"../My_Library/Dynamic_Stack.hpp" //.gch file are precompiled headers generated by GCC. They are header files that have been processed into 
                              //a form that the compiler can process more quickly
#include"../My_Library/Utility.h"

#define MAX_CHAR 80

int main(void){
    char expression[MAX_CHAR] = {"(-A + B) * (C - D) / (E + F ^ (G * H - I)) + J * K - L / (M + N * O) ^ P"};

    STACK <char>operation;
    STACK <char>operand;

    for(int i = 0; expression[i] != '\0'; i++){
        if(expression[i] == ' ') continue; // ignore white space.
        if(is_alphabet(expression[i])){ // if operand push
            operand.push(expression[i]);
        }
        else{// if operation
            if(expression[i] == ')'){ // if operation is closing bracket pop untill you pop opening bracket
                while(operation.current() != '('){
                    operand.push(operation.pop());
                }
                operation.pop();
            }
            // order of condition matters.
            // if operation has higher priority, push to stack
            else if(operation.is_empty() || operation_priority(expression[i]) > operation_priority(operation.current()) || operation.current() == '('){
                operation.push(expression[i]);
            }
            // if operation is lower priority pop, untill operation with lower priority is reached or you incounter opening bracket
            else if(operation_priority(expression[i]) <= operation_priority(operation.current())){
                while(!operation.is_empty() && operation_priority(expression[i]) <= operation_priority(operation.current()) && operation.current() != '(' ){
                    operand.push(operation.pop());
                }
                operation.push(expression[i]);
            }
            
        }
    }
    while(!operation.is_empty()){// push remaining operation in operation stack in operand stack
        operand.push(operation.pop());
    }
    
    operand.display();
}