/**
 * ISOENGINE
 * clock.h
 * 
 * matt.g@castus.tv
 */

#ifndef __ISOENGINE_CLOCK_H__
#define __ISOENGINE_CLOCK_H__

#include "engine.h"

bool _start_clock(isoengine *engine);
bool _cycle_clock(isoengine *engine, double *res);

#endif