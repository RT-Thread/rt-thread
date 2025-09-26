/*
 * Copyright (c) 2024-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_BOARD_H
#define _HPM_BOARD_H
#include <stdio.h>
#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_soc_feature.h"
#include "hpm_clock_drv.h"
#include "hpm_lobs_drv.h"
#include "pinmux.h"
#if !defined(CONFIG_NDEBUG_CONSOLE) || !CONFIG_NDEBUG_CONSOLE
#include "hpm_debug_console.h"
#endif

#define BOARD_NAME          "hpm6p00evk"
#define BOARD_UF2_SIGNATURE (0x0A4D5048UL)
#define BOARD_CPU_FREQ      (600000000UL)

#define SEC_CORE_IMG_START CORE1_ILM_LOCAL_BASE

#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE HPM_CORE0
#endif

/* ACMP desction */
#define BOARD_ACMP             HPM_ACMP2
#define BOARD_ACMP_CLK         clock_acmp2
#define BOARD_ACMP_CHANNEL     ACMP_CHANNEL_CHN0
#define BOARD_ACMP_IRQ         IRQn_ACMP2_0
#define BOARD_ACMP_PLUS_INPUT  ACMP_INPUT_DAC_OUT  /* use internal DAC */
#define BOARD_ACMP_MINUS_INPUT ACMP_INPUT_ANALOG_6 /* align with used pin */

/* uart section */
#ifndef BOARD_APP_UART_BASE
#define BOARD_APP_UART_BASE       HPM_UART4
#define BOARD_APP_UART_IRQ        IRQn_UART4
#define BOARD_APP_UART_BAUDRATE   (115200UL)
#define BOARD_APP_UART_CLK_NAME   clock_uart4
#define BOARD_APP_UART_RX_DMA_REQ HPM_DMA_SRC_UART4_RX
#define BOARD_APP_UART_TX_DMA_REQ HPM_DMA_SRC_UART4_TX
#endif

#define BOARD_APP_UART_BREAK_SIGNAL_PIN IOC_PAD_PY05

/* Trigger UART: UART0~3 use HPM_TRGM0_OUTPUT_SRC_UART_TRIG0, UART4~7 use HPM_TRGM0_OUTPUT_SRC_UART_TRIG1 */
#define BOARD_APP_UART_TRIG HPM_TRGM0_OUTPUT_SRC_UART_TRIG1
#define BOARD_UART_TRGM                     HPM_TRGM0
#define BOARD_UART_TRGM_GPTMR               HPM_GPTMR3
#define BOARD_UART_TRGM_GPTMR_CLK           clock_gptmr3
#define BOARD_UART_TRGM_GPTMR_CH            2
#define BOARD_UART_TRGM_GPTMR_INPUT         HPM_TRGM0_INPUT_SRC_GPTMR3_OUT2

/* uart rx idle demo section */
#define BOARD_UART_IDLE            BOARD_APP_UART_BASE
#define BOARD_UART_IDLE_IRQ        BOARD_APP_UART_IRQ
#define BOARD_UART_IDLE_CLK_NAME   BOARD_APP_UART_CLK_NAME
#define BOARD_UART_IDLE_TX_DMA_SRC BOARD_APP_UART_TX_DMA_REQ
#define BOARD_UART_IDLE_DMA_SRC    BOARD_APP_UART_RX_DMA_REQ

#define BOARD_UART_IDLE_GPTMR          HPM_GPTMR2
#define BOARD_UART_IDLE_GPTMR_CLK_NAME clock_gptmr2
#define BOARD_UART_IDLE_GPTMR_IRQ      IRQn_GPTMR2
#define BOARD_UART_IDLE_GPTMR_CMP_CH   0
#define BOARD_UART_IDLE_GPTMR_CAP_CH   2

/* uart microros sample section */
#define BOARD_MICROROS_UART_BASE     BOARD_APP_UART_BASE
#define BOARD_MICROROS_UART_IRQ      BOARD_APP_UART_IRQ
#define BOARD_MICROROS_UART_CLK_NAME BOARD_APP_UART_CLK_NAME

/* enet section */
#define BOARD_ENET_PPS           HPM_ENET0
#define BOARD_ENET_PPS_IDX       enet_pps_0
#define BOARD_ENET_PPS_PTP_CLOCK clock_ptp0

#define BOARD_ENET_RGMII                HPM_ENET0
#define BOARD_ENET_RGMII_RST_GPIO       HPM_GPIO0
#define BOARD_ENET_RGMII_RST_GPIO_INDEX GPIO_DO_GPIOC
#define BOARD_ENET_RGMII_RST_GPIO_PIN   (22U)
#define BOARD_ENET_RGMII_TX_DLY         (0U)
#define BOARD_ENET_RGMII_RX_DLY         (0U)
#define BOARD_ENET_RGMII_PTP_CLOCK      (clock_ptp0)
#define BOARD_ENET_RGMII_PPS0_PINOUT    (1)

/* usb cdc acm uart section */
#define BOARD_USB_CDC_ACM_UART            BOARD_APP_UART_BASE
#define BOARD_USB_CDC_ACM_UART_CLK_NAME   BOARD_APP_UART_CLK_NAME
#define BOARD_USB_CDC_ACM_UART_TX_DMA_SRC BOARD_APP_UART_TX_DMA_REQ
#define BOARD_USB_CDC_ACM_UART_RX_DMA_SRC BOARD_APP_UART_RX_DMA_REQ

/* uart lin sample section */
#define BOARD_UART_LIN          BOARD_APP_UART_BASE
#define BOARD_UART_LIN_IRQ      BOARD_APP_UART_IRQ
#define BOARD_UART_LIN_CLK_NAME BOARD_APP_UART_CLK_NAME
#define BOARD_UART_LIN_TX_PORT  GPIO_DI_GPIOY
#define BOARD_UART_LIN_TX_PIN   (0U) /* PY00 should align with used pin in pinmux configuration */
#define BOARD_UART_LIN_PLB_TRGM_IN_SRC HPM_TRGM0_INPUT_SRC_TRGM0_P08 /* align with used pin in pinmux configuration */

