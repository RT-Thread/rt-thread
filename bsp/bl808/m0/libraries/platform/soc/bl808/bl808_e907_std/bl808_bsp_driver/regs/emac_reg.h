/**
  ******************************************************************************
  * @file    emac_reg.h
  * @version V1.0
  * @date    2021-09-10
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __EMAC_REG_H__
#define __EMAC_REG_H__

#include "bl808.h"

/* 0x0 : MODE */
#define EMAC_MODE_OFFSET   (0x0)
#define EMAC_RXEN          EMAC_RXEN
#define EMAC_RXEN_POS      (0U)
#define EMAC_RXEN_LEN      (1U)
#define EMAC_RXEN_MSK      (((1U << EMAC_RXEN_LEN) - 1) << EMAC_RXEN_POS)
#define EMAC_RXEN_UMSK     (~(((1U << EMAC_RXEN_LEN) - 1) << EMAC_RXEN_POS))
#define EMAC_TXEN          EMAC_TXEN
#define EMAC_TXEN_POS      (1U)
#define EMAC_TXEN_LEN      (1U)
#define EMAC_TXEN_MSK      (((1U << EMAC_TXEN_LEN) - 1) << EMAC_TXEN_POS)
#define EMAC_TXEN_UMSK     (~(((1U << EMAC_TXEN_LEN) - 1) << EMAC_TXEN_POS))
#define EMAC_NOPRE         EMAC_NOPRE
#define EMAC_NOPRE_POS     (2U)
#define EMAC_NOPRE_LEN     (1U)
#define EMAC_NOPRE_MSK     (((1U << EMAC_NOPRE_LEN) - 1) << EMAC_NOPRE_POS)
#define EMAC_NOPRE_UMSK    (~(((1U << EMAC_NOPRE_LEN) - 1) << EMAC_NOPRE_POS))
#define EMAC_BRO           EMAC_BRO
#define EMAC_BRO_POS       (3U)
#define EMAC_BRO_LEN       (1U)
#define EMAC_BRO_MSK       (((1U << EMAC_BRO_LEN) - 1) << EMAC_BRO_POS)
#define EMAC_BRO_UMSK      (~(((1U << EMAC_BRO_LEN) - 1) << EMAC_BRO_POS))
#define EMAC_PRO           EMAC_PRO
#define EMAC_PRO_POS       (5U)
#define EMAC_PRO_LEN       (1U)
#define EMAC_PRO_MSK       (((1U << EMAC_PRO_LEN) - 1) << EMAC_PRO_POS)
#define EMAC_PRO_UMSK      (~(((1U << EMAC_PRO_LEN) - 1) << EMAC_PRO_POS))
#define EMAC_IFG           EMAC_IFG
#define EMAC_IFG_POS       (6U)
#define EMAC_IFG_LEN       (1U)
#define EMAC_IFG_MSK       (((1U << EMAC_IFG_LEN) - 1) << EMAC_IFG_POS)
#define EMAC_IFG_UMSK      (~(((1U << EMAC_IFG_LEN) - 1) << EMAC_IFG_POS))
#define EMAC_FULLD         EMAC_FULLD
#define EMAC_FULLD_POS     (10U)
#define EMAC_FULLD_LEN     (1U)
#define EMAC_FULLD_MSK     (((1U << EMAC_FULLD_LEN) - 1) << EMAC_FULLD_POS)
#define EMAC_FULLD_UMSK    (~(((1U << EMAC_FULLD_LEN) - 1) << EMAC_FULLD_POS))
#define EMAC_CRCEN         EMAC_CRCEN
#define EMAC_CRCEN_POS     (13U)
#define EMAC_CRCEN_LEN     (1U)
#define EMAC_CRCEN_MSK     (((1U << EMAC_CRCEN_LEN) - 1) << EMAC_CRCEN_POS)
#define EMAC_CRCEN_UMSK    (~(((1U << EMAC_CRCEN_LEN) - 1) << EMAC_CRCEN_POS))
#define EMAC_HUGEN         EMAC_HUGEN
#define EMAC_HUGEN_POS     (14U)
#define EMAC_HUGEN_LEN     (1U)
#define EMAC_HUGEN_MSK     (((1U << EMAC_HUGEN_LEN) - 1) << EMAC_HUGEN_POS)
#define EMAC_HUGEN_UMSK    (~(((1U << EMAC_HUGEN_LEN) - 1) << EMAC_HUGEN_POS))
#define EMAC_PAD           EMAC_PAD
#define EMAC_PAD_POS       (15U)
#define EMAC_PAD_LEN       (1U)
#define EMAC_PAD_MSK       (((1U << EMAC_PAD_LEN) - 1) << EMAC_PAD_POS)
#define EMAC_PAD_UMSK      (~(((1U << EMAC_PAD_LEN) - 1) << EMAC_PAD_POS))
#define EMAC_RECSMALL      EMAC_RECSMALL
#define EMAC_RECSMALL_POS  (16U)
#define EMAC_RECSMALL_LEN  (1U)
#define EMAC_RECSMALL_MSK  (((1U << EMAC_RECSMALL_LEN) - 1) << EMAC_RECSMALL_POS)
#define EMAC_RECSMALL_UMSK (~(((1U << EMAC_RECSMALL_LEN) - 1) << EMAC_RECSMALL_POS))
#define EMAC_RMII_EN       EMAC_RMII_EN
#define EMAC_RMII_EN_POS   (17U)
#define EMAC_RMII_EN_LEN   (1U)
#define EMAC_RMII_EN_MSK   (((1U << EMAC_RMII_EN_LEN) - 1) << EMAC_RMII_EN_POS)
#define EMAC_RMII_EN_UMSK  (~(((1U << EMAC_RMII_EN_LEN) - 1) << EMAC_RMII_EN_POS))

