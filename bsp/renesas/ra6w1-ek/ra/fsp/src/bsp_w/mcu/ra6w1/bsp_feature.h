/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_FEATURE_H
#define BSP_FEATURE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* TODO remove the following code when we finally drop AA chip revision: */
#ifndef DEVICE_REV_A
 #define DEVICE_REV_A                                    ((((1 << 0) << 8) & 0x00000F00))
#endif
#ifndef DEVICE_REV_B
 #define DEVICE_REV_B                                    ((((1 << 1) << 8) & 0x00000F00))
#endif
#ifndef BSP_DEVICE_REVISION
 #define BSP_DEVICE_REVISION                             DEVICE_REV_B
#endif

#define BSP_FEATURE_BSP_HAS_ICU                          (0U)

/*
 * \brief TCS - Trimmed Configuration Script
 *
 * Enabling this feature the system will always use the trimmed configuration values
 * stored by the TCS in OTP
 */
#define BSP_FEATURE_BSP_USE_TCS                          (1U)

// TIN-TODO Is this a BSP_FEATURE ?
#define BSP_FEATURE_BLOCK_MEDIA_SPI_W_BLOCK_SIZE         (4096U)

#define BSP_FEATURE_ADC_W_MAX_NUM_CHANNELS               (4U)

#define BSP_FEATURE_CGC_HAS_HCLK_DIV                     (1U)
#define BSP_FEATURE_CGC_HAS_PCLK_DIV                     (0U)
#define BSP_FEATURE_CGC_HAS_QCLK_DIV                     (0U)
#define BSP_FEATURE_CGC_HAS_LP_CLOCK                     (0U)
#define BSP_FEATURE_CGC_HAS_RCHS                         (0U)
#define BSP_FEATURE_CGC_HAS_RCLP                         (0U)
#define BSP_FEATURE_CGC_HAS_RCX                          (1U)
#define BSP_FEATURE_CGC_HAS_RCX_CONTROL                  (0U)
#define BSP_FEATURE_CGC_HAS_XTALM_SWITCH                 (0U)

// Crypto Features
#define BSP_FEATURE_CRYPTO_HAS_AES                       (1)
#define BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED               (0)
#define BSP_FEATURE_CRYPTO_HAS_ECC                       (1)
#define BSP_FEATURE_CRYPTO_HAS_ECC_WRAPPED               (0)
#define BSP_FEATURE_CRYPTO_HAS_HASH                      (1)
#define BSP_FEATURE_CRYPTO_HAS_RSA                       (1)
#define BSP_FEATURE_CRYPTO_HAS_RSA_WRAPPED               (0)
#define BSP_FEATURE_CRYPTO_HAS_CC312                     (1)
#define BSP_FEATURE_CRYPTO_HAS_CTR_DRBG                  (1)

#define BSP_FEATURE_DMAC_W                               (1)
#define BSP_FEATURE_DMAC_HAS_SHARED_IRQ                  (1U)
#define BSP_FEATURE_DMAC_MAX_CHANNEL                     (16U)

#define BSP_FEATURE_ELC_MISSING                          (1U)

#define BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE               (0)
#define BSP_FEATURE_FLASH_HP_VERSION                     (0)
#define BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE               (0)
#define BSP_FEATURE_FLASH_LP_VERSION                     (0)
#define BSP_FEATURE_FLASH_IS_INTERNAL                    (0)

#define BSP_FEATURE_I2C_VERSION                          (1)
#define BSP_FEATURE_I2C_VALID_CHANNEL_MASK               (0x06U)
#define BSP_FEATURE_I2C_HAS_DEDICATED_IRQS               (0)
#define BSP_FEATURE_I2C_HAS_SEPARATE_PD                  (0)
#define BSP_FEATURE_I2C_IRQ_TRIGGER_EDGE                 (1)

// I2S Features
#define BSP_FEATURE_I2S_FIFO_NUM_STAGES                  (4U)
#define BSP_FEATURE_I2S_VALID_CHANNEL_MASK               (1U)

#define BSP_FEATURE_ICU_IRQ_CHANNELS_MASK                (0x3FFFFFFFU)

#define BSP_FEATURE_IO_HAS_LATCHING                      (0U)
#define BSP_FEATURE_IO_PORT_COUNT                        (2U)
#define BSP_FEATURE_IO_PORT0_GPIO_COUNT                  (14U)
#define BSP_FEATURE_IO_PORT1_GPIO_COUNT                  (18U)
#define BSP_FEATURE_IO_PORT2_GPIO_COUNT                  (0U)

