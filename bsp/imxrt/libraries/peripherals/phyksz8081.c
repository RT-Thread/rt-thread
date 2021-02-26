/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-14     wangqiang    the first version
 */

#include <rtthread.h>

#ifdef PHY_USING_KSZ8081

#include <rtdevice.h>
#include "drv_gpio.h"
#include "drv_mdio.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the PHY registers. */
#define PHY_BASICCONTROL_REG 0x00U      /*!< The PHY basic control register. */
#define PHY_BASICSTATUS_REG 0x01U       /*!< The PHY basic status register. */
#define PHY_ID1_REG 0x02U               /*!< The PHY ID one register. */
#define PHY_ID2_REG 0x03U               /*!< The PHY ID two register. */
#define PHY_AUTONEG_ADVERTISE_REG 0x04U /*!< The PHY auto-negotiate advertise register. */
#define PHY_CONTROL1_REG 0x1EU          /*!< The PHY control one register. */
#define PHY_CONTROL2_REG 0x1FU          /*!< The PHY control two register. */

#define PHY_CONTROL_ID1 0x22U /*!< The PHY ID1*/

/*! @brief Defines the mask flag in basic control register. */
#define PHY_BCTL_DUPLEX_MASK 0x0100U          /*!< The PHY duplex bit mask. */
#define PHY_BCTL_RESTART_AUTONEG_MASK 0x0200U /*!< The PHY restart auto negotiation mask. */
#define PHY_BCTL_AUTONEG_MASK 0x1000U         /*!< The PHY auto negotiation bit mask. */
#define PHY_BCTL_SPEED_MASK 0x2000U           /*!< The PHY speed bit mask. */
#define PHY_BCTL_LOOP_MASK 0x4000U            /*!< The PHY loop bit mask. */
#define PHY_BCTL_RESET_MASK 0x8000U           /*!< The PHY reset bit mask. */
#define PHY_BCTL_SPEED_100M_MASK 0x2000U      /*!< The PHY 100M speed mask. */

/*!@brief Defines the mask flag of operation mode in control two register*/
#define PHY_CTL2_REMOTELOOP_MASK 0x0004U    /*!< The PHY remote loopback mask. */
#define PHY_CTL2_REFCLK_SELECT_MASK 0x0080U /*!< The PHY RMII reference clock select. */
#define PHY_CTL1_10HALFDUPLEX_MASK 0x0001U  /*!< The PHY 10M half duplex mask. */
#define PHY_CTL1_100HALFDUPLEX_MASK 0x0002U /*!< The PHY 100M half duplex mask. */
#define PHY_CTL1_10FULLDUPLEX_MASK 0x0005U  /*!< The PHY 10M full duplex mask. */
#define PHY_CTL1_100FULLDUPLEX_MASK 0x0006U /*!< The PHY 100M full duplex mask. */
#define PHY_CTL1_SPEEDUPLX_MASK 0x0007U     /*!< The PHY speed and duplex mask. */
#define PHY_CTL1_ENERGYDETECT_MASK 0x10U    /*!< The PHY signal present on rx differential pair. */
#define PHY_CTL1_LINKUP_MASK 0x100U         /*!< The PHY link up. */
#define PHY_LINK_READY_MASK (PHY_CTL1_ENERGYDETECT_MASK | PHY_CTL1_LINKUP_MASK)

/*! @brief Defines the mask flag in basic status register. */
#define PHY_BSTATUS_LINKSTATUS_MASK 0x0004U  /*!< The PHY link status mask. */
#define PHY_BSTATUS_AUTONEGABLE_MASK 0x0008U /*!< The PHY auto-negotiation ability mask. */
#define PHY_BSTATUS_AUTONEGCOMP_MASK 0x0020U /*!< The PHY auto-negotiation complete mask. */

/*! @brief Defines the mask flag in PHY auto-negotiation advertise register. */
#define PHY_100BaseT4_ABILITY_MASK 0x200U    /*!< The PHY have the T4 ability. */
#define PHY_100BASETX_FULLDUPLEX_MASK 0x100U /*!< The PHY has the 100M full duplex ability.*/
#define PHY_100BASETX_HALFDUPLEX_MASK 0x080U /*!< The PHY has the 100M full duplex ability.*/
#define PHY_10BASETX_FULLDUPLEX_MASK 0x040U  /*!< The PHY has the 10M full duplex ability.*/
#define PHY_10BASETX_HALFDUPLEX_MASK 0x020U  /*!< The PHY has the 10M full duplex ability.*/



/*! @brief Defines the timeout macro. */
#define PHY_TIMEOUT_COUNT 0x3FFFFFFU

