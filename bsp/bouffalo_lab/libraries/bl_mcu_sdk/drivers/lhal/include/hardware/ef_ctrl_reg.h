/**
  ******************************************************************************
  * @file    ef_ctrl_reg.h
  * @version V1.0
  * @date    2022-10-20
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
#ifndef __HARDWARE_EF_CTRL_H__
#define __HARDWARE_EF_CTRL_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define EF_CTRL_EF_IF_CTRL_0_OFFSET   (0x800) /* efuse control */
#define EF_CTRL_EF_IF_CYC_0_OFFSET    (0x804) /* efuse cycle config 0 */
#define EF_CTRL_EF_IF_CYC_1_OFFSET    (0x808) /* efuse cycle config 1 */
#define EF_CTRL_EF_IF_0_MANUAL_OFFSET (0x80C) /* efuse manual config 1 */
#define EF_CTRL_EF_IF_0_STATUS_OFFSET (0x810) /* efuse status */
#define EF_CTRL_EF_IF_CFG_0_OFFSET    (0x814) /* efuse config 0 */

/* 0x800 :efuse control */
#define EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE       EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE
#define EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_POS   (0U)
#define EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_LEN   (1U)
#define EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_MASK  (((1U << EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_LEN) - 1) << EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_POS)
#define EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_UMASK (~(((1U << EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_LEN) - 1) << EF_CTRL_EF_IF_0_AUTOLOAD_P1_DONE_POS))
#define EF_CTRL_EF_IF_0_AUTOLOAD_DONE          EF_CTRL_EF_IF_0_AUTOLOAD_DONE
#define EF_CTRL_EF_IF_0_AUTOLOAD_DONE_POS      (1U)
#define EF_CTRL_EF_IF_0_AUTOLOAD_DONE_LEN      (1U)
#define EF_CTRL_EF_IF_0_AUTOLOAD_DONE_MASK     (((1U << EF_CTRL_EF_IF_0_AUTOLOAD_DONE_LEN) - 1) << EF_CTRL_EF_IF_0_AUTOLOAD_DONE_POS)
#define EF_CTRL_EF_IF_0_AUTOLOAD_DONE_UMASK    (~(((1U << EF_CTRL_EF_IF_0_AUTOLOAD_DONE_LEN) - 1) << EF_CTRL_EF_IF_0_AUTOLOAD_DONE_POS))
//#define EF_CTRL_EF_IF_0_BUSY                   EF_CTRL_EF_IF_0_BUSY
#define EF_CTRL_EF_IF_0_BUSY_POS               (2U)
#define EF_CTRL_EF_IF_0_BUSY_LEN               (1U)
#define EF_CTRL_EF_IF_0_BUSY_MASK              (((1U << EF_CTRL_EF_IF_0_BUSY_LEN) - 1) << EF_CTRL_EF_IF_0_BUSY_POS)
#define EF_CTRL_EF_IF_0_BUSY_UMASK             (~(((1U << EF_CTRL_EF_IF_0_BUSY_LEN) - 1) << EF_CTRL_EF_IF_0_BUSY_POS))
#define EF_CTRL_EF_IF_0_RW                     EF_CTRL_EF_IF_0_RW
#define EF_CTRL_EF_IF_0_RW_POS                 (3U)
#define EF_CTRL_EF_IF_0_RW_LEN                 (1U)
#define EF_CTRL_EF_IF_0_RW_MASK                (((1U << EF_CTRL_EF_IF_0_RW_LEN) - 1) << EF_CTRL_EF_IF_0_RW_POS)
#define EF_CTRL_EF_IF_0_RW_UMASK               (~(((1U << EF_CTRL_EF_IF_0_RW_LEN) - 1) << EF_CTRL_EF_IF_0_RW_POS))
#define EF_CTRL_EF_IF_0_TRIG                   EF_CTRL_EF_IF_0_TRIG
#define EF_CTRL_EF_IF_0_TRIG_POS               (4U)
#define EF_CTRL_EF_IF_0_TRIG_LEN               (1U)
#define EF_CTRL_EF_IF_0_TRIG_MASK              (((1U << EF_CTRL_EF_IF_0_TRIG_LEN) - 1) << EF_CTRL_EF_IF_0_TRIG_POS)
#define EF_CTRL_EF_IF_0_TRIG_UMASK             (~(((1U << EF_CTRL_EF_IF_0_TRIG_LEN) - 1) << EF_CTRL_EF_IF_0_TRIG_POS))
#define EF_CTRL_EF_IF_0_MANUAL_EN              EF_CTRL_EF_IF_0_MANUAL_EN
#define EF_CTRL_EF_IF_0_MANUAL_EN_POS          (5U)
#define EF_CTRL_EF_IF_0_MANUAL_EN_LEN          (1U)
#define EF_CTRL_EF_IF_0_MANUAL_EN_MASK         (((1U << EF_CTRL_EF_IF_0_MANUAL_EN_LEN) - 1) << EF_CTRL_EF_IF_0_MANUAL_EN_POS)
#define EF_CTRL_EF_IF_0_MANUAL_EN_UMASK        (~(((1U << EF_CTRL_EF_IF_0_MANUAL_EN_LEN) - 1) << EF_CTRL_EF_IF_0_MANUAL_EN_POS))
#define EF_CTRL_EF_IF_0_CYC_MODIFY             EF_CTRL_EF_IF_0_CYC_MODIFY
#define EF_CTRL_EF_IF_0_CYC_MODIFY_POS         (6U)
#define EF_CTRL_EF_IF_0_CYC_MODIFY_LEN         (1U)
#define EF_CTRL_EF_IF_0_CYC_MODIFY_MASK        (((1U << EF_CTRL_EF_IF_0_CYC_MODIFY_LEN) - 1) << EF_CTRL_EF_IF_0_CYC_MODIFY_POS)
#define EF_CTRL_EF_IF_0_CYC_MODIFY_UMASK       (~(((1U << EF_CTRL_EF_IF_0_CYC_MODIFY_LEN) - 1) << EF_CTRL_EF_IF_0_CYC_MODIFY_POS))
#if defined(BL702) || defined(BL602) || defined(BL702L)
#define EF_CTRL_EF_CLK_SAHB_DATA_SEL       EF_CTRL_EF_CLK_SAHB_DATA_SEL
#define EF_CTRL_EF_CLK_SAHB_DATA_SEL_POS   (7U)
#define EF_CTRL_EF_CLK_SAHB_DATA_SEL_LEN   (1U)
#define EF_CTRL_EF_CLK_SAHB_DATA_SEL_MASK  (((1U << EF_CTRL_EF_CLK_SAHB_DATA_SEL_LEN) - 1) << EF_CTRL_EF_CLK_SAHB_DATA_SEL_POS)
#define EF_CTRL_EF_CLK_SAHB_DATA_SEL_UMASK (~(((1U << EF_CTRL_EF_CLK_SAHB_DATA_SEL_LEN) - 1) << EF_CTRL_EF_CLK_SAHB_DATA_SEL_POS))
#endif
#define EF_CTRL_EF_IF_PROT_CODE_CTRL       EF_CTRL_EF_IF_PROT_CODE_CTRL
#define EF_CTRL_EF_IF_PROT_CODE_CTRL_POS   (8U)
#define EF_CTRL_EF_IF_PROT_CODE_CTRL_LEN   (8U)
#define EF_CTRL_EF_IF_PROT_CODE_CTRL_MASK  (((1U << EF_CTRL_EF_IF_PROT_CODE_CTRL_LEN) - 1) << EF_CTRL_EF_IF_PROT_CODE_CTRL_POS)
#define EF_CTRL_EF_IF_PROT_CODE_CTRL_UMASK (~(((1U << EF_CTRL_EF_IF_PROT_CODE_CTRL_LEN) - 1) << EF_CTRL_EF_IF_PROT_CODE_CTRL_POS))
#define EF_CTRL_EF_IF_POR_DIG              EF_CTRL_EF_IF_POR_DIG
#define EF_CTRL_EF_IF_POR_DIG_POS          (16U)
#define EF_CTRL_EF_IF_POR_DIG_LEN          (1U)
#define EF_CTRL_EF_IF_POR_DIG_MASK         (((1U << EF_CTRL_EF_IF_POR_DIG_LEN) - 1) << EF_CTRL_EF_IF_POR_DIG_POS)
#define EF_CTRL_EF_IF_POR_DIG_UMASK        (~(((1U << EF_CTRL_EF_IF_POR_DIG_LEN) - 1) << EF_CTRL_EF_IF_POR_DIG_POS))
#if defined(BL702) || defined(BL602) || defined(BL702L)
#define EF_CTRL_EF_CLK_SAHB_DATA_GATE       EF_CTRL_EF_CLK_SAHB_DATA_GATE
#define EF_CTRL_EF_CLK_SAHB_DATA_GATE_POS   (17U)
#define EF_CTRL_EF_CLK_SAHB_DATA_GATE_LEN   (1U)
#define EF_CTRL_EF_CLK_SAHB_DATA_GATE_MASK  (((1U << EF_CTRL_EF_CLK_SAHB_DATA_GATE_LEN) - 1) << EF_CTRL_EF_CLK_SAHB_DATA_GATE_POS)
#define EF_CTRL_EF_CLK_SAHB_DATA_GATE_UMASK (~(((1U << EF_CTRL_EF_CLK_SAHB_DATA_GATE_LEN) - 1) << EF_CTRL_EF_CLK_SAHB_DATA_GATE_POS))
#else
#define EF_CTRL_EF_PCLK_FORCE_ON       EF_CTRL_EF_PCLK_FORCE_ON
#define EF_CTRL_EF_PCLK_FORCE_ON_POS   (17U)
#define EF_CTRL_EF_PCLK_FORCE_ON_LEN   (1U)
#define EF_CTRL_EF_PCLK_FORCE_ON_MASK  (((1U << EF_CTRL_EF_PCLK_FORCE_ON_LEN) - 1) << EF_CTRL_EF_PCLK_FORCE_ON_POS)
#define EF_CTRL_EF_PCLK_FORCE_ON_UMASK (~(((1U << EF_CTRL_EF_PCLK_FORCE_ON_LEN) - 1) << EF_CTRL_EF_PCLK_FORCE_ON_POS))
#endif
#define EF_CTRL_EF_IF_AUTO_RD_EN            EF_CTRL_EF_IF_AUTO_RD_EN
#define EF_CTRL_EF_IF_AUTO_RD_EN_POS        (18U)
#define EF_CTRL_EF_IF_AUTO_RD_EN_LEN        (1U)
#define EF_CTRL_EF_IF_AUTO_RD_EN_MASK       (((1U << EF_CTRL_EF_IF_AUTO_RD_EN_LEN) - 1) << EF_CTRL_EF_IF_AUTO_RD_EN_POS)
#define EF_CTRL_EF_IF_AUTO_RD_EN_UMASK      (~(((1U << EF_CTRL_EF_IF_AUTO_RD_EN_LEN) - 1) << EF_CTRL_EF_IF_AUTO_RD_EN_POS))
#define EF_CTRL_EF_IF_CYC_MODIFY_LOCK       EF_CTRL_EF_IF_CYC_MODIFY_LOCK
#define EF_CTRL_EF_IF_CYC_MODIFY_LOCK_POS   (19U)
#define EF_CTRL_EF_IF_CYC_MODIFY_LOCK_LEN   (1U)
#define EF_CTRL_EF_IF_CYC_MODIFY_LOCK_MASK  (((1U << EF_CTRL_EF_IF_CYC_MODIFY_LOCK_LEN) - 1) << EF_CTRL_EF_IF_CYC_MODIFY_LOCK_POS)
#define EF_CTRL_EF_IF_CYC_MODIFY_LOCK_UMASK (~(((1U << EF_CTRL_EF_IF_CYC_MODIFY_LOCK_LEN) - 1) << EF_CTRL_EF_IF_CYC_MODIFY_LOCK_POS))
#define EF_CTRL_EF_IF_0_INT                 EF_CTRL_EF_IF_0_INT
#define EF_CTRL_EF_IF_0_INT_POS             (20U)
#define EF_CTRL_EF_IF_0_INT_LEN             (1U)
#define EF_CTRL_EF_IF_0_INT_MASK            (((1U << EF_CTRL_EF_IF_0_INT_LEN) - 1) << EF_CTRL_EF_IF_0_INT_POS)
#define EF_CTRL_EF_IF_0_INT_UMASK           (~(((1U << EF_CTRL_EF_IF_0_INT_LEN) - 1) << EF_CTRL_EF_IF_0_INT_POS))
#define EF_CTRL_EF_IF_0_INT_CLR             EF_CTRL_EF_IF_0_INT_CLR
#define EF_CTRL_EF_IF_0_INT_CLR_POS         (21U)
#define EF_CTRL_EF_IF_0_INT_CLR_LEN         (1U)
#define EF_CTRL_EF_IF_0_INT_CLR_MASK        (((1U << EF_CTRL_EF_IF_0_INT_CLR_LEN) - 1) << EF_CTRL_EF_IF_0_INT_CLR_POS)
#define EF_CTRL_EF_IF_0_INT_CLR_UMASK       (~(((1U << EF_CTRL_EF_IF_0_INT_CLR_LEN) - 1) << EF_CTRL_EF_IF_0_INT_CLR_POS))
#define EF_CTRL_EF_IF_0_INT_SET             EF_CTRL_EF_IF_0_INT_SET
#define EF_CTRL_EF_IF_0_INT_SET_POS         (22U)
#define EF_CTRL_EF_IF_0_INT_SET_LEN         (1U)
#define EF_CTRL_EF_IF_0_INT_SET_MASK        (((1U << EF_CTRL_EF_IF_0_INT_SET_LEN) - 1) << EF_CTRL_EF_IF_0_INT_SET_POS)
#define EF_CTRL_EF_IF_0_INT_SET_UMASK       (~(((1U << EF_CTRL_EF_IF_0_INT_SET_LEN) - 1) << EF_CTRL_EF_IF_0_INT_SET_POS))
#define EF_CTRL_EF_IF_PROT_CODE_CYC         EF_CTRL_EF_IF_PROT_CODE_CYC
#define EF_CTRL_EF_IF_PROT_CODE_CYC_POS     (24U)
#define EF_CTRL_EF_IF_PROT_CODE_CYC_LEN     (8U)
#define EF_CTRL_EF_IF_PROT_CODE_CYC_MASK    (((1U << EF_CTRL_EF_IF_PROT_CODE_CYC_LEN) - 1) << EF_CTRL_EF_IF_PROT_CODE_CYC_POS)
#define EF_CTRL_EF_IF_PROT_CODE_CYC_UMASK   (~(((1U << EF_CTRL_EF_IF_PROT_CODE_CYC_LEN) - 1) << EF_CTRL_EF_IF_PROT_CODE_CYC_POS))

