/*
** ###################################################################
**     Version:             rev. 1.0, 2024-03-11
**     Build:               b240411
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2024-03-11)
**         Initial version.
**
** ###################################################################
*/

#ifndef _MCXC444_FEATURES_H_
#define _MCXC444_FEATURES_H_

/* SOC module features */

/* @brief ADC16 availability on the SoC. */
#define FSL_FEATURE_SOC_ADC16_COUNT (1)
/* @brief CMP availability on the SoC. */
#define FSL_FEATURE_SOC_CMP_COUNT (1)
/* @brief DAC availability on the SoC. */
#define FSL_FEATURE_SOC_DAC_COUNT (1)
/* @brief DMA availability on the SoC. */
#define FSL_FEATURE_SOC_DMA_COUNT (1)
/* @brief DMAMUX availability on the SoC. */
#define FSL_FEATURE_SOC_DMAMUX_COUNT (1)
/* @brief FGPIO availability on the SoC. */
#define FSL_FEATURE_SOC_FGPIO_COUNT (5)
/* @brief FLEXIO availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXIO_COUNT (1)
/* @brief FTFA availability on the SoC. */
#define FSL_FEATURE_SOC_FTFA_COUNT (1)
/* @brief GPIO availability on the SoC. */
#define FSL_FEATURE_SOC_GPIO_COUNT (5)
/* @brief I2C availability on the SoC. */
#define FSL_FEATURE_SOC_I2C_COUNT (2)
/* @brief I2S availability on the SoC. */
#define FSL_FEATURE_SOC_I2S_COUNT (1)
/* @brief SLCD availability on the SoC. */
#define FSL_FEATURE_SOC_SLCD_COUNT (1)
/* @brief LLWU availability on the SoC. */
#define FSL_FEATURE_SOC_LLWU_COUNT (1)
/* @brief LPTMR availability on the SoC. */
#define FSL_FEATURE_SOC_LPTMR_COUNT (1)
/* @brief LPUART availability on the SoC. */
#define FSL_FEATURE_SOC_LPUART_COUNT (2)
/* @brief MCGLITE availability on the SoC. */
#define FSL_FEATURE_SOC_MCGLITE_COUNT (1)
/* @brief MCM availability on the SoC. */
#define FSL_FEATURE_SOC_MCM_COUNT (1)
/* @brief MTB availability on the SoC. */
#define FSL_FEATURE_SOC_MTB_COUNT (1)
/* @brief MTBDWT availability on the SoC. */
#define FSL_FEATURE_SOC_MTBDWT_COUNT (1)
/* @brief OSC availability on the SoC. */
#define FSL_FEATURE_SOC_OSC_COUNT (1)
/* @brief PIT availability on the SoC. */
#define FSL_FEATURE_SOC_PIT_COUNT (1)
/* @brief PMC availability on the SoC. */
#define FSL_FEATURE_SOC_PMC_COUNT (1)
/* @brief PORT availability on the SoC. */
#define FSL_FEATURE_SOC_PORT_COUNT (5)
/* @brief RCM availability on the SoC. */
#define FSL_FEATURE_SOC_RCM_COUNT (1)
/* @brief RFSYS availability on the SoC. */
#define FSL_FEATURE_SOC_RFSYS_COUNT (1)
/* @brief ROM availability on the SoC. */
#define FSL_FEATURE_SOC_ROM_COUNT (1)
/* @brief RTC availability on the SoC. */
#define FSL_FEATURE_SOC_RTC_COUNT (1)
/* @brief SIM availability on the SoC. */
#define FSL_FEATURE_SOC_SIM_COUNT (1)
/* @brief SMC availability on the SoC. */
#define FSL_FEATURE_SOC_SMC_COUNT (1)
/* @brief SPI availability on the SoC. */
#define FSL_FEATURE_SOC_SPI_COUNT (2)
/* @brief TPM availability on the SoC. */
#define FSL_FEATURE_SOC_TPM_COUNT (3)
/* @brief UART availability on the SoC. */
#define FSL_FEATURE_SOC_UART_COUNT (1)
/* @brief USB availability on the SoC. */
#define FSL_FEATURE_SOC_USB_COUNT (1)
/* @brief VREF availability on the SoC. */
#define FSL_FEATURE_SOC_VREF_COUNT (1)

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
#define FSL_FEATURE_ADC16_HAS_DIFF_MODE (1)
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
#define FSL_FEATURE_ADC16_CONVERSION_CONTROL_COUNT (2)

/* CMP module features */

/* @brief Has Trigger mode in CMP (register bit field CR1[TRIGM]). */
#define FSL_FEATURE_CMP_HAS_TRIGGER_MODE (1)
/* @brief Has Window mode in CMP (register bit field CR1[WE]). */
#define FSL_FEATURE_CMP_HAS_WINDOW_MODE (0)
/* @brief Has External sample supported in CMP (register bit field CR1[SE]). */
#define FSL_FEATURE_CMP_HAS_EXTERNAL_SAMPLE_SUPPORT (0)
/* @brief Has DMA support in CMP (register bit field SCR[DMAEN]). */
#define FSL_FEATURE_CMP_HAS_DMA (1)
/* @brief Has Pass Through mode in CMP (register bit field MUXCR[PSTM]). */
#define FSL_FEATURE_CMP_HAS_PASS_THROUGH_MODE (0)
/* @brief Has DAC Test function in CMP (register DACTEST). */
#define FSL_FEATURE_CMP_HAS_DAC_TEST (0)

/* COP module features */

/* @brief Has the COP Debug Enable bit (COPC[COPDBGEN]) */
#define FSL_FEATURE_COP_HAS_DEBUG_ENABLE (1)
/* @brief Has the COP Stop mode Enable bit (COPC[COPSTPEN]) */
#define FSL_FEATURE_COP_HAS_STOP_ENABLE (1)
/* @brief Has more clock sources like MCGIRC */
#define FSL_FEATURE_COP_HAS_MORE_CLKSRC (1)
/* @brief Has the timeout long and short mode bit (COPC[COPCLKS]) */
#define FSL_FEATURE_COP_HAS_LONGTIME_MODE (1)

/* DAC module features */

