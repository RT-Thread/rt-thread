/*!
    \file    gd32h7xx_usart.c
    \brief   USART driver

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

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

#include "gd32h7xx_usart.h"

/* USART register bit offset */
#define CTL1_ADDR0_OFFSET         ((uint32_t)24U)      /* bit offset of ADDR0 in USART_CTL1 */
#define CTL2_ADDR1_OFFSET         ((uint32_t)24U)      /* bit offset of ADDR1 in USART_CTL2 */
#define GP_GUAT_OFFSET            ((uint32_t)8U)       /* bit offset of GUAT in USART_GP */
#define CTL2_SCRTNUM_OFFSET       ((uint32_t)17U)      /* bit offset of SCRTNUM in USART_CTL2 */
#define RT_BL_OFFSET              ((uint32_t)24U)      /* bit offset of BL in USART_RT */
#define CTL0_DEA_OFFSET           ((uint32_t)21U)      /* bit offset of DEA in USART_CTL0 */
#define CTL0_DED_OFFSET           ((uint32_t)16U)      /* bit offset of DED in USART_CTL0 */
#define FCS_RFCNT_3_4_OFFSET      ((uint32_t)3U)       /* bit offset of RFCNT[4:3] in USART_FCS */

/*!
    \brief      reset USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_deinit(uint32_t usart_periph)
{
    switch(usart_periph)
    {
    case USART0:
        /* reset USART0 */
        rcu_periph_reset_enable(RCU_USART0RST);
        rcu_periph_reset_disable(RCU_USART0RST);
        break;
    case USART1:
        /* reset USART1 */
        rcu_periph_reset_enable(RCU_USART1RST);
        rcu_periph_reset_disable(RCU_USART1RST);
        break;
    case USART2:
        /* reset USART2 */
        rcu_periph_reset_enable(RCU_USART2RST);
        rcu_periph_reset_disable(RCU_USART2RST);
        break;
    case UART3:
        /* reset UART3 */
        rcu_periph_reset_enable(RCU_UART3RST);
        rcu_periph_reset_disable(RCU_UART3RST);
        break;
    case UART4:
        /* reset UART4 */
        rcu_periph_reset_enable(RCU_UART4RST);
        rcu_periph_reset_disable(RCU_UART4RST);
        break;
    case USART5:
        /* reset USART5 */
        rcu_periph_reset_enable(RCU_USART5RST);
        rcu_periph_reset_disable(RCU_USART5RST);
        break;
    case UART6:
        /* reset UART6 */
        rcu_periph_reset_enable(RCU_UART6RST);
        rcu_periph_reset_disable(RCU_UART6RST);
        break;
    case UART7:
        /* reset UART7 */
        rcu_periph_reset_enable(RCU_UART7RST);
        rcu_periph_reset_disable(RCU_UART7RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure USART baud rate value
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  baudval: baud rate value
    \param[out] none
    \retval     none
*/
void usart_baudrate_set(uint32_t usart_periph, uint32_t baudval)
{
    uint32_t uclk = 0U, intdiv = 0U, fradiv = 0U, udiv = 0U;
    switch(usart_periph)
    {
         /* get clock frequency */
    case USART0:
         /* get USART0 clock */
         uclk = rcu_clock_freq_get(CK_USART0);
         break;
    case USART1:
         /* get USART1 clock */
         uclk = rcu_clock_freq_get(CK_USART1);
         break;
    case USART2:
         /* get USART2 clock */
         uclk = rcu_clock_freq_get(CK_USART2);
         break;
    case UART3:
         /* get UART3 clock */
         uclk = rcu_clock_freq_get(CK_APB1);
         break;
    case UART4:
         /* get UART4 clock */
         uclk = rcu_clock_freq_get(CK_APB1);
         break;
    case USART5:
         /* get USART5 clock */
         uclk = rcu_clock_freq_get(CK_USART5);
         break;
    case UART6:
         /* get UART6 clock */
         uclk = rcu_clock_freq_get(CK_APB1);
         break;
    case UART7:
         /* get UART7 clock */
         uclk = rcu_clock_freq_get(CK_APB1);
         break;
    default:
         break;
    }

    if(USART_CTL0(usart_periph) & USART_CTL0_OVSMOD)
    {
        /* oversampling by 8, configure the value of USART_BAUD */
        udiv = ((2U * uclk) + baudval / 2U) / baudval;
        intdiv = udiv & 0x0000fff0U;
        fradiv = (udiv >> 1U) & 0x00000007U;
        USART_BAUD(usart_periph) = ((USART_BAUD_FRADIV | USART_BAUD_INTDIV) & (intdiv | fradiv));
    }else{
        /* oversampling by 16, configure the value of USART_BAUD */
        udiv = (uclk + baudval / 2U) / baudval;
        intdiv = udiv & 0x0000fff0U;
        fradiv = udiv & 0x0000000fU;
        USART_BAUD(usart_periph) = ((USART_BAUD_FRADIV | USART_BAUD_INTDIV) & (intdiv | fradiv));
    }
}

/*!
    \brief      configure USART parity
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  paritycfg: USART parity configure
                only one parameter can be selected which is shown as below:
      \arg        USART_PM_NONE: no parity
      \arg        USART_PM_ODD: odd parity
      \arg        USART_PM_EVEN: even parity
    \param[out] none
    \retval     none
*/
void usart_parity_config(uint32_t usart_periph, uint32_t paritycfg)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* clear USART_CTL0 PM, PCEN bits */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_PM | USART_CTL0_PCEN);
    /* configure USART parity mode */
    USART_CTL0(usart_periph) |= paritycfg;
}

