/*
 * Copyright (c) 2026 HPMicro
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
#include "pinmux.h"
#if !defined(CONFIG_NDEBUG_CONSOLE) || !CONFIG_NDEBUG_CONSOLE
#include "hpm_debug_console.h"
#endif

#define BOARD_NAME          "hpm5100evk"
#define BOARD_UF2_SIGNATURE (0x0A4D5048UL)

#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE HPM_CORE0
#endif

/* ACMP desction */
#define BOARD_ACMP             HPM_ACMP0
#define BOARD_ACMP_CLK         clock_acmp0
#define BOARD_ACMP_CHANNEL     ACMP_CHANNEL_CHN0
#define BOARD_ACMP_IRQ         IRQn_ACMP0_0
#define BOARD_ACMP_PLUS_INPUT  ACMP_INPUT_DAC_OUT  /* use internal DAC */
#define BOARD_ACMP_MINUS_INPUT ACMP_INPUT_ANALOG_1 /* align with used pin */

/* dma section */
#define BOARD_APP_DMA0      HPM_HDMA0
#define BOARD_APP_DMA1      HPM_HDMA1
#define BOARD_APP_DMA0_IRQ  IRQn_HDMA0
#define BOARD_APP_DMA1_IRQ  IRQn_HDMA1
#define BOARD_APP_DMAMUX    HPM_DMAMUX
#define TEST_DMA_CONTROLLER HPM_HDMA0
#define TEST_DMA_IRQ        IRQn_HDMA0

/* uart section */
#ifndef BOARD_APP_UART_BASE
#define BOARD_APP_UART_BASE       HPM_UART2
#define BOARD_APP_UART_IRQ        IRQn_UART2
#define BOARD_APP_UART_BAUDRATE   (115200UL)
#define BOARD_APP_UART_CLK_NAME   clock_uart2
#define BOARD_APP_UART_RX_DMA_REQ HPM_DMA_SRC_UART2_RX
#define BOARD_APP_UART_TX_DMA_REQ HPM_DMA_SRC_UART2_TX
#endif

#define BOARD_APP_UART_BREAK_SIGNAL_PIN IOC_PAD_PC14

#define BOARD_APP_UART_TRIG HPM_TRGM0_OUTPUT_SRC_UART_TRIG1 /* need to match UART instance */
#define BOARD_UART_TRGM                     HPM_TRGM0
#define BOARD_UART_TRGM_GPTMR               HPM_GPTMR1
#define BOARD_UART_TRGM_GPTMR_CLK           clock_gptmr1
#define BOARD_UART_TRGM_GPTMR_CH            2
#define BOARD_UART_TRGM_GPTMR_INPUT         HPM_TRGM0_INPUT_SRC_GPTMR1_OUT2

/* uart lin sample section */
#define BOARD_UART_LIN          HPM_UART3
#define BOARD_UART_LIN_IRQ      IRQn_UART3
#define BOARD_UART_LIN_CLK_NAME clock_uart3
#define BOARD_UART_LIN_TX_PORT  GPIO_DI_GPIOC
#define BOARD_UART_LIN_TX_PIN   (0U) /* PC00 should align with used pin in pinmux configuration */

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

/* nor flash section */
#define BOARD_FLASH_BASE_ADDRESS (0x80000000UL)
#define BOARD_FLASH_SIZE         (SIZE_1MB)

/* i2c section */
#define BOARD_APP_I2C_BASE     HPM_I2C1
#define BOARD_APP_I2C_IRQ      IRQn_I2C1
#define BOARD_APP_I2C_CLK_NAME clock_i2c1
#define BOARD_APP_I2C_DMA      HPM_HDMA0
#define BOARD_APP_I2C_DMAMUX   HPM_DMAMUX
#define BOARD_APP_I2C_DMA_SRC  HPM_DMA_SRC_I2C1

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
#define BOARD_LED_GPIO_PIN   18
#define BOARD_LED_GPIO_NAME  "PA18"

#define BOARD_LED_OFF_LEVEL 1
#define BOARD_LED_ON_LEVEL  0

/* gpiom section */
#define BOARD_APP_GPIOM_BASE            HPM_GPIOM
#define BOARD_APP_GPIOM_USING_CTRL      HPM_FGPIO
#define BOARD_APP_GPIOM_USING_CTRL_NAME gpiom_core0_fast

/* User button */
#define BOARD_APP_GPIO_CTRL  HPM_GPIO0
#define BOARD_APP_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_APP_GPIO_PIN   15
#define BOARD_APP_GPIO_IRQ   IRQn_GPIO0_A
#define BOARD_BUTTON_PRESSED_VALUE 0

/* spi section */
#define BOARD_APP_SPI_BASE              HPM_SPI3
#define BOARD_APP_SPI_CLK_NAME          clock_spi3
#define BOARD_APP_SPI_IRQ               IRQn_SPI3
#define BOARD_APP_SPI_SCLK_FREQ         (10000000UL)
#define BOARD_APP_SPI_ADDR_LEN_IN_BYTES (1U)
#define BOARD_APP_SPI_DATA_LEN_IN_BITS  (8U)
#define BOARD_APP_SPI_RX_DMA            HPM_DMA_SRC_SPI3_RX
#define BOARD_APP_SPI_TX_DMA            HPM_DMA_SRC_SPI3_TX
#define BOARD_SPI_CS_GPIO_CTRL          HPM_GPIO0
#define BOARD_SPI_CS_PIN                IOC_PAD_PC06
#define BOARD_SPI_CS_ACTIVE_LEVEL       (0U)

