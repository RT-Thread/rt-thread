/*
 * Copyright (C) Cvitek Co., Ltd. 2019-2020. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "cvi_eth_phy.h"
#include "mii.h"
#include "drv_pinmux.h"

// #define CVI_ETH_PHY_LOOPBACK
#define LOOPBACK_XMII2MAC       0x8000
#define LOOPBACK_PCS2MAC        0x2000
#define LOOPBACK_PMA2MAC        0x1000
#define LOOPBACK_RMII2PHY       0x0080

#define CVITEK_EFUSE_BASE           (uintptr_t)DRV_IOREMAP((void *)0x03050000, 0x2000)
#define EPHY_EFUSE_VALID_BIT_BASE   (CVITEK_EFUSE_BASE + 0x120)
#define EPHY_EFUSE_TXECHORC_FLAG    0x00000100 // bit 8
#define EPHY_EFUSE_TXITUNE_FLAG     0x00000200 // bit 9
#define EPHY_EFUSE_TXRXTERM_FLAG    0x00000800 // bit 11

static inline bool phy_if_mode_is_rgmii(phy_if_mode_t interface)
{
    return interface >= PHY_IF_MODE_RGMII && interface <= PHY_IF_MODE_RGMII_TXID;
}

#if defined(CVI_ETH_PHY_LOOPBACK)
static int cv181x_set_phy_loopback(eth_phy_handle_t handle, phy_loopback_mode_t mode)
{
    return 0;
}
#endif

/**
  \brief       Configure the cv181x before make it start up.
  \param[in]   handle  phy handle
  \return      error code
*/
/* CVITEK cv181x */
int32_t cv181x_config(eth_phy_handle_t handle)
{
    assert(handle);
    eth_phy_dev_t *dev = (eth_phy_dev_t *)handle;
    uint32_t val = 0;

    // eth_phy_reset(dev);

    // set rg_ephy_apb_rw_sel 0x0804@[0]=1/APB by using APB interface
    mmio_write_32(ETH_PHY_BASE + 0x804, 0x0001);

    // Release 0x0800[0]=0/shutdown
    // mmio_write_32(ETH_PHY_BASE + 0x800, 0x0900);

    // Release 0x0800[2]=1/dig_rst_n, Let mii_reg can be accessabile
    // mmio_write_32(ETH_PHY_BASE + 0x800, 0x0904);

    //mdelay(10);

    // ANA INIT (PD/EN), switch to MII-page5
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x0500);

    // Release ANA_PD p5.0x10@[13:8] = 6'b001100
    mmio_write_32(ETH_PHY_BASE + 0x040, 0x0c00);

    // Release ANA_EN p5.0x10@[7:0] = 8'b01111110
    mmio_write_32(ETH_PHY_BASE + 0x040, 0x0c7e);

    // Wait PLL_Lock, Lock_Status p5.0x12@[15] = 1
    //mdelay(1);

    // Release 0x0800[1] = 1/ana_rst_n
    mmio_write_32(ETH_PHY_BASE + 0x800, 0x0906);

    // ANA INIT
    // @Switch to MII-page5
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x0500);

