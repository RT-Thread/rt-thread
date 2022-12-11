/*
 * Copyright (C) 2020 ETH Zurich and University of Bologna
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Description: SoC configuration registers (apb_soc_ctrl)
 * Authors: Germain Haugou (germain.haugou@iis.ee.ethz.ch)
 *          Robert Balas (balasr@iis.ee.ethz.ch)
 */

#ifndef HAL_INCLUDE_HAL_APB_SOC_H_
#define HAL_INCLUDE_HAL_APB_SOC_H_

#define APB_SOC_BOOT_OTHER    0
#define APB_SOC_BOOT_JTAG     1
#define APB_SOC_BOOT_SPI      2
#define APB_SOC_BOOT_ROM      3
#define APB_SOC_BOOT_PRELOAD  4
#define APB_SOC_BOOT_HYPER    5
#define APB_SOC_BOOT_SPIM     6
#define APB_SOC_BOOT_SPIM_QPI 7

#define APB_SOC_PLT_OTHER   0
#define APB_SOC_PLT_FPGA    1
#define APB_SOC_PLT_RTL     2
#define APB_SOC_PLT_VP      3
#define APB_SOC_PLT_CHIP    4

//PADs configuration is made of 8bits out of which only the first 6 are used
//bit0    enable pull UP
//bit1    enable pull DOWN
//bit2    enable ST
//bit3    enable SlewRate Limit
//bit4..5 Driving Strength
//bit6..7 not used

#define APB_SOC_BOOTADDR_OFFSET   0x04
#define APB_SOC_INFO_OFFSET       0x00 //contains number of cores [31:16] and clusters [15:0]
#define APB_SOC_INFOEXTD_OFFSET   0x04 //not used at the moment
#define APB_SOC_NOTUSED0_OFFSET   0x08 //not used at the moment
#define APB_SOC_CLUSTER_ISOLATE_OFFSET   0x0C //not used at the moment

#define	APB_SOC_PADFUN0_OFFSET	  0x10
#define	APB_SOC_PADCFG0_OFFSET	  0x20

#define APB_SOC_PADFUN_OFFSET(g)   (APB_SOC_PADFUN0_OFFSET+(g)*4) //sets the mux for pins  g*16+0 (bits [1:0]) to g*16+15 (bits [31:30])
#define APB_SOC_PADFUN_NO(pad)     ((pad) >> 4)
#define APB_SOC_PADFUN_PAD(padfun) ((padfun)*16)
#define APB_SOC_PADFUN_SIZE        2
#define ARCHI_APB_SOC_PADFUN_NB          4
#define APB_SOC_PADFUN_BIT(pad)    (((pad) & 0xF) << 1)

#define APB_SOC_PADCFG_OFFSET(g)   (APB_SOC_PADCFG0_OFFSET+(g)*4) //sets config for pin  g*4+0(bits [7:0]) to pin  g*4+3(bits [31:24])
#define APB_SOC_PADCFG_NO(pad)     ((pad) >> 2)
#define APB_SOC_PADCFG_PAD(padfun) ((padfun)*4)
#define APB_SOC_PADCFG_SIZE        8
#define APB_SOC_PADCFG_BIT(pad)    (((pad) & 0x3) << 3)

#define APB_SOC_PWRCMD_OFFSET     0x60 //change power mode(not funtional yet)
#define APB_SOC_PWRCFG_OFFSET     0x64 //configures power modes(not funtional yet)
#define APB_SOC_PWRREG_OFFSET     0x68 //32 bit GP register used by power pngmt routines to see if is hard or cold reboot
#define APB_SOC_BUSY_OFFSET       0x6C //not used at the moment
#define APB_SOC_MMARGIN_OFFSET    0x70 //memory margin pins(not used at the moment)
#define APB_SOC_JTAG_REG          0x74 // R/W register for interaction with the the chip environment
#define APB_SOC_L2_SLEEP_OFFSET   0x78 //memory margin pins(not used at the moment)
#define APB_SOC_NOTUSED3_OFFSET   0x7C //not used at the moment
#define APB_SOC_CLKDIV0_OFFSET    0x80 //soc clock divider(to be removed)
#define APB_SOC_CLKDIV1_OFFSET    0x84 //cluster clock divider(to be removed)
#define APB_SOC_CLKDIV2_OFFSET    0x88 //not used at the moment
#define APB_SOC_CLKDIV3_OFFSET    0x8C //not used at the moment
#define APB_SOC_CLKDIV4_OFFSET    0x90 //not used at the moment
#define APB_SOC_NOTUSED4_OFFSET   0x94 //not used at the moment
#define APB_SOC_NOTUSED5_OFFSET   0x98 //not used at the moment
#define APB_SOC_NOTUSED6_OFFSET   0x9C //not used at the moment
#define APB_SOC_CORESTATUS_OFFSET 0xA0 //32bit GP register to be used during testing to return EOC(bit[31]) and status(bit[30:0])
#define APB_SOC_CORESTATUS_RO_OFFSET 0xC0 //32bit GP register to be used during testing to return EOC(bit[31]) and status(bit[30:0])
#define APB_SOC_PADS_CONFIG       0xC4

#define APB_SOC_PADS_CONFIG_BOOTSEL_BIT 0

#define APB_SOC_JTAG_REG_EXT_BIT   8
#define APB_SOC_JTAG_REG_EXT_WIDTH 4

#define APB_SOC_JTAG_REG_LOC_BIT   0
#define APB_SOC_JTAG_REG_LOC_WIDTH 4

#define APB_SOC_INFO_CORES_OFFSET    (APB_SOC_INFO_OFFSET + 2)
#define APB_SOC_INFO_CLUSTERS_OFFSET (APB_SOC_INFO_OFFSET)

#define APB_SOC_STATUS_EOC_BIT  31
#define APB_SOC_NB_CORE_BIT     16

#define APB_SOC_BYPASS_OFFSET   0x70

#define APB_SOC_BYPASS_CLOCK_GATE_BIT 10
#define APB_SOC_BYPASS_CLUSTER_STATE_BIT 3
#define APB_SOC_BYPASS_USER0_BIT       14
#define APB_SOC_BYPASS_USER1_BIT       15

#define APB_SOC_FLL_CTRL_OFFSET         0xD0
#define APB_SOC_CLKDIV_SOC_OFFSET       0xD4
#define APB_SOC_CLKDIV_CLUSTER_OFFSET   0xD8
#define APB_SOC_CLKDIV_PERIPH_OFFSET    0xDC

#define APB_SOC_FLL_CTRL_SOC_BIT        0
#define APB_SOC_FLL_CTRL_CLUSTER_BIT    1
#define APB_SOC_FLL_CTRL_PERIPH_BIT     2

#define APB_SOC_RTC_OFFSET     0x1D0

#endif /* HAL_INCLUDE_HAL_APB_SOC_H_ */