/* plb lin baudrate detection */
#define BOARD_PLB_TRGM_FILTER_GPIO_INPUT0  HPM_TRGM0_FILTER_SRC_TRGM0_P00
#define BOARD_PLB_TRGM_DMA_REQ0            HPM_TRGM0_DMA_SRC_TRGM0

#if !defined(CONFIG_NDEBUG_CONSOLE) || !CONFIG_NDEBUG_CONSOLE
#ifndef BOARD_CONSOLE_TYPE
#define BOARD_CONSOLE_TYPE CONSOLE_TYPE_UART
#endif

#if BOARD_CONSOLE_TYPE == CONSOLE_TYPE_UART
#ifndef BOARD_CONSOLE_UART_BASE
#if BOARD_RUNNING_CORE == HPM_CORE0
#define BOARD_CONSOLE_UART_BASE       HPM_UART0
#define BOARD_CONSOLE_UART_CLK_NAME   clock_uart0
#define BOARD_CONSOLE_UART_IRQ        IRQn_UART0
#define BOARD_CONSOLE_UART_TX_DMA_REQ HPM_DMA_SRC_UART0_TX
#define BOARD_CONSOLE_UART_RX_DMA_REQ HPM_DMA_SRC_UART0_RX
#else
#define BOARD_CONSOLE_UART_BASE       HPM_UART4
#define BOARD_CONSOLE_UART_CLK_NAME   clock_uart4
#define BOARD_CONSOLE_UART_IRQ        IRQn_UART4
#define BOARD_CONSOLE_UART_TX_DMA_REQ HPM_DMA_SRC_UART4_TX
#define BOARD_CONSOLE_UART_RX_DMA_REQ HPM_DMA_SRC_UART4_RX
#endif
#endif
#define BOARD_CONSOLE_UART_BAUDRATE (115200UL)
#endif
#endif

/* rtthread-nano finsh section */
#define BOARD_RT_CONSOLE_BASE        BOARD_CONSOLE_UART_BASE
#define BOARD_RT_CONSOLE_CLK_NAME    BOARD_CONSOLE_UART_CLK_NAME
#define BOARD_RT_CONSOLE_IRQ         BOARD_CONSOLE_UART_IRQ

/* modbus sample section */
#define BOARD_MODBUS_UART_BASE       BOARD_APP_UART_BASE
#define BOARD_MODBUS_UART_CLK_NAME   BOARD_APP_UART_CLK_NAME
#define BOARD_MODBUS_UART_RX_DMA_REQ BOARD_APP_UART_RX_DMA_REQ
#define BOARD_MODBUS_UART_TX_DMA_REQ BOARD_APP_UART_TX_DMA_REQ

/* sdram section */
#define BOARD_SDRAM_ADDRESS          (0x40000000UL)
#define BOARD_SDRAM_SIZE             (32 * SIZE_1MB)
#define BOARD_SDRAM_CS               FEMC_SDRAM_CS0
#define BOARD_SDRAM_PORT_SIZE        FEMC_SDRAM_PORT_SIZE_16_BITS
#define BOARD_SDRAM_COLUMN_ADDR_BITS FEMC_SDRAM_COLUMN_ADDR_9_BITS
#define BOARD_SDRAM_REFRESH_COUNT    (8192UL)
#define BOARD_SDRAM_REFRESH_IN_MS    (64UL)

#define BOARD_FEMC_ASYNC_SRAM_CS_INDEX    2
#define BOARD_FEMC_ASYNC_SRAM_AD_MUX_MODE true
#define BOARD_FEMC_ASYNC_SRAM_SIZE        (1024 * SIZE_1KB)

/* nor flash section */
#define BOARD_FLASH_BASE_ADDRESS (0x80000000UL)
#define BOARD_FLASH_SIZE         (1 * SIZE_1MB)

/* i2c section */
#define BOARD_APP_I2C_BASE     HPM_I2C1
#define BOARD_APP_I2C_IRQ      IRQn_I2C1
#define BOARD_APP_I2C_CLK_NAME clock_i2c1
#define BOARD_APP_I2C_DMA      HPM_HDMA
#define BOARD_APP_I2C_DMAMUX   HPM_DMAMUX
#define BOARD_APP_I2C_DMA_SRC  HPM_DMA_SRC_I2C1

/* i2c for i2s codec section */
#define BOARD_CODEC_I2C_BASE     HPM_I2C3
#define BOARD_CODEC_I2C_CLK_NAME clock_i2c3

/* PDM record data BUFF size */
#define BOARD_PDM_USING_SMALL_BUFF true

/* i2s section */
#define BOARD_APP_I2S_BASE           HPM_I2S0
#define BOARD_APP_I2S_CLK_NAME       clock_i2s0
#define BOARD_APP_AUDIO_CLK_SRC      clock_source_pll2_clk0
#define BOARD_APP_AUDIO_CLK_SRC_NAME clk_pll2clk0
#define BOARD_APP_I2S_TX_DATA_LINE   I2S_DATA_LINE_3
#define BOARD_APP_I2S_RX_DATA_LINE   I2S_DATA_LINE_0
#define BOARD_APP_I2S_TX_DMA_REQ     HPM_DMA_SRC_I2S0_TX_3
#define BOARD_APP_I2S_IRQ            IRQn_I2S0

#define BOARD_MIC_I2S               HPM_I2S0
#define BOARD_MIC_I2S_CLK_NAME      clock_i2s0
#define BOARD_MIC_I2S_DATA_LINE     I2S_DATA_LINE_0
#define BOARD_MIC_I2S_RX_DMAMUX_SRC HPM_DMA_SRC_I2S0_RX_0

#define BOARD_SPEAKER_I2S               HPM_I2S1
#define BOARD_SPEAKER_I2S_CLK_NAME      clock_i2s1
#define BOARD_SPEAKER_I2S_DATA_LINE     I2S_DATA_LINE_0
#define BOARD_SPEAKER_I2S_TX_DMAMUX_SRC HPM_DMA_SRC_I2S1_TX_0

