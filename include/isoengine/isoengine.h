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

// Create window
bool isoengine_window_create(void *const engine, const char *title, uint16_t width, uint16_t height);

#endif