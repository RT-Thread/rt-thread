/*!
    \file  gd32f3x0_cec.c
    \brief CEC driver
    
    \version 2017-06-06, V1.0.0, firmware for GD32F3x0
    \version 2019-06-01, V2.0.0, firmware for GD32F3x0
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

#ifdef GD32F350

#include "gd32f3x0_cec.h"

/*!
    \brief      reset HDMI-CEC controller
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cec_deinit(void)
{
    rcu_periph_reset_enable(RCU_CECRST);
    rcu_periph_reset_disable(RCU_CECRST);
}

/*!
    \brief      configure signal free time,the signal free time counter start option,own address 
    \param[in]  sftmopt: signal free time counter start option
                only one parameter can be selected which is shown as below:
      \arg        CEC_SFT_START_STAOM: signal free time counter starts counting when STAOM is asserted
      \arg        CEC_SFT_START_LAST: signal free time counter starts automatically after transmission/reception end
    \param[in]  sft: signal free time
                only one parameter can be selected which is shown as below:
      \arg        CEC_SFT_PROTOCOL_PERIOD: the signal free time will perform as HDMI-CEC protocol description
      \arg        CEC_SFT_1POINT5_PERIOD: 1.5 nominal data bit periods
      \arg        CEC_SFT_2POINT5_PERIOD: 2.5 nominal data bit periods
      \arg        CEC_SFT_3POINT5_PERIOD: 3.5 nominal data bit periods
      \arg        CEC_SFT_4POINT5_PERIOD: 4.5 nominal data bit periods
      \arg        CEC_SFT_5POINT5_PERIOD: 5.5 nominal data bit periods
      \arg        CEC_SFT_6POINT5_PERIOD: 6.5 nominal data bit periods
      \arg        CEC_SFT_7POINT5_PERIOD: 7.5 nominal data bit periods
    \param[in]  address: own address
                only one parameter can be selected which is shown as below:
      \arg        CEC_OWN_ADDRESS_CLEAR: own address is cleared
      \arg        CEC_OWN_ADDRESSx(x=0..14): own address is x
    \param[out] none
    \retval     none
*/
void cec_init(uint32_t sftmopt, uint32_t sft, uint32_t address)
{
    uint32_t cfg;
    cfg = CEC_CFG;
    /* clear SFTMOPT bit,SFT[2:0] */
    cfg &= ~(CEC_CFG_SFTOPT | CEC_CFG_SFT);
    /* assign SFTMOPT bit,SFT[2:0] */
    cfg |= (sftmopt | sft);
    CEC_CFG = cfg;
    if(CEC_OWN_ADDRESS_CLEAR == address){
        CEC_CFG &= ~CEC_CFG_OWN_ADDRESS;
    }else{
        CEC_CFG |= address;
    }
}

/*!
    \brief      configure generate Error-bit when detected some abnormal situation or not,
                whether stop receive message when detected bit rising error
    \param[in]  broadcast:
                only one parameter can be selected which is shown as below:
      \arg        CEC_BROADCAST_ERROR_BIT_ON:generate Error-bit in broadcast
      \arg        CEC_BROADCAST_ERROR_BIT_OFF:do not generate Error-bit in broadcast
    \param[in]  singlecast_lbpe:
                only one parameter can be selected which is shown as below:
      \arg        CEC_LONG_PERIOD_ERROR_BIT_ON:generate Error-bit on long bit period error
      \arg        CEC_LONG_PERIOD_ERROR_BIT_OFF:do not generate Error-bit on long bit period error
    \param[in]  singlecast_bre:
                only one parameter can be selected which is shown as below:
      \arg        CEC_RISING_PERIOD_ERROR_BIT_ON:generate Error-bit on bit rising error
      \arg        CEC_RISING_PERIOD_ERROR_BIT_OFF:do not generate Error-bit on bit rising error
    \param[in]  rxbrestp:
                only one parameter can be selected which is shown as below:
      \arg        CEC_STOP_RISING_ERROR_BIT_ON: stop reception when detected bit rising error
      \arg        CEC_STOP_RISING_ERROR_BIT_OFF: do not stop reception when detected bit rising error
    \param[out] none
    \retval     none
*/
void cec_error_config(uint32_t broadcast, uint32_t singlecast_lbpe, uint32_t singlecast_bre, uint32_t rxbrestp)
{
    uint32_t cfg;
    cfg = CEC_CFG;
    /* clear BCNG bit, BPLEG bit, BREG bit */
    cfg &= ~(CEC_CFG_BCNG | CEC_CFG_BPLEG | CEC_CFG_BREG);
    /* assign BCNG bit, BPLEG bit, BREG bit */
    cfg |= (broadcast | singlecast_lbpe | singlecast_bre);
    CEC_CFG = cfg;
    if(CEC_STOP_RISING_ERROR_BIT_ON == rxbrestp){
        CEC_CFG |= CEC_CFG_BRES;
    }else{
        CEC_CFG &= ~CEC_CFG_BRES;
    }
}

