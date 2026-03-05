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
    isoengine_2dcoords coords2d = {0, 0};

    void *engine = isoengine_create();
    assert(engine != nullptr);

    {
        uint32_t objects2d[ITER];
        for(int i = 0; i < ITER; i++) {
            assert((objects2d[i] = isoengine_object2d_create(engine, &coords2d)) != 0);
        }

        for(int i = 0; i < ITER/2; i++) {
            assert(isoengine_object2d_delete(engine, objects2d[i*2]));
        }
    }

    {
        uint32_t objects2d[ITER*2];
        for(int i = 0; i < ITER*2; i++) {
            assert((objects2d[i] = isoengine_object2d_create(engine, &coords2d)) != 0);
        }

        for(int i = 0; i < (ITER*2)/2; i++) {
            assert(isoengine_object2d_delete(engine, objects2d[i*2]));
        }
    }

    {
        uint32_t objects2d[ITER*3];
        for(int i = 0; i < ITER*3; i++) {
            assert((objects2d[i] = isoengine_object2d_create(engine, &coords2d)) != 0);
        }

        for(int i = 0; i < (ITER*3)/2; i++) {
            assert(isoengine_object2d_delete(engine, objects2d[i*2]));
        }
    }

    {
        uint32_t objects2d[ITER*20];
        for(int i = 0; i < ITER*20; i++) {
            assert((objects2d[i] = isoengine_object2d_create(engine, &coords2d)) != 0);
        }

        for(int i = 0; i < (ITER*20)/2; i++) {
            assert(isoengine_object2d_delete(engine, objects2d[i*2]));
        }
    }

    {
        uint32_t objects2d[ITER*100];
        for(int i = 0; i < ITER*100; i++) {
            assert((objects2d[i] = isoengine_object2d_create(engine, &coords2d)) != 0);
        }

        for(int i = 0; i < (ITER*100)/2; i++) {
            assert(isoengine_object2d_delete(engine, objects2d[i*2]));
        }
    }

    assert(isoengine_destroy(engine));

    return EXIT_SUCCESS;
}