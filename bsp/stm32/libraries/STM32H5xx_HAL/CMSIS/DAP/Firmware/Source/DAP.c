/*
 * Copyright (c) 2013-2022 ARM Limited. All rights reserved.
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
 * $Date:        26. April 2022
 * $Revision:    V2.1.1
 *
 * Project:      CMSIS-DAP Source
 * Title:        DAP.c CMSIS-DAP Commands
 *
 *---------------------------------------------------------------------------*/

#include <string.h>
#include "DAP_config.h"
#include "DAP.h"


#if (DAP_PACKET_SIZE < 64U)
#error "Minimum Packet Size is 64!"
#endif
#if (DAP_PACKET_SIZE > 32768U)
#error "Maximum Packet Size is 32768!"
#endif
#if (DAP_PACKET_COUNT < 1U)
#error "Minimum Packet Count is 1!"
#endif
#if (DAP_PACKET_COUNT > 255U)
#error "Maximum Packet Count is 255!"
#endif


// Clock Macros
#define MAX_SWJ_CLOCK(delay_cycles) \
  ((CPU_CLOCK/2U) / (IO_PORT_WRITE_CYCLES + delay_cycles))


         DAP_Data_t DAP_Data;           // DAP Data
volatile uint8_t    DAP_TransferAbort;  // Transfer Abort Flag


static const char DAP_FW_Ver [] = DAP_FW_VER;


// Common clock delay calculation routine
//   clock:    requested SWJ frequency in Hertz
static void Set_Clock_Delay(uint32_t clock) {
  uint32_t delay;

  if (clock >= MAX_SWJ_CLOCK(DELAY_FAST_CYCLES)) {
    DAP_Data.fast_clock  = 1U;
    DAP_Data.clock_delay = 1U;
  } else {
    DAP_Data.fast_clock  = 0U;

    delay = ((CPU_CLOCK/2U) + (clock - 1U)) / clock;
    if (delay > IO_PORT_WRITE_CYCLES) {
      delay -= IO_PORT_WRITE_CYCLES;
      delay  = (delay + (DELAY_SLOW_CYCLES - 1U)) / DELAY_SLOW_CYCLES;
    } else {
      delay  = 1U;
    }

    DAP_Data.clock_delay = delay;
  }
}


// Get DAP Information
//   id:      info identifier
//   info:    pointer to info data
//   return:  number of bytes in info data
static uint8_t DAP_Info(uint8_t id, uint8_t *info) {
  uint8_t length = 0U;

  switch (id) {
    case DAP_ID_VENDOR:
      length = DAP_GetVendorString((char *)info);
      break;
    case DAP_ID_PRODUCT:
      length = DAP_GetProductString((char *)info);
      break;
    case DAP_ID_SER_NUM:
      length = DAP_GetSerNumString((char *)info);
      break;
    case DAP_ID_DAP_FW_VER:
      length = (uint8_t)sizeof(DAP_FW_Ver);
      memcpy(info, DAP_FW_Ver, length);
      break;
    case DAP_ID_DEVICE_VENDOR:
      length = DAP_GetTargetDeviceVendorString((char *)info);
      break;
    case DAP_ID_DEVICE_NAME:
      length = DAP_GetTargetDeviceNameString((char *)info);
      break;
    case DAP_ID_BOARD_VENDOR:
      length = DAP_GetTargetBoardVendorString((char *)info);
      break;
    case DAP_ID_BOARD_NAME:
      length = DAP_GetTargetBoardNameString((char *)info);
      break;
    case DAP_ID_PRODUCT_FW_VER:
      length = DAP_GetProductFirmwareVersionString((char *)info);
      break;
    case DAP_ID_CAPABILITIES:
      info[0] = ((DAP_SWD  != 0)         ? (1U << 0) : 0U) |
                ((DAP_JTAG != 0)         ? (1U << 1) : 0U) |
                ((SWO_UART != 0)         ? (1U << 2) : 0U) |
                ((SWO_MANCHESTER != 0)   ? (1U << 3) : 0U) |
                /* Atomic Commands  */     (1U << 4)       |
                ((TIMESTAMP_CLOCK != 0U) ? (1U << 5) : 0U) |
                ((SWO_STREAM != 0U)      ? (1U << 6) : 0U) |
                ((DAP_UART != 0U)        ? (1U << 7) : 0U);

      info[1] = ((DAP_UART_USB_COM_PORT != 0) ? (1U << 0) : 0U);
      length = 2U;
      break;
    case DAP_ID_TIMESTAMP_CLOCK:
#if (TIMESTAMP_CLOCK != 0U)
      info[0] = (uint8_t)(TIMESTAMP_CLOCK >>  0);
      info[1] = (uint8_t)(TIMESTAMP_CLOCK >>  8);
      info[2] = (uint8_t)(TIMESTAMP_CLOCK >> 16);
      info[3] = (uint8_t)(TIMESTAMP_CLOCK >> 24);
      length = 4U;
#endif
      break;
    case DAP_ID_UART_RX_BUFFER_SIZE:
#if (DAP_UART != 0)
      info[0] = (uint8_t)(DAP_UART_RX_BUFFER_SIZE >>  0);
      info[1] = (uint8_t)(DAP_UART_RX_BUFFER_SIZE >>  8);
      info[2] = (uint8_t)(DAP_UART_RX_BUFFER_SIZE >> 16);
      info[3] = (uint8_t)(DAP_UART_RX_BUFFER_SIZE >> 24);
      length = 4U;
#endif
      break;
    case DAP_ID_UART_TX_BUFFER_SIZE:
#if (DAP_UART != 0)
      info[0] = (uint8_t)(DAP_UART_TX_BUFFER_SIZE >>  0);
      info[1] = (uint8_t)(DAP_UART_TX_BUFFER_SIZE >>  8);
      info[2] = (uint8_t)(DAP_UART_TX_BUFFER_SIZE >> 16);
      info[3] = (uint8_t)(DAP_UART_TX_BUFFER_SIZE >> 24);
      length = 4U;
#endif
      break;
    case DAP_ID_SWO_BUFFER_SIZE:
#if ((SWO_UART != 0) || (SWO_MANCHESTER != 0))
      info[0] = (uint8_t)(SWO_BUFFER_SIZE >>  0);
      info[1] = (uint8_t)(SWO_BUFFER_SIZE >>  8);
      info[2] = (uint8_t)(SWO_BUFFER_SIZE >> 16);
      info[3] = (uint8_t)(SWO_BUFFER_SIZE >> 24);
      length = 4U;
#endif
      break;
    case DAP_ID_PACKET_SIZE:
      info[0] = (uint8_t)(DAP_PACKET_SIZE >> 0);
      info[1] = (uint8_t)(DAP_PACKET_SIZE >> 8);
      length = 2U;
      break;
    case DAP_ID_PACKET_COUNT:
      info[0] = DAP_PACKET_COUNT;
      length = 1U;
      break;
    default:
      break;
  }

  return (length);
}


