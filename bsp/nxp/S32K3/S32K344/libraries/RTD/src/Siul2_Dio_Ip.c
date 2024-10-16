/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/


/**
*   @file Siul2_Dio_Ip.c
*
*   @addtogroup DIO_IPL
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Siul2_Dio_Ip.h"
#include "SchM_Dio.h"
#if (STD_ON == SIUL2_DIO_IP_DEV_ERROR_DETECT)
    #include "Devassert.h"
#endif /* (STD_ON == SIUL2_DIO_IP_DEV_ERROR_DETECT) */
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
* @brief Parameters that shall be published within the driver header file and also in the
* module's description file
*/
#define SIUL2_DIO_IP_VENDOR_ID_C                     43
#define SIUL2_DIO_IP_AR_RELEASE_MAJOR_VERSION_C      4
#define SIUL2_DIO_IP_AR_RELEASE_MINOR_VERSION_C      7
#define SIUL2_DIO_IP_AR_RELEASE_REVISION_VERSION_C   0
#define SIUL2_DIO_IP_SW_MAJOR_VERSION_C              5
#define SIUL2_DIO_IP_SW_MINOR_VERSION_C              0
#define SIUL2_DIO_IP_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if Siul2_Dio_Ip source file and Siul2_Dio_Ip header file are of the same vendor */
#if (SIUL2_DIO_IP_VENDOR_ID_C != SIUL2_DIO_IP_VENDOR_ID_H)
    #error "Siul2_Dio_Ip.c and Siul2_Dio_Ip.h have different vendor ids"
#endif

/* Check if  Siul2_Dio_Ip source file and Siul2_Dio_Ip header file are of the same Autosar version */
#if ((SIUL2_DIO_IP_AR_RELEASE_MAJOR_VERSION_C    != SIUL2_DIO_IP_AR_RELEASE_MAJOR_VERSION_H) || \
     (SIUL2_DIO_IP_AR_RELEASE_MINOR_VERSION_C    != SIUL2_DIO_IP_AR_RELEASE_MINOR_VERSION_H) || \
     (SIUL2_DIO_IP_AR_RELEASE_REVISION_VERSION_C != SIUL2_DIO_IP_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Siul2_Dio_Ip.c and Siul2_Dio_Ip.h are different"
#endif

/* Check if Siul2_Dio_Ip source file and Siul2_Dio_Ip header file are of the same Software version */
#if ((SIUL2_DIO_IP_SW_MAJOR_VERSION_C != SIUL2_DIO_IP_SW_MAJOR_VERSION_H) || \
     (SIUL2_DIO_IP_SW_MINOR_VERSION_C != SIUL2_DIO_IP_SW_MINOR_VERSION_H) || \
     (SIUL2_DIO_IP_SW_PATCH_VERSION_C != SIUL2_DIO_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Siul2_Dio_Ip.c and Siul2_Dio_Ip.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if Siul2_Dio_Ip source file and Devassert.h header file are of the same release version */
    #if (STD_ON == SIUL2_DIO_IP_DEV_ERROR_DETECT)
        #if ((SIUL2_DIO_IP_AR_RELEASE_MAJOR_VERSION_C != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
            (SIUL2_DIO_IP_AR_RELEASE_MINOR_VERSION_C != DEVASSERT_AR_RELEASE_MINOR_VERSION)     \
            )
            #error "AutoSar Version Numbers of Siul2_Dio_Ip.c and Devassert.h are different"
        #endif
    #endif /* (STD_ON == SIUL2_DIO_IP_DEV_ERROR_DETECT) */
    /* SchM_Dio.h version check start */
    #if ((SIUL2_DIO_IP_AR_RELEASE_MAJOR_VERSION_C != SCHM_DIO_AR_RELEASE_MAJOR_VERSION) ||   \
        (SIUL2_DIO_IP_AR_RELEASE_MINOR_VERSION_C != SCHM_DIO_AR_RELEASE_MINOR_VERSION)       \
        )
        #error "AUTOSAR Version Numbers of Siul2_Dio_Ip.c and SchM_Dio.h are different"
    #endif
    /* SchM_Dio.h version check end */
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/
#define SIUL2_DIO_IP_NUM_OF_PIN_PORT           16u


