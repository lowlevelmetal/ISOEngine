/**
 * ISOENGINE
 * memory.c
 * 
 * matt.g@castus.tv
 */

#include "memory.h"
#include "macro.h"

#include <string.h>
#include <stdckdint.h>

void *recalloc(void *buffer, size_t old_nmemb, size_t new_nmemb, size_t size) {
    size_t result = 0;
    if(ckd_mul(&result, new_nmemb, size)) {
        ERROR("Overflow protection");
        return nullptr;
    }
    
    void *buf = realloc(buffer, result);
    if(buf == nullptr) {
        ERROR("Out of memory");
        return nullptr;
    }

    if(new_nmemb > old_nmemb)
        memset((char*)buf + (size * old_nmemb), 0, size * (new_nmemb - old_nmemb));

    return buf;
}