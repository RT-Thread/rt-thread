/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <board.h>
#include "drv_hard_i2c.h"
#include "drv_config.h"
#include <string.h>

#if defined(BSP_USING_HARD_I2C1) || defined(BSP_USING_HARD_I2C2) || defined(BSP_USING_HARD_I2C3) || defined(BSP_USING_HARD_I2C4) || defined(BSP_USING_HARD_I2C5) || \
    defined(BSP_USING_HARD_I2C6) || defined(BSP_USING_HARD_I2C7) || defined(BSP_USING_HARD_I2C8) || defined(BSP_USING_HARD_I2C9) || defined(BSP_USING_HARD_I2C10)


#define I2C_CTRL2_NBYTES_POS         (16U)
#define MAX_NBYTE_SIZE               (255U)

#define I2C_NO_STARTSTOP             (0x00000000U)
#define I2C_START_READ               (I2C_CTRL2_START | I2C_CTRL2_RWN)
#define I2C_START_WRITE              (I2C_CTRL2_START)

#define I2C_RELOAD_MODE              (CTRL2_REFILL_ENABLE)
#define I2C_AUTOEND_MODE             (CTRL2_AUTO_STOP)
#define I2C_SOFTEND_MODE             (0x00000000U)

#define I2C_FIRST_FRAME              ((uint32_t)I2C_SOFTEND_MODE)
#define I2C_FIRST_AND_NEXT_FRAME     ((uint32_t)(I2C_RELOAD_MODE | I2C_SOFTEND_MODE))
#define I2C_NEXT_FRAME               ((uint32_t)(I2C_RELOAD_MODE | I2C_SOFTEND_MODE))
#define I2C_FIRST_AND_LAST_FRAME     ((uint32_t)I2C_AUTOEND_MODE)
#define I2C_LAST_FRAME               ((uint32_t)I2C_AUTOEND_MODE)
#define I2C_LAST_FRAME_NO_STOP       ((uint32_t)I2C_SOFTEND_MODE)

/* Slave address | Transfer direction | START generation | STOP generation | Number of bytes | NBYTES reload mode | Automatic end mode */
#define I2C_CTRL2_CLEAR              (I2C_CTRL2_SADR | I2C_CTRL2_RWN | I2C_CTRL2_START | I2C_CTRL2_STOP | I2C_CTRL2_BYTECNT | I2C_CTRL2_REFILL | I2C_CTRL2_AUTOSTOP)

//#define DRV_DEBUG
#define LOG_TAG "drv.i2c.hw"
#include <drv_log.h>

static rt_bool_t first_valid_rx_isr = RT_FALSE;
static void i2c_master_ev_isr_handler_it(struct n32_i2c *drv_i2c);
static void i2c_master_ev_isr_handler_dma(struct n32_i2c *drv_i2c);

enum
{
#ifdef BSP_USING_HARD_I2C1
    I2C1_INDEX,
#endif /* BSP_USING_HARD_I2C1 */
#ifdef BSP_USING_HARD_I2C2
    I2C2_INDEX,
#endif /* BSP_USING_HARD_I2C2 */
#ifdef BSP_USING_HARD_I2C3
    I2C3_INDEX,
#endif /* BSP_USING_HARD_I2C3 */
#ifdef BSP_USING_HARD_I2C4
    I2C4_INDEX,
#endif /* BSP_USING_HARD_I2C4 */
#ifdef BSP_USING_HARD_I2C5
    I2C5_INDEX,
#endif /* BSP_USING_HARD_I2C5 */
#ifdef BSP_USING_HARD_I2C6
    I2C6_INDEX,
#endif /* BSP_USING_HARD_I2C6 */
#ifdef BSP_USING_HARD_I2C7
    I2C7_INDEX,
#endif /* BSP_USING_HARD_I2C7 */
#ifdef BSP_USING_HARD_I2C8
    I2C8_INDEX,
#endif /* BSP_USING_HARD_I2C8 */
#ifdef BSP_USING_HARD_I2C9
    I2C9_INDEX,
#endif /* BSP_USING_HARD_I2C9 */
#ifdef BSP_USING_HARD_I2C10
    I2C10_INDEX,
#endif /* BSP_USING_HARD_I2C10 */
};

static struct n32_i2c_config i2c_config[] =
{
#ifdef BSP_USING_HARD_I2C1
    I2C1_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C1 */
#ifdef BSP_USING_HARD_I2C2
    I2C2_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C2 */
#ifdef BSP_USING_HARD_I2C3
    I2C3_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C3 */
#ifdef BSP_USING_HARD_I2C4
    I2C4_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C4 */
#ifdef BSP_USING_HARD_I2C5
    I2C5_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C5 */
#ifdef BSP_USING_HARD_I2C6
    I2C6_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C6 */
#ifdef BSP_USING_HARD_I2C7
    I2C7_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C7 */
#ifdef BSP_USING_HARD_I2C8
    I2C8_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C8 */
#ifdef BSP_USING_HARD_I2C9
    I2C9_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C9 */
#ifdef BSP_USING_HARD_I2C10
    I2C10_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C10 */
};

static struct n32_i2c i2c_objs[sizeof(i2c_config) / sizeof(i2c_config[0])] = {0};

static rt_ssize_t n32_iic_transfer_by_dma(struct n32_i2c_config *config, uint8_t *pData, uint16_t Size, rt_bool_t is_rx)
{
    struct dma_config *dma_config;

    RT_ASSERT(config != RT_NULL);
    RT_ASSERT(pData != RT_NULL);

    if (is_rx)
    {
        dma_config = config->dma_rx;
    }
    else
    {
        dma_config = config->dma_tx;
    }

#if defined(SOC_SERIES_N32H7xx)
    /* Check whether DMA Channel is disable */
    if (DMA_ChannelIsEnabled(dma_config->Instance, dma_config->dma_channel))
    {
        /* Disable DMA Channel */
        DMA_ChannelCmd(dma_config->Instance, dma_config->dma_channel, DISABLE);
    }

    if (is_rx)
    {
        /* Sets the destination address of the specified channel */
        DMA_SetChannelDestinationAddress(dma_config->Instance, dma_config->dma_channel, (uint32_t *)pData);
    }
    else
    {
        /* Sets the source address of the specified channel */
        DMA_SetChannelSourceAddress(dma_config->Instance, dma_config->dma_channel, (uint32_t *)pData);
    }

    /* Sets the block transfer size of the specified channel */
    DMA_SetChannelBlockSize(dma_config->Instance, dma_config->dma_channel, Size);

    /* Clear a DMA channel event status */
    DMA_ClearChannelEventStatus(dma_config->Instance, dma_config->dma_channel, DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE);

    /* Enable transaction complete interrupt event */
    DMA_ChannelEventCmd(dma_config->Instance, dma_config->dma_channel, DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE, ENABLE);

    /* Configure DMAMUX */
    DMAMUX_SetRequestID(DMAMUX1_ID, dma_config->dmamux_channel, dma_config->dmamux_request);

    /* Enable the specified DMA channel */
    DMA_ChannelCmd(dma_config->Instance, dma_config->dma_channel, ENABLE);
#endif

    return Size;
}


