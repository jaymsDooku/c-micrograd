//
// Created by james on 14/07/2023.
//

#include "list.h"

#include <stdio.h>
#include <stdlib.h>

void list_add(list* list, void* value) {
    list->arr[list->count++] = value;
}

void list_insert(list* list, int index, void* value) {
    if (index < 0 || index > list->arr_size) {
        return;
    }

    if (list->arr[index] == NULL) {
        list->count++;
    }

    list->arr[index] = value;
}

void* list_get(list* list, int index) {
    return list->arr[index];
}

void* list_remove(list* list, int index) {
    void* removed = list->arr[index];
    list->arr[index] = NULL;
    list->count--;
    return removed;
}

void** list_allocate(list* list, int new_arr_size) {
    void** new_arr = malloc(new_arr_size * list->type_size);
    if (list->arr != NULL) {
        for (int i = 0; i < list->arr_size; i++) {
            new_arr[i] = list->arr[i];
        }
    } else {
        for (int i = 0; i < new_arr_size; i++) {
            new_arr[i] = NULL;
        }
    };
    list->arr_size = new_arr_size;
    return new_arr;
}

list* list_initialize(int type_size) {
    list* result = malloc(sizeof(list));
    result->type_size = type_size;
    result->count = 0;
    result->arr = NULL;
    result->arr = list_allocate(result, DEFAULT_SIZE);
    return result;
}

void list_free(list* list) {
    free(list->arr);
    free(list);
}