/*!
    \brief      enable HDMI-CEC controller
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cec_enable(void)
{
    CEC_CTL |= CEC_CTL_CECEN;
}

/*!
    \brief      disable HDMI-CEC controller
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cec_disable(void)
{
    CEC_CTL &= ~CEC_CTL_CECEN;
}

/*!
    \brief      start CEC message transmission 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cec_transmission_start(void)
{
    CEC_CTL |= CEC_CTL_STAOM;
}

/*!
    \brief      end CEC message transmission
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cec_transmission_end(void)
{
    CEC_CTL |= CEC_CTL_ENDOM;
}

/*!
    \brief      enable CEC listen mode.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cec_listen_mode_enable(void)
{
    CEC_CFG |= CEC_CFG_LMEN;
}

/*!
    \brief      disable CEC listen mode.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cec_listen_mode_disable(void)
{
    CEC_CFG &= ~CEC_CFG_LMEN;
}

/*!
    \brief      configure and clear own address.the controller can be configured to multiple own address 
    \param[in]  address: own address
                one or more parameters can be selected which are shown as below:
      \arg        CEC_OWN_ADDRESS_CLEAR: own address is cleared
      \arg        CEC_OWN_ADDRESSx(x=0..14): own address is x
    \param[out] none
    \retval     none
*/
void cec_own_address_config(uint32_t address)
{
    if(CEC_OWN_ADDRESS_CLEAR == address){
        CEC_CFG &= ~CEC_CFG_OWN_ADDRESS;
    } else {
        CEC_CFG |= address;
    }
}

/*!
    \brief      configure signal free time and the signal free time counter start option 
    \param[in]  sftmopt: signal free time counter start option
                only one parameter can be selected which is shown as below:
      \arg        CEC_SFT_START_STAOM: signal free time counter starts counting when STAOM is asserted
      \arg        CEC_SFT_START_LAST: signal free time counter starts automatically after transmission/reception end
    \param[in]  sft: signal free time
                only one parameter can be selected which is shown as below:
      \arg        CEC_SFT_PROTOCOL_PERIOD: the signal free time will perform as HDMI-CEC protocol description
      \arg        CEC_SFT_1POINT5_PERIOD: 1.5 nominal data bit periods
      \arg        CEC_SFT_2POINT5_PERIOD: 2.5 nominal data bit periods
      \arg        CEC_SFT_3POINT5_PERIOD: 3.5 nominal data bit periods
      \arg        CEC_SFT_4POINT5_PERIOD: 4.5 nominal data bit periods
      \arg        CEC_SFT_5POINT5_PERIOD: 5.5 nominal data bit periods
      \arg        CEC_SFT_6POINT5_PERIOD: 6.5 nominal data bit periods
      \arg        CEC_SFT_7POINT5_PERIOD: 7.5 nominal data bit periods
    \param[out] none
    \retval     none
*/
void cec_sft_config(uint32_t sftmopt, uint32_t sft)
{
    uint32_t cfg;
    cfg = CEC_CFG;
    /* clear SFTMOPT bit,SFT[2:0] */
    cfg &= ~(CEC_CFG_SFTOPT | CEC_CFG_SFT);
    /* assign SFTMOPT bit,SFT[2:0] */
    cfg |= (sftmopt | sft);
    CEC_CFG = cfg;
}

/*!
    \brief      configure generate Error-bit when detected some abnormal situation or not
    \param[in]  broadcast:
                only one parameter can be selected which is shown as below:
      \arg        CEC_BROADCAST_ERROR_BIT_ON:generate Error-bit in broadcast
      \arg        CEC_BROADCAST_ERROR_BIT_OFF:do not generate Error-bit in broadcast
    \param[in]  singlecast_lbpe:
                only one parameter can be selected which is shown as below:
      \arg        CEC_LONG_PERIOD_ERROR_BIT_ON:generate Error-bit on long bit period error
      \arg        CEC_LONG_PERIOD_ERROR_BIT_OFF:do not generate Error-bit on long bit period error
    \param[in]  singlecast_bre:
                only one parameter can be selected which is shown as below:
      \arg        CEC_RISING_PERIOD_ERROR_BIT_ON:generate Error-bit on bit rising error
      \arg        CEC_RISING_PERIOD_ERROR_BIT_OFF:do not generate Error-bit on bit rising error
    \param[out] none
    \retval     none
*/
void cec_generate_errorbit_config(uint32_t broadcast, uint32_t singlecast_lbpe, uint32_t singlecast_bre)
{
    uint32_t cfg;
    cfg = CEC_CFG;
    /* clear BCNG bit, RLBPEGEN bit, RBREGEN bit */
    cfg &= ~(CEC_CFG_BCNG | CEC_CFG_BPLEG | CEC_CFG_BREG);
    /* assign BCNG bit, RLBPEGEN bit, RBREGEN bit */
    cfg |= (broadcast | singlecast_lbpe | singlecast_bre);
    CEC_CFG = cfg;
}

