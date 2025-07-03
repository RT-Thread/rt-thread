/*!
    \file    gd32f5xx_can.c
    \brief   CAN driver

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
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

#include "gd32f5xx_can.h"
#include <stdlib.h>

#define CAN_ERROR_HANDLE(s)         do{}while(1)

/* This table can be used to calculate data length in FD mode */
const uint8_t g_can_fdlength_table[] = {12, 16, 20, 24, 32, 48, 64};

/*!
    \brief      deinitialize CAN
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     none
*/
void can_deinit(uint32_t can_periph)
{
    if(CAN0 == can_periph) {
        rcu_periph_reset_enable(RCU_CAN0RST);
        rcu_periph_reset_disable(RCU_CAN0RST);
    } else {
        rcu_periph_reset_enable(RCU_CAN1RST);
        rcu_periph_reset_disable(RCU_CAN1RST);
    }
}

/*!
    \brief      initialize CAN parameter struct with a default value
    \param[in]  type: the type of CAN parameter struct
                only one parameter can be selected which is shown as below:
      \arg        CAN_INIT_STRUCT: the CAN initial struct
      \arg        CAN_FILTER_STRUCT: the CAN filter struct
      \arg        CAN_FD_FRAME_STRUCT: the CAN FD initial struct
      \arg        CAN_TX_MESSAGE_STRUCT: the CAN TX message struct
      \arg        CAN_RX_MESSAGE_STRUCT: the CAN RX message struct
    \param[in]  p_struct: the pointer of the specific struct
    \param[out] none
    \retval     none
*/
void can_struct_para_init(can_struct_type_enum type, void *p_struct)
{
    uint8_t i;

    if(NULL == p_struct) {
        CAN_ERROR_HANDLE("struct parameter can not be NULL \r\n");
    }

    /* get type of the struct */
    switch(type) {
    /* used for can_init() */
    case CAN_INIT_STRUCT:
        ((can_parameter_struct *)p_struct)->auto_bus_off_recovery = DISABLE;
        ((can_parameter_struct *)p_struct)->auto_retrans = DISABLE;
        ((can_parameter_struct *)p_struct)->auto_wake_up = DISABLE;
        ((can_parameter_struct *)p_struct)->prescaler = 0x03FFU;
        ((can_parameter_struct *)p_struct)->rec_fifo_overwrite = DISABLE;
        ((can_parameter_struct *)p_struct)->resync_jump_width = CAN_BT_SJW_1TQ;
        ((can_parameter_struct *)p_struct)->time_segment_1 = CAN_BT_BS1_3TQ;
        ((can_parameter_struct *)p_struct)->time_segment_2 = CAN_BT_BS2_1TQ;
        ((can_parameter_struct *)p_struct)->time_triggered = DISABLE;
        ((can_parameter_struct *)p_struct)->trans_fifo_order = DISABLE;
        ((can_parameter_struct *)p_struct)->working_mode = CAN_NORMAL_MODE;

        break;
    /* used for can_filter_init() */
    case CAN_FILTER_STRUCT:
        ((can_filter_parameter_struct *)p_struct)->filter_bits = CAN_FILTERBITS_32BIT;
        ((can_filter_parameter_struct *)p_struct)->filter_enable = DISABLE;
        ((can_filter_parameter_struct *)p_struct)->filter_fifo_number = CAN_FIFO0;
        ((can_filter_parameter_struct *)p_struct)->filter_list_high = 0x0000U;
        ((can_filter_parameter_struct *)p_struct)->filter_list_low = 0x0000U;
        ((can_filter_parameter_struct *)p_struct)->filter_mask_high = 0x0000U;
        ((can_filter_parameter_struct *)p_struct)->filter_mask_low = 0x0000U;
        ((can_filter_parameter_struct *)p_struct)->filter_mode = CAN_FILTERMODE_MASK;
        ((can_filter_parameter_struct *)p_struct)->filter_number = 0U;

        break;
    /* used for can_fd_init() */
    case CAN_FD_FRAME_STRUCT:
        ((can_fdframe_struct *)p_struct)->data_prescaler = 0x0400U;
        ((can_fdframe_struct *)p_struct)->data_resync_jump_width = 1U - 1U;
        ((can_fdframe_struct *)p_struct)->data_time_segment_1 = 3U - 1U;
        ((can_fdframe_struct *)p_struct)->data_time_segment_2 = 2U - 1U;
        ((can_fdframe_struct *)p_struct)->delay_compensation = DISABLE;
        ((can_fdframe_struct *)p_struct)->esi_mode = CAN_ESIMOD_HARDWARE;
        ((can_fdframe_struct *)p_struct)->excp_event_detect = ENABLE;
        ((can_fdframe_struct *)p_struct)->fd_frame = DISABLE;
        ((can_fdframe_struct *)p_struct)->iso_bosch = CAN_FDMOD_ISO;
        ((can_fdframe_struct *)p_struct)->p_delay_compensation = 0U;

        break;
    /* used for can_message_transmit() */
    case CAN_TX_MESSAGE_STRUCT:
        ((can_trasnmit_message_struct *)p_struct)->fd_brs = CAN_BRS_DISABLE;
        ((can_trasnmit_message_struct *)p_struct)->fd_esi = CAN_ESI_DOMINANT;
        ((can_trasnmit_message_struct *)p_struct)->fd_flag = CAN_FDF_CLASSIC;

        for(i = 0U; i < 64U; i++) {
            ((can_trasnmit_message_struct *)p_struct)->tx_data[i] = 0U;
        }

        ((can_trasnmit_message_struct *)p_struct)->tx_dlen = 0u;
        ((can_trasnmit_message_struct *)p_struct)->tx_efid = 0U;
        ((can_trasnmit_message_struct *)p_struct)->tx_ff = (uint8_t)CAN_FF_STANDARD;
        ((can_trasnmit_message_struct *)p_struct)->tx_ft = (uint8_t)CAN_FT_DATA;
        ((can_trasnmit_message_struct *)p_struct)->tx_sfid = 0U;

        break;
    /* used for can_message_receive() */
    case CAN_RX_MESSAGE_STRUCT:
        ((can_receive_message_struct *)p_struct)->fd_brs = CAN_BRS_DISABLE;
        ((can_receive_message_struct *)p_struct)->fd_esi = CAN_ESI_DOMINANT;
        ((can_receive_message_struct *)p_struct)->fd_flag = CAN_FDF_CLASSIC;

        for(i = 0U; i < 64U; i++) {
            ((can_receive_message_struct *)p_struct)->rx_data[i] = 0U;
        }

        ((can_receive_message_struct *)p_struct)->rx_dlen = 0U;
        ((can_receive_message_struct *)p_struct)->rx_efid = 0U;
        ((can_receive_message_struct *)p_struct)->rx_ff = (uint8_t)CAN_FF_STANDARD;
        ((can_receive_message_struct *)p_struct)->rx_fi = 0U;
        ((can_receive_message_struct *)p_struct)->rx_ft = (uint8_t)CAN_FT_DATA;
        ((can_receive_message_struct *)p_struct)->rx_sfid = 0U;

        break;

    default:
        CAN_ERROR_HANDLE("parameter is invalid \r\n");
    }
}