/* 0x4 : INT_SOURCE */
#define EMAC_INT_SOURCE_OFFSET (0x4)
#define EMAC_TXB               EMAC_TXB
#define EMAC_TXB_POS           (0U)
#define EMAC_TXB_LEN           (1U)
#define EMAC_TXB_MSK           (((1U << EMAC_TXB_LEN) - 1) << EMAC_TXB_POS)
#define EMAC_TXB_UMSK          (~(((1U << EMAC_TXB_LEN) - 1) << EMAC_TXB_POS))
#define EMAC_TXE               EMAC_TXE
#define EMAC_TXE_POS           (1U)
#define EMAC_TXE_LEN           (1U)
#define EMAC_TXE_MSK           (((1U << EMAC_TXE_LEN) - 1) << EMAC_TXE_POS)
#define EMAC_TXE_UMSK          (~(((1U << EMAC_TXE_LEN) - 1) << EMAC_TXE_POS))
#define EMAC_RXB               EMAC_RXB
#define EMAC_RXB_POS           (2U)
#define EMAC_RXB_LEN           (1U)
#define EMAC_RXB_MSK           (((1U << EMAC_RXB_LEN) - 1) << EMAC_RXB_POS)
#define EMAC_RXB_UMSK          (~(((1U << EMAC_RXB_LEN) - 1) << EMAC_RXB_POS))
#define EMAC_RXE               EMAC_RXE
#define EMAC_RXE_POS           (3U)
#define EMAC_RXE_LEN           (1U)
#define EMAC_RXE_MSK           (((1U << EMAC_RXE_LEN) - 1) << EMAC_RXE_POS)
#define EMAC_RXE_UMSK          (~(((1U << EMAC_RXE_LEN) - 1) << EMAC_RXE_POS))
#define EMAC_BUSY              EMAC_BUSY
#define EMAC_BUSY_POS          (4U)
#define EMAC_BUSY_LEN          (1U)
#define EMAC_BUSY_MSK          (((1U << EMAC_BUSY_LEN) - 1) << EMAC_BUSY_POS)
#define EMAC_BUSY_UMSK         (~(((1U << EMAC_BUSY_LEN) - 1) << EMAC_BUSY_POS))
#define EMAC_TXC               EMAC_TXC
#define EMAC_TXC_POS           (5U)
#define EMAC_TXC_LEN           (1U)
#define EMAC_TXC_MSK           (((1U << EMAC_TXC_LEN) - 1) << EMAC_TXC_POS)
#define EMAC_TXC_UMSK          (~(((1U << EMAC_TXC_LEN) - 1) << EMAC_TXC_POS))
#define EMAC_RXC               EMAC_RXC
#define EMAC_RXC_POS           (6U)
#define EMAC_RXC_LEN           (1U)
#define EMAC_RXC_MSK           (((1U << EMAC_RXC_LEN) - 1) << EMAC_RXC_POS)
#define EMAC_RXC_UMSK          (~(((1U << EMAC_RXC_LEN) - 1) << EMAC_RXC_POS))

