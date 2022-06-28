/*!
    \file    gd32f30x_dma.h
    \brief   definitions for the DMA

    \version 2017-02-10, V1.0.0, firmware for GD32F30x
    \version 2018-10-10, V1.1.0, firmware for GD32F30x
    \version 2018-12-25, V2.0.0, firmware for GD32F30x
    \version 2020-09-30, V2.1.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

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

#ifndef GD32F30X_DMA_H
#define GD32F30X_DMA_H

#include "gd32f30x.h"

/* DMA definitions */
#define DMA0                            (DMA_BASE)               /*!< DMA0 base address */
#define DMA1                            (DMA_BASE + 0x0400U)     /*!< DMA1 base address */

/* registers definitions */
#define DMA_INTF(dmax)                  REG32((dmax) + 0x00U)    /*!< DMA interrupt flag register */
#define DMA_INTC(dmax)                  REG32((dmax) + 0x04U)    /*!< DMA interrupt flag clear register */

#define DMA_CH0CTL(dmax)                REG32((dmax) + 0x08U)    /*!< DMA channel 0 control register */
#define DMA_CH0CNT(dmax)                REG32((dmax) + 0x0CU)    /*!< DMA channel 0 counter register */
#define DMA_CH0PADDR(dmax)              REG32((dmax) + 0x10U)    /*!< DMA channel 0 peripheral base address register */
#define DMA_CH0MADDR(dmax)              REG32((dmax) + 0x14U)    /*!< DMA channel 0 memory base address register */

#define DMA_CH1CTL(dmax)                REG32((dmax) + 0x1CU)    /*!< DMA channel 1 control register */
#define DMA_CH1CNT(dmax)                REG32((dmax) + 0x20U)    /*!< DMA channel 1 counter register */
#define DMA_CH1PADDR(dmax)              REG32((dmax) + 0x24U)    /*!< DMA channel 1 peripheral base address register */
#define DMA_CH1MADDR(dmax)              REG32((dmax) + 0x28U)    /*!< DMA channel 1 memory base address register */

#define DMA_CH2CTL(dmax)                REG32((dmax) + 0x30U)    /*!< DMA channel 2 control register */
#define DMA_CH2CNT(dmax)                REG32((dmax) + 0x34U)    /*!< DMA channel 2 counter register */
#define DMA_CH2PADDR(dmax)              REG32((dmax) + 0x38U)    /*!< DMA channel 2 peripheral base address register */
#define DMA_CH2MADDR(dmax)              REG32((dmax) + 0x3CU)    /*!< DMA channel 2 memory base address register */

#define DMA_CH3CTL(dmax)                REG32((dmax) + 0x44U)    /*!< DMA channel 3 control register */
#define DMA_CH3CNT(dmax)                REG32((dmax) + 0x48U)    /*!< DMA channel 3 counter register */
#define DMA_CH3PADDR(dmax)              REG32((dmax) + 0x4CU)    /*!< DMA channel 3 peripheral base address register */
#define DMA_CH3MADDR(dmax)              REG32((dmax) + 0x50U)    /*!< DMA channel 3 memory base address register */

#define DMA_CH4CTL(dmax)                REG32((dmax) + 0x58U)    /*!< DMA channel 4 control register */
#define DMA_CH4CNT(dmax)                REG32((dmax) + 0x5CU)    /*!< DMA channel 4 counter register */
#define DMA_CH4PADDR(dmax)              REG32((dmax) + 0x60U)    /*!< DMA channel 4 peripheral base address register */
#define DMA_CH4MADDR(dmax)              REG32((dmax) + 0x64U)    /*!< DMA channel 4 memory base address register */

#define DMA_CH5CTL(dmax)                REG32((dmax) + 0x6CU)    /*!< DMA channel 5 control register */
#define DMA_CH5CNT(dmax)                REG32((dmax) + 0x70U)    /*!< DMA channel 5 counter register */
#define DMA_CH5PADDR(dmax)              REG32((dmax) + 0x74U)    /*!< DMA channel 5 peripheral base address register */
#define DMA_CH5MADDR(dmax)              REG32((dmax) + 0x78U)    /*!< DMA channel 5 memory base address register */

#define DMA_CH6CTL(dmax)                REG32((dmax) + 0x80U)    /*!< DMA channel 6 control register */
#define DMA_CH6CNT(dmax)                REG32((dmax) + 0x84U)    /*!< DMA channel 6 counter register */
#define DMA_CH6PADDR(dmax)              REG32((dmax) + 0x88U)    /*!< DMA channel 6 peripheral base address register */
#define DMA_CH6MADDR(dmax)              REG32((dmax) + 0x8CU)    /*!< DMA channel 6 memory base address register */

