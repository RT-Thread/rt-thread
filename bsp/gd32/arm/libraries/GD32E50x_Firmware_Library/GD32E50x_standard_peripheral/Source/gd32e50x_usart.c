/*!
    \file    gd32e50x_usart.c
    \brief   USART driver

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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


#include "gd32e50x_usart.h"

/* USART register bit offset */
#define GP_GUAT_OFFSET            ((uint32_t)8U)       /* bit offset of GUAT in USART_GP */
#define CTL2_SCRTNUM_OFFSET       ((uint32_t)17U)       /* bit offset of SCRTNUM in USART_CTL2 */
#define CTL3_SCRTNUM_OFFSET       ((uint32_t)1U)       /* bit offset of SCRTNUM in USART_CTL3 */
#define RT_BL_OFFSET              ((uint32_t)24U)      /* bit offset of BL in USART_RT */

/*!
    \brief      reset USART/UART
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_deinit(uint32_t usart_periph)
{
    switch(usart_periph)
    {
    case USART0:
        rcu_periph_reset_enable(RCU_USART0RST);
        rcu_periph_reset_disable(RCU_USART0RST);
        break;
    case USART1:
        rcu_periph_reset_enable(RCU_USART1RST);
        rcu_periph_reset_disable(RCU_USART1RST);
        break;
    case USART2:
        rcu_periph_reset_enable(RCU_USART2RST);
        rcu_periph_reset_disable(RCU_USART2RST);
        break;
    case USART5:
        rcu_periph_reset_enable(RCU_USART5RST);
        rcu_periph_reset_disable(RCU_USART5RST);
        break;
    case UART3:
        rcu_periph_reset_enable(RCU_UART3RST);
        rcu_periph_reset_disable(RCU_UART3RST);
        break;
    case UART4:
        rcu_periph_reset_enable(RCU_UART4RST);
        rcu_periph_reset_disable(RCU_UART4RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure USART baud rate value
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  baudval: baud rate value
    \param[out] none
    \retval     none
*/
void usart_baudrate_set(uint32_t usart_periph, uint32_t baudval)
{
    uint32_t uclk=0U, intdiv=0U, fradiv=0U, udiv=0U;
    switch(usart_periph)
    {
         /* get clock frequency */
    case USART0:
         uclk=rcu_clock_freq_get(CK_APB2);
         break;
    case USART5:
         uclk=rcu_clock_freq_get(CK_USART);
         break;
    case USART1:
         uclk=rcu_clock_freq_get(CK_APB1);
         break;
    case USART2:
         uclk=rcu_clock_freq_get(CK_APB1);
         break;
    case UART3:
         uclk=rcu_clock_freq_get(CK_APB1);
         break;
    case UART4:
         uclk=rcu_clock_freq_get(CK_APB1);
         break;
    default:
         break;
    }

    if(USART5 == usart_periph)
    {
        /* configure USART5 baud rate value */
        if(USART5_CTL0(usart_periph) & USART5_CTL0_OVSMOD)
        {
            /* when oversampling by 8, configure the value of USART_BAUD */
            udiv = ((2U*uclk) + baudval/2U)/baudval;
            intdiv = udiv & 0x0000fff0U;
            fradiv = (udiv>>1) & 0x00000007U;
        }else{
            /* when oversampling by 16, configure the value of USART_BAUD */
            udiv = (uclk+baudval/2U)/baudval;
            intdiv = udiv & 0x0000fff0U;
            fradiv = udiv & 0x0000000fU;
        }
        USART5_BAUD(usart_periph) = ((USART5_BAUD_FRADIV | USART5_BAUD_INTDIV) & (intdiv | fradiv));
    }else{
        /* configure USARTx(x=0,1,2)/UARTx(x=3,4) baud rate value */
        if(USART_CTL0(usart_periph) & USART_CTL0_OVSMOD)
        {
            /* when oversampling by 8, configure the value of USART_BAUD */
            udiv = ((2U*uclk) + baudval/2U)/baudval;
            intdiv = udiv & 0x0000fff0U;
            fradiv = (udiv>>1) & 0x00000007U;
        }else{
            /* when oversampling by 16, configure the value of USART_BAUD */
            udiv = (uclk+baudval/2U)/baudval;
            intdiv = udiv & 0x0000fff0U;
            fradiv = udiv & 0x0000000fU;
            }
        USART_BAUD(usart_periph) = ((USART_BAUD_FRADIV | USART_BAUD_INTDIV) & (intdiv | fradiv));
    }
}

/*!
    \brief     configure USART parity function
    \param[in] usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in] paritycfg: configure USART parity
               only one parameter can be selected which is shown as below:
      \arg       USART_PM_NONE: no parity
      \arg       USART_PM_EVEN: even parity
      \arg       USART_PM_ODD:  odd parity
    \param[out] none
    \retval     none
*/
void usart_parity_config(uint32_t usart_periph, uint32_t paritycfg)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* clear USART5_CTL0 PM,PCEN Bits */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_PM | USART5_CTL0_PCEN);
        /* configure USART5 parity mode */
        USART5_CTL0(usart_periph) |= ((USART5_CTL0_PM | USART5_CTL0_PCEN) & paritycfg);
    }else{
        /* clear USART_CTL0 PM,PCEN Bits */
        USART_CTL0(usart_periph) &= ~(USART_CTL0_PM | USART_CTL0_PCEN);
        /* configure USARTx(x=0,1,2)/UARTx(x=3,4) parity mode */
        USART_CTL0(usart_periph) |= ((USART_CTL0_PM | USART_CTL0_PCEN) & paritycfg);
    }
}

/*!
    \brief     configure USART word length
    \param[in] usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in] wlen: USART word length configure
               only one parameter can be selected which is shown as below:
      \arg       USART_WL_8BIT: 8 bits
      \arg       USART_WL_9BIT: 9 bits
    \param[out] none
    \retval     none
*/
void usart_word_length_set(uint32_t usart_periph, uint32_t wlen)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* clear USART5_CTL0 WL bit */
        USART5_CTL0(usart_periph) &= ~USART5_CTL0_WL;
        /* configure USART word length */
        USART5_CTL0(usart_periph) |= (USART5_CTL0_WL & wlen);
    }else{
        /* clear USART_CTL0 WL bit */
        USART_CTL0(usart_periph) &= ~USART_CTL0_WL;
        /* configure USARTx(x=0,1,2)/UARTx(x=3,4) word length */
        USART_CTL0(usart_periph) |= (USART_CTL0_WL & wlen);
    }
}

/*!
    \brief     configure USART stop bit length
    \param[in] usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in] stblen: USART stop bit configure
               only one parameter can be selected which is shown as below:
      \arg       USART_STB_1BIT:   1 bit
      \arg       USART_STB_0_5BIT: 0.5 bit(not available for UARTx(x=3,4,6,7))
      \arg       USART_STB_2BIT:   2 bits
      \arg       USART_STB_1_5BIT: 1.5 bits(not available for UARTx(x=3,4,6,7))
    \param[out] none
    \retval     none
*/
void usart_stop_bit_set(uint32_t usart_periph, uint32_t stblen)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* clear USART5_CTL1 STB bits */
        USART5_CTL1(usart_periph) &= ~USART5_CTL1_STB;
        /* configure USART stop bits */
        USART5_CTL1(usart_periph) |= (USART5_CTL1_STB & stblen);
    }else{
        /* clear USART_CTL1 STB bits */
        USART_CTL1(usart_periph) &= ~USART_CTL1_STB;
        /* configure USARTx(x=0,1,2)/UARTx(x=3,4) stop bits */
        USART_CTL1(usart_periph) |= (USART_CTL1_STB & stblen);
    }
}