/* pdm selection */
#define BOARD_PDM_SINGLE_CHANNEL_MASK (1U)
#define BOARD_PDM_DUAL_CHANNEL_MASK   (0x11U)

/* dma section */
#define BOARD_APP_XDMA      HPM_XDMA
#define BOARD_APP_HDMA      HPM_HDMA
#define BOARD_APP_XDMA_IRQ  IRQn_XDMA
#define BOARD_APP_HDMA_IRQ  IRQn_HDMA
#define BOARD_APP_DMAMUX    HPM_DMAMUX
#define TEST_DMA_CONTROLLER HPM_XDMA
#define TEST_DMA_IRQ        IRQn_XDMA

/* APP PWM */
#define BOARD_APP_PWM                   HPM_PWM1
#define BOARD_APP_PWM_CLOCK_NAME        clock_pwm1
#define BOARD_APP_PWM_OUT1              pwm_channel_0
#define BOARD_APP_PWM_OUT2              pwm_channel_1
#define BOARD_APP_PWM_OUT3              pwm_channel_2
#define BOARD_APP_PWM_OUT4              pwm_channel_3
#define BOARD_APP_PWM_OUT5              pwm_channel_4
#define BOARD_APP_PWM_OUT6              pwm_channel_5
#define BOARD_APP_PWM_FAULT_PIN         (2)
#define BOARD_APP_TRGM                  HPM_TRGM0
#define BOARD_APP_PWM_IRQ               IRQn_PWM1
#define BOARD_APP_TRGM_PWM_OUTPUT       HPM_TRGM0_OUTPUT_SRC_PWM1_TRIG_IN0
#define BOARD_APP_TRGM_PWM_OUTPUT1      HPM_TRGM0_OUTPUT_SRC_PWM1_TRIG_IN1
#define BOARD_APP_TRGM_PWM_OUTPUT2      HPM_TRGM0_OUTPUT_SRC_PWM1_TRIG_IN2
#define BOARD_APP_TRGM_PWM_INPUT        HPM_TRGM0_INPUT_SRC_PWM1_TRGO_0

/* gptmr section */
#define BOARD_GPTMR                   HPM_GPTMR3
#define BOARD_GPTMR_IRQ               IRQn_GPTMR3
#define BOARD_GPTMR_CHANNEL           0
#define BOARD_GPTMR_DMA_SRC           HPM_DMA_SRC_GPTMR3_0
#define BOARD_GPTMR_CLK_NAME          clock_gptmr3
#define BOARD_GPTMR_PWM               HPM_GPTMR3
#define BOARD_GPTMR_PWM_CHANNEL       0
#define BOARD_GPTMR_PWM_DMA_SRC       HPM_DMA_SRC_GPTMR3_0
#define BOARD_GPTMR_PWM_CLK_NAME      clock_gptmr3
#define BOARD_GPTMR_PWM_IRQ           IRQn_GPTMR3
#define BOARD_GPTMR_PWM_SYNC          HPM_GPTMR3
#define BOARD_GPTMR_PWM_SYNC_CHANNEL  2
#define BOARD_GPTMR_PWM_SYNC_CLK_NAME clock_gptmr3

/* User button */
#define BOARD_APP_GPIO_CTRL        HPM_GPIO0
#define BOARD_APP_GPIO_INDEX       GPIO_DI_GPIOC
#define BOARD_APP_GPIO_PIN         23
#define BOARD_APP_GPIO_IRQ         IRQn_GPIO0_C
#define BOARD_BUTTON_PRESSED_VALUE 0

/* gpiom section */
#define BOARD_APP_GPIOM_BASE            HPM_GPIOM
#define BOARD_APP_GPIOM_USING_CTRL      HPM_FGPIO
#define BOARD_APP_GPIOM_USING_CTRL_NAME gpiom_core0_fast

/* spi section */
#define BOARD_APP_SPI_BASE              HPM_SPI2
#define BOARD_APP_SPI_CLK_NAME          clock_spi2
#define BOARD_APP_SPI_IRQ               IRQn_SPI2
#define BOARD_APP_SPI_SCLK_FREQ         (20000000UL)
#define BOARD_APP_SPI_ADDR_LEN_IN_BYTES (1U)
#define BOARD_APP_SPI_DATA_LEN_IN_BITS  (8U)
#define BOARD_APP_SPI_RX_DMA            HPM_DMA_SRC_SPI2_RX
#define BOARD_APP_SPI_TX_DMA            HPM_DMA_SRC_SPI2_TX
#define BOARD_SPI_CS_GPIO_CTRL          HPM_GPIO0
#define BOARD_SPI_CS_PIN                IOC_PAD_PY05
#define BOARD_SPI_CS_ACTIVE_LEVEL       (0U)

/* DAC section */
#define BOARD_DAC_BASE           HPM_DAC0
#define BOARD_DAC_IRQn           IRQn_DAC0
#define BOARD_APP_DAC_CLOCK_NAME clock_dac0

/* Flash section */
#define BOARD_APP_XPI_NOR_XPI_BASE     (HPM_XPI0)
#define BOARD_APP_XPI_NOR_CFG_OPT_HDR  (0xfcf90002U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT0 (0x00000005U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT1 (0x00001000U)

/* ADC section */
#define BOARD_APP_ADC16_NAME     "ADC2"
#define BOARD_APP_ADC16_BASE     HPM_ADC2
#define BOARD_APP_ADC16_IRQn     IRQn_ADC2
#define BOARD_APP_ADC16_CH_1     (10U)
#define BOARD_APP_ADC16_CLK_NAME (clock_adc2)
#define BOARD_APP_ADC16_CLK_BUS  (clk_adc_src_ahb0)

