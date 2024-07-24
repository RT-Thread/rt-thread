/*!
    \file    gd32h7xx_axiim.h
    \brief   definitions for AXIIM(AXI interconnect matrix)

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32H7XX_AXIIM_H
#define GD32H7XX_AXIIM_H

#include "gd32h7xx.h"

/* AXI interconnect matrix definitions */
#define AXIIM_BASE                          ((uint32_t)0x51000000U)                                 /*!< AXI interconnect matrix base address */
#define AXIIM                               AXIIM_BASE                                              /*!< AXI interconnect matrix definition */

/* registers definitions */
#define AXI_PERIPH_ID4                      REG32(AXIIM + 0x00001FD0U)                              /*!< AXI peripheral ID4 register */
#define AXI_PERIPH_ID0                      REG32(AXIIM + 0x00001FE0U)                              /*!< AXI peripheral ID0 register */
#define AXI_PERIPH_ID1                      REG32(AXIIM + 0x00001FE4U)                              /*!< AXI peripheral ID1 register */
#define AXI_PERIPH_ID2                      REG32(AXIIM + 0x00001FE8U)                              /*!< AXI peripheral ID2 register */
#define AXI_PERIPH_ID3                      REG32(AXIIM + 0x00001FECU)                              /*!< AXI peripheral ID3 register */

#define AXI_COMP_ID0                        REG32(AXIIM + 0x00001FF0U)                              /*!< AXI componet ID0 register */
#define AXI_COMP_ID1                        REG32(AXIIM + 0x00001FF4U)                              /*!< AXI componet ID1 register */
#define AXI_COMP_ID2                        REG32(AXIIM + 0x00001FF8U)                              /*!< AXI componet ID2 register */
#define AXI_COMP_ID3                        REG32(AXIIM + 0x00001FFCU)                              /*!< AXI componet ID3 register */

#define AXI_MPXBM_ISS_CTL(mportx)           REG32(AXIIM + 0x00002008U + 0x00001000U * (mportx))     /*!< AXI master port x bus matrix issuing functionality control register */
#define AXI_MP0BM_ISS_CTL                   REG32(AXIIM + 0x00002008U)                              /*!< AXI master port 0 bus matrix issuing functionality control register */
#define AXI_MP1BM_ISS_CTL                   REG32(AXIIM + 0x00003008U)                              /*!< AXI master port 1 bus matrix issuing functionality control register */
#define AXI_MP2BM_ISS_CTL                   REG32(AXIIM + 0x00004008U)                              /*!< AXI master port 2 bus matrix issuing functionality control register */
#define AXI_MP3BM_ISS_CTL                   REG32(AXIIM + 0x00005008U)                              /*!< AXI master port 3 bus matrix issuing functionality control register */
#define AXI_MP4BM_ISS_CTL                   REG32(AXIIM + 0x00006008U)                              /*!< AXI master port 4 bus matrix issuing functionality control register */
#define AXI_MP5BM_ISS_CTL                   REG32(AXIIM + 0x00007008U)                              /*!< AXI master port 5 bus matrix issuing functionality control register */
#define AXI_MP6BM_ISS_CTL                   REG32(AXIIM + 0x00008008U)                              /*!< AXI master port 6 bus matrix issuing functionality control register */
#define AXI_MP7BM_ISS_CTL                   REG32(AXIIM + 0x00009008U)                              /*!< AXI master port 7 bus matrix issuing functionality control register */

#define AXI_MPXBM_CTL(mportx)               REG32(AXIIM + 0x00002024U + 0x00001000U * (mportx))     /*!< AXI master port x bus matrix functionality control register */
#define AXI_MP0BM_CTL                       REG32(AXIIM + 0x00002024U)                              /*!< AXI master port 0 bus matrix functionality control register */
#define AXI_MP1BM_CTL                       REG32(AXIIM + 0x00003024U)                              /*!< AXI master port 1 bus matrix functionality control register */
#define AXI_MP6BM_CTL                       REG32(AXIIM + 0x00008024U)                              /*!< AXI master port 6 bus matrix functionality control register */
#define AXI_MP7BM_CTL                       REG32(AXIIM + 0x00009024U)                              /*!< AXI master port 7 bus matrix functionality control register */