// Delay for specified time
//    delay:  delay time in ms
void Delayms(uint32_t delay) {
  delay *= ((CPU_CLOCK/1000U) + (DELAY_SLOW_CYCLES-1U)) / DELAY_SLOW_CYCLES;
  PIN_DELAY_SLOW(delay);
}


// Process Delay command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_Delay(const uint8_t *request, uint8_t *response) {
  uint32_t delay;

  delay  = (uint32_t)(*(request+0)) |
           (uint32_t)(*(request+1) << 8);
  delay *= ((CPU_CLOCK/1000000U) + (DELAY_SLOW_CYCLES-1U)) / DELAY_SLOW_CYCLES;

  PIN_DELAY_SLOW(delay);

  *response = DAP_OK;
  return ((2U << 16) | 1U);
}


// Process Host Status command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_HostStatus(const uint8_t *request, uint8_t *response) {

  switch (*request) {
    case DAP_DEBUGGER_CONNECTED:
      LED_CONNECTED_OUT((*(request+1) & 1U));
      break;
    case DAP_TARGET_RUNNING:
      LED_RUNNING_OUT((*(request+1) & 1U));
      break;
    default:
      *response = DAP_ERROR;
      return ((2U << 16) | 1U);
  }

  *response = DAP_OK;
  return ((2U << 16) | 1U);
}


// Process Connect command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_Connect(const uint8_t *request, uint8_t *response) {
  uint32_t port;

  if (*request == DAP_PORT_AUTODETECT) {
    port = DAP_DEFAULT_PORT;
  } else {
    port = *request;
  }

  switch (port) {
#if (DAP_SWD != 0)
    case DAP_PORT_SWD:
      DAP_Data.debug_port = DAP_PORT_SWD;
      PORT_SWD_SETUP();
      break;
#endif
#if (DAP_JTAG != 0)
    case DAP_PORT_JTAG:
      DAP_Data.debug_port = DAP_PORT_JTAG;
      PORT_JTAG_SETUP();
      break;
#endif
    default:
      port = DAP_PORT_DISABLED;
      break;
  }

  *response = (uint8_t)port;
  return ((1U << 16) | 1U);
}


// Process Disconnect command and prepare response
//   response: pointer to response data
//   return:   number of bytes in response
static uint32_t DAP_Disconnect(uint8_t *response) {

  DAP_Data.debug_port = DAP_PORT_DISABLED;
  PORT_OFF();

  *response = DAP_OK;
  return (1U);
}


// Process Reset Target command and prepare response
//   response: pointer to response data
//   return:   number of bytes in response
static uint32_t DAP_ResetTarget(uint8_t *response) {

  *(response+1) = RESET_TARGET();
  *(response+0) = DAP_OK;
  return (2U);
}


// Process SWJ Pins command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_SWJ_Pins(const uint8_t *request, uint8_t *response) {
#if ((DAP_SWD != 0) || (DAP_JTAG != 0))
  uint32_t value;
  uint32_t select;
  uint32_t wait;
  uint32_t timestamp;

  value  = (uint32_t) *(request+0);
  select = (uint32_t) *(request+1);
  wait   = (uint32_t)(*(request+2) <<  0) |
           (uint32_t)(*(request+3) <<  8) |
           (uint32_t)(*(request+4) << 16) |
           (uint32_t)(*(request+5) << 24);

  if ((select & (1U << DAP_SWJ_SWCLK_TCK)) != 0U) {
    if ((value & (1U << DAP_SWJ_SWCLK_TCK)) != 0U) {
      PIN_SWCLK_TCK_SET();
    } else {
      PIN_SWCLK_TCK_CLR();
    }
  }
  if ((select & (1U << DAP_SWJ_SWDIO_TMS)) != 0U) {
    if ((value & (1U << DAP_SWJ_SWDIO_TMS)) != 0U) {
      PIN_SWDIO_TMS_SET();
    } else {
      PIN_SWDIO_TMS_CLR();
    }
  }
  if ((select & (1U << DAP_SWJ_TDI)) != 0U) {
    PIN_TDI_OUT(value >> DAP_SWJ_TDI);
  }
  if ((select & (1U << DAP_SWJ_nTRST)) != 0U) {
    PIN_nTRST_OUT(value >> DAP_SWJ_nTRST);
  }
  if ((select & (1U << DAP_SWJ_nRESET)) != 0U){
    PIN_nRESET_OUT(value >> DAP_SWJ_nRESET);
  }

  if (wait != 0U) {
#if (TIMESTAMP_CLOCK != 0U)
    if (wait > 3000000U) {
      wait = 3000000U;
    }
#if (TIMESTAMP_CLOCK >= 1000000U)
    wait *= TIMESTAMP_CLOCK / 1000000U;
#else
    wait /= 1000000U / TIMESTAMP_CLOCK;
#endif
#else
    wait  = 1U;
#endif
    timestamp = TIMESTAMP_GET();
    do {
      if ((select & (1U << DAP_SWJ_SWCLK_TCK)) != 0U) {
        if ((value >> DAP_SWJ_SWCLK_TCK) ^ PIN_SWCLK_TCK_IN()) {
          continue;
        }
      }
      if ((select & (1U << DAP_SWJ_SWDIO_TMS)) != 0U) {
        if ((value >> DAP_SWJ_SWDIO_TMS) ^ PIN_SWDIO_TMS_IN()) {
          continue;
        }
      }
      if ((select & (1U << DAP_SWJ_TDI)) != 0U) {
        if ((value >> DAP_SWJ_TDI) ^ PIN_TDI_IN()) {
          continue;
        }
      }
      if ((select & (1U << DAP_SWJ_nTRST)) != 0U) {
        if ((value >> DAP_SWJ_nTRST) ^ PIN_nTRST_IN()) {
          continue;
        }
      }
      if ((select & (1U << DAP_SWJ_nRESET)) != 0U) {
        if ((value >> DAP_SWJ_nRESET) ^ PIN_nRESET_IN()) {
          continue;
        }
      }
      break;
    } while ((TIMESTAMP_GET() - timestamp) < wait);
  }

  value = (PIN_SWCLK_TCK_IN() << DAP_SWJ_SWCLK_TCK) |
          (PIN_SWDIO_TMS_IN() << DAP_SWJ_SWDIO_TMS) |
          (PIN_TDI_IN()       << DAP_SWJ_TDI)       |
          (PIN_TDO_IN()       << DAP_SWJ_TDO)       |
          (PIN_nTRST_IN()     << DAP_SWJ_nTRST)     |
          (PIN_nRESET_IN()    << DAP_SWJ_nRESET);

  *response = (uint8_t)value;
#else
  *response = 0U;
