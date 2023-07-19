//
// Created by james on 16/07/2023.
//

#ifndef C_MICROGRAD_LAYER_H
#define C_MICROGRAD_LAYER_H

#include "neuron.h"

typedef struct {
    neuron** neurons;
    int neurons_count;
    bool linear;
} layer;

variable** layer_activate(layer* layer, variable** inputs);
layer* layer_initialize(int neuron_weights_size, int neurons_count, bool linear);
void layer_free(layer* layer);

#endif //C_MICROGRAD_LAYER_H
