/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-15     xjy198903    the first version
 * 2024-04-18     Jiading      add a parameter passed into rt_phy_ops APIs
 */
#include <rtthread.h>

#ifdef PHY_USING_RTL8211F

#include <rtdevice.h>
#include "drv_gpio.h"
#include "drv_mdio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @note The following PHY registers are the IEEE802.3 standard definition, same register and bit field may
          have different names in various PHYs, but the feature they represent should be same or very similar. */

/*! @brief Defines the IEEE802.3 standard PHY registers. */
#define PHY_BASICCONTROL_REG 0x00U        /*!< The PHY basic control register. */
#define PHY_BASICSTATUS_REG 0x01U         /*!< The PHY basic status register. */
#define PHY_ID1_REG 0x02U                 /*!< The PHY ID one register. */
#define PHY_ID2_REG 0x03U                 /*!< The PHY ID two register. */
#define PHY_AUTONEG_ADVERTISE_REG 0x04U   /*!< The PHY auto-negotiate advertise register. */
#define PHY_AUTONEG_LINKPARTNER_REG 0x05U /*!< The PHY auto negotiation link partner ability register. */
#define PHY_AUTONEG_EXPANSION_REG 0x06U   /*!< The PHY auto negotiation expansion register. */
#define PHY_1000BASET_CONTROL_REG 0x09U   /*!< The PHY 1000BASE-T control register. */
#define PHY_MMD_ACCESS_CONTROL_REG 0x0DU  /*!< The PHY MMD access control register. */
#define PHY_MMD_ACCESS_DATA_REG 0x0EU     /*!< The PHY MMD access data register. */

/*! @brief Defines the mask flag in basic control register(Address 0x00). */
#define PHY_BCTL_SPEED1_MASK 0x0040U          /*!< The PHY speed bit mask(MSB).*/
#define PHY_BCTL_ISOLATE_MASK 0x0400U         /*!< The PHY isolate mask.*/
#define PHY_BCTL_DUPLEX_MASK 0x0100U          /*!< The PHY duplex bit mask. */
#define PHY_BCTL_RESTART_AUTONEG_MASK 0x0200U /*!< The PHY restart auto negotiation mask. */
#define PHY_BCTL_AUTONEG_MASK 0x1000U         /*!< The PHY auto negotiation bit mask. */
#define PHY_BCTL_SPEED0_MASK 0x2000U          /*!< The PHY speed bit mask(LSB). */
#define PHY_BCTL_LOOP_MASK 0x4000U            /*!< The PHY loop bit mask. */
#define PHY_BCTL_RESET_MASK 0x8000U           /*!< The PHY reset bit mask. */

/*! @brief Defines the mask flag in basic status register(Address 0x01). */
#define PHY_BSTATUS_LINKSTATUS_MASK 0x0004U  /*!< The PHY link status mask. */
#define PHY_BSTATUS_AUTONEGABLE_MASK 0x0008U /*!< The PHY auto-negotiation ability mask. */
#define PHY_BSTATUS_SPEEDUPLX_MASK 0x001CU   /*!< The PHY speed and duplex mask. */
#define PHY_BSTATUS_AUTONEGCOMP_MASK 0x0020U /*!< The PHY auto-negotiation complete mask. */

/*! @brief Defines the mask flag in PHY auto-negotiation advertise register(Address 0x04). */
#define PHY_100BaseT4_ABILITY_MASK 0x200U    /*!< The PHY have the T4 ability. */
#define PHY_100BASETX_FULLDUPLEX_MASK 0x100U /*!< The PHY has the 100M full duplex ability.*/
#define PHY_100BASETX_HALFDUPLEX_MASK 0x080U /*!< The PHY has the 100M full duplex ability.*/
#define PHY_10BASETX_FULLDUPLEX_MASK 0x040U  /*!< The PHY has the 10M full duplex ability.*/
#define PHY_10BASETX_HALFDUPLEX_MASK 0x020U  /*!< The PHY has the 10M full duplex ability.*/
#define PHY_IEEE802_3_SELECTOR_MASK 0x001U   /*!< The message type being sent by Auto-Nego.*/

/*! @brief Defines the mask flag in the 1000BASE-T control register(Address 0x09). */
#define PHY_1000BASET_FULLDUPLEX_MASK 0x200U /*!< The PHY has the 1000M full duplex ability.*/
#define PHY_1000BASET_HALFDUPLEX_MASK 0x100U /*!< The PHY has the 1000M half duplex ability.*/

