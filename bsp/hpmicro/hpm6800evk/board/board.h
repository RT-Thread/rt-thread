/*
 * Copyright (c) 2023-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_BOARD_H
#define _HPM_BOARD_H
#include <stdio.h>
#include "hpm_common.h"
#include "hpm_clock_drv.h"
#include "hpm_lcdc_drv.h"
#include "hpm_soc.h"
#include "hpm_soc_feature.h"
#include "pinmux.h"
#ifdef CONFIG_HPM_PANEL
#include "hpm_panel.h"
#endif
#if !defined(CONFIG_NDEBUG_CONSOLE) || !CONFIG_NDEBUG_CONSOLE
#include "hpm_debug_console.h"
#endif

#define BOARD_NAME          "hpm6800evk"
#define BOARD_UF2_SIGNATURE (0x0A4D5048UL)

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

#define BOARD_APP_UART_BREAK_SIGNAL_PIN IOC_PAD_PE04

/* uart lin sample section */
#define BOARD_UART_LIN          BOARD_APP_UART_BASE
#define BOARD_UART_LIN_IRQ      BOARD_APP_UART_IRQ
#define BOARD_UART_LIN_CLK_NAME BOARD_APP_UART_CLK_NAME
#define BOARD_UART_LIN_TX_PORT  GPIO_DI_GPIOE
#define BOARD_UART_LIN_TX_PIN   (15U) /* PE15 should align with used pin in pinmux configuration */

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

/* lin section */
#define BOARD_LIN          HPM_LIN0
#define BOARD_LIN_CLK_NAME clock_lin0
#define BOARD_LIN_IRQ      IRQn_LIN0
#define BOARD_LIN_BAUDRATE (19200U)

/* nor flash section */
#define BOARD_FLASH_BASE_ADDRESS (0x80000000UL)
#define BOARD_FLASH_SIZE         (16 * SIZE_1MB)

/* i2c section */
#define BOARD_APP_I2C_BASE     HPM_I2C1
#define BOARD_APP_I2C_IRQ      IRQn_I2C1
#define BOARD_APP_I2C_CLK_NAME clock_i2c1
#define BOARD_APP_I2C_DMA      HPM_HDMA
#define BOARD_APP_I2C_DMAMUX   HPM_DMAMUX
#define BOARD_APP_I2C_DMA_SRC  HPM_DMA_SRC_I2C1

/* cam */
#define BOARD_CAM_I2C_BASE     HPM_I2C0
#define BOARD_CAM_I2C_CLK_NAME clock_i2c0
#define BOARD_SUPPORT_CAM_RESET
#define BOARD_SUPPORT_CAM_PWDN
#define BOARD_CAM_RST_GPIO_CTRL   HPM_GPIO0
#define BOARD_CAM_RST_GPIO_INDEX  GPIO_DI_GPIOA
#define BOARD_CAM_RST_GPIO_PIN    22
#define BOARD_CAM_PWDN_GPIO_CTRL  HPM_GPIO0
#define BOARD_CAM_PWDN_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_CAM_PWDN_GPIO_PIN   21

/* touch panel */
#define BOARD_CAP_I2C_BASE           (HPM_I2C0)
#define BOARD_CAP_I2C_CLK_NAME       clock_i2c0
#define BOARD_CAP_RST_GPIO           (HPM_GPIO0)
#define BOARD_CAP_RST_GPIO_INDEX     (GPIO_DI_GPIOY)
#define BOARD_CAP_RST_GPIO_PIN       (7)
#define BOARD_CAP_RST_GPIO_IRQ       (IRQn_GPIO0_Y)
#define BOARD_CAP_INTR_GPIO          (HPM_GPIO0)
#define BOARD_CAP_INTR_GPIO_INDEX    (GPIO_DI_GPIOY)
#define BOARD_CAP_INTR_GPIO_PIN      (6)
#define BOARD_CAP_INTR_GPIO_IRQ      (IRQn_GPIO0_Y)
#define BOARD_CAP_I2C_GPIO           HPM_GPIO0
#define BOARD_CAP_I2C_SDA_GPIO_INDEX (GPIO_DI_GPIOF)
#define BOARD_CAP_I2C_SDA_GPIO_PIN   (9)
#define BOARD_CAP_I2C_CLK_GPIO_INDEX (GPIO_DI_GPIOF)
#define BOARD_CAP_I2C_CLK_GPIO_PIN   (8)