/* @brief Define the size of hardware buffer */
#define FSL_FEATURE_DAC_BUFFER_SIZE (2)
/* @brief Define whether the buffer supports watermark event detection or not. */
#define FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION (0)
/* @brief Define whether the buffer supports watermark selection detection or not. */
#define FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION (0)
/* @brief Define whether the buffer supports watermark event 1 word before buffer upper limit. */
#define FSL_FEATURE_DAC_HAS_WATERMARK_1_WORD (0)
/* @brief Define whether the buffer supports watermark event 2 words before buffer upper limit. */
#define FSL_FEATURE_DAC_HAS_WATERMARK_2_WORDS (0)
/* @brief Define whether the buffer supports watermark event 3 words before buffer upper limit. */
#define FSL_FEATURE_DAC_HAS_WATERMARK_3_WORDS (0)
/* @brief Define whether the buffer supports watermark event 4 words before buffer upper limit. */
#define FSL_FEATURE_DAC_HAS_WATERMARK_4_WORDS (0)
/* @brief Define whether FIFO buffer mode is available or not. */
#define FSL_FEATURE_DAC_HAS_BUFFER_FIFO_MODE (1)
/* @brief Define whether swing buffer mode is available or not.. */
#define FSL_FEATURE_DAC_HAS_BUFFER_SWING_MODE (0)

/* DMA module features */

/* @brief Number of DMA channels. */
#define FSL_FEATURE_DMA_MODULE_CHANNEL (4)
/* @brief Total number of DMA channels on all modules. */
#define FSL_FEATURE_DMA_DMAMUX_CHANNELS (4)

/* DMAMUX module features */

/* @brief Number of DMA channels (related to number of register CHCFGn). */
#define FSL_FEATURE_DMAMUX_MODULE_CHANNEL (4)
/* @brief Total number of DMA channels on all modules. */
#define FSL_FEATURE_DMAMUX_DMAMUX_CHANNELS (4)
/* @brief Has the periodic trigger capability for the triggered DMA channel (register bit CHCFG0[TRIG]). */
#define FSL_FEATURE_DMAMUX_HAS_TRIG (1)
/* @brief Register CHCFGn width. */
#define FSL_FEATURE_DMAMUX_CHCFG_REGISTER_WIDTH (8)

/* FGPIO module features */

/* No feature definitions */

/* FLEXIO module features */

/* @brief Has Shifter Status Register (FLEXIO_SHIFTSTAT) */
#define FSL_FEATURE_FLEXIO_HAS_SHIFTER_STATUS (1)
/* @brief Has Pin Data Input Register (FLEXIO_PIN) */
#define FSL_FEATURE_FLEXIO_HAS_PIN_STATUS (0)
/* @brief Has Shifter Buffer N Nibble Byte Swapped Register (FLEXIO_SHIFTBUFNBSn) */
#define FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_NIBBLE_BYTE_SWAP (0)
/* @brief Has Shifter Buffer N Half Word Swapped Register (FLEXIO_SHIFTBUFHWSn) */
#define FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_HALF_WORD_SWAP (0)
/* @brief Has Shifter Buffer N Nibble Swapped Register (FLEXIO_SHIFTBUFNISn) */
#define FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_NIBBLE_SWAP (0)
/* @brief Supports Shifter State Mode (FLEXIO_SHIFTCTLn[SMOD]) */
#define FSL_FEATURE_FLEXIO_HAS_STATE_MODE (0)
/* @brief Supports Shifter Logic Mode (FLEXIO_SHIFTCTLn[SMOD]) */
#define FSL_FEATURE_FLEXIO_HAS_LOGIC_MODE (0)
/* @brief Supports paralle width (FLEXIO_SHIFTCFGn[PWIDTH]) */
#define FSL_FEATURE_FLEXIO_HAS_PARALLEL_WIDTH (0)
/* @brief Reset value of the FLEXIO_VERID register */
#define FSL_FEATURE_FLEXIO_VERID_RESET_VALUE (0x1000000)
/* @brief Reset value of the FLEXIO_PARAM register */
#define FSL_FEATURE_FLEXIO_PARAM_RESET_VALUE (0x10080404)
/* @brief Represent the bit width of the TIMDCE field (FLEXIO_TIMCFGLn[TIMDEC]) */
#define FSL_FEATURE_FLEXIO_TIMCFG_TIMDCE_FIELD_WIDTH (2)
/* @brief Flexio DMA request base channel */
#define FSL_FEATURE_FLEXIO_DMA_REQUEST_BASE_CHANNEL (0)

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
/* @brief Has flash cache control in MSCM module. */
#define FSL_FEATURE_FLASH_HAS_MSCM_FLASH_CACHE_CONTROLS (0)
/* @brief Has prefetch speculation control in flash, such as kv5x. */
#define FSL_FEATURE_FLASH_PREFETCH_SPECULATION_CONTROL_IN_FLASH (0)
/* @brief P-Flash flash size coding rule version, value 0 for K1 and K2, value 1 for K3. */
#define FSL_FEATURE_FLASH_SIZE_ENCODING_RULE_VERSION (0)
/* @brief P-Flash start address. */
#define FSL_FEATURE_FLASH_PFLASH_START_ADDRESS (0x00000000)
/* @brief P-Flash block count. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_COUNT (2)
/* @brief P-Flash block size. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_SIZE (131072)
/* @brief P-Flash sector size. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE (1024)
/* @brief P-Flash write unit size. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE (4)
/* @brief P-Flash data path width. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_DATA_PATH_WIDTH (4)
/* @brief P-Flash block swap feature. */
#define FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP (0)
/* @brief P-Flash protection region count. */
#define FSL_FEATURE_FLASH_PFLASH_PROTECTION_REGION_COUNT (32)
/* @brief Has FlexNVM memory. */
#define FSL_FEATURE_FLASH_HAS_FLEX_NVM (0)
/* @brief Has FlexNVM alias. */
#define FSL_FEATURE_FLASH_HAS_FLEX_NVM_ALIAS (0)
/* @brief FlexNVM start address. (Valid only if FlexNVM is available.) */
#define FSL_FEATURE_FLASH_FLEX_NVM_START_ADDRESS (0x00000000)
/* @brief FlexNVM alias start address. (Valid only if FlexNVM alias is available.) */
#define FSL_FEATURE_FLASH_FLEX_NVM_ALIAS_START_ADDRESS (0x00000000)
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
#define FSL_FEATURE_FLASH_HAS_READ_1S_BLOCK_CMD (1)
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
#define FSL_FEATURE_FLASH_HAS_ERASE_FLASH_BLOCK_CMD (1)
/* @brief Has 0x09 Erase Flash Sector command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_FLASH_SECTOR_CMD (1)
/* @brief Has 0x0B Program Section command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD (0)
/* @brief Has 0x40 Read 1s All Blocks command. */
#define FSL_FEATURE_FLASH_HAS_READ_1S_ALL_BLOCKS_CMD (1)
/* @brief Has 0x41 Read Once command. */
#define FSL_FEATURE_FLASH_HAS_READ_ONCE_CMD (1)
/* @brief Has 0x43 Program Once command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_ONCE_CMD (1)
/* @brief Has 0x44 Erase All Blocks command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_CMD (1)
/* @brief Has 0x45 Verify Backdoor Access Key command. */
#define FSL_FEATURE_FLASH_HAS_VERIFY_BACKDOOR_ACCESS_KEY_CMD (1)
/* @brief Has 0x46 Swap Control command. */
#define FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD (0)
/* @brief Has 0x49 Erase All Blocks Unsecure command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD (1)
/* @brief Has 0x4A Read 1s All Execute-only Segments command. */
#define FSL_FEATURE_FLASH_HAS_READ_1S_ALL_EXECUTE_ONLY_SEGMENTS_CMD (0)
/* @brief Has 0x4B Erase All Execute-only Segments command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_ALL_EXECUTE_ONLY_SEGMENTS_CMD (0)
/* @brief Has 0x80 Program Partition command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_PARTITION_CMD (0)
/* @brief Has 0x81 Set FlexRAM Function command. */
#define FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD (0)
/* @brief P-Flash Erase/Read 1st all block command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_CMD_ADDRESS_ALIGMENT (4)
/* @brief P-Flash Erase sector command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT (4)
/* @brief P-Flash Rrogram/Verify section command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT (4)
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
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0000 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 0001 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0001 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 0010 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0010 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 0011 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0011 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 0100 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0100 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 0101 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0101 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 0110 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0110 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 0111 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0111 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 1000 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1000 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 1001 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1001 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 1010 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1010 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 1011 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1011 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 1100 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1100 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 1101 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1101 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 1110 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1110 (0xFFFFFFFFU)
/* @brief FlexNVM partition code 1111 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1111 (0xFFFFFFFFU)
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

/* @brief Has GPIO attribute checker register (GACR). */
#define FSL_FEATURE_GPIO_HAS_ATTRIBUTE_CHECKER (0)

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
/* @brief Has double buffer enable. */
#define FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE (0)

