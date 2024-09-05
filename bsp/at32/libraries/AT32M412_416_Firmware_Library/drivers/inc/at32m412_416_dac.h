/**
  **************************************************************************
  * @file     at32F45x_dac.h
  * @brief    at32F45x dac header file
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
#ifndef __AT32M412_416_DAC_H
#define __AT32M412_416_DAC_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32m412_416.h"

/** @addtogroup AT32M412_416_periph_driver
  * @{
  */

/** @addtogroup DAC
  * @{
  */

#define DAC1_D1DMAUDRF                   ((uint32_t)(0x00002000))
#define DAC2_D2DMAUDRF                   ((uint32_t)(0x20000000))

/** @defgroup DAC_exported_types
  * @{
  */

/**
  * @brief dac select type
  */
typedef enum
{
  DAC1_SELECT                            = 0x01, /*!< dac1 select */
  DAC2_SELECT                            = 0x02  /*!< dac2 select */
} dac_select_type;

/**
  * @brief dac trigger type
  */
typedef enum
{
  DAC_TMR6_TRGOUT_EVENT                  = 0x00, /*!< dac trigger selection:timer6 trgout event */
  DAC_TMR3_TRGOUT_EVENT                  = 0x01, /*!< dac trigger selection:timer3 trgout event */
  DAC_TMR7_TRGOUT_EVENT                  = 0x02, /*!< dac trigger selection:timer7 trgout event */
  DAC_TMR9_TRGOUT_EVENT                  = 0x03, /*!< dac trigger selection:timer9 trgout event */
  DAC_TMR4_TRGOUT_EVENT                  = 0x05, /*!< dac trigger selection:timer4 trgout event */
  DAC_EXTERNAL_INTERRUPT_LINE_9          = 0x06, /*!< dac trigger selection:external line9 */
  DAC_SOFTWARE_TRIGGER                   = 0x07  /*!< dac trigger selection:software trigger */
} dac_trigger_type;

/**
  * @brief  dac reference voltage type
  */
typedef enum
{
  DAC_VDDA                               = 0x00, /*!<dac use vdda as reference voltage */
  DAC_VREF                               = 0x01  /*!<dac use vref as reference voltage */
} dac_reference_voltage_type;

/**
  * @brief type define dac register all
  */
