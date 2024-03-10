/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __CAN_H__
#define __CAN_H__

#include "sdk.h"

#define CAN_TIMING_MASK  0x00C0FFF8  // to zero out presdiv, pseg1, pseg2, prop_seg
#define CAN_NUMBER_OF_BUFFERS 64    // Define the number of MB
#define CAN_LAST_MB 63
#define CAN_TIMING_PARAMETERS 0x0892
#define CAN_MB_OFFSET 0x80
#define CAN_IRQS(x) ( (x) == HW_FLEXCAN1 ? IMX_INT_FLEXCAN1 : (x) == HW_FLEXCAN2 ? IMX_INT_FLEXCAN2 : 0xFFFFFFFF)

//! @brief  CAN message buffer structure
struct can_mb {
    volatile uint32_t cs;       //! Code and Status
    volatile uint32_t id;       //! ID
    volatile uint32_t data0;    
    volatile uint32_t data1;   
};

//! @brief  CAN Message Buffers   0x80 - 0x170
struct can_message_buffers {
    volatile struct can_mb MB[64];
};

//! @brief  CAN timing related structures 
struct time_segment {
	uint32_t propseg;
	uint32_t pseg1;
	uint32_t pseg2;
};

//! @brief    Baudrates of CAN bus(kps) 
enum can_bitrate {
      MBPS_1,
      KBPS_800,
      KBPS_500,
      KBPS_250,
      KBPS_125,
      KBPS_62,  //62.5kps
      KBPS_20,
      KBPS_10
};

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

/* CAN driver list of functions */
/*!
 * @brief Reset FlexCAN controller
 *
 * @param   instance	the FlexCAN instance number.
 */
void can_sw_reset(uint32_t instance);

/*!
 * @brief Initialize CAN controller
 *
 * @param   instance 	the FlexCAN instance number.
 * @param   max_mb	Max mailbox will be used
 */
void can_init(uint32_t instance, uint32_t max_mb);

/*!
 * @brief Set message box fields
 *
 * @param   instance	the FlexCAN instance number.
 * @param   mbID	Index of the message box 
 * @param   cs		control/statuc code
 * @param   id		ID of the message to be transfer
 * @param   data0	first 4 bytes of the CAN message 
 * @param   data1	last 4 bytes of the CAN message 
 */
void set_can_mb(uint32_t instance, uint32_t mbID, uint32_t cs, uint32_t id, uint32_t data0, uint32_t data1);

/*!
 * @brief Dump the message box
 *
 * @param   instance	the FlexCAN instance number.
 * @param   mbID	Index of the message box 
 */
void print_can_mb(uint32_t instance, uint32_t mbID);

/*!
 * @brief Enable the interrupt of the FlexCAN module
 *
 * @param   instance	the FlexCAN instance number.
 * @param   mbID	Index of the message box 
 */
void can_enable_mb_interrupt(uint32_t instance, uint32_t mbID);

/*!
 * @brief Disable the interrupt of the FlexCAN module
 *
 * @param   instance	the FlexCAN instance number.
 * @param   mbID	Index of the message box 
 */
void can_disable_mb_interrupt(uint32_t instance, uint32_t mbID);


/*!
 * @brief Setup the interrupt of the FlexCAN module
 *
 * It enables or disables the related HW module interrupt, and attached the related sub-routine
 * into the vector table.
 *
 * @param   instance	the FlexCAN instance number.
 * @param   irq_subroutine the FlexCAN interrupt interrupt routine.
 * @param   enableIt True to enable the interrupt, false to disable.
 */
void can_setup_interrupt(uint32_t instance, void (*irq_subroutine)(void), bool enableIt);

/*!
 * @brief Un-freeze the FlexCAN module
 *
 * @param   instance	the FlexCAN instance number.
 */
void can_exit_freeze(uint32_t instance);

/*!
 * @brief Freeze the FlexCAN module
 *
 * @param   instance	the FlexCAN instance number.
 */
void can_freeze(uint32_t instance);

/*!
 * @brief Set bit rate
 *
 * CAN bit rate = sclk (aka Freq-TQ) / number-of-time-quanta
 *
 * @param   instance	the FlexCAN instance number.
 * @param   bitrate	CAN bit rate.
 */
void can_update_bitrate(uint32_t instance, enum can_bitrate bitrate);

/*!
 * @brief Get the interrupt flags(iflag1 | (iflag2<<32))
 *
 * @param   instance	the FlexCAN instance number.
 * 
 * @return 	interrupt flags(ie, iflag1 | (iflag2<<32))
 */
uint64_t can_mb_int_flag(uint32_t instance);

/*!
 * @brief Clear the interrupt flag of the message box
 *
 * @param   instance	the FlexCAN instance number.
 * @param   mbID	Index of the message box 
 */
void can_mb_int_ack(uint32_t instance, uint32_t mbID);

//! @name Board support functions
//!
//! These functions are called by the flexcan driver and must be defined in the
//! board support library or the application.
//@{

/*!
 * @brief Configure IOMUX and GPIOs to enable CAN.
 *
 * @param module_instance The CAN module instance number to configure for, starting at 1.
 */
void hw_can_iomux_config(uint32_t module_instance);

//@}

#endif //__CAN_H__
