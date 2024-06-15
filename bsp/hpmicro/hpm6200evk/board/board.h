/*
 * Copyright (c) 2023 HPMicro
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

#define BOARD_NAME          "hpm6200evk"
#define BOARD_UF2_SIGNATURE (0x0A4D5048UL)

#define SEC_CORE_IMG_START CORE1_ILM_LOCAL_BASE

/* dma section */
#define BOARD_APP_XDMA     HPM_XDMA
#define BOARD_APP_HDMA     HPM_HDMA
#define BOARD_APP_XDMA_IRQ IRQn_XDMA
#define BOARD_APP_HDMA_IRQ IRQn_HDMA
#define BOARD_APP_DMAMUX   HPM_DMAMUX

#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE HPM_CORE0
#endif

/* uart section */
#ifndef BOARD_APP_UART_BASE
#define BOARD_APP_UART_BASE HPM_UART2
#define BOARD_APP_UART_IRQ  IRQn_UART2
#define BOARD_APP_UART_BAUDRATE   (115200UL)
#define BOARD_APP_UART_CLK_NAME   clock_uart2
#define BOARD_APP_UART_RX_DMA_REQ HPM_DMA_SRC_UART2_RX
#define BOARD_APP_UART_TX_DMA_REQ HPM_DMA_SRC_UART2_TX
#endif

/* uart lin sample section */
#define BOARD_UART_LIN          BOARD_APP_UART_BASE
#define BOARD_UART_LIN_IRQ      BOARD_APP_UART_IRQ
#define BOARD_UART_LIN_CLK_NAME BOARD_APP_UART_CLK_NAME
#define BOARD_UART_LIN_TX_PORT  GPIO_DI_GPIOC
#define BOARD_UART_LIN_TX_PIN   (26U) /* PC26 should align with used pin in pinmux configuration */


#if !defined(CONFIG_NDEBUG_CONSOLE) || !CONFIG_NDEBUG_CONSOLE
#ifndef BOARD_CONSOLE_TYPE
#define BOARD_CONSOLE_TYPE CONSOLE_TYPE_UART
#endif

#if BOARD_CONSOLE_TYPE == CONSOLE_TYPE_UART
#ifndef BOARD_CONSOLE_UART_BASE
#if BOARD_RUNNING_CORE == HPM_CORE0
#define BOARD_CONSOLE_UART_BASE     HPM_UART0
#define BOARD_CONSOLE_UART_CLK_NAME clock_uart0
#define BOARD_CONSOLE_UART_IRQ      IRQn_UART0
#define BOARD_CONSOLE_UART_TX_DMA_REQ HPM_DMA_SRC_UART0_TX
#define BOARD_CONSOLE_UART_RX_DMA_REQ HPM_DMA_SRC_UART0_RX
#else
#define BOARD_CONSOLE_UART_BASE     HPM_UART2
#define BOARD_CONSOLE_UART_CLK_NAME clock_uart2
#define BOARD_CONSOLE_UART_IRQ      IRQn_UART2
#define BOARD_CONSOLE_UART_TX_DMA_REQ HPM_DMA_SRC_UART2_TX
#define BOARD_CONSOLE_UART_RX_DMA_REQ HPM_DMA_SRC_UART2_RX
#endif
#endif
#define BOARD_CONSOLE_UART_BAUDRATE (115200UL)
#endif
#endif

/* uart microros sample section */
#define BOARD_MICROROS_UART_BASE     BOARD_APP_UART_BASE
#define BOARD_MICROROS_UART_IRQ      BOARD_APP_UART_IRQ
#define BOARD_MICROROS_UART_CLK_NAME BOARD_APP_UART_CLK_NAME

/* rtthread-nano finsh section */
#define BOARD_RT_CONSOLE_BASE        BOARD_CONSOLE_UART_BASE