#define AXI_MPX_LB_CTL(mportx)              REG32(AXIIM + 0x0000202CU + 0x00001000U * (mportx))     /*!< AXI master port x long burst functionality control register */
#define AXI_MP0_LB_CTL                      REG32(AXIIM + 0x0000202CU)                              /*!< AXI master port 0 long burst functionality control register */
#define AXI_MP1_LB_CTL                      REG32(AXIIM + 0x0000302CU)                              /*!< AXI master port 1 long burst functionality control register */

#define AXI_MPX_ISS_CTL(mportx)             REG32(AXIIM + 0x00002108U + 0x00001000U * (mportx))     /*!< AXI master port x issuing functionality control register */
#define AXI_MP0_ISS_CTL                     REG32(AXIIM + 0x00002108U)                              /*!< AXI master port 0 issuing functionality control register */
#define AXI_MP1_ISS_CTL                     REG32(AXIIM + 0x00003108U)                              /*!< AXI master port 1 issuing functionality control register */
#define AXI_MP6_ISS_CTL                     REG32(AXIIM + 0x00008108U)                              /*!< AXI master port 6 issuing functionality control register */
#define AXI_MP7_ISS_CTL                     REG32(AXIIM + 0x00009108U)                              /*!< AXI master port 7 issuing functionality control register */

#define AXI_SPX_CTL(sportx)                 REG32(AXIIM + 0x00042024U + 0x00001000U * (sportx))     /*!< AXI slave port x functionality control register */
#define AXI_SP0_CTL                         REG32(AXIIM + 0x00042024U)                              /*!< AXI slave port 0 functionality control register */
#define AXI_SP2_CTL                         REG32(AXIIM + 0x00044024U)                              /*!< AXI slave port 2 functionality control register */

#define AXI_SPX_AHBISS_CTL(sportx)          REG32(AXIIM + 0x00042028U + 0x00001000U * (sportx))     /*!< AXI slave port x AHB issuing functionality control register */
#define AXI_SP0_AHBISS_CTL                  REG32(AXIIM + 0x00042028U)                              /*!< AXI slave port 0 AHB issuing functionality control register */
#define AXI_SP2_AHBISS_CTL                  REG32(AXIIM + 0x00044028U)                              /*!< AXI slave port 2 AHB issuing functionality control register */

/* AXI slave port x = 0 to 5 */
#define AXI_SPX_RDQOS_CTL(sportx)           REG32(AXIIM + 0x00042100U + 0x00001000U * (sportx))     /*!< AXI slave port x read QOS control register */
#define AXI_SPX_WRQOS_CTL(sportx)           REG32(AXIIM + 0x00042104U + 0x00001000U * (sportx))     /*!< AXI slave port x write QOS control register */
#define AXI_SPX_ISS_CTL(sportx)             REG32(AXIIM + 0x00042108U + 0x00001000U * (sportx))     /*!< AXI slave port x issuing functionality control register */

#define AXI_PERIPH_ID4_JEP106CCODE          BITS(0,3)                                               /*!< JEP106 continuation code */
#define AXI_PERIPH_ID4_4KBCNT               BITS(4,7)                                               /*!< register file size */

#define AXI_PERIPH_ID0_PARTNUM              BITS(0,7)                                               /*!< part number bit[7:0] */

#define AXI_PERIPH_ID1_PARTNUM              BITS(0,3)                                               /*!< part number bit[11:8] */
#define AXI_PERIPH_ID1_JEP106ID             BITS(4,7)                                               /*!< JEP106 identity[3:0] */

#define AXI_PERIPH_ID2_JEP106ID             BITS(0,2)                                               /*!< JEP106 identity[6:4] */
#define AXI_PERIPH_ID2_JEP106CF             BIT(3)                                                  /*!< JEP106 code flag */
#define AXI_PERIPH_ID2_PARTREV              BITS(4,7)                                               /*!< part revision */

