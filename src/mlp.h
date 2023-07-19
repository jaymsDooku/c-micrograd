//
// Created by james on 16/07/2023.
//

#ifndef C_MICROGRAD_MLP_H
#define C_MICROGRAD_MLP_H

#include "layer.h"

typedef struct {
    layer** layers;
    int layer_count;
} mlp;



#endif //C_MICROGRAD_MLP_H