/*!
    \brief      configure USART word length
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  wlen: USART word length configure
                only one parameter can be selected which is shown as below:
      \arg        USART_WL_8BIT : 8 bits
      \arg        USART_WL_9BIT : 9 bits
      \arg        USART_WL_7BIT : 7 bits
      \arg        USART_WL_10BIT: 10 bits
    \param[out] none
    \retval     none
*/
void usart_word_length_set(uint32_t usart_periph, uint32_t wlen)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* clear USART_CTL0 WL bit */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_WL0 | USART_CTL0_WL1);
    /* configure USART word length */
    USART_CTL0(usart_periph) |= wlen;
}

/*!
    \brief      configure USART stop bit length
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  stblen: USART stop bit configure
                only one parameter can be selected which is shown as below:
      \arg        USART_STB_1BIT: 1 bit
      \arg        USART_STB_0_5BIT: 0.5bit
      \arg        USART_STB_2BIT: 2 bits
      \arg        USART_STB_1_5BIT: 1.5bit
    \param[out] none
    \retval     none
*/
void usart_stop_bit_set(uint32_t usart_periph, uint32_t stblen)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* clear USART_CTL1 STB bits */
    USART_CTL1(usart_periph) &= ~USART_CTL1_STB;
    USART_CTL1(usart_periph) |= stblen;
}

/*!
    \brief      enable USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_enable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) |= USART_CTL0_UEN;
}

/*!
    \brief      disable USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_disable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
}

/*!
    \brief      configure USART transmitter
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  txconfig: enable or disable USART transmitter
                only one parameter can be selected which is shown as below:
      \arg        USART_TRANSMIT_ENABLE: enable USART transmission
      \arg        USART_TRANSMIT_DISABLE: enable USART transmission
    \param[out] none
    \retval     none
*/
void usart_transmit_config(uint32_t usart_periph, uint32_t txconfig)
{
    USART_CTL0(usart_periph) &= ~USART_CTL0_TEN;
    /* configure transfer mode */
    USART_CTL0(usart_periph) |= txconfig;
}

/*!
    \brief      configure USART receiver
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  rxconfig: enable or disable USART receiver
                only one parameter can be selected which is shown as below:
      \arg        USART_RECEIVE_ENABLE: enable USART reception
      \arg        USART_RECEIVE_DISABLE: disable USART reception
    \param[out] none
    \retval     none
*/
void usart_receive_config(uint32_t usart_periph, uint32_t rxconfig)
{
    USART_CTL0(usart_periph) &= ~USART_CTL0_REN;
    /* configure receiver mode */
    USART_CTL0(usart_periph) |= rxconfig;
}

/*!
    \brief      data is transmitted/received with the LSB/MSB first
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  msbf: LSB/MSB
                only one parameter can be selected which is shown as below:
      \arg        USART_MSBF_LSB: LSB first
      \arg        USART_MSBF_MSB: MSB first
    \param[out] none
    \retval     none
*/
void usart_data_first_config(uint32_t usart_periph, uint32_t msbf)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* configure LSB or MSB first */
    USART_CTL1(usart_periph) &= ~(USART_CTL1_MSBF);
    USART_CTL1(usart_periph) |= (USART_CTL1_MSBF & msbf);
}

/*!
    \brief      USART inverted configure
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  invertpara: refer to usart_invert_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_DINV_ENABLE: data bit level inversion
      \arg        USART_DINV_DISABLE: data bit level not inversion
      \arg        USART_TXPIN_ENABLE: TX pin level inversion
      \arg        USART_TXPIN_DISABLE: TX pin level not inversion
      \arg        USART_RXPIN_ENABLE: RX pin level inversion
      \arg        USART_RXPIN_DISABLE: RX pin level not inversion
      \arg        USART_SWAP_ENABLE: swap TX/RX pins
      \arg        USART_SWAP_DISABLE: not swap TX/RX pins
    \param[out] none
    \retval     none
*/
void usart_invert_config(uint32_t usart_periph, usart_invert_enum invertpara)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* inverted or not the specified signal */
    switch(invertpara)
    {
    case USART_DINV_ENABLE:
        USART_CTL1(usart_periph) |= USART_CTL1_DINV;
        break;
    case USART_DINV_DISABLE:
        USART_CTL1(usart_periph) &= ~(USART_CTL1_DINV);
        break;
    case USART_TXPIN_ENABLE:
        USART_CTL1(usart_periph) |= USART_CTL1_TINV;
        break;
    case USART_TXPIN_DISABLE:
        USART_CTL1(usart_periph) &= ~(USART_CTL1_TINV);
        break;
    case USART_RXPIN_ENABLE:
        USART_CTL1(usart_periph) |= USART_CTL1_RINV;
        break;
    case USART_RXPIN_DISABLE:
        USART_CTL1(usart_periph) &= ~(USART_CTL1_RINV);
        break;
    case USART_SWAP_ENABLE:
        USART_CTL1(usart_periph) |= USART_CTL1_STRP;
        break;
    case USART_SWAP_DISABLE:
        USART_CTL1(usart_periph) &= ~(USART_CTL1_STRP);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable the USART overrun function
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_overrun_enable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* enable overrun function */
    USART_CTL2(usart_periph) &= ~(USART_CTL2_OVRD);
}

/*!
    \brief      disable the USART overrun function
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_overrun_disable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* disable overrun function */
    USART_CTL2(usart_periph) |= USART_CTL2_OVRD;
}

