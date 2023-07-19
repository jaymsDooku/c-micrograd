//
// Created by james on 16/07/2023.
//

#include "layer.h"

#include <stdlib.h>

variable** layer_activate(layer* layer, variable** inputs) {
    variable** outputs = malloc(layer->neurons_count * sizeof(variable*));
    for (int i = 0; i < layer->neurons_count; i++) {
        neuron* neuron = layer->neurons[i];
        outputs[i] = neuron_activate(neuron, inputs);
    }
    return outputs;
}

layer* layer_initialize(int neuron_weights_size, int neurons_count, bool linear) {
    layer* result = malloc(sizeof(layer));
    result->neurons = malloc(neurons_count * sizeof(neuron*));
    for (int i = 0; i < neurons_count; i++) {
        result->neurons[i] = neuron_initialize(neuron_weights_size, linear);
    }
    result->neurons_count = neurons_count;
    result->linear = linear;
    return result;
}

void layer_free(layer* layer) {
    for (int i = 0; i < layer->neurons_count; i++) {
        neuron_free(layer->neurons[i]);
    }
    free(layer->neurons);
    free(layer);
}
