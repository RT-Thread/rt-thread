/**
  ******************************************************************************
  * @file    bl616_psram.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2022 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
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
#ifndef __BL616_PSRAM_CTRL_H__
#define __BL616_PSRAM_CTRL_H__

#include "psram_reg.h"
#include "bl616_common.h"

/** @addtogroup  BL616_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PSRAM_CTRL
 *  @{
 */

/** @defgroup  PSRAM_CTRL_Public_Types
 *  @{
 */

/**
 *  @brief PSRAM ID
 */
typedef enum {
    PSRAM0_ID, /*!< PSRAM0 identifier */
} PSRAM_ID_Type;

/**
 *  @brief PSRAM Ctrl IO mode type definition
 */
typedef enum {
    PSRAM_CTRL_X8_MODE,  /*!< PSRAM X8 mode */
    PSRAM_CTRL_X16_MODE, /*!< PSRAM X16 mode */
} PSRAM_Ctrl_Io_Mode_Type;

/**
 *  @brief PSRAM Ctrl  PSRAM vendor type definition
 */
typedef enum {
    PSRAM_CTRL_VENDOR_WINBOND = 0x1,           /*!< Winbond psram */
    PSRAM_CTRL_VENDOR_APMEM_EXCLUDE_4MB = 0x2, /*!< AP memory psram exclude 4MB size */
    PSRAM_CTRL_VENDOR_APMEM_4MB = 0x4,         /*!< AP memory psram 4MB size */
} PSRAM_Ctrl_Vendor_Type;

/**
 *  @brief PSRAM SIZE
 */
typedef enum {
    PSRAM_SIZE_4MB = 0x3,   /*!< PSRAM size is 4MB */
    PSRAM_SIZE_8MB = 0x7,   /*!< PSRAM size is 8MB */
    PSRAM_SIZE_16MB = 0xf,  /*!< PSRAM size is 16MB */
    PSRAM_SIZE_32MB = 0x1f, /*!< PSRAM size is 32MB */
} PSRAM_Ctrl_Size_Type;

/**
 *  @brief Winbond PSRAM configuration register type definition
 */
typedef enum {
    PSRAM_WINBOND_REG_ID0, /*!< Winbond register ID0 */
    PSRAM_WINBOND_REG_ID1, /*!< Winbond register ID1 */
    PSRAM_WINBOND_REG_CR0, /*!< Winbond register CR0 */
    PSRAM_WINBOND_REG_CR1, /*!< Winbond register CR1 */
    PSRAM_WINBOND_REG_CR2, /*!< Winbond register CR2 */
    PSRAM_WINBOND_REG_CR3, /*!< Winbond register CR3 */
    PSRAM_WINBOND_REG_CR4, /*!< Winbond register CR4 */
} PSRAM_Ctrl_Winbond_Cfg_Reg_Type;

/**
 *  @brief APMemory PSRAM configuration register type definition
 */
typedef enum {
    PSRAM_APMEM_REG_0 = 0, /*!< APMemory register 0 */
    PSRAM_APMEM_REG_1,     /*!< APMemory register 1 */
    PSRAM_APMEM_REG_2,     /*!< APMemory register 2 */
    PSRAM_APMEM_REG_3,     /*!< APMemory register 3 */
    PSRAM_APMEM_REG_4,     /*!< APMemory register 4 */
    PSRAM_APMEM_REG_5,     /*!< APMemory register 5 */
    PSRAM_APMEM_REG_6,     /*!< APMemory register 6 */
    PSRAM_APMEM_REG_8,     /*!< APMemory register 8 */
} PSRAM_Ctrl_ApMem_Cfg_Reg_Type;

/**
 *  @brief PSRAM Latency Counter type definition
 */
typedef enum {
    PSRAM_WINBOND_5_CLOCKS_LATENCY,        /*!< PSRAM 5 clocks latency 133MHZ */
    PSRAM_WINBOND_6_CLOCKS_LATENCY,        /*!< PSRAM 6 clocks latency 166MHZ */
    PSRAM_WINBOND_7_CLOCKS_LATENCY,        /*!< PSRAM 7 clocks latency 200MHZ */
    PSRAM_WINBOND_3_CLOCKS_LATENCY = 0xE,  /*!< PSRAM 3 clocks latency 83MHZ */
    PSRAM_WINBOND_4_CLOCKS_LATENCY = 0xF,  /*!< PSRAM 4 clocks latency 100MHZ */
    PSRAM_WINBOND_14_CLOCKS_LATENCY = 0x7, /*!< PSRAM 14 clocks latency only for Hyperbus3 400MHZ */
    PSRAM_WINBOND_19_CLOCKS_LATENCY = 0x9, /*!< PSRAM 19 clocks latency only for Hyperbus3 533MHZ */
} PSRAM_Latency_Winbond_Type;