/*!
    \brief      whether stop receive message when detected bit rising error
    \param[in]  rxbrestp:
                only one parameter can be selected which is shown as below:
      \arg        CEC_STOP_RISING_ERROR_BIT_ON: stop reception when detected bit rising error
      \arg        CEC_STOP_RISING_ERROR_BIT_OFF: do not stop reception when detected bit rising error
    \param[out] none
    \retval     none
*/
void cec_stop_receive_bre_config(uint32_t rxbrestp)
{
    if(CEC_STOP_RISING_ERROR_BIT_ON == rxbrestp){
        CEC_CFG |= CEC_CFG_BRES;
    } else {
        CEC_CFG &= ~CEC_CFG_BRES;
    }
}

/*!
    \brief      enable reception bit timing tolerance
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cec_reception_tolerance_enable(void)
{
    CEC_CFG |= CEC_CFG_RTOL;
}

/*!
    \brief      disable reception bit timing tolerance
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cec_reception_tolerance_disable(void)
{
    CEC_CFG &= ~CEC_CFG_RTOL;
}

/*!
    \brief      send a data by the CEC peripheral
    \param[in]  data: the data to transmit
    \param[out] none
    \retval     none
*/
void cec_data_send(uint8_t data)
{
    CEC_TDATA = (uint32_t)data;
}

/*!
    \brief      receive a data by the CEC peripheral
    \param[in]  data: the data to receive
    \param[out] none
    \retval     none
*/
uint8_t cec_data_receive(void)
{
    return (uint8_t)CEC_RDATA;
}


/*!
    \brief      enable interrupt
    \param[in]  flag: specify which flag
                one or more parameters can be selected which are shown as below:
      \arg        CEC_INT_BR: enable Rx-byte data received interrupt
      \arg        CEC_INT_REND: enable end of reception interrupt
      \arg        CEC_INT_RO: enable RX overrun interrupt
      \arg        CEC_INT_BRE: enable bit rising error interrupt
      \arg        CEC_INT_BPSE: enable short bit period error interrupt
      \arg        CEC_INT_BPLE: enable long bit period error interrupt
      \arg        CEC_INT_RAE: enable Rx ACK error interrupt
      \arg        CEC_INT_ARBF: enable arbitration lost interrupt
      \arg        CEC_INT_TBR: enable Tx-byte data request interrupt
      \arg        CEC_INT_TEND: enable transmission successfully end interrupt
      \arg        CEC_INT_TU: enable Tx data buffer underrun interrupt
      \arg        CEC_INT_TERR: enable Tx-error interrupt 
      \arg        CEC_INT_TAERR: enable Tx ACK error interrupt
    \param[out] none
    \retval     none
*/
void cec_interrupt_enable(uint32_t flag)
{
    CEC_INTEN |= flag;
}

/*!
    \brief      disable interrupt
    \param[in]  flag: specify which flag
                one or more parameters can be selected which are shown as below:
      \arg        CEC_INT_BR: disable Rx-byte data received interrupt
      \arg        CEC_INT_REND: disable end of reception interrupt
      \arg        CEC_INT_RO: disable RX overrun interrupt
      \arg        CEC_INT_BRE: disable bit rising error interrupt
      \arg        CEC_INT_BPSE: disable short bit period error interrupt
      \arg        CEC_INT_BPLE: disable long bit period error interrupt
      \arg        CEC_INT_RAE: disable Rx ACK error interrupt
      \arg        CEC_INT_ARBF: disable arbitration lost interrupt
      \arg        CEC_INT_TBR: disable Tx-byte data request interrupt
      \arg        CEC_INT_TEND: disable transmission successfully end interrupt
      \arg        CEC_INT_TU: disable Tx data buffer underrun interrupt
      \arg        CEC_INT_TERR: disable Tx-error interrupt 
      \arg        CEC_INT_TAERR: disable Tx ACK error  interrupt

    \param[out] none
    \retval     none
*/
void cec_interrupt_disable(uint32_t flag)
{
    CEC_INTEN &= ~flag;
}