// Efuse register
    // Set Double Bias Current
    //Set rg_eth_txitune1  0x03009064 [15:8]
    //Set rg_eth_txitune0  0x03009064 [7:0]
    if ((mmio_read_32(EPHY_EFUSE_VALID_BIT_BASE) & EPHY_EFUSE_TXITUNE_FLAG) == EPHY_EFUSE_TXITUNE_FLAG)
    {
        val = ((mmio_read_32(CVITEK_EFUSE_BASE + 0x1024) >> 24) & 0xFF) | (((mmio_read_32(CVITEK_EFUSE_BASE + 0x1024) >> 16) & 0xFF) << 8);
        mmio_clrsetbits_32(ETH_PHY_BASE + 0x064, 0xFFFF, val);
    }
    else
        mmio_write_32(ETH_PHY_BASE + 0x064, 0x5a5a);

    // Set Echo_I
    // Set rg_eth_txechoiadj 0x03009054  [15:8]
    if ((mmio_read_32(EPHY_EFUSE_VALID_BIT_BASE) & EPHY_EFUSE_TXECHORC_FLAG) == EPHY_EFUSE_TXECHORC_FLAG)
    {
        mmio_clrsetbits_32(ETH_PHY_BASE + 0x054, 0xFF00, ((mmio_read_32(CVITEK_EFUSE_BASE + 0x1024) >> 8) & 0xFF) << 8);
    }
    else
        mmio_write_32(ETH_PHY_BASE + 0x054, 0x0000);

    //Set TX_Rterm & Echo_RC_Delay
    // Set rg_eth_txrterm_p1  0x03009058 [11:8]
    // Set rg_eth_txrterm     0x03009058  [7:4]
    // Set rg_eth_txechorcadj 0x03009058  [3:0]
    if ((mmio_read_32(EPHY_EFUSE_VALID_BIT_BASE) & EPHY_EFUSE_TXRXTERM_FLAG) == EPHY_EFUSE_TXRXTERM_FLAG)
    {
        val = (((mmio_read_32(CVITEK_EFUSE_BASE + 0x1020) >> 28) & 0xF) << 4) | (((mmio_read_32(CVITEK_EFUSE_BASE + 0x1020) >> 24) & 0xF) << 8);
        mmio_clrsetbits_32(ETH_PHY_BASE + 0x058, 0xFF0, val);
    }
    else
        mmio_write_32(ETH_PHY_BASE + 0x058, 0x0bb0);

    // ETH_100BaseT
    // Set Rise update
    mmio_write_32(ETH_PHY_BASE + 0x05c, 0x0c10);

    // Set Falling phase
    mmio_write_32(ETH_PHY_BASE + 0x068, 0x0003);

    // Set Double TX Bias Current
    mmio_write_32(ETH_PHY_BASE + 0x054, 0x0000);

    // Switch to MII-page16
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x1000);

    // Set MLT3 Positive phase code, Set MLT3 +0
    mmio_write_32(ETH_PHY_BASE + 0x068, 0x1000);
    mmio_write_32(ETH_PHY_BASE + 0x06c, 0x3020);
    mmio_write_32(ETH_PHY_BASE + 0x070, 0x5040);
    mmio_write_32(ETH_PHY_BASE + 0x074, 0x7060);

    // Set MLT3 +I
    mmio_write_32(ETH_PHY_BASE + 0x058, 0x1708);
    mmio_write_32(ETH_PHY_BASE + 0x05c, 0x3827);
    mmio_write_32(ETH_PHY_BASE + 0x060, 0x5748);
    mmio_write_32(ETH_PHY_BASE + 0x064, 0x7867);

    // Switch to MII-page17
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x1100);

    // Set MLT3 Negative phase code, Set MLT3 -0
    mmio_write_32(ETH_PHY_BASE + 0x040, 0x9080);
    mmio_write_32(ETH_PHY_BASE + 0x044, 0xb0a0);
    mmio_write_32(ETH_PHY_BASE + 0x048, 0xd0c0);
    mmio_write_32(ETH_PHY_BASE + 0x04c, 0xf0e0);

    // Set MLT3 -I
    mmio_write_32(ETH_PHY_BASE + 0x050, 0x9788);
    mmio_write_32(ETH_PHY_BASE + 0x054, 0xb8a7);
    mmio_write_32(ETH_PHY_BASE + 0x058, 0xd7c8);
    mmio_write_32(ETH_PHY_BASE + 0x05c, 0xf8e7);

    // @Switch to MII-page5
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x0500);

    // En TX_Rterm
    mmio_write_32(ETH_PHY_BASE + 0x040, (0x0001 | mmio_read_32(ETH_PHY_BASE + 0x040)));

//  Link Pulse
    // Switch to MII-page10
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x0a00);

    // Set Link Pulse
    mmio_write_32(ETH_PHY_BASE + 0x040, 0x2000);
    mmio_write_32(ETH_PHY_BASE + 0x044, 0x3832);
    mmio_write_32(ETH_PHY_BASE + 0x048, 0x3132);
    mmio_write_32(ETH_PHY_BASE + 0x04c, 0x2d2f);
    mmio_write_32(ETH_PHY_BASE + 0x050, 0x2c2d);
    mmio_write_32(ETH_PHY_BASE + 0x054, 0x1b2b);
    mmio_write_32(ETH_PHY_BASE + 0x058, 0x94a0);
    mmio_write_32(ETH_PHY_BASE + 0x05c, 0x8990);
    mmio_write_32(ETH_PHY_BASE + 0x060, 0x8788);
    mmio_write_32(ETH_PHY_BASE + 0x064, 0x8485);
    mmio_write_32(ETH_PHY_BASE + 0x068, 0x8283);
    mmio_write_32(ETH_PHY_BASE + 0x06c, 0x8182);
    mmio_write_32(ETH_PHY_BASE + 0x070, 0x0081);

