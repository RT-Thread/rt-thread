/*!
    \file    gd32h7xx_exmc.h
    \brief   definitions for the EXMC

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32H7XX_EXMC_H
#define GD32H7XX_EXMC_H

#include "gd32h7xx.h"

/* EXMC definitions */
#define EXMC                                EXMC_BASE                     /*!< EXMC register base address */

/* registers definitions */
/* NOR/PSRAM */
#define EXMC_SNCTL0                         REG32(EXMC + 0x00000000U)     /*!< EXMC SRAM/NOR flash control register for region0 */
#define EXMC_SNTCFG0                        REG32(EXMC + 0x00000004U)     /*!< EXMC SRAM/NOR flash timing configuration register for region0 */
#define EXMC_SNWTCFG0                       REG32(EXMC + 0x00000104U)     /*!< EXMC SRAM/NOR flash write timing configuration register for region0 */
#define EXMC_SNCTL1                         REG32(EXMC + 0x00000008U)     /*!< EXMC SRAM/NOR flash control register for region1 */
#define EXMC_SNTCFG1                        REG32(EXMC + 0x0000000CU)     /*!< EXMC SRAM/NOR flash timing configuration register for region1 */
#define EXMC_SNWTCFG1                       REG32(EXMC + 0x0000010CU)     /*!< EXMC SRAM/NOR flash write timing configuration register for region1 */
#define EXMC_SNCTL2                         REG32(EXMC + 0x00000010U)     /*!< EXMC SRAM/NOR flash control register for region2 */
#define EXMC_SNTCFG2                        REG32(EXMC + 0x00000014U)     /*!< EXMC SRAM/NOR flash timing configuration register for region2 */
#define EXMC_SNWTCFG2                       REG32(EXMC + 0x00000114U)     /*!< EXMC SRAM/NOR flash write timing configuration register for region2 */
#define EXMC_SNCTL3                         REG32(EXMC + 0x00000018U)     /*!< EXMC SRAM/NOR flash control register for region3 */
#define EXMC_SNTCFG3                        REG32(EXMC + 0x0000001CU)     /*!< EXMC SRAM/NOR flash timing configuration register for region3 */
#define EXMC_SNWTCFG3                       REG32(EXMC + 0x0000011CU)     /*!< EXMC SRAM/NOR flash write timing configuration register for region3 */

/* NAND */
#define EXMC_NCTL                           REG32(EXMC + 0x00000080U)     /*!< EXMC NAND control register */
#define EXMC_NINTEN                         REG32(EXMC + 0x00000084U)     /*!< EXMC NAND interrupt enable register */
#define EXMC_NCTCFG                         REG32(EXMC + 0x00000088U)     /*!< EXMC NAND common space timing configuration register */
#define EXMC_NATCFG                         REG32(EXMC + 0x0000008CU)     /*!< EXMC NAND attribute space timing configuration register */
#define EXMC_NECC                           REG32(EXMC + 0x00000094U)     /*!< EXMC NAND ECC register */

/* SDRAM */
#define EXMC_SDCTL0                         REG32(EXMC + 0x00000140U)     /*!< EXMC SDRAM control register for device0 */
#define EXMC_SDTCFG0                        REG32(EXMC + 0x00000148U)     /*!< EXMC SDRAM timing configuration register register for device0 */
#define EXMC_SDCTL1                         REG32(EXMC + 0x00000144U)     /*!< EXMC SDRAM control register for device1 */
#define EXMC_SDTCFG1                        REG32(EXMC + 0x0000014CU)     /*!< EXMC SDRAM timing configuration register register for device1 */
#define EXMC_SDCMD                          REG32(EXMC + 0x00000150U)     /*!< EXMC SDRAM command register */
#define EXMC_SDARI                          REG32(EXMC + 0x00000154U)     /*!< EXMC SDRAM auto-refresh interval register */
#define EXMC_SDSTAT                         REG32(EXMC + 0x00000158U)     /*!< EXMC SDRAM status register */
#define EXMC_SDRSCTL                        REG32(EXMC + 0x00000180U)     /*!< EXMC SDRAM read sample control register */

/* bits definitions */
/* EXMC_SNCTLx,x=0..3 */
#define EXMC_SNCTL_NRBKEN                   BIT(0)                        /*!< NOR region enable */
#define EXMC_SNCTL_NRMUX                    BIT(1)                        /*!< NOR region memory address/data multiplexing enable */
#define EXMC_SNCTL_NRTP                     BITS(2,3)                     /*!< NOR region memory type */
#define EXMC_SNCTL_NRW                      BITS(4,5)                     /*!< NOR region memory data bus width */
#define EXMC_SNCTL_NREN                     BIT(6)                        /*!< NOR flash access enable */
#define EXMC_SNCTL_SBRSTEN                  BIT(8)                        /*!< synchronous burst enable */
#define EXMC_SNCTL_NRWTPOL                  BIT(9)                        /*!< NWAIT signal polarity */
#define EXMC_SNCTL_NRWTCFG                  BIT(11)                       /*!< NWAIT signal configuration, only work in synchronous mode */
#define EXMC_SNCTL_WEN                      BIT(12)                       /*!< write enable */
#define EXMC_SNCTL_NRWTEN                   BIT(13)                       /*!< NWAIT signal enable */
#define EXMC_SNCTL_EXMODEN                  BIT(14)                       /*!< extended mode enable */
#define EXMC_SNCTL_ASYNCWTEN                BIT(15)                       /*!< asynchronous wait enable */
#define EXMC_SNCTL_CPS                      BITS(16,18)                   /*!< CRAM page size */
#define EXMC_SNCTL_SYNCWR                   BIT(19)                       /*!< synchronous write configuration */
#define EXMC_SNCTL_CCK                      BIT(20)                       /*!< consecutive clock configuration */
#define EXMC_SNCTL_BKREMAP                  BITS(24,25)                   /*!< bank remap */

/* EXMC_SNTCFGx,x=0..3 */
#define EXMC_SNTCFG_ASET                    BITS(0,3)                     /*!< asynchronous address setup time */
#define EXMC_SNTCFG_AHLD                    BITS(4,7)                     /*!< asynchronous address hold time */
#define EXMC_SNTCFG_DSET                    BITS(8,15)                    /*!< asynchronous data setup time */
#define EXMC_SNTCFG_BUSLAT                  BITS(16,19)                   /*!< bus latency */
#define EXMC_SNTCFG_CKDIV                   BITS(20,23)                   /*!< synchronous clock divide ratio */
#define EXMC_SNTCFG_DLAT                    BITS(24,27)                   /*!< synchronous data latency for NOR flash */
#define EXMC_SNTCFG_ASYNCMOD                BITS(28,29)                   /*!< asynchronous access mode */