/*!
    \brief      configure the USART oversample mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  oversamp: oversample value
                only one parameter can be selected which is shown as below:
      \arg        USART_OVSMOD_8: oversampling by 8
      \arg        USART_OVSMOD_16: oversampling by 16
    \param[out] none
    \retval     none
*/
void usart_oversample_config(uint32_t usart_periph, uint32_t oversamp)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* clear OVSMOD bit */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_OVSMOD);
    USART_CTL0(usart_periph) |= oversamp;
}

/*!
    \brief      configure the sample bit method
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  osb: sample bit
                only one parameter can be selected which is shown as below:
      \arg        USART_OSB_1BIT: 1 bit
      \arg        USART_OSB_3BIT: 3 bits
    \param[out] none
    \retval     none
*/
void usart_sample_bit_config(uint32_t usart_periph, uint32_t osb)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_OSB);
    USART_CTL2(usart_periph) |= osb;
}

/*!
    \brief      enable receiver timeout
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_receiver_timeout_enable(uint32_t usart_periph)
{
    USART_CTL1(usart_periph) |= USART_CTL1_RTEN;
}

/*!
    \brief      disable receiver timeout
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_receiver_timeout_disable(uint32_t usart_periph)
{
    USART_CTL1(usart_periph) &= ~(USART_CTL1_RTEN);
}

/*!
    \brief      configure receiver timeout threshold
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  rtimeout: 0x00000000-0x00FFFFFF, receiver timeout value in terms of number of baud clocks
    \param[out] none
    \retval     none
*/
void usart_receiver_timeout_threshold_config(uint32_t usart_periph, uint32_t rtimeout)
{
    USART_RT(usart_periph) &= ~(USART_RT_RT);
    USART_RT(usart_periph) |= rtimeout;
}

/*!
    \brief      USART transmit data function
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  data: data of transmission
    \param[out] none
    \retval     none
*/
void usart_data_transmit(uint32_t usart_periph, uint16_t data)
{
    USART_TDATA(usart_periph) = USART_TDATA_TDATA & (uint32_t)data;
}

/*!
    \brief      USART receive data function
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     data of received
*/
uint16_t usart_data_receive(uint32_t usart_periph)
{
    return (uint16_t)(GET_BITS(USART_RDATA(usart_periph), 0U, 8U));
}

/*!
    \brief      enable USART command
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  cmdtype: command type
                only one parameter can be selected which is shown as below:
      \arg        USART_CMD_SBKCMD: send break command
      \arg        USART_CMD_MMCMD: mute mode command
      \arg        USART_CMD_RXFCMD: receive data flush command
      \arg        USART_CMD_TXFCMD: transmit data flush request
    \param[out] none
    \retval     none
*/
void usart_command_enable(uint32_t usart_periph, uint32_t cmdtype)
{
    USART_CMD(usart_periph) |= (cmdtype);
}

/*!
    \brief      enable address 0 match mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_address_0_match_mode_enable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL1(usart_periph) |= USART_CTL1_AMEN0;
}

/*!
    \brief      disable address 0 match mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_address_0_match_mode_disable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL1(usart_periph) &= ~(USART_CTL1_AMEN0);
}

/*!
    \brief      enable address 1 match mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_address_1_match_mode_enable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) |= USART_CTL2_AMEN1;
}

/*!
    \brief      disable address 1 match mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_address_1_match_mode_disable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_AMEN1);
}

/*!
    \brief      configure address 0 of the USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  addr: 0x00-0xFF, address of USART terminal
    \param[out] none
    \retval     none
*/
void usart_address_0_config(uint32_t usart_periph, uint8_t addr)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL1(usart_periph) &= ~(USART_CTL1_ADDR0);
    USART_CTL1(usart_periph) |= (USART_CTL1_ADDR0 & (((uint32_t)addr) << CTL1_ADDR0_OFFSET));
}

/*!
    \brief      configure address 1 of the USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  addr: 0x00-0xFF, address of USART terminal
    \param[out] none
    \retval     none
*/
void usart_address_1_config(uint32_t usart_periph, uint8_t addr)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_ADDR1);
    USART_CTL2(usart_periph) |= (USART_CTL2_ADDR1 & (((uint32_t)addr) << CTL2_ADDR1_OFFSET));
}

/*!
    \brief      configure address 0 detection mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  addmod: address detection mode
                only one parameter can be selected which is shown as below:
      \arg        USART_ADDM0_4BIT: 4 bits
      \arg        USART_ADDM0_FULLBIT: full bits
    \param[out] none
    \retval     none
*/
void usart_address_0_detection_mode_config(uint32_t usart_periph, uint32_t addmod)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL1(usart_periph) &= ~(USART_CTL1_ADDM0);
    USART_CTL1(usart_periph) |= USART_CTL1_ADDM0 & (addmod);
}

/*!
    \brief      configure address 1 detection mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  addmod: address detection mode
                only one parameter can be selected which is shown as below:
      \arg        USART_ADDM1_4BIT: 4 bits
      \arg        USART_ADDM1_FULLBIT: full bits
    \param[out] none
    \retval     none
*/
void usart_address_1_detection_mode_config(uint32_t usart_periph, uint32_t addmod)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_ADDM1);
    USART_CTL2(usart_periph) |= USART_CTL2_ADDM1 & (addmod);
}

