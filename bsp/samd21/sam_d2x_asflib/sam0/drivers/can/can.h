/**
 * \file
 *
 * \brief SAM Control Area Network (CAN) Low Level Driver
 *
 * Copyright (C) 2015-2016 Atmel Corporation. All rights reserved.
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

#ifndef CAN_H_INCLUDED
#define CAN_H_INCLUDED

#include <compiler.h>
#include <system.h>
#include <conf_can.h>

/**
 * \name Message RAM
 * @{
 */

/* -------- CAN_RX_ELEMENT_R0 : (CAN RX element: 0x00) (R/W 32) Rx Element R0 Configuration -------- */
typedef union {
  struct {
    uint32_t ID:29;            /*!< bit:  0..28  Identifier */
    uint32_t RTR:1;            /*!< bit:  29     Remote Transmission Request */
    uint32_t XTD:1;            /*!< bit:  30     Extended Identifier */
    uint32_t ESI:1;            /*!< bit:  31     Error State Indicator */
  } bit;                       /*!< Structure used for bit access */
  uint32_t reg;                /*!< Type used for register access */
} CAN_RX_ELEMENT_R0_Type;

#define CAN_RX_ELEMENT_R0_ID_Pos          0
#define CAN_RX_ELEMENT_R0_ID_Msk          (0x1FFFFFFFul << CAN_RX_ELEMENT_R0_ID_Pos)
#define CAN_RX_ELEMENT_R0_ID(value)       ((CAN_RX_ELEMENT_R0_ID_Msk & ((value) << CAN_RX_ELEMENT_R0_ID_Pos)))
#define CAN_RX_ELEMENT_R0_RTR_Pos         29
#define CAN_RX_ELEMENT_R0_RTR             (0x1ul << CAN_RX_ELEMENT_R0_RTR_Pos)
#define CAN_RX_ELEMENT_R0_XTD_Pos         30
#define CAN_RX_ELEMENT_R0_XTD             (0x1ul << CAN_RX_ELEMENT_R0_XTD_Pos)
#define CAN_RX_ELEMENT_R0_ESI_Pos         31
#define CAN_RX_ELEMENT_R0_ESI             (0x1ul << CAN_RX_ELEMENT_R0_ESI_Pos)

/* -------- CAN_RX_ELEMENT_R1 : (CAN RX element: 0x01) (R/W 32) Rx Element R1 Configuration -------- */
typedef union {
  struct {
    uint32_t RXTS:16;          /*!< bit: 0..15   Rx Timestamp */
    uint32_t DLC:4;            /*!< bit: 16..19  Data Length Code */
    uint32_t BRS:1;            /*!< bit: 20      Bit Rate Switch */
    uint32_t FDF:1;            /*!< bit: 21      FD Format */
    uint32_t :2;               /*!< bit: 22..23  Reserved */
    uint32_t FIDX:7;           /*!< bit: 24..30  Filter Index */
    uint32_t ANMF:1;           /*!< bit: 31      Accepted Non-matching Frame */
  } bit;                       /*!< Structure used for bit  access */
  uint32_t reg;                /*!< Type used for register access */
} CAN_RX_ELEMENT_R1_Type;

#define CAN_RX_ELEMENT_R1_RXTS_Pos        0
#define CAN_RX_ELEMENT_R1_RXTS_Msk        (0xFFFFul << CAN_RX_ELEMENT_R1_RXTS_Pos)
#define CAN_RX_ELEMENT_R1_RXTS(value)     ((CAN_RX_ELEMENT_R1_RXTS_Msk & ((value) << CAN_RX_ELEMENT_R1_RXTS_Pos)))
#define CAN_RX_ELEMENT_R1_DLC_Pos         16
#define CAN_RX_ELEMENT_R1_DLC_Msk         (0xFul << CAN_RX_ELEMENT_R1_DLC_Pos)
#define CAN_RX_ELEMENT_R1_DLC(value)      ((CAN_RX_ELEMENT_R1_DLC_Msk & ((value) << CAN_RX_ELEMENT_R1_DLC_Pos)))
#define CAN_RX_ELEMENT_R1_BRS_Pos         20
#define CAN_RX_ELEMENT_R1_BRS             (0x1ul << CAN_RX_ELEMENT_R1_BRS_Pos)
#define CAN_RX_ELEMENT_R1_FDF_Pos         21
#define CAN_RX_ELEMENT_R1_FDF             (0x1ul << CAN_RX_ELEMENT_R1_FDF_Pos)
#define CAN_RX_ELEMENT_R1_FIDX_Pos        24
#define CAN_RX_ELEMENT_R1_FIDX_Msk        (0x7Ful << CAN_RX_ELEMENT_R1_FIDX_Pos)
#define CAN_RX_ELEMENT_R1_FIDX(value)     ((CAN_RX_ELEMENT_R1_FIDX_Msk & ((value) << CAN_RX_ELEMENT_R1_FIDX_Pos)))
#define CAN_RX_ELEMENT_R1_ANMF_Pos        31
#define CAN_RX_ELEMENT_R1_ANMF            (0x1ul << CAN_RX_ELEMENT_R1_ANMF_Pos)

/**
 * \brief CAN receive element structure for buffer.
 */
struct can_rx_element_buffer {
	__IO CAN_RX_ELEMENT_R0_Type R0;
	__IO CAN_RX_ELEMENT_R1_Type R1;
	uint8_t data[CONF_CAN_ELEMENT_DATA_SIZE];
};

/**
 * \brief CAN receive element structure for FIFO 0.
 */
struct can_rx_element_fifo_0 {
	__IO CAN_RX_ELEMENT_R0_Type R0;
	__IO CAN_RX_ELEMENT_R1_Type R1;
	uint8_t data[CONF_CAN_ELEMENT_DATA_SIZE];
};

/**
 * \brief CAN receive element structure for FIFO 1.
 */
struct can_rx_element_fifo_1 {
	__IO CAN_RX_ELEMENT_R0_Type R0;
	__IO CAN_RX_ELEMENT_R1_Type R1;
	uint8_t data[CONF_CAN_ELEMENT_DATA_SIZE];
};

/* -------- CAN_TX_ELEMENT_T0 : (CAN TX element: 0x00) (R/W 32) Tx Element T0 Configuration -------- */
typedef union {
  struct {
    uint32_t ID:29;            /*!< bit:  0..28  Identifier */
    uint32_t RTR:1;            /*!< bit:  29     Remote Transmission Request */
    uint32_t XTD:1;            /*!< bit:  30     Extended Identifier */
    uint32_t ESI:1;            /*!< bit:  31     Error State Indicator */
  } bit;                       /*!< Structure used for bit  access */
  uint32_t reg;                /*!< Type used for register access */
} CAN_TX_ELEMENT_T0_Type;