// TP_IDLE
    // Switch to MII-page11
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x0b00);

// Set TP_IDLE
    mmio_write_32(ETH_PHY_BASE + 0x040, 0x5252);
    mmio_write_32(ETH_PHY_BASE + 0x044, 0x5252);
    mmio_write_32(ETH_PHY_BASE + 0x048, 0x4B52);
    mmio_write_32(ETH_PHY_BASE + 0x04c, 0x3D47);
    mmio_write_32(ETH_PHY_BASE + 0x050, 0xAA99);
    mmio_write_32(ETH_PHY_BASE + 0x054, 0x989E);
    mmio_write_32(ETH_PHY_BASE + 0x058, 0x9395);
    mmio_write_32(ETH_PHY_BASE + 0x05C, 0x9091);
    mmio_write_32(ETH_PHY_BASE + 0x060, 0x8E8F);
    mmio_write_32(ETH_PHY_BASE + 0x064, 0x8D8E);
    mmio_write_32(ETH_PHY_BASE + 0x068, 0x8C8C);
    mmio_write_32(ETH_PHY_BASE + 0x06C, 0x8B8B);
    mmio_write_32(ETH_PHY_BASE + 0x070, 0x008A);

// ETH 10BaseT Data
    // Switch to MII-page13
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x0d00);

    mmio_write_32(ETH_PHY_BASE + 0x040, 0x1E0A);
    mmio_write_32(ETH_PHY_BASE + 0x044, 0x3862);
    mmio_write_32(ETH_PHY_BASE + 0x048, 0x1E62);
    mmio_write_32(ETH_PHY_BASE + 0x04c, 0x2A08);
    mmio_write_32(ETH_PHY_BASE + 0x050, 0x244C);
    mmio_write_32(ETH_PHY_BASE + 0x054, 0x1A44);
    mmio_write_32(ETH_PHY_BASE + 0x058, 0x061C);

    // Switch to MII-page14
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x0e00);

    mmio_write_32(ETH_PHY_BASE + 0x040, 0x2D30);
    mmio_write_32(ETH_PHY_BASE + 0x044, 0x3470);
    mmio_write_32(ETH_PHY_BASE + 0x048, 0x0648);
    mmio_write_32(ETH_PHY_BASE + 0x04c, 0x261C);
    mmio_write_32(ETH_PHY_BASE + 0x050, 0x3160);
    mmio_write_32(ETH_PHY_BASE + 0x054, 0x2D5E);

    // Switch to MII-page15
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x0f00);

    mmio_write_32(ETH_PHY_BASE + 0x040, 0x2922);
    mmio_write_32(ETH_PHY_BASE + 0x044, 0x366E);
    mmio_write_32(ETH_PHY_BASE + 0x048, 0x0752);
    mmio_write_32(ETH_PHY_BASE + 0x04c, 0x2556);
    mmio_write_32(ETH_PHY_BASE + 0x050, 0x2348);
    mmio_write_32(ETH_PHY_BASE + 0x054, 0x0C30);

    // Switch to MII-page16
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x1000);

    mmio_write_32(ETH_PHY_BASE + 0x040, 0x1E08);
    mmio_write_32(ETH_PHY_BASE + 0x044, 0x3868);
    mmio_write_32(ETH_PHY_BASE + 0x048, 0x1462);
    mmio_write_32(ETH_PHY_BASE + 0x04c, 0x1A0E);
    mmio_write_32(ETH_PHY_BASE + 0x050, 0x305E);
    mmio_write_32(ETH_PHY_BASE + 0x054, 0x2F62);

// LED PAD MUX
    uintptr_t addr = (uintptr_t)DRV_IOREMAP((void *)0x03001000, 0x1000);
    mmio_write_32((uintptr_t)(addr + 0xe0), 0x05);
    mmio_write_32((uintptr_t)(addr + 0xe4), 0x05);

    //(SD1_CLK selphy)
    addr = (uintptr_t)DRV_IOREMAP((void *)0x05027000, 0x1000);
    mmio_write_32((intptr_t)(addr + 0xb0), 0x11111111);
    //(SD1_CMD selphy)
    mmio_write_32((intptr_t)(addr + 0xb4), 0x11111111);

