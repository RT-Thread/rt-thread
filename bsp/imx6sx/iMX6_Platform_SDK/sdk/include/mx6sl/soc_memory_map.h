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

#ifndef _SOC_MEMORY_MAP_H
#define _SOC_MEMORY_MAP_H

// NOTE: THIS FILE IS GOING AWAY. 
//
//       DEVELOPERS - PLEASE USE register/*.h MACROS TO ACCESS REGSITERS.
//



#define BAAD_STATUS     0xbaadbaad
#define GOOD_STATUS     0x900d900d

// CPU Memory Map
#define MMDC0_ARB_BASE_ADDR             0x80000000
#define MMDC0_ARB_END_ADDR              0xFFFFFFFF
#define MMDC1_ARB_BASE_ADDR             0xC0000000
#define MMDC1_ARB_END_ADDR              0xFFFFFFFF
#define OCRAM_ARB_BASE_ADDR             0x00900000
#define OCRAM_ARB_END_ADDR          0x0091FFFF
#define IRAM_BASE_ADDR                  OCRAM_ARB_BASE_ADDR

// Blocks connected via pl301periph
// s_e_N ports
#define ROMCP_ARB_BASE_ADDR             0x00000000
#define ROMCP_ARB_END_ADDR              0x00017FFF
#define BOOT_ROM_BASE_ADDR              ROMCP_ARB_BASE_ADDR
#define GPU_2D_ARB_BASE_ADDR            0x02200000
#define GPU_2D_ARB_END_ADDR             0x02203FFF
#define OPENVG_ARB_BASE_ADDR           0x02204000
#define OPENVG_ARB_END_ADDR            0x02207FFF
// GPV - PL301 configuration ports
#define GPV0_BASE_ADDR                  0x00B00000
#define GPV1_BASE_ADDR                  0x00C00000
#define GPV2_BASE_ADDR                  0x00D00000
// s_g_N ports
#define AIPS1_ARB_BASE_ADDR             0x02000000
#define AIPS1_ARB_END_ADDR              0x020FFFFF
#define AIPS2_ARB_BASE_ADDR             0x02100000
#define AIPS2_ARB_END_ADDR              0x021FFFFF
// #define SATA_ARB_BASE_ADDR              0x02200000
// #define SATA_ARB_END_ADDR               0x02203FFF
// #define OPENVG_ARB_BASE_ADDR            0x02204000
// #define OPENVG_ARB_END_ADDR             0x02207FFF
#define WEIM_ARB_BASE_ADDR              0x08000000
#define WEIM_ARB_END_ADDR               0x0FFFFFFF

// CoreSight (ARM Debug)
// ***** TO UPDATE *****
#define DEBUG_ROM_BASE_ADDR             0x02140000
#define ETB_BASE_ADDR                   0x02141000
#define EXT_CTI_BASE_ADDR               0x02142000
#define TPIU_BASE_ADDR                  0x02143000
#define FUNNEL_BASE_ADDR                0x02144000
#define CORTEX_ROM_TABLE                0x0214F000
#define CORTEX_DEBUG_UNIT               0x02150000
#define CORE0_DEBUG_UNIT                0x02150000
#define PMU0_BASE_ADDR                  0x02151000
#define CORE1_DEBUG_UNIT                0x02152000
#define PMU1_BASE_ADDR                  0x02153000
#define CORE2_DEBUG_UNIT                0x02154000
#define PMU2_BASE_ADDR                  0x02155000
#define CORE3_DEBUG_UNIT                0x02156000
#define PMU3_BASE_ADDR                  0x02157000
#define CTI0_BASE_ADDR                  0x02158000
#define CTI1_BASE_ADDR                  0x02159000
#define CTI2_BASE_ADDR                  0x0215A000
#define CTI3_BASE_ADDR                  0x0215B000
#define PTM0_BASE_ADDR                  0x0215C000
#define PTM_BASE_ADDR                  0x0215C000
#define PTM1_BASE_ADDR                  0x0215D000
#define PTM2_BASE_ADDR                  0x0215E000
#define PTM3_BASE_ADDR                  0x0215F000
// *********************