/*!
    \brief      enable USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_enable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* enable USART5 */
        USART5_CTL0(usart_periph) |= USART5_CTL0_UEN;
    }else{
        /* enable USARTx(x=0,1,2)/UARTx(x=3,4) */
        USART_CTL0(usart_periph) |= USART_CTL0_UEN;
    }
}

/*!
    \brief     disable USART
    \param[in] usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_disable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
    }else{
        /* disable USARTx(x=0,1,2)/UARTx(x=3,4) */
        USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    }
}

/*!
    \brief      configure USART transmitter
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  txconfig: enable or disable USART transmitter
                only one parameter can be selected which is shown as below:
      \arg        USART_TRANSMIT_ENABLE: enable USART transmission
      \arg        USART_TRANSMIT_DISABLE: enable USART transmission
    \param[out] none
    \retval     none
*/
void usart_transmit_config(uint32_t usart_periph, uint32_t txconfig)
{
    uint32_t ctl = 0U;

    if(USART5 == usart_periph)
    {
        ctl = USART5_CTL0(usart_periph);
        ctl &= ~USART5_CTL0_TEN;
        ctl |= (USART5_CTL0_TEN & txconfig);
        /* configure USART5 transfer mode */
        USART5_CTL0(usart_periph) = ctl;
    }else{
        ctl = USART_CTL0(usart_periph);
        ctl &= ~USART_CTL0_TEN;
        ctl |= (USART_CTL0_TEN & txconfig);
        /* configure USARTx(x=0,1,2)/UARTx(x=3,4) transfer mode */
        USART_CTL0(usart_periph) = ctl;
    }
}

/*!
    \brief      configure USART receiver
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  rxconfig: enable or disable USART receiver
                only one parameter can be selected which is shown as below:
      \arg        USART_RECEIVE_ENABLE: enable USART reception
      \arg        USART_RECEIVE_DISABLE: disable USART reception
    \param[out] none
    \retval     none
*/
void usart_receive_config(uint32_t usart_periph, uint32_t rxconfig)
{
    uint32_t ctl = 0U;

    if(USART5 == usart_periph)
    {
        ctl = USART5_CTL0(usart_periph);
        ctl &= ~USART5_CTL0_REN;
        ctl |= (USART5_CTL0_REN & rxconfig);
        /* configure USART5 receive mode */
        USART5_CTL0(usart_periph) = ctl;
    }else{
        ctl = USART_CTL0(usart_periph);
        ctl &= ~USART_CTL0_REN;
        ctl |= (USART_CTL0_REN & rxconfig);
        /* configure USARTx(x=0,1,2)/UARTx(x=3,4) receive mode */
        USART_CTL0(usart_periph) = ctl;
    }
}

/*!
    \brief      configure the USART oversample mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  oversamp: oversample value
                only one parameter can be selected which is shown as below:
      \arg        USART_OVSMOD_8: 8 bits
      \arg        USART_OVSMOD_16: 16 bits
    \param[out] none
    \retval     none
*/
void usart_oversample_config(uint32_t usart_periph, uint32_t oversamp)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* clear OVSMOD bit */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_OVSMOD);
        /* configure the USART5 oversample mode */
        USART5_CTL0(usart_periph) |= (USART5_CTL0_OVSMOD & oversamp);
    }else{
        /* clear OVSMOD bit */
        USART_CTL0(usart_periph) &= ~(USART_CTL0_OVSMOD);
        /* configure the USARTx(x=0,1,2)/UARTx(x=3,4) oversample mode */
        USART_CTL0(usart_periph) |= (USART_CTL0_OVSMOD & oversamp);
    }
}

/*!
    \brief      configure sample bit method
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  obsm: sample bit
                only one parameter can be selected which is shown as below:
      \arg        USART_OSB_1bit: 1 bit
      \arg        USART_OSB_3bit: 3 bits
    \param[out] none
    \retval     none
*/
void usart_sample_bit_config(uint32_t usart_periph, uint32_t obsm)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* clear USART5 OSB bit */
        USART5_CTL2(usart_periph) &= ~(USART5_CTL2_OSB);
        /* configure USART5 sample bit method */
        USART5_CTL2(usart_periph) |= (USART5_CTL2_OSB & obsm);
    }else{
        USART_CTL2(usart_periph) &= ~(USART_CTL2_OSB);
        /* configure USARTx(x=0,1,2)/UARTx(x=3,4) sample bit method */
        USART_CTL2(usart_periph) |= (USART_CTL2_OSB & obsm);
    }
}

/*!
    \brief      enable receiver timeout of USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_receiver_timeout_enable(uint32_t usart_periph)
{
    if(USART5 ==usart_periph)
    {
        /* enable receiver timeout of USART5 */
        USART5_CTL1(usart_periph) |= USART5_CTL1_RTEN;
    }else{
        /* enable receiver timeout of USARTx(x=0,1,2) */
        USART_CTL3(usart_periph) |= USART_CTL3_RTEN;
    }
}

/*!
    \brief      disable receiver timeout of USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_receiver_timeout_disable(uint32_t usart_periph)
{
    if(USART5 ==usart_periph)
    {
        /* disable receiver timeout of USART5 */
        USART5_CTL1(usart_periph) &= ~USART5_CTL1_RTEN;
    }else{
        /* disable receiver timeout of USARTx(x=0,1,2) */
        USART_CTL3(usart_periph) &= ~(USART_CTL3_RTEN);
    }
}

/*!
    \brief      configure the receiver timeout threshold of USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  rtimeout: 0x00000000-0x00FFFFFF
    \param[out] none
    \retval     none
*/
void usart_receiver_timeout_threshold_config(uint32_t usart_periph, uint32_t rtimeout)
{
    if(USART5 == usart_periph)
    {
        USART5_RT(usart_periph) &= ~(USART5_RT_RT);
        /* configure USART5 receiver timeout threshold */
        USART5_RT(usart_periph) |= (USART5_RT_RT & rtimeout);
    }else{
        USART_RT(usart_periph) &= ~(USART_RT_RT);
        /* configure USARTx(x=0,1,2) receiver timeout threshold */
        USART_RT(usart_periph) |= (USART_RT_RT & rtimeout);
    }
}

/*!
    \brief      USART transmit data function
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  data: data of transmission
    \param[out] none
    \retval     none
*/
void usart_data_transmit(uint32_t usart_periph, uint16_t data)
{
    if(USART5 == usart_periph)
    {
        /* USART5 transmit data */
        USART5_TDATA(usart_periph) = USART5_TDATA_TDATA & (uint32_t)data;
    }else{
        /* USARTx(x=0,1,2)/UARTx(x=3,4) transmit data */
        USART_DATA(usart_periph) = USART_DATA_DATA & (uint32_t)data;
    }
}

/*!
    \brief      USART receive data function
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     data of received
*/
uint16_t usart_data_receive(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* USART5 receive data */
        return (uint16_t)(GET_BITS(USART5_RDATA(usart_periph), 0U, 8U));
    }else{
        /* USARTx(x=0,1,2)/UARTx(x=3,4) receive data */
       return (uint16_t)(GET_BITS(USART_DATA(usart_periph), 0U, 8U));
    }
}

