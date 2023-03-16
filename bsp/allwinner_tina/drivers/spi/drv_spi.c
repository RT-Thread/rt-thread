/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-30     tanek        first implementation.
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <stdbool.h>

#include "drv_spi.h"
#include "drv_gpio.h"
#include "drv_clock.h"

#define SPI_BUS_MAX_CLK    (30 * 1000 * 1000)

//#define DEBUG

#define DBG_TAG  "SPI"
#ifdef DEBUG
#define DBG_LVL  DBG_LOG
#else
#define DBG_LVL  DBG_WARNING
#endif /* DEBUG */
#include <rtdbg.h>

#ifdef RT_USING_SPI

#define ARR_LEN(__N)      (sizeof(__N) / sizeof(__N[0]))

#define __SPI_STATIC_INLINE__ rt_inline

/*
 * @brief Hardware Layer Interface
 */
__SPI_STATIC_INLINE__
rt_uint32_t SPI_GetVersion(SPI_T *spi)
{
    return spi->VER;
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_Reset(SPI_T *spi)
{
    HAL_SET_BIT(spi->CTRL, SPI_CTRL_RST_MASK);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_SetMode(SPI_T *spi, SPI_CTRL_Mode mode)
{
    HAL_MODIFY_REG(spi->CTRL, SPI_CTRL_MODE_MASK, mode);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_Enable(SPI_T *spi)
{
    HAL_SET_BIT(spi->CTRL, SPI_CTRL_EN_MASK);
}

__SPI_STATIC_INLINE__
void SPI_Disable(SPI_T *spi)
{
    HAL_CLR_BIT(spi->CTRL, SPI_CTRL_EN_MASK);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_StartTransmit(SPI_T *spi)
{
    HAL_SET_BIT(spi->TCTRL, SPI_TCTRL_XCH_MASK);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_SetFirstTransmitBit(SPI_T *spi, SPI_TCTRL_Fbs bit)
{
    HAL_MODIFY_REG(spi->TCTRL, SPI_TCTRL_FBS_MASK, bit);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_EnableRapidsMode(SPI_T *spi, bool delay_sample)
{
    HAL_SET_BIT(spi->TCTRL, SPI_TCTRL_RPSM_MASK);
    HAL_MODIFY_REG(spi->TCTRL, SPI_TCTRL_SDC_MASK, delay_sample << SPI_TCTRL_SDC_SHIFT);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_DisableRapidsMode(SPI_T *spi)
{
    HAL_CLR_BIT(spi->TCTRL, SPI_TCTRL_RPSM_MASK);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_SetDuplex(SPI_T *spi, SPI_TCTRL_DHB_Duplex duplex)
{
    HAL_MODIFY_REG(spi->TCTRL, SPI_TCTRL_DHB_MASK, duplex);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_SetCsLevel(SPI_T *spi,  bool level)
{
    HAL_MODIFY_REG(spi->TCTRL, SPI_TCTRL_SS_LEVEL_MASK, level << SPI_TCTRL_SS_LEVEL_SHIFT);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_ManualChipSelect(SPI_T *spi, SPI_TCTRL_SS_Sel cs)
{
    HAL_SET_BIT(spi->TCTRL, SPI_TCTRL_SS_OWNER_MASK);
    HAL_MODIFY_REG(spi->TCTRL, SPI_TCTRL_SS_SEL_MASK, cs);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_AutoChipSelect(SPI_T *spi, SPI_TCTRL_SS_Sel cs, bool cs_remain)
{
    HAL_MODIFY_REG(spi->TCTRL, SPI_TCTRL_SS_SEL_MASK, cs);
    HAL_CLR_BIT(spi->TCTRL, SPI_TCTRL_SS_OWNER_MASK);
    HAL_MODIFY_REG(spi->TCTRL, SPI_TCTRL_SS_CTL_MASK, (!cs_remain) << SPI_TCTRL_SS_CTL_SHIFT);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_SetCsIdle(SPI_T *spi, bool idle)
{
    HAL_MODIFY_REG(spi->TCTRL, SPI_TCTRL_SPOL_MASK, (!!idle) << SPI_TCTRL_SPOL_SHIFT);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_SetSclkMode(SPI_T *spi, SPI_SCLK_Mode mode)
{
    HAL_MODIFY_REG(spi->TCTRL, SPI_TCTRL_CPOL_MASK | SPI_TCTRL_CPHA_MASK, mode);
}

typedef enum
{
    SPI_INT_CS_DESELECT = SPI_IER_SS_INT_EN_MASK,
    SPI_INT_TRANSFER_COMPLETE = SPI_IER_TC_INT_EN_MASK,
    SPI_INT_TXFIFO_UNDER_RUN = SPI_IER_TF_UDR_INT_EN_MASK,
    SPI_INT_TXFIFO_OVERFLOW = SPI_IER_TF_OVF_INT_EN_MASK,
    SPI_INT_RXFIFO_UNDER_RUN = SPI_IER_RF_UDR_INT_EN_MASK,
    SPI_INT_RXFIFO_OVERFLOW = SPI_IER_RF_OVF_INT_EN_MASK,
    SPI_INT_TXFIFO_FULL = SPI_IER_TF_FUL_INT_EN_MASK,
    SPI_INT_TXFIFO_EMPTY = SPI_IER_TX_EMP_INT_EN_MASK,
    SPI_INT_TXFIFO_READY = SPI_IER_TX_ERQ_INT_EN_MASK,
    SPI_INT_RXFIFO_FULL = SPI_IER_RF_FUL_INT_EN_MASK,
    SPI_INT_RXFIFO_EMPTY = SPI_IER_RX_EMP_INT_EN_MASK,
    SPI_INT_RXFIFO_READY = SPI_IER_RF_RDY_INT_EN_MASK
} SPI_Int_Type;

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_EnableInt(SPI_T *spi, SPI_Int_Type type)
{
    HAL_SET_BIT(spi->IER, type);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_DisableInt(SPI_T *spi, SPI_Int_Type type)
{
    HAL_CLR_BIT(spi->IER, type);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
bool SPI_IntState(SPI_T *spi, SPI_Int_Type type)
{
    return !!HAL_GET_BIT(spi->STA, type);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
bool SPI_ClearInt(SPI_T *spi, SPI_Int_Type type)
{
    HAL_SET_BIT(spi->STA, type);
    return HAL_GET_BIT(spi->STA, type);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_DebugReadTx(SPI_T *spi, rt_uint32_t *data)
{
    // tbc...
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_DebugWriteRx(SPI_T *spi, rt_uint32_t *data)
{
    // tbc...
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_ResetTxFifo(SPI_T *spi)
{
    HAL_SET_BIT(spi->FCTL, SPI_FCTL_TF_RST_MASK);
    while (HAL_GET_BIT(spi->FCTL, SPI_FCTL_TF_RST_MASK) != 0);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_ResetRxFifo(SPI_T *spi)
{
    HAL_SET_BIT(spi->FCTL, SPI_FCTL_RF_RST_MASK);
    while (HAL_GET_BIT(spi->FCTL, SPI_FCTL_RF_RST_MASK) != 0);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_DMA(SPI_T *spi, bool txEn, bool rxEn)
{
    HAL_MODIFY_REG(spi->FCTL,
                   SPI_FCTL_TF_DRQ_EN_MASK | SPI_FCTL_RF_DRQ_EN_MASK,
                   ((!!txEn) << SPI_FCTL_TF_DRQ_EN_SHIFT) | ((!!rxEn) << SPI_FCTL_RF_DRQ_EN_SHIFT));
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_SetTxFifoThreshold(SPI_T *spi, rt_uint8_t threshold)
{
    HAL_MODIFY_REG(spi->FCTL, SPI_FCTL_TX_TRIG_LEVEL_MASK, threshold << SPI_FCTL_TX_TRIG_LEVEL_SHIFT);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_SetRxFifoThreshold(SPI_T *spi, rt_uint8_t threshold)
{
    HAL_MODIFY_REG(spi->FCTL, SPI_FCTL_RX_TRIG_LEVEL_MASK, threshold << SPI_FCTL_RX_TRIG_LEVEL_SHIFT);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
rt_uint8_t SPI_GetTxFifoCounter(SPI_T *spi)
{
    return (rt_uint8_t)((spi->FST & SPI_FST_TF_CNT_MASK) >> SPI_FST_TF_CNT_SHIFT);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
rt_uint8_t SPI_GetRxFifoCounter(SPI_T *spi)
{
    return (rt_uint8_t)((spi->FST & SPI_FST_RF_CNT_MASK) >> SPI_FST_RF_CNT_SHIFT);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_EnableDualMode(SPI_T *spi)
{
    HAL_SET_BIT(spi->BCC, SPI_BCC_DRM_MASK);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_DisableDualMode(SPI_T *spi)
{
    HAL_CLR_BIT(spi->BCC, SPI_BCC_DRM_MASK);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_SetInterval(SPI_T *spi, rt_uint16_t nSCLK)
{
    HAL_MODIFY_REG(spi->WAIT, SPI_WAIT_WCC_MASK, nSCLK << SPI_WAIT_WCC_SHIFT);
}

/*
 * @brief
 */
static void SPI_SetClkDiv(SPI_T *spi, rt_uint16_t div)
{
    rt_uint8_t n = 0;
    if (div < 1)
    {
        return;
    }

    if (div > 2 * (0xFF + 1))
    {
        HAL_CLR_BIT(spi->CCTR, SPI_CCTR_DRS_MASK);
        do
        {
            div = (div == 1) ? 0 : ((div + 1) / 2);
            n++;
        }
        while (div);

        HAL_MODIFY_REG(spi->CCTR, SPI_CCTR_CDR1_MASK, (n & 0x0F) << SPI_CCTR_CDR1_SHIFT);
    }
    else
    {
        HAL_SET_BIT(spi->CCTR, SPI_CCTR_DRS_MASK);
        n = ((div + 1) / 2) - 1;
        HAL_MODIFY_REG(spi->CCTR, SPI_CCTR_CDR2_MASK, (n & 0xFF) << SPI_CCTR_CDR2_SHIFT);
    }
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_SetDataSize(SPI_T *spi, rt_uint32_t data_size, rt_uint32_t dummy_size)
{
    HAL_MODIFY_REG(spi->BC, SPI_BC_MBC_MASK, data_size + dummy_size);
    HAL_MODIFY_REG(spi->TC, SPI_TC_MWTC_MASK, data_size);
    HAL_MODIFY_REG(spi->BCC, SPI_BCC_STC_MASK, data_size);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_Write(SPI_T *spi, rt_uint8_t *data)
{
    HAL_REG_8BIT(&spi->TXD) = *data;
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
void SPI_Read(SPI_T *spi, rt_uint8_t *data)
{
    *data = HAL_REG_8BIT(&spi->RXD);
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
rt_uint8_t *SPI_TxAddress(SPI_T *spi)
{
    return (rt_uint8_t *)&spi->TXD;
}

/*
 * @brief
 */
__SPI_STATIC_INLINE__
rt_uint8_t *SPI_RxAddress(SPI_T *spi)
{
    return (rt_uint8_t *)&spi->RXD;
}

/* private rt-thread spi ops function */
static rt_err_t configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
static rt_uint32_t xfer(struct rt_spi_device *device, struct rt_spi_message *message);

static struct rt_spi_ops tina_spi_ops =
{
    configure,
    xfer
};

static rt_err_t configure(struct rt_spi_device *device,
                          struct rt_spi_configuration *configuration)
{
    struct rt_spi_bus *spi_bus = (struct rt_spi_bus *)device->bus;
    struct tina_spi_cs *tina_spi_cs = device->parent.user_data;
    struct tina_spi *_spi_info = (struct tina_spi *)spi_bus->parent.user_data;
    SPI_T *spi = _spi_info->spi;

    LOG_D("%s -> %d", __FUNCTION__, __LINE__);

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    LOG_D("%s -> %d", __FUNCTION__, __LINE__);

    LOG_D("spi address: %08X", (rt_uint32_t)spi);

    SPI_Disable(spi);
    SPI_Reset(spi);
    SPI_ResetRxFifo(spi);
    SPI_ResetTxFifo(spi);

    LOG_D("%s -> %d", __FUNCTION__, __LINE__);

    /* data_width */
    if (configuration->data_width != 8)
    {
        LOG_D("error: data_width is %d", configuration->data_width);
        return -RT_EIO;
    }

    LOG_D("%s -> %d", __FUNCTION__, __LINE__);
    SPI_SetDuplex(spi, SPI_TCTRL_DHB_FULL_DUPLEX);
    SPI_SetMode(spi, SPI_CTRL_MODE_MASTER);

    /* MSB or LSB */
    if (configuration->mode & RT_SPI_MSB)
    {
        SPI_SetFirstTransmitBit(spi, SPI_TCTRL_FBS_MSB);
    }
    else
    {
        SPI_SetFirstTransmitBit(spi, SPI_TCTRL_FBS_LSB);
    }

    switch (configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        SPI_SetSclkMode(spi, SPI_SCLK_Mode0);
        break;
    case RT_SPI_MODE_1:
        SPI_SetSclkMode(spi, SPI_SCLK_Mode1);
        break;
    case RT_SPI_MODE_2:
        SPI_SetSclkMode(spi, SPI_SCLK_Mode2);
        break;
    case RT_SPI_MODE_3:
        SPI_SetSclkMode(spi, SPI_SCLK_Mode3);
        break;
    }

    /* baudrate */
    {
        unsigned int spi_clock = 0;
        rt_uint32_t max_hz;
        rt_uint32_t div;

        LOG_D("%s -> %d", __FUNCTION__, __LINE__);

        max_hz = configuration->max_hz;

        if (max_hz > SPI_BUS_MAX_CLK)
        {
            max_hz = SPI_BUS_MAX_CLK;
        }
        spi_clock = ahb_get_clk();

        LOG_D("%s -> %d", __FUNCTION__, __LINE__);

        div = (spi_clock + max_hz - 1) / max_hz;

        LOG_D("configuration->max_hz: %d", configuration->max_hz);
        LOG_D("max freq: %d", max_hz);
        LOG_D("spi_clock: %d", spi_clock);
        LOG_D("div: %d", div);

        SPI_SetClkDiv(spi, div / 2);
    } /* baudrate */

    SPI_ManualChipSelect(spi, tina_spi_cs->cs);
    SPI_SetDataSize(spi, 0, 0);
    SPI_Enable(spi);

    LOG_D("%s -> %d", __FUNCTION__, __LINE__);

    return RT_EOK;
};

static rt_uint32_t xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct rt_spi_bus *r6_spi_bus = (struct rt_spi_bus *)device->bus;
    struct tina_spi *_spi_info = (struct tina_spi *)r6_spi_bus->parent.user_data;
    SPI_T *spi = _spi_info->spi;
    struct rt_spi_configuration *config = &device->config;
    struct tina_spi_cs *tina_spi_cs = device->parent.user_data;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    LOG_D("%s -> %d", __FUNCTION__, __LINE__);
    LOG_D("spi_info: %08X", (rt_uint32_t)_spi_info);
    LOG_D("spi address: %08X", (rt_uint32_t)spi);

    /* take CS */
    if (message->cs_take)
    {
        SPI_ManualChipSelect(spi, tina_spi_cs->cs);
        SPI_SetCsLevel(spi, false);
        LOG_D("spi take cs");
    }

    LOG_D("%s -> %d", __FUNCTION__, __LINE__);

    {
        if ((config->data_width <= 8) && (message->length > 0))
        {
            const rt_uint8_t *send_ptr = message->send_buf;
            rt_uint8_t *recv_ptr = message->recv_buf;
            rt_uint32_t tx_size = message->length;
            rt_uint32_t rx_size = message->length;

            LOG_D("spi poll transfer start: %d", tx_size);

            SPI_ResetTxFifo(spi);
            SPI_ResetRxFifo(spi);
            SPI_SetDataSize(spi, tx_size, 0);

            SPI_StartTransmit(spi);

            LOG_D("%s -> %d", __FUNCTION__, __LINE__);

            while (tx_size > 0 || rx_size > 0)
            {
                rt_uint8_t tx_data = 0xFF;
                rt_uint8_t rx_data = 0xFF;

                while ((SPI_GetTxFifoCounter(spi) < SPI_FIFO_SIZE) && (tx_size > 0))
                {
                    if (send_ptr != RT_NULL)
                    {
                        tx_data = *send_ptr++;
                    }
                    SPI_Write(spi, &tx_data);
                    tx_size--;
                }

                while (SPI_GetRxFifoCounter(spi) > 0)
                {
                    rx_size--;
                    SPI_Read(spi, &rx_data);

                    if (recv_ptr != RT_NULL)
                    {
                        *recv_ptr++ = rx_data;
                    }
                }
            }

            LOG_D("%s -> %d", __FUNCTION__, __LINE__);

            if ((tx_size != 0) || (rx_size != 0))
            {
                LOG_D("spi_tx_rx error with tx count = %d, rx count = %d.", tx_size, rx_size);

                return 0;
            }

            LOG_D("%s -> %d", __FUNCTION__, __LINE__);

            while (SPI_IntState(spi, SPI_INT_TRANSFER_COMPLETE) == 0);
            SPI_ClearInt(spi, SPI_INT_TRANSFER_COMPLETE);

            LOG_D("spi poll transfer finsh");
        }
        else if (config->data_width > 8)
        {
            LOG_D("data width: %d", config->data_width);
            RT_ASSERT(NULL);
        }
    }

    /* release CS */
    if (message->cs_release)
    {
        SPI_SetCsLevel(spi, true);
        LOG_D("spi release cs");
    }

    return message->length;
};

#ifdef TINA_USING_SPI0
static struct rt_spi_bus spi_bus0;
#endif

#ifdef TINA_USING_SPI1
static struct rt_spi_bus spi_bus1;
#endif

static const struct tina_spi spis[] =
{
#ifdef TINA_USING_SPI0
    {(SPI_T *)SPI0_BASE_ADDR, SPI0_GATING, &spi_bus0},
#endif

#ifdef TINA_USING_SPI1
    {(SPI_T *)SPI1_BASE_ADDR, SPI1_GATING, &spi_bus1},
#endif
};



/** \brief init and register r6 spi bus.
 *
 * \param SPI: R6 SPI, e.g: SPI1,SPI2,SPI3.
 * \param spi_bus_name: spi bus name, e.g: "spi1"
 * \return
 *
 */
rt_err_t tina_spi_bus_register(SPI_T *spi, const char *spi_bus_name)
{
    int i;

    LOG_D("%s -> %d", __FUNCTION__, __LINE__);

    RT_ASSERT(spi_bus_name != RT_NULL);

    for (i = 0; i < ARR_LEN(spis); i++)
    {
        if (spi == spis[i].spi)
        {
            bus_software_reset_disalbe(spis[i].spi_gate);
            bus_gate_clk_enalbe(spis[i].spi_gate);

            spis[i].spi_bus->parent.user_data = (void *)&spis[i];
            LOG_D("bus  addr: %08X", (rt_uint32_t)spis[i].spi_bus);
            LOG_D("user_data: %08X", (rt_uint32_t)spis[i].spi_bus->parent.user_data);
            LOG_D("%s -> %d", __FUNCTION__, __LINE__);
            rt_spi_bus_register(spis[i].spi_bus, spi_bus_name, &tina_spi_ops);
            LOG_D("%s -> %d", __FUNCTION__, __LINE__);
            return RT_EOK;
        }
    }

    LOG_D("%s -> %d", __FUNCTION__, __LINE__);

    return RT_ERROR;
}

int rt_hw_spi_init(void)
{
    LOG_D("register spi bus");

#ifdef TINA_USING_SPI0
    /* register spi bus */
    {
        rt_err_t result;

        LOG_D("%s -> %d", __FUNCTION__, __LINE__);

        gpio_set_func(GPIO_PORT_C, GPIO_PIN_0, IO_FUN_1);
        gpio_set_func(GPIO_PORT_C, GPIO_PIN_2, IO_FUN_1);
        gpio_set_func(GPIO_PORT_C, GPIO_PIN_3, IO_FUN_1);

        LOG_D("%s -> %d", __FUNCTION__, __LINE__);

        result = tina_spi_bus_register((SPI_T *)SPI0_BASE_ADDR, "spi0");
        if (result != RT_EOK)
        {
            LOG_D("%s -> %d", __FUNCTION__, __LINE__);
            return result;
        }
    }

    LOG_D("%s -> %d", __FUNCTION__, __LINE__);
    /* attach cs */
    {
        static struct rt_spi_device spi_device;
        static struct tina_spi_cs  spi_cs;
        rt_err_t result;

        LOG_D("%s -> %d", __FUNCTION__, __LINE__);
        spi_cs.cs = SPI_TCTRL_SS_SEL_SS0;

        LOG_D("%s -> %d", __FUNCTION__, __LINE__);
        gpio_set_func(GPIO_PORT_C, GPIO_PIN_1, IO_FUN_1);

        LOG_D("%s -> %d", __FUNCTION__, __LINE__);
        result = rt_spi_bus_attach_device(&spi_device, "spi00", "spi0", (void *)&spi_cs);
        if (result != RT_EOK)
        {
            LOG_D("%s -> %d", __FUNCTION__, __LINE__);
            return result;
        }
    }
    LOG_D("%s -> %d", __FUNCTION__, __LINE__);
#endif

#ifdef TINA_USING_SPI1
    /* register spi bus */
    {
        rt_err_t result;

        gpio_set_func(GPIO_PORT_A, GPIO_PIN_1,  IO_FUN_5);
        gpio_set_func(GPIO_PORT_A, GPIO_PIN_2,  IO_FUN_5);
        gpio_set_func(GPIO_PORT_A, GPIO_PIN_3, IO_FUN_5);

        result = tina_spi_bus_register((SPI_T *)SPI1_BASE_ADDR, "spi1");
        if (result != RT_EOK)
        {
            LOG_D("register spi bus faild: %d", result);
            return result;
        }
    }

    LOG_D("attach cs");
    /* attach cs */
    {
        static struct rt_spi_device spi_device;
        static struct tina_spi_cs spi_cs;
        rt_err_t result;

        spi_cs.cs = SPI_TCTRL_SS_SEL_SS0;
        gpio_set_func(GPIO_PORT_A, GPIO_PIN_0,  IO_FUN_5);

        result = rt_spi_bus_attach_device(&spi_device, "spi10", "spi1", (void *)&spi_cs);
        if (result != RT_EOK)
        {
            LOG_D("attach cs faild: %d", result);
            return result;
        }
    }
#endif

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);
#endif