/* bits definitions */
/* DMA_INTF */
#define DMA_INTF_GIF                    BIT(0)                  /*!< global interrupt flag of channel */
#define DMA_INTF_FTFIF                  BIT(1)                  /*!< full transfer finish flag of channel */
#define DMA_INTF_HTFIF                  BIT(2)                  /*!< half transfer finish flag of channel */
#define DMA_INTF_ERRIF                  BIT(3)                  /*!< error flag of channel */

/* DMA_INTC */
#define DMA_INTC_GIFC                   BIT(0)                  /*!< clear global interrupt flag of channel */
#define DMA_INTC_FTFIFC                 BIT(1)                  /*!< clear transfer finish flag of channel */
#define DMA_INTC_HTFIFC                 BIT(2)                  /*!< clear half transfer finish flag of channel */
#define DMA_INTC_ERRIFC                 BIT(3)                  /*!< clear error flag of channel */

/* DMA_CHxCTL, x=0..6 */
#define DMA_CHXCTL_CHEN                 BIT(0)                  /*!< channel enable */
#define DMA_CHXCTL_FTFIE                BIT(1)                  /*!< enable bit for channel full transfer finish interrupt */
#define DMA_CHXCTL_HTFIE                BIT(2)                  /*!< enable bit for channel half transfer finish interrupt */
#define DMA_CHXCTL_ERRIE                BIT(3)                  /*!< enable bit for channel error interrupt */
#define DMA_CHXCTL_DIR                  BIT(4)                  /*!< transfer direction */
#define DMA_CHXCTL_CMEN                 BIT(5)                  /*!< circular mode enable */
#define DMA_CHXCTL_PNAGA                BIT(6)                  /*!< next address generation algorithm of peripheral */
#define DMA_CHXCTL_MNAGA                BIT(7)                  /*!< next address generation algorithm of memory */
#define DMA_CHXCTL_PWIDTH               BITS(8,9)               /*!< transfer data width of peripheral */
#define DMA_CHXCTL_MWIDTH               BITS(10,11)             /*!< transfer data width of memory */
#define DMA_CHXCTL_PRIO                 BITS(12,13)             /*!< priority level */
#define DMA_CHXCTL_M2M                  BIT(14)                 /*!< memory to memory mode */

/* DMA_CHxCNT,x=0..6 */
#define DMA_CHXCNT_CNT                  BITS(0,15)              /*!< transfer counter */

/* DMA_CHxPADDR,x=0..6 */
#define DMA_CHXPADDR_PADDR              BITS(0,31)              /*!< peripheral base address */

/* DMA_CHxMADDR,x=0..6 */
#define DMA_CHXMADDR_MADDR              BITS(0,31)              /*!< memory base address */

/* constants definitions */
/* DMA channel select */
typedef enum
{
    DMA_CH0 = 0,                /*!< DMA Channel0 */
    DMA_CH1,                    /*!< DMA Channel1 */
    DMA_CH2,                    /*!< DMA Channel2 */
    DMA_CH3,                    /*!< DMA Channel3 */
    DMA_CH4,                    /*!< DMA Channel4 */
    DMA_CH5,                    /*!< DMA Channel5 */
    DMA_CH6                     /*!< DMA Channel6 */
} dma_channel_enum;

/* DMA initialize struct */
typedef struct
{
    uint32_t periph_addr;       /*!< peripheral base address */
    uint32_t periph_width;      /*!< transfer data size of peripheral */
    uint32_t memory_addr;       /*!< memory base address */
    uint32_t memory_width;      /*!< transfer data size of memory */
    uint32_t number;            /*!< channel transfer number */
    uint32_t priority;          /*!< channel priority level */
    uint8_t periph_inc;         /*!< peripheral increasing mode */
    uint8_t memory_inc;         /*!< memory increasing mode */
    uint8_t direction;          /*!< channel data transfer direction */

} dma_parameter_struct;

#define DMA_FLAG_ADD(flag, shift)           ((flag) << ((shift) * 4U))                      /*!< DMA channel flag shift */

