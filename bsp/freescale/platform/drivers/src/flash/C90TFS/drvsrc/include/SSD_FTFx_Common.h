/****************************************************************************
 (c) Copyright 2010-2015 Freescale Semiconductor, Inc.
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
*****************************************************************************

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
1.3.GA      06.23.2015      ROM Team      Added FAC Error Status 
*************************************************************************/
#ifndef _SSD_FTFx_COMMON_H_
#define _SSD_FTFx_COMMON_H_

#include "SSD_Types.h"

/* Endianness */
#define BIG_ENDIAN                        0   /* Big Endian */
#define LITTLE_ENDIAN                     1   /* Little Endian */

/* cpu cores */
#define COLDFIRE                          0   /* ColdFire core */
#define ARM_CORTEX_M                      1   /* ARM Cortex M4 core M0 core*/
#define DSC_56800EX                       2   /* 32 bit DSC core */

/* Word size */
#define FTFx_WORD_SIZE                    0x0002U     /* 2 bytes */

/* Longword size */
#define FTFx_LONGWORD_SIZE                0x0004U     /* 4 bytes */

/* Phrase size */
#define FTFx_PHRASE_SIZE                  0x0008U     /* 8 bytes */

/* Double-phrase size */
#define FTFx_DPHRASE_SIZE                 0x0010U     /* 16 bytes */

/* Flash security status */
#define FLASH_SECURITY_STATE_KEYEN         0x80U
#define FLASH_SECURITY_STATE_UNSECURED     0x02U

/*!
 * @addtogroup c90tfs_flash_driver
 * @{
 */

/*------------ Return Code Definition for FTFx SSD ---------------------*/
/*!
 * @name Return Code Definition for FTFx SSD
 * @{
 */
/*! @brief  Function executes successfully */
#define FTFx_OK                            0x0000U
/*!@brief  MGSTAT0 bit is set in the FSTAT register
*
* Possible causes:
*
* MGSTAT0 bit in FSTAT register is set. Refer to corresponding command description
* of each API on reference manual to get detail reasons
*
* Solution:
*
* Hardware error
*
*/
#define FTFx_ERR_MGSTAT0                   0x0001U
/*! @brief  Protection violation is set in FSTAT register
*
* Possible causes:
*
* FPVIOL bit in FSTAT register is set. Refer to corresponding command description
* of each API  on reference manual to get detail reasons
*
* Solution:
*
* The  flash location targeted to program/erase operation must be unprotected. Swap
* indicator must not be programmed/erased except in Update or Update-Erase state.
*
*/
#define FTFx_ERR_PVIOL                     0x0010U
/*! @brief  Access error is set in the FSTAT register
*
* Possible causes:
*
* ACCERR bit in FSTAT register is set. Refer to corresponding command description
* of each API  on reference manual to get detail reasons.
*
* Solution:
*
* Provide valid input parameters for each API according to specific flash module.
*
*/
#define FTFx_ERR_ACCERR                    0x0020U
/*! @brief  Cannot change protection status
*
* Possible causes:
*
* Violates protection transition.
*
* Solution:
*
* In NVM normal mode, protection size cannot be decreased. Therefore, the only increasing
* protection size is permitted if the device is operating in this mode.
*
*/
#define FTFx_ERR_CHANGEPROT                0x0100U
/*! @brief  FlexRAM is not set for EEPROM use
*
* Possible causes:
*
* User accesses to EEPROM operation but there is no EEPROM backup enabled.
*
* Solution:
*
* Need to enable EEPROM by partitioning FlexNVM to have EEPROM backup and/or
* enable it by SetEEEnable API.
*
*/
#define FTFx_ERR_NOEEE                     0x0200U
/*! @brief  FlexNVM is set for full EEPROM backup
*
* Possible causes:
*
* User accesses to D-Flash operation but there is no D-Flash on FlexNVM.
*
* Solution:
*
* Need to partition FlexNVM to have D-Flash.
*
*/
#define FTFx_ERR_EFLASHONLY                0x0400U
/*! @brief  Programming acceleration RAM is not available
*
* Possible causes:
*
* User invokes flash program section command but FlexRam is being set for EEPROM emulation.
*
* Solution:
*
* Need to set FlexRam as traditional  Ram by SetEEEnable API.
*
*/
#define FTFx_ERR_RAMRDY                    0x0800U
/*! @brief  Address is out of the valid range
*
* Possible causes:
*
* The size or destination provided by user makes start address or end address
* out of valid range.
*
* Solution:
*
* Make sure the destination and (destination + size) within valid address range.
*
*/
#define FTFx_ERR_RANGE                     0x1000U
/*! @brief  Misaligned size
*
* Possible causes:
*
* The size provided by user is misaligned.
*
* Solution:
*
* Size must be an aligned value according to specific constrain of each API.
*
*/
#define FTFx_ERR_SIZE                      0x2000U

