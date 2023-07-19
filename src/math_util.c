//
// Created by james on 16/07/2023.
//

#include "math_util.h"

#include <stdlib.h>

float randf(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