/* 0x8 : INT_MASK */
#define EMAC_INT_MASK_OFFSET (0x8)
#define EMAC_TXB_M           EMAC_TXB_M
#define EMAC_TXB_M_POS       (0U)
#define EMAC_TXB_M_LEN       (1U)
#define EMAC_TXB_M_MSK       (((1U << EMAC_TXB_M_LEN) - 1) << EMAC_TXB_M_POS)
#define EMAC_TXB_M_UMSK      (~(((1U << EMAC_TXB_M_LEN) - 1) << EMAC_TXB_M_POS))
#define EMAC_TXE_M           EMAC_TXE_M
#define EMAC_TXE_M_POS       (1U)
#define EMAC_TXE_M_LEN       (1U)
#define EMAC_TXE_M_MSK       (((1U << EMAC_TXE_M_LEN) - 1) << EMAC_TXE_M_POS)
#define EMAC_TXE_M_UMSK      (~(((1U << EMAC_TXE_M_LEN) - 1) << EMAC_TXE_M_POS))
#define EMAC_RXB_M           EMAC_RXB_M
#define EMAC_RXB_M_POS       (2U)
#define EMAC_RXB_M_LEN       (1U)
#define EMAC_RXB_M_MSK       (((1U << EMAC_RXB_M_LEN) - 1) << EMAC_RXB_M_POS)
#define EMAC_RXB_M_UMSK      (~(((1U << EMAC_RXB_M_LEN) - 1) << EMAC_RXB_M_POS))
#define EMAC_RXE_M           EMAC_RXE_M
#define EMAC_RXE_M_POS       (3U)
#define EMAC_RXE_M_LEN       (1U)
#define EMAC_RXE_M_MSK       (((1U << EMAC_RXE_M_LEN) - 1) << EMAC_RXE_M_POS)
#define EMAC_RXE_M_UMSK      (~(((1U << EMAC_RXE_M_LEN) - 1) << EMAC_RXE_M_POS))
#define EMAC_BUSY_M          EMAC_BUSY_M
#define EMAC_BUSY_M_POS      (4U)
#define EMAC_BUSY_M_LEN      (1U)
#define EMAC_BUSY_M_MSK      (((1U << EMAC_BUSY_M_LEN) - 1) << EMAC_BUSY_M_POS)
#define EMAC_BUSY_M_UMSK     (~(((1U << EMAC_BUSY_M_LEN) - 1) << EMAC_BUSY_M_POS))
#define EMAC_TXC_M           EMAC_TXC_M
#define EMAC_TXC_M_POS       (5U)
#define EMAC_TXC_M_LEN       (1U)
#define EMAC_TXC_M_MSK       (((1U << EMAC_TXC_M_LEN) - 1) << EMAC_TXC_M_POS)
#define EMAC_TXC_M_UMSK      (~(((1U << EMAC_TXC_M_LEN) - 1) << EMAC_TXC_M_POS))
#define EMAC_RXC_M           EMAC_RXC_M
#define EMAC_RXC_M_POS       (6U)
#define EMAC_RXC_M_LEN       (1U)
#define EMAC_RXC_M_MSK       (((1U << EMAC_RXC_M_LEN) - 1) << EMAC_RXC_M_POS)
#define EMAC_RXC_M_UMSK      (~(((1U << EMAC_RXC_M_LEN) - 1) << EMAC_RXC_M_POS))

/* 0xC : IPGT */
#define EMAC_IPGT_OFFSET (0xC)
#define EMAC_IPGT        EMAC_IPGT
#define EMAC_IPGT_POS    (0U)
#define EMAC_IPGT_LEN    (7U)
#define EMAC_IPGT_MSK    (((1U << EMAC_IPGT_LEN) - 1) << EMAC_IPGT_POS)
#define EMAC_IPGT_UMSK   (~(((1U << EMAC_IPGT_LEN) - 1) << EMAC_IPGT_POS))

/* 0x18 : PACKETLEN */
#define EMAC_PACKETLEN_OFFSET (0x18)
#define EMAC_MAXFL            EMAC_MAXFL
#define EMAC_MAXFL_POS        (0U)
#define EMAC_MAXFL_LEN        (16U)
#define EMAC_MAXFL_MSK        (((1U << EMAC_MAXFL_LEN) - 1) << EMAC_MAXFL_POS)
#define EMAC_MAXFL_UMSK       (~(((1U << EMAC_MAXFL_LEN) - 1) << EMAC_MAXFL_POS))
#define EMAC_MINFL            EMAC_MINFL
#define EMAC_MINFL_POS        (16U)
#define EMAC_MINFL_LEN        (16U)
#define EMAC_MINFL_MSK        (((1U << EMAC_MINFL_LEN) - 1) << EMAC_MINFL_POS)
#define EMAC_MINFL_UMSK       (~(((1U << EMAC_MINFL_LEN) - 1) << EMAC_MINFL_POS))