/*!
    \brief      get CEC status
    \param[in]  flag:  specify which flag
                one or more parameters can be selected which are shown as below:
      \arg        CEC_FLAG_BR: Rx-byte data received
      \arg        CEC_FLAG_REND: end of reception
      \arg        CEC_FLAG_RO: RX overrun
      \arg        CEC_FLAG_BRE: bit rising error
      \arg        CEC_FLAG_BPSE: short bit period error
      \arg        CEC_FLAG_BPLE: long bit period error
      \arg        CEC_FLAG_RAE: Rx ACK error
      \arg        CEC_FLAG_ARBF: arbitration lost
      \arg        CEC_FLAG_TBR: Tx-byte data request
      \arg        CEC_FLAG_TEND: transmission successfully end
      \arg        CEC_FLAG_TU: Tx data buffer underrun
      \arg        CEC_FLAG_TERR: Tx-error
      \arg        CEC_FLAG_TAERR Tx ACK error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cec_flag_get(uint32_t flag)
{
    if(CEC_INTF & flag){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CEC status
    \param[in]  flag:  specify which flag
                one or more parameters can be selected which are shown as below:
      \arg        CEC_FLAG_BR: Rx-byte data received
      \arg        CEC_FLAG_REND: end of reception
      \arg        CEC_FLAG_RO: RX overrun
      \arg        CEC_FLAG_BRE: bit rising error
      \arg        CEC_FLAG_BPSE: short bit period error
      \arg        CEC_FLAG_BPLE: long bit period error
      \arg        CEC_FLAG_RAE: Rx ACK error
      \arg        CEC_FLAG_ARBF: arbitration lost
      \arg        CEC_FLAG_TBR: Tx-byte data request
      \arg        CEC_FLAG_TEND: transmission successfully end
      \arg        CEC_FLAG_TU: Tx data buffer underrun
      \arg        CEC_FLAG_TERR: Tx-error
      \arg        CEC_FLAG_TAERR: Tx ACK error flag

    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
void cec_flag_clear(uint32_t flag)
{
    CEC_INTF |= flag;
}

/*!
    \brief      get CEC int flag and status
    \param[in]  flag:  specify which flag
                one or more parameters can be selected which are shown as below:
      \arg        CEC_INT_FLAG_BR: Rx-byte data received
      \arg        CEC_INT_FLAG_REND: end of reception
      \arg        CEC_INT_FLAG_RO: RX overrun
      \arg        CEC_INT_FLAG_BRE: bit rising error
      \arg        CEC_INT_FLAG_BPSE: short bit period error
      \arg        CEC_INT_FLAG_BPLE: long bit period error
      \arg        CEC_INT_FLAG_RAE: Rx ACK error
      \arg        CEC_INT_FLAG_ARBF: arbitration lost
      \arg        CEC_INT_FLAG_TBR: Tx-byte data request
      \arg        CEC_INT_FLAG_TEND: transmission successfully end
      \arg        CEC_INT_FLAG_TU: Tx data buffer underrun
      \arg        CEC_INT_FLAG_TERR: Tx-error
      \arg        CEC_INT_FLAG_TAERR: Tx ACK error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cec_interrupt_flag_get(uint32_t flag)
{
    uint32_t interrupt_enable = 0U,interrupt_flag = 0U;
    interrupt_flag = (CEC_INTF & flag);
    interrupt_enable = (CEC_INTEN & flag);
    if(interrupt_flag && interrupt_enable){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CEC int flag and status
    \param[in]  flag:  specify which flag
                one or more parameters can be selected which are shown as below:
      \arg        CEC_INT_FLAG_BR: Rx-byte data received
      \arg        CEC_INT_FLAG_REND: end of reception
      \arg        CEC_INT_FLAG_RO: RX overrun
      \arg        CEC_INT_FLAG_BRE: bit rising error
      \arg        CEC_INT_FLAG_BPSE: short bit period error
      \arg        CEC_INT_FLAG_BPLE: long bit period error
      \arg        CEC_INT_FLAG_RAE: Rx ACK error
      \arg        CEC_INT_FLAG_ARBF: arbitration lost
      \arg        CEC_INT_FLAG_TBR: Tx-byte data request
      \arg        CEC_INT_FLAG_TEND: transmission successfully end
      \arg        CEC_INT_FLAG_TU: Tx data buffer underrun
      \arg        CEC_INT_FLAG_TERR: Tx-error
      \arg        CEC_INT_FLAG_TAERR: Tx ACK error flag
    \param[out] none
    \retval     none
*/
void cec_interrupt_flag_clear(uint32_t flag)
{
    CEC_INTF = flag;
}


#endif