/* SAI module features */

/* @brief SAI has FIFO in this soc (register bit fields TCR1[TFW]. */
#define FSL_FEATURE_SAI_HAS_FIFO (0)
/* @brief Receive/transmit FIFO size in item count (register bit fields TCSR[FRDE], TCSR[FRIE], TCSR[FRF], TCR1[TFW], RCSR[FRDE], RCSR[FRIE], RCSR[FRF], RCR1[RFW], registers TFRn, RFRn). */
#define FSL_FEATURE_SAI_FIFO_COUNTn(x) (0)
/* @brief Receive/transmit channel number (register bit fields TCR3[TCE], RCR3[RCE], registers TDRn and RDRn). */
#define FSL_FEATURE_SAI_CHANNEL_COUNTn(x) (1)
/* @brief Maximum words per frame (register bit fields TCR3[WDFL], TCR4[FRSZ], TMR[TWM], RCR3[WDFL], RCR4[FRSZ], RMR[RWM]). */
#define FSL_FEATURE_SAI_MAX_WORDS_PER_FRAME (2)
/* @brief Has support of combining multiple data channel FIFOs into single channel FIFO (register bit fields TCR3[CFR], TCR4[FCOMB], TFR0[WCP], TFR1[WCP], RCR3[CFR], RCR4[FCOMB], RFR0[RCP], RFR1[RCP]). */
#define FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE (0)
/* @brief Has packing of 8-bit and 16-bit data into each 32-bit FIFO word (register bit fields TCR4[FPACK], RCR4[FPACK]). */
#define FSL_FEATURE_SAI_HAS_FIFO_PACKING (1)
/* @brief Configures when the SAI will continue transmitting after a FIFO error has been detected (register bit fields TCR4[FCONT], RCR4[FCONT]). */
#define FSL_FEATURE_SAI_HAS_FIFO_FUNCTION_AFTER_ERROR (1)
/* @brief Configures if the frame sync is generated internally, a frame sync is only generated when the FIFO warning flag is clear or continuously (register bit fields TCR4[ONDEM], RCR4[ONDEM]). */
#define FSL_FEATURE_SAI_HAS_ON_DEMAND_MODE (1)
/* @brief Simplified bit clock source and asynchronous/synchronous mode selection (register bit fields TCR2[CLKMODE], RCR2[CLKMODE]), in comparison with the exclusively implemented TCR2[SYNC,BCS,BCI,MSEL], RCR2[SYNC,BCS,BCI,MSEL]. */
#define FSL_FEATURE_SAI_HAS_CLOCKING_MODE (0)
/* @brief Has register for configuration of the MCLK divide ratio (register bit fields MDR[FRACT], MDR[DIVIDE]). */
#define FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER (0)
/* @brief Ihe interrupt source number */
#define FSL_FEATURE_SAI_INT_SOURCE_NUM (1)
/* @brief Has register of MCR. */
#define FSL_FEATURE_SAI_HAS_MCR (1)
/* @brief Has register of MDR */
#define FSL_FEATURE_SAI_HAS_MDR (0)
/* @brief Has DIV bit fields of MCR register (register bit fields MCR[DIV]. */
#define FSL_FEATURE_SAI_HAS_MCR_MCLK_POST_DIV (0)
/* @brief Support Channel Mode (register bit fields TCR4[CHMOD]). */
#define FSL_FEATURE_SAI_HAS_CHANNEL_MODE (0)

/* SLCD module features */

