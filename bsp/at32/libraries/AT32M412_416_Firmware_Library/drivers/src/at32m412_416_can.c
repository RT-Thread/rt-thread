/**
  **************************************************************************
  * @file     at32m412_416_can.c
  * @brief    contains all the functions for the can firmware library
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

#include "at32m412_416_conf.h"

/** @addtogroup AT32M412_416_periph_driver
  * @{
  */

/** @defgroup CAN
  * @brief CAN driver modules
  * @{
  */

#ifdef CAN_MODULE_ENABLED

#ifdef SUPPORT_CAN_FD 
static const uint8_t dlc_to_bytes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};
#endif

/** @defgroup CAN_private_functions
  * @{
  */

/**
  * @brief  deinitialize the can peripheral registers to their default reset values.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @retval none
  */
void can_reset(can_type* can_x)
{
  if(can_x == CAN1)
  {
    crm_periph_reset(CRM_CAN1_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_CAN1_PERIPH_RESET, FALSE);
  }
}

/**
  * @brief  enable can software reset, it is forces several components to a reset state.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  new_state: new state of software reset request.
  *         this parameter can be: TRUE or FALSE.
  * @retval none.
  */
void can_software_reset(can_type* can_x, confirm_state new_state)
{
  can_x->ctrlstat_bit.reset = new_state;
}

#ifdef SUPPORT_CAN_FD
/**
  * @brief  enable the ISO 11898-1:2015 protocol mode of the can peripheral.
  *         can-fd frame format is according to ISO 11898-1:2015 or Bosch(non-ISO) standard.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  new_state: new state of the can ISO 11898-1 protocol mode.
  *         this parameter can be: TRUE or FALSE.
  * @note   this bit is only writeable if RESET=1.
  * @retval none
  */
void can_fd_iso_mode_enable(can_type* can_x, confirm_state new_state)
{
  can_x->ctrlstat_bit.fd_iso = new_state;
}
#endif

/**
  * @brief  set the mode of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  mode_selection: select can mode type.
  *         this parameter can be one of the following values:
  *         - CAN_MODE_COMMUNICATE
  *         - CAN_MODE_EXT_LOOPBACK
  *         - CAN_MODE_EXT_LOOPBACK_ACK
  *         - CAN_MODE_INT_LOOPBACK
  *         - CAN_MODE_LISTENONLY
  *         - CAN_MODE_LISTENONLY_EXT
  *         - CAN_MODE_LISTENONLY_EXT_ACK
  * @retval none
  */
void can_mode_set(can_type* can_x, can_mode_type mode_selection)
{
  switch(mode_selection)
  {
    case CAN_MODE_COMMUNICATE:
      can_x->ctrlstat_bit.lbme = FALSE;
      can_x->ctrlstat_bit.sack = FALSE;
      can_x->ctrlstat_bit.lbmi = FALSE;
      can_x->ctrlstat_bit.lom = FALSE;
      break;
    case CAN_MODE_EXT_LOOPBACK:
      can_x->ctrlstat_bit.lbme = TRUE;
      can_x->ctrlstat_bit.sack = FALSE;
      can_x->ctrlstat_bit.lbmi = FALSE;
      can_x->ctrlstat_bit.lom = FALSE;
      break;
    case CAN_MODE_EXT_LOOPBACK_ACK:
      can_x->ctrlstat_bit.lbme = TRUE;
      can_x->ctrlstat_bit.sack = TRUE;
      can_x->ctrlstat_bit.lbmi = FALSE;
      can_x->ctrlstat_bit.lom = FALSE;
      break;
    case CAN_MODE_INT_LOOPBACK:
      can_x->ctrlstat_bit.lbme = FALSE;
      can_x->ctrlstat_bit.sack = FALSE;
      can_x->ctrlstat_bit.lbmi = TRUE;
      can_x->ctrlstat_bit.lom = FALSE;
      break;
    case CAN_MODE_LISTENONLY:
      can_x->ctrlstat_bit.lbme = FALSE;
      can_x->ctrlstat_bit.sack = FALSE;
      can_x->ctrlstat_bit.lbmi = FALSE;
      can_x->ctrlstat_bit.lom = TRUE;
      break;
    case CAN_MODE_LISTENONLY_EXT:
      can_x->ctrlstat_bit.lbme = TRUE;
      can_x->ctrlstat_bit.sack = FALSE;
      can_x->ctrlstat_bit.lbmi = FALSE;
      can_x->ctrlstat_bit.lom = TRUE;
      break;
    case CAN_MODE_LISTENONLY_EXT_ACK:
      can_x->ctrlstat_bit.lbme = TRUE;
      can_x->ctrlstat_bit.sack = TRUE;
      can_x->ctrlstat_bit.lbmi = FALSE;
      can_x->ctrlstat_bit.lom = TRUE;
      break;
    default:
      return;
  }
}

/**
  * @brief  enable the transceiver standby mode of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  new_state: new state of the can transceiver standby mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval SUCCESS or ERROR
  */
error_status can_standby_mode_enable(can_type* can_x, confirm_state new_state)
{
  if (new_state != FALSE)
  {
    /* CAN-CTRL does not allow STBY to be set if a transmission is already active (TPE, TSONE or TSALL is set). */
    if(can_x->ctrlstat_bit.tsall || can_x->ctrlstat_bit.tsone || can_x->ctrlstat_bit.tpe)
      return ERROR;
    can_x->ctrlstat_bit.stby = TRUE;
  }
  else
  {
    can_x->ctrlstat_bit.stby = FALSE;
  }
  
  return SUCCESS;
}

/**
  * @brief  enable restricted operation of the can peripheral.
  *         a can node which is in restricted operation mode shall not transmit data frames 
  *         unless it is a potential time master for ttcan.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  new_state: new state of the can restricted operation.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void can_restricted_operation_enable(can_type* can_x, confirm_state new_state)
{
  can_x->tncfg_bit.rop = new_state;
}

/**
  * @brief  fill each can_bittime_struct member with its default value.
  * @param  can_bittime_struct: pointer to a can_bittime_type structure which will be initialized.
  * @retval none.
  */
