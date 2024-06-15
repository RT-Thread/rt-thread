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
#include <drv_gpio.h>

/* gpio section */
#define APP_LED0_PIN_NUM GET_PIN(A, 10)
#define APP_LED_ON (1)
#define APP_LED_OFF (0)



/* mchtimer section */
#define BOARD_MCHTMR_FREQ_IN_HZ (24000000UL)

/* CAN section */
#define BOARD_CAN_NAME                        "can0"
#define BOARD_CAN_HWFILTER_INDEX              (0U)

/* UART section */
#define BOARD_UART_NAME                        "uart2"
#define BOARD_UART_RX_BUFFER_SIZE              BSP_UART2_RX_BUFSIZE

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

void app_init_led_pins(void);
void app_led_write(uint32_t index, bool state);
void app_init_usb_pins(void);

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */




#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _RTT_BOARD_H */
