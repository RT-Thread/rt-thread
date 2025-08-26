/*
* Copyright 2025 NXP
*
* SPDX-License-Identifier: BSD-3-Clause
*/


#ifndef PIN_MUX_H
#define PIN_MUX_H

#if defined(__cplusplus)
extern "C" {
#endif

void BOARD_InitBootPins(void);
void BOARD_InitPins(void);
void BOARD_InitUART0Pins(void);
void BOARD_InitUART1Pins(void);
void BOARD_InitUART2Pins(void);
void BOARD_InitI2C0Pins(void);
void BOARD_InitI2C1Pins(void);

#if defined(__cplusplus)
}
#endif

#endif /* PIN_MUX_H */
