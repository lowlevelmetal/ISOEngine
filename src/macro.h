/**
 * ISOENGINE
 * macro.h
 * 
 * matt.g@castus.tv
 */

#ifndef __ISOENGINE_MACRO_H__
#define __ISOENGINE_MACRO_H__

#include <stdio.h>
#include <stdlib.h>

#ifndef _SUPPRESS_LOG
#ifndef _DEBUG

#define FATAL(str, ...) {\
    fprintf(stderr, "[ISOENGINE] [FATAL]: " str "\n", ##__VA_ARGS__); \
    exit(EXIT_FAILURE); \
}

#define ERROR(str, ...) {\
    fprintf(stderr, "[ISOENGINE] [ERROR]: " str "\n", ##__VA_ARGS__); \
    exit(EXIT_FAILURE); \
}

#define DEBUG(str, ...)

#else

#define FATAL(str, ...) {\
    fprintf(stderr, "[DEBUG] [ISOENGINE] [FATAL @ %s]: " str, "\n", __func__, ##__VA_ARGS__) \
    exit(EXIT_FAILURE); \
}

#define ERROR(str, ...) {\
    fprintf(stderr, "[DEBUG] [ISOENGINE] [ERROR @ %s]: " str "\n", __func__, ##__VA_ARGS__); \
    exit(EXIT_FAILURE); \
}

#endif // ! _DEBUG
#endif // ! _SUPPRESS_LOG
#endif // ! __ISOENGINE_MACRO_H__