/*!
    \brief      enable mute mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_mute_mode_enable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) |= USART_CTL0_MEN;
}

/*!
    \brief      disable mute mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_mute_mode_disable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_MEN);
}

/*!
    \brief      configure wakeup method in mute mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  wmethod: two methods be used to enter or exit the mute mode
                only one parameter can be selected which is shown as below:
      \arg        USART_WM_IDLE: idle line
      \arg        USART_WM_ADDR: address mark
    \param[out] none
    \retval     none
*/
void usart_mute_mode_wakeup_config(uint32_t usart_periph, uint32_t wmethod)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL0(usart_periph) &= ~(USART_CTL0_WM);
    USART_CTL0(usart_periph) |= wmethod;
}

/*!
    \brief      enable LIN mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_lin_mode_enable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL1(usart_periph) |= USART_CTL1_LMEN;
}

/*!
    \brief      disable LIN mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_lin_mode_disable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL1(usart_periph) &= ~(USART_CTL1_LMEN);
}

/*!
    \brief      LIN break detection length
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  lblen: LIN break detection length
                only one parameter can be selected which is shown as below:
      \arg        USART_LBLEN_10B: 10 bits break detection
      \arg        USART_LBLEN_11B: 11 bits break detection
    \param[out] none
    \retval     none
*/
void usart_lin_break_detection_length_config(uint32_t usart_periph, uint32_t lblen)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL1(usart_periph) &= ~(USART_CTL1_LBLEN);
    USART_CTL1(usart_periph) |= USART_CTL1_LBLEN & (lblen);
}

/*!
    \brief      enable half-duplex mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_halfduplex_enable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) |= USART_CTL2_HDEN;
}

/*!
    \brief      disable half-duplex mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_halfduplex_disable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_HDEN);
}

/*!
    \brief      enable clock
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_clock_enable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL1(usart_periph) |= USART_CTL1_CKEN;
}

/*!
    \brief      disable clock
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_clock_disable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL1(usart_periph) &= ~(USART_CTL1_CKEN);
}

/*!
    \brief      configure USART synchronous mode parameters
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  clen: last bit clock pulse
                only one parameter can be selected which is shown as below:
      \arg        USART_CLEN_NONE: clock pulse of the last data bit (MSB) is not output to the CK pin
      \arg        USART_CLEN_EN: clock pulse of the last data bit (MSB) is output to the CK pin
    \param[in]  cph: clock phase
                only one parameter can be selected which is shown as below:
      \arg        USART_CPH_1CK: first clock transition is the first data capture edge
      \arg        USART_CPH_2CK: second clock transition is the first data capture edge
    \param[in]  cpl: clock polarity
                only one parameter can be selected which is shown as below:
      \arg        USART_CPL_LOW: steady low value on CK pin
      \arg        USART_CPL_HIGH: steady high value on CK pin
    \param[out] none
    \retval     none
*/
void usart_synchronous_clock_config(uint32_t usart_periph, uint32_t clen, uint32_t cph, uint32_t cpl)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* reset USART_CTL1 CLEN,CPH,CPL bits */
    USART_CTL1(usart_periph) &= ~(USART_CTL1_CLEN | USART_CTL1_CPH | USART_CTL1_CPL);

    USART_CTL1(usart_periph) |= (USART_CTL1_CLEN & clen);
    USART_CTL1(usart_periph) |= (USART_CTL1_CPH & cph);
    USART_CTL1(usart_periph) |= (USART_CTL1_CPL & cpl);
}

/*!
    \brief      configure guard time value in smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  guat: 0x00-0xFF
    \param[out] none
    \retval     none
*/
void usart_guard_time_config(uint32_t usart_periph, uint32_t guat)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_GP(usart_periph) &= ~(USART_GP_GUAT);
    USART_GP(usart_periph) |= (USART_GP_GUAT & ((guat) << GP_GUAT_OFFSET));
}

/*!
    \brief      enable smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_enable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) |= USART_CTL2_SCEN;
}

/*!
    \brief      disable smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_disable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_SCEN);
}

/*!
    \brief      enable NACK in smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_nack_enable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) |= USART_CTL2_NKEN;
}

/*!
    \brief      disable NACK in smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_nack_disable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_NKEN);
}

/*!
    \brief      enable early NACK in smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_early_nack_enable(uint32_t usart_periph)
{
    USART_FCS(usart_periph) |= USART_FCS_ELNACK;
}

/*!
    \brief      disable early NACK in smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_early_nack_disable(uint32_t usart_periph)
{
    USART_FCS(usart_periph) &= ~USART_FCS_ELNACK;
}

/*!
    \brief      configure smartcard auto-retry number
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  scrtnum: 0x00000000-0x00000007, smartcard auto-retry number
    \param[out] none
    \retval     none
*/
void usart_smartcard_autoretry_config(uint32_t usart_periph, uint32_t scrtnum)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_SCRTNUM);
    USART_CTL2(usart_periph) |= (USART_CTL2_SCRTNUM & (scrtnum << CTL2_SCRTNUM_OFFSET));
}

/*!
    \brief      configure block length
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  bl: 0x00000000-0x000000FF
    \param[out] none
    \retval     none
*/
void usart_block_length_config(uint32_t usart_periph, uint32_t bl)
{
    USART_RT(usart_periph) &= ~(USART_RT_BL);
    USART_RT(usart_periph) |= (USART_RT_BL & ((bl) << RT_BL_OFFSET));
}

