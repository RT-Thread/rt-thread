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
1.1.GA      09.25.2014      FPT Team      First version of SDK C90TFS Flash driver
                                          inherited from BM C90TFS Flash driver v1.02
                                          (08.04.2014, FPT Team)
1.3.GA      06.23.2015      ROM Team      Added new features: check FAC protection status,
                                          program FAC IFR and Erase All Blocks Unsecure command.
*************************************************************************/
#ifndef _SSD_FTFx_INTERNAL_H_
#define _SSD_FTFx_INTERNAL_H_

#include "SSD_FTFx_Internal.h"

#define FTFx_SSD_FSTAT_CCIF                 0x80U
#define FTFx_SSD_FSTAT_RDCOLERR             0x40U
#define FTFx_SSD_FSTAT_ACCERR               0x20U
#define FTFx_SSD_FSTAT_FPVIOL               0x10U
#define FTFx_SSD_FSTAT_MGSTAT0              0x01U
#define FTFx_SSD_FSTAT_ERROR_BITS           (FTFx_SSD_FSTAT_ACCERR \
                                            |FTFx_SSD_FSTAT_FPVIOL \
                                            |FTFx_SSD_FSTAT_MGSTAT0)

#define FTFx_SSD_FCNFG_CCIE                 0x80U
#define FTFx_SSD_FCNFG_RDCOLLIE             0x40U
#define FTFx_SSD_FCNFG_ERSAREQ              0x20U
#define FTFx_SSD_FCNFG_ERSSUSP              0x10U
#define FTFx_SSD_FCNFG_RAMRDY               0x02U
#define FTFx_SSD_FCNFG_EEERDY               0x01U

#define FTFx_SSD_FSEC_KEYEN                 0xC0U
#define FTFx_SSD_FSEC_FSLACC                0x0CU
#define FTFx_SSD_FSEC_SEC                   0x03U

/*--------------- FTFx Flash Module Memory Offset Map -----------------*/
#if(BIG_ENDIAN == ENDIANNESS)    /* Big Endian - coldfire CPU */
    /* Flash Status Register (FSTAT)*/
    #define FTFx_SSD_FSTAT_OFFSET               0x00000003U
    /* Flash configuration register (FCNFG)*/
    #define FTFx_SSD_FCNFG_OFFSET               0x00000002U
    /* Flash security register (FSEC) */
    #define FTFx_SSD_FSEC_OFFSET                0x00000001U
    /* Flash Option Register (FOPT) */
    #define FTFx_SSD_FOPT_OFFSET                0x00000000U
    /* Flash common command object registers (FCCOB0-B) */
    #define FTFx_SSD_FCCOB0_OFFSET              0x00000004U
    #define FTFx_SSD_FCCOB1_OFFSET              0x00000005U
    #define FTFx_SSD_FCCOB2_OFFSET              0x00000006U
    #define FTFx_SSD_FCCOB3_OFFSET              0x00000007U
    #define FTFx_SSD_FCCOB4_OFFSET              0x00000008U
    #define FTFx_SSD_FCCOB5_OFFSET              0x00000009U
    #define FTFx_SSD_FCCOB6_OFFSET              0x0000000AU
    #define FTFx_SSD_FCCOB7_OFFSET              0x0000000BU
    #define FTFx_SSD_FCCOB8_OFFSET              0x0000000CU
    #define FTFx_SSD_FCCOB9_OFFSET              0x0000000DU
    #define FTFx_SSD_FCCOBA_OFFSET              0x0000000EU
    #define FTFx_SSD_FCCOBB_OFFSET              0x0000000FU
    /* P-Flash protection registers (FPROT0-3) */
    #define FTFx_SSD_FPROT0_OFFSET              0x00000010U
    #define FTFx_SSD_FPROT1_OFFSET              0x00000011U
    #define FTFx_SSD_FPROT2_OFFSET              0x00000012U
    #define FTFx_SSD_FPROT3_OFFSET              0x00000013U
    /* D-Flash protection registers (FDPROT) */
    #define FTFx_SSD_FDPROT_OFFSET              0x00000014U
    /* EERAM Protection Register (FEPROT)  */
    #define FTFx_SSD_FEPROT_OFFSET              0x00000015U

