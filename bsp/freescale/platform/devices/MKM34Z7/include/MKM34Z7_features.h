/*
** ###################################################################
**     Version:             rev. 1.4, 2015-05-25
**     Build:               b150715
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2014-10-17)
**         Initial version.
**     - rev. 1.1 (2015-01-21)
**         Added FSL_FEATURE_SOC_peripheral_COUNT with number of peripheral instances
**     - rev. 1.2 (2015-01-27)
**         Update according to reference manual rev. 1, RC.
**     - rev. 1.3 (2015-03-06)
**         Update according to reference manual rev. 1.
**     - rev. 1.4 (2015-05-25)
**         Added FSL_FEATURE_FLASH_PFLASH_START_ADDRESS
**
** ###################################################################
*/

#if !defined(__FSL_MKM34Z7_FEATURES_H__)
#define __FSL_MKM34Z7_FEATURES_H__

/* ADC16 module features */

/* @brief Has Programmable Gain Amplifier (PGA) in ADC (register PGA). */
#define FSL_FEATURE_ADC16_HAS_PGA (0)
/* @brief Has PGA chopping control in ADC (bit PGA[PGACHPb] or PGA[PGACHP]). */
#define FSL_FEATURE_ADC16_HAS_PGA_CHOPPING (0)
/* @brief Has PGA offset measurement mode in ADC (bit PGA[PGAOFSM]). */
#define FSL_FEATURE_ADC16_HAS_PGA_OFFSET_MEASUREMENT (0)
/* @brief Has DMA support (bit SC2[DMAEN] or SC4[DMAEN]). */
#define FSL_FEATURE_ADC16_HAS_DMA (1)
/* @brief Has differential mode (bitfield SC1x[DIFF]). */
#define FSL_FEATURE_ADC16_HAS_DIFF_MODE (0)
/* @brief Has FIFO (bit SC4[AFDEP]). */
#define FSL_FEATURE_ADC16_HAS_FIFO (0)
/* @brief FIFO size if available (bitfield SC4[AFDEP]). */
#define FSL_FEATURE_ADC16_FIFO_SIZE (0)
/* @brief Has channel set a/b multiplexor (bitfield CFG2[MUXSEL]). */
#define FSL_FEATURE_ADC16_HAS_MUX_SELECT (1)
/* @brief Has HW trigger masking (bitfield SC5[HTRGMASKE]. */
#define FSL_FEATURE_ADC16_HAS_HW_TRIGGER_MASK (0)
/* @brief Has calibration feature (bit SC3[CAL] and registers CLPx, CLMx). */
#define FSL_FEATURE_ADC16_HAS_CALIBRATION (1)
/* @brief Has HW averaging (bit SC3[AVGE]). */
#define FSL_FEATURE_ADC16_HAS_HW_AVERAGE (1)
/* @brief Has offset correction (register OFS). */
#define FSL_FEATURE_ADC16_HAS_OFFSET_CORRECTION (1)
/* @brief Maximum ADC resolution. */
#define FSL_FEATURE_ADC16_MAX_RESOLUTION (16)
/* @brief Number of SC1x and Rx register pairs (conversion control and result registers). */
#define FSL_FEATURE_ADC16_CONVERSION_CONTROL_COUNT (4)

/* AFE module features */

/* @brief AFE channel counter. */
#define FSL_FEATURE_AFE_CHANNEL_NUMBER (4)
/* @brief AFE channel counter with PGA feature. */
#define FSL_FEATURE_AFE_CHANNEL_NUMBER_WITH_PGA (4)
/* @brief  AFE has four channels. */
#define FSL_FEATURE_AFE_HAS_FOUR_CHANNELS (1)

/* CMP module features */

/* @brief Has Trigger mode in CMP (register bit field CR1[TRIGM]). */
#define FSL_FEATURE_CMP_HAS_TRIGGER_MODE (1)
/* @brief Has Window mode in CMP (register bit field CR1[WE]). */
#define FSL_FEATURE_CMP_HAS_WINDOW_MODE (1)
/* @brief Has External sample supported in CMP (register bit field CR1[SE]). */
#define FSL_FEATURE_CMP_HAS_EXTERNAL_SAMPLE_SUPPORT (1)
/* @brief Has DMA support in CMP (register bit field SCR[DMAEN]). */
#define FSL_FEATURE_CMP_HAS_DMA (1)
/* @brief Has Pass Through mode in CMP (register bit field MUXCR[PSTM]). */
#define FSL_FEATURE_CMP_HAS_PASS_THROUGH_MODE (0)
/* @brief Has DAC Test function in CMP (register DACTEST). */
#define FSL_FEATURE_CMP_HAS_DAC_TEST (0)

/* SOC module features */

/* @brief ACMP availability on the SoC. */
#define FSL_FEATURE_SOC_ACMP_COUNT (0)
/* @brief ADC16 availability on the SoC. */
#define FSL_FEATURE_SOC_ADC16_COUNT (1)
/* @brief AFE availability on the SoC. */
#define FSL_FEATURE_SOC_AFE_COUNT (1)
/* @brief AIPS availability on the SoC. */
#define FSL_FEATURE_SOC_AIPS_COUNT (1)
/* @brief AOI availability on the SoC. */
#define FSL_FEATURE_SOC_AOI_COUNT (0)
/* @brief AXBS availability on the SoC. */
#define FSL_FEATURE_SOC_AXBS_COUNT (0)
/* @brief CADC availability on the SoC. */
#define FSL_FEATURE_SOC_CADC_COUNT (0)
/* @brief FLEXCAN availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXCAN_COUNT (0)
/* @brief MMCAU availability on the SoC. */
#define FSL_FEATURE_SOC_MMCAU_COUNT (1)
/* @brief CMP availability on the SoC. */
#define FSL_FEATURE_SOC_CMP_COUNT (3)
/* @brief CMT availability on the SoC. */
#define FSL_FEATURE_SOC_CMT_COUNT (0)
/* @brief CNC availability on the SoC. */
#define FSL_FEATURE_SOC_CNC_COUNT (0)
/* @brief CRC availability on the SoC. */
#define FSL_FEATURE_SOC_CRC_COUNT (1)
/* @brief DAC availability on the SoC. */
#define FSL_FEATURE_SOC_DAC_COUNT (0)
/* @brief DCDC availability on the SoC. */
#define FSL_FEATURE_SOC_DCDC_COUNT (0)
/* @brief DDR availability on the SoC. */
#define FSL_FEATURE_SOC_DDR_COUNT (0)
/* @brief DMA availability on the SoC. */
#define FSL_FEATURE_SOC_DMA_COUNT (1)
/* @brief DMAMUX availability on the SoC. */
#define FSL_FEATURE_SOC_DMAMUX_COUNT (1)
/* @brief DRY availability on the SoC. */
#define FSL_FEATURE_SOC_DRY_COUNT (0)
/* @brief DSPI availability on the SoC. */
#define FSL_FEATURE_SOC_DSPI_COUNT (0)
/* @brief EDMA availability on the SoC. */
#define FSL_FEATURE_SOC_EDMA_COUNT (0)
/* @brief EMVSIM availability on the SoC. */
#define FSL_FEATURE_SOC_EMVSIM_COUNT (0)
/* @brief ENC availability on the SoC. */
#define FSL_FEATURE_SOC_ENC_COUNT (0)
/* @brief ENET availability on the SoC. */
#define FSL_FEATURE_SOC_ENET_COUNT (0)
/* @brief EWM availability on the SoC. */
#define FSL_FEATURE_SOC_EWM_COUNT (1)
/* @brief FB availability on the SoC. */
#define FSL_FEATURE_SOC_FB_COUNT (0)
/* @brief FGPIO availability on the SoC. */
#define FSL_FEATURE_SOC_FGPIO_COUNT (0)
/* @brief FLEXIO availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXIO_COUNT (0)
/* @brief FMC availability on the SoC. */
#define FSL_FEATURE_SOC_FMC_COUNT (0)
/* @brief FSKDT availability on the SoC. */
#define FSL_FEATURE_SOC_FSKDT_COUNT (0)
/* @brief FTFA availability on the SoC. */
#define FSL_FEATURE_SOC_FTFA_COUNT (1)
/* @brief FTFE availability on the SoC. */
#define FSL_FEATURE_SOC_FTFE_COUNT (0)
/* @brief FTFL availability on the SoC. */
#define FSL_FEATURE_SOC_FTFL_COUNT (0)
/* @brief FTM availability on the SoC. */
#define FSL_FEATURE_SOC_FTM_COUNT (0)
/* @brief FTMRA availability on the SoC. */
#define FSL_FEATURE_SOC_FTMRA_COUNT (0)
/* @brief FTMRE availability on the SoC. */
#define FSL_FEATURE_SOC_FTMRE_COUNT (0)
/* @brief FTMRH availability on the SoC. */
#define FSL_FEATURE_SOC_FTMRH_COUNT (0)
/* @brief GPIO availability on the SoC. */
#define FSL_FEATURE_SOC_GPIO_COUNT (13)
/* @brief HSADC availability on the SoC. */
#define FSL_FEATURE_SOC_HSADC_COUNT (0)
/* @brief I2C availability on the SoC. */
#define FSL_FEATURE_SOC_I2C_COUNT (2)
/* @brief I2S availability on the SoC. */
#define FSL_FEATURE_SOC_I2S_COUNT (0)
/* @brief ICS availability on the SoC. */
#define FSL_FEATURE_SOC_ICS_COUNT (0)
/* @brief IRQ availability on the SoC. */
#define FSL_FEATURE_SOC_IRQ_COUNT (0)
/* @brief KBI availability on the SoC. */
#define FSL_FEATURE_SOC_KBI_COUNT (0)
/* @brief SLCD availability on the SoC. */
#define FSL_FEATURE_SOC_SLCD_COUNT (1)
/* @brief LCDC availability on the SoC. */
#define FSL_FEATURE_SOC_LCDC_COUNT (0)
/* @brief LDO availability on the SoC. */
#define FSL_FEATURE_SOC_LDO_COUNT (0)
/* @brief LLWU availability on the SoC. */
#define FSL_FEATURE_SOC_LLWU_COUNT (1)
/* @brief LMEM availability on the SoC. */
#define FSL_FEATURE_SOC_LMEM_COUNT (0)
/* @brief LPSCI availability on the SoC. */
#define FSL_FEATURE_SOC_LPSCI_COUNT (0)
/* @brief LPTMR availability on the SoC. */
#define FSL_FEATURE_SOC_LPTMR_COUNT (1)
/* @brief LPTPM availability on the SoC. */
#define FSL_FEATURE_SOC_LPTPM_COUNT (0)
/* @brief LPUART availability on the SoC. */
#define FSL_FEATURE_SOC_LPUART_COUNT (1)
/* @brief LTC availability on the SoC. */
#define FSL_FEATURE_SOC_LTC_COUNT (0)
/* @brief MC availability on the SoC. */
#define FSL_FEATURE_SOC_MC_COUNT (0)
/* @brief MCG availability on the SoC. */
#define FSL_FEATURE_SOC_MCG_COUNT (1)
/* @brief MCGLITE availability on the SoC. */
#define FSL_FEATURE_SOC_MCGLITE_COUNT (0)
/* @brief MCM availability on the SoC. */
#define FSL_FEATURE_SOC_MCM_COUNT (1)
/* @brief MMAU availability on the SoC. */
#define FSL_FEATURE_SOC_MMAU_COUNT (1)
/* @brief MMDVSQ availability on the SoC. */
#define FSL_FEATURE_SOC_MMDVSQ_COUNT (0)
/* @brief MPU availability on the SoC. */
#define FSL_FEATURE_SOC_MPU_COUNT (1)
/* @brief MSCAN availability on the SoC. */
#define FSL_FEATURE_SOC_MSCAN_COUNT (0)
/* @brief MTB availability on the SoC. */
#define FSL_FEATURE_SOC_MTB_COUNT (1)
/* @brief MTBDWT availability on the SoC. */
#define FSL_FEATURE_SOC_MTBDWT_COUNT (1)
/* @brief NFC availability on the SoC. */
#define FSL_FEATURE_SOC_NFC_COUNT (0)
/* @brief OPAMP availability on the SoC. */
#define FSL_FEATURE_SOC_OPAMP_COUNT (0)
/* @brief OSC availability on the SoC. */
#define FSL_FEATURE_SOC_OSC_COUNT (1)
/* @brief OTFAD availability on the SoC. */
#define FSL_FEATURE_SOC_OTFAD_COUNT (0)
/* @brief PDB availability on the SoC. */
#define FSL_FEATURE_SOC_PDB_COUNT (1)
/* @brief PGA availability on the SoC. */
#define FSL_FEATURE_SOC_PGA_COUNT (0)
/* @brief PIT availability on the SoC. */
#define FSL_FEATURE_SOC_PIT_COUNT (2)
/* @brief PMC availability on the SoC. */
#define FSL_FEATURE_SOC_PMC_COUNT (1)
/* @brief PORT availability on the SoC. */
#define FSL_FEATURE_SOC_PORT_COUNT (13)
/* @brief PWM availability on the SoC. */
#define FSL_FEATURE_SOC_PWM_COUNT (0)
/* @brief PWT availability on the SoC. */
#define FSL_FEATURE_SOC_PWT_COUNT (0)
/* @brief QuadSPIO availability on the SoC. */
#define FSL_FEATURE_SOC_QuadSPIO_COUNT (0)
/* @brief RCM availability on the SoC. */
#define FSL_FEATURE_SOC_RCM_COUNT (1)
/* @brief RFSYS availability on the SoC. */
#define FSL_FEATURE_SOC_RFSYS_COUNT (0)
/* @brief RFVBAT availability on the SoC. */
#define FSL_FEATURE_SOC_RFVBAT_COUNT (0)
/* @brief RNG availability on the SoC. */
#define FSL_FEATURE_SOC_RNG_COUNT (1)
/* @brief RNGB availability on the SoC. */
#define FSL_FEATURE_SOC_RNGB_COUNT (0)
/* @brief ROM availability on the SoC. */
#define FSL_FEATURE_SOC_ROM_COUNT (1)
/* @brief RSIM availability on the SoC. */
#define FSL_FEATURE_SOC_RSIM_COUNT (0)
/* @brief RTC availability on the SoC. */
#define FSL_FEATURE_SOC_RTC_COUNT (1)
/* @brief SCI availability on the SoC. */
#define FSL_FEATURE_SOC_SCI_COUNT (0)
/* @brief SDHC availability on the SoC. */
#define FSL_FEATURE_SOC_SDHC_COUNT (0)
/* @brief SDRAM availability on the SoC. */
#define FSL_FEATURE_SOC_SDRAM_COUNT (0)
/* @brief SIM availability on the SoC. */
#define FSL_FEATURE_SOC_SIM_COUNT (1)
/* @brief SMC availability on the SoC. */
#define FSL_FEATURE_SOC_SMC_COUNT (1)
/* @brief SPI availability on the SoC. */
#define FSL_FEATURE_SOC_SPI_COUNT (2)
/* @brief TMR availability on the SoC. */
#define FSL_FEATURE_SOC_TMR_COUNT (4)
/* @brief TPM availability on the SoC. */
#define FSL_FEATURE_SOC_TPM_COUNT (0)
/* @brief TRIAMP availability on the SoC. */
#define FSL_FEATURE_SOC_TRIAMP_COUNT (0)
/* @brief TRNG availability on the SoC. */
#define FSL_FEATURE_SOC_TRNG_COUNT (0)
/* @brief TSI availability on the SoC. */
#define FSL_FEATURE_SOC_TSI_COUNT (0)
/* @brief UART availability on the SoC. */
#define FSL_FEATURE_SOC_UART_COUNT (4)
/* @brief USB availability on the SoC. */
#define FSL_FEATURE_SOC_USB_COUNT (0)
/* @brief USBDCD availability on the SoC. */
#define FSL_FEATURE_SOC_USBDCD_COUNT (0)
/* @brief USBHSDCD availability on the SoC. */
#define FSL_FEATURE_SOC_USBHSDCD_COUNT (0)
/* @brief USBPHY availability on the SoC. */
#define FSL_FEATURE_SOC_USBPHY_COUNT (0)
/* @brief VREF availability on the SoC. */
#define FSL_FEATURE_SOC_VREF_COUNT (1)
/* @brief WDOG availability on the SoC. */
#define FSL_FEATURE_SOC_WDOG_COUNT (1)
/* @brief XBAR availability on the SoC. */
#define FSL_FEATURE_SOC_XBAR_COUNT (1)
/* @brief XCVR availability on the SoC. */
#define FSL_FEATURE_SOC_XCVR_COUNT (0)
/* @brief ZLL availability on the SoC. */
#define FSL_FEATURE_SOC_ZLL_COUNT (0)

