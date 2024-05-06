/**
  **************************************************************************
  * @file     at32a423_scfg.h
  * @brief    at32a423 system config header file
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
#ifndef __AT32A423_SCFG_H
#define __AT32A423_SCFG_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32a423.h"

/** @addtogroup AT32A423_periph_driver
  * @{
  */

/** @addtogroup SCFG
  * @{
  */

#define SCFG_REG(value)                  PERIPH_REG(SCFG_BASE, value)
#define SCFG_REG_BIT(value)              PERIPH_REG_BIT(value)

/** @defgroup SCFG_exported_types
  * @{
  */

/**
  * @brief scfg infrared modulation signal source selecting type
  */
typedef enum
{
  SCFG_IR_SOURCE_TMR10                   = 0x00  /* infrared signal source select tmr10 */
} scfg_ir_source_type;

/**
  * @brief scfg infrared output polarity selecting type
  */
typedef enum
{
  SCFG_IR_POLARITY_NO_AFFECTE            = 0x00, /* infrared output polarity no affecte */
  SCFG_IR_POLARITY_REVERSE               = 0x01  /* infrared output polarity reverse */
} scfg_ir_polarity_type;

/**
  * @brief scfg memory address mapping selecting type
  */
typedef enum
{
  SCFG_MEM_MAP_MAIN_MEMORY               = 0x00, /* 0x00000000 address mapping from main memory */
  SCFG_MEM_MAP_BOOT_MEMORY               = 0x01, /* 0x00000000 address mapping from boot memory */
  SCFG_MEM_MAP_INTERNAL_SRAM             = 0x03, /* 0x00000000 address mapping from internal sram */
} scfg_mem_map_type;

/**
  * @brief scfg pin source type
  */
typedef enum
{
  SCFG_PINS_SOURCE0                      = 0x00,
  SCFG_PINS_SOURCE1                      = 0x01,
  SCFG_PINS_SOURCE2                      = 0x02,
  SCFG_PINS_SOURCE3                      = 0x03,
  SCFG_PINS_SOURCE4                      = 0x04,
  SCFG_PINS_SOURCE5                      = 0x05,
  SCFG_PINS_SOURCE6                      = 0x06,
  SCFG_PINS_SOURCE7                      = 0x07,
  SCFG_PINS_SOURCE8                      = 0x08,
  SCFG_PINS_SOURCE9                      = 0x09,
  SCFG_PINS_SOURCE10                     = 0x0A,
  SCFG_PINS_SOURCE11                     = 0x0B,
  SCFG_PINS_SOURCE12                     = 0x0C,
  SCFG_PINS_SOURCE13                     = 0x0D,
  SCFG_PINS_SOURCE14                     = 0x0E,
  SCFG_PINS_SOURCE15                     = 0x0F
} scfg_pins_source_type;

/**
  * @brief gpio port source type
  */
typedef enum
{
  SCFG_PORT_SOURCE_GPIOA                 = 0x00,
  SCFG_PORT_SOURCE_GPIOB                 = 0x01,
  SCFG_PORT_SOURCE_GPIOC                 = 0x02,
  SCFG_PORT_SOURCE_GPIOD                 = 0x03,
  SCFG_PORT_SOURCE_GPIOE                 = 0x04,
  SCFG_PORT_SOURCE_GPIOF                 = 0x05,
  SCFG_PORT_SOURCE_GPIOG                 = 0x06,
  SCFG_PORT_SOURCE_GPIOH                 = 0x07
} scfg_port_source_type;

/**
  * @brief scfg i2s full duplex type
  */
typedef enum
{
  SCFG_FULL_DUPLEX_I2S_NONE              = 0x00, /* no i2s full duplex */
  SCFG_FULL_DUPLEX_I2S1_I2S3             = 0x01, /* i2s full duplex with i2s1 and i2s3 */
  SCFG_FULL_DUPLEX_I2S2_I2S3             = 0x02, /* i2s full duplex with i2s2 and i2s3 */
  SCFG_FULL_DUPLEX_I2S1_I2S2             = 0x03, /* i2s full duplex with i2s1 and i2s2 */
} scfg_i2s_type;

/**
  * @brief scfg ultra high sourcing/sinking strength pins type
  */
typedef enum
{
  SCFG_ULTRA_DRIVEN_PB9                  = MAKE_VALUE(0x2C, 1),
  SCFG_ULTRA_DRIVEN_PB8                  = MAKE_VALUE(0x2C, 3),
  SCFG_ULTRA_DRIVEN_PD12                 = MAKE_VALUE(0x2C, 5),
  SCFG_ULTRA_DRIVEN_PD13                 = MAKE_VALUE(0x2C, 6)
} scfg_ultra_driven_pins_type;

