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
#include "soc_memory_map.h"

//! @brief dcd data, list of (register, value) pairs to initialize ddr
uint8_t input_dcd[] __attribute__ ((section (".dcd_data")))= {
    /*DDR clk to 400MHz*/
    /*CCM_BASE_ADDR = 0x020c4000*/
    EXPAND_UINT32(CCM_BASE_ADDR + 0x018), EXPAND_UINT32(0x00260324),
    /*========================================================================*/
    /* IOMUX*/
    /*========================================================================*/
    /* Megrez note: IOMUX configs specify absolute addr in Arik IOMUXC. Changes to
       Megrez addr.*/
    /* Megrez note: Good chance that drive strength change is required. to change
       them all by editing the LSB value "38"-> ""30" or "28"*/
    /* Megrez note: Timing also can be tweaked by drive strength values. It is
       mainly by giving SDCLk and SDQS different values than the sampled signals*/
    /*IOMUXC_BASE_ADDR = 0x020e0000*/
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS0*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x344), EXPAND_UINT32(0x00003030),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS1*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x348), EXPAND_UINT32(0x00003030),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS2*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x34c), EXPAND_UINT32(0x00003030),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_SDQS3*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x350), EXPAND_UINT32(0x00003030),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_DQM0*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x30c), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_DQM1*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x310), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_DQM2*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x314), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_DQM3*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x318), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_CAS*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x300), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_RAS*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x31c), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_SDCLK_0*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x338), EXPAND_UINT32(0x00000028),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_RESET*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x320), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_SDBA2 - DSE can be configured using Group Control
      Register: IOMUXC_SW_PAD_CTL_GRP_CTLDS*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x32c), EXPAND_UINT32(0x00000000),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_SDODT0*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x33c), EXPAND_UINT32(0x00000008),
    /*IOMUXC_SW_PAD_CTL_PAD_DRAM_SDODT1*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x340), EXPAND_UINT32(0x00000008),
    /*IOMUXC_SW_PAD_CTL_GRP_B0DS*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x5c4), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_GRP_B1DS*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x5cc), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_GRP_B2DS*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x5d4), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_GRP_B3DS*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x5d8), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_GRP_ADDDS*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x5ac), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_GRP_CTLDS*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x5c8), EXPAND_UINT32(0x00000030),
    /*IOMUXC_SW_PAD_CTL_GRP_DDRMODE_CTL*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x5b0), EXPAND_UINT32(0x00020000),
    /*IOMUXC_SW_PAD_CTL_GRP_DDRPKE*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x5b4), EXPAND_UINT32(0x00000000),
    /*IOMUXC_SW_PAD_CTL_GRP_DDRMODE*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x5c0), EXPAND_UINT32(0x00020000),
    /*IOMUXC_SW_PAD_CTL_GRP_DDR_TYPE*/
    EXPAND_UINT32(IOMUXC_BASE_ADDR + 0x5d0), EXPAND_UINT32(0x00080000),
    /*========================================================================*/
    /* DDR Controller Registers*/
    /*========================================================================*/
    /* Manufacturer:	Samsung*/
    /* Device Part Number:	K4P8G304EB-AGC1*/
    /* Clock Freq.: 	400MMHz*/
    /* MMDC channels:       MMDC0*/
    /* Density per CS in Gb: 	512M*/
    /* Chip Selects used:	2*/
    /* Number of Banks:	8*/
    /* Row address:    	14*/
    /* Column address: 	10*/
    /* Data bus width	32*/
    /*========================================================================*/
    /*MMDC_P0_BASE_ADDR = 0x021b0000*/
    /*MMDC0_MDSCR, set the Configuration request bit during MMDC set up*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x01c), EXPAND_UINT32(0x00008000),
    /*setmem /32      0x021b085c = 0x1b5f01ff*/
    /*LPDDR2 ZQ params*/
    /*LPDDR2 ZQ params*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x85c), EXPAND_UINT32(0x1b4700c7),
    /*========================================================================*/
    /* Calibration setup.*/
    /**/
    /*========================================================================*/
    /*DDR_PHY_P0_MPZQHWCTRL, enable on time ZQ calibration*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x800), EXPAND_UINT32(0xa1390003),
    /* Megrez note: If entire word fails, CA bus might be involved. Try changing
       this:*/
    /*ca bus abs delay*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x890), EXPAND_UINT32(0x00300000),
    /* values of 20,40,50,60,7f tried. no difference seen*/
    /* Megrez note: This is also for CA bus. A bit-bit fine tuning.*/
    /*setmem /32	0x021b48bc =	0x00055555*/
    /*DDR_PHY_P1_MPWRCADL*/
    /*frc_msr.*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x8b8), EXPAND_UINT32(0x00000800),
    /*DDR_PHY_P0_MPREDQBY0DL3*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x81c), EXPAND_UINT32(0x33333333),
    /*DDR_PHY_P0_MPREDQBY1DL3*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x820), EXPAND_UINT32(0x33333333),
    /*DDR_PHY_P0_MPREDQBY2DL3*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x824), EXPAND_UINT32(0x33333333),
    /*DDR_PHY_P0_MPREDQBY3DL3*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x828), EXPAND_UINT32(0x33333333),
    /*write delayes:*/
    /*all byte 0 data & dm delayed by 3*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x82c), EXPAND_UINT32(0xf3333333),
    /*all byte 1 data & dm delayed by 3*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x830), EXPAND_UINT32(0xf3333333),
    /*all byte 2 data & dm delayed by 3*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x834), EXPAND_UINT32(0xf3333333),
    /*all byte 3 data & dm delayed by 3*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x838), EXPAND_UINT32(0xf3333333),
    /* Read and write data delay, per byte.*/
    /* For optimized DDR operation it is recommended to run mmdc_calibration on your
       board, and replace 4 delay register assigns with resulted values*/
    /* Note:*/
    /* a. DQS gating is not relevant for LPDDR2. DSQ gating calibration section
       should be skipped, or the write/read calibration comming after that will
       stall*/
    /* b. The calibration code that runs for both MMDC0 & MMDC1 should be used.*/
    /*it is strongly recommended to run calibration on your board, and replace
      bellow values:*/
    /* Megrez note: New set of values is required for the following 2 delay
       registers. Try running calibration code as in Arik APN.*/
    /*Read calibration*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x848), EXPAND_UINT32(0x4241444a),
    /*Write calibration*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x850), EXPAND_UINT32(0x3030312b),
    /*dqs gating dis*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x83c), EXPAND_UINT32(0x20000000),
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x840), EXPAND_UINT32(0x00000000),
    /* Megrez note: Try enabling and changing the clock delay, as part of the
       calibration:*/
    /*setmem /32 0x021b0858 = 0xa00*/
    /*clk delay*/
    /*fine tune duty cyc to low*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x8c0), EXPAND_UINT32(0x24911492),
    /*frc_msr*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x8b8), EXPAND_UINT32(0x00000800),
    /*========================================================================*/
    /* Calibration setup end*/
    /*========================================================================*/
    /* Channel0 - startng address 0x80000000*/
    /*setmem /32	0x021b000c =	0x3f436133*/
    /* MMDC0_MDCFG0*/
    /*MMDC0_MDCFG0*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x00c), EXPAND_UINT32(0x33374133),
    /*MMDC0_MDPDC - where is tCKSRX and tCKSRE defined in LPDDR2 data sheet?????*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x004), EXPAND_UINT32(0x00020024),
    /*MMDC0_MDCFG1*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x010), EXPAND_UINT32(0x00100A82),
    /*MMDC0_MDCFG2*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x014), EXPAND_UINT32(0x00000093),
    /*MMDC0_MDMISC. RALAT=3. Try increasing RALAT if case of failures at higher DDR
      freq*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x018), EXPAND_UINT32(0x00001688),
    /*MMDC0_MDRWD;*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x02c), EXPAND_UINT32(0x0f9f26d2),
    /*MMDC0_MDOR*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x030), EXPAND_UINT32(0x0000020e),
    /*setmem /32	0x021b0038 =	0x001a099a*/
    /* MMDC0_MDCFG3LP*/
    /*MMDC0_MDCFG3LP*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x038), EXPAND_UINT32(0x00190778),
    /*MMDC0_MDOTC*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x008), EXPAND_UINT32(0x00000000),
    /*CS0_END = 0x8fffffff*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x040), EXPAND_UINT32(0x0000004f),
    /*MMDC0_MDCTL*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x000), EXPAND_UINT32(0xc3110000),
    /* Channel0 : Configure DDR device:*/
    /* Megrez note: Device drive strength change might help, consult device/JEDEC
       for the values.*/
    /*MRW: BA=0 CS=0 MR_ADDR=63 MR_OP=0  //reset*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x01c), EXPAND_UINT32(0x003f8030),
    /*MRW: BA=0 CS=0 MR_ADDR=10 MR_OP=ff /zq*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x01c), EXPAND_UINT32(0xff0a8030),
    /*MRW: BA=0 CS=0 MR_ADDR=1  MR_OP=c2*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x01c), EXPAND_UINT32(0x82018030),
    /*MRW: BA=0 CS=0 MR_ADDR=2  MR_OP=4. tcl=6, tcwl=3*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x01c), EXPAND_UINT32(0x04028030),
    /*MRW: BA=0 CS=0 MR_ADDR=3  MR_OP=2.drive=240/6*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x01c), EXPAND_UINT32(0x02038030),
    /* Need to comment out MRW reset command to CS1 - investigating this*/
    /* Also, adding delays before and after this makes no difference*/
    /*setmem /32 0x021b001c = 0x003f8038*/
    /* MRW: BA=0 CS=1 MR_ADDR=63 MR_OP=0*/
    /*reset*/
    /*MRW: BA=0 CS=1 MR_ADDR=10 MR_OP=ff*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x01c), EXPAND_UINT32(0xff0a8038),
    /*MRW: BA=0 CS=1 MR_ADDR=1  MR_OP=c2*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x01c), EXPAND_UINT32(0x82018038),
    /*MRW: BA=0 CS=1 MR_ADDR=2  MR_OP=4. tcl=6, tcwl=3*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x01c), EXPAND_UINT32(0x04028038),
    /*MRW: BA=0 CS=1 MR_ADDR=3  MR_OP=2.drive=240/6*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x01c), EXPAND_UINT32(0x02038038),
    /*######################################################*/
    /*final DDR setup, before operation start:*/
    /*DDR_PHY_P0_MPZQHWCTRL, enable automatic ZQ calibration*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x800), EXPAND_UINT32(0xa1310003),
    /*MMDC0_MDREF*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x020), EXPAND_UINT32(0x00001800),
    /*DDR_PHY_P0_MPODTCTRL*/
    /*setmem /32	0x021b0818 =	0*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x818), EXPAND_UINT32(0x00000000),
    /*DDR_PHY_P0_MPMUR0, frc_msr*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x8b8), EXPAND_UINT32(0x00000800),
    /*MMDC0_MDPDC now SDCTL power down enabled*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x004), EXPAND_UINT32(0x00025564),
    /*MMDC0_MAPSR ADOPT power down enabled*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x404), EXPAND_UINT32(0x00011006),
    /*MMDC0_MDSCR, clear this register (especially the configuration bit as
      initialization is complete),*/
    EXPAND_UINT32(MMDC_P0_BASE_ADDR + 0x01c), EXPAND_UINT32(0x00000000),
};

//! @brief HAB command write data header, with tag, 
//!        size of dcd data with hdr, 
//!        parameter field (size of register value and flag)
uint8_t input_dcd_wrt_cmd[] __attribute__ ((section (".dcd_wrt_cmd")))= {
    HAB_CMD_WRT_DAT, 
    EXPAND_UINT16(sizeof(input_dcd) + HDR_BYTES),
    WRT_DAT_PAR(0, HAB_DATA_WIDTH_WORD) //!< flag 0, width 4
};

//! @brief HAB dcd header with dcd tag, size of entire dcd and version.
uint8_t input_dcd_hdr[] __attribute__ ((section (".dcd_hdr")))= {
    HAB_TAG_DCD, 
    EXPAND_UINT16(sizeof(input_dcd) + sizeof(input_dcd_wrt_cmd) + HDR_BYTES),
    HAB_VER(4,0)
};
