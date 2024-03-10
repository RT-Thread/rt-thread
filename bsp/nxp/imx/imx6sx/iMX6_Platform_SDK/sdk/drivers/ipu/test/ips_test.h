/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file ips_test.h
 * @brief some definitions for the IPU test.
 * @ingroup diag_ipu
 */

#ifndef __IPS_TEST__
#define __IPS_TEST__

#include "sdk.h"
#include "ipu/ipu_common.h"

#define MEM_PRO_UNCACHEABLE
#define MEM_PRO_UNBUFFERABEL

/*This macro do nothing because the the mmu and cache has beed disabled*/
#define MEM_VIRTUAL_2_PHYSICAL(addr,size,pro)

typedef struct {
    const char *name;
     int32_t(*test) (ips_dev_panel_t *);
} ipu_test_t;

int32_t ips_display_test(ips_dev_panel_t * panel);
int32_t ips_csc_test(ips_dev_panel_t * panel);
int32_t ips_combiner_test(ips_dev_panel_t * panel);
int32_t ips_rotate_test(ips_dev_panel_t * panel);
int32_t ips_resize_test(ips_dev_panel_t * panel);

#endif
