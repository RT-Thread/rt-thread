/*
 * Copyright (c) 2023-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_BOARD_H
#define _HPM_BOARD_H
#include <stdio.h>
#include <stdarg.h>
#include "hpm_common.h"
#include "hpm_clock_drv.h"
#include "hpm_soc.h"
#include "hpm_soc_feature.h"
#include "pinmux.h"
#if !defined(CONFIG_NDEBUG_CONSOLE) || !CONFIG_NDEBUG_CONSOLE
#include "hpm_debug_console.h"
#endif

#define BOARD_NAME          "hpm5300evk"
#define BOARD_UF2_SIGNATURE (0x0A4D5048UL)

/* ACMP desction */
#define BOARD_ACMP             HPM_ACMP
#define BOARD_ACMP_CLK         clock_acmp0
#define BOARD_ACMP_CHANNEL     ACMP_CHANNEL_CHN1
#define BOARD_ACMP_IRQ         IRQn_ACMP_1
#define BOARD_ACMP_PLUS_INPUT  ACMP_INPUT_DAC_OUT  /* use internal DAC */
#define BOARD_ACMP_MINUS_INPUT ACMP_INPUT_ANALOG_4 /* align with used pin */

/* dma section */
#define BOARD_APP_HDMA      HPM_HDMA
#define BOARD_APP_HDMA_IRQ  IRQn_HDMA
#define BOARD_APP_DMAMUX    HPM_DMAMUX
#define TEST_DMA_CONTROLLER HPM_HDMA
#define TEST_DMA_IRQ        IRQn_HDMA

#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE HPM_CORE0
#endif

/* uart section */
#ifndef BOARD_APP_UART_BASE
#define BOARD_APP_UART_BASE       HPM_UART2
#define BOARD_APP_UART_IRQ        IRQn_UART2
#define BOARD_APP_UART_BAUDRATE   (115200UL)
#define BOARD_APP_UART_CLK_NAME   clock_uart2
#define BOARD_APP_UART_RX_DMA_REQ HPM_DMA_SRC_UART2_RX
#define BOARD_APP_UART_TX_DMA_REQ HPM_DMA_SRC_UART2_TX
#endif

#define BOARD_APP_UART_BREAK_SIGNAL_PIN IOC_PAD_PA26

/* Trigger UART: UART0~3 use HPM_TRGM0_OUTPUT_SRC_UART_TRIG0, UART4~7 use HPM_TRGM0_OUTPUT_SRC_UART_TRIG1 */
#define BOARD_APP_UART_TRIG HPM_TRGM0_OUTPUT_SRC_UART_TRIG0
#define BOARD_UART_TRGM                     HPM_TRGM0
#define BOARD_UART_TRGM_GPTMR               HPM_GPTMR3
#define BOARD_UART_TRGM_GPTMR_CLK           clock_gptmr3
#define BOARD_UART_TRGM_GPTMR_CH            2
#define BOARD_UART_TRGM_GPTMR_INPUT         HPM_TRGM0_INPUT_SRC_GPTMR3_OUT2

/* uart lin sample section */
#define BOARD_UART_LIN          HPM_UART3
#define BOARD_UART_LIN_IRQ      IRQn_UART3
#define BOARD_UART_LIN_CLK_NAME clock_uart3
#define BOARD_UART_LIN_TX_PORT  GPIO_DI_GPIOA
#define BOARD_UART_LIN_TX_PIN   (15U) /* PA15 should align with used pin in pinmux configuration */

#if !defined(CONFIG_NDEBUG_CONSOLE) || !CONFIG_NDEBUG_CONSOLE
#ifndef BOARD_CONSOLE_TYPE
#define BOARD_CONSOLE_TYPE CONSOLE_TYPE_UART
#endif

