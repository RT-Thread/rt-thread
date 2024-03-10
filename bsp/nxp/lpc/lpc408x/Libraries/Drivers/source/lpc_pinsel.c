/**********************************************************************
* $Id$      lpc_pinsel.c            2011-06-02
*//**
* @file     lpc_pinsel.c
* @brief    Contains all functions support for Pin-connection block
*           firmware library on LPC
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
/** @addtogroup PINSEL
 * @{
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _PINSEL

/* Includes ------------------------------------------------------------------- */
#include "lpc_pinsel.h"

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
 * @brief       Get type of a pin.
 * @param[in]   portnum PORT number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @return      Port type:
 *              - PINSEL_PIN_TYPE_D
 *              - PINSEL_PIN_TYPE_A
 *              - PINSEL_PIN_TYPE_I
 *              - PINSEL_PIN_TYPE_W
 *              - PINSEL_PIN_TYPE_U   
 *              - PINSEL_PIN_TYPE_UNKNOWN: Invalid pin
 **********************************************************************/
PinSel_PinType PINSEL_GetPinType(uint8_t portnum, uint8_t pinnum)
{
    PinSel_PinType Ret = PINSEL_PIN_TYPE_UNKNOWN;
    switch(portnum)
    {
        case 0:
            if((pinnum <=6)||
                ((pinnum >= 10)&&(pinnum <=11))||
                ((pinnum >= 14)&&(pinnum <=22)))
                Ret = PINSEL_PIN_TYPE_D;
            else if ((pinnum == 12)||(pinnum==13)||
                    ((pinnum >= 23)&&(pinnum <=26)))
                Ret = PINSEL_PIN_TYPE_A;
            else if ((pinnum == 29) || (pinnum==30)|| (pinnum==31))
                Ret = PINSEL_PIN_TYPE_U;
            else if ((pinnum == 27) || (pinnum==28))
                Ret = PINSEL_PIN_TYPE_I;
            else if ((pinnum == 7) || (pinnum==8)|| (pinnum==9))
                Ret = PINSEL_PIN_TYPE_W;
            break;
        case 1:
            if(pinnum <=29)
                Ret = PINSEL_PIN_TYPE_D;
            else if ((pinnum == 30) || (pinnum==31))
                Ret = PINSEL_PIN_TYPE_A;
            break;
        case 2:
        case 3:
        case 4:
            Ret = PINSEL_PIN_TYPE_D;
            break;
        case 5:
            if((pinnum <=1)||
                (pinnum == 4))
                Ret = PINSEL_PIN_TYPE_D;
            else if ((pinnum == 2) || (pinnum==3))
                Ret = PINSEL_PIN_TYPE_I;
            break;
        default:
            break;
    }

    return Ret;
}

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
 * @return      PINSEL Return Code
 *              - PINSEL_RET_INVALID_PIN
 *              - PINSEL_RET_OK
 **********************************************************************/
PINSEL_RET_CODE PINSEL_ConfigPin ( uint8_t portnum, uint8_t pinnum, uint8_t funcnum)
{
    uint32_t *pPIN = NULL;
    PinSel_PinType type = PINSEL_GetPinType(portnum,pinnum);

    if(type == PINSEL_PIN_TYPE_UNKNOWN)
        return PINSEL_RET_INVALID_PIN;
    
    pPIN = PIN_GetPointer(portnum, pinnum);
    *pPIN &= ~IOCON_FUNC_MASK;//Clear function bits
    *pPIN |= funcnum&IOCON_FUNC_MASK;

    return PINSEL_RET_OK;
}


/*********************************************************************//**
 * @brief       Setup resistor mode for pin of type D,A,W
 * @param[in]   portnum PORT number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   modenum: Mode number, should be in range: 0..3
                - PINSEL_BASICMODE_PLAINOUT: Plain output
                - PINSEL_BASICMODE_PULLDOWN: Pull-down enable
                - PINSEL_BASICMODE_PULLUP: Pull-up enable
                - PINSEL_BASICMODE_REPEATER: Repeater mode
 * @return      PINSEL Return Code
 *              - PINSEL_RET_INVALID_PIN
 *              - PINSEL_RET_NOT_SUPPORT
 *              - PINSEL_RET_OK
 **********************************************************************/
PINSEL_RET_CODE PINSEL_SetPinMode ( uint8_t portnum, uint8_t pinnum, PinSel_BasicMode modenum)
{
    uint32_t *pPIN = NULL;
    PinSel_PinType type = PINSEL_GetPinType(portnum,pinnum);

    if(type == PINSEL_PIN_TYPE_UNKNOWN)
        return PINSEL_RET_INVALID_PIN;
    if((type != PINSEL_PIN_TYPE_D )&&
        (type != PINSEL_PIN_TYPE_A )&&
        (type != PINSEL_PIN_TYPE_W))
        return PINSEL_RET_NOT_SUPPORT;
    
    pPIN = PIN_GetPointer(portnum, pinnum);
    *(uint32_t *)pPIN &= ~(IOCON_MODE_MASK);//Clear function bits
    *(uint32_t *)pPIN |= (modenum << IOCON_MODE_POS)&IOCON_MODE_MASK;

    return PINSEL_RET_OK;
}

