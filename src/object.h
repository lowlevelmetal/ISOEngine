/**
 * ISOENGINE
 * object.h
 * 
 * matt.g@castus.tv
 */

#ifndef __ISOENGINE_OBJECT_H__
#define __ISOENGINE_OBJECT_H__

#include "isoengine/isoengine.h"

typedef struct isoengine_object {
    isoengine_keypress_callback keypress_callback;
    isoengine_3dcoords coords;
} isoengine_object;

struct isoengine;
bool _object_handle_keys(struct isoengine *engine, const bool *const scancodes);

#endif