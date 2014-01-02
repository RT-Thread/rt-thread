/**********************************************************************
* $Id$      lpc_qei.c           2011-06-02
*//**
* @file     lpc_qei.c
* @brief    Contains all functions support for QEI firmware library
*           on LPC
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
/** @addtogroup QEI
 * @{
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _QEI

/* Includes ------------------------------------------------------------------- */
#include "lpc_qei.h"
#include "lpc_clkpwr.h"

/* Private Types -------------------------------------------------------------- */
/** @defgroup QEI_Private_Types QEI Private Types
 * @{
 */

/**
 * @brief QEI configuration union type definition
 */
typedef union {
    QEI_CFG_Type bmQEIConfig;
    uint32_t ulQEIConfig;
} QEI_CFGOPT_Type;

/**
 * @}
 */

LPC_QEI_TypeDef* QEI_GetPointer(uint8_t qeiId);


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup QEI_Public_Functions
 * @{
 */

/*********************************************************************//**
 * @brief       Get the point to typedef of QEI component
 * @param[in]   qeiId           The Id of the expected QEI component
 *                              It should be 0 (zero) always with LPC
 * @return      None
 **********************************************************************/
LPC_QEI_TypeDef* QEI_GetPointer(uint8_t qeiId)
{
    LPC_QEI_TypeDef* pQei = NULL;

    if(qeiId == 0)
    {
        pQei = LPC_QEI;
    }

    return pQei;
}


/*********************************************************************//**
 * @brief       Resets value for each type of QEI value, such as velocity,
 *              counter, position, etc..
 * @param[in]   qeiId           The Id of the expected QEI component
 *                              It should be 0 (zero) always with LPC
 *
 * @param[in]   ulResetType     QEI Reset Type, should be one of the following:
 *                              - QEI_RESET_POS: Reset Position Counter
 *                              - QEI_RESET_POSOnIDX: Reset Position Counter on Index signal
 *                              - QEI_RESET_VEL: Reset Velocity
 *                              - QEI_RESET_IDX: Reset Index Counter
 * @return      None
 **********************************************************************/
void QEI_Reset(uint8_t qeiId, uint32_t ulResetType)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    pQei->CON = ulResetType;
}

/*********************************************************************//**
 * @brief       Initializes the QEI peripheral according to the specified
*               parameters in the QEI_ConfigStruct.
* @param[in]    qeiId           The Id of the expected QEI component
*                               It should be 0 (zero) always with LPC
*
* @param[in]    QEI_ConfigStruct    Pointer to a QEI_CFG_Type structure
*                    that contains the configuration information for the
*                    specified QEI peripheral
 * @return      None
 **********************************************************************/
void QEI_Init(uint8_t qeiId, QEI_CFG_Type *QEI_ConfigStruct)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    /* Set up clock and power for QEI module */
    CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCQEI, ENABLE);

    // Reset all remaining value in QEI peripheral

    pQei->MAXPOS = 0x00;
    pQei->CMPOS0 = 0x00;
    pQei->CMPOS1 = 0x00;
    pQei->CMPOS2 = 0x00;
    pQei->INXCMP0 = 0x00;
    pQei->VELCOMP = 0x00;

    pQei->LOAD = 0x00;
    pQei->CON = QEI_CON_RESP | QEI_CON_RESV | QEI_CON_RESI;

    pQei->FILTERPHA = 0x00;
    pQei->FILTERPHB = 0x00;
    pQei->FILTERINX = 0x00;

    // Disable all Interrupt
    pQei->IEC = QEI_IECLR_BITMASK;

    // Clear all Interrupt pending
    pQei->CLR = QEI_INTCLR_BITMASK;

    // Set QEI configuration value corresponding to its setting up value
    pQei->CONF = ((QEI_CFGOPT_Type *)QEI_ConfigStruct)->ulQEIConfig;
}


/*********************************************************************//**
 * @brief       De-initializes the QEI peripheral registers to their
 *                  default reset values.
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @return      None
 **********************************************************************/
void QEI_DeInit(uint8_t qeiId)
{
    /* Turn off clock and power for QEI module */
    CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCQEI, DISABLE);
}