#if BOARD_CONSOLE_TYPE == CONSOLE_TYPE_UART
#ifndef BOARD_CONSOLE_UART_BASE
#define BOARD_CONSOLE_UART_BASE       HPM_UART0
#define BOARD_CONSOLE_UART_CLK_NAME   clock_uart0
#define BOARD_CONSOLE_UART_IRQ        IRQn_UART0
#define BOARD_CONSOLE_UART_TX_DMA_REQ HPM_DMA_SRC_UART0_TX
#define BOARD_CONSOLE_UART_RX_DMA_REQ HPM_DMA_SRC_UART0_RX
#endif
#define BOARD_CONSOLE_UART_BAUDRATE (115200UL)
#endif
#endif

/* usb cdc acm uart section */
#define BOARD_USB_CDC_ACM_UART            BOARD_APP_UART_BASE
#define BOARD_USB_CDC_ACM_UART_CLK_NAME   BOARD_APP_UART_CLK_NAME
#define BOARD_USB_CDC_ACM_UART_TX_DMA_SRC BOARD_APP_UART_TX_DMA_REQ
#define BOARD_USB_CDC_ACM_UART_RX_DMA_SRC BOARD_APP_UART_RX_DMA_REQ

/* rtthread-nano finsh section */
#define BOARD_RT_CONSOLE_BASE        BOARD_CONSOLE_UART_BASE
#define BOARD_RT_CONSOLE_CLK_NAME    BOARD_CONSOLE_UART_CLK_NAME
#define BOARD_RT_CONSOLE_IRQ         BOARD_CONSOLE_UART_IRQ

/* modbus sample section */
#define BOARD_MODBUS_UART_BASE       BOARD_APP_UART_BASE
#define BOARD_MODBUS_UART_CLK_NAME   BOARD_APP_UART_CLK_NAME
#define BOARD_MODBUS_UART_RX_DMA_REQ BOARD_APP_UART_RX_DMA_REQ
#define BOARD_MODBUS_UART_TX_DMA_REQ BOARD_APP_UART_TX_DMA_REQ

/* nor flash section */
#define BOARD_FLASH_BASE_ADDRESS (0x80000000UL) /* Check */
#define BOARD_FLASH_SIZE         (SIZE_1MB)

/* i2c section */
#define BOARD_APP_I2C_BASE     HPM_I2C0
#define BOARD_APP_I2C_IRQ      IRQn_I2C0
#define BOARD_APP_I2C_CLK_NAME clock_i2c0
#define BOARD_APP_I2C_DMA      HPM_HDMA
#define BOARD_APP_I2C_DMAMUX   HPM_DMAMUX
#define BOARD_APP_I2C_DMA_SRC  HPM_DMA_SRC_I2C0

/* gptmr section */
#define BOARD_GPTMR                   HPM_GPTMR0
#define BOARD_GPTMR_IRQ               IRQn_GPTMR0
#define BOARD_GPTMR_CHANNEL           0
#define BOARD_GPTMR_DMA_SRC           HPM_DMA_SRC_GPTMR0_0
#define BOARD_GPTMR_CLK_NAME          clock_gptmr0
#define BOARD_GPTMR_PWM               HPM_GPTMR0
#define BOARD_GPTMR_PWM_CHANNEL       0
#define BOARD_GPTMR_PWM_DMA_SRC       HPM_DMA_SRC_GPTMR0_0
#define BOARD_GPTMR_PWM_CLK_NAME      clock_gptmr0
#define BOARD_GPTMR_PWM_IRQ           IRQn_GPTMR0
#define BOARD_GPTMR_PWM_SYNC          HPM_GPTMR0
#define BOARD_GPTMR_PWM_SYNC_CHANNEL  1
#define BOARD_GPTMR_PWM_SYNC_CLK_NAME clock_gptmr0

/* User LED */
#define BOARD_LED_GPIO_CTRL  HPM_GPIO0
#define BOARD_LED_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_LED_GPIO_PIN   23

#define BOARD_LED_OFF_LEVEL 1
#define BOARD_LED_ON_LEVEL  0

