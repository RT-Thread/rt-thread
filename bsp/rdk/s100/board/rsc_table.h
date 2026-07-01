/*
 * Copyright (c) 2014, Mentor Graphics Corporation
 * All rights reserved.
 *
 * Copyright (C) 2015 Xilinx, Inc.  All rights reserved.
 * Copyright (C) 2023, Horizon Robotics
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of Mentor Graphics Corporation nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* This file populates resource table for BM remote
 * for use by the Linux Master */
#ifndef HB_RSC_TABLE_H
#define HB_RSC_TABLE_H

#include <stddef.h>
#include <stdint.h>

struct fw_rsc_version_with_type {
    uint32_t typefw_rsc_version;
    uint8_t version[48];
    uint8_t compile_time[16];
    uint8_t git_hash_id[40];
};

enum fw_resource_type {
    RSC_CARVEOUT        = 0,
    RSC_DEVMEM      = 1,
    RSC_TRACE       = 2,
    RSC_VDEV        = 3,
    RSC_RPROC_MEM   = 4U,
    RSC_FW_CHKSUM   = 5U,
    RSC_VERSION     = 6U,
    RSC_LAST        = 7U,
    RSC_VENDOR_START    = 128,
    RSC_VENDOR_END      = 512,
};

struct fw_rsc_devmem_with_type {
    uint32_t typefw_rsc_devmem;
    uint32_t da;
    uint32_t pa;
    uint32_t len;
    uint32_t flags;
    uint32_t reserved;
    uint8_t name[32];
};

#define NO_RESOURCE_ENTRIES         (7U)

/* Resource table for the given remote */
struct remote_resource_table {
    uint32_t version;
    uint32_t num;
    uint32_t reserved[2];
    uint32_t offset[NO_RESOURCE_ENTRIES];
    struct fw_rsc_version_with_type fw_version; /*PRQA S ALL*/
    struct fw_rsc_devmem_with_type startup_devmem;
    struct fw_rsc_devmem_with_type flash_devmem;
    struct fw_rsc_devmem_with_type freertos_heap_devmem;
    struct fw_rsc_devmem_with_type log_devmem;
    struct fw_rsc_devmem_with_type scmi_devmem;
    struct fw_rsc_devmem_with_type atcm_devmem;
}__attribute__((packed, aligned(0x100)));

extern const struct remote_resource_table resources;

#endif /* RSC_TABLE_H_ */