/*!
    \brief      enable mute mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_mute_mode_enable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* enable USART5 mute mode */
        USART5_CTL0(usart_periph) |= USART5_CTL0_MEN;
    }else{
        /* enable USARTx(x=0,1,2)/UARTx(x=3,4) mute mode */
        USART_CTL0(usart_periph) |= USART_CTL0_RWU;
    }
}

/*!
    \brief      disable mute mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_mute_mode_disable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 mute mode */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_MEN);
    }else{
        /* disable USARTx(x=0,1,2)/UARTx(x=3,4) mute mode */
        USART_CTL0(usart_periph) &= ~(USART_CTL0_RWU);
    }
}

/*!
    \brief      configure wakeup method in mute mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  wmethod: two method be used to enter or exit the mute mode
                only one parameter can be selected which is shown as below:
      \arg        USART_WM_IDLE: idle line
      \arg        USART_WM_ADDR: address mask
    \param[out] none
    \retval     none
*/
void usart_mute_mode_wakeup_config(uint32_t usart_periph, uint32_t wmethod)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* clear USART5 WM bit */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_WM);
        /* configure USART5 wakeup method in mute mode */
        USART5_CTL0(usart_periph) |= (USART5_CTL0_WM & wmethod);
    }else{
        /* clear USARTx(x=0,1,2)/UARTx(x=3,4) WM bit */
        USART_CTL0(usart_periph) &= ~(USART_CTL0_WM);
        /* configure USARTx(x=0,1,2)/UARTx(x=3,4) wakeup method in mute mode */
        USART_CTL0(usart_periph) |= (USART_CTL0_WM & wmethod);
    }
}

/*!
    \brief      enable LIN mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_lin_mode_enable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* enable USART5 LIN mode */
        USART5_CTL1(usart_periph) |= USART5_CTL1_LMEN;
    }else{
        /* enable USARTx(x=0,1,2)/UARTx(x=3,4) LIN mode */
        USART_CTL1(usart_periph) |= USART_CTL1_LMEN;
    }
}

/*!
    \brief      disable LIN mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_lin_mode_disable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* disable USART5 LIN mode */
        USART5_CTL1(usart_periph) &= ~(USART5_CTL1_LMEN);
    }else{
        /* disable USARTx(x=0,1,2)/UARTx(x=3,4) LIN mode */
        USART_CTL1(usart_periph) &= ~(USART_CTL1_LMEN);
    }
}

/*!
    \brief      configure lin break frame length
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  lblen: lin break frame length
                only one parameter can be selected which is shown as below:
      \arg        USART_LBLEN_10B: 10 bits
      \arg        USART_LBLEN_11B: 11 bits
    \param[out] none
    \retval     none
*/
void usart_lin_break_detection_length_config(uint32_t usart_periph, uint32_t lblen)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);

        USART5_CTL1(usart_periph) &= ~(USART5_CTL1_LBLEN);
        /* configure USART5 lin brek frame length */
        USART5_CTL1(usart_periph) |= USART5_CTL1_LBLEN & (lblen);
    }else{
        USART_CTL1(usart_periph) &= ~(USART_CTL1_LBLEN);
        /* configure USARTx(x=0,1,2)/UARTx(x=3,4) lin brek frame length */
        USART_CTL1(usart_periph) |= (USART_CTL1_LBLEN & lblen);
    }
}

/*!
    \brief      enable half duplex mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_halfduplex_enable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* enable USART5 half duplex mode */
        USART5_CTL2(usart_periph) |= (USART5_CTL2_HDEN);
    }else{
        /* enable USARTx(x=0,1,2)/UARTx(x=3,4) half duplex mode */
        USART_CTL2(usart_periph) |= USART_CTL2_HDEN;
    }
}

/*!
    \brief      disable half duplex mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_halfduplex_disable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* disable USART5 half duplex mode */
        USART5_CTL2(usart_periph) &= ~(USART5_CTL2_HDEN);
    }else{
        /* disable USARTx(x=0,1,2)/UARTx(x=3,4) half duplex mode */
        USART_CTL2(usart_periph) &= ~(USART_CTL2_HDEN);
    }
}

/*!
    \brief      enable CK pin in synchronous mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_synchronous_clock_enable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* enable USART5 CK pin in synchronous mode */
        USART5_CTL1(usart_periph) |= USART5_CTL1_CKEN;
    }else{
        /* enable USARTx(x=0,1,2) CK pin in synchronous mode */
        USART_CTL1(usart_periph) |= USART_CTL1_CKEN;
    }
}

/*!
    \brief      disable CK pin in synchronous mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_synchronous_clock_disable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* disable USART5 CK pin in synchronous mode */
        USART5_CTL1(usart_periph) &= ~(USART5_CTL1_CKEN);
    }else{
        /* disable USARTx(x=0,1,2) CK pin in synchronous mode */
        USART_CTL1(usart_periph) &= ~(USART_CTL1_CKEN);
    }
}

/*!
    \brief      configure USART synchronous mode parameters
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  clen: CK length
                only one parameter can be selected which is shown as below:
      \arg        USART_CLEN_NONE: there are 7 CK pulses for an 8 bit frame and 8 CK pulses for a 9 bit frame
      \arg        USART_CLEN_EN:   there are 8 CK pulses for an 8 bit frame and 9 CK pulses for a 9 bit frame
    \param[in]  cph: clock phase
                only one parameter can be selected which is shown as below:
      \arg        USART_CPH_1CK: first clock transition is the first data capture edge
      \arg        USART_CPH_2CK: second clock transition is the first data capture edge
    \param[in]  cpl: clock polarity
                only one parameter can be selected which is shown as below:
      \arg        USART_CPL_LOW:  steady low value on CK pin
      \arg        USART_CPL_HIGH: steady high value on CK pin
    \param[out] none
    \retval     none
*/
void usart_synchronous_clock_config(uint32_t usart_periph, uint32_t clen, uint32_t cph, uint32_t cpl)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);

        USART5_CTL1(usart_periph) &= ~(USART_CTL1_CLEN | USART_CTL1_CPH | USART_CTL1_CPL);
        USART5_CTL1(usart_periph) |= (USART_CTL1_CLEN & clen) | (USART_CTL1_CPH & cph) | (USART_CTL1_CPL & cpl);
    }else{
        USART_CTL1(usart_periph) &= ~(USART_CTL1_CLEN | USART_CTL1_CPH | USART_CTL1_CPL);
        USART_CTL1(usart_periph) |= (USART_CTL1_CLEN & clen) | (USART_CTL1_CPH & cph) | (USART_CTL1_CPL & cpl);
    }
}

/*!
    \brief      configure guard time value in smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  guat: guard time value, 0x00000000-0x000000FF
    \param[out] none
    \retval     none
*/
void usart_guard_time_config(uint32_t usart_periph,uint8_t guat)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);

        USART5_GP(usart_periph) &= ~(USART5_GP_GUAT);
        /* configure USART5 guard time value */
        USART5_GP(usart_periph) |= (USART5_GP_GUAT & ((uint32_t)guat << GP_GUAT_OFFSET));
    }else{
        USART_GP(usart_periph) &= ~(USART_GP_GUAT);
        /* configure USARTx(x=0,1,2) guard time value */
        USART_GP(usart_periph) |= (USART_GP_GUAT & ((uint32_t)guat << GP_GUAT_OFFSET));
    }
}

/*!
    \brief      enable smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_enable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);

        /* enable USART5 smartcard mode */
        USART5_CTL2(usart_periph) |= USART5_CTL2_SCEN;
    }else{
        /* enable USARTx(x=0,1,2) smartcard mode */
        USART_CTL2(usart_periph) |= USART_CTL2_SCEN;
    }
}

