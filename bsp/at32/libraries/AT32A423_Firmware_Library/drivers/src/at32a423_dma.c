/**
  **************************************************************************
  * @file     at32a423_dma.c
  * @brief    contains all the functions for the dma firmware library
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32a423_conf.h"

/** @addtogroup AT32A423_periph_driver
  * @{
  */

/** @defgroup DMA
  * @brief DMA driver modules
  * @{
  */

#ifdef DMA_MODULE_ENABLED

/** @defgroup DMA_private_functions
  * @{
  */

/**
  * @brief  reset dmax channely register.
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  *         - DMA2_CHANNEL1
  *         - DMA2_CHANNEL2
  *         - DMA2_CHANNEL3
  *         - DMA2_CHANNEL4
  *         - DMA2_CHANNEL5
  *         - DMA2_CHANNEL6
  *         - DMA2_CHANNEL7
  * @retval none.
  */
void dma_reset(dma_channel_type *dmax_channely)
{
  uint32_t temp = 0;
  dmax_channely->ctrl_bit.chen = FALSE;
  dmax_channely->ctrl = 0;
  dmax_channely->dtcnt = 0;
  dmax_channely->paddr = 0;
  dmax_channely->maddr = 0;

  temp = (uint32_t)dmax_channely;

  if((temp & 0x6FF) < 0x608)
  {
    /* dma1 channel */
    DMA1->clr |= (uint32_t)(0x0F << ((((temp & 0xFF) - 0x08) / 0x14) * 4));
  }
  else if((temp & 0x6FF) < 0x688)
  {
    /* dma2 channel */
    DMA2->clr |= (uint32_t)(0x0F << ((((temp & 0xFF) - 0x08) / 0x14) * 4));
  }
}

/**
  * @brief  set the number of data to be transferred.
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  *         - DMA2_CHANNEL1
  *         - DMA2_CHANNEL2
  *         - DMA2_CHANNEL3
  *         - DMA2_CHANNEL4
  *         - DMA2_CHANNEL5
  *         - DMA2_CHANNEL6
  *         - DMA2_CHANNEL7
  * @param  data_number: the number of data to be transferred (0x0000~0xFFFF).
  * @retval none.
  */
void dma_data_number_set(dma_channel_type *dmax_channely, uint16_t data_number)
{
  dmax_channely->dtcnt = data_number;
}

/**
  * @brief  get the number of data to be transferred.
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  *         - DMA2_CHANNEL1
  *         - DMA2_CHANNEL2
  *         - DMA2_CHANNEL3
  *         - DMA2_CHANNEL4
  *         - DMA2_CHANNEL5
  *         - DMA2_CHANNEL6
  *         - DMA2_CHANNEL7
  * @retval the number value.
  */
uint16_t dma_data_number_get(dma_channel_type *dmax_channely)
{
  return (uint16_t)dmax_channely->dtcnt;
}

/**
  * @brief  enable or disable dma interrupt.
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  *         - DMA2_CHANNEL1
  *         - DMA2_CHANNEL2
  *         - DMA2_CHANNEL3
  *         - DMA2_CHANNEL4
  *         - DMA2_CHANNEL5
  *         - DMA2_CHANNEL6
  *         - DMA2_CHANNEL7
  * @param  dma_int:
  *         this parameter can be any combination of the following values:
  *         - DMA_FDT_INT
  *         - DMA_HDT_INT
  *         - DMA_DTERR_INT
  * @param  new_state (TRUE or FALSE)
  * @retval none.
  */
void dma_interrupt_enable(dma_channel_type *dmax_channely, uint32_t dma_int, confirm_state new_state)
{
  if(new_state != FALSE)
  {
    dmax_channely->ctrl |= dma_int;
  }
  else
  {
    dmax_channely->ctrl &= ~dma_int;
  }
}

/**
  * @brief  enable or disable dma channel.
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  *         - DMA2_CHANNEL1
  *         - DMA2_CHANNEL2
  *         - DMA2_CHANNEL3
  *         - DMA2_CHANNEL4
  *         - DMA2_CHANNEL5
  *         - DMA2_CHANNEL6
  *         - DMA2_CHANNEL7
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void dma_channel_enable(dma_channel_type *dmax_channely, confirm_state new_state)
{
  dmax_channely->ctrl_bit.chen = new_state;
}

/**
  * @brief  dma interrupt flag get.
  * @param  dma_flag
  *         - DMA1_FDT1_FLAG        - DMA1_HDT1_FLAG        - DMA1_DTERR1_FLAG
  *         - DMA1_FDT2_FLAG        - DMA1_HDT2_FLAG        - DMA1_DTERR2_FLAG
  *         - DMA1_FDT3_FLAG        - DMA1_HDT3_FLAG        - DMA1_DTERR3_FLAG
  *         - DMA1_FDT4_FLAG        - DMA1_HDT4_FLAG        - DMA1_DTERR4_FLAG
  *         - DMA1_FDT5_FLAG        - DMA1_HDT5_FLAG        - DMA1_DTERR5_FLAG
  *         - DMA1_FDT6_FLAG        - DMA1_HDT6_FLAG        - DMA1_DTERR6_FLAG
  *         - DMA1_FDT7_FLAG        - DMA1_HDT7_FLAG        - DMA1_DTERR7_FLAG
  *         - DMA2_FDT1_FLAG        - DMA2_HDT1_FLAG        - DMA2_DTERR1_FLAG
  *         - DMA2_FDT2_FLAG        - DMA2_HDT2_FLAG        - DMA2_DTERR2_FLAG
  *         - DMA2_FDT3_FLAG        - DMA2_HDT3_FLAG        - DMA2_DTERR3_FLAG
  *         - DMA2_FDT4_FLAG        - DMA2_HDT4_FLAG        - DMA2_DTERR4_FLAG
  *         - DMA2_FDT5_FLAG        - DMA2_HDT5_FLAG        - DMA2_DTERR5_FLAG
  *         - DMA2_FDT6_FLAG        - DMA2_HDT6_FLAG        - DMA2_DTERR6_FLAG
  *         - DMA2_FDT7_FLAG        - DMA2_HDT7_FLAG        - DMA2_DTERR7_FLAG
  * @retval state of dma flag.
  */
