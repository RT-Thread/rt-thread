/*!
    \file    gd32h7xx_can.c
    \brief   CAN driver

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

#include "gd32h7xx_can.h"

/* DLC to data size in bytes definitions */
static const uint8_t dlc_to_databytes[16] = {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U};

/* computes the maximum payload size (in bytes) */
static uint32_t can_payload_size_compute(uint32_t mdes0);
/* swap data to little endian */
static void can_data_to_little_endian_swap(uint32_t dest[], uint32_t src[], uint32_t len);
/* swap data to big endian */
static void can_data_to_big_endian_swap(uint32_t dest[], uint32_t src[], uint32_t len);
/* computes the dlc field value, given a payload size (in bytes) */
static uint32_t can_dlc_value_compute(uint32_t payload_size);

/*!
    \brief      deinitialize CAN
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_deinit(uint32_t can_periph)
{
    if(CAN0 == can_periph)
    {
        /* reset CAN0 */
        rcu_periph_reset_enable(RCU_CAN0RST);
        rcu_periph_reset_disable(RCU_CAN0RST);
    }
    if(CAN1 == can_periph)
    {
        /* reset CAN1 */
        rcu_periph_reset_enable(RCU_CAN1RST);
        rcu_periph_reset_disable(RCU_CAN1RST);
    }
    if(CAN2 == can_periph)
    {
        /* reset CAN2 */
        rcu_periph_reset_enable(RCU_CAN2RST);
        rcu_periph_reset_disable(RCU_CAN2RST);
    }
}

/*!
    \brief      reset CAN internal state machines and CAN registers
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus can_software_reset(uint32_t can_periph)
{
    uint32_t timeout = CAN_DELAY;

    /* reset internal state machines and CAN registers */
    CAN_CTL0(can_periph) |= CAN_CTL0_SWRST;
    /* wait reset complete */
    while((CAN_CTL0(can_periph) & CAN_CTL0_SWRST) && (timeout))
    {
        timeout--;
    }
    if(CAN_CTL0(can_periph) & CAN_CTL0_SWRST)
    {
        return ERROR;
    }
    return SUCCESS;
}

/*!
    \brief      CAN module initialization
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  can_parameter_init: can parameter struct
                  internal_counter_source: CAN_TIMER_SOURCE_BIT_CLOCK, CAN_TIMER_SOURCE_EXTERNAL_TIME_TICK
                  self_reception: ENABLE, DISABLE
                  mb_tx_order: CAN_TX_HIGH_PRIORITY_MB_FIRST, CAN_TX_LOW_NUM_MB_FIRST
                  mb_tx_abort_enable: ENABLE, DISABLE
                  local_priority_enable: ENABLE, DISABLE
                  mb_rx_ide_rtr_type: CAN_IDE_RTR_COMPARED, CAN_IDE_RTR_FILTERED
                  mb_remote_frame: CAN_GEN_REMOTE_RESPONSE_FRAME, CAN_STORE_REMOTE_REQUEST_FRAME
                  rx_private_filter_queue_enable: ENABLE, DISABLE
                  edge_filter_enable: ENABLE, DISABLE
                  protocol_exception_enable: ENABLE, DISABLE
                  rx_filter_order: CAN_RX_FILTER_ORDER_FIFO_FIRST, CAN_RX_FILTER_ORDER_MAILBOX_FIRST
                  memory_size: CAN_MEMSIZE_1_UNIT, CAN_MEMSIZE_2_UNIT, CAN_MEMSIZE_3_UNIT, CAN_MEMSIZE_4_UNIT,
                               CAN_MEMSIZE_5_UNIT, CAN_MEMSIZE_6_UNIT, CAN_MEMSIZE_7_UNIT, CAN_MEMSIZE_8_UNIT,
                               CAN_MEMSIZE_9_UNIT, CAN_MEMSIZE_10_UNIT, CAN_MEMSIZE_11_UNIT, CAN_MEMSIZE_12_UNIT,
                               CAN_MEMSIZE_13_UNIT, CAN_MEMSIZE_14_UNIT, CAN_MEMSIZE_15_UNIT, CAN_MEMSIZE_16_UNIT,
                               CAN_MEMSIZE_17_UNIT, CAN_MEMSIZE_18_UNIT, CAN_MEMSIZE_19_UNIT, CAN_MEMSIZE_20_UNIT,
                               CAN_MEMSIZE_21_UNIT, CAN_MEMSIZE_22_UNIT, CAN_MEMSIZE_23_UNIT, CAN_MEMSIZE_24_UNIT,
                               CAN_MEMSIZE_25_UNIT, CAN_MEMSIZE_26_UNIT, CAN_MEMSIZE_27_UNIT, CAN_MEMSIZE_28_UNIT,
                               CAN_MEMSIZE_29_UNIT, CAN_MEMSIZE_30_UNIT, CAN_MEMSIZE_31_UNIT, CAN_MEMSIZE_32_UNIT
                  mb_public_filter: 0x00000000 ~ 0xFFFFFFFF
                  prescaler: 1~1024
                  resync_jump_width: 1~32
                  prop_time_segment: 1~64
                  time_segment_1: 1~32
                  time_segment_2: 1~32
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus can_init(uint32_t can_periph, can_parameter_struct *can_parameter_init)
{
    uint32_t i;
    uint32_t *canram = (uint32_t *)(CAN_RAM(can_periph));

    /* clear CAN RAM */
    for(i = 0U; i < CAN_MAX_RAM_SIZE; i++)
    {
        canram[i] = 0U;
    }
    /* reset CAN_RFIFOMPFx */
    for(i = 0U; i < CAN_MAX_MAILBOX_NUM; i++)
    {
        CAN_RFIFOMPF(can_periph, i) = 0x00000000U;
    }

    /* reset internal state machines and CAN registers */
    if(ERROR == can_software_reset(can_periph))
    {
        return ERROR;
    }

    /* reset CAN_INTEN */
    CAN_INTEN(can_periph) = 0U;
    /* reset CAN_STAT */
    CAN_STAT(can_periph) = (uint32_t)0xFFFFFFFFU;
    CAN_TIMER(can_periph);
    while(CAN_STAT(can_periph) & CAN_STAT_MS5_RFNE)
    {
        CAN_STAT(can_periph) = CAN_STAT_MS5_RFNE;
    }

    /* clear register bits */
    CAN_CTL0(can_periph) &= ~(CAN_CTL0_RFEN | CAN_CTL0_FDEN | CAN_CTL0_SRDIS | CAN_CTL0_LAPRIOEN | CAN_CTL0_MST | CAN_CTL0_RPFQEN | CAN_CTL0_MSZ);
    CAN_CTL2(can_periph) &= ~(CAN_CTL2_ITSRC | CAN_CTL2_IDERTR_RMF | CAN_CTL2_RRFRMS | CAN_CTL2_RFO | CAN_CTL2_EFDIS | CAN_CTL2_PREEN);
    CAN_CTL1(can_periph) &= ~CAN_CTL1_MTO;
    CAN_BT(can_periph) &= ~(CAN_BT_BAUDPSC | CAN_BT_SJW | CAN_BT_PTS | CAN_BT_PBS1 | CAN_BT_PBS2);

    /* set self reception */
    if((uint8_t)DISABLE == can_parameter_init->self_reception)
    {
        CAN_CTL0(can_periph) |= CAN_CTL0_SRDIS;
    }
    /* enable local arbitration priority */
    if((uint8_t)ENABLE == can_parameter_init->local_priority_enable)
    {
        CAN_CTL0(can_periph) |= CAN_CTL0_LAPRIOEN;
    }
    /* set rx private filters and mailbox queue */
    if((uint8_t)ENABLE == can_parameter_init->rx_private_filter_queue_enable)
    {
        CAN_CTL0(can_periph) |= CAN_CTL0_RPFQEN;
    }
    /* configure edge filtering */
    if((uint32_t)DISABLE == can_parameter_init->edge_filter_enable)
    {
        CAN_CTL2(can_periph) |= CAN_CTL2_EFDIS;
    }
    /* configure protocol exception */
    if((uint32_t)ENABLE == can_parameter_init->protocol_exception_enable)
    {
        CAN_CTL2(can_periph) |= CAN_CTL2_PREEN;
    }
    /* set mailbox stop transmission */
    if((uint8_t)ENABLE == can_parameter_init->mb_tx_abort_enable)
    {
        CAN_CTL0(can_periph) |= CAN_CTL0_MST;
    }

    /* set internal counter source */
    CAN_CTL2(can_periph) |= can_parameter_init->internal_counter_source;
    /* set mailbox arbitration process order */
    CAN_CTL1(can_periph) |= can_parameter_init->mb_tx_order;
    /* set IDE and RTR field filter type */
    CAN_CTL2(can_periph) |= can_parameter_init->mb_rx_ide_rtr_type;
    /* configure remote request frame */
    CAN_CTL2(can_periph) |= can_parameter_init->mb_remote_frame;
    /* set mailbox public filter */
    CAN_RMPUBF(can_periph) = can_parameter_init->mb_public_filter;
    /* configure receive filter order */
    CAN_CTL2(can_periph) |= can_parameter_init->rx_filter_order;
    /* set memory size */
    CAN_CTL0(can_periph) |= can_parameter_init->memory_size;
    /* set time segment */
    CAN_BT(can_periph) |= (uint32_t)(BT_BAUDPSC(can_parameter_init->prescaler - 1U) |
                                     BT_SJW((uint32_t)can_parameter_init->resync_jump_width - 1U) |
                                     BT_PTS((uint32_t)can_parameter_init->prop_time_segment - 1U) |
                                     BT_PBS1((uint32_t)can_parameter_init->time_segment_1 - 1U) |
                                     BT_PBS2((uint32_t)can_parameter_init->time_segment_2 - 1U));

    return SUCCESS;
}