#endif

  return ((6U << 16) | 1U);
}


// Process SWJ Clock command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_SWJ_Clock(const uint8_t *request, uint8_t *response) {
#if ((DAP_SWD != 0) || (DAP_JTAG != 0))
  uint32_t clock;
  uint32_t delay;

  clock = (uint32_t)(*(request+0) <<  0) |
          (uint32_t)(*(request+1) <<  8) |
          (uint32_t)(*(request+2) << 16) |
          (uint32_t)(*(request+3) << 24);

  if (clock == 0U) {
    *response = DAP_ERROR;
    return ((4U << 16) | 1U);
  }

  Set_Clock_Delay(clock);

  *response = DAP_OK;
#else
  *response = DAP_ERROR;
#endif

  return ((4U << 16) | 1U);
}


// Process SWJ Sequence command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_SWJ_Sequence(const uint8_t *request, uint8_t *response) {
  uint32_t count;

  count = *request++;
  if (count == 0U) {
    count = 256U;
  }

#if ((DAP_SWD != 0) || (DAP_JTAG != 0))
  SWJ_Sequence(count, request);
  *response = DAP_OK;
#else
  *response = DAP_ERROR;
#endif

  count = (count + 7U) >> 3;

  return (((count + 1U) << 16) | 1U);
}


// Process SWD Configure command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_SWD_Configure(const uint8_t *request, uint8_t *response) {
#if (DAP_SWD != 0)
  uint8_t value;

  value = *request;
  DAP_Data.swd_conf.turnaround = (value & 0x03U) + 1U;
  DAP_Data.swd_conf.data_phase = (value & 0x04U) ? 1U : 0U;

  *response = DAP_OK;
#else
  *response = DAP_ERROR;
#endif

  return ((1U << 16) | 1U);
}


// Process SWD Sequence command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_SWD_Sequence(const uint8_t *request, uint8_t *response) {
  uint32_t sequence_info;
  uint32_t sequence_count;
  uint32_t request_count;
  uint32_t response_count;
  uint32_t count;

#if (DAP_SWD != 0)
  *response++ = DAP_OK;
#else
  *response++ = DAP_ERROR;
#endif
  request_count  = 1U;
  response_count = 1U;

  sequence_count = *request++;
  while (sequence_count--) {
    sequence_info = *request++;
    count = sequence_info & SWD_SEQUENCE_CLK;
    if (count == 0U) {
      count = 64U;
    }
    count = (count + 7U) / 8U;
#if (DAP_SWD != 0)
    if ((sequence_info & SWD_SEQUENCE_DIN) != 0U) {
      PIN_SWDIO_OUT_DISABLE();
    } else {
      PIN_SWDIO_OUT_ENABLE();
    }
    SWD_Sequence(sequence_info, request, response);
    if (sequence_count == 0U) {
      PIN_SWDIO_OUT_ENABLE();
    }
#endif
    if ((sequence_info & SWD_SEQUENCE_DIN) != 0U) {
      request_count++;
#if (DAP_SWD != 0)
      response += count;
      response_count += count;
#endif
    } else {
      request += count;
      request_count += count + 1U;
    }
  }

  return ((request_count << 16) | response_count);
}


// Process JTAG Sequence command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_JTAG_Sequence(const uint8_t *request, uint8_t *response) {
  uint32_t sequence_info;
  uint32_t sequence_count;
  uint32_t request_count;
  uint32_t response_count;
  uint32_t count;

#if (DAP_JTAG != 0)
  *response++ = DAP_OK;
#else
  *response++ = DAP_ERROR;
#endif
  request_count  = 1U;
  response_count = 1U;

  sequence_count = *request++;
  while (sequence_count--) {
    sequence_info = *request++;
    count = sequence_info & JTAG_SEQUENCE_TCK;
    if (count == 0U) {
      count = 64U;
    }
    count = (count + 7U) / 8U;
#if (DAP_JTAG != 0)
    JTAG_Sequence(sequence_info, request, response);
#endif
    request += count;
    request_count += count + 1U;
#if (DAP_JTAG != 0)
    if ((sequence_info & JTAG_SEQUENCE_TDO) != 0U) {
      response += count;
      response_count += count;
    }
#endif
  }

  return ((request_count << 16) | response_count);
}


// Process JTAG Configure command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_JTAG_Configure(const uint8_t *request, uint8_t *response) {
  uint32_t count;
#if (DAP_JTAG != 0)
  uint32_t length;
  uint32_t bits;
  uint32_t n;

  count = *request++;
  DAP_Data.jtag_dev.count = (uint8_t)count;

  bits = 0U;
  for (n = 0U; n < count; n++) {
    length = *request++;
    DAP_Data.jtag_dev.ir_length[n] =  (uint8_t)length;
    DAP_Data.jtag_dev.ir_before[n] = (uint16_t)bits;
    bits += length;
  }
  for (n = 0U; n < count; n++) {
    bits -= DAP_Data.jtag_dev.ir_length[n];
    DAP_Data.jtag_dev.ir_after[n] = (uint16_t)bits;
  }

  *response = DAP_OK;
#else
  count = *request;
  *response = DAP_ERROR;
#endif

  return (((count + 1U) << 16) | 1U);
}


// Process JTAG IDCODE command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_JTAG_IDCode(const uint8_t *request, uint8_t *response) {
#if (DAP_JTAG != 0)
  uint32_t data;

  if (DAP_Data.debug_port != DAP_PORT_JTAG) {
    goto id_error;
  }

  // Device index (JTAP TAP)
  DAP_Data.jtag_dev.index = *request;
  if (DAP_Data.jtag_dev.index >= DAP_Data.jtag_dev.count) {
    goto id_error;
  }

  // Select JTAG chain
  JTAG_IR(JTAG_IDCODE);

  // Read IDCODE register
  data = JTAG_ReadIDCode();

  // Store Data
  *(response+0) =  DAP_OK;
  *(response+1) = (uint8_t)(data >>  0);
  *(response+2) = (uint8_t)(data >>  8);
  *(response+3) = (uint8_t)(data >> 16);
  *(response+4) = (uint8_t)(data >> 24);

  return ((1U << 16) | 5U);

id_error:
#endif
  *response = DAP_ERROR;
  return ((1U << 16) | 1U);
}


// Process Transfer Configure command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_TransferConfigure(const uint8_t *request, uint8_t *response) {

  DAP_Data.transfer.idle_cycles =            *(request+0);
  DAP_Data.transfer.retry_count = (uint16_t) *(request+1) |
                                  (uint16_t)(*(request+2) << 8);
  DAP_Data.transfer.match_retry = (uint16_t) *(request+3) |
                                  (uint16_t)(*(request+4) << 8);

  *response = DAP_OK;
  return ((5U << 16) | 1U);
}