/*********************************************************************//**
 * @brief       Setup hysteresis for pin of type D, W
 * @param[in]   portnum Port number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   NewState new state of Hysteresis mode, should be:
 *              - ENABLE: Hysteresis enable
 *              - DISABLE: Hysteresis disable
 * @return      PINSEL Return Code
 *              - PINSEL_RET_INVALID_PIN
 *              - PINSEL_RET_NOT_SUPPORT
 *              - PINSEL_RET_OK
 **********************************************************************/
PINSEL_RET_CODE PINSEL_SetHysMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState)
{
    uint32_t *pPIN = NULL;
    PinSel_PinType type = PINSEL_GetPinType(portnum,pinnum);

    if(type == PINSEL_PIN_TYPE_UNKNOWN)
        return PINSEL_RET_INVALID_PIN;
    if((type != PINSEL_PIN_TYPE_D )&&
        (type != PINSEL_PIN_TYPE_W))
        return PINSEL_RET_NOT_SUPPORT;
    
    pPIN = PIN_GetPointer(portnum, pinnum);
    if(NewState == DISABLE)
    {
        *(uint32_t *)pPIN &= ~IOCON_HYS_ENABLE;//Clear hys bits
    }
    else
        *(uint32_t *)pPIN |= IOCON_HYS_ENABLE;

    return PINSEL_RET_OK;
}
/*********************************************************************//**
 * @brief       Setup input polarity for pin of type A,I,D,W
 * @param[in]   portnum Port number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   NewState new state of Invert mode, should be:
 *              - ENABLE: Input is inverted.
 *              - DISABLE: Input isn't inverted.
 * @return      PINSEL Return Code
 *              - PINSEL_RET_INVALID_PIN
 *              - PINSEL_RET_NOT_SUPPORT
 *              - PINSEL_RET_OK
 **********************************************************************/
PINSEL_RET_CODE PINSEL_SetInvertInput(uint8_t portnum, uint8_t pinnum, FunctionalState NewState)
{
    uint32_t *pPIN = NULL;
    PinSel_PinType type = PINSEL_GetPinType(portnum,pinnum);

    if(type == PINSEL_PIN_TYPE_UNKNOWN)
        return PINSEL_RET_INVALID_PIN;
    if(type== PINSEL_PIN_TYPE_U)
        return PINSEL_RET_NOT_SUPPORT;
    
    pPIN = PIN_GetPointer(portnum, pinnum);
    if(NewState == DISABLE)
    {
        *(uint32_t *)pPIN &= ~IOCON_INVERT_INPUT;//Clear hys bits
    }
    else
        *(uint32_t *)pPIN |= IOCON_INVERT_INPUT;

    return PINSEL_RET_OK;
}

/*********************************************************************//**
 * @brief       Setup Slew rate for pin of type D,W
 * @param[in]   portnum Port number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   NewState new state of Slew rate control, should be:
 *              - ENABLE: Output slew rate control is enable
 *              - DISABLE: Output slew rate control is disable
 * @return      PINSEL Return Code
 *              - PINSEL_RET_INVALID_PIN
 *              - PINSEL_RET_NOT_SUPPORT
 *              - PINSEL_RET_OK
 **********************************************************************/
PINSEL_RET_CODE PINSEL_SetSlewMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState)
{
    uint32_t *pPIN = NULL;
    PinSel_PinType type = PINSEL_GetPinType(portnum,pinnum);

    if(type == PINSEL_PIN_TYPE_UNKNOWN)
        return PINSEL_RET_INVALID_PIN;
    if((type!= PINSEL_PIN_TYPE_D) &&
        (type!= PINSEL_PIN_TYPE_W))
        return PINSEL_RET_NOT_SUPPORT;
    
    pPIN = PIN_GetPointer(portnum, pinnum);
    if(NewState == DISABLE)
    {
        *(uint32_t *)pPIN &= ~IOCON_SLEW_ENABLE;//Clear hys bits
    }
    else
        *(uint32_t *)pPIN |= IOCON_SLEW_ENABLE;

    return PINSEL_RET_OK;
}

