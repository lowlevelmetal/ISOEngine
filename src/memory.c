/**
 * ISOENGINE
 * memory.c
 * 
 * matt.g@castus.tv
 */

#include "memory.h"
#include "macro.h"

#include <string.h>

void *recalloc(void *buffer, size_t nmemb, size_t size) {
    void *buf = realloc(buffer, nmemb * size);
    if(buf == nullptr) {
        ERROR("Out of memory");
        return nullptr;
    }

    memset(buf, 0, nmemb * size);

    return buf;
}