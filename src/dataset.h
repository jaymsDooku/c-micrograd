//
// Created by james on 16/07/2023.
//

#ifndef C_MICROGRAD_DATASET_H
#define C_MICROGRAD_DATASET_H

//https://github.com/scikit-learn/scikit-learn/blob/7f9bad99d/sklearn/datasets/_samples_generator.py#L786

#include "variable.h"

typedef struct {
    variable*** X;
    int input_length;
    int* y;
    int count;
} dataset;

dataset* dataset_random(int count, int input_length);
dataset* dataset_initialize(variable*** X, int* y, int count, int input_length);
void dataset_free(dataset* dataset);

#endif //C_MICROGRAD_DATASET_H
