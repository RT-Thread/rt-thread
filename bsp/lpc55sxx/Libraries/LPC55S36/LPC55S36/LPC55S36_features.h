/*
** ###################################################################
**     Version:             rev. 1.1, 2021-08-04
**     Build:               b220118
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2022 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2021-04-12)
**         Initial version based on RM DraftF
**     - rev. 1.1 (2021-08-04)
**         Initial version based on RM DraftG
**
** ###################################################################
*/

#ifndef _LPC55S36_FEATURES_H_
#define _LPC55S36_FEATURES_H_

/* SOC module features */

#if defined(CPU_LPC55S36JBD100)
    /* @brief AOI availability on the SoC. */
    #define FSL_FEATURE_SOC_AOI_COUNT (2)
    /* @brief CACHE64_CTRL availability on the SoC. */
    #define FSL_FEATURE_SOC_CACHE64_CTRL_COUNT (1)
    /* @brief CACHE64_POLSEL availability on the SoC. */
    #define FSL_FEATURE_SOC_CACHE64_POLSEL_COUNT (1)
    /* @brief LPC_CAN availability on the SoC. */
    #define FSL_FEATURE_SOC_LPC_CAN_COUNT (1)
    /* @brief CRC availability on the SoC. */
    #define FSL_FEATURE_SOC_CRC_COUNT (1)
    /* @brief CTIMER availability on the SoC. */
    #define FSL_FEATURE_SOC_CTIMER_COUNT (5)
    /* @brief CDOG availability on the SoC. */
    #define FSL_FEATURE_SOC_CDOG_COUNT (1)
    /* @brief DMA availability on the SoC. */
    #define FSL_FEATURE_SOC_DMA_COUNT (2)
    /* @brief DMIC availability on the SoC. */
    #define FSL_FEATURE_SOC_DMIC_COUNT (1)
    /* @brief ENC availability on the SoC. */
    #define FSL_FEATURE_SOC_ENC_COUNT (2)
    /* @brief FLASH availability on the SoC. */
    #define FSL_FEATURE_SOC_FLASH_COUNT (1)
    /* @brief FLEXCOMM availability on the SoC. */
    #define FSL_FEATURE_SOC_FLEXCOMM_COUNT (9)
    /* @brief FLEXSPI availability on the SoC. */
    #define FSL_FEATURE_SOC_FLEXSPI_COUNT (1)
    /* @brief FREQME availability on the SoC. */
    #define FSL_FEATURE_SOC_FREQME_COUNT (1)
    /* @brief GINT availability on the SoC. */
    #define FSL_FEATURE_SOC_GINT_COUNT (2)
    /* @brief GPIO availability on the SoC. */
    #define FSL_FEATURE_SOC_GPIO_COUNT (1)
    /* @brief SECGPIO availability on the SoC. */
    #define FSL_FEATURE_SOC_SECGPIO_COUNT (1)
    /* @brief I2C availability on the SoC. */
    #define FSL_FEATURE_SOC_I2C_COUNT (8)
    /* @brief I3C availability on the SoC. */
    #define FSL_FEATURE_SOC_I3C_COUNT (1)
    /* @brief I2S availability on the SoC. */
    #define FSL_FEATURE_SOC_I2S_COUNT (8)
    /* @brief INPUTMUX availability on the SoC. */
    #define FSL_FEATURE_SOC_INPUTMUX_COUNT (1)
    /* @brief IOCON availability on the SoC. */
    #define FSL_FEATURE_SOC_IOCON_COUNT (1)
    /* @brief LPADC availability on the SoC. */
    #define FSL_FEATURE_SOC_LPADC_COUNT (2)
    /* @brief LPCMP availability on the SoC. */
    #define FSL_FEATURE_SOC_LPCMP_COUNT (3)
    /* @brief LPDAC availability on the SoC. */
    #define FSL_FEATURE_SOC_LPDAC_COUNT (3)
    /* @brief MAILBOX availability on the SoC. */
    #define FSL_FEATURE_SOC_MAILBOX_COUNT (1)
    /* @brief MRT availability on the SoC. */
    #define FSL_FEATURE_SOC_MRT_COUNT (1)
    /* @brief OPAMP availability on the SoC. */
    #define FSL_FEATURE_SOC_OPAMP_COUNT (3)
    /* @brief OSTIMER availability on the SoC. */
    #define FSL_FEATURE_SOC_OSTIMER_COUNT (1)
    /* @brief PINT availability on the SoC. */
    #define FSL_FEATURE_SOC_PINT_COUNT (1)
    /* @brief SECPINT availability on the SoC. */
    #define FSL_FEATURE_SOC_SECPINT_COUNT (1)
    /* @brief PMC availability on the SoC. */
    #define FSL_FEATURE_SOC_PMC_COUNT (1)
    /* @brief POWERQUAD availability on the SoC. */
    #define FSL_FEATURE_SOC_POWERQUAD_COUNT (1)
    /* @brief PWM availability on the SoC. */
    #define FSL_FEATURE_SOC_PWM_COUNT (2)
    /* @brief PUF availability on the SoC. */
    #define FSL_FEATURE_SOC_PUF_COUNT (1)
    /* @brief RTC availability on the SoC. */
    #define FSL_FEATURE_SOC_RTC_COUNT (2)
    /* @brief SCT availability on the SoC. */
    #define FSL_FEATURE_SOC_SCT_COUNT (1)
    /* @brief SPI availability on the SoC. */
    #define FSL_FEATURE_SOC_SPI_COUNT (9)
    /* @brief SYSCON availability on the SoC. */
    #define FSL_FEATURE_SOC_SYSCON_COUNT (1)
    /* @brief USART availability on the SoC. */
    #define FSL_FEATURE_SOC_USART_COUNT (8)
    /* @brief USB availability on the SoC. */
    #define FSL_FEATURE_SOC_USB_COUNT (1)
    /* @brief USBFSH availability on the SoC. */
    #define FSL_FEATURE_SOC_USBFSH_COUNT (1)
    /* @brief UTICK availability on the SoC. */
    #define FSL_FEATURE_SOC_UTICK_COUNT (1)
    /* @brief VREF availability on the SoC. */
    #define FSL_FEATURE_SOC_VREF_COUNT (1)
    /* @brief WWDT availability on the SoC. */
    #define FSL_FEATURE_SOC_WWDT_COUNT (1)