/* 0x1C : COLLCONFIG */
#define EMAC_COLLCONFIG_OFFSET (0x1C)
#define EMAC_COLLVALID         EMAC_COLLVALID
#define EMAC_COLLVALID_POS     (0U)
#define EMAC_COLLVALID_LEN     (6U)
#define EMAC_COLLVALID_MSK     (((1U << EMAC_COLLVALID_LEN) - 1) << EMAC_COLLVALID_POS)
#define EMAC_COLLVALID_UMSK    (~(((1U << EMAC_COLLVALID_LEN) - 1) << EMAC_COLLVALID_POS))
#define EMAC_MAXRET            EMAC_MAXRET
#define EMAC_MAXRET_POS        (16U)
#define EMAC_MAXRET_LEN        (4U)
#define EMAC_MAXRET_MSK        (((1U << EMAC_MAXRET_LEN) - 1) << EMAC_MAXRET_POS)
#define EMAC_MAXRET_UMSK       (~(((1U << EMAC_MAXRET_LEN) - 1) << EMAC_MAXRET_POS))

/* 0x20 : TX_BD_NUM */
#define EMAC_TX_BD_NUM_OFFSET (0x20)
#define EMAC_TXBDNUM          EMAC_TXBDNUM
#define EMAC_TXBDNUM_POS      (0U)
#define EMAC_TXBDNUM_LEN      (8U)
#define EMAC_TXBDNUM_MSK      (((1U << EMAC_TXBDNUM_LEN) - 1) << EMAC_TXBDNUM_POS)
#define EMAC_TXBDNUM_UMSK     (~(((1U << EMAC_TXBDNUM_LEN) - 1) << EMAC_TXBDNUM_POS))
#define EMAC_TXBDPTR          EMAC_TXBDPTR
#define EMAC_TXBDPTR_POS      (16U)
#define EMAC_TXBDPTR_LEN      (7U)
#define EMAC_TXBDPTR_MSK      (((1U << EMAC_TXBDPTR_LEN) - 1) << EMAC_TXBDPTR_POS)
#define EMAC_TXBDPTR_UMSK     (~(((1U << EMAC_TXBDPTR_LEN) - 1) << EMAC_TXBDPTR_POS))
#define EMAC_RXBDPTR          EMAC_RXBDPTR
#define EMAC_RXBDPTR_POS      (24U)
#define EMAC_RXBDPTR_LEN      (7U)
#define EMAC_RXBDPTR_MSK      (((1U << EMAC_RXBDPTR_LEN) - 1) << EMAC_RXBDPTR_POS)
#define EMAC_RXBDPTR_UMSK     (~(((1U << EMAC_RXBDPTR_LEN) - 1) << EMAC_RXBDPTR_POS))

/* 0x28 : MIIMODE */
#define EMAC_MIIMODE_OFFSET (0x28)
#define EMAC_CLKDIV         EMAC_CLKDIV
#define EMAC_CLKDIV_POS     (0U)
#define EMAC_CLKDIV_LEN     (8U)
#define EMAC_CLKDIV_MSK     (((1U << EMAC_CLKDIV_LEN) - 1) << EMAC_CLKDIV_POS)
#define EMAC_CLKDIV_UMSK    (~(((1U << EMAC_CLKDIV_LEN) - 1) << EMAC_CLKDIV_POS))
#define EMAC_MIINOPRE       EMAC_MIINOPRE
#define EMAC_MIINOPRE_POS   (8U)
#define EMAC_MIINOPRE_LEN   (1U)
#define EMAC_MIINOPRE_MSK   (((1U << EMAC_MIINOPRE_LEN) - 1) << EMAC_MIINOPRE_POS)
#define EMAC_MIINOPRE_UMSK  (~(((1U << EMAC_MIINOPRE_LEN) - 1) << EMAC_MIINOPRE_POS))

