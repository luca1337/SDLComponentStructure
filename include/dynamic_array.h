#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct dynamic_array{
    void** data;
    size_t len;
    size_t offset;
}dynamic_array_t;

dynamic_array_t* dynamic_array_new(size_t size, int* error);

int dynamic_array_insert_at(dynamic_array_t* array, size_t offset, void* elem);

int dynamic_array_insert(dynamic_array_t* array, void* elem);

void dynamic_array_destroy(dynamic_array_t* array);

#endif