// LED
    // Switch to MII-page1
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x0100);

    // select LED_LNK/SPD/DPX out to LED_PAD
    mmio_write_32(ETH_PHY_BASE + 0x068, (mmio_read_32(ETH_PHY_BASE + 0x068) & ~0x0f00));

    // @Switch to MII-page0
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x0000);

    // PHY_ID
    mmio_write_32(ETH_PHY_BASE + 0x008, 0x0043);
    mmio_write_32(ETH_PHY_BASE + 0x00c, 0x5649);

    // Switch to MII-page19
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x1300);
    mmio_write_32(ETH_PHY_BASE + 0x058, 0x0012);
    // set agc max/min swing
    mmio_write_32(ETH_PHY_BASE + 0x05C, 0x6848);

    // Switch to MII-page18
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x1200);
    // p18.0x12, lpf
    mmio_write_32(ETH_PHY_BASE + 0x048, 0x0808);
    mmio_write_32(ETH_PHY_BASE + 0x04C, 0x0808);
// hpf
//sean
    mmio_write_32(ETH_PHY_BASE + 0x050, 0x32f8);
    mmio_write_32(ETH_PHY_BASE + 0x054, 0xf8dc);

    // Switch to MII-page0
    mmio_write_32(ETH_PHY_BASE + 0x07c, 0x0000);
    // EPHY start auto-neg procedure
    mmio_write_32(ETH_PHY_BASE + 0x800, 0x090e);

    // switch to MDIO control by ETH_MAC
    mmio_write_32(ETH_PHY_BASE + 0x804, 0x0000);

    genphy_config(dev);

#if defined(CVI_ETH_PHY_LOOPBACK)
    cv181x_set_phy_loopback(handle, LOOPBACK_PCS2MAC);
#endif

    return 0;
}

/**
  \brief       Parse 88E1xxx's speed and duplex from status register.
  \param[in]   dev  phy device pointer
  \return      error code
*/
static int32_t cv181x_parse_status(eth_phy_dev_t *dev)
{
    assert(dev);
    assert(dev->priv);
    eth_phy_priv_t *priv = dev->priv;
    uint8_t phy_addr = dev->phy_addr;
    uint16_t mii_reg;
    int32_t ret;

    ret = eth_phy_read(priv, phy_addr, CVI_MII_BMSR, &mii_reg);

    if (ret != 0) {
        return ret;
    }

    if (mii_reg & (CVI_BMSR_100FULL | CVI_BMSR_100HALF))
        priv->link_info.speed = CSI_ETH_SPEED_100M;
    else
        priv->link_info.speed = CSI_ETH_SPEED_10M;

    if (mii_reg & (CVI_BMSR_10FULL | CVI_BMSR_100FULL))
        priv->link_info.duplex = CSI_ETH_DUPLEX_FULL;
    else
        priv->link_info.duplex = CSI_ETH_DUPLEX_HALF;

    return 0;
}

/**
  \brief       Start up the 88E1111.
  \param[in]   handle  phy handle
  \return      error code
*/
int32_t cv181x_start(eth_phy_handle_t handle)
{
    assert(handle);

    eth_phy_dev_t *dev = (eth_phy_dev_t *)handle;

    /* Read the Status (2x to make sure link is right) */
    genphy_update_link(dev);

    return cv181x_parse_status(dev);
}

/**
  \brief       Halt the cv181x.
  \param[in]   handle  phy handle
  \return      error code
*/
int32_t cv181x_stop(eth_phy_handle_t handle)
{
    return 0;
}

/**
  \brief       Update the cv181x's link state.
  \param[in]   handle  phy handle
  \return      error code
*/
int32_t cv181x_update_link(eth_phy_handle_t handle)
{
    assert(handle);
    eth_phy_dev_t *dev = (eth_phy_dev_t *)handle;
    return cv181x_parse_status(dev);;
}


/* Support for cv181x PHYs */
eth_phy_dev_t cv181x_device = {
    .name = "CVITEK,CV181X",
    .phy_id = 0x00435649,
    .mask = 0xffffffff,
    .features = CVI_PHY_BASIC_FEATURES,
    .config = &cv181x_config,
    .start = &cv181x_start,
    .stop = &cv181x_stop,
    //.loopback = &cv181x_loopback,
    //.update_link = &cv181x_update_link,
};
