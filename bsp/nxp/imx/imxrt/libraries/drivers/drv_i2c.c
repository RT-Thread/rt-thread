/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang         the first version
 * 2018-03-24     LaiYiKeTang  add hardware iic
 * 2019-04-22     tyustli      add imxrt series support
 * 2026-08-13     Ran          add RT1180 CM33 DMA support
 *
 */

#include <rtthread.h>

#ifdef BSP_USING_I2C

#define LOG_TAG "drv.i2c"
#include <drv_log.h>

#include <rtdevice.h>
#include "fsl_lpi2c.h"
#ifdef SOC_IMXRT1180_SERIES
#include "fsl_lpi2c_edma.h"
#endif
#include "drv_i2c.h"

#ifdef SOC_IMXRT1180_SERIES
struct i2c_dma_config
{
    lpi2c_master_edma_handle_t i2c_edma;

    edma_handle_t rx_edma;
    dma_request_source_t rx_request;
    rt_uint8_t rx_channel;

    edma_handle_t tx_edma;
    dma_request_source_t tx_request;
    rt_uint8_t tx_channel;

    EDMA_Type *edma_base;
    volatile status_t last_status; /* completion status from DMA callback */

    /* rx_offset: number of leading bytes to skip in the RX bounce buffer.
     * DMA3 (AON domain, LPI2C1/2): EDMA reads one spurious 0x00 beat from
     * MRDR before real data arrives, so rx_offset = 1.
     * DMA4 (WAKEUP domain, LPI2C3/6): no spurious beat, rx_offset = 0. */
    rt_uint8_t rx_offset;
};
#endif /* SOC_IMXRT1180_SERIES */

struct imxrt_i2c_bus
{
    struct rt_i2c_bus_device parent;
    LPI2C_Type *I2C;
    struct rt_i2c_msg *msg;
    rt_uint32_t msg_cnt;
    volatile rt_uint32_t msg_ptr;
    volatile rt_uint32_t dptr;
    char *device_name;
#if defined(SOC_IMXRT1170_SERIES) || defined(SOC_IMXRT1180_SERIES)
    clock_root_t clock_root;
#endif
#ifdef SOC_IMXRT1180_SERIES
    struct i2c_dma_config *dma;
    rt_uint8_t dma_flag;
    rt_sem_t xfer_sem;
#endif
};

#if defined(BSP_USING_I2C1)
#define I2C1BUS_NAME "i2c1"
#endif /*BSP_USING_I2C1*/

#if defined(BSP_USING_I2C2)
#define I2C2BUS_NAME "i2c2"
#endif /*BSP_USING_I2C2*/

#if !defined(MIMXRT1015_SERIES)      /* imxrt1015 only have two i2c bus*/

#if defined(BSP_USING_I2C3)
#define I2C3BUS_NAME "i2c3"
#endif /*BSP_USING_I2C3*/

#if defined(BSP_USING_I2C4)
#define I2C4BUS_NAME "i2c4"
#endif /*BSP_USING_I2C4*/

#if defined(BSP_USING_I2C5)
#define I2C5BUS_NAME "i2c5"
#endif /*BSP_USING_I2C5*/

#if defined(BSP_USING_I2C6)
#define I2C6BUS_NAME "i2c6"
#endif /*BSP_USING_I2C6*/

#endif /* MIMXRT1015_SERIES */

/* Select USB1 PLL (360 MHz) as master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_SELECT (1U)
#ifdef SOC_IMXRT1170_SERIES
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (12U)
#else
#define LPI2C_CLOCK_SOURCE_DIVIDER (0U)

/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY      ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1U))

#endif
#ifdef BSP_USING_I2C1
static struct imxrt_i2c_bus lpi2c1 = {
    .I2C = LPI2C1,
    .device_name = I2C1BUS_NAME,
#ifdef SOC_IMXRT1180_SERIES
    .dma = RT_NULL,
    .dma_flag = RT_FALSE,
#endif
};
#endif /* RT_USING_HW_I2C1 */

#ifdef BSP_USING_I2C2
static struct imxrt_i2c_bus lpi2c2 = {
    .I2C = LPI2C2,
    .device_name = I2C2BUS_NAME,
#ifdef SOC_IMXRT1180_SERIES
    .dma = RT_NULL,
    .dma_flag = RT_FALSE,
#endif
};
#endif /* RT_USING_HW_I2C2 */

#if !defined(MIMXRT1015_SERIES)        /* imxrt1015 only have two i2c bus*/

