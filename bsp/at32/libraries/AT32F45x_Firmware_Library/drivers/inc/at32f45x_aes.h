/**
  **************************************************************************
  * @file     at32f45x_aes.h
  * @brief    at32f45x aes header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F45x_AES_H
#define __AT32F45x_AES_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f45x.h"

/** @addtogroup AT32F45x_periph_driver
  * @{
  */

/** @addtogroup AES
  * @{
  */

/** @defgroup AES_flags_definition
  * @brief aes flag
  * @{
  */

#define AES_PDFS_FLAG                    ((uint32_t)0x00000001) /*!< processing done flag */
#define AES_REFS_FLAG                    ((uint32_t)0x00000002) /*!< read error flag */
#define AES_WEFS_FLAG                    ((uint32_t)0x00000004) /*!< write error flag */
#define AES_PBS_FLAG                     ((uint32_t)0x00000008) /*!< busy flag status */
#define AES_NZDFS_FLAG                   ((uint32_t)0x00000010) /*!< non-zero dummy data processed flag */

/**
  * @}
  */

/** @defgroup AES_interrupts_definition
  * @brief aes interrupt
  * @{
  */

#define AES_PDIE_INT                     ((uint32_t)0x00000200) /*!< processing done interrupt */
#define AES_RWEIE_INT                    ((uint32_t)0x00000400) /*!< read and write error interrupt */

/**
  * @}
  */

/** @defgroup AES_exported_types
  * @{
  */

/**
  * @brief aes key length type
  */
typedef enum
{
  AES_KEY_LENGTH_128                     = 0, /*!< aes-128 */
  AES_KEY_LENGTH_192                     = 1, /*!< aes-192 */
  AES_KEY_LENGTH_256                     = 2  /*!< aes-256 */
} aes_key_length_type;

/**
  * @brief aes operate mode type
  */
typedef enum
{
  AES_OPMODE_ENCRYPT                     = 0, /*!< encryption */
  AES_OPMODE_KEY_SCHEDULING              = 1, /*!< key expansion */
  AES_OPMODE_DECRYPT                     = 2, /*!< decryption */
  AES_OPMODE_KEY_SCHEDULING_DECRYPT      = 3  /*!< key expansion and decryption */
} aes_operate_mode_type;

/**
  * @brief aes data swap type
  */
typedef enum
{
  AES_SWAP_TYPE_NONE                     = 0, /*!< no swap */
  AES_SWAP_TYPE_HALF_WROD                = 1, /*!< half-word exchange on word */
  AES_SWAP_TYPE_BYTE                     = 2, /*!< byte exchange on word */
  AES_SWAP_TYPE_BIT                      = 3  /*!< bit exchange on word */
} aes_data_swap_type;

/**
  * @brief aes chaining mode type
  */
typedef enum
{
  AES_CHMODE_ECB                         = 0, /*!< ecb */
  AES_CHMODE_CBC                         = 1, /*!< cbc */
  AES_CHMODE_CTR                         = 2, /*!< ctr */
  AES_CHMODE_GCM                         = 3, /*!< gcm */
  AES_CHMODE_CCM                         = 4  /*!< ccm */
} aes_chaining_mode_type;

/**
  * @brief aes gcm/ccm processing stage type
  */
typedef enum
{
  AES_PRC_INIT                           = 0, /*!< initial stage */
  AES_PRC_ASSOC                          = 1, /*!< assoc data stage */
  AES_PRC_DATA                           = 2, /*!< data stage */
  AES_PRC_TAG                            = 3  /*!< tag stage */
} aes_processing_stage_type;

/**
  * @brief aes initial structure type
  */
typedef struct
{
  aes_operate_mode_type                  operate_mode;  /*!< aes operation mode */
  aes_chaining_mode_type                 chaining_mode; /*!< aes chaining mode */
  aes_key_length_type                    key_len;       /*!< aes key length */
  uint32_t                               *key_buf;      /*!< aes key value */
  aes_data_swap_type                     data_swap_mode;/*!< aes data swap type */
} aes_init_type;

/**
  * @brief type define aes register all
  */