#define IS_STATIC static /* non-ZE case, function must be static */

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/
#define DIO_START_SEC_VAR_INIT_32
#include "Dio_MemMap.h"

#if (STD_ON == DIO_VIRTWRAPPER_SUPPORT)
#ifdef SIUL2_VIRTWRAPPER_MULTIINSTANCE
Siul2_Dio_Ip_CoreType Siul2_Dio_Ip_au32BaseAdresses[SIUL2_INSTANCE_COUNT] = IP_SIUL2_BASE_ADDRS;
#else
Siul2_Dio_Ip_CoreType Siul2_Dio_Ip_au32BaseAdresses[6] =
{
    DIO_SIUL2_VIRTWRAPPER_PDAC0,
    DIO_SIUL2_VIRTWRAPPER_PDAC1,
    DIO_SIUL2_VIRTWRAPPER_PDAC2,
    DIO_SIUL2_VIRTWRAPPER_PDAC3,
    DIO_SIUL2_VIRTWRAPPER_PDAC4,
    DIO_SIUL2_VIRTWRAPPER_PDAC5
};
#endif
#else
    #ifdef IP_SIUL2_AE_BASE
Siul2_Dio_Ip_CoreType Siul2_Dio_Ip_au32BaseAdresses[SIUL2_INSTANCE_COUNT + SIUL2_AE_INSTANCE_COUNT] = { IP_SIUL2_0_BASE, IP_SIUL2_1_BASE, IP_SIUL2_3_BASE, IP_SIUL2_4_BASE, IP_SIUL2_5_BASE, IP_SIUL2_AE_BASE };
    #else
Siul2_Dio_Ip_CoreType Siul2_Dio_Ip_au32BaseAdresses[SIUL2_INSTANCE_COUNT] = IP_SIUL2_BASE_ADDRS;
    #endif /* IP_SIUL2_AE_BASE */
#endif
#define DIO_STOP_SEC_VAR_INIT_32
#include "Dio_MemMap.h"
/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define DIO_START_SEC_CODE
#include "Dio_MemMap.h"

static inline uint16 Siul2_Dio_Ip_Rev_Bit_16(uint16 value);

static inline void Siul2_Dio_Ip_WriteGPDOValue(const uint8 u8Siul2Instance,
                                               const uint16 GPDOnum,
                                               const Siul2_Dio_Ip_PinsLevelType value
                                              );

#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
IS_STATIC void Siul2_Dio_Ip_WritePinsRunTime(Siul2_Dio_Ip_GpioType * const base,
                                             Siul2_Dio_Ip_PinsChannelType pins
                                            );
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */

IS_STATIC void Siul2_Dio_Ip_ClearPinsRunTime(Siul2_Dio_Ip_GpioType * const base,
                                             Siul2_Dio_Ip_PinsChannelType pins
                                            );

IS_STATIC void Siul2_Dio_Ip_WritePinRunTime(Siul2_Dio_Ip_GpioType * const base,
                                            Siul2_Dio_Ip_PinsChannelType pin,
                                            Siul2_Dio_Ip_PinsLevelType value
                                           );

IS_STATIC Siul2_Dio_Ip_PinsChannelType Siul2_Dio_Ip_GetPinsOutputRunTime(const Siul2_Dio_Ip_GpioType * const base);

IS_STATIC void Siul2_Dio_Ip_SetPinsRunTime(Siul2_Dio_Ip_GpioType * const base,
                                           Siul2_Dio_Ip_PinsChannelType pins
                                          );

#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
IS_STATIC void Siul2_Dio_Ip_MaskedWritePinsRunTime(uint8 u8Siul2Instance,
                                                   uint8 u8PortId,
                                                   Siul2_Dio_Ip_PinsChannelType pins,
                                                   Siul2_Dio_Ip_PinsChannelType mask
                                                  );
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */

IS_STATIC void Siul2_Dio_Ip_TogglePinsRunTime(Siul2_Dio_Ip_GpioType * const base,
                                              Siul2_Dio_Ip_PinsChannelType pins
                                             );

IS_STATIC Siul2_Dio_Ip_PinsLevelType Siul2_Dio_Ip_ReadPinRunTime(const Siul2_Dio_Ip_GpioType * const base,
                                                                 Siul2_Dio_Ip_PinsChannelType pin
                                                                );

IS_STATIC Siul2_Dio_Ip_PinsChannelType Siul2_Dio_Ip_ReadPinsRunTime(const Siul2_Dio_Ip_GpioType * const base);

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/* Reverse bit order in each halfword independently */
static inline uint16 Siul2_Dio_Ip_Rev_Bit_16(uint16 value)
{
    uint8 i;
    uint16 ret = 0U;

    for (i = 0U; i < 8U; i++)
    {
        ret |= (uint16)((((value >> i) & 1U) << (15U - i)) | (((value << i) & 0x8000U) >> (15U - i)));
    }

    return ret;
}

/* Set/reset value of GPDO register */
static inline void Siul2_Dio_Ip_WriteGPDOValue(const uint8 u8Siul2Instance,
                                               const uint16 GPDOnum,
                                               const Siul2_Dio_Ip_PinsLevelType value
                                              )
{
    *(Siul2_Dio_Ip_PinsLevelType*)(SIUL2_DIO_IP_GPDO_ADDR32(u8Siul2Instance, GPDOnum)) = (Siul2_Dio_Ip_PinsLevelType)value;
}
/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

IS_STATIC void Siul2_Dio_Ip_WritePinRunTime(Siul2_Dio_Ip_GpioType * const base,
                                            Siul2_Dio_Ip_PinsChannelType pin,
                                            Siul2_Dio_Ip_PinsLevelType value
                                           )
{
    /* Enter critical region */
    SchM_Enter_Dio_DIO_EXCLUSIVE_AREA_01();

    Siul2_Dio_Ip_PinsChannelType pinsValues = (Siul2_Dio_Ip_PinsChannelType)base->PGPDO;
    pinsValues &= (Siul2_Dio_Ip_PinsChannelType)(~((Siul2_Dio_Ip_PinsChannelType)1U << (15U - pin)));
    pinsValues |= (Siul2_Dio_Ip_PinsChannelType)(((Siul2_Dio_Ip_PinsChannelType)value & 1U) << (15U - pin));
    base->PGPDO = pinsValues;

    /* Exit critical region */
    SchM_Exit_Dio_DIO_EXCLUSIVE_AREA_01();
}

/**
 *Function Name : Siul2_Dio_Ip_WritePin
 * Description   : This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * @implements    Siul2_Dio_Ip_WritePin_Activity
 */
void Siul2_Dio_Ip_WritePin(Siul2_Dio_Ip_GpioType * const base,
                           Siul2_Dio_Ip_PinsChannelType pin,
                           Siul2_Dio_Ip_PinsLevelType value
                          )
{
    SIUL2_DIO_IP_DEV_ASSERT(NULL_PTR != base);
    SIUL2_DIO_IP_DEV_ASSERT((boolean)(pin < SIUL2_DIO_IP_NUM_OF_PIN_PORT));
    SIUL2_DIO_IP_DEV_ASSERT((boolean)(value <= 1U));

    Siul2_Dio_Ip_WritePinRunTime(base, pin, value);
}

/**
 * Function Name : Siul2_Dio_Ip_SetGPDO
 * Description   : This function sets the GPDO register for a given Siul2 Instance and GPDO register number
 *
 */
void Siul2_Dio_Ip_SetGPDO(const uint8 u8Siul2Instance,
                          const uint16 GPDOnum
                         )
{
    Siul2_Dio_Ip_WriteGPDOValue(u8Siul2Instance, GPDOnum, (Siul2_Dio_Ip_PinsLevelType)(STD_HIGH));
}

