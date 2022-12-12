/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-03-31 14:59:20
 * @LastEditTime: 2021-05-24 14:34:13
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