#else /* Little Endian - kinetis CPU + Nevis2 CPU */
    /* Flash Status Register (FSTAT)*/
    #define FTFx_SSD_FSTAT_OFFSET               0x00000000U
    /* Flash configuration register (FCNFG)*/
    #define FTFx_SSD_FCNFG_OFFSET               0x00000001U
    /* Flash security register (FSEC) */
    #define FTFx_SSD_FSEC_OFFSET                0x00000002U
    /* Flash Option Register (FOPT) */
    #define FTFx_SSD_FOPT_OFFSET                0x00000003U
    /* Flash common command object registers (FCCOB0-B) */
    #define FTFx_SSD_FCCOB0_OFFSET              0x00000007U
    #define FTFx_SSD_FCCOB1_OFFSET              0x00000006U
    #define FTFx_SSD_FCCOB2_OFFSET              0x00000005U
    #define FTFx_SSD_FCCOB3_OFFSET              0x00000004U
    #define FTFx_SSD_FCCOB4_OFFSET              0x0000000BU
    #define FTFx_SSD_FCCOB5_OFFSET              0x0000000AU
    #define FTFx_SSD_FCCOB6_OFFSET              0x00000009U
    #define FTFx_SSD_FCCOB7_OFFSET              0x00000008U
    #define FTFx_SSD_FCCOB8_OFFSET              0x0000000FU
    #define FTFx_SSD_FCCOB9_OFFSET              0x0000000EU
    #define FTFx_SSD_FCCOBA_OFFSET              0x0000000DU
    #define FTFx_SSD_FCCOBB_OFFSET              0x0000000CU
    /* P-Flash protection registers (FPROT0-3) */
    #define FTFx_SSD_FPROT0_OFFSET              0x00000013U
    #define FTFx_SSD_FPROT1_OFFSET              0x00000012U
    #define FTFx_SSD_FPROT2_OFFSET              0x00000011U
    #define FTFx_SSD_FPROT3_OFFSET              0x00000010U
    /* D-Flash protection registers (FDPROT) */
    #define FTFx_SSD_FDPROT_OFFSET              0x00000017U
    /* EERAM Protection Register (FEPROT)  */
    #define FTFx_SSD_FEPROT_OFFSET              0x00000016U
    /* P-Flash Flash Access Controller XAC regisers (XACCH0-3, XACCL0-3) */
    #define FTFx_SSD_XACCH0_OFFSET              0x0000001BU
    #define FTFx_SSD_XACCH1_OFFSET              0x0000001AU
    #define FTFx_SSD_XACCH2_OFFSET              0x00000019U
    #define FTFx_SSD_XACCH3_OFFSET              0x00000018U
    #define FTFx_SSD_XACCL0_OFFSET              0x0000001FU
    #define FTFx_SSD_XACCL1_OFFSET              0x0000001EU
    #define FTFx_SSD_XACCL2_OFFSET              0x0000001DU
    #define FTFx_SSD_XACCL3_OFFSET              0x0000001CU
    /* P-Flash Flash Access Controller SAC regisers (SACCH0-3, SACCL0-3) */
    #define FTFx_SSD_SACCH0_OFFSET              0x00000023U
    #define FTFx_SSD_SACCH1_OFFSET              0x00000022U
    #define FTFx_SSD_SACCH2_OFFSET              0x00000021U
    #define FTFx_SSD_SACCH3_OFFSET              0x00000020U
    #define FTFx_SSD_SACCL0_OFFSET              0x00000027U
    #define FTFx_SSD_SACCL1_OFFSET              0x00000026U
    #define FTFx_SSD_SACCL2_OFFSET              0x00000025U
    #define FTFx_SSD_SACCL3_OFFSET              0x00000024U

    /* P-Flash Access Segment Size register (FACSS) */
    #define FTFx_SSD_FACSS_OFFSET               0x00000028U
    /* P-Flash Access Segment Number register (FACSN) */
    #define FTFx_SSD_FACSN_OFFSET               0x0000002BU
#endif

/* fccob offset address to store resource code */
#if (PGM_SIZE_BYTE == FTFx_PHRASE_SIZE)
	#define RSRC_CODE_OFSSET        FTFx_SSD_FCCOB4_OFFSET
#else
	#define RSRC_CODE_OFSSET        FTFx_SSD_FCCOB8_OFFSET
#endif

/*------------- Flash hardware algorithm operation commands -------------*/
#define FTFx_VERIFY_BLOCK               0x00U
#define FTFx_VERIFY_SECTION             0x01U
#define FTFx_PROGRAM_CHECK              0x02U
#define FTFx_READ_RESOURCE              0x03U
#define FTFx_PROGRAM_LONGWORD           0x06U
#define FTFx_PROGRAM_PHRASE             0x07U
#define FTFx_ERASE_BLOCK                0x08U
#define FTFx_ERASE_SECTOR               0x09U
#define FTFx_PROGRAM_SECTION            0x0BU
#define FTFx_VERIFY_ALL_BLOCK           0x40U
#define FTFx_READ_ONCE                  0x41U
#define FTFx_PROGRAM_ONCE               0x43U
#define FTFx_ERASE_ALL_BLOCK            0x44U
#define FTFx_SECURITY_BY_PASS           0x45U
#define FTFx_PFLASH_SWAP                0x46U
#define FTFx_ERASE_ALL_BLOCK_UNSECURE   0x49U
#define FTFx_PROGRAM_PARTITION          0x80U
#define FTFx_SET_EERAM                  0x81U



/* EERAM Function Control Code */
#define EEE_ENABLE                      0x00U
#define EEE_DISABLE                     0xFFU

/*!
 * @addtogroup c90tfs_flash_driver
 * @{
 */

/*!
 * @name PFlash swap control codes
 * @{
 */
/*! @brief Initialize Swap System control code */
#define FTFx_SWAP_SET_INDICATOR_ADDR    0x01U
/*! @brief Set Swap in Update State */
#define FTFx_SWAP_SET_IN_PREPARE        0x02U
/*! @brief Set Swap in Complete State */
#define FTFx_SWAP_SET_IN_COMPLETE       0x04U
/*! @brief  Report Swap Status */
#define FTFx_SWAP_REPORT_STATUS         0x08U

/*@}*/

/*!
 * @name PFlash swap states
 * @{
 */
/*! @brief  Uninitialized swap mode */
#define FTFx_SWAP_UNINIT                0x00U
/*! @brief  Ready swap mode */
#define FTFx_SWAP_READY                 0x01U
/*! @brief  Update swap mode */
#define FTFx_SWAP_UPDATE                0x02U
/*! @brief  Update-Erased swap mode */
#define FTFx_SWAP_UPDATE_ERASED         0x03U
/*! @brief  Complete swap mode */
#define FTFx_SWAP_COMPLETE              0x04U

/*@}*/

