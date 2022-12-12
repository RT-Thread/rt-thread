/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"

#ifdef HAL_DWDMA_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup DWDMA
 *  @{
 */

/** @defgroup DWDMA_How_To_Use How To Use
 *  @{

 The DWDMA driver can be used as follows:

 - Invoke HAL_DWDMA_Init() to initialize dma.
 - Invoke HAL_DWDMA_RequestChannel() to request a available dma channel.
 - Invoke HAL_DWDMA_Config() to config dma transfer config.
 - Invoke HAL_DWDMA_PrepDmaSingle()/HAL_DWDMA_PrepDmaCyclic() for single/cyclic transfer.
 - Invoke HAL_DWDMA_Start() to start a ready dma transfer.
 - Invoke HAL_DWDMA_Stop() to stop the dma channel.
 - Invoke HAL_DWDMA_ReleaseChannel() to release the dma channel.
 - Invoke HAL_DWDMA_DeInit() to deinitialize dma.
 - More details refer to APIs' descriptions as below.

 @} */

/** @defgroup DWDMA_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/

#define DW_CHAN_SET_BIT(reg, mask) \
    WRITE_REG(reg, ((mask) << 8) | (mask))
#define DW_CHAN_CLEAR_BIT(reg, mask) \
    WRITE_REG(reg, ((mask) << 8) | 0)

#define DWC_DEFAULT_CTLLO(_dwc) ({                                  \
        struct DMA_SLAVE_CONFIG *_config = &(_dwc)->config;         \
        bool _islave = HAL_DMA_IsSlaveDirection((_dwc)->direction); \
        uint8_t _smSize = _islave ? _config->srcMaxBurst :          \
            DWDMA_MSIZE_256;                                        \
        uint8_t _dmSize = _islave ? _config->dstMaxBurst :          \
            DWDMA_MSIZE_256;                                        \
                                                                    \
        (DWC_CTLL_DST_MSIZE(_dmSize)                                \
         | DWC_CTLL_SRC_MSIZE(_smSize)                              \
         | DWC_CTLL_LLP_D_EN                                        \
         | DWC_CTLL_LLP_S_EN                                        \
         | DWC_CTLL_DMS((_dwc)->dstMaster)                          \
         | DWC_CTLL_SMS((_dwc)->srcMaster));                        \
    })

/********************* Private Structure Definition **************************/

/********************* Private Variable Definition ***************************/

/********************* Private Function Definition ***************************/

__STATIC_INLINE void DWC_DumpRegs(struct DWDMA_CHAN *dwc)
{
    HAL_DBG("SAR: 0x%08lx DAR: 0x%08lx LLP: 0x%08lx CTL: 0x%08lx:%08lx\n",
            READ_REG(dwc->creg->SAR), READ_REG(dwc->creg->DAR),
            READ_REG(dwc->creg->LLP), READ_REG(dwc->creg->CTL_HI),
            READ_REG(dwc->creg->CTL_LO));
}

/**
 * Fix config's burst len to bit.
 */
__STATIC_INLINE void DW_ConvertBurst(uint16_t *maxburst)
{
    uint32_t val;

    switch (*maxburst) {
    case 1:
        val = 0;
        break;
    case 4:
        val = 1;
        break;
    case 8:
        val = 2;
        break;
    case 16:
        val = 3;
        break;
    case 32:
        val = 4;
        break;
    case 64:
        val = 5;
        break;
    case 128:
        val = 6;
        break;
    case 256:
        val = 7;
        break;
    default:
        val = 0;
        break;
    }

    *maxburst = val;
}

/**
 * Get burst len from bit.
 * refer to MSIZE of register CTLx[13:11].
 */
__STATIC_INLINE uint32_t DW_GetBurstLength(uint32_t val)
{
    uint32_t len = 1;

    if (val >= 1 && val <= 7) {
        len = 1 << (val + 1);
    }

    return len;
}

__STATIC_INLINE uint32_t DW_FFS(uint32_t word)
{
#ifdef __GNUC__
    HAL_ASSERT(word);

    return (__builtin_ffs(word) - 1);
#else
    int num = 0;

    HAL_ASSERT(word);
    if ((word & 0xffff) == 0) {
        num += 16;
        word >>= 16;
    }
    if ((word & 0xff) == 0) {
        num += 8;
        word >>= 8;
    }
    if ((word & 0xf) == 0) {
        num += 4;
        word >>= 4;
    }
    if ((word & 0x3) == 0) {
        num += 2;
        word >>= 2;
    }
    if ((word & 0x1) == 0) {
        num += 1;
    }

    return num;
#endif
}

static void DWDMA_off(struct HAL_DWDMA_DEV *dw)
{
    struct DMA_REG *reg = dw->pReg;

    WRITE_REG(reg->DMACFGREG, 0);

    DW_CHAN_CLEAR_BIT(reg->MASK.TFR, dw->allChanMask);
    DW_CHAN_CLEAR_BIT(reg->MASK.BLOCK, dw->allChanMask);
    DW_CHAN_CLEAR_BIT(reg->MASK.SRCTRAN, dw->allChanMask);
    DW_CHAN_CLEAR_BIT(reg->MASK.DSTTRAN, dw->allChanMask);
    DW_CHAN_CLEAR_BIT(reg->MASK.ERR, dw->allChanMask);

    while (READ_REG(reg->DMACFGREG) & DW_CFG_DMA_EN) {
        ;
    }
}

static void DWDMA_on(struct HAL_DWDMA_DEV *dw)
{
    struct DMA_REG *reg = dw->pReg;

    WRITE_REG(reg->DMACFGREG, DW_CFG_DMA_EN);
}

static void DWC_initialize(struct DWDMA_CHAN *dwc)
{
    struct HAL_DWDMA_DEV *dw = dwc->dw;
    uint32_t cfghi = DWC_CFGH_FIFO_MODE;
    uint32_t cfglo = 0;

    switch (dwc->direction) {
    case DMA_MEM_TO_DEV:
        cfglo |= dwc->cyclic ? DWC_CFGL_RELOAD_DAR : 0;
        cfghi |= DWC_CFGH_DST_PER(dwc->periId);
        break;
    case DMA_DEV_TO_MEM:
        cfglo |= dwc->cyclic ? DWC_CFGL_RELOAD_SAR : 0;
        cfghi |= DWC_CFGH_SRC_PER(dwc->periId);
        break;
    default:
        break;
    }

    WRITE_REG(dwc->creg->CFG_LO, cfglo);
    WRITE_REG(dwc->creg->CFG_HI, cfghi);

    /* Enable interrupts */
    DW_CHAN_SET_BIT(dw->pReg->MASK.TFR, dwc->mask);
    DW_CHAN_SET_BIT(dw->pReg->MASK.ERR, dwc->mask);
    if (dwc->cyclic) {
        DW_CHAN_SET_BIT(dw->pReg->MASK.BLOCK, dwc->mask);
    }
}

static void DWC_deinitialize(struct DWDMA_CHAN *dwc)
{
    struct HAL_DWDMA_DEV *dw = dwc->dw;

    /* Disable interrupts */
    DW_CHAN_CLEAR_BIT(dw->pReg->MASK.TFR, dwc->mask);
    DW_CHAN_CLEAR_BIT(dw->pReg->MASK.ERR, dwc->mask);
    DW_CHAN_CLEAR_BIT(dw->pReg->MASK.BLOCK, dwc->mask);

    /* Clear interrupts. */
    WRITE_REG(dw->pReg->CLEAR.TFR, dwc->mask);
    WRITE_REG(dw->pReg->CLEAR.SRCTRAN, dwc->mask);
    WRITE_REG(dw->pReg->CLEAR.DSTTRAN, dwc->mask);
    WRITE_REG(dw->pReg->CLEAR.ERR, dwc->mask);
    WRITE_REG(dw->pReg->CLEAR.BLOCK, dwc->mask);
}

static void DWC_HandleCyclic(struct HAL_DWDMA_DEV *dw, struct DWDMA_CHAN *dwc,
                             uint32_t statusBlock, uint32_t statusErr, uint32_t statusXfer)
{
    if (statusBlock & dwc->mask) {
        if (!dwc->paused) {
            WRITE_REG(dw->pReg->CLEAR.BLOCK, dwc->mask);
        }
    }

    /* TODO: execption handler */
    HAL_ASSERT(!statusErr && !statusXfer);

    if (!dwc->paused) {
        DW_CHAN_SET_BIT(dw->pReg->MASK.BLOCK, dwc->mask);
    }
}

static void DWC_HandleError(struct HAL_DWDMA_DEV *dw, struct DWDMA_CHAN *dwc)
{
    HAL_DBG("%s: %d\n", __func__, __LINE__);

    /* TODO: error handler */
    DWC_DumpRegs(dwc);
    WRITE_REG(dw->pReg->CLEAR.ERR, dwc->mask);
}

static void DWC_HandleXfer(struct HAL_DWDMA_DEV *dw, struct DWDMA_CHAN *dwc)
{
    HAL_DBG("%s: %d\n", __func__, __LINE__);

    WRITE_REG(dw->pReg->CLEAR.TFR, dwc->mask);
}

/** @} */
/********************* Public Function Definition ****************************/

/** @defgroup DWDMA_Exported_Functions_Group2 State and Errors Functions

 This section provides functions allowing to get the status of the module:

 *  @{
 */

/** @} */

/** @defgroup DWDMA_Exported_Functions_Group4 Init and DeInit Functions

 This section provides functions allowing to init and deinit the module:

 *  @{
 */

/**
 * @brief DW DMA Get Raw Block Status
 *
 * @param dw: the handle of dw dma.
 *
 * @return raw block status
 */
uint32_t HAL_DWDMA_GetRawBlockStatus(struct HAL_DWDMA_DEV *dw)
{
    return READ_REG(dw->pReg->RAW.BLOCK);
}

/**
 * @brief DW DMA Get Raw Err Status
 *
 * @param dw: the handle of dw dma.
 *
 * @return raw err status
 */
uint32_t HAL_DWDMA_GetRawErrStatus(struct HAL_DWDMA_DEV *dw)
{
    return READ_REG(dw->pReg->RAW.ERR);
}

/**
 * @brief DW DMA Get Raw Xfer Status
 *
 * @param dw: the handle of dw dma.
 *
 * @return raw xfer status
 */
uint32_t HAL_DWDMA_GetRawXferStatus(struct HAL_DWDMA_DEV *dw)
{
    return READ_REG(dw->pReg->RAW.TFR);
}

/**
 * @brief Initializes a specific dw dma.
 *
 * @param dw: the handle of dw dma.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_DWDMA_Init(struct HAL_DWDMA_DEV *dw)
{
    int i;
    struct DMA_REG *reg = dw->pReg;
    struct DWDMA_CHAN *dwc;

    HAL_ASSERT(dw);

#ifdef HAL_DWDMA_BLOCK_ALIGN_SZ
    HAL_ASSERT(HAL_DWDMA_BLOCK_ALIGN_SZ);
    dw->blockSize &= ~(HAL_DWDMA_BLOCK_ALIGN_SZ - 1);
#endif
    /* Calculate all channel mask before DMA setup */
    dw->allChanMask = (1 << dw->maxChans) - 1;
    /* Force dma off, just in case */
    DWDMA_off(dw);

    for (i = 0; i < dw->maxChans; i++) {
        dwc = &dw->chan[i];

        dwc->dw = dw;
        dwc->creg = &(dw->pReg->CHAN[i]);
        dwc->mask = 1 << i;
        /* clear bit */
        DW_CHAN_CLEAR_BIT(reg->CHENREG, dwc->mask);

        dwc->direction = DMA_TRANS_NONE;
    }

    /* Clear all interrupts on all channels. */
    WRITE_REG(reg->CLEAR.TFR, dw->allChanMask);
    WRITE_REG(reg->CLEAR.BLOCK, dw->allChanMask);
    WRITE_REG(reg->CLEAR.SRCTRAN, dw->allChanMask);
    WRITE_REG(reg->CLEAR.DSTTRAN, dw->allChanMask);
    WRITE_REG(reg->CLEAR.ERR, dw->allChanMask);

    return HAL_OK;
}