/* ADC section */
#define BOARD_APP_ADC16_NAME     "ADC0"
#define BOARD_APP_ADC16_BASE     HPM_ADC0
#define BOARD_APP_ADC16_IRQn     IRQn_ADC0
#define BOARD_APP_ADC16_CH_1     (2U)
#define BOARD_APP_ADC16_CLK_NAME (clock_adc0)
#define BOARD_APP_ADC16_CLK_BUS  (clk_adc_src_ahb0)

#define BOARD_APP_ADC16_HW_TRIG_SRC_CLK_NAME clock_pwm0
#define BOARD_APP_ADC16_HW_TRIG_SRC          HPM_PWM0
#define BOARD_APP_ADC16_HW_TRGM              HPM_TRGM0
#define BOARD_APP_ADC16_HW_TRGM_IN           HPM_TRGM0_INPUT_SRC_PWM0_TRIGO_8
#define BOARD_APP_ADC16_HW_TRGM_OUT_SEQ      TRGM_TRGOCFG_ADC0_STRGI
#define BOARD_APP_ADC16_HW_TRGM_OUT_PMT      TRGM_TRGOCFG_ADCX_PTRGI0A

#define BOARD_APP_ADC16_PMT_TRIG_CH ADC16_CONFIG_TRG0A

/* Flash section */
#define BOARD_APP_XPI_NOR_XPI_BASE     (HPM_XPI0)
#define BOARD_APP_XPI_NOR_CFG_OPT_HDR  (0xfcf90002U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT0 (0x00000006U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT1 (0x00001000U)

/* MCAN section */
#define BOARD_APP_CAN_BASE HPM_MCAN0
#define BOARD_APP_CAN_IRQn IRQn_MCAN0

/* CALLBACK TIMER section */
#define BOARD_CALLBACK_TIMER          (HPM_GPTMR0)
#define BOARD_CALLBACK_TIMER_CH       3
#define BOARD_CALLBACK_TIMER_IRQ      IRQn_GPTMR0
#define BOARD_CALLBACK_TIMER_CLK_NAME (clock_gptmr0)

/* APP PWM */
#define BOARD_APP_TRGM            HPM_TRGM0
#define BOARD_APP_PWM             HPM_PWM3
#define BOARD_APP_PWM_CLOCK_NAME  clock_pwm3
#define BOARD_APP_PWM_OUT1        0
#define BOARD_APP_PWM_OUT2        1
#define BOARD_APP_PWM_IRQ         IRQn_PWM3
#define BOARD_APP_TRGM_PWM_OUTPUT TRGM_TRGOCFG_PWM3_SYNCI
#define BOARD_APP_TRGM_PWM_INPUT  HPM_TRGM0_INPUT_SRC_PWM3_TRIGO_8

/* moto */
#define BOARD_MOTOR_CLK_NAME clock_mot0

/* OPAMP */
#define BOARD_APP_OPAMP           HPM_OPAMP3
#define BOARD_APP_OPAMP_CLOCK     clock_opa3
#define BOARD_APP_OPAMP_INP_PAD   inp_pad_vip1

#ifndef BOARD_SHOW_CLOCK
#define BOARD_SHOW_CLOCK 1
#endif
#ifndef BOARD_SHOW_BANNER
#define BOARD_SHOW_BANNER 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*board_timer_cb)(void);

void board_init(void);
void board_init_console(void);
void board_init_gpio_pins(void);
void board_init_led_pins(void);
void board_init_usb(USB_Type *ptr);
void board_led_write(uint8_t state);
void board_led_toggle(void);
void board_init_uart(UART_Type *ptr);
void board_init_spi_pins(SPI_Type *ptr);
void board_write_spi_cs(uint32_t pin, uint8_t state);
void board_init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void board_init_adc16_pins(void);
void board_init_acmp_pins(void);
void board_init_acmp_clock(ACMP_Type *ptr);
void board_init_can(MCAN_Type *ptr);
void board_init_rgb_pwm_pins(void);
void board_disable_output_rgb_led(uint8_t color);
void board_enable_output_rgb_led(uint8_t color);
void board_init_dac_pins(void *ptr);
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
uint32_t board_init_i2c_clock(I2C_Type *ptr);
void board_init_i2c(I2C_Type *ptr);
void board_init_adc_qeiv2_pins(void);
void board_init_gptmr_channel_pin(GPTMRV2_Type *ptr, uint32_t channel, bool as_comp);
void board_init_clk_ref_pin(void);
uint32_t board_init_gptmr_clock(GPTMRV2_Type *ptr);

/* Pin dispatch wrappers (used by RT-Thread drivers) */
void init_pwm_pins(PWM_Type *ptr);
void init_py_pins_as_pgpio(void);
void init_uart_pins(UART_Type *ptr);
hpm_stat_t init_i2c_pins(I2C_Type *ptr);
void init_can_pins(MCAN_Type *ptr);
void init_usb_pins(USB_Type *ptr);
void init_spi_pins(SPI_Type *ptr);
void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void init_gptmr_channel_pin(GPTMRV2_Type *ptr, uint32_t channel, bool as_comp);
uint32_t board_init_spi_clock(SPI_Type *ptr);
#ifdef __cplusplus
}
#endif

#endif /* _HPM_BOARD_H */
