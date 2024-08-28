/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SOC_FEATURE_H
#define HPM_SOC_FEATURE_H

#include "hpm_soc.h"
#include "hpm_soc_ip_feature.h"

/*
 * UART section
 */
#define UART_SOC_FIFO_SIZE (16U)

/*
 * I2C Section
 */
#define I2C_SOC_FIFO_SIZE (4U)
#define I2C_SOC_TRANSFER_COUNT_MAX (4096U)

/*
 * PMIC Section
 */
#define PCFG_SOC_LDO1P1_MIN_VOLTAGE_IN_MV (700U)
#define PCFG_SOC_LDO1P1_MAX_VOLTAGE_IN_MV (1320U)
#define PCFG_SOC_LDO2P5_MIN_VOLTAGE_IN_MV (2125)
#define PCFG_SOC_LDO2P5_MAX_VOLTAGE_IN_MV (2900U)
#define PCFG_SOC_DCDC_MIN_VOLTAGE_IN_MV (600U)
#define PCFG_SOC_DCDC_MAX_VOLTAGE_IN_MV (1375U)

/*
 * I2S Section
 */
#define I2S_SOC_MAX_CHANNEL_NUM (16U)
#define I2S_SOC_MAX_TX_CHANNEL_NUM (8U)
#define I2S_SOC_MAX_TX_FIFO_DEPTH (8U)
#define PDM_I2S HPM_I2S0
#define DAO_I2S HPM_I2S1
#define PDM_SOC_SAMPLE_RATE_IN_HZ (16000U)
#define VAD_SOC_SAMPLE_RATE_IN_HZ (16000U)
#define DAO_SOC_SAMPLE_RATE_IN_HZ (48000U)
#define DAO_SOC_PDM_SAMPLE_RATE_RATIO (3U)
#define DAO_SOC_VAD_SAMPLE_RATE_RATIO (3U)

/*
 * PLLCTL Section
 */
#define PLLCTL_SOC_PLL_MAX_COUNT (3U)
/* PLL reference clock in hz */
#define PLLCTL_SOC_PLL_REFCLK_FREQ (24U * 1000000UL)
/* only PLL1 and PLL2 have DIV0, DIV1 */
#define PLLCTL_SOC_PLL_HAS_DIV0(x) ((((x) == 1) || ((x) == 2)) ? 1 : 0)
#define PLLCTL_SOC_PLL_HAS_DIV1(x) ((((x) == 1) || ((x) == 2)) ? 1 : 0)


/*
 * PWM Section
 */
#define PWM_SOC_PWM_MAX_COUNT (8U)
#define PWM_SOC_CMP_MAX_COUNT (24U)
#define PWM_SOC_OUTPUT_TO_PWM_MAX_COUNT (8U)

/*
 * DMA Section
 */
#define DMA_SOC_TRANSFER_WIDTH_MAX(x) (((x) == HPM_XDMA) ? DMA_TRANSFER_WIDTH_DOUBLE_WORD : DMA_TRANSFER_WIDTH_WORD)
#define DMA_SOC_TRANSFER_PER_BURST_MAX(x) (((x) == HPM_XDMA) ? DMA_NUM_TRANSFER_PER_BURST_1024T : DMA_NUM_TRANSFER_PER_BURST_128T)
#define DMA_SOC_CHANNEL_NUM (32U)
#define DMA_SOC_MAX_COUNT (2U)
#define DMA_SOC_CHN_TO_DMAMUX_CHN(x, n) (((x) == HPM_XDMA) ? (DMAMUX_MUXCFG_XDMA_MUX0 + n) : (DMAMUX_MUXCFG_HDMA_MUX0 + n))
#define DMA_SOC_HAS_IDLE_FLAG (1U)

/*
 * PDMA Section
 */
#define PDMA_SOC_PS_MAX_COUNT (0U)

/*
 * LCDC Section
 */
#define LCDC_SOC_MAX_LAYER_COUNT         (0U)
#define LCDC_SOC_MAX_CSC_LAYER_COUNT     (0U)
#define LCDC_SOC_LAYER_SUPPORTS_CSC(x) ((x) < 2)
#define LCDC_SOC_LAYER_SUPPORTS_YUV(x) ((x) < 2)

/*
* USB Section
*/
#define USB_SOC_MAX_COUNT                          (1U)

#define USB_SOC_DCD_QTD_NEXT_INVALID               (1U)
#define USB_SOC_DCD_QHD_BUFFER_COUNT               (5U)
#define USB_SOC_DCD_MAX_ENDPOINT_COUNT             (16U)
#ifndef USB_SOC_DCD_QTD_COUNT_EACH_ENDPOINT
#define USB_SOC_DCD_QTD_COUNT_EACH_ENDPOINT        (8U)
#endif
#define USB_SOC_DCD_MAX_QTD_COUNT                  (USB_SOC_DCD_MAX_ENDPOINT_COUNT * 2U * USB_SOC_DCD_QTD_COUNT_EACH_ENDPOINT)
#define USB_SOS_DCD_MAX_QHD_COUNT                  (USB_SOC_DCD_MAX_ENDPOINT_COUNT * 2U)
#define USB_SOC_DCD_DATA_RAM_ADDRESS_ALIGNMENT     (2048U)

#define USB_SOC_HCD_FRAMELIST_MAX_ELEMENTS         (1024U)