/*!
    \brief      enable IrDA mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_irda_mode_enable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) |= USART_CTL2_IREN;
}

/*!
    \brief      disable IrDA mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_irda_mode_disable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_IREN);
}

/*!
    \brief      configure the peripheral clock prescaler in USART IrDA low-power or SmartCard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  psc: 0x00000000-0x000000FF
    \param[out] none
    \retval     none
*/
void usart_prescaler_config(uint32_t usart_periph, uint32_t psc)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_GP(usart_periph) &= ~(USART_GP_PSC);
    USART_GP(usart_periph) |= psc;
}

/*!
    \brief      configure IrDA low-power
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  irlp: IrDA low-power or normal
                only one parameter can be selected which is shown as below:
      \arg        USART_IRLP_LOW:    low-power
      \arg        USART_IRLP_NORMAL: normal
    \param[out] none
    \retval     none
*/
void usart_irda_lowpower_config(uint32_t usart_periph, uint32_t irlp)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_IRLP);
    USART_CTL2(usart_periph) |= (USART_CTL2_IRLP & irlp);
}

/*!
    \brief      configure hardware flow control RTS
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  rtsconfig: enable or disable RTS
                only one parameter can be selected which is shown as below:
      \arg        USART_RTS_ENABLE:  enable RTS
      \arg        USART_RTS_DISABLE: disable RTS
    \param[out] none
    \retval     none
*/
void usart_hardware_flow_rts_config(uint32_t usart_periph, uint32_t rtsconfig)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_RTSEN);
    USART_CTL2(usart_periph) |= rtsconfig;
}

/*!
    \brief      configure hardware flow control CTS
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  ctsconfig:  enable or disable CTS
                only one parameter can be selected which is shown as below:
      \arg        USART_CTS_ENABLE:  enable CTS
      \arg        USART_CTS_DISABLE: disable CTS
    \param[out] none
    \retval     none
*/
void usart_hardware_flow_cts_config(uint32_t usart_periph, uint32_t ctsconfig)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~USART_CTL2_CTSEN;
    USART_CTL2(usart_periph) |= ctsconfig;
}

 /*!
    \brief      configure hardware flow control coherence mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  hcm:
                only one parameter can be selected which is shown as below:
      \arg        USART_HCM_NONE: nRTS signal equals to the rxne status register
      \arg        USART_HCM_EN:   nRTS signal is set when the last data bit has been sampled
    \param[out] none
    \retval     none
*/
void usart_hardware_flow_coherence_config(uint32_t usart_periph, uint32_t hcm)
{
    USART_CHC(usart_periph) &= ~(USART_CHC_HCM);
    USART_CHC(usart_periph) |= (USART_CHC_HCM & hcm);
}

/*!
    \brief      enable RS485 driver
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_rs485_driver_enable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) |= USART_CTL2_DEM;
}

/*!
    \brief      disable RS485 driver
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_rs485_driver_disable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_DEM);
}

/*!
    \brief      configure driver enable assertion time
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  deatime: 0x00000000-0x0000001F
    \param[out] none
    \retval     none
*/
void usart_driver_assertime_config(uint32_t usart_periph, uint32_t deatime)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL0(usart_periph) &= ~(USART_CTL0_DEA);
    USART_CTL0(usart_periph) |= (USART_CTL0_DEA & ((deatime) << CTL0_DEA_OFFSET));
}

/*!
    \brief      configure driver enable de-assertion time
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  dedtime: 0x00000000-0x0000001F
    \param[out] none
    \retval     none
*/
void usart_driver_deassertime_config(uint32_t usart_periph, uint32_t dedtime)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL0(usart_periph) &= ~(USART_CTL0_DED);
    USART_CTL0(usart_periph) |= (USART_CTL0_DED & ((dedtime) << CTL0_DED_OFFSET));
}

/*!
    \brief      configure driver enable polarity mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  dep: DE signal
                only one parameter can be selected which is shown as below:
      \arg        USART_DEP_HIGH: DE signal is active high
      \arg        USART_DEP_LOW: DE signal is active low
    \param[out] none
    \retval     none
*/
void usart_depolarity_config(uint32_t usart_periph, uint32_t dep)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* reset DEP bit */
    USART_CTL2(usart_periph) &= ~(USART_CTL2_DEP);
    USART_CTL2(usart_periph) |= (USART_CTL2_DEP & dep);
}

/*!
    \brief      configure USART DMA reception
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  dmacmd: enable or disable DMA for reception
                only one parameter can be selected which is shown as below:
      \arg        USART_RECEIVE_DMA_ENABLE: USART enable DMA for reception
      \arg        USART_RECEIVE_DMA_DISABLE: USART disable DMA for reception
    \param[out] none
    \retval     none
*/
void usart_dma_receive_config(uint32_t usart_periph, uint32_t dmacmd)
{
    uint32_t ctl = 0U;

    ctl = USART_CTL2(usart_periph);
    ctl &= ~USART_CTL2_DENR;
    ctl |= dmacmd;
    /* configure DMA reception */
    USART_CTL2(usart_periph) = ctl;
}

/*!
    \brief      configure USART DMA transmission
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  dmacmd: enable or disable DMA for transmission
                only one parameter can be selected which is shown as below:
      \arg        USART_TRANSMIT_DMA_ENABLE: USART enable DMA for transmission
      \arg        USART_TRANSMIT_DMA_DISABLE: USART disable DMA for transmission
    \param[out] none
    \retval     none
*/
void usart_dma_transmit_config(uint32_t usart_periph, uint32_t dmacmd)
{
    uint32_t ctl = 0U;

    ctl = USART_CTL2(usart_periph);
    ctl &= ~USART_CTL2_DENT;
    ctl |= dmacmd;
    /* configure DMA transmission */
    USART_CTL2(usart_periph) = ctl;
}