#elif defined(CPU_LPC55S36JHI48)
    /* @brief AOI availability on the SoC. */
    #define FSL_FEATURE_SOC_AOI_COUNT (2)
    /* @brief CACHE64_CTRL availability on the SoC. */
    #define FSL_FEATURE_SOC_CACHE64_CTRL_COUNT (1)
    /* @brief CACHE64_POLSEL availability on the SoC. */
    #define FSL_FEATURE_SOC_CACHE64_POLSEL_COUNT (1)
    /* @brief LPC_CAN availability on the SoC. */
    #define FSL_FEATURE_SOC_LPC_CAN_COUNT (1)
    /* @brief CRC availability on the SoC. */
    #define FSL_FEATURE_SOC_CRC_COUNT (1)
    /* @brief CTIMER availability on the SoC. */
    #define FSL_FEATURE_SOC_CTIMER_COUNT (5)
    /* @brief CDOG availability on the SoC. */
    #define FSL_FEATURE_SOC_CDOG_COUNT (1)
    /* @brief DMA availability on the SoC. */
    #define FSL_FEATURE_SOC_DMA_COUNT (2)
    /* @brief DMIC availability on the SoC. */
    #define FSL_FEATURE_SOC_DMIC_COUNT (1)
    /* @brief ENC availability on the SoC. */
    #define FSL_FEATURE_SOC_ENC_COUNT (2)
    /* @brief FLASH availability on the SoC. */
    #define FSL_FEATURE_SOC_FLASH_COUNT (1)
    /* @brief FLEXCOMM availability on the SoC. */
    #define FSL_FEATURE_SOC_FLEXCOMM_COUNT (9)
    /* @brief FLEXSPI availability on the SoC. */
    #define FSL_FEATURE_SOC_FLEXSPI_COUNT (1)
    /* @brief FREQME availability on the SoC. */
    #define FSL_FEATURE_SOC_FREQME_COUNT (1)
    /* @brief GINT availability on the SoC. */
    #define FSL_FEATURE_SOC_GINT_COUNT (2)
    /* @brief GPIO availability on the SoC. */
    #define FSL_FEATURE_SOC_GPIO_COUNT (1)
    /* @brief SECGPIO availability on the SoC. */
    #define FSL_FEATURE_SOC_SECGPIO_COUNT (1)
    /* @brief I2C availability on the SoC. */
    #define FSL_FEATURE_SOC_I2C_COUNT (8)
    /* @brief I3C availability on the SoC. */
    #define FSL_FEATURE_SOC_I3C_COUNT (1)
    /* @brief I2S availability on the SoC. */
    #define FSL_FEATURE_SOC_I2S_COUNT (8)
    /* @brief INPUTMUX availability on the SoC. */
    #define FSL_FEATURE_SOC_INPUTMUX_COUNT (1)
    /* @brief IOCON availability on the SoC. */
    #define FSL_FEATURE_SOC_IOCON_COUNT (1)
    /* @brief LPADC availability on the SoC. */
    #define FSL_FEATURE_SOC_LPADC_COUNT (2)
    /* @brief LPCMP availability on the SoC. */
    #define FSL_FEATURE_SOC_LPCMP_COUNT (3)
    /* @brief LPDAC availability on the SoC. */
    #define FSL_FEATURE_SOC_LPDAC_COUNT (3)
    /* @brief MAILBOX availability on the SoC. */
    #define FSL_FEATURE_SOC_MAILBOX_COUNT (1)
    /* @brief MRT availability on the SoC. */
    #define FSL_FEATURE_SOC_MRT_COUNT (1)
    /* @brief OPAMP availability on the SoC. */
    #define FSL_FEATURE_SOC_OPAMP_COUNT (3)
    /* @brief OSTIMER availability on the SoC. */
    #define FSL_FEATURE_SOC_OSTIMER_COUNT (1)
    /* @brief PINT availability on the SoC. */
    #define FSL_FEATURE_SOC_PINT_COUNT (1)
    /* @brief SECPINT availability on the SoC. */
    #define FSL_FEATURE_SOC_SECPINT_COUNT (1)
    /* @brief PMC availability on the SoC. */
    #define FSL_FEATURE_SOC_PMC_COUNT (1)
    /* @brief POWERQUAD availability on the SoC. */
    #define FSL_FEATURE_SOC_POWERQUAD_COUNT (1)
    /* @brief PWM availability on the SoC. */
    #define FSL_FEATURE_SOC_PWM_COUNT (2)
    /* @brief PUF availability on the SoC. */
    #define FSL_FEATURE_SOC_PUF_COUNT (1)
    /* @brief RTC availability on the SoC. */
    #define FSL_FEATURE_SOC_RTC_COUNT (2)
    /* @brief SCT availability on the SoC. */
    #define FSL_FEATURE_SOC_SCT_COUNT (1)
    /* @brief SPI availability on the SoC. */
    #define FSL_FEATURE_SOC_SPI_COUNT (9)
    /* @brief SYSCON availability on the SoC. */
    #define FSL_FEATURE_SOC_SYSCON_COUNT (1)
    /* @brief USART availability on the SoC. */
    #define FSL_FEATURE_SOC_USART_COUNT (8)
    /* @brief UTICK availability on the SoC. */
    #define FSL_FEATURE_SOC_UTICK_COUNT (1)
    /* @brief VREF availability on the SoC. */
    #define FSL_FEATURE_SOC_VREF_COUNT (1)
    /* @brief WWDT availability on the SoC. */
    #define FSL_FEATURE_SOC_WWDT_COUNT (1)