void can_bittime_default_para_init(can_bittime_type* can_bittime_struct)
{
  /* reset can bittime structure parameters values */

  can_bittime_struct->bittime_div = 1;
  
  can_bittime_struct->ac_bts1_size = 12;
  can_bittime_struct->ac_bts2_size = 4;
  can_bittime_struct->ac_rsaw_size = 4;
 
#ifdef SUPPORT_CAN_FD   
  can_bittime_struct->fd_bts1_size = 6;
  can_bittime_struct->fd_bts2_size = 2;
  can_bittime_struct->fd_rsaw_size = 2;
  can_bittime_struct->fd_ssp_offset = 7;
#endif
}

/**
  * @brief  set the bittime of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  can_bittime_struct: pointer to a can_bittime_type structure which will be set.
  * @note   baudrate calculate method is:
  *         baudrate = can_clk/(baudrate_div *(bts1_size + bts2_size))
  * @retval none
  */
void can_bittime_set(can_type* can_x, can_bittime_type* can_bittime_struct)
{
  can_x->lbtcfg_bit.presc = can_bittime_struct->bittime_div - 1;
  
  can_x->actime_bit.ac_seg_1 = can_bittime_struct->ac_bts1_size-2;
  can_x->actime_bit.ac_seg_2 = can_bittime_struct->ac_bts2_size-1;
  can_x->actime_bit.ac_sjw = can_bittime_struct->ac_rsaw_size-1;
 
#ifdef SUPPORT_CAN_FD   
  can_x->fdtime_bit.fd_seg_1 = can_bittime_struct->fd_bts1_size-2;
  can_x->fdtime_bit.fd_seg_2 = can_bittime_struct->fd_bts2_size-1;
  can_x->fdtime_bit.fd_sjw = can_bittime_struct->fd_rsaw_size-1;
  can_x->lbtcfg_bit.fd_sspoff = can_bittime_struct->fd_ssp_offset;
#endif
}

/**
  * @brief  set the retransmission limit value of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  re_trans_times: can re-transmission times type.
  *         this parameter can be one of the following values:
  *         - CAN_RE_TRANS_TIMES_0
  *         - CAN_RE_TRANS_TIMES_1
  *         - CAN_RE_TRANS_TIMES_2
  *         - CAN_RE_TRANS_TIMES_3
  *         - CAN_RE_TRANS_TIMES_4
  *         - CAN_RE_TRANS_TIMES_5
  *         - CAN_RE_TRANS_TIMES_6
  *         - CAN_RE_TRANS_TIMES_UNLIMIT
  * @retval none
  */
void can_retransmission_limit_set(can_type* can_x, can_retransmission_times_type re_trans_times)
{
  can_x->lbtcfg_bit.retlim = re_trans_times;
}

/**
  * @brief  set the re-arbitration limit value of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  re_arbi_times: can re-arbitration times type.
  *         this parameter can be one of the following values:
  *         - CAN_RE_ARBI_TIMES_0
  *         - CAN_RE_ARBI_TIMES_1
  *         - CAN_RE_ARBI_TIMES_2
  *         - CAN_RE_ARBI_TIMES_3
  *         - CAN_RE_ARBI_TIMES_4
  *         - CAN_RE_ARBI_TIMES_5
  *         - CAN_RE_ARBI_TIMES_6
  *         - CAN_RE_ARBI_TIMES_UNLIMIT
  * @retval none
  */
void can_rearbitration_limit_set(can_type* can_x, can_rearbitration_times_type re_arbi_times)
{
  can_x->lbtcfg_bit.realim = re_arbi_times;
}

/**
  * @brief  enable time-stamping of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  new_state: new state of the can time-stamping.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void can_timestamp_enable(can_type* can_x, confirm_state new_state)
{
  can_x->tncfg_bit.tsen = new_state;
}

/**
  * @brief  set time-stamping position of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  timestamp_position: can timestamp position type.
  *         this parameter can be one of the following values:
  *         - CAN_TIMESTAMP_AT_SOF
  *         - CAN_TIMESTAMP_AT_EOF
  * @retval none
  */
void can_timestamp_position_set(can_type* can_x, can_timestamp_position_type timestamp_position)
{
  can_x->tncfg_bit.tspos = timestamp_position;
}

/**
  * @brief  return the transmission timestamp of the specified can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @retval the value of transmission timestamp.
  */
uint32_t can_transmit_timestamp_get(can_type* can_x)
{
  return (uint32_t)can_x->tts;
}

/**
  * @brief  write the transmission buffer of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  txbuf_type: txbuf select type
  *         this parameter can be one of the following values:
  *         - CAN_TXBUF_PTB
  *         - CAN_TXBUF_STB
  * @param  can_txbuf_struct: pointer to a structure which contains the buffer to be trans.
  * @retval SUCCESS or ERROR
  */