/*!
    \brief      disable DMA on reception error
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_reception_error_dma_disable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) |= USART_CTL2_DDRE;
}

/*!
    \brief      enable DMA on reception error
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_reception_error_dma_enable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);

    USART_CTL2(usart_periph) &= ~(USART_CTL2_DDRE);
}

/*!
    \brief      enable USART to wakeup the mcu from deep-sleep mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_wakeup_enable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) |= USART_CTL0_UESM;
}

/*!
    \brief      disable USART to wakeup the mcu from deep-sleep mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_wakeup_disable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UESM);
}

/*!
    \brief      configure the USART wakeup mode from deep-sleep mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  wum: wakeup mode
                only one parameter can be selected which is shown as below:
      \arg        USART_WUM_ADDR: WUF active on address match
      \arg        USART_WUM_STARTB: WUF active on start bit
      \arg        USART_WUM_RBNE: WUF active on RBNE
    \param[out] none
    \retval     none
*/
void usart_wakeup_mode_config(uint32_t usart_periph, uint32_t wum)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* reset WUM bit */
    USART_CTL2(usart_periph) &= ~(USART_CTL2_WUM);
    USART_CTL2(usart_periph) |= USART_CTL2_WUM & (wum);
}

/*!
    \brief      enable FIFO
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_fifo_enable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* set FEN bit */
    USART_FCS(usart_periph) |= USART_FCS_FEN;
}

/*!
    \brief      disable FIFO
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_fifo_disable(uint32_t usart_periph)
{
    /* disable USART */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
    /* reset FEN bit */
    USART_FCS(usart_periph) &= ~(USART_FCS_FEN);
}

/*!
    \brief      configure transmit FIFO threshold
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  txthreshold: transmit FIFO threshold
                only one parameter can be selected which is shown as below:
      \arg        USART_TFTCFG_THRESHOLD_1_8: transmit FIFO reaches 1/8 of its depth
      \arg        USART_TFTCFG_THRESHOLD_1_4: transmit FIFO reaches 1/4 of its depth
      \arg        USART_TFTCFG_THRESHOLD_1_2: transmit FIFO reaches 1/2 of its depth
      \arg        USART_TFTCFG_THRESHOLD_3_4: transmit FIFO reaches 3/4 of its depth
      \arg        USART_TFTCFG_THRESHOLD_7_8: transmit FIFO reaches 7/8 of its depth
      \arg        USART_TFTCFG_THRESHOLD_EMPTY: transmit FIFO becomes empty
    \param[out] none
    \retval     none
*/
void usart_transmit_fifo_threshold_config(uint32_t usart_periph, uint32_t txthreshold)
{
    USART_FCS(usart_periph) &= ~(USART_FCS_TFTCFG);
    USART_FCS(usart_periph) |= txthreshold;
}

/*!
    \brief      configure receive FIFO threshold
    \param[in]  usart_periph: receive FIFO threshold
                only one parameter can be selected which is shown as below:
      \arg        USART_RFTCFG_THRESHOLD_1_8: receive FIFO reaches 1/8 of its depth
      \arg        USART_RFTCFG_THRESHOLD_1_4: receive FIFO reaches 1/4 of its depth
      \arg        USART_RFTCFG_THRESHOLD_1_2: receive FIFO reaches 1/2 of its depth
      \arg        USART_RFTCFG_THRESHOLD_3_4: receive FIFO reaches 3/4 of its depth
      \arg        USART_RFTCFG_THRESHOLD_7_8: receive FIFO reaches 7/8 of its depth
      \arg        USART_RFTCFG_THRESHOLD_FULL: receive FIFO becomes full
    \param[out] none
    \retval     none
*/
void usart_receive_fifo_threshold_config(uint32_t usart_periph, uint32_t rxthreshold)
{
    USART_FCS(usart_periph) &= ~(USART_FCS_RFTCFG);
    USART_FCS(usart_periph) |= rxthreshold;
}

/*!
    \brief      read receive FIFO counter number
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[out] none
    \retval     uint8_t: receive FIFO counter number
*/
uint8_t usart_receive_fifo_counter_number(uint32_t usart_periph)
{
    uint32_t cnt = 0U;

    cnt |= GET_BITS(USART_FCS(usart_periph), 12U, 14U);
    cnt |= (GET_BITS(USART_FCS(usart_periph), 1U, 2U) << FCS_RFCNT_3_4_OFFSET);

    return (uint8_t)(cnt);
}