/* 0x2C : MIICOMMAND */
#define EMAC_MIICOMMAND_OFFSET (0x2C)
#define EMAC_SCANSTAT          EMAC_SCANSTAT
#define EMAC_SCANSTAT_POS      (0U)
#define EMAC_SCANSTAT_LEN      (1U)
#define EMAC_SCANSTAT_MSK      (((1U << EMAC_SCANSTAT_LEN) - 1) << EMAC_SCANSTAT_POS)
#define EMAC_SCANSTAT_UMSK     (~(((1U << EMAC_SCANSTAT_LEN) - 1) << EMAC_SCANSTAT_POS))
#define EMAC_RSTAT             EMAC_RSTAT
#define EMAC_RSTAT_POS         (1U)
#define EMAC_RSTAT_LEN         (1U)
#define EMAC_RSTAT_MSK         (((1U << EMAC_RSTAT_LEN) - 1) << EMAC_RSTAT_POS)
#define EMAC_RSTAT_UMSK        (~(((1U << EMAC_RSTAT_LEN) - 1) << EMAC_RSTAT_POS))
#define EMAC_WCTRLDATA         EMAC_WCTRLDATA
#define EMAC_WCTRLDATA_POS     (2U)
#define EMAC_WCTRLDATA_LEN     (1U)
#define EMAC_WCTRLDATA_MSK     (((1U << EMAC_WCTRLDATA_LEN) - 1) << EMAC_WCTRLDATA_POS)
#define EMAC_WCTRLDATA_UMSK    (~(((1U << EMAC_WCTRLDATA_LEN) - 1) << EMAC_WCTRLDATA_POS))

/* 0x30 : MIIADDRESS */
#define EMAC_MIIADDRESS_OFFSET (0x30)
#define EMAC_FIAD              EMAC_FIAD
#define EMAC_FIAD_POS          (0U)
#define EMAC_FIAD_LEN          (5U)
#define EMAC_FIAD_MSK          (((1U << EMAC_FIAD_LEN) - 1) << EMAC_FIAD_POS)
#define EMAC_FIAD_UMSK         (~(((1U << EMAC_FIAD_LEN) - 1) << EMAC_FIAD_POS))
#define EMAC_RGAD              EMAC_RGAD
#define EMAC_RGAD_POS          (8U)
#define EMAC_RGAD_LEN          (5U)
#define EMAC_RGAD_MSK          (((1U << EMAC_RGAD_LEN) - 1) << EMAC_RGAD_POS)
#define EMAC_RGAD_UMSK         (~(((1U << EMAC_RGAD_LEN) - 1) << EMAC_RGAD_POS))

/* 0x34 : MIITX_DATA */
#define EMAC_MIITX_DATA_OFFSET (0x34)
#define EMAC_CTRLDATA          EMAC_CTRLDATA
#define EMAC_CTRLDATA_POS      (0U)
#define EMAC_CTRLDATA_LEN      (16U)
#define EMAC_CTRLDATA_MSK      (((1U << EMAC_CTRLDATA_LEN) - 1) << EMAC_CTRLDATA_POS)
#define EMAC_CTRLDATA_UMSK     (~(((1U << EMAC_CTRLDATA_LEN) - 1) << EMAC_CTRLDATA_POS))

/* 0x38 : MIIRX_DATA */
#define EMAC_MIIRX_DATA_OFFSET (0x38)
#define EMAC_PRSD              EMAC_PRSD
#define EMAC_PRSD_POS          (0U)
#define EMAC_PRSD_LEN          (16U)
#define EMAC_PRSD_MSK          (((1U << EMAC_PRSD_LEN) - 1) << EMAC_PRSD_POS)
#define EMAC_PRSD_UMSK         (~(((1U << EMAC_PRSD_LEN) - 1) << EMAC_PRSD_POS))

/* 0x3C : MIISTATUS */
#define EMAC_MIISTATUS_OFFSET   (0x3C)
#define EMAC_MIIM_LINKFAIL      EMAC_MIIM_LINKFAIL
#define EMAC_MIIM_LINKFAIL_POS  (0U)
#define EMAC_MIIM_LINKFAIL_LEN  (1U)
#define EMAC_MIIM_LINKFAIL_MSK  (((1U << EMAC_MIIM_LINKFAIL_LEN) - 1) << EMAC_MIIM_LINKFAIL_POS)
#define EMAC_MIIM_LINKFAIL_UMSK (~(((1U << EMAC_MIIM_LINKFAIL_LEN) - 1) << EMAC_MIIM_LINKFAIL_POS))
#define EMAC_MIIM_BUSY          EMAC_MIIM_BUSY
#define EMAC_MIIM_BUSY_POS      (1U)
#define EMAC_MIIM_BUSY_LEN      (1U)
#define EMAC_MIIM_BUSY_MSK      (((1U << EMAC_MIIM_BUSY_LEN) - 1) << EMAC_MIIM_BUSY_POS)
#define EMAC_MIIM_BUSY_UMSK     (~(((1U << EMAC_MIIM_BUSY_LEN) - 1) << EMAC_MIIM_BUSY_POS))

