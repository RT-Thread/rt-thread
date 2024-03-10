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

#include "sdk.h"
#include "pcie/pcie_common.h"
#include "pcie/pcie_prot.h"

#define PCIE_VERIFY_PATTERN		0x5a

extern int pcie_init(pcie_dm_mode_e dev_mode);

extern void (*pcie_func_clk_setup) (uint32_t enable);
extern void (*pcie_func_pwr_setup) (uint32_t enable);
extern void (*pcie_func_card_pwr_setup) (uint32_t enable);
extern void (*pcie_func_card_ref_clk_setup) (uint32_t enable);
extern void (*pcie_func_card_rst) (void);

extern void pcie_clk_setup(uint32_t enable);
extern void pcie_card_pwr_setup(uint32_t enable);
extern void pcie_enable_extrn_100mhz_clk(uint32_t enable);
extern void pcie_enable_extrn_125mhz_clk(uint32_t enable);
extern void pcie_card_rst(void);

pcie_resource_t ep1_resources[6];
uint32_t res_num = 6;

int pcie_test(void)
{
    uint32_t i;
    uint8_t ch;

    printf("\n---- Running PCIE test. Type 'y' to continue.\n");

    do {
        ch = getchar();
    } while (ch == (uint8_t) 0xFF);

    if ((ch != 'Y') && (ch != 'y')) {
        printf("\nTest exit.\n");
        return -1;
    }

    printf("Please make sure the mini pcie card inserted. Type\"y\" or \"Y\" to confirm.\n");
    do {
        ch = getchar();
    } while (ch == (uint8_t) 0xFF);

    if ((ch != 'Y') && (ch != 'y')) {
        printf("\nTest exit.\n");
        return -1;
    }

    pcie_func_clk_setup = pcie_clk_setup;
    pcie_func_card_rst = pcie_card_rst;
    pcie_func_card_ref_clk_setup = pcie_enable_extrn_100mhz_clk;
    pcie_func_card_pwr_setup = pcie_card_pwr_setup;

    if (0 != pcie_init(PCIE_DM_MODE_RC)) {
        printf("PCIE init failed.\n");
        return -1;
    } else {
        printf("PCIE init succeed. Link setup\n");
    }

    printf("Remap the endpoint's configuration space to arm's memory space.\n");
    uint32_t cfg_hdr_base = pcie_map_space(PCIE_IATU_VIEWPORT_0,
                                           TLP_TYPE_CfgRdWr0,
                                           PCIE_ARB_BASE_ADDR, 0, SZ_64K);

    printf("Dump the endpoint's configuration header.\n");
    pcie_dump_cfg_header((uint32_t *) cfg_hdr_base);

    pcie_enum_resources((uint32_t *) cfg_hdr_base, ep1_resources, &res_num);
    if (0 == res_num) {
        printf("Enumerate endpoint's resource failed.\n");
        return -1;
    }

    printf("List the endpoint's resource requirement.\n");
    for (i = 0; i < res_num; i++) {
        printf("\tResourse%d\t", i);
        if (ep1_resources[i].type == RESOURCE_TYPE_IO) {
            printf("IO\t");
        } else {
            printf("Memory\t");
        }
        printf("%dbyte\t", ep1_resources[i].size);
        printf("%dbits\t", ep1_resources[i].bits);
        printf("\n");
    }

#if 0
    printf("Dump the endpoint's configuration header.\n");
    pcie_dump_cfg_header((uint32_t *) cfg_hdr_base);
#endif

    printf("Allocate resources for the endpoint.\n");
    uint32_t viewport = PCIE_IATU_VIEWPORT_1;
    uint32_t ep_io_base = 0, ep_mem_base = 0, base_cpu_side = PCIE_ARB_BASE_ADDR + SZ_64K;
    uint32_t tlp_type = 0, size, bar, *ep_base = NULL;
    char *str_space[] = { "IO", "Memory" };
    char *str = 0;

    for (i = 0; (i < res_num) && (viewport < PCIE_IATU_VIEWPORT_MAX); i++, viewport++) {
        bar = ep1_resources[i].bar;
        size = ep1_resources[i].size;
        if (ep1_resources[i].type == RESOURCE_TYPE_IO) {
            ep_base = &ep_io_base;
            tlp_type = TLP_TYPE_IORdWr;
            str = str_space[0];
            base_cpu_side = (base_cpu_side + 0xFF) & (~0xFF);
            *ep_base = (*ep_base + 0xFF) & (~0xFF);
        } else if (ep1_resources[i].type == RESOURCE_TYPE_MEM) {
            ep_base = &ep_mem_base;
            tlp_type = TLP_TYPE_MemRdWr;
            str = str_space[1];
            // 64Kbytes aligned on cpu side.
            base_cpu_side = (base_cpu_side + 0xFFFF) & (~0xFFFF);
            *ep_base = (*ep_base + 0xFFFF) & (~0xFFFF);
        }

        /*
         * Actually, all the IO spaces can be mapped using one iATU, and all MEM spaces using another one.
         */
        printf("Map endpoint's bar%d %s space %d byte to CPU memory base 0x%x.\n ", bar, str, size,
               base_cpu_side);
        pcie_cfg_ep_bar(cfg_hdr_base, bar, *ep_base, ~(size - 1));
        ep1_resources[i].base = pcie_map_space(viewport, tlp_type, base_cpu_side, *ep_base, size);
        ep1_resources[i].is_mapped = 1;
        *ep_base += size;
        base_cpu_side += size;
    }

#if 0
    printf("Dump the endpoint's configuration header.\n");
    pcie_dump_cfg_header((uint32_t *) cfg_hdr_base);
#endif

    printf("Accessing every IO/Mem space one by one.\n");
    //All the space should support 32bit read access.
    volatile uint32_t *space_ptr = NULL;

    for (i = 0; i < res_num; i++) {
        if (ep1_resources[i].is_mapped) {
            space_ptr = (volatile uint32_t *)ep1_resources[i].base;
            printf("Dump the first word of Resource%d as : 0x%08x\n", i, *space_ptr);
        }
    }

    return 0;
}
