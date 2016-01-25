/**
  ******************************************************************************
  * @file    s25fl512s.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    03-August-2015
  * @brief   This file contains all the description of the S25FL512S QSPI memory.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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
#ifndef __S25FL512S_H
#define __S25FL512S_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup s25fl512s
  * @brief     This file provides a set of definitions for the Spansion
  *            S25FL512S memory (configuration, commands, registers).
  * @{
  */

/** @defgroup S25FL512S_Exported_Types
  * @{
  */
   
/**
  * @}
  */ 

/** @defgroup S25FL512S_Exported_Constants
  * @{
  */
   
/* S25FL512SAGMFI01 Spansion Memory */
/**
  * @brief  S25FL512S Configuration
  */
#define S25FL512S_FLASH_SIZE                            0x4000000 /* 512 MBits => 64MBytes */
#define S25FL512S_SECTOR_SIZE                           0x40000   /* 256 sectors of 256KBytes */
#define S25FL512S_PAGE_SIZE                             0x200     /* 131072 pages of 512 bytes */

#define S25FL512S_BULK_ERASE_MAX_TIME                   460000
#define S25FL512S_SECTOR_ERASE_MAX_TIME                 2600


/**
  * @brief  S25FL512S Commands
  */
/* Reset Operations */
#define S25FL512S_SOFTWARE_RESET_CMD                    0xF0
#define S25FL512S_MODE_BIT_RESET_CMD                    0xFF

/* Identification Operations */
#define S25FL512S_READ_ID_CMD                           0x90
#define S25FL512S_READ_ID_CMD2                          0x9F
#define S25FL512S_READ_ELECTRONIC_SIGNATURE             0xAB
#define S25FL512S_READ_SERIAL_FLASH_DISCO_PARAM_CMD     0x5A

/* Register Operations */
#define S25FL512S_READ_STATUS_REG1_CMD                  0x05
#define S25FL512S_READ_STATUS_REG2_CMD                  0x07
#define S25FL512S_READ_CONFIGURATION_REG1_CMD           0x35
#define S25FL512S_WRITE_STATUS_CMD_REG_CMD              0x01
#define S25FL512S_WRITE_DISABLE_CMD                     0x04
#define S25FL512S_WRITE_ENABLE_CMD                      0x06
#define S25FL512S_CLEAR_STATUS_REG1_CMD                 0x30
#define S25FL512S_READ_AUTOBOOT_REG_CMD                 0x14
#define S25FL512S_WRITE_AUTOBOOT_REG_CMD                0x15
#define S25FL512S_READ_BANK_REG_CMD                     0x16
#define S25FL512S_WRITE_BANK_REG_CMD                    0x17
#define S25FL512S_ACCESS_BANK_REG_CMD                   0xB9
#define S25FL512S_READ_DATA_LEARNING_PATTERN_CMD        0x41
#define S25FL512S_PGM_NV_DATA_LEARNING_REG_CMD          0x43
#define S25FL512S_WRITE_VOL_DATA_LEARNING_REG_CMD       0x4A

/* Read Operations */
#define S25FL512S_READ_CMD                              0x03
#define S25FL512S_READ_4_BYTE_ADDR_CMD                  0x13

#define S25FL512S_FAST_READ_CMD                         0x0B
#define S25FL512S_FAST_READ_4_BYTE_ADDR_CMD             0x0C
#define S25FL512S_FAST_READ_DDR_CMD                     0x0D
#define S25FL512S_FAST_READ__DDR_4_BYTE_ADDR_CMD        0x0E

#define S25FL512S_DUAL_OUT_FAST_READ_CMD                0x3B
#define S25FL512S_DUAL_OUT_FAST_READ_4_BYTE_ADDR_CMD    0x3C

#define S25FL512S_QUAD_OUT_FAST_READ_CMD                0x6B
#define S25FL512S_QUAD_OUT_FAST_READ_4_BYTE_ADDR_CMD    0x6C

#define S25FL512S_DUAL_INOUT_FAST_READ_CMD              0xBB
#define S25FL512S_DUAL_INOUT_FAST_READ_DTR_CMD          0xBD
#define S25FL512S_DUAL_INOUT_FAST_READ_4_BYTE_ADDR_CMD  0xBC
#define S25FL512S_DDR_DUAL_INOUT_READ_4_BYTE_ADDR_CMD   0xBE

#define S25FL512S_QUAD_INOUT_FAST_READ_CMD              0xEB
#define S25FL512S_QUAD_INOUT_FAST_READ_4_BYTE_ADDR_CMD  0xEC
#define S25FL512S_QUAD_INOUT_FAST_READ_DDR_CMD          0xED
#define S25FL512S_QUAD_INOUT_READ_DDR_4_BYTE_ADDR_CMD   0xEE


/* Program Operations */
#define S25FL512S_PAGE_PROG_CMD                         0x02
#define S25FL512S_PAGE_PROG_4_BYTE_ADDR_CMD             0x12

#define S25FL512S_QUAD_IN_FAST_PROG_CMD                 0x32
#define S25FL512S_QUAD_IN_FAST_PROG_ALTERNATE_CMD       0x38
#define S25FL512S_QUAD_IN_FAST_PROG_4_BYTE_ADDR_CMD     0x34

#define S25FL512S_PROGRAM_SUSPEND_CMD                   0x85
#define S25FL512S_PROGRAM_RESUME_CMD                    0x8A