/**
 * @brief DeInitializes a specific dw dma.
 *
 * @param dw: the handle of dw dma.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_DWDMA_DeInit(struct HAL_DWDMA_DEV *dw)
{
    HAL_ASSERT(dw);

    DWDMA_off(dw);

    DW_CHAN_CLEAR_BIT(dw->pReg->CHENREG, dw->allChanMask);

    return HAL_OK;
}

/** @} */

/** @defgroup DWDMA_Exported_Functions_Group3 IO Functions

 This section provides functions allowing to IO controlling:

 *  @{
 */

/**
 * @brief Pause the dma chan.
 *
 * @param dwc: the handle of dma chan.
 *
 * @return
 *        - HAL_OK on success
 *        - HAL_ERROR on other failures
 */
HAL_Status HAL_DWDMA_Pause(struct DWDMA_CHAN *dwc)
{
    dwc->paused = true;

    return HAL_OK;
}

/**
 * @brief Resume the dma chan.
 *
 * @param dwc: the handle of dma chan.
 *
 * @return
 *        - HAL_OK on success
 *        - HAL_ERROR on other failures
 */
HAL_Status HAL_DWDMA_Resume(struct DWDMA_CHAN *dwc)
{
    if (!dwc->paused) {
        return HAL_OK;
    }

    dwc->paused = false;

    WRITE_REG(dwc->dw->pReg->CLEAR.BLOCK, dwc->mask);
    DW_CHAN_SET_BIT(dwc->dw->pReg->MASK.BLOCK, dwc->mask);

    return HAL_OK;
}

