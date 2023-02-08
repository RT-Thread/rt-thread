/**
  **************************************************************************
  * @file     at32f425_dma.c
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

#include "at32f425_conf.h"

/** @addtogroup AT32F425_periph_driver
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
  * @brief  reset the dmax channely registers.
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  * @retval none
  */
void dma_reset(dma_channel_type* dmax_channely)
{
  uint32_t temp = 0;
  dmax_channely->ctrl_bit.chen = FALSE;
  dmax_channely->ctrl = 0;
  dmax_channely->dtcnt = 0;
  dmax_channely->paddr = 0;
  dmax_channely->maddr = 0;

  temp = (uint32_t)dmax_channely;

  /* dma1 channel */
  DMA1->clr |= (uint32_t)(0x0f << ((((temp & 0xff) - 0x08) / 0x14) * 4));
}

/**
  * @brief  set the number of data to be transferred
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  * @param  data_number: the number of data to be transferred(0x0000~0xFFFF)
  *         transfer.
  * @retval none.
  */
void dma_data_number_set(dma_channel_type* dmax_channely, uint16_t data_number)
{
  dmax_channely->dtcnt = data_number;
}

/**
  * @brief  get number of data from dtcnt register
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  * @retval the number of data.
  */
uint16_t dma_data_number_get(dma_channel_type* dmax_channely)
{
  return (uint16_t)dmax_channely->dtcnt;
}

/**
  * @brief  enable or disable dma interrupt
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  * @param  dma_int:
  *         this parameter can be any combination of the following values:
  *         - DMA_FDT_INT
  *         - DMA_HDT_INT
  *         - DMA_DTERR_INT
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dma_interrupt_enable(dma_channel_type* dmax_channely, uint32_t dma_int, confirm_state new_state)
{
  if (new_state != FALSE)
  {
    dmax_channely->ctrl |= dma_int;
  }
  else
  {
    dmax_channely->ctrl &= ~dma_int;
  }
}

/**
  * @brief  enable or disable dma channely
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  * @param  new_state (TRUE or FALSE)
  * @retval None
  */
void dma_channel_enable(dma_channel_type* dmax_channely, confirm_state new_state)
{
  dmax_channely->ctrl_bit.chen = new_state;
}

/**
  * @brief  initialize the dma_x flexible function according to the specified parameters.
  * @param  dma_x:
  *         this parameter can be one of the following values:
  *         - DMA1
  * @param  flex_channelx:
  *         this parameter can be one of the following values:
  *         - FLEX_CHANNEL1
  *         - FLEX_CHANNEL2
  *         - FLEX_CHANNEL3
  *         - FLEX_CHANNEL4
  *         - FLEX_CHANNEL5
  *         - FLEX_CHANNEL6
  *         - FLEX_CHANNEL7
  * @param  flexible_request: every peripheral have specified hardware_id.
  *         this parameter can be one of the following values:
  *         - DMA_FLEXIBLE_ADC1         - DMA_FLEXIBLE_UART4_RX      - DMA_FLEXIBLE_TMR2_TRIG     - DMA_FLEXIBLE_TMR7_OVERFLOW
  *         - DMA_FLEXIBLE_SPI1_RX      - DMA_FLEXIBLE_UART4_TX      - DMA_FLEXIBLE_TMR2_OVERFLOW - DMA_FLEXIBLE_TMR15_TRIG
  *         - DMA_FLEXIBLE_SPI1_TX      - DMA_FLEXIBLE_I2C1_RX       - DMA_FLEXIBLE_TMR2_CH1      - DMA_FLEXIBLE_TMR15_HALL
  *         - DMA_FLEXIBLE_SPI2_RX      - DMA_FLEXIBLE_I2C1_TX       - DMA_FLEXIBLE_TMR2_CH2      - DMA_FLEXIBLE_TMR15_OVERFLOW
  *         - DMA_FLEXIBLE_SPI2_TX      - DMA_FLEXIBLE_I2C2_RX       - DMA_FLEXIBLE_TMR2_CH3      - DMA_FLEXIBLE_TMR15_CH1
  *         - DMA_FLEXIBLE_SPI3_RX      - DMA_FLEXIBLE_I2C2_TX       - DMA_FLEXIBLE_TMR2_CH4      - DMA_FLEXIBLE_TMR15_CH2
  *         - DMA_FLEXIBLE_SPI3_TX      - DMA_FLEXIBLE_TMR1_TRIG     - DMA_FLEXIBLE_TMR3_TRIG     - DMA_FLEXIBLE_TMR16_OVERFLOW
  *         - DMA_FLEXIBLE_UART1_RX     - DMA_FLEXIBLE_TMR1_HALL     - DMA_FLEXIBLE_TMR3_OVERFLOW - DMA_FLEXIBLE_TMR16_CH1
  *         - DMA_FLEXIBLE_UART1_TX     - DMA_FLEXIBLE_TMR1_OVERFLOW - DMA_FLEXIBLE_TMR3_CH1      - DMA_FLEXIBLE_TMR17_OVERFLOW
  *         - DMA_FLEXIBLE_UART2_RX     - DMA_FLEXIBLE_TMR1_CH1      - DMA_FLEXIBLE_TMR3_CH2      - DMA_FLEXIBLE_TMR17_CH1
  *         - DMA_FLEXIBLE_UART2_TX     - DMA_FLEXIBLE_TMR1_CH2      - DMA_FLEXIBLE_TMR3_CH3
  *         - DMA_FLEXIBLE_UART3_RX     - DMA_FLEXIBLE_TMR1_CH3      - DMA_FLEXIBLE_TMR3_CH4
  *         - DMA_FLEXIBLE_UART3_TX     - DMA_FLEXIBLE_TMR1_CH4      - DMA_FLEXIBLE_TMR6_OVERFLOW
  * @retval none
  */

