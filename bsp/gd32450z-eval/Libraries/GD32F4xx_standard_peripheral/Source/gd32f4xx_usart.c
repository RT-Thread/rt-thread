/*!
    \file  gd32f4xx_usart.c
    \brief USART driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_usart.h"

/*!
    \brief      reset USART/UART 
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_deinit(uint32_t usart_periph)
{
    switch(usart_periph){
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
    case UART6:
        rcu_periph_reset_enable(RCU_UART6RST);
        rcu_periph_reset_disable(RCU_UART6RST);
        break;
    case UART7:
        rcu_periph_reset_enable(RCU_UART7RST);
        rcu_periph_reset_disable(RCU_UART7RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure USART baud rate value
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  baudval: baud rate value
    \param[out] none
    \retval     none
*/ 
void usart_baudrate_set(uint32_t usart_periph, uint32_t baudval)
{
    uint32_t uclk=0U, intdiv=0U, fradiv=0U, udiv=0U;
    switch(usart_periph){
         /* get clock frequency */
    case USART0:
         uclk=rcu_clock_freq_get(CK_APB2);
         break;
    case USART5:
         uclk=rcu_clock_freq_get(CK_APB2);
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
    case UART6:
         uclk=rcu_clock_freq_get(CK_APB1);
         break;
    case UART7:
         uclk=rcu_clock_freq_get(CK_APB1);
         break;
    default:
         break;
    }
    if(USART_CTL0(usart_periph) & USART_CTL0_OVSMOD){
        /* when oversampling by 8, configure the value of USART_BAUD */
        udiv = ((2U*uclk) + baudval/2U)/baudval;
        intdiv = udiv & 0xfff0U;
        fradiv = udiv & 0x7U;
        USART_BAUD(usart_periph) |= ((USART_BAUD_FRADIV | USART_BAUD_INTDIV) & (intdiv | fradiv));
    }else{
        /* when oversampling by 16, configure the value of USART_BAUD */
        udiv = (uclk+baudval/2U)/baudval;
        intdiv = udiv & 0xfff0U;
        fradiv = udiv & 0xfU;
        USART_BAUD(usart_periph) |= ((USART_BAUD_FRADIV | USART_BAUD_INTDIV) & (intdiv | fradiv));
    }   
}

/*!
    \brief     configure USART parity function
    \param[in] usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in] paritycfg: configure USART parity
      \arg       USART_PM_NONE: no parity
      \arg       USART_PM_ODD:  odd parity
      \arg       USART_PM_EVEN: even parity 
    \param[out] none
    \retval     none
*/
void usart_parity_config(uint32_t usart_periph, uint32_t paritycfg)
{
    /* clear USART_CTL0 PM,PCEN Bits */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_PM | USART_CTL0_PCEN);
     /* configure USART parity mode */
    USART_CTL0(usart_periph) |= paritycfg ;
}

/*!
    \brief     configure USART word length
    \param[in] usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in] wlen: USART word length configure
      \arg       USART_WL_8BIT: 8 bits
      \arg       USART_WL_9BIT: 9 bits
    \param[out] none
    \retval     none
*/
void usart_word_length_set(uint32_t usart_periph, uint32_t wlen)
{
    /* clear USART_CTL0 WL bit */
    USART_CTL0(usart_periph) &= ~USART_CTL0_WL;
    /* configure USART word length */
    USART_CTL0(usart_periph) |= wlen;
}

/*!
    \brief     configure USART stop bit length
    \param[in] usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in] stblen: USART stop bit configure
      \arg       USART_STB_1BIT:   1 bit
      \arg       USART_STB_0_5BIT: 0.5 bit
      \arg       USART_STB_2BIT:   2 bits
      \arg       USART_STB_1_5BIT: 1.5 bits
    \param[out] none
    \retval     none
*/
void usart_stop_bit_set(uint32_t usart_periph, uint32_t stblen)
{
    /* clear USART_CTL1 STB bits */
    USART_CTL1(usart_periph) &= ~USART_CTL1_STB; 
    /* configure USART stop bits */
    USART_CTL1(usart_periph) |= stblen;
}
/*!
    \brief      enable USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_enable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) |= USART_CTL0_UEN;
}

/*!
    \brief     disable USART
    \param[in] usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_disable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
}

/*!
    \brief      configure USART transmitter
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  rtconfig: enable or disable USART transmitter
      \arg        USART_TRANSMIT_ENABLE: enable USART transmission
      \arg        USART_TRANSMIT_DISABLE: enable USART transmission
    \param[out] none
    \retval     none
*/
void usart_transmit_config(uint32_t usart_periph, uint32_t txconfig)
{
    uint32_t ctl = 0U;
    
    ctl = USART_CTL0(usart_periph);
    ctl &= ~USART_CTL0_TEN;
    ctl |= txconfig;
    /* configure transfer mode */
    USART_CTL0(usart_periph) = ctl;
}

