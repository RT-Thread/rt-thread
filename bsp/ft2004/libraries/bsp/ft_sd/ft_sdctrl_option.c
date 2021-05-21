/*
 * @ : Copyright (c) 2020 Phytium Information Technology(TianJin), Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-03-31 14:59:20
 * @LastEditTime: 2021-04-07 13:40:38
 * @Description:  This files is for sd ctrl option setting
 * 
 * @Modify History: * * Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_sdctrl.h"
#include "ft_sdctrl_hw.h"
#include "ft_types.h"
#include "ft_io.h"
#include "ft_printf.h"
#include "ft_assert.h"

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FtsdCtrl_t} *pFtsdCtrl
 * @param {FT_IN FSdCtrl_NormalIrqSelect_t} flgs
 */
void FSdCtrl_NormalIrqSet(FtsdCtrl_t *pFtsdCtrl, FT_IN FSdCtrl_NormalIrqSelect_t flgs)
{
    FSdCtrl_Config_t *pConfig;
    u32 regValue;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    /*  */
    regValue = ((flgs & NORMAL_IRQ_CC) ? NORMAL_INT_EN_ECC : 0) | ((flgs & NORMAL_IRQ_CR) ? NORMAL_INT_EN_ECCRCE : 0) |
               ((flgs & NORMAL_IRQ_EI) ? NORMAL_INT_EN_ECIE : 0);

    Ft_out32(pConfig->baseAddress + NORMAL_INT_EN_REG_OFFSET, regValue);
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FtsdCtrl_t} *pFtsdCtrl
 * @param {FT_IN FSdCtrl_ErrorIrqSelect_t} flgs
 */
void FsdCtrl_errorIrqSet(FtsdCtrl_t *pFtsdCtrl, FT_IN FSdCtrl_ErrorIrqSelect_t flgs)
{
    FSdCtrl_Config_t *pConfig;
    u32 regValue;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    regValue = ((flgs & ERROR_IRQ_CTE) ? ERROR_INT_EN_CTE : 0) | ((flgs & ERROR_IRQ_CCRCE) ? ERROR_INT_EN_CCRCE : 0) |
               ((flgs & ERROR_IRQ_CIR) ? ERROR_INT_EN_CIR : 0) | ((flgs & ERROR_IRQ_CNR) ? ERROR_INT_EN_CNR : 0);

    Ft_out32(pConfig->baseAddress + ERROR_INT_EN_REG_OFFSET, regValue);
}

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FtsdCtrl_t} *pFtsdCtrl
 * @param {FT_IN FSdCtrl_BdIrqSelect} flgs
 */
void FSdCtrl_BdIrqSet(FtsdCtrl_t *pFtsdCtrl, FT_IN FSdCtrl_BdIrqSelect flgs)
{
    FSdCtrl_Config_t *pConfig;
    u32 regValue;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;

    regValue = ((flgs & BD_IRQ_TRS) ? BD_ISR_EN_ETRS : 0) | ((flgs & BD_IRQ_DTE) ? BD_ISR_EN_EDTE : 0) |
               ((flgs & BD_IRQ_CMDE) ? BD_ISR_EN_ECMDE : 0) | ((flgs & BD_IRQ_TRE) ? BD_ISR_EN_ETRE : 0) |
               ((flgs & BD_IRQ_NRCRC) ? BD_ISR_EN_ENRCRCE : 0) | ((flgs & BD_IRQ_DATFRAX) ? BD_ISR_EN_EDATFRAXE : 0) |
               ((flgs & BD_IRQ_RESPE) ? BD_ISR_EN_RESPE : 0) | ((flgs & BD_IRQ_DAIS) ? BD_ISR_EN_EDAISE : 0);

    Ft_out32(pConfig->baseAddress + BD_ISR_EN_REG_OFFSET, regValue);
}