// Process SWD Transfer command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
#if (DAP_SWD != 0)
static uint32_t DAP_SWD_Transfer(const uint8_t *request, uint8_t *response) {
  const
  uint8_t  *request_head;
  uint32_t  request_count;
  uint32_t  request_value;
  uint8_t  *response_head;
  uint32_t  response_count;
  uint32_t  response_value;
  uint32_t  post_read;
  uint32_t  check_write;
  uint32_t  match_value;
  uint32_t  match_retry;
  uint32_t  retry;
  uint32_t  data;
#if (TIMESTAMP_CLOCK != 0U)
  uint32_t  timestamp;
#endif

  request_head   = request;

  response_count = 0U;
  response_value = 0U;
  response_head  = response;
  response      += 2;

  DAP_TransferAbort = 0U;

  post_read   = 0U;
  check_write = 0U;

  request++;            // Ignore DAP index

  request_count = *request++;

  for (; request_count != 0U; request_count--) {
    request_value = *request++;
    if ((request_value & DAP_TRANSFER_RnW) != 0U) {
      // Read register
      if (post_read) {
        // Read was posted before
        retry = DAP_Data.transfer.retry_count;
        if ((request_value & (DAP_TRANSFER_APnDP | DAP_TRANSFER_MATCH_VALUE)) == DAP_TRANSFER_APnDP) {
          // Read previous AP data and post next AP read
          do {
            response_value = SWD_Transfer(request_value, &data);
          } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
        } else {
          // Read previous AP data
          do {
            response_value = SWD_Transfer(DP_RDBUFF | DAP_TRANSFER_RnW, &data);
          } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
          post_read = 0U;
        }
        if (response_value != DAP_TRANSFER_OK) {
          break;
        }
        // Store previous AP data
        *response++ = (uint8_t) data;
        *response++ = (uint8_t)(data >>  8);
        *response++ = (uint8_t)(data >> 16);
        *response++ = (uint8_t)(data >> 24);
#if (TIMESTAMP_CLOCK != 0U)
        if (post_read) {
          // Store Timestamp of next AP read
          if ((request_value & DAP_TRANSFER_TIMESTAMP) != 0U) {
            timestamp = DAP_Data.timestamp;
            *response++ = (uint8_t) timestamp;
            *response++ = (uint8_t)(timestamp >>  8);
            *response++ = (uint8_t)(timestamp >> 16);
            *response++ = (uint8_t)(timestamp >> 24);
          }
        }
#endif
      }
      if ((request_value & DAP_TRANSFER_MATCH_VALUE) != 0U) {
        // Read with value match
        match_value = (uint32_t)(*(request+0) <<  0) |
                      (uint32_t)(*(request+1) <<  8) |
                      (uint32_t)(*(request+2) << 16) |
                      (uint32_t)(*(request+3) << 24);
        request += 4;
        match_retry = DAP_Data.transfer.match_retry;
        if ((request_value & DAP_TRANSFER_APnDP) != 0U) {
          // Post AP read
          retry = DAP_Data.transfer.retry_count;
          do {
            response_value = SWD_Transfer(request_value, NULL);
          } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
          if (response_value != DAP_TRANSFER_OK) {
            break;
          }
        }
        do {
          // Read register until its value matches or retry counter expires
          retry = DAP_Data.transfer.retry_count;
          do {
            response_value = SWD_Transfer(request_value, &data);
          } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
          if (response_value != DAP_TRANSFER_OK) {
            break;
          }
        } while (((data & DAP_Data.transfer.match_mask) != match_value) && match_retry-- && !DAP_TransferAbort);
        if ((data & DAP_Data.transfer.match_mask) != match_value) {
          response_value |= DAP_TRANSFER_MISMATCH;
        }
        if (response_value != DAP_TRANSFER_OK) {
          break;
        }
      } else {
        // Normal read
        retry = DAP_Data.transfer.retry_count;
        if ((request_value & DAP_TRANSFER_APnDP) != 0U) {
          // Read AP register
          if (post_read == 0U) {
            // Post AP read
            do {
              response_value = SWD_Transfer(request_value, NULL);
            } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
            if (response_value != DAP_TRANSFER_OK) {
              break;
            }
#if (TIMESTAMP_CLOCK != 0U)
            // Store Timestamp
            if ((request_value & DAP_TRANSFER_TIMESTAMP) != 0U) {
              timestamp = DAP_Data.timestamp;
              *response++ = (uint8_t) timestamp;
              *response++ = (uint8_t)(timestamp >>  8);
              *response++ = (uint8_t)(timestamp >> 16);
              *response++ = (uint8_t)(timestamp >> 24);
            }
#endif
            post_read = 1U;
          }
        } else {
          // Read DP register
          do {
            response_value = SWD_Transfer(request_value, &data);
          } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
          if (response_value != DAP_TRANSFER_OK) {
            break;
          }
#if (TIMESTAMP_CLOCK != 0U)
          // Store Timestamp
          if ((request_value & DAP_TRANSFER_TIMESTAMP) != 0U) {
            timestamp = DAP_Data.timestamp;
            *response++ = (uint8_t) timestamp;
            *response++ = (uint8_t)(timestamp >>  8);
            *response++ = (uint8_t)(timestamp >> 16);
            *response++ = (uint8_t)(timestamp >> 24);
          }
#endif
          // Store data
          *response++ = (uint8_t) data;
          *response++ = (uint8_t)(data >>  8);
          *response++ = (uint8_t)(data >> 16);
          *response++ = (uint8_t)(data >> 24);
        }
      }
      check_write = 0U;
    } else {
      // Write register
      if (post_read) {
        // Read previous data
        retry = DAP_Data.transfer.retry_count;
        do {
          response_value = SWD_Transfer(DP_RDBUFF | DAP_TRANSFER_RnW, &data);
        } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
        if (response_value != DAP_TRANSFER_OK) {
          break;
        }
        // Store previous data
        *response++ = (uint8_t) data;
        *response++ = (uint8_t)(data >>  8);
        *response++ = (uint8_t)(data >> 16);
        *response++ = (uint8_t)(data >> 24);
        post_read = 0U;
      }
      // Load data
      data = (uint32_t)(*(request+0) <<  0) |
             (uint32_t)(*(request+1) <<  8) |
             (uint32_t)(*(request+2) << 16) |
             (uint32_t)(*(request+3) << 24);
      request += 4;
      if ((request_value & DAP_TRANSFER_MATCH_MASK) != 0U) {
        // Write match mask
        DAP_Data.transfer.match_mask = data;
        response_value = DAP_TRANSFER_OK;
      } else {
        // Write DP/AP register
        retry = DAP_Data.transfer.retry_count;
        do {
          response_value = SWD_Transfer(request_value, &data);
        } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
        if (response_value != DAP_TRANSFER_OK) {
          break;
        }
#if (TIMESTAMP_CLOCK != 0U)
        // Store Timestamp
        if ((request_value & DAP_TRANSFER_TIMESTAMP) != 0U) {
          timestamp = DAP_Data.timestamp;
          *response++ = (uint8_t) timestamp;
          *response++ = (uint8_t)(timestamp >>  8);
          *response++ = (uint8_t)(timestamp >> 16);
          *response++ = (uint8_t)(timestamp >> 24);
        }
#endif
        check_write = 1U;
      }
    }
    response_count++;
    if (DAP_TransferAbort) {
      break;
    }
  }

  for (; request_count != 0U; request_count--) {
    // Process canceled requests
    request_value = *request++;
    if ((request_value & DAP_TRANSFER_RnW) != 0U) {
      // Read register
      if ((request_value & DAP_TRANSFER_MATCH_VALUE) != 0U) {
        // Read with value match
        request += 4;
      }
    } else {
      // Write register
      request += 4;
    }
  }

  if (response_value == DAP_TRANSFER_OK) {
    if (post_read) {
      // Read previous data
      retry = DAP_Data.transfer.retry_count;
      do {
        response_value = SWD_Transfer(DP_RDBUFF | DAP_TRANSFER_RnW, &data);
      } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
      if (response_value != DAP_TRANSFER_OK) {
        goto end;
      }
      // Store previous data
      *response++ = (uint8_t) data;
      *response++ = (uint8_t)(data >>  8);
      *response++ = (uint8_t)(data >> 16);
      *response++ = (uint8_t)(data >> 24);
    } else if (check_write) {
      // Check last write
      retry = DAP_Data.transfer.retry_count;
      do {
        response_value = SWD_Transfer(DP_RDBUFF | DAP_TRANSFER_RnW, NULL);
      } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
    }
  }

end:
  *(response_head+0) = (uint8_t)response_count;
  *(response_head+1) = (uint8_t)response_value;

  return (((uint32_t)(request - request_head) << 16) | (uint32_t)(response - response_head));
}
#endif