#ifdef BSP_USING_I2C3
static struct imxrt_i2c_bus lpi2c3 = {
    .I2C = LPI2C3,
    .device_name = I2C3BUS_NAME,
#ifdef SOC_IMXRT1180_SERIES
    .dma = RT_NULL,
    .dma_flag = RT_FALSE,
#endif
};
#endif /* RT_USING_HW_I2C3 */

#ifdef BSP_USING_I2C4
static struct imxrt_i2c_bus lpi2c4 = {
    .I2C = LPI2C4,
    .device_name = I2C4BUS_NAME,
#ifdef SOC_IMXRT1180_SERIES
    .dma = RT_NULL,
    .dma_flag = RT_FALSE,
#endif
};
#endif /* RT_USING_HW_I2C4 */

#ifdef BSP_USING_I2C5
static struct imxrt_i2c_bus lpi2c5 = {
    .I2C = LPI2C5,
    .device_name = I2C5BUS_NAME,
#ifdef SOC_IMXRT1180_SERIES
    .dma = RT_NULL,
    .dma_flag = RT_FALSE,
#endif
};
#endif /* RT_USING_HW_I2C5 */

#ifdef BSP_USING_I2C6
static struct imxrt_i2c_bus lpi2c6 = {
    .I2C = LPI2C6,
    .device_name = I2C6BUS_NAME,
#ifdef SOC_IMXRT1180_SERIES
    .dma = RT_NULL,
    .dma_flag = RT_FALSE,
#endif
};
#endif /* RT_USING_HW_I2C6 */

#endif /* MIMXRT1015_SERIES */

/* --- RT1180 DMA config instances ---
 * i2c_dma_config contains lpi2c_master_edma_handle_t which embeds edma_tcd_t[]
 * that the DMA engine accesses directly. Place in non-cacheable memory to prevent
 * cache coherency issues. */
#ifdef SOC_IMXRT1180_SERIES

#ifdef BSP_I2C1_USING_DMA
static AT_NONCACHEABLE_SECTION_ALIGN_INIT(struct i2c_dma_config i2c1_dma, 32) = {
    .rx_request = kDma3RequestMuxLPI2C1Rx,
    .rx_channel = BSP_I2C1_RX_DMA_CHANNEL,
    .tx_request = kDma3RequestMuxLPI2C1Tx,
    .tx_channel = BSP_I2C1_TX_DMA_CHANNEL,
    .edma_base = (EDMA_Type *)DMA3,
    .rx_offset = 1U, /* DMA3: one spurious 0x00 beat before real data */
};
#endif

#ifdef BSP_I2C2_USING_DMA
static AT_NONCACHEABLE_SECTION_ALIGN_INIT(struct i2c_dma_config i2c2_dma, 32) = {
    .rx_request = kDma3RequestMuxLPI2C2Rx,
    .rx_channel = BSP_I2C2_RX_DMA_CHANNEL,
    .tx_request = kDma3RequestMuxLPI2C2Tx,
    .tx_channel = BSP_I2C2_TX_DMA_CHANNEL,
    .edma_base = (EDMA_Type *)DMA3,
    .rx_offset = 1U, /* DMA3: one spurious 0x00 beat before real data */
};
#endif

#ifdef BSP_I2C3_USING_DMA
static AT_NONCACHEABLE_SECTION_ALIGN_INIT(struct i2c_dma_config i2c3_dma, 32) = {
    .rx_request = kDma4RequestMuxLPI2C3Rx,
    .rx_channel = BSP_I2C3_RX_DMA_CHANNEL,
    .tx_request = kDma4RequestMuxLPI2C3Tx,
    .tx_channel = BSP_I2C3_TX_DMA_CHANNEL,
    .edma_base = (EDMA_Type *)DMA4,
    .rx_offset = 0U, /* DMA4: no spurious beat, real data at bounce[0] */
};
#endif

#ifdef BSP_I2C6_USING_DMA
static AT_NONCACHEABLE_SECTION_ALIGN_INIT(struct i2c_dma_config i2c6_dma, 32) = {
    .rx_request = kDma4RequestMuxLPI2C6Rx,
    .rx_channel = BSP_I2C6_RX_DMA_CHANNEL,
    .tx_request = kDma4RequestMuxLPI2C6Tx,
    .tx_channel = BSP_I2C6_TX_DMA_CHANNEL,
    .edma_base = (EDMA_Type *)DMA4,
    .rx_offset = 0U, /* DMA4: no spurious beat, real data at bounce[0] */
};
#endif