#endif

/* LPADC module features */

/* @brief FIFO availability on the SoC. */
#define FSL_FEATURE_LPADC_FIFO_COUNT (2)
/* @brief Has subsequent trigger priority (bitfield CFG[TPRICTRL]). */
#define FSL_FEATURE_LPADC_HAS_CFG_SUBSEQUENT_PRIORITY (1)
/* @brief Has differential mode (bitfield CMDLn[DIFF]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_DIFF (0)
/* @brief Has channel scale (bitfield CMDLn[CSCALE]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_CSCALE (0)
/* @brief Has conversion type select (bitfield CMDLn[CTYPE]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_CTYPE (1)
/* @brief Has conversion resolution select  (bitfield CMDLn[MODE]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_MODE (1)
/* @brief Has compare function enable (bitfield CMDHn[CMPEN]). */
#define FSL_FEATURE_LPADC_HAS_CMDH_CMPEN (1)
/* @brief Has Wait for trigger assertion before execution (bitfield CMDHn[WAIT_TRIG]). */
#define FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG (1)
/* @brief Has offset calibration (bitfield CTRL[CALOFS]). */
#define FSL_FEATURE_LPADC_HAS_CTRL_CALOFS (1)
/* @brief Has gain calibration (bitfield CTRL[CAL_REQ]). */
#define FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ (1)
/* @brief Has calibration average (bitfield CTRL[CAL_AVGS]). */
#define FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS (1)
/* @brief Has internal clock (bitfield CFG[ADCKEN]). */
#define FSL_FEATURE_LPADC_HAS_CFG_ADCKEN (0)
/* @brief Enable support for low voltage reference on option 1 reference (bitfield CFG[VREF1RNG]). */
#define FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG (0)
/* @brief Has calibration (bitfield CFG[CALOFS]). */
#define FSL_FEATURE_LPADC_HAS_CFG_CALOFS (0)
/* @brief Has offset trim (register OFSTRIM). */
#define FSL_FEATURE_LPADC_HAS_OFSTRIM (1)
/* @brief Has trigger status (register TSTAT). */
#define FSL_FEATURE_LPADC_HAS_TSTAT (1)
/* @brief Has internal temperature sensor. */
#define FSL_FEATURE_LPADC_HAS_INTERNAL_TEMP_SENSOR (1)
/* @brief Temperature sensor parameter A (slope). */
#define FSL_FEATURE_LPADC_TEMP_PARAMETER_A (768.0f)
/* @brief Temperature sensor parameter B (offset). */
#define FSL_FEATURE_LPADC_TEMP_PARAMETER_B (292.7f)
/* @brief Temperature sensor parameter Alpha. */
#define FSL_FEATURE_LPADC_TEMP_PARAMETER_ALPHA (9.7f)
/* @brief Temperature sensor need calibration. */
#define FSL_FEATURE_LPADC_TEMP_NEED_CALIBRATION (1)
/* @brief the address of temperature sensor parameter A (slope) in Flash. */
#define FSL_FEATURE_FLASH_NMPA_TEMP_SLOPE_ADDRS (0x3FD28U)
/* @brief the address of temperature sensor parameter B (offset) in Flash. */
#define FSL_FEATURE_FLASH_NMPA_TEMP_OFFSET_ADDRS (0x3FD2CU)
/* @brief the buffer size of temperature sensor. */
#define FSL_FEATURE_LPADC_TEMP_SENS_BUFFER_SIZE (2U)

