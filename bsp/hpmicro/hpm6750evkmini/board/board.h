/*
 * Copyright (c) 2021-2025 HPMicro
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
#include "hpm_lcdc_drv.h"
#include "hpm_trgm_drv.h"
#ifdef CONFIG_HPM_PANEL
#include "hpm_panel.h"
#endif
#if !defined(CONFIG_NDEBUG_CONSOLE) || !CONFIG_NDEBUG_CONSOLE
#include "hpm_debug_console.h"
#endif

#define BOARD_NAME          "hpm6750evkmini"
#define BOARD_UF2_SIGNATURE (0x0A4D5048UL)

#define SEC_CORE_IMG_START ILM_LOCAL_BASE

#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE HPM_CORE0
#endif

/* uart section */
#ifndef BOARD_APP_UART_BASE
#define BOARD_APP_UART_BASE       HPM_UART13
#define BOARD_APP_UART_IRQ        IRQn_UART13
#define BOARD_APP_UART_BAUDRATE   (115200UL)
#define BOARD_APP_UART_CLK_NAME   clock_uart13
#define BOARD_APP_UART_RX_DMA_REQ HPM_DMA_SRC_UART13_RX
#define BOARD_APP_UART_TX_DMA_REQ HPM_DMA_SRC_UART13_TX
#endif

#define BOARD_APP_UART_BREAK_SIGNAL_PIN IOC_PAD_PB24

/* uart rx idle demo section */
#define BOARD_UART_IDLE            BOARD_APP_UART_BASE
#define BOARD_UART_IDLE_IRQ        BOARD_APP_UART_IRQ
#define BOARD_UART_IDLE_CLK_NAME   BOARD_APP_UART_CLK_NAME
#define BOARD_UART_IDLE_TX_DMA_SRC BOARD_APP_UART_TX_DMA_REQ
#define BOARD_UART_IDLE_DMA_SRC    BOARD_APP_UART_RX_DMA_REQ

#define BOARD_UART_IDLE_TRGM                    HPM_TRGM2
#define BOARD_UART_IDLE_TRGM_PIN                IOC_PAD_PD19
#define BOARD_UART_IDLE_TRGM_INPUT_SRC          HPM_TRGM2_INPUT_SRC_TRGM2_P9
#define BOARD_UART_IDLE_TRGM_OUTPUT_GPTMR_IN    HPM_TRGM2_OUTPUT_SRC_GPTMR4_IN2
#define BOARD_UART_IDLE_TRGM_OUTPUT_GPTMR_SYNCI HPM_TRGM2_OUTPUT_SRC_GPTMR4_SYNCI

#define BOARD_UART_IDLE_GPTMR          HPM_GPTMR4
#define BOARD_UART_IDLE_GPTMR_CLK_NAME clock_gptmr4
#define BOARD_UART_IDLE_GPTMR_IRQ      IRQn_GPTMR4
#define BOARD_UART_IDLE_GPTMR_CMP_CH   0
#define BOARD_UART_IDLE_GPTMR_CAP_CH   2

/* uart microros sample section */
#define BOARD_MICROROS_UART_BASE     BOARD_APP_UART_BASE
#define BOARD_MICROROS_UART_IRQ      BOARD_APP_UART_IRQ
#define BOARD_MICROROS_UART_CLK_NAME BOARD_APP_UART_CLK_NAME

/* rtthread-nano finsh section */
#define BOARD_RT_CONSOLE_BASE        BOARD_CONSOLE_UART_BASE
#define BOARD_RT_CONSOLE_CLK_NAME    BOARD_CONSOLE_UART_CLK_NAME
#define BOARD_RT_CONSOLE_IRQ         BOARD_CONSOLE_UART_IRQ

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

/* uart lin sample section */
#define BOARD_UART_LIN          BOARD_APP_UART_BASE
#define BOARD_UART_LIN_IRQ      BOARD_APP_UART_IRQ
#define BOARD_UART_LIN_CLK_NAME BOARD_APP_UART_CLK_NAME
#define BOARD_UART_LIN_TX_PORT  GPIO_DI_GPIOZ
#define BOARD_UART_LIN_TX_PIN   (9U) /* PZ09 should align with used pin in pinmux configuration */

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
#define BOARD_CONSOLE_UART_BASE       HPM_UART13
#define BOARD_CONSOLE_UART_CLK_NAME   clock_uart13
#define BOARD_CONSOLE_UART_IRQ        IRQn_UART13
#define BOARD_CONSOLE_UART_TX_DMA_REQ HPM_DMA_SRC_UART13_TX
#define BOARD_CONSOLE_UART_RX_DMA_REQ HPM_DMA_SRC_UART13_RX
#endif
#endif
#define BOARD_CONSOLE_UART_BAUDRATE (115200UL)
#endif
#endif