/*!
    \brief      disable smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_disable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* disable USART5 smartcard mode */
        USART5_CTL2(usart_periph) &= ~(USART5_CTL2_SCEN);
    }else{
        /* disable USARTx(x=0,1,2) smartcard mode */
        USART_CTL2(usart_periph) &= ~(USART_CTL2_SCEN);
    }
}

/*!
    \brief      enable NACK in smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_nack_enable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* enable USART5 NACK in smartcard mode */
        USART5_CTL2(usart_periph) |= USART5_CTL2_NKEN;
    }else{
        /* enable USARTx(x=0,1,2) NACK in smartcard mode */
        USART_CTL2(usart_periph) |= USART_CTL2_NKEN;
    }
}

/*!
    \brief      disable NACK in smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_nack_disable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* disable USART5 NACK in smartcard mode */
        USART5_CTL2(usart_periph) &= ~(USART5_CTL2_NKEN);
    }else{
        /* disable USARTx(x=0,1,2) NACK in smartcard mode */
        USART_CTL2(usart_periph) &= ~(USART_CTL2_NKEN);
    }
}

/*!
    \brief      configure smartcard auto-retry number
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  scrtnum: smartcard auto-retry number, 0x00000000-0x00000007
    \param[out] none
    \retval     none
*/
void usart_smartcard_autoretry_config(uint32_t usart_periph, uint8_t scrtnum)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);

        USART5_CTL2(usart_periph) &= ~(USART5_CTL2_SCRTNUM);
        /* configure USART5 smartcard auto-retry number */
        USART5_CTL2(usart_periph) |= (USART5_CTL2_SCRTNUM & ((uint32_t) scrtnum << CTL2_SCRTNUM_OFFSET));
    }else{
        USART_CTL3(usart_periph) &= ~(USART_CTL3_SCRTNUM);
        /* configure USARTx(x=0,1,2) smartcard auto-retry number */
        USART_CTL3(usart_periph) |= (USART_CTL3_SCRTNUM & ((uint32_t)scrtnum << CTL3_SCRTNUM_OFFSET));
    }
}

/*!
    \brief      configure block length in Smartcard T=1 reception
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  bl: block length, 0x00000000-0x000000FF
    \param[out] none
    \retval     none
*/
void usart_block_length_config(uint32_t usart_periph, uint8_t bl)
{
    if(USART5 == usart_periph)
    {
        USART5_RT(usart_periph) &= ~(USART5_RT_BL);
        /* configure USART5 block length */
        USART5_RT(usart_periph) |= (USART5_RT_BL & ((uint32_t)bl << RT_BL_OFFSET));
    }else{
        USART_RT(usart_periph) &= ~(USART_RT_BL);
        /* configure USARTx(x=0,1,2) block length */
        USART_RT(usart_periph) |= (USART_RT_BL & ((uint32_t)bl << RT_BL_OFFSET));
    }
}

/*!
    \brief      enable IrDA mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_irda_mode_enable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* enable USART5 IrDA mode */
        USART5_CTL2(usart_periph) |= USART5_CTL2_IREN;
    }else{
        /* enable USARTx(x=0,1,2)/UARTx(x=3,4) IrDA mode */
        USART_CTL2(usart_periph) |= USART_CTL2_IREN;
    }
}

/*!
    \brief      disable IrDA mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_irda_mode_disable(uint32_t usart_periph)
{
    if(USART5 == usart_periph)
    {
        /* disable USART */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
        /* disable USART5 IrDA mode */
        USART5_CTL2(usart_periph) &= ~(USART5_CTL2_IREN);
    }else{
        /* disable USARTx(x=0,1,2)/UARTx(x=3,4) IrDA mode */
        USART_CTL2(usart_periph) &= ~(USART_CTL2_IREN);
    }
}

/*!
    \brief      configure the peripheral clock prescaler in USART IrDA low-power mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  psc: 0x00000000-0x000000FF
    \param[out] none
    \retval     none
*/
void usart_prescaler_config(uint32_t usart_periph, uint8_t psc)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);

        USART5_GP(usart_periph) &= ~(USART5_GP_PSC);
        /* configure the psc in USART5 */
        USART5_GP(usart_periph) |= (uint32_t)psc;
    }else{
        USART_GP(usart_periph) &= ~(USART_GP_PSC);
        /* configure the psc in USARTx(x=0,1,2)/UARTx(x=3,4) */
        USART_GP(usart_periph) |= (uint32_t)psc;
    }
}

/*!
    \brief      configure IrDA low-power
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  irlp: IrDA low-power or normal
                only one parameter can be selected which is shown as below:
      \arg        USART_IRLP_LOW: low-power
      \arg        USART_IRLP_NORMAL: normal
    \param[out] none
    \retval     none
*/
void usart_irda_lowpower_config(uint32_t usart_periph, uint32_t irlp)
{
    if(USART5 == usart_periph)
    {
        /* disable USART5 */
        USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);

        USART5_CTL2(usart_periph) &= ~(USART5_CTL2_IRLP);
        /* configure USART5 IrDA low-power */
        USART5_CTL2(usart_periph) |= (USART5_CTL2_IRLP & irlp);
    }else{
        USART_CTL2(usart_periph) &= ~(USART_CTL2_IRLP);
        /* configure USARTx(x=0,1,2)/UARTx(x=3,4) IrDA low-power */
        USART_CTL2(usart_periph) |= (USART_CTL2_IRLP & irlp);
    }
}

/*!
    \brief      configure USART DMA reception
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  dmaconfig: enable or disable DMA for reception
                only one parameter can be selected which is shown as below:
      \arg        USART_RECEIVE_DMA_ENABLE:  DMA enable for reception
      \arg        USART_RECEIVE_DMA_DISABLE: DMA disable for reception
    \param[out] none
    \retval     none
*/
void usart_dma_receive_config(uint32_t usart_periph, uint8_t dmacmd)
{
    uint32_t ctl = 0U;

    if(USART5 == usart_periph)
    {
        ctl = USART5_CTL2(usart_periph);
        ctl &= ~USART5_CTL2_DENR;
        ctl |= dmacmd;
        /* configure DMA reception */
        USART5_CTL2(usart_periph) = ctl;
    }else{
        ctl = USART_CTL2(usart_periph);
        ctl &= ~USART_CTL2_DENR;
        ctl |= dmacmd;
        /* configure DMA reception */
        USART_CTL2(usart_periph) = ctl;
    }
}

/*!
    \brief      configure USART DMA transmission
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4)
    \param[in]  dmaconfig: enable or disable DMA for transmission
                only one parameter can be selected which is shown as below:
      \arg        USART_TRANSMIT_DMA_ENABLE:  DMA enable for transmission
      \arg        USART_TRANSMIT_DMA_DISABLE: DMA disable for transmission
    \param[out] none
    \retval     none
*/
void usart_dma_transmit_config(uint32_t usart_periph, uint8_t dmacmd)
{
    uint32_t ctl = 0U;

    if(USART5 == usart_periph)
    {
        ctl = USART5_CTL2(usart_periph);
        ctl &= ~USART5_CTL2_DENT;
        ctl |= dmacmd;
        /* configure DMA reception */
        USART5_CTL2(usart_periph) = ctl;
    }else{
        ctl = USART_CTL2(usart_periph);
        ctl &= ~USART_CTL2_DENT;
        ctl |= dmacmd;
        /* configure DMA reception */
        USART_CTL2(usart_periph) = ctl;
    }
}