flag_status dma_interrupt_flag_get(uint32_t dmax_flag)
{
  uint32_t temp = 0;

  if(dmax_flag > 0x10000000)
  {
    temp = DMA2->sts;
  }
  else
  {
    temp = DMA1->sts;
  }

  if((temp & dmax_flag) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  dma flag get.
  * @param  dma_flag
  *         - DMA1_GL1_FLAG        - DMA1_FDT1_FLAG        - DMA1_HDT1_FLAG        - DMA1_DTERR1_FLAG
  *         - DMA1_GL2_FLAG        - DMA1_FDT2_FLAG        - DMA1_HDT2_FLAG        - DMA1_DTERR2_FLAG
  *         - DMA1_GL3_FLAG        - DMA1_FDT3_FLAG        - DMA1_HDT3_FLAG        - DMA1_DTERR3_FLAG
  *         - DMA1_GL4_FLAG        - DMA1_FDT4_FLAG        - DMA1_HDT4_FLAG        - DMA1_DTERR4_FLAG
  *         - DMA1_GL5_FLAG        - DMA1_FDT5_FLAG        - DMA1_HDT5_FLAG        - DMA1_DTERR5_FLAG
  *         - DMA1_GL6_FLAG        - DMA1_FDT6_FLAG        - DMA1_HDT6_FLAG        - DMA1_DTERR6_FLAG
  *         - DMA1_GL7_FLAG        - DMA1_FDT7_FLAG        - DMA1_HDT7_FLAG        - DMA1_DTERR7_FLAG
  *         - DMA2_GL1_FLAG        - DMA2_FDT1_FLAG        - DMA2_HDT1_FLAG        - DMA2_DTERR1_FLAG
  *         - DMA2_GL2_FLAG        - DMA2_FDT2_FLAG        - DMA2_HDT2_FLAG        - DMA2_DTERR2_FLAG
  *         - DMA2_GL3_FLAG        - DMA2_FDT3_FLAG        - DMA2_HDT3_FLAG        - DMA2_DTERR3_FLAG
  *         - DMA2_GL4_FLAG        - DMA2_FDT4_FLAG        - DMA2_HDT4_FLAG        - DMA2_DTERR4_FLAG
  *         - DMA2_GL5_FLAG        - DMA2_FDT5_FLAG        - DMA2_HDT5_FLAG        - DMA2_DTERR5_FLAG
  *         - DMA2_GL6_FLAG        - DMA2_FDT6_FLAG        - DMA2_HDT6_FLAG        - DMA2_DTERR6_FLAG
  *         - DMA2_GL7_FLAG        - DMA2_FDT7_FLAG        - DMA2_HDT7_FLAG        - DMA2_DTERR7_FLAG
  * @retval state of dma flag.
  */
flag_status dma_flag_get(uint32_t dmax_flag)
{
  uint32_t temp = 0;

  if(dmax_flag > 0x10000000)
  {
    temp = DMA2->sts;
  }
  else
  {
    temp = DMA1->sts;
  }

  if((temp & dmax_flag) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  dma flag clear.
  * @param  dma_flag
  *         this parameter can be one of the following values:
  *         - DMA1_GL1_FLAG        - DMA1_FDT1_FLAG        - DMA1_HDT1_FLAG        - DMA1_DTERR1_FLAG
  *         - DMA1_GL2_FLAG        - DMA1_FDT2_FLAG        - DMA1_HDT2_FLAG        - DMA1_DTERR2_FLAG
  *         - DMA1_GL3_FLAG        - DMA1_FDT3_FLAG        - DMA1_HDT3_FLAG        - DMA1_DTERR3_FLAG
  *         - DMA1_GL4_FLAG        - DMA1_FDT4_FLAG        - DMA1_HDT4_FLAG        - DMA1_DTERR4_FLAG
  *         - DMA1_GL5_FLAG        - DMA1_FDT5_FLAG        - DMA1_HDT5_FLAG        - DMA1_DTERR5_FLAG
  *         - DMA1_GL6_FLAG        - DMA1_FDT6_FLAG        - DMA1_HDT6_FLAG        - DMA1_DTERR6_FLAG
  *         - DMA1_GL7_FLAG        - DMA1_FDT7_FLAG        - DMA1_HDT7_FLAG        - DMA1_DTERR7_FLAG
  *         - DMA2_GL1_FLAG        - DMA2_FDT1_FLAG        - DMA2_HDT1_FLAG        - DMA2_DTERR1_FLAG
  *         - DMA2_GL2_FLAG        - DMA2_FDT2_FLAG        - DMA2_HDT2_FLAG        - DMA2_DTERR2_FLAG
  *         - DMA2_GL3_FLAG        - DMA2_FDT3_FLAG        - DMA2_HDT3_FLAG        - DMA2_DTERR3_FLAG
  *         - DMA2_GL4_FLAG        - DMA2_FDT4_FLAG        - DMA2_HDT4_FLAG        - DMA2_DTERR4_FLAG
  *         - DMA2_GL5_FLAG        - DMA2_FDT5_FLAG        - DMA2_HDT5_FLAG        - DMA2_DTERR5_FLAG
  *         - DMA2_GL6_FLAG        - DMA2_FDT6_FLAG        - DMA2_HDT6_FLAG        - DMA2_DTERR6_FLAG
  *         - DMA2_GL7_FLAG        - DMA2_FDT7_FLAG        - DMA2_HDT7_FLAG        - DMA2_DTERR7_FLAG
  * @retval none.
  */
void dma_flag_clear(uint32_t dmax_flag)
{
  if(dmax_flag > ((uint32_t)0x10000000))
  {
    DMA2->clr = (uint32_t)(dmax_flag & 0x0FFFFFFF);
  }
  else
  {
    DMA1->clr = dmax_flag;
  }
}

/**
  * @brief  dma init config with its default value.
  * @param  dma_init_struct: pointer to a dma_init_type structure which will be initialized.
  * @retval none.
  */
void dma_default_para_init(dma_init_type *dma_init_struct)
{
  dma_init_struct->peripheral_base_addr = 0;
  dma_init_struct->memory_base_addr = 0;
  dma_init_struct->direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct->buffer_size = 0;
  dma_init_struct->peripheral_inc_enable = FALSE;
  dma_init_struct->memory_inc_enable = FALSE;
  dma_init_struct->peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct->memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct->loop_mode_enable = FALSE;
  dma_init_struct->priority = DMA_PRIORITY_LOW;
}

/**
  * @brief  dma init.
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  *         - DMA2_CHANNEL1
  *         - DMA2_CHANNEL2
  *         - DMA2_CHANNEL3
  *         - DMA2_CHANNEL4
  *         - DMA2_CHANNEL5
  *         - DMA2_CHANNEL6
  *         - DMA2_CHANNEL7
  * @param  dma_init_struct: pointer to a dma_init_type structure.
  * @retval none.
  */
void dma_init(dma_channel_type *dmax_channely, dma_init_type *dma_init_struct)
{
  /* clear ctrl register dtd bit and m2m bit */
  dmax_channely->ctrl &= 0xbfef;
  dmax_channely->ctrl |= dma_init_struct->direction;

  dmax_channely->ctrl_bit.chpl = dma_init_struct->priority;
  dmax_channely->ctrl_bit.mwidth = dma_init_struct->memory_data_width;
  dmax_channely->ctrl_bit.pwidth = dma_init_struct->peripheral_data_width;
  dmax_channely->ctrl_bit.mincm = dma_init_struct->memory_inc_enable;
  dmax_channely->ctrl_bit.pincm = dma_init_struct->peripheral_inc_enable;
  dmax_channely->ctrl_bit.lm = dma_init_struct->loop_mode_enable;
  dmax_channely->dtcnt_bit.cnt = dma_init_struct->buffer_size;
  dmax_channely->paddr = dma_init_struct->peripheral_base_addr;
  dmax_channely->maddr = dma_init_struct->memory_base_addr;
}
/**
  * @brief  dmamux init.
  * @param  dma_x: pointer to a dma_type structure, can be DMA1 or DMA2.
  * @param  dmamux_channelx:
  *         this parameter can be one of the following values:
  *         - DMA1MUX_CHANNEL1
  *         - DMA1MUX_CHANNEL2
  *         - DMA1MUX_CHANNEL3
  *         - DMA1MUX_CHANNEL4
  *         - DMA1MUX_CHANNEL5
  *         - DMA1MUX_CHANNEL6
  *         - DMA1MUX_CHANNEL7
  *         - DMA2MUX_CHANNEL1
  *         - DMA2MUX_CHANNEL2
  *         - DMA2MUX_CHANNEL3
  *         - DMA2MUX_CHANNEL4
  *         - DMA2MUX_CHANNEL5
  *         - DMA2MUX_CHANNEL6
  *         - DMA2MUX_CHANNEL7
  * @param  dmamux_req_sel:
  *         this parameter can be one of the following values:
  *         - DMAMUX_DMAREQ_ID_REQ_G1        - DMAMUX_DMAREQ_ID_REQ_G2        - DMAMUX_DMAREQ_ID_REQ_G3        - DMAMUX_DMAREQ_ID_REQ_G4
  *         - DMAMUX_DMAREQ_ID_ADC1          - DMAMUX_DMAREQ_ID_DAC1          - DMAMUX_DMAREQ_ID_DAC2          - DMAMUX_DMAREQ_ID_TMR6_OVERFLOW
  *         - DMAMUX_DMAREQ_ID_TMR7_OVERFLOW - DMAMUX_DMAREQ_ID_SPI1_RX       - DMAMUX_DMAREQ_ID_SPI1_TX       - DMAMUX_DMAREQ_ID_SPI2_RX
  *         - DMAMUX_DMAREQ_ID_SPI2_TX       - DMAMUX_DMAREQ_ID_SPI3_RX       - DMAMUX_DMAREQ_ID_SPI3_TX       - DMAMUX_DMAREQ_ID_I2C1_RX
  *         - DMAMUX_DMAREQ_ID_I2C1_TX       - DMAMUX_DMAREQ_ID_I2C2_RX       - DMAMUX_DMAREQ_ID_I2C2_TX       - DMAMUX_DMAREQ_ID_I2C3_RX
  *         - DMAMUX_DMAREQ_ID_I2C3_TX       - DMAMUX_DMAREQ_ID_USART1_RX     - DMAMUX_DMAREQ_ID_USART1_TX     - DMAMUX_DMAREQ_ID_USART2_RX
  *         - DMAMUX_DMAREQ_ID_USART2_TX     - DMAMUX_DMAREQ_ID_USART3_RX     - DMAMUX_DMAREQ_ID_USART3_TX     - DMAMUX_DMAREQ_ID_USART4_RX
  *         - DMAMUX_DMAREQ_ID_USART4_TX     - DMAMUX_DMAREQ_ID_USART5_RX     - DMAMUX_DMAREQ_ID_USART5_TX     - DMAMUX_DMAREQ_ID_USART6_RX
  *         - DMAMUX_DMAREQ_ID_USART6_TX     - DMAMUX_DMAREQ_ID_USART7_RX     - DMAMUX_DMAREQ_ID_USART7_TX     - DMAMUX_DMAREQ_ID_USART8_RX
  *         - DMAMUX_DMAREQ_ID_USART8_TX     - DMAMUX_DMAREQ_ID_TMR1_CH1      - DMAMUX_DMAREQ_ID_TMR1_CH2      - DMAMUX_DMAREQ_ID_TMR1_CH3
  *         - DMAMUX_DMAREQ_ID_TMR1_CH4      - DMAMUX_DMAREQ_ID_TMR1_OVERFLOW - DMAMUX_DMAREQ_ID_TMR1_TRIG     - DMAMUX_DMAREQ_ID_TMR1_HALL
  *         - DMAMUX_DMAREQ_ID_TMR2_CH1      - DMAMUX_DMAREQ_ID_TMR2_CH2      - DMAMUX_DMAREQ_ID_TMR2_CH3      - DMAMUX_DMAREQ_ID_TMR2_CH4
  *         - DMAMUX_DMAREQ_ID_TMR2_OVERFLOW - DMAMUX_DMAREQ_ID_TMR2_TRIG     - DMAMUX_DMAREQ_ID_TMR3_CH1      - DMAMUX_DMAREQ_ID_TMR3_CH2
  *         - DMAMUX_DMAREQ_ID_TMR3_CH3      - DMAMUX_DMAREQ_ID_TMR3_CH4      - DMAMUX_DMAREQ_ID_TMR3_OVERFLOW - DMAMUX_DMAREQ_ID_TMR3_TRIG
  *         - DMAMUX_DMAREQ_ID_TMR4_CH1      - DMAMUX_DMAREQ_ID_TMR4_CH2      - DMAMUX_DMAREQ_ID_TMR4_CH3      - DMAMUX_DMAREQ_ID_TMR4_CH4
  *         - DMAMUX_DMAREQ_ID_TMR4_OVERFLOW - DMAMUX_DMAREQ_ID_TMR4_TRIG     - DMAMUX_DMAREQ_ID_TMR9_CH1      - DMAMUX_DMAREQ_ID_TMR9_CH2
  *         - DMAMUX_DMAREQ_ID_TMR9_OVERFLOW - DMAMUX_DMAREQ_ID_TMR9_TRIG     - DMAMUX_DMAREQ_ID_TMR9_HALL     - DMAMUX_DMAREQ_ID_TMR10_CH1
  *         - DMAMUX_DMAREQ_ID_TMR10_OVERFLOW- DMAMUX_DMAREQ_ID_TMR11_CH1     - DMAMUX_DMAREQ_ID_TMR11_OVERFLOW- DMAMUX_DMAREQ_ID_TMR12_CH1
  *         - DMAMUX_DMAREQ_ID_TMR12_CH2     - DMAMUX_DMAREQ_ID_TMR12_OVERFLOW- DMAMUX_DMAREQ_ID_TMR12_TRIG    - DMAMUX_DMAREQ_ID_TMR12_HALL
  *         - DMAMUX_DMAREQ_ID_TMR13_CH1     - DMAMUX_DMAREQ_ID_TMR13_OVERFLOW- DMAMUX_DMAREQ_ID_TMR14_CH1     - DMAMUX_DMAREQ_ID_TMR14_OVERFLOW
  * @retval none.
  */
void dma_flexible_config(dma_type* dma_x, dmamux_channel_type *dmamux_channelx, dmamux_requst_id_sel_type dmamux_req_sel)
{
  dma_x->muxsel_bit.tblsel = TRUE;
  dmamux_channelx->muxctrl_bit.reqsel = dmamux_req_sel;
}

/**
  * @brief  enable or disable the dmamux.
  * @param  dma_x: pointer to a dma_type structure, can be DMA1 or DMA2.
  * @param  new_state (TRUE or FALSE) .
  * @retval none.
  */
void dmamux_enable(dma_type *dma_x, confirm_state new_state)
{
  dma_x->muxsel_bit.tblsel = new_state;
}

/**
  * @brief  dmamux init.
  * @param  dmamux_channelx:
  *         this parameter can be one of the following values:
  *         - DMA1MUX_CHANNEL1
  *         - DMA1MUX_CHANNEL2
  *         - DMA1MUX_CHANNEL3
  *         - DMA1MUX_CHANNEL4
  *         - DMA1MUX_CHANNEL5
  *         - DMA1MUX_CHANNEL6
  *         - DMA1MUX_CHANNEL7
  *         - DMA2MUX_CHANNEL1
  *         - DMA2MUX_CHANNEL2
  *         - DMA2MUX_CHANNEL3
  *         - DMA2MUX_CHANNEL4
  *         - DMA2MUX_CHANNEL5
  *         - DMA2MUX_CHANNEL6
  *         - DMA2MUX_CHANNEL7
  * @param  dmamux_req_sel:
  *         this parameter can be one of the following values:
  *         - DMAMUX_DMAREQ_ID_REQ_G1        - DMAMUX_DMAREQ_ID_REQ_G2        - DMAMUX_DMAREQ_ID_REQ_G3        - DMAMUX_DMAREQ_ID_REQ_G4
  *         - DMAMUX_DMAREQ_ID_ADC1          - DMAMUX_DMAREQ_ID_DAC1          - DMAMUX_DMAREQ_ID_DAC2          - DMAMUX_DMAREQ_ID_TMR6_OVERFLOW
  *         - DMAMUX_DMAREQ_ID_TMR7_OVERFLOW - DMAMUX_DMAREQ_ID_SPI1_RX       - DMAMUX_DMAREQ_ID_SPI1_TX       - DMAMUX_DMAREQ_ID_SPI2_RX
  *         - DMAMUX_DMAREQ_ID_SPI2_TX       - DMAMUX_DMAREQ_ID_SPI3_RX       - DMAMUX_DMAREQ_ID_SPI3_TX       - DMAMUX_DMAREQ_ID_I2C1_RX
  *         - DMAMUX_DMAREQ_ID_I2C1_TX       - DMAMUX_DMAREQ_ID_I2C2_RX       - DMAMUX_DMAREQ_ID_I2C2_TX       - DMAMUX_DMAREQ_ID_I2C3_RX
  *         - DMAMUX_DMAREQ_ID_I2C3_TX       - DMAMUX_DMAREQ_ID_USART1_RX     - DMAMUX_DMAREQ_ID_USART1_TX     - DMAMUX_DMAREQ_ID_USART2_RX
  *         - DMAMUX_DMAREQ_ID_USART2_TX     - DMAMUX_DMAREQ_ID_USART3_RX     - DMAMUX_DMAREQ_ID_USART3_TX     - DMAMUX_DMAREQ_ID_USART4_RX
  *         - DMAMUX_DMAREQ_ID_USART4_TX     - DMAMUX_DMAREQ_ID_USART5_RX     - DMAMUX_DMAREQ_ID_USART5_TX     - DMAMUX_DMAREQ_ID_USART6_RX
  *         - DMAMUX_DMAREQ_ID_USART6_TX     - DMAMUX_DMAREQ_ID_USART7_RX     - DMAMUX_DMAREQ_ID_USART7_TX     - DMAMUX_DMAREQ_ID_USART8_RX
  *         - DMAMUX_DMAREQ_ID_USART8_TX     - DMAMUX_DMAREQ_ID_TMR1_CH1      - DMAMUX_DMAREQ_ID_TMR1_CH2      - DMAMUX_DMAREQ_ID_TMR1_CH3
  *         - DMAMUX_DMAREQ_ID_TMR1_CH4      - DMAMUX_DMAREQ_ID_TMR1_OVERFLOW - DMAMUX_DMAREQ_ID_TMR1_TRIG     - DMAMUX_DMAREQ_ID_TMR1_HALL
  *         - DMAMUX_DMAREQ_ID_TMR2_CH1      - DMAMUX_DMAREQ_ID_TMR2_CH2      - DMAMUX_DMAREQ_ID_TMR2_CH3      - DMAMUX_DMAREQ_ID_TMR2_CH4
  *         - DMAMUX_DMAREQ_ID_TMR2_OVERFLOW - DMAMUX_DMAREQ_ID_TMR2_TRIG     - DMAMUX_DMAREQ_ID_TMR3_CH1      - DMAMUX_DMAREQ_ID_TMR3_CH2
  *         - DMAMUX_DMAREQ_ID_TMR3_CH3      - DMAMUX_DMAREQ_ID_TMR3_CH4      - DMAMUX_DMAREQ_ID_TMR3_OVERFLOW - DMAMUX_DMAREQ_ID_TMR3_TRIG
  *         - DMAMUX_DMAREQ_ID_TMR4_CH1      - DMAMUX_DMAREQ_ID_TMR4_CH2      - DMAMUX_DMAREQ_ID_TMR4_CH3      - DMAMUX_DMAREQ_ID_TMR4_CH4
  *         - DMAMUX_DMAREQ_ID_TMR4_OVERFLOW - DMAMUX_DMAREQ_ID_TMR4_TRIG     - DMAMUX_DMAREQ_ID_TMR9_CH1      - DMAMUX_DMAREQ_ID_TMR9_CH2
  *         - DMAMUX_DMAREQ_ID_TMR9_OVERFLOW - DMAMUX_DMAREQ_ID_TMR9_TRIG     - DMAMUX_DMAREQ_ID_TMR9_HALL     - DMAMUX_DMAREQ_ID_TMR10_CH1
  *         - DMAMUX_DMAREQ_ID_TMR10_OVERFLOW- DMAMUX_DMAREQ_ID_TMR11_CH1     - DMAMUX_DMAREQ_ID_TMR11_OVERFLOW- DMAMUX_DMAREQ_ID_TMR12_CH1
  *         - DMAMUX_DMAREQ_ID_TMR12_CH2     - DMAMUX_DMAREQ_ID_TMR12_OVERFLOW- DMAMUX_DMAREQ_ID_TMR12_TRIG    - DMAMUX_DMAREQ_ID_TMR12_HALL
  *         - DMAMUX_DMAREQ_ID_TMR13_CH1     - DMAMUX_DMAREQ_ID_TMR13_OVERFLOW- DMAMUX_DMAREQ_ID_TMR14_CH1     - DMAMUX_DMAREQ_ID_TMR14_OVERFLOW
  * @retval none.
  */
void dmamux_init(dmamux_channel_type *dmamux_channelx, dmamux_requst_id_sel_type dmamux_req_sel)
{
  dmamux_channelx->muxctrl_bit.reqsel = dmamux_req_sel;
}

/**
  * @brief  dmamux sync init struct config with its default value.
  * @param  dmamux_sync_init_struct: pointer to a dmamux_sync_init_type structure which will be initialized.
  * @retval none.
  */
void dmamux_sync_default_para_init(dmamux_sync_init_type *dmamux_sync_init_struct)
{
  dmamux_sync_init_struct->sync_enable = FALSE;
  dmamux_sync_init_struct->sync_event_enable = FALSE;
  dmamux_sync_init_struct->sync_polarity = DMAMUX_SYNC_POLARITY_DISABLE;
  dmamux_sync_init_struct->sync_request_number = 0x0;
  dmamux_sync_init_struct->sync_signal_sel = (dmamux_sync_id_sel_type)0;
}

/**
  * @brief  dmamux synchronization config.
  * @param  dmamux_channelx:
  *         this parameter can be one of the following values:
  *         - DMA1MUX_CHANNEL1
  *         - DMA1MUX_CHANNEL2
  *         - DMA1MUX_CHANNEL3
  *         - DMA1MUX_CHANNEL4
  *         - DMA1MUX_CHANNEL5
  *         - DMA1MUX_CHANNEL6
  *         - DMA1MUX_CHANNEL7
  *         - DMA2MUX_CHANNEL1
  *         - DMA2MUX_CHANNEL2
  *         - DMA2MUX_CHANNEL3
  *         - DMA2MUX_CHANNEL4
  *         - DMA2MUX_CHANNEL5
  *         - DMA2MUX_CHANNEL6
  *         - DMA2MUX_CHANNEL7
  * @param  dmamux_sync_init_struct: ointer to a dmamux_sync_init_type structure.
  * @retval none.
  */
void dmamux_sync_config(dmamux_channel_type *dmamux_channelx, dmamux_sync_init_type *dmamux_sync_init_struct)
{
  dmamux_channelx->muxctrl_bit.syncsel = dmamux_sync_init_struct->sync_signal_sel;
  dmamux_channelx->muxctrl_bit.syncpol = dmamux_sync_init_struct->sync_polarity;
  dmamux_channelx->muxctrl_bit.reqcnt  = dmamux_sync_init_struct->sync_request_number - 1;
  dmamux_channelx->muxctrl_bit.evtgen  = dmamux_sync_init_struct->sync_event_enable;
  dmamux_channelx->muxctrl_bit.syncen  = dmamux_sync_init_struct->sync_enable;
}

/**
  * @brief  dmamux request generator init struct config with its default value.
  * @param  dmamux_gen_init_struct: pointer to a dmamux_gen_init_type structure which will be initialized.
  * @retval none.
  */
void dmamux_generator_default_para_init(dmamux_gen_init_type *dmamux_gen_init_struct)
{
  dmamux_gen_init_struct->gen_enable         = FALSE;
  dmamux_gen_init_struct->gen_polarity       = DMAMUX_GEN_POLARITY_DISABLE;
  dmamux_gen_init_struct->gen_request_number = 0x0;
  dmamux_gen_init_struct->gen_signal_sel     = (dmamux_gen_id_sel_type)0x0;
}

/**
  * @brief  dmamux request generator init.
  * @param  dmamux_gen_x :
  *         this parameter can be one of the following values:
  *         - DMA1MUX_GENERATOR1
  *         - DMA1MUX_GENERATOR2
  *         - DMA1MUX_GENERATOR3
  *         - DMA1MUX_GENERATOR4
  *         - DMA2MUX_GENERATOR1
  *         - DMA2MUX_GENERATOR2
  *         - DMA2MUX_GENERATOR3
  *         - DMA2MUX_GENERATOR4
  * @param  dmamux_gen_init_struct: pointer to a dmamux_gen_init_type structure which will be initialized.
  * @retval none.
  */
void dmamux_generator_config(dmamux_generator_type *dmamux_gen_x, dmamux_gen_init_type *dmamux_gen_init_struct)
{
  dmamux_gen_x->gctrl_bit.sigsel  = dmamux_gen_init_struct->gen_signal_sel;
  dmamux_gen_x->gctrl_bit.gpol    = dmamux_gen_init_struct->gen_polarity;
  dmamux_gen_x->gctrl_bit.greqcnt = dmamux_gen_init_struct->gen_request_number - 1;
  dmamux_gen_x->gctrl_bit.gen     = dmamux_gen_init_struct->gen_enable;
}

/**
  * @brief  enable or disable the dmamux sync interrupts.
  * @param  dmamux_channelx:
  *         this parameter can be one of the following values:
  *         - DMA1MUX_CHANNEL1
  *         - DMA1MUX_CHANNEL2
  *         - DMA1MUX_CHANNEL3
  *         - DMA1MUX_CHANNEL4
  *         - DMA1MUX_CHANNEL5
  *         - DMA1MUX_CHANNEL6
  *         - DMA1MUX_CHANNEL7
  *         - DMA2MUX_CHANNEL1
  *         - DMA2MUX_CHANNEL2
  *         - DMA2MUX_CHANNEL3
  *         - DMA2MUX_CHANNEL4
  *         - DMA2MUX_CHANNEL5
  *         - DMA2MUX_CHANNEL6
  *         - DMA2MUX_CHANNEL7
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void dmamux_sync_interrupt_enable(dmamux_channel_type *dmamux_channelx, confirm_state new_state)
{
  if(new_state != FALSE)
  {
    dmamux_channelx->muxctrl_bit.syncovien = TRUE;
  }
  else
  {
    dmamux_channelx->muxctrl_bit.syncovien = FALSE;
  }
}

/**
  * @brief  enable or disable the dmamux request generator interrupts.
  * @param  dmamux_gen_x : pointer to a dmamux_generator_type structure.
  *         this parameter can be one of the following values:
  *         - DMA1MUX_GENERATOR1
  *         - DMA1MUX_GENERATOR2
  *         - DMA1MUX_GENERATOR3
  *         - DMA1MUX_GENERATOR4
  *         - DMA2MUX_GENERATOR1
  *         - DMA2MUX_GENERATOR2
  *         - DMA2MUX_GENERATOR3
  *         - DMA2MUX_GENERATOR4
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void dmamux_generator_interrupt_enable(dmamux_generator_type *dmamux_gen_x, confirm_state new_state)
{
  if(new_state != FALSE)
  {
    dmamux_gen_x->gctrl_bit.trgovien = TRUE;
  }
  else
  {
    dmamux_gen_x->gctrl_bit.trgovien = FALSE;
  }
}

/**
  * @brief  dmamux sync flag get.
  * @param  dma_x : pointer to a dma_type structure, can be DMA1 or DMA2.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - DMAMUX_SYNC_OV1_FLAG
  *         - DMAMUX_SYNC_OV2_FLAG
  *         - DMAMUX_SYNC_OV3_FLAG
  *         - DMAMUX_SYNC_OV4_FLAG
  *         - DMAMUX_SYNC_OV5_FLAG
  *         - DMAMUX_SYNC_OV6_FLAG
  *         - DMAMUX_SYNC_OV7_FLAG
  * @retval state of dmamux sync flag.
  */
flag_status dmamux_sync_flag_get(dma_type *dma_x, uint32_t flag)
{
  if((dma_x->muxsyncsts & flag) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  dmamux sync interrupt flag get.
  * @param  dma_x : pointer to a dma_type structure, can be DMA1 or DMA2.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - DMAMUX_SYNC_OV1_FLAG
  *         - DMAMUX_SYNC_OV2_FLAG
  *         - DMAMUX_SYNC_OV3_FLAG
  *         - DMAMUX_SYNC_OV4_FLAG
  *         - DMAMUX_SYNC_OV5_FLAG
  *         - DMAMUX_SYNC_OV6_FLAG
  *         - DMAMUX_SYNC_OV7_FLAG
  * @retval state of dmamux sync flag.
  */
flag_status dmamux_sync_interrupt_flag_get(dma_type *dma_x, uint32_t flag)
{

  flag_status bitstatus = RESET;
  uint32_t sync_int_temp = flag;
  uint32_t index = 0;
  uint32_t tmpreg = 0, enablestatus = 0;
  uint32_t regoffset = 0x4;

  while((sync_int_temp & 0x00000001) == RESET)
  {
    sync_int_temp = sync_int_temp >> 1;
    index++;
  }

  if(dma_x == DMA1)
  {
    tmpreg = *(uint32_t*)(DMA1MUX_BASE + (index * regoffset));
  }
  else
  {
    tmpreg = *(uint32_t*)(DMA2MUX_BASE + (index * regoffset));
  }

  if((tmpreg & (uint32_t)0x00000100) != (uint32_t)RESET)
  {
    enablestatus = SET;
  }
  else
  {
    enablestatus = RESET;
  }

  if(dma_x == DMA1)
  {
    if(((DMA1->muxsyncsts & flag) != (uint32_t)RESET) && (enablestatus != RESET))
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
    if(((DMA2->muxsyncsts & flag) != (uint32_t)RESET) && (enablestatus != RESET))
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  return bitstatus;
}

/**
  * @brief  dmamux sync flag clear.
  * @param  dma_x : pointer to a dma_type structure, can be DMA1 or DMA2.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - DMAMUX_SYNC_OV1_FLAG
  *         - DMAMUX_SYNC_OV2_FLAG
  *         - DMAMUX_SYNC_OV3_FLAG
  *         - DMAMUX_SYNC_OV4_FLAG
  *         - DMAMUX_SYNC_OV5_FLAG
  *         - DMAMUX_SYNC_OV6_FLAG
  *         - DMAMUX_SYNC_OV7_FLAG
  * @retval none.
  */
void dmamux_sync_flag_clear(dma_type *dma_x, uint32_t flag)
{
  dma_x->muxsyncclr = flag;
}

/**
  * @brief  dmamux request generator flag get.
  * @param  dma_x : pointer to a dma_type structure, can be DMA1 or DMA2.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - DMAMUX_GEN_TRIG_OV1_FLAG
  *         - DMAMUX_GEN_TRIG_OV2_FLAG
  *         - DMAMUX_GEN_TRIG_OV3_FLAG
  *         - DMAMUX_GEN_TRIG_OV4_FLAG
  * @retval state of dmamux sync flag.
  */
flag_status dmamux_generator_flag_get(dma_type *dma_x, uint32_t flag)
{
  if((dma_x->muxgsts & flag) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  dmamux request generator interrupt flag get.
  * @param  dma_x : pointer to a dma_type structure, can be DMA1 or DMA2.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - DMAMUX_GEN_TRIG_OV1_FLAG
  *         - DMAMUX_GEN_TRIG_OV2_FLAG
  *         - DMAMUX_GEN_TRIG_OV3_FLAG
  *         - DMAMUX_GEN_TRIG_OV4_FLAG
  * @retval state of dmamux sync flag.
  */
flag_status dmamux_generator_interrupt_flag_get(dma_type *dma_x, uint32_t flag)
{
  flag_status bitstatus = RESET;
  uint32_t sync_int_temp = flag;
  uint32_t index = 0;
  uint32_t tmpreg = 0, enablestatus = 0;
  uint32_t regoffset = 0x4;

  while((sync_int_temp & 0x00000001) == RESET)
  {
    sync_int_temp = sync_int_temp >> 1;
    index++;
  }

  if(dma_x == DMA1)
    tmpreg = *(uint32_t*)(DMA1MUX_GENERATOR1_BASE + (index * regoffset));
  else
    tmpreg = *(uint32_t*)(DMA2MUX_GENERATOR1_BASE + (index * regoffset));

  if((tmpreg & (uint32_t)0x00000100) != (uint32_t)RESET)
  {
    enablestatus = SET;
  }
  else
  {
    enablestatus = RESET;
  }
  if(dma_x == DMA1)
  {
    if(((DMA1->muxgsts & flag) != (uint32_t)RESET) && (enablestatus != RESET))
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
    if(((DMA2->muxgsts & flag) != (uint32_t)RESET) && (enablestatus != RESET))
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }

  return bitstatus;
}

/**
  * @brief  dmamux request generator flag clear.
  * @param  dma_x : pointer to a dma_type structure, can be DMA1 or DMA2.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - DMAMUX_GEN_TRIG_OV1_FLAG
  *         - DMAMUX_GEN_TRIG_OV2_FLAG
  *         - DMAMUX_GEN_TRIG_OV3_FLAG
  *         - DMAMUX_GEN_TRIG_OV4_FLAG
  * @retval none.
  */
void dmamux_generator_flag_clear(dma_type *dma_x, uint32_t flag)
{
  dma_x->muxgclr = flag;
}

/**
  * @}
  */

#endif

/**
  * @}
  */

/**
  * @}
  */