static rt_err_t n32_i2c_dma_init(struct n32_i2c_config *config, rt_bool_t is_rx)
{
    struct dma_config *dma_config;
    DMA_ChInitType DMA_ChInitStr;

    RT_ASSERT(config != RT_NULL);

#if defined(SOC_SERIES_N32H7xx)
    /* Enable DMAMUX clock  */
    RCC_EnableAHB1PeriphClk1(RCC_AHB1_PERIPHEN_M7_DMAMUX1, ENABLE);

    /* DMA channel struct configuration */
    DMA_ChannelStructInit(&DMA_ChInitStr);
    DMA_ChInitStr.SrcTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
    DMA_ChInitStr.DstTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
    DMA_ChInitStr.DstBurstLen        = DMA_CH_BURST_LENGTH_1;
    DMA_ChInitStr.SrcBurstLen        = DMA_CH_BURST_LENGTH_1;
    DMA_ChInitStr.ChannelPriority    = DMA_CH_PRIORITY_7;
    DMA_ChInitStr.TfrType            = DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;

    /* Read by DMA */
    if (is_rx)
    {
        dma_config = config->dma_rx;

        /* DMA clock enable */
        RCC_EnableAHB1PeriphClk3(dma_config->dma_rcc, ENABLE);

        /* DMA channel struct configuration */
        DMA_ChInitStr.SrcAddr            = (uint32_t)&config->Instance->RDR;
        DMA_ChInitStr.DstAddr            = (uint32_t)RT_NULL;
        DMA_ChInitStr.DstAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
        DMA_ChInitStr.SrcAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
        DMA_ChInitStr.TfrTypeFlowCtrl    = DMA_CH_TRANSFER_FLOW_P2M_DMA;
        DMA_ChInitStr.SrcHandshaking     = DMA_CH_SRC_HANDSHAKING_HARDWARE;
        DMA_ChInitStr.SrcHsInterface     = dma_config->HsInterface;
    }
    /* Write by DMA */
    else
    {
        dma_config = config->dma_tx;

        /* DMA clock enable */
        RCC_EnableAHB1PeriphClk3(dma_config->dma_rcc, ENABLE);

        /* DMA channel struct configuration */
        DMA_ChInitStr.SrcAddr            = (uint32_t) RT_NULL;
        DMA_ChInitStr.DstAddr            = (uint32_t)&config->Instance->WDR;
        DMA_ChInitStr.DstAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
        DMA_ChInitStr.SrcAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
        DMA_ChInitStr.TfrTypeFlowCtrl    = DMA_CH_TRANSFER_FLOW_M2P_DMA;
        DMA_ChInitStr.DstHandshaking     = DMA_CH_DST_HANDSHAKING_HARDWARE;
        DMA_ChInitStr.DstHsInterface     = dma_config->HsInterface;
    }

    /* DMA controller must be enabled before initializing the channel */
    DMA_ControllerCmd(dma_config->Instance, ENABLE);

    /* Initialize the specified DMA channel */
    if (DMA_ChannelInit(dma_config->Instance, &DMA_ChInitStr, dma_config->dma_channel) != 0)
    {
        return -RT_ERROR;
    }
#endif

    /* enable dma irq */
    NVIC_SetPriority(dma_config->dma_irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(dma_config->dma_irq);

    return RT_EOK;
}

static rt_err_t n32_i2c_init(struct n32_i2c *i2c_drv)
{
    rt_err_t ret;
    uint32_t BusTim_Reg;
    I2C_InitType I2C_InitStructure;
    RT_ASSERT(i2c_drv != RT_NULL);

    struct n32_i2c_config *cfg = i2c_drv->config;

    /* Enable I2C Clock */
    cfg->EnablePeriphClk(cfg->periph, ENABLE);

#if defined(SOC_SERIES_N32H7xx)
    /* Call I2C_Configuration() from an external file */
    I2C_Configuration();
    /* Disable IIC */
    I2C_Enable(cfg->Instance, DISABLE);
    /* Get IIC BUSTIM Register value */
    BusTim_Reg = cfg->Instance->BUSTIM;

    if (BusTim_Reg == 0U)
    {
        /* IIC Kernal use default kernal clock */
        RCC_ConfigHse(RCC_HSE_ENABLE);
        if (RCC_WaitHseStable() != SUCCESS)
        {
            return -RT_ERROR;
        }
        RCC_ConfigPll3(RCC_PLL_SRC_HSE, HSE_VALUE, 480000000, ENABLE);
        RCC_ConfigPLL3CDivider(RCC_PLLC_DIV10);
        /*Choose I2C1 ker clk source*/
        cfg->I2CKerClkSource(RCC_I2CKERCLK_SRC_PLL3C);
    }
#endif

    /* Deinitializes the I2Cx peripheral registers to their default reset values */
    I2C_DeInit(cfg->Instance);

    I2C_InitStruct(&I2C_InitStructure);
    I2C_InitStructure.Timing           = ((BusTim_Reg != 0) ? BusTim_Reg : cfg->timing);
    I2C_InitStructure.OwnAddress1      = 0x0;
    I2C_InitStructure.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    I2C_InitStructure.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    I2C_InitStructure.OwnAddress2      = 0x0;
    I2C_InitStructure.OwnAddress2Masks = I2C_ADDRESS2MASK_NONE;
    I2C_InitStructure.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    I2C_InitStructure.NoStretchMode    = I2C_NOSTRCH_DISABLE;
    I2C_Init(cfg->Instance, &I2C_InitStructure);

    I2C_Enable(cfg->Instance, ENABLE);

#if defined(SOC_SERIES_N32H7xx)
    /* Configure Analogue filter */
    I2C_EnableAnalogFilter(cfg->Instance, ENABLE);
    I2C_EnableSDAAnalogFilter(cfg->Instance, ENABLE);
    I2C_EnableSCLAnalogFilter(cfg->Instance, ENABLE);
    I2C_SetSCLAnalogFilterWidth(cfg->Instance, cfg->scl_af_width);
    I2C_SetSDAAnalogFilterWidth(cfg->Instance, cfg->sda_af_width);

    /* Configure Digital filter */
    I2C_SetDigitalFilterWidth(cfg->Instance, cfg->df_width);
#endif /* defined(SOC_SERIES_N32H7xx) */

    /* I2C2 DMA Init */
    if (i2c_drv->i2c_dma_flag & I2C_USING_RX_DMA_FLAG)
    {
        ret = n32_i2c_dma_init(cfg, RT_TRUE);
        RT_ASSERT(ret == RT_EOK);
    }

    if (i2c_drv->i2c_dma_flag & I2C_USING_TX_DMA_FLAG)
    {
        ret = n32_i2c_dma_init(cfg, RT_FALSE);
        RT_ASSERT(ret == RT_EOK);
    }

    /* Enable Event IRQ */
    NVIC_SetPriority(i2c_drv->config->evirq_type, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
    NVIC_EnableIRQ(i2c_drv->config->evirq_type);

    /* Enable Error IRQ */
    NVIC_SetPriority(i2c_drv->config->erirq_type, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
    NVIC_EnableIRQ(i2c_drv->config->erirq_type);

    i2c_drv->transfer.state = I2C_READY;

    return RT_EOK;
}

static rt_err_t n32_i2c_master_seq_receive_it(struct n32_i2c *i2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{
    uint32_t setmask;
    uint32_t xfermode;

    if (i2c->transfer.state == I2C_READY)
    {
        first_valid_rx_isr = RT_FALSE;
        /* Set transfer parameters */
        i2c->transfer.state = I2C_BUSY_RX;
        i2c->transfer.pBuffPtr = pData;
        i2c->transfer.XferCount = Size;
        i2c->transfer.XferOptions = XferOptions;
        i2c->i2c_isr_callback = i2c_master_ev_isr_handler_it;

        /* If i2c->transfer.XferCount > MAX_NBYTE_SIZE, use reload mode */
        if (Size > MAX_NBYTE_SIZE)
        {
            i2c->transfer.XferSize = MAX_NBYTE_SIZE;
            xfermode = I2C_RELOAD_MODE;   // Use reload mode
        }
        else
        {
            i2c->transfer.XferSize = i2c->transfer.XferCount;
            xfermode = i2c->transfer.XferOptions;
        }

        /* Slave address | Transfer direction | START generation | STOP generation | Number of bytes | NBYTES reload mode | Automatic end mode */
        setmask = ((uint32_t)DevAddress & I2C_CTRL2_SADR) | (uint32_t)I2C_START_READ | (((uint32_t)i2c->transfer.XferSize << I2C_CTRL2_NBYTES_POS) & I2C_CTRL2_BYTECNT) | (uint32_t)xfermode;

        /* Set IIC CTRL2 Register */
        MODIFY_REG(i2c->config->Instance->CTRL2, I2C_CTRL2_CLEAR, (uint32_t)setmask);

        I2C_ConfigInt(i2c->config->Instance, I2C_INT_ERR | I2C_INT_TFC | I2C_INT_STOP | I2C_INT_NACK | I2C_INT_RDR, ENABLE);

        return RT_EOK;
    }
    else
    {
        return -RT_EBUSY;
    }
}

static rt_err_t n32_i2c_master_seq_send_it(struct n32_i2c *i2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{
    uint32_t setmask;
    uint32_t xfermode;

    if (i2c->transfer.state == I2C_READY)
    {
        /* Set transfer parameters */
        i2c->transfer.state = I2C_BUSY_TX;
        i2c->transfer.pBuffPtr = pData;
        i2c->transfer.XferCount = Size;
        i2c->transfer.XferOptions = XferOptions;
        i2c->i2c_isr_callback = i2c_master_ev_isr_handler_it;

        /* If i2c->transfer.XferCount > MAX_NBYTE_SIZE, use reload mode */
        if (Size > MAX_NBYTE_SIZE)
        {
            i2c->transfer.XferSize = MAX_NBYTE_SIZE;
            xfermode = I2C_RELOAD_MODE;   // Use reload mode
        }
        else
        {
            i2c->transfer.XferSize = i2c->transfer.XferCount;
            xfermode = i2c->transfer.XferOptions;
        }

        I2C_ConfigInt(i2c->config->Instance, I2C_INT_ERR | I2C_INT_TFC | I2C_INT_STOP | I2C_INT_NACK | I2C_INT_WDR, ENABLE);

        /* Slave address | Transfer direction | START generation | STOP generation | Number of bytes | NBYTES reload mode | Automatic end mode */
        setmask = ((uint32_t)DevAddress & I2C_CTRL2_SADR) | (uint32_t)I2C_START_WRITE | (((uint32_t)i2c->transfer.XferSize << I2C_CTRL2_NBYTES_POS) & I2C_CTRL2_BYTECNT) | (uint32_t)xfermode;

        /* Wait for bus idele */
        while ((i2c->config->Instance->STSINT & I2C_STSINT_BUSY) == I2C_STSINT_BUSY)
        {
        }

        /* Set IIC CTRL2 Register */
        MODIFY_REG(i2c->config->Instance->CTRL2, I2C_CTRL2_CLEAR, (uint32_t)setmask);

        return RT_EOK;
    }
    else
    {
        return -RT_EBUSY;
    }
}

static rt_err_t n32_i2c_master_seq_receive_dma(struct n32_i2c *i2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{
    uint32_t setmask;
    uint32_t xfermode;

    if (i2c->transfer.state == I2C_READY)
    {
        first_valid_rx_isr = RT_FALSE;
        /* Set transfer parameters */
        i2c->transfer.state = I2C_BUSY_RX;
        i2c->transfer.pBuffPtr = pData;
        i2c->transfer.XferCount = Size;
        i2c->transfer.XferOptions = XferOptions;
        i2c->i2c_isr_callback = i2c_master_ev_isr_handler_dma;

        /* If i2c->transfer.XferCount > MAX_NBYTE_SIZE, use reload mode */
        if (Size > MAX_NBYTE_SIZE)
        {
            i2c->transfer.XferSize = MAX_NBYTE_SIZE;
            xfermode = I2C_RELOAD_MODE;   // Use reload mode
        }
        else
        {
            i2c->transfer.XferSize = i2c->transfer.XferCount;
            xfermode = i2c->transfer.XferOptions;
        }

        if (i2c->transfer.XferSize > 0U)
        {
            n32_iic_transfer_by_dma(i2c->config, i2c->transfer.pBuffPtr, i2c->transfer.XferSize, RT_TRUE);

            /* Slave address | Transfer direction | START generation | STOP generation | Number of bytes | NBYTES reload mode | Automatic end mode */
            setmask = ((uint32_t)DevAddress & I2C_CTRL2_SADR) | (uint32_t)I2C_START_READ | (((uint32_t)i2c->transfer.XferSize << I2C_CTRL2_NBYTES_POS) & I2C_CTRL2_BYTECNT) | (uint32_t)xfermode;

            /* Set IIC CTRL2 Register */
            MODIFY_REG(i2c->config->Instance->CTRL2, I2C_CTRL2_CLEAR, (uint32_t)setmask);

            /* Update XferCount value */
            i2c->transfer.XferCount -= i2c->transfer.XferSize;

            /* Enable ERR and NACK interrupts */
            i2c->config->Instance->CTRL1 |= (I2C_CTRL1_ERRIE | I2C_CTRL1_NAKIE);

            /* Enable DMA Request */
            i2c->config->Instance->CTRL1 |= I2C_CTRL1_DMARDEN;
        }
        else
        {
            i2c->i2c_isr_callback = i2c_master_ev_isr_handler_it;

            /* Slave address | Transfer direction | START generation | STOP generation | Number of bytes | NBYTES reload mode | Automatic end mode */
            setmask = ((uint32_t)DevAddress & I2C_CTRL2_SADR) | (uint32_t)I2C_START_READ | (((uint32_t)i2c->transfer.XferSize << I2C_CTRL2_NBYTES_POS) & I2C_CTRL2_BYTECNT) | (uint32_t)I2C_AUTOEND_MODE;

            /* Set IIC CTRL2 Register */
            MODIFY_REG(i2c->config->Instance->CTRL2, I2C_CTRL2_CLEAR, (uint32_t)setmask);

            i2c->config->Instance->CTRL1 |= (I2C_CTRL1_ERRIE | I2C_CTRL1_TFCIE | I2C_CTRL1_STOPIE | I2C_CTRL1_NAKIE | I2C_CTRL1_WDRIE);
        }

        return RT_EOK;
    }
    else
    {
        return -RT_EBUSY;
    }
}

static rt_err_t n32_i2c_master_seq_send_dma(struct n32_i2c *i2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{
    uint32_t setmask;
    uint32_t xfermode;

    if (i2c->transfer.state == I2C_READY)
    {
        /* Set transfer parameters */
        i2c->transfer.state = I2C_BUSY_TX;
        i2c->transfer.pBuffPtr = pData;
        i2c->transfer.XferCount = Size;
        i2c->transfer.XferOptions = XferOptions;
        i2c->i2c_isr_callback = i2c_master_ev_isr_handler_dma;

        /* If i2c->transfer.XferCount > MAX_NBYTE_SIZE, use reload mode */
        if (Size > MAX_NBYTE_SIZE)
        {
            i2c->transfer.XferSize = MAX_NBYTE_SIZE;
            xfermode = I2C_RELOAD_MODE;   // Use reload mode
        }
        else
        {
            i2c->transfer.XferSize = i2c->transfer.XferCount;
            xfermode = i2c->transfer.XferOptions;
        }

        if (i2c->transfer.XferSize > 0U)
        {
            n32_iic_transfer_by_dma(i2c->config, i2c->transfer.pBuffPtr, i2c->transfer.XferSize, RT_FALSE);

            /* Slave address | Transfer direction | START generation | STOP generation | Number of bytes | NBYTES reload mode | Automatic end mode */
            setmask = ((uint32_t)DevAddress & I2C_CTRL2_SADR) | (uint32_t)I2C_START_WRITE | (((uint32_t)i2c->transfer.XferSize << I2C_CTRL2_NBYTES_POS) & I2C_CTRL2_BYTECNT) | (uint32_t)xfermode;

            /* Set IIC CTRL2 Register */
            MODIFY_REG(i2c->config->Instance->CTRL2, I2C_CTRL2_CLEAR, (uint32_t)setmask);

            /* Update XferCount value */
            i2c->transfer.XferCount -= i2c->transfer.XferSize;

            /* Enable ERR and NACK interrupts */
            i2c->config->Instance->CTRL1 |= (I2C_CTRL1_ERRIE | I2C_CTRL1_NAKIE);

            /* Enable DMA Request */
            i2c->config->Instance->CTRL1 |= I2C_CTRL1_DMAWREN;
        }
        else
        {
            i2c->i2c_isr_callback = i2c_master_ev_isr_handler_it;

            /* Slave address | Transfer direction | START generation | STOP generation | Number of bytes | NBYTES reload mode | Automatic end mode */
            setmask = ((uint32_t)DevAddress & I2C_CTRL2_SADR) | (uint32_t)I2C_START_WRITE | (((uint32_t)i2c->transfer.XferSize << I2C_CTRL2_NBYTES_POS) & I2C_CTRL2_BYTECNT) | (uint32_t)I2C_AUTOEND_MODE;

            /* Set IIC CTRL2 Register */
            MODIFY_REG(i2c->config->Instance->CTRL2, I2C_CTRL2_CLEAR, (uint32_t)setmask);

            i2c->config->Instance->CTRL1 |= (I2C_CTRL1_ERRIE | I2C_CTRL1_TFCIE | I2C_CTRL1_STOPIE | I2C_CTRL1_NAKIE | I2C_CTRL1_WDRIE);
        }

        return RT_EOK;
    }
    else
    {
        return -RT_EBUSY;
    }
}

static rt_err_t n32_i2c_configure(struct rt_i2c_bus_device *bus)
{
    RT_ASSERT(RT_NULL != bus);
    struct n32_i2c *i2c_drv = rt_container_of(bus, struct n32_i2c, i2c_bus);

    return n32_i2c_init(i2c_drv);
}

static rt_ssize_t n32_i2c_master_xfer(struct rt_i2c_bus_device *bus,
                                      struct rt_i2c_msg msgs[],
                                      rt_uint32_t num)
{
#define DMA_TRANS_MIN_LEN 2 /* only buffer length >= DMA_TRANS_MIN_LEN will use DMA mode */
#define TRANS_TIMEOUT_PERSEC 8 /* per ms will trans nums bytes */

    rt_int32_t i, ret;
    struct rt_i2c_msg *msg = msgs;
    struct rt_i2c_msg *next_msg = 0;
    struct n32_i2c *i2c_obj;
    uint32_t mode = 0;
    uint8_t next_flag = 0;
    struct rt_completion *completion;
    rt_uint32_t timeout;
    if (num == 0)
    {
        return 0;
    }
    RT_ASSERT((msgs != RT_NULL) && (bus != RT_NULL));

    i2c_obj = rt_container_of(bus, struct n32_i2c, i2c_bus);
    completion = &i2c_obj->completion;

    LOG_D("xfer start %d mags", num);
    for (i = 0; i < (num - 1); i++)
    {
        mode = 0;
        msg = &msgs[i];
        LOG_D("xfer       msgs[%d] addr=0x%2x buf=0x%x len= 0x%x flags= 0x%x", i, msg->addr, msg->buf, msg->len, msg->flags);
        next_msg = &msgs[i + 1];
        next_flag = next_msg->flags;

        timeout = msg->len / TRANS_TIMEOUT_PERSEC + 2;
        if (next_flag & RT_I2C_NO_START)
        {
            if ((next_flag & RT_I2C_RD) == (msg->flags & RT_I2C_RD))
            {
                /* The same mode, can use no start */
                mode = I2C_FIRST_AND_NEXT_FRAME;
            }
            else
            {
                /* Not allowed to use no start, sending address is required when changing direction, user setting error */
                LOG_W("user set flags error msg[%d] flags RT_I2C_NO_START has canceled", i + 1);
                mode = I2C_LAST_FRAME_NO_STOP;
            }
        }
        else
        {
            mode = I2C_LAST_FRAME_NO_STOP;
        }

        if (msg->flags & RT_I2C_RD)
        {
            LOG_D("xfer  rec  msgs[%d] i2c mode = %s", i, mode == I2C_FIRST_AND_NEXT_FRAME ? "I2C_FIRST_AND_NEXT_FRAME" : mode == I2C_LAST_FRAME_NO_STOP ? "I2C_FIRST_FRAME/I2C_LAST_FRAME_NO_STOP"
                  : mode == I2C_LAST_FRAME           ? "I2C_LAST_FRAME"
                  : "nuknown mode");
            if ((i2c_obj->i2c_dma_flag & I2C_USING_RX_DMA_FLAG) && (msg->len >= DMA_TRANS_MIN_LEN))
            {
                ret = n32_i2c_master_seq_receive_dma(i2c_obj, (msg->addr << 1), msg->buf, msg->len, mode);
            }
            else
            {
                ret = n32_i2c_master_seq_receive_it(i2c_obj, (msg->addr << 1), msg->buf, msg->len, mode);
            }
            if (ret != RT_EOK)
            {
                LOG_E("[%s:%d]I2C Read error(%d)!\n", __func__, __LINE__, ret);
                goto out;
            }
            if (rt_completion_wait(completion, timeout) != RT_EOK)
            {
                LOG_D("receive time out");
                goto out;

            }
        }
        else
        {
            LOG_D("xfer trans msgs[%d] hal mode = %s", i, mode == I2C_FIRST_AND_NEXT_FRAME ? "I2C_FIRST_AND_NEXT_FRAME" : mode == I2C_LAST_FRAME_NO_STOP ? "I2C_FIRST_FRAME/I2C_LAST_FRAME_NO_STOP"
                  : mode == I2C_LAST_FRAME           ? "I2C_LAST_FRAME"
                  : "nuknown mode");
            if ((i2c_obj->i2c_dma_flag & I2C_USING_TX_DMA_FLAG) && (msg->len >= DMA_TRANS_MIN_LEN))
            {
                ret = n32_i2c_master_seq_send_dma(i2c_obj, (msg->addr << 1), msg->buf, msg->len, mode);
            }
            else
            {
                ret = n32_i2c_master_seq_send_it(i2c_obj, (msg->addr << 1), msg->buf, msg->len, mode);
            }
            if (ret != RT_EOK)
            {
                LOG_D("[%s:%d]I2C Write error(%d)!\n", __func__, __LINE__, ret);
                goto out;
            }
            if (rt_completion_wait(completion, timeout) != RT_EOK)
            {
                LOG_D("transmit time out");
                goto out;
            }
        }
        LOG_D("xfer  next msgs[%d] addr=0x%2x buf= 0x%x len= 0x%x flags = 0x%x\r\n", i + 1, next_msg->addr, next_msg->buf, next_msg->len, next_msg->flags);
    }

    /* last msg */
    msg = &msgs[i];
    timeout = msg->len / TRANS_TIMEOUT_PERSEC + 2;

    if (msg->flags & RT_I2C_NO_STOP)
        mode = I2C_LAST_FRAME_NO_STOP;
    else
        mode = I2C_LAST_FRAME;

    LOG_D("xfer  last msgs[%d] addr=0x%2x buf= 0x%x len= 0x%x flags = 0x%x", i, msg->addr, msg->buf, msg->len, msg->flags);
    if (msg->flags & RT_I2C_RD)
    {
        LOG_D("xfer  rec  msgs[%d] hal mode=%s", i, mode == I2C_FIRST_AND_NEXT_FRAME ? "I2C_FIRST_AND_NEXT_FRAME" : mode == I2C_LAST_FRAME_NO_STOP ? "I2C_FIRST_FRAME/I2C_LAST_FRAME_NO_STOP"
              : mode == I2C_LAST_FRAME           ? "I2C_LAST_FRAME"
              : "nuknown mode");
        if ((i2c_obj->i2c_dma_flag & I2C_USING_RX_DMA_FLAG) && (msg->len >= DMA_TRANS_MIN_LEN))
        {
            ret = n32_i2c_master_seq_receive_dma(i2c_obj, (msg->addr << 1), msg->buf, msg->len, mode);
        }
        else
        {
            uint32_t itflags   = READ_REG(i2c_obj->config->Instance->STSINT);
            ret = n32_i2c_master_seq_receive_it(i2c_obj, (msg->addr << 1), msg->buf, msg->len, mode);
        }
        if (ret != RT_EOK)
        {
            LOG_D("[%s:%d]I2C Read error(%d)!\n", __func__, __LINE__, ret);
            goto out;
        }
        if (rt_completion_wait(completion, timeout) != RT_EOK)
        {
            LOG_D("receive time out");
            goto out;
        }
    }
    else
    {
        LOG_D("xfer trans msgs[%d] hal mode = %s", i, mode == I2C_FIRST_AND_NEXT_FRAME ? "I2C_FIRST_AND_NEXT_FRAME" : mode == I2C_LAST_FRAME       ? "I2C_LAST_FRAME"
              : mode == I2C_LAST_FRAME_NO_STOP ? "I2C_FIRST_FRAME/I2C_LAST_FRAME_NO_STOP"
              : "nuknown mode");
        if ((i2c_obj->i2c_dma_flag & I2C_USING_TX_DMA_FLAG) && (msg->len >= DMA_TRANS_MIN_LEN))
        {
            ret = n32_i2c_master_seq_send_dma(i2c_obj, (msg->addr << 1), msg->buf, msg->len, mode);
        }
        else
        {
            ret = n32_i2c_master_seq_send_it(i2c_obj, (msg->addr << 1), msg->buf, msg->len, mode);
        }
        if (ret != RT_EOK)
        {
            LOG_D("[%s:%d]I2C Write error(%d)!\n", __func__, __LINE__, ret);
            goto out;
        }
        if (rt_completion_wait(completion, timeout) != RT_EOK)
        {
            LOG_D("transmit time out");
            goto out;

        }
    }
    LOG_D("xfer  end  %d mags\r\n", num);
    return num;

out:
    return (i - 1);
}


static const struct rt_i2c_bus_device_ops n32_i2c_ops =
{
    .master_xfer = n32_i2c_master_xfer,
    RT_NULL,
    RT_NULL
};


static void n32_get_dma_info(void)
{
#ifdef BSP_I2C1_RX_USING_DMA
    i2c_objs[I2C1_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C1_dma_rx = I2C1_RX_DMA_CONFIG;
    i2c_config[I2C1_INDEX].dma_rx = &I2C1_dma_rx;
#endif /* BSP_I2C1_RX_USING_DMA */
#ifdef BSP_I2C1_TX_USING_DMA
    i2c_objs[I2C1_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C1_dma_tx = I2C1_TX_DMA_CONFIG;
    i2c_config[I2C1_INDEX].dma_tx = &I2C1_dma_tx;
#endif /* BSP_I2C1_TX_USING_DMA */

#ifdef BSP_I2C2_RX_USING_DMA
    i2c_objs[I2C2_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C2_dma_rx = I2C2_RX_DMA_CONFIG;
    i2c_config[I2C2_INDEX].dma_rx = &I2C2_dma_rx;
#endif /* BSP_I2C2_RX_USING_DMA */
#ifdef BSP_I2C2_TX_USING_DMA
    i2c_objs[I2C2_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C2_dma_tx = I2C2_TX_DMA_CONFIG;
    i2c_config[I2C2_INDEX].dma_tx = &I2C2_dma_tx;
#endif /* BSP_I2C2_TX_USING_DMA */
#ifdef BSP_I2C3_RX_USING_DMA
    i2c_objs[I2C3_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C3_dma_rx = I2C3_RX_DMA_CONFIG;
    i2c_config[I2C3_INDEX].dma_rx = &I2C3_dma_rx;
#endif /* BSP_I2C3_RX_USING_DMA */
#ifdef BSP_I2C3_TX_USING_DMA
    i2c_objs[I2C3_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C3_dma_tx = I2C3_TX_DMA_CONFIG;
    i2c_config[I2C3_INDEX].dma_tx = &I2C3_dma_tx;
#endif /* BSP_I2C3_TX_USING_DMA */
#ifdef BSP_I2C4_RX_USING_DMA
    i2c_objs[I2C4_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C4_dma_rx = I2C4_RX_DMA_CONFIG;
    i2c_config[I2C4_INDEX].dma_rx = &I2C4_dma_rx;
#endif /* BSP_I2C4_RX_USING_DMA */
#ifdef BSP_I2C4_TX_USING_DMA
    i2c_objs[I2C4_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C4_dma_tx = I2C4_TX_DMA_CONFIG;
    i2c_config[I2C4_INDEX].dma_tx = &I2C4_dma_tx;
#endif /* BSP_I2C4_TX_USING_DMA */
#ifdef BSP_I2C5_RX_USING_DMA
    i2c_objs[I2C5_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C5_dma_rx = I2C5_RX_DMA_CONFIG;
    i2c_config[I2C5_INDEX].dma_rx = &I2C5_dma_rx;
#endif /* BSP_I2C5_RX_USING_DMA */
#ifdef BSP_I2C5_TX_USING_DMA
    i2c_objs[I2C5_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C5_dma_tx = I2C5_TX_DMA_CONFIG;
    i2c_config[I2C5_INDEX].dma_tx = &I2C5_dma_tx;
#endif /* BSP_I2C5_TX_USING_DMA */
#ifdef BSP_I2C6_RX_USING_DMA
    i2c_objs[I2C6_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C6_dma_rx = I2C6_RX_DMA_CONFIG;
    i2c_config[I2C6_INDEX].dma_rx = &I2C6_dma_rx;
#endif /* BSP_I2C6_RX_USING_DMA */
#ifdef BSP_I2C6_TX_USING_DMA
    i2c_objs[I2C6_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C6_dma_tx = I2C6_TX_DMA_CONFIG;
    i2c_config[I2C6_INDEX].dma_tx = &I2C6_dma_tx;
#endif /* BSP_I2C6_TX_USING_DMA */
#ifdef BSP_I2C7_RX_USING_DMA
    i2c_objs[I2C7_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C7_dma_rx = I2C7_RX_DMA_CONFIG;
    i2c_config[I2C7_INDEX].dma_rx = &I2C7_dma_rx;
#endif /* BSP_I2C7_RX_USING_DMA */
#ifdef BSP_I2C7_TX_USING_DMA
    i2c_objs[I2C7_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C7_dma_tx = I2C7_TX_DMA_CONFIG;
    i2c_config[I2C7_INDEX].dma_tx = &I2C7_dma_tx;
#endif /* BSP_I2C7_TX_USING_DMA */
#ifdef BSP_I2C8_RX_USING_DMA
    i2c_objs[I2C8_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C8_dma_rx = I2C8_RX_DMA_CONFIG;
    i2c_config[I2C8_INDEX].dma_rx = &I2C8_dma_rx;
#endif /* BSP_I2C8_RX_USING_DMA */
#ifdef BSP_I2C8_TX_USING_DMA
    i2c_objs[I2C8_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C8_dma_tx = I2C8_TX_DMA_CONFIG;
    i2c_config[I2C8_INDEX].dma_tx = &I2C8_dma_tx;
#endif /* BSP_I2C8_TX_USING_DMA */
#ifdef BSP_I2C9_RX_USING_DMA
    i2c_objs[I2C9_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C9_dma_rx = I2C9_RX_DMA_CONFIG;
    i2c_config[I2C9_INDEX].dma_rx = &I2C9_dma_rx;
#endif /* BSP_I2C9_RX_USING_DMA */
#ifdef BSP_I2C9_TX_USING_DMA
    i2c_objs[I2C9_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C9_dma_tx = I2C9_TX_DMA_CONFIG;
    i2c_config[I2C9_INDEX].dma_tx = &I2C9_dma_tx;
#endif /* BSP_I2C9_TX_USING_DMA */
#ifdef BSP_I2C10_RX_USING_DMA
    i2c_objs[I2C10_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C10_dma_rx = I2C10_RX_DMA_CONFIG;
    i2c_config[I2C10_INDEX].dma_rx = &I2C10_dma_rx;
#endif /* BSP_I2C10_RX_USING_DMA */
#ifdef BSP_I2C10_TX_USING_DMA
    i2c_objs[I2C10_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C10_dma_tx = I2C10_TX_DMA_CONFIG;
    i2c_config[I2C10_INDEX].dma_tx = &I2C10_dma_tx;
#endif /* BSP_I2C10_TX_USING_DMA */
}


static void i2c_flush_wdr(I2C_Module *Instance)
{
    /* If a pending WRAVL flag is set, Write a dummy data in WDR to clear it */
    if ((((Instance->STSINT) & I2C_STSINT_WRAVL) == I2C_STSINT_WRAVL) ? SET : RESET)
    {
        Instance->WDR = 0x00U;
    }

    /* Flush WDR register if not empty */
    if ((((Instance->STSINT) & I2C_STSINT_WRE) == I2C_STSINT_WRE) ? SET : RESET)
    {
        Instance->STSINT |= I2C_STSINT_WRE;
    }
}

static void i2c_it_error_handler(struct n32_i2c *drv_i2c, uint32_t itflags)
{
    uint32_t setmask;
    I2C_StateTypeDef tmpstate = drv_i2c->transfer.state;

    drv_i2c->transfer.pBuffPtr = RT_NULL;
    drv_i2c->transfer.XferCount = 0;

    setmask = I2C_CTRL1_TFCIE | I2C_CTRL1_WDRIE | I2C_CTRL1_RDRIE | I2C_CTRL1_STOPIE | I2C_CTRL1_NAKIE | I2C_CTRL1_ERRIE;

    /* Disable all interrupts */
    drv_i2c->config->Instance->CTRL1 &= (~(setmask));

    drv_i2c->transfer.state = I2C_READY;
    drv_i2c->i2c_isr_callback = RT_NULL;

    /* Abort DMA TX transfer */
    if ((tmpstate == I2C_BUSY_TX) && (drv_i2c->i2c_dma_flag & I2C_USING_TX_DMA_FLAG) == I2C_USING_TX_DMA_FLAG)
    {
        if ((drv_i2c->config->Instance->CTRL1 & I2C_CTRL1_DMAWREN) == I2C_CTRL1_DMAWREN)
        {
            drv_i2c->config->Instance->CTRL1 &= ~I2C_CTRL1_DMAWREN;
        }

        DMA_ChannelCmd(drv_i2c->config->dma_tx->Instance, drv_i2c->config->dma_tx->dma_channel, DISABLE);

        DMA_ChannelEventCmd(drv_i2c->config->dma_tx->Instance, drv_i2c->config->dma_tx->dma_channel, DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE, DISABLE);

        DMA_ClearChannelEventStatus(drv_i2c->config->dma_tx->Instance, drv_i2c->config->dma_tx->dma_channel, DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE);
    }

    /* Abort DMA RX transfer */
    if ((tmpstate == I2C_BUSY_RX) && (drv_i2c->i2c_dma_flag & I2C_USING_RX_DMA_FLAG) == I2C_USING_RX_DMA_FLAG)
    {
        if ((drv_i2c->config->Instance->CTRL1 & I2C_CTRL1_DMARDEN) == I2C_CTRL1_DMARDEN)
        {
            drv_i2c->config->Instance->CTRL1 &= ~I2C_CTRL1_DMARDEN;
        }

        DMA_ChannelCmd(drv_i2c->config->dma_rx->Instance, drv_i2c->config->dma_rx->dma_channel, DISABLE);

        DMA_ChannelEventCmd(drv_i2c->config->dma_rx->Instance, drv_i2c->config->dma_rx->dma_channel, DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE, DISABLE);

        DMA_ClearChannelEventStatus(drv_i2c->config->dma_rx->Instance, drv_i2c->config->dma_rx->dma_channel, DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE);
    }

    if (((((itflags & I2C_STSINT_NAKF) == I2C_STSINT_NAKF) ? SET : RESET) != RESET) ||
            ((((itflags & I2C_STSINT_BSER) == I2C_STSINT_BSER) ? SET : RESET) != RESET))
    {
        /* Send stop signal to prevent bus lock-up */
        LOG_D("I2C NACK Error or BUS Error now stoped");
        drv_i2c->config->Instance->CTRL1 |= I2C_CTRL1_STOPIE;
    }
}

static void i2c_it_master_complete(struct n32_i2c *drv_i2c, uint32_t itflags)
{
    uint32_t setmask;
    __IO uint32_t tmpreg;

    /* Clear STOP Flag */
    drv_i2c->config->Instance->INTCLR = I2C_INTCLR_STOPCLR;

    /* I2C Write */
    if (drv_i2c->transfer.state == I2C_BUSY_TX)
    {
        setmask = I2C_CTRL1_TFCIE | I2C_CTRL1_WDRIE | I2C_CTRL1_STOPIE | I2C_CTRL1_NAKIE | I2C_CTRL1_ERRIE;

        /* Disable interrupt */
        drv_i2c->config->Instance->CTRL1 &= (~(setmask));
    }
    /* I2C Read */
    if (drv_i2c->transfer.state == I2C_BUSY_RX)
    {
        setmask = I2C_CTRL1_TFCIE | I2C_CTRL1_RDRIE | I2C_CTRL1_STOPIE | I2C_CTRL1_NAKIE | I2C_CTRL1_ERRIE;

        /* Disable interrupt */
        drv_i2c->config->Instance->CTRL1 &= (~(setmask));
    }

    /* Clear CTRL2 */
    drv_i2c->config->Instance->CTRL2 &= (~(I2C_CTRL2_CLEAR | I2C_CTRL2_HDR10));

    drv_i2c->i2c_isr_callback = RT_NULL;

    if (((((itflags & I2C_STSINT_NAKF) == I2C_STSINT_NAKF) ? SET : RESET) != RESET))
    {
        /* Clear NACK Flag */
        drv_i2c->config->Instance->INTCLR = I2C_INTCLR_NAKCLR;
    }

    /* Fetch Last receive data */
    if (((((itflags & I2C_STSINT_RDAVL) == I2C_STSINT_RDAVL) ? SET : RESET) != RESET))
    {
        /* Read data from RXDR */
        tmpreg = (uint8_t)drv_i2c->config->Instance->RDR;
        RT_UNUSED(tmpreg);
    }

    i2c_flush_wdr(drv_i2c->config->Instance);

    drv_i2c->transfer.state = I2C_READY;
    rt_completion_done(&drv_i2c->completion);
}

static void i2c_it_completion_done(struct n32_i2c *drv_i2c)
{
    uint32_t setmask;

    /* I2C Write */
    if (drv_i2c->transfer.state == I2C_BUSY_TX)
    {
        drv_i2c->transfer.state = I2C_READY;
        drv_i2c->i2c_isr_callback = RT_NULL;

        setmask = I2C_CTRL1_TFCIE | I2C_CTRL1_WDRIE | I2C_CTRL1_STOPIE | I2C_CTRL1_NAKIE | I2C_CTRL1_ERRIE;

        /* Disable interrupt */
        drv_i2c->config->Instance->CTRL1 &= (~(setmask));

        rt_completion_done(&drv_i2c->completion);
    }
    /* I2C Read */
    if (drv_i2c->transfer.state == I2C_BUSY_RX)
    {
        drv_i2c->transfer.state = I2C_READY;
        drv_i2c->i2c_isr_callback = RT_NULL;

        setmask = I2C_CTRL1_TFCIE | I2C_CTRL1_RDRIE | I2C_CTRL1_STOPIE | I2C_CTRL1_NAKIE | I2C_CTRL1_ERRIE;

        /* Disable interrupt */
        drv_i2c->config->Instance->CTRL1 &= (~(setmask));

        rt_completion_done(&drv_i2c->completion);
    }
}

static void i2c_master_ev_isr_handler_it(struct n32_i2c *drv_i2c)
{
    uint16_t devaddress;
    uint32_t setmask;
    /* Get current IT Flags and IT sources value */
    volatile uint32_t itflags   = READ_REG(drv_i2c->config->Instance->STSINT);
    volatile uint32_t itsources = READ_REG(drv_i2c->config->Instance->CTRL1);

    /* It takes more than 100 microseconds to clear the TC flag after starting, so wait for the TC flag to clear */
    if (drv_i2c->transfer.state == I2C_BUSY_RX && first_valid_rx_isr != RT_TRUE)
    {
        if ((itflags & I2C_STSINT_TFC) == I2C_STSINT_TFC)
        {
            return;
        }
        else
        {
            first_valid_rx_isr = RT_TRUE;
        }
    }

    if (((((itflags & I2C_STSINT_NAKF) == I2C_STSINT_NAKF) ? SET : RESET) != RESET) &&
            ((((itsources & I2C_CTRL1_NAKIE) == I2C_CTRL1_NAKIE) ? SET : RESET) != RESET))
    {
        /* Clear Not Acknowledge received flag */
        drv_i2c->config->Instance->INTCLR = I2C_INTCLR_NAKCLR;

        /* Flush WDR register */
        i2c_flush_wdr(drv_i2c->config->Instance);
    }
    else if (((((itflags & I2C_STSINT_RDAVL) == I2C_STSINT_RDAVL) ? SET : RESET) != RESET) &&
             ((((itsources & I2C_CTRL1_RDRIE) == I2C_CTRL1_RDRIE) ? SET : RESET) != RESET))
    {
        /* Remove RDAVL flag as read done */
        itflags &= ~I2C_STSINT_RDAVL;

        /* Read data from RDR */
        *drv_i2c->transfer.pBuffPtr = (uint8_t)drv_i2c->config->Instance->RDR;

        /* Increment Buffer pointer */
        drv_i2c->transfer.pBuffPtr++;

        drv_i2c->transfer.XferSize--;
        drv_i2c->transfer.XferCount--;
    }
    else if (((((itflags & I2C_STSINT_WRAVL) == I2C_STSINT_WRAVL) ? SET : RESET) != RESET) &&
             ((((itsources & I2C_CTRL1_WDRIE) == I2C_CTRL1_WDRIE) ? SET : RESET) != RESET))
    {
        /* Write data to WDR */
        drv_i2c->config->Instance->WDR = *drv_i2c->transfer.pBuffPtr;

        /* Increment Buffer pointer */
        drv_i2c->transfer.pBuffPtr++;

        drv_i2c->transfer.XferSize--;
        drv_i2c->transfer.XferCount--;
    }
    else if (((((itflags & I2C_STSINT_TFCR) == I2C_STSINT_TFCR) ? SET : RESET) != RESET) &&
             ((((itsources & I2C_CTRL1_TFCIE) == I2C_CTRL1_TFCIE) ? SET : RESET) != RESET))
    {
        if ((drv_i2c->transfer.XferCount != 0U) && (drv_i2c->transfer.XferSize == 0U))
        {
            devaddress = (uint16_t)(drv_i2c->config->Instance->CTRL2 & I2C_CTRL2_SADR);

            if (drv_i2c->transfer.XferCount > MAX_NBYTE_SIZE)
            {
                drv_i2c->transfer.XferSize = MAX_NBYTE_SIZE;

                /* Slave address | Transfer direction | START generation | STOP generation | Number of bytes | NBYTES reload mode | Automatic end mode */
                setmask = ((uint32_t)devaddress & I2C_CTRL2_SADR) | (uint32_t)I2C_NO_STARTSTOP | (((uint32_t)drv_i2c->transfer.XferSize << I2C_CTRL2_NBYTES_POS) & I2C_CTRL2_BYTECNT) | (uint32_t)I2C_RELOAD_MODE;

                /* Set IIC CTRL2 Register */
                MODIFY_REG(drv_i2c->config->Instance->CTRL2, I2C_CTRL2_CLEAR, (uint32_t)setmask);
            }
            else
            {
                drv_i2c->transfer.XferSize = drv_i2c->transfer.XferCount;

                /* Slave address | Transfer direction | START generation | STOP generation | Number of bytes | NBYTES reload mode | Automatic end mode */
                setmask = ((uint32_t)devaddress & I2C_CTRL2_SADR) | (uint32_t)I2C_NO_STARTSTOP | (((uint32_t)drv_i2c->transfer.XferSize << I2C_CTRL2_NBYTES_POS) & I2C_CTRL2_BYTECNT) | (uint32_t)drv_i2c->transfer.XferOptions;

                /* Set IIC CTRL2 Register */
                MODIFY_REG(drv_i2c->config->Instance->CTRL2, I2C_CTRL2_CLEAR, (uint32_t)setmask);
            }
        }
        else
        {
            if (((drv_i2c->config->Instance->CTRL2 & I2C_AUTOEND_MODE) != I2C_AUTOEND_MODE))
            {
                i2c_it_completion_done(drv_i2c);
            }
            else
            {
                i2c_it_error_handler(drv_i2c, itflags);
            }
        }
    }
    else if (((((itflags & I2C_STSINT_TFC) == I2C_STSINT_TFC) ? SET : RESET) != RESET) &&
             ((((itsources & I2C_CTRL1_TFCIE) == I2C_CTRL1_TFCIE) ? SET : RESET) != RESET))
    {
        if (drv_i2c->transfer.XferCount == 0U)
        {
            if (((drv_i2c->config->Instance->CTRL2 & I2C_AUTOEND_MODE) != I2C_AUTOEND_MODE))
            {
                i2c_it_completion_done(drv_i2c);
            }
        }
        else
        {
            i2c_it_error_handler(drv_i2c, itflags);
        }
    }
    else
    {
        /* Nothing to do */
    }

    if (((((itflags & I2C_STSINT_STOPF) == I2C_STSINT_STOPF) ? SET : RESET) != RESET) &&
            ((((itsources & I2C_CTRL1_STOPIE) == I2C_CTRL1_STOPIE) ? SET : RESET) != RESET))
    {
        i2c_it_master_complete(drv_i2c, itflags);
    }
}

static void i2c_master_ev_isr_handler_dma(struct n32_i2c *drv_i2c)
{
    uint16_t devaddress;
    uint32_t setmask;
    uint32_t xfermode;
    /* Get current IT Flags and IT sources value */
    volatile uint32_t itflags   = READ_REG(drv_i2c->config->Instance->STSINT);
    volatile uint32_t itsources = READ_REG(drv_i2c->config->Instance->CTRL1);

    if (((((itflags & I2C_STSINT_NAKF) == I2C_STSINT_NAKF) ? SET : RESET) != RESET) &&
            ((((itsources & I2C_CTRL1_NAKIE) == I2C_CTRL1_NAKIE) ? SET : RESET) != RESET))
    {
        /* Clear Not Acknowledge received flag */
        drv_i2c->config->Instance->INTCLR = I2C_INTCLR_NAKCLR;

        setmask = I2C_CTRL1_TFCIE | I2C_CTRL1_STOPIE;

        /* Enable STOP interrupts */
        drv_i2c->config->Instance->CTRL1 |= setmask;

        /* Flush WDR register */
        i2c_flush_wdr(drv_i2c->config->Instance);
    }
    else if (((((itflags & I2C_STSINT_TFCR) == I2C_STSINT_TFCR) ? SET : RESET) != RESET) &&
             ((((itsources & I2C_CTRL1_TFCIE) == I2C_CTRL1_TFCIE) ? SET : RESET) != RESET))
    {
        /* Disable TC interrupt */
        drv_i2c->config->Instance->CTRL1 &= ~I2C_CTRL1_TFCIE;

        if (drv_i2c->transfer.XferCount != 0U)
        {
            devaddress = (uint16_t)(drv_i2c->config->Instance->CTRL2 & I2C_CTRL2_SADR);

            /* Prepare the new XferSize to transfer */
            if (drv_i2c->transfer.XferCount > MAX_NBYTE_SIZE)
            {
                drv_i2c->transfer.XferSize = MAX_NBYTE_SIZE;
                xfermode = I2C_RELOAD_MODE;
            }
            else
            {
                drv_i2c->transfer.XferSize = drv_i2c->transfer.XferCount;
                xfermode = drv_i2c->transfer.XferOptions;
            }

            /* Slave address | Transfer direction | START generation | STOP generation | Number of bytes | NBYTES reload mode | Automatic end mode */
            setmask = ((uint32_t)devaddress & I2C_CTRL2_SADR) | (uint32_t)I2C_NO_STARTSTOP | (((uint32_t)drv_i2c->transfer.XferSize << I2C_CTRL2_NBYTES_POS) & I2C_CTRL2_BYTECNT) | (uint32_t)xfermode;

            /* Set IIC CTRL2 Register */
            MODIFY_REG(drv_i2c->config->Instance->CTRL2, I2C_CTRL2_CLEAR, (uint32_t)setmask);

            /* Update XferCount value */
            drv_i2c->transfer.XferCount -= drv_i2c->transfer.XferSize;

            /* Enable DMA Request */
            if (drv_i2c->transfer.state == I2C_BUSY_TX)
            {
                drv_i2c->config->Instance->CTRL1 |= I2C_CTRL1_DMAWREN;
            }
            if (drv_i2c->transfer.state == I2C_BUSY_RX)
            {
                drv_i2c->config->Instance->CTRL1 |= I2C_CTRL1_DMARDEN;
            }
        }
        else
        {
            if (((drv_i2c->config->Instance->CTRL2 & I2C_AUTOEND_MODE) != I2C_AUTOEND_MODE))
            {
                i2c_it_completion_done(drv_i2c);
            }
            else
            {
                i2c_it_error_handler(drv_i2c, itflags);
            }
        }
    }
    else if (((((itflags & I2C_STSINT_TFC) == I2C_STSINT_TFC) ? SET : RESET) != RESET) &&
             ((((itsources & I2C_CTRL1_TFCIE) == I2C_CTRL1_TFCIE) ? SET : RESET) != RESET))
    {
        if (drv_i2c->transfer.XferCount == 0U)
        {
            if (((drv_i2c->config->Instance->CTRL2 & I2C_AUTOEND_MODE) != I2C_AUTOEND_MODE))
            {
                i2c_it_completion_done(drv_i2c);
            }
        }
        else
        {
            i2c_it_error_handler(drv_i2c, itflags);
        }
    }
    else if (((((itflags & I2C_STSINT_STOPF) == I2C_STSINT_STOPF) ? SET : RESET) != RESET) &&
             ((((itsources & I2C_CTRL1_STOPIE) == I2C_CTRL1_STOPIE) ? SET : RESET) != RESET))
    {
        i2c_it_master_complete(drv_i2c, itflags);
    }
    else
    {
        /* Nothing to do */
    }
}

static void i2c_master_er_isr_handler(struct n32_i2c *drv_i2c)
{
    uint32_t tmperror = 0;
    volatile uint32_t itflags   = READ_REG(drv_i2c->config->Instance->STSINT);
    volatile uint32_t itsources = READ_REG(drv_i2c->config->Instance->CTRL1);

    /* I2C Bus error interrupt occurred */
    if (((((itflags & I2C_STSINT_BSER) == I2C_STSINT_BSER) ? SET : RESET) != RESET) &&
            ((((itsources & I2C_CTRL1_ERRIE) == I2C_CTRL1_ERRIE) ? SET : RESET) != RESET))
    {
        tmperror |= I2C_STSINT_BSER;

        drv_i2c->config->Instance->INTCLR = I2C_INTCLR_BSERCLR;
    }

    /* I2C Over-Run/Under-Run interrupt occurred */
    if (((((itflags & I2C_STSINT_OVF) == I2C_STSINT_OVF) ? SET : RESET) != RESET) &&
            ((((itsources & I2C_CTRL1_ERRIE) == I2C_CTRL1_ERRIE) ? SET : RESET) != RESET))
    {
        tmperror |= I2C_STSINT_OVF;

        drv_i2c->config->Instance->INTCLR = I2C_INTCLR_OVFCLR;
    }

    /* I2C Arbitration Loss error interrupt occurred */
    if (((((itflags & I2C_STSINT_ABLO) == I2C_STSINT_ABLO) ? SET : RESET) != RESET) &&
            ((((itsources & I2C_CTRL1_ERRIE) == I2C_CTRL1_ERRIE) ? SET : RESET) != RESET))
    {
        tmperror |= I2C_STSINT_ABLO;

        drv_i2c->config->Instance->INTCLR = I2C_INTCLR_ABLOCLR;
    }

    /* I2C PEC error interrupt occurred */
    if (((((itflags & I2C_STSINT_CRCERR) == I2C_STSINT_CRCERR) ? SET : RESET) != RESET) &&
            ((((itsources & I2C_CTRL1_ERRIE) == I2C_CTRL1_ERRIE) ? SET : RESET) != RESET))
    {
        tmperror |= I2C_STSINT_CRCERR;

        drv_i2c->config->Instance->INTCLR = I2C_INTCLR_CRCCLR;
    }

    /* I2C PEC error interrupt occurred */
    if (((((itflags & I2C_STSINT_TMOUT) == I2C_STSINT_TMOUT) ? SET : RESET) != RESET) &&
            ((((itsources & I2C_CTRL1_ERRIE) == I2C_CTRL1_ERRIE) ? SET : RESET) != RESET))
    {
        tmperror |= I2C_STSINT_TMOUT;

        drv_i2c->config->Instance->INTCLR = I2C_INTCLR_TMOUTCLR;
    }

    if ((tmperror & (I2C_STSINT_BSER | I2C_STSINT_OVF | I2C_STSINT_ABLO | I2C_STSINT_CRCERR | I2C_STSINT_TMOUT)) != 0)
    {
        i2c_it_error_handler(drv_i2c, itflags);
    }
}

static void i2c_master_ev_isr_handler(struct n32_i2c *drv_i2c)
{
    if (drv_i2c->i2c_isr_callback != RT_NULL)
    {
        drv_i2c->i2c_isr_callback(drv_i2c);
    }
}


#if defined(BSP_I2C1_RX_USING_DMA) || defined(BSP_I2C2_RX_USING_DMA) || defined(BSP_I2C3_RX_USING_DMA) || defined(BSP_I2C4_RX_USING_DMA) || defined(BSP_I2C5_RX_USING_DMA) || \
    defined(BSP_I2C6_RX_USING_DMA) || defined(BSP_I2C7_RX_USING_DMA) || defined(BSP_I2C8_RX_USING_DMA) || defined(BSP_I2C9_RX_USING_DMA) || defined(BSP_I2C10_RX_USING_DMA)
static void i2c_master_dma_receive_isr_handler(struct n32_i2c *drv_i2c)
{
#if defined(SOC_SERIES_N32H7xx)
    if (DMA_GetCombinedStatus(drv_i2c->config->dma_rx->Instance))
    {
        if (DMA_GetChannelIntBlockStatus(drv_i2c->config->dma_rx->Instance, drv_i2c->config->dma_rx->dma_channel) == SET)
        {
            /* Disable DMA Request */
            drv_i2c->config->Instance->CTRL1 &= (~I2C_CTRL1_DMARDEN);

            /* If last transfer, enable STOP interrupt */
            if (drv_i2c->transfer.XferCount == 0U)
            {
                /* Enable interrupt */
                drv_i2c->config->Instance->CTRL1 |= (I2C_CTRL1_TFCIE | I2C_CTRL1_STOPIE);
            }
            /* else prepare a new DMA transfer and enable TCReload interrupt */
            else
            {
                /* Update Buffer pointer */
                drv_i2c->transfer.pBuffPtr += drv_i2c->transfer.XferSize;

                /* Set the XferSize to transfer */
                if (drv_i2c->transfer.XferCount > MAX_NBYTE_SIZE)
                {
                    drv_i2c->transfer.XferSize = MAX_NBYTE_SIZE;
                }
                else
                {
                    drv_i2c->transfer.XferSize = drv_i2c->transfer.XferCount;
                }

                n32_iic_transfer_by_dma(drv_i2c->config, drv_i2c->transfer.pBuffPtr, drv_i2c->transfer.XferSize, RT_TRUE);

                /* Enable TC interrupts */
                drv_i2c->config->Instance->CTRL1 |= I2C_CTRL1_TFCIE;
            }

            /* Clear interrupt event status */
            DMA_ClearChannelEventStatus(drv_i2c->config->dma_rx->Instance, drv_i2c->config->dma_rx->dma_channel, DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE);
        }
    }
#endif
}
#endif

#if defined(BSP_I2C1_TX_USING_DMA) || defined(BSP_I2C2_TX_USING_DMA) || defined(BSP_I2C3_TX_USING_DMA) || defined(BSP_I2C4_TX_USING_DMA) || defined(BSP_I2C5_TX_USING_DMA) || \
    defined(BSP_I2C6_TX_USING_DMA) || defined(BSP_I2C7_TX_USING_DMA) || defined(BSP_I2C8_TX_USING_DMA) || defined(BSP_I2C9_TX_USING_DMA) || defined(BSP_I2C10_TX_USING_DMA)
static void i2c_master_dma_send_isr_handler(struct n32_i2c *drv_i2c)
{
#if defined(SOC_SERIES_N32H7xx)
    if (DMA_GetCombinedStatus(drv_i2c->config->dma_tx->Instance))
    {
        if (DMA_GetChannelIntBlockStatus(drv_i2c->config->dma_tx->Instance, drv_i2c->config->dma_tx->dma_channel) == SET)
        {
            /* Disable DMA Request */
            drv_i2c->config->Instance->CTRL1 &= (~I2C_CTRL1_DMAWREN);

            /* If last transfer, enable STOP interrupt */
            if (drv_i2c->transfer.XferCount == 0U)
            {
                /* Enable interrupt */
                drv_i2c->config->Instance->CTRL1 |= (I2C_CTRL1_TFCIE | I2C_CTRL1_STOPIE);
            }
            /* else prepare a new DMA transfer and enable TCReload interrupt */
            else
            {
                /* Update Buffer pointer */
                drv_i2c->transfer.pBuffPtr += drv_i2c->transfer.XferSize;

                /* Set the XferSize to transfer */
                if (drv_i2c->transfer.XferCount > MAX_NBYTE_SIZE)
                {
                    drv_i2c->transfer.XferSize = MAX_NBYTE_SIZE;
                }
                else
                {
                    drv_i2c->transfer.XferSize = drv_i2c->transfer.XferCount;
                }

                n32_iic_transfer_by_dma(drv_i2c->config, drv_i2c->transfer.pBuffPtr, drv_i2c->transfer.XferSize, RT_TRUE);

                /* Enable TC interrupts */
                drv_i2c->config->Instance->CTRL1 |= I2C_CTRL1_TFCIE;
            }

            /* Clear interrupt event status */
            DMA_ClearChannelEventStatus(drv_i2c->config->dma_tx->Instance, drv_i2c->config->dma_tx->dma_channel, DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE);
        }
    }
#endif
}
#endif

#ifdef BSP_USING_HARD_I2C1
/**
 * @brief This function handles I2C2 event interrupt.
 */
void I2C1_EV_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_master_ev_isr_handler(&i2c_objs[I2C1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
/**
 * @brief This function handles I2C2 error interrupt.
 */
void I2C1_ER_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_master_er_isr_handler(&i2c_objs[I2C1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(BSP_I2C1_RX_USING_DMA) && defined(I2C1_RX_DMA_IRQHandler)
void I2C1_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_master_dma_receive_isr_handler(&i2c_objs[I2C1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_I2C1_RX_USING_DMA) && defined(I2C1_RX_DMA_IRQHandler) */

#if defined(BSP_I2C1_TX_USING_DMA) && defined(I2C1_TX_DMA_IRQHandler)
void I2C1_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    i2c_master_dma_send_isr_handler(&i2c_objs[I2C1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_I2C1_TX_USING_DMA) && defined(I2C1_TX_DMA_IRQHandler) */
#endif /* BSP_USING_HARD_I2C1 */


int rt_hw_hw_i2c_init(void)
{
    int ret = -RT_ERROR;
    rt_size_t obj_num = sizeof(i2c_objs) / sizeof(i2c_objs[0]);

    n32_get_dma_info();

    for (int i = 0; i < obj_num; i++)
    {
        i2c_objs[i].i2c_bus.ops = &n32_i2c_ops;
        i2c_objs[i].transfer.state = I2C_RESET;
        i2c_objs[i].config = &i2c_config[i];
        i2c_objs[i].i2c_bus.timeout = i2c_config[i].timeout;

        rt_completion_init(&i2c_objs[i].completion);
        n32_i2c_configure(&i2c_objs[i].i2c_bus);
        ret = rt_i2c_bus_device_register(&i2c_objs[i].i2c_bus, i2c_objs[i].config->name);
        RT_ASSERT(ret == RT_EOK);
        LOG_D("%s bus init done", i2c_config[i].name);
    }
    return ret;
}
INIT_CORE_EXPORT(rt_hw_hw_i2c_init);

#endif