#define CAN_TX_ELEMENT_T0_EXTENDED_ID_Pos          0
#define CAN_TX_ELEMENT_T0_EXTENDED_ID_Msk          (0x1FFFFFFFul << CAN_TX_ELEMENT_T0_EXTENDED_ID_Pos)
#define CAN_TX_ELEMENT_T0_EXTENDED_ID(value)       ((CAN_TX_ELEMENT_T0_EXTENDED_ID_Msk & ((value) << CAN_TX_ELEMENT_T0_EXTENDED_ID_Pos)))
#define CAN_TX_ELEMENT_T0_STANDARD_ID_Pos          18
#define CAN_TX_ELEMENT_T0_STANDARD_ID_Msk          (0x7FFul << CAN_TX_ELEMENT_T0_STANDARD_ID_Pos)
#define CAN_TX_ELEMENT_T0_STANDARD_ID(value)       ((CAN_TX_ELEMENT_T0_STANDARD_ID_Msk & ((value) << CAN_TX_ELEMENT_T0_STANDARD_ID_Pos)))
#define CAN_TX_ELEMENT_T0_RTR_Pos         29
#define CAN_TX_ELEMENT_T0_RTR             (0x1ul << CAN_TX_ELEMENT_T0_RTR_Pos)
#define CAN_TX_ELEMENT_T0_XTD_Pos         30
#define CAN_TX_ELEMENT_T0_XTD             (0x1ul << CAN_TX_ELEMENT_T0_XTD_Pos)
#define CAN_TX_ELEMENT_T0_ESI_Pos         31
#define CAN_TX_ELEMENT_T0_ESI             (0x1ul << CAN_TX_ELEMENT_T0_ESI_Pos)

/* -------- CAN_TX_ELEMENT_T1 : (CAN TX element: 0x01) (R/W 32) Tx Element T1 Configuration -------- */
typedef union {
  struct {
    uint32_t :16;              /*!< bit: 0..15   Reserved */
    uint32_t DLC:4;            /*!< bit: 16..19  Data Length Code */
    uint32_t BRS:1;            /*!< bit: 20      Bit Rate Switch */
    uint32_t FDF:1;            /*!< bit: 21      FD Format */
    uint32_t :1;               /*!< bit: 22      Reserved */
    uint32_t EFC:1;            /*!< bit: 23      Event FIFO Control */
    uint32_t MM:8;             /*!< bit: 24..31  Message Marker */
  } bit;                       /*!< Structure used for bit  access */
  uint32_t reg;                /*!< Type used for register access */
} CAN_TX_ELEMENT_T1_Type;

#define CAN_TX_ELEMENT_T1_DLC_Pos         16
#define CAN_TX_ELEMENT_T1_DLC_Msk         (0xFul << CAN_TX_ELEMENT_T1_DLC_Pos)
#define CAN_TX_ELEMENT_T1_DLC(value)      ((CAN_TX_ELEMENT_T1_DLC_Msk & ((value) << CAN_TX_ELEMENT_T1_DLC_Pos)))
#define   CAN_TX_ELEMENT_T1_DLC_DATA8_Val        0x8ul  /**< \brief (CAN_RXESC) 8 byte data field */
#define   CAN_TX_ELEMENT_T1_DLC_DATA12_Val       0x9ul  /**< \brief (CAN_RXESC) 12 byte data field */
#define   CAN_TX_ELEMENT_T1_DLC_DATA16_Val       0xAul  /**< \brief (CAN_RXESC) 16 byte data field */
#define   CAN_TX_ELEMENT_T1_DLC_DATA20_Val       0xBul  /**< \brief (CAN_RXESC) 20 byte data field */
#define   CAN_TX_ELEMENT_T1_DLC_DATA24_Val       0xCul  /**< \brief (CAN_RXESC) 24 byte data field */
#define   CAN_TX_ELEMENT_T1_DLC_DATA32_Val       0xDul  /**< \brief (CAN_RXESC) 32 byte data field */
#define   CAN_TX_ELEMENT_T1_DLC_DATA48_Val       0xEul  /**< \brief (CAN_RXESC) 48 byte data field */
#define   CAN_TX_ELEMENT_T1_DLC_DATA64_Val       0xFul  /**< \brief (CAN_RXESC) 64 byte data field */
#define CAN_TX_ELEMENT_T1_BRS_Pos         20
#define CAN_TX_ELEMENT_T1_BRS             (0x1ul << CAN_TX_ELEMENT_T1_BRS_Pos)
#define CAN_TX_ELEMENT_T1_FDF_Pos         21
#define CAN_TX_ELEMENT_T1_FDF             (0x1ul << CAN_TX_ELEMENT_T1_FDF_Pos)
#define CAN_TX_ELEMENT_T1_EFC_Pos         23
#define CAN_TX_ELEMENT_T1_EFC             (0x1ul << CAN_TX_ELEMENT_T1_EFC_Pos)
#define CAN_TX_ELEMENT_T1_MM_Pos          24
#define CAN_TX_ELEMENT_T1_MM_Msk          (0xFFul << CAN_TX_ELEMENT_T1_MM_Pos)
#define CAN_TX_ELEMENT_T1_MM(value)       ((CAN_TX_ELEMENT_T1_MM_Msk & ((value) << CAN_TX_ELEMENT_T1_MM_Pos)))

/**
 * \brief CAN transfer element structure.
 *
 *  Common element structure for transfer buffer and FIFO/QUEUE.
 */
struct can_tx_element {
	__IO CAN_TX_ELEMENT_T0_Type T0;
	__IO CAN_TX_ELEMENT_T1_Type T1;
	uint8_t data[CONF_CAN_ELEMENT_DATA_SIZE];
};

/* -------- CAN_TX_EVENT_ELEMENT_E0 : (CAN TX event element: 0x00) (R/W 32) Tx Event Element E0 Configuration -------- */
typedef union {
  struct {
    uint32_t ID:29;            /*!< bit: 0..28  Identifier */
    uint32_t RTR:1;            /*!< bit: 29     Remote Transmission Request */
    uint32_t XTD:1;            /*!< bit: 30     Extended Identifier */
    uint32_t ESI:1;            /*!< bit: 31     Error State Indicator */
  } bit;                       /*!< Structure used for bit  access */
  uint32_t reg;                /*!< Type used for register access */
} CAN_TX_EVENT_ELEMENT_E0_Type;

