/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_SD_H__
#define AB32VG1_HAL_SD_H__

#include "ab32vg1_hal_def.h"
#include "ab32vg1_ll_sdio.h"
#include <stdbool.h>

struct sd_card_info
{
    uint32_t rca;           /*!< Specifies the Relative Card Address        */
    uint32_t capacity;      /*!< Specifies the capacity of the card         */
    uint8_t  abend;         /*!< Specifies if the card is abnormal end      */
    uint8_t  flag_sdhc;     /*!< Specifies if the card is SDHC card         */
    uint8_t  type;          /*!< Specifies the card type                    */
    uint8_t  state;         /*!< Specifies the card state                   */
    uint8_t  rw_state;      /*!< Specifies the last r/w state of the card   */
};
typedef struct sd_card_info* sd_card_info_t;

struct sd_cfg
{
    uint16_t go_ready_retry;
    uint8_t  identification_retry;
    uint8_t  rw_retry;
    uint8_t  rw_init_retry;
    uint8_t  stop_retry;
    uint8_t  rw_need_stop;
};

struct sd_handle
{
    hal_sfr_t               instance;
    struct sdio_init        init;
    struct sd_card_info     sdcard;
    struct sd_cfg           cfg;
};
typedef struct sd_handle* sd_handle_t;

#define SD0N                (0x00u)

// #define CARD_SDSC           (0x00u)
// #define CARD_SDHC           (0x01u)
// #define CARD_SECURED        (0x03u)

enum
{
    CARD_INVAL = 0x00,
    CARD_V1,
    CARD_V2,
    CARD_MMC
};

enum
{
    HAL_SD_RW_STATE_IDLE = 0x00,
    HAL_SD_RW_STATE_READ,
    HAL_SD_RW_STATE_WRITE,
};

enum
{
    HAL_SD_STATE_RESET = 0x00,
    HAL_SD_STATE_NEW,
    HAL_SD_STATE_OK,
    HAL_SD_STATE_INVAL,
};

#define SDMMC_CHECK_PATTERM         (0x000001AAu)

#define SDMMC0_BASE     ((hal_sfr_t)&SD0CON)

/* Initialization functions */
hal_error_t hal_sd_init(sd_handle_t hsd);
void hal_sd_deinit(uint32_t sdx);
void hal_sd_mspinit(sd_handle_t hsd);

hal_error_t hal_sd_control(uint32_t control, uint32_t arg);
void hal_sd_write(uint32_t sdx, uint32_t data);
bool hal_sd_read(sd_handle_t hsd, void *buf, uint32_t lba);
// void hal_uart_write_it(uint32_t uartx, uint8_t data);
// uint8_t hal_uart_read_it(uint32_t uartx);

#endif