/* usb cdc acm uart section */
#define BOARD_USB_CDC_ACM_UART            BOARD_APP_UART_BASE
#define BOARD_USB_CDC_ACM_UART_CLK_NAME   BOARD_APP_UART_CLK_NAME
#define BOARD_USB_CDC_ACM_UART_TX_DMA_SRC BOARD_APP_UART_TX_DMA_REQ
#define BOARD_USB_CDC_ACM_UART_RX_DMA_SRC BOARD_APP_UART_RX_DMA_REQ

/* modbus sample section */
#define BOARD_MODBUS_UART_BASE       BOARD_APP_UART_BASE
#define BOARD_MODBUS_UART_CLK_NAME   BOARD_APP_UART_CLK_NAME
#define BOARD_MODBUS_UART_RX_DMA_REQ BOARD_APP_UART_RX_DMA_REQ
#define BOARD_MODBUS_UART_TX_DMA_REQ BOARD_APP_UART_TX_DMA_REQ

/* sdm section */
#define BOARD_SDM                 HPM_SDM
#define BOARD_SDM_IRQ             IRQn_SDFM
#define BOARD_SDM_CHANNEL         3
#define BOARD_SDM_TRGM            HPM_TRGM3
#define BOARD_SDM_TRGM_GPTMR      HPM_GPTMR3
#define BOARD_SDM_TRGM_GPTMR_CH   2
#define BOARD_SDM_TRGM_INPUT_SRC  HPM_TRGM3_INPUT_SRC_GPTMR3_OUT2
#define BOARD_SDM_TRGM_OUTPUT_DST HPM_TRGM3_OUTPUT_SRC_SDFM_TRG15

/* lin section */
#define BOARD_LIN          HPM_LIN0
#define BOARD_LIN_CLK_NAME clock_lin0
#define BOARD_LIN_IRQ      IRQn_LIN0
#define BOARD_LIN_BAUDRATE (19200U)

/* nor flash section */
#define BOARD_FLASH_BASE_ADDRESS (0x80000000UL)
#define BOARD_FLASH_SIZE         (16 * SIZE_1MB)

/* i2c section */
#define BOARD_APP_I2C_BASE       HPM_I2C3
#define BOARD_APP_I2C_IRQ        IRQn_I2C3
#define BOARD_APP_I2C_CLK_NAME   clock_i2c3
#define BOARD_APP_I2C_DMA        HPM_HDMA
#define BOARD_APP_I2C_DMAMUX     HPM_DMAMUX
#define BOARD_APP_I2C_DMA_SRC    HPM_DMA_SRC_I2C3
#define BOARD_APP_I2C_DMAMUX_CH  DMAMUX_MUXCFG_HDMA_MUX0
#define BOARD_I2C_GPIO_CTRL      HPM_GPIO0
#define BOARD_I2C_SCL_GPIO_INDEX GPIO_DO_GPIOB
#define BOARD_I2C_SCL_GPIO_PIN   20
#define BOARD_I2C_SDA_GPIO_INDEX GPIO_DO_GPIOB
#define BOARD_I2C_SDA_GPIO_PIN   21

/* ACMP desction */
#define BOARD_ACMP             HPM_ACMP
#define BOARD_ACMP_CHANNEL     ACMP_CHANNEL_CHN1
#define BOARD_ACMP_IRQ         IRQn_ACMP_1
#define BOARD_ACMP_PLUS_INPUT  ACMP_INPUT_DAC_OUT  /* use internal DAC */
#define BOARD_ACMP_MINUS_INPUT ACMP_INPUT_ANALOG_5 /* align with used pin */

/* dma section */
#define BOARD_APP_XDMA     HPM_XDMA
#define BOARD_APP_HDMA     HPM_HDMA
#define BOARD_APP_XDMA_IRQ IRQn_XDMA
#define BOARD_APP_HDMA_IRQ IRQn_HDMA
#define BOARD_APP_DMAMUX   HPM_DMAMUX

