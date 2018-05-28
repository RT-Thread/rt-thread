/*
 * File      : nuc97x_mfp.c
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "nuc97x_conf.h"


void mfp_set_port_a(uint32_t pin, uint32_t func)
{
    if (pin < 8)
    {
        pin *= 4;
        writel((readl(REG_SYS_GPA_MFPL) & ~(0xF << pin)) | (func << pin), REG_SYS_GPA_MFPL);
    }
    else
    {
        pin = (pin - 8) * 4;
        writel((readl(REG_SYS_GPA_MFPH) & ~(0xF << pin)) | (func << pin), REG_SYS_GPA_MFPH);
    }
}

void mfp_set_port_b(uint32_t pin, uint32_t func)
{
    if (pin < 8)
    {
        pin *= 4;
        writel((readl(REG_SYS_GPB_MFPL) & ~(0xF << pin)) | (func << pin), REG_SYS_GPB_MFPL);
    }
    else
    {
        pin = (pin - 8) * 4;
        writel((readl(REG_SYS_GPB_MFPH) & ~(0xF << pin)) | (func << pin), REG_SYS_GPB_MFPH);
    }
}

void mfp_set_port_c(uint32_t pin, uint32_t func)
{
    if (pin < 8)
    {
        pin *= 4;
        writel((readl(REG_SYS_GPC_MFPL) & ~(0xF << pin)) | (func << pin), REG_SYS_GPC_MFPL);
    }
    else
    {
        pin = (pin - 8) * 4;
        writel((readl(REG_SYS_GPC_MFPH) & ~(0xF << pin)) | (func << pin), REG_SYS_GPC_MFPH);
    }
}

void mfp_set_port_d(uint32_t pin, uint32_t func)
{
    if (pin < 8)
    {
        pin *= 4;
        writel((readl(REG_SYS_GPD_MFPL) & ~(0xF << pin)) | (func << pin), REG_SYS_GPD_MFPL);
    }
    else
    {
        pin = (pin - 8) * 4;
        writel((readl(REG_SYS_GPD_MFPH) & ~(0xF << pin)) | (func << pin), REG_SYS_GPD_MFPH);
    }
}

void mfp_set_port_e(uint32_t pin, uint32_t func)
{
    if (pin < 8)
    {
        pin *= 4;
        writel((readl(REG_SYS_GPE_MFPL) & ~(0xF << pin)) | (func << pin), REG_SYS_GPE_MFPL);
    }
    else
    {
        pin = (pin - 8) * 4;
        writel((readl(REG_SYS_GPE_MFPH) & ~(0xF << pin)) | (func << pin), REG_SYS_GPE_MFPH);
    }
}

void mfp_set_port_f(uint32_t pin, uint32_t func)
{
    if (pin < 8)
    {
        pin *= 4;
        writel((readl(REG_SYS_GPF_MFPL) & ~(0xF << pin)) | (func << pin), REG_SYS_GPF_MFPL);
    }
    else
    {
        pin = (pin - 8) * 4;
        writel((readl(REG_SYS_GPF_MFPH) & ~(0xF << pin)) | (func << pin), REG_SYS_GPF_MFPH);
    }
}

void mfp_set_port_g(uint32_t pin, uint32_t func)
{
    if (pin < 8)
    {
        pin *= 4;
        writel((readl(REG_SYS_GPG_MFPL) & ~(0xF << pin)) | (func << pin), REG_SYS_GPG_MFPL);
    }
    else
    {
        pin = (pin - 8) * 4;
        writel((readl(REG_SYS_GPG_MFPH) & ~(0xF << pin)) | (func << pin), REG_SYS_GPG_MFPH);
    }
}

void mfp_set_port_h(uint32_t pin, uint32_t func)
{
    if (pin < 8)
    {
        pin *= 4;
        writel((readl(REG_SYS_GPH_MFPL) & ~(0xF << pin)) | (func << pin), REG_SYS_GPH_MFPL);
    }
    else
    {
        pin = (pin - 8) * 4;
        writel((readl(REG_SYS_GPH_MFPH) & ~(0xF << pin)) | (func << pin), REG_SYS_GPH_MFPH);
    }
}

void mfp_set_port_i(uint32_t pin, uint32_t func)
{
    if (pin < 8)
    {
        pin *= 4;
        writel((readl(REG_SYS_GPI_MFPL) & ~(0xF << pin)) | (func << pin), REG_SYS_GPI_MFPL);
    }
    else
    {
        pin = (pin - 8) * 4;
        writel((readl(REG_SYS_GPI_MFPH) & ~(0xF << pin)) | (func << pin), REG_SYS_GPI_MFPH);
    }
}