/*****************************************************************************//**
* @brief        Fills each QIE_InitStruct member with its default value:
*               - DirectionInvert = QEI_DIRINV_NONE
*               - SignalMode = QEI_SIGNALMODE_QUAD
*               - CaptureMode = QEI_CAPMODE_4X
*               - InvertIndex = QEI_INVINX_NONE
* @param[in]    QIE_InitStruct Pointer to a QEI_CFG_Type structure
*                    which will be initialized.
* @return       None
*******************************************************************************/
void QEI_GetCfgDefault(QEI_CFG_Type *QIE_InitStruct)
{
    QIE_InitStruct->CaptureMode = QEI_CAPMODE_4X;
    QIE_InitStruct->DirectionInvert = QEI_DIRINV_NONE;
    QIE_InitStruct->InvertIndex = QEI_INVINX_NONE;
    QIE_InitStruct->SignalMode = QEI_SIGNALMODE_QUAD;
}


/*********************************************************************//**
 * @brief       Check whether if specified flag status is set or not
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   ulFlagType  Status Flag Type, should be one of the following:
 *                          - QEI_STATUS_DIR: Direction Status
 * @return      New Status of this status flag (SET or RESET)
 **********************************************************************/
FlagStatus QEI_GetStatus(uint8_t qeiId, uint32_t ulFlagType)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    return ((pQei->STAT & ulFlagType) ? SET : RESET);
}

/*********************************************************************//**
 * @brief       Get current position value in QEI peripheral
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @return      Current position value of QEI peripheral
 **********************************************************************/
uint32_t QEI_GetPosition(uint8_t qeiId)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    return (pQei->POS);
}

/*********************************************************************//**
 * @brief       Set max position value for QEI peripheral
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   ulMaxPos    Max position value to set
 * @return      None
 **********************************************************************/
void QEI_SetMaxPosition(uint8_t qeiId, uint32_t ulMaxPos)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    pQei->MAXPOS = ulMaxPos;
}

/*********************************************************************//**
 * @brief       Set position compare value for QEI peripheral
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   bPosCompCh  Compare Position channel, should be:
 *                          - QEI_COMPPOS_CH_0: QEI compare position channel 0
 *                          - QEI_COMPPOS_CH_1: QEI compare position channel 1
 *                          - QEI_COMPPOS_CH_2: QEI compare position channel 2
 * @param[in]   ulPosComp   Compare Position value to set
 * @return      None
 **********************************************************************/
void QEI_SetPositionComp(uint8_t qeiId, uint8_t bPosCompCh, uint32_t ulPosComp)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);
    uint32_t *tmp;

    tmp = (uint32_t *) (&(pQei->CMPOS0) + bPosCompCh * 4);
    *tmp = ulPosComp;
}

/*********************************************************************//**
 * @brief       Get current index counter of QEI peripheral
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @return      Current value of QEI index counter
 **********************************************************************/
uint32_t QEI_GetIndex(uint8_t qeiId)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    return (pQei->INXCNT);
}

/*********************************************************************//**
 * @brief       Set value for index compare in QEI peripheral
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   ulIndexComp     Compare Index Value to set
 * @return      None
 **********************************************************************/
void QEI_SetIndexComp(uint8_t qeiId, uint32_t ulIndexComp)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    pQei->INXCMP0 = ulIndexComp;
}

/*********************************************************************//**
 * @brief       Set timer reload value for QEI peripheral. When the velocity timer is
 *              over-flow, the value that set for Timer Reload register will be loaded
 *              into the velocity timer for next period. The calculated velocity in RPM
 *              therefore will be affect by this value.
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   QEIReloadStruct QEI reload structure
 * @return      None
 **********************************************************************/
void QEI_SetTimerReload(uint8_t qeiId, QEI_RELOADCFG_Type *QEIReloadStruct)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);
    uint64_t pclk;


    if (QEIReloadStruct->ReloadOption == QEI_TIMERRELOAD_TICKVAL)
    {
        pQei->LOAD = QEIReloadStruct->ReloadValue - 1;
    }
    else
    {
#if 1
        pclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);

        pclk = (pclk /(1000000/QEIReloadStruct->ReloadValue)) - 1;

        pQei->LOAD = (uint32_t)pclk;
#else
        ld = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);

        if (ld/1000000 > 0)
        {
            ld /= 1000000;
            ld *= QEIReloadStruct->ReloadValue;
            ld -= 1;
        }
        else
        {
            ld *= QEIReloadStruct->ReloadValue;
            ld /= 1000000;
            ld -= 1;
        }

        pQei->LOAD = ld;
#endif
    }
}

/*********************************************************************//**
 * @brief       Get current timer counter in QEI peripheral
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @return      Current timer counter in QEI peripheral
 **********************************************************************/
