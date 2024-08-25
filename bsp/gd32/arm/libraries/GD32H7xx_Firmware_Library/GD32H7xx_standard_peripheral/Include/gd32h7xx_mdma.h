/*!
    \file    gd32h7xx_mdma.h
    \brief   definitions for the MDMA

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

#ifndef GD32H7XX_MDMA_H
#define GD32H7XX_MDMA_H

#include "gd32h7xx.h"

/* MDMA definitions */
#define MDMA                                (MDMA_BASE)                                                     /*!< MDMA base address */

/* registers definitions */
#define MDMA_GINTF                          REG32(MDMA + 0x00000000U)                                       /*!< MDMA global interrupt flag register */

#define MDMA_CHXSTAT0(mdma_chx)             REG32(MDMA + 0x00000040U + (0x40U * (mdma_chx)))                /*!< MDMA channel x status register 0 */
#define MDMA_CHXSTATC(mdma_chx)             REG32(MDMA + 0x00000044U + (0x40U * (mdma_chx)))                /*!< MDMA channel x status clear register */
#define MDMA_CHXSTAT1(mdma_chx)             REG32(MDMA + 0x00000048U + (0x40U * (mdma_chx)))                /*!< MDMA channel x status register 1*/
#define MDMA_CHXCTL0(mdma_chx)              REG32(MDMA + 0x0000004CU + (0x40U * (mdma_chx)))                /*!< MDMA channel x control register 0 */
#define MDMA_CHXCFG(mdma_chx)               REG32(MDMA + 0x00000050U + (0x40U * (mdma_chx)))                /*!< MDMA channel x configure register */
#define MDMA_CHXBTCFG(mdma_chx)             REG32(MDMA + 0x00000054U + (0x40U * (mdma_chx)))                /*!< MDMA channel x block transfer configure register */
#define MDMA_CHXSADDR(mdma_chx)             REG32(MDMA + 0x00000058U + (0x40U * (mdma_chx)))                /*!< MDMA channel x source address register */
#define MDMA_CHXDADDR(mdma_chx)             REG32(MDMA + 0x0000005CU + (0x40U * (mdma_chx)))                /*!< MDMA channel x destination address register */
#define MDMA_CHXMBADDRU(mdma_chx)           REG32(MDMA + 0x00000060U + (0x40U * (mdma_chx)))                /*!< MDMA channel x multi-block address update register */
#define MDMA_CHXLADDR(mdma_chx)             REG32(MDMA + 0x00000064U + (0x40U * (mdma_chx)))                /*!< MDMA channel x link address register */
#define MDMA_CHXCTL1(mdma_chx)              REG32(MDMA + 0x00000068U + (0x40U * (mdma_chx)))                /*!< MDMA channel x control register 1 */
#define MDMA_CHXMADDR(mdma_chx)             REG32(MDMA + 0x00000070U + (0x40U * (mdma_chx)))                /*!< MDMA channel x mask address register */
#define MDMA_CHXMDATA(mdma_chx)             REG32(MDMA + 0x00000074U + (0x40U * (mdma_chx)))                /*!< MDMA channel x mask data register */

/* bits definitions */
/* MDMA_GINTF */
#define MDMA_GINTF_GIF0                     BIT(0)                                                          /*!< global interrupt flag of channel 0 */
#define MDMA_GINTF_GIF1                     BIT(1)                                                          /*!< global interrupt flag of channel 1 */
#define MDMA_GINTF_GIF2                     BIT(2)                                                          /*!< global interrupt flag of channel 2 */
#define MDMA_GINTF_GIF3                     BIT(3)                                                          /*!< global interrupt flag of channel 3 */
#define MDMA_GINTF_GIF4                     BIT(4)                                                          /*!< global interrupt flag of channel 4 */
#define MDMA_GINTF_GIF5                     BIT(5)                                                          /*!< global interrupt flag of channel 5 */
#define MDMA_GINTF_GIF6                     BIT(6)                                                          /*!< global interrupt flag of channel 6 */
#define MDMA_GINTF_GIF7                     BIT(7)                                                          /*!< global interrupt flag of channel 7 */
#define MDMA_GINTF_GIF8                     BIT(8)                                                          /*!< global interrupt flag of channel 8 */
#define MDMA_GINTF_GIF9                     BIT(9)                                                          /*!< global interrupt flag of channel 9 */
#define MDMA_GINTF_GIF10                    BIT(10)                                                         /*!< global interrupt flag of channel 10 */
#define MDMA_GINTF_GIF11                    BIT(11)                                                         /*!< global interrupt flag of channel 11 */
#define MDMA_GINTF_GIF12                    BIT(12)                                                         /*!< global interrupt flag of channel 12 */
#define MDMA_GINTF_GIF13                    BIT(13)                                                         /*!< global interrupt flag of channel 13 */
#define MDMA_GINTF_GIF14                    BIT(14)                                                         /*!< global interrupt flag of channel 14 */
#define MDMA_GINTF_GIF15                    BIT(15)                                                         /*!< global interrupt flag of channel 15 */

/* MDMA_CHxSTAT0,x=0..15 */
#define MDMA_CHXSTAT0_ERR                   BIT(0)                                                          /*!< channel x transfer error flag */
#define MDMA_CHXSTAT0_CHTCF                 BIT(1)                                                          /*!< channel x channel transfer complete flag */
#define MDMA_CHXSTAT0_MBTCF                 BIT(2)                                                          /*!< channel x multi-block transfer complete flag */
#define MDMA_CHXSTAT0_BTCF                  BIT(3)                                                          /*!< channel x block transfer complete flag */
#define MDMA_CHXSTAT0_TCF                   BIT(4)                                                          /*!< channel x buffer transfer complete flag */
#define MDMA_CHXSTAT0_REQAF                 BIT(16)                                                         /*!< channel x request active flag */