/*!
    \brief      configure hardware flow control RTS
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  rtsconfig: enable or disable RTS
                only one parameter can be selected which is shown as below:
      \arg        USART_RTS_ENABLE:  enable RTS
      \arg        USART_RTS_DISABLE: disable RTS
    \param[out] none
    \retval     none
*/
void usart_hardware_flow_rts_config(uint32_t usart_periph, uint32_t rtsconfig)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_RTSEN);
    USART_CTL2(usart_periph) |= (USART_CTL2_RTSEN & rtsconfig);
}

/*!
    \brief      configure hardware flow control CTS
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  ctsconfig: enable or disable CTS
                only one parameter can be selected which is shown as below:
      \arg        USART_CTS_ENABLE:  enable CTS
      \arg        USART_CTS_DISABLE: disable CTS
    \param[out] none
    \retval     none
*/
void usart_hardware_flow_cts_config(uint32_t usart_periph, uint32_t ctsconfig)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_CTSEN);
    USART_CTL2(usart_periph) |= (USART_CTL2_CTSEN & ctsconfig);
}

/*!
    \brief      data is transmitted/received with the LSB/MSB first
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  msbf: LSB/MSB
                only one parameter can be selected which is shown as below:
      \arg        USART_MSBF_LSB: LSB first
      \arg        USART_MSBF_MSB: MSB first
    \param[out] none
    \retval     none
*/
void usart_data_first_config(uint32_t usart_periph, uint32_t msbf)
{
    uint32_t ctl = 0U;

    ctl = USART_CTL3(usart_periph);
    ctl &= ~(USART_CTL3_MSBF);
    ctl |= (USART_CTL3_MSBF & msbf);
    /* configure data transmitted/received mode */
    USART_CTL3(usart_periph) = ctl;
}

