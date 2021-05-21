/*
 * @ : Copyright (c) 2020 Phytium Information Technology(TianJin), Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-03-31 14:59:20
 * @LastEditTime: 2021-04-07 13:40:04
 * @Description:  This files is for sd ctrl register-related implementations
 * 
 * @Modify History: * * Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_sdctrl_hw.h"
#include "ft_sdctrl.h"

#include "ft_io.h"
#include "ft_types.h"
#include "ft_assert.h"
#include "ft_generic_timer.h"

/**
 * @name: 
 * @msg: 
 * @in param: 
 * @inout param: 
 * @out param: 
 * @return {*}
 * @param {FT_INOUT FtsdCtrl_t} *pFtsdCtrl
 * @param {pFtsdCtrl_delayTimer_t} fDelayTimer
 */
void FSdCtrl_Reset(FT_INOUT FtsdCtrl_t *pFtsdCtrl, pFtsdCtrl_delayTimer_t fDelayTimer)
{
    FSdCtrl_Config_t *pConfig;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);

    pConfig = &pFtsdCtrl->config;
    /* trigger software reset for 1us */
    Ft_setBit32(pConfig->baseAddress + SOFTWARE_RESET_REG_OFFSET, SOFTWARE_RESET_SRST);
    /* Wait for reset is ok */
    Ft_GenericTimer_UsDelay(1);
    Ft_clearBit32(pConfig->baseAddress + SOFTWARE_RESET_REG_OFFSET, SOFTWARE_RESET_SRST);

    /* wait dat[0] to be high-lev */
    while ((!(Ft_in32(pConfig->baseAddress + STATUS_REG) & STATUS_REG_DLSL(1))))
    {
        fDelayTimer(1);
    }

    return;
}
