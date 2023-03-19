/**
  ******************************************************************************
  * @file    mcu_misc_reg.h
  * @version V1.0
  * @date    2021-07-12
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
#ifndef __MCU_MISC_REG_H__
#define __MCU_MISC_REG_H__

#include "bl808.h"

/* 0x0 : mcu_bus_cfg0 */
#define MCU_MISC_MCU_BUS_CFG0_OFFSET            (0x0)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN       MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_POS   (0U)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_LEN   (1U)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_MSK   (((1U << MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_LEN) - 1) << MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_POS)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_UMSK  (~(((1U << MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_LEN) - 1) << MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_POS))
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR      MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_POS  (1U)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_LEN  (1U)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_MSK  (((1U << MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_LEN) - 1) << MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_POS)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_UMSK (~(((1U << MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_LEN) - 1) << MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_POS))
#define MCU_MISC_STS_MCU_INFRA_TIMEOUT          MCU_MISC_STS_MCU_INFRA_TIMEOUT
#define MCU_MISC_STS_MCU_INFRA_TIMEOUT_POS      (16U)
#define MCU_MISC_STS_MCU_INFRA_TIMEOUT_LEN      (1U)
#define MCU_MISC_STS_MCU_INFRA_TIMEOUT_MSK      (((1U << MCU_MISC_STS_MCU_INFRA_TIMEOUT_LEN) - 1) << MCU_MISC_STS_MCU_INFRA_TIMEOUT_POS)
#define MCU_MISC_STS_MCU_INFRA_TIMEOUT_UMSK     (~(((1U << MCU_MISC_STS_MCU_INFRA_TIMEOUT_LEN) - 1) << MCU_MISC_STS_MCU_INFRA_TIMEOUT_POS))

