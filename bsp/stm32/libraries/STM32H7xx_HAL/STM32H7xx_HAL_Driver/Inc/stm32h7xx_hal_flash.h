/**
  ******************************************************************************
  * @file    stm32h7xx_hal_flash.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32H7xx_HAL_FLASH_H
#define __STM32H7xx_HAL_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup FLASH_Exported_Types FLASH Exported Types
  * @{
  */
 
/**
  * @brief  FLASH Procedure structure definition
  */
typedef enum 
{
  FLASH_PROC_NONE = 0U, 
  FLASH_PROC_SECTERASE_BANK1,
  FLASH_PROC_MASSERASE_BANK1,
  FLASH_PROC_PROGRAM_BANK1,
  FLASH_PROC_SECTERASE_BANK2,
  FLASH_PROC_MASSERASE_BANK2,
  FLASH_PROC_PROGRAM_BANK2,
  FLASH_PROC_ALLBANK_MASSERASE
} FLASH_ProcedureTypeDef;


/** 
  * @brief  FLASH handle Structure definition  
  */
typedef struct
{
  __IO FLASH_ProcedureTypeDef ProcedureOnGoing;   /*!< Internal variable to indicate which procedure is ongoing or not in IT context */
  
  __IO uint32_t               NbSectorsToErase;   /*!< Internal variable to save the remaining sectors to erase in IT context        */
  
  __IO uint8_t                VoltageForErase;    /*!< Internal variable to provide voltage range selected by user in IT context     */
  
  __IO uint32_t               Sector;             /*!< Internal variable to define the current sector which is erasing               */
  
  __IO uint32_t               Address;            /*!< Internal variable to save address selected for program                        */
  
  HAL_LockTypeDef             Lock;               /*!< FLASH locking object                                                          */

  __IO uint32_t               ErrorCode;          /*!< FLASH error code                                                              */

}FLASH_ProcessTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */  

/** @defgroup FLASH_Error_Code FLASH Error Code
  * @brief    FLASH Error Code 
  * @{
  */ 

#define HAL_FLASH_ERROR_NONE         ((uint32_t)0x00000000U)  /*!< No error                         */

#define HAL_FLASH_ERROR_WRP    ((uint32_t)0x00000001U)  /*!< Write Protection Error */
#define HAL_FLASH_ERROR_PGS    ((uint32_t)0x00000002U)  /*!< Program Sequence Error */
#define HAL_FLASH_ERROR_STRB   ((uint32_t)0x00000004U)  /*!< Strobe Error           */
#define HAL_FLASH_ERROR_INC    ((uint32_t)0x00000008U)  /*!< Inconsistency Error    */
#define HAL_FLASH_ERROR_OPE    ((uint32_t)0x00000010U)  /*!< Operation Error        */
#define HAL_FLASH_ERROR_RDP    ((uint32_t)0x00000020U)  /*!< Read Protection Error  */
#define HAL_FLASH_ERROR_RDS    ((uint32_t)0x00000040U)  /*!< Read Secured Error     */
#define HAL_FLASH_ERROR_SNECC  ((uint32_t)0x00000080U)  /*!< Single Detection ECC   */
#define HAL_FLASH_ERROR_DBECC  ((uint32_t)0x00000100U)  /*!< Double Detection ECC   */

#define HAL_FLASH_ERROR_WRP_BANK1    ((uint32_t)0x00000001U)  /*!< Write Protection Error on Bank 1 */
#define HAL_FLASH_ERROR_PGS_BANK1    ((uint32_t)0x00000002U)  /*!< Program Sequence Error on Bank 1 */
#define HAL_FLASH_ERROR_STRB_BANK1   ((uint32_t)0x00000004U)  /*!< Strobe Error on Bank 1           */
#define HAL_FLASH_ERROR_INC_BANK1    ((uint32_t)0x00000008U)  /*!< Inconsistency Error on Bank 1    */
#define HAL_FLASH_ERROR_OPE_BANK1    ((uint32_t)0x00000010U)  /*!< Operation Error on Bank 1        */
#define HAL_FLASH_ERROR_RDP_BANK1    ((uint32_t)0x00000020U)  /*!< Read Protection Error on Bank 1  */
#define HAL_FLASH_ERROR_RDS_BANK1    ((uint32_t)0x00000040U)  /*!< Read Secured Error on Bank 1     */
#define HAL_FLASH_ERROR_SNECC_BANK1  ((uint32_t)0x00000080U)  /*!< Single Detection ECC on Bank 1   */
#define HAL_FLASH_ERROR_DBECC_BANK1  ((uint32_t)0x00000100U)  /*!< Double Detection ECC on Bank 1   */
  
