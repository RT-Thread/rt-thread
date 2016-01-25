/**
  ******************************************************************************
  * @file    n25q512a.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    28-April-2015
  * @brief   This file contains all the description of the N25Q512A QSPI memory.
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
#ifndef __N25Q512A_H
#define __N25Q512A_H

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
  
/** @addtogroup n25q512a
  * @{
  */

/** @defgroup N25Q512A_Exported_Types
  * @{
  */
   
/**
  * @}
  */ 

/** @defgroup N25Q512A_Exported_Constants
  * @{
  */
   
/** 
  * @brief  N25Q512A Configuration  
  */  
#define N25Q512A_FLASH_SIZE                  0x4000000 /* 512 MBits => 64MBytes */
#define N25Q512A_SECTOR_SIZE                 0x10000   /* 1024 sectors of 64KBytes */
#define N25Q512A_SUBSECTOR_SIZE              0x1000    /* 16384 subsectors of 4kBytes */
#define N25Q512A_PAGE_SIZE                   0x100     /* 262144 pages of 256 bytes */

#define N25Q512A_DUMMY_CYCLES_READ           8
#define N25Q512A_DUMMY_CYCLES_READ_QUAD      10
#define N25Q512A_DUMMY_CYCLES_READ_DTR       6
#define N25Q512A_DUMMY_CYCLES_READ_QUAD_DTR  8

#define N25Q512A_BULK_ERASE_MAX_TIME         480000
#define N25Q512A_SECTOR_ERASE_MAX_TIME       3000
#define N25Q512A_SUBSECTOR_ERASE_MAX_TIME    800

/** 
  * @brief  N25Q512A Commands  
  */  
/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99

/* Identification Operations */
#define READ_ID_CMD                          0x9E
#define READ_ID_CMD2                         0x9F
#define MULTIPLE_IO_READ_ID_CMD              0xAF
#define READ_SERIAL_FLASH_DISCO_PARAM_CMD    0x5A

/* Read Operations */
#define READ_CMD                             0x03
#define READ_4_BYTE_ADDR_CMD                 0x13

#define FAST_READ_CMD                        0x0B
#define FAST_READ_DTR_CMD                    0x0D
#define FAST_READ_4_BYTE_ADDR_CMD            0x0C

#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_OUT_FAST_READ_DTR_CMD           0x3D
#define DUAL_OUT_FAST_READ_4_BYTE_ADDR_CMD   0x3C

#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define DUAL_INOUT_FAST_READ_DTR_CMD         0xBD
#define DUAL_INOUT_FAST_READ_4_BYTE_ADDR_CMD 0xBC

#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_OUT_FAST_READ_DTR_CMD           0x6D
#define QUAD_OUT_FAST_READ_4_BYTE_ADDR_CMD   0x6C

#define QUAD_INOUT_FAST_READ_CMD             0xEB
#define QUAD_INOUT_FAST_READ_DTR_CMD         0xED
#define QUAD_INOUT_FAST_READ_4_BYTE_ADDR_CMD 0xEC

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Register Operations */
#define READ_STATUS_REG_CMD                  0x05
#define WRITE_STATUS_REG_CMD                 0x01

#define READ_LOCK_REG_CMD                    0xE8
#define WRITE_LOCK_REG_CMD                   0xE5

#define READ_FLAG_STATUS_REG_CMD             0x70
#define CLEAR_FLAG_STATUS_REG_CMD            0x50

#define READ_NONVOL_CFG_REG_CMD              0xB5
#define WRITE_NONVOL_CFG_REG_CMD             0xB1

#define READ_VOL_CFG_REG_CMD                 0x85
#define WRITE_VOL_CFG_REG_CMD                0x81

#define READ_ENHANCED_VOL_CFG_REG_CMD        0x65
#define WRITE_ENHANCED_VOL_CFG_REG_CMD       0x61

#define READ_EXT_ADDR_REG_CMD                0xC8
#define WRITE_EXT_ADDR_REG_CMD               0xC5

/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define PAGE_PROG_4_BYTE_ADDR_CMD            0x12

#define DUAL_IN_FAST_PROG_CMD                0xA2
#define EXT_DUAL_IN_FAST_PROG_CMD            0xD2

#define QUAD_IN_FAST_PROG_CMD                0x32
#define EXT_QUAD_IN_FAST_PROG_CMD            0x12 /*0x38*/
#define QUAD_IN_FAST_PROG_4_BYTE_ADDR_CMD    0x34

/* Erase Operations */
#define SUBSECTOR_ERASE_CMD                  0x20
#define SUBSECTOR_ERASE_4_BYTE_ADDR_CMD      0x21

#define SECTOR_ERASE_CMD                     0xD8
#define SECTOR_ERASE_4_BYTE_ADDR_CMD         0xDC