/*------------------- Setting Flash interrupt macro --------------------*/
/*!
* @brief  Sets the Flash interrupt enable bits in the FCNFG register.
*
* @param ftfxRegBase:   Specifies register base address of the Flash module
* @param value:         The bit map value ( 0: disabled, 1 enabled) .
*                       The numbering is marked from 0 to 7 where bit 0
*                       is the least significant bit. Bit 7 is corresponding
*                       to command complete interrupt. Bit 6 is corresponding
*                       to read collision error interrupt.
*/
#define SET_FLASH_INT_BITS(ftfxRegBase, value)  REG_WRITE((ftfxRegBase) + FTFx_SSD_FCNFG_OFFSET,\
                                                ((value)&(FTFx_SSD_FCNFG_CCIE | FTFx_SSD_FCNFG_RDCOLLIE)))
/*!
* @brief  Returns the Flash interrupt enable bits in the FCNFG register.
*
* @param ftfxRegBase:   Specifies register base address of the Flash module.
*/
#define GET_FLASH_INT_BITS(ftfxRegBase)         REG_READ((ftfxRegBase) + FTFx_SSD_FCNFG_OFFSET) &\
                                                (FTFx_SSD_FCNFG_CCIE | FTFx_SSD_FCNFG_RDCOLLIE)

/*!
 * @name C90TFS Flash driver APIs
 * @{
 */

/*---------------- Function Prototypes for Flash SSD --------------------*/
/*!
 * @brief Relocates a function to RAM address.
 *
 * This function provides a facility to relocate a function in RAM.
 *
 * @param dest:    Destination address where you want to place the function.
 * @param size:    Size of the function
 * @param src:     Address of the function will be relocated
 * @return Relocated address of the function .
 */
extern uint32_t RelocateFunction(uint32_t dest, uint32_t size, uint32_t src);
/*!
 * @brief Initializes Flash.
 *
 * This API  initializes  Flash  module by clearing status error
 * bit and reporting the memory configuration via SSD configuration structure.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @return Successful completion (FTFx_OK)
 */
extern uint32_t FlashInit(PFLASH_SSD_CONFIG pSSDConfig);

/*!
 * @brief Flash command sequence.
 *
 * This API is used to perform command write sequence on  Flash.
 * It is internal function, called by driver APIs only.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @return Successful completion (FTFx_OK)
 * @return Failed in Flash command execution (FTFx_ERR_ACCERR, FTFx_ERR_PVIOL,
 * FTFx_ERR_MGSTAT0)
 */
extern uint32_t FlashCommandSequence(PFLASH_SSD_CONFIG pSSDConfig);
/*!
 * @brief P-Flash get protection.
 *
 * This  API  retrieves  the current  P-Flash  protection  status.  Considering
 * the  time  consumption  for getting protection is very  low and even can
 * be  ignored. It is not necessary to utilize the Callback function to
 * support the time-critical events.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param protectStatus: To return the current value of the P-Flash Protection.
 *                       Each bit is corresponding
 *                       to protection of 1/32 of the total P-Flash. The least
 *                       significant bit is corresponding to the lowest
 *                       address area of P-Flash. The most significant bit
 *                       is corresponding to the highest address area of P-
 *                       Flash and so on. There are two possible cases as below:
 *                       -  0: this area is protected.
 *                       -  1: this area is unprotected.
 * @return Successful completion (FTFx_OK)
 */
extern uint32_t PFlashGetProtection(PFLASH_SSD_CONFIG pSSDConfig, \
                                  uint32_t*  protectStatus);

/*!
 * @brief P-Flash set protection.
 *
 * This API sets the P-Flash protection to the intended protection status.
 * Setting P-Flash protection status is subject to a protection transition
 * restriction. If there is a setting violation, it  returns
 * an error code and the current protection status won’t be changed.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param protectStatus: The expected protect status user wants to set to
 *                       P-Flash protection register. Each bit is corresponding
 *                       to protection of 1/32 of the total P-Flash. The least
 *                       significant bit is corresponding to the lowest
 *                       address area of P-Flash. The most significant bit
 *                       is corresponding to the highest address area of P-
 *                       Flash, and so on. There are two possible cases as shown below:
 *                       -  0: this area is protected.
 *                       -  1: this area is unprotected.
 * @return Successful completion (FTFx_OK )
 * @return Error value (FTFx_ERR_CHANGEPROT)
 */
extern uint32_t PFlashSetProtection(PFLASH_SSD_CONFIG pSSDConfig, \
                                  uint32_t  protectStatus);

#if PFLASH_FAC_PRESENCE
/*!
 * @brief P-Flash Get FAC Execute Access protection.
 *
 * This API retrieves the current P-Flash FAC Exeucte Access protection status.
 * Considering the  time  consumption  for getting protection is very  low and even can
 * be  ignored. It is not necessary to utilize the Callback function to
 * support the time-critical events.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param protectStatus: To return the current value of the P-Flash  FAC Execute Access Protection.
 *                       Each bit is corresponding
 *                       to protection of 1/64 of the total P-Flash. The least
 *                       significant bit of protectStatus[0] is corresponding to the lowest
 *                       address area of P-Flash. The most significant bit of protectStatus[7]
 *                       is corresponding to the highest address area of P-
 *                       Flash and so on. There are two possible cases as below:
 *                       -  0: this area is protected.
 *                       -  1: this area is unprotected.
 * @param numberOfSegments: To return the number of program flash segments that are available for
 *                          XACC and SACC permissions.
 * @param segmentSize: To return segment size of program flash based on the available program size
 *                     divided by numberOfSegments.
 * @return Successful completion (FTFx_OK)
 */
extern uint32_t PFlashFacGetXAProtection(PFLASH_SSD_CONFIG pSSDConfig, \
                                  uint8_t *protectStatus,\
                                  uint8_t *numberOfSegments,\
                                  uint32_t *segmentSize);

