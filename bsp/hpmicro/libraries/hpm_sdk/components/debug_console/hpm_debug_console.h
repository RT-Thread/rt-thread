/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_DEBUG_CONSOLE_H
#define _HPM_DEBUG_CONSOLE_H
#include <stdio.h>
#include "hpm_common.h"

typedef enum console_type {
    console_type_uart = 0,
} console_type_t;

typedef struct {
    console_type_t type;
    uint32_t base;
    uint32_t src_freq_in_hz;
    uint32_t baudrate;
} console_config_t;


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

hpm_stat_t console_init(console_config_t *cfg);

uint8_t console_receive_byte(void);

void console_send_byte(uint8_t c);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _HPM_CONSOLE_H */