/**
 * @brief Start to run the dma chan.
 *
 * @param dwc: the handle of dma chan.
 *
 * @return
 *        - HAL_OK on success
 *        - HAL_BUSY if chan is busy
 *        - HAL_ERROR on other failures
 */
HAL_Status HAL_DWDMA_Start(struct DWDMA_CHAN *dwc)
{
    struct HAL_DWDMA_DEV *dw;
    struct DMA_REG *reg;
    struct DW_DESC *desc = &dwc->desc[0];
    uint32_t ctllo = desc->lli.ctllo;

    HAL_ASSERT(dwc);

    dw = dwc->dw;
    reg = dw->pReg;

    if (READ_REG(reg->CHENREG) & dwc->mask) {
        HAL_DBG("%s: chan is not idle\n", __func__);
        DWC_DumpRegs(dwc);

        return HAL_ERROR;
    }

    DWC_initialize(dwc);

    desc = &dwc->desc[0];
    WRITE_REG(dwc->creg->LLP, (uint32_t)desc);

    ctllo = desc->lli.ctllo;
    switch (dwc->direction) {
    case DMA_MEM_TO_DEV:
        ctllo |= DWC_CTLL_LLP_S_EN;
        break;
    case DMA_DEV_TO_MEM:
        ctllo |= DWC_CTLL_LLP_D_EN;
        break;
    case DMA_MEM_TO_MEM:
        ctllo |= DWC_CTLL_LLP_D_EN | DWC_CTLL_LLP_S_EN;
        break;
    default:
        break;
    }

    WRITE_REG(dwc->creg->CTL_LO, ctllo);
    WRITE_REG(dwc->creg->CTL_HI, 0);

    DW_CHAN_SET_BIT(dw->pReg->CHENREG, dwc->mask);

    return HAL_OK;
}