/*!
    \brief      configure USART inversion
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  invertpara: refer to enum USART_INVERT_CONFIG
                only one parameter can be selected which is shown as below:
      \arg        USART_DINV_ENABLE: data bit level inversion
      \arg        USART_DINV_DISABLE: data bit level not inversion
      \arg        USART_TXPIN_ENABLE: TX pin level inversion
      \arg        USART_TXPIN_DISABLE: TX pin level not inversion
      \arg        USART_RXPIN_ENABLE: RX pin level inversion
      \arg        USART_RXPIN_DISABLE: RX pin level not inversion
    \param[out] none
    \retval     none
*/
void usart_invert_config(uint32_t usart_periph, usart_invert_enum invertpara)
{
    /* inverted or not the specified siginal */
    switch(invertpara)
    {
    case USART_DINV_ENABLE:
        USART_CTL3(usart_periph) |= USART_CTL3_DINV;
        break;
    case USART_DINV_DISABLE:
        USART_CTL3(usart_periph) &= ~(USART_CTL3_DINV);
        break;
    case USART_TXPIN_ENABLE:
        USART_CTL3(usart_periph) |= USART_CTL3_TINV;
        break;
    case USART_TXPIN_DISABLE:
        USART_CTL3(usart_periph) &= ~(USART_CTL3_TINV);
        break;
    case USART_RXPIN_ENABLE:
        USART_CTL3(usart_periph) |= USART_CTL3_RINV;
        break;
    case USART_RXPIN_DISABLE:
        USART_CTL3(usart_periph) &= ~(USART_CTL3_RINV);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the address of the USART in wake up by address match mode
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  addr: address of USART/UART, 0x00000000-0x0000000F
    \param[out] none
    \retval     none
*/
void usart_address_config(uint32_t usart_periph, uint8_t addr)
{
    USART_CTL1(usart_periph) &= ~(USART_CTL1_ADDR);
    USART_CTL1(usart_periph) |= (USART_CTL1_ADDR & (uint32_t)addr);
}

/*!
    \brief      send break frame
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_send_break(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) |= USART_CTL0_SBKCMD;
}

/*!
    \brief      enable collision detected interrupt
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_collision_detected_interrupt_enable(uint32_t usart_periph)
{
    USART_GDCTL(usart_periph) |= USART_GDCTL_CDIE;
}

/*!
    \brief      disable collision detected interrupt
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_collision_detected_interrupt_disable(uint32_t usart_periph)
{
    USART_GDCTL(usart_periph) &= ~(USART_GDCTL_CDIE);
}

/*!
    \brief      enable collision detection
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_collision_detection_enable(uint32_t usart_periph)
{
    USART_GDCTL(usart_periph) |= USART_GDCTL_CDEN;
}

/*!
    \brief      disable collision detection
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_collision_detection_disable(uint32_t usart_periph)
{
    USART_GDCTL(usart_periph) &= ~(USART_GDCTL_CDEN);
}

/*!
    \brief      get flag in STAT0/STAT1/GDCTL register
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  flag: USART flags, refer to usart_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_FLAG_CTS: CTS change flag
      \arg        USART_FLAG_LBD: LIN break detected flag
      \arg        USART_FLAG_TBE: transmit data buffer empty
      \arg        USART_FLAG_TC: transmission complete
      \arg        USART_FLAG_RBNE: read data buffer not empty
      \arg        USART_FLAG_IDLE: IDLE frame detected flag
      \arg        USART_FLAG_ORERR: overrun error flag
      \arg        USART_FLAG_NERR: noise error flag
      \arg        USART_FLAG_FERR: frame error flag
      \arg        USART_FLAG_PERR: parity error flag
      \arg        USART_FLAG_BSY: busy flag
      \arg        USART_FLAG_EB: end of block flag
      \arg        USART_FLAG_RT: receiver timeout flag
      \arg        USART_FLAG_CD: collision detected flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus usart_flag_get(uint32_t usart_periph, usart_flag_enum flag)
{
    if(RESET != (USART_REG_VAL(usart_periph, flag) & BIT(USART_BIT_POS(flag))))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear flag in STAT0/STAT1/GDCTL register
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  flag: USART flags, refer to usart_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_FLAG_CTS: CTS change flag
      \arg        USART_FLAG_LBD: LIN break detected flag
      \arg        USART_FLAG_TC: transmission complete
      \arg        USART_FLAG_RBNE: read data buffer not empty
      \arg        USART_FLAG_EB: end of block flag
      \arg        USART_FLAG_RT: receiver timeout flag
      \arg        USART_FLAG_CD: collision detected flag
    \param[out] none
    \retval     none
*/
void usart_flag_clear(uint32_t usart_periph, usart_flag_enum flag)
{
    if (USART_FLAG_CD == flag)
    {
        USART_REG_VAL(usart_periph, flag) &= ~BIT(USART_BIT_POS(flag));
    } else {
        USART_REG_VAL(usart_periph, flag) = ~BIT(USART_BIT_POS(flag));
    }
}

/*!
    \brief      enable USART interrupt
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  interrupt: USART interrupts, refer to usart_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_PERR: parity error interrupt
      \arg        USART_INT_TBE: transmitter buffer empty interrupt
      \arg        USART_INT_TC: transmission complete interrupt
      \arg        USART_INT_RBNE: read data buffer not empty interrupt and overrun error interrupt
      \arg        USART_INT_IDLE: IDLE line detected interrupt
      \arg        USART_INT_LBD: LIN break detected interrupt
      \arg        USART_INT_ERR: error interrupt
      \arg        USART_INT_CTS: CTS interrupt
      \arg        USART_INT_RT: interrupt enable bit of receive timeout event
      \arg        USART_INT_EB: interrupt enable bit of end of block event
      \arg        USART_INT_CD: collision detected interrupt
    \param[out] none
    \retval     none
*/
void usart_interrupt_enable(uint32_t usart_periph, usart_interrupt_enum interrupt)
{
    USART_REG_VAL(usart_periph, interrupt) |= BIT(USART_BIT_POS(interrupt));
}

/*!
    \brief      disable USART interrupt
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  interrupt: USART interrupts, refer to usart_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_PERR: parity error interrupt
      \arg        USART_INT_TBE: transmitter buffer empty interrupt
      \arg        USART_INT_TC: transmission complete interrupt
      \arg        USART_INT_RBNE: read data buffer not empty interrupt and overrun error interrupt
      \arg        USART_INT_IDLE: IDLE line detected interrupt
      \arg        USART_INT_LBD: LIN break detected interrupt
      \arg        USART_INT_ERR: error interrupt
      \arg        USART_INT_CTS: CTS interrupt
      \arg        USART_INT_RT: interrupt enable bit of receive timeout event
      \arg        USART_INT_EB: interrupt enable bit of end of block event
      \arg        USART_INT_CD: collision detected interrupt
    \param[out] none
    \retval     none
*/
void usart_interrupt_disable(uint32_t usart_periph, usart_interrupt_enum interrupt)
{
    USART_REG_VAL(usart_periph, interrupt) &= ~BIT(USART_BIT_POS(interrupt));
}

/*!
    \brief      get USART interrupt and flag status
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  int_flag: USART interrupt flags, refer to usart_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_FLAG_PERR: parity error interrupt and flag
      \arg        USART_INT_FLAG_TBE: transmitter buffer empty interrupt and flag
      \arg        USART_INT_FLAG_TC: transmission complete interrupt and flag
      \arg        USART_INT_FLAG_RBNE: read data buffer not empty interrupt and flag
      \arg        USART_INT_FLAG_RBNE_ORERR: read data buffer not empty interrupt and overrun error flag
      \arg        USART_INT_FLAG_IDLE: IDLE line detected interrupt and flag
      \arg        USART_INT_FLAG_LBD: LIN break detected interrupt and flag
      \arg        USART_INT_FLAG_CTS: CTS interrupt and flag
      \arg        USART_INT_FLAG_ERR_ORERR: error interrupt and overrun error
      \arg        USART_INT_FLAG_ERR_NERR: error interrupt and noise error flag
      \arg        USART_INT_FLAG_ERR_FERR: error interrupt and frame error flag
      \arg        USART_INT_FLAG_EB: interrupt enable bit of end of block event and flag
      \arg        USART_INT_FLAG_RT: interrupt enable bit of receive timeout event and flag
      \arg        USART_INT_FLAG_CD: collision detected interrupt and flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus usart_interrupt_flag_get(uint32_t usart_periph, usart_interrupt_flag_enum int_flag)
{
    uint32_t intenable = 0U, flagstatus = 0U;
    /* get the interrupt enable bit status */
    intenable = (USART_REG_VAL(usart_periph, int_flag) & BIT(USART_BIT_POS(int_flag)));
    /* get the corresponding flag bit status */
    flagstatus = (USART_REG_VAL2(usart_periph, int_flag) & BIT(USART_BIT_POS2(int_flag)));

    if((0U != flagstatus) && (0U != intenable))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear USART interrupt flag in STAT0/STAT1 register
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  int_flag: USART interrupt flags, refer to usart_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_FLAG_CTS: CTS interrupt and flag
      \arg        USART_INT_FLAG_LBD: LIN break detected interrupt and flag
      \arg        USART_INT_FLAG_TC: transmission complete interrupt and flag
      \arg        USART_INT_FLAG_RBNE: read data buffer not empty interrupt and flag
      \arg        USART_INT_FLAG_EB: interrupt enable bit of end of block event and flag
      \arg        USART_INT_FLAG_RT: interrupt enable bit of receive timeout event and flag
      \arg        USART_INT_FLAG_CD: collision detected interrupt and flag
    \param[out] none
    \retval     none
*/
void usart_interrupt_flag_clear(uint32_t usart_periph, usart_interrupt_flag_enum int_flag)
{
    USART_REG_VAL2(usart_periph, int_flag) = ~BIT(USART_BIT_POS2(int_flag));
}

/*!
    \brief      data is transmitted/received with the LSB/MSB first
    \param[in]  usart_periph: USART5
    \param[in]  msbf: LSB/MSB
                only one parameter can be selected which is shown as below:
      \arg        USART5_MSBF_LSB: LSB first
      \arg        USART5_MSBF_MSB: MSB first
    \param[out] none
    \retval     none
*/
void usart5_data_first_config(uint32_t usart_periph, uint32_t msbf)
{
    uint32_t ctl = 0U;

    USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
    ctl = USART5_CTL1(usart_periph);
    ctl &= ~(USART5_CTL1_MSBF);
    ctl |= (USART5_CTL1_MSBF & msbf);
    /* configure data transmitted/received mode */
    USART5_CTL1(usart_periph) = ctl;
}

/*!
    \brief      configure USART5 inversion
    \param[in]  usart_periph: USART5
    \param[in]  invertpara: refer to enum USART5_INVERT_CONFIG
                only one parameter can be selected which is shown as below:
      \arg        USART5_DINV_ENABLE: data bit level inversion
      \arg        USART5_DINV_DISABLE: data bit level not inversion
      \arg        USART5_TXPIN_ENABLE: TX pin level inversion
      \arg        USART5_TXPIN_DISABLE: TX pin level not inversion
      \arg        USART5_RXPIN_ENABLE: RX pin level inversion
      \arg        USART5_RXPIN_DISABLE: RX pin level not inversion
      \arg        USART5_SWAP_ENABLE: swap TX/RX pins
      \arg        USART5_SWAP_DISABLE: not swap TX/RX pins
    \param[out] none
    \retval     none
*/
void usart5_invert_config(uint32_t usart_periph, usart5_invert_enum invertpara)
{
    /* inverted or not the specified siginal */
    switch(invertpara)
    {
    case USART5_DINV_ENABLE:
        USART5_CTL1(usart_periph) |= USART5_CTL1_DINV;
        break;
    case USART5_DINV_DISABLE:
        USART5_CTL1(usart_periph) &= ~(USART5_CTL1_DINV);
        break;
    case USART5_TXPIN_ENABLE:
        USART5_CTL1(usart_periph) |= USART5_CTL1_TINV;
        break;
    case USART5_TXPIN_DISABLE:
        USART5_CTL1(usart_periph) &= ~(USART5_CTL1_TINV);
        break;
    case USART5_RXPIN_ENABLE:
        USART5_CTL1(usart_periph) |= USART5_CTL1_RINV;
        break;
    case USART5_RXPIN_DISABLE:
        USART5_CTL1(usart_periph) &= ~(USART5_CTL1_RINV);
        break;
    case USART5_SWAP_ENABLE:
        USART5_CTL1(usart_periph) |= USART5_CTL1_STRP;
        break;
    case USART5_SWAP_DISABLE:
        USART5_CTL1(usart_periph) &= ~(USART5_CTL1_STRP);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable the USART5 overrun function
    \param[in]  usart_periph: USART5
    \param[out] none
    \retval     none
*/
void usart5_overrun_enable(uint32_t usart_periph)
{
    USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
    /* enable overrun function */
    USART5_CTL2(usart_periph) &= ~(USART5_CTL2_OVRD);
}

/*!
    \brief      disable the USART5 overrun function
    \param[in]  usart_periph: USART5
    \param[out] none
    \retval     none
*/
void usart5_overrun_disable(uint32_t usart_periph)
{
    USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
    /* disable overrun function */
    USART5_CTL2(usart_periph) |= USART5_CTL2_OVRD;
}

/*!
    \brief      address of the USART terminal
    \param[in]  usart_periph: USART5
    \param[in]  addr: address of USART terminal, 0x00000000-0x000000FF
    \param[out] none
    \retval     none
*/
void usart5_address_config(uint32_t usart_periph, uint8_t addr)
{
    /* disable USART5 */
    USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);

    USART5_CTL1(usart_periph) &= ~(USART5_CTL1_ADDR);
    USART5_CTL1(usart_periph) |= (USART5_CTL1_ADDR & (((uint32_t)addr) << 24));
}

/*!
    \brief      configure address detection mode
    \param[in]  usart_periph: USART5
    \param[in]  addmod: address detection mode
                only one parameter can be selected which is shown as below:
      \arg        USART5_ADDM_4BIT: 4 bits
      \arg        USART5_ADDM_FULLBIT: full bits
    \param[out] none
    \retval     none
*/
void usart5_address_detection_mode_config(uint32_t usart_periph, uint32_t addmod)
{
    /* disable USART */
    USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);

    USART5_CTL1(usart_periph) &= ~(USART5_CTL1_ADDM);
    USART5_CTL1(usart_periph) |= (USART5_CTL1_ADDM & addmod);
}

/*!
    \brief      enable early NACK in smartcard mode
    \param[in]  usart_periph: USART5
    \param[out] none
    \retval     none
*/
void usart5_smartcard_mode_early_nack_enable(uint32_t usart_periph)
{
    USART5_RFCS(usart_periph) |= USART5_RFCS_ELNACK;
}

/*!
    \brief      disable early NACK in smartcard mode
    \param[in]  usart_periph: USART5
    \param[out] none
    \retval     none
*/
void usart5_smartcard_mode_early_nack_disable(uint32_t usart_periph)
{
    USART5_RFCS(usart_periph) &= ~USART5_RFCS_ELNACK;
}

/*!
    \brief      enable DMA on reception error
    \param[in]  usart_periph: USART5
    \param[out] none
    \retval     none
*/
void usart5_reception_error_dma_enable(uint32_t usart_periph)
{
    /* disable USART5 */
    USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);

    USART5_CTL2(usart_periph) &= ~(USART5_CTL2_DDRE);
}

/*!
    \brief      disable DMA on reception error
    \param[in]  usart_periph: USART5
    \param[out] none
    \retval     none
*/
void usart5_reception_error_dma_disable(uint32_t usart_periph)
{
    /* disable USART5 */
    USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);

    USART5_CTL2(usart_periph) |= USART5_CTL2_DDRE;
}

