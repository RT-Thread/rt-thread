/*
 * Copyright (c) 2013-2021 ARM Limited. All rights reserved.
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
 * $Date:        29. March 2021
 * $Revision:    V2.0.1
 *
 * Project:      CMSIS-DAP Source
 * Title:        SWO.c CMSIS-DAP SWO I/O
 *
 *---------------------------------------------------------------------------*/

#include "DAP_config.h"
#include "DAP.h"
#if (SWO_UART != 0)
#include "Driver_USART.h"
#endif
#if (SWO_STREAM != 0)
#include "cmsis_os2.h"
#define   osObjectsExternal
#include "osObjects.h"
#endif

#if (SWO_STREAM != 0)
#ifdef DAP_FW_V1
#error "SWO Streaming Trace not supported in DAP V1!"
#endif
#endif

#if (SWO_UART != 0)

// USART Driver
#define _USART_Driver_(n)  Driver_USART##n
#define  USART_Driver_(n) _USART_Driver_(n)
extern ARM_DRIVER_USART    USART_Driver_(SWO_UART_DRIVER);
#define pUSART           (&USART_Driver_(SWO_UART_DRIVER))

static uint8_t USART_Ready = 0U;

#endif  /* (SWO_UART != 0) */


#if ((SWO_UART != 0) || (SWO_MANCHESTER != 0))


#define SWO_STREAM_TIMEOUT      50U     /* Stream timeout in ms */

#define USB_BLOCK_SIZE          512U    /* USB Block Size */
#define TRACE_BLOCK_SIZE        64U     /* Trace Block Size (2^n: 32...512) */

// Trace State
static uint8_t  TraceTransport =  0U;       /* Trace Transport */
static uint8_t  TraceMode      =  0U;       /* Trace Mode */
static uint8_t  TraceStatus    =  0U;       /* Trace Status without Errors */
static uint8_t  TraceError[2]  = {0U, 0U};  /* Trace Error flags (banked) */
static uint8_t  TraceError_n   =  0U;       /* Active Trace Error bank */

// Trace Buffer
static uint8_t  TraceBuf[SWO_BUFFER_SIZE];  /* Trace Buffer (must be 2^n) */
static volatile uint32_t TraceIndexI  = 0U; /* Incoming Trace Index */
static volatile uint32_t TraceIndexO  = 0U; /* Outgoing Trace Index */
static volatile uint8_t  TraceUpdate;       /* Trace Update Flag */
static          uint32_t TraceBlockSize;    /* Current Trace Block Size */

#if (TIMESTAMP_CLOCK != 0U)
// Trace Timestamp
static volatile struct {
  uint32_t index;
  uint32_t tick;
} TraceTimestamp;
#endif

// Trace Helper functions
static void     ClearTrace     (void);
static void     ResumeTrace    (void);
static uint32_t GetTraceCount  (void);
static uint8_t  GetTraceStatus (void);
static void     SetTraceError  (uint8_t flag);

#if (SWO_STREAM != 0)
extern osThreadId_t      SWO_ThreadId;
static volatile uint8_t  TransferBusy = 0U; /* Transfer Busy Flag */
static          uint32_t TransferSize;      /* Current Transfer Size */
#endif


#if (SWO_UART != 0)

// USART Driver Callback function
//   event: event mask
static void USART_Callback (uint32_t event) {
  uint32_t index_i;
  uint32_t index_o;
  uint32_t count;
  uint32_t num;

  if (event &  ARM_USART_EVENT_RECEIVE_COMPLETE) {
#if (TIMESTAMP_CLOCK != 0U)
    TraceTimestamp.tick = TIMESTAMP_GET();
#endif
    index_o  = TraceIndexO;
    index_i  = TraceIndexI;
    index_i += TraceBlockSize;
    TraceIndexI = index_i;
#if (TIMESTAMP_CLOCK != 0U)
    TraceTimestamp.index = index_i;
#endif
    num   = TRACE_BLOCK_SIZE - (index_i & (TRACE_BLOCK_SIZE - 1U));
    count = index_i - index_o;
    if (count <= (SWO_BUFFER_SIZE - num)) {
      index_i &= SWO_BUFFER_SIZE - 1U;
      TraceBlockSize = num;
      pUSART->Receive(&TraceBuf[index_i], num);
    } else {
      TraceStatus = DAP_SWO_CAPTURE_ACTIVE | DAP_SWO_CAPTURE_PAUSED;
    }
    TraceUpdate = 1U;
#if (SWO_STREAM != 0)
    if (TraceTransport == 2U) {
      if (count >= (USB_BLOCK_SIZE - (index_o & (USB_BLOCK_SIZE - 1U)))) {
        osThreadFlagsSet(SWO_ThreadId, 1U);
      }
    }
#endif
  }
  if (event &  ARM_USART_EVENT_RX_OVERFLOW) {
    SetTraceError(DAP_SWO_BUFFER_OVERRUN);
  }
  if (event & (ARM_USART_EVENT_RX_BREAK         |
               ARM_USART_EVENT_RX_FRAMING_ERROR |
               ARM_USART_EVENT_RX_PARITY_ERROR)) {
    SetTraceError(DAP_SWO_STREAM_ERROR);
  }
}

