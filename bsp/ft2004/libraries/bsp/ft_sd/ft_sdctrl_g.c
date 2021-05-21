/*
 * @ : Copyright (c) 2020 Phytium Information Technology(TianJin), Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-03-31 14:59:20
 * @LastEditTime: 2021-04-12 10:03:52
 * @Description:  This files is for sd ctrl config definition
 * 
 * @Modify History: * * Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_sdctrl.h"
#include "ft_parameters.h"

/* configs of sd ctrl */
FSdCtrl_Config_t FSdCtrl_Config[FT_SDC_NUM] =
    {
        {
            .instanceId = FT_SDC_INSTANCE,
            .baseAddress = FT_SDC_BASEADDR,
            .inputClockHz = FT_SDC_FREQ,
            .cardDetect = 1,
            .writeProtect = 0,
            .busWidth = 1,
            .dmaIrqNum = 52,
            .normalIrqNum = 53,
            .errIrqNum = 54,
            .workMode = 0 /*FTSDCTRL_CMD_IRQ_MASK | FTSDCTRL_DATA_WRITE_IRQ_MASK | FTSDCTRL_DATA_READ_IRQ_MASK*/
        }};