#define BOARD_APP_ADC16_HW_TRIG_SRC_CLK_NAME clock_pwm0
#define BOARD_APP_ADC16_HW_TRIG_SRC          HPM_PWM0
#define BOARD_APP_ADC16_HW_TRGM              HPM_TRGM0
#define BOARD_APP_ADC16_HW_TRGM_IN           HPM_TRGM0_INPUT_SRC_PWM0_TRGO_0
#define BOARD_APP_ADC16_HW_TRGM_OUT_SEQ      TRGM_TRGOCFG_ADC2_STRGI

#define BOARD_APP_ADC16_NAME_MASTER     "ADC2"
#define BOARD_APP_ADC16_BASE_MASTER     HPM_ADC2
#define BOARD_APP_ADC16_IRQn_MASTER     IRQn_ADC2
#define BOARD_APP_ADC16_CLK_NAME_MASTER (clock_adc2)

#define BOARD_APP_ADC16_NAME_SLAVE     "ADC3"
#define BOARD_APP_ADC16_BASE_SLAVE     HPM_ADC3
#define BOARD_APP_ADC16_IRQn_SLAVE     IRQn_ADC3
#define BOARD_APP_ADC16_CLK_NAME_SLAVE (clock_adc3)

#define BOARD_APP_ADC16_MASTER_CH_1 (1U)
#define BOARD_APP_ADC16_SLAVE_CH_1  (0U)

#define BOARD_APP_ADC16_HW_TRIG_SRC_CLK_NAME   clock_pwm0
#define BOARD_APP_ADC16_HW_TRIG_SRC            HPM_PWM0
#define BOARD_APP_ADC16_HW_TRGM                HPM_TRGM0
#define BOARD_APP_ADC16_HW_TRGM_IN             HPM_TRGM0_INPUT_SRC_PWM0_TRGO_0
#define BOARD_APP_ADC16_HW_TRGM_OUT_SEQ_MASTER TRGM_TRGOCFG_ADC2_STRGI
#define BOARD_APP_ADC16_HW_TRGM_OUT_SEQ_SLAVE  TRGM_TRGOCFG_ADC3_STRGI
#define BOARD_APP_ADC16_HW_TRGM_OUT_PMT        TRGM_TRGOCFG_ADCX_PTRGI0A

#define BOARD_APP_ADC16_PMT_TRIG_CH ADC16_CONFIG_TRG0A

/* DAC section */
#define BOARD_DAC_BASE           HPM_DAC0
#define BOARD_DAC_IRQn           IRQn_DAC0
#define BOARD_APP_DAC_CLOCK_NAME clock_dac0

/* CAN section */
#define BOARD_APP_CAN_BASE HPM_MCAN1
#define BOARD_APP_CAN_IRQn IRQn_MCAN1

/*
 * timer for board delay
 */
#define BOARD_DELAY_TIMER          (HPM_GPTMR0)
#define BOARD_DELAY_TIMER_CH       0
#define BOARD_DELAY_TIMER_CLK_NAME (clock_gptmr0)

#define BOARD_CALLBACK_TIMER          (HPM_GPTMR0)
#define BOARD_CALLBACK_TIMER_CH       1
#define BOARD_CALLBACK_TIMER_IRQ      IRQn_GPTMR0
#define BOARD_CALLBACK_TIMER_CLK_NAME (clock_gptmr0)

/* LED */
#define BOARD_LED_GPIO_CTRL  HPM_GPIO0
#define BOARD_LED_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_LED_GPIO_PIN   25
#define BOARD_LED_OFF_LEVEL  0
#define BOARD_LED_ON_LEVEL   1

/* MOTOR */
#define BOARD_MOTOR_CLK_NAME clock_mot0

/*BLDC PWM */
#define BOARD_BLDCPWM              HPM_PWM1
#define BOARD_BLDC_UH_PWM_OUTPIN   (pwm_channel_0)
#define BOARD_BLDC_UL_PWM_OUTPIN   (pwm_channel_1)
#define BOARD_BLDC_VH_PWM_OUTPIN   (pwm_channel_2)
#define BOARD_BLDC_VL_PWM_OUTPIN   (pwm_channel_3)
#define BOARD_BLDC_WH_PWM_OUTPIN   (pwm_channel_4)
#define BOARD_BLDC_WL_PWM_OUTPIN   (pwm_channel_5)
#define BOARD_BLDCPWM_TRGM         HPM_TRGM0
#define BOARD_BLDCAPP_PWM_IRQ      IRQn_PWM1
#define BOARD_BLDCPWM_CMP_INDEX_0  (0U)
#define BOARD_BLDCPWM_CMP_INDEX_1  (1U)
#define BOARD_BLDCPWM_CMP_INDEX_2  (2U)
#define BOARD_BLDCPWM_CMP_INDEX_3  (3U)
#define BOARD_BLDCPWM_CMP_INDEX_4  (4U)
#define BOARD_BLDCPWM_CMP_INDEX_5  (5U)
#define BOARD_BLDCPWM_CMP_INDEX_6  (6U)
#define BOARD_BLDCPWM_CMP_INDEX_7  (7U)
#define BOARD_BLDCPWM_CMP_TRIG_CMP (16U)

/* BLDC ADC */
#define BOARD_BLDC_ADC_MODULE    ADCX_MODULE_ADC16
#define BOARD_BLDC_ADC_U_BASE    HPM_ADC0
#define BOARD_BLDC_ADC_V_BASE    HPM_ADC2
#define BOARD_BLDC_ADC_W_BASE    HPM_ADC3
#define BOARD_BLDC_ADC_TRIG_FLAG adc16_event_trig_complete

