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

#define BOARD_NAME          "hpm5301evklite"
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
#define BOARD_APP_UART_BASE       HPM_UART3
#define BOARD_APP_UART_IRQ        IRQn_UART3
#define BOARD_APP_UART_BAUDRATE   (115200UL)
#define BOARD_APP_UART_CLK_NAME   clock_uart3
#define BOARD_APP_UART_RX_DMA_REQ HPM_DMA_SRC_UART3_RX
#define BOARD_APP_UART_TX_DMA_REQ HPM_DMA_SRC_UART3_TX
#endif

#define BOARD_APP_UART_BREAK_SIGNAL_PIN IOC_PAD_PA26

/* Trigger UART: UART0~3 use HPM_TRGM0_OUTPUT_SRC_UART_TRIG0, UART4~7 use HPM_TRGM0_OUTPUT_SRC_UART_TRIG1 */
#define BOARD_APP_UART_TRIG                 HPM_TRGM0_OUTPUT_SRC_UART_TRIG0
#define BOARD_UART_TRGM                     HPM_TRGM0
#define BOARD_UART_TRGM_GPTMR               HPM_GPTMR1
#define BOARD_UART_TRGM_GPTMR_CLK           clock_gptmr1
#define BOARD_UART_TRGM_GPTMR_CH            2
#define BOARD_UART_TRGM_GPTMR_INPUT         HPM_TRGM0_INPUT_SRC_GPTMR1_OUT2

/* uart lin sample section */
#define BOARD_UART_LIN          BOARD_APP_UART_BASE
#define BOARD_UART_LIN_IRQ      BOARD_APP_UART_IRQ
#define BOARD_UART_LIN_CLK_NAME BOARD_APP_UART_CLK_NAME
#define BOARD_UART_LIN_TX_PORT  GPIO_DI_GPIOB
#define BOARD_UART_LIN_TX_PIN   (15U) /* PB15 should align with used pin in pinmux configuration */

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
#define BOARD_APP_I2C_BASE     HPM_I2C3
#define BOARD_APP_I2C_IRQ      IRQn_I2C3
#define BOARD_APP_I2C_CLK_NAME clock_i2c3
#define BOARD_APP_I2C_DMA      HPM_HDMA
#define BOARD_APP_I2C_DMAMUX   HPM_DMAMUX
#define BOARD_APP_I2C_DMA_SRC  HPM_DMA_SRC_I2C3

/* gptmr section */
#define BOARD_GPTMR                   HPM_GPTMR0
#define BOARD_GPTMR_IRQ               IRQn_GPTMR0
#define BOARD_GPTMR_CHANNEL           1
#define BOARD_GPTMR_DMA_SRC           HPM_DMA_SRC_GPTMR0_1
#define BOARD_GPTMR_CLK_NAME          clock_gptmr0
#define BOARD_GPTMR_PWM               HPM_GPTMR0
#define BOARD_GPTMR_PWM_CHANNEL       1
#define BOARD_GPTMR_PWM_DMA_SRC       HPM_DMA_SRC_GPTMR0_1
#define BOARD_GPTMR_PWM_CLK_NAME      clock_gptmr0
#define BOARD_GPTMR_PWM_IRQ           IRQn_GPTMR0
#define BOARD_GPTMR_PWM_SYNC          HPM_GPTMR0
#define BOARD_GPTMR_PWM_SYNC_CHANNEL  2
#define BOARD_GPTMR_PWM_SYNC_CLK_NAME clock_gptmr0

/* User LED */
#define BOARD_LED_GPIO_CTRL  HPM_GPIO0
#define BOARD_LED_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_LED_GPIO_PIN   10

#define BOARD_LED_OFF_LEVEL 1
#define BOARD_LED_ON_LEVEL  0

/* 12V Power Enable*/
#define BOARD_12V_EN_GPIO_CTRL  HPM_GPIO0
#define BOARD_12V_EN_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_12V_EN_GPIO_PIN   24