/* i2s section */
#define BOARD_APP_I2S_BASE           HPM_I2S3
#define BOARD_APP_I2S_TX_DATA_LINE   I2S_DATA_LINE_2
#define BOARD_APP_I2S_RX_DATA_LINE   I2S_DATA_LINE_2
#define BOARD_APP_I2S_CLK_NAME       clock_i2s3
#define BOARD_APP_I2S_TX_DMA_REQ     HPM_DMA_SRC_I2S3_TX
#define BOARD_APP_I2S_IRQ            IRQn_I2S3
#define BOARD_APP_AUDIO_CLK_SRC      clock_source_pll3_clk0
#define BOARD_APP_AUDIO_CLK_SRC_NAME clk_pll3clk0

#define BOARD_MIC_I2S               HPM_I2S0
#define BOARD_MIC_I2S_CLK_NAME      clock_i2s0
#define BOARD_MIC_I2S_DATA_LINE     I2S_DATA_LINE_0
#define BOARD_MIC_I2S_RX_DMAMUX_SRC HPM_DMA_SRC_I2S0_RX

#define BOARD_SPEAKER_I2S               HPM_I2S1
#define BOARD_SPEAKER_I2S_CLK_NAME      clock_i2s1
#define BOARD_SPEAKER_I2S_DATA_LINE     I2S_DATA_LINE_0
#define BOARD_SPEAKER_I2S_TX_DMAMUX_SRC HPM_DMA_SRC_I2S1_TX

/* pdm selection */
#define BOARD_PDM_SINGLE_CHANNEL_MASK (0x02U)
#define BOARD_PDM_DUAL_CHANNEL_MASK   (0x22U)

/* i2c for i2s codec section */
#define BOARD_CODEC_I2C_BASE     HPM_I2C3
#define BOARD_CODEC_I2C_CLK_NAME clock_i2c3

/* dma section */
#define BOARD_APP_XDMA      HPM_XDMA
#define BOARD_APP_HDMA      HPM_HDMA
#define BOARD_APP_XDMA_IRQ  IRQn_XDMA
#define BOARD_APP_HDMA_IRQ  IRQn_HDMA
#define BOARD_APP_DMAMUX    HPM_DMAMUX
#define TEST_DMA_CONTROLLER HPM_XDMA
#define TEST_DMA_IRQ        IRQn_XDMA

/* gptmr section */
#define BOARD_GPTMR                   HPM_GPTMR2
#define BOARD_GPTMR_IRQ               IRQn_GPTMR2
#define BOARD_GPTMR_CHANNEL           0
#define BOARD_GPTMR_DMA_SRC           HPM_DMA_SRC_GPTMR2_0
#define BOARD_GPTMR_CLK_NAME          clock_gptmr2
#define BOARD_GPTMR_PWM               HPM_GPTMR2
#define BOARD_GPTMR_PWM_CHANNEL       0
#define BOARD_GPTMR_PWM_DMA_SRC       HPM_DMA_SRC_GPTMR2_0
#define BOARD_GPTMR_PWM_CLK_NAME      clock_gptmr2
#define BOARD_GPTMR_PWM_IRQ           IRQn_GPTMR2
#define BOARD_GPTMR_PWM_SYNC          HPM_GPTMR2
#define BOARD_GPTMR_PWM_SYNC_CHANNEL  1
#define BOARD_GPTMR_PWM_SYNC_CLK_NAME clock_gptmr2

/* gpio software filter*/
#define DEBOUNCE_THRESHOLD_IN_MS 150

/* pinmux section */
#define USING_GPIO0_FOR_GPIOZ
#ifndef USING_GPIO0_FOR_GPIOZ
#define BOARD_APP_GPIO_CTRL HPM_BGPIO
#define BOARD_APP_GPIO_IRQ  IRQn_BGPIO
#else
#define BOARD_APP_GPIO_CTRL HPM_GPIO0
#define BOARD_APP_GPIO_IRQ  IRQn_GPIO0_F
#endif

