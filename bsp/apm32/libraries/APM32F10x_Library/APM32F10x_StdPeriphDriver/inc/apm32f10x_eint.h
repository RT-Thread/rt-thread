/*!
 * @file       apm32f10x_eint.h
 *
 * @brief      This file contains all the functions prototypes for the EINT firmware library
 *
 * @version    V1.0.1
 *
 * @date       2021-03-23
 *
 */

#ifndef __APM32F10X_EINT_H
#define __APM32F10X_EINT_H

#include "apm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup EINT_Driver EINT Driver
  @{
*/

/** @addtogroup EINT_Enumerations Enumerations
  @{
*/

/**
 * @brief    EINT mode enumeration
 */
typedef enum
{
    EINT_MODE_INTERRUPT = 0x00,
    EINT_MODE_EVENT     = 0x04
} EINT_MODE_T;

/**
 * @brief    EINT Trigger enumeration
 */
typedef enum
{
    EINT_TRIGGER_RISING         = 0x08,
    EINT_TRIGGER_FALLING        = 0x0C,
    EINT_TRIGGER_RISING_FALLING = 0x10
} EINT_TRIGGER_T;

typedef enum
{
    EINT_LINE_0   = 0x00001,  //!< External interrupt line 0
    EINT_LINE_1   = 0x00002,  //!< External interrupt line 1
    EINT_LINE_2   = 0x00004,  //!< External interrupt line 2
    EINT_LINE_3   = 0x00008,  //!< External interrupt line 3
    EINT_LINE_4   = 0x00010,  //!< External interrupt line 4
    EINT_LINE_5   = 0x00020,  //!< External interrupt line 5
    EINT_LINE_6   = 0x00040,  //!< External interrupt line 6
    EINT_LINE_7   = 0x00080,  //!< External interrupt line 7
    EINT_LINE_8   = 0x00100,  //!< External interrupt line 8
    EINT_LINE_9   = 0x00200,  //!< External interrupt line 9
    EINT_LINE_10  = 0x00400,  //!< External interrupt line 10
    EINT_LINE_11  = 0x00800,  //!< External interrupt line 11
    EINT_LINE_12  = 0x01000,  //!< External interrupt line 12
    EINT_LINE_13  = 0x02000,  //!< External interrupt line 13
    EINT_LINE_14  = 0x04000,  //!< External interrupt line 14
    EINT_LINE_15  = 0x08000,  //!< External interrupt line 15
    EINT_LINE_16  = 0x10000,  //!< External interrupt line 16 Connected to the PVD Output
    EINT_LINE_17  = 0x20000,  //!< External interrupt line 17 Connected to the RTC Alarm event
    EINT_LINE_18  = 0x40000,  //!< External interrupt line 18 Connected to the USB Device
} EINT_LINE_T;

/**@} end of group EINT_Enumerations*/


/** @addtogroup EINT_Structure Data Structure
  @{
*/

/**
 * @brief    EINT Config structure definition
 */
typedef struct
{
    uint32_t        line;
    EINT_MODE_T     mode;
    EINT_TRIGGER_T  trigger;
    uint8_t         lineCmd;
} EINT_Config_T;

/**@} end of group EINT_Structure*/


/** @addtogroup EINT_Fuctions Fuctions
  @{
*/

/** Reset and configuration */
void EINT_Reset(void);
void EINT_Config( EINT_Config_T* eintConfig);

/** Interrupt and flag */
void EINT_SelectSWInterrupt(uint32_t line);
uint8_t EINT_ReadStatusFlag(EINT_LINE_T line);
void EINT_ClearStatusFlag(uint32_t line);
uint8_t EINT_ReadIntFlag(EINT_LINE_T line);
void EINT_ClearIntFlag(uint32_t line);

/**@} end of group EINT_Fuctions*/
/**@} end of group EINT_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __APM32F10X_cplusplus
}
#endif

#endif /* __EINT_H */
