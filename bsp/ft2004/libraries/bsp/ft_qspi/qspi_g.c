/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 11:31:12
 * @LastEditTime: 2021-04-07 11:31:13
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 * *   v1.0   hh       2021-04-07    init
 */
#include "ft_qspi.h"
#include "ft_parameters.h"

FQSpi_Config_t FqSpi_ConfigTable[FT_QSPI_NUM] = {
    {.instanceId = FT_QSPI_INSTANCE,      /* Id of device */
     .baseAddress = FT_QSPI_BASEADDR,     /* Base address of qspi */
     .transMode = FT_QSPI_TRANSFER_1_1_1, /* Transfer mode */
     .capacity = FT_QSPI_FLASH_CAP_32MB,  /* Flash capacity */
     .addrMode = FT_QSPI_ADDR_SEL_3,      /**/
     .clkDiv = FT_QSPI_SCK_DIV_128,
     .qspiDevNum = 1,
     .channel = 0,
     .bitWidth = 8}};
