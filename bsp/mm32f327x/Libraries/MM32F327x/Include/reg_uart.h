////////////////////////////////////////////////////////////////////////////////
/// @file     reg_uart.h
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

#ifndef __REG_UART_H
#define __REG_UART_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif










////////////////////////////////////////////////////////////////////////////////
/// @brief UART Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define UART1_BASE                      (APB2PERIPH_BASE + 0x3800)              ///< Base Address: 0x40013800
#define UART2_BASE                      (APB1PERIPH_BASE + 0x4400)              ///< Base Address: 0x40004400
#define UART3_BASE                      (APB1PERIPH_BASE + 0x4800)              ///< Base Address: 0x40004800
#define UART4_BASE                      (APB1PERIPH_BASE + 0x4C00)              ///< Base Address: 0x40004C00
#define UART5_BASE                      (APB1PERIPH_BASE + 0x5000)              ///< Base Address: 0x40005000
#define UART6_BASE                      (APB2PERIPH_BASE + 0x3C00)              ///< Base Address: 0x40013C00
#define UART7_BASE                      (APB1PERIPH_BASE + 0x7800)              ///< Base Address: 0x40007800
#define UART8_BASE                      (APB1PERIPH_BASE + 0x7C00)              ///< Base Address: 0x40007C00







////////////////////////////////////////////////////////////////////////////////
/// @brief UART Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 TDR;                                                               ///< Transmit Data Register,                        offset: 0x00
    __IO u32 RDR;                                                               ///< Receive Data Register,                         offset: 0x04
    __IO u32 CSR;                                                               ///< Current Status Register,                       offset: 0x08
    __IO u32 ISR;                                                               ///< Interrupt Status Register,                     offset: 0x0C
    __IO u32 IER;                                                               ///< Interrupt Enable Register,                     offset: 0x10
    __IO u32 ICR;                                                               ///< Interrupt Clear Register,                      offset: 0x14
    __IO u32 GCR;                                                               ///< Global Control Register,                       offset: 0x18
    __IO u32 CCR;                                                               ///< Config Control Register,                       offset: 0x1C
    __IO u32 BRR;                                                               ///< Baud Rate Register,                            offset: 0x20
    __IO u32 FRA;                                                               ///< Fraction Register,                             offset: 0x24

    __IO u32 RXAR;                                                              ///< Receive Address Register,                      offset: 0x28
    __IO u32 RXMR;                                                              ///< Receive Address Mask Register,                 offset: 0x2C
    __IO u32 SCR;                                                               ///< Smart Card Register,                           offset: 0x30

    __IO u32 IDLR;                                                              ///< Data length register                          offset: 0x34
    __IO u32 ABRCR;                                                             ///< automatic Baud rate control delivery          offset: 0x38
    __IO u32 IRDA;                                                              ///< Infrared function control register,           offset: 0x3C
} UART_TypeDef;


////////////////////////////////////////////////////////////////////////////////
/// @brief UART type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define UART1                           ((UART_TypeDef*) UART1_BASE)
#define UART2                           ((UART_TypeDef*) UART2_BASE)

#define UART3                           ((UART_TypeDef*) UART3_BASE)
#define UART4                           ((UART_TypeDef*) UART4_BASE)
#define UART5                           ((UART_TypeDef*) UART5_BASE)
#define UART6                           ((UART_TypeDef*) UART6_BASE)
#define UART7                           ((UART_TypeDef*) UART7_BASE)
#define UART8                           ((UART_TypeDef*) UART8_BASE)


