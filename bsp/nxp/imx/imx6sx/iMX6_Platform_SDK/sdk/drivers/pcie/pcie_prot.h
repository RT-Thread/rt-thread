/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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

//! @addtogroup diag_pcie
//! @{

/*!
 * @file pcie_prot.h
 * @brief Interface for PCIE protocal
 */

#ifndef __PCIE_PROT__
#define __PCIE_PROT__

#include "sdk.h"

//! @brief PCIE configuration header(type0)
typedef struct {
    uint16_t vendor_id;
    uint16_t dev_id;

    uint16_t cmd;
    uint16_t status;

    uint8_t rev_id;
    uint8_t cls_id[3];

    uint8_t cache_line_size;
    uint8_t latency_timer;
    uint8_t hdr_type;
    uint8_t bist;

    uint32_t bar0;
    uint32_t bar1;
    uint32_t bar2;
    uint32_t bar3;
    uint32_t bar4;
    uint32_t bar5;
    uint32_t cardbus_cis_ptr;

    uint16_t subsys_vendor_id;
    uint16_t sybsys_id;

    uint32_t exp_rom_base;

    uint8_t cap_ptr;
    uint8_t rsv0[3];

    uint8_t rsv1[4];

    uint8_t interrupt_line;
    uint8_t interrupt_pin;
    uint8_t min_grant;
    uint8_t max_latency;
} __attribute__ ((packed)) pcie_cfg_hdr_type0_t, *pcie_cfg_hdr_type0_p;

//! @brief PCIE configuration header(type1)
typedef struct {
    uint16_t vendor_id;
    uint16_t dev_id;

    uint16_t cmd;
    uint16_t status;

    uint8_t rev_id;
    uint8_t cls_id[3];

    uint8_t cache_line_size;
    uint8_t latency_timer;
    uint8_t hdr_type;
    uint8_t bist;

    uint32_t bar0;
    uint32_t bar1;

    uint8_t primary_bus;
    uint8_t snd_pus;
    uint8_t sub_bus;
    uint8_t snd_latency_timer;

    uint8_t io_base;
    uint8_t io_limit;
    uint16_t snd_status;

    uint16_t mem_base;
    uint16_t mem_limit;

    uint16_t prefetch_mem_base;
    uint16_t prefetch_mem_limit;

    uint32_t prefetch_base_upper;
    uint32_t prefetch_limit_upper;

    uint8_t cap_ptr;
    uint8_t rsv0[3];

    uint32_t exp_rom_base;

    uint8_t interrupt_line;
    uint8_t interrupt_pin;
    uint16_t bridge_ctrl;
} __attribute__ ((packed)) pcie_cfg_hdr_type1_t, *pcie_cfg_hdr_type1_p;

//! @brief PCIE recource types 
typedef enum {
    RESOURCE_TYPE_IO,
    RESOURCE_TYPE_MEM,
    RESOURCE_TYPE_INIT,
} resource_type_e;

//! @brief PCIE BARs
typedef enum {
    PCIE_BAR_0,
    PCIE_BAR_1,
    PCIE_BAR_2,
    PCIE_BAR_3,
    PCIE_BAR_4,
    PCIE_BAR_5,
} pcie_bar_e;

//! @brief PCIE resource structure
typedef struct {
    pcie_bar_e bar;
    resource_type_e type;
    uint32_t bits;
    uint32_t base;
    uint32_t size;
    uint32_t is_mapped;
} pcie_resource_t, *pcie_resource_p;

////////////////////////////////////////////////////////////////////////////////
// API
///////////////////////////////////////////////////////////////////////////////

/*! 
 * @brief This function dump the PCIE configuration header 
 *
 * @param    header_base the base address of the configuration header to be dumped	
 *
 * @return   0 on success,
 *           -1 if failed
 */
int pcie_dump_cfg_header(uint32_t * header_base);

/*! 
 * @brief This function enumerate the PCIE endpoint's IO/memory recource 
 *
 * @param    header_base the base address of the configuration header to be enumerated
 * @param	 res:	the array to save the resources enumerated
 * @param	 num:	the number of the resources
 *
 * @return   0 on success,
 *           -1 if failed
 */
int pcie_enum_resources(uint32_t * header_base, pcie_resource_t res[], uint32_t * num);

/*! 
 * @brief This function configure the endpoint's BARs 
 *
 * @param    header_base the base address of the configuration header
 * @param	 bar:	the index of the BAR to be configured
 * @param	 base:	the base address to be written to the BAR
 * @param	 base_msk:	the mask of the base
 *
 * @return   the base addrss of the BAR
 */
uint32_t pcie_cfg_ep_bar(uint32_t header_base, uint32_t bar, uint32_t base, uint32_t base_msk);

#endif
