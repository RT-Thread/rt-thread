////////////////////////////////////////////////////////////////////////////////
/// @file     reg_i2c.h
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

#ifndef __REG_I2C_H
#define __REG_I2C_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif








////////////////////////////////////////////////////////////////////////////////
/// @brief I2C Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C1_BASE                       (APB1PERIPH_BASE + 0x5400)              ///< Base Address: 0x40005400
#define I2C2_BASE                       (APB1PERIPH_BASE + 0x5800)              ///< Base Address: 0x40005800



////////////////////////////////////////////////////////////////////////////////
/// @brief I2C Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
#undef USENCOMBINEREGISTER
#undef USENNEWREGISTER
#undef USENOLDREGISTER
#define USENCOMBINEREGISTER
#ifdef USENCOMBINEREGISTER
typedef struct {
    union {
        __IO u32 CR;                                                           ///< Control Register                               offset: 0x00
        __IO u32 IC_CON;
    };
    union {
        __IO u32 TAR;                                                          ///< Target Address Register                        offset: 0x04
        __IO u32 IC_TAR;
    };
    union {
        __IO u32 SAR;                                                          ///< Slave Address Register                         offset: 0x08
        __IO u32 IC_SAR;
    };
    __IO u32 IC_HS_MADDR_RESERVED;                                             ///< Reserved Register                              offset: 0x0C
    union {
        __IO u32 DR;                                                           ///< Data Command Register                          offset: 0x10
        __IO u32 IC_DATA_CMD;
    };
    union {
        __IO u32 SSHR;                                                         ///< SCL High Period Count for Std. Speed Register  offset: 0x14
        __IO u32 IC_SS_SCL_HCNT;
    };
    union {
        __IO u32 SSLR;                                                         ///< SCL Low Period Count for Std. Speed Register   offset: 0x18
        __IO u32 IC_SS_SCL_LCNT;
    };
    union {
        __IO u32 FSHR;                                                         ///< SCL High Period Count for Fast Speed Register  offset: 0x1C
        __IO u32 IC_FS_SCL_HCNT;
    };
    union {
        __IO u32 FSLR;                                                         ///< SCL Low Period Count for Fast Speed Register   offset: 0x20
        __IO u32 IC_FS_SCL_LCNT;
    };
    __IO u32 IC_HS_SCL_HCNT_RESERVED;                                          ///< Reserved Register                              offset: 0x24
    __IO u32 IC_HS_SCL_LCNT_RESERVED;                                          ///< Reserved Register                              offset: 0x28
    union {
        __IO u32 ISR;                                                          ///< Interrupt Status Register                      offset: 0x2C
        __IO u32 IC_INTR_STAT;
    };
    union {
        __IO u32 IMR;                                                          ///< Interrupt Mask Register                        offset: 0x30
        __IO u32 IC_INTR_MASK;
    };
    union {
        __IO u32 RAWISR;                                                       ///< RAW Interrupt Status Register                  offset: 0x34
        __IO u32 IC_RAW_INTR_STAT;
    };
    union {
        __IO u32 RXTLR;                                                        ///< Receive FIFO Threshold Level Register          offset: 0x38
        __IO u32 IC_RX_TL;
    };
    union {
        __IO u32 TXTLR;                                                        ///< Transmit FIFO Threshold Level Register         offset: 0x3C
        __IO u32 IC_TX_TL;
    };
    union {
        __IO u32 ICR;                                                          ///< Clear All Interrupt Register                   offset: 0x40
        __IO u32 IC_CLR_INTR;
    };
    union {
        __IO u32 RX_UNDER;                                                     ///< Clear RX_UNDER Interrupt Register              offset: 0x44
        __IO u32 IC_CLR_RX_UNDER;
    };
    union {
        __IO u32 RX_OVER;                                                      ///< Clear RX_OVER Interrupt Register               offset: 0x48
        __IO u32 IC_CLR_RX_OVER;
    };
    union {
        __IO u32 TX_OVER;                                                      ///< Clear TX_OVER Interrupt Register               offset: 0x4C
        __IO u32 IC_CLR_TX_OVER;
    };
    union {
        __IO u32 RD_REQ;                                                       ///< Clear RD_REQ Interrupt Register                offset: 0x50
        __IO u32 IC_CLR_RD_REQ;
    };
    union {
        __IO u32 TX_ABRT;                                                      ///< Clear TX_ABRT Interrupt Register               offset: 0x54
        __IO u32 IC_CLR_TX_ABRT;
    };
    union {
        __IO u32 RX_DONE;                                                      ///< Clear RX_DONE Interrupt Register               offset: 0x58
        __IO u32 IC_CLR_RX_DONE;
    };
    union {
        __IO u32 ACTIV;                                                        ///< Clear ACTIVITY Interrupt Register              offset: 0x5C
        __IO u32 IC_CLR_ACTIVITY;
    };
    union {
        __IO u32 STOP;                                                         ///< Clear STOP_DET Interrupt Register              offset: 0x60
        __IO u32 IC_CLR_STOP_DET;
    };
    union {
        __IO u32 START;                                                        ///< Clear START_DET Interrupt Register             offset: 0x64
        __IO u32 IC_CLR_START_DET;
    };
    union {
        __IO u32 GC;                                                           ///< Clear GEN_CALL Interrupt Register              offset: 0x68
        __IO u32 IC_CLR_GEN_CALL;
    };
    union {
        __IO u32 ENR;                                                          ///< Enable Register                                offset: 0x6C
        __IO u32 IC_ENABLE;
    };
    union {
        __IO u32 SR;                                                           ///< Status Register                                offset: 0x70
        __IO u32 IC_STATUS;
    };
    union {
        __IO u32 TXFLR;                                                        ///< Transmit FIFO Level Register                   offset: 0x74
        __IO u32 IC_TXFLR;
    };
    union {
        __IO u32 RXFLR;                                                        ///< Receive FIFO Level Register                    offset: 0x78
        __IO u32 IC_RXFLR;
    };
    union {
        __IO u32 HOLD;                                                         ///< SDA Hold Time Register                         offset: 0x7C
        __IO u32 IC_SDA_HOLD;
    };
    __IO u32 RESERVED28;                                                       ///IC_TX_ABRT_SOURCE_RESERVED;
    __IO u32 RESERVED29;                                                       ///IC_SLV_DATA_NACK_ONLY_RESERVED;

    union {
        __IO u32 DMA;                                                          ///< DMA Control Register                           offset: 0x88
        __IO u32 IC_DMA_CR;
    };
    __IO u32 RESERVED30;                                                       ///IC_DMA_TDLR_RESERVED;
    __IO u32 RESERVED31;                                                       ///IC_DMA_RDLR_RESERVED;
    union {
        __IO u32 SETUP;                                                        ///< SDA Setup Time Register                        offset: 0x94
        __IO u32 IC_SDA_SETUP;
    };
    union {
        __IO u32 GCR;                                                          ///< ACK General Call Register                      offset: 0x98
        __IO u32 IC_ACK_GENERAL_CALL;
    };
    __IO u32 RESERVED32a;                                                       ///_RESERVED;                                     offset: 0x9C
    __IO u32 RESERVED33;                                                        ///_RESERVED;                                     offset: 0xA0
    __IO u32 RESERVED34;                                                        ///_RESERVED;                                     offset: 0xA4
    __IO u32 RESERVED35;                                                        ///_RESERVED;                                     offset: 0xA8
    __IO u32 RESERVED36;                                                        ///_RESERVED;                                     offset: 0xAC    
    __IO u32 SLVMASK;                                                           ///<I2C Slave Mode Mask Register                  offset: 0xB0
    __IO u32 SLVRCVADDR;                                                        ///<I2C Slave Mode Address Register               offset: 0xB4

} I2C_TypeDef;
#endif
#ifdef USENNEWREGISTER
typedef struct {
    __IO u32 CR;                                                                ///< Control Register                               offset: 0x00
    __IO u32 TAR;                                                               ///< Target Address Register                        offset: 0x04
    __IO u32 SAR;                                                               ///< Slave Address Register                         offset: 0x08
    __IO u32 RESERVED3;
    __IO u32 DR;                                                                ///< Data Command Register                          offset: 0x10
    __IO u32 SSHR;                                                              ///< SCL High Period Count for Std. Speed Register  offset: 0x14
    __IO u32 SSLR;                                                              ///< SCL Low Period Count for Std. Speed Register   offset: 0x18
    __IO u32 FSHR;                                                              ///< SCL High Period Count for Fast Speed Register  offset: 0x1C
    __IO u32 FSLR;                                                              ///< SCL Low Period Count for Fast Speed Register   offset: 0x20
    __IO u32 RESERVED9;
    __IO u32 RESERVED10;
    __IO u32 ISR;                                                               ///< Interrupt Status Register                      offset: 0x2C
    __IO u32 IMR;                                                               ///< Interrupt Mask Register                        offset: 0x30
    __IO u32 RAWISR;                                                            ///< RAW Interrupt Status Register                  offset: 0x34
    __IO u32 RXTLR;                                                             ///< Receive FIFO Threshold Level Register          offset: 0x38
    __IO u32 TXTLR;                                                             ///< Transmit FIFO Threshold Level Register         offset: 0x3C
    __IO u32 ICR;                                                               ///< Clear All Interrupt Register                   offset: 0x40
    __IO u32 RX_UNDER;                                                          ///< Clear RX_UNDER Interrupt Register              offset: 0x44
    __IO u32 RX_OVER;                                                           ///< Clear RX_OVER Interrupt Register               offset: 0x48
    __IO u32 TX_OVER;                                                           ///< Clear TX_OVER Interrupt Register               offset: 0x4C
    __IO u32 RD_REQ;                                                            ///< Clear RD_REQ Interrupt Register                offset: 0x50
    __IO u32 TX_ABRT;                                                           ///< Clear TX_ABRT Interrupt Register               offset: 0x54
    __IO u32 RX_DONE;                                                           ///< Clear RX_DONE Interrupt Register               offset: 0x58
    __IO u32 ACTIV;                                                             ///< Clear ACTIVITY Interrupt Register              offset: 0x5C
    __IO u32 STOP;                                                              ///< Clear STOP_DET Interrupt Register              offset: 0x60
    __IO u32 START;                                                             ///< Clear START_DET Interrupt Register             offset: 0x64
    __IO u32 GC;                                                                ///< Clear GEN_CALL Interrupt Register              offset: 0x68
    __IO u32 ENR;                                                               ///< Enable Register                                offset: 0x6C
    __IO u32 SR;                                                                ///< Status Register                                offset: 0x70
    __IO u32 TXFLR;                                                             ///< Transmit FIFO Level Register                   offset: 0x74
    __IO u32 RXFLR;                                                             ///< Receive FIFO Level Register                    offset: 0x78
    __IO u32 HOLD;                                                              ///< SDA Hold Time Register                         offset: 0x7C
    __IO u32 RESERVED28;
    __IO u32 RESERVED29;
    __IO u32 RESERVED30;
    __IO u32 RESERVED30a;
    __IO u32 SETUP;                                                             ///< SDA Setup Time Register                        offset: 0x94
    __IO u32 GCR;                                                               ///< ACK General Call Register                      offset: 0x98
} I2C_TypeDef;
#endif
#ifdef USENOLDREGISTER
typedef struct {
    __IO u32 IC_CON;
    __IO u32 IC_TAR;
    __IO u32 IC_SAR;
    __IO u32 IC_HS_MADDR_RESERVED;
    __IO u32 IC_DATA_CMD;
    __IO u32 IC_SS_SCL_HCNT;
    __IO u32 IC_SS_SCL_LCNT;
    __IO u32 IC_FS_SCL_HCNT;
    __IO u32 IC_FS_SCL_LCNT;
    __IO u32 IC_HS_SCL_HCNT_RESERVED;
    __IO u32 IC_HS_SCL_LCNT_RESERVED;
    __IO u32 IC_INTR_STAT;
    __IO u32 IC_INTR_MASK;
    __IO u32 IC_RAW_INTR_STAT;
    __IO u32 IC_RX_TL;
    __IO u32 IC_TX_TL;
    __IO u32 IC_CLR_INTR;
    __IO u32 IC_CLR_RX_UNDER;
    __IO u32 IC_CLR_RX_OVER;
    __IO u32 IC_CLR_TX_OVER;
    __IO u32 IC_CLR_RD_REQ;
    __IO u32 IC_CLR_TX_ABRT;
    __IO u32 IC_CLR_RX_DONE;
    __IO u32 IC_CLR_ACTIVITY;
    __IO u32 IC_CLR_STOP_DET;
    __IO u32 IC_CLR_START_DET;
    __IO u32 IC_CLR_GEN_CALL;
    __IO u32 IC_ENABLE;
    __IO u32 IC_STATUS;
    __IO u32 IC_TXFLR;
    __IO u32 IC_RXFLR;
    __IO u32 IC_SDA_HOLD;
    __IO u32 IC_TX_ABRT_SOURCE_RESERVED;
    __IO u32 IC_SLV_DATA_NACK_ONLY_RESERVED;
    __IO u32 IC_DMA_CR;
    __IO u32 IC_DMA_TDLR_RESERVED;
    __IO u32 IC_DMA_RDLR_RESERVED;
    __IO u32 IC_SDA_SETUP;
    __IO u32 IC_ACK_GENERAL_CALL;
} I2C_TypeDef;
#endif