/* 0x4 : mcu_bus_cfg1 */
#define MCU_MISC_MCU_BUS_CFG1_OFFSET         (0x4)
#define MCU_MISC_REG_MCU1_HQOS               MCU_MISC_REG_MCU1_HQOS
#define MCU_MISC_REG_MCU1_HQOS_POS           (0U)
#define MCU_MISC_REG_MCU1_HQOS_LEN           (1U)
#define MCU_MISC_REG_MCU1_HQOS_MSK           (((1U << MCU_MISC_REG_MCU1_HQOS_LEN) - 1) << MCU_MISC_REG_MCU1_HQOS_POS)
#define MCU_MISC_REG_MCU1_HQOS_UMSK          (~(((1U << MCU_MISC_REG_MCU1_HQOS_LEN) - 1) << MCU_MISC_REG_MCU1_HQOS_POS))
#define MCU_MISC_REG_MCU1_AWQOS              MCU_MISC_REG_MCU1_AWQOS
#define MCU_MISC_REG_MCU1_AWQOS_POS          (1U)
#define MCU_MISC_REG_MCU1_AWQOS_LEN          (1U)
#define MCU_MISC_REG_MCU1_AWQOS_MSK          (((1U << MCU_MISC_REG_MCU1_AWQOS_LEN) - 1) << MCU_MISC_REG_MCU1_AWQOS_POS)
#define MCU_MISC_REG_MCU1_AWQOS_UMSK         (~(((1U << MCU_MISC_REG_MCU1_AWQOS_LEN) - 1) << MCU_MISC_REG_MCU1_AWQOS_POS))
#define MCU_MISC_REG_MCU1_ARQOS              MCU_MISC_REG_MCU1_ARQOS
#define MCU_MISC_REG_MCU1_ARQOS_POS          (2U)
#define MCU_MISC_REG_MCU1_ARQOS_LEN          (1U)
#define MCU_MISC_REG_MCU1_ARQOS_MSK          (((1U << MCU_MISC_REG_MCU1_ARQOS_LEN) - 1) << MCU_MISC_REG_MCU1_ARQOS_POS)
#define MCU_MISC_REG_MCU1_ARQOS_UMSK         (~(((1U << MCU_MISC_REG_MCU1_ARQOS_LEN) - 1) << MCU_MISC_REG_MCU1_ARQOS_POS))
#define MCU_MISC_REG_MCU_X2HS_SP_BYPASS      MCU_MISC_REG_MCU_X2HS_SP_BYPASS
#define MCU_MISC_REG_MCU_X2HS_SP_BYPASS_POS  (3U)
#define MCU_MISC_REG_MCU_X2HS_SP_BYPASS_LEN  (1U)
#define MCU_MISC_REG_MCU_X2HS_SP_BYPASS_MSK  (((1U << MCU_MISC_REG_MCU_X2HS_SP_BYPASS_LEN) - 1) << MCU_MISC_REG_MCU_X2HS_SP_BYPASS_POS)
#define MCU_MISC_REG_MCU_X2HS_SP_BYPASS_UMSK (~(((1U << MCU_MISC_REG_MCU_X2HS_SP_BYPASS_LEN) - 1) << MCU_MISC_REG_MCU_X2HS_SP_BYPASS_POS))
#define MCU_MISC_REG_X_WTHRE_MCU2EXT         MCU_MISC_REG_X_WTHRE_MCU2EXT
#define MCU_MISC_REG_X_WTHRE_MCU2EXT_POS     (7U)
#define MCU_MISC_REG_X_WTHRE_MCU2EXT_LEN     (2U)
#define MCU_MISC_REG_X_WTHRE_MCU2EXT_MSK     (((1U << MCU_MISC_REG_X_WTHRE_MCU2EXT_LEN) - 1) << MCU_MISC_REG_X_WTHRE_MCU2EXT_POS)
#define MCU_MISC_REG_X_WTHRE_MCU2EXT_UMSK    (~(((1U << MCU_MISC_REG_X_WTHRE_MCU2EXT_LEN) - 1) << MCU_MISC_REG_X_WTHRE_MCU2EXT_POS))
#define MCU_MISC_REG_MCU_INFRA_ARB_MODE      MCU_MISC_REG_MCU_INFRA_ARB_MODE
#define MCU_MISC_REG_MCU_INFRA_ARB_MODE_POS  (16U)
#define MCU_MISC_REG_MCU_INFRA_ARB_MODE_LEN  (1U)
#define MCU_MISC_REG_MCU_INFRA_ARB_MODE_MSK  (((1U << MCU_MISC_REG_MCU_INFRA_ARB_MODE_LEN) - 1) << MCU_MISC_REG_MCU_INFRA_ARB_MODE_POS)
#define MCU_MISC_REG_MCU_INFRA_ARB_MODE_UMSK (~(((1U << MCU_MISC_REG_MCU_INFRA_ARB_MODE_LEN) - 1) << MCU_MISC_REG_MCU_INFRA_ARB_MODE_POS))

