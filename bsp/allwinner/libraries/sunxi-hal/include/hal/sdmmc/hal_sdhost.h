/**
  * @file  hal_sdhost.h
  * @author  ALLWINNERTECH IOT WLAN Team
  */

/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _DRIVER_CHIP_SDMMC_HAL_SDHOST_H_
#define _DRIVER_CHIP_SDMMC_HAL_SDHOST_H_

//#include "driver/chip/hal_def.h"
#include "hal/hal_gpio.h"
#include <stddef.h>
#include <stdint.h>
#include <kconfig.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SDC0 = 0,       /*!< SDC0 controller */
    SDC1 = 1,       /*!< SDC1 controller */
    SDC_NUM         /*!< only support 2 SD controller. */
} SDC_Port;

typedef enum {
    SDCGPIO_BAS = 0,
    SDCGPIO_DET = 1,
} HAL_SDCGPIOType;

typedef struct {
    uint8_t   data_bits;
    int8_t    has_detect_gpio;
    GPIO_Port detect_port;
    GPIO_Pin  detect_pin;
    uint16_t  detect_delay; /* delay interval (in ms) to wait power stable */
    GPIO_PinState   detect_pin_present_val;
} HAL_SDCGPIOCfg;

/** @bried Detect card callback if used CONFIG_DETECT_CARD. */
typedef void (*card_detect_cb)(uint32_t present);

/** @bried SDC Init Structure definition. */
typedef struct {
    uint16_t                debug_mask;
    uint8_t                 low_speed;
    uint8_t                 dma_use;
    uint32_t                pwr_mode;
#ifdef CONFIG_DETECT_CARD
    uint32_t                cd_mode;
/* NOTE: The specification advise that CARD_DETECT_BY_D3 is not a preferred
 *       mechanism for card detection. Moreover it won't work with MMC cards.
 *       And, this won't work with external pull-up resistors on the card interface.
 *       The preferred card detection mechanism is a mechanical switch on the card connector.
*/
#define CARD_DETECT_BY_GPIO_IRQ  (2)    /* mmc detected by gpio irq */
#define CARD_ALWAYS_PRESENT      (3)    /* mmc always present, without detect pin */
#define CARD_DETECT_BY_FS        (4)    /* mmc insert/remove by fs */
#define CARD_DETECT_BY_D3        (5)    /* mmc detected by data3 */

    card_detect_cb          cd_cb;  /* NOTE: should delay 500ms before rescan card to wait Voltage stable */
#endif
} SDC_InitTypeDef;

/**
 * @brief Initializes the SDC peripheral.
 * @param sdc_id:
 *        @arg sdc_id->SDC ID.
 * @param param:
 *        @arg param->[in] The configuration information.
 * @retval  SDC handler.
 */
extern struct mmc_host *hal_sdc_init(struct mmc_host *host);

/**
 * @brief DeInitializes the SDC peripheral.
 * @param sdc_id:
 *        @arg sdc_id-> SDC ID.
 * @retval  None.
 */
extern int32_t hal_sdc_deinit(uint32_t sdc_id);

extern struct mmc_host *hal_sdc_create(uint32_t sdc_id, SDC_InitTypeDef *param);
extern int32_t hal_sdc_destroy(struct mmc_host *host);

extern struct mmc_host *hal_sdc_open(uint32_t sdc_id);
extern uint32_t hal_sdc_close(uint32_t sdc_id);
extern void hal_sdc_set_high_speed(struct mmc_host *host);

extern int hal_sdc_init_timeout(void);

#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_CHIP_SDMMC_HAL_SDHOST_H_ */
