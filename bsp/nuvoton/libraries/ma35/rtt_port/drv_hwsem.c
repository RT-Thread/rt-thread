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

#if defined(BSP_USING_HWSEM)

#include <rthw.h>
#include "drv_hwsem.h"
#include "drv_sys.h"
#include "drv_common.h"
#include "nu_bitutil.h"

/* Private define ---------------------------------------------------------------*/
enum
{
    HWSEM_START = -1,
#if defined(BSP_USING_HWSEM0)
    HWSEM0_IDX,
#endif
    HWSEM_END
};

/* Private typedef --------------------------------------------------------------*/

struct nu_mutex_priv
{
    struct nu_mutex parent;

    rt_thread_t owner;
    uint8_t key;
    uint8_t hold;
    struct rt_completion completion;
    void *user_data;
};
typedef struct nu_mutex_priv *nu_mutex_priv_t;

struct nu_hwsem
{
    struct rt_device  dev;
    char            *name;
    HWSEM_T         *base;
    IRQn_Type       irqn;
    uint32_t        rstidx;

    struct nu_mutex_priv mutex[evHWSEM_CNT];
};
typedef struct nu_hwsem *nu_hwsem_t;

static struct nu_hwsem nu_hwsem_arr [] =
{
#if defined(BSP_USING_HWSEM0)
    {
        .name   = "hwsem0",
        .base   = HWSEM0,
        .irqn   = HWSEM0_IRQn,
        .rstidx = HWSEM0_RST,
    },
#endif
}; /* nu_hwsem */

/**
 * All HWSEM interrupt service routine
 */
static void nu_hwsem_isr(int vector, void *param)
{
    nu_hwsem_t psNuHwSem = (nu_hwsem_t)param;
    rt_int32_t irqidx;

    volatile uint32_t vu32Intsts = psNuHwSem->base->INTSTS_CORE;

    while ((irqidx = nu_ctz(vu32Intsts)) < evHWSEM_CNT)
    {
        nu_mutex_priv_t priv = (nu_mutex_priv_t)&psNuHwSem->mutex[irqidx];
        uint32_t u32IsrBitMask =  1 << irqidx ;

        HWSEM_CLR_INT_FLAG(psNuHwSem->base, irqidx);

        /* Unlocked, Signal waiter. */
        rt_completion_done(&priv->completion);

        /* Clear sent bit */
        vu32Intsts &= ~(u32IsrBitMask);
    }
}

nu_mutex_t nu_mutex_init(struct rt_device *device, E_HWSEM_ID id)
{
    if (id < evHWSEM_CNT)
    {
        nu_hwsem_t psNuHwSem = (nu_hwsem_t)device->user_data;
        nu_mutex_t mutex = (nu_mutex_t)&psNuHwSem->mutex[id];
        nu_mutex_priv_t priv = (nu_mutex_priv_t)mutex;

        if (!priv->owner)
        {
            priv->owner = rt_thread_self();
        }
        else
        {
            goto exit_nu_mutex_init;
        }

        return mutex;
    }

exit_nu_mutex_init:

    return RT_NULL;
}

void nu_mutex_deinit(struct rt_device *device, E_HWSEM_ID id)
{
    if (id < evHWSEM_CNT)
    {
        nu_hwsem_t psNuHwSem = (nu_hwsem_t)device->user_data;
        nu_mutex_t mutex = (nu_mutex_t)&psNuHwSem->mutex[id];
        nu_mutex_priv_t priv = (nu_mutex_priv_t)mutex;

        if (priv->owner == rt_thread_self())
        {
            priv->owner = RT_NULL;
        }

    }

}