/* Erase Operations */
#define S25FL512S_SECTOR_ERASE_CMD                      0xD8
#define S25FL512S_SECTOR_ERASE_4_BYTE_ADDR_CMD          0xDC

#define S25FL512S_BULK_ERASE_CMD                        0x60
#define S25FL512S_BULK_ERASE_ALTERNATE_CMD              0xC7

#define S25FL512S_PROG_ERASE_SUSPEND_CMD                0x75
#define S25FL512S_PROG_ERASE_RESUME_CMD                 0x7A

/* One-Time Programmable Operations */
#define S25FL512S_PROG_OTP_ARRAY_CMD                    0x42
#define S25FL512S_READ_OTP_ARRAY_CMD                    0x4B

/* Advanced Sector Protection Operations */
#define S25FL512S_READ_DYB_CMD                          0xE0
#define S25FL512S_WRITE_DYB_CMD                         0xE1

#define S25FL512S_READ_PPB_CMD                          0xE2
#define S25FL512S_PROGRAM_PPB_CMD                       0xE3
#define S25FL512S_ERASE_PPB_CMD                         0xE4

#define S25FL512S_READ_ASP_CMD                          0x2B
#define S25FL512S_PROGRAM_ASP_CMD                       0x2F

#define S25FL512S_READ_PPB_LOCKBIT_CMD                  0xA7
#define S25FL512S_WRITE_PPB_LOCKBIT_CMD                 0xA6

#define S25FL512S_READ_PASSWORD_CMD                     0xE7
#define S25FL512S_PROGRAM_PASSWORD_CMD                  0xE8
#define S25FL512S_UNLOCK_PASSWORD_CMD                   0xE9



/**
  * @brief  S25FL512S Registers
  */
/* Status Register-1 */
#define S25FL512S_SR1_WIP                               ((uint8_t)0x01)      /*!< Write in progress, device busy */
#define S25FL512S_SR1_WREN                              ((uint8_t)0x02)      /*!< Write Registers, program or commands are accepted */
#define S25FL512S_SR1_BP0                               ((uint8_t)0x04)      /*!< Sector0 protected from Program or Erase */
#define S25FL512S_SR1_BP1                               ((uint8_t)0x08)      /*!< Sector1 protected from Program or Erase */
#define S25FL512S_SR1_BP2                               ((uint8_t)0x10)      /*!< Sector2 protected from Program or Erase */
#define S25FL512S_SR1_ERERR                             ((uint8_t)0x20)      /*!< Erase error */
#define S25FL512S_SR1_PGERR                             ((uint8_t)0x40)      /*!< Program error */
#define S25FL512S_SR1_SRWD                              ((uint8_t)0x80)      /*!< Status Register Write Disable */

/* Status Register-2 */
#define S25FL512S_SR2_PS                                ((uint8_t)0x01)      /*!< Program in Suspend mode */
#define S25FL512S_SR2_ES                                ((uint8_t)0x02)      /*!< Erase Suspend Mode */

/* Configuration Register CR1 */
#define S25FL512S_CR1_FREEZE                            ((uint8_t)0x01)      /*!< Block protection and OTP locked */
#define S25FL512S_CR1_QUAD                              ((uint8_t)0x02)      /*!< Quad mode enable */
#define S25FL512S_CR1_BPNV                              ((uint8_t)0x08)      /*!< BP2-0 bits of Status Reg are volatile */
#define S25FL512S_CR1_TBPROT                            ((uint8_t)0x20)      /*!< BPstarts at bottom */
#define S25FL512S_CR1_LC_MASK                           ((uint8_t)0xC0)      /*!< Latency Code mask */
#define S25FL512S_CR1_LC0                               ((uint8_t)0x00)      /*!< Latency Code = 0 */
#define S25FL512S_CR1_LC1                               ((uint8_t)0x40)      /*!< Latency Code = 1 */
#define S25FL512S_CR1_LC2                               ((uint8_t)0x80)      /*!< Latency Code = 2 */
#define S25FL512S_CR1_LC3                               ((uint8_t)0xC0)      /*!< Latency Code = 3 */

/* AutoBoot Register */
#define S25FL512S_AB_EN                                 ((uint32_t)0x00000001) /*!< AutoBoot Enabled     */
#define S25FL512S_AB_SD_MASK                            ((uint32_t)0x000001FE) /*!< AutoBoot Start Delay mask */
#define S25FL512S_AB_SA_MASK                            ((uint32_t)0xFFFFFE00) /*!< AutoBoot Start Address mask */

/* Bank Address Register */
#define S25FL512S_BA_BA24                               ((uint8_t)0x01)      /*!< A24 for 512 Mb device */
#define S25FL512S_BA_BA25                               ((uint8_t)0x02)      /*!< A25 for 512 Mb device */
#define S25FL512S_BA_EXTADD                             ((uint8_t)0x80)      /*!< 4 bytes addressing required from command */

/* ASP Register */
#define S25FL512S_ASP_PSTMLB                            ((uint16_t)0x0002)   /*!< Persistent protection mode not permanently enabled */
#define S25FL512S_ASP_PWSMLB                            ((uint16_t)0x0003)   /*!< Password protection mode not permanently enabled */

/* PPB Lock Register */
#define S25FL512S_PPBLOCK                               ((uint8_t)0x01)      /*!< PPB array may be programmed or erased */

/**
  * @}
  */
  
/** @defgroup S25FL512S_Exported_Functions
  * @{
  */ 
/**
  * @}
  */ 
      
#ifdef __cplusplus
}
#endif

#endif /* __S25FL512S_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