/* 12V Power Enable for lin transceiver */
#define BOARD_SUPPORT_LIN_TRANSCEIVER_CONTROL 1
#define BOARD_12V_EN_GPIO_CTRL                HPM_GPIO0
#define BOARD_12V_EN_GPIO_INDEX               GPIO_DI_GPIOA
#define BOARD_12V_EN_GPIO_PIN                 24
#define BOARD_LIN_TRANSCEIVER_GPIO_CTRL       HPM_GPIO0
#define BOARD_LIN_TRANSCEIVER_GPIO_INDEX      GPIO_DI_GPIOA
#define BOARD_LIN_TRANSCEIVER_GPIO_PIN        13

/* gpiom section */
#define BOARD_APP_GPIOM_BASE            HPM_GPIOM
#define BOARD_APP_GPIOM_USING_CTRL      HPM_FGPIO
#define BOARD_APP_GPIOM_USING_CTRL_NAME gpiom_core0_fast

/* User button */
#define BOARD_APP_GPIO_CTRL  HPM_GPIO0
#define BOARD_APP_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_APP_GPIO_PIN   9
#define BOARD_APP_GPIO_IRQ   IRQn_GPIO0_A
#define BOARD_BUTTON_PRESSED_VALUE 0

/* spi section */
#define BOARD_APP_SPI_BASE              HPM_SPI1
#define BOARD_APP_SPI_CLK_NAME          clock_spi1
#define BOARD_APP_SPI_IRQ               IRQn_SPI1
#define BOARD_APP_SPI_SCLK_FREQ         (20000000UL)
#define BOARD_APP_SPI_ADDR_LEN_IN_BYTES (1U)
#define BOARD_APP_SPI_DATA_LEN_IN_BITS  (8U)
#define BOARD_APP_SPI_RX_DMA            HPM_DMA_SRC_SPI1_RX
#define BOARD_APP_SPI_TX_DMA            HPM_DMA_SRC_SPI1_TX
#define BOARD_SPI_CS_GPIO_CTRL          HPM_GPIO0
#define BOARD_SPI_CS_PIN                IOC_PAD_PA26
#define BOARD_SPI_CS_ACTIVE_LEVEL       (0U)

/* ADC section */
#define BOARD_APP_ADC16_NAME     "ADC0"
#define BOARD_APP_ADC16_BASE     HPM_ADC0
#define BOARD_APP_ADC16_IRQn     IRQn_ADC0
#define BOARD_APP_ADC16_CH_1     (13U)
#define BOARD_APP_ADC16_CLK_NAME (clock_adc0)
#define BOARD_APP_ADC16_CLK_BUS  (clk_adc_src_ahb0)

#define BOARD_APP_ADC16_HW_TRIG_SRC_CLK_NAME clock_mot0
#define BOARD_APP_ADC16_HW_TRIG_SRC          HPM_PWM0
#define BOARD_APP_ADC16_HW_TRGM              HPM_TRGM0
#define BOARD_APP_ADC16_HW_TRGM_IN           HPM_TRGM0_INPUT_SRC_PWM0_CH8REF
#define BOARD_APP_ADC16_HW_TRGM_OUT_SEQ      TRGM_TRGOCFG_ADC0_STRGI
#define BOARD_APP_ADC16_HW_TRGM_OUT_PMT      TRGM_TRGOCFG_ADCX_PTRGI0A

#define BOARD_APP_ADC16_PMT_TRIG_CH ADC16_CONFIG_TRG0A

/* DAC section */
#define BOARD_DAC_BASE           HPM_DAC0
#define BOARD_DAC_IRQn           IRQn_DAC0
#define BOARD_APP_DAC_CLOCK_NAME clock_dac0

/* Flash section */
#define BOARD_APP_XPI_NOR_XPI_BASE     (HPM_XPI0)
#define BOARD_APP_XPI_NOR_CFG_OPT_HDR  (0xfcf90002U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT0 (0x00000006U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT1 (0x00001000U)

/* SDXC section */
#define BOARD_APP_SDCARD_SDXC_BASE   (HPM_SDXC0)
#define BOARD_APP_SDCARD_SUPPORT_1V8 (0)