/* sdram section */
#define BOARD_SDRAM_ADDRESS          (0x40000000UL)
#define BOARD_SDRAM_SIZE             (16 * SIZE_1MB)
#define BOARD_SDRAM_CS               FEMC_SDRAM_CS0
#define BOARD_SDRAM_PORT_SIZE        FEMC_SDRAM_PORT_SIZE_16_BITS
#define BOARD_SDRAM_COLUMN_ADDR_BITS FEMC_SDRAM_COLUMN_ADDR_9_BITS
#define BOARD_SDRAM_REFRESH_COUNT    (4096UL)
#define BOARD_SDRAM_REFRESH_IN_MS    (64UL)

/* lcd section */
#define BOARD_LCD_BASE                 HPM_LCDC
#define BOARD_LCD_IRQ                  IRQn_LCDC_D0
#define BOARD_LCD_POWER_GPIO_BASE      HPM_GPIO0
#define BOARD_LCD_POWER_GPIO_INDEX     GPIO_DO_GPIOB
#define BOARD_LCD_POWER_GPIO_PIN       12
#define BOARD_LCD_BACKLIGHT_GPIO_BASE  HPM_GPIO0
#define BOARD_LCD_BACKLIGHT_GPIO_INDEX GPIO_DO_GPIOB
#define BOARD_LCD_BACKLIGHT_GPIO_PIN   23

/* i2c section */
#define BOARD_APP_I2C_BASE     HPM_I2C0
#define BOARD_APP_I2C_IRQ      IRQn_I2C0
#define BOARD_APP_I2C_IRQ      IRQn_I2C0
#define BOARD_APP_I2C_CLK_NAME clock_i2c0
#define BOARD_APP_I2C_DMA      HPM_HDMA
#define BOARD_APP_I2C_DMAMUX   HPM_DMAMUX
#define BOARD_APP_I2C_DMA_SRC  HPM_DMA_SRC_I2C0

#define BOARD_CAM_I2C_BASE     HPM_I2C0
#define BOARD_CAM_I2C_CLK_NAME clock_i2c0

#define BOARD_CAP_I2C_BASE           (HPM_I2C0)
#define BOARD_CAP_I2C_CLK_NAME       clock_i2c0
#define BOARD_CAP_RST_GPIO           (HPM_GPIO0)
#define BOARD_CAP_RST_GPIO_INDEX     (GPIO_DI_GPIOB)
#define BOARD_CAP_RST_GPIO_PIN       (9)
#define BOARD_CAP_RST_GPIO_IRQ       (IRQn_GPIO0_B)
#define BOARD_CAP_INTR_GPIO          (HPM_GPIO0)
#define BOARD_CAP_INTR_GPIO_INDEX    (GPIO_DI_GPIOB)
#define BOARD_CAP_INTR_GPIO_PIN      (8)
#define BOARD_CAP_INTR_GPIO_IRQ      (IRQn_GPIO0_B)
#define BOARD_CAP_I2C_SDA_GPIO_INDEX (GPIO_DI_GPIOB)
#define BOARD_CAP_I2C_SDA_GPIO_PIN   (10)
#define BOARD_CAP_I2C_CLK_GPIO_INDEX (GPIO_DI_GPIOB)
#define BOARD_CAP_I2C_CLK_GPIO_PIN   (11)

/* ACMP desction */
#define BOARD_ACMP             HPM_ACMP
#define BOARD_ACMP_CLK         clock_acmp0
#define BOARD_ACMP_CHANNEL     ACMP_CHANNEL_CHN1
#define BOARD_ACMP_IRQ         IRQn_ACMP_1
#define BOARD_ACMP_PLUS_INPUT  ACMP_INPUT_DAC_OUT  /* use internal DAC */
#define BOARD_ACMP_MINUS_INPUT ACMP_INPUT_ANALOG_6 /* align with used pin */

/* dma section */
#define BOARD_APP_XDMA      HPM_XDMA
#define BOARD_APP_HDMA      HPM_HDMA
#define BOARD_APP_XDMA_IRQ  IRQn_XDMA
#define BOARD_APP_HDMA_IRQ  IRQn_HDMA
#define BOARD_APP_DMAMUX    HPM_DMAMUX
#define TEST_DMA_CONTROLLER HPM_XDMA
#define TEST_DMA_IRQ        IRQn_XDMA

