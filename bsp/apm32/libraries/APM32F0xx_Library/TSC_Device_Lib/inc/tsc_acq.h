/*!
 * @file        tsc_acq.h
 *
 * @brief       This file contains external declarations of the tsc_acq.c file.
 *
 * @version     V1.0.1
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __TSC_ACQ_H
#define __TSC_ACQ_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"
#include "tsc_config.h"
#include "tsc_types.h"
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_Acquisition_Driver TSC Acquisition Driver
  @{
*/

#if !defined(APM32F051) && defined(APM32F071) && defined(APM32F072) && defined(APM32F091)
#error "Device family not declared in the toolchain compiler preprocessor."
#endif

/** @defgroup TSC_Acquisition_Macros Macros
  @{
  */

#ifndef CONST
#define CONST const
#endif

/* SysTick enable/disable interrupt macros */
#define enableInterrupts()  {SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;}
#define disableInterrupts() {SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;}

#define TSC_NB_GROUPS (8)

#define TSC_GROUP1 (0x01)
#define TSC_GROUP2 (0x02)
#define TSC_GROUP3 (0x04)
#define TSC_GROUP4 (0x08)
#define TSC_GROUP5 (0x10)
#define TSC_GROUP6 (0x20)
#define TSC_GROUP7 (0x40)
#define TSC_GROUP8 (0x80)

/* GxIOy masks */
#define TSC_GROUP1_IO1 (0x00000001)
#define TSC_GROUP1_IO2 (0x00000002)
#define TSC_GROUP1_IO3 (0x00000004)
#define TSC_GROUP1_IO4 (0x00000008)
#define TSC_GROUP2_IO1 (0x00000010)
#define TSC_GROUP2_IO2 (0x00000020)
#define TSC_GROUP2_IO3 (0x00000040)
#define TSC_GROUP2_IO4 (0x00000080)
#define TSC_GROUP3_IO1 (0x00000100)
#define TSC_GROUP3_IO2 (0x00000200)
#define TSC_GROUP3_IO3 (0x00000400)
#define TSC_GROUP3_IO4 (0x00000800)
#define TSC_GROUP4_IO1 (0x00001000)
#define TSC_GROUP4_IO2 (0x00002000)
#define TSC_GROUP4_IO3 (0x00004000)
#define TSC_GROUP4_IO4 (0x00008000)
#define TSC_GROUP5_IO1 (0x00010000)
#define TSC_GROUP5_IO2 (0x00020000)
#define TSC_GROUP5_IO3 (0x00040000)
#define TSC_GROUP5_IO4 (0x00080000)
#define TSC_GROUP6_IO1 (0x00100000)
#define TSC_GROUP6_IO2 (0x00200000)
#define TSC_GROUP6_IO3 (0x00400000)
#define TSC_GROUP6_IO4 (0x00800000)
#define TSC_GROUP7_IO1 (0x01000000)
#define TSC_GROUP7_IO2 (0x02000000)
#define TSC_GROUP7_IO3 (0x04000000)
#define TSC_GROUP7_IO4 (0x08000000)
#define TSC_GROUP8_IO1 (0x10000000)
#define TSC_GROUP8_IO2 (0x20000000)
#define TSC_GROUP8_IO3 (0x40000000)
#define TSC_GROUP8_IO4 (0x80000000)

/* Exported types, For all devices/acquisitions */
typedef uint16_t  TSC_tMeas_T;         /*!< Measurement */
typedef uint16_t  TSC_tRefer_T;        /*!< Reference */
typedef int16_t   TSC_tDelta_T;        /*!< Delta */

typedef uint8_t   TSC_tIndexSrc_T;     /*!< Channel source index */
typedef uint16_t  TSC_tIndexDest_T;    /*!< Channel destination index */

typedef uint8_t   TSC_tRefRest_T;      /*!< Reference Rest (ECS) */
typedef uint16_t  TSC_tKCoeff_T;       /*!< K coefficient (ECS) */

typedef uint8_t   TSC_tIndex_T;        /*!< Generic index */
typedef uint16_t  TSC_tNum_T;          /*!< Generic number */
typedef uint8_t   TSC_tCounter_T;      /*!< Generic counter used for debounce */

typedef uint8_t   TSC_tThreshold_T;    /*!< Delta threshold */

typedef int16_t   TSC_tPosition_T;     /*!< Linear and Rotary sensors position */
typedef uint8_t   TSC_tsignPosition_T; /*!< Linear and Rotary sensors position */

typedef uint16_t  TSC_tTick_ms_T;      /*!< Time in ms */
typedef uint8_t   TSC_tTick_sec_T;     /*!< Time in sec */

/**@} end of group TSC_Acquisition_Macros */

/** @defgroup TSC_Acquisition_Enumerations Enumerations
  @{
  */

/**@} end of group TSC_Acquisition_Enumerations */

/** @defgroup TSC_Acquisition_Structures Structures
  @{
  */

/* Pointer to the Measure filter function */
typedef TSC_tMeas_T(* TSC_pMeasFilter_T)(TSC_tMeas_T, TSC_tMeas_T);
/* Pointer to the Delta filter function */
typedef TSC_tDelta_T(* TSC_pDeltaFilter_T)(TSC_tDelta_T);

