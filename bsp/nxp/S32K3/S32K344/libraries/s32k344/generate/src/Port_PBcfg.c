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
*   @file    Port_PBcfg.c
*
*   @implements Port_PBcfg.c_Artifact
*   @addtogroup Port_CFG
*   @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Port.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
#define PORT_VENDOR_ID_PBCFG_C                       43
#define PORT_AR_RELEASE_MAJOR_VERSION_PBCFG_C        4
#define PORT_AR_RELEASE_MINOR_VERSION_PBCFG_C        7
#define PORT_AR_RELEASE_REVISION_VERSION_PBCFG_C     0
#define PORT_SW_MAJOR_VERSION_PBCFG_C                5
#define PORT_SW_MINOR_VERSION_PBCFG_C                0
#define PORT_SW_PATCH_VERSION_PBCFG_C                0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if Port_PBcfg.c and Port.h are of the same vendor */
#if (PORT_VENDOR_ID_PBCFG_C != PORT_VENDOR_ID)
    #error "Port_PBcfg.c and Port.h have different vendor ids"
#endif
/* Check if Port_PBcfg.c and Port.h are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_PBCFG_C    != PORT_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_AR_RELEASE_MINOR_VERSION_PBCFG_C    != PORT_AR_RELEASE_MINOR_VERSION) || \
     (PORT_AR_RELEASE_REVISION_VERSION_PBCFG_C != PORT_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Port_PBcfg.c and Port.h are different"
#endif
/* Check if Port_PBcfg.c and Port.h are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_PBCFG_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_PBCFG_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_PBCFG_C != PORT_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Port_PBcfg.c and Port.h are different"
#endif
/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/

/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/

/*=================================================================================================
*                                      LOCAL CONSTANTS
=================================================================================================*/
#define PORT_START_SEC_CONFIG_DATA_8
#include "Port_MemMap.h"

/**
* @brief Array containing list of partition which used in driver
*/
static const uint8 au8Port_PartitionList[PORT_MAX_PARTITION] =
{
    1
};

#define PORT_STOP_SEC_CONFIG_DATA_8
#include "Port_MemMap.h"

#define PORT_START_SEC_CONFIG_DATA_32
#include "Port_MemMap.h"
/**
* @brief Array containing list of mapping information for mappable elements
*/
static const uint32 au32Port_PinToPartitionMap[PORT_MAX_CONFIGURED_PADS_U16] =
{
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001
};

#define PORT_STOP_SEC_CONFIG_DATA_32
#include "Port_MemMap.h"

#if (PORT_MAX_UNUSED_PADS_U16 != 0U)

#define PORT_START_SEC_CONFIG_DATA_16
#include "Port_MemMap.h"