/* 0x80C : ef_if_0_manual, 606P and 808 manual config is the same but not need witch clock */
#if defined(BL702) || defined(BL602) || defined(BL702L) || defined(BL606P) || defined(BL808)
#define EF_CTRL_EF_IF_0_MANUAL_OFFSET        (0x80C)
#define EF_CTRL_EF_IF_A                      EF_CTRL_EF_IF_A
#define EF_CTRL_EF_IF_A_POS                  (0U)
#define EF_CTRL_EF_IF_A_LEN                  (10U)
#define EF_CTRL_EF_IF_A_MASK                 (((1U << EF_CTRL_EF_IF_A_LEN) - 1) << EF_CTRL_EF_IF_A_POS)
#define EF_CTRL_EF_IF_A_UMASK                (~(((1U << EF_CTRL_EF_IF_A_LEN) - 1) << EF_CTRL_EF_IF_A_POS))
#define EF_CTRL_EF_IF_PD                     EF_CTRL_EF_IF_PD
#define EF_CTRL_EF_IF_PD_POS                 (10U)
#define EF_CTRL_EF_IF_PD_LEN                 (1U)
#define EF_CTRL_EF_IF_PD_MASK                (((1U << EF_CTRL_EF_IF_PD_LEN) - 1) << EF_CTRL_EF_IF_PD_POS)
#define EF_CTRL_EF_IF_PD_UMASK               (~(((1U << EF_CTRL_EF_IF_PD_LEN) - 1) << EF_CTRL_EF_IF_PD_POS))
#define EF_CTRL_EF_IF_PS                     EF_CTRL_EF_IF_PS
#define EF_CTRL_EF_IF_PS_POS                 (11U)
#define EF_CTRL_EF_IF_PS_LEN                 (1U)
#define EF_CTRL_EF_IF_PS_MASK                (((1U << EF_CTRL_EF_IF_PS_LEN) - 1) << EF_CTRL_EF_IF_PS_POS)
#define EF_CTRL_EF_IF_PS_UMASK               (~(((1U << EF_CTRL_EF_IF_PS_LEN) - 1) << EF_CTRL_EF_IF_PS_POS))
#define EF_CTRL_EF_IF_STROBE                 EF_CTRL_EF_IF_STROBE
#define EF_CTRL_EF_IF_STROBE_POS             (12U)
#define EF_CTRL_EF_IF_STROBE_LEN             (1U)
#define EF_CTRL_EF_IF_STROBE_MASK            (((1U << EF_CTRL_EF_IF_STROBE_LEN) - 1) << EF_CTRL_EF_IF_STROBE_POS)
#define EF_CTRL_EF_IF_STROBE_UMASK           (~(((1U << EF_CTRL_EF_IF_STROBE_LEN) - 1) << EF_CTRL_EF_IF_STROBE_POS))
#define EF_CTRL_EF_IF_PGENB                  EF_CTRL_EF_IF_PGENB
#define EF_CTRL_EF_IF_PGENB_POS              (13U)
#define EF_CTRL_EF_IF_PGENB_LEN              (1U)
#define EF_CTRL_EF_IF_PGENB_MASK             (((1U << EF_CTRL_EF_IF_PGENB_LEN) - 1) << EF_CTRL_EF_IF_PGENB_POS)
#define EF_CTRL_EF_IF_PGENB_UMASK            (~(((1U << EF_CTRL_EF_IF_PGENB_LEN) - 1) << EF_CTRL_EF_IF_PGENB_POS))
#define EF_CTRL_EF_IF_LOAD                   EF_CTRL_EF_IF_LOAD
#define EF_CTRL_EF_IF_LOAD_POS               (14U)
#define EF_CTRL_EF_IF_LOAD_LEN               (1U)
#define EF_CTRL_EF_IF_LOAD_MASK              (((1U << EF_CTRL_EF_IF_LOAD_LEN) - 1) << EF_CTRL_EF_IF_LOAD_POS)
#define EF_CTRL_EF_IF_LOAD_UMASK             (~(((1U << EF_CTRL_EF_IF_LOAD_LEN) - 1) << EF_CTRL_EF_IF_LOAD_POS))
#define EF_CTRL_EF_IF_CSB                    EF_CTRL_EF_IF_CSB
#define EF_CTRL_EF_IF_CSB_POS                (15U)
#define EF_CTRL_EF_IF_CSB_LEN                (1U)
#define EF_CTRL_EF_IF_CSB_MASK               (((1U << EF_CTRL_EF_IF_CSB_LEN) - 1) << EF_CTRL_EF_IF_CSB_POS)
#define EF_CTRL_EF_IF_CSB_UMASK              (~(((1U << EF_CTRL_EF_IF_CSB_LEN) - 1) << EF_CTRL_EF_IF_CSB_POS))
#define EF_CTRL_EF_IF_0_Q                    EF_CTRL_EF_IF_0_Q
#define EF_CTRL_EF_IF_0_Q_POS                (16U)
#define EF_CTRL_EF_IF_0_Q_LEN                (8U)
#define EF_CTRL_EF_IF_0_Q_MASK               (((1U << EF_CTRL_EF_IF_0_Q_LEN) - 1) << EF_CTRL_EF_IF_0_Q_POS)
#define EF_CTRL_EF_IF_0_Q_UMASK              (~(((1U << EF_CTRL_EF_IF_0_Q_LEN) - 1) << EF_CTRL_EF_IF_0_Q_POS))
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL       EF_CTRL_EF_IF_PROT_CODE_MANUAL
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_POS   (24U)
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_LEN   (8U)
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_MASK  (((1U << EF_CTRL_EF_IF_PROT_CODE_MANUAL_LEN) - 1) << EF_CTRL_EF_IF_PROT_CODE_MANUAL_POS)
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_UMASK (~(((1U << EF_CTRL_EF_IF_PROT_CODE_MANUAL_LEN) - 1) << EF_CTRL_EF_IF_PROT_CODE_MANUAL_POS))
#else
/* 0x80C : ef_if_0_manual_0 */
#define EF_CTRL_EF_IF_0_MANUAL_0_OFFSET      (0x80C)
#define EF_CTRL_EF_IF_A                      EF_CTRL_EF_IF_A
#define EF_CTRL_EF_IF_A_POS                  (0U)
#define EF_CTRL_EF_IF_A_LEN                  (12U)
#define EF_CTRL_EF_IF_A_MASK                 (((1U << EF_CTRL_EF_IF_A_LEN) - 1) << EF_CTRL_EF_IF_A_POS)
#define EF_CTRL_EF_IF_A_UMASK                (~(((1U << EF_CTRL_EF_IF_A_LEN) - 1) << EF_CTRL_EF_IF_A_POS))
#define EF_CTRL_EF_IF_PD                     EF_CTRL_EF_IF_PD
#define EF_CTRL_EF_IF_PD_POS                 (18U)
#define EF_CTRL_EF_IF_PD_LEN                 (1U)
#define EF_CTRL_EF_IF_PD_MASK                (((1U << EF_CTRL_EF_IF_PD_LEN) - 1) << EF_CTRL_EF_IF_PD_POS)
#define EF_CTRL_EF_IF_PD_UMASK               (~(((1U << EF_CTRL_EF_IF_PD_LEN) - 1) << EF_CTRL_EF_IF_PD_POS))
#define EF_CTRL_EF_IF_PS                     EF_CTRL_EF_IF_PS
#define EF_CTRL_EF_IF_PS_POS                 (19U)
#define EF_CTRL_EF_IF_PS_LEN                 (1U)
#define EF_CTRL_EF_IF_PS_MASK                (((1U << EF_CTRL_EF_IF_PS_LEN) - 1) << EF_CTRL_EF_IF_PS_POS)
#define EF_CTRL_EF_IF_PS_UMASK               (~(((1U << EF_CTRL_EF_IF_PS_LEN) - 1) << EF_CTRL_EF_IF_PS_POS))
#define EF_CTRL_EF_IF_STROBE                 EF_CTRL_EF_IF_STROBE
#define EF_CTRL_EF_IF_STROBE_POS             (20U)
#define EF_CTRL_EF_IF_STROBE_LEN             (1U)
#define EF_CTRL_EF_IF_STROBE_MASK            (((1U << EF_CTRL_EF_IF_STROBE_LEN) - 1) << EF_CTRL_EF_IF_STROBE_POS)
#define EF_CTRL_EF_IF_STROBE_UMASK           (~(((1U << EF_CTRL_EF_IF_STROBE_LEN) - 1) << EF_CTRL_EF_IF_STROBE_POS))
#define EF_CTRL_EF_IF_PGENB                  EF_CTRL_EF_IF_PGENB
#define EF_CTRL_EF_IF_PGENB_POS              (21U)
#define EF_CTRL_EF_IF_PGENB_LEN              (1U)
#define EF_CTRL_EF_IF_PGENB_MASK             (((1U << EF_CTRL_EF_IF_PGENB_LEN) - 1) << EF_CTRL_EF_IF_PGENB_POS)
#define EF_CTRL_EF_IF_PGENB_UMASK            (~(((1U << EF_CTRL_EF_IF_PGENB_LEN) - 1) << EF_CTRL_EF_IF_PGENB_POS))
#define EF_CTRL_EF_IF_LOAD                   EF_CTRL_EF_IF_LOAD
#define EF_CTRL_EF_IF_LOAD_POS               (22U)
#define EF_CTRL_EF_IF_LOAD_LEN               (1U)
#define EF_CTRL_EF_IF_LOAD_MASK              (((1U << EF_CTRL_EF_IF_LOAD_LEN) - 1) << EF_CTRL_EF_IF_LOAD_POS)
#define EF_CTRL_EF_IF_LOAD_UMASK             (~(((1U << EF_CTRL_EF_IF_LOAD_LEN) - 1) << EF_CTRL_EF_IF_LOAD_POS))
#define EF_CTRL_EF_IF_CSB                    EF_CTRL_EF_IF_CSB
#define EF_CTRL_EF_IF_CSB_POS                (23U)
#define EF_CTRL_EF_IF_CSB_LEN                (1U)
#define EF_CTRL_EF_IF_CSB_MASK               (((1U << EF_CTRL_EF_IF_CSB_LEN) - 1) << EF_CTRL_EF_IF_CSB_POS)
#define EF_CTRL_EF_IF_CSB_UMASK              (~(((1U << EF_CTRL_EF_IF_CSB_LEN) - 1) << EF_CTRL_EF_IF_CSB_POS))
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL       EF_CTRL_EF_IF_PROT_CODE_MANUAL
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_POS   (24U)
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_LEN   (8U)
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_MASK  (((1U << EF_CTRL_EF_IF_PROT_CODE_MANUAL_LEN) - 1) << EF_CTRL_EF_IF_PROT_CODE_MANUAL_POS)
#define EF_CTRL_EF_IF_PROT_CODE_MANUAL_UMASK (~(((1U << EF_CTRL_EF_IF_PROT_CODE_MANUAL_LEN) - 1) << EF_CTRL_EF_IF_PROT_CODE_MANUAL_POS))
#endif

