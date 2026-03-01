/**
 * ISOENGINE
 * test_engine.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/engine.h"

#include <assert.h>
#include <stddef.h>

int main() {
    isoengine *engine = NULL;
    assert((engine = create_iso_engine()) != NULL);

    free(engine);
}