////////////////////////////////////////////////////////////////////////////////
/// @file     reg_can.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SERIES OF
///           MM32 FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion

#ifndef __REG_CAN_H
#define __REG_CAN_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif







////////////////////////////////////////////////////////////////////////////////
/// @brief CAN Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define CAN1_BASE                       (APB1PERIPH_BASE + 0x6400)              ///< Base Address: 0x40006400




////////////////////////////////////////////////////////////////////////////////
/// @brief CAN Register Structure Definition
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN basic
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CR;                                                                ///< Control register,                              offset: 0x00
    __IO u32 CMR;                                                               ///< Command register,                              offset: 0x04
    __IO u32 SR;                                                                ///< <Status register,                              offset: 0x08
    __IO u32 IR;                                                                ///< Interrupt register,                            offset: 0x0c
    __IO u32 ACR;                                                               ///< Acceptance Code register,                      offset: 0x10
    __IO u32 AMR;                                                               ///< Acceptance Mask register,                      offset: 0x14
    __IO u32 BTR0;                                                              ///< Bus Timing register 0,                         offset: 0x18
    __IO u32 BTR1;                                                              ///< Bus Timing register 1,                         offset: 0x1C
    __IO u32 RESERVED0;
    __IO u32 RESERVED1;
    __IO u32 TXID0;                                                             ///< Send ID register 0,                            offset: 0x28
    __IO u32 TXID1;                                                             ///< Send ID register 1,                            offset: 0x2c
    __IO u32 TXDR0;                                                             ///< Send Data register 0,                          offset: 0x30
    __IO u32 TXDR1;                                                             ///< Send Data register 1,                          offset: 0x34
    __IO u32 TXDR2;                                                             ///< Send Data register 2,                          offset: 0x38
    __IO u32 TXDR3;                                                             ///< Send Data register 3,                          offset: 0x3c
    __IO u32 TXDR4;                                                             ///< Send Data register 4,                          offset: 0x40
    __IO u32 TXDR5;                                                             ///< Send Data register 5,                          offset: 0x44
    __IO u32 TXDR6;                                                             ///< Send Data register 6,                          offset: 0x48
    __IO u32 TXDR7;                                                             ///< Send Data register 7,                          offset: 0x4c
    __IO u32 RXID0;                                                             ///< Mode register,                                 offset: 0x50
    __IO u32 RXID1;                                                             ///< Mode register,                                 offset: 0x54
    __IO u32 RXDR0;                                                             ///< Mode register,                                 offset: 0x58
    __IO u32 RXDR1;                                                             ///< Mode register,                                 offset: 0x5C
    __IO u32 RXDR2;                                                             ///< Mode register,                                 offset: 0x60
    __IO u32 RXDR3;                                                             ///< Mode register,                                 offset: 0x64
    __IO u32 RXDR4;                                                             ///< Mode register,                                 offset: 0x68
    __IO u32 RXDR5;                                                             ///< Mode register,                                 offset: 0x6c
    __IO u32 RXDR6;                                                             ///< Mode register,                                 offset: 0x70
    __IO u32 RXDR7;                                                             ///< Mode register,                                 offset: 0x74
    __IO u32 RESERVED2;
    __IO u32 CDR;                                                               ///< Clock Divider register,                        offset: 0x7c
} CAN_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN Peli
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 MOD;                                                               ///< Mode register,                                 offset: 0x00
    __IO u32 CMR;                                                               ///< Command register,                              offset: 0x04
    __IO u32 SR;                                                                ///< Status register,                               offset: 0x08
    __IO u32 IR;                                                                ///< Interrupt Enable register,                     offset: 0x0c
    __IO u32 IER;                                                               ///< Mode register,                                 offset: 0x10
    __IO u32 RESERVED0;
    __IO u32 BTR0;                                                              ///< Bus Timing register 0,                         offset: 0x18
    __IO u32 BTR1;                                                              ///< Bus Timing register 1,                         offset: 0x1C
    __IO u32 RESERVED1;
    __IO u32 RESERVED2;
    __IO u32 RESERVED3;
    __IO u32 ALC;                                                               ///< Arbitration Lost Capture register,             offset: 0x2c
    __IO u32 ECC;                                                               ///< Error Code Capture register,                   offset: 0x30
    __IO u32 EWLR;                                                              ///< Error Warning Limit register,                  offset: 0x34
    __IO u32 RXERR;                                                             ///< RX Error Counter register,                     offset: 0x38
    __IO u32 TXERR;                                                             ///< TX Error Counter register,                     offset: 0x3c
    __IO u32 FF;                                                                ///< Frame Format register,                         offset: 0x40
    __IO u32 ID0;                                                               ///< ID register 0,                                 offset: 0x44
    __IO u32 ID1;                                                               ///< ID register 1,                                 offset: 0x48
    __IO u32 DATA0;                                                             ///< Data register 0,                               offset: 0x4c
    __IO u32 DATA1;                                                             ///< Data register 1,                               offset: 0x50
    __IO u32 DATA2;                                                             ///< Data register 2,                               offset: 0x54
    __IO u32 DATA3;                                                             ///< Data register 3,                               offset: 0x58
    __IO u32 DATA4;                                                             ///< Data register 4,                               offset: 0x5c
    __IO u32 DATA5;                                                             ///< Data register 5,                               offset: 0x60
    __IO u32 DATA6;                                                             ///< Data register 6,                               offset: 0x64
    __IO u32 DATA7;                                                             ///< Data register 7,                               offset: 0x68
    __IO u32 DATA8;                                                             ///< Data register 8,                               offset: 0x6c
    __IO u32 DATA9;                                                             ///< Data register 9,                               offset: 0x70
    __IO u32 RMC;                                                               ///< RMC register,                                  offset: 0x74
    __IO u32 RBSA;                                                              ///< RBSA register,                                 offset: 0x78
    __IO u32 CDR;                                                               ///< Clock Divider register                         offset: 0x7c
} CAN_Peli_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief CAN type pointer Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 ACR0;
    __IO u32 ACR1;
    __IO u32 ACR2;
    __IO u32 ACR3;
    __IO u32 AMR0;
    __IO u32 AMR1;
    __IO u32 AMR2;
    __IO u32 AMR3;
} CAN_FLT_GROUP;

