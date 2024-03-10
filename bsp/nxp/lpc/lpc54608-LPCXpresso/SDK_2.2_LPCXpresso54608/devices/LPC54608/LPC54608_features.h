/*
** ###################################################################
**     Version:             rev. 1.1, 2016-11-25
**     Build:               b170112
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright (c) 2016 Freescale Semiconductor, Inc.
**     Copyright 2016 - 2017 NXP
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
**     o Neither the name of the copyright holder nor the names of its
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
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2016-08-12)
**         Initial version.
**     - rev. 1.1 (2016-11-25)
**         Update CANFD and Classic CAN register.
**         Add MAC TIMERSTAMP registers.
**
** ###################################################################
*/

#ifndef _LPC54608_FEATURES_H_
#define _LPC54608_FEATURES_H_

/* SOC module features */

/* @brief ADC availability on the SoC. */
#define FSL_FEATURE_SOC_ADC_COUNT (1)
/* @brief ASYNC_SYSCON availability on the SoC. */
#define FSL_FEATURE_SOC_ASYNC_SYSCON_COUNT (1)
/* @brief CRC availability on the SoC. */
#define FSL_FEATURE_SOC_CRC_COUNT (1)
/* @brief DMA availability on the SoC. */
#define FSL_FEATURE_SOC_DMA_COUNT (1)
/* @brief DMIC availability on the SoC. */
#define FSL_FEATURE_SOC_DMIC_COUNT (1)
/* @brief FLEXCOMM availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXCOMM_COUNT (10)
/* @brief GINT availability on the SoC. */
#define FSL_FEATURE_SOC_GINT_COUNT (2)
/* @brief GPIO availability on the SoC. */
#define FSL_FEATURE_SOC_GPIO_COUNT (1)
/* @brief I2C availability on the SoC. */
#define FSL_FEATURE_SOC_I2C_COUNT (10)
/* @brief I2S availability on the SoC. */
#define FSL_FEATURE_SOC_I2S_COUNT (2)
/* @brief INPUTMUX availability on the SoC. */
#define FSL_FEATURE_SOC_INPUTMUX_COUNT (1)
/* @brief IOCON availability on the SoC. */
#define FSL_FEATURE_SOC_IOCON_COUNT (1)
/* @brief MRT availability on the SoC. */
#define FSL_FEATURE_SOC_MRT_COUNT (1)
/* @brief PINT availability on the SoC. */
#define FSL_FEATURE_SOC_PINT_COUNT (1)
/* @brief RTC availability on the SoC. */
#define FSL_FEATURE_SOC_RTC_COUNT (1)
/* @brief SCT availability on the SoC. */
#define FSL_FEATURE_SOC_SCT_COUNT (1)
/* @brief SPI availability on the SoC. */
#define FSL_FEATURE_SOC_SPI_COUNT (10)
/* @brief SPIFI availability on the SoC. */
#define FSL_FEATURE_SOC_SPIFI_COUNT (1)
/* @brief SYSCON availability on the SoC. */
#define FSL_FEATURE_SOC_SYSCON_COUNT (1)
/* @brief CTIMER availability on the SoC. */
#define FSL_FEATURE_SOC_CTIMER_COUNT (5)
/* @brief USART availability on the SoC. */
#define FSL_FEATURE_SOC_USART_COUNT (10)
/* @brief USB availability on the SoC. */
#define FSL_FEATURE_SOC_USB_COUNT (1)
/* @brief UTICK availability on the SoC. */
#define FSL_FEATURE_SOC_UTICK_COUNT (1)
/* @brief WWDT availability on the SoC. */
#define FSL_FEATURE_SOC_WWDT_COUNT (1)
/* @brief USBFSH availability on the SoC. */
#define FSL_FEATURE_SOC_USBFSH_COUNT (1)
/* @brief USBHSD availability on the SoC. */
#define FSL_FEATURE_SOC_USBHSD_COUNT (1)
/* @brief USBHSH availability on the SoC. */
#define FSL_FEATURE_SOC_USBHSH_COUNT (1)
/* @brief EEPROM availability on the SoC. */
#define FSL_FEATURE_SOC_EEPROM_COUNT (1)
/* @brief EMC availability on the SoC. */
#define FSL_FEATURE_SOC_EMC_COUNT (1)
/* @brief ENET availability on the SoC. */
#define FSL_FEATURE_SOC_LPC_ENET_COUNT (1)
/* @brief SDIF availability on the SoC. */
#define FSL_FEATURE_SOC_SDIF_COUNT (1)
/* @brief SMARTCARD availability on the SoC. */
#define FSL_FEATURE_SOC_SMARTCARD_COUNT (2)
/* @brief LCD availability on the SoC. */
#define FSL_FEATURE_SOC_LCD_COUNT (1)
/* @brief CAN availability on the SoC. */
#define FSL_FEATURE_SOC_LPC_CAN_COUNT (2)
/* @brief SHA availability on the SoC. */
#define FSL_FEATURE_SOC_SHA_COUNT (0)
/* @brief AES availability on the SoC. */
#define FSL_FEATURE_SOC_AES_COUNT (0)
/* @brief RIT availability on the SoC. */
#define FSL_FEATURE_SOC_RIT_COUNT (1)
/* @brief FMC availability on the SoC. */
#define FSL_FEATURE_SOC_FMC_COUNT (1)
/* @brief RNG availability on the SoC. */
#define FSL_FEATURE_SOC_LPC_RNG_COUNT (1)

