/**
  ******************************************************************************
  * @file    bl808_lz4d.h
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
#ifndef __BL808_LZ4D_H__
#define __BL808_LZ4D_H__

#include "lz4_reg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  LZ4D
 *  @{
 */

/** @defgroup  LZ4D_Public_Types
 *  @{
 */

typedef enum {
    LZ4D_STATUS_INVALID = 0,
    LZ4D_STATUS_DONE = (1 << 0),  /*!< 0->decompress done */
    LZ4D_STATUS_ERROR = (1 << 1), /*!< 1->decompress error */
    LZ4D_STATUS_MAX = 0x7FFFFFFF
} LZ4D_STATUS_Type;

typedef enum {
    LZ4D_ADDR_END_SRC = 0,         /*!< 0->src address end: 26-bit */
    LZ4D_ADDR_END_DST,             /*!< 1->dst address end: 26-bit */
    LZ4D_ADDR_BASE_SRC,            /*!< 2->src address start: 32-bit */
    LZ4D_ADDR_BASE_DST,            /*!< 3->dst address start: 32-bit */
    LZ4D_ADDR_END_MAX = 0x03FFFFFF /* max: 64MB */
} LZ4D_ADDR_REG_Type;

/**
 *  @brief LZ4D interrupt type definition
 */
typedef enum {
    LZ4D_INT_DONE,  /*!< LZ4 decompress job done */
    LZ4D_INT_ERROR, /*!< LZ4 decompress processing error */
    LZ4D_INT_ALL,   /*!< LZ4D all interrupts */
    LZ4D_INT_MAX = 0x7FFFFFFF
} LZ4D_INT_Type;

/*@} end of group LZ4D_Public_Types */

/** @defgroup  LZ4D_Public_Constants
 *  @{
 */

/*@} end of group LZ4D_Public_Constants */

/** @defgroup  LZ4D_Public_Macros
 *  @{
 */

#define LZ4DECOMPRESSOR ((lz4_reg_t *)(LZ4D_BASE))

/*@} end of group LZ4D_Public_Macros */

/** @defgroup  LZ4D_Public_Functions
 *  @{
 */
void LZ4D_Stop(void);
void LZ4D_Start(void);
uint32_t LZ4D_GetAddrReg(LZ4D_ADDR_REG_Type addr);
uint32_t LZ4D_GetDecompressLen(void);
uint32_t LZ4D_GetStatus(LZ4D_STATUS_Type sts);
void LZ4D_Decompress(const void *in, void *out);
void LZ4D_IntMask(LZ4D_INT_Type intType, BL_Mask_Type intMask);
#ifndef BFLB_USE_HAL_DRIVER
void LZ4D_Int_Callback_Install(LZ4D_INT_Type intType, intCallback_Type *cbFun);
#endif
void LZ4D_Init(void);

/*@} end of group LZ4D_Public_Functions */

/*@} end of group LZ4D */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_LZ4D_H__ */
