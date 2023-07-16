//*****************************************************************************
//
// bl_i2c.h - Definitions for the I2C transport functions.
//
// Copyright (c) 2006-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#ifndef __BL_I2C_H__
#define __BL_I2C_H__

//*****************************************************************************
//
// This section maps the defines to default for I2C Boot Loader for legacy
// projects
//
//*****************************************************************************
#ifndef I2C_CLOCK_ENABLE
#define I2C_CLOCK_ENABLE        SYSCTL_RCGCI2C_R0
#endif

#ifndef I2Cx
#define I2Cx                    I2C0
#endif

#ifndef I2C_SCLPIN_CLOCK_ENABLE
#define I2C_SCLPIN_CLOCK_ENABLE SYSCTL_RCGCGPIO_R1
#endif

#ifndef I2C_SCLPIN_BASE
#define I2C_SCLPIN_BASE         GPIOB
#endif

#ifndef I2C_SCLPIN_PCTL
#define I2C_SCLPIN_PCTL         0x2
#endif

#ifndef I2C_SCLPIN_POS
#define I2C_SCLPIN_POS          2
#endif

#ifndef I2C_SDAPIN_CLOCK_ENABLE
#define I2C_SDAPIN_CLOCK_ENABLE SYSCTL_RCGCGPIO_R1
#endif

#ifndef I2C_SDAPIN_BASE
#define I2C_SDAPIN_BASE         GPIOB
#endif

#ifndef I2C_SDAPIN_PCTL
#define I2C_SDAPIN_PCTL         0x2
#endif

#ifndef I2C_SDAPIN_POS
#define I2C_SDAPIN_POS          3
#endif

//*****************************************************************************
//
// This defines the I2C clock pin that is being used by the boot loader.
//
//*****************************************************************************
#define I2C_CLK                 (1 << I2C_SCLPIN_POS)
#define I2C_CLK_PCTL            (I2C_SCLPIN_PCTL << (4 * I2C_SCLPIN_POS))

//*****************************************************************************
//
// This defines the I2C data pin that is being used by the boot loader.
//
//*****************************************************************************
#define I2C_DATA                (1 << I2C_SDAPIN_POS)
#define I2C_DATA_PCTL           (I2C_SDAPIN_PCTL << (4 * I2C_SDAPIN_POS))

//*****************************************************************************
//
// I2C Transport APIs
//
//*****************************************************************************
extern void I2CSend(const uint8_t *pui8Data, uint32_t ui32Size);
extern void I2CReceive(uint8_t *pui8Data, uint32_t ui32Size);
extern void I2CFlush(void);

//*****************************************************************************
//
// Define the transport functions if the I2C port is being used.
//
//*****************************************************************************
#ifdef I2C_ENABLE_UPDATE
#define SendData                I2CSend
#define FlushData               I2CFlush
#define ReceiveData             I2CReceive
#endif

#endif // __BL_I2C_H__