/*!
    \brief      configure USART receiver
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  rtconfig: enable or disable USART receiver
      \arg        USART_RECEIVE_ENABLE: enable USART reception
      \arg        USART_RECEIVE_DISABLE: disable USART reception
    \param[out] none
    \retval     none
*/
void usart_receive_config(uint32_t usart_periph, uint32_t rxconfig)
{
    uint32_t ctl = 0U;
    
    ctl = USART_CTL0(usart_periph);
    ctl &= ~USART_CTL0_REN;
    ctl |= rxconfig;
    /* configure transfer mode */
    USART_CTL0(usart_periph) = ctl;
}

/*!
    \brief      data is transmitted/received with the LSB/MSB first
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  msbf: LSB/MSB
      \arg        USART_MSBF_LSB: LSB first
      \arg        USART_MSBF_MSB: MSB first
    \param[out] none
    \retval     none
*/
void usart_data_first_config(uint32_t usart_periph, uint32_t msbf)
{
    USART_CTL3(usart_periph) &= ~(USART_CTL3_MSBF); 
    USART_CTL3(usart_periph) |= msbf;
}

/*!
    \brief      configure USART inversion
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  invertpara: refer to enum USART_INVERT_CONFIG
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
    switch(invertpara){
    case USART_DINV_ENABLE:
        USART_CTL3(usart_periph) |= USART_CTL3_DINV;
        break;
    case USART_TXPIN_ENABLE:
        USART_CTL3(usart_periph) |= USART_CTL3_TINV;
        break;
    case USART_RXPIN_ENABLE:
        USART_CTL3(usart_periph) |= USART_CTL3_RINV;
        break;
    case USART_DINV_DISABLE:
        USART_CTL3(usart_periph) &= ~(USART_CTL3_DINV);
        break;
    case USART_TXPIN_DISABLE:
        USART_CTL3(usart_periph) &= ~(USART_CTL3_TINV);
        break;
    case USART_RXPIN_DISABLE:
        USART_CTL3(usart_periph) &= ~(USART_CTL3_RINV);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the USART oversample mode 
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  oversamp: oversample value
      \arg        USART_OVSMOD_8: 8 bits
      \arg        USART_OVSMOD_16: 16 bits
    \param[out] none
    \retval     none
*/
void usart_oversample_config(uint32_t usart_periph, uint32_t oversamp)
{
    /*  clear OVSMOD bit */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_OVSMOD);
    USART_CTL0(usart_periph) |= oversamp;
}

/*!
    \brief      configure sample bit method
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  obsm: sample bit
      \arg        USART_OSB_1bit: 1 bit
      \arg        USART_OSB_3bit: 3 bits
    \param[out] none
    \retval     none
*/
void usart_sample_bit_config(uint32_t usart_periph, uint32_t obsm)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_OSB); 
    USART_CTL2(usart_periph) |= obsm;
}

/*!
    \brief      enable receiver timeout of USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_receiver_timeout_enable(uint32_t usart_periph)
{
    USART_CTL3(usart_periph) |= USART_CTL3_RTEN;
}

/*!
    \brief      disable receiver timeout of USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_receiver_timeout_disable(uint32_t usart_periph)
{
    USART_CTL3(usart_periph) &= ~(USART_CTL3_RTEN);
}

/*!
    \brief      set the receiver timeout threshold of USART
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  rtimeout: 0-0x00FFFFFF
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
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  data: data of transmission 
    \param[out] none
    \retval     none
*/
void usart_data_transmit(uint32_t usart_periph, uint32_t data)
{
    USART_DATA(usart_periph) = ((uint16_t)USART_DATA_DATA & data);
}