/* gpiom section */
#define BOARD_APP_GPIOM_BASE            HPM_GPIOM
#define BOARD_APP_GPIOM_USING_CTRL      HPM_FGPIO
#define BOARD_APP_GPIOM_USING_CTRL_NAME gpiom_core0_fast
/*
 * in errata, for gpiom, setting the ASSIGN register of GPIOF is invalid.
 * so need to configure GPIOE to make it effective at the same time.
 */
#define BOARD_LED_GPIOM_GPIO_INDEX GPIO_DI_GPIOE

/* spi section */
#define BOARD_APP_SPI_BASE              HPM_SPI3
#define BOARD_APP_SPI_CLK_NAME          clock_spi3
#define BOARD_APP_SPI_IRQ               IRQn_SPI3
#define BOARD_APP_SPI_SCLK_FREQ         (20000000UL)
#define BOARD_APP_SPI_ADDR_LEN_IN_BYTES (1U)
#define BOARD_APP_SPI_DATA_LEN_IN_BITS  (8U)
#define BOARD_APP_SPI_RX_DMA            HPM_DMA_SRC_SPI3_RX
#define BOARD_APP_SPI_TX_DMA            HPM_DMA_SRC_SPI3_TX
#define BOARD_SPI_CS_GPIO_CTRL          HPM_GPIO0
#define BOARD_SPI_CS_PIN                IOC_PAD_PE04
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
#define BOARD_APP_ADC16_CLK_BUS  (clk_adc_src_axi0)
#define BOARD_APP_ADC16_PMT_TRIG_CH ADC16_CONFIG_TRG0A

/* CAN section */
#define BOARD_APP_CAN_BASE HPM_MCAN3
#define BOARD_APP_CAN_IRQn IRQn_MCAN3

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

#define BOARD_CPU_FREQ (600000000UL)

/* LED */
#define BOARD_R_GPIO_CTRL  HPM_GPIO0
#define BOARD_R_GPIO_INDEX GPIO_DI_GPIOF
#define BOARD_R_GPIO_PIN   1
#define BOARD_G_GPIO_CTRL  HPM_GPIO0
#define BOARD_G_GPIO_INDEX GPIO_DI_GPIOF
#define BOARD_G_GPIO_PIN   2
#define BOARD_B_GPIO_CTRL  HPM_GPIO0
#define BOARD_B_GPIO_INDEX GPIO_DI_GPIOF
#define BOARD_B_GPIO_PIN   5

#define BOARD_RGB_RED   0
#define BOARD_RGB_GREEN (BOARD_RGB_RED + 1)
#define BOARD_RGB_BLUE  (BOARD_RGB_RED + 2)

#define BOARD_LED_GPIO_CTRL  BOARD_G_GPIO_CTRL
#define BOARD_LED_GPIO_INDEX BOARD_G_GPIO_INDEX
#define BOARD_LED_GPIO_PIN   BOARD_G_GPIO_PIN

#define BOARD_LED_OFF_LEVEL  0
#define BOARD_LED_ON_LEVEL   !BOARD_LED_OFF_LEVEL
#define BOARD_LED_TOGGLE_RGB 1

/* Key */
#define BOARD_APP_GPIO_INDEX GPIO_DI_GPIOF
#define BOARD_APP_GPIO_PIN   6
#define BOARD_BUTTON_PRESSED_VALUE 0

/* ACMP desction */
#define BOARD_ACMP             0
#define BOARD_ACMP_CHANNEL     ACMP_CHANNEL_CHN1
#define BOARD_ACMP_IRQ         0
#define BOARD_ACMP_PLUS_INPUT  ACMP_INPUT_DAC_OUT  /* use internal DAC */
#define BOARD_ACMP_MINUS_INPUT ACMP_INPUT_ANALOG_6 /* align with used pin */

#define BOARD_GWC_BASE         HPM_GWC0
#define BOARD_GWC_FUNC_IRQ     IRQn_GWCK0_FUNC
#define BOARD_GWC_ERR_IRQ      IRQn_GWCK0_ERR
#define BOARD_GWC_PIXEL_WIDTH  1920
#define BOARD_GWC_PIXEL_HEIGHT 1080