/* LPM_B */
#define BSP_FEATURE_LPM_CHANGE_MSTP_ARRAY                (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED             (0U)
#define BSP_FEATURE_LPM_DPSIEGR_MASK                     (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_DPSIER_MASK                      (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_HAS_DEEP_SLEEP                   (0U)
#define BSP_FEATURE_LPM_HAS_DEEP_STANDBY                 (0U)
#define BSP_FEATURE_LPM_HAS_DPSBYCR_DEEPCUT              (0U)
#define BSP_FEATURE_LPM_HAS_DPSBYCR_DPSBY                (0U)
#define BSP_FEATURE_LPM_HAS_DPSBYCR_SRKEEP               (0U)
#define BSP_FEATURE_LPM_HAS_LDO_CONTROL                  (0U)
#define BSP_FEATURE_LPM_HAS_LPSCR                        (0U)
#define BSP_FEATURE_LPM_HAS_PDRAMSCR                     (0U)
#define BSP_FEATURE_LPM_HAS_SBYCR_OPE                    (0U)
#define BSP_FEATURE_LPM_HAS_SBYCR_SSBY                   (0U)
#define BSP_FEATURE_LPM_HAS_SNOOZE                       (0U)
#define BSP_FEATURE_LPM_HAS_SNZEDCR1                     (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_HAS_SNZREQCR1                    (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_HAS_STCONR                       (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_SBYCR_WRITE1_B14                 (0)
#define BSP_FEATURE_LPM_SNZEDCR_MASK                     (0x0000009FU)
#define BSP_FEATURE_LPM_SNZREQCR_MASK                    (0x738200FFU)
#define BSP_FEATURE_LPM_STANDBY_MOCO_REQUIRED            (0U)

/* OSPI_W
 * RA6W1 has only one channel for OSPI_W
 */
#define BSP_FEATURE_OSPI_W_DEVICE_0_START_ADDRESS        (0x2A000000U)
#define BSP_FEATURE_OSPI_W_DEVICE_1_START_ADDRESS        (0x0U) /* not supported */
#define BSP_FEATURE_FLASH_DATA_FLASH_START               (BSP_FEATURE_OSPI_W_DEVICE_0_START_ADDRESS | 0x00300000U)

/* QSPI_W */
#define BSP_FEATURE_QSPI_DEVICE_START_ADDRESS            (0x24000000U)
#define BSP_FEATURE_QSPI_DEVICE_START_ADDRESS_DATA       (0x24000000U)
#define BSP_FEATURE_QSPI_MAX_CHANNEL                     (1U)
#define BSP_FEATURE_QSPI_HAS_DDR_SUPPORT                 (0U)

#define BSP_FEATURE_SPI_VALID_CHANNEL_MASK               (0x06U)
#define BSP_FEATURE_SPI_MAX_CHANNEL                      (2U)

#define BSP_FEATURE_TCS_APPLY                            (0U)
#define BSP_FEATURE_TCS_SYS_RAM                          (1U)

#define BSP_FEATURE_TIM_W_VALID_CHANNEL_MASK             (0x1FEU)
#define BSP_FEATURE_TIM_W_NUM_OF_CCM_CHANNELS            (0x4U)
#define BSP_FEATURE_TIM_W_HAS_IRQ_PER_CAPTURE_CHANNEL    (0x0U)
#define BSP_FEATURE_TIM_W_LINEAR_SRC_DIV_STEP            (0x1U)
#define BSP_FEATURE_TIM_W_SUPPORTS_COMPARE_MATCH         (0x0U)
#define BSP_FEATURE_TIM_W_SUPPORTS_PAUSE_NATIVELY        (0x0U)
#define BSP_FEATURE_TIM_W_SUPPORTS_SEQ_CAPTURES          (0x0U)
#define BSP_FEATURE_TIM_W_SUPPORTS_OVERFLOW_UNDERFLOW    (0x0U)
#define BSP_FEATURE_TIM_W_SUPPORTS_RESET_NATIVELY        (0x0U)

#define BSP_FEATURE_TRANSFER_HAS_DTC                     (0)

#define BSP_FEATURE_UART_W_VALID_CHANNEL_MASK            (0x0EU)
#define BSP_FEATURE_UART_W_FIFO_DEPTH                    (32U)

#define BSP_FEATURE_WDT_CLOCK_FREQUENCY                  (100U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

#endif