/**
  * @brief type define system config register all
  */
typedef struct
{
  /**
    * @brief scfg cfg1 register, offset:0x00
    */
  union
  {
    __IO uint32_t cfg1;
    struct
    {
      __IO uint32_t mem_map_sel          : 2; /* [1:0] */
      __IO uint32_t reserved1            : 3; /* [4:2] */
      __IO uint32_t ir_pol               : 1; /* [5] */
      __IO uint32_t ir_src_sel           : 2; /* [7:6] */
      __IO uint32_t reserved2            : 24;/* [31:8] */
    } cfg1_bit;
  };

  /**
    * @brief scfg cfg2 register, offset:0x04
    */
  union
  {
    __IO uint32_t cfg2;
    struct
    {
      __IO uint32_t lockup_lk            : 1; /* [0] */
      __IO uint32_t reserved1            : 1; /* [1] */
      __IO uint32_t pvm_lk               : 1; /* [2] */
      __IO uint32_t reserved2            : 27;/* [29:3] */
      __IO uint32_t i2s_fd               : 2; /* [31:30] */
    } cfg2_bit;
  };

  /**
    * @brief scfg exintc1 register, offset:0x08
    */
  union
  {
    __IO uint32_t exintc1;
    struct
    {
      __IO uint32_t exint0               : 4; /* [3:0] */
      __IO uint32_t exint1               : 4; /* [7:4] */
      __IO uint32_t exint2               : 4; /* [11:8] */
      __IO uint32_t exint3               : 4; /* [15:12] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } exintc1_bit;
  };

  /**
    * @brief scfg exintc2 register, offset:0x0C
    */
  union
  {
    __IO uint32_t exintc2;
    struct
    {
      __IO uint32_t exint4               : 4; /* [3:0] */
      __IO uint32_t exint5               : 4; /* [7:4] */
      __IO uint32_t exint6               : 4; /* [11:8] */
      __IO uint32_t exint7               : 4; /* [15:12] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } exintc2_bit;
  };

  /**
    * @brief scfg exintc3 register, offset:0x10
    */
  union
  {
    __IO uint32_t exintc3;
    struct
    {
      __IO uint32_t exint8               : 4; /* [3:0] */
      __IO uint32_t exint9               : 4; /* [7:4] */
      __IO uint32_t exint10              : 4; /* [11:8] */
      __IO uint32_t exint11              : 4; /* [15:12] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } exintc3_bit;
  };

  /**
    * @brief scfg exintc4 register, offset:0x14
    */
  union
  {
    __IO uint32_t exintc4;
    struct
    {
      __IO uint32_t exint12              : 4; /* [3:0] */
      __IO uint32_t exint13              : 4; /* [7:4] */
      __IO uint32_t exint14              : 4; /* [11:8] */
      __IO uint32_t exint15              : 4; /* [15:12] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } exintc4_bit;
  };

  /**
    * @brief crm reserved1 register, offset:0x18~0x28
    */
  __IO uint32_t reserved1[5];

  /**
    * @brief scfg uhdrv register, offset:0x2C
    */
  union
  {
    __IO uint32_t uhdrv;
    struct
    {
      __IO uint32_t reserved1            : 1; /* [0] */
      __IO uint32_t pb9_uh               : 1; /* [1] */
      __IO uint32_t reserved2            : 1; /* [2] */
      __IO uint32_t pb8_uh               : 1; /* [3] */
      __IO uint32_t reserved3            : 1; /* [4] */
      __IO uint32_t pd12_uh              : 1; /* [5] */
      __IO uint32_t pd13_uh              : 1; /* [6] */
      __IO uint32_t reserved4            : 25;/* [31:7] */
    } uhdrv_bit;
  };

} scfg_type;

/**
  * @}
  */

#define SCFG                             ((scfg_type *) SCFG_BASE)

/** @defgroup SCFG_exported_functions
  * @{
  */

void scfg_reset(void);
void scfg_infrared_config(scfg_ir_source_type source, scfg_ir_polarity_type polarity);
scfg_mem_map_type scfg_mem_map_get(void);
void scfg_i2s_full_duplex_config(scfg_i2s_type i2s_full_duplex);
void scfg_pvm_lock_enable(confirm_state new_state);
void scfg_lockup_enable(confirm_state new_state);
void scfg_exint_line_config(scfg_port_source_type port_source, scfg_pins_source_type pin_source);
void scfg_pins_ultra_driven_enable(scfg_ultra_driven_pins_type value, confirm_state new_state);

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
