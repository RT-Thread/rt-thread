/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_BOARD_H
#define _HPM_BOARD_H
#include <stdio.h>
#include "hpm_common.h"
#include "hpm_clock_drv.h"
#include "hpm_soc.h"
#include "hpm_soc_feature.h"
#include "pinmux.h"
#if !defined(CONFIG_NDEBUG_CONSOLE) || !CONFIG_NDEBUG_CONSOLE
#include "hpm_debug_console.h"
#endif

#define BOARD_NAME          "hpm6e00evk"
#define BOARD_UF2_SIGNATURE (0x0A4D5048UL)
#define BOARD_CPU_FREQ      (600000000UL)

#define SEC_CORE_IMG_START CORE1_ILM_LOCAL_BASE

#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE HPM_CORE0
#endif

/* ACMP desction */
#define BOARD_ACMP             HPM_ACMP0
#define BOARD_ACMP_CHANNEL     ACMP_CHANNEL_CHN1
#define BOARD_ACMP_IRQ         IRQn_ACMP0_1
#define BOARD_ACMP_PLUS_INPUT  ACMP_INPUT_DAC_OUT  /* use internal DAC */
#define BOARD_ACMP_MINUS_INPUT ACMP_INPUT_ANALOG_4 /* align with used pin */

/* uart section */
#ifndef BOARD_APP_UART_BASE
#define BOARD_APP_UART_BASE       HPM_UART1
#define BOARD_APP_UART_IRQ        IRQn_UART1
#define BOARD_APP_UART_BAUDRATE   (115200UL)
#define BOARD_APP_UART_CLK_NAME   clock_uart1
#define BOARD_APP_UART_RX_DMA_REQ HPM_DMA_SRC_UART1_RX
#define BOARD_APP_UART_TX_DMA_REQ HPM_DMA_SRC_UART1_TX
#endif

#define BOARD_APP_UART_BREAK_SIGNAL_PIN   IOC_PAD_PF27

/* uart rx idle demo section */
#define BOARD_UART_IDLE            BOARD_APP_UART_BASE
#define BOARD_UART_IDLE_IRQ        BOARD_APP_UART_IRQ
#define BOARD_UART_IDLE_CLK_NAME   BOARD_APP_UART_CLK_NAME
#define BOARD_UART_IDLE_TX_DMA_SRC BOARD_APP_UART_TX_DMA_REQ
#define BOARD_UART_IDLE_DMA_SRC    BOARD_APP_UART_RX_DMA_REQ

#define BOARD_UART_IDLE_GPTMR          HPM_GPTMR4
#define BOARD_UART_IDLE_GPTMR_CLK_NAME clock_gptmr4
#define BOARD_UART_IDLE_GPTMR_IRQ      IRQn_GPTMR4
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
#define BOARD_ENET_RMII HPM_ENET0
#define BOARD_ENET_RMII_RST_GPIO
#define BOARD_ENET_RMII_RST_GPIO_INDEX
#define BOARD_ENET_RMII_RST_GPIO_PIN
#define BOARD_ENET_RMII             HPM_ENET0
#define BOARD_ENET_RMII_INT_REF_CLK (1U)
#define BOARD_ENET_RMII_PTP_CLOCK   (clock_ptp0)
#define BOARD_ENET_RMII_PPS0_PINOUT (1)

#define BOARD_ENET0_INF             (1U)  /* 0: RMII, 1: RGMII */
#define BOARD_ENET0_INT_REF_CLK     (0U)
#define BOARD_ENET0_PHY_RST_TIME    (30)
#if BOARD_ENET0_INF
#define BOARD_ENET0_TX_DLY          (0U)
#define BOARD_ENET0_RX_DLY          (0U)
#endif
#if __USE_ENET_PTP
#define BOARD_ENET0_PTP_CLOCK       (clock_ptp0)
#endif

/* usb cdc acm uart section */
#define BOARD_USB_CDC_ACM_UART            BOARD_APP_UART_BASE
#define BOARD_USB_CDC_ACM_UART_CLK_NAME   BOARD_APP_UART_CLK_NAME
#define BOARD_USB_CDC_ACM_UART_TX_DMA_SRC BOARD_APP_UART_TX_DMA_REQ
#define BOARD_USB_CDC_ACM_UART_RX_DMA_SRC BOARD_APP_UART_RX_DMA_REQ

