/**
  ******************************************************************************
  * @file    bl606p_ipc.h
  * @version V1.2
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2018 Bouffalo Lab</center></h2>
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
#ifndef __BL808_IPC_H__
#define __BL808_IPC_H__

#include "ipc_reg.h"
#include "bl808_common.h"
#include "bl808_glb.h"

/** @addtogroup  BL606P_Peripheral_Driver
 *  @{
 */

/** @addtogroup  IPC
 *  @{
 */

/** @defgroup  IPC_Public_Types
 *  @{
 */
typedef void(ipcIntCallback)(uint32_t src);
/**
 *  @brief IPC interrupt source type definition
 */
typedef enum {
    IPC_INT_SRC_BIT0 = 0, /*!< IPC interrupt source bit 0 */
    IPC_INT_SRC_BIT1,     /*!< IPC interrupt source bit 1 */
    IPC_INT_SRC_BIT2,     /*!< IPC interrupt source bit 2 */
    IPC_INT_SRC_BIT3,     /*!< IPC interrupt source bit 3 */
    IPC_INT_SRC_BIT4,     /*!< IPC interrupt source bit 4 */
    IPC_INT_SRC_BIT5,     /*!< IPC interrupt source bit 5 */
    IPC_INT_SRC_BIT6,     /*!< IPC interrupt source bit 6 */
    IPC_INT_SRC_BIT7,     /*!< IPC interrupt source bit 7 */
    IPC_INT_SRC_BIT8,     /*!< IPC interrupt source bit 8 */
    IPC_INT_SRC_BIT9,     /*!< IPC interrupt source bit 9 */
    IPC_INT_SRC_BIT10,    /*!< IPC interrupt source bit 10 */
    IPC_INT_SRC_BIT11,    /*!< IPC interrupt source bit 11 */
    IPC_INT_SRC_BIT12,    /*!< IPC interrupt source bit 12 */
    IPC_INT_SRC_BIT13,    /*!< IPC interrupt source bit 13 */
    IPC_INT_SRC_BIT14,    /*!< IPC interrupt source bit 14 */
    IPC_INT_SRC_BIT15,    /*!< IPC interrupt source bit 15 */
    IPC_INT_SRC_BIT16,    /*!< IPC interrupt source bit 16 */
    IPC_INT_SRC_BIT17,    /*!< IPC interrupt source bit 17 */
    IPC_INT_SRC_BIT18,    /*!< IPC interrupt source bit 18 */
    IPC_INT_SRC_BIT19,    /*!< IPC interrupt source bit 19 */
    IPC_INT_SRC_BIT20,    /*!< IPC interrupt source bit 20 */
    IPC_INT_SRC_BIT21,    /*!< IPC interrupt source bit 21 */
    IPC_INT_SRC_BIT22,    /*!< IPC interrupt source bit 22 */
    IPC_INT_SRC_BIT23,    /*!< IPC interrupt source bit 23 */
    IPC_INT_SRC_BIT24,    /*!< IPC interrupt source bit 24 */
    IPC_INT_SRC_BIT25,    /*!< IPC interrupt source bit 25 */
    IPC_INT_SRC_BIT26,    /*!< IPC interrupt source bit 26 */
    IPC_INT_SRC_BIT27,    /*!< IPC interrupt source bit 27 */
    IPC_INT_SRC_BIT28,    /*!< IPC interrupt source bit 28 */
    IPC_INT_SRC_BIT29,    /*!< IPC interrupt source bit 29 */
    IPC_INT_SRC_BIT30,    /*!< IPC interrupt source bit 30 */
    IPC_INT_SRC_BIT31,    /*!< IPC interrupt source bit 31 */
    IPC_INT_SRC_MAX,      /*!<  */
} IPC_Int_Src_Type;

/**
 *  @brief IPC interrupt source type definition
 */