/* 0x14 : mcu_e907_rtc */
#define MCU_MISC_MCU_E907_RTC_OFFSET  (0x14)
#define MCU_MISC_REG_MCU_RTC_DIV      MCU_MISC_REG_MCU_RTC_DIV
#define MCU_MISC_REG_MCU_RTC_DIV_POS  (0U)
#define MCU_MISC_REG_MCU_RTC_DIV_LEN  (10U)
#define MCU_MISC_REG_MCU_RTC_DIV_MSK  (((1U << MCU_MISC_REG_MCU_RTC_DIV_LEN) - 1) << MCU_MISC_REG_MCU_RTC_DIV_POS)
#define MCU_MISC_REG_MCU_RTC_DIV_UMSK (~(((1U << MCU_MISC_REG_MCU_RTC_DIV_LEN) - 1) << MCU_MISC_REG_MCU_RTC_DIV_POS))
#define MCU_MISC_REG_MCU_RTC_RST      MCU_MISC_REG_MCU_RTC_RST
#define MCU_MISC_REG_MCU_RTC_RST_POS  (30U)
#define MCU_MISC_REG_MCU_RTC_RST_LEN  (1U)
#define MCU_MISC_REG_MCU_RTC_RST_MSK  (((1U << MCU_MISC_REG_MCU_RTC_RST_LEN) - 1) << MCU_MISC_REG_MCU_RTC_RST_POS)
#define MCU_MISC_REG_MCU_RTC_RST_UMSK (~(((1U << MCU_MISC_REG_MCU_RTC_RST_LEN) - 1) << MCU_MISC_REG_MCU_RTC_RST_POS))
#define MCU_MISC_REG_MCU_RTC_EN       MCU_MISC_REG_MCU_RTC_EN
#define MCU_MISC_REG_MCU_RTC_EN_POS   (31U)
#define MCU_MISC_REG_MCU_RTC_EN_LEN   (1U)
#define MCU_MISC_REG_MCU_RTC_EN_MSK   (((1U << MCU_MISC_REG_MCU_RTC_EN_LEN) - 1) << MCU_MISC_REG_MCU_RTC_EN_POS)
#define MCU_MISC_REG_MCU_RTC_EN_UMSK  (~(((1U << MCU_MISC_REG_MCU_RTC_EN_LEN) - 1) << MCU_MISC_REG_MCU_RTC_EN_POS))

