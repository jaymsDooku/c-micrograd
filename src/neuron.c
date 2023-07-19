//
// Created by james on 14/07/2023.
//

#include "neuron.h"

#include <stdio.h>
#include <stdlib.h>

#include "math_util.h"

void neuron_print(neuron* neuron) {
    variable** weights = neuron->weights;
    for (int i = 0; i < neuron->weights_size; i++) {
        variable* weight = weights[i];
        printf("%f, ", weight->value);
    }
    printf("\n");
}

variable* neuron_activate(neuron* neuron, variable** inputs) {
    variable** weights = neuron->weights;
    variable* bias = neuron->bias;

    variable* sum = variable_initialize_fresh("sum", 0);
    for (int i = 0; i < neuron->weights_size; i++) {
        variable* weight = weights[i];
        variable* input = inputs[i];
        variable* weight_input = variable_mul("weight_input", weight, input);
        variable* new_sum = variable_add("sum", sum, weight_input);
        variable_free(sum);
        variable_free(weight_input);
        sum = new_sum;
    }

    variable* act = variable_add("act", sum, bias);
    if (!neuron->linear) {
        variable* act_relu = variable_relu("act_relu", act);
        variable_free(act);
        return act_relu;
    }
    return act;
}

neuron* neuron_initialize(int weights_size, bool linear) {
    neuron* result = malloc(sizeof(neuron));
    result->weights = malloc(weights_size * sizeof(variable*));
    for (int i = 0; i < weights_size; i++) {
        char weight_name[5];
        snprintf(weight_name, 5, "%s%d", "w", i);
        result->weights[i] = variable_initialize_fresh(weight_name, randf(-1, 1));
    }
    result->weights_size = weights_size;
    result->bias = variable_initialize_fresh("b", 0);
    result->linear = linear;
    return result;
}

void neuron_free(neuron* neuron) {
    for (int i = 0; i < neuron->weights_size; i++) {
        variable_free(neuron->weights[i]);
    }
    free(neuron->weights);
    free(neuron->bias);
    free(neuron);
}
