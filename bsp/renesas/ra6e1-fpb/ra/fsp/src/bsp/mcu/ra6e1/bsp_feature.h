/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_FEATURE_H
#define BSP_FEATURE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_feature_gen.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** The main oscillator drive value is based upon the oscillator frequency selected in the configuration */
#if (BSP_CFG_XTAL_HZ > (19999999))
 #define CGC_MAINCLOCK_DRIVE    (0x00U)
#elif (BSP_CFG_XTAL_HZ > (15999999)) && (BSP_CFG_XTAL_HZ < (20000000))
 #define CGC_MAINCLOCK_DRIVE    (0x01U)
#elif (BSP_CFG_XTAL_HZ > (7999999)) && (BSP_CFG_XTAL_HZ < (16000000))
 #define CGC_MAINCLOCK_DRIVE    (0x02U)
#else
 #define CGC_MAINCLOCK_DRIVE    (0x03U)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

#define BSP_FEATURE_ACMPHS_MIN_WAIT_TIME_US                  (0) // Feature not available on this MCU
#define BSP_FEATURE_ACMPHS_VREF                              (0) // Feature not available on this MCU

#define BSP_FEATURE_ACMPLP_HAS_COMPSEL_REGISTERS             (0) // Feature not available on this MCU
#define BSP_FEATURE_ACMPLP_MIN_WAIT_TIME_US                  (0) // Feature not available on this MCU

#define BSP_FEATURE_ADC_ADDITION_SUPPORTED                   (1U)
#define BSP_FEATURE_ADC_B_TSN_CALIBRATION32_MASK             (0U)
#define BSP_FEATURE_ADC_B_TSN_SLOPE                          (0U)
#define BSP_FEATURE_ADC_B_UNIT_0_CHANNELS                    (0U)
#define BSP_FEATURE_ADC_B_UNIT_1_CHANNELS                    (0U)
#define BSP_FEATURE_ADC_CALIBRATION_REG_AVAILABLE            (0U)
#define BSP_FEATURE_ADC_CLOCK_SOURCE                         (FSP_PRIV_CLOCK_PCLKC)
#define BSP_FEATURE_ADC_D_CHANNELS                           (0) // Feature not available on this MCU
#define BSP_FEATURE_ADC_D_SCAN_MODE_CHANNELS                 (0) // Feature not available on this MCU
#define BSP_FEATURE_ADC_GROUP_B_SENSORS_ALLOWED              (1U)
#define BSP_FEATURE_ADC_HAS_ADBUF                            (1U)
#define BSP_FEATURE_ADC_HAS_ADCER_ADPRC                      (1U)
#define BSP_FEATURE_ADC_HAS_ADCER_ADRFMT                     (1U)
#define BSP_FEATURE_ADC_HAS_ADHVREFCNT                       (0U)
#define BSP_FEATURE_ADC_HAS_PGA                              (0U)
#define BSP_FEATURE_ADC_HAS_SAMPLE_HOLD_REG                  (0U)
#define BSP_FEATURE_ADC_HAS_VREFAMPCNT                       (0U)
#define BSP_FEATURE_ADC_MAX_RESOLUTION_BITS                  (12U)
#define BSP_FEATURE_ADC_SENSORS_EXCLUSIVE                    (0U)
#define BSP_FEATURE_ADC_SENSOR_MIN_SAMPLING_TIME             (4150U)
#define BSP_FEATURE_ADC_TSN_CALIBRATION32_AVAILABLE          (0)      // Feature not available on this MCU
#define BSP_FEATURE_ADC_TSN_CALIBRATION32_MASK               (0)      // Feature not available on this MCU
#define BSP_FEATURE_ADC_TSN_CALIBRATION_AVAILABLE            (0)      // Feature not available on this MCU
#define BSP_FEATURE_ADC_TSN_CONTROL_AVAILABLE                (0)      // Feature not available on this MCU
#define BSP_FEATURE_ADC_TSN_SLOPE                            (0)      // Feature not available on this MCU
#define BSP_FEATURE_ADC_UNIT_0_CHANNELS                      (0x31FF) // 0 to 8, 12, 13
#define BSP_FEATURE_ADC_UNIT_1_CHANNELS                      (0)      // Feature not available on this MCU
#define BSP_FEATURE_ADC_VALID_UNIT_MASK                      (1U)

#define BSP_FEATURE_AGT_AGTW_CHANNEL_COUNT                   (0)
#define BSP_FEATURE_AGT_AGT_CHANNEL_COUNT                    (6)
#define BSP_FEATURE_AGT_USE_AGTIOSEL_ALT                     (0) // Indicates use of AGTIOSEL_ALT instead of AGTIOSEL
#define BSP_FEATURE_AGT_VALID_CHANNEL_MASK                   (0x3F)

