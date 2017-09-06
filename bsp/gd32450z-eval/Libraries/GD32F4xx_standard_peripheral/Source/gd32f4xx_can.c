/*!
    \file  gd32f4xx_can.c
    \brief CAN driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_can.h"

/*!
    \brief      deinitialize CAN 
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     none
*/
void can_deinit(uint32_t can_periph)
{
    if(CAN0 == can_periph){
        rcu_periph_reset_enable(RCU_CAN0RST);
        rcu_periph_reset_disable(RCU_CAN0RST);
    }else{
        rcu_periph_reset_enable(RCU_CAN1RST);
        rcu_periph_reset_disable(RCU_CAN1RST);
    }
}

/*!
    \brief      initialize CAN
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  can_parameter_struct: parameters for CAN initializtion
                  can_mode: CAN_NORMAL_MODE, CAN_LOOPBACK_MODE, CAN_SILENT_MODE, CAN_SILENT_LOOPBACK_MODE
                  can_sjw: CAN_BT_SJW_xTQ(x=1, 2, 3, 4)
                  can_bs1: CAN_BT_BS1_xTQ(1..16)
                  can_bs2: CAN_BT_BS2_xTQ(1..8)
                  can_ttc: ENABLE or DISABLE
                  can_abor: ENABLE or DISABLE
                  can_awu: ENABLE or DISABLE
                  can_ard: ENABLE or DISABLE
                  can_rfod: ENABLE or DISABLE
                  can_tfo: ENABLE or DISABLE
                  can_psc: 0x0001 - 0x03FF
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_init(uint32_t can_periph, can_parameter_struct* can_parameter_init)
{
    uint32_t timeout = CAN_TIMEOUT;
    ErrStatus flag = ERROR;
    
    /* disable sleep mode */
    CAN_CTL(can_periph) &= ~CAN_CTL_SLPWMOD;
    /* enable initialize mode */
    CAN_CTL(can_periph) |= CAN_CTL_IWMOD;
    /* wait ACK */
    while((CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)) && (timeout)){
        timeout--;
    }
    /* check initialize working success */
    if(CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)){
        flag = ERROR;
    } else {
        /* set the bit timing register */
        CAN_BT(can_periph) = (BT_MODE((uint32_t)can_parameter_init->working_mode) | \
                              BT_SJW((uint32_t)can_parameter_init->resync_jump_width) | \
                              BT_BS1((uint32_t)can_parameter_init->time_segment_1) | \
                              BT_BS2((uint32_t)can_parameter_init->time_segment_2) | \
                              BT_BAUDPSC(((uint32_t)(can_parameter_init->prescaler) - 1U)));
        /* time trigger communication mode */
        if(ENABLE == can_parameter_init->time_triggered){
            CAN_CTL(can_periph) |= CAN_CTL_TTC;
        }else{
            CAN_CTL(can_periph) &= ~CAN_CTL_TTC;
        }
        /* automatic bus-off managment */
        if(ENABLE == can_parameter_init->auto_bus_off_recovery){
            CAN_CTL(can_periph) |= CAN_CTL_ABOR;
        }else{
            CAN_CTL(can_periph) &= ~CAN_CTL_ABOR;
        }
        /* automatic wakeup mode */
        if(ENABLE == can_parameter_init->auto_wake_up){
            CAN_CTL(can_periph) |= CAN_CTL_AWU;
        }else{
            CAN_CTL(can_periph) &= ~CAN_CTL_AWU;
        }
        /* automatic retransmission mode */
        if(ENABLE == can_parameter_init->auto_retrans){
            CAN_CTL(can_periph) |= CAN_CTL_ARD;
        }else{
            CAN_CTL(can_periph) &= ~CAN_CTL_ARD;
        }
        /* receive fifo overwrite mode */        
        if(ENABLE == can_parameter_init->rec_fifo_overwrite){
            CAN_CTL(can_periph) |= CAN_CTL_RFOD;
        }else{
            CAN_CTL(can_periph) &= ~CAN_CTL_RFOD;
        } 
        /* transmit fifo order */
        if(ENABLE == can_parameter_init->trans_fifo_order){
            CAN_CTL(can_periph) |= CAN_CTL_TFO;
        }else{
            CAN_CTL(can_periph) &= ~CAN_CTL_TFO;
        }  
        /* disable initialize mode */
        CAN_CTL(can_periph) &= ~CAN_CTL_IWMOD;
        timeout = CAN_TIMEOUT;
        /* wait the ACK */
        while((CAN_STAT_IWS == (CAN_STAT(can_periph) & CAN_STAT_IWS)) && (timeout)){
            timeout--;
        }
        /* check exit initialize mode */
        if(CAN_STAT_IWS == (CAN_STAT(can_periph) & CAN_STAT_IWS)){
            flag = SUCCESS;
        }
    }  
    return flag;
}

