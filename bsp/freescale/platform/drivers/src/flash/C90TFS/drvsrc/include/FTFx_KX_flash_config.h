/************************************************************************
 (c) Copyright 2012-2015 Freescale Semiconductor, Inc.
 ALL RIGHTS RESERVED.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*************************************************************************


*****************************************************************************
*                                                                           *
*        Standard Software Flash Driver For FTFx                            *
*                                                                           *
* FILE NAME     :  SSD_FTFx.h                                               *
* DATE          :  Sep 25, 2014                                           *
*                                                                           *
* AUTHOR        :  FPT Team                                                 *
* E-mail        :  r56611@freescale.com                                     *
*                                                                           *
*****************************************************************************/

/************************** CHANGES *************************************
1.1.GA      09.25.2014      FPT Team      First version of SDK C90TFS flash driver
                                          inherited from BM C90TFS flash driver v1.02
                                          (08.04.2014, FPT Team)
1.3.GA     06.23.2015       ROM Team      Support FAC presence detection

*************************************************************************/

#ifndef _FTFx_KX_flash_config_H_
#define _FTFx_KX_flash_config_H_

#include "SSD_FTFx_Common.h"
#include "fsl_device_registers.h"

/*!
 * @addtogroup c90tfs_flash_driver
 * @{
 */

/*!
 * @name C90TFS Flash configuration
 * @{
 */

/* Flash module */
#if (FSL_FEATURE_FLASH_IS_FTFA == 1)
    /*! @brief C90TFS sub-flash module is FTFA_M */
    #define FTFA_M
#endif
#if (FSL_FEATURE_FLASH_IS_FTFE == 1)
    /*! @brief C90TFS sub-flash module is FTFE_M */
    #define FTFE_M
#endif

#if (FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP == 1)
  /*! Include Swap control API if the feature is available in the platform */
    #define SWAP_M
#endif


#if (FSL_FEATURE_FLASH_HAS_ERASE_FLASH_BLOCK_CMD == 1)
  /*! @brief Include Read 1s block and erase block API if the feature is available in the platform */
    #define BLOCK_COMMANDS
#endif
/*@}*/
/*!
 * @name Address convert macros
 * @{
 */
/*! @brief Convert from byte address to word(2 bytes) address
 *
 * Two address types are only different in DSC devices. In Kinstis devices, they are the same
 *
*/
#define BYTE2WORD(x) (x)
/*! @brief Convert from word(2 bytes) address to byte address
  *
  * Two address types are only different in DSC devices. In Kinstis devices, they are the same
  *
 */
#define WORD2BYTE(x) (x)
/*@}*/

/*!
 * @name C90TFS Flash configuration
 * @{
 */
/*! @brief Endianness */
#define ENDIANNESS              LITTLE_ENDIAN

/*! @brief CPU core */
#define CPU_CORE                ARM_CORTEX_M

/*! @brief P-Flash sector size */
#define FTFx_PSECTOR_SIZE       FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE
/*! @brief D-Flash sector size */
#define FTFx_DSECTOR_SIZE       FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_SECTOR_SIZE
/*! @brief FlexNVM block size */
#define DEBLOCK_SIZE            (FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_SIZE * FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_COUNT)

/* EEE Data Set Size Field Description */
/*! @brief Emulated EEPROM size code 0000 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_0000            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0000
/*! @brief Emulated EEPROM size code 0001 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_0001            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0001
/*! @brief Emulated EEPROM size code 0010 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_0010            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0010
/*! @brief Emulated EEPROM size code 0011 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_0011            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0011
/*! @brief Emulated EEPROM size code 0100 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_0100            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0100
/*! @brief Emulated EEPROM size code 0101 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_0101            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0101
/*! @brief Emulated EEPROM size code 0110 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_0110            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0110
/*! @brief Emulated EEPROM size code 0111 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_0111            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0111
/*! @brief Emulated EEPROM size code 1000 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_1000            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1000
/*! @brief Emulated EEPROM size code 1001 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_1001            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1001
/*! @brief Emulated EEPROM size code 1010 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_1010            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1010
/*! @brief Emulated EEPROM size code 1011 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_1011            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1011
/*! @brief Emulated EEPROM size code 1100 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_1100            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1100
/*! @brief Emulated EEPROM size code 1101 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_1101            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1101
/*! @brief Emulated EEPROM size code 1110 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_1110            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1110
/*! @brief Emulated EEPROM size code 1111 mapping to emulated EEPROM size in bytes (0xFFFF = reserved) */
#define EEESIZE_1111            FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1111

/* D/E-Flash Partition Code Field Description */
/*! @brief FlexNVM partition code 0000 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_0000             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0000
/*! @brief FlexNVM partition code 0001 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_0001             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0001
/*! @brief FlexNVM partition code 0010 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_0010             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0010
/*! @brief FlexNVM partition code 0011 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_0011             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0011
/*! @brief FlexNVM partition code 0100 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_0100             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0100
/*! @brief FlexNVM partition code 0101 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_0101             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0101
/*! @brief FlexNVM partition code 0110 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_0110             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0110
/*! @brief FlexNVM partition code 0111 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_0111             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0111
/*! @brief FlexNVM partition code 1000 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_1000             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1000
/*! @brief FlexNVM partition code 1001 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_1001             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1001
/*! @brief FlexNVM partition code 1010 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_1010             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1010
/*! @brief FlexNVM partition code 1011 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_1011             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1011
/*! @brief FlexNVM partition code 1100 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_1100             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1100
/*! @brief FlexNVM partition code 1101 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_1101             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1101
/*! @brief FlexNVM partition code 1110 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_1110             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1110
/*! @brief FlexNVM partition code 1111 mapping to data flash size in bytes (0xFFFFFFFF = reserved) */
#define DEPART_1111             FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1111


/*! @brief Data flash IFR map */
#if (FSL_FEATURE_FLASH_IS_FTFE == 1)
    #define DFLASH_IFR_READRESOURCE_ADDRESS                0x8003F8U
#else /* FSL_FEATURE_FLASH_IS_FTFL == 1 or FSL_FEATURE_FLASH_IS_FTFA = =1 */
    #define DFLASH_IFR_READRESOURCE_ADDRESS                0x8000FCU
#endif

/* Size for checking alignment of a section */
/*! @brief P-Flash Program check command address alignment */
#define PGMCHK_ALIGN_SIZE       FSL_FEATURE_FLASH_PFLASH_CHECK_CMD_ADDRESS_ALIGMENT
/*! @brief P-Flash write unit size */
#define PGM_SIZE_BYTE           FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE
/*! @brief Resume wait count used in FlashResume function */
#define RESUME_WAIT_CNT         0x20U


/*! @brief PFlash FAC presence */
#define PFLASH_FAC_PRESENCE        FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL

/*@}*/

/*! @}*/

#endif  /* _FTFx_KX_flash_config_H_ */