/*!
    \brief      USART receive data function
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     data of received
*/
uint16_t usart_data_receive(uint32_t usart_periph)
{
    return (uint16_t)(USART_DATA(usart_periph) & (uint16_t)USART_DATA_DATA); 
}

/*!
    \brief      configure the address of the USART in wake up by address match mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  addr: address of USART/UART
    \param[out] none
    \retval     none
*/
void usart_address_config(uint32_t usart_periph, uint8_t addr)
{
    USART_CTL1(usart_periph) &= ~(USART_CTL1_ADDR);
    USART_CTL1(usart_periph) |= (USART_CTL1_ADDR & addr);
}

/*!
    \brief      receiver in mute mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_mute_mode_enable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) |= USART_CTL0_RWU;
}

/*!
    \brief      receiver in active mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_mute_mode_disable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_RWU);
}

/*!
    \brief      configure wakeup method in mute mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  wmehtod: two method be used to enter or exit the mute mode
      \arg        USART_WM_IDLE: idle line
      \arg        USART_WM_ADDR: address mask
    \param[out] none
    \retval     none
*/
void usart_mute_mode_wakeup_config(uint32_t usart_periph, uint32_t wmehtod)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_WM);
    USART_CTL0(usart_periph) |= wmehtod;
}

/*!
    \brief      enable LIN mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_lin_mode_enable(uint32_t usart_periph)
{   
    USART_CTL1(usart_periph) |= USART_CTL1_LMEN;
}

/*!
    \brief      disable LIN mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_lin_mode_disable(uint32_t usart_periph)
{   
    USART_CTL1(usart_periph) &= ~(USART_CTL1_LMEN);
}

/*!
    \brief      configure lin break frame length
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  lblen: lin break frame length
      \arg        USART_LBLEN_10B: 10 bits
      \arg        USART_LBLEN_11B: 11 bits
    \param[out] none
    \retval     none
*/
void usart_lin_break_dection_length_config(uint32_t usart_periph, uint32_t lblen)
{
    USART_CTL1(usart_periph) &= ~(USART_CTL1_LBLEN);
    USART_CTL1(usart_periph) |= (USART_CTL1_LBLEN & lblen);
}

/*!
    \brief      send break frame
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_send_break(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) |= USART_CTL0_SBKCMD;
}

/*!
    \brief      enable half duplex mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_halfduplex_enable(uint32_t usart_periph)
{   
    USART_CTL2(usart_periph) |= USART_CTL2_HDEN;
}

/*!
    \brief      disable half duplex mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_halfduplex_disable(uint32_t usart_periph)
{  
    USART_CTL2(usart_periph) &= ~(USART_CTL2_HDEN);
}

/*!
    \brief      enable CK pin in synchronous mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_synchronous_clock_enable(uint32_t usart_periph)
{
    USART_CTL1(usart_periph) |= USART_CTL1_CKEN;
}

/*!
    \brief      disable CK pin in synchronous mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_synchronous_clock_disable(uint32_t usart_periph)
{
    USART_CTL1(usart_periph) &= ~(USART_CTL1_CKEN);
}

/*!
    \brief      configure USART synchronous mode parameters
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  clen: CK length
      \arg        USART_CLEN_NONE: there are 7 CK pulses for an 8 bit frame and 8 CK pulses for a 9 bit frame 
      \arg        USART_CLEN_EN:   there are 8 CK pulses for an 8 bit frame and 9 CK pulses for a 9 bit frame
    \param[in]  cph: clock phase
      \arg        USART_CPH_1CK: first clock transition is the first data capture edge 
      \arg        USART_CPH_2CK: second clock transition is the first data capture edge
    \param[in]  cpl: clock polarity 
      \arg        USART_CPL_LOW:  steady low value on CK pin 
      \arg        USART_CPL_HIGH: steady high value on CK pin
    \param[out] none
    \retval     none
*/
void usart_synchronous_clock_config(uint32_t usart_periph, uint32_t clen, uint32_t cph, uint32_t cpl)
{
    uint32_t ctl = 0U;
    
    /* read USART_CTL1 register */
    ctl = USART_CTL1(usart_periph);
    /* set CK length, CK phase, CK polarity */
    ctl |= (USART_CTL1_CLEN & clen) | (USART_CTL1_CPH & cph) | (USART_CTL1_CPL & cpl);

    USART_CTL1(usart_periph) |= ctl;
}

