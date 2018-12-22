/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ENET_PRIVATE_H__
#define __ENET_PRIVATE_H__

#include "enet/enet.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#define     NUM_OF_ETH_DEVS 1

#define ENET_RX_FRAMES      8

#define ENET_FRAME_LEN      (1540+4)

/* the defines to active transmit or receive frame */
#define ENET_RX_TX_ACTIVE   BM_ENET_TDAR_TDAR   //BM_ENET_RDAR_RDAR

/* the defines of Ethernet Control register */
#define ENET_RESET  BM_ENET_ECR_RESET

#define ENET_ETHER_EN   BM_ENET_ECR_ETHEREN
#define ENET_ETHER_SPEED_1000M (1<<5)
#define ENET_ETHER_LITTLE_ENDIAN (1<<8)
/* the defins of MII operation */
#define ENET_MII_ST 0x40000000

#define ENET_MII_OP_OFF BP_ENET_MMFR_OP

#define ENET_MII_OP_MASK 0x03

#define ENET_MII_OP_RD  0x02

#define ENET_MII_OP_WR  0x01

#define ENET_MII_PA_OFF BP_ENET_MMFR_PA

#define ENET_MII_PA_MASK 0xFF

#define ENET_MII_RA_OFF 18

#define ENET_MII_RA_MASK    0xFF

#define ENET_MII_TA 0x00020000

#define ENET_MII_DATA_OFF BP_ENET_MMFR_DATA

#define ENET_MII_DATA_MASK 0x0000FFFF

#define ENET_MII_FRAME  ( ENET_MII_ST | ENET_MII_TA )

#define ENET_MII_OP(x)  ( ((x) & ENET_MII_OP_MASK) << ENET_MII_OP_OFF )

#define ENET_MII_PA(pa)  (((pa)& ENET_MII_PA_MASK) << ENET_MII_PA_OFF)

#define ENET_MII_RA(ra) (((ra)& ENET_MII_RA_MASK) << ENET_MII_RA_OFF)

#define ENET_MII_SET_DATA(v) (((v) & ENET_MII_DATA_MASK) << ENET_MII_DATA_OFF)

#define ENET_MII_GET_DATA(v) (((v) >> ENET_MII_DATA_OFF) & ENET_MII_DATA_MASK )

#define ENET_MII_READ(pa, ra) ( ( ENET_MII_FRAME | ENET_MII_OP(ENET_MII_OP_RD) )|\
                    ENET_MII_PA(pa) | ENET_MII_RA(ra) )

#define ENET_MII_WRITE(pa, ra, v) ( ENET_MII_FRAME | ENET_MII_OP(ENET_MII_OP_WR)|\
                ENET_MII_PA(pa) | ENET_MII_RA(ra) |ENET_MII_SET_DATA(v) )

#define MII_SPEED_SHIFT 1

#define MII_SPEED_MASK  0x0000003F

#define MII_SPEED(x)    ( (((((x)+499999)/2500000)&(MII_SPEED_MASK))>>1)<<(MII_SPEED_SHIFT) )

/*the defines of MIB control */
#define ENET_MIB_DISABLE    BM_ENET_MIBC_MIB_DIS

/*the defines of Receive Control*/
#define ENET_RCR_FCE    BM_ENET_RCR_FCE

#define ENET_RCR_BC_REJ BM_ENET_RCR_BC_REJ

#define ENET_RCR_PROM   BM_ENET_RCR_PROM

#define ENET_RCR_MII_MODE   (BM_ENET_RCR_MII_MODE)
#define ENET_RCR_RGMII_EN       (1<<6)  /*RGMII enable/disable */
#define ENET_RCR_RMII_MODE      (BM_ENET_RCR_RMII_MODE)  /*RMII mode:1->10M, 0->100M */

/*the defines of Transmit Control*/
#define ENET_TCR_RFC_PAUSE  BM_ENET_TCR_RFC_PAUSE

#define ENET_TCR_FDEN       BM_ENET_TCR_FDEN

/*the defines of buffer description*/
#define ENET_BD_RX_NUM  8

#define ENET_BD_TX_NUM  2

#define BD_RX_ST_EMPTY 0x8000

#define BD_RX_ST_WRAP  0x2000

#define BD_RX_ST_LAST  0x0800

#define BD_RX_ST_ERRS  0x0037

#define BD_TX_ST_RDY    0x8000

#define BD_TX_ST_WRAP   0x2000

#define BD_TX_ST_LAST   0x0800

#define BD_TX_ST_TC     0x0400

#define BD_TX_ST_ABC    0x0200

//! @brief  Data structure for Tx/Rx buffer descriptor
typedef struct imx_enet_bd {
    unsigned short int length;  /*packet size */
    unsigned short int status;  /*control & statue of this buffer description */
    unsigned char *data;        /*frame buffer address */
} imx_enet_bd_t;

#define MXC_ENET_PRIVATE(x) ((imx_enet_priv_t *)(x)->driver_private)

/*The defines of the status field of imx_enet_priv_t */
#define ENET_STATUS_LINK_ON 0x80000000

#define ENET_STATUS_FULL_DPLX   0x40000000

#define ENET_STATUS_AUTO_NEG    0x20000000
#define ENET_STATUS_10M     0x8000000
#define ENET_STATUS_100M        0x10000000
#define ENET_STATUS_1000M       0x20000000

enum
{
    PHY_LAN8700_ID = 0x0007c0c0,
    PHY_LAN8720_ID = 0x0007c0f0,
    PHY_AR8031_ID = 0x004dd070,
    PHY_KSZ9021RN_ID = 0x00221610
};

#define PHY_CTRL_REG        0x00

#define PHY_CTRL_RESET      0x8000

#define PHY_CTRL_AUTO_NEG   0x1000

#define PHY_CTRL_FULL_DPLX  0x0100

#define PHY_STATUS_REG      0x01

#define PHY_STATUS_LINK_ST  0x0004

#define PHY_IDENTIFY_1      0x02

#define PHY_IDENTIFY_2      0x03

#define PHY_ID1_SHIFT       16

#define PHY_ID1_MASK        0xFFFF

#define PHY_ID2_SHIFT       0

#define PHY_ID2_MASK        0xFFFF

#define PHY_MODE_NUM        0x03F0

#define PHY_REV_NUM     0x000F

#define PHY_DIAG_REG        0x12

#define PHY_DIAG_DPLX       0x0800

#define PHY_DIAG_RATE       0x0400

#define PHY_MODE_REG        0x15

#define PHY_LED_SEL         0x200

#define PHY_AUTO_NEG_REG    0x5

#define PHY_AUTO_10BASET    0x20

#define PHY_AUTO_10BASET_DPLX       0x40

#define PHY_AUTO_100BASET   0x80

#define PHY_AUTO_100BASET_DPLX  0x100

#define PHY_AUTO_NEG_EXP_REG    0x6

#define PHY_AUTO_NEG_NEW_PAGE   0x2

#define PHY_AUTO_NEG_CAP        0x1

#define PHY_INT_SRC_REG 29

#define PHY_INT_AUTO_NEG    0x40

#define ENET_COMMON_TICK    2

#define ENET_COMMON_TIMEOUT (1000*1000)

#define ENET_MII_TICK   2

#define ENET_MII_TIMEOUT    (1000*1000)


#endif //__ENET_PRIVATE_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
