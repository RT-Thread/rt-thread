/*
 * Copyright (c) 2021 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ----------------------------------------------------------------------
 *
 * $Date:        1. March 2021
 * $Revision:    V1.0.0
 *
 * Project:      CMSIS-DAP Source
 * Title:        UART.c CMSIS-DAP UART
 *
 *---------------------------------------------------------------------------*/

#include "DAP_config.h"
#include "DAP.h"

#if (DAP_UART != 0)

#ifdef DAP_FW_V1
#error "UART Communication Port not supported in DAP V1!"
#endif

#include "Driver_USART.h"

#include "cmsis_os2.h"
#include <string.h>

#define UART_RX_BLOCK_SIZE    32U   /* Uart Rx Block Size (must be 2^n) */

// USART Driver
#define _USART_Driver_(n)  Driver_USART##n
#define  USART_Driver_(n) _USART_Driver_(n)
extern ARM_DRIVER_USART    USART_Driver_(DAP_UART_DRIVER);
#define pUSART           (&USART_Driver_(DAP_UART_DRIVER))

// UART Configuration
#if (DAP_UART_USB_COM_PORT != 0)
static uint8_t  UartTransport = DAP_UART_TRANSPORT_USB_COM_PORT;
#else
static uint8_t  UartTransport = DAP_UART_TRANSPORT_NONE;
#endif

// UART Flags
static uint8_t  UartConfigured = 0U;
static uint8_t  UartReceiveEnabled = 0U;
static uint8_t  UartTransmitEnabled = 0U;
static uint8_t  UartTransmitActive = 0U;

// UART TX Buffer
static uint8_t  UartTxBuf[DAP_UART_TX_BUFFER_SIZE];
static volatile uint32_t UartTxIndexI = 0U;
static volatile uint32_t UartTxIndexO = 0U;

// UART RX Buffer
static uint8_t  UartRxBuf[DAP_UART_RX_BUFFER_SIZE];
static volatile uint32_t UartRxIndexI = 0U;
static volatile uint32_t UartRxIndexO = 0U;

// Uart Errors
static volatile uint8_t  UartErrorRxDataLost = 0U;
static volatile uint8_t  UartErrorFraming = 0U;
static volatile uint8_t  UartErrorParity = 0U;

// UART Transmit
static uint32_t UartTxNum = 0U;

// Function prototypes
static uint8_t  UART_Init (void);
static void     UART_Uninit (void);
static uint8_t  UART_Get_Status (void);
static uint8_t  UART_Receive_Enable (void);
static uint8_t  UART_Transmit_Enable (void);
static void     UART_Receive_Disable (void);
static void     UART_Transmit_Disable (void);
static void     UART_Receive_Flush (void);
static void     UART_Transmit_Flush (void);
static void     UART_Receive (void);
static void     UART_Transmit (void);


// USART Driver Callback function
//   event: event mask
static void USART_Callback (uint32_t event) {
  if (event &  ARM_USART_EVENT_SEND_COMPLETE) {
    UartTxIndexO += UartTxNum;
    UartTransmitActive = 0U;
    UART_Transmit();
  }
  if (event &  ARM_USART_EVENT_RECEIVE_COMPLETE) {
    UartRxIndexI += UART_RX_BLOCK_SIZE;
    UART_Receive();
  }
  if (event &  ARM_USART_EVENT_RX_OVERFLOW) {
    UartErrorRxDataLost = 1U;
  }
  if (event &  ARM_USART_EVENT_RX_FRAMING_ERROR) {
    UartErrorFraming = 1U;
  }
  if (event &  ARM_USART_EVENT_RX_PARITY_ERROR) {
    UartErrorParity = 1U;
  }
}

// Init UART
//   return: DAP_OK or DAP_ERROR
static uint8_t UART_Init (void) {
  int32_t status;
  uint8_t ret = DAP_ERROR;

  UartConfigured = 0U;
  UartReceiveEnabled = 0U;
  UartTransmitEnabled = 0U;
  UartTransmitActive = 0U;
  UartErrorRxDataLost = 0U;
  UartErrorFraming = 0U;
  UartErrorParity = 0U;
  UartTxIndexI = 0U;
  UartTxIndexO = 0U;
  UartRxIndexI = 0U;
  UartRxIndexO = 0U;
  UartTxNum = 0U;

  status = pUSART->Initialize(USART_Callback);
  if (status == ARM_DRIVER_OK) {
    status = pUSART->PowerControl(ARM_POWER_FULL);
  }
  if (status == ARM_DRIVER_OK) {
    ret = DAP_OK;
  }

  return (ret);
}