/* EXMC_SNWTCFGx,x=0..3 */
#define EXMC_SNWTCFG_WASET                  BITS(0,3)                     /*!< asynchronous address setup time */
#define EXMC_SNWTCFG_WAHLD                  BITS(4,7)                     /*!< asynchronous address hold time */
#define EXMC_SNWTCFG_WDSET                  BITS(8,15)                    /*!< asynchronous data setup time */
#define EXMC_SNWTCFG_WBUSLAT                BITS(16,19)                   /*!< bus latency */
#define EXMC_SNWTCFG_WASYNCMOD              BITS(28,29)                   /*!< asynchronous access mode */

/* EXMC_NCTL */
#define EXMC_NCTL_NDWTEN                    BIT(1)                        /*!< wait function enable */
#define EXMC_NCTL_NDBKEN                    BIT(2)                        /*!< NAND bank enable */
#define EXMC_NCTL_NDW                       BITS(4,5)                     /*!< NAND bank memory data bus width */
#define EXMC_NCTL_ECCEN                     BIT(6)                        /*!< ECC enable */
#define EXMC_NCTL_CTR                       BITS(9,12)                    /*!< CLE to RE delay */
#define EXMC_NCTL_ATR                       BITS(13,16)                   /*!< ALE to RE delay */
#define EXMC_NCTL_ECCSZ                     BITS(17,19)                   /*!< ECC size */

/* EXMC_NINTEN */
#define EXMC_NINTEN_INTRS                   BIT(0)                        /*!< rising edge interrupt status bit */
#define EXMC_NINTEN_INTHS                   BIT(1)                        /*!< high-level interrupt status bit */
#define EXMC_NINTEN_INTFS                   BIT(2)                        /*!< falling edge interrupt status bit */
#define EXMC_NINTEN_INTREN                  BIT(3)                        /*!< rising edge detection interrupt enable bit */
#define EXMC_NINTEN_INTHEN                  BIT(4)                        /*!< high-level detection interrupt enable bit */
#define EXMC_NINTEN_INTFEN                  BIT(5)                        /*!< falling edge detection interrupt enable bit */
#define EXMC_NINTEN_FFEPT                   BIT(6)                        /*!< FIFO empty flag */

/* EXMC_NCTCFG */
#define EXMC_NCTCFG_COMSET                  BITS(0,7)                     /*!< common memory setup time */
#define EXMC_NCTCFG_COMWAIT                 BITS(8,15)                    /*!< common memory wait time */
#define EXMC_NCTCFG_COMHLD                  BITS(16,23)                   /*!< common memory hold time */
#define EXMC_NCTCFG_COMHIZ                  BITS(24,31)                   /*!< common memory data bus HiZ time */

/* EXMC_NATCFG */
#define EXMC_NATCFG_ATTSET                  BITS(0,7)                     /*!< attribute memory setup time */
#define EXMC_NATCFG_ATTWAIT                 BITS(8,15)                    /*!< attribute memory wait time */
#define EXMC_NATCFG_ATTHLD                  BITS(16,23)                   /*!< attribute memory hold time */
#define EXMC_NATCFG_ATTHIZ                  BITS(24,31)                   /*!< attribute memory data bus HiZ time */

/* EXMC_NECC */
#define EXMC_NECC_ECC                       BITS(0,31)                    /*!< ECC result */

/* EXMC_SDCTLx,(x=0,1) */
#define EXMC_SDCTL_CAW                      BITS(0,1)                     /*!< column address bit width */
#define EXMC_SDCTL_RAW                      BITS(2,3)                     /*!< row address bit width */
#define EXMC_SDCTL_SDW                      BITS(4,5)                     /*!< SDRAM data bus width */
#define EXMC_SDCTL_NBK                      BIT(6)                        /*!< number of banks */
#define EXMC_SDCTL_CL                       BIT(7,8)                      /*!< CAS Latency */
#define EXMC_SDCTL_WPEN                     BIT(9)                        /*!< write protection enable */
#define EXMC_SDCTL_SDCLK                    BITS(10,11)                   /*!< SDRAM clock configuration */
#define EXMC_SDCTL_BRSTRD                   BIT(12)                       /*!< burst read enable bit */
#define EXMC_SDCTL_PIPED                    BITS(13,14)                   /*!< pipeline delay */
#define EXMC_SDCTL_SDCLK_2                  BIT(15)                       /*!< bit 2 SDCLK */

/* EXMC_SDTCFGx,(x=0,1) */
#define EXMC_SDTCFG_LMRD                    BITS(0,3)                     /*!< load mode register delay */
#define EXMC_SDTCFG_XSRD                    BITS(4,7)                     /*!< exit self-refresh delay */
#define EXMC_SDTCFG_RASD                    BITS(8,11)                    /*!< row address select delay */
#define EXMC_SDTCFG_ARFD                    BITS(12,15)                   /*!< auto refresh delay */
#define EXMC_SDTCFG_WRD                     BITS(16,19)                   /*!< write recovery delay */
#define EXMC_SDTCFG_RPD                     BITS(20,23)                   /*!< row precharge delay */
#define EXMC_SDTCFG_RCD                     BITS(24,27)                   /*!< row to column delay */

/* EXMC_SDCMD */
#define EXMC_SDCMD_CMD                      BITS(0,2)                     /*!< command */
#define EXMC_SDCMD_DS1                      BIT(3)                        /*!< select device1 */
#define EXMC_SDCMD_DS0                      BIT(4)                        /*!< select device0 */
#define EXMC_SDCMD_NARF                     BITS(5,8)                     /*!< number of successive auto-refresh */
#define EXMC_SDCMD_MRC                      BITS(9,21)                    /*!< mode register content */

/* EXMC_SDARI */
#define EXMC_SDARI_REC                      BIT(0)                        /*!< refresh error flag clear */
#define EXMC_SDARI_ARINTV                   BITS(1,13)                    /*!< auto-refresh interval */
#define EXMC_SDARI_REIE                     BIT(14)                       /*!< refresh error interrupt enable bit */

/* EXMC_SDSTAT */
#define EXMC_SDSDAT_REIF                    BIT(0)                        /*!< refresh error interrupt flag */
#define EXMC_SDSDAT_STA0                    BITS(1,2)                     /*!< device0 status */
#define EXMC_SDSDAT_STA1                    BITS(3,4)                     /*!< device1 status */
#define EXMC_SDSDAT_NRDY                    BIT(5)                        /*!< not ready status */

/* EXMC_SDRSCTL */
#define EXMC_SDRSCTL_RSEN                   BIT(0)                        /*!< read sample enable bit */
#define EXMC_SDRSCTL_SSCR                   BIT(1)                        /*!< select sample cycle of read data */
#define EXMC_SDRSCTL_SDSC                   BITS(4,7)                     /*!< select the delayed sample clock of read data */

