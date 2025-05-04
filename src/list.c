#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define LIST_RAW_DATA(list) ((int*)(list) - 2)
#define LIST_CAPACITY(list) (LIST_RAW_DATA(list)[0])
#define LIST_OCCUPIED(list) (LIST_RAW_DATA(list)[1])

void* list_hold(void* list, int count, int item_size) {
    if (list == NULL) {
        int raw_size = (sizeof(int) * 2) + (item_size * count);
        int* base = (int*)malloc(raw_size);
        base[0] = count;  // capacity
        base[1] = count;  // occupied
        return base + 2;
    } else if (LIST_OCCUPIED(list) + count <= LIST_CAPACITY(list)) {
        LIST_OCCUPIED(list) += count;
        return list;
    } else {
        int needed_size = LIST_OCCUPIED(list) + count;
        int float_curr = LIST_CAPACITY(list) * 2;
        int capacity = needed_size > float_curr ? needed_size : float_curr;
        int occupied = needed_size;
        int raw_size = sizeof(int) * 2 + item_size * capacity;
        int* base = (int*)realloc(LIST_RAW_DATA(list), raw_size);
        base[0] = capacity;
        base[1] = occupied;
        return base + 2;
    }
}

int list_length(void* list) {
    return (list != NULL) ? LIST_OCCUPIED(list) : 0;
}

void list_free(void* list) {
    if (list != NULL) {
        free(LIST_RAW_DATA(list));
    }
}