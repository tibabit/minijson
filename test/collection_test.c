#include <stdlib.h>
#include "../src/collection.h"
#include "assert/assert.h"

module(collection)
{
    suite("collection _test")
    {
        test("# new")
        {
            collection_t * c = collection_new(sizeof(int));
            expect_int((int)c) to not be equal(0);
            collection_destroy(c);
        } end
        test("# add")
        {
            collection_t * c = collection_new(sizeof(int));
            int p = 10;
            collection_add(c, &p);
            expect_int(collection_count(c)) to be equal(1);
            collection_destroy(c);

        } end

        test("# at#int")
        {
            collection_t * c = collection_new(sizeof(int));
            int p = 10;
            collection_add(c, &p);
            int v;
            collection_at(c, 0, &v);
            expect_int(v) to be equal(p);
            collection_destroy(c);

        } end

        test("# at#float")
        {
            collection_t * c = collection_new(sizeof(float));
            float p = 10;
            collection_add(c, &p);
            float v;
            collection_at(c, 0, &v);
            expect_float(v) to be equal(p);
            collection_destroy(c);

        } end

        test("# at#string")
        {
            collection_t * c = collection_new(sizeof(char*));
            char* p = "hello";
            collection_add(c, &p);
            char* v;
            collection_at(c, 0, &v);
            expect_string(v) to be equal(p);
            collection_destroy(c);

        } end

        test("# at#ptr")
        {
            collection_t * c = collection_new(sizeof(void*));
            int *p = malloc(sizeof(int));
            *p = 20;
            collection_add(c, &p);
            int *v;
            collection_at(c, 0, &v);
            expect_int(*v) to be equal(*p);
            collection_destroy(c);

        } end

    } end
}

int main()
{
    register_module(collection);

    run_all();
}