/* constants definitions */
/* EXMC NOR/SRAM timing initialize structure */
typedef struct {
    uint32_t asyn_access_mode;                                            /*!< asynchronous access mode */
    uint32_t syn_data_latency;                                            /*!< configure the data latency */
    uint32_t syn_clk_division;                                            /*!< configure the clock divide ratio */
    uint32_t bus_latency;                                                 /*!< configure the bus latency */
    uint32_t asyn_data_setuptime;                                         /*!< configure the data setup time, asynchronous access mode valid */
    uint32_t asyn_address_holdtime;                                       /*!< configure the address hold time, asynchronous access mode valid */
    uint32_t asyn_address_setuptime;                                      /*!< configure the address setup time, asynchronous access mode valid */
} exmc_norsram_timing_parameter_struct;

/* EXMC NOR/SRAM initialize structure */
typedef struct {
    uint32_t norsram_region;                                              /*!< select the region of EXMC NOR/PSRAM region */
    uint32_t address_data_mux;                                            /*!< specify whether the data bus and address bus are multiplexed */
    uint32_t memory_type;                                                 /*!< specify the type of external memory */
    uint32_t databus_width;                                               /*!< specify the databus width of external memory */
    uint32_t burst_mode;                                                  /*!< enable or disable the burst mode */
    uint32_t nwait_polarity;                                              /*!< specify the polarity of NWAIT signal from memory */
    uint32_t nwait_config;                                                /*!< NWAIT signal configuration */
    uint32_t memory_write;                                                /*!< enable or disable the write operation */
    uint32_t nwait_signal;                                                /*!< enable or disable the NWAIT signal while in synchronous bust mode */
    uint32_t extended_mode;                                               /*!< enable or disable the extended mode */
    uint32_t asyn_wait;                                                   /*!< enable or disable the asynchronous wait function */
    uint32_t cram_page_size;                                              /*!< specify CRAM page size */
    uint32_t write_mode;                                                  /*!< the write mode, synchronous mode or asynchronous mode */
    exmc_norsram_timing_parameter_struct
    *read_write_timing;              /*!< timing parameters for read and write if the extendedmode is not used or the timing
                                                                               parameters for read if the extendedmode is used */
    exmc_norsram_timing_parameter_struct *write_timing;                   /*!< timing parameters for write when the extendedmode is used */
} exmc_norsram_parameter_struct;

/* EXMC NAND timing initialize structure */
typedef struct {
    uint32_t databus_hiztime;                                             /*!< configure the dadtabus HiZ time for write operation */
    uint32_t holdtime;                                                    /*!< configure the address hold time(or the data hold time for write operation) */
    uint32_t waittime;                                                    /*!< configure the minimum wait time */
    uint32_t setuptime;                                                   /*!< configure the address setup time */
} exmc_nand_timing_parameter_struct;

/* EXMC NAND initialize structure */
typedef struct {
    uint32_t ecc_size;                                                    /*!< the page size for the ECC calculation */
    uint32_t atr_latency;                                                 /*!< configure the latency of ALE low to RB low */
    uint32_t ctr_latency;                                                 /*!< configure the latency of CLE low to RB low */
    uint32_t ecc_logic;                                                   /*!< enable or disable the ECC calculation logic */
    uint32_t databus_width;                                               /*!< the NAND flash databus width */
    uint32_t wait_feature;                                                /*!< enable or disable the wait feature */
    exmc_nand_timing_parameter_struct *common_space_timing;               /*!< the timing parameters for NAND flash common space */
    exmc_nand_timing_parameter_struct *attribute_space_timing;            /*!< the timing parameters for NAND flash attribute space */
} exmc_nand_parameter_struct;

/* EXMC SDRAM timing initialize structure */
typedef struct {
    uint32_t row_to_column_delay;                                         /*!< configure the row to column delay */
    uint32_t row_precharge_delay;                                         /*!< configure the row precharge delay */
    uint32_t write_recovery_delay;                                        /*!< configure the write recovery delay */
    uint32_t auto_refresh_delay;                                          /*!< configure the auto refresh delay */
    uint32_t row_address_select_delay;                                    /*!< configure the row address select delay */
    uint32_t exit_selfrefresh_delay;                                      /*!< configure the exit self-refresh delay */
    uint32_t load_mode_register_delay;                                    /*!< configure the load mode register delay */
} exmc_sdram_timing_parameter_struct;

/* EXMC SDRAM initialize structure */
typedef struct {
    uint32_t sdram_device;                                                /*!< device of SDRAM */
    uint32_t pipeline_read_delay;                                         /*!< the delay for reading data after CAS latency in CK_EXMC clock cycles */
    uint32_t burst_read_switch;                                           /*!< enable or disable the burst read */
    uint32_t sdclock_config;                                              /*!< the SDCLK memory clock for both SDRAM devices */
    uint32_t write_protection;                                            /*!< enable or disable SDRAM device write protection function */
    uint32_t cas_latency;                                                 /*!< configure the SDRAM CAS latency */
    uint32_t internal_bank_number;                                        /*!< the number of internal bank */
    uint32_t data_width;                                                  /*!< the databus width of SDRAM memory */
    uint32_t row_address_width;                                           /*!< the bit width of a row address */
    uint32_t column_address_width;                                        /*!< the bit width of a column address */
    exmc_sdram_timing_parameter_struct *timing;                           /*!< the timing parameters for write and read SDRAM */
} exmc_sdram_parameter_struct;

/* EXMC SDRAM command initialize structure */
typedef struct {
    uint32_t mode_register_content;                                       /*!< the SDRAM mode register content */
    uint32_t auto_refresh_number;                                         /*!< the number of successive auto-refresh cycles will be send when CMD = 011 */
    uint32_t bank_select;                                                 /*!< the bank which command will be sent to */
    uint32_t command;                                                     /*!< the commands that will be sent to SDRAM */
} exmc_sdram_command_parameter_struct;

/* EXMC_register address */
#define EXMC_SNCTL(region)                  REG32(EXMC + 0x08U*((uint32_t)(region)))                      /*!< EXMC SRAM/NOR flash control registers, region = 0,1,2,3 */
#define EXMC_SNTCFG(region)                 REG32(EXMC + 0x04U + 0x08U*((uint32_t)(region)))              /*!< EXMC SRAM/NOR flash timing configuration registers, region = 0,1,2,3 */
#define EXMC_SNWTCFG(region)                REG32(EXMC + 0x104U + 0x08U*((uint32_t)(region)))             /*!< EXMC SRAM/NOR flash write timing configuration registers, region = 0,1,2,3 */

#define EXMC_SDCTL(device)                  REG32(EXMC + 0x140U + 0x4U*(((uint32_t)(device)) - 0x4U))     /*!< EXMC SDRAM control registers,device = 0,1 */
#define EXMC_SDTCFG(device)                 REG32(EXMC + 0x148U + 0x4U*(((uint32_t)(device)) - 0x4U))     /*!< EXMC SDRAM timing configuration registers,device = 0,1 */

/* bank remap */
#define SNCTL_BKREMAP(regval)               (BITS(24,25) & ((uint32_t)(regval) << 24))
#define EXMC_BANK_REMAP_DEFAULT             SNCTL_BKREMAP(0)                                              /*!< default mapping */
#define EXMC_BANK_NORPSRAM_SDRAM_SWAP       SNCTL_BKREMAP(1)                                              /*!< swap NOR/PSRAM bank and SDRAM device 0 address mapping */

