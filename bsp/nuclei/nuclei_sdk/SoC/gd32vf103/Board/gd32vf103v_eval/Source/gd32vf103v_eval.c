/*!
    \file    gd32vf103v_eval.c
    \brief   firmware functions to manage leds, keys, COM ports

    \version 2019-6-5, V1.0.0, demo for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "nuclei_sdk_hal.h"
#include "gd32vf103_usart.h"
#include "gd32vf103_gpio.h"
#include "gd32vf103_exti.h"

/* private variables */
static uint32_t GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT,
                                   LED3_GPIO_PORT, LED4_GPIO_PORT};
static uint32_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};

static rcu_periph_enum COM_CLK[COMn] = {GD32_COM0_CLK, GD32_COM1_CLK};
static uint32_t COM_TX_PIN[COMn] = {GD32_COM0_TX_PIN, GD32_COM1_TX_PIN};
static uint32_t COM_RX_PIN[COMn] = {GD32_COM0_RX_PIN, GD32_COM1_RX_PIN};
static uint32_t COM_GPIO_PORT[COMn] = {GD32_COM0_GPIO_PORT, GD32_COM1_GPIO_PORT};
static rcu_periph_enum COM_GPIO_CLK[COMn] = {GD32_COM0_GPIO_CLK, GD32_COM1_GPIO_CLK};

static rcu_periph_enum GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK,
                                         LED3_GPIO_CLK, LED4_GPIO_CLK};

static uint32_t KEY_PORT[KEYn] = {KEY_A_GPIO_PORT,
                                  KEY_B_GPIO_PORT,
                                  KEY_C_GPIO_PORT,
                                  KEY_D_GPIO_PORT,
                                  KEY_CET_GPIO_PORT};
static uint32_t KEY_PIN[KEYn] = {KEY_A_PIN,
                                 KEY_B_PIN,
                                 KEY_C_PIN,
                                 KEY_D_PIN,
                                 KEY_CET_PIN};
static rcu_periph_enum KEY_CLK[KEYn] = {KEY_A_GPIO_CLK,
                                        KEY_B_GPIO_CLK,
                                        KEY_C_GPIO_CLK,
                                        KEY_D_GPIO_CLK,
                                        KEY_CET_GPIO_CLK};
static exti_line_enum KEY_EXTI_LINE[KEYn] = {KEY_A_EXTI_LINE,
                                             KEY_B_EXTI_LINE,
                                             KEY_C_EXTI_LINE,
                                             KEY_D_EXTI_LINE,
                                             KEY_CET_EXTI_LINE};
static uint8_t KEY_PORT_SOURCE[KEYn] = {KEY_A_EXTI_PORT_SOURCE,
                                        KEY_B_EXTI_PORT_SOURCE,
                                        KEY_C_EXTI_PORT_SOURCE,
                                        KEY_D_EXTI_PORT_SOURCE,
                                        KEY_CET_EXTI_PORT_SOURCE};
static uint8_t KEY_PIN_SOURCE[KEYn] = {KEY_A_EXTI_PIN_SOURCE,
                                       KEY_B_EXTI_PIN_SOURCE,
                                       KEY_C_EXTI_PIN_SOURCE,
                                       KEY_D_EXTI_PIN_SOURCE,
                                       KEY_CET_EXTI_PIN_SOURCE};
static uint8_t KEY_IRQn[KEYn] = {KEY_A_EXTI_IRQn,
                                 KEY_B_EXTI_IRQn,
                                 KEY_C_EXTI_IRQn,
                                 KEY_D_EXTI_IRQn,
                                 KEY_CET_EXTI_IRQn};