/* MDMA_CHxSTATC,x=0..15 */
#define MDMA_CHXSTATC_ERRC                  BIT(0)                                                          /*!< channel x transfer error flag clear */
#define MDMA_CHXSTATC_CHTCFC                BIT(1)                                                          /*!< channel x channel transfer complete flag clear */
#define MDMA_CHXSTATC_MBTCFC                BIT(2)                                                          /*!< channel x multi-block transfer complete flag clear */
#define MDMA_CHXSTATC_BTCFC                 BIT(3)                                                          /*!< channel x block transfer complete flag clear */
#define MDMA_CHXSTATC_TCFC                  BIT(4)                                                          /*!< channel x buffer transfer complete flag clear */

/* MDMA_CHxSTAT1,x=0..15 */
#define MDMA_CHXSTAT1_ERRADDR               BITS(0,6)                                                       /*!< transfer error address */
#define MDMA_CHXSTAT1_TERRD                 BIT(7)                                                          /*!< transfer error direction */
#define MDMA_CHXSTAT1_LDTERR                BIT(8)                                                          /*!< link data transfer error flag in the last transfer of the channel */
#define MDMA_CHXSTAT1_MDTERR                BIT(9)                                                          /*!< mask data error flag */
#define MDMA_CHXSTAT1_ASERR                 BIT(10)                                                         /*!< address and size error flag */
#define MDMA_CHXSTAT1_BZERR                 BIT(11)                                                         /*!< block size error flag */

/* MDMA_CHxCTL0,x=0..15 */
#define MDMA_CHXCTL0_CHEN                   BIT(0)                                                          /*!< channel enable */
#define MDMA_CHXCTL0_ERRIE                  BIT(1)                                                          /*!< transfer error interrupt enable */
#define MDMA_CHXCTL0_CHTCIE                 BIT(2)                                                          /*!< channel transfer complete interrupt enable */
#define MDMA_CHXCTL0_MBTCIE                 BIT(3)                                                          /*!< multi-block transfer complete interrupt enable */
#define MDMA_CHXCTL0_BTCIE                  BIT(4)                                                          /*!< block transfer complete interrupt enable */
#define MDMA_CHXCTL0_TCIE                   BIT(5)                                                          /*!< buffer transfer complete interrupt enable */
#define MDMA_CHXCTL0_PRIO                   BITS(6,7)                                                       /*!< priority level */
#define MDMA_CHXCTL0_SMODEN                 BIT(8)                                                          /*!< secure mode enable */
#define MDMA_CHXCTL0_BES                    BIT(12)                                                         /*!< byte endianess swapping in half word */
#define MDMA_CHXCTL0_HWES                   BIT(13)                                                         /*!< half word endianess swapping in word */
#define MDMA_CHXCTL0_WES                    BIT(14)                                                         /*!< word endianess swapping in double word */
#define MDMA_CHXCTL0_SWREQ                  BIT(16)                                                         /*!< software request */

/* MDMA_CHxCFG,x=0..15 */
#define MDMA_CHXCFG_SIMOD                   BITS(0,1)                                                       /*!< source increment mode */
#define MDMA_CHXCFG_DIMOD                   BITS(2,3)                                                       /*!< destination increment mode */
#define MDMA_CHXCFG_SWIDTH                  BITS(4,5)                                                       /*!< data size of source */
#define MDMA_CHXCFG_DWIDTH                  BITS(6,7)                                                       /*!< data size of destination */
#define MDMA_CHXCFG_SIOS                    BITS(8,9)                                                       /*!< offset size of source increment */
#define MDMA_CHXCFG_DIOS                    BITS(10,11)                                                     /*!< offset size of destination  increment */
#define MDMA_CHXCFG_SBURST                  BITS(12,14)                                                     /*!< transfer burst type of source */
#define MDMA_CHXCFG_DBURST                  BITS(15,17)                                                     /*!< transfer burst type of destination */
#define MDMA_CHXCFG_BTLEN                   BITS(18,24)                                                     /*!< buffer transfer length */
#define MDMA_CHXCFG_PKEN                    BIT(25)                                                         /*!< pack enable */
#define MDMA_CHXCFG_PAMOD                   BITS(26,27)                                                     /*!< padding and alignement mode */
#define MDMA_CHXCFG_TRIGMOD                 BITS(28,29)                                                     /*!< trigger mode */
#define MDMA_CHXCFG_SWREQMOD                BIT(30)                                                         /*!< software request mode */
#define MDMA_CHXCFG_BWMOD                   BIT(31)                                                         /*!< bufferable write mode */

/* MDMA_CHxBTCFG,x=0..15 */
#define MDMA_CHXBTCFG_TBNUM                 BITS(0,16)                                                      /*!< transfer byte number in block */
#define MDMA_CHXBTCFG_SADDRUM               BIT(18)                                                         /*!< multi-block source address update mode */
#define MDMA_CHXBTCFG_DADDRUM               BIT(19)                                                         /*!< multi-block destination address update mode */
#define MDMA_CHXBTCFG_BRNUM                 BITS(20,31)                                                     /*!< multi-block number */

