#include "list.h"


list_t* list_create(size_t element_size, size_t capacity)
{
    // allocating memory for the list
    list_t* list = (list_t*)malloc(sizeof(list_t));

    // if the memory hasn't been allocated correctly
    if (!list) 
        return NULL;

    // allocating memory for the underlying array
    list->data = malloc(capacity * element_size);

    // if the memory hasn't been allocated correctly
    if (!list->data) 
    {
        // removing the list created earlier
        free(list);

        return NULL;
    }

    // setting other properties
    list->count = 0;
    list->capacity = capacity;
    list->element_size = element_size;

    // returning the successfully created list 
    return list;
}

int list_resize(list_t* list)
{
    // an increased capacity
    size_t new_capacity = list->capacity * 2;

    // reallocating the memory of list's underlying array
    void* new_data = realloc(
        list->data, 
        new_capacity * list->element_size
    );

    // if the memory hasn't been re-allocated correctly
    if (!new_data) return -1;

    // setting the list's properties
    list->data = new_data;
    list->capacity = new_capacity;

    // everything is fine
    return 0;
}

int list_add(list_t* list, const void* obj) 
{
    // if there' no more space...
    if (list->count == list->capacity) 
    {
        // ...resizing the underlying array and 
        // if there's an error returning -1 
        if (list_resize(list) != 0) return -1;
    }

    // copying the obj to the list
    memcpy(
        // the first byte of underlying array + (count of elements * size of single element)
        (char*)list->data + list->count * list->element_size,
        obj,
        list->element_size
    );
    
    // increasing the count of elements
    list->count++;

    // everything's fine
    return 0;
}

void list_pop(list_t* list)
{
    if (list->count > 0)
    {
        // just decreasing the count 
        // (left element will be overwritten by next element attition)
        list->count--;
    }
}

void* list_get(list_t* list, size_t index)
{
    // checking if the index is in the bounds
    if (index >= list->count)
    {
        fprintf(stderr, "clist: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    // returning the address of the element at the index
    return (char*)list->data + index * list->element_size;
}

void list_free(list_t* list)
{
    free(list->data);
    free(list);
}