/* gptmr section */
#define BOARD_GPTMR                   HPM_GPTMR5
#define BOARD_GPTMR_IRQ               IRQn_GPTMR5
#define BOARD_GPTMR_CHANNEL           1
#define BOARD_GPTMR_DMA_SRC           HPM_DMA_SRC_GPTMR5_1
#define BOARD_GPTMR_CLK_NAME          clock_gptmr5
#define BOARD_GPTMR_PWM               HPM_GPTMR5
#define BOARD_GPTMR_PWM_DMA_SRC       HPM_DMA_SRC_GPTMR5_1
#define BOARD_GPTMR_PWM_CHANNEL       1
#define BOARD_GPTMR_PWM_CLK_NAME      clock_gptmr5
#define BOARD_GPTMR_PWM_IRQ           IRQn_GPTMR5
#define BOARD_GPTMR_PWM_SYNC          HPM_GPTMR5
#define BOARD_GPTMR_PWM_SYNC_CHANNEL  0
#define BOARD_GPTMR_PWM_SYNC_CLK_NAME clock_gptmr5

/* gpio section */
#define BOARD_R_GPIO_CTRL  HPM_GPIO0
#define BOARD_R_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_R_GPIO_PIN   19
#define BOARD_G_GPIO_CTRL  HPM_GPIO0
#define BOARD_G_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_G_GPIO_PIN   18
#define BOARD_B_GPIO_CTRL  HPM_GPIO0
#define BOARD_B_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_B_GPIO_PIN   20

#define BOARD_LED_GPIO_CTRL  BOARD_G_GPIO_CTRL
#define BOARD_LED_GPIO_INDEX BOARD_G_GPIO_INDEX
#define BOARD_LED_GPIO_PIN   BOARD_G_GPIO_PIN

/*
 *led Internal pull-up and pull-down resistance direction
 *The configurations of Rev-A / B boards are different
 */
#define BOARD_LED_OFF_LEVEL 1
#define BOARD_LED_ON_LEVEL  0

#define BOARD_APP_GPIO_INDEX GPIO_DI_GPIOZ
#define BOARD_APP_GPIO_PIN   2
#define BOARD_BUTTON_PRESSED_VALUE 0

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
#define BOARD_APP_SPI_BASE              HPM_SPI2
#define BOARD_APP_SPI_CLK_NAME          clock_spi2
#define BOARD_APP_SPI_IRQ               IRQn_SPI2
#define BOARD_APP_SPI_SCLK_FREQ         (20000000UL)
#define BOARD_APP_SPI_ADDR_LEN_IN_BYTES (1U)
#define BOARD_APP_SPI_DATA_LEN_IN_BITS  (8U)
#define BOARD_APP_SPI_RX_DMA            HPM_DMA_SRC_SPI2_RX
#define BOARD_APP_SPI_TX_DMA            HPM_DMA_SRC_SPI2_TX
#define BOARD_SPI_CS_GPIO_CTRL          HPM_GPIO0
#define BOARD_SPI_CS_PIN                IOC_PAD_PB24
#define BOARD_SPI_CS_ACTIVE_LEVEL       (0U)

/* Flash section */
#define BOARD_APP_XPI_NOR_XPI_BASE     (HPM_XPI0)
#define BOARD_APP_XPI_NOR_CFG_OPT_HDR  (0xfcf90002U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT0 (0x00000007U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT1 (0x0000000EU)

#define BOARD_FLASH_BASE_ADDRESS (0x80000000UL)
#define BOARD_FLASH_SIZE         (8 << 20)

/* lcd section */

#ifndef BOARD_LCD_WIDTH
#define BOARD_LCD_WIDTH PANEL_SIZE_WIDTH
#endif
#ifndef BOARD_LCD_HEIGHT
#define BOARD_LCD_HEIGHT PANEL_SIZE_HEIGHT
#endif

/* pdma section */
#define BOARD_PDMA_BASE HPM_PDMA

/* i2s section */
#define BOARD_MIC_I2S               HPM_I2S0
#define BOARD_MIC_I2S_CLK_NAME      clock_i2s0
#define BOARD_MIC_I2S_DATA_LINE     I2S_DATA_LINE_0
#define BOARD_MIC_I2S_RX_DMAMUX_SRC HPM_DMA_SRC_I2S0_RX