/**
 * Function Name : Siul2_Dio_GPDO_ClearGPDO
 * Description   : This function clears the GPDO register for a given Siul2 Instance and GPDO register number
 *
 */
void Siul2_Dio_Ip_ClearGPDO(const uint8 u8Siul2Instance,
                            const uint16 GPDOnum
                           )
{
    Siul2_Dio_Ip_WriteGPDOValue(u8Siul2Instance, GPDOnum, (Siul2_Dio_Ip_PinsLevelType)(STD_LOW));
}

#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
 * Function Name : Siul2_Dio_Ip_WritePinsRunTime
 * Description   : This function writes all pins configured as output with the values given in
 * the parameter pins. '0' represents LOW, '1' represents HIGH.
 *
 */
IS_STATIC void Siul2_Dio_Ip_WritePinsRunTime(Siul2_Dio_Ip_GpioType * const base,
                                             Siul2_Dio_Ip_PinsChannelType pins
                                            )
{
    base->PGPDO = Siul2_Dio_Ip_Rev_Bit_16(pins);
}

/**
 * Function Name : Siul2_Dio_Ip_WritePins
 * Description   : This function writes all pins configured as output with the values given in
 * the parameter pins. '0' represents LOW, '1' represents HIGH.
 *
 * @implements    Siul2_Dio_Ip_WritePins_Activity
 */
