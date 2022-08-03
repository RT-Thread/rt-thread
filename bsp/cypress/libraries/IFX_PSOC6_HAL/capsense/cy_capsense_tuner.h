/***************************************************************************//**
* \file cy_capsense_tuner.h
* \version 3.0
*
* \brief
* This file provides CAPSENSE&trade; MW Tuner module function prototypes.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_TUNER_H)
#define CY_CAPSENSE_TUNER_H

#include "cy_syslib.h"
#include "cy_capsense_structure.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
* Macros Definitions
*******************************************************************************/
#define CY_CAPSENSE_COMMAND_PACKET_SIZE             (16u)
#define CY_CAPSENSE_COMMAND_CRC_DATA_SIZE           (11u)

#define CY_CAPSENSE_COMMAND_HEAD_0_IDX              (0u)
#define CY_CAPSENSE_COMMAND_HEAD_1_IDX              (1u)
#define CY_CAPSENSE_COMMAND_CODE_0_IDX              (2u)
#define CY_CAPSENSE_COMMAND_CNTR_0_IDX              (3u)
#define CY_CAPSENSE_COMMAND_SIZE_0_IDX              (4u)
#define CY_CAPSENSE_COMMAND_OFFS_0_IDX              (5u)
#define CY_CAPSENSE_COMMAND_OFFS_1_IDX              (6u)
#define CY_CAPSENSE_COMMAND_DATA_0_IDX              (7u)
#define CY_CAPSENSE_COMMAND_DATA_1_IDX              (8u)
#define CY_CAPSENSE_COMMAND_DATA_2_IDX              (9u)
#define CY_CAPSENSE_COMMAND_DATA_3_IDX              (10u)
#define CY_CAPSENSE_COMMAND_CRC_0_IDX               (11u)
#define CY_CAPSENSE_COMMAND_CRC_1_IDX               (12u)
#define CY_CAPSENSE_COMMAND_TAIL_0_IDX              (13u)
#define CY_CAPSENSE_COMMAND_TAIL_1_IDX              (14u)
#define CY_CAPSENSE_COMMAND_TAIL_2_IDX              (15u)

#define CY_CAPSENSE_COMMAND_HEAD_0                  (0x0Du)
#define CY_CAPSENSE_COMMAND_HEAD_1                  (0x0Au)
#define CY_CAPSENSE_COMMAND_TAIL_0                  (0x00u)
#define CY_CAPSENSE_COMMAND_TAIL_1                  (0xFFu)
#define CY_CAPSENSE_COMMAND_TAIL_2                  (0xFFu)

#define CY_CAPSENSE_COMMAND_OK                      (0u)
#define CY_CAPSENSE_WRONG_HEADER                    (1u)
#define CY_CAPSENSE_WRONG_CRC                       (2u)
#define CY_CAPSENSE_WRONG_TAIL                      (3u)
#define CY_CAPSENSE_WRONG_CODE                      (4u)

#define CY_CAPSENSE_MSB_SHIFT                       (8u)

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************/
/** \addtogroup group_capsense_high_level *//** \{ */
/******************************************************************************/

uint32_t Cy_CapSense_RunTuner(cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_CheckTunerCmdIntegrity(const uint8_t * commandPacket);

/** \} */

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/

void Cy_CapSense_TuInitialize(cy_stc_capsense_context_t * context);


/*******************************************************************************
* Function Name: Cy_CapSense_CheckCommandIntegrity
****************************************************************************//**
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_CheckTunerCmdIntegrity() function should be used instead.
*
* \param commandPacket
* The pointer to the data packet that should be verified.
*
* \return
* Returns the result of the command verification.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_CapSense_CheckCommandIntegrity(const uint8_t * commandPacket)
{
    return(Cy_CapSense_CheckTunerCmdIntegrity(commandPacket));
}


/*******************************************************************************
* Function Name: Cy_CapSense_CalculateCrc16
****************************************************************************//**
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_GetCRC() function should be used instead.
*
* \param ptrData
* The pointer to the data.
*
* \param len
* The length of the data in bytes.
*
* \return
* Returns a calculated CRC-16 value.
*
*******************************************************************************/
__STATIC_INLINE uint16_t Cy_CapSense_CalculateCrc16(const uint8_t *ptrData, uint32_t len)
{
    return(Cy_CapSense_GetCRC(ptrData, len));
}

/** \} \endcond */


#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */

#endif /* CY_CAPSENSE_TUNER_H */


/* [] END OF FILE */