/* 0x100 : mcu_cfg1 */
#define MCU_MISC_MCU_CFG1_OFFSET        (0x100)
#define MCU_MISC_REG_MCU1_DFS_REQ       MCU_MISC_REG_MCU1_DFS_REQ
#define MCU_MISC_REG_MCU1_DFS_REQ_POS   (0U)
#define MCU_MISC_REG_MCU1_DFS_REQ_LEN   (1U)
#define MCU_MISC_REG_MCU1_DFS_REQ_MSK   (((1U << MCU_MISC_REG_MCU1_DFS_REQ_LEN) - 1) << MCU_MISC_REG_MCU1_DFS_REQ_POS)
#define MCU_MISC_REG_MCU1_DFS_REQ_UMSK  (~(((1U << MCU_MISC_REG_MCU1_DFS_REQ_LEN) - 1) << MCU_MISC_REG_MCU1_DFS_REQ_POS))
#define MCU_MISC_STS_MCU1_DFS_ACK       MCU_MISC_STS_MCU1_DFS_ACK
#define MCU_MISC_STS_MCU1_DFS_ACK_POS   (2U)
#define MCU_MISC_STS_MCU1_DFS_ACK_LEN   (1U)
#define MCU_MISC_STS_MCU1_DFS_ACK_MSK   (((1U << MCU_MISC_STS_MCU1_DFS_ACK_LEN) - 1) << MCU_MISC_STS_MCU1_DFS_ACK_POS)
#define MCU_MISC_STS_MCU1_DFS_ACK_UMSK  (~(((1U << MCU_MISC_STS_MCU1_DFS_ACK_LEN) - 1) << MCU_MISC_STS_MCU1_DFS_ACK_POS))
#define MCU_MISC_REG_MCU1_SRST_EN       MCU_MISC_REG_MCU1_SRST_EN
#define MCU_MISC_REG_MCU1_SRST_EN_POS   (4U)
#define MCU_MISC_REG_MCU1_SRST_EN_LEN   (2U)
#define MCU_MISC_REG_MCU1_SRST_EN_MSK   (((1U << MCU_MISC_REG_MCU1_SRST_EN_LEN) - 1) << MCU_MISC_REG_MCU1_SRST_EN_POS)
#define MCU_MISC_REG_MCU1_SRST_EN_UMSK  (~(((1U << MCU_MISC_REG_MCU1_SRST_EN_LEN) - 1) << MCU_MISC_REG_MCU1_SRST_EN_POS))
#define MCU_MISC_STS_MCU1_LPMD_B        MCU_MISC_STS_MCU1_LPMD_B
#define MCU_MISC_STS_MCU1_LPMD_B_POS    (10U)
#define MCU_MISC_STS_MCU1_LPMD_B_LEN    (2U)
#define MCU_MISC_STS_MCU1_LPMD_B_MSK    (((1U << MCU_MISC_STS_MCU1_LPMD_B_LEN) - 1) << MCU_MISC_STS_MCU1_LPMD_B_POS)
#define MCU_MISC_STS_MCU1_LPMD_B_UMSK   (~(((1U << MCU_MISC_STS_MCU1_LPMD_B_LEN) - 1) << MCU_MISC_STS_MCU1_LPMD_B_POS))
#define MCU_MISC_MCU1_WFI_FORCE         MCU_MISC_MCU1_WFI_FORCE
#define MCU_MISC_MCU1_WFI_FORCE_POS     (16U)
#define MCU_MISC_MCU1_WFI_FORCE_LEN     (1U)
#define MCU_MISC_MCU1_WFI_FORCE_MSK     (((1U << MCU_MISC_MCU1_WFI_FORCE_LEN) - 1) << MCU_MISC_MCU1_WFI_FORCE_POS)
#define MCU_MISC_MCU1_WFI_FORCE_UMSK    (~(((1U << MCU_MISC_MCU1_WFI_FORCE_LEN) - 1) << MCU_MISC_MCU1_WFI_FORCE_POS))
#define MCU_MISC_MCU1_NDM_RSTN_EN       MCU_MISC_MCU1_NDM_RSTN_EN
#define MCU_MISC_MCU1_NDM_RSTN_EN_POS   (28U)
#define MCU_MISC_MCU1_NDM_RSTN_EN_LEN   (1U)
#define MCU_MISC_MCU1_NDM_RSTN_EN_MSK   (((1U << MCU_MISC_MCU1_NDM_RSTN_EN_LEN) - 1) << MCU_MISC_MCU1_NDM_RSTN_EN_POS)
#define MCU_MISC_MCU1_NDM_RSTN_EN_UMSK  (~(((1U << MCU_MISC_MCU1_NDM_RSTN_EN_LEN) - 1) << MCU_MISC_MCU1_NDM_RSTN_EN_POS))
#define MCU_MISC_MCU1_HART_RSTN_EN      MCU_MISC_MCU1_HART_RSTN_EN
#define MCU_MISC_MCU1_HART_RSTN_EN_POS  (29U)
#define MCU_MISC_MCU1_HART_RSTN_EN_LEN  (1U)
#define MCU_MISC_MCU1_HART_RSTN_EN_MSK  (((1U << MCU_MISC_MCU1_HART_RSTN_EN_LEN) - 1) << MCU_MISC_MCU1_HART_RSTN_EN_POS)
#define MCU_MISC_MCU1_HART_RSTN_EN_UMSK (~(((1U << MCU_MISC_MCU1_HART_RSTN_EN_LEN) - 1) << MCU_MISC_MCU1_HART_RSTN_EN_POS))

/* 0x110 : mcu1_log1 */
#define MCU_MISC_MCU1_LOG1_OFFSET     (0x110)
#define MCU_MISC_STS_MCU1_MCAUSE      MCU_MISC_STS_MCU1_MCAUSE
#define MCU_MISC_STS_MCU1_MCAUSE_POS  (0U)
#define MCU_MISC_STS_MCU1_MCAUSE_LEN  (32U)
#define MCU_MISC_STS_MCU1_MCAUSE_MSK  (((1U << MCU_MISC_STS_MCU1_MCAUSE_LEN) - 1) << MCU_MISC_STS_MCU1_MCAUSE_POS)
#define MCU_MISC_STS_MCU1_MCAUSE_UMSK (~(((1U << MCU_MISC_STS_MCU1_MCAUSE_LEN) - 1) << MCU_MISC_STS_MCU1_MCAUSE_POS))

