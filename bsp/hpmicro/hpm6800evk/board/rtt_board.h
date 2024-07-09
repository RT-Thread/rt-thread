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
#define APP_LED0_GPIO_INDEX GPIO_DI_GPIOF
#define APP_LED0_GPIO_PIN 1
#define APP_LED1_GPIO_CTRL HPM_GPIO0
#define APP_LED1_GPIO_INDEX GPIO_DI_GPIOF
#define APP_LED1_GPIO_PIN 2
#define APP_LED2_GPIO_CTRL HPM_GPIO0
#define APP_LED2_GPIO_INDEX GPIO_DI_GPIOF
#define APP_LED2_GPIO_PIN 5
#define APP_LED_ON (1)
#define APP_LED_OFF (0)



/* mchtimer section */
#define BOARD_MCHTMR_FREQ_IN_HZ (24000000UL)

/* CAN section */
#define BOARD_CAN_NAME                        "can3"
#define BOARD_CAN_HWFILTER_INDEX               (3U)

/* UART section */
#define BOARD_UART_NAME                        "uart3"
#define BOARD_UART_RX_BUFFER_SIZE              BSP_UART3_RX_BUFSIZE

/* eeprom section */
#define BOARD_EEPROM_I2C_NAME                  "i2c1"

#define BOARD_SD_NAME                          "sd1"
/* audio section */
#define BOARD_AUDIO_CODEC_I2C_NAME             "i2c3"
#define BOARD_AUDIO_CODEC_I2S_NAME             "i2s3"

#define IRQn_PendSV IRQn_DEBUG0

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
