/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-27 15:31:44
 * @LastEditTime: 2021-04-27 15:31:44
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#include "ft_can.h"
#include "ft_parameters.h"

FCan_Config_t FCan_Config[FT_CAN_NUM] =
    {
        {
            .InstanceId = 0,                    /* Id of device */
            .CanBaseAddress = FT_CAN0_BASEADDR, /* Can base Address */
            .IrqNum = FT_CAN0_IRQNUM,
            .BaudRate = 250000,
            .TxFifoDeepth = 16,
        },
        {
            .InstanceId = 1,                    /* Id of device */
            .CanBaseAddress = FT_CAN1_BASEADDR, /* Can base Address */
            .IrqNum = FT_CAN1_IRQNUM,
            .BaudRate = 250000,
            .TxFifoDeepth = 16,
        },
        {
            .InstanceId = 2,                    /* Id of device */
            .CanBaseAddress = FT_CAN2_BASEADDR, /* Can base Address */
            .IrqNum = FT_CAN2_IRQNUM,
            .BaudRate = 250000,
            .TxFifoDeepth = 16,
        }};