#define BOARD_SPEAKER_I2S               HPM_I2S1
#define BOARD_SPEAKER_I2S_CLK_NAME      clock_i2s1
#define BOARD_SPEAKER_I2S_DATA_LINE     I2S_DATA_LINE_0
#define BOARD_SPEAKER_I2S_TX_DMAMUX_SRC HPM_DMA_SRC_I2S1_TX

#define BOARD_MASTER_I2S               HPM_I2S0
#define BOARD_MASTER_I2S_CLK_NAME      clock_i2s0
#define BOARD_MASTER_I2S_RX_DATA_LINE  I2S_DATA_LINE_1
#define BOARD_MASTER_I2S_RX_DMAMUX_SRC HPM_DMA_SRC_I2S0_RX

#define BOARD_SLAVE_I2S               HPM_I2S0
#define BOARD_SLAVE_I2S_CLK_NAME      clock_i2s0
#define BOARD_SLAVE_I2S_TX_DATA_LINE  I2S_DATA_LINE_1
#define BOARD_SLAVE_I2S_TX_DMAMUX_SRC HPM_DMA_SRC_I2S0_TX

/* pdm selection */
#define BOARD_PDM_SINGLE_CHANNEL_MASK (1U)
#define BOARD_PDM_DUAL_CHANNEL_MASK   (0x11U)

/* enet section */
#define BOARD_ENET_PPS           HPM_ENET0
#define BOARD_ENET_PPS_IDX       enet_pps_0
#define BOARD_ENET_PPS_PTP_CLOCK clock_ptp0

#define BOARD_ENET_AUXI_SNAPSHOT           HPM_ENET0
#define BOARD_ENET_AUXI_SNAPSHOT_IDX       enet_ptp_auxi_snapshot_trigger_0
#define BOARD_ENET_AUXI_SNAPSHOT_PTP_CLOCK clock_ptp0

#define BOARD_ENET_RMII_RST_GPIO       HPM_GPIO0
#define BOARD_ENET_RMII_RST_GPIO_INDEX GPIO_DO_GPIOD
#define BOARD_ENET_RMII_RST_GPIO_PIN   (15U)
#define BOARD_ENET_RMII                HPM_ENET1
#define BOARD_ENET_RMII_INT_REF_CLK    (0U)
#define BOARD_ENET_RMII_PTP_CLOCK      clock_ptp1

/* ADC section */
#define BOARD_APP_ADC12_NAME     "ADC0"
#define BOARD_APP_ADC12_BASE     HPM_ADC0
#define BOARD_APP_ADC12_IRQn     IRQn_ADC0
#define BOARD_APP_ADC12_CH_1     (14U)
#define BOARD_APP_ADC12_CLK_NAME (clock_adc0)

#define BOARD_APP_ADC16_NAME     "ADC3"
#define BOARD_APP_ADC16_IRQn     IRQn_ADC3
#define BOARD_APP_ADC16_BASE     HPM_ADC3
#define BOARD_APP_ADC16_CH_1     (2U)
#define BOARD_APP_ADC16_CLK_NAME (clock_adc3)
#define BOARD_APP_ADC16_CLK_BUS  (clk_adc_src_ahb0)

#define BOARD_APP_ADC12_HW_TRIG_SRC_CLK_NAME clock_mot0
#define BOARD_APP_ADC12_HW_TRIG_SRC          HPM_PWM0
#define BOARD_APP_ADC12_HW_TRGM              HPM_TRGM0
#define BOARD_APP_ADC12_HW_TRGM_IN           HPM_TRGM0_INPUT_SRC_PWM0_CH8REF
#define BOARD_APP_ADC12_HW_TRGM_OUT_SEQ      TRGM_TRGOCFG_ADC0_STRGI
#define BOARD_APP_ADC12_HW_TRGM_OUT_PMT      TRGM_TRGOCFG_ADCX_PTRGI0A

#define BOARD_APP_ADC16_HW_TRIG_SRC_CLK_NAME clock_mot0
#define BOARD_APP_ADC16_HW_TRIG_SRC          HPM_PWM0
#define BOARD_APP_ADC16_HW_TRGM              HPM_TRGM0
#define BOARD_APP_ADC16_HW_TRGM_IN           HPM_TRGM0_INPUT_SRC_PWM0_CH8REF
#define BOARD_APP_ADC16_HW_TRGM_OUT_SEQ      TRGM_TRGOCFG_ADC3_STRGI
#define BOARD_APP_ADC16_HW_TRGM_OUT_PMT      TRGM_TRGOCFG_ADCX_PTRGI0A