/* CRAM page size */
#define SNCTL_CPS(regval)                   (BITS(16,18) & ((uint32_t)(regval) << 16))
#define EXMC_CRAM_AUTO_SPLIT                SNCTL_CPS(0)                                                  /*!< automatic burst split on page boundary crossing */
#define EXMC_CRAM_PAGE_SIZE_128_BYTES       SNCTL_CPS(1)                                                  /*!< page size is 128 bytes */
#define EXMC_CRAM_PAGE_SIZE_256_BYTES       SNCTL_CPS(2)                                                  /*!< page size is 256 bytes */
#define EXMC_CRAM_PAGE_SIZE_512_BYTES       SNCTL_CPS(3)                                                  /*!< page size is 512 bytes */
#define EXMC_CRAM_PAGE_SIZE_1024_BYTES      SNCTL_CPS(4)                                                  /*!< page size is 1024 bytes */

/* NOR region memory data bus width */
#define SNCTL_NRW(regval)                   (BITS(4,5) & ((uint32_t)(regval) << 4))
#define EXMC_NOR_DATABUS_WIDTH_8B           SNCTL_NRW(0)                                                  /*!< NOR data width is 8 bits */
#define EXMC_NOR_DATABUS_WIDTH_16B          SNCTL_NRW(1)                                                  /*!< NOR data width is 16 bits */

/* NOR region memory type */
#define SNCTL_NRTP(regval)                  (BITS(2,3) & ((uint32_t)(regval) << 2))
#define EXMC_MEMORY_TYPE_SRAM               SNCTL_NRTP(0)                                                 /*!< SRAM,ROM */
#define EXMC_MEMORY_TYPE_PSRAM              SNCTL_NRTP(1)                                                 /*!< PSRAM,CRAM */
#define EXMC_MEMORY_TYPE_NOR                SNCTL_NRTP(2)                                                 /*!< NOR flash */

/* asynchronous access mode */
#define SNTCFG_ASYNCMOD(regval)             (BITS(28,29) & ((uint32_t)(regval) << 28))
#define EXMC_ACCESS_MODE_A                  SNTCFG_ASYNCMOD(0)                                            /*!< mode A access */
#define EXMC_ACCESS_MODE_B                  SNTCFG_ASYNCMOD(1)                                            /*!< mode B access */
#define EXMC_ACCESS_MODE_C                  SNTCFG_ASYNCMOD(2)                                            /*!< mode C access */
#define EXMC_ACCESS_MODE_D                  SNTCFG_ASYNCMOD(3)                                            /*!< mode D access */

/* data latency for NOR flash */
#define SNTCFG_DLAT(regval)                 (BITS(24,27) & ((uint32_t)(regval) << 24))
#define EXMC_DATALAT_2_CLK                  SNTCFG_DLAT(0)                                                /*!< data latency of first burst access is 2 EXMC_CLK */
#define EXMC_DATALAT_3_CLK                  SNTCFG_DLAT(1)                                                /*!< data latency of first burst access is 3 EXMC_CLK */
#define EXMC_DATALAT_4_CLK                  SNTCFG_DLAT(2)                                                /*!< data latency of first burst access is 4 EXMC_CLK */
#define EXMC_DATALAT_5_CLK                  SNTCFG_DLAT(3)                                                /*!< data latency of first burst access is 5 EXMC_CLK */
#define EXMC_DATALAT_6_CLK                  SNTCFG_DLAT(4)                                                /*!< data latency of first burst access is 6 EXMC_CLK */
#define EXMC_DATALAT_7_CLK                  SNTCFG_DLAT(5)                                                /*!< data latency of first burst access is 7 EXMC_CLK */
#define EXMC_DATALAT_8_CLK                  SNTCFG_DLAT(6)                                                /*!< data latency of first burst access is 8 EXMC_CLK */
#define EXMC_DATALAT_9_CLK                  SNTCFG_DLAT(7)                                                /*!< data latency of first burst access is 9 EXMC_CLK */
#define EXMC_DATALAT_10_CLK                 SNTCFG_DLAT(8)                                                /*!< data latency of first burst access is 10 EXMC_CLK */
#define EXMC_DATALAT_11_CLK                 SNTCFG_DLAT(9)                                                /*!< data latency of first burst access is 11 EXMC_CLK */
#define EXMC_DATALAT_12_CLK                 SNTCFG_DLAT(10)                                               /*!< data latency of first burst access is 12 EXMC_CLK */
#define EXMC_DATALAT_13_CLK                 SNTCFG_DLAT(11)                                               /*!< data latency of first burst access is 13 EXMC_CLK */
#define EXMC_DATALAT_14_CLK                 SNTCFG_DLAT(12)                                               /*!< data latency of first burst access is 14 EXMC_CLK */
#define EXMC_DATALAT_15_CLK                 SNTCFG_DLAT(13)                                               /*!< data latency of first burst access is 15 EXMC_CLK */
#define EXMC_DATALAT_16_CLK                 SNTCFG_DLAT(14)                                               /*!< data latency of first burst access is 16 EXMC_CLK */
#define EXMC_DATALAT_17_CLK                 SNTCFG_DLAT(15)                                               /*!< data latency of first burst access is 17 EXMC_CLK */

/* synchronous clock divide ratio */
#define SNTCFG_CKDIV(regval)                (BITS(20,23) & ((uint32_t)(regval) << 20))
#define EXMC_SYN_CLOCK_RATIO_DISABLE        SNTCFG_CKDIV(0)                                               /*!< no EXMC_CLK output */
#define EXMC_SYN_CLOCK_RATIO_2_CLK          SNTCFG_CKDIV(1)                                               /*!< EXMC_CLK period = 2*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_3_CLK          SNTCFG_CKDIV(2)                                               /*!< EXMC_CLK period = 3*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_4_CLK          SNTCFG_CKDIV(3)                                               /*!< EXMC_CLK period = 4*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_5_CLK          SNTCFG_CKDIV(4)                                               /*!< EXMC_CLK period = 5*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_6_CLK          SNTCFG_CKDIV(5)                                               /*!< EXMC_CLK period = 6*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_7_CLK          SNTCFG_CKDIV(6)                                               /*!< EXMC_CLK period = 7*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_8_CLK          SNTCFG_CKDIV(7)                                               /*!< EXMC_CLK period = 8*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_9_CLK          SNTCFG_CKDIV(8)                                               /*!< EXMC_CLK period = 9*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_10_CLK         SNTCFG_CKDIV(9)                                               /*!< EXMC_CLK period = 10*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_11_CLK         SNTCFG_CKDIV(10)                                              /*!< EXMC_CLK period = 11*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_12_CLK         SNTCFG_CKDIV(11)                                              /*!< EXMC_CLK period = 12*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_13_CLK         SNTCFG_CKDIV(12)                                              /*!< EXMC_CLK period = 13*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_14_CLK         SNTCFG_CKDIV(13)                                              /*!< EXMC_CLK period = 14*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_15_CLK         SNTCFG_CKDIV(14)                                              /*!< EXMC_CLK period = 15*CK_EXMC period */
#define EXMC_SYN_CLOCK_RATIO_16_CLK         SNTCFG_CKDIV(15)                                              /*!< EXMC_CLK period = 16*CK_EXMC period */