// Process JTAG Transfer command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
#if (DAP_JTAG != 0)
static uint32_t DAP_JTAG_Transfer(const uint8_t *request, uint8_t *response) {
  const
  uint8_t  *request_head;
  uint32_t  request_count;
  uint32_t  request_value;
  uint32_t  request_ir;
  uint8_t  *response_head;
  uint32_t  response_count;
  uint32_t  response_value;
  uint32_t  post_read;
  uint32_t  match_value;
  uint32_t  match_retry;
  uint32_t  retry;
  uint32_t  data;
  uint32_t  ir;
#if (TIMESTAMP_CLOCK != 0U)
  uint32_t  timestamp;
#endif

  request_head   = request;

  response_count = 0U;
  response_value = 0U;
  response_head  = response;
  response      += 2;

  DAP_TransferAbort = 0U;

  ir        = 0U;
  post_read = 0U;

  // Device index (JTAP TAP)
  DAP_Data.jtag_dev.index = *request++;
  if (DAP_Data.jtag_dev.index >= DAP_Data.jtag_dev.count) {
    goto end;
  }

  request_count = *request++;

  for (; request_count != 0U; request_count--) {
    request_value = *request++;
    request_ir = (request_value & DAP_TRANSFER_APnDP) ? JTAG_APACC : JTAG_DPACC;
    if ((request_value & DAP_TRANSFER_RnW) != 0U) {
      // Read register
      if (post_read) {
        // Read was posted before
        retry = DAP_Data.transfer.retry_count;
        if ((ir == request_ir) && ((request_value & DAP_TRANSFER_MATCH_VALUE) == 0U)) {
          // Read previous data and post next read
          do {
            response_value = JTAG_Transfer(request_value, &data);
          } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
        } else {
          // Select JTAG chain
          if (ir != JTAG_DPACC) {
            ir = JTAG_DPACC;
            JTAG_IR(ir);
          }
          // Read previous data
          do {
            response_value = JTAG_Transfer(DP_RDBUFF | DAP_TRANSFER_RnW, &data);
          } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
          post_read = 0U;
        }
        if (response_value != DAP_TRANSFER_OK) {
          break;
        }
        // Store previous data
        *response++ = (uint8_t) data;
        *response++ = (uint8_t)(data >>  8);
        *response++ = (uint8_t)(data >> 16);
        *response++ = (uint8_t)(data >> 24);
#if (TIMESTAMP_CLOCK != 0U)
        if (post_read) {
          // Store Timestamp of next AP read
          if ((request_value & DAP_TRANSFER_TIMESTAMP) != 0U) {
            timestamp = DAP_Data.timestamp;
            *response++ = (uint8_t) timestamp;
            *response++ = (uint8_t)(timestamp >>  8);
            *response++ = (uint8_t)(timestamp >> 16);
            *response++ = (uint8_t)(timestamp >> 24);
          }
        }
#endif
      }
      if ((request_value & DAP_TRANSFER_MATCH_VALUE) != 0U) {
        // Read with value match
        match_value = (uint32_t)(*(request+0) <<  0) |
                      (uint32_t)(*(request+1) <<  8) |
                      (uint32_t)(*(request+2) << 16) |
                      (uint32_t)(*(request+3) << 24);
        request += 4;
        match_retry  = DAP_Data.transfer.match_retry;
        // Select JTAG chain
        if (ir != request_ir) {
          ir = request_ir;
          JTAG_IR(ir);
        }
        // Post DP/AP read
        retry = DAP_Data.transfer.retry_count;
        do {
          response_value = JTAG_Transfer(request_value, NULL);
        } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
        if (response_value != DAP_TRANSFER_OK) {
          break;
        }
        do {
          // Read register until its value matches or retry counter expires
          retry = DAP_Data.transfer.retry_count;
          do {
            response_value = JTAG_Transfer(request_value, &data);
          } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
          if (response_value != DAP_TRANSFER_OK) {
            break;
          }
        } while (((data & DAP_Data.transfer.match_mask) != match_value) && match_retry-- && !DAP_TransferAbort);
        if ((data & DAP_Data.transfer.match_mask) != match_value) {
          response_value |= DAP_TRANSFER_MISMATCH;
        }
        if (response_value != DAP_TRANSFER_OK) {
          break;
        }
      } else {
        // Normal read
        if (post_read == 0U) {
          // Select JTAG chain
          if (ir != request_ir) {
            ir = request_ir;
            JTAG_IR(ir);
          }
          // Post DP/AP read
          retry = DAP_Data.transfer.retry_count;
          do {
            response_value = JTAG_Transfer(request_value, NULL);
          } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
          if (response_value != DAP_TRANSFER_OK) {
            break;
          }
#if (TIMESTAMP_CLOCK != 0U)
          // Store Timestamp
          if ((request_value & DAP_TRANSFER_TIMESTAMP) != 0U) {
            timestamp = DAP_Data.timestamp;
            *response++ = (uint8_t) timestamp;
            *response++ = (uint8_t)(timestamp >>  8);
            *response++ = (uint8_t)(timestamp >> 16);
            *response++ = (uint8_t)(timestamp >> 24);
          }
#endif
          post_read = 1U;
        }
      }
    } else {
      // Write register
      if (post_read) {
        // Select JTAG chain
        if (ir != JTAG_DPACC) {
          ir = JTAG_DPACC;
          JTAG_IR(ir);
        }
        // Read previous data
        retry = DAP_Data.transfer.retry_count;
        do {
          response_value = JTAG_Transfer(DP_RDBUFF | DAP_TRANSFER_RnW, &data);
        } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
        if (response_value != DAP_TRANSFER_OK) {
          break;
        }
        // Store previous data
        *response++ = (uint8_t) data;
        *response++ = (uint8_t)(data >>  8);
        *response++ = (uint8_t)(data >> 16);
        *response++ = (uint8_t)(data >> 24);
        post_read = 0U;
      }
      // Load data
      data = (uint32_t)(*(request+0) <<  0) |
             (uint32_t)(*(request+1) <<  8) |
             (uint32_t)(*(request+2) << 16) |
             (uint32_t)(*(request+3) << 24);
      request += 4;
      if ((request_value & DAP_TRANSFER_MATCH_MASK) != 0U) {
        // Write match mask
        DAP_Data.transfer.match_mask = data;
        response_value = DAP_TRANSFER_OK;
      } else {
        // Select JTAG chain
        if (ir != request_ir) {
          ir = request_ir;
          JTAG_IR(ir);
        }
        // Write DP/AP register
        retry = DAP_Data.transfer.retry_count;
        do {
          response_value = JTAG_Transfer(request_value, &data);
        } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
        if (response_value != DAP_TRANSFER_OK) {
          break;
        }
#if (TIMESTAMP_CLOCK != 0U)
        // Store Timestamp
        if ((request_value & DAP_TRANSFER_TIMESTAMP) != 0U) {
          timestamp = DAP_Data.timestamp;
          *response++ = (uint8_t) timestamp;
          *response++ = (uint8_t)(timestamp >>  8);
          *response++ = (uint8_t)(timestamp >> 16);
          *response++ = (uint8_t)(timestamp >> 24);
        }
#endif
      }
    }
    response_count++;
    if (DAP_TransferAbort) {
      break;
    }
  }

  for (; request_count != 0U; request_count--) {
    // Process canceled requests
    request_value = *request++;
    if ((request_value & DAP_TRANSFER_RnW) != 0U) {
      // Read register
      if ((request_value & DAP_TRANSFER_MATCH_VALUE) != 0U) {
        // Read with value match
        request += 4;
      }
    } else {
      // Write register
      request += 4;
    }
  }

  if (response_value == DAP_TRANSFER_OK) {
    // Select JTAG chain
    if (ir != JTAG_DPACC) {
      ir = JTAG_DPACC;
      JTAG_IR(ir);
    }
    if (post_read) {
      // Read previous data
      retry = DAP_Data.transfer.retry_count;
      do {
        response_value = JTAG_Transfer(DP_RDBUFF | DAP_TRANSFER_RnW, &data);
      } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
      if (response_value != DAP_TRANSFER_OK) {
        goto end;
      }
      // Store previous data
      *response++ = (uint8_t) data;
      *response++ = (uint8_t)(data >>  8);
      *response++ = (uint8_t)(data >> 16);
      *response++ = (uint8_t)(data >> 24);
    } else {
      // Check last write
      retry = DAP_Data.transfer.retry_count;
      do {
        response_value = JTAG_Transfer(DP_RDBUFF | DAP_TRANSFER_RnW, NULL);
      } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
    }
  }

end:
  *(response_head+0) = (uint8_t)response_count;
  *(response_head+1) = (uint8_t)response_value;

  return (((uint32_t)(request - request_head) << 16) | (uint32_t)(response - response_head));
}
#endif


