/**
  ******************************************************************************
  * @file    bl702_l1c.h
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
#ifndef __BL702_L1C_H__
#define __BL702_L1C_H__

#include "l1c_reg.h"
#include "bl702_common.h"

/** @addtogroup  BL702_Peripheral_Driver
 *  @{
 */

/** @addtogroup  L1C
 *  @{
 */

/** @defgroup  L1C_Public_Types
 *  @{
 */

/**
 *  @brief L1C configuration structure type definition
 */
typedef struct
{
    BL_Fun_Type wrapDis;  /*!< wrap disable */
    BL_Fun_Type bypassEn; /*!< bypass cache enable */
    uint8_t wayDis;       /*!< Disable part of cache ways & used as ITCM */
    BL_Fun_Type cntEn;    /*!< l1c count enable */
} L1C_CACHE_Cfg_Type;

/**
 *  @brief L1C BMX arb mode type definition
 */
typedef enum {
    L1C_BMX_ARB_FIX,         /*!< 0->fix */
    L1C_BMX_ARB_ROUND_ROBIN, /*!< 2->round-robin */
    L1C_BMX_ARB_RANDOM,      /*!< 3->random */
} L1C_BMX_ARB_Type;

/**
 *  @brief L1C BMX configuration structure type definition
 */
typedef struct
{
    uint8_t timeoutEn;       /*!< Bus timeout enable: detect slave no reaponse in 1024 cycles */
    BL_Fun_Type errEn;       /*!< Bus error response enable */
    L1C_BMX_ARB_Type arbMod; /*!< 0->fix, 2->round-robin, 3->random */
} L1C_BMX_Cfg_Type;

/**
 *  @brief L1C BMX bus err type definition
 */
typedef enum {
    L1C_BMX_BUS_ERR_TRUSTZONE_DECODE, /*!< Bus trustzone decode error */
    L1C_BMX_BUS_ERR_ADDR_DECODE,      /*!< Bus addr decode error */
} L1C_BMX_BUS_ERR_Type;

/**
 *  @brief L1C BMX bus err interrupt type definition
 */
typedef enum {
    L1C_BMX_ERR_INT_ERR, /*!< L1C BMX bus err interrupt */
    L1C_BMX_ERR_INT_ALL, /*!< L1C BMX bus err interrupt max num */
} L1C_BMX_ERR_INT_Type;

/**
 *  @brief L1C BMX time out interrupt type definition
 */
typedef enum {
    L1C_BMX_TO_INT_TIMEOUT, /*!< L1C_BMX timeout interrupt */
    L1C_BMX_TO_INT_ALL,     /*!< L1C_BMX timeout interrupt max num */
} L1C_BMX_TO_INT_Type;

/*@} end of group L1C_Public_Types */

/** @defgroup  L1C_Public_Constants
 *  @{
 */

/** @defgroup  L1C_BMX_ARB_TYPE
 *  @{
 */
#define IS_L1C_BMX_ARB_TYPE(type) (((type) == L1C_BMX_ARB_FIX) ||         \
                                   ((type) == L1C_BMX_ARB_ROUND_ROBIN) || \
                                   ((type) == L1C_BMX_ARB_RANDOM))

/** @defgroup  L1C_BMX_BUS_ERR_TYPE
 *  @{
 */
#define IS_L1C_BMX_BUS_ERR_TYPE(type) (((type) == L1C_BMX_BUS_ERR_TRUSTZONE_DECODE) || \
                                       ((type) == L1C_BMX_BUS_ERR_ADDR_DECODE))

/** @defgroup  L1C_BMX_ERR_INT_TYPE
 *  @{
 */
#define IS_L1C_BMX_ERR_INT_TYPE(type) (((type) == L1C_BMX_ERR_INT_ERR) || \
                                       ((type) == L1C_BMX_ERR_INT_ALL))

/** @defgroup  L1C_BMX_TO_INT_TYPE
 *  @{
 */
#define IS_L1C_BMX_TO_INT_TYPE(type) (((type) == L1C_BMX_TO_INT_TIMEOUT) || \
                                      ((type) == L1C_BMX_TO_INT_ALL))

/*@} end of group L1C_Public_Constants */

/** @defgroup  L1C_Public_Macros
 *  @{
 */
#define L1C_WAY_DISABLE_NONE  0x00
#define L1C_WAY_DISABLE_ONE   0x01
#define L1C_WAY_DISABLE_TWO   0x03
#define L1C_WAY_DISABLE_THREE 0x07
#define L1C_WAY_DISABLE_ALL   0x0F
#define L1C_WAY_DISABLE_USER  0xFF
#if 1
/*NP config address */
#define L1C_CONF_REG        (L1C_BASE + 0x00)
#define L1C_HIT_CNT_LSB_REG (L1C_BASE + 0x04)
#define L1C_HIT_CNT_MSB_REG (L1C_BASE + 0x08)
#define L1C_MISS_CNT_REG    (L1C_BASE + 0x0C)
/* Get miss and hit count */
#define L1C_Get_Miss_Cnt()    BL702_REG_RD(L1C_MISS_CNT_REG)
#define L1C_Get_Hit_Cnt_LSB() BL702_REG_RD(L1C_HIT_CNT_LSB_REG)
#define L1C_Get_Hit_Cnt_MSB() BL702_REG_RD(L1C_HIT_CNT_MSB_REG)
#endif

/*@} end of group L1C_Public_Macros */

/** @defgroup  L1C_Public_Functions
 *  @{
 */
/*----------*/
#ifndef BFLB_USE_HAL_DRIVER
void L1C_BMX_ERR_IRQHandler(void);
void L1C_BMX_TO_IRQHandler(void);
#endif
/*----------*/
BL_Err_Type L1C_Cache_Enable_Set(uint8_t wayDisable);
void L1C_Cache_Write_Set(BL_Fun_Type wtEn, BL_Fun_Type wbEn, BL_Fun_Type waEn);
BL_Err_Type L1C_Cache_Flush(void);
void L1C_Cache_Hit_Count_Get(uint32_t *hitCountLow, uint32_t *hitCountHigh);
uint32_t L1C_Cache_Miss_Count_Get(void);
void L1C_Cache_Read_Disable(void);
/*----------*/
BL_Err_Type L1C_Set_Wrap(BL_Fun_Type wrap);
BL_Err_Type L1C_Set_Way_Disable(uint8_t disableVal);
BL_Err_Type L1C_IROM_2T_Access_Set(uint8_t enable);
/*----------*/
BL_Err_Type L1C_BMX_Init(L1C_BMX_Cfg_Type *l1cBmxCfg);
BL_Err_Type L1C_BMX_Addr_Monitor_Enable(void);
BL_Err_Type L1C_BMX_Addr_Monitor_Disable(void);
BL_Err_Type L1C_BMX_BusErrResponse_Enable(void);
BL_Err_Type L1C_BMX_BusErrResponse_Disable(void);
BL_Sts_Type L1C_BMX_Get_Status(L1C_BMX_BUS_ERR_Type errType);
uint32_t L1C_BMX_Get_Err_Addr(void);
BL_Err_Type L1C_BMX_ERR_INT_Callback_Install(L1C_BMX_ERR_INT_Type intType, intCallback_Type *cbFun);
BL_Err_Type L1C_BMX_TIMEOUT_INT_Callback_Install(L1C_BMX_TO_INT_Type intType,
                                                 intCallback_Type *cbFun);
/*----------*/;

/*@} end of group L1C_Public_Functions */

/*@} end of group L1C */

/*@} end of group BL702_Peripheral_Driver */

#endif /* __BL702_L1C_H__ */