#define BOARD_BLDC_ADC_CH_U                   (14U)
#define BOARD_BLDC_ADC_CH_V                   (8U)
#define BOARD_BLDC_ADC_CH_W                   (9U)
#define BOARD_BLDC_ADC_IRQn                   IRQn_ADC0 /* ADC_U_IRQ */
#define BOARD_BLDC_ADC_PMT_DMA_SIZE_IN_4BYTES (ADC_SOC_PMT_MAX_DMA_BUFF_LEN_IN_4BYTES)
#define BOARD_BLDC_ADC_TRG                    ADC16_CONFIG_TRG0A
#define BOARD_BLDC_ADC_PREEMPT_TRIG_LEN       (1U)
#define BOARD_BLDC_PWM_TRIG_OUT_CHN           (0U)
#define BOARD_BLDC_DMA_MUX_SRC                HPM_DMA_SRC_MOT_0
#define BOARD_BLDC_DMA_CHN                    (0U)
#define BOARD_BLDC_DMA_TRG_DST                TRGM_TRGOCFG_TRGM_DMA0
#define BOARD_BLDC_DMA_TRG_SRC                HPM_TRGM0_DMA_SRC_TRGM0
#define BOARD_BLDC_DMA_TRG_INDEX              TRGM_DMACFG_0
#define BOARD_BLDC_DMA_TRG_CMP_INDEX          (9U)
#define BOARD_BLDC_DMA_TRG_IN                 HPM_TRGM0_INPUT_SRC_PWM0_CH9REF

/* BLDC TRGM */
#define BOARD_BLDC_PWM_TRG_ADC         HPM_TRGM0_INPUT_SRC_PWM1_TRGO_0
#define BOARD_BLDC_TRG_ADC             HPM_TRGM0_OUTPUT_SRC_ADCX_PTRGI0A
#define BOARD_BLDC_TRG_VSC             HPM_TRGM0_OUTPUT_SRC_VSC0_TRIG_IN0

#define BOARD_BLDC_TRGM_ADC_MATRIX_TO_VSC_ADC0 trgm_adc_matrix_output_to_vsc0_adc0
#define BOARD_BLDC_TRGM_ADC_MATRIX_TO_VSC_ADC1 trgm_adc_matrix_output_to_vsc0_adc1
#define BOARD_BLDC_TRGM_ADC_MATRIX_TO_VSC_ADC2 trgm_adc_matrix_output_to_vsc0_adc2
#define BOARD_BLDC_TRGM_ADC_MATRIX_FROM_ADC_U  trgm_adc_matrix_in_from_adc0 /* ADC_U_BASE */
#define BOARD_BLDC_TRGM_ADC_MATRIX_FROM_ADC_V  trgm_adc_matrix_in_from_adc2 /* ADC_V_BASE */
#define BOARD_BLDC_TRGM_ADC_MATRIX_FROM_ADC_W  trgm_adc_matrix_in_from_adc3 /* ADC_W_BASE */

#define BOARD_BLDC_TRGM_ADC_MATRIX_TO_CLC_ID_ADC   trgm_adc_matrix_output_to_clc0_id_adc
#define BOARD_BLDC_TRGM_ADC_MATRIX_TO_CLC_IQ_ADC   trgm_adc_matrix_output_to_clc0_iq_adc
#define BOARD_BLDC_TRGM_ADC_MATRIX_FROM_VSC_ID_ADC trgm_adc_matrix_in_from_vsc0_id_adc
#define BOARD_BLDC_TRGM_ADC_MATRIX_FROM_VSC_IQ_ADC trgm_adc_matrix_in_from_vsc0_iq_adc

#define BOARD_BLDC_TRGM_DAC_MATRIX_TO_QEO_VD_DAC   trgm_dac_matrix_output_to_qeo0_vd_dac
#define BOARD_BLDC_TRGM_DAC_MATRIX_TO_QEO_VQ_DAC   trgm_dac_matrix_output_to_qeo0_vq_dac
#define BOARD_BLDC_TRGM_DAC_MATRIX_FROM_CLC_VD_DAC trgm_dac_matrix_in_from_clc0_vd_dac
#define BOARD_BLDC_TRGM_DAC_MATRIX_FROM_CLC_VQ_DAC trgm_dac_matrix_in_from_clc0_vq_dac

#define BOARD_BLDC_TRGM_DAC_MATRIX_TO_PWM_DAC0   trgm_dac_matrix_output_to_pwm1_dac0
#define BOARD_BLDC_TRGM_DAC_MATRIX_TO_PWM_DAC1   trgm_dac_matrix_output_to_pwm1_dac1
#define BOARD_BLDC_TRGM_DAC_MATRIX_TO_PWM_DAC2   trgm_dac_matrix_output_to_pwm1_dac2
#define BOARD_BLDC_TRGM_DAC_MATRIX_FROM_QEO_DAC0 trgm_dac_matrix_in_from_qeo0_dac0
#define BOARD_BLDC_TRGM_DAC_MATRIX_FROM_QEO_DAC1 trgm_dac_matrix_in_from_qeo0_dac1
#define BOARD_BLDC_TRGM_DAC_MATRIX_FROM_QEO_DAC2 trgm_dac_matrix_in_from_qeo0_dac2

#define BOARD_BLDC_QEO                      HPM_QEO0
#define BOARD_BLDC_TRGM_POS_MATRIX_TO_VSC   trgm_pos_matrix_output_to_vsc0
#define BOARD_BLDC_TRGM_POS_MATRIX_TO_QEO   trgm_pos_matrix_output_to_qeo0
#define BOARD_BLDC_TRGM_POS_MATRIX_FROM_QEI trgm_pos_matrix_in_from_qei0

/* BLDC TIMER */
#define BOARD_BLDC_TMR_1MS    HPM_GPTMR2
#define BOARD_BLDC_TMR_BASE   HPM_GPTMR2
#define BOARD_BLDC_TMR_CH     0
#define BOARD_BLDC_TMR_CMP    0
#define BOARD_BLDC_TMR_IRQ    IRQn_GPTMR2
#define BOARD_BLDC_TMR_CLOCK  clock_gptmr2
#define BOARD_BLDC_TMR_RELOAD (100000U)

/* BLDC PARAM */
#define BOARD_BLDC_BLOCK_SPEED_KP (0.0005f)
#define BOARD_BLDC_BLOCK_SPEED_KI (0.000009f)