/* MDMA_CHxSADDR,x=0..15 */
#define MDMA_CHXSADDR_SADDR                 BITS(0,31)                                                      /*!< source address */

/* MDMA_CHxDADDR,x=0..15 */
#define MDMA_CHXDADDR_DADDR                 BITS(0,31)                                                      /*!< destination address */

/* MDMA_CHxMBADDRU,x=0..15 */
#define MDMA_CHXMBADDRU_SADDRUV             BITS(0,15)                                                      /*!< source address update value */
#define MDMA_CHXMBADDRU_DADDRUV             BITS(16,31)                                                     /*!< destination address update value */

/* MDMA_CHxLADDR,x=0..15 */
#define MDMA_CHXLADDR_LADDR                 BITS(0,31)                                                      /*!< link address */

/* MDMA_CHxCTL1,x=0..15 */
#define MDMA_CHXCTL1_TRIGSEL                BITS(0,5)                                                       /*!< trigger select */
#define MDMA_CHXCTL1_SBSEL                  BIT(16)                                                         /*!< source bus select */
#define MDMA_CHXCTL1_DBSEL                  BIT(17)                                                         /*!< destination bus select */

/* MDMA_CHxMADDR,x=0..15 */
#define MDMA_CHXMADDR_MADDR                 BITS(0,31)                                                      /*!< mask address */

/* MDMA_CHxMDATA,x=0..15 */
#define MDMA_CHXMDATA_MDATA                 BITS(0,31)                                                      /*!< mask data */

/* constants definitions */
/* MDMA configuration structure definition */
typedef struct {
    uint32_t request;                                                                                       /*!< specifies the MDMA request */
    uint32_t trans_trig_mode;                                                                               /*!< specifies the trigger transfer mode */
    uint32_t priority;                                                                                      /*!< specifies the software priority for the MDMA channelx */
    uint32_t endianness;                                                                                    /*!< specifies if the MDMA transactions preserve the little endianness */
    uint32_t source_inc;                                                                                    /*!< specifies the source increment mode */
    uint32_t dest_inc;                                                                                      /*!< specifies the destination increment mode */
    uint32_t source_data_size;                                                                              /*!< specifies the source data size */
    uint32_t dest_data_dize;                                                                                /*!< specifies the destination data size */
    uint32_t data_alignment;                                                                                /*!< specifies the source to destination memory data packing/padding mode */
    uint32_t buff_trans_len;                                                                                /*!< specifies the buffer transfer length (number of bytes) */
    uint32_t source_burst;                                                                                  /*!< specifies the burst transfer configuration for the source memory transfers */
    uint32_t dest_burst;                                                                                    /*!< specifies the burst transfer configuration for the destination memory transfers */
    uint32_t mask_addr;                                                                                     /*!< mask address */
    uint32_t mask_data;                                                                                     /*!< mask data */
    uint32_t source_addr;                                                                                   /*!< specifies the source address */
    uint32_t destination_addr;                                                                              /*!< specifies the destination address */
    uint32_t tbytes_num_in_block;                                                                           /*!< specifies the transfer bytes number in a buffer or block transfer */
    uint32_t source_bus;                                                                                    /*!< specifies the source bus */
    uint32_t destination_bus;                                                                               /*!< specifies the destination bus */
    uint32_t bufferable_write_mode;                                                                         /*!< specifies the bufferable write mode */
} mdma_parameter_struct;

/* MDMA address update direction */
typedef enum {
    UPDATE_DIR_INCREASE = 0,                                                                                /*!< MDMA address update increase */
    UPDATE_DIR_DECREASE = 1,                                                                                /*!< MDMA address update decrease */
} mdma_add_update_dir_enum;

/* MDMA multi block transfer configuration structure definition */
typedef struct {
    uint32_t block_num;                                                                                     /*!< multi-block number */
    uint16_t saddr_update_val;                                                                              /*!< source address update value */
    uint16_t dstaddr_update_val;                                                                            /*!< destination address update value */
    mdma_add_update_dir_enum saddr_update_dir;                                                              /*!< source address update direction */
    mdma_add_update_dir_enum dstaddr_update_dir;                                                            /*!< destination address update direction */
} mdma_multi_block_parameter_struct;

/* MDMA link node configuration structure definition */
typedef struct {
    __IO uint32_t chxcfg_reg;                                                                               /*!< channel x configure register */
    __IO uint32_t chxbtcfg_reg;                                                                             /*!< channel x block transfer configure register */
    __IO uint32_t chxsaddr_reg;                                                                             /*!< channel x source address register */
    __IO uint32_t chxdaddr_reg;                                                                             /*!< channel x destination address register */
    __IO uint32_t chxmbaddru_reg;                                                                           /*!< channel x multi-block address update register */
    __IO uint32_t chxladdr_reg;                                                                             /*!< channel x link address register */
    __IO uint32_t chxctl1_reg;                                                                              /*!< channel x control register 1 */
    __IO uint32_t reserved;                                                                                 /*!< channel x reserved register */
    __IO uint32_t chxmaddr_reg;                                                                             /*!< channel x mask address register */
    __IO uint32_t chxmdata_reg;                                                                             /*!< channel x mask data register */
} mdma_link_node_parameter_struct;