/*!
 * @brief P-Flash Get FAC Supervisor Access protection.
 *
 * This API retrieves the current P-Flash FAC Supervisor Access protection status.
 * Considering the  time  consumption  for getting protection is very  low and even can
 * be  ignored. It is not necessary to utilize the Callback function to
 * support the time-critical events.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param protectStatus: To return the current value of the P-Flash  FAC Supervisor Access Protection.
 *                       Each bit is corresponding
 *                       to protection of 1/64 of the total P-Flash. The least
 *                       significant bit of protectStatus[0] is corresponding to the lowest
 *                       address area of P-Flash. The most significant bit of protectStatus[7]
 *                       is corresponding to the highest address area of P-
 *                       Flash and so on. There are two possible cases as below:
 *                       -  0: this area is protected.
 *                       -  1: this area is unprotected.
 * @param numberOfSegments: To return the number of program flash segments that are available for
 *                          XACC and SACC permissions.
 * @param segmentSize: To return segment size of program flash based on the available program size
 *                     divided by numberOfSegments.
 * @return Successful completion (FTFx_OK)
 */
extern uint32_t PFlashFacGetSAProtection(PFLASH_SSD_CONFIG pSSDConfig,\
                                  uint8_t *protectStatus,\
                                  uint8_t *numberOfSegments,\
                                  uint32_t *segmentSize);
#endif // PFLASH_FAC_PRESENCE

/*!
 * @brief Flash get security state.
 *
 * This API retrieves the current Flash security status, including
 * the security enabling state and the back door key enabling state.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param securityState: To return the current security status code.
 *                       FLASH_NOT_SECURE (0x01): Flash currently not in secure state;
 *                       FLASH_SECURE_BACKDOOR_ENABLED (0x02): Flash is secured and
 *                       back door key access enabled;
 *                       FLASH_SECURE_BACKDOOR_DISABLED (0x04): Flash is secured and
 *                       back door key access disabled.
 * @return Successful completion (FTFx_OK)
 */
extern uint32_t FlashGetSecurityState(PFLASH_SSD_CONFIG pSSDConfig, \
                                    uint8_t* securityState);
/*!
 * @brief Flash security bypass.
 *
 * This API un-secures the device by comparing the user's provided back
 * door key with the ones in  the Flash Configuration Field.  If  they are
 * matched,  the  security is  released. Otherwise, an
 * error code is returned.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param keyBuffer:     Point to the user buffer containing the back door key.
 * @param pFlashCommandSequence :     Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_ACCERR)
 */
extern uint32_t FlashSecurityBypass(PFLASH_SSD_CONFIG pSSDConfig, \
                                  uint8_t* keyBuffer, \
                                  pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*!
 * @brief Flash erase all Blocks.
 *
 * This API  erases all Flash memory,  initializes  the FlexRAM, verifies
 * all memory contents, and then releases the MCU security.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param pFlashCommandSequence :     Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_PVIOL, FTFx_ERR_MGSTAT0, FTFx_ERR_ACCERR)
 */
extern uint32_t FlashEraseAllBlock(PFLASH_SSD_CONFIG pSSDConfig, \
                                 pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*!
 * @brief Flash erase all Blocks unsecure.
 *
 * This API  erases all Flash memory,  initializes  the FlexRAM, verifies
 * all memory contents, program security byte to unsecure state, and then releases
 * MCU security.
 * Note: This API only applies to limited targets, please refer to FTFA/FTFE/FTFL chapter
 *       and check the validity of this API.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param pFlashCommandSequence :     Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_MGSTAT0, FTFx_ERR_ACCERR)
 */
extern uint32_t FlashEraseAllBlockUnsecure(PFLASH_SSD_CONFIG pSSDConfig, \
                                 pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*!
 * @brief Flash verify all Blocks.
 *
 * This function checks to see if the P-Flash and/or D-Flash, EEPROM
 * backup area, and D-Flash IFR have been erased to the specified read
 * margin level, if applicable, and releases security if the readout passes.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param marginLevel:   Read Margin Choice as follows:
 *                       marginLevel = 0x0: use the Normal read level
 *                       marginLevel = 0x1: use the User read
 *                       marginLevel = 0x2: use the Factory read
 * @param pFlashCommandSequence :     Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_MGSTAT0, FTFx_ERR_ACCERR)
 */
extern uint32_t FlashVerifyAllBlock(PFLASH_SSD_CONFIG pSSDConfig, \
                                  uint8_t marginLevel, \
                                  pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*!
 * @brief Flash erase sector.
 *
 * This API erases one or more sectors in P-Flash or  D-Flash memory.
 * This  API  always  returns  FTFx_OK  if  size  provided  by  the user  is
 * zero  regardless  of  the  input validation.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param dest:          Address in the first sector to be erased.
 * @param size:          Size to be erased in bytes. It is used to determine
 *                       number of sectors to be erased.
 * @param pFlashCommandSequence :     Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_MGSTAT0, FTFx_ERR_ACCERR, FTFx_ERR_PVIOL,FTFx_ERR_SIZE)
 */
extern uint32_t FlashEraseSector(PFLASH_SSD_CONFIG pSSDConfig, \
                               uint32_t dest, \
                               uint32_t size, \
                               pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*!
 * @brief Flash verify sector.
 *
 * This API  checks  if a section of the P-Flash or the D-Flash memory
 * is erased  to  the specified read margin level.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param dest:          Start address for the intended verify operation.
 * @param number:        Number of alignment unit to be verified. Refer to
 *                       corresponding reference manual to get correct
 *                       information of alignment constrain.
 * @param marginLevel:   Read Margin Choice as follows:
 *                       marginLevel = 0x0: use Normal read level
 *                       marginLevel = 0x1: use the User read
 *                       marginLevel = 0x2: use the Factory read
 * @param pFlashCommandSequence :     Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_MGSTAT0, FTFx_ERR_ACCERR)
 */
