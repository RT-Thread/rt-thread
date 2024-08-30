/**
  **************************************************************************
  * @file     at32m412_416_can.h
  * @brief    at32m412_416 can header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to 
  * download from Artery official website is the copyrighted work of Artery. 
  * Artery authorizes customers to use, copy, and distribute the BSP 
  * software and its related documentation for the purpose of design and 
  * development in conjunction with Artery microcontrollers. Use of the 
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32M412_416_CAN_H
#define __AT32M412_416_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "at32m412_416.h"

/* only AT32M416xx support can-fd */
#if defined (AT32M416xx)
#define SUPPORT_CAN_FD
#endif

/** @addtogroup AT32M412_416_periph_driver
  * @{
  */

/** @addtogroup CAN
  * @{
  */ 
 
/** @defgroup CAN_interrupts_definition
  * @brief can interrupt
  * @{
  */

#define CAN_AIE_INT                      ((uint32_t)0x00000001) /*!< abort interrupt */
#define CAN_EIE_INT                      ((uint32_t)0x00000002) /*!< error interrupt */
#define CAN_TSIE_INT                     ((uint32_t)0x00000004) /*!< transmission of the secondary transmit buffer completed interrupt */
#define CAN_TPIE_INT                     ((uint32_t)0x00000008) /*!< transmission of the primary transmit buffer completed interrupt */
#define CAN_RAFIE_INT                    ((uint32_t)0x00000010) /*!< rxbuf almost full interrupt */
#define CAN_RFIE_INT                     ((uint32_t)0x00000020) /*!< rxbuf full interrupt */
#define CAN_ROIE_INT                     ((uint32_t)0x00000040) /*!< rxbuf overflow interrupt */
#define CAN_RIE_INT                      ((uint32_t)0x00000080) /*!< receiver interrupt */
#define CAN_BEIE_INT                     ((uint32_t)0x00000100) /*!< bus error interrupt */
#define CAN_ALIE_INT                     ((uint32_t)0x00000200) /*!< arbitration lost interrupt */
#define CAN_EPIE_INT                     ((uint32_t)0x00000400) /*!< error passive interrupt */
#define CAN_TTIE_INT                     ((uint32_t)0x00000800) /*!< time trigger interrupt */
#define CAN_TEIE_INT                     ((uint32_t)0x00001000) /*!< trigger error interrupt */
#define CAN_WTIE_INT                     ((uint32_t)0x00002000) /*!< watch trigger interrupt */
#define CAN_ALL_INT                      ((uint32_t)0xFFFFFFFF) /*!< all interrupt */

/**
  * @}
  */

/** @defgroup CAN_flags_definition
  * @brief can flag
  * @{
  */

#define CAN_AIF_FLAG                     ((uint32_t)0x00000001) /*!< abort interrupt flag */
#define CAN_EIF_FLAG                     ((uint32_t)0x00000002) /*!< error interrupt flag: error warning or busoff. */
#define CAN_TSIF_FLAG                    ((uint32_t)0x00000004) /*!< transmission of the secondary transmit buffer be completed interrupt flag */
#define CAN_TPIF_FLAG                    ((uint32_t)0x00000008) /*!< transmission of the primary transmit buffer be completed interrupt flag */
#define CAN_RAFIF_FLAG                   ((uint32_t)0x00000010) /*!< rxbuf almost full interrupt flag */
#define CAN_RFIF_FLAG                    ((uint32_t)0x00000020) /*!< rxbuf full interrupt flag */
#define CAN_ROIF_FLAG                    ((uint32_t)0x00000040) /*!< rxbuf overflow interrupt flag */
#define CAN_RIF_FLAG                     ((uint32_t)0x00000080) /*!< receiver interrupt flag */
#define CAN_BEIF_FLAG                    ((uint32_t)0x00000100) /*!< bus error interrupt flag */
#define CAN_ALIF_FLAG                    ((uint32_t)0x00000200) /*!< arbitration lost interrupt flag */
#define CAN_EPIF_FLAG                    ((uint32_t)0x00000400) /*!< error passive interrupt flag */
#define CAN_TTIF_FLAG                    ((uint32_t)0x00000800) /*!< time trigger interrupt flag */
#define CAN_TEIF_FLAG                    ((uint32_t)0x00001000) /*!< trigger error interrupt flag */
#define CAN_WTIF_FLAG                    ((uint32_t)0x00002000) /*!< watch trigger interrupt flag */
#define CAN_EPASS_FLAG                   ((uint32_t)0x40000000) /*!< error passive status flag */
#define CAN_EWARN_FLAG                   ((uint32_t)0x80000000) /*!< error warning limit reached status flag */
#define CAN_ALL_FLAG                     ((uint32_t)0xFFFFFFFF) /*!< all interrupt and status flag */

/**
  * @}
  */

/**
  * @brief  can identifier type
  */
typedef enum
{
  CAN_ID_STANDARD                        = 0x00, /*!< standard Id */
  CAN_ID_EXTENDED                        = 0x01  /*!< extended Id */
} can_identifier_type;

/**
  * @brief  can frame type
  */
typedef enum
{
  CAN_FRAME_DATA                         = 0x00, /*!< data frame */
  CAN_FRAME_REMOTE                       = 0x01  /*!< remote frame */
} can_frame_type;

#ifdef SUPPORT_CAN_FD
/**
  * @brief  can format type
  */
typedef enum
{
  CAN_FORMAT_CLASSIC                     = 0x00, /*!< CLASSIC-CAN format */
  CAN_FORMAT_FD                          = 0x01  /*!< FD-CAN format */
} can_format_type;

/**
  * @brief  can bitrate switch type
  */
typedef enum
{
  CAN_BRS_OFF                            = 0x00, /*!< bit rate switch off */
  CAN_BRS_ON                             = 0x01  /*!< bit rate switch on */
} can_rate_switch_type;

/**
  * @brief  can error state indicator type
  */
typedef enum
{
  CAN_ESI_ACTIVE                         = 0x00, /*!< error_state_indicator active */
  CAN_ESI_PASSIVE                        = 0x01  /*!< error_state_indicator passive */
} can_error_state_type;
#endif 

/**
  * @brief  can data length type
  */