typedef struct
{
  /**
    * @brief dac ctrl register, offset:0x00
    */
  union
  {
    __IO uint32_t ctrl;
    struct
    {
      __IO uint32_t d1en                 : 1; /* [0] */
      __IO uint32_t dac1_vref_sel        : 1; /* [1] */
      __IO uint32_t d1trgen              : 1; /* [2] */
      __IO uint32_t d1trgsel             : 3; /* [5:3] */
      __IO uint32_t reserved1            : 6; /* [11:6] */
      __IO uint32_t d1dmaen              : 1; /* [12] */
      __IO uint32_t d1dmaudrien          : 1; /* [13] */
      __IO uint32_t reserved2            : 2; /* [15:14] */
      __IO uint32_t d2en                 : 1; /* [16] */
      __IO uint32_t dac2_vref_sel        : 1; /* [17] */
      __IO uint32_t d2trgen              : 1; /* [18] */
      __IO uint32_t d2trgsel             : 3; /* [21:19] */
      __IO uint32_t reserved3            : 6; /* [27:22] */
      __IO uint32_t d2dmaen              : 1; /* [28] */
      __IO uint32_t d2dmaudrien          : 1; /* [29] */
      __IO uint32_t reserved4            : 2; /* [31:30] */
    } ctrl_bit;
  };

 /**
    * @brief dac swtrg register, offset:0x04
    */
  union
  {
    __IO uint32_t swtrg;
    struct
    {
      __IO uint32_t d1swtrg              : 1; /* [0] */
      __IO uint32_t d2swtrg              : 1; /* [1] */
      __IO uint32_t reserved1            : 30;/* [31:2] */
    } swtrg_bit;
  };

 /**
    * @brief dac d1dth register, offset:0x08
    */
  union
  {
    __IO uint32_t d1dth;
    struct
    {
      __IO uint32_t d1dth                : 6; /* [5:0] */
      __IO uint32_t reserved1            : 26;/* [31:6] */
    } d1dth_bit;
  };

 /**
    * @brief dac d2dth register, offset:0x0C
    */
  union
  {
    __IO uint32_t d2dth;
    struct
    {
      __IO uint32_t d2dth                : 6; /* [5:0] */
      __IO uint32_t reserved1            : 26;/* [31:6] */
    } d2dth_bit;
  };

 /**
    * @brief dac dddth register, offset:0x10
    */
  union
  {
    __IO uint32_t dddth;
    struct
    {
      __IO uint32_t d1dth                : 6; /* [5:0] */
      __IO uint32_t reserved1            : 2; /* [7:6] */
      __IO uint32_t d2dth                : 6; /* [13:8] */
      __IO uint32_t reserved2            : 18;/* [31:14] */
    } dddth_bit;
  };


 /**
    * @brief dac d1odt register, offset:0x14
    */
  union
  {
    __IO uint32_t d1odt;
    struct
    {
      __IO uint32_t d1odt                : 6; /* [5:0] */
      __IO uint32_t reserved1            : 26;/* [31:6] */
    } d1odt_bit;
  };

 /**
    * @brief dac d2odt register, offset:0x18
    */
  union
  {
    __IO uint32_t d2odt;
    struct
    {
      __IO uint32_t d2odt                : 6; /* [5:0] */
      __IO uint32_t reserved1            : 26;/* [31:6] */
    } d2odt_bit;
  };

 /**
    * @brief dac sts register, offset:0x1c
    */
  union
  {
    __IO uint32_t sts;
    struct
    {
      __IO uint32_t reserved1            : 13;/* [12:0] */
      __IO uint32_t d1dmaudrf            : 1; /* [13] */
      __IO uint32_t reserved2            : 15;/* [28:14] */
      __IO uint32_t d2dmaudrf            : 1; /* [29] */
      __IO uint32_t reserved3            : 2; /* [31:30] */
    } sts_bit;
  };
  
  /**
    * @brief dac sts register, offset:0x1c
    */
  union
  {
    __IO uint32_t outen;
    struct
    {
      __IO uint32_t d1_io                : 1; /* [0] */
      __IO uint32_t d2_io                : 1; /* [1] */
      __IO uint32_t reserved1            : 30;/* [31:2] */
    } outen_bit;
  };
} dac_type;

/**
  * @}
  */

#define DAC                              ((dac_type *) DAC_BASE)

/** @defgroup DAC_exported_functions
  * @{
  */

void dac_reset(void);
void dac_enable(dac_select_type dac_select, confirm_state new_state);
void dac_trigger_enable(dac_select_type dac_select, confirm_state new_state);
void dac_trigger_select(dac_select_type dac_select, dac_trigger_type dac_trigger_source);
void dac_software_trigger_generate(dac_select_type dac_select);
void dac_dual_software_trigger_generate(void);
void dac_dma_enable(dac_select_type dac_select, confirm_state new_state);
uint8_t dac_data_output_get(dac_select_type dac_select);
void dac_1_data_set(uint8_t dac1_data);
void dac_2_data_set(uint8_t dac2_data);
void dac_dual_data_set(uint8_t data1, uint8_t data2);
void dac_udr_enable(dac_select_type dac_select, confirm_state new_state);
flag_status dac_udr_flag_get(dac_select_type dac_select);
flag_status dac_udr_interrupt_flag_get(dac_select_type dac_select);
void dac_udr_flag_clear(dac_select_type dac_select);
void dac_reference_voltage_select(dac_select_type dac_select, dac_reference_voltage_type dac_reference_voltage);
void dac_output_enable(dac_select_type dac_select, confirm_state new_state);


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
