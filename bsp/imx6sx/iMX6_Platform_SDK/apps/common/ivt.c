/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "hab_defines.h"

extern unsigned * _start_image_add;
extern unsigned * __start_boot_data;
extern unsigned * _image_size;

extern unsigned * __hab_data;

extern uint8_t input_dcd_hdr[];

extern void _start(void);

struct hab_ivt input_ivt __attribute__ ((section (".ivt"))) ={
    /** @ref hdr word with tag #HAB_TAG_IVT, length and HAB version fields
     *  (see @ref data)
     */
    IVT_HDR(sizeof(struct hab_ivt), HAB_VER(4, 0)),
    /** Absolute address of the first instruction to execute from the
     *  image
     */
    (hab_image_entry_f)_start,

    /** Reserved in this version of HAB: should be NULL. */
    NULL,
    /** Absolute address of the image DCD: may be NULL. */
    &input_dcd_hdr,
    /** Absolute address of the Boot Data: may be NULL, but not interpreted
     *  any further by HAB
     */
    &__start_boot_data,
    /** Absolute address of the IVT.*/
    (const void*) (&input_ivt),
    
    /** Absolute address of the image CSF.*/
    (const void*) &__hab_data,

    /** Reserved in this version of HAB: should be zero. */
    0
};

typedef struct {
    uint32_t start;            /**< Start address of the image */
    uint32_t size;             /**< Size of the image */
    uint32_t plugin;           /**< Plugin flag */
} boot_data_t;

boot_data_t bd __attribute__ ((section (".boot_data"))) ={
    (uint32_t) &_start_image_add,
    (uint32_t) &_image_size,
    0,
};