/* MDMA channel select */
typedef enum {
    MDMA_CH0 = 0,                                                                                           /*!< MDMA channel 0 */
    MDMA_CH1,                                                                                               /*!< MDMA channel 1 */
    MDMA_CH2,                                                                                               /*!< MDMA channel 2 */
    MDMA_CH3,                                                                                               /*!< MDMA channel 3 */
    MDMA_CH4,                                                                                               /*!< MDMA channel 4 */
    MDMA_CH5,                                                                                               /*!< MDMA channel 5 */
    MDMA_CH6,                                                                                               /*!< MDMA channel 6 */
    MDMA_CH7,                                                                                               /*!< MDMA channel 7 */
    MDMA_CH8,                                                                                               /*!< MDMA channel 8 */
    MDMA_CH9,                                                                                               /*!< MDMA channel 9 */
    MDMA_CH10,                                                                                              /*!< MDMA channel 10 */
    MDMA_CH11,                                                                                              /*!< MDMA channel 11 */
    MDMA_CH12,                                                                                              /*!< MDMA channel 12 */
    MDMA_CH13,                                                                                              /*!< MDMA channel 13 */
    MDMA_CH14,                                                                                              /*!< MDMA channel 14 */
    MDMA_CH15                                                                                               /*!< MDMA channel 15 */
} mdma_channel_enum;

/* MDMA request selection */
#define CHXCTL1_TRIGSEL(regval)                     (BITS(0,5) & ((uint32_t)(regval) << 0U))                /*!< trigger select */
#define MDMA_REQUEST_DMA0_CH0_FTFIF                 CHXCTL1_TRIGSEL(0)                                      /*!< MDMA hardware request is DMA0 channel 0 transfer complete flag */
#define MDMA_REQUEST_DMA0_CH1_FTFIF                 CHXCTL1_TRIGSEL(1)                                      /*!< MDMA hardware request is DMA0 channel 1 transfer complete flag */
#define MDMA_REQUEST_DMA0_CH2_FTFIF                 CHXCTL1_TRIGSEL(2)                                      /*!< MDMA hardware request is DMA0 channel 2 transfer complete flag */
#define MDMA_REQUEST_DMA0_CH3_FTFIF                 CHXCTL1_TRIGSEL(3)                                      /*!< MDMA hardware request is DMA0 channel 3 transfer complete flag */
#define MDMA_REQUEST_DMA0_CH4_FTFIF                 CHXCTL1_TRIGSEL(4)                                      /*!< MDMA hardware request is DMA0 channel 4 transfer complete flag */
#define MDMA_REQUEST_DMA0_CH5_FTFIF                 CHXCTL1_TRIGSEL(5)                                      /*!< MDMA hardware request is DMA0 channel 5 transfer complete flag */
#define MDMA_REQUEST_DMA0_CH6_FTFIF                 CHXCTL1_TRIGSEL(6)                                      /*!< MDMA hardware request is DMA0 channel 6 transfer complete flag */
#define MDMA_REQUEST_DMA0_CH7_FTFIF                 CHXCTL1_TRIGSEL(7)                                      /*!< MDMA hardware request is DMA0 channel 7 transfer complete flag */
#define MDMA_REQUEST_DMA1_CH0_FTFIF                 CHXCTL1_TRIGSEL(8)                                      /*!< MDMA hardware request is DMA1 channel 0 transfer complete flag */
#define MDMA_REQUEST_DMA1_CH1_FTFIF                 CHXCTL1_TRIGSEL(9)                                      /*!< MDMA hardware request is DMA1 channel 1 transfer complete flag */
#define MDMA_REQUEST_DMA1_CH2_FTFIF                 CHXCTL1_TRIGSEL(10)                                     /*!< MDMA hardware request is DMA1 channel 2 transfer complete flag */
#define MDMA_REQUEST_DMA1_CH3_FTFIF                 CHXCTL1_TRIGSEL(11)                                     /*!< MDMA hardware request is DMA1 channel 3 transfer complete flag */
#define MDMA_REQUEST_DMA1_CH4_FTFIF                 CHXCTL1_TRIGSEL(12)                                     /*!< MDMA hardware request is DMA1 channel 4 transfer complete flag */
#define MDMA_REQUEST_DMA1_CH5_FTFIF                 CHXCTL1_TRIGSEL(13)                                     /*!< MDMA hardware request is DMA1 channel 5 transfer complete flag */
#define MDMA_REQUEST_DMA1_CH6_FTFIF                 CHXCTL1_TRIGSEL(14)                                     /*!< MDMA hardware request is DMA1 channel 6 transfer complete flag */
#define MDMA_REQUEST_DMA1_CH7_FTFIF                 CHXCTL1_TRIGSEL(15)                                     /*!< MDMA hardware request is DMA1 channel 7 transfer complete flag */
#define MDMA_REQUEST_TLI_INT                        CHXCTL1_TRIGSEL(16)                                     /*!< MDMA hardware request is TLI interrupt flag */
#define MDMA_REQUEST_OSPI0_FT                       CHXCTL1_TRIGSEL(22)                                     /*!< MDMA hardware request is OSPI0_FT */
#define MDMA_REQUEST_OSPI0_TC                       CHXCTL1_TRIGSEL(23)                                     /*!< MDMA hardware request is OSPI0_TC */
#define MDMA_REQUEST_IPA_CLUT_TRIG                  CHXCTL1_TRIGSEL(24)                                     /*!< MDMA hardware request is IPA_CLUT_TRIG */
#define MDMA_REQUEST_IPA_TC_TRIG                    CHXCTL1_TRIGSEL(25)                                     /*!< MDMA hardware request is IPA_TC_TRIG */
#define MDMA_REQUEST_IPA_TWM_TRIG                   CHXCTL1_TRIGSEL(26)                                     /*!< MDMA hardware request is IPA_TWM_TRIG */
#define MDMA_REQUEST_SDIO0_DATA_END                 CHXCTL1_TRIGSEL(29)                                     /*!< MDMA hardware request is SDIO0_DATA_END signal */
#define MDMA_REQUEST_SDIO0_BUF_END                  CHXCTL1_TRIGSEL(30)                                     /*!< MDMA hardware request is SDIO0_BUF_END signal */
#define MDMA_REQUEST_SDIO0_CMD_END                  CHXCTL1_TRIGSEL(31)                                     /*!< MDMA hardware request is SDIO0_CMD_END signal */
#define MDMA_REQUEST_OSPI1_FT                       CHXCTL1_TRIGSEL(32)                                     /*!< MDMA hardware request is OSPI1_FT */
#define MDMA_REQUEST_OSPI1_TC                       CHXCTL1_TRIGSEL(33)                                     /*!< MDMA hardware request is OSPI1_TC */
#define MDMA_REQUEST_SW                             ((uint32_t)0x40000000U)                                 /*!< MDMA software request */