/*!
    \brief      configure guard time value in smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  gaut: guard time value
    \param[out] none
    \retval     none
*/
void usart_guard_time_config(uint32_t usart_periph,uint32_t gaut)
{
    USART_GP(usart_periph) &= ~(USART_GP_GUAT);
    USART_GP(usart_periph) |= (USART_GP_GUAT & ((gaut)<<8));
}

/*!
    \brief      enable smartcard mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_enable(uint32_t usart_periph)
{
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
    USART_CTL2(usart_periph) &= ~(USART_CTL2_NKEN);
}

/*!
    \brief      configure smartcard auto-retry number
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  scrtnum: smartcard auto-retry number
    \param[out] none
    \retval     none
*/
void usart_smartcard_autoretry_config(uint32_t usart_periph, uint32_t scrtnum)
{
    USART_CTL3(usart_periph) &= ~(USART_CTL3_SCRTNUM);
    USART_CTL3(usart_periph) |= (USART_CTL3_SCRTNUM & ((scrtnum)<<1));
}

/*!
    \brief      configure block length in Smartcard T=1 reception
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  bl: block length
    \param[out] none
    \retval     none
*/
void usart_block_length_config(uint32_t usart_periph, uint32_t bl)
{
    USART_RT(usart_periph) &= ~(USART_RT_BL);
    USART_RT(usart_periph) |= (USART_RT_BL & ((bl)<<24));
}

/*!
    \brief      enable IrDA mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_irda_mode_enable(uint32_t usart_periph)
{
    USART_CTL2(usart_periph) |= USART_CTL2_IREN;
}

/*!
    \brief      disable IrDA mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[out] none
    \retval     none
*/
void usart_irda_mode_disable(uint32_t usart_periph)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_IREN);
}

/*!
    \brief      configure the peripheral clock prescaler in USART IrDA low-power mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  psc: 0-0x00FFFFFF
    \param[out] none
    \retval     none
*/
void usart_prescaler_config(uint32_t usart_periph, uint32_t psc)
{
    USART_GP(usart_periph) &= ~(USART_GP_PSC);
    USART_GP(usart_periph) |= psc;
}

/*!
    \brief      configure IrDA low-power
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  irlp: IrDA low-power or normal
      \arg        USART_IRLP_LOW:    low-power
      \arg        USART_IRLP_NORMAL: normal
    \param[out] none
    \retval     none
*/
void usart_irda_lowpower_config(uint32_t usart_periph, uint32_t irlp)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_IRLP);
    USART_CTL2(usart_periph) |= (USART_CTL2_IRLP & irlp);
}

/*!
    \brief      configure hardware flow control RTS
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  hardwareflow: enable or disable RTS
      \arg        USART_RTS_ENABLE:  enable RTS
      \arg        USART_RTS_DISABLE: disable RTS
    \param[out] none
    \retval     none
*/
void usart_hardware_flow_rts_config(uint32_t usart_periph, uint32_t rtsconfig)
{
    uint32_t ctl = 0U;
    
    ctl = USART_CTL2(usart_periph);
    ctl &= ~USART_CTL2_RTSEN;
    ctl |= rtsconfig;
    /* configure RTS */
    USART_CTL2(usart_periph) = ctl;
}

/*!
    \brief      configure hardware flow control CTS
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  hardwareflow: enable or disable CTS
      \arg        USART_CTS_ENABLE:  enable CTS
      \arg        USART_CTS_DISABLE: disable CTS
    \param[out] none
    \retval     none
*/
void usart_hardware_flow_cts_config(uint32_t usart_periph, uint32_t ctsconfig)
{
    uint32_t ctl = 0U;
    
    ctl = USART_CTL2(usart_periph);
    ctl &= ~USART_CTL2_CTSEN;
    ctl |= ctsconfig;
    /* configure CTS */
    USART_CTL2(usart_periph) = ctl;
}