#define BOARD_APP_ADC12_PMT_TRIG_CH ADC12_CONFIG_TRG0A
#define BOARD_APP_ADC16_PMT_TRIG_CH ADC16_CONFIG_TRG0A

/* CAN section */
#define BOARD_APP_CAN_BASE HPM_CAN1
#define BOARD_APP_CAN_IRQn IRQn_CAN1

/*
 * timer for board delay
 */
#define BOARD_DELAY_TIMER          (HPM_GPTMR7)
#define BOARD_DELAY_TIMER_CH       0
#define BOARD_DELAY_TIMER_CLK_NAME (clock_gptmr7)

#define BOARD_CALLBACK_TIMER          (HPM_GPTMR7)
#define BOARD_CALLBACK_TIMER_CH       1
#define BOARD_CALLBACK_TIMER_IRQ      IRQn_GPTMR7
#define BOARD_CALLBACK_TIMER_CLK_NAME (clock_gptmr7)

/* SDXC section */
#define BOARD_APP_SDCARD_SDXC_BASE                 (HPM_SDXC1)
#define BOARD_APP_SDCARD_SDXC_IRQ                  IRQn_SDXC1
#define BOARD_APP_SDCARD_SUPPORT_3V3               (1)
#define BOARD_APP_SDCARD_SUPPORT_1V8               (1)
#define BOARD_APP_SDCARD_SUPPORT_4BIT              (1)
#define BOARD_APP_SDCARD_SUPPORT_CARD_DETECTION    (1)
#define BOARD_APP_SDCARD_SUPPORT_POWER_SWITCH      (0)
#define BOARD_APP_SDCARD_SUPPORT_VOLTAGE_SWITCH    (1)
#define BOARD_APP_SDCARD_SUPPORT_CARD_DETECTION    (1)
#define BOARD_APP_SDCARD_CARD_DETECTION_USING_GPIO (0)
#if defined(BOARD_APP_SDCARD_CARD_DETECTION_USING_GPIO) && (BOARD_APP_SDCARD_CARD_DETECTION_USING_GPIO == 1)
#define BOARD_APP_SDCARD_CARD_DETECTION_GPIO       NULL
#define BOARD_APP_SDCARD_CARD_DETECTION_GPIO_INDEX 0
#define BOARD_APP_SDCARD_CARD_DETECTION_PIN_INDEX  0
#endif

#define BOARD_APP_EMMC_SDXC_BASE              (HPM_SDXC1)
#define BOARD_APP_EMMC_SDXC_IRQ               IRQn_SDXC1
#define BOARD_APP_EMMC_SUPPORT_3V3            (1)
#define BOARD_APP_EMMC_SUPPORT_1V8            (0)
#define BOARD_APP_EMMC_SUPPORT_4BIT           (1)
#define BOARD_APP_EMMC_SUPPORT_8BIT           (0)
#define BOARD_APP_EMMC_SUPPORT_VOLTAGE_SWITCH (0)
/* For eMMC device, it is recommended to use GPIO to switch voltage directly */
#define BOARD_APP_EMMC_VOLTAGE_SWITCH_USING_GPIO (1)
#if defined(BOARD_APP_EMMC_VOLTAGE_SWITCH_USING_GPIO) && (BOARD_APP_EMMC_VOLTAGE_SWITCH_USING_GPIO == 1)
#define BOARD_APP_EMMC_VSEL_PIN IOC_PAD_PD29
#endif

/* APP PWM */
#define BOARD_APP_PWM             HPM_PWM0
#define BOARD_APP_PWM_CLOCK_NAME  clock_mot0
#define BOARD_APP_PWM_OUT1        4
#define BOARD_APP_PWM_OUT2        5
#define BOARD_APP_TRGM            HPM_TRGM0
#define BOARD_APP_PWM_IRQ         IRQn_PWM0
#define BOARD_APP_TRGM_PWM_OUTPUT TRGM_TRGOCFG_PWM_SYNCI

/* RGB LED Section */
#define BOARD_RED_PWM_IRQ              IRQn_PWM1
#define BOARD_RED_PWM                  HPM_PWM1
#define BOARD_RED_PWM_OUT              0
#define BOARD_RED_PWM_CMP              0
#define BOARD_RED_PWM_CMP_INITIAL_ZERO true
#define BOARD_RED_PWM_CLOCK_NAME       clock_mot1

