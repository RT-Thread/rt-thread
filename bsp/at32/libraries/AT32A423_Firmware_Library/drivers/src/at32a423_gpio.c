/**
  **************************************************************************
  * @file     at32a423_gpio.c
  * @brief    contains all the functions for the gpio firmware library
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

#include "at32a423_conf.h"

/** @addtogroup AT32A423_periph_driver
  * @{
  */

/** @defgroup GPIO
  * @brief GPIO driver modules
  * @{
  */

#ifdef GPIO_MODULE_ENABLED

/** @defgroup GPIO_private_functions
  * @{
  */

/**
  * @brief  reset the gpio register
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @retval none
  */
void gpio_reset(gpio_type *gpio_x)
{
  if(gpio_x == GPIOA)
  {
    crm_periph_reset(CRM_GPIOA_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_GPIOA_PERIPH_RESET, FALSE);
  }
  else if(gpio_x == GPIOB)
  {
    crm_periph_reset(CRM_GPIOB_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_GPIOB_PERIPH_RESET, FALSE);
  }
  else if(gpio_x == GPIOC)
  {
    crm_periph_reset(CRM_GPIOC_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_GPIOC_PERIPH_RESET, FALSE);
  }
  else if(gpio_x == GPIOD)
  {
    crm_periph_reset(CRM_GPIOD_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_GPIOD_PERIPH_RESET, FALSE);
  }
  else if(gpio_x == GPIOE)
  {
    crm_periph_reset(CRM_GPIOE_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_GPIOE_PERIPH_RESET, FALSE);
  }
  else if(gpio_x == GPIOF)
  {
    crm_periph_reset(CRM_GPIOF_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_GPIOF_PERIPH_RESET, FALSE);
  }
}

/**
  * @brief  initialize the gpio peripheral.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @param  gpio_init_struct: pointer to gpio init structure.
  * @retval none
  */
void gpio_init(gpio_type *gpio_x, gpio_init_type *gpio_init_struct)
{
  uint16_t pinx_value, pin_index = 0;

  pinx_value = (uint16_t)gpio_init_struct->gpio_pins;

  while(pinx_value > 0)
  {
    if(pinx_value & 0x01)
    {
      gpio_x->cfgr  &= (uint32_t)~(0x03 << (pin_index * 2));
      gpio_x->cfgr  |= (uint32_t)(gpio_init_struct->gpio_mode << (pin_index * 2));

      gpio_x->omode &= (uint32_t)~(0x01 << (pin_index));
      gpio_x->omode |= (uint32_t)(gpio_init_struct->gpio_out_type << (pin_index));

      gpio_x->odrvr &= (uint32_t)~(0x03 << (pin_index * 2));
      gpio_x->odrvr |= (uint32_t)(gpio_init_struct->gpio_drive_strength << (pin_index * 2));

      gpio_x->pull  &= (uint32_t)~(0x03 << (pin_index * 2));
      gpio_x->pull  |= (uint32_t)(gpio_init_struct->gpio_pull << (pin_index * 2));
    }
    pinx_value >>= 1;
    pin_index++;
  }
}

/**
  * @brief  fill each gpio_init_type member with its default value.
  * @param  gpio_init_struct : pointer to a gpio_init_type structure which will be initialized.
  * @retval none
  */
void gpio_default_para_init(gpio_init_type *gpio_init_struct)
{
  /* reset gpio init structure parameters values */
  gpio_init_struct->gpio_pins  = GPIO_PINS_ALL;
  gpio_init_struct->gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct->gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct->gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct->gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
}

