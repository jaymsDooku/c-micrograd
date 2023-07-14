//
// Created by James Leaver on 13/07/2023.
//

#include "grad_function.h"

#include <stdlib.h>
#include <math.h>

void grad_add(grad_function* grad_function) {
    grad_function->operand1->grad += grad_function->result->grad;
    grad_function->operand2->grad += grad_function->result->grad;

    variable_backward(grad_function->operand1);
    variable_backward(grad_function->operand2);
}

void grad_mul(grad_function* grad_function) {
    float result_grad = grad_function->result->grad;
    float value1 = grad_function->operand1->value;
    float value2 = grad_function->operand2->value;

    grad_function->operand1->grad += value2 * result_grad;
    grad_function->operand2->grad += value1 * result_grad;

    variable_backward(grad_function->operand1);
    variable_backward(grad_function->operand2);
}
void grad_exp(grad_function* grad_function) {
    float result_grad = grad_function->result->grad;
    float value1 = grad_function->operand1->value;
    float value2 = grad_function->operand2->value;
    grad_function->operand1->grad += value2 * (powf(value1, value2-1)) * result_grad;
    grad_function->operand2->grad += powf(value2, value1) * logf(value1) * result_grad;

    variable_backward(grad_function->operand1);
    variable_backward(grad_function->operand2);
}

void grad_function_compute(grad_function* grad_function) {
    switch (grad_function->operation) {
        case ADD:
            grad_add(grad_function);
            break;
        case MUL:
            grad_mul(grad_function);
            break;
        case EXP:
            grad_exp(grad_function);
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