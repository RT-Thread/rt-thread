/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_SD_H__
#define AB32VG1_HAL_SD_H__

#include "ab32vg1_hal_def.h"

struct sd_init
{
    // uint8_t
};

struct sd_card_info
{
    uint32_t rca;           /*!< Specifies the Relative Card Address    */
    uint8_t  type;          /*!< Specifies the card type                */
};
typedef struct sd_card_info* sd_card_info_t;

struct sd_handle
{
    hal_sfr_t               instance;
    struct sd_init          init;
    struct sd_card_info     sdcard;
};
typedef struct sd_handle* sd_handle_t;

#define SD0N            (0x00u)

#define CARD_V1         (0x01u)
#define CARD_V2         (0x02u)
#define CARD_MMC        (0x03u)

#define SDMMC_CHECK_PATTERM         (0x000001AAu)

/* Initialization functions */
hal_error_t hal_sd_init(sd_handle_t hsd);
void hal_sd_deinit(uint32_t sdx);
void hal_sd_mspinit(sd_handle_t hsd);

hal_error_t hal_sd_control(uint32_t control, uint32_t arg);
void hal_sd_write(uint32_t sdx, uint32_t data);
uint32_t hal_sd_read(uint32_t sdx);
// void hal_uart_write_it(uint32_t uartx, uint8_t data);
// uint8_t hal_uart_read_it(uint32_t uartx);

#endif