/**
 *  @brief PSRAM Burst Type
 */
typedef enum {
    PSRAM_HYBRID_BURST,  /*!< PSRAM use hybrid brust */
    PSRAM_WRAPPED_BURST, /*!< PSRAM use warpped brust */
} PSRAM_Burst_Type;

/**
 *  @brief PSRAM Latency Counter type definition
 */
typedef enum {
    PSRAM_APMEM_3_CLOCKS_LATENCY,       /*!< PSRAM 3 clocks latency */
    PSRAM_APMEM_4_CLOCKS_LATENCY = 0x4, /*!< PSRAM 4 clocks latency */
    PSRAM_APMEM_5_CLOCKS_LATENCY = 0x2, /*!< PSRAM 5 clocks latency */
    PSRAM_APMEM_6_CLOCKS_LATENCY = 0x6, /*!< PSRAM 6 clocks latency */
    PSRAM_APMEM_7_CLOCKS_LATENCY = 0x1, /*!< PSRAM 7 clocks latency */
} PSRAM_Latency_ApMem_Type;

/**
 *  @brief PSRAM Drive Strength type definition for Winbon 4M
 */
typedef enum {
    PSRAM_WINBOND_DRIVE_STRENGTH_50_OHMS_FOR_4M_34_OHMS_FOR_8M,  /*!< drive strength 50 ohms for 4M size ,34 ohms for 8M size */
    PSRAM_WINBOND_DRIVE_STRENGTH_35_OHMS_FOR_4M_115_OHMS_FOR_8M, /*!< drive strength 35 ohms for 4M size ,115 ohms for 8M size */
    PSRAM_WINBOND_DRIVE_STRENGTH_100_OHMS_FOR_4M_67_OHMS_FOR_8M, /*!< drive strength 100 ohms for 4M size ,67 ohms for 8M size */
    PSRAM_WINBOND_DRIVE_STRENGTH_200_OHMS_FOR_4M_46_OHMS_FOR_8M, /*!< drive strength 200 ohms for 4M size ,46 ohms for 8M size */
    PSRAM_DRIVE_STRENGTH_34_OHMS_ONLY_FOR_8M,                    /*!< drive strength 34 ohms only for 8M size */
    PSRAM_DRIVE_STRENGTH_27_OHMS_ONLY_FOR_8M,                    /*!< drive strength 27 ohms only for 8M size */
    PSRAM_DRIVE_STRENGTH_22_OHMS_ONLY_FOR_8M,                    /*!< drive strength 22 ohms only for 8M size */
    PSRAM_DRIVE_STRENGTH_19_OHMS_ONLY_FOR_8M,                    /*!< drive strength 19 ohms only for 8M size */
} PSRAM_Winbond_Drive_Strength;

/**
 *  @brief PSRAM Drive Strength type definition for Winbon 8MB
 */
typedef enum {
    PSRAM_APMEM_DRIVE_STRENGTH_25_OHMS,  /*!< drive strength 25 ohms */
    PSRAM_APMEM_DRIVE_STRENGTH_50_OHMS,  /*!< drive strength 50 ohms */
    PSRAM_APMEM_DRIVE_STRENGTH_100_OHMS, /*!< drive strength 100 ohms */
    PSRAM_APMEM_DRIVE_STRENGTH_200_OHMS, /*!< drive strength 200 ohms */
} PSRAM_ApMem_Drive_Strength;

/**
 *  @brief PSRAM Burst Length type definition
 */
