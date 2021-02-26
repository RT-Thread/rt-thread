
/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-29     WangQiang    the first version
 *
 */

#include <rtthread.h>

#ifdef BSP_USING_PHY

#define LOG_TAG "drv.mdio"
#include <drv_log.h>

#include <rtdevice.h>
#include "drv_mdio.h"



/*! @brief Defines the timeout macro. */
#define PHY_TIMEOUT_COUNT 0x3FFFFFFU

/*!
 * @brief Get the ENET instance from peripheral base address.
 *
 * @param base ENET peripheral base address.
 * @return ENET instance.
 */
extern uint32_t ENET_GetInstance(ENET_Type *base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to enet clocks for each instance. */
extern clock_ip_name_t s_enetClock[FSL_FEATURE_SOC_ENET_COUNT];
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

static rt_bool_t rt_hw_mdio_init(void *bus, rt_uint32_t src_clock_hz)
{
    struct rt_mdio_bus *bus_obj = (struct rt_mdio_bus *)bus;
    uint32_t instance = ENET_GetInstance((ENET_Type *)(bus_obj->hw_obj));
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Set SMI first. */
    CLOCK_EnableClock(s_enetClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    ENET_SetSMI((ENET_Type *)(bus_obj->hw_obj), src_clock_hz, RT_FALSE);

    return RT_TRUE;
}

static rt_size_t rt_hw_mdio_read(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size)
{
    RT_ASSERT(data);
    struct rt_mdio_bus *bus_obj = (struct rt_mdio_bus *)bus;

    rt_uint32_t counter;
    rt_uint32_t *data_ptr = (rt_uint32_t *)data;

    if (4 != size)
    {
        return 0;
    }

    /* Clear the MII interrupt event. */
    ENET_ClearInterruptStatus((ENET_Type *)(bus_obj->hw_obj), ENET_EIR_MII_MASK);

    /* Starts a SMI read command operation. */
    ENET_StartSMIRead((ENET_Type *)(bus_obj->hw_obj), addr, reg, kENET_MiiReadValidFrame);

    /* Wait for MII complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--)
    {
        if (ENET_GetInterruptStatus((ENET_Type *)(bus_obj->hw_obj)) & ENET_EIR_MII_MASK)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter)
    {
        // return kStatus_PHY_SMIVisitTimeout;
        return 0;
    }

    /* Get data from MII register. */
    *data_ptr = ENET_ReadSMIData((ENET_Type *)(bus_obj->hw_obj));

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus((ENET_Type *)bus_obj->hw_obj, ENET_EIR_MII_MASK);

    return 4;
}


static rt_size_t rt_hw_mdio_write(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size)
{
    struct rt_mdio_bus *bus_obj = (struct rt_mdio_bus *)bus;
    uint32_t counter;
    rt_uint32_t *data_ptr = (rt_uint32_t *)data;

    if (4 != size)
    {
        return 0;
    }

    /* Clear the SMI interrupt event. */
    ENET_ClearInterruptStatus((ENET_Type *)(bus_obj->hw_obj), ENET_EIR_MII_MASK);

    /* Starts a SMI write command. */
    ENET_StartSMIWrite((ENET_Type *)(bus_obj->hw_obj), addr, reg, kENET_MiiWriteValidFrame, *data_ptr);

    /* Wait for SMI complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--)
    {
        if (ENET_GetInterruptStatus((ENET_Type *)(bus_obj->hw_obj)) & ENET_EIR_MII_MASK)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter)
    {
        return 0;
    }

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus((ENET_Type *)(bus_obj->hw_obj), ENET_EIR_MII_MASK);

    return size;
}

static struct rt_mdio_bus_ops imxrt_mdio_ops =
{
    .init = rt_hw_mdio_init,
    .read = rt_hw_mdio_read,
    .write = rt_hw_mdio_write,
    .uninit = RT_NULL,
};

static rt_mdio_t mdio_bus;

rt_mdio_t *rt_hw_mdio_register(void *hw_obj, char *name)
{
    mdio_bus.hw_obj = hw_obj;
    mdio_bus.name = name;
    mdio_bus.ops = &imxrt_mdio_ops;
    return &mdio_bus;
}

rt_mdio_t *rt_hw_mdio_get(void)
{
    return &mdio_bus;
}

#endif
