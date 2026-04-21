/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_LLSI)

#include "drv_llsi.h"
#include "drv_pdma.h"
#include "nu_bitutil.h"
#include "rthw.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.llsi"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#define MAKE_LLSI_NAME(x)         #x
#define MAKE_PDMA_LLSI_TX(x)      PDMA_LLSI##x##_TX
#define MAKE_PDMA_ELLSI_TX(x)     PDMA_ELLSI##x##_TX

#if defined(BSP_USING_PDMA_LLSI_TX)
#define MAKE_LLSI_PDMA_TX_REQ(t)    .pdma_perp_tx = t
#else
#define MAKE_LLSI_PDMA_TX_REQ(t)
#endif
#define MAKE_LLSI_INSTANCE(x, t) \
    { \
        .name  = MAKE_LLSI_NAME(llsi##x), \
        .base  = LLSI##x, \
        .rst   = LLSI##x##_RST, \
        .irqn  = LLSI##x##_IRQn, \
        .modid = LLSI##x##_MODULE, \
        MAKE_LLSI_PDMA_TX_REQ(t)  \
    },
#define MAKE_ELLSI_INSTANCE(x, t) \
    { \
        .name  = MAKE_LLSI_NAME(ellsi##x), \
        .base  = (LLSI_T*)ELLSI##x, \
        .rst   = ELLSI##x##_RST, \
        .irqn  = ELLSI##x##_IRQn, \
        .modid = ELLSI##x##_MODULE, \
        MAKE_LLSI_PDMA_TX_REQ(t)  \
    },

/* Types / Structures ---------------------------------------------------------*/
enum
{
    LLSI_START = -1,
#if defined(BSP_USING_LLSI0)
    LLSI0_IDX,
#endif
#if defined(BSP_USING_LLSI1)
    LLSI1_IDX,
#endif
#if defined(BSP_USING_LLSI2)
    LLSI2_IDX,
#endif
#if defined(BSP_USING_LLSI3)
    LLSI3_IDX,
#endif
#if defined(BSP_USING_LLSI4)
    LLSI4_IDX,
#endif
#if defined(BSP_USING_LLSI5)
    LLSI5_IDX,
#endif
#if defined(BSP_USING_LLSI6)
    LLSI6_IDX,
#endif
#if defined(BSP_USING_LLSI7)
    LLSI7_IDX,
#endif
#if defined(BSP_USING_LLSI8)
    LLSI8_IDX,
#endif
#if defined(BSP_USING_LLSI9)
    LLSI9_IDX,
#endif
#if defined(BSP_USING_ELLSI0)
    ELLSI0_IDX,
#endif
    LLSI_CNT
};

struct nu_llsi
{
    struct rt_device device;
    char *name;
    LLSI_T *base;
    uint32_t rst;
    uint32_t modid;
    IRQn_Type irqn;
#if defined(BSP_USING_PDMA_LLSI_TX)
    uint32_t dma_flag;

    int32_t pdma_perp_tx;
    int32_t pdma_chanid_tx;

    nu_pdma_desc_t pdma_tx_desc;
#endif

    S_LLSI_CONFIG_T config;
};
typedef struct nu_llsi *nu_llsi_t;

/* Static Function Prototypes ------------------------------------------------*/
static void dump_interrupt_event(uint32_t u32Status);
static void nu_llsi_isr(nu_llsi_t llsi);
static rt_err_t llsi_init(rt_device_t dev);
static rt_err_t llsi_open(rt_device_t dev, rt_uint16_t oflag);
static rt_err_t llsi_close(rt_device_t dev);
static rt_err_t llsi_control(rt_device_t dev, int cmd, void *args);
static rt_size_t llsi_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
static void nu_pdma_llsi_tx_cb_trigger(void *pvUserData, uint32_t u32UserData);
static rt_size_t llsi_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
static int nu_hw_llsi_dma_allocate(nu_llsi_t psNuLlsi);
static rt_err_t llsi_register(struct rt_device *device, const char *name, void *user_data);

/* Static Variables ----------------------------------------------------------*/
static const S_LLSI_CONFIG_T s_sLlsiConfig = NU_LLSI_CONFIG_DEFAULT;

static struct nu_llsi nu_llsi_arr [] =
{
#if defined(BSP_USING_LLSI0)
    MAKE_LLSI_INSTANCE(0, MAKE_PDMA_LLSI_TX(0))
#endif
#if defined(BSP_USING_LLSI1)
    MAKE_LLSI_INSTANCE(1, MAKE_PDMA_LLSI_TX(1))
#endif
#if defined(BSP_USING_LLSI2)
    MAKE_LLSI_INSTANCE(2, MAKE_PDMA_LLSI_TX(2))
#endif
#if defined(BSP_USING_LLSI3)
    MAKE_LLSI_INSTANCE(3, MAKE_PDMA_LLSI_TX(3))
#endif
#if defined(BSP_USING_LLSI4)
    MAKE_LLSI_INSTANCE(4, MAKE_PDMA_LLSI_TX(4))
#endif
#if defined(BSP_USING_LLSI5)
    MAKE_LLSI_INSTANCE(5, MAKE_PDMA_LLSI_TX(5))
#endif
#if defined(BSP_USING_LLSI6)
    MAKE_LLSI_INSTANCE(6, MAKE_PDMA_LLSI_TX(6))
#endif
#if defined(BSP_USING_LLSI7)
    MAKE_LLSI_INSTANCE(7, MAKE_PDMA_LLSI_TX(7))
#endif
#if defined(BSP_USING_LLSI8)
    MAKE_LLSI_INSTANCE(8, MAKE_PDMA_LLSI_TX(8))
#endif
#if defined(BSP_USING_LLSI9)
    MAKE_LLSI_INSTANCE(9, MAKE_PDMA_LLSI_TX(9))
#endif
#if defined(BSP_USING_ELLSI0)
    MAKE_ELLSI_INSTANCE(0, MAKE_PDMA_ELLSI_TX(0))
#endif
};

static const char *szIR[] =
{
    "LLSI_RSTCIF - Reset Command Interrupt",
    "LLSI_EMPIF - Transmit FIFO buffer is empty",
    "LLSI_FULIF - Transmit FIFO buffer is full",
    "LLSI_TXTHIF - FIFO buffer is less than or equal to the setting",
    "LLSI_UNDFLIF - Valid data in FIFO is less than 3 bytes",
    "LLSI_FENDIF - Finished data transmission",
    "RESERVE",
    "RESERVE",
    "LLSI_LDT - Last Data Transmit",
};

#if defined(RT_USING_DEVICE_OPS)
static struct rt_device_ops llsi_ops =
{
    .init = llsi_init,
    .open = llsi_open,
    .close = llsi_close,
    .read = llsi_read,
    .write = llsi_write,
    .control = llsi_control,
};
#endif

/* Functions Implementation --------------------------------------------------*/
static void dump_interrupt_event(uint32_t u32Status)
{
    uint32_t idx;
    while ((idx = nu_ctz(u32Status)) < 32) // Count Trailing Zeros == > Find First One
    {
        LOG_D("[%s]", szIR[idx]);
        u32Status &= ~(1 << idx);
    }
}

static void nu_llsi_isr(nu_llsi_t llsi)
{
    LLSI_T *base = llsi->base;
    uint32_t u32IntSts;

    u32IntSts = base->STATUS;

    /* Dump IR event */
    dump_interrupt_event(u32IntSts);

    base->STATUS = u32IntSts;
}
#define MAKE_LLSI_ISR(x) \
    void LLSI##x##_IRQHandler(void) \
    { \
       rt_interrupt_enter(); \
       nu_llsi_isr(&nu_llsi_arr[LLSI##x##_IDX]); \
       rt_interrupt_leave(); \
    }
#define MAKE_ELLSI_ISR(x) \
    void ELLSI##x##_IRQHandler(void) \
    { \
       rt_interrupt_enter(); \
       nu_llsi_isr(&nu_llsi_arr[ELLSI##x##_IDX]); \
       rt_interrupt_leave(); \
    }
#if defined(BSP_USING_LLSI0)
    MAKE_LLSI_ISR(0);
#endif
#if defined(BSP_USING_LLSI1)
    MAKE_LLSI_ISR(1);
#endif
#if defined(BSP_USING_LLSI2)
    MAKE_LLSI_ISR(2);
#endif
#if defined(BSP_USING_LLSI3)
    MAKE_LLSI_ISR(3);
#endif
#if defined(BSP_USING_LLSI4)
    MAKE_LLSI_ISR(4);
#endif
#if defined(BSP_USING_LLSI5)
    MAKE_LLSI_ISR(5);
#endif
#if defined(BSP_USING_LLSI6)
    MAKE_LLSI_ISR(6);
#endif
#if defined(BSP_USING_LLSI7)
    MAKE_LLSI_ISR(7);
#endif
#if defined(BSP_USING_LLSI8)
    MAKE_LLSI_ISR(8);
#endif
#if defined(BSP_USING_LLSI9)
    MAKE_LLSI_ISR(9);
#endif
#if defined(BSP_USING_ELLSI0)
    MAKE_ELLSI_ISR(0);
#endif

/* common device interface */
static rt_err_t llsi_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t llsi_open(rt_device_t dev, rt_uint16_t oflag)
{
    nu_llsi_t psNuLlsi = (nu_llsi_t)dev;

    RT_ASSERT(psNuLlsi);

    /* Reset IP */
    SYS_ResetModule(psNuLlsi->rst);

    LLSI_OpenbyConfig(psNuLlsi->base, &psNuLlsi->config);

    /* Enable reset command function */
    LLSI_ENABLE_RESET_COMMAND(psNuLlsi->base);

    /* Unmask External LLSI Interrupt */
    NVIC_EnableIRQ(psNuLlsi->irqn);

    return RT_EOK;
}

static rt_err_t llsi_close(rt_device_t dev)
{
    nu_llsi_t psNuLlsi = (nu_llsi_t)dev;

    RT_ASSERT(psNuLlsi);

    /* Mask External LLSI Interrupt */
    NVIC_DisableIRQ(psNuLlsi->irqn);

    LLSI_Close(psNuLlsi->base);

    return RT_EOK;
}

static rt_err_t llsi_control(rt_device_t dev, int cmd, void *args)
{
    nu_llsi_t psNuLlsi = (nu_llsi_t)dev;

    RT_ASSERT(psNuLlsi);

    switch (cmd)
    {
    default:
    {
        S_LLSI_CONFIG_T *pconfig = (S_LLSI_CONFIG_T *)args;

        RT_ASSERT(args);

        rt_memcpy(&psNuLlsi->config, pconfig, sizeof(S_LLSI_CONFIG_T));
    }
    break;
    }

    return RT_EOK;
}

static rt_size_t llsi_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    nu_llsi_t psNuLlsi = (nu_llsi_t)dev;
    rt_err_t ret = -RT_ERROR;

    RT_ASSERT(psNuLlsi);

    return 0;
}

static void nu_pdma_llsi_tx_cb_trigger(void *pvUserData, uint32_t u32UserData)
{
    /* Get base address of LLSI */
    LLSI_T *base = (LLSI_T *)pvUserData;

    /* Trigger PDMA transfer. */
    LLSI_ENABLE(base);
}

static rt_size_t llsi_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    nu_llsi_t psNuLlsi = (nu_llsi_t)dev;
    rt_err_t ret = -RT_ERROR;
    struct nu_pdma_chn_cb sChnCB;

    RT_ASSERT(psNuLlsi);

    /* Register llsi trigger callback function */
    sChnCB.m_eCBType = eCBType_Trigger;
    sChnCB.m_pfnCBHandler = nu_pdma_llsi_tx_cb_trigger;
    sChnCB.m_pvUserData = (void *)psNuLlsi->base;
    ret = nu_pdma_callback_register(psNuLlsi->pdma_chanid_tx, &sChnCB);
    RT_ASSERT(ret == RT_EOK);

    ret = nu_pdma_transfer(psNuLlsi->pdma_chanid_tx,
                           32,
                           (uint32_t)buffer,
                           (uint32_t)&psNuLlsi->base->DATA,
                           RT_ALIGN(size, 4) / 4,
                           0);  // wait-forever
    RT_ASSERT(ret == RT_EOK);

    return size;
}

static int nu_hw_llsi_dma_allocate(nu_llsi_t psNuLlsi)
{
    rt_err_t ret = -RT_ERROR;

    RT_ASSERT(psNuLlsi);

    psNuLlsi->dma_flag = 0;

    /* Allocate LLSI nu_dma channel */
    if (psNuLlsi->pdma_perp_tx != NU_PDMA_UNUSED)
    {
        psNuLlsi->pdma_chanid_tx = nu_pdma_channel_allocate(psNuLlsi->pdma_perp_tx);
        if (psNuLlsi->pdma_chanid_tx >= 0)
        {
            psNuLlsi->dma_flag |= RT_DEVICE_FLAG_DMA_TX;
            ret = RT_EOK;
        }
    }

    return ret;
}
static rt_err_t llsi_register(struct rt_device *device, const char *name, void *user_data)
{
    RT_ASSERT(device);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
#if defined(RT_USING_DEVICE_OPS)
    device->ops         = &llsi_ops;
#else
    device->init        = llsi_init;
    device->open        = llsi_open;
    device->close       = llsi_close;
    device->read        = llsi_read;
    device->write       = llsi_write;
    device->control     = llsi_control;
#endif

    device->user_data   = user_data;

    return rt_device_register(device, name, RT_DEVICE_FLAG_WRONLY);
}

/**
 * Hardware LLSI Initialization
 */
int rt_hw_llsi_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (LLSI_START + 1); i < LLSI_CNT; i++)
    {
        nu_llsi_arr[i].config = s_sLlsiConfig;
#if defined(BSP_USING_PDMA_LLSI_TX)
        ret = nu_hw_llsi_dma_allocate(&nu_llsi_arr[i]);
        RT_ASSERT(ret == RT_EOK);
#endif

        ret = llsi_register(&nu_llsi_arr[i].device, nu_llsi_arr[i].name, NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_llsi_init);
#endif //#if defined(BSP_USING_LLSI)
