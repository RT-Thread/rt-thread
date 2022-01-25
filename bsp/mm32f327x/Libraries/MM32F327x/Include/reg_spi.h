////////////////////////////////////////////////////////////////////////////////
/// @file     reg_spi.h
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

#ifndef __REG_SPI_H
#define __REG_SPI_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif








////////////////////////////////////////////////////////////////////////////////
/// @brief SPI Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI2_BASE                       (APB1PERIPH_BASE + 0x3800)              ///< Base Address: 0x40003800
#define SPI1_BASE                       (APB2PERIPH_BASE + 0x3000)              ///< Base Address: 0x400013000
#define SPI3_BASE                       (APB1PERIPH_BASE + 0x3C00)             ///< Base Address: 0x40003C000




////////////////////////////////////////////////////////////////////////////////
/// @brief SPI Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
#undef USENCOMBINEREGISTER
#undef USENNEWREGISTER
#undef USENOLDREGISTER
#define USENCOMBINEREGISTER
#ifdef USENCOMBINEREGISTER
typedef struct {
    union {
        __IO u32 TDR;                                                               ///< SPI transmit data register,                    offset: 0x00
        __IO u32 TXREG;
    };
    union {
        __IO u32 RDR;                                                               ///< SPI receive data register,                     offset: 0x04
        __IO u32 RXREG;
    };
    union {
        __IO u32 SR;                                                                ///< SPI current state register,                    offset: 0x08
        __IO u32 CSTAT;
    };
    union {
        __IO u32 ISR;                                                               ///< SPI interruput state register,                 offset: 0x0C
        __IO u32 INTSTAT;
    };
    union {
        __IO u32 IER;                                                               ///< SPI interruput enable register,                offset: 0x10
        __IO u32 INTEN;
    };
    union {
        __IO u32 ICR;                                                               ///< SPI interruput control register,               offset: 0x14
        __IO u32 INTCLR;
    };
    union {
        __IO u32 GCR;                                                               ///< SPI global control register,                   offset: 0x18
        __IO u32 GCTL;
    };
    union {
        __IO u32 CCR;                                                               ///< SPI common control register,                   offset: 0x1C
        __IO u32 CCTL;
    };
    union {
        __IO u32 BRR;                                                               ///< SPI baud rate control register,                offset: 0x20
        __IO u32 SPBRG;
    };
    union {
        __IO u32 RDNR;                                                              ///< SPI receive data number register,              offset: 0x24
        __IO u32 RXDNR;
    };
    union {
        __IO u32 NSSR;                                                              ///< SPI chip select register,                      offset: 0x28
        __IO u32 SCSR;
    };
    union {
        __IO u32 ECR;                                                               ///< SPI extand control register,                   offset: 0x2C
        __IO u32 EXTCTL;
    };
    __IO u32 CFGR;                                                              ///< I2S configuration register,                   offset: 0x30
} SPI_TypeDef;
#endif
#ifdef USENNEWREGISTER
typedef struct {
    __IO u32 TDR;                                                               ///< SPI transmit data register,                    offset: 0x00
    __IO u32 RDR;                                                               ///< SPI receive data register,                     offset: 0x04
    __IO u32 SR;                                                                ///< SPI current state register,                    offset: 0x08
    __IO u32 ISR;                                                               ///< SPI interruput state register,                 offset: 0x0C
    __IO u32 IER;                                                               ///< SPI interruput enable register,                offset: 0x10
    __IO u32 ICR;                                                               ///< SPI interruput control register,               offset: 0x14
    __IO u32 GCR;                                                               ///< SPI global control register,                   offset: 0x18
    __IO u32 CCR;                                                               ///< SPI common control register,                   offset: 0x1C
    __IO u32 BRR;                                                               ///< SPI baud rate control register,                offset: 0x20
    __IO u32 RDNR;                                                              ///< SPI receive data number register,              offset: 0x24
    __IO u32 NSSR;                                                              ///< SPI chip select register,                      offset: 0x28
    __IO u32 ECR;                                                               ///< SPI extand control register,                   offset: 0x2C
} SPI_TypeDef;
#endif
#ifdef USENOLDREGISTER
typedef struct {
    __IO u32 TXREG;                                                             ///< SPI transmit data register,                    offset: 0x00
    __IO u32 RXREG;                                                             ///< SPI receive data register,                     offset: 0x04
    __IO u32 CSTAT;                                                             ///< SPI current state register,                    offset: 0x08
    __IO u32 INTSTAT;                                                           ///< SPI interruput state register,                 offset: 0x0C
    __IO u32 INTEN;                                                             ///< SPI interruput enable register,                offset: 0x10
    __IO u32 INTCLR;                                                            ///< SPI interruput control register,               offset: 0x14
    __IO u32 GCTL;                                                              ///< SPI global control register,                   offset: 0x18
    __IO u32 CCTL;                                                              ///< SPI common control register,                   offset: 0x1C
    __IO u32 SPBRG;                                                             ///< SPI baud rate control register,                offset: 0x20
    __IO u32 RXDNR;                                                             ///< SPI receive data number register,              offset: 0x24
    __IO u32 NSSR;                                                              ///< SPI chip select register,                      offset: 0x28
    __IO u32 EXTCTL;                                                            ///< SPI extand control register,                   offset: 0x2C
} SPI_TypeDef;
#endif


