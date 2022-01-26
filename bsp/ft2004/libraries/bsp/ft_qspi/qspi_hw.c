/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-02 18:32:42
 * @LastEditTime: 2021-04-02 18:32:43
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */
#include "qspi_hw.h"
#include "ft_qspi.h"
#include "ft_assert.h"
#include "ft_io.h"

void FQSpi_Reset(FQSpi_t *pQspi)
{
    FQSpi_Config_t *pConfig = NULL;
    Ft_assertVoid(pQspi != NULL);
    pConfig = &pQspi->config;
    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_CAP_OFFSET,
             FT_REG_QSPI_CAP_FLASH_NUM(pConfig->qspiDevNum) | FT_REG_QSPI_CAP_FLASH_CAP(pConfig->capacity));
}
