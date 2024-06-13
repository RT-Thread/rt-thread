/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _RTT_BOARD_H
#define _RTT_BOARD_H
#include "hpm_common.h"
#include "hpm_soc.h"

/* gpio section */
#define APP_LED0_GPIO_CTRL HPM_GPIO0
#define APP_LED0_GPIO_INDEX GPIO_DI_GPIOB
#define APP_LED0_GPIO_PIN 11
#define APP_LED1_GPIO_CTRL HPM_GPIO0
#define APP_LED1_GPIO_INDEX GPIO_DI_GPIOB
#define APP_LED1_GPIO_PIN 12
#define APP_LED2_GPIO_CTRL HPM_GPIO0
#define APP_LED2_GPIO_INDEX GPIO_DI_GPIOB
#define APP_LED2_GPIO_PIN 13
#define APP_LED_ON (0)
#define APP_LED_OFF (1)



/* mchtimer section */
#define BOARD_MCHTMR_FREQ_IN_HZ (24000000UL)

/* SPI WIFI section */
#define RW007_RST_PIN                         (IOC_PAD_PE02)
#define RW007_INT_BUSY_PIN                    (IOC_PAD_PE01)
#define RW007_CS_PIN                          (IOC_PAD_PE03)
#define RW007_CS_GPIO                         (HPM_GPIO0)
#define RW007_SPI_BUS_NAME                    "spi1"


/* CAN section */
#define BOARD_CAN_NAME                        "can0"
#define BOARD_CAN_HWFILTER_INDEX               (0U)

/* UART section */
#define BOARD_UART_NAME                        "uart13"
#define BOARD_UART_RX_BUFFER_SIZE              BSP_UART13_RX_BUFSIZE

/* eeprom section */
#define BOARD_EEPROM_I2C_NAME                  "i2c0"

#define BOARD_SD_NAME                          "sd1"
/* audio section */
#define BOARD_AUDIO_CODEC_I2C_NAME             "i2c0"
#define BOARD_AUDIO_CODEC_I2S_NAME             "i2s0"

/* PWM section */
#define BOARD_PWM_NAME                        "pwm2"
#define BOARD_PWM_CHANNEL                     (0)

#define IRQn_PendSV IRQn_DEBUG_0

/***************************************************************
 *
 * RT-Thread related definitions
 *
 **************************************************************/
extern unsigned int __heap_start__;
extern unsigned int __heap_end__;

#define RT_HW_HEAP_BEGIN ((void*)&__heap_start__)
#define RT_HW_HEAP_END ((void*)&__heap_end__)


typedef struct {
    uint16_t vdd;
    uint8_t bus_width;
    uint8_t drive_strength;
}sdxc_io_cfg_t;


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */


void app_init_led_pins(void);
void app_led_write(uint32_t index, bool state);
void app_init_usb_pins(void);


#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _RTT_BOARD_H */
