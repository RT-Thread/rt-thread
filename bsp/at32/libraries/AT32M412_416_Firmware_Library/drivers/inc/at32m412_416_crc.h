/**
  **************************************************************************
  * @file     at32m412_416_crc.h
  * @brief    at32m412_416 crc header file
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

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32M412_416_CRC_H
#define __AT32M412_416_CRC_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32m412_416.h"

/** @addtogroup AT32M412_416_periph_driver
  * @{
  */

/** @addtogroup  CRC
  * @{
  */

/** @defgroup CRC_exported_types
  * @{
  */

/**
  * @brief crc reverse input data
  */
typedef enum
{
  CRC_REVERSE_INPUT_NO_AFFECTE           = 0x00, /*!< input data no reverse */
  CRC_REVERSE_INPUT_BY_BYTE              = 0x01, /*!< input data reverse by byte */
  CRC_REVERSE_INPUT_BY_HALFWORD          = 0x02, /*!< input data reverse by half word */
  CRC_REVERSE_INPUT_BY_WORD              = 0x03  /*!< input data reverse by word */
} crc_reverse_input_type;

/**
  * @brief crc reverse output data
  */
typedef enum
{
  CRC_REVERSE_OUTPUT_NO_AFFECTE          = 0x00, /*!< output data no reverse */
  CRC_REVERSE_OUTPUT_DATA                = 0x01  /*!< output data reverse by word */
} crc_reverse_output_type;

/**
  * @brief crc polynomial size
  */
typedef enum
{
  CRC_POLY_SIZE_32B                      = 0x00, /*!< polynomial size 32 bits */
  CRC_POLY_SIZE_16B                      = 0x01, /*!< polynomial size 16 bits */
  CRC_POLY_SIZE_8B                       = 0x02, /*!< polynomial size 8 bits */
  CRC_POLY_SIZE_7B                       = 0x03  /*!< polynomial size 7 bits */
} crc_poly_size_type;

/**
 * @brief type define crc register all
 */
typedef struct
{
  /**
    * @brief crc dt register, offset:0x00
    */
  union
  {
    __IO uint32_t dt;
    struct
    {
      __IO uint32_t dt                   : 32; /* [31:0] */
    } dt_bit;
  };

  /**
    * @brief crc cdt register, offset:0x04
    */
  union
  {
    __IO uint32_t cdt;
    struct
    {
      __IO uint32_t cdt                  : 8 ; /* [7:0] */
      __IO uint32_t reserved1            : 24 ;/* [31:8] */
    } cdt_bit;
  };

  /**
    * @brief crc ctrl register, offset:0x08
    */
  union
  {
    __IO uint32_t ctrl;
    struct
    {
      __IO uint32_t rst                  : 1 ; /* [0] */
      __IO uint32_t reserved1            : 2 ; /* [2:1] */
      __IO uint32_t poly_size            : 2 ; /* [4:3] */
      __IO uint32_t revid                : 2 ; /* [6:5] */
      __IO uint32_t revod                : 1 ; /* [7] */
      __IO uint32_t reserved2            : 24 ;/* [31:8] */
    } ctrl_bit;
  };

  /**
    * @brief crm reserved1 register, offset:0x0C
    */
  __IO uint32_t reserved1;

  /**
    * @brief crc idt register, offset:0x10
    */
  union
  {
    __IO uint32_t idt;
    struct
    {
      __IO uint32_t idt                  : 32; /* [31:0] */
    } idt_bit;
  };

  /**
    * @brief crc polynomial register, offset:0x14
    */
  union
  {
    __IO uint32_t poly;
    struct
    {
      __IO uint32_t poly                 : 32; /* [31:0] */
    } poly_bit;
  };

} crc_type;

/**
  * @}
  */

#define CRC                              ((crc_type *) CRC_BASE)

/** @defgroup CRC_exported_functions
  * @{
  */

void crc_data_reset(void);
uint32_t crc_one_word_calculate(uint32_t data);
uint32_t crc_block_calculate(uint32_t *pbuffer, uint32_t length);
uint32_t crc_data_get(void);
void crc_common_data_set(uint8_t cdt_value);
uint8_t crc_common_data_get(void);
void crc_init_data_set(uint32_t value);
void crc_reverse_input_data_set(crc_reverse_input_type value);
void crc_reverse_output_data_set(crc_reverse_output_type value);
void crc_poly_value_set(uint32_t value);
uint32_t crc_poly_value_get(void);
void crc_poly_size_set(crc_poly_size_type size);
crc_poly_size_type crc_poly_size_get(void);

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