// Un-Init UART
static void UART_Uninit (void) {
  UartConfigured = 0U;

  pUSART->PowerControl(ARM_POWER_OFF);
  pUSART->Uninitialize();
}

// Get UART Status
//   return: status
static uint8_t UART_Get_Status (void) {
  uint8_t status = 0U;

  if (UartReceiveEnabled != 0U) {
    status |= DAP_UART_STATUS_RX_ENABLED;
  }
  if (UartErrorRxDataLost != 0U) {
    UartErrorRxDataLost = 0U;
    status |= DAP_UART_STATUS_RX_DATA_LOST;
  }
  if (UartErrorFraming != 0U) {
    UartErrorFraming = 0U;
    status |= DAP_UART_STATUS_FRAMING_ERROR;
  }
  if (UartErrorParity != 0U) {
    UartErrorParity = 0U;
    status |= DAP_UART_STATUS_PARITY_ERROR;
  }
  if (UartTransmitEnabled != 0U) {
    status |= DAP_UART_STATUS_TX_ENABLED;
  }

  return (status);
}

// Enable UART Receive
//   return: DAP_OK or DAP_ERROR
static uint8_t UART_Receive_Enable (void) {
  int32_t status;
  uint8_t ret = DAP_ERROR;

  if (UartReceiveEnabled == 0U) {
    // Flush Buffers
    UartRxIndexI = 0U;
    UartRxIndexO = 0U;

    UART_Receive();
    status = pUSART->Control(ARM_USART_CONTROL_RX, 1U);
    if (status == ARM_DRIVER_OK) {
      UartReceiveEnabled = 1U;
      ret = DAP_OK;
    }
  } else {
    ret = DAP_OK;
  }

  return (ret);
}

// Enable UART Transmit
//   return: DAP_OK or DAP_ERROR
static uint8_t UART_Transmit_Enable (void) {
  int32_t status;
  uint8_t ret = DAP_ERROR;

  if (UartTransmitEnabled == 0U) {
    // Flush Buffers
    UartTransmitActive = 0U;
    UartTxIndexI = 0U;
    UartTxIndexO = 0U;
    UartTxNum = 0U;

    status = pUSART->Control(ARM_USART_CONTROL_TX, 1U);
    if (status == ARM_DRIVER_OK) {
      UartTransmitEnabled = 1U;
      ret = DAP_OK;
    }
  } else {
    ret = DAP_OK;
  }

  return (ret);
}

// Disable UART Receive
static void UART_Receive_Disable (void) {
  if (UartReceiveEnabled != 0U) {
    pUSART->Control(ARM_USART_CONTROL_RX, 0U);
    pUSART->Control(ARM_USART_ABORT_RECEIVE, 0U);
    UartReceiveEnabled = 0U;
  }
}

// Disable UART Transmit
static void UART_Transmit_Disable (void) {
  if (UartTransmitEnabled != 0U) {
    pUSART->Control(ARM_USART_ABORT_SEND, 0U);
    pUSART->Control(ARM_USART_CONTROL_TX, 0U);
    UartTransmitActive = 0U;
    UartTransmitEnabled = 0U;
  }
}

// Flush UART Receive buffer
static void UART_Receive_Flush (void) {
  pUSART->Control(ARM_USART_ABORT_RECEIVE, 0U);
  UartRxIndexI = 0U;
  UartRxIndexO = 0U;
  if (UartReceiveEnabled != 0U) {
    UART_Receive();
  }
}

// Flush UART Transmit buffer
static void UART_Transmit_Flush (void) {
  pUSART->Control(ARM_USART_ABORT_SEND, 0U);
  UartTransmitActive = 0U;
  UartTxIndexI = 0U;
  UartTxIndexO = 0U;
  UartTxNum = 0U;
}

// Receive data from target via UART
static void UART_Receive (void) {
  uint32_t index;

  index = UartRxIndexI & (DAP_UART_RX_BUFFER_SIZE - 1U);
  pUSART->Receive(&UartRxBuf[index], UART_RX_BLOCK_SIZE);
}

