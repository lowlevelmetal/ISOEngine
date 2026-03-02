/**
 * ISOENGINE Examples
 * window.c
 * 
 * matt.g@castus.tv
 */

#include <isoengine/isoengine.h>

#include <stdlib.h>
#include <stdio.h>

int main() {
    void *engine = isoengine_create();

    if(!isoengine_window_create(engine, "ISOENGINE Window Example", 1280, 720)) {
        fprintf(stderr, "Failed to create window\n");
        isoengine_destroy(engine);
        return EXIT_FAILURE;
    }

    while(isoengine_handle_events(engine)) {
        if(!isoengine_render_draw(engine)) {
            fprintf(stderr, "Failed to render!\n");
            break;
        }
    }

    isoengine_destroy(engine);

    return EXIT_SUCCESS;
}