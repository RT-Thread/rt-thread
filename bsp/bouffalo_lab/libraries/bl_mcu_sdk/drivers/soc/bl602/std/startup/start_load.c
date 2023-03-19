/**
 * @file start_load.c
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

#include <stdint.h>

#define __STARTUP_CLEAR_BSS 1

/*----------------------------------------------------------------------------
  Linker generated Symbols
 *----------------------------------------------------------------------------*/
extern uint32_t __itcm_load_addr;
extern uint32_t __dtcm_load_addr;
extern uint32_t __system_ram_load_addr;
extern uint32_t __ram_load_addr;

extern uint32_t __text_code_start__;
extern uint32_t __text_code_end__;
extern uint32_t __tcm_code_start__;
extern uint32_t __tcm_code_end__;
extern uint32_t __tcm_data_start__;
extern uint32_t __tcm_data_end__;
extern uint32_t __ram_data_start__;
extern uint32_t __ram_data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __noinit_data_start__;
extern uint32_t __noinit_data_end__;

extern uint32_t __StackTop;
extern uint32_t __StackLimit;
extern uint32_t __HeapBase;
extern uint32_t __HeapLimit;

//extern uint32_t __copy_table_start__;
//extern uint32_t __copy_table_end__;
//extern uint32_t __zero_table_start__;
//extern uint32_t __zero_table_end__;

void start_load(void)
{
    uint32_t *pSrc, *pDest;
    uint32_t *pTable __attribute__((unused));

    /* Copy ITCM code */
    pSrc = &__itcm_load_addr;
    pDest = &__tcm_code_start__;

    for (; pDest < &__tcm_code_end__;) {
        *pDest++ = *pSrc++;
    }

    /* Copy DTCM code */
    pSrc = &__dtcm_load_addr;
    pDest = &__tcm_data_start__;

    for (; pDest < &__tcm_data_end__;) {
        *pDest++ = *pSrc++;
    }

    /* BF Add OCARAM data copy */
    pSrc = &__ram_load_addr;
    pDest = &__ram_data_start__;

    for (; pDest < &__ram_data_end__;) {
        *pDest++ = *pSrc++;
    }

#ifdef __STARTUP_CLEAR_BSS
    /*  Single BSS section scheme.
     *
     *  The BSS section is specified by following symbols
     *    __bss_start__: start of the BSS section.
     *    __bss_end__: end of the BSS section.
     *
     *  Both addresses must be aligned to 4 bytes boundary.
     */
    pDest = &__bss_start__;

    for (; pDest < &__bss_end__;) {
        *pDest++ = 0ul;
    }

#endif
}