/* gptmr section */
#define BOARD_GPTMR                   HPM_GPTMR1
#define BOARD_GPTMR_IRQ               IRQn_GPTMR1
#define BOARD_GPTMR_CHANNEL           0
#define BOARD_GPTMR_DMA_SRC           HPM_DMA_SRC_GPTMR1_0
#define BOARD_GPTMR_CLK_NAME          clock_gptmr1
#define BOARD_GPTMR_PWM               HPM_GPTMR1
#define BOARD_GPTMR_PWM_CHANNEL       0
#define BOARD_GPTMR_PWM_DMA_SRC       HPM_DMA_SRC_GPTMR1_0
#define BOARD_GPTMR_PWM_CLK_NAME      clock_gptmr1
#define BOARD_GPTMR_PWM_IRQ           IRQn_GPTMR1
#define BOARD_GPTMR_PWM_SYNC          HPM_GPTMR1
#define BOARD_GPTMR_PWM_SYNC_CHANNEL  1
#define BOARD_GPTMR_PWM_SYNC_CLK_NAME clock_gptmr1

/* pinmux section */
#define USING_GPIO0_FOR_GPIOZ
#ifndef USING_GPIO0_FOR_GPIOZ
#define BOARD_APP_GPIO_CTRL HPM_BGPIO
#define BOARD_APP_GPIO_IRQ  IRQn_BGPIO
#else
#define BOARD_APP_GPIO_CTRL HPM_GPIO0
#define BOARD_APP_GPIO_IRQ  IRQn_GPIO0_Z
#endif

/* gpiom section */
#define BOARD_APP_GPIOM_BASE            HPM_GPIOM
#define BOARD_APP_GPIOM_USING_CTRL      HPM_FGPIO
#define BOARD_APP_GPIOM_USING_CTRL_NAME gpiom_core0_fast

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
#define BOARD_SPI_CS_PIN                IOC_PAD_PB02
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
#define BOARD_APP_ADC16_CH_1     (8U)
#define BOARD_APP_ADC16_CLK_NAME (clock_adc0)

#define BOARD_APP_ADC16_HW_TRIG_SRC     HPM_PWM0
#define BOARD_APP_ADC16_HW_TRGM         HPM_TRGM0
#define BOARD_APP_ADC16_HW_TRGM_IN      HPM_TRGM0_INPUT_SRC_PWM0_CH8REF
#define BOARD_APP_ADC16_HW_TRGM_OUT_SEQ TRGM_TRGOCFG_ADC0_STRGI
#define BOARD_APP_ADC16_HW_TRGM_OUT_PMT TRGM_TRGOCFG_ADCX_PTRGI0A

#define BOARD_APP_ADC16_PMT_TRIG_CH ADC16_CONFIG_TRG0A

/* DAC section */
#define BOARD_DAC_BASE           HPM_DAC0
#define BOARD_DAC_IRQn           IRQn_DAC0
#define BOARD_APP_DAC_CLOCK_NAME clock_dac0

/* CAN section */
#define BOARD_APP_CAN_BASE HPM_MCAN0
#define BOARD_APP_CAN_IRQn IRQn_MCAN0

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
#define BOARD_USB0_ID_PORT       (HPM_GPIO0)
#define BOARD_USB0_ID_GPIO_INDEX (GPIO_DO_GPIOC)
#define BOARD_USB0_ID_GPIO_PIN   (23)

/*BLDC pwm*/

/*PWM define*/
#define BOARD_BLDCPWM              HPM_PWM0
#define BOARD_BLDC_UH_PWM_OUTPIN   (0U)
#define BOARD_BLDC_UL_PWM_OUTPIN   (1U)
#define BOARD_BLDC_VH_PWM_OUTPIN   (2U)
#define BOARD_BLDC_VL_PWM_OUTPIN   (3U)
#define BOARD_BLDC_WH_PWM_OUTPIN   (4U)
#define BOARD_BLDC_WL_PWM_OUTPIN   (5U)
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
#define BOARD_BLDCPWM_CMP_TRIG_CMP (15U)

/*HALL define*/