/* MCAN section */
#define BOARD_APP_CAN_BASE HPM_MCAN3
#define BOARD_APP_CAN_IRQn IRQn_MCAN3

/* CALLBACK TIMER section */
#define BOARD_CALLBACK_TIMER          (HPM_GPTMR3)
#define BOARD_CALLBACK_TIMER_CH       1
#define BOARD_CALLBACK_TIMER_IRQ      IRQn_GPTMR3
#define BOARD_CALLBACK_TIMER_CLK_NAME (clock_gptmr3)

/* APP PWM */
#define BOARD_APP_PWM             HPM_PWM0
#define BOARD_APP_PWM_CLOCK_NAME  clock_mot0
#define BOARD_APP_PWM_OUT1        2
#define BOARD_APP_PWM_OUT2        3
#define BOARD_APP_TRGM            HPM_TRGM0
#define BOARD_APP_PWM_IRQ         IRQn_PWM0
#define BOARD_APP_TRGM_PWM_OUTPUT TRGM_TRGOCFG_PWM0_SYNCI
#define BOARD_APP_TRGM_PWM_INPUT  HPM_TRGM0_INPUT_SRC_PWM0_TRGO_0

/*BLDC pwm*/
/*PWM define*/
#define BOARD_BLDCPWM              HPM_PWM0
#define BOARD_BLDC_UH_PWM_OUTPIN   (6U)
#define BOARD_BLDC_UL_PWM_OUTPIN   (7U)
#define BOARD_BLDC_VH_PWM_OUTPIN   (4U)
#define BOARD_BLDC_VL_PWM_OUTPIN   (5U)
#define BOARD_BLDC_WH_PWM_OUTPIN   (2U)
#define BOARD_BLDC_WL_PWM_OUTPIN   (3U)
#define BOARD_BLDCPWM_TRGM         HPM_TRGM0
#define BOARD_BLDCAPP_PWM_IRQ      IRQn_PWM0
#define BOARD_BLDCPWM_CMP_INDEX_0  (0U)
#define BOARD_BLDCPWM_CMP_INDEX_1  (1U)
#define BOARD_BLDCPWM_CMP_INDEX_2  (2U)
#define BOARD_BLDCPWM_CMP_INDEX_3  (3U)
#define BOARD_BLDCPWM_CMP_INDEX_4  (4U)
#define BOARD_BLDCPWM_CMP_INDEX_5  (5U)
#define BOARD_BLDCPWM_CMP_INDEX_6  (6U)
#define BOARD_BLDCPWM_CMP_INDEX_7  (7U)
#define BOARD_BLDCPWM_CMP_TRIG_CMP (20U)

/*HALL define*/

/*RDC*/
#define BOARD_RDC_BASE            HPM_RDC
#define BOARD_RDC_TRGM            HPM_TRGM0
#define BOARD_RDC_TRG_IN          HPM_TRGM0_INPUT_SRC_RDC_TRGO_0
#define BOARD_RDC_TRG_OUT         TRGM_TRGOCFG_MOT_GPIO0
#define BOARD_RDC_TRG_ADC         TRGM_TRGOCFG_ADCX_PTRGI0A
#define BOARD_RDC_ADC_I_BASE      HPM_ADC0
#define BOARD_RDC_ADC_Q_BASE      HPM_ADC1
#define BOARD_RDC_ADC_I_CHN       (5U)
#define BOARD_RDC_ADC_Q_CHN       (6U)
#define BOARD_RDC_IRQ        IRQn_RDC
#define BOARD_RDC_ADC_TRIG_FLAG   adc16_event_trig_complete
#define BOARD_RDC_ADC_TRG         ADC16_CONFIG_TRG0A

/*QEI*/
#define BOARD_BLDC_QEI_TRGM                      HPM_TRGM0
#define BOARD_BLDC_QEIV2_BASE                    HPM_QEI1
#define BOARD_BLDC_QEIV2_IRQ                     IRQn_QEI1
#define BOARD_BLDC_QEI_MOTOR_PHASE_COUNT_PER_REV (16U)
#define BOARD_BLDC_QEI_CLOCK_SOURCE              clock_mot0
#define BOARD_BLDC_QEI_FOC_PHASE_COUNT_PER_REV   (4000U)

