/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

#ifdef HAL_PL330_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup PL330
 *  @{
 */

#ifndef _HAL_PL330_H
#define _HAL_PL330_H

#include "hal_def.h"

/** @defgroup PL330_Exported_Definition_Group1 Basic Definition
 *  @{
 */

/***************************** MACRO Definition ******************************/

/** PL330 status */
#define PL330_STATE_STOPPED        HAL_BIT(0)
#define PL330_STATE_EXECUTING      HAL_BIT(1)
#define PL330_STATE_WFE            HAL_BIT(2)
#define PL330_STATE_FAULTING       HAL_BIT(3)
#define PL330_STATE_COMPLETING     HAL_BIT(4)
#define PL330_STATE_WFP            HAL_BIT(5)
#define PL330_STATE_KILLING        HAL_BIT(6)
#define PL330_STATE_FAULT_COMPLETE HAL_BIT(7)
#define PL330_STATE_CACHEMISS      HAL_BIT(8)
#define PL330_STATE_UPDTPC         HAL_BIT(9)
#define PL330_STATE_ATBARRIER      HAL_BIT(10)
#define PL330_STATE_QUEUEBUSY      HAL_BIT(11)
#define PL330_STATE_INVALID        HAL_BIT(15)

#define PL330_STABLE_STATES                                          \
    (PL330_STATE_STOPPED | PL330_STATE_EXECUTING | PL330_STATE_WFE | \
     PL330_STATE_FAULTING)

#define PL330_MAX_CHAN  8
#define PL330_MAX_IRQS  32
#define PL330_MAX_PERI  32
#define PL330_MAX_BURST 16

/*
 * With 256 bytes, we can do more than 2.5MB and 5MB xfers per req
 * at 1byte/burst for P<->M and M<->M respectively.
 * For typical scenario, at 1word/burst, 10MB and 20MB xfers per req
 * should be enough for P<->M and M<->M respectively.
 */
#define MCODE_BUFF_PER_REQ     256
#define PL330_MAX_CHAN_BUFS    2
#define PL330_CHAN_BUF_LEN     128
#define PL330_CHANNELS_PER_DEV 8
#define PL330_NR_IRQS          2

/***************************** Structure Definition **************************/

/** enum PL330_CACHECTRL - pl330 cache control */
typedef enum {
    CCTRL0, /**< Noncacheable and nonbufferable */
    CCTRL1, /**< Bufferable only */
    CCTRL2, /**< Cacheable, but do not allocate */
    CCTRL3, /**< Cacheable and bufferable, but do not allocate */
    INVALID1, /**< AWCACHE = 0x1000 */
    INVALID2,
    CCTRL6, /**< Cacheable write-through, allocate on writes only */
    CCTRL7, /**< Cacheable write-back, allocate on writes only */
} ePL330_CACHECTRL;

/** enum PL330_BYTESWAP - pl330 byte swap control */
typedef enum {
    SWAP_NO,
    SWAP_2,
    SWAP_4,
    SWAP_8,
    SWAP_16,
} ePL330_BYTESWAP;

/**
 * enum PL330_COND - dma transfer mode
 */
typedef enum {
    SINGLE,
    BURST,
    ALWAYS,
} ePL330_COND;

/** PL330 soc configuration */
struct PL330_CONFIG {
    uint32_t periphId;
    uint32_t mode;
    uint32_t dataBusWidth; /**< In number of bits */
    uint32_t dataBufDep;
    uint32_t numChan;
    uint32_t numPeri;
    uint32_t periNs;
    uint32_t numEvents;
    uint32_t irqNs;
};

/** PL330 request config */
struct PL330_REQCFG {
    /* Address Incrementing */
    uint32_t dstInc;
    uint32_t srcInc;

    /*
     * For now, the SRC & DST protection levels
     * and burst size/length are assumed same.
     */
    bool nonsecure;
    bool privileged;
    bool insnaccess;
    uint32_t brstLen;
    uint32_t brstSize; /**< bytes */

    ePL330_CACHECTRL dcctl;
    ePL330_CACHECTRL scctl;
    ePL330_BYTESWAP swap;
};

/** DMA block descriptor struct. */
struct PL330_XFER {
    uint32_t srcAddr; /**< Source starting address */
    uint32_t dstAddr; /**< Destination starting address */
    uint32_t length; /**< Number of bytes for the xfer */
};

/**
 * It's the done callback a user can set for a desc
 */
typedef void (*PL330_Callback)(void *cparam);

/**
 * A DMA Desc consisits of a request config struct, a xfer descriptor,
 * a pointer pointing to generated DMA program, and execution result.
 */
struct PL330_DESC {
    struct PL330_REQCFG rqcfg;
    struct PL330_XFER px;
    uint8_t peri;
    eDMA_TRANSFER_DIRECTION dir;
    bool cyclic;
    uint32_t numPeriods;
    uint32_t bytesReq;
    uint16_t srcInterlaceSize;
    uint16_t dstInterlaceSize;
    void *mcBuf;
    PL330_Callback callback;
    void *cparam;
};

struct PL330_XFER_SPEC {
    uint32_t ccr;
    struct PL330_DESC *desc;
};

struct HAL_PL330_DEV;
/**
 * The PL330_CHAN Data is a struct to book keep individual channel of
 * the DMAC.
 */
struct PL330_CHAN {
    uint16_t periId;
    uint16_t chanId;
    uint32_t fifoAddr;
    uint32_t brstSz;
    uint32_t brstLen;
    uint16_t srcInterlaceSize;
    uint16_t dstInterlaceSize;
    struct PL330_DESC desc;
    struct HAL_PL330_DEV *pl330;
    void *mcBuf;
    bool used;
};

/**
 * The PL330 driver instance data structure. A pointer to an instance data
 * structure is passed around by functions to refer to a specific driver
 * instance.
 */
struct HAL_PL330_DEV {
    struct DMA_REG *pReg;
    struct PL330_CHAN chans[PL330_CHANNELS_PER_DEV];
    struct PL330_CONFIG pcfg;
    ePL330_COND peripReqType;
    IRQn_Type irq[PL330_NR_IRQS];
    ePD_Id pd;

    void *priv;
};

/** @} */

/***************************** Function Declare ******************************/
/** @defgroup PL330_Public_Function_Declare Public Function Declare
 *  @{
 */

HAL_Status HAL_PL330_Init(struct HAL_PL330_DEV *pl330);
HAL_Status HAL_PL330_DeInit(struct HAL_PL330_DEV *pl330);

HAL_Status HAL_PL330_Start(struct PL330_CHAN *pchan);
HAL_Status HAL_PL330_Stop(struct PL330_CHAN *pchan);

struct PL330_CHAN *HAL_PL330_RequestChannel(struct HAL_PL330_DEV *pl330, DMA_REQ_Type id);
HAL_Status HAL_PL330_ReleaseChannel(struct PL330_CHAN *pchan);

HAL_Status HAL_PL330_Config(struct PL330_CHAN *pchan, struct DMA_SLAVE_CONFIG *config);
HAL_Status HAL_PL330_PrepDmaMemcpy(struct PL330_CHAN *pchan, uint32_t dst,
                                   uint32_t src, uint32_t len,
                                   PL330_Callback callback, void *cparam);
HAL_Status HAL_PL330_PrepDmaCyclic(struct PL330_CHAN *pchan, uint32_t dmaAddr,
                                   uint32_t len, uint32_t periodLen,
                                   eDMA_TRANSFER_DIRECTION direction,
                                   PL330_Callback callback, void *cparam);
HAL_Status HAL_PL330_PrepDmaSingle(struct PL330_CHAN *pchan, uint32_t dmaAddr,
                                   uint32_t len,
                                   eDMA_TRANSFER_DIRECTION direction,
                                   PL330_Callback callback, void *cparam);
int HAL_PL330_GetPosition(struct PL330_CHAN *pchan);

uint32_t HAL_PL330_IrqHandler(struct HAL_PL330_DEV *pl330);
uint32_t HAL_PL330_GetRawIrqStatus(struct HAL_PL330_DEV *pl330);
HAL_Status HAL_PL330_ClearIrq(struct HAL_PL330_DEV *pl330, uint32_t irq);

HAL_Status HAL_PL330_SetMcBuf(struct PL330_CHAN *pchan, void *buf);
void *HAL_PL330_GetMcBuf(struct PL330_CHAN *pchan);
const struct PL330_DESC *HAL_PL330_GetDesc(struct PL330_CHAN *pchan);

/** @} */

#endif

/** @} */

/** @} */

#endif
/* HAL_PL330_MODULE_ENABLED */