/*!
    \brief      initialize CAN filter 
    \param[in]  can_filter_parameter_struct: struct for CAN filter initialization
                  can_filter_list_high: 0x0000 - 0xFFFF
                  can_filter_list_low: 0x0000 - 0xFFFF
                  can_filter_mask_high: 0x0000 - 0xFFFF
                  can_filter_mask_low: 0x0000 - 0xFFFF
                  can_filter_fifo_number: CAN_FIFO0, CAN_FIFO1 
                  can_filter_number: 0 - 27
                  can_filter_mode: CAN_FILTERMODE_MASK, CAN_FILTERMODE_LIST
                  can_filter_bits: CAN_FILTERBITS_32BIT, CAN_FILTERBITS_16BIT 
                  can_filter_enable: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void can_filter_init(can_filter_parameter_struct* can_filter_parameter_init)
{
    uint32_t val = 0U;
    
    val = ((uint32_t)1) << (can_filter_parameter_init->filter_number);
    /* filter lock disable */
    CAN_FCTL(CAN0) |= CAN_FCTL_FLD;
    /* disable filter */
    CAN_FW(CAN0) &= ~(uint32_t)val;
    
    /* filter 16 bits */
    if(CAN_FILTERBITS_16BIT == can_filter_parameter_init->filter_bits){
        /* set filter 16 bits */
        CAN_FSCFG(CAN0) &= ~(uint32_t)val;
        /* first 16 bits list and  first 16 bits mask or first 16 bits list and  second 16 bits list */
        CAN_FDATA0(CAN0, can_filter_parameter_init->filter_number) = \
                                FDATA_MASK_HIGH((can_filter_parameter_init->filter_mask_low) & CAN_FILTER_MASK_16BITS) | \
                                FDATA_MASK_LOW((can_filter_parameter_init->filter_list_low) & CAN_FILTER_MASK_16BITS);
        /* second 16 bits list and  second 16 bits mask or third 16 bits list and  fourth 16 bits list */
        CAN_FDATA1(CAN0, can_filter_parameter_init->filter_number) = \
                                FDATA_MASK_HIGH((can_filter_parameter_init->filter_mask_high) & CAN_FILTER_MASK_16BITS) | \
                                FDATA_MASK_LOW((can_filter_parameter_init->filter_list_high) & CAN_FILTER_MASK_16BITS);
    }
    /* filter 32 bits */
    if(CAN_FILTERBITS_32BIT == can_filter_parameter_init->filter_bits){
        /* set filter 32 bits */
        CAN_FSCFG(CAN0) |= (uint32_t)val;
        /* 32 bits list or first 32 bits list */
        CAN_FDATA0(CAN0, can_filter_parameter_init->filter_number) = \
                                FDATA_MASK_HIGH((can_filter_parameter_init->filter_list_high) & CAN_FILTER_MASK_16BITS) |
                                FDATA_MASK_LOW((can_filter_parameter_init->filter_list_low) & CAN_FILTER_MASK_16BITS);
        /* 32 bits mask or second 32 bits list */
        CAN_FDATA1(CAN0, can_filter_parameter_init->filter_number) = \
                                FDATA_MASK_HIGH((can_filter_parameter_init->filter_mask_high) & CAN_FILTER_MASK_16BITS) |
                                FDATA_MASK_LOW((can_filter_parameter_init->filter_mask_low) & CAN_FILTER_MASK_16BITS);
    }
    
    /* filter mode */
    if(CAN_FILTERMODE_MASK == can_filter_parameter_init->filter_mode){
        /* mask mode */
        CAN_FMCFG(CAN0) &= ~(uint32_t)val;
    }else{
        /* list mode */
        CAN_FMCFG(CAN0) |= (uint32_t)val;
    }
    
    /* filter FIFO */
    if(CAN_FIFO0 == (can_filter_parameter_init->filter_fifo_number)){
        /* FIFO0 */
        CAN_FAFIFO(CAN0) &= ~(uint32_t)val;
    }
    
    if(CAN_FIFO1 == can_filter_parameter_init->filter_fifo_number){
        /* FIFO1 */
        CAN_FAFIFO(CAN0) |= (uint32_t)val;
    }
    
    /* filter working */
    if(ENABLE == can_filter_parameter_init->filter_enable){
        
        CAN_FW(CAN0) |= (uint32_t)val;
    }
    
    /* filter lock enable */
    CAN_FCTL(CAN0) &= ~CAN_FCTL_FLD;
}