/* uart lin sample section */
#define BOARD_UART_LIN          BOARD_APP_UART_BASE
#define BOARD_UART_LIN_IRQ      BOARD_APP_UART_IRQ
#define BOARD_UART_LIN_CLK_NAME BOARD_APP_UART_CLK_NAME
#define BOARD_UART_LIN_TX_PORT  GPIO_DI_GPIOC
#define BOARD_UART_LIN_TX_PIN   (23U) /* PC23 should align with used pin in pinmux configuration */

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
#define BOARD_CONSOLE_UART_BASE       HPM_UART1
#define BOARD_CONSOLE_UART_CLK_NAME   clock_uart1
#define BOARD_CONSOLE_UART_IRQ        IRQn_UART1
#define BOARD_CONSOLE_UART_TX_DMA_REQ HPM_DMA_SRC_UART1_TX
#define BOARD_CONSOLE_UART_RX_DMA_REQ HPM_DMA_SRC_UART1_RX
#endif
#endif
#define BOARD_CONSOLE_UART_BAUDRATE (115200UL)
#endif
#endif

/* rtthread-nano finsh section */
#define BOARD_RT_CONSOLE_BASE        BOARD_CONSOLE_UART_BASE

/* modbus sample section */
#define BOARD_MODBUS_UART_BASE       BOARD_APP_UART_BASE
#define BOARD_MODBUS_UART_CLK_NAME   BOARD_APP_UART_CLK_NAME
#define BOARD_MODBUS_UART_RX_DMA_REQ BOARD_APP_UART_RX_DMA_REQ
#define BOARD_MODBUS_UART_TX_DMA_REQ BOARD_APP_UART_TX_DMA_REQ

/* sdram section */
#define BOARD_SDRAM_ADDRESS            (0x40000000UL)
#define BOARD_SDRAM_SIZE               (32 * SIZE_1MB)
#define BOARD_SDRAM_CS                 FEMC_SDRAM_CS0
#define BOARD_SDRAM_PORT_SIZE          FEMC_SDRAM_PORT_SIZE_16_BITS
#define BOARD_SDRAM_REFRESH_COUNT      (8192UL)
#define BOARD_SDRAM_REFRESH_IN_MS      (64UL)

/* nor flash section */
#define BOARD_FLASH_BASE_ADDRESS (0x80000000UL)
#define BOARD_FLASH_SIZE         (16 * SIZE_1MB)

/* i2c section */
#define BOARD_APP_I2C_BASE     HPM_I2C0
#define BOARD_APP_I2C_IRQ      IRQn_I2C0
#define BOARD_APP_I2C_CLK_NAME clock_i2c0
#define BOARD_APP_I2C_DMA      HPM_HDMA
#define BOARD_APP_I2C_DMAMUX   HPM_DMAMUX
#define BOARD_APP_I2C_DMA_SRC  HPM_DMA_SRC_I2C0

#define BOARD_APP_I2C_DMAMUX_CH  DMAMUX_MUXCFG_HDMA_MUX0
#define BOARD_I2C_GPIO_CTRL      HPM_GPIO0
#define BOARD_I2C_SCL_GPIO_INDEX GPIO_DO_GPIOY
#define BOARD_I2C_SCL_GPIO_PIN   2
#define BOARD_I2C_SDA_GPIO_INDEX GPIO_DO_GPIOY
#define BOARD_I2C_SDA_GPIO_PIN   3

/* i2c for i2s codec section */
#define BOARD_CODEC_I2C_BASE     HPM_I2C1
#define BOARD_CODEC_I2C_CLK_NAME clock_i2c1

/* i2s section */
#define BOARD_APP_I2S_BASE            HPM_I2S0
#define BOARD_APP_I2S_DATA_LINE       (0U)
#define BOARD_APP_I2S_CLK_NAME        clock_i2s0
#define BOARD_APP_AUDIO_CLK_SRC       clock_source_pll2_clk0
#define BOARD_APP_AUDIO_CLK_SRC_NAME  clk_pll2clk0
#define BOARD_APP_I2S_TX_DMA_REQ      HPM_DMA_SRC_I2S0_TX
#define BOARD_APP_I2S_IRQ             IRQn_I2S0
#define BOARD_PDM_SINGLE_CHANNEL_MASK (1U)
#define BOARD_PDM_DUAL_CHANNEL_MASK   (0x11U)

/* dma section */
#define BOARD_APP_XDMA      HPM_XDMA
#define BOARD_APP_HDMA      HPM_HDMA
#define BOARD_APP_XDMA_IRQ  IRQn_XDMA
#define BOARD_APP_HDMA_IRQ  IRQn_HDMA
#define BOARD_APP_DMAMUX    HPM_DMAMUX
#define TEST_DMA_CONTROLLER HPM_HDMA
#define TEST_DMA_IRQ        IRQn_HDMA

