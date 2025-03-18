#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// List represents a dynamic array, which size is increased 
// automaticaly according to new elements being added
typedef struct {
    // a pointer to the list's underlying array
    void* data;

    // a number of elements
    size_t count;

    // a size of list's underlying array
    size_t capacity;

    // a size of a single element
    size_t element_size;
} list_t;


// Creates a new list_t and returns a pointer to this list
list_t* list_create(size_t element_size, size_t capacity);

// Resizes the underlying array by two times
int list_resize(list_t* list);

// Adds a new object in the list (OBJ SIZE MUST BE EQUAL TO THE LIST ELEMENT SIZE)
int list_add(list_t* list, const void* obj);

// Removes the last element in the list
void list_pop(list_t* list);

// Returns a pointer to an element at the index
void* list_get(list_t* list, size_t index);

// Deletes the list
void list_free(list_t* list);

#endif