typedef enum {
    PSRAM_WINBOND_BURST_LENGTH_128_BYTES = 0x4, /*!< Burst Length 128 bytes */
    PSRAM_WINBOND_BURST_LENGTH_64_BYTES,        /*!< Burst Length 64 bytes */
    PSRAM_WINBOND_BURST_LENGTH_16_BYTES,        /*!< Burst Length 16 bytes */
    PSRAM_WINBOND_BURST_LENGTH_32_BYTES,        /*!< Burst Length 32 bytes */
    PSRAM_WINBOND_BURST_LENGTH_512_BYTES,       /*!< Burst Length 512 only for HyperBus3 */
} PSRAM_Winbond_Burst_Length;

/**
 *  @brief PSRAM Burst Length type definition
 */
typedef enum {
    PSRAM_APMEM_BURST_LENGTH_16_BYTES,                   /*!< Burst Length 16 bytes */
    PSRAM_APMEM_BURST_LENGTH_32_BYTES,                   /*!< Burst Length 32 bytes */
    PSRAM_APMEM_BURST_LENGTH_64_BYTES,                   /*!< Burst Length 64 bytes */
    PSRAM_APMEM_BURST_LENGTH_1K_FOR_APS64_2K_FOR_APS256, /*!< Burst Length 1K bytes for APS6408L and 2Kbytes for APS256XXN */
} PSRAM_ApMem_Burst_Length;

/**
 *  @brief PSRAM Fixed Latency Enable type definition
 */
typedef enum {
    PSRAM_VARIALBE_INITIAL_LATENCY,      /*!< 1 or 2 times Initial Latency depending on RWDS during CA cycles */
    PSRAM_FIXED_2_TIMES_INITIAL_LATENCY, /*!< Fixed 2 times Initial Latency (default) */
} PSRAM_Fixed_Latency_Enable;

/**
 *  @brief PSRAM Deep Power Down Enable type definition
 */
typedef enum {
    PSRAM_DPD_ENTER,  /*!< Writing 0 to CR0[15] causes the device to enter Deep Power Down */
    PSRAM_DPD_NORMAL, /*!< Normal operation (default) */
} PSRAM_Deep_Power_Down;

/**
 *  @brief Partial Array Self Refresh definition
 */
typedef enum {
    PSRAM_PARTIAL_REFRESH_FULL,        /*!< PSRAM partial refresh full array (000000h - 1FFFFFh) */
    PSRAM_PARTIAL_REFRESH_BOTTOM_1TO2, /*!< PSRAM partial refresh Bottom 1/2 array (000000h - 0FFFFFh) */
    PSRAM_PARTIAL_REFRESH_BOTTOM_1TO4, /*!< PSRAM partial refresh Bottom 1/4 array (000000h - 07FFFFh) */
    PSRAM_PARTIAL_REFRESH_BOTTOM_1TO8, /*!< PSRAM partial refresh Bottom 1/8 array (000000h - 03FFFFh) */
    PSRAM_PARTIAL_REFRESH_NONE,        /*!< PSRAM partial refresh None */
    PSRAM_PARTIAL_REFRESH_TOP_1TO2,    /*!< PSRAM partial refresh Top 1/2 array (100000h - 1FFFFFh) */
    PSRAM_PARTIAL_REFRESH_TOP_1TO4,    /*!< PSRAM partial refresh Top 1/4 array (180000h - 1FFFFFh) */
    PSRAM_PARTIAL_REFRESH_TOP_1TO8,    /*!< PSRAM partial refresh Top 1/8 array (1C0000h - 1FFFFFh) */
} PSRAM_Partial_Array_Refresh;

/**
 *  @brief PSRAM ApMem self-fresh freq
 */
typedef enum {
    PSRAM_APMEM_FAST_REFRESH, /*!< Fast Refresh (default) */
    PSRAM_APMEM_SLOW_REFRESH, /*!< Enables Slow Refresh when temperature allows */
} PSRAM_ApMem_Refresh_Speed;

/**
 *  @brief PSRAM Hybrid Sleep Mode type definition
 */
typedef enum {
    PSRAM_HYBRID_SLEEP_DISABLE, /*!< not in Hybrid Sleep Mode */
    PSRAM_HYBRID_SLEEP_ENABLE,  /*!< entering Hybrid Sleep Mode */
} PSRAM_Hybrid_Sleep_Mode;

/**
 *  @brief PSRAM Master Clock type definition
 */