#define BOARD_APP_QEIV2_BASE                  HPM_QEI1
#define BOARD_APP_QEIV2_IRQ                   IRQn_QEI1
#define BOARD_APP_QEI_CLOCK_SOURCE            clock_mot0
#define BOARD_APP_QEI_ADC_COS_BASE            HPM_ADC0
#define BOARD_APP_QEI_ADC_COS_CHN             (4U)
#define BOARD_APP_QEI_ADC_SIN_BASE            HPM_ADC1
#define BOARD_APP_QEI_ADC_SIN_CHN             (5U)
#define BOARD_APP_QEI_ADC_MATRIX_TO_ADC0      trgm_adc_matrix_output_to_qei1_adc0
#define BOARD_APP_QEI_ADC_MATRIX_TO_ADC1      trgm_adc_matrix_output_to_qei1_adc1
#define BOARD_APP_QEI_ADC_MATRIX_FROM_ADC_COS trgm_adc_matrix_in_from_adc0
#define BOARD_APP_QEI_ADC_MATRIX_FROM_ADC_SIN trgm_adc_matrix_in_from_adc1
#define BOARD_APP_QEI_TRG_ADC                 TRGM_TRGOCFG_ADCX_PTRGI0A

/*Timer define*/
#define BOARD_BLDC_TMR_1MS    HPM_GPTMR2
#define BOARD_BLDC_TMR_CH     0
#define BOARD_BLDC_TMR_CMP    0
#define BOARD_BLDC_TMR_IRQ    IRQn_GPTMR2
#define BOARD_BLDC_TMR_CLOCK  clock_gptmr2
#define BOARD_BLDC_TMR_RELOAD (100000U)

/* BLDC PARAM */
#define BOARD_BLDC_BLOCK_SPEED_KP (0.0005f)
#define BOARD_BLDC_BLOCK_SPEED_KI (0.000009f)

#define BOARD_BLDC_SW_FOC_SPEED_LOOP_SPEED_KP (0.0074f)
#define BOARD_BLDC_SW_FOC_SPEED_LOOP_SPEED_KI (0.0001f)
#define BOARD_BLDC_SW_FOC_POSITION_LOOP_SPEED_KP (0.05f)
#define BOARD_BLDC_SW_FOC_POSITION_LOOP_SPEED_KI (0.001f)
#define BOARD_BLDC_SW_FOC_POSITION_KP (154.7f)
#define BOARD_BLDC_SW_FOC_POSITION_KI (0.113f)

#define BOARD_BLDC_HFI_SPEED_LOOP_KP (40.0f)
#define BOARD_BLDC_HFI_SPEED_LOOP_KI (0.015f)
#define BOARD_BLDC_HFI_PLL_KP (10.0f)
#define BOARD_BLDC_HFI_PLL_KI (1.0f)

/*adc*/
#define BOARD_BLDC_ADC_MODULE    (ADCX_MODULE_ADC16)
#define BOARD_BLDC_ADC_U_BASE    HPM_ADC0
#define BOARD_BLDC_ADC_V_BASE    HPM_ADC1
#define BOARD_BLDC_ADC_W_BASE    HPM_ADC1
#define BOARD_BLDC_ADC_TRIG_FLAG adc16_event_trig_complete