////////////////////////////////////////////////////////////////////////////////
/// @brief UART_TDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_TDR_DATA_Pos               (0)
#define UART_TDR_DATA                   (0xFFU << UART_TDR_DATA_Pos)            ///< Transmit data register

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_RDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_RDR_DATA_Pos               (0)
#define UART_RDR_DATA                   (0xFFU << UART_RDR_DATA_Pos)            ///< Receive data register

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_CSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_CSR_TXC_Pos                (0)
#define UART_CSR_TXC                    (0x01U << UART_CSR_TXC_Pos)             ///< Transmit complete flag bit
#define UART_CSR_RXAVL_Pos              (1)
#define UART_CSR_RXAVL                  (0x01U << UART_CSR_RXAVL_Pos)           ///< Receive valid data flag bit
#define UART_CSR_TXFULL_Pos             (2)
#define UART_CSR_TXFULL                 (0x01U << UART_CSR_TXFULL_Pos)          ///< Transmit buffer full flag bit
#define UART_CSR_TXEPT_Pos              (3)
#define UART_CSR_TXEPT                  (0x01U << UART_CSR_TXEPT_Pos)           ///< Transmit buffer empty flag bit

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_ISR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_ISR_TX_Pos                 (0)
#define UART_ISR_TX                     (0x01U << UART_ISR_TX_Pos)              ///< Transmit buffer empty interrupt flag bit
#define UART_ISR_RX_Pos                 (1)
#define UART_ISR_RX                     (0x01U << UART_ISR_RX_Pos)              ///< Receive valid data interrupt flag bit

#define UART_ISR_TXC_Pos                (2)
#define UART_ISR_TXC                    (0x01U << UART_ISR_TXC_Pos)             ///< Transmit complete interrupt flag bit

#define UART_ISR_RXOERR_Pos             (3)
#define UART_ISR_RXOERR                 (0x01U << UART_ISR_RXOERR_Pos)          ///< Receive overflow error interrupt flag bit
#define UART_ISR_RXPERR_Pos             (4)
#define UART_ISR_RXPERR                 (0x01U << UART_ISR_RXPERR_Pos)          ///< Parity error interrupt flag bit
#define UART_ISR_RXFERR_Pos             (5)
#define UART_ISR_RXFERR                 (0x01U << UART_ISR_RXFERR_Pos)          ///< Frame error interrupt flag bit
#define UART_ISR_RXBRK_Pos              (6)
#define UART_ISR_RXBRK                  (0x01U << UART_ISR_RXBRK_Pos)           ///< Receive frame break interrupt flag bit

#define UART_ISR_TXBRK_Pos              (7)
#define UART_ISR_TXBRK                  (0x01U << UART_ISR_TXBRK_Pos)           ///< Transmit Break Frame Interrupt Flag Bit
#define UART_ISR_RXB8_Pos               (8)
#define UART_ISR_RXB8                   (0x01U << UART_ISR_RXB8_Pos)            ///< Receive Bit 8 Interrupt Flag Bit

#define UART_ISR_RXIDLE_Pos             (9)
#define UART_ISR_RXIDLE                 (0x01U << UART_ISR_RXIDLE_Pos)          ///< Receive Bit 8 Interrupt clear Bit
#define UART_ISR_ABREND_INTF_Pos         (10)
#define UART_ISR_ABREND_INTF             (0x01U << UART_ISR_ABREND_INTF_Pos)          ///< Auto baud rate end interrupt flag bit
#define UART_ISR_ABRERR_INTF_Pos         (11)
#define UART_ISR_ABRERR_INTF             (0x01U << UART_ISR_ABRERR_INTF_Pos)          ///< Auto baud rate error interrupt flag bit

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_IER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_IER_TX_Pos                 (0)
#define UART_IER_TX                     (0x01U << UART_IER_TX_Pos)              ///< Transmit buffer empty interrupt enable bit
#define UART_IER_RX_Pos                 (1)
#define UART_IER_RX                     (0x01U << UART_IER_RX_Pos)              ///< Receive buffer interrupt enable bit

#define UART_IER_TXC_Pos                (2)
#define UART_IER_TXC                    (0x01U << UART_IER_TXC_Pos)             ///< Transmit complete interrupt enable bit