typedef enum {
    PSRAM_CLOCK_DIFF,   /*!< PSRAM Master Clock is differential */
    PSRAM_CLOCK_SINGLE, /*!< PSRAM Master Clock is single end */
} PSRAM_Clock_Type;

/**
 *  @brief PSRAM delay chain configuration definition
 */
typedef struct
{
    PSRAM_Ctrl_Vendor_Type vendor;  /*!< PSRAM Vendor */
    PSRAM_Ctrl_Io_Mode_Type ioMode; /*!< PSRAM interface mode */
    PSRAM_Ctrl_Size_Type size;      /*!< PSRAM size */
    uint32_t dqs_delay;             /*!< PSRAM dqs delay value */
} PSRAM_Ctrl_Cfg_Type;

/**
 *  @brief PSRAM Winbon configuration definition
 */
typedef struct
{
    BL_Fun_Type rst;                            /*!< Winbond pSRAM CR1 - Software Reset */
    PSRAM_Clock_Type clockType;                 /*!< Winbond pSRAM CR1 - Master Clock Type */
    BL_Fun_Type inputPowerDownMode;             /*!< Winbond pSRAM CR1 - Input Power Down */
    BL_Fun_Type linear_dis;                     /*!< Winbond pSRAM linear burst disable */
    BL_Fun_Type hybridSleepMode;                /*!< Winbond pSRAM CR1 - Hybrid Sleep Mode configuration */
    PSRAM_Partial_Array_Refresh PASR;           /*!< Winbond pSRAM CR1 - Partial Array Refresh + Distributed Refresh Interval */
    BL_Fun_Type disDeepPowerDownMode;           /*!< Winbond pSRAM CR0 - Deep Power-Down Disable configuration */
    BL_Fun_Type fixedLatency;                   /*!< Winbond pSRAM CR1 - Fix Latency configuration */
    PSRAM_Winbond_Burst_Length brustLen;        /*!< Winbond pSRAM CR0 - Burst Length configuration */
    PSRAM_Burst_Type brustType;                 /*!< Winbond pSRAM CR0 - Hybrid Burst Enable */
    PSRAM_Winbond_Drive_Strength driveStrength; /*!< Winbond pSRAM CR0 - Drive Strength configuration */
    PSRAM_Latency_Winbond_Type latency;         /*!< Winbond pSRAM CR0 - Latency Counter configuration */
} PSRAM_Winbond_Cfg_Type;

/**
 *  @brief PSRAM Winbon configuration definition
 */
typedef struct
{
    BL_Fun_Type rst;                          /*!< AP Memory pSRAM configure global reset enable */
    BL_Fun_Type fixedLatency;                 /*!< AP Memory pSRAM configure MR0 - read latency type */
    PSRAM_Latency_ApMem_Type readLatency;     /*!< AP Memory pSRAM configure MR0 - read latency code */
    PSRAM_ApMem_Refresh_Speed refreshFreq;    /*!< AP Memory pSRAM configure MR4 - refresh frequency */
    PSRAM_ApMem_Drive_Strength driveStrength; /*!< AP Memory pSRAM configure MR0 - drive strength */
    PSRAM_Latency_ApMem_Type writeLatency;    /*!< AP Memory pSRAM configure MR4 - write latency code */
    PSRAM_Partial_Array_Refresh PASR;         /*!< AP Memory pSRAM configure MR4 - partial array refresh */
    BL_Fun_Type halfSleepModeEnable;          /*!< AP Memory pSRAM configure MR6 - Half Sleep enable */
    BL_Fun_Type deepPowerDownModeEnable;      /*!< AP Memory pSRAM configure MR6 - Deep Power Down enable */
    BL_Fun_Type crossBoundaryEnable;          /*!< AP Memory pSRAM configure MR8 - cross boundary enable 1'b0 - Read within 1K boundary 1'b1 -
                                                 Read cross 1K boundary */
    PSRAM_Burst_Type brustType;               /*!< AP Memory pSRAM configure MR8 - burst type */
    PSRAM_ApMem_Burst_Length brustLen;        /*!< AP Memory pSRAM configure MR8 - burst length */
} PSRAM_APMemory_Cfg_Type;

/*@} end of group PSRAM_CTRL_Public_Types */

/** @defgroup  PSRAM_CTRL_Public_Constants
 *  @{
 */