#define BOARD_BLDC_HALL_BASE                      HPM_HALL0
#define BOARD_BLDC_HALL_TRGM                      HPM_TRGM0
#define BOARD_BLDC_HALL_IRQ                       IRQn_HALL0
#define BOARD_BLDC_HALL_TRGM_HALL_U_SRC           HPM_TRGM0_INPUT_SRC_TRGM0_P8
#define BOARD_BLDC_HALL_TRGM_HALL_V_SRC           HPM_TRGM0_INPUT_SRC_TRGM0_P7
#define BOARD_BLDC_HALL_TRGM_HALL_W_SRC           HPM_TRGM0_INPUT_SRC_TRGM0_P6
#define BOARD_BLDC_HALL_MOTOR_PHASE_COUNT_PER_REV (1000U)

/*QEI*/

#define BOARD_BLDC_QEI_BASE                      HPM_QEI0
#define BOARD_BLDC_QEI_IRQ                       IRQn_QEI0
#define BOARD_BLDC_QEI_TRGM                      HPM_TRGM0
#define BOARD_BLDC_QEI_TRGM_QEI_A_SRC            HPM_TRGM0_INPUT_SRC_TRGM0_P6
#define BOARD_BLDC_QEI_TRGM_QEI_B_SRC            HPM_TRGM0_INPUT_SRC_TRGM0_P7
#define BOARD_BLDC_QEI_MOTOR_PHASE_COUNT_PER_REV (16U)
#define BOARD_BLDC_QEI_CLOCK_SOURCE              clock_mot0
#define BOARD_BLDC_QEI_FOC_PHASE_COUNT_PER_REV   (4000U)

/*Timer define*/

#define BOARD_BLDC_TMR_1MS    HPM_GPTMR2
#define BOARD_BLDC_TMR_CH     0
#define BOARD_BLDC_TMR_CMP    0
#define BOARD_BLDC_TMR_IRQ    IRQn_GPTMR2
#define BOARD_BLDC_TMR_RELOAD (100000U)

/*adc*/
#define BOARD_BLDC_ADC_MODULE    ADCX_MODULE_ADC16
#define BOARD_BLDC_ADC_U_BASE    HPM_ADC0
#define BOARD_BLDC_ADC_V_BASE    HPM_ADC1
#define BOARD_BLDC_ADC_W_BASE    HPM_ADC2
#define BOARD_BLDC_ADC_TRIG_FLAG adc16_event_trig_complete

#define BOARD_BLDC_ADC_CH_U                   (11U)
#define BOARD_BLDC_ADC_CH_V                   (9U)
#define BOARD_BLDC_ADC_CH_W                   (4U)
#define BOARD_BLDC_ADC_IRQn                   IRQn_ADC0
#define BOARD_BLDC_ADC_PMT_DMA_SIZE_IN_4BYTES (ADC_SOC_PMT_MAX_DMA_BUFF_LEN_IN_4BYTES)
#define BOARD_BLDC_ADC_TRG                    ADC16_CONFIG_TRG0A
#define BOARD_BLDC_ADC_PREEMPT_TRIG_LEN       (1U)
#define BOARD_BLDC_PWM_TRIG_CMP_INDEX         (8U)
#define BOARD_BLDC_TRIGMUX_IN_NUM             HPM_TRGM0_INPUT_SRC_PWM0_CH8REF
#define BOARD_BLDC_TRG_NUM                    TRGM_TRGOCFG_ADCX_PTRGI0A

/*PLA*/
#define BOARD_PLA_COUNTER        HPM_PLA0
#define BOARD_PLA_PWM_BASE       HPM_PWM0
#define BOARD_PLA_PWM_CLOCK_NAME clock_mot0
#define BOARD_PLA_TRGM           HPM_TRGM0
#define BOARD_PLA_PWM_TRG        (HPM_TRGM0_INPUT_SRC_PWM0_CH8REF)
#define BOARD_PLA_IN_TRG_NUM     (TRGM_TRGOCFG_PLA_IN0)
#define BOARD_PLA_OUT_TRG        (HPM_TRGM0_INPUT_SRC_PLA0_OUT0)
#define BOARD_PLA_IO_TRG_NUM     (TRGM_TRGOCFG_TRGM_OUT5)
#define BOARD_PLA_PWM_CMP        (8U)
#define BOARD_PLA_PWM_CHN        (8U)