#define BOARD_GREEN_PWM_IRQ              IRQn_PWM1
#define BOARD_GREEN_PWM                  HPM_PWM1
#define BOARD_GREEN_PWM_OUT              1
#define BOARD_GREEN_PWM_CMP              1
#define BOARD_GREEN_PWM_CMP_INITIAL_ZERO true
#define BOARD_GREEN_PWM_CLOCK_NAME       clock_mot1

#define BOARD_BLUE_PWM_IRQ              IRQn_PWM0
#define BOARD_BLUE_PWM                  HPM_PWM0
#define BOARD_BLUE_PWM_OUT              7
#define BOARD_BLUE_PWM_CMP              7
#define BOARD_BLUE_PWM_CMP_INITIAL_ZERO true
#define BOARD_BLUE_PWM_CLOCK_NAME       clock_mot0

#define BOARD_RGB_RED   0
#define BOARD_RGB_GREEN (BOARD_RGB_RED + 1)
#define BOARD_RGB_BLUE  (BOARD_RGB_RED + 2)

/* Beep Section */
#define BOARD_BEEP_PWM            HPM_PWM3
#define BOARD_BEEP_PWM_OUT        4
#define BOARD_BEEP_PWM_CLOCK_NAME clock_mot3

/*BLDC pwm*/

/*PWM define*/
#define BOARD_BLDCPWM              HPM_PWM1
#define BOARD_BLDC_UH_PWM_OUTPIN   (2U)
#define BOARD_BLDC_UL_PWM_OUTPIN   (3U)
#define BOARD_BLDC_VH_PWM_OUTPIN   (4U)
#define BOARD_BLDC_VL_PWM_OUTPIN   (5U)
#define BOARD_BLDC_WH_PWM_OUTPIN   (6U)
#define BOARD_BLDC_WL_PWM_OUTPIN   (7U)
#define BOARD_BLDCPWM_TRGM         HPM_TRGM1
#define BOARD_BLDCAPP_PWM_IRQ      IRQn_PWM1
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

#define BOARD_BLDC_HALL_BASE                      HPM_HALL2
#define BOARD_BLDC_HALL_TRGM                      HPM_TRGM2
#define BOARD_BLDC_HALL_IRQ                       IRQn_HALL2
#define BOARD_BLDC_HALL_TRGM_HALL_U_SRC           HPM_TRGM2_INPUT_SRC_TRGM2_P9
#define BOARD_BLDC_HALL_TRGM_HALL_V_SRC           HPM_TRGM2_INPUT_SRC_TRGM2_P10
#define BOARD_BLDC_HALL_TRGM_HALL_W_SRC           HPM_TRGM2_INPUT_SRC_TRGM2_P11
#define BOARD_BLDC_HALL_MOTOR_PHASE_COUNT_PER_REV (1000U)

/*QEI*/

#define BOARD_BLDC_QEI_BASE                      HPM_QEI2
#define BOARD_BLDC_QEI_IRQ                       IRQn_QEI2
#define BOARD_BLDC_QEI_TRGM                      HPM_TRGM2
#define BOARD_BLDC_QEI_TRGM_QEI_A_SRC            HPM_TRGM2_INPUT_SRC_TRGM2_P6
#define BOARD_BLDC_QEI_TRGM_QEI_B_SRC            HPM_TRGM2_INPUT_SRC_TRGM2_P7
#define BOARD_BLDC_QEI_MOTOR_PHASE_COUNT_PER_REV (16U)
#define BOARD_BLDC_QEI_CLOCK_SOURCE              clock_mot2
#define BOARD_BLDC_QEI_FOC_PHASE_COUNT_PER_REV   (4000U)

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
#define BOARD_BLDC_ADC_MODULE    ADCX_MODULE_ADC12
#define BOARD_BLDC_ADC_U_BASE    HPM_ADC0
#define BOARD_BLDC_ADC_V_BASE    HPM_ADC1
#define BOARD_BLDC_ADC_W_BASE    HPM_ADC2
#define BOARD_BLDC_ADC_TRIG_FLAG adc12_event_trig_complete