/**
  * @brief  read the specified input port pin.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @param  pins: gpio pin number
  *         this parameter can be one of the following values:
  *         - GPIO_PINS_0
  *         - GPIO_PINS_1
  *         - GPIO_PINS_2
  *         - GPIO_PINS_3
  *         - GPIO_PINS_4
  *         - GPIO_PINS_5
  *         - GPIO_PINS_6
  *         - GPIO_PINS_7
  *         - GPIO_PINS_8
  *         - GPIO_PINS_9
  *         - GPIO_PINS_10
  *         - GPIO_PINS_11
  *         - GPIO_PINS_12
  *         - GPIO_PINS_13
  *         - GPIO_PINS_14
  *         - GPIO_PINS_15
  * @retval flag_status (SET or RESET)
  */
flag_status gpio_input_data_bit_read(gpio_type *gpio_x, uint16_t pins)
{
  flag_status status = RESET;

  if(pins != (pins & gpio_x->idt))
  {
    status = RESET;
  }
  else
  {
    status = SET;
  }

  return status;
}

/**
  * @brief  read the specified gpio input data port.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @retval gpio input data port value.
  */
uint16_t gpio_input_data_read(gpio_type *gpio_x)
{
  return ((uint16_t)(gpio_x->idt));
}

/**
  * @brief  read the specified output port pin.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @param  pins: gpio pin number
  *         this parameter can be one of the following values:
  *         - GPIO_PINS_0
  *         - GPIO_PINS_1
  *         - GPIO_PINS_2
  *         - GPIO_PINS_3
  *         - GPIO_PINS_4
  *         - GPIO_PINS_5
  *         - GPIO_PINS_6
  *         - GPIO_PINS_7
  *         - GPIO_PINS_8
  *         - GPIO_PINS_9
  *         - GPIO_PINS_10
  *         - GPIO_PINS_11
  *         - GPIO_PINS_12
  *         - GPIO_PINS_13
  *         - GPIO_PINS_14
  *         - GPIO_PINS_15
  * @retval flag_status (SET or RESET)
  */
