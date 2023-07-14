//
// Created by james on 14/07/2023.
//

#ifndef ALGORITHMS_LIST_H
#define ALGORITHMS_LIST_H

#define DEFAULT_SIZE 1024

typedef struct {
    void** arr;
    int arr_size;
    int type_size;
    int count;
} list;

void list_add(list* list, void* value);
void list_insert(list* list, int index, void* value);
void* list_get(list* list, int index);
void* list_remove(list* list, int index);
void** list_allocate(list* list, int new_arr_size);
list* list_initialize(int type_size);
void list_free(list* list);

#endif //ALGORITHMS_LIST_H