static void i2c_get_dma_config(void)
{
#ifdef BSP_I2C1_USING_DMA
    lpi2c1.dma = &i2c1_dma;
    lpi2c1.dma_flag = RT_TRUE;
#endif
#ifdef BSP_I2C2_USING_DMA
    lpi2c2.dma = &i2c2_dma;
    lpi2c2.dma_flag = RT_TRUE;
#endif
#ifdef BSP_I2C3_USING_DMA
    lpi2c3.dma = &i2c3_dma;
    lpi2c3.dma_flag = RT_TRUE;
#endif
#ifdef BSP_I2C6_USING_DMA
    lpi2c6.dma = &i2c6_dma;
    lpi2c6.dma_flag = RT_TRUE;
#endif
}

#if (defined(BSP_USING_I2C1) || defined(BSP_USING_I2C2) || defined(BSP_USING_I2C3) || defined(BSP_USING_I2C4) || defined(BSP_USING_I2C5) || defined(BSP_USING_I2C6))

/* RT1180 EDMA4 RX bounce buffer.
 *
 * Observed behavior on RT1180 LPI2C + EDMA4:
 *   The EDMA reads one spurious 0x00 byte from the (not-yet-ready) MRDR before
 *   the first real data byte arrives. After that, data bytes land consecutively:
 *     bounce[0]   = 0x00  (spurious MRDR read before data is ready)
 *     bounce[1]   = I2C data byte 0
 *     bounce[2]   = I2C data byte 1
 *     ...
 *     bounce[N]   = I2C data byte N-1
 *   To capture all N data bytes the DMA must perform N+1 beats minimum.
 *   Setting xfer.dataSize = 2*N is safe (drives 2N beats, easily covers N+1).
 *   After DMA completes, de-interleave: result[j] = bounce[j + 1].
 *
 * Size: 512 bytes supports up to 255 I2C bytes per transfer ((512/2)-1).
 *
 * TX bounce buffer:
 *   DMA3 cannot access DTCM (stack/heap). The caller's TX buffer may be on the
 *   stack. memcpy it into this SRAM buffer before starting the EDMA TX so the
 *   DMA engine can always read from DMA-accessible SRAM.
 */
#define I2C_DMA_BOUNCE_SIZE 512U
static rt_uint8_t i2c_dma_bounce[I2C_DMA_BOUNCE_SIZE];     /* RX bounce buffer */
static rt_uint8_t i2c_dma_tx_bounce[I2C_DMA_BOUNCE_SIZE];  /* TX bounce buffer */

static void lpi2c_edma_callback(LPI2C_Type *base, lpi2c_master_edma_handle_t *handle,
                                status_t completionStatus, void *userData)
{
    struct imxrt_i2c_bus *i2c = (struct imxrt_i2c_bus *)userData;
    rt_sem_release(i2c->xfer_sem);
}

static void lpi2c_dma_config(struct imxrt_i2c_bus *bus)
{
    EDMA_Type *edma_base = bus->dma->edma_base;

    EDMA_SetChannelMux(edma_base, bus->dma->rx_channel, bus->dma->rx_request);
    EDMA_CreateHandle(&bus->dma->rx_edma, edma_base, bus->dma->rx_channel);

    EDMA_SetChannelMux(edma_base, bus->dma->tx_channel, bus->dma->tx_request);
    EDMA_CreateHandle(&bus->dma->tx_edma, edma_base, bus->dma->tx_channel);

    LPI2C_MasterCreateEDMAHandle(bus->I2C,
                                 &bus->dma->i2c_edma,
                                 &bus->dma->rx_edma,
                                 &bus->dma->tx_edma,
                                 lpi2c_edma_callback,
                                 bus);

    LOG_D("%s dma config done", bus->device_name);
}

#endif /* BSP_USING_I2Cx - bounce buffers and lpi2c_dma_config */
#endif /* SOC_IMXRT1180_SERIES */

#if (defined(BSP_USING_I2C1) || defined(BSP_USING_I2C2) || defined(BSP_USING_I2C3) || defined(BSP_USING_I2C4) || defined(BSP_USING_I2C5) || defined(BSP_USING_I2C6))

static rt_ssize_t imxrt_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                     struct rt_i2c_msg msgs[],
                                     rt_uint32_t num);
static rt_ssize_t imxrt_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                     struct rt_i2c_msg msgs[],
                                     rt_uint32_t num);