#define BOARD_BLDC_HW_FOC_SPEED_KP (0.01f)
#define BOARD_BLDC_HW_FOC_SPEED_KI (0.001f)
#define BOARD_BLDC_SW_FOC_SPEED_LOOP_SPEED_KP (0.0074f)
#define BOARD_BLDC_SW_FOC_SPEED_LOOP_SPEED_KI (0.0001f)
#define BOARD_BLDC_SW_FOC_POSITION_LOOP_SPEED_KP (0.05f)
#define BOARD_BLDC_SW_FOC_POSITION_LOOP_SPEED_KI (0.001f)
#define BOARD_BLDC_HW_FOC_POSITION_KP (34.7f)
#define BOARD_BLDC_HW_FOC_POSITION_KI (0.113f)
#define BOARD_BLDC_SW_FOC_POSITION_KP (154.7f)
#define BOARD_BLDC_SW_FOC_POSITION_KI (0.113f)

#define BOARD_BLDC_HFI_SPEED_LOOP_KP (40.0f)
#define BOARD_BLDC_HFI_SPEED_LOOP_KI (0.005f)
#define BOARD_BLDC_HFI_PLL_KP (11.0f)
#define BOARD_BLDC_HFI_PLL_KI (0.008f)

/* HALL */

/* RDC */
#define BOARD_RDC_BASE                      HPM_RDC0
#define BOARD_RDC_TRGM                      HPM_TRGM0
#define BOARD_RDC_TRG_IN                    HPM_TRGM0_INPUT_SRC_RDC0_TRGO_0
#define BOARD_RDC_TRG_OUT                   TRGM_TRGOCFG_TRGM0_P00
#define BOARD_RDC_TRG_ADC                   HPM_TRGM0_OUTPUT_SRC_ADCX_PTRGI0A
#define BOARD_RDC_ADC_I_BASE                HPM_ADC0
#define BOARD_RDC_ADC_Q_BASE                HPM_ADC2
#define BOARD_RDC_ADC_I_CHN                 (14U)
#define BOARD_RDC_ADC_Q_CHN                 (8U)
#define BOARD_RDC_IRQ                  IRQn_RDC0
#define BOARD_RDC_ADC_TRIG_FLAG             adc16_event_trig_complete
#define BOARD_RDC_ADC_TRG                   ADC16_CONFIG_TRG0A
#define BOARD_APP_RDC_ADC_MATRIX_TO_ADC0    trgm_adc_matrix_output_to_rdc0_adc0
#define BOARD_APP_RDC_ADC_MATRIX_TO_ADC1    trgm_adc_matrix_output_to_rdc0_adc1
#define BOARD_APP_RDC_ADC_MATRIX_FROM_ADC_I trgm_adc_matrix_in_from_adc0
#define BOARD_APP_RDC_ADC_MATRIX_FROM_ADC_Q trgm_adc_matrix_in_from_adc2

/* QEIV2 */
#define BOARD_BLDC_QEI_TRGM                      HPM_TRGM0
#define BOARD_BLDC_QEIV2_BASE                    HPM_QEI0
#define BOARD_BLDC_QEIV2_IRQ                     IRQn_QEI0
#define BOARD_BLDC_QEI_MOTOR_PHASE_COUNT_PER_REV (16U)
#define BOARD_BLDC_QEI_CLOCK_SOURCE              clock_qei0
#define BOARD_BLDC_QEI_FOC_PHASE_COUNT_PER_REV   (4000U)

#define BOARD_APP_QEIV2_BASE                  HPM_QEI1
#define BOARD_APP_QEIV2_IRQ                   IRQn_QEI1
#define BOARD_APP_QEI_CLOCK_SOURCE            clock_qei1
#define BOARD_APP_QEI_ADC_COS_BASE            HPM_ADC2
#define BOARD_APP_QEI_ADC_COS_CHN             (9U)
#define BOARD_APP_QEI_ADC_SIN_BASE            HPM_ADC0
#define BOARD_APP_QEI_ADC_SIN_CHN             (14U)
#define BOARD_APP_QEI_ADC_MATRIX_TO_ADC0      trgm_adc_matrix_output_to_qei1_adc0
#define BOARD_APP_QEI_ADC_MATRIX_TO_ADC1      trgm_adc_matrix_output_to_qei1_adc1
#define BOARD_APP_QEI_ADC_MATRIX_FROM_ADC_COS trgm_adc_matrix_in_from_adc2
#define BOARD_APP_QEI_ADC_MATRIX_FROM_ADC_SIN trgm_adc_matrix_in_from_adc0
#define BOARD_APP_QEI_TRG_ADC                 HPM_TRGM0_OUTPUT_SRC_ADCX_PTRGI0A

/* PLB */
#define BOARD_PLB_CLOCK_NAME           clock_plb0

#define BOARD_PLB_COUNTER              HPM_PLB
#define BOARD_PLB_PWM_BASE             HPM_PWM0
#define BOARD_PLB_PWM_CLOCK_NAME       clock_mot0
#define BOARD_PLB_TRGM                 HPM_TRGM0
#define BOARD_PLB_PWM_TRG              (HPM_TRGM0_INPUT_SRC_PWM0_TRGO_0)
#define BOARD_PLB_IN_PWM_TRG           (TRGM_TRGOCFG_PLB_IN_00)
#define BOARD_PLB_IN_PWM_PULSE_TRG     (TRGM_TRGOCFG_PLB_IN_02)
#define BOARD_PLB_CLR_SIGNAL_INPUT     (HPM_TRGM0_INPUT_SRC_PLB_OUT32)
#define BOARD_PLB_TO_TRG_IN            (HPM_TRGM0_INPUT_SRC_PLB_OUT00)
#define BOARD_PLB_TRG_OUT              (HPM_TRGM0_OUTPUT_SRC_TRGM0_P10)
#define BOARD_PLB_IO_TRG_SHIFT         (10)
#define BOARD_PLB_PWM_CMP              (8U)
#define BOARD_PLB_PWM_CHN              (8U)
#define BOARD_PLB_CHN                  plb_chn0