/* MDMA transfer trigger mode */
#define CHCFG_TRIGMOD(regval)                       (BITS(28,29) & ((uint32_t)(regval) << 28U))             /*!< trigger mode */
#define MDMA_BUFFER_TRANSFER                        CHCFG_TRIGMOD(0)                                        /*!< software request or hardware request triggers a buffer transfer */
#define MDMA_BLOCK_TRANSFER                         CHCFG_TRIGMOD(1)                                        /*!< software request or hardware request triggers a block transfer */
#define MDMA_MULTI_BLOCK_TRANSFER                   CHCFG_TRIGMOD(2)                                        /*!< software request or hardware request triggers a multi-block transfer */
#define MDMA_COMPLETE_TRANSFER                      CHCFG_TRIGMOD(3)                                        /*!< software request or hardware request triggers a complete data transfer (for example, link mode) */

/* channel priority level */
#define CHCTL0_PRIO(regval)                         (BITS(6,7) & ((uint32_t)(regval) << 6U))
#define MDMA_PRIORITY_LOW                           CHCTL0_PRIO(0)                                          /*!< priority level: low */
#define MDMA_PRIORITY_MEDIUM                        CHCTL0_PRIO(1)                                          /*!< priority level: medium */
#define MDMA_PRIORITY_HIGH                          CHCTL0_PRIO(2)                                          /*!< priority level: high */
#define MDMA_PRIORITY_ULTRA_HIGH                    CHCTL0_PRIO(3)                                          /*!< priority level: very high */

/* MDMA endianness */
#define MDMA_LITTLE_ENDIANNESS                      ((uint32_t)0x00000000U)                                 /*!< little endianness preserve */
#define MDMA_BYTE_ENDIANNESS_EXCHANGE               ((uint32_t)MDMA_CHXCTL0_BES)                            /*!< exchange the order of the bytes in a half-word */
#define MDMA_HALFWORD_ENDIANNESS_EXCHANGE           ((uint32_t)MDMA_CHXCTL0_HWES)                           /*!< exchange the order of the half-words in a word */
#define MDMA_WORD_ENDIANNESS_EXCHANGE               ((uint32_t)MDMA_CHXCTL0_WES)                            /*!< exchange the order of the words in a double word */

/* MDMA source adress increment mode */
#define CHCFG_SIMOD(regval)                         (BITS(0,1) & ((uint32_t)(regval) << 0U))                /*!< source increment mode */
#define CHCFG_SIOS(regval)                          (BITS(8,9) & ((uint32_t)(regval) << 8U))                /*!< offset size of source increment */
#define MDMA_SOURCE_INCREASE_DISABLE                CHCFG_SIMOD(0)                                          /*!< no increment */
#define MDMA_SOURCE_INCREASE_8BIT                   (CHCFG_SIMOD(2) | CHCFG_SIOS(0))                        /*!< source address pointer is incremented by a byte (8 bits) */
#define MDMA_SOURCE_INCREASE_16BIT                  (CHCFG_SIMOD(2) | CHCFG_SIOS(1))                        /*!< source address pointer is incremented by a half word (16 bits) */
#define MDMA_SOURCE_INCREASE_32BIT                  (CHCFG_SIMOD(2) | CHCFG_SIOS(2))                        /*!< source address pointer is incremented by a word (32 bits) */
#define MDMA_SOURCE_INCREASE_64BIT                  (CHCFG_SIMOD(2) | CHCFG_SIOS(3))                        /*!< source address pointer is incremented by a double word (64 bits) */
#define MDMA_SOURCE_DECREASE_8BIT                   (CHCFG_SIMOD(3) | CHCFG_SIOS(0))                        /*!< source address pointer is decremented by a byte (8 bits) */
#define MDMA_SOURCE_DECREASE_16BIT                  (CHCFG_SIMOD(3) | CHCFG_SIOS(1))                        /*!< source address pointer is decremented by a half word (16 bits) */
#define MDMA_SOURCE_DECREASE_32BIT                  (CHCFG_SIMOD(3) | CHCFG_SIOS(2))                        /*!< source address pointer is decremented by a word (32 bits) */
#define MDMA_SOURCE_DECREASE_64BIT                  (CHCFG_SIMOD(3) | CHCFG_SIOS(3))                        /*!< source address pointer is decremented by a double word (64 bits) */

