/*!
    \file    gd32h7xx_dma.c
    \brief   DMA driver

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

#include "gd32h7xx_dma.h"
#include <stdlib.h>

#define DMA_WRONG_HANDLE        while(1)
{}

/* DMA register bit offset */
#define CHXFCTL_FCNT_OFFSET        ((uint32_t)0x00000003U)               /*!< bit offset of FCNT in DMA_CHxFCTL */

/* DMAMUX register bit offset */
#define RM_CHXCFG_NBR_OFFSET       ((uint32_t)0x00000013U)               /*!< bit offset of NBR in DMAMUX_RM_CHXCFG */
#define RG_CHXCFG_NBRG_OFFSET      ((uint32_t)0x00000013U)               /*!< bit offset of NBRG in DMAMUX_RG_CHXCFG */

/*!
    \brief      deinitialize DMA registers of a channel
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel is deinitialized
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_deinit(uint32_t dma_periph, dma_channel_enum channelx)
{
    /* disable DMA a channel */
    DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_CHEN;
    /* reset DMA channel registers */
    DMA_CHCTL(dma_periph, channelx) = DMA_CHCTL_RESET_VALUE;
    DMA_CHCNT(dma_periph, channelx) = DMA_CHCNT_RESET_VALUE;
    DMA_CHPADDR(dma_periph, channelx) = DMA_CHPADDR_RESET_VALUE;
    DMA_CHM0ADDR(dma_periph, channelx) = DMA_CHMADDR_RESET_VALUE;
    DMA_CHM1ADDR(dma_periph, channelx) = DMA_CHMADDR_RESET_VALUE;
    DMA_CHFCTL(dma_periph, channelx) = DMA_CHFCTL_RESET_VALUE;
    if(channelx < DMA_CH4)
    {
        DMA_INTC0(dma_periph) |= DMA_FLAG_ADD(DMA_CHINTF_RESET_VALUE, channelx);
    } else {
        channelx -= (dma_channel_enum)4;
        DMA_INTC1(dma_periph) |= DMA_FLAG_ADD(DMA_CHINTF_RESET_VALUE, channelx);
    }
}

/*!
    \brief      initialize the DMA single data mode parameters structure with the default values
    \param[in]  none
    \param[out] init_struct: the initialization data needed to initialize DMA channel
    \retval     none
*/
void dma_single_data_para_struct_init(dma_single_data_parameter_struct *init_struct)
{
    /* set the DMA struct with the default values */
    init_struct->request             = DMA_REQUEST_M2M;
    init_struct->periph_addr         = 0U;
    init_struct->periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
    init_struct->memory0_addr        = 0U;
    init_struct->memory_inc          = DMA_MEMORY_INCREASE_DISABLE;
    init_struct->periph_memory_width = 0U;
    init_struct->circular_mode       = DMA_CIRCULAR_MODE_DISABLE;
    init_struct->direction           = DMA_PERIPH_TO_MEMORY;
    init_struct->number              = 0U;
    init_struct->priority            = DMA_PRIORITY_LOW;
}

/*!
    \brief      initialize the DMA multi data mode parameters structure with the default values
    \param[in]  none
    \param[out] init_struct: the initialization data needed to initialize DMA channel
    \retval     none
*/
void dma_multi_data_para_struct_init(dma_multi_data_parameter_struct *init_struct)
{
    /* set the DMA structure with the default values */
    init_struct->request             = DMA_REQUEST_M2M;
    init_struct->periph_addr         = 0U;
    init_struct->periph_width        = 0U;
    init_struct->periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
    init_struct->memory0_addr        = 0U;
    init_struct->memory_width        = 0U;
    init_struct->memory_inc          = DMA_MEMORY_INCREASE_DISABLE;
    init_struct->memory_burst_width  = 0U;
    init_struct->periph_burst_width  = 0U;
    init_struct->circular_mode       = DMA_CIRCULAR_MODE_DISABLE;
    init_struct->direction           = DMA_PERIPH_TO_MEMORY;
    init_struct->number              = 0U;
    init_struct->priority            = DMA_PRIORITY_LOW;
}

/*!
    \brief      initialize DMA single data mode
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel is initialized
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  init_struct: the data needed to initialize DMA single data mode
                  request: DMA_REQUEST_x x is the type of request
                  periph_addr: peripheral base address
                  periph_inc: DMA_PERIPH_INCREASE_ENABLE,DMA_PERIPH_INCREASE_DISABLE,DMA_PERIPH_INCREASE_FIX
                  memory0_addr: memory base address
                  memory_inc: DMA_MEMORY_INCREASE_ENABLE,DMA_MEMORY_INCREASE_DISABLE
                  periph_memory_width: DMA_PERIPH_WIDTH_8BIT,DMA_PERIPH_WIDTH_16BIT,DMA_PERIPH_WIDTH_32BIT
                  circular_mode: DMA_CIRCULAR_MODE_ENABLE,DMA_CIRCULAR_MODE_DISABLE
                  direction: DMA_PERIPH_TO_MEMORY,DMA_MEMORY_TO_PERIPH,DMA_MEMORY_TO_MEMORY
                  number: the number of remaining data to be transferred by the DMA
                  priority: DMA_PRIORITY_LOW,DMA_PRIORITY_MEDIUM,DMA_PRIORITY_HIGH,DMA_PRIORITY_ULTRA_HIGH
    \param[out] none
    \retval     none
*/
void dma_single_data_mode_init(uint32_t dma_periph, dma_channel_enum channelx, dma_single_data_parameter_struct *init_struct)
{
    uint32_t ctl;

    /* select single data mode */
    DMA_CHFCTL(dma_periph, channelx) &= ~DMA_CHXFCTL_MDMEN;

    /* configure peripheral base address */
    DMA_CHPADDR(dma_periph, channelx) = init_struct->periph_addr;

    /* configure memory base address */
    DMA_CHM0ADDR(dma_periph, channelx) = init_struct->memory0_addr;

    /* configure the number of remaining data to be transferred */
    DMA_CHCNT(dma_periph, channelx) = init_struct->number;

    /* configure peripheral and memory transfer width,channel priotity,transfer mode */
    ctl = DMA_CHCTL(dma_periph, channelx);
    ctl &= ~(DMA_CHXCTL_PWIDTH | DMA_CHXCTL_MWIDTH | DMA_CHXCTL_PRIO | DMA_CHXCTL_TM);
    ctl |= (init_struct->periph_memory_width | (init_struct->periph_memory_width << 2U) | init_struct->priority | init_struct->direction);
    DMA_CHCTL(dma_periph, channelx) = ctl;

    /* configure peripheral increasing mode */
    if(DMA_PERIPH_INCREASE_ENABLE == init_struct->periph_inc)
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
    } else if(DMA_PERIPH_INCREASE_DISABLE == init_struct->periph_inc)
    {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_PNAGA;
    } else {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PAIF;
    }

    /* configure memory increasing mode */
    if(DMA_MEMORY_INCREASE_ENABLE == init_struct->memory_inc)
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MNAGA;
    } else {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MNAGA;
    }

    /* configure DMA circular mode */
    if(DMA_CIRCULAR_MODE_ENABLE == init_struct->circular_mode)
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_CMEN;
    } else {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_CMEN;
    }
    if(DMA0 == dma_periph)
    {
        DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_MUXID;
        DMAMUX_RM_CHXCFG(channelx) |= init_struct->request;
    } else {
        DMAMUX_RM_CHXCFG((uint32_t)channelx + 8U) &= ~DMAMUX_RM_CHXCFG_MUXID;
        DMAMUX_RM_CHXCFG((uint32_t)channelx + 8U) |= init_struct->request;
    }
}