// Legacy Defines
#define CSD0_DDR_BASE_ADDR              MMDC0_ARB_BASE_ADDR
#define CSD1_DDR_BASE_ADDR              0xC0000000
#define CS0_BASE_ADDR                   WEIM_ARB_BASE_ADDR
// Defines for Blocks connected via AIPS (SkyBlue)
#define AIPS_TZ1_BASE_ADDR              AIPS1_ARB_BASE_ADDR
#define AIPS_TZ2_BASE_ADDR              AIPS2_ARB_BASE_ADDR

//slots 0,7 of SDMA reserved, therefore left unused in IPMUX3
#define SPDIF_BASE_ADDR             (AIPS_TZ1_BASE_ADDR + 0x00004000)    // 0x02004000
#define ECSPI1_BASE_ADDR            (AIPS_TZ1_BASE_ADDR + 0x00008000)    // 0x02008000
#define ECSPI2_BASE_ADDR            (AIPS_TZ1_BASE_ADDR + 0x0000C000)    // 0x0200C000
#define ECSPI3_BASE_ADDR            (AIPS_TZ1_BASE_ADDR + 0x00010000)    // 0x02010000
#define ECSPI4_BASE_ADDR            (AIPS_TZ1_BASE_ADDR + 0x00014000)    // 0x02014000
#define UART5_BASE_ADDR             (AIPS_TZ1_BASE_ADDR + 0x00018000) 	 //slot 6
#define UART1_BASE_ADDR             (AIPS_TZ1_BASE_ADDR + 0x00020000)    // 0x02020000
#define UART2_BASE_ADDR             (AIPS_TZ1_BASE_ADDR + 0x00024000)    //slot 9
#define SSI1_BASE_ADDR              (AIPS_TZ1_BASE_ADDR + 0x00028000)    // 0x02028000
#define SSI2_BASE_ADDR              (AIPS_TZ1_BASE_ADDR + 0x0002C000)    // 0x0202C000
#define SSI3_BASE_ADDR              (AIPS_TZ1_BASE_ADDR + 0x00030000)    // 0x02030000
#define UART3_BASE_ADDR             (AIPS_TZ1_BASE_ADDR + 0x00034000) 	 //slot 13
#define UART4_BASE_ADDR             (AIPS_TZ1_BASE_ADDR + 0x00038000) 	 //slot 14
#define SPBA_BASE_ADDR              (AIPS_TZ1_BASE_ADDR + 0x0003C000)    // 0x0203C000     haku
#define VPU_BASE_ADDR               (AIPS_TZ1_BASE_ADDR + 0x00040000)    //slot 33, global en[1], til 0x7BFFF

// AIPS_TZ#1- On Platform
#define AIPS1_ON_BASE_ADDR          (AIPS_TZ1_BASE_ADDR + 0x0007C000)    // 0x0207C000

// AIPS_TZ#1- Off Platform
#define AIPS1_OFF_BASE_ADDR         (AIPS_TZ1_BASE_ADDR + 0x00080000)    // 0x02080000
//#define USBOH3_BASE_ADDR              AIPS1_BASE_ADDR