/* @brief Has Multi Alternate Clock Source (register bit GCR[ATLSOURCE]).  */
#define FSL_FEATURE_SLCD_HAS_MULTI_ALTERNATE_CLOCK_SOURCE (1)
/* @brief Has fast frame rate (register bit GCR[FFR]). */
#define FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE (1)
/* @brief Has frame frequency interrupt (register bit GCR[LCDIEN]). */
#define FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT (0)
/* @brief Has high reference select (register bit GCR[HREFSEL]). */
#define FSL_FEATURE_SLCD_HAS_HIGH_REFERENCE_SELECT (0)
/* @brief Has pad safe (register bit GCR[PADSAFE]). */
#define FSL_FEATURE_SLCD_HAS_PAD_SAFE (1)
/* @brief Has lcd wait (register bit GCR[LCDWAIT]). */
#define FSL_FEATURE_SLCD_HAS_LCD_WAIT (0)
/* @brief Has lcd doze enable (register bit GCR[LCDDOZE]). */
#define FSL_FEATURE_SLCD_HAS_LCD_DOZE_ENABLE (1)
/* @brief Total pin number on LCD. */
#define FSL_FEATURE_SLCD_HAS_PIN_NUM (64)
/* @brief Total phase number on SLCD. */
#define FSL_FEATURE_SLCD_HAS_PHASE_NUM (8)

/* LLWU module features */

/* @brief Maximum number of pins (maximal index plus one) connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN (16)
/* @brief Has pins 8-15 connected to LLWU device. */
#define FSL_FEATURE_LLWU_EXTERNAL_PIN_GROUP2 (1)
/* @brief Maximum number of internal modules connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE (8)
/* @brief Number of digital filters. */
#define FSL_FEATURE_LLWU_HAS_PIN_FILTER (2)
/* @brief Has MF register. */
#define FSL_FEATURE_LLWU_HAS_MF (0)
/* @brief Has PF register. */
#define FSL_FEATURE_LLWU_HAS_PF (0)
/* @brief Has possibility to enable reset in low leakage power mode and enable digital filter for RESET pin (register LLWU_RST). */
#define FSL_FEATURE_LLWU_HAS_RESET_ENABLE (0)
/* @brief Has no internal module wakeup flag register. */
#define FSL_FEATURE_LLWU_HAS_NO_INTERNAL_MODULE_WAKEUP_FLAG_REG (0)
/* @brief Has external pin 0 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN0 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN0_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN0_GPIO_PIN (0)
/* @brief Has external pin 1 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN1 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN1_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN1_GPIO_PIN (0)
/* @brief Has external pin 2 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN2 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN2_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN2_GPIO_PIN (0)
/* @brief Has external pin 3 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN3 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN3_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN3_GPIO_PIN (0)
/* @brief Has external pin 4 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN4 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN4_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN4_GPIO_PIN (0)
/* @brief Has external pin 5 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN5 (1)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN5_GPIO_IDX (GPIOB_IDX)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN5_GPIO_PIN (0)
/* @brief Has external pin 6 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN6 (1)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN6_GPIO_IDX (GPIOC_IDX)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN6_GPIO_PIN (1)
/* @brief Has external pin 7 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN7 (1)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN7_GPIO_IDX (GPIOC_IDX)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN7_GPIO_PIN (3)
/* @brief Has external pin 8 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN8 (1)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN8_GPIO_IDX (GPIOC_IDX)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN8_GPIO_PIN (4)
/* @brief Has external pin 9 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN9 (1)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN9_GPIO_IDX (GPIOC_IDX)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN9_GPIO_PIN (5)
/* @brief Has external pin 10 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN10 (1)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN10_GPIO_IDX (GPIOC_IDX)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN10_GPIO_PIN (6)
/* @brief Has external pin 11 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN11 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN11_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN11_GPIO_PIN (0)
/* @brief Has external pin 12 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN12 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN12_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN12_GPIO_PIN (0)
/* @brief Has external pin 13 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN13 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN13_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN13_GPIO_PIN (0)
/* @brief Has external pin 14 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN14 (1)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN14_GPIO_IDX (GPIOD_IDX)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN14_GPIO_PIN (4)
/* @brief Has external pin 15 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN15 (1)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN15_GPIO_IDX (GPIOD_IDX)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN15_GPIO_PIN (6)
/* @brief Has external pin 16 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN16 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN16_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN16_GPIO_PIN (0)
/* @brief Has external pin 17 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN17 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN17_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN17_GPIO_PIN (0)
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
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN20 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN20_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN20_GPIO_PIN (0)
/* @brief Has external pin 21 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN21 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN21_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN21_GPIO_PIN (0)
/* @brief Has external pin 22 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN22 (0)
/* @brief Index of port of external pin. */
#define FSL_FEATURE_LLWU_PIN22_GPIO_IDX (0)
/* @brief Number of external pin port on specified port. */
#define FSL_FEATURE_LLWU_PIN22_GPIO_PIN (0)
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
#define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE2 (0)
/* @brief Has internal module 3 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE3 (0)
/* @brief Has internal module 4 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE4 (0)
/* @brief Has internal module 5 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE5 (1)
/* @brief Has internal module 6 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE6 (0)
/* @brief Has internal module 7 connected to LLWU device. */
#define FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE7 (1)
/* @brief Has Version ID Register (LLWU_VERID). */
#define FSL_FEATURE_LLWU_HAS_VERID (0)
/* @brief Has Parameter Register (LLWU_PARAM). */
#define FSL_FEATURE_LLWU_HAS_PARAM (0)
/* @brief Width of registers of the LLWU. */
#define FSL_FEATURE_LLWU_REG_BITWIDTH (8)
/* @brief Has DMA Enable register (LLWU_DE). */
#define FSL_FEATURE_LLWU_HAS_DMA_ENABLE_REG (0)

/* LPTMR module features */

/* @brief Has shared interrupt handler with another LPTMR module. */
#define FSL_FEATURE_LPTMR_HAS_SHARED_IRQ_HANDLER (0)
/* @brief Whether LPTMR counter is 32 bits width. */
#define FSL_FEATURE_LPTMR_CNR_WIDTH_IS_32B (0)
/* @brief Has timer DMA request enable (register bit CSR[TDRE]). */
#define FSL_FEATURE_LPTMR_HAS_CSR_TDRE (0)

/* LPUART module features */