/* 0x40 : MAC_ADDR0 */
#define EMAC_MAC_ADDR0_OFFSET (0x40)
#define EMAC_MAC_B5           EMAC_MAC_B5
#define EMAC_MAC_B5_POS       (0U)
#define EMAC_MAC_B5_LEN       (8U)
#define EMAC_MAC_B5_MSK       (((1U << EMAC_MAC_B5_LEN) - 1) << EMAC_MAC_B5_POS)
#define EMAC_MAC_B5_UMSK      (~(((1U << EMAC_MAC_B5_LEN) - 1) << EMAC_MAC_B5_POS))
#define EMAC_MAC_B4           EMAC_MAC_B4
#define EMAC_MAC_B4_POS       (8U)
#define EMAC_MAC_B4_LEN       (8U)
#define EMAC_MAC_B4_MSK       (((1U << EMAC_MAC_B4_LEN) - 1) << EMAC_MAC_B4_POS)
#define EMAC_MAC_B4_UMSK      (~(((1U << EMAC_MAC_B4_LEN) - 1) << EMAC_MAC_B4_POS))
#define EMAC_MAC_B3           EMAC_MAC_B3
#define EMAC_MAC_B3_POS       (16U)
#define EMAC_MAC_B3_LEN       (8U)
#define EMAC_MAC_B3_MSK       (((1U << EMAC_MAC_B3_LEN) - 1) << EMAC_MAC_B3_POS)
#define EMAC_MAC_B3_UMSK      (~(((1U << EMAC_MAC_B3_LEN) - 1) << EMAC_MAC_B3_POS))
#define EMAC_MAC_B2           EMAC_MAC_B2
#define EMAC_MAC_B2_POS       (24U)
#define EMAC_MAC_B2_LEN       (8U)
#define EMAC_MAC_B2_MSK       (((1U << EMAC_MAC_B2_LEN) - 1) << EMAC_MAC_B2_POS)
#define EMAC_MAC_B2_UMSK      (~(((1U << EMAC_MAC_B2_LEN) - 1) << EMAC_MAC_B2_POS))

/* 0x44 : MAC_ADDR1 */
#define EMAC_MAC_ADDR1_OFFSET (0x44)
#define EMAC_MAC_B1           EMAC_MAC_B1
#define EMAC_MAC_B1_POS       (0U)
#define EMAC_MAC_B1_LEN       (8U)
#define EMAC_MAC_B1_MSK       (((1U << EMAC_MAC_B1_LEN) - 1) << EMAC_MAC_B1_POS)
#define EMAC_MAC_B1_UMSK      (~(((1U << EMAC_MAC_B1_LEN) - 1) << EMAC_MAC_B1_POS))
#define EMAC_MAC_B0           EMAC_MAC_B0
#define EMAC_MAC_B0_POS       (8U)
#define EMAC_MAC_B0_LEN       (8U)
#define EMAC_MAC_B0_MSK       (((1U << EMAC_MAC_B0_LEN) - 1) << EMAC_MAC_B0_POS)
#define EMAC_MAC_B0_UMSK      (~(((1U << EMAC_MAC_B0_LEN) - 1) << EMAC_MAC_B0_POS))

/* 0x48 : HASH0_ADDR */
#define EMAC_HASH0_ADDR_OFFSET (0x48)
#define EMAC_HASH0             EMAC_HASH0
#define EMAC_HASH0_POS         (0U)
#define EMAC_HASH0_LEN         (32U)
#define EMAC_HASH0_MSK         (((1U << EMAC_HASH0_LEN) - 1) << EMAC_HASH0_POS)
#define EMAC_HASH0_UMSK        (~(((1U << EMAC_HASH0_LEN) - 1) << EMAC_HASH0_POS))

/* 0x4C : HASH1_ADDR */
#define EMAC_HASH1_ADDR_OFFSET (0x4C)
#define EMAC_HASH1             EMAC_HASH1
#define EMAC_HASH1_POS         (0U)
#define EMAC_HASH1_LEN         (32U)
#define EMAC_HASH1_MSK         (((1U << EMAC_HASH1_LEN) - 1) << EMAC_HASH1_POS)
#define EMAC_HASH1_UMSK        (~(((1U << EMAC_HASH1_LEN) - 1) << EMAC_HASH1_POS))