typedef struct {
    CAN_FLT_GROUP GROUP0;                                                        //Address offset: 0x40
    u32      RESERVED[8];                                                        //Address offset: 0x60
    __IO u32 AFM0;                                                               //Address offset: 0x80
    __IO u32 AFM1;                                                               //Address offset: 0x84
    __IO u32 AFM2;                                                               //Address offset: 0x88
    __IO u32 FGA0;                                                               //Address offset: 0x8C
    __IO u32 FGA1;                                                               //Address offset: 0x90
    __IO u32 FGA2;                                                               //Address offset: 0x94
    CAN_FLT_GROUP GROUP1;                                                        //Address offset: 0x98
    CAN_FLT_GROUP GROUP2;                                                        //Address offset: 0xB8
    CAN_FLT_GROUP GROUP3;                                                        //Address offset: 0xD8
    CAN_FLT_GROUP GROUP4;                                                        //Address offset: 0xF8
    CAN_FLT_GROUP GROUP5;                                                        //Address offset: 0x118
    CAN_FLT_GROUP GROUP6;                                                        //Address offset: 0x138
    CAN_FLT_GROUP GROUP7;                                                        //Address offset: 0x158
    CAN_FLT_GROUP GROUP8;                                                        //Address offset: 0x178
    CAN_FLT_GROUP GROUP9;                                                        //Address offset: 0x198
    CAN_FLT_GROUP GROUP10;                                                       //Address offset: 0x1B8
    CAN_FLT_GROUP GROUP11;                                                       //Address offset: 0x1D8
    CAN_FLT_GROUP GROUP12;                                                       //Address offset: 0x1F8
    CAN_FLT_GROUP GROUP13;                                                       //Address offset: 0x218
    CAN_FLT_GROUP GROUP14;                                                       //Address offset: 0x238
    CAN_FLT_GROUP GROUP15;                                                       //Address offset: 0x258
    CAN_FLT_GROUP GROUP16;                                                       //Address offset: 0x278
    CAN_FLT_GROUP GROUP17;                                                       //Address offset: 0x298
    CAN_FLT_GROUP GROUP18;                                                       //Address offset: 0x2B8
    CAN_FLT_GROUP GROUP19;                                                       //Address offset: 0x2D8
} CAN_Peli_FLT_TypeDef;



