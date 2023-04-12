/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-10-5       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_WHC)

#include <rthw.h>
#include "drv_whc.h"
#include "drv_sys.h"
#include "nu_bitutil.h"

/* Private define ---------------------------------------------------------------*/
enum
{
    WHC_START = -1,
#if defined(BSP_USING_WHC0)
    WHC0_IDX,
#endif
#if defined(BSP_USING_WHC1)
    WHC1_IDX,
#endif
    WHC_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_whc_priv
{
    char            *name;
    WHC_T           *base;
    IRQn_Type       irqn;
    uint32_t        rstidx;

    rt_device_t     psChDev[WHC_CH];
};
typedef struct nu_whc_priv *nu_whc_priv_t;

struct nu_whc
{
    struct rt_device dev;
    nu_whc_priv_t    psPriv;
    uint32_t u32WhcChNum;
    void *pvTxBuf;
};
typedef struct nu_whc *nu_whc_t;

static struct nu_whc_priv nu_whc_priv_arr [] =
{
#if defined(BSP_USING_WHC0)
    {
        .name   = "whc0",
        .base   = WHC0,
        .irqn   = WHC0_IRQn,
        .rstidx = WHC0_RST,
    },
#endif
#if defined(BSP_USING_WHC1)
    {
        .name   = "whc1",
        .base   = WHC1,
        .irqn   = WHC1_IRQn,
        .rstidx = WHC1_RST,
    },
#endif
}; /* nu_whc_priv */

/**
 * All WHC interrupt service routine
 */
static void nu_whc_isr(int vector, void *param)
{
    nu_whc_priv_t psNuWhcPriv = (nu_whc_priv_t)param;

    volatile uint32_t vu32Intsts = psNuWhcPriv->base->INTSTS;
    uint32_t irqidx;

    while ((irqidx = nu_ctz(vu32Intsts)) != 32)
    {
        uint32_t u32IsrBitMask =  1 << irqidx ;

        switch (irqidx)
        {
        /* Process TX-complete interrupt event */
        case WHC_INTSTS_TX0IF_Pos:
        case WHC_INTSTS_TX1IF_Pos:
        case WHC_INTSTS_TX2IF_Pos:
        case WHC_INTSTS_TX3IF_Pos:
        {
            uint32_t u32ChNum = irqidx - WHC_INTSTS_TX0IF_Pos;
            rt_device_t device = psNuWhcPriv->psChDev[u32ChNum];
            nu_whc_t psWhc = (nu_whc_t)device;

            if (device->tx_complete && psWhc->pvTxBuf)
            {
                device->tx_complete(device, psWhc->pvTxBuf);
                psWhc->pvTxBuf = RT_NULL;
            }
        }
        break;

        /* Process RX-indicate interrupt event */
        case WHC_INTSTS_RX0IF_Pos:
        case WHC_INTSTS_RX1IF_Pos:
        case WHC_INTSTS_RX2IF_Pos:
        case WHC_INTSTS_RX3IF_Pos:
        {
            uint32_t u32ChNum = irqidx - WHC_INTSTS_RX0IF_Pos;
            rt_device_t device = psNuWhcPriv->psChDev[u32ChNum];

            if (device->rx_indicate)
            {
                device->rx_indicate(device, 1);
            }
        }
        break;

        default:
            break;
        }

        /* Clear interrupt bit. */
        WHC_CLR_INT_FLAG(psNuWhcPriv->base, u32IsrBitMask);

        /* Clear served bit */
        vu32Intsts &= ~(u32IsrBitMask);
    }
}

rt_err_t nu_whc_init(rt_device_t dev)
{
    return RT_EOK;
}

rt_err_t nu_whc_open(rt_device_t dev, rt_uint16_t oflag)
{
    nu_whc_t psWhc = (nu_whc_t)dev;
    nu_whc_priv_t psWhcPriv = psWhc->psPriv;

    WHC_ENABLE_INT(psWhcPriv->base, WHC_INTEN_TX0IEN_Msk << psWhc->u32WhcChNum |
                   WHC_INTEN_RX0IEN_Msk << psWhc->u32WhcChNum);

    return RT_EOK;
}

rt_err_t nu_whc_close(rt_device_t dev)
{
    nu_whc_t psWhc = (nu_whc_t)dev;
    nu_whc_priv_t psWhcPriv = psWhc->psPriv;

    WHC_DISABLE_INT(psWhcPriv->base, WHC_INTEN_TX0IEN_Msk << psWhc->u32WhcChNum |
                    WHC_INTEN_RX0IEN_Msk << psWhc->u32WhcChNum);

    return RT_EOK;
}

rt_ssize_t nu_whc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    nu_whc_t psWhc = (nu_whc_t)dev;
    nu_whc_priv_t psWhcPriv = psWhc->psPriv;