error_status can_txbuf_write(can_type* can_x, can_txbuf_select_type txbuf_type, can_txbuf_type* can_txbuf_struct)
{ 
#ifdef SUPPORT_CAN_FD  
  uint8_t len = dlc_to_bytes[can_txbuf_struct->data_length];
#else  
  uint8_t len = can_txbuf_struct->data_length;
#endif 
  uint32_t* wp = (uint32_t*)can_x->tbdat;
  uint8_t* rp = can_txbuf_struct->data;
  uint8_t byte_cnt;
  
  uint8_t* reg;
  uint8_t tmp; 
  
  switch(txbuf_type)
  {
    case CAN_TXBUF_PTB:
      if(can_x->ctrlstat_bit.tpe == TRUE)
      {
        /* if tpe=1 then the primary transmit buffer is write-locked. */
        return ERROR;
      }
      break;
    case CAN_TXBUF_STB:
      if(can_x->ctrlstat_bit.tsnext == TRUE)
      {
        /* while TSNEXT=1, then writing to the secondary transmit buffer is blocked. */
        return ERROR;
      }
      break;
    default:
      return ERROR;
  }

  /* write TBSEL, avoid duplicate setting these bits(TSA, TSALL, TSONE, TPA, TPE and TBSEL). */
  reg = (uint8_t*)&can_x->ctrlstat + 1;
  tmp = *reg & 0x60;
  *reg = tmp | (txbuf_type<<7);
  
  switch(can_txbuf_struct->id_type)
  {
    case CAN_ID_STANDARD:
      can_x->tbid = (0x7FF & can_txbuf_struct->id)<<18;
      break;
    case CAN_ID_EXTENDED:
      can_x->tbid = (0x1FFFFFFF & can_txbuf_struct->id);
      break;
    default:
      return ERROR;
  }
  can_x->tbid |= (can_txbuf_struct->tx_timestamp << 31);
  
  can_x->tbfmt = 0;
  can_x->tbfmt_bit.ide = can_txbuf_struct->id_type;
  can_x->tbfmt_bit.rmf = can_txbuf_struct->frame_type;  
  can_x->tbfmt_bit.dlc = can_txbuf_struct->data_length;
#ifdef  SUPPORT_CAN_FD  
  can_x->tbfmt_bit.brs = can_txbuf_struct->fd_rate_switch;
  can_x->tbfmt_bit.fdf = can_txbuf_struct->fd_format;
#endif
  
  /* write tx payload to the buffer ram. */
  for (byte_cnt = 0; byte_cnt < len; byte_cnt += 4U)
  {
    *wp++ = (((uint32_t)rp[byte_cnt + 3U] << 24U) |
             ((uint32_t)rp[byte_cnt + 2U] << 16U) |
             ((uint32_t)rp[byte_cnt + 1U] << 8U)  |
              (uint32_t)rp[byte_cnt]);
  }
  
  can_x->tbtyp = 0;
  can_x->tbtyp_bit.handle = can_txbuf_struct->handle;
  can_x->tbacf = 0;
  
  if(txbuf_type == CAN_TXBUF_STB)
  {
    /* write TSNEXT, mark a slot filled and point to the next frame slot. */
    reg = (uint8_t*)&can_x->ctrlstat + 2;
    tmp = *reg;
    *reg = tmp | 0x40;    
  }
  
  return SUCCESS;
}

/**
  * @brief  read the receive buffer of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  can_rxbuf_struct: pointer to a structure which contains the buffer to be receive.
  * @retval SUCCESS or ERROR
  */
error_status can_rxbuf_read(can_type* can_x, can_rxbuf_type* can_rxbuf_struct)
{
#ifdef SUPPORT_CAN_FD
  uint8_t len = dlc_to_bytes[can_x->rbfmt_bit.dlc];
#else
  uint8_t len = can_x->rbfmt_bit.dlc;
#endif
  uint32_t* rp = (uint32_t*)can_x->rbdat;
  uint8_t* wp = can_rxbuf_struct->data;
  uint8_t byte_cnt;
  uint16_t pos;

  uint8_t* reg;
  uint8_t tmp; 

  if(can_x->ctrlstat_bit.rstat == CAN_RXBUF_STATUS_EMPTY)
  {
    /* receive buffer is empty. */
    return ERROR;  
  }
  
  can_rxbuf_struct->id_type = (can_identifier_type)can_x->rbfmt_bit.ide;
  switch(can_rxbuf_struct->id_type)
  {
    case CAN_ID_STANDARD:
      can_rxbuf_struct->id = 0x7FF & (can_x->rbid >> 18);
      break;
    case CAN_ID_EXTENDED:
      can_rxbuf_struct->id = (0x1FFFFFFF & can_x->rbid);
      break;
    default:
      return ERROR;
  }
  
  can_rxbuf_struct->frame_type = (can_frame_type)can_x->rbfmt_bit.rmf;
#ifdef SUPPORT_CAN_FD  
  can_rxbuf_struct->fd_format = (can_format_type)can_x->rbfmt_bit.fdf;
  can_rxbuf_struct->fd_rate_switch = (can_rate_switch_type)can_x->rbfmt_bit.brs;
  can_rxbuf_struct->fd_error_state = (can_error_state_type)can_x->rbfmt_bit.esi;
#endif 
  can_rxbuf_struct->kind_error = (can_error_type)can_x->rbfmt_bit.koer;
  can_rxbuf_struct->recv_frame = (can_recv_frame_type)can_x->rbfmt_bit.lbf;
  can_rxbuf_struct->data_length = (can_data_length_type)can_x->rbfmt_bit.dlc;
  
  /* read the buffer ram to rx payload */
  for (byte_cnt = 0; byte_cnt < len; byte_cnt += 4U)
  {
    wp[byte_cnt] = *rp & 0xFF;
    wp[byte_cnt+1U] = (*rp >> 8U) & 0xFF;
    wp[byte_cnt+2U] = (*rp >> 16U) & 0xFF;
    wp[byte_cnt+3U] = (*rp >> 24U) & 0xFF;
    rp++;
  }
  
  can_x->llcformat = can_x->rbfmt;
  pos = (can_x->llcsize_bit.llcaot / 4) - 4;
  can_rxbuf_struct->rx_timestamp = (uint32_t)can_x->rbdat[pos];
  can_rxbuf_struct->cycle_time = (uint16_t)can_x->rbdat[pos + 2];
  
  /* set RREL, receive buffer release. */
  reg = (uint8_t*)&can_x->ctrlstat + 3;
  tmp = *reg;
  *reg = tmp | 0x10;

  return SUCCESS;
}

/**
  * @brief  enable acceptance filters of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  filter_number: point to a specific acceptance filter.
  *         this parameter can be one of the following values:  
  *         - CAN_FILTER_NUM_0
  *         - CAN_FILTER_NUM_1
  *         - CAN_FILTER_NUM_2
  *         - CAN_FILTER_NUM_3
  *         - CAN_FILTER_NUM_4
  *         - CAN_FILTER_NUM_5
  *         - CAN_FILTER_NUM_6
  *         - CAN_FILTER_NUM_7
  *         - CAN_FILTER_NUM_8
  *         - CAN_FILTER_NUM_9
  *         - CAN_FILTER_NUM_10
  *         - CAN_FILTER_NUM_11
  *         - CAN_FILTER_NUM_12
  *         - CAN_FILTER_NUM_13
  *         - CAN_FILTER_NUM_14
  *         - CAN_FILTER_NUM_15
  * @param  new_state: new state of the specific acceptance filter.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void can_filter_enable(can_type* can_x, can_filter_type filter_number, confirm_state new_state)
{
  if (new_state != FALSE)
  {
    can_x->acfctrl_bit.ae_x |= (uint16_t)(1<<filter_number);
  }
  else
  {
    can_x->acfctrl_bit.ae_x &= (uint16_t)~(1<<filter_number);
  }
}

/**
  * @brief  fill each filter_config_struct member with its default value.
  * @param  filter_config_struct: pointer to a can_filter_config_type structure which will be initialized.
  * @retval none.
  */