/*!
    \brief      initialize CAN
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  can_parameter_init: parameters for CAN initialization
      \arg        working_mode: CAN_NORMAL_MODE, CAN_LOOPBACK_MODE, CAN_SILENT_MODE, CAN_SILENT_LOOPBACK_MODE
      \arg        resync_jump_width: 0x00 - 0x07
      \arg        time_segment_1: 0x00 - 0x7F
      \arg        time_segment_2: 0x00 - 0x1F
      \arg        time_triggered: ENABLE or DISABLE
      \arg        auto_bus_off_recovery: ENABLE or DISABLE
      \arg        auto_wake_up: ENABLE or DISABLE
      \arg        auto_retrans: ENABLE or DISABLE
      \arg        rec_fifo_overwrite: ENABLE or DISABLE
      \arg        trans_fifo_order: ENABLE or DISABLE
      \arg        prescaler: 0x0001 - 0x0400
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_init(uint32_t can_periph, can_parameter_struct *can_parameter_init)
{
    uint32_t timeout = CAN_TIMEOUT;
    ErrStatus flag = ERROR;
    uint32_t fdctl_status;

    /* disable sleep mode */
    CAN_CTL(can_periph) &= ~CAN_CTL_SLPWMOD;
    /* enable initialize mode */
    CAN_CTL(can_periph) |= CAN_CTL_IWMOD;
    /* wait ACK */
    while((CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)) && (0U != timeout)) {
        timeout--;
    }
    /* check initialize working success */
    if(CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)) {
        flag = ERROR;
    } else {
        /* set the bit timing register */
        fdctl_status = CAN_FDCTL(can_periph);
        if(CAN_FDCTL_FDEN != (fdctl_status & CAN_FDCTL_FDEN)) {
            /* CAN FD disable, should first enable, then write */
            fdctl_status = fdctl_status | CAN_FDCTL_FDEN;
            CAN_FDCTL(can_periph) = fdctl_status;
            CAN_BT(can_periph) = (BT_MODE((uint32_t)can_parameter_init->working_mode) | \
                                  BT_SJW((uint32_t)can_parameter_init->resync_jump_width) | \
                                  BT_BS1((uint32_t)can_parameter_init->time_segment_1) | \
                                  BT_BS2((uint32_t)can_parameter_init->time_segment_2) | \
                                  BT_BAUDPSC(((uint32_t)(can_parameter_init->prescaler) - 1U)));
            fdctl_status = fdctl_status & (~CAN_FDCTL_FDEN);
            CAN_FDCTL(can_periph) = fdctl_status;
        } else {
            /* CAN FD enable */
            CAN_BT(can_periph) = (BT_MODE((uint32_t)can_parameter_init->working_mode) | \
                                  BT_SJW((uint32_t)can_parameter_init->resync_jump_width) | \
                                  BT_BS1((uint32_t)can_parameter_init->time_segment_1) | \
                                  BT_BS2((uint32_t)can_parameter_init->time_segment_2) | \
                                  BT_BAUDPSC(((uint32_t)(can_parameter_init->prescaler) - 1U)));
        }

        /* time trigger communication mode */
        if(ENABLE == can_parameter_init->time_triggered) {
            CAN_CTL(can_periph) |= CAN_CTL_TTC;
        } else {
            CAN_CTL(can_periph) &= ~CAN_CTL_TTC;
        }
        /* automatic bus-off management */
        if(ENABLE == can_parameter_init->auto_bus_off_recovery) {
            CAN_CTL(can_periph) |= CAN_CTL_ABOR;
        } else {
            CAN_CTL(can_periph) &= ~CAN_CTL_ABOR;
        }
        /* automatic wakeup mode */
        if(ENABLE == can_parameter_init->auto_wake_up) {
            CAN_CTL(can_periph) |= CAN_CTL_AWU;
        } else {
            CAN_CTL(can_periph) &= ~CAN_CTL_AWU;
        }
        /* automatic retransmission mode */
        if(ENABLE == can_parameter_init->auto_retrans) {
            CAN_CTL(can_periph) &= ~CAN_CTL_ARD;
        } else {
            CAN_CTL(can_periph) |= CAN_CTL_ARD;
        }
        /* receive FIFO overwrite mode */
        if(ENABLE == can_parameter_init->rec_fifo_overwrite) {
            CAN_CTL(can_periph) &= ~CAN_CTL_RFOD;
        } else {
            CAN_CTL(can_periph) |= CAN_CTL_RFOD;
        }
        /* transmit FIFO order */
        if(ENABLE == can_parameter_init->trans_fifo_order) {
            CAN_CTL(can_periph) |= CAN_CTL_TFO;
        } else {
            CAN_CTL(can_periph) &= ~CAN_CTL_TFO;
        }
        /* disable initialize mode */
        CAN_CTL(can_periph) &= ~CAN_CTL_IWMOD;
        timeout = CAN_TIMEOUT;
        /* wait the ACK */
        while((CAN_STAT_IWS == (CAN_STAT(can_periph) & CAN_STAT_IWS)) && (0U != timeout)) {
            timeout--;
        }
        /* check exit initialize mode */
        if(0U != timeout) {
            flag = SUCCESS;
        }
    }
    return flag;
}

/*!
    \brief      initialize CAN FD function
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  can_fdframe_init: parameters for CAN FD initialization
      \arg        fd_frame: ENABLE or DISABLE
      \arg        excp_event_detect: ENABLE or DISABLE
      \arg        delay_compensation: ENABLE or DISABLE
      \arg        p_delay_compensation: the pointer of tdc struct
                  can_fd_tdc_struct:
                    tdc_mode: CAN_TDCMOD_CALC_AND_OFFSET or CAN_TDCMOD_OFFSET
                    tdc_filter: 0x00 - 0x07
                    tdc_offset: 0x00 - 0x07
      \arg        iso_bosch: CAN_FDMOD_ISO or CAN_FDMOD_BOSCH
      \arg        esi_mode: CAN_ESIMOD_HARDWARE or CAN_ESIMOD_SOFTWARE
      \arg        data_resync_jump_width: 0x00 - 0x07
      \arg        data_time_segment_1: 0x00 - 0x0F
      \arg        data_time_segment_2: 0x00 - 0x07
      \arg        data_prescaler: 0x0001 - 0x0400
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_fd_init(uint32_t can_periph, can_fdframe_struct *can_fdframe_init)
{
    uint32_t timeout = CAN_TIMEOUT;
    uint32_t tempreg = 0U;

    /* check null pointer */
    if(0 == can_fdframe_init) {
        return ERROR;
    }
    /* disable sleep mode */
    CAN_CTL(can_periph) &= ~CAN_CTL_SLPWMOD;
    /* enable initialize mode */
    CAN_CTL(can_periph) |= CAN_CTL_IWMOD;
    /* wait ACK */
    while((CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)) && (0U != timeout)) {
        timeout--;
    }
    /* check initialize working success */
    if(CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)) {
        return ERROR;
    } else {
        /* set the data bit timing register */
        CAN_DBT(can_periph) = (BT_DSJW((uint32_t)can_fdframe_init->data_resync_jump_width) | \
                               BT_DBS1((uint32_t)can_fdframe_init->data_time_segment_1) | \
                               BT_DBS2((uint32_t)can_fdframe_init->data_time_segment_2) | \
                               BT_BAUDPSC(((uint32_t)can_fdframe_init->data_prescaler) - 1U));

        tempreg = can_fdframe_init->esi_mode | can_fdframe_init->iso_bosch;

        /* Protocol exception event detection */
        if(ENABLE == can_fdframe_init->excp_event_detect) {
            tempreg &= ~CAN_FDCTL_PRED;
        } else {
            tempreg |= CAN_FDCTL_PRED;
        }

        /* Transmitter delay compensation mode */
        if(ENABLE == can_fdframe_init->delay_compensation) {
            tempreg |= CAN_FDCTL_TDCEN;
            /* p_delay_compensation pointer should be config when TDC mode is enabled */
            if(0 != can_fdframe_init->p_delay_compensation) {
                tempreg |= (can_fdframe_init->p_delay_compensation->tdc_mode & CAN_FDCTL_TDCMOD);
                CAN_FDTDC(can_periph) = (FDTDC_TDCF(can_fdframe_init->p_delay_compensation->tdc_filter) | FDTDC_TDCO(
                                             can_fdframe_init->p_delay_compensation->tdc_offset));
            } else {
                return ERROR;
            }
        } else {
            /* Transmitter delay compensation mode is disabled */
            tempreg &= ~CAN_FDCTL_TDCEN;
        }

        /* FD operation mode */
        if(ENABLE == can_fdframe_init->fd_frame) {
            tempreg |= CAN_FDCTL_FDEN;
        } else {
            tempreg &= ~CAN_FDCTL_FDEN;
        }
        CAN_FDCTL(can_periph) = tempreg;

        /* disable initialize mode */
        CAN_CTL(can_periph) &= ~CAN_CTL_IWMOD;
        timeout = CAN_TIMEOUT;
        /* wait the ACK */
        while((CAN_STAT_IWS == (CAN_STAT(can_periph) & CAN_STAT_IWS)) && (0U != timeout)) {
            timeout--;
        }
        /* check exit initialize mode */
        if(0U == timeout) {
            return ERROR;
        }
    }

    return SUCCESS;
}