typedef enum {
    IPC_GRP_INT_SRC_BIT0 = 0, /*!< IPC interrupt source bit 0 */
    IPC_GRP_INT_SRC_BIT1,     /*!< IPC interrupt source bit 1 */
    IPC_GRP_INT_SRC_BIT2,     /*!< IPC interrupt source bit 2 */
    IPC_GRP_INT_SRC_BIT3,     /*!< IPC interrupt source bit 3 */
    IPC_GRP_INT_SRC_BIT4,     /*!< IPC interrupt source bit 4 */
    IPC_GRP_INT_SRC_BIT5,     /*!< IPC interrupt source bit 5 */
    IPC_GRP_INT_SRC_BIT6,     /*!< IPC interrupt source bit 6 */
    IPC_GRP_INT_SRC_BIT7,     /*!< IPC interrupt source bit 7 */
    IPC_GRP_INT_SRC_BIT8,     /*!< IPC interrupt source bit 8 */
    IPC_GRP_INT_SRC_BIT9,     /*!< IPC interrupt source bit 9 */
    IPC_GRP_INT_SRC_BIT10,    /*!< IPC interrupt source bit 10 */
    IPC_GRP_INT_SRC_BIT11,    /*!< IPC interrupt source bit 11 */
    IPC_GRP_INT_SRC_BIT12,    /*!< IPC interrupt source bit 12 */
    IPC_GRP_INT_SRC_BIT13,    /*!< IPC interrupt source bit 13 */
    IPC_GRP_INT_SRC_BIT14,    /*!< IPC interrupt source bit 14 */
    IPC_GRP_INT_SRC_BIT15,    /*!< IPC interrupt source bit 15 */
    IPC_GRP_INT_SRC_MAX,      /*!<  */
} IPC_Grp_Int_Src_Type;

/*@} end of group IPC_Public_Types */

/** @defgroup  IPC_Public_Constants
 *  @{
 */

/** @defgroup  IPC_INT_GRP_TYPE
 *  @{
 */
#define IS_IPC_GRP_INT_TYPE(type) (((type) == IPC_GRP_INT_SRC_BIT0) ||  \
                                   ((type) == IPC_GRP_INT_SRC_BIT1) ||  \
                                   ((type) == IPC_GRP_INT_SRC_BIT2) ||  \
                                   ((type) == IPC_GRP_INT_SRC_BIT3) ||  \
                                   ((type) == IPC_GRP_INT_SRC_BIT4) ||  \
                                   ((type) == IPC_GRP_INT_SRC_BIT5) ||  \
                                   ((type) == IPC_GRP_INT_SRC_BIT6) ||  \
                                   ((type) == IPC_GRP_INT_SRC_BIT7) ||  \
                                   ((type) == IPC_GRP_INT_SRC_BIT8) ||  \
                                   ((type) == IPC_GRP_INT_SRC_BIT9) ||  \
                                   ((type) == IPC_GRP_INT_SRC_BIT10) || \
                                   ((type) == IPC_GRP_INT_SRC_BIT11) || \
                                   ((type) == IPC_GRP_INT_SRC_BIT12) || \
                                   ((type) == IPC_GRP_INT_SRC_BIT13) || \
                                   ((type) == IPC_GRP_INT_SRC_BIT14) || \
                                   ((type) == IPC_GRP_INT_SRC_BIT15))

/** @defgroup  IPC_INT_SRC_TYPE
 *  @{
 */
#define IS_IPC_INT_SRC_TYPE(type) (((type) == IPC_INT_SRC_BIT0) ||  \
                                   ((type) == IPC_INT_SRC_BIT1) ||  \
                                   ((type) == IPC_INT_SRC_BIT2) ||  \
                                   ((type) == IPC_INT_SRC_BIT3) ||  \
                                   ((type) == IPC_INT_SRC_BIT4) ||  \
                                   ((type) == IPC_INT_SRC_BIT5) ||  \
                                   ((type) == IPC_INT_SRC_BIT6) ||  \
                                   ((type) == IPC_INT_SRC_BIT7) ||  \
                                   ((type) == IPC_INT_SRC_BIT8) ||  \
                                   ((type) == IPC_INT_SRC_BIT9) ||  \
                                   ((type) == IPC_INT_SRC_BIT10) || \
                                   ((type) == IPC_INT_SRC_BIT11) || \
                                   ((type) == IPC_INT_SRC_BIT12) || \
                                   ((type) == IPC_INT_SRC_BIT13) || \
                                   ((type) == IPC_INT_SRC_BIT14) || \
                                   ((type) == IPC_INT_SRC_BIT15) || \
                                   ((type) == IPC_INT_SRC_BIT16) || \
                                   ((type) == IPC_INT_SRC_BIT17) || \
                                   ((type) == IPC_INT_SRC_BIT18) || \
                                   ((type) == IPC_INT_SRC_BIT19) || \
                                   ((type) == IPC_INT_SRC_BIT20) || \
                                   ((type) == IPC_INT_SRC_BIT21) || \
                                   ((type) == IPC_INT_SRC_BIT22) || \
                                   ((type) == IPC_INT_SRC_BIT23) || \
                                   ((type) == IPC_INT_SRC_BIT24) || \
                                   ((type) == IPC_INT_SRC_BIT25) || \
                                   ((type) == IPC_INT_SRC_BIT26) || \
                                   ((type) == IPC_INT_SRC_BIT27) || \
                                   ((type) == IPC_INT_SRC_BIT28) || \
                                   ((type) == IPC_INT_SRC_BIT29) || \
                                   ((type) == IPC_INT_SRC_BIT30) || \
                                   ((type) == IPC_INT_SRC_BIT31))