/*!
    \brief      initialize CAN parameter structure with a default value
    \param[in]  type: the type of CAN parameter struct
                only one parameter can be selected which is shown as below:
      \arg        CAN_INIT_STRUCT: the CAN initial struct
      \arg        CAN_FD_INIT_STRUCT: the CAN FD initial struct
      \arg        CAN_FIFO_INIT_STRUCT: the CAN FIFO initial struct
      \arg        CAN_PN_MODE_INIT_STRUCT: the CAN Pretended Networking mode initial struct
      \arg        CAN_PN_MODE_FILTER_STRUCT: the CAN Pretended Networking mode filter struct
      \arg        CAN_MDSC_STRUCT: mailbox descriptor strcut
      \arg        CAN_FDES_STRUCT: Rx fifo descriptor strcut
      \arg        CAN_FIFO_ID_FILTER_STRUCT: Rx fifo id filter strcut
      \arg        CAN_CRC_STRUCT: CRC strcut
      \arg        CAN_ERRCNT_STRUCT: error counter strcut
    \param[in]  p_struct: the pointer of the specific struct
    \param[out] none
    \retval     none
*/
void can_struct_para_init(can_struct_type_enum type, void *p_struct)
{
    /* get type of the struct */
    switch(type)
    {
    /* used for initialize can_parameter_struct */
    case CAN_INIT_STRUCT:
        ((can_parameter_struct *)p_struct)->self_reception = (uint8_t)DISABLE;
        ((can_parameter_struct *)p_struct)->internal_counter_source = CAN_TIMER_SOURCE_BIT_CLOCK;
        ((can_parameter_struct *)p_struct)->mb_tx_order = CAN_TX_HIGH_PRIORITY_MB_FIRST;
        ((can_parameter_struct *)p_struct)->mb_tx_abort_enable = (uint8_t)ENABLE;
        ((can_parameter_struct *)p_struct)->local_priority_enable = (uint8_t)DISABLE;
        ((can_parameter_struct *)p_struct)->mb_rx_ide_rtr_type = CAN_IDE_RTR_COMPARED;
        ((can_parameter_struct *)p_struct)->mb_remote_frame = CAN_STORE_REMOTE_REQUEST_FRAME;
        ((can_parameter_struct *)p_struct)->rx_private_filter_queue_enable = (uint8_t)DISABLE;
        ((can_parameter_struct *)p_struct)->edge_filter_enable = (uint32_t)DISABLE;
        ((can_parameter_struct *)p_struct)->protocol_exception_enable = (uint32_t)DISABLE;
        ((can_parameter_struct *)p_struct)->rx_filter_order = CAN_RX_FILTER_ORDER_FIFO_FIRST;
        ((can_parameter_struct *)p_struct)->memory_size = CAN_MEMSIZE_32_UNIT;
        ((can_parameter_struct *)p_struct)->mb_public_filter = 0xFFFFFFFFU;
        ((can_parameter_struct *)p_struct)->prescaler = 0x00000001U;
        ((can_parameter_struct *)p_struct)->resync_jump_width = 0x01U;
        ((can_parameter_struct *)p_struct)->prop_time_segment = 0x01U;
        ((can_parameter_struct *)p_struct)->time_segment_1 = 0x01U;
        ((can_parameter_struct *)p_struct)->time_segment_2 = 0x01U;
        break;
    /* used for initialize can_fd_parameter_struct */
    case CAN_FD_INIT_STRUCT:
        ((can_fd_parameter_struct *)p_struct)->iso_can_fd_enable = (uint32_t)DISABLE;
        ((can_fd_parameter_struct *)p_struct)->bitrate_switch_enable = (uint32_t)ENABLE;
        ((can_fd_parameter_struct *)p_struct)->mailbox_data_size = CAN_MAILBOX_DATA_SIZE_8_BYTES;
        ((can_fd_parameter_struct *)p_struct)->tdc_enable = (uint32_t)DISABLE;
        ((can_fd_parameter_struct *)p_struct)->tdc_offset = 0x00U;
        ((can_fd_parameter_struct *)p_struct)->prescaler = 0x00000001U;
        ((can_fd_parameter_struct *)p_struct)->resync_jump_width = 0x01U;
        ((can_fd_parameter_struct *)p_struct)->prop_time_segment = 0x00U;
        ((can_fd_parameter_struct *)p_struct)->time_segment_1 = 0x01U;
        ((can_fd_parameter_struct *)p_struct)->time_segment_2 = 0x01U;
        break;
    /* used for initialize can_fifo_parameter_struct */
    case CAN_FIFO_INIT_STRUCT:
        ((can_fifo_parameter_struct *)p_struct)->dma_enable = (uint8_t)DISABLE;
        ((can_fifo_parameter_struct *)p_struct)->filter_format_and_number = CAN_RXFIFO_FILTER_A_NUM_8;
        ((can_fifo_parameter_struct *)p_struct)->fifo_public_filter = 0xFFFFFFFFU;
        break;
    /* used for initialize can_pn_mode_config_struct */
    case CAN_PN_MODE_INIT_STRUCT:
        ((can_pn_mode_config_struct *)p_struct)->timeout_int = (uint32_t)DISABLE;
        ((can_pn_mode_config_struct *)p_struct)->match_int = (uint32_t)DISABLE;
        ((can_pn_mode_config_struct *)p_struct)->num_matches = 0x01U;
        ((can_pn_mode_config_struct *)p_struct)->match_timeout = 0x0000U;
        ((can_pn_mode_config_struct *)p_struct)->frame_filter = CAN_PN_FRAME_FILTERING_ID;
        ((can_pn_mode_config_struct *)p_struct)->id_filter = CAN_PN_ID_FILTERING_EXACT;
        ((can_pn_mode_config_struct *)p_struct)->data_filter = CAN_PN_DATA_FILTERING_EXACT;
        break;
    /* used for initialize can_pn_mode_filter_struct */
    case CAN_PN_MODE_FILTER_STRUCT:
        ((can_pn_mode_filter_struct *)p_struct)->rtr = (uint32_t)RESET;
        ((can_pn_mode_filter_struct *)p_struct)->ide = (uint32_t)RESET;
        ((can_pn_mode_filter_struct *)p_struct)->id = 0x00000000U;
        ((can_pn_mode_filter_struct *)p_struct)->dlc_high_threshold = 0x00000000U;
        ((can_pn_mode_filter_struct *)p_struct)->dlc_low_threshold = 0x00000000U;
        ((can_pn_mode_filter_struct *)p_struct)->payload[0] = 0x00000000U;
        ((can_pn_mode_filter_struct *)p_struct)->payload[1] = 0x00000000U;
        break;
    /* used for initialize can_mailbox_descriptor_struct */
    case CAN_MDSC_STRUCT:
        ((can_mailbox_descriptor_struct *)p_struct)->timestamp = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->dlc = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->rtr = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->ide = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->srr = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->reserve1 = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->code = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->reserve2 = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->esi = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->brs = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->fdf = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->id = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->prio = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->data = (void *)0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->data_bytes = 0x00000000U;
        ((can_mailbox_descriptor_struct *)p_struct)->padding = 0x0000U;
        break;
    /* used for initialize can_rx_fifo_struct */
    case CAN_FDES_STRUCT:
        ((can_rx_fifo_struct *)p_struct)->timestamp = 0x00000000U;
        ((can_rx_fifo_struct *)p_struct)->dlc = 0x00000000U;
        ((can_rx_fifo_struct *)p_struct)->rtr = 0x00000000U;
        ((can_rx_fifo_struct *)p_struct)->ide = 0x00000000U;
        ((can_rx_fifo_struct *)p_struct)->srr = 0x00000000U;
        ((can_rx_fifo_struct *)p_struct)->idhit = 0x00000000U;
        ((can_rx_fifo_struct *)p_struct)->id = 0x00000000U;
        ((can_rx_fifo_struct *)p_struct)->data[0] = 0x00000000U;
        ((can_rx_fifo_struct *)p_struct)->data[1] = 0x00000000U;
        break;
    /* used for initialize can_rx_fifo_id_filter_struct */
    case CAN_FIFO_ID_FILTER_STRUCT:
        ((can_rx_fifo_id_filter_struct *)p_struct)->remote_frame = 0x00000000U;
        ((can_rx_fifo_id_filter_struct *)p_struct)->extended_frame = 0x00000000U;
        ((can_rx_fifo_id_filter_struct *)p_struct)->id = 0x00000000U;
        break;
    /* used for initialize can_crc_struct */
    case CAN_CRC_STRUCT:
        ((can_crc_struct *)p_struct)->classical_frm_mb_number = 0x00000000U;
        ((can_crc_struct *)p_struct)->classical_frm_transmitted_crc = 0x00000000U;
        ((can_crc_struct *)p_struct)->classical_fd_frm_mb_number = 0x00000000U;
        ((can_crc_struct *)p_struct)->classical_fd_frm_transmitted_crc = 0x00000000U;
        break;
    /* used for initialize can_crc_struct */
    case CAN_ERRCNT_STRUCT:
        ((can_error_counter_struct *)p_struct)->fd_data_phase_rx_errcnt = 0x00U;
        ((can_error_counter_struct *)p_struct)->fd_data_phase_tx_errcnt = 0x00U;
        ((can_error_counter_struct *)p_struct)->rx_errcnt = 0x00U;
        ((can_error_counter_struct *)p_struct)->tx_errcnt = 0x00U;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure receive fifo/mailbox private filter
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  index: mailbox index
    \param[in]  filter_data: filter data to configure
    \param[out] none
    \retval     none
*/
void can_private_filter_config(uint32_t can_periph, uint32_t index, uint32_t filter_data)
{
    CAN_RFIFOMPF(can_periph, index) = filter_data;
}

/*!
    \brief      enter the corresponding mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  mode: the mode to enter
                only one parameter can be selected which is shown as below:
      \arg        CAN_NORMAL_MODE: normal mode
      \arg        CAN_MONITOR_MODE: monitor mode
      \arg        CAN_LOOPBACK_SILENT_MODE: loopback mode
      \arg        CAN_INACTIVE_MODE: inactive mode
      \arg        CAN_DISABLE_MODE: disable mode
      \arg        CAN_PN_MODE: Pretended Networking mode
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus can_operation_mode_enter(uint32_t can_periph, can_operation_modes_enum mode)
{
    uint32_t timeout;
    ErrStatus ret = SUCCESS;

    /* enter INACTIVE mode */
    /* exit can_disable mode */
    CAN_CTL0(can_periph) &= ~CAN_CTL0_CANDIS;
    /* enter inactive mode */
    CAN_CTL0(can_periph) |= CAN_CTL0_HALT | CAN_CTL0_INAMOD;
    /* exit Pretended Networking mode */
    CAN_CTL0(can_periph) &= ~(CAN_CTL0_PNEN | CAN_CTL0_PNMOD);
    timeout = CAN_DELAY;
    /* wait for inactive mode state */
    while(((CAN_CTL0_NRDY | CAN_CTL0_INAS) != (CAN_CTL0(can_periph) & (CAN_CTL0_NRDY | CAN_CTL0_INAS))) && (timeout))
    {
        timeout--;
    }
    if((CAN_CTL0_NRDY | CAN_CTL0_INAS) != (CAN_CTL0(can_periph) & (CAN_CTL0_NRDY | CAN_CTL0_INAS)))
    {
        return ERROR;
    }

    /* configure the modes */
    switch(mode)
    {
    case CAN_NORMAL_MODE:
        CAN_CTL1(can_periph) &= ~(CAN_CTL1_LSCMOD | CAN_CTL1_MMOD);
        break;
    case CAN_MONITOR_MODE:
        CAN_CTL1(can_periph) &= ~CAN_CTL1_LSCMOD;
        CAN_CTL1(can_periph) |= CAN_CTL1_MMOD;
        break;
    case CAN_LOOPBACK_SILENT_MODE:
        CAN_CTL1(can_periph) &= ~CAN_CTL1_MMOD;
        CAN_CTL0(can_periph) &= ~CAN_CTL0_SRDIS;
        CAN_FDCTL(can_periph) &= ~CAN_FDCTL_TDCEN;
        CAN_CTL1(can_periph) |= CAN_CTL1_LSCMOD;
        break;
    case CAN_INACTIVE_MODE:
        break;
    case CAN_DISABLE_MODE:
        CAN_CTL0(can_periph) |= CAN_CTL0_CANDIS;
        break;
    case CAN_PN_MODE:
        CAN_CTL0(can_periph) |= (CAN_CTL0_PNEN | CAN_CTL0_PNMOD);
        break;
    default:
        break;
    }

    /* exit INACTIVE mode */
    if(CAN_INACTIVE_MODE != mode)
    {
        /* exit inactive mode */
        CAN_CTL0(can_periph) &= ~(CAN_CTL0_HALT | CAN_CTL0_INAMOD);
        timeout = CAN_DELAY;
        while((CAN_CTL0(can_periph) & CAN_CTL0_INAS) && (timeout))
        {
            timeout--;
        }
        if(CAN_CTL0(can_periph) & CAN_CTL0_INAS)
        {
            return ERROR;
        }
    }

    if(CAN_PN_MODE == mode)
    {
        timeout = CAN_DELAY;
        while((0U == (CAN_CTL0(can_periph) & CAN_CTL0_PNS)) && (timeout))
        {
            timeout--;
        }
        if(0U == (CAN_CTL0(can_periph) & CAN_CTL0_PNS))
        {
            return ERROR;
        }
    }
    return ret;
}

/*!
    \brief      get operation mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     can_operation_modes_enum
*/
can_operation_modes_enum can_operation_mode_get(uint32_t can_periph)
{
    uint32_t reg;
    can_operation_modes_enum state = CAN_NORMAL_MODE;

    reg = CAN_CTL0(can_periph);
    reg &= (CAN_CTL0_NRDY | CAN_CTL0_INAS | CAN_CTL0_PNS | CAN_CTL0_LPS);

    if((CAN_CTL0_NRDY | CAN_CTL0_LPS) == reg)
    {
        state = CAN_DISABLE_MODE;
    } else if((CAN_CTL0_NRDY | CAN_CTL0_INAS) == reg)
    {
        state = CAN_INACTIVE_MODE;
    } else if(0U == reg)
    {
        if(CAN_CTL1(can_periph)&CAN_CTL1_MMOD)
        {
            state = CAN_MONITOR_MODE;
        } else if(CAN_CTL1(can_periph)&CAN_CTL1_LSCMOD)
        {
            state = CAN_LOOPBACK_SILENT_MODE;
        } else {
            state = CAN_NORMAL_MODE;
        }
    } else if(CAN_CTL0_PNS == reg)
    {
        state = CAN_PN_MODE;
    } else {
        /* should not get here */
    }

    return state;
}

/*!
    \brief      exit inactive mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus can_inactive_mode_exit(uint32_t can_periph)
{
    uint32_t timeout;

    /* exit inactive mode */
    CAN_CTL0(can_periph) &= ~CAN_CTL0_HALT;
    timeout = CAN_DELAY;
    while((CAN_CTL0(can_periph) & CAN_CTL0_INAS) && (timeout))
    {
        timeout--;
    }
    if(CAN_CTL0(can_periph) & CAN_CTL0_INAS)
    {
        return ERROR;
    } else {
        return SUCCESS;
    }
}

