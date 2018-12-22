/**
 * \file
 *
 * \brief SAM Control Area Network Driver Configuration Header
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef CONF_CAN_H_INCLUDED
#define CONF_CAN_H_INCLUDED

/*
 * Below is the message RAM setting, it will be stored in the system RAM.
 * Please adjust the message size according to your application.
 */
#define CONF_CAN0_RX_FIFO_0_NUM         16            /* Range: 1..64 */ 
#define CONF_CAN0_RX_FIFO_1_NUM         16            /* Range: 1..64 */ 
#define CONF_CAN0_RX_BUFFER_NUM         16            /* Range: 1..64 */ 
#define CONF_CAN0_TX_BUFFER_NUM         4             /* Range: 1..16 */ 
#define CONF_CAN0_TX_FIFO_QUEUE_NUM     4             /* Range: 1..16 */ 
#define CONF_CAN0_TX_EVENT_FIFO         8             /* Range: 1..32 */ 

#define CONF_CAN0_RX_STANDARD_ID_FILTER_NUM     32    /* Range: 1..128 */ 
#define CONF_CAN0_RX_EXTENDED_ID_FILTER_NUM     16    /* Range: 1..64 */ 

#define CONF_CAN1_RX_FIFO_0_NUM         16            /* Range: 1..64 */ 
#define CONF_CAN1_RX_FIFO_1_NUM         16            /* Range: 1..64 */ 
#define CONF_CAN1_RX_BUFFER_NUM         16            /* Range: 1..64 */ 
#define CONF_CAN1_TX_BUFFER_NUM         4             /* Range: 1..16 */ 
#define CONF_CAN1_TX_FIFO_QUEUE_NUM     4             /* Range: 1..16 */ 
#define CONF_CAN1_TX_EVENT_FIFO         8             /* Range: 1..32 */ 

#define CONF_CAN1_RX_STANDARD_ID_FILTER_NUM     32    /* Range: 1..128 */ 
#define CONF_CAN1_RX_EXTENDED_ID_FILTER_NUM     16    /* Range: 1..64 */ 

/* The value should be 8/12/16/20/24/32/48/64. */
#define CONF_CAN_ELEMENT_DATA_SIZE         8

/*
 * The setting of the nominal bit rate is based on the GCLK_CAN is 48M which you can
 * change in the conf_clock.h. Below is the default configuration. The
 * time quanta is 48MHz / (5+1) =  8MHz. And each bit is (3+10+3) = 16 time
 * quanta which means the bit rate is 8MHz / 16 = 500KHz.
 */
/* Nominal bit Baud Rate Prescaler */
#define CONF_CAN_NBTP_NBRP_VALUE    5
/* Nominal bit (Re)Synchronization Jump Width */
#define CONF_CAN_NBTP_NSJW_VALUE    3
/* Nominal bit Time segment before sample point */
#define CONF_CAN_NBTP_NTSEG1_VALUE  10
/* Nominal bit Time segment after sample point */
#define CONF_CAN_NBTP_NTSEG2_VALUE  3

/*
 * The setting of the data bit rate is based on the GCLK_CAN is 48M which you can
 * change in the conf_clock.h. Below is the default configuration. The
 * time quanta is 48MHz / (5+1) =  8MHz. And each bit is (3+10+3) = 16 time
 * quanta which means the bit rate is 8MHz / 16 = 500KHz.
 */
/* Data bit Baud Rate Prescaler */
#define CONF_CAN_DBTP_DBRP_VALUE    5
/* Data bit (Re)Synchronization Jump Width */
#define CONF_CAN_DBTP_DSJW_VALUE    3
/* Data bit Time segment before sample point */
#define CONF_CAN_DBTP_DTSEG1_VALUE  10
/* Data bit Time segment after sample point */
#define CONF_CAN_DBTP_DTSEG2_VALUE  3

#endif