uint32_t QEI_GetTimer(uint8_t qeiId)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    return (pQei->TIME);
}

/*********************************************************************//**
 * @brief       Get current velocity pulse counter in current time period
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @return      Current velocity pulse counter value
 **********************************************************************/
uint32_t QEI_GetVelocity(uint8_t qeiId)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    return (pQei->VEL);
}

/*********************************************************************//**
 * @brief       Get the most recently measured velocity of the QEI. When
 *              the Velocity timer in QEI is over-flow, the current velocity
 *              value will be loaded into Velocity Capture register.
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @return      The most recently measured velocity value
 **********************************************************************/
uint32_t QEI_GetVelocityCap(uint8_t qeiId)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    return (pQei->CAP);
}

/*********************************************************************//**
 * @brief       Set Velocity Compare value for QEI peripheral
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   ulVelComp       Compare Velocity value to set
 * @return      None
 **********************************************************************/
void QEI_SetVelocityComp(uint8_t qeiId, uint32_t ulVelComp)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    pQei->VELCOMP = ulVelComp;
}

/*********************************************************************//**
 * @brief       Set value of sampling count for the digital filter in
 *              QEI peripheral
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   ulSamplingPulse Value of sampling count to set
 * @return      None
 **********************************************************************/
void QEI_SetDigiFilter(uint8_t qeiId, st_Qei_FilterCfg FilterVal)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    pQei->FILTERPHA = FilterVal.PHA_FilterVal;
    pQei->FILTERPHB = FilterVal.PHB_FilterVal;
    pQei->FILTERINX = FilterVal.INX_FilterVal;
}

/*********************************************************************//**
 * @brief       Check whether if specified interrupt flag status in QEI
 *              peripheral is set or not
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   ulIntType       Interrupt Flag Status type, should be:
                - QEI_INTFLAG_INX_Int: index pulse was detected interrupt
                - QEI_INTFLAG_TIM_Int: Velocity timer over flow interrupt
                - QEI_INTFLAG_VELC_Int: Capture velocity is less than compare interrupt
                - QEI_INTFLAG_DIR_Int: Change of direction interrupt
                - QEI_INTFLAG_ERR_Int: An encoder phase error interrupt
                - QEI_INTFLAG_ENCLK_Int: An encoder clock pulse was detected interrupt
                - QEI_INTFLAG_POS0_Int: position 0 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_POS1_Int: position 1 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_POS2_Int: position 2 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_REV_Int: Index compare value is equal to the current
                                        index count interrupt
                - QEI_INTFLAG_POS0REV_Int: Combined position 0 and revolution count interrupt
                - QEI_INTFLAG_POS1REV_Int: Combined position 1 and revolution count interrupt
                - QEI_INTFLAG_POS2REV_Int: Combined position 2 and revolution count interrupt
 * @return      New State of specified interrupt flag status (SET or RESET)
 **********************************************************************/
FlagStatus QEI_GetIntStatus(uint8_t qeiId, uint32_t ulIntType)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    return((pQei->INTSTAT & ulIntType) ? SET : RESET);
}

/*********************************************************************//**
 * @brief       Enable/Disable specified interrupt in QEI peripheral
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   ulIntType       Interrupt Flag Status type, should be:
                - QEI_INTFLAG_INX_Int: index pulse was detected interrupt
                - QEI_INTFLAG_TIM_Int: Velocity timer over flow interrupt
                - QEI_INTFLAG_VELC_Int: Capture velocity is less than compare interrupt
                - QEI_INTFLAG_DIR_Int: Change of direction interrupt
                - QEI_INTFLAG_ERR_Int: An encoder phase error interrupt
                - QEI_INTFLAG_ENCLK_Int: An encoder clock pulse was detected interrupt
                - QEI_INTFLAG_POS0_Int: position 0 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_POS1_Int: position 1 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_POS2_Int: position 2 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_REV_Int: Index compare value is equal to the current
                                        index count interrupt
                - QEI_INTFLAG_POS0REV_Int: Combined position 0 and revolution count interrupt
                - QEI_INTFLAG_POS1REV_Int: Combined position 1 and revolution count interrupt
                - QEI_INTFLAG_POS2REV_Int: Combined position 2 and revolution count interrupt
 * @param[in]   NewState        New function state, should be:
 *                              - DISABLE
 *                              - ENABLE
 * @return      None
 **********************************************************************/
