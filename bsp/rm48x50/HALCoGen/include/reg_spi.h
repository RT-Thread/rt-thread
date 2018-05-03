/** @file reg_spi.h
*   @brief SPI Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the SPI driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_SPI_H__
#define __REG_SPI_H__

#include "sys_common.h"
#include "gio.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Spi Register Frame Definition */
/** @struct spiBase
*   @brief SPI Register Definition
*
*   This structure is used to access the SPI module registers.
*/
/** @typedef spiBASE_t
*   @brief SPI Register Frame Type Definition
*
*   This type is used to access the SPI Registers.
*/
typedef volatile struct spiBase
{
    uint32  GCR0;                 /**< 0x0000: Global Control 0 */
    uint32  GCR1;                  /**< 0x0004: Global Control 1 */	
    uint32  INT0;                  /**< 0x0008: Interrupt Register */	
    uint32  LVL;                  /**< 0x000C: Interrupt Level */
    uint32  FLG;                  /**< 0x0010: Interrupt flags */		
    uint32  PCFUN;                /**< 0x0014: Function Pin Enable */
    uint32  PCDIR;                /**< 0x0018: Pin Direction */
    uint32  PCDIN;                /**< 0x001C: Pin Input Latch */
    uint32  PCDOUT;               /**< 0x0020: Pin Output Latch */
    uint32  PCSET;                /**< 0x0024: Output Pin Set */
    uint32  PCCLR;                /**< 0x0028: Output Pin Clr */
    uint32  PCPDR;                /**< 0x002C: Open Drain Output Enable */
    uint32  PCDIS;                /**< 0x0030: Pullup/Pulldown Disable */
    uint32  PCPSL;                /**< 0x0034: Pullup/Pulldown Selection */
    uint32  DAT0;                 /**< 0x0038: Transmit Data */
    uint32  DAT1;                 /**< 0x003C: Transmit Data with Format and Chip Select */
    uint32  BUF;                  /**< 0x0040: Receive Buffer */
    uint32  EMU;                  /**< 0x0044: Emulation Receive Buffer */
    uint32  DELAY;                /**< 0x0048: Delays */
    uint32  CSDEF;                /**< 0x004C: Default Chip Select */
    uint32  FMT0;                 /**< 0x0050: Data Format 0 */
    uint32  FMT1;                 /**< 0x0054: Data Format 1 */
    uint32  FMT2;                 /**< 0x0058: Data Format 2 */
    uint32  FMT3;                 /**< 0x005C: Data Format 3 */
    uint32  INTVECT0;             /**< 0x0060: Interrupt Vector 0 */
    uint32  INTVECT1;             /**< 0x0064: Interrupt Vector 1 */
    uint32  SRSEL;                /**< 0x0068: Slew Rate Select */
    uint32  RESERVED[50U];        /**< 0x006C to 0x0130: Reserved */	
    uint32  IOLPKTSTCR;           /**< 0x0134: IO loopback */
} spiBASE_t;

/** @def spiREG1
*   @brief SPI1 (MIBSPI - Compatibility Mode) Register Frame Pointer
*
*   This pointer is used by the SPI driver to access the spi module registers.
*/
#define spiREG1 ((spiBASE_t *)0xFFF7F400U)


/** @def spiPORT1
*   @brief SPI1 (MIBSPI - Compatibility Mode) GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of SPI1
*   (use the GIO drivers to access the port pins).
*/
#define spiPORT1 ((gioPORT_t *)0xFFF7F418U)

/** @def spiREG2
*   @brief SPI2 Register Frame Pointer
*
*   This pointer is used by the SPI driver to access the spi module registers.
*/
#define spiREG2 ((spiBASE_t *)0xFFF7F600U)


/** @def spiPORT2
*   @brief SPI2 GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of SPI2
*   (use the GIO drivers to access the port pins).
*/
#define spiPORT2 ((gioPORT_t *)0xFFF7F618U)

/** @def spiREG3
*   @brief SPI3 (MIBSPI - Compatibility Mode) Register Frame Pointer
*
*   This pointer is used by the SPI driver to access the spi module registers.
*/
#define spiREG3 ((spiBASE_t *)0xFFF7F800U)


/** @def spiPORT3
*   @brief SPI3 (MIBSPI - Compatibility Mode) GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of SPI3
*   (use the GIO drivers to access the port pins).
*/
#define spiPORT3 ((gioPORT_t *)0xFFF7F818U)

/** @def spiREG4
*   @brief SPI4 Register Frame Pointer
*
*   This pointer is used by the SPI driver to access the spi module registers.
*/
#define spiREG4 ((spiBASE_t *)0xFFF7FA00U)


/** @def spiPORT4
*   @brief SPI4 GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of SPI4
*   (use the GIO drivers to access the port pins).
*/
#define spiPORT4 ((gioPORT_t *)0xFFF7FA18U)

/** @def spiREG5
*   @brief SPI5 (MIBSPI - Compatibility Mode) Register Frame Pointer
*
*   This pointer is used by the SPI driver to access the spi module registers.
*/
#define spiREG5 ((spiBASE_t *)0xFFF7FC00U)


/** @def spiPORT5
*   @brief SPI5 (MIBSPI - Compatibility Mode) GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of SPI5
*   (use the GIO drivers to access the port pins).
*/
#define spiPORT5 ((gioPORT_t *)0xFFF7FC18U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