#define UART_IER_RXOERR_Pos             (3)
#define UART_IER_RXOERR                 (0x01U << UART_IER_RXOERR_Pos)          ///< Receive overflow error interrupt enable bit
#define UART_IER_RXPERR_Pos             (4)
#define UART_IER_RXPERR                 (0x01U << UART_IER_RXPERR_Pos)          ///< Parity error interrupt enable bit
#define UART_IER_RXFERR_Pos             (5)
#define UART_IER_RXFERR                 (0x01U << UART_IER_RXFERR_Pos)          ///< Frame error interrupt enable bit
#define UART_IER_RXBRK_Pos              (6)
#define UART_IER_RXBRK                  (0x01U << UART_IER_RXBRK_Pos)           ///< Receive frame break interrupt enable bit

#define UART_IER_TXBRK_Pos              (7)
#define UART_IER_TXBRK                  (0x01U << UART_IER_TXBRK_Pos)           ///< Transmit Break Frame Interrupt Enable Bit
#define UART_IER_RXB8_Pos               (8)
#define UART_IER_RXB8                   (0x01U << UART_IER_RXB8_Pos)            ///< Receive Bit 8 Interrupt Enable Bit

#define UART_IER_RXIDLE_Pos             (9)
#define UART_IER_RXIDLE                 (0x01U << UART_IER_RXIDLE_Pos)          ///< Receive Bit 8 Interrupt clear Bit
#define UART_IER_ABREND_IEN_Pos         (10)
#define UART_IER_ABREND_IEN             (0x01U << UART_IER_ABREND_IEN_Pos)          ///< Auto baud rate end enable bit
#define UART_IER_ABRERR_IEN_Pos         (11)
#define UART_IER_ABRERR_IEN             (0x01U << UART_IER_ABRERR_IEN_Pos)          ///< Auto baud rate error enable bit

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_ICR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////

#define UART_ICR_TX_Pos                 (0)
#define UART_ICR_TX                     (0x01U << UART_ICR_TX_Pos)              ///< Transmit buffer empty interrupt clear bit
#define UART_ICR_RX_Pos                 (1)
#define UART_ICR_RX                     (0x01U << UART_ICR_RX_Pos)              ///< Receive interrupt clear bit

#define UART_ICR_TXC_Pos                (2)
#define UART_ICR_TXC                    (0x01U << UART_ICR_TXC_Pos)             ///< Transmit complete interrupt clear bit

#define UART_ICR_RXOERR_Pos             (3)
#define UART_ICR_RXOERR                 (0x01U << UART_ICR_RXOERR_Pos)          ///< Receive overflow error interrupt clear bit
#define UART_ICR_RXPERR_Pos             (4)
#define UART_ICR_RXPERR                 (0x01U << UART_ICR_RXPERR_Pos)          ///< Parity error interrupt clear bit

#define UART_ICR_RXFERR_Pos             (5)
#define UART_ICR_RXFERR                 (0x01U << UART_ICR_RXFERR_Pos)          ///< Frame error interrupt clear bit
#define UART_ICR_RXBRK_Pos              (6)
#define UART_ICR_RXBRK                  (0x01U << UART_ICR_RXBRK_Pos)           ///< Receive frame break interrupt clear bit

#define UART_ICR_TXBRK_Pos              (7)
#define UART_ICR_TXBRK                  (0x01U << UART_ICR_TXBRK_Pos)           ///< Transmit Break Frame Interrupt clear Bit
#define UART_ICR_RXB8_Pos               (8)
#define UART_ICR_RXB8                   (0x01U << UART_ICR_RXB8_Pos)            ///< Receive Bit 8 Interrupt clear Bit