void dma_flexible_config(dma_type* dma_x, uint8_t flex_channelx, dma_flexible_request_type flexible_request)
{
  if(dma_x->src_sel1_bit.dma_flex_en == RESET)
  {
    dma_x->src_sel1_bit.dma_flex_en = TRUE;
  }

  if(flex_channelx == FLEX_CHANNEL1)
  {
    dma_x->src_sel0_bit.ch1_src = flexible_request;
  }
  else if(flex_channelx == FLEX_CHANNEL2)
  {
    dma_x->src_sel0_bit.ch2_src = flexible_request;
  }
  else if(flex_channelx == FLEX_CHANNEL3)
  {
    dma_x->src_sel0_bit.ch3_src = flexible_request;
  }
  else if(flex_channelx == FLEX_CHANNEL4)
  {
    dma_x->src_sel0_bit.ch4_src = flexible_request;
  }
  else if(flex_channelx == FLEX_CHANNEL5)
  {
    dma_x->src_sel1_bit.ch5_src = flexible_request;
  }
  else if(flex_channelx == FLEX_CHANNEL6)
  {
    dma_x->src_sel1_bit.ch6_src = flexible_request;
  }
  else
  {
    if(flex_channelx == FLEX_CHANNEL7)
    {
      dma_x->src_sel1_bit.ch7_src = flexible_request;
    }
  }
}

/**
  * @brief  get dma flag
  * @param  dmax_flag
  *         this parameter can be one of the following values:
  *         - DMA1_GL1_FLAG        - DMA1_FDT1_FLAG        - DMA1_HDT1_FLAG        - DMA1_DTERR1_FLAG
  *         - DMA1_GL2_FLAG        - DMA1_FDT2_FLAG        - DMA1_HDT2_FLAG        - DMA1_DTERR2_FLAG
  *         - DMA1_GL3_FLAG        - DMA1_FDT3_FLAG        - DMA1_HDT3_FLAG        - DMA1_DTERR3_FLAG
  *         - DMA1_GL4_FLAG        - DMA1_FDT4_FLAG        - DMA1_HDT4_FLAG        - DMA1_DTERR4_FLAG
  *         - DMA1_GL5_FLAG        - DMA1_FDT5_FLAG        - DMA1_HDT5_FLAG        - DMA1_DTERR5_FLAG
  *         - DMA1_GL6_FLAG        - DMA1_FDT6_FLAG        - DMA1_HDT6_FLAG        - DMA1_DTERR6_FLAG
  *         - DMA1_GL7_FLAG        - DMA1_FDT7_FLAG        - DMA1_HDT7_FLAG        - DMA1_DTERR7_FLAG
  * @retval state of dma flag
  */