/* MDMA destination adress increment mode*/
#define CHCFG_DIMOD(regval)                         (BITS(2,3) & ((uint32_t)(regval) << 2U))                /*!< destination increment mode */
#define CHCFG_DIOS(regval)                          (BITS(10,11) & ((uint32_t)(regval) << 10U))             /*!< offset size of destination increment */
#define MDMA_DESTINATION_INCREASE_DISABLE           CHCFG_DIMOD(0)                                          /*!< no increment */
#define MDMA_DESTINATION_INCREASE_8BIT              (CHCFG_DIMOD(2) | CHCFG_DIOS(0))                        /*!< destination address pointer is incremented by a byte (8 bits) */
#define MDMA_DESTINATION_INCREASE_16BIT             (CHCFG_DIMOD(2) | CHCFG_DIOS(1))                        /*!< destination address pointer is incremented by a half word (16 bits) */
#define MDMA_DESTINATION_INCREASE_32BIT             (CHCFG_DIMOD(2) | CHCFG_DIOS(2))                        /*!< destination address pointer is incremented by a word (32 bits) */
#define MDMA_DESTINATION_INCREASE_64BIT             (CHCFG_DIMOD(2) | CHCFG_DIOS(3))                        /*!< destination address pointer is incremented by a double word (64 bits) */
#define MDMA_DESTINATION_DECREASE_8BIT              (CHCFG_DIMOD(3) | CHCFG_DIOS(0))                        /*!< destination address pointer is decremented by a byte (8 bits) */
#define MDMA_DESTINATION_DECREASE_16BIT             (CHCFG_DIMOD(3) | CHCFG_DIOS(1))                        /*!< destination address pointer is decremented by a half word (16 bits) */
#define MDMA_DESTINATION_DECREASE_32BIT             (CHCFG_DIMOD(3) | CHCFG_DIOS(2))                        /*!< destination address pointer is decremented by a word (32 bits) */
#define MDMA_DESTINATION_DECREASE_64BIT             (CHCFG_DIMOD(3) | CHCFG_DIOS(3))                        /*!< destination address pointer is decremented by a double word (64 bits) */

/* MDMA source data size */
#define CHCFG_SWIDTH(regval)                        (BITS(4,5) & ((uint32_t)(regval) << 4U))                /*!< data size of source */
#define MDMA_SOURCE_DATASIZE_8BIT                   CHCFG_SWIDTH(0)                                         /*!< source data size is byte */
#define MDMA_SOURCE_DATASIZE_16BIT                  CHCFG_SWIDTH(1)                                         /*!< source data size is half word */
#define MDMA_SOURCE_DATASIZE_32BIT                  CHCFG_SWIDTH(2)                                         /*!< source data size is word */
#define MDMA_SOURCE_DATASIZE_64BIT                  CHCFG_SWIDTH(3)                                         /*!< source data size is double word */

/* MDMA destination data size */
#define CHCFG_DWIDTH(regval)                        (BITS(6,7) & ((uint32_t)(regval) << 6U))                /*!< data size of destination */
#define MDMA_DESTINATION_DATASIZE_8BIT              CHCFG_DWIDTH(0)                                         /*!< destination data size is byte */
#define MDMA_DESTINATION_DATASIZE_16BIT             CHCFG_DWIDTH(1)                                         /*!< destination data size is half word */
#define MDMA_DESTINATION_DATASIZE_32BIT             CHCFG_DWIDTH(2)                                         /*!< destination data size is word */
#define MDMA_DESTINATION_DATASIZE_64BIT             CHCFG_DWIDTH(3)                                         /*!< destination data size is double word */

/* MDMA data alignment */
#define CHCFG_PAMOD(regval)                         (BITS(26,27) & ((uint32_t)(regval) << 26U))             /*!< padding and alignement mode */
#define MDMA_DATAALIGN_PKEN                         ((uint32_t)MDMA_CHXCFG_PKEN)                            /*!< pack/unpack the source data to match the destination data size */
#define MDMA_DATAALIGN_RIGHT                        CHCFG_PAMOD(0)                                          /*!< right aligned, padded with 0s (default) */
#define MDMA_DATAALIGN_RIGHT_SIGNED                 CHCFG_PAMOD(1)                                          /*!< right aligned with sign extended, note: this mode is allowed only if the source data size is smaller than destination data size */
#define MDMA_DATAALIGN_LEFT                         CHCFG_PAMOD(2)                                          /*!< left aligned, padded with 0s in low bytes position when source data size smaller than destination data size, and only high byte of source is written when source data size larger than destination data size */

/* MDMA source burst */
#define CHCFG_SBURST(regval)                        (BITS(12,14) & ((uint32_t)(regval) << 12U))             /*!< transfer burst type of source */
#define MDMA_SOURCE_BURST_SINGLE                    CHCFG_SBURST(0)                                         /*!< single transfer */
#define MDMA_SOURCE_BURST_2BEATS                    CHCFG_SBURST(1)                                         /*!< burst 2 beats */
#define MDMA_SOURCE_BURST_4BEATS                    CHCFG_SBURST(2)                                         /*!< burst 4 beats */
#define MDMA_SOURCE_BURST_8BEATS                    CHCFG_SBURST(3)                                         /*!< burst 8 beats */
#define MDMA_SOURCE_BURST_16BEATS                   CHCFG_SBURST(4)                                         /*!< burst 16 beats */
#define MDMA_SOURCE_BURST_32BEATS                   CHCFG_SBURST(5)                                         /*!< burst 32 beats */
#define MDMA_SOURCE_BURST_64BEATS                   CHCFG_SBURST(6)                                         /*!< burst 64 beats */
#define MDMA_SOURCE_BURST_128BEATS                  CHCFG_SBURST(7)                                         /*!< burst 128 beats */