/* ANACTRL module features */

/* @brief Has PLL_USB_OUT_BIT_FIELD bitfile in XO32M_CTRL reigster. */
#define FSL_FEATURE_ANACTRL_HAS_NO_ENABLE_PLL_USB_OUT_BIT_FIELD (1)
/* @brief Has XO32M_ADC_CLK_MODE bitfile in DUMMY_CTRL reigster. */
#define FSL_FEATURE_ANACTRL_HAS_XO32M_ADC_CLK_MODE_BIF_FIELD (1)
/* @brief Has FREQ_ME_CTRL reigster. */
#define FSL_FEATURE_ANACTRL_HAS_NO_FREQ_ME_CTRL (1)
/* @brief Has auxiliary bias(register AUX_BIAS). */
#define FSL_FEATURE_ANACTRL_HAS_AUX_BIAS_REG (0)
/* @brief ANACTRL control VDDMAIN. */
#define FSL_FEATURE_ANACTRL_CONTROL_VDD_MAIN (1)

/* AOI module features */

/* @brief Maximum value of input mux. */
#define FSL_FEATURE_AOI_MODULE_INPUTS (4)
/* @brief Number of events related to number of registers AOIx_BFCRT01n/AOIx_BFCRT23n. */
#define FSL_FEATURE_AOI_EVENT_COUNT (4)

/* CACHE64_CTRL module features */

/* @brief Cache Line size in byte. */
#define FSL_FEATURE_CACHE64_CTRL_LINESIZE_BYTE (32)

/* CACHE64_POLSEL module features */

/* No feature definitions */

/* CAN module features */

/* @brief Support CANFD or not */
#define FSL_FEATURE_CAN_SUPPORT_CANFD (1)

/* CRC module features */

/* @brief Has data register with name CRC */
#define FSL_FEATURE_CRC_HAS_CRC_REG (0)

/* CTIMER module features */

/* No feature definitions */

/* LPDAC module features */