static rt_err_t imxrt_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                      int cmd,
                                      void *args);

static const struct rt_i2c_bus_device_ops imxrt_i2c_ops = {
    .master_xfer = imxrt_i2c_mst_xfer,
    .slave_xfer = imxrt_i2c_slv_xfer,
    .i2c_bus_control = imxrt_i2c_bus_control,
};

static rt_err_t imxrt_lpi2c_configure(struct imxrt_i2c_bus *bus, lpi2c_master_config_t *cfg)
{
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    bus->parent.ops = &imxrt_i2c_ops;
#ifdef SOC_IMXRT1170_SERIES
    clock_root_config_t rootCfg = { 0 };
    rootCfg.mux = LPI2C_CLOCK_SOURCE_SELECT;
    rootCfg.div = LPI2C_CLOCK_SOURCE_DIVIDER + 1;
    CLOCK_SetRootClock(bus->clock_root, &rootCfg);
    volatile uint32_t freq = CLOCK_GetRootClockFreq(bus->clock_root);
    LPI2C_MasterInit(bus->I2C, cfg, freq);
#elif defined(SOC_IMXRT1180_SERIES)
    volatile uint32_t freq = CLOCK_GetRootClockFreq(bus->clock_root);
    LPI2C_MasterInit(bus->I2C, cfg, freq);
#else
    CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);
    LPI2C_MasterInit(bus->I2C, cfg, LPI2C_CLOCK_FREQUENCY);
#endif

    return RT_EOK;
}

status_t LPI2C_MasterCheck(LPI2C_Type *base, uint32_t status)
{
    status_t result = kStatus_Success;

    /* Check for error. These errors cause a stop to automatically be sent. We must */
    /* clear the errors before a new transfer can start. */
    status &= 0x3c00;
    if (status)
    {
        /* Select the correct error code. Ordered by severity, with bus issues first. */
        if (status & kLPI2C_MasterPinLowTimeoutFlag)
        {
            result = kStatus_LPI2C_PinLowTimeout;
        }
        else if (status & kLPI2C_MasterArbitrationLostFlag)
        {
            result = kStatus_LPI2C_ArbitrationLost;
        }
        else if (status & kLPI2C_MasterNackDetectFlag)
        {
            result = kStatus_LPI2C_Nak;
        }
        else if (status & kLPI2C_MasterFifoErrFlag)
        {
            result = kStatus_LPI2C_FifoError;
        }
        else
        {
            assert(false);
        }

        /* Clear the flags. */
        LPI2C_MasterClearStatusFlags(base, status);

        /* Reset fifos. These flags clear automatically. */
        base->MCR |= LPI2C_MCR_RRF_MASK | LPI2C_MCR_RTF_MASK;
    }

    return result;
}

/* LPI2C_MasterWaitForTxFifoAllEmpty is only used in the non-RT1180 legacy
 * transfer path. Guard it so the compiler does not warn about an unused
 * static function when building for RT1180. */
#ifndef SOC_IMXRT1180_SERIES
/*!
 * @brief Wait until the tx fifo all empty.
 * @param base The LPI2C peripheral base address.
 * @retval #kStatus_Success
 * @retval #kStatus_LPI2C_PinLowTimeout
 * @retval #kStatus_LPI2C_ArbitrationLost
 * @retval #kStatus_LPI2C_Nak
 * @retval #kStatus_LPI2C_FifoError
 */
static status_t LPI2C_MasterWaitForTxFifoAllEmpty(LPI2C_Type *base)
{
    uint32_t status;
    size_t txCount;

    do
    {
        status_t result;

        /* Get the number of words in the tx fifo and compute empty slots. */
        LPI2C_MasterGetFifoCounts(base, NULL, &txCount);

        /* Check for error flags. */
        status = LPI2C_MasterGetStatusFlags(base);
        result = LPI2C_MasterCheck(base, status);
        if (result)
        {
            return result;
        }
    }

    while (txCount);

    return kStatus_Success;
}
#endif /* !SOC_IMXRT1180_SERIES */