/* APP PWM */
#define BOARD_APP_PWM             HPM_PWM0
#define BOARD_APP_PWM_CLOCK_NAME  clock_mot0
#define BOARD_APP_PWM_OUT1        0
#define BOARD_APP_PWM_OUT2        1
#define BOARD_APP_TRGM            HPM_TRGM0
#define BOARD_APP_PWM_IRQ         IRQn_PWM0
#define BOARD_APP_TRGM_PWM_OUTPUT TRGM_TRGOCFG_PWM_SYNCI

/* APP HRPWM */
#define BOARD_APP_HRPWM            HPM_PWM1
#define BOARD_APP_HRPWM_CLOCK_NAME clock_mot1
#define BOARD_APP_HRPWM_OUT1       0
#define BOARD_APP_HRPWM_OUT2       2
#define BOARD_APP_HRPWM_TRGM       HPM_TRGM1

#define BOARD_CPU_FREQ (480000000UL)

/* LED */
#define BOARD_R_GPIO_CTRL  HPM_GPIO0
#define BOARD_R_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_R_GPIO_PIN   27
#define BOARD_G_GPIO_CTRL  HPM_GPIO0
#define BOARD_G_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_G_GPIO_PIN   1
#define BOARD_B_GPIO_CTRL  HPM_GPIO0
#define BOARD_B_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_B_GPIO_PIN   19

#define BOARD_LED_GPIO_CTRL  BOARD_G_GPIO_CTRL
#define BOARD_LED_GPIO_INDEX BOARD_G_GPIO_INDEX
#define BOARD_LED_GPIO_PIN   BOARD_G_GPIO_PIN

#define BOARD_LED_OFF_LEVEL  0
#define BOARD_LED_ON_LEVEL   !BOARD_LED_OFF_LEVEL
#define BOARD_LED_TOGGLE_RGB 1

/* Key Section */
#define BOARD_APP_GPIO_INDEX GPIO_DI_GPIOZ
#define BOARD_APP_GPIO_PIN   2

/* RGB LED Section */
#define BOARD_RED_PWM_IRQ              IRQn_PWM3
#define BOARD_RED_PWM                  HPM_PWM3
#define BOARD_RED_PWM_OUT              7
#define BOARD_RED_PWM_CMP              8
#define BOARD_RED_PWM_CMP_INITIAL_ZERO true
#define BOARD_RED_PWM_CLOCK_NAME       clock_mot3

#define BOARD_GREEN_PWM_IRQ              IRQn_PWM1
#define BOARD_GREEN_PWM                  HPM_PWM1
#define BOARD_GREEN_PWM_OUT              1
#define BOARD_GREEN_PWM_CMP              8
#define BOARD_GREEN_PWM_CMP_INITIAL_ZERO true
#define BOARD_GREEN_PWM_CLOCK_NAME       clock_mot1

#define BOARD_BLUE_PWM_IRQ              IRQn_PWM0
#define BOARD_BLUE_PWM                  HPM_PWM0
#define BOARD_BLUE_PWM_OUT              7
#define BOARD_BLUE_PWM_CMP              8
#define BOARD_BLUE_PWM_CMP_INITIAL_ZERO true
#define BOARD_BLUE_PWM_CLOCK_NAME       clock_mot0

#define BOARD_RGB_RED   0
#define BOARD_RGB_GREEN (BOARD_RGB_RED + 1)
#define BOARD_RGB_BLUE  (BOARD_RGB_RED + 2)

/* PLA TAMAGAWA*/