/*!
    \brief      enable USART to wakeup the mcu from deep-sleep mode
    \param[in]  usart_periph: USART5
    \param[out] none
    \retval     none
*/
void usart5_wakeup_enable(uint32_t usart_periph)
{
    USART5_CTL0(usart_periph) |= USART5_CTL0_UESM;
}

/*!
    \brief      disable USART to wakeup the mcu from deep-sleep mode
    \param[in]  usart_periph: USART5
    \param[out] none
    \retval     none
*/
void usart5_wakeup_disable(uint32_t usart_periph)
{
    USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UESM);
}

/*!
    \brief      configure the USART wakeup mode from deep-sleep mode
    \param[in]  usart_periph: USART5
    \param[in]  wum: wakeup mode
                only one parameter can be selected which is shown as below:
      \arg        USART5_WUM_ADDR: WUF active on address match
      \arg        USART5_WUM_STARTB: WUF active on start bit
      \arg        USART5_WUM_RBNE: WUF active on RBNE
    \param[out] none
    \retval     none
*/
void usart5_wakeup_mode_config(uint32_t usart_periph, uint32_t wum)
{
    /* disable USART5 */
    USART5_CTL0(usart_periph) &= ~(USART5_CTL0_UEN);
    /* reset WUM bit */
    USART5_CTL2(usart_periph) &= ~(USART5_CTL2_WUM);
    USART5_CTL2(usart_periph) |= (USART5_CTL2_WUM & wum);
}

/*!
    \brief      enable receive FIFO
    \param[in]  usart_periph: USART5
    \param[out] none
    \retval     none
*/
void usart5_receive_fifo_enable(uint32_t usart_periph)
{
    USART5_RFCS(usart_periph) |= USART5_RFCS_RFEN;
}

/*!
    \brief      disable receive FIFO
    \param[in]  usart_periph: USART5
    \param[out] none
    \retval     none
*/
void usart5_receive_fifo_disable(uint32_t usart_periph)
{
    USART5_RFCS(usart_periph) &= ~(USART5_RFCS_RFEN);
}

/*!
    \brief      read receive FIFO counter number
    \param[in]  usart_periph: USART5
    \param[out] none
    \retval     receive FIFO counter number
*/
uint8_t usart5_receive_fifo_counter_number(uint32_t usart_periph)
{
    return (uint8_t)(GET_BITS(USART5_RFCS(usart_periph), 12U, 14U));
}

/*!
    \brief      get flag in STAT/CHC/RFCS register
    \param[in]  usart_periph: USART5
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        USART5_FLAG_PERR: parity error flag
      \arg        USART5_FLAG_FERR: frame error flag
      \arg        USART5_FLAG_NERR: noise error flag
      \arg        USART5_FLAG_ORERR: overrun error
      \arg        USART5_FLAG_IDLE: idle line detected flag
      \arg        USART5_FLAG_RBNE: read data buffer not empty
      \arg        USART5_FLAG_TC: transmission completed
      \arg        USART5_FLAG_TBE: transmit data register empty
      \arg        USART5_FLAG_LBD: LIN break detected flag
      \arg        USART5_FLAG_RT: receiver timeout flag
      \arg        USART5_FLAG_EB: end of block flag
      \arg        USART5_FLAG_BSY: busy flag
      \arg        USART5_FLAG_AM: address match flag
      \arg        USART5_FLAG_SB: send break flag
      \arg        USART5_FLAG_RWU: receiver wakeup from mute mode.
      \arg        USART5_FLAG_WU: wakeup from deep-sleep mode flag
      \arg        USART5_FLAG_TEA: transmit enable acknowledge flag
      \arg        USART5_FLAG_REA: receive enable acknowledge flag
      \arg        USART5_FLAG_EPERR: early parity error flag
      \arg        USART5_FLAG_RFE: receive FIFO empty flag
      \arg        USART5_FLAG_RFF: receive FIFO full flag
      \arg        USART5_FLAG_RFFINT: receive FIFO full interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus usart5_flag_get(uint32_t usart_periph, usart5_flag_enum flag)
{
    if(RESET != (USART_REG_VAL(usart_periph, flag) & BIT(USART_BIT_POS(flag))))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear USART status
    \param[in]  usart_periph: USART5
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        USART5_FLAG_PERR: parity error flag
      \arg        USART5_FLAG_FERR: frame error flag
      \arg        USART5_FLAG_NERR: noise detected flag
      \arg        USART5_FLAG_ORERR: overrun error flag
      \arg        USART5_FLAG_IDLE: idle line detected flag
      \arg        USART5_FLAG_TC: transmission complete flag
      \arg        USART5_FLAG_LBD: LIN break detected flag
      \arg        USART5_FLAG_RT: receiver timeout flag
      \arg        USART5_FLAG_EB: end of block flag
      \arg        USART5_FLAG_AM: address match flag
      \arg        USART5_FLAG_WU: wakeup from deep-sleep mode flag
      \arg        USART5_FLAG_EPERR: early parity error flag
    \param[out] none
    \retval     none
*/
void usart5_flag_clear(uint32_t usart_periph, usart5_flag_enum flag)
{
    USART5_INTC(usart_periph) |= BIT(USART_BIT_POS(flag));
}