typedef struct
{
  /**
    * @brief aes ctrl register, offset:0x00
    */
  union
  {
    __IO uint32_t ctrl;
    struct
    {
      __IO uint32_t aesen                :1; /* [0] */
      __IO uint32_t swp                  :2; /* [2:1] */
      __IO uint32_t opr                  :2; /* [4:3] */
      __IO uint32_t chn                  :3; /* [7:5] */
      __IO uint32_t reserved1            :1; /* [8] */
      __IO uint32_t pdie                 :1; /* [9] */
      __IO uint32_t rweie                :1; /* [10] */
      __IO uint32_t dmawe                :1; /* [11] */
      __IO uint32_t dmare                :1; /* [12] */
      __IO uint32_t prc                  :2; /* [14:13] */
      __IO uint32_t reserved2            :1; /* [15] */
      __IO uint32_t reserved3            :1; /* [16] */
      __IO uint32_t kl                   :2; /* [18:17] */
      __IO uint32_t reserved4            :1; /* [19] */
      __IO uint32_t ndd                  :4; /* [23:20] */
      __IO uint32_t lst                  :1; /* [24] */
      __IO uint32_t reserved5            :7; /* [31:25] */
    } ctrl_bit;
  };

  /**
    * @brief aes sts register, offset:0x04
    */
  union
  {
    __IO uint32_t sts;
    struct
    {
      __IO uint32_t pdfs                 :1; /* [0] */
      __IO uint32_t refs                 :1; /* [1] */
      __IO uint32_t wefs                 :1; /* [2] */
      __IO uint32_t pbs                  :1; /* [3] */
      __IO uint32_t nzdfs                :1; /* [4] */
      __IO uint32_t reserved1            :27;/* [31:5] */
    } sts_bit;
  };

  /**
    * @brief aes idt register, offset:0x08
    */
  __IO uint32_t idt;

  /**
    * @brief aes odt register, offset:0x0C
    */
  __IO uint32_t odt;

  /**
    * @brief aes key0 register, offset:0x10
    */
  __IO uint32_t key0;

  /**
    * @brief aes key1 register, offset:0x14
    */
  __IO uint32_t key1;

  /**
    * @brief aes key2 register, offset:0x18
    */
  __IO uint32_t key2;

  /**
    * @brief aes key3 register, offset:0x1C
    */
  __IO uint32_t key3;

  /**
    * @brief aes iv0 register, offset:0x20
    */
  __IO uint32_t iv0;

  /**
    * @brief aes iv1 register, offset:0x24
    */
  __IO uint32_t iv1;

  /**
    * @brief aes iv2 register, offset:0x28
    */
  __IO uint32_t iv2;

  /**
    * @brief aes iv3 register, offset:0x2C
    */
  __IO uint32_t iv3;

  /**
    * @brief aes key4 register, offset:0x30
    */
  __IO uint32_t key4;

  /**
    * @brief aes key5 register, offset:0x34
    */
  __IO uint32_t key5;

  /**
    * @brief aes key6 register, offset:0x38
    */
  __IO uint32_t key6;

  /**
    * @brief aes key7 register, offset:0x3C
    */
  __IO uint32_t key7;

  /**
    * @brief aes si0 register, offset:0x40
    */
  __IO uint32_t si0;

  /**
    * @brief aes si1 register, offset:0x44
    */
  __IO uint32_t si1;

  /**
    * @brief aes si2 register, offset:0x48
    */
  __IO uint32_t si2;

  /**
    * @brief aes si3 register, offset:0x4C
    */
  __IO uint32_t si3;

  /**
    * @brief aes si4 register, offset:0x50
    */
  __IO uint32_t si4;

  /**
    * @brief aes si5 register, offset:0x54
    */
  __IO uint32_t si5;

  /**
    * @brief aes si6 register, offset:0x58
    */
  __IO uint32_t si6;

  /**
    * @brief aes si7 register, offset:0x5C
    */
  __IO uint32_t si7;

  /**
    * @brief aes fclr register, offset:0x60
    */
  union
  {
    __IO uint32_t fclr;
    struct
    {
      __IO uint32_t pdfc                 :1; /* [0] */
      __IO uint32_t refc                 :1; /* [1] */
      __IO uint32_t wefc                 :1; /* [2] */
      __IO uint32_t reserved1            :1; /* [3] */
      __IO uint32_t nzdfc                :1; /* [4] */
      __IO uint32_t reserved2            :27;/* [31:5] */
    } fclr_bit;
  };

} aes_type;

/**
  * @}
  */

#define AES                              ((aes_type*)AES_BASE)

/** @defgroup AES_exported_functions
  * @{
  */

void aes_reset(void);
void aes_key_set(aes_key_length_type aes_kl, uint32_t* aes_key);
void aes_iv_set(uint32_t* aes_iv);
void aes_dummy_data_num_set(uint8_t num);
void aes_processing_stage_set(aes_processing_stage_type prc_type);
void aes_default_para_init(aes_init_type* aes_init_struct);
void aes_init(aes_init_type* aes_init_struct);
void aes_suspend_info_init(void);
void aes_suspend_info_set(uint32_t* si_buf);
void aes_operate_mode_set(aes_operate_mode_type op_mode);
void aes_enable(confirm_state new_state);
void aes_dma_in_enable(confirm_state new_state);
void aes_dma_out_enable(confirm_state new_state);
void aes_last_block_enable(confirm_state new_state);
void aes_interrupt_enable(uint32_t aes_int, confirm_state new_state);
flag_status aes_interrupt_flag_get(uint32_t flag);
flag_status aes_flag_get(uint32_t flag);
void aes_flag_clear(uint32_t flag);
void aes_data_input(uint32_t* input_ptr);
void aes_data_output(uint32_t* output_ptr);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