/* 0x114 : mcu1_log2 */
#define MCU_MISC_MCU1_LOG2_OFFSET         (0x114)
#define MCU_MISC_STS_MCU1_MINTSTATUS      MCU_MISC_STS_MCU1_MINTSTATUS
#define MCU_MISC_STS_MCU1_MINTSTATUS_POS  (0U)
#define MCU_MISC_STS_MCU1_MINTSTATUS_LEN  (32U)
#define MCU_MISC_STS_MCU1_MINTSTATUS_MSK  (((1U << MCU_MISC_STS_MCU1_MINTSTATUS_LEN) - 1) << MCU_MISC_STS_MCU1_MINTSTATUS_POS)
#define MCU_MISC_STS_MCU1_MINTSTATUS_UMSK (~(((1U << MCU_MISC_STS_MCU1_MINTSTATUS_LEN) - 1) << MCU_MISC_STS_MCU1_MINTSTATUS_POS))

/* 0x118 : mcu1_log3 */
#define MCU_MISC_MCU1_LOG3_OFFSET      (0x118)
#define MCU_MISC_STS_MCU1_MSTATUS      MCU_MISC_STS_MCU1_MSTATUS
#define MCU_MISC_STS_MCU1_MSTATUS_POS  (0U)
#define MCU_MISC_STS_MCU1_MSTATUS_LEN  (32U)
#define MCU_MISC_STS_MCU1_MSTATUS_MSK  (((1U << MCU_MISC_STS_MCU1_MSTATUS_LEN) - 1) << MCU_MISC_STS_MCU1_MSTATUS_POS)
#define MCU_MISC_STS_MCU1_MSTATUS_UMSK (~(((1U << MCU_MISC_STS_MCU1_MSTATUS_LEN) - 1) << MCU_MISC_STS_MCU1_MSTATUS_POS))

/* 0x11C : mcu1_log4 */
#define MCU_MISC_MCU1_LOG4_OFFSET (0x11C)
#define MCU_MISC_STS_MCU1_SP      MCU_MISC_STS_MCU1_SP
#define MCU_MISC_STS_MCU1_SP_POS  (0U)
#define MCU_MISC_STS_MCU1_SP_LEN  (1U)
#define MCU_MISC_STS_MCU1_SP_MSK  (((1U << MCU_MISC_STS_MCU1_SP_LEN) - 1) << MCU_MISC_STS_MCU1_SP_POS)
#define MCU_MISC_STS_MCU1_SP_UMSK (~(((1U << MCU_MISC_STS_MCU1_SP_LEN) - 1) << MCU_MISC_STS_MCU1_SP_POS))
#define MCU_MISC_STS_MCU1_PC      MCU_MISC_STS_MCU1_PC
#define MCU_MISC_STS_MCU1_PC_POS  (1U)
#define MCU_MISC_STS_MCU1_PC_LEN  (31U)
#define MCU_MISC_STS_MCU1_PC_MSK  (((1U << MCU_MISC_STS_MCU1_PC_LEN) - 1) << MCU_MISC_STS_MCU1_PC_POS)
#define MCU_MISC_STS_MCU1_PC_UMSK (~(((1U << MCU_MISC_STS_MCU1_PC_LEN) - 1) << MCU_MISC_STS_MCU1_PC_POS))

