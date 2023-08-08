//
// Created by james on 16/07/2023.
//

#include "dataset.h"

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "math_util.h"


variable* dataset_min(dataset* dataset, int input_index) {
    variable* result = dataset->X[0][input_index];
    for (int i = 1; i < dataset->count; i++) {
        variable** x = dataset->X[i];
        if (x[input_index]->value < result->value) {
            result = x[input_index];
        }
    }
    return result;
}

variable* dataset_max(dataset* dataset, int input_index) {
    variable* result = dataset->X[0][input_index];
    for (int i = 1; i < dataset->count; i++) {
        variable** x = dataset->X[i];
        if (x[input_index]->value > result->value) {
            result = x[input_index];
        }
    }
    return result;
}

dataset* dataset_make_moons(int count, float noise) {
    int input_length = 2;
    variable*** X = malloc(count * sizeof(variable**));
    int* y = malloc(count * sizeof(int));

    float x_start = 0;
    float x_stop = M_PI;
    float x_delta = x_stop - x_start;
    float x_step = x_delta / (count / 2);

    float y_start = 0;
    float y_stop = M_PI;
    float y_delta = y_stop - y_start;
    float y_step = y_delta / (count / 2);

    for (int i = 0; i < count / 2; i++) {
        variable** x = malloc(input_length * sizeof(variable*));
        x[0] = variable_initialize_fresh("x", (cosf(x_start)) + randf(-noise, noise));
        x[1] = variable_initialize_fresh("y", (sinf(y_start)) + randf(-noise, noise));
        x_start += x_step;
        y_start += y_step;

        X[i] = x;
        y[i] = 0;
    }

    x_start = 0;
    y_start = 0;

    for (int i = count / 2; i < count; i++) {
        variable** x = malloc(input_length * sizeof(variable*));
        x[0] = variable_initialize_fresh("x", (1.f - cosf(x_start)) + randf(-noise, noise));
        x[1] = variable_initialize_fresh("y", (1.f - sinf(y_start) - 0.5f) + randf(-noise, noise));
        x_start += x_step;
        y_start += y_step;

        X[i] = x;
        y[i] = 1;
    }

    return dataset_initialize(X, y, count, input_length);
}

dataset* dataset_random(int count, int input_length) {
    variable*** X = malloc(count * sizeof(variable**));
    int* y = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        variable** x = malloc(input_length * sizeof(variable*));
        for (int j = 0; j < input_length; j++) {
            char input_name[5];
            snprintf(input_name, 5, "%s%d", "x", j);
            float value = randf(-1, 1);
            x[j] = variable_initialize_fresh(input_name, value);
        }
        X[i] = x;

        float y_val = randf(0.f, 1.f);
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
        for (int j = 0; j < dataset->input_length; j++) {
            variable_free(input[j]);
        }
        free(input);
    }
    free(dataset->X);
    free(dataset->y);
    free(dataset);
}