/*!
    \brief      initialize CAN filter
    \param[in]  can_filter_parameter_init: struct for CAN filter initialization
      \arg        filter_list_high: 0x0000 - 0xFFFF
      \arg        filter_list_low: 0x0000 - 0xFFFF
      \arg        filter_mask_high: 0x0000 - 0xFFFF
      \arg        filter_mask_low: 0x0000 - 0xFFFF
      \arg        filter_fifo_number: CAN_FIFO0, CAN_FIFO1
      \arg        filter_number: 0 - 27
      \arg        filter_mode: CAN_FILTERMODE_MASK, CAN_FILTERMODE_LIST
      \arg        filter_bits: CAN_FILTERBITS_32BIT, CAN_FILTERBITS_16BIT
      \arg        filter_enable: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void can_filter_init(can_filter_parameter_struct *can_filter_parameter_init)
{
    uint32_t val = 0U;

    val = ((uint32_t)1) << (can_filter_parameter_init->filter_number);
    /* filter lock disable */
    CAN_FCTL(CAN0) |= CAN_FCTL_FLD;
    /* disable filter */
    CAN_FW(CAN0) &= ~(uint32_t)val;

    /* filter 16 bits */
    if(CAN_FILTERBITS_16BIT == can_filter_parameter_init->filter_bits) {
        /* set filter 16 bits */
        CAN_FSCFG(CAN0) &= ~(uint32_t)val;
        /* first 16 bits list and first 16 bits mask or first 16 bits list and second 16 bits list */
        CAN_FDATA0(CAN0, can_filter_parameter_init->filter_number) = \
                FDATA_MASK_HIGH((can_filter_parameter_init->filter_mask_low) & CAN_FILTER_MASK_16BITS) | \
                FDATA_MASK_LOW((can_filter_parameter_init->filter_list_low) & CAN_FILTER_MASK_16BITS);
        /* second 16 bits list and second 16 bits mask or third 16 bits list and fourth 16 bits list */
        CAN_FDATA1(CAN0, can_filter_parameter_init->filter_number) = \
                FDATA_MASK_HIGH((can_filter_parameter_init->filter_mask_high) & CAN_FILTER_MASK_16BITS) | \
                FDATA_MASK_LOW((can_filter_parameter_init->filter_list_high) & CAN_FILTER_MASK_16BITS);
    }
    /* filter 32 bits */
    if(CAN_FILTERBITS_32BIT == can_filter_parameter_init->filter_bits) {
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
    if(CAN_FILTERMODE_MASK == can_filter_parameter_init->filter_mode) {
        /* mask mode */
        CAN_FMCFG(CAN0) &= ~(uint32_t)val;
    } else {
        /* list mode */
        CAN_FMCFG(CAN0) |= (uint32_t)val;
    }

    /* filter FIFO */
    if(CAN_FIFO0 == (can_filter_parameter_init->filter_fifo_number)) {
        /* FIFO0 */
        CAN_FAFIFO(CAN0) &= ~(uint32_t)val;
    } else {
        /* FIFO1 */
        CAN_FAFIFO(CAN0) |= (uint32_t)val;
    }

    /* filter working */
    if(ENABLE == can_filter_parameter_init->filter_enable) {

        CAN_FW(CAN0) |= (uint32_t)val;
    }

    /* filter lock enable */
    CAN_FCTL(CAN0) &= ~CAN_FCTL_FLD;
}

/*!
    \brief      CAN filter mask mode initialization
    \param[in]  id: extended(11-bits) or standard(29-bits) identifier
      \arg        0x00000000 - 0x1FFFFFFF
    \param[in]  mask: extended(11-bits) or standard(29-bits) identifier mask
      \arg        0x00000000 - 0x1FFFFFFF
    \param[in]  format_fifo: format and FIFO states
                only one parameter can be selected which is shown as below:
      \arg        CAN_STANDARD_FIFO0
      \arg        CAN_STANDARD_FIFO1
      \arg        CAN_EXTENDED_FIFO0
      \arg        CAN_EXTENDED_FIFO1
    \param[in]  filter_number: filter sequence number
      \arg        0x00 - 0x1B
    \param[out] none
    \retval     none
*/
void can_filter_mask_mode_init(uint32_t id, uint32_t mask, can_format_fifo_enum format_fifo, uint16_t filter_number)
{
    can_filter_parameter_struct can_filter;

    /* Initialize the filter structure */
    can_struct_para_init(CAN_FILTER_STRUCT, &can_filter);

    /* filter config */
    can_filter.filter_number = filter_number;
    can_filter.filter_mode = CAN_FILTERMODE_MASK;
    can_filter.filter_bits = CAN_FILTERBITS_32BIT;
    can_filter.filter_enable = ENABLE;

    switch(format_fifo) {
    /* standard FIFO 0 */
    case CAN_STANDARD_FIFO0:
        can_filter.filter_fifo_number = CAN_FIFO0;
        /* configure SFID[10:0] */
        can_filter.filter_list_high = (uint16_t)id << 5;
        can_filter.filter_list_low = 0x0000U;
        /* configure SFID[10:0] mask */
        can_filter.filter_mask_high = (uint16_t)mask << 5;
        /* both data and remote frames can be received */
        can_filter.filter_mask_low = (uint16_t)(1U << 2U);

        break;
    /* standard FIFO 1 */
    case CAN_STANDARD_FIFO1:
        can_filter.filter_fifo_number = CAN_FIFO1;
        /* configure SFID[10:0] */
        can_filter.filter_list_high = (uint16_t)id << 5;
        can_filter.filter_list_low =  0x0000U;
        /* configure SFID[10:0] mask */
        can_filter.filter_mask_high = (uint16_t)mask << 5;
        /* both data and remote frames can be received */
        can_filter.filter_mask_low = (uint16_t)(1U << 2U);

        break;
    /* extended FIFO 0 */
    case CAN_EXTENDED_FIFO0:
        can_filter.filter_fifo_number = CAN_FIFO0;
        /* configure EFID[28:13] */
        can_filter.filter_list_high = (uint16_t)(id >> 13);
        /* configure EFID[12:0] and frame format bit set */
        can_filter.filter_list_low = ((uint16_t)(id << 3)) | (1U << 2);
        /* configure EFID[28:13] mask */
        can_filter.filter_mask_high = (uint16_t)(mask >> 13);
        /* configure EFID[12:0] and frame format bit mask */
        /* both data and remote frames can be received */
        can_filter.filter_mask_low = ((uint16_t)(mask << 3)) | (1U << 2);

        break;
    /* extended FIFO 1 */
    case CAN_EXTENDED_FIFO1:
        can_filter.filter_fifo_number = CAN_FIFO1;
        /* configure EFID[28:13] */
        can_filter.filter_list_high = (uint16_t)(id >> 13);
        /* configure EFID[12:0] and frame format bit set */
        can_filter.filter_list_low = ((uint16_t)(id << 3)) | (1U << 2);
        /* configure EFID[28:13] mask */
        can_filter.filter_mask_high = (uint16_t)(mask >> 13);
        /* configure EFID[12:0] and frame format bit mask */
        /* both data and remote frames can be received */
        can_filter.filter_mask_low = ((uint16_t)(mask << 3)) | (1U << 2);

        break;
    default:
        CAN_ERROR_HANDLE("parameter is invalid \r\n");
    }

    can_filter_init(&can_filter);
}

