/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_MEMCPY_H
#define USB_MEMCPY_H

#include <stdint.h>
#include <stddef.h>

#define ALIGN_UP_DWORD(x) ((uint32_t)(uintptr_t)(x) & (sizeof(uint32_t) - 1))

static inline void dword2array(char *addr, uint32_t w)
{
    addr[0] = w;
    addr[1] = w >> 8;
    addr[2] = w >> 16;
    addr[3] = w >> 24;
}

static inline void *usb_memcpy(void *s1, const void *s2, size_t n)
{
    char *b1 = (char *)s1;
    const char *b2 = (const char *)s2;
    uint32_t *w1;
    const uint32_t *w2;

    if (ALIGN_UP_DWORD(b1) == ALIGN_UP_DWORD(b2)) {
        while (ALIGN_UP_DWORD(b1) != 0 && n > 0) {
            *b1++ = *b2++;
            --n;
        }

        w1 = (uint32_t *)b1;
        w2 = (const uint32_t *)b2;

        while (n >= 4 * sizeof(uint32_t)) {
            *w1++ = *w2++;
            *w1++ = *w2++;
            *w1++ = *w2++;
            *w1++ = *w2++;
            n -= 4 * sizeof(uint32_t);
        }

        while (n >= sizeof(uint32_t)) {
            *w1++ = *w2++;
            n -= sizeof(uint32_t);
        }

        b1 = (char *)w1;
        b2 = (const char *)w2;

        while (n--) {
            *b1++ = *b2++;
        }
    } else {
        while (n > 0 && ALIGN_UP_DWORD(b2) != 0) {
            *b1++ = *b2++;
            --n;
        }

        w2 = (const uint32_t *)b2;

        while (n >= 4 * sizeof(uint32_t)) {
         dword2array(b1, *w2++);
            b1 += sizeof(uint32_t);
         dword2array(b1, *w2++);
            b1 += sizeof(uint32_t);
         dword2array(b1, *w2++);
            b1 += sizeof(uint32_t);
         dword2array(b1, *w2++);
            b1 += sizeof(uint32_t);
            n -= 4 * sizeof(uint32_t);
        }

        while (n >= sizeof(uint32_t)) {
         dword2array(b1, *w2++);
            b1 += sizeof(uint32_t);
            n -= sizeof(uint32_t);
        }

        b2 = (const char *)w2;

        while (n--) {
            *b1++ = *b2++;
        }
    }
    return s1;
}
#endif