void can_filter_default_para_init(can_filter_config_type* filter_config_struct)
{
  /* reset can filter config structure parameters values */
 
  filter_config_struct->code_para.id = 0;
  filter_config_struct->code_para.id_type = CAN_ID_STANDARD;
  filter_config_struct->code_para.frame_type = CAN_FRAME_DATA;
  filter_config_struct->code_para.data_length = 0;
  filter_config_struct->code_para.recv_frame = CAN_RECV_NORMAL;
#ifdef SUPPORT_CAN_FD
  filter_config_struct->code_para.fd_format = CAN_FORMAT_CLASSIC;
  filter_config_struct->code_para.fd_rate_switch = CAN_BRS_OFF;
  filter_config_struct->code_para.fd_error_state = CAN_ESI_ACTIVE;
#endif 
 
  filter_config_struct->mask_para.id = 0xFFFFFFFF;
  filter_config_struct->mask_para.id_type = TRUE;
  filter_config_struct->mask_para.frame_type = TRUE;
  filter_config_struct->mask_para.data_length = 0xF;
  filter_config_struct->mask_para.recv_frame = TRUE;
#ifdef SUPPORT_CAN_FD
  filter_config_struct->mask_para.fd_format = TRUE;
  filter_config_struct->mask_para.fd_rate_switch = TRUE;
  filter_config_struct->mask_para.fd_error_state = TRUE;
#endif 
}

/**
  * @brief  set acceptance filters of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  filter_number: point to a specific acceptance filter number.
  *         this parameter can be one of the following values:  
  *         - CAN_FILTER_NUM_0
  *         - CAN_FILTER_NUM_1
  *         - CAN_FILTER_NUM_2
  *         - CAN_FILTER_NUM_3
  *         - CAN_FILTER_NUM_4
  *         - CAN_FILTER_NUM_5
  *         - CAN_FILTER_NUM_6
  *         - CAN_FILTER_NUM_7
  *         - CAN_FILTER_NUM_8
  *         - CAN_FILTER_NUM_9
  *         - CAN_FILTER_NUM_10
  *         - CAN_FILTER_NUM_11
  *         - CAN_FILTER_NUM_12
  *         - CAN_FILTER_NUM_13
  *         - CAN_FILTER_NUM_14
  *         - CAN_FILTER_NUM_15
  * @param  filter_config_struct: pointer to a structure which contains acceptance filter config.
  * @retval none
  */
void can_filter_set(can_type* can_x, can_filter_type filter_number, can_filter_config_type* filter_config_struct)
{
  can_x->acfctrl_bit.acfadr = filter_number;
  
  switch(filter_config_struct->code_para.id_type)
  {
    case CAN_ID_STANDARD:
      can_x->fcid = (0x7FF & filter_config_struct->code_para.id)<<18;
      break;
    case CAN_ID_EXTENDED:
      can_x->fcid = (0x1FFFFFFF & filter_config_struct->code_para.id);
      break;
    default:
      break;
  }
  can_x->fcfmt_bit.ide = filter_config_struct->code_para.id_type;
  can_x->fcfmt_bit.rmf = filter_config_struct->code_para.frame_type;
  can_x->fcfmt_bit.dlc = filter_config_struct->code_para.data_length;
  can_x->fcfmt_bit.lbf = filter_config_struct->code_para.recv_frame;
#ifdef SUPPORT_CAN_FD  
  can_x->fcfmt_bit.brs = filter_config_struct->code_para.fd_rate_switch;
  can_x->fcfmt_bit.fdf = filter_config_struct->code_para.fd_format;
  can_x->fcfmt_bit.esi = filter_config_struct->code_para.fd_error_state;
#endif  
  
  can_x->fmid = 0xFFFFFFFF;
  /* write mask_id by id_type of filter_code_struct. */
  switch(filter_config_struct->code_para.id_type)
  {
    case CAN_ID_STANDARD:
      can_x->fmid &= ~((0x7FF & ~filter_config_struct->mask_para.id)<<18);
      break;
    case CAN_ID_EXTENDED:
      can_x->fmid &= ~(0x1FFFFFFF & ~filter_config_struct->mask_para.id);
      break;
    default:
      break;
  }
  can_x->fmfmt = 0xFFFFFFFF;
  can_x->fmfmt_bit.ide = filter_config_struct->mask_para.id_type;
  can_x->fmfmt_bit.rmf = filter_config_struct->mask_para.frame_type;  
  can_x->fmfmt_bit.dlc = filter_config_struct->mask_para.data_length;
  can_x->fmfmt_bit.lbf = filter_config_struct->mask_para.recv_frame; 
#ifdef SUPPORT_CAN_FD  
  can_x->fmfmt_bit.brs = filter_config_struct->mask_para.fd_rate_switch;
  can_x->fmfmt_bit.fdf = filter_config_struct->mask_para.fd_format;
  can_x->fmfmt_bit.esi = filter_config_struct->mask_para.fd_error_state;
#endif  
  can_x->fmtyp = 0xFFFFFFFF;
  can_x->fmacf = 0xFFFFFFFF;
}

/**
  * @brief  release the receive buffer of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @retval SUCCESS or ERROR
  */