/*!
    \brief      get flag in STAT/CHC/FCS register
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        USART_FLAG_PERR: parity error flag
      \arg        USART_FLAG_FERR: frame error flag
      \arg        USART_FLAG_NERR: noise error flag
      \arg        USART_FLAG_ORERR: overrun error
      \arg        USART_FLAG_IDLE: idle line detected flag
      \arg        USART_FLAG_RFNE: receive FIFO not empty(when FIFO is enabled)
      \arg        USART_FLAG_RBNE: read data buffer not empty(when FIFO is disabled)
      \arg        USART_FLAG_TC: transmission completed
      \arg        USART_FLAG_TFNF: transmit FIFO not full(when FIFO is enabled)
      \arg        USART_FLAG_TBE: transmit data register empty(when FIFO is disabled)
      \arg        USART_FLAG_LBD: LIN break detected flag
      \arg        USART_FLAG_CTSF: CTS change flag
      \arg        USART_FLAG_CTS: CTS level
      \arg        USART_FLAG_RT: receiver timeout flag
      \arg        USART_FLAG_EB: end of block flag
      \arg        USART_FLAG_BSY: busy flag
      \arg        USART_FLAG_AM0: address 0 match flag
      \arg        USART_FLAG_AM1: address 1 match flag
      \arg        USART_FLAG_SB: send break flag
      \arg        USART_FLAG_RWU: receiver wakeup from mute mode.
      \arg        USART_FLAG_WU: wakeup from deep-sleep mode flag
      \arg        USART_FLAG_TEA: transmit enable acknowledge flag
      \arg        USART_FLAG_REA: receive enable acknowledge flag
      \arg        USART_FLAG_EPERR: early parity error flag
      \arg        USART_FLAG_RFE: receive FIFO empty flag
      \arg        USART_FLAG_RFF: receive FIFO full flag
      \arg        USART_FLAG_TFT: transmit FIFO threshold flag
      \arg        USART_FLAG_TFE: transmit FIFO empty flag
      \arg        USART_FLAG_TFF: transmit FIFO full flag
      \arg        USART_FLAG_RFT: receive FIFO threshold flag
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
    \brief      clear USART status
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        USART_FLAG_PERR: parity error flag
      \arg        USART_FLAG_FERR: frame error flag
      \arg        USART_FLAG_NERR: noise detected flag
      \arg        USART_FLAG_ORERR: overrun error flag
      \arg        USART_FLAG_IDLE: idle line detected flag
      \arg        USART_FLAG_TC: transmission complete flag
      \arg        USART_FLAG_LBD: LIN break detected flag
      \arg        USART_FLAG_CTSF: CTS change flag
      \arg        USART_FLAG_RT: receiver timeout flag
      \arg        USART_FLAG_EB: end of block flag
      \arg        USART_FLAG_AM0: address 0 match flag
      \arg        USART_FLAG_AM1: address 1 match flag
      \arg        USART_FLAG_WU: wakeup from deep-sleep mode flag
      \arg        USART_FLAG_EPERR: early parity error flag
      \arg        USART_FLAG_TFE: transmit FIFO empty flag
    \param[out] none
    \retval     none
*/
void usart_flag_clear(uint32_t usart_periph, usart_flag_enum flag)
{
    if(USART_FLAG_AM1 == flag)
    {
        USART_INTC(usart_periph) |= USART_INTC_AMC1;
    }else if(USART_FLAG_EPERR == flag)
    {
        USART_CHC(usart_periph) &= (uint32_t)(~USART_CHC_EPERR);
    }else if(USART_FLAG_TFE == flag)
    {
        USART_FCS(usart_periph) |= USART_FCS_TFEC;
    }else{
        USART_INTC(usart_periph) |= BIT(USART_BIT_POS(flag));
    }
}

/*!
    \brief      enable USART interrupt
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  interrupt: interrupt type
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_IDLE: idle interrupt
      \arg        USART_INT_RFNE: receive FIFO not empty interrupt and overrun error interrupt(when FIFO is enabled)
      \arg        USART_INT_RBNE: read data buffer not empty interrupt and overrun error interrupt enable interrupt(when FIFO is disabled)
      \arg        USART_INT_TC: transmission complete interrupt
      \arg        USART_INT_TFNF: transmit FIFO not full interrupt(when FIFO is enabled)
      \arg        USART_INT_TBE: transmit data register empty interrupt(when FIFO is disabled)
      \arg        USART_INT_PERR: parity error interrupt
      \arg        USART_INT_AM0: address 0 match interrupt
      \arg        USART_INT_AM1: address 1 match interrupt
      \arg        USART_INT_RT: receiver timeout interrupt
      \arg        USART_INT_EB: end of block interrupt
      \arg        USART_INT_LBD: LIN break detection interrupt
      \arg        USART_INT_ERR: error interrupt enable in multibuffer communication
      \arg        USART_INT_CTS: CTS interrupt
      \arg        USART_INT_WU: wakeup from deep-sleep mode interrupt
      \arg        USART_INT_TFE: transmit FIFO empty interrupt
      \arg        USART_INT_TFT: transmit FIFO threshold interrupt
      \arg        USART_INT_RFT: receive FIFO threshold interrupt
      \arg        USART_INT_RFF: receive FIFO full interrupt
    \param[out] none
    \retval     none
*/
void usart_interrupt_enable(uint32_t usart_periph, usart_interrupt_enum interrupt)
{
    USART_REG_VAL(usart_periph, interrupt) |= BIT(USART_BIT_POS(interrupt));
}

/*!
    \brief      disable USART interrupt
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  interrupt: interrupt type
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_IDLE: idle interrupt
      \arg        USART_INT_RFNE: receive FIFO not empty interrupt and overrun error interrupt(when FIFO is enabled)
      \arg        USART_INT_RBNE: read data buffer not empty interrupt and overrun error interrupt enable interrupt(when FIFO is disabled)
      \arg        USART_INT_TC: transmission complete interrupt
      \arg        USART_INT_TFNF: transmit FIFO not full interrupt(when FIFO is enabled)
      \arg        USART_INT_TBE: transmit data register empty interrupt(when FIFO is disabled)
      \arg        USART_INT_PERR: parity error interrupt
      \arg        USART_INT_AM0: address 0 match interrupt
      \arg        USART_INT_AM1: address 1 match interrupt
      \arg        USART_INT_RT: receiver timeout interrupt
      \arg        USART_INT_EB: end of block interrupt
      \arg        USART_INT_LBD: LIN break detection interrupt
      \arg        USART_INT_ERR: error interrupt enable in multibuffer communication
      \arg        USART_INT_CTS: CTS interrupt
      \arg        USART_INT_WU: wakeup from deep-sleep mode interrupt
      \arg        USART_INT_TFE: transmit FIFO empty interrupt
      \arg        USART_INT_TFT: transmit FIFO threshold interrupt
      \arg        USART_INT_RFT: receive FIFO threshold interrupt
      \arg        USART_INT_RFF: receive FIFO full interrupt
    \param[out] none
    \retval     none
*/
void usart_interrupt_disable(uint32_t usart_periph, usart_interrupt_enum interrupt)
{
    USART_REG_VAL(usart_periph, interrupt) &= ~BIT(USART_BIT_POS(interrupt));
}