/*
* ENET Section
*/
#define ENET_SOC_RGMII_EN                          (0U)
#define ENET_SOC_DESC_ADDR_ALIGNMENT               (32U)
#define ENET_SOC_BUFF_ADDR_ALIGNMENT               (4U)
#define ENET_SOC_ADDR_MAX_COUNT                    (5U)
#define ENET_SOC_ALT_EHD_DES_MIN_LEN               (4U)
#define ENET_SOC_ALT_EHD_DES_MAX_LEN               (8U)
#define ENET_SOC_ALT_EHD_DES_LEN                   (8U)
#define ENET_SOC_PPS_MAX_COUNT                     (2L)
#define ENET_SOC_PPS1_EN                           (0U)

/*
* ADC Section
*/
#define ADC_SOC_IP_VERSION                         (3U)
#define ADC_SOC_SEQ_MAX_LEN                        (16U)
#define ADC_SOC_SEQ_HCFG_EN                        (1U)
#define ADC_SOC_MAX_TRIG_CH_LEN                    (4U)
#define ADC_SOC_MAX_TRIG_CH_NUM                    (11U)
#define ADC_SOC_DMA_ADDR_ALIGNMENT                 (4U)
#define ADC_SOC_CONFIG_INTEN_CHAN_BIT_SIZE         (8U)
#define ADC_SOC_BUSMODE_ENABLE_CTRL_SUPPORT        (1U)
#define ADC_SOC_PREEMPT_ENABLE_CTRL_SUPPORT        (1U)
#define ADC_SOC_SEQ_MAX_DMA_BUFF_LEN_IN_4BYTES     (16777216U)
#define ADC_SOC_PMT_MAX_DMA_BUFF_LEN_IN_4BYTES     (48U)

#define ADC16_SOC_PARAMS_LEN                       (34U)
#define ADC16_SOC_MAX_CH_NUM                       (15U)
#define ADC16_SOC_MAX_SAMPLE_VALUE                 (65535U)
#define ADC16_SOC_MAX_CONV_CLK_NUM                 (21U)

/*
 * SYSCTL Section
 */
#define SYSCTL_SOC_CPU_GPR_COUNT (14U)
#define SYSCTL_SOC_MONITOR_SLICE_COUNT (4U)

/*
 * PTPC Section
 */
#define PTPC_SOC_TIMER_MAX_COUNT       (2U)

/*
 * SDP Section
 */
#define SDP_REGISTER_DESCRIPTOR_COUNT (1U)
#define SDP_HAS_SM3_SUPPORT (1U)
#define SDP_HAS_SM4_SUPPORT (1U)

/*
 * SOC Privilege mode
 */
#define SOC_HAS_S_MODE              (1U)

/*
 * DAC Section
 */
#define DAC_SOC_BUFF_ALIGNED_SIZE (32U)
#define DAC_SOC_MAX_DATA          (4095U)
#define DAC_SOC_MAX_BUFF_COUNT    (65536U)
#define DAC_SOC_MAX_OUTPUT_FREQ   (1000000UL)

/*
 * SPI Section
 */
#define SPI_SOC_TRANSFER_COUNT_MAX  (512U)
#define SPI_SOC_FIFO_DEPTH          (4U)

/*
 * ROM API section
 */
#define ROMAPI_HAS_SW_SM3 (1)
#define ROMAPI_HAS_SW_SM4 (1)

/*
 * OTP Section
 */
#define OTP_SOC_MAC0_IDX   (65U)
#define OTP_SOC_MAC0_LEN   (6U)  /* in bytes */

#define OTP_SOC_UUID_IDX   (88U)
#define OTP_SOC_UUID_LEN   (16U) /* in bytes */

/**
 * PWM Section
 *
 */
#define PWM_SOC_HRPWM_SUPPORT  (1U)
#define PWM_SOC_SHADOW_TRIG_SUPPORT (0U)
#define PWM_SOC_TIMER_RESET_SUPPORT (1U)

/*
 * TRGM section
 */
#define TRGM_SOC_HAS_FILTER_SHIFT   (1U)
#define TRGM_SOC_HAS_DMAMUX_EN      (1U)
#define TRGM_SOC_HAS_ADC_MATRIX_SEL (1U)
#define TRGM_SOC_HAS_DAC_MATRIX_SEL (1U)
#define TRGM_SOC_HAS_POS_MATRIX_SEL (1U)

/*
 * MCAN Section
 */
#define MCAN_SOC_MAX_COUNT              (8U)
#define MCAN_SOC_MSG_BUF_IN_IP          (0U)
#define MCAN_SOC_MSG_BUF_IN_AHB_RAM     (1U)
#define CAN_SOC_MAX_COUNT               MCAN_SOC_MAX_COUNT

/*
 * EWDG Section
 */
#define EWDG_SOC_CLK_DIV_VAL_MAX        (32U)
#define EWDG_SOC_OVERTIME_REG_WIDTH     (32U)
#define EWDG_SOC_SUPPORT_TIMEOUT_INTERRUPT  (1)
#define EWDG_TIMEOUT_INTERRUPT_REQUIRE_EDGE_TRIGGER (0)

/*
 * Sync Timer Section
 */
#define SYNT_SOC_HAS_TIMESTAMP             (1U)

#endif /* HPM_SOC_FEATURE_H */