error_status can_rxbuf_release(can_type* can_x)
{
  uint8_t* reg;
  uint8_t tmp; 

  if(can_x->ctrlstat_bit.rstat == CAN_RXBUF_STATUS_EMPTY)
  {
    /* receive buffer is empty. */
    return ERROR;
  }

  /* set RREL, receive buffer release. */
  reg = (uint8_t*)&can_x->ctrlstat + 3;
  tmp = *reg;
  *reg = tmp | 0x10;

  return SUCCESS;
}

/**
  * @brief  return the bit position in the frame where the arbitration has been lost.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @retval the value of the bit position in the frame.
  */
uint8_t can_arbitration_lost_position_get(can_type* can_x)
{
  return (uint8_t)can_x->err_bit.alc;
}

/**
  * @brief  set the value of receive buffer almost full warning limit.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  warning_value: defines the internal warning limit of receive buffer almost full. 
  *         this parameter can be 1~6.
  * @retval none
  */
void can_rxbuf_warning_set(can_type* can_x, uint8_t warning_value)
{
  can_x->err_bit.afwl = warning_value;
}

/**
  * @brief  set the value of error warning limit controls EIF.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  warning_value: programmable error warning limit = (warning_value + 1)*8. possible limit values: 8, 16, бн 128. 
  *         this parameter can be 0~15.
  * @retval none
  */
void can_error_warning_set(can_type* can_x, uint8_t warning_value)
{
  can_x->err_bit.ewl = warning_value;
}

/**
  * @brief  return the receive error counter of the specified can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @retval the value of receive error counter.
  */
uint8_t can_receive_error_counter_get(can_type* can_x)
{
  uint8_t counter = 0;
  counter = can_x->err_bit.recnt;
  return counter;
}

/**
  * @brief  return the transmit error counter of the specified can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @retval the value of transmit error counter.
  */
uint8_t can_transmit_error_counter_get(can_type* can_x)
{
  uint8_t counter = 0;
  counter = can_x->err_bit.tecnt;
  return counter;
}

/**
  * @brief  return error type of the specified can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @retval can kind of error type. 
  *         the returned value can be one of the following values:
  *         - CAN_KOER_NOERR
  *         - CAN_KOER_BIT
  *         - CAN_KOER_FORM
  *         - CAN_KOER_STUFF
  *         - CAN_KOER_ACK
  *         - CAN_KOER_CRC
  *         - CAN_KOER_OTHER
  *         - CAN_KOER_PCRC
  */
can_error_type can_kind_error_get(can_type* can_x)
{
  can_error_type error_code = CAN_KOER_NOERR;

  error_code = (can_error_type)can_x->err_bit.koer;

  return error_code;
}

/**
  * @brief  get bus off flag of the specified can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @retval status of can bus off flag, the returned value can be:SET or RESET.
  */
flag_status can_busoff_get(can_type* can_x)
{
  flag_status bit_status = RESET;
  if(can_x->ctrlstat_bit.busoff)
  {
    bit_status = SET;
  }
  return bit_status; 
}

/**
  * @brief  resets the error counters and therefore forces the node to leave the bus off state.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @retval none.
  */
void can_busoff_reset(can_type* can_x)
{
  can_x->ctrlstat_bit.busoff = SET;
}

/**
  * @brief  set the secondary transmit buffer operation mode.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  stb_transmit_mode: secondary transmit buffer operation mode.
  *         this parameter can be one of the following values:
  *         - CAN_STB_TRANSMIT_BY_FIFO
  *         - CAN_STB_TRANSMIT_BY_ID
  * @note   the secondary transmit buffer operation mode shall be switched only if RESET=1.
  * @retval none
  */
void can_stb_transmit_mode_set(can_type* can_x, can_stb_transmit_mode_type stb_transmit_mode)
{
  can_x->ctrlstat_bit.tsmode = stb_transmit_mode;
}

/**
  * @brief  get the status of can secondary transmit buffer.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @retval the status of the secondary transmit buffer. 
  *         the returned value can be one of the following values:
  *         - CAN_STB_STATUS_EMPTY
  *         - CAN_STB_STATUS_LESS
  *         - CAN_STB_STATUS_MORE
  *         - CAN_STB_STATUS_FULL
  */
can_stb_status_type can_stb_status_get(can_type* can_x)
{
  uint8_t status = can_x->ctrlstat_bit.tsstat;
  return (can_stb_status_type)status;
}

/**
  * @brief  get the status of can frame transmissions.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  transmit_status_struct: pointer to a structure which contains the status of the frame transmissions.
  * @retval none
  */
void can_transmit_status_get(can_type* can_x, can_transmit_status_type* transmit_status_struct)
{
  transmit_status_struct->current_handle = can_x->tstat_bit.handle_1;
  transmit_status_struct->current_tstat = (can_tstat_encoding_type)can_x->tstat_bit.tstat_1;
  transmit_status_struct->final_handle = can_x->tstat_bit.handle_2;
  transmit_status_struct->final_tstat = (can_tstat_encoding_type)can_x->tstat_bit.tstat_2;
}

/**
  * @brief  get the status of can receive buffer.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @retval the status of can receive buffer. 
  *         the returned value can be:
  *         - CAN_RXBUF_STATUS_EMPTY
  *         - CAN_RXBUF_STATUS_LESS
  *         - CAN_RXBUF_STATUS_ALMOST
  *         - CAN_RXBUF_STATUS_FULL
  *         - CAN_RXBUF_STATUS_OVERFLOW
  */
can_rxbuf_status_type can_rxbuf_status_get(can_type* can_x)
{
  uint8_t status = can_x->ctrlstat_bit.rstat;
  
  if(can_x->ctrlstat_bit.rov == SET)
  {
    status = CAN_RXBUF_STATUS_OVERFLOW;
  }
  
  return (can_rxbuf_status_type)status;
}

/**
  * @brief  set the mode of receive buffer overflow.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  rxbuf_overflow_mode: the mode of receive buffer overflow.
  *         this parameter can be one of the following values:
  *         - CAN_RXBUF_OVERFLOW_BE_OVWR
  *         - CAN_RXBUF_OVERFLOW_BE_LOSE
  * @retval none
  */