/* MDMA destination burst */
#define CHCFG_DBURST(regval)                        (BITS(15,17) & ((uint32_t)(regval) << 15U))             /*!< transfer burst type of destination */
#define MDMA_DESTINATION_BURST_SINGLE               CHCFG_DBURST(0)                                         /*!< single transfer */
#define MDMA_DESTINATION_BURST_2BEATS               CHCFG_DBURST(1)                                         /*!< burst 2 beats */
#define MDMA_DESTINATION_BURST_4BEATS               CHCFG_DBURST(2)                                         /*!< burst 4 beats */
#define MDMA_DESTINATION_BURST_8BEATS               CHCFG_DBURST(3)                                         /*!< burst 8 beats */
#define MDMA_DESTINATION_BURST_16BEATS              CHCFG_DBURST(4)                                         /*!< burst 16 beats */
#define MDMA_DESTINATION_BURST_32BEATS              CHCFG_DBURST(5)                                         /*!< burst 32 beats */
#define MDMA_DESTINATION_BURST_64BEATS              CHCFG_DBURST(6)                                         /*!< burst 64 beats */
#define MDMA_DESTINATION_BURST_128BEATS             CHCFG_DBURST(7)                                         /*!< burst 128 beats */

/* source bus select */
#define MDMA_SOURCE_AXI                             ((uint32_t)0x00000000U)                                 /*!< source bus of channel x is the system bus or AXI bus */
#define MDMA_SOURCE_AHB_TCM                         MDMA_CHXCTL1_SBSEL                                      /*!< source bus of channel x is AHB bus or TCM */

/* destination bus select */
#define MDMA_DESTINATION_AXI                        ((uint32_t)0x00000000U)                                 /*!< destination bus of channel x is the system bus or AXI bus */
#define MDMA_DESTINATION_AHB_TCM                    MDMA_CHXCTL1_DBSEL                                      /*!< destination bus of channel x is AHB bus or TCM */

/* MDMA access error direction */
#define MDMA_READ_ERROR                             ((uint32_t)0x00000000U)                                 /*!< read access error */
#define MDMA_WRITE_ERROR                            MDMA_CHXSTAT1_TERRD                                     /*!< write access error */

/* MDMA bufferable write mode */
#define MDMA_BUFFERABLE_WRITE_DISABLE               ((uint32_t)0x00000000U)                                 /*!< diable bufferable write mode */
#define MDMA_BUFFERABLE_WRITE_ENABLE                MDMA_CHXCFG_BWMOD                                       /*!< enable bufferable write mode */

/* MDMA flags */
#define STAT1_FLAG                                  BIT(31)                                                 /*!< flag to indicate that flag is in STAT1 register */
#define MDMA_FLAG_ERR                               MDMA_CHXSTAT0_ERR                                       /*!< channel x transfer error flag */
#define MDMA_FLAG_CHTCF                             MDMA_CHXSTAT0_CHTCF                                     /*!< channel x channel transfer complete flag */
#define MDMA_FLAG_MBTCF                             MDMA_CHXSTAT0_MBTCF                                     /*!< channel x multi-block transfer complete flag */
#define MDMA_FLAG_BTCF                              MDMA_CHXSTAT0_BTCF                                      /*!< channel x block transfer complete flag */
#define MDMA_FLAG_TCF                               MDMA_CHXSTAT0_TCF                                       /*!< channel x buffer transfer complete flag */
#define MDMA_FLAG_REQAF                             MDMA_CHXSTAT0_REQAF                                     /*!< channel x request active flag */
#define MDMA_FLAG_LDTERR                            (MDMA_CHXSTAT1_LDTERR | STAT1_FLAG)                     /*!< link data transfer error flag in the last transfer of the channel */
#define MDMA_FLAG_MDTERR                            (MDMA_CHXSTAT1_MDTERR | STAT1_FLAG)                     /*!< mask data error flag */
#define MDMA_FLAG_ASERR                             (MDMA_CHXSTAT1_ASERR | STAT1_FLAG)                      /*!< address and size error flag */
#define MDMA_FLAG_BZERR                             (MDMA_CHXSTAT1_BZERR | STAT1_FLAG)                      /*!< block size error flag */

/* MDMA interrupt */
#define MDMA_INT_ERR                                MDMA_CHXCTL0_ERRIE                                      /*!< transfer error interrupt */
#define MDMA_INT_CHTC                               MDMA_CHXCTL0_CHTCIE                                     /*!< channel transfer complete interrupt */
#define MDMA_INT_MBTC                               MDMA_CHXCTL0_MBTCIE                                     /*!< multi-block transfer complete interrupt */
#define MDMA_INT_BTC                                MDMA_CHXCTL0_BTCIE                                      /*!< block transfer complete interrupt */
#define MDMA_INT_TC                                 MDMA_CHXCTL0_TCIE                                       /*!< buffer transfer complete interrupt */

