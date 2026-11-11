/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/12/23     Bernard      The first version
 * 2018/12/27     Jesven       Add secondary cpu boot
 * 2023/11/10     WangShun     Adapted to Xuantie C908MP
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <csi_core.h>
#include <soc.h>
#include <drv/tick.h>
#include <asm/riscv_csr.h>

enum
{
    CRXX_MP_CORE0 = 0,
    CRXX_MP_CORE1,
    CRXX_MP_CORE2,
    CRXX_MP_CORE3,
    CRXX_MP_CORE4,
    CRXX_MP_CORE5,
    CRXX_MP_CORE6,
    CRXX_MP_CORE7,
};

/**
 * @brief    This function is used to suspend a specified kernel software interrupt.
 *
 * @note     Calling this function will trigger inter core interrupts.
 *
 * @param    id is the ID of the specific physical core.
 *
 */
void clint_ipi_send(uint64_t id)
{
    CLINT_Type *clint = (CLINT_Type *)CORET_BASE;

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    switch (id)
    {
    case CRXX_MP_CORE0:
        clint->SSIP0 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE1:
        clint->SSIP1 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE2:
        clint->SSIP2 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE3:
        clint->SSIP3 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE4:
        clint->SSIP4 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE5:
        clint->SSIP5 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE6:
        clint->SSIP6 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE7:
        clint->SSIP7 |= (uint32_t)0x1;
        break;
    default:
        break;
    }
#else
    switch (id)
    {
    case CRXX_MP_CORE0:
        clint->MSIP0 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE1:
        clint->MSIP1 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE2:
        clint->MSIP2 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE3:
        clint->MSIP3 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE4:
        clint->MSIP4 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE5:
        clint->MSIP5 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE6:
        clint->MSIP6 |= (uint32_t)0x1;
        break;
    case CRXX_MP_CORE7:
        clint->MSIP7 |= (uint32_t)0x1;
        break;
    default:
        break;
    }
#endif
}

/**
 * @brief    This function is used to clear the specified kernel software interrupt.
 *
 * @note     Calling this function will clear the inter core interrupt suspend flag.
 *
 * @param    id is the ID of the specific physical core.
 *
 */
void clint_ipi_clear(uint64_t id)
{
    CLINT_Type *clint = (CLINT_Type *)CORET_BASE;

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    switch (id)
    {
    case CRXX_MP_CORE0:
        clint->SSIP0 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE1:
        clint->SSIP1 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE2:
        clint->SSIP2 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE3:
        clint->SSIP3 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE4:
        clint->SSIP4 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE5:
        clint->SSIP5 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE6:
        clint->SSIP6 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE7:
        clint->SSIP7 &= ~(uint32_t)0x1;
        break;
    default:
        break;
    }
#else
    switch (id)
    {
    case CRXX_MP_CORE0:
        clint->MSIP0 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE1:
        clint->MSIP1 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE2:
        clint->MSIP2 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE3:
        clint->MSIP3 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE4:
        clint->MSIP4 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE5:
        clint->MSIP5 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE6:
        clint->MSIP6 &= ~(uint32_t)0x1;
        break;
    case CRXX_MP_CORE7:
        clint->MSIP7 &= ~(uint32_t)0x1;
        break;
    default:
        break;
    }
#endif
}

/**
 * @brief    This function is used to configure timers for specific physical cores.
 *
 * @note     Calling this function will configure Heartbeat Time.
 *
 * @param    NULL.
 *
 */
int rt_hw_tick_init(void)
{
    int core_id = rt_hw_cpu_id();

    if (core_id == CRXX_MP_CORE0)
    {
        return 0;
    }
    csi_tick_init();
    return 0;
}

/**
 * @brief    This function is used to enable software interrupts for specific physical cores.
 *
 * @note     Calling this function will enable software interruption.
 *
 * @param    NULL.
 *
 */
int rt_hw_clint_ipi_enable(void)
{
    /* Set the Machine-Software bit in MIE */
    rv_csr_set(0x304, SR_MIE);
    return 0;
}

/**
 * @brief    This function is used to initialize the interrupt management function unique to the physical core.
 *
 * @note     Calling this function will close the specific core external interrupt and set the trigger threshold to 0.
 *
 * @param    NULL.
 *
 */