/*! @breife No FAC feature
* 
* Possible causes:
*
* User invokes get FAC XA or SA protection command but there is not FAC on FTFA/FTFE/FTFL modules.
* 
* Solution:
*
* Do not invoke FAC related APIs when it is unavailable.
* 
*/
#define FTFx_ERR_NOFAC                     0x4000U
/*@}*/

/*!
 * @name Flash security status
 * @{
 */
/*! @brief  Flash currently not in secure state */
#define FLASH_NOT_SECURE                   0x01U
/*! @brief  Flash is secured and backdoor key access enabled */
#define FLASH_SECURE_BACKDOOR_ENABLED      0x02U
/*! @brief  Flash is secured and backdoor key access disabled */
#define FLASH_SECURE_BACKDOOR_DISABLED     0x04U
/*@}*/

/*! @}*/
/*-------------- Read/Write/Set/Clear Operation Macros -----------------*/
#define REG_BIT_SET(address, mask)      (*(vuint8_t*)(address) |= (mask))
#define REG_BIT_CLEAR(address, mask)    (*(vuint8_t*)(address) &= ~(mask))
#define REG_BIT_GET(address, mask)      (*(vuint8_t *)(address) & (uint8_t)(mask))
#define REG_WRITE(address, value)       (*(vuint8_t*)(address) = (value))
#define REG_READ(address)               ((uint8_t)(*(vuint8_t*)(address)))
#define REG_WRITE32(address, value)     (*(vuint32_t*)(address) = (value))
#define REG_READ32(address)             ((uint32_t)(*(vuint32_t*)(address)))
#define WRITE8(address, value)          (*(vuint8_t*)(address) = (value))
#define READ8(address)                  ((uint8_t)(*(vuint8_t*)(address)))
#define SET8(address, value)            (*(vuint8_t*)(address) |= (value))
#define CLEAR8(address, value)          (*(vuint8_t*)(address) &= ~(value))
#define TEST8(address, value)           (*(vuint8_t*)(address) & (value))

#define WRITE16(address, value)         (*(vuint16_t*)(address) = (value))
#define READ16(address)                 ((uint16_t)(*(vuint16_t*)(address)))
#define SET16(address, value)           (*(vuint16_t*)(address) |= (value))
#define CLEAR16(address, value)         (*(vuint16_t*)(address) &= ~(value))
#define TEST16(address, value)          (*(vuint16_t*)(address) & (value))

#define WRITE32(address, value)         (*(vuint32_t*)(address) = (value))
#define READ32(address)                 ((uint32_t)(*(vuint32_t*)(address)))
#define SET32(address, value)           (*(vuint32_t*)(address) |= (value))
#define CLEAR32(address, value)         (*(vuint32_t*)(address) &= ~(value))
#define TEST32(address, value)          (*(vuint32_t*)(address) & (value))
#define GET_BIT_0_7(value)              ((uint8_t)((value) & 0xFFU))
#define GET_BIT_8_15(value)             ((uint8_t)(((value)>>8) & 0xFFU))
#define GET_BIT_16_23(value)            ((uint8_t)(((value)>>16) & 0xFFU))
#define GET_BIT_24_31(value)            ((uint8_t)((value)>>24))

/*--------------------- CallBack function period -----------------------*/
#ifndef FLASH_CALLBACK_CS
#define FLASH_CALLBACK_CS               0x0AU          /* Check Sum */
#endif

/*!
 * @addtogroup c90tfs_flash_driver
 * @{
 */
/*--------------------Null Callback function definition ----------------*/
/*!
 * @name Null Callback function definition
 * @{
 */
/*! @brief  Null callback */
#define NULL_CALLBACK                   ((PCALLBACK)0xFFFFFFFF)
/*! @brief  Null swap callback */
#define NULL_SWAP_CALLBACK              ((PFLASH_SWAP_CALLBACK)0xFFFFFFFF)
/*@}*/

/*! @}*/

#endif /* _SSD_FTFx_COMMON_H_ */