/** @defgroup  PSRAM_ID_TYPE
 *  @{
 */
#define IS_PSRAM_ID_TYPE(type) (((type) == PSRAM0_ID))

/** @defgroup  PSRAM_CTRL_IO_MODE_TYPE
 *  @{
 */
#define IS_PSRAM_CTRL_IO_MODE_TYPE(type) (((type) == PSRAM_CTRL_X8_MODE) || \
                                          ((type) == PSRAM_CTRL_X16_MODE))

/** @defgroup  PSRAM_CTRL_VENDOR_TYPE
 *  @{
 */
#define IS_PSRAM_CTRL_VENDOR_TYPE(type) (((type) == PSRAM_CTRL_VENDOR_WINBOND) ||           \
                                         ((type) == PSRAM_CTRL_VENDOR_APMEM_EXCLUDE_4MB) || \
                                         ((type) == PSRAM_CTRL_VENDOR_APMEM_4MB))

/** @defgroup  PSRAM_CTRL_SIZE_TYPE
 *  @{
 */
#define IS_PSRAM_CTRL_SIZE_TYPE(type) (((type) == PSRAM_SIZE_4MB) ||  \
                                       ((type) == PSRAM_SIZE_8MB) ||  \
                                       ((type) == PSRAM_SIZE_16MB) || \
                                       ((type) == PSRAM_SIZE_32MB))

/** @defgroup  PSRAM_CTRL_WINBOND_CFG_REG_TYPE
 *  @{
 */
#define IS_PSRAM_CTRL_WINBOND_CFG_REG_TYPE(type) (((type) == PSRAM_WINBOND_REG_ID0) || \
                                                  ((type) == PSRAM_WINBOND_REG_ID1) || \
                                                  ((type) == PSRAM_WINBOND_REG_CR0) || \
                                                  ((type) == PSRAM_WINBOND_REG_CR1) || \
                                                  ((type) == PSRAM_WINBOND_REG_CR2) || \
                                                  ((type) == PSRAM_WINBOND_REG_CR3) || \
                                                  ((type) == PSRAM_WINBOND_REG_CR4))

/** @defgroup  PSRAM_CTRL_APMEM_CFG_REG_TYPE
 *  @{
 */
#define IS_PSRAM_CTRL_APMEM_CFG_REG_TYPE(type) (((type) == PSRAM_APMEM_REG_0) || \
                                                ((type) == PSRAM_APMEM_REG_1) || \
                                                ((type) == PSRAM_APMEM_REG_2) || \
                                                ((type) == PSRAM_APMEM_REG_3) || \
                                                ((type) == PSRAM_APMEM_REG_4) || \
                                                ((type) == PSRAM_APMEM_REG_5) || \
                                                ((type) == PSRAM_APMEM_REG_6) || \
                                                ((type) == PSRAM_APMEM_REG_8))

/** @defgroup  PSRAM_LATENCY_WINBOND_TYPE
 *  @{
 */
#define IS_PSRAM_LATENCY_WINBOND_TYPE(type) (((type) == PSRAM_WINBOND_5_CLOCKS_LATENCY) ||  \
                                             ((type) == PSRAM_WINBOND_6_CLOCKS_LATENCY) ||  \
                                             ((type) == PSRAM_WINBOND_7_CLOCKS_LATENCY) ||  \
                                             ((type) == PSRAM_WINBOND_3_CLOCKS_LATENCY) ||  \
                                             ((type) == PSRAM_WINBOND_4_CLOCKS_LATENCY) ||  \
                                             ((type) == PSRAM_WINBOND_14_CLOCKS_LATENCY) || \
                                             ((type) == PSRAM_WINBOND_19_CLOCKS_LATENCY))

/** @defgroup  PSRAM_BURST_TYPE
 *  @{
 */
#define IS_PSRAM_BURST_TYPE(type) (((type) == PSRAM_HYBRID_BURST) || \
                                   ((type) == PSRAM_WRAPPED_BURST))

/** @defgroup  PSRAM_LATENCY_APMEM_TYPE
 *  @{
 */