/*!
    \brief      exit Pretended Networking mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  none
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus can_pn_mode_exit(uint32_t can_periph)
{
    uint32_t timeout;

    CAN_CTL0(can_periph) &= ~(CAN_CTL0_PNEN | CAN_CTL0_PNMOD);
    timeout = CAN_DELAY;
    while((CAN_CTL0(can_periph) & CAN_CTL0_PNS) && (timeout))
    {
        timeout--;
    }
    if(CAN_CTL0(can_periph) & CAN_CTL0_PNS)
    {
        return ERROR;
    } else {
        return SUCCESS;
    }
}

/*!
    \brief      can FD initialize
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  can_fd_para_init: can fd parameter struct
                  iso_can_fd_enable: ENABLE, DISABLE
                  bitrate_switch_enable: ENABLE, DISABLE
                  mailbox_data_size: CAN_MAILBOX_DATA_SIZE_8_BYTES, CAN_MAILBOX_DATA_SIZE_16_BYTES,
                                     CAN_MAILBOX_DATA_SIZE_32_BYTES, CAN_MAILBOX_DATA_SIZE_64_BYTES
                  tdc_enable: ENABLE, DISABLE
                  tdc_offset: 0 ~ 31
                  prescaler: 1~1024
                  resync_jump_width: 1~8
                  prop_time_segment: 0~31
                  time_segment_1: 1~8
                  time_segment_2: 2~8
    \param[out] none
    \retval     none
*/
void can_fd_config(uint32_t can_periph, can_fd_parameter_struct *can_fd_para_init)
{
    /* clear register bits, then enable FD mode */
    CAN_CTL0(can_periph) &= ~CAN_CTL0_RFEN;
    CAN_CTL1(can_periph) &= ~CAN_CTL1_BSPMOD;
    CAN_CTL2(can_periph) &= ~CAN_CTL2_ISO;
    CAN_FDCTL(can_periph) &= ~(CAN_FDCTL_BRSEN | CAN_FDCTL_MDSZ | CAN_FDCTL_TDCEN | CAN_FDCTL_TDCO);
    CAN_FDBT(can_periph) &= ~(CAN_FDBT_DBAUDPSC | CAN_FDBT_DSJW | CAN_FDBT_DPTS | CAN_FDBT_DPBS1 | CAN_FDBT_DPBS2);
    CAN_CTL0(can_periph) |= CAN_CTL0_FDEN;

    /* support ISO or non-ISO mode */
    if((uint32_t)ENABLE == can_fd_para_init->iso_can_fd_enable)
    {
        CAN_CTL2(can_periph) |= CAN_CTL2_ISO;
    }
    /* set TDC parameter */
    if((uint32_t)ENABLE == can_fd_para_init->tdc_enable)
    {
        CAN_FDCTL(can_periph) |= CAN_FDCTL_TDCEN;
    }
    /* set data bit rate */
    if((uint32_t)ENABLE == can_fd_para_init->bitrate_switch_enable)
    {
        CAN_FDCTL(can_periph) |= CAN_FDCTL_BRSEN;
    }

    /* set mailbox data size */
    CAN_FDCTL(can_periph) |= can_fd_para_init->mailbox_data_size;
    /* configure FD bit timing */
    CAN_FDBT(can_periph) |= (uint32_t)(FDBT_DBAUDPSC(can_fd_para_init->prescaler - 1U) |
                                       FDBT_DSJW((uint32_t)can_fd_para_init->resync_jump_width - 1U) |
                                       FDBT_DPTS(can_fd_para_init->prop_time_segment) |
                                       FDBT_DPBS1((uint32_t)can_fd_para_init->time_segment_1 - 1U) |
                                       FDBT_DPBS2((uint32_t)can_fd_para_init->time_segment_2 - 1U));
    /* configure transmitter delay compensation offset */
    CAN_FDCTL(can_periph) |= FDCTL_TDCO(can_fd_para_init->tdc_offset);
}

/*!
    \brief      enable bit rate switching
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_bitrate_switch_enable(uint32_t can_periph)
{
    CAN_FDCTL(can_periph) |= CAN_FDCTL_BRSEN;
}

/*!
    \brief      disable bit rate switching
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_bitrate_switch_disable(uint32_t can_periph)
{
    CAN_FDCTL(can_periph) &= ~CAN_FDCTL_BRSEN;
}

/*!
    \brief      get transmitter delay compensation value
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     0 - 0x3F
*/
uint32_t can_tdc_get(uint32_t can_periph)
{
    uint32_t reg = 0U;

    reg = CAN_FDCTL(can_periph);

    return GET_FDCTL_TDCV(reg);
}