/* 0x50 : TXCTRL */
#define EMAC_TXCTRL_OFFSET  (0x50)
#define EMAC_TXPAUSETV      EMAC_TXPAUSETV
#define EMAC_TXPAUSETV_POS  (0U)
#define EMAC_TXPAUSETV_LEN  (16U)
#define EMAC_TXPAUSETV_MSK  (((1U << EMAC_TXPAUSETV_LEN) - 1) << EMAC_TXPAUSETV_POS)
#define EMAC_TXPAUSETV_UMSK (~(((1U << EMAC_TXPAUSETV_LEN) - 1) << EMAC_TXPAUSETV_POS))
#define EMAC_TXPAUSERQ      EMAC_TXPAUSERQ
#define EMAC_TXPAUSERQ_POS  (16U)
#define EMAC_TXPAUSERQ_LEN  (1U)
#define EMAC_TXPAUSERQ_MSK  (((1U << EMAC_TXPAUSERQ_LEN) - 1) << EMAC_TXPAUSERQ_POS)
#define EMAC_TXPAUSERQ_UMSK (~(((1U << EMAC_TXPAUSERQ_LEN) - 1) << EMAC_TXPAUSERQ_POS))

struct emac_reg {
    /* 0x0 : MODE */
    union {
        struct {
            uint32_t RXEN           : 1; /* [    0],        r/w,        0x0 */
            uint32_t TXEN           : 1; /* [    1],        r/w,        0x0 */
            uint32_t NOPRE          : 1; /* [    2],        r/w,        0x0 */
            uint32_t BRO            : 1; /* [    3],        r/w,        0x1 */
            uint32_t rsvd_4         : 1; /* [    4],       rsvd,        0x0 */
            uint32_t PRO            : 1; /* [    5],        r/w,        0x0 */
            uint32_t IFG            : 1; /* [    6],        r/w,        0x0 */
            uint32_t rsvd_9_7       : 3; /* [ 9: 7],       rsvd,        0x0 */
            uint32_t FULLD          : 1; /* [   10],        r/w,        0x0 */
            uint32_t rsvd_12_11     : 2; /* [12:11],       rsvd,        0x0 */
            uint32_t CRCEN          : 1; /* [   13],        r/w,        0x1 */
            uint32_t HUGEN          : 1; /* [   14],        r/w,        0x0 */
            uint32_t PAD            : 1; /* [   15],        r/w,        0x1 */
            uint32_t RECSMALL       : 1; /* [   16],        r/w,        0x0 */
            uint32_t RMII_EN        : 1; /* [   17],        r/w,        0x0 */
            uint32_t rsvd_23_18     : 6; /* [23:18],       rsvd,        0x0 */
            uint32_t reserved_24_31 : 8; /* [31:24],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } MODE;

    /* 0x4 : INT_SOURCE */
    union {
        struct {
            uint32_t TXB           : 1;  /* [    0],        r/w,        0x0 */
            uint32_t TXE           : 1;  /* [    1],        r/w,        0x0 */
            uint32_t RXB           : 1;  /* [    2],        r/w,        0x0 */
            uint32_t RXE           : 1;  /* [    3],        r/w,        0x0 */
            uint32_t BUSY          : 1;  /* [    4],        r/w,        0x0 */
            uint32_t TXC           : 1;  /* [    5],        r/w,        0x0 */
            uint32_t RXC           : 1;  /* [    6],        r/w,        0x0 */
            uint32_t reserved_7_31 : 25; /* [31: 7],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } INT_SOURCE;

    /* 0x8 : INT_MASK */
    union {
        struct {
            uint32_t TXB_M         : 1;  /* [    0],        r/w,        0x1 */
            uint32_t TXE_M         : 1;  /* [    1],        r/w,        0x1 */
            uint32_t RXB_M         : 1;  /* [    2],        r/w,        0x1 */
            uint32_t RXE_M         : 1;  /* [    3],        r/w,        0x1 */
            uint32_t BUSY_M        : 1;  /* [    4],        r/w,        0x1 */
            uint32_t TXC_M         : 1;  /* [    5],        r/w,        0x1 */
            uint32_t RXC_M         : 1;  /* [    6],        r/w,        0x1 */
            uint32_t reserved_7_31 : 25; /* [31: 7],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } INT_MASK;

    /* 0xC : IPGT */
    union {
        struct {
            uint32_t IPGT          : 7;  /* [ 6: 0],        r/w,       0x18 */
            uint32_t reserved_7_31 : 25; /* [31: 7],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } IPGT;

    /* 0x10  reserved */
    uint8_t RESERVED0x10[8];

