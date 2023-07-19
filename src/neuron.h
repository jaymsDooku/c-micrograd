//
// Created by james on 14/07/2023.
//

#ifndef C_MICROGRAD_NEURON_H
#define C_MICROGRAD_NEURON_H

#include "variable.h"

#include <stdbool.h>

typedef struct {
    variable** weights;
    int weights_size;
    variable* bias;
    bool linear;
} neuron;

void neuron_print(neuron* neuron);
variable* neuron_activate(neuron* neuron, variable** x);
neuron* neuron_initialize(int weights_size, bool linear);
void neuron_free(neuron* neuron);

#endif //C_MICROGRAD_NEURON_H
