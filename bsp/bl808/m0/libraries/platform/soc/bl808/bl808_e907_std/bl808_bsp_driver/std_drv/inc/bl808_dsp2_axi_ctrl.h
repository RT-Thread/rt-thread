/**
  ******************************************************************************
  * @file    bl808_dsp2_axi_ctrl.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
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
#ifndef __BL808_DSP2_AXI_CTRL_H__
#define __BL808_DSP2_AXI_CTRL_H__

#include "dsp2_axi_ctrl_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DSP2_AXI_CTRL
 *  @{
 */

/** @defgroup  DSP2_AXI_CTRL_Public_Types
 *  @{
 */

/**
 *  @brief 3DNR burst type definition
 */
typedef enum {
    DSP2_3DNR_BURST_TYPE_SINGLE,     /*!< DSP2 3DNR burst type:single */
    DSP2_3DNR_BURST_TYPE_INCR4,      /*!< DSP2 3DNR burst type:incrementing 4 */
    DSP2_3DNR_BURST_TYPE_INCR8,      /*!< DSP2 3DNR burst type:incrementing 8 */
    DSP2_3DNR_BURST_TYPE_INCR16,     /*!< DSP2 3DNR burst type:incrementing 16 */
    DSP2_3DNR_BURST_TYPE_INCR32 = 5, /*!< DSP2 3DNR burst type:incrementing 32 */
    DSP2_3DNR_BURST_TYPE_INCR64,     /*!< DSP2 3DNR burst type:incrementing 64 */
} DSP2_3DNR_Burst_Type;

/**
 *  @brief 3DNR status type definition
 */
typedef enum {
    DSP2_3DNR_STATUS_R_DRAIN = 4,    /*!< Read fifo drain error status */
    DSP2_3DNR_STATUS_W_OVERFLOW,     /*!< Write overflow status */
    DSP2_3DNR_STATUS_W_DVP_IDLE = 8, /*!< Write dvp idle status */
    DSP2_3DNR_STATUS_W_DVP_WTST,     /*!< Write dvp wait start status */
    DSP2_3DNR_STATUS_W_DVP_FUNC,     /*!< Write dvp function status */
    DSP2_3DNR_STATUS_W_DVP_FEND,     /*!< Write dvp function end status */
    DSP2_3DNR_STATUS_W_DVP_FLSH,     /*!< Write dvp flush status */
    DSP2_3DNR_STATUS_W_BUS_IDLE,     /*!< Write bus idle status */
    DSP2_3DNR_STATUS_W_BUS_FUNC,     /*!< Write bus function status */
    DSP2_3DNR_STATUS_W_BUS_FEND,     /*!< Write bus function end status */
    DSP2_3DNR_STATUS_W_BUS_FLSH,     /*!< Write bus flush status */
    DSP2_3DNR_STATUS_R_DVP_IDLE,     /*!< Read dvp idle status */
    DSP2_3DNR_STATUS_R_DVP_WTST,     /*!< Read dvp wait start status */
    DSP2_3DNR_STATUS_R_DVP_FUNC,     /*!< Read dvp function status */
    DSP2_3DNR_STATUS_R_DVP_FEND,     /*!< Read dvp function end status */
    DSP2_3DNR_STATUS_R_DVP_FLSH,     /*!< Read dvp flush status */
    DSP2_3DNR_STATUS_R_BUS_IDLE,     /*!< Read bus idle status */
    DSP2_3DNR_STATUS_R_BUS_FUNC,     /*!< Read bus function status */
    DSP2_3DNR_STATUS_R_BUS_FEND,     /*!< Read bus function end status */
    DSP2_3DNR_STATUS_R_BUS_FLSH,     /*!< Read bus flush status */
    DSP2_3DNR_STATUS_R_IDLE,         /*!< AXI read channel idle status */
    DSP2_3DNR_STATUS_W_IDLE,         /*!< AXI write channel idle status */
} DSP2_3DNR_Status_Type;

/**
 *  @brief 3DNR configure strcut definition
 */