////////////////////////////////////////////////////////////////////////////////
/// @brief SPI type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI2                            ((SPI_TypeDef*) SPI2_BASE)
#define SPI1                            ((SPI_TypeDef*) SPI1_BASE)
#define SPI3                            ((SPI_TypeDef*) SPI3_BASE)
////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_TDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_TDR_TXREG_Pos               (0)
#define SPI_TDR_TXREG                   (0xFFFFFFFFU << SPI_TDR_TXREG_Pos)      ///< Transmit data register

////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_RDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_RDR_RXREG_Pos               (0)
#define SPI_RDR_RXREG                   (0xFFFFFFFFU << SPI_RDR_RXREG_Pos)      ///< Receive data register

////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_SR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_SR_TXEPT_Pos                (0)
#define SPI_SR_TXEPT                    (0x01U << SPI_SR_TXEPT_Pos)             ///< Transmitter empty bit
#define SPI_SR_RXAVL_Pos                (1)
#define SPI_SR_RXAVL                    (0x01U << SPI_SR_RXAVL_Pos)             ///< Receive available byte data message
#define SPI_SR_TXFULL_Pos               (2)
#define SPI_SR_TXFULL                   (0x01U << SPI_SR_TXFULL_Pos)            ///< Transmitter FIFO full status bit
#define SPI_SR_RXAVL_4BYTE_Pos          (3)
#define SPI_SR_RXAVL_4BYTE              (0x01U << SPI_SR_RXAVL_4BYTE_Pos)       ///< Receive available 4 byte data message
#define SPI_SR_TXFADDR_Pos              (4)
#define SPI_SR_TXFADDR                  (0x0FU << SPI_SR_TXFADDR_Pos)           ///< Transmit FIFO address
#define SPI_SR_RXFADDR_Pos              (8)
#define SPI_SR_RXFADDR                  (0x0FU << SPI_SR_RXFADDR_Pos)           ///< Receive FIFO address
#define SPI_SR_BUSY_Pos                 (12)
#define SPI_SR_BUSY                     (0x01U << SPI_SR_BUSY_Pos)              ///< Data transfer flag
#define SPI_SR_CHSIDE_Pos               (13)
#define SPI_SR_CHSIDE                   (0x01U << SPI_SR_CHSIDE_Pos)            ///< transmission channel     
////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_ISR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_ISR_TX_INTF_Pos             (0)
#define SPI_ISR_TX_INTF                 (0x01U << SPI_ISR_TX_INTF_Pos)          ///<  Transmit FIFO available interrupt flag bit
#define SPI_ISR_RX_INTF_Pos             (1)
#define SPI_ISR_RX_INTF                 (0x01U << SPI_ISR_RX_INTF_Pos)          ///<  Receive data available interrupt flag bit
#define SPI_ISR_UNDERRUN_INTF_Pos       (2)
#define SPI_ISR_UNDERRUN_INTF           (0x01U << SPI_ISR_UNDERRUN_INTF_Pos)    ///<  SPI underrun interrupt flag bit
#define SPI_ISR_RXOERR_INTF_Pos         (3)
#define SPI_ISR_RXOERR_INTF             (0x01U << SPI_ISR_RXOERR_INTF_Pos)      ///<  Receive overrun error interrupt flag bit
#define SPI_ISR_RXMATCH_INTF_Pos        (4)
#define SPI_ISR_RXMATCH_INTF            (0x01U << SPI_ISR_RXMATCH_INTF_Pos)     ///<  Receive data match the RXDNR number, the receive process will be completed and generate the interrupt
#define SPI_ISR_RXFULL_INTF_Pos         (5)
#define SPI_ISR_RXFULL_INTF             (0x01U << SPI_ISR_RXFULL_INTF_Pos)      ///<  RX FIFO full interrupt flag bit
#define SPI_ISR_TXEPT_INTF_Pos          (6)
#define SPI_ISR_TXEPT_INTF              (0x01U << SPI_ISR_TXEPT_INTF_Pos)       ///<  Transmitter empty interrupt flag bit
#define SPI_ISR_FRE_INTF_Pos            (7)
#define SPI_ISR_FRE_INTF                (0x01U << SPI_ISR_FRE_INTF_Pos)         ///< I2S frame transmission error flag bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_IER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_IER_TX_IEN_Pos              (0)
#define SPI_IER_TX_IEN                  (0x01U << SPI_IER_TX_IEN_Pos)           ///<  Transmit FIFO empty interrupt enable bit
#define SPI_IER_RX_IEN_Pos              (1)
#define SPI_IER_RX_IEN                  (0x01U << SPI_IER_RX_IEN_Pos)           ///<  Receive FIFO interrupt enable bit
#define SPI_IER_UNDERRUN_IEN_Pos        (2)
#define SPI_IER_UNDERRUN_IEN            (0x01U << SPI_IER_UNDERRUN_IEN_Pos)     ///<  Transmitter underrun interrupt enable bit
#define SPI_IER_RXOERR_IEN_Pos          (3)
#define SPI_IER_RXOERR_IEN              (0x01U << SPI_IER_RXOERR_IEN_Pos)       ///<  Overrun error interrupt enable bit
#define SPI_IER_RXMATCH_IEN_Pos         (4)
#define SPI_IER_RXMATCH_IEN             (0x01U << SPI_IER_RXMATCH_IEN_Pos)      ///<  Receive data complete interrupt enable bit
#define SPI_IER_RXFULL_IEN_Pos          (5)
#define SPI_IER_RXFULL_IEN              (0x01U << SPI_IER_RXFULL_IEN_Pos)       ///<  Receive FIFO full interrupt enable bit
#define SPI_IER_TXEPT_IEN_Pos           (6)
#define SPI_IER_TXEPT_IEN               (0x01U << SPI_IER_TXEPT_IEN_Pos)        ///<  Transmit empty interrupt enable bit
#define SPI_IER_FRE_IEN_Pos            (7)
#define SPI_IER_FRE_IEN                (0x01U << SPI_IER_FRE_IEN_Pos)           ///< I2S frame transmission interrupt enable bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_ICR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_ICR_TX_ICLR_Pos             (0)
#define SPI_ICR_TX_ICLR                 (0x01U << SPI_ICR_TX_ICLR_Pos)          ///<  Transmitter FIFO empty interrupt clear bit
#define SPI_ICR_RX_ICLR_Pos             (1)
#define SPI_ICR_RX_ICLR                 (0x01U << SPI_ICR_RX_ICLR_Pos)          ///<  Receive interrupt clear bit
#define SPI_ICR_UNDERRUN_ICLR_Pos       (2)
#define SPI_ICR_UNDERRUN_ICLR           (0x01U << SPI_ICR_UNDERRUN_ICLR_Pos)    ///<  Transmitter underrun interrupt clear bit
#define SPI_ICR_RXOERR_ICLR_Pos         (3)
#define SPI_ICR_RXOERR_ICLR             (0x01U << SPI_ICR_RXOERR_ICLR_Pos)      ///<  Overrun error interrupt clear bit
#define SPI_ICR_RXMATCH_ICLR_Pos        (4)
#define SPI_ICR_RXMATCH_ICLR            (0x01U << SPI_ICR_RXMATCH_ICLR_Pos)     ///<  Receive completed interrupt clear bit
#define SPI_ICR_RXFULL_ICLR_Pos         (5)
#define SPI_ICR_RXFULL_ICLR             (0x01U << SPI_ICR_RXFULL_ICLR_Pos)      ///<  Receiver buffer full interrupt clear bit
#define SPI_ICR_TXEPT_ICLR_Pos          (6)
#define SPI_ICR_TXEPT_ICLR              (0x01U << SPI_ICR_TXEPT_ICLR_Pos)       ///<  Transmitter empty interrupt clear bit
#define SPI_ICR_FRE_ICLR_Pos            (7)
#define SPI_ICR_FRE_ICLR                (0x01U << SPI_ICR_FRE_ICLR_Pos)         ///< I2S frame transmission interrupt clear bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_GCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_GCR_SPIEN_Pos               (0)
#define SPI_GCR_SPIEN                   (0x01U << SPI_GCR_SPIEN_Pos)            ///<  SPI select bit
#define SPI_GCR_IEN_Pos                 (1)
#define SPI_GCR_IEN                     (0x01U << SPI_GCR_IEN_Pos)              ///<  SPI interrupt enable bit
#define SPI_GCR_MODE_Pos                (2)
#define SPI_GCR_MODE                    (0x01U << SPI_GCR_MODE_Pos)             ///<  Master mode bit
#define SPI_GCR_TXEN_Pos                (3)
#define SPI_GCR_TXEN                    (0x01U << SPI_GCR_TXEN_Pos)             ///<  Transmit enable bit
#define SPI_GCR_RXEN_Pos                (4)
#define SPI_GCR_RXEN                    (0x01U << SPI_GCR_RXEN_Pos)             ///<  Receive enable bit