typedef enum
{
  CAN_DLC_BYTES_0                        = 0x00, /*!< 0 bytes data field */
  CAN_DLC_BYTES_1                        = 0x01, /*!< 1 bytes data field */
  CAN_DLC_BYTES_2                        = 0x02, /*!< 2 bytes data field */
  CAN_DLC_BYTES_3                        = 0x03, /*!< 3 bytes data field */
  CAN_DLC_BYTES_4                        = 0x04, /*!< 4 bytes data field */
  CAN_DLC_BYTES_5                        = 0x05, /*!< 5 bytes data field */
  CAN_DLC_BYTES_6                        = 0x06, /*!< 6 bytes data field */
  CAN_DLC_BYTES_7                        = 0x07, /*!< 7 bytes data field */
  CAN_DLC_BYTES_8                        = 0x08, /*!< 8 bytes data field */
#ifdef SUPPORT_CAN_FD
  CAN_DLC_BYTES_12                       = 0x09, /*!< 12 bytes data field */
  CAN_DLC_BYTES_16                       = 0x0A, /*!< 16 bytes data field */
  CAN_DLC_BYTES_20                       = 0x0B, /*!< 20 bytes data field */
  CAN_DLC_BYTES_24                       = 0x0C, /*!< 24 bytes data field */
  CAN_DLC_BYTES_32                       = 0x0D, /*!< 32 bytes data field */
  CAN_DLC_BYTES_48                       = 0x0E, /*!< 48 bytes data field */
  CAN_DLC_BYTES_64                       = 0x0F  /*!< 64 bytes data field */
#endif 
} can_data_length_type;

/**
  * @brief  can txbuf select type
  */
typedef enum
{
  CAN_TXBUF_PTB                          = 0x00, /*!< the primary transmit buffer (high priority) */
  CAN_TXBUF_STB                          = 0x01  /*!< the secondary transmit buffer (low priority) */
} can_txbuf_select_type;

/**
  * @brief  can txbuf transmit type
  */
typedef enum
{
  CAN_TRANSMIT_PTB                       = 0x10, /*!< transmit the primary transmit buffer */
  CAN_TRANSMIT_STB_ONE                   = 0x04, /*!< transmit one frame of the secondary transmit buffer */
  CAN_TRANSMIT_STB_ALL                   = 0x02  /*!< transmit all frames of the secondary transmit buffer */
} can_txbuf_transmit_type;

/**
  * @brief  can abort transmit type
  */
typedef enum
{
  CAN_ABORT_TRANSMIT_PTB                 = 0x08, /*!< abort transmit of the primary transmit buffer */
  CAN_ABORT_TRANSMIT_STB                 = 0x01  /*!< abort transmit of the secondary transmit buffer */
} can_abort_transmit_type;

/**
  * @brief  can clear the secondary transmit buffer type 
  */
typedef enum
{
  CAN_CLEAR_STB_ONE                      = 0x05, /*!< clear one frame of the secondary transmit buffer */
  CAN_CLEAR_STB_ALL                      = 0x03  /*!< clear all frames of the secondary transmit buffer */
} can_clear_stb_type;

/**
  * @brief  can the secondary transmit buffer transmit mode type  
  */
typedef enum
{
  CAN_STB_TRANSMIT_BY_FIFO               = 0x00, /*!< the secondary transmit buffer transmit by fifo */
  CAN_STB_TRANSMIT_BY_ID                 = 0x01  /*!< the secondary transmit buffer transmit by id */
} can_stb_transmit_mode_type;

/**
  * @brief  can the secondary transmit buffer status type
  */
typedef enum
{
  CAN_STB_STATUS_EMPTY                   = 0x00, /*!< the secondary transmit buffer(0) is empty */
  CAN_STB_STATUS_LESS                    = 0x01, /*!< the secondary transmit buffer(1) is less than or equal to half full */
  CAN_STB_STATUS_MORE                    = 0x02, /*!< the secondary transmit buffer(2) is more than half full */
  CAN_STB_STATUS_FULL                    = 0x03  /*!< the secondary transmit buffer(3) is full */
} can_stb_status_type;

/**
  * @brief  can rxbuf status type
  */
typedef enum
{
  CAN_RXBUF_STATUS_EMPTY                 = 0x00, /*!< rxbuf: empty */
  CAN_RXBUF_STATUS_LESS                  = 0x01, /*!< rxbuf: > empty and < almost full(AFWL) */
  CAN_RXBUF_STATUS_ALMOST                = 0x02, /*!< rxbuf: >= almost full (programmable threshold by AFWL) but not full and no overflow */
  CAN_RXBUF_STATUS_FULL                  = 0x03, /*!< rxbuf: full */
  CAN_RXBUF_STATUS_OVERFLOW              = 0x04  /*!< rxbuf: overflow */
} can_rxbuf_status_type;

/**
  * @brief  can rxbuf overflow mode type
  */
typedef enum
{
  CAN_RXBUF_OVERFLOW_BE_OVWR             = 0x00, /*!< the oldest frame will be overwritten. */
  CAN_RXBUF_OVERFLOW_BE_LOSE             = 0x01  /*!< the new frame will not be stored. */
} can_rxbuf_overflow_mode_type;

/**
  * @brief  can timestamp position type
  */
typedef enum
{
  CAN_TIMESTAMP_AT_SOF                   = 0x00, /*!< time stamping position at sof */
  CAN_TIMESTAMP_AT_EOF                   = 0x01  /*!< time stamping position at eof */
} can_timestamp_position_type;

/**
  * @brief  can error state indicator type
  */
typedef enum
{
  CAN_KOER_NOERR                         = 0x00, /*!< kind_of_error: no error */
  CAN_KOER_BIT                           = 0x01, /*!< kind_of_error: bit error */
  CAN_KOER_FORM                          = 0x02, /*!< kind_of_error: form error */
  CAN_KOER_STUFF                         = 0x03, /*!< kind_of_error: stuff error */
  CAN_KOER_ACK                           = 0x04, /*!< kind_of_error: ack error */
  CAN_KOER_CRC                           = 0x05, /*!< kind_of_error: crc error */
  CAN_KOER_OTHER                         = 0x06, /*!< kind_of_error: other error */
  CAN_KOER_PCRC                          = 0x07  /*!< kind_of_error: pcrc error (can-xl only) */
} can_error_type;

/**
  * @brief  can receive frame type
  */
typedef enum
{
  CAN_RECV_NORMAL                        = 0x00, /*!< receive normal frame */
  CAN_RECV_LOOPBACK                      = 0x01  /*!< receive loop back frame */
} can_recv_frame_type;