#define PWM1_BASE_ADDR              (AIPS1_OFF_BASE_ADDR + 0x00000000)   // 0x02080000
#define PWM2_BASE_ADDR              (AIPS1_OFF_BASE_ADDR + 0x00004000)   // 0x02084000
#define PWM3_BASE_ADDR              (AIPS1_OFF_BASE_ADDR + 0x00008000)   // 0x02088000
#define PWM4_BASE_ADDR              (AIPS1_OFF_BASE_ADDR + 0x0000C000)   // 0x0208C000
#define DBGMON_BASE_ADDR            (AIPS1_OFF_BASE_ADDR + 0x00010000)   // 0x02090000
#define QOSC_BASE_ADDR              (AIPS1_OFF_BASE_ADDR + 0x00014000)   // 0x02094000
#define GPT_BASE_ADDR               (AIPS1_OFF_BASE_ADDR + 0x00018000)   // 0x02098000
#define GPIO1_BASE_ADDR             (AIPS1_OFF_BASE_ADDR + 0x0001C000)   // 0x0209C000
#define GPIO2_BASE_ADDR             (AIPS1_OFF_BASE_ADDR + 0x00020000)   // 0x020A0000
#define GPIO3_BASE_ADDR             (AIPS1_OFF_BASE_ADDR + 0x00024000)   // 0x020A4000
#define GPIO4_BASE_ADDR             (AIPS1_OFF_BASE_ADDR + 0x00028000)   // 0x020A8000
#define GPIO5_BASE_ADDR             (AIPS1_OFF_BASE_ADDR + 0x0002C000)   // 0x020AC000
#define GPIO6_BASE_ADDR             (AIPS1_OFF_BASE_ADDR + 0x00030000)
#define GPIO7_BASE_ADDR             (AIPS1_OFF_BASE_ADDR + 0x00034000)
#define KPP_BASE_ADDR               (AIPS1_OFF_BASE_ADDR + 0x00038000)   // 0x020B8000
#define WDOG1_BASE_ADDR             (AIPS1_OFF_BASE_ADDR + 0x0003C000)   // 0x020BC000
#define WDOG2_BASE_ADDR             (AIPS1_OFF_BASE_ADDR + 0x00040000)   // 0x020C0000
#define CCM_BASE_ADDR               (AIPS1_OFF_BASE_ADDR + 0x00044000)   // 0x020C4000
#define ANATOP_BASE_ADDR            (AIPS1_OFF_BASE_ADDR + 0x00048000)   // 0x020C8000		same as CCM_ANALOG	above
#define SNVS_BASE_ADDR              (AIPS1_OFF_BASE_ADDR + 0x0004C000)   // 0x020CC000
#define EPIT1_BASE_ADDR             (AIPS1_OFF_BASE_ADDR + 0x00050000)   // 0x020D0000
#define EPIT2_BASE_ADDR             (AIPS1_OFF_BASE_ADDR + 0x00054000)   // 0x020D4000
#define SRC_BASE_ADDR               (AIPS1_OFF_BASE_ADDR + 0x00058000)   // 0x020D8000
#define GPC_BASE_ADDR               (AIPS1_OFF_BASE_ADDR + 0x0005C000)   // 0x020DC000		same as DVFS below
#define IOMUXC_BASE_ADDR            (AIPS1_OFF_BASE_ADDR + 0x00060000)   // 0x020E0000
#define CSI_BASE_ADDR               (AIPS1_OFF_BASE_ADDR + 0x00064000)   // 0x020E4000 (was DCIC1)
#define SPDC_BASE_ADDR              (AIPS1_OFF_BASE_ADDR + 0x00068000)   // 0x020E8000 (was DCIC2)
#define SDMA_BASE_ADDR              (AIPS1_OFF_BASE_ADDR + 0x0006C000)   // 0x020EC000
#define EPXP_BASE_ADDR              (AIPS1_OFF_BASE_ADDR + 0x00070000)   // 0x020F0000
#define SDMA_IPS_HOST_BASE_ADDR     SDMA_BASE_ADDR                   
#define EPDC_BASE_ADDR              (AIPS1_OFF_BASE_ADDR + 0x00074000)   // 0x020F4000
#define ELCDIF_BASE_ADDR            (AIPS1_OFF_BASE_ADDR + 0x00078000)   // 0x020F8000
#define DCP_BASE_ADDRESS            (AIPS1_OFF_BASE_ADDR + 0x0007C000)   // 0x020FC000