/**
* @brief Array containing list of MSCRs that are not used and should be configured with values from NotUsedPortPin container
*/
static const Port_Siul2_UnUsedPinType Port_aUnusedPads[PORT_MAX_UNUSED_PADS_U16] =
{
    /* Mscr Id, Mscr Siul Instance */
    { (uint16)0, PORT_SIUL2_0_U8 },
    { (uint16)1, PORT_SIUL2_0_U8 },
    { (uint16)2, PORT_SIUL2_0_U8 },
    { (uint16)3, PORT_SIUL2_0_U8 },
    { (uint16)5, PORT_SIUL2_0_U8 },
    { (uint16)6, PORT_SIUL2_0_U8 },
    { (uint16)7, PORT_SIUL2_0_U8 },
    { (uint16)8, PORT_SIUL2_0_U8 },
    { (uint16)9, PORT_SIUL2_0_U8 },
    { (uint16)11, PORT_SIUL2_0_U8 },
    { (uint16)12, PORT_SIUL2_0_U8 },
    { (uint16)13, PORT_SIUL2_0_U8 },
    { (uint16)14, PORT_SIUL2_0_U8 },
    { (uint16)15, PORT_SIUL2_0_U8 },
    { (uint16)16, PORT_SIUL2_0_U8 },
    { (uint16)17, PORT_SIUL2_0_U8 },
    { (uint16)18, PORT_SIUL2_0_U8 },
    { (uint16)19, PORT_SIUL2_0_U8 },
    { (uint16)20, PORT_SIUL2_0_U8 },
    { (uint16)21, PORT_SIUL2_0_U8 },
    { (uint16)22, PORT_SIUL2_0_U8 },
    { (uint16)23, PORT_SIUL2_0_U8 },
    { (uint16)24, PORT_SIUL2_0_U8 },
    { (uint16)25, PORT_SIUL2_0_U8 },
    { (uint16)26, PORT_SIUL2_0_U8 },
    { (uint16)27, PORT_SIUL2_0_U8 },
    { (uint16)28, PORT_SIUL2_0_U8 },
    { (uint16)29, PORT_SIUL2_0_U8 },
    { (uint16)30, PORT_SIUL2_0_U8 },
    { (uint16)31, PORT_SIUL2_0_U8 },
    { (uint16)32, PORT_SIUL2_0_U8 },
    { (uint16)33, PORT_SIUL2_0_U8 },
    { (uint16)34, PORT_SIUL2_0_U8 },
    { (uint16)35, PORT_SIUL2_0_U8 },
    { (uint16)36, PORT_SIUL2_0_U8 },
    { (uint16)37, PORT_SIUL2_0_U8 },
    { (uint16)40, PORT_SIUL2_0_U8 },
    { (uint16)41, PORT_SIUL2_0_U8 },
    { (uint16)42, PORT_SIUL2_0_U8 },
    { (uint16)43, PORT_SIUL2_0_U8 },
    { (uint16)44, PORT_SIUL2_0_U8 },
    { (uint16)45, PORT_SIUL2_0_U8 },
    { (uint16)46, PORT_SIUL2_0_U8 },
    { (uint16)47, PORT_SIUL2_0_U8 },
    { (uint16)48, PORT_SIUL2_0_U8 },
    { (uint16)49, PORT_SIUL2_0_U8 },
    { (uint16)50, PORT_SIUL2_0_U8 },
    { (uint16)51, PORT_SIUL2_0_U8 },
    { (uint16)52, PORT_SIUL2_0_U8 },
    { (uint16)53, PORT_SIUL2_0_U8 },
    { (uint16)54, PORT_SIUL2_0_U8 },
    { (uint16)55, PORT_SIUL2_0_U8 },
    { (uint16)56, PORT_SIUL2_0_U8 },
    { (uint16)57, PORT_SIUL2_0_U8 },
    { (uint16)58, PORT_SIUL2_0_U8 },
    { (uint16)59, PORT_SIUL2_0_U8 },
    { (uint16)60, PORT_SIUL2_0_U8 },
    { (uint16)61, PORT_SIUL2_0_U8 },
    { (uint16)62, PORT_SIUL2_0_U8 },
    { (uint16)63, PORT_SIUL2_0_U8 },
    { (uint16)64, PORT_SIUL2_0_U8 },
    { (uint16)65, PORT_SIUL2_0_U8 },
    { (uint16)66, PORT_SIUL2_0_U8 },
    { (uint16)67, PORT_SIUL2_0_U8 },
    { (uint16)70, PORT_SIUL2_0_U8 },
    { (uint16)71, PORT_SIUL2_0_U8 },
    { (uint16)72, PORT_SIUL2_0_U8 },
    { (uint16)73, PORT_SIUL2_0_U8 },
    { (uint16)74, PORT_SIUL2_0_U8 },
    { (uint16)75, PORT_SIUL2_0_U8 },
    { (uint16)76, PORT_SIUL2_0_U8 },
    { (uint16)77, PORT_SIUL2_0_U8 },
    { (uint16)78, PORT_SIUL2_0_U8 },
    { (uint16)79, PORT_SIUL2_0_U8 },
    { (uint16)80, PORT_SIUL2_0_U8 },
    { (uint16)81, PORT_SIUL2_0_U8 },
    { (uint16)82, PORT_SIUL2_0_U8 },
    { (uint16)83, PORT_SIUL2_0_U8 },
    { (uint16)84, PORT_SIUL2_0_U8 },
    { (uint16)85, PORT_SIUL2_0_U8 },
    { (uint16)86, PORT_SIUL2_0_U8 },
    { (uint16)87, PORT_SIUL2_0_U8 },
    { (uint16)88, PORT_SIUL2_0_U8 },
    { (uint16)90, PORT_SIUL2_0_U8 },
    { (uint16)91, PORT_SIUL2_0_U8 },
    { (uint16)92, PORT_SIUL2_0_U8 },
    { (uint16)93, PORT_SIUL2_0_U8 },
    { (uint16)94, PORT_SIUL2_0_U8 },
    { (uint16)95, PORT_SIUL2_0_U8 },
    { (uint16)96, PORT_SIUL2_0_U8 },
    { (uint16)97, PORT_SIUL2_0_U8 },
    { (uint16)100, PORT_SIUL2_0_U8 },
    { (uint16)101, PORT_SIUL2_0_U8 },
    { (uint16)102, PORT_SIUL2_0_U8 },
    { (uint16)103, PORT_SIUL2_0_U8 },
    { (uint16)104, PORT_SIUL2_0_U8 },
    { (uint16)105, PORT_SIUL2_0_U8 },
    { (uint16)106, PORT_SIUL2_0_U8 },
    { (uint16)107, PORT_SIUL2_0_U8 },
    { (uint16)108, PORT_SIUL2_0_U8 },
    { (uint16)109, PORT_SIUL2_0_U8 },
    { (uint16)110, PORT_SIUL2_0_U8 },
    { (uint16)111, PORT_SIUL2_0_U8 },
    { (uint16)112, PORT_SIUL2_0_U8 },
    { (uint16)113, PORT_SIUL2_0_U8 },
    { (uint16)114, PORT_SIUL2_0_U8 },
    { (uint16)115, PORT_SIUL2_0_U8 },
    { (uint16)116, PORT_SIUL2_0_U8 },
    { (uint16)117, PORT_SIUL2_0_U8 },
    { (uint16)118, PORT_SIUL2_0_U8 },
    { (uint16)119, PORT_SIUL2_0_U8 },
    { (uint16)120, PORT_SIUL2_0_U8 },
    { (uint16)121, PORT_SIUL2_0_U8 },
    { (uint16)122, PORT_SIUL2_0_U8 },
    { (uint16)123, PORT_SIUL2_0_U8 },
    { (uint16)124, PORT_SIUL2_0_U8 },
    { (uint16)125, PORT_SIUL2_0_U8 },
    { (uint16)126, PORT_SIUL2_0_U8 },
    { (uint16)127, PORT_SIUL2_0_U8 },
    { (uint16)128, PORT_SIUL2_0_U8 },
    { (uint16)129, PORT_SIUL2_0_U8 },
    { (uint16)130, PORT_SIUL2_0_U8 },
    { (uint16)131, PORT_SIUL2_0_U8 },
    { (uint16)132, PORT_SIUL2_0_U8 },
    { (uint16)133, PORT_SIUL2_0_U8 },
    { (uint16)134, PORT_SIUL2_0_U8 },
    { (uint16)135, PORT_SIUL2_0_U8 },
    { (uint16)136, PORT_SIUL2_0_U8 },
    { (uint16)137, PORT_SIUL2_0_U8 },
    { (uint16)138, PORT_SIUL2_0_U8 },
    { (uint16)139, PORT_SIUL2_0_U8 },
    { (uint16)140, PORT_SIUL2_0_U8 },
    { (uint16)141, PORT_SIUL2_0_U8 },
    { (uint16)142, PORT_SIUL2_0_U8 },
    { (uint16)143, PORT_SIUL2_0_U8 },
    { (uint16)144, PORT_SIUL2_0_U8 },
    { (uint16)145, PORT_SIUL2_0_U8 },
    { (uint16)146, PORT_SIUL2_0_U8 },
    { (uint16)147, PORT_SIUL2_0_U8 },
    { (uint16)148, PORT_SIUL2_0_U8 },
    { (uint16)149, PORT_SIUL2_0_U8 },
    { (uint16)150, PORT_SIUL2_0_U8 },
    { (uint16)151, PORT_SIUL2_0_U8 },
    { (uint16)152, PORT_SIUL2_0_U8 },
    { (uint16)153, PORT_SIUL2_0_U8 },
    { (uint16)154, PORT_SIUL2_0_U8 },
    { (uint16)155, PORT_SIUL2_0_U8 },
    { (uint16)156, PORT_SIUL2_0_U8 },
    { (uint16)157, PORT_SIUL2_0_U8 },
    { (uint16)158, PORT_SIUL2_0_U8 },
    { (uint16)159, PORT_SIUL2_0_U8 },
    { (uint16)160, PORT_SIUL2_0_U8 },
    { (uint16)161, PORT_SIUL2_0_U8 },
    { (uint16)162, PORT_SIUL2_0_U8 },
    { (uint16)163, PORT_SIUL2_0_U8 },
    { (uint16)164, PORT_SIUL2_0_U8 },
    { (uint16)165, PORT_SIUL2_0_U8 },
    { (uint16)166, PORT_SIUL2_0_U8 },
    { (uint16)167, PORT_SIUL2_0_U8 },
    { (uint16)168, PORT_SIUL2_0_U8 },
    { (uint16)169, PORT_SIUL2_0_U8 },
    { (uint16)170, PORT_SIUL2_0_U8 },
    { (uint16)171, PORT_SIUL2_0_U8 },
    { (uint16)172, PORT_SIUL2_0_U8 },
    { (uint16)173, PORT_SIUL2_0_U8 },
    { (uint16)174, PORT_SIUL2_0_U8 },
    { (uint16)175, PORT_SIUL2_0_U8 },
    { (uint16)176, PORT_SIUL2_0_U8 },
    { (uint16)177, PORT_SIUL2_0_U8 },
    { (uint16)178, PORT_SIUL2_0_U8 },
    { (uint16)179, PORT_SIUL2_0_U8 },
    { (uint16)180, PORT_SIUL2_0_U8 },
    { (uint16)181, PORT_SIUL2_0_U8 },
    { (uint16)182, PORT_SIUL2_0_U8 },
    { (uint16)183, PORT_SIUL2_0_U8 },
    { (uint16)184, PORT_SIUL2_0_U8 },
    { (uint16)185, PORT_SIUL2_0_U8 },
    { (uint16)186, PORT_SIUL2_0_U8 },
    { (uint16)187, PORT_SIUL2_0_U8 },
    { (uint16)188, PORT_SIUL2_0_U8 },
    { (uint16)189, PORT_SIUL2_0_U8 },
    { (uint16)190, PORT_SIUL2_0_U8 },
    { (uint16)191, PORT_SIUL2_0_U8 },
    { (uint16)192, PORT_SIUL2_0_U8 },
    { (uint16)193, PORT_SIUL2_0_U8 },
    { (uint16)194, PORT_SIUL2_0_U8 },
    { (uint16)195, PORT_SIUL2_0_U8 },
    { (uint16)196, PORT_SIUL2_0_U8 },
    { (uint16)197, PORT_SIUL2_0_U8 },
    { (uint16)198, PORT_SIUL2_0_U8 },
    { (uint16)199, PORT_SIUL2_0_U8 },
    { (uint16)200, PORT_SIUL2_0_U8 },
    { (uint16)201, PORT_SIUL2_0_U8 },
    { (uint16)202, PORT_SIUL2_0_U8 },
    { (uint16)203, PORT_SIUL2_0_U8 },
    { (uint16)204, PORT_SIUL2_0_U8 },
    { (uint16)205, PORT_SIUL2_0_U8 },
    { (uint16)206, PORT_SIUL2_0_U8 },
    { (uint16)207, PORT_SIUL2_0_U8 },
    { (uint16)208, PORT_SIUL2_0_U8 },
    { (uint16)209, PORT_SIUL2_0_U8 },
    { (uint16)210, PORT_SIUL2_0_U8 },
    { (uint16)211, PORT_SIUL2_0_U8 },
    { (uint16)212, PORT_SIUL2_0_U8 },
    { (uint16)213, PORT_SIUL2_0_U8 },
    { (uint16)214, PORT_SIUL2_0_U8 },
    { (uint16)215, PORT_SIUL2_0_U8 },
    { (uint16)216, PORT_SIUL2_0_U8 },
    { (uint16)217, PORT_SIUL2_0_U8 },
    { (uint16)218, PORT_SIUL2_0_U8 },
    { (uint16)219, PORT_SIUL2_0_U8 }
};