/*!
    \brief      enable transmitter delay compensation
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_tdc_enable(uint32_t can_periph)
{
    CAN_FDCTL(can_periph) |= CAN_FDCTL_TDCEN;
}

/*!
    \brief      disable transmitter delay compensation
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_tdc_disable(uint32_t can_periph)
{
    CAN_FDCTL(can_periph) &= ~CAN_FDCTL_TDCEN;
}

/*!
    \brief      configure rx FIFO
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  can_fifo_para_init: fifo parameter struct
                  dma_enable: ENABLE, DISABLE
                  filter_format_and_number: CAN_RXFIFO_FILTER_A_NUM_8, CAN_RXFIFO_FILTER_A_NUM_16, CAN_RXFIFO_FILTER_A_NUM_24, CAN_RXFIFO_FILTER_A_NUM_32,
                                            CAN_RXFIFO_FILTER_A_NUM_40, CAN_RXFIFO_FILTER_A_NUM_48, CAN_RXFIFO_FILTER_A_NUM_56, CAN_RXFIFO_FILTER_A_NUM_64,
                                            CAN_RXFIFO_FILTER_A_NUM_72, CAN_RXFIFO_FILTER_A_NUM_80, CAN_RXFIFO_FILTER_A_NUM_88, CAN_RXFIFO_FILTER_A_NUM_96, CAN_RXFIFO_FILTER_A_NUM_104,
                                            CAN_RXFIFO_FILTER_B_NUM_16, CAN_RXFIFO_FILTER_B_NUM_32, CAN_RXFIFO_FILTER_B_NUM_48, CAN_RXFIFO_FILTER_B_NUM_64,
                                            CAN_RXFIFO_FILTER_B_NUM_80, CAN_RXFIFO_FILTER_B_NUM_96, CAN_RXFIFO_FILTER_B_NUM_112, CAN_RXFIFO_FILTER_B_NUM_128,
                                            CAN_RXFIFO_FILTER_B_NUM_144, CAN_RXFIFO_FILTER_B_NUM_160, CAN_RXFIFO_FILTER_B_NUM_176, CAN_RXFIFO_FILTER_B_NUM_192, CAN_RXFIFO_FILTER_B_NUM_208,
                                            CAN_RXFIFO_FILTER_C_NUM_32, CAN_RXFIFO_FILTER_C_NUM_64, CAN_RXFIFO_FILTER_C_NUM_96, CAN_RXFIFO_FILTER_C_NUM_128,
                                            CAN_RXFIFO_FILTER_C_NUM_160, CAN_RXFIFO_FILTER_C_NUM_192, CAN_RXFIFO_FILTER_C_NUM_224, CAN_RXFIFO_FILTER_C_NUM_256,
                                            CAN_RXFIFO_FILTER_C_NUM_288, CAN_RXFIFO_FILTER_C_NUM_320, CAN_RXFIFO_FILTER_C_NUM_352, CAN_RXFIFO_FILTER_C_NUM_384, CAN_RXFIFO_FILTER_C_NUM_416,
                                            CAN_RXFIFO_FILTER_D
                  fifo_public_filter: 0x00000000 ~ 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void can_rx_fifo_config(uint32_t can_periph, can_fifo_parameter_struct *can_fifo_para_init)
{
    uint32_t num;

    /* clear register bits, disable FD mode, then enable rx FIFO mode */
    CAN_CTL0(can_periph) &= ~(CAN_CTL0_FDEN | CAN_CTL0_DMAEN | CAN_CTL0_FS);
    CAN_CTL2(can_periph) &= ~CAN_CTL2_RFFN;
    CAN_CTL0(can_periph) |= CAN_CTL0_RFEN;

    /* clear FIFO status */
    CAN_STAT(can_periph) = (uint32_t)0xFFFFFFFFU;
    while(CAN_STAT(can_periph) & CAN_STAT_MS5_RFNE)
    {
        CAN_STAT(can_periph) = CAN_STAT_MS5_RFNE;
    }

    /* set DMA mode */
    if((uint8_t)ENABLE == can_fifo_para_init->dma_enable)
    {
        CAN_CTL0(can_periph) |= CAN_CTL0_DMAEN;
    }

    /* configure filter format */
    CAN_CTL0(can_periph) |= (can_fifo_para_init->filter_format_and_number & CAN_CTL0_FS);
    /* configure filter number */
    CAN_CTL2(can_periph) |= (can_fifo_para_init->filter_format_and_number & CAN_CTL2_RFFN);
    /* configure fifo public fiter */
    CAN_RFIFOPUBF(can_periph) = can_fifo_para_init->fifo_public_filter;
    /* configure fifo private fiter */
    if(!(CAN_CTL0(can_periph) & CAN_CTL0_RPFQEN))
    {
        for(num = 0U; num < CAN_MAX_MAILBOX_NUM; num++)
        {
            CAN_RFIFOMPF(can_periph, num) = can_fifo_para_init->fifo_public_filter;
        }
    }
}

/*!
    \brief      configure rx FIFO filter table
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  id_filter_table: id filter table struct
                  remote_frame: CAN_DATA_FRAME_ACCEPTED, CAN_REMOTE_FRAME_ACCEPTED
                  extended_frame: CAN_STANDARD_FRAME_ACCEPTED, CAN_EXTENDED_FRAME_ACCEPTED
                  id: 11 bits for standard frame, 29 bits for extended frame
    \param[out] none
    \retval     none
*/
void can_rx_fifo_filter_table_config(uint32_t can_periph, can_rx_fifo_id_filter_struct id_filter_table[])
{
    /* set rx FIFO ID filter table elements */
    uint32_t i = 0U, j = 0U, num_of_filters = 0U;
    uint32_t val = 0U;
    uint32_t id_format = 0U;
    uint32_t *filter_table = (uint32_t *)(uint32_t)(CAN_RAM(can_periph) + 0x00000060U);

    num_of_filters = (GET_CTL2_RFFN(CAN_CTL2(can_periph)) + 1U) * 8U;
    id_format = CAN_CTL0(can_periph) & CAN_CTL0_FS;

    switch(id_format)
    {
    case(CAN_FIFO_FILTER_FORMAT_A):
        /* one full id (standard and extended) per id filter table element */
        for(i = 0U; i < num_of_filters; i++)
        {
            val = 0U;

            if(CAN_REMOTE_FRAME_ACCEPTED == id_filter_table[i].remote_frame)
            {
                val |= CAN_FDESX_RTR_A;
            }
            if(CAN_EXTENDED_FRAME_ACCEPTED == id_filter_table[i].extended_frame)
            {
                val |= CAN_FDESX_IDE_A;
                val |= (uint32_t)FIFO_FILTER_ID_EXD_A(id_filter_table[i].id);
            } else {
                val |= (uint32_t)FIFO_FILTER_ID_STD_A(id_filter_table[i].id);
            }
            filter_table[i] = val;
        }
        break;
    case(CAN_FIFO_FILTER_FORMAT_B):
        /* two full standard id or two partial 14-bit (standard and extended) id */
        j = 0U;
        for(i = 0U; i < num_of_filters; i++)
        {
            val = 0U;

            if(CAN_REMOTE_FRAME_ACCEPTED == id_filter_table[j].remote_frame)
            {
                val |= CAN_FDESX_RTR_B0;
            }
            if(CAN_EXTENDED_FRAME_ACCEPTED == id_filter_table[j].extended_frame)
            {
                val |= CAN_FDESX_IDE_B0;
                val |= (uint32_t)FIFO_FILTER_ID_EXD_B0(id_filter_table[j].id);
            } else {
                val |= (uint32_t)FIFO_FILTER_ID_STD_B0(id_filter_table[j].id);
            }
            j++;

            if(CAN_REMOTE_FRAME_ACCEPTED == id_filter_table[j].remote_frame)
            {
                val |= CAN_FDESX_RTR_B1;
            }
            if(CAN_EXTENDED_FRAME_ACCEPTED == id_filter_table[j].extended_frame)
            {
                val |= CAN_FDESX_IDE_B1;
                val |= (uint32_t)FIFO_FILTER_ID_EXD_B1(id_filter_table[j].id);
            } else {
                val |= (uint32_t)FIFO_FILTER_ID_STD_B1(id_filter_table[j].id);
            }
            j++;

            filter_table[i] = val;
        }
        break;
    case(CAN_FIFO_FILTER_FORMAT_C):
        /* four partial 8-bit standard id per id filter table element */
        j = 0U;
        for(i = 0U; i < num_of_filters; i++)
        {
            val = 0U;
            if(CAN_EXTENDED_FRAME_ACCEPTED == id_filter_table[j].extended_frame)
            {
                val |= (uint32_t)FIFO_FILTER_ID_EXD_C0(id_filter_table[j].id);
            } else {
                val |= (uint32_t)FIFO_FILTER_ID_STD_C0(id_filter_table[j].id);
            }
            j++;
            if(CAN_EXTENDED_FRAME_ACCEPTED == id_filter_table[j].extended_frame)
            {
                val |= (uint32_t)FIFO_FILTER_ID_EXD_C1(id_filter_table[j].id);
            } else {
                val |= (uint32_t)FIFO_FILTER_ID_STD_C1(id_filter_table[j].id);
            }
            j++;
            if(CAN_EXTENDED_FRAME_ACCEPTED == id_filter_table[j].extended_frame)
            {
                val |= (uint32_t)FIFO_FILTER_ID_EXD_C2(id_filter_table[j].id);
            } else {
                val |= (uint32_t)FIFO_FILTER_ID_STD_C2(id_filter_table[j].id);
            }
            j++;
            if(CAN_EXTENDED_FRAME_ACCEPTED == id_filter_table[j].extended_frame)
            {
                val |= (uint32_t)FIFO_FILTER_ID_EXD_C3(id_filter_table[j].id);
            } else {
                val |= (uint32_t)FIFO_FILTER_ID_STD_C3(id_filter_table[j].id);
            }
            j++;

            filter_table[i] = val;
        }
        break;
    case(CAN_FIFO_FILTER_FORMAT_D):
        /* all frames rejected */
        break;
    default:
        /* should not get here */
        break;
    }
}

/*!
    \brief      read rx FIFO data
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] rx_fifo: rx FIFO struct
    \retval     none
*/
void can_rx_fifo_read(uint32_t can_periph, can_rx_fifo_struct *rx_fifo)
{
    uint32_t *rx_fifo_addr = (uint32_t *)rx_fifo;
    uint32_t *can_mb = (uint32_t *)CAN_RAM(can_periph);

    /* read FIFO descriptor 0 */
    rx_fifo_addr[0] = can_mb[0];
    rx_fifo_addr[1] = can_mb[1];
    rx_fifo->data[0] = can_mb[2];
    rx_fifo->data[1] = can_mb[3];

    /* clear FIFO status */
    CAN_STAT(can_periph) = CAN_STAT_MS5_RFNE;

    /* read FIFO id field */
    if(rx_fifo->ide)
    {
        rx_fifo->id = GET_FDES1_ID_EXD(rx_fifo->id);
    } else {
        rx_fifo->id = GET_FDES1_ID_STD(rx_fifo->id);
    }

    /* read FIFO data */
    can_data_to_little_endian_swap(rx_fifo->data, rx_fifo->data, rx_fifo->dlc);
}

/*!
    \brief      get rx FIFO filter matching number
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     filter number
*/
uint32_t can_rx_fifo_filter_matching_number_get(uint32_t can_periph)
{
    return GET_RFIFOIFMN_IDFMN(CAN_RFIFOIFMN(can_periph));
}