/**
  * @brief  can time_trigger_can timer_div type
  */
typedef enum
{
  CAN_TTCAN_TIMER_DIV_1                  = 0x00, /*!< classic-can bit time div1 to ttcan timer */
  CAN_TTCAN_TIMER_DIV_2                  = 0x01, /*!< classic-can bit time div2 to ttcan timer */
  CAN_TTCAN_TIMER_DIV_4                  = 0x02, /*!< classic-can bit time div4 to ttcan timer */
  CAN_TTCAN_TIMER_DIV_8                  = 0x03, /*!< classic-can bit time div8 to ttcan timer */
} can_ttcan_timer_div_type;

/**
  * @brief  can time_trigger_can trigger type
  */
typedef enum
{
  CAN_TTCAN_TRIGGER_IMMEDIATE            = 0x00, /*!< immediate trigger for immediate transmission */
  CAN_TTCAN_TRIGGER_TIME                 = 0x01, /*!< time trigger for receive triggers */
  CAN_TTCAN_TRIGGER_SINGLE_TRANSMIT      = 0x02, /*!< single shot transmit trigger for exclusive time windows */
  CAN_TTCAN_TRIGGER_TRANSMIT_START       = 0x03, /*!< transmit start trigger for merged arbitrating time windows */
  CAN_TTCAN_TRIGGER_TRANSMIT_STOP        = 0x04, /*!< transmit stop trigger for merged arbitrating time windows */
} can_ttcan_trigger_type;

/**
  * @brief  can ttcan txbuf slot status type
  */
typedef enum
{
  CAN_TTCAN_TXBUF_EMPTY                  = 0x00, /*!< set ttcan txbuf slot to "empty" */
  CAN_TTCAN_TXBUF_FILLED                 = 0x01, /*!< set ttcan txbuf slot to "filled" */
} can_ttcan_txbuf_status_type;

/**
  * @brief  can re-transmission times type
  */
typedef enum
{
  CAN_RE_TRANS_TIMES_0                   = 0x00, /*!< re-transmission 0 times */
  CAN_RE_TRANS_TIMES_1                   = 0x01, /*!< re-transmission 1 times */
  CAN_RE_TRANS_TIMES_2                   = 0x02, /*!< re-transmission 2 times */
  CAN_RE_TRANS_TIMES_3                   = 0x03, /*!< re-transmission 3 times */
  CAN_RE_TRANS_TIMES_4                   = 0x04, /*!< re-transmission 4 times */
  CAN_RE_TRANS_TIMES_5                   = 0x05, /*!< re-transmission 5 times */
  CAN_RE_TRANS_TIMES_6                   = 0x06, /*!< re-transmission 6 times */
  CAN_RE_TRANS_TIMES_UNLIMIT             = 0x07  /*!< re-transmission unlimited times */
} can_retransmission_times_type;

/**
  * @brief  can re-arbitration times type
  */
typedef enum
{
  CAN_RE_ARBI_TIMES_0                    = 0x00, /*!< re-arbitration 0 times */
  CAN_RE_ARBI_TIMES_1                    = 0x01, /*!< re-arbitration 1 times */
  CAN_RE_ARBI_TIMES_2                    = 0x02, /*!< re-arbitration 2 times */
  CAN_RE_ARBI_TIMES_3                    = 0x03, /*!< re-arbitration 3 times */
  CAN_RE_ARBI_TIMES_4                    = 0x04, /*!< re-arbitration 4 times */
  CAN_RE_ARBI_TIMES_5                    = 0x05, /*!< re-arbitration 5 times */
  CAN_RE_ARBI_TIMES_6                    = 0x06, /*!< re-arbitration 6 times */
  CAN_RE_ARBI_TIMES_UNLIMIT              = 0x07  /*!< re-arbitration unlimited times */
} can_rearbitration_times_type;

/**
  * @brief  can mode type
  */
typedef enum
{
  CAN_MODE_COMMUNICATE                   = 0x00, /*!< normal communication mode */
  CAN_MODE_EXT_LOOPBACK                  = 0x01, /*!< external loopback mode */
  CAN_MODE_EXT_LOOPBACK_ACK              = 0x02, /*!< external loopback mode with self-ack */
  CAN_MODE_INT_LOOPBACK                  = 0x03, /*!< internal loopback mode */
  CAN_MODE_LISTENONLY                    = 0x04, /*!< listen-only mode */
  CAN_MODE_LISTENONLY_EXT                = 0x05, /*!< listen-only combined with external loopback mode */
  CAN_MODE_LISTENONLY_EXT_ACK            = 0x06  /*!< listen-only combined with external loopback mode with self-ack */
} can_mode_type;

/**
  * @brief  can transmit state encoding type
  */
typedef enum
{
  CAN_TSTAT_IDLE                         = 0x00, /*!< no transmission in progress */
  CAN_TSTAT_ONGOING                      = 0x01, /*!< transmission active without any issues */
  CAN_TSTAT_LOST_ARBITRATION             = 0x02, /*!< arbitration lost. re-arbitration may take place with respect to REALIM. */
  CAN_TSTAT_TRANSMITTED                  = 0x03, /*!< transmission successfully completed */
  CAN_TSTAT_ABORTED                      = 0x04, /*!< transmission aborted */
  CAN_TSTAT_DISTURBED                    = 0x05, /*!< transmission error. retransmission may take place with respect to RETLIM. */
  CAN_TSTAT_REJECTED                     = 0x06  /*!< misconfiguration of the frame format in the LLC frame. */
} can_tstat_encoding_type;

/**
  * @brief can filter type 
  */
