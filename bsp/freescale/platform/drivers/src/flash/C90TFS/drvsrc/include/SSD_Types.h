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
1.3.GA      06.23.2015      ROM Team      Sync function pointers with new updates in SSD_FTFx.h
*************************************************************************/

#ifndef _SSD_TYPES_H_
#define _SSD_TYPES_H_


#ifndef FALSE
#define FALSE 0x0U
#endif

#ifndef TRUE
#define TRUE 0x01U
#endif

#include <stdint.h>
#include <stdbool.h>

typedef volatile signed char vint8_t;
typedef volatile unsigned char vuint8_t;
typedef volatile signed short vint16_t;
typedef volatile unsigned short vuint16_t;
typedef volatile signed long vint32_t;
typedef volatile unsigned long vuint32_t;

#if (defined __MWERKS__)
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed long int32_t;
typedef unsigned long uint32_t;
#endif
/*!
 * @addtogroup c90tfs_flash_driver
 * @{
 */


/*!
 * @name Type definition for flash driver
 * @{
 */
/*-------------------- Callback function prototype ---------------------*/
/*! @brief Call back function pointer data type */
typedef void (* PCALLBACK)(void);
/*! @brief Swap call back function pointer data type */
typedef bool (* PFLASH_SWAP_CALLBACK)(uint8_t function);


/*---------------- Flash SSD Configuration Structure -------------------*/
/*! @brief Flash SSD Configuration Structure
*
* The structure includes the static parameters for  C90TFS/FTFx  which are
* device-dependent. The user should correctly initialize the fields including
* ftfxRegBase, PFlashBlockBase, PFlashBlockSize, DFlashBlockBase, EERAMBlockBase,
* DebugEnable and CallBack before passing the structure to SSD functions.
* The rest of parameters such as DFlashBlockSize, and EEEBlockSize will be
* initialized in FlashInit() automatically. The pointer to CallBack has to be
* initialized either for null callback or a valid call back function.
*
*/
typedef struct _ssd_config
{
    uint32_t      ftfxRegBase;        /*!< The  register  base address of  C90TFS/FTFx */
    uint32_t      PFlashBase;         /*!< The base address of P-Flash memory */
    uint32_t      PFlashSize;         /*!< The size in byte of P-Flash memory */
    uint32_t      DFlashBase;         /*!< For FlexNVM device, this is the base address of D-Flash memory (FlexNVM memory); For non-FlexNVM device, this field is unused */
    uint32_t      DFlashSize;         /*!< For FlexNVM device, this is the size in byte of area
                                          which is used as  D-Flash  from FlexNVM
                                          memory;  For non-FlexNVM device, this field is unused */
    uint32_t      EERAMBase;          /*!< The base address of  FlexRAM  (for FlexNVM
                                          device) or acceleration RAM  memory  (for non-FlexNVM device) */
    uint32_t      EEESize;            /*!< For FlexNVM device, this is the size in byte of
                                          EEPROM area  which was partitioned from
                                          FlexRAM; For non-FlexNVM device, this field is unused */
    bool          DebugEnable;        /*!< Background debug mode enable */
    PCALLBACK     CallBack;           /*!< Call back function to service the time critical events */
} FLASH_SSD_CONFIG, *PFLASH_SSD_CONFIG;

/* -------------------- Function Pointer ------------------------------- */
/*! @brief FlashCommandSequence function pointer */
typedef uint32_t (*pFLASHCOMMANDSEQUENCE) (PFLASH_SSD_CONFIG pSSDConfig);

/*! @brief FlashInit function pointer */
typedef uint32_t (*pFLASHINIT) (PFLASH_SSD_CONFIG pSSDConfig);

/*! @brief PFlashGetProtection function pointer */
typedef uint32_t (*pPFLASHGETPROTECTION) (PFLASH_SSD_CONFIG pSSDConfig, \
                                        uint32_t*  protectStatus);

/*! @brief PFlashSetProtection function pointer */
typedef uint32_t (*pPFLASHSETPROTECTION) (PFLASH_SSD_CONFIG  pSSDConfig, \
                                        uint32_t  protectStatus);

/*! @brief PFlashFacGetXAProtection function pointer */
typedef uint32_t (*pPFLASHFACGETXAPROTECTION)(PFLASH_SSD_CONFIG pSSDConfig, \
                                         uint8_t * protectStatus,\
                                         uint8_t * numberOfSegments,\
                                         uint32_t * segmentSize);

/*! @brief PFlashFacGetSAProtection function pointer */
typedef uint32_t (*pPFLASHFACGETSAPROTECTION)(PFLASH_SSD_CONFIG pSSDConfig, \
                                         uint8_t * protectStatus,\
                                         uint8_t * numberOfSegments,\
                                         uint32_t * segmentSize);

/*! @brief FlashGetSecurityState function pointer */
typedef uint32_t (*pFLASHGETSECURITYSTATE) (PFLASH_SSD_CONFIG pSSDConfig, \
                                          uint8_t* securityState);