/*!
    \brief      initialize DMA multi data mode
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel is initialized
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  dma_multi_data_parameter_struct: the data needed to initialize DMA multi data mode
                  request: DMA_REQUEST_x x is the type of request
                  periph_addr: peripheral base address
                  periph_width: DMA_PERIPH_WIDTH_8BIT,DMA_PERIPH_WIDTH_16BIT,DMA_PERIPH_WIDTH_32BIT
                  periph_inc: DMA_PERIPH_INCREASE_ENABLE,DMA_PERIPH_INCREASE_DISABLE,DMA_PERIPH_INCREASE_FIX
                  memory0_addr: memory0 base address
                  memory_width: DMA_MEMORY_WIDTH_8BIT,DMA_MEMORY_WIDTH_16BIT,DMA_MEMORY_WIDTH_32BIT
                  memory_inc: DMA_MEMORY_INCREASE_ENABLE,DMA_MEMORY_INCREASE_DISABLE
                  memory_burst_width: DMA_MEMORY_BURST_SINGLE,DMA_MEMORY_BURST_4_BEAT,DMA_MEMORY_BURST_8_BEAT,DMA_MEMORY_BURST_16_BEAT
                  periph_burst_width: DMA_PERIPH_BURST_SINGLE,DMA_PERIPH_BURST_4_BEAT,DMA_PERIPH_BURST_8_BEAT,DMA_PERIPH_BURST_16_BEAT
                  critical_value: DMA_FIFO_1_WORD,DMA_FIFO_2_WORD,DMA_FIFO_3_WORD,DMA_FIFO_4_WORD
                  circular_mode: DMA_CIRCULAR_MODE_ENABLE,DMA_CIRCULAR_MODE_DISABLE
                  direction: DMA_PERIPH_TO_MEMORY,DMA_MEMORY_TO_PERIPH,DMA_MEMORY_TO_MEMORY
                  number: the number of remaining data to be transferred by the DMA
                  priority: DMA_PRIORITY_LOW,DMA_PRIORITY_MEDIUM,DMA_PRIORITY_HIGH,DMA_PRIORITY_ULTRA_HIGH
    \param[out] none
    \retval     none
*/
void dma_multi_data_mode_init(uint32_t dma_periph, dma_channel_enum channelx, dma_multi_data_parameter_struct *init_struct)
{
    uint32_t ctl;

    /* select multi data mode and configure FIFO critical value */
    DMA_CHFCTL(dma_periph, channelx) |= (DMA_CHXFCTL_MDMEN | init_struct->critical_value);

    /* configure peripheral base address */
    DMA_CHPADDR(dma_periph, channelx) = init_struct->periph_addr;

    /* configure memory base address */
    DMA_CHM0ADDR(dma_periph, channelx) = init_struct->memory0_addr;

    /* configure the number of remaining data to be transferred */
    DMA_CHCNT(dma_periph, channelx) = init_struct->number;

    /* configure peripheral and memory transfer width,channel priotity,transfer mode,peripheral and memory burst transfer width */
    ctl = DMA_CHCTL(dma_periph, channelx);
    ctl &= ~(DMA_CHXCTL_PWIDTH | DMA_CHXCTL_MWIDTH | DMA_CHXCTL_PRIO | DMA_CHXCTL_TM | DMA_CHXCTL_PBURST | DMA_CHXCTL_MBURST);
    ctl |= (init_struct->periph_width | (init_struct->memory_width) | init_struct->priority | init_struct->direction | init_struct->memory_burst_width |
            init_struct->periph_burst_width);
    DMA_CHCTL(dma_periph, channelx) = ctl;

    /* configure peripheral increasing mode */
    if(DMA_PERIPH_INCREASE_ENABLE == init_struct->periph_inc)
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
    } else if(DMA_PERIPH_INCREASE_DISABLE == init_struct->periph_inc)
    {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_PNAGA;
    } else {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PAIF;
    }

    /* configure memory increasing mode */
    if(DMA_MEMORY_INCREASE_ENABLE == init_struct->memory_inc)
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MNAGA;
    } else {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MNAGA;
    }

    /* configure DMA circular mode */
    if(DMA_CIRCULAR_MODE_ENABLE == init_struct->circular_mode)
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_CMEN;
    } else {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_CMEN;
    }

    if(DMA0 == dma_periph)
    {
        DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_MUXID;
        DMAMUX_RM_CHXCFG(channelx) |= init_struct->request;
    } else {
        DMAMUX_RM_CHXCFG((uint32_t)channelx + 8U) &= ~DMAMUX_RM_CHXCFG_MUXID;
        DMAMUX_RM_CHXCFG((uint32_t)channelx + 8U) |= init_struct->request;
    }
}

/*!
    \brief      configure DMA peripheral base address
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to set peripheral base address
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  address: peripheral base address, ranges from 0x00000000 to 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void dma_periph_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t address)
{
    DMA_CHPADDR(dma_periph, channelx) = address;
}

/*!
    \brief      configure DMA memory base address
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to set memory base address
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  memory_flag: the selected memory
      \arg        DMA_MEMORY_0: DMA memory 0
      \arg        DMA_MEMORY_1: DMA memory 1
    \param[in]  address: memory base address
    \param[out] none
    \retval     none
*/
void dma_memory_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t memory_flag, uint32_t address)
{
    if(memory_flag)
    {
        DMA_CHM1ADDR(dma_periph, channelx) = address;
    } else {
        DMA_CHM0ADDR(dma_periph, channelx) = address;
    }
}

/*!
    \brief      configure the number of remaining data to be transferred by the DMA
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to set number
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  number: the number of remaining data to be transferred by the DMA, ranges from 0x00000000 to 0x0000FFFF
    \param[out] none
    \retval     none
*/
void dma_transfer_number_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t number)
{
    DMA_CHCNT(dma_periph, channelx) = number;
}

/*!
    \brief      get the number of remaining data to be transferred by the DMA
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to get number
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     uint32_t: the number of remaining data to be transferred by the DMA, ranges from 0x00000000 to 0x0000FFFF
*/
uint32_t dma_transfer_number_get(uint32_t dma_periph, dma_channel_enum channelx)
{
    return (uint32_t)DMA_CHCNT(dma_periph, channelx);
}

/*!
    \brief      configure priority level of DMA channel
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  priority: priority level of this channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_PRIORITY_LOW: low priority
      \arg        DMA_PRIORITY_MEDIUM: medium priority
      \arg        DMA_PRIORITY_HIGH: high priority
      \arg        DMA_PRIORITY_ULTRA_HIGH: ultra high priority
    \param[out] none
    \retval     none
*/
void dma_priority_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t priority)
{
    uint32_t ctl;
    /* acquire DMA_CHxCTL register */
    ctl = DMA_CHCTL(dma_periph, channelx);
    /* assign regiser */
    ctl &= ~DMA_CHXCTL_PRIO;
    ctl |= priority;
    DMA_CHCTL(dma_periph, channelx) = ctl;
}

/*!
    \brief      configure transfer burst beats of memory
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  mbeat: memory transfer burst beats
      \arg        DMA_MEMORY_BURST_SINGLE: memory transfer single burst
      \arg        DMA_MEMORY_BURST_4_BEAT: memory transfer 4-beat burst
      \arg        DMA_MEMORY_BURST_8_BEAT: memory transfer 8-beat burst
      \arg        DMA_MEMORY_BURST_16_BEAT: memory transfer 16-beat burst
    \param[out] none
    \retval     none
*/
void dma_memory_burst_beats_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t mbeat)
{
    uint32_t ctl;
    /* acquire DMA_CHxCTL register */
    ctl = DMA_CHCTL(dma_periph, channelx);
    /* assign regiser */
    ctl &= ~DMA_CHXCTL_MBURST;
    ctl |= mbeat;
    DMA_CHCTL(dma_periph, channelx) = ctl;
}

/*!
    \brief      configure transfer burst beats of peripheral
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  pbeat: peripheral transfer burst beats
                only one parameter can be selected which is shown as below:
      \arg        DMA_PERIPH_BURST_SINGLE: peripheral transfer single burst
      \arg        DMA_PERIPH_BURST_4_BEAT: peripheral transfer 4-beat burst
      \arg        DMA_PERIPH_BURST_8_BEAT: peripheral transfer 8-beat burst
      \arg        DMA_PERIPH_BURST_16_BEAT: peripheral transfer 16-beat burst
    \param[out] none
    \retval     none
*/
void dma_periph_burst_beats_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t pbeat)
{
    uint32_t ctl;
    /* acquire DMA_CHxCTL register */
    ctl = DMA_CHCTL(dma_periph, channelx);
    /* assign regiser */
    ctl &= ~DMA_CHXCTL_PBURST;
    ctl |= pbeat;
    DMA_CHCTL(dma_periph, channelx) = ctl;
}

/*!
    \brief      configure transfer data size of memory
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  msize: transfer data size of memory
                only one parameter can be selected which is shown as below:
      \arg        DMA_MEMORY_WIDTH_8BIT: transfer data size of memory is 8-bit
      \arg        DMA_MEMORY_WIDTH_16BIT: transfer data size of memory is 16-bit
      \arg        DMA_MEMORY_WIDTH_32BIT: transfer data size of memory is 32-bit
    \param[out] none
    \retval     none
*/
void dma_memory_width_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t msize)
{
    uint32_t ctl;
    /* acquire DMA_CHxCTL register */
    ctl = DMA_CHCTL(dma_periph, channelx);
    /* assign regiser */
    ctl &= ~DMA_CHXCTL_MWIDTH;
    ctl |= msize;
    DMA_CHCTL(dma_periph, channelx) = ctl;
}

/*!
    \brief      configure transfer data size of peripheral
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  psize: transfer data size of peripheral
                only one parameter can be selected which is shown as below:
      \arg        DMA_PERIPH_WIDTH_8BIT: transfer data size of peripheral is 8-bit
      \arg        DMA_PERIPH_WIDTH_16BIT: transfer data size of peripheral is 16-bit
      \arg        DMA_PERIPH_WIDTH_32BIT: transfer data size of peripheral is 32-bit
    \param[out] none
    \retval     none
*/
void dma_periph_width_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t psize)
{
    uint32_t ctl;
    /* acquire DMA_CHxCTL register */
    ctl = DMA_CHCTL(dma_periph, channelx);
    /* assign regiser */
    ctl &= ~DMA_CHXCTL_PWIDTH;
    ctl |= psize;
    DMA_CHCTL(dma_periph, channelx) = ctl;
}