extern uint32_t FlashVerifySection(PFLASH_SSD_CONFIG pSSDConfig, \
                                 uint32_t dest, \
                                 uint16_t number, \
                                 uint8_t marginLevel, \
                                 pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*!
 * @brief Flash erase suspend.
 *
 * This API is used to suspend a current operation of Flash erase sector command.
 * This function must be located in RAM memory or different Flash blocks which are
 * targeted for writing to avoid the RWW error.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @return Successful completion (FTFx_OK)
 */
extern uint32_t FlashEraseSuspend(PFLASH_SSD_CONFIG pSSDConfig);
/*!
 * @brief Flash erase resume.
 *
 * This API is used to resume a previous suspended operation of Flash erase sector command
 * This function must be located in RAM memory or different Flash blocks which are targeted
 * for writing to avoid RWW error.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @return Successful completion (FTFx_OK)
 */
extern uint32_t FlashEraseResume(PFLASH_SSD_CONFIG pSSDConfig);
/*!
 * @brief Flash read once.
 *
 * This API is used to read out a reserved 64 byte field located in the P-Flash IFR via given number
 * of record. See the corresponding reference manual to get the correct value of this number.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param recordIndex:   The record index will be read. It can be from 0x0
 *                       to 0x7 or other range according to specific derivative.
 * @param size:          Byte count of data to be read. The value of size should
 *                       be 4 or 8 according to specific derivative.
 * @param pDataArray:    Pointer to the array to return the data read by the read once command.
 * @param pFlashCommandSequence :     Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_ACCERR)
 */
extern uint32_t FlashReadOnce(PFLASH_SSD_CONFIG pSSDConfig, \
                            uint8_t recordIndex,\
                            uint8_t* pDataArray, \
                            uint32_t size, \
                            pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*!
 * @brief Flash program once.
 *
 * This API  is  used  to  program  to  a  reserved  64  byte  field  located  in  the
 * P-Flash  IFR  via  given number of record. See the corresponding reference manual
 * to get correct value of this number.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param recordIndex:   The record index will be read. It can be from 0x0
 *                       to 0x7 or other range according to specific derivative.
 * @param pDataArray:    Pointer to the array from which data will be
 *                       taken for program once command.
 * @param size:          Byte count of data to be programmed. The value of size
 *                       should be 4 or 8 according to specific derivative.
 * @param pFlashCommandSequence :     Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_ACCERR,FTFx_ERR_MGSTAT0)
 */
extern uint32_t FlashProgramOnce(PFLASH_SSD_CONFIG pSSDConfig, \
                               uint8_t recordIndex,\
                               uint8_t* pDataArray, \
                               uint32_t size,\
                               pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*!
 * @brief Flash read resource.
 *
 * This API is used to read data from special purpose memory in Flash memory module
 * including P-Flash IFR, swap IFR, D-Flash IFR space and version ID.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param dest:          Start address for the intended read operation.
 * @param pDataArray:    Pointer to the data returned by the read resource command.
 * @param resourceSelectCode:    Read resource select code:
 *                               0 : Flash IFR
 *                               1: Version ID
 * @param pFlashCommandSequence :     Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_ACCERR)
 */
extern uint32_t FlashReadResource(PFLASH_SSD_CONFIG pSSDConfig, \
                                uint32_t dest, \
                                uint8_t* pDataArray, \
                                uint8_t  resourceSelectCode, \
                                pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*!
 * @brief Flash program
 *
 * This  API  is  used  to  program  4  consecutive  bytes  (for  program  long
 * word  command)  and  8 consecutive bytes (for program phrase command) on
 * P-Flash or D-Flash block. This  API  always  returns  FTFx_OK  if  size
 * provided  by  user  is  zero  regardless  of  the  input validation
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param dest:          Start address for the intended program operation.
 * @param size:          Size in byte to be programmed
 * @param pData:         Pointer of source address from which data has to
 *                       be taken for program operation.
 * @param pFlashCommandSequence :     Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_ACCERR, FTFx_ERR_PVIOL, FTFx_ERR_SIZE, FTFx_ERR_MGSTAT0)
 */
extern uint32_t FlashProgram(PFLASH_SSD_CONFIG pSSDConfig, \
                                   uint32_t dest, \
                                   uint32_t size, \
                                   uint8_t* pData, \
                                   pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*!
 * @brief Flash program check
 *
 * This API tests a previously programmed P-Flash or D-Flash long word
 * to see if it reads correctly at the specified margin level. This
 * API always returns FTFx_OK if size provided by user is zero
 * regardless  of  the  input validation
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param dest:          Start address for the intended program check operation.
 * @param size:          Size in byte to check accuracy of program operation
 * @param pExpectedData: The pointer to the expected data.
 * @param pFailAddr:     Returned the first aligned failing address.
 * @param marginLevel:   Read margin choice as follows:
 *                       marginLevel = 0x1: read at User margin 1/0 level.
 *                       marginLevel = 0x2: read at Factory margin 1/0 level.
 * @param pFlashCommandSequence :     Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_ACCERR, FTFx_ERR_MGSTAT0)
 */
extern uint32_t FlashProgramCheck(PFLASH_SSD_CONFIG pSSDConfig, \
                                uint32_t  dest, \
                                uint32_t  size, \
                                uint8_t*  pExpectedData, \
                                uint32_t* pFailAddr, \
                                uint8_t   marginLevel, \
                                pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

/*!
 * @brief Calculates check sum.
 *
 * This API  performs 32 bit sum of each byte data over a specified Flash
 * memory range without carry which provides rapid method for checking data integrity.
 * The  callback  time  period  of  this  API  is  determined  via  FLASH_CALLBACK_CS  macro  in the
 * SSD_FTFx_Common.h  which is used as a counter value for the CallBack() function calling in
 * this API. This value can be changed as per  the user  requirement. User can change  this value  to
 * obtain the maximum permissible callback time period.
 * This  API  always  returns  FTFx_OK  if  size  provided  by  user  is  zero  regardless  of  the  input
 * validation.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param dest:          Start address of the Flash range to be summed
 * @param size:          Size in byte of the Flash range to be summed
 * @param pSum:          To return the sum value
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_RANGE)
 */
extern uint32_t FlashCheckSum(PFLASH_SSD_CONFIG pSSDConfig, \
                            uint32_t dest, \
                            uint32_t size, \
                            uint32_t* pSum);

#ifndef FTFA_M
/*!
 * @brief Flash program section
 *
 * This API will program the data found in the Section Program Buffer
 * to previously erased locations in the Flash memory. Data is preloaded into
 * the Section Program Buffer by writing to the acceleration Ram and FlexRam
 * while it is set to function as a RAM. The Section Program Buffer is limited
 * to  the  value of FlexRam divides by a ratio. Refer to the associate reference
 * manual to get correct value of this ratio.
 * For derivatives including swap feature, the swap indicator address is encountered
 * during FlashProgramSection, it is bypassed without setting FPVIOL but the content
 * are not be programmed. In addition, the content of source data used to program to
 * swap indicator will be re-initialized to 0xFF after completion of this command.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param dest:          Start address for the intended program operation.
 * @param number:          Number of alignment unit to be programmed. Refer to associate
 *                       reference manual to get correct value of this alignment constrain.
 * @param pFlashCommandSequence :  Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_ACCERR, FTFx_ERR_PVIOL, FTFx_ERR_MGSTAT0, FTFx_ERR_RAMRDY)
 */
extern uint32_t FlashProgramSection(PFLASH_SSD_CONFIG pSSDConfig, \
                                  uint32_t dest, \
                                  uint16_t number, \
                                  pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
#endif

#if (!(defined(FTFA_M)) || (defined(BLOCK_COMMANDS)))
/*!
 * @brief Flash erase block
 *
 * This API  erases all addresses in an individual P-Flash or D-Flash block.
 * For  the derivatives  including multiply  logical P-Flash or D-Flash blocks,
 * this API   erases a single block in a single call.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param dest:          Start address for the intended erase operation.
 * @param pFlashCommandSequence :  Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_ACCERR, FTFx_ERR_PVIOL, FTFx_ERR_MGSTAT0)
 */
extern uint32_t FlashEraseBlock(PFLASH_SSD_CONFIG pSSDConfig, \
                                   uint32_t dest, \
                                   pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*!
 * @brief Flash verify block
 *
 * This API  checks to see  if an entire P-Flash or D-Flash block has been
 * erased to the specified margin level
 * For  the derivatives  including multiply  logical P-Flash or D-Flash blocks,
 * this API   erases a single block in a single call.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param dest:          Start address for the intended verify operation.
 * @param marginLevel:   Read Margin Choice as follows:
 *                       marginLevel = 0x0: use Normal read level
 *                       marginLevel = 0x1: use the User read
 *                       marginLevel = 0x2: use the Factory read
 * @param pFlashCommandSequence :  Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_ACCERR, FTFx_ERR_MGSTAT0)
 */
extern uint32_t FlashVerifyBlock(PFLASH_SSD_CONFIG pSSDConfig, \
                               uint32_t dest, \
                               uint8_t marginLevel, \
                               pFLASHCOMMANDSEQUENCE pFlashCommandSequence);

#endif

#if (DEBLOCK_SIZE != 0x0U)
/*!
 * @brief EERAM get protection
 *
 * This  API  retrieves  which  EEPROM  sections  of  FlexRAM  are  protected
 * against  program  and erase operations. Considering  the  time consumption
 * for getting protection is very low and even can be ignored, it is not necessary
 * to utilize the Callback function to support the time-critical events
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param protectStatus: To return the current value of the EEPROM
 *                       Protection Register. Each bit is corresponding to
 *                       protection status of 1/8 of the total EEPROM
 *                       use. The least significant bit is corresponding to
 *                       the lowest address area of EEPROM. The most
 *                       significant bit is corresponding to the highest
 *                       address area of EEPROM and so on. There are
 *                       two possible cases as below:
 *                       -  0: this area is protected.
 *                       -  1: this area is unprotected.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_NOEEE)
 */
extern uint32_t EERAMGetProtection(PFLASH_SSD_CONFIG pSSDConfig, \
                                 uint8_t*  protectStatus);
/*!
 * @brief EERAM set protection
 *
 * This API sets protection to the intended protection status for EEPROM us
 * area of FlexRam. This is subject to a protection transition restriction.
 * If there is a setting violation, it returns failed information and
 * the current protection status won’t be changed.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param protectStatus: The intended protection status value should be
 *                       written to the EEPROM Protection Register.
 *                       Each bit is corresponding to
 *                       protection status of 1/8 of the total EEPROM
 *                       use. The least significant bit is corresponding to
 *                       the lowest address area of EEPROM. The most
 *                       significant bit is corresponding to the highest
 *                       address area of EEPROM and so on. There are
 *                       two possible cases as below:
 *                       -  0: this area is protected.
 *                       -  1: this area is unprotected.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_NOEEE,FTFx_ERR_CHANGEPROT)
 */
extern uint32_t EERAMSetProtection(PFLASH_SSD_CONFIG pSSDConfig, \
                                 uint8_t  protectStatus);
/*!
 * @brief Flash Set EEEEnable
 *
 * This function is used to change the function of the FlexRAM. When not
 * partitioned for EEPROM backup, the FlexRam is typically used as traditional
 * RAM. Otherwise, the FlexRam is typically used to store EEPROM data and user
 * can use this API to change its functionality according to his application requirement.
 * For example, after partitioning to have EEPROM backup, FlexRAM  is used  for EEPROM
 * use accordingly. And this API is used to set FlexRAM is available for
 * traditional RAM for FlashProgramSection() use.
 *
 * @param pSSDConfig:               The SSD configuration structure pointer.
 * @param EEEEnable:                FlexRam function control code. It can be:
 *                                  -  0xFF: make FlexRam available for RAM.
 *                                  -  0x00: make FlexRam available for EEPROM.
 * @param pFlashCommandSequence:    Pointer to the Flash command sequence function.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_ACCERR)
 */
extern uint32_t SetEEEEnable(PFLASH_SSD_CONFIG pSSDConfig, \
                           uint8_t EEEEnable,pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*!
 * @brief EEPROM Emulator Write
 *
 * This API is used to write data to FlexRAM section which is  partitioned
 * as EEPROM use for EEPROM operation. After data has been written to EEPROM
 * use section of FlexRAM, the EEPROM file system will create new data record
 * in EEPROM back-up area of FlexNVM in round-robin fashion.
 * There  is no alignment constraint for destination and size parameters
 * provided by user. However, according to user’s input provided, this
 * API will set priority to write to FlexRAM with following rules:
 * 32-bit writing is invoked if destination is 32 bit aligned and size
 * is not  less than 32 bits.
 * 16-bit writing is  invoked if destination is 16 bit aligned and size
 * is not  less than 16 bits.
 * 8-bit writing is invoked if destination is 8 bit aligned and size is not less than 8 bits.
 *
 * @param pSSDConfig:    The SSD configuration structure pointer.
 * @param dest:          Start address for the intended write operation.
 * @param size:          Size in byte to be written.
 * @param pData:         Pointer to source address from which data
 *                       has to be taken for writing operation.
 * @return Successful completion (FTFx_OK)
 * @return Error value  (FTFx_ERR_RANGE, FTFx_ERR_NOEEE, FTFx_ERR_PVIOL)
 */
extern uint32_t EEEWrite(PFLASH_SSD_CONFIG pSSDConfig, \
                       uint32_t dest, \
                       uint32_t size, \
                       uint8_t* pData);
/*!
 * @brief Flash D/E-Flash Partition.
 *
 * This API prepares the FlexNVM block for use as D-Flash, EEPROM backup, or a combination
 * of both and initializes the FlexRAM.
 *
 * The single partition choice should be used through entire life time of a given
 * application to guarantee the Flash endurance and data retention of Flash module.
 *
 * @param   pSSDConfig                The SSD configuration structure pointer
 * @param   EEEDataSizeCode           EEPROM Data Size Code
 * @param   DEPartitionCode           FlexNVM Partition Code
 * @param   pFlashCommandSequence     Pointer to the Flash command sequence function.
 *
 * @return  Successful completion(FTFx_OK)
 * @return  Error value(FTFx_ERR_ACCERR, FTFx_ERR_MGSTAT0)
 */

extern uint32_t DEFlashPartition(PFLASH_SSD_CONFIG pSSDConfig, \
                               uint8_t EEEDataSizeCode, \
                               uint8_t DEPartitionCode, \
                               pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*!
 * @brief D-Flash get protection.
 *
 * This API retrieves current P-Flash protection status. Considering the time consumption
 * for getting protection is very low and even can be ignored, it is not necessary to utilize
 * the Callback function to support the time-critical events.
 *
 * @param   pSSDConfig                The SSD configuration structure pointer
 * @param   protectStatus             To return the current value of the D-Flash Protection
 *                                    Register. Each bit is corresponding to protection status
 *                                    of 1/8 of the total D-Flash. The least significant bit is
 *                                    corresponding to the lowest address area of D-Flash. The
 *                                    most significant bit is corresponding to the highest address
 *                                    area of D-Flash and so on. There are two possible cases as below:
 *                                    - 0 : this area is protected.
 *                                    - 1 : this area is unprotected.
 *
 * @return  Successful completion(FTFx_OK)
 * @return  Error value(FTFx_ERR_EFLASHONLY)
 */
extern uint32_t DFlashGetProtection(PFLASH_SSD_CONFIG pSSDConfig, \
                                  uint8_t*  protectStatus);

/*!
 * @brief D-Flash set protection.
 *
 * This API sets the D-Flash protection to the intended protection status. Setting D-Flash
 * protection status is subject to a protection transition restriction. If there is a setting
 * violation, it returns failed information and the current protection status won’t be changed.
 *
 * @param   pSSDConfig                The SSD configuration structure pointer
 * @param   protectStatus             The expected protect status user wants to set to D-Flash Protection
 *                                    Register. Each bit is corresponding to protection status
 *                                    of 1/8 of the total D-Flash. The least significant bit is
 *                                    corresponding to the lowest address area of D-Flash. The
 *                                    most significant bit is corresponding to the highest address
 *                                    area of D-Flash and so on. There are two possible cases as below:
 *                                    - 0 : this area is protected.
 *                                    - 1 : this area is unprotected.
 *
 * @return  Successful completion(FTFx_OK)
 * @return  Error value(FTFx_ERR_EFLASHONLY,FTFx_ERR_CHANGEPROT)
 */
extern uint32_t DFlashSetProtection(PFLASH_SSD_CONFIG pSSDConfig, \
                                  uint8_t  protectStatus);
#endif /* End of DEBLOCK_SIZE */

#ifdef SWAP_M
/*!
 * @brief  Swaps between the two halves of the total logical P-Flash memory blocks in the memory map.
 *
 * The swap API provides to user with an ability to interfere in a swap progress by letting the
 * user code know about the swap state in each phase of the process. This is done via pSwapCallBack()
 * parameter. To stop at each intermediate swap state,  set the return value of
 * this callback function to FALSE. To complete swap process within a single call,
 * set the return value of this function to TRUE.
 *
 * Erase the non-active swap indicator  somewhere in the
 * application code or  in the swap call back function when swap system is in UPDATE state.
 *
 * In addition, if user does not want to use the swap call back parameter,  pass the NULL_SWAP_CALLBACK
 * as a null pointer. In this situation, the PFlashSwap()  behaves in the same way as  setting the return
 * value of pSwapCallBack to TRUE and the user does not need to erase the non-active swap
 * indicator when the swap system is in UPDATE state.
 *
 * Below is an example to show how to implement a swap callback:
 * @code
 * bool PFlashSwapCallback(uint8_t currentSwapMode)
 * {
 *     switch (currentSwapMode)
 *     {
 *     case FTFx_SWAP_UNINI:
 *         // Put your application-specific code here
 *         break;
 *     case FTFx_SWAP_READY:
 *         // Put your application-specific code here
 *         break;
 *     case FTFx_SWAP_UPDATE:
 *         // Put your application-specific code here (example: erase non-active swap indicator here)
 *         break;
 *     case FTFx_SWAP_UPDATE_ERASED:
 *         // Put your application-specific code here (example: erase non-active swap indicator here)
 *         break;
 *     case FTFx_SWAP_COMPLETE:
 *         // Put your application-specific code here
 *         break;
 *     default:
 *         break;
 *    }
 *        return TRUE; // Return FALSE to stop at intermediate swap state
 *}
 * @endcode
 * The swap indicator provided by the user must be within the lower half of P-Flash block but not in the
 * Flash configuration area. If P-Flash block has two logical blocks, the swap indicator must be
 * in P-Flash block 0. If the P-Flash block has four logical blocks, the swap indicator can be in block
 * 0 or block 1. It must not be in the Flash configuration field.
 * The user must use the same swap indicator for all swap control code except report swap status once
 * swap system has been initialized. To refresh swap system to un-initialization state,
 * use the FlashEraseAllBlock() to clean up the swap environment.
 *
 * @param   pSSDConfig                The SSD configuration structure pointer
 * @param   addr                      Address of swap indicator.
 * @param   pSwapCallback             Callback to do specific task while the swapping is being performed
 * @param   pFlashCommandSequence     Pointer to the Flash command sequence function.
 *
 * @return  Successful completion(FTFx_OK)
 * @return  Error value(FTFx_ERR_ACCERR,FTFx_ERR_MGSTAT0)
 */
extern uint32_t PFlashSwap(PFLASH_SSD_CONFIG pSSDConfig, \
                  uint32_t addr, \
                  PFLASH_SWAP_CALLBACK pSwapCallback, \
                  pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
/*!
 * @brief  Implements swap control command corresponding with the swap control code provided via the swapcmd parameter.
 *
 * @param   pSSDConfig                The SSD configuration structure pointer
 * @param   addr                      Address of swap indicator.
 * @param   swapcmd                   Swap Control Code:
 *                                      0x01 - Initialize Swap System
 *                                      0x02 - Set Swap in Update State
 *                                      0x04 - Set Swap in Complete Stat
 *                                      0x08 - Report Swap Status
 * @param   pCurrentSwapMode          Current Swap Mode:
 *                                      0x00 - Uninitialized
 *                                      0x01 - Ready
 *                                      0x02 - Update
 *                                      0x03 - Update-Erased
 *                                      0x04 - Complete
 * @param   pCurrentSwapBlockStatus   Current Swap Block Status indicates which program Flash block
 *                                    is currently located at relative Flash address 0x0_0000
 *                                      0x00 - Program Flash block 0
 *                                      0x01 - Program Flash block 1
 * @param   pNextSwapBlockStatus      Next Swap Block Status indicates which program Flash block
 *                                    is located at relative Flash address 0x0_0000 after the next reset.
 *                                      0x00 - Program Flash block 0
 *                                      0x01 - Program Flash block 1
 * @param   pFlashCommandSequence     Pointer to the Flash command sequence function.
 *
 * @return  Successful completion(FTFx_OK)
 * @return  Error value(FTFx_ERR_ACCERR,FTFx_ERR_MGSTAT0)
 */
extern uint32_t PFlashSwapCtl(PFLASH_SSD_CONFIG pSSDConfig, \
                             uint32_t addr, \
                             uint8_t swapcmd, \
                             uint8_t* pCurrentSwapMode,\
                             uint8_t* pCurrentSwapBlockStatus, \
                             uint8_t* pNextSwapBlockStatus, \
                             pFLASHCOMMANDSEQUENCE pFlashCommandSequence);
#endif /* End of SWAP_M */
/*@}*/

/*! @}*/
#endif  /* _SSD_FTFx_INTERNAL_H_ */