#define HAL_FLASH_ERROR_WRP_BANK2    ((uint32_t)0x00001000U)  /*!< Write Protection Error on Bank 2 */
#define HAL_FLASH_ERROR_PGS_BANK2    ((uint32_t)0x00002000U)  /*!< Program Sequence Error on Bank 2 */
#define HAL_FLASH_ERROR_STRB_BANK2   ((uint32_t)0x00004000U)  /*!< Strobe Error on Bank 2           */
#define HAL_FLASH_ERROR_INC_BANK2    ((uint32_t)0x00008000U)  /*!< Inconsistency Error on Bank 2    */
#define HAL_FLASH_ERROR_OPE_BANK2    ((uint32_t)0x00010000U)  /*!< Operation Error on Bank 2        */
#define HAL_FLASH_ERROR_RDP_BANK2    ((uint32_t)0x00020000U)  /*!< Read Protection Error on Bank 2  */
#define HAL_FLASH_ERROR_RDS_BANK2    ((uint32_t)0x00040000U)  /*!< Read Secured Error on Bank 2     */
#define HAL_FLASH_ERROR_SNECC_BANK2  ((uint32_t)0x00080000U)  /*!< Single Detection ECC on Bank 2   */
#define HAL_FLASH_ERROR_DBECC_BANK2  ((uint32_t)0x00100000U)  /*!< Double Detection ECC on Bank 2   */

#define HAL_FLASH_ERROR_OB_CHANGE    ((uint32_t)0x01000000U)  /*!< Option Byte Change Error         */
  
/**
  * @}
  */
  
/** @defgroup FLASH_Type_Program FLASH Type Program
  * @{
  */ 
#define FLASH_TYPEPROGRAM_FLASHWORD  ((uint32_t)0x03U)  /*!< Program a flash word (256-bit) at a specified address */
/**
  * @}
  */

/** @defgroup FLASH_Flag_definition FLASH Flag definition
  * @brief Flag definition
  * @{
  */ 


#define FLASH_FLAG_BSY               FLASH_SR_BSY             /*!< FLASH Busy flag */
#define FLASH_FLAG_WDW               FLASH_SR_WDW             /*!< Waiting for Data to Write on flag */
#define FLASH_FLAG_QW                FLASH_SR_QW              /*!< Write Waiting in Operation Queue on flag */
#define FLASH_FLAG_CRC_BUSY          FLASH_SR_CRC_BUSY        /*!< CRC module is working on flag */
#define FLASH_FLAG_EOP               FLASH_SR_EOP             /*!< End Of Program on flag */
#define FLASH_FLAG_WRPERR            FLASH_SR_WRPERR          /*!< Write Protection Error on flag */
#define FLASH_FLAG_PGSERR            FLASH_SR_PGSERR          /*!< Program Sequence Error on flag */
#define FLASH_FLAG_STRBERR           FLASH_SR_STRBERR         /*!< strobe Error on flag */
#define FLASH_FLAG_INCERR            FLASH_SR_INCERR          /*!< Inconsistency Error on flag */
#define FLASH_FLAG_OPERR             FLASH_SR_OPERR           /*!< Operation Error on flag */
#define FLASH_FLAG_RDPERR            FLASH_SR_RDPERR          /*!< Read Protection Error on flag */
#define FLASH_FLAG_RDSERR            FLASH_SR_RDSERR          /*!< Read Secured Error on flag */
#define FLASH_FLAG_SNECCERR          FLASH_SR_SNECCERR        /*!< Single ECC Error Correction on flag */
#define FLASH_FLAG_DBECCERR          FLASH_SR_DBECCERR        /*!< Double Detection ECC Error on flag */
#define FLASH_FLAG_CRCEND            FLASH_SR_CRCEND          /*!< CRC module completes on bank flag */


#define FLASH_FLAG_BSY_BANK1               FLASH_SR_BSY             /*!< FLASH Bank 1 Busy flag */
#define FLASH_FLAG_WBNE_BANK1              FLASH_SR_WBNE            /*!< Waiting for Data to Write on Bank 1 flag */
#define FLASH_FLAG_QW_BANK1                FLASH_SR_QW              /*!< Write Waiting in Operation Queue on Bank 1 flag */
#define FLASH_FLAG_CRC_BUSY_BANK1          FLASH_SR_CRC_BUSY        /*!< CRC module is working on Bank 1 flag */
#define FLASH_FLAG_EOP_BANK1               FLASH_SR_EOP             /*!< End Of Program on Bank 1 flag */
#define FLASH_FLAG_WRPERR_BANK1            FLASH_SR_WRPERR          /*!< Write Protection Error on Bank 1 flag */
#define FLASH_FLAG_PGSERR_BANK1            FLASH_SR_PGSERR          /*!< Program Sequence Error on Bank 1 flag */
#define FLASH_FLAG_STRBER_BANK1R           FLASH_SR_STRBERR         /*!< strobe Error on Bank 1 flag */
#define FLASH_FLAG_INCERR_BANK1            FLASH_SR_INCERR          /*!< Inconsistency Error on Bank 1 flag */
#define FLASH_FLAG_OPERR_BANK1             FLASH_SR_OPERR           /*!< Operation Error on Bank 1 flag */
#define FLASH_FLAG_RDPERR_BANK1            FLASH_SR_RDPERR          /*!< Read Protection Error on Bank 1 flag */
#define FLASH_FLAG_RDSERR_BANK1            FLASH_SR_RDSERR          /*!< Read Secured Error on Bank 1 flag */
#define FLASH_FLAG_SNECCE_BANK1RR          FLASH_SR_SNECCERR        /*!< Single ECC Error Correction on Bank 1 flag */
#define FLASH_FLAG_DBECCE_BANK1RR          FLASH_SR_DBECCERR        /*!< Double Detection ECC Error on Bank 1 flag */
#define FLASH_FLAG_CRCEND_BANK1            FLASH_SR_CRCEND          /*!< CRC module completes on bank Bank 1 flag */


