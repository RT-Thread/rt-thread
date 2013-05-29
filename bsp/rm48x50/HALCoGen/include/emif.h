/** @file emif.h
*   @brief emif Driver Definition File
*   @date 29.May.2013
*   @version 03.05.02
*   
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef _EMIF_H_
#define _EMIF_H_

#include "reg_emif.h"



/** @enum emif_pins
*   @brief Alias for emif pins
*
*/
enum emif_pins
{
    emif_wait_pin0 = 0U,
    emif_wait_pin1 = 1U
};


/** @enum emif_size
*   @brief Alias for emif page size
*
*/
enum emif_size
{
    elements_256 = 0U,
    elements_512 = 1U,
    elements_1024 = 2U,
    elements_2048 = 3U
};

/** @enum emif_port
*   @brief Alias for emif port
*
*/
enum emif_port
{
    emif_8_bit_port = 0U,
    emif_16_bit_port = 1U
};


/** @enum emif_pagesize
*   @brief Alias for emif pagesize
*
*/
enum emif_pagesize
{
    emif_4_words = 0U,
    emif_8_words = 1U
};

/** @enum emif_wait_polarity
*   @brief Alias for emif wait polarity
*
*/
enum emif_wait_polarity
{
    emif_pin_low = 0U,
    emif_pin_high = 1U
};


#define PTR (uint32 *)(0x80000000U)

/** 
 *  @defgroup EMIF EMIF
 *  @brief Error Signaling Module.
 *  
 *  This EMIF memory controller is compliant with the JESD21-C SDR SDRAM memories utilizing a 16-bit
 *  data bus. The purpose of this EMIF is to provide a means for the CPU to connect to a variety of external
 *  devices including:
 *  - Single data rate (SDR) SDRAM
 *  - Asynchronous devices including NOR Flash and SRAM
 *  The most common use for the EMIF is to interface with both a flash device and an SDRAM device
 *  simultaneously. contains an example of operating the EMIF in this configuration.
 *
 *	Related Files
 *   - reg_emif.h
 *   - emif.h
 *   - emif.c
 *  @addtogroup EMIF
 *  @{
 */
/* EMIF Interface Functions */

void emif_SDRAMInit(void);
void emif_ASYNC1Init(void);
void emif_ASYNC2Init(void);
void emif_ASYNC3Init(void);

/**@}*/
#endif /*EMIF_H_*/