#define CAN_TX_EVENT_ELEMENT_E0_ID_Pos          0
#define CAN_TX_EVENT_ELEMENT_E0_ID_Msk          (0x1FFFFFFFul << CAN_TX_EVENT_ELEMENT_E0_ID_Pos)
#define CAN_TX_EVENT_ELEMENT_E0_ID(value)       ((CAN_TX_EVENT_ELEMENT_E0_ID_Msk & ((value) << CAN_TX_EVENT_ELEMENT_E0_ID_Pos)))
#define CAN_TX_EVENT_ELEMENT_E0_RTR_Pos         29
#define CAN_TX_EVENT_ELEMENT_E0_RTR             (0x1ul << CAN_TX_EVENT_ELEMENT_E0_RTR_Pos)
#define CAN_TX_EVENT_ELEMENT_E0_XTD_Pos         30
#define CAN_TX_EVENT_ELEMENT_E0_XTD             (0x1ul << CAN_TX_EVENT_ELEMENT_E0_XTD_Pos)
#define CAN_TX_EVENT_ELEMENT_E0_ESI_Pos         31
#define CAN_TX_EVENT_ELEMENT_E0_ESI             (0x1ul << CAN_TX_EVENT_ELEMENT_E0_ESI_Pos)

/* -------- CAN_TX_EVENT_ELEMENT_E1 : (CAN TX event element: 0x01) (R/W 32) Tx Event Element E1 Configuration -------- */
typedef union {
  struct {
    uint32_t TXTS:16;          /*!< bit: 0..15   Tx Timestamp */
    uint32_t DLC:4;            /*!< bit: 16..19  Data Length Code */
    uint32_t BRS:1;            /*!< bit: 20      Bit Rate Switch */
    uint32_t FDF:1;            /*!< bit: 21      FD Format */
    uint32_t ET:2;             /*!< bit: 22..23  Event Type */
    uint32_t MM:8;             /*!< bit: 24..31  Message Marker */
  } bit;                       /*!< Structure used for bit  access */
  uint32_t reg;                /*!< Type used for register access */
} CAN_TX_EVENT_ELEMENT_E1_Type;

#define CAN_TX_EVENT_ELEMENT_E1_TXTS_Pos        0
#define CAN_TX_EVENT_ELEMENT_E1_TXTS_Msk        (0xFFFFul << CAN_TX_EVENT_ELEMENT_E1_TXTS_Pos)
#define CAN_TX_EVENT_ELEMENT_E1_TXTS(value)     ((CAN_TX_EVENT_ELEMENT_E1_TXTS_Msk & ((value) << CAN_TX_EVENT_ELEMENT_E1_TXTS_Pos)))
#define CAN_TX_EVENT_ELEMENT_E1_DLC_Pos         16
#define CAN_TX_EVENT_ELEMENT_E1_DLC_Msk         (0xFul << CAN_TX_EVENT_ELEMENT_E1_DLC_Pos)
#define CAN_TX_EVENT_ELEMENT_E1_DLC(value)      ((CAN_TX_EVENT_ELEMENT_E1_DLC_Msk & ((value) << CAN_TX_EVENT_ELEMENT_E1_DLC_Pos)))
#define CAN_TX_EVENT_ELEMENT_E1_BRS_Pos         20
#define CAN_TX_EVENT_ELEMENT_E1_BRS             (0x1ul << CAN_TX_EVENT_ELEMENT_E1_BRS_Pos)
#define CAN_TX_EVENT_ELEMENT_E1_FDF_Pos         21
#define CAN_TX_EVENT_ELEMENT_E1_FDF             (0x1ul << CAN_TX_EVENT_ELEMENT_E1_FDF_Pos)
#define CAN_TX_EVENT_ELEMENT_E1_ET_Pos          22
#define CAN_TX_EVENT_ELEMENT_E1_ET_Msk          (0x3ul << CAN_TX_EVENT_ELEMENT_E1_ET_Pos)
#define CAN_TX_EVENT_ELEMENT_E1_ET(value)       ((CAN_TX_EVENT_ELEMENT_E1_ET_Msk & ((value) << CAN_TX_EVENT_ELEMENT_E1_ET_Pos)))
#define CAN_TX_EVENT_ELEMENT_E1_MM_Pos          24
#define CAN_TX_EVENT_ELEMENT_E1_MM_Msk          (0xFFul << CAN_TX_EVENT_ELEMENT_E1_MM_Pos)
#define CAN_TX_EVENT_ELEMENT_E1_MM(value)       ((CAN_TX_EVENT_ELEMENT_E1_MM_Msk & ((value) << CAN_TX_EVENT_ELEMENT_E1_MM_Pos)))

/**
 * \brief CAN transfer event  FIFO element structure.
 *
 *  Common element structure for transfer event FIFO.
 */
struct can_tx_event_element {
	__IO CAN_TX_EVENT_ELEMENT_E0_Type E0;
	__IO CAN_TX_EVENT_ELEMENT_E1_Type E1;
};

/* -------- CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0 : (CAN standard message ID filter element: 0x00) (R/W 32) Standard Message ID Filter Element S0 Configuration -------- */
typedef union {
  struct {
    uint32_t SFID2:11;         /*!< bit: 0..10   Standard Filter ID 2 */
    uint32_t :5;               /*!< bit: 11..15  Reserved */
    uint32_t SFID1:11;         /*!< bit: 16..26  Standard Filter ID 1 */
    uint32_t SFEC:3;           /*!< bit: 27..29  Standard Filter Element Configuration */
    uint32_t SFT:2;            /*!< bit: 30..31  Standard Filter Type */
  } bit;                       /*!< Structure used for bit  access */
  uint32_t reg;                /*!< Type used for register access */
} CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_Type;

#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID2_Pos          0
#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID2_Msk          (0x7FFul << CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID2_Pos)
#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID2(value)       ((CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID2_Msk & ((value) << CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID2_Pos)))
#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID1_Pos          16
#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID1_Msk          (0x7FFul << CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID1_Pos)
#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID1(value)       ((CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID1_Msk & ((value) << CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID1_Pos)))
#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_Pos           27
#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_Msk           (0x7ul << CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_Pos)
#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC(value)        ((CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_Msk & ((value) << CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_Pos)))
#define   CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_DISABLE_Val     0
#define   CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_STF0M_Val       1
#define   CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_STF1M_Val       2
#define   CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_REJECT_Val      3
#define   CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_PRIORITY_Val    4
#define   CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_PRIF0M_Val      5
#define   CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_PRIF1M_Val      6
#define   CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_STRXBUF_Val     7
#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT_Pos            30
#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT_Msk            (0x3ul << CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT_Pos)
#define CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT(value)         ((CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT_Msk & ((value) << CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT_Pos)))
#define   CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT_RANGE          CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT(0)
#define   CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT_DUAL           CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT(1)
#define   CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT_CLASSIC        CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT(2)

/**
 * \brief CAN standard message ID filter element structure.
 *
 *  Common element structure for standard message ID filter element.
 */