#define FLASH_FLAG_ALL_ERRORS_BANK1       (FLASH_FLAG_WRPERR_BANK1  | FLASH_FLAG_PGSERR_BANK1   | \
                                           FLASH_FLAG_STRBER_BANK1R | FLASH_FLAG_INCERR_BANK1   | \
                                           FLASH_FLAG_OPERR_BANK1   | FLASH_FLAG_RDPERR_BANK1   | \
                                           FLASH_FLAG_RDSERR_BANK1  | FLASH_FLAG_SNECCE_BANK1RR | \
                                           FLASH_FLAG_DBECCE_BANK1RR)

#define FLASH_FLAG_ALL_BANK1              (FLASH_FLAG_BSY_BANK1      | FLASH_FLAG_WBNE_BANK1      | \
                                           FLASH_FLAG_QW_BANK1       | FLASH_FLAG_CRC_BUSY_BANK1 | \
                                           FLASH_FLAG_EOP_BANK1      | FLASH_FLAG_CRCEND_BANK1   | \
                                           FLASH_FLAG_ALL_ERRORS_BANK1)

#define FLASH_FLAG_BSY_BANK2               (FLASH_SR_BSY      | 0x80000000U)        /*!< FLASH Bank 2 Busy flag */
#define FLASH_FLAG_WBNE_BANK2              (FLASH_SR_WBNE     | 0x80000000U)        /*!< Waiting for Data to Write on Bank 2 flag */
#define FLASH_FLAG_QW_BANK2                (FLASH_SR_QW       | 0x80000000U)        /*!< Write Waiting in Operation Queue on Bank 2 flag */
#define FLASH_FLAG_CRC_BUSY_BANK2          (FLASH_SR_CRC_BUSY | 0x80000000U)        /*!< CRC module is working on Bank 2 flag */
#define FLASH_FLAG_EOP_BANK2               (FLASH_SR_EOP      | 0x80000000U)        /*!< End Of Program on Bank 2 flag */
#define FLASH_FLAG_WRPERR_BANK2            (FLASH_SR_WRPERR   | 0x80000000U)        /*!< Write Protection Error on Bank 2 flag */
#define FLASH_FLAG_PGSERR_BANK2            (FLASH_SR_PGSERR   | 0x80000000U)        /*!< Program Sequence Error on Bank 2 flag */
#define FLASH_FLAG_STRBER_BANK2R           (FLASH_SR_STRBERR  | 0x80000000U)        /*!< Strobe Error on Bank 2 flag */
#define FLASH_FLAG_INCERR_BANK2            (FLASH_SR_INCERR   | 0x80000000U)        /*!< Inconsistency Error on Bank 2 flag */
#define FLASH_FLAG_OPERR_BANK2             (FLASH_SR_OPERR    | 0x80000000U)        /*!< Operation Error on Bank 2 flag */
#define FLASH_FLAG_RDPERR_BANK2            (FLASH_SR_RDPERR   | 0x80000000U)        /*!< Read Protection Error on Bank 2 flag */
#define FLASH_FLAG_RDSERR_BANK2            (FLASH_SR_RDSERR   | 0x80000000U)        /*!< Read Secured Error on Bank 2 flag */
#define FLASH_FLAG_SNECCE_BANK2RR          (FLASH_SR_SNECCERR | 0x80000000U)        /*!< Single ECC Error Correction on Bank 2 flag */
#define FLASH_FLAG_DBECCE_BANK2RR          (FLASH_SR_DBECCERR | 0x80000000U)        /*!< Double Detection ECC Error on Bank 2 flag */
#define FLASH_FLAG_CRCEND_BANK2            (FLASH_SR_CRCEND   | 0x80000000U)        /*!< CRC module completes on bank Bank 2 flag */


#define FLASH_FLAG_ALL_ERRORS_BANK2       (FLASH_FLAG_WRPERR_BANK2  | FLASH_FLAG_PGSERR_BANK2   | \
                                           FLASH_FLAG_STRBER_BANK2R | FLASH_FLAG_INCERR_BANK2   | \
                                           FLASH_FLAG_OPERR_BANK2   | FLASH_FLAG_RDPERR_BANK2   | \
                                           FLASH_FLAG_RDSERR_BANK2  | FLASH_FLAG_SNECCE_BANK2RR | \
                                           FLASH_FLAG_DBECCE_BANK2RR)

#define FLASH_FLAG_ALL_BANK2              (FLASH_FLAG_BSY_BANK2      | FLASH_FLAG_WBNE_BANK2      | \
                                           FLASH_FLAG_QW_BANK2       | FLASH_FLAG_CRC_BUSY_BANK2 | \
                                           FLASH_FLAG_EOP_BANK2      | FLASH_FLAG_CRCEND_BANK2   | \
                                           FLASH_FLAG_ALL_ERRORS_BANK2)



/**
  * @}
  */

/** @defgroup FLASH_Interrupt_definition FLASH Interrupt definition
  * @brief FLASH Interrupt definition
  * @{
  */