#define BSP_FEATURE_BSP_CODE_CACHE_VERSION                   (1)
#define BSP_FEATURE_BSP_FLASH_CACHE                          (1)
#define BSP_FEATURE_BSP_FLASH_CACHE_DISABLE_OPM              (0U)
#define BSP_FEATURE_BSP_FLASH_PREFETCH_BUFFER                (0)
#define BSP_FEATURE_BSP_HAS_ADC_CLOCK                        (0)
#define BSP_FEATURE_BSP_HAS_CANFD_CLOCK                      (0)
#define BSP_FEATURE_BSP_HAS_CEC_CLOCK                        (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_CLOCK_SUPPLY_TYPEB               (0U)
#define BSP_FEATURE_BSP_HAS_DCDC_REGULATOR                   (0U)
#define BSP_FEATURE_BSP_HAS_DTCM                             (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_FSXP_CLOCK                       (0)
#define BSP_FEATURE_BSP_HAS_GRAPHICS_DOMAIN                  (0)
#define BSP_FEATURE_BSP_HAS_I3C_CLOCK                        (0)
#define BSP_FEATURE_BSP_HAS_IIC_CLOCK                        (0U)
#define BSP_FEATURE_BSP_HAS_ITCM                             (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_LCD_CLOCK                        (0)
#define BSP_FEATURE_BSP_HAS_OCTASPI_CLOCK                    (0)
#define BSP_FEATURE_BSP_HAS_OFS2                             (0)
#define BSP_FEATURE_BSP_HAS_OFS3                             (0)
#define BSP_FEATURE_BSP_HAS_SCE5                             (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_SCE_ON_RA2                       (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_SCISPI_CLOCK                     (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_SCI_CLOCK                        (0)
#define BSP_FEATURE_BSP_HAS_SDADC_CLOCK                      (0)
#define BSP_FEATURE_BSP_HAS_SECURITY_MPU                     (0U)
#define BSP_FEATURE_BSP_HAS_SPI_CLOCK                        (0)
#define BSP_FEATURE_BSP_HAS_SP_MON                           (0U)
#define BSP_FEATURE_BSP_HAS_SYRACCR                          (0U)
#define BSP_FEATURE_BSP_HAS_TZFSAR                           (1)
#define BSP_FEATURE_BSP_HAS_USB60_CLOCK                      (0U) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_USBCKDIVCR                       (1U)
#define BSP_FEATURE_BSP_HAS_USB_CLOCK_DIV                    (1U)
#define BSP_FEATURE_BSP_HAS_USB_CLOCK_REQ                    (1U)
#define BSP_FEATURE_BSP_HAS_USB_CLOCK_SEL                    (1U)
#define BSP_FEATURE_BSP_HAS_USB_CLOCK_SEL_ALT                (0U)
#define BSP_FEATURE_BSP_MCU_INFO_POINTER_LOCATION            (0U)
#define BSP_FEATURE_BSP_MPU_REGION0_MASK                     (0U) // Feature not available on this MCU
#define BSP_FEATURE_BSP_MSTP_GPT_MSTPD5                      (0)  // If MSTPCRE is present then the setting is not valid.
#define BSP_FEATURE_BSP_MSTP_GPT_MSTPD5_MAX_CH               (0U) // If MSTPCRE is present then the setting is not valid.
#define BSP_FEATURE_BSP_MSTP_HAS_MSTPCRE                     (1U)
#define BSP_FEATURE_BSP_MSTP_POEG_MSTPD13                    (0)  // If MSTPCRE is present then the setting is not valid.
#define BSP_FEATURE_BSP_NUM_PMSAR                            (8U)
#define BSP_FEATURE_BSP_OFS1_HOCOFRQ_MASK                    (0xFFFFF9FFU)
#define BSP_FEATURE_BSP_OFS1_HOCOFRQ_OFFSET                  (9U)
#define BSP_FEATURE_BSP_OFS_HAS_SECURITY_ATTRIBUTION         (1U)
#define BSP_FEATURE_BSP_OSIS_PADDING                         (0U)
#define BSP_FEATURE_BSP_POWER_CHANGE_MSTP_REQUIRED           (0U)
#define BSP_FEATURE_BSP_RESET_TRNG                           (0U)
#define BSP_FEATURE_BSP_SYS_CLOCK_FREQ_FIVE_ROM_WAITS        (0U)         // The maximum frequency allowed without having five ROM wait cycles (Set to zero if this is not an option).
#define BSP_FEATURE_BSP_SYS_CLOCK_FREQ_FOUR_ROM_WAITS        (0U)         // The maximum frequency allowed without having four ROM wait cycles (Set to zero if this is not an option).
#define BSP_FEATURE_BSP_SYS_CLOCK_FREQ_NO_RAM_WAITS          (100000000U) // The maximum frequency allowed without having RAM wait state enabled in SRAMWTSC.
#define BSP_FEATURE_BSP_SYS_CLOCK_FREQ_ONE_ROM_WAITS         (50000000U)  // The maximum frequency allowed without having one ROM wait cycle.
#define BSP_FEATURE_BSP_SYS_CLOCK_FREQ_THREE_ROM_WAITS       (150000000U) // The maximum frequency allowed without having three ROM wait cycles (Set to zero if this is not an option).
#define BSP_FEATURE_BSP_SYS_CLOCK_FREQ_TWO_ROM_WAITS         (100000000U) // The maximum frequency allowed without having two ROM wait cycles.
#define BSP_FEATURE_BSP_UNIQUE_ID_OFFSET                     (0U)
#define BSP_FEATURE_BSP_UNIQUE_ID_POINTER                    (0x01008190U)
#define BSP_FEATURE_BSP_VBATT_HAS_VBTCR1_BPWSWSTP            (0U)