#define AXI_PERIPH_ID3_CUSTMOD              BITS(0,3)                                               /*!< customer modification[3:0] */
#define AXI_PERIPH_ID3_CUSTREV              BITS(4,7)                                               /*!< customer version */

#define AXI_COMP_ID0_PREAMB                 BITS(0,7)                                               /*!< preamble bits[7:0] */

#define AXI_COMP_ID1_PREAMB                 BITS(0,3)                                               /*!< preamble bits[11:8] */
#define AXI_COMP_ID1_CLASS                  BITS(4,7)                                               /*!< component class */

#define AXI_COMP_ID2_PREAMB                 BITS(0,7)                                               /*!< preamble bits[19:12] */

#define AXI_COMP_ID3_PREAMB                 BITS(0,7)                                               /*!< preamble bits[27:20] */

#define AXI_MPXBM_ISS_CTL_RD_ISSOV          BIT(0)                                                  /*!< override target read issuing function */
#define AXI_MPXBM_ISS_CTL_WR_ISSOV          BIT(1)                                                  /*!< override target write issuing function */

#define AXI_MPXBM_CTL_BPDIS                 BIT(0)                                                  /*!< beats packing function disable configure */

#define AXI_MPX_LB_CTL_LBEN                 BIT(0)                                                  /*!< control long burst function */

#define AXI_MPX_ISS_CTL_RD_ISSOV            BIT(0)                                                  /*!< override AMIB read issuing function */
#define AXI_MPX_ISS_CTL_WR_ISSOV            BIT(1)                                                  /*!< override AMIB write issuing function */

#define AXI_SPX_CTL_TRANSALT                BIT(0)                                                  /*!< slave port transaction alteration configure bit */

#define AXI_SPX_AHBISS_CTL_WR_AHB_ISSOV     BIT(0)                                                  /*!< converts AHB-Lite write transaction to single beat AXI transaction */
#define AXI_SPX_AHBISS_CTL_RD_AHB_ISSOV     BIT(1)                                                  /*!< converts AHB-Lite read transaction to single beat AXI transaction */

#define AXI_SPX_RDQOS_CTL_RDQOS             BITS(0,3)                                               /*!< slave port read channel QoS configure bits */

#define AXI_SPX_WRQOS_CTL_WRQOS             BITS(0,3)                                               /*!< slave port write channel QoS configure bits */

#define AXI_SPX_ISS_CTL_RD_ISSOV            BIT(0)                                                  /*!< slave port override ASIB read issuing control bit */
#define AXI_SPX_ISS_CTL_WR_ISSOV            BIT(1)                                                  /*!< slave port override ASIB write issuing control bit */

/* AXI master port select */
typedef enum
{
    MASTER_PORT0 = 0U,                                   /*!< AXI master port 0 */
    MASTER_PORT1,                                        /*!< AXI master port 1 */
    MASTER_PORT2,                                        /*!< AXI master port 2 */
    MASTER_PORT3,                                        /*!< AXI master port 3 */
    MASTER_PORT4,                                        /*!< AXI master port 4 */
    MASTER_PORT5,                                        /*!< AXI master port 5 */
    MASTER_PORT6,                                        /*!< AXI master port 6 */
    MASTER_PORT7                                         /*!< AXI master port 7 */
} master_port_enum;

/* AXI slave port select */
typedef enum
{
    SLAVE_PORT0 = 0U,                                    /*!< AXI slave port 0 */
    SLAVE_PORT1,                                         /*!< AXI slave port 1 */
    SLAVE_PORT2,                                         /*!< AXI slave port 2 */
    SLAVE_PORT3,                                         /*!< AXI slave port 3 */
    SLAVE_PORT4,                                         /*!< AXI slave port 4 */
    SLAVE_PORT5                                          /*!< AXI slave port 5 */
} slave_port_enum;