/* CRC module features */

/* @brief Has data register with name CRC */
#define FSL_FEATURE_CRC_HAS_CRC_REG (0)

/* DMA module features */

/* @brief Total number of DMA channels on all modules. */
#define FSL_FEATURE_DMA_DMAMUX_CHANNELS (DMA_INSTANCE_COUNT * 4)

/* DMAMUX module features */

/* @brief Number of DMA channels (related to number of register CHCFGn). */
#define FSL_FEATURE_DMAMUX_MODULE_CHANNEL (4)
/* @brief Total number of DMA channels on all modules. */
#define FSL_FEATURE_DMAMUX_DMAMUX_CHANNELS (DMAMUX_INSTANCE_COUNT * 4)
/* @brief Has the periodic trigger capability for the triggered DMA channel 0 (register bit CHCFG0[TRIG]). */
#define FSL_FEATURE_DMAMUX_HAS_TRIG (1)

/* EWM module features */

/* @brief Has clock prescaler (register CLKPRESCALER). */
#define FSL_FEATURE_EWM_HAS_PRESCALER  (1)

/* FLASH module features */

/* @brief Is of type FTFA. */
#define FSL_FEATURE_FLASH_IS_FTFA (1)
/* @brief Is of type FTFE. */
#define FSL_FEATURE_FLASH_IS_FTFE (0)
/* @brief Is of type FTFL. */
#define FSL_FEATURE_FLASH_IS_FTFL (0)
/* @brief Has flags indicating the status of the FlexRAM (register bits FCNFG[EEERDY], FCNFG[RAMRDY] and FCNFG[PFLSH]). */
#define FSL_FEATURE_FLASH_HAS_FLEX_RAM_FLAGS (0)
/* @brief Has program flash swapping status flag (register bit FCNFG[SWAP]). */
#define FSL_FEATURE_FLASH_HAS_PFLASH_SWAPPING_STATUS_FLAG (0)
/* @brief Has EEPROM region protection (register FEPROT). */
#define FSL_FEATURE_FLASH_HAS_EEROM_REGION_PROTECTION (0)
/* @brief Has data flash region protection (register FDPROT). */
#define FSL_FEATURE_FLASH_HAS_DATA_FLASH_REGION_PROTECTION (0)
/* @brief Has flash access control (registers XACCHn, SACCHn, where n is a number, FACSS and FACSN). */
#define FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL (0)
/* @brief Has flash cache control in FMC module. */
#define FSL_FEATURE_FLASH_HAS_FMC_FLASH_CACHE_CONTROLS (0)
/* @brief Has flash cache control in MCM module. */
#define FSL_FEATURE_FLASH_HAS_MCM_FLASH_CACHE_CONTROLS (1)
/* @brief P-Flash start address. */
#define FSL_FEATURE_FLASH_PFLASH_START_ADDRESS (0x00000000)
/* @brief P-Flash block count. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_COUNT (1)
/* @brief P-Flash block size. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_SIZE (262144)
/* @brief P-Flash sector size. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE (2048)
/* @brief P-Flash write unit size. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE (4)
/* @brief P-Flash data path width. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_DATA_PATH_WIDTH (8)
/* @brief P-Flash block swap feature. */
#define FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP (0)
/* @brief Has FlexNVM memory. */
#define FSL_FEATURE_FLASH_HAS_FLEX_NVM (0)
/* @brief FlexNVM start address. (Valid only if FlexNVM is available.) */
#define FSL_FEATURE_FLASH_FLEX_NVM_START_ADDRESS (0x00000000)
/* @brief FlexNVM block count. */
#define FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_COUNT (0)
/* @brief FlexNVM block size. */
#define FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_SIZE (0)
/* @brief FlexNVM sector size. */
#define FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_SECTOR_SIZE (0)
/* @brief FlexNVM write unit size. */
#define FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_WRITE_UNIT_SIZE (0)
/* @brief FlexNVM data path width. */
#define FSL_FEATURE_FLASH_FLEX_BLOCK_DATA_PATH_WIDTH (0)
/* @brief Has FlexRAM memory. */
#define FSL_FEATURE_FLASH_HAS_FLEX_RAM (0)
/* @brief FlexRAM start address. (Valid only if FlexRAM is available.) */
#define FSL_FEATURE_FLASH_FLEX_RAM_START_ADDRESS (0x00000000)
/* @brief FlexRAM size. */
#define FSL_FEATURE_FLASH_FLEX_RAM_SIZE (0)
/* @brief Has 0x00 Read 1s Block command. */
#define FSL_FEATURE_FLASH_HAS_READ_1S_BLOCK_CMD (0)
/* @brief Has 0x01 Read 1s Section command. */
#define FSL_FEATURE_FLASH_HAS_READ_1S_SECTION_CMD (1)
/* @brief Has 0x02 Program Check command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_CHECK_CMD (1)
/* @brief Has 0x03 Read Resource command. */
#define FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD (1)
/* @brief Has 0x06 Program Longword command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_LONGWORD_CMD (1)
/* @brief Has 0x07 Program Phrase command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_PHRASE_CMD (0)
/* @brief Has 0x08 Erase Flash Block command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_FLASH_BLOCK_CMD (0)
/* @brief Has 0x09 Erase Flash Sector command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_FLASH_SECTOR_CMD (1)
/* @brief Has 0x0B Program Section command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD (0)
/* @brief Has 0x40 Read 1s All Blocks command. */
#define FSL_FEATURE_FLASH_HAS_READ_1S_ALL_BLOCKS_CMD (0)
/* @brief Has 0x41 Read Once command. */
#define FSL_FEATURE_FLASH_HAS_READ_ONCE_CMD (1)
/* @brief Has 0x43 Program Once command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_ONCE_CMD (1)
/* @brief Has 0x44 Erase All Blocks command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_CMD (0)
/* @brief Has 0x45 Verify Backdoor Access Key command. */
#define FSL_FEATURE_FLASH_HAS_VERIFY_BACKDOOR_ACCESS_KEY_CMD (1)
/* @brief Has 0x46 Swap Control command. */
#define FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD (0)
/* @brief Has 0x80 Program Partition command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_PARTITION_CMD (0)
/* @brief Has 0x81 Set FlexRAM Function command. */
#define FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD (0)
/* @brief P-Flash Erase/Read 1st all block command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_CMD_ADDRESS_ALIGMENT (4)
/* @brief P-Flash Erase sector command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT (8)
/* @brief P-Flash Rrogram/Verify section command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT (8)
/* @brief P-Flash Read resource command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_RESOURCE_CMD_ADDRESS_ALIGMENT (4)
/* @brief P-Flash Program check command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_CHECK_CMD_ADDRESS_ALIGMENT (4)
/* @brief P-Flash Program check command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_SWAP_CONTROL_CMD_ADDRESS_ALIGMENT (0)
/* @brief FlexNVM Erase/Read 1st all block command address alignment. */
#define FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_CMD_ADDRESS_ALIGMENT (0)
/* @brief FlexNVM Erase sector command address alignment. */
#define FSL_FEATURE_FLASH_FLEX_NVM_SECTOR_CMD_ADDRESS_ALIGMENT (0)
/* @brief FlexNVM Rrogram/Verify section command address alignment. */
#define FSL_FEATURE_FLASH_FLEX_NVM_SECTION_CMD_ADDRESS_ALIGMENT (0)
/* @brief FlexNVM Read resource command address alignment. */
#define FSL_FEATURE_FLASH_FLEX_NVM_RESOURCE_CMD_ADDRESS_ALIGMENT (0)
/* @brief FlexNVM Program check command address alignment. */
#define FSL_FEATURE_FLASH_FLEX_NVM_CHECK_CMD_ADDRESS_ALIGMENT (0)
/* @brief FlexNVM partition code 0000 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0000 (0xFFFFFFFF)
/* @brief FlexNVM partition code 0001 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0001 (0xFFFFFFFF)
/* @brief FlexNVM partition code 0010 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0010 (0xFFFFFFFF)
/* @brief FlexNVM partition code 0011 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0011 (0xFFFFFFFF)
/* @brief FlexNVM partition code 0100 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0100 (0xFFFFFFFF)
/* @brief FlexNVM partition code 0101 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0101 (0xFFFFFFFF)
/* @brief FlexNVM partition code 0110 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0110 (0xFFFFFFFF)
/* @brief FlexNVM partition code 0111 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0111 (0xFFFFFFFF)
/* @brief FlexNVM partition code 1000 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1000 (0xFFFFFFFF)
/* @brief FlexNVM partition code 1001 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1001 (0xFFFFFFFF)
/* @brief FlexNVM partition code 1010 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1010 (0xFFFFFFFF)
/* @brief FlexNVM partition code 1011 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1011 (0xFFFFFFFF)
/* @brief FlexNVM partition code 1100 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1100 (0xFFFFFFFF)
/* @brief FlexNVM partition code 1101 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1101 (0xFFFFFFFF)
/* @brief FlexNVM partition code 1110 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1110 (0xFFFFFFFF)
/* @brief FlexNVM partition code 1111 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1111 (0xFFFFFFFF)
/* @brief Emulated eeprom size code 0000 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0000 (0xFFFF)
/* @brief Emulated eeprom size code 0001 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0001 (0xFFFF)
/* @brief Emulated eeprom size code 0010 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0010 (0xFFFF)
/* @brief Emulated eeprom size code 0011 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0011 (0xFFFF)
/* @brief Emulated eeprom size code 0100 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0100 (0xFFFF)
/* @brief Emulated eeprom size code 0101 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0101 (0xFFFF)
/* @brief Emulated eeprom size code 0110 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0110 (0xFFFF)
/* @brief Emulated eeprom size code 0111 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0111 (0xFFFF)
/* @brief Emulated eeprom size code 1000 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1000 (0xFFFF)
/* @brief Emulated eeprom size code 1001 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1001 (0xFFFF)
/* @brief Emulated eeprom size code 1010 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1010 (0xFFFF)
/* @brief Emulated eeprom size code 1011 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1011 (0xFFFF)
/* @brief Emulated eeprom size code 1100 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1100 (0xFFFF)
/* @brief Emulated eeprom size code 1101 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1101 (0xFFFF)
/* @brief Emulated eeprom size code 1110 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1110 (0xFFFF)
/* @brief Emulated eeprom size code 1111 mapping to emulated eeprom size in bytes (0xFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1111 (0xFFFF)

/* GPIO module features */

/* @brief Has fast (single cycle) access capability via a dedicated memory region. */
#define FSL_FEATURE_GPIO_HAS_FAST_GPIO (0)
/* @brief Has port input disable register (PIDR). */
#define FSL_FEATURE_GPIO_HAS_INPUT_DISABLE (0)
/* @brief Has dedicated interrupt vector. */
#define FSL_FEATURE_GPIO_HAS_INTERRUPT_VECTOR (1)

/* I2C module features */

/* @brief Has System Management Bus support (registers SMB, A2, SLTL and SLTH). */
#define FSL_FEATURE_I2C_HAS_SMBUS (1)
/* @brief Maximum supported baud rate in kilobit per second. */
#define FSL_FEATURE_I2C_MAX_BAUD_KBPS (400)
/* @brief Is affected by errata with ID 6070 (repeat start cannot be generated if the F[MULT] bit field is set to a non-zero value). */
#define FSL_FEATURE_I2C_HAS_ERRATA_6070 (0)
/* @brief Has DMA support (register bit C1[DMAEN]). */
#define FSL_FEATURE_I2C_HAS_DMA_SUPPORT (1)
/* @brief Has I2C bus start and stop detection (register bits FLT[SSIE], FLT[STARTF] and FLT[STOPF]). */
#define FSL_FEATURE_I2C_HAS_START_STOP_DETECT (1)
/* @brief Has I2C bus stop detection (register bits FLT[STOPIE] and FLT[STOPF]). */
#define FSL_FEATURE_I2C_HAS_STOP_DETECT (0)
/* @brief Has I2C bus stop hold off (register bit FLT[SHEN]). */
#define FSL_FEATURE_I2C_HAS_STOP_HOLD_OFF (1)
/* @brief Maximum width of the glitch filter in number of bus clocks. */
#define FSL_FEATURE_I2C_MAX_GLITCH_FILTER_WIDTH (15)
/* @brief Has control of the drive capability of the I2C pins. */
#define FSL_FEATURE_I2C_HAS_HIGH_DRIVE_SELECTION (1)
/* @brief Has double buffering support (register S2). */
#define FSL_FEATURE_I2C_HAS_DOUBLE_BUFFERING (1)

/* SLCD module features */

/* @brief Has Multi Alternate Clock Source (register bit GCR[ATLSOURCE]).  */
#define FSL_FEATURE_SLCD_HAS_MULTI_ALTERNATE_CLOCK_SOURCE (0)
/* @brief Has fast frame rate (register bit GCR[FFR]). */
#define FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE (0)
/* @brief Has frame frequency interrupt (register bit GCR[LCDIEN]). */
#define FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT (1)
/* @brief Has pad safe (register bit GCR[PADSAFE]). */
#define FSL_FEATURE_SLCD_HAS_PAD_SAFE (0)
/* @brief Total pin number on LCD. */
#define FSL_FEATURE_SLCD_HAS_PIN_NUM (64)
/* @brief Total phase number on SLCD. */
#define FSL_FEATURE_SLCD_HAS_PHASE_NUM (8)

/* LLWU module features */