/*!
    \brief      set CAN1 fliter start bank number
    \param[in]  can1_start_bank_number
      \arg        (1..27)
    \param[out] none
    \retval     none
*/
void can1_filter_start_bank(uint8_t start_bank)
{
    /* filter lock disable */
    CAN_FCTL(CAN0) |= CAN_FCTL_FLD;
    /* set CAN1 filter start number */
    CAN_FCTL(CAN0) &= ~(uint32_t)CAN_FCTL_HBC1F;
    CAN_FCTL(CAN0) |= FCTL_HBC1F(start_bank);
    /* filter lock enaable */
    CAN_FCTL(CAN0) &= ~CAN_FCTL_FLD;
}

/*!
    \brief      enable CAN debug freeze
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     none
*/
void can_debug_freeze_enable(uint32_t can_periph)
{
    CAN_CTL(can_periph) |= CAN_CTL_DFZ;
    if(CAN0 == can_periph){
        dbg_periph_enable(DBG_CAN0_HOLD);
    }else{
        dbg_periph_enable(DBG_CAN1_HOLD);
    }
}

/*!
    \brief      disable CAN debug freeze
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     none
*/
void can_debug_freeze_disable(uint32_t can_periph)
{
    CAN_CTL(can_periph) &= ~CAN_CTL_DFZ;
    if(CAN0 == can_periph){
        dbg_periph_disable(DBG_CAN0_HOLD);
    }else{
        dbg_periph_disable(DBG_CAN0_HOLD);
    }
}

/*!
    \brief      enable CAN time trigger mode
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     none
*/
void can_time_trigger_mode_enable(uint32_t can_periph)
{
    uint8_t mailbox_number;
    
    /* enable the tcc mode */
    CAN_CTL(can_periph) |= CAN_CTL_TTC;
    /* enable time stamp */
    for(mailbox_number=0U; mailbox_number<3U; mailbox_number++){
        CAN_TMP(can_periph, mailbox_number) |= CAN_TMP_TSEN;
    }
}

/*!
    \brief      disable CAN time trigger mode
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     none
*/
void can_time_trigger_mode_disable(uint32_t can_periph)
{
    uint8_t mailbox_number; 
    
    /* disable the TCC mode */
    CAN_CTL(can_periph) &= ~CAN_CTL_TTC;
    /* reset TSEN bits */
    for(mailbox_number=0U; mailbox_number<3U; mailbox_number++){
        CAN_TMP(can_periph, mailbox_number) &= ~CAN_TMP_TSEN;
    }
}