/* ECC size */
#define NCTL_ECCSZ(regval)                  (BITS(17,19) & ((uint32_t)(regval) << 17))
#define EXMC_ECC_SIZE_256BYTES              NCTL_ECCSZ(0)                                                 /* ECC size is 256 bytes */
#define EXMC_ECC_SIZE_512BYTES              NCTL_ECCSZ(1)                                                 /* ECC size is 512 bytes */
#define EXMC_ECC_SIZE_1024BYTES             NCTL_ECCSZ(2)                                                 /* ECC size is 1024 bytes */
#define EXMC_ECC_SIZE_2048BYTES             NCTL_ECCSZ(3)                                                 /* ECC size is 2048 bytes */
#define EXMC_ECC_SIZE_4096BYTES             NCTL_ECCSZ(4)                                                 /* ECC size is 4096 bytes */
#define EXMC_ECC_SIZE_8192BYTES             NCTL_ECCSZ(5)                                                 /* ECC size is 8192 bytes */

/* ALE to RE delay */
#define NCTL_ATR(regval)                    (BITS(13,16) & ((uint32_t)(regval) << 13))
#define EXMC_ALE_RE_DELAY_1_CK_EXMC         NCTL_ATR(0)                                                   /* ALE to RE delay = 1*CK_EXMC */
#define EXMC_ALE_RE_DELAY_2_CK_EXMC         NCTL_ATR(1)                                                   /* ALE to RE delay = 2*CK_EXMC */
#define EXMC_ALE_RE_DELAY_3_CK_EXMC         NCTL_ATR(2)                                                   /* ALE to RE delay = 3*CK_EXMC */
#define EXMC_ALE_RE_DELAY_4_CK_EXMC         NCTL_ATR(3)                                                   /* ALE to RE delay = 4*CK_EXMC */
#define EXMC_ALE_RE_DELAY_5_CK_EXMC         NCTL_ATR(4)                                                   /* ALE to RE delay = 5*CK_EXMC */
#define EXMC_ALE_RE_DELAY_6_CK_EXMC         NCTL_ATR(5)                                                   /* ALE to RE delay = 6*CK_EXMC */
#define EXMC_ALE_RE_DELAY_7_CK_EXMC         NCTL_ATR(6)                                                   /* ALE to RE delay = 7*CK_EXMC */
#define EXMC_ALE_RE_DELAY_8_CK_EXMC         NCTL_ATR(7)                                                   /* ALE to RE delay = 8*CK_EXMC */
#define EXMC_ALE_RE_DELAY_9_CK_EXMC         NCTL_ATR(8)                                                   /* ALE to RE delay = 9*CK_EXMC */
#define EXMC_ALE_RE_DELAY_10_CK_EXMC        NCTL_ATR(9)                                                   /* ALE to RE delay = 10*CK_EXMC */
#define EXMC_ALE_RE_DELAY_11_CK_EXMC        NCTL_ATR(10)                                                  /* ALE to RE delay = 11*CK_EXMC */
#define EXMC_ALE_RE_DELAY_12_CK_EXMC        NCTL_ATR(11)                                                  /* ALE to RE delay = 12*CK_EXMC */
#define EXMC_ALE_RE_DELAY_13_CK_EXMC        NCTL_ATR(12)                                                  /* ALE to RE delay = 13*CK_EXMC */
#define EXMC_ALE_RE_DELAY_14_CK_EXMC        NCTL_ATR(13)                                                  /* ALE to RE delay = 14*CK_EXMC */
#define EXMC_ALE_RE_DELAY_15_CK_EXMC        NCTL_ATR(14)                                                  /* ALE to RE delay = 15*CK_EXMC */
#define EXMC_ALE_RE_DELAY_16_CK_EXMC        NCTL_ATR(15)                                                  /* ALE to RE delay = 16*CK_EXMC */

/* CLE to RE delay */
#define NCTL_CTR(regval)                    (BITS(9,12) & ((uint32_t)(regval) << 9))
#define EXMC_CLE_RE_DELAY_1_CK_EXMC         NCTL_CTR(0)                                                   /* CLE to RE delay = 1*CK_EXMC */
#define EXMC_CLE_RE_DELAY_2_CK_EXMC         NCTL_CTR(1)                                                   /* CLE to RE delay = 2*CK_EXMC */
#define EXMC_CLE_RE_DELAY_3_CK_EXMC         NCTL_CTR(2)                                                   /* CLE to RE delay = 3*CK_EXMC */
#define EXMC_CLE_RE_DELAY_4_CK_EXMC         NCTL_CTR(3)                                                   /* CLE to RE delay = 4*CK_EXMC */
#define EXMC_CLE_RE_DELAY_5_CK_EXMC         NCTL_CTR(4)                                                   /* CLE to RE delay = 5*CK_EXMC */
#define EXMC_CLE_RE_DELAY_6_CK_EXMC         NCTL_CTR(5)                                                   /* CLE to RE delay = 6*CK_EXMC */
#define EXMC_CLE_RE_DELAY_7_CK_EXMC         NCTL_CTR(6)                                                   /* CLE to RE delay = 7*CK_EXMC */
#define EXMC_CLE_RE_DELAY_8_CK_EXMC         NCTL_CTR(7)                                                   /* CLE to RE delay = 8*CK_EXMC */
#define EXMC_CLE_RE_DELAY_9_CK_EXMC         NCTL_CTR(8)                                                   /* CLE to RE delay = 9*CK_EXMC */
#define EXMC_CLE_RE_DELAY_10_CK_EXMC        NCTL_CTR(9)                                                   /* CLE to RE delay = 10*CK_EXMC */
#define EXMC_CLE_RE_DELAY_11_CK_EXMC        NCTL_CTR(10)                                                  /* CLE to RE delay = 11*CK_EXMC */
#define EXMC_CLE_RE_DELAY_12_CK_EXMC        NCTL_CTR(11)                                                  /* CLE to RE delay = 12*CK_EXMC */
#define EXMC_CLE_RE_DELAY_13_CK_EXMC        NCTL_CTR(12)                                                  /* CLE to RE delay = 13*CK_EXMC */
#define EXMC_CLE_RE_DELAY_14_CK_EXMC        NCTL_CTR(13)                                                  /* CLE to RE delay = 14*CK_EXMC */
#define EXMC_CLE_RE_DELAY_15_CK_EXMC        NCTL_CTR(14)                                                  /* CLE to RE delay = 15*CK_EXMC */
#define EXMC_CLE_RE_DELAY_16_CK_EXMC        NCTL_CTR(15)                                                  /* CLE to RE delay = 16*CK_EXMC */

