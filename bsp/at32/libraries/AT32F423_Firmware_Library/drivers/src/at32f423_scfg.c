/**
  **************************************************************************
  * @file     at32f423_scfg.c
  * @brief    contains all the functions for the system config firmware library
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

#include "at32f423_conf.h"

/** @addtogroup AT32F423_periph_driver
  * @{
  */

/** @defgroup SCFG
  * @brief SCFG driver modules
  * @{
  */

#ifdef SCFG_MODULE_ENABLED

/** @defgroup SCFG_private_functions
  * @{
  */

/**
  * @brief  scfg reset
  * @param  none
  * @retval none
  */
void scfg_reset(void)
{
  crm_periph_reset(CRM_SCFG_PERIPH_RESET, TRUE);
  crm_periph_reset(CRM_SCFG_PERIPH_RESET, FALSE);
}

/**
  * @brief  scfg infrared config
  * @param  source
  *         this parameter can be one of the following values:
  *         - SCFG_IR_SOURCE_TMR10
  *         - SCFG_IR_SOURCE_USART1
  *         - SCFG_IR_SOURCE_USART2
  * @param  polarity
  *         this parameter can be one of the following values:
  *         - SCFG_IR_POLARITY_NO_AFFECTE
  *         - SCFG_IR_POLARITY_REVERSE
  * @retval none
  */
void scfg_infrared_config(scfg_ir_source_type source, scfg_ir_polarity_type polarity)
{
  SCFG->cfg1_bit.ir_src_sel = source;
  SCFG->cfg1_bit.ir_pol = polarity;
}

/**
  * @brief  scfg memory address mapping get
  * @param  none
  * @retval return parameter can be one of the following values:
  *         - SCFG_MEM_MAP_MAIN_MEMORY
  *         - SCFG_MEM_MAP_BOOT_MEMORY
  *         - SCFG_MEM_MAP_INTERNAL_SRAM
  */
uint8_t scfg_mem_map_get(void)
{
  return (uint8_t)SCFG->cfg1_bit.mem_map_sel;
}

/**
  * @brief  i2s full duplex config.
  * @param  i2s_full_duplex:
  *         this parameter can be one of the following values:
  *         - SCFG_FULL_DUPLEX_I2S_NONE
  *         - SCFG_FULL_DUPLEX_I2S1_I2S3
  *         - SCFG_FULL_DUPLEX_I2S2_I2S3
  *         - SCFG_FULL_DUPLEX_I2S1_I2S2
  * @retval none
  */
void scfg_i2s_full_duplex_config(scfg_i2s_type i2s_full_duplex)
{
  SCFG->cfg2_bit.i2s_fd = i2s_full_duplex;
}

/**
  * @brief  scfg pvm lock enable.
  * @param  new_state (TRUE or FALSE)
  *         - TRUE   (pvm interrupt connect to the brake of TMR1/9/10/11/12/13/14 )
  *         - FALSE  (pvm interrupt not connect to the brake of TMR1/9/10/11/12/13/14 )
  * @retval none
  */
void scfg_pvm_lock_enable(confirm_state new_state)
{
  SCFG->cfg2_bit.pvm_lk = new_state;
}

/**
  * @brief  scfg cm4 lockup lock enable.
  * @param  new_state (TRUE or FALSE)
  *         - TRUE
  *         - FALSE
  * @retval none
  */
void scfg_lockup_enable(confirm_state new_state)
{
  SCFG->cfg2_bit.lockup_lk = new_state;
}

/**
  * @brief  select the gpio pin used as exint line.
  * @param  port_source:
  *         select the gpio port to be used as source for exint lines.
  *         this parameter can be one of the following values:
  *         - SCFG_PORT_SOURCE_GPIOA
  *         - SCFG_PORT_SOURCE_GPIOB
  *         - SCFG_PORT_SOURCE_GPIOC
  *         - SCFG_PORT_SOURCE_GPIOD
  *         - SCFG_PORT_SOURCE_GPIOE
  *         - SCFG_PORT_SOURCE_GPIOF
  * @param  pin_source:
  *         specifies the exint line to be configured.
  *         this parameter can be one of the following values:
  *         - SCFG_PINS_SOURCE0
  *         - SCFG_PINS_SOURCE1
  *         - SCFG_PINS_SOURCE2
  *         - SCFG_PINS_SOURCE3
  *         - SCFG_PINS_SOURCE4
  *         - SCFG_PINS_SOURCE5
  *         - SCFG_PINS_SOURCE6
  *         - SCFG_PINS_SOURCE7
  *         - SCFG_PINS_SOURCE8
  *         - SCFG_PINS_SOURCE9
  *         - SCFG_PINS_SOURCE10
  *         - SCFG_PINS_SOURCE11
  *         - SCFG_PINS_SOURCE12
  *         - SCFG_PINS_SOURCE13
  *         - SCFG_PINS_SOURCE14
  *         - SCFG_PINS_SOURCE15
  * @retval none
  */
void scfg_exint_line_config(scfg_port_source_type port_source, scfg_pins_source_type pin_source)
{
  uint32_t tmp = 0x00;
  tmp = ((uint32_t)0x0F) << (0x04 * (pin_source & (uint8_t)0x03));

  switch (pin_source >> 0x02)
  {
    case 0:
      SCFG->exintc1 &= ~tmp;
      SCFG->exintc1 |= (((uint32_t)port_source) << (0x04 * (pin_source & (uint8_t)0x03)));
      break;
    case 1:
      SCFG->exintc2 &= ~tmp;
      SCFG->exintc2 |= (((uint32_t)port_source) << (0x04 * (pin_source & (uint8_t)0x03)));
      break;
    case 2:
      SCFG->exintc3 &= ~tmp;
      SCFG->exintc3 |= (((uint32_t)port_source) << (0x04 * (pin_source & (uint8_t)0x03)));
      break;
    case 3:
      SCFG->exintc4 &= ~tmp;
      SCFG->exintc4 |= (((uint32_t)port_source) << (0x04 * (pin_source & (uint8_t)0x03)));
      break;
    default:
      break;
  }
}

/**
  * @brief  enable or disable gpio pins ultra driven.
  * @param  value:
  *         this parameter can be one of the following values:
  *         - SCFG_ULTRA_DRIVEN_PB9
  *         - SCFG_ULTRA_DRIVEN_PB8
  *         - SCFG_ULTRA_DRIVEN_PD12
  *         - SCFG_ULTRA_DRIVEN_PD13
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void scfg_pins_ultra_driven_enable(scfg_ultra_driven_pins_type value, confirm_state new_state)
{
  if(TRUE == new_state)
  {
    SCFG_REG(value) |= SCFG_REG_BIT(value);
  }
  else
  {
    SCFG_REG(value) &= ~(SCFG_REG_BIT(value));
  }
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