void can_rxbuf_overflow_mode_set(can_type* can_x, can_rxbuf_overflow_mode_type rxbuf_overflow_mode)
{
  can_x->ctrlstat_bit.rom = rxbuf_overflow_mode;
}

/**
  * @brief  enable receive buffer stores all frames include frames with error.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  new_state: new state of receive buffer stores frames.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void can_receive_all_enable(can_type* can_x, confirm_state new_state)
{
  can_x->ctrlstat_bit.rball = new_state;
}

/**
  * @brief  abort a transmission from the primary transmit buffer or the secondary transmit buffer of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  abort_type: abort transmit type.
  *         this parameter can be one of the following values:
  *         - CAN_ABORT_TRANSMIT_PTB
  *         - CAN_ABORT_TRANSMIT_STB
  * @retval none
  */
void can_transmit_abort(can_type* can_x, can_abort_transmit_type abort_type)
{
  uint8_t* reg = (uint8_t*)&can_x->ctrlstat + 1;
  uint8_t tmp;
  
  /* avoid duplicate setting these bits(TSA, TSALL, TSONE, TPA, TPE). */
  tmp = *reg & 0xE0;
  *reg = tmp | abort_type;
}

/**
  * @brief  clear the secondary transmit buffer of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  abort_type: abort transmit type.
  *         this parameter can be one of the following values:
  *         - CAN_CLEAR_STB_ONE
  *         - CAN_CLEAR_STB_ALL
  * @retval SUCCESS or ERROR
  */
error_status can_stb_clear(can_type* can_x, can_clear_stb_type clear_type)
{
  uint8_t* reg = (uint8_t*)&can_x->ctrlstat + 1;
  uint8_t tmp;
  
  if(can_x->ctrlstat_bit.tsstat == CAN_STB_STATUS_EMPTY)
  {
    /* the secondary transmit buffer is empty. */
    return ERROR; 
  }
  
  /* avoid duplicate setting these bits(TSA, TSALL, TSONE, TPA, TPE). */
  tmp = *reg & 0xE0;
  *reg = tmp | clear_type;
  
  return SUCCESS;
}

/**
  * @brief  transmit the frame from txbuf of the can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  transmit_type: select transmit txbuf type.
  *         this parameter can be one of the following values:
  *         - CAN_TRANSMIT_PTB
  *         - CAN_TRANSMIT_STB_ONE
  *         - CAN_TRANSMIT_STB_ALL
  * @retval SUCCESS or ERROR
  */
error_status can_txbuf_transmit(can_type* can_x, can_txbuf_transmit_type transmit_type)
{
  uint8_t* reg = (uint8_t*)&can_x->ctrlstat + 1;
  uint8_t tmp; 
  
  /* once standby is activated no transmission is possible. */
  if(can_x->ctrlstat_bit.stby == SET)
    return ERROR;

  switch(transmit_type)
  {
    case CAN_TRANSMIT_PTB:
      if(can_x->ctrlstat_bit.tpe || can_x->ctrlstat_bit.tpa)
        return ERROR;     
      break;
    case CAN_TRANSMIT_STB_ONE:
    case CAN_TRANSMIT_STB_ALL:
      if(can_x->ctrlstat_bit.tsstat == CAN_STB_STATUS_EMPTY)
        return ERROR;     
      if(can_x->ctrlstat_bit.tsall || can_x->ctrlstat_bit.tsone || can_x->ctrlstat_bit.tsa)
        return ERROR;
      break;
    default:
      return ERROR;
  }
  
  /* avoid duplicate setting these bits(TSA, TSALL, TSONE, TPA, TPE). */
  tmp = *reg & 0xE0;
  *reg = tmp | transmit_type;
  
  return SUCCESS;
}

/**
  * @brief  set the reference message identifier for ttcan.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  id_type: the identifier type of reference message for ttcan.
  *         this parameter can be one of the following values:
  *         - CAN_ID_STANDARD
  *         - CAN_ID_EXTENDED
  * @param  id: the identifier of reference message for ttcan.
  * @retval none
  */
void can_ttcan_ref_message_set(can_type* can_x, can_identifier_type id_type, uint32_t id)
{
  can_x->refmsg_bit.ref_ide = id_type;
  switch(id_type)
  {
    case CAN_ID_STANDARD:
      can_x->refmsg_bit.ref_id = (0x7FF & id);
      break;
    case CAN_ID_EXTENDED:
      can_x->refmsg_bit.ref_id = (0x1FFFFFFF & id);
      break;
    default:
      break;
  }
}

/**
  * @brief  set the timer prescaler for ttcan.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  div_value: can ttcan time trigger div type.
  *         this parameter can be one of the following values:
  *         - CAN_TTCAN_TIMER_DIV_1
  *         - CAN_TTCAN_TIMER_DIV_2
  *         - CAN_TTCAN_TIMER_DIV_4
  *         - CAN_TTCAN_TIMER_DIV_8
  * @retval none
  */
void can_ttcan_timer_div_set(can_type* can_x, can_ttcan_timer_div_type div_value)
{
  can_x->ttcfg_bit.t_presc = div_value;
}

/**
  * @brief  enable time trigger for ttcan.
  *         if ttcan enabled, the timer for ttcan is running.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  new_state: new state of ttcan enable.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void can_ttcan_enable(can_type* can_x, confirm_state new_state)
{
  can_x->ttcfg_bit.tten = new_state;
}

/**
  * @brief  enable transmit buffer support for ttcan mode.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  new_state: new state of transmit buffer support for ttcan.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void can_ttcan_txbuf_enable(can_type* can_x, confirm_state new_state)
{
  can_x->ctrlstat_bit.tttbm = new_state;
}

/**
  * @brief  set the trigger type for ttcan.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  trigger_type: can ttcan trigger type.
  *         this parameter can be one of the following values:
  *         - CAN_TTCAN_TRIGGER_IMMEDIATE
  *         - CAN_TTCAN_TRIGGER_TIME
  *         - CAN_TTCAN_TRIGGER_SINGLE_TRANSMIT
  *         - CAN_TTCAN_TRIGGER_TRANSMIT_START
  *         - CAN_TTCAN_TRIGGER_TRANSMIT_STOP
  * @retval none
  */