/* NAND bank memory data bus width */
#define NCTL_NDW(regval)                    (BITS(4,5) & ((uint32_t)(regval) << 4))
#define EXMC_NAND_DATABUS_WIDTH_8B          NCTL_NDW(0)                                                   /*!< NAND data width is 8 bits */
#define EXMC_NAND_DATABUS_WIDTH_16B         NCTL_NDW(1)                                                   /*!< NAND data width is 16 bits */

/* SDRAM pipeline delay */
#define SDCTL_PIPED(regval)                 (BITS(13,14) & ((uint32_t)(regval) << 13))
#define EXMC_PIPELINE_DELAY_0_CK_EXMC       SDCTL_PIPED(0)                                                /*!< 0 CK_EXMC clock cycle delay */
#define EXMC_PIPELINE_DELAY_1_CK_EXMC       SDCTL_PIPED(1)                                                /*!< 1 CK_EXMC clock cycle delay */
#define EXMC_PIPELINE_DELAY_2_CK_EXMC       SDCTL_PIPED(2)                                                /*!< 2 CK_EXMC clock cycle delay */

/* SDRAM clock configuration */
#define SDCTL_SDCLK(regval)                 (BITS(10,11) & ((uint32_t)(regval) << 10))
#define EXMC_SDCLK_DISABLE                  SDCTL_SDCLK(0)                                                /*!< SDCLK memory clock disabled */
#define EXMC_SDCLK_PERIODS_2_CK_EXMC        SDCTL_SDCLK(2)                                                /*!< SDCLK memory period = 2*CK_EXMC */
#define EXMC_SDCLK_PERIODS_3_CK_EXMC        SDCTL_SDCLK(3)                                                /*!< SDCLK memory period = 3*CK_EXMC */
#define EXMC_SDCLK_PERIODS_4_CK_EXMC        (EXMC_SDCTL_SDCLK_2 | SDCTL_SDCLK(2))                         /*!< SDCLK memory period = 4*CK_EXMC */
#define EXMC_SDCLK_PERIODS_5_CK_EXMC        (EXMC_SDCTL_SDCLK_2 | SDCTL_SDCLK(3))                         /*!< SDCLK memory period = 5*CK_EXMC */

/* CAS latency */
#define SDCTL_CL(regval)                    (BITS(7,8) & ((uint32_t)(regval) << 7))
#define EXMC_CAS_LATENCY_1_SDCLK            SDCTL_CL(1)                                                   /*!< CAS latency is 1 memory clock cycle */
#define EXMC_CAS_LATENCY_2_SDCLK            SDCTL_CL(2)                                                   /*!< CAS latency is 2 memory clock cycle */
#define EXMC_CAS_LATENCY_3_SDCLK            SDCTL_CL(3)                                                   /*!< CAS latency is 3 memory clock cycle */

/* SDRAM data bus width */
#define SDCTL_SDW(regval)                   (BITS(4,5) & ((uint32_t)(regval) << 4))
#define EXMC_SDRAM_DATABUS_WIDTH_8B         SDCTL_SDW(0)                                                  /*!< SDRAM data width 8 bits */
#define EXMC_SDRAM_DATABUS_WIDTH_16B        SDCTL_SDW(1)                                                  /*!< SDRAM data width 16 bits */
#define EXMC_SDRAM_DATABUS_WIDTH_32B        SDCTL_SDW(2)                                                  /*!< SDRAM data width 32 bits */

/* SDRAM row address bit width */
#define SDCTL_RAW(regval)                   (BITS(2,3) & ((uint32_t)(regval) << 2))
#define EXMC_SDRAM_ROW_ADDRESS_11           SDCTL_RAW(0)                                                  /*!< row address bit width is 11 bits */
#define EXMC_SDRAM_ROW_ADDRESS_12           SDCTL_RAW(1)                                                  /*!< row address bit width is 12 bits */
#define EXMC_SDRAM_ROW_ADDRESS_13           SDCTL_RAW(2)                                                  /*!< row address bit width is 13 bits */

/* SDRAM column address bit width */
#define SDCTL_CAW(regval)                   (BITS(0,1) & ((uint32_t)(regval) << 0))
#define EXMC_SDRAM_COW_ADDRESS_8            SDCTL_CAW(0)                                                  /*!< column address bit width is 8 bits */
#define EXMC_SDRAM_COW_ADDRESS_9            SDCTL_CAW(1)                                                  /*!< column address bit width is 9 bits */
#define EXMC_SDRAM_COW_ADDRESS_10           SDCTL_CAW(2)                                                  /*!< column address bit width is 10 bits */
#define EXMC_SDRAM_COW_ADDRESS_11           SDCTL_CAW(3)                                                  /*!< column address bit width is 11 bits */

/* SDRAM number of successive auto-refresh */
#define SDCMD_NARF(regval)                  (BITS(5,8) & ((uint32_t)(regval) << 5))
#define EXMC_SDRAM_AUTO_REFLESH_1_SDCLK     SDCMD_NARF(0)                                                 /*!< 1 auto-refresh cycle */
#define EXMC_SDRAM_AUTO_REFLESH_2_SDCLK     SDCMD_NARF(1)                                                 /*!< 2 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_3_SDCLK     SDCMD_NARF(2)                                                 /*!< 3 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_4_SDCLK     SDCMD_NARF(3)                                                 /*!< 4 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_5_SDCLK     SDCMD_NARF(4)                                                 /*!< 5 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_6_SDCLK     SDCMD_NARF(5)                                                 /*!< 6 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_7_SDCLK     SDCMD_NARF(6)                                                 /*!< 7 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_8_SDCLK     SDCMD_NARF(7)                                                 /*!< 8 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_9_SDCLK     SDCMD_NARF(8)                                                 /*!< 9 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_10_SDCLK    SDCMD_NARF(9)                                                 /*!< 10 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_11_SDCLK    SDCMD_NARF(10)                                                /*!< 11 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_12_SDCLK    SDCMD_NARF(11)                                                /*!< 12 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_13_SDCLK    SDCMD_NARF(12)                                                /*!< 13 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_14_SDCLK    SDCMD_NARF(13)                                                /*!< 14 auto-refresh cycles */
#define EXMC_SDRAM_AUTO_REFLESH_15_SDCLK    SDCMD_NARF(14)                                                /*!< 15 auto-refresh cycles */