/* DMA_register address */
#define DMA_CHCTL(dma, channel)             REG32(((dma) + 0x08U) + 0x14U * (uint32_t)(channel))      /*!< the address of DMA channel CHXCTL register */
#define DMA_CHCNT(dma, channel)             REG32(((dma) + 0x0CU) + 0x14U * (uint32_t)(channel))      /*!< the address of DMA channel CHXCNT register */
#define DMA_CHPADDR(dma, channel)           REG32(((dma) + 0x10U) + 0x14U * (uint32_t)(channel))      /*!< the address of DMA channel CHXPADDR register */
#define DMA_CHMADDR(dma, channel)           REG32(((dma) + 0x14U) + 0x14U * (uint32_t)(channel))      /*!< the address of DMA channel CHXMADDR register */

/* DMA reset value */
#define DMA_CHCTL_RESET_VALUE               ((uint32_t)0x00000000U)                         /*!< the reset value of DMA channel CHXCTL register  */
#define DMA_CHCNT_RESET_VALUE               ((uint32_t)0x00000000U)                         /*!< the reset value of DMA channel CHXCNT register  */
#define DMA_CHPADDR_RESET_VALUE             ((uint32_t)0x00000000U)                         /*!< the reset value of DMA channel CHXPADDR register  */
#define DMA_CHMADDR_RESET_VALUE             ((uint32_t)0x00000000U)                         /*!< the reset value of DMA channel CHXMADDR register  */
#define DMA_CHINTF_RESET_VALUE              (DMA_INTF_GIF | DMA_INTF_FTFIF | \
                                             DMA_INTF_HTFIF | DMA_INTF_ERRIF)               /*!< clear DMA channel DMA_INTF register */

/* DMA_INTF register */
/* interrupt flag bits */
#define DMA_INT_FLAG_G                      DMA_INTF_GIF                                    /*!< global interrupt flag of channel */
#define DMA_INT_FLAG_FTF                    DMA_INTF_FTFIF                                  /*!< full transfer finish interrupt flag of channel */
#define DMA_INT_FLAG_HTF                    DMA_INTF_HTFIF                                  /*!< half transfer finish interrupt flag of channel */
#define DMA_INT_FLAG_ERR                    DMA_INTF_ERRIF                                  /*!< error interrupt flag of channel */

/* flag bits */
#define DMA_FLAG_G                          DMA_INTF_GIF                                    /*!< global interrupt flag of channel */
#define DMA_FLAG_FTF                        DMA_INTF_FTFIF                                  /*!< full transfer finish flag of channel */
#define DMA_FLAG_HTF                        DMA_INTF_HTFIF                                  /*!< half transfer finish flag of channel */
#define DMA_FLAG_ERR                        DMA_INTF_ERRIF                                  /*!< error flag of channel */

/* DMA_CHxCTL register */
/* interrupt enable bits */
#define DMA_INT_FTF                         DMA_CHXCTL_FTFIE                                /*!< enable bit for channel full transfer finish interrupt */
#define DMA_INT_HTF                         DMA_CHXCTL_HTFIE                                /*!< enable bit for channel half transfer finish interrupt */
#define DMA_INT_ERR                         DMA_CHXCTL_ERRIE                                /*!< enable bit for channel error interrupt */

/* transfer direction */
#define DMA_PERIPHERAL_TO_MEMORY            ((uint8_t)0x0000U)                              /*!< read from peripheral and write to memory */
#define DMA_MEMORY_TO_PERIPHERAL            ((uint8_t)0x0001U)                              /*!< read from memory and write to peripheral */

/* peripheral increasing mode */
#define DMA_PERIPH_INCREASE_DISABLE         ((uint8_t)0x0000U)                              /*!< next address of peripheral is fixed address mode */
#define DMA_PERIPH_INCREASE_ENABLE          ((uint8_t)0x0001U)                              /*!< next address of peripheral is increasing address mode */

/* memory increasing mode */
#define DMA_MEMORY_INCREASE_DISABLE         ((uint8_t)0x0000U)                              /*!< next address of memory is fixed address mode */
#define DMA_MEMORY_INCREASE_ENABLE          ((uint8_t)0x0001U)                              /*!< next address of memory is increasing address mode */

/* transfer data size of peripheral */
#define CHCTL_PWIDTH(regval)                (BITS(8,9) & ((uint32_t)(regval) << 8))         /*!< transfer data size of peripheral */
#define DMA_PERIPHERAL_WIDTH_8BIT           CHCTL_PWIDTH(0)                                 /*!< transfer data size of peripheral is 8-bit */
#define DMA_PERIPHERAL_WIDTH_16BIT          CHCTL_PWIDTH(1)                                 /*!< transfer data size of peripheral is 16-bit */
#define DMA_PERIPHERAL_WIDTH_32BIT          CHCTL_PWIDTH(2)                                 /*!< transfer data size of peripheral is 32-bit */