#define BOARD_PLB_PHASE_COUNT_DEFAULT   (4000)
#define BOARD_PLB_FILTER_LENGTH_DEFAULT (100)
#define BOARD_PLB_QEI_A_PIN_SOURCE      HPM_TRGM0_INPUT_SRC_TRGM0_P08
#define BOARD_PLB_QEI_B_PIN_SOURCE      HPM_TRGM0_INPUT_SRC_TRGM0_P09
#define BOARD_PLB_QEI_Z_PIN_SOURCE      HPM_TRGM0_INPUT_SRC_TRGM0_P10

#define BOARD_PLB_FILTER_SIG_INPUT_SOURCE  HPM_TRGM0_INPUT_SRC_TRGM0_P10
#define BOARD_PLB_FILTER_SIG_OUTUPT_SOURCE HPM_TRGM0_OUTPUT_SRC_TRGM0_P12
#define BOARD_PLB_FILTER_IO_TRG_SHIFT      (12)

/* QEO */
#define BOARD_QEO          HPM_QEO1
#define BOARD_QEO_TRGM_POS trgm_pos_matrix_output_to_qeo1

#define BOARD_QEO_PWM             HPM_QEO1 /*QEO instance should align with PWM instance, such as QEO1 -> PWM1 */
#define BOARD_QEO_TRGM_POS_PWM    trgm_pos_matrix_output_to_qeo1
#define BOARD_QEO_PWM_SAFETY_TRGM HPM_TRGM0_OUTPUT_SRC_QEO1_TRIG_IN1

/* SEI */
#define BOARD_SEI                 HPM_SEI
#define BOARD_SEI_CTRL            SEI_CTRL_1
#define BOARD_SEI_IRQn            IRQn_SEI0_1
#define BOARD_SEI_CLOCK_NAME      clock_sei0
#define BOARD_TRGM_POS_SOURCE_SEI trgm_pos_matrix_in_from_sei_pos1

/* MTG */
#define BOARD_TRGM_POS_DEST_MTG trgm_pos_matrix_output_to_mtg0

/* VSC */
#define BOARD_VSC      HPM_VSC0
#define BOARD_VSC_IRQn IRQn_VSC0

/* CLC */
#define BOARD_CLC      HPM_CLC0
#define BOARD_CLC_IRQn IRQn_CLC0_0

/* Tamper Section */
#define BOARD_TAMP_ACTIVE_CH    4
#define BOARD_TAMP_LOW_LEVEL_CH 6

/* sdm section */
#define BOARD_SDM                 HPM_SDM0
#define BOARD_SDM_IRQ             IRQn_SDM0
#define BOARD_SDM_CHANNEL         0
#define BOARD_SDM_TRGM            HPM_TRGM0
#define BOARD_SDM_TRGM_GPTMR      HPM_GPTMR3
#define BOARD_SDM_TRGM_GPTMR_CLK  clock_gptmr3
#define BOARD_SDM_TRGM_GPTMR_CH   2
#define BOARD_SDM_TRGM_INPUT_SRC  HPM_TRGM0_INPUT_SRC_GPTMR3_OUT2
#define BOARD_SDM_TRGM_OUTPUT_DST HPM_TRGM0_OUTPUT_SRC_SDM_PWM_SOC15
#define BOARD_SDM_TRGM_SYNC_SRC   (15)
/* need to provide clock to sdm sensor */
#define BOARD_SDM_SENSOR_REQUIRE_CLK true
#define BOARD_SDM_CLK_PWM            HPM_PWM0
#define BOARD_SDM_CLK_PWM_CLK_NAME   clock_pwm0
#define BOARD_SDM_CLK_PWM_OUT        (2)

#ifndef BOARD_SHOW_CLOCK
#define BOARD_SHOW_CLOCK 1
#endif
#ifndef BOARD_SHOW_BANNER
#define BOARD_SHOW_BANNER 1
#endif

/* FreeRTOS Definitions */
#define BOARD_FREERTOS_TIMER          HPM_GPTMR2
#define BOARD_FREERTOS_TIMER_CHANNEL  1
#define BOARD_FREERTOS_TIMER_IRQ      IRQn_GPTMR2
#define BOARD_FREERTOS_TIMER_CLK_NAME clock_gptmr2

#define BOARD_FREERTOS_TICK_SRC_PWM          HPM_PWM0
#define BOARD_FREERTOS_TICK_SRC_PWM_IRQ      IRQn_PWM0
#define BOARD_FREERTOS_TICK_SRC_PWM_CLK_NAME clock_pwm0
#define BOARD_FREERTOS_TICK_SRC_PWM_COUNTER  pwm_counter_0
#define BOARD_FREERTOS_TICK_SRC_PWM_SHADOW   PWMV2_SHADOW_INDEX(0)

#define BOARD_FREERTOS_LOWPOWER_TIMER          HPM_PTMR
#define BOARD_FREERTOS_LOWPOWER_TIMER_CHANNEL  1
#define BOARD_FREERTOS_LOWPOWER_TIMER_IRQ      IRQn_PTMR
#define BOARD_FREERTOS_LOWPOWER_TIMER_CLK_NAME clock_ptmr

/* Threadx Definitions */
#define BOARD_THREADX_TIMER          HPM_GPTMR2
#define BOARD_THREADX_TIMER_CHANNEL  1
#define BOARD_THREADX_TIMER_IRQ      IRQn_GPTMR2
#define BOARD_THREADX_TIMER_CLK_NAME clock_gptmr2

#define BOARD_THREADX_LOWPOWER_TIMER          HPM_PTMR
#define BOARD_THREADX_LOWPOWER_TIMER_CHANNEL  1
#define BOARD_THREADX_LOWPOWER_TIMER_IRQ      IRQn_PTMR
#define BOARD_THREADX_LOWPOWER_TIMER_CLK_NAME clock_ptmr

/* uC/OS-III Definitions */
#define BOARD_UCOS_TIMER          HPM_GPTMR2
#define BOARD_UCOS_TIMER_CHANNEL  1
#define BOARD_UCOS_TIMER_IRQ      IRQn_GPTMR2
#define BOARD_UCOS_TIMER_CLK_NAME clock_gptmr2

