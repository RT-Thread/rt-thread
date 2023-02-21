/**************************************************************************//**
 * @file     qei.c
 * @brief    Quadrature Encoder Interface (QEI) driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup QEI_Driver QEI Driver
  @{
*/

/** @addtogroup QEI_EXPORTED_FUNCTIONS QEI Exported Functions
  @{
*/

/**
  * @brief      Close QEI function
  * @param[in]  qei         The pointer of the specified QEI module.
  * @return     None
  * @details    This function reset QEI configuration and stop QEI counting.
  */
void QEI_Close(QEI_T *qei)
{
    /* Reset QEI configuration */
    qei->CTL = (uint32_t)0;
}

/**
  * @brief      Disable QEI interrupt
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32IntSel   Interrupt type selection.
  *                         - \ref QEI_CTL_DIRIEN_Msk   : Direction change interrupt
  *                         - \ref QEI_CTL_OVUNIEN_Msk  : Counter overflow or underflow interrupt
  *                         - \ref QEI_CTL_CMPIEN_Msk   : Compare-match interrupt
  *                         - \ref QEI_CTL_IDXIEN_Msk   : Index detected interrupt
  * @return     None
  * @details    This function disable QEI specified interrupt.
  */
void QEI_DisableInt(QEI_T *qei, uint32_t u32IntSel)
{
    /* Disable QEI specified interrupt */
    QEI_DISABLE_INT(qei, u32IntSel);
}

/**
  * @brief      Enable QEI interrupt
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32IntSel   Interrupt type selection.
  *                         - \ref QEI_CTL_DIRIEN_Msk   : Direction change interrupt
  *                         - \ref QEI_CTL_OVUNIEN_Msk  : Counter overflow or underflow interrupt
  *                         - \ref QEI_CTL_CMPIEN_Msk   : Compare-match interrupt
  *                         - \ref QEI_CTL_IDXIEN_Msk   : Index detected interrupt
  * @return     None
  * @details    This function enable QEI specified interrupt.
  */
void QEI_EnableInt(QEI_T *qei, uint32_t u32IntSel)
{
    /* Enable QEI specified interrupt */
    QEI_ENABLE_INT(qei, u32IntSel);
}

/**
  * @brief      Open QEI in specified mode and enable input
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32Mode     QEI counting mode.
  *                         - \ref QEI_CTL_X4_FREE_COUNTING_MODE
  *                         - \ref QEI_CTL_X2_FREE_COUNTING_MODE
  *                         - \ref QEI_CTL_X4_COMPARE_COUNTING_MODE
  *                         - \ref QEI_CTL_X2_COMPARE_COUNTING_MODE
  * @param[in]  u32Value    The counter maximum value in compare-counting mode.
  * @return     None
  * @details    This function set QEI in specified mode and enable input.
  */
void QEI_Open(QEI_T *qei, uint32_t u32Mode, uint32_t u32Value)
{
    /* Set QEI function configuration */
    /* Set QEI counting mode */
    /* Enable IDX, QEA and QEB input to QEI controller */
    qei->CTL = (qei->CTL & (~QEI_CTL_MODE_Msk)) | ((u32Mode) | QEI_CTL_CHAEN_Msk | QEI_CTL_CHBEN_Msk | QEI_CTL_IDXEN_Msk);

    /* Set QEI maximum count value in in compare-counting mode */
    qei->CNTMAX = u32Value;
}

/**
  * @brief      Start QEI function
  * @param[in]  qei     The pointer of the specified QEI module.
  * @return     None
  * @details    This function enable QEI function and start QEI counting.
  */
void QEI_Start(QEI_T *qei)
{
    /* Enable QEI controller function */
    qei->CTL |= QEI_CTL_QEIEN_Msk;
}

/**
  * @brief      Stop QEI function
  * @param[in]  qei     The pointer of the specified QEI module.
  * @return     None
  * @details    This function disable QEI function and stop QEI counting.
  */
void QEI_Stop(QEI_T *qei)
{
    /* Disable QEI controller function */
    qei->CTL &= (~QEI_CTL_QEIEN_Msk);
}


/*@}*/ /* end of group QEI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group QEI_Driver */

/*@}*/ /* end of group Standard_Driver */

