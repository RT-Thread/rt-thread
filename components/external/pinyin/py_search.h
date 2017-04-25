#ifndef _PY_SEARCH_H_
#define _PY_SEARCH_H_

#include <stdint.h>

#define PY_LIST_2 // PY_LIST_1,PY_LIST_2

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _py_mb
{
    const char *msg; // Æ´Òô´®
#ifdef PY_LIST_2
    uint8_t wlen; // ×Ö´Ê³¤¶È
#endif
    const char *mb; // Âë±í
}py_mb_t;

typedef struct _py_num
{
    const char *msg; // Êý×Ö´®
    uint16_t index; // Âë±íÐòºÅ
}py_num_t;

uint8_t py_mb_search(const char *msg, const py_mb_t **list, uint8_t size);
uint8_t py_num_search(const char *msg, const py_mb_t **list, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif
