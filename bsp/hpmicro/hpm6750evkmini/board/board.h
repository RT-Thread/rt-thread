/*
 * Copyright (c) 2021-2023 HPMicro
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
#include "hpm_enet_drv.h"
#include "hpm_otp_drv.h"
#include "hpm_lcdc_drv.h"
#include "pinmux.h"

#define BOARD_NAME "hpm6750evkmini"

/* uart section */
#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE HPM_CORE0
#endif
#ifndef BOARD_APP_UART_BASE
#define BOARD_APP_UART_BASE HPM_UART0
#define BOARD_APP_UART_IRQ  IRQn_UART0
#else
#ifndef BOARD_APP_UART_IRQ
#warning no IRQ specified for applicaiton uart
#endif
#endif

#define BOARD_APP_UART_BAUDRATE (115200UL)
#define BOARD_APP_UART_CLK_NAME clock_uart0

#ifndef BOARD_CONSOLE_TYPE
#define BOARD_CONSOLE_TYPE CONSOLE_TYPE_UART
#endif

#if BOARD_CONSOLE_TYPE == CONSOLE_TYPE_UART
#define BOARD_CONSOLE_BASE HPM_UART0
#define BOARD_CONSOLE_CLK_NAME clock_uart0
#define BOARD_CONSOLE_BAUDRATE (115200UL)
#endif

#define BOARD_FREEMASTER_UART_BASE HPM_UART0
#define BOARD_FREEMASTER_UART_IRQ IRQn_UART0
#define BOARD_FREEMASTER_UART_CLK_NAME clock_uart0

/* sdram section */
#define BOARD_SDRAM_ADDRESS  (0x40000000UL)
#define BOARD_SDRAM_SIZE     (16*SIZE_1MB)
#define BOARD_SDRAM_CS       FEMC_SDRAM_CS0
#define BOARD_SDRAM_PORT_SIZE FEMC_SDRAM_PORT_SIZE_16_BITS
#define BOARD_SDRAM_REFRESH_COUNT (4096UL)
#define BOARD_SDRAM_REFRESH_IN_MS (64UL)
#define BOARD_SDRAM_DATA_WIDTH_IN_BYTE (2UL)

/* lcd section */
/*
 * BOARD_PANEL_TIMING_PARA {HSPW, HBP, HFP, VSPW, VBP, VFP, HSSP, VSSP, DESP, PDSP, PCSP}
 *
 * HSPW: Horizontal Synchronization Pulse width
 * HBP: Horizontal Back Porch
 * HFP: Horizontal Front Porch
 * VSPW: Vertical Synchronization Pulse width
 * VBP: Vertical Back Porch
 * VFP: Vertical Front Porch
 * HSSP: Horizontal Synchronization Signal Polarity, 0: High Active, 1: Low Active
 * VSSP: Vertical Synchronization Signal Polarity, 0: High Active, 1: Low Active
 * DESP: Data Enable Signal Polarity, 0: High Active, 1: Low Active
 * PDSP: Pixel Data Signal Polarity, 0: High Active, 1: Low Active
 * PCSP: Pixel Clock Signal Polarity, 0: High Active, 1: Low Active
 */
#define BOARD_PANEL_TIMEING_PARA_HSPW_INDEX 0
#define BOARD_PANEL_TIMEING_PARA_HBP_INDEX 1
#define BOARD_PANEL_TIMEING_PARA_HFP_INDEX 2
#define BOARD_PANEL_TIMEING_PARA_VSPW_INDEX 3
#define BOARD_PANEL_TIMEING_PARA_VBP_INDEX 4
#define BOARD_PANEL_TIMEING_PARA_VFP_INDEX 5
#define BOARD_PANEL_TIMEING_PARA_HSSP_INDEX 6
#define BOARD_PANEL_TIMEING_PARA_VSSP_INDEX 7
#define BOARD_PANEL_TIMEING_PARA_DESP_INDEX 8
#define BOARD_PANEL_TIMEING_PARA_PDSP_INDEX 9
#define BOARD_PANEL_TIMEING_PARA_PCSP_INDEX 10

#if defined(PANEL_TM070RDH13)

#ifndef BOARD_LCD_WIDTH
#define BOARD_LCD_WIDTH 800
#endif
#ifndef BOARD_LCD_HEIGHT
#define BOARD_LCD_HEIGHT 480
#endif
#ifndef BOARD_PANEL_TIMING_PARA
#define BOARD_PANEL_TIMING_PARA {10, 46, 50, 3, 23, 10, 0, 0, 0, 0, 0}
#endif

#else

#ifndef BOARD_LCD_WIDTH
#define BOARD_LCD_WIDTH 800
#endif
#ifndef BOARD_LCD_HEIGHT
#define BOARD_LCD_HEIGHT 480
#endif
#ifndef BOARD_PANEL_TIMING_PARA
#define BOARD_PANEL_TIMING_PARA {10, 46, 50, 3, 23, 10, 0, 0, 0, 0, 0}
#endif