struct can_standard_message_filter_element {
	__IO CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_Type S0;
};

/* -------- CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0 : (CAN extended message ID filter element: 0x00) (R/W 32) Extended Message ID Filter Element F0 Configuration -------- */
typedef union {
  struct {
    uint32_t EFID1:29;         /*!< bit: 0..28   Extended Filter ID 1 */
    uint32_t EFEC:3;           /*!< bit: 29..31  Extended Filter Element Configuration */
  } bit;                       /*!< Structure used for bit  access */
  uint32_t reg;                /*!< Type used for register access */
} CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_Type;

#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFID1_Pos          0
#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFID1_Msk          (0x1FFFFFFFul << CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFID1_Pos)
#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFID1(value)       ((CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFID1_Msk & ((value) << CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFID1_Pos)))
#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_Pos           29
#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_Msk           (0x7ul << CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_Pos)
#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC(value)        ((CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_Msk & ((value) << CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_Pos)))
#  define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_DISABLE_Val       0
#  define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_STF0M_Val         1
#  define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_STF1M_Val         2
#  define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_REJECT_Val        3
#  define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_PRIORITY_Val      4
#  define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_PRIF0M_Val        5
#  define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_PRIF1M_Val        6
#  define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_STRXBUF_Val       7

/* -------- CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1 : (CAN extended message ID filter element: 0x01) (R/W 32) Extended Message ID Filter Element F1 Configuration -------- */
typedef union {
  struct {
    uint32_t EFID2:29;         /*!< bit: 0..28  Extended Filter ID 2 */
    uint32_t :1;               /*!< bit: 29     Reserved */
    uint32_t EFT:2;            /*!< bit: 30..31 Extended Filter Type */
  } bit;                       /*!< Structure used for bit  access */
  uint32_t reg;                /*!< Type used for register access */
} CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_Type;

#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFID2_Pos          0
#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFID2_Msk          (0x1FFFFFFFul << CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFID2_Pos)
#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFID2(value)       ((CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFID2_Msk & ((value) << CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFID2_Pos)))
#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_Pos            30
#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_Msk            (0x3ul << CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_Pos)
#define CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT(value)         ((CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_Msk & ((value) << CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_Pos)))
#define   CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_RANGEM       CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT(0)
#define   CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_DUAL         CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT(1)
#define   CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_CLASSIC      CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT(2)
#define   CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_RANGE        CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT(3)

/**
 * \brief CAN extended message ID filter element structure.
 *
 *  Common element structure for extended message ID filter element.
 */
struct can_extended_message_filter_element {
	__IO CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_Type F0;
	__IO CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_Type F1;
};
/** @} */

/**
 * \defgroup asfdoc_sam0_can_group SAM Control Area Network (CAN) Low Level Driver
 *
 * This driver for Atmel® | SMART SAM devices provides an low level
 * interface for the configuration and management of the device's
 * Control Area Network functionality.
 *
 * \note  Since "The Control Area Network (CAN) performs communication according
 * to ISO 11898-1 (Bosch CAN specification 2.0 part A,B) and to Bosch CAN FD
 * specification V1.0", the driver is focus on the MAC layer and try to offer
 * the APIs which can be used by upper application layer.
 *
 * For storage of Rx/Tx messages and for storage of the filter configuration,
 * a message RAM is needed to the CAN module. In this driver, the message RAM
 * is static allocated, the related setting is defined and can be changed in
 * the module configuration file "conf_can.h".
 *
 * The following peripherals are used by this module:
 *  - CAN (Control Area Network)
 *
 * The following devices can use this module:
 *  - SAM C21
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_can_prerequisites
 *  - \ref asfdoc_sam0_can_module_overview
 *  - \ref asfdoc_sam0_can_special_considerations
 *  - \ref asfdoc_sam0_can_extra_info
 *  - \ref asfdoc_sam0_can_examples
 *  - \ref asfdoc_sam0_can_api_overview
 *
 *
 * \section asfdoc_sam0_can_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_can_module_overview Module Overview
 *
 * This driver provides an interface for the Control Area Network Controller
 * functions on the device.
 *
 *
 * \section asfdoc_sam0_can_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 *
 * \section asfdoc_sam0_can_extra_info Extra Information
 *
 * For extra information see \ref asfdoc_sam0_can_extra. This includes:
 *  - \ref asfdoc_sam0_can_extra_acronyms
 *  - \ref asfdoc_sam0_can_extra_dependencies
 *  - \ref asfdoc_sam0_can_extra_errata
 *  - \ref asfdoc_sam0_can_extra_history
 *
 *
 * \section asfdoc_sam0_can_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_can_exqsg.
 *
 *
 * \section asfdoc_sam0_can_api_overview API Overview
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name Module Setting
 * @{
 */

/**
 * \brief Can time out modes.
 */
enum can_timeout_mode {
	/** Continuous operation. */
	CAN_TIMEOUT_CONTINUES = CAN_TOCC_TOS_CONT,
	/** Timeout controlled by TX Event FIFO. */
	CAN_TIMEOUT_TX_EVEN_FIFO = CAN_TOCC_TOS_TXEF,
	/** Timeout controlled by Rx FIFO 0. */
	CAN_TIMEOUT_RX_FIFO_0 = CAN_TOCC_TOS_RXF0,
	/** Timeout controlled by Rx FIFO 1. */
	CAN_TIMEOUT_RX_FIFO_1 = CAN_TOCC_TOS_RXF1,
};

/**
 * \brief Can nonmatching frames action.
 */
enum can_nonmatching_frames_action {
	/** Accept in Rx FIFO 0. */
	CAN_NONMATCHING_FRAMES_FIFO_0,
	/** Accept in Rx FIFO 1. */
	CAN_NONMATCHING_FRAMES_FIFO_1,
	/** Reject. */
	CAN_NONMATCHING_FRAMES_REJECT,
};

/**
 * \brief CAN software device instance structure.
 *
 * CAN software instance structure, used to retain software state information
 * of an associated hardware module instance.
 *
 * \note The fields of this structure should not be altered by the user
 *       application; they are reserved for module-internal use only.
 */
struct can_module {
#if !defined(__DOXYGEN__)
	/** Pointer to CAN hardware module. */
	Can *hw;
#endif
};

/**
 * \brief CAN configuration structure.
 *
 * Configuration structure for an CAN instance. This structure should be
 * initialized by the \ref can_get_config_defaults()
 * function before being modified by the user application.
 */
