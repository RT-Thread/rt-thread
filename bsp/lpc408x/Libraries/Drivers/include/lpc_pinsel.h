/**********************************************************************
* $Id$      lpc_pinsel.h            2011-06-02
*//**
* @file     lpc_pinsel.h
* @brief    Contains all macro definitions and function prototypes
*           support for Pin-connection block firmware library on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup PINSEL    PINSEL (Pin Selection)
 * @ingroup LPC_CMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC_PINSEL_H
#define __LPC_PINSEL_H

/* Includes ------------------------------------------------------------------- */
#include "LPC407x_8x_177x_8x.h"
#include "lpc_types.h"


/* Public Macros -------------------------------------------------------------- */
/** @defgroup PINSEL_Public_Macros PINSEL Public Macros
 * @{
 */

/* Macros define IOCON bits*/

/** Selects pin functions */
#define IOCON_FUNC_POS              (0)
#define IOCON_FUNC_MASK             (0x07<<IOCON_FUNC_POS)

/** Selects output function mode (on-chip pull-up/pull-down resistor control */
#define IOCON_MODE_POS              (3)
#define IOCON_MODE_MASK             (0x03<<IOCON_MODE_POS)
#define IOCON_MODE_PLAIN                ((0<<IOCON_MODE_POS))
#define IOCON_MODE_PULLDOWN     ((1<<IOCON_MODE_POS))
#define IOCON_MODE_PULLUP           ((2<<IOCON_MODE_POS))
#define IOCON_MODE_REPEATER         ((3<<IOCON_MODE_POS))

/** Hysteresis */
#define IOCON_HYS_POS               (5)
#define IOCON_HYS_MASK              (0x01<<IOCON_HYS_POS)
#define IOCON_HYS_ENABLE                ((1<<IOCON_HYS_POS))

/** Input polarity */
#define IOCON_INVERT_POS                (6)
#define IOCON_INVERT_MASK           (0x01<<IOCON_INVERT_POS)
#define IOCON_INVERT_INPUT          (1<<IOCON_INVERT_POS)

/** Selects Analog/Digital mode */
#define IOCON_ADMODE_POS            (7)
#define IOCON_ADMODE_MASK           (0x01<<IOCON_ADMODE_POS)
#define IOCON_ANALOG_MODE           (0<<IOCON_ADMODE_POS)
#define IOCON_DIGITIAL_MODE         (1<<IOCON_ADMODE_POS)

/* Controls Glitch Filter */
#define IOCON_FILTER_POS                (8)
#define IOCON_FILTER_MASK               (0x01<<IOCON_FILTER_POS)
#define IOCON_10ns_FILTER_ENABLE            (0<<IOCON_FILTER_POS)
#define IOCON_10ns_FILTER_DISABLE           (1<<IOCON_FILTER_POS)

/** I2C 50ns glitch filter and slew rate control */ 
#define IOCON_HS_POS                    (8)
#define IOCON_HS_MASK               (0x01<<IOCON_HS_POS)
#define IOCON_I2C_FILTER_ENABLE     (0<<IOCON_HS_POS)
#define IOCON_I2C_FILTER_DISABLE        (1<<IOCON_HS_POS)

/** Driver Output Slew Rate Control*/
#define IOCON_SLEW_POS              (9)
#define IOCON_SLEW_MASK             (0x01<<IOCON_SLEW_POS)
#define IOCON_SLEW_ENABLE           ((1<<IOCON_SLEW_POS))

/** Controls sink current capability of the pin*/
#define IOCON_HIDRIVE_POS               (9)
#define IOCON_HIDRIVE_MASK          (0x01<<IOCON_HIDRIVE_POS)
#define IOCON_I2CMODE_FASTPLUS      (1<<IOCON_HIDRIVE_POS)

/** Controls open-drain mode */
#define IOCON_OD_POS                    (10)
#define IOCON_OD_MASK               (0x01<<IOCON_OD_POS)
#define IOCON_OPENDRAIN_MODE        (1<<IOCON_OD_POS)