////////////////////////////////////////////////////////////////////////////////
/// @brief I2C type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C1                            ((I2C_TypeDef*)I2C1_BASE)
#define I2C2                            ((I2C_TypeDef*)I2C2_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_CR_MASTER_Pos               (0)
#define I2C_CR_MASTER                   (0x01U << I2C_CR_MASTER_Pos)            ///< I2C master mode enable
#define I2C_CR_SPEED_Pos                (1)
#define I2C_CR_SPEED                    (0x03U << I2C_CR_SPEED_Pos)             ///< I2C speed mode
#define I2C_CR_STD                      (0x01U << I2C_CR_SPEED_Pos)             ///< I2C standard speed mode
#define I2C_CR_FAST                     (0x02U << I2C_CR_SPEED_Pos)             ///< I2C fast speed mode
#define I2C_CR_SLAVE10_Pos              (3)
#define I2C_CR_SLAVE10                  (0x01U << I2C_CR_SLAVE10_Pos)           ///< I2C slave mode responds to 10-bit address
#define I2C_CR_MASTER10_Pos             (4)
#define I2C_CR_MASTER10                 (0x01U << I2C_CR_MASTER10_Pos)          ///< I2C master mode responds to 10-bit address
#define I2C_CR_REPEN_Pos                (5)
#define I2C_CR_REPEN                    (0x01U << I2C_CR_REPEN_Pos)             ///< Enable send RESTART
#define I2C_CR_SLAVEDIS_Pos             (6)
#define I2C_CR_SLAVEDIS                 (0x01U << I2C_CR_SLAVEDIS_Pos)          ///< I2C slave mode disable
#define I2C_CR_STOPINT_Pos              (7)
#define I2C_CR_STOPINT                  (0x01U << I2C_CR_STOPINT_Pos)           ///< Generate STOP interrupt in slave mode
#define I2C_CR_EMPINT_Pos               (8)
#define I2C_CR_EMPINT                   (0x01U << I2C_CR_EMPINT_Pos)            ///< I2C TX_EMPTY interrupt