#define BSP_FEATURE_CANFD_FD_SUPPORT                         (0U)
#define BSP_FEATURE_CANFD_LITE                               (0U)
#define BSP_FEATURE_CANFD_NUM_CHANNELS                       (0U) // Feature not available on this MCU
#define BSP_FEATURE_CANFD_NUM_INSTANCES                      (0U)

#define BSP_FEATURE_CAN_CHECK_PCLKB_RATIO                    (0U)
#define BSP_FEATURE_CAN_CLOCK                                (0U)
#define BSP_FEATURE_CAN_MCLOCK_ONLY                          (0U)
#define BSP_FEATURE_CAN_NUM_CHANNELS                         (1U)

#define BSP_FEATURE_CGC_EXECUTE_FROM_LOCO                    (1)
#define BSP_FEATURE_CGC_HAS_BCLK                             (0U)
#define BSP_FEATURE_CGC_HAS_CPUCLK                           (0U)
#define BSP_FEATURE_CGC_HAS_EXTRACLK2                        (0)
#define BSP_FEATURE_CGC_HAS_FCLK                             (1U)
#define BSP_FEATURE_CGC_HAS_FLDWAITR                         (0U)
#define BSP_FEATURE_CGC_HAS_FLL                              (1U)
#define BSP_FEATURE_CGC_HAS_FLWT                             (1U)
#define BSP_FEATURE_CGC_HAS_HOCOWTCR                         (0U)
#define BSP_FEATURE_CGC_HAS_MEMWAIT                          (0U)
#define BSP_FEATURE_CGC_HAS_OSTDCSE                          (0) // Feature not available on this MCU
#define BSP_FEATURE_CGC_HAS_PCLKA                            (1U)
#define BSP_FEATURE_CGC_HAS_PCLKB                            (1U)
#define BSP_FEATURE_CGC_HAS_PCLKC                            (1U)
#define BSP_FEATURE_CGC_HAS_PCLKD                            (1U)
#define BSP_FEATURE_CGC_HAS_PCLKE                            (0U)
#define BSP_FEATURE_CGC_HAS_PLL                              (1U)
#define BSP_FEATURE_CGC_HAS_PLL2                             (1U) // This MCU has a second PLL that can be used as a clock source for certain peripherals.
#define BSP_FEATURE_CGC_HAS_SOPCCR                           (1U)
#define BSP_FEATURE_CGC_HAS_SOSC                             (1U)
#define BSP_FEATURE_CGC_HAS_SRAMPRCR2                        (1U) // This MCU has another register to enable write access for SRAMWTSC.
#define BSP_FEATURE_CGC_HAS_SRAMWTSC                         (1U)
#define BSP_FEATURE_CGC_HOCOSF_BEFORE_OPCCR                  (0U)
#define BSP_FEATURE_CGC_HOCOWTCR_64MHZ_ONLY                  (0U)
#define BSP_FEATURE_CGC_HOCOWTCR_SCI_SNOOZE_VALUE            (0)
#define BSP_FEATURE_CGC_HOCOWTCR_VALUE                       (6U)
#define BSP_FEATURE_CGC_ICLK_DIV_RESET                       (BSP_CLOCKS_SYS_CLOCK_DIV_4)
#define BSP_FEATURE_CGC_LOCO_STABILIZATION_MAX_US            (61U)
#define BSP_FEATURE_CGC_LOW_SPEED_MAX_FREQ_HZ                (1000000U) // This MCU does have Low Speed Mode, up to 1MHz
#define BSP_FEATURE_CGC_LOW_VOLTAGE_MAX_FREQ_HZ              (0U)       // This MCU does not have Low Voltage Mode
#define BSP_FEATURE_CGC_MIDDLE_SPEED_MAX_FREQ_HZ             (0U)       // This MCU does not have Middle Speed Mode
#define BSP_FEATURE_CGC_MOCO_STABILIZATION_MAX_US            (15U)
#define BSP_FEATURE_CGC_MODRV_MASK                           (R_SYSTEM_MOMCR_MODRV0_Msk)
#define BSP_FEATURE_CGC_MODRV_SHIFT                          (R_SYSTEM_MOMCR_MODRV0_Pos)
#define BSP_FEATURE_CGC_OSCILLATON_STOP_DETECT               (1)
#define BSP_FEATURE_CGC_PLL1_NUM_OUTPUT_CLOCKS               (1U)
#define BSP_FEATURE_CGC_PLL2_NUM_OUTPUT_CLOCKS               (1U)
#define BSP_FEATURE_CGC_PLL2_OUT_MAX_HZ                      (240000000U)
#define BSP_FEATURE_CGC_PLL2_OUT_MIN_HZ                      (120000000U)
#define BSP_FEATURE_CGC_PLLCCR_TYPE                          (1U)
#define BSP_FEATURE_CGC_PLLCCR_VCO_MAX_HZ                    (200000000U)
#define BSP_FEATURE_CGC_PLLCCR_VCO_MIN_HZ                    (0)  // Feature not available on this MCU
#define BSP_FEATURE_CGC_PLLCCR_WAIT_US                       (0U) // No wait between setting PLLCCR and clearing PLLSTP
#define BSP_FEATURE_CGC_PLL_HOCO_MAX_CPUCLK_HZ               (0U)
#define BSP_FEATURE_CGC_PLL_OUT_MAX_HZ                       (200000000U)
#define BSP_FEATURE_CGC_PLL_OUT_MIN_HZ                       (120000000U)
#define BSP_FEATURE_CGC_PLL_REFERENCE_CLK_MAX_HZ             (0)  // Feature not available on this MCU
#define BSP_FEATURE_CGC_PLL_REFERENCE_CLK_MIN_HZ             (0)  // Feature not available on this MCU
#define BSP_FEATURE_CGC_PLL_SRC_MAX_HZ                       (24000000U)
#define BSP_FEATURE_CGC_PLL_SRC_MIN_HZ                       (8000000U)
#define BSP_FEATURE_CGC_REGISTER_SET_B                       (0)
#define BSP_FEATURE_CGC_SCKDIVCR2_HAS_EXTRA_CLOCKS           (0)
#define BSP_FEATURE_CGC_SCKDIVCR_BCLK_MATCHES_PCLKB          (1)
#define BSP_FEATURE_CGC_SODRV_MASK                           (0x02U)
#define BSP_FEATURE_CGC_SODRV_SHIFT                          (0x01U)
#define BSP_FEATURE_CGC_SRAMPRCR_KW_OFFSET                   (1)
#define BSP_FEATURE_CGC_SRAMPRCR_KW_VALUE                    (0x78)
#define BSP_FEATURE_CGC_STARTUP_OPCCR_MODE                   (0)
#define BSP_FEATURE_CGC_STARTUP_SCKDIVCR                     (0x22022222)
#define BSP_FEATURE_CGC_STARTUP_SCKDIVCR2                    (0x00)
#define BSP_FEATURE_CGC_STARTUP_SCKSCR                       (0x01)

