/**
 * ISOENGINE
 * test_engine.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/isoengine.h"

#include <assert.h>
#include <stdlib.h>

int main() {
    void *engine = nullptr;
    assert((engine = isoengine_create()) != NULL);

    free(engine);
}