/*!
    \brief      CAN transmit message
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  can_trasnmit_message_struct: struct for CAN transmit message
                  can_rx_sfid: 0x00000000 - 0x000007FF
                  can_rx_efid: 0x00000000 - 0x1FFFFFFF
                  can_rx_ff: CAN_FF_STANDARD, CAN_FF_EXTENDED
                  can_rx_ft: CAN_FT_DATA, CAN_FT_REMOTE
                  can_rx_dlenc: 1 - 7
                  can_rx_data[]: 0x00 - 0xFF
    \param[out] none
    \retval     none
*/
uint8_t can_message_transmit(uint32_t can_periph, can_trasnmit_message_struct* transmit_message)
{
    uint8_t mailbox_number = CAN_MAILBOX0;

    /* select one empty mailbox */
    if(CAN_TSTAT_TME0 == (CAN_TSTAT(can_periph)&CAN_TSTAT_TME0)){
        mailbox_number = CAN_MAILBOX0;
    }else if(CAN_TSTAT_TME1 == (CAN_TSTAT(can_periph)&CAN_TSTAT_TME1)){
        mailbox_number = CAN_MAILBOX1;
    }else if(CAN_TSTAT_TME2 == (CAN_TSTAT(can_periph)&CAN_TSTAT_TME2)){
        mailbox_number = CAN_MAILBOX2;
    }else{
        mailbox_number = CAN_NOMAILBOX;
    }
    if(CAN_NOMAILBOX == mailbox_number){
        return CAN_NOMAILBOX;
    }
    
    CAN_TMI(can_periph, mailbox_number) &= CAN_TMI_TEN;
    if(CAN_FF_STANDARD == transmit_message->tx_ff){
        /* set transmit mailbox standard identifier */
        CAN_TMI(can_periph, mailbox_number) |= (uint32_t)(TMI_SFID(transmit_message->tx_sfid) | \
                                                transmit_message->tx_ft);
    }else{
        /* set transmit mailbox extended identifier */
        CAN_TMI(can_periph, mailbox_number) |= (uint32_t)(TMI_EFID(transmit_message->tx_efid) | \
                                                transmit_message->tx_ff | \
                                                transmit_message->tx_ft);
    }
    /* set the data length */
    transmit_message->tx_dlen &= (uint8_t)(CAN_TMP_DLENC);
    CAN_TMP(can_periph, mailbox_number) &= ((uint32_t)~CAN_TMP_DLENC);
    CAN_TMP(can_periph, mailbox_number) |= transmit_message->tx_dlen;
    /* set the data */
    CAN_TMDATA0(can_periph, mailbox_number) = TMDATA0_DB3(transmit_message->tx_data[3]) | \
                                              TMDATA0_DB2(transmit_message->tx_data[2]) | \
                                              TMDATA0_DB1(transmit_message->tx_data[1]) | \
                                              TMDATA0_DB0(transmit_message->tx_data[0]);
    CAN_TMDATA1(can_periph, mailbox_number) = TMDATA1_DB7(transmit_message->tx_data[7]) | \
                                              TMDATA1_DB6(transmit_message->tx_data[6]) | \
                                              TMDATA1_DB5(transmit_message->tx_data[5]) | \
                                              TMDATA1_DB4(transmit_message->tx_data[4]);
    /* enable transmission */
    CAN_TMI(can_periph, mailbox_number) |= CAN_TMI_TEN;

    return mailbox_number;
}

/*!
    \brief      CAN transmit state 
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  mailbox_number
      \arg        CAN_MAILBOX(x=0,1,2)
    \param[out] none
    \retval     can_transmit_state_enum
*/
can_transmit_state_enum can_transmit_states(uint32_t can_periph, uint8_t mailbox_number)
{
    can_transmit_state_enum state = CAN_TRANSMIT_FAILED;
    uint32_t val = 0U;
     
    switch(mailbox_number){
    case CAN_MAILBOX0:
        val = CAN_TSTAT(can_periph) & (CAN_TSTAT_MTF0 | CAN_TSTAT_MTFNERR0 | CAN_TSTAT_TME0);
        break;
    case CAN_MAILBOX1:
        val = CAN_TSTAT(can_periph) & (CAN_TSTAT_MTF1 | CAN_TSTAT_MTFNERR1 | CAN_TSTAT_TME1);
        break;
    case CAN_MAILBOX2:
        val = CAN_TSTAT(can_periph) & (CAN_TSTAT_MTF2 | CAN_TSTAT_MTFNERR2 | CAN_TSTAT_TME2);
        break;
    default:
        val = CAN_TRANSMIT_FAILED;
        break;
    }
    switch(val){
        /* transmit pending  */
    case (CAN_STATE_PENDING): 
        state = CAN_TRANSMIT_PENDING;
        break;
        /* transmit failed  */
    case (CAN_TSTAT_MTF0 | CAN_TSTAT_TME0): 
        state = CAN_TRANSMIT_FAILED;
        break;
    case (CAN_TSTAT_MTF1 | CAN_TSTAT_TME1): 
        state = CAN_TRANSMIT_FAILED;
        break;
    case (CAN_TSTAT_MTF2 | CAN_TSTAT_TME2): 
        state = CAN_TRANSMIT_FAILED;
        break;
        /* transmit succeeded  */
    case (CAN_TSTAT_MTF0 | CAN_TSTAT_MTFNERR0 | CAN_TSTAT_TME0):
        state = CAN_TRANSMIT_OK;
        break;
    case (CAN_TSTAT_MTF1 | CAN_TSTAT_MTFNERR1 | CAN_TSTAT_TME1):
        state = CAN_TRANSMIT_OK;
        break;
    case (CAN_TSTAT_MTF2 | CAN_TSTAT_MTFNERR2 | CAN_TSTAT_TME2):
        state = CAN_TRANSMIT_OK;
        break;
    default: 
        state = CAN_TRANSMIT_FAILED;
        break;
    }
    return state;
}