// Enable or disable SWO Mode (UART)
//   enable: enable flag
//   return: 1 - Success, 0 - Error
__WEAK uint32_t SWO_Mode_UART (uint32_t enable) {
  int32_t status;

  USART_Ready = 0U;

  if (enable != 0U) {
    status = pUSART->Initialize(USART_Callback);
    if (status != ARM_DRIVER_OK) {
      return (0U);
    }
    status = pUSART->PowerControl(ARM_POWER_FULL);
    if (status != ARM_DRIVER_OK) {
      pUSART->Uninitialize();
      return (0U);
    }
  } else {
    pUSART->Control(ARM_USART_CONTROL_RX, 0U);
    pUSART->Control(ARM_USART_ABORT_RECEIVE, 0U);
    pUSART->PowerControl(ARM_POWER_OFF);
    pUSART->Uninitialize();
  }
  return (1U);
}

// Configure SWO Baudrate (UART)
//   baudrate: requested baudrate
//   return:   actual baudrate or 0 when not configured
__WEAK uint32_t SWO_Baudrate_UART (uint32_t baudrate) {
  int32_t  status;
  uint32_t index;
  uint32_t num;

  if (baudrate > SWO_UART_MAX_BAUDRATE) {
    baudrate = SWO_UART_MAX_BAUDRATE;
  }

  if (TraceStatus & DAP_SWO_CAPTURE_ACTIVE) {
    pUSART->Control(ARM_USART_CONTROL_RX, 0U);
    if (pUSART->GetStatus().rx_busy) {
      TraceIndexI += pUSART->GetRxCount();
      pUSART->Control(ARM_USART_ABORT_RECEIVE, 0U);
    }
  }

  status = pUSART->Control(ARM_USART_MODE_ASYNCHRONOUS |
                           ARM_USART_DATA_BITS_8       |
                           ARM_USART_PARITY_NONE       |
                           ARM_USART_STOP_BITS_1,
                           baudrate);

  if (status == ARM_DRIVER_OK) {
    USART_Ready = 1U;
  } else {
    USART_Ready = 0U;
    return (0U);
  }

  if (TraceStatus & DAP_SWO_CAPTURE_ACTIVE) {
    if ((TraceStatus & DAP_SWO_CAPTURE_PAUSED) == 0U) {
      index = TraceIndexI & (SWO_BUFFER_SIZE - 1U);
      num = TRACE_BLOCK_SIZE - (index & (TRACE_BLOCK_SIZE - 1U));
      TraceBlockSize = num;
      pUSART->Receive(&TraceBuf[index], num);
    }
    pUSART->Control(ARM_USART_CONTROL_RX, 1U);
  }

  return (baudrate);
}

// Control SWO Capture (UART)
//   active: active flag
//   return: 1 - Success, 0 - Error
__WEAK uint32_t SWO_Control_UART (uint32_t active) {
  int32_t status;

  if (active) {
    if (!USART_Ready) {
      return (0U);
    }
    TraceBlockSize = 1U;
    status = pUSART->Receive(&TraceBuf[0], 1U);
    if (status != ARM_DRIVER_OK) {
      return (0U);
    }
    status = pUSART->Control(ARM_USART_CONTROL_RX, 1U);
    if (status != ARM_DRIVER_OK) {
      return (0U);
    }
  } else {
    pUSART->Control(ARM_USART_CONTROL_RX, 0U);
    if (pUSART->GetStatus().rx_busy) {
      TraceIndexI += pUSART->GetRxCount();
      pUSART->Control(ARM_USART_ABORT_RECEIVE, 0U);
    }
  }
  return (1U);
}

// Start SWO Capture (UART)
//   buf: pointer to buffer for capturing
//   num: number of bytes to capture
__WEAK void SWO_Capture_UART (uint8_t *buf, uint32_t num) {
  TraceBlockSize = num;
  pUSART->Receive(buf, num);
}

