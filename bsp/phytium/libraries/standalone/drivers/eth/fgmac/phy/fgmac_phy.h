/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fgmac_phy.h
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file implements functionalities to:
 * Detect the available PHYs connected to a MAC
 * Negotiate speed
 * Configure speed
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 *  1.0   huanghe    2021/07/13    first release
 */

#ifndef  FGMAC_PHY_H
#define  FGMAC_PHY_H

#include "ftypes.h"
#include "fassert.h"
#include "fkernel.h"
#include "fgmac.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/
#define FGMAC_PHY_MAX_NUM                         32U

/* Generic MII registers. */
#define FGMAC_PHY_MII_CTRL_REG                      0x00    /* Basic mode control register */
#define FGMAC_PHY_MII_STATUS_REG                    0x01    /* Basic mode status register  */
#define FGMAC_PHY_MII_PHYSID1_REG                   0x02    /* PHYS ID 1                   */
#define FGMAC_PHY_MII_PHYSID2_REG                   0x03    /* PHYS ID 2                   */
#define FGMAC_PHY_MII_AUTONEG_REG                   0x04    /* Advertisement control reg   */
#define FGMAC_PHY_MII_LP_REG                        0x05    /* Link partner ability reg    */
#define FGMAC_PHY_MII_AUTONEG_EX_REG                0x06    /* Expansion register          */
#define FGMAC_PHY_MII_NEXT_PAGE_REG                 0x07    /* Next Page Transmit Register */
#define FGMAC_PHY_MII_LP_NEXT_PAGE_REG              0x08    /* Link Partner Next Page Register */
#define FGMAC_PHY_MII_CTRL1000_REG                  0x09    /* 1000BASE-T control          */
#define FGMAC_PHY_MII_STAT1000_REG                  0x0a    /* 1000BASE-T status           */
#define FGMAC_PHY_MII_MMD_CTRL_REG                  0x0d    /* MMD Access Control Register */
#define FGMAC_PHY_MII_MMD_DATA_REG                  0x0e    /* MMD Access Data Register */
#define FGMAC_PHY_MII_ESTATUS_REG                   0x0f    /* Extended Status             */
#define FGMAC_PHY_MII_FUNC_CONTROL_REG              0x10    /* Function control            */
#define FGMAC_PHY_MII_PHY_SPECIAL_REG               0x11    /* PHY-specific status         */
#define FGMAC_PHY_MII_DCOUNTER_REG                  0x12    /* Disconnect counter          */
#define FGMAC_PHY_MII_FCSCOUNTER_REG                0x13    /* False carrier counter       */
#define FGMAC_PHY_MII_NWAYTEST_REG                  0x14    /* N-way auto-neg test reg     */
#define FGMAC_PHY_MII_RERRCOUNTER_REG               0x15    /* Receive error counter       */
#define FGMAC_PHY_MII_SREVISION_REG                 0x16    /* Silicon revision            */
#define FGMAC_PHY_MII_RESV1_REG                     0x17    /* Reserved...                 */
#define FGMAC_PHY_MII_LBRERROR_REG                  0x18    /* Lpback, rx, bypass error    */
#define FGMAC_PHY_MII_PHYADDR_REG                   0x19    /* PHY address                 */
#define FGMAC_PHY_MII_RESV2_REG                     0x1a    /* Reserved...                 */
#define FGMAC_PHY_MII_TPISTATUS_REG                 0x1b    /* TPI status for 10mbps       */
#define FGMAC_PHY_MII_NCONFIG_REG                   0x1c    /* Network interface config    */

#define FGMAC_PHY_ID1  (0xffff)
#define FGMAC_PHY_ID2  (0xffff)

/* Basic mode control register */
#define FGMAC_PHY_MII_CR_RES                      GENMASK(5, 0) /* Unused...                   */
#define FGMAC_PHY_MII_CR_SPEED_SEL_MSB            BIT(6) /* MSB of Speed (1000)         */
#define FGMAC_PHY_MII_CR_COLLISION_TEST           BIT(7) /* Collision test              */
#define FGMAC_PHY_MII_CR_DUPLEX_MODE              BIT(8) /* Full duplex                 */
#define FGMAC_PHY_MII_CR_RESTART_AUTO_NEGO        BIT(9) /* Auto negotiation restart    */
#define FGMAC_PHY_MII_CR_ISOLATE                  BIT(10) /* Isolate data paths from MII */
#define FGMAC_PHY_MII_CR_POWER_DOWN               BIT(11) /* Enable low power state      */
#define FGMAC_PHY_MII_CR_AUTO_NEGOT               BIT(12) /* Enable auto negotiation     */
#define FGMAC_PHY_MII_CR_SPEED_SEL_LSB            BIT(13) /* Select 100Mbps              */
#define FGMAC_PHY_MII_CR_LOOPBACK                 BIT(14) /* TXD loopback bits           */
#define FGMAC_PHY_MII_CR_RESET                    BIT(15) /* Reset to default state      */