/*!
    \brief      CAN stop transmission
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  mailbox_number
      \arg        CAN_MAILBOXx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_transmission_stop(uint32_t can_periph, uint8_t mailbox_number)
{
    if(CAN_MAILBOX0 == mailbox_number){
        CAN_TSTAT(can_periph) |= CAN_TSTAT_MST0;
    }else if(CAN_MAILBOX1 == mailbox_number){
        CAN_TSTAT(can_periph) |= CAN_TSTAT_MST1;
    }else if(CAN_MAILBOX2 == mailbox_number){
        CAN_TSTAT(can_periph) |= CAN_TSTAT_MST2;
    }else{
        /* illegal parameter*/
    }
}

/*!
    \brief      CAN receive message
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  fifo_number
      \arg        CAN_FIFO0x(x=0,1)
    \param[out]  can_receive_message_struct: struct for CAN receive message
                  can_rx_sfid: 0x00000000 - 0x000007FF
                  can_rx_efid: 0x00000000 - 0x1FFFFFFF
                  can_rx_ff: CAN_FF_STANDARD, CAN_FF_EXTENDED
                  can_rx_ft: CAN_FT_DATA, CAN_FT_REMOTE
                  can_rx_dlenc: 1 - 7
                  can_rx_data[]: 0x00 - 0xFF
                  can_rx_fi: 0 - 27
    \retval     none
*/
void can_message_receive(uint32_t can_periph, uint8_t fifo_number, can_receive_message_struct* receive_message)
{
    /* get the frame format */
    receive_message->rx_ff = (uint8_t)(CAN_RFIFOMI_FF & CAN_RFIFOMI(can_periph, fifo_number));
    if(CAN_FF_STANDARD == receive_message->rx_ff){
        /* get standard identifier */
        receive_message -> rx_sfid = (uint32_t)(RFIFOMI_SFID(CAN_RFIFOMI(can_periph, fifo_number)));
    }else{
        /* get extended identifier */
        receive_message -> rx_efid = (uint32_t)(RFIFOMI_EFID(CAN_RFIFOMI(can_periph, fifo_number)));
    }
    
    /* get frame type */
    receive_message -> rx_ft = (uint8_t)(CAN_RFIFOMI_FT & CAN_RFIFOMI(can_periph, fifo_number));
    /* get recevie data length */
    receive_message -> rx_dlen = (uint8_t)(RFIFOMP_DLENC(CAN_RFIFOMP(can_periph, fifo_number)));        
    /* filtering index */
    receive_message -> rx_fi = (uint8_t)(RFIFOMP_FI(CAN_RFIFOMP(can_periph, fifo_number)));     
    
    /* receive data */
    receive_message -> rx_data[0] = (uint8_t)(RFIFOMDATA0_DB0(CAN_RFIFOMDATA0(can_periph, fifo_number)));
    receive_message -> rx_data[1] = (uint8_t)(RFIFOMDATA0_DB1(CAN_RFIFOMDATA0(can_periph, fifo_number)));
    receive_message -> rx_data[2] = (uint8_t)(RFIFOMDATA0_DB2(CAN_RFIFOMDATA0(can_periph, fifo_number)));
    receive_message -> rx_data[3] = (uint8_t)(RFIFOMDATA0_DB3(CAN_RFIFOMDATA0(can_periph, fifo_number)));
    receive_message -> rx_data[4] = (uint8_t)(RFIFOMDATA1_DB4(CAN_RFIFOMDATA1(can_periph, fifo_number)));
    receive_message -> rx_data[5] = (uint8_t)(RFIFOMDATA1_DB5(CAN_RFIFOMDATA1(can_periph, fifo_number)));
    receive_message -> rx_data[6] = (uint8_t)(RFIFOMDATA1_DB6(CAN_RFIFOMDATA1(can_periph, fifo_number)));
    receive_message -> rx_data[7] = (uint8_t)(RFIFOMDATA1_DB7(CAN_RFIFOMDATA1(can_periph, fifo_number)));
    
    /* release FIFO */
    if(CAN_FIFO0 == fifo_number){
        CAN_RFIFO0(can_periph) |= CAN_RFIFO0_RFD0;
    }else{
        CAN_RFIFO1(can_periph) |= CAN_RFIFO1_RFD1;
    }
}