void Siul2_Dio_Ip_WritePins(Siul2_Dio_Ip_GpioType * const base,
                            Siul2_Dio_Ip_PinsChannelType pins
                           )
{
    SIUL2_DIO_IP_DEV_ASSERT(NULL_PTR != base);
    Siul2_Dio_Ip_WritePinsRunTime(base, pins);
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */

/**
 * Function Name : Siul2_Dio_Ip_GetPinsOutputRunTime
 * Description   : This function returns the current output that is written to a port. Only pins
 * that are configured as output will have meaningful values.
 *
 */
IS_STATIC Siul2_Dio_Ip_PinsChannelType Siul2_Dio_Ip_GetPinsOutputRunTime(const Siul2_Dio_Ip_GpioType * const base)
{
    Siul2_Dio_Ip_PinsChannelType returnValue = 0U;
    returnValue = (Siul2_Dio_Ip_PinsChannelType)Siul2_Dio_Ip_Rev_Bit_16(base->PGPDO);
    return returnValue;
}

/**
 * Function Name : Siul2_Dio_Ip_GetPinsOutput
 * Description   : This function returns the current output that is written to a port. Only pins
 * that are configured as output will have meaningful values.
 *
 * @implements    Siul2_Dio_Ip_GetPinsOutput_Activity
 */
Siul2_Dio_Ip_PinsChannelType Siul2_Dio_Ip_GetPinsOutput(const Siul2_Dio_Ip_GpioType * const base)
{
    SIUL2_DIO_IP_DEV_ASSERT(NULL_PTR != base);
    Siul2_Dio_Ip_PinsChannelType returnValue = 0U;
    returnValue = Siul2_Dio_Ip_GetPinsOutputRunTime(base);
    return returnValue;
}

/**
 * Function Name : Siul2_Dio_Ip_SetPinsRunTime
 * Description   : This function configures output pins listed in parameter pins (bits that are
 * '1') to have a value of 'set' (HIGH). Pins corresponding to '0' will be
 * unaffected.
 *
 */
IS_STATIC void Siul2_Dio_Ip_SetPinsRunTime(Siul2_Dio_Ip_GpioType * const base,
                                           Siul2_Dio_Ip_PinsChannelType pins
                                          )
{
    base->PGPDO |= Siul2_Dio_Ip_Rev_Bit_16(pins);
}

/**
 * Function Name : Siul2_Dio_Ip_SetPins
 * Description   : This function configures output pins listed in parameter pins (bits that are
 * '1') to have a value of 'set' (HIGH). Pins corresponding to '0' will be
 * unaffected.
 *
 * @implements    Siul2_Dio_Ip_SetPins_Activity
 */
void Siul2_Dio_Ip_SetPins(Siul2_Dio_Ip_GpioType * const base,
                          Siul2_Dio_Ip_PinsChannelType pins
                         )
{
    SIUL2_DIO_IP_DEV_ASSERT(NULL_PTR != base);
    Siul2_Dio_Ip_SetPinsRunTime(base, pins);
}

/**
 * Function Name : Siul2_Dio_Ip_ClearPinsRunTime
 * Description   : This function configures output pins listed in parameter pins (bits that are
 * '1') to have a 'cleared' value (LOW). Pins corresponding to '0' will be
 * unaffected.
 *
 */
IS_STATIC void Siul2_Dio_Ip_ClearPinsRunTime(Siul2_Dio_Ip_GpioType * const base,
                                             Siul2_Dio_Ip_PinsChannelType pins
                                            )
{
    base->PGPDO &= (Siul2_Dio_Ip_PinsChannelType)(~Siul2_Dio_Ip_Rev_Bit_16(pins));
}

/**
 * Function Name : Siul2_Dio_Ip_ClearPins
 * Description   : This function configures output pins listed in parameter pins (bits that are
 * '1') to have a 'cleared' value (LOW). Pins corresponding to '0' will be
 * unaffected.
 *
 * @implements    Siul2_Dio_Ip_ClearPins_Activity
 */
void Siul2_Dio_Ip_ClearPins(Siul2_Dio_Ip_GpioType * const base,
                            Siul2_Dio_Ip_PinsChannelType pins
                           )
{
    SIUL2_DIO_IP_DEV_ASSERT(NULL_PTR != base);
    Siul2_Dio_Ip_ClearPinsRunTime(base, pins);
}

/**
 * Function Name : Siul2_Dio_Ip_TogglePinsRunTime
 * Description   : This function toggles output pins listed in parameter pins (bits that are
 * '1'). Pins corresponding to '0' will be unaffected.
 *
 */
IS_STATIC void Siul2_Dio_Ip_TogglePinsRunTime(Siul2_Dio_Ip_GpioType * const base,
                                              Siul2_Dio_Ip_PinsChannelType pins
                                             )
{
    base->PGPDO ^= Siul2_Dio_Ip_Rev_Bit_16(pins);
}

/**
 * Function Name : Siul2_Dio_Ip_TogglePins
 * Description   : This function toggles output pins listed in parameter pins (bits that are
 * '1'). Pins corresponding to '0' will be unaffected.
 *
 * @implements    Siul2_Dio_Ip_TogglePins_Activity
 */
void Siul2_Dio_Ip_TogglePins(Siul2_Dio_Ip_GpioType * const base,
                             Siul2_Dio_Ip_PinsChannelType pins
                            )
{
    SIUL2_DIO_IP_DEV_ASSERT(NULL_PTR != base);
    Siul2_Dio_Ip_TogglePinsRunTime(base, pins);
}

/**
 * Function Name : Siul2_Dio_Ip_ReadPinsRunTime
 * Description   : This function returns the current input values from a port. Only pins
 * configured as input will have meaningful values.
 *
 */
IS_STATIC Siul2_Dio_Ip_PinsChannelType Siul2_Dio_Ip_ReadPinsRunTime(const Siul2_Dio_Ip_GpioType * const base)
{
    Siul2_Dio_Ip_PinsChannelType returnValue = 0U;
    returnValue = (Siul2_Dio_Ip_PinsChannelType)Siul2_Dio_Ip_Rev_Bit_16(base->PGPDI);
    return returnValue;
}

/**
 * Function Name : Siul2_Dio_Ip_ReadPins
 * Description   : This function returns the current input values from a port. Only pins
 * configured as input will have meaningful values.
 *
 * @implements    Siul2_Dio_Ip_ReadPins_Activity
 */
Siul2_Dio_Ip_PinsChannelType Siul2_Dio_Ip_ReadPins(const Siul2_Dio_Ip_GpioType * const base)
{
    SIUL2_DIO_IP_DEV_ASSERT(NULL_PTR != base);
    Siul2_Dio_Ip_PinsChannelType returnValue = 0U;
    returnValue = Siul2_Dio_Ip_ReadPinsRunTime(base);
    return returnValue;
}

/**
 * Function Name : Siul2_Dio_Ip_ReadPinRunTime
 * Description   : This function returns the current  input value of the given pin from port. Only pin
 * configured as input will have meaningful value.
 *
 */
IS_STATIC Siul2_Dio_Ip_PinsLevelType Siul2_Dio_Ip_ReadPinRunTime(const Siul2_Dio_Ip_GpioType * const base,
                                                                 Siul2_Dio_Ip_PinsChannelType pin
                                                                )
{
    Siul2_Dio_Ip_PinsLevelType returnValue = 0U;
    returnValue = (Siul2_Dio_Ip_PinsLevelType)((Siul2_Dio_Ip_Rev_Bit_16(base->PGPDI) & ((Siul2_Dio_Ip_PinsChannelType)1U << pin)) >> pin);
    return returnValue;
}

/**
 * Function Name : Siul2_Dio_Ip_ReadPin
 * Description   : This function returns the current  input value of the given pin from port. Only pin
 * configured as input will have meaningful value.
 *
 * @implements    Siul2_Dio_Ip_ReadPin_Activity
 */
Siul2_Dio_Ip_PinsLevelType Siul2_Dio_Ip_ReadPin(const Siul2_Dio_Ip_GpioType * const base,
                                                Siul2_Dio_Ip_PinsChannelType pin
                                               )
{
    SIUL2_DIO_IP_DEV_ASSERT(NULL_PTR != base);
    SIUL2_DIO_IP_DEV_ASSERT((boolean)(pin < SIUL2_DIO_IP_NUM_OF_PIN_PORT));
    Siul2_Dio_Ip_PinsLevelType returnValue = 0U;
    returnValue = Siul2_Dio_Ip_ReadPinRunTime(base, pin);
    return returnValue;
}

#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
 * Function Name : Siul2_Dio_Ip_MaskedWritePinsRunTime
 * Description   : This function writes the masked pins configured as output with the values given
 * in the parameter pins. '0' represents LOW, '1' represents HIGH.
 *
 */
IS_STATIC void Siul2_Dio_Ip_MaskedWritePinsRunTime(uint8 u8Siul2Instance,
                                                   uint8 u8PortId,
                                                   Siul2_Dio_Ip_PinsChannelType pins,
                                                   Siul2_Dio_Ip_PinsChannelType mask
                                                  )
{
    uint32 maskRev;
    uint32 pinsRev;

    maskRev = (uint32)(Siul2_Dio_Ip_Rev_Bit_16(mask));
    pinsRev = (uint32)(Siul2_Dio_Ip_Rev_Bit_16(pins));
    *(Siul2_Dio_Ip_CoreType *)(SIUL2_DIO_IP_MPGPDO_ADDR32(u8Siul2Instance, u8PortId)) = (maskRev << (uint32)16U) | pinsRev;
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */

#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
 * Function Name : Siul2_Dio_Ip_MaskedWritePins
 * Description   : This function writes the masked pins configured as output with the values given
 * in the parameter pins. '0' represents LOW, '1' represents HIGH.
 *
 * @implements    Siul2_Dio_Ip_MaskedWritePins_Activity
 */
void Siul2_Dio_Ip_MaskedWritePins(uint8 u8Siul2Instance,
                                  uint8 u8PortId,
                                  Siul2_Dio_Ip_PinsChannelType pins,
                                  Siul2_Dio_Ip_PinsChannelType mask
                                 )
{
    Siul2_Dio_Ip_MaskedWritePinsRunTime(u8Siul2Instance, u8PortId, pins, mask);
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */

#define DIO_STOP_SEC_CODE
#include "Dio_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

/******************************************************************************
 * EOF
 *****************************************************************************/
