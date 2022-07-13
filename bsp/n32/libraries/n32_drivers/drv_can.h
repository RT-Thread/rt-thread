/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file drv_can.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
 
#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#include <rtdevice.h>
#include <rtthread.h>
#include "n32g45x_can.h"

#define CAN_BAUDRATE_1M   ((uint32_t)1000)
#define CAN_BAUDRATE_500K ((uint32_t)500)
#define CAN_BAUDRATE_250K ((uint32_t)250)
#define CAN_BAUDRATE_125K ((uint32_t)125)
#define CAN_BAUDRATE_100K ((uint32_t)100)
#define CAN_BAUDRATE_50K  ((uint32_t)50)
#define CAN_BAUDRATE_20K  ((uint32_t)20)
#define CAN_BAUDRATE_10K  ((uint32_t)10)
#define CAN_BTR_CALCULATE ((uint32_t)6000)

#define CAN_TX_MAILBOX0             (0x00000001U)  /*!< Tx Mailbox 0  */
#define CAN_TX_MAILBOX1             (0x00000002U)  /*!< Tx Mailbox 1  */
#define CAN_TX_MAILBOX2             (0x00000004U)  /*!< Tx Mailbox 2  */


#define CAN_FILTERNUM0 ((uint8_t)0)

/* attention !!! baud calculation example: Tclk / ((ss + bs1 + bs2) * brp)  36 / ((1 + 8 + 3) * 3) = 1MHz*/

/* Default config for serial_configure structure */
#define RT_CAN_FILTER_CONFIG_DEFAULT           \
{                                          \
    BAUD_RATE_115200,   /* 115200 bits/s */  \
    DATA_BITS_8,        /* 8 databits */     \
    STOP_BITS_1,        /* 1 stopbit */      \
    PARITY_NONE,        /* No parity  */     \
    HFC_CONTROL_NONE,   /* No Hardwareflow control */ \
    TX_RX_MODE,         /* Tx_Rx mode */    \
    RT_SERIAL_RB_BUFSZ, /* Buffer size */  \
    0                                      \
}

struct n32_baud_rate_tab
{
    rt_uint32_t baud_rate;
    rt_uint32_t config_data;
};

/**
  * @brief  CAN handle Structure definition
  */
typedef struct
{
  CAN_Module                *Instance;  /*!< Register base address          */

  CAN_InitType              Init;       /*!< CAN required parameters        */

  CanTxMessage*             pTxMsg;     /*!< Pointer to transmit structure  */

  CanRxMessage*             pRxMsg;     /*!< Pointer to reception structure for RX FIFO0 msg */

  CanRxMessage*             pRx1Msg;    /*!< Pointer to reception structure for RX FIFO1 msg */

  uint32_t                  State;      /*!< CAN communication state        */

  FlagStatus                Lock;       /*!< CAN locking object             */

  uint32_t                  ErrorCode;  /*!< CAN Error code                 */

}CAN_HandleTypeDef;

/* n32 can device */
struct n32_can
{
    char *name;
    CAN_HandleTypeDef CanHandle;
    CAN_FilterInitType FilterConfig;
    struct rt_can_device device;     /* inherit from can device */
};

int rt_hw_can_init(void);

#endif /* __DRV_CAN_H__ */
