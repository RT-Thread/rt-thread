/**
 * @file misc.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "misc.h"

#ifndef BFLB_USE_ROM_DRIVER
/****************************************************************************/ /**
 * @brief  Char memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of char
 *
 * @return Destination pointer
 *
 *******************************************************************************/
__WEAK__ void *ATTR_TCM_SECTION arch_memcpy(void *dst, const void *src, uint32_t n)
{
    const uint8_t *p = src;
    uint8_t *q = dst;

    while (n--) {
        *q++ = *p++;
    }

    return dst;
}

/****************************************************************************/ /**
 * @brief  Word memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of words
 *
 * @return Destination pointer
 *
 *******************************************************************************/
__WEAK__ uint32_t *ATTR_TCM_SECTION arch_memcpy4(uint32_t *dst, const uint32_t *src, uint32_t n)
{
    const uint32_t *p = src;
    uint32_t *q = dst;

    while (n--) {
        *q++ = *p++;
    }

    return dst;
}

/****************************************************************************/ /**
 * @brief  Fast memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of bytes
 *
 * @return Destination pointer
 *
 *******************************************************************************/
__WEAK__ void *ATTR_TCM_SECTION arch_memcpy_fast(void *pdst, const void *psrc, uint32_t n)
{
    uint32_t left, done, i = 0;
    uint8_t *dst = (uint8_t *)pdst;
    uint8_t *src = (uint8_t *)psrc;

    if (((uint32_t)(uintptr_t)dst & 0x3) == 0 && ((uint32_t)(uintptr_t)src & 0x3) == 0) {
        arch_memcpy4((uint32_t *)dst, (const uint32_t *)src, n >> 2);
        left = n % 4;
        done = n - left;

        while (i < left) {
            dst[done + i] = src[done + i];
            i++;
        }
    } else {
        arch_memcpy(dst, src, n);
    }

    return dst;
}

/****************************************************************************/ /**
 * @brief  char memset
 *
 * @param  dst: Destination
 * @param  val: Value to set
 * @param  n: Count of char
 *
 * @return Destination pointer
 *
 *******************************************************************************/
__WEAK__ void *ATTR_TCM_SECTION arch_memset(void *s, uint8_t c, uint32_t n)
{
    uint8_t *p = (uint8_t *)s;

    while (n > 0) {
        *p++ = (uint8_t)c;
        --n;
    }

    return s;
}
/****************************************************************************/ /**
 * @brief  Word memset
 *
 * @param  dst: Destination
 * @param  val: Value to set
 * @param  n: Count of words
 *
 * @return Destination pointer
 *
 *******************************************************************************/
__WEAK__ uint32_t *ATTR_TCM_SECTION arch_memset4(uint32_t *dst, const uint32_t val, uint32_t n)
{
    uint32_t *q = dst;

    while (n--) {
        *q++ = val;
    }

    return dst;
}

/****************************************************************************/ /**
 * @brief  string compare
 *
 * @param  s1: string 1
 * @param  s2: string 2
 * @param  n: Count of chars
 *
 * @return compare result
 *
 *******************************************************************************/
__WEAK__ int ATTR_TCM_SECTION arch_memcmp(const void *s1, const void *s2, uint32_t n)
{
    const unsigned char *c1 = s1, *c2 = s2;
    int d = 0;

    while (n--) {
        d = (int)*c1++ - (int)*c2++;

        if (d) {
            break;
        }
    }

    return d;
}
#endif

void memcopy_to_fifo(void *fifo_addr, uint8_t *data, uint32_t length)
{
    uint8_t *p = (uint8_t *)fifo_addr;
    uint8_t *q = data;

    while (length--) {
        *p = *q++;
    }
}

void fifocopy_to_mem(void *fifo_addr, uint8_t *data, uint32_t length)
{
    uint8_t *p = (uint8_t *)fifo_addr;
    uint8_t *q = data;

    while (length--) {
        *q++ = *p;
    }
}

/****************************************************************************/ /**
 * @brief  get u64 first number 1 from right to left
 *
 * @param  val: target value
 * @param  bit: first 1 in bit
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
int arch_ffsll(uint64_t *val, uint32_t *bit)
{
    if (!*val) {
        return ERROR;
    }

    *bit = __builtin_ffsll(*val) - 1;
    *val &= ~((1ULL) << (*bit));
    return 0;
}

int arch_ctzll(uint64_t *val, uint32_t *bit)
{
    if (!*val)
        return -1;

    *bit = __builtin_ctzll(*val);
    *val &= ~((1ULL) << (*bit));
    return 0;
}

int arch_clzll(uint64_t *val, uint32_t *bit)
{
    if (!*val)
        return -1;

    *bit = __builtin_clzll(*val);
    *val &= ~((1ULL) << (*bit));
    return 0;
}

#ifdef DEBUG
/*******************************************************************************
* @brief  Reports the name of the source file and the source line number
*         where the CHECK_PARAM error has occurred.

* @param  file: Pointer to the source file name
* @param  line: assert_param error line source number

* @return None
*******************************************************************************/
void check_failed(uint8_t *file, uint32_t line)
{
    /* Infinite loop */
    while (1)
        ;
}
#endif /* DEBUG */

/*@} end of group DRIVER_Public_Functions */

/*@} end of group DRIVER_COMMON */

/*@} end of group BL602_Periph_Driver */