rt_err_t nu_mutex_take(nu_mutex_t mutex, rt_int32_t timeout)
{
    rt_err_t ret = RT_EOK;
    nu_mutex_priv_t priv = (nu_mutex_priv_t)mutex;
    nu_hwsem_t dev = (nu_hwsem_t)priv->user_data;

    uint8_t u8PrivKey = priv->key;

#ifdef RT_USING_SMP
    u8PrivKey |= (rt_hw_cpu_id() << 6);
#endif /* RT_USING_SMP */

    if (priv->owner != rt_thread_self())
    {
        return -RT_ERROR;
    }

    rt_completion_init(&priv->completion);

    while (1)
    {
        if (HWSEM_IS_LOCKED(dev->base, mutex->id) != HWSEM_NOLOCK)
        {
            /* LOCKED */
            if (HWSEM_GET_KEY(dev->base, mutex->id) != u8PrivKey)
            {
                /* Enable interrupt */
                HWSEM_ENABLE_INT(dev->base, mutex->id);

                /* owner is NOT me. */
                if (rt_completion_wait(&priv->completion, timeout) != RT_EOK)
                {
                    ret = -RT_EBUSY;
                    break;
                }
                else
                {
                    /* Got notification, do lock. */
                }
            }
            else
            {
                /* owner is me. */
                priv->hold++;
                break;
            }
        }
        else
        {
            /* NOLOCK, To lock */
            HWSEM_LOCK(dev->base, mutex->id, u8PrivKey);
            if (HWSEM_GET_KEY(dev->base, mutex->id) == u8PrivKey)
            {
                /* owner is me. */
                priv->hold = 1;

                /* Disable interrupt */
                HWSEM_DISABLE_INT(dev->base, mutex->id);

                break;
            }
            else
            {
                /* Failed to lock, owner is not me. wait notification. */
            }
        }

    } //while(1)

    return ret;
}
RTM_EXPORT(nu_mutex_take);

rt_err_t nu_mutex_release(nu_mutex_t mutex)
{
    rt_err_t ret = RT_EOK;
    nu_mutex_priv_t priv = (nu_mutex_priv_t)mutex;
    nu_hwsem_t dev = (nu_hwsem_t)priv->user_data;

    uint8_t u8PrivKey = priv->key;

    if (priv->owner != rt_thread_self())
    {
        return -RT_ERROR;
    }

#ifdef RT_USING_SMP
    u8PrivKey |= (rt_hw_cpu_id() << 6);
#endif /* RT_USING_SMP */

    if (HWSEM_IS_LOCKED(dev->base, mutex->id) != 0 &&
            HWSEM_GET_KEY(dev->base, mutex->id) == u8PrivKey)
    {
        priv->hold--;
        if (priv->hold == 0)
        {
            /* Unlocked */
            HWSEM_UNLOCK(dev->base, mutex->id, u8PrivKey);
        }
    }
    else
    {
        ret = -RT_ERROR;
    }

    return ret;
}
RTM_EXPORT(nu_mutex_release);

static rt_err_t hwsem_register(struct rt_device *device, const char *name, void *user_data)
{
    RT_ASSERT(device);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = RT_NULL;
#else
    device->init        = RT_NULL;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = RT_NULL;
#endif
    device->user_data   = user_data;

    return rt_device_register(device, name, RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_STANDALONE);
}

/**
 * Hardware Sem Initialization
 */
int rt_hw_hwsem_init(void)
{
    int i, j;
    rt_err_t ret = RT_EOK;

    for (i = (HWSEM_START + 1); i < HWSEM_END; i++)
    {
#if !defined(USE_MA35D1_SUBM)
        /* Reset this module */
        nu_sys_ip_reset(nu_hwsem_arr[i].rstidx);
#endif
        for (j = 0; j < evHWSEM_CNT; j++)
        {
            nu_hwsem_arr[i].mutex[j].parent.id = (E_HWSEM_ID)j;
            nu_hwsem_arr[i].mutex[j].user_data = (void *)&nu_hwsem_arr[i];
            nu_hwsem_arr[i].mutex[j].key = (HWSEM_LOCK_BY_OWNER << 4) | j;   // CoreID + SemID
            nu_hwsem_arr[i].mutex[j].hold = 0;
            nu_hwsem_arr[i].mutex[j].owner = RT_NULL;

            if (HWSEM_IS_LOCKED(nu_hwsem_arr[i].base, j) == HWSEM_LOCK_BY_OWNER)
                HWSEM_UNLOCK(nu_hwsem_arr[i].base, j, nu_hwsem_arr[i].mutex[j].key);

            /* Disable interrupt */
            HWSEM_DISABLE_INT(nu_hwsem_arr[i].base, j);
        }

        rt_hw_interrupt_install(nu_hwsem_arr[i].irqn, nu_hwsem_isr, &nu_hwsem_arr[i], nu_hwsem_arr[i].name);
        rt_hw_interrupt_umask(nu_hwsem_arr[i].irqn);

        ret = hwsem_register(&nu_hwsem_arr[i].dev, (const char *)nu_hwsem_arr[i].name, (void *)&nu_hwsem_arr[i]);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_hwsem_init);

#endif //#if defined(BSP_USING_UART)
