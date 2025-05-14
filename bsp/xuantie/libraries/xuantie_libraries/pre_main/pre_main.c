 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     pre_main.c
 * @brief    source file for the pre_main
 * @version  V1.0
 * @date     04. April 2024
 ******************************************************************************/
#include "pre_main.h"

/*
 *  The ranges of copy from/to are specified by following symbols
 *    __erodata: LMA of start of the section to copy from. Usually end of rodata
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
void section_data_copy(void)
{
    extern unsigned long __erodata;
    extern unsigned long __data_start__;
    extern unsigned long __data_end__;

    if (((unsigned long)&__erodata != (unsigned long)&__data_start__)) {
        unsigned long src_addr = (unsigned long)&__erodata;
        memcpy((void *)(&__data_start__), \
               (void *)src_addr, \
               (unsigned long)(&__data_end__) - (unsigned long)(&__data_start__));
    }
}

void section_ram_code_copy(void)
{
    extern unsigned long __erodata;
    extern unsigned long __data_start__;
    extern unsigned long __data_end__;
    extern unsigned long __ram_code_start__;
    extern unsigned long __ram_code_end__;

    if (((unsigned long)&__erodata != (unsigned long)&__data_start__)) {
        unsigned long src_addr = (unsigned long)&__erodata;
        src_addr += (unsigned long)(&__data_end__) - (unsigned long)(&__data_start__);
        memcpy((void *)(&__ram_code_start__), \
               (void *)src_addr, \
               (unsigned long)(&__ram_code_end__) - (unsigned long)(&__ram_code_start__));
    }
}

/*
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
void section_bss_clear(void)
{
    extern unsigned long __bss_start__;
    extern unsigned long __bss_end__;

    memset((void *)(&__bss_start__), \
           0, \
           (unsigned long)(&__bss_end__) - (unsigned long)(&__bss_start__));

}
