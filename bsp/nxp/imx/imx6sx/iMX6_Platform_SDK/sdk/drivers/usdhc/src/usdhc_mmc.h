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

#ifndef __USDHC_MMC_H__
#define __USDHC_MMC_H__

#define MMC_SWITCH_SET_BUS_WIDTH 0x3B70000
#define MMC_SWITCH_SET_BOOT_BUS_WIDTH 0x3B10000
#define MMC_SWITCH_SET_BOOT_PARTITION 0x3B30000

#define MMC_SWITCH_SET_BOOT_ACK 0x01B34000
#define MMC_SWITCH_CLR_BOOT_ACK 0x02B34000

#define MMC_SWITCH_SET_PARAM_SHIFT 0x8

/* boot bus width */
#define BBW_1BIT 	(0x0<<0)
#define BBW_4BIT 	(0x1<<0)
#define BBW_8BIT 	(0x2<<0)
#define BBW_SAVE 	(0x1<<2)
#define BBW_DDR 	(0x2<<3)

#define BBW_DDR_MASK	(0x3<<3)
#define BBW_BUS_MASK	(0x3<<0)
#define BBW_SAV_MASK	(0x1<<2)

/* boot partition */
#define BP_USER		(0x7<<3)
#define BP_BT1		(0x1<<3)
#define BP_BT2		(0x2<<3)
#define BT_ACK		(0x1<<6)
#define BP_MASK		(0x7<<3)

//#define BP_SHIFT 3
//#define ACK_SHIFT 6

/* offset in esd */
#define MMC_ESD_OFF_PRT_CFG 179
#define MMC_ESD_OFF_BT_BW 177

enum mmc_ver_e {
    MMC_CARD_3_X,
    MMC_CARD_4_X,
    MMC_CARD_4_4,
    MMC_CARD_INV
};

struct csd_struct {
    uint32_t response[4];

    uint8_t ssv;                //system spec version
    uint8_t csds;               //CSD structure
};

#endif