/*!
    \brief      CAN communication mode configure
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  mode: communication mode
                only one parameter can be selected which is shown as below:
      \arg        CAN_NORMAL_MODE
      \arg        CAN_LOOPBACK_MODE
      \arg        CAN_SILENT_MODE
      \arg        CAN_SILENT_LOOPBACK_MODE
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_monitor_mode_set(uint32_t can_periph, uint8_t mode)
{
    ErrStatus reval = SUCCESS;
    uint32_t timeout = CAN_TIMEOUT;

    if(mode == (mode & CAN_SILENT_LOOPBACK_MODE)) {
        /* disable sleep mode */
        CAN_CTL(can_periph) &= (~(uint32_t)CAN_CTL_SLPWMOD);
        /* set initialize mode */
        CAN_CTL(can_periph) |= (uint8_t)CAN_CTL_IWMOD;
        /* wait the acknowledge */
        timeout = CAN_TIMEOUT;
        while((CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)) && (0U != timeout)) {
            timeout--;
        }

        if(CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)) {
            reval = ERROR;
        } else {
            CAN_BT(can_periph) &= ~BT_MODE(3);
            CAN_BT(can_periph) |= BT_MODE(mode);

            timeout = CAN_TIMEOUT;
            /* enter normal mode */
            CAN_CTL(can_periph) &= ~(uint32_t)(CAN_CTL_SLPWMOD | CAN_CTL_IWMOD);
            /* wait the acknowledge */
            while((0U != (CAN_STAT(can_periph) & (CAN_STAT_IWS | CAN_STAT_SLPWS))) && (0U != timeout)) {
                timeout--;
            }
            if(0U != (CAN_STAT(can_periph) & (CAN_STAT_IWS | CAN_STAT_SLPWS))) {
                reval = ERROR;
            }
        }
    } else {
        reval = ERROR;
    }

    return reval;
}

/*!
    \brief      CAN FD frame function enable
    \param[in]  can_periph
    \arg        CANx(x=0,1)
    \param[out] none
    \retval     none
*/
void can_fd_function_enable(uint32_t can_periph)
{
    CAN_FDCTL(can_periph) |= CAN_FDCTL_FDEN;
}

/*!
    \brief      CAN FD frame function disable
    \param[in]  can_periph
    \arg        CANx(x=0,1)
    \param[out] none
    \retval     none
*/
void can_fd_function_disable(uint32_t can_periph)
{
    CAN_FDCTL(can_periph) &= ~CAN_FDCTL_FDEN;
}