#define PORT_STOP_SEC_CONFIG_DATA_16
#include "Port_MemMap.h"

#endif /* (PORT_MAX_UNUSED_PADS_U16 != 0) */

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/**
 * @brief Default Configuration for Pins not initialized
 */
static const Port_Siul2_UnUsedPinConfigType Port_UnusedPinConfig =
{
    /**
    * @note: Configuration of Default pin
    */
    (uint32)0x00080000, (uint8)1
};

/**
* @brief Pin default configuration data for configPB
*/
static const Port_Siul2_PinConfigType Port_aUsedPinConfigs[PORT_MAX_CONFIGURED_PADS_U16] =
{
    /* Mscr Id, Mscr Value, Mscr Siul Instance, Output Level, Direction, IsGpio, Direction Configurable, Mode Changeable, Is Imcr Available, Imcr Id */
    { (uint16)98, (uint32)0x00200006, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE, 65535 },
    { (uint16)99, (uint32)0x00080000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_IN, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE, (boolean)TRUE, 190 },
    { (uint16)89, (uint32)0x00200000, (uint8)PORT_SIUL2_0_U8, (uint8)0, PORT_PIN_OUT, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE, (boolean)FALSE, 65535 }
};

#ifdef PORT_CODE_SIZE_OPTIMIZATION
#if (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION)