#define UART_ICR_RXIDLE_Pos             (9)
#define UART_ICR_RXIDLE                 (0x01U << UART_ICR_RXIDLE_Pos)          ///< Receive Bit 8 Interrupt clear Bit
#define UART_ICR_ABRENDCLR_Pos         (10)
#define UART_ICR_ABRENDCLR             (0x01U << UART_ICR_ABRENDCLR_Pos)          ///< Auto baud rate end clear bit
#define UART_ICR_ABRERRCLR_Pos         (11)
#define UART_ICR_ABRERRCLR             (0x01U << UART_ICR_ABRERRCLR_Pos)          ///< Auto baud rate error clear bit

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_GCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_GCR_UART_Pos               (0)
#define UART_GCR_UART                   (0x01U << UART_GCR_UART_Pos)            ///< UART mode selection bit
#define UART_GCR_DMA_Pos                (1)
#define UART_GCR_DMA                    (0x01U << UART_GCR_DMA_Pos)             ///< DMA mode selection bit
#define UART_GCR_AUTOFLOW_Pos           (2)
#define UART_GCR_AUTOFLOW               (0x01U << UART_GCR_AUTOFLOW_Pos)        ///< Automatic flow control enable bit
#define UART_GCR_RX_Pos                 (3)
#define UART_GCR_RX                     (0x01U << UART_GCR_RX_Pos)              ///< Enable receive
#define UART_GCR_TX_Pos                 (4)
#define UART_GCR_TX                     (0x01U << UART_GCR_TX_Pos)              ///< Enable transmit

#define UART_GCR_SELB8_Pos              (7)
#define UART_GCR_SELB8                  (0x01U << UART_GCR_SELB8_Pos)           ///< UART mode selection bit
#define UART_GCR_SWAP_Pos               (8)
#define UART_GCR_SWAP                   (0x01U << UART_GCR_SWAP_Pos)            ///< DMA mode selection bit
#define UART_GCR_RXTOG_Pos              (9)
#define UART_GCR_RXTOG                  (0x01U << UART_GCR_RXTOG_Pos)           ///< Automatic flow control enable bit
#define UART_GCR_TXTOG_Pos              (10)
#define UART_GCR_TXTOG                  (0x01U << UART_GCR_TXTOG_Pos)           ///< Enable receive

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_CCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_CCR_PEN_Pos                (0)
#define UART_CCR_PEN                    (0x01U << UART_CCR_PEN_Pos)             ///< Parity enable bit
#define UART_CCR_PSEL_Pos               (1)
#define UART_CCR_PSEL                   (0x01U << UART_CCR_PSEL_Pos)            ///< Parity selection bit

#define UART_CCR_SPB_Pos                (2)
#define UART_CCR_SPB                    (0x01U << UART_CCR_SPB_Pos)             ///< Stop bit selection



#define UART_CCR_SPB0_Pos               UART_CCR_SPB_Pos
#define UART_CCR_SPB0                   UART_CCR_SPB                            ///< Stop bit 0 selection

#define UART_CCR_BRK_Pos                (3)
#define UART_CCR_BRK                    (0x01U << UART_CCR_BRK_Pos)             ///< UART transmit frame break
#define UART_CCR_CHAR_Pos               (4)
#define UART_CCR_CHAR                   (0x03U << UART_CCR_CHAR_Pos)            ///< UART width bit
#define UART_CCR_CHAR_5b                (0x00U << UART_CCR_CHAR_Pos)            ///< UART Word Length 5b
#define UART_CCR_CHAR_6b                (0x01U << UART_CCR_CHAR_Pos)            ///< UART Word Length 6b
#define UART_CCR_CHAR_7b                (0x02U << UART_CCR_CHAR_Pos)            ///< UART Word Length 7b
#define UART_CCR_CHAR_8b                (0x03U << UART_CCR_CHAR_Pos)            ///< UART Word Length 8b

#define UART_CCR_SPB1_Pos               (6)
#define UART_CCR_SPB1                   (0x01U << UART_CCR_SPB1_Pos)            ///< Stop bit 1 selection
#define UART_CCR_B8RXD_Pos              (7)
#define UART_CCR_B8RXD                  (0x01U << UART_CCR_B8RXD_Pos)           ///< Synchronous frame receive
#define UART_CCR_B8TXD_Pos              (8)
#define UART_CCR_B8TXD                  (0x01U << UART_CCR_B8TXD_Pos)           ///< Synchronous frame transmit
#define UART_CCR_B8POL_Pos              (9)
#define UART_CCR_B8POL                  (0x01U << UART_CCR_B8POL_Pos)           ///< Synchronous frame polarity control bit
#define UART_CCR_B8TOG_Pos              (10)
#define UART_CCR_B8TOG                  (0x01U << UART_CCR_B8TOG_Pos)           ///< Synchronous frame auto toggle bit
#define UART_CCR_B8EN_Pos               (11)
#define UART_CCR_B8EN                   (0x01U << UART_CCR_B8EN_Pos)            ///< Synchronous frame enable bit
#define UART_CCR_RWU_Pos                (12)
#define UART_CCR_RWU                    (0x01U << UART_CCR_RWU_Pos)             ///< Receive wake up method
#define UART_CCR_WAKE_Pos               (13)
#define UART_CCR_WAKE                   (0x01U << UART_CCR_WAKE_Pos)            ///< Wake up method