/* SDRAM command selection */
#define SDCMD_CMD(regval)                   (BITS(0,2) & ((uint32_t)(regval) << 0))
#define EXMC_SDRAM_NORMAL_OPERATION         SDCMD_CMD(0)                                                  /*!< normal operation command */
#define EXMC_SDRAM_CLOCK_ENABLE             SDCMD_CMD(1)                                                  /*!< clock enable command */
#define EXMC_SDRAM_PRECHARGE_ALL            SDCMD_CMD(2)                                                  /*!< precharge all command */
#define EXMC_SDRAM_AUTO_REFRESH             SDCMD_CMD(3)                                                  /*!< auto-refresh command */
#define EXMC_SDRAM_LOAD_MODE_REGISTER       SDCMD_CMD(4)                                                  /*!< load mode register command */
#define EXMC_SDRAM_SELF_REFRESH             SDCMD_CMD(5)                                                  /*!< self-refresh command */
#define EXMC_SDRAM_POWERDOWN_ENTRY          SDCMD_CMD(6)                                                  /*!< power-down entry command */

/* SDRAM the delayed sample clock of read data */
#define SDRSCTL_SDSC(regval)                (BITS(4,7) & ((uint32_t)(regval) << 4))
#define EXMC_SDRAM_0_DELAY_CELL             SDRSCTL_SDSC(0)                                               /*!< select the clock after 0 delay cell */
#define EXMC_SDRAM_1_DELAY_CELL             SDRSCTL_SDSC(1)                                               /*!< select the clock after 1 delay cell */
#define EXMC_SDRAM_2_DELAY_CELL             SDRSCTL_SDSC(2)                                               /*!< select the clock after 2 delay cell */
#define EXMC_SDRAM_3_DELAY_CELL             SDRSCTL_SDSC(3)                                               /*!< select the clock after 3 delay cell */
#define EXMC_SDRAM_4_DELAY_CELL             SDRSCTL_SDSC(4)                                               /*!< select the clock after 4 delay cell */
#define EXMC_SDRAM_5_DELAY_CELL             SDRSCTL_SDSC(5)                                               /*!< select the clock after 5 delay cell */
#define EXMC_SDRAM_6_DELAY_CELL             SDRSCTL_SDSC(6)                                               /*!< select the clock after 6 delay cell */
#define EXMC_SDRAM_7_DELAY_CELL             SDRSCTL_SDSC(7)                                               /*!< select the clock after 7 delay cell */
#define EXMC_SDRAM_8_DELAY_CELL             SDRSCTL_SDSC(8)                                               /*!< select the clock after 8 delay cell */
#define EXMC_SDRAM_9_DELAY_CELL             SDRSCTL_SDSC(9)                                               /*!< select the clock after 9 delay cell */
#define EXMC_SDRAM_10_DELAY_CELL            SDRSCTL_SDSC(10)                                              /*!< select the clock after 10 delay cell */
#define EXMC_SDRAM_11_DELAY_CELL            SDRSCTL_SDSC(11)                                              /*!< select the clock after 11 delay cell */
#define EXMC_SDRAM_12_DELAY_CELL            SDRSCTL_SDSC(12)                                              /*!< select the clock after 12 delay cell */
#define EXMC_SDRAM_13_DELAY_CELL            SDRSCTL_SDSC(13)                                              /*!< select the clock after 13 delay cell */
#define EXMC_SDRAM_14_DELAY_CELL            SDRSCTL_SDSC(14)                                              /*!< select the clock after 14 delay cell */
#define EXMC_SDRAM_15_DELAY_CELL            SDRSCTL_SDSC(15)                                              /*!< select the clock after 15 delay cell */

/* EXMC NOR/SRAM bank region definition */
#define EXMC_BANK0_NORSRAM_REGION0          ((uint32_t)0x00000000U)                                       /*!< bank0 NOR/SRAM region0 */
#define EXMC_BANK0_NORSRAM_REGION1          ((uint32_t)0x00000001U)                                       /*!< bank0 NOR/SRAM region1 */
#define EXMC_BANK0_NORSRAM_REGION2          ((uint32_t)0x00000002U)                                       /*!< bank0 NOR/SRAM region2 */
#define EXMC_BANK0_NORSRAM_REGION3          ((uint32_t)0x00000003U)                                       /*!< bank0 NOR/SRAM region3 */

/* EXMC consecutive clock */
#define EXMC_CLOCK_SYN_MODE                 ((uint32_t)0x00000000U)                                       /*!< EXMC_CLK is generated only during synchronous access */
#define EXMC_CLOCK_UNCONDITIONALLY          EXMC_SNCTL_CCK                                                /*!< EXMC_CLK is generated unconditionally */

/* EXMC NOR/SRAM write mode */
#define EXMC_ASYN_WRITE                     ((uint32_t)0x00000000U)                                       /*!< asynchronous write mode */
#define EXMC_SYN_WRITE                      EXMC_SNCTL_SYNCWR                                             /*!< synchronous write mode */

/* EXMC NWAIT signal configuration */
#define EXMC_NWAIT_CONFIG_BEFORE            ((uint32_t)0x00000000U)                                       /*!< NWAIT signal is active one data cycle before wait state */
#define EXMC_NWAIT_CONFIG_DURING            EXMC_SNCTL_NRWTCFG                                            /*!< NWAIT signal is active during wait state */

/* EXMC NWAIT signal polarity configuration */
#define EXMC_NWAIT_POLARITY_LOW             ((uint32_t)0x00000000U)                                       /*!< low level is active of NWAIT */
#define EXMC_NWAIT_POLARITY_HIGH            EXMC_SNCTL_NRWTPOL                                            /*!< high level is active of NWAIT */

/* EXMC NAND bank definition */
#define EXMC_BANK2_NAND                     ((uint32_t)0x00000002U)                                       /*!< NAND flash bank2 */

/* EXMC SDRAM bank definition */
#define EXMC_SDRAM_DEVICE0                  ((uint32_t)0x00000004U)                                       /*!< SDRAM device0 */
#define EXMC_SDRAM_DEVICE1                  ((uint32_t)0x00000005U)                                       /*!< SDRAM device1 */

/* EXMC SDRAM internal banks */
#define EXMC_SDRAM_2_INTER_BANK             ((uint32_t)0x00000000U)                                       /*!< 2 internal banks */
#define EXMC_SDRAM_4_INTER_BANK             EXMC_SDCTL_NBK                                                /*!< 4 internal banks */

/* SDRAM device0 select */
#define EXMC_SDRAM_DEVICE0_UNSELECT         ((uint32_t)0x00000000U)                                       /*!< SDRAM device0 unselect */
#define EXMC_SDRAM_DEVICE0_SELECT           EXMC_SDCMD_DS0                                                /*!< SDRAM device0 select */

/* SDRAM device1 select */
#define EXMC_SDRAM_DEVICE1_UNSELECT         ((uint32_t)0x00000000U)                                       /*!< SDRAM device1 unselect */
#define EXMC_SDRAM_DEVICE1_SELECT           EXMC_SDCMD_DS1                                                /*!< SDRAM device1 select */

/* SDRAM device status */
#define EXMC_SDRAM_DEVICE_NORMAL            ((uint32_t)0x00000000U)                                       /*!< normal status */
#define EXMC_SDRAM_DEVICE_SELF_REFRESH      ((uint32_t)0x00000001U)                                       /*!< self refresh status */
#define EXMC_SDRAM_DEVICE_POWER_DOWN        ((uint32_t)0x00000002U)                                       /*!< power down status */