/**
 * @brief Stop the dma chan.
 *
 * @param dwc: the handle of dma chan.
 *
 * @return
 *        - HAL_OK on success
 *        - HAL_BUSY if dma is busy
 *        - HAL_ERROR on other failures
 */
HAL_Status HAL_DWDMA_Stop(struct DWDMA_CHAN *dwc)
{
    struct HAL_DWDMA_DEV *dw;

    HAL_ASSERT(dwc);

    dw = dwc->dw;

    DW_CHAN_CLEAR_BIT(dw->pReg->CHENREG, dwc->mask);
    while (READ_REG(dw->pReg->CHENREG) & dwc->mask) {
        ;
    }

    DWC_deinitialize(dwc);

    return HAL_OK;
}

/**
 * @brief Handle dma chan
 *
 * @param dw: the handle of dw dma.
 * @param chanId: the chan num.
 *
 * @return raw irq status
 */
uint32_t HAL_DWDMA_HandleChan(struct HAL_DWDMA_DEV *dw, uint32_t chanId)
{
    struct DWDMA_CHAN *dwc = &dw->chan[chanId];
    uint32_t statusBlock;
    uint32_t statusXfer;
    uint32_t statusErr;

    statusBlock = READ_REG(dw->pReg->RAW.BLOCK);
    statusXfer = READ_REG(dw->pReg->RAW.TFR);
    statusErr = READ_REG(dw->pReg->RAW.ERR);

    if (dwc->cyclic) {
        DWC_HandleCyclic(dw, dwc, statusBlock, statusXfer, statusXfer);
    } else if (statusErr & dwc->mask) {
        DWC_HandleError(dw, dwc);
    } else if (statusXfer & dwc->mask) {
        DWC_HandleXfer(dw, dwc);
    }

    return (statusBlock & dwc->mask) | (statusXfer & dwc->mask);
}