#if defined(CPU_MKM34Z256VLL7)
    /* @brief Maximum number of pins (maximal index plus one) connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN (23)
    /* @brief Has pins 8-15 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_EXTERNAL_PIN_GROUP2 (1)
    /* @brief Maximum number of internal modules connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE (6)
    /* @brief Number of digital filters. */
    #define FSL_FEATURE_LLWU_HAS_PIN_FILTER (2)
    /* @brief Has MF5 register. */
    #define FSL_FEATURE_LLWU_HAS_MF (1)
    /* @brief Has possibility to enable reset in low leakage power mode and enable digital filter for RESET pin (register LLWU_RST). */
    #define FSL_FEATURE_LLWU_HAS_RESET_ENABLE (0)
    /* @brief Has external pin 0 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN0 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN0_GPIO_IDX (GPIOG_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN0_GPIO_PIN (6)
    /* @brief Has external pin 1 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN1 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN1_GPIO_IDX (GPIOG_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN1_GPIO_PIN (2)
    /* @brief Has external pin 2 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN2 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN2_GPIO_IDX (GPIOG_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN2_GPIO_PIN (1)
    /* @brief Has external pin 3 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN3 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN3_GPIO_IDX (GPIOF_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN3_GPIO_PIN (6)
    /* @brief Has external pin 4 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN4 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN4_GPIO_IDX (GPIOF_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN4_GPIO_PIN (0)
    /* @brief Has external pin 5 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN5 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN5_GPIO_IDX (GPIOE_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN5_GPIO_PIN (6)
    /* @brief Has external pin 6 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN6 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN6_GPIO_IDX (GPIOE_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN6_GPIO_PIN (5)
    /* @brief Has external pin 7 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN7 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN7_GPIO_IDX (GPIOD_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN7_GPIO_PIN (7)
    /* @brief Has external pin 8 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN8 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN8_GPIO_IDX (GPIOD_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN8_GPIO_PIN (6)
    /* @brief Has external pin 9 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN9 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN9_GPIO_IDX (GPIOD_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN9_GPIO_PIN (4)
    /* @brief Has external pin 10 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN10 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN10_GPIO_IDX (GPIOD_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN10_GPIO_PIN (2)
    /* @brief Has external pin 11 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN11 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN11_GPIO_IDX (GPIOD_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN11_GPIO_PIN (0)
    /* @brief Has external pin 12 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN12 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN12_GPIO_IDX (GPIOC_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN12_GPIO_PIN (5)
    /* @brief Has external pin 13 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN13 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN13_GPIO_IDX (GPIOC_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN13_GPIO_PIN (3)
    /* @brief Has external pin 14 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN14 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN14_GPIO_IDX (GPIOA_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN14_GPIO_PIN (6)
    /* @brief Has external pin 15 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN15 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN15_GPIO_IDX (GPIOA_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN15_GPIO_PIN (4)
    /* @brief Has external pin 16 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN16 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN16_GPIO_IDX (GPIOA_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN16_GPIO_PIN (0)
    /* @brief Has external pin 17 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN17 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN17_GPIO_IDX (GPIOB_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN17_GPIO_PIN (1)
    /* @brief Has external pin 18 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN18 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN18_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN18_GPIO_PIN (0)
    /* @brief Has external pin 19 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN19 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN19_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN19_GPIO_PIN (0)
    /* @brief Has external pin 20 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN20 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN20_GPIO_IDX (GPIOF_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN20_GPIO_PIN (3)
    /* @brief Has external pin 21 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN21 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN21_GPIO_IDX (GPIOI_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN21_GPIO_PIN (0)
    /* @brief Has external pin 22 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN22 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN22_GPIO_IDX (GPIOI_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN22_GPIO_PIN (2)
    /* @brief Has external pin 23 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN23 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN23_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN23_GPIO_PIN (0)
    /* @brief Has external pin 24 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN24 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN24_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN24_GPIO_PIN (0)
    /* @brief Has external pin 25 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN25 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN25_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN25_GPIO_PIN (0)
    /* @brief Has external pin 26 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN26 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN26_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN26_GPIO_PIN (0)
    /* @brief Has external pin 27 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN27 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN27_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN27_GPIO_PIN (0)
    /* @brief Has external pin 28 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN28 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN28_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN28_GPIO_PIN (0)
    /* @brief Has external pin 29 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN29 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN29_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN29_GPIO_PIN (0)
    /* @brief Has external pin 30 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN30 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN30_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN30_GPIO_PIN (0)
    /* @brief Has external pin 31 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN31 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN31_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN31_GPIO_PIN (0)
    /* @brief Has internal module 0 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE0 (1)
    /* @brief Has internal module 1 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE1 (1)
    /* @brief Has internal module 2 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE2 (1)
    /* @brief Has internal module 3 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE3 (1)
    /* @brief Has internal module 4 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE4 (1)
    /* @brief Has internal module 5 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE5 (1)
    /* @brief Has internal module 6 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE6 (0)
    /* @brief Has internal module 7 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE7 (0)
#elif defined(CPU_MKM34Z256VLQ7)
    /* @brief Maximum number of pins (maximal index plus one) connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN (24)
    /* @brief Has pins 8-15 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_EXTERNAL_PIN_GROUP2 (1)
    /* @brief Maximum number of internal modules connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE (6)
    /* @brief Number of digital filters. */
    #define FSL_FEATURE_LLWU_HAS_PIN_FILTER (2)
    /* @brief Has MF5 register. */
    #define FSL_FEATURE_LLWU_HAS_MF (1)
    /* @brief Has possibility to enable reset in low leakage power mode and enable digital filter for RESET pin (register LLWU_RST). */
    #define FSL_FEATURE_LLWU_HAS_RESET_ENABLE (0)
    /* @brief Has external pin 0 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN0 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN0_GPIO_IDX (GPIOG_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN0_GPIO_PIN (6)
    /* @brief Has external pin 1 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN1 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN1_GPIO_IDX (GPIOG_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN1_GPIO_PIN (2)
    /* @brief Has external pin 2 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN2 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN2_GPIO_IDX (GPIOG_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN2_GPIO_PIN (1)
    /* @brief Has external pin 3 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN3 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN3_GPIO_IDX (GPIOF_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN3_GPIO_PIN (6)
    /* @brief Has external pin 4 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN4 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN4_GPIO_IDX (GPIOF_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN4_GPIO_PIN (0)
    /* @brief Has external pin 5 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN5 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN5_GPIO_IDX (GPIOE_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN5_GPIO_PIN (6)
    /* @brief Has external pin 6 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN6 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN6_GPIO_IDX (GPIOE_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN6_GPIO_PIN (5)
    /* @brief Has external pin 7 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN7 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN7_GPIO_IDX (GPIOD_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN7_GPIO_PIN (7)
    /* @brief Has external pin 8 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN8 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN8_GPIO_IDX (GPIOD_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN8_GPIO_PIN (6)
    /* @brief Has external pin 9 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN9 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN9_GPIO_IDX (GPIOD_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN9_GPIO_PIN (4)
    /* @brief Has external pin 10 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN10 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN10_GPIO_IDX (GPIOD_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN10_GPIO_PIN (2)
    /* @brief Has external pin 11 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN11 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN11_GPIO_IDX (GPIOD_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN11_GPIO_PIN (0)
    /* @brief Has external pin 12 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN12 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN12_GPIO_IDX (GPIOC_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN12_GPIO_PIN (5)
    /* @brief Has external pin 13 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN13 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN13_GPIO_IDX (GPIOC_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN13_GPIO_PIN (3)
    /* @brief Has external pin 14 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN14 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN14_GPIO_IDX (GPIOA_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN14_GPIO_PIN (6)
    /* @brief Has external pin 15 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN15 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN15_GPIO_IDX (GPIOA_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN15_GPIO_PIN (4)
    /* @brief Has external pin 16 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN16 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN16_GPIO_IDX (GPIOA_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN16_GPIO_PIN (0)
    /* @brief Has external pin 17 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN17 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN17_GPIO_IDX (GPIOB_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN17_GPIO_PIN (1)
    /* @brief Has external pin 18 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN18 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN18_GPIO_IDX (GPIOJ_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN18_GPIO_PIN (6)
    /* @brief Has external pin 19 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN19 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN19_GPIO_IDX (GPIOK_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN19_GPIO_PIN (3)
    /* @brief Has external pin 20 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN20 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN20_GPIO_IDX (GPIOF_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN20_GPIO_PIN (3)
    /* @brief Has external pin 21 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN21 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN21_GPIO_IDX (GPIOI_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN21_GPIO_PIN (0)
    /* @brief Has external pin 22 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN22 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN22_GPIO_IDX (GPIOI_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN22_GPIO_PIN (2)
    /* @brief Has external pin 23 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN23 (1)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN23_GPIO_IDX (GPIOL_IDX)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN23_GPIO_PIN (5)
    /* @brief Has external pin 24 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN24 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN24_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN24_GPIO_PIN (0)
    /* @brief Has external pin 25 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN25 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN25_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN25_GPIO_PIN (0)
    /* @brief Has external pin 26 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN26 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN26_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN26_GPIO_PIN (0)
    /* @brief Has external pin 27 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN27 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN27_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN27_GPIO_PIN (0)
    /* @brief Has external pin 28 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN28 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN28_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN28_GPIO_PIN (0)
    /* @brief Has external pin 29 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN29 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN29_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN29_GPIO_PIN (0)
    /* @brief Has external pin 30 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN30 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN30_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN30_GPIO_PIN (0)
    /* @brief Has external pin 31 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN31 (0)
    /* @brief Index of port of external pin. */
    #define FSL_FEATURE_LLWU_PIN31_GPIO_IDX (0)
    /* @brief Number of external pin port on specified port. */
    #define FSL_FEATURE_LLWU_PIN31_GPIO_PIN (0)
    /* @brief Has internal module 0 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE0 (1)
    /* @brief Has internal module 1 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE1 (1)
    /* @brief Has internal module 2 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE2 (1)
    /* @brief Has internal module 3 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE3 (1)
    /* @brief Has internal module 4 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE4 (1)
    /* @brief Has internal module 5 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE5 (1)
    /* @brief Has internal module 6 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE6 (0)
    /* @brief Has internal module 7 connected to LLWU device. */
    #define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE7 (0)
#endif

/* LPTMR module features */

/* @brief Has shared interrupt handler with another LPTMR module. */
#define FSL_FEATURE_LPTMR_HAS_SHARED_IRQ_HANDLER (0)

/* LPUART module features */

/* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
#define FSL_FEATURE_LPUART_HAS_IRQ_EXTENDED_FUNCTIONS (0)
/* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_LOW_POWER_UART_SUPPORT (1)
/* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_LPUART_HAS_FIFO (0)
/* @brief Has 32-bit register MODIR */
#define FSL_FEATURE_LPUART_HAS_MODIR (1)
/* @brief Hardware flow control (RTS, CTS) is supported. */
#define FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT (1)
/* @brief Infrared (modulation) is supported. */
#define FSL_FEATURE_LPUART_HAS_IR_SUPPORT (1)
/* @brief 2 bits long stop bit is available. */
#define FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
/* @brief Maximal data width without parity bit. */
#define FSL_FEATURE_LPUART_HAS_10BIT_DATA_SUPPORT (1)
/* @brief Baud rate fine adjustment is available. */
#define FSL_FEATURE_LPUART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (0)
/* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (1)
/* @brief Baud rate oversampling is available. */
#define FSL_FEATURE_LPUART_HAS_RX_RESYNC_SUPPORT (1)
/* @brief Baud rate oversampling is available. */
#define FSL_FEATURE_LPUART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (1)
/* @brief Peripheral type. */
#define FSL_FEATURE_LPUART_IS_SCI (1)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_LPUART_FIFO_SIZE (0)
/* @brief Maximal data width without parity bit. */
#define FSL_FEATURE_LPUART_MAX_DATA_WIDTH_WITH_NO_PARITY (10)
/* @brief Maximal data width with parity bit. */
#define FSL_FEATURE_LPUART_MAX_DATA_WIDTH_WITH_PARITY (9)
/* @brief Supports two match addresses to filter incoming frames. */
#define FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING (1)
/* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_DMA_ENABLE (1)
/* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
#define FSL_FEATURE_LPUART_HAS_DMA_SELECT (0)
/* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_BIT_ORDER_SELECT (1)
/* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
#define FSL_FEATURE_LPUART_HAS_SMART_CARD_SUPPORT (0)
/* @brief Has improved smart card (ISO7816 protocol) support. */
#define FSL_FEATURE_LPUART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
/* @brief Has local operation network (CEA709.1-B protocol) support. */
#define FSL_FEATURE_LPUART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
/* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
#define FSL_FEATURE_LPUART_HAS_32BIT_REGISTERS (1)
/* @brief Lin break detect available (has bit BDH[LBKDIE]). */
#define FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT (0)
/* @brief UART stops in Wait mode available (has bit C1[UARTSWAI]). */
#define FSL_FEATURE_LPUART_HAS_WAIT_MODE_OPERATION (0)
/* @brief Has separate DMA RX and TX requests. */
#define FSL_FEATURE_LPUART_HAS_SEPARATE_DMA_RX_TX_REQn(x) \
    ((x) == 0 ? (1) : (-1))

/* MCG module features */

/* @brief PRDIV base value (divider of register bit field [PRDIV] zero value). */
#define FSL_FEATURE_MCG_PLL_PRDIV_BASE (0)
/* @brief Maximum PLL external reference divider value (max. value of register bit field C5[PRVDIV]). */
#define FSL_FEATURE_MCG_PLL_PRDIV_MAX (0)
/* @brief VCO divider base value (multiply factor of register bit field C6[VDIV] zero value). */
#define FSL_FEATURE_MCG_PLL_VDIV_BASE (0)
/* @brief PLL reference clock low range. OSCCLK/PLL_R. */
#define FSL_FEATURE_MCG_PLL_REF_MIN (0)
/* @brief PLL reference clock high range. OSCCLK/PLL_R. */
#define FSL_FEATURE_MCG_PLL_REF_MAX (0)
/* @brief The PLL clock is divided by 2 before VCO divider. */
#define FSL_FEATURE_MCG_HAS_PLL_INTERNAL_DIV (0)
/* @brief FRDIV supports 1280. */
#define FSL_FEATURE_MCG_FRDIV_SUPPORT_1280 (1)
/* @brief FRDIV supports 1536. */
#define FSL_FEATURE_MCG_FRDIV_SUPPORT_1536 (1)
/* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection in the SIM module. */
#define FSL_FEATURE_MCG_HAS_PLL_EXTRA_DIV (0)
/* @brief Has 32kHz RTC external reference clock (register bits C8[LOCS1], C8[CME1], C8[LOCRE1] and RTC module are present). */
#define FSL_FEATURE_MCG_HAS_RTC_32K (1)
/* @brief Has PLL1 external reference clock (registers C10, C11, C12, S2). */
#define FSL_FEATURE_MCG_HAS_PLL1 (0)
/* @brief Has 48MHz internal oscillator. */
#define FSL_FEATURE_MCG_HAS_IRC_48M (0)
/* @brief Has OSC1 external oscillator (registers C10, C11, C12, S2). */
#define FSL_FEATURE_MCG_HAS_OSC1 (0)
/* @brief Has fast internal reference clock fine trim (register bit C2[FCFTRIM]). */
#define FSL_FEATURE_MCG_HAS_FCFTRIM (0)
/* @brief Has PLL loss of lock reset (register bit C8[LOLRE]). */
#define FSL_FEATURE_MCG_HAS_LOLRE (1)
/* @brief Has MCG OSC clock selection (register bit C7[OSCSEL]). */
#define FSL_FEATURE_MCG_USE_OSCSEL (1)
/* @brief Has PLL external reference selection (register bits C5[PLLREFSEL0] and C11[PLLREFSEL1]). */
#define FSL_FEATURE_MCG_USE_PLLREFSEL (0)
/* @brief TBD */
#define FSL_FEATURE_MCG_USE_SYSTEM_CLOCK (0)
/* @brief Has phase-locked loop (PLL) (register C5 and bits C6[VDIV], C6[PLLS], C6[LOLIE0], S[PLLST], S[LOCK0], S[LOLS]). */
#define FSL_FEATURE_MCG_HAS_PLL (1)
/* @brief Has phase-locked loop (PLL) PRDIV (register C5[PRDIV]. */
#define FSL_FEATURE_MCG_HAS_PLL_PRDIV (0)
/* @brief Has phase-locked loop (PLL) VDIV (register C6[VDIV]. */
#define FSL_FEATURE_MCG_HAS_PLL_VDIV (0)
/* @brief PLL/OSC related register bit fields have PLL/OSC index in their name. */
#define FSL_FEATURE_MCG_HAS_PLL_OSC_INDEX (1)
/* @brief Has frequency-locked loop (FLL) (register ATCVH, ATCVL and bits C1[IREFS], C1[FRDIV]). */
#define FSL_FEATURE_MCG_HAS_FLL (1)
/* @brief Has PLL external to MCG (C9[PLL_CME], C9[PLL_LOCRE], C9[EXT_PLL_LOCS]). */
#define FSL_FEATURE_MCG_HAS_EXTERNAL_PLL (0)
/* @brief Has crystal oscillator or external reference clock low power controls (register bits C2[HGO], C2[RANGE]). */
#define FSL_FEATURE_MCG_HAS_EXT_REF_LOW_POWER_CONTROL (1)
/* @brief Has PLL/FLL selection as MCG output (register bit C6[PLLS]). */
#define FSL_FEATURE_MCG_HAS_PLL_FLL_SELECTION (1)
/* @brief Has PLL output selection (PLL0/PLL1, PLL/external PLL) (register bit C11[PLLCS]). */
#define FSL_FEATURE_MCG_HAS_PLL_OUTPUT_SELECTION (0)
/* @brief Has automatic trim machine (registers ATCVH, ATCVL and bits SC[ATMF], SC[ATMS], SC[ATME]). */
#define FSL_FEATURE_MCG_HAS_AUTO_TRIM_MACHINE (1)
/* @brief Has external clock monitor (register bit C6[CME]). */
#define FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR (1)
/* @brief Has low frequency internal reference clock (IRC) (registers LTRIMRNG, LFRIM, LSTRIM and bit MC[LIRC_DIV2]). */
#define FSL_FEATURE_MCG_HAS_LOW_FREQ_IRC (0)
/* @brief Has high frequency internal reference clock (IRC) (registers HCTRIM, HTTRIM, HFTRIM and bit MC[HIRCEN]). */
#define FSL_FEATURE_MCG_HAS_HIGH_FREQ_IRC (0)
/* @brief Has PEI mode or PBI mode. */
#define FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE (1)
/* @brief Reset clock mode is BLPI. */
#define FSL_FEATURE_MCG_RESET_IS_BLPI (1)

