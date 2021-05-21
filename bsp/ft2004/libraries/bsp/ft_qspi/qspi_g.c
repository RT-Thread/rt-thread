/*
 * @[H]: Copyright (C) 2014-2021 Tianjin Phytium Technology.  All rights reserved.
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  Use of the Software is limited solely to applications:
 *  (a) running on a Phytium device, or
 *  (b) that interact with a Phytium device through a bus or interconnect.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  PHYTIUM  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 *  OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 * 
 *  Except as contained in this notice, the name of the Phytium shall not be used
 *  in advertising or otherwise to promote the sale, use or other dealings in
 *  this Software without prior written authorization from Phytium. 
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