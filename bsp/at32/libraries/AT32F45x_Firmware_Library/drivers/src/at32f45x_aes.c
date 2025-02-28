/**
  **************************************************************************
  * @file     at32f45x_aes.c
  * @brief    contains all the functions for the aes firmware library
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

#include "at32f45x_conf.h"

/** @addtogroup AT32F45x_periph_driver
  * @{
  */

/** @defgroup AES
  * @brief AES driver modules
  * @{
  */

#ifdef AES_MODULE_ENABLED

/** @defgroup AES_private_functions
  * @{
  */

/**
  * @brief  reset the aes register
  * @param  none
  * @retval none
  */
void aes_reset(void)
{
  crm_periph_reset(CRM_AES_PERIPH_RESET, TRUE);
  crm_periph_reset(CRM_AES_PERIPH_RESET, FALSE);
}

/**
  * @brief  set aes key value
  * @param  aes_kl
  *         this parameter can be one of the following values:
  *         - AES_KEY_LENGTH_128
  *         - AES_KEY_LENGTH_192
  *         - AES_KEY_LENGTH_256
  * @param  aes_key
  *         - pointer to the aes key value
  * @retval none
  */
void aes_key_set(aes_key_length_type aes_kl, uint32_t* aes_key)
{
  AES->key0 = aes_key[0];
  AES->key1 = aes_key[1];
  AES->key2 = aes_key[2];
  AES->key3 = aes_key[3];
  if(aes_kl == AES_KEY_LENGTH_192)
  {
    AES->key4 = aes_key[4];
    AES->key5 = aes_key[5];
  }
  else if(aes_kl == AES_KEY_LENGTH_256)
  {
    AES->key4 = aes_key[4];
    AES->key5 = aes_key[5];
    AES->key6 = aes_key[6];
    AES->key7 = aes_key[7];
  }
}

/**
  * @brief  set aes initial vector
  * @param  aes_iv
  *         - pointer to the aes initial vector
  * @retval none
  */
void aes_iv_set(uint32_t* aes_iv)
{
  AES->iv0 = aes_iv[0];
  AES->iv1 = aes_iv[1];
  AES->iv2 = aes_iv[2];
  AES->iv3 = aes_iv[3];
}

/**
  * @brief  set aes number of dummy data
  * @param  num: number of dummy data (0~15)
  * @retval none
  */
void aes_dummy_data_num_set(uint8_t num)
{
  AES->ctrl_bit.ndd = (num & 0x0F);
}

/**
  * @brief  set processing stage field in ctrl regsiter, valid for ccm/gcm mode
  * @param  prc_type
  *         this parameter can be one of the following values:
  *         - AES_PRC_INIT
  *         - AES_PRC_ASSOC
  *         - AES_PRC_DATA
  *         - AES_PRC_TAG
  * @retval none
  */
void aes_processing_stage_set(aes_processing_stage_type prc_type)
{
  AES->ctrl_bit.prc = prc_type;
}

/**
  * @brief  aes init config with its default value
  * @param  aes_init_struct
  *         - pointer to a aes_init_type structure which will be initialized
  * @retval none
  */
void aes_default_para_init(aes_init_type* aes_init_struct)
{
  aes_init_struct->operate_mode = AES_OPMODE_DECRYPT;
  aes_init_struct->chaining_mode = AES_CHMODE_ECB;
  aes_init_struct->key_len = AES_KEY_LENGTH_128;
  aes_init_struct->key_buf = 0;
  aes_init_struct->data_swap_mode = AES_SWAP_TYPE_NONE;
}

/**
  * @brief  init aes
  * @param  aes_init_struct
  *         - pointer to a aes_init_type structure
  * @retval none
  */
void aes_init(aes_init_type* aes_init_struct)
{
  /* setup ctrl */
  AES->ctrl_bit.opr = aes_init_struct->operate_mode;
  AES->ctrl_bit.chn = aes_init_struct->chaining_mode;
  AES->ctrl_bit.swp = aes_init_struct->data_swap_mode;
  AES->ctrl_bit.kl = aes_init_struct->key_len;

  aes_key_set(aes_init_struct->key_len, aes_init_struct->key_buf);
}

/**
  * @brief  init aes suspend information
  * @param  none
  * @retval none
  */
void aes_suspend_info_init(void)
{
  AES->si0 = 0;
  AES->si1 = 0;
  AES->si2 = 0;
  AES->si3 = 0;
  AES->si4 = 0;
  AES->si5 = 0;
  AES->si6 = 0;
  AES->si7 = 0;
}

/**
  * @brief  set aes suspend information
  * @param  si_buf
  *         - pointer to the aes suspend information
  * @retval none
  */
