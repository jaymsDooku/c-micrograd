//
// Created by James Leaver on 12/07/2023.
//

#include "variable.h"

#include "grad_function.h"
#include "data_structures/list.h"
#include "data_structures/set.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void variable_build_topo(variable* variable, list* topo, set* visited) {
    if (variable == NULL) {
        return;
    }

    if (!set_contains(visited, variable)) {
        set_add(visited, variable);
        variable_build_topo(variable->children[0], topo, visited);
        variable_build_topo(variable->children[1], topo, visited);
        list_add(topo, variable);
    }
}

void variable_first_backward(variable* variable) {
    list* topo = list_initialize(sizeof(void*));
    set* visited = set_initialize();
    variable_build_topo(variable, topo, visited);

    variable->grad = 1;
    for (int i = topo->count - 1; i >= 0; i--) {
        variable_backward(list_get(topo, i));
    }

    list_free(topo);
    set_free(visited);
}

void variable_backward(variable* variable) {
    grad_function* grad_function = variable->grad_function;
    if (grad_function != NULL) {
        grad_function_compute(grad_function);
    }
}

variable* variable_mul(char* name, variable* a, variable* b) {
    variable* result = variable_initialize(name, a->value * b->value, a, b, MUL);
    grad_function* grad_function = grad_function_initialize(a, b, result, MUL);
    result->grad_function = grad_function;
    return result;
}

variable* variable_add(char* name, variable* a, variable* b) {
    variable* result = variable_initialize(name, a->value + b->value, a, b, ADD);
    grad_function* grad_function = grad_function_initialize(a, b, result, ADD);
    result->grad_function = grad_function;
    return result;
}

variable* variable_exp(char* name, variable* a, variable* b) {
    variable* result = variable_initialize(name, powf(a->value, b->value), a, b, EXP);
    grad_function* grad_function = grad_function_initialize(a, b, result, EXP);
    result->grad_function = grad_function;
    return result;
}

variable* variable_relu(char* name, variable* a) {
    float result_value = 0;
    if (a->value > 0) {
        result_value = a->value;
    }
    variable* result = variable_initialize(name, result_value, a, NULL, RELU);
    grad_function* grad_function = grad_function_initialize(a, NULL, result, RELU);
    result->grad_function = grad_function;
    return result;
}

void variable_print(variable* variable) {
    struct variable* child1 = variable->children[0];
    struct variable* child2 = variable->children[1];
    if (child1 != NULL && child2 != NULL) {
        printf("variable[name=%s, value=%f, grad=%f, from=%s(%f) %s %s(%f)]\n", variable->name, variable->value, variable->grad,
               child1->name, child1->value, OP_STRING[variable->op], child2->name, child2->value);
    } else {
        printf("variable[name=%s, value=%f, grad=%f, op=%s]\n", variable->name, variable->value, variable->grad, OP_STRING[variable->op]);
    }
}

variable* variable_initialize_fresh(char* name, float value) {
    return variable_initialize(name, value, NULL, 0, NOP);
}

variable* variable_initialize(char* name, float value, variable* a, variable* b, OP_ENUM op) {
    variable* result = malloc(sizeof(variable));
    result->name = name;
    result->value = value;
    result->grad = 0;
    result->children[0] = a;
    result->children[1] = b;
    result->op = op;
    result->grad_function = NULL;
    return result;
}

void variable_free(variable* variable) {
    if (variable->grad_function != NULL) {
        grad_function_free(variable->grad_function);
    }
    free(variable);
}