/*!
    \brief      configure memory address generation algorithm
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  generation_algorithm: the address generation algorithm
                only one parameter can be selected which is shown as below:
      \arg        DMA_MEMORY_INCREASE_ENABLE: next address of memory is increasing address mode
      \arg        DMA_MEMORY_INCREASE_DISABLE: next address of memory is fixed address mode
    \param[out] none
    \retval     none
*/
void dma_memory_address_generation_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t generation_algorithm)
{
    if(DMA_MEMORY_INCREASE_ENABLE == generation_algorithm)
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MNAGA;
    } else {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MNAGA;
    }
}

/*!
    \brief      configure peripheral address generation algorithm
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  generation_algorithm: the address generation algorithm
                only one parameter can be selected which is shown as below:
      \arg        DMA_PERIPH_INCREASE_ENABLE: next address of peripheral is increasing address mode
      \arg        DMA_PERIPH_INCREASE_DISABLE: next address of peripheral is fixed address mode
      \arg        DMA_PERIPH_INCREASE_FIX: increasing steps of peripheral address is fixed
    \param[out] none
    \retval     none
*/
void dma_peripheral_address_generation_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t generation_algorithm)
{
    if(DMA_PERIPH_INCREASE_ENABLE == generation_algorithm)
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
    } else if(DMA_PERIPH_INCREASE_DISABLE == generation_algorithm)
    {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_PNAGA;
    } else {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PAIF;
    }
}

/*!
    \brief      enable DMA circulation mode
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_circulation_enable(uint32_t dma_periph, dma_channel_enum channelx)
{
    DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_CMEN;
}

/*!
    \brief      disable DMA circulation mode
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_circulation_disable(uint32_t dma_periph, dma_channel_enum channelx)
{
    DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_CMEN;
}

/*!
    \brief      enable DMA channel
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_channel_enable(uint32_t dma_periph, dma_channel_enum channelx)
{
    DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_CHEN;
}

/*!
    \brief      disable DMA channel
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_channel_disable(uint32_t dma_periph, dma_channel_enum channelx)
{
    DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_CHEN;
}

/*!
    \brief      configure the direction of  data transfer on the channel
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  direction: specify the direction of  data transfer
                only one parameter can be selected which is shown as below:
      \arg        DMA_PERIPH_TO_MEMORY: read from peripheral and write to memory
      \arg        DMA_MEMORY_TO_PERIPH: read from memory and write to peripheral
      \arg        DMA_MEMORY_TO_MEMORY: read from memory and write to memory
    \param[out] none
    \retval     none
*/
void dma_transfer_direction_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t direction)
{
    uint32_t ctl;
    /* acquire DMA_CHxCTL register */
    ctl = DMA_CHCTL(dma_periph, channelx);
    /* assign regiser */
    ctl &= ~DMA_CHXCTL_TM;
    ctl |= direction;

    DMA_CHCTL(dma_periph, channelx) = ctl;
}

/*!
    \brief      configure DMA switch buffer mode
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  memory1_addr: memory1 base address, ranges from 0x00000000 to 0xFFFFFFFF
    \param[in]  memory_select: the selected memory
      \arg        DMA_MEMORY_0: DMA memory 0
      \arg        DMA_MEMORY_1: DMA memory 1
    \param[out] none
    \retval     none
*/
void dma_switch_buffer_mode_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t memory1_addr, uint32_t memory_select)
{
    /* configure memory1 base address */
    DMA_CHM1ADDR(dma_periph, channelx) = memory1_addr;

    if(DMA_MEMORY_0 == memory_select)
    {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MBS;
    } else {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MBS;
    }
}

/*!
    \brief      get DMA using memory
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     the using memory, DMA_MEMORY_0 or DMA_MEMORY_1
*/
uint32_t dma_using_memory_get(uint32_t dma_periph, dma_channel_enum channelx)
{
    if((DMA_CHCTL(dma_periph, channelx)) & DMA_CHXCTL_MBS)
    {
        return DMA_MEMORY_1;
    } else {
        return DMA_MEMORY_0;
    }
}

/*!
    \brief      enable DMA switch buffer mode
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_switch_buffer_mode_enable(uint32_t dma_periph, dma_channel_enum channelx)
{
    /* enable switch buffer mode */
    DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_SBMEN;
}

/*!
    \brief      disable DMA switch buffer mode
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_switch_buffer_mode_disable(uint32_t dma_periph, dma_channel_enum channelx)
{
    /* disable switch buffer mode */
    DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_SBMEN;
}

/*!
    \brief      get DMA FIFO status
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     the number of words stored in FIFO
      \arg        DMA_FIFO_CNT_NO_DATA: no data
      \arg        DMA_FIFO_CNT_1_WORD: 1 word
      \arg        DMA_FIFO_CNT_2_WORD: 2 words
      \arg        DMA_FIFO_CNT_3_WORD: 3 words
      \arg        DMA_FIFO_CNT_EMPTY: empty
      \arg        DMA_FIFO_CNT_FULL: full
*/
uint32_t dma_fifo_status_get(uint32_t dma_periph, dma_channel_enum channelx)
{
    return ((DMA_CHFCTL(dma_periph, channelx) & DMA_CHXFCTL_FCNT)>>CHXFCTL_FCNT_OFFSET);
}

/*!
    \brief      get DMA flag
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to get flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  flag: specify get which flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_FLAG_FEE: FIFO error and exception flag
      \arg        DMA_FLAG_SDE: single data mode exception flag
      \arg        DMA_FLAG_TAE: transfer access error flag
      \arg        DMA_FLAG_HTF: half transfer finish flag
      \arg        DMA_FLAG_FTF: full transger finish flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dma_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag)
{
    if(channelx < DMA_CH4)
    {
        if(DMA_INTF0(dma_periph) & DMA_FLAG_ADD(flag, channelx))
        {
            return SET;
        } else {
            return RESET;
        }
    } else {
        channelx -= (dma_channel_enum)4;
        if(DMA_INTF1(dma_periph) & DMA_FLAG_ADD(flag, channelx))
        {
            return SET;
        } else {
            return RESET;
        }
    }
}

/*!
    \brief      clear DMA flag
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to clear flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  flag: specify get which flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_FLAG_FEE: FIFO error and exception flag
      \arg        DMA_FLAG_SDE: single data mode exception flag
      \arg        DMA_FLAG_TAE: transfer access error flag
      \arg        DMA_FLAG_HTF: half transfer finish flag
      \arg        DMA_FLAG_FTF: full transger finish flag
    \param[out] none
    \retval     none
*/
void dma_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag)
{
    if(channelx < DMA_CH4)
    {
        DMA_INTC0(dma_periph) |= DMA_FLAG_ADD(flag, channelx);
    } else {
        channelx -= (dma_channel_enum)4;
        DMA_INTC1(dma_periph) |= DMA_FLAG_ADD(flag, channelx);
    }
}

/*!
    \brief      enable DMA interrupt
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  interrupt: specify which interrupt to enbale
                one or more parameters can be selected which are shown as below:
      \arg        DMA_INT_SDE: single data mode exception interrupt
      \arg        DMA_INT_TAE: tranfer access error interrupt
      \arg        DMA_INT_HTF: half transfer finish interrupt
      \arg        DMA_INT_FTF: full transfer finish interrupt
      \arg        DMA_INT_FEE: FIFO exception interrupt
    \param[out] none
    \retval     none
*/
void dma_interrupt_enable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt)
{
    if(DMA_CHXFCTL_FEEIE != (DMA_CHXFCTL_FEEIE & interrupt))
    {
        DMA_CHCTL(dma_periph, channelx) |= interrupt;
    } else {
        DMA_CHFCTL(dma_periph, channelx) |= DMA_CHXFCTL_FEEIE;
        DMA_CHCTL(dma_periph, channelx) |= (interrupt & (~DMA_CHXFCTL_FEEIE));
    }
}

/*!
    \brief      disable DMA interrupt
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  interrupt: specify which interrupt to disbale
                one or more parameters can be selected which are shown as below:
      \arg        DMA_INT_SDE: single data mode exception interrupt
      \arg        DMA_INT_TAE: tranfer access error interrupt
      \arg        DMA_INT_HTF: half transfer finish interrupt
      \arg        DMA_INT_FTF: full transfer finish interrupt
      \arg        DMA_INT_FEE: FIFO exception interrupt
    \param[out] none
    \retval     none
*/
void dma_interrupt_disable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt)
{
    if(DMA_CHXFCTL_FEEIE != (DMA_CHXFCTL_FEEIE & interrupt))
    {
        DMA_CHCTL(dma_periph, channelx) &= ~interrupt;
    } else {
        DMA_CHFCTL(dma_periph, channelx) &= ~DMA_CHXFCTL_FEEIE;
        DMA_CHCTL(dma_periph, channelx) &= ~(interrupt & (~DMA_CHXFCTL_FEEIE));
    }
}