/*! @brief FlashSecurityByPass function pointer */
typedef uint32_t (*pFLASHSECURITYBYPASS) (PFLASH_SSD_CONFIG pSSDConfig, \
                                        uint8_t* keyBuffer, \
                                        pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief FlashEraseAllBlock function pointer */
typedef uint32_t (*pFLASHERASEALLBLOCK) (PFLASH_SSD_CONFIG pSSDConfig, \
                                       pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief FlashEraseAllBlockUnsecure function pointer */
typedef uint32_t (*pFLASHERASEALLBLOCKUNSECURE) (PFLASH_SSD_CONFIG pSSDConfig, \
                                       pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief FlashEraseBlock function pointer */
typedef uint32_t (*pFLASHERASEBLOCK) (PFLASH_SSD_CONFIG pSSDConfig, \
                                    uint32_t dest, \
                                    pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief FlashEraseSector function pointer */
typedef uint32_t (*pFLASHERASESECTOR) (PFLASH_SSD_CONFIG pSSDConfig, \
                                     uint32_t dest, \
                                     uint32_t size, \
                                     pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*! @brief FlashEraseSuspend function pointer */
typedef uint32_t (*pFLASHERASESUSPEND) (PFLASH_SSD_CONFIG pSSDConfig);

/*! @brief FlashEraseResume function pointer */
typedef uint32_t (*pFLASHERASERESUME) (PFLASH_SSD_CONFIG pSSDConfig);

/*! @brief FlashProgramSection function pointer */
typedef uint32_t (*pFLASHPROGRAMSECTION) (PFLASH_SSD_CONFIG pSSDConfig, \
                                        uint32_t dest, \
                                        uint16_t number, \
                                        pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief FlashChecksum function pointer */
typedef uint32_t (*pFLASHCHECKSUM) (PFLASH_SSD_CONFIG pSSDConfig, \
                                  uint32_t dest, \
                                  uint32_t size, \
                                  uint32_t* pSum);

/*! @brief FlashVerifyAllBlock function pointer */
typedef uint32_t (*pFLASHVERIFYALLBLOCK) (PFLASH_SSD_CONFIG pSSDConfig, \
                                        uint8_t marginLevel, \
                                        pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! Flash verify block */
typedef uint32_t (*pFLASHVERIFYBLOCK) (PFLASH_SSD_CONFIG pSSDConfig, \
                                     uint32_t dest, \
                                     uint8_t marginLevel, \
                                     pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief FlashVerifySection function pointer */
typedef uint32_t (*pFLASHVERIFYSECTION) (PFLASH_SSD_CONFIG pSSDConfig, \
                                       uint32_t dest, \
                                       uint16_t number, \
                                       uint8_t marginLevel, \
                                       pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief FlashReadOnce function pointer */
typedef uint32_t (*pFLASHREADONCE) (PFLASH_SSD_CONFIG pSSDConfig, \
                                  uint8_t* pDataArray, \
                                  uint32_t size, \
                                  pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief FlashProgramOnce function pointer */
typedef uint32_t (*pFLASHPROGRAMONCE) (PFLASH_SSD_CONFIG pSSDConfig, \
                                     uint8_t* pDataArray, \
                                     uint32_t size, \
                                     pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*! @brief FlashProgramCheck function pointer */
typedef uint32_t (*pFLASHPROGRAMCHECK) (PFLASH_SSD_CONFIG pSSDConfig, \
                                      uint32_t  dest, \
                                      uint32_t  size, \
                                      uint8_t*  pExpectedData, \
                                      uint32_t* pFailAddr, \
                                      uint8_t   marginLevel, \
                                      pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief FlashReadResource function pointer */
typedef uint32_t (*pFLASHREADRESOURCE) (PFLASH_SSD_CONFIG pSSDConfig, \
                                      uint32_t dest, \
                                      uint8_t* pDataArray, \
                                      uint8_t  resourceSelectCode, \
                                      pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief FlashProgram function pointer */
typedef uint32_t (*pFLASHPROGRAM) (PFLASH_SSD_CONFIG pSSDConfig, \
                                         uint32_t dest, \
                                         uint32_t size, \
                                         uint8_t* pData, \
                                         pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief PFlashSwapCtrl function pointer */
typedef uint32_t (*pPFLASHSWAPCTRL) (PFLASH_SSD_CONFIG pSSDConfig, \
                             uint32_t addr, \
                             uint8_t swapcmd, \
                             uint8_t* pCurrentSwapMode,\
                             uint8_t* pCurrentSwapBlockStatus, \
                             uint8_t* pNextSwapBlockStatus, \
                             pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief PFlashSwap function pointer */
typedef uint32_t (*pFLASHSWAP)(PFLASH_SSD_CONFIG pSSDConfig, \
                             uint32_t flashAddress, \
                             PFLASH_SWAP_CALLBACK pSwapCallback, \
                             pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*! @brief DFlashGetProtection function pointer */
typedef uint32_t (*pDFLASHGETPROTECTION) (PFLASH_SSD_CONFIG pSSDConfig, \
                                        uint8_t*  protectStatus);
/*! @brief DFlashSetProtection function pointer */
typedef uint32_t (*pDFLASHSETPROTECTION) (PFLASH_SSD_CONFIG pSSDConfig, \
                                        uint8_t  protectStatus);

/*! @brief EERAMGetProtection function pointer */
typedef uint32_t (*pEERAMGETPROTECTION) (PFLASH_SSD_CONFIG pSSDConfig, \
                                       uint8_t*  protectStatus);

/*! @brief EERAMSetProtection function pointer */
typedef uint32_t (*pEERAMSETPROTECTION) (PFLASH_SSD_CONFIG pSSDConfig, \
                                       uint8_t  protectStatus);
/*! @brief DEFlashParition function pointer */
typedef uint32_t (*pDEFLASHPARTITION) (PFLASH_SSD_CONFIG pSSDConfig, \
                                     uint8_t EEEDataSizeCode, \
                                     uint8_t DEPartitionCode, \
                                     pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*! @brief SetEEEEnable function pointer */
typedef uint32_t (*pSETEEEENABLE) (PFLASH_SSD_CONFIG pSSDConfig, \
                                 uint8_t EEEEnable,pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*! @brief EEEWrite function pointer */
typedef uint32_t (*pEEEWRITE) (PFLASH_SSD_CONFIG pSSDConfig, \
                             uint32_t dest, \
                             uint32_t size, \
                             uint8_t* pData);

/*@}*/

/*! @}*/

#endif /* _SSD_TYPES_H_ */