/* MDMA interrupt flags */
#define MDMA_INT_FLAG_ERR                           MDMA_CHXSTAT0_ERR                                       /*!< transfer error interrupt flag */
#define MDMA_INT_FLAG_CHTCF                         MDMA_CHXSTAT0_CHTCF                                     /*!< channel transfer complete interrupt flag */
#define MDMA_INT_FLAG_MBTCF                         MDMA_CHXSTAT0_MBTCF                                     /*!< multi-block transfer complete interrupt flag */
#define MDMA_INT_FLAG_BTCF                          MDMA_CHXSTAT0_BTCF                                      /*!< block transfer complete interrupt flag */
#define MDMA_INT_FLAG_TCF                           MDMA_CHXSTAT0_TCF                                       /*!< buffer transfer complete interrupt flag */

/* function declarations */
/* MDMA deinitialization and initialization functions */
/* deinitialize MDMA */
void mdma_deinit(void);
/* deinitialize MDMA registers of a channel */
void mdma_channel_deinit(mdma_channel_enum channelx);
/* initialize the MDMA parameters struct with the default values */
void mdma_para_struct_init(mdma_parameter_struct *init_struct);
/* initialize the MDMA multi block transfer mode parameters struct with the default values */
void mdma_multi_block_para_struct_init(mdma_multi_block_parameter_struct *block_init_struct);
/* initialize the MDMA link node configuration struct with the default values */
void mdma_link_node_para_struct_init(mdma_link_node_parameter_struct *node);
/* initialize MDMA channel with MDMA parameter structure */
void mdma_init(mdma_channel_enum channelx, mdma_parameter_struct *init_struct);
/* configure MDMA buffer/block transfer mode */
void mdma_buffer_block_mode_config(mdma_channel_enum channelx, uint32_t saddr, uint32_t daddr, uint32_t tbnum);
/* configure MDMA multi block transfer mode */
void mdma_multi_block_mode_config(mdma_channel_enum channelx, uint32_t tbnum, mdma_multi_block_parameter_struct *block_init_struct);
/* create MDMA link list node */
void mdma_node_create(mdma_link_node_parameter_struct *node, mdma_multi_block_parameter_struct *block_init_struct, mdma_parameter_struct *init_struct);
/* MDMA add node to link list */
void mdma_node_add(mdma_link_node_parameter_struct *pre_node, mdma_link_node_parameter_struct *new_node);
/* MDMA disconnect link list node */
ErrStatus mdma_node_delete(mdma_link_node_parameter_struct *pre_node, mdma_link_node_parameter_struct *unused_node);

/* MDMA configuration functions */
/* configure MDMA destination base address */
void mdma_destination_address_config(mdma_channel_enum channelx, uint32_t address);
/* configure MDMA source base address */
void mdma_source_address_config(mdma_channel_enum channelx, uint32_t address);
/* configure MDMA destination bus */
void mdma_destination_bus_config(mdma_channel_enum channelx, uint32_t bus);
/* configure MDMA source bus */
void mdma_source_bus_config(mdma_channel_enum channelx, uint32_t bus);
/* configure priority level of MDMA channel */
void mdma_priority_config(mdma_channel_enum channelx, uint32_t priority);
/* configure endianness of MDMA channel */
void mdma_endianness_config(mdma_channel_enum channelx, uint32_t endianness);
/* configure data alignment of MDMA channel */
void mdma_alignment_config(mdma_channel_enum channelx, uint32_t alignment);
/* configure transfer burst beats of source */
void mdma_source_burst_beats_config(mdma_channel_enum channelx, uint32_t sbeat);
/* configure transfer burst beats of destination */
void mdma_destination_burst_beats_config(mdma_channel_enum channelx, uint32_t dbeat);
/* configure data size of source */
void mdma_source_width_config(mdma_channel_enum channelx, uint32_t swidth);
/* configure data size of destination */
void mdma_destination_width_config(mdma_channel_enum channelx, uint32_t dwidth);
/* configure source adress increment mode */
void mdma_source_increment_config(mdma_channel_enum channelx, uint32_t sinc);
/* configure destination adress increment mode */
void mdma_destination_increment_config(mdma_channel_enum channelx, uint32_t dinc);
/* enable MDMA channel bufferable write mode */
void mdma_channel_bufferable_write_enable(mdma_channel_enum channelx);
/* disable MDMA channel bufferable write mode */
void mdma_channel_bufferable_write_disable(mdma_channel_enum channelx);
/* enable MDMA channel software request */
void mdma_channel_software_request_enable(mdma_channel_enum channelx);
/* enable MDMA channel */
void mdma_channel_enable(mdma_channel_enum channelx);
/* disable MDMA channel */
void mdma_channel_disable(mdma_channel_enum channelx);
/* get MDMA transfer error direction */
uint32_t mdma_transfer_error_direction_get(mdma_channel_enum channelx);
/* get MDMA transfer error address */
uint32_t mdma_transfer_error_address_get(mdma_channel_enum channelx);

/* interrupt & flag functions */
/* get MDMA flag */
FlagStatus mdma_flag_get(mdma_channel_enum channelx, uint32_t flag);
/* clear MDMA flag */
void mdma_flag_clear(mdma_channel_enum channelx, uint32_t flag);
/* enable MDMA interrupt */
void mdma_interrupt_enable(mdma_channel_enum channelx, uint32_t interrupt);
/* disable MDMA interrupt */
void mdma_interrupt_disable(mdma_channel_enum channelx, uint32_t interrupt);
/* get MDMA interrupt flag */
FlagStatus mdma_interrupt_flag_get(mdma_channel_enum channelx, uint32_t int_flag);
/* clear MDMA interrupt flag */
void mdma_interrupt_flag_clear(mdma_channel_enum channelx, uint32_t int_flag);

#endif /* GD32H7XX_MDMA_H */
