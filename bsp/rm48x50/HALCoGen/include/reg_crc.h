/** @file reg_crc.h
*   @brief CRC Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the CRC driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_CRC_H__
#define __REG_CRC_H__

#include "sys_common.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Crc Register Frame Definition */
/** @struct crcBase
*   @brief CRC Register Frame Definition
*
*   This type is used to access the CRC Registers.
*/
/** @typedef crcBASE_t
*   @brief CRC Register Frame Type Definition
*
*   This type is used to access the CRC Registers.
*/
typedef volatile struct crcBase
{
    uint32      CTRL0;                /**< 0x0000: Global Control Register 0 >**/
    uint32        rsvd1;              /**< 0x0004: reserved >**/
    uint32      CTRL1;                /**< 0x0008: Global Control Register 1 >**/
    uint32        rsvd2;              /**< 0x000C: reserved >**/    
    uint32      CTRL2;                /**< 0x0010: Global Control Register 2 >**/
    uint32        rsvd3;              /**< 0x0014: reserved >**/        
    uint32      INTS;                 /**< 0x0018: Interrupt Enable Set Register >**/
    uint32        rsvd4;              /**< 0x001C: reserved >**/        
    uint32      INTR;                 /**< 0x0020: Interrupt Enable Reset Register >**/
    uint32        rsvd5;              /**< 0x0024: reserved >**/    
    uint32      STATUS;               /**< 0x0028: Interrupt Status Register >**/
    uint32        rsvd6;              /**< 0x002C: reserved >**/    
    uint32      INT_OFFSET_REG;       /**< 0x0030: Interrupt Offset >**/
    uint32        rsvd7;              /**< 0x0034: reserved >**/    
    uint32      BUSY;                 /**< 0x0038: CRC Busy Register >**/
    uint32        rsvd8;              /**< 0x003C: reserved >**/    
    uint32      PCOUNT_REG1;          /**< 0x0040: Pattern Counter Preload Register1 >**/
    uint32      SCOUNT_REG1;          /**< 0x0044: Sector Counter Preload Register1 >**/
    uint32      CURSEC_REG1;          /**< 0x0048: Current Sector Register 1 >**/
    uint32      WDTOPLD1;             /**< 0x004C: Channel 1 Watchdog Timeout Preload Register A >**/
    uint32      BCTOPLD1;             /**< 0x0050: Channel 1 Block Complete Timeout Preload Register B >**/
    uint32        rsvd9[3];           /**< 0x0054: reserved >**/
    uint32      PSA_SIGREGL1;         /**< 0x0060: Channel 1 PSA signature low register >**/
    uint32      PSA_SIGREGH1;         /**< 0x0064: Channel 1 PSA signature high register >**/
    uint32      REGL1;                /**< 0x0068: Channel 1 CRC value low register >**/
    uint32      REGH1;                /**< 0x006C: Channel 1 CRC value high register >**/
    uint32      PSA_SECSIGREGL1;      /**< 0x0070: Channel 1 PSA sector signature low register >**/
    uint32      PSA_SECSIGREGH1;      /**< 0x0074: Channel 1 PSA sector signature high register >**/
    uint32      RAW_DATAREGL1;        /**< 0x0078: Channel 1 Raw Data Low Register >**/
    uint32      RAW_DATAREGH1;        /**< 0x007C: Channel 1 Raw Data High Register >**/
    uint32      PCOUNT_REG2;          /**< 0x0080: CRC Pattern Counter Preload Register2 >**/
    uint32      SCOUNT_REG2;          /**< 0x0084: Sector Counter Preload Register2 >**/
    uint32      CURSEC_REG2;          /**< 0x0088: Current Sector Register 2>**/
    uint32      WDTOPLD2;             /**< 0x008C: Channel 2 Watchdog Timeout Preload Register A >**/
    uint32      BCTOPLD2;             /**< 0x0090: Channel 2 Block Complete Timeout Preload Register B >**/
    uint32        rsvd10[3];           /**< 0x0094: reserved >**/
    uint32      PSA_SIGREGL2;         /**< 0x00A0: Channel 2 PSA signature low register >**/
    uint32      PSA_SIGREGH2;         /**< 0x00A8: Channel 2 PSA signature high register >**/
    uint32      REGL2;                /**< 0x00AC: Channel 2 CRC value low register >**/
    uint32      REGH2;                /**< 0x00AC: Channel 2 CRC value high register >**/
    uint32      PSA_SECSIGREGL2;      /**< 0x00B0: Channel 2 PSA sector signature low register >**/
    uint32      PSA_SECSIGREGH2;      /**< 0x00B4: Channel 2 PSA sector signature high register >**/
    uint32      RAW_DATAREGL2;        /**< 0x00B8: Channel 2 Raw Data Low Register >**/
    uint32      RAW_DATAREGH2;        /**< 0x00BC: Channel 2 Raw Data High Register >**/
}crcBASE_t;
 
/** @def crcREG
*   @brief CRC Register Frame Pointer
*
*   This pointer is used by the CRC driver to access the CRC registers.
*/
#define crcREG ((crcBASE_t *)0xFE000000U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