void rt_hw_scondary_interrupt_init(void)
{
    int i;
    int core_id = 0;
    core_id = rt_hw_cpu_id();

    if (core_id == CRXX_MP_CORE0)
    {
        return;
    }
    else if (core_id == CRXX_MP_CORE1)
    {
        for (i = 0; i < (CONFIG_IRQ_NUM + 31) / 32; i++)
        {
            PLIC->PLIC_H1_MIE[i] = 0;
            PLIC->PLIC_H1_SIE[i] = 0;
        }

        /* set hart threshold 0, enable all interrupt */
        PLIC->PLIC_H1_MTH = 0;
        PLIC->PLIC_H1_STH = 0;
    }
    else if (core_id == CRXX_MP_CORE2)
    {
        for (i = 0; i < (CONFIG_IRQ_NUM + 31) / 32; i++)
        {
            PLIC->PLIC_H2_MIE[i] = 0;
            PLIC->PLIC_H2_SIE[i] = 0;
        }

        /* set hart threshold 0, enable all interrupt */
        PLIC->PLIC_H2_MTH = 0;
        PLIC->PLIC_H2_STH = 0;
    }
    else if (core_id == CRXX_MP_CORE3)
    {
        for (i = 0; i < (CONFIG_IRQ_NUM + 31) / 32; i++)
        {
            PLIC->PLIC_H3_MIE[i] = 0;
            PLIC->PLIC_H3_SIE[i] = 0;
        }

        /* set hart threshold 0, enable all interrupt */
        PLIC->PLIC_H3_MTH = 0;
        PLIC->PLIC_H3_STH = 0;
    }
    else if (core_id == CRXX_MP_CORE4)
    {
        for (i = 0; i < (CONFIG_IRQ_NUM + 31) / 32; i++)
        {
            PLIC->PLIC_H4_MIE[i] = 0;
            PLIC->PLIC_H4_SIE[i] = 0;
        }

        /* set hart threshold 0, enable all interrupt */
        PLIC->PLIC_H4_MTH = 0;
        PLIC->PLIC_H4_STH = 0;
    }
    else if (core_id == CRXX_MP_CORE5)
    {
        for (i = 0; i < (CONFIG_IRQ_NUM + 31) / 32; i++)
        {
            PLIC->PLIC_H5_MIE[i] = 0;
            PLIC->PLIC_H5_SIE[i] = 0;
        }

        /* set hart threshold 0, enable all interrupt */
        PLIC->PLIC_H5_MTH = 0;
        PLIC->PLIC_H5_STH = 0;
    }
    else if (core_id == CRXX_MP_CORE6)
    {
        for (i = 0; i < (CONFIG_IRQ_NUM + 31) / 32; i++)
        {
            PLIC->PLIC_H6_MIE[i] = 0;
            PLIC->PLIC_H6_SIE[i] = 0;
        }

        /* set hart threshold 0, enable all interrupt */
        PLIC->PLIC_H6_MTH = 0;
        PLIC->PLIC_H6_STH = 0;
    }
    else if (core_id == CRXX_MP_CORE7)
    {
        for (i = 0; i < (CONFIG_IRQ_NUM + 31) / 32; i++)
        {
            PLIC->PLIC_H7_MIE[i] = 0;
            PLIC->PLIC_H7_SIE[i] = 0;
        }

        /* set hart threshold 0, enable all interrupt */
        PLIC->PLIC_H7_MTH = 0;
        PLIC->PLIC_H7_STH = 0;
    }
    else
    {
        rt_kprintf("Illegal CPU core, ID = %d", core_id);
        while (1)
            ;
    }

    /* enable MEIE & MSIE */
    uint32_t mie = __get_MIE();
    mie |= (1 << 11 | 1 << 7 | 1 << 3);
#if CONFIG_ECC_L1_ENABLE
    mie |= (1 << 16);
#endif
    __set_MIE(mie);
}

/**
 * @brief    Software interrupt handling function.
 *
 * @note     This function is used to respond to inter core interrupts.
 *
 * @param    NULL.
 *
 */
void ipi_irq(void)
{
    int core_id = 0;
    core_id = rt_hw_cpu_id();
    clint_ipi_clear(core_id);
    rt_schedule();
}