/**
 * @brief   Channel destination index
 */
typedef struct
{
    TSC_tIndexDest_T  IdxDest; /*!< Index in the Channel data array */
} TSC_Channel_Dest_T;

/**
 * @brief   Channel Source and Configuration
 */
typedef struct
{
    TSC_tIndexSrc_T  IdxSrc; /*!< Index of TSC->IOGxCNT[] registers */
    /* For apm32f0xx only */
    uint32_t         msk_IOCHCTRL_channel; /*!< Mask of the Channel IO (electrodes only) */
    uint32_t         msk_IOGCSTS_group;    /*!< Mask of the Group used (electrodes only) */
} TSC_Channel_Src_T;

/**
 * @brief   Channel flags
 */
typedef struct
{
    unsigned int DataReady : 1;   /*!< To identify a new measurement (TSC_DATA_T) */
    unsigned int AcqStatus : 2;   /*!< Acquisition status (TSC_ACQ_STATUS_T) */
    unsigned int ObjStatus : 2;   /*!< Object status (TSC_OBJ_STATUS_T) */
} TSC_Channel_Flag_T;

/**
 * @brief    Channel Data
 */
typedef struct
{
    TSC_Channel_Flag_T   Flag;    /*!< Flag */
    TSC_tRefer_T         Refer;   /*!< Reference */
    TSC_tRefRest_T       RefRest; /*!< Reference rest for ECS */
    TSC_tDelta_T         Delta;   /*!< Delta */
#if TOUCH_USE_MEAS > 0
    TSC_tMeas_T          Meas;    /*!< Hold the last acquisition measure */
#endif
} TSC_Channel_Data_T;

/**
 * @brief   Block Configuration
 */
typedef struct
{
    /* Common to all acquisitions */
    CONST TSC_Channel_Src_T*  p_chSrc;     /*!< Pointer to the Channel Source and Configuration */
    CONST TSC_Channel_Dest_T* p_chDest;    /*!< Pointer to the Channel Destination */
    TSC_Channel_Data_T*       p_chData;    /*!< Pointer to the Channel Data */
    TSC_tNum_T                NumChannel;  /*!< Number of channels in the block */
    /* For apm32f0xx only */
    uint32_t      msk_IOCHCTRL_channels;   /*!< Mask of all channel IOs (electrodes and shields) */
    uint32_t      msk_IOGCSTS_groups;      /*!< Mask of all groups used (electrodes only) */
} TSC_Block_T;

/**
 * @brief  Structure containing all data of a Zone.
 *         A Zone is a set of Blocks.
 *         Variables of this structure type can be placed in RAM or ROM.
 */
typedef struct
{
    /* Common to all acquisitions */
    TSC_tIndex_T*         indexBlock;   /*!< Pointer to an array of block indexes */
    TSC_pDeltaFilter_T*   daltaFilter;  /*!< Pointer to a Delta filter function */
    TSC_tNum_T            numBlock;     /*!< Number of blocks in the zone */
} TSC_Zone_T;

/**@} end of group TSC_Acquisition_Structures */

/** @defgroup TSC_Acquisition_Functions Functions
  @{
  */

TSC_STATUS_T TSC_Acq_Config(void);
void TSC_Acq_ConfigGPIO(void);
TSC_STATUS_T TSC_Acq_ConfigBlock(TSC_tIndex_T idxBlock);
TSC_BOOL_T TSC_Acq_UseFilter(TSC_Channel_Data_T* pCh);
TSC_BOOL_T TSC_Acq_TestReferenceRange(TSC_Channel_Data_T* pCh);
TSC_BOOL_T TSC_Acq_TestFirstReference(TSC_Channel_Data_T* pCh, TSC_tMeas_T newMeas);
void TSC_Acq_StartPerConfigBlock(void);
TSC_STATUS_T TSC_Acq_WaitBlockEOA(void);
TSC_ACQ_STATUS_T TSC_Acq_CheckNoise(void);
TSC_tMeas_T TSC_Acq_ReadMeasurVal(TSC_tIndexSrc_T index);
TSC_tDelta_T TSC_Acq_ComputeDelta(TSC_tRefer_T refVal, TSC_tMeas_T measVal);
TSC_tMeas_T TSC_Acq_ComputeMeas(TSC_tRefer_T refVal, TSC_tDelta_T deltaVal);

TSC_STATUS_T TSC_Acq_ConfigZone(CONST TSC_Zone_T* zone, TSC_tIndex_T idxBlock);
TSC_STATUS_T TSC_Acq_ReadBlockResult(TSC_tIndex_T idxBlock, TSC_pMeasFilter_T mfilter, TSC_pDeltaFilter_T dfilter);
TSC_STATUS_T TSC_Acq_CalibrateBlock(TSC_tIndex_T block);
void TSC_acq_ClearBlockData(TSC_tIndex_T block);

#ifdef __cplusplus
}
#endif

#endif /* __TSC_ACQ_H */

/**@} end of group TSC_Acquisition_Functions */
/**@} end of group TSC_Acquisition_Driver */
/**@} end of group TSC_Driver_Library */