/* @brief FIFO size. */
#define FSL_FEATURE_LPDAC_FIFO_SIZE (16)
/* @brief Has OPAMP as buffer, speed control signal (bitfield GCR[BUF_SPD_CTRL]). */
#define FSL_FEATURE_LPDAC_HAS_GCR_BUF_SPD_CTRL (1)
/* @brief Buffer Enable(bitfield GCR[BUF_EN]). */
#define FSL_FEATURE_LPDAC_HAS_GCR_BUF_EN (1)
/* @brief RCLK cycles before data latch(bitfield GCR[LATCH_CYC]). */
#define FSL_FEATURE_LPDAC_HAS_GCR_LATCH_CYC (1)
/* @brief VREF source number. */
#define FSL_FEATURE_ANALOG_NUM_OF_VREF_SRC (3)
/* @brief Has internal reference current options. */
#define FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT (1)

/* DMA module features */

/* @brief Number of channels */
#define FSL_FEATURE_DMA_NUMBER_OF_CHANNELSn(x) \
    (((x) == DMA0) ? (52) : \
    (((x) == DMA1) ? (16) : (-1)))
/* @brief Max channels */
#define FSL_FEATURE_DMA_MAX_CHANNELS (52)
/* @brief All channels */
#define FSL_FEATURE_DMA_ALL_CHANNELS (68U)
/* @brief Align size of DMA0 descriptor */
#define FSL_FEATURE_DMA0_DESCRIPTOR_ALIGN_SIZE (1024)
/* @brief Align size of DMA1 descriptor */
#define FSL_FEATURE_DMA1_DESCRIPTOR_ALIGN_SIZE (256)
/* @brief Align size of DMA descriptor */
#define FSL_FEATURE_DMA_DESCRIPTOR_ALIGN_SIZEn(x) \
    (((x) == DMA0) ? (1024) : \
    (((x) == DMA1) ? (256) : (-1)))
/* @brief DMA head link descriptor table align size */
#define FSL_FEATURE_DMA_LINK_DESCRIPTOR_ALIGN_SIZE (16U)

/* DMIC module features */

/* @brief Number of channels */
#define FSL_FEATURE_DMIC_CHANNEL_NUM (2)
/* @brief DMIC channel FIFO register support sign extended */
#define FSL_FEATURE_DMIC_CHANNEL_HAS_SIGNEXTEND (1)
/* @brief DMIC has no IOCFG register */
#define FSL_FEATURE_DMIC_HAS_NO_IOCFG (1)
/* @brief DMIC has decimator reset function */
#define FSL_FEATURE_DMIC_HAS_DECIMATOR_RESET_FUNC (1)
/* @brief DMIC has global channel synchronization function */
#define FSL_FEATURE_DMIC_HAS_GLOBAL_SYNC_FUNC (1)

/* FLEXCOMM module features */