/**
 * @brief dw dma IrqHandler
 *
 * @param dw: the handle of dw dma.
 * @param chanId: the chan num.
 *
 * @return raw irq status
 */
uint32_t HAL_DWDMA_IrqHandler(struct HAL_DWDMA_DEV *dw, uint32_t chanId)
{
    struct DWDMA_CHAN *dwc = &dw->chan[chanId];
    uint32_t status = 0;

    DW_CHAN_CLEAR_BIT(dw->pReg->MASK.TFR, dwc->mask);
    DW_CHAN_CLEAR_BIT(dw->pReg->MASK.BLOCK, dwc->mask);
    DW_CHAN_CLEAR_BIT(dw->pReg->MASK.ERR, dwc->mask);

    status = HAL_DWDMA_HandleChan(dw, chanId);

    /* Re-enable interrupts */
    DW_CHAN_SET_BIT(dw->pReg->MASK.TFR, dwc->mask);
    DW_CHAN_SET_BIT(dw->pReg->MASK.ERR, dwc->mask);

    return status;
}

/**
 * @brief Get the dma channel
 *
 * @param dw: the handle of dw dma.
 * @param chanId: the chan id.
 *
 * @return the dma channel by chan id or NULL on error.
 */
struct DWDMA_CHAN *HAL_DWDMA_GetChannel(struct HAL_DWDMA_DEV *dw, uint32_t chanId)
{
    HAL_ASSERT(dw);

    if (chanId > dw->maxChans) {
        return NULL;
    }

    return &dw->chan[chanId];
}

/**
 * @brief Request a dma channel
 *
 * @param dw: the handle of dw dma.
 * @param id: the peri id.
 *
 * @return a idle dma channel.
 * @note must hold lock.
 */
struct DWDMA_CHAN *HAL_DWDMA_RequestChannel(struct HAL_DWDMA_DEV *dw, DMA_REQ_Type id)
{
    struct DWDMA_CHAN *dwc = NULL;
    int i;

    HAL_ASSERT(dw);

    if (!dw->used) {
        DWDMA_on(dw);
    }