#define BOARD_BLDC_ADC_CH_U                   (5U)
#define BOARD_BLDC_ADC_CH_V                   (6U)
#define BOARD_BLDC_ADC_CH_W                   (4U)
#define BOARD_BLDC_ADC_IRQn                   IRQn_ADC0
#define BOARD_BLDC_ADC_PMT_DMA_SIZE_IN_4BYTES (ADC_SOC_PMT_MAX_DMA_BUFF_LEN_IN_4BYTES)
#define BOARD_BLDC_ADC_TRG                    ADC16_CONFIG_TRG0A
#define BOARD_BLDC_ADC_PREEMPT_TRIG_LEN       (1U)
#define BOARD_BLDC_PWM_TRIG_CMP_INDEX         (8U)
#define BOARD_BLDC_TRG_ADC                    TRGM_TRGOCFG_ADCX_PTRGI0A
#define BOARD_BLDC_PWM_TRG_ADC                HPM_TRGM0_INPUT_SRC_PWM0_CH8REF
#define BOARD_BLDC_DMA_MUX_SRC                HPM_DMA_SRC_MOT_0
#define BOARD_BLDC_DMA_CHN                    (0U)
#define BOARD_BLDC_DMA_TRG_DST                TRGM_TRGOCFG_TRGM_DMA0
#define BOARD_BLDC_DMA_TRG_SRC                HPM_TRGM0_DMA_SRC_TRGM0
#define BOARD_BLDC_DMA_TRG_INDEX              TRGM_DMACFG_0
#define BOARD_BLDC_DMA_TRG_CMP_INDEX          (9U)
#define BOARD_BLDC_DMA_TRG_IN                 HPM_TRGM0_INPUT_SRC_PWM0_CH9REF

/* PLB */
#define BOARD_PLB_CLOCK_NAME           clock_mot0

#define BOARD_PLB_COUNTER              HPM_PLB
#define BOARD_PLB_PWM_BASE             HPM_PWM0
#define BOARD_PLB_PWM_CLOCK_NAME       clock_mot0
#define BOARD_PLB_TRGM                 HPM_TRGM0
#define BOARD_PLB_PWM_TRG              (HPM_TRGM0_INPUT_SRC_PWM0_CH8REF)
#define BOARD_PLB_IN_PWM_TRG           (TRGM_TRGOCFG_PLB_IN_00)
#define BOARD_PLB_IN_PWM_PULSE_TRG     (TRGM_TRGOCFG_PLB_IN_02)
#define BOARD_PLB_CLR_SIGNAL_INPUT     (HPM_TRGM0_INPUT_SRC_PLB_OUT16)
#define BOARD_PLB_TO_TRG_IN            (HPM_TRGM0_INPUT_SRC_PLB_OUT00)
#define BOARD_PLB_TRG_OUT              (HPM_TRGM0_OUTPUT_SRC_TRGM0_P2)
#define BOARD_PLB_IO_TRG_SHIFT         (2)
#define BOARD_PLB_PWM_CMP              (8U)
#define BOARD_PLB_PWM_CHN              (8U)
#define BOARD_PLB_CHN                  plb_chn0

#define BOARD_PLB_FILTER_SIG_INPUT_SOURCE  HPM_TRGM0_INPUT_SRC_TRGM0_P4
#define BOARD_PLB_FILTER_SIG_OUTUPT_SOURCE HPM_TRGM0_OUTPUT_SRC_MOT_GPIO2
#define BOARD_PLB_FILTER_IO_TRG_SHIFT      (2)

/* QEO */
#define BOARD_QEO          HPM_QEO0
#define BOARD_QEO_TRGM_POS trgm_pos_matrix_output_to_qeo0

/* moto */
#define BOARD_MOTOR_CLK_NAME clock_mot0

/* SEI */
#define BOARD_SEI      HPM_SEI
#define BOARD_SEI_CTRL SEI_CTRL_1
#define BOARD_SEI_IRQn IRQn_SEI0_1
#define BOARD_SEI_CLOCK_NAME clock_mot0

/* OPAMP */
#define BOARD_APP_OPAMP       HPM_OPAMP0
#define BOARD_APP_OPAMP_CLOCK clock_opa0

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
#define BOARD_FREERTOS_TICK_SRC_PWM_CLK_NAME clock_mot0

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

/* i2s over spi Section*/
#define BOARD_I2S_SPI_CS_GPIO_CTRL  HPM_GPIO0
#define BOARD_I2S_SPI_CS_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_I2S_SPI_CS_GPIO_PIN   11
#define BOARD_I2S_SPI_CS_GPIO_PAD   IOC_PAD_PA11