#define BSP_FEATURE_CRC_HAS_CRCCR0_LMS                       (1)
#define BSP_FEATURE_CRC_HAS_SNOOP                            (0U)
#define BSP_FEATURE_CRC_POLYNOMIAL_MASK                      (0x3EU)
#define BSP_FEATURE_CRC_SNOOP_ADDRESS_TYPE_TDR               (0x0U)

#define BSP_FEATURE_CRYPTO_AES_IP_VERSION                    (0)
#define BSP_FEATURE_CRYPTO_HAS_AES                           (0)
#define BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED                   (0)
#define BSP_FEATURE_CRYPTO_HAS_CTR_DRBG                      (1)
#define BSP_FEATURE_CRYPTO_HAS_ECC                           (0)
#define BSP_FEATURE_CRYPTO_HAS_ECC_WRAPPED                   (0)
#define BSP_FEATURE_CRYPTO_HAS_HASH                          (0)
#define BSP_FEATURE_CRYPTO_HAS_RSA                           (0)
#define BSP_FEATURE_CRYPTO_HAS_RSA_WRAPPED                   (0)
#define BSP_FEATURE_CRYPTO_HAS_RSIP7                         (0) // Feature not available on this MCU
#define BSP_FEATURE_CRYPTO_HAS_RSIP_E11A                     (0) // Feature not available on this MCU
#define BSP_FEATURE_CRYPTO_HAS_SCE5                          (0)
#define BSP_FEATURE_CRYPTO_HAS_SCE5B                         (0)
#define BSP_FEATURE_CRYPTO_HAS_SCE7                          (0)
#define BSP_FEATURE_CRYPTO_HAS_SCE9                          (1)

#define BSP_FEATURE_CTSU_CTSUCHAC_REGISTER_COUNT             (0) // Feature not available on this MCU
#define BSP_FEATURE_CTSU_CTSUCHTRC_REGISTER_COUNT            (0) // Feature not available on this MCU
#define BSP_FEATURE_CTSU_HAS_TXVSEL                          (0) // Feature not available on this MCU
#define BSP_FEATURE_CTSU_VERSION                             (0) // Feature not available on this MCU

#define BSP_FEATURE_DAC8_HAS_CHARGEPUMP                      (0) // Feature not available on this MCU
#define BSP_FEATURE_DAC8_HAS_DA_AD_SYNCHRONIZE               (0) // Feature not available on this MCU
#define BSP_FEATURE_DAC8_HAS_REALTIME_MODE                   (0) // Feature not available on this MCU
#define BSP_FEATURE_DAC8_MAX_CHANNELS                        (0) // Feature not available on this MCU

#define BSP_FEATURE_DAC_AD_SYNC_UNIT_MASK                    (0x01U)
#define BSP_FEATURE_DAC_HAS_CHARGEPUMP                       (0U)
#define BSP_FEATURE_DAC_HAS_DAVREFCR                         (0U)
#define BSP_FEATURE_DAC_HAS_DA_AD_SYNCHRONIZE                (1U)
#define BSP_FEATURE_DAC_HAS_INTERNAL_OUTPUT                  (0U)
#define BSP_FEATURE_DAC_HAS_OUTPUT_AMPLIFIER                 (1U)
#define BSP_FEATURE_DAC_MAX_CHANNELS                         (1U)