/* @brief FLEXCOMM0 USART INDEX 0 */
#define FSL_FEATURE_FLEXCOMM0_USART_INDEX  (0)
/* @brief FLEXCOMM0 SPI INDEX 0 */
#define FSL_FEATURE_FLEXCOMM0_SPI_INDEX  (0)
/* @brief FLEXCOMM0 I2C INDEX 0 */
#define FSL_FEATURE_FLEXCOMM0_I2C_INDEX  (0)
/* @brief FLEXCOMM0 I2S INDEX 0 */
#define FSL_FEATURE_FLEXCOMM0_I2S_INDEX  (0)
/* @brief FLEXCOMM1 USART INDEX 1 */
#define FSL_FEATURE_FLEXCOMM1_USART_INDEX  (1)
/* @brief FLEXCOMM1 SPI INDEX 1 */
#define FSL_FEATURE_FLEXCOMM1_SPI_INDEX  (1)
/* @brief FLEXCOMM1 I2C INDEX 1 */
#define FSL_FEATURE_FLEXCOMM1_I2C_INDEX  (1)
/* @brief FLEXCOMM1 I2S INDEX 1 */
#define FSL_FEATURE_FLEXCOMM1_I2S_INDEX  (1)
/* @brief FLEXCOMM2 USART INDEX 2 */
#define FSL_FEATURE_FLEXCOMM2_USART_INDEX  (2)
/* @brief FLEXCOMM2 SPI INDEX 2 */
#define FSL_FEATURE_FLEXCOMM2_SPI_INDEX  (2)
/* @brief FLEXCOMM2 I2C INDEX 2 */
#define FSL_FEATURE_FLEXCOMM2_I2C_INDEX  (2)
/* @brief FLEXCOMM2 I2S INDEX 2 */
#define FSL_FEATURE_FLEXCOMM2_I2S_INDEX  (2)
/* @brief FLEXCOMM3 USART INDEX 3 */
#define FSL_FEATURE_FLEXCOMM3_USART_INDEX  (3)
/* @brief FLEXCOMM3 SPI INDEX 3 */
#define FSL_FEATURE_FLEXCOMM3_SPI_INDEX  (3)
/* @brief FLEXCOMM3 I2C INDEX 3 */
#define FSL_FEATURE_FLEXCOMM3_I2C_INDEX  (3)
/* @brief FLEXCOMM3 I2S INDEX 3 */
#define FSL_FEATURE_FLEXCOMM3_I2S_INDEX  (3)
/* @brief FLEXCOMM4 USART INDEX 4 */
#define FSL_FEATURE_FLEXCOMM4_USART_INDEX  (4)
/* @brief FLEXCOMM4 SPI INDEX 4 */
#define FSL_FEATURE_FLEXCOMM4_SPI_INDEX  (4)
/* @brief FLEXCOMM4 I2C INDEX 4 */
#define FSL_FEATURE_FLEXCOMM4_I2C_INDEX  (4)
/* @brief FLEXCOMM4 I2S INDEX 4 */
#define FSL_FEATURE_FLEXCOMM4_I2S_INDEX  (4)
/* @brief FLEXCOMM5 USART INDEX 5 */
#define FSL_FEATURE_FLEXCOMM5_USART_INDEX  (5)
/* @brief FLEXCOMM5 SPI INDEX 5 */
#define FSL_FEATURE_FLEXCOMM5_SPI_INDEX  (5)
/* @brief FLEXCOMM5 I2C INDEX 5 */
#define FSL_FEATURE_FLEXCOMM5_I2C_INDEX  (5)
/* @brief FLEXCOMM5 I2S INDEX 5 */
#define FSL_FEATURE_FLEXCOMM5_I2S_INDEX  (5)
/* @brief FLEXCOMM6 USART INDEX 6 */
#define FSL_FEATURE_FLEXCOMM6_USART_INDEX  (6)
/* @brief FLEXCOMM6 SPI INDEX 6 */
#define FSL_FEATURE_FLEXCOMM6_SPI_INDEX  (6)
/* @brief FLEXCOMM6 I2C INDEX 6 */
#define FSL_FEATURE_FLEXCOMM6_I2C_INDEX  (6)
/* @brief FLEXCOMM6 I2S INDEX 6 */
#define FSL_FEATURE_FLEXCOMM6_I2S_INDEX  (6)
/* @brief FLEXCOMM7 USART INDEX 7 */
#define FSL_FEATURE_FLEXCOMM7_USART_INDEX  (7)
/* @brief FLEXCOMM7 SPI INDEX 7 */
#define FSL_FEATURE_FLEXCOMM7_SPI_INDEX  (7)
/* @brief FLEXCOMM7 I2C INDEX 7 */
#define FSL_FEATURE_FLEXCOMM7_I2C_INDEX  (7)
/* @brief FLEXCOMM7 I2S INDEX 7 */
#define FSL_FEATURE_FLEXCOMM7_I2S_INDEX  (7)
/* @brief FLEXCOMM8 SPI(HS_SPI) INDEX 8 */
#define FSL_FEATURE_FLEXCOMM8_SPI_INDEX  (8)
/* @brief I2S has DMIC interconnection */
#define FSL_FEATURE_FLEXCOMM_INSTANCE_I2S_HAS_DMIC_INTERCONNECTIONn(x) \
    (((x) == FLEXCOMM0) ? (0) : \
    (((x) == FLEXCOMM1) ? (0) : \
    (((x) == FLEXCOMM2) ? (0) : \
    (((x) == FLEXCOMM3) ? (0) : \
    (((x) == FLEXCOMM4) ? (0) : \
    (((x) == FLEXCOMM5) ? (0) : \
    (((x) == FLEXCOMM6) ? (0) : \
    (((x) == FLEXCOMM7) ? (1) : \
    (((x) == FLEXCOMM8) ? (0) : (-1))))))))))
