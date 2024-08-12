/*
 * Copyright (c) 2021 HPMicro
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
#define I2C_SOC_TRANSFER_COUNT_MAX (256U)

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
#define PWM_SOC_CMP_MAX_COUNT (16U)
#define PWM_SOC_OUTPUT_TO_PWM_MAX_COUNT (8U)

/*
 * DMA Section
 */
#define DMA_SOC_TRANSFER_WIDTH_MAX(x) (((x) == HPM_XDMA) ? DMA_TRANSFER_WIDTH_DOUBLE_WORD : DMA_TRANSFER_WIDTH_WORD)
#define DMA_SOC_TRANSFER_PER_BURST_MAX(x) (((x) == HPM_XDMA) ? DMA_NUM_TRANSFER_PER_BURST_1024T : DMA_NUM_TRANSFER_PER_BURST_128T)
#define DMA_SOC_CHANNEL_NUM (8U)
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
#define USB_SOC_DCD_MAX_ENDPOINT_COUNT             (8U)
#ifndef USB_SOC_DCD_QTD_COUNT_EACH_ENDPOINT
#define USB_SOC_DCD_QTD_COUNT_EACH_ENDPOINT        (8U)
#endif
#define USB_SOC_DCD_MAX_QTD_COUNT                  (USB_SOC_DCD_MAX_ENDPOINT_COUNT * 2U * USB_SOC_DCD_QTD_COUNT_EACH_ENDPOINT)
#define USB_SOS_DCD_MAX_QHD_COUNT                  (USB_SOC_DCD_MAX_ENDPOINT_COUNT * 2U)
#define USB_SOC_DCD_DATA_RAM_ADDRESS_ALIGNMENT     (2048U)

#define USB_SOC_HCD_FRAMELIST_MAX_ELEMENTS         (1024U)

/*
 * ADC Section
 */
#define ADC_SOC_IP_VERSION                         (1U)
#define ADC_SOC_SEQ_MAX_LEN                        (16U)
#define ADC_SOC_MAX_TRIG_CH_LEN                    (4U)
#define ADC_SOC_MAX_TRIG_CH_NUM                    (11U)
#define ADC_SOC_DMA_ADDR_ALIGNMENT                 (4U)
#define ADC_SOC_CONFIG_INTEN_CHAN_BIT_SIZE         (8U)
#define ADC_SOC_PREEMPT_ENABLE_CTRL_SUPPORT        (1U)
#define ADC_SOC_SEQ_MAX_DMA_BUFF_LEN_IN_4BYTES     (4096U)
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
 * CAN Section
 */
#define CAN_SOC_MAX_COUNT       (2U)
#define CAN_SOC_TX_RX_BUFFER_ACCESS_WORKAROUND (1)    /* Refer to E00028 in HPM6200 Errata */

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
 * SDXC Section
 */
#define SDXC_SOC_HAS_MISC_CTRL0 (1)
#define SDXC_SOC_HAS_MISC_CTRL1 (1)

/*
 * SPI Section
 */
#define SPI_SOC_TRANSFER_COUNT_MAX  (512U)
#define SPI_SOC_FIFO_DEPTH          (4U)

/**
 * PWM Section
 *
 */
#define PWM_SOC_HRPWM_SUPPORT  (1U)
#define PWM_SOC_SHADOW_TRIG_SUPPORT (1U)
#define PWM_SOC_TIMER_RESET_SUPPORT (1U)

#endif /* HPM_SOC_FEATURE_H */