#define I2C_CR_STOP_Pos             (9)
#define I2C_CR_STOP                 (0x01U << I2C_CR_STOP_Pos)                  ///< STOP signal enable
#define I2C_CR_RESTART_Pos          (10)
#define I2C_CR_RESTART              (0x01U << I2C_CR_RESTART_Pos)               ///< RESTART signal enable
#define I2C_CR_SLV_TX_ABRT_DIS_Pos  (11)
#define I2C_CR_SLV_TX_ABRT_DIS      (0x01U << I2C_CR_SLV_TX_ABRT_DIS_Pos)       ///< I2C as a slave
#define I2C_CR_PADSEL_Pos           (12)
#define I2C_CR_PADSEL               (0x01U << I2C_CR_PADSEL_Pos)               ///< PAD mode select

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_TAR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_TAR_ADDR_Pos                (0)
#define I2C_TAR_ADDR                    (0x03FFU << I2C_TAR_ADDR_Pos)           ///< Target address for master mode
#define I2C_TAR_GC_Pos                  (10)
#define I2C_TAR_GC                      (0x01U << I2C_TAR_GC_Pos)               ///< General Call or START byte
#define I2C_TAR_SPECIAL_Pos             (11)
#define I2C_TAR_SPECIAL                 (0x01U << I2C_TAR_SPECIAL_Pos)          ///< Special command enable like General Call or START byte

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_SAR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_SAR_ADDR_Pos                (0)
#define I2C_SAR_ADDR                    (0x03FFU << I2C_SAR_ADDR_Pos)           ///< Slave address

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_DR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_DR_DAT_Pos                  (0)
#define I2C_DR_DAT                      (0xFFU << I2C_DR_DAT_Pos)               ///< The data to be transmitted or received
#define I2C_DR_CMD_Pos                  (8)
#define I2C_DR_CMD                      (0x01U << I2C_DR_CMD_Pos)               ///< Read or write command