struct can_config {
	/** GCLK generator used to clock the peripheral. */
	enum gclk_generator clock_source;
	/** CAN run in standby control. */
	bool run_in_standby;
	/** Start value of the Message RAM Watchdog Counter */
	uint8_t watchdog_configuration;
	/** Transmit Pause. */
	bool transmit_pause;
	/** Edge Filtering during Bus Integration. */
	bool edge_filtering;
	/** Protocol Exception Handling. */
	bool protocol_exception_handling;
	/** Automatic Retransmission. */
	bool automatic_retransmission;
	/** Clock Stop Request. */
	bool clock_stop_request;
	/** Clock Stop Acknowledge. */
	bool clock_stop_acknowledge;
	/** Timestamp Counter Prescaler: 0x0-0xF */
	uint8_t timestamp_prescaler;
	/** Timeout Period. */
	uint16_t timeout_period;
	/** Timeout Mode. */
	enum can_timeout_mode timeout_mode;
	/** Timeout enable. */
	bool timeout_enable;
	/** Transceiver Delay Compensation enable. */		
	bool tdc_enable;
	/** Transmitter Delay Compensation Offset : 0x0-0x7F */
	uint8_t delay_compensation_offset;
	/** Transmitter Delay Compensation Filter Window Length : 0x0-0x7F */
	uint8_t delay_compensation_filter_window_length;
	/** Nonmatching frames action for standard frames. */
	enum can_nonmatching_frames_action nonmatching_frames_action_standard;
	/** Nonmatching frames action for extended frames. */
	enum can_nonmatching_frames_action nonmatching_frames_action_extended;
	/** Reject Remote Standard Frames. */
	bool remote_frames_standard_reject;
	/** Reject Remote Extended Frames. */
	bool remote_frames_extended_reject;
	/** Extended ID Mask: 0x0-0x1FFFFFFF. */
	uint32_t extended_id_mask;
	/** Rx FIFO 0 Operation Mode. */
	bool rx_fifo_0_overwrite;
	/** Rx FIFO 0 Watermark: 1-64, other value disable it. */
	uint8_t rx_fifo_0_watermark;
	/** Rx FIFO 1 Operation Mode. */
	bool rx_fifo_1_overwrite;
	/** Rx FIFO 1 Watermark: 1-64, other value disable it. */
	uint8_t rx_fifo_1_watermark;
	/** Tx FIFO/Queue Mode, 0 for FIFO and 1 for Queue. */
	bool tx_queue_mode;
	/** Tx Event FIFO Watermark: 1-32, other value disable it. */
	uint8_t tx_event_fifo_watermark;

};

/**
 * \brief Initializes an CAN configuration structure to defaults
 *
 * Initializes a given CAN configuration struct to a set of known default
 * values. This function should be called on any new instance of the
 * configuration struct before being modified by the user application.
 *
 * The default configuration is as follows:
 *  \li GCLK generator 8 (GCLK main) clock source
 *  \li Not run in standby mode
 *  \li Disable Watchdog
 *  \li Transmit pause enabled
 *  \li Edge filtering during bus integration enabled
 *  \li Protocol exception handling enabled
 *  \li Automatic retransmission enabled
 *  \li Clock stop request disabled
 *  \li Clock stop acknowledge disabled
 *  \li Timestamp Counter Prescaler 1
 *  \li Timeout Period with 0xFFFF
 *  \li Timeout Mode: Continuous operation
 *  \li Disable Timeout
 *  \li Transmitter Delay Compensation Offset is 0
 *  \li Transmitter Delay Compensation Filter Window Length is 0
 *  \li Reject nonmatching standard frames
 *  \li Reject nonmatching extended frames
 *  \li Reject remote standard frames
 *  \li Reject remote extended frames
 *  \li Extended ID Mask is 0x1FFFFFFF
 *  \li Rx FIFO 0 Operation Mode: overwrite
 *  \li Disable Rx FIFO 0 Watermark
 *  \li Rx FIFO 1 Operation Mode: overwrite
 *  \li Disable Rx FIFO 1 Watermark
 *  \li Tx FIFO/Queue Mode: FIFO
 *  \li Disable Tx Event FIFO Watermark
 *
 * \param[out] config  Pointer to configuration struct to initialize to
 *                     default values
 */
static inline void can_get_config_defaults(
		struct can_config *const config)
{
	/* Sanity check arguments */
	Assert(config);

	/* Default configuration values */
	config->clock_source = GCLK_GENERATOR_8;
	config->run_in_standby = false;
	config->watchdog_configuration = 0x00;
	config->transmit_pause = true;
	config->edge_filtering = true;
	config->protocol_exception_handling = true;
	config->automatic_retransmission = true;
	config->clock_stop_request = false;
	config->clock_stop_acknowledge = false;
	config->timestamp_prescaler = 0;
	config->timeout_period = 0xFFFF;
	config->timeout_mode = CAN_TIMEOUT_CONTINUES;
	config->timeout_enable = false;
	config->tdc_enable = false;
	config->delay_compensation_offset = 0;
	config->delay_compensation_filter_window_length = 0;
	config->nonmatching_frames_action_standard = CAN_NONMATCHING_FRAMES_REJECT;
	config->nonmatching_frames_action_extended = CAN_NONMATCHING_FRAMES_REJECT;
	config->remote_frames_standard_reject = true;
	config->remote_frames_extended_reject = true;
	config->extended_id_mask = 0x1FFFFFFF;
	config->rx_fifo_0_overwrite = true;
	config->rx_fifo_0_watermark = 0;
	config->rx_fifo_1_overwrite = true;
	config->rx_fifo_1_watermark = 0;
	config->tx_queue_mode = false;
	config->tx_event_fifo_watermark = 0;
}


/**
 * \brief Initializes CAN module.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in]  hw          Pointer to the CAN module instance
 * \param[in]  config      Pointer to the configuration struct
 */
void can_init(struct can_module *const module_inst, Can *hw,
		struct can_config *config);

/**
 * \brief Set CAN baudrate.
 *
 * \param[in]  hw          Pointer to the CAN module instance
 * \param[in]  baudrate    CAN baudrate
 */
void can_set_baudrate(Can *hw, uint32_t baudrate);

/**
 * \brief Set CAN_FD baudrate.
 *
 * \param[in]  hw          Pointer to the CAN module instance
 * \param[in]  baudrate    CAN_FD baudrate
 */
void can_fd_set_baudrate(Can *hw, uint32_t baudrate);