/*!
    \brief      get USART interrupt and flag status
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  int_flag: interrupt and flag type, refer to usart_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_FLAG_EB: end of block interrupt and flag
      \arg        USART_INT_FLAG_RT: receiver timeout interrupt and flag
      \arg        USART_INT_FLAG_AM0: address 0 match interrupt and flag
      \arg        USART_INT_FLAG_AM1: address 1 match interrupt and flag
      \arg        USART_INT_FLAG_PERR: parity error interrupt and flag
      \arg        USART_INT_FLAG_TBE: transmitter buffer empty interrupt and flag(when FIFO is disabled)
      \arg        USART_INT_FLAG_TFNF: transmit FIFO not full interrupt and flag(when FIFO is enabled)
      \arg        USART_INT_FLAG_TC: transmission complete interrupt and flag
      \arg        USART_INT_FLAG_RBNE: read data buffer not empty interrupt and flag(when FIFO is disabled)
      \arg        USART_INT_FLAG_RFNE: receive FIFO not empty interrupt and flag(when FIFO is enabled)
      \arg        USART_INT_FLAG_RBNE_ORERR: read data buffer not empty interrupt and overrun error flag(when FIFO is disabled)
      \arg        USART_INT_FLAG_RFNE_ORERR: receive FIFO not empty interrupt and overrun error flag(when FIFO is enabled)
      \arg        USART_INT_FLAG_IDLE: IDLE line detected interrupt and flag
      \arg        USART_INT_FLAG_LBD: LIN break detected interrupt and flag
      \arg        USART_INT_FLAG_WU: wakeup from deep-sleep mode interrupt and flag
      \arg        USART_INT_FLAG_CTS: CTS interrupt and flag
      \arg        USART_INT_FLAG_ERR_NERR: error interrupt and noise error flag
      \arg        USART_INT_FLAG_ERR_ORERR: error interrupt and overrun error
      \arg        USART_INT_FLAG_ERR_FERR: error interrupt and frame error flag
      \arg        USART_INT_FLAG_TFT: transmit FIFO threshold interrupt and flag
      \arg        USART_INT_FLAG_TFE: transmit FIFO empty interrupt and flag
      \arg        USART_INT_FLAG_RFT: receive FIFO threshold interrupt and flag
      \arg        USART_INT_FLAG_RFF: receive FIFO full interrupt and flag
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

    if(flagstatus && intenable)
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear USART interrupt flag
    \param[in]  usart_periph: USARTx(x=0,1,2,5), UARTx(x=3,4,6,7)
    \param[in]  flag: USART interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_FLAG_PERR: parity error flag
      \arg        USART_INT_FLAG_ERR_FERR: frame error flag
      \arg        USART_INT_FLAG_ERR_NERR: noise detected flag
      \arg        USART_INT_FLAG_RBNE_ORERR: read data buffer not empty interrupt and overrun error flag
      \arg        USART_INT_FLAG_ERR_ORERR: error interrupt and overrun error
      \arg        USART_INT_FLAG_IDLE: idle line detected flag
      \arg        USART_INT_FLAG_TC: transmission complete flag
      \arg        USART_INT_FLAG_LBD: LIN break detected flag
      \arg        USART_INT_FLAG_CTS: CTS change flag
      \arg        USART_INT_FLAG_RT: receiver timeout flag
      \arg        USART_INT_FLAG_EB: end of block flag
      \arg        USART_INT_FLAG_AM0: address 0 match flag
      \arg        USART_INT_FLAG_AM1: address 1 match flag
      \arg        USART_INT_FLAG_WU: wakeup from deep-sleep mode flag
      \arg        USART_INT_FLAG_RFT: receive FIFO threshold reach interrupt and flag
      \arg        USART_INT_FLAG_RFF: receive FIFO full interrupt and flag
      \arg        USART_INT_FLAG_TFE: transmit FIFO empty interrupt and flag
    \param[out] none
    \retval     none
*/
void usart_interrupt_flag_clear(uint32_t usart_periph, usart_interrupt_flag_enum int_flag)
{
    if(USART_INT_FLAG_TFE == int_flag)
    {
        USART_FCS(usart_periph) |= USART_FCS_TFEC;
    }else if(USART_INT_FLAG_RFF == int_flag)
    {
        USART_FCS(usart_periph) &= (uint32_t)(~USART_FCS_RFFIF);
    }else if(USART_INT_FLAG_RFT == int_flag)
    {
        USART_FCS(usart_periph) &= (uint32_t)(~USART_FCS_RFTIF);
    }else{
        USART_INTC(usart_periph) |= BIT(USART_BIT_POS2(int_flag));
    }
}