// Get SWO Pending Trace Count (UART)
//   return: number of pending trace data bytes
__WEAK uint32_t SWO_GetCount_UART (void) {
  uint32_t count;

  if (pUSART->GetStatus().rx_busy) {
    count = pUSART->GetRxCount();
  } else {
    count = 0U;
  }
  return (count);
}

#endif  /* (SWO_UART != 0) */


#if (SWO_MANCHESTER != 0)

// Enable or disable SWO Mode (Manchester)
//   enable: enable flag
//   return: 1 - Success, 0 - Error
__WEAK uint32_t SWO_Mode_Manchester (uint32_t enable) {
  return (0U);
}

// Configure SWO Baudrate (Manchester)
//   baudrate: requested baudrate
//   return:   actual baudrate or 0 when not configured
__WEAK uint32_t SWO_Baudrate_Manchester (uint32_t baudrate) {
  return (0U);
}

// Control SWO Capture (Manchester)
//   active: active flag
//   return: 1 - Success, 0 - Error
__WEAK uint32_t SWO_Control_Manchester (uint32_t active) {
  return (0U);
}

// Start SWO Capture (Manchester)
//   buf: pointer to buffer for capturing
//   num: number of bytes to capture
__WEAK void SWO_Capture_Manchester (uint8_t *buf, uint32_t num) {
}

// Get SWO Pending Trace Count (Manchester)
//   return: number of pending trace data bytes
__WEAK uint32_t SWO_GetCount_Manchester (void) {
}

#endif  /* (SWO_MANCHESTER != 0) */


// Clear Trace Errors and Data
static void ClearTrace (void) {

#if (SWO_STREAM != 0)
  if (TraceTransport == 2U) {
    if (TransferBusy != 0U) {
      SWO_AbortTransfer();
      TransferBusy = 0U;
    }
  }
#endif

  TraceError[0] = 0U;
  TraceError[1] = 0U;
  TraceError_n  = 0U;
  TraceIndexI   = 0U;
  TraceIndexO   = 0U;

#if (TIMESTAMP_CLOCK != 0U)
  TraceTimestamp.index = 0U;
  TraceTimestamp.tick  = 0U;
#endif
}

// Resume Trace Capture
static void ResumeTrace (void) {
  uint32_t index_i;
  uint32_t index_o;

  if (TraceStatus == (DAP_SWO_CAPTURE_ACTIVE | DAP_SWO_CAPTURE_PAUSED)) {
    index_i = TraceIndexI;
    index_o = TraceIndexO;
    if ((index_i - index_o) < SWO_BUFFER_SIZE) {
      index_i &= SWO_BUFFER_SIZE - 1U;
      switch (TraceMode) {
#if (SWO_UART != 0)
        case DAP_SWO_UART:
          TraceStatus = DAP_SWO_CAPTURE_ACTIVE;
          SWO_Capture_UART(&TraceBuf[index_i], 1U);
          break;
#endif
#if (SWO_MANCHESTER != 0)
        case DAP_SWO_MANCHESTER:
          TraceStatus = DAP_SWO_CAPTURE_ACTIVE;
          SWO_Capture_Manchester(&TraceBuf[index_i], 1U);
          break;
#endif
        default:
          break;
      }
    }
  }
}

// Get Trace Count
//   return: number of available data bytes in trace buffer
static uint32_t GetTraceCount (void) {
  uint32_t count;

  if (TraceStatus == DAP_SWO_CAPTURE_ACTIVE) {
    do {
      TraceUpdate = 0U;
      count = TraceIndexI - TraceIndexO;
      switch (TraceMode) {
#if (SWO_UART != 0)
        case DAP_SWO_UART:
          count += SWO_GetCount_UART();
          break;
#endif
#if (SWO_MANCHESTER != 0)
        case DAP_SWO_MANCHESTER:
          count += SWO_GetCount_Manchester();
          break;
#endif
        default:
          break;
      }
    } while (TraceUpdate != 0U);
  } else {
    count = TraceIndexI - TraceIndexO;
  }

  return (count);
}

// Get Trace Status (clear Error flags)
//   return: Trace Status (Active flag and Error flags)
static uint8_t GetTraceStatus (void) {
  uint8_t  status;
  uint32_t n;

  n = TraceError_n;
  TraceError_n ^= 1U;
  status = TraceStatus | TraceError[n];
  TraceError[n] = 0U;

  return (status);
}

// Set Trace Error flag(s)
//   flag:  error flag(s) to set
static void SetTraceError (uint8_t flag) {
  TraceError[TraceError_n] |= flag;
}