/**
 * \brief Start CAN module communication.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_start(struct can_module *const module_inst);

/**
 * \brief Stop CAN module communication.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_stop(struct can_module *const module_inst);

/**
 * \brief Enable CAN FD mode.
 *
 * \note This function will set the CCCR.INIT bit, can_start() is needed to
 * restart the communication.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_enable_fd_mode(struct can_module *const module_inst);

/**
 * \brief Disable CAN FD mode.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_disable_fd_mode(struct can_module *const module_inst);

/**
 * \brief Enable CAN restricted operation mode.
 *
 * \note This function will set the CCCR.INIT bit, can_start() is needed to
 * restart the communication.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_enable_restricted_operation_mode(
		struct can_module *const module_inst);

/**
 * \brief Disable CAN restricted operation mode.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_disable_restricted_operation_mode(
		struct can_module *const module_inst);

/**
 * \brief Enable CAN bus monitor mode.
 *
 * \note This function will set the CCCR.INIT bit, can_start() is needed to
 * restart the communication.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_enable_bus_monitor_mode(struct can_module *const module_inst);

/**
 * \brief Disable CAN bus monitor mode.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_disable_bus_monitor_mode(struct can_module *const module_inst);

/**
 * \brief Enable CAN sleep mode.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_enable_sleep_mode(struct can_module *const module_inst);

/**
 * \brief Disable CAN sleep mode.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_disable_sleep_mode(struct can_module *const module_inst);

/**
 * \brief Enable CAN test mode.
 *
 * \note This function will set the CCCR.INIT bit, can_start() is needed to
 * restart the communication.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_enable_test_mode(struct can_module *const module_inst);

/**
 * \brief Disable CAN test mode.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
void can_disable_test_mode(struct can_module *const module_inst);

/**
 * \brief Can read timestamp count value.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 *
 * \return Timestamp count value.
 */
static inline uint16_t can_read_timestamp_count_value(
		struct can_module *const module_inst)
{
	return module_inst->hw->TSCV.bit.TSC;
}

/**
 * \brief Can read timeout  count value.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 *
 * \return Timeout count value.
 */
static inline uint16_t can_read_timeout_count_value(
		struct can_module *const module_inst)
{
	return module_inst->hw->TOCV.bit.TOC;
}

/**
 * \brief Can read error count.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 *
 * \return Error count value.
 */
static inline uint32_t can_read_error_count(
		struct can_module *const module_inst)
{
	return module_inst->hw->ECR.reg;
}

/**
 * \brief Can read protocol status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 *
 * \return protocol status value.
 */
static inline uint32_t can_read_protocal_status(
		struct can_module *const module_inst)
{
	return module_inst->hw->PSR.reg;
}

/** @} */

/**
 * \name Rx Handling
 * @{
 */

/**
 * \brief Read high priority message status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 *
 * \return High priority message status value.
 */
static inline uint32_t can_read_high_priority_message_status(
		struct can_module *const module_inst)
{
	return module_inst->hw->HPMS.reg;
}

/**
 * \brief Get Rx buffer status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] index  Index offset in Rx buffer
 *
 * \return Rx buffer status value.
 *
 *  \retval true Rx Buffer updated from new message.
 *  \retval false Rx Buffer not updated.
 */
static inline bool can_rx_get_buffer_status(
		struct can_module *const module_inst, uint32_t index)
{
	if (index < 32) {
		if (module_inst->hw->NDAT1.reg & (1 << index)) {
			return true;
		} else {
			return false;
		}
	} else {
		index -= 32;
		if (module_inst->hw->NDAT2.reg & (1 << index)) {
			return true;
		} else {
			return false;
		}
	}
}

/**
 * \brief Clear Rx buffer status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] index  Index offset in Rx buffer
 *
 */
static inline void can_rx_clear_buffer_status(
		struct can_module *const module_inst, uint32_t index)
{
	if (index < 32) {
		module_inst->hw->NDAT1.reg = (1 << index);
	} else {
		index -= 32;
		module_inst->hw->NDAT2.reg = (1 << index);
	}
}

/**
 * \brief Get Rx FIFO status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] fifo_number  Rx FIFO 0 or 1
 *
 * \return Rx FIFO status value.
 */
static inline uint32_t can_rx_get_fifo_status(
		struct can_module *const module_inst, bool fifo_number)
{
	if (!fifo_number) {
		return module_inst->hw->RXF0S.reg;
	} else {
		return module_inst->hw->RXF1S.reg;
	}
}

/**
 * \brief Set Rx acknowledge.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] fifo_number  Rx FIFO 0 or 1
 * \param[in] index  Index offset in FIFO
 */
static inline void can_rx_fifo_acknowledge(
		struct can_module *const module_inst, bool fifo_number, uint32_t index)
{
	if (!fifo_number) {
		module_inst->hw->RXF0A.reg = CAN_RXF0A_F0AI(index);
	} else {
		module_inst->hw->RXF1A.reg = CAN_RXF1A_F1AI(index);
	}
}

/**
 * \brief Get the standard message filter default value.
 *
 * The default configuration is as follows:
 *  \li Classic filter: SFID1 = filter, SFID2 = mask
 *  \li Store in Rx FIFO 0 if filter matches
 *  \li SFID2 = 0x7FFul
 *  \li SFID1 = 0x0ul
 *
 * \param[out] sd_filter  Pointer to standard filter element struct to initialize to default values
 */
static inline void can_get_standard_message_filter_element_default(
		struct can_standard_message_filter_element *sd_filter)
{
	sd_filter->S0.reg = CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID2_Msk |
			CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFID1(0) |
			CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC(
			CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_STF0M_Val) |
			CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFT_CLASSIC;
}

/**
 * \brief Set the standard message filter.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] sd_filter  Pointer to standard filter element struct
 * \param[in] index  Index offset in standard filter element
 *
 *  \return Status of the result.
 *
 *  \retval STATUS_OK   Set the correct standard message filter.
 *  \retval STATUS_ERR_INVALID_ARG The parameter is not correct.
 */
enum status_code can_set_rx_standard_filter(
		struct can_module *const module_inst,
		struct can_standard_message_filter_element *sd_filter, uint32_t index);

/**
 * \brief Get the extended message filter default value.
 *
 * The default configuration is as follows:
 *  \li Classic filter: SFID1 = filter, SFID2 = mask
 *  \li Store in Rx FIFO 1 if filter matches
 *  \li SFID2 = 0x1FFFFFFFul
 *  \li SFID1 = 0x0ul
 *
 * \param[out] et_filter  Pointer to extended filter element struct to initialize to default values
 */
static inline void can_get_extended_message_filter_element_default(
		struct can_extended_message_filter_element *et_filter)
{
	et_filter->F0.reg = CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFID1(0) |
			CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC(
			CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_STF1M_Val);
	et_filter->F1.reg = CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFID2_Msk |
			CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_CLASSIC;
}

/**
 * \brief Set the extended message filter.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] et_filter  Pointer to extended filter element struct
 * \param[in] index  Index offset in extended filter element
 *
 *  \return Status of the result.
 *
 *  \retval STATUS_OK   Set the correct extended message filter.
 *  \retval STATUS_ERR_INVALID_ARG The parameter is not correct.
 */