#define BSP_FEATURE_DMAC_HAS_DELSR                           (0U)
#define BSP_FEATURE_DMAC_HAS_DMCTL                           (0U) // Feature not available on this MCU
#define BSP_FEATURE_DMAC_HAS_REPEAT_BLOCK_MODE               (1U)
#define BSP_FEATURE_DMAC_MAX_CHANNEL                         (8U)

#define BSP_FEATURE_DOC_VERSION                              (1U)

#define BSP_FEATURE_DTC_TRANSFER_INFO_ALIGNMENT              (4)

#define BSP_FEATURE_DWT_CYCCNT                               (1U) // This MCU has Data Watchpoint Cycle Count Register

#define BSP_FEATURE_ELC_VERSION                              (1U)

#define BSP_FEATURE_ETHER_FIFO_DEPTH                         (0x0000070FU)
#define BSP_FEATURE_ETHER_MAX_CHANNELS                       (1U)
#define BSP_FEATURE_ETHER_SUPPORTS_TZ_SECURE                 (0) // Feature not available on this MCU

#define BSP_FEATURE_FLASH_CODE_FLASH_START                   (0x0U)
#define BSP_FEATURE_FLASH_DATA_FLASH_START                   (0x08000000U)
#define BSP_FEATURE_FLASH_HP_CF_DUAL_BANK_START              (0x00200000U)
#define BSP_FEATURE_FLASH_HP_CF_REGION0_BLOCK_SIZE           (0x2000U)
#define BSP_FEATURE_FLASH_HP_CF_REGION0_SIZE                 (0x10000U)
#define BSP_FEATURE_FLASH_HP_CF_REGION1_BLOCK_SIZE           (0x8000U)
#define BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE                   (128U)
#define BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE                   (64U)
#define BSP_FEATURE_FLASH_HP_DF_WRITE_SIZE                   (4U)
#define BSP_FEATURE_FLASH_HP_HAS_FMEPROT                     (1)
#define BSP_FEATURE_FLASH_HP_SUPPORTS_DUAL_BANK              (1)
#define BSP_FEATURE_FLASH_HP_VERSION                         (40U)
#define BSP_FEATURE_FLASH_LP_AWS_FAW_MASK                    (0) // Feature not available on this MCU
#define BSP_FEATURE_FLASH_LP_AWS_FAW_SHIFT                   (0) // Feature not available on this MCU
#define BSP_FEATURE_FLASH_LP_CF_BLOCK_SIZE                   (0) // Feature not available on this MCU
#define BSP_FEATURE_FLASH_LP_CF_DUAL_BANK_START              (0) // Feature not available on this MCU
#define BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE                   (0) // Feature not available on this MCU
#define BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE                   (0) // Feature not available on this MCU
#define BSP_FEATURE_FLASH_LP_DF_WRITE_SIZE                   (0) // Feature not available on this MCU
#define BSP_FEATURE_FLASH_LP_FLASH_CLOCK_SRC                 (0) // Feature not available on this MCU
#define BSP_FEATURE_FLASH_LP_SUPPORTS_DUAL_BANK              (0) // Feature not available on this MCU
#define BSP_FEATURE_FLASH_LP_VERSION                         (0) // Feature not available on this MCU
#define BSP_FEATURE_FLASH_SUPPORTS_ACCESS_WINDOW             (0) // Feature not available on this MCU
#define BSP_FEATURE_FLASH_SUPPORTS_ID_CODE                   (0) // Feature not available on this MCU

#define BSP_FEATURE_GPT_32BIT_CHANNEL_MASK                   (0x06U)
#define BSP_FEATURE_GPT_CLOCK_DIVIDER_STEP_SIZE              (2U)
#define BSP_FEATURE_GPT_CLOCK_DIVIDER_VALUE_7_9_VALID        (0U)
#define BSP_FEATURE_GPT_ODC_FRANGE_FREQ_MIN                  (0U) // Feature not available on this MCU
#define BSP_FEATURE_GPT_ODC_FRANGE_SET_BIT(gpt_frequency)    (0U) // Feature not available on this MCU
#define BSP_FEATURE_GPT_ODC_FREQ_MAX                         (0U) // Feature not available on this MCU
#define BSP_FEATURE_GPT_ODC_FREQ_MIN                         (0U) // Feature not available on this MCU
#define BSP_FEATURE_GPT_TPCS_SHIFT                           (0U)

#define BSP_FEATURE_I3C_HAS_HDR_MODE                         (0U) // Feature not available on this MCU
#define BSP_FEATURE_I3C_MAX_DEV_COUNT                        (0U) // Feature not available on this MCU
#define BSP_FEATURE_I3C_MSTP_OFFSET                          (0U) // Feature not available on this MCU
#define BSP_FEATURE_I3C_NTDTBP0_DEPTH                        (0U) // Feature not available on this MCU
#define BSP_FEATURE_I3C_NUM_CHANNELS                         (0U) // Feature not available on this MCU