/* @brief I2S support dual channel transfer */
#define FSL_FEATURE_FLEXCOMM_INSTANCE_I2S_SUPPORT_SECONDARY_CHANNELn(x) \
    (((x) == FLEXCOMM0) ? (0) : \
    (((x) == FLEXCOMM1) ? (0) : \
    (((x) == FLEXCOMM2) ? (0) : \
    (((x) == FLEXCOMM3) ? (0) : \
    (((x) == FLEXCOMM4) ? (0) : \
    (((x) == FLEXCOMM5) ? (0) : \
    (((x) == FLEXCOMM6) ? (1) : \
    (((x) == FLEXCOMM7) ? (1) : \
    (((x) == FLEXCOMM8) ? (0) : (-1))))))))))

/* FLEXSPI module features */

/* @brief FlexSPI AHB buffer count */
#define FSL_FEATURE_FLEXSPI_AHB_BUFFER_COUNTn(x) (8)
/* @brief FlexSPI has no MCR0 ARDFEN bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_ARDFEN (1)
/* @brief FlexSPI has no MCR0 ATDFEN bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_ATDFEN (1)
/* @brief FlexSPI has no MCR0 COMBINATIONEN bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_COMBINATIONEN (1)
/* @brief FlexSPI has no STS0 DATALEARNPHASEB bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_STS0_DATALEARNPHASEB (1)
/* @brief FlexSPI has no IPCR1 IPAREN bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_IPCR1_IPAREN (1)
/* @brief FlexSPI has no AHBCR APAREN bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_AHBCR_APAREN (1)
/* @brief FlexSPI has no MCR2 SCKBDIFFOPT bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_MCR2_SCKBDIFFOPT (1)
/* @brief FlexSPI has no FLSHCR4 WMENB bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_FLSHCR4_WMENB (1)
/* @brief FlexSPI has no STS2 BSLVLOCK bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_STS2_BSLVLOCK (1)
/* @brief FlexSPI has no STS2 BREFLOCK bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_STS2_BREFLOCK (1)
/* @brief FlexSPI supports Port A only, do not support Port B. */
#define FSL_FEATURE_FLEXSPI_NO_SUPPORT_PORTB (1)
/* @brief FlexSPI LUTKEY is read only. */
#define FSL_FEATURE_FLEXSPI_LUTKEY_IS_RO (1)

/* I2S module features */

/* @brief I2S support dual channel transfer. */
#define FSL_FEATURE_I2S_SUPPORT_SECONDARY_CHANNEL (1)
/* @brief I2S has DMIC interconnection. */
#define FSL_FEATURE_FLEXCOMM_I2S_HAS_DMIC_INTERCONNECTION  (1)

/* I3C module features */

/* @brief Has TERM bitfile in MERRWARN reigster. */
#define FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM (1)

/* INPUTMUX module features */

/* @brief Number of channels */
#define FSL_FEATURE_INPUTMUX_HAS_SIGNAL_ENA (1)
/* @brief Inputmux has channel mux control */
#define FSL_FEATURE_INPUTMUX_HAS_CHANNEL_MUX (0)

/* IOCON module features */

/* @brief Func bit field width */
#define FSL_FEATURE_IOCON_FUNC_FIELD_WIDTH (4)

/* MRT module features */

/* @brief number of channels. */
#define FSL_FEATURE_MRT_NUMBER_OF_CHANNELS  (4)

/* PINT module features */

/* @brief Number of connected outputs */
#define FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS (8)
/* @brief Number of connected outputs */
#define FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS (2)

/* PMC module features */

/* @brief UTICK does not support PD configure. */
#define FSL_FEATURE_UTICK_HAS_NO_PDCFG (1)
/* @brief WDT OSC does not support PD configure. */
#define FSL_FEATURE_WWDT_HAS_NO_PDCFG (1)

/* POWERQUAD module features */

/* @brief Sine and Cossine fix errata */
#define FSL_FEATURE_POWERQUAD_SIN_COS_FIX_ERRATA  (1)

/* PUF module features */

/* @brief the shift status value */
#define FSL_FEATURE_PUF_HAS_SHIFT_STATUS (1)

/* PWM module features */