#define IS_PSRAM_LATENCY_APMEM_TYPE(type) (((type) == PSRAM_APMEM_3_CLOCKS_LATENCY) || \
                                           ((type) == PSRAM_APMEM_4_CLOCKS_LATENCY) || \
                                           ((type) == PSRAM_APMEM_5_CLOCKS_LATENCY) || \
                                           ((type) == PSRAM_APMEM_6_CLOCKS_LATENCY) || \
                                           ((type) == PSRAM_APMEM_7_CLOCKS_LATENCY))

/** @defgroup  PSRAM_WINBOND_DRIVE_STRENGTH
 *  @{
 */
#define IS_PSRAM_WINBOND_DRIVE_STRENGTH(type) (((type) == PSRAM_WINBOND_DRIVE_STRENGTH_50_OHMS_FOR_4M_34_OHMS_FOR_8M) ||  \
                                               ((type) == PSRAM_WINBOND_DRIVE_STRENGTH_35_OHMS_FOR_4M_115_OHMS_FOR_8M) || \
                                               ((type) == PSRAM_WINBOND_DRIVE_STRENGTH_100_OHMS_FOR_4M_67_OHMS_FOR_8M) || \
                                               ((type) == PSRAM_WINBOND_DRIVE_STRENGTH_200_OHMS_FOR_4M_46_OHMS_FOR_8M) || \
                                               ((type) == PSRAM_DRIVE_STRENGTH_34_OHMS_ONLY_FOR_8M) ||                    \
                                               ((type) == PSRAM_DRIVE_STRENGTH_27_OHMS_ONLY_FOR_8M) ||                    \
                                               ((type) == PSRAM_DRIVE_STRENGTH_22_OHMS_ONLY_FOR_8M) ||                    \
                                               ((type) == PSRAM_DRIVE_STRENGTH_19_OHMS_ONLY_FOR_8M))

/** @defgroup  PSRAM_APMEM_DRIVE_STRENGTH
 *  @{
 */
#define IS_PSRAM_APMEM_DRIVE_STRENGTH(type) (((type) == PSRAM_APMEM_DRIVE_STRENGTH_25_OHMS) ||  \
                                             ((type) == PSRAM_APMEM_DRIVE_STRENGTH_50_OHMS) ||  \
                                             ((type) == PSRAM_APMEM_DRIVE_STRENGTH_100_OHMS) || \
                                             ((type) == PSRAM_APMEM_DRIVE_STRENGTH_200_OHMS))

/** @defgroup  PSRAM_WINBOND_BURST_LENGTH
 *  @{
 */
#define IS_PSRAM_WINBOND_BURST_LENGTH(type) (((type) == PSRAM_WINBOND_BURST_LENGTH_128_BYTES) || \
                                             ((type) == PSRAM_WINBOND_BURST_LENGTH_64_BYTES) ||  \
                                             ((type) == PSRAM_WINBOND_BURST_LENGTH_16_BYTES) ||  \
                                             ((type) == PSRAM_WINBOND_BURST_LENGTH_32_BYTES) ||  \
                                             ((type) == PSRAM_WINBOND_BURST_LENGTH_512_BYTES))

/** @defgroup  PSRAM_APMEM_BURST_LENGTH
 *  @{
 */
#define IS_PSRAM_APMEM_BURST_LENGTH(type) (((type) == PSRAM_APMEM_BURST_LENGTH_16_BYTES) || \
                                           ((type) == PSRAM_APMEM_BURST_LENGTH_32_BYTES) || \
                                           ((type) == PSRAM_APMEM_BURST_LENGTH_64_BYTES) || \
                                           ((type) == PSRAM_APMEM_BURST_LENGTH_1K_FOR_APS64_2K_FOR_APS256))

/** @defgroup  PSRAM_FIXED_LATENCY_ENABLE
 *  @{
 */
#define IS_PSRAM_FIXED_LATENCY_ENABLE(type) (((type) == PSRAM_VARIALBE_INITIAL_LATENCY) || \
                                             ((type) == PSRAM_FIXED_2_TIMES_INITIAL_LATENCY))

/** @defgroup  PSRAM_DEEP_POWER_DOWN
 *  @{
 */
#define IS_PSRAM_DEEP_POWER_DOWN(type) (((type) == PSRAM_DPD_ENTER) || \
                                        ((type) == PSRAM_DPD_NORMAL))

/** @defgroup  PSRAM_PARTIAL_ARRAY_REFRESH
 *  @{
 */