/* APP PWM */
#define BOARD_APP_PWM             HPM_PWM1
#define BOARD_APP_PWM_CLOCK_NAME  clock_pwm1
#define BOARD_APP_PWM_OUT1        pwm_channel_0
#define BOARD_APP_PWM_OUT2        pwm_channel_1
#define BOARD_APP_PWM_OUT3        pwm_channel_2
#define BOARD_APP_PWM_OUT4        pwm_channel_3
#define BOARD_APP_PWM_FAULT_PIN     (5)
#define BOARD_APP_TRGM            HPM_TRGM0
#define BOARD_APP_PWM_IRQ         IRQn_PWM1
#define BOARD_APP_TRGM_PWM_OUTPUT HPM_TRGM0_OUTPUT_SRC_PWM1_TRIG_IN0
#define BOARD_APP_TRGM_PWM_INPUT  HPM_TRGM0_INPUT_SRC_PWM1_TRGO_0

/* gptmr section */
#define BOARD_GPTMR                   HPM_GPTMR4
#define BOARD_GPTMR_IRQ               IRQn_GPTMR4
#define BOARD_GPTMR_CHANNEL           0
#define BOARD_GPTMR_DMA_SRC           HPM_DMA_SRC_GPTMR4_0
#define BOARD_GPTMR_CLK_NAME          clock_gptmr4
#define BOARD_GPTMR_PWM               HPM_GPTMR4
#define BOARD_GPTMR_PWM_CHANNEL       0
#define BOARD_GPTMR_PWM_DMA_SRC       HPM_DMA_SRC_GPTMR4_0
#define BOARD_GPTMR_PWM_CLK_NAME      clock_gptmr4
#define BOARD_GPTMR_PWM_IRQ           IRQn_GPTMR4
#define BOARD_GPTMR_PWM_SYNC          HPM_GPTMR0
#define BOARD_GPTMR_PWM_SYNC_CHANNEL  0
#define BOARD_GPTMR_PWM_SYNC_CLK_NAME clock_gptmr0

/* User button */
#define BOARD_APP_GPIO_CTRL  HPM_GPIO0
#define BOARD_APP_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_APP_GPIO_PIN   24
#define BOARD_APP_GPIO_IRQ   IRQn_GPIO0_B

#define BOARD_APP_GPIO_CTRL2  HPM_GPIO0
#define BOARD_APP_GPIO_INDEX2 GPIO_DI_GPIOB
#define BOARD_APP_GPIO_PIN2   25
#define BOARD_APP_GPIO_IRQ2   IRQn_GPIO0_B

/* gpiom section */
#define BOARD_APP_GPIOM_BASE            HPM_GPIOM
#define BOARD_APP_GPIOM_USING_CTRL      HPM_FGPIO
#define BOARD_APP_GPIOM_USING_CTRL_NAME gpiom_core0_fast

/* spi section */
#define BOARD_APP_SPI_BASE              HPM_SPI7
#define BOARD_APP_SPI_CLK_NAME          clock_spi7
#define BOARD_APP_SPI_IRQ               IRQn_SPI7
#define BOARD_APP_SPI_SCLK_FREQ         (20000000UL)
#define BOARD_APP_SPI_ADDR_LEN_IN_BYTES (1U)
#define BOARD_APP_SPI_DATA_LEN_IN_BITS  (8U)
#define BOARD_APP_SPI_RX_DMA            HPM_DMA_SRC_SPI7_RX
#define BOARD_APP_SPI_TX_DMA            HPM_DMA_SRC_SPI7_TX
#define BOARD_SPI_CS_GPIO_CTRL          HPM_GPIO0
#define BOARD_SPI_CS_PIN                IOC_PAD_PF27
#define BOARD_SPI_CS_ACTIVE_LEVEL       (0U)

/* Flash section */
#define BOARD_APP_XPI_NOR_XPI_BASE     (HPM_XPI0)
#define BOARD_APP_XPI_NOR_CFG_OPT_HDR  (0xfcf90001U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT0 (0x00000005U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT1 (0x00001000U)

/* ADC section */
#define BOARD_APP_ADC16_NAME     "ADC0"
#define BOARD_APP_ADC16_BASE     HPM_ADC0
#define BOARD_APP_ADC16_IRQn     IRQn_ADC0
#define BOARD_APP_ADC16_CH_1     (15U)
#define BOARD_APP_ADC16_CLK_NAME (clock_adc0)