void aes_suspend_info_set(uint32_t* si_buf)
{
  AES->si0 = si_buf[0];
  AES->si1 = si_buf[1];
  AES->si2 = si_buf[2];
  AES->si3 = si_buf[3];
  AES->si4 = si_buf[4];
  AES->si5 = si_buf[5];
  AES->si6 = si_buf[6];
  AES->si7 = si_buf[7];
}

/**
  * @brief  set aes operation mode
  * @param  op_mode
  *         this parameter can be one of the following values:
  *         - AES_OPMODE_ENCRYPT
  *         - AES_OPMODE_KEY_SCHEDULING
  *         - AES_OPMODE_DECRYPT
  *         - AES_OPMODE_KEY_SCHEDULING_DECRYPT
  * @retval none
  */
void aes_operate_mode_set(aes_operate_mode_type op_mode)
{
  AES->ctrl_bit.opr = op_mode;
}

/**
  * @brief  enable or disable the aes
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void aes_enable(confirm_state new_state)
{
  AES->ctrl_bit.aesen = new_state;
}

/**
  * @brief  enable or disable using dma when data in
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void aes_dma_in_enable(confirm_state new_state)
{
  AES->ctrl_bit.dmawe = new_state;
}

/**
  * @brief  enable or disable using dma when data out
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void aes_dma_out_enable(confirm_state new_state)
{
  AES->ctrl_bit.dmare = new_state;
}

/**
  * @brief  enable or disable the last block data
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void aes_last_block_enable(confirm_state new_state)
{
  AES->ctrl_bit.lst = new_state;
}

/**
  * @brief  enable or disable the specified aes interrupts
  * @param  aes_int
  *         this parameter can be any combination of the following values:
  *         - AES_RWEIE_INT
  *         - AES_PDIE_INT
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void aes_interrupt_enable(uint32_t aes_int, confirm_state new_state)
{
  if(new_state == TRUE)
  {
    AES->ctrl |= aes_int;
  }
  else if(new_state == FALSE)
  {
    AES->ctrl |= aes_int;
  }
}

/**
  * @brief  check whether the specified aes interrupt flag is set or not.
  * @param  flag
  *         this parameter can be one of the following values:
  *         - AES_PDFS_FLAG
  *         - AES_REFS_FLAG
  *         - AES_WEFS_FLAG
  * @retval flag_status (SET or RESET)
  */
flag_status aes_interrupt_flag_get(uint32_t flag)
{
  flag_status status = RESET;
  switch(flag)
  {
    case AES_PDFS_FLAG:
      if((AES->sts & flag) && (AES->ctrl_bit.pdie))
        status = SET;
      break;
    case AES_REFS_FLAG:
    case AES_WEFS_FLAG:
      if((AES->sts & flag) && (AES->ctrl_bit.rweie))
        status = SET;
      break;
    default:
      break;
  }
  return status;
}

/**
  * @brief  check whether the specified aes flag is set or not.
  * @param  flag
  *         this parameter can be one of the following values:
  *         - AES_PDFS_FLAG
  *         - AES_REFS_FLAG
  *         - AES_WEFS_FLAG
  *         - AES_PBS_FLAG
  *         - AES_NZDFS_FLAG
  * @retval flag_status (SET or RESET)
  */
flag_status aes_flag_get(uint32_t flag)
{
  if(AES->sts & flag)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  clear aes flag
  * @param  flag
  *         this parameter can be one of the following values:
  *         - AES_PDFS_FLAG
  *         - AES_REFS_FLAG
  *         - AES_WEFS_FLAG
  *         - AES_NZDFS_FLAG
  * @retval none
  */
void aes_flag_clear(uint32_t flag)
{
  switch(flag)
  {
    case AES_PDFS_FLAG:
      AES->fclr_bit.pdfc = 1;
      break;
    case AES_REFS_FLAG:
      AES->fclr_bit.refc = 1;
      break;
    case AES_WEFS_FLAG:
      AES->fclr_bit.wefc = 1;
      break;
    case AES_NZDFS_FLAG:
      AES->fclr_bit.nzdfc = 1;
      break;
    default:
      break;
  }
}

/**
  * @brief  aes process input data and return remaining data pointer
  * @param  input_ptr:
  *         - pointer to aes process input data(word alignment)
  * @retval pointer to remaining data
  */
void aes_data_input(uint32_t* input_ptr)
{
  AES->idt = input_ptr[0];
  AES->idt = input_ptr[1];
  AES->idt = input_ptr[2];
  AES->idt = input_ptr[3];
}

/**
  * @brief  aes store output data and return remaining data pointer
  * @param  output_ptr
  *         - pointer to aes store output data(word alignment)
  * @retval pointer to remaining data
  */
void aes_data_output(uint32_t* output_ptr)
{
  output_ptr[0] = AES->odt;
  output_ptr[1] = AES->odt;
  output_ptr[2] = AES->odt;
  output_ptr[3] = AES->odt;
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
