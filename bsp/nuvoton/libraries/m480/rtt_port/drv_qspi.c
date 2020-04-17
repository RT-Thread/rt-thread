/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of Nuvoton Technology Corp. nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Change Logs:
* Date            Author       Notes
* 2020-2-6        YH           First version
*
******************************************************************************/

#include <rtconfig.h>

#ifdef RT_USING_SPI

#include <rtdevice.h>
#include <NuMicro.h>

/* Private define ---------------------------------------------------------------*/
#define USING_QSPI0

/* Private Typedef --------------------------------------------------------------*/
struct nu_qspi
{
    struct rt_spi_bus dev;
    struct rt_spi_configuration configuration;
    QSPI_T *spi_base;
    rt_uint8_t init_gpio: 1;
};

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_qspi_bus_configure(struct rt_spi_device *device,
                                      struct rt_spi_configuration *configuration);
static rt_uint32_t nu_qspi_bus_xfer(struct rt_spi_device *device,
                                    struct rt_spi_message *message);

/* Private Variables ------------------------------------------------------------*/
static struct rt_spi_ops nu_qspi_poll_ops =
{
    .configure = nu_qspi_bus_configure,
    .xfer      = nu_qspi_bus_xfer,
};

#ifdef USING_QSPI0
static struct nu_qspi qspi0 =
{
    .spi_base = QSPI0,
};
#endif

static rt_err_t nu_qspi_bus_configure(struct rt_spi_device *device,
                                      struct rt_spi_configuration *configuration)
{

    struct nu_qspi *spi;
    uint32_t u32QSPIMode;
    uint32_t u32BusClock;
    rt_uint8_t init_bus;

    spi = (struct nu_qspi *) device->bus;
    init_bus = 0;

    if (!spi->init_gpio)
    {
        spi->init_gpio = 1;
        init_bus = 1;

        if (spi->spi_base == QSPI0)
        {
            /* Select PCLK0 as the clock source of QSPI0 */
            CLK_SetModuleClock(QSPI0_MODULE, CLK_CLKSEL2_QSPI0SEL_PLL,
                               MODULE_NoMsk);

            /* Enable QSPI0 peripheral clock */
            CLK_EnableModuleClock(QSPI0_MODULE);

            /* Setup QSPI0 multi-function pins */
            SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC0MFP_Msk | SYS_GPC_MFPL_PC1MFP_Msk
                               | SYS_GPC_MFPL_PC2MFP_Msk | SYS_GPC_MFPL_PC3MFP_Msk);
            SYS->GPC_MFPL |= SYS_GPC_MFPL_PC0MFP_QSPI0_MOSI0 | SYS_GPC_MFPL_PC1MFP_QSPI0_MISO0
                             | SYS_GPC_MFPL_PC2MFP_QSPI0_CLK | SYS_GPC_MFPL_PC3MFP_QSPI0_SS;

            /* Enable SPI0 clock pin (PC2) schmitt trigger */
            PC->SMTEN |= GPIO_SMTEN_SMTEN2_Msk;
        }
    }

    if (rt_memcmp(configuration, &spi->configuration, sizeof(*configuration)) != 0)
    {
        rt_memcpy(&spi->configuration, configuration, sizeof(*configuration));
        init_bus = 1;
    }

    if (init_bus)
    {
        switch (configuration->mode & RT_SPI_MODE_3)
        {
        case RT_SPI_MODE_0:
            u32QSPIMode = QSPI_MODE_0;
            break;
        case RT_SPI_MODE_1:
            u32QSPIMode = QSPI_MODE_1;
            break;
        case RT_SPI_MODE_2:
            u32QSPIMode = QSPI_MODE_2;
            break;
        case RT_SPI_MODE_3:
            u32QSPIMode = QSPI_MODE_3;
            break;
        default:
            RT_ASSERT(0);
        }

        u32BusClock = configuration->max_hz;
        if (u32BusClock > 50 * 1000 * 1000)
        {
            u32BusClock = 50 * 1000 * 1000;
        }

        QSPI_Open(spi->spi_base, QSPI_MASTER, u32QSPIMode, configuration->data_width, u32BusClock);

        QSPI_EnableAutoSS(spi->spi_base, QSPI_SS, QSPI_SS_ACTIVE_LOW);

        if (configuration->mode & RT_SPI_MSB)
        {
            QSPI_SET_MSB_FIRST(spi->spi_base);
        }
        else
        {
            QSPI_SET_LSB_FIRST(spi->spi_base);
        }
    }

    return RT_EOK;
}