/* MPU module features */

/* @brief Specifies number of descriptors available. */
#define FSL_FEATURE_MPU_DESCRIPTOR_COUNT (8)
/* @brief Has process identifier support. */
#define FSL_FEATURE_MPU_HAS_PROCESS_IDENTIFIER (1)
/* @brief Has master 0. */
#define FSL_FEATURE_MPU_HAS_MASTER0 (1)
/* @brief Has master 1. */
#define FSL_FEATURE_MPU_HAS_MASTER1 (1)
/* @brief Has master 2. */
#define FSL_FEATURE_MPU_HAS_MASTER2 (1)
/* @brief Has master 3. */
#define FSL_FEATURE_MPU_HAS_MASTER3 (0)
/* @brief Has master 4. */
#define FSL_FEATURE_MPU_HAS_MASTER4 (0)
/* @brief Has master 5. */
#define FSL_FEATURE_MPU_HAS_MASTER5 (0)
/* @brief Has master 6. */
#define FSL_FEATURE_MPU_HAS_MASTER6 (0)
/* @brief Has master 7. */
#define FSL_FEATURE_MPU_HAS_MASTER7 (0)

/* interrupt module features */

/* @brief Lowest interrupt request number. */
#define FSL_FEATURE_INTERRUPT_IRQ_MIN (-14)
/* @brief Highest interrupt request number. */
#define FSL_FEATURE_INTERRUPT_IRQ_MAX (31)

/* OSC module features */

/* @brief Has OSC1 external oscillator. */
#define FSL_FEATURE_OSC_HAS_OSC1 (0)
/* @brief Has OSC0 external oscillator. */
#define FSL_FEATURE_OSC_HAS_OSC0 (0)
/* @brief Has OSC external oscillator (without index). */
#define FSL_FEATURE_OSC_HAS_OSC (0)
/* @brief Number of OSC external oscillators. */
#define FSL_FEATURE_OSC_OSC_COUNT (0)
/* @brief Has external reference clock divider (register bit field DIV[ERPS]). */
#define FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER (0)

/* PDB module features */

/* @brief Define the count of supporting ADC pre-trigger for each channel. */
#define FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT (4)
/* @brief Has DAC support. */
#define FSL_FEATURE_PDB_HAS_DAC (0)
/* @brief Has shared interrupt handler (has not individual interrupt handler for each channel). */
#define FSL_FEATURE_PDB_HAS_SHARED_IRQ_HANDLER (0)

/* PIT module features */

/* @brief Number of channels (related to number of registers LDVALn, CVALn, TCTRLn, TFLGn). */
#define FSL_FEATURE_PIT_TIMER_COUNT (2)
/* @brief Has lifetime timer (related to existence of registers LTMR64L and LTMR64H). */
#define FSL_FEATURE_PIT_HAS_LIFETIME_TIMER (0)
/* @brief Has chain mode (related to existence of register bit field TCTRLn[CHN]). */
#define FSL_FEATURE_PIT_HAS_CHAIN_MODE (1)
/* @brief Has shared interrupt handler (has not individual interrupt handler for each channel). */
#define FSL_FEATURE_PIT_HAS_SHARED_IRQ_HANDLER (1)

/* PMC module features */

/* @brief Has Bandgap Enable In VLPx Operation support. */
#define FSL_FEATURE_PMC_HAS_BGEN (1)
/* @brief Has Bandgap Buffer Drive Select. */
#define FSL_FEATURE_PMC_HAS_BGBDS (0)

/* PORT module features */

/* @brief Has control lock (register bit PCR[LK]). */
#define FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK (1)
/* @brief Has open drain control (register bit PCR[ODE]). */
#define FSL_FEATURE_PORT_HAS_OPEN_DRAIN (1)
/* @brief Has digital filter (registers DFER, DFCR and DFWR). */
#define FSL_FEATURE_PORT_HAS_DIGITAL_FILTER (1)
/* @brief Has DMA request (register bit field PCR[IRQC] values). */
#define FSL_FEATURE_PORT_HAS_DMA_REQUEST (1)
/* @brief Has pull resistor selection available. */
#define FSL_FEATURE_PORT_HAS_PULL_SELECTION (1)
/* @brief Has pull resistor enable (register bit PCR[PE]). */
#define FSL_FEATURE_PORT_HAS_PULL_ENABLE (1)
/* @brief Has slew rate control (register bit PCR[SRE]). */
#define FSL_FEATURE_PORT_HAS_SLEW_RATE (1)
/* @brief Has passive filter (register bit field PCR[PFE]). */
#define FSL_FEATURE_PORT_HAS_PASSIVE_FILTER (0)
/* @brief Has drive strength control (register bit PCR[DSE]). */
#define FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH (0)
/* @brief Has separate drive strength register (HDRVE). */
#define FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH_REGISTER (0)
/* @brief Has glitch filter (register IOFLT). */
#define FSL_FEATURE_PORT_HAS_GLITCH_FILTER (0)
/* @brief Defines width of PCR[MUX] field. */
#define FSL_FEATURE_PORT_PCR_MUX_WIDTH (3)
/* @brief Defines whether PCR[IRQC] bit-field has flag states. */
#define FSL_FEATURE_PORT_HAS_IRQC_FLAG (0)
/* @brief Defines whether PCR[IRQC] bit-field has trigger states. */
#define FSL_FEATURE_PORT_HAS_IRQC_TRIGGER (0)

/* RCM module features */

/* @brief Has Loss-of-Lock Reset support. */
#define FSL_FEATURE_RCM_HAS_LOL (1)
/* @brief Has Loss-of-Clock Reset support. */
#define FSL_FEATURE_RCM_HAS_LOC (1)
/* @brief Has JTAG generated Reset support. */
#define FSL_FEATURE_RCM_HAS_JTAG (0)
/* @brief Has EzPort generated Reset support. */
#define FSL_FEATURE_RCM_HAS_EZPORT (0)
/* @brief Has bit-field indicating EZP_MS_B pin state during last reset. */
#define FSL_FEATURE_RCM_HAS_EZPMS (0)
/* @brief Has boot ROM configuration, MR[BOOTROM], FM[FORCEROM] */
#define FSL_FEATURE_RCM_HAS_BOOTROM (0)
/* @brief Has sticky system reset status register RCM_SSRS0 and RCM_SSRS1. */
#define FSL_FEATURE_RCM_HAS_SSRS (1)

/* RTC module features */

/* @brief Has Tamper Direction Register support. */
#define FSL_FEATURE_RTC_HAS_TAMPER_DIRECTION (0)
/* @brief Has Tamper Queue Status and Control Register support. */
#define FSL_FEATURE_RTC_HAS_TAMPER_QUEUE (0)
/* @brief Whether RTC is IRTC. */
#define FSL_FEATURE_RTC_IS_IRTC (1)

/* SIM module features */

/* @brief Has USB FS divider. */
#define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
/* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
#define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
/* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
#define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (0)
/* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
#define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
/* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
/* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
#define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
/* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (0)
/* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
#define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (0)
/* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
#define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
/* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
#define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
/* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
#define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
/* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
#define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
/* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
#define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
/* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
#define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
/* @brief Number of LPUART modules (number of register bits LPUARTn, where n is a number, in register SCGC5). */
#define FSL_FEATURE_SIM_OPT_LPUART_COUNT (0)
/* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
#define FSL_FEATURE_SIM_OPT_UART_COUNT (4)
/* @brief Has UART0 open drain enable (register bit SOPT5[UART0ODE]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART0_ODE (0)
/* @brief Has UART1 open drain enable (register bit SOPT5[UART1ODE]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART1_ODE (0)
/* @brief Has UART2 open drain enable (register bit SOPT5[UART2ODE]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART2_ODE (0)
/* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
/* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
/* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
#define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
/* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
/* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
/* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
/* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
/* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (0)
/* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
#define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (0)
/* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (0)
/* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
#define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (0)
/* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (0)
/* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (0)
/* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
#define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (0)
/* @brief Has FTM module(s) configuration. */
#define FSL_FEATURE_SIM_OPT_HAS_FTM (0)
/* @brief Number of FTM modules. */
#define FSL_FEATURE_SIM_OPT_FTM_COUNT (0)
/* @brief Number of FTM triggers with selectable source. */
#define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (0)
/* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
#define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (0)
/* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
#define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (0)
/* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (0)
/* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (0)
/* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
/* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
/* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
#define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (0)
/* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
#define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (0)
/* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
#define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (0)
/* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
#define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (0)
/* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
#define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (0)
/* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
#define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (0)
/* @brief Has TPM module(s) configuration. */
#define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
/* @brief The highest TPM module index. */
#define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
/* @brief Has TPM module with index 0. */
#define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
/* @brief Has TPM0 clock selection (register bit field SOPT4[TPM0CLKSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM0_CLK_SEL (0)
/* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
/* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
/* @brief Has TPM1 clock selection (register bit field SOPT4[TPM1CLKSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM1_CLK_SEL (0)
/* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
#define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
/* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
/* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
/* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (0)
/* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
#define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (0)
/* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
/* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
/* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
/* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
/* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
/* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
/* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_USBSRC (0)
/* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
/* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
/* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
/* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
/* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
/* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
/* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
/* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
/* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (0)
/* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
#define FSL_FEATURE_SIM_OPT_ADC_COUNT (0)
/* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (0)
/* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
/* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (0)
/* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
#define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (0)
/* @brief Has clock 5 output divider (register bit field CLKDIV1[OUTDIV5]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV5 (0)
/* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
/* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
/* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
/* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
/* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
/* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
/* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
/* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
#define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (0)
/* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
#define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
/* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
#define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
/* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
#define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
/* @brief Has device die ID (register bit field SDID[DIEID]). */
#define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
/* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
#define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (1)
/* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
#define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
/* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
#define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
/* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
#define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
/* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
#define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
/* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
#define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
/* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
#define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
/* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
#define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (0)
/* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
#define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (0)
/* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
#define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
/* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
#define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
/* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
#define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
/* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
#define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
/* @brief Has miscellanious control register (register MCR). */
#define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
/* @brief Has COP watchdog (registers COPC and SRVCOP). */
#define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
/* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
#define FSL_FEATURE_SIM_HAS_COP_STOP (0)
/* @brief Has LLWU clock gate bit (e.g SIM_SCGC4). */
#define FSL_FEATURE_SIM_HAS_SCGC_LLWU (0)

/* SMC module features */

/* @brief Has partial stop option (register bit STOPCTRL[PSTOPO]). */
#define FSL_FEATURE_SMC_HAS_PSTOPO (1)
/* @brief Has LPO power option (register bit STOPCTRL[LPOPO]). */
#define FSL_FEATURE_SMC_HAS_LPOPO (0)
/* @brief Has POR power option (register bit STOPCTRL[PORPO] or VLLSCTRL[PORPO]). */
#define FSL_FEATURE_SMC_HAS_PORPO (1)
/* @brief Has low power wakeup on interrupt (register bit PMCTRL[LPWUI]). */
#define FSL_FEATURE_SMC_HAS_LPWUI (0)
/* @brief Has LLS or VLLS mode control (register bit STOPCTRL[LLSM]). */
#define FSL_FEATURE_SMC_HAS_LLS_SUBMODE (0)
/* @brief Has VLLS mode control (register bit VLLSCTRL[VLLSM]). */
#define FSL_FEATURE_SMC_USE_VLLSCTRL_REG (0)
/* @brief Has VLLS mode control (register bit STOPCTRL[VLLSM]). */
#define FSL_FEATURE_SMC_USE_STOPCTRL_VLLSM (1)
/* @brief Has RAM partition 2 power option (register bit STOPCTRL[RAM2PO]). */
#define FSL_FEATURE_SMC_HAS_RAM2_POWER_OPTION (0)
/* @brief Has high speed run mode (register bit PMPROT[AHSRUN]). */
#define FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE (0)
/* @brief Has low leakage stop mode (register bit PMPROT[ALLS]). */
#define FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE (0)
/* @brief Has stop submode 0(VLLS0). */
#define FSL_FEATURE_SMC_HAS_STOP_SUBMODE0 (1)
/* @brief Has stop submode 2(VLLS2). */
#define FSL_FEATURE_SMC_HAS_STOP_SUBMODE2 (1)

/* SPI module features */

/* @brief Has DMA support (register bit fields C2[RXDMAE] and C2[TXDMAE]). */
#define FSL_FEATURE_SPI_HAS_DMA_SUPPORT (1)
/* @brief Receive/transmit FIFO size in number of 16-bit communication items. */
#define FSL_FEATURE_SPI_FIFO_SIZE (4)
#define FSL_FEATURE_SPI_FIFO_SIZEx { 0, 4 }
/* @brief Maximum transfer data width in bits. */
#define FSL_FEATURE_SPI_MAX_DATA_WIDTH (16)
/* @brief The data register name has postfix (L as low and H as high). */
#define FSL_FEATURE_SPI_DATA_REGISTER_HAS_POSTFIX (1)
/* @brief Has separated TXDATA and CMD FIFOs (register SREX). */
#define FSL_FEATURE_SPI_HAS_SEPARATE_TXDATA_CMD_FIFO (0)
/* @brief Has 16-bit data transfer support. */
#define FSL_FEATURE_SPI_16BIT_TRANSFERS (1)

/* SysTick module features */

/* @brief Systick has external reference clock. */
#define FSL_FEATURE_SYSTICK_HAS_EXT_REF (1)
/* @brief Systick external reference clock is core clock divided by this value. */
#define FSL_FEATURE_SYSTICK_EXT_REF_CORE_DIV (16)

/* UART module features */

/* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
#define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
/* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
#define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
/* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
#define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_UART_HAS_FIFO (1)
/* @brief Hardware flow control (RTS, CTS) is supported. */
#define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (1)
/* @brief Infrared (modulation) is supported. */
#define FSL_FEATURE_UART_HAS_IR_SUPPORT (0)
/* @brief 2 bits long stop bit is available. */
#define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (0)
/* @brief Maximal data width without parity bit. */
#define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (0)
/* @brief Baud rate fine adjustment is available. */
#define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (1)
/* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
#define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (0)
/* @brief Baud rate oversampling is available. */
#define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (0)
/* @brief Baud rate oversampling is available. */
#define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (0)
/* @brief Peripheral type. */
#define FSL_FEATURE_UART_IS_SCI (0)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_UART_FIFO_SIZE (8)
/* @brief Maximal data width without parity bit. */
#define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (9)
/* @brief Maximal data width with parity bit. */
#define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (10)
/* @brief Supports two match addresses to filter incoming frames. */
#define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
/* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
#define FSL_FEATURE_UART_HAS_DMA_ENABLE (0)
/* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
#define FSL_FEATURE_UART_HAS_DMA_SELECT (1)
/* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
#define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
/* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
#define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (1)
/* @brief Has improved smart card (ISO7816 protocol) support. */
#define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (1)
/* @brief Has local operation network (CEA709.1-B protocol) support. */
#define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
/* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
#define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
/* @brief Lin break detect available (has bit BDH[LBKDIE]). */
#define FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT (0)
/* @brief UART stops in Wait mode available (has bit C1[UARTSWAI]). */
#define FSL_FEATURE_UART_HAS_WAIT_MODE_OPERATION (0)
/* @brief Has separate DMA RX and TX requests. */
#define FSL_FEATURE_UART_HAS_SEPARATE_DMA_RX_TX_REQn(x) \
    ((x) == 0 ? (1) : \
    ((x) == 1 ? (1) : \
    ((x) == 2 ? (1) : \
    ((x) == 3 ? (1) : (-1)))))

/* VREF module features */

/* @brief Has chop oscillator (bit TRM[CHOPEN]) */
#define FSL_FEATURE_VREF_HAS_CHOP_OSC (1)
/* @brief Has second order curvature compensation (bit SC[ICOMPEN]) */
#define FSL_FEATURE_VREF_HAS_COMPENSATION (1)
/* @brief Describes the set of SC[MODE_LV] bitfield values */
#define FSL_FEATURE_VREF_MODE_LV_TYPE (1)
/* @brief Module has also low reference (registers VREFL/VREFH) */
#define FSL_FEATURE_VREF_HAS_LOW_REFERENCE (1)

/* WDOG module features */

/* @brief Watchdog is available. */
#define FSL_FEATURE_WDOG_HAS_WATCHDOG (1)
/* @brief Has Wait mode support. */
#define FSL_FEATURE_WDOG_HAS_WAITEN (0)

/* XBAR module features */