#define PLA_TMGW_SPI              HPM_SPI2
#define PLA_TMGW_SPI_DMA          BOARD_APP_HDMA
#define PLA_TMGW_SPI_DMAMUX       BOARD_APP_DMAMUX
#define PLA_TMGW_SPI_RX_DMA_REQ   HPM_DMA_SRC_SPI2_RX
#define PLA_TMGW_SPI_TX_DMA_REQ   HPM_DMA_SRC_SPI2_TX
#define PLA_TMGW_SPI_RX_DMA_CH    0
#define PLA_TMGW_SPI_TX_DMA_CH    1
#define PLA_TMGW_SPI_RX_DMAMUX_CH DMA_SOC_CHN_TO_DMAMUX_CHN(PLA_TMGW_SPI_DMA, PLA_TMGW_SPI_RX_DMA_CH)
#define PLA_TMGW_SPI_TX_DMAMUX_CH DMA_SOC_CHN_TO_DMAMUX_CHN(PLA_TMGW_SPI_DMA, PLA_TMGW_SPI_TX_DMA_CH)

#define PLA_TMGW_SPI_CS_GPIO_CTRL  HPM_GPIO0
#define PLA_TMGW_SPI_CS_GPIO_INDEX GPIO_DI_GPIOB
#define PLA_TMGW_SPI_CS_GPIO_PIN   30

#define PLA_TMGW_DATA_DIR_GPIO_CTRL  HPM_GPIO0
#define PLA_TMGW_DATA_DIR_GPIO_INDEX GPIO_DI_GPIOB
#define PLA_TMGW_DATA_DIR_GPIO_PIN   21

#define PLA_TMGW_POWER_GPIO_CTRL  HPM_GPIO0
#define PLA_TMGW_POWER_GPIO_INDEX GPIO_DI_GPIOB
#define PLA_TMGW_POWER_GPIO_PIN   31

#define PLA_TMGW_SPI_485_DIR_TRG      (HPM_TRGM0_INPUT_SRC_PLA0_OUT1)
#define PLA_TMGW_SPI_485_DIR_TRGNUM   (TRGM_TRGOCFG_TRGM_OUT1)
#define PLA_TMGW_SPI_MOSI_DATA_TRG    (HPM_TRGM0_INPUT_SRC_TRGM0_P3)
#define PLA_TMGW_SPI_MOSI_DATA_TRGNUM (TRGM_TRGOCFG_PLA_IN3)

#define PLA_TMGW_SPI_CS_TRG    (TEST_MOTOR_PWM_TRG_PLA_TRG)
#define PLA_TMGW_SPI_CS_TRGNUM (TRGM_TRGOCFG_TRGM_OUT0)

#define PLA_TMGW_COUNTER                HPM_PLA0
#define PLA_TMGW_PWM_BASE               HPM_PWM3
#define PLA_TMGW_PWM_CLOCK_NAME         clock_mot3
#define PLA_TMGW_TRGM_CLK_IN_TRG        (HPM_TRGM0_INPUT_SRC_TRGM3_OUTX0)
#define PLA_TMGW_TRGM_CLK_To_PLA_TRGNUM (TRGM_TRGOCFG_PLA_IN0)
#define PLA_TMGW_TRGM                   (HPM_TRGM0)
#define PLA_TMGW_CLK_TRGM               (HPM_TRGM3)
#define PLA_TMGW_CLK_PWM_TRG            (HPM_TRGM3_INPUT_SRC_PWM3_CH15REF)
#define PLA_TMGW_CLK_TRG_NUM            (TRGM_TRGOCFG_TRGM_OUTX0)
#define PLA_TMGW_OUT_TRG                (HPM_TRGM0_INPUT_SRC_PLA0_OUT0)
#define PLA_TMGW_IO_TRG_NUM             (TRGM_TRGOCFG_TRGM_OUT5)
#define PLA_TMGW_PWM_CMP                (15U)
#define PLA_TMGW_PWM_CHN                (15U)
#define PLA_TMGW_PWM_SYNCI_TRG          (HPM_TRGM0_INPUT_SRC_PLA0_OUT2)
#define PLA_TMGW_PWM_SYNCI_TRGNUM       (TRGM_TRGOCFG_TRGM_OUTX0)
#define PLA_TMGW_PWM_SYNCI_IN_TRG       (HPM_TRGM3_INPUT_SRC_TRGM0_OUTX0)
#define PLA_TMGW_PWM_SYNCI_IN_TRGNUM    (TRGM_TRGOCFG_PWM_SYNCI)