/* @brief LPUART0 and LPUART1 has shared interrupt vector. */
#define FSL_FEATURE_LPUART_HAS_SHARED_IRQ0_IRQ1 (0)
/* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
#define FSL_FEATURE_LPUART_HAS_IRQ_EXTENDED_FUNCTIONS (0)
/* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_LOW_POWER_UART_SUPPORT (1)
/* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_LPUART_HAS_FIFO (0)
/* @brief Has 32-bit register MODIR */
#define FSL_FEATURE_LPUART_HAS_MODIR (0)
/* @brief Hardware flow control (RTS, CTS) is supported. */
#define FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT (0)
/* @brief Infrared (modulation) is supported. */
#define FSL_FEATURE_LPUART_HAS_IR_SUPPORT (0)
/* @brief 2 bits long stop bit is available. */
#define FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
/* @brief If 10-bit mode is supported. */
#define FSL_FEATURE_LPUART_HAS_10BIT_DATA_SUPPORT (1)
/* @brief If 7-bit mode is supported. */
#define FSL_FEATURE_LPUART_HAS_7BIT_DATA_SUPPORT (0)
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
#define FSL_FEATURE_LPUART_FIFO_SIZEn(x) (0)
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
/* @brief Lin break detect available (has bit BAUD[LBKDIE]). */
#define FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT (1)
/* @brief UART stops in Wait mode available (has bit C1[UARTSWAI]). */
#define FSL_FEATURE_LPUART_HAS_WAIT_MODE_OPERATION (0)
/* @brief Has separate DMA RX and TX requests. */
#define FSL_FEATURE_LPUART_HAS_SEPARATE_DMA_RX_TX_REQn(x) (1)
/* @brief Has separate RX and TX interrupts. */
#define FSL_FEATURE_LPUART_HAS_SEPARATE_RX_TX_IRQ (0)
/* @brief Has LPAURT_PARAM. */
#define FSL_FEATURE_LPUART_HAS_PARAM (0)
/* @brief Has LPUART_VERID. */
#define FSL_FEATURE_LPUART_HAS_VERID (0)
/* @brief Has LPUART_GLOBAL. */
#define FSL_FEATURE_LPUART_HAS_GLOBAL (0)
/* @brief Has LPUART_PINCFG. */
#define FSL_FEATURE_LPUART_HAS_PINCFG (0)

/* MCGLITE module features */

/* @brief Defines that clock generator is MCG Lite. */
#define FSL_FEATURE_MCGLITE_MCGLITE (1)
/* @brief Has Crystal Oscillator Operation Mode Selection. */
#define FSL_FEATURE_MCGLITE_HAS_HGO0 (1)
/* @brief Has HCTRIM register available. */
#define FSL_FEATURE_MCGLITE_HAS_HCTRIM (1)
/* @brief Has HTTRIM register available. */
#define FSL_FEATURE_MCGLITE_HAS_HTTRIM (1)
/* @brief Has HFTRIM register available. */
#define FSL_FEATURE_MCGLITE_HAS_HFTRIM (1)
/* @brief Has LTRIMRNG register available. */
#define FSL_FEATURE_MCGLITE_HAS_LTRIMRNG (1)
/* @brief Has LFTRIM register available. */
#define FSL_FEATURE_MCGLITE_HAS_LFTRIM (1)
/* @brief Has LSTRIM register available. */
#define FSL_FEATURE_MCGLITE_HAS_LSTRIM (1)
/* @brief Has External Clock Source Frequency Range Selection. */
#define FSL_FEATURE_MCGLITE_HAS_RANGE0 (1)

/* interrupt module features */

/* @brief Lowest interrupt request number. */
#define FSL_FEATURE_INTERRUPT_IRQ_MIN (-14)
/* @brief Highest interrupt request number. */
#define FSL_FEATURE_INTERRUPT_IRQ_MAX (31)

/* OSC module features */

/* @brief Has OSC1 external oscillator. */
#define FSL_FEATURE_OSC_HAS_OSC1 (0)
/* @brief Has OSC0 external oscillator. */
#define FSL_FEATURE_OSC_HAS_OSC0 (1)
/* @brief Has OSC external oscillator (without index). */
#define FSL_FEATURE_OSC_HAS_OSC (0)
/* @brief Number of OSC external oscillators. */
#define FSL_FEATURE_OSC_OSC_COUNT (1)
/* @brief Has external reference clock divider (register bit field DIV[ERPS]). */
#define FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER (0)

/* PIT module features */

/* @brief Number of channels (related to number of registers LDVALn, CVALn, TCTRLn, TFLGn). */
#define FSL_FEATURE_PIT_TIMER_COUNT (2)
/* @brief Has lifetime timer (related to existence of registers LTMR64L and LTMR64H). */
#define FSL_FEATURE_PIT_HAS_LIFETIME_TIMER (1)
/* @brief Has chain mode (related to existence of register bit field TCTRLn[CHN]). */
#define FSL_FEATURE_PIT_HAS_CHAIN_MODE (1)
/* @brief Has shared interrupt handler (has not individual interrupt handler for each channel). */
#define FSL_FEATURE_PIT_HAS_SHARED_IRQ_HANDLER (1)
/* @brief Has timer enable control. */
#define FSL_FEATURE_PIT_HAS_MDIS (1)
/* @brief Has ERRATA 7914. */
#define FSL_FEATURE_PIT_HAS_ERRATA_7914 (1)

/* PMC module features */

/* @brief Has Bandgap Enable In VLPx Operation support. */
#define FSL_FEATURE_PMC_HAS_BGEN (1)
/* @brief Has Bandgap Buffer Enable. */
#define FSL_FEATURE_PMC_HAS_BGBE (1)
/* @brief Has Bandgap Buffer Drive Select. */
#define FSL_FEATURE_PMC_HAS_BGBDS (0)
/* @brief Has Low-Voltage Detect Voltage Select support. */
#define FSL_FEATURE_PMC_HAS_LVDV (1)
/* @brief Has Low-Voltage Warning Voltage Select support. */
#define FSL_FEATURE_PMC_HAS_LVWV (1)
/* @brief Has LPO. */
#define FSL_FEATURE_PMC_HAS_LPO (0)
/* @brief Has VLPx option PMC_REGSC[VLPO]. */
#define FSL_FEATURE_PMC_HAS_VLPO (0)
/* @brief Has acknowledge isolation support. */
#define FSL_FEATURE_PMC_HAS_ACKISO (1)
/* @brief Has Regulator In Full Performance Mode Status Bit PMC_REGSC[REGFPM]. */
#define FSL_FEATURE_PMC_HAS_REGFPM (0)
/* @brief Has Regulator In Run Regulation Status Bit PMC_REGSC[REGONS]. */
#define FSL_FEATURE_PMC_HAS_REGONS (1)
/* @brief Has PMC_HVDSC1. */
#define FSL_FEATURE_PMC_HAS_HVDSC1 (0)
/* @brief Has PMC_PARAM. */
#define FSL_FEATURE_PMC_HAS_PARAM (0)
/* @brief Has PMC_VERID. */
#define FSL_FEATURE_PMC_HAS_VERID (0)