#define BOARD_APP_ADC16_HW_TRIG_SRC_CLK_NAME clock_pwm0
#define BOARD_APP_ADC16_HW_TRIG_SRC          HPM_PWM0
#define BOARD_APP_ADC16_HW_TRGM              HPM_TRGM0
#define BOARD_APP_ADC16_HW_TRGM_IN           HPM_TRGM0_INPUT_SRC_PWM0_TRGO_0
#define BOARD_APP_ADC16_HW_TRGM_OUT_SEQ      TRGM_TRGOCFG_ADC0_STRGI
#define BOARD_APP_ADC16_HW_TRGM_OUT_PMT      TRGM_TRGOCFG_ADCX_PTRGI0A
#define BOARD_APP_ADC16_PMT_TRIG_CH          ADC16_CONFIG_TRG0A

/* CAN section */
#define BOARD_APP_CAN_BASE HPM_MCAN4
#define BOARD_APP_CAN_IRQn IRQn_MCAN4

/*
 * timer for board delay
 */
#define BOARD_DELAY_TIMER          (HPM_GPTMR3)
#define BOARD_DELAY_TIMER_CH       0
#define BOARD_DELAY_TIMER_CLK_NAME (clock_gptmr3)

#define BOARD_CALLBACK_TIMER          (HPM_GPTMR3)
#define BOARD_CALLBACK_TIMER_CH       1
#define BOARD_CALLBACK_TIMER_IRQ      IRQn_GPTMR3
#define BOARD_CALLBACK_TIMER_CLK_NAME (clock_gptmr3)

/* USB section */
#define BOARD_USB HPM_USB0

/* LED */
#define BOARD_R_GPIO_CTRL  HPM_GPIO0
#define BOARD_R_GPIO_INDEX GPIO_DI_GPIOE
#define BOARD_R_GPIO_PIN   14
#define BOARD_G_GPIO_CTRL  HPM_GPIO0
#define BOARD_G_GPIO_INDEX GPIO_DI_GPIOE
#define BOARD_G_GPIO_PIN   15
#define BOARD_B_GPIO_CTRL  HPM_GPIO0
#define BOARD_B_GPIO_INDEX GPIO_DI_GPIOE
#define BOARD_B_GPIO_PIN   4

#define BOARD_LED_GPIO_CTRL  HPM_GPIO0
#define BOARD_LED_GPIO_INDEX GPIO_DI_GPIOE
#define BOARD_LED_GPIO_PIN   15
#define BOARD_LED_OFF_LEVEL  0
#define BOARD_LED_ON_LEVEL   1

#define BOARD_LED_TOGGLE_RGB 1

/* RGB LED Section */
#define BOARD_RED_PWM_IRQ              IRQn_PWM1
#define BOARD_RED_PWM                  HPM_PWM1
#define BOARD_RED_PWM_OUT_CH           6
#define BOARD_RED_PWM_SHADOW_ID        1
#define BOARD_RED_PWM_CMP_ID           6
#define BOARD_RED_PWM_COUNTER_INDEX    2
#define BOARD_RED_PWM_CMP_INITIAL_ZERO true
#define BOARD_RED_PWM_CLOCK_NAME       clock_mot1

#define BOARD_GREEN_PWM_IRQ              IRQn_PWM1
#define BOARD_GREEN_PWM                  HPM_PWM1
#define BOARD_GREEN_PWM_OUT_CH           7
#define BOARD_GREEN_PWM_SHADOW_ID        2
#define BOARD_GREEN_PWM_CMP_ID           7
#define BOARD_GREEN_PWM_COUNTER_INDEX    2
#define BOARD_GREEN_PWM_CMP_INITIAL_ZERO true
#define BOARD_GREEN_PWM_CLOCK_NAME       clock_mot1

#define BOARD_BLUE_PWM_IRQ              IRQn_PWM0
#define BOARD_BLUE_PWM                  HPM_PWM0
#define BOARD_BLUE_PWM_OUT_CH           4
#define BOARD_BLUE_PWM_SHADOW_ID        3
#define BOARD_BLUE_PWM_CMP_ID           4
#define BOARD_BLUE_PWM_COUNTER_INDEX    1
#define BOARD_BLUE_PWM_CMP_INITIAL_ZERO true
#define BOARD_BLUE_PWM_CLOCK_NAME       clock_mot0

#define BOARD_RGB_RED   0
#define BOARD_RGB_GREEN (BOARD_RGB_RED + 1)
#define BOARD_RGB_BLUE  (BOARD_RGB_RED + 2)

/* pdma section */
#define BOARD_PDMA_BASE HPM_PDMA

#ifndef BOARD_SHOW_CLOCK
#define BOARD_SHOW_CLOCK 1
#endif
#ifndef BOARD_SHOW_BANNER
#define BOARD_SHOW_BANNER 1
#endif

/* enet section */
#define BOARD_ENET_RGMII_RST_GPIO       HPM_GPIO0
#define BOARD_ENET_RGMII_RST_GPIO_INDEX GPIO_DO_GPIOA
#define BOARD_ENET_RGMII_RST_GPIO_PIN   (14U)