#define BULK_ERASE_CMD                       0xC7

#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75

/* One-Time Programmable Operations */
#define READ_OTP_ARRAY_CMD                   0x4B
#define PROG_OTP_ARRAY_CMD                   0x42

/* 4-byte Address Mode Operations */
#define ENTER_4_BYTE_ADDR_MODE_CMD           0xB7
#define EXIT_4_BYTE_ADDR_MODE_CMD            0xE9

/* Quad Operations */
#define ENTER_QUAD_CMD                       0x35
#define EXIT_QUAD_CMD                        0xF5
   
/** 
  * @brief  N25Q512A Registers  
  */ 
/* Status Register */
#define N25Q512A_SR_WIP                      ((uint8_t)0x01)    /*!< Write in progress */
#define N25Q512A_SR_WREN                     ((uint8_t)0x02)    /*!< Write enable latch */
#define N25Q512A_SR_BLOCKPR                  ((uint8_t)0x5C)    /*!< Block protected against program and erase operations */
#define N25Q512A_SR_PRBOTTOM                 ((uint8_t)0x20)    /*!< Protected memory area defined by BLOCKPR starts from top or bottom */
#define N25Q512A_SR_SRWREN                   ((uint8_t)0x80)    /*!< Status register write enable/disable */

/* Non volatile Configuration Register */
#define N25Q512A_NVCR_NBADDR                 ((uint16_t)0x0001) /*!< 3-bytes or 4-bytes addressing */
#define N25Q512A_NVCR_SEGMENT                ((uint16_t)0x0002) /*!< Upper or lower 128Mb segment selected by default */
#define N25Q512A_NVCR_DUAL                   ((uint16_t)0x0004) /*!< Dual I/O protocol */
#define N25Q512A_NVCR_QUAB                   ((uint16_t)0x0008) /*!< Quad I/O protocol */
#define N25Q512A_NVCR_RH                     ((uint16_t)0x0010) /*!< Reset/hold */
#define N25Q512A_NVCR_ODS                    ((uint16_t)0x01C0) /*!< Output driver strength */
#define N25Q512A_NVCR_XIP                    ((uint16_t)0x0E00) /*!< XIP mode at power-on reset */
#define N25Q512A_NVCR_NB_DUMMY               ((uint16_t)0xF000) /*!< Number of dummy clock cycles */

/* Volatile Configuration Register */
#define N25Q512A_VCR_WRAP                    ((uint8_t)0x03)    /*!< Wrap */
#define N25Q512A_VCR_XIP                     ((uint8_t)0x08)    /*!< XIP */
#define N25Q512A_VCR_NB_DUMMY                ((uint8_t)0xF0)    /*!< Number of dummy clock cycles */

/* Extended Address Register */
#define N25Q512A_EAR_A24                     ((uint8_t)0x01)    /*!< Select the lower or upper 128Mb segment */

/* Enhanced Volatile Configuration Register */
#define N25Q512A_EVCR_ODS                    ((uint8_t)0x07)    /*!< Output driver strength */
#define N25Q512A_EVCR_VPPA                   ((uint8_t)0x08)    /*!< Vpp accelerator */
#define N25Q512A_EVCR_RH                     ((uint8_t)0x10)    /*!< Reset/hold */
#define N25Q512A_EVCR_DUAL                   ((uint8_t)0x40)    /*!< Dual I/O protocol */
#define N25Q512A_EVCR_QUAD                   ((uint8_t)0x80)    /*!< Quad I/O protocol */

/* Flag Status Register */
#define N25Q512A_FSR_NBADDR                  ((uint8_t)0x01)    /*!< 3-bytes or 4-bytes addressing */
#define N25Q512A_FSR_PRERR                   ((uint8_t)0x02)    /*!< Protection error */
#define N25Q512A_FSR_PGSUS                   ((uint8_t)0x04)    /*!< Program operation suspended */
#define N25Q512A_FSR_VPPERR                  ((uint8_t)0x08)    /*!< Invalid voltage during program or erase */
#define N25Q512A_FSR_PGERR                   ((uint8_t)0x10)    /*!< Program error */
#define N25Q512A_FSR_ERERR                   ((uint8_t)0x20)    /*!< Erase error */
#define N25Q512A_FSR_ERSUS                   ((uint8_t)0x40)    /*!< Erase operation suspended */
#define N25Q512A_FSR_READY                   ((uint8_t)0x80)    /*!< Ready or command in progress */

/**
  * @}
  */
  
/** @defgroup N25Q512A_Exported_Functions
  * @{
  */ 
/**
  * @}
  */ 
      
#ifdef __cplusplus
}
#endif

#endif /* __N25Q512A_H */

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