/**
 * @brief SPI bus polling
 * @param dev : The pointer of the specified QSPI module.
 * @param send_addr : Source address
 * @param recv_addr : Destination address
 * @param length    : Data length
 */
static void qspi_transmission_with_poll(struct nu_qspi *spi_bus,
                                        const uint8_t *send_addr, uint8_t *recv_addr, int length)
{
    QSPI_T *spi_base = spi_bus->spi_base;

    // Write
    if (send_addr != RT_NULL && recv_addr == RT_NULL)
    {
        while (length--)
        {
            // Wait QSPI TX send data
            while (QSPI_GET_TX_FIFO_FULL_FLAG(spi_base));

            // Input data to QSPI TX
            QSPI_WRITE_TX(spi_base, *send_addr++);
        }

        // Wait QSPI transmission done
        while (QSPI_IS_BUSY(spi_base));
    }
    // Read&Write
    else if (send_addr != RT_NULL && recv_addr != RT_NULL)
    {
        // Clear QSPI RX FIFO
        if (!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
        {
            QSPI_ClearRxFIFO(spi_base);
            while (!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base));
        }

        while (length--)
        {
            // Wait QSPI TX send data
            while (QSPI_GET_TX_FIFO_FULL_FLAG(spi_base));

            // Input data to QSPI TX
            QSPI_WRITE_TX(spi_base, *send_addr++);

            // Read RX data
            while (!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
            {
                *recv_addr++ = QSPI_READ_RX(spi_base);
            }
        }

        // Wait QSPI transmission done
        while (QSPI_IS_BUSY(spi_base))
        {
            while (!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
            {
                *recv_addr++ = QSPI_READ_RX(spi_base);
            }
        }
    }
    // Read
    else
    {
        // Clear QSPI RX FIFO
        if (!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
        {
            QSPI_ClearRxFIFO(spi_base);
            while (!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base));
        }

        while (length--)
        {
            // Wait QSPI TX send data
            while (QSPI_GET_TX_FIFO_FULL_FLAG(spi_base));

            // Input data to QSPI TX
            QSPI_WRITE_TX(spi_base, 0x00);

            // Read RX data
            while (!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
            {
                *recv_addr++ = QSPI_READ_RX(spi_base);
            }
        }

        // Wait QSPI transmission done
        while (QSPI_IS_BUSY(spi_base))
        {
            while (!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
            {
                *recv_addr++ = QSPI_READ_RX(spi_base);
            }
        }

        while (!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
        {
            *recv_addr++ = QSPI_READ_RX(spi_base);
        }
    }
}

static rt_uint32_t nu_qspi_bus_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct nu_qspi *spi;

    spi = (struct nu_qspi *) device->bus;

    if (message->cs_take)
    {
        QSPI_SET_SS_LOW(spi->spi_base);
    }

    if (message->length > 0)
    {
        qspi_transmission_with_poll(spi, message->send_buf,
                                    message->recv_buf, message->length);
    }

    if (message->cs_release)
    {
        QSPI_SET_SS_HIGH(spi->spi_base);
    }

    return message->length;
}

static int nu_qspi_register_bus(struct nu_qspi *spi_bus, const char *name)
{
    return rt_spi_bus_register(&spi_bus->dev, name, &nu_qspi_poll_ops);
}

/**
 * Hardware SPI Initial
 */
static int rt_hw_qspi_init(void)
{
#ifdef USING_QSPI0
    nu_qspi_register_bus(&qspi0, "qspi0");
#endif

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_qspi_init);
#endif