/*!
    \brief      enable USART interrupt
    \param[in]  usart_periph: USART5
    \param[in]  interrupt: USART5 interrupts, refer to usart5_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        USART5_INT_IDLE: idle interrupt
      \arg        USART5_INT_RBNE: read data buffer not empty interrupt and
                                  overrun error interrupt enable interrupt
      \arg        USART5_INT_TC: transmission complete interrupt
      \arg        USART5_INT_TBE: transmit data register empty interrupt
      \arg        USART5_INT_PERR: parity error interrupt
      \arg        USART5_INT_AM: address match interrupt
      \arg        USART5_INT_RT: receiver timeout interrupt
      \arg        USART5_INT_EB: end of block interrupt
      \arg        USART5_INT_LBD: LIN break detection interrupt
      \arg        USART5_INT_ERR: error interrupt enable in multibuffer communication
      \arg        USART5_INT_WU: wakeup from deep-sleep mode interrupt
      \arg        USART5_INT_RFF: receive FIFO full interrupt enable
    \param[out] none
    \retval     none
*/
void usart5_interrupt_enable(uint32_t usart_periph, usart5_interrupt_enum interrupt)
{
    USART_REG_VAL(usart_periph, interrupt) |= BIT(USART_BIT_POS(interrupt));
}

/*!
    \brief      disable USART interrupt
    \param[in]  usart_periph: USART5
    \param[in]  interrupt: USART5 interrupts, refer to usart5_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        USART5_INT_IDLE: idle interrupt
      \arg        USART5_INT_RBNE: read data buffer not empty interrupt and
                                  overrun error interrupt
      \arg        USART5_INT_TC: transmission complete interrupt
      \arg        USART5_INT_TBE: transmit data register empty interrupt
      \arg        USART5_INT_PERR: parity error interrupt
      \arg        USART5_INT_AM: address match interrupt
      \arg        USART5_INT_RT: receiver timeout interrupt
      \arg        USART5_INT_EB: end of block interrupt
      \arg        USART5_INT_LBD: LIN break detection interrupt
      \arg        USART5_INT_ERR: error interrupt enable in multibuffer communication
      \arg        USART5_INT_WU: wakeup from deep-sleep mode interrupt
      \arg        USART5_INT_RFF: receive FIFO full interrupt enable
    \param[out] none
    \retval     none
*/
void usart5_interrupt_disable(uint32_t usart_periph, usart5_interrupt_enum interrupt)
{
    USART_REG_VAL(usart_periph, interrupt) &= ~BIT(USART_BIT_POS(interrupt));
}

/*!
    \brief      enable USART command
    \param[in]  usart_periph: USART5
    \param[in]  cmdtype: command type
                only one parameter can be selected which is shown as below:
      \arg        USART5_CMD_SBKCMD: send break command
      \arg        USART5_CMD_MMCMD: mute mode command
      \arg        USART5_CMD_RXFCMD: receive data flush command
      \arg        USART5_CMD_TXFCMD: transmit data flush request
    \param[out] none
    \retval     none
*/
void usart5_command_enable(uint32_t usart_periph, uint32_t cmdtype)
{
    USART5_CMD(usart_periph) |= (cmdtype);
}

/*!
    \brief      get USART interrupt and flag status
    \param[in]  usart_periph: USART5
    \param[in]  int_flag: interrupt and flag type, refer to usart5_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        USART5_INT_FLAG_EB: end of block interrupt and flag
      \arg        USART5_INT_FLAG_RT: receiver timeout interrupt and flag
      \arg        USART5_INT_FLAG_AM: address match interrupt and flag
      \arg        USART5_INT_FLAG_PERR: parity error interrupt and flag
      \arg        USART5_INT_FLAG_TBE: transmitter buffer empty interrupt and flag
      \arg        USART5_INT_FLAG_TC: transmission complete interrupt and flag
      \arg        USART5_INT_FLAG_RBNE: read data buffer not empty interrupt and flag
      \arg        USART5_INT_FLAG_RBNE_ORERR: read data buffer not empty interrupt and overrun error flag
      \arg        USART5_INT_FLAG_IDLE: IDLE line detected interrupt and flag
      \arg        USART5_INT_FLAG_LBD: LIN break detected interrupt and flag
      \arg        USART5_INT_FLAG_WU: wakeup from deep-sleep mode interrupt and flag
      \arg        USART5_INT_FLAG_ERR_NERR: error interrupt and noise error flag
      \arg        USART5_INT_FLAG_ERR_ORERR: error interrupt and overrun error
      \arg        USART5_INT_FLAG_ERR_FERR: error interrupt and frame error flag
      \arg        USART5_INT_FLAG_RFF: receive FIFO full interrupt and flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus usart5_interrupt_flag_get(uint32_t usart_periph, usart5_interrupt_flag_enum int_flag)
{
    uint32_t intenable = 0U, flagstatus = 0U;
    /* get the interrupt enable bit status */
    intenable = (USART_REG_VAL(usart_periph, int_flag) & BIT(USART_BIT_POS(int_flag)));
    /* get the corresponding flag bit status */
    flagstatus = (USART_REG_VAL2(usart_periph, int_flag) & BIT(USART_BIT_POS2(int_flag)));

    if(flagstatus && intenable)
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear USART interrupt flag
    \param[in]  usart_periph: USART5
    \param[in]  int_flag: interrupt and flag type, refer to usart5_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        USART5_INT_FLAG_PERR: parity error interrupt and flag
      \arg        USART5_INT_FLAG_ERR_FERR: error interrupt and frame error flag
      \arg        USART5_INT_FLAG_ERR_NERR: error interrupt and noise error flag
      \arg        USART5_INT_FLAG_RBNE_ORERR: read data buffer not empty interrupt and overrun error flag
      \arg        USART5_INT_FLAG_ERR_ORERR: error interrupt and overrun error
      \arg        USART5_INT_FLAG_IDLE: IDLE line detected interrupt and flag
      \arg        USART5_INT_FLAG_TC: transmission complete interrupt and flag
      \arg        USART5_INT_FLAG_LBD: LIN break detected interrupt and flag
      \arg        USART5_INT_FLAG_RT: receiver timeout interrupt and flag
      \arg        USART5_INT_FLAG_EB: end of block interrupt and flag
      \arg        USART5_INT_FLAG_AM: address match interrupt and flag
      \arg        USART5_INT_FLAG_WU: wakeup from deep-sleep mode interrupt and flag
      \arg        USART5_INT_FLAG_RFF: receive FIFO full interrupt and flag
    \param[out] none
    \retval     none
*/
void usart5_interrupt_flag_clear(uint32_t usart_periph, usart5_interrupt_flag_enum int_flag)
{
    if(USART5_INT_FLAG_RFF == int_flag)
    {
        USART5_RFCS(usart_periph) &= (uint32_t)(~USART5_RFCS_RFFINT);
    }else{
        USART5_INTC(usart_periph) |= BIT(USART_BIT_POS2(int_flag));
    }
}