/*********************************************************************//**
 * @brief       Setup I2CMode for only pins that provide special I2C functionality
 * @param[in]   portnum Port number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   I2CMode I2C mode, should be:
 *              - PINSEL_I2CMODE_FAST_STANDARD: Fast mode and standard I2C mode
 *              - PINSEL_I2CMODE_OPENDRAINIO: Open drain I/O
 *              - PINSEL_I2CMODE_FASTMODEPLUS: Fast Mode Plus I/O
 * @return      PINSEL Return Code
 *              - PINSEL_RET_INVALID_PIN
 *              - PINSEL_RET_NOT_SUPPORT
 *              - PINSEL_RET_OK
 **********************************************************************/
PINSEL_RET_CODE PINSEL_SetI2CMode(uint8_t portnum, uint8_t pinnum, PinSel_I2cMode I2CMode)
{
    uint32_t *pPIN = NULL;
    PinSel_PinType type = PINSEL_GetPinType(portnum,pinnum);

    if(type == PINSEL_PIN_TYPE_UNKNOWN)
        return PINSEL_RET_INVALID_PIN;
    if(type != PINSEL_PIN_TYPE_I )
        return PINSEL_RET_NOT_SUPPORT;
    
    pPIN = PIN_GetPointer(portnum, pinnum);

    switch(I2CMode)
    {
        // Standard/Fast Mode I2C: HS = HIDRIVE = 0
        case PINSEL_I2CMODE_FAST_STANDARD: 
            PINSEL_SetI2CFilter(portnum,pinnum,ENABLE);
            *(uint32_t *)pPIN &= ~(IOCON_I2CMODE_FASTPLUS);
            break;

        // Non-I2C: HS = 1, HIDRIVE = 0
        case PINSEL_I2CMODE_OPENDRAINIO:
            PINSEL_SetI2CFilter(portnum,pinnum,DISABLE);
            *(uint32_t *)pPIN &= ~(IOCON_I2CMODE_FASTPLUS);
            break;

        // Fast Mode Plus I2C: HS = 0, HIDRIVE =1
        case PINSEL_I2CMODE_FASTMODEPLUS:   
            PINSEL_SetI2CFilter(portnum,pinnum,ENABLE);
            *(uint32_t *)pPIN |= (IOCON_I2CMODE_FASTPLUS);
            break;
        default:
            return PINSEL_RET_ERR;
    }

    return PINSEL_RET_OK;
}

/*********************************************************************//**
 * @brief       Setup Open-drain mode in pin of type D, A, W
 * @param[in]   portnum Port number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   NewState new state of Open-drain mode:
 *              - DISABLE: Normal pin I/O mode
 *              - ENABLE: Open-drain enable
 * @return      PINSEL Return Code
 *              - PINSEL_RET_INVALID_PIN
 *              - PINSEL_RET_NOT_SUPPORT
 *              - PINSEL_RET_OK
 **********************************************************************/
PINSEL_RET_CODE PINSEL_SetOpenDrainMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState)
{
    uint32_t *pPIN = NULL;
    PinSel_PinType type = PINSEL_GetPinType(portnum,pinnum);

    if(type == PINSEL_PIN_TYPE_UNKNOWN)
        return PINSEL_RET_INVALID_PIN;
    if((type != PINSEL_PIN_TYPE_D ) &&
        (type != PINSEL_PIN_TYPE_A ) &&
        (type != PINSEL_PIN_TYPE_W ))
        return PINSEL_RET_NOT_SUPPORT;
    
    pPIN = PIN_GetPointer(portnum, pinnum);
    if(NewState == DISABLE)
    {
        *(uint32_t *)pPIN &= ~IOCON_OPENDRAIN_MODE;//Clear hys bits
    }
    else
    {
        *(uint32_t *)pPIN |= IOCON_OPENDRAIN_MODE;
    }
    return PINSEL_RET_OK;
}

/*********************************************************************//**
 * @brief       Enable the Analog mode for each pin  of Type A(default is as Digital pins)
 * @param[in]   portnum PORT number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   enable: the state of the pin that is expected to run
                - ENABLE: Enable the DAC mode of the pin
                - DISABLE: Disable the DAC mode
 * @return      PINSEL Return Code
 *              - PINSEL_RET_INVALID_PIN
 *              - PINSEL_RET_NOT_SUPPORT
 *              - PINSEL_RET_OK
 **********************************************************************/
PINSEL_RET_CODE PINSEL_SetAnalogPinMode (uint8_t portnum, uint8_t pinnum, uint8_t enable)
{
    uint32_t *pPIN = NULL;
    PinSel_PinType type = PINSEL_GetPinType(portnum,pinnum);

    if(type == PINSEL_PIN_TYPE_UNKNOWN)
        return PINSEL_RET_INVALID_PIN;
    if(type != PINSEL_PIN_TYPE_A )
        return PINSEL_RET_NOT_SUPPORT;

    pPIN = PIN_GetPointer(portnum, pinnum);

    if(enable)
    {
        *(uint32_t *)pPIN &= ~(IOCON_DIGITIAL_MODE);
    }
    else
    {
        *(uint32_t *)pPIN |= IOCON_DIGITIAL_MODE;//Set 7th bit to one
    }

    return PINSEL_RET_OK;
}