void can_ttcan_trigger_type_set(can_type* can_x, can_ttcan_trigger_type trigger_type)
{
  can_x->ttcfg_bit.ttype = trigger_type;
}

/**
  * @brief  set the cycle time for a time trigger for ttcan.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  trigger_time: defines the cycle time for a time trigger.
  * @retval none
  */
void can_ttcan_trigger_set(can_type* can_x, uint16_t trigger_time)
{
  uint16_t* reg = (uint16_t*)&(can_x->tttrig);
  *reg = trigger_time;
}

/**
  * @brief  set the cycle time for a watch time trigger for ttcan.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  watch_trigger_time: defines the cycle time for a watch time trigger.
  * @retval none
  */
void can_ttcan_watch_trigger_set(can_type* can_x, uint16_t watch_trigger_time)
{
  uint16_t* reg = (uint16_t*)&(can_x->tttrig);
  *(reg + 1) = watch_trigger_time;
}

/**
  * @brief  set the txbuf slot status for ttcan.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  txbuf_number: pointer to a txbuf frame slot.
  *         this parameter can be one of the following values:  
  *         - CAN_TTCAN_TXBUF_NUM_0
  *         - CAN_TTCAN_TXBUF_NUM_1
  *         - CAN_TTCAN_TXBUF_NUM_2
  *         - CAN_TTCAN_TXBUF_NUM_3
  * @param  ttcan_buffer_type: ttcan txbuf slot status.
  *         this parameter can be one of the following values:
  *         - CAN_TTCAN_TXBUF_EMPTY
  *         - CAN_TTCAN_TXBUF_FILLED   
  * @retval none
  */
void can_ttcan_txbuf_status_set(can_type* can_x,  can_ttcan_txbuf_type txbuf_number, can_ttcan_txbuf_status_type status_type)
{
  can_x->ttcfg_bit.tbptr = txbuf_number;
  switch(status_type)
  {
    case CAN_TTCAN_TXBUF_EMPTY:
      can_x->ttcfg_bit.tbe = TRUE;
      break;
    case CAN_TTCAN_TXBUF_FILLED:
      can_x->ttcfg_bit.tbf = TRUE;
      break;
    default:
      return;
  }
}

/**
  * @brief  get the txbuf slot status for ttcan.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  txbuf_number: pointer to a txbuf frame slot.
  *         this parameter can be one of the following values:  
  *         - CAN_TTCAN_TXBUF_NUM_0
  *         - CAN_TTCAN_TXBUF_NUM_1
  *         - CAN_TTCAN_TXBUF_NUM_2
  *         - CAN_TTCAN_TXBUF_NUM_3
  * @retval ttcan_buffer_type: ttcan txbuf slot status.
  *         this parameter can be one of the following values:
  *         - CAN_TTCAN_TXBUF_EMPTY
  *         - CAN_TTCAN_TXBUF_FILLED
  */
can_ttcan_txbuf_status_type can_ttcan_txbuf_status_get(can_type* can_x, can_ttcan_txbuf_type txbuf_number)
{
  can_x->ttcfg_bit.tbptr = txbuf_number;
  if(can_x->ctrlstat_bit.tsff != SET)
  {
    return CAN_TTCAN_TXBUF_EMPTY;
  }
  else{
    return CAN_TTCAN_TXBUF_FILLED;
  }
}

/**
  * @brief  write the transmission buffer of the can peripheral for ttcan.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  txbuf_number: pointer to a txbuf frame slot.
  *         this parameter can be one of the following values:  
  *         - CAN_TTCAN_TXBUF_NUM_0
  *         - CAN_TTCAN_TXBUF_NUM_1
  *         - CAN_TTCAN_TXBUF_NUM_2
  *         - CAN_TTCAN_TXBUF_NUM_3
  * @param  can_txbuf_struct: pointer to a structure which contains the buffer to be trans.
  * @retval SUCCESS or ERROR.
  */
error_status can_ttcan_txbuf_write(can_type* can_x,  can_ttcan_txbuf_type txbuf_number, can_txbuf_type* can_txbuf_struct)
{
#ifdef SUPPORT_CAN_FD 
  uint8_t len = dlc_to_bytes[can_txbuf_struct->data_length];
#else 
  uint8_t len = can_txbuf_struct->data_length;
#endif 
  uint32_t *wp = (uint32_t*)can_x->tbdat;
  uint8_t *rp = can_txbuf_struct->data;
  uint8_t byte_cnt;
  
  can_x->ttcfg_bit.tbptr = txbuf_number;
  if(can_x->ctrlstat_bit.tsff == SET)
  {
    /* the buffer slot selected by tbptr be filled are write-locked. */
    return ERROR;
  }
  
  switch(can_txbuf_struct->id_type)
  {
    case CAN_ID_STANDARD:
      can_x->tbid = (0x7FF & can_txbuf_struct->id)<<18;
      break;
    case CAN_ID_EXTENDED:
      can_x->tbid = (0x1FFFFFFF & can_txbuf_struct->id);
      break;
    default:
      return ERROR;
  }
  can_x->tbid |= (can_txbuf_struct->tx_timestamp << 31);
  
  can_x->tbfmt = 0;
  can_x->tbfmt_bit.ide = can_txbuf_struct->id_type;
  can_x->tbfmt_bit.rmf = can_txbuf_struct->frame_type;  
  can_x->tbfmt_bit.dlc = can_txbuf_struct->data_length;
#ifdef SUPPORT_CAN_FD 
  can_x->tbfmt_bit.brs = can_txbuf_struct->fd_rate_switch;
  can_x->tbfmt_bit.fdf = can_txbuf_struct->fd_format;
#endif
  
  /* Write Tx payload to the message RAM */
  for (byte_cnt = 0; byte_cnt < len; byte_cnt += 4U)
  {
    *wp++ = (((uint32_t)rp[byte_cnt + 3U] << 24U) |
             ((uint32_t)rp[byte_cnt + 2U] << 16U) |
             ((uint32_t)rp[byte_cnt + 1U] << 8U)  |
              (uint32_t)rp[byte_cnt]);
  }
  
  can_x->tbtyp = 0;
  can_x->tbtyp_bit.handle = can_txbuf_struct->handle;
  can_x->tbacf = 0;
  
  /* the buffer slot selected by tbptr shall be marked as filled. */
  can_x->ttcfg_bit.tbf = TRUE;
  
  return SUCCESS;
}