#define BSP_FEATURE_ICU_FIXED_IELSR_COUNT                    (0U)
#define BSP_FEATURE_ICU_HAS_FILTER                           (1U)
#define BSP_FEATURE_ICU_HAS_IELSR                            (1U)
#define BSP_FEATURE_ICU_HAS_INTERRUPT_GROUPS                 (0U)
#define BSP_FEATURE_ICU_HAS_WUPEN1                           (1U)
#define BSP_FEATURE_ICU_HAS_WUPEN2                           (0U)             // Feature not available on this MCU
#define BSP_FEATURE_ICU_IRQ_CHANNELS_MASK                    (0xFFFFU)
#define BSP_FEATURE_ICU_NMIER_MAX_INDEX                      (15U)            // Max used index in NMIER
#define BSP_FEATURE_ICU_SBYEDCR_MASK                         (0U)             // Feature not available on this MCU
#define BSP_FEATURE_ICU_WUPEN_MASK                           (0x7FB0DFFFFULL) // Note there is another WUPEN1 register

#define BSP_FEATURE_IIC_BUS_FREE_TIME_MULTIPLIER             (0U)
#define BSP_FEATURE_IIC_B_FAST_MODE_PLUS                     (0)              // Feature not available on this MCU
#define BSP_FEATURE_IIC_B_VALID_CHANNEL_MASK                 (0)              // Feature not available on this MCU
#define BSP_FEATURE_IIC_FAST_MODE_PLUS                       (1U)
#define BSP_FEATURE_IIC_VALID_CHANNEL_MASK                   (0x03)
#define BSP_FEATURE_IIC_VERSION                              (0)              // Feature not available on this MCU

#define BSP_FEATURE_IOPORT_ELC_PORTS                         (0x001EU)
#define BSP_FEATURE_IOPORT_VERSION                           (1U)

#define BSP_FEATURE_IWDT_CLOCK_FREQUENCY                     (15000UL)
#define BSP_FEATURE_IWDT_SUPPORTS_REGISTER_START_MODE        (0U) // Feature not available on this MCU

#define BSP_FEATURE_KINT_HAS_MSTP                            (0U)

#define BSP_FEATURE_LPM_CHANGE_MSTP_ARRAY                    (0U)
#define BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED                 (0U)
#define BSP_FEATURE_LPM_DPSIEGR_MASK                         (0x13DFF3U)
#define BSP_FEATURE_LPM_DPSIER_MASK                          (0x0D1FDFF3U)
#define BSP_FEATURE_LPM_HAS_DEEP_SLEEP                       (0U)
#define BSP_FEATURE_LPM_HAS_DEEP_STANDBY                     (1U)
#define BSP_FEATURE_LPM_HAS_DPSBYCR_DEEPCUT                  (1U)
#define BSP_FEATURE_LPM_HAS_DPSBYCR_DPSBY                    (1U)
#define BSP_FEATURE_LPM_HAS_DPSBYCR_SRKEEP                   (0U)
#define BSP_FEATURE_LPM_HAS_FLASH_MODE_SELECT                (0U) // Feature not available on this MCU
#define BSP_FEATURE_LPM_HAS_HOCO_STARTUP_SPEED_MODE          (0U) // Feature not available on this MCU
#define BSP_FEATURE_LPM_HAS_LDO_CONTROL                      (0U)
#define BSP_FEATURE_LPM_HAS_LPSCR                            (0U)
#define BSP_FEATURE_LPM_HAS_PDRAMSCR                         (0U)
#define BSP_FEATURE_LPM_HAS_SBYCR_OPE                        (0U)
#define BSP_FEATURE_LPM_HAS_SBYCR_SSBY                       (1U)
#define BSP_FEATURE_LPM_HAS_SNOOZE                           (1U)
#define BSP_FEATURE_LPM_HAS_SNZEDCR1                         (1U)
#define BSP_FEATURE_LPM_HAS_SNZREQCR1                        (1U)
#define BSP_FEATURE_LPM_HAS_STANDBY_SOSC_SELECT              (0U)                                  // Feature not available on this MCU
#define BSP_FEATURE_LPM_HAS_STCONR                           (0U)
#define BSP_FEATURE_LPM_RTC_REGISTER_CLOCK_DISABLE           (0U)                                  // Feature not available on this MCU
#define BSP_FEATURE_LPM_SBYCR_WRITE1_B14                     (0)
#define BSP_FEATURE_LPM_SNZEDCR_MASK                         (0x0000019FU)                         // note there is another SNZEDCR1 register
#define BSP_FEATURE_LPM_SNZREQCR_MASK                        (0x77300FFFFULL)                      // note tehre is another SNZEREQCR1 register
#define BSP_FEATURE_LPM_STANDBY_MOCO_REQUIRED                (0U)
#define BSP_FEATURE_LPM_STANDBY_MODE_CLEAR_DTCST             (0U)                                  // Feature not available on this MCU