typedef struct
{
    DSP2_3DNR_Burst_Type burst; /*!< 3DNR burst length */
    uint32_t memStart;         /*!< Data start address */
    uint32_t memSize;          /*!< Memory size */
    uint16_t hsyncStart;       /*!< Hsync active start count */
    uint16_t hsyncEnd;         /*!< Hsync active end count */
    uint16_t vsyncStart;       /*!< Vsync active start count */
    uint16_t vsyncEnd;         /*!< Vsync active end count */
} DSP2_3DNR_Cfg_Type;

/*@} end of group DSP2_AXI_CTRL_Public_Types */

/** @defgroup  DSP2_AXI_CTRL_Public_Constants
 *  @{
 */

/** @defgroup  DSP2_3DNR_BURST_TYPE
 *  @{
 */
#define IS_DSP2_3DNR_BURST_TYPE(type) (((type) == DSP2_3DNR_BURST_TYPE_SINGLE) || \
                                      ((type) == DSP2_3DNR_BURST_TYPE_INCR4) ||  \
                                      ((type) == DSP2_3DNR_BURST_TYPE_INCR8) ||  \
                                      ((type) == DSP2_3DNR_BURST_TYPE_INCR16) || \
                                      ((type) == DSP2_3DNR_BURST_TYPE_INCR32) || \
                                      ((type) == DSP2_3DNR_BURST_TYPE_INCR64))

/** @defgroup  DSP2_3DNR_STATUS_TYPE
 *  @{
 */
#define IS_DSP2_3DNR_STATUS_TYPE(type) (((type) == DSP2_3DNR_STATUS_R_DRAIN) ||    \
                                       ((type) == DSP2_3DNR_STATUS_W_OVERFLOW) || \
                                       ((type) == DSP2_3DNR_STATUS_W_DVP_IDLE) || \
                                       ((type) == DSP2_3DNR_STATUS_W_DVP_WTST) || \
                                       ((type) == DSP2_3DNR_STATUS_W_DVP_FUNC) || \
                                       ((type) == DSP2_3DNR_STATUS_W_DVP_FEND) || \
                                       ((type) == DSP2_3DNR_STATUS_W_DVP_FLSH) || \
                                       ((type) == DSP2_3DNR_STATUS_W_BUS_IDLE) || \
                                       ((type) == DSP2_3DNR_STATUS_W_BUS_FUNC) || \
                                       ((type) == DSP2_3DNR_STATUS_W_BUS_FEND) || \
                                       ((type) == DSP2_3DNR_STATUS_W_BUS_FLSH) || \
                                       ((type) == DSP2_3DNR_STATUS_R_DVP_IDLE) || \
                                       ((type) == DSP2_3DNR_STATUS_R_DVP_WTST) || \
                                       ((type) == DSP2_3DNR_STATUS_R_DVP_FUNC) || \
                                       ((type) == DSP2_3DNR_STATUS_R_DVP_FEND) || \
                                       ((type) == DSP2_3DNR_STATUS_R_DVP_FLSH) || \
                                       ((type) == DSP2_3DNR_STATUS_R_BUS_IDLE) || \
                                       ((type) == DSP2_3DNR_STATUS_R_BUS_FUNC) || \
                                       ((type) == DSP2_3DNR_STATUS_R_BUS_FEND) || \
                                       ((type) == DSP2_3DNR_STATUS_R_BUS_FLSH) || \
                                       ((type) == DSP2_3DNR_STATUS_R_IDLE) ||     \
                                       ((type) == DSP2_3DNR_STATUS_W_IDLE))

/*@} end of group DSP2_AXI_CTRL_Public_Constants */

/** @defgroup  DSP2_AXI_CTRL_Public_Macros
 *  @{
 */

/*@} end of group DSP2_AXI_CTRL_Public_Macros */

/** @defgroup  DSP2_AXI_CTRL_Public_Functions
 *  @{
 */
void DSP2_3DNR_Init(DSP2_3DNR_Cfg_Type *dsp23DNRCfg);
void DSP2_3DNR_Enable(void);
void DSP2_3DNR_Disable(void);
void DSP2_3DNR_Clear_Write_Overflow(void);
void DSP2_3DNR_Clear_Read_Drain(void);
BL_Sts_Type DSP2_3DNR_Get_status(DSP2_3DNR_Status_Type dsp23DNRStatus);

/*@} end of group DSP2_AXI_CTRL_Public_Functions */

/*@} end of group DSP2_AXI_CTRL */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_DSP2_AXI_CTRL_H__ */