// Process Dummy Transfer command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_Dummy_Transfer(const uint8_t *request, uint8_t *response) {
  const
  uint8_t  *request_head;
  uint32_t  request_count;
  uint32_t  request_value;

  request_head  =  request;

  request++;            // Ignore DAP index

  request_count = *request++;

  for (; request_count != 0U; request_count--) {
    // Process dummy requests
    request_value = *request++;
    if ((request_value & DAP_TRANSFER_RnW) != 0U) {
      // Read register
      if ((request_value & DAP_TRANSFER_MATCH_VALUE) != 0U) {
        // Read with value match
        request += 4;
      }
    } else {
      // Write register
      request += 4;
    }
  }

  *(response+0) = 0U;   // Response count
  *(response+1) = 0U;   // Response value

  return (((uint32_t)(request - request_head) << 16) | 2U);
}


// Process Transfer command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_Transfer(const uint8_t *request, uint8_t *response) {
  uint32_t num;

  switch (DAP_Data.debug_port) {
#if (DAP_SWD != 0)
    case DAP_PORT_SWD:
      num = DAP_SWD_Transfer(request, response);
      break;
#endif
#if (DAP_JTAG != 0)
    case DAP_PORT_JTAG:
      num = DAP_JTAG_Transfer(request, response);
      break;
#endif
    default:
      num = DAP_Dummy_Transfer(request, response);
      break;
  }

  return (num);
}