/*@} end of group IPC_Public_Constants */

/** @defgroup  IPC_Public_Macros
 *  @{
 */

/*@} end of group IPC_Public_Macros */

/** @defgroup  IPC_Public_Functions
 *  @{
 */
void IPC_M0_Init(ipcIntCallback *onLPTriggerCallBack,
                 ipcIntCallback *onD0TriggerCallBack);
void IPC_M0_Int_Unmask(IPC_Int_Src_Type src);
void IPC_M0_Int_Unmask_By_Word(uint32_t src);
uint32_t IPC_M0_Get_Int_Raw_Status(void);
void IPC_M0_Clear_Int(IPC_Int_Src_Type src);
void IPC_M0_Clear_Int_By_Word(uint32_t src);
void IPC_LP_Trigger_M0(IPC_Grp_Int_Src_Type src);
void IPC_D0_Trigger_M0(IPC_Grp_Int_Src_Type src);
void IPC_M0_Trigger_CPUx(GLB_CORE_ID_Type tgtCPU, IPC_Grp_Int_Src_Type src);

void IPC_LP_Init(ipcIntCallback *onM0TriggerCallBack,
                 ipcIntCallback *onD0TriggerCallBack);
void IPC_LP_Int_Unmask(IPC_Int_Src_Type src);
void IPC_LP_Int_Unmask_By_Word(uint32_t src);
uint32_t IPC_LP_Get_Int_Raw_Status(void);
void IPC_LP_Clear_Int(IPC_Int_Src_Type src);
void IPC_LP_Clear_Int_By_Word(uint32_t src);
void IPC_M0_Trigger_LP(IPC_Grp_Int_Src_Type src);
void IPC_D0_Trigger_LP(IPC_Grp_Int_Src_Type src);
void IPC_LP_Trigger_CPUx(GLB_CORE_ID_Type tgtCPU, IPC_Grp_Int_Src_Type src);

void IPC_D0_Init(ipcIntCallback *onM0TriggerCallBack,
                 ipcIntCallback *onLPTriggerCallBack);
void IPC_D0_Int_Unmask(IPC_Int_Src_Type src);
void IPC_D0_Int_Unmask_By_Word(uint32_t src);
uint32_t IPC_D0_Get_Int_Raw_Status(void);
void IPC_D0_Clear_Int(IPC_Int_Src_Type src);
void IPC_D0_Clear_Int_By_Word(uint32_t src);
void IPC_M0_Trigger_D0(IPC_Grp_Int_Src_Type src);
void IPC_LP_Trigger_D0(IPC_Grp_Int_Src_Type src);
void IPC_D0_Trigger_CPUx(GLB_CORE_ID_Type tgtCPU, IPC_Grp_Int_Src_Type src);

void IPC_Trigger_Target_CPU(GLB_CORE_ID_Type tgtCPU, IPC_Grp_Int_Src_Type src);

#ifndef BFLB_USE_HAL_DRIVER
void IPC_M0_IRQHandler(void);
#endif
#ifndef BFLB_USE_HAL_DRIVER
void IPC_LP_IRQHandler(void);
#endif
#ifndef BFLB_USE_HAL_DRIVER
void IPC_D0_IRQHandler(void);
#endif

/*@} end of group IPC_Public_Functions */

/*@} end of group IPC */

/*@} end of group BL606P_Peripheral_Driver */

#endif /* __BL606P_IPC_H__ */
