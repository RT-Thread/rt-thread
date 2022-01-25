/**********************************************************************
* $Id$      lpc177x_8x_pinsel.c         2011-06-02
*//**
* @file     lpc177x_8x_pinsel.c
* @brief    Contains all functions support for Pin-connection block
*           firmware library on LPC177x_8x
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
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup PINSEL
 * @{
 */

/* Includes ------------------------------------------------------------------- */
#include "lpc177x_8x_pinsel.h"

#define PINSEL_I2C_MODE_POS             (8)
#define PINSEL_I2C_MODE_NUMBITS         (2)
#define PINSEL_I2C_MODE_BITMASK         (0x03)

#define PINSEL_BASIC_MODE_POS           (3)
#define PINSEL_BASIC_MODE_NUMBITS       (2)
#define PINSEL_BASIC_MODE_BITMASK       (0x03)

#define PINSEL_DACEN_POS                (16)
#define PINSEL_DACEN_BITMASK            (0x01)
#define PINSEL_DACEN_NUMBITS            (1)

#define PINSEL_GLITCH_FILTER_POS                (8)
#define PINSEL_GLITCH_FILTER_BITMASK            (0x01)
#define PINSEL_GLITCH_FILTER_NUMBITS            (1)

#define PINSEL_ADMODE_POS               (7)
#define PINSEL_ADMODE_BITMASK           (0x01)
#define PINSEL_ADMODE_NUMBITS           (1)

/* Private Functions ---------------------------------------------------------- */

/*********************************************************************//**
 * @brief       Get pointer to GPIO peripheral due to GPIO port
 * @param[in]   portnum     Port Number value, should be in range from 0..3.
 * @param[in]   pinnum      Pin number value, should be in range from 0..31
 * @return      Pointer to GPIO peripheral
 **********************************************************************/
static uint32_t * PIN_GetPointer(uint8_t portnum, uint8_t pinnum)
{
    uint32_t *pPIN = NULL;
    pPIN = (uint32_t *)(LPC_IOCON_BASE + ((portnum * 32 + pinnum)*sizeof(uint32_t)));
    return pPIN;
}

/* Public Functions ----------------------------------------------------------- */
/** @addtogroup PINSEL_Public_Functions
 * @{
 */

/*********************************************************************//**
 * @brief       Setup the pin selection function
 * @param[in]   portnum PORT number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   funcnum Function number, should be range: 0..7
 *              - 0: Select GPIO (Default)
 *              - 1: Selects the 1st alternate function
 *              - 2: Selects the 2nd alternate function
 *              ...
 *              - 7: Selects the 7th alternate function
 * @return      None
 **********************************************************************/
void PINSEL_ConfigPin ( uint8_t portnum, uint8_t pinnum, uint8_t funcnum)
{
    uint32_t *pPIN = NULL;
    pPIN = PIN_GetPointer(portnum, pinnum);
    *pPIN &= 0x00000007;//Clear function bits
    *pPIN |= funcnum;
}


/*********************************************************************//**
 * @brief       Setup resistor mode for each pin
 * @param[in]   portnum PORT number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   modenum: Mode number, should be in range: 0..3
                - IOCON_MODE_PLAIN: Plain output
                - IOCON_MODE_PULLDOWN: Pull-down enable
                - IOCON_MODE_PULLUP: Pull-up enable
                - IOCON_MODE_REPEATER: Repeater mode
 * @return      None
 **********************************************************************/
void PINSEL_SetPinMode ( uint8_t portnum, uint8_t pinnum, PinSel_BasicMode modenum)
{
    uint32_t *pPIN = NULL;
    pPIN = PIN_GetPointer(portnum, pinnum);
    *(uint32_t *)pPIN &= ~(3<<3);//Clear function bits
    *(uint32_t *)pPIN |= modenum;
}

/*********************************************************************//**
 * @brief       Setup hysteresis for each pin
 * @param[in]   portnum Port number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   NewState new state of Hysteresis mode, should be:
 *              - ENABLE: Hysteresis enable
 *              - DISABLE: Hysteresis disable
 * @return      None
 **********************************************************************/
void PINSEL_SetHysMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState)
{
    uint32_t *pPIN = NULL;
    pPIN = PIN_GetPointer(portnum, pinnum);
    if(NewState == DISABLE)
    {
        *(uint32_t *)pPIN &= ~IOCON_HYS;//Clear hys bits
    }
    else
        *(uint32_t *)pPIN |= IOCON_HYS;
}

/*********************************************************************//**
 * @brief       Setup Slew rate for each pin
 * @param[in]   portnum Port number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   NewState new state of Slew rate control, should be:
 *              - ENABLE: Output slew rate control is enable
 *              - DISABLE: Output slew rate control is disable
 * @return      None
 **********************************************************************/
void PINSEL_SetSlewMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState)
{
    uint32_t *pPIN = NULL;
    pPIN = PIN_GetPointer(portnum, pinnum);
    if(NewState == DISABLE)
    {
        *(uint32_t *)pPIN &= ~IOCON_SLEW;//Clear hys bits
    }
    else
        *(uint32_t *)pPIN |= IOCON_SLEW;
}

/*********************************************************************//**
 * @brief       Setup Input Buffer for each pin
 * @param[in]   portnum Port number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   NewState new state of Input buffer mode, should be:
 *              - ENABLE: The input buffer is enable
 *              - DISABLE: The input buffer is disable
 * @return      None
 **********************************************************************/