/* lcd section */
#define BOARD_LCD_BASE HPM_LCDC
#define BOARD_LCD_IRQ  IRQn_LCDC
#define clock_display  clock_lcd0

#ifndef BOARD_LCD_WIDTH
#define BOARD_LCD_WIDTH PANEL_SIZE_WIDTH
#endif
#ifndef BOARD_LCD_HEIGHT
#define BOARD_LCD_HEIGHT PANEL_SIZE_HEIGHT
#endif

#define BOARD_MULTI_PANEL_LVDS_LCDC_BASE HPM_LCDC1
#define BOARD_MULTI_PANEL_LVDS_LCDC_CLK clock_lcd1
#define BOARD_MULTI_PANEL_LVDS_NAME "cc10128007"

#define BOARD_MULTI_PANEL_MIPI_LCDC_BASE HPM_LCDC
#define BOARD_MULTI_PANEL_MIPI_LCDC_CLK clock_lcd0
#define BOARD_MULTI_PANEL_MIPI_NAME "mc10128007_31b"


/* pdma section */
#define BOARD_PDMA_BASE HPM_PDMA
#ifndef IRQn_PDMA_D0
#define IRQn_PDMA_D0 IRQn_PDMA
#endif

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

/* SDXC section */
#define BOARD_APP_SDCARD_SDXC_BASE              (HPM_SDXC1)
#define BOARD_APP_SDCARD_SDXC_IRQ               IRQn_SDXC1
#define BOARD_APP_SDCARD_SUPPORT_3V3            (1)
#define BOARD_APP_SDCARD_SUPPORT_1V8            (1)
#define BOARD_APP_SDCARD_SUPPORT_4BIT           (1)
#define BOARD_APP_SDCARD_SUPPORT_CARD_DETECTION (1)
#define BOARD_APP_SDCARD_SUPPORT_POWER_SWITCH   (1)
#define BOARD_APP_SDCARD_SUPPORT_VOLTAGE_SWITCH (1)

#define BOARD_APP_SDCARD_CARD_DETECTION_USING_GPIO (1)
#define BOARD_APP_SDCARD_POWER_SWITCH_USING_GPIO   (1)
#define BOARD_APP_SDCARD_VOLTAGE_SWITCH_USING_GPIO (1)
#if BOARD_APP_SDCARD_CARD_DETECTION_USING_GPIO
#define BOARD_APP_SDCARD_CARD_DETECTION_PIN     IOC_PAD_PD05
#define BOARD_APP_SDCARD_CARD_DETECTION_PIN_POL (1) /* pin value 0 means card was detected*/
#endif
#ifdef BOARD_APP_SDCARD_POWER_SWITCH_USING_GPIO
#define BOARD_APP_SDCARD_POWER_SWITCH_PIN IOC_PAD_PD07
#endif
#ifdef BOARD_APP_SDCARD_VOLTAGE_SWITCH_USING_GPIO
#define BOARD_APP_SDCARD_VSEL_PIN IOC_PAD_PD12
#endif
#define BOARD_APP_SDCARD_HOST_USING_IRQ (1)

#define BOARD_APP_EMMC_SDXC_BASE      (HPM_SDXC0)
#define BOARD_APP_EMMC_SDXC_IRQ       IRQn_SDXC0
#define BOARD_APP_EMMC_SUPPORT_3V3    (0)
#define BOARD_APP_EMMC_SUPPORT_1V8    (1)
#define BOARD_APP_EMMC_SUPPORT_4BIT   (0)
#define BOARD_APP_EMMC_SUPPORT_8BIT   (1)
#define BOARD_APP_EMMC_SUPPORT_DS     (1)
#define BOARD_APP_EMMC_HOST_USING_IRQ (0)