#define PLA_TMGW_HALL_TIME_TRG (HPM_TRGM0_INPUT_SRC_PLA0_OUT2)

#define PLA_TMGW_IN_MOTOR_TRG_NUM (TRGM_TRGOCFG_PLA_IN2)

#define PLA_TMGW_QEI_BASE                  HPM_QEI0
#define PLA_TMGW_QEI_TRGM                  HPM_TRGM0
#define PLA_TMGW_QEI_TRGM_QEI_A_SRC        HPM_TRGM0_INPUT_SRC_PLA0_OUT0
#define PLA_TMGW_QEI_IRQ                   IRQn_QEI0
#define PLA_TMGW_QEI_MOTOR_PHASE_COUNT_MAX (0xffffff)

#define PLA_TMGW_QEI_TRGM_QEI_TRG0   HPM_TRGM0_INPUT_SRC_QEI0_TRGO
#define PLA_TMGW_QEI_TRGM_QEI_PLA_IN TRGM_TRGOCFG_PLA_IN1

#define PLA_TMGW_QEI_DMA       BOARD_APP_HDMA
#define PLA_TMGW_QEI_DMAMUX    BOARD_APP_DMAMUX
#define PLA_TMGW_QEI_DMAREQ    HPM_DMA_SRC_MOT0_0
#define PLA_TMGW_QEI_DMACH     (2UL)
#define PLA_TMGW_QEI_DMAMUX_CH DMA_SOC_CHN_TO_DMAMUX_CHN(PLA_TMGW_QEI_DMA, PLA_TMGW_QEI_DMACH)

#define PLA_TMGW_HALL_BASE      HPM_HALL0
#define PLA_TMGW_HALL_TRGM      HPM_TRGM0
#define PLA_TMGW_HALL_DMA       BOARD_APP_HDMA
#define PLA_TMGW_HALL_DMAMUX    BOARD_APP_DMAMUX
#define PLA_TMGW_HALL_DMA_CH    (3U)
#define PLA_TMGW_HALL_DMAMUX_CH DMA_SOC_CHN_TO_DMAMUX_CHN(PLA_TMGW_HALL_DMA, PLA_TMGW_HALL_DMA_CH)
#define PLA_TMGW_HALL_TRAN_SIZE (4U) /* four world */
#define PLA_TMGW_HALL_DMA_REQ   HPM_DMA_SRC_MOT0_1

#define PLA_TMGW_DMA_LINK_NUM        (25U)
#define PLA_TMGW_DMA_LINK_TRGM       HPM_TRGM0
#define PLA_TMGW_DMA_LINK_DMA        BOARD_APP_HDMA
#define PLA_TMGW_DMA_LINK_DMAMUX     BOARD_APP_DMAMUX
#define PLA_TMGW_DMA_LINK_DMA_CH     (4U)
#define PLA_TMGW_DMA_LINK_DMAMUX_CH  DMA_SOC_CHN_TO_DMAMUX_CHN(PLA_TMGW_DMA_LINK_DMA, PLA_TMGW_DMA_LINK_DMA_CH)
#define PLA_TMGW_DMA_LINK_TRAN_SIZE  (4U)
#define PLA_TMGW_DMA_LINK_DMA_REQ    HPM_DMA_SRC_MOT0_2
#define PLA_TMGW_DMA_LINK_TRGM_INPUT HPM_TRGM0_INPUT_SRC_PLA0_OUT6

/**
 * @brief Get adc phase current
 *
 */