#if defined(BL606P) || defined(BL808)
/* 0x900 : ef_if_ctrl_1 */
#define EF_CTRL_EF_IF_CTRL_1_OFFSET      (0x900)
#define EF_CTRL_EF_IF_1_BUSY             EF_CTRL_EF_IF_1_BUSY
#define EF_CTRL_EF_IF_1_BUSY_POS         (2U)
#define EF_CTRL_EF_IF_1_BUSY_LEN         (1U)
#define EF_CTRL_EF_IF_1_BUSY_MASK        (((1U << EF_CTRL_EF_IF_1_BUSY_LEN) - 1) << EF_CTRL_EF_IF_1_BUSY_POS)
#define EF_CTRL_EF_IF_1_BUSY_UMASK       (~(((1U << EF_CTRL_EF_IF_1_BUSY_LEN) - 1) << EF_CTRL_EF_IF_1_BUSY_POS))
#define EF_CTRL_EF_IF_1_RW               EF_CTRL_EF_IF_1_RW
#define EF_CTRL_EF_IF_1_RW_POS           (3U)
#define EF_CTRL_EF_IF_1_RW_LEN           (1U)
#define EF_CTRL_EF_IF_1_RW_MASK          (((1U << EF_CTRL_EF_IF_1_RW_LEN) - 1) << EF_CTRL_EF_IF_1_RW_POS)
#define EF_CTRL_EF_IF_1_RW_UMASK         (~(((1U << EF_CTRL_EF_IF_1_RW_LEN) - 1) << EF_CTRL_EF_IF_1_RW_POS))
#define EF_CTRL_EF_IF_1_TRIG             EF_CTRL_EF_IF_1_TRIG
#define EF_CTRL_EF_IF_1_TRIG_POS         (4U)
#define EF_CTRL_EF_IF_1_TRIG_LEN         (1U)
#define EF_CTRL_EF_IF_1_TRIG_MASK        (((1U << EF_CTRL_EF_IF_1_TRIG_LEN) - 1) << EF_CTRL_EF_IF_1_TRIG_POS)
#define EF_CTRL_EF_IF_1_TRIG_UMASK       (~(((1U << EF_CTRL_EF_IF_1_TRIG_LEN) - 1) << EF_CTRL_EF_IF_1_TRIG_POS))
#define EF_CTRL_EF_IF_1_MANUAL_EN        EF_CTRL_EF_IF_1_MANUAL_EN
#define EF_CTRL_EF_IF_1_MANUAL_EN_POS    (5U)
#define EF_CTRL_EF_IF_1_MANUAL_EN_LEN    (1U)
#define EF_CTRL_EF_IF_1_MANUAL_EN_MASK   (((1U << EF_CTRL_EF_IF_1_MANUAL_EN_LEN) - 1) << EF_CTRL_EF_IF_1_MANUAL_EN_POS)
#define EF_CTRL_EF_IF_1_MANUAL_EN_UMASK  (~(((1U << EF_CTRL_EF_IF_1_MANUAL_EN_LEN) - 1) << EF_CTRL_EF_IF_1_MANUAL_EN_POS))
#define EF_CTRL_EF_IF_1_CYC_MODIFY       EF_CTRL_EF_IF_1_CYC_MODIFY
#define EF_CTRL_EF_IF_1_CYC_MODIFY_POS   (6U)
#define EF_CTRL_EF_IF_1_CYC_MODIFY_LEN   (1U)
#define EF_CTRL_EF_IF_1_CYC_MODIFY_MASK  (((1U << EF_CTRL_EF_IF_1_CYC_MODIFY_LEN) - 1) << EF_CTRL_EF_IF_1_CYC_MODIFY_POS)
#define EF_CTRL_EF_IF_1_CYC_MODIFY_UMASK (~(((1U << EF_CTRL_EF_IF_1_CYC_MODIFY_LEN) - 1) << EF_CTRL_EF_IF_1_CYC_MODIFY_POS))
#define EF_CTRL_EF_IF_1_INT              EF_CTRL_EF_IF_1_INT
#define EF_CTRL_EF_IF_1_INT_POS          (20U)
#define EF_CTRL_EF_IF_1_INT_LEN          (1U)
#define EF_CTRL_EF_IF_1_INT_MASK         (((1U << EF_CTRL_EF_IF_1_INT_LEN) - 1) << EF_CTRL_EF_IF_1_INT_POS)
#define EF_CTRL_EF_IF_1_INT_UMASK        (~(((1U << EF_CTRL_EF_IF_1_INT_LEN) - 1) << EF_CTRL_EF_IF_1_INT_POS))
#define EF_CTRL_EF_IF_1_INT_CLR          EF_CTRL_EF_IF_1_INT_CLR
#define EF_CTRL_EF_IF_1_INT_CLR_POS      (21U)
#define EF_CTRL_EF_IF_1_INT_CLR_LEN      (1U)
#define EF_CTRL_EF_IF_1_INT_CLR_MASK     (((1U << EF_CTRL_EF_IF_1_INT_CLR_LEN) - 1) << EF_CTRL_EF_IF_1_INT_CLR_POS)
#define EF_CTRL_EF_IF_1_INT_CLR_UMASK    (~(((1U << EF_CTRL_EF_IF_1_INT_CLR_LEN) - 1) << EF_CTRL_EF_IF_1_INT_CLR_POS))
#define EF_CTRL_EF_IF_1_INT_SET          EF_CTRL_EF_IF_1_INT_SET
#define EF_CTRL_EF_IF_1_INT_SET_POS      (22U)
#define EF_CTRL_EF_IF_1_INT_SET_LEN      (1U)
#define EF_CTRL_EF_IF_1_INT_SET_MASK     (((1U << EF_CTRL_EF_IF_1_INT_SET_LEN) - 1) << EF_CTRL_EF_IF_1_INT_SET_POS)
#define EF_CTRL_EF_IF_1_INT_SET_UMASK    (~(((1U << EF_CTRL_EF_IF_1_INT_SET_LEN) - 1) << EF_CTRL_EF_IF_1_INT_SET_POS))