////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_SSHR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_SSHR_CNT_Pos                (0)
#define I2C_SSHR_CNT                    (0xFFFFU << I2C_SSHR_CNT_Pos)           ///< SCL clock high period count for standard speed

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_SSLR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_SSLR_CNT_Pos                (0)
#define I2C_SSLR_CNT                    (0xFFFFU << I2C_SSLR_CNT_Pos)           ///< SCL clock low period count for standard speed

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_FSHR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_FSHR_CNT_Pos                (0)
#define I2C_FSHR_CNT                    (0xFFFFU << I2C_FSHR_CNT_Pos)           ///< SCL clock high period count for fast speed

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_FSLR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_FSLR_CNT_Pos                (0)
#define I2C_FSLR_CNT                    (0xFFFFU << I2C_FSLR_CNT_Pos)           ///< SCL clock low period count for fast speed

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_ISR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_ISR_RX_UNDER_Pos            (0)
#define I2C_ISR_RX_UNDER                (0x01U << I2C_ISR_RX_UNDER_Pos)         ///< RX_UNDER interrupt status
#define I2C_ISR_RX_OVER_Pos             (1)
#define I2C_ISR_RX_OVER                 (0x01U << I2C_ISR_RX_OVER_Pos)          ///< RX_OVER interrupt status
#define I2C_ISR_RX_FULL_Pos             (2)
#define I2C_ISR_RX_FULL                 (0x01U << I2C_ISR_RX_FULL_Pos)          ///< RX_FULL interrupt status
#define I2C_ISR_TX_OVER_Pos             (3)
#define I2C_ISR_TX_OVER                 (0x01U << I2C_ISR_TX_OVER_Pos)          ///< TX_OVER interrupt status
#define I2C_ISR_TX_EMPTY_Pos            (4)
#define I2C_ISR_TX_EMPTY                (0x01U << I2C_ISR_TX_EMPTY_Pos)         ///< TX_EMPTY interrupt status
#define I2C_ISR_RX_REQ_Pos              (5)
#define I2C_ISR_RX_REQ                  (0x01U << I2C_ISR_RX_REQ_Pos)           ///< RX_REQ interrupt status
#define I2C_ISR_TX_ABRT_Pos             (6)
#define I2C_ISR_TX_ABRT                 (0x01U << I2C_ISR_TX_ABRT_Pos)          ///< TX_ABRT interrupt status
#define I2C_ISR_RX_DONE_Pos             (7)
#define I2C_ISR_RX_DONE                 (0x01U << I2C_ISR_RX_DONE_Pos)          ///< RX_DONE interrupt status
#define I2C_ISR_ACTIV_Pos               (8)
#define I2C_ISR_ACTIV                   (0x01U << I2C_ISR_ACTIV_Pos)            ///< ACTIVITY interrupt status
#define I2C_ISR_STOP_Pos                (9)
#define I2C_ISR_STOP                    (0x01U << I2C_ISR_STOP_Pos)             ///< STOP_DET interrupt status
#define I2C_ISR_START_Pos               (10)
#define I2C_ISR_START                   (0x01U << I2C_ISR_START_Pos)            ///< START_DET interrupt status
#define I2C_ISR_GC_Pos                  (11)
#define I2C_ISR_GC                      (0x01U << I2C_ISR_GC_Pos)               ///< GEN_CALL interrupt status
#define I2C_ISR_RESTART_Pos             (12)
#define I2C_ISR_RESTART                 (0x01U << I2C_ISR_RESTART_Pos)          ///< RESTART_DET interrupt status
#define I2C_ISR_HOLD_Pos                (13)
#define I2C_ISR_HOLD                    (0x01U << I2C_ISR_HOLD_Pos)             ///< MST_ON_HOLD interrupt status
////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_IMR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_IMR_RX_UNDER_Pos            (0)
#define I2C_IMR_RX_UNDER                (0x01U << I2C_IMR_RX_UNDER_Pos)         ///< RX_UNDER interrupt mask
#define I2C_IMR_RX_OVER_Pos             (1)
#define I2C_IMR_RX_OVER                 (0x01U << I2C_IMR_RX_OVER_Pos)          ///< RX_OVER interrupt mask
#define I2C_IMR_RX_FULL_Pos             (2)
#define I2C_IMR_RX_FULL                 (0x01U << I2C_IMR_RX_FULL_Pos)          ///< RX_FULL interrupt mask
#define I2C_IMR_TX_OVER_Pos             (3)
#define I2C_IMR_TX_OVER                 (0x01U << I2C_IMR_TX_OVER_Pos)          ///< TX_OVER interrupt mask
#define I2C_IMR_TX_EMPTY_Pos            (4)
#define I2C_IMR_TX_EMPTY                (0x01U << I2C_IMR_TX_EMPTY_Pos)         ///< TX_EMPTY interrupt mask
#define I2C_IMR_RX_REQ_Pos              (5)
#define I2C_IMR_RX_REQ                  (0x01U << I2C_IMR_RX_REQ_Pos)           ///< RX_REQ interrupt mask
#define I2C_IMR_TX_ABRT_Pos             (6)
#define I2C_IMR_TX_ABRT                 (0x01U << I2C_IMR_TX_ABRT_Pos)          ///< TX_ABRT interrupt mask
#define I2C_IMR_RX_DONE_Pos             (7)
#define I2C_IMR_RX_DONE                 (0x01U << I2C_IMR_RX_DONE_Pos)          ///< RX_DONE interrupt mask