#define IS_PSRAM_PARTIAL_ARRAY_REFRESH(type) (((type) == PSRAM_PARTIAL_REFRESH_FULL) ||        \
                                              ((type) == PSRAM_PARTIAL_REFRESH_BOTTOM_1TO2) || \
                                              ((type) == PSRAM_PARTIAL_REFRESH_BOTTOM_1TO4) || \
                                              ((type) == PSRAM_PARTIAL_REFRESH_BOTTOM_1TO8) || \
                                              ((type) == PSRAM_PARTIAL_REFRESH_NONE) ||        \
                                              ((type) == PSRAM_PARTIAL_REFRESH_TOP_1TO2) ||    \
                                              ((type) == PSRAM_PARTIAL_REFRESH_TOP_1TO4) ||    \
                                              ((type) == PSRAM_PARTIAL_REFRESH_TOP_1TO8))

/** @defgroup  PSRAM_APMEM_REFRESH_SPEED
 *  @{
 */
#define IS_PSRAM_APMEM_REFRESH_SPEED(type) (((type) == PSRAM_APMEM_FAST_REFRESH) || \
                                            ((type) == PSRAM_APMEM_SLOW_REFRESH))

/** @defgroup  PSRAM_HYBRID_SLEEP_MODE
 *  @{
 */
#define IS_PSRAM_HYBRID_SLEEP_MODE(type) (((type) == PSRAM_HYBRID_SLEEP_DISABLE) || \
                                          ((type) == PSRAM_HYBRID_SLEEP_ENABLE))

/** @defgroup  PSRAM_CLOCK_TYPE
 *  @{
 */
#define IS_PSRAM_CLOCK_TYPE(type) (((type) == PSRAM_CLOCK_DIFF) || \
                                   ((type) == PSRAM_CLOCK_SINGLE))

/*@} end of group PSRAM_CTRL_Public_Constants */

/** @defgroup  PSRAM_CTRL_Public_Macros
 *  @{
 */

/*@} end of group PSRAM_CTRL_Public_Macros */

/** @defgroup  PSRAM_CTRL_Public_Functions
 *  @{
 */
void PSram_Ctrl_Init(PSRAM_ID_Type PSRAM_ID, PSRAM_Ctrl_Cfg_Type *psramCtrlCfg);
BL_Err_Type PSram_Ctrl_Winbond_Read_Reg(PSRAM_ID_Type PSRAM_ID, PSRAM_Ctrl_Winbond_Cfg_Reg_Type reg_addr, uint16_t *regVal);
BL_Err_Type PSram_Ctrl_Winbond_Write_Reg(PSRAM_ID_Type PSRAM_ID, PSRAM_Ctrl_Winbond_Cfg_Reg_Type reg_addr,
                                         PSRAM_Winbond_Cfg_Type *reg_cfg);
BL_Err_Type PSram_Ctrl_ApMem_Read_Reg(PSRAM_ID_Type PSRAM_ID, PSRAM_Ctrl_ApMem_Cfg_Reg_Type reg_addr, uint16_t *regVal);
BL_Err_Type PSram_Ctrl_ApMem_Write_Reg(PSRAM_ID_Type PSRAM_ID, PSRAM_Ctrl_ApMem_Cfg_Reg_Type reg_addr,
                                       PSRAM_APMemory_Cfg_Type *reg_cfg);
void PSram_Ctrl_ApMem_Reset(PSRAM_ID_Type PSRAM_ID);
void PSram_Ctrl_CK_Sel(PSRAM_ID_Type PSRAM_ID, PSRAM_Clock_Type clkSel);
void PSram_Ctrl_Winbond_Reset(PSRAM_ID_Type PSRAM_ID);
uint8_t PSram_Ctrl_Get_Timeout_Flag(PSRAM_ID_Type PSRAM_ID);
void PSram_Ctrl_Clear_Timout_Flag(PSRAM_ID_Type PSRAM_ID);
void PSram_Ctrl_Debug_Timout(PSRAM_ID_Type PSRAM_ID, uint8_t enable, uint32_t timeoutThr);

/*@} end of group PSRAM_CTRL_Public_Functions */

/*@} end of group PSRAM_CTRL */

/*@} end of group BL616_Peripheral_Driver */

#endif /* __BL616_PSRAM_CTRL_H__ */