#define FLASH_IT_EOP_BANK1                  FLASH_CR_EOPIE       /*!< End of FLASH Bank 1 Operation Interrupt source */ 
#define FLASH_IT_WRPERR_BANK1               FLASH_CR_WRPERRIE    /*!< Write Protection Error on Bank 1 Interrupt source */ 
#define FLASH_IT_PGSERR_BANK1               FLASH_CR_PGSERRIE    /*!< Program Sequence Error on Bank 1 Interrupt source */ 
#define FLASH_IT_STRBERR_BANK1              FLASH_CR_STRBERRIE   /*!< Strobe Error on Bank 1 Interrupt source */ 
#define FLASH_IT_INCERR_BANK1               FLASH_CR_INCERRIE    /*!< Inconsistency Error on Bank 1 Interrupt source */ 
#define FLASH_IT_OPERR_BANK1                FLASH_CR_OPERRIE     /*!< Operation Error on Bank 1 Interrupt source */ 
#define FLASH_IT_RDPERR_BANK1               FLASH_CR_RDPERRIE    /*!< Read protection Error on Bank 1 Interrupt source */ 
#define FLASH_IT_RDSERR_BANK1               FLASH_CR_RDSERRIE    /*!< Read Secured Error on Bank 1 Interrupt source */ 
#define FLASH_IT_SNECCERR_BANK1             FLASH_CR_SNECCERRIE  /*!< Single ECC Error Correction on Bank 1 Interrupt source */
#define FLASH_IT_DBECCERR_BANK1             FLASH_CR_DBECCERRIE  /*!< Double Detection ECC Error on Bank 1 Interrupt source */
#define FLASH_IT_CRCEND_BANK1               FLASH_CR_CRCENDIE    /*!< CRC End on Bank 1 Interrupt source */

#define FLASH_IT_ALL_BANK1                 (FLASH_IT_EOP_BANK1       | FLASH_IT_WRPERR_BANK1    | \
                                            FLASH_IT_PGSERR_BANK1    | FLASH_IT_STRBERR_BANK1   | \
                                            FLASH_IT_INCERR_BANK1    | FLASH_IT_OPERR_BANK1     | \
                                            FLASH_IT_RDPERR_BANK1    | FLASH_IT_RDSERR_BANK1    | \
                                            FLASH_CR_SNECCERRIE | FLASH_CR_DBECCERRIE | \
                                            FLASH_CR_CRCENDIE )

#define FLASH_IT_EOP_BANK2                 (FLASH_CR_EOPIE      | 0x80000000U)  /*!< End of FLASH Bank 2 Operation Interrupt source */ 
#define FLASH_IT_WRPERR_BANK2              (FLASH_CR_WRPERRIE   | 0x80000000U)  /*!< Write Protection Error on Bank 2 Interrupt source */ 
#define FLASH_IT_PGSERR_BANK2              (FLASH_CR_PGSERRIE   | 0x80000000U)  /*!< Program Sequence Error on Bank 2 Interrupt source */ 
#define FLASH_IT_STRBERR_BANK2             (FLASH_CR_STRBERRIE  | 0x80000000U)  /*!< Strobe Error on Bank 2 Interrupt source */ 
#define FLASH_IT_INCERR_BANK2              (FLASH_CR_INCERRIE   | 0x80000000U)  /*!< Inconsistency Error on Bank 2 Interrupt source */ 
#define FLASH_IT_OPERR_BANK2               (FLASH_CR_OPERRIE    | 0x80000000U)  /*!< Operation Error on Bank 2 Interrupt source */ 
#define FLASH_IT_RDPERR_BANK2              (FLASH_CR_RDPERRIE   | 0x80000000U)  /*!< Read protection Error on Bank 2 Interrupt source */ 
#define FLASH_IT_RDSERR_BANK2              (FLASH_CR_RDSERRIE   | 0x80000000U)  /*!< Read Secured Error on Bank 2 Interrupt source */ 
#define FLASH_IT_SNECCERR_BANK2            (FLASH_CR_SNECCERRIE | 0x80000000U)  /*!< Single ECC Error Correction on Bank 2 Interrupt source */
#define FLASH_IT_DBECCERR_BANK2            (FLASH_CR_DBECCERRIE | 0x80000000U)  /*!< Double Detection ECC Error on Bank 2 Interrupt source */
#define FLASH_IT_CRCEND_BANK2              (FLASH_CR_CRCENDIE   | 0x80000000U)  /*!< CRC End on Bank 2 Interrupt source */


#define FLASH_IT_ALL_BANK2                 (FLASH_IT_EOP_BANK2       | FLASH_IT_WRPERR_BANK1    | \
                                            FLASH_IT_PGSERR_BANK2    | FLASH_IT_STRBERR_BANK1   | \
                                            FLASH_IT_INCERR_BANK2    | FLASH_IT_OPERR_BANK1     | \
                                            FLASH_IT_RDPERR_BANK2    | FLASH_IT_RDSERR_BANK1    | \
                                            FLASH_CR_SNECCERRIE | FLASH_CR_DBECCERRIE | \
                                            FLASH_CR_CRCENDIE )
/**
  * @}
  */