typedef enum
{
  CAN_FILTER_NUM_0                       = 0x00, /*!< can filter number 0 */
  CAN_FILTER_NUM_1                       = 0x01, /*!< can filter number 1 */
  CAN_FILTER_NUM_2                       = 0x02, /*!< can filter number 2 */
  CAN_FILTER_NUM_3                       = 0x03, /*!< can filter number 3 */
  CAN_FILTER_NUM_4                       = 0x04, /*!< can filter number 4 */
  CAN_FILTER_NUM_5                       = 0x05, /*!< can filter number 5 */
  CAN_FILTER_NUM_6                       = 0x06, /*!< can filter number 6 */
  CAN_FILTER_NUM_7                       = 0x07, /*!< can filter number 7 */
  CAN_FILTER_NUM_8                       = 0x08, /*!< can filter number 8 */
  CAN_FILTER_NUM_9                       = 0x09, /*!< can filter number 9 */
  CAN_FILTER_NUM_10                      = 0x0A, /*!< can filter number 10 */
  CAN_FILTER_NUM_11                      = 0x0B, /*!< can filter number 11 */
  CAN_FILTER_NUM_12                      = 0x0C, /*!< can filter number 12 */
  CAN_FILTER_NUM_13                      = 0x0D, /*!< can filter number 13 */
  CAN_FILTER_NUM_14                      = 0x0E, /*!< can filter number 14 */
  CAN_FILTER_NUM_15                      = 0x0F, /*!< can filter number 15 */
} can_filter_type;

/**
  * @brief can ttcan txbuf type 
  */
typedef enum
{
  CAN_TTCAN_TXBUF_NUM_0                  = 0x00, /*!< can ttcan txbuf number 0 */
  CAN_TTCAN_TXBUF_NUM_1                  = 0x01, /*!< can ttcan txbuf number 1 */
  CAN_TTCAN_TXBUF_NUM_2                  = 0x02, /*!< can ttcan txbuf number 2 */
  CAN_TTCAN_TXBUF_NUM_3                  = 0x03, /*!< can ttcan txbuf number 3 */
} can_ttcan_txbuf_type;

/**
  * @brief  can transmit status structure definition
  */
typedef struct
{
  uint8_t                                current_handle; /*!< specifies current handle for frame identification. */
  
  can_tstat_encoding_type                current_tstat;  /*!< specifies current transmission status of transmit frame.*/
  
  uint8_t                                final_handle;   /*!< specifies final handle for frame identification. */
  
  can_tstat_encoding_type                final_tstat;    /*!< specifies final transmission status of transmit frame.*/
  
} can_transmit_status_type;

/**
  * @brief  can transmit buffer structure definition
  */
typedef struct
{
  uint32_t                               id;             /*!< specifies the 11 or 29 bits standard or extended identifier. 
                                                              this parameter can be a value between 0 to 0x7FF or 0 to 0x1FFFFFFF. */

  can_identifier_type                    id_type;        /*!< specifies identifier type for the transmit buffer. */

  can_frame_type                         frame_type;     /*!< specifies frame type for the transmit buffer. */
 
  can_data_length_type                   data_length;    /*!< specifies the frame data length that will be transmitted. */

#ifdef SUPPORT_CAN_FD
  can_format_type                        fd_format;      /*!< specifies format for the transmit buffer. */

  can_rate_switch_type                   fd_rate_switch; /*!< specifies bit rate switch for the transmit buffer. */
 
  uint8_t                                data[64];       /*!< contains the transmit data. it ranges from 0 to 0xFF. */
#else
  uint8_t                                data[8];        /*!< contains the transmit data. it ranges from 0 to 0xFF. */
#endif
  
  confirm_state                          tx_timestamp;   /*!< specifies get transmit timestamp for the transmit buffer. */
  
  uint8_t                                handle;         /*!< The purpose of the handle is frame identification using TSTAT(transmit status). */

} can_txbuf_type;

/**
  * @brief  can receive buffer structure definition
  */
typedef struct
{ 
  uint32_t                               id;             /*!< specifies the 11 or 29 bits standard or extended identifier.
                                                              this parameter can be a value between 0 to 0x7FF or 0 to 0x1FFFFFFF. */
                                         
  can_identifier_type                    id_type;        /*!< specifies identifier type for the receive buffer. */
                                         
  can_frame_type                         frame_type;     /*!< specifies frame type for the receive buffer. */
                                         
  can_data_length_type                   data_length;    /*!< specifies the frame data length that will be received. */
                                         
#ifdef SUPPORT_CAN_FD                    
  can_format_type                        fd_format;      /*!< specifies format for the receive buffer. */
                                         
  can_rate_switch_type                   fd_rate_switch; /*!< specifies bit rate switch for the receive buffer. */
                                         
  can_error_state_type                   fd_error_state; /*!< specifies error state indicator type for the receive buffer. */
                                         
  uint8_t                                data[64];       /*!< contains the receive data. it ranges from 0 to 0xFF. */
#else                                    
  uint8_t                                data[8];        /*!< contains the receive data. it ranges from 0 to 0xFF. */
#endif                                   
                                         
  can_recv_frame_type                    recv_frame;     /*!< specifies receive frame mode for the receive buffer. */
                                         
  can_error_type                         kind_error;     /*!< specifies kind of error type for the receive buffer. */
                                         
  uint32_t                               rx_timestamp;   /*!< specifies the timestamp for the receive buffer. */

  uint16_t                               cycle_time;     /*!< specifies the cycle time for the receive buffer using TTCAN(Time-Triggered CAN). */

} can_rxbuf_type;

/**
  * @brief  can filter code type
  */
typedef struct
{ 
  uint32_t                               id;             /*!< specifies the 11 or 29 bits standard or extended identifier.
                                                              this parameter can be a value between 0 to 0x7FF or 0 to 0x1FFFFFFF. */

  can_identifier_type                    id_type;        /*!< specifies identifier type for the filter code. */

  can_frame_type                         frame_type;     /*!< specifies frame type for the filter code. */
 
  uint8_t                                data_length;    /*!< specifies frame data length for the filter code. */
 
#ifdef SUPPORT_CAN_FD  
  can_format_type                        fd_format;      /*!< specifies format for the filter code. */

  can_rate_switch_type                   fd_rate_switch; /*!< specifies bit rate switch for the filter code. */
 
  can_error_state_type                   fd_error_state; /*!< specifies error state indicator for the filter code. */
#endif  
  
  can_recv_frame_type                    recv_frame;     /*!< specifies receive frame mode for the filter code. */

} can_filter_code_type;              

/**
  * @brief  can filter mask type
  */