// Process SWD Transfer Block command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response
#if (DAP_SWD != 0)
static uint32_t DAP_SWD_TransferBlock(const uint8_t *request, uint8_t *response) {
  uint32_t  request_count;
  uint32_t  request_value;
  uint32_t  response_count;
  uint32_t  response_value;
  uint8_t  *response_head;
  uint32_t  retry;
  uint32_t  data;

  response_count = 0U;
  response_value = 0U;
  response_head  = response;
  response      += 3;

  DAP_TransferAbort = 0U;

  request++;            // Ignore DAP index

  request_count = (uint32_t)(*(request+0) << 0) |
                  (uint32_t)(*(request+1) << 8);
  request += 2;
  if (request_count == 0U) {
    goto end;
  }

  request_value = *request++;
  if ((request_value & DAP_TRANSFER_RnW) != 0U) {
    // Read register block
    if ((request_value & DAP_TRANSFER_APnDP) != 0U) {
      // Post AP read
      retry = DAP_Data.transfer.retry_count;
      do {
        response_value = SWD_Transfer(request_value, NULL);
      } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
      if (response_value != DAP_TRANSFER_OK) {
        goto end;
      }
    }
    while (request_count--) {
      // Read DP/AP register
      if ((request_count == 0U) && ((request_value & DAP_TRANSFER_APnDP) != 0U)) {
        // Last AP read
        request_value = DP_RDBUFF | DAP_TRANSFER_RnW;
      }
      retry = DAP_Data.transfer.retry_count;
      do {
        response_value = SWD_Transfer(request_value, &data);
      } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
      if (response_value != DAP_TRANSFER_OK) {
        goto end;
      }
      // Store data
      *response++ = (uint8_t) data;
      *response++ = (uint8_t)(data >>  8);
      *response++ = (uint8_t)(data >> 16);
      *response++ = (uint8_t)(data >> 24);
      response_count++;
    }
  } else {
    // Write register block
    while (request_count--) {
      // Load data
      data = (uint32_t)(*(request+0) <<  0) |
             (uint32_t)(*(request+1) <<  8) |
             (uint32_t)(*(request+2) << 16) |
             (uint32_t)(*(request+3) << 24);
      request += 4;
      // Write DP/AP register
      retry = DAP_Data.transfer.retry_count;
      do {
        response_value = SWD_Transfer(request_value, &data);
      } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
      if (response_value != DAP_TRANSFER_OK) {
        goto end;
      }
      response_count++;
    }
    // Check last write
    retry = DAP_Data.transfer.retry_count;
    do {
      response_value = SWD_Transfer(DP_RDBUFF | DAP_TRANSFER_RnW, NULL);
    } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
  }

end:
  *(response_head+0) = (uint8_t)(response_count >> 0);
  *(response_head+1) = (uint8_t)(response_count >> 8);
  *(response_head+2) = (uint8_t) response_value;

  return ((uint32_t)(response - response_head));
}
#endif


// Process JTAG Transfer Block command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response
#if (DAP_JTAG != 0)
static uint32_t DAP_JTAG_TransferBlock(const uint8_t *request, uint8_t *response) {
  uint32_t  request_count;
  uint32_t  request_value;
  uint32_t  response_count;
  uint32_t  response_value;
  uint8_t  *response_head;
  uint32_t  retry;
  uint32_t  data;
  uint32_t  ir;

  response_count = 0U;
  response_value = 0U;
  response_head  = response;
  response      += 3;

  DAP_TransferAbort = 0U;

  // Device index (JTAP TAP)
  DAP_Data.jtag_dev.index = *request++;
  if (DAP_Data.jtag_dev.index >= DAP_Data.jtag_dev.count) {
    goto end;
  }

  request_count = (uint32_t)(*(request+0) << 0) |
                  (uint32_t)(*(request+1) << 8);
  request += 2;
  if (request_count == 0U) {
    goto end;
  }

  request_value = *request++;

  // Select JTAG chain
  ir = (request_value & DAP_TRANSFER_APnDP) ? JTAG_APACC : JTAG_DPACC;
  JTAG_IR(ir);

  if ((request_value & DAP_TRANSFER_RnW) != 0U) {
    // Post read
    retry = DAP_Data.transfer.retry_count;
    do {
      response_value = JTAG_Transfer(request_value, NULL);
    } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
    if (response_value != DAP_TRANSFER_OK) {
      goto end;
    }
    // Read register block
    while (request_count--) {
      // Read DP/AP register
      if (request_count == 0U) {
        // Last read
        if (ir != JTAG_DPACC) {
          JTAG_IR(JTAG_DPACC);
        }
        request_value = DP_RDBUFF | DAP_TRANSFER_RnW;
      }
      retry = DAP_Data.transfer.retry_count;
      do {
        response_value = JTAG_Transfer(request_value, &data);
      } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
      if (response_value != DAP_TRANSFER_OK) {
        goto end;
      }
      // Store data
      *response++ = (uint8_t) data;
      *response++ = (uint8_t)(data >>  8);
      *response++ = (uint8_t)(data >> 16);
      *response++ = (uint8_t)(data >> 24);
      response_count++;
    }
  } else {
    // Write register block
    while (request_count--) {
      // Load data
      data = (uint32_t)(*(request+0) <<  0) |
             (uint32_t)(*(request+1) <<  8) |
             (uint32_t)(*(request+2) << 16) |
             (uint32_t)(*(request+3) << 24);
      request += 4;
      // Write DP/AP register
      retry = DAP_Data.transfer.retry_count;
      do {
        response_value = JTAG_Transfer(request_value, &data);
      } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
      if (response_value != DAP_TRANSFER_OK) {
        goto end;
      }
      response_count++;
    }
    // Check last write
    if (ir != JTAG_DPACC) {
      JTAG_IR(JTAG_DPACC);
    }
    retry = DAP_Data.transfer.retry_count;
    do {
      response_value = JTAG_Transfer(DP_RDBUFF | DAP_TRANSFER_RnW, NULL);
    } while ((response_value == DAP_TRANSFER_WAIT) && retry-- && !DAP_TransferAbort);
  }

end:
  *(response_head+0) = (uint8_t)(response_count >> 0);
  *(response_head+1) = (uint8_t)(response_count >> 8);
  *(response_head+2) = (uint8_t) response_value;

  return ((uint32_t)(response - response_head));
}
#endif


// Process Transfer Block command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_TransferBlock(const uint8_t *request, uint8_t *response) {
  uint32_t num;

  switch (DAP_Data.debug_port) {
#if (DAP_SWD != 0)
    case DAP_PORT_SWD:
      num = DAP_SWD_TransferBlock (request, response);
      break;
#endif
#if (DAP_JTAG != 0)
    case DAP_PORT_JTAG:
      num = DAP_JTAG_TransferBlock(request, response);
      break;
#endif
    default:
      *(response+0) = 0U;       // Response count [7:0]
      *(response+1) = 0U;       // Response count[15:8]
      *(response+2) = 0U;       // Response value
      num = 3U;
      break;
  }

  if ((*(request+3) & DAP_TRANSFER_RnW) != 0U) {
    // Read register block
    num |=  4U << 16;
  } else {
    // Write register block
    num |= (4U + (((uint32_t)(*(request+1)) | (uint32_t)(*(request+2) << 8)) * 4)) << 16;
  }

  return (num);
}


// Process SWD Write ABORT command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response
#if (DAP_SWD != 0)
static uint32_t DAP_SWD_WriteAbort(const uint8_t *request, uint8_t *response) {
  uint32_t data;

  // Load data (Ignore DAP index)
  data = (uint32_t)(*(request+1) <<  0) |
         (uint32_t)(*(request+2) <<  8) |
         (uint32_t)(*(request+3) << 16) |
         (uint32_t)(*(request+4) << 24);

  // Write Abort register
  SWD_Transfer(DP_ABORT, &data);

  *response = DAP_OK;
  return (1U);
}
#endif