// Process SWO Transport command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t SWO_Transport (const uint8_t *request, uint8_t *response) {
  uint8_t  transport;
  uint32_t result;

  if ((TraceStatus & DAP_SWO_CAPTURE_ACTIVE) == 0U) {
    transport = *request;
    switch (transport) {
      case 0U:
      case 1U:
#if (SWO_STREAM != 0)
      case 2U:
#endif
        TraceTransport = transport;
        result = 1U;
        break;
      default:
        result = 0U;
        break;
    }
  } else {
    result = 0U;
  }

  if (result != 0U) {
    *response = DAP_OK;
  } else {
    *response = DAP_ERROR;
  }

  return ((1U << 16) | 1U);
}


// Process SWO Mode command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t SWO_Mode (const uint8_t *request, uint8_t *response) {
  uint8_t  mode;
  uint32_t result;

  mode = *request;

  switch (TraceMode) {
#if (SWO_UART != 0)
    case DAP_SWO_UART:
      SWO_Mode_UART(0U);
      break;
#endif
#if (SWO_MANCHESTER != 0)
    case DAP_SWO_MANCHESTER:
      SWO_Mode_Manchester(0U);
      break;
#endif
    default:
      break;
  }

  switch (mode) {
    case DAP_SWO_OFF:
      result = 1U;
      break;
#if (SWO_UART != 0)
    case DAP_SWO_UART:
      result = SWO_Mode_UART(1U);
      break;
#endif
#if (SWO_MANCHESTER != 0)
    case DAP_SWO_MANCHESTER:
      result = SWO_Mode_Manchester(1U);
      break;
#endif
    default:
      result = 0U;
      break;
  }
  if (result != 0U) {
    TraceMode = mode;
  } else {
    TraceMode = DAP_SWO_OFF;
  }

  TraceStatus = 0U;

  if (result != 0U) {
    *response = DAP_OK;
  } else {
    *response = DAP_ERROR;
  }

  return ((1U << 16) | 1U);
}


// Process SWO Baudrate command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t SWO_Baudrate (const uint8_t *request, uint8_t *response) {
  uint32_t baudrate;

  baudrate = (uint32_t)(*(request+0) <<  0) |
             (uint32_t)(*(request+1) <<  8) |
             (uint32_t)(*(request+2) << 16) |
             (uint32_t)(*(request+3) << 24);

  switch (TraceMode) {
#if (SWO_UART != 0)
    case DAP_SWO_UART:
      baudrate = SWO_Baudrate_UART(baudrate);
      break;
#endif
#if (SWO_MANCHESTER != 0)
    case DAP_SWO_MANCHESTER:
      baudrate = SWO_Baudrate_Manchester(baudrate);
      break;
#endif
    default:
      baudrate = 0U;
      break;
  }

  if (baudrate == 0U) {
    TraceStatus = 0U;
  }

  *response++ = (uint8_t)(baudrate >>  0);
  *response++ = (uint8_t)(baudrate >>  8);
  *response++ = (uint8_t)(baudrate >> 16);
  *response   = (uint8_t)(baudrate >> 24);

  return ((4U << 16) | 4U);
}


// Process SWO Control command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t SWO_Control (const uint8_t *request, uint8_t *response) {
  uint8_t  active;
  uint32_t result;

  active = *request & DAP_SWO_CAPTURE_ACTIVE;

  if (active != (TraceStatus & DAP_SWO_CAPTURE_ACTIVE)) {
    if (active) {
      ClearTrace();
    }
    switch (TraceMode) {
#if (SWO_UART != 0)
      case DAP_SWO_UART:
        result = SWO_Control_UART(active);
        break;
#endif
#if (SWO_MANCHESTER != 0)
      case DAP_SWO_MANCHESTER:
        result = SWO_Control_Manchester(active);
        break;
#endif
      default:
        result = 0U;
        break;
    }
    if (result != 0U) {
      TraceStatus = active;
#if (SWO_STREAM != 0)
      if (TraceTransport == 2U) {
        osThreadFlagsSet(SWO_ThreadId, 1U);
      }
#endif
    }
  } else {
    result = 1U;
  }

  if (result != 0U) {
    *response = DAP_OK;
  } else {
    *response = DAP_ERROR;
  }

  return ((1U << 16) | 1U);
}


// Process SWO Status command and prepare response
//   response: pointer to response data
//   return:   number of bytes in response
uint32_t SWO_Status (uint8_t *response) {
  uint8_t  status;
  uint32_t count;

  status = GetTraceStatus();
  count  = GetTraceCount();

  *response++ = status;
  *response++ = (uint8_t)(count >>  0);
  *response++ = (uint8_t)(count >>  8);
  *response++ = (uint8_t)(count >> 16);
  *response   = (uint8_t)(count >> 24);

  return (5U);
}


