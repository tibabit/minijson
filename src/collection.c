#include "collection.h"

#include <stdlib.h>
#include <string.h>

#define COLLECTION_CAPACITY_BIN_SIZE    16
#define ITEM_SIZE                       sizeof(item_t)

collection_ptr_t collection_new(void)
{
    collection_ptr_t collection = calloc(1, sizeof(collection_t));

    return collection;
}
void collection_destroy(collection_ptr_t collection)
{
    if (collection->items)
    {
        free(collection->items);
    }
    free(collection);
}
void collection_add(collection_ptr_t collection, item_t item)
{
    if (collection->count == collection->capacity)
    {
        collection->items = realloc(collection->items,
            (collection->count + COLLECTION_CAPACITY_BIN_SIZE) * ITEM_SIZE);
    }
    collection->items[collection->count] =  item;
    collection->count++;
}
item_t collection_at(collection_ptr_t collection, int index)
{
    if (index < collection->count)
    {
        return collection->items[index];
    }
    return NULL;
}