#define SPI_GCR_RXTLF_Pos               (5)
#define SPI_GCR_RXTLF                   (0x03U << SPI_GCR_RXTLF_Pos)            ///<  RX FIFO trigger level bit
#define SPI_GCR_RXTLF_One               (0x00U << SPI_GCR_RXTLF_Pos)            ///<
#define SPI_GCR_RXTLF_Half              (0x01U << SPI_GCR_RXTLF_Pos)            ///<

#define SPI_GCR_TXTLF_Pos               (7)
#define SPI_GCR_TXTLF                   (0x03U << SPI_GCR_TXTLF_Pos)            ///<  TX FIFO trigger level bit
#define SPI_GCR_TXTLF_One               (0x00U << SPI_GCR_TXTLF_Pos)            ///<
#define SPI_GCR_TXTLF_Half              (0x01U << SPI_GCR_TXTLF_Pos)            ///<
#define SPI_GCR_DMAEN_Pos               (9)
#define SPI_GCR_DMAEN                   (0x01U << SPI_GCR_DMAEN_Pos)            ///<  DMA access mode enable
#define SPI_GCR_NSS_Pos                 (10)
#define SPI_GCR_NSS                     (0x01U << SPI_GCR_NSS_Pos)              ///<  NSS select signal that from software or hardware
#define SPI_GCR_DWSEL_Pos               (11)
#define SPI_GCR_DWSEL                   (0x01U << SPI_GCR_DWSEL_Pos)            ///<  Valid byte or double-word data select signal