    /* 0x18 : PACKETLEN */
    union {
        struct {
            uint32_t MAXFL : 16; /* [15: 0],        r/w,      0x600 */
            uint32_t MINFL : 16; /* [31:16],        r/w,       0x40 */
        } BF;
        uint32_t WORD;
    } PACKETLEN;

    /* 0x1C : COLLCONFIG */
    union {
        struct {
            uint32_t COLLVALID      : 6;  /* [ 5: 0],        r/w,       0x3f */
            uint32_t reserved_6_15  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t MAXRET         : 4;  /* [19:16],        r/w,        0xf */
            uint32_t reserved_20_31 : 12; /* [31:20],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } COLLCONFIG;

    /* 0x20 : TX_BD_NUM */
    union {
        struct {
            uint32_t TXBDNUM       : 8; /* [ 7: 0],        r/w,       0x40 */
            uint32_t reserved_8_15 : 8; /* [15: 8],       rsvd,        0x0 */
            uint32_t TXBDPTR       : 7; /* [22:16],          r,        0x0 */
            uint32_t reserved_23   : 1; /* [   23],       rsvd,        0x0 */
            uint32_t RXBDPTR       : 7; /* [30:24],          r,        0x0 */
            uint32_t reserved_31   : 1; /* [   31],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TX_BD_NUM;

    /* 0x24  reserved */
    uint8_t RESERVED0x24[4];

    /* 0x28 : MIIMODE */
    union {
        struct {
            uint32_t CLKDIV        : 8;  /* [ 7: 0],        r/w,       0x64 */
            uint32_t MIINOPRE      : 1;  /* [    8],        r/w,        0x0 */
            uint32_t reserved_9_31 : 23; /* [31: 9],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } MIIMODE;

    /* 0x2C : MIICOMMAND */
    union {
        struct {
            uint32_t SCANSTAT      : 1;  /* [    0],        r/w,        0x0 */
            uint32_t RSTAT         : 1;  /* [    1],        r/w,        0x0 */
            uint32_t WCTRLDATA     : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_31 : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } MIICOMMAND;

    /* 0x30 : MIIADDRESS */
    union {
        struct {
            uint32_t FIAD           : 5;  /* [ 4: 0],        r/w,        0x0 */
            uint32_t reserved_5_7   : 3;  /* [ 7: 5],       rsvd,        0x0 */
            uint32_t RGAD           : 5;  /* [12: 8],        r/w,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } MIIADDRESS;

    /* 0x34 : MIITX_DATA */
    union {
        struct {
            uint32_t CTRLDATA       : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } MIITX_DATA;

    /* 0x38 : MIIRX_DATA */
    union {
        struct {
            uint32_t PRSD           : 16; /* [15: 0],          r,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } MIIRX_DATA;

    /* 0x3C : MIISTATUS */
    union {
        struct {
            uint32_t MIIM_LINKFAIL : 1;  /* [    0],          r,        0x0 */
            uint32_t MIIM_BUSY     : 1;  /* [    1],          r,        0x0 */
            uint32_t reserved_2_31 : 30; /* [31: 2],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } MIISTATUS;

    /* 0x40 : MAC_ADDR0 */
    union {
        struct {
            uint32_t MAC_B5 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t MAC_B4 : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t MAC_B3 : 8; /* [23:16],        r/w,        0x0 */
            uint32_t MAC_B2 : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } MAC_ADDR0;

    /* 0x44 : MAC_ADDR1 */
    union {
        struct {
            uint32_t MAC_B1         : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t MAC_B0         : 8;  /* [15: 8],        r/w,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } MAC_ADDR1;

    /* 0x48 : HASH0_ADDR */
    union {
        struct {
            uint32_t HASH0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } HASH0_ADDR;

    /* 0x4C : HASH1_ADDR */
    union {
        struct {
            uint32_t HASH1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } HASH1_ADDR;

    /* 0x50 : TXCTRL */
    union {
        struct {
            uint32_t TXPAUSETV      : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t TXPAUSERQ      : 1;  /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31 : 15; /* [31:17],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TXCTRL;
};

typedef volatile struct emac_reg emac_reg_t;

#endif /* __EMAC_REG_H__ */