/*!
    \brief      get DMA interrupt flag
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to get interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  int_flag: specify get which flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_INT_FLAG_FEE: FIFO error and exception flag
      \arg        DMA_INT_FLAG_SDE: single data mode exception flag
      \arg        DMA_INT_FLAG_TAE: transfer access error flag
      \arg        DMA_INT_FLAG_HTF: half transfer finish flag
      \arg        DMA_INT_FLAG_FTF: full transger finish flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dma_interrupt_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t int_flag)
{
    uint32_t interrupt_enable = 0U, interrupt_flag = 0U;

    dma_channel_enum channel_flag_offset = channelx;
    /* flags for channel0-3 */
    if(channelx < DMA_CH4)
    {
        switch(int_flag)
        {
        case DMA_INTF_FEEIF:
            interrupt_flag = DMA_INTF0(dma_periph) & DMA_FLAG_ADD(int_flag, channelx);
            interrupt_enable = DMA_CHFCTL(dma_periph, channelx) & DMA_CHXFCTL_FEEIE;
            break;
        case DMA_INTF_SDEIF:
            interrupt_flag = DMA_INTF0(dma_periph) & DMA_FLAG_ADD(int_flag, channelx);
            interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_SDEIE;
            break;
        case DMA_INTF_TAEIF:
            interrupt_flag = DMA_INTF0(dma_periph) & DMA_FLAG_ADD(int_flag, channelx);
            interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_TAEIE;
            break;
        case DMA_INTF_HTFIF:
            interrupt_flag = DMA_INTF0(dma_periph) & DMA_FLAG_ADD(int_flag, channelx);
            interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_HTFIE;
            break;
        case DMA_INTF_FTFIF:
            interrupt_flag = (DMA_INTF0(dma_periph) & DMA_FLAG_ADD(int_flag, channelx));
            interrupt_enable = (DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_FTFIE);
            break;
        default:
            break;
        }
    /* flags for channel4-7 */
    } else {
        channel_flag_offset -= (dma_channel_enum)4U;
        switch(int_flag)
        {
        case DMA_INTF_FEEIF:
            interrupt_flag = DMA_INTF1(dma_periph) & DMA_FLAG_ADD(int_flag, channel_flag_offset);
            interrupt_enable = DMA_CHFCTL(dma_periph, channelx) & DMA_CHXFCTL_FEEIE;
            break;
        case DMA_INTF_SDEIF:
            interrupt_flag = DMA_INTF1(dma_periph) & DMA_FLAG_ADD(int_flag, channel_flag_offset);
            interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_SDEIE;
            break;
        case DMA_INTF_TAEIF:
            interrupt_flag = DMA_INTF1(dma_periph) & DMA_FLAG_ADD(int_flag, channel_flag_offset);
            interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_TAEIE;
            break;
        case DMA_INTF_HTFIF:
            interrupt_flag = DMA_INTF1(dma_periph) & DMA_FLAG_ADD(int_flag, channel_flag_offset);
            interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_HTFIE;
            break;
        case DMA_INTF_FTFIF:
            interrupt_flag = DMA_INTF1(dma_periph) & DMA_FLAG_ADD(int_flag, channel_flag_offset);
            interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_FTFIE;
            break;
        default:
            break;
        }
    }

    if(interrupt_flag && interrupt_enable)
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear DMA interrupt flag
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to clear interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  int_flag: specify get which flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_INT_FLAG_FEE: FIFO error and exception flag
      \arg        DMA_INT_FLAG_SDE: single data mode exception flag
      \arg        DMA_INT_FLAG_TAE: transfer access error flag
      \arg        DMA_INT_FLAG_HTF: half transfer finish flag
      \arg        DMA_INT_FLAG_FTF: full transger finish flag
    \param[out] none
    \retval     none
*/
void dma_interrupt_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t int_flag)
{
    if(channelx < DMA_CH4)
    {
        DMA_INTC0(dma_periph) |= DMA_FLAG_ADD(int_flag, channelx);
    } else {
        channelx -= (dma_channel_enum)4U;
        DMA_INTC1(dma_periph) |= DMA_FLAG_ADD(int_flag, channelx);
    }
}

/*!
    \brief      initialize the parameters of DMAMUX synchronization mode structure with the default values
    \param[in]  none
    \param[out] init_struct: the initialization data needed to initialize DMAMUX request multiplexer channel synchronization mode
    \retval     none
*/
void dmamux_sync_struct_para_init(dmamux_sync_parameter_struct *init_struct)
{
    if(NULL == init_struct)
    {
        DMA_WRONG_HANDLE
    }

    /* set the DMAMUX synchronization structure with the default values */
    init_struct->sync_id        = DMAMUX_SYNC_EVT0_OUT;
    init_struct->sync_polarity  = DMAMUX_SYNC_RISING;
    init_struct->request_number = 1U;
}

/*!
    \brief      initialize DMAMUX request multiplexer channel synchronization mode
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is initialized
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..15)
    \param[in]  init_struct: the data needed to initialize DMAMUX request multiplexer channel
                  sync_id: DMAMUX_SYNC_EXTI0, DMAMUX_SYNC_EXTI1, DMAMUX_SYNC_EXTI2, DMAMUX_SYNC_EXTI3,
                           DMAMUX_SYNC_EXTI4, DMAMUX_SYNC_EXTI5, DMAMUX_SYNC_EXTI6, DMAMUX_SYNC_EXTI7,
                           DMAMUX_SYNC_EXTI8, DMAMUX_SYNC_EXTI9, DMAMUX_SYNC_EXTI10, DMAMUX_SYNC_EXTI11,
                           DMAMUX_SYNC_EXTI12, DMAMUX_SYNC_EXTI13, DMAMUX_SYNC_EXTI14, DMAMUX_SYNC_EXTI15,
                           DMAMUX_SYNC_EVT0_OUT, DMAMUX_SYNC_EVT1_OUT, DMAMUX_SYNC_EVT2_OUT, DMAMUX_SYNC_EVT3_OUT,
                           DMAMUX_SYNC_EVT4_OUT, DMAMUX_SYNC_EVT5_OUT, DMAMUX_SYNC_EVT6_OUT, DMAMUX_SYNC_RTC_WAKEUP,
                           DMAMUX_SYNC_CMP0_OUTPUT, DMAMUX_SYNC_I2C0_WAKEUP, DMAMUX_SYNC_I2C1_WAKEUP, DMAMUX_SYNC_I2C2_WAKEUP,
                           DMAMUX_SYNC_I2C3_WAKEUP
                  sync_polarity: DMAMUX_SYNC_NO_EVENT, DMAMUX_SYNC_RISING, DMAMUX_SYNC_FALLING, DMAMUX_SYNC_RISING_FALLING
                  request_number: the number of DMA request that will be authorized after a sync event, from 1 to 32
    \param[out] none
    \retval     none
*/
void dmamux_synchronization_init(dmamux_multiplexer_channel_enum channelx, dmamux_sync_parameter_struct *init_struct)
{
    uint32_t cfg;

    if(NULL == init_struct)
    {
        DMA_WRONG_HANDLE
    }

    /* disable synchronization mode and event generation for DMA request forward number configuration */
    DMAMUX_RM_CHXCFG(channelx) &= ~(DMAMUX_RM_CHXCFG_SYNCEN | DMAMUX_RM_CHXCFG_EVGEN);

    /* configure synchronization input identification, synchronization input polarity, number of DMA requests to forward */
    cfg = DMAMUX_RM_CHXCFG(channelx);
    cfg &= ~(DMAMUX_RM_CHXCFG_SYNCID | DMAMUX_RM_CHXCFG_NBR | DMAMUX_RM_CHXCFG_SYNCP);
    cfg |= (init_struct->sync_polarity | (init_struct->sync_id) | RM_CHXCFG_NBR(init_struct->request_number - 1U));
    DMAMUX_RM_CHXCFG(channelx) = cfg;
}

/*!
    \brief      enable synchronization mode
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dmamux_synchronization_enable(dmamux_multiplexer_channel_enum channelx)
{
    DMAMUX_RM_CHXCFG(channelx) |= DMAMUX_RM_CHXCFG_SYNCEN;
}

/*!
    \brief      disable synchronization mode
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dmamux_synchronization_disable(dmamux_multiplexer_channel_enum channelx)
{
    DMAMUX_RM_CHXCFG(channelx) &= (~DMAMUX_RM_CHXCFG_SYNCEN);
}
/*!
    \brief      enable event generation
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dmamux_event_generation_enable(dmamux_multiplexer_channel_enum channelx)
{
    DMAMUX_RM_CHXCFG(channelx) |= DMAMUX_RM_CHXCFG_EVGEN;
}

/*!
    \brief      disable event generation
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dmamux_event_generation_disable(dmamux_multiplexer_channel_enum channelx)
{
    DMAMUX_RM_CHXCFG(channelx) &= (~DMAMUX_RM_CHXCFG_EVGEN);
}

/*!
    \brief      initialize the parameters of DMAMUX request generator structure with the default values
    \param[in]  none
    \param[out] init_struct: the initialization data needed to initialize DMAMUX request generator channel
    \retval     none
*/
void dmamux_gen_struct_para_init(dmamux_gen_parameter_struct *init_struct)
{
    if(NULL == init_struct)
    {
        DMA_WRONG_HANDLE
    }

    /* set the DMAMUX request generator structure with the default values */
    init_struct->trigger_id        = DMAMUX_SYNC_EVT0_OUT;
    init_struct->trigger_polarity  = DMAMUX_SYNC_RISING;
    init_struct->request_number = 1U;
}