#define I2C_IMR_ACTIV_Pos               (8)
#define I2C_IMR_ACTIV                   (0x01U << I2C_IMR_ACTIV_Pos)            ///< ACTIVITY interrupt status
#define I2C_IMR_STOP_Pos                (9)
#define I2C_IMR_STOP                    (0x01U << I2C_IMR_STOP_Pos)             ///< STOP_DET interrupt status
#define I2C_IMR_START_Pos               (10)
#define I2C_IMR_START                   (0x01U << I2C_IMR_START_Pos)            ///< START_DET interrupt status
#define I2C_IMR_GC_Pos                  (11)
#define I2C_IMR_GC                      (0x01U << I2C_IMR_GC_Pos)               ///< GEN_CALL interrupt status
#define I2C_IMR_RESTART_Pos             (12)
#define I2C_IMR_RESTART                 (0x01U << I2C_IMR_RESTART_Pos)          ///< RESTART_DET interrupt status
#define I2C_IMR_HOLD_Pos                (13)
#define I2C_IMR_HOLD                    (0x01U << I2C_IMR_HOLD_Pos)             ///< MST_ON_HOLD interrupt status
////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_RAWISR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_RAWISR_RX_UNDER_Pos         (0)
#define I2C_RAWISR_RX_UNDER             (0x01U << I2C_RAWISR_RX_UNDER_Pos)      ///< RX_UNDER raw interrupt status
#define I2C_RAWISR_RX_OVER_Pos          (1)
#define I2C_RAWISR_RX_OVER              (0x01U << I2C_RAWISR_RX_OVER_Pos)       ///< RX_OVER raw interrupt status
#define I2C_RAWISR_RX_FULL_Pos          (2)
#define I2C_RAWISR_RX_FULL              (0x01U << I2C_RAWISR_RX_FULL_Pos)       ///< RX_FULL raw interrupt status
#define I2C_RAWISR_TX_OVER_Pos          (3)
#define I2C_RAWISR_TX_OVER              (0x01U << I2C_RAWISR_TX_OVER_Pos)       ///< TX_OVER raw interrupt status
#define I2C_RAWISR_TX_EMPTY_Pos         (4)
#define I2C_RAWISR_TX_EMPTY             (0x01U << I2C_RAWISR_TX_EMPTY_Pos)      ///< TX_EMPTY raw interrupt status
#define I2C_RAWISR_RX_REQ_Pos           (5)
#define I2C_RAWISR_RX_REQ               (0x01U << I2C_RAWISR_RX_REQ_Pos)        ///< RX_REQ raw interrupt status
#define I2C_RAWISR_TX_ABRT_Pos          (6)
#define I2C_RAWISR_TX_ABRT              (0x01U << I2C_RAWISR_TX_ABRT_Pos)       ///< TX_ABRT raw interrupt status
#define I2C_RAWISR_RX_DONE_Pos          (7)
#define I2C_RAWISR_RX_DONE              (0x01U << I2C_RAWISR_RX_DONE_Pos)       ///< RX_DONE raw interrupt status