/*!
    \brief      configure break frame coherence mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  bcm: 
      \arg        USART_BCM_NONE: no parity error is detected
      \arg        USART_BCM_EN:   parity error is detected
    \param[out] none
    \retval     none
*/
void usart_break_frame_coherence_config(uint32_t usart_periph, uint32_t bcm)
{
    USART_CHC(usart_periph) &= ~(USART_CHC_BCM);
    USART_CHC(usart_periph) |= (USART_CHC_BCM & bcm);
}

/*!
    \brief      configure parity check coherence mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  pcm: 
      \arg        USART_PCM_NONE: not check parity
      \arg        USART_PCM_EN:   check the parity
    \param[out] none
    \retval     none
*/
void usart_parity_check_coherence_config(uint32_t usart_periph, uint32_t pcm)
{
    USART_CHC(usart_periph) &= ~(USART_CHC_PCM);
    USART_CHC(usart_periph) |= (USART_CHC_PCM & pcm);
}

/*!
    \brief      configure hardware flow control coherence mode
    \param[in]  usart_periph: USARTx(x=0,1,2,5)
    \param[in]  hcm: 
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
    \brief      configure USART DMA reception
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  dmacmd: enable or disable DMA for reception
      \arg        USART_DENR_ENABLE:  DMA enable for reception
      \arg        USART_DENR_DISABLE: DMA disable for reception
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
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  dmacmd: enable or disable DMA for transmission
      \arg        USART_DENT_ENABLE:  DMA enable for transmission
      \arg        USART_DENT_DISABLE: DMA disable for transmission
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
    \brief      get flag in STAT0/STAT1/CHC register
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  flag: USART flags, refer to usart_flag_enum
      \arg        USART_FLAG_CTSF: CTS change flag
      \arg        USART_FLAG_LBDF: LIN break detected flag 
      \arg        USART_FLAG_TBE: transmit data buffer empty 
      \arg        USART_FLAG_TC: transmission complete 
      \arg        USART_FLAG_RBNE: read data buffer not empty 
      \arg        USART_FLAG_IDLEF: IDLE frame detected flag 
      \arg        USART_FLAG_ORERR: overrun error 
      \arg        USART_FLAG_NERR: noise error flag 
      \arg        USART_FLAG_FERR: frame error flag 
      \arg        USART_FLAG_PERR: parity error flag 
      \arg        USART_FLAG_BSY: busy flag 
      \arg        USART_FLAG_EBF: end of block flag 
      \arg        USART_FLAG_RTF: receiver timeout flag 
      \arg        USART_FLAG_EPERR: early parity error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus usart_flag_get(uint32_t usart_periph, usart_flag_enum flag)
{
    if(RESET != (USART_REG_VAL(usart_periph, flag) & BIT(USART_BIT_POS(flag)))){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear flag in STAT0/STAT1/CHC register
    \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  flag: USART flags, refer to usart_flag_enum
      \arg        USART_FLAG_CTSF: CTS change flag
      \arg        USART_FLAG_LBDF: LIN break detected flag
      \arg        USART_FLAG_TC: transmission complete
      \arg        USART_FLAG_RBNE: read data buffer not empty
      \arg        USART_FLAG_EBF: end of block flag
      \arg        USART_FLAG_RTF: receiver timeout flag
      \arg        USART_FLAG_EPERR: early parity error flag
    \param[out] none
    \retval     none
*/
void usart_flag_clear(uint32_t usart_periph, usart_flag_enum flag)
{
    USART_REG_VAL(usart_periph, flag) &= ~BIT(USART_BIT_POS(flag));
}