/*!
    \brief      initialize DMAMUX request generator channel
    \param[in]  channelx: specify which DMAMUX request generator channel is initialized
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[in]  init_struct: the data needed to initialize DMAMUX request generator channel
                  trigger_id: DMAMUX_TRIGGER_EXTI0, DMAMUX_TRIGGER_EXTI1, DMAMUX_TRIGGER_EXTI2, DMAMUX_TRIGGER_EXTI3,
                              DMAMUX_TRIGGER_EXTI4, DMAMUX_TRIGGER_EXTI5, DMAMUX_TRIGGER_EXTI6, DMAMUX_TRIGGER_EXTI7,
                              DMAMUX_TRIGGER_EXTI8, DMAMUX_TRIGGER_EXTI9, DMAMUX_TRIGGER_EXTI10, DMAMUX_TRIGGER_EXTI11,
                              DMAMUX_TRIGGER_EXTI12, DMAMUX_TRIGGER_EXTI13, DMAMUX_TRIGGER_EXTI14, DMAMUX_TRIGGER_EXTI15,
                              DMAMUX_TRIGGER_EVT0_OUT, DMAMUX_TRIGGER_EVT1_OUT, DMAMUX_TRIGGER_EVT2_OUT, DMAMUX_TRIGGER_EVT3_OUT,
                              DMAMUX_SYNC_EVT4_OUT, DMAMUX_SYNC_EVT5_OUT, DMAMUX_SYNC_EVT6_OUT, DMAMUX_SYNC_RTC_WAKEUP,
                              DMAMUX_SYNC_CMP0_OUTPUT, DMAMUX_SYNC_I2C0_WAKEUP, DMAMUX_SYNC_I2C1_WAKEUP, DMAMUX_SYNC_I2C2_WAKEUP,
                              DMAMUX_SYNC_I2C3_WAKEUP
                  trigger_polarity: DMAMUX_GEN_NO_EVENT, DMAMUX_GEN_RISING, DMAMUX_GEN_FALLING, DMAMUX_GEN_RISING_FALLING
                  request_number: the number of DMA request that will be generated after a signal event, from 1 to 32
    \param[out] none
    \retval     none
*/
void dmamux_request_generator_init(dmamux_generator_channel_enum channelx, dmamux_gen_parameter_struct *init_struct)
{
    uint32_t cfg;

    if(NULL == init_struct)
    {
        DMA_WRONG_HANDLE
    }

    /* disable DMAMUX request generator channel for DMA request generation number configuration */
    DMAMUX_RG_CHXCFG(channelx) &= ~(DMAMUX_RG_CHXCFG_RGEN);

    /* configure trigger input identification, trigger polarity, number of DMA requests to be generated */
    cfg = DMAMUX_RG_CHXCFG(channelx);
    cfg &= ~(DMAMUX_RG_CHXCFG_TID | DMAMUX_RG_CHXCFG_NBRG | DMAMUX_RG_CHXCFG_RGTP);
    cfg |= (RG_CHXCFG_NBRG(init_struct->request_number - 1U) | init_struct->trigger_id | init_struct->trigger_polarity);
    DMAMUX_RG_CHXCFG(channelx) = cfg;
}

/*!
    \brief      enable DMAMUX request generator channel
    \param[in]  channelx: specify which DMAMUX request generator channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dmamux_request_generator_channel_enable(dmamux_generator_channel_enum channelx)
{
    DMAMUX_RG_CHXCFG(channelx) |= DMAMUX_RG_CHXCFG_RGEN;
}

/*!
    \brief      disable DMAMUX request generator channel
    \param[in]  channelx: specify which DMAMUX request generator channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dmamux_request_generator_channel_disable(dmamux_generator_channel_enum channelx)
{
    DMAMUX_RG_CHXCFG(channelx) &= (~DMAMUX_RG_CHXCFG_RGEN);
}

/*!
    \brief      configure synchronization input polarity
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..15)
    \param[in]  polarity: synchronization input polarity
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_SYNC_NO_EVENT: no event detection
      \arg        DMAMUX_SYNC_RISING: rising edge
      \arg        DMAMUX_SYNC_FALLING: falling edge
      \arg        DMAMUX_SYNC_RISING_FALLING: rising and falling edges
    \param[out] none
    \retval     none
*/
void dmamux_synchronization_polarity_config(dmamux_multiplexer_channel_enum channelx, uint32_t polarity)
{
    DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_SYNCP;
    DMAMUX_RM_CHXCFG(channelx) |= polarity;
}

/*!
    \brief      configure number of DMA requests to forward
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..15)
    \param[in]  number: DMA requests number to forward
                only one parameter can be selected which is shown as below:
      \arg        1 - 32
    \param[out] none
    \retval     none
*/
void dmamux_request_forward_number_config(dmamux_multiplexer_channel_enum channelx, uint32_t number)
{
    DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_NBR;
    DMAMUX_RM_CHXCFG(channelx) |= ((number - 1U) << RM_CHXCFG_NBR_OFFSET);
}

/*!
    \brief      configure synchronization input identification
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..15)
    \param[in]  id: synchronization input identification
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_SYNC_EXTI0: synchronization input is EXTI0
      \arg        DMAMUX_SYNC_EXTI1: synchronization input is EXTI1
      \arg        DMAMUX_SYNC_EXTI2: synchronization input is EXTI2
      \arg        DMAMUX_SYNC_EXTI3: synchronization input is EXTI3
      \arg        DMAMUX_SYNC_EXTI4: synchronization input is EXTI4
      \arg        DMAMUX_SYNC_EXTI5: synchronization input is EXTI5
      \arg        DMAMUX_SYNC_EXTI6: synchronization input is EXTI6
      \arg        DMAMUX_SYNC_EXTI7: synchronization input is EXTI7
      \arg        DMAMUX_SYNC_EXTI8: synchronization input is EXTI8
      \arg        DMAMUX_SYNC_EXTI9: synchronization input is EXTI9
      \arg        DMAMUX_SYNC_EXTI10: synchronization input is EXTI10
      \arg        DMAMUX_SYNC_EXTI11: synchronization input is EXTI11
      \arg        DMAMUX_SYNC_EXTI12: synchronization input is EXTI12
      \arg        DMAMUX_SYNC_EXTI13: synchronization input is EXTI13
      \arg        DMAMUX_SYNC_EXTI14: synchronization input is EXTI14
      \arg        DMAMUX_SYNC_EXTI15: synchronization input is EXTI15
      \arg        DMAMUX_SYNC_EVT0_OUT: synchronization input is Evt0_out
      \arg        DMAMUX_SYNC_EVT1_OUT: synchronization input is Evt1_out
      \arg        DMAMUX_SYNC_EVT2_OUT: synchronization input is Evt2_out
      \arg        DMAMUX_SYNC_EVT3_OUT: synchronization input is Evt3_out
      \arg        DMAMUX_SYNC_EVT4_OUT: synchronization input is Evt4_out
      \arg        DMAMUX_SYNC_EVT5_OUT: synchronization input is Evt5_out
      \arg        DMAMUX_SYNC_EVT6_OUT: synchronization input is Evt6_out
      \arg        DMAMUX_SYNC_RTC_WAKEUP: synchronization input is RTC wakeup
      \arg        DMAMUX_SYNC_CMP0_OUTPUT: synchronization input is CMP0 output
      \arg        DMAMUX_SYNC_I2C0_WAKEUP: synchronization input is I2C0 wakeup
      \arg        DMAMUX_SYNC_I2C1_WAKEUP: synchronization input is I2C1 wakeup
      \arg        DMAMUX_SYNC_I2C2_WAKEUP: synchronization input is I2C2 wakeup
      \arg        DMAMUX_SYNC_I2C3_WAKEUP: synchronization input is I2C3 wakeup
    \param[out] none
    \retval     none
*/
void dmamux_sync_id_config(dmamux_multiplexer_channel_enum channelx, uint32_t id)
{
    DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_SYNCID;
    DMAMUX_RM_CHXCFG(channelx) |= id;
}