#define BSP_FEATURE_LVD_EXLVD_STABILIZATION_TIME_US          (0)                                   // Feature not available on this MCU
#define BSP_FEATURE_LVD_HAS_DIGITAL_FILTER                   (1U)
#define BSP_FEATURE_LVD_HAS_EXT_MONITOR                      (0U)
#define BSP_FEATURE_LVD_HAS_LVDLVLR                          (0U)
#define BSP_FEATURE_LVD_MONITOR_1_HI_THRESHOLD               (LVD_THRESHOLD_MONITOR_1_LEVEL_2_99V) // 2.99V
#define BSP_FEATURE_LVD_MONITOR_1_LOW_THRESHOLD              (LVD_THRESHOLD_MONITOR_1_LEVEL_2_85V) // 2.85V
#define BSP_FEATURE_LVD_MONITOR_1_STABILIZATION_TIME_US      (10U)                                 // LVD1 operation stabilization time after LVD1 is enabled
#define BSP_FEATURE_LVD_MONITOR_2_HI_THRESHOLD               (LVD_THRESHOLD_MONITOR_2_LEVEL_2_99V) // 2.99V
#define BSP_FEATURE_LVD_MONITOR_2_LOW_THRESHOLD              (LVD_THRESHOLD_MONITOR_2_LEVEL_2_85V) // 2.85V
#define BSP_FEATURE_LVD_MONITOR_2_STABILIZATION_TIME_US      (10U)                                 // LVD2 operation stabilization time after LVD2 is enabled
#define BSP_FEATURE_LVD_SUPPORT_RESET_ON_RISING_EDGE         (0U)
#define BSP_FEATURE_LVD_VBAT_STABILIZATION_TIME_US           (0)                                   // Feature not available on this MCU
#define BSP_FEATURE_LVD_VERSION                              (1U)
#define BSP_FEATURE_LVD_VRTC_STABILIZATION_TIME_US           (0)                                   // Feature not available on this MCU

#define BSP_FEATURE_MACL_SUPPORTED                           (0U)

#define BSP_FEATURE_OPAMP_BASE_ADDRESS                       (0U)
#define BSP_FEATURE_OPAMP_HAS_MIDDLE_SPEED                   (0) // Feature not available on this MCU
#define BSP_FEATURE_OPAMP_HAS_SWITCHES                       (0U)
#define BSP_FEATURE_OPAMP_MIN_WAIT_TIME_HS_US                (0) // Feature not available on this MCU
#define BSP_FEATURE_OPAMP_MIN_WAIT_TIME_LP_US                (0) // Feature not available on this MCU
#define BSP_FEATURE_OPAMP_MIN_WAIT_TIME_MS_US                (0) // Feature not available on this MCU
#define BSP_FEATURE_OPAMP_TRIM_CAPABLE                       (0U)
#define BSP_FEATURE_OPAMP_VARIANT_CHANNEL_MASK               (0U)

#define BSP_FEATURE_OSPI_B_DEVICE_0_START_ADDRESS            (0) // Feature not available on this MCU
#define BSP_FEATURE_OSPI_B_DEVICE_1_START_ADDRESS            (0) // Feature not available on this MCU
#define BSP_FEATURE_OSPI_DEVICE_0_START_ADDRESS              (0x0U)
#define BSP_FEATURE_OSPI_DEVICE_1_START_ADDRESS              (0x0U)

#define BSP_FEATURE_POEG_CHANNEL_MASK                        (0xFU)

#define BSP_FEATURE_QSPI_DEVICE_START_ADDRESS                (0x60000000U)

#define BSP_FEATURE_RTC_HAS_ROPSEL                           (0U)
#define BSP_FEATURE_RTC_HAS_TCEN                             (1U)
#define BSP_FEATURE_RTC_IS_AVAILABLE                         (1U)
#define BSP_FEATURE_RTC_IS_IRTC                              (0U)
#define BSP_FEATURE_RTC_RTCCR_CHANNELS                       (3U)

#define BSP_FEATURE_SAU_UART_VALID_CHANNEL_MASK              (0U) // Feature not available on this MCU

#define BSP_FEATURE_SCI_ADDRESS_MATCH_CHANNELS               (0x219U)
#define BSP_FEATURE_SCI_CHANNELS                             (0x21FU)
#define BSP_FEATURE_SCI_CLOCK                                (FSP_PRIV_CLOCK_PCLKA)
#define BSP_FEATURE_SCI_LIN_CHANNELS                         (0U)      // Feature not available on this MCU
#define BSP_FEATURE_SCI_SPI_SCKSEL_VALUE                     (0U)      // Feature not available on this MCU
#define BSP_FEATURE_SCI_UART_ABCSE_RESTRICTED_CHANNELS       (0x0006U) // Channel 1 and channel 2 have ABCSE bit restriction
#define BSP_FEATURE_SCI_UART_CSTPEN_CHANNELS                 (0x0219U) // Channel 0, channel 3, Channel 4, channel 9 have CSTPEN feature
#define BSP_FEATURE_SCI_UART_DE_IS_INVERTED                  (0)       // Feature not available on this MCU
#define BSP_FEATURE_SCI_UART_FIFO_CHANNELS                   (0x219U)
#define BSP_FEATURE_SCI_UART_FIFO_DEPTH                      (16U)
#define BSP_FEATURE_SCI_VERSION                              (1U)