/* AXI master port x bus mutrix read issuing capability is set to 1, mportx: MASTER_PORTx (x=0..7) */
#define __AXI_MPXBM_READ_ISSOV_ENABLE(mportx)                         {AXI_MPXBM_ISS_CTL(mportx) |= AXI_MPXBM_ISS_CTL_RD_ISSOV}
/* AXI master port x bus mutrix read issuing capability is normal, mportx: MASTER_PORTx (x=0..7) */
#define __AXI_MPXBM_READ_ISSOV_DISABLE(mportx)                        {AXI_MPXBM_ISS_CTL(mportx) &= ~AXI_MPXBM_ISS_CTL_RD_ISSOV}

/* AXI master port x bus mutrix write issuing capability is set to 1, mportx: MASTER_PORTx (x=0..7) */
#define __AXI_MPXBM_WRITE_ISSOV_ENABLE(mportx)                        {AXI_MPXBM_ISS_CTL(mportx) |= AXI_MPXBM_ISS_CTL_WR_ISSOV}
/* AXI master port x bus mutrix write issuing capability is normal, mportx: MASTER_PORTx (x=0..7) */
#define __AXI_MPXBM_WRITE_ISSOV_DISABLE(mportx)                       {AXI_MPXBM_ISS_CTL(mportx) &= ~AXI_MPXBM_ISS_CTL_WR_ISSOV}

/* enable AXI master port x beats packing function, mportx: MASTER_PORTx (x=0,1,6,7) */
#define __AXI_MPXBM_BEATS_PACKING_ENABLE(mportx)                      {AXI_MPXBM_CTL(mportx) &= ~AXI_MPXBM_CTL_BPDIS}
/* disable AXI master port x beats packing function, mportx: MASTER_PORTx (x=0,1,6,7) */
#define __AXI_MPXBM_BEATS_PACKING_DISABLE(mportx)                     {AXI_MPXBM_CTL(mportx) |= AXI_MPXBM_CTL_BPDIS}

/* enable AXI master port long burst function, mportx: MASTER_PORTx (x=0,1) */
#define __AXI_MPX_LONG_BURST_ENABLE(mportx)                           {AXI_MPX_LB_CTL(mportx) |= AXI_MPX_LB_CTL_LBEN}
/* disable AXI master port x long burst function, mportx: MASTER_PORTx (x=0,1) */
#define __AXI_MPX_LONG_BURST_DISABLE(mportx)                          {AXI_MPX_LB_CTL(mportx) &= ~AXI_MPX_LB_CTL_LBEN}

/* force AMIB read issuing capability to 1, mportx: MASTER_PORTx (x=0,1,2,7) */
#define __AXI_MPX_READ_ISSOV_ENABLE(mportx)                           {AXI_MPX_ISS_CTL(mportx) |= AXI_MPX_ISS_CTL_RD_ISSOV}
/* AMIB read issuing capability is normal, mportx: MASTER_PORTx (x=0,1,2,7) */
#define __AXI_MPX_READ_ISSOV_DISABLE(mportx)                          {AXI_MPX_ISS_CTL(mportx) &= ~AXI_MPX_ISS_CTL_RD_ISSOV}

/* force AMIB write issuing capability to 1, mportx: MASTER_PORTx (x=0,1,2,7) */
#define __AXI_MPX_WRITE_ISSOV_ENABLE(mportx)                          {AXI_MPX_ISS_CTL(mportx) |= AXI_MPX_ISS_CTL_WR_ISSOV}
/* AMIB write issuing capability is normal, mportx: MASTER_PORTx (x=0,1,2,7) */
#define __AXI_MPX_WRITE_ISSOV_DISABLE(mportx)                         {AXI_MPX_ISS_CTL(mportx) &= ~AXI_MPX_ISS_CTL_WR_ISSOV}