/* defined the Reset pin, PORT and PIN config by menuconfig */
#define RESET_PIN GET_PIN(PHY_RESET_PORT, PHY_RESET_PIN)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/
static struct rt_phy_device phy_ksz8081;

/*******************************************************************************
 * Code
 ******************************************************************************/



static inline rt_bool_t read_reg(rt_mdio_t *bus, rt_uint32_t addr, rt_uint32_t reg_id, rt_uint32_t *value)
{
    if (4 != bus->ops->read(bus, addr, reg_id, value, 4))
    {
        return RT_FALSE;
    }
    return RT_TRUE;
}

static inline rt_bool_t write_reg(rt_mdio_t *bus, rt_uint32_t addr, rt_uint32_t reg_id, rt_uint32_t value)
{
    if (4 != bus->ops->write(bus, addr, reg_id, &value, 4))
    {
        return RT_FALSE;
    }
    return RT_TRUE;
}

static rt_phy_status rt_phy_init(void *object, rt_uint32_t phy_addr, rt_uint32_t src_clock_hz)
{
    rt_bool_t ret;
    rt_phy_status result;
    rt_uint32_t counter = PHY_TIMEOUT_COUNT;
    rt_uint32_t id_reg = 0;
    rt_uint32_t time_delay;
    rt_uint32_t bss_reg;
    rt_uint32_t ctl_reg = 0;

    // reset phy device by gpio
    rt_pin_mode(RESET_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(RESET_PIN, PIN_LOW);
    rt_thread_mdelay(100);
    rt_pin_write(RESET_PIN, PIN_HIGH);

    rt_mdio_t *mdio_bus = rt_hw_mdio_register(object, "phy_mdio");
    if (RT_NULL == mdio_bus)
    {
        return PHY_STATUS_FAIL;
    }
    phy_ksz8081.bus = mdio_bus;
    phy_ksz8081.addr = phy_addr;
    ret = mdio_bus->ops->init(mdio_bus, src_clock_hz);
    if ( !ret )
    {
        return PHY_STATUS_FAIL;
    }

    /* Initialization after PHY stars to work. */
    while ((id_reg != PHY_CONTROL_ID1) && (counter != 0))
    {
        phy_ksz8081.ops->read(PHY_ID1_REG, &id_reg);
        counter--;
    }

    if (!counter)
    {
        return PHY_STATUS_FAIL;
    }

    /* Reset PHY. */
    counter = PHY_TIMEOUT_COUNT;
    result = phy_ksz8081.ops->write(PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (PHY_STATUS_OK == result)
    {
        #if defined(FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE)
        rt_uint32_t data = 0;
        result = phy_ksz8081.ops->read(PHY_CONTROL2_REG, &data);
        if (PHY_STATUS_FAIL == result)
        {
            return PHY_STATUS_FAIL;
        }
        result = phy_ksz8081.ops->write(PHY_CONTROL2_REG, (data | PHY_CTL2_REFCLK_SELECT_MASK));
        if (PHY_STATUS_FAIL == result)
        {
            return PHY_STATUS_FAIL;
        }
        #endif  /* FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE */

        /* Set the negotiation. */
        result = phy_ksz8081.ops->write(PHY_AUTONEG_ADVERTISE_REG, 
                                        (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                                        PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | 0x1U));
        if (PHY_STATUS_OK == result)
        {
            result = phy_ksz8081.ops->write(PHY_BASICCONTROL_REG, (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
            if (PHY_STATUS_OK == result)
            {
                /* Check auto negotiation complete. */
                while (counter--)
                {
                    result = phy_ksz8081.ops->read(PHY_BASICSTATUS_REG, &bss_reg);
                    if (PHY_STATUS_OK == result)
                    {
                        phy_ksz8081.ops->read(PHY_CONTROL1_REG, &ctl_reg);
                        if (((bss_reg & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0) && (ctl_reg & PHY_LINK_READY_MASK))
                        {
                            /* Wait a moment for Phy status stable. */
                            for (time_delay = 0; time_delay < PHY_TIMEOUT_COUNT; time_delay++)
                            {
                                __ASM("nop");
                            }
                            break;
                        }
                    }

                    if (!counter)
                    {
                        return PHY_STATUS_FAIL;
                    }
                }
            }
        }
    }

    return PHY_STATUS_OK;
}


static rt_phy_status rt_phy_read(rt_uint32_t reg, rt_uint32_t *data)
{
    rt_mdio_t *mdio_bus = phy_ksz8081.bus;
    rt_uint32_t device_id = phy_ksz8081.addr;

    if (read_reg(mdio_bus, device_id, reg, data))
    {
        return PHY_STATUS_OK;
    }
    return PHY_STATUS_FAIL;
}

static rt_phy_status rt_phy_write(rt_uint32_t reg, rt_uint32_t data)
{
    rt_mdio_t *mdio_bus = phy_ksz8081.bus;
    rt_uint32_t device_id = phy_ksz8081.addr;

    if (write_reg(mdio_bus, device_id, reg, data))
    {
        return PHY_STATUS_OK;
    }
    return PHY_STATUS_FAIL;
}

static rt_phy_status rt_phy_loopback(rt_uint32_t mode, rt_uint32_t speed, rt_bool_t enable)
{
    rt_uint32_t data = 0;
    rt_phy_status result;

    /* Set the loop mode. */
    if (enable)
    {
        if (PHY_LOCAL_LOOP == mode)
        {
            if (PHY_SPEED_100M == speed)
            {
                data = PHY_BCTL_SPEED_100M_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            else
            {
                data = PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            return phy_ksz8081.ops->write(PHY_BASICCONTROL_REG, data);
        }
        else
        {
            /* First read the current status in control register. */
            result = phy_ksz8081.ops->read(PHY_CONTROL2_REG, &data);
            if (PHY_STATUS_OK == result)
            {
                return phy_ksz8081.ops->write(PHY_CONTROL2_REG, (data | PHY_CTL2_REMOTELOOP_MASK));
            }
        }
    }
    else
    {
        /* Disable the loop mode. */
        if (PHY_LOCAL_LOOP == mode)
        {
            /* First read the current status in control register. */
            result = phy_ksz8081.ops->read(PHY_BASICCONTROL_REG, &data);
            if (PHY_STATUS_OK == result)
            {
                data &= ~PHY_BCTL_LOOP_MASK;
                return phy_ksz8081.ops->write(PHY_BASICCONTROL_REG, (data | PHY_BCTL_RESTART_AUTONEG_MASK));
            }
        }
        else
        {
            /* First read the current status in control one register. */
            result = phy_ksz8081.ops->read(PHY_CONTROL2_REG, &data);
            if (PHY_STATUS_OK == result)
            {
                return phy_ksz8081.ops->write(PHY_CONTROL2_REG, (data & ~PHY_CTL2_REMOTELOOP_MASK));
            }
        }
    }
    return result;
}

static rt_phy_status get_link_status(rt_bool_t *status)
{
    rt_phy_status result;
    rt_uint32_t data;

    /* Read the basic status register. */
    result = phy_ksz8081.ops->read(PHY_BASICSTATUS_REG, &data);
    if (PHY_STATUS_OK == result)
    {
        if (!(PHY_BSTATUS_LINKSTATUS_MASK & data))
        {
            /* link down. */
            *status = RT_FALSE;
        }
        else
        {
            /* link up. */
            *status = RT_TRUE;
        }
    }
    return result;
}
static rt_phy_status get_link_speed_duplex(rt_uint32_t *speed, rt_uint32_t *duplex)
{
    rt_phy_status result = PHY_STATUS_OK;
    rt_uint32_t data, ctl_reg;

    /* Read the control two register. */
    result = phy_ksz8081.ops->read(PHY_CONTROL1_REG, &ctl_reg);
    if (PHY_STATUS_OK == result)
    {
        data = ctl_reg & PHY_CTL1_SPEEDUPLX_MASK;
        if ((PHY_CTL1_10FULLDUPLEX_MASK == data) || (PHY_CTL1_100FULLDUPLEX_MASK == data))
        {
            /* Full duplex. */
            *duplex = PHY_FULL_DUPLEX;
        }
        else
        {
            /* Half duplex. */
            *duplex = PHY_HALF_DUPLEX;
        }

        data = ctl_reg & PHY_CTL1_SPEEDUPLX_MASK;
        if ((PHY_CTL1_100HALFDUPLEX_MASK == data) || (PHY_CTL1_100FULLDUPLEX_MASK == data))
        {
            /* 100M speed. */
            *speed = PHY_SPEED_100M;
        }
        else
        { /* 10M speed. */
            *speed = PHY_SPEED_10M;
        }
    }

    return result;
}

static struct rt_phy_ops phy_ops =
{
    .init = rt_phy_init,
    .read = rt_phy_read,
    .write = rt_phy_write,
    .loopback = rt_phy_loopback,
    .get_link_status = get_link_status,
    .get_link_speed_duplex = get_link_speed_duplex,
};

static int rt_phy_ksz8081_register( void )
{
    phy_ksz8081.ops = &phy_ops;
    rt_hw_phy_register(&phy_ksz8081, "rtt-phy");
    return 1;
}

INIT_DEVICE_EXPORT(rt_phy_ksz8081_register);



#endif /* PHY_USING_KSZ8081 */