// Process SWO Extended Status command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t SWO_ExtendedStatus (const uint8_t *request, uint8_t *response) {
  uint8_t  cmd;
  uint8_t  status;
  uint32_t count;
#if (TIMESTAMP_CLOCK != 0U)
  uint32_t index;
  uint32_t tick;
#endif
  uint32_t num;

  num = 0U;
  cmd = *request;

  if (cmd & 0x01U) {
    status = GetTraceStatus();
    *response++ = status;
    num += 1U;
  }

  if (cmd & 0x02U) {
    count = GetTraceCount();
    *response++ = (uint8_t)(count >>  0);
    *response++ = (uint8_t)(count >>  8);
    *response++ = (uint8_t)(count >> 16);
    *response++ = (uint8_t)(count >> 24);
    num += 4U;
  }

#if (TIMESTAMP_CLOCK != 0U)
  if (cmd & 0x04U) {
    do {
      TraceUpdate = 0U;
      index = TraceTimestamp.index;
      tick  = TraceTimestamp.tick;
    } while (TraceUpdate != 0U);
    *response++ = (uint8_t)(index >>  0);
    *response++ = (uint8_t)(index >>  8);
    *response++ = (uint8_t)(index >> 16);
    *response++ = (uint8_t)(index >> 24);
    *response++ = (uint8_t)(tick  >>  0);
    *response++ = (uint8_t)(tick  >>  8);
    *response++ = (uint8_t)(tick  >> 16);
    *response++ = (uint8_t)(tick  >> 24);
    num += 4U;
  }
#endif

  return ((1U << 16) | num);
}


// Process SWO Data command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t SWO_Data (const uint8_t *request, uint8_t *response) {
  uint8_t  status;
  uint32_t count;
  uint32_t index;
  uint32_t n, i;

  status = GetTraceStatus();
  count  = GetTraceCount();

  if (TraceTransport == 1U) {
    n = (uint32_t)(*(request+0) << 0) |
        (uint32_t)(*(request+1) << 8);
    if (n > (DAP_PACKET_SIZE - 4U)) {
      n = DAP_PACKET_SIZE - 4U;
    }
    if (count > n) {
      count = n;
    }
  } else {
    count = 0U;
  }

  *response++ = status;
  *response++ = (uint8_t)(count >> 0);
  *response++ = (uint8_t)(count >> 8);

  if (TraceTransport == 1U) {
    index = TraceIndexO;
    for (i = index, n = count; n; n--) {
      i &= SWO_BUFFER_SIZE - 1U;
      *response++ = TraceBuf[i++];
    }
    TraceIndexO = index + count;
    ResumeTrace();
  }

  return ((2U << 16) | (3U + count));
}


#if (SWO_STREAM != 0)

// SWO Data Transfer complete callback
void SWO_TransferComplete (void) {
  TraceIndexO += TransferSize;
  TransferBusy = 0U;
  ResumeTrace();
  osThreadFlagsSet(SWO_ThreadId, 1U);
}

// SWO Thread
__NO_RETURN void SWO_Thread (void *argument) {
  uint32_t timeout;
  uint32_t flags;
  uint32_t count;
  uint32_t index;
  uint32_t i, n;
  (void)   argument;

  timeout = osWaitForever;

  for (;;) {
    flags = osThreadFlagsWait(1U, osFlagsWaitAny, timeout);
    if (TraceStatus & DAP_SWO_CAPTURE_ACTIVE) {
      timeout = SWO_STREAM_TIMEOUT;
    } else {
      timeout = osWaitForever;
      flags   = osFlagsErrorTimeout;
    }
    if (TransferBusy == 0U) {
      count = GetTraceCount();
      if (count != 0U) {
        index = TraceIndexO & (SWO_BUFFER_SIZE - 1U);
        n = SWO_BUFFER_SIZE - index;
        if (count > n) {
          count = n;
        }
        if (flags != osFlagsErrorTimeout) {
          i = index & (USB_BLOCK_SIZE - 1U);
          if (i == 0U) {
            count &= ~(USB_BLOCK_SIZE - 1U);
          } else {
            n = USB_BLOCK_SIZE - i;
            if (count >= n) {
              count = n;
            } else {
              count = 0U;
            }
          }
        }
        if (count != 0U) {
          TransferSize = count;
          TransferBusy = 1U;
          SWO_QueueTransfer(&TraceBuf[index], count);
        }
      }
    }
  }
}

#endif  /* (SWO_STREAM != 0) */


#endif  /* ((SWO_UART != 0) || (SWO_MANCHESTER != 0)) */
