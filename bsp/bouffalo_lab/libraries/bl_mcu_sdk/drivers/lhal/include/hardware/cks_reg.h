/**
  ******************************************************************************
  * @file    cks_reg.h
  * @version V1.0
  * @date    2022-10-25
  * @brief   This file is the description of.IP register
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
#ifndef  __CKS_REG_H__
#define  __CKS_REG_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define CKS_CONFIG_OFFSET                                       (0x0)/* cks_config */
#define CKS_DATA_IN_OFFSET                                      (0x4)/* data_in */
#define CKS_OUT_OFFSET                                          (0x8)/* cks_out */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : cks_config */
#define CKS_CR_CKS_CLR                                          (1<<0U)
#define CKS_CR_CKS_BYTE_SWAP                                    (1<<1U)

/* 0x4 : data_in */
#define CKS_DATA_IN_SHIFT                                       (0U)
#define CKS_DATA_IN_MASK                                        (0xff<<CKS_DATA_IN_SHIFT)

/* 0x8 : cks_out */
#define CKS_OUT_SHIFT                                           (0U)
#define CKS_OUT_MASK                                            (0xffff<<CKS_OUT_SHIFT)


#endif  /* __CKS_REG_H__ */
