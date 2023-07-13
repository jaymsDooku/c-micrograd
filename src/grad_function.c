//
// Created by James Leaver on 13/07/2023.
//

#include "grad_function.h"

#include <stdlib.h>

void grad_function_compute(grad_function* grad_function) {
    float result_grad = grad_function->result->grad;
    float operand1_value = grad_function->operand1->value;
    float operand2_value = grad_function->operand2->value;
    switch (grad_function->operation) {
        case ADD:
            grad_function->operand1->grad += result_grad;
            grad_function->operand2->grad += result_grad;

            variable_backward(grad_function->operand1);
            variable_backward(grad_function->operand2);
            break;
        case MUL:
            grad_function->operand1->grad += operand2_value * result_grad;
            grad_function->operand2->grad += operand1_value * result_grad;

            variable_backward(grad_function->operand1);
            variable_backward(grad_function->operand2);
            break;
        case NOP:
            break;
    }
}

grad_function* grad_function_initialize(variable* operand1, variable* operand2, variable* result, OP_ENUM operation) {
    grad_function* grad_function_result = malloc(sizeof(grad_function));
    grad_function_result->operand1 = operand1;
    grad_function_result->operand2 = operand2;
    grad_function_result->result = result;
    grad_function_result->operation = operation;
    return grad_function_result;
}

void grad_function_free(grad_function* grad_function) {
    free(grad_function);
}