/*!
    \brief      release FIFO0
    \param[in]  can_periph
      \arg        CANx(x=0,1)
      \arg        CAN_FIFO0x(x=0,1)
    \param[out] none
    \retval     none
*/
void can_fifo_release(uint32_t can_periph, uint8_t fifo_number)
{
    if(CAN_FIFO0 == fifo_number){
        CAN_RFIFO0(can_periph) |= CAN_RFIFO0_RFD0;
    }else if(CAN_FIFO1 == fifo_number){
        CAN_RFIFO1(can_periph) |= CAN_RFIFO1_RFD1;
    }else{
        /* illegal parameter */
    }
}

/*!
    \brief      CAN receive message length
    \param[in]  can_periph
      \arg        CANx(x=0,1)
      \arg        CAN_FIFO0x(x=0,1) 
    \param[out] none
    \retval     message length
*/
uint8_t can_receive_message_length(uint32_t can_periph, uint8_t fifo_number)
{
    uint8_t val = 0U;
    
    if(CAN_FIFO0 == fifo_number){
        val = (uint8_t)(CAN_RFIFO0(can_periph) & CAN_RFIFO_RFL0_MASK);
    }else if(CAN_FIFO0 == fifo_number){
        val = (uint8_t)(CAN_RFIFO1(can_periph) & CAN_RFIFO_RFL0_MASK);
    }else{
        /* illegal parameter */
    }
    return val;
}

/*!
    \brief      set CAN working mode
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  can_working_mode
      \arg        CAN_INITIALIZE_MODE
      \arg        CAN_NORMAL_MODE
      \arg        CAN_SLEEP_MODE
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_working_mode_set(uint32_t can_periph, uint8_t working_mode)
{
    ErrStatus flag = ERROR;
    /* timeout for IWS or also for SLPWS bits*/
    uint32_t timeout = CAN_TIMEOUT; 
    
    if(CAN_MODE_INITIALIZE == working_mode){
        /* disable sleep mode */
        CAN_CTL(can_periph) &= (~(uint32_t)CAN_CTL_SLPWMOD);
        /* set initialize mode */
        CAN_CTL(can_periph) |= (uint8_t)CAN_CTL_IWMOD;
        /* wait the acknowledge */
        while((CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)) && (timeout != 0U)){
            timeout--;
        }
        if(CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)){
            flag = ERROR;
        }else{
            flag = SUCCESS;
        }
    }else if(CAN_MODE_NORMAL == working_mode){
        /* enter normal mode */
        CAN_CTL(can_periph) &= ~(uint32_t)(CAN_CTL_SLPWMOD | CAN_CTL_IWMOD);
        /* wait the acknowledge */
        while((0U != (CAN_STAT(can_periph) & (CAN_STAT_IWS | CAN_STAT_SLPWS))) && (timeout != 0U)){
            timeout--;
        }
        if(0U != (CAN_STAT(can_periph) & (CAN_STAT_IWS | CAN_STAT_SLPWS))){
            flag = ERROR;
        }else{
            flag = SUCCESS;
        }
    }else if(CAN_MODE_SLEEP == working_mode){
        /* disable initialize mode */
        CAN_CTL(can_periph) &= (~(uint32_t)CAN_CTL_IWMOD);
        /* set sleep mode */
        CAN_CTL(can_periph) |= (uint8_t)CAN_CTL_SLPWMOD;
        /* wait the acknowledge */
        while((CAN_STAT_SLPWS != (CAN_STAT(can_periph) & CAN_STAT_SLPWS)) && (timeout != 0U)){
            timeout--;
        }
        if (CAN_STAT_SLPWS != (CAN_STAT(can_periph) & CAN_STAT_SLPWS)){
            flag = ERROR;
        }else{
            flag = SUCCESS;
        }
    }else{
        flag = ERROR;
    }
    return  flag;
}