flag_status dma_flag_get(uint32_t dmax_flag)
{
  flag_status status = RESET;
  uint32_t temp = 0;

  temp = DMA1->sts;

  if ((temp & dmax_flag) != (uint16_t)RESET)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/**
  * @brief  clear dma flag
  * @param  dmax_flag
  *         this parameter can be one of the following values:
  *         - DMA1_GL1_FLAG        - DMA1_FDT1_FLAG        - DMA1_HDT1_FLAG        - DMA1_DTERR1_FLAG
  *         - DMA1_GL2_FLAG        - DMA1_FDT2_FLAG        - DMA1_HDT2_FLAG        - DMA1_DTERR2_FLAG
  *         - DMA1_GL3_FLAG        - DMA1_FDT3_FLAG        - DMA1_HDT3_FLAG        - DMA1_DTERR3_FLAG
  *         - DMA1_GL4_FLAG        - DMA1_FDT4_FLAG        - DMA1_HDT4_FLAG        - DMA1_DTERR4_FLAG
  *         - DMA1_GL5_FLAG        - DMA1_FDT5_FLAG        - DMA1_HDT5_FLAG        - DMA1_DTERR5_FLAG
  *         - DMA1_GL6_FLAG        - DMA1_FDT6_FLAG        - DMA1_HDT6_FLAG        - DMA1_DTERR6_FLAG
  *         - DMA1_GL7_FLAG        - DMA1_FDT7_FLAG        - DMA1_HDT7_FLAG        - DMA1_DTERR7_FLAG
  * @retval none
  */
void dma_flag_clear(uint32_t dmax_flag)
{
  DMA1->clr = dmax_flag;
}

/**
  * @brief  dma init config with its default value.
  * @param  dma_init_struct : pointer to a dma_init_type structure which will
  *         be initialized.
  * @retval none
  */
void dma_default_para_init(dma_init_type* dma_init_struct)
{
  dma_init_struct->peripheral_base_addr = 0x0;
  dma_init_struct->memory_base_addr = 0x0;
  dma_init_struct->direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct->buffer_size = 0x0;
  dma_init_struct->peripheral_inc_enable = FALSE;
  dma_init_struct->memory_inc_enable = FALSE;
  dma_init_struct->peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct->memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct->loop_mode_enable = FALSE;
  dma_init_struct->priority = DMA_PRIORITY_LOW;
}

/**
  * @brief  dma init
  * @param  dmax_channely:
  *         this parameter can be one of the following values:
  *         - DMA1_CHANNEL1
  *         - DMA1_CHANNEL2
  *         - DMA1_CHANNEL3
  *         - DMA1_CHANNEL4
  *         - DMA1_CHANNEL5
  *         - DMA1_CHANNEL6
  *         - DMA1_CHANNEL7
  * @param  dma_initstruct : pointer to a dma_init_type structure.
  * @retval none
  */
void dma_init(dma_channel_type* dmax_channely, dma_init_type* dma_init_struct)
{
  /* clear ctrl register dtd bit and m2m bit */
  dmax_channely->ctrl &= 0xbfef;
  dmax_channely->ctrl |= dma_init_struct->direction;

  dmax_channely->ctrl_bit.chpl =  dma_init_struct->priority;
  dmax_channely->ctrl_bit.mwidth = dma_init_struct->memory_data_width;
  dmax_channely->ctrl_bit.pwidth = dma_init_struct->peripheral_data_width;
  dmax_channely->ctrl_bit.mincm = dma_init_struct->memory_inc_enable;
  dmax_channely->ctrl_bit.pincm = dma_init_struct->peripheral_inc_enable;
  dmax_channely->ctrl_bit.lm = dma_init_struct->loop_mode_enable;
  dmax_channely->dtcnt = dma_init_struct->buffer_size;
  dmax_channely->paddr = dma_init_struct->peripheral_base_addr;
  dmax_channely->maddr = dma_init_struct->memory_base_addr;
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
