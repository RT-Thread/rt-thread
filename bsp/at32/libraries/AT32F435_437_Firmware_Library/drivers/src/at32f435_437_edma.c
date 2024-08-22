/**
  **************************************************************************
  * @file     at32f435_437_edma.c
  * @brief    contains all the functions for the edma firmware library
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

#include "at32f435_437_conf.h"

/** @addtogroup AT32F435_437_periph_driver
  * @{
  */

/** @defgroup EDMA
  * @brief EDMA driver modules
  * @{
  */

#ifdef EDMA_MODULE_ENABLED

/** @defgroup EDMA_private_functions
  * @{
  */

/**
  * @brief  reset edma_streamx channely register.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @retval none.
  */
void edma_reset(edma_stream_type *edma_streamx)
{
  /* reset registers for the selected stream */
  edma_streamx->ctrl_bit.sen = FALSE;
  edma_streamx->ctrl = 0x0;
  edma_streamx->dtcnt = 0x0;
  edma_streamx->paddr = 0x0;
  edma_streamx->m0addr = 0x0;
  edma_streamx->m1addr = 0x0;
  edma_streamx->fctrl = (uint32_t)0x00000021;

  /* reset interrupt pending bits for the selected stream */
  switch((uint32_t)edma_streamx)
  {
    case EDMA_STREAM1_BASE:
      EDMA->clr1 = EDMA_STREAM1_INT_MASK;
      break;
    case EDMA_STREAM2_BASE:
      EDMA->clr1 = EDMA_STREAM2_INT_MASK;
      break;
    case EDMA_STREAM3_BASE:
      EDMA->clr1 = EDMA_STREAM3_INT_MASK;
      break;
    case EDMA_STREAM4_BASE:
      EDMA->clr1 = EDMA_STREAM4_INT_MASK;
      break;
    case EDMA_STREAM5_BASE:
      EDMA->clr2 = EDMA_STREAM5_INT_MASK;
      break;
    case EDMA_STREAM6_BASE:
      EDMA->clr2 = EDMA_STREAM6_INT_MASK;
      break;
    case EDMA_STREAM7_BASE:
      EDMA->clr2 = EDMA_STREAM7_INT_MASK;
      break;
    case EDMA_STREAM8_BASE:
      EDMA->clr2 = EDMA_STREAM8_INT_MASK;
      break;
    default: break;
  }
}

/**
  * @brief  edma init.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @param  edma_init_struct: pointer to a edma_init_type structure.
  * @retval none.
  */
void edma_init(edma_stream_type *edma_streamx, edma_init_type *edma_init_struct)
{
  /* config dtd bits */
  edma_streamx->ctrl_bit.dtd = edma_init_struct->direction;

  /* config pincm bit */
  edma_streamx->ctrl_bit.pincm = edma_init_struct->peripheral_inc_enable;

  /* config mincm bit*/
  edma_streamx->ctrl_bit.mincm = edma_init_struct->memory_inc_enable;

  /* config pwidth bits */
  edma_streamx->ctrl_bit.pwidth = edma_init_struct->peripheral_data_width;

  /* config mwidth bits */
  edma_streamx->ctrl_bit.mwidth = edma_init_struct->memory_data_width;

  /* config lm bit */
  edma_streamx->ctrl_bit.lm = edma_init_struct->loop_mode_enable;

  /* config spl bits */
  edma_streamx->ctrl_bit.spl = edma_init_struct->priority;

  /* config mct bits */
  edma_streamx->ctrl_bit.mct = edma_init_struct->memory_burst_mode;

  /* config pct bits */
  edma_streamx->ctrl_bit.pct = edma_init_struct->peripheral_burst_mode;

  /* config fen bits */
  edma_streamx->fctrl_bit.fen = edma_init_struct->fifo_mode_enable;

  /* config fthsel bits*/
  edma_streamx->fctrl_bit.fthsel = edma_init_struct->fifo_threshold;

  /* config dtcnt */
  edma_streamx->dtcnt = edma_init_struct->buffer_size;

  /* config paddr */
  edma_streamx->paddr = edma_init_struct->peripheral_base_addr;

  /* config m0addr */
  edma_streamx->m0addr = edma_init_struct->memory0_base_addr;
}

/**
  * @brief  edma init struct config with its default value.
  * @param  edma_init_struct: pointer to a edma_init_type structure which will be initialized.
  * @retval none.
  */
void edma_default_para_init(edma_init_type *edma_init_struct)
{
  edma_init_struct->buffer_size = 0;
  edma_init_struct->loop_mode_enable = FALSE;
  edma_init_struct->direction = EDMA_DIR_PERIPHERAL_TO_MEMORY;
  edma_init_struct->fifo_threshold = EDMA_FIFO_THRESHOLD_1QUARTER;
  edma_init_struct->fifo_mode_enable = FALSE;
  edma_init_struct->memory0_base_addr = 0;
  edma_init_struct->memory_burst_mode = EDMA_MEMORY_SINGLE;
  edma_init_struct->memory_data_width = EDMA_MEMORY_DATA_WIDTH_BYTE;
  edma_init_struct->memory_inc_enable = FALSE;
  edma_init_struct->peripheral_base_addr = 0;
  edma_init_struct->peripheral_burst_mode = EDMA_PERIPHERAL_SINGLE;
  edma_init_struct->peripheral_data_width = EDMA_PERIPHERAL_DATA_WIDTH_BYTE;
  edma_init_struct->peripheral_inc_enable = FALSE;
  edma_init_struct->priority = EDMA_PRIORITY_LOW;
}