#define BOARD_APP_SDIO_SDXC_BASE                 (HPM_SDXC1)
#define BOARD_APP_SDIO_SDXC_IRQ                  IRQn_SDXC1
#define BOARD_APP_SDIO_SUPPORT_3V3               (1)
#define BOARD_APP_SDIO_SUPPORT_1V8               (0)
#define BOARD_APP_SDIO_SUPPORT_4BIT              (1)
#define BOARD_APP_SDIO_SUPPORT_POWER_SWITCH      (1)
#define BOARD_APP_SDIO_SUPPORT_VOLTAGE_SWITCH    (0)
#define BOARD_APP_SDIO_SUPPORT_CARD_DETECTION    (0)
#define BOARD_APP_SDIO_POWER_SWITCH_USING_GPIO   (1)
#define BOARD_APP_SDIO_VOLTAGE_SWITCH_USING_GPIO (0)
#define BOARD_APP_SDIO_POWER_SWITCH_USING_GPIO   (1)
#ifdef BOARD_APP_SDIO_POWER_SWITCH_USING_GPIO
#define BOARD_APP_SDIO_POWER_SWITCH_PIN IOC_PAD_PD07
#endif
#ifdef BOARD_APP_SDIO_VOLTAGE_SWITCH_USING_GPIO
#define BOARD_APP_SDIO_VSEL_PIN IOC_PAD_PD12
#endif


#define BOARD_APP_SDIO_WIFI_OOB_PORT       (HPM_GPIO0)
#define BOARD_APP_SDIO_WIFI_OOB_PIN        (IOC_PAD_PE16)
#define BOARD_APP_SDIO_WIFI_OOB_IRQ        IRQn_GPIO0_E
#define BOARD_APP_SDIO_WIFI_WL_REG_ON_PORT (HPM_GPIO0)
#define BOARD_APP_SDIO_WIFI_WL_REG_ON_PIN  (IOC_PAD_PE17)
#define BOARD_APP_SDIO_WIFI_SDXC_PORT      HPM_SDXC1

/* enet section */
#define BOARD_ENET_COUNT         (1U)
#define BOARD_ENET_PPS           HPM_ENET0
#define BOARD_ENET_PPS_IDX       enet_pps_0
#define BOARD_ENET_PPS_PTP_CLOCK clock_ptp0

#define BOARD_ENET_AUXI_SNAPSHOT           HPM_ENET0
#define BOARD_ENET_AUXI_SNAPSHOT_IDX       enet_ptp_auxi_snapshot_trigger_0
#define BOARD_ENET_AUXI_SNAPSHOT_PTP_CLOCK clock_ptp0

#define BOARD_ENET_RGMII_PHY_ITF        enet_inf_rgmii
#define BOARD_ENET_RGMII_RST_GPIO       HPM_GPIO0
#define BOARD_ENET_RGMII_RST_GPIO_INDEX GPIO_DO_GPIOD
#define BOARD_ENET_RGMII_RST_GPIO_PIN   (18U)
#define BOARD_ENET_RGMII                HPM_ENET0
#define BOARD_ENET_RGMII_TX_DLY         (0U)
#define BOARD_ENET_RGMII_RX_DLY         (0U)
#define BOARD_ENET_RGMII_PTP_CLOCK      clock_ptp0
#define BOARD_ENET_RGMII_PPS0_PINOUT    (1)

/* dram section */
#define DDR_TYPE_DDR2  (0U)
#define DDR_TYPE_DDR3L (1U)
#define BOARD_DDR_TYPE DDR_TYPE_DDR3L

#define BOARD_SDRAM_ADDRESS (0x40000000UL)
#if (BOARD_DDR_TYPE == DDR_TYPE_DDR2)
#define BOARD_SDRAM_SIZE (256UL * 1024UL * 1024UL)
#else
#define BOARD_SDRAM_SIZE (512UL * 1024UL * 1024UL)
#endif

/* Tamper Section */
#define BOARD_TAMP_ACTIVE_CH    4
#define BOARD_TAMP_LOW_LEVEL_CH 6

/* i2s over spi Section*/
#define BOARD_I2S_SPI_CS_GPIO_CTRL  HPM_GPIO0
#define BOARD_I2S_SPI_CS_GPIO_INDEX GPIO_DI_GPIOE
#define BOARD_I2S_SPI_CS_GPIO_PIN   27
#define BOARD_I2S_SPI_CS_GPIO_PAD   IOC_PAD_PE27

#define BOARD_GPTMR_I2S_MCLK          HPM_GPTMR2
#define BOARD_GPTMR_I2S_MCLK_CHANNEL  0
#define BOARD_GPTMR_I2S_MCLK_CLK_NAME clock_gptmr2