/* 0x120 : mcu1_log5 */
#define MCU_MISC_MCU1_LOG5_OFFSET        (0x120)
#define MCU_MISC_STS_MCU1_LOCKUP         MCU_MISC_STS_MCU1_LOCKUP
#define MCU_MISC_STS_MCU1_LOCKUP_POS     (24U)
#define MCU_MISC_STS_MCU1_LOCKUP_LEN     (1U)
#define MCU_MISC_STS_MCU1_LOCKUP_MSK     (((1U << MCU_MISC_STS_MCU1_LOCKUP_LEN) - 1) << MCU_MISC_STS_MCU1_LOCKUP_POS)
#define MCU_MISC_STS_MCU1_LOCKUP_UMSK    (~(((1U << MCU_MISC_STS_MCU1_LOCKUP_LEN) - 1) << MCU_MISC_STS_MCU1_LOCKUP_POS))
#define MCU_MISC_STS_MCU1_HALTED         MCU_MISC_STS_MCU1_HALTED
#define MCU_MISC_STS_MCU1_HALTED_POS     (25U)
#define MCU_MISC_STS_MCU1_HALTED_LEN     (1U)
#define MCU_MISC_STS_MCU1_HALTED_MSK     (((1U << MCU_MISC_STS_MCU1_HALTED_LEN) - 1) << MCU_MISC_STS_MCU1_HALTED_POS)
#define MCU_MISC_STS_MCU1_HALTED_UMSK    (~(((1U << MCU_MISC_STS_MCU1_HALTED_LEN) - 1) << MCU_MISC_STS_MCU1_HALTED_POS))
#define MCU_MISC_MCU1_NDM_RSTN_REQ       MCU_MISC_MCU1_NDM_RSTN_REQ
#define MCU_MISC_MCU1_NDM_RSTN_REQ_POS   (28U)
#define MCU_MISC_MCU1_NDM_RSTN_REQ_LEN   (1U)
#define MCU_MISC_MCU1_NDM_RSTN_REQ_MSK   (((1U << MCU_MISC_MCU1_NDM_RSTN_REQ_LEN) - 1) << MCU_MISC_MCU1_NDM_RSTN_REQ_POS)
#define MCU_MISC_MCU1_NDM_RSTN_REQ_UMSK  (~(((1U << MCU_MISC_MCU1_NDM_RSTN_REQ_LEN) - 1) << MCU_MISC_MCU1_NDM_RSTN_REQ_POS))
#define MCU_MISC_MCU1_HART_RSTN_REQ      MCU_MISC_MCU1_HART_RSTN_REQ
#define MCU_MISC_MCU1_HART_RSTN_REQ_POS  (29U)
#define MCU_MISC_MCU1_HART_RSTN_REQ_LEN  (1U)
#define MCU_MISC_MCU1_HART_RSTN_REQ_MSK  (((1U << MCU_MISC_MCU1_HART_RSTN_REQ_LEN) - 1) << MCU_MISC_MCU1_HART_RSTN_REQ_POS)
#define MCU_MISC_MCU1_HART_RSTN_REQ_UMSK (~(((1U << MCU_MISC_MCU1_HART_RSTN_REQ_LEN) - 1) << MCU_MISC_MCU1_HART_RSTN_REQ_POS))

/* 0x208 : irom1_misr_dataout_0 */
#define MCU_MISC_IROM1_MISR_DATAOUT_0_OFFSET (0x208)

/* 0x20C : irom1_misr_dataout_1 */
#define MCU_MISC_IROM1_MISR_DATAOUT_1_OFFSET (0x20C)

struct mcu_misc_reg {
    /* 0x0 : mcu_bus_cfg0 */
    union {
        struct {
            uint32_t reg_mcu_infra_timeout_en  : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reg_mcu_infra_timeout_clr : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_15             : 14; /* [15: 2],       rsvd,        0x0 */
            uint32_t sts_mcu_infra_timeout     : 1;  /* [   16],          r,        0x0 */
            uint32_t reserved_17_31            : 15; /* [31:17],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mcu_bus_cfg0;

    /* 0x4 : mcu_bus_cfg1 */
    union {
        struct {
            uint32_t reg_mcu1_hqos          : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reg_mcu1_awqos         : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reg_mcu1_arqos         : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reg_mcu_x2hs_sp_bypass : 1;  /* [    3],        r/w,        0x0 */
            uint32_t reserved_4_6           : 3;  /* [ 6: 4],       rsvd,        0x0 */
            uint32_t reg_x_wthre_mcu2ext    : 2;  /* [ 8: 7],        r/w,        0x0 */
            uint32_t reserved_9_15          : 7;  /* [15: 9],       rsvd,        0x0 */
            uint32_t reg_mcu_infra_arb_mode : 1;  /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31         : 15; /* [31:17],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mcu_bus_cfg1;

    /* 0x8  reserved */
    uint8_t RESERVED0x8[12];