/*!
    \brief      configure multiplexer input identification
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..15)
    \param[in]  id: input DMA request identification
                only one parameter can be selected which is shown as below:
      \arg        DMA_REQUEST_M2M: memory to memory transfer
      \arg        DMA_REQUEST_GENERATOR0: DMAMUX request generator 0
      \arg        DMA_REQUEST_GENERATOR1: DMAMUX request generator 1
      \arg        DMA_REQUEST_GENERATOR2: DMAMUX request generator 2
      \arg        DMA_REQUEST_GENERATOR3: DMAMUX request generator 3
      \arg        DMA_REQUEST_GENERATOR4: DMAMUX request generator 4
      \arg        DMA_REQUEST_GENERATOR5: DMAMUX request generator 5
      \arg        DMA_REQUEST_GENERATOR6: DMAMUX request generator 6
      \arg        DMA_REQUEST_GENERATOR7: DMAMUX request generator 7
      \arg        DMA_REQUEST_ADC0: DMAMUX ADC0 request
      \arg        DMA_REQUEST_ADC1: DMAMUX ADC1 request
      \arg        DMA_REQUEST_TIMER0_CH0: DMAMUX TIMER0 CH0 request
      \arg        DMA_REQUEST_TIMER0_CH1: DMAMUX TIMER0 CH1 request
      \arg        DMA_REQUEST_TIMER0_CH2: DMAMUX TIMER0 CH2 request
      \arg        DMA_REQUEST_TIMER0_CH3: DMAMUX TIMER0 CH3 request
      \arg        DMA_REQUEST_TIMER0_MCH0: DMAMUX TIMER0 MCH0 request
      \arg        DMA_REQUEST_TIMER0_MCH1: DMAMUX TIMER0 MCH1 request
      \arg        DMA_REQUEST_TIMER0_MCH2: DMAMUX TIMER0 MCH2 request
      \arg        DMA_REQUEST_TIMER0_MCH3: DMAMUX TIMER0 MCH3 request
      \arg        DMA_REQUEST_TIMER0_UP: DMAMUX TIMER0 UP request
      \arg        DMA_REQUEST_TIMER0_TRG: DMAMUX TIMER0 TRG request
      \arg        DMA_REQUEST_TIMER0_CMT: DMAMUX TIMER0 CMT request
      \arg        DMA_REQUEST_TIMER1_CH0: DMAMUX TIMER1 CH0 request
      \arg        DMA_REQUEST_TIMER1_CH1: DMAMUX TIMER1 CH1 request
      \arg        DMA_REQUEST_TIMER1_CH2: DMAMUX TIMER1 CH2 request
      \arg        DMA_REQUEST_TIMER1_CH3: DMAMUX TIMER1 CH3 request
      \arg        DMA_REQUEST_TIMER1_UP: DMAMUX TIMER1 UP request
      \arg        DMA_REQUEST_TIMER1_TRG: DMAMUX TIMER1 TRG request
      \arg        DMA_REQUEST_TIMER2_CH0: DMAMUX TIMER2 CH0 request
      \arg        DMA_REQUEST_TIMER2_CH1: DMAMUX TIMER2 CH1 request
      \arg        DMA_REQUEST_TIMER2_CH2: DMAMUX TIMER2 CH2 request
      \arg        DMA_REQUEST_TIMER2_CH3: DMAMUX TIMER2 CH3 request
      \arg        DMA_REQUEST_TIMER2_UP: DMAMUX TIMER2 UP request
      \arg        DMA_REQUEST_TIMER2_TRG: DMAMUX TIMER2 TRG request
      \arg        DMA_REQUEST_TIMER3_CH0: DMAMUX TIMER3 CH0 request
      \arg        DMA_REQUEST_TIMER3_CH1: DMAMUX TIMER3 CH1 request
      \arg        DMA_REQUEST_TIMER3_CH2: DMAMUX TIMER3 CH2 request
      \arg        DMA_REQUEST_TIMER3_CH3: DMAMUX TIMER3 CH3 request
      \arg        DMA_REQUEST_TIMER3_TRG: DMAMUX TIMER3 TRG request
      \arg        DMA_REQUEST_TIMER3_UP: DMAMUX TIMER3 UP request
      \arg        DMA_REQUEST_I2C0_RX: DMAMUX I2C0 RX request
      \arg        DMA_REQUEST_I2C0_TX: DMAMUX I2C0 TX request
      \arg        DMA_REQUEST_I2C1_RX: DMAMUX I2C1 RX request
      \arg        DMA_REQUEST_I2C1_TX: DMAMUX I2C1 TX request
      \arg        DMA_REQUEST_SPI0_RX: DMAMUX SPI0 RX request
      \arg        DMA_REQUEST_SPI0_TX: DMAMUX SPI0 TX request
      \arg        DMA_REQUEST_SPI1_RX: DMAMUX SPI1 RX request
      \arg        DMA_REQUEST_SPI1_TX: DMAMUX SPI1 TX request
      \arg        DMA_REQUEST_USART0_RX: DMAMUX USART0 RX request
      \arg        DMA_REQUEST_USART0_TX: DMAMUX USART0 TX request
      \arg        DMA_REQUEST_USART1_RX: DMAMUX USART1 RX request
      \arg        DMA_REQUEST_USART1_TX: DMAMUX USART1 TX request
      \arg        DMA_REQUEST_USART2_RX: DMAMUX USART2 RX request
      \arg        DMA_REQUEST_USART2_TX: DMAMUX USART2 TX request
      \arg        DMA_REQUEST_TIMER7_CH0: DMAMUX TIMER7 CH0 request
      \arg        DMA_REQUEST_TIMER7_CH1: DMAMUX TIMER7 CH1 request
      \arg        DMA_REQUEST_TIMER7_CH2: DMAMUX TIMER7 CH2 request
      \arg        DMA_REQUEST_TIMER7_CH3: DMAMUX TIMER7 CH3 request
      \arg        DMA_REQUEST_TIMER7_MCH0: DMAMUX TIMER7 MCH0 request
      \arg        DMA_REQUEST_TIMER7_MCH1: DMAMUX TIMER7 MCH1 request
      \arg        DMA_REQUEST_TIMER7_MCH2: DMAMUX TIMER7 MCH2 request
      \arg        DMA_REQUEST_TIMER7_MCH3: DMAMUX TIMER7 MCH3 request
      \arg        DMA_REQUEST_TIMER7_UP: DMAMUX TIMER7 UP request
      \arg        DMA_REQUEST_TIMER7_TRG: DMAMUX TIMER7 TRG request
      \arg        DMA_REQUEST_TIMER7_CMT: DMAMUX TIMER7 CMT request
      \arg        DMA_REQUEST_TIMER4_CH0: DMAMUX TIMER4 CH0 request
      \arg        DMA_REQUEST_TIMER4_CH1: DMAMUX TIMER4 CH1 request
      \arg        DMA_REQUEST_TIMER4_CH2: DMAMUX TIMER4 CH2 request
      \arg        DMA_REQUEST_TIMER4_CH3: DMAMUX TIMER4 CH3 request
      \arg        DMA_REQUEST_TIMER4_UP: DMAMUX TIMER4 UP request
      \arg        DMA_REQUEST_TIMER4_CMT: DMAMUX TIMER4 CMT request
      \arg        DMA_REQUEST_TIMER4_TRG: DMAMUX TIMER4 TRG request
      \arg        DMA_REQUEST_SPI2_RX: DMAMUX SPI2 RX request
      \arg        DMA_REQUEST_SPI2_TX: DMAMUX SPI2 TX request
      \arg        DMA_REQUEST_UART3_RX: DMAMUX UART3 RX request
      \arg        DMA_REQUEST_UART3_TX: DMAMUX UART3 TX request
      \arg        DMA_REQUEST_UART4_RX: DMAMUX UART4 RX request
      \arg        DMA_REQUEST_UART4_TX: DMAMUX UART4 TX request
      \arg        DMA_REQUEST_DAC_CH0: DMAMUX DAC CH0 request
      \arg        DMA_REQUEST_DAC_CH1: DMAMUX DAC CH1 request
      \arg        DMA_REQUEST_TIMER5_UP: DMAMUX TIMER5 UP request
      \arg        DMA_REQUEST_TIMER6_UP: DMAMUX TIMER6 UP request
      \arg        DMA_REQUEST_USART5_RX: DMAMUX USART5 RX request
      \arg        DMA_REQUEST_USART5_TX: DMAMUX USART5 TX request
      \arg        DMA_REQUEST_I2C2_RX: DMAMUX I2C2 RX request
      \arg        DMA_REQUEST_I2C2_TX: DMAMUX I2C2 TX request
      \arg        DMA_REQUEST_DCI: DMAMUX DCI request
      \arg        DMA_REQUEST_CAU_IN: DMAMUX CAU IN request
      \arg        DMA_REQUEST_CAU_OUT: DMAMUX CAU OUT request
      \arg        DMA_REQUEST_HAU_IN: DMAMUX HAU IN request
      \arg        DMA_REQUEST_UART6_RX: DMAMUX UART6 RX request
      \arg        DMA_REQUEST_UART6_TX: DMAMUX UART6 TX request
      \arg        DMA_REQUEST_UART7_RX: DMAMUX UART7 RX request
      \arg        DMA_REQUEST_UART7_TX: DMAMUX UART7 TX request
      \arg        DMA_REQUEST_SPI3_RX: DMAMUX SPI3 RX request
      \arg        DMA_REQUEST_SPI3_TX: DMAMUX SPI3 TX request
      \arg        DMA_REQUEST_SPI4_RX: DMAMUX SPI4 RX request
      \arg        DMA_REQUEST_SPI4_TX: DMAMUX SPI4 TX request
      \arg        DMA_REQUEST_SAI0_B0: DMAMUX SAI0 B0 request
      \arg        DMA_REQUEST_SAI0_B1: DMAMUX SAI0 B1 request
      \arg        DMA_REQUEST_RSPDIF_DATA: DMAMUX RSPDIF DATA request
      \arg        DMA_REQUEST_RSPDIF_CS: DMAMUX RSPDIF CS request
      \arg        DMA_REQUEST_HPDF_FLT0: DMAMUX HPDF FLT0 request
      \arg        DMA_REQUEST_HPDF_FLT1: DMAMUX HPDF FLT1 request
      \arg        DMA_REQUEST_HPDF_FLT2: DMAMUX HPDF FLT2 request
      \arg        DMA_REQUEST_HPDF_FLT3: DMAMUX HPDF FLT3 request
      \arg        DMA_REQUEST_TIMER14_CH0: DMAMUX TIMER14 CH0 request
      \arg        DMA_REQUEST_TIMER14_CH1: DMAMUX TIMER14 CH1 request
      \arg        DMA_REQUEST_TIMER14_MCH0: DMAMUX TIMER14 MCH0 request
      \arg        DMA_REQUEST_TIMER14_UP: DMAMUX TIMER14 UP request
      \arg        DMA_REQUEST_TIMER14_TRG: DMAMUX TIMER14 TRG request
      \arg        DMA_REQUEST_TIMER14_CMT: DMAMUX TIMER14 CMT request
      \arg        DMA_REQUEST_TIMER15_CH0: DMAMUX TIMER15 CH0 request
      \arg        DMA_REQUEST_TIMER15_MCH0: DMAMUX TIMER15 MCH0 request
      \arg        DMA_REQUEST_TIMER15_UP: DMAMUX TIMER15 UP request
      \arg        DMA_REQUEST_TIMER16_CH0: DMAMUX TIMER16 CH0 request
      \arg        DMA_REQUEST_TIMER16_MCH0: DMAMUX TIMER16 MCH0 request
      \arg        DMA_REQUEST_TIMER16_UP: DMAMUX TIMER16 TRG request
      \arg        DMA_REQUEST_ADC2: DMAMUX ADC2 request
      \arg        DMA_REQUEST_FAC_READ: DMAMUX FAC READ request
      \arg        DMA_REQUEST_FAC_WRITE: DMAMUX FAC WRITE request
      \arg        DMA_REQUEST_TMU_INPUT: DMAMUX TMU INPUT request
      \arg        DMA_REQUEST_TMU_OUTPUT: DMAMUX TMU OUTPUT request
      \arg        DMA_REQUEST_TIMER22_CH0: DMAMUX TIMER22 CH0 request
      \arg        DMA_REQUEST_TIMER22_CH1: DMAMUX TIMER22 CH1 request
      \arg        DMA_REQUEST_TIMER22_CH2: DMAMUX TIMER22 CH2 request
      \arg        DMA_REQUEST_TIMER22_CH3: DMAMUX TIMER22 CH3 request
      \arg        DMA_REQUEST_TIMER22_UP: DMAMUX TIMER22 UP request
      \arg        DMA_REQUEST_TIMER22_TRG: DMAMUX TIMER22 TRG request
      \arg        DMA_REQUEST_TIMER23_CH0: DMAMUX TIMER23 CH0 request
      \arg        DMA_REQUEST_TIMER23_CH1: DMAMUX TIMER23 CH1 request
      \arg        DMA_REQUEST_TIMER23_CH2: DMAMUX TIMER23 CH2 request
      \arg        DMA_REQUEST_TIMER23_CH3: DMAMUX TIMER23 CH3 request
      \arg        DMA_REQUEST_TIMER23_UP: DMAMUX TIMER23 UP request
      \arg        DMA_REQUEST_TIMER23_TRG: DMAMUX TIMER23 TRG request
      \arg        DMA_REQUEST_TIMER30_CH0: DMAMUX TIMER30 CH0 request
      \arg        DMA_REQUEST_TIMER30_CH1: DMAMUX TIMER30 CH1 request
      \arg        DMA_REQUEST_TIMER30_CH2: DMAMUX TIMER30 CH2 request
      \arg        DMA_REQUEST_TIMER30_CH3: DMAMUX TIMER30 CH3 request
      \arg        DMA_REQUEST_TIMER30_UP: DMAMUX TIMER30 UP request
      \arg        DMA_REQUEST_TIMER30_TRG: DMAMUX TIMER30 TRG request
      \arg        DMA_REQUEST_TIMER31_CH0: DMAMUX TIMER31 CH0 request
      \arg        DMA_REQUEST_TIMER31_CH1: DMAMUX TIMER31 CH1 request
      \arg        DMA_REQUEST_TIMER31_CH2: DMAMUX TIMER31 CH2 request
      \arg        DMA_REQUEST_TIMER31_CH3: DMAMUX TIMER31 CH3 request
      \arg        DMA_REQUEST_TIMER31_UP: DMAMUX TIMER31 UP request
      \arg        DMA_REQUEST_TIMER31_TRG: DMAMUX TIMER31 TRG request
      \arg        DMA_REQUEST_TIMER40_CH0: DMAMUX TIMER40 CH0 request
      \arg        DMA_REQUEST_TIMER40_MCH0: DMAMUX TIMER40 MCH0 request
      \arg        DMA_REQUEST_TIMER40_CMT: DMAMUX TIMER40 CMT request
      \arg        DMA_REQUEST_TIMER40_UP: DMAMUX TIMER40 UP request
      \arg        DMA_REQUEST_TIMER41_CH0: DMAMUX TIMER41 CH0 request
      \arg        DMA_REQUEST_TIMER41_MCH0: DMAMUX TIMER41 MCH0 request
      \arg        DMA_REQUEST_TIMER41_CMT: DMAMUX TIMER41 CMT request
      \arg        DMA_REQUEST_TIMER41_UP: DMAMUX TIMER41 UP request
      \arg        DMA_REQUEST_TIMER42_CH0: DMAMUX TIMER42 CH0 request
      \arg        DMA_REQUEST_TIMER42_MCH0: DMAMUX TIMER42 MCH0 request
      \arg        DMA_REQUEST_TIMER42_CMT: DMAMUX TIMER42 CMT request
      \arg        DMA_REQUEST_TIMER42_UP: DMAMUX TIMER42 UP request
      \arg        DMA_REQUEST_TIMER43_CH0: DMAMUX TIMER43 CH0 request
      \arg        DMA_REQUEST_TIMER43_MCH0: DMAMUX TIMER43 MCH0 request
      \arg        DMA_REQUEST_TIMER43_CMT: DMAMUX TIMER43 CMT request
      \arg        DMA_REQUEST_TIMER43_UP: DMAMUX TIMER43 UP request
      \arg        DMA_REQUEST_TIMER44_CH0: DMAMUX TIMER44 CH0 request
      \arg        DMA_REQUEST_TIMER44_MCH0: DMAMUX TIMER44 MCH0 request
      \arg        DMA_REQUEST_TIMER44_CMT: DMAMUX TIMER44 CMT request
      \arg        DMA_REQUEST_TIMER44_UP: DMAMUX TIMER44 UP request
      \arg        DMA_REQUEST_TIMER50_UP: DMAMUX TIMER50 UP request
      \arg        DMA_REQUEST_TIMER51_UP: DMAMUX TIMER51 UP request
      \arg        DMA_REQUEST_SAI1_B0: DMAMUX SAI1 B0 request
      \arg        DMA_REQUEST_SAI1_B1: DMAMUX SAI1 B1 request
      \arg        DMA_REQUEST_SAI2_B0: DMAMUX SAI2 B0 request
      \arg        DMA_REQUEST_SAI2_B1: DMAMUX SAI2 B1 request
      \arg        DMA_REQUEST_SPI5_RX: DMAMUX SPI5 RX request
      \arg        DMA_REQUEST_SPI5_TX: DMAMUX SPI5 TX request
      \arg        DMA_REQUEST_I2C3_RX: DMAMUX I2C3 RX request
      \arg        DMA_REQUEST_I2C3_TX: DMAMUX I2C3 TX request
      \arg        DMA_REQUEST_CAN0: DMAMUX CAN0 request
      \arg        DMA_REQUEST_CAN1: DMAMUX CAN1 request
      \arg        DMA_REQUEST_CAN2: DMAMUX CAN2 request
      \arg        DMA_REQUEST_TIMER40_CH1: DMAMUX TIMER40 CH1 request
      \arg        DMA_REQUEST_TIMER40_TRG: DMAMUX TIMER40 TRG request
      \arg        DMA_REQUEST_TIMER41_CH1: DMAMUX TIMER41 CH1 request
      \arg        DMA_REQUEST_TIMER41_TRG: DMAMUX TIMER41 TRG request
      \arg        DMA_REQUEST_TIMER42_CH1: DMAMUX TIMER42 CH1 request
      \arg        DMA_REQUEST_TIMER42_TRG: DMAMUX TIMER42 TRG request
      \arg        DMA_REQUEST_TIMER43_CH1: DMAMUX TIMER43 CH1 request
      \arg        DMA_REQUEST_TIMER43_TRG: DMAMUX TIMER43 TRG request
      \arg        DMA_REQUEST_TIMER44_CH1: DMAMUX TIMER44 CH1 request
      \arg        DMA_REQUEST_TIMER44_TRG: DMAMUX TIMER44 TRG request
    \param[out] none
    \retval     none
*/
void dmamux_request_id_config(dmamux_multiplexer_channel_enum channelx, uint32_t id)
{
    DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_MUXID;
    DMAMUX_RM_CHXCFG(channelx) |= id;
}