#define BOARD_BLDC_ADC_PHASE_CH_U             (3U)
#define BOARD_BLDC_ADC_PHASE_CH_V             (4U)
#define BOARD_BLDC_ADC_PHASE_CH_W             (2U)
#define BOARD_BLDC_ADC_PHASE_U_BASE           HPM_ADC0
#define BOARD_BLDC_ADC_PHASE_V_BASE           HPM_ADC0
#define BOARD_BLDC_ADC_PHASE_W_BASE           HPM_ADC0
#define BOARD_BLDC_ADC_PHASE_TRG              ADC16_CONFIG_TRG0A
#define BOARD_BLDC_ADC_PHASE_PREEMPT_TRIG_LEN (3)
#define BOARD_BLDC_ADC_PHASE_IRQn             IRQn_ADC0
#define BOARD_BLDC_ADC_PHASE_TRIG_FLAG        adc16_event_trig_complete

#ifndef BOARD_SHOW_CLOCK
#define BOARD_SHOW_CLOCK 1
#endif
#ifndef BOARD_SHOW_BANNER
#define BOARD_SHOW_BANNER 1
#endif

/* FreeRTOS Definitions */
#define BOARD_FREERTOS_TIMER          HPM_GPTMR1
#define BOARD_FREERTOS_TIMER_CHANNEL  1
#define BOARD_FREERTOS_TIMER_IRQ      IRQn_GPTMR1
#define BOARD_FREERTOS_TIMER_CLK_NAME clock_gptmr1

/* Threadx Definitions */
#define BOARD_THREADX_TIMER           HPM_GPTMR1
#define BOARD_THREADX_TIMER_CHANNEL   1
#define BOARD_THREADX_TIMER_IRQ       IRQn_GPTMR1
#define BOARD_THREADX_TIMER_CLK_NAME  clock_gptmr1
/* Tamper Section */
#define BOARD_TAMP_ACTIVE_CH    4
#define BOARD_TAMP_LOW_LEVEL_CH 6

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

void board_init_gpio_pins(void);
void board_init_spi_pins(SPI_Type *ptr);
void board_init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void board_write_spi_cs(uint32_t pin, uint8_t state);
uint8_t board_get_led_gpio_off_level(void);
uint8_t board_get_led_pwm_off_level(void);
void board_init_led_pins(void);
void board_disable_output_rgb_led(uint8_t color);
void board_enable_output_rgb_led(uint8_t color);
void board_init_rgb_pwm_pins(void);

void board_led_write(uint8_t state);
void board_led_toggle(void);

/* Initialize SoC overall clocks */
void board_init_clock(void);

uint32_t board_init_gptmr_clock(GPTMR_Type *ptr);

uint32_t board_init_spi_clock(SPI_Type *ptr);

void board_init_lin_pins(LIN_Type *ptr);
uint32_t board_init_lin_clock(LIN_Type *ptr);

uint32_t board_init_adc16_clock(ADC16_Type *ptr, bool clk_src_ahb);

uint32_t board_init_dac_clock(DAC_Type *ptr, bool clk_src_ahb);

void board_init_adc16_pins(void);

void board_init_dac_pins(DAC_Type *ptr);

uint32_t board_init_can_clock(MCAN_Type *ptr);

void board_init_usb_pins(void);
void board_usb_vbus_ctrl(uint8_t usb_index, uint8_t level);
uint8_t board_get_usb_id_status(void);

/*
 * @brief Initialize PMP and PMA for but not limited to the following purposes:
 *      -- non-cacheable memory initialization
 */
void board_init_pmp(void);

void board_delay_us(uint32_t us);
void board_delay_ms(uint32_t ms);

void board_timer_create(uint32_t ms, board_timer_cb cb);
void board_ungate_mchtmr_at_lp_mode(void);

/* Initialize the UART clock */
uint32_t board_init_uart_clock(UART_Type *ptr);

uint32_t board_init_pwm_clock(PWM_Type *ptr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _HPM_BOARD_H */
