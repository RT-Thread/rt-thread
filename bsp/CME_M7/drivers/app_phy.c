#include <stdio.h>
#include "app_phy.h"

#define PHY_BASE_ADDR                           0x7

#define PHY_REG_CONTROL             0x0
#define PHY_REG_STATUS              0x1
#define PHY_REG_ANE                 0x6
#define PHY_REG_SPEC_STATUS         0x11
#define PHY_REG_EXTEND_STATUS               0x1B

#define PHY_BIT_CONTROL_RESET           0x8000          /*!< Control reg : reset */
#define PHY_BIT_CONTROL_ANEN            0x1000          /*!< Control reg : auto-negotiation enable */
#define PHY_BIT_CONTROL_RSAN            0x0200          /*!< Control reg : auto-negotiation restart */

#define PHY_BIT_STATUS_ANC              0x0020          /*!< Status reg : auto-negotiation complete */
#define PHY_BIT_STATUS_LINK             0x0004          /*!< Status reg : link is up */

#define PHY_BIT_ANE_LPAN                0x0001          /*!< ANE reg : link partner can auto-neg */

#define PHY_BIT_SPEED                   0xC000      /*!< specific status reg : speed */
#define PHY_BIT_DUPLEX                  0x2000      /*!< specific status reg : duplex */

#define PHY_BIT_AUTO_MEDIA_DISABLE      0x8000      /*!< extended status reg : auto media select disable */
#define PHY_BIT_AUTO_MEDIA_REG_DISABLE  0x0200      /*!< extended status reg : auto media register select disable */

void phy_Reset() {
    ETH_PhyWrite(PHY_BASE_ADDR, PHY_REG_CONTROL, PHY_BIT_CONTROL_RESET);

    while (1) {
        uint32_t ret = ETH_PhyRead(PHY_BASE_ADDR, PHY_REG_CONTROL);
      if ((ret & PHY_BIT_CONTROL_RESET) == 0) {
            break;
        }
    }
}

void phy_AutoMediaSelect() {
    uint32_t data;

    // auto media and auto media register selection
    data = ETH_PhyRead(PHY_BASE_ADDR, PHY_REG_EXTEND_STATUS);
    data &= ~PHY_BIT_AUTO_MEDIA_DISABLE;
    data &= ~PHY_BIT_AUTO_MEDIA_REG_DISABLE;
    ETH_PhyWrite(PHY_BASE_ADDR, PHY_REG_EXTEND_STATUS, data);
}

void phy_AutoNeg()
{
    uint32_t data;

    data = ETH_PhyRead(PHY_BASE_ADDR, PHY_REG_CONTROL);
    data |= (PHY_BIT_CONTROL_ANEN | PHY_BIT_CONTROL_RSAN);
    ETH_PhyWrite(PHY_BASE_ADDR, PHY_REG_CONTROL, data);

    while (1)
    {
        uint32_t ret = ETH_PhyRead(PHY_BASE_ADDR, PHY_REG_STATUS);
        if ((ret & PHY_BIT_STATUS_ANC) == PHY_BIT_STATUS_ANC)
        {
            break;
        }
        rt_thread_delay(1);
    }
}

BOOL phy_IsLink() {
    uint32_t ret = ETH_PhyRead(PHY_BASE_ADDR, PHY_REG_STATUS);
    return (ret & PHY_BIT_STATUS_LINK) ? TRUE : FALSE;
}

BOOL phy_PartnerCanAutoNeg() {
    uint32_t ret = ETH_PhyRead(PHY_BASE_ADDR, PHY_REG_ANE);
    return (ret & PHY_BIT_ANE_LPAN) ? TRUE : FALSE;
}

uint32_t phy_GetSpeed() {
    uint32_t ret = ETH_PhyRead(PHY_BASE_ADDR, PHY_REG_SPEC_STATUS);
    return ((ret & PHY_BIT_SPEED) >> 14);
}

uint32_t phy_GetDuplex() {
    uint32_t ret = ETH_PhyRead(PHY_BASE_ADDR, PHY_REG_SPEC_STATUS);
    return ((ret & PHY_BIT_DUPLEX) >> 13);
}

BOOL phy_Init() {
    phy_AutoMediaSelect();
    phy_AutoNeg();

    if (!phy_PartnerCanAutoNeg()) {
        printf("Warning:: PHY's partner can't do auto-negotiation\n");
    }

    if (!phy_IsLink()) {
        printf("link is down\n");
        return FALSE;
    }

    {
        uint32_t speed = phy_GetSpeed();
        if (speed == PHY_SPEED_10) {
            speed = 10;
        } else if (speed == PHY_SPEED_100) {
            speed = 100;
        } else if (speed == PHY_SPEED_1000) {
            speed = 1000;
        }

        printf("PHY runs in %uM speed %s duplex\n",
            speed, (phy_GetDuplex() == PHY_DUPLEX_HALF) ? "half" : "full");
    }

    // After auto-negcioation, Mawell PHY need some
    // time to initial itself.
    // So we have to delay some time since different
    // connection way, such as direct wire, hub, switch.
    // If not to delay, the first several sent frame
    // may be lost.
    // Please according to actual environment to tune
    // this delay.
    udelay(200000);

    return TRUE;
}