/*! @brief Defines the PHY RTL8211F vendor defined registers. */
#define PHY_SPECIFIC_STATUS_REG 0x1AU /*!< The PHY specific status register. */
#define PHY_PAGE_SELECT_REG 0x1FU     /*!< The PHY page select register. */

/*! @brief Defines the PHY RTL8211F ID number. */
#define PHY_CONTROL_ID1 0x001CU /*!< The PHY ID1 . */

/*! @brief Defines the mask flag in specific status register. */
#define PHY_SSTATUS_LINKSTATUS_MASK 0x04U /*!< The PHY link status mask. */
#define PHY_SSTATUS_LINKSPEED_MASK 0x30U  /*!< The PHY link speed mask. */
#define PHY_SSTATUS_LINKDUPLEX_MASK 0x08U /*!< The PHY link duplex mask. */
#define PHY_SSTATUS_LINKSPEED_SHIFT 4U    /*!< The link speed shift */

/*! @brief Defines the PHY RTL8211F extra page and the registers in specified page. */
#define PHY_PAGE_RGMII_TXRX_DELAY_ADDR 0xD08U /*!< The register page including RGMII TX/RX delay setting. */
#define PHY_RGMII_TX_DELAY_REG 0x11U          /*!< The RGMII TXC delay register. */
#define PHY_RGMII_RX_DELAY_REG 0x15U          /*!< The RGMII RXC delay register. */
#define PHY_RGMII_TX_DELAY_MASK 0x100U        /*!< The RGMII TXC delay mask. */
#define PHY_RGMII_RX_DELAY_MASK 0x8U          /*!< The RGMII RXC delay mask. */

/*! @brief MDIO MMD Devices .*/
#define PHY_MDIO_MMD_PCS 3U
#define PHY_MDIO_MMD_AN 7U

/*! @brief MDIO MMD Physical Coding layer device registers .*/
#define PHY_MDIO_PCS_EEE_CAP 0x14U /* EEE capability */

/*! @brief MDIO MMD AutoNegotiation device registers .*/
#define PHY_MDIO_AN_EEE_ADV 0x3CU /* EEE advertisement */

/*! @brief MDIO MMD EEE mask flags. (common for adv and cap) */
#define PHY_MDIO_EEE_100TX 0x2U
#define PHY_MDIO_EEE_1000T 0x4U

/*! @brief Defines the timeout macro. */
#define PHY_READID_TIMEOUT_COUNT 1000U

/* defined the Reset pin, PORT and PIN config by menuconfig */
#define RESET_PIN GET_PIN(PHY_RESET_RTL8211F_PORT, PHY_RESET_RTL8211F_PIN)

/*! @brief Defines the PHY MMD data access mode. */
typedef enum _phy_mmd_access_mode
{
    kPHY_MMDAccessNoPostIncrement = (1U << 14), /*!< ENET PHY MMD access data with no address post increment. */
    kPHY_MMDAccessRdWrPostIncrement =
        (2U << 14),                             /*!< ENET PHY MMD access data with Read/Write address post increment. */
    kPHY_MMDAccessWrPostIncrement = (3U << 14), /*!< ENET PHY MMD access data with Write address post increment. */
} phy_mmd_access_mode_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static struct rt_phy_device phy_rtl8211f;

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

static inline status_t PHY_RTL8211F_MMD_WriteData(uint32_t data)
{
    return phy_rtl8211f.ops->write(PHY_MMD_ACCESS_DATA_REG, data);
}

static status_t PHY_RTL8211F_MMD_SetDevice(uint8_t device,
                                           uint16_t addr,
                                           phy_mmd_access_mode_t mode)
{
    status_t result = PHY_STATUS_OK;

    /* Set Function mode of address access(b00) and device address. */
    result = phy_rtl8211f.ops->write(PHY_MMD_ACCESS_CONTROL_REG, device);
    if (result != PHY_STATUS_OK)
    {
        return result;
    }

    /* Set register address. */
    result = phy_rtl8211f.ops->write(PHY_MMD_ACCESS_DATA_REG, addr);
    if (result != PHY_STATUS_OK)
    {
        return result;
    }

    /* Set Function mode of data access(b01~11) and device address. */
    result = phy_rtl8211f.ops->write(PHY_MMD_ACCESS_CONTROL_REG, (uint32_t)mode | (uint32_t)device);
    return result;
}