/*!
    \brief      enable USART interrupt
     \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  int_flag
      \arg        USART_INTEN_PERRIE: parity error interrupt
      \arg        USART_INTEN_TBEIE: transmitter buffer empty interrupt
      \arg        USART_INTEN_TCIE: transmission complete interrupt
      \arg        USART_INTEN_RBNEIE: read data buffer not empty interrupt and overrun error interrupt
      \arg        USART_INTEN_IDLEIE: IDLE line detected interrupt
      \arg        USART_INTEN_LBDIE: LIN break detected interrupt
      \arg        USART_INTEN_ERRIE: error interrupt
      \arg        USART_INTEN_CTSIE: CTS interrupt
      \arg        USART_INTEN_RTIE: interrupt enable bit of receive timeout event
      \arg        USART_INTEN_EBIE: interrupt enable bit of end of block event
    \param[out] none
*/
void usart_interrupt_enable(uint32_t usart_periph, uint32_t int_flag)
{
    uint32_t usart_reg = 0U;
    
    usart_reg = int_flag & (~(uint32_t)USART_INTEN_MASK);
    int_flag &= USART_INTEN_MASK;
    /* flags in USART_CTL0 */
    if(USART_INTS_CTL0 == usart_reg){
        USART_CTL0(usart_periph) |= int_flag;
    /* flags in USART_CTL1 */
    }else if(USART_INTS_CTL1 == usart_reg){
        USART_CTL1(usart_periph) |= int_flag;
    /* flags in USART_CTL2 */
    }else if(USART_INTS_CTL2 == usart_reg){
        USART_CTL2(usart_periph) |= int_flag;
    /* flags in USART_CTL3 */
    }else if(USART_INTS_CTL3 == usart_reg){
        USART_CTL3(usart_periph) |= int_flag;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      disable USART interrupt
     \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  int_flag
      \arg        USART_INTEN_PERRIE: parity error interrupt
      \arg        USART_INTEN_TBEIE: transmitter buffer empty interrupt
      \arg        USART_INTEN_TCIE: transmission complete interrupt
      \arg        USART_INTEN_RBNEIE: read data buffer not empty interrupt and overrun error interrupt
      \arg        USART_INTEN_IDLEIE: IDLE line detected interrupt
      \arg        USART_INTEN_LBDIE: LIN break detected interrupt
      \arg        USART_INTEN_ERRIE: error interrupt
      \arg        USART_INTEN_CTSIE: CTS interrupt
      \arg        USART_INTEN_RTIE: interrupt enable bit of receive timeout event
      \arg        USART_INTEN_EBIE: interrupt enable bit of end of block event
    \param[out] none
*/
void usart_interrupt_disable(uint32_t usart_periph, uint32_t int_flag)
{
    uint32_t usart_reg = 0U;
    
    usart_reg = int_flag & (~(uint32_t)USART_INTEN_MASK);
    int_flag &= USART_INTEN_MASK;
    /* flags in USART_CTL0 */
    if(USART_INTS_CTL0 == usart_reg){
        USART_CTL0(usart_periph) &= ~(int_flag);
    /* flags in USART_CTL1 */
    }else if(USART_INTS_CTL1 == usart_reg){
        USART_CTL1(usart_periph) &= ~(int_flag);
    /* flags in USART_CTL2 */
    }else if(USART_INTS_CTL2 == usart_reg){
        USART_CTL2(usart_periph) &= ~(int_flag);
    /* flags in USART_CTL3 */
    }else if(USART_INTS_CTL3 == usart_reg){
        USART_CTL3(usart_periph) &= ~(int_flag);
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      get USART interrupt enable flag
     \param[in]  usart_periph: USARTx(x=0,1,2,5)/UARTx(x=3,4,6,7)
    \param[in]  int_flag
      \arg        USART_INT_PERRIE: parity error interrupt
      \arg        USART_INT_TBEIE: transmitter buffer empty interrupt
      \arg        USART_INT_TCIE: transmission complete interrupt
      \arg        USART_INT_RBNEIE: read data buffer not empty interrupt and overrun error interrupt
      \arg        USART_INT_IDLEIE: IDLE line detected interrupt
      \arg        USART_INT_LBDIE: LIN break detected interrupt
      \arg        USART_INT_CTSIE: CTS interrupt
      \arg        USART_INT_ERRIE: error interrupt
      \arg        USART_INT_EBIE: interrupt enable bit of end of block event
      \arg        USART_INT_RTIE: interrupt enable bit of receive timeout event
    \param[out] none
    \retval     FlagStatus
*/
FlagStatus usart_interrupt_flag_get(uint32_t usart_periph, uint32_t int_flag)
{
    if(RESET != (USART_REG_VAL(usart_periph, int_flag) & BIT(USART_BIT_POS(int_flag)))){
        return SET;
    }else{
        return RESET;
    }
}