#ifdef SOC_IMXRT1180_SERIES
static rt_ssize_t imxrt_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                     struct rt_i2c_msg msgs[],
                                     rt_uint32_t num)
{
    struct imxrt_i2c_bus *imxrt_i2c;
    rt_size_t i;
    status_t status;
    RT_ASSERT(bus != RT_NULL);
    imxrt_i2c = (struct imxrt_i2c_bus *)bus;

    imxrt_i2c->msg = msgs;
    imxrt_i2c->msg_ptr = 0;
    imxrt_i2c->msg_cnt = num;
    imxrt_i2c->dptr = 0;

#ifdef BSP_USING_DMA
    if (imxrt_i2c->dma_flag == RT_TRUE)
    {
        /* DMA path: use the SDK non-blocking EDMA transfer API.
         * Each rt_i2c_msg maps to one lpi2c_master_transfer_t.
         *
         * Restrictions:
         * - DMA cannot handle zero-length data (EDMA never fires a completion
         *   interrupt, and NACK detection is unreliable). Fall back to blocking
         *   for zero-length probe transfers.
         * - The caller's buffer may be in cacheable memory (e.g. stack).
         *   Clean the D-cache before a TX DMA so the DMA sees current data.
         *   Invalidate the D-cache after an RX DMA so the CPU sees DMA data. */
        for (i = 0; i < num; i++)
        {
            lpi2c_master_transfer_t xfer;
            rt_memset(&xfer, 0, sizeof(xfer));

            xfer.slaveAddress = msgs[i].addr;
            xfer.data = msgs[i].buf;
            xfer.dataSize = msgs[i].len;
            xfer.direction = (msgs[i].flags & RT_I2C_RD) ? kLPI2C_Read : kLPI2C_Write;

            if (msgs[i].flags & RT_I2C_NO_START)
            {
                xfer.flags = kLPI2C_TransferNoStartFlag;
            }
            else if (i + 1 < num)
            {
                xfer.flags = kLPI2C_TransferNoStopFlag;
            }
            else
            {
                xfer.flags = kLPI2C_TransferDefaultFlag;
            }

            /* Short or zero-length transfers: use blocking.
             * Zero-length: EDMA never fires completion, NACK not detected.
             * Short (<4 bytes): overhead is negligible; use blocking. */
            if (xfer.dataSize < 4U)
            {
                status = LPI2C_MasterTransferBlocking(imxrt_i2c->I2C, &xfer);
                if (status != kStatus_Success)
                {
                    i = 0;
                    break;
                }
                continue;
            }

            /* RT1180 EDMA4 DMA-accessible buffer workaround:
             *
             * TX: DMA3 cannot read from DTCM (stack/heap). Copy the caller's TX
             *     data into the SRAM TX bounce buffer before starting the EDMA.
             *
             * RX: EDMA4 prepends one spurious 0x00 beat before real data arrives.
             *     Redirect into a 2x RX bounce buffer; de-interleave after DMA. */
            if (xfer.direction == kLPI2C_Write)
            {
                if (xfer.dataSize > I2C_DMA_BOUNCE_SIZE)
                {
                    /* TX data too large for bounce; fall back to blocking. */
                    status = LPI2C_MasterTransferBlocking(imxrt_i2c->I2C, &xfer);
                    if (status != kStatus_Success)
                    {
                        i = 0;
                        break;
                    }
                    continue;
                }
                rt_memcpy(i2c_dma_tx_bounce, xfer.data, xfer.dataSize);
                xfer.data = i2c_dma_tx_bounce;
            }

            if (xfer.direction == kLPI2C_Read)
            {
                /* DMA3 (LPI2C1/2): one spurious 0x00 beat precedes real data,
                 * so request orig_len + 1 beats to capture all N real bytes.
                 * DMA4 (LPI2C3/6): no spurious beat, request orig_len beats. */
                rt_size_t orig_len = xfer.dataSize;
                rt_uint8_t rx_off = imxrt_i2c->dma->rx_offset;
                rt_size_t bounce_len = orig_len + (rt_size_t)rx_off;
                if (bounce_len > I2C_DMA_BOUNCE_SIZE)
                {
                    /* Bounce buffer too small; fall back to blocking. */
                    status = LPI2C_MasterTransferBlocking(imxrt_i2c->I2C, &xfer);
                    if (status != kStatus_Success)
                    {
                        i = 0;
                        break;
                    }
                    continue;
                }
                rt_memset(i2c_dma_bounce, 0, bounce_len);
                xfer.data = i2c_dma_bounce;
                xfer.dataSize = bounce_len;
                (void)orig_len; /* used after DMA completes below */
            }

            status = LPI2C_MasterTransferEDMA(imxrt_i2c->I2C,
                                              &imxrt_i2c->dma->i2c_edma,
                                              &xfer);
            if (status != kStatus_Success)
            {
                i = 0;
                break;
            }
            if (rt_sem_take(imxrt_i2c->xfer_sem, rt_tick_from_millisecond(1000)) != RT_EOK)
            {
                LPI2C_MasterTransferAbortEDMA(imxrt_i2c->I2C, &imxrt_i2c->dma->i2c_edma);
                i = 0;
                break;
            }
            /* Wait for the LPI2C master to finish driving the STOP condition.
             * The EDMA callback fires when the last DMA beat completes, but the
             * LPI2C peripheral may still be clocking out the STOP condition.
             * Poll the StopDetect flag (set when STOP is seen on bus, cleared by writing 1)
             * then also wait for BusBusy to clear so SCL/SDA are released. */
            {
                uint32_t deadline = 100000U;
                /* Wait for stop detect or timeout. */
                while (!(LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterStopDetectFlag) && (deadline > 0U))
                {
                    deadline--;
                }
                /* Clear the stop detect flag. */
                LPI2C_MasterClearStatusFlags(imxrt_i2c->I2C, kLPI2C_MasterStopDetectFlag);
                /* Also wait for bus to go idle. */
                deadline = 10000U;
                while ((LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterBusBusyFlag) && (deadline > 0U))
                {
                    deadline--;
                }
                /* Flush RX and TX FIFOs to discard any residual bytes left after DMA.
                 * Without this, a stale byte in the RX FIFO is returned by the next
                 * blocking read instead of a fresh byte from the bus. */
                imxrt_i2c->I2C->MCR |= LPI2C_MCR_RRF_MASK | LPI2C_MCR_RTF_MASK;
            }

            /* Copy bounce into caller buffer for RX.
             * DMA3 (LPI2C1/2): real data starts at bounce[1] (skip spurious byte).
             * DMA4 (LPI2C3/6): real data starts at bounce[0] (no spurious byte). */
            if ((msgs[i].flags & RT_I2C_RD) && (msgs[i].len >= 4U))
            {
                rt_size_t j;
                rt_uint8_t rx_off = imxrt_i2c->dma->rx_offset;
                for (j = 0; j < msgs[i].len; j++)
                {
                    msgs[i].buf[j] = i2c_dma_bounce[j + (rt_size_t)rx_off];
                }
            }
        }
    }
    else
#endif /* BSP_USING_DMA */
    {
        /* Non-DMA (polling) path.
         * Use LPI2C_MasterTransferBlocking which handles the complete state machine
         * (START, address, ACK/NACK, data, repeated-START, STOP) correctly. */
        for (i = 0; i < num; i++)
        {
            lpi2c_master_transfer_t xfer;
            rt_memset(&xfer, 0, sizeof(xfer));

            xfer.slaveAddress = msgs[i].addr;
            xfer.data = msgs[i].buf;
            xfer.dataSize = msgs[i].len;
            xfer.direction = (msgs[i].flags & RT_I2C_RD) ? kLPI2C_Read : kLPI2C_Write;

            if (msgs[i].flags & RT_I2C_NO_START)
            {
                /* Continue an in-progress transaction: no START, no STOP. */
                xfer.flags = kLPI2C_TransferNoStartFlag;
            }
            else if (i + 1 < num)
            {
                /* More messages follow: hold the bus (no STOP) so the next
                 * message issues a repeated START. */
                xfer.flags = kLPI2C_TransferNoStopFlag;
            }
            else
            {
                /* Last (or only) message: send a STOP to release the bus. */
                xfer.flags = kLPI2C_TransferDefaultFlag;
            }

            status = LPI2C_MasterTransferBlocking(imxrt_i2c->I2C, &xfer);
            if (status != kStatus_Success)
            {
                i = 0;
                break;
            }
        }
    }

    imxrt_i2c->msg = RT_NULL;
    imxrt_i2c->msg_ptr = 0;
    imxrt_i2c->msg_cnt = 0;
    imxrt_i2c->dptr = 0;

    return i;
}
#else
static rt_ssize_t imxrt_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                     struct rt_i2c_msg msgs[],
                                     rt_uint32_t num)
{
    struct imxrt_i2c_bus *imxrt_i2c;
    rt_size_t i;
    RT_ASSERT(bus != RT_NULL);
    imxrt_i2c = (struct imxrt_i2c_bus *)bus;

    imxrt_i2c->msg = msgs;
    imxrt_i2c->msg_ptr = 0;
    imxrt_i2c->msg_cnt = num;
    imxrt_i2c->dptr = 0;

    for (i = 0; i < num; i++)
    {
        if (imxrt_i2c->msg[i].flags & RT_I2C_RD)
        {
            if ((imxrt_i2c->msg[i].flags & RT_I2C_NO_START) != RT_I2C_NO_START)
            {
                if (LPI2C_MasterStart(imxrt_i2c->I2C, imxrt_i2c->msg[i].addr, kLPI2C_Write) != kStatus_Success)
                {
                    i = 0;
                    break;
                }

                while (LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterNackDetectFlag)
                {
                }

                if (LPI2C_MasterRepeatedStart(imxrt_i2c->I2C, imxrt_i2c->msg[i].addr, kLPI2C_Read) != kStatus_Success)
                {
                    i = 0;
                    break;
                }
            }
            else
            {
                if (LPI2C_MasterStart(imxrt_i2c->I2C, imxrt_i2c->msg[i].addr, kLPI2C_Read) != kStatus_Success)
                {
                    i = 0;
                    break;
                }

                while (LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterNackDetectFlag)
                {
                }
            }

            if (LPI2C_MasterStart(imxrt_i2c->I2C, imxrt_i2c->msg[i].addr, kLPI2C_Read) != kStatus_Success)
            {
                i = 0;
                break;
            }

            while (LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterNackDetectFlag)
            {
            }

            if (LPI2C_MasterReceive(imxrt_i2c->I2C, imxrt_i2c->msg[i].buf, imxrt_i2c->msg[i].len) != kStatus_Success)
            {
                i = 0;
                break;
            }
        }
        else
        {
            if (LPI2C_MasterStart(imxrt_i2c->I2C, imxrt_i2c->msg[i].addr, kLPI2C_Write) != kStatus_Success)
            {
                i = 0;
                break;
            }

            // while((LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterBusBusyFlag))
            // {
            // }
            if (LPI2C_MasterWaitForTxFifoAllEmpty(imxrt_i2c->I2C) != kStatus_Success)
            {
                i = 0;
                break;
            }

            if (LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterNackDetectFlag)
            {
                i = 0;
                break;
            }

            if (LPI2C_MasterSend(imxrt_i2c->I2C, imxrt_i2c->msg[i].buf, imxrt_i2c->msg[i].len) != kStatus_Success)
            {
                i = 0;
                break;
            }

            if (LPI2C_MasterWaitForTxFifoAllEmpty(imxrt_i2c->I2C) != kStatus_Success)
            {
                i = 0;
                break;
            }
        }

        if (LPI2C_MasterStop(imxrt_i2c->I2C) != kStatus_Success)
        {
            i = 0;
        }
    }

    imxrt_i2c->msg = RT_NULL;
    imxrt_i2c->msg_ptr = 0;
    imxrt_i2c->msg_cnt = 0;
    imxrt_i2c->dptr = 0;

    return i;
}
#endif