/* transfer data size of memory */
#define CHCTL_MWIDTH(regval)                (BITS(10,11) & ((uint32_t)(regval) << 10))      /*!< transfer data size of memory */
#define DMA_MEMORY_WIDTH_8BIT               CHCTL_MWIDTH(0)                                 /*!< transfer data size of memory is 8-bit */
#define DMA_MEMORY_WIDTH_16BIT              CHCTL_MWIDTH(1)                                 /*!< transfer data size of memory is 16-bit */
#define DMA_MEMORY_WIDTH_32BIT              CHCTL_MWIDTH(2)                                 /*!< transfer data size of memory is 32-bit */

/* channel priority level */
#define CHCTL_PRIO(regval)                  (BITS(12,13) & ((uint32_t)(regval) << 12))      /*!< DMA channel priority level */
#define DMA_PRIORITY_LOW                    CHCTL_PRIO(0)                                   /*!< low priority */
#define DMA_PRIORITY_MEDIUM                 CHCTL_PRIO(1)                                   /*!< medium priority */
#define DMA_PRIORITY_HIGH                   CHCTL_PRIO(2)                                   /*!< high priority */
#define DMA_PRIORITY_ULTRA_HIGH             CHCTL_PRIO(3)                                   /*!< ultra high priority */

/* memory to memory mode */
#define DMA_MEMORY_TO_MEMORY_DISABLE        ((uint32_t)0x00000000U)
#define DMA_MEMORY_TO_MEMORY_ENABLE         ((uint32_t)0x00000001U)

/* DMA_CHxCNT register */
/* transfer counter */
#define DMA_CHANNEL_CNT_MASK                DMA_CHXCNT_CNT                                  /*!< transfer counter mask */

/* function declarations */
/* DMA deinitialization and initialization functions */
/* deinitialize DMA a channel registers */
void dma_deinit(uint32_t dma_periph, dma_channel_enum channelx);
/* initialize the parameters of DMA struct with the default values */
void dma_struct_para_init(dma_parameter_struct* init_struct);
/* initialize DMA channel */
void dma_init(uint32_t dma_periph, dma_channel_enum channelx, dma_parameter_struct* init_struct);
/* enable DMA circulation mode */
void dma_circulation_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable DMA circulation mode */
void dma_circulation_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* enable memory to memory mode */
void dma_memory_to_memory_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable memory to memory mode */
void dma_memory_to_memory_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* enable DMA channel */
void dma_channel_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable DMA channel */
void dma_channel_disable(uint32_t dma_periph, dma_channel_enum channelx);

/* DMA configuration functions */
/* set DMA peripheral base address */
void dma_periph_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t address);
/* set DMA memory base address */
void dma_memory_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t address);
/* set the number of remaining data to be transferred by the DMA */
void dma_transfer_number_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t number);
/* get the number of remaining data to be transferred by the DMA */
uint32_t dma_transfer_number_get(uint32_t dma_periph, dma_channel_enum channelx);
/* configure priority level of DMA channel */
void dma_priority_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t priority);
/* configure transfer data size of memory */
void dma_memory_width_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t mwidth);
/* configure transfer data size of peripheral */
void dma_periph_width_config (uint32_t dma_periph, dma_channel_enum channelx, uint32_t pwidth);
/* enable next address increasement algorithm of memory */
void dma_memory_increase_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable next address increasement algorithm of memory */
void dma_memory_increase_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* enable next address increasement algorithm of peripheral */
void dma_periph_increase_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable next address increasement algorithm of peripheral */
void dma_periph_increase_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* configure the direction of data transfer on the channel */
void dma_transfer_direction_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t direction);

/* flag and interrupt functions */
/* check DMA flag is set or not */
FlagStatus dma_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* clear DMA a channel flag */
void dma_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* check DMA flag and interrupt enable bit is set or not */
FlagStatus dma_interrupt_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* clear DMA a channel flag */
void dma_interrupt_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* enable DMA interrupt */
void dma_interrupt_enable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t source);
/* disable DMA interrupt */
void dma_interrupt_disable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t source);

#endif /* GD32F30X_DMA_H */
