/**
 * ISOENGINE Examples
 * sprite.c
 * 
 * matt.g@castus.tv
 */

#include "isoengine/isoengine.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
    void *engine = isoengine_create();
    if(!engine) {
        fprintf(stderr, "Failed to create isoengine instance\n");
        return EXIT_FAILURE;
    }

    if(!isoengine_window_create(engine, "ISOENGINE Sprite Example", 1280, 720)) {
        fprintf(stderr, "Failed to create isoengine window\n");
        isoengine_destroy(engine);
        return EXIT_FAILURE;
    }

    isoengine_2dcoords coords = {256, 256};
    uint32_t obj = isoengine_object2d_create(engine, &coords);
    if(!obj) {
        fprintf(stderr, "Failed to create 2d object\n");
        return EXIT_FAILURE;
    }

    if(!isoengine_object2d_texture(engine, obj, "assets/sprite.png")) {
        fprintf(stderr, "Failed to apply texture to object\n");
        return EXIT_FAILURE;
    }

    while(isoengine_handle_events(engine)) {
        if(!isoengine_render_draw(engine)) {
            fprintf(stderr, "Failed to render!\n");
            isoengine_destroy(engine);
            return EXIT_FAILURE;
        }
    }

    if(!isoengine_destroy(engine)) {
        fprintf(stderr, "Failed to destroy isoengine!\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}