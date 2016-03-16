#ifndef COLLECTION_H_
#define COLLECTION_H_

typedef void * item_t;

typedef struct _collection
{
    item_t * items;
    int     count;
    int     capacity;
}collection_t;

typedef collection_t * collection_ptr_t;

collection_ptr_t    collection_new      (void);
void                collection_destroy  (collection_ptr_t collection);
void                collection_add      (collection_ptr_t collection, item_t item);
item_t              collection_at       (collection_ptr_t collection, int index);
#endif  // COLLECTION_H_
