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
    isoengine_3dcoords coords3d = {0, 0, 0};
    isoengine_2dcoords coords2d = {0, 0};

    void *engine = isoengine_create();
    assert(engine != nullptr);

    void *objects3d[ITER];
    void *objects2d[ITER];
    for(int i = 0; i < ITER; i++) {
        assert((objects3d[i] = isoengine_object3d_create(engine, &coords3d)) != nullptr);
        assert((objects2d[i] = isoengine_object2d_create(engine, &coords2d)) != nullptr);
    }

    assert(isoengine_destroy(engine));

    return EXIT_SUCCESS;
}