////////////////////////////////////////////////////////////////////////////////
/// @brief CAN type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define CAN1                        ((CAN_TypeDef*) CAN1_BASE)
#define CAN1_PELI                   ((CAN_Peli_TypeDef*) CAN1_BASE)
#define CAN_Peli_FLT                ((CAN_Peli_FLT_TypeDef*)(CAN1_BASE + 0x40))



////////////////////////////////////////////////////////////////////////////////
/// @brief CAN basic
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_CR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_CR_RR_Pos               (0)
#define CAN_CR_RR                   (0x01U << CAN_CR_RR_Pos)                ///< CAN reset request
#define CAN_CR_RIE_Pos              (1)
#define CAN_CR_RIE                  (0x01U << CAN_CR_RIE_Pos)               ///< CAN receive interrupt enable
#define CAN_CR_TIE_Pos              (2)
#define CAN_CR_TIE                  (0x01U << CAN_CR_TIE_Pos)               ///< CAN transmit interrupt enable
#define CAN_CR_EIE_Pos              (3)
#define CAN_CR_EIE                  (0x01U << CAN_CR_EIE_Pos)               ///< CAN error interrupt enable
#define CAN_CR_OIE_Pos              (4)
#define CAN_CR_OIE                  (0x01U << CAN_CR_OIE_Pos)               ///< CAN overflow interrupt enable

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_CMR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_CMR_TR_Pos              (0)
#define CAN_CMR_TR                  (0x01U << CAN_CMR_TR_Pos )              ///< CAN transmission request
#define CAN_CMR_AT_Pos              (1)
#define CAN_CMR_AT                  (0x01U << CAN_CMR_AT_Pos )              ///< CAN abort transmission
#define CAN_CMR_RRB_Pos             (2)
#define CAN_CMR_RRB                 (0x01U << CAN_CMR_RRB_Pos)              ///< CAN release receive buffer
#define CAN_CMR_CDO_Pos             (3)
#define CAN_CMR_CDO                 (0x01U << CAN_CMR_CDO_Pos)              ///< CAN clear data overrun
#define CAN_CMR_GTS_Pos             (4)
#define CAN_CMR_GTS                 (0x01U << CAN_CMR_GTS_Pos)              ///< CAN go to sleep

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_SR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_SR_RBS_Pos              (0)
#define CAN_SR_RBS                  (0x01U << CAN_SR_RBS_Pos)               ///< CAN receive buffer status
#define CAN_SR_DOS_Pos              (1)
#define CAN_SR_DOS                  (0x01U << CAN_SR_DOS_Pos)               ///< CAN data overrun status
#define CAN_SR_TBS_Pos              (2)
#define CAN_SR_TBS                  (0x01U << CAN_SR_TBS_Pos)               ///< CAN transmit buffer status
#define CAN_SR_TCS_Pos              (3)
#define CAN_SR_TCS                  (0x01U << CAN_SR_TCS_Pos)               ///< CAN transmission complete status
#define CAN_SR_RS_Pos               (4)
#define CAN_SR_RS                   (0x01U << CAN_SR_RS_Pos)                ///< CAN receive status
#define CAN_SR_TS_Pos               (5)
#define CAN_SR_TS                   (0x01U << CAN_SR_TS_Pos)                ///< CAN transmit status
#define CAN_SR_ES_Pos               (6)
#define CAN_SR_ES                   (0x01U << CAN_SR_ES_Pos)                ///< CAN error status
#define CAN_SR_BS_Pos               (7)
#define CAN_SR_BS                   (0x01U << CAN_SR_BS_Pos)                ///< CAN bus status

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_ACR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_ACR_AC                  (0xFFU << 0)                            ///< CAN acceptance code

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_AMR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_AMR_AM_Pos              (0)
#define CAN_AMR_AM                  (0xFFU << CAN_AMR_AM_Pos)               ///< CAN acceptance mask

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_BTR0 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_BTR0_BRP_Pos            (0)
#define CAN_BTR0_BRP                (0x003FU << CAN_BTR0_BRP_Pos)           ///< CAN baud rate prescaler
#define CAN_BTR0_SJW_Pos            (6)
#define CAN_BTR0_SJW                (0x03U << CAN_BTR0_SJW_Pos)             ///< CAN synchronization jump width

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_BTR1 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_BTR1_TESG1_Pos          (0)
#define CAN_BTR1_TESG1              (0x000FU << CAN_BTR1_TESG1_Pos)         ///< CAN Time segment 1
#define CAN_BTR1_TESG2_Pos          (4)
#define CAN_BTR1_TESG2              (0x07U << CAN_BTR1_TESG2_Pos)           ///< CAN Time segment 2
#define CAN_BTR1_SAM_Pos            (7)
#define CAN_BTR1_SAM                (0x01U << CAN_BTR1_SAM_Pos)             ///< CAN sampling

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_TXID0 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_TXID0_ID_3_Pos          (0)
#define CAN_TXID0_ID_3              (0x01U << CAN_TXID0_ID_3_Pos)           ///< CAN identifier byte 3
#define CAN_TXID0_ID_4_Pos          (1)
#define CAN_TXID0_ID_4              (0x01U << CAN_TXID0_ID_4_Pos)           ///< CAN identifier byte 4
#define CAN_TXID0_ID_5_Pos          (2)
#define CAN_TXID0_ID_5              (0x01U << CAN_TXID0_ID_5_Pos)           ///< CAN identifier byte 5
#define CAN_TXID0_ID_6_Pos          (3)
#define CAN_TXID0_ID_6              (0x01U << CAN_TXID0_ID_6_Pos)           ///< CAN identifier byte 6
#define CAN_TXID0_ID_7_Pos          (4)
#define CAN_TXID0_ID_7              (0x01U << CAN_TXID0_ID_7_Pos)           ///< CAN identifier byte 7
#define CAN_TXID0_ID_8_Pos          (5)
#define CAN_TXID0_ID_8              (0x01U << CAN_TXID0_ID_8_Pos)           ///< CAN identifier byte 8
#define CAN_TXID0_ID_9_Pos          (6)
#define CAN_TXID0_ID_9              (0x01U << CAN_TXID0_ID_9_Pos)           ///< CAN identifier byte 9
#define CAN_TXID0_ID_10_Pos         (7)
#define CAN_TXID0_ID_10             (0x01U << CAN_TXID0_ID_10_Pos)          ///< CAN identifier byte 10

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_TXID1 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_TXID1_DLC0_Pos          (0)
#define CAN_TXID1_DLC0              (0x01U << CAN_TXID1_DLC0_Pos)           ///< CAN data length code 0 ~ 8
#define CAN_TXID1_DLC1_Pos          (1)
#define CAN_TXID1_DLC1              (0x01U << CAN_TXID1_DLC1_Pos)           ///< CAN data length code 0 ~ 8
#define CAN_TXID1_DLC2_Pos          (2)
#define CAN_TXID1_DLC2              (0x01U << CAN_TXID1_DLC2_Pos)           ///< CAN data length code 0 ~ 8
#define CAN_TXID1_DLC3_Pos          (3)
#define CAN_TXID1_DLC3              (0x01U << CAN_TXID1_DLC3_Pos)           ///< CAN data length code 0 ~ 8
#define CAN_TXID1_RTR_Pos           (4)
#define CAN_TXID1_RTR               (0x01U << CAN_TXID1_RTR_Pos )           ///< CAN remote transmission request
#define CAN_TXID1_ID_0_Pos          (5)
#define CAN_TXID1_ID_0              (0x01U << CAN_TXID1_ID_0_Pos)           ///< CAN identifier byte 0
#define CAN_TXID1_ID_1_Pos          (6)
#define CAN_TXID1_ID_1              (0x01U << CAN_TXID1_ID_1_Pos)           ///< CAN identifier byte 1
#define CAN_TXID1_ID_2_Pos          (7)
#define CAN_TXID1_ID_2              (0x01U << CAN_TXID1_ID_2_Pos)           ///< CAN identifier byte 2

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_TXDRn register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_TXDRn                   (0x00FFU)                               // (n = 0..7)        ///< CAN send data

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_CDR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_CDR_MODE_Pos            (7)
#define CAN_CDR_MODE                (0x01U << CAN_CDR_MODE_Pos)             ///< CAN mode

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN Peli
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_MOD register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_MOD_RM_Pos              (0)
#define CAN_MOD_RM                  (0x01U << CAN_MOD_RM_Pos)               ///< CAN reset mode
#define CAN_MOD_LOM_Pos             (1)
#define CAN_MOD_LOM                 (0x01U << CAN_MOD_LOM_Pos)              ///< CAN listen only mode
#define CAN_MOD_STM_Pos             (2)
#define CAN_MOD_STM                 (0x01U << CAN_MOD_STM_Pos)              ///< CAN self test mode
#define CAN_MOD_AFM_Pos             (3)
#define CAN_MOD_AFM                 (0x01U << CAN_MOD_AFM_Pos)              ///< CAN acceptance filter mode

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_CMR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_CMR_TR_Pos              (0)
#define CAN_CMR_TR                  (0x01U << CAN_CMR_TR_Pos )              ///< CAN transmission request
#define CAN_CMR_AT_Pos              (1)
#define CAN_CMR_AT                  (0x01U << CAN_CMR_AT_Pos )              ///< CAN abort transmission
#define CAN_CMR_RRB_Pos             (2)
#define CAN_CMR_RRB                 (0x01U << CAN_CMR_RRB_Pos)              ///< CAN release receive buffer
#define CAN_CMR_CDO_Pos             (3)
#define CAN_CMR_CDO                 (0x01U << CAN_CMR_CDO_Pos)              ///< CAN clear data overrun
#define CAN_CMR_SRR_Pos             (4)
#define CAN_CMR_SRR                 (0x01U << CAN_CMR_SRR_Pos)              ///< CAN self reset request

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_SR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_SR_RBS_Pos              (0)
#define CAN_SR_RBS                  (0x01U << CAN_SR_RBS_Pos)               ///< CAN receive buffer status
#define CAN_SR_DOS_Pos              (1)
#define CAN_SR_DOS                  (0x01U << CAN_SR_DOS_Pos)               ///< CAN data overrun status
#define CAN_SR_TBS_Pos              (2)
#define CAN_SR_TBS                  (0x01U << CAN_SR_TBS_Pos)               ///< CAN transmit buffer status
#define CAN_SR_TCS_Pos              (3)
#define CAN_SR_TCS                  (0x01U << CAN_SR_TCS_Pos)               ///< CAN transmission complete status
#define CAN_SR_RS_Pos               (4)
#define CAN_SR_RS                   (0x01U << CAN_SR_RS_Pos)                ///< CAN receive status
#define CAN_SR_TS_Pos               (5)
#define CAN_SR_TS                   (0x01U << CAN_SR_TS_Pos)                ///< CAN transmit status
#define CAN_SR_ES_Pos               (6)
#define CAN_SR_ES                   (0x01U << CAN_SR_ES_Pos)                ///< CAN error status
#define CAN_SR_BS_Pos               (7)
#define CAN_SR_BS                   (0x01U << CAN_SR_BS_Pos)                ///< CAN bus status

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_IR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_IR_RI_Pos               (0)
#define CAN_IR_RI                   (0x01U << CAN_IR_RI_Pos)                ///< CAN receive interrupt
#define CAN_IR_TI_Pos               (1)
#define CAN_IR_TI                   (0x01U << CAN_IR_TI_Pos)                ///< CAN transmit interrupt
#define CAN_IR_EI_Pos               (2)
#define CAN_IR_EI                   (0x01U << CAN_IR_EI_Pos)                ///< CAN error interrupt
#define CAN_IR_DOI_Pos              (3)
#define CAN_IR_DOI                  (0x01U << CAN_IR_DOI_Pos)               ///< CAN data overrun interrupt
#define CAN_IR_EPI_Pos              (5)
#define CAN_IR_EPI                  (0x01U << CAN_IR_EPI_Pos)               ///< CAN error passive interrupt
#define CAN_IR_ALI_Pos              (6)
#define CAN_IR_ALI                  (0x01U << CAN_IR_ALI_Pos)               ///< CAN arbitration lost interrupt
#define CAN_IR_BEI_Pos              (7)
#define CAN_IR_BEI                  (0x01U << CAN_IR_BEI_Pos)               ///< CAN bus error interrupt

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_IR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_IER_RIE_Pos             (0)
#define CAN_IER_RIE                 (0x01U << CAN_IER_RIE_Pos)              ///< CAN receive interrupt enable
#define CAN_IER_TIE_Pos             (1)
#define CAN_IER_TIE                 (0x01U << CAN_IER_TIE_Pos)              ///< CAN transmit interrupt enable
#define CAN_IER_EIE_Pos             (2)
#define CAN_IER_EIE                 (0x01U << CAN_IER_EIE_Pos)              ///< CAN error interrupt enable
#define CAN_IER_DOIE_Pos            (3)
#define CAN_IER_DOIE                (0x01U << CAN_IER_DOIE_Pos)             ///< CAN data overrun interrupt enable
#define CAN_IER_EPIE_Pos            (5)
#define CAN_IER_EPIE                (0x01U << CAN_IER_EPI_Pos)              ///< CAN error passive interrupt enable
#define CAN_IER_ALIE_Pos            (6)
#define CAN_IER_ALIE                (0x01U << CAN_IER_ALIE_Pos)             ///< CAN arbitration lost interrupt enable
#define CAN_IER_BEIE_Pos            (7)
#define CAN_IER_BEIE                (0x01U << CAN_IER_BEIE_Pos)             ///< CAN bus error interrupt enable

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_ACRn register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_ACRn_AC_Pos             (0)
#define CAN_ACRn_AC                 (0xFFU << CAN_ACRn_AC_Pos)              ///< CAN acceptance code

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_AMRn register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_AMRn_AM_Pos             (0)
#define CAN_AMRn_AM                 (0xFFU << CAN_AMRn_AM_Pos)              ///< CAN acceptance mask

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_BTR0 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_BTR0_BRP_Pos            (0)
#define CAN_BTR0_BRP                (0x003FU << CAN_BTR0_BRP_Pos)           ///< CAN baud rate prescaler
#define CAN_BTR0_SJW_Pos            (6)
#define CAN_BTR0_SJW                (0x03U << CAN_BTR0_SJW_Pos)             ///< CAN synchronization jump width

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_ALC register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_ALC_BITNO_Pos           (0)
#define CAN_ALC_BITNO               (0x001FU << CAN_ALC_BITNO_Pos)          ///< CAN bit number

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_ECC register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_ECC_SEG_Pos             (0)
#define CAN_ECC_SEG                 (0x001FU <<CAN_ECC_SEG_Pos)             ///< CAN error code capture
#define CAN_ECC_DIR_Pos             (5)
#define CAN_ECC_DIR                 (0x01U << CAN_ECC_DIR_Pos)              ///< CAN direction
#define CAN_ECC_ERRC_Pos            (6)
#define CAN_ECC_ERRC                (0x03U << CAN_ECC_ERRC_Pos)             ///< CAN error code

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_EWLR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_EWLR_EWL_Pos            (0)
#define CAN_EWLR_EWL                (0x00FFU << CAN_EWLR_EWL_Pos)           ///< CAN programmable error warning limit

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_RXERR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_RXERR_RXERR_Pos         (0)
#define CAN_RXERR_RXERR             (0x00FFU << CAN_RXERR_RXERR_Pos)        ///< CAN RX error counter register

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_TXERR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_TXERR_TXERR_Pos         (0)
#define CAN_TXERR_TXERR             (0x00FFU << CAN_TXERR_TXERR_Pos)        ///< CAN TX error counter register

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_FF register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_FF_DLC_0_Pos            (0)
#define CAN_FF_DLC_0                (0x01U << CAN_FF_DLC_0_Pos)             ///< CAN data length code bit
#define CAN_FF_DLC_1_Pos            (1)
#define CAN_FF_DLC_1                (0x01U << CAN_FF_DLC_1_Pos)             ///< CAN data length code bit
#define CAN_FF_DLC_2_Pos            (2)
#define CAN_FF_DLC_2                (0x01U << CAN_FF_DLC_2_Pos)             ///< CAN data length code bit
#define CAN_FF_DLC_3_Pos            (3)
#define CAN_FF_DLC_3                (0x01U << CAN_FF_DLC_3_Pos)             ///< CAN data length code bit
#define CAN_FF_RTR_Pos              (6)
#define CAN_FF_RTR                  (0x01U << CAN_FF_RTR_Pos)               ///< CAN remote transmission request
#define CAN_FF_FF_Pos               (7)
#define CAN_FF_FF                   (0x01U << CAN_FF_FF_Pos)                ///< CAN frame format
////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_TXID0 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_TXID0_ID_21_Pos         (0)
#define CAN_TXID0_ID_21             (0x01U << CAN_TXID0_ID_21_Pos)          ///< CAN identifier bit 21
#define CAN_TXID0_ID_22_Pos         (1)
#define CAN_TXID0_ID_22             (0x01U << CAN_TXID0_ID_22_Pos)          ///< CAN identifier bit 22
#define CAN_TXID0_ID_23_Pos         (2)
#define CAN_TXID0_ID_23             (0x01U << CAN_TXID0_ID_23_Pos)          ///< CAN identifier bit 23
#define CAN_TXID0_ID_24_Pos         (3)
#define CAN_TXID0_ID_24             (0x01U << CAN_TXID0_ID_24_Pos)          ///< CAN identifier bit 24
#define CAN_TXID0_ID_25_Pos         (4)
#define CAN_TXID0_ID_25             (0x01U << CAN_TXID0_ID_25_Pos)          ///< CAN identifier bit 25
#define CAN_TXID0_ID_26_Pos         (5)
#define CAN_TXID0_ID_26             (0x01U << CAN_TXID0_ID_26_Pos)          ///< CAN identifier bit 26
#define CAN_TXID0_ID_27_Pos         (6)
#define CAN_TXID0_ID_27             (0x01U << CAN_TXID0_ID_27_Pos)          ///< CAN identifier bit 27
#define CAN_TXID0_ID_28_Pos         (7)
#define CAN_TXID0_ID_28             (0x01U << CAN_TXID0_ID_28_Pos)          ///< CAN identifier bit 28

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_TXID1 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_TXID1_ID_13_Pos         (0)
#define CAN_TXID1_ID_13             (0x01U << CAN_TXID1_ID_13_Pos)          ///< CAN identifier bit 13
#define CAN_TXID1_ID_14_Pos         (1)
#define CAN_TXID1_ID_14             (0x01U << CAN_TXID1_ID_14_Pos)          ///< CAN identifier bit 14
#define CAN_TXID1_ID_15_Pos         (2)
#define CAN_TXID1_ID_15             (0x01U << CAN_TXID1_ID_15_Pos)          ///< CAN identifier bit 15
#define CAN_TXID1_ID_16_Pos         (3)
#define CAN_TXID1_ID_16             (0x01U << CAN_TXID1_ID_16_Pos)          ///< CAN identifier bit 16
#define CAN_TXID1_ID_17_Pos         (4)
#define CAN_TXID1_ID_17             (0x01U << CAN_TXID1_ID_17_Pos)          ///< CAN identifier bit 17
#define CAN_TXID1_ID_18_Pos         (5)
#define CAN_TXID1_ID_18             (0x01U << CAN_TXID1_ID_18_Pos)          ///< CAN identifier bit 18
#define CAN_TXID1_ID_19_Pos         (6)
#define CAN_TXID1_ID_19             (0x01U << CAN_TXID1_ID_19_Pos)          ///< CAN identifier bit 19
#define CAN_TXID1_ID_20_Pos         (7)
#define CAN_TXID1_ID_20             (0x01U << CAN_TXID1_ID_20_Pos)          ///< CAN identifier bit 20

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_TXDATAn register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_TXDATAn_Pos             (0)
#define CAN_TXDATAn                 (0x00FFU << CAN_TXDATAn_Pos)            ///< CAN transmit data n

////////////////////////////////////////////////////////////////////////////////
/// @brief CAN_CDR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define CAN_CDR_MODE_Pos            (7)
#define CAN_CDR_MODE                (0x01U << CAN_CDR_MODE_Pos)             ///< CAN mode



/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