/*!
    \brief      wake up CAN
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_wakeup(uint32_t can_periph)
{
    ErrStatus flag = ERROR;
    uint32_t timeout = CAN_TIMEOUT;
    
    /* wakeup */
    CAN_CTL(can_periph) &= ~CAN_CTL_SLPWMOD;
    
    while((0U != (CAN_STAT(can_periph) & CAN_STAT_SLPWS)) && (timeout != 0x00U)){
        timeout--;
    }
    if(0U != (CAN_STAT(can_periph) & CAN_STAT_SLPWS)){
        flag = ERROR;
    }else{
        flag = SUCCESS;
    }
    return flag;
}

/*!
    \brief      get CAN error type
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     can_error_enum
*/
can_error_enum can_error_get(uint32_t can_periph)
{
    can_error_enum error;
    error = CAN_ERROR_NONE;
    
    /* get error type */
    error = (can_error_enum)((CAN_ERR(can_periph) & CAN_ERR_ERRN) >> 4U);
    return error;
}

/*!
    \brief      CAN receive error number
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     error number
*/
uint8_t can_receive_error_number(uint32_t can_periph)
{
    uint8_t val;
    
    val = (uint8_t)((CAN_ERR(can_periph) & CAN_ERR_RECNT) >> 24U);
    return val;
}

/*!
    \brief      CAN transmit error number
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     error number
*/
uint8_t can_transmit_error_number(uint32_t can_periph)
{
    uint8_t val;
    
    val = (uint8_t)((CAN_ERR(can_periph) & CAN_ERR_TECNT) >> 16U);
    return val;
}

/*!
    \brief      enable CAN interrupt 
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  interrupt 
      \arg        CAN_INTEN_TMEIE
      \arg        CAN_INTEN_RFNEIE0
      \arg        CAN_INTEN_RFFIE0
      \arg        CAN_INTEN_RFOIE0
      \arg        CAN_INTEN_RFNEIE1
      \arg        CAN_INTEN_RFFIE1
      \arg        CAN_INTEN_RFOIE1
      \arg        CAN_INTEN_WERRIE
      \arg        CAN_INTEN_PERRIE
      \arg        CAN_INTEN_BOIE
      \arg        CAN_INTEN_ERRNIE
      \arg        CAN_INTEN_ERRIE
      \arg        CAN_INTEN_WUIE
      \arg        CAN_INTEN_SLPWIE
    \param[out] none
    \retval     none
*/
void can_interrupt_enable(uint32_t can_periph, uint32_t interrupt)
{
    CAN_INTEN(can_periph) |= interrupt;
}

/*!
    \brief      disable CAN interrupt 
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  interrupt
      \arg        CAN_INTEN_TMEIE
      \arg        CAN_INTEN_RFNEIE0
      \arg        CAN_INTEN_RFFIE0
      \arg        CAN_INTEN_RFOIE0
      \arg        CAN_INTEN_RFNEIE1
      \arg        CAN_INTEN_RFFIE1
      \arg        CAN_INTEN_RFOIE1
      \arg        CAN_INTEN_WERRIE
      \arg        CAN_INTEN_PERRIE
      \arg        CAN_INTEN_BOIE
      \arg        CAN_INTEN_ERRNIE
      \arg        CAN_INTEN_ERRIE
      \arg        CAN_INTEN_WUIE
      \arg        CAN_INTEN_SLPWIE
    \param[out] none
    \retval     none
*/
void can_interrupt_disable(uint32_t can_periph, uint32_t interrupt)
{
    CAN_INTEN(can_periph) &= ~interrupt;
}

