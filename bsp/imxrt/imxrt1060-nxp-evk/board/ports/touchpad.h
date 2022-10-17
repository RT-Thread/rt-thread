/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __TOUCHPAD_PORT_H__
#define __TOUCHPAD_PORT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fsl_common.h"
#include "clock_config.h"
#include "fsl_lpi2c.h"
#include "fsl_gpio.h"

/* @Brief Board touch panel configuration */
#define BOARD_TOUCH_I2C_BASEADDR LPI2C1
#define BOARD_TOUCH_RST_GPIO     GPIO1
#define BOARD_TOUCH_RST_PIN      2
#define BOARD_TOUCH_INT_GPIO     GPIO1
#define BOARD_TOUCH_INT_PIN      11

void BOARD_Delay(uint32_t ms);
void BOARD_LPI2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subaddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize);
status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize);
status_t BOARD_LPI2C_SendSCCB(LPI2C_Type *base,
                              uint8_t deviceAddress,
                              uint32_t subAddress,
                              uint8_t subaddressSize,
                              uint8_t *txBuff,
                              uint8_t txBuffSize);
status_t BOARD_LPI2C_ReceiveSCCB(LPI2C_Type *base,
                                 uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subaddressSize,
                                 uint8_t *rxBuff,
                                 uint8_t rxBuffSize);
status_t BOARD_Touch_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Touch_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