static rt_ssize_t imxrt_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                     struct rt_i2c_msg msgs[],
                                     rt_uint32_t num)
{
    return 0;
}
static rt_err_t imxrt_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                      int cmd,
                                      void *args)
{
    return -RT_ERROR;
}

#endif

int rt_hw_i2c_init(void)
{
#if (defined(BSP_USING_I2C1) || defined(BSP_USING_I2C2) || defined(BSP_USING_I2C3) || defined(BSP_USING_I2C4) || defined(BSP_USING_I2C5) || defined(BSP_USING_I2C6))
    lpi2c_master_config_t masterConfig = { 0 };
#endif

#ifdef SOC_IMXRT1180_SERIES
    i2c_get_dma_config();
#endif

#if defined(BSP_USING_I2C1)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if defined(HW_I2C1_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C1_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /*HW_I2C1_BADURATE_400kHZ*/
#if defined(SOC_IMXRT1170_SERIES)
    lpi2c1.clock_root = kCLOCK_Root_Lpi2c1;
#elif defined(SOC_IMXRT1180_SERIES)
    lpi2c1.clock_root = kCLOCK_Root_Lpi2c0102;
#endif
    imxrt_lpi2c_configure(&lpi2c1, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c1.parent, lpi2c1.device_name);
#ifdef SOC_IMXRT1180_SERIES
    lpi2c1.xfer_sem = rt_sem_create("i2c1_s", 0, RT_IPC_FLAG_PRIO);
    if (lpi2c1.dma_flag == RT_TRUE)
    {
        lpi2c_dma_config(&lpi2c1);
    }
#endif
#endif  /* BSP_USING_I2C1 */

#if defined(BSP_USING_I2C2)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if defined(HW_I2C2_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C2_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /* HW_I2C2_BADURATE_400kHZ */
#if defined(SOC_IMXRT1170_SERIES)
    lpi2c2.clock_root = kCLOCK_Root_Lpi2c2;
#elif defined(SOC_IMXRT1180_SERIES)
    lpi2c2.clock_root = kCLOCK_Root_Lpi2c0102;
#endif
    imxrt_lpi2c_configure(&lpi2c2, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c2.parent, lpi2c2.device_name);
#ifdef SOC_IMXRT1180_SERIES
    lpi2c2.xfer_sem = rt_sem_create("i2c2_s", 0, RT_IPC_FLAG_PRIO);
    if (lpi2c2.dma_flag == RT_TRUE)
    {
        lpi2c_dma_config(&lpi2c2);
    }
#endif
#endif  /* BSP_USING_I2C2 */

#if !defined(MIMXRT1015_SERIES) /* imxrt1015 only have two i2c bus*/

#if defined(BSP_USING_I2C3)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if defined(HW_I2C3_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C3_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /* HW_I2C3_BADURATE_400kHZ */
#if defined(SOC_IMXRT1170_SERIES)
    lpi2c3.clock_root = kCLOCK_Root_Lpi2c3;
#elif defined(SOC_IMXRT1180_SERIES)
    lpi2c3.clock_root = kCLOCK_Root_Lpi2c0304;
#endif
    imxrt_lpi2c_configure(&lpi2c3, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c3.parent, lpi2c3.device_name);
#ifdef SOC_IMXRT1180_SERIES
    lpi2c3.xfer_sem = rt_sem_create("i2c3_s", 0, RT_IPC_FLAG_PRIO);
    if (lpi2c3.dma_flag == RT_TRUE)
    {
        lpi2c_dma_config(&lpi2c3);
    }
#endif
#endif  /* BSP_USING_I2C3 */

#if defined(BSP_USING_I2C4)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if defined(HW_I2C4_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C4_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /* HW_I2C4_BADURATE_400kHZ */
#if defined(SOC_IMXRT1170_SERIES)
    lpi2c4.clock_root = kCLOCK_Root_Lpi2c4;
#elif defined(SOC_IMXRT1180_SERIES)
    lpi2c4.clock_root = kCLOCK_Root_Lpi2c0304;
#endif
    imxrt_lpi2c_configure(&lpi2c4, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c4.parent, lpi2c4.device_name);
#ifdef SOC_IMXRT1180_SERIES
    lpi2c4.xfer_sem = rt_sem_create("i2c4_s", 0, RT_IPC_FLAG_PRIO);
#endif
#endif /* BSP_USING_I2C4 */

#if defined(BSP_USING_I2C5)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if defined(HW_I2C5_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C5_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /* HW_I2C5_BADURATE_400kHZ */
#if defined(SOC_IMXRT1170_SERIES)
    lpi2c5.clock_root = kCLOCK_Root_Lpi2c5;
#elif defined(SOC_IMXRT1180_SERIES)
    lpi2c5.clock_root = kCLOCK_Root_Lpi2c0506;
#endif
    imxrt_lpi2c_configure(&lpi2c5, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c5.parent, lpi2c5.device_name);
#ifdef SOC_IMXRT1180_SERIES
    lpi2c5.xfer_sem = rt_sem_create("i2c5_s", 0, RT_IPC_FLAG_PRIO);
#endif
#endif /* BSP_USING_I2C5 */

#if defined(BSP_USING_I2C6)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if defined(HW_I2C6_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C6_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /* HW_I2C6_BADURATE_400kHZ */
#if defined(SOC_IMXRT1170_SERIES)
    lpi2c6.clock_root = kCLOCK_Root_Lpi2c6;
#elif defined(SOC_IMXRT1180_SERIES)
    lpi2c6.clock_root = kCLOCK_Root_Lpi2c0506;
#endif
    imxrt_lpi2c_configure(&lpi2c6, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c6.parent, lpi2c6.device_name);
#ifdef SOC_IMXRT1180_SERIES
    lpi2c6.xfer_sem = rt_sem_create("i2c6_s", 0, RT_IPC_FLAG_PRIO);
    if (lpi2c6.dma_flag == RT_TRUE)
    {
        lpi2c_dma_config(&lpi2c6);
    }
#endif
#endif /* BSP_USING_I2C6 */


#endif /* MIMXRT1015_SERIES */

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* BSP_USING_I2C */
