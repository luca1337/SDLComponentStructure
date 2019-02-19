#include <dynamic_array.h>

#define NO_MEM -1
#define OK 0
#define OUT_OF_BOUND 1

dynamic_array_t* dynamic_array_new(size_t size, int* error)
{
    if(error)
        *error = OK;

    dynamic_array_t* list = (dynamic_array_t*)malloc(sizeof(dynamic_array_t));
    if(!list){

        if(error)
            *error = NO_MEM;

        return NULL;
    }
    memset(list, 0, sizeof(dynamic_array_t));

    if(size)
    {
        list->len = size;
        list->data = malloc(sizeof(void*) * list->len);
        if(!list->data)
        {
            free(list);
            if(error)
                *error = NO_MEM;
            return NULL;
        }
        memset(list->data, 0, sizeof(void*) * list->len);
    }

    return list;
}

int dynamic_array_insert_at(dynamic_array_t* array, size_t offset, void* elem)
{
    if(offset >= array->len)
    {
        void* new_data = realloc(array->data, sizeof(void*) * offset + 1);
        if(!new_data)
        {
            return NO_MEM;
        }
        array->data = new_data;
        unsigned long remains = (sizeof(void*) * offset + 1) - (sizeof(void*) * array->len);
        memset(array->data + sizeof(void*) * array->len, 0, remains);
        array->len = offset + 1;
    }

    array->data[offset] = elem;
    return OK;
}

int dynamic_array_insert(dynamic_array_t* array, void* elem)
{
    if(array->offset >= array->len)
    {
        void* new_data = realloc(array->data, sizeof(void*) * array->offset + 1);
        if(!new_data)
        {
            return NO_MEM;
        }
        array->data = new_data;
        unsigned long remains = (sizeof(void*) * array->offset + 1) - (sizeof(void*) * array->len);
        memset(array->data + sizeof(void*) * array->len, 0, remains);
        array->len = array->offset + 1;
    }

    array->data[array->offset++] = elem;
    return OK;
}

void dynamic_array_destroy(dynamic_array_t* array)
{
    for(size_t i = 0; i < array->len; i++)
        array->data[i] = 0;
    
    free(array->data);
    array->data = NULL;
    free(array);
}