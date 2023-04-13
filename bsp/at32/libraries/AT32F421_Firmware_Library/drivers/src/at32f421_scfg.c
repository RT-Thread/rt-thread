/**
  **************************************************************************
  * @file     at32f421_scfg.c
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

#include "at32f421_conf.h"

/** @addtogroup AT32F421_periph_driver
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
  *         - SCFG_IR_SOURCE_TMR16
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
  return (uint8_t)SCFG->cfg1_bit.mem_map_sel ;
}

/**
  * @brief  scfg pa11/12 pin remap
  * @param  pin_remap
  *         this parameter can be one of the following values:
  *         - SCFG_PA11PA12_NO_REMAP
  *         - SCFG_PA11PA12_TO_PA9PA10
  * @retval none
  */
void scfg_pa11pa12_pin_remap(scfg_pa11pa12_remap_type pin_remap)
{
  SCFG->cfg1_bit.pa11_12_rmp = pin_remap;
}

/**
  * @brief  scfg adc dma channel remap
  * @param  dma_channel
  *         this parameter can be one of the following values:
  *         - SCFG_ADC_TO_DMA_CHANNEL_1
  *         - SCFG_ADC_TO_DMA_CHANNEL_2
  * @retval none
  */
void scfg_adc_dma_channel_remap(scfg_adc_dma_remap_type dma_channel)
{
  SCFG->cfg1_bit.adc_dma_rmp = dma_channel;
}

/**
  * @brief  scfg usart1 tx dma channel remap
  * @param  dma_channel
  *         this parameter can be one of the following values:
  *         - SCFG_USART1_TX_TO_DMA_CHANNEL_2
  *         - SCFG_USART1_TX_TO_DMA_CHANNEL_4
  * @retval none
  */
void scfg_usart1_tx_dma_channel_remap(scfg_usart1_tx_dma_remap_type dma_channel)
{
  SCFG->cfg1_bit.usart1_tx_dma_rmp = dma_channel;
}

/**
  * @brief  scfg usart1 rx dma channel remap
  * @param  dma_channel
  *         this parameter can be one of the following values:
  *         - SCFG_USART1_RX_TO_DMA_CHANNEL_3
  *         - SCFG_USART1_RX_TO_DMA_CHANNEL_5
  * @retval none
  */
void scfg_usart1_rx_dma_channel_remap(scfg_usart1_rx_dma_remap_type dma_channel)
{
  SCFG->cfg1_bit.usart1_rx_dma_rmp = dma_channel;
}

/**
  * @brief  scfg tmr16 dma channel remap
  * @param  dma_channel
  *         this parameter can be one of the following values:
  *         - SCFG_TMR16_TO_DMA_CHANNEL_3
  *         - SCFG_TMR16_TO_DMA_CHANNEL_4
  * @retval none
  */
void scfg_tmr16_dma_channel_remap(scfg_tmr16_dma_remap_type dma_channel)
{
  SCFG->cfg1_bit.tmr16_dma_rmp = dma_channel;
}

/**
  * @brief  scfg tmr17 dma channel remap
  * @param  dma_channel
  *         this parameter can be one of the following values:
  *         - SCFG_TMR17_TO_DMA_CHANNEL_1
  *         - SCFG_TMR17_TO_DMA_CHANNEL_2
  * @retval none
  */
void scfg_tmr17_dma_channel_remap(scfg_tmr17_dma_remap_type dma_channel)
{
  SCFG->cfg1_bit.tmr17_dma_rmp = dma_channel;
}

/**
  * @brief  select the gpio pin used as exint line.
  * @param  port_source:
  *         select the gpio port to be used as source for exint lines.
  *         this parameter can be one of the following values:
  *         - SCFG_PORT_SOURCE_GPIOA
  *         - SCFG_PORT_SOURCE_GPIOB
  *         - SCFG_PORT_SOURCE_GPIOC
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
  * @}
  */

#endif

/**
  * @}
  */

/**
  * @}
  */
