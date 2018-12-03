#include <tex_list.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>

tex_list_item_t* tex_list_item_new(int* err)
{
    tex_list_item_t* item = malloc(sizeof(tex_list_item_t));
    CHECK_RET(item, NULL, "could not create linked list node.")
    memset(item, 0, sizeof(*item));
    return item;
}

void tex_list_item_destroy(tex_list_item_t* item)
{
    // implement destroy
    free(item->next);
    free(item->prev);
    free(item);
    item = NULL;
}

tex_list_t* tex_list_new(int* err)
{
    tex_list_t* list = malloc(sizeof(tex_list_t));
    CHECK_RET(list, NULL, "could not allocate list!!")
    memset(list,0, sizeof(*list));
    return list;
}

int tex_list_append(tex_list_t* list, texture_t* tex)
{
    tex_list_item_t* current = list->head;    

    while(current)
    {
        if(!strcmp(current->tex->name, tex->name))
        {
            fprintf(stderr, "texture already exists!\n");
            return -1;
        }

        current = current->next;
    }

    tex_list_item_t* item = tex_list_item_new(NULL);

    if(!list->head){
        list->head = item;
        list->tail = item;
        item->tex = tex;
        list->count++;
        return 0;
    }

    list->tail->next = item;
    item->prev = list->tail;
    list->tail = item;
    item->next = NULL;
    item->tex = tex;
    list->count++;

    return 0;
}

texture_t* tex_list_get(tex_list_t* list, const char* key)
{
    tex_list_item_t* current = list->head;
    texture_t* tex = NULL;
    while(current)
    {
        if(strcmp(current->tex->name, key) == 0)
        {
            tex = current->tex;
            return tex;
        }

        current = current->next;
    }
    return tex;
}

void tex_list_destroy(tex_list_t* list)
{
    tex_list_item_t* current = list->head;

    while(current)
    {
        tex_list_item_t* next = current->next;
        SDL_DestroyTexture(current->tex->texture);
        free(current);
        current = next;
    }
    free(current);
}