#endif

/* i2c section */
#define BOARD_APP_I2C_BASE HPM_I2C0
#define BOARD_APP_I2C_IRQ IRQn_I2C0
#define BOARD_APP_I2C_CLK_NAME clock_i2c0

#define BOARD_APP_I2C_SLAVE_BASE HPM_I2C3
#define BOARD_APP_I2C_SLAVE_IRQ IRQn_I2C3
#define BOARD_APP_I2C_SLAVE_CLK_NAME clock_i2c3

#define BOARD_CAM_I2C_BASE HPM_I2C0
#define BOARD_CAM_I2C_CLK_NAME clock_i2c0

#define BOARD_CAP_I2C_BASE (HPM_I2C0)
#define BOARD_CAP_I2C_CLK_NAME clock_i2c0
#define BOARD_CAP_RST_GPIO (HPM_GPIO0)
#define BOARD_CAP_RST_GPIO_INDEX (GPIO_DI_GPIOB)
#define BOARD_CAP_RST_GPIO_PIN (9)
#define BOARD_CAP_RST_GPIO_IRQ (IRQn_GPIO0_B)
#define BOARD_CAP_INTR_GPIO (HPM_GPIO0)
#define BOARD_CAP_INTR_GPIO_INDEX (GPIO_DI_GPIOB)
#define BOARD_CAP_INTR_GPIO_PIN (8)
#define BOARD_CAP_INTR_GPIO_IRQ (IRQn_GPIO0_B)
#define BOARD_CAP_I2C_SDA_GPIO_INDEX (GPIO_DI_GPIOB)
#define BOARD_CAP_I2C_SDA_GPIO_PIN (10)
#define BOARD_CAP_I2C_CLK_GPIO_INDEX (GPIO_DI_GPIOB)
#define BOARD_CAP_I2C_CLK_GPIO_PIN (11)

/* dma section */
#define BOARD_APP_XDMA_IRQ IRQn_XDMA
#define BOARD_APP_HDMA_IRQ IRQn_HDMA

/* gpio section */
#define BOARD_R_GPIO_CTRL HPM_GPIO0
#define BOARD_R_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_R_GPIO_PIN 19
#define BOARD_G_GPIO_CTRL HPM_GPIO0
#define BOARD_G_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_G_GPIO_PIN 18
#define BOARD_B_GPIO_CTRL HPM_GPIO0
#define BOARD_B_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_B_GPIO_PIN 20

#define BOARD_LED_GPIO_CTRL BOARD_G_GPIO_CTRL
#define BOARD_LED_GPIO_INDEX BOARD_G_GPIO_INDEX
#define BOARD_LED_GPIO_PIN BOARD_G_GPIO_PIN

#define BOARD_LED_OFF_LEVEL 1
#define BOARD_LED_ON_LEVEL 0

#define BOARD_APP_GPIO_INDEX GPIO_DI_GPIOZ
#define BOARD_APP_GPIO_PIN 2

/* pinmux section */
#define USING_GPIO0_FOR_GPIOZ
#ifndef USING_GPIO0_FOR_GPIOZ
#define BOARD_APP_GPIO_CTRL HPM_BGPIO
#define BOARD_APP_GPIO_IRQ IRQn_BGPIO
#else
#define BOARD_APP_GPIO_CTRL HPM_GPIO0
#define BOARD_APP_GPIO_IRQ IRQn_GPIO0_Z
#endif

/* gpiom section */
#define BOARD_APP_GPIOM_BASE            HPM_GPIOM
#define BOARD_APP_GPIOM_USING_CTRL      HPM_FGPIO
#define BOARD_APP_GPIOM_USING_CTRL_NAME gpiom_core0_fast

/* spi section */
#define BOARD_APP_SPI_BASE HPM_SPI2
#define BOARD_APP_SPI_CLK_SRC_FREQ      (24000000UL)
#define BOARD_APP_SPI_SCLK_FREQ         (1562500UL)
#define BOARD_APP_SPI_ADDR_LEN_IN_BYTES (1U)
#define BOARD_APP_SPI_DATA_LEN_IN_BITS  (8U)

/* Flash section */
#define BOARD_APP_XPI_NOR_XPI_BASE            (HPM_XPI0)
#define BOARD_APP_XPI_NOR_CFG_OPT_HDR         (0xfcf90001U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT0        (0x00000007U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT1        (0x00000000U)

/* lcd section */
#define BOARD_LCD_BASE HPM_LCDC
#define BOARD_LCD_IRQ  IRQn_LCDC_D0
#define BOARD_LCD_POWER_GPIO_BASE HPM_GPIO0
#define BOARD_LCD_POWER_GPIO_INDEX GPIO_DO_GPIOB
#define BOARD_LCD_POWER_GPIO_PIN 12
#define BOARD_LCD_BACKLIGHT_GPIO_BASE HPM_GPIO0
#define BOARD_LCD_BACKLIGHT_GPIO_INDEX GPIO_DO_GPIOB
#define BOARD_LCD_BACKLIGHT_GPIO_PIN 23

#ifndef BOARD_LCD_WIDTH
#define BOARD_LCD_WIDTH (800)
#endif
#ifndef BOARD_LCD_HEIGHT
#define BOARD_LCD_HEIGHT (480)
#endif

/* pdma section */
#define BOARD_PDMA_BASE HPM_PDMA

/* enet section */
#define BOARD_ENET0_RST_GPIO
#define BOARD_ENET0_RST_GPIO_INDEX
#define BOARD_ENET0_RST_GPIO_PIN

#define BOARD_ENET0_INF             (0U)  /* 0: RMII, 1: RGMII */
#define BOARD_ENET0_INT_REF_CLK     (0U)
#define BOARD_ENET0_PHY_RST_TIME    (30)

#if BOARD_ENET0_INF
#define BOARD_ENET0_TX_DLY          (0U)
#define BOARD_ENET0_RX_DLY          (0U)
#endif

#if __USE_ENET_PTP
#define BOARD_ENET0_PTP_CLOCK       (clock_ptp0)
#endif


#define BOARD_ENET1_RST_GPIO        HPM_GPIO0
#define BOARD_ENET1_RST_GPIO_INDEX  GPIO_DO_GPIOD
#define BOARD_ENET1_RST_GPIO_PIN    (15U)

#define BOARD_ENET1_INF             (0U)  /* 0: RMII, 1: RGMII */
#define BOARD_ENET1_INT_REF_CLK     (0U)
#define BOARD_ENET1_PHY_RST_TIME    (30)

#if BOARD_ENET1_INF
#define BOARD_ENET1_TX_DLY          (0U)
#define BOARD_ENET1_RX_DLY          (0U)
#endif

#if __USE_ENET_PTP
#define BOARD_ENET1_PTP_CLOCK       (clock_ptp1)
#endif

/* adc section */
#define BOARD_APP_ADC12_BASE HPM_ADC0
#define BOARD_APP_ADC16_BASE HPM_ADC3
#define BOARD_APP_ADC12_IRQn IRQn_ADC0
#define BOARD_APP_ADC16_IRQn IRQn_ADC3
#define BOARD_APP_ADC_CH                         (0U)
#define BOARD_APP_ADC_SEQ_DMA_SIZE_IN_4BYTES     (1024U)
#define BOARD_APP_ADC_PREEMPT_DMA_SIZE_IN_4BYTES (192U)
#define BOARD_APP_ADC_PREEMPT_TRIG_LEN           (1U)
#define BOARD_APP_ADC_SINGLE_CONV_CNT            (6)
#define BOARD_APP_ADC_TRIG_PWMT0                 HPM_PWM0
#define BOARD_APP_ADC_TRIG_PWMT1                 HPM_PWM1
#define BOARD_APP_ADC_TRIG_TRGM0                 HPM_TRGM0
#define BOARD_APP_ADC_TRIG_TRGM1                 HPM_TRGM1
#define BOARD_APP_ADC_TRIG_PWM_SYNC              HPM_SYNT

/*
 * timer for board delay
 */
#define BOARD_DELAY_TIMER (HPM_GPTMR0)
#define BOARD_DELAY_TIMER_CH 0
#define BOARD_DELAY_TIMER_CLK_NAME (clock_gptmr0)

#define BOARD_CALLBACK_TIMER (HPM_GPTMR0)
#define BOARD_CALLBACK_TIMER_CH 1
#define BOARD_CALLBACK_TIMER_IRQ IRQn_GPTMR0
#define BOARD_CALLBACK_TIMER_CLK_NAME (clock_gptmr0)

/* SDXC section */
#define BOARD_APP_SDCARD_SDXC_BASE            (HPM_SDXC1)
#define BOARD_APP_SDCARD_SUPPORT_1V8          (0)

/* USB section */
#define BOARD_USB0_VBUS_PORT       (HPM_GPIO0)
#define BOARD_USB0_VBUS_GPIO_INDEX (GPIO_DO_GPIOF)
#define BOARD_USB0_VBUS_GPIO_PIN   (9)

#define BOARD_USB0_OC_PORT         (HPM_GPIO0)
#define BOARD_USB0_OC_GPIO_INDEX   (GPIO_DI_GPIOF)
#define BOARD_USB0_OC_GPIO_PIN     (8)