typedef struct
{ 
  uint32_t                               id;             /*!< specifies the 11 or 29 bits standard or extended identifier.
                                                              this parameter can be a value between 0 to 0x7FF or 0 to 0x1FFFFFFF. */
                                    
  confirm_state                          id_type;        /*!< specifies identifier type for the filter mask. */
                                       
  confirm_state                          frame_type;     /*!< specifies frame type for the filter mask. */
                                       
  uint8_t                                data_length;    /*!< specifies frame data length for the filter mask. */ 
                                       
#ifdef SUPPORT_CAN_FD                    
  confirm_state                          fd_format;      /*!< specifies format for the filter mask. */
                                         
  confirm_state                          fd_rate_switch; /*!< specifies bit rate switch for the filter mask. */
                                         
  confirm_state                          fd_error_state; /*!< specifies error state indicator for the filter mask. */
#endif                                   
                              
  confirm_state                          recv_frame;     /*!< specifies receive frame mode for the filter mask. */
  
} can_filter_mask_type;

/**
  * @brief  can filter config type
  */
typedef struct
{ 
  can_filter_code_type                   code_para;      /*!< specifies the filter code type. */
  
  can_filter_mask_type                   mask_para;      /*!< specifies the filter mask type. */
  
} can_filter_config_type;

/**
  * @brief  can baudrate structure definition
  */
typedef struct
{
  uint8_t                                bittime_div;    /*!< bittime division, this parameter can be 0x01~0x20. */
  
  uint8_t                                ac_rsaw_size;   /*!< classic-can resynchronization adjust width, this parameter can be 0x01~0x80. */
  
  uint16_t                               ac_bts1_size;   /*!< classic-can bit time segment 1, this parameter can be 0x02~0x201. */
  
  uint8_t                                ac_bts2_size;   /*!< classic-can bit time segment 2, this parameter can be 0x01~0x80. */
  
#ifdef SUPPORT_CAN_FD 
  uint8_t                                fd_rsaw_size;   /*!< can-fd resynchronization adjust width, this parameter can be 0x01~0x80. */

  uint16_t                               fd_bts1_size;   /*!< can-fd bit time segment 1, this parameter can be 0x02~0x101. */

  uint8_t                                fd_bts2_size;   /*!< can-fd bit time segment 2, this parameter can be 0x01~0x80. */
  
  uint8_t                                fd_ssp_offset;  /*!< can-fd secondary sample point offset, this parameter can be 0x00~0xFF. */
#endif 
 
} can_bittime_type;

/**
  * @brief type define can register all
  */
