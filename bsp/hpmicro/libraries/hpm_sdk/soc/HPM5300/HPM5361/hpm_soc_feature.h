/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SOC_FEATURE_H
#define HPM_SOC_FEATURE_H

#include "hpm_soc.h"
#include "hpm_soc_ip_feature.h"

/*
 * PLIC feature
 */
#define PLIC_SUPPORT_EDGE_TRIGGER (1)

/*
 * PMP/PMA Feature
 */
#define PMP_SUPPORT_PMA (0)

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
 * PLLCTL Section
 */
#define PLLCTL_SOC_PLL_MAX_COUNT (2U)
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
#define DMA_SOC_TRANSFER_WIDTH_MAX(x) (DMA_TRANSFER_WIDTH_WORD)
#define DMA_SOC_TRANSFER_PER_BURST_MAX(x) (DMA_NUM_TRANSFER_PER_BURST_128T)
#define DMA_SOC_CHANNEL_NUM (32U)
#define DMA_SOC_MAX_COUNT (1U)
#define DMA_SOC_CHN_TO_DMAMUX_CHN(x, n) (DMAMUX_MUXCFG_HDMA_MUX0 + n)
#define DMA_SOC_HAS_IDLE_FLAG (1U)

/*
 * DMAMUX Section
 */
#define DMAMUX_SOC_WRITEONLY    (1U)

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
#define SOC_HAS_S_MODE              (0U)

/*
 * DAC Section
 */
#define DAC_SOC_BUFF_ALIGNED_SIZE (32U)
#define DAC_SOC_MAX_DATA          (4095U)
#define DAC_SOC_MAX_BUFF_COUNT    (65536U)
#define DAC_SOC_MAX_OUTPUT_FREQ   (1000000UL)

/*
 * UART Section
 */
#define UART_SOC_FIFO_SIZE       (16U)
#define UART_SOC_OVERSAMPLE_MAX   (30U) /* only support 30 oversample rate for rx idle detection */

/*
 * SPI Section
 */
#define SPI_SOC_TRANSFER_COUNT_MAX  (0xFFFFFFFFU)
#define SPI_SOC_FIFO_DEPTH          (8U)

/*
 * OTP Section
 */
#define OTP_SOC_UUID_IDX   (88U)
#define OTP_SOC_UUID_LEN   (16U) /* in bytes */

/*
 * PWM Section
 */
#define PWM_SOC_HRPWM_SUPPORT  (0U)
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
#define MCAN_SOC_MAX_COUNT              (4U)
#define MCAN_SOC_MSG_BUF_IN_IP          (0U)
#define MCAN_SOC_MSG_BUF_IN_AHB_RAM     (1U)
#define CAN_SOC_MAX_COUNT               MCAN_SOC_MAX_COUNT

/*
 * EWDG Section
 */
#define EWDG_SOC_CLK_DIV_VAL_MAX        (5U)
#define EWDG_SOC_OVERTIME_REG_WIDTH     (16U)
#define EWDG_SOC_SUPPORT_TIMEOUT_INTERRUPT  (1)
#define EWDG_TIMEOUT_INTERRUPT_REQUIRE_EDGE_TRIGGER (1)

/*
 * Sync Timer
 */
#define SYNT_SOC_HAS_TIMESTAMP             (1U)

/*
 * GPIO
 */
#define GPIO_SOC_HAS_EDGE_BOTH_INTERRUPT   (1U)

/**
 * OPAMP
 */
#define OPAMP_SOC_HAS_MAX_PRESET_CHN_NUM    (7U)


#endif /* HPM_SOC_FEATURE_H */