/* LOBS */
#define BOARD_LOBS_TRIG_GROUP lobs_signal_group_PC
#define BOARD_LOBS_TRIG_PIN_0 28
#define BOARD_LOBS_TRIG_PIN_1 29

/* i2s over spi Section*/
#define BOARD_I2S_SPI_CS_GPIO_CTRL  HPM_GPIO0
#define BOARD_I2S_SPI_CS_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_I2S_SPI_CS_GPIO_PIN   16
#define BOARD_I2S_SPI_CS_GPIO_PAD   IOC_PAD_PA16

#define BOARD_GPTMR_I2S_MCLK          HPM_GPTMR0
#define BOARD_GPTMR_I2S_MCLK_CHANNEL  2
#define BOARD_GPTMR_I2S_MCLK_CLK_NAME clock_gptmr0

#define BOARD_GPTMR_I2S_LRCK          HPM_GPTMR3
#define BOARD_GPTMR_I2S_LRCK_CHANNEL  0
#define BOARD_GPTMR_I2S_LRCK_CLK_NAME clock_gptmr3

#define BOARD_GPTMR_I2S_BCLK          HPM_GPTMR3
#define BOARD_GPTMR_I2S_BLCK_CHANNEL  2
#define BOARD_GPTMR_I2S_BLCK_CLK_NAME clock_gptmr3

#define BOARD_GPTMR_I2S_FINSH          HPM_GPTMR3
#define BOARD_GPTMR_I2S_FINSH_IRQ      IRQn_GPTMR3
#define BOARD_GPTMR_I2S_FINSH_CHANNEL  1
#define BOARD_GPTMR_I2S_FINSH_CLK_NAME clock_gptmr3

/* PPI */
#define BOARD_PPI_ASYNC_SRAM_AD_MUX_MODE  true
#define BOARD_PPI_ASYNC_SRAM_CS_INDEX     3
#define BOARD_PPI_ASYNC_SRAM_SIG_DQ0_7    ppi_dq_pins_0_7
#define BOARD_PPI_ASYNC_SRAM_SIG_DQ8_15   ppi_dq_pins_8_15
#define BOARD_PPI_ASYNC_SRAM_SIG_DQ16_23  ppi_dq_pins_16_23
#define BOARD_PPI_ASYNC_SRAM_SIG_DQ24_31  ppi_dq_pins_24_31
#define BOARD_PPI_ASYNC_SRAM_ADV_CTRL_PIN 7
#define BOARD_PPI_ASYNC_SRAM_WE_CTRL_PIN  6
#define BOARD_PPI_ASYNC_SRAM_OE_CTRL_PIN  5
#define BOARD_PPI_ASYNC_SRAM_SIZE         (1024 * SIZE_1KB)

#define BOARD_PPI_ADC_CS_INDEX 2

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

typedef void (*board_timer_cb)(void);

void board_init(void);
void board_init_console(void);
void board_init_core1(void);
void board_init_uart(UART_Type *ptr);
uint32_t board_init_i2c_clock(I2C_Type *ptr);
void board_init_i2c(I2C_Type *ptr);
void board_init_can(MCAN_Type *ptr);
void board_init_femc_pins(void);
void board_init_gpio_pins(void);
void board_init_spi_pins(SPI_Type *ptr);
void board_init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void board_write_spi_cs(uint32_t pin, uint8_t state);
uint8_t board_get_led_gpio_off_level(void);
void board_init_led_pins(void);
void board_led_write(uint8_t state);
void board_led_toggle(void);

/* Initialize SoC overall clocks */
void board_init_clock(void);
uint32_t board_init_femc_clock(void);
uint32_t board_init_uart_clock(UART_Type *ptr);
uint32_t board_init_spi_clock(SPI_Type *ptr);
uint32_t board_init_can_clock(MCAN_Type *ptr);
uint32_t board_init_adc_clock(void *ptr, bool clk_src_bus);
uint32_t board_init_dac_clock(DAC_Type *ptr, bool clk_src_ahb);
void board_init_acmp_clock(ACMP_Type *ptr);
void board_init_i2s_pins(I2S_Type *ptr);
uint32_t board_config_i2s_clock(I2S_Type *ptr, uint32_t sample_rate);
uint32_t board_init_pdm_clock(void);
uint32_t board_init_dao_clock(void);
void board_init_dao_pins(void);
void board_init_adc16_pins(void);
void board_init_acmp_pins(void);
void board_init_dac_pins(DAC_Type *ptr);
void board_init_usb(USB_Type *ptr);
void board_init_enet_pps_pins(ENET_Type *ptr);
uint8_t board_get_enet_dma_pbl(ENET_Type *ptr);
hpm_stat_t board_reset_enet_phy(ENET_Type *ptr);
hpm_stat_t board_init_enet_pins(ENET_Type *ptr);
hpm_stat_t board_init_enet_rmii_reference_clock(ENET_Type *ptr, bool internal);
hpm_stat_t board_init_enet_rgmii_clock_delay(ENET_Type *ptr);
hpm_stat_t board_init_enet_ptp_clock(ENET_Type *ptr);
hpm_stat_t board_enable_enet_irq(ENET_Type *ptr);
hpm_stat_t board_disable_enet_irq(ENET_Type *ptr);

/*
 * @brief Initialize PMP and PMA for but not limited to the following purposes:
 *      -- non-cacheable memory initialization
 */
void board_init_pmp(void);
void board_delay_us(uint32_t us);
void board_delay_ms(uint32_t ms);
void board_timer_create(uint32_t ms, board_timer_cb cb);
void board_ungate_mchtmr_at_lp_mode(void);

/*
 * Get GPIO pin level of onboard LED
 */
uint8_t board_get_led_gpio_off_level(void);
void board_init_sei_pins(SEI_Type *ptr, uint8_t sei_ctrl_idx);
void board_init_adc_qeiv2_pins(void);

void board_init_gptmr_channel_pin(GPTMR_Type *ptr, uint32_t channel, bool as_comp);
uint32_t board_init_gptmr_clock(GPTMR_Type *ptr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _HPM_BOARD_H */