/** @defgroup FLASH_Program_Parallelism FLASH Program Parallelism
  * @{
  */
#define FLASH_PSIZE_BYTE           ((uint32_t)0x00000000U)
#define FLASH_PSIZE_HALF_WORD      ((uint32_t)FLASH_CR_PSIZE_0)
#define FLASH_PSIZE_WORD           ((uint32_t)FLASH_CR_PSIZE_1)
#define FLASH_PSIZE_DOUBLE_WORD    ((uint32_t)FLASH_CR_PSIZE)
#define CR_PSIZE_MASK              ((uint32_t)0xFFFFFFCFU)
/**
  * @}
  */ 


/** @defgroup FLASH_Keys FLASH Keys
  * @{
  */ 
#define FLASH_KEY1               ((uint32_t)0x45670123U)
#define FLASH_KEY2               ((uint32_t)0xCDEF89ABU)
#define FLASH_OPT_KEY1           ((uint32_t)0x08192A3BU)
#define FLASH_OPT_KEY2           ((uint32_t)0x4C5D6E7FU)
/**
  * @}
  */

/** @defgroup FLASH_Sectors FLASH Sectors
  * @{
  */
#define FLASH_SECTOR_0           ((uint32_t)0U) /*!< Sector Number 0   */
#define FLASH_SECTOR_1           ((uint32_t)1U) /*!< Sector Number 1   */
#define FLASH_SECTOR_2           ((uint32_t)2U) /*!< Sector Number 2   */
#define FLASH_SECTOR_3           ((uint32_t)3U) /*!< Sector Number 3   */
#define FLASH_SECTOR_4           ((uint32_t)4U) /*!< Sector Number 4   */
#define FLASH_SECTOR_5           ((uint32_t)5U) /*!< Sector Number 5   */
#define FLASH_SECTOR_6           ((uint32_t)6U) /*!< Sector Number 6   */
#define FLASH_SECTOR_7           ((uint32_t)7U) /*!< Sector Number 7   */
/**
  * @}
  */ 

/**
  * @}
  */  
  
/* Exported macro ------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
  * @{
  */
/**
  * @brief  Set the FLASH Latency.
  * @param  __LATENCY__: FLASH Latency                   
  *         The value of this parameter depend on device used within the same series
  * @retval none
  */
#define __HAL_FLASH_SET_LATENCY(__LATENCY__) \
                  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (uint32_t)(__LATENCY__))

/**
  * @brief  Get the FLASH Latency.
  * @retval FLASH Latency                   
  *          The value of this parameter depend on device used within the same series
  */ 
#define __HAL_FLASH_GET_LATENCY()     (READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY))

/**
  * @brief  Enable the specified FLASH interrupt.
  * @param  __INTERRUPT__ : FLASH interrupt 
  *   In case of Bank 1 This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP_BANK1       : End of FLASH Bank 1 Operation Interrupt source 
  *     @arg FLASH_IT_WRPERR_BANK1    : Write Protection Error on Bank 1 Interrupt source 
  *     @arg FLASH_IT_PGSERR_BANK1    : Program Sequence Error on Bank 1 Interrupt source 
  *     @arg FLASH_IT_STRBERR_BANK1   : Strobe Error on Bank 1 Interrupt source 
  *     @arg FLASH_IT_INCERR_BANK1    : Inconsistency Error on Bank 1 Interrupt source 
  *     @arg FLASH_IT_OPERR_BANK1     : Operation Error on Bank 1 Interrupt source
  *     @arg FLASH_IT_RDPERR_BANK1    : Read protection Error on Bank 1 Interrupt source 
  *     @arg FLASH_IT_RDSERR_BANK1    : Read secure Error on Bank 1 Interrupt source
  *     @arg FLASH_IT_SNECCERR_BANK1  : Single ECC Error Correction on Bank 1 Interrupt source
  *     @arg FLASH_IT_DBECCERR_BANK1  : Double Detection ECC Error on Bank 1 Interrupt source
  *     @arg FLASH_IT_CRCEND_BANK1    : CRC End on Bank 1 Interrupt source

  *   In case of Bank 2 This parameter can be any combination of the following values:  *
  *     @arg FLASH_IT_EOP_BANK2       : End of FLASH Bank 2 Operation Interrupt source 
  *     @arg FLASH_IT_WRPERR_BANK2    : Write Protection Error on Bank 2 Interrupt source 
  *     @arg FLASH_IT_PGSERR_BANK2    : Program Sequence Error on Bank 2 Interrupt source 
  *     @arg FLASH_IT_STRBERR_BANK2   : Strobe Error on Bank 2 Interrupt source 
  *     @arg FLASH_IT_INCERR_BANK2    : Inconsistency Error on Bank 2 Interrupt source 
  *     @arg FLASH_IT_OPERR_BANK2     : Operation Error on Bank 2 Interrupt source
  *     @arg FLASH_IT_RDPERR_BANK2    : Read protection Error on Bank 2 Interrupt source 
  *     @arg FLASH_IT_RDSERR_BANK2    : Read secure Error on Bank 2 Interrupt source
  *     @arg FLASH_IT_SNECCERR_BANK2  : Single ECC Error Correction on Bank 2 Interrupt source
  *     @arg FLASH_IT_DBECCERR_BANK2  : Double Detection ECC Error on Bank 2 Interrupt source
  *     @arg FLASH_IT_CRCEND_BANK2    : CRC End on Bank 2 Interrupt source
  * @retval none
  */