/*!
    \brief      clear rx FIFO
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_rx_fifo_clear(uint32_t can_periph)
{
    CAN_STAT(can_periph) = CAN_STAT_MS0_RFC;
}

/*!
    \brief      get mailbox RAM address
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  index: mailbox index, 0-31
    \param[out] none
    \retval     pointer to the mailbox address
*/
uint32_t *can_ram_address_get(uint32_t can_periph, uint32_t index)
{
    uint32_t payload_size;
    uint32_t *address;

    /* if CAN FD mode is enabled */
    if(CAN_CTL0(can_periph) & CAN_CTL0_FDEN)
    {
        payload_size = (uint32_t)1U << (GET_FDCTL_MDSZ(CAN_FDCTL(can_periph)) + 3U);
    } else {
        payload_size = 8U;
    }
    address = (uint32_t *)(uint32_t)(CAN_RAM(can_periph) + (payload_size + 8U) * index);

    return address;
}

/*!
    \brief      configure mailbox
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  index: mailbox index
                only one parameter can be selected which is shown as below:
      \arg        0 - 31
    \param[in]  mdpara: mailbox descriptor struct
                  rtr: 0, 1
                  ide: 0, 1
                  id: 0 - 0x1FFFFFFF
                  code: CAN_MB_RX_STATUS_INACTIVE, CAN_MB_RX_STATUS_FULL, CAN_MB_RX_STATUS_EMPTY,
                        CAN_MB_RX_STATUS_OVERRUN, CAN_MB_RX_STATUS_RANSWER, CAN_MB_RX_STATUS_BUSY,
                        CAN_MB_TX_STATUS_INACTIVE, CAN_MB_TX_STATUS_ABORT, CAN_MB_TX_STATUS_DATA
                  data_bytes: 0 - 64
                  data: point to the data
                  esi: 0, 1
                  fdf: 0, 1
                  brs: 0, 1
                  prio: 0 - 7
    \param[out] none
    \retval     none
*/
void can_mailbox_config(uint32_t can_periph, uint32_t index, can_mailbox_descriptor_struct *mdpara)
{
    uint32_t dlc;
    uint32_t mdes0 = 0U;
    uint32_t length;
    uint32_t *mdes;

    /* clear mailbox status */
    CAN_STAT(can_periph) = STAT_MS(index);

    /* get mailbox base address */
    mdes = can_ram_address_get(can_periph, index);
    mdes[0] = 0U;
    mdes[1] = 0U;
    mdes[2] = 0U;
    mdes[3] = 0U;

    /* set RTR bit */
    if(mdpara->rtr)
    {
        mdes0 |= CAN_MDES0_RTR;
    }

    /* set IDE bit and ID field */
    if(mdpara->ide)
    {
        mdes0 |= CAN_MDES0_IDE;
        mdes0 |= CAN_MDES0_SRR;
        mdes[1] |= MDES1_ID_EXD(mdpara->id);
    } else {
        mdes[1] |= MDES1_ID_STD(mdpara->id);
    }

    /* set CODE field */
    mdes0 |= MDES0_CODE(mdpara->code);

    if(mdpara->code != CAN_MB_RX_STATUS_EMPTY)
    {
        /* copy user's buffer into the mailbox data area */
        if(mdpara->data_bytes)
        {
            dlc = can_dlc_value_compute(mdpara->data_bytes);
            mdes0 |= MDES0_DLC(dlc);
            length = (uint32_t)1U << (GET_FDCTL_MDSZ(CAN_FDCTL(can_periph)) + 3U);
            if(mdpara->data_bytes < length)
            {
                length = mdpara->data_bytes;
            }
            can_data_to_big_endian_swap(&mdes[2], mdpara->data, length);
        }

        /* prepare mailbox for transmission */
        if(CAN_MB_TX_STATUS_DATA == mdpara->code)
        {
            /* set ESI bit */
            if(mdpara->esi)
            {
                mdes0 |= CAN_MDES0_ESI;
            }
            /* set FDF and BRS bit */
            if(mdpara->fdf)
            {
                mdes0 |= CAN_MDES0_FDF;
                if(mdpara->brs)
                {
                    mdes0 |= CAN_MDES0_BRS;
                }
                mdes0 &= ~CAN_MDES0_RTR;
            }
        }

        /* set PRIO field */
        mdes[1] |= MDES1_PRIO(mdpara->prio);
    }

    /* set mailbox descriptor 0 */
    mdes[0] = mdes0;
}

/*!
    \brief      abort mailbox transmit
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  index: mailbox index
                only one parameter can be selected which is shown as below:
      \arg        0 - 31
    \param[out] none
    \retval     none
*/
void can_mailbox_transmit_abort(uint32_t can_periph, uint32_t index)
{
    uint32_t mdes0;
    uint32_t *mdes;

    /* abort transmit mailbox */
    mdes = can_ram_address_get(can_periph, index);
    mdes0 = mdes[0];
    mdes0 &= ~CAN_MDES0_CODE;
    mdes0 |= MDES0_CODE(CAN_MB_TX_STATUS_ABORT);
    mdes[0] = mdes0;
}

/*!
    \brief      inactive transmit mailbox
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  index: mailbox index
                only one parameter can be selected which is shown as below:
      \arg        0 - 31
    \param[out] none
    \retval     none
*/
void can_mailbox_transmit_inactive(uint32_t can_periph, uint32_t index)
{
    uint32_t mdes0;
    uint32_t *mdes;

    /* inactive transmit mailbox */
    mdes = can_ram_address_get(can_periph, index);
    mdes0 = mdes[0];
    mdes0 &= ~CAN_MDES0_CODE;
    mdes0 |= MDES0_CODE(CAN_MB_TX_STATUS_INACTIVE);
    mdes[0] = mdes0;
}

/*!
    \brief      read receive mailbox data
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  index: mailbox index
                only one parameter can be selected which is shown as below:
      \arg        0 - 31
    \param[out] mdpara: mailbox descriptor struct
    \retval     ERROR or SUCCESS
*/
ErrStatus can_mailbox_receive_data_read(uint32_t can_periph, uint32_t index, can_mailbox_descriptor_struct *mdpara)
{
    uint32_t i;
    uint32_t cnt;
    uint32_t timeout;
    uint32_t *mdes = can_ram_address_get(can_periph, index);
    uint32_t *mdaddr = (uint32_t *)mdpara;

    /* wait mailbox data ready */
    timeout = CAN_DELAY;
    while((mdes[0] & MDES0_CODE(CAN_MB_RX_STATUS_BUSY)) && (timeout))
    {
        timeout--;
    }
    if(mdes[0] & MDES0_CODE(CAN_MB_RX_STATUS_BUSY))
    {
        return ERROR;
    }

    /* get mailbox descriptor 0 */
    mdaddr[0] = mdes[0];
    mdaddr[1] = mdes[1];
    mdpara->data_bytes = can_payload_size_compute(mdaddr[0]);
    cnt = (mdpara->data_bytes + 3U) / 4U;
    mdaddr = mdpara->data;
    mdes += 2U;
    for(i = 0U; i < cnt; i++)
    {
        mdaddr[i] = mdes[i];
    }

    /* clear mailbox status */
    CAN_STAT(can_periph) = STAT_MS(index);
    /* unlock mailbox */
    CAN_TIMER(can_periph);

    /* get mailbox ID */
    if(mdpara->ide)
    {
        mdpara->id = GET_MDES1_ID_EXD(mdpara->id);
    } else {
        mdpara->id = GET_MDES1_ID_STD(mdpara->id);
    }

    /* get mailbox data */
    if(mdpara->data_bytes)
    {
        can_data_to_little_endian_swap(mdpara->data, mdpara->data, mdpara->data_bytes);
    }

    return SUCCESS;
}

/*!
    \brief      lock the receive mailbox
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  index: mailbox index
                only one parameter can be selected which is shown as below:
      \arg        0 - 31
    \param[out] none
    \retval     none
*/
void can_mailbox_receive_lock(uint32_t can_periph, uint32_t index)
{
    uint32_t *mdes;

    mdes = can_ram_address_get(can_periph, index);
    REG32((uint32_t)mdes);
}

/*!
    \brief      unlock the receive mailbox
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_mailbox_receive_unlock(uint32_t can_periph)
{
    CAN_TIMER(can_periph);
}

/*!
    \brief      inactive the receive mailbox
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  index: mailbox index
                only one parameter can be selected which is shown as below:
      \arg        0 - 31
    \param[out] none
    \retval     none
*/
void can_mailbox_receive_inactive(uint32_t can_periph, uint32_t index)
{
    uint32_t mdes0;
    uint32_t *mdes;

    /* inactive receive mailbox */
    mdes = can_ram_address_get(can_periph, index);
    mdes0 = mdes[0];
    mdes0 &= ~CAN_MDES0_CODE;
    mdes0 |= MDES0_CODE(CAN_MB_RX_STATUS_INACTIVE);
    mdes[0] = mdes0;
}

/*!
    \brief      get mailbox code value
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  index: mailbox index(0~31)
                only one parameter can be selected which is shown as below:
      \arg        0 - 31
    \param[out] none
    \retval     mailbox code
*/
uint32_t can_mailbox_code_get(uint32_t can_periph, uint32_t index)
{
    uint32_t code;
    uint32_t *mdes;

    mdes = can_ram_address_get(can_periph, index);
    code = GET_MDES0_CODE(mdes[0]);

    return code;
}

/*!
    \brief      configure error counter
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  errcnt_struct
                  fd_data_phase_rx_errcnt: 0-255
                  fd_data_phase_tx_errcnt: 0-255
                  rx_errcnt: 0-255
                  tx_errcnt: 0-255
    \retval     none
*/
void can_error_counter_config(uint32_t can_periph, can_error_counter_struct *errcnt_struct)
{
    CAN_ERR0(can_periph) = ERR0_REFCNT(errcnt_struct->fd_data_phase_rx_errcnt) | ERR0_TEFCNT(errcnt_struct->fd_data_phase_tx_errcnt) | \
                           ERR0_RECNT(errcnt_struct->rx_errcnt) | ERR0_TECNT(errcnt_struct->tx_errcnt);
}

/*!
    \brief      get error counter
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] errcnt_struct
                  fd_data_phase_rx_errcnt: 0-255
                  fd_data_phase_tx_errcnt: 0-255
                  rx_errcnt: 0-255
                  tx_errcnt: 0-255
    \retval     none
*/
void can_error_counter_get(uint32_t can_periph, can_error_counter_struct *errcnt_struct)
{
    uint32_t reg = 0U;

    reg = CAN_ERR0(can_periph);
    errcnt_struct->fd_data_phase_rx_errcnt = (uint8_t)GET_ERR0_REFCNT(reg);
    errcnt_struct->fd_data_phase_tx_errcnt = (uint8_t)GET_ERR0_TEFCNT(reg);
    errcnt_struct->rx_errcnt = (uint8_t)GET_ERR0_RECNT(reg);
    errcnt_struct->tx_errcnt = (uint8_t)GET_ERR0_TECNT(reg);
}