/**
  * @brief  enable or disable the edma streamx.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void edma_stream_enable(edma_stream_type *edma_streamx, confirm_state new_state)
{
  edma_streamx->ctrl_bit.sen = new_state;
}

/**
  * @brief  enable or disable the edma streamx interrupts.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @param  edma_int:
  *         this parameter can be one of the following values:
  *         - EDMA_FDT_INT
  *         - EDMA_HDT_INT
  *         - EDMA_DTERR_INT
  *         - EDMA_DMERR_INT
  *         - EDMA_FERR_INT
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void edma_interrupt_enable(edma_stream_type *edma_streamx, uint32_t edma_int, confirm_state new_state)
{
  if((edma_int & EDMA_FERR_INT) != 0)
  {
    if(new_state != FALSE)
    {
      edma_streamx->fctrl |= (uint32_t)EDMA_FERR_INT;
    }
    else
    {
      edma_streamx->fctrl &= ~(uint32_t)EDMA_FERR_INT;
    }
  }

  if(edma_int != EDMA_FERR_INT)
  {
    if(new_state != FALSE)
    {
      edma_streamx->ctrl |= (uint32_t)edma_int;
    }
    else
    {
      edma_streamx->ctrl &= ~(uint32_t)edma_int;
    }
  }
}

/**
  * @brief  config the edma peripheral increment offset size mode.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @param  offset: peripheral increment offset size.
  *         this parameter can be one of the following values:
  *         - EDMA_PERIPHERAL_INC_PSIZE
  *         - EDMA_PERIPHERAL_INC_4_BYTE
  * @retval none.
  */
void edma_peripheral_inc_offset_set(edma_stream_type *edma_streamx, edma_peripheral_inc_offset_type offset)
{
  edma_streamx->ctrl_bit.pincos = offset;
}

/**
  * @brief  enable or disable the edma streamx flow controller.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void edma_flow_controller_enable(edma_stream_type *edma_streamx, confirm_state new_state)
{
  edma_streamx->ctrl_bit.pfctrl = new_state;
}

/**
  * @brief  set the number of data to be transferred.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @param  data_number: the number of data to be transferred (0x0000~0xFFFF).
  * @retval none.
  */
void edma_data_number_set(edma_stream_type *edma_streamx, uint16_t data_number)
{
  /* write the number of data units to be transferred */
  edma_streamx->dtcnt = data_number;
}

/**
  * @brief  get the number of data to be transferred.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @retval the number value.
  */
uint16_t edma_data_number_get(edma_stream_type *edma_streamx)
{
  return ((uint16_t)(edma_streamx->dtcnt));
}

/**
  * @brief  config the the double buffer mode.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @param  memory1_addr: the address of the second buffer.
  * @param  current_memory: specifies the target area of the first transfer.
  *         this parameter can be one of the following values:
  *         - EDMA_MEMORY_0
  *         - EDMA_MEMORY_1
  * @retval none.
  */
void edma_double_buffer_mode_init(edma_stream_type *edma_streamx, uint32_t memory1_addr, edma_memory_type current_memory)
{
  if(current_memory != EDMA_MEMORY_0)
  {
    edma_streamx->ctrl_bit.cm = 1;
  }
  else
  {
    edma_streamx->ctrl_bit.cm = 0;
  }

  edma_streamx->m1addr = memory1_addr;
}

/**
  * @brief  enable or disable the double memory mode.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void edma_double_buffer_mode_enable(edma_stream_type *edma_streamx, confirm_state new_state)
{
  if(new_state != FALSE)
  {
    edma_streamx->ctrl_bit.dmm = 1;
  }
  else
  {
    edma_streamx->ctrl_bit.dmm = 0;
  }
}

/**
  * @brief  config the memory address in double buffer mode.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @param  memory_addr: the address of the buffer.
  * @param  memory_target: indicates the which memory addr register will be config.
  *         this parameter can be one of the following values:
  *         - EDMA_MEMORY_0
  *         - EDMA_MEMORY_1
  * @retval none.
  */
void edma_memory_addr_set(edma_stream_type *edma_streamx, uint32_t memory_addr, uint32_t memory_target)
{
  if(memory_target != EDMA_MEMORY_0)
  {
    edma_streamx->m1addr = memory_addr;
  }
  else
  {
    edma_streamx->m0addr = memory_addr;
  }
}

/**
  * @brief  get the current memory target.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @retval the memory target
  *         - EDMA_MEMORY_0
  *         - EDMA_MEMORY_1
  */
edma_memory_type edma_memory_target_get(edma_stream_type *edma_streamx)
{
  return (edma_memory_type)(edma_streamx->ctrl_bit.cm);
}

/**
  * @brief  get the enable status of edma streamx.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @retval current state of the edma streamx (SET or RESET).
  */