// AIPS_TZ#2- On Platform
#define AIPS2_ON_BASE_ADDR          (AIPS_TZ2_BASE_ADDR+0x0007C000)    // 0x0217C000

// AIPS_TZ#2- Off Platform
#define AIPS2_OFF_BASE_ADDR         (AIPS_TZ2_BASE_ADDR+0x00080000)    // 0x02180000

#define AIPS1_BASE_ADDR			AIPS1_ON_BASE_ADDR
#define AIPS2_BASE_ADDR			AIPS2_ON_BASE_ADDR

#define USBO2H_PL301_BASE_ADDR          (AIPS2_OFF_BASE_ADDR + 0x00000000)
#define USBO2H_USB_BASE_ADDR            (AIPS2_OFF_BASE_ADDR + 0x00004000)
#define ENET_BASE_ADDR              (AIPS2_OFF_BASE_ADDR + 0x00008000)   // 0x02188000
#define MSHC_BASE_ADDR                   (AIPS2_OFF_BASE_ADDR + 0x0000C000)
//For ESDHC became Usdhc, temporarily allowing both new and old names
#define USDHC1_BASE_ADDR            (AIPS2_OFF_BASE_ADDR + 0x00010000)   // 0x02190000
#define USDHC2_BASE_ADDR            (AIPS2_OFF_BASE_ADDR + 0x00014000)   // 0x02194000
#define USDHC3_BASE_ADDR            (AIPS2_OFF_BASE_ADDR + 0x00018000)   // 0x02198000
#define USDHC4_BASE_ADDR            (AIPS2_OFF_BASE_ADDR + 0x0001C000)   // 0x0219C000
#define I2C1_BASE_ADDR              (AIPS2_OFF_BASE_ADDR + 0x00020000)   // 0x021A0000
#define I2C2_BASE_ADDR              (AIPS2_OFF_BASE_ADDR + 0x00024000)   // 0x021A4000
#define I2C3_BASE_ADDR              (AIPS2_OFF_BASE_ADDR + 0x00028000)   // 0x021A8000
#define I2C4_BASE_ADDR              (AIPS2_OFF_BASE_ADDR + 0x00078000)
//AIPS2_OFF_BASE_ADDR
#define ROMCP_BASE_ADDR             (AIPS2_OFF_BASE_ADDR + 0x0002C000)   // 0x021AC000
#define MMDC_P0_BASE_ADDR           (AIPS2_OFF_BASE_ADDR + 0x00030000)   // 0x021B0000
#define RNGB_BASE_ADDR              (AIPS2_OFF_BASE_ADDR + 0x00034000)   // 0x021B4000
#define WEIM_BASE_ADDR              (AIPS2_OFF_BASE_ADDR + 0x00038000)   // 0x021B8000
#define OCOTP_BASE_ADDR             (AIPS2_OFF_BASE_ADDR + 0x0003C000)   // 0x021BC000
#define CSU_BASE_ADDR               (AIPS2_OFF_BASE_ADDR + 0x00040000)   // 0x021C0000
#define IP2APB_PERFMON1_BASE_ADDR   (AIPS2_OFF_BASE_ADDR + 0x00044000)   // 0x021C4000
#define IP2APB_PERFMON2_BASE_ADDR   (AIPS2_OFF_BASE_ADDR + 0x00048000)   // 0x021C8000
#define IP2APB_TZASC1_BASE_ADDR     (AIPS2_OFF_BASE_ADDR + 0x00050000)   // 0x021D0000
#define AUDMUX_BASE_ADDR            (AIPS2_OFF_BASE_ADDR + 0x00058000)   // 0x021D8000
#define IP2APB_USBPHY1_BASE_ADDR    (AIPS2_OFF_BASE_ADDR + 0x00078000)
#define IP2APB_USBPHY2_BASE_ADDR    (AIPS2_OFF_BASE_ADDR + 0x0007C000)

#endif //_SOC_MEMORY_MAP_H