/*!
    \brief      get error state indicator
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     CAN_ERROR_STATE_ACTIVE, CAN_ERROR_STATE_PASSIVE or CAN_ERROR_STATE_BUS_OFF
*/
can_error_state_enum can_error_state_get(uint32_t can_periph)
{
    uint32_t reg;

    reg = GET_ERR1_ERRSI(CAN_ERR1(can_periph));
    if(reg >= (uint32_t)CAN_ERROR_STATE_BUS_OFF)
    {
        reg = (uint32_t)CAN_ERROR_STATE_BUS_OFF;
    }

    return (can_error_state_enum)reg;
}

/*!
    \brief      get mailbox CRC value
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] crc_struct:
                  classical_frm_mb_number: 0 - 0x1F
                  classical_frm_transmitted_crc: 0 - 0x7FFF
                  classical_fd_frm_mb_number: 0 - 0x1F
                  classical_fd_frm_transmitted_crc: 0 - 0x1FFFFF
    \retval     none
*/
void can_crc_get(uint32_t can_periph, can_crc_struct *crc_struct)
{
    uint32_t reg1 = 0U, reg2 = 0U;

    reg1 = CAN_CRCC(can_periph);
    reg2 = CAN_CRCCFD(can_periph);
    crc_struct->classical_frm_mb_number = GET_CRCC_ANTM(reg1);
    crc_struct->classical_frm_transmitted_crc = GET_CRCC_CRCTC(reg1);
    crc_struct->classical_fd_frm_mb_number = GET_CRCCFD_ANTM(reg2);
    crc_struct->classical_fd_frm_transmitted_crc = GET_CRCCFD_CRCTCI(reg2);
}

/*!
    \brief      configure Pretended Networking mode parameter
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  pnmod_config: Pretended Networking mode config struct
                  timeout_int: ENABLE, DISABLE
                  match_int: ENABLE, DISABLE
                  num_matches: 1 ~ 255
                  match_timeout: 0 ~ 0xFFFF
                  frame_filter: CAN_PN_FRAME_FILTERING_ID, CAN_PN_FRAME_FILTERING_ID_DATA
                                CAN_PN_FRAME_FILTERING_ID_NMM, CAN_PN_FRAME_FILTERING_ID_DATA_NMM
                  id_filter: CAN_PN_ID_FILTERING_EXACT, CAN_PN_ID_FILTERING_GREATER
                             CAN_PN_ID_FILTERING_SMALLER, CAN_PN_ID_FILTERING_RANGE
                  data_filter: CAN_PN_DATA_FILTERING_EXACT, CAN_PN_DATA_FILTERING_GREATER
                               CAN_PN_DATA_FILTERING_SMALLER, CAN_PN_DATA_FILTERING_RANGE
    \param[out] none
    \retval     none
*/
void can_pn_mode_config(uint32_t can_periph, can_pn_mode_config_struct *pnmod_config)
{
    uint32_t tmp;

    /* configure specific Pretended Networking mode settings */
    tmp = CAN_PN_CTL0(can_periph);
    tmp &= ~(CAN_PN_CTL0_FFT | CAN_PN_CTL0_IDFT | CAN_PN_CTL0_DATAFT |
             CAN_PN_CTL0_NMM | CAN_PN_CTL0_WMIE | CAN_PN_CTL0_WTOIE);
    tmp |= (uint32_t)PN_CTL0_WTOIE(pnmod_config->timeout_int) | PN_CTL0_WMIE(pnmod_config->match_int) | \
           PN_CTL0_NMM(pnmod_config->num_matches) | pnmod_config->data_filter | \
           pnmod_config->id_filter | pnmod_config->frame_filter;

    CAN_PN_CTL0(can_periph) = tmp;

    /* set timeout value */
    CAN_PN_TO(can_periph) &= ~CAN_PN_TO_WTO;
    CAN_PN_TO(can_periph) |= (uint32_t)PN_TO_WTO(pnmod_config->match_timeout);

    /* enable Pretended Networking mode */
    CAN_CTL0(can_periph) |= CAN_CTL0_PNMOD;
}

/*!
    \brief      configure Pretended Networking mode filter
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  expect: Pretended Networking mode struct of expected wakeup frame
                  rtr: SET, RESET
                  ide: SET, RESET
                  id: 0~0x7FF | CAN_STANDARD, or 0~0x1FFFFFFF | CAN_EXTENDED
                  dlc_high_threshold: 0~8
                  dlc_low_threshold: 0~8
                  payload[0]: 0x00000000~0xFFFFFFFF
                  payload[1]: 0x00000000~0xFFFFFFFF
    \param[in]  filter: Pretended Networking mode struct of filter data
                  remote_frame: SET, RESET
                  extended_frame: SET, RESET
                  id: 0~0x7FF | CAN_STANDARD, or 0~0x1FFFFFFF | CAN_EXTENDED. Used as id filter data, or id expected high threshold.
                  payload[0]: 0x00000000~0xFFFFFFFF. Used as payload filter data, or payload expected high threshold.
                  payload[1]: 0x00000000~0xFFFFFFFF. Used as payload filter data, or payload expected high threshold.
    \param[out] none
    \retval     none
*/
void can_pn_mode_filter_config(uint32_t can_periph, can_pn_mode_filter_struct *expect, can_pn_mode_filter_struct *filter)
{
    uint32_t reg, temp;

    /* set filter identifier 0 */
    reg = 0U;
    if((uint32_t)SET == expect->ide)
    {
        reg |= CAN_PN_EID0_EIDE;
    }
    if((uint32_t)SET == expect->rtr)
    {
        reg |= CAN_PN_EID0_ERTR;
    }
    if(CAN_STANDARD == (expect->id & BIT(31)))
    {
        reg |= (uint32_t)PN_EID0_EIDF_ELT_STD(expect->id);
    }else{
        reg |= (uint32_t)PN_EID0_EIDF_ELT_EXD(expect->id);
    }

    CAN_PN_EID0(can_periph) = reg;

    temp = CAN_PN_CTL0(can_periph);
    reg = 0U;
    /* ID field 1 is used when ID filtering type is EXACT or RANGE */
    if(((temp & CAN_PN_CTL0_IDFT) == CAN_PN_ID_FILTERING_EXACT) || ((temp & CAN_PN_CTL0_IDFT) == CAN_PN_ID_FILTERING_RANGE))
    {
        if(CAN_STANDARD == (filter->id & BIT(31)))
        {
            reg |= (uint32_t)PN_IFEID1_IDEFD_STD(filter->id);
        }else{
            reg |= (uint32_t)PN_IFEID1_IDEFD_EXD(filter->id);
        }
    }
    if((uint32_t)SET == filter->ide)
    {
        reg |= CAN_PN_IFEID1_IDEFD;
    }
    if((uint32_t)SET == filter->rtr)
    {
        reg |= CAN_PN_IFEID1_RTRFD;
    }
    /* set filter identifier 1 */
    CAN_PN_IFEID1(can_periph) = reg;

    /* data field is used when frame filtering type is not MATCH or MATCH NMM */
    if(((temp & CAN_PN_CTL0_FFT) == CAN_PN_FRAME_FILTERING_ID_DATA) ||
            ((temp & CAN_PN_CTL0_FFT) == CAN_PN_FRAME_FILTERING_ID_DATA_NMM))
            {
        /* set filter data payload 0 */
        CAN_PN_EDLC(can_periph) = PN_EDLC_DLCEHT(expect->dlc_high_threshold) | PN_EDLC_DLCELT(expect->dlc_low_threshold);
        CAN_PN_EDL0(can_periph) = ((expect->payload[0] << 24U) & CAN_PN_EDL0_DB0ELT) |
                                  ((expect->payload[0] << 8U) & CAN_PN_EDL0_DB1ELT) |
                                  ((expect->payload[0] >> 8U) & CAN_PN_EDL0_DB2ELT) |
                                  ((expect->payload[0] >> 24U) & CAN_PN_EDL0_DB3ELT);
        CAN_PN_EDL1(can_periph) = ((expect->payload[1] << 24U) & CAN_PN_EDL1_DB4ELT) |
                                  ((expect->payload[1] << 8U) & CAN_PN_EDL1_DB5ELT) |
                                  ((expect->payload[1] >> 8U) & CAN_PN_EDL1_DB6ELT) |
                                  ((expect->payload[1] >> 24U) & CAN_PN_EDL1_DB7ELT);

        /* data field 1 is used when data filtering type is EXACT or RANGE */
        if(((temp & CAN_PN_CTL0_DATAFT) == CAN_PN_DATA_FILTERING_EXACT)
                || ((temp & CAN_PN_CTL0_DATAFT) == CAN_PN_DATA_FILTERING_RANGE))
                {
            /* set filter data payload 1 */
            CAN_PN_DF0EDH0(can_periph) = ((filter->payload[0] << 24U) & CAN_PN_DF0EDH0_DB0FD_EHT) |
                                         ((filter->payload[0] << 8U) & CAN_PN_DF0EDH0_DB1FD_EHT) |
                                         ((filter->payload[0] >> 8U) & CAN_PN_DF0EDH0_DB2FD_EHT) |
                                         ((filter->payload[0] >> 24U) & CAN_PN_DF0EDH0_DB3FD_EHT);
            CAN_PN_DF1EDH1(can_periph) = ((filter->payload[1] << 24U) & CAN_PN_DF1EDH1_DB4FD_EHT) |
                                         ((filter->payload[1] << 8U) & CAN_PN_DF1EDH1_DB5FD_EHT) |
                                         ((filter->payload[1] >> 8U) & CAN_PN_DF1EDH1_DB6FD_EHT) |
                                         ((filter->payload[1] >> 24U) & CAN_PN_DF1EDH1_DB7FD_EHT);
        }
    }
}


/*!
    \brief      get matching message counter of Pretended Networking mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     0~255 or -1
*/
int32_t can_pn_mode_num_of_match_get(uint32_t can_periph)
{
    int32_t ret = 0;
    uint32_t reg = 0U;

    reg = CAN_PN_STAT(can_periph);
    if(0U != (reg & CAN_PN_STAT_MMCNTS))
    {
        ret = (int32_t)(uint32_t)GET_PN_STAT_MMCNT(reg);
    } else {
        ret = -1;
    }
    return ret;
}