void PINSEL_SetInBufMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState)
{
    uint32_t *pPIN = NULL;
    pPIN = PIN_GetPointer(portnum, pinnum);
    if(NewState == DISABLE)
    {
        *(uint32_t *)pPIN &= ~IOCON_INBUF;//Clear hys bits
    }
    else
        *(uint32_t *)pPIN |= IOCON_INBUF;
}

/*********************************************************************//**
 * @brief       Setup I2CMode for only pins that provide special I2C functionality
 * @param[in]   portnum Port number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   I2CMode I2C mode, should be:
 *              - IOCON_I2CMODE_FAST: Fast mode and standard I2C mode
 *              - IOCON_I2CMODE_OPENDRAIN: Open drain I/O
 *              - IOCON_I2CMODE_FASTPLUS: Fast Mode Plus I/O
 *              - IOCON_I2CMODE_HIGHOPENDRAIN: High drive open drain I/O
 * @return      None
 **********************************************************************/
void PINSEL_SetI2CMode(uint8_t portnum, uint8_t pinnum, PinSel_I2cMode I2CMode)
{
    uint32_t *pPIN = NULL;
    pPIN = PIN_GetPointer(portnum, pinnum);

    *(uint32_t *)pPIN &= ~(PINSEL_I2C_MODE_BITMASK<< PINSEL_I2C_MODE_POS);
    *(uint32_t *)pPIN |= (I2CMode << PINSEL_I2C_MODE_POS);
}

/*********************************************************************//**
 * @brief       Setup Open-drain mode in each pin
 * @param[in]   portnum Port number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   NewState new state of Open-drain mode:
 *              - DISABLE: Normal pin I/O mode
 *              - ENABLE: Open-drain enable
 * @return      None
 **********************************************************************/
void PINSEL_SetOpenDrainMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState)
{
    uint32_t *pPIN = NULL;
    pPIN = PIN_GetPointer(portnum, pinnum);
    if(NewState == DISABLE)
    {
        *(uint32_t *)pPIN &= ~IOCON_ODMODE;//Clear hys bits
    }
    else
    {
        *(uint32_t *)pPIN |= IOCON_ODMODE;
    }
}

/*********************************************************************//**
 * @brief       Enable the Analog mode for each pin (default is as Digital pins)
 * @param[in]   portnum PORT number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   enable: the state of the pin that is expected to run
                - ENABLE: Enable the DAC mode of the pin
                - DISABLE: Disable the DAC mode
 * @return      None
 **********************************************************************/
void PINSEL_SetAnalogPinMode (uint8_t portnum, uint8_t pinnum, uint8_t enable)
{
    uint32_t *pPIN = NULL;

    uint8_t condition = 0;

    condition = ((portnum == 0) && (pinnum == 12)) || ((portnum == 0) && (pinnum == 13))
                    | ((portnum == 0) && (pinnum <= 26) && (pinnum >= 23))
                    | ((portnum == 1) && (pinnum == 30)) || ((portnum == 1) && (pinnum == 31));

    if(!condition)
    {
        return;
    }

    pPIN = PIN_GetPointer(portnum, pinnum);

    //Clear this bit to set the pin to Analog mode
    *(uint32_t *)pPIN &= ~(PINSEL_ADMODE_BITMASK << PINSEL_ADMODE_POS);

    if(enable)
    {

    }
    else
    {
        *(uint32_t *)pPIN |= (1 << PINSEL_ADMODE_POS);//Set 16th bit to one
    }

    return;
}



/*********************************************************************//**
 * @brief       Choose the DAC mode for each pin
 * @param[in]   portnum PORT number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   enable: the state of the pin that is expected to run
                - ENABLE: Enable the DAC mode of the pin
                - DISABLE: Disable the DAC mode
 * @return      None
 **********************************************************************/
void PINSEL_DacEnable (uint8_t portnum, uint8_t pinnum, uint8_t enable)
{
    uint32_t *pPIN = NULL;

    // This setting is only for DAC pin (output pin)
    if(!((portnum == 0) && (pinnum == 26)))
    {
        return;
    }

    pPIN = PIN_GetPointer(portnum, pinnum);

    //Clear DAC Enable function bits
    *(uint32_t *)pPIN &= ~(PINSEL_DACEN_BITMASK << PINSEL_DACEN_POS);

    if(enable)
    {
        *(uint32_t *)pPIN |= (1 << PINSEL_DACEN_POS);//Set 16th bit to one
    }
    else
    {

    }

    return;
}

/*********************************************************************//**
 * @brief       Control the glitch filter for each pin
 * @param[in]   portnum PORT number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   enable: the state of the pin that is expected to run
                - ENABLE: The noise pulses below approximately 10ns are filtered out
                - DISABLE: No input filtering is done.
 * @return      None
 **********************************************************************/
void PINSEL_SetFilter (uint8_t portnum, uint8_t pinnum, uint8_t enable)
{
    uint32_t *pPIN = NULL;

    // This setting is only for DAC pin (output pin)
    if(!((portnum == 0) && ((pinnum == 7) || (pinnum == 8) || (pinnum == 9))))
    {
        return;
    }

    pPIN = PIN_GetPointer(portnum, pinnum);

    *(uint32_t *)pPIN |= (1 << 7);//Set 7th bit for normal operation following the UM1.0

    //Clear Filter bits
    *(uint32_t *)pPIN &= ~(PINSEL_GLITCH_FILTER_BITMASK << PINSEL_GLITCH_FILTER_POS);

    if(!enable)
    {
        *(uint32_t *)pPIN |= (1 << PINSEL_GLITCH_FILTER_POS);//Set 8th bit to one
    }
    else
    {

    }

    *pPIN = *pPIN;

    return;
}

/**
 * @}
 */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