/* gpiom section */
#define BOARD_APP_GPIOM_BASE            HPM_GPIOM
#define BOARD_APP_GPIOM_USING_CTRL      HPM_FGPIO
#define BOARD_APP_GPIOM_USING_CTRL_NAME gpiom_core0_fast

/* tinyuf2 button on hpm5301evklite*/
#define BOARD_BUTTON_TINYUF2_PIN 9

/* User button */
#define BOARD_APP_GPIO_CTRL  HPM_GPIO0
#define BOARD_APP_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_APP_GPIO_PIN   3
#define BOARD_APP_GPIO_IRQ   IRQn_GPIO0_A
#define BOARD_BUTTON_PRESSED_VALUE 1

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
#define BOARD_APP_ADC16_CH_1     (2U)
#define BOARD_APP_ADC16_CLK_NAME (clock_adc0)
#define BOARD_APP_ADC16_CLK_BUS  (clk_adc_src_ahb0)
#define BOARD_APP_ADC16_PMT_TRIG_CH ADC16_CONFIG_TRG0A

/* Flash section */
#define BOARD_APP_XPI_NOR_XPI_BASE     (HPM_XPI0)
#define BOARD_APP_XPI_NOR_CFG_OPT_HDR  (0xfcf90002U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT0 (0x00000006U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT1 (0x00001000U)

/* CALLBACK TIMER section */
#define BOARD_CALLBACK_TIMER          (HPM_GPTMR1)
#define BOARD_CALLBACK_TIMER_CH       0
#define BOARD_CALLBACK_TIMER_IRQ      IRQn_GPTMR1
#define BOARD_CALLBACK_TIMER_CLK_NAME (clock_gptmr1)

/*Timer define*/
#define BOARD_BLDC_TMR_1MS    HPM_GPTMR2
#define BOARD_BLDC_TMR_CH     0
#define BOARD_BLDC_TMR_CMP    0
#define BOARD_BLDC_TMR_IRQ    IRQn_GPTMR2
#define BOARD_BLDC_TMR_CLOCK  clock_gptmr2
#define BOARD_BLDC_TMR_RELOAD (100000U)

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

#ifndef BOARD_SHOW_CLOCK
#define BOARD_SHOW_CLOCK 1
#endif
#ifndef BOARD_SHOW_BANNER
#define BOARD_SHOW_BANNER 1
#endif

/* FreeRTOS Definitions */
#define BOARD_FREERTOS_TIMER          HPM_GPTMR0
#define BOARD_FREERTOS_TIMER_CHANNEL  1
#define BOARD_FREERTOS_TIMER_IRQ      IRQn_GPTMR0
#define BOARD_FREERTOS_TIMER_CLK_NAME clock_gptmr0

#define BOARD_FREERTOS_TICK_SRC_PWM          HPM_PWM0
#define BOARD_FREERTOS_TICK_SRC_PWM_IRQ      IRQn_PWM0
#define BOARD_FREERTOS_TICK_SRC_PWM_CLK_NAME clock_mot0

#define BOARD_FREERTOS_LOWPOWER_TIMER          HPM_PTMR
#define BOARD_FREERTOS_LOWPOWER_TIMER_CHANNEL  1
#define BOARD_FREERTOS_LOWPOWER_TIMER_IRQ      IRQn_PTMR
#define BOARD_FREERTOS_LOWPOWER_TIMER_CLK_NAME clock_ptmr

/* Threadx Definitions */
#define BOARD_THREADX_TIMER          HPM_GPTMR0
#define BOARD_THREADX_TIMER_CHANNEL  1
#define BOARD_THREADX_TIMER_IRQ      IRQn_GPTMR0
#define BOARD_THREADX_TIMER_CLK_NAME clock_gptmr0