#define BOARD_GPTMR_I2S_MCLK          HPM_GPTMR0
#define BOARD_GPTMR_I2S_MCLK_CHANNEL  3
#define BOARD_GPTMR_I2S_MCLK_CLK_NAME clock_gptmr0

#define BOARD_GPTMR_I2S_LRCK          HPM_GPTMR0
#define BOARD_GPTMR_I2S_LRCK_CHANNEL  1
#define BOARD_GPTMR_I2S_LRCK_CLK_NAME clock_gptmr0

#define BOARD_GPTMR_I2S_BCLK          HPM_GPTMR0
#define BOARD_GPTMR_I2S_BLCK_CHANNEL  0
#define BOARD_GPTMR_I2S_BLCK_CLK_NAME clock_gptmr0

#define BOARD_GPTMR_I2S_FINSH          HPM_GPTMR0
#define BOARD_GPTMR_I2S_FINSH_IRQ      IRQn_GPTMR0
#define BOARD_GPTMR_I2S_FINSH_CHANNEL  2
#define BOARD_GPTMR_I2S_FINSH_CLK_NAME clock_gptmr0

#define BOARD_APP_CLK_REF_PIN_NAME "P1[15] (PA30)"
#define BOARD_APP_CLK_REF_CLK_NAME clock_ref0
#define BOARD_APP_CLK_REF_SRC_NAME clk_src_pll1_clk1
#define BOARD_APP_PLLCTLV2_TEST_PLL pllctlv2_pll1
#define BOARD_APP_PLLCTLV2_TEST_PLL_CLK pllctlv2_clk1
#define BOARD_APP_PLLCTLV2_TEST_PLL_NAME clk_pll1clk1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

typedef void (*board_timer_cb)(void);

void board_init(void);
void board_init_console(void);
void board_init_gpio_pins(void);
void board_init_led_pins(void);
void board_init_usb(USB_Type *ptr);
void board_led_write(uint8_t state);
void board_led_toggle(void);
void board_init_uart(UART_Type *ptr);
uint32_t board_init_spi_clock(SPI_Type *ptr);
void board_init_spi_pins(SPI_Type *ptr);
uint32_t board_init_adc_clock(void *ptr, bool clk_src_bus);
void board_init_adc16_pins(void);
uint32_t board_init_dac_clock(DAC_Type *ptr, bool clk_src_ahb);
void board_init_acmp_pins(void);
void board_init_acmp_clock(ACMP_Type *ptr);
void board_init_can(MCAN_Type *ptr);
uint32_t board_init_can_clock(MCAN_Type *ptr);
void board_init_rgb_pwm_pins(void);
void board_disable_output_rgb_led(uint8_t color);
void board_enable_output_rgb_led(uint8_t color);
void board_init_dac_pins(DAC_Type *ptr);
void board_write_spi_cs(uint32_t pin, uint8_t state);
void board_init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);

void board_init_usb_dp_dm_pins(void);
void board_init_clock(void);
void board_delay_us(uint32_t us);
void board_delay_ms(uint32_t ms);
void board_timer_create(uint32_t ms, board_timer_cb cb);
void board_ungate_mchtmr_at_lp_mode(void);

uint8_t board_get_led_gpio_off_level(void);
uint8_t board_get_led_pwm_off_level(void);

void board_init_pmp(void);

uint32_t board_init_uart_clock(UART_Type *ptr);
void board_init_sei_pins(SEI_Type *ptr, uint8_t sei_ctrl_idx);

uint32_t board_init_i2c_clock(I2C_Type *ptr);
void board_init_i2c(I2C_Type *ptr);

void board_init_adc_qeiv2_pins(void);

void board_lin_transceiver_control(bool enable);

void board_init_gptmr_channel_pin(GPTMR_Type *ptr, uint32_t channel, bool as_comp);
void board_init_clk_ref_pin(void);
uint32_t board_init_gptmr_clock(GPTMR_Type *ptr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _HPM_BOARD_H */