/*!
    \brief      configure led GPIO
    \param[in]  lednum: specify the led to be configured
      \arg        LED1
      \arg        LED2
      \arg        LED3
      \arg        LED4
    \param[out] none
    \retval     none
*/
void gd_eval_led_init(led_typedef_enum lednum)
{
    /* enable the led clock */
    rcu_periph_clock_enable(GPIO_CLK[lednum]);
    /* configure led GPIO port */ 
    gpio_init(GPIO_PORT[lednum], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN[lednum]);

    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      turn on selected led
    \param[in]  lednum: specify the led to be turned on
      \arg        LED1
      \arg        LED2
      \arg        LED3
      \arg        LED4
    \param[out] none
    \retval     none
*/
void gd_eval_led_on(led_typedef_enum lednum)
{
    GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      turn off selected led
    \param[in]  lednum: specify the led to be turned off
      \arg        LED1
      \arg        LED2
      \arg        LED3
      \arg        LED4
    \param[out] none
    \retval     none
*/
void gd_eval_led_off(led_typedef_enum lednum)
{
    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      toggle selected led
    \param[in]  lednum: specify the led to be toggled
      \arg        LED1
      \arg        LED2
      \arg        LED3
      \arg        LED4
    \param[out] none
    \retval     none
*/
void gd_eval_led_toggle(led_typedef_enum lednum)
{
    gpio_bit_write(GPIO_PORT[lednum], GPIO_PIN[lednum], 
        (bit_status)(1-gpio_input_bit_get(GPIO_PORT[lednum], GPIO_PIN[lednum])));
}

/*!
    \brief      configure key
    \param[in]  key_num: specify the key to be configured
      \arg        KEY_A: wakeup key
      \arg        KEY_B: tamper key
      \arg        KEY_C: user key
      \arg        KEY_D: user key
      \arg        KEY_CET: user key
    \param[in]  key_mode: specify button mode
      \arg        KEY_MODE_GPIO: key will be used as simple IO
      \arg        KEY_MODE_EXTI: key will be connected to EXTI line with interrupt
    \param[out] none
    \retval     none
*/

void gd_eval_key_init(key_typedef_enum keynum, keymode_typedef_enum key_mode)
{
    ECLIC_ClearPendingIRQ(KEY_IRQn[keynum]);	
    /* enable the key clock */
    rcu_periph_clock_enable(KEY_CLK[keynum]);
    rcu_periph_clock_enable(RCU_AF);

    /* configure button pin as input */
    gpio_init(KEY_PORT[keynum], GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, KEY_PIN[keynum]);

    if (key_mode == KEY_MODE_EXTI) {
        /* enable and set key EXTI interrupt to the lowest priority */
	ECLIC_EnableIRQ(KEY_IRQn[keynum]);
        ECLIC_SetLevelIRQ(KEY_IRQn[keynum],1);
        ECLIC_SetPriorityIRQ(KEY_IRQn[keynum],1);	

        /* connect key EXTI line to key GPIO pin */
        gpio_exti_source_select(KEY_PORT_SOURCE[keynum], KEY_PIN_SOURCE[keynum]);

        /* configure key EXTI line */
        exti_init(KEY_EXTI_LINE[keynum], EXTI_INTERRUPT, EXTI_TRIG_FALLING);
        exti_interrupt_flag_clear(KEY_EXTI_LINE[keynum]);
    }
}

/*!
    \brief      return the selected key state
    \param[in]  key: specify the key to be checked
      \arg        KEY_A: wakeup key
      \arg        KEY_B: tamper key
      \arg        KEY_C: user key
      \arg        KEY_D: user key
      \arg        KEY_CET: user key
    \param[out] none
    \retval     the key's GPIO pin value
*/
uint8_t gd_eval_key_state_get(key_typedef_enum key)
{
    return gpio_input_bit_get(KEY_PORT[key], KEY_PIN[key]);
}

/*!
    \brief      configure COM port
    \param[in]  com: COM on the board
      \arg        GD32_COM0: COM0 on the board
      \arg        GD32_COM1: COM1 on the board
    \param[out] none
    \retval     none
*/
void gd_com_init(uint32_t com)
{
    uint32_t com_id = 0U;
    if(GD32_COM0 == com){
        com_id = 0U;
    }else if(GD32_COM1 == com){
        com_id = 1U;
    }
    
    /* enable GPIO clock */
    rcu_periph_clock_enable(COM_GPIO_CLK[com_id]);

    /* enable USART clock */
    rcu_periph_clock_enable(COM_CLK[com_id]);

    /* connect port to USARTx_Tx */
    gpio_init(COM_GPIO_PORT[com_id], GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, COM_TX_PIN[com_id]);

    /* connect port to USARTx_Rx */
    gpio_init(COM_GPIO_PORT[com_id], GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, COM_RX_PIN[com_id]);

    /* USART configure */
    usart_deinit(com);
    usart_baudrate_set(com, 115200U);
    usart_word_length_set(com, USART_WL_8BIT);
    usart_stop_bit_set(com, USART_STB_1BIT);
    usart_parity_config(com, USART_PM_NONE);
    usart_hardware_flow_rts_config(com, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(com, USART_CTS_DISABLE);
    usart_receive_config(com, USART_RECEIVE_ENABLE);
    usart_transmit_config(com, USART_TRANSMIT_ENABLE);
    usart_enable(com);
}