#define BOARD_ENET_RGMII        HPM_ENET0
#define BOARD_ENET_RGMII_TX_DLY (0U)
#define BOARD_ENET_RGMII_RX_DLY (0U)

#define BOARD_ENET_RGMII_PTP_CLOCK (clock_ptp0)

/* TSW section */
#define BOARD_TSW HPM_TSW

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

#define BOARD_BLDC_TMR_1MS    HPM_GPTMR2
#define BOARD_BLDC_TMR_CH     0
#define BOARD_BLDC_TMR_CMP    0
#define BOARD_BLDC_TMR_IRQ    IRQn_GPTMR2
#define BOARD_BLDC_TMR_RELOAD (100000U)

/* BLDC ADC */
#define BOARD_BLDC_ADC_MODULE    ADCX_MODULE_ADC16
#define BOARD_BLDC_ADC_U_BASE                 HPM_ADC0
#define BOARD_BLDC_ADC_V_BASE                 HPM_ADC1
#define BOARD_BLDC_ADC_W_BASE                 HPM_ADC2
#define BOARD_BLDC_ADC_TRIG_FLAG adc16_event_trig_complete

#define BOARD_BLDC_ADC_CH_U                   (14U)
#define BOARD_BLDC_ADC_CH_V                   (10U)
#define BOARD_BLDC_ADC_CH_W                   (11U)
#define BOARD_BLDC_ADC_IRQn                   IRQn_ADC0
#define BOARD_BLDC_ADC_PMT_DMA_SIZE_IN_4BYTES (ADC_SOC_PMT_MAX_DMA_BUFF_LEN_IN_4BYTES)
#define BOARD_BLDC_ADC_TRG                    ADC16_CONFIG_TRG0A
#define BOARD_BLDC_ADC_PREEMPT_TRIG_LEN       (1U)
#define BOARD_BLDC_TRG_NUM                    TRGM_TRGOCFG_ADCX_PTRGI0A
#define BOARD_BLDC_PWM_TRIG_OUT_CHN           (0U)

/* BLDC TRGM */
#define BOARD_BLDC_TRIGMUX_IN_NUM      HPM_TRGM0_INPUT_SRC_PWM1_TRGO_0
#define BOARD_BLDC_TRIGMUX_OUT_NUM_ADC HPM_TRGM0_OUTPUT_SRC_ADCX_PTRGI0A
#define BOARD_BLDC_TRIGMUX_OUT_NUM_VSC HPM_TRGM0_OUTPUT_SRC_VSC0_TRIG_IN0

#define BOARD_BLDC_TRGM_ADC_MATRIX_TO_VSC_ADC0 trgm_adc_matrix_output_to_vsc0_adc0
#define BOARD_BLDC_TRGM_ADC_MATRIX_TO_VSC_ADC1 trgm_adc_matrix_output_to_vsc0_adc1
#define BOARD_BLDC_TRGM_ADC_MATRIX_TO_VSC_ADC2 trgm_adc_matrix_output_to_vsc0_adc2
#define BOARD_BLDC_TRGM_ADC_MATRIX_FROM_ADC_U  trgm_adc_matrix_in_from_adc0
#define BOARD_BLDC_TRGM_ADC_MATRIX_FROM_ADC_V  trgm_adc_matrix_in_from_adc1
#define BOARD_BLDC_TRGM_ADC_MATRIX_FROM_ADC_W  trgm_adc_matrix_in_from_adc2

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

#define BOARD_BLDC_TRGM_POS_MATRIX_TO_VSC   trgm_pos_matrix_output_to_vsc0
#define BOARD_BLDC_TRGM_POS_MATRIX_TO_QEO   trgm_pos_matrix_output_to_qeo0
#define BOARD_BLDC_TRGM_POS_MATRIX_FROM_QEI trgm_pos_matrix_in_from_qei0

/* BLDC TIMER */
#define BOARD_BLDC_TMR_BASE      HPM_GPTMR2
#define BOARD_BLDC_TMR_CH        0
#define BOARD_BLDC_TMR_IRQ       IRQn_GPTMR2
#define BOARD_BLDC_TMR_CLOCK     clock_gptmr2
#define BOARD_BLDC_TMR_PERIOD_MS (1u)

/* HALL */