/*!
    \brief      configure trigger input polarity
    \param[in]  channelx: specify which DMAMUX request generator channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[in]  polarity: trigger input polarity
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GEN_NO_EVENT: no event detection
      \arg        DMAMUX_GEN_RISING: rising edge
      \arg        DMAMUX_GEN_FALLING: falling edge
      \arg        DMAMUX_GEN_RISING_FALLING: rising and falling edges
    \param[out] none
    \retval     none
*/
void dmamux_trigger_polarity_config(dmamux_generator_channel_enum channelx, uint32_t polarity)
{
    DMAMUX_RG_CHXCFG(channelx) &= ~DMAMUX_RG_CHXCFG_RGTP;
    DMAMUX_RG_CHXCFG(channelx) |= polarity;
}

/*!
    \brief      configure number of DMA requests to be generated
    \param[in]  channelx: specify which DMAMUX request generator channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[in]  number: DMA requests number to be generated
                only one parameter can be selected which is shown as below:
      \arg        1 - 32
    \param[out] none
    \retval     none
*/
void dmamux_request_generate_number_config(dmamux_generator_channel_enum channelx, uint32_t number)
{
    DMAMUX_RG_CHXCFG(channelx) &= ~DMAMUX_RG_CHXCFG_NBRG;
    DMAMUX_RG_CHXCFG(channelx) |= ((number - 1U) << RG_CHXCFG_NBRG_OFFSET);
}

