//
// Created by James Leaver on 13/07/2023.
//

#ifndef C_MICROGRAD_GRAD_FUNCTION_H
#define C_MICROGRAD_GRAD_FUNCTION_H

#include "variable.h"

typedef struct grad_function {
    variable* operand1;
    variable* operand2;
    variable* result;
    OP_ENUM operation;
} grad_function;

void grad_add(grad_function* grad_function);
void grad_mul(grad_function* grad_function);
void grad_exp(grad_function* grad_function);
void grad_relu(grad_function* grad_function);

void grad_function_compute(grad_function* grad_function);
grad_function* grad_function_initialize(variable* operand1, variable* operand2, variable* result, OP_ENUM operation);
void grad_function_free(grad_function* grad_function);

#endif //C_MICROGRAD_GRAD_FUNCTION_H
