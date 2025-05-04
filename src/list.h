#ifndef LIST_H
#define LIST_H

#define list_push(list, value)                                              \
    do {                                                                      \
        (list) = list_hold((list), 1, sizeof(*(list)));                   \
        (list)[list_length(list) - 1] = (value);                           \
    } while (0);

void* list_hold(void* list, int count, int item_size);
int list_length(void* list);
void list_free(void* list);

#endif