/* RDC */
#define BOARD_RDC_BASE            HPM_RDC0
#define BOARD_RDC_TRGM            HPM_TRGM0
#define BOARD_RDC_TRGIGMUX_IN_NUM HPM_TRGM0_INPUT_SRC_RDC0_TRGO_0
#define BOARD_RDC_TRG_NUM         TRGM_TRGOCFG_MOT_GPIO0
#define BOARD_RDC_TRG_ADC_NUM     HPM_TRGM0_OUTPUT_SRC_ADCX_PTRGI0A
#define BOARD_RDC_ADC_I_BASE      HPM_ADC0
#define BOARD_RDC_ADC_Q_BASE      HPM_ADC1
#define BOARD_RDC_ADC_I_CHN       (14U)
#define BOARD_RDC_ADC_Q_CHN       (10U)
#define BOARD_RDC_ADC_IRQn        IRQn_ADC0
#define BOARD_RDC_ADC_TRIG_FLAG   adc16_event_trig_complete
#define BOARD_RDC_ADC_TRG         ADC16_CONFIG_TRG0A
#define BOARD_APP_RDC_ADC_MATRIX_TO_ADC0      trgm_adc_matrix_output_to_rdc0_adc0
#define BOARD_APP_RDC_ADC_MATRIX_TO_ADC1      trgm_adc_matrix_output_to_rdc0_adc1
#define BOARD_APP_RDC_ADC_MATRIX_FROM_ADC_I trgm_adc_matrix_in_from_adc0
#define BOARD_APP_RDC_ADC_MATRIX_FROM_ADC_Q trgm_adc_matrix_in_from_adc1

/* QEIV2 */
#define BOARD_BLDC_QEI_TRGM                      HPM_TRGM0
#define BOARD_BLDC_QEIV2_BASE                    HPM_QEI0
#define BOARD_BLDC_QEIV2_IRQ                     IRQn_QEI0
#define BOARD_BLDC_QEI_MOTOR_PHASE_COUNT_PER_REV (16U)
#define BOARD_BLDC_QEI_CLOCK_SOURCE              clock_qei0
#define BOARD_BLDC_QEI_FOC_PHASE_COUNT_PER_REV   (4000U)

#define BOARD_APP_QEIV2_BASE                  HPM_QEI3
#define BOARD_APP_QEIV2_IRQ                   IRQn_QEI3
#define BOARD_APP_QEI_CLOCK_SOURCE            clock_qei3
#define BOARD_APP_QEI_ADC_COS_BASE            HPM_ADC2
#define BOARD_APP_QEI_ADC_COS_CHN             (11U)
#define BOARD_APP_QEI_ADC_SIN_BASE            HPM_ADC0
#define BOARD_APP_QEI_ADC_SIN_CHN             (14U)
#define BOARD_APP_QEI_ADC_MATRIX_TO_ADC0      trgm_adc_matrix_output_to_qei3_adc0
#define BOARD_APP_QEI_ADC_MATRIX_TO_ADC1      trgm_adc_matrix_output_to_qei3_adc1
#define BOARD_APP_QEI_ADC_MATRIX_FROM_ADC_COS trgm_adc_matrix_in_from_adc2
#define BOARD_APP_QEI_ADC_MATRIX_FROM_ADC_SIN trgm_adc_matrix_in_from_adc0

/* PLB */
#define BOARD_PLB_COUNTER              HPM_PLB
#define BOARD_PLB_PWM_BASE             HPM_PWM0
#define BOARD_PLB_PWM_CLOCK_NAME       clock_mot0
#define BOARD_PLB_TRGM                 HPM_TRGM0
#define BOARD_PLB_PWM_TRG              (HPM_TRGM0_INPUT_SRC_PWM0_TRGO_0)
#define BOARD_PLB_IN_PWM_TRG_NUM       (TRGM_TRGOCFG_PLB_IN_00)
#define BOARD_PLB_IN_PWM_PULSE_TRG_NUM (TRGM_TRGOCFG_PLB_IN_02)
#define BOARD_PLB_CLR_SIGNAL_INPUT     (HPM_TRGM0_INPUT_SRC_PLB_OUT32)
#define BOARD_PLB_TYPEB_INPUT0         (TRGM_TRGOCFG_PLB_IN_32)
#define BOARD_PLB_OUT_TRG              (HPM_TRGM0_INPUT_SRC_PLB_OUT00)
#define BOARD_PLB_IO_TRG_NUM           (TRGM_TRGOCFG_MOT_GPIO5)
#define BOARD_PLB_IO_TRG_SHIFT         (5)
#define BOARD_PLB_PWM_CMP              (8U)
#define BOARD_PLB_PWM_CHN              (8U)
#define BOARD_PLB_CHN                  plb_chn0

/* QEO */
#define BOARD_QEO          HPM_QEO0
#define BOARD_QEO_TRGM_POS trgm_pos_matrix_output_to_qeo0

