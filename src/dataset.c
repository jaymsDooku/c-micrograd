//
// Created by james on 16/07/2023.
//

#include "dataset.h"

#include <stdio.h>
#include <stdlib.h>

#include "math_util.h"

dataset* dataset_random(int count, int input_length) {
    variable*** X = malloc(count * sizeof(variable**));
    int* y = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        variable** x = malloc(input_length * sizeof(variable*));
        for (int j = 0; j < input_length; j++) {
            char input_name[5];
            snprintf(input_name, 5, "%s%d", "x", i);
            float value = randf(-1, 1);
            x[i] = variable_initialize_fresh(input_name, value);
        }
        X[i] = x;

        float y_val = randf(0, 1);
        if (y_val > 0.5) {
            y[i] = 1;
        } else {
            y[i] = 0;
        }
    }

    return dataset_initialize(X, y, count, input_length);
}

dataset* dataset_initialize(variable*** X, int* y, int count, int input_length) {
    dataset* result = malloc(sizeof(dataset));
    result->X = X;
    result->input_length = input_length;
    result->y = y;
    result->count = count;
    return result;
}

void dataset_free(dataset* dataset) {
    for (int i = 0; i < dataset->count; i++) {
        variable** input = dataset->X[i];
        for (int j = 0; j < dataset->input_length; i++) {
            variable_free(input[j]);
        }
        free(input);
    }
    free(dataset->X);
    free(dataset->y);
    free(dataset);
}