// Transmit available data to target via UART
static void UART_Transmit (void) {
  uint32_t count;
  uint32_t index;

  count = UartTxIndexI - UartTxIndexO;
  index = UartTxIndexO & (DAP_UART_TX_BUFFER_SIZE - 1U);

  if (count != 0U) {
    if ((index + count) <= DAP_UART_TX_BUFFER_SIZE) {
      UartTxNum = count;
    } else {
      UartTxNum = DAP_UART_TX_BUFFER_SIZE - index;
    }
    UartTransmitActive = 1U;
    pUSART->Send(&UartTxBuf[index], UartTxNum);
  }
}

// Process UART Transport command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t UART_Transport (const uint8_t *request, uint8_t *response) {
  uint8_t  transport;
  uint8_t  ret = DAP_ERROR;

  transport = *request;
  switch (transport) {
    case DAP_UART_TRANSPORT_NONE:
      switch (UartTransport) {
        case DAP_UART_TRANSPORT_NONE:
          ret = DAP_OK;
          break;
        case DAP_UART_TRANSPORT_USB_COM_PORT:
#if (DAP_UART_USB_COM_PORT != 0)
          USB_COM_PORT_Activate(0U);
          UartTransport = DAP_UART_TRANSPORT_NONE;
          ret = DAP_OK;
#endif
          break;
        case DAP_UART_TRANSPORT_DAP_COMMAND:
          UART_Receive_Disable();
          UART_Transmit_Disable();
          UART_Uninit();
          UartTransport = DAP_UART_TRANSPORT_NONE;
          ret= DAP_OK;
          break;
      }
      break;
    case DAP_UART_TRANSPORT_USB_COM_PORT:
      switch (UartTransport) {
        case DAP_UART_TRANSPORT_NONE:
#if (DAP_UART_USB_COM_PORT != 0)
          if (USB_COM_PORT_Activate(1U) == 0U) {
            UartTransport = DAP_UART_TRANSPORT_USB_COM_PORT;
            ret = DAP_OK;
          }
#endif
          break;
        case DAP_UART_TRANSPORT_USB_COM_PORT:
          ret = DAP_OK;
          break;
        case DAP_UART_TRANSPORT_DAP_COMMAND:
          UART_Receive_Disable();
          UART_Transmit_Disable();
          UART_Uninit();
          UartTransport = DAP_UART_TRANSPORT_NONE;
#if (DAP_UART_USB_COM_PORT != 0)
          if (USB_COM_PORT_Activate(1U) == 0U) {
            UartTransport = DAP_UART_TRANSPORT_USB_COM_PORT;
            ret = DAP_OK;
          }
#endif
          break;
      }
      break;
    case DAP_UART_TRANSPORT_DAP_COMMAND:
      switch (UartTransport) {
        case DAP_UART_TRANSPORT_NONE:
          ret = UART_Init();
          if (ret == DAP_OK) {
            UartTransport = DAP_UART_TRANSPORT_DAP_COMMAND;
          }
          break;
        case DAP_UART_TRANSPORT_USB_COM_PORT:
#if (DAP_UART_USB_COM_PORT != 0)
          USB_COM_PORT_Activate(0U);
          UartTransport = DAP_UART_TRANSPORT_NONE;
#endif
          ret = UART_Init();
          if (ret == DAP_OK) {
            UartTransport = DAP_UART_TRANSPORT_DAP_COMMAND;
          }
          break;
        case DAP_UART_TRANSPORT_DAP_COMMAND:
          ret = DAP_OK;
          break;
      }
      break;
    default:
      break;
  }

  *response = ret;

  return ((1U << 16) | 1U);
}