/*!
    \brief      get matching message
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  index: Pretended Networking mailbox index
                only one parameter can be selected which is shown as below:
      \arg        0 - 31
    \param[out] mdpara: wakeup message information
    \retval     none
*/
void can_pn_mode_data_read(uint32_t can_periph, uint32_t index, can_mailbox_descriptor_struct *mdpara)
{
    uint32_t *mdaddr = (uint32_t *)mdpara;
    uint32_t *pnram = (uint32_t *)(uint32_t)(CAN_PN_RAM(can_periph) + index * 16U);

    mdaddr[0] = pnram[0];
    mdaddr[1] = pnram[1];
    /* get mailbox ID */
    if(0U != mdpara->ide)
    {
        mdpara->id = GET_MDES1_ID_EXD(mdpara->id);
    } else {
        mdpara->id = GET_MDES1_ID_STD(mdpara->id);
    }
    mdpara->data_bytes = mdpara->dlc;
    /* remote frame */
    if(0U != (mdaddr[0] & CAN_PN_RWMXCS_RRTR))
    {
        mdpara->data_bytes = 0U;
    }else{
        /* classical frame */
        if(mdpara->dlc <= 8U)
        {
            mdpara->data_bytes = mdpara->dlc;
        }else{
            mdpara->data_bytes = 8U;
        }
    }
    if(mdpara->data_bytes)
    {
        can_data_to_little_endian_swap(mdpara->data, &pnram[2], mdpara->data_bytes);
    }
}

/*!
    \brief      enable self reception
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_self_reception_enable(uint32_t can_periph)
{
    CAN_CTL0(can_periph) &= ~CAN_CTL0_SRDIS;
}

/*!
    \brief      disable self reception
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_self_reception_disable(uint32_t can_periph)
{
    CAN_CTL0(can_periph) |= CAN_CTL0_SRDIS;
}

/*!
    \brief      enable transmit abort
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_transmit_abort_enable(uint32_t can_periph)
{
    CAN_CTL0(can_periph) |= CAN_CTL0_MST;
}

/*!
    \brief      disable transmit abort
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_transmit_abort_disable(uint32_t can_periph)
{
    CAN_CTL0(can_periph) &= ~CAN_CTL0_MST;
}

/*!
    \brief      enable auto bus off recovery mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_auto_busoff_recovery_enable(uint32_t can_periph)
{
    CAN_CTL1(can_periph) &= ~CAN_CTL1_ABORDIS;
}

/*!
    \brief      disable auto bus off recovery mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_auto_busoff_recovery_disable(uint32_t can_periph)
{
    CAN_CTL1(can_periph) |= CAN_CTL1_ABORDIS;
}

/*!
    \brief      enable time sync mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_time_sync_enable(uint32_t can_periph)
{
    CAN_CTL1(can_periph) |= CAN_CTL1_TSYNC;
}

/*!
    \brief      disable time sync mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_time_sync_disable(uint32_t can_periph)
{
    CAN_CTL1(can_periph) &= ~CAN_CTL1_TSYNC;
}

/*!
    \brief      enable edge filter mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_edge_filter_mode_enable(uint32_t can_periph)
{
    CAN_CTL2(can_periph) &= ~CAN_CTL2_EFDIS;
}

/*!
    \brief      disable edge filter mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_edge_filter_mode_disable(uint32_t can_periph)
{
    CAN_CTL2(can_periph) |= CAN_CTL2_EFDIS;
}

/*!
    \brief      enable protocol exception detection mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_ped_mode_enable(uint32_t can_periph)
{
    CAN_CTL2(can_periph) |= CAN_CTL2_PREEN;
}

/*!
    \brief      disable protocol exception detection mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void can_ped_mode_disable(uint32_t can_periph)
{
    CAN_CTL2(can_periph) &= ~CAN_CTL2_PREEN;
}

/*!
    \brief      configure arbitration delay bits
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  delay_bits: delay bits
                only one parameter can be selected which is shown as below:
      \arg        0 - 31
    \param[out] none
    \retval     none
*/
void can_arbitration_delay_bits_config(uint32_t can_periph, uint32_t delay_bits)
{
    CAN_CTL2(can_periph) &= ~CAN_CTL2_ASD;
    CAN_CTL2(can_periph) |= (uint32_t)CTL2_ASD(delay_bits);
}

/*!
    \brief      configure bit sampling mode
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  sampling_mode: bit sampling mode
                only one parameter can be selected which is shown as below:
      \arg        CAN_BSP_MODE_ONE_SAMPLE: one sample for received bit
      \arg        CAN_BSP_MODE_THREE_SAMPLES: three samples for received bit
    \param[out] none
    \retval     none
*/
void can_bsp_mode_config(uint32_t can_periph, uint32_t sampling_mode)
{
    if(CAN_BSP_MODE_ONE_SAMPLE == sampling_mode)
    {
        CAN_CTL1(can_periph) &= ~CAN_CTL1_BSPMOD;
    } else {
        CAN_CTL1(can_periph) |= CAN_CTL1_BSPMOD;
    }
}

/*!
    \brief      get CAN flag
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  flag: CAN flags, refer to can_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_FLAG_CAN_PN: Pretended Networking state flag
      \arg        CAN_FLAG_SOFT_RST: software reset flag
      \arg        CAN_FLAG_ERR_SUMMARY: error summary flag
      \arg        CAN_FLAG_BUSOFF: bus off flag
      \arg        CAN_FLAG_RECEIVING: receiving state flag
      \arg        CAN_FLAG_TRANSMITTING: transmitting state flag
      \arg        CAN_FLAG_IDLE: IDLE state flag
      \arg        CAN_FLAG_RX_WARNING: receive warning flag
      \arg        CAN_FLAG_TX_WARNING: transmit warning flag
      \arg        CAN_FLAG_STUFF_ERR: stuff error flag
      \arg        CAN_FLAG_FORM_ERR: form error flag
      \arg        CAN_FLAG_CRC_ERR: CRC error flag
      \arg        CAN_FLAG_ACK_ERR: ACK error flag
      \arg        CAN_FLAG_BIT_DOMINANT_ERR: bit dominant error flag
      \arg        CAN_FLAG_BIT_RECESSIVE_ERR: bit recessive error flag
      \arg        CAN_FLAG_SYNC_ERR: synchronization flag
      \arg        CAN_FLAG_BUSOFF_RECOVERY: bus off recovery flag
      \arg        CAN_FLAG_ERR_SUMMARY_FD: fd error summary flag
      \arg        CAN_FLAG_ERR_OVERRUN: error overrun flag
      \arg        CAN_FLAG_STUFF_ERR_FD: stuff error in FD data phase flag
      \arg        CAN_FLAG_FORM_ERR_FD: form error in FD data phase flag
      \arg        CAN_FLAG_CRC_ERR_FD: CRC error in FD data phase flag
      \arg        CAN_FLAG_BIT_DOMINANT_ERR_FD: bit dominant error in FD data phase flag
      \arg        CAN_FLAG_BIT_RECESSIVE_ERR_FD: bit recessive error in FD data phase flag
      \arg        CAN_FLAG_MBx(x=0~31): mailbox x flag
      \arg        CAN_FLAG_FIFO_AVAILABLE: fifo available flag
      \arg        CAN_FLAG_FIFO_WARNING: fifo warning flag
      \arg        CAN_FLAG_FIFO_OVERFLOW: fifo overflow flag
      \arg        CAN_FLAG_WAKEUP_MATCH: Pretended Networking match flag
      \arg        CAN_FLAG_WAKEUP_TIMEOUT: Pretended Networking timeout wakeup flag
      \arg        CAN_FLAG_TDC_OUT_OF_RANGE: transmitter delay is out of compensation range flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_flag_get(uint32_t can_periph, can_flag_enum flag)
{
    if(CAN_REG_VAL(can_periph, flag) & BIT(CAN_BIT_POS(flag)))
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear CAN flag
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  flag: CAN flags, refer to can_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_FLAG_ERR_SUMMARY: error summary flag
      \arg        CAN_FLAG_BUSOFF: bus off flag
      \arg        CAN_FLAG_BUSOFF_RECOVERY: bus off recovery flag
      \arg        CAN_FLAG_ERR_SUMMARY_FD: fd error summary flag
      \arg        CAN_FLAG_ERR_OVERRUN: error overrun flag
      \arg        CAN_FLAG_MBx(x=0~31): mailbox x flag
      \arg        CAN_FLAG_FIFO_AVAILABLE: fifo available flag
      \arg        CAN_FLAG_FIFO_WARNING: fifo warning flag
      \arg        CAN_FLAG_FIFO_OVERFLOW: fifo overflow flag
      \arg        CAN_FLAG_WAKEUP_MATCH: Pretended Networking match flag
      \arg        CAN_FLAG_WAKEUP_TIMEOUT: Pretended Networking timeout wakeup flag
      \arg        CAN_FLAG_TDC_OUT_OF_RANGE: transmitter delay is out of compensation range flag
    \param[out] none
    \retval     none
*/
void can_flag_clear(uint32_t can_periph, can_flag_enum flag)
{
    if(CAN_FLAG_TDC_OUT_OF_RANGE == flag)
    {
        CAN_FDCTL(can_periph) |= CAN_FDCTL_TDCS;
    } else {
        CAN_REG_VAL(can_periph, flag) = BIT(CAN_BIT_POS(flag));
    }
}