/*********************************************************************//**
 * @brief       Choose the DAC mode for pin P0.26
 * @param[in]   portnum PORT number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   enable: the state of the pin that is expected to run
                - ENABLE: Enable the DAC mode of the pin
                - DISABLE: Disable the DAC mode
 * @return      PINSEL Return Code
 *              - PINSEL_RET_INVALID_PIN
 *              - PINSEL_RET_NOT_SUPPORT
 *              - PINSEL_RET_OK
 **********************************************************************/
PINSEL_RET_CODE PINSEL_DacEnable (uint8_t portnum, uint8_t pinnum, uint8_t enable)
{
    uint32_t *pPIN = NULL;
    
    PinSel_PinType type = PINSEL_GetPinType(portnum,pinnum);
    
    if(type == PINSEL_PIN_TYPE_UNKNOWN)
        return PINSEL_RET_INVALID_PIN;

    // This setting is only for DAC pin (output pin)
    if(!((portnum == 0) && (pinnum == 26)))
    {
        return PINSEL_RET_NOT_SUPPORT;
    }

    pPIN = PIN_GetPointer(portnum, pinnum);

    if(enable)
    {
        *(uint32_t *)pPIN |= IOCON_DAC_ENABLE;//Set 16th bit to one
    }
    else
    {
        *(uint32_t *)pPIN &= ~IOCON_DAC_ENABLE;//Set 16th bit to one

    }

    return PINSEL_RET_OK;
}

/*********************************************************************//**
 * @brief       Control the 10ns glitch filter for pin of type A,W
 * @param[in]   portnum PORT number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   enable: the state of the pin that is expected to run
                - ENABLE: The noise pulses below approximately 10ns are filtered out
                - DISABLE: No input filtering is done.
 * @return      PINSEL Return Code
 *              - PINSEL_RET_INVALID_PIN
 *              - PINSEL_RET_NOT_SUPPORT
 *              - PINSEL_RET_OK
 **********************************************************************/
PINSEL_RET_CODE PINSEL_SetFilter (uint8_t portnum, uint8_t pinnum, uint8_t enable)
{
    uint32_t *pPIN = NULL;
    PinSel_PinType type = PINSEL_GetPinType(portnum,pinnum);
    
    if(type == PINSEL_PIN_TYPE_UNKNOWN)
        return PINSEL_RET_INVALID_PIN;
    if((type != PINSEL_PIN_TYPE_A ) &&
        (type != PINSEL_PIN_TYPE_W ))
        return PINSEL_RET_NOT_SUPPORT;

    pPIN = PIN_GetPointer(portnum, pinnum);


    if(enable)
    {
        *(uint32_t *)pPIN &= ~(IOCON_10ns_FILTER_DISABLE);//Clear 8th bit to 0
    }
    else
    {
        *(uint32_t *)pPIN |= (IOCON_10ns_FILTER_DISABLE);//Set 8th bit to one
    }


    return PINSEL_RET_OK;
}
/*********************************************************************//**
 * @brief       Control the 50ns glitch filter for I2C pins (type I)
 * @param[in]   portnum PORT number, should be in range: 0..3
 * @param[in]   pinnum  Pin number, should be in range: 0..31
 * @param[in]   enable: the state of the pin that is expected to run
                - ENABLE: The noise pulses below approximately 10ns are filtered out
                - DISABLE: No input filtering is done.
 * @return      PINSEL Return Code
 *              - PINSEL_RET_INVALID_PIN
 *              - PINSEL_RET_NOT_SUPPORT
 *              - PINSEL_RET_OK
 **********************************************************************/
PINSEL_RET_CODE PINSEL_SetI2CFilter (uint8_t portnum, uint8_t pinnum, uint8_t enable)
{
    uint32_t *pPIN = NULL;
    PinSel_PinType type = PINSEL_GetPinType(portnum,pinnum);
    
    if(type == PINSEL_PIN_TYPE_UNKNOWN)
        return PINSEL_RET_INVALID_PIN;
    if(type != PINSEL_PIN_TYPE_I)
        return PINSEL_RET_NOT_SUPPORT;

    pPIN = PIN_GetPointer(portnum, pinnum);


    if(enable)
    {
        *(uint32_t *)pPIN &= ~(IOCON_HS_MASK);//Clear 8th bit to 0
    }
    else
    {
        *(uint32_t *)pPIN |= (IOCON_I2C_FILTER_DISABLE);//Set 8th bit to one
    }


    return PINSEL_RET_OK;
}


/**
 * @}
 */
#endif /*_PINSEL*/

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