// Process UART Configure command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t UART_Configure (const uint8_t *request, uint8_t *response) {
  uint8_t  control, status;
  uint32_t baudrate;
  int32_t  result;

  if (UartTransport != DAP_UART_TRANSPORT_DAP_COMMAND) {
    status = DAP_UART_CFG_ERROR_DATA_BITS |
             DAP_UART_CFG_ERROR_PARITY    |
             DAP_UART_CFG_ERROR_STOP_BITS;
    baudrate = 0U;  // baudrate error
  } else {

    status   = 0U;
    control  = *request;
    baudrate = (uint32_t)(*(request+1) <<  0) |
               (uint32_t)(*(request+2) <<  8) |
               (uint32_t)(*(request+3) << 16) |
               (uint32_t)(*(request+4) << 24);

    result = pUSART->Control(control |
                             ARM_USART_MODE_ASYNCHRONOUS |
                             ARM_USART_FLOW_CONTROL_NONE,
                             baudrate);
    if (result == ARM_DRIVER_OK) {
      UartConfigured = 1U;
    } else {
      UartConfigured = 0U;
      switch (result) {
        case ARM_USART_ERROR_BAUDRATE:
          status = 0U;
          baudrate = 0U;
          break;
        case ARM_USART_ERROR_DATA_BITS:
          status = DAP_UART_CFG_ERROR_DATA_BITS;
          break;
        case ARM_USART_ERROR_PARITY:
          status = DAP_UART_CFG_ERROR_PARITY;
          break;
        case ARM_USART_ERROR_STOP_BITS:
          status = DAP_UART_CFG_ERROR_STOP_BITS;
          break;
        default:
          status = DAP_UART_CFG_ERROR_DATA_BITS |
                   DAP_UART_CFG_ERROR_PARITY    |
                   DAP_UART_CFG_ERROR_STOP_BITS;
          baudrate = 0U;
          break;
      }
    }
  }

  *response++ = status;
  *response++ = (uint8_t)(baudrate >>  0);
  *response++ = (uint8_t)(baudrate >>  8);
  *response++ = (uint8_t)(baudrate >> 16);
  *response   = (uint8_t)(baudrate >> 24);

  return ((5U << 16) | 5U);
}

// Process UART Control command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t UART_Control (const uint8_t *request, uint8_t *response) {
  uint8_t control;
  uint8_t result;
  uint8_t ret = DAP_OK;

  if (UartTransport != DAP_UART_TRANSPORT_DAP_COMMAND) {
    ret = DAP_ERROR;
  } else {
 
    control = *request;

    if ((control & DAP_UART_CONTROL_RX_DISABLE) != 0U) {
      // Receive disable
      UART_Receive_Disable();
    } else if ((control & DAP_UART_CONTROL_RX_ENABLE) != 0U) {
      // Receive enable
      if (UartConfigured != 0U) {
        result = UART_Receive_Enable();
        if (result != DAP_OK) {
          ret = DAP_ERROR;
        }
      } else {
        ret = DAP_ERROR;
      }
    }
    if ((control & DAP_UART_CONTROL_RX_BUF_FLUSH) != 0U) {
      UART_Receive_Flush();
    }

    if ((control & DAP_UART_CONTROL_TX_DISABLE) != 0U) {
      // Transmit disable
      UART_Transmit_Disable();
    } else if ((control & DAP_UART_CONTROL_TX_ENABLE) != 0U) {
      // Transmit enable
      if (UartConfigured != 0U) {
        result = UART_Transmit_Enable();
        if (result != DAP_OK) {
          ret = DAP_ERROR;
        }
      } else {
        ret = DAP_ERROR;
      }
    } 
    if ((control & DAP_UART_CONTROL_TX_BUF_FLUSH) != 0U) {
      UART_Transmit_Flush();
    }
  }

  *response = ret;

  return ((1U << 16) | 1U);
}

// Process UART Status command and prepare response
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t UART_Status (uint8_t *response) {
  uint32_t rx_cnt, tx_cnt;
  uint32_t cnt;
  uint8_t  status;

  if ((UartTransport != DAP_UART_TRANSPORT_DAP_COMMAND) ||
      (UartConfigured == 0U)) {
    rx_cnt = 0U;
    tx_cnt = 0U;
    status = 0U;
  } else {

    rx_cnt  = UartRxIndexI - UartRxIndexO;
    rx_cnt += pUSART->GetRxCount();
    if (rx_cnt > (DAP_UART_RX_BUFFER_SIZE - (UART_RX_BLOCK_SIZE*2))) {
      // Overflow
      UartErrorRxDataLost = 1U;
      rx_cnt = (DAP_UART_RX_BUFFER_SIZE - (UART_RX_BLOCK_SIZE*2));
      UartRxIndexO = UartRxIndexI - rx_cnt;
    }

    tx_cnt = UartTxIndexI - UartTxIndexO;
    cnt = pUSART->GetTxCount();
    if (UartTransmitActive != 0U) {
      tx_cnt -= cnt;
    }

    status = UART_Get_Status();
  }

  *response++ = status;
  *response++ = (uint8_t)(rx_cnt >>  0);
  *response++ = (uint8_t)(rx_cnt >>  8);
  *response++ = (uint8_t)(rx_cnt >> 16);
  *response++ = (uint8_t)(rx_cnt >> 24);
  *response++ = (uint8_t)(tx_cnt >>  0);
  *response++ = (uint8_t)(tx_cnt >>  8);
  *response++ = (uint8_t)(tx_cnt >> 16);
  *response   = (uint8_t)(tx_cnt >> 24);

  return ((0U << 16) | 9U);
}