#define __HAL_FLASH_ENABLE_IT_BANK1(__INTERRUPT__)      (FLASH->CR1 |= (__INTERRUPT__))

#define __HAL_FLASH_ENABLE_IT_BANK2(__INTERRUPT__)      (FLASH->CR2 |= ((__INTERRUPT__) & 0x7FFFFFFF))

#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)    (IS_FLASH_IT_BANK1(__INTERRUPT__) ? \
                                                 __HAL_FLASH_ENABLE_IT_BANK1(__INTERRUPT__) : \
                                                 __HAL_FLASH_ENABLE_IT_BANK2(__INTERRUPT__))


/**
  * @brief  Disable the specified FLASH interrupt.
  * @param  __INTERRUPT__ : FLASH interrupt 
  *   In case of Bank 1 This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP_BANK1       : End of FLASH Bank 1 Operation Interrupt source 
  *     @arg FLASH_IT_WRPERR_BANK1    : Write Protection Error on Bank 1 Interrupt source 
  *     @arg FLASH_IT_PGSERR_BANK1    : Program Sequence Error on Bank 1 Interrupt source 
  *     @arg FLASH_IT_STRBERR_BANK1   : Strobe Error on Bank 1 Interrupt source 
  *     @arg FLASH_IT_INCERR_BANK1    : Inconsistency Error on Bank 1 Interrupt source 
  *     @arg FLASH_IT_OPERR_BANK1     : Operation Error on Bank 1 Interrupt source
  *     @arg FLASH_IT_RDPERR_BANK1    : Read protection Error on Bank 1 Interrupt source 
  *     @arg FLASH_IT_RDSERR_BANK1    : Read secure Error on Bank 1 Interrupt source
  *     @arg FLASH_IT_SNECCERR_BANK1  : Single ECC Error Correction on Bank 1 Interrupt source
  *     @arg FLASH_IT_DBECCERR_BANK1  : Double Detection ECC Error on Bank 1 Interrupt source
  *     @arg FLASH_IT_CRCEND_BANK1    : CRC End on Bank 1 Interrupt source

  *   In case of Bank 2 This parameter can be any combination of the following values:  *
  *     @arg FLASH_IT_EOP_BANK2       : End of FLASH Bank 2 Operation Interrupt source 
  *     @arg FLASH_IT_WRPERR_BANK2    : Write Protection Error on Bank 2 Interrupt source 
  *     @arg FLASH_IT_PGSERR_BANK2    : Program Sequence Error on Bank 2 Interrupt source 
  *     @arg FLASH_IT_STRBERR_BANK2   : Strobe Error on Bank 2 Interrupt source 
  *     @arg FLASH_IT_INCERR_BANK2    : Inconsistency Error on Bank 2 Interrupt source 
  *     @arg FLASH_IT_OPERR_BANK2     : Operation Error on Bank 2 Interrupt source
  *     @arg FLASH_IT_RDPERR_BANK2    : Read protection Error on Bank 2 Interrupt source 
  *     @arg FLASH_IT_RDSERR_BANK2    : Read secure Error on Bank 2 Interrupt source
  *     @arg FLASH_IT_SNECCERR_BANK2  : Single ECC Error Correction on Bank 2 Interrupt source
  *     @arg FLASH_IT_DBECCERR_BANK2  : Double Detection ECC Error on Bank 2 Interrupt source
  *     @arg FLASH_IT_CRCEND_BANK2    : CRC End on Bank 2 Interrupt source

  * @retval none
  */  

#define __HAL_FLASH_DISABLE_IT_BANK1(__INTERRUPT__)  (FLASH->CR1 &= ~(uint32_t)(__INTERRUPT__))

#define __HAL_FLASH_DISABLE_IT_BANK2(__INTERRUPT__)  (FLASH->CR2 &= ~(uint32_t)((__INTERRUPT__) & 0x7FFFFFFF))

#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)  (IS_FLASH_IT_BANK1(__INTERRUPT__) ? \
                                                __HAL_FLASH_DISABLE_IT_BANK1(__INTERRUPT__) : \
                                                __HAL_FLASH_DISABLE_IT_BANK2(__INTERRUPT__))   