/**
  * @brief  set transmit trigger txbuf slot pointer for ttcan.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  txbuf_number: pointer to a txbuf frame slot.
  *         this parameter can be one of the following values:  
  *         - CAN_TTCAN_TXBUF_NUM_0
  *         - CAN_TTCAN_TXBUF_NUM_1
  *         - CAN_TTCAN_TXBUF_NUM_2
  *         - CAN_TTCAN_TXBUF_NUM_3  
  * @retval none
  */
void can_ttcan_txbuf_transmit_set(can_type* can_x,  can_ttcan_txbuf_type txbuf_number)
{
  can_x->ttcfg_bit.ttptr = txbuf_number;
}

/**
  * @brief  set transmit enable window for ttcan.
  *         for a single shot transmit trigger there is a time of up to 16 ticks of the cycle time where the frame is allowed to start.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  window_ticks: transmit enable window. window_ticks+1 defines the number of ticks.
  *         this parameter can be 0~15.
  * @retval none
  */
void can_ttcan_transmit_window_set(can_type* can_x, uint8_t window_ticks)
{
  can_x->ttcfg_bit.tew = window_ticks;
}

/**
  * @brief  enable or disable the interrupt of the specified can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  can_int: specifies the can interrupt sources to be enabled or disabled.
  *         this parameter can be one of the following values:
  *         - CAN_AIE_INT
  *         - CAN_EIE_INT
  *         - CAN_TSIE_INT
  *         - CAN_TPIE_INT
  *         - CAN_RAFIE_INT
  *         - CAN_RFIE_INT
  *         - CAN_ROIE_INT
  *         - CAN_RIE_INT
  *         - CAN_BEIE_INT
  *         - CAN_ALIE_INT
  *         - CAN_EPIE_INT
  *         - CAN_TTIE_INT
  *         - CAN_TEIF_FLAG
  *         - CAN_WTIE_INT
  *         - CAN_ALL_INT
  * @param  new_state: new state of the can interrupts.
  *         this parameter can be: TRUE or FALSE.
  * @retval none.
  */
void can_interrupt_enable(can_type* can_x, uint32_t can_int, confirm_state new_state)
{
  if (new_state != FALSE)
  {
    can_x->inten |= can_int;
  }
  else
  {
    can_x->inten &= ~can_int;
  }
}  

/**
  * @brief  get flag of the specified can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  can_flag: select the flag.
  *         this parameter can be one of the following flags:
  *         - CAN_AIF_FLAG   
  *         - CAN_EIF_FLAG   
  *         - CAN_TSIF_FLAG   
  *         - CAN_TPIF_FLAG  
  *         - CAN_RAFIF_FLAG 
  *         - CAN_RFIF_FLAG  
  *         - CAN_ROIF_FLAG  
  *         - CAN_RIF_FLAG   
  *         - CAN_BEIF_FLAG  
  *         - CAN_ALIF_FLAG  
  *         - CAN_EPIF_FLAG  
  *         - CAN_TTIF_FLAG  
  *         - CAN_TEIF_FLAG  
  *         - CAN_WTIE_FLAG  
  *         - CAN_EPASS_FLAG 
  *         - CAN_EWARN_FLAG 
  * @retval status of can flag, the returned value can be:SET or RESET.
  */
flag_status can_flag_get(can_type* can_x, uint32_t can_flag)
{
  flag_status bit_status = RESET;
  if(can_x->sts & can_flag)
  {
    bit_status = SET;
  }
  return bit_status;
}

/**
  * @brief  get interrupt flag of the specified can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  can_flag: select the flag.
  *         this parameter can be one of the following flags:
  *         - CAN_AIF_FLAG   
  *         - CAN_EIF_FLAG   
  *         - CAN_TSIF_FLAG   
  *         - CAN_TPIF_FLAG  
  *         - CAN_RAFIF_FLAG 
  *         - CAN_RFIF_FLAG  
  *         - CAN_ROIF_FLAG  
  *         - CAN_RIF_FLAG   
  *         - CAN_BEIF_FLAG  
  *         - CAN_ALIF_FLAG  
  *         - CAN_EPIF_FLAG  
  *         - CAN_TTIF_FLAG  
  *         - CAN_TEIF_FLAG  
  *         - CAN_WTIE_FLAG
  * @retval flag_status (SET or RESET)
  */
flag_status can_interrupt_flag_get(can_type* can_x, uint32_t can_flag)
{
  flag_status status = RESET;
  if((can_x->inten & can_flag) && (can_x->sts & can_flag))
  {
    status = SET;
  }
  return status;
}

/**
  * @brief  clear flag of the specified can peripheral.
  * @param  can_x: select the can peripheral.
  *         this parameter can be one of the following values:
  *         CAN1.
  * @param  can_flag: select the flag.
  *         this parameter can be one of the following flags:
  *         - CAN_AIF_FLAG   
  *         - CAN_EIF_FLAG   
  *         - CAN_TSIF_FLAG  
  *         - CAN_TPIF_FLAG  
  *         - CAN_RAFIF_FLAG  
  *         - CAN_RFIF_FLAG  
  *         - CAN_ROIF_FLAG  
  *         - CAN_RIF_FLAG    
  *         - CAN_BEIF_FLAG  
  *         - CAN_ALIF_FLAG  
  *         - CAN_EPIF_FLAG  
  *         - CAN_TTIF_FLAG  
  *         - CAN_TEIF_FLAG   
  *         - CAN_WTIE_FLAG  
  *         - CAN_EPASS_FLAG 
  *         - CAN_EWARN_FLAG 
  *         - CAN_ALL_FLAG   
  * @retval none.
  */
void can_flag_clear(can_type* can_x, uint32_t can_flag)
{
  can_x->sts = can_flag;
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
