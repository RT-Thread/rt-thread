/*
 * Copyright 2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    peripherals.h
 * @brief   Peripherals initialization header file.
 */

/* This is an empty template for board specific configuration.*/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
 * @brief 	Initialize peripherals specific settings.
 */
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _PERIPHERALS_H_ */