/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  __FLAG__: specifies the FLASH flag to check.
  *   In case of Bank 1 This parameter can be any combination of the following values :
  *     @arg FLASH_FLAG_BSY_BANK1      : FLASH Bank 1 Busy flag
  *     @arg FLASH_FLAG_WBNE_BANK1      : Waiting for Data to Write on Bank 1 flag
  *     @arg FLASH_FLAG_QW_BANK1       : Write Waiting in Operation Queue on Bank 1 flag
  *     @arg FLASH_FLAG_CRC_BUSY_BANK1 : CRC module is working on Bank 1 flag
  *     @arg FLASH_FLAG_EOP_BANK1      : End Of Program on Bank 1 flag
  *     @arg FLASH_FLAG_WRPERR_BANK1   : Write Protection Error on Bank 1 flag
  *     @arg FLASH_FLAG_PGSERR_BANK1   : Program Sequence Error on Bank 1 flag
  *     @arg FLASH_FLAG_STRBER_BANK1   : Program Alignment Error on Bank 1 flag
  *     @arg FLASH_FLAG_INCERR_BANK1   : Inconsistency Error on Bank 1 flag
  *     @arg FLASH_FLAG_OPERR_BANK1    : Operation Error on Bank 1 flag
  *     @arg FLASH_FLAG_RDPERR_BANK1   : Read Protection Error on Bank 1 flag
  *     @arg FLASH_FLAG_RDSERR_BANK1   : Read secure  Error on Bank 1 flag 
  *     @arg FLASH_FLAG_SNECCE_BANK1   : Single ECC Error Correction on Bank 1 flag
  *     @arg FLASH_FLAG_DBECCE_BANK1   : Double Detection ECC Error on Bank 1 flag
  *     @arg FLASH_FLAG_CRCEND_BANK1   : CRC End on Bank 1 flag
  *
  *   In case of Bank 2 This parameter can be any combination of the following values :
  *     @arg FLASH_FLAG_BSY_BANK2      : FLASH Bank 2 Busy flag
  *     @arg FLASH_FLAG_WBNE_BANK2      : Waiting for Data to Write on Bank 2 flag
  *     @arg FLASH_FLAG_QW_BANK2       : Write Waiting in Operation Queue on Bank 2 flag
  *     @arg FLASH_FLAG_CRC_BUSY_BANK2 : CRC module is working on Bank 2 flag
  *     @arg FLASH_FLAG_EOP_BANK2      : End Of Program on Bank 2 flag
  *     @arg FLASH_FLAG_WRPERR_BANK2   : Write Protection Error on Bank 2 flag
  *     @arg FLASH_FLAG_PGSERR_BANK2   : Program Sequence Error on Bank 2 flag
  *     @arg FLASH_FLAG_STRBER_BANK2   : Program Alignment Error on Bank 2 flag
  *     @arg FLASH_FLAG_INCERR_BANK2   : Inconsistency Error on Bank 2 flag
  *     @arg FLASH_FLAG_OPERR_BANK2    : Operation Error on Bank 2 flag
  *     @arg FLASH_FLAG_RDPERR_BANK2   : Read Protection Error on Bank 2 flag
  *     @arg FLASH_FLAG_RDSERR_BANK2   : Read secure  Error on Bank 2 flag 
  *     @arg FLASH_FLAG_SNECCE_BANK2   : Single ECC Error Correction on Bank 2 flag
  *     @arg FLASH_FLAG_DBECCE_BANK2   : Double Detection ECC Error on Bank 2 flag
  *     @arg FLASH_FLAG_CRCEND_BANK2   : CRC End on Bank 2 flag
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG_BANK1(__FLAG__)          (READ_BIT(FLASH->SR1, (__FLAG__)) == (__FLAG__))

#define __HAL_FLASH_GET_FLAG_BANK2(__FLAG__)          (READ_BIT(FLASH->SR2, ((__FLAG__) & 0x7FFFFFFF)) == (((__FLAG__) & 0x7FFFFFFF)))

#define __HAL_FLASH_GET_FLAG(__FLAG__)          (IS_FLASH_FLAG_BANK1(__FLAG__) ?  __HAL_FLASH_GET_FLAG_BANK1(__FLAG__) : \
                                                 __HAL_FLASH_GET_FLAG_BANK2(__FLAG__))


/**
  * @brief  Clear the specified FLASH flag.
  * @param  __FLAG__: specifies the FLASH flags to clear.
  *          This parameter can be any combination of the following values:
  *     @arg FLASH_FLAG_EOP_BANK1      : End Of Program on Bank 1 flag
  *     @arg FLASH_FLAG_WRPERR_BANK1   : Write Protection Error on Bank 1 flag
  *     @arg FLASH_FLAG_PGSERR_BANK1   : Program Sequence Error on Bank 1 flag
  *     @arg FLASH_FLAG_STRBER_BANK1   : Program Alignment Error on Bank 1 flag
  *     @arg FLASH_FLAG_INCERR_BANK1   : Inconsistency Error on Bank 1 flag
  *     @arg FLASH_FLAG_OPERR_BANK1    : Operation Error on Bank 1 flag
  *     @arg FLASH_FLAG_RDPERR_BANK1   : Read Protection Error on Bank 1 flag
  *     @arg FLASH_FLAG_RDSERR_BANK1   : Read secure  Error on Bank 1 flag 
  *     @arg FLASH_FLAG_SNECCE_BANK1   : Single ECC Error Correction on Bank 1 flag
  *     @arg FLASH_FLAG_DBECCE_BANK1   : Double Detection ECC Error on Bank 1 flag
  *     @arg FLASH_FLAG_CRCEND_BANK1   : CRC End on Bank 1 flag
  *
  *   In case of Bank 2 This parameter can be any combination of the following values :
  *     @arg FLASH_FLAG_EOP_BANK2      : End Of Program on Bank 2 flag
  *     @arg FLASH_FLAG_WRPERR_BANK2   : Write Protection Error on Bank 2 flag
  *     @arg FLASH_FLAG_PGSERR_BANK2   : Program Sequence Error on Bank 2 flag
  *     @arg FLASH_FLAG_STRBER_BANK2   : Program Alignment Error on Bank 2 flag
  *     @arg FLASH_FLAG_INCERR_BANK2   : Inconsistency Error on Bank 2 flag
  *     @arg FLASH_FLAG_OPERR_BANK2    : Operation Error on Bank 2 flag
  *     @arg FLASH_FLAG_RDPERR_BANK2   : Read Protection Error on Bank 2 flag
  *     @arg FLASH_FLAG_RDSERR_BANK2   : Read secure  Error on Bank 2 flag 
  *     @arg FLASH_FLAG_SNECCE_BANK2   : Single ECC Error Correction on Bank 2 flag
  *     @arg FLASH_FLAG_DBECCE_BANK2   : Double Detection ECC Error on Bank 2 flag
  *     @arg FLASH_FLAG_CRCEND_BANK2   : CRC End on Bank 2 flag
  * @retval none
  */