void QEI_IntCmd(uint8_t qeiId, uint32_t ulIntType, FunctionalState NewState)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    if (NewState == ENABLE)
    {
        pQei->IES = ulIntType;
    }
    else
    {
        pQei->IEC = ulIntType;
    }
}


/*********************************************************************//**
 * @brief       Sets (forces) specified interrupt in QEI peripheral
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   ulIntType       Interrupt Flag Status type, should be:
                - QEI_INTFLAG_INX_Int: index pulse was detected interrupt
                - QEI_INTFLAG_TIM_Int: Velocity timer over flow interrupt
                - QEI_INTFLAG_VELC_Int: Capture velocity is less than compare interrupt
                - QEI_INTFLAG_DIR_Int: Change of direction interrupt
                - QEI_INTFLAG_ERR_Int: An encoder phase error interrupt
                - QEI_INTFLAG_ENCLK_Int: An encoder clock pulse was detected interrupt
                - QEI_INTFLAG_POS0_Int: position 0 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_POS1_Int: position 1 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_POS2_Int: position 2 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_REV_Int: Index compare value is equal to the current
                                        index count interrupt
                - QEI_INTFLAG_POS0REV_Int: Combined position 0 and revolution count interrupt
                - QEI_INTFLAG_POS1REV_Int: Combined position 1 and revolution count interrupt
                - QEI_INTFLAG_POS2REV_Int: Combined position 2 and revolution count interrupt
 * @return      None
 **********************************************************************/
void QEI_IntSet(uint8_t qeiId, uint32_t ulIntType)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    pQei->SET = ulIntType;
}

/*********************************************************************//**
 * @brief       Clear (force) specified interrupt (pending) in QEI peripheral
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   ulIntType       Interrupt Flag Status type, should be:
                - QEI_INTFLAG_INX_Int: index pulse was detected interrupt
                - QEI_INTFLAG_TIM_Int: Velocity timer over flow interrupt
                - QEI_INTFLAG_VELC_Int: Capture velocity is less than compare interrupt
                - QEI_INTFLAG_DIR_Int: Change of direction interrupt
                - QEI_INTFLAG_ERR_Int: An encoder phase error interrupt
                - QEI_INTFLAG_ENCLK_Int: An encoder clock pulse was detected interrupt
                - QEI_INTFLAG_POS0_Int: position 0 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_POS1_Int: position 1 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_POS2_Int: position 2 compare value is equal to the
                                        current position interrupt
                - QEI_INTFLAG_REV_Int: Index compare value is equal to the current
                                        index count interrupt
                - QEI_INTFLAG_POS0REV_Int: Combined position 0 and revolution count interrupt
                - QEI_INTFLAG_POS1REV_Int: Combined position 1 and revolution count interrupt
                - QEI_INTFLAG_POS2REV_Int: Combined position 2 and revolution count interrupt
 * @return      None
 **********************************************************************/
void QEI_IntClear(uint8_t qeiId, uint32_t ulIntType)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    pQei->CLR = ulIntType;
}


/*********************************************************************//**
 * @brief       Calculates the actual velocity in RPM passed via velocity
 *              capture value and Pulse Per Round (of the encoder) value
 *              parameter input.
 * @param[in]    qeiId           The Id of the expected QEI component
 *                               It should be 0 (zero) always with LPC
 *
 * @param[in]   ulVelCapValue   Velocity capture input value that can
 *                              be got from QEI_GetVelocityCap() function
 * @param[in]   ulPPR           Pulse per round of encoder
 * @return      The actual value of velocity in RPM (Round per minute)
 **********************************************************************/
uint32_t QEI_CalculateRPM(uint8_t qeiId, uint32_t ulVelCapValue, uint32_t ulPPR)
{
    LPC_QEI_TypeDef* pQei = QEI_GetPointer(qeiId);

    uint64_t rpm, clock, Load, edges;

    // Get current Clock rate for timer input
    clock = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);

    // Get Timer load value (velocity capture period)
    Load  = (uint64_t)(pQei->LOAD + 1);

    // Get Edge
    edges = (uint64_t)((pQei->CONF & QEI_CONF_CAPMODE) ? 4 : 2);

    // Calculate RPM
    rpm = ((clock * ulVelCapValue * 60) / (Load * ulPPR * edges));

    return (uint32_t)(rpm);
}


/**
 * @}
 */

#endif /*_QEI*/

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

