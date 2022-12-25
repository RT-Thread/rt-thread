/**
  ******************************************************************************
  * @file    bl808_lz4d.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
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

#include "bl808.h"
#include "bl808_common.h"
#include "bl808_lz4d.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  LZ4D
 *  @{
 */

/** @defgroup  LZ4D_Private_Macros
 *  @{
 */

/*@} end of group LZ4D_Private_Macros */

/** @defgroup  LZ4D_Private_Types
 *  @{
 */

/*@} end of group LZ4D_Private_Types */

/** @defgroup  LZ4D_Private_Variables
 *  @{
 */

#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *lz4dIntCbfArra[LZ4D_INT_ALL] = { NULL };
#endif

/*@} end of group LZ4D_Private_Variables */

/** @defgroup  LZ4D_Global_Variables
 *  @{
 */

/*@} end of group LZ4D_Global_Variables */

/** @defgroup  LZ4D_Private_Fun_Declaration
 *  @{
 */

/*@} end of group LZ4D_Private_Fun_Declaration */

/** @defgroup  LZ4D_Private_Functions
 *  @{
 */

/*@} end of group LZ4D_Private_Functions */

/** @defgroup  LZ4D_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  None
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void LZ4D_Stop(void)
{
    LZ4DECOMPRESSOR->lz4_config.BF.lz4_en = 0;
}

void LZ4D_Start(void)
{
    LZ4DECOMPRESSOR->lz4_config.BF.lz4_en = 1;
}

uint32_t LZ4D_GetAddrReg(LZ4D_ADDR_REG_Type addr)
{
    uint32_t res = -1;

    switch (addr) {
        case LZ4D_ADDR_END_SRC:
            res = LZ4DECOMPRESSOR->lz4_src_end.WORD & LZ4D_ADDR_END_MAX;
            break;

        case LZ4D_ADDR_END_DST:
            res = LZ4DECOMPRESSOR->lz4_dst_end.WORD & LZ4D_ADDR_END_MAX;
            break;

        case LZ4D_ADDR_BASE_SRC:
            res = LZ4DECOMPRESSOR->lz4_src_start.WORD;
            break;

        case LZ4D_ADDR_BASE_DST:
            res = LZ4DECOMPRESSOR->lz4_dst_start.WORD;
            break;

        default:
            break;
    }

    return res;
}

uint32_t LZ4D_GetDecompressLen(void)
{
    uint32_t len = 0;

    len = LZ4D_GetAddrReg(LZ4D_ADDR_END_DST) -
          (LZ4D_GetAddrReg(LZ4D_ADDR_BASE_DST) & LZ4D_ADDR_END_MAX);

    return len;
}

uint32_t LZ4D_GetStatus(LZ4D_STATUS_Type sts)
{
    uint32_t res = 0;

    switch (sts) {
        case LZ4D_STATUS_DONE ... LZ4D_STATUS_ERROR:
            res = LZ4DECOMPRESSOR->lz4_int_sta.WORD & sts;
            break;

        default:
            break;
    }

    return res;
}

void LZ4D_Decompress(const void *in, void *out)
{
    LZ4DECOMPRESSOR->lz4_config.BF.lz4_en = 0;

    LZ4DECOMPRESSOR->lz4_src_start.WORD = (uint32_t)(uintptr_t)in;
    /* TODO: the out region length must be 4-byte aligned:
     * e.g.: the decompressed length is 33, you have to allocate 36 bytes for it.
     * or, the HW will overwrite the RAM space from offset 34 to 36. 
     */
    LZ4DECOMPRESSOR->lz4_dst_start.WORD = (uint32_t)(uintptr_t)out;

    /* flush the CPU D$ in case of data bas been cached,
     * e.g., the compressed data is copied by CPU.
     */
    //L1C_DCache_Clean_Invalid_All();

    LZ4DECOMPRESSOR->lz4_config.BF.lz4_en = 1;

    /* after LZ4D doing it's job, CPU has to invalid the cache line for *out */
}

/*******************************************************************************
 * @brief  LZ4D mask or unmask certain or all interrupt
 *
 * @param  intType: interrupt type
 * @param  intMask: mask or unmask
 *
 * @return None
 *
*******************************************************************************/
void LZ4D_IntMask(LZ4D_INT_Type intType, BL_Mask_Type intMask)
{
    /* Check the parameters */
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    switch (intType) {
        case LZ4D_INT_DONE:
            if (UNMASK == intMask) {
                LZ4DECOMPRESSOR->lz4_int_en.BF.lz4_done_en = 1;
            } else {
                LZ4DECOMPRESSOR->lz4_int_en.BF.lz4_done_en = 0;
            }
            break;

        case LZ4D_INT_ERROR:
            if (UNMASK == intMask) {
                LZ4DECOMPRESSOR->lz4_int_en.BF.lz4_err_en = 1;
            } else {
                LZ4DECOMPRESSOR->lz4_int_en.BF.lz4_err_en = 0;
            }
            break;

        case LZ4D_INT_ALL:
            if (UNMASK == intMask) {
                LZ4DECOMPRESSOR->lz4_int_en.BF.lz4_done_en = 1;
                LZ4DECOMPRESSOR->lz4_int_en.BF.lz4_err_en = 1;
            } else {
                LZ4DECOMPRESSOR->lz4_int_en.BF.lz4_done_en = 0;
                LZ4DECOMPRESSOR->lz4_int_en.BF.lz4_err_en = 0;
            }
            break;

        default:
            /* invalid param */
            break;
    }
}

/*******************************************************************************
 * @brief  ADC install interrupt callback
 *
 * @param  intType: ADC interrupt type
 * @param  cbFun: ADC interrupt callback
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void LZ4D_Int_Callback_Install(LZ4D_INT_Type intType, intCallback_Type *cbFun)
{
    if (intType < LZ4D_INT_ALL)
        lz4dIntCbfArra[intType] = cbFun;
}
#endif

/*******************************************************************************
 * @brief  LZ4D interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void LZ4D_IRQHandler(void)
{
    if (LZ4D_GetStatus(LZ4D_STATUS_DONE)) {
        if (lz4dIntCbfArra[LZ4D_INT_DONE] != NULL) {
            lz4dIntCbfArra[LZ4D_INT_DONE]();
        }
    }

    if (LZ4D_GetStatus(LZ4D_STATUS_ERROR)) {
        if (lz4dIntCbfArra[LZ4D_INT_ERROR] != NULL) {
            lz4dIntCbfArra[LZ4D_INT_ERROR]();
        }
    }
}
#endif

void LZ4D_Init(void)
{
#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(LZ4D_IRQn, LZ4D_IRQHandler);
#endif
}

/*@} end of group LZ4D_Public_Functions */

/*@} end of group LZ4D */

/*@} end of group BL808_Peripheral_Driver */
