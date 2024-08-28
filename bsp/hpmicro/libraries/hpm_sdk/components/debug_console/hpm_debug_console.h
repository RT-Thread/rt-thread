/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_DEBUG_CONSOLE_H
#define _HPM_DEBUG_CONSOLE_H
#include "hpm_common.h"

#define CONSOLE_TYPE_UART 0

typedef struct {
    uint32_t type;
    uint32_t base;
    uint32_t src_freq_in_hz;
    uint32_t baudrate;
} console_config_t;


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

hpm_stat_t console_init(console_config_t *cfg);

uint8_t console_receive_byte(void);
uint8_t console_try_receive_byte(void);
void console_send_byte(uint8_t c);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _HPM_CONSOLE_H */