#define SPI_GCR_NSSTOG_Pos              (12)
#define SPI_GCR_NSSTOG                  (0x01U << SPI_GCR_NSSTOG_Pos)           ///<  Slave select toggle
#define SPI_GCR_PAD_SEL_Pos             (13)
#define SPI_GCR_PAD_SEL                 (0x1FU << SPI_GCR_PAD_SEL_Pos)          ///< Bus mapping transformation
////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_CCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_CCR_CPHA_Pos                (0)
#define SPI_CCR_CPHA                    (0x01U << SPI_CCR_CPHA_Pos)             ///<  Clock phase select bit
#define SPI_CCR_CPOL_Pos                (1)
#define SPI_CCR_CPOL                    (0x01U << SPI_CCR_CPOL_Pos)             ///<  Clock polarity select bit
#define SPI_CCR_LSBFE_Pos               (2)
#define SPI_CCR_LSBFE                   (0x01U << SPI_CCR_LSBFE_Pos)            ///<  LSI first enable bit
#define SPI_CCR_SPILEN_Pos              (3)
#define SPI_CCR_SPILEN                  (0x01U << SPI_CCR_SPILEN_Pos)           ///<  SPI character length bit
#define SPI_CCR_RXEDGE_Pos              (4)
#define SPI_CCR_RXEDGE                  (0x01U << SPI_CCR_RXEDGE_Pos)           ///<  Receive data edge select
#define SPI_CCR_TXEDGE_Pos              (5)
#define SPI_CCR_TXEDGE                  (0x01U << SPI_CCR_TXEDGE_Pos)           ///<  Transmit data edge select