/** DAC enable control */
#define IOCON_DACEN_POS             (16)
#define IOCON_DACEN_MASK            (0x01<<IOCON_DACEN_POS)
#define IOCON_DAC_ENABLE                (1<<IOCON_DACEN_POS)

/* Macros define for Return Code */
typedef    int32_t      PINSEL_RET_CODE;
#define PINSEL_RET_OK               (0)
#define PINSEL_RET_INVALID_PIN      (0x10000001)
#define PINSEL_RET_NOT_SUPPORT      (0x10000002)
#define PINSEL_RET_ERR              (-1)

/**
 * @}
 */

/** @defgroup PINSEL_Public_Types PINSEL Public Types
 * @{
 */
 

typedef enum
{
    PINSEL_BASICMODE_PLAINOUT  = 0, /**< Plain output */
    PINSEL_BASICMODE_PULLDOWN,      /**< Pull-down enabled */
    PINSEL_BASICMODE_PULLUP,        /**< Pull-up enabled (default) */
    PINSEL_BASICMODE_REPEATER       /**< Repeater mode */
}PinSel_BasicMode;

typedef enum
{
    /** Fast mode (400 kHz clock rate) and standard (100 kHz clock rate) */
    PINSEL_I2CMODE_FAST_STANDARD  = 0,
    /** Open drain I/O (not I2C). No glitch filter, 3 mA typical output drive */
    PINSEL_I2CMODE_OPENDRAINIO,
    /** Fast Mode Plus I2C. This includes a filter for <50 ns glitches */
    PINSEL_I2CMODE_FASTMODEPLUS,
}PinSel_I2cMode;

typedef enum
{
    /** Type D IOCON registers */
    PINSEL_PIN_TYPE_D,
    /** Type A IOCON registers */
    PINSEL_PIN_TYPE_A,
    /** Type U IOCON registers */
    PINSEL_PIN_TYPE_U,
    /** Type I IOCON registers */
    PINSEL_PIN_TYPE_I,
    /** Type W IOCON registers */
    PINSEL_PIN_TYPE_W,
    /** Unknown type */
    PINSEL_PIN_TYPE_UNKNOWN,
}PinSel_PinType;


/**
 * @}
 */
 

/* Public Functions ----------------------------------------------------------- */
/** @defgroup PINSEL_Public_Functions PINSEL Public Functions
 * @{
 */
 PinSel_PinType       PINSEL_GetPinType(uint8_t portnum, uint8_t pinnum);
PINSEL_RET_CODE PINSEL_ConfigPin(uint8_t portnum, uint8_t pinnum, uint8_t funcnum);
PINSEL_RET_CODE PINSEL_SetPinMode(uint8_t portnum, uint8_t pinnum, PinSel_BasicMode modenum);
PINSEL_RET_CODE PINSEL_SetHysMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
PINSEL_RET_CODE PINSEL_SetInvertInput(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
PINSEL_RET_CODE PINSEL_SetSlewMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
PINSEL_RET_CODE PINSEL_SetI2CMode(uint8_t portnum, uint8_t pinnum, PinSel_I2cMode I2CMode);
PINSEL_RET_CODE PINSEL_SetOpenDrainMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
PINSEL_RET_CODE PINSEL_SetAnalogPinMode (uint8_t portnum, uint8_t pinnum, uint8_t enable);
PINSEL_RET_CODE PINSEL_DacEnable (uint8_t portnum, uint8_t pinnum, uint8_t enable);
PINSEL_RET_CODE PINSEL_SetFilter (uint8_t portnum, uint8_t pinnum, uint8_t enable);
PINSEL_RET_CODE PINSEL_SetI2CFilter (uint8_t portnum, uint8_t pinnum, uint8_t enable);


/**
 * @}
 */

#endif /* LPC_PINSEL_H */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

