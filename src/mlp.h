//
// Created by james on 16/07/2023.
//

#ifndef C_MICROGRAD_MLP_H
#define C_MICROGRAD_MLP_H

#include "layer.h"
#include "dataset.h"

typedef struct {
    layer** layers;
    int layer_count;
} mlp;

typedef struct {
    mlp* mlp;
    dataset** layer_outputs;
    dataset* final_result;
    float* final_values;
} mlp_result;

mlp_result* mlp_activate(mlp* mlp, dataset* inputs);
void mlp_result_free(mlp_result* mlp_result);

void mlp_print(mlp* mlp);
mlp* mlp_initialize(int layer_in, int* layer_outputs, int layer_outputs_length);
void mlp_free(mlp* mlp);

#endif //C_MICROGRAD_MLP_H