#define BOARD_BLDC_ADC_CH_U                   (1U)
#define BOARD_BLDC_ADC_CH_V                   (2U)
#define BOARD_BLDC_ADC_CH_W                   (3U)
#define BOARD_BLDC_ADC_IRQn                   IRQn_ADC0
#define BOARD_BLDC_ADC_PMT_DMA_SIZE_IN_4BYTES (ADC_SOC_PMT_MAX_DMA_BUFF_LEN_IN_4BYTES)
#define BOARD_BLDC_ADC_TRG                    ADC12_CONFIG_TRG1A
#define BOARD_BLDC_ADC_PREEMPT_TRIG_LEN       (1U)
#define BOARD_BLDC_PWM_TRIG_CMP_INDEX         (8U)
#define BOARD_BLDC_TRG_ADC                    TRGM_TRGOCFG_ADCX_PTRGI0A
#define BOARD_BLDC_PWM_TRG_ADC                HPM_TRGM1_INPUT_SRC_PWM1_CH8REF

#define BOARD_BLDC_ADC_IRQn                   IRQn_ADC0

#define BOARD_CPU_FREQ (816000000UL)

#define BOARD_APP_DISPLAY_CLOCK clock_display

#ifndef BOARD_SHOW_CLOCK
#define BOARD_SHOW_CLOCK 1
#endif
#ifndef BOARD_SHOW_BANNER
#define BOARD_SHOW_BANNER 1
#endif

/* FreeRTOS Definitions */
#define BOARD_FREERTOS_TIMER          HPM_GPTMR4
#define BOARD_FREERTOS_TIMER_CHANNEL  1
#define BOARD_FREERTOS_TIMER_IRQ      IRQn_GPTMR4
#define BOARD_FREERTOS_TIMER_CLK_NAME clock_gptmr4

#define BOARD_FREERTOS_TICK_SRC_PWM          HPM_PWM0
#define BOARD_FREERTOS_TICK_SRC_PWM_IRQ      IRQn_PWM0
#define BOARD_FREERTOS_TICK_SRC_PWM_CLK_NAME clock_mot0

#define BOARD_FREERTOS_LOWPOWER_TIMER          HPM_PTMR
#define BOARD_FREERTOS_LOWPOWER_TIMER_CHANNEL  1
#define BOARD_FREERTOS_LOWPOWER_TIMER_IRQ      IRQn_PTMR
#define BOARD_FREERTOS_LOWPOWER_TIMER_CLK_NAME clock_ptmr

/* Threadx Definitions */
#define BOARD_THREADX_TIMER          HPM_GPTMR4
#define BOARD_THREADX_TIMER_CHANNEL  1
#define BOARD_THREADX_TIMER_IRQ      IRQn_GPTMR4
#define BOARD_THREADX_TIMER_CLK_NAME clock_gptmr4

#define BOARD_THREADX_LOWPOWER_TIMER          HPM_PTMR
#define BOARD_THREADX_LOWPOWER_TIMER_CHANNEL  1
#define BOARD_THREADX_LOWPOWER_TIMER_IRQ      IRQn_PTMR
#define BOARD_THREADX_LOWPOWER_TIMER_CLK_NAME clock_ptmr

/* uC/OS-III Definitions */
#define BOARD_UCOS_TIMER          HPM_GPTMR4
#define BOARD_UCOS_TIMER_CHANNEL  1
#define BOARD_UCOS_TIMER_IRQ      IRQn_GPTMR4
#define BOARD_UCOS_TIMER_CLK_NAME clock_gptmr4

#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE 0
#endif

/* Tamper Section */
#define BOARD_TAMP_ACTIVE_CH    8
#define BOARD_TAMP_LOW_LEVEL_CH 10

/* i2s over spi Section*/
#define BOARD_I2S_SPI_CS_GPIO_CTRL  HPM_GPIO0
#define BOARD_I2S_SPI_CS_GPIO_INDEX GPIO_DI_GPIOD
#define BOARD_I2S_SPI_CS_GPIO_PIN   25
#define BOARD_I2S_SPI_CS_GPIO_PAD   IOC_PAD_PD25

#define BOARD_GPTMR_I2S_MCLK          HPM_GPTMR5
#define BOARD_GPTMR_I2S_MCLK_CHANNEL  0
#define BOARD_GPTMR_I2S_MCLK_CLK_NAME clock_gptmr5

#define BOARD_GPTMR_I2S_LRCK          HPM_GPTMR5
#define BOARD_GPTMR_I2S_LRCK_CHANNEL  1
#define BOARD_GPTMR_I2S_LRCK_CLK_NAME clock_gptmr5

#define BOARD_GPTMR_I2S_BCLK          HPM_GPTMR5
#define BOARD_GPTMR_I2S_BLCK_CHANNEL  2
#define BOARD_GPTMR_I2S_BLCK_CLK_NAME clock_gptmr5

