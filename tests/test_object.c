/**
 * ISOENGINE - Tests
 * test_object.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/isoengine.h"

#include <assert.h>
#include <stdlib.h>

#define ITER 2048

int main() {
    void *engine = isoengine_create();
    assert(engine != nullptr);

    void *objects[2048];
    for(int i = 0; i < ITER; i++) {
        assert((objects[i] = isoengine_object_create(engine, 0, 0)) != nullptr);
    }

    return EXIT_SUCCESS;
}