    if ((sizeof(nu_whc_msg) != size) || ((uint32_t)buffer & 0x3))
        goto exit_nu_whc_read;

    if (WHC_Recv(psWhcPriv->base, psWhc->u32WhcChNum, (uint32_t *)buffer) < 0)
        goto exit_nu_whc_read;

    return size;

exit_nu_whc_read:

    return 0;
}

rt_ssize_t nu_whc_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    nu_whc_t psWhc = (nu_whc_t)dev;
    nu_whc_priv_t psWhcPriv = psWhc->psPriv;

    if ((sizeof(nu_whc_msg) != size) || ((uint32_t)buffer & 0x3))
        goto exit_nu_whc_write;

    psWhc->pvTxBuf = (void *)buffer;
    if (WHC_Send(psWhcPriv->base, psWhc->u32WhcChNum, (uint32_t *)buffer) < 0)
        goto exit_nu_whc_write;

    return size;

exit_nu_whc_write:

    return 0;
}

rt_err_t  nu_whc_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

static rt_err_t whc_register(nu_whc_priv_t psWhcPriv)
{
    int i;
    char szDevName[16];

    for (i = 0; i < WHC_CH; i++)
    {
        nu_whc_t  psWhc;
        rt_device_t device = rt_device_create(RT_Device_Class_Miscellaneous, sizeof(struct nu_whc) - sizeof(struct rt_device));
        RT_ASSERT(device);

        psWhcPriv->psChDev[i] = device;
        psWhc = (nu_whc_t)device;
        psWhc->psPriv = psWhcPriv;
        psWhc->u32WhcChNum = i;

        device->type        = RT_Device_Class_Miscellaneous;
        device->rx_indicate = RT_NULL;
        device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
        device->ops         = RT_NULL;
#else
        device->init        = nu_whc_init;
        device->open        = nu_whc_open;
        device->close       = nu_whc_close;
        device->read        = nu_whc_read;
        device->write       = nu_whc_write;
        device->control     = nu_whc_control;
#endif
        device->user_data   = (void *)psWhcPriv;

        rt_snprintf(szDevName, sizeof(szDevName), "%s-%d", psWhcPriv->name, psWhc->u32WhcChNum);

        RT_ASSERT(rt_device_register(device, szDevName, RT_DEVICE_FLAG_STANDALONE) == RT_EOK);
    }

    return RT_EOK;
}

/**
 * Hardware Sem Initialization
 */
int rt_hw_whc_init(void)
{
    int i;

    for (i = (WHC_START + 1); i < WHC_CNT; i++)
    {
        nu_whc_priv_t psNuWhcPriv = &nu_whc_priv_arr[i];

        whc_register(psNuWhcPriv);

        rt_hw_interrupt_install(psNuWhcPriv->irqn, nu_whc_isr, psNuWhcPriv, psNuWhcPriv->name);
        rt_hw_interrupt_umask(nu_whc_priv_arr[i].irqn);
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_whc_init);

#endif //#if defined(BSP_USING_WHC)