/* PORT module features */

/* @brief Has control lock (register bit PCR[LK]). */
#define FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK (0)
/* @brief Has open drain control (register bit PCR[ODE]). */
#define FSL_FEATURE_PORT_HAS_OPEN_DRAIN (0)
/* @brief Has digital filter (registers DFER, DFCR and DFWR). */
#define FSL_FEATURE_PORT_HAS_DIGITAL_FILTER (0)
/* @brief Has DMA request (register bit field PCR[IRQC] values). */
#define FSL_FEATURE_PORT_HAS_DMA_REQUEST (1)
/* @brief Has pull resistor selection available. */
#define FSL_FEATURE_PORT_HAS_PULL_SELECTION (1)
/* @brief Has pull resistor enable (register bit PCR[PE]). */
#define FSL_FEATURE_PORT_HAS_PULL_ENABLE (1)
/* @brief Has slew rate control (register bit PCR[SRE]). */
#define FSL_FEATURE_PORT_HAS_SLEW_RATE (1)
/* @brief Has passive filter (register bit field PCR[PFE]). */
#define FSL_FEATURE_PORT_HAS_PASSIVE_FILTER (1)
/* @brief Has drive strength control (register bit PCR[DSE]). */
#define FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH (1)
/* @brief Has separate drive strength register (HDRVE). */
#define FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH_REGISTER (0)
/* @brief Has glitch filter (register IOFLT). */
#define FSL_FEATURE_PORT_HAS_GLITCH_FILTER (0)
/* @brief Defines width of PCR[MUX] field. */
#define FSL_FEATURE_PORT_PCR_MUX_WIDTH (3)
/* @brief Has dedicated interrupt vector. */
#define FSL_FEATURE_PORT_HAS_INTERRUPT_VECTOR (1)
/* @brief Has multiple pin IRQ configuration (register GICLR and GICHR). */
#define FSL_FEATURE_PORT_HAS_MULTIPLE_IRQ_CONFIG (0)
/* @brief Defines whether PCR[IRQC] bit-field has flag states. */
#define FSL_FEATURE_PORT_HAS_IRQC_FLAG (0)
/* @brief Defines whether PCR[IRQC] bit-field has trigger states. */
#define FSL_FEATURE_PORT_HAS_IRQC_TRIGGER (0)

/* RCM module features */

/* @brief Has Loss-of-Lock Reset support. */
#define FSL_FEATURE_RCM_HAS_LOL (0)
/* @brief Has Loss-of-Clock Reset support. */
#define FSL_FEATURE_RCM_HAS_LOC (0)
/* @brief Has JTAG generated Reset support. */
#define FSL_FEATURE_RCM_HAS_JTAG (0)
/* @brief Has EzPort generated Reset support. */
#define FSL_FEATURE_RCM_HAS_EZPORT (0)
/* @brief Has bit-field indicating EZP_MS_B pin state during last reset. */
#define FSL_FEATURE_RCM_HAS_EZPMS (0)
/* @brief Has boot ROM configuration, MR[BOOTROM], FM[FORCEROM] */
#define FSL_FEATURE_RCM_HAS_BOOTROM (1)
/* @brief Has sticky system reset status register RCM_SSRS0 and RCM_SSRS1. */
#define FSL_FEATURE_RCM_HAS_SSRS (1)
/* @brief Has Version ID Register (RCM_VERID). */
#define FSL_FEATURE_RCM_HAS_VERID (0)
/* @brief Has Parameter Register (RCM_PARAM). */
#define FSL_FEATURE_RCM_HAS_PARAM (0)
/* @brief Has Reset Interrupt Enable Register RCM_SRIE. */
#define FSL_FEATURE_RCM_HAS_SRIE (0)
/* @brief Width of registers of the RCM. */
#define FSL_FEATURE_RCM_REG_WIDTH (8)
/* @brief Has Core 1 generated Reset support RCM_SRS[CORE1] */
#define FSL_FEATURE_RCM_HAS_CORE1 (0)
/* @brief Has MDM-AP system reset support RCM_SRS1[MDM_AP] */
#define FSL_FEATURE_RCM_HAS_MDM_AP (1)
/* @brief Has wakeup reset feature. Register bit SRS[WAKEUP]. */
#define FSL_FEATURE_RCM_HAS_WAKEUP (1)

/* RTC module features */

