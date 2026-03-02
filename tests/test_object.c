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
    isoengine_3dcoords coords = {0, 0, 0};

    void *engine = isoengine_create();
    assert(engine != nullptr);

    void *objects[2048];
    for(int i = 0; i < ITER; i++) {
        assert((objects[i] = isoengine_object_create(engine, &coords)) != nullptr);
    }

    assert(isoengine_destroy(engine));

    return EXIT_SUCCESS;
}