#define UART_CCR_LIN_Pos            (14)
#define UART_CCR_LIN                (0x01U << UART_CCR_LIN_Pos)             ///< Wake up method

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_BRR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_BRR_MANTISSA_Pos        (0)
#define UART_BRR_MANTISSA            (0xFFFFU << UART_BRR_MANTISSA_Pos)      ///< UART DIV MANTISSA

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_FRA Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_BRR_FRACTION_Pos        (0)
#define UART_BRR_FRACTION            (0x0FU << UART_BRR_FRACTION_Pos)        ///< UART DIV FRACTION

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_RXAR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_RXAR_ADDR_Pos          (0)
#define UART_RXAR_ADDR              (0xFFU << UART_RXAR_ADDR_Pos)           ///< Synchronous frame match address

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_RXMR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_RXMR_MASK_Pos          (0)
#define UART_RXMR_MASK              (0xFFU << UART_RXMR_MASK_Pos)           ///< Synchronous frame match address mask

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_SCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_SCR_SCEN_Pos           (0)
#define UART_SCR_SCEN               (0x01U << UART_SCR_SCEN_Pos)            ///< ISO7816 enable bit
#define UART_SCR_SCARB_Pos          (1)
#define UART_SCR_SCARB              (0x01U << UART_SCR_SCARB_Pos)           ///< ISO7816 check auto answer bit
#define UART_SCR_NACK_Pos           (2)
#define UART_SCR_NACK               (0x01U << UART_SCR_NACK_Pos)            ///< Master receive frame answer bit
#define UART_SCR_SCFCNT_Pos         (4)
#define UART_SCR_SCFCNT             (0xFFU << UART_SCR_SCFCNT_Pos)          ///< ISO7816 protection counter bit
#define UART_SCR_HDSEL_Pos          (12)
#define UART_SCR_HDSEL              (0x01U << UART_SCR_HDSEL_Pos)           ///< Single-line half-duplex mode selection bit
////////////////////////////////////////////////////////////////////////////////
/// @brief UART_ABRCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_ABRCR_ABREN_Pos        (0)
#define UART_ABRCR_ABREN            (0x01U<<UART_ABRCR_ABREN_Pos)
#define UART_ABRCR_BITCNT_Pos       (1)
#define UART_ABRCR_BITCNT           (0x03U<<UART_ABRCR_BITCNT_Pos)
#define UART_ABRCR_BITCNT_MODE0     (0x00U<<UART_ABRCR_BITCNT_Pos)
#define UART_ABRCR_BITCNT_MODE1     (0x01U<<UART_ABRCR_BITCNT_Pos)
#define UART_ABRCR_BITCNT_MODE2     (0x02U<<UART_ABRCR_BITCNT_Pos)
#define UART_ABRCR_BITCNT_MODE3     (0x03U<<UART_ABRCR_BITCNT_Pos)
#define UART_ABRCR_FORMER_Pos       (3)
#define UART_ABRCR_FORMER           (0x01U<<UART_ABRCR_FORMER_Pos)
#define UART_ABRCR_LATTER_Pos       (4)
#define UART_ABRCR_LATTER           (0x01U<<UART_ABRCR_LATTER_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief UART_IDLR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define UART_IDLR_IDLR_Pos          (0)
#define UART_IDLR_IDLR              (0xFFFFU << UART_IDLR_IDLR_Pos)         ///< ISO7816 enable bit



/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