/*!
    \brief      set CAN1 filter start bank number
    \param[in]  start_bank: CAN1 start bank number
                only one parameter can be selected which is shown as below:
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
    /* filter lock enable */
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
    /* set DFZ bit */
    CAN_CTL(can_periph) |= CAN_CTL_DFZ;

    if(CAN0 == can_periph) {
        dbg_periph_enable(DBG_CAN0_HOLD);
    } else {
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
    /* set DFZ bit */
    CAN_CTL(can_periph) &= ~CAN_CTL_DFZ;

    if(CAN0 == can_periph) {
        dbg_periph_disable(DBG_CAN0_HOLD);
    } else {
        dbg_periph_disable(DBG_CAN1_HOLD);
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

    /* enable the TTC mode */
    CAN_CTL(can_periph) |= CAN_CTL_TTC;
    /* enable time stamp */
    for(mailbox_number = 0U; mailbox_number < 3U; mailbox_number++) {
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

    /* disable the TTC mode */
    CAN_CTL(can_periph) &= ~CAN_CTL_TTC;
    /* reset TSEN bits */
    for(mailbox_number = 0U; mailbox_number < 3U; mailbox_number++) {
        CAN_TMP(can_periph, mailbox_number) &= ~CAN_TMP_TSEN;
    }
}

/*!
    \brief      transmit CAN message
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  transmit_message: struct for CAN transmit message
      \arg        tx_sfid: 0x00000000 - 0x000007FF
      \arg        tx_efid: 0x00000000 - 0x1FFFFFFF
      \arg        tx_ff: CAN_FF_STANDARD, CAN_FF_EXTENDED
      \arg        tx_ft: CAN_FT_DATA, CAN_FT_REMOTE
      \arg        tx_dlen: 0 - 8 (FD mode: 0 - 8, or 12, 16, 20, 24, 32, 48, 64)
      \arg        tx_data[]: 0x00 - 0xFF
    \param[out] none
    \retval     mailbox_number
*/
uint8_t can_message_transmit(uint32_t can_periph, can_trasnmit_message_struct *transmit_message)
{
    uint8_t mailbox_number = CAN_MAILBOX0;
    uint8_t i = 0U;
    uint8_t hit = 0U;
    uint32_t canfd_en = 0U;
    volatile uint32_t p_temp;
    uint32_t reg_temp = 0U;

    /* select one empty mailbox */
    if(CAN_TSTAT_TME0 == (CAN_TSTAT(can_periph)&CAN_TSTAT_TME0)) {
        mailbox_number = CAN_MAILBOX0;
    } else if(CAN_TSTAT_TME1 == (CAN_TSTAT(can_periph)&CAN_TSTAT_TME1)) {
        mailbox_number = CAN_MAILBOX1;
    } else if(CAN_TSTAT_TME2 == (CAN_TSTAT(can_periph)&CAN_TSTAT_TME2)) {
        mailbox_number = CAN_MAILBOX2;
    } else {
        mailbox_number = CAN_NOMAILBOX;
    }
    /* return no mailbox empty */
    if(CAN_NOMAILBOX == mailbox_number) {
        return CAN_NOMAILBOX;
    }

    CAN_TMI(can_periph, mailbox_number) &= CAN_TMI_TEN;
    if(CAN_FF_STANDARD == transmit_message->tx_ff) {
        /* set transmit mailbox standard identifier */
        CAN_TMI(can_periph, mailbox_number) |= (uint32_t)(TMI_SFID(transmit_message->tx_sfid) | \
                                               transmit_message->tx_ft);
    } else {
        /* set transmit mailbox extended identifier */
        CAN_TMI(can_periph, mailbox_number) |= (uint32_t)(TMI_EFID(transmit_message->tx_efid) | \
                                               transmit_message->tx_ff | \
                                               transmit_message->tx_ft);
    }

    if(CAN_FDF_CLASSIC == transmit_message->fd_flag) {
        /* set the data length */
        CAN_TMP(can_periph, mailbox_number) &= ~(CAN_TMP_DLENC | CAN_TMP_ESI | CAN_TMP_BRS | CAN_TMP_FDF);
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
    } else {
        canfd_en = CAN_FDCTL(can_periph) & CAN_FDCTL_FDEN;
        /* check FD function has been enabled */
        if(canfd_en) {
            if(transmit_message->tx_dlen <= 8U) {
                /* set the data length */
                reg_temp |= transmit_message->tx_dlen;
            } else {
                /* data length greater than 8 */
                for(i = 0U; i < 7U; i++) {
                    if(transmit_message->tx_dlen == g_can_fdlength_table[i]) {
                        hit = 1U;
                        break;
                    }
                }
                /* data length is valid */
                if(1U == hit) {
                    reg_temp |= 9U + i;
                } else {
                    CAN_ERROR_HANDLE("dlen is invalid \r\n");
                }
            }
            reg_temp |= (((uint32_t)transmit_message->fd_brs << 5U) | ((uint32_t)transmit_message->fd_esi << 4U) | ((
                             uint32_t)transmit_message->fd_flag << 7U));
            CAN_TMP(can_periph, mailbox_number) = reg_temp;

            /* set the data */
            i = transmit_message->tx_dlen / 4U;

            /* data length is 5-7 need send 2 word */
            if((1U == i) && (4U != transmit_message->tx_dlen)) {
                i++;
            }
            p_temp = (uint32_t)transmit_message->tx_data;
            if((0U == i)) {
                CAN_TMDATA0(can_periph, mailbox_number) = *(uint32_t *)p_temp;
            } else {
                for(; i > 0U; i--) {
                    CAN_TMDATA0(can_periph, mailbox_number) = *(uint32_t *)p_temp;
                    p_temp = ((uint32_t)((uint32_t)p_temp + 4U));
                }
            }

        } else {
            CAN_ERROR_HANDLE("CAN FD function disabled \r\n");
        }
    }

    /* enable transmission */
    CAN_TMI(can_periph, mailbox_number) |= CAN_TMI_TEN;

    return mailbox_number;
}

/*!
    \brief      get CAN transmit state
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  mailbox_number
                only one parameter can be selected which is shown as below:
      \arg        CAN_MAILBOX(x=0,1,2)
    \param[out] none
    \retval     can_transmit_state_enum
*/
can_transmit_state_enum can_transmit_states(uint32_t can_periph, uint8_t mailbox_number)
{
    can_transmit_state_enum state = CAN_TRANSMIT_FAILED;
    uint32_t val = 0U;

    /* check selected mailbox state */
    switch(mailbox_number) {
    /* mailbox0 */
    case CAN_MAILBOX0:
        val = CAN_TSTAT(can_periph) & (CAN_TSTAT_MTF0 | CAN_TSTAT_MTFNERR0 | CAN_TSTAT_TME0);
        break;
    /* mailbox1 */
    case CAN_MAILBOX1:
        val = CAN_TSTAT(can_periph) & (CAN_TSTAT_MTF1 | CAN_TSTAT_MTFNERR1 | CAN_TSTAT_TME1);
        break;
    /* mailbox2 */
    case CAN_MAILBOX2:
        val = CAN_TSTAT(can_periph) & (CAN_TSTAT_MTF2 | CAN_TSTAT_MTFNERR2 | CAN_TSTAT_TME2);
        break;
    default:
        val = CAN_TRANSMIT_FAILED;
        break;
    }

    switch(val) {
    /* transmit pending */
    case(CAN_STATE_PENDING):
        state = CAN_TRANSMIT_PENDING;
        break;
    /* mailbox0 transmit succeeded */
    case(CAN_TSTAT_MTF0 | CAN_TSTAT_MTFNERR0 | CAN_TSTAT_TME0):
        state = CAN_TRANSMIT_OK;
        break;
    /* mailbox1 transmit succeeded */
    case(CAN_TSTAT_MTF1 | CAN_TSTAT_MTFNERR1 | CAN_TSTAT_TME1):
        state = CAN_TRANSMIT_OK;
        break;
    /* mailbox2 transmit succeeded */
    case(CAN_TSTAT_MTF2 | CAN_TSTAT_MTFNERR2 | CAN_TSTAT_TME2):
        state = CAN_TRANSMIT_OK;
        break;
    /* transmit failed */
    default:
        state = CAN_TRANSMIT_FAILED;
        break;
    }
    return state;
}

/*!
    \brief      stop CAN transmission
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  mailbox_number
                only one parameter can be selected which is shown as below:
      \arg        CAN_MAILBOXx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_transmission_stop(uint32_t can_periph, uint8_t mailbox_number)
{
    if(CAN_MAILBOX0 == mailbox_number) {
        CAN_TSTAT(can_periph) |= CAN_TSTAT_MST0;
        while(CAN_TSTAT_MST0 == (CAN_TSTAT(can_periph) & CAN_TSTAT_MST0)) {
        }
    } else if(CAN_MAILBOX1 == mailbox_number) {
        CAN_TSTAT(can_periph) |= CAN_TSTAT_MST1;
        while(CAN_TSTAT_MST1 == (CAN_TSTAT(can_periph) & CAN_TSTAT_MST1)) {
        }
    } else if(CAN_MAILBOX2 == mailbox_number) {
        CAN_TSTAT(can_periph) |= CAN_TSTAT_MST2;
        while(CAN_TSTAT_MST2 == (CAN_TSTAT(can_periph) & CAN_TSTAT_MST2)) {
        }
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      CAN receive message
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  fifo_number
      \arg        CAN_FIFOx(x=0,1)
    \param[out] receive_message: struct for CAN receive message
      \arg        rx_sfid: 0x00000000 - 0x000007FF
      \arg        rx_efid: 0x00000000 - 0x1FFFFFFF
      \arg        rx_ff: CAN_FF_STANDARD, CAN_FF_EXTENDED
      \arg        rx_ft: CAN_FT_DATA, CAN_FT_REMOTE
      \arg        rx_dlen: 0 - 8 (FD mode: 0 - 8, or 12, 16, 20, 24, 32, 48, 64)
      \arg        rx_data[]: 0x00 - 0xFF
      \arg        rx_fi: 0 - 27
    \retval     none
*/
void can_message_receive(uint32_t can_periph, uint8_t fifo_number, can_receive_message_struct *receive_message)
{
    uint32_t canfd_en = 0U;
    volatile uint32_t p_temp;
    uint32_t data_temp;
    uint8_t canfd_recv_cnt = 0U;
    uint8_t i;

    /* get the frame format */
    receive_message->rx_ff = (uint8_t)(CAN_RFIFOMI_FF & CAN_RFIFOMI(can_periph, fifo_number));
    if(CAN_FF_STANDARD == receive_message->rx_ff) {
        /* get standard identifier */
        receive_message->rx_sfid = (uint32_t)(GET_RFIFOMI_SFID(CAN_RFIFOMI(can_periph, fifo_number)));
    } else {
        /* get extended identifier */
        receive_message->rx_efid = (uint32_t)(GET_RFIFOMI_EFID(CAN_RFIFOMI(can_periph, fifo_number)));
    }

    /* get frame type */
    receive_message->rx_ft = (uint8_t)(CAN_RFIFOMI_FT & CAN_RFIFOMI(can_periph, fifo_number));
    /* filtering index */
    receive_message->rx_fi = (uint8_t)(GET_RFIFOMP_FI(CAN_RFIFOMP(can_periph, fifo_number)));
    receive_message->fd_flag = (uint8_t)((CAN_RFIFOMP_FDF & CAN_RFIFOMP(can_periph, fifo_number)) >> 7);

    canfd_en = CAN_FDCTL(can_periph) & CAN_FDCTL_FDEN;
    if(!canfd_en) {
        if(CAN_FDF_CLASSIC == receive_message->fd_flag) {
            /* get receive data length */
            receive_message->rx_dlen = (uint8_t)(GET_RFIFOMP_DLENC(CAN_RFIFOMP(can_periph, fifo_number)));
            /* receive data */
            receive_message->rx_data[0] = (uint8_t)(GET_RFIFOMDATA0_DB0(CAN_RFIFOMDATA0(can_periph, fifo_number)));
            receive_message->rx_data[1] = (uint8_t)(GET_RFIFOMDATA0_DB1(CAN_RFIFOMDATA0(can_periph, fifo_number)));
            receive_message->rx_data[2] = (uint8_t)(GET_RFIFOMDATA0_DB2(CAN_RFIFOMDATA0(can_periph, fifo_number)));
            receive_message->rx_data[3] = (uint8_t)(GET_RFIFOMDATA0_DB3(CAN_RFIFOMDATA0(can_periph, fifo_number)));
            receive_message->rx_data[4] = (uint8_t)(GET_RFIFOMDATA1_DB4(CAN_RFIFOMDATA1(can_periph, fifo_number)));
            receive_message->rx_data[5] = (uint8_t)(GET_RFIFOMDATA1_DB5(CAN_RFIFOMDATA1(can_periph, fifo_number)));
            receive_message->rx_data[6] = (uint8_t)(GET_RFIFOMDATA1_DB6(CAN_RFIFOMDATA1(can_periph, fifo_number)));
            receive_message->rx_data[7] = (uint8_t)(GET_RFIFOMDATA1_DB7(CAN_RFIFOMDATA1(can_periph, fifo_number)));
        } else {
            CAN_ERROR_HANDLE("CAN FD function disabled \r\n");
        }
    } else {
        /* check FD function has been enabled */
        /* get receive data length */
        canfd_recv_cnt = (uint8_t)(GET_RFIFOMP_DLENC(CAN_RFIFOMP(can_periph, fifo_number)));

        if(canfd_recv_cnt <= 8U) {
            /* set the data length */
            receive_message->rx_dlen = canfd_recv_cnt;
        } else {
            receive_message->rx_dlen = g_can_fdlength_table[canfd_recv_cnt - 9U];
        }

        receive_message->fd_brs = (uint8_t)((CAN_RFIFOMP(can_periph, fifo_number) & CAN_RFIFOMP_BRS) >> 5);
        receive_message->fd_esi = (uint8_t)((CAN_RFIFOMP(can_periph, fifo_number) & CAN_RFIFOMP_ESI) >> 4);

        /* get the data */
        i = receive_message->rx_dlen / 4U;

        /* data length is 5-7 need receive 2 word */
        if((1U == i) && (4U != receive_message->rx_dlen)) {
            i++;
        }
        p_temp = (uint32_t)(uint32_t)receive_message->rx_data;
        if(0U == i) {
            data_temp = CAN_RFIFOMDATA0(can_periph, fifo_number);
            *(uint32_t *)p_temp = data_temp;
        } else {
            /* get the data by reading from CAN_RFIFOMDATA0 register*/
            for(; i > 0U; i--) {
                data_temp = CAN_RFIFOMDATA0(can_periph, fifo_number);
                *(uint32_t *)p_temp = data_temp;
                p_temp = ((uint32_t)((uint32_t)p_temp + 4U));
            }
        }
    }

    /* release FIFO */
    if(CAN_FIFO0 == fifo_number) {
        CAN_RFIFO0(can_periph) |= CAN_RFIFO0_RFD0;
    } else {
        CAN_RFIFO1(can_periph) |= CAN_RFIFO1_RFD1;
    }
}

/*!
    \brief      release FIFO
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  fifo_number
                only one parameter can be selected which is shown as below:
      \arg        CAN_FIFOx(x=0,1)
    \param[out] none
    \retval     none
*/
void can_fifo_release(uint32_t can_periph, uint8_t fifo_number)
{
    if(CAN_FIFO0 == fifo_number) {
        CAN_RFIFO0(can_periph) |= CAN_RFIFO0_RFD0;
    } else if(CAN_FIFO1 == fifo_number) {
        CAN_RFIFO1(can_periph) |= CAN_RFIFO1_RFD1;
    } else {
        /* illegal parameters */
        CAN_ERROR_HANDLE("CAN FIFO NUM is invalid \r\n");
    }
}

/*!
    \brief      CAN receive message length
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  fifo_number
                only one parameter can be selected which is shown as below:
      \arg        CAN_FIFOx(x=0,1)
    \param[out] none
    \retval     message length
*/
uint8_t can_receive_message_length_get(uint32_t can_periph, uint8_t fifo_number)
{
    uint8_t val = 0U;

    if(CAN_FIFO0 == fifo_number) {
        /* FIFO0 */
        val = (uint8_t)(CAN_RFIFO0(can_periph) & CAN_RFIF_RFL_MASK);
    } else if(CAN_FIFO1 == fifo_number) {
        /* FIFO1 */
        val = (uint8_t)(CAN_RFIFO1(can_periph) & CAN_RFIF_RFL_MASK);
    } else {
        /* illegal parameters */
    }
    return val;
}

/*!
    \brief      set CAN working mode
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  can_working_mode
                only one parameter can be selected which is shown as below:
      \arg        CAN_MODE_INITIALIZE
      \arg        CAN_MODE_NORMAL
      \arg        CAN_MODE_SLEEP
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_working_mode_set(uint32_t can_periph, uint8_t working_mode)
{
    ErrStatus flag = ERROR;
    /* timeout for IWS or also for SLPWS bits */
    uint32_t timeout = CAN_TIMEOUT;

    if(CAN_MODE_INITIALIZE == working_mode) {
        /* disable sleep mode */
        CAN_CTL(can_periph) &= (~(uint32_t)CAN_CTL_SLPWMOD);
        /* set initialize mode */
        CAN_CTL(can_periph) |= (uint8_t)CAN_CTL_IWMOD;
        /* wait the acknowledge */
        while((CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)) && (0U != timeout)) {
            timeout--;
        }
        if(CAN_STAT_IWS != (CAN_STAT(can_periph) & CAN_STAT_IWS)) {
            flag = ERROR;
        } else {
            flag = SUCCESS;
        }
    } else if(CAN_MODE_NORMAL == working_mode) {
        /* enter normal mode */
        CAN_CTL(can_periph) &= ~(uint32_t)(CAN_CTL_SLPWMOD | CAN_CTL_IWMOD);
        /* wait the acknowledge */
        while((0U != (CAN_STAT(can_periph) & (CAN_STAT_IWS | CAN_STAT_SLPWS))) && (0U != timeout)) {
            timeout--;
        }
        if(0U != (CAN_STAT(can_periph) & (CAN_STAT_IWS | CAN_STAT_SLPWS))) {
            flag = ERROR;
        } else {
            flag = SUCCESS;
        }
    } else if(CAN_MODE_SLEEP == working_mode) {
        /* disable initialize mode */
        CAN_CTL(can_periph) &= (~(uint32_t)CAN_CTL_IWMOD);
        /* set sleep mode */
        CAN_CTL(can_periph) |= (uint8_t)CAN_CTL_SLPWMOD;
        /* wait the acknowledge */
        while((CAN_STAT_SLPWS != (CAN_STAT(can_periph) & CAN_STAT_SLPWS)) && (0U != timeout)) {
            timeout--;
        }
        if(CAN_STAT_SLPWS != (CAN_STAT(can_periph) & CAN_STAT_SLPWS)) {
            flag = ERROR;
        } else {
            flag = SUCCESS;
        }
    } else {
        flag = ERROR;
    }
    return flag;
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

    while((0U != (CAN_STAT(can_periph) & CAN_STAT_SLPWS)) && (0x00U != timeout)) {
        timeout--;
    }
    /* check state */
    if(0U != (CAN_STAT(can_periph) & CAN_STAT_SLPWS)) {
        flag = ERROR;
    } else {
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
      \arg        CAN_ERROR_NONE: no error
      \arg        CAN_ERROR_FILL: fill error
      \arg        CAN_ERROR_FORMATE: format error
      \arg        CAN_ERROR_ACK: ACK error
      \arg        CAN_ERROR_BITRECESSIVE: bit recessive
      \arg        CAN_ERROR_BITDOMINANTER: bit dominant error
      \arg        CAN_ERROR_CRC: CRC error
      \arg        CAN_ERROR_SOFTWARECFG: software configure
*/
can_error_enum can_error_get(uint32_t can_periph)
{
    can_error_enum error;
    error = CAN_ERROR_NONE;

    /* get error type */
    error = (can_error_enum)(GET_ERR_ERRN(CAN_ERR(can_periph)));
    return error;
}

/*!
    \brief      get CAN receive error number
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     error number
*/
uint8_t can_receive_error_number_get(uint32_t can_periph)
{
    uint8_t val;

    /* get error count */
    val = (uint8_t)(GET_ERR_RECNT(CAN_ERR(can_periph)));
    return val;
}

/*!
    \brief      get CAN transmit error number
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[out] none
    \retval     error number
*/
uint8_t can_transmit_error_number_get(uint32_t can_periph)
{
    uint8_t val;

    val = (uint8_t)(GET_ERR_TECNT(CAN_ERR(can_periph)));
    return val;
}

/*!
    \brief      get CAN flag state
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  flag: CAN flags, refer to can_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_FLAG_RXL: RX level
      \arg        CAN_FLAG_LASTRX: last sample value of RX pin
      \arg        CAN_FLAG_RS: receiving state
      \arg        CAN_FLAG_TS: transmitting state
      \arg        CAN_FLAG_SLPIF: status change flag of entering sleep working mode
      \arg        CAN_FLAG_WUIF: status change flag of wakeup from sleep working mode
      \arg        CAN_FLAG_ERRIF: error flag
      \arg        CAN_FLAG_SLPWS: sleep working state
      \arg        CAN_FLAG_IWS: initial working state
      \arg        CAN_FLAG_TMLS2: transmit mailbox 2 last sending in TX FIFO
      \arg        CAN_FLAG_TMLS1: transmit mailbox 1 last sending in TX FIFO
      \arg        CAN_FLAG_TMLS0: transmit mailbox 0 last sending in TX FIFO
      \arg        CAN_FLAG_TME2: transmit mailbox 2 empty
      \arg        CAN_FLAG_TME1: transmit mailbox 1 empty
      \arg        CAN_FLAG_TME0: transmit mailbox 0 empty
      \arg        CAN_FLAG_MTE2: mailbox 2 transmit error
      \arg        CAN_FLAG_MTE1: mailbox 1 transmit error
      \arg        CAN_FLAG_MTE0: mailbox 0 transmit error
      \arg        CAN_FLAG_MAL2: mailbox 2 arbitration lost
      \arg        CAN_FLAG_MAL1: mailbox 1 arbitration lost
      \arg        CAN_FLAG_MAL0: mailbox 0 arbitration lost
      \arg        CAN_FLAG_MTFNERR2: mailbox 2 transmit finished with no error
      \arg        CAN_FLAG_MTFNERR1: mailbox 1 transmit finished with no error
      \arg        CAN_FLAG_MTFNERR0: mailbox 0 transmit finished with no error
      \arg        CAN_FLAG_MTF2: mailbox 2 transmit finished
      \arg        CAN_FLAG_MTF1: mailbox 1 transmit finished
      \arg        CAN_FLAG_MTF0: mailbox 0 transmit finished
      \arg        CAN_FLAG_RFO0: receive FIFO0 overfull
      \arg        CAN_FLAG_RFF0: receive FIFO0 full
      \arg        CAN_FLAG_RFO1: receive FIFO1 overfull
      \arg        CAN_FLAG_RFF1: receive FIFO1 full
      \arg        CAN_FLAG_BOERR: bus-off error
      \arg        CAN_FLAG_PERR: passive error
      \arg        CAN_FLAG_WERR: warning error
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_flag_get(uint32_t can_periph, can_flag_enum flag)
{
    /* get flag and interrupt enable state */
    if(RESET != (CAN_REG_VAL(can_periph, flag) & BIT(CAN_BIT_POS(flag)))) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear CAN flag state
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  flag: CAN flags, refer to can_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_FLAG_SLPIF: status change flag of entering sleep working mode
      \arg        CAN_FLAG_WUIF: status change flag of wakeup from sleep working mode
      \arg        CAN_FLAG_ERRIF: error flag
      \arg        CAN_FLAG_MTE2: mailbox 2 transmit error
      \arg        CAN_FLAG_MTE1: mailbox 1 transmit error
      \arg        CAN_FLAG_MTE0: mailbox 0 transmit error
      \arg        CAN_FLAG_MAL2: mailbox 2 arbitration lost
      \arg        CAN_FLAG_MAL1: mailbox 1 arbitration lost
      \arg        CAN_FLAG_MAL0: mailbox 0 arbitration lost
      \arg        CAN_FLAG_MTFNERR2: mailbox 2 transmit finished with no error
      \arg        CAN_FLAG_MTFNERR1: mailbox 1 transmit finished with no error
      \arg        CAN_FLAG_MTFNERR0: mailbox 0 transmit finished with no error
      \arg        CAN_FLAG_MTF2: mailbox 2 transmit finished
      \arg        CAN_FLAG_MTF1: mailbox 1 transmit finished
      \arg        CAN_FLAG_MTF0: mailbox 0 transmit finished
      \arg        CAN_FLAG_RFO0: receive FIFO0 overfull
      \arg        CAN_FLAG_RFF0: receive FIFO0 full
      \arg        CAN_FLAG_RFO1: receive FIFO1 overfull
      \arg        CAN_FLAG_RFF1: receive FIFO1 full
    \param[out] none
    \retval     none
*/
void can_flag_clear(uint32_t can_periph, can_flag_enum flag)
{
    CAN_REG_VAL(can_periph, flag) = BIT(CAN_BIT_POS(flag));
}

/*!
    \brief      enable CAN interrupt
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  interrupt
                one or more parameters can be selected which are shown as below:
      \arg        CAN_INT_TME: transmit mailbox empty interrupt enable
      \arg        CAN_INT_RFNE0: receive FIFO0 not empty interrupt enable
      \arg        CAN_INT_RFF0: receive FIFO0 full interrupt enable
      \arg        CAN_INT_RFO0: receive FIFO0 overfull interrupt enable
      \arg        CAN_INT_RFNE1: receive FIFO1 not empty interrupt enable
      \arg        CAN_INT_RFF1: receive FIFO1 full interrupt enable
      \arg        CAN_INT_RFO1: receive FIFO1 overfull interrupt enable
      \arg        CAN_INT_WERR: warning error interrupt enable
      \arg        CAN_INT_PERR: passive error interrupt enable
      \arg        CAN_INT_BO: bus-off interrupt enable
      \arg        CAN_INT_ERRN: error number interrupt enable
      \arg        CAN_INT_ERR: error interrupt enable
      \arg        CAN_INT_WAKEUP: wakeup interrupt enable
      \arg        CAN_INT_SLPW: sleep working interrupt enable
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
                one or more parameters can be selected which are shown as below:
      \arg        CAN_INT_TME: transmit mailbox empty interrupt enable
      \arg        CAN_INT_RFNE0: receive FIFO0 not empty interrupt enable
      \arg        CAN_INT_RFF0: receive FIFO0 full interrupt enable
      \arg        CAN_INT_RFO0: receive FIFO0 overfull interrupt enable
      \arg        CAN_INT_RFNE1: receive FIFO1 not empty interrupt enable
      \arg        CAN_INT_RFF1: receive FIFO1 full interrupt enable
      \arg        CAN_INT_RFO1: receive FIFO1 overfull interrupt enable
      \arg        CAN_INT_WERR: warning error interrupt enable
      \arg        CAN_INT_PERR: passive error interrupt enable
      \arg        CAN_INT_BO: bus-off interrupt enable
      \arg        CAN_INT_ERRN: error number interrupt enable
      \arg        CAN_INT_ERR: error interrupt enable
      \arg        CAN_INT_WAKEUP: wakeup interrupt enable
      \arg        CAN_INT_SLPW: sleep working interrupt enable
    \param[out] none
    \retval     none
*/
void can_interrupt_disable(uint32_t can_periph, uint32_t interrupt)
{
    CAN_INTEN(can_periph) &= ~interrupt;
}

/*!
    \brief      get CAN interrupt flag state
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  flag: CAN interrupt flags, refer to can_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_FLAG_SLPIF: status change interrupt flag of sleep working mode entering
      \arg        CAN_INT_FLAG_WUIF: status change interrupt flag of wakeup from sleep working mode
      \arg        CAN_INT_FLAG_ERRIF: error interrupt flag
      \arg        CAN_INT_FLAG_MTF2: mailbox 2 transmit finished interrupt flag
      \arg        CAN_INT_FLAG_MTF1: mailbox 1 transmit finished interrupt flag
      \arg        CAN_INT_FLAG_MTF0: mailbox 0 transmit finished interrupt flag
      \arg        CAN_INT_FLAG_RFO0: receive FIFO0 overfull interrupt flag
      \arg        CAN_INT_FLAG_RFF0: receive FIFO0 full interrupt flag
      \arg        CAN_INT_FLAG_RFL0: receive FIFO0 not empty interrupt flag
      \arg        CAN_INT_FLAG_RFO1: receive FIFO1 overfull interrupt flag
      \arg        CAN_INT_FLAG_RFF1: receive FIFO1 full interrupt flag
      \arg        CAN_INT_FLAG_RFL1: receive FIFO1 not empty interrupt flag
      \arg        CAN_INT_FLAG_ERRN: error number interrupt flag
      \arg        CAN_INT_FLAG_BOERR: bus-off error interrupt flag
      \arg        CAN_INT_FLAG_PERR: passive error interrupt flag
      \arg        CAN_INT_FLAG_WERR: warning error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_interrupt_flag_get(uint32_t can_periph, can_interrupt_flag_enum flag)
{
    uint32_t ret1 = RESET;
    uint32_t ret2 = RESET;

    /* get the status of interrupt flag */
    if(flag == CAN_INT_FLAG_RFL0) {
        ret1 = can_receive_message_length_get(can_periph, CAN_FIFO0);
    } else if(flag == CAN_INT_FLAG_RFL1) {
        ret1 = can_receive_message_length_get(can_periph, CAN_FIFO1);
    } else if(flag == CAN_INT_FLAG_ERRN) {
        ret1 = can_error_get(can_periph);
    } else {
        ret1 = CAN_REG_VALS(can_periph, flag) & BIT(CAN_BIT_POS0(flag));
    }
    /* get the status of interrupt enable bit */
    ret2 = CAN_INTEN(can_periph) & BIT(CAN_BIT_POS1(flag));
    if(ret1 && ret2) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear CAN interrupt flag state
    \param[in]  can_periph
      \arg        CANx(x=0,1)
    \param[in]  flag: CAN interrupt flags, refer to can_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_FLAG_SLPIF: status change interrupt flag of sleep working mode entering
      \arg        CAN_INT_FLAG_WUIF: status change interrupt flag of wakeup from sleep working mode
      \arg        CAN_INT_FLAG_ERRIF: error interrupt flag
      \arg        CAN_INT_FLAG_MTF2: mailbox 2 transmit finished interrupt flag
      \arg        CAN_INT_FLAG_MTF1: mailbox 1 transmit finished interrupt flag
      \arg        CAN_INT_FLAG_MTF0: mailbox 0 transmit finished interrupt flag
      \arg        CAN_INT_FLAG_RFO0: receive FIFO0 overfull interrupt flag
      \arg        CAN_INT_FLAG_RFF0: receive FIFO0 full interrupt flag
      \arg        CAN_INT_FLAG_RFO1: receive FIFO1 overfull interrupt flag
      \arg        CAN_INT_FLAG_RFF1: receive FIFO1 full interrupt flag
    \param[out] none
    \retval     none
*/
void can_interrupt_flag_clear(uint32_t can_periph, can_interrupt_flag_enum flag)
{
    CAN_REG_VALS(can_periph, flag) = BIT(CAN_BIT_POS0(flag));
}