enum status_code can_set_rx_extended_filter(
		struct can_module *const module_inst,
		struct can_extended_message_filter_element *et_filter, uint32_t index);

/**
 * \brief Get the pointer to the receive buffer element.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] rx_element  Pointer to receive buffer element
 * \param[in] index  Index offset in receive buffer
 *
 *  \return Status of the result.
 *
 *  \retval STATUS_OK   Get the correct pointer to the receive buffer element.
 *  \retval STATUS_ERR_INVALID_ARG The parameter is not correct.
 */
enum status_code can_get_rx_buffer_element(
		struct can_module *const module_inst,
		struct can_rx_element_buffer *rx_element, uint32_t index);

/**
 * \brief Get the pointer to the receive FIFO 0 element.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] rx_element  Pointer to receive FIFO 0
 * \param[in] index  Index offset in receive FIFO 0
 *
 *  \return Status of the result.
 *
 *  \retval STATUS_OK   Get the correct pointer to the receive FIFO 0 element.
 *  \retval STATUS_ERR_INVALID_ARG The parameter is not correct.
 */
enum status_code can_get_rx_fifo_0_element(
		struct can_module *const module_inst,
		struct can_rx_element_fifo_0 *rx_element, uint32_t index);

/**
 * \brief Get the pointer to the receive FIFO 1 element.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] rx_element  Pointer to receive FIFO 1
 * \param[in] index  Index offset in receive FIFO 1
 *
 *  \return Status of the result.
 *
 *  \retval STATUS_OK   Get the correct pointer to the receive FIFO 1 element.
 *  \retval STATUS_ERR_INVALID_ARG The parameter is not correct.
 */
enum status_code can_get_rx_fifo_1_element(
		struct can_module *const module_inst,
		struct can_rx_element_fifo_1 *rx_element, uint32_t index);

/** @} */

/**
 * \name Tx Handling
 * @{
 */

/**
 * \brief Get Tx FIFO/Queue status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 *
 * \return Tx FIFO/Queue status value.
 */
static inline uint32_t can_tx_get_fifo_queue_status(
		struct can_module *const module_inst)
{
	return module_inst->hw->TXFQS.reg;
}

/**
 * \brief Get Tx buffer request pending status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 *
 * \return Bit mask of Tx buffer request pending status value.
 */
static inline uint32_t can_tx_get_pending_status(
		struct can_module *const module_inst)
{
	return module_inst->hw->TXBRP.reg;
}

/**
 * \brief Tx buffer add transfer request.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] trig_mask  The mask value to trigger transfer buffer
 *
 *  \return Status of the result.
 *
 *  \retval STATUS_OK   Set the transfer request.
 *  \retval STATUS_BUSY The module is in configuration.
 */
static inline enum status_code can_tx_transfer_request(
		struct can_module *const module_inst, uint32_t trig_mask)
{
	if (module_inst->hw->CCCR.reg & CAN_CCCR_CCE) {
		return STATUS_BUSY;
	}
	module_inst->hw->TXBAR.reg = trig_mask;
	return STATUS_OK;
}

/**
 * \brief Set Tx Queue operation.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] trig_mask  The mask value to cancel transfer buffer
 *
 *  \return Status of the result.
 *
 *  \retval STATUS_OK   Set the transfer request.
 *  \retval STATUS_BUSY The module is in configuration.
 */
static inline enum status_code can_tx_cancel_request(
		struct can_module *const module_inst, uint32_t trig_mask)
{
	if (module_inst->hw->CCCR.reg & CAN_CCCR_CCE) {
		return STATUS_BUSY;
	}
	module_inst->hw->TXBCR.reg = trig_mask;
	return STATUS_OK;
}

/**
 * \brief Get Tx transmission status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 *
 * \return Bit mask of Tx transmission status value.
 */
static inline uint32_t can_tx_get_transmission_status(
		struct can_module *const module_inst)
{
	return module_inst->hw->TXBTO.reg;
}

/**
 * \brief Get Tx cancellation status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 *
 * \return Bit mask of Tx cancellation status value.
 */
static inline uint32_t can_tx_get_cancellation_status(
		struct can_module *const module_inst)
{
	return module_inst->hw->TXBCF.reg;
}

/**
 * \brief Get Tx event FIFO status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 *
 * \return Tx event FIFO status value.
 */
static inline uint32_t can_tx_get_event_fifo_status(
		struct can_module *const module_inst)
{
	return module_inst->hw->TXEFS.reg;
}

/**
 * \brief Set Tx Queue operation.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] index  Index for the transfer FIFO
 */
static inline void can_tx_event_fifo_acknowledge(
		struct can_module *const module_inst, uint32_t index)
{
	module_inst->hw->TXEFA.reg = CAN_TXEFA_EFAI(index);
}

/**
 * \brief Get the default transfer buffer element.
 *
 * The default configuration is as follows:
 *  \li 11-bit standard identifier
 *  \li Transmit data frame
 *  \li ID = 0x0ul
 *  \li Store Tx events
 *  \li Frame transmitted in Classic CAN format
 *  \li Data Length Code is 8
 *
 * \param[out] tx_element  Pointer to transfer element struct to initialize to default values
 */
static inline void can_get_tx_buffer_element_defaults(
		struct can_tx_element *tx_element)
{
	tx_element->T0.reg = 0;
	tx_element->T1.reg = CAN_TX_ELEMENT_T1_EFC |
			CAN_TX_ELEMENT_T1_DLC(CAN_TX_ELEMENT_T1_DLC_DATA8_Val);
}

/**
 * \brief Set the transfer buffer element.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] tx_element  Pointer to transfer element struct
 * \param[in] index  Index for the transfer buffer
 *
 *  \return Status of the result.
 *
 *  \retval STATUS_OK   Set the correct transfer buffer element.
 *  \retval STATUS_ERR_INVALID_ARG The parameter is not correct.
 */
enum status_code can_set_tx_buffer_element(
		struct can_module *const module_inst,
		struct can_tx_element *tx_element, uint32_t index);

/**
 * \brief Get the pointer to the transfer event FIFO element.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] tx_event_element  Pointer to transfer event element
 * \param[in] index  Index offset in transfer event FIFO
 *
 *  \return Status of the result.
 *
 *  \retval STATUS_OK   Get the correct pointer to the transfer event FIFO element.
 *  \retval STATUS_ERR_INVALID_ARG The parameter is not correct.
 */
enum status_code can_get_tx_event_fifo_element(
		struct can_module *const module_inst,
		struct can_tx_event_element *tx_event_element, uint32_t index);

/** @} */

/**
 * \name Interrupt Handling
 * @{
 */

/**
 * \brief Can module interrupt source.
 *
 * Enum for the interrupt source.
 */