#define BOARD_QEO_PWM           HPM_QEO1  /*QEO instance should align with PWM instance, such as QEO1 -> PWM1 */
#define BOARD_QEO_TRGM_POS_PWM  trgm_pos_matrix_output_to_qeo1

/* SEI */
#define BOARD_SEI      HPM_SEI
#define BOARD_SEI_CTRL SEI_CTRL_1
#define BOARD_SEI_IRQn IRQn_SEI_1
#define BOARD_TRGM_POS_SOURCE_SEI trgm_pos_matrix_in_from_sei_pos1

/* MTG */
#define BOARD_TRGM_POS_DEST_MTG trgm_pos_matrix_output_to_mtg0

/* VSC */
#define BOARD_VSC                     HPM_VSC0
#define BOARD_VSC_IRQn                IRQn_VSC0

/* CLC */
#define BOARD_CLC      HPM_CLC0
#define BOARD_CLC_IRQn IRQn_CLC0_0

/* Tamper Section */
#define BOARD_TAMP_ACTIVE_CH    4
#define BOARD_TAMP_LOW_LEVEL_CH 3

/* sdm section */
#define BOARD_SDM                 HPM_SDM0
#define BOARD_SDM_IRQ             IRQn_SDM0
#define BOARD_SDM_CHANNEL         0
#define BOARD_SDM_TRGM            HPM_TRGM0
#define BOARD_SDM_TRGM_GPTMR      HPM_GPTMR3
#define BOARD_SDM_TRGM_GPTMR_CH   2
#define BOARD_SDM_TRGM_INPUT_SRC  HPM_TRGM0_INPUT_SRC_GPTMR3_OUT2
#define BOARD_SDM_TRGM_OUTPUT_DST HPM_TRGM0_OUTPUT_SRC_SDM_PWM_SOC15
#define BOARD_SDM_TRGM_SYNC_SRC   (15)
/* need to provide clock to sdm sensor */
#define BOARD_SDM_SENSOR_REQUIRE_CLK true
#define BOARD_SDM_CLK_PWM            HPM_PWM2
#define BOARD_SDM_CLK_PWM_CLK_NAME   clock_pwm2
#define BOARD_SDM_CLK_PWM_OUT        (3)



/* EtherCAT definitions */
/* ECAT PORT0 must support */
#define BOARD_ECAT_SUPPORT_PORT1       (1)
#define BOARD_ECAT_SUPPORT_PORT2       (0)

#define BOARD_ECAT_PHY0_RESET_GPIO              HPM_GPIO0
#define BOARD_ECAT_PHY0_RESET_GPIO_PORT_INDEX   GPIO_DO_GPIOA
#define BOARD_ECAT_PHY0_RESET_PIN_INDEX         (10)

#define BOARD_ECAT_PHY1_RESET_GPIO              HPM_GPIO0
#define BOARD_ECAT_PHY1_RESET_GPIO_PORT_INDEX   GPIO_DO_GPIOA
#define BOARD_ECAT_PHY1_RESET_PIN_INDEX         (10)
#define BOARD_ECAT_PHY_RESET_LEVEL              (0)

#define BOARD_ECAT_IN1_GPIO            HPM_GPIO0
#define BOARD_ECAT_IN1_GPIO_PORT_INDEX GPIO_DO_GPIOC
#define BOARD_ECAT_IN1_GPIO_PIN_INDEX  (31U)

#define BOARD_ECAT_IN2_GPIO            HPM_GPIO0
#define BOARD_ECAT_IN2_GPIO_PORT_INDEX GPIO_DO_GPIOD
#define BOARD_ECAT_IN2_GPIO_PIN_INDEX  (9U)

#define BOARD_ECAT_OUT1_GPIO            HPM_GPIO0
#define BOARD_ECAT_OUT1_GPIO_PORT_INDEX GPIO_DO_GPIOD
#define BOARD_ECAT_OUT1_GPIO_PIN_INDEX  (8U)

#define BOARD_ECAT_OUT2_GPIO            BOARD_R_GPIO_CTRL /* reuse RGB red led */
#define BOARD_ECAT_OUT2_GPIO_PORT_INDEX BOARD_R_GPIO_INDEX
#define BOARD_ECAT_OUT2_GPIO_PIN_INDEX  BOARD_R_GPIO_PIN

#define BOARD_ECAT_OUT_ON_LEVEL         (1) /* ECAT control LED on level */

#define BOARD_ECAT_NMII_LINK0_CTRL_INDEX 3
#define BOARD_ECAT_NMII_LINK1_CTRL_INDEX 0
#define BOARD_ECAT_LED_RUN_CTRL_INDEX    1
#define BOARD_ECAT_LED_ERROR_CTRL_INDEX  6