/* @brief Has single XBAR module. */
#define FSL_FEATURE_XBAR_HAS_SINGLE_MODULE (1)
/* @brief Maximum value of XBAR input. */
#define FSL_FEATURE_XBAR_MODULE_INPUTS (52)
/* @brief Maximum value of XBAR output. */
#define FSL_FEATURE_XBAR_MODULE_OUTPUTS (44)
/* @brief Half register position. */
#define FSL_FEATURE_XBAR_HALF_REGISTER_SHIFT (BP_XBAR_SEL0_SEL1)
/* @brief Number of interrupt requests. */
#define FSL_FEATURE_XBAR_INTERRUPT_COUNT (4)
/* @brief XBAR has input 0. */
#define FSL_FEATURE_XBAR_HAS_INPUT0 (1)
/* @brief XBAR has input 1. */
#define FSL_FEATURE_XBAR_HAS_INPUT1 (1)
/* @brief XBAR has input 2. */
#define FSL_FEATURE_XBAR_HAS_INPUT2 (1)
/* @brief XBAR has input 3. */
#define FSL_FEATURE_XBAR_HAS_INPUT3 (1)
/* @brief XBAR has input 4. */
#define FSL_FEATURE_XBAR_HAS_INPUT4 (1)
/* @brief XBAR has input 5. */
#define FSL_FEATURE_XBAR_HAS_INPUT5 (1)
/* @brief XBAR has input 6. */
#define FSL_FEATURE_XBAR_HAS_INPUT6 (1)
/* @brief XBAR has input 7. */
#define FSL_FEATURE_XBAR_HAS_INPUT7 (1)
/* @brief XBAR has input 8. */
#define FSL_FEATURE_XBAR_HAS_INPUT8 (1)
/* @brief XBAR has input 9. */
#define FSL_FEATURE_XBAR_HAS_INPUT9 (1)
/* @brief XBAR has input 10. */
#define FSL_FEATURE_XBAR_HAS_INPUT10 (1)
/* @brief XBAR has input 11. */
#define FSL_FEATURE_XBAR_HAS_INPUT11 (1)
/* @brief XBAR has input 12. */
#define FSL_FEATURE_XBAR_HAS_INPUT12 (1)
/* @brief XBAR has input 13. */
#define FSL_FEATURE_XBAR_HAS_INPUT13 (1)
/* @brief XBAR has input 14. */
#define FSL_FEATURE_XBAR_HAS_INPUT14 (1)
/* @brief XBAR has input 15. */
#define FSL_FEATURE_XBAR_HAS_INPUT15 (1)
/* @brief XBAR has input 16. */
#define FSL_FEATURE_XBAR_HAS_INPUT16 (1)
/* @brief XBAR has input 17. */
#define FSL_FEATURE_XBAR_HAS_INPUT17 (1)
/* @brief XBAR has input 18. */
#define FSL_FEATURE_XBAR_HAS_INPUT18 (1)
/* @brief XBAR has input 19. */
#define FSL_FEATURE_XBAR_HAS_INPUT19 (1)
/* @brief XBAR has input 20. */
#define FSL_FEATURE_XBAR_HAS_INPUT20 (1)
/* @brief XBAR has input 21. */
#define FSL_FEATURE_XBAR_HAS_INPUT21 (1)
/* @brief XBAR has input 22. */
#define FSL_FEATURE_XBAR_HAS_INPUT22 (1)
/* @brief XBAR has input 23. */
#define FSL_FEATURE_XBAR_HAS_INPUT23 (1)
/* @brief XBAR has input 24. */
#define FSL_FEATURE_XBAR_HAS_INPUT24 (1)
/* @brief XBAR has input 25. */
#define FSL_FEATURE_XBAR_HAS_INPUT25 (1)
/* @brief XBAR has input 26. */
#define FSL_FEATURE_XBAR_HAS_INPUT26 (1)
/* @brief XBAR has input 27. */
#define FSL_FEATURE_XBAR_HAS_INPUT27 (1)
/* @brief XBAR has input 28. */
#define FSL_FEATURE_XBAR_HAS_INPUT28 (1)
/* @brief XBAR has input 29. */
#define FSL_FEATURE_XBAR_HAS_INPUT29 (1)
/* @brief XBAR has input 30. */
#define FSL_FEATURE_XBAR_HAS_INPUT30 (1)
/* @brief XBAR has input 31. */
#define FSL_FEATURE_XBAR_HAS_INPUT31 (1)
/* @brief XBAR has input 32. */
#define FSL_FEATURE_XBAR_HAS_INPUT32 (1)
/* @brief XBAR has input 33. */
#define FSL_FEATURE_XBAR_HAS_INPUT33 (1)
/* @brief XBAR has input 34. */
#define FSL_FEATURE_XBAR_HAS_INPUT34 (1)
/* @brief XBAR has input 35. */
#define FSL_FEATURE_XBAR_HAS_INPUT35 (1)
/* @brief XBAR has input 36. */
#define FSL_FEATURE_XBAR_HAS_INPUT36 (1)
/* @brief XBAR has input 37. */
#define FSL_FEATURE_XBAR_HAS_INPUT37 (1)
/* @brief XBAR has input 38. */
#define FSL_FEATURE_XBAR_HAS_INPUT38 (1)
/* @brief XBAR has input 39. */
#define FSL_FEATURE_XBAR_HAS_INPUT39 (1)
/* @brief XBAR has input 40. */
#define FSL_FEATURE_XBAR_HAS_INPUT40 (1)
/* @brief XBAR has input 41. */
#define FSL_FEATURE_XBAR_HAS_INPUT41 (1)
/* @brief XBAR has input 42. */
#define FSL_FEATURE_XBAR_HAS_INPUT42 (1)
/* @brief XBAR has input 43. */
#define FSL_FEATURE_XBAR_HAS_INPUT43 (1)
/* @brief XBAR has input 44. */
#define FSL_FEATURE_XBAR_HAS_INPUT44 (1)
/* @brief XBAR has input 45. */
#define FSL_FEATURE_XBAR_HAS_INPUT45 (1)
/* @brief XBAR has input 46. */
#define FSL_FEATURE_XBAR_HAS_INPUT46 (1)
/* @brief XBAR has input 47. */
#define FSL_FEATURE_XBAR_HAS_INPUT47 (1)
/* @brief XBAR has input 48. */
#define FSL_FEATURE_XBAR_HAS_INPUT48 (1)
/* @brief XBAR has input 49. */
#define FSL_FEATURE_XBAR_HAS_INPUT49 (1)
/* @brief XBAR has input 50. */
#define FSL_FEATURE_XBAR_HAS_INPUT50 (1)
/* @brief XBAR has input 51. */
#define FSL_FEATURE_XBAR_HAS_INPUT51 (1)
/* @brief XBAR has input 52. */
#define FSL_FEATURE_XBAR_HAS_INPUT52 (0)
/* @brief XBAR has input 53. */
#define FSL_FEATURE_XBAR_HAS_INPUT53 (0)
/* @brief XBAR has input 54. */
#define FSL_FEATURE_XBAR_HAS_INPUT54 (0)
/* @brief XBAR has input 55. */
#define FSL_FEATURE_XBAR_HAS_INPUT55 (0)
/* @brief XBAR has input 56. */
#define FSL_FEATURE_XBAR_HAS_INPUT56 (0)
/* @brief XBAR has input 57. */
#define FSL_FEATURE_XBAR_HAS_INPUT57 (0)
/* @brief XBAR has input 58. */
#define FSL_FEATURE_XBAR_HAS_INPUT58 (0)
/* @brief XBAR has input 59. */
#define FSL_FEATURE_XBAR_HAS_INPUT59 (0)
/* @brief XBAR has input 60. */
#define FSL_FEATURE_XBAR_HAS_INPUT60 (0)
/* @brief XBAR has input 61. */
#define FSL_FEATURE_XBAR_HAS_INPUT61 (0)
/* @brief XBAR has input 62. */
#define FSL_FEATURE_XBAR_HAS_INPUT62 (0)
/* @brief XBAR has input 63. */
#define FSL_FEATURE_XBAR_HAS_INPUT63 (0)
/* @brief XBAR has input 64. */
#define FSL_FEATURE_XBAR_HAS_INPUT64 (0)
/* @brief XBAR has input 65. */
#define FSL_FEATURE_XBAR_HAS_INPUT65 (0)
/* @brief XBAR has input 66. */
#define FSL_FEATURE_XBAR_HAS_INPUT66 (0)
/* @brief XBAR has input 67. */
#define FSL_FEATURE_XBAR_HAS_INPUT67 (0)
/* @brief XBAR has input 68. */
#define FSL_FEATURE_XBAR_HAS_INPUT68 (0)
/* @brief XBAR has input 69. */
#define FSL_FEATURE_XBAR_HAS_INPUT69 (0)
/* @brief XBAR has input 70. */
#define FSL_FEATURE_XBAR_HAS_INPUT70 (0)
/* @brief XBAR has input 71. */
#define FSL_FEATURE_XBAR_HAS_INPUT71 (0)
/* @brief XBAR has input 72. */
#define FSL_FEATURE_XBAR_HAS_INPUT72 (0)
/* @brief XBAR has input 73. */
#define FSL_FEATURE_XBAR_HAS_INPUT73 (0)
/* @brief XBAR has input 74. */
#define FSL_FEATURE_XBAR_HAS_INPUT74 (0)
/* @brief XBAR has input 75. */
#define FSL_FEATURE_XBAR_HAS_INPUT75 (0)
/* @brief XBAR has input 76. */
#define FSL_FEATURE_XBAR_HAS_INPUT76 (0)
/* @brief XBAR has input 77. */
#define FSL_FEATURE_XBAR_HAS_INPUT77 (0)
/* @brief XBAR has input 78. */
#define FSL_FEATURE_XBAR_HAS_INPUT78 (0)
/* @brief XBAR has input 79. */
#define FSL_FEATURE_XBAR_HAS_INPUT79 (0)
/* @brief XBAR has input 80. */
#define FSL_FEATURE_XBAR_HAS_INPUT80 (0)
/* @brief XBAR has input 81. */
#define FSL_FEATURE_XBAR_HAS_INPUT81 (0)
/* @brief XBAR has input 82. */
#define FSL_FEATURE_XBAR_HAS_INPUT82 (0)
/* @brief XBAR has input 83. */
#define FSL_FEATURE_XBAR_HAS_INPUT83 (0)
/* @brief XBAR has input 84. */
#define FSL_FEATURE_XBAR_HAS_INPUT84 (0)
/* @brief XBAR has input 85. */
#define FSL_FEATURE_XBAR_HAS_INPUT85 (0)
/* @brief XBAR has input 86. */
#define FSL_FEATURE_XBAR_HAS_INPUT86 (0)
/* @brief XBAR has input 87. */
#define FSL_FEATURE_XBAR_HAS_INPUT87 (0)
/* @brief XBAR has input 88. */
#define FSL_FEATURE_XBAR_HAS_INPUT88 (0)
/* @brief XBAR has input 89. */
#define FSL_FEATURE_XBAR_HAS_INPUT89 (0)
/* @brief XBAR has input 90. */
#define FSL_FEATURE_XBAR_HAS_INPUT90 (0)
/* @brief XBAR has input 91. */
#define FSL_FEATURE_XBAR_HAS_INPUT91 (0)
/* @brief XBAR has input 92. */
#define FSL_FEATURE_XBAR_HAS_INPUT92 (0)
/* @brief XBAR has input 93. */
#define FSL_FEATURE_XBAR_HAS_INPUT93 (0)
/* @brief XBAR has input 94. */
#define FSL_FEATURE_XBAR_HAS_INPUT94 (0)
/* @brief XBAR has input 95. */
#define FSL_FEATURE_XBAR_HAS_INPUT95 (0)
/* @brief XBAR has input 96. */
#define FSL_FEATURE_XBAR_HAS_INPUT96 (0)
/* @brief XBAR has input 97. */
#define FSL_FEATURE_XBAR_HAS_INPUT97 (0)
/* @brief XBAR has input 98. */
#define FSL_FEATURE_XBAR_HAS_INPUT98 (0)
/* @brief XBAR has input 99. */
#define FSL_FEATURE_XBAR_HAS_INPUT99 (0)
/* @brief XBAR has input 100. */
#define FSL_FEATURE_XBAR_HAS_INPUT100 (0)
/* @brief XBAR has input 101. */
#define FSL_FEATURE_XBAR_HAS_INPUT101 (0)
/* @brief XBAR has input 102. */
#define FSL_FEATURE_XBAR_HAS_INPUT102 (0)
/* @brief XBAR has input 103. */
#define FSL_FEATURE_XBAR_HAS_INPUT103 (0)
/* @brief XBAR has input 104. */
#define FSL_FEATURE_XBAR_HAS_INPUT104 (0)
/* @brief XBAR has input 105. */
#define FSL_FEATURE_XBAR_HAS_INPUT105 (0)
/* @brief XBAR has input 106. */
#define FSL_FEATURE_XBAR_HAS_INPUT106 (0)
/* @brief XBAR has input 107. */
#define FSL_FEATURE_XBAR_HAS_INPUT107 (0)
/* @brief XBAR has input 108. */
#define FSL_FEATURE_XBAR_HAS_INPUT108 (0)
/* @brief XBAR has input 109. */
#define FSL_FEATURE_XBAR_HAS_INPUT109 (0)
/* @brief XBAR has input 110. */
#define FSL_FEATURE_XBAR_HAS_INPUT110 (0)
/* @brief XBAR has input 111. */
#define FSL_FEATURE_XBAR_HAS_INPUT111 (0)
/* @brief XBAR has input 112. */
#define FSL_FEATURE_XBAR_HAS_INPUT112 (0)
/* @brief XBAR has input 113. */
#define FSL_FEATURE_XBAR_HAS_INPUT113 (0)
/* @brief XBAR has input 114. */
#define FSL_FEATURE_XBAR_HAS_INPUT114 (0)
/* @brief XBAR has input 115. */
#define FSL_FEATURE_XBAR_HAS_INPUT115 (0)
/* @brief XBAR has input 116. */
#define FSL_FEATURE_XBAR_HAS_INPUT116 (0)
/* @brief XBAR has input 117. */
#define FSL_FEATURE_XBAR_HAS_INPUT117 (0)
/* @brief XBAR has input 118. */
#define FSL_FEATURE_XBAR_HAS_INPUT118 (0)
/* @brief XBAR has input 119. */
#define FSL_FEATURE_XBAR_HAS_INPUT119 (0)
/* @brief XBAR has input 120. */
#define FSL_FEATURE_XBAR_HAS_INPUT120 (0)
/* @brief XBAR has input 121. */
#define FSL_FEATURE_XBAR_HAS_INPUT121 (0)
/* @brief XBAR has input 122. */
#define FSL_FEATURE_XBAR_HAS_INPUT122 (0)
/* @brief XBAR has input 123. */
#define FSL_FEATURE_XBAR_HAS_INPUT123 (0)
/* @brief XBAR has input 124. */
#define FSL_FEATURE_XBAR_HAS_INPUT124 (0)
/* @brief XBAR has input 125. */
#define FSL_FEATURE_XBAR_HAS_INPUT125 (0)
/* @brief XBAR has input 126. */
#define FSL_FEATURE_XBAR_HAS_INPUT126 (0)
/* @brief XBAR has input 127. */
#define FSL_FEATURE_XBAR_HAS_INPUT127 (0)
/* @brief XBAR has output 0. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT0 (1)
/* @brief XBAR has output 1. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT1 (1)
/* @brief XBAR has output 2. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT2 (1)
/* @brief XBAR has output 3. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT3 (1)
/* @brief XBAR has output 4. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT4 (1)
/* @brief XBAR has output 5. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT5 (1)
/* @brief XBAR has output 6. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT6 (1)
/* @brief XBAR has output 7. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT7 (1)
/* @brief XBAR has output 8. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT8 (1)
/* @brief XBAR has output 9. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT9 (1)
/* @brief XBAR has output 10. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT10 (1)
/* @brief XBAR has output 11. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT11 (1)
/* @brief XBAR has output 12. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT12 (1)
/* @brief XBAR has output 13. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT13 (1)
/* @brief XBAR has output 14. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT14 (1)
/* @brief XBAR has output 15. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT15 (1)
/* @brief XBAR has output 16. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT16 (1)
/* @brief XBAR has output 17. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT17 (1)
/* @brief XBAR has output 18. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT18 (1)
/* @brief XBAR has output 19. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT19 (1)
/* @brief XBAR has output 20. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT20 (1)
/* @brief XBAR has output 21. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT21 (1)
/* @brief XBAR has output 22. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT22 (1)
/* @brief XBAR has output 23. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT23 (1)
/* @brief XBAR has output 24. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT24 (1)
/* @brief XBAR has output 25. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT25 (1)
/* @brief XBAR has output 26. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT26 (1)
/* @brief XBAR has output 27. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT27 (1)
/* @brief XBAR has output 28. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT28 (1)
/* @brief XBAR has output 29. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT29 (1)
/* @brief XBAR has output 30. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT30 (1)
/* @brief XBAR has output 31. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT31 (1)
/* @brief XBAR has output 32. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT32 (1)
/* @brief XBAR has output 33. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT33 (1)
/* @brief XBAR has output 34. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT34 (1)
/* @brief XBAR has output 35. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT35 (1)
/* @brief XBAR has output 36. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT36 (1)
/* @brief XBAR has output 37. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT37 (1)
/* @brief XBAR has output 38. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT38 (1)
/* @brief XBAR has output 39. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT39 (1)
/* @brief XBAR has output 40. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT40 (1)
/* @brief XBAR has output 41. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT41 (1)
/* @brief XBAR has output 42. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT42 (1)
/* @brief XBAR has output 43. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT43 (1)
/* @brief XBAR has output 44. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT44 (0)
/* @brief XBAR has output 45. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT45 (0)
/* @brief XBAR has output 46. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT46 (0)
/* @brief XBAR has output 47. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT47 (0)
/* @brief XBAR has output 48. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT48 (0)
/* @brief XBAR has output 49. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT49 (0)
/* @brief XBAR has output 50. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT50 (0)
/* @brief XBAR has output 51. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT51 (0)
/* @brief XBAR has output 52. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT52 (0)
/* @brief XBAR has output 53. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT53 (0)
/* @brief XBAR has output 54. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT54 (0)
/* @brief XBAR has output 55. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT55 (0)
/* @brief XBAR has output 56. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT56 (0)
/* @brief XBAR has output 57. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT57 (0)
/* @brief XBAR has output 58. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT58 (0)
/* @brief XBAR has output 59. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT59 (0)
/* @brief XBAR has output 60. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT60 (0)
/* @brief XBAR has output 61. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT61 (0)
/* @brief XBAR has output 62. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT62 (0)
/* @brief XBAR has output 63. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT63 (0)
/* @brief XBAR has output 64. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT64 (0)
/* @brief XBAR has output 65. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT65 (0)
/* @brief XBAR has output 66. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT66 (0)
/* @brief XBAR has output 67. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT67 (0)
/* @brief XBAR has output 68. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT68 (0)
/* @brief XBAR has output 69. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT69 (0)
/* @brief XBAR has output 70. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT70 (0)
/* @brief XBAR has output 71. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT71 (0)
/* @brief XBAR has output 72. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT72 (0)
/* @brief XBAR has output 73. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT73 (0)
/* @brief XBAR has output 74. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT74 (0)
/* @brief XBAR has output 75. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT75 (0)
/* @brief XBAR has output 76. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT76 (0)
/* @brief XBAR has output 77. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT77 (0)
/* @brief XBAR has output 78. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT78 (0)
/* @brief XBAR has output 79. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT79 (0)
/* @brief XBAR has output 80. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT80 (0)
/* @brief XBAR has output 81. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT81 (0)
/* @brief XBAR has output 82. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT82 (0)
/* @brief XBAR has output 83. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT83 (0)
/* @brief XBAR has output 84. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT84 (0)
/* @brief XBAR has output 85. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT85 (0)
/* @brief XBAR has output 86. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT86 (0)
/* @brief XBAR has output 87. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT87 (0)
/* @brief XBAR has output 88. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT88 (0)
/* @brief XBAR has output 89. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT89 (0)
/* @brief XBAR has output 90. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT90 (0)
/* @brief XBAR has output 91. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT91 (0)
/* @brief XBAR has output 92. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT92 (0)
/* @brief XBAR has output 93. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT93 (0)
/* @brief XBAR has output 94. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT94 (0)
/* @brief XBAR has output 95. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT95 (0)
/* @brief XBAR has output 96. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT96 (0)
/* @brief XBAR has output 97. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT97 (0)
/* @brief XBAR has output 98. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT98 (0)
/* @brief XBAR has output 99. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT99 (0)
/* @brief XBAR has output 100. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT100 (0)
/* @brief XBAR has output 101. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT101 (0)
/* @brief XBAR has output 102. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT102 (0)
/* @brief XBAR has output 103. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT103 (0)
/* @brief XBAR has output 104. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT104 (0)
/* @brief XBAR has output 105. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT105 (0)
/* @brief XBAR has output 106. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT106 (0)
/* @brief XBAR has output 107. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT107 (0)
/* @brief XBAR has output 108. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT108 (0)
/* @brief XBAR has output 109. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT109 (0)
/* @brief XBAR has output 110. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT110 (0)
/* @brief XBAR has output 111. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT111 (0)
/* @brief XBAR has output 112. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT112 (0)
/* @brief XBAR has output 113. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT113 (0)
/* @brief XBAR has output 114. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT114 (0)
/* @brief XBAR has output 115. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT115 (0)
/* @brief XBAR has output 116. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT116 (0)
/* @brief XBAR has output 117. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT117 (0)
/* @brief XBAR has output 118. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT118 (0)
/* @brief XBAR has output 119. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT119 (0)
/* @brief XBAR has output 120. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT120 (0)
/* @brief XBAR has output 121. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT121 (0)
/* @brief XBAR has output 122. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT122 (0)
/* @brief XBAR has output 123. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT123 (0)
/* @brief XBAR has output 124. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT124 (0)
/* @brief XBAR has output 125. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT125 (0)
/* @brief XBAR has output 126. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT126 (0)
/* @brief XBAR has output 127. */
#define FSL_FEATURE_XBAR_HAS_OUTPUT127 (0)
/* @brief XBAR input 0 ID. */
#define FSL_FEATURE_XBAR_INPUT0_ID (VDD)
/* @brief XBAR input 1 ID. */
#define FSL_FEATURE_XBAR_INPUT1_ID (VSS)
/* @brief XBAR input 2 ID. */
#define FSL_FEATURE_XBAR_INPUT2_ID (AFE_Clock)
/* @brief XBAR input 3 ID. */
#define FSL_FEATURE_XBAR_INPUT3_ID (AFE_Mod0_Date_Output)
/* @brief XBAR input 4 ID. */
#define FSL_FEATURE_XBAR_INPUT4_ID (LPTMR0_Output)
/* @brief XBAR input 5 ID. */
#define FSL_FEATURE_XBAR_INPUT5_ID (Clock_Output)
/* @brief XBAR input 6 ID. */
#define FSL_FEATURE_XBAR_INPUT6_ID (TMR_CH0_Output)
/* @brief XBAR input 7 ID. */
#define FSL_FEATURE_XBAR_INPUT7_ID (TMR_CH1_Output)
/* @brief XBAR input 8 ID. */
#define FSL_FEATURE_XBAR_INPUT8_ID (TMR_CH2_Output)
/* @brief XBAR input 9 ID. */
#define FSL_FEATURE_XBAR_INPUT9_ID (TMR_CH3_Output)
/* @brief XBAR input 10 ID. */
#define FSL_FEATURE_XBAR_INPUT10_ID (RTC_CLK_Output)
/* @brief XBAR input 11 ID. */
#define FSL_FEATURE_XBAR_INPUT11_ID (CMP0_Output)
/* @brief XBAR input 12 ID. */
#define FSL_FEATURE_XBAR_INPUT12_ID (CMP1_Output)
/* @brief XBAR input 13 ID. */
#define FSL_FEATURE_XBAR_INPUT13_ID (RTC_ALARM_Output)
/* @brief XBAR input 14 ID. */
#define FSL_FEATURE_XBAR_INPUT14_ID (UART_TX_Output)
/* @brief XBAR input 15 ID. */
#define FSL_FEATURE_XBAR_INPUT15_ID (EWM_Output)
/* @brief XBAR input 16 ID. */
#define FSL_FEATURE_XBAR_INPUT16_ID (PIT0_TIF0)
/* @brief XBAR input 17 ID. */
#define FSL_FEATURE_XBAR_INPUT17_ID (XBAR_IN0)
/* @brief XBAR input 18 ID. */
#define FSL_FEATURE_XBAR_INPUT18_ID (XBAR_IN1)
/* @brief XBAR input 19 ID. */
#define FSL_FEATURE_XBAR_INPUT19_ID (XBAR_IN2)
/* @brief XBAR input 20 ID. */
#define FSL_FEATURE_XBAR_INPUT20_ID (XBAR_IN3)
/* @brief XBAR input 21 ID. */
#define FSL_FEATURE_XBAR_INPUT21_ID (XBAR_IN4)
/* @brief XBAR input 22 ID. */
#define FSL_FEATURE_XBAR_INPUT22_ID (XBAR_IN5)
/* @brief XBAR input 23 ID. */
#define FSL_FEATURE_XBAR_INPUT23_ID (XBAR_IN6)
/* @brief XBAR input 24 ID. */
#define FSL_FEATURE_XBAR_INPUT24_ID (XBAR_IN7)
/* @brief XBAR input 25 ID. */
#define FSL_FEATURE_XBAR_INPUT25_ID (XBAR_IN8)
/* @brief XBAR input 26 ID. */
#define FSL_FEATURE_XBAR_INPUT26_ID (ADC_COCO_Flag)
/* @brief XBAR input 27 ID. */
#define FSL_FEATURE_XBAR_INPUT27_ID (AFE_All_COC_Flag)
/* @brief XBAR input 28 ID. */
#define FSL_FEATURE_XBAR_INPUT28_ID (AFE_CH0_COC_Flag)
/* @brief XBAR input 29 ID. */
#define FSL_FEATURE_XBAR_INPUT29_ID (AFE_CH1_COC_Flag)
/* @brief XBAR input 30 ID. */
#define FSL_FEATURE_XBAR_INPUT30_ID (AFE_CH2_COC_Flag)
/* @brief XBAR input 31 ID. */
#define FSL_FEATURE_XBAR_INPUT31_ID (AFE_CH3_COC_Flag)
/* @brief XBAR input 32 ID. */
#define FSL_FEATURE_XBAR_INPUT32_ID (DMA_DONE_Signal)
/* @brief XBAR input 33 ID. */
#define FSL_FEATURE_XBAR_INPUT33_ID (XBAR_IN9)
/* @brief XBAR input 34 ID. */
#define FSL_FEATURE_XBAR_INPUT34_ID (XBAR_IN10)
/* @brief XBAR input 35 ID. */
#define FSL_FEATURE_XBAR_INPUT35_ID (CMP2_Output)
/* @brief XBAR input 36 ID. */
#define FSL_FEATURE_XBAR_INPUT36_ID (PIT0_TIF1)
/* @brief XBAR input 37 ID. */
#define FSL_FEATURE_XBAR_INPUT37_ID (PIT1_TIF0)
/* @brief XBAR input 38 ID. */
#define FSL_FEATURE_XBAR_INPUT38_ID (PIT1_TIF1)
/* @brief XBAR input 39 ID. */
#define FSL_FEATURE_XBAR_INPUT39_ID (AFE_Mod1_Date_Output)
/* @brief XBAR input 40 ID. */
#define FSL_FEATURE_XBAR_INPUT40_ID (AFE_Mod2_Date_Output)
/* @brief XBAR input 41 ID. */
#define FSL_FEATURE_XBAR_INPUT41_ID (AFE_Mod3_Date_Output)
/* @brief XBAR input 42 ID. */
#define FSL_FEATURE_XBAR_INPUT42_ID (ADC_COCO_A)
/* @brief XBAR input 43 ID. */
#define FSL_FEATURE_XBAR_INPUT43_ID (ADC_COCO_B)
/* @brief XBAR input 44 ID. */
#define FSL_FEATURE_XBAR_INPUT44_ID (ADC_COCO_C)
/* @brief XBAR input 45 ID. */
#define FSL_FEATURE_XBAR_INPUT45_ID (ADC_COCO_D)
/* @brief XBAR input 46 ID. */
#define FSL_FEATURE_XBAR_INPUT46_ID (PDB0_CH0_Pretrigger0)
/* @brief XBAR input 47 ID. */
#define FSL_FEATURE_XBAR_INPUT47_ID (PDB0_CH0_Pretrigger1)
/* @brief XBAR input 48 ID. */
#define FSL_FEATURE_XBAR_INPUT48_ID (PDB0_CH0_Pretrigger2)
/* @brief XBAR input 49 ID. */
#define FSL_FEATURE_XBAR_INPUT49_ID (PDB0_CH0_Pretrigger3)
/* @brief XBAR input 50 ID. */
#define FSL_FEATURE_XBAR_INPUT50_ID (PDB0_Ch0_Trigger)
/* @brief XBAR input 51 ID. */
#define FSL_FEATURE_XBAR_INPUT51_ID (PDB0_PulseOut0)
/* @brief XBAR input 52 ID. */
#define FSL_FEATURE_XBAR_INPUT52_ID (XBAR_IN_RESERVED52)
/* @brief XBAR input 53 ID. */
#define FSL_FEATURE_XBAR_INPUT53_ID (XBAR_IN_RESERVED53)
/* @brief XBAR input 54 ID. */
#define FSL_FEATURE_XBAR_INPUT54_ID (XBAR_IN_RESERVED54)
/* @brief XBAR input 55 ID. */
#define FSL_FEATURE_XBAR_INPUT55_ID (XBAR_IN_RESERVED55)
/* @brief XBAR input 56 ID. */
#define FSL_FEATURE_XBAR_INPUT56_ID (XBAR_IN_RESERVED56)
/* @brief XBAR input 57 ID. */
#define FSL_FEATURE_XBAR_INPUT57_ID (XBAR_IN_RESERVED57)
/* @brief XBAR input 58 ID. */
#define FSL_FEATURE_XBAR_INPUT58_ID (XBAR_IN_RESERVED58)
/* @brief XBAR input 59 ID. */
#define FSL_FEATURE_XBAR_INPUT59_ID (XBAR_IN_RESERVED59)
/* @brief XBAR input 60 ID. */
#define FSL_FEATURE_XBAR_INPUT60_ID (XBAR_IN_RESERVED60)
/* @brief XBAR input 61 ID. */
#define FSL_FEATURE_XBAR_INPUT61_ID (XBAR_IN_RESERVED61)
/* @brief XBAR input 62 ID. */
#define FSL_FEATURE_XBAR_INPUT62_ID (XBAR_IN_RESERVED62)
/* @brief XBAR input 63 ID. */
#define FSL_FEATURE_XBAR_INPUT63_ID (XBAR_IN_RESERVED63)
/* @brief XBAR input 64 ID. */
#define FSL_FEATURE_XBAR_INPUT64_ID (XBAR_IN_RESERVED64)
/* @brief XBAR input 65 ID. */
#define FSL_FEATURE_XBAR_INPUT65_ID (XBAR_IN_RESERVED65)
/* @brief XBAR input 66 ID. */
#define FSL_FEATURE_XBAR_INPUT66_ID (XBAR_IN_RESERVED66)
/* @brief XBAR input 67 ID. */
#define FSL_FEATURE_XBAR_INPUT67_ID (XBAR_IN_RESERVED67)
/* @brief XBAR input 68 ID. */
#define FSL_FEATURE_XBAR_INPUT68_ID (XBAR_IN_RESERVED68)
/* @brief XBAR input 69 ID. */
#define FSL_FEATURE_XBAR_INPUT69_ID (XBAR_IN_RESERVED69)
/* @brief XBAR input 70 ID. */
#define FSL_FEATURE_XBAR_INPUT70_ID (XBAR_IN_RESERVED70)
/* @brief XBAR input 71 ID. */
#define FSL_FEATURE_XBAR_INPUT71_ID (XBAR_IN_RESERVED71)
/* @brief XBAR input 72 ID. */
#define FSL_FEATURE_XBAR_INPUT72_ID (XBAR_IN_RESERVED72)
/* @brief XBAR input 73 ID. */
#define FSL_FEATURE_XBAR_INPUT73_ID (XBAR_IN_RESERVED73)
/* @brief XBAR input 74 ID. */
#define FSL_FEATURE_XBAR_INPUT74_ID (XBAR_IN_RESERVED74)
/* @brief XBAR input 75 ID. */
#define FSL_FEATURE_XBAR_INPUT75_ID (XBAR_IN_RESERVED75)
/* @brief XBAR input 76 ID. */
#define FSL_FEATURE_XBAR_INPUT76_ID (XBAR_IN_RESERVED76)
/* @brief XBAR input 77 ID. */
#define FSL_FEATURE_XBAR_INPUT77_ID (XBAR_IN_RESERVED77)
/* @brief XBAR input 78 ID. */
#define FSL_FEATURE_XBAR_INPUT78_ID (XBAR_IN_RESERVED78)
/* @brief XBAR input 79 ID. */
#define FSL_FEATURE_XBAR_INPUT79_ID (XBAR_IN_RESERVED79)
/* @brief XBAR input 80 ID. */
#define FSL_FEATURE_XBAR_INPUT80_ID (XBAR_IN_RESERVED80)
/* @brief XBAR input 81 ID. */
#define FSL_FEATURE_XBAR_INPUT81_ID (XBAR_IN_RESERVED81)
/* @brief XBAR input 82 ID. */
#define FSL_FEATURE_XBAR_INPUT82_ID (XBAR_IN_RESERVED82)
/* @brief XBAR input 83 ID. */
#define FSL_FEATURE_XBAR_INPUT83_ID (XBAR_IN_RESERVED83)
/* @brief XBAR input 84 ID. */
#define FSL_FEATURE_XBAR_INPUT84_ID (XBAR_IN_RESERVED84)
/* @brief XBAR input 85 ID. */
#define FSL_FEATURE_XBAR_INPUT85_ID (XBAR_IN_RESERVED85)
/* @brief XBAR input 86 ID. */
#define FSL_FEATURE_XBAR_INPUT86_ID (XBAR_IN_RESERVED86)
/* @brief XBAR input 87 ID. */
#define FSL_FEATURE_XBAR_INPUT87_ID (XBAR_IN_RESERVED87)
/* @brief XBAR input 88 ID. */
#define FSL_FEATURE_XBAR_INPUT88_ID (XBAR_IN_RESERVED88)
/* @brief XBAR input 89 ID. */
#define FSL_FEATURE_XBAR_INPUT89_ID (XBAR_IN_RESERVED89)
/* @brief XBAR input 90 ID. */
#define FSL_FEATURE_XBAR_INPUT90_ID (XBAR_IN_RESERVED90)
/* @brief XBAR input 91 ID. */
#define FSL_FEATURE_XBAR_INPUT91_ID (XBAR_IN_RESERVED91)
/* @brief XBAR input 92 ID. */
#define FSL_FEATURE_XBAR_INPUT92_ID (XBAR_IN_RESERVED92)
/* @brief XBAR input 93 ID. */
#define FSL_FEATURE_XBAR_INPUT93_ID (XBAR_IN_RESERVED93)
/* @brief XBAR input 94 ID. */
#define FSL_FEATURE_XBAR_INPUT94_ID (XBAR_IN_RESERVED94)
/* @brief XBAR input 95 ID. */
#define FSL_FEATURE_XBAR_INPUT95_ID (XBAR_IN_RESERVED95)
/* @brief XBAR input 96 ID. */
#define FSL_FEATURE_XBAR_INPUT96_ID (XBAR_IN_RESERVED96)
/* @brief XBAR input 97 ID. */
#define FSL_FEATURE_XBAR_INPUT97_ID (XBAR_IN_RESERVED97)
/* @brief XBAR input 98 ID. */
#define FSL_FEATURE_XBAR_INPUT98_ID (XBAR_IN_RESERVED98)
/* @brief XBAR input 99 ID. */
#define FSL_FEATURE_XBAR_INPUT99_ID (XBAR_IN_RESERVED99)
/* @brief XBAR input 100 ID. */
#define FSL_FEATURE_XBAR_INPUT100_ID (XBAR_IN_RESERVED100)
/* @brief XBAR input 101 ID. */
#define FSL_FEATURE_XBAR_INPUT101_ID (XBAR_IN_RESERVED101)
/* @brief XBAR input 102 ID. */
#define FSL_FEATURE_XBAR_INPUT102_ID (XBAR_IN_RESERVED102)
/* @brief XBAR input 103 ID. */
#define FSL_FEATURE_XBAR_INPUT103_ID (XBAR_IN_RESERVED103)
/* @brief XBAR input 104 ID. */
#define FSL_FEATURE_XBAR_INPUT104_ID (XBAR_IN_RESERVED104)
/* @brief XBAR input 105 ID. */
#define FSL_FEATURE_XBAR_INPUT105_ID (XBAR_IN_RESERVED105)
/* @brief XBAR input 106 ID. */
#define FSL_FEATURE_XBAR_INPUT106_ID (XBAR_IN_RESERVED106)
/* @brief XBAR input 107 ID. */
#define FSL_FEATURE_XBAR_INPUT107_ID (XBAR_IN_RESERVED107)
/* @brief XBAR input 108 ID. */
#define FSL_FEATURE_XBAR_INPUT108_ID (XBAR_IN_RESERVED108)
/* @brief XBAR input 109 ID. */
#define FSL_FEATURE_XBAR_INPUT109_ID (XBAR_IN_RESERVED109)
/* @brief XBAR input 110 ID. */
#define FSL_FEATURE_XBAR_INPUT110_ID (XBAR_IN_RESERVED110)
/* @brief XBAR input 111 ID. */
#define FSL_FEATURE_XBAR_INPUT111_ID (XBAR_IN_RESERVED111)
/* @brief XBAR input 112 ID. */
#define FSL_FEATURE_XBAR_INPUT112_ID (XBAR_IN_RESERVED112)
/* @brief XBAR input 113 ID. */
#define FSL_FEATURE_XBAR_INPUT113_ID (XBAR_IN_RESERVED113)
/* @brief XBAR input 114 ID. */
#define FSL_FEATURE_XBAR_INPUT114_ID (XBAR_IN_RESERVED114)
/* @brief XBAR input 115 ID. */
#define FSL_FEATURE_XBAR_INPUT115_ID (XBAR_IN_RESERVED115)
/* @brief XBAR input 116 ID. */
#define FSL_FEATURE_XBAR_INPUT116_ID (XBAR_IN_RESERVED116)
/* @brief XBAR input 117 ID. */
#define FSL_FEATURE_XBAR_INPUT117_ID (XBAR_IN_RESERVED117)
/* @brief XBAR input 118 ID. */
#define FSL_FEATURE_XBAR_INPUT118_ID (XBAR_IN_RESERVED118)
/* @brief XBAR input 119 ID. */
#define FSL_FEATURE_XBAR_INPUT119_ID (XBAR_IN_RESERVED119)
/* @brief XBAR input 120 ID. */
#define FSL_FEATURE_XBAR_INPUT120_ID (XBAR_IN_RESERVED120)
/* @brief XBAR input 121 ID. */
#define FSL_FEATURE_XBAR_INPUT121_ID (XBAR_IN_RESERVED121)
/* @brief XBAR input 122 ID. */
#define FSL_FEATURE_XBAR_INPUT122_ID (XBAR_IN_RESERVED122)
/* @brief XBAR input 123 ID. */
#define FSL_FEATURE_XBAR_INPUT123_ID (XBAR_IN_RESERVED123)
/* @brief XBAR input 124 ID. */
#define FSL_FEATURE_XBAR_INPUT124_ID (XBAR_IN_RESERVED124)
/* @brief XBAR input 125 ID. */
#define FSL_FEATURE_XBAR_INPUT125_ID (XBAR_IN_RESERVED125)
/* @brief XBAR input 126 ID. */
#define FSL_FEATURE_XBAR_INPUT126_ID (XBAR_IN_RESERVED126)
/* @brief XBAR input 127 ID. */
#define FSL_FEATURE_XBAR_INPUT127_ID (XBAR_IN_RESERVED127)
/* @brief XBAR output 0 ID. */
#define FSL_FEATURE_XBAR_OUTPUT0_ID (XB_DMA_INT0)
/* @brief XBAR output 1 ID. */
#define FSL_FEATURE_XBAR_OUTPUT1_ID (XB_DMA_INT1)
/* @brief XBAR output 2 ID. */
#define FSL_FEATURE_XBAR_OUTPUT2_ID (XB_DMA_INT2)
/* @brief XBAR output 3 ID. */
#define FSL_FEATURE_XBAR_OUTPUT3_ID (XB_DMA_INT3)
/* @brief XBAR output 4 ID. */
#define FSL_FEATURE_XBAR_OUTPUT4_ID (CMP2_Sample_Window_Input)
/* @brief XBAR output 5 ID. */
#define FSL_FEATURE_XBAR_OUTPUT5_ID (TMR_CH0_SecInput)
/* @brief XBAR output 6 ID. */
#define FSL_FEATURE_XBAR_OUTPUT6_ID (TMR_CH1_SecInput)
/* @brief XBAR output 7 ID. */
#define FSL_FEATURE_XBAR_OUTPUT7_ID (TMR_CH2_SecInput)
/* @brief XBAR output 8 ID. */
#define FSL_FEATURE_XBAR_OUTPUT8_ID (TMR_CH3_SecInput)
/* @brief XBAR output 9 ID. */
#define FSL_FEATURE_XBAR_OUTPUT9_ID (TMR_CLK_Input1)
/* @brief XBAR output 10 ID. */
#define FSL_FEATURE_XBAR_OUTPUT10_ID (TMR_CLK_Input2)
/* @brief XBAR output 11 ID. */
#define FSL_FEATURE_XBAR_OUTPUT11_ID (CMP0_Sample_Window_Input)
/* @brief XBAR output 12 ID. */
#define FSL_FEATURE_XBAR_OUTPUT12_ID (CMP1_Sample_Window_Input)
/* @brief XBAR output 13 ID. */
#define FSL_FEATURE_XBAR_OUTPUT13_ID (UART_RX_Input)
/* @brief XBAR output 14 ID. */
#define FSL_FEATURE_XBAR_OUTPUT14_ID (UART_TX_Output)
/* @brief XBAR output 15 ID. */
#define FSL_FEATURE_XBAR_OUTPUT15_ID (ADC_TRGA)
/* @brief XBAR output 16 ID. */
#define FSL_FEATURE_XBAR_OUTPUT16_ID (ADC_TRGB)
/* @brief XBAR output 17 ID. */
#define FSL_FEATURE_XBAR_OUTPUT17_ID (XB_OUT0)
/* @brief XBAR output 18 ID. */
#define FSL_FEATURE_XBAR_OUTPUT18_ID (XB_OUT1)
/* @brief XBAR output 19 ID. */
#define FSL_FEATURE_XBAR_OUTPUT19_ID (XB_OUT2)
/* @brief XBAR output 20 ID. */
#define FSL_FEATURE_XBAR_OUTPUT20_ID (XB_OUT3)
/* @brief XBAR output 21 ID. */
#define FSL_FEATURE_XBAR_OUTPUT21_ID (XB_OUT4)
/* @brief XBAR output 22 ID. */
#define FSL_FEATURE_XBAR_OUTPUT22_ID (XB_OUT5)
/* @brief XBAR output 23 ID. */
#define FSL_FEATURE_XBAR_OUTPUT23_ID (XB_OUT6)
/* @brief XBAR output 24 ID. */
#define FSL_FEATURE_XBAR_OUTPUT24_ID (XB_OUT7)
/* @brief XBAR output 25 ID. */
#define FSL_FEATURE_XBAR_OUTPUT25_ID (XB_OUT8)
/* @brief XBAR output 26 ID. */
#define FSL_FEATURE_XBAR_OUTPUT26_ID (ADC_TRGC)
/* @brief XBAR output 27 ID. */
#define FSL_FEATURE_XBAR_OUTPUT27_ID (ADC_TRGD)
/* @brief XBAR output 28 ID. */
#define FSL_FEATURE_XBAR_OUTPUT28_ID (AFE_CH0_TGR)
/* @brief XBAR output 29 ID. */
#define FSL_FEATURE_XBAR_OUTPUT29_ID (AFE_CH1_TGR)
/* @brief XBAR output 30 ID. */
#define FSL_FEATURE_XBAR_OUTPUT30_ID (AFE_CH2_TGR)
/* @brief XBAR output 31 ID. */
#define FSL_FEATURE_XBAR_OUTPUT31_ID (AFE_CH3_TGR)
/* @brief XBAR output 32 ID. */
#define FSL_FEATURE_XBAR_OUTPUT32_ID (EWM_IN)
/* @brief XBAR output 33 ID. */
#define FSL_FEATURE_XBAR_OUTPUT33_ID (XB_OUT9)
/* @brief XBAR output 34 ID. */
#define FSL_FEATURE_XBAR_OUTPUT34_ID (XB_OUT10)
/* @brief XBAR output 35 ID. */
#define FSL_FEATURE_XBAR_OUTPUT35_ID (PDB0_PreTrigger0_ACK)
/* @brief XBAR output 36 ID. */
#define FSL_FEATURE_XBAR_OUTPUT36_ID (PDB0_PreTrigger1_ACK)
/* @brief XBAR output 37 ID. */
#define FSL_FEATURE_XBAR_OUTPUT37_ID (PDB0_PreTrigger2_ACK)
/* @brief XBAR output 38 ID. */
#define FSL_FEATURE_XBAR_OUTPUT38_ID (PDB0_PreTrigger3_ACK)
/* @brief XBAR output 39 ID. */
#define FSL_FEATURE_XBAR_OUTPUT39_ID (PDB0_Trigger_Input)
/* @brief XBAR output 40 ID. */
#define FSL_FEATURE_XBAR_OUTPUT40_ID (AFE_Ch0_ExMod_Data)
/* @brief XBAR output 41 ID. */
#define FSL_FEATURE_XBAR_OUTPUT41_ID (AFE_Ch1_ExMod_Data)
/* @brief XBAR output 42 ID. */
#define FSL_FEATURE_XBAR_OUTPUT42_ID (AFE_Ch2_ExMod_Data)
/* @brief XBAR output 43 ID. */
#define FSL_FEATURE_XBAR_OUTPUT43_ID (AFE_Ch3_ExMod_Data)
/* @brief XBAR output 44 ID. */
#define FSL_FEATURE_XBAR_OUTPUT44_ID (XBAR_OUT_RESERVED44)
/* @brief XBAR output 45 ID. */
#define FSL_FEATURE_XBAR_OUTPUT45_ID (XBAR_OUT_RESERVED45)
/* @brief XBAR output 46 ID. */
#define FSL_FEATURE_XBAR_OUTPUT46_ID (XBAR_OUT_RESERVED46)
/* @brief XBAR output 47 ID. */
#define FSL_FEATURE_XBAR_OUTPUT47_ID (XBAR_OUT_RESERVED47)
/* @brief XBAR output 48 ID. */
#define FSL_FEATURE_XBAR_OUTPUT48_ID (XBAR_OUT_RESERVED48)
/* @brief XBAR output 49 ID. */
#define FSL_FEATURE_XBAR_OUTPUT49_ID (XBAR_OUT_RESERVED49)
/* @brief XBAR output 50 ID. */
#define FSL_FEATURE_XBAR_OUTPUT50_ID (XBAR_OUT_RESERVED50)
/* @brief XBAR output 51 ID. */
#define FSL_FEATURE_XBAR_OUTPUT51_ID (XBAR_OUT_RESERVED51)
/* @brief XBAR output 52 ID. */
#define FSL_FEATURE_XBAR_OUTPUT52_ID (XBAR_OUT_RESERVED52)
/* @brief XBAR output 53 ID. */
#define FSL_FEATURE_XBAR_OUTPUT53_ID (XBAR_OUT_RESERVED53)
/* @brief XBAR output 54 ID. */
#define FSL_FEATURE_XBAR_OUTPUT54_ID (XBAR_OUT_RESERVED54)
/* @brief XBAR output 55 ID. */
#define FSL_FEATURE_XBAR_OUTPUT55_ID (XBAR_OUT_RESERVED55)
/* @brief XBAR output 56 ID. */
#define FSL_FEATURE_XBAR_OUTPUT56_ID (XBAR_OUT_RESERVED56)
/* @brief XBAR output 57 ID. */
#define FSL_FEATURE_XBAR_OUTPUT57_ID (XBAR_OUT_RESERVED57)
/* @brief XBAR output 58 ID. */
#define FSL_FEATURE_XBAR_OUTPUT58_ID (XBAR_OUT_RESERVED58)
/* @brief XBAR output 59 ID. */
#define FSL_FEATURE_XBAR_OUTPUT59_ID (XBAR_OUT_RESERVED59)
/* @brief XBAR output 60 ID. */
#define FSL_FEATURE_XBAR_OUTPUT60_ID (XBAR_OUT_RESERVED60)
/* @brief XBAR output 61 ID. */
#define FSL_FEATURE_XBAR_OUTPUT61_ID (XBAR_OUT_RESERVED61)
/* @brief XBAR output 62 ID. */
#define FSL_FEATURE_XBAR_OUTPUT62_ID (XBAR_OUT_RESERVED62)
/* @brief XBAR output 63 ID. */
#define FSL_FEATURE_XBAR_OUTPUT63_ID (XBAR_OUT_RESERVED63)
/* @brief XBAR output 64 ID. */
#define FSL_FEATURE_XBAR_OUTPUT64_ID (XBAR_OUT_RESERVED64)
/* @brief XBAR output 65 ID. */
#define FSL_FEATURE_XBAR_OUTPUT65_ID (XBAR_OUT_RESERVED65)
/* @brief XBAR output 66 ID. */
#define FSL_FEATURE_XBAR_OUTPUT66_ID (XBAR_OUT_RESERVED66)
/* @brief XBAR output 67 ID. */
#define FSL_FEATURE_XBAR_OUTPUT67_ID (XBAR_OUT_RESERVED67)
/* @brief XBAR output 68 ID. */
#define FSL_FEATURE_XBAR_OUTPUT68_ID (XBAR_OUT_RESERVED68)
/* @brief XBAR output 69 ID. */
#define FSL_FEATURE_XBAR_OUTPUT69_ID (XBAR_OUT_RESERVED69)
/* @brief XBAR output 70 ID. */
#define FSL_FEATURE_XBAR_OUTPUT70_ID (XBAR_OUT_RESERVED70)
/* @brief XBAR output 71 ID. */
#define FSL_FEATURE_XBAR_OUTPUT71_ID (XBAR_OUT_RESERVED71)
/* @brief XBAR output 72 ID. */
#define FSL_FEATURE_XBAR_OUTPUT72_ID (XBAR_OUT_RESERVED72)
/* @brief XBAR output 73 ID. */
#define FSL_FEATURE_XBAR_OUTPUT73_ID (XBAR_OUT_RESERVED73)
/* @brief XBAR output 74 ID. */
#define FSL_FEATURE_XBAR_OUTPUT74_ID (XBAR_OUT_RESERVED74)
/* @brief XBAR output 75 ID. */
#define FSL_FEATURE_XBAR_OUTPUT75_ID (XBAR_OUT_RESERVED75)
/* @brief XBAR output 76 ID. */
#define FSL_FEATURE_XBAR_OUTPUT76_ID (XBAR_OUT_RESERVED76)
/* @brief XBAR output 77 ID. */
#define FSL_FEATURE_XBAR_OUTPUT77_ID (XBAR_OUT_RESERVED77)
/* @brief XBAR output 78 ID. */
#define FSL_FEATURE_XBAR_OUTPUT78_ID (XBAR_OUT_RESERVED78)
/* @brief XBAR output 79 ID. */
#define FSL_FEATURE_XBAR_OUTPUT79_ID (XBAR_OUT_RESERVED79)
/* @brief XBAR output 80 ID. */
#define FSL_FEATURE_XBAR_OUTPUT80_ID (XBAR_OUT_RESERVED80)
/* @brief XBAR output 81 ID. */
#define FSL_FEATURE_XBAR_OUTPUT81_ID (XBAR_OUT_RESERVED81)
/* @brief XBAR output 82 ID. */
#define FSL_FEATURE_XBAR_OUTPUT82_ID (XBAR_OUT_RESERVED82)
/* @brief XBAR output 83 ID. */
#define FSL_FEATURE_XBAR_OUTPUT83_ID (XBAR_OUT_RESERVED83)
/* @brief XBAR output 84 ID. */
#define FSL_FEATURE_XBAR_OUTPUT84_ID (XBAR_OUT_RESERVED84)
/* @brief XBAR output 85 ID. */
#define FSL_FEATURE_XBAR_OUTPUT85_ID (XBAR_OUT_RESERVED85)
/* @brief XBAR output 86 ID. */
#define FSL_FEATURE_XBAR_OUTPUT86_ID (XBAR_OUT_RESERVED86)
/* @brief XBAR output 87 ID. */
#define FSL_FEATURE_XBAR_OUTPUT87_ID (XBAR_OUT_RESERVED87)
/* @brief XBAR output 88 ID. */
#define FSL_FEATURE_XBAR_OUTPUT88_ID (XBAR_OUT_RESERVED88)
/* @brief XBAR output 89 ID. */
#define FSL_FEATURE_XBAR_OUTPUT89_ID (XBAR_OUT_RESERVED89)
/* @brief XBAR output 90 ID. */
#define FSL_FEATURE_XBAR_OUTPUT90_ID (XBAR_OUT_RESERVED90)
/* @brief XBAR output 91 ID. */
#define FSL_FEATURE_XBAR_OUTPUT91_ID (XBAR_OUT_RESERVED91)
/* @brief XBAR output 92 ID. */
#define FSL_FEATURE_XBAR_OUTPUT92_ID (XBAR_OUT_RESERVED92)
/* @brief XBAR output 93 ID. */
#define FSL_FEATURE_XBAR_OUTPUT93_ID (XBAR_OUT_RESERVED93)
/* @brief XBAR output 94 ID. */
#define FSL_FEATURE_XBAR_OUTPUT94_ID (XBAR_OUT_RESERVED94)
/* @brief XBAR output 95 ID. */
#define FSL_FEATURE_XBAR_OUTPUT95_ID (XBAR_OUT_RESERVED95)
/* @brief XBAR output 96 ID. */
#define FSL_FEATURE_XBAR_OUTPUT96_ID (XBAR_OUT_RESERVED96)
/* @brief XBAR output 97 ID. */
#define FSL_FEATURE_XBAR_OUTPUT97_ID (XBAR_OUT_RESERVED97)
/* @brief XBAR output 98 ID. */
#define FSL_FEATURE_XBAR_OUTPUT98_ID (XBAR_OUT_RESERVED98)
/* @brief XBAR output 99 ID. */
#define FSL_FEATURE_XBAR_OUTPUT99_ID (XBAR_OUT_RESERVED99)
/* @brief XBAR output 100 ID. */
#define FSL_FEATURE_XBAR_OUTPUT100_ID (XBAR_OUT_RESERVED100)
/* @brief XBAR output 101 ID. */
#define FSL_FEATURE_XBAR_OUTPUT101_ID (XBAR_OUT_RESERVED101)
/* @brief XBAR output 102 ID. */
#define FSL_FEATURE_XBAR_OUTPUT102_ID (XBAR_OUT_RESERVED102)
/* @brief XBAR output 103 ID. */
#define FSL_FEATURE_XBAR_OUTPUT103_ID (XBAR_OUT_RESERVED103)
/* @brief XBAR output 104 ID. */
#define FSL_FEATURE_XBAR_OUTPUT104_ID (XBAR_OUT_RESERVED104)
/* @brief XBAR output 105 ID. */
#define FSL_FEATURE_XBAR_OUTPUT105_ID (XBAR_OUT_RESERVED105)
/* @brief XBAR output 106 ID. */
#define FSL_FEATURE_XBAR_OUTPUT106_ID (XBAR_OUT_RESERVED106)
/* @brief XBAR output 107 ID. */
#define FSL_FEATURE_XBAR_OUTPUT107_ID (XBAR_OUT_RESERVED107)
/* @brief XBAR output 108 ID. */
#define FSL_FEATURE_XBAR_OUTPUT108_ID (XBAR_OUT_RESERVED108)
/* @brief XBAR output 109 ID. */
#define FSL_FEATURE_XBAR_OUTPUT109_ID (XBAR_OUT_RESERVED109)
/* @brief XBAR output 110 ID. */
#define FSL_FEATURE_XBAR_OUTPUT110_ID (XBAR_OUT_RESERVED110)
/* @brief XBAR output 111 ID. */
#define FSL_FEATURE_XBAR_OUTPUT111_ID (XBAR_OUT_RESERVED111)
/* @brief XBAR output 112 ID. */
#define FSL_FEATURE_XBAR_OUTPUT112_ID (XBAR_OUT_RESERVED112)
/* @brief XBAR output 113 ID. */
#define FSL_FEATURE_XBAR_OUTPUT113_ID (XBAR_OUT_RESERVED113)
/* @brief XBAR output 114 ID. */
#define FSL_FEATURE_XBAR_OUTPUT114_ID (XBAR_OUT_RESERVED114)
/* @brief XBAR output 115 ID. */
#define FSL_FEATURE_XBAR_OUTPUT115_ID (XBAR_OUT_RESERVED115)
/* @brief XBAR output 116 ID. */
#define FSL_FEATURE_XBAR_OUTPUT116_ID (XBAR_OUT_RESERVED116)
/* @brief XBAR output 117 ID. */
#define FSL_FEATURE_XBAR_OUTPUT117_ID (XBAR_OUT_RESERVED117)
/* @brief XBAR output 118 ID. */
#define FSL_FEATURE_XBAR_OUTPUT118_ID (XBAR_OUT_RESERVED118)
/* @brief XBAR output 119 ID. */
#define FSL_FEATURE_XBAR_OUTPUT119_ID (XBAR_OUT_RESERVED119)
/* @brief XBAR output 120 ID. */
#define FSL_FEATURE_XBAR_OUTPUT120_ID (XBAR_OUT_RESERVED120)
/* @brief XBAR output 121 ID. */
#define FSL_FEATURE_XBAR_OUTPUT121_ID (XBAR_OUT_RESERVED121)
/* @brief XBAR output 122 ID. */
#define FSL_FEATURE_XBAR_OUTPUT122_ID (XBAR_OUT_RESERVED122)
/* @brief XBAR output 123 ID. */
#define FSL_FEATURE_XBAR_OUTPUT123_ID (XBAR_OUT_RESERVED123)
/* @brief XBAR output 124 ID. */
#define FSL_FEATURE_XBAR_OUTPUT124_ID (XBAR_OUT_RESERVED124)
/* @brief XBAR output 125 ID. */
#define FSL_FEATURE_XBAR_OUTPUT125_ID (XBAR_OUT_RESERVED125)
/* @brief XBAR output 126 ID. */
#define FSL_FEATURE_XBAR_OUTPUT126_ID (XBAR_OUT_RESERVED126)
/* @brief XBAR output 127 ID. */
#define FSL_FEATURE_XBAR_OUTPUT127_ID (XBAR_OUT_RESERVED127)

#endif /* __FSL_MKM34Z7_FEATURES_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