    for (i = 0; i < dw->maxChans; i++) {
        dwc = &dw->chan[i];

        if (dw->used & dwc->mask) {
            continue;
        }

        dwc->periId = id;
        dwc->chanId = i;
        dw->used |= dwc->mask;
        break;
    }

    if (i >= dw->maxChans || !dwc) {
        return NULL;
    }

    return dwc;
}

/**
 * @brief Release a dma channel
 *
 * @param dwc: the handle of dma chan.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 * @note must hold lock.
 */
HAL_Status HAL_DWDMA_ReleaseChannel(struct DWDMA_CHAN *dwc)
{
    struct HAL_DWDMA_DEV *dw;

    HAL_ASSERT(dwc);

    dw = dwc->dw;

    dwc->periId = 0xff;

    dwc->srcMaster = 0;
    dwc->dstMaster = 0;

    dwc->cyclic = false;

    /* Disable interrupts */
    DW_CHAN_CLEAR_BIT(dw->pReg->MASK.TFR, dwc->mask);
    DW_CHAN_CLEAR_BIT(dw->pReg->MASK.BLOCK, dwc->mask);
    DW_CHAN_CLEAR_BIT(dw->pReg->MASK.ERR, dwc->mask);

    dw->used &= ~dwc->mask;
    if (!dw->used) {
        DWDMA_off(dw);
    }

    return HAL_OK;
}

/**
 * @brief Config a dma channel
 *
 * @param dwc: the handle of dma chan.
 * @param config: the peri req config.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_DWDMA_Config(struct DWDMA_CHAN *dwc, struct DMA_SLAVE_CONFIG *config)
{
    memcpy(&dwc->config, config, sizeof(*config));
    dwc->direction = config->direction;

    DW_ConvertBurst(&dwc->config.srcMaxBurst);
    DW_ConvertBurst(&dwc->config.dstMaxBurst);

    return HAL_OK;
}

/**
 * @brief Prepare a cyclic dma transfer for the channel
 *
 * @param dwc: the handle of dma chan.
 * @param dmaAddr: the memory addr.
 * @param len: data len.
 * @param periodLen: periodic len.
 * @param direction: transfer direction.
 * @param callback: callback function.
 * @param cparam: callback param.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_DWDMA_PrepDmaCyclic(struct DWDMA_CHAN *dwc, uint32_t dmaAddr,
                                   uint32_t len, uint32_t periodLen,
                                   eDMA_TRANSFER_DIRECTION direction,
                                   DMA_Callback callback, void *cparam)
{
    HAL_UNUSED struct HAL_DWDMA_DEV *dw;
    struct DMA_SLAVE_CONFIG *config;
    struct DW_DESC *desc, *last = NULL;
    uint32_t regWidth;
    uint32_t periods;
    uint32_t i;

    HAL_ASSERT(dwc);

    dw = dwc->dw;
    config = &dwc->config;

    HAL_ASSERT(HAL_DMA_IsSlaveDirection(direction));

    dwc->direction = direction;

    if (direction == DMA_MEM_TO_DEV) {
        regWidth = DW_FFS(config->dstAddrWidth);
        WRITE_REG(dwc->creg->DAR, config->dstAddr);
    } else {
        regWidth = DW_FFS(config->srcAddrWidth);
        WRITE_REG(dwc->creg->SAR, config->srcAddr);
    }

    periods = len / periodLen;

    /* Check for too big/unaligned periods and unaligned DMA buffer. */
#ifdef HAL_DWDMA_BLOCK_ALIGN_SZ
    HAL_ASSERT(HAL_IS_ALIGNED(periodLen, HAL_DWDMA_BLOCK_ALIGN_SZ));