/*!
    \brief      configure trigger input identification
    \param[in]  channelx: specify which DMAMUX request generator channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[in]  id: trigger input identification
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_TRIGGER_EXTI0: trigger input is EXTI0
      \arg        DMAMUX_TRIGGER_EXTI1: trigger input is EXTI1
      \arg        DMAMUX_TRIGGER_EXTI2: trigger input is EXTI2
      \arg        DMAMUX_TRIGGER_EXTI3: trigger input is EXTI3
      \arg        DMAMUX_TRIGGER_EXTI4: trigger input is EXTI4
      \arg        DMAMUX_TRIGGER_EXTI5: trigger input is EXTI5
      \arg        DMAMUX_TRIGGER_EXTI6: trigger input is EXTI6
      \arg        DMAMUX_TRIGGER_EXTI7: trigger input is EXTI7
      \arg        DMAMUX_TRIGGER_EXTI8: trigger input is EXTI8
      \arg        DMAMUX_TRIGGER_EXTI9: trigger input is EXTI9
      \arg        DMAMUX_TRIGGER_EXTI10: trigger input is EXTI10
      \arg        DMAMUX_TRIGGER_EXTI11: trigger input is EXTI11
      \arg        DMAMUX_TRIGGER_EXTI12: trigger input is EXTI12
      \arg        DMAMUX_TRIGGER_EXTI13: trigger input is EXTI13
      \arg        DMAMUX_TRIGGER_EXTI14: trigger input is EXTI14
      \arg        DMAMUX_TRIGGER_EXTI15: trigger input is EXTI15
      \arg        DMAMUX_TRIGGER_EVT0_OUT: trigger input is Evt0_out
      \arg        DMAMUX_TRIGGER_EVT1_OUT: trigger input is Evt1_out
      \arg        DMAMUX_TRIGGER_EVT2_OUT: trigger input is Evt2_out
      \arg        DMAMUX_TRIGGER_EVT3_OUT: trigger input is Evt3_out
      \arg        DMAMUX_TRIGGER_EVT4_OUT: trigger input is Evt4_out
      \arg        DMAMUX_TRIGGER_EVT5_OUT: trigger input is Evt5_out
      \arg        DMAMUX_TRIGGER_EVT6_OUT: trigger input is Evt6_out
      \arg        DMAMUX_TRIGGER_RTC_WAKEUP: trigger input is wakeup
      \arg        DMAMUX_TRIGGER_CMP0_OUTPUT: trigger input is CMP0 output
      \arg        DMAMUX_TRIGGER_CMP1_OUTPUT: trigger input is CMP1 output
      \arg        DMAMUX_TRIGGER_I2C0_WAKEUP: trigger input is I2C0 wakeup
      \arg        DMAMUX_TRIGGER_I2C1_WAKEUP: trigger input is I2C1 wakeup
      \arg        DMAMUX_TRIGGER_I2C2_WAKEUP: trigger input is I2C2 wakeup
      \arg        DMAMUX_TRIGGER_I2C3_WAKEUP: trigger input is I2C3 wakeup
      \arg        DMAMUX_TRIGGER_I2C0_INT_EVENT: trigger input is I2C0 interrupt event
      \arg        DMAMUX_TRIGGER_I2C1_INT_EVENT: trigger input is I2C1 interrupt event
      \arg        DMAMUX_TRIGGER_I2C2_INT_EVENT: trigger input is I2C2 interrupt event
      \arg        DMAMUX_TRIGGER_I2C3_INT_EVENT: trigger input is I2C3 interrupt event
      \arg        DMAMUX_TRIGGER_ADC2_INT: ADC2 interrupt
    \param[out] none
    \retval     none
*/
void dmamux_trigger_id_config(dmamux_generator_channel_enum channelx, uint32_t id)
{
    DMAMUX_RG_CHXCFG(channelx) &= ~DMAMUX_RG_CHXCFG_TID;
    DMAMUX_RG_CHXCFG(channelx) |= id;
}

/*!
    \brief      get DMAMUX flag
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_FLAG_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun flag
      \arg        DMAMUX_FLAG_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dmamux_flag_get(dmamux_flag_enum flag)
{
    FlagStatus reval;

    if(RESET != (DMAMUX_REG_VAL(flag) & BIT(DMAMUX_BIT_POS(flag))))
    {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      clear DMAMUX flag
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_FLAG_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun flag
      \arg        DMAMUX_FLAG_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun flag
    \param[out] none
    \retval     none
*/
void dmamux_flag_clear(dmamux_flag_enum flag)
{
    DMAMUX_REG_VAL3(flag) = BIT(DMAMUX_BIT_POS(flag));
}

/*!
    \brief      enable DMAMUX interrupt
    \param[in]  interrupt: specify which interrupt to enable
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_INT_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun interrupt
      \arg        DMAMUX_INT_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun interrupt
    \param[out] none
    \retval     none
*/
void dmamux_interrupt_enable(dmamux_interrupt_enum interrupt)
{
    DMAMUX_REG_VAL(interrupt) |= BIT(DMAMUX_BIT_POS(interrupt));
}

/*!
    \brief      disable DMAMUX interrupt
    \param[in]  interrupt: specify which interrupt to disable
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_INT_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun interrupt
      \arg        DMAMUX_INT_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun interrupt
    \param[out] none
    \retval     none
*/
void dmamux_interrupt_disable(dmamux_interrupt_enum interrupt)
{
    DMAMUX_REG_VAL(interrupt) &= ~BIT(DMAMUX_BIT_POS(interrupt));
}

/*!
    \brief      get DMAMUX interrupt flag
    \param[in]  int_flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_INT_FLAG_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dmamux_interrupt_flag_get(dmamux_interrupt_flag_enum int_flag)
{
    FlagStatus reval;
    uint32_t intenable = 0U, flagstatus = 0U;

    /* get the interrupt enable bit status */
    intenable = (DMAMUX_REG_VAL2(int_flag) & BIT(DMAMUX_BIT_POS2(int_flag)));
    /* get the corresponding flag bit status */
    flagstatus = (DMAMUX_REG_VAL(int_flag) & BIT(DMAMUX_BIT_POS(int_flag)));

    if(flagstatus && intenable)
    {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      clear DMAMUX interrupt flag
    \param[in]  int_flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_INT_FLAG_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun interrupt flag
    \param[out] none
    \retval     none
*/
void dmamux_interrupt_flag_clear(dmamux_interrupt_flag_enum int_flag)
{
    DMAMUX_REG_VAL3(int_flag) = BIT(DMAMUX_BIT_POS(int_flag));
}