/* APP PWM */
#define BOARD_APP_PWM HPM_PWM0
#define BOARD_APP_PWM_CLOCK_NAME clock_mot0
#define BOARD_APP_PWM_OUT1 4
#define BOARD_APP_PWM_OUT2 5
#define BOARD_APP_TRGM HPM_TRGM0

/* RGB LED Section */
#define BOARD_RED_PWM_IRQ IRQn_PWM1
#define BOARD_RED_PWM HPM_PWM1
#define BOARD_RED_PWM_OUT 0
#define BOARD_RED_PWM_CMP 0
#define BOARD_RED_PWM_CMP_INITIAL_ZERO true
#define BOARD_RED_PWM_CLOCK_NAME clock_mot1

#define BOARD_GREEN_PWM_IRQ IRQn_PWM1
#define BOARD_GREEN_PWM HPM_PWM1
#define BOARD_GREEN_PWM_OUT 1
#define BOARD_GREEN_PWM_CMP 1
#define BOARD_GREEN_PWM_CMP_INITIAL_ZERO true
#define BOARD_GREEN_PWM_CLOCK_NAME clock_mot1

#define BOARD_BLUE_PWM_IRQ IRQn_PWM0
#define BOARD_BLUE_PWM HPM_PWM0
#define BOARD_BLUE_PWM_OUT 7
#define BOARD_BLUE_PWM_CMP 0
#define BOARD_BLUE_PWM_CMP_INITIAL_ZERO true
#define BOARD_BLUE_PWM_CLOCK_NAME clock_mot0


/* Beep Section */
#define BOARD_BEEP_PWM HPM_PWM3
#define BOARD_BEEP_PWM_OUT 4
#define BOARD_BEEP_PWM_CLOCK_NAME clock_mot3

#define BOARD_CPU_FREQ (816000000UL)

#ifndef BOARD_SHOW_CLOCK
#define BOARD_SHOW_CLOCK 1
#endif
#ifndef BOARD_SHOW_BANNER
#define BOARD_SHOW_BANNER 1
#endif

#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE 0
#endif

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

typedef void (*board_timer_cb)(void);

void board_init(void);
void board_init_console(void);

void board_init_uart(UART_Type *ptr);
void board_init_i2c(I2C_Type *ptr);
void board_init_lcd(void);
void board_panel_para_to_lcdc(lcdc_config_t *config);

void board_init_can(CAN_Type *ptr);

uint32_t board_init_femc_clock(void);

void board_init_sdram_pins(void);
void board_init_gpio_pins(void);
void board_init_spi_pins(SPI_Type *ptr);
void board_init_led_pins(void);

/* cap touch */
void board_init_cap_touch(void);

void board_led_write(bool state);
void board_led_toggle(void);

void board_fpga_power_enable(void);

void board_init_cam_pins(void);

/* Initialize SoC overall clocks */
void board_init_clock(void);

/* Initialize the CAM(camera) dot clock */
uint32_t board_init_cam_clock(CAM_Type *ptr);

/* Initialize the LCD pixel clock */
uint32_t board_init_lcd_clock(void);

uint32_t board_init_uart_clock(UART_Type *ptr);

uint32_t board_init_spi_clock(SPI_Type *ptr);

uint32_t board_init_adc12_clock(ADC12_Type *ptr);

uint32_t board_init_adc16_clock(ADC16_Type *ptr);

uint32_t board_init_can_clock(CAN_Type *ptr);

uint32_t board_init_i2s_clock(I2S_Type *ptr);
uint32_t board_init_pdm_clock(void);
uint32_t board_init_dao_clock(void);

uint32_t board_init_gptmr_clock(GPTMR_Type *ptr);

void board_init_sd_pins(SDXC_Type *ptr);
uint32_t board_sd_configure_clock(SDXC_Type *ptr, uint32_t freq);
void board_sd_switch_pins_to_1v8(SDXC_Type *ptr);
void board_sd_power_switch(SDXC_Type *ptr, bool on_off);
bool board_sd_detect_card(SDXC_Type *ptr);

void board_init_usb_pins(void);
void board_usb_vbus_ctrl(uint8_t usb_index, uint8_t level);

/*
 * @brief Initialize PMP and PMA for but not limited to the following purposes:
 *      -- non-cacheable memory initialization
 */
void board_init_pmp(void);

void board_delay_ms(uint32_t ms);

void board_init_beep_pwm_pins(void);
void board_init_rgb_pwm_pins(void);

void board_timer_create(uint32_t ms, void *cb);

hpm_stat_t board_init_enet_pins(ENET_Type *ptr);
hpm_stat_t board_init_enet_rmii_reference_clock(ENET_Type *ptr, bool internal);
hpm_stat_t board_reset_enet_phy(ENET_Type *ptr);
uint8_t    board_enet_get_dma_pbl(ENET_Type *ptr);
hpm_stat_t board_init_enet_ptp_clock(ENET_Type *ptr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _HPM_BOARD_H */
