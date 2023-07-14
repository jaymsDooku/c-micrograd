//
// Created by james on 14/07/2023.
//

#ifndef ALGORITHMS_SET_H
#define ALGORITHMS_SET_H

#include <stdbool.h>

#define SET_SIZE 100

typedef struct {
    int (*hash_function)(void*);
    void* arr[SET_SIZE];
} set;

int fnv1a_hash(void* value);
void set_add(set* set, void* value);
void set_remove(set* set, void* value);
bool set_contains(set* set, void* value);
set* set_initialize();
set* set_initialize_hash(int (*hash_function)(void*));
void set_free(set* set);

#endif //ALGORITHMS_SET_H
