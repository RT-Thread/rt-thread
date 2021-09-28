/******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_rmu.c
 **
 ** A detailed description is available at
 ** @link RmuGroup RMU description @endlink
 **
 **   - 2018-10-28  CDT  First version for Device Driver Library of RMU.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_rmu.h"
#include "hc32f460_utility.h"

#if (DDL_RMU_ENABLE == DDL_ON)

/**
 *******************************************************************************
 ** \addtogroup RmuGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define ENABLE_RMU_REG_WRITE()            (M4_SYSREG->PWR_FPRC = 0xa502u)
#define DISABLE_RMU_REG_WRITE()           (M4_SYSREG->PWR_FPRC = 0xa500u)

#define RMU_FLAG_TIM                      ((uint16_t)0x1000u)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief Get the chip reset cause.
 **
 ** \param [in] pstcData          Pointer to return reset cause structure.
 **
 ** \retval Ok                    Get successfully.
 **
 ******************************************************************************/
en_result_t RMU_GetResetCause(stc_rmu_rstcause_t *pstcData)
{
    uint16_t u16RstCause = 0u;
    stc_sysreg_rmu_rstf0_field_t *RMU_RSTF0_f = NULL;

    if(NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }

    u16RstCause = M4_SYSREG->RMU_RSTF0;
    RMU_RSTF0_f = (stc_sysreg_rmu_rstf0_field_t *)(&u16RstCause);

    pstcData->enMultiRst = (en_flag_status_t)(RMU_RSTF0_f->MULTIRF == 1u);
    pstcData->enXtalErr = (en_flag_status_t)(RMU_RSTF0_f->XTALERF == 1u);
    pstcData->enClkFreqErr = (en_flag_status_t)(RMU_RSTF0_f->CKFERF == 1u);
    pstcData->enRamEcc = (en_flag_status_t)(RMU_RSTF0_f->RAECRF == 1u);
    pstcData->enRamParityErr = (en_flag_status_t)(RMU_RSTF0_f->RAPERF == 1u);
    pstcData->enMpuErr = (en_flag_status_t)(RMU_RSTF0_f->MPUERF == 1u);
    pstcData->enSoftware = (en_flag_status_t)(RMU_RSTF0_f->SWRF == 1u);
    pstcData->enPowerDown = (en_flag_status_t)(RMU_RSTF0_f->PDRF == 1u);
    pstcData->enSwdt = (en_flag_status_t)(RMU_RSTF0_f->SWDRF == 1u);
    pstcData->enWdt = (en_flag_status_t)(RMU_RSTF0_f->WDRF == 1u);
    pstcData->enPvd2 = (en_flag_status_t)(RMU_RSTF0_f->PVD2RF == 1u);
    pstcData->enPvd1 = (en_flag_status_t)(RMU_RSTF0_f->PVD2RF == 1u);
    pstcData->enBrownOut = (en_flag_status_t)(RMU_RSTF0_f->BORF == 1u);
    pstcData->enRstPin = (en_flag_status_t)(RMU_RSTF0_f->PINRF == 1u);
    pstcData->enPowerOn = (en_flag_status_t)(RMU_RSTF0_f->PORF == 1u);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief Clear the reset flag.
 **
 ** \param None
 **
 ** \retval Ok                    Clear successfully.
 **
 ** \note   clear reset flag should be done after read RMU_RSTF0 register.
 ******************************************************************************/
en_result_t RMU_ClrResetFlag(void)
{
    uint16_t u16status  = 0u;
    uint32_t u32timeout = 0u;

    ENABLE_RMU_REG_WRITE();

    do
    {
        u32timeout++;
        M4_SYSREG->RMU_RSTF0_f.CLRF = 1u;
        u16status = M4_SYSREG->RMU_RSTF0;
    }while((u32timeout != RMU_FLAG_TIM) && u16status);

     DISABLE_RMU_REG_WRITE();

     if(u32timeout >= RMU_FLAG_TIM)
    {
        return ErrorTimeout;
    }

    return Ok;
}


//@} // RmuGroup

#endif /* DDL_RMU_ENABLE */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