    /* 0x14 : mcu_e907_rtc */
    union {
        struct {
            uint32_t reg_mcu_rtc_div : 10; /* [ 9: 0],        r/w,        0xa */
            uint32_t reserved_10_29  : 20; /* [29:10],       rsvd,        0x0 */
            uint32_t reg_mcu_rtc_rst : 1;  /* [   30],        r/w,        0x0 */
            uint32_t reg_mcu_rtc_en  : 1;  /* [   31],        r/w,        0x1 */
        } BF;
        uint32_t WORD;
    } mcu_e907_rtc;

    /* 0x18  reserved */
    uint8_t RESERVED0x18[232];

    /* 0x100 : mcu_cfg1 */
    union {
        struct {
            uint32_t reg_mcu1_dfs_req  : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1        : 1;  /* [    1],       rsvd,        0x0 */
            uint32_t sts_mcu1_dfs_ack  : 1;  /* [    2],          r,        0x0 */
            uint32_t reserved_3        : 1;  /* [    3],       rsvd,        0x0 */
            uint32_t reg_mcu1_srst_en  : 2;  /* [ 5: 4],        r/w,        0x3 */
            uint32_t reserved_6_9      : 4;  /* [ 9: 6],       rsvd,        0x0 */
            uint32_t sts_mcu1_lpmd_b   : 2;  /* [11:10],          r,        0x0 */
            uint32_t reserved_12_15    : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t MCU1_WFI_FORCE    : 1;  /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_27    : 11; /* [27:17],       rsvd,        0x0 */
            uint32_t mcu1_ndm_rstn_en  : 1;  /* [   28],        r/w,        0x0 */
            uint32_t mcu1_hart_rstn_en : 1;  /* [   29],        r/w,        0x0 */
            uint32_t reserved_30_31    : 2;  /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mcu_cfg1;

    /* 0x104  reserved */
    uint8_t RESERVED0x104[12];

    /* 0x110 : mcu1_log1 */
    union {
        struct {
            uint32_t sts_mcu1_mcause : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } mcu1_log1;

    /* 0x114 : mcu1_log2 */
    union {
        struct {
            uint32_t sts_mcu1_mintstatus : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } mcu1_log2;

    /* 0x118 : mcu1_log3 */
    union {
        struct {
            uint32_t sts_mcu1_mstatus : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } mcu1_log3;

    /* 0x11C : mcu1_log4 */
    union {
        struct {
            uint32_t sts_mcu1_sp : 1;  /* [    0],          r,        0x0 */
            uint32_t sts_mcu1_pc : 31; /* [31: 1],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } mcu1_log4;

    /* 0x120 : mcu1_log5 */
    union {
        struct {
            uint32_t reserved_0_23      : 24; /* [23: 0],       rsvd,        0x0 */
            uint32_t sts_mcu1_lockup    : 1;  /* [   24],          r,        0x0 */
            uint32_t sts_mcu1_halted    : 1;  /* [   25],          r,        0x0 */
            uint32_t reserved_26_27     : 2;  /* [27:26],       rsvd,        0x0 */
            uint32_t mcu1_ndm_rstn_req  : 1;  /* [   28],          r,        0x0 */
            uint32_t mcu1_hart_rstn_req : 1;  /* [   29],          r,        0x0 */
            uint32_t reserved_30_31     : 2;  /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mcu1_log5;

    /* 0x124  reserved */
    uint8_t RESERVED0x124[228];

    /* 0x208 : irom1_misr_dataout_0 */
    union {
        struct {
            uint32_t reserved_0_31 : 32; /* [31: 0],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } irom1_misr_dataout_0;

    /* 0x20C : irom1_misr_dataout_1 */
    union {
        struct {
            uint32_t reserved_0_31 : 32; /* [31: 0],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } irom1_misr_dataout_1;
};

typedef volatile struct mcu_misc_reg mcu_misc_reg_t;

#endif /* __MCU_MISC_REG_H__ */