/* enable AXI slave port transaction alteration function, mportx: SLAVE_PORTx (x=0,2) */
#define __AXI_SPX_TRANSACTION_ALTER_ENABLE(sportx)                    {AXI_SPX_CTL(sportx) |= AXI_SPX_CTL_TRANSALT}
/* AXI slave port transaction alteration function in normal operation, mportx: SLAVE_PORTx (x=0,2) */
#define __AXI_SPX_TRANSACTION_ALTER_DISABLE(sportx)                   {AXI_SPX_CTL(sportx) &= ~AXI_SPX_CTL_TRANSALT}

/* enable convert AHB-Lite write transaction to single beat AXI transaction, mportx: SLAVE_PORTx (x=0,2) */
#define __AXI_SPX_CONVERT_AHB_WR_TO_SINGLE_BEAT_TRANS_ENABLE(sportx)  {AXI_SPX_AHBISS_CTL(sportx) |= AXI_SPX_AHBISS_CTL_WR_AHB_ISSOV}
/* disable convert AHB-Lite write transaction to single beat AXI transaction, mportx: SLAVE_PORTx (x=0,2) */
#define __AXI_SPX_CONVERT_AHB_WR_TO_SINGLE_BEAT_TRANS_DISABLE(sportx) {AXI_SPX_AHBISS_CTL(sportx) &= ~AXI_SPX_AHBISS_CTL_WR_AHB_ISSOV}

/* enable convert AHB-Lite read transaction to single beat AXI transaction, mportx: SLAVE_PORTx (x=0,2) */
#define __AXI_SPX_CONVERT_AHB_RD_TO_SINGLE_BEAT_TRANS_ENABLE(sportx)  {AXI_SPX_AHBISS_CTL(sportx) |= AXI_SPX_AHBISS_CTL_RD_AHB_ISSOV}
/* disable convert AHB-Lite read transaction to single beat AXI transaction, mportx: SLAVE_PORTx (x=0,2) */
#define __AXI_SPX_CONVERT_AHB_RD_TO_SINGLE_BEAT_TRANS_DISABLE(sportx) {AXI_SPX_AHBISS_CTL(sportx) &= ~AXI_SPX_AHBISS_CTL_RD_AHB_ISSOV}

/* configure slave port read channel QoS, sportx: SLAVE_PORTx (x=0..5), priority: 0x0~0xF */
#define __AXI_SPX_READ_QOS_SET(sportx, priority)                      {AXI_SPX_RDQOS_CTL(sportx) |= ( (priority) & AXI_SPX_RDQOS_CTL_RDQOS)}

/* configure slave port write channel QoS, sportx: SLAVE_PORTx (x=0..5), priority: 0x0~0xF */
#define __AXI_SPX_WRITE_QOS_SET(sportx, priority)                     {AXI_SPX_WRQOS_CTL(sportx) |= ( (priority) & AXI_SPX_WRQOS_CTL_WRQOS)}

/* force ASIB read issuing capability to 1, sportx: SLAVE_PORTx (x=0..5) */
#define __AXI_SPX_READ_ISSOV_ENABLE(sportx)                           {AXI_SPX_ISS_CTL(sportx) |= AXI_SPX_ISS_CTL_RD_ISSOV}
/* ASIB read issuing capability in normal operation, mportx: SLAVE_PORTx (x=0..5) */
#define __AXI_SPX_READ_ISSOV_DISABLE(sportx)                          {AXI_SPX_ISS_CTL(sportx) &= ~AXI_SPX_ISS_CTL_RD_ISSOV}

/* force ASIB write issuing capability to 1, sportx: SLAVE_PORTx (x=0..5) */
#define __AXI_SPX_WRITE_ISSOV_ENABLE(sportx)                          {AXI_SPX_ISS_CTL(sportx) |= AXI_SPX_ISS_CTL_WD_ISSOV}
/* ASIB write issuing capability in normal operation, mportx: SLAVE_PORTx (x=0..5) */
#define __AXI_SPX_WRITE_ISSOV_DISABLE(sportx)                         {AXI_SPX_ISS_CTL(sportx) &= ~AXI_SPX_ISS_CTL_WD_ISSOV}

#endif /* GD32H7XX_AXIIM_H */