#ifndef BOARD_SHOW_CLOCK
#define BOARD_SHOW_CLOCK 1
#endif
#ifndef BOARD_SHOW_BANNER
#define BOARD_SHOW_BANNER 1
#endif

/* FreeRTOS Definitions */
#define BOARD_FREERTOS_TIMER          HPM_GPTMR6
#define BOARD_FREERTOS_TIMER_CHANNEL  1
#define BOARD_FREERTOS_TIMER_IRQ      IRQn_GPTMR6
#define BOARD_FREERTOS_TIMER_CLK_NAME clock_gptmr6

#define BOARD_FREERTOS_LOWPOWER_TIMER          HPM_PTMR
#define BOARD_FREERTOS_LOWPOWER_TIMER_CHANNEL  1
#define BOARD_FREERTOS_LOWPOWER_TIMER_IRQ      IRQn_PTMR
#define BOARD_FREERTOS_LOWPOWER_TIMER_CLK_NAME clock_ptmr
/* Threadx Definitions */
#define BOARD_THREADX_TIMER           HPM_GPTMR6
#define BOARD_THREADX_TIMER_CHANNEL   1
#define BOARD_THREADX_TIMER_IRQ       IRQn_GPTMR6
#define BOARD_THREADX_TIMER_CLK_NAME  clock_gptmr6

#define BOARD_THREADX_LOWPOWER_TIMER           HPM_PTMR
#define BOARD_THREADX_LOWPOWER_TIMER_CHANNEL   1
#define BOARD_THREADX_LOWPOWER_TIMER_IRQ       IRQn_PTMR
#define BOARD_THREADX_LOWPOWER_TIMER_CLK_NAME  clock_ptmr

/* LOBS */
#define BOARD_LOBS_TRIG_GROUP     5       /* group5 <--> PF */
#define BOARD_LOBS_TRIG_PIN       26

/* i2s over spi Section*/
#define BOARD_I2S_SPI_CS_GPIO_CTRL         HPM_GPIO0
#define BOARD_I2S_SPI_CS_GPIO_INDEX        GPIO_DI_GPIOE
#define BOARD_I2S_SPI_CS_GPIO_PIN          6
#define BOARD_I2S_SPI_CS_GPIO_PAD          IOC_PAD_PA06

#define BOARD_GPTMR_I2S_MCLK               HPM_GPTMR5
#define BOARD_GPTMR_I2S_MCLK_CHANNEL       2
#define BOARD_GPTMR_I2S_MCLK_CLK_NAME      clock_gptmr5

#define BOARD_GPTMR_I2S_LRCK               HPM_GPTMR4
#define BOARD_GPTMR_I2S_LRCK_CHANNEL       0
#define BOARD_GPTMR_I2S_LRCK_CLK_NAME      clock_gptmr4

#define BOARD_GPTMR_I2S_BCLK               HPM_GPTMR0
#define BOARD_GPTMR_I2S_BLCK_CHANNEL       0
#define BOARD_GPTMR_I2S_BLCK_CLK_NAME      clock_gptmr0

#define BOARD_GPTMR_I2S_FINSH              HPM_GPTMR0
#define BOARD_GPTMR_I2S_FINSH_IRQ          IRQn_GPTMR0
#define BOARD_GPTMR_I2S_FINSH_CHANNEL      1
#define BOARD_GPTMR_I2S_FINSH_CLK_NAME     clock_gptmr0

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

typedef void (*board_timer_cb)(void);

void board_init(void);
void board_init_console(void);
void board_init_core1(void);
void board_init_uart(UART_Type *ptr);
void board_init_i2c(I2C_Type *ptr);
void board_init_can(MCAN_Type *ptr);
void board_init_sdram_pins(void);
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
uint32_t board_init_adc16_clock(void *ptr, bool clk_src_ahb);
void board_init_i2s_pins(I2S_Type *ptr);
uint32_t board_config_i2s_clock(I2S_Type *ptr, uint32_t sample_rate);
uint32_t board_init_pdm_clock(void);
uint32_t board_init_dao_clock(void);
void board_init_dao_pins(void);
void board_init_adc16_pins(void);
void board_init_usb_pins(void);
void board_usb_vbus_ctrl(uint8_t usb_index, uint8_t level);
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
void board_init_ethercat(ESC_Type *ptr);
void board_init_switch_led(void);
void board_init_tsw(TSW_Type *ptr);
void board_init_sei_pins(SEI_Type *ptr, uint8_t sei_ctrl_idx);
void board_init_adc_qeiv2_pins(void);

uint32_t board_init_gptmr_clock(GPTMR_Type *ptr);
uint32_t board_init_pwm_clock(PWMV2_Type *ptr);
#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _HPM_BOARD_H */