#define BOARD_GPTMR_I2S_LRCK          HPM_GPTMR2
#define BOARD_GPTMR_I2S_LRCK_CHANNEL  1
#define BOARD_GPTMR_I2S_LRCK_CLK_NAME clock_gptmr2

#define BOARD_GPTMR_I2S_BCLK          HPM_GPTMR2
#define BOARD_GPTMR_I2S_BLCK_CHANNEL  2
#define BOARD_GPTMR_I2S_BLCK_CLK_NAME clock_gptmr2

#define BOARD_GPTMR_I2S_FINSH          HPM_GPTMR2
#define BOARD_GPTMR_I2S_FINSH_IRQ      IRQn_GPTMR5
#define BOARD_GPTMR_I2S_FINSH_CHANNEL  3
#define BOARD_GPTMR_I2S_FINSH_CLK_NAME clock_gptmr2

#define BOARD_APP_CLK_REF_PIN_NAME "J20[7] (PD31)"
#define BOARD_APP_CLK_REF_CLK_NAME clock_ref1
#define BOARD_APP_CLK_REF_SRC_NAME clk_src_pll4_clk0
#define BOARD_APP_PLLCTLV2_TEST_PLL pllctlv2_pll4
#define BOARD_APP_PLLCTLV2_TEST_PLL_CLK pllctlv2_clk0
#define BOARD_APP_PLLCTLV2_TEST_PLL_NAME clk_pll4clk0

/* BGPR */
#define BOARD_BGPR HPM_BGPR

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

typedef void (*board_timer_cb)(void);

void board_init(void);
void board_init_console(void);

void board_init_uart(UART_Type *ptr);
uint32_t board_init_i2c_clock(I2C_Type *ptr);
void board_init_i2c(I2C_Type *ptr);
void board_init_can(MCAN_Type *ptr);

void board_init_gpio_pins(void);
void board_init_spi_pins(SPI_Type *ptr);
void board_init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void board_write_spi_cs(uint32_t pin, uint8_t state);
uint8_t board_get_led_gpio_off_level(void);
void board_init_led_pins(void);
void board_disable_output_rgb_led(uint8_t color);
void board_enable_output_rgb_led(uint8_t color);

void board_led_write(uint8_t state);
void board_led_toggle(void);

/* Initialize SoC overall clocks */
void board_init_clock(void);

uint32_t board_init_spi_clock(SPI_Type *ptr);
uint32_t board_init_can_clock(MCAN_Type *ptr);

void board_init_enet_pps_pins(ENET_Type *ptr);
void board_init_enet_pps_capture_pins(ENET_Type *ptr);
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

/* Initialize the UART clock */
uint32_t board_init_uart_clock(UART_Type *ptr);

void board_lcd_backlight(bool is_on);
void board_init_lcd(void);
void board_panel_para_to_lcdc_by_name(char *name, lcdc_config_t *config);
void board_panel_para_to_lcdc(lcdc_config_t *config);
void board_init_gwc(void);
void board_init_cap_touch(void);
void board_init_usb(USB_Type *ptr);

void board_init_sd_pins(SDXC_Type *ptr);
uint32_t board_sd_configure_clock(SDXC_Type *ptr, uint32_t freq, bool need_inverse);
void board_sd_switch_pins_to_1v8(SDXC_Type *ptr);
bool board_sd_detect_card(SDXC_Type *ptr);

uint32_t board_init_dao_clock(void);
uint32_t board_init_pdm_clock(void);
uint32_t board_config_i2s_clock(I2S_Type *ptr, uint32_t sample_rate);

void board_init_adc16_pins(void);
uint32_t board_init_adc_clock(void *ptr, bool clk_src_bus);

void board_init_cam_pins(void);
void board_write_cam_rst(uint8_t state);
void board_write_cam_pwdn(uint8_t state);
uint32_t board_init_cam_clock(CAM_Type *ptr);

void board_init_mipi_csi_cam_pins(void);
void board_write_mipi_csi_cam_rst(uint8_t state);

void board_init_gptmr_channel_pin(GPTMR_Type *ptr, uint32_t channel, bool as_comp);
void board_init_clk_ref_pin(void);
uint32_t board_init_gptmr_clock(GPTMR_Type *ptr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _HPM_BOARD_H */