#define SPI_CCR_CPHASEL_Pos             (6)
#define SPI_CCR_CPHASEL                 (0x01U << SPI_CCR_CPHASEL)              ///<  CPHA polarity select

#define SPI_CCR_HISPD_Pos               (7)
#define SPI_CCR_HISPD                   (0x01U << SPI_CCR_HISPD)                ///<  High speed slave mode

////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_BRR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_BRR_DIVF_Pos                (0)
#define SPI_BRR_DIVF                    (0xFFFFU << SPI_BRR_DIVF_Pos)       ///<  SPI baud rate control register for baud rate

////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_RDNR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_RDNR_RDN_Pos                (0)
#define SPI_RDNR_RDN                    (0xFFFFU << SPI_RDNR_RDN_Pos)       ///<  The register is used to hold a count of to be received bytes in next receive process

////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_NSSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_NSSR_NSS_Pos                (0)
#define SPI_NSSR_NSS                    (0xFFU << SPI_NSSR_NSS_Pos)             ///<  Chip select output signal in Master mode

////////////////////////////////////////////////////////////////////////////////
/// @brief SPI_ECR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SPI_ECR_EXTLEN_Pos              (0)
#define SPI_ECR_EXTLEN                  (0x1FU << SPI_ECR_EXTLEN_Pos)           ///<  control SPI data length

////////////////////////////////////////////////////////////////////////////////
/// @brief I2S_CFGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////

#define I2SCFGR_CLEAR_Mask              ((u32)0xFE00F388)
#define I2S_CFGR_CHLEN_Pos              (0)
#define I2S_CFGR_CHLEN                  (0x01U << I2S_CFGR_CHLEN_Pos)             ///<  Vocal tract length
#define I2S_CFGR_DATLEN_Pos             (1)
#define I2S_CFGR_DATLEN_16              (0x00U << I2S_CFGR_DATLEN_Pos)            ///<  Audio data width 16 
#define I2S_CFGR_DATLEN_24              (0x01U << I2S_CFGR_DATLEN_Pos)            ///<  Audio data width 24 
#define I2S_CFGR_DATLEN_32              (0x02U << I2S_CFGR_DATLEN_Pos)            ///<  Audio data width 32 

#define I2S_CFGR_I2SSTD_Pos             (4)
#define I2S_CFGR_I2SSTD_PCM             (0x00U << I2S_CFGR_I2SSTD_Pos)            ///<  I2S selection PCM standard
#define I2S_CFGR_I2SSTD_MSB_R           (0x01U << I2S_CFGR_I2SSTD_Pos)            ///<  I2S selection Right alignment (MSB) standard
#define I2S_CFGR_I2SSTD_MSB_L           (0x02U << I2S_CFGR_I2SSTD_Pos)            ///<  I2S selection Left aligned (MSB) standard
#define I2S_CFGR_I2SSTD_Philips         (0x03U << I2S_CFGR_I2SSTD_Pos)            ///<  I2S selection Philips standard

#define I2S_CFGR_PCMSYNC_Pos            (6)
#define I2S_CFGR_PCMSYNC                (0x01U << I2S_CFGR_PCMSYNC_Pos)           ///<  PCM frame synchronization mode
#define I2S_CFGR_SPI_I2S_Pos            (10)
#define I2S_CFGR_SPI_I2S                (0x01U << I2S_CFGR_SPI_I2S_Pos)           ///<  SPI/I2S module function selection
#define I2S_CFGR_MCKOE_Pos              (11)
#define I2S_CFGR_MCKOE                  (0x01U << I2S_CFGR_MCKOE_Pos)             ///<  I2S master clock output enable
#define I2S_CFGR_I2SDIV_Pos             (16)
#define I2S_CFGR_I2SDIV                 (0x1FFU << I2S_CFGR_I2SDIV_Pos)           ///<  The frequency division



/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
