/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-2-7        Wayne            First version
*
******************************************************************************/

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtconfig.h>

#include <rtdevice.h>
#include "NuMicro.h"
#include <nu_bitutil.h>

#if defined(BSP_USING_SPI_PDMA)
    #include <drv_pdma.h>
#endif

struct nu_spi
{
    struct rt_spi_bus dev;
    char *name;
    SPI_T *spi_base;
    E_SYS_IPRST rstidx;
    E_SYS_IPCLK clkidx;
    uint32_t dummy;
#if defined(BSP_USING_SPI_PDMA)
    int16_t pdma_perp_tx;
    int8_t  pdma_chanid_tx;
    int16_t pdma_perp_rx;
    int8_t  pdma_chanid_rx;
    rt_sem_t m_psSemBus;
#endif
    struct rt_qspi_configuration  configuration;
};

typedef struct nu_spi *nu_spi_t;

void nu_spi_drain_rxfifo(SPI_T *spi_base);
void nu_spi_transfer(struct nu_spi *spi_bus, uint8_t *tx, uint8_t *rx, int length, uint8_t bytes_per_word);

#if defined(BSP_USING_SPI_PDMA)
    rt_err_t nu_hw_spi_pdma_allocate(struct nu_spi *spi_bus);
#endif

#endif // __DRV_SPI_H___