#define BSP_FEATURE_SDHI_CLOCK                               (FSP_PRIV_CLOCK_PCLKB)
#define BSP_FEATURE_SDHI_HAS_CARD_DETECTION                  (1U)
#define BSP_FEATURE_SDHI_MIN_CLOCK_DIVISION_SHIFT            (0U) // 1 (2^0) is minimum division supported
#define BSP_FEATURE_SDHI_SUPPORTS_8_BIT_MMC                  (0U)
#define BSP_FEATURE_SDHI_VALID_CHANNEL_MASK                  (1U)

#define BSP_FEATURE_SDRAM_START_ADDRESS                      (0x0U)

#define BSP_FEATURE_SLCDC_CONTRAST_MAX                       (0) // Feature not available on this MCU
#define BSP_FEATURE_SLCDC_CONTRAST_MAX_4BIAS                 (0) // Feature not available on this MCU
#define BSP_FEATURE_SLCDC_HAS_8_TIME_SLICE                   (0) // Feature not available on this MCU
#define BSP_FEATURE_SLCDC_HAS_INTERNAL_VOLT_GEN              (0) // Feature not available on this MCU
#define BSP_FEATURE_SLCDC_HAS_VL1SEL                         (0) // Feature not available on this MCU
#define BSP_FEATURE_SLCDC_MAX_NUM_SEG                        (0) // Feature not available on this MCU

#define BSP_FEATURE_SPI_CLK                                  (FSP_PRIV_CLOCK_PCLKA)
#define BSP_FEATURE_SPI_HAS_SPCR3                            (1U)
#define BSP_FEATURE_SPI_HAS_SSL_LEVEL_KEEP                   (1U)
#define BSP_FEATURE_SPI_MAX_CHANNEL                          (2U)
#define BSP_FEATURE_SPI_SSL_LEVEL_KEEP_VALID_CHANNEL_MASK    (0x3U)

#define BSP_FEATURE_SRAM_SRAMWTSC_WAIT_CYCLE_ENABLE          (0x01U)

#define BSP_FEATURE_SSI_FIFO_NUM_STAGES                      (32U)
#define BSP_FEATURE_SSI_VALID_CHANNEL_MASK                   (1U)

#define BSP_FEATURE_SYSC_HAS_VBTICTLR                        (1U)

#define BSP_FEATURE_TAU_VALID_CHANNEL_MASK                   (0)  // Feature not available on this MCU

#define BSP_FEATURE_TFU_SUPPORTED                            (0U) // Trigonometric Function Unit (TFU) not available on this MCU

#define BSP_FEATURE_TML_MAX_CLOCK_DIVIDER                    (0U) // Feature not available on this MCU
#define BSP_FEATURE_TML_NUM_CHANNELS                         (0)  // Feature not available on this MCU
#define BSP_FEATURE_TML_VALID_CHANNEL_MASK                   (0U) // Feature not available on this MCU

#define BSP_FEATURE_TRNG_HAS_MODULE_STOP                     (0U)

#define BSP_FEATURE_TZ_HAS_DLM                               (1U)
#define BSP_FEATURE_TZ_HAS_TRUSTZONE                         (1U)
#define BSP_FEATURE_TZ_NS_OFFSET                             (0U)
#define BSP_FEATURE_TZ_VERSION                               (1U)

#define BSP_FEATURE_UARTA_HAS_CLOCK_OUTPUT                   (0)  // Feature not available on this MCU
#define BSP_FEATURE_UARTA_MSTP_OFFSET                        (0)  // Feature not available on this MCU
#define BSP_FEATURE_UARTA_PCLK_RESTRICTION                   (0U) // Feature not available on this MCU

#define BSP_FEATURE_ULPT_MAX_CHANNEL_NUM                     (0)
#define BSP_FEATURE_ULPT_VALID_CHANNEL_MASK                  (0U)

#define BSP_FEATURE_USB_HAS_NOT_HOST                         (0) // Feature not available on this MCU
#define BSP_FEATURE_USB_HAS_PIPE04567                        (0U)
#define BSP_FEATURE_USB_HAS_TYPEC                            (0) // Feature not available on this MCU
#define BSP_FEATURE_USB_HAS_USBFS                            (1U)
#define BSP_FEATURE_USB_HAS_USBFS_BC                         (1U)
#define BSP_FEATURE_USB_HAS_USBHS                            (0U)
#define BSP_FEATURE_USB_HAS_USBHS_BC                         (0U)
#define BSP_FEATURE_USB_HAS_USBLS_PERI                       (0U)
#define BSP_FEATURE_USB_REG_PHYSECTRL_CNEN                   (1U) // For USB Full-speed module
#define BSP_FEATURE_USB_REG_PHYSLEW                          (0U)
#define BSP_FEATURE_USB_REG_PHYSLEW_VALUE                    (0U)
#define BSP_FEATURE_USB_REG_UCKSEL_UCKSELC                   (0U)
#define BSP_FEATURE_USB_REG_USBMC_VDCEN                      (0U)
#define BSP_FEATURE_USB_REG_USBMC_VDDUSBE                    (0U)

#endif