/* sample cycle of read data */
#define EXMC_SDRAM_READSAMPLE_0_EXTRACK     ((uint32_t)0x00000000U)                                       /*!< add 0 extra CK_EXMC cycle to the read data sample clock besides the delay chain */
#define EXMC_SDRAM_READSAMPLE_1_EXTRACK     EXMC_SDRSCTL_SSCR                                             /*!< add 1 extra CK_EXMC cycle to the read data sample clock besides the delay chain */

/* EXMC flag bits */
#define EXMC_NAND_FLAG_RISE                 EXMC_NINTEN_INTRS                                             /*!< rising edge interrupt status */
#define EXMC_NAND_FLAG_LEVEL                EXMC_NINTEN_INTHS                                             /*!< high-level interrupt status */
#define EXMC_NAND_FLAG_FALL                 EXMC_NINTEN_INTFS                                             /*!< falling edge interrupt status */
#define EXMC_NAND_FLAG_FIFOE                EXMC_NINTEN_FFEPT                                             /*!< FIFO empty flag */
#define EXMC_SDRAM_FLAG_REFRESH             EXMC_SDSDAT_REIF                                              /*!< refresh error interrupt flag */
#define EXMC_SDRAM_FLAG_NREADY              EXMC_SDSDAT_NRDY                                              /*!< not ready status */

/* EXMC interrupt bits */
#define EXMC_NAND_INT_RISE                  EXMC_NINTEN_INTREN                                            /*!< rising edge interrupt */
#define EXMC_NAND_INT_LEVEL                 EXMC_NINTEN_INTHEN                                            /*!< high-level interrupt */
#define EXMC_NAND_INT_FALL                  EXMC_NINTEN_INTFEN                                            /*!< falling edge interrupt */
#define EXMC_SDRAM_INT_REFRESH              EXMC_SDARI_REIE                                               /*!< refresh error interrupt */

/* EXMC interrupt flag bits */
#define EXMC_NAND_INT_FLAG_RISE             EXMC_NINTEN_INTREN                                            /*!< rising edge interrupt flag */
#define EXMC_NAND_INT_FLAG_LEVEL            EXMC_NINTEN_INTHEN                                            /*!< high-level interrupt flag */
#define EXMC_NAND_INT_FLAG_FALL             EXMC_NINTEN_INTFEN                                            /*!< falling edge interrupt flag */
#define EXMC_SDRAM_INT_FLAG_REFRESH         EXMC_SDARI_REIE                                               /*!< refresh error interrupt flag */

/* function declarations */
/* initialization functions */
/* NOR/SRAM */
/* deinitialize EXMC NOR/SRAM region */
void exmc_norsram_deinit(uint32_t exmc_norsram_region);
/* initialize exmc_norsram_parameter_struct with the default values */
void exmc_norsram_struct_para_init(exmc_norsram_parameter_struct *exmc_norsram_init_struct);
/* initialize EXMC NOR/SRAM region */
void exmc_norsram_init(exmc_norsram_parameter_struct *exmc_norsram_init_struct);
/* enable EXMC NOR/SRAM region */
void exmc_norsram_enable(uint32_t exmc_norsram_region);
/* disable EXMC NOR/SRAM region */
void exmc_norsram_disable(uint32_t exmc_norsram_region);
/* NAND */
/* deinitialize EXMC NAND bank */
void exmc_nand_deinit(void);
/* initialize exmc_nand_parameter_struct with the default values */
void exmc_nand_struct_para_init(exmc_nand_parameter_struct *exmc_nand_init_struct);
/* initialize EXMC NAND bank */
void exmc_nand_init(exmc_nand_parameter_struct *exmc_nand_init_struct);
/* enable EXMC NAND bank */
void exmc_nand_enable(void);
/* disable EXMC NAND bank */
void exmc_nand_disable(void);
/* SDRAM */
/* deinitialize EXMC SDRAM device */
void exmc_sdram_deinit(uint32_t exmc_sdram_device);
/* initialize exmc_sdram_parameter_struct with the default values */
void exmc_sdram_struct_para_init(exmc_sdram_parameter_struct *exmc_sdram_init_struct);
/* initialize EXMC SDRAM device */
void exmc_sdram_init(exmc_sdram_parameter_struct *exmc_sdram_init_struct);

/* configuration functions */
/* NOR/SRAM */
/* configure NOR/PSRAM and SDRAM remap */
void exmc_norsram_sdram_remap_config(uint32_t bank_remap);
/* get NOR/PSRAM and SDRAM remap configuration */
uint32_t exmc_norsram_sdram_remap_get(void);
/* configure consecutive clock mode (only supported in EXMC BANK0 REGION0) */
void exmc_norsram_consecutive_clock_config(uint32_t clock_mode);
/* configure CRAM page size */
void exmc_norsram_page_size_config(uint32_t exmc_norsram_region, uint32_t page_size);
/* NAND */
/* enable or disable the EXMC NAND ECC function */
void exmc_nand_ecc_config(ControlStatus newvalue);
/* get NAND ECC value */
uint32_t exmc_ecc_get(void);
/* SDRAM */
/* enable read sample function */
void exmc_sdram_readsample_enable(void);
/* disable read sample function */
void exmc_sdram_readsample_disable(void);
/* configure the delayed sample clock of read data */
void exmc_sdram_readsample_config(uint32_t delay_cell, uint32_t extra_clk);
/* configure the SDRAM memory command */
void exmc_sdram_command_config(exmc_sdram_command_parameter_struct *exmc_sdram_command_init_struct);
/* set auto-refresh interval */
void exmc_sdram_refresh_count_set(uint32_t exmc_count);
/* set the number of successive auto-refresh command */
void exmc_sdram_autorefresh_number_set(uint32_t exmc_number);
/* configure the write protection function */
void exmc_sdram_write_protection_config(uint32_t exmc_sdram_device, ControlStatus newvalue);
/* get the status of SDRAM device0 or device1 */
uint32_t exmc_sdram_bankstatus_get(uint32_t exmc_sdram_device);

/* interrupt & flag functions */
/* get EXMC flag status */
FlagStatus exmc_flag_get(uint32_t exmc_bank, uint32_t flag);
/* clear EXMC flag status */
void exmc_flag_clear(uint32_t exmc_bank, uint32_t flag);
/* enable EXMC interrupt */
void exmc_interrupt_enable(uint32_t exmc_bank, uint32_t interrupt);
/* disable EXMC interrupt */
void exmc_interrupt_disable(uint32_t exmc_bank, uint32_t interrupt);
/* get EXMC interrupt flag */
FlagStatus exmc_interrupt_flag_get(uint32_t exmc_bank, uint32_t interrupt);
/* clear EXMC interrupt flag */
void exmc_interrupt_flag_clear(uint32_t exmc_bank, uint32_t interrupt);

#endif /* GD32H7XX_EXMC_H */