typedef struct
{  
  /**
    * @brief can tncfg register, offset:0x00 
    */
  union
  {
    __IO uint32_t tncfg;
    struct
    {
      __IO uint32_t reserved1            : 17;/* [16:0] */
      __IO uint32_t rop                  : 1; /* [17] */
      __IO uint32_t reserved2            : 6; /* [23:18] */ 
      __IO uint32_t tsen                 : 1; /* [24] */ 
      __IO uint32_t tspos                : 1; /* [25] */ 
      __IO uint32_t reserved3            : 6; /* [31:26] */ 
    } tncfg_bit;
  };
  
  /**
    * @brief can actime register, offset:0x04 
    */
  union
  {
    __IO uint32_t actime;
    struct
    {
      __IO uint32_t ac_seg_1            : 9; /* [8:0] */
      __IO uint32_t reserved1           : 7; /* [15:9] */
      __IO uint32_t ac_seg_2            : 7; /* [22:16] */
      __IO uint32_t reserved2           : 1; /* [23] */
      __IO uint32_t ac_sjw              : 7; /* [30:24] */ 
      __IO uint32_t reserved3           : 1; /* [31] */      
    } actime_bit;
  };
  
  /**
    * @brief can fdtime register, offset:0x08 
    */
  union
  {
    __IO uint32_t fdtime;
    struct
    {
      __IO uint32_t fd_seg_1            : 8; /* [7:0] */
      __IO uint32_t reserved1           : 8; /* [15:8] */
      __IO uint32_t fd_seg_2            : 7; /* [22:16] */
      __IO uint32_t reserved2           : 1; /* [23] */
      __IO uint32_t fd_sjw              : 7; /* [30:24] */ 
      __IO uint32_t reserved3           : 1; /* [31] */      
    } fdtime_bit;
  };
  
  /**
    * @brief can reserved1 register, offset:0x0C 
    */
  __IO uint32_t reserved1;
  
  /**
    * @brief can lbtcfg register, offset:0x10 
    */
  union
  {
    __IO uint32_t lbtcfg;
    struct
    {
      __IO uint32_t presc               : 5; /* [4:0] */
      __IO uint32_t reserved1           : 3; /* [7:5] */
      __IO uint32_t fd_sspoff           : 8; /* [15:8] */
      __IO uint32_t reserved2           : 8; /* [23:16] */
      __IO uint32_t realim              : 3; /* [26:24] */ 
      __IO uint32_t reserved3           : 1; /* [27] */ 
      __IO uint32_t retlim              : 3; /* [30:28] */
      __IO uint32_t reserved4           : 1; /* [31] */ 
    } lbtcfg_bit;
  };
  
  /**
    * @brief can sts register, offset:0x14 
    */
  union
  {
    __IO uint32_t sts;
    struct
    {
      __IO uint32_t aif                 : 1; /* [0] */
      __IO uint32_t eif                 : 1; /* [1] */
      __IO uint32_t tsif                : 1; /* [2] */
      __IO uint32_t tpif                : 1; /* [3] */
      __IO uint32_t rafif               : 1; /* [4] */ 
      __IO uint32_t rfif                : 1; /* [5] */      
      __IO uint32_t roif                : 1; /* [6] */
      __IO uint32_t rif                 : 1; /* [7] */
      __IO uint32_t beif                : 1; /* [8] */
      __IO uint32_t alif                : 1; /* [9] */
      __IO uint32_t epif                : 1; /* [10] */
      __IO uint32_t ttif                : 1; /* [11] */
      __IO uint32_t teif                : 1; /* [12] */
      __IO uint32_t wtif                : 1; /* [13] */
      __IO uint32_t reserved1           : 16; /* [29:14] */
      __IO uint32_t epass               : 1; /* [30] */
      __IO uint32_t ewarn               : 1; /* [31] */
    } sts_bit;
  };

  /**
    * @brief can reserved register, offset:0x18 
    */
  __IO uint32_t reserved2;

  /**
    * @brief can tstat register, offset:0x1C 
    */
  union
  {
    __IO uint32_t tstat;
    struct
    {
      __IO uint32_t handle_1            : 8; /* [7:0] */
      __IO uint32_t tstat_1             : 3; /* [10:8] */
      __IO uint32_t reserved1           : 5; /* [15:11] */
      __IO uint32_t handle_2            : 8; /* [23:16] */
      __IO uint32_t tstat_2             : 3; /* [26:24] */ 
      __IO uint32_t reserved2           : 5; /* [31:27] */      
    } tstat_bit;
  };
  
  /**
    * @brief can tts register, offset:0x20 
    */
  __IO uint32_t tts;
  
  /**
    * @brief can reserved register, offset:0x24
    */
  __IO uint32_t reserved3;
  
  /**
    * @brief can ctrlstat register, offset:0x28 
    */
  union
  {
    __IO uint32_t ctrlstat;
    struct
    {
      __IO uint32_t busoff              : 1; /* [0] */
      __IO uint32_t reserved1           : 4; /* [4:1] */
      __IO uint32_t lbmi                : 1; /* [5] */
      __IO uint32_t lbme                : 1; /* [6] */
      __IO uint32_t reset               : 1; /* [7] */ 
      __IO uint32_t tsa                 : 1; /* [8] */ 
      __IO uint32_t tsall               : 1; /* [9] */
      __IO uint32_t tsone               : 1; /* [10] */
      __IO uint32_t tpa                 : 1; /* [11] */
      __IO uint32_t tpe                 : 1; /* [12] */
      __IO uint32_t stby                : 1; /* [13] */
      __IO uint32_t lom                 : 1; /* [14] */
      __IO uint32_t tbsel               : 1; /* [15] */
      __IO uint32_t tsstat              : 2; /* [17:16] */   
      __IO uint32_t tsff                : 1; /* [18] */ 
      __IO uint32_t reserved2           : 1; /* [19] */ 
      __IO uint32_t tttbm               : 1; /* [20] */
      __IO uint32_t tsmode              : 1; /* [21] */
      __IO uint32_t tsnext              : 1; /* [22] */
      __IO uint32_t fd_iso              : 1; /* [23] */
      __IO uint32_t rstat               : 2; /* [25:24] */
      __IO uint32_t reserved3           : 1; /* [26] */
      __IO uint32_t rball               : 1; /* [27] */
      __IO uint32_t rrel                : 1; /* [28] */
      __IO uint32_t rov                 : 1; /* [29] */
      __IO uint32_t rom                 : 1; /* [30] */
      __IO uint32_t sack                : 1; /* [31] */
    } ctrlstat_bit;
  };
  
  /**
    * @brief can err register, offset:0x2C 
    */
  union
  {
    __IO uint32_t err;
    struct
    {
      __IO uint32_t ewl                 : 4; /* [3:0] */
      __IO uint32_t afwl                : 4; /* [7:4] */
      __IO uint32_t alc                 : 5; /* [12:8] */
      __IO uint32_t koer                : 3; /* [15:13] */
      __IO uint32_t recnt               : 8; /* [23:16] */ 
      __IO uint32_t tecnt               : 8; /* [31:24] */      
    } err_bit;
  };
  
  /**
    * @brief can refmsg register, offset:0x30 
    */
  union
  {
    __IO uint32_t refmsg;
    struct
    {
      __IO uint32_t ref_id              : 29; /* [28:0] */
      __IO uint32_t reserved1           : 2; /* [30:29] */
      __IO uint32_t ref_ide             : 1; /* [31] */     
    } refmsg_bit;
  };
  
  /**
    * @brief can ttcfg register, offset:0x34 
    */
  union
  {
    __IO uint32_t ttcfg;
    struct
    {
      __IO uint32_t ttptr               : 6; /* [5:0] */
      __IO uint32_t reserved1           : 2; /* [7:6] */
      __IO uint32_t ttype               : 3; /* [10:8] */
      __IO uint32_t reserved2           : 1; /* [11] */
      __IO uint32_t tew                 : 4; /* [15:12] */ 
      __IO uint32_t tbptr               : 6; /* [21:16] */  
      __IO uint32_t tbf                 : 1; /* [22] */  
      __IO uint32_t tbe                 : 1; /* [23] */
      __IO uint32_t tten                : 1; /* [24] */
      __IO uint32_t t_presc             : 2; /* [26:25] */
      __IO uint32_t reserved3           : 5; /* [31:27] */
    } ttcfg_bit;
  };
  
  /**
    * @brief can tttrig register, offset:0x38 
    */
  union
  {
    __IO uint32_t tttrig;
    struct
    {
      __IO uint32_t tttrig              : 16; /* [15:0] */
      __IO uint32_t ttwtrig             : 16; /* [31:16] */  
    } tttrig_bit;
  };
  
  /**
    * @brief can reserved register, offset:0x3C-0x40 
    */
  __IO uint32_t reserved4[2];
  
  /**
    * @brief can acfctrl register, offset:0x44 
    */
  union
  {
    __IO uint32_t acfctrl;
    struct
    {
      __IO uint32_t acfadr              : 4; /* [3:0] */
      __IO uint32_t reserved1           : 12; /* [15:4] */
      __IO uint32_t ae_x                : 16; /* [31:16] */
    } acfctrl_bit;
  };
  
  /**
    * @brief can fcid register, offset:0x48 
    */
  __IO uint32_t fcid;

  
  /**
    * @brief can fcfmt register, offset:0x4C 
    */
  union 
  {
    __IO uint32_t fcfmt;
    struct
    {
      __IO uint32_t dlc                 : 4; /* [3:0] */
      __IO uint32_t reserved1           : 12; /* [15:4] */
      __IO uint32_t ide                 : 1; /* [16] */
      __IO uint32_t fdf                 : 1; /* [17] */  
      __IO uint32_t brs                 : 1; /* [18] */
      __IO uint32_t xlf                 : 1; /* [19] */
      __IO uint32_t rmf                 : 1; /* [20] */
      __IO uint32_t sec                 : 1; /* [21] */
      __IO uint32_t reserved2           : 2; /* [23:22] */
      __IO uint32_t koer                : 3; /* [26:24] */
      __IO uint32_t esi                 : 1; /* [27] */
      __IO uint32_t lbf                 : 1; /* [28] */
      __IO uint32_t reserved3           : 3; /* [31:29] */    
    } fcfmt_bit;
  };
  
  /**
    * @brief can fctyp register, offset:0x50 
    */
    union 
  {
    __IO uint32_t fctyp;
    struct
    {
      __IO uint32_t sdt                 : 8; /* [7:0] */
      __IO uint32_t vcid                : 8; /* [15:8] */
      __IO uint32_t reserved1           : 8; /* [23:16] */
      __IO uint32_t handle              : 8; /* [31:24] */    
    } fctyp_bit;
  };

  /**
    * @brief can fcacf register, offset:0x54 
    */
  __IO uint32_t fcacf;
  
  /**
    * @brief can fmid register, offset:0x58 
    */
  __IO uint32_t fmid;
  
  /**
    * @brief can fmfmt register, offset:0x5C 
    */
  union 
  {
    __IO uint32_t fmfmt;
    struct
    {
      __IO uint32_t dlc                 : 4; /* [3:0] */
      __IO uint32_t reserved1           : 12; /* [15:4] */
      __IO uint32_t ide                 : 1; /* [16] */
      __IO uint32_t fdf                 : 1; /* [17] */  
      __IO uint32_t brs                 : 1; /* [18] */
      __IO uint32_t xlf                 : 1; /* [19] */
      __IO uint32_t rmf                 : 1; /* [20] */
      __IO uint32_t sec                 : 1; /* [21] */
      __IO uint32_t reserved2           : 2; /* [23:22] */
      __IO uint32_t koer                : 3; /* [26:24] */
      __IO uint32_t esi                 : 1; /* [27] */
      __IO uint32_t lbf                 : 1; /* [28] */
      __IO uint32_t reserved3           : 3; /* [31:29] */    
    } fmfmt_bit;
  };
  
  /**
    * @brief can fmtyp register, offset:0x60 
    */
  union 
  {
    __IO uint32_t fmtyp;
    struct
    {
      __IO uint32_t sdt                 : 8; /* [7:0] */
      __IO uint32_t vcid                : 8; /* [15:8] */
      __IO uint32_t reserved1           : 8; /* [23:16] */
      __IO uint32_t handle              : 8; /* [31:24] */    
    } fmtyp_bit;
  };
  
  /**
    * @brief can fmacf register, offset:0x64 
    */
  __IO uint32_t fmacf;
  
  /**
    * @brief can reserved register, offset:0x68-0x6C
    */
  __IO uint32_t reserved5[2];
  
  /**
    * @brief can rbid register, offset:0x70
    */
  __IO uint32_t rbid;
  
  /**
    * @brief can rbfmt register, offset:0x74
    */
  union 
  {
    __IO uint32_t rbfmt;
    struct
    {
      __IO uint32_t dlc                 : 4; /* [3:0] */
      __IO uint32_t reserved1           : 12; /* [15:4] */
      __IO uint32_t ide                 : 1; /* [16] */
      __IO uint32_t fdf                 : 1; /* [17] */  
      __IO uint32_t brs                 : 1; /* [18] */
      __IO uint32_t xlf                 : 1; /* [19] */
      __IO uint32_t rmf                 : 1; /* [20] */
      __IO uint32_t sec                 : 1; /* [21] */
      __IO uint32_t reserved2           : 2; /* [23:22] */
      __IO uint32_t koer                : 3; /* [26:24] */
      __IO uint32_t esi                 : 1; /* [27] */
      __IO uint32_t lbf                 : 1; /* [28] */
      __IO uint32_t reserved3           : 3; /* [31:29] */    
    } rbfmt_bit;
  };
  
  /**
    * @brief can rbtyp register, offset:0x78
    */
  union 
  {
    __IO uint32_t rbtyp;
    struct
    {
      __IO uint32_t sdt                 : 8; /* [7:0] */
      __IO uint32_t vcid                : 8; /* [15:8] */
      __IO uint32_t reserved1           : 8; /* [23:16] */
      __IO uint32_t handle              : 8; /* [31:24] */    
    } rbtyp_bit;
  };
  
  /**
    * @brief can rbacf register, offset:0x7C
    */
  __IO uint32_t rbacf;
  
  /**
    * @brief can rbdat register, offset:0x80-0xC8
    */
  __IO uint32_t rbdat[19];
  
  /**
    * @brief can tbid register, offset:0xCC
    */
  __IO uint32_t tbid;
  
  /**
    * @brief can tbfmt register, offset:0xD0
    */
  union 
  {
    __IO uint32_t tbfmt;
    struct
    {
      __IO uint32_t dlc                 : 4; /* [3:0] */
      __IO uint32_t reserved1           : 12; /* [15:4] */
      __IO uint32_t ide                 : 1; /* [16] */
      __IO uint32_t fdf                 : 1; /* [17] */  
      __IO uint32_t brs                 : 1; /* [18] */
      __IO uint32_t xlf                 : 1; /* [19] */
      __IO uint32_t rmf                 : 1; /* [20] */
      __IO uint32_t sec                 : 1; /* [21] */
      __IO uint32_t reserved2           : 2; /* [23:22] */
      __IO uint32_t koer                : 3; /* [26:24] */
      __IO uint32_t esi                 : 1; /* [27] */
      __IO uint32_t lbf                 : 1; /* [28] */
      __IO uint32_t reserved3           : 3; /* [31:29] */    
    } tbfmt_bit;
  };
  
  /**
    * @brief can tbtyp register, offset:0xD4
    */
  union 
  {
    __IO uint32_t tbtyp;
    struct
    {
      __IO uint32_t sdt                 : 8; /* [7:0] */
      __IO uint32_t vcid                : 8; /* [15:8] */
      __IO uint32_t reserved1           : 8; /* [23:16] */
      __IO uint32_t handle              : 8; /* [31:24] */    
    } tbtyp_bit;
  };
  
  /**
    * @brief can tbacf register, offset:0xD8
    */
  __IO uint32_t tbacf;
  
  /**
    * @brief can tbdat register, offset:0xDC-0x118
    */
  __IO uint32_t tbdat[16];
  
  /**
    * @brief can reserved register, offset:0x11C-0x120
    */
  __IO uint32_t reserved6[2];
  
  /**
    * @brief can llcformat register, offset:0x124
    */
  __IO uint32_t llcformat;
  
  /**
    * @brief can llcsize register, offset:0x128
    */
  union
  {
    __IO uint32_t llcsize;
    struct
    {
      __IO uint32_t llcpbytes           : 16; /* [15:0] */
      __IO uint32_t llcaot              : 16; /* [31:16] */
    } llcsize_bit;
  };
  
  /**
    * @brief can reserved register, offset:0x12C-0x13C
    */
  __IO uint32_t reserved7[5];
  
  /**
    * @brief can inten register, offset:0x140
    */
  union
  {
    __IO uint32_t inten;
    struct
    {
      __IO uint32_t aien                : 1; /* [0] */
      __IO uint32_t eien                : 1; /* [1] */
      __IO uint32_t tsien               : 1; /* [2] */
      __IO uint32_t tpien               : 1; /* [3] */
      __IO uint32_t rafien              : 1; /* [4] */ 
      __IO uint32_t rfien               : 1; /* [5] */      
      __IO uint32_t roien               : 1; /* [6] */
      __IO uint32_t rien                : 1; /* [7] */
      __IO uint32_t beien               : 1; /* [8] */
      __IO uint32_t alien               : 1; /* [9] */
      __IO uint32_t epien               : 1; /* [10] */
      __IO uint32_t ttien               : 1; /* [11] */
      __IO uint32_t teien               : 1; /* [12] */
      __IO uint32_t wtien               : 1; /* [13] */
      __IO uint32_t reserved1           : 18; /* [31:14] */
    } inten_bit;
  }; 
} can_type;  