/* 0x904 : ef_if_1_manual */
#define EF_CTRL_EF_IF_1_MANUAL_OFFSET (0x904)
#define EF_CTRL_EF_IF_1_Q             EF_CTRL_EF_IF_1_Q
#define EF_CTRL_EF_IF_1_Q_POS         (16U)
#define EF_CTRL_EF_IF_1_Q_LEN         (8U)
#define EF_CTRL_EF_IF_1_Q_MASK        (((1U << EF_CTRL_EF_IF_1_Q_LEN) - 1) << EF_CTRL_EF_IF_1_Q_POS)
#define EF_CTRL_EF_IF_1_Q_UMASK       (~(((1U << EF_CTRL_EF_IF_1_Q_LEN) - 1) << EF_CTRL_EF_IF_1_Q_POS))

/* 0x908 : ef_if_1_status */
#define EF_CTRL_EF_IF_1_STATUS_OFFSET (0x908)
#define EF_CTRL_EF_IF_1_STATUS        EF_CTRL_EF_IF_1_STATUS
#define EF_CTRL_EF_IF_1_STATUS_POS    (0U)
#define EF_CTRL_EF_IF_1_STATUS_LEN    (32U)
#define EF_CTRL_EF_IF_1_STATUS_MASK   (((1U << EF_CTRL_EF_IF_1_STATUS_LEN) - 1) << EF_CTRL_EF_IF_1_STATUS_POS)
#define EF_CTRL_EF_IF_1_STATUS_UMASK  (~(((1U << EF_CTRL_EF_IF_1_STATUS_LEN) - 1) << EF_CTRL_EF_IF_1_STATUS_POS))
#endif

#endif /* __HARDWARE_EF_CTRL_H__ */