static status_t PHY_RTL8211F_MMD_Write(uint8_t device, uint16_t addr, uint32_t data)
{
    status_t result = PHY_STATUS_OK;

    result = PHY_RTL8211F_MMD_SetDevice(device, addr, kPHY_MMDAccessNoPostIncrement);
    if (result == PHY_STATUS_OK)
    {
        result = PHY_RTL8211F_MMD_WriteData(data);
    }
    return result;
}

static rt_phy_status rt_phy_init(void *object, rt_uint32_t phy_addr, rt_uint32_t src_clock_hz)
{
    rt_bool_t ret;
    rt_phy_status result;
    rt_uint32_t counter = PHY_READID_TIMEOUT_COUNT;
    rt_uint32_t regValue = 0U;

    // reset phy device by gpio
    rt_pin_mode(RESET_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(RESET_PIN, PIN_LOW);
    rt_thread_mdelay(10);
    rt_pin_write(RESET_PIN, PIN_HIGH);
    rt_thread_mdelay(30);

    rt_mdio_t *mdio_bus = rt_hw_mdio_register(object, "phy_mdio");
    if (RT_NULL == mdio_bus)
    {
        return PHY_STATUS_FAIL;
    }
    phy_rtl8211f.bus = mdio_bus;
    phy_rtl8211f.addr = phy_addr;
    ret = mdio_bus->ops->init(mdio_bus, src_clock_hz);
    if (!ret)
    {
        return PHY_STATUS_FAIL;
    }

    /* Check PHY ID. */
    do
    {
        result = phy_rtl8211f.ops->read(NULL, PHY_ID1_REG, &regValue);
        if (result != PHY_STATUS_OK)
        {
            return result;
        }
        counter--;
    } while ((regValue != PHY_CONTROL_ID1) && (counter != 0U));

    if (counter == 0U)
    {
        return PHY_STATUS_FAIL;
    }

    /* Reset PHY. */
    result = phy_rtl8211f.ops->write(PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result != PHY_STATUS_OK)
    {
        return result;
    }

    /* The RGMII specifies output TXC/RXC and TXD/RXD without any clock skew. Need to add skew on clock line
       to make sure the other side sample right data. This can also be done in PCB traces. */
    result = phy_rtl8211f.ops->write(PHY_PAGE_SELECT_REG, PHY_PAGE_RGMII_TXRX_DELAY_ADDR);
    if (PHY_STATUS_OK != result)
    {
        return result;
    }

    /* Set Tx Delay */
    result = phy_rtl8211f.ops->read(NULL, PHY_RGMII_TX_DELAY_REG, &regValue);
    if (PHY_STATUS_OK == result)
    {
        regValue |= PHY_RGMII_TX_DELAY_MASK;
        result = phy_rtl8211f.ops->write(PHY_RGMII_TX_DELAY_REG, regValue);
        if (result != PHY_STATUS_OK)
        {
            return result;
        }
    }
    else
    {
        return result;
    }

    /* Set Rx Delay */
    result = phy_rtl8211f.ops->read(NULL, PHY_RGMII_RX_DELAY_REG, &regValue);
    if (PHY_STATUS_OK == result)
    {
        regValue |= PHY_RGMII_RX_DELAY_MASK;
        result = phy_rtl8211f.ops->write(PHY_RGMII_RX_DELAY_REG, regValue);
        if (result != PHY_STATUS_OK)
        {
            return result;
        }
    }
    else
    {
        return result;
    }

    /* Restore to default page 0 */
    result = phy_rtl8211f.ops->write(PHY_PAGE_SELECT_REG, 0x0);
    if (result != PHY_STATUS_OK)
    {
        return result;
    }

    // disabled EEE
    result = PHY_RTL8211F_MMD_Write(PHY_MDIO_MMD_AN, PHY_MDIO_AN_EEE_ADV, 0);
    if (result != PHY_STATUS_OK)
    {
        return result;
    }

    /* Set the auto-negotiation. */
    result = phy_rtl8211f.ops->write(PHY_AUTONEG_ADVERTISE_REG,
                                     PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK | PHY_10BASETX_FULLDUPLEX_MASK |
                                         PHY_10BASETX_HALFDUPLEX_MASK | PHY_IEEE802_3_SELECTOR_MASK);
    if (result == PHY_STATUS_OK)
    {
        result = phy_rtl8211f.ops->write(PHY_1000BASET_CONTROL_REG, PHY_1000BASET_FULLDUPLEX_MASK);
        if (result == PHY_STATUS_OK)
        {
            result = phy_rtl8211f.ops->read(NULL, PHY_BASICCONTROL_REG, &regValue);
            if (result == PHY_STATUS_OK)
            {
                result = phy_rtl8211f.ops->write(PHY_BASICCONTROL_REG, (regValue | PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
            }
        }
    }

    return result;
}

static rt_phy_status rt_phy_read(rt_phy_t *phy, rt_uint32_t reg, rt_uint32_t *data)
{
    rt_mdio_t *mdio_bus = phy_rtl8211f.bus;
    rt_uint32_t device_id = phy_rtl8211f.addr;

    if (read_reg(mdio_bus, device_id, reg, data))
    {
        return PHY_STATUS_OK;
    }
    return PHY_STATUS_FAIL;
}

static rt_phy_status rt_phy_write(rt_phy_t *phy, rt_uint32_t reg, rt_uint32_t data)
{
    rt_mdio_t *mdio_bus = phy_rtl8211f.bus;
    rt_uint32_t device_id = phy_rtl8211f.addr;

    if (write_reg(mdio_bus, device_id, reg, data))
    {
        return PHY_STATUS_OK;
    }
    return PHY_STATUS_FAIL;
}

static rt_phy_status rt_phy_loopback(rt_phy_t *phy, rt_uint32_t mode, rt_uint32_t speed, rt_bool_t enable)
{
    /* This PHY only supports local loopback. */
    //    rt_assert(mode == PHY_LOCAL_LOOP);

    status_t result;
    uint32_t regValue;

    /* Set the loop mode. */
    if (enable)
    {
        if (speed == PHY_SPEED_1000M)
        {
            regValue = PHY_BCTL_SPEED1_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
        }
        else if (speed == PHY_SPEED_100M)
        {
            regValue = PHY_BCTL_SPEED0_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
        }
        else
        {
            regValue = PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
        }
        result = phy_rtl8211f.ops->write(PHY_BASICCONTROL_REG, regValue);
    }
    else
    {
        /* First read the current status in control register. */
        result = phy_rtl8211f.ops->read(NULL, PHY_BASICCONTROL_REG, &regValue);
        if (result == PHY_STATUS_OK)
        {
            regValue &= ~PHY_BCTL_LOOP_MASK;
            result = phy_rtl8211f.ops->write(PHY_BASICCONTROL_REG, (regValue | PHY_BCTL_RESTART_AUTONEG_MASK));
        }
    }
    return result;
}

static rt_phy_status get_link_status(rt_phy_t *phy, rt_bool_t *status)
{
    // assert(status);

    status_t result;
    uint32_t regValue;

    /* Read the basic status register. */
    result = phy_rtl8211f.ops->read(PHY_SPECIFIC_STATUS_REG, &regValue);
    if (result == PHY_STATUS_OK)
    {
        if ((PHY_SSTATUS_LINKSTATUS_MASK & regValue) != 0U)
        {
            /* Link up. */
            *status = true;
        }
        else
        {
            /* Link down. */
            *status = false;
        }
    }
    return result;
}

static rt_phy_status get_link_speed_duplex(rt_phy_t *phy, rt_uint32_t *speed, rt_uint32_t *duplex)
{
    // assert(!((speed == NULL) && (duplex == NULL)));

    status_t result;
    uint32_t regValue;

    /* Read the status register. */
    result = phy_rtl8211f.ops->read(NULL, PHY_SPECIFIC_STATUS_REG, &regValue);
    if (result == PHY_STATUS_OK)
    {
        if (speed != NULL)
        {
            switch ((regValue & PHY_SSTATUS_LINKSPEED_MASK) >> PHY_SSTATUS_LINKSPEED_SHIFT)
            {
            case (uint32_t)PHY_SPEED_10M:
                *speed = PHY_SPEED_10M;
                break;
            case (uint32_t)PHY_SPEED_100M:
                *speed = PHY_SPEED_100M;
                break;
            case (uint32_t)PHY_SPEED_1000M:
                *speed = PHY_SPEED_1000M;
                break;
            default:
                *speed = PHY_SPEED_10M;
                break;
            }
        }

        if (duplex != NULL)
        {
            if ((regValue & PHY_SSTATUS_LINKDUPLEX_MASK) != 0U)
            {
                *duplex = PHY_FULL_DUPLEX;
            }
            else
            {
                *duplex = PHY_HALF_DUPLEX;
            }
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

static int rt_phy_rtl8211f_register(void)
{
    phy_rtl8211f.ops = &phy_ops;
    rt_hw_phy_register(&phy_rtl8211f, "rtl8211f");
    return 1;
}

INIT_DEVICE_EXPORT(rt_phy_rtl8211f_register);
#endif /* PHY_USING_RTL8211F */
