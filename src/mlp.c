//
// Created by james on 04/08/2023.
//

#include "mlp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mlp_result* mlp_activate(mlp* mlp, dataset* ds) {
    layer** layers = mlp->layers;
    dataset** layer_outputs = malloc(mlp->layer_count * sizeof(dataset*));

    variable*** first_layer_output = malloc(ds->count * sizeof(variable**));
    variable*** first_X = ds->X;
    printf("ds count: %d\n", ds->count);
    printf("ds input length: %d\n", ds->input_length);
    layer* first_layer = layers[0];
    for (int i = 0; i < ds->count; i++) {
        variable** inputs = first_X[i];
        variable** outputs = layer_activate(first_layer, inputs);
        first_layer_output[i] = outputs;
    }

    int* first_y = malloc(ds->count * sizeof(int));
    memcpy(first_y, ds->y, ds->count * sizeof(int));
    layer_outputs[0] = dataset_initialize(first_layer_output, first_y, ds->count, first_layer->neurons_count);

    for (int i = 1; i < mlp->layer_count; i++) {
        dataset* last_output = layer_outputs[i - 1];

        variable*** next_layer_output = malloc(ds->count * sizeof(variable**));
        variable*** next_X = last_output->X;
        layer* next_layer = layers[i];
        for (int j = 0; j < ds->count; j++) {
            variable** inputs = next_X[j];
            variable** outputs = layer_activate(next_layer, inputs);
            next_layer_output[j] = outputs;
        }

        int* next_y = malloc(ds->count * sizeof(int));
        memcpy(next_y, ds->y, ds->count * sizeof(int));
        layer_outputs[i] = dataset_initialize(next_layer_output, next_y, ds->count, next_layer->neurons_count);
    }

    variable*** copyX = malloc(ds->count * sizeof(variable**));
    dataset* final_output = layer_outputs[mlp->layer_count - 1];
    int* final_y = malloc(ds->count * sizeof(int));
    float* final_values = malloc(ds->count * sizeof(float));
    for (int i = 0; i < ds->count; i++) {
        variable** input = ds->X[i];
        variable** inputCopy = malloc(ds->input_length * sizeof(variable*));
        for (int j = 0; j < ds->input_length; j++) {
            inputCopy[j] = variable_copy(input[j]);
        }
        copyX[i] = inputCopy;

        float y_value = final_output->X[i][0]->value;
        final_values[i] = y_value;
        if (y_value > 0) {
            final_y[i] = 1;
        } else {
            final_y[i] = 0;
        }
    }

    dataset* final_result = dataset_initialize(copyX, final_y, ds->count, ds->input_length);

    mlp_result* results = malloc(sizeof(mlp_result));
    results->mlp = mlp;
    results->layer_outputs = layer_outputs;
    results->final_result = final_result;
    results->final_values = final_values;
    return results;
}

void mlp_result_free(mlp_result* mlp_result) {
    for (int i = 0; i < mlp_result->mlp->layer_count; i++) {
        dataset_free(mlp_result->layer_outputs[i]);
    }
    dataset_free(mlp_result->final_result);
    free(mlp_result);
}

void mlp_print(mlp* mlp) {
    printf("mlp\n");
    printf("layer count: %d\n", mlp->layer_count);
    printf("layers:\n");
    for (int i = 0; i < mlp->layer_count; i++) {
        layer* layer = mlp->layers[i];
        printf("layer %d - %d - %d\n", i, layer->neurons_count, layer->linear);
        for (int j = 0; j < layer->neurons_count; j++) {
            neuron* neuron = layer->neurons[j];
            printf("\tneuron %d - %d - %d\n", j, neuron->weights_size, neuron->linear);
        }
    }
}

mlp* mlp_initialize(int layer_in, int* layer_outputs, int layer_outputs_length) {
    mlp* result = malloc(sizeof(mlp));
    result->layer_count = layer_outputs_length;
    result->layers = malloc(result->layer_count * sizeof(layer*));
    result->layers[0] = layer_initialize(layer_in, layer_outputs[0], false);
    for (int i = 1; i < result->layer_count; i++) {
        result->layers[i] = layer_initialize(layer_outputs[i - 1], layer_outputs[i], i == result->layer_count-1);
    }
    return result;
}

void mlp_free(mlp* mlp) {
    free(mlp);
}