#endif
    HAL_ASSERT(periodLen <= (dw->blockSize << regWidth));
    HAL_ASSERT(!(periodLen & ((1 << regWidth) - 1)));
    HAL_ASSERT(!(dmaAddr & ((1 << regWidth) - 1)));

    for (i = 0; i < periods; i++) {
        desc = &dwc->desc[i];

        HAL_ASSERT(desc);

        switch (direction) {
        case DMA_MEM_TO_DEV:
            desc->lli.dar = config->dstAddr;
            desc->lli.sar = dmaAddr + (periodLen * i);
            desc->lli.ctllo = (DWC_DEFAULT_CTLLO(dwc)
                               | DWC_CTLL_DST_WIDTH(regWidth)
                               | DWC_CTLL_SRC_WIDTH(regWidth)
                               | DWC_CTLL_DST_FIX
                               | DWC_CTLL_SRC_INC
                               | DWC_CTLL_INT_EN
                               | DWC_CTLL_FC_M2P);

            desc->lli.ctllo &= ~DWC_CTLL_LLP_D_EN;

            break;
        case DMA_DEV_TO_MEM:
            desc->lli.dar = dmaAddr + (periodLen * i);
            desc->lli.sar = config->srcAddr;
            desc->lli.ctllo = (DWC_DEFAULT_CTLLO(dwc)
                               | DWC_CTLL_SRC_WIDTH(regWidth)
                               | DWC_CTLL_DST_WIDTH(regWidth)
                               | DWC_CTLL_DST_INC
                               | DWC_CTLL_SRC_FIX
                               | DWC_CTLL_INT_EN
                               | DWC_CTLL_FC_P2M);

            desc->lli.ctllo &= ~DWC_CTLL_LLP_S_EN;

            break;
        default:
            break;
        }

        desc->lli.ctlhi = (periodLen >> regWidth);
        if (last) {
            last->lli.llp = (uint32_t)desc;
        }

        last = desc;
    }

    /* cyclic */
    last->lli.llp = (uint32_t)&dwc->desc[0];
    dwc->cyclic = true;
    dwc->callback = callback;
    dwc->cparam = cparam;

    HAL_DCACHE_CleanByRange((uint32_t)dwc->desc,
                            NR_DESCS_PER_CHANNEL * sizeof(*(dwc->desc)));

    return HAL_OK;
}