/*!
    \brief      enable CAN interrupt
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  interrupt: CAN interrupt, refer to can_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_ERR_SUMMARY: error interrupt
      \arg        CAN_INT_RX_WARNING: receive warning interrupt
      \arg        CAN_INT_TX_WARNING: transmit warning interrupt
      \arg        CAN_INT_BUSOFF: bus off interrupt
      \arg        CAN_INT_BUSOFF_RECOVERY: bus off recovery interrupt
      \arg        CAN_INT_ERR_SUMMARY_FD: fd error interrupt
      \arg        CAN_INT_MBx(x=0~31): mailbox x interrupt
      \arg        CAN_INT_FIFO_AVAILABLE: fifo available interrupt
      \arg        CAN_INT_FIFO_WARNING: fifo warning interrupt
      \arg        CAN_INT_FIFO_OVERFLOW: fifo overflow interrupt
      \arg        CAN_INT_WAKEUP_MATCH: Pretended Networking match interrupt
      \arg        CAN_INT_WAKEUP_TIMEOUT: Pretended Networking timeout wakeup interrupt
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus can_interrupt_enable(uint32_t can_periph, can_interrupt_enum interrupt)
{
    can_operation_modes_enum mode = CAN_NORMAL_MODE;
    ErrStatus ret = SUCCESS;

    /* enable receive or transmit warning error interrupt should enable error warning in CTL0 register  */
    if((CAN_INT_RX_WARNING == interrupt) || (CAN_INT_TX_WARNING == interrupt))
    {
        mode = can_operation_mode_get(can_periph);
        /* in INACTIVE mode */
        if(CAN_INACTIVE_MODE == mode)
        {
            CAN_CTL0(can_periph) |= CAN_CTL0_WERREN;
        }else{
            ret = can_operation_mode_enter(can_periph, CAN_INACTIVE_MODE);
            if(SUCCESS == ret)
            {
                CAN_CTL0(can_periph) |= CAN_CTL0_WERREN;
                ret = can_operation_mode_enter(can_periph, mode);
            }
        }
    }

    CAN_REG_VAL(can_periph, interrupt) |= BIT(CAN_BIT_POS(interrupt));
    return ret;
}

/*!
    \brief      disable CAN interrupt
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  interrupt: CAN interrupt, refer to can_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_ERR_SUMMARY: error interrupt
      \arg        CAN_INT_RX_WARNING: receive warning interrupt
      \arg        CAN_INT_TX_WARNING: transmit warning interrupt
      \arg        CAN_INT_BUSOFF: bus off interrupt
      \arg        CAN_INT_BUSOFF_RECOVERY: bus off recovery interrupt
      \arg        CAN_INT_ERR_SUMMARY_FD: fd error interrupt
      \arg        CAN_INT_MBx(x=0~31): mailbox x interrupt
      \arg        CAN_INT_FIFO_AVAILABLE: fifo available interrupt
      \arg        CAN_INT_FIFO_WARNING: fifo warning interrupt
      \arg        CAN_INT_FIFO_OVERFLOW: fifo overflow interrupt
      \arg        CAN_INT_WAKEUP_MATCH: Pretended Networking match interrupt
      \arg        CAN_INT_WAKEUP_TIMEOUT: Pretended Networking timeout wakeup interrupt
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus can_interrupt_disable(uint32_t can_periph, can_interrupt_enum interrupt)
{
    can_operation_modes_enum mode = CAN_NORMAL_MODE;
    ErrStatus ret = SUCCESS;

    /* disable receive or transmit warning error interrupt should enable error warning in CTL0 register  */
    if((0U == (CAN_CTL0(can_periph) & CAN_CTL0_WERREN)) && ((CAN_INT_RX_WARNING == interrupt) || (CAN_INT_TX_WARNING == interrupt)))
    {
        mode = can_operation_mode_get(can_periph);
        /* in INACTIVE mode */
        if(CAN_INACTIVE_MODE == mode)
        {
            CAN_CTL0(can_periph) |= CAN_CTL0_WERREN;
        }else{
            ret = can_operation_mode_enter(can_periph, CAN_INACTIVE_MODE);
            if(SUCCESS == ret)
            {
                CAN_CTL0(can_periph) |= CAN_CTL0_WERREN;
                ret = can_operation_mode_enter(can_periph, mode);
            }
        }
    }

    CAN_REG_VAL(can_periph, interrupt) &= ~BIT(CAN_BIT_POS(interrupt));
    return ret;
}

/*!
    \brief      get CAN interrupt flag
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  int_flag: CAN interrupt flags, refer to can_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_FLAG_ERR_SUMMARY: error summary interrupt flag
      \arg        CAN_INT_FLAG_BUSOFF: bus off interrupt flag
      \arg        CAN_INT_FLAG_RX_WARNING: receive warning interrupt flag
      \arg        CAN_INT_FLAG_TX_WARNING: transmit warning interrupt flag
      \arg        CAN_INT_FLAG_BUSOFF_RECOVERY: bus off recovery interrupt flag
      \arg        CAN_INT_FLAG_ERR_SUMMARY_FD: fd error summary interrupt flag
      \arg        CAN_INT_FLAG_MBx(x=0~31): mailbox x interrupt flag
      \arg        CAN_INT_FLAG_FIFO_AVAILABLE: fifo available interrupt flag
      \arg        CAN_INT_FLAG_FIFO_WARNING: fifo warning interrupt flag
      \arg        CAN_INT_FLAG_FIFO_OVERFLOW: fifo overflow interrupt flag
      \arg        CAN_INT_FLAG_WAKEUP_MATCH: Pretended Networking match interrupt flag
      \arg        CAN_INT_FLAG_WAKEUP_TIMEOUT: Pretended Networking timeout wakeup interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_interrupt_flag_get(uint32_t can_periph, can_interrupt_flag_enum int_flag)
{
    if(CAN_REG_VAL(can_periph, int_flag) & BIT(CAN_BIT_POS(int_flag)))
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear CAN interrupt flag
    \param[in]  can_periph: CANx(x=0,1,2)
    \param[in]  int_flag: CAN interrupt flags, refer to can_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_FLAG_ERR_SUMMARY: error summary interrupt flag
      \arg        CAN_INT_FLAG_BUSOFF: bus off interrupt flag
      \arg        CAN_INT_FLAG_RX_WARNING: receive warning interrupt flag
      \arg        CAN_INT_FLAG_TX_WARNING: transmit warning interrupt flag
      \arg        CAN_INT_FLAG_BUSOFF_RECOVERY: bus off recovery interrupt flag
      \arg        CAN_INT_FLAG_ERR_SUMMARY_FD: fd error summary interrupt flag
      \arg        CAN_INT_FLAG_MBx(x=0~31): mailbox x interrupt flag
      \arg        CAN_INT_FLAG_FIFO_AVAILABLE: fifo available interrupt flag
      \arg        CAN_INT_FLAG_FIFO_WARNING: fifo warning interrupt flag
      \arg        CAN_INT_FLAG_FIFO_OVERFLOW: fifo overflow interrupt flag
      \arg        CAN_INT_FLAG_WAKEUP_MATCH: Pretended Networking match interrupt flag
      \arg        CAN_INT_FLAG_WAKEUP_TIMEOUT: Pretended Networking timeout wakeup interrupt flag
    \param[out] none
    \retval     none
*/
void can_interrupt_flag_clear(uint32_t can_periph, can_interrupt_flag_enum int_flag)
{
    CAN_REG_VAL(can_periph, int_flag) = BIT(CAN_BIT_POS(int_flag));
}

/*!
    \brief      computes the maximum payload size (in bytes), given a dlc
    \param[in]  mdes0: mailbox descriptor 0 data
    \param[out] none
    \retval     payload_size
*/
static uint32_t can_payload_size_compute(uint32_t mdes0)
{
    uint8_t ret = 0U;
    uint32_t dlc_value = GET_MDES0_DLC(mdes0);

    /* remote frame */
    if(0U != (mdes0 & CAN_MDES0_RTR))
    {
        ret = 0U;
    }else{
        /* FD frame */
        if(0U != (mdes0 & CAN_MDES0_FDF))
        {
            if(dlc_value <= 15U)
            {
                ret = dlc_to_databytes[dlc_value];
            }
        /* classical frame */
        }else{
            if(dlc_value <= 8U)
            {
                ret = (uint8_t)dlc_value;
            }else{
                ret = 8U;
            }
        }
    }

    return (uint32_t)ret;
}

/*!
    \brief      swap data to little endian
    \param[in]  src: data source address
    \param[in]  len: data length be byte
    \param[out] dest: data destination address
    \retval     none
*/
static void can_data_to_little_endian_swap(uint32_t dest[], uint32_t src[], uint32_t len)
{
    volatile uint32_t i = 0U;
    uint32_t cnt;
    uint32_t temp_src = 0U;

    /* get the word length of the data */
    cnt = (len + 3U) / 4U;
    /* change each word from big endian to little endian */
    for(i = 0U; i < cnt; i++)
    {
        temp_src = src[i];
        dest[i] = ((uint32_t)(temp_src >> 24U) & 0x000000FFU) |
                  ((uint32_t)(temp_src >> 8U) & 0x0000FF00U) |
                  ((uint32_t)(temp_src << 8U) & 0x00FF0000U) |
                  ((uint32_t)(temp_src << 24U) & 0xFF000000U);
    }

    cnt = len % 4U;
    if(cnt)
    {
        dest[i - 1U] &= ((uint32_t)1U << (cnt * 8U)) - 1U;
    }
}

/*!
    \brief      swap data to big endian
    \param[in]  src: data source address
    \param[in]  len: data length be byte
    \param[out] dest: data destination address
    \retval     none
*/
static void can_data_to_big_endian_swap(uint32_t dest[], uint32_t src[], uint32_t len)
{
    volatile uint32_t i = 0U;
    uint32_t cnt;
    uint32_t temp_src = 0U;

    /* get the word length of the data */
    cnt = (len + 3U) / 4U;
    for(i = 0U; i < cnt; i++)
    {
        /* change each word from little endian to big endian */
        temp_src = src[i];
        dest[i] = ((uint32_t)(temp_src >> 24U) & 0x000000FFU) |
                  ((uint32_t)(temp_src >> 8U) & 0x0000FF00U) |
                  ((uint32_t)(temp_src << 8U) & 0x00FF0000U) |
                  ((uint32_t)(temp_src << 24U) & 0xFF000000U);
    }

    cnt = len % 4U;
    if(cnt)
    {
        dest[i - 1U] &= ~(((uint32_t)1U << ((4U - cnt) * 8U)) - 1U);
    }
}

/*!
    \brief      computes the DLC field value, given a payload size (in bytes)
    \param[in]  payload_size: payload size
    \param[out] none
    \retval     DLC value
*/
static uint32_t can_dlc_value_compute(uint32_t payload_size)
{
    uint32_t ret = 8U;

    if(payload_size <= 8U)
    {
        ret = payload_size;
    } else if(payload_size <= 24U)
    {
        ret = (payload_size - 9U) / 4U + 9U;
    } else if(payload_size <= 64U)
    {
        ret = (payload_size - 17U) / 16U + 13U;
    } else {
        ret = 8U;
    }

    return ret;
}