/*!
    \brief      get CAN flag state
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  flag: CAN flags, refer to can_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_FLAG_MTE2
      \arg        CAN_FLAG_MTE1
      \arg        CAN_FLAG_MTE0
      \arg        CAN_FLAG_MTF2
      \arg        CAN_FLAG_MTF1
      \arg        CAN_FLAG_MTF0
      \arg        CAN_FLAG_RFO0
      \arg        CAN_FLAG_RFF0
      \arg        CAN_FLAG_RFO1
      \arg        CAN_FLAG_RFF1
      \arg        CAN_FLAG_BOERR
      \arg        CAN_FLAG_PERR
      \arg        CAN_FLAG_WERR
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_flag_get(uint32_t can_periph, can_flag_enum flag)
{  
    if(RESET != (CAN_REG_VAL(can_periph, flag) & BIT(CAN_BIT_POS(flag)))){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CAN flag state
     \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  flag: CAN flags, refer to can_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_FLAG_MTE2
      \arg        CAN_FLAG_MTE1
      \arg        CAN_FLAG_MTE0
      \arg        CAN_FLAG_MTF2
      \arg        CAN_FLAG_MTF1
      \arg        CAN_FLAG_MTF0
      \arg        CAN_FLAG_RFO0
      \arg        CAN_FLAG_RFF0
      \arg        CAN_FLAG_RFO1
      \arg        CAN_FLAG_RFF1
    \param[out] none
    \retval     none
*/
void can_flag_clear(uint32_t can_periph, can_flag_enum flag)
{
    CAN_REG_VAL(can_periph, flag) |= BIT(CAN_BIT_POS(flag));
}

/*!
    \brief      get CAN interrupt flag state
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  flag: CAN interrupt flags, refer to can_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_SLPIF
      \arg        CAN_INT_WUIF
      \arg        CAN_INT_ERRIF
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_interrupt_flag_get(uint32_t can_periph, can_interrupt_flag_enum flag)
{  
    FlagStatus inten = RESET;
    FlagStatus temp = RESET;
    FlagStatus status1 = RESET;
    FlagStatus status2 = RESET;
    
    switch(flag){
    /* get the status of sleep working interrupt enable bit */
    case CAN_INT_SLPIF:
        inten = (FlagStatus)(CAN_INTEN(can_periph) & CAN_INTEN_SLPWIE);
        break;
    /* get the status of wakeup interrupt enable bit */
    case CAN_INT_WUIF:
        inten = (FlagStatus)(CAN_INTEN(can_periph) & CAN_INTEN_WUIE);
        break;
    /* get the status of error falgs and its enable bit */
    case CAN_INT_ERRIF:
        /* check if the BOERR bit in CAN_ERR register and BOIE bit in CAN_INTEN register are set */
        status1 = (FlagStatus)(CAN_INTEN(can_periph) & CAN_INTEN_BOIE);
        status2 = (FlagStatus)(CAN_ERR(can_periph) & CAN_ERR_BOERR);
        if((RESET != status1) && (RESET != status2)){
            inten = SET;
        }
        /* check if the WERR bit in CAN_ERR register and WERRIE bit in CAN_INTEN register are set */
        status1 = (FlagStatus)(CAN_INTEN(can_periph) & CAN_INTEN_WERRIE);
        status2 = (FlagStatus)(CAN_ERR(can_periph) & CAN_ERR_WERR);
        if((RESET != status1) && (RESET != status2)){
            inten = SET;
        }
        /* check if the PERR bit in CAN_ERR register and PERRIE bit in CAN_INTEN register are set */
        status1 = (FlagStatus)(CAN_INTEN(can_periph) & CAN_INTEN_PERRIE);
        status2 = (FlagStatus)(CAN_ERR(can_periph) & CAN_ERR_PERR);
        if((RESET != status1) && (RESET != status2)){
            inten = SET;
        }
        /* check if the ERRN bit in CAN_ERR register and ERRNIE bit in CAN_INTEN register are set */
        status1 = (FlagStatus)(CAN_INTEN(can_periph) & CAN_INTEN_ERRNIE);
        status2 = (FlagStatus)(CAN_ERR(can_periph) & CAN_ERR_ERRN);
        if((RESET != status1) && (RESET != status2)){
            inten = SET;
        }
        break;
    default:
        break;
    }
    /* get the interrupt flag */
    temp = (FlagStatus)(CAN_REG_VAL(can_periph, flag) & BIT(CAN_BIT_POS(flag)));
    /* check the interrupt enable bit and corresponding flag bit are set */
    if((RESET != inten) && (RESET != temp)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CAN interrupt flag state
     \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  flag: CAN interrupt flags, refer to can_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_SLPIF
      \arg        CAN_INT_WUIF
      \arg        CAN_INT_ERRIF
    \param[out] none
    \retval     none
*/
void can_interrupt_flag_clear(uint32_t can_periph, can_interrupt_flag_enum flag)
{
    CAN_REG_VAL(can_periph, flag) |= BIT(CAN_BIT_POS(flag));
}