#define FGMAC_PHY_MII_CR_FULLDUPLEX_1000M ((u16)0x2140U)        /* Set the full-duplex mode at 1000 Mb/s */
#define FGMAC_PHY_MII_CR_HALFDUPLEX_1000M ((u16)0x2040U)        /* Set the half-duplex mode at 1000 Mb/s */
#define FGMAC_PHY_MII_CR_FULLDUPLEX_100M ((u16)0x2100U)         /* Set the full-duplex mode at 100 Mb/s */
#define FGMAC_PHY_MII_CR_HALFDUPLEX_100M ((u16)0x2000U)         /* Set the half-duplex mode at 100 Mb/s */
#define FGMAC_PHY_MII_CR_FULLDUPLEX_10M ((u16)0x0100U)          /* Set the full-duplex mode at 10 Mb/s  */
#define FGMAC_PHY_MII_CR_HALFDUPLEX_10M ((u16)0x0000U)          /* Set the half-duplex mode at 10 Mb/s  */

/* Basic mode status register. */
#define FGMAC_PHY_MII_SR_EXT_CAP                  BIT(0)  /* Ext-reg capability          */
#define FGMAC_PHY_MII_SR_JCD                      BIT(1)  /* Jabber detected             */
#define FGMAC_PHY_MII_SR_LSTATUS                  BIT(2)  /* Link status                 */
#define FGMAC_PHY_MII_SR_AUTO_NEGOT               BIT(3)  /* Able to do auto-negotiation */
#define FGMAC_PHY_MII_SR_REMOTE_FAULT             BIT(4)  /* Remote fault detected       */
#define FGMAC_PHY_MII_SR_AUTO_NEGOT_COMPLETE      BIT(5)  /* Auto-negotiation complete   */
#define FGMAC_PHY_MII_SR_MF_PREAM                 BIT(6)  /* MF Preamble Suppression */
#define FGMAC_PHY_MII_SR_EXT_STATUS               BIT(8)  /* Extended Status in R15 */
#define FGMAC_PHY_MII_SR_100HALF2                   BIT(9)  /* Can do 100BASE-T2 HDX       */
#define FGMAC_PHY_MII_SR_100FULL2                   BIT(10) /* Can do 100BASE-T2 FDX       */
#define FGMAC_PHY_MII_SR_10HALF                     BIT(11) /* Can do 10mbps, half-duplex  */
#define FGMAC_PHY_MII_SR_10FULL                     BIT(12) /* Can do 10mbps, full-duplex  */
#define FGMAC_PHY_MII_SR_100HALF                    BIT(13) /* Can do 100mbps, half-duplex */
#define FGMAC_PHY_MII_SR_100FULL                    BIT(14) /* Can do 100mbps, full-duplex */
#define FGMAC_PHY_MII_SR_100BASE4                   BIT(15) /* Can do 100mbps, 4k packets  */

/* MII_STAT1000 masks */
#define FGMAC_PHY_MII_1000BTSR_MSCF             BIT(15) /* Master/Slave Configuration Fault */
#define FGMAC_PHY_MII_1000BTSR_MSCR             BIT(14) /* Master/Slave Configuration Resolution */
#define FGMAC_PHY_MII_1000BTSR_LRS              BIT(13) /* Local Receiver Status */
#define FGMAC_PHY_MII_1000BTSR_RRS              BIT(12) /* Remote Receiver Status */
#define FGMAC_PHY_MII_1000BTSR_1000FD             BIT(11) /* Full Duplex Capability */
#define FGMAC_PHY_MII_1000BTSR_1000HD             BIT(10) /* Half Duplex Capability */
#define FGMAC_PHY_MII_1000BTSR_IDLE_ERR_CNT       GENMASK(7, 0) /* MSB of Idle Error Counter */