/* CAN module features */

/* @brief Support CANFD or not */
#define FSL_FEATURE_CAN_SUPPORT_CANFD (0)

/* DMA module features */

/* @brief Number of channels */
#define FSL_FEATURE_DMA_NUMBER_OF_CHANNELS (30)

/* EEPROM module features */

/* @brief Size of the EEPROM */
#define FSL_FEATURE_EEPROM_SIZE (0x00004000)
/* @brief Base address of the EEPROM */
#define FSL_FEATURE_EEPROM_BASE_ADDRESS (0x40108000)
/* @brief Page count of the EEPROM */
#define FSL_FEATURE_EEPROM_PAGE_COUNT (128)
/* @brief Command number for eeprom program */
#define FSL_FEATURE_EEPROM_PROGRAM_CMD (6)
/* @brief EEPROM internal clock freqency */
#define FSL_FEATURE_EEPROM_INTERNAL_FREQ (1500000)

/* IOCON module features */

/* @brief Func bit field width */
#define FSL_FEATURE_IOCON_FUNC_FIELD_WIDTH (4)

/* PINT module features */

/* @brief Number of connected outputs */
#define FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS (8)

/* SCT module features */

/* @brief Number of events */
#define FSL_FEATURE_SCT_NUMBER_OF_EVENTS (10)
/* @brief Number of states */
#define FSL_FEATURE_SCT_NUMBER_OF_STATES (10)
/* @brief Number of match capture */
#define FSL_FEATURE_SCT_NUMBER_OF_MATCH_CAPTURE (10)

/* SDIF module features */

/* @brief FIFO depth, every location is a WORD */
#define FSL_FEATURE_SDIF_FIFO_DEPTH_64_32BITS  (64)
/* @brief Max DMA buffer size */
#define FSL_FEATURE_SDIF_INTERNAL_DMA_MAX_BUFFER_SIZE  (4096)
/* @brief Max source clock in HZ */
#define FSL_FEATURE_SDIF_MAX_SOURCE_CLOCK  (52000000)

/* SPIFI module features */

/* @brief SPIFI start address */
#define FSL_FEATURE_SPIFI_START_ADDR (0x10000000)
/* @brief SPIFI end address */
#define FSL_FEATURE_SPIFI_END_ADDR (0x17FFFFFF)

/* SYSCON module features */

/* @brief Pointer to ROM IAP entry functions */
#define FSL_FEATURE_SYSCON_IAP_ENTRY_LOCATION (0x03000205)
/* @brief Flash page size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES (256)
/* @brief Flash sector size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_SECTOR_SIZE_BYTES (32768)
/* @brief Flash size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_SIZE_BYTES (524288)

/* USB module features */

/* @brief Size of the USB dedicated RAM */
#define FSL_FEATURE_USB_USB_RAM (0x00002000)
/* @brief Base address of the USB dedicated RAM */
#define FSL_FEATURE_USB_USB_RAM_BASE_ADDRESS (0x40100000)

/* USBFSH module features */

/* @brief Size of the USB dedicated RAM */
#define FSL_FEATURE_USBFSH_USB_RAM (0x00002000)
/* @brief Base address of the USB dedicated RAM */
#define FSL_FEATURE_USBFSH_USB_RAM_BASE_ADDRESS (0x40100000)

/* USBHSD module features */

/* @brief Size of the USB dedicated RAM */
#define FSL_FEATURE_USBHSD_USB_RAM (0x00002000)
/* @brief Base address of the USB dedicated RAM */
#define FSL_FEATURE_USBHSD_USB_RAM_BASE_ADDRESS (0x40100000)

/* USBHSH module features */

/* @brief Size of the USB dedicated RAM */
#define FSL_FEATURE_USBHSH_USB_RAM (0x00002000)
/* @brief Base address of the USB dedicated RAM */
#define FSL_FEATURE_USBHSH_USB_RAM_BASE_ADDRESS (0x40100000)

#endif /* _LPC54608_FEATURES_H_ */