// Process JTAG Write ABORT command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response
#if (DAP_JTAG != 0)
static uint32_t DAP_JTAG_WriteAbort(const uint8_t *request, uint8_t *response) {
  uint32_t data;

  // Device index (JTAP TAP)
  DAP_Data.jtag_dev.index = *request;
  if (DAP_Data.jtag_dev.index >= DAP_Data.jtag_dev.count) {
    *response = DAP_ERROR;
    return (1U);
  }

  // Select JTAG chain
  JTAG_IR(JTAG_ABORT);

  // Load data
  data = (uint32_t)(*(request+1) <<  0) |
         (uint32_t)(*(request+2) <<  8) |
         (uint32_t)(*(request+3) << 16) |
         (uint32_t)(*(request+4) << 24);

  // Write Abort register
  JTAG_WriteAbort(data);

  *response = DAP_OK;
  return (1U);
}
#endif


// Process Write ABORT command and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
static uint32_t DAP_WriteAbort(const uint8_t *request, uint8_t *response) {
  uint32_t num;

  switch (DAP_Data.debug_port) {
#if (DAP_SWD != 0)
    case DAP_PORT_SWD:
      num = DAP_SWD_WriteAbort (request, response);
      break;
#endif
#if (DAP_JTAG != 0)
    case DAP_PORT_JTAG:
      num = DAP_JTAG_WriteAbort(request, response);
      break;
#endif
    default:
      *response = DAP_ERROR;
      num = 1U;
      break;
  }
  return ((5U << 16) | num);
}


// Process DAP Vendor command request and prepare response
// Default function (can be overridden)
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
__WEAK uint32_t DAP_ProcessVendorCommand(const uint8_t *request, uint8_t *response) {
  (void)request;
  *response = ID_DAP_Invalid;
  return ((1U << 16) | 1U);
}


// Process DAP command request and prepare response
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t DAP_ProcessCommand(const uint8_t *request, uint8_t *response) {
  uint32_t num;

  if ((*request >= ID_DAP_Vendor0) && (*request <= ID_DAP_Vendor31)) {
    return DAP_ProcessVendorCommand(request, response);
  }

  *response++ = *request;

  switch (*request++) {
    case ID_DAP_Info:
      num = DAP_Info(*request, response+1);
      *response = (uint8_t)num;
      return ((2U << 16) + 2U + num);

    case ID_DAP_HostStatus:
      num = DAP_HostStatus(request, response);
      break;

    case ID_DAP_Connect:
      num = DAP_Connect(request, response);
      break;
    case ID_DAP_Disconnect:
      num = DAP_Disconnect(response);
      break;

    case ID_DAP_Delay:
      num = DAP_Delay(request, response);
      break;

    case ID_DAP_ResetTarget:
      num = DAP_ResetTarget(response);
      break;

    case ID_DAP_SWJ_Pins:
      num = DAP_SWJ_Pins(request, response);
      break;
    case ID_DAP_SWJ_Clock:
      num = DAP_SWJ_Clock(request, response);
      break;
    case ID_DAP_SWJ_Sequence:
      num = DAP_SWJ_Sequence(request, response);
      break;

    case ID_DAP_SWD_Configure:
      num = DAP_SWD_Configure(request, response);
      break;
    case ID_DAP_SWD_Sequence:
      num = DAP_SWD_Sequence(request, response);
      break;

    case ID_DAP_JTAG_Sequence:
      num = DAP_JTAG_Sequence(request, response);
      break;
    case ID_DAP_JTAG_Configure:
      num = DAP_JTAG_Configure(request, response);
      break;
    case ID_DAP_JTAG_IDCODE:
      num = DAP_JTAG_IDCode(request, response);
      break;

    case ID_DAP_TransferConfigure:
      num = DAP_TransferConfigure(request, response);
      break;
    case ID_DAP_Transfer:
      num = DAP_Transfer(request, response);
      break;
    case ID_DAP_TransferBlock:
      num = DAP_TransferBlock(request, response);
      break;

    case ID_DAP_WriteABORT:
      num = DAP_WriteAbort(request, response);
      break;

#if ((SWO_UART != 0) || (SWO_MANCHESTER != 0))
    case ID_DAP_SWO_Transport:
      num = SWO_Transport(request, response);
      break;
    case ID_DAP_SWO_Mode:
      num = SWO_Mode(request, response);
      break;
    case ID_DAP_SWO_Baudrate:
      num = SWO_Baudrate(request, response);
      break;
    case ID_DAP_SWO_Control:
      num = SWO_Control(request, response);
      break;
    case ID_DAP_SWO_Status:
      num = SWO_Status(response);
      break;
    case ID_DAP_SWO_ExtendedStatus:
      num = SWO_ExtendedStatus(request, response);
      break;
    case ID_DAP_SWO_Data:
      num = SWO_Data(request, response);
      break;
#endif

#if (DAP_UART != 0)
    case ID_DAP_UART_Transport:
      num = UART_Transport(request, response);
      break;
    case ID_DAP_UART_Configure:
      num = UART_Configure(request, response);
      break;
    case ID_DAP_UART_Control:
      num = UART_Control(request, response);
      break;
    case ID_DAP_UART_Status:
      num = UART_Status(response);
      break;
    case ID_DAP_UART_Transfer:
      num = UART_Transfer(request, response);
      break;
#endif

    default:
      *(response-1) = ID_DAP_Invalid;
      return ((1U << 16) | 1U);
  }

  return ((1U << 16) + 1U + num);
}


// Execute DAP command (process request and prepare response)
//   request:  pointer to request data
//   response: pointer to response data
//   return:   number of bytes in response (lower 16 bits)
//             number of bytes in request (upper 16 bits)
uint32_t DAP_ExecuteCommand(const uint8_t *request, uint8_t *response) {
  uint32_t cnt, num, n;

  if (*request == ID_DAP_ExecuteCommands) {
    *response++ = *request++;
    cnt = *request++;
    *response++ = (uint8_t)cnt;
    num = (2U << 16) | 2U;
    while (cnt--) {
      n = DAP_ProcessCommand(request, response);
      num += n;
      request  += (uint16_t)(n >> 16);
      response += (uint16_t) n;
    }
    return (num);
  }

  return DAP_ProcessCommand(request, response);
}


// Setup DAP
void DAP_Setup(void) {

  // Default settings
  DAP_Data.debug_port  = 0U;
  DAP_Data.transfer.idle_cycles = 0U;
  DAP_Data.transfer.retry_count = 100U;
  DAP_Data.transfer.match_retry = 0U;
  DAP_Data.transfer.match_mask  = 0x00000000U;
#if (DAP_SWD != 0)
  DAP_Data.swd_conf.turnaround  = 1U;
  DAP_Data.swd_conf.data_phase  = 0U;
#endif
#if (DAP_JTAG != 0)
  DAP_Data.jtag_dev.count = 0U;
#endif

  // Sets DAP_Data.fast_clock and DAP_Data.clock_delay.
  Set_Clock_Delay(DAP_DEFAULT_SWJ_CLOCK);

  DAP_SETUP();  // Device specific setup
}