/* Link partner ability register. */
#define FGMAC_PHY_MII_LPA_SELECT                  GENMASK(4, 0) /* Selector Field */
#define FGMAC_PHY_MII_LPA_10HALF                  BIT(5) /* 10BASE-T half-duplex capable */
#define FGMAC_PHY_MII_LPA_10FULL                  BIT(6) /* 10BASE-T full-duplex capable */
#define FGMAC_PHY_MII_LPA_1000TXHALF              BIT(7) /* 100BASE-TX half-duplex capable */
#define FGMAC_PHY_MII_LPA_1000TXFULL              BIT(8) /* 100BASE-TX full-duplex capable */
#define FGMAC_PHY_MII_LPA_T4                      BIT(9) /* 100BASE-T4 capable */
#define FGMAC_PHY_MII_LPA_PAUSE                   BIT(10) /* capable of pause operation */
#define FGMAC_PHY_MII_LPA_ASY_PAUSE               BIT(11) /* asymmetric pause */
#define FGMAC_PHY_MII_LPA_REMOTE_FAULT            BIT(13) /* Remote Fault */
#define FGMAC_PHY_MII_LPA_ACK                     BIT(14) /* Acknowledge */
#define FGMAC_PHY_MII_LPA_NEXT_PAGE               BIT(15) /* capable of next page */

/* Expansion register for auto-negotiation. */
#define FGMAC_PHY_MII_ESTATUS_1000_XFULL            BIT(15) /* Can do 1000BX Full */
#define FGMAC_PHY_MII_ESTATUS_1000_XHALF            BIT(14) /* Can do 1000BX Half */
#define FGMAC_PHY_MII_ESTATUS_1000_TFULL            BIT(13) /* Can do 1000BT Full          */
#define FGMAC_PHY_MII_ESTATUS_1000_THALF            BIT(12) /* Can do 1000BT Half          */
#define FGMAC_PHY_MII_ESTATUS_MASK     (FGMAC_PHY_MII_ESTATUS_1000_XFULL | FGMAC_PHY_MII_ESTATUS_1000_XHALF | \
                                        FGMAC_PHY_MII_ESTATUS_1000_TFULL | FGMAC_PHY_MII_ESTATUS_1000_THALF)
#define FGMAC_PHY_MII_ESTATUS_FULL_MASK  (FGMAC_PHY_MII_ESTATUS_1000_XFULL | FGMAC_PHY_MII_ESTATUS_1000_TFULL)


#define FGMAC_PHY_SPECIFIC_STATUS_SPEED_MASK GENMASK(15, 14)

#define FGMAC_PHY_SPECIFIC_STATUS_SPEED_1000M (2L << 14)
#define FGMAC_PHY_SPECIFIC_STATUS_SPEED_100M (1L << 14)
#define FGMAC_PHY_SPECIFIC_STATUS_SPEED_10M (0L << 14)

#define FGMAC_PHY_SPECIFIC_STATUS_DUPLEX_MASK BIT(13)

enum
{
    FGMAC_PHY_AUTONEGOTIATION_DISABLE = 0,
    FGMAC_PHY_AUTONEGOTIATION_ENABLE
};

enum
{
    FGMAC_PHY_MODE_HALFDUPLEX = 0,
    FGMAC_PHY_MODE_FULLDUPLEX = 1
};

/* The forced speed, 10Mb, 100Mb, gigabit, 2.5Gb, 10GbE. */
enum
{
    FGMAC_PHY_SPEED_10 = 10,
    FGMAC_PHY_SPEED_100 = 100,
    FGMAC_PHY_SPEED_1000 = 1000,
    FGMAC_PHY_SPEED_2500 = 2500,
    FGMAC_PHY_SPEED_10000 = 10000
};

enum
{
    FGMAC_PHY_MII_ADDR_CR_60_100MHZ   = (0b0000),
    FGMAC_PHY_MII_ADDR_CR_100_150MHZ  = (0b0001),
    FGMAC_PHY_MII_ADDR_CR_23_35MHZ    = (0b0010),
    FGMAC_PHY_MII_ADDR_CR_35_60MHZ    = (0b0011),
    FGMAC_PHY_MII_ADDR_CR_150_250MHZ  = (0b0100),
    FGMAC_PHY_MII_ADDR_CR_250_300MHZ  = (0b0101)
};

/**************************** Type Definitions *******************************/
/**
 * This typedef contains driver instance data. The user is required to allocate a
 * variable of this type for every device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */


/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/* init phy device */
FError FGmacPhyCfgInitialize(FGmac *instance_p);
/* write phy register */
FError FGmacWritePhyReg(FGmac *instance_p, u32 phy_address, u16 phy_reg, u16 phy_reg_val);
/* read phy register */
FError FGmacReadPhyReg(FGmac *instance_p, u32 phy_address, u16 phy_reg, u16 *phy_reg_val_p);

FError FGmacPhyCfgDeInitialize(FGmac *instance_p);

FError FGmacPhyAwaken(FGmac *instance_p);

#ifdef __cplusplus
}
#endif


#endif