flag_status gpio_output_data_bit_read(gpio_type *gpio_x, uint16_t pins)
{
  flag_status status = RESET;

  if((gpio_x->odt & pins) != RESET)
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
  * @brief  read the specified gpio ouput data port.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @retval gpio input data port value.
  */
uint16_t gpio_output_data_read(gpio_type *gpio_x)
{
  return ((uint16_t)(gpio_x->odt));
}

/**
  * @brief  set the selected data port bits.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @param  pins: gpio pin number
  *         parameter can be any combination of gpio_pin_x, gpio_pin_x as following values:
  *         - GPIO_PINS_0
  *         - GPIO_PINS_1
  *         - GPIO_PINS_2
  *         - GPIO_PINS_3
  *         - GPIO_PINS_4
  *         - GPIO_PINS_5
  *         - GPIO_PINS_6
  *         - GPIO_PINS_7
  *         - GPIO_PINS_8
  *         - GPIO_PINS_9
  *         - GPIO_PINS_10
  *         - GPIO_PINS_11
  *         - GPIO_PINS_12
  *         - GPIO_PINS_13
  *         - GPIO_PINS_14
  *         - GPIO_PINS_15
  *         - GPIO_PINS_ALL
  * @retval none
  */
void gpio_bits_set(gpio_type *gpio_x, uint16_t pins)
{
  gpio_x->scr = pins;
}

/**
  * @brief  clear the selected data port bits.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @param  pins: gpio pin number
  *         parameter can be any combination of gpio_pin_x, gpio_pin_x as following values:
  *         - GPIO_PINS_0
  *         - GPIO_PINS_1
  *         - GPIO_PINS_2
  *         - GPIO_PINS_3
  *         - GPIO_PINS_4
  *         - GPIO_PINS_5
  *         - GPIO_PINS_6
  *         - GPIO_PINS_7
  *         - GPIO_PINS_8
  *         - GPIO_PINS_9
  *         - GPIO_PINS_10
  *         - GPIO_PINS_11
  *         - GPIO_PINS_12
  *         - GPIO_PINS_13
  *         - GPIO_PINS_14
  *         - GPIO_PINS_15
  *         - GPIO_PINS_ALL
  * @retval none
  */
void gpio_bits_reset(gpio_type *gpio_x, uint16_t pins)
{
  gpio_x->clr = pins;
}

/**
  * @brief  toggle the selected data port bits.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @param  pins: gpio pin number
  *         parameter can be any combination of gpio_pin_x, gpio_pin_x as following values:
  *         - GPIO_PINS_0
  *         - GPIO_PINS_1
  *         - GPIO_PINS_2
  *         - GPIO_PINS_3
  *         - GPIO_PINS_4
  *         - GPIO_PINS_5
  *         - GPIO_PINS_6
  *         - GPIO_PINS_7
  *         - GPIO_PINS_8
  *         - GPIO_PINS_9
  *         - GPIO_PINS_10
  *         - GPIO_PINS_11
  *         - GPIO_PINS_12
  *         - GPIO_PINS_13
  *         - GPIO_PINS_14
  *         - GPIO_PINS_15
  *         - GPIO_PINS_ALL
  * @retval none
  */
void gpio_bits_toggle(gpio_type *gpio_x, uint16_t pins)
{
  gpio_x->togr = pins;
}

/**
  * @brief  set or clear the selected data port bit.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @param  pins: gpio pin number
  *         parameter can be any combination of gpio_pin_x, gpio_pin_x as following values:
  *         - GPIO_PINS_0
  *         - GPIO_PINS_1
  *         - GPIO_PINS_2
  *         - GPIO_PINS_3
  *         - GPIO_PINS_4
  *         - GPIO_PINS_5
  *         - GPIO_PINS_6
  *         - GPIO_PINS_7
  *         - GPIO_PINS_8
  *         - GPIO_PINS_9
  *         - GPIO_PINS_10
  *         - GPIO_PINS_11
  *         - GPIO_PINS_12
  *         - GPIO_PINS_13
  *         - GPIO_PINS_14
  *         - GPIO_PINS_15
  *         - GPIO_PINS_ALL
  * @param  bit_state: specifies the value to be written to the selected bit (TRUE or FALSE).
  * @retval none
  */
void gpio_bits_write(gpio_type *gpio_x, uint16_t pins, confirm_state bit_state)
{
  if(bit_state != FALSE)
  {
    gpio_x->scr = pins;
  }
  else
  {
    gpio_x->clr = pins;
  }
}

/**
  * @brief  write data to the specified gpio data port.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @param  port_value: specifies the value to be written to the port output data register.
  * @retval none
  */
void gpio_port_write(gpio_type *gpio_x, uint16_t port_value)
{
  gpio_x->odt = port_value;
}

/**
  * @brief  write protect gpio pins configuration registers.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @param  pins: gpio pin number
  *         this parameter can be any combination of the following:
  *         - GPIO_PINS_0
  *         - GPIO_PINS_1
  *         - GPIO_PINS_2
  *         - GPIO_PINS_3
  *         - GPIO_PINS_4
  *         - GPIO_PINS_5
  *         - GPIO_PINS_6
  *         - GPIO_PINS_7
  *         - GPIO_PINS_8
  *         - GPIO_PINS_9
  *         - GPIO_PINS_10
  *         - GPIO_PINS_11
  *         - GPIO_PINS_12
  *         - GPIO_PINS_13
  *         - GPIO_PINS_14
  *         - GPIO_PINS_15
  *         - GPIO_PINS_ALL
  * @retval none
  */
void gpio_pin_wp_config(gpio_type *gpio_x, uint16_t pins)
{
  uint32_t temp = 0x00010000;

  temp |= pins;
  /* set wpen bit */
  gpio_x->wpr = temp;
  /* reset wpen bit */
  gpio_x->wpr =  pins;
  /* set wpen bit */
  gpio_x->wpr = temp;
  /* read wpen bit*/
  temp = gpio_x->wpr;
  /* read wpen bit*/
  temp = gpio_x->wpr;
}

/**
  * @brief  enable or disable gpio pins huge driven.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @param  pins: gpio pin number
  *         parameter can be any combination of gpio_pin_x, gpio_pin_x as following values:
  *         - GPIO_PINS_0
  *         - GPIO_PINS_1
  *         - GPIO_PINS_2
  *         - GPIO_PINS_3
  *         - GPIO_PINS_4
  *         - GPIO_PINS_5
  *         - GPIO_PINS_6
  *         - GPIO_PINS_7
  *         - GPIO_PINS_8
  *         - GPIO_PINS_9
  *         - GPIO_PINS_10
  *         - GPIO_PINS_11
  *         - GPIO_PINS_12
  *         - GPIO_PINS_13
  *         - GPIO_PINS_14
  *         - GPIO_PINS_15
  *         - GPIO_PINS_ALL
  * @param  new_state: new state of the slew rate.
  *         this parameter can be: true or false.
  * @retval none
  */
void gpio_pins_huge_driven_config(gpio_type *gpio_x, uint16_t pins, confirm_state new_state)
{
  if(new_state != FALSE)
  {
    gpio_x->hdrv |= pins;
  }
  else
  {
    gpio_x->hdrv &= ~pins;
  }
}

/**
  * @brief  configure the pin's muxing function.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF.
  * @param  gpio_pin_source: specifies the pin for the muxing function.
  *         this parameter can be one of the following values:
  *         - GPIO_PINS_SOURCE0
  *         - GPIO_PINS_SOURCE1
  *         - GPIO_PINS_SOURCE2
  *         - GPIO_PINS_SOURCE3
  *         - GPIO_PINS_SOURCE4
  *         - GPIO_PINS_SOURCE5
  *         - GPIO_PINS_SOURCE6
  *         - GPIO_PINS_SOURCE7
  *         - GPIO_PINS_SOURCE8
  *         - GPIO_PINS_SOURCE9
  *         - GPIO_PINS_SOURCE10
  *         - GPIO_PINS_SOURCE11
  *         - GPIO_PINS_SOURCE12
  *         - GPIO_PINS_SOURCE13
  *         - GPIO_PINS_SOURCE14
  *         - GPIO_PINS_SOURCE15
  * @param  gpio_mux: select the pin to used as muxing function.
  *         this parameter can be one of the following values:
  *         - GPIO_MUX_0
  *         - GPIO_MUX_1
  *         - GPIO_MUX_2
  *         - GPIO_MUX_3
  *         - GPIO_MUX_4
  *         - GPIO_MUX_5
  *         - GPIO_MUX_6
  *         - GPIO_MUX_7
  *         - GPIO_MUX_8
  *         - GPIO_MUX_9
  *         - GPIO_MUX_10
  *         - GPIO_MUX_11
  *         - GPIO_MUX_12
  *         - GPIO_MUX_13
  *         - GPIO_MUX_14
  *         - GPIO_MUX_15
  * @retval none
  */
void gpio_pin_mux_config(gpio_type *gpio_x, gpio_pins_source_type gpio_pin_source, gpio_mux_sel_type gpio_mux)
{
  uint32_t temp = 0x00;
  uint32_t temp_2 = 0x00;

  temp = ((uint32_t)(gpio_mux) << ((uint32_t)((uint32_t)gpio_pin_source & (uint32_t)0x07) * 4));
  if(gpio_pin_source >> 0x03)
  {
    gpio_x->muxh &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)gpio_pin_source & (uint32_t)0x07) * 4));
    temp_2 = gpio_x->muxh | temp;
    gpio_x->muxh = temp_2;
  }
  else
  {
    gpio_x->muxl &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)gpio_pin_source & (uint32_t)0x07) * 4));
    temp_2 = gpio_x->muxl | temp;
    gpio_x->muxl = temp_2;
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