/* @brief If (e)FlexPWM has module A channels (outputs). */
#define FSL_FEATURE_PWM_HAS_CHANNELA (1)
/* @brief If (e)FlexPWM has module B channels (outputs). */
#define FSL_FEATURE_PWM_HAS_CHANNELB (1)
/* @brief If (e)FlexPWM has module X channels (outputs). */
#define FSL_FEATURE_PWM_HAS_CHANNELX (1)
/* @brief If (e)FlexPWM has fractional feature. */
#define FSL_FEATURE_PWM_HAS_FRACTIONAL (1)
/* @brief If (e)FlexPWM has mux trigger source select bit field. */
#define FSL_FEATURE_PWM_HAS_MUX_TRIGGER_SOURCE_SEL (1)
/* @brief Number of submodules in each (e)FlexPWM module. */
#define FSL_FEATURE_PWM_SUBMODULE_COUNT (4U)
/* @brief Number of fault channel in each (e)FlexPWM module. */
#define FSL_FEATURE_PWM_FAULT_CH_COUNT (1)

/* RTC module features */

/* @brief Has Tamper Direction Register support. */
#define FSL_FEATURE_RTC_HAS_TAMPER_DIRECTION (0)
/* @brief Has Tamper Queue Status and Control Register support. */
#define FSL_FEATURE_RTC_HAS_TAMPER_QUEUE (1)
/* @brief Has RTC subsystem. */
#define FSL_FEATURE_RTC_HAS_SUBSYSTEM (1)
/* @brief Has Reset in system level. */
#define FSL_FEATURE_RTC_HAS_RESET (1)
/* @brief Has RTC Tamper 23 Filter Configuration Register support. */
#define FSL_FEATURE_RTC_HAS_FILTER23_CFG (1)
/* @brief Has WAKEUP_MODE bitfile in CTRL2 reigster. */
#define FSL_FEATURE_RTC_HAS_NO_CTRL2_WAKEUP_MODE (1)

/* SCT module features */

/* @brief Number of events */
#define FSL_FEATURE_SCT_NUMBER_OF_EVENTS (16)
/* @brief Number of states */
#define FSL_FEATURE_SCT_NUMBER_OF_STATES (32)
/* @brief Number of match capture */
#define FSL_FEATURE_SCT_NUMBER_OF_MATCH_CAPTURE (16)
/* @brief Number of outputs */
#define FSL_FEATURE_SCT_NUMBER_OF_OUTPUTS (10)

/* SECPINT module features */

/* @brief Number of connected outputs */
#define FSL_FEATURE_SECPINT_NUMBER_OF_CONNECTED_OUTPUTS (2)

/* SYSCON module features */

/* @brief Flash page size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES (512)
/* @brief Flash sector size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_SECTOR_SIZE_BYTES (32768)
/* @brief Flash size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_SIZE_BYTES (251904)

/* SYSCTL module features */

/* @brief SYSCTRL has Code Gray feature. */
#define FSL_FEATURE_SYSCTRL_HAS_CODE_GRAY (1)

/* USB module features */

#if defined(CPU_LPC55S36JBD100)
    /* @brief USB version */
    #define FSL_FEATURE_USB_VERSION (200)
    /* @brief Number of the endpoint in USB FS */
    #define FSL_FEATURE_USB_EP_NUM (5)
#endif /* defined(CPU_LPC55S36JBD100) */

/* USBFSH module features */

#if defined(CPU_LPC55S36JBD100)
    /* @brief USBFSH version */
    #define FSL_FEATURE_USBFSH_VERSION (200)
#endif /* defined(CPU_LPC55S36JBD100) */

/* VREF module features */

/* @brief Has chop oscillator (bit TRM[CHOPEN]) */
#define FSL_FEATURE_VREF_HAS_CHOP_OSC (0)
/* @brief Has second order curvature compensation (bit SC[ICOMPEN]) */
#define FSL_FEATURE_VREF_HAS_COMPENSATION (0)
/* @brief If high/low buffer mode supported */
#define FSL_FEATURE_VREF_MODE_LV_TYPE (0)
/* @brief Module has also low reference (registers VREFL/VREFH) */
#define FSL_FEATURE_VREF_HAS_LOW_REFERENCE (0)
/* @brief Has VREF_TRM4. */
#define FSL_FEATURE_VREF_HAS_TRM4 (0)

/* WWDT module features */

/* No feature definitions */

#endif /* _LPC55S36_FEATURES_H_ */