#define BOARD_GPTMR_I2S_FINSH          HPM_GPTMR5
#define BOARD_GPTMR_I2S_FINSH_IRQ      IRQn_GPTMR5
#define BOARD_GPTMR_I2S_FINSH_CHANNEL  3
#define BOARD_GPTMR_I2S_FINSH_CLK_NAME clock_gptmr5

/* BGPR */
#define BOARD_BGPR HPM_BGPR

#define BOARD_APP_CLK_REF_PIN_NAME "P2[16]"
#define BOARD_APP_CLK_REF_CLK_NAME clock_ref1

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
void board_init_lcd(void);
void board_lcd_backlight(bool is_on);
void board_panel_para_to_lcdc(lcdc_config_t *config);
void board_init_can(CAN_Type *ptr);

uint32_t board_init_femc_clock(void);

void board_init_sdram_pins(void);
void board_init_gpio_pins(void);
void board_init_spi_pins(SPI_Type *ptr);
void board_init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void board_write_spi_cs(uint32_t pin, uint8_t state);
void board_init_led_pins(void);

/* cap touch */
void board_init_cap_touch(void);

void board_led_write(uint8_t state);
void board_led_toggle(void);

void board_fpga_power_enable(void);

void board_init_cam_pins(void);
/* Initialize SoC overall clocks */
void board_init_clock(void);

/* Initialize the UART clock */
uint32_t board_init_uart_clock(UART_Type *ptr);

/* Initialize the CAM(camera) dot clock */
uint32_t board_init_cam_clock(CAM_Type *ptr);

uint32_t board_init_spi_clock(SPI_Type *ptr);

uint32_t board_init_adc_clock(void *ptr, bool clk_src_bus);

void board_init_acmp_clock(ACMP_Type *ptr);

uint32_t board_init_can_clock(CAN_Type *ptr);

hpm_stat_t board_set_audio_pll_clock(uint32_t freq);

void board_init_i2s_pins(I2S_Type *ptr);
uint32_t board_config_i2s_clock(I2S_Type *ptr, uint32_t sample_rate);
uint32_t board_init_pdm_clock(void);
uint32_t board_init_dao_clock(void);

void board_init_sd_pins(SDXC_Type *ptr);
uint32_t board_sd_configure_clock(SDXC_Type *ptr, uint32_t freq, bool need_inverse);
void board_sd_switch_pins_to_1v8(SDXC_Type *ptr);
bool board_sd_detect_card(SDXC_Type *ptr);

void board_init_dao_pins(void);

void board_init_adc12_pins(void);
void board_init_adc16_pins(void);
void board_init_acmp_pins(void);
void board_init_usb(USB_Type *ptr);

void board_init_enet_pps_pins(ENET_Type *ptr);
void board_init_enet_pps_capture_pins(ENET_Type *ptr);
uint8_t board_get_enet_dma_pbl(ENET_Type *ptr);
hpm_stat_t board_reset_enet_phy(ENET_Type *ptr);
hpm_stat_t board_init_enet_pins(ENET_Type *ptr);
hpm_stat_t board_init_enet_rmii_reference_clock(ENET_Type *ptr, bool internal);
hpm_stat_t board_init_enet_ptp_clock(ENET_Type *ptr);
hpm_stat_t board_enable_enet_irq(ENET_Type *ptr);
hpm_stat_t board_disable_enet_irq(ENET_Type *ptr);

/*
 * @brief Initialize PMP and PMA for but not limited to the following purposes:
 *      -- non-cacheable memory initialization
 */
void board_init_pmp(void);

void board_delay_ms(uint32_t ms);
void board_delay_us(uint32_t us);

void board_init_beep_pwm_pins(void);
void board_init_rgb_pwm_pins(void);

void board_timer_create(uint32_t ms, board_timer_cb cb);
void board_enable_output_rgb_led(uint8_t color);
void board_disable_output_rgb_led(uint8_t color);

/*
 * Keep mchtmr clock on low power mode
 */
void board_ungate_mchtmr_at_lp_mode(void);

/*
 * Get PWM output level of onboard LED
 */
uint8_t board_get_led_pwm_off_level(void);

/*
 * Get GPIO pin level of onboard LED
 */
uint8_t board_get_led_gpio_off_level(void);

void board_init_gptmr_channel_pin(GPTMR_Type *ptr, uint32_t channel, bool as_comp);

void board_init_clk_ref_pin(void);

uint32_t board_init_gptmr_clock(GPTMR_Type *ptr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _HPM_BOARD_H */