// Process UART Transfer command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t UART_Transfer (const uint8_t *request, uint8_t *response) {
  uint32_t rx_cnt, tx_cnt;
  uint32_t rx_num, tx_num;
  uint8_t *rx_data;
  const
  uint8_t *tx_data;
  uint32_t num;
  uint32_t index;
  uint8_t  status;

  if (UartTransport != DAP_UART_TRANSPORT_DAP_COMMAND) {
    status = 0U;
    rx_cnt = 0U;
    tx_cnt = 0U;
  } else {

    // RX Data
    rx_cnt = ((uint32_t)(*(request+0) << 0)  |
              (uint32_t)(*(request+1) << 8));

    if (rx_cnt > (DAP_PACKET_SIZE - 6U)) {
      rx_cnt = (DAP_PACKET_SIZE - 6U);
    }
    rx_num  = UartRxIndexI - UartRxIndexO;
    rx_num += pUSART->GetRxCount();
    if (rx_num > (DAP_UART_RX_BUFFER_SIZE - (UART_RX_BLOCK_SIZE*2))) {
      // Overflow
      UartErrorRxDataLost = 1U;
      rx_num = (DAP_UART_RX_BUFFER_SIZE - (UART_RX_BLOCK_SIZE*2));
      UartRxIndexO = UartRxIndexI - rx_num;
    }
    if (rx_cnt > rx_num) {
      rx_cnt = rx_num;
    }

    rx_data = (response+5);
    index = UartRxIndexO & (DAP_UART_RX_BUFFER_SIZE - 1U);
    if ((index + rx_cnt) <= DAP_UART_RX_BUFFER_SIZE) {
      memcpy( rx_data,      &UartRxBuf[index], rx_cnt);
    } else {
      num = DAP_UART_RX_BUFFER_SIZE - index;
      memcpy( rx_data,      &UartRxBuf[index], num);
      memcpy(&rx_data[num], &UartRxBuf[0],     rx_cnt - num);
    }
    UartRxIndexO += rx_cnt;

    // TX Data
    tx_cnt  = ((uint32_t)(*(request+2) << 0) |
               (uint32_t)(*(request+3) << 8));
    tx_data =              (request+4);

    if (tx_cnt > (DAP_PACKET_SIZE - 5U)) {
      tx_cnt = (DAP_PACKET_SIZE - 5U);
    }
    tx_num = UartTxIndexI - UartTxIndexO;
    num = pUSART->GetTxCount();
    if (UartTransmitActive != 0U) {
      tx_num -= num;
    }
    if (tx_cnt > (DAP_UART_TX_BUFFER_SIZE - tx_num)) {
      tx_cnt = (DAP_UART_TX_BUFFER_SIZE - tx_num);
    }

    index = UartTxIndexI & (DAP_UART_TX_BUFFER_SIZE - 1U);
    if ((index + tx_cnt) <= DAP_UART_TX_BUFFER_SIZE) {
      memcpy(&UartTxBuf[index],  tx_data,      tx_cnt);
    } else {
      num = DAP_UART_TX_BUFFER_SIZE - index;
      memcpy(&UartTxBuf[index],  tx_data,      num);
      memcpy(&UartTxBuf[0],     &tx_data[num], tx_cnt - num);
    }
    UartTxIndexI += tx_cnt;

    if (UartTransmitActive == 0U) {
      UART_Transmit();
    }

    status = UART_Get_Status();
  }

  *response++ = status;
  *response++ = (uint8_t)(tx_cnt >> 0);
  *response++ = (uint8_t)(tx_cnt >> 8);
  *response++ = (uint8_t)(rx_cnt >> 0);
  *response   = (uint8_t)(rx_cnt >> 8);

  return (((4U + tx_cnt) << 16) | (5U + rx_cnt));
}

#endif /* DAP_UART */