enum can_interrupt_source {
	/** Rx FIFO 0 New Message Interrupt Enable. */
	CAN_RX_FIFO_0_NEW_MESSAGE = CAN_IE_RF0NE,
	/** Rx FIFO 0 Watermark Reached Interrupt Enable. */
	CAN_RX_FIFO_0_WATERMARK = CAN_IE_RF0WE,
	/** Rx FIFO 0 Full Interrupt Enable. */
	CAN_RX_FIFO_0_FULL = CAN_IE_RF0FE,
	/** Rx FIFO 0 Message Lost Interrupt Enable. */
	CAN_RX_FIFO_0_LOST_MESSAGE = CAN_IE_RF0LE,
	/** Rx FIFO 1 New Message Interrupt Enable. */
	CAN_RX_FIFO_1_NEW_MESSAGE = CAN_IE_RF1NE,
	/** Rx FIFO 1 Watermark Reached Interrupt Enable. */
	CAN_RX_FIFO_1_WATERMARK = CAN_IE_RF1WE,
	/** Rx FIFO 1 Full Interrupt Enable. */
	CAN_RX_FIFO_1_FULL = CAN_IE_RF1FE,
	/** Rx FIFO 1 Message Lost Interrupt Enable. */
	CAN_RX_FIFO_1_MESSAGE_LOST = CAN_IE_RF1LE,
	/** High Priority Message Interrupt Enable. */
	CAN_RX_HIGH_PRIORITY_MESSAGE = CAN_IE_HPME,
	/** Timestamp Completed Interrupt Enable. */
	CAN_TIMESTAMP_COMPLETE = CAN_IE_TCE,
	/** Transmission Cancellation Finished Interrupt Enable. */
	CAN_TX_CANCELLATION_FINISH = CAN_IE_TCFE,
	/** Tx FIFO Empty Interrupt Enable. */
	CAN_TX_FIFO_EMPTY = CAN_IE_TFEE,
	/** Tx Event FIFO New Entry Interrupt Enable. */
	CAN_TX_EVENT_FIFO_NEW_ENTRY = CAN_IE_TEFNE,
	/** Tx Event FIFO Watermark Reached Interrupt Enable. */
	CAN_TX_EVENT_FIFO_WATERMARK = CAN_IE_TEFWE,
	/** Tx Event FIFO Full Interrupt Enable. */
	CAN_TX_EVENT_FIFO_FULL = CAN_IE_TEFFE,
	/** Tx Event FIFO Element Lost Interrupt Enable. */
	CAN_TX_EVENT_FIFO_ELEMENT_LOST = CAN_IE_TEFLE,
	/** Timestamp Wraparound Interrupt Enable. */
	CAN_TIMESTAMP_WRAPAROUND = CAN_IE_TSWE,
	/** Message RAM Access Failure Interrupt Enable. */
	CAN_MESSAGE_RAM_ACCESS_FAILURE = CAN_IE_MRAFE,
	/** Timeout Occurred Interrupt Enable. */
	CAN_TIMEOUT_OCCURRED = CAN_IE_TOOE,
	/** Message stored to Dedicated Rx Buffer Interrupt Enable. */
	CAN_RX_BUFFER_NEW_MESSAGE = CAN_IE_DRXE,
	/** Bit Error Corrected Interrupt Enable. */
	CAN_BIT_ERROR_CORRECTED = CAN_IE_BECE,
	/** Bit Error Uncorrected Interrupt Enable. */
	CAN_BIT_ERROR_UNCORRECTED = CAN_IE_BEUE,
	/** Error Logging Overflow Interrupt Enable. */
	CAN_ERROR_LOGGING_OVERFLOW = CAN_IE_ELOE,
	/** Error Passive Interrupt Enable. */
	CAN_ERROR_PASSIVE = CAN_IE_EPE,
	/** Warning Status Interrupt Enable. */
	CAN_WARNING_STATUS = CAN_IE_EWE,
	/** Bus_Off Status Interrupt Enable. */
	CAN_BUS_OFF = CAN_IE_BOE,
	/** Watchdog Interrupt Interrupt Enable. */
	CAN_WATCHDOG = CAN_IE_WDIE,
	/** Protocol Error in Arbitration Phase Enable. */
	CAN_PROTOCOL_ERROR_ARBITRATION = CAN_IE_PEAE,
	/** Protocol Error in Data Phase Enable. */
	CAN_PROTOCOL_ERROR_DATA = CAN_IE_PEDE,
	/** Access to Reserved Address Enable. */
	CAN_ACCESS_RESERVED_ADDRESS = CAN_IE_ARAE,
};

/**
 * \brief Enable CAN interrupt.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] source  Interrupt source type
 */
static inline void can_enable_interrupt(struct can_module *const module_inst,
		const enum can_interrupt_source source)
{
	module_inst->hw->IE.reg |= source;
}

/**
 * \brief Disable CAN interrupt.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] source  Interrupt source type
 */
static inline void can_disable_interrupt(struct can_module *const module_inst,
		const enum can_interrupt_source source)
{
	module_inst->hw->IE.reg &= ~source;
}

/**
 * \brief Get CAN interrupt status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 */
static inline uint32_t can_read_interrupt_status(
		struct can_module *const module_inst)
{
	return module_inst->hw->IR.reg;
}

/**
 * \brief Clear CAN interrupt status.
 *
 * \param[in] module_inst  Pointer to the CAN software instance struct
 * \param[in] source  Interrupt source type
 *
 * \return Bit mask of interrupt status value.
 */
static inline void can_clear_interrupt_status(
		struct can_module *const module_inst,
		const enum can_interrupt_source source)
{
	module_inst->hw->IR.reg = source;
}

/** @} */



#ifdef __cplusplus
}
#endif

/** @} */

/**
 * \page asfdoc_sam0_can_extra Extra Information for CAN Driver
 *
 * \section asfdoc_sam0_can_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *  <tr>
 *		<td>CAN</td>
 *		<td>Control Area Network (CAN) Controller</td>
 *	</tr>
 *  <tr>
 *		<td>CAN FD</td>
 *		<td>CAN with Flexible Data-Rate</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_can_extra_dependencies Dependencies
 * This driver has no dependencies.
 *
 *
 * \section asfdoc_sam0_can_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_can_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
  *	<tr>
 *		<td>Initial Release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_sam0_can_exqsg Examples for CAN Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_can_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_can_basic_use_case
 *
 *  - \subpage asfdoc_sam0_can_fd_use_case
 *
 * \page asfdoc_sam0_can_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>A</td>
 *		<td>03/2015</td>
 *		<td>Initial release</td>
 *	</tr>
 * </table>
 */

#endif /* CAN_H_INCLUDED */

