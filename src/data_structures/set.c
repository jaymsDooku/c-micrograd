//
// Created by james on 14/07/2023.
//

#include "set.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
#define FNV_PRIME 0x01000193
#define FNV_OFFSET_BASIS 0x811c9dc5
// https://gist.github.com/ctmatthews/c1cbd1b2e68c29a88b236475a0b26cd0
int fnv1a_hash(void* value) {
    int result = FNV_OFFSET_BASIS;
    char* s = (char*) value;

    for (int i = 0; i < sizeof(void*); i++) {
        result ^= (int) (*s);
        result *= (int) FNV_PRIME;
        s++;
    }
    //printf("real hash: %d\n", result);
    return result % SET_SIZE;
}

void set_add(set* set, void* value) {
    int hash = fnv1a_hash(value);
    set->arr[hash] = value;
}

void set_remove(set* set, void* value) {
    int hash = fnv1a_hash(value);
    set->arr[hash] = NULL;
}

bool set_contains(set* set, void* value) {
    int hash = fnv1a_hash(value);
    return set->arr[hash] != NULL;
}

set* set_initialize() {
    return set_initialize_hash(fnv1a_hash);
}

set* set_initialize_hash(int (*hash_function)(void*)) {
    set* result = malloc(sizeof(set));
    for (int i = 0; i < SET_SIZE; i++) {
        result->arr[i] = NULL;
    }
    result->hash_function = hash_function;
    return result;
}

void set_free(set* set) {
    free(set);
}