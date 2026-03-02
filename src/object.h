/**
 * ISOENGINE
 * object.h
 * 
 * matt.g@castus.tv
 */

#ifndef __ISOENGINE_OBJECT_H__
#define __ISOENGINE_OBJECT_H__

#include "isoengine/isoengine.h"

#include <stdint.h>

typedef struct isoengine_object {
    isoengine_keypress_callback keypress_callback;
    uint32_t x;
    uint32_t y;
} isoengine_object;

#endif