/* SIUL2_0 */
/**
* @brief IMCR configuration set by Port_Init() for SIUL2 instance: SIUL2_0
*/
static const Port_Siul2_ImcrConfigType Port_aSIUL2_0_ImcrInitConfig[PORT_SIUL2_0_NUM_IMCRS_U16] =
{
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x03, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0xFFU, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
    { (uint8)0x00, (uint8)0 },
};

#endif /* (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION) */
#endif /* PORT_CODE_SIZE_OPTIMIZATION */

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*=================================================================================================
*                                      LOCAL VARIABLES
=================================================================================================*/

/*=================================================================================================
*                                      GLOBAL CONSTANTS
=================================================================================================*/
#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/**
* @brief This table contains all the Configured Port Pin parameters and the
*        number of Port Pins configured by the tool for the post-build mode
*/
const Port_ConfigType Port_Config =
{
    PORT_MAX_CONFIGURED_PADS_U16,
    PORT_MAX_UNUSED_PADS_U16,
    {
        PORT_SIUL2_0_NUM_IMCRS_U16
    },
#if (PORT_MAX_UNUSED_PADS_U16 != 0U)
    Port_aUnusedPads,
#else
    NULL_PTR,
#endif
    &Port_UnusedPinConfig,
    Port_aUsedPinConfigs,
#ifdef PORT_CODE_SIZE_OPTIMIZATION
#if (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION)
    {
        Port_aSIUL2_0_ImcrInitConfig
    },
#else
    {
        NULL_PTR
    },
#endif /* (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION) */
#endif /* PORT_CODE_SIZE_OPTIMIZATION */
    au32Port_PinToPartitionMap,
    au8Port_PartitionList,
    g_pin_mux_InitConfigArr,
    aTspc_InitConfigArr
    };

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*=================================================================================================
*                                      GLOBAL VARIABLES
=================================================================================================*/

/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/

/*=================================================================================================
*                                       LOCAL FUNCTIONS
=================================================================================================*/

/*=================================================================================================
*                                       GLOBAL FUNCTIONS
=================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

/* End of File */