/* @brief Has wakeup pin. */
#define FSL_FEATURE_RTC_HAS_WAKEUP_PIN (1)
/* @brief Has wakeup pin selection (bit field CR[WPS]). */
#define FSL_FEATURE_RTC_HAS_WAKEUP_PIN_SELECTION (1)
/* @brief Has low power features (registers MER, MCLR and MCHR). */
#define FSL_FEATURE_RTC_HAS_MONOTONIC (0)
/* @brief Has read/write access control (registers WAR and RAR). */
#define FSL_FEATURE_RTC_HAS_ACCESS_CONTROL (0)
/* @brief Has security features (registers TTSR, MER, MCLR and MCHR). */
#define FSL_FEATURE_RTC_HAS_SECURITY (0)
/* @brief Has RTC_CLKIN available. */
#define FSL_FEATURE_RTC_HAS_RTC_CLKIN (1)
/* @brief Has prescaler adjust for LPO. */
#define FSL_FEATURE_RTC_HAS_LPO_ADJUST (0)
/* @brief Has Clock Pin Enable field. */
#define FSL_FEATURE_RTC_HAS_CPE (0)
/* @brief Has Timer Seconds Interrupt Configuration field. */
#define FSL_FEATURE_RTC_HAS_TSIC (0)
/* @brief Has OSC capacitor setting RTC_CR[SC2P ~ SC16P] */
#define FSL_FEATURE_RTC_HAS_OSC_SCXP (1)
/* @brief Has Tamper Interrupt Register (register TIR). */
#define FSL_FEATURE_RTC_HAS_TIR (0)
/* @brief Has Tamper Pin Interrupt Enable (bitfield TIR[TPIE]). */
#define FSL_FEATURE_RTC_HAS_TIR_TPIE (0)
/* @brief Has Security Interrupt Enable (bitfield TIR[SIE]). */
#define FSL_FEATURE_RTC_HAS_TIR_SIE (0)
/* @brief Has Loss of Clock Interrupt Enable (bitfield TIR[LCIE]). */
#define FSL_FEATURE_RTC_HAS_TIR_LCIE (0)
/* @brief Has Tamper Interrupt Detect Flag (bitfield SR[TIDF]). */
#define FSL_FEATURE_RTC_HAS_SR_TIDF (0)
/* @brief Has Tamper Detect Register (register TDR). */
#define FSL_FEATURE_RTC_HAS_TDR (0)
/* @brief Has Tamper Pin Flag (bitfield TDR[TPF]). */
#define FSL_FEATURE_RTC_HAS_TDR_TPF (0)
/* @brief Has Security Tamper Flag (bitfield TDR[STF]). */
#define FSL_FEATURE_RTC_HAS_TDR_STF (0)
/* @brief Has Loss of Clock Tamper Flag (bitfield TDR[LCTF]). */
#define FSL_FEATURE_RTC_HAS_TDR_LCTF (0)
/* @brief Has Tamper Time Seconds Register (register TTSR). */
#define FSL_FEATURE_RTC_HAS_TTSR (0)
/* @brief Has Pin Configuration Register (register PCR). */
#define FSL_FEATURE_RTC_HAS_PCR (0)

/* SIM module features */

/* @brief Has USB FS divider. */
#define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
/* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
#define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
/* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
#define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (0)
/* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
#define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (1)
/* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
/* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
#define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
/* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
/* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
#define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (1)
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
#define FSL_FEATURE_SIM_OPT_HAS_ODE (1)
/* @brief Number of LPUART modules (number of register bits LPUARTn, where n is a number, in register SCGC5). */
#define FSL_FEATURE_SIM_OPT_LPUART_COUNT (2)
/* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
#define FSL_FEATURE_SIM_OPT_UART_COUNT (1)
/* @brief Has UART0 open drain enable (register bit SOPT5[UART0ODE]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART0_ODE (0)
/* @brief Has UART1 open drain enable (register bit SOPT5[UART1ODE]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART1_ODE (0)
/* @brief Has UART2 open drain enable (register bit SOPT5[UART2ODE]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART2_ODE (1)
/* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (1)
/* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (1)
/* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
#define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
/* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (1)
/* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (1)
/* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (1)
/* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (1)
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
#define FSL_FEATURE_SIM_OPT_HAS_TPM (1)
/* @brief The highest TPM module index. */
#define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (2)
/* @brief Has TPM module with index 0. */
#define FSL_FEATURE_SIM_OPT_HAS_TPM0 (1)
/* @brief Has TPM0 clock selection (register bit field SOPT4[TPM0CLKSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM0_CLK_SEL (1)
/* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (1)
/* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (1)
/* @brief Has TPM1 clock selection (register bit field SOPT4[TPM1CLKSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM1_CLK_SEL (1)
/* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
#define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (2)
/* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (1)
/* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (1)
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
#define FSL_FEATURE_SIM_OPT_HAS_USBSRC (1)
/* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
/* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
/* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
/* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (1)
/* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (1)
/* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (1)
/* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
/* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
#define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (1)
/* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
#define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (0)
/* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
#define FSL_FEATURE_SIM_OPT_ADC_COUNT (1)
/* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (0)
/* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
/* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
#define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
/* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
#define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (3)
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
#define FSL_FEATURE_SIM_SDID_HAS_DIEID (0)
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
#define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
/* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
#define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
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
#define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (1)
/* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
#define FSL_FEATURE_SIM_HAS_COP_STOP (1)
/* @brief Has LLWU clock gate bit (e.g SIM_SCGC4). */
#define FSL_FEATURE_SIM_HAS_SCGC_LLWU (0)
/* @brief Has UIDH registers. */
#define FSL_FEATURE_SIM_HAS_UIDH (0)
/* @brief Has UIDM registers. */
#define FSL_FEATURE_SIM_HAS_UIDM (0)

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
#define FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE (1)
/* @brief Has very low leakage stop mode (register bit PMPROT[AVLLS]). */
#define FSL_FEATURE_SMC_HAS_VERY_LOW_LEAKAGE_STOP_MODE (1)
/* @brief Has stop submode. */
#define FSL_FEATURE_SMC_HAS_SUB_STOP_MODE (1)
/* @brief Has stop submode 0(VLLS0). */
#define FSL_FEATURE_SMC_HAS_STOP_SUBMODE0 (1)
/* @brief Has stop submode 1(VLLS1). */
#define FSL_FEATURE_SMC_HAS_STOP_SUBMODE1 (1)
/* @brief Has stop submode 2(VLLS2). */
#define FSL_FEATURE_SMC_HAS_STOP_SUBMODE2 (0)
/* @brief Has SMC_PARAM. */
#define FSL_FEATURE_SMC_HAS_PARAM (0)
/* @brief Has SMC_VERID. */
#define FSL_FEATURE_SMC_HAS_VERID (0)
/* @brief Has stop abort flag (register bit PMCTRL[STOPA]). */
#define FSL_FEATURE_SMC_HAS_PMCTRL_STOPA (1)
/* @brief Has tamper reset (register bit SRS[TAMPER]). */
#define FSL_FEATURE_SMC_HAS_SRS_TAMPER (0)
/* @brief Has security violation reset (register bit SRS[SECVIO]). */
#define FSL_FEATURE_SMC_HAS_SRS_SECVIO (0)
/* @brief Width of SMC registers. */
#define FSL_FEATURE_SMC_REG_WIDTH (8)

/* SPI module features */

