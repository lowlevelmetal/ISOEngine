/**
 * ISOENGINE
 * engine.h
 * 
 * matt.g@castus.tv
 */

#ifndef __ISOENGINE_ISOENGINE_H__
#define __ISOENGINE_ISOENGINE_H__

#include <stdint.h>

// Initialize engine. Setup internal data structures.
void *isoengine_create();

// Destroy engine instance
bool isoengine_destroy(void *engine);


bool isoengine_handle_events(void *engine);

// Create window
bool isoengine_window_create(void *const engine, const char *title, uint16_t width, uint16_t height);


bool isoengine_render_draw(void *const engine);

#endif