#define CAN1                            ((can_type *) CAN1_BASE)

/** @defgroup CAN_exported_functions
  * @{
  */

void can_reset(can_type* can_x);
void can_software_reset(can_type* can_x, confirm_state new_state);
#ifdef SUPPORT_CAN_FD
void can_fd_iso_mode_enable(can_type* can_x, confirm_state new_state);
#endif
void can_mode_set(can_type* can_x, can_mode_type mode_selection);
error_status can_standby_mode_enable(can_type* can_x, confirm_state new_state);
void can_restricted_operation_enable(can_type* can_x, confirm_state new_state);
void can_bittime_default_para_init(can_bittime_type* can_bittime_struct);
void can_bittime_set(can_type* can_x, can_bittime_type* can_bittime_struct);
void can_retransmission_limit_set(can_type* can_x, can_retransmission_times_type re_trans_times);
void can_rearbitration_limit_set(can_type* can_x, can_rearbitration_times_type re_arbi_times);
void can_timestamp_enable(can_type* can_x, confirm_state new_state);
void can_timestamp_position_set(can_type* can_x, can_timestamp_position_type timestamp_position);

uint32_t can_transmit_timestamp_get(can_type* can_x);
error_status can_txbuf_write(can_type* can_x, can_txbuf_select_type txbuf_type, can_txbuf_type* can_txbuf_struct);
error_status can_txbuf_transmit(can_type* can_x, can_txbuf_transmit_type transmit_type);
void can_transmit_abort(can_type* can_x, can_abort_transmit_type abort_type);
void can_stb_transmit_mode_set(can_type* can_x, can_stb_transmit_mode_type stb_transmit_mode);
can_stb_status_type can_stb_status_get(can_type* can_x);
void can_transmit_status_get(can_type* can_x, can_transmit_status_type* transmit_status_struct);
error_status can_stb_clear(can_type* can_x, can_clear_stb_type clear_type);

void can_rxbuf_overflow_mode_set(can_type* can_x, can_rxbuf_overflow_mode_type rxbuf_overflow_mode);
void can_receive_all_enable(can_type* can_x, confirm_state new_state);
error_status can_rxbuf_read(can_type* can_x, can_rxbuf_type* can_rxbuf_struct);
error_status can_rxbuf_release(can_type* can_x);
can_rxbuf_status_type can_rxbuf_status_get(can_type* can_x);

void can_filter_enable(can_type* can_x, can_filter_type filter_number, confirm_state new_state);
void can_filter_default_para_init(can_filter_config_type* filter_config_struct);
void can_filter_set(can_type* can_x, can_filter_type filter_number, can_filter_config_type* filter_config_struct);

uint8_t can_arbitration_lost_position_get(can_type* can_x);
void can_rxbuf_warning_set(can_type* can_x, uint8_t warning_value);
void can_error_warning_set(can_type* can_x, uint8_t warning_value);
can_error_type can_kind_error_get(can_type* can_x);
uint8_t can_receive_error_counter_get(can_type* can_x);
uint8_t can_transmit_error_counter_get(can_type* can_x);
flag_status can_busoff_get(can_type* can_x);
void can_busoff_reset(can_type* can_x);

void can_ttcan_ref_message_set(can_type* can_x, can_identifier_type id_type, uint32_t id);
void can_ttcan_timer_div_set(can_type* can_x, can_ttcan_timer_div_type div_value); 
void can_ttcan_enable(can_type* can_x, confirm_state new_state); 
void can_ttcan_trigger_type_set(can_type* can_x, can_ttcan_trigger_type trigger_type);
void can_ttcan_trigger_set(can_type* can_x, uint16_t trigger_time);
void can_ttcan_watch_trigger_set(can_type* can_x, uint16_t watch_trigger_time);
void can_ttcan_transmit_window_set(can_type* can_x, uint8_t window_ticks);
void can_ttcan_txbuf_enable(can_type* can_x, confirm_state new_state);
void can_ttcan_txbuf_status_set(can_type* can_x, can_ttcan_txbuf_type txbuf_number, can_ttcan_txbuf_status_type status_type);
can_ttcan_txbuf_status_type can_ttcan_txbuf_status_get(can_type* can_x, can_ttcan_txbuf_type txbuf_number);
void can_ttcan_txbuf_transmit_set(can_type* can_x, can_ttcan_txbuf_type txbuf_number);
error_status can_ttcan_txbuf_write(can_type* can_x, can_ttcan_txbuf_type txbuf_number, can_txbuf_type* can_txbuf_struct);

void can_interrupt_enable(can_type* can_x, uint32_t can_int, confirm_state new_state);
flag_status can_flag_get(can_type* can_x, uint32_t can_flag);
flag_status can_interrupt_flag_get(can_type* can_x, uint32_t can_flag);
void can_flag_clear(can_type* can_x, uint32_t can_flag);

/*
note: 
the following functions is only support can-fd.
 - can_fd_iso_mode_enable
the following functions is support classic-can and can-fd.
 - can_bittime_default_para_init
 - can_bittime_set
 - can_txbuf_write
 - can_rxbuf_read
 - can_filter_default_para_init
 - can_filter_set 
 - can_ttcan_txbuf_write
*/

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