#define BOARD_THREADX_LOWPOWER_TIMER          HPM_PTMR
#define BOARD_THREADX_LOWPOWER_TIMER_CHANNEL  1
#define BOARD_THREADX_LOWPOWER_TIMER_IRQ      IRQn_PTMR
#define BOARD_THREADX_LOWPOWER_TIMER_CLK_NAME clock_ptmr

/* uC/OS-III Definitions */
#define BOARD_UCOS_TIMER          HPM_GPTMR0
#define BOARD_UCOS_TIMER_CHANNEL  1
#define BOARD_UCOS_TIMER_IRQ      IRQn_GPTMR0
#define BOARD_UCOS_TIMER_CLK_NAME clock_gptmr0

/* i2s over spi Section*/
#define BOARD_I2S_SPI_CS_GPIO_CTRL  HPM_GPIO0
#define BOARD_I2S_SPI_CS_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_I2S_SPI_CS_GPIO_PIN   31
#define BOARD_I2S_SPI_CS_GPIO_PAD   IOC_PAD_PA31

#define BOARD_GPTMR_I2S_MCLK          HPM_GPTMR1
#define BOARD_GPTMR_I2S_MCLK_CHANNEL  1
#define BOARD_GPTMR_I2S_MCLK_CLK_NAME clock_gptmr1

#define BOARD_GPTMR_I2S_LRCK          HPM_GPTMR0
#define BOARD_GPTMR_I2S_LRCK_CHANNEL  2
#define BOARD_GPTMR_I2S_LRCK_CLK_NAME clock_gptmr0

#define BOARD_GPTMR_I2S_BCLK          HPM_GPTMR0
#define BOARD_GPTMR_I2S_BLCK_CHANNEL  3
#define BOARD_GPTMR_I2S_BLCK_CLK_NAME clock_gptmr0

#define BOARD_GPTMR_I2S_FINSH          HPM_GPTMR0
#define BOARD_GPTMR_I2S_FINSH_IRQ      IRQn_GPTMR0
#define BOARD_GPTMR_I2S_FINSH_CHANNEL  0
#define BOARD_GPTMR_I2S_FINSH_CLK_NAME clock_gptmr0

#define BOARD_APP_CLK_REF_PIN_NAME "J3[32] (PA09)"
#define BOARD_APP_CLK_REF_CLK_NAME clock_ref0

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

typedef void (*board_timer_cb)(void);

void board_init_gpio_pins(void);
void board_init_led_pins(void);
void board_init_usb(USB_Type *ptr);
void board_led_write(uint8_t state);
void board_led_toggle(void);
void board_init_console(void);
void board_init_uart(UART_Type *ptr);
uint32_t board_init_spi_clock(SPI_Type *ptr);
void board_init_spi_pins(SPI_Type *ptr);
uint32_t board_init_adc_clock(void *ptr, bool clk_src_bus);
void board_init_adc16_pins(void);
void board_init_acmp_pins(void);
void board_init_acmp_clock(ACMP_Type *ptr);
void board_disable_output_rgb_led(uint8_t color);
void board_enable_output_rgb_led(uint8_t color);
void board_write_spi_cs(uint32_t pin, uint8_t state);
void board_init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);

void board_init(void);
void board_init_usb_dp_dm_pins(void);
void board_init_clock(void);
void board_delay_us(uint32_t us);
void board_delay_ms(uint32_t ms);
void board_timer_create(uint32_t ms, board_timer_cb cb);
void board_ungate_mchtmr_at_lp_mode(void);

uint8_t board_get_led_gpio_off_level(void);

void board_init_pmp(void);

uint32_t board_init_uart_clock(UART_Type *ptr);

uint32_t board_init_i2c_clock(I2C_Type *ptr);
void board_init_i2c(I2C_Type *ptr);

void board_init_gptmr_channel_pin(GPTMR_Type *ptr, uint32_t channel, bool as_comp);
void board_init_clk_ref_pin(void);
uint32_t board_init_gptmr_clock(GPTMR_Type *ptr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _HPM_BOARD_H */