#define I2C_RAWISR_ACTIV_Pos            (8)
#define I2C_RAWISR_ACTIV                (0x01U << I2C_RAWISR_ACTIV_Pos)         ///< ACTIVITY interrupt status
#define I2C_RAWISR_STOP_Pos             (9)
#define I2C_RAWISR_STOP                 (0x01U << I2C_RAWISR_STOP_Pos)          ///< STOP_DET interrupt status
#define I2C_RAWISR_START_Pos            (10)
#define I2C_RAWISR_START                (0x01U << I2C_RAWISR_START_Pos)         ///< START_DET interrupt status
#define I2C_RAWISR_GC_Pos               (11)
#define I2C_RAWISR_GC                   (0x01U << I2C_RAWISR_GC_Pos)            ///< GEN_CALL interrupt status
#define I2C_RAWISR_RESTART_Pos          (12)
#define I2C_RAWISR_RESTART              (0x01U << I2C_RAWISR_RESTART_Pos)       ///< RESTART_DET interrupt status
#define I2C_RAWISR_HOLD_Pos             (13)
#define I2C_RAWISR_HOLD                 (0x01U << I2C_RAWISR_HOLD_Pos)          ///< MST_ON_HOLD interrupt status
////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_RXTLR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_RXTLR_Pos                   (0)
#define I2C_RXTLR_TL                    (0xFFU << I2C_RXTLR_Pos)                ///< Receive FIFO threshold level

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_TXTLR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_TXTLR_Pos                   (0)
#define I2C_TXTLR_TL                    (0xFFU << I2C_TXTLR_Pos)                ///< Transmit FIFO threshold level

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_ICR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_ICR_Pos                     (0)
#define I2C_ICR                         (0x01U << I2C_ICR_Pos)                  ///< Read this register to clear the combined interrupt, all individual interrupts

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_RX_UNDER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_RX_UNDER_Pos                (0)
#define I2C_RX_UNDER                    (0x01U << I2C_RX_UNDER_Pos)             ///< Read this register to clear the RX_UNDER interrupt of the I2C_RAW_INTR_STAT register

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_RX_OVER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_RX_OVER_Pos                 (0)
#define I2C_RX_OVER                     (0x01U << I2C_RX_OVER_Pos)              ///< Read this register to clear the RX_OVER interrupt of the I2C_RAW_INTR_STAT register
////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_TX_OVER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_TX_OVER_Pos                 (0)
#define I2C_TX_OVER                     (0x01U << I2C_TX_OVER_Pos)              ///< Read this register to clear the TX_OVER interrupt of the I2C_RAW_INTR_STAT register

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_RD_REQ Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_RD_REQ_Pos                  (0)
#define I2C_RD_REQ                      (0x01U << I2C_RD_REQ_Pos)               ///< Read this register to clear the RD_REQ interrupt of the I2C_RAW_INTR_STAT register

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_TX_ABRT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_TX_ABRT_Pos                 (0)
#define I2C_TX_ABRT                     (0x01U << I2C_TX_ABRT_Pos)              ///< Read this register to clear the TX_ABRT interrupt of the I2C_RAW_INTR_STAT register

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_RX_DONE Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_RX_DONE_Pos                 (0)
#define I2C_RX_DONE                     (0x01U << I2C_RX_DONE_Pos)              ///< Read this register to clear the RX_DONE interrupt of the I2C_RAW_INTR_STAT register

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_ACTIV Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_ACTIV_Pos                   (0)
#define I2C_ACTIV                       (0x01U << I2C_ACTIV_Pos)                ///< Read this register to clear the ACTIVITY interrupt of the I2C_RAW_INTR_STAT register
////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_STOP Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_STOP_Pos                    (0)
#define I2C_STOP                        (0x01U << I2C_STOP_Pos)                 ///< Read this register to clear the STOP_DET interrupt of the I2C_RAW_INTR_STAT register

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_START Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_START_Pos                   (0)
#define I2C_START                       (0x01U << I2C_START_Pos)                ///< Read this register to clear the START_DET interrupt of the I2C_RAW_INTR_STAT register

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_GC Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_GC_Pos                      (0)
#define I2C_GC                          (0x01U << I2C_GC_Pos)                   ///< Read this register to clear the GEN_CALL interrupt of the I2C_RAW_INTR_STAT register

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_ENR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_ENR_ENABLE_Pos              (0)
#define I2C_ENR_ENABLE                  (0x01U << I2C_ENR_ENABLE_Pos)           ///< I2C mode enable
#define I2C_ENR_ABORT_Pos               (1)
#define I2C_ENR_ABORT                   (0x01U << I2C_ENR_ABORT_Pos)            ///< I2C transfer abort

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_SR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_SR_ACTIV_Pos                (0)
#define I2C_SR_ACTIV                    (0x01U << I2C_SR_ACTIV_Pos)             ///< I2C activity status
#define I2C_SR_TFNF_Pos                 (1)
#define I2C_SR_TFNF                     (0x01U << I2C_SR_TFNF_Pos)              ///< Transmit FIFO not full
#define I2C_SR_TFE_Pos                  (2)
#define I2C_SR_TFE                      (0x01U << I2C_SR_TFE_Pos)               ///< Transmit FIFO completely empty
#define I2C_SR_RFNE_Pos                 (3)
#define I2C_SR_RFNE                     (0x01U << I2C_SR_RFNE_Pos)              ///< Receive FIFO not empty
#define I2C_SR_RFF_Pos                  (4)
#define I2C_SR_RFF                      (0x01U << I2C_SR_RFF_Pos)               ///< Receive FIFO completely full
#define I2C_SR_MST_ACTIV_Pos            (5)
#define I2C_SR_MST_ACTIV                (0x01U << I2C_SR_MST_ACTIV_Pos)         ///< Master FSM activity status
#define I2C_SR_SLV_ACTIV_Pos            (6)
#define I2C_SR_SLV_ACTIV                (0x01U << I2C_SR_SLV_ACTIV_Pos)         ///< Slave FSM activity status

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_TXFLR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_TXFLR_CNT_Pos               (0)
#define I2C_TXFLR_CNT                   (0x03U << I2C_TXFLR_CNT_Pos)            ///< Number of valid data in the transmit FIFO

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_RXFLR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_RXFLR_CNT_Pos               (0)
#define I2C_RXFLR_CNT                   (0x03U << I2C_RXFLR_CNT_Pos)            ///< Number of valid data in the receive FIFO

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_HOLD Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_HOLD_TXCNT_Pos              (0)
#define I2C_HOLD_TXCNT                  (0xFFFFU << I2C_HOLD_TXCNT_Pos)         ///< SDA hold time when I2C acts as a transmit
#define I2C_HOLD_RXCNT_Pos              (16)
#define I2C_HOLD_RXCNT                  (0xFFU << I2C_HOLD_RXCNT_Pos)           ///< SDA hold time when I2C acts as a receiver

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_DMA Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_DMA_RXEN_Pos                (0)
#define I2C_DMA_RXEN                    (0x01U << I2C_DMA_RXEN_Pos)             ///< Receive DMA enable
#define I2C_DMA_TXEN_Pos                (1)
#define I2C_DMA_TXEN                    (0x01U << I2C_DMA_TXEN_Pos)             ///< Transmit DMA enable
////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_SETUP Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_SETUP_CNT_Pos               (0)
#define I2C_SETUP_CNT                   (0xFFU << I2C_SETUP_CNT_Pos)            ///< SDA setup

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C_GCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define I2C_GCR_GC_Pos                  (0)
#define I2C_GCR_GC                      (0x01U << I2C_GCR_GC_Pos)               ///< ACK general call


#define I2C_SLVMASK_Pos                (0)
#define I2C_SLVMASK                    (0x3FFU <<I2C_SLVMASK_Pos)

#define I2C_SLVRCVADDR_Pos             (0)
#define I2C_SLVRCVADDR                 (0x3FFU <<I2C_SLVRCVADDR_Pos)


/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