/**
 * @brief Prepare a single dma transfer for the channel
 *
 * @param dwc: the handle of dma chan.
 * @param dmaAddr: the memory addr.
 * @param len: data len.
 * @param direction: transfer direction.
 * @param callback: callback function.
 * @param cparam: callback param.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_DWDMA_PrepDmaSingle(struct DWDMA_CHAN *dwc, uint32_t dmaAddr,
                                   uint32_t len,
                                   eDMA_TRANSFER_DIRECTION direction,
                                   DMA_Callback callback, void *cparam)
{
    struct HAL_DWDMA_DEV *dw;
    struct DMA_SLAVE_CONFIG *config;
    struct DW_DESC *desc, *last = NULL;
    uint32_t regWidth;
    uint32_t xferCount;
    uint32_t offset;
    uint32_t src, dst;
    uint32_t ctllo;
    uint32_t burstLen;
    uint32_t i = 0;

    HAL_ASSERT(dwc);

    dw = dwc->dw;
    config = &dwc->config;

    HAL_ASSERT(HAL_DMA_IsSlaveDirection(direction));

    dwc->direction = direction;

    if (direction == DMA_MEM_TO_DEV) {
        burstLen = config->dstMaxBurst;
        regWidth = DW_FFS(config->dstAddrWidth);
        src = dmaAddr;
        dst = config->dstAddr;
        ctllo = (DWC_DEFAULT_CTLLO(dwc)
                 | DWC_CTLL_SRC_WIDTH(regWidth)
                 | DWC_CTLL_DST_WIDTH(regWidth)
                 | DWC_CTLL_DST_FIX
                 | DWC_CTLL_SRC_INC
                 | DWC_CTLL_FC_M2P);
    } else {
        burstLen = config->srcMaxBurst;
        regWidth = DW_FFS(config->srcAddrWidth);
        src = config->srcAddr;
        dst = dmaAddr;
        ctllo = (DWC_DEFAULT_CTLLO(dwc)
                 | DWC_CTLL_SRC_WIDTH(regWidth)
                 | DWC_CTLL_DST_WIDTH(regWidth)
                 | DWC_CTLL_DST_INC
                 | DWC_CTLL_SRC_FIX
                 | DWC_CTLL_FC_P2M);
    }

    burstLen = DW_GetBurstLength(burstLen);

    for (offset = 0; offset < len; offset += xferCount << regWidth) {
        xferCount = HAL_MIN((len - offset) >> regWidth, dw->blockSize);
        xferCount &= ~(burstLen - 1);
        desc = &dwc->desc[i];
        desc->lli.sar = (ctllo & DWC_CTLL_SRC_FIX) ? src : src + offset;
        desc->lli.dar = (ctllo & DWC_CTLL_DST_FIX) ? dst : dst + offset;
        desc->lli.ctllo = ctllo;
        desc->lli.ctlhi = xferCount;
        desc->len = xferCount << regWidth;

        if (last) {
            last->lli.llp = (uint32_t)desc;
        }

        last = desc;

        i++;
    }

    last->lli.ctllo |= DWC_CTLL_INT_EN;
    last->lli.llp = 0;

    dwc->callback = callback;
    dwc->cparam = cparam;

    HAL_DCACHE_CleanByRange((uint32_t)dwc->desc,
                            NR_DESCS_PER_CHANNEL * sizeof(*(dwc->desc)));

    return HAL_OK;
}

/**
 * @brief Prepare a dma memcpy
 *
 * @param dwc: the handle of dma chan.
 * @param dst: the memory dst addr.
 * @param src: the memory src addr.
 * @param len: data len.
 * @param callback: callback function.
 * @param cparam: callback param.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_DWDMA_PrepDmaMemcpy(struct DWDMA_CHAN *dwc, uint32_t dst,
                                   uint32_t src, uint32_t len,
                                   DMA_Callback callback, void *cparam)
{
    struct HAL_DWDMA_DEV *dw;
    struct DW_DESC *desc, *last = NULL;
    uint32_t xferCount;
    uint32_t offset;
    uint32_t srcWidth;
    uint32_t dstWidth;
    uint32_t dataWidth;
    uint32_t ctllo;
    int i = 0;

    HAL_ASSERT(dwc);
    HAL_ASSERT(len);

    dw = dwc->dw;

    dwc->direction = DMA_MEM_TO_MEM;

    dataWidth = dw->dataWidth;

    srcWidth = dstWidth = DW_FFS(dataWidth | src | dst | len);

    ctllo = DWC_DEFAULT_CTLLO(dwc)
            | DWC_CTLL_DST_WIDTH(dstWidth)
            | DWC_CTLL_SRC_WIDTH(srcWidth)
            | DWC_CTLL_DST_INC
            | DWC_CTLL_SRC_INC
            | DWC_CTLL_FC_M2M;

    for (offset = 0; offset < len; offset += xferCount << srcWidth) {
        xferCount = HAL_MIN((len - offset) >> srcWidth, dw->blockSize);

        desc = &dwc->desc[i];

        desc->lli.sar = src + offset;
        desc->lli.dar = dst + offset;
        desc->lli.ctllo = ctllo;
        desc->lli.ctlhi = xferCount;
        desc->len = xferCount << srcWidth;

        if (last) {
            last->lli.llp = (uint32_t)desc;
        }

        last = desc;

        i++;
    }

    last->lli.ctllo |= DWC_CTLL_INT_EN;
    last->lli.llp = 0;

    dwc->callback = callback;
    dwc->cparam = cparam;

    HAL_DCACHE_CleanByRange((uint32_t)dwc->desc,
                            NR_DESCS_PER_CHANNEL * sizeof(*(dwc->desc)));

    return HAL_OK;
}

/** @} */

/** @} */

/** @} */

#endif /* HAL_DWDMA_MODULE_ENABLED */