flag_status edma_stream_status_get(edma_stream_type *edma_streamx)
{
  if((edma_streamx->ctrl_bit.sen) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  get the fifo level status.
  * @param  edma_streamx:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1
  *         - EDMA_STREAM2
  *         - EDMA_STREAM3
  *         - EDMA_STREAM4
  *         - EDMA_STREAM5
  *         - EDMA_STREAM6
  *         - EDMA_STREAM7
  *         - EDMA_STREAM8
  * @retval the fifo filling state.
  *         - EDMA_FIFO_STATUS_LESS_1QUARTER: (0)   <  fifo level < (1/4).
  *         - EDMA_FIFO_STATUS_1QUARTER:      (1/4) <= fifo level < (1/2) .
  *         - EDMA_FIFO_STATUS_HALF:          (1/2) <= fifo level < (3/4).
  *         - EDMA_FIFO_STATUS_3QUARTER:      (3/4) <= fifo level < (1).
  *         - EDMA_FIFO_STATUS_EMPTY: fifo is empty.
  *         - EDMA_FIFO_STATUS_FULL: fifo is full.
  */
uint8_t edma_fifo_status_get(edma_stream_type *edma_streamx)
{
  return (uint8_t)(edma_streamx->fctrl_bit.fsts);
}

/**
  * @brief  get the edma flag.
  * @param  edma_flag:
  *         this parameter can be one of the following values:
  *         - EDMA_FERR1_FLAG   - EDMA_DMERR1_FLAG  - EDMA_DTERR1_FLAG  - EDMA_HDT1_FLAG   - EDMA_FDT1_FLAG
  *         - EDMA_FERR2_FLAG   - EDMA_DMERR2_FLAG  - EDMA_DTERR2_FLAG  - EDMA_HDT2_FLAG   - EDMA_FDT2_FLAG
  *         - EDMA_FERR3_FLAG   - EDMA_DMERR3_FLAG  - EDMA_DTERR3_FLAG  - EDMA_HDT3_FLAG   - EDMA_FDT3_FLAG
  *         - EDMA_FERR4_FLAG   - EDMA_DMERR4_FLAG  - EDMA_DTERR4_FLAG  - EDMA_HDT4_FLAG   - EDMA_FDT4_FLAG
  *         - EDMA_FERR5_FLAG   - EDMA_DMERR5_FLAG  - EDMA_DTERR5_FLAG  - EDMA_HDT5_FLAG   - EDMA_FDT5_FLAG
  *         - EDMA_FERR6_FLAG   - EDMA_DMERR6_FLAG  - EDMA_DTERR6_FLAG  - EDMA_HDT6_FLAG   - EDMA_FDT6_FLAG
  *         - EDMA_FERR7_FLAG   - EDMA_DMERR7_FLAG  - EDMA_DTERR7_FLAG  - EDMA_HDT7_FLAG   - EDMA_FDT7_FLAG
  *         - EDMA_FERR8_FLAG   - EDMA_DMERR8_FLAG  - EDMA_DTERR8_FLAG  - EDMA_HDT8_FLAG   - EDMA_FDT8_FLAG
  * @retval the new state of edma flag (SET or RESET).
  */
flag_status edma_flag_get(uint32_t edma_flag)
{
  uint32_t status;

  if(edma_flag > ((uint32_t)0x20000000))
  {
    status = EDMA->sts2;
  }
  else
  {
    status = EDMA->sts1;
  }

  if((status & edma_flag) != ((uint32_t)RESET))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  get the edma interrupt flag.
  * @param  edma_flag:
  *         this parameter can be one of the following values:
  *         - EDMA_FERR1_FLAG   - EDMA_DMERR1_FLAG  - EDMA_DTERR1_FLAG  - EDMA_HDT1_FLAG   - EDMA_FDT1_FLAG
  *         - EDMA_FERR2_FLAG   - EDMA_DMERR2_FLAG  - EDMA_DTERR2_FLAG  - EDMA_HDT2_FLAG   - EDMA_FDT2_FLAG
  *         - EDMA_FERR3_FLAG   - EDMA_DMERR3_FLAG  - EDMA_DTERR3_FLAG  - EDMA_HDT3_FLAG   - EDMA_FDT3_FLAG
  *         - EDMA_FERR4_FLAG   - EDMA_DMERR4_FLAG  - EDMA_DTERR4_FLAG  - EDMA_HDT4_FLAG   - EDMA_FDT4_FLAG
  *         - EDMA_FERR5_FLAG   - EDMA_DMERR5_FLAG  - EDMA_DTERR5_FLAG  - EDMA_HDT5_FLAG   - EDMA_FDT5_FLAG
  *         - EDMA_FERR6_FLAG   - EDMA_DMERR6_FLAG  - EDMA_DTERR6_FLAG  - EDMA_HDT6_FLAG   - EDMA_FDT6_FLAG
  *         - EDMA_FERR7_FLAG   - EDMA_DMERR7_FLAG  - EDMA_DTERR7_FLAG  - EDMA_HDT7_FLAG   - EDMA_FDT7_FLAG
  *         - EDMA_FERR8_FLAG   - EDMA_DMERR8_FLAG  - EDMA_DTERR8_FLAG  - EDMA_HDT8_FLAG   - EDMA_FDT8_FLAG
  * @retval the new state of edma flag (SET or RESET).
  */
flag_status edma_interrupt_flag_get(uint32_t edma_flag)
{
  uint32_t status;

  if(edma_flag > ((uint32_t)0x20000000))
  {
    status = EDMA->sts2;
  }
  else
  {
    status = EDMA->sts1;
  }

  if((status & edma_flag) != ((uint32_t)RESET))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  clear the edma flag.
  * @param  edma_flag:
  *         this parameter can be one of the following values:
  *         - EDMA_FERR1_FLAG   - EDMA_DMERR1_FLAG  - EDMA_DTERR1_FLAG  - EDMA_HDT1_FLAG   - EDMA_FDT1_FLAG
  *         - EDMA_FERR2_FLAG   - EDMA_DMERR2_FLAG  - EDMA_DTERR2_FLAG  - EDMA_HDT2_FLAG   - EDMA_FDT2_FLAG
  *         - EDMA_FERR3_FLAG   - EDMA_DMERR3_FLAG  - EDMA_DTERR3_FLAG  - EDMA_HDT3_FLAG   - EDMA_FDT3_FLAG
  *         - EDMA_FERR4_FLAG   - EDMA_DMERR4_FLAG  - EDMA_DTERR4_FLAG  - EDMA_HDT4_FLAG   - EDMA_FDT4_FLAG
  *         - EDMA_FERR5_FLAG   - EDMA_DMERR5_FLAG  - EDMA_DTERR5_FLAG  - EDMA_HDT5_FLAG   - EDMA_FDT5_FLAG
  *         - EDMA_FERR6_FLAG   - EDMA_DMERR6_FLAG  - EDMA_DTERR6_FLAG  - EDMA_HDT6_FLAG   - EDMA_FDT6_FLAG
  *         - EDMA_FERR7_FLAG   - EDMA_DMERR7_FLAG  - EDMA_DTERR7_FLAG  - EDMA_HDT7_FLAG   - EDMA_FDT7_FLAG
  *         - EDMA_FERR8_FLAG   - EDMA_DMERR8_FLAG  - EDMA_DTERR8_FLAG  - EDMA_HDT8_FLAG   - EDMA_FDT8_FLAG
  * @retval none.
  */
void edma_flag_clear(uint32_t edma_flag)
{
  if(edma_flag > ((uint32_t)0x20000000))
  {
    EDMA->clr2 = (uint32_t)(edma_flag & 0x0FFFFFFF);
  }
  else
  {
    EDMA->clr1 = edma_flag;
  }
}

/**
  * @brief  initialize the edma 2d mode.
  * @param  edma_streamx_2d:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1_2D
  *         - EDMA_STREAM2_2D
  *         - EDMA_STREAM3_2D
  *         - EDMA_STREAM4_2D
  *         - EDMA_STREAM5_2D
  *         - EDMA_STREAM6_2D
  *         - EDMA_STREAM7_2D
  *         - EDMA_STREAM8_2D
  * @param  src_stride: source stride(-32768 ~ 32767).
  * @param  dst_stride: destination stride(-32768 ~ 32767).
  * @param  xcnt: x dimension transfer count(0x0000~ 0xFFFF).
  * @param  ycnt: y dimension transfer count(0x0000~ 0xFFFF).
  * @retval none.
  */
void edma_2d_init(edma_stream_2d_type *edma_streamx_2d, int16_t src_stride, int16_t dst_stride, uint16_t xcnt, uint16_t ycnt)
{
  edma_streamx_2d->s2dcnt = (uint32_t)((ycnt << 16) | (xcnt));

  edma_streamx_2d->stride = (uint32_t)((dst_stride << 16) | (src_stride));
}

/**
  * @brief  enable or disable the edma 2d mode.
  * @param  edma_streamx_2d:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1_2D
  *         - EDMA_STREAM2_2D
  *         - EDMA_STREAM3_2D
  *         - EDMA_STREAM4_2D
  *         - EDMA_STREAM5_2D
  *         - EDMA_STREAM6_2D
  *         - EDMA_STREAM7_2D
  *         - EDMA_STREAM8_2D
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void edma_2d_enable(edma_stream_2d_type *edma_streamx_2d, confirm_state new_state)
{
  uint32_t offset;

  offset = ((uint32_t)edma_streamx_2d - EDMA_STREAM1_2D_BASE) / 4;

  if(new_state != FALSE)
  {
    EDMA->s2dctrl |= (uint16_t)0x0001 << offset;
  }
  else
  {
    EDMA->s2dctrl &= ~((uint16_t)0x0001 << offset);
  }
}

/**
  * @brief  initialize the edma link list.
  * @param  edma_streamx_ll:
  *         this parameter can be one of the following values:
  *         - EDMA_STREAM1_LL
  *         - EDMA_STREAM2_LL
  *         - EDMA_STREAM3_LL
  *         - EDMA_STREAM4_LL
  *         - EDMA_STREAM5_LL
  *         - EDMA_STREAM6_LL
  *         - EDMA_STREAM7_LL
  *         - EDMA_STREAM8_LL
  * @param  pointer: link list pointer.
  * @retval none.
  */
void edma_link_list_init(edma_stream_link_list_type *edma_streamx_ll, uint32_t pointer)
{
  edma_streamx_ll->llp = pointer;
}

/**
  * @brief  enable or disable the edma stream link list mode.
  * @param  edma_streamx_ll:
  *         this parameter can be any combination of the following values:
  *         - EDMA_STREAM1_LL
  *         - EDMA_STREAM2_LL
  *         - EDMA_STREAM3_LL
  *         - EDMA_STREAM4_LL
  *         - EDMA_STREAM5_LL
  *         - EDMA_STREAM6_LL
  *         - EDMA_STREAM7_LL
  *         - EDMA_STREAM8_LL
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void edma_link_list_enable(edma_stream_link_list_type *edma_streamx_ll, confirm_state new_state)
{
  uint32_t offset;

  offset = ((uint32_t)edma_streamx_ll - EDMA_STREAM1_LL_BASE) / 4;

  if(new_state != FALSE)
  {
    EDMA->llctrl |= (uint16_t)0x0001 << offset;
  }
  else
  {
    EDMA->llctrl &= ~((uint16_t)0x0001 << offset);
  }
}

/**
  * @brief  enable or disable the edma edmamux.
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void edmamux_enable(confirm_state new_state)
{
  EDMA->muxsel_bit.tblsel = new_state;
}

/**
  * @brief  edmamux init.
  * @param  edmamux_channelx:
  *         this parameter can be one of the following values:
  *         - EDMAMUX_CHANNEL1
  *         - EDMAMUX_CHANNEL2
  *         - EDMAMUX_CHANNEL3
  *         - EDMAMUX_CHANNEL4
  *         - EDMAMUX_CHANNEL5
  *         - EDMAMUX_CHANNEL6
  *         - EDMAMUX_CHANNEL7
  *         - EDMAMUX_CHANNEL8
  * @param  edmamux_req_id:
  *         this parameter can be one of the following values:
  *         - EDMAMUX_DMAREQ_ID_REQ_G1       - EDMAMUX_DMAREQ_ID_REQ_G2       - EDMAMUX_DMAREQ_ID_REQ_G3       - EDMAMUX_DMAREQ_ID_REQ_G4
  *         - EDMAMUX_DMAREQ_ID_ADC1         - EDMAMUX_DMAREQ_ID_ADC2         - EDMAMUX_DMAREQ_ID_ADC3         - EDMAMUX_DMAREQ_ID_DAC1
  *         - EDMAMUX_DMAREQ_ID_DAC2         - EDMAMUX_DMAREQ_ID_TMR6_OVERFLOW- EDMAMUX_DMAREQ_ID_TMR7_OVERFLOW- EDMAMUX_DMAREQ_ID_SPI1_RX
  *         - EDMAMUX_DMAREQ_ID_SPI1_TX      - EDMAMUX_DMAREQ_ID_SPI2_RX      - EDMAMUX_DMAREQ_ID_SPI2_TX      - EDMAMUX_DMAREQ_ID_SPI3_RX
  *         - EDMAMUX_DMAREQ_ID_SPI3_TX      - EDMAMUX_DMAREQ_ID_SPI4_RX      - EDMAMUX_DMAREQ_ID_SPI4_TX      - EDMAMUX_DMAREQ_ID_I2S2_EXT_RX
  *         - EDMAMUX_DMAREQ_ID_I2S2_EXT_TX  - EDMAMUX_DMAREQ_ID_I2S3_EXT_RX  - EDMAMUX_DMAREQ_ID_I2S3_EXT_TX  - EDMAMUX_DMAREQ_ID_I2C1_RX
  *         - EDMAMUX_DMAREQ_ID_I2C1_TX      - EDMAMUX_DMAREQ_ID_I2C2_RX      - EDMAMUX_DMAREQ_ID_I2C2_TX      - EDMAMUX_DMAREQ_ID_I2C3_RX
  *         - EDMAMUX_DMAREQ_ID_I2C3_TX      - EDMAMUX_DMAREQ_ID_USART1_RX    - EDMAMUX_DMAREQ_ID_USART1_TX    - EDMAMUX_DMAREQ_ID_USART2_RX
  *         - EDMAMUX_DMAREQ_ID_USART2_TX    - EDMAMUX_DMAREQ_ID_USART3_RX    - EDMAMUX_DMAREQ_ID_USART3_TX    - EDMAMUX_DMAREQ_ID_UART4_RX
  *         - EDMAMUX_DMAREQ_ID_UART4_TX     - EDMAMUX_DMAREQ_ID_UART5_RX     - EDMAMUX_DMAREQ_ID_UART5_TX     - EDMAMUX_DMAREQ_ID_USART6_RX
  *         - EDMAMUX_DMAREQ_ID_USART6_TX    - EDMAMUX_DMAREQ_ID_UART7_RX     - EDMAMUX_DMAREQ_ID_UART7_TX     - EDMAMUX_DMAREQ_ID_UART8_RX
  *         - EDMAMUX_DMAREQ_ID_UART8_TX     - EDMAMUX_DMAREQ_ID_SDIO1        - EDMAMUX_DMAREQ_ID_SDIO2        - EDMAMUX_DMAREQ_ID_QSPI1
  *         - EDMAMUX_DMAREQ_ID_QSPI2        - EDMAMUX_DMAREQ_ID_TMR1_CH1     - EDMAMUX_DMAREQ_ID_TMR1_CH2     - EDMAMUX_DMAREQ_ID_TMR1_CH3
  *         - EDMAMUX_DMAREQ_ID_TMR1_CH4     - EDMAMUX_DMAREQ_ID_TMR1_OVERFLOW- EDMAMUX_DMAREQ_ID_TMR1_TRIG    - EDMAMUX_DMAREQ_ID_TMR1_COM
  *         - EDMAMUX_DMAREQ_ID_TMR8_CH1     - EDMAMUX_DMAREQ_ID_TMR8_CH2     - EDMAMUX_DMAREQ_ID_TMR8_CH3     - EDMAMUX_DMAREQ_ID_TMR8_CH4
  *         - EDMAMUX_DMAREQ_ID_TMR8_UP      - EDMAMUX_DMAREQ_ID_TMR8_TRIG    - EDMAMUX_DMAREQ_ID_TMR8_COM     - EDMAMUX_DMAREQ_ID_TMR2_CH1
  *         - EDMAMUX_DMAREQ_ID_TMR2_CH2     - EDMAMUX_DMAREQ_ID_TMR2_CH3     - EDMAMUX_DMAREQ_ID_TMR2_CH4     - EDMAMUX_DMAREQ_ID_TMR2_OVERFLOW
  *         - EDMAMUX_DMAREQ_ID_TMR2_TRIG    - EDMAMUX_DMAREQ_ID_TMR3_CH1     - EDMAMUX_DMAREQ_ID_TMR3_CH2     - EDMAMUX_DMAREQ_ID_TMR3_CH3
  *         - EDMAMUX_DMAREQ_ID_TMR3_CH4     - EDMAMUX_DMAREQ_ID_TMR3_OVERFLOW- EDMAMUX_DMAREQ_ID_TMR3_TRIG    - EDMAMUX_DMAREQ_ID_TMR4_CH1
  *         - EDMAMUX_DMAREQ_ID_TMR4_CH2     - EDMAMUX_DMAREQ_ID_TMR4_CH3     - EDMAMUX_DMAREQ_ID_TMR4_CH4     - EDMAMUX_DMAREQ_ID_TMR4_OVERFLOW
  *         - EDMAMUX_DMAREQ_ID_TMR4_TRIG    - EDMAMUX_DMAREQ_ID_TMR5_CH1     - EDMAMUX_DMAREQ_ID_TMR5_CH2     - EDMAMUX_DMAREQ_ID_TMR5_CH3
  *         - EDMAMUX_DMAREQ_ID_TMR5_CH4     - EDMAMUX_DMAREQ_ID_TMR5_OVERFLOW- EDMAMUX_DMAREQ_ID_TMR5_TRIG    - EDMAMUX_DMAREQ_ID_TMR20_CH1
  *         - EDMAMUX_DMAREQ_ID_TMR20_CH2    - EDMAMUX_DMAREQ_ID_TMR20_CH3    - EDMAMUX_DMAREQ_ID_TMR20_CH4    - EDMAMUX_DMAREQ_ID_TMR20_OVERFLOW
  *         - EDMAMUX_DMAREQ_ID_TMR20_TRIG   - EDMAMUX_DMAREQ_ID_TMR20_HALL   - EDMAMUX_DMAREQ_ID_DVP
  * @retval none.
  */
void edmamux_init(edmamux_channel_type *edmamux_channelx, edmamux_requst_id_sel_type edmamux_req_id)
{
  edmamux_channelx->muxctrl_bit.reqsel = edmamux_req_id;
}

/**
  * @brief  edmamux sync init struct config with its default value.
  * @param  edmamux_sync_init_struct: pointer to a edmamux_sync_init_type structure which will be initialized.
  * @retval none.
  */
void edmamux_sync_default_para_init(edmamux_sync_init_type *edmamux_sync_init_struct)
{
  edmamux_sync_init_struct->sync_enable = FALSE;
  edmamux_sync_init_struct->sync_event_enable = FALSE;
  edmamux_sync_init_struct->sync_polarity = EDMAMUX_SYNC_POLARITY_DISABLE;
  edmamux_sync_init_struct->sync_request_number = 0x0;
  edmamux_sync_init_struct->sync_signal_sel = EDMAMUX_SYNC_ID_EXINT0;
}

/**
  * @brief  edmamux synchronization config.
  * @param  edmamux_channelx:
  *         this parameter can be one of the following values:
  *         - EDMAMUX_CHANNEL1
  *         - EDMAMUX_CHANNEL2
  *         - EDMAMUX_CHANNEL3
  *         - EDMAMUX_CHANNEL4
  *         - EDMAMUX_CHANNEL5
  *         - EDMAMUX_CHANNEL6
  *         - EDMAMUX_CHANNEL7
  *         - EDMAMUX_CHANNEL8
  * @param  edmamux_sync_init_struct: ointer to a edmamux_sync_init_type structure.
  * @retval none.
  */
void edmamux_sync_config(edmamux_channel_type *edmamux_channelx, edmamux_sync_init_type *edmamux_sync_init_struct)
{
  edmamux_channelx->muxctrl_bit.syncsel = edmamux_sync_init_struct->sync_signal_sel;
  edmamux_channelx->muxctrl_bit.syncpol = edmamux_sync_init_struct->sync_polarity;
  edmamux_channelx->muxctrl_bit.reqcnt  = edmamux_sync_init_struct->sync_request_number - 1;
  edmamux_channelx->muxctrl_bit.evtgen  = edmamux_sync_init_struct->sync_event_enable;
  edmamux_channelx->muxctrl_bit.syncen  = edmamux_sync_init_struct->sync_enable;
}

/**
  * @brief  edmamux request generator init struct config with its default value.
  * @param  edmamux_gen_init_struct: pointer to a edmamux_gen_init_type structure which will be initialized.
  * @retval none.
  */
void edmamux_generator_default_para_init(edmamux_gen_init_type *edmamux_gen_init_struct)
{
  edmamux_gen_init_struct->gen_enable         = FALSE;
  edmamux_gen_init_struct->gen_polarity       = EDMAMUX_GEN_POLARITY_DISABLE;
  edmamux_gen_init_struct->gen_request_number = 0x0;
  edmamux_gen_init_struct->gen_signal_sel     = EDMAMUX_GEN_ID_EXINT0;
}

/**
  * @brief  edmamux request generator init.
  * @param  edmamux_gen_init_struct: pointer to a edmamux_gen_init_type structure which will be initialized.
  * @retval none.
  */
void edmamux_generator_config(edmamux_generator_type *edmamux_gen_x, edmamux_gen_init_type *edmamux_gen_init_struct)
{
  edmamux_gen_x->gctrl_bit.sigsel  = edmamux_gen_init_struct->gen_signal_sel;
  edmamux_gen_x->gctrl_bit.gpol    = edmamux_gen_init_struct->gen_polarity;
  edmamux_gen_x->gctrl_bit.greqcnt = edmamux_gen_init_struct->gen_request_number - 1;
  edmamux_gen_x->gctrl_bit.gen     = edmamux_gen_init_struct->gen_enable;
}

/**
  * @brief  enable or disable the edmamux sync interrupts.
  * @param  edmamux_channelx:
  *         this parameter can be one of the following values:
  *         - EDMAMUX_CHANNEL1
  *         - EDMAMUX_CHANNEL2
  *         - EDMAMUX_CHANNEL3
  *         - EDMAMUX_CHANNEL4
  *         - EDMAMUX_CHANNEL5
  *         - EDMAMUX_CHANNEL6
  *         - EDMAMUX_CHANNEL7
  *         - EDMAMUX_CHANNEL8
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void edmamux_sync_interrupt_enable(edmamux_channel_type *edmamux_channelx, confirm_state new_state)
{
  if(new_state != FALSE)
  {
    edmamux_channelx->muxctrl_bit.syncovien = TRUE;
  }
  else
  {
    edmamux_channelx->muxctrl_bit.syncovien = FALSE;
  }
}

/**
  * @brief  enable or disable the edmamux request generator interrupts.
  * @param  edmamux_gen_x: pointer to a edmamux_generator_type structure.
  *         this parameter can be one of the following values:
  *         - EDMAMUX_GENERATOR1
  *         - EDMAMUX_GENERATOR2
  *         - EDMAMUX_GENERATOR3
  *         - EDMAMUX_GENERATOR4
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void edmamux_generator_interrupt_enable(edmamux_generator_type *edmamux_gen_x, confirm_state new_state)
{
  if(new_state != FALSE)
  {
    edmamux_gen_x->gctrl_bit.trgovien = TRUE;
  }
  else
  {
    edmamux_gen_x->gctrl_bit.trgovien = FALSE;
  }
}

/**
  * @brief  edmamux sync flag get.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - EDMAMUX_SYNC_OV1_FLAG
  *         - EDMAMUX_SYNC_OV2_FLAG
  *         - EDMAMUX_SYNC_OV3_FLAG
  *         - EDMAMUX_SYNC_OV4_FLAG
  *         - EDMAMUX_SYNC_OV5_FLAG
  *         - EDMAMUX_SYNC_OV6_FLAG
  *         - EDMAMUX_SYNC_OV7_FLAG
  *         - EDMAMUX_SYNC_OV8_FLAG
  * @retval state of edmamux sync flag.
  */
flag_status edmamux_sync_flag_get(uint32_t flag)
{
  if((EDMA->muxsyncsts & flag) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  edmamux sync interrupt flag get.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - EDMAMUX_SYNC_OV1_FLAG
  *         - EDMAMUX_SYNC_OV2_FLAG
  *         - EDMAMUX_SYNC_OV3_FLAG
  *         - EDMAMUX_SYNC_OV4_FLAG
  *         - EDMAMUX_SYNC_OV5_FLAG
  *         - EDMAMUX_SYNC_OV6_FLAG
  *         - EDMAMUX_SYNC_OV7_FLAG
  *         - EDMAMUX_SYNC_OV8_FLAG
  * @retval state of edmamux sync flag.
  */
flag_status edmamux_sync_interrupt_flag_get(uint32_t flag)
{
  uint32_t int_stat = 0;

  if(flag == EDMAMUX_SYNC_OV1_FLAG)
  {
    int_stat = (uint32_t)EDMAMUX_CHANNEL1->muxctrl_bit.syncovien;
  }
  else if(flag == EDMAMUX_SYNC_OV2_FLAG)
  {
    int_stat = (uint32_t)EDMAMUX_CHANNEL2->muxctrl_bit.syncovien;
  }
  else if(flag == EDMAMUX_SYNC_OV3_FLAG)
  {
    int_stat = (uint32_t)EDMAMUX_CHANNEL3->muxctrl_bit.syncovien;
  }
  else if(flag == EDMAMUX_SYNC_OV4_FLAG)
  {
    int_stat = (uint32_t)EDMAMUX_CHANNEL4->muxctrl_bit.syncovien;
  }
  else if(flag == EDMAMUX_SYNC_OV5_FLAG)
  {
    int_stat = (uint32_t)EDMAMUX_CHANNEL5->muxctrl_bit.syncovien;
  }
  else if(flag == EDMAMUX_SYNC_OV6_FLAG)
  {
    int_stat = (uint32_t)EDMAMUX_CHANNEL6->muxctrl_bit.syncovien;
  }
  else if(flag == EDMAMUX_SYNC_OV7_FLAG)
  {
    int_stat = (uint32_t)EDMAMUX_CHANNEL7->muxctrl_bit.syncovien;
  }
  else
  {
    int_stat = (uint32_t)EDMAMUX_CHANNEL8->muxctrl_bit.syncovien;
  }

  if((int_stat != RESET) && ((EDMA->muxsyncsts & flag) != RESET))
    return SET;
  else
    return RESET;
}

/**
  * @brief  edmamux sync flag clear.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - EDMAMUX_SYNC_OV1_FLAG
  *         - EDMAMUX_SYNC_OV2_FLAG
  *         - EDMAMUX_SYNC_OV3_FLAG
  *         - EDMAMUX_SYNC_OV4_FLAG
  *         - EDMAMUX_SYNC_OV5_FLAG
  *         - EDMAMUX_SYNC_OV6_FLAG
  *         - EDMAMUX_SYNC_OV7_FLAG
  *         - EDMAMUX_SYNC_OV8_FLAG
  * @retval none.
  */
void edmamux_sync_flag_clear(uint32_t flag)
{
  EDMA->muxsyncclr = flag;
}

/**
  * @brief  edmamux request generator flag get.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - EDMAMUX_GEN_TRIG_OV1_FLAG
  *         - EDMAMUX_GEN_TRIG_OV2_FLAG
  *         - EDMAMUX_GEN_TRIG_OV3_FLAG
  *         - EDMAMUX_GEN_TRIG_OV4_FLAG
  * @retval state of edmamux sync flag.
  */
flag_status edmamux_generator_flag_get(uint32_t flag)
{
  if((EDMA->muxgsts & flag) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  edmamux request generator interrupt flag get.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - EDMAMUX_GEN_TRIG_OV1_FLAG
  *         - EDMAMUX_GEN_TRIG_OV2_FLAG
  *         - EDMAMUX_GEN_TRIG_OV3_FLAG
  *         - EDMAMUX_GEN_TRIG_OV4_FLAG
  * @retval state of edmamux sync flag.
  */
flag_status edmamux_generator_interrupt_flag_get(uint32_t flag)
{
  uint32_t int_stat = 0;

  if(flag == EDMAMUX_GEN_TRIG_OV1_FLAG)
  {
    int_stat = EDMAMUX_GENERATOR1->gctrl_bit.trgovien;
  }
  else if(flag == EDMAMUX_GEN_TRIG_OV2_FLAG)
  {
    int_stat = EDMAMUX_GENERATOR2->gctrl_bit.trgovien;
  }
  else if(flag == EDMAMUX_GEN_TRIG_OV3_FLAG)
  {
    int_stat = EDMAMUX_GENERATOR3->gctrl_bit.trgovien;
  }
  else
  {
    int_stat = EDMAMUX_GENERATOR4->gctrl_bit.trgovien;
  }

  if((int_stat != RESET) && ((EDMA->muxgsts & flag) != RESET))
    return SET;
  else
    return RESET;
}

/**
  * @brief  edmamux request generator flag clear.
  * @param  flag
  *         this parameter can be any combination of the following values:
  *         - EDMAMUX_GEN_TRIG_OV1_FLAG
  *         - EDMAMUX_GEN_TRIG_OV2_FLAG
  *         - EDMAMUX_GEN_TRIG_OV3_FLAG
  *         - EDMAMUX_GEN_TRIG_OV4_FLAG
  * @retval none.
  */
void edmamux_generator_flag_clear(uint32_t flag)
{
  EDMA->muxgclr = flag;
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