#define __HAL_FLASH_CLEAR_FLAG_BANK1(__FLAG__)    WRITE_REG(FLASH->CCR1, (__FLAG__))

#define __HAL_FLASH_CLEAR_FLAG_BANK2(__FLAG__)    WRITE_REG(FLASH->CCR2, ((__FLAG__) & 0x7FFFFFFF))

#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)         (IS_FLASH_FLAG_BANK1(__FLAG__) ?  __HAL_FLASH_CLEAR_FLAG_BANK1(__FLAG__) : \
                                                   __HAL_FLASH_CLEAR_FLAG_BANK2(__FLAG__)) 

/**
  * @}
  */

/* Include FLASH HAL Extension module */
#include "stm32h7xx_hal_flash_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */
/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
  */
/* Program operation functions  ***********************************************/
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t DataAddress);
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t DataAddress);
/* FLASH IRQ handler method */
void HAL_FLASH_IRQHandler(void);
/* Callbacks in non blocking modes */ 
void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);
/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions  **********************************************/
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void);
/* Option bytes control */
HAL_StatusTypeDef HAL_FLASH_OB_Launch(void);
/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group3
  * @{
  */
/* Peripheral State functions  ************************************************/
uint32_t HAL_FLASH_GetError(void);
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout, uint32_t Bank);
HAL_StatusTypeDef FLASH_OB_WaitForLastOperation(uint32_t Timeout);
/**
  * @}
  */

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup FLASH_Private_Variables FLASH Private Variables
  * @{
  */

/**
  * @}
  */
/* Private constants ---------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
  * @{
  */

/** @defgroup FLASH_IS_FLASH_Definitions FLASH Definitions
  * @{
  */
#define IS_FLASH_TYPEPROGRAM(VALUE) ((VALUE) == FLASH_TYPEPROGRAM_FLASHWORD)
/**
  * @}
  */
/** @defgroup FLASH_IS_BANK_IT_Definitions FLASH BANK IT Definitions
  * @{
  */
  
#define IS_FLASH_IT_BANK1(IT)               (((IT) & FLASH_IT_ALL_BANK1) == (IT))

#define IS_FLASH_IT_BANK2(IT)               (((IT) & FLASH_IT_ALL_BANK2) == (IT))

/**
  * @}
  */

#define IS_FLASH_FLAG_BANK1(FLAG)          (((FLAG) & FLASH_FLAG_ALL_BANK1) == (FLAG))

#define IS_FLASH_FLAG_BANK2(FLAG)          (((FLAG) & FLASH_FLAG_ALL_BANK2) == (FLAG))

/** @defgroup FLASH_Address FLASH Address
  * @{
  */

#define IS_FLASH_PROGRAM_ADDRESS_BANK1(ADDRESS) (((ADDRESS) >= FLASH_BANK1_BASE) && ((ADDRESS) < (FLASH_BANK1_BASE + FLASH_BANK_SIZE) ))
#define IS_FLASH_PROGRAM_ADDRESS_BANK2(ADDRESS) (((ADDRESS) >= FLASH_BANK2_BASE ) && ((ADDRESS) < (FLASH_BANK2_BASE + FLASH_BANK_SIZE) ))
#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS)  (IS_FLASH_PROGRAM_ADDRESS_BANK1(ADDRESS) || IS_FLASH_PROGRAM_ADDRESS_BANK2(ADDRESS))

#define IS_BOOT_ADDRESS(ADDRESS)           ((ADDRESS) <= (0x3FFF0000U))

#define IS_FLASH_BANK(BANK)                (((BANK) == FLASH_BANK_1)  || \
                                            ((BANK) == FLASH_BANK_2)  || \
                                            ((BANK) == FLASH_BANK_BOTH))

#define IS_FLASH_BANK_EXCLUSIVE(BANK)      (((BANK) == FLASH_BANK_1)  || \
                                            ((BANK) == FLASH_BANK_2))

/**
  * @}
  */
  
/**
  * @}
  */ 
/* Private functions ---------------------------------------------------------*/
/** @defgroup FLASH_Private_Functions FLASH Private functions
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32H7xx_HAL_FLASH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