/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_SPI_HAS_FIFO (1)
/* @brief Has DMA support (register bit fields C2[RXDMAE] and C2[TXDMAE]). */
#define FSL_FEATURE_SPI_HAS_DMA_SUPPORT (1)
/* @brief Has separate DMA RX and TX requests. */
#define FSL_FEATURE_SPI_HAS_SEPARATE_DMA_RX_TX_REQn(x) (1)
/* @brief Receive/transmit FIFO size in number of 16-bit communication items. */
#define FSL_FEATURE_SPI_FIFO_SIZEn(x) \
    (((x) == SPI0) ? (0) : \
    (((x) == SPI1) ? (4) : (-1)))
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

/* TPM module features */

/* @brief Bus clock is the source clock for the module. */
#define FSL_FEATURE_TPM_BUS_CLOCK (0)
/* @brief Number of channels. */
#define FSL_FEATURE_TPM_CHANNEL_COUNTn(x) \
    (((x) == TPM0) ? (6) : \
    (((x) == TPM1) ? (2) : \
    (((x) == TPM2) ? (2) : (-1))))
/* @brief Has counter reset by the selected input capture event (register bits C0SC[ICRST], C1SC[ICRST], ...). */
#define FSL_FEATURE_TPM_HAS_COUNTER_RESET_BY_CAPTURE_EVENT (0)
/* @brief Has TPM_PARAM. */
#define FSL_FEATURE_TPM_HAS_PARAM (0)
/* @brief Has TPM_VERID. */
#define FSL_FEATURE_TPM_HAS_VERID (0)
/* @brief Has TPM_GLOBAL. */
#define FSL_FEATURE_TPM_HAS_GLOBAL (0)
/* @brief Has TPM_TRIG. */
#define FSL_FEATURE_TPM_HAS_TRIG (0)
/* @brief Whether TRIG register has effect. */
#define FSL_FEATURE_TPM_TRIG_HAS_EFFECTn(x) \
    (((x) == TPM0) ? (1) : \
    (((x) == TPM1) ? (0) : \
    (((x) == TPM2) ? (0) : (-1))))
/* @brief Has counter pause on trigger. */
#define FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER (1)
/* @brief Has external trigger selection. */
#define FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION (1)
/* @brief Has TPM_COMBINE register. */
#define FSL_FEATURE_TPM_HAS_COMBINE (0)
/* @brief Whether COMBINE register has effect. */
#define FSL_FEATURE_TPM_COMBINE_HAS_EFFECTn(x) (0)
/* @brief Has TPM_POL. */
#define FSL_FEATURE_TPM_HAS_POL (1)
/* @brief Whether POL register has effect. */
#define FSL_FEATURE_TPM_POL_HAS_EFFECTn(x) (1)
/* @brief Has TPM_FILTER register. */
#define FSL_FEATURE_TPM_HAS_FILTER (0)
/* @brief Whether FILTER register has effect. */
#define FSL_FEATURE_TPM_FILTER_HAS_EFFECTn(x) (0)
/* @brief Has TPM_QDCTRL register. */
#define FSL_FEATURE_TPM_HAS_QDCTRL (0)
/* @brief Whether QDCTRL register has effect. */
#define FSL_FEATURE_TPM_QDCTRL_HAS_EFFECTn(x) (0)
/* @brief Is affected by errata with ID 050050 (Incorrect duty output when EPWM mode is set to PS=0 during write 1 to CnV register). */
#define FSL_FEATURE_TPM_HAS_ERRATA_050050 (0)
/* @brief Whether 32 bits counter has effect. */
#define FSL_FEATURE_TPM_HAS_32BIT_COUNTERn(x) (0)

/* UART module features */

/* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
#define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (0)
/* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
#define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
/* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
#define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (0)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_UART_HAS_FIFO (0)
/* @brief Hardware flow control (RTS, CTS) is supported. */
#define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (0)
/* @brief Infrared (modulation) is supported. */
#define FSL_FEATURE_UART_HAS_IR_SUPPORT (0)
/* @brief 2 bits long stop bit is available. */
#define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (0)
/* @brief If 10-bit mode is supported. */
#define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (1)
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
#define FSL_FEATURE_UART_FIFO_SIZEn(x) (0)
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
#define FSL_FEATURE_UART_HAS_SEPARATE_DMA_RX_TX_REQn(x) (1)

/* USB module features */

/* @brief KHCI module instance count */
#define FSL_FEATURE_USB_KHCI_COUNT (1)
/* @brief HOST mode enabled */
#define FSL_FEATURE_USB_KHCI_HOST_ENABLED (0)
/* @brief OTG mode enabled */
#define FSL_FEATURE_USB_KHCI_OTG_ENABLED (0)
/* @brief Size of the USB dedicated RAM */
#define FSL_FEATURE_USB_KHCI_USB_RAM (0)
/* @brief Has KEEP_ALIVE_CTRL register */
#define FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED (0)
/* @brief Has the Dynamic SOF threshold compare support */
#define FSL_FEATURE_USB_KHCI_DYNAMIC_SOF_THRESHOLD_COMPARE_ENABLED (0)
/* @brief Has the VBUS detect support */
#define FSL_FEATURE_USB_KHCI_VBUS_DETECT_ENABLED (0)
/* @brief Has the IRC48M module clock support */
#define FSL_FEATURE_USB_KHCI_IRC48M_MODULE_CLOCK_ENABLED (1)
/* @brief Number of endpoints supported */
#define FSL_FEATURE_USB_ENDPT_COUNT (16)
/* @brief Has STALL_IL/OL_DIS registers */
#define FSL_FEATURE_USB_KHCI_HAS_STALL_LOW (0)
/* @brief Has STALL_IH/OH_DIS registers */
#define FSL_FEATURE_USB_KHCI_HAS_STALL_HIGH (0)

/* VREF module features */

/* @brief Has chop oscillator (bit TRM[CHOPEN]) */
#define FSL_FEATURE_VREF_HAS_CHOP_OSC (1)
/* @brief Has second order curvature compensation (bit SC[ICOMPEN]) */
#define FSL_FEATURE_VREF_HAS_COMPENSATION (1)
/* @brief If high/low buffer mode supported */
#define FSL_FEATURE_VREF_MODE_LV_TYPE (1)
/* @brief Module has also low reference (registers VREFL/VREFH) */
#define FSL_FEATURE_VREF_HAS_LOW_REFERENCE (0)
/* @brief Has VREF_TRM4. */
#define FSL_FEATURE_VREF_HAS_TRM4 (0)

#endif /* _MCXC444_FEATURES_H_ */

