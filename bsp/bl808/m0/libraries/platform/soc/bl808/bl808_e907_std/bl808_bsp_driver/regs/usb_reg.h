/**
  ******************************************************************************
  * @file    usb_reg.h
  * @version V1.0
  * @date    2021-04-20
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
#ifndef __USB_REG_H__
#define __USB_REG_H__

#include "bl808.h"

/* 0x000 : HCCAP */
#define USB_HCCAP_OFFSET    (0x000)
#define USB_CAPLENGTH       USB_CAPLENGTH
#define USB_CAPLENGTH_POS   (0U)
#define USB_CAPLENGTH_LEN   (8U)
#define USB_CAPLENGTH_MSK   (((1U << USB_CAPLENGTH_LEN) - 1) << USB_CAPLENGTH_POS)
#define USB_CAPLENGTH_UMSK  (~(((1U << USB_CAPLENGTH_LEN) - 1) << USB_CAPLENGTH_POS))
#define USB_HCIVERSION      USB_HCIVERSION
#define USB_HCIVERSION_POS  (16U)
#define USB_HCIVERSION_LEN  (16U)
#define USB_HCIVERSION_MSK  (((1U << USB_HCIVERSION_LEN) - 1) << USB_HCIVERSION_POS)
#define USB_HCIVERSION_UMSK (~(((1U << USB_HCIVERSION_LEN) - 1) << USB_HCIVERSION_POS))

/* 0x004 : HCSPARAMS */
#define USB_HCSPARAMS_OFFSET (0x004)
#define USB_N_PORTS          USB_N_PORTS
#define USB_N_PORTS_POS      (0U)
#define USB_N_PORTS_LEN      (4U)
#define USB_N_PORTS_MSK      (((1U << USB_N_PORTS_LEN) - 1) << USB_N_PORTS_POS)
#define USB_N_PORTS_UMSK     (~(((1U << USB_N_PORTS_LEN) - 1) << USB_N_PORTS_POS))

/* 0x008 : HCCPARAMS */
#define USB_HCCPARAMS_OFFSET       (0x008)
#define USB_PROG_FR_LIST_FLAG      USB_PROG_FR_LIST_FLAG
#define USB_PROG_FR_LIST_FLAG_POS  (1U)
#define USB_PROG_FR_LIST_FLAG_LEN  (1U)
#define USB_PROG_FR_LIST_FLAG_MSK  (((1U << USB_PROG_FR_LIST_FLAG_LEN) - 1) << USB_PROG_FR_LIST_FLAG_POS)
#define USB_PROG_FR_LIST_FLAG_UMSK (~(((1U << USB_PROG_FR_LIST_FLAG_LEN) - 1) << USB_PROG_FR_LIST_FLAG_POS))
#define USB_ASYN_SCH_PARK_CAP      USB_ASYN_SCH_PARK_CAP
#define USB_ASYN_SCH_PARK_CAP_POS  (2U)
#define USB_ASYN_SCH_PARK_CAP_LEN  (1U)
#define USB_ASYN_SCH_PARK_CAP_MSK  (((1U << USB_ASYN_SCH_PARK_CAP_LEN) - 1) << USB_ASYN_SCH_PARK_CAP_POS)
#define USB_ASYN_SCH_PARK_CAP_UMSK (~(((1U << USB_ASYN_SCH_PARK_CAP_LEN) - 1) << USB_ASYN_SCH_PARK_CAP_POS))

/* 0x010 : USBCMD */
#define USBCMD_OFFSET        (0x010)
#define USB_RS               USB_RS
#define USB_RS_POS           (0U)
#define USB_RS_LEN           (1U)
#define USB_RS_MSK           (((1U << USB_RS_LEN) - 1) << USB_RS_POS)
#define USB_RS_UMSK          (~(((1U << USB_RS_LEN) - 1) << USB_RS_POS))
#define USB_HC_RESET         USB_HC_RESET
#define USB_HC_RESET_POS     (1U)
#define USB_HC_RESET_LEN     (1U)
#define USB_HC_RESET_MSK     (((1U << USB_HC_RESET_LEN) - 1) << USB_HC_RESET_POS)
#define USB_HC_RESET_UMSK    (~(((1U << USB_HC_RESET_LEN) - 1) << USB_HC_RESET_POS))
#define USB_FRL_SIZE         USB_FRL_SIZE
#define USB_FRL_SIZE_POS     (2U)
#define USB_FRL_SIZE_LEN     (2U)
#define USB_FRL_SIZE_MSK     (((1U << USB_FRL_SIZE_LEN) - 1) << USB_FRL_SIZE_POS)
#define USB_FRL_SIZE_UMSK    (~(((1U << USB_FRL_SIZE_LEN) - 1) << USB_FRL_SIZE_POS))
#define USB_PSCH_EN          USB_PSCH_EN
#define USB_PSCH_EN_POS      (4U)
#define USB_PSCH_EN_LEN      (1U)
#define USB_PSCH_EN_MSK      (((1U << USB_PSCH_EN_LEN) - 1) << USB_PSCH_EN_POS)
#define USB_PSCH_EN_UMSK     (~(((1U << USB_PSCH_EN_LEN) - 1) << USB_PSCH_EN_POS))
#define USB_ASCH_EN          USB_ASCH_EN
#define USB_ASCH_EN_POS      (5U)
#define USB_ASCH_EN_LEN      (1U)
#define USB_ASCH_EN_MSK      (((1U << USB_ASCH_EN_LEN) - 1) << USB_ASCH_EN_POS)
#define USB_ASCH_EN_UMSK     (~(((1U << USB_ASCH_EN_LEN) - 1) << USB_ASCH_EN_POS))
#define USB_INT_OAAD         USB_INT_OAAD
#define USB_INT_OAAD_POS     (6U)
#define USB_INT_OAAD_LEN     (1U)
#define USB_INT_OAAD_MSK     (((1U << USB_INT_OAAD_LEN) - 1) << USB_INT_OAAD_POS)
#define USB_INT_OAAD_UMSK    (~(((1U << USB_INT_OAAD_LEN) - 1) << USB_INT_OAAD_POS))
#define USB_ASYN_PK_CNT      USB_ASYN_PK_CNT
#define USB_ASYN_PK_CNT_POS  (8U)
#define USB_ASYN_PK_CNT_LEN  (2U)
#define USB_ASYN_PK_CNT_MSK  (((1U << USB_ASYN_PK_CNT_LEN) - 1) << USB_ASYN_PK_CNT_POS)
#define USB_ASYN_PK_CNT_UMSK (~(((1U << USB_ASYN_PK_CNT_LEN) - 1) << USB_ASYN_PK_CNT_POS))
#define USB_ASYN_PK_EN       USB_ASYN_PK_EN
#define USB_ASYN_PK_EN_POS   (11U)
#define USB_ASYN_PK_EN_LEN   (1U)
#define USB_ASYN_PK_EN_MSK   (((1U << USB_ASYN_PK_EN_LEN) - 1) << USB_ASYN_PK_EN_POS)
#define USB_ASYN_PK_EN_UMSK  (~(((1U << USB_ASYN_PK_EN_LEN) - 1) << USB_ASYN_PK_EN_POS))
#define USB_INT_THRC         USB_INT_THRC
#define USB_INT_THRC_POS     (16U)
#define USB_INT_THRC_LEN     (8U)
#define USB_INT_THRC_MSK     (((1U << USB_INT_THRC_LEN) - 1) << USB_INT_THRC_POS)
#define USB_INT_THRC_UMSK    (~(((1U << USB_INT_THRC_LEN) - 1) << USB_INT_THRC_POS))

/* 0x014 : USBSTS */
#define USBSTS_OFFSET        (0x014)
#define USB_INT              USB_INT
#define USB_INT_POS          (0U)
#define USB_INT_LEN          (1U)
#define USB_INT_MSK          (((1U << USB_INT_LEN) - 1) << USB_INT_POS)
#define USB_INT_UMSK         (~(((1U << USB_INT_LEN) - 1) << USB_INT_POS))
#define USBERR_INT           USBERR_INT
#define USBERR_INT_POS       (1U)
#define USBERR_INT_LEN       (1U)
#define USBERR_INT_MSK       (((1U << USBERR_INT_LEN) - 1) << USBERR_INT_POS)
#define USBERR_INT_UMSK      (~(((1U << USBERR_INT_LEN) - 1) << USBERR_INT_POS))
#define USB_PO_CHG_DET       USB_PO_CHG_DET
#define USB_PO_CHG_DET_POS   (2U)
#define USB_PO_CHG_DET_LEN   (1U)
#define USB_PO_CHG_DET_MSK   (((1U << USB_PO_CHG_DET_LEN) - 1) << USB_PO_CHG_DET_POS)
#define USB_PO_CHG_DET_UMSK  (~(((1U << USB_PO_CHG_DET_LEN) - 1) << USB_PO_CHG_DET_POS))
#define USB_FRL_ROL          USB_FRL_ROL
#define USB_FRL_ROL_POS      (3U)
#define USB_FRL_ROL_LEN      (1U)
#define USB_FRL_ROL_MSK      (((1U << USB_FRL_ROL_LEN) - 1) << USB_FRL_ROL_POS)
#define USB_FRL_ROL_UMSK     (~(((1U << USB_FRL_ROL_LEN) - 1) << USB_FRL_ROL_POS))
#define USB_H_SYSERR         USB_H_SYSERR
#define USB_H_SYSERR_POS     (4U)
#define USB_H_SYSERR_LEN     (1U)
#define USB_H_SYSERR_MSK     (((1U << USB_H_SYSERR_LEN) - 1) << USB_H_SYSERR_POS)
#define USB_H_SYSERR_UMSK    (~(((1U << USB_H_SYSERR_LEN) - 1) << USB_H_SYSERR_POS))
#define USB_INT_OAA          USB_INT_OAA
#define USB_INT_OAA_POS      (5U)
#define USB_INT_OAA_LEN      (1U)
#define USB_INT_OAA_MSK      (((1U << USB_INT_OAA_LEN) - 1) << USB_INT_OAA_POS)
#define USB_INT_OAA_UMSK     (~(((1U << USB_INT_OAA_LEN) - 1) << USB_INT_OAA_POS))
#define USB_HCHALTED         USB_HCHALTED
#define USB_HCHALTED_POS     (12U)
#define USB_HCHALTED_LEN     (1U)
#define USB_HCHALTED_MSK     (((1U << USB_HCHALTED_LEN) - 1) << USB_HCHALTED_POS)
#define USB_HCHALTED_UMSK    (~(((1U << USB_HCHALTED_LEN) - 1) << USB_HCHALTED_POS))
#define USB_RECLAMATION      USB_RECLAMATION
#define USB_RECLAMATION_POS  (13U)
#define USB_RECLAMATION_LEN  (1U)
#define USB_RECLAMATION_MSK  (((1U << USB_RECLAMATION_LEN) - 1) << USB_RECLAMATION_POS)
#define USB_RECLAMATION_UMSK (~(((1U << USB_RECLAMATION_LEN) - 1) << USB_RECLAMATION_POS))
#define USB_PSCH_STS         USB_PSCH_STS
#define USB_PSCH_STS_POS     (14U)
#define USB_PSCH_STS_LEN     (1U)
#define USB_PSCH_STS_MSK     (((1U << USB_PSCH_STS_LEN) - 1) << USB_PSCH_STS_POS)
#define USB_PSCH_STS_UMSK    (~(((1U << USB_PSCH_STS_LEN) - 1) << USB_PSCH_STS_POS))
#define USB_ASCH_STS         USB_ASCH_STS
#define USB_ASCH_STS_POS     (15U)
#define USB_ASCH_STS_LEN     (1U)
#define USB_ASCH_STS_MSK     (((1U << USB_ASCH_STS_LEN) - 1) << USB_ASCH_STS_POS)
#define USB_ASCH_STS_UMSK    (~(((1U << USB_ASCH_STS_LEN) - 1) << USB_ASCH_STS_POS))

/* 0x018 : USBINTR */
#define USBINTR_OFFSET         (0x018)
#define USB_INT_EN             USB_INT_EN
#define USB_INT_EN_POS         (0U)
#define USB_INT_EN_LEN         (1U)
#define USB_INT_EN_MSK         (((1U << USB_INT_EN_LEN) - 1) << USB_INT_EN_POS)
#define USB_INT_EN_UMSK        (~(((1U << USB_INT_EN_LEN) - 1) << USB_INT_EN_POS))
#define USBERR_INT_EN          USBERR_INT_EN
#define USBERR_INT_EN_POS      (1U)
#define USBERR_INT_EN_LEN      (1U)
#define USBERR_INT_EN_MSK      (((1U << USBERR_INT_EN_LEN) - 1) << USBERR_INT_EN_POS)
#define USBERR_INT_EN_UMSK     (~(((1U << USBERR_INT_EN_LEN) - 1) << USBERR_INT_EN_POS))
#define USB_PO_CHG_INT_EN      USB_PO_CHG_INT_EN
#define USB_PO_CHG_INT_EN_POS  (2U)
#define USB_PO_CHG_INT_EN_LEN  (1U)
#define USB_PO_CHG_INT_EN_MSK  (((1U << USB_PO_CHG_INT_EN_LEN) - 1) << USB_PO_CHG_INT_EN_POS)
#define USB_PO_CHG_INT_EN_UMSK (~(((1U << USB_PO_CHG_INT_EN_LEN) - 1) << USB_PO_CHG_INT_EN_POS))
#define USB_FRL_ROL_EN         USB_FRL_ROL_EN
#define USB_FRL_ROL_EN_POS     (3U)
#define USB_FRL_ROL_EN_LEN     (1U)
#define USB_FRL_ROL_EN_MSK     (((1U << USB_FRL_ROL_EN_LEN) - 1) << USB_FRL_ROL_EN_POS)
#define USB_FRL_ROL_EN_UMSK    (~(((1U << USB_FRL_ROL_EN_LEN) - 1) << USB_FRL_ROL_EN_POS))
#define USB_H_SYSERR_EN        USB_H_SYSERR_EN
#define USB_H_SYSERR_EN_POS    (4U)
#define USB_H_SYSERR_EN_LEN    (1U)
#define USB_H_SYSERR_EN_MSK    (((1U << USB_H_SYSERR_EN_LEN) - 1) << USB_H_SYSERR_EN_POS)
#define USB_H_SYSERR_EN_UMSK   (~(((1U << USB_H_SYSERR_EN_LEN) - 1) << USB_H_SYSERR_EN_POS))
#define USB_INT_OAA_EN         USB_INT_OAA_EN
#define USB_INT_OAA_EN_POS     (5U)
#define USB_INT_OAA_EN_LEN     (1U)
#define USB_INT_OAA_EN_MSK     (((1U << USB_INT_OAA_EN_LEN) - 1) << USB_INT_OAA_EN_POS)
#define USB_INT_OAA_EN_UMSK    (~(((1U << USB_INT_OAA_EN_LEN) - 1) << USB_INT_OAA_EN_POS))

/* 0x01C : FRINDEX */
#define USB_FRINDEX_OFFSET (0x01C)
#define USB_FRINDEX        USB_FRINDEX
#define USB_FRINDEX_POS    (0U)
#define USB_FRINDEX_LEN    (14U)
#define USB_FRINDEX_MSK    (((1U << USB_FRINDEX_LEN) - 1) << USB_FRINDEX_POS)
#define USB_FRINDEX_UMSK   (~(((1U << USB_FRINDEX_LEN) - 1) << USB_FRINDEX_POS))

/* 0x024 : PERIODICLISTBASE */
#define USB_PERIODICLISTBASE_OFFSET (0x024)
#define USB_PERI_BASADR             USB_PERI_BASADR
#define USB_PERI_BASADR_POS         (12U)
#define USB_PERI_BASADR_LEN         (20U)
#define USB_PERI_BASADR_MSK         (((1U << USB_PERI_BASADR_LEN) - 1) << USB_PERI_BASADR_POS)
#define USB_PERI_BASADR_UMSK        (~(((1U << USB_PERI_BASADR_LEN) - 1) << USB_PERI_BASADR_POS))

/* 0x028 : ASYNCLISTADDR */
#define USB_ASYNCLISTADDR_OFFSET (0x028)
#define USB_ASYNC_LADR           USB_ASYNC_LADR
#define USB_ASYNC_LADR_POS       (5U)
#define USB_ASYNC_LADR_LEN       (27U)
#define USB_ASYNC_LADR_MSK       (((1U << USB_ASYNC_LADR_LEN) - 1) << USB_ASYNC_LADR_POS)
#define USB_ASYNC_LADR_UMSK      (~(((1U << USB_ASYNC_LADR_LEN) - 1) << USB_ASYNC_LADR_POS))

/* 0x030 : PORTSC */
#define USB_PORTSC_OFFSET      (0x030)
#define USB_CONN_STS           USB_CONN_STS
#define USB_CONN_STS_POS       (0U)
#define USB_CONN_STS_LEN       (1U)
#define USB_CONN_STS_MSK       (((1U << USB_CONN_STS_LEN) - 1) << USB_CONN_STS_POS)
#define USB_CONN_STS_UMSK      (~(((1U << USB_CONN_STS_LEN) - 1) << USB_CONN_STS_POS))
#define USB_CONN_CHG           USB_CONN_CHG
#define USB_CONN_CHG_POS       (1U)
#define USB_CONN_CHG_LEN       (1U)
#define USB_CONN_CHG_MSK       (((1U << USB_CONN_CHG_LEN) - 1) << USB_CONN_CHG_POS)
#define USB_CONN_CHG_UMSK      (~(((1U << USB_CONN_CHG_LEN) - 1) << USB_CONN_CHG_POS))
#define USB_PO_EN              USB_PO_EN
#define USB_PO_EN_POS          (2U)
#define USB_PO_EN_LEN          (1U)
#define USB_PO_EN_MSK          (((1U << USB_PO_EN_LEN) - 1) << USB_PO_EN_POS)
#define USB_PO_EN_UMSK         (~(((1U << USB_PO_EN_LEN) - 1) << USB_PO_EN_POS))
#define USB_PO_EN_CHG          USB_PO_EN_CHG
#define USB_PO_EN_CHG_POS      (3U)
#define USB_PO_EN_CHG_LEN      (1U)
#define USB_PO_EN_CHG_MSK      (((1U << USB_PO_EN_CHG_LEN) - 1) << USB_PO_EN_CHG_POS)
#define USB_PO_EN_CHG_UMSK     (~(((1U << USB_PO_EN_CHG_LEN) - 1) << USB_PO_EN_CHG_POS))
#define USB_F_PO_RESM          USB_F_PO_RESM
#define USB_F_PO_RESM_POS      (6U)
#define USB_F_PO_RESM_LEN      (1U)
#define USB_F_PO_RESM_MSK      (((1U << USB_F_PO_RESM_LEN) - 1) << USB_F_PO_RESM_POS)
#define USB_F_PO_RESM_UMSK     (~(((1U << USB_F_PO_RESM_LEN) - 1) << USB_F_PO_RESM_POS))
#define USB_PO_SUSP            USB_PO_SUSP
#define USB_PO_SUSP_POS        (7U)
#define USB_PO_SUSP_LEN        (1U)
#define USB_PO_SUSP_MSK        (((1U << USB_PO_SUSP_LEN) - 1) << USB_PO_SUSP_POS)
#define USB_PO_SUSP_UMSK       (~(((1U << USB_PO_SUSP_LEN) - 1) << USB_PO_SUSP_POS))
#define USB_PO_RESET           USB_PO_RESET
#define USB_PO_RESET_POS       (8U)
#define USB_PO_RESET_LEN       (1U)
#define USB_PO_RESET_MSK       (((1U << USB_PO_RESET_LEN) - 1) << USB_PO_RESET_POS)
#define USB_PO_RESET_UMSK      (~(((1U << USB_PO_RESET_LEN) - 1) << USB_PO_RESET_POS))
#define USB_LINE_STS           USB_LINE_STS
#define USB_LINE_STS_POS       (10U)
#define USB_LINE_STS_LEN       (2U)
#define USB_LINE_STS_MSK       (((1U << USB_LINE_STS_LEN) - 1) << USB_LINE_STS_POS)
#define USB_LINE_STS_UMSK      (~(((1U << USB_LINE_STS_LEN) - 1) << USB_LINE_STS_POS))
#define USB_PORT_TEST          USB_PORT_TEST
#define USB_PORT_TEST_POS      (16U)
#define USB_PORT_TEST_LEN      (4U)
#define USB_PORT_TEST_MSK      (((1U << USB_PORT_TEST_LEN) - 1) << USB_PORT_TEST_POS)
#define USB_PORT_TEST_UMSK     (~(((1U << USB_PORT_TEST_LEN) - 1) << USB_PORT_TEST_POS))
#define USB_HC_TST_PKDONE      USB_HC_TST_PKDONE
#define USB_HC_TST_PKDONE_POS  (20U)
#define USB_HC_TST_PKDONE_LEN  (1U)
#define USB_HC_TST_PKDONE_MSK  (((1U << USB_HC_TST_PKDONE_LEN) - 1) << USB_HC_TST_PKDONE_POS)
#define USB_HC_TST_PKDONE_UMSK (~(((1U << USB_HC_TST_PKDONE_LEN) - 1) << USB_HC_TST_PKDONE_POS))

/* 0x040 : HCMISC */
#define USB_HCMISC_OFFSET        (0x040)
#define USB_ASYN_SCH_SLPT        USB_ASYN_SCH_SLPT
#define USB_ASYN_SCH_SLPT_POS    (0U)
#define USB_ASYN_SCH_SLPT_LEN    (2U)
#define USB_ASYN_SCH_SLPT_MSK    (((1U << USB_ASYN_SCH_SLPT_LEN) - 1) << USB_ASYN_SCH_SLPT_POS)
#define USB_ASYN_SCH_SLPT_UMSK   (~(((1U << USB_ASYN_SCH_SLPT_LEN) - 1) << USB_ASYN_SCH_SLPT_POS))
#define USB_EOF1_TIME            USB_EOF1_TIME
#define USB_EOF1_TIME_POS        (2U)
#define USB_EOF1_TIME_LEN        (2U)
#define USB_EOF1_TIME_MSK        (((1U << USB_EOF1_TIME_LEN) - 1) << USB_EOF1_TIME_POS)
#define USB_EOF1_TIME_UMSK       (~(((1U << USB_EOF1_TIME_LEN) - 1) << USB_EOF1_TIME_POS))
#define USB_EOF2_TIME            USB_EOF2_TIME
#define USB_EOF2_TIME_POS        (4U)
#define USB_EOF2_TIME_LEN        (2U)
#define USB_EOF2_TIME_MSK        (((1U << USB_EOF2_TIME_LEN) - 1) << USB_EOF2_TIME_POS)
#define USB_EOF2_TIME_UMSK       (~(((1U << USB_EOF2_TIME_LEN) - 1) << USB_EOF2_TIME_POS))
#define USB_HOSTPHY_SUSPEND      USB_HOSTPHY_SUSPEND
#define USB_HOSTPHY_SUSPEND_POS  (6U)
#define USB_HOSTPHY_SUSPEND_LEN  (1U)
#define USB_HOSTPHY_SUSPEND_MSK  (((1U << USB_HOSTPHY_SUSPEND_LEN) - 1) << USB_HOSTPHY_SUSPEND_POS)
#define USB_HOSTPHY_SUSPEND_UMSK (~(((1U << USB_HOSTPHY_SUSPEND_LEN) - 1) << USB_HOSTPHY_SUSPEND_POS))
#define USB_HC_WKP_DET_EN        USB_HC_WKP_DET_EN
#define USB_HC_WKP_DET_EN_POS    (8U)
#define USB_HC_WKP_DET_EN_LEN    (1U)
#define USB_HC_WKP_DET_EN_MSK    (((1U << USB_HC_WKP_DET_EN_LEN) - 1) << USB_HC_WKP_DET_EN_POS)
#define USB_HC_WKP_DET_EN_UMSK   (~(((1U << USB_HC_WKP_DET_EN_LEN) - 1) << USB_HC_WKP_DET_EN_POS))
#define USB_HC_CONN_DET_EN       USB_HC_CONN_DET_EN
#define USB_HC_CONN_DET_EN_POS   (9U)
#define USB_HC_CONN_DET_EN_LEN   (1U)
#define USB_HC_CONN_DET_EN_MSK   (((1U << USB_HC_CONN_DET_EN_LEN) - 1) << USB_HC_CONN_DET_EN_POS)
#define USB_HC_CONN_DET_EN_UMSK  (~(((1U << USB_HC_CONN_DET_EN_LEN) - 1) << USB_HC_CONN_DET_EN_POS))

/* 0x044 : FS_EOF */
#define USB_FS_EOF_OFFSET           (0x044)
#define USB_FS_EOF1_TIME            USB_FS_EOF1_TIME
#define USB_FS_EOF1_TIME_POS        (0U)
#define USB_FS_EOF1_TIME_LEN        (12U)
#define USB_FS_EOF1_TIME_MSK        (((1U << USB_FS_EOF1_TIME_LEN) - 1) << USB_FS_EOF1_TIME_POS)
#define USB_FS_EOF1_TIME_UMSK       (~(((1U << USB_FS_EOF1_TIME_LEN) - 1) << USB_FS_EOF1_TIME_POS))
#define USB_FS_EOF1_TIME_125US      USB_FS_EOF1_TIME_125US
#define USB_FS_EOF1_TIME_125US_POS  (12U)
#define USB_FS_EOF1_TIME_125US_LEN  (3U)
#define USB_FS_EOF1_TIME_125US_MSK  (((1U << USB_FS_EOF1_TIME_125US_LEN) - 1) << USB_FS_EOF1_TIME_125US_POS)
#define USB_FS_EOF1_TIME_125US_UMSK (~(((1U << USB_FS_EOF1_TIME_125US_LEN) - 1) << USB_FS_EOF1_TIME_125US_POS))
#define USB_ITDDMASM                USB_ITDDMASM
#define USB_ITDDMASM_POS            (16U)
#define USB_ITDDMASM_LEN            (4U)
#define USB_ITDDMASM_MSK            (((1U << USB_ITDDMASM_LEN) - 1) << USB_ITDDMASM_POS)
#define USB_ITDDMASM_UMSK           (~(((1U << USB_ITDDMASM_LEN) - 1) << USB_ITDDMASM_POS))
#define USB_ITDTRAVSM               USB_ITDTRAVSM
#define USB_ITDTRAVSM_POS           (20U)
#define USB_ITDTRAVSM_LEN           (2U)
#define USB_ITDTRAVSM_MSK           (((1U << USB_ITDTRAVSM_LEN) - 1) << USB_ITDTRAVSM_POS)
#define USB_ITDTRAVSM_UMSK          (~(((1U << USB_ITDTRAVSM_LEN) - 1) << USB_ITDTRAVSM_POS))
#define USB_DMADMSM                 USB_DMADMSM
#define USB_DMADMSM_POS             (22U)
#define USB_DMADMSM_LEN             (4U)
#define USB_DMADMSM_MSK             (((1U << USB_DMADMSM_LEN) - 1) << USB_DMADMSM_POS)
#define USB_DMADMSM_UMSK            (~(((1U << USB_DMADMSM_LEN) - 1) << USB_DMADMSM_POS))
#define USB_QHTTRSM                 USB_QHTTRSM
#define USB_QHTTRSM_POS             (26U)
#define USB_QHTTRSM_LEN             (3U)
#define USB_QHTTRSM_MSK             (((1U << USB_QHTTRSM_LEN) - 1) << USB_QHTTRSM_POS)
#define USB_QHTTRSM_UMSK            (~(((1U << USB_QHTTRSM_LEN) - 1) << USB_QHTTRSM_POS))
#define USB_QHTRAVSM                USB_QHTRAVSM
#define USB_QHTRAVSM_POS            (29U)
#define USB_QHTRAVSM_LEN            (3U)
#define USB_QHTRAVSM_MSK            (((1U << USB_QHTRAVSM_LEN) - 1) << USB_QHTRAVSM_POS)
#define USB_QHTRAVSM_UMSK           (~(((1U << USB_QHTRAVSM_LEN) - 1) << USB_QHTRAVSM_POS))

/* 0x048 : HS_EOF */
#define USB_HS_EOF_OFFSET     (0x048)
#define USB_HS_EOF1_TIME      USB_HS_EOF1_TIME
#define USB_HS_EOF1_TIME_POS  (0U)
#define USB_HS_EOF1_TIME_LEN  (12U)
#define USB_HS_EOF1_TIME_MSK  (((1U << USB_HS_EOF1_TIME_LEN) - 1) << USB_HS_EOF1_TIME_POS)
#define USB_HS_EOF1_TIME_UMSK (~(((1U << USB_HS_EOF1_TIME_LEN) - 1) << USB_HS_EOF1_TIME_POS))
#define USB_SITDDMASM         USB_SITDDMASM
#define USB_SITDDMASM_POS     (16U)
#define USB_SITDDMASM_LEN     (4U)
#define USB_SITDDMASM_MSK     (((1U << USB_SITDDMASM_LEN) - 1) << USB_SITDDMASM_POS)
#define USB_SITDDMASM_UMSK    (~(((1U << USB_SITDDMASM_LEN) - 1) << USB_SITDDMASM_POS))
#define USB_SITDTRAVSM        USB_SITDTRAVSM
#define USB_SITDTRAVSM_POS    (20U)
#define USB_SITDTRAVSM_LEN    (2U)
#define USB_SITDTRAVSM_MSK    (((1U << USB_SITDTRAVSM_LEN) - 1) << USB_SITDTRAVSM_POS)
#define USB_SITDTRAVSM_UMSK   (~(((1U << USB_SITDTRAVSM_LEN) - 1) << USB_SITDTRAVSM_POS))

/* 0x080 : OTG_CSR */
#define USB_OTG_CSR_OFFSET            (0x080)
#define USB_B_BUS_REQ                 USB_B_BUS_REQ
#define USB_B_BUS_REQ_POS             (0U)
#define USB_B_BUS_REQ_LEN             (1U)
#define USB_B_BUS_REQ_MSK             (((1U << USB_B_BUS_REQ_LEN) - 1) << USB_B_BUS_REQ_POS)
#define USB_B_BUS_REQ_UMSK            (~(((1U << USB_B_BUS_REQ_LEN) - 1) << USB_B_BUS_REQ_POS))
#define USB_B_HNP_EN                  USB_B_HNP_EN
#define USB_B_HNP_EN_POS              (1U)
#define USB_B_HNP_EN_LEN              (1U)
#define USB_B_HNP_EN_MSK              (((1U << USB_B_HNP_EN_LEN) - 1) << USB_B_HNP_EN_POS)
#define USB_B_HNP_EN_UMSK             (~(((1U << USB_B_HNP_EN_LEN) - 1) << USB_B_HNP_EN_POS))
#define USB_B_DSCHRG_VBUS             USB_B_DSCHRG_VBUS
#define USB_B_DSCHRG_VBUS_POS         (2U)
#define USB_B_DSCHRG_VBUS_LEN         (1U)
#define USB_B_DSCHRG_VBUS_MSK         (((1U << USB_B_DSCHRG_VBUS_LEN) - 1) << USB_B_DSCHRG_VBUS_POS)
#define USB_B_DSCHRG_VBUS_UMSK        (~(((1U << USB_B_DSCHRG_VBUS_LEN) - 1) << USB_B_DSCHRG_VBUS_POS))
#define USB_A_BUS_REQ_HOV             USB_A_BUS_REQ_HOV
#define USB_A_BUS_REQ_HOV_POS         (4U)
#define USB_A_BUS_REQ_HOV_LEN         (1U)
#define USB_A_BUS_REQ_HOV_MSK         (((1U << USB_A_BUS_REQ_HOV_LEN) - 1) << USB_A_BUS_REQ_HOV_POS)
#define USB_A_BUS_REQ_HOV_UMSK        (~(((1U << USB_A_BUS_REQ_HOV_LEN) - 1) << USB_A_BUS_REQ_HOV_POS))
#define USB_A_BUS_DROP_HOV            USB_A_BUS_DROP_HOV
#define USB_A_BUS_DROP_HOV_POS        (5U)
#define USB_A_BUS_DROP_HOV_LEN        (1U)
#define USB_A_BUS_DROP_HOV_MSK        (((1U << USB_A_BUS_DROP_HOV_LEN) - 1) << USB_A_BUS_DROP_HOV_POS)
#define USB_A_BUS_DROP_HOV_UMSK       (~(((1U << USB_A_BUS_DROP_HOV_LEN) - 1) << USB_A_BUS_DROP_HOV_POS))
#define USB_A_SET_B_HNP_EN            USB_A_SET_B_HNP_EN
#define USB_A_SET_B_HNP_EN_POS        (6U)
#define USB_A_SET_B_HNP_EN_LEN        (1U)
#define USB_A_SET_B_HNP_EN_MSK        (((1U << USB_A_SET_B_HNP_EN_LEN) - 1) << USB_A_SET_B_HNP_EN_POS)
#define USB_A_SET_B_HNP_EN_UMSK       (~(((1U << USB_A_SET_B_HNP_EN_LEN) - 1) << USB_A_SET_B_HNP_EN_POS))
#define USB_A_SRP_DET_EN              USB_A_SRP_DET_EN
#define USB_A_SRP_DET_EN_POS          (7U)
#define USB_A_SRP_DET_EN_LEN          (1U)
#define USB_A_SRP_DET_EN_MSK          (((1U << USB_A_SRP_DET_EN_LEN) - 1) << USB_A_SRP_DET_EN_POS)
#define USB_A_SRP_DET_EN_UMSK         (~(((1U << USB_A_SRP_DET_EN_LEN) - 1) << USB_A_SRP_DET_EN_POS))
#define USB_A_SRP_RESP_TYP            USB_A_SRP_RESP_TYP
#define USB_A_SRP_RESP_TYP_POS        (8U)
#define USB_A_SRP_RESP_TYP_LEN        (1U)
#define USB_A_SRP_RESP_TYP_MSK        (((1U << USB_A_SRP_RESP_TYP_LEN) - 1) << USB_A_SRP_RESP_TYP_POS)
#define USB_A_SRP_RESP_TYP_UMSK       (~(((1U << USB_A_SRP_RESP_TYP_LEN) - 1) << USB_A_SRP_RESP_TYP_POS))
#define USB_ID_FLT_SEL                USB_ID_FLT_SEL
#define USB_ID_FLT_SEL_POS            (9U)
#define USB_ID_FLT_SEL_LEN            (1U)
#define USB_ID_FLT_SEL_MSK            (((1U << USB_ID_FLT_SEL_LEN) - 1) << USB_ID_FLT_SEL_POS)
#define USB_ID_FLT_SEL_UMSK           (~(((1U << USB_ID_FLT_SEL_LEN) - 1) << USB_ID_FLT_SEL_POS))
#define USB_VBUS_FLT_SEL_HOV_POV      USB_VBUS_FLT_SEL_HOV_POV
#define USB_VBUS_FLT_SEL_HOV_POV_POS  (10U)
#define USB_VBUS_FLT_SEL_HOV_POV_LEN  (1U)
#define USB_VBUS_FLT_SEL_HOV_POV_MSK  (((1U << USB_VBUS_FLT_SEL_HOV_POV_LEN) - 1) << USB_VBUS_FLT_SEL_HOV_POV_POS)
#define USB_VBUS_FLT_SEL_HOV_POV_UMSK (~(((1U << USB_VBUS_FLT_SEL_HOV_POV_LEN) - 1) << USB_VBUS_FLT_SEL_HOV_POV_POS))
#define USB_HDISCON_FLT_SEL_HOV       USB_HDISCON_FLT_SEL_HOV
#define USB_HDISCON_FLT_SEL_HOV_POS   (11U)
#define USB_HDISCON_FLT_SEL_HOV_LEN   (1U)
#define USB_HDISCON_FLT_SEL_HOV_MSK   (((1U << USB_HDISCON_FLT_SEL_HOV_LEN) - 1) << USB_HDISCON_FLT_SEL_HOV_POS)
#define USB_HDISCON_FLT_SEL_HOV_UMSK  (~(((1U << USB_HDISCON_FLT_SEL_HOV_LEN) - 1) << USB_HDISCON_FLT_SEL_HOV_POS))
#define USB_IDPULUP_HOV_POV           USB_IDPULUP_HOV_POV
#define USB_IDPULUP_HOV_POV_POS       (13U)
#define USB_IDPULUP_HOV_POV_LEN       (1U)
#define USB_IDPULUP_HOV_POV_MSK       (((1U << USB_IDPULUP_HOV_POV_LEN) - 1) << USB_IDPULUP_HOV_POV_POS)
#define USB_IDPULUP_HOV_POV_UMSK      (~(((1U << USB_IDPULUP_HOV_POV_LEN) - 1) << USB_IDPULUP_HOV_POV_POS))
#define USB_B_SESS_END_POV            USB_B_SESS_END_POV
#define USB_B_SESS_END_POV_POS        (16U)
#define USB_B_SESS_END_POV_LEN        (1U)
#define USB_B_SESS_END_POV_MSK        (((1U << USB_B_SESS_END_POV_LEN) - 1) << USB_B_SESS_END_POV_POS)
#define USB_B_SESS_END_POV_UMSK       (~(((1U << USB_B_SESS_END_POV_LEN) - 1) << USB_B_SESS_END_POV_POS))
#define USB_B_SESS_VLD_POV            USB_B_SESS_VLD_POV
#define USB_B_SESS_VLD_POV_POS        (17U)
#define USB_B_SESS_VLD_POV_LEN        (1U)
#define USB_B_SESS_VLD_POV_MSK        (((1U << USB_B_SESS_VLD_POV_LEN) - 1) << USB_B_SESS_VLD_POV_POS)
#define USB_B_SESS_VLD_POV_UMSK       (~(((1U << USB_B_SESS_VLD_POV_LEN) - 1) << USB_B_SESS_VLD_POV_POS))
#define USB_A_SESS_VLD                USB_A_SESS_VLD
#define USB_A_SESS_VLD_POS            (18U)
#define USB_A_SESS_VLD_LEN            (1U)
#define USB_A_SESS_VLD_MSK            (((1U << USB_A_SESS_VLD_LEN) - 1) << USB_A_SESS_VLD_POS)
#define USB_A_SESS_VLD_UMSK           (~(((1U << USB_A_SESS_VLD_LEN) - 1) << USB_A_SESS_VLD_POS))
#define USB_VBUS_VLD_HOV              USB_VBUS_VLD_HOV
#define USB_VBUS_VLD_HOV_POS          (19U)
#define USB_VBUS_VLD_HOV_LEN          (1U)
#define USB_VBUS_VLD_HOV_MSK          (((1U << USB_VBUS_VLD_HOV_LEN) - 1) << USB_VBUS_VLD_HOV_POS)
#define USB_VBUS_VLD_HOV_UMSK         (~(((1U << USB_VBUS_VLD_HOV_LEN) - 1) << USB_VBUS_VLD_HOV_POS))
#define USB_CROLE_HOV_POV             USB_CROLE_HOV_POV
#define USB_CROLE_HOV_POV_POS         (20U)
#define USB_CROLE_HOV_POV_LEN         (1U)
#define USB_CROLE_HOV_POV_MSK         (((1U << USB_CROLE_HOV_POV_LEN) - 1) << USB_CROLE_HOV_POV_POS)
#define USB_CROLE_HOV_POV_UMSK        (~(((1U << USB_CROLE_HOV_POV_LEN) - 1) << USB_CROLE_HOV_POV_POS))
#define USB_ID_HOV_POV                USB_ID_HOV_POV
#define USB_ID_HOV_POV_POS            (21U)
#define USB_ID_HOV_POV_LEN            (1U)
#define USB_ID_HOV_POV_MSK            (((1U << USB_ID_HOV_POV_LEN) - 1) << USB_ID_HOV_POV_POS)
#define USB_ID_HOV_POV_UMSK           (~(((1U << USB_ID_HOV_POV_LEN) - 1) << USB_ID_HOV_POV_POS))
#define USB_SPD_TYP_HOV_POV           USB_SPD_TYP_HOV_POV
#define USB_SPD_TYP_HOV_POV_POS       (22U)
#define USB_SPD_TYP_HOV_POV_LEN       (2U)
#define USB_SPD_TYP_HOV_POV_MSK       (((1U << USB_SPD_TYP_HOV_POV_LEN) - 1) << USB_SPD_TYP_HOV_POV_POS)
#define USB_SPD_TYP_HOV_POV_UMSK      (~(((1U << USB_SPD_TYP_HOV_POV_LEN) - 1) << USB_SPD_TYP_HOV_POV_POS))

/* 0x084 : OTG_ISR */
#define USB_OTG_ISR_OFFSET          (0x084)
#define USB_B_SRP_DN                USB_B_SRP_DN
#define USB_B_SRP_DN_POS            (0U)
#define USB_B_SRP_DN_LEN            (1U)
#define USB_B_SRP_DN_MSK            (((1U << USB_B_SRP_DN_LEN) - 1) << USB_B_SRP_DN_POS)
#define USB_B_SRP_DN_UMSK           (~(((1U << USB_B_SRP_DN_LEN) - 1) << USB_B_SRP_DN_POS))
#define USB_A_SRP_DET               USB_A_SRP_DET
#define USB_A_SRP_DET_POS           (4U)
#define USB_A_SRP_DET_LEN           (1U)
#define USB_A_SRP_DET_MSK           (((1U << USB_A_SRP_DET_LEN) - 1) << USB_A_SRP_DET_POS)
#define USB_A_SRP_DET_UMSK          (~(((1U << USB_A_SRP_DET_LEN) - 1) << USB_A_SRP_DET_POS))
#define USB_A_VBUS_ERR_HOV          USB_A_VBUS_ERR_HOV
#define USB_A_VBUS_ERR_HOV_POS      (5U)
#define USB_A_VBUS_ERR_HOV_LEN      (1U)
#define USB_A_VBUS_ERR_HOV_MSK      (((1U << USB_A_VBUS_ERR_HOV_LEN) - 1) << USB_A_VBUS_ERR_HOV_POS)
#define USB_A_VBUS_ERR_HOV_UMSK     (~(((1U << USB_A_VBUS_ERR_HOV_LEN) - 1) << USB_A_VBUS_ERR_HOV_POS))
#define USB_B_SESS_END_INT_POV      USB_B_SESS_END_INT_POV
#define USB_B_SESS_END_INT_POV_POS  (6U)
#define USB_B_SESS_END_INT_POV_LEN  (1U)
#define USB_B_SESS_END_INT_POV_MSK  (((1U << USB_B_SESS_END_INT_POV_LEN) - 1) << USB_B_SESS_END_INT_POV_POS)
#define USB_B_SESS_END_INT_POV_UMSK (~(((1U << USB_B_SESS_END_INT_POV_LEN) - 1) << USB_B_SESS_END_INT_POV_POS))
#define USB_RLCHG                   USB_RLCHG
#define USB_RLCHG_POS               (8U)
#define USB_RLCHG_LEN               (1U)
#define USB_RLCHG_MSK               (((1U << USB_RLCHG_LEN) - 1) << USB_RLCHG_POS)
#define USB_RLCHG_UMSK              (~(((1U << USB_RLCHG_LEN) - 1) << USB_RLCHG_POS))
#define USB_IDCHG                   USB_IDCHG
#define USB_IDCHG_POS               (9U)
#define USB_IDCHG_LEN               (1U)
#define USB_IDCHG_MSK               (((1U << USB_IDCHG_LEN) - 1) << USB_IDCHG_POS)
#define USB_IDCHG_UMSK              (~(((1U << USB_IDCHG_LEN) - 1) << USB_IDCHG_POS))
#define USB_OVC_HOV                 USB_OVC_HOV
#define USB_OVC_HOV_POS             (10U)
#define USB_OVC_HOV_LEN             (1U)
#define USB_OVC_HOV_MSK             (((1U << USB_OVC_HOV_LEN) - 1) << USB_OVC_HOV_POS)
#define USB_OVC_HOV_UMSK            (~(((1U << USB_OVC_HOV_LEN) - 1) << USB_OVC_HOV_POS))
#define USB_A_WAIT_CON_HOV          USB_A_WAIT_CON_HOV
#define USB_A_WAIT_CON_HOV_POS      (11U)
#define USB_A_WAIT_CON_HOV_LEN      (1U)
#define USB_A_WAIT_CON_HOV_MSK      (((1U << USB_A_WAIT_CON_HOV_LEN) - 1) << USB_A_WAIT_CON_HOV_POS)
#define USB_A_WAIT_CON_HOV_UMSK     (~(((1U << USB_A_WAIT_CON_HOV_LEN) - 1) << USB_A_WAIT_CON_HOV_POS))
#define USB_APLGRMV                 USB_APLGRMV
#define USB_APLGRMV_POS             (12U)
#define USB_APLGRMV_LEN             (1U)
#define USB_APLGRMV_MSK             (((1U << USB_APLGRMV_LEN) - 1) << USB_APLGRMV_POS)
#define USB_APLGRMV_UMSK            (~(((1U << USB_APLGRMV_LEN) - 1) << USB_APLGRMV_POS))

/* 0x088 : OTG_IER */
#define USB_OTG_IER_OFFSET         (0x088)
#define USB_B_SRP_DN_EN            USB_B_SRP_DN_EN
#define USB_B_SRP_DN_EN_POS        (0U)
#define USB_B_SRP_DN_EN_LEN        (1U)
#define USB_B_SRP_DN_EN_MSK        (((1U << USB_B_SRP_DN_EN_LEN) - 1) << USB_B_SRP_DN_EN_POS)
#define USB_B_SRP_DN_EN_UMSK       (~(((1U << USB_B_SRP_DN_EN_LEN) - 1) << USB_B_SRP_DN_EN_POS))
#define USB_A_SRP_DET_INT_EN       USB_A_SRP_DET_INT_EN
#define USB_A_SRP_DET_INT_EN_POS   (4U)
#define USB_A_SRP_DET_INT_EN_LEN   (1U)
#define USB_A_SRP_DET_INT_EN_MSK   (((1U << USB_A_SRP_DET_INT_EN_LEN) - 1) << USB_A_SRP_DET_INT_EN_POS)
#define USB_A_SRP_DET_INT_EN_UMSK  (~(((1U << USB_A_SRP_DET_INT_EN_LEN) - 1) << USB_A_SRP_DET_INT_EN_POS))
#define USB_A_VBUS_ERR_EN_HOV      USB_A_VBUS_ERR_EN_HOV
#define USB_A_VBUS_ERR_EN_HOV_POS  (5U)
#define USB_A_VBUS_ERR_EN_HOV_LEN  (1U)
#define USB_A_VBUS_ERR_EN_HOV_MSK  (((1U << USB_A_VBUS_ERR_EN_HOV_LEN) - 1) << USB_A_VBUS_ERR_EN_HOV_POS)
#define USB_A_VBUS_ERR_EN_HOV_UMSK (~(((1U << USB_A_VBUS_ERR_EN_HOV_LEN) - 1) << USB_A_VBUS_ERR_EN_HOV_POS))
#define USB_B_SESS_END_EN_POV      USB_B_SESS_END_EN_POV
#define USB_B_SESS_END_EN_POV_POS  (6U)
#define USB_B_SESS_END_EN_POV_LEN  (1U)
#define USB_B_SESS_END_EN_POV_MSK  (((1U << USB_B_SESS_END_EN_POV_LEN) - 1) << USB_B_SESS_END_EN_POV_POS)
#define USB_B_SESS_END_EN_POV_UMSK (~(((1U << USB_B_SESS_END_EN_POV_LEN) - 1) << USB_B_SESS_END_EN_POV_POS))
#define USB_RLCHG_EN               USB_RLCHG_EN
#define USB_RLCHG_EN_POS           (8U)
#define USB_RLCHG_EN_LEN           (1U)
#define USB_RLCHG_EN_MSK           (((1U << USB_RLCHG_EN_LEN) - 1) << USB_RLCHG_EN_POS)
#define USB_RLCHG_EN_UMSK          (~(((1U << USB_RLCHG_EN_LEN) - 1) << USB_RLCHG_EN_POS))
#define USB_IDCHG_EN               USB_IDCHG_EN
#define USB_IDCHG_EN_POS           (9U)
#define USB_IDCHG_EN_LEN           (1U)
#define USB_IDCHG_EN_MSK           (((1U << USB_IDCHG_EN_LEN) - 1) << USB_IDCHG_EN_POS)
#define USB_IDCHG_EN_UMSK          (~(((1U << USB_IDCHG_EN_LEN) - 1) << USB_IDCHG_EN_POS))
#define USB_OVC_EN_HOV             USB_OVC_EN_HOV
#define USB_OVC_EN_HOV_POS         (10U)
#define USB_OVC_EN_HOV_LEN         (1U)
#define USB_OVC_EN_HOV_MSK         (((1U << USB_OVC_EN_HOV_LEN) - 1) << USB_OVC_EN_HOV_POS)
#define USB_OVC_EN_HOV_UMSK        (~(((1U << USB_OVC_EN_HOV_LEN) - 1) << USB_OVC_EN_HOV_POS))
#define USB_A_WAIT_CON_EN_HOV      USB_A_WAIT_CON_EN_HOV
#define USB_A_WAIT_CON_EN_HOV_POS  (11U)
#define USB_A_WAIT_CON_EN_HOV_LEN  (1U)
#define USB_A_WAIT_CON_EN_HOV_MSK  (((1U << USB_A_WAIT_CON_EN_HOV_LEN) - 1) << USB_A_WAIT_CON_EN_HOV_POS)
#define USB_A_WAIT_CON_EN_HOV_UMSK (~(((1U << USB_A_WAIT_CON_EN_HOV_LEN) - 1) << USB_A_WAIT_CON_EN_HOV_POS))
#define USB_APLGRMV_EN             USB_APLGRMV_EN
#define USB_APLGRMV_EN_POS         (12U)
#define USB_APLGRMV_EN_LEN         (1U)
#define USB_APLGRMV_EN_MSK         (((1U << USB_APLGRMV_EN_LEN) - 1) << USB_APLGRMV_EN_POS)
#define USB_APLGRMV_EN_UMSK        (~(((1U << USB_APLGRMV_EN_LEN) - 1) << USB_APLGRMV_EN_POS))

/* 0x0C0 : GLB_ISR */
#define USB_GLB_ISR_OFFSET (0x0C0)
#define USB_DEV_INT        USB_DEV_INT
#define USB_DEV_INT_POS    (0U)
#define USB_DEV_INT_LEN    (1U)
#define USB_DEV_INT_MSK    (((1U << USB_DEV_INT_LEN) - 1) << USB_DEV_INT_POS)
#define USB_DEV_INT_UMSK   (~(((1U << USB_DEV_INT_LEN) - 1) << USB_DEV_INT_POS))
#define USB_OTG_INT        USB_OTG_INT
#define USB_OTG_INT_POS    (1U)
#define USB_OTG_INT_LEN    (1U)
#define USB_OTG_INT_MSK    (((1U << USB_OTG_INT_LEN) - 1) << USB_OTG_INT_POS)
#define USB_OTG_INT_UMSK   (~(((1U << USB_OTG_INT_LEN) - 1) << USB_OTG_INT_POS))
#define USB_HC_INT         USB_HC_INT
#define USB_HC_INT_POS     (2U)
#define USB_HC_INT_LEN     (1U)
#define USB_HC_INT_MSK     (((1U << USB_HC_INT_LEN) - 1) << USB_HC_INT_POS)
#define USB_HC_INT_UMSK    (~(((1U << USB_HC_INT_LEN) - 1) << USB_HC_INT_POS))

/* 0x0C4 : GLB_INT */
#define USB_GLB_INT_OFFSET    (0x0C4)
#define USB_MDEV_INT          USB_MDEV_INT
#define USB_MDEV_INT_POS      (0U)
#define USB_MDEV_INT_LEN      (1U)
#define USB_MDEV_INT_MSK      (((1U << USB_MDEV_INT_LEN) - 1) << USB_MDEV_INT_POS)
#define USB_MDEV_INT_UMSK     (~(((1U << USB_MDEV_INT_LEN) - 1) << USB_MDEV_INT_POS))
#define USB_MOTG_INT          USB_MOTG_INT
#define USB_MOTG_INT_POS      (1U)
#define USB_MOTG_INT_LEN      (1U)
#define USB_MOTG_INT_MSK      (((1U << USB_MOTG_INT_LEN) - 1) << USB_MOTG_INT_POS)
#define USB_MOTG_INT_UMSK     (~(((1U << USB_MOTG_INT_LEN) - 1) << USB_MOTG_INT_POS))
#define USB_MHC_INT           USB_MHC_INT
#define USB_MHC_INT_POS       (2U)
#define USB_MHC_INT_LEN       (1U)
#define USB_MHC_INT_MSK       (((1U << USB_MHC_INT_LEN) - 1) << USB_MHC_INT_POS)
#define USB_MHC_INT_UMSK      (~(((1U << USB_MHC_INT_LEN) - 1) << USB_MHC_INT_POS))
#define USB_INT_POLARITY      USB_INT_POLARITY
#define USB_INT_POLARITY_POS  (3U)
#define USB_INT_POLARITY_LEN  (1U)
#define USB_INT_POLARITY_MSK  (((1U << USB_INT_POLARITY_LEN) - 1) << USB_INT_POLARITY_POS)
#define USB_INT_POLARITY_UMSK (~(((1U << USB_INT_POLARITY_LEN) - 1) << USB_INT_POLARITY_POS))

/* 0x0E0 : REVISION */
#define USB_REVISION_OFFSET (0x0E0)
#define USB_REVISION        USB_REVISION
#define USB_REVISION_POS    (0U)
#define USB_REVISION_LEN    (32U)
#define USB_REVISION_MSK    (((1U << USB_REVISION_LEN) - 1) << USB_REVISION_POS)
#define USB_REVISION_UMSK   (~(((1U << USB_REVISION_LEN) - 1) << USB_REVISION_POS))

/* 0x0E4 : FEATURE */
#define USB_FEATURE_OFFSET  (0x0E4)
#define USB_DMABUFSIZE      USB_DMABUFSIZE
#define USB_DMABUFSIZE_POS  (0U)
#define USB_DMABUFSIZE_LEN  (5U)
#define USB_DMABUFSIZE_MSK  (((1U << USB_DMABUFSIZE_LEN) - 1) << USB_DMABUFSIZE_POS)
#define USB_DMABUFSIZE_UMSK (~(((1U << USB_DMABUFSIZE_LEN) - 1) << USB_DMABUFSIZE_POS))
#define USB_FIFO_NUM        USB_FIFO_NUM
#define USB_FIFO_NUM_POS    (5U)
#define USB_FIFO_NUM_LEN    (5U)
#define USB_FIFO_NUM_MSK    (((1U << USB_FIFO_NUM_LEN) - 1) << USB_FIFO_NUM_POS)
#define USB_FIFO_NUM_UMSK   (~(((1U << USB_FIFO_NUM_LEN) - 1) << USB_FIFO_NUM_POS))
#define USB_EP_NUM          USB_EP_NUM
#define USB_EP_NUM_POS      (10U)
#define USB_EP_NUM_LEN      (5U)
#define USB_EP_NUM_MSK      (((1U << USB_EP_NUM_LEN) - 1) << USB_EP_NUM_POS)
#define USB_EP_NUM_UMSK     (~(((1U << USB_EP_NUM_LEN) - 1) << USB_EP_NUM_POS))
#define USB_DEV_ONLY        USB_DEV_ONLY
#define USB_DEV_ONLY_POS    (15U)
#define USB_DEV_ONLY_LEN    (1U)
#define USB_DEV_ONLY_MSK    (((1U << USB_DEV_ONLY_LEN) - 1) << USB_DEV_ONLY_POS)
#define USB_DEV_ONLY_UMSK   (~(((1U << USB_DEV_ONLY_LEN) - 1) << USB_DEV_ONLY_POS))
#define USB_HOST_ONLY       USB_HOST_ONLY
#define USB_HOST_ONLY_POS   (16U)
#define USB_HOST_ONLY_LEN   (1U)
#define USB_HOST_ONLY_MSK   (((1U << USB_HOST_ONLY_LEN) - 1) << USB_HOST_ONLY_POS)
#define USB_HOST_ONLY_UMSK  (~(((1U << USB_HOST_ONLY_LEN) - 1) << USB_HOST_ONLY_POS))

/* 0x0E8 : AXI_CR */
#define USB_AXI_CR_OFFSET   (0x0E8)
#define USB_AXI_SGLBST      USB_AXI_SGLBST
#define USB_AXI_SGLBST_POS  (0U)
#define USB_AXI_SGLBST_LEN  (1U)
#define USB_AXI_SGLBST_MSK  (((1U << USB_AXI_SGLBST_LEN) - 1) << USB_AXI_SGLBST_POS)
#define USB_AXI_SGLBST_UMSK (~(((1U << USB_AXI_SGLBST_LEN) - 1) << USB_AXI_SGLBST_POS))

/* 0x100 : DEV_CTL */
#define USB_DEV_CTL_OFFSET         (0x100)
#define USB_CAP_RMWAKUP            USB_CAP_RMWAKUP
#define USB_CAP_RMWAKUP_POS        (0U)
#define USB_CAP_RMWAKUP_LEN        (1U)
#define USB_CAP_RMWAKUP_MSK        (((1U << USB_CAP_RMWAKUP_LEN) - 1) << USB_CAP_RMWAKUP_POS)
#define USB_CAP_RMWAKUP_UMSK       (~(((1U << USB_CAP_RMWAKUP_LEN) - 1) << USB_CAP_RMWAKUP_POS))
#define USB_HALF_SPEED_HOV         USB_HALF_SPEED_HOV
#define USB_HALF_SPEED_HOV_POS     (1U)
#define USB_HALF_SPEED_HOV_LEN     (1U)
#define USB_HALF_SPEED_HOV_MSK     (((1U << USB_HALF_SPEED_HOV_LEN) - 1) << USB_HALF_SPEED_HOV_POS)
#define USB_HALF_SPEED_HOV_UMSK    (~(((1U << USB_HALF_SPEED_HOV_LEN) - 1) << USB_HALF_SPEED_HOV_POS))
#define USB_GLINT_EN_HOV           USB_GLINT_EN_HOV
#define USB_GLINT_EN_HOV_POS       (2U)
#define USB_GLINT_EN_HOV_LEN       (1U)
#define USB_GLINT_EN_HOV_MSK       (((1U << USB_GLINT_EN_HOV_LEN) - 1) << USB_GLINT_EN_HOV_POS)
#define USB_GLINT_EN_HOV_UMSK      (~(((1U << USB_GLINT_EN_HOV_LEN) - 1) << USB_GLINT_EN_HOV_POS))
#define USB_GOSUSP                 USB_GOSUSP
#define USB_GOSUSP_POS             (3U)
#define USB_GOSUSP_LEN             (1U)
#define USB_GOSUSP_MSK             (((1U << USB_GOSUSP_LEN) - 1) << USB_GOSUSP_POS)
#define USB_GOSUSP_UMSK            (~(((1U << USB_GOSUSP_LEN) - 1) << USB_GOSUSP_POS))
#define USB_SFRST_HOV              USB_SFRST_HOV
#define USB_SFRST_HOV_POS          (4U)
#define USB_SFRST_HOV_LEN          (1U)
#define USB_SFRST_HOV_MSK          (((1U << USB_SFRST_HOV_LEN) - 1) << USB_SFRST_HOV_POS)
#define USB_SFRST_HOV_UMSK         (~(((1U << USB_SFRST_HOV_LEN) - 1) << USB_SFRST_HOV_POS))
#define USB_CHIP_EN_HOV            USB_CHIP_EN_HOV
#define USB_CHIP_EN_HOV_POS        (5U)
#define USB_CHIP_EN_HOV_LEN        (1U)
#define USB_CHIP_EN_HOV_MSK        (((1U << USB_CHIP_EN_HOV_LEN) - 1) << USB_CHIP_EN_HOV_POS)
#define USB_CHIP_EN_HOV_UMSK       (~(((1U << USB_CHIP_EN_HOV_LEN) - 1) << USB_CHIP_EN_HOV_POS))
#define USB_HS_EN_HOV              USB_HS_EN_HOV
#define USB_HS_EN_HOV_POS          (6U)
#define USB_HS_EN_HOV_LEN          (1U)
#define USB_HS_EN_HOV_MSK          (((1U << USB_HS_EN_HOV_LEN) - 1) << USB_HS_EN_HOV_POS)
#define USB_HS_EN_HOV_UMSK         (~(((1U << USB_HS_EN_HOV_LEN) - 1) << USB_HS_EN_HOV_POS))
#define USB_SYSBUS_WIDTH_HOV       USB_SYSBUS_WIDTH_HOV
#define USB_SYSBUS_WIDTH_HOV_POS   (7U)
#define USB_SYSBUS_WIDTH_HOV_LEN   (1U)
#define USB_SYSBUS_WIDTH_HOV_MSK   (((1U << USB_SYSBUS_WIDTH_HOV_LEN) - 1) << USB_SYSBUS_WIDTH_HOV_POS)
#define USB_SYSBUS_WIDTH_HOV_UMSK  (~(((1U << USB_SYSBUS_WIDTH_HOV_LEN) - 1) << USB_SYSBUS_WIDTH_HOV_POS))
#define USB_FORCE_FS               USB_FORCE_FS
#define USB_FORCE_FS_POS           (9U)
#define USB_FORCE_FS_LEN           (1U)
#define USB_FORCE_FS_MSK           (((1U << USB_FORCE_FS_LEN) - 1) << USB_FORCE_FS_POS)
#define USB_FORCE_FS_UMSK          (~(((1U << USB_FORCE_FS_LEN) - 1) << USB_FORCE_FS_POS))
#define USB_IDLE_DEGLITCH_HOV      USB_IDLE_DEGLITCH_HOV
#define USB_IDLE_DEGLITCH_HOV_POS  (10U)
#define USB_IDLE_DEGLITCH_HOV_LEN  (2U)
#define USB_IDLE_DEGLITCH_HOV_MSK  (((1U << USB_IDLE_DEGLITCH_HOV_LEN) - 1) << USB_IDLE_DEGLITCH_HOV_POS)
#define USB_IDLE_DEGLITCH_HOV_UMSK (~(((1U << USB_IDLE_DEGLITCH_HOV_LEN) - 1) << USB_IDLE_DEGLITCH_HOV_POS))
#define USB_LPM_BESL_MAX           USB_LPM_BESL_MAX
#define USB_LPM_BESL_MAX_POS       (12U)
#define USB_LPM_BESL_MAX_LEN       (4U)
#define USB_LPM_BESL_MAX_MSK       (((1U << USB_LPM_BESL_MAX_LEN) - 1) << USB_LPM_BESL_MAX_POS)
#define USB_LPM_BESL_MAX_UMSK      (~(((1U << USB_LPM_BESL_MAX_LEN) - 1) << USB_LPM_BESL_MAX_POS))
#define USB_LPM_BESL_MIN           USB_LPM_BESL_MIN
#define USB_LPM_BESL_MIN_POS       (16U)
#define USB_LPM_BESL_MIN_LEN       (4U)
#define USB_LPM_BESL_MIN_MSK       (((1U << USB_LPM_BESL_MIN_LEN) - 1) << USB_LPM_BESL_MIN_POS)
#define USB_LPM_BESL_MIN_UMSK      (~(((1U << USB_LPM_BESL_MIN_LEN) - 1) << USB_LPM_BESL_MIN_POS))
#define USB_LPM_BESL               USB_LPM_BESL
#define USB_LPM_BESL_POS           (20U)
#define USB_LPM_BESL_LEN           (4U)
#define USB_LPM_BESL_MSK           (((1U << USB_LPM_BESL_LEN) - 1) << USB_LPM_BESL_POS)
#define USB_LPM_BESL_UMSK          (~(((1U << USB_LPM_BESL_LEN) - 1) << USB_LPM_BESL_POS))
#define USB_LPM_EN                 USB_LPM_EN
#define USB_LPM_EN_POS             (25U)
#define USB_LPM_EN_LEN             (1U)
#define USB_LPM_EN_MSK             (((1U << USB_LPM_EN_LEN) - 1) << USB_LPM_EN_POS)
#define USB_LPM_EN_UMSK            (~(((1U << USB_LPM_EN_LEN) - 1) << USB_LPM_EN_POS))
#define USB_LPM_ACCEPT             USB_LPM_ACCEPT
#define USB_LPM_ACCEPT_POS         (26U)
#define USB_LPM_ACCEPT_LEN         (1U)
#define USB_LPM_ACCEPT_MSK         (((1U << USB_LPM_ACCEPT_LEN) - 1) << USB_LPM_ACCEPT_POS)
#define USB_LPM_ACCEPT_UMSK        (~(((1U << USB_LPM_ACCEPT_LEN) - 1) << USB_LPM_ACCEPT_POS))

/* 0x104 : DEV_ADR */
#define USB_DEV_ADR_OFFSET (0x104)
#define USB_DEVADR         USB_DEVADR
#define USB_DEVADR_POS     (0U)
#define USB_DEVADR_LEN     (7U)
#define USB_DEVADR_MSK     (((1U << USB_DEVADR_LEN) - 1) << USB_DEVADR_POS)
#define USB_DEVADR_UMSK    (~(((1U << USB_DEVADR_LEN) - 1) << USB_DEVADR_POS))
#define USB_AFT_CONF       USB_AFT_CONF
#define USB_AFT_CONF_POS   (7U)
#define USB_AFT_CONF_LEN   (1U)
#define USB_AFT_CONF_MSK   (((1U << USB_AFT_CONF_LEN) - 1) << USB_AFT_CONF_POS)
#define USB_AFT_CONF_UMSK  (~(((1U << USB_AFT_CONF_LEN) - 1) << USB_AFT_CONF_POS))

/* 0x108 : DEV_TST */
#define USB_DEV_TST_OFFSET       (0x108)
#define USB_TST_CLRFF_HOV        USB_TST_CLRFF_HOV
#define USB_TST_CLRFF_HOV_POS    (0U)
#define USB_TST_CLRFF_HOV_LEN    (1U)
#define USB_TST_CLRFF_HOV_MSK    (((1U << USB_TST_CLRFF_HOV_LEN) - 1) << USB_TST_CLRFF_HOV_POS)
#define USB_TST_CLRFF_HOV_UMSK   (~(((1U << USB_TST_CLRFF_HOV_LEN) - 1) << USB_TST_CLRFF_HOV_POS))
#define USB_TST_LPCX             USB_TST_LPCX
#define USB_TST_LPCX_POS         (1U)
#define USB_TST_LPCX_LEN         (1U)
#define USB_TST_LPCX_MSK         (((1U << USB_TST_LPCX_LEN) - 1) << USB_TST_LPCX_POS)
#define USB_TST_LPCX_UMSK        (~(((1U << USB_TST_LPCX_LEN) - 1) << USB_TST_LPCX_POS))
#define USB_TST_CLREA            USB_TST_CLREA
#define USB_TST_CLREA_POS        (2U)
#define USB_TST_CLREA_LEN        (1U)
#define USB_TST_CLREA_MSK        (((1U << USB_TST_CLREA_LEN) - 1) << USB_TST_CLREA_POS)
#define USB_TST_CLREA_UMSK       (~(((1U << USB_TST_CLREA_LEN) - 1) << USB_TST_CLREA_POS))
#define USB_TST_DISTO_HOV        USB_TST_DISTO_HOV
#define USB_TST_DISTO_HOV_POS    (4U)
#define USB_TST_DISTO_HOV_LEN    (1U)
#define USB_TST_DISTO_HOV_MSK    (((1U << USB_TST_DISTO_HOV_LEN) - 1) << USB_TST_DISTO_HOV_POS)
#define USB_TST_DISTO_HOV_UMSK   (~(((1U << USB_TST_DISTO_HOV_LEN) - 1) << USB_TST_DISTO_HOV_POS))
#define USB_TST_MOD_HOV          USB_TST_MOD_HOV
#define USB_TST_MOD_HOV_POS      (5U)
#define USB_TST_MOD_HOV_LEN      (1U)
#define USB_TST_MOD_HOV_MSK      (((1U << USB_TST_MOD_HOV_LEN) - 1) << USB_TST_MOD_HOV_POS)
#define USB_TST_MOD_HOV_UMSK     (~(((1U << USB_TST_MOD_HOV_LEN) - 1) << USB_TST_MOD_HOV_POS))
#define USB_DISGENSOF            USB_DISGENSOF
#define USB_DISGENSOF_POS        (6U)
#define USB_DISGENSOF_LEN        (1U)
#define USB_DISGENSOF_MSK        (((1U << USB_DISGENSOF_LEN) - 1) << USB_DISGENSOF_POS)
#define USB_DISGENSOF_UMSK       (~(((1U << USB_DISGENSOF_LEN) - 1) << USB_DISGENSOF_POS))
#define USB_TST_MOD_TYP_HOV      USB_TST_MOD_TYP_HOV
#define USB_TST_MOD_TYP_HOV_POS  (7U)
#define USB_TST_MOD_TYP_HOV_LEN  (1U)
#define USB_TST_MOD_TYP_HOV_MSK  (((1U << USB_TST_MOD_TYP_HOV_LEN) - 1) << USB_TST_MOD_TYP_HOV_POS)
#define USB_TST_MOD_TYP_HOV_UMSK (~(((1U << USB_TST_MOD_TYP_HOV_LEN) - 1) << USB_TST_MOD_TYP_HOV_POS))

/* 0x10C : DEV_SFN */
#define USB_DEV_SFN_OFFSET (0x10C)
#define USB_SOFN           USB_SOFN
#define USB_SOFN_POS       (0U)
#define USB_SOFN_LEN       (11U)
#define USB_SOFN_MSK       (((1U << USB_SOFN_LEN) - 1) << USB_SOFN_POS)
#define USB_SOFN_UMSK      (~(((1U << USB_SOFN_LEN) - 1) << USB_SOFN_POS))
#define USB_USOFN          USB_USOFN
#define USB_USOFN_POS      (11U)
#define USB_USOFN_LEN      (3U)
#define USB_USOFN_MSK      (((1U << USB_USOFN_LEN) - 1) << USB_USOFN_POS)
#define USB_USOFN_UMSK     (~(((1U << USB_USOFN_LEN) - 1) << USB_USOFN_POS))

/* 0x110 : DEV_SMT */
#define USB_DEV_SMT_OFFSET (0x110)
#define USB_SOFMT          USB_SOFMT
#define USB_SOFMT_POS      (0U)
#define USB_SOFMT_LEN      (16U)
#define USB_SOFMT_MSK      (((1U << USB_SOFMT_LEN) - 1) << USB_SOFMT_POS)
#define USB_SOFMT_UMSK     (~(((1U << USB_SOFMT_LEN) - 1) << USB_SOFMT_POS))

/* 0x114 : PHY_TST */
#define USB_PHY_TST_OFFSET  (0x114)
#define USB_UNPLUG          USB_UNPLUG
#define USB_UNPLUG_POS      (0U)
#define USB_UNPLUG_LEN      (1U)
#define USB_UNPLUG_MSK      (((1U << USB_UNPLUG_LEN) - 1) << USB_UNPLUG_POS)
#define USB_UNPLUG_UMSK     (~(((1U << USB_UNPLUG_LEN) - 1) << USB_UNPLUG_POS))
#define USB_TST_JSTA        USB_TST_JSTA
#define USB_TST_JSTA_POS    (1U)
#define USB_TST_JSTA_LEN    (1U)
#define USB_TST_JSTA_MSK    (((1U << USB_TST_JSTA_LEN) - 1) << USB_TST_JSTA_POS)
#define USB_TST_JSTA_UMSK   (~(((1U << USB_TST_JSTA_LEN) - 1) << USB_TST_JSTA_POS))
#define USB_TST_KSTA        USB_TST_KSTA
#define USB_TST_KSTA_POS    (2U)
#define USB_TST_KSTA_LEN    (1U)
#define USB_TST_KSTA_MSK    (((1U << USB_TST_KSTA_LEN) - 1) << USB_TST_KSTA_POS)
#define USB_TST_KSTA_UMSK   (~(((1U << USB_TST_KSTA_LEN) - 1) << USB_TST_KSTA_POS))
#define USB_TST_SE0NAK      USB_TST_SE0NAK
#define USB_TST_SE0NAK_POS  (3U)
#define USB_TST_SE0NAK_LEN  (1U)
#define USB_TST_SE0NAK_MSK  (((1U << USB_TST_SE0NAK_LEN) - 1) << USB_TST_SE0NAK_POS)
#define USB_TST_SE0NAK_UMSK (~(((1U << USB_TST_SE0NAK_LEN) - 1) << USB_TST_SE0NAK_POS))
#define USB_TST_PKT         USB_TST_PKT
#define USB_TST_PKT_POS     (4U)
#define USB_TST_PKT_LEN     (1U)
#define USB_TST_PKT_MSK     (((1U << USB_TST_PKT_LEN) - 1) << USB_TST_PKT_POS)
#define USB_TST_PKT_UMSK    (~(((1U << USB_TST_PKT_LEN) - 1) << USB_TST_PKT_POS))

/* 0x118 : DEV_VCTL */
#define USB_DEV_VCTL_OFFSET    (0x118)
#define USB_VCTL_HOV           USB_VCTL_HOV
#define USB_VCTL_HOV_POS       (0U)
#define USB_VCTL_HOV_LEN       (5U)
#define USB_VCTL_HOV_MSK       (((1U << USB_VCTL_HOV_LEN) - 1) << USB_VCTL_HOV_POS)
#define USB_VCTL_HOV_UMSK      (~(((1U << USB_VCTL_HOV_LEN) - 1) << USB_VCTL_HOV_POS))
#define USB_VCTLOAD_N_HOV      USB_VCTLOAD_N_HOV
#define USB_VCTLOAD_N_HOV_POS  (5U)
#define USB_VCTLOAD_N_HOV_LEN  (1U)
#define USB_VCTLOAD_N_HOV_MSK  (((1U << USB_VCTLOAD_N_HOV_LEN) - 1) << USB_VCTLOAD_N_HOV_POS)
#define USB_VCTLOAD_N_HOV_UMSK (~(((1U << USB_VCTLOAD_N_HOV_LEN) - 1) << USB_VCTLOAD_N_HOV_POS))

/* 0x11C : DEV_CXCFG */
#define USB_DEV_CXCFG_OFFSET (0x11C)
#define USB_VSTA_HOV         USB_VSTA_HOV
#define USB_VSTA_HOV_POS     (0U)
#define USB_VSTA_HOV_LEN     (8U)
#define USB_VSTA_HOV_MSK     (((1U << USB_VSTA_HOV_LEN) - 1) << USB_VSTA_HOV_POS)
#define USB_VSTA_HOV_UMSK    (~(((1U << USB_VSTA_HOV_LEN) - 1) << USB_VSTA_HOV_POS))

/* 0x120 : DEV_CXCFE */
#define USB_DEV_CXCFE_OFFSET (0x120)
#define USB_CX_DONE          USB_CX_DONE
#define USB_CX_DONE_POS      (0U)
#define USB_CX_DONE_LEN      (1U)
#define USB_CX_DONE_MSK      (((1U << USB_CX_DONE_LEN) - 1) << USB_CX_DONE_POS)
#define USB_CX_DONE_UMSK     (~(((1U << USB_CX_DONE_LEN) - 1) << USB_CX_DONE_POS))
#define USB_TST_PKDONE       USB_TST_PKDONE
#define USB_TST_PKDONE_POS   (1U)
#define USB_TST_PKDONE_LEN   (1U)
#define USB_TST_PKDONE_MSK   (((1U << USB_TST_PKDONE_LEN) - 1) << USB_TST_PKDONE_POS)
#define USB_TST_PKDONE_UMSK  (~(((1U << USB_TST_PKDONE_LEN) - 1) << USB_TST_PKDONE_POS))
#define USB_CX_STL           USB_CX_STL
#define USB_CX_STL_POS       (2U)
#define USB_CX_STL_LEN       (1U)
#define USB_CX_STL_MSK       (((1U << USB_CX_STL_LEN) - 1) << USB_CX_STL_POS)
#define USB_CX_STL_UMSK      (~(((1U << USB_CX_STL_LEN) - 1) << USB_CX_STL_POS))
#define USB_CX_CLR           USB_CX_CLR
#define USB_CX_CLR_POS       (3U)
#define USB_CX_CLR_LEN       (1U)
#define USB_CX_CLR_MSK       (((1U << USB_CX_CLR_LEN) - 1) << USB_CX_CLR_POS)
#define USB_CX_CLR_UMSK      (~(((1U << USB_CX_CLR_LEN) - 1) << USB_CX_CLR_POS))
#define USB_CX_FUL           USB_CX_FUL
#define USB_CX_FUL_POS       (4U)
#define USB_CX_FUL_LEN       (1U)
#define USB_CX_FUL_MSK       (((1U << USB_CX_FUL_LEN) - 1) << USB_CX_FUL_POS)
#define USB_CX_FUL_UMSK      (~(((1U << USB_CX_FUL_LEN) - 1) << USB_CX_FUL_POS))
#define USB_CX_EMP           USB_CX_EMP
#define USB_CX_EMP_POS       (5U)
#define USB_CX_EMP_LEN       (1U)
#define USB_CX_EMP_MSK       (((1U << USB_CX_EMP_LEN) - 1) << USB_CX_EMP_POS)
#define USB_CX_EMP_UMSK      (~(((1U << USB_CX_EMP_LEN) - 1) << USB_CX_EMP_POS))
#define USB_F0_EMP           USB_F0_EMP
#define USB_F0_EMP_POS       (8U)
#define USB_F0_EMP_LEN       (1U)
#define USB_F0_EMP_MSK       (((1U << USB_F0_EMP_LEN) - 1) << USB_F0_EMP_POS)
#define USB_F0_EMP_UMSK      (~(((1U << USB_F0_EMP_LEN) - 1) << USB_F0_EMP_POS))
#define USB_F1_EMP           USB_F1_EMP
#define USB_F1_EMP_POS       (9U)
#define USB_F1_EMP_LEN       (1U)
#define USB_F1_EMP_MSK       (((1U << USB_F1_EMP_LEN) - 1) << USB_F1_EMP_POS)
#define USB_F1_EMP_UMSK      (~(((1U << USB_F1_EMP_LEN) - 1) << USB_F1_EMP_POS))
#define USB_F2_EMP           USB_F2_EMP
#define USB_F2_EMP_POS       (10U)
#define USB_F2_EMP_LEN       (1U)
#define USB_F2_EMP_MSK       (((1U << USB_F2_EMP_LEN) - 1) << USB_F2_EMP_POS)
#define USB_F2_EMP_UMSK      (~(((1U << USB_F2_EMP_LEN) - 1) << USB_F2_EMP_POS))
#define USB_F3_EMP           USB_F3_EMP
#define USB_F3_EMP_POS       (11U)
#define USB_F3_EMP_LEN       (1U)
#define USB_F3_EMP_MSK       (((1U << USB_F3_EMP_LEN) - 1) << USB_F3_EMP_POS)
#define USB_F3_EMP_UMSK      (~(((1U << USB_F3_EMP_LEN) - 1) << USB_F3_EMP_POS))
#define USB_F4_EMP           USB_F4_EMP
#define USB_F4_EMP_POS       (12U)
#define USB_F4_EMP_LEN       (1U)
#define USB_F4_EMP_MSK       (((1U << USB_F4_EMP_LEN) - 1) << USB_F4_EMP_POS)
#define USB_F4_EMP_UMSK      (~(((1U << USB_F4_EMP_LEN) - 1) << USB_F4_EMP_POS))
#define USB_F5_EMP           USB_F5_EMP
#define USB_F5_EMP_POS       (13U)
#define USB_F5_EMP_LEN       (1U)
#define USB_F5_EMP_MSK       (((1U << USB_F5_EMP_LEN) - 1) << USB_F5_EMP_POS)
#define USB_F5_EMP_UMSK      (~(((1U << USB_F5_EMP_LEN) - 1) << USB_F5_EMP_POS))
#define USB_F6_EMP           USB_F6_EMP
#define USB_F6_EMP_POS       (14U)
#define USB_F6_EMP_LEN       (1U)
#define USB_F6_EMP_MSK       (((1U << USB_F6_EMP_LEN) - 1) << USB_F6_EMP_POS)
#define USB_F6_EMP_UMSK      (~(((1U << USB_F6_EMP_LEN) - 1) << USB_F6_EMP_POS))
#define USB_F7_EMP           USB_F7_EMP
#define USB_F7_EMP_POS       (15U)
#define USB_F7_EMP_LEN       (1U)
#define USB_F7_EMP_MSK       (((1U << USB_F7_EMP_LEN) - 1) << USB_F7_EMP_POS)
#define USB_F7_EMP_UMSK      (~(((1U << USB_F7_EMP_LEN) - 1) << USB_F7_EMP_POS))
#define USB_F8_EMP           USB_F8_EMP
#define USB_F8_EMP_POS       (16U)
#define USB_F8_EMP_LEN       (1U)
#define USB_F8_EMP_MSK       (((1U << USB_F8_EMP_LEN) - 1) << USB_F8_EMP_POS)
#define USB_F8_EMP_UMSK      (~(((1U << USB_F8_EMP_LEN) - 1) << USB_F8_EMP_POS))
#define USB_F9_EMP           USB_F9_EMP
#define USB_F9_EMP_POS       (17U)
#define USB_F9_EMP_LEN       (1U)
#define USB_F9_EMP_MSK       (((1U << USB_F9_EMP_LEN) - 1) << USB_F9_EMP_POS)
#define USB_F9_EMP_UMSK      (~(((1U << USB_F9_EMP_LEN) - 1) << USB_F9_EMP_POS))
#define USB_F10_EMP          USB_F10_EMP
#define USB_F10_EMP_POS      (18U)
#define USB_F10_EMP_LEN      (1U)
#define USB_F10_EMP_MSK      (((1U << USB_F10_EMP_LEN) - 1) << USB_F10_EMP_POS)
#define USB_F10_EMP_UMSK     (~(((1U << USB_F10_EMP_LEN) - 1) << USB_F10_EMP_POS))
#define USB_F11_EMP          USB_F11_EMP
#define USB_F11_EMP_POS      (19U)
#define USB_F11_EMP_LEN      (1U)
#define USB_F11_EMP_MSK      (((1U << USB_F11_EMP_LEN) - 1) << USB_F11_EMP_POS)
#define USB_F11_EMP_UMSK     (~(((1U << USB_F11_EMP_LEN) - 1) << USB_F11_EMP_POS))
#define USB_F12_EMP          USB_F12_EMP
#define USB_F12_EMP_POS      (20U)
#define USB_F12_EMP_LEN      (1U)
#define USB_F12_EMP_MSK      (((1U << USB_F12_EMP_LEN) - 1) << USB_F12_EMP_POS)
#define USB_F12_EMP_UMSK     (~(((1U << USB_F12_EMP_LEN) - 1) << USB_F12_EMP_POS))
#define USB_F13_EMP          USB_F13_EMP
#define USB_F13_EMP_POS      (21U)
#define USB_F13_EMP_LEN      (1U)
#define USB_F13_EMP_MSK      (((1U << USB_F13_EMP_LEN) - 1) << USB_F13_EMP_POS)
#define USB_F13_EMP_UMSK     (~(((1U << USB_F13_EMP_LEN) - 1) << USB_F13_EMP_POS))
#define USB_F14_EMP          USB_F14_EMP
#define USB_F14_EMP_POS      (22U)
#define USB_F14_EMP_LEN      (1U)
#define USB_F14_EMP_MSK      (((1U << USB_F14_EMP_LEN) - 1) << USB_F14_EMP_POS)
#define USB_F14_EMP_UMSK     (~(((1U << USB_F14_EMP_LEN) - 1) << USB_F14_EMP_POS))
#define USB_F15_EMP          USB_F15_EMP
#define USB_F15_EMP_POS      (23U)
#define USB_F15_EMP_LEN      (1U)
#define USB_F15_EMP_MSK      (((1U << USB_F15_EMP_LEN) - 1) << USB_F15_EMP_POS)
#define USB_F15_EMP_UMSK     (~(((1U << USB_F15_EMP_LEN) - 1) << USB_F15_EMP_POS))
#define USB_CX_FNT           USB_CX_FNT
#define USB_CX_FNT_POS       (24U)
#define USB_CX_FNT_LEN       (7U)
#define USB_CX_FNT_MSK       (((1U << USB_CX_FNT_LEN) - 1) << USB_CX_FNT_POS)
#define USB_CX_FNT_UMSK      (~(((1U << USB_CX_FNT_LEN) - 1) << USB_CX_FNT_POS))

/* 0x124 : DEV_ICR */
#define USB_DEV_ICR_OFFSET (0x124)
#define USB_IDLE_CNT       USB_IDLE_CNT
#define USB_IDLE_CNT_POS   (0U)
#define USB_IDLE_CNT_LEN   (3U)
#define USB_IDLE_CNT_MSK   (((1U << USB_IDLE_CNT_LEN) - 1) << USB_IDLE_CNT_POS)
#define USB_IDLE_CNT_UMSK  (~(((1U << USB_IDLE_CNT_LEN) - 1) << USB_IDLE_CNT_POS))

/* 0x130 : DEV_MIGR */
#define USB_DEV_MIGR_OFFSET (0x130)
#define USB_MINT_G0         USB_MINT_G0
#define USB_MINT_G0_POS     (0U)
#define USB_MINT_G0_LEN     (1U)
#define USB_MINT_G0_MSK     (((1U << USB_MINT_G0_LEN) - 1) << USB_MINT_G0_POS)
#define USB_MINT_G0_UMSK    (~(((1U << USB_MINT_G0_LEN) - 1) << USB_MINT_G0_POS))
#define USB_MINT_G1         USB_MINT_G1
#define USB_MINT_G1_POS     (1U)
#define USB_MINT_G1_LEN     (1U)
#define USB_MINT_G1_MSK     (((1U << USB_MINT_G1_LEN) - 1) << USB_MINT_G1_POS)
#define USB_MINT_G1_UMSK    (~(((1U << USB_MINT_G1_LEN) - 1) << USB_MINT_G1_POS))
#define USB_MINT_G2         USB_MINT_G2
#define USB_MINT_G2_POS     (2U)
#define USB_MINT_G2_LEN     (1U)
#define USB_MINT_G2_MSK     (((1U << USB_MINT_G2_LEN) - 1) << USB_MINT_G2_POS)
#define USB_MINT_G2_UMSK    (~(((1U << USB_MINT_G2_LEN) - 1) << USB_MINT_G2_POS))
#define USB_MINT_G3         USB_MINT_G3
#define USB_MINT_G3_POS     (3U)
#define USB_MINT_G3_LEN     (1U)
#define USB_MINT_G3_MSK     (((1U << USB_MINT_G3_LEN) - 1) << USB_MINT_G3_POS)
#define USB_MINT_G3_UMSK    (~(((1U << USB_MINT_G3_LEN) - 1) << USB_MINT_G3_POS))
#define USB_MINT_G4         USB_MINT_G4
#define USB_MINT_G4_POS     (4U)
#define USB_MINT_G4_LEN     (1U)
#define USB_MINT_G4_MSK     (((1U << USB_MINT_G4_LEN) - 1) << USB_MINT_G4_POS)
#define USB_MINT_G4_UMSK    (~(((1U << USB_MINT_G4_LEN) - 1) << USB_MINT_G4_POS))

/* 0x134 : DEV_MISG0 */
#define USB_DEV_MISG0_OFFSET      (0x134)
#define USB_MCX_SETUP_INT         USB_MCX_SETUP_INT
#define USB_MCX_SETUP_INT_POS     (0U)
#define USB_MCX_SETUP_INT_LEN     (1U)
#define USB_MCX_SETUP_INT_MSK     (((1U << USB_MCX_SETUP_INT_LEN) - 1) << USB_MCX_SETUP_INT_POS)
#define USB_MCX_SETUP_INT_UMSK    (~(((1U << USB_MCX_SETUP_INT_LEN) - 1) << USB_MCX_SETUP_INT_POS))
#define USB_MCX_IN_INT            USB_MCX_IN_INT
#define USB_MCX_IN_INT_POS        (1U)
#define USB_MCX_IN_INT_LEN        (1U)
#define USB_MCX_IN_INT_MSK        (((1U << USB_MCX_IN_INT_LEN) - 1) << USB_MCX_IN_INT_POS)
#define USB_MCX_IN_INT_UMSK       (~(((1U << USB_MCX_IN_INT_LEN) - 1) << USB_MCX_IN_INT_POS))
#define USB_MCX_OUT_INT           USB_MCX_OUT_INT
#define USB_MCX_OUT_INT_POS       (2U)
#define USB_MCX_OUT_INT_LEN       (1U)
#define USB_MCX_OUT_INT_MSK       (((1U << USB_MCX_OUT_INT_LEN) - 1) << USB_MCX_OUT_INT_POS)
#define USB_MCX_OUT_INT_UMSK      (~(((1U << USB_MCX_OUT_INT_LEN) - 1) << USB_MCX_OUT_INT_POS))
#define USB_MCX_COMFAIL_INT       USB_MCX_COMFAIL_INT
#define USB_MCX_COMFAIL_INT_POS   (4U)
#define USB_MCX_COMFAIL_INT_LEN   (1U)
#define USB_MCX_COMFAIL_INT_MSK   (((1U << USB_MCX_COMFAIL_INT_LEN) - 1) << USB_MCX_COMFAIL_INT_POS)
#define USB_MCX_COMFAIL_INT_UMSK  (~(((1U << USB_MCX_COMFAIL_INT_LEN) - 1) << USB_MCX_COMFAIL_INT_POS))
#define USB_MCX_COMABORT_INT      USB_MCX_COMABORT_INT
#define USB_MCX_COMABORT_INT_POS  (5U)
#define USB_MCX_COMABORT_INT_LEN  (1U)
#define USB_MCX_COMABORT_INT_MSK  (((1U << USB_MCX_COMABORT_INT_LEN) - 1) << USB_MCX_COMABORT_INT_POS)
#define USB_MCX_COMABORT_INT_UMSK (~(((1U << USB_MCX_COMABORT_INT_LEN) - 1) << USB_MCX_COMABORT_INT_POS))

/* 0x138 : DEV_MISG1 */
#define USB_DEV_MISG1_OFFSET (0x138)
#define USB_MF0_OUT_INT      USB_MF0_OUT_INT
#define USB_MF0_OUT_INT_POS  (0U)
#define USB_MF0_OUT_INT_LEN  (1U)
#define USB_MF0_OUT_INT_MSK  (((1U << USB_MF0_OUT_INT_LEN) - 1) << USB_MF0_OUT_INT_POS)
#define USB_MF0_OUT_INT_UMSK (~(((1U << USB_MF0_OUT_INT_LEN) - 1) << USB_MF0_OUT_INT_POS))
#define USB_MF0_SPK_INT      USB_MF0_SPK_INT
#define USB_MF0_SPK_INT_POS  (1U)
#define USB_MF0_SPK_INT_LEN  (1U)
#define USB_MF0_SPK_INT_MSK  (((1U << USB_MF0_SPK_INT_LEN) - 1) << USB_MF0_SPK_INT_POS)
#define USB_MF0_SPK_INT_UMSK (~(((1U << USB_MF0_SPK_INT_LEN) - 1) << USB_MF0_SPK_INT_POS))
#define USB_MF1_OUT_INT      USB_MF1_OUT_INT
#define USB_MF1_OUT_INT_POS  (2U)
#define USB_MF1_OUT_INT_LEN  (1U)
#define USB_MF1_OUT_INT_MSK  (((1U << USB_MF1_OUT_INT_LEN) - 1) << USB_MF1_OUT_INT_POS)
#define USB_MF1_OUT_INT_UMSK (~(((1U << USB_MF1_OUT_INT_LEN) - 1) << USB_MF1_OUT_INT_POS))
#define USB_MF1_SPK_INT      USB_MF1_SPK_INT
#define USB_MF1_SPK_INT_POS  (3U)
#define USB_MF1_SPK_INT_LEN  (1U)
#define USB_MF1_SPK_INT_MSK  (((1U << USB_MF1_SPK_INT_LEN) - 1) << USB_MF1_SPK_INT_POS)
#define USB_MF1_SPK_INT_UMSK (~(((1U << USB_MF1_SPK_INT_LEN) - 1) << USB_MF1_SPK_INT_POS))
#define USB_MF2_OUT_INT      USB_MF2_OUT_INT
#define USB_MF2_OUT_INT_POS  (4U)
#define USB_MF2_OUT_INT_LEN  (1U)
#define USB_MF2_OUT_INT_MSK  (((1U << USB_MF2_OUT_INT_LEN) - 1) << USB_MF2_OUT_INT_POS)
#define USB_MF2_OUT_INT_UMSK (~(((1U << USB_MF2_OUT_INT_LEN) - 1) << USB_MF2_OUT_INT_POS))
#define USB_MF2_SPK_INT      USB_MF2_SPK_INT
#define USB_MF2_SPK_INT_POS  (5U)
#define USB_MF2_SPK_INT_LEN  (1U)
#define USB_MF2_SPK_INT_MSK  (((1U << USB_MF2_SPK_INT_LEN) - 1) << USB_MF2_SPK_INT_POS)
#define USB_MF2_SPK_INT_UMSK (~(((1U << USB_MF2_SPK_INT_LEN) - 1) << USB_MF2_SPK_INT_POS))
#define USB_MF3_OUT_INT      USB_MF3_OUT_INT
#define USB_MF3_OUT_INT_POS  (6U)
#define USB_MF3_OUT_INT_LEN  (1U)
#define USB_MF3_OUT_INT_MSK  (((1U << USB_MF3_OUT_INT_LEN) - 1) << USB_MF3_OUT_INT_POS)
#define USB_MF3_OUT_INT_UMSK (~(((1U << USB_MF3_OUT_INT_LEN) - 1) << USB_MF3_OUT_INT_POS))
#define USB_MF3_SPK_INT      USB_MF3_SPK_INT
#define USB_MF3_SPK_INT_POS  (7U)
#define USB_MF3_SPK_INT_LEN  (1U)
#define USB_MF3_SPK_INT_MSK  (((1U << USB_MF3_SPK_INT_LEN) - 1) << USB_MF3_SPK_INT_POS)
#define USB_MF3_SPK_INT_UMSK (~(((1U << USB_MF3_SPK_INT_LEN) - 1) << USB_MF3_SPK_INT_POS))
#define USB_MF4_OUT_INT      USB_MF4_OUT_INT
#define USB_MF4_OUT_INT_POS  (8U)
#define USB_MF4_OUT_INT_LEN  (1U)
#define USB_MF4_OUT_INT_MSK  (((1U << USB_MF4_OUT_INT_LEN) - 1) << USB_MF4_OUT_INT_POS)
#define USB_MF4_OUT_INT_UMSK (~(((1U << USB_MF4_OUT_INT_LEN) - 1) << USB_MF4_OUT_INT_POS))
#define USB_MF4_SPK_INT      USB_MF4_SPK_INT
#define USB_MF4_SPK_INT_POS  (9U)
#define USB_MF4_SPK_INT_LEN  (1U)
#define USB_MF4_SPK_INT_MSK  (((1U << USB_MF4_SPK_INT_LEN) - 1) << USB_MF4_SPK_INT_POS)
#define USB_MF4_SPK_INT_UMSK (~(((1U << USB_MF4_SPK_INT_LEN) - 1) << USB_MF4_SPK_INT_POS))
#define USB_MF5_OUT_INT      USB_MF5_OUT_INT
#define USB_MF5_OUT_INT_POS  (10U)
#define USB_MF5_OUT_INT_LEN  (1U)
#define USB_MF5_OUT_INT_MSK  (((1U << USB_MF5_OUT_INT_LEN) - 1) << USB_MF5_OUT_INT_POS)
#define USB_MF5_OUT_INT_UMSK (~(((1U << USB_MF5_OUT_INT_LEN) - 1) << USB_MF5_OUT_INT_POS))
#define USB_MF5_SPK_INT      USB_MF5_SPK_INT
#define USB_MF5_SPK_INT_POS  (11U)
#define USB_MF5_SPK_INT_LEN  (1U)
#define USB_MF5_SPK_INT_MSK  (((1U << USB_MF5_SPK_INT_LEN) - 1) << USB_MF5_SPK_INT_POS)
#define USB_MF5_SPK_INT_UMSK (~(((1U << USB_MF5_SPK_INT_LEN) - 1) << USB_MF5_SPK_INT_POS))
#define USB_MF6_OUT_INT      USB_MF6_OUT_INT
#define USB_MF6_OUT_INT_POS  (12U)
#define USB_MF6_OUT_INT_LEN  (1U)
#define USB_MF6_OUT_INT_MSK  (((1U << USB_MF6_OUT_INT_LEN) - 1) << USB_MF6_OUT_INT_POS)
#define USB_MF6_OUT_INT_UMSK (~(((1U << USB_MF6_OUT_INT_LEN) - 1) << USB_MF6_OUT_INT_POS))
#define USB_MF6_SPK_INT      USB_MF6_SPK_INT
#define USB_MF6_SPK_INT_POS  (13U)
#define USB_MF6_SPK_INT_LEN  (1U)
#define USB_MF6_SPK_INT_MSK  (((1U << USB_MF6_SPK_INT_LEN) - 1) << USB_MF6_SPK_INT_POS)
#define USB_MF6_SPK_INT_UMSK (~(((1U << USB_MF6_SPK_INT_LEN) - 1) << USB_MF6_SPK_INT_POS))
#define USB_MF7_OUT_INT      USB_MF7_OUT_INT
#define USB_MF7_OUT_INT_POS  (14U)
#define USB_MF7_OUT_INT_LEN  (1U)
#define USB_MF7_OUT_INT_MSK  (((1U << USB_MF7_OUT_INT_LEN) - 1) << USB_MF7_OUT_INT_POS)
#define USB_MF7_OUT_INT_UMSK (~(((1U << USB_MF7_OUT_INT_LEN) - 1) << USB_MF7_OUT_INT_POS))
#define USB_MF7_SPK_INT      USB_MF7_SPK_INT
#define USB_MF7_SPK_INT_POS  (15U)
#define USB_MF7_SPK_INT_LEN  (1U)
#define USB_MF7_SPK_INT_MSK  (((1U << USB_MF7_SPK_INT_LEN) - 1) << USB_MF7_SPK_INT_POS)
#define USB_MF7_SPK_INT_UMSK (~(((1U << USB_MF7_SPK_INT_LEN) - 1) << USB_MF7_SPK_INT_POS))
#define USB_MF0_IN_INT       USB_MF0_IN_INT
#define USB_MF0_IN_INT_POS   (16U)
#define USB_MF0_IN_INT_LEN   (1U)
#define USB_MF0_IN_INT_MSK   (((1U << USB_MF0_IN_INT_LEN) - 1) << USB_MF0_IN_INT_POS)
#define USB_MF0_IN_INT_UMSK  (~(((1U << USB_MF0_IN_INT_LEN) - 1) << USB_MF0_IN_INT_POS))
#define USB_MF1_IN_INT       USB_MF1_IN_INT
#define USB_MF1_IN_INT_POS   (17U)
#define USB_MF1_IN_INT_LEN   (1U)
#define USB_MF1_IN_INT_MSK   (((1U << USB_MF1_IN_INT_LEN) - 1) << USB_MF1_IN_INT_POS)
#define USB_MF1_IN_INT_UMSK  (~(((1U << USB_MF1_IN_INT_LEN) - 1) << USB_MF1_IN_INT_POS))
#define USB_MF2_IN_INT       USB_MF2_IN_INT
#define USB_MF2_IN_INT_POS   (18U)
#define USB_MF2_IN_INT_LEN   (1U)
#define USB_MF2_IN_INT_MSK   (((1U << USB_MF2_IN_INT_LEN) - 1) << USB_MF2_IN_INT_POS)
#define USB_MF2_IN_INT_UMSK  (~(((1U << USB_MF2_IN_INT_LEN) - 1) << USB_MF2_IN_INT_POS))
#define USB_MF3_IN_INT       USB_MF3_IN_INT
#define USB_MF3_IN_INT_POS   (19U)
#define USB_MF3_IN_INT_LEN   (1U)
#define USB_MF3_IN_INT_MSK   (((1U << USB_MF3_IN_INT_LEN) - 1) << USB_MF3_IN_INT_POS)
#define USB_MF3_IN_INT_UMSK  (~(((1U << USB_MF3_IN_INT_LEN) - 1) << USB_MF3_IN_INT_POS))
#define USB_MF4_IN_INT       USB_MF4_IN_INT
#define USB_MF4_IN_INT_POS   (20U)
#define USB_MF4_IN_INT_LEN   (1U)
#define USB_MF4_IN_INT_MSK   (((1U << USB_MF4_IN_INT_LEN) - 1) << USB_MF4_IN_INT_POS)
#define USB_MF4_IN_INT_UMSK  (~(((1U << USB_MF4_IN_INT_LEN) - 1) << USB_MF4_IN_INT_POS))
#define USB_MF5_IN_INT       USB_MF5_IN_INT
#define USB_MF5_IN_INT_POS   (21U)
#define USB_MF5_IN_INT_LEN   (1U)
#define USB_MF5_IN_INT_MSK   (((1U << USB_MF5_IN_INT_LEN) - 1) << USB_MF5_IN_INT_POS)
#define USB_MF5_IN_INT_UMSK  (~(((1U << USB_MF5_IN_INT_LEN) - 1) << USB_MF5_IN_INT_POS))
#define USB_MF6_IN_INT       USB_MF6_IN_INT
#define USB_MF6_IN_INT_POS   (22U)
#define USB_MF6_IN_INT_LEN   (1U)
#define USB_MF6_IN_INT_MSK   (((1U << USB_MF6_IN_INT_LEN) - 1) << USB_MF6_IN_INT_POS)
#define USB_MF6_IN_INT_UMSK  (~(((1U << USB_MF6_IN_INT_LEN) - 1) << USB_MF6_IN_INT_POS))
#define USB_MF7_IN_INT       USB_MF7_IN_INT
#define USB_MF7_IN_INT_POS   (23U)
#define USB_MF7_IN_INT_LEN   (1U)
#define USB_MF7_IN_INT_MSK   (((1U << USB_MF7_IN_INT_LEN) - 1) << USB_MF7_IN_INT_POS)
#define USB_MF7_IN_INT_UMSK  (~(((1U << USB_MF7_IN_INT_LEN) - 1) << USB_MF7_IN_INT_POS))
#define USB_MF8_IN_INT       USB_MF8_IN_INT
#define USB_MF8_IN_INT_POS   (24U)
#define USB_MF8_IN_INT_LEN   (1U)
#define USB_MF8_IN_INT_MSK   (((1U << USB_MF8_IN_INT_LEN) - 1) << USB_MF8_IN_INT_POS)
#define USB_MF8_IN_INT_UMSK  (~(((1U << USB_MF8_IN_INT_LEN) - 1) << USB_MF8_IN_INT_POS))
#define USB_MF9_IN_INT       USB_MF9_IN_INT
#define USB_MF9_IN_INT_POS   (25U)
#define USB_MF9_IN_INT_LEN   (1U)
#define USB_MF9_IN_INT_MSK   (((1U << USB_MF9_IN_INT_LEN) - 1) << USB_MF9_IN_INT_POS)
#define USB_MF9_IN_INT_UMSK  (~(((1U << USB_MF9_IN_INT_LEN) - 1) << USB_MF9_IN_INT_POS))
#define USB_MF10_IN_INT      USB_MF10_IN_INT
#define USB_MF10_IN_INT_POS  (26U)
#define USB_MF10_IN_INT_LEN  (1U)
#define USB_MF10_IN_INT_MSK  (((1U << USB_MF10_IN_INT_LEN) - 1) << USB_MF10_IN_INT_POS)
#define USB_MF10_IN_INT_UMSK (~(((1U << USB_MF10_IN_INT_LEN) - 1) << USB_MF10_IN_INT_POS))
#define USB_MF11_IN_INT      USB_MF11_IN_INT
#define USB_MF11_IN_INT_POS  (27U)
#define USB_MF11_IN_INT_LEN  (1U)
#define USB_MF11_IN_INT_MSK  (((1U << USB_MF11_IN_INT_LEN) - 1) << USB_MF11_IN_INT_POS)
#define USB_MF11_IN_INT_UMSK (~(((1U << USB_MF11_IN_INT_LEN) - 1) << USB_MF11_IN_INT_POS))
#define USB_MF12_IN_INT      USB_MF12_IN_INT
#define USB_MF12_IN_INT_POS  (28U)
#define USB_MF12_IN_INT_LEN  (1U)
#define USB_MF12_IN_INT_MSK  (((1U << USB_MF12_IN_INT_LEN) - 1) << USB_MF12_IN_INT_POS)
#define USB_MF12_IN_INT_UMSK (~(((1U << USB_MF12_IN_INT_LEN) - 1) << USB_MF12_IN_INT_POS))
#define USB_MF13_IN_INT      USB_MF13_IN_INT
#define USB_MF13_IN_INT_POS  (29U)
#define USB_MF13_IN_INT_LEN  (1U)
#define USB_MF13_IN_INT_MSK  (((1U << USB_MF13_IN_INT_LEN) - 1) << USB_MF13_IN_INT_POS)
#define USB_MF13_IN_INT_UMSK (~(((1U << USB_MF13_IN_INT_LEN) - 1) << USB_MF13_IN_INT_POS))
#define USB_MF14_IN_INT      USB_MF14_IN_INT
#define USB_MF14_IN_INT_POS  (30U)
#define USB_MF14_IN_INT_LEN  (1U)
#define USB_MF14_IN_INT_MSK  (((1U << USB_MF14_IN_INT_LEN) - 1) << USB_MF14_IN_INT_POS)
#define USB_MF14_IN_INT_UMSK (~(((1U << USB_MF14_IN_INT_LEN) - 1) << USB_MF14_IN_INT_POS))
#define USB_MF15_IN_INT      USB_MF15_IN_INT
#define USB_MF15_IN_INT_POS  (31U)
#define USB_MF15_IN_INT_LEN  (1U)
#define USB_MF15_IN_INT_MSK  (((1U << USB_MF15_IN_INT_LEN) - 1) << USB_MF15_IN_INT_POS)
#define USB_MF15_IN_INT_UMSK (~(((1U << USB_MF15_IN_INT_LEN) - 1) << USB_MF15_IN_INT_POS))

/* 0x13C : DEV_MISG2 */
#define USB_DEV_MISG2_OFFSET        (0x13C)
#define USB_MUSBRST_INT             USB_MUSBRST_INT
#define USB_MUSBRST_INT_POS         (0U)
#define USB_MUSBRST_INT_LEN         (1U)
#define USB_MUSBRST_INT_MSK         (((1U << USB_MUSBRST_INT_LEN) - 1) << USB_MUSBRST_INT_POS)
#define USB_MUSBRST_INT_UMSK        (~(((1U << USB_MUSBRST_INT_LEN) - 1) << USB_MUSBRST_INT_POS))
#define USB_MSUSP_INT               USB_MSUSP_INT
#define USB_MSUSP_INT_POS           (1U)
#define USB_MSUSP_INT_LEN           (1U)
#define USB_MSUSP_INT_MSK           (((1U << USB_MSUSP_INT_LEN) - 1) << USB_MSUSP_INT_POS)
#define USB_MSUSP_INT_UMSK          (~(((1U << USB_MSUSP_INT_LEN) - 1) << USB_MSUSP_INT_POS))
#define USB_MRESM_INT               USB_MRESM_INT
#define USB_MRESM_INT_POS           (2U)
#define USB_MRESM_INT_LEN           (1U)
#define USB_MRESM_INT_MSK           (((1U << USB_MRESM_INT_LEN) - 1) << USB_MRESM_INT_POS)
#define USB_MRESM_INT_UMSK          (~(((1U << USB_MRESM_INT_LEN) - 1) << USB_MRESM_INT_POS))
#define USB_MSEQ_ERR_INT            USB_MSEQ_ERR_INT
#define USB_MSEQ_ERR_INT_POS        (3U)
#define USB_MSEQ_ERR_INT_LEN        (1U)
#define USB_MSEQ_ERR_INT_MSK        (((1U << USB_MSEQ_ERR_INT_LEN) - 1) << USB_MSEQ_ERR_INT_POS)
#define USB_MSEQ_ERR_INT_UMSK       (~(((1U << USB_MSEQ_ERR_INT_LEN) - 1) << USB_MSEQ_ERR_INT_POS))
#define USB_MSEQ_ABORT_INT          USB_MSEQ_ABORT_INT
#define USB_MSEQ_ABORT_INT_POS      (4U)
#define USB_MSEQ_ABORT_INT_LEN      (1U)
#define USB_MSEQ_ABORT_INT_MSK      (((1U << USB_MSEQ_ABORT_INT_LEN) - 1) << USB_MSEQ_ABORT_INT_POS)
#define USB_MSEQ_ABORT_INT_UMSK     (~(((1U << USB_MSEQ_ABORT_INT_LEN) - 1) << USB_MSEQ_ABORT_INT_POS))
#define USB_MTX0BYTE_INT            USB_MTX0BYTE_INT
#define USB_MTX0BYTE_INT_POS        (5U)
#define USB_MTX0BYTE_INT_LEN        (1U)
#define USB_MTX0BYTE_INT_MSK        (((1U << USB_MTX0BYTE_INT_LEN) - 1) << USB_MTX0BYTE_INT_POS)
#define USB_MTX0BYTE_INT_UMSK       (~(((1U << USB_MTX0BYTE_INT_LEN) - 1) << USB_MTX0BYTE_INT_POS))
#define USB_MRX0BYTE_INT            USB_MRX0BYTE_INT
#define USB_MRX0BYTE_INT_POS        (6U)
#define USB_MRX0BYTE_INT_LEN        (1U)
#define USB_MRX0BYTE_INT_MSK        (((1U << USB_MRX0BYTE_INT_LEN) - 1) << USB_MRX0BYTE_INT_POS)
#define USB_MRX0BYTE_INT_UMSK       (~(((1U << USB_MRX0BYTE_INT_LEN) - 1) << USB_MRX0BYTE_INT_POS))
#define USB_MDMA_CMPLT_HOV          USB_MDMA_CMPLT_HOV
#define USB_MDMA_CMPLT_HOV_POS      (7U)
#define USB_MDMA_CMPLT_HOV_LEN      (1U)
#define USB_MDMA_CMPLT_HOV_MSK      (((1U << USB_MDMA_CMPLT_HOV_LEN) - 1) << USB_MDMA_CMPLT_HOV_POS)
#define USB_MDMA_CMPLT_HOV_UMSK     (~(((1U << USB_MDMA_CMPLT_HOV_LEN) - 1) << USB_MDMA_CMPLT_HOV_POS))
#define USB_MDMA_ERROR_HOV          USB_MDMA_ERROR_HOV
#define USB_MDMA_ERROR_HOV_POS      (8U)
#define USB_MDMA_ERROR_HOV_LEN      (1U)
#define USB_MDMA_ERROR_HOV_MSK      (((1U << USB_MDMA_ERROR_HOV_LEN) - 1) << USB_MDMA_ERROR_HOV_POS)
#define USB_MDMA_ERROR_HOV_UMSK     (~(((1U << USB_MDMA_ERROR_HOV_LEN) - 1) << USB_MDMA_ERROR_HOV_POS))
#define USB_MDEV_IDLE_HOV           USB_MDEV_IDLE_HOV
#define USB_MDEV_IDLE_HOV_POS       (9U)
#define USB_MDEV_IDLE_HOV_LEN       (1U)
#define USB_MDEV_IDLE_HOV_MSK       (((1U << USB_MDEV_IDLE_HOV_LEN) - 1) << USB_MDEV_IDLE_HOV_POS)
#define USB_MDEV_IDLE_HOV_UMSK      (~(((1U << USB_MDEV_IDLE_HOV_LEN) - 1) << USB_MDEV_IDLE_HOV_POS))
#define USB_MDEV_WAKEUP_BYVBUS      USB_MDEV_WAKEUP_BYVBUS
#define USB_MDEV_WAKEUP_BYVBUS_POS  (10U)
#define USB_MDEV_WAKEUP_BYVBUS_LEN  (1U)
#define USB_MDEV_WAKEUP_BYVBUS_MSK  (((1U << USB_MDEV_WAKEUP_BYVBUS_LEN) - 1) << USB_MDEV_WAKEUP_BYVBUS_POS)
#define USB_MDEV_WAKEUP_BYVBUS_UMSK (~(((1U << USB_MDEV_WAKEUP_BYVBUS_LEN) - 1) << USB_MDEV_WAKEUP_BYVBUS_POS))
#define USB_MF8_OUT_INT             USB_MF8_OUT_INT
#define USB_MF8_OUT_INT_POS         (16U)
#define USB_MF8_OUT_INT_LEN         (1U)
#define USB_MF8_OUT_INT_MSK         (((1U << USB_MF8_OUT_INT_LEN) - 1) << USB_MF8_OUT_INT_POS)
#define USB_MF8_OUT_INT_UMSK        (~(((1U << USB_MF8_OUT_INT_LEN) - 1) << USB_MF8_OUT_INT_POS))
#define USB_MF8_SPK_INT             USB_MF8_SPK_INT
#define USB_MF8_SPK_INT_POS         (17U)
#define USB_MF8_SPK_INT_LEN         (1U)
#define USB_MF8_SPK_INT_MSK         (((1U << USB_MF8_SPK_INT_LEN) - 1) << USB_MF8_SPK_INT_POS)
#define USB_MF8_SPK_INT_UMSK        (~(((1U << USB_MF8_SPK_INT_LEN) - 1) << USB_MF8_SPK_INT_POS))
#define USB_MF9_OUT_INT             USB_MF9_OUT_INT
#define USB_MF9_OUT_INT_POS         (18U)
#define USB_MF9_OUT_INT_LEN         (1U)
#define USB_MF9_OUT_INT_MSK         (((1U << USB_MF9_OUT_INT_LEN) - 1) << USB_MF9_OUT_INT_POS)
#define USB_MF9_OUT_INT_UMSK        (~(((1U << USB_MF9_OUT_INT_LEN) - 1) << USB_MF9_OUT_INT_POS))
#define USB_MF9_SPK_INT             USB_MF9_SPK_INT
#define USB_MF9_SPK_INT_POS         (19U)
#define USB_MF9_SPK_INT_LEN         (1U)
#define USB_MF9_SPK_INT_MSK         (((1U << USB_MF9_SPK_INT_LEN) - 1) << USB_MF9_SPK_INT_POS)
#define USB_MF9_SPK_INT_UMSK        (~(((1U << USB_MF9_SPK_INT_LEN) - 1) << USB_MF9_SPK_INT_POS))
#define USB_MF10_OUT_INT            USB_MF10_OUT_INT
#define USB_MF10_OUT_INT_POS        (20U)
#define USB_MF10_OUT_INT_LEN        (1U)
#define USB_MF10_OUT_INT_MSK        (((1U << USB_MF10_OUT_INT_LEN) - 1) << USB_MF10_OUT_INT_POS)
#define USB_MF10_OUT_INT_UMSK       (~(((1U << USB_MF10_OUT_INT_LEN) - 1) << USB_MF10_OUT_INT_POS))
#define USB_MF10_SPK_INT            USB_MF10_SPK_INT
#define USB_MF10_SPK_INT_POS        (21U)
#define USB_MF10_SPK_INT_LEN        (1U)
#define USB_MF10_SPK_INT_MSK        (((1U << USB_MF10_SPK_INT_LEN) - 1) << USB_MF10_SPK_INT_POS)
#define USB_MF10_SPK_INT_UMSK       (~(((1U << USB_MF10_SPK_INT_LEN) - 1) << USB_MF10_SPK_INT_POS))
#define USB_MF11_OUT_INT            USB_MF11_OUT_INT
#define USB_MF11_OUT_INT_POS        (22U)
#define USB_MF11_OUT_INT_LEN        (1U)
#define USB_MF11_OUT_INT_MSK        (((1U << USB_MF11_OUT_INT_LEN) - 1) << USB_MF11_OUT_INT_POS)
#define USB_MF11_OUT_INT_UMSK       (~(((1U << USB_MF11_OUT_INT_LEN) - 1) << USB_MF11_OUT_INT_POS))
#define USB_MF11_SPK_INT            USB_MF11_SPK_INT
#define USB_MF11_SPK_INT_POS        (23U)
#define USB_MF11_SPK_INT_LEN        (1U)
#define USB_MF11_SPK_INT_MSK        (((1U << USB_MF11_SPK_INT_LEN) - 1) << USB_MF11_SPK_INT_POS)
#define USB_MF11_SPK_INT_UMSK       (~(((1U << USB_MF11_SPK_INT_LEN) - 1) << USB_MF11_SPK_INT_POS))
#define USB_MF12_OUT_INT            USB_MF12_OUT_INT
#define USB_MF12_OUT_INT_POS        (24U)
#define USB_MF12_OUT_INT_LEN        (1U)
#define USB_MF12_OUT_INT_MSK        (((1U << USB_MF12_OUT_INT_LEN) - 1) << USB_MF12_OUT_INT_POS)
#define USB_MF12_OUT_INT_UMSK       (~(((1U << USB_MF12_OUT_INT_LEN) - 1) << USB_MF12_OUT_INT_POS))
#define USB_MF12_SPK_INT            USB_MF12_SPK_INT
#define USB_MF12_SPK_INT_POS        (25U)
#define USB_MF12_SPK_INT_LEN        (1U)
#define USB_MF12_SPK_INT_MSK        (((1U << USB_MF12_SPK_INT_LEN) - 1) << USB_MF12_SPK_INT_POS)
#define USB_MF12_SPK_INT_UMSK       (~(((1U << USB_MF12_SPK_INT_LEN) - 1) << USB_MF12_SPK_INT_POS))
#define USB_MF13_OUT_INT            USB_MF13_OUT_INT
#define USB_MF13_OUT_INT_POS        (26U)
#define USB_MF13_OUT_INT_LEN        (1U)
#define USB_MF13_OUT_INT_MSK        (((1U << USB_MF13_OUT_INT_LEN) - 1) << USB_MF13_OUT_INT_POS)
#define USB_MF13_OUT_INT_UMSK       (~(((1U << USB_MF13_OUT_INT_LEN) - 1) << USB_MF13_OUT_INT_POS))
#define USB_MF13_SPK_INT            USB_MF13_SPK_INT
#define USB_MF13_SPK_INT_POS        (27U)
#define USB_MF13_SPK_INT_LEN        (1U)
#define USB_MF13_SPK_INT_MSK        (((1U << USB_MF13_SPK_INT_LEN) - 1) << USB_MF13_SPK_INT_POS)
#define USB_MF13_SPK_INT_UMSK       (~(((1U << USB_MF13_SPK_INT_LEN) - 1) << USB_MF13_SPK_INT_POS))
#define USB_MF14_OUT_INT            USB_MF14_OUT_INT
#define USB_MF14_OUT_INT_POS        (28U)
#define USB_MF14_OUT_INT_LEN        (1U)
#define USB_MF14_OUT_INT_MSK        (((1U << USB_MF14_OUT_INT_LEN) - 1) << USB_MF14_OUT_INT_POS)
#define USB_MF14_OUT_INT_UMSK       (~(((1U << USB_MF14_OUT_INT_LEN) - 1) << USB_MF14_OUT_INT_POS))
#define USB_MF14_SPK_INT            USB_MF14_SPK_INT
#define USB_MF14_SPK_INT_POS        (29U)
#define USB_MF14_SPK_INT_LEN        (1U)
#define USB_MF14_SPK_INT_MSK        (((1U << USB_MF14_SPK_INT_LEN) - 1) << USB_MF14_SPK_INT_POS)
#define USB_MF14_SPK_INT_UMSK       (~(((1U << USB_MF14_SPK_INT_LEN) - 1) << USB_MF14_SPK_INT_POS))
#define USB_MF15_OUT_INT            USB_MF15_OUT_INT
#define USB_MF15_OUT_INT_POS        (30U)
#define USB_MF15_OUT_INT_LEN        (1U)
#define USB_MF15_OUT_INT_MSK        (((1U << USB_MF15_OUT_INT_LEN) - 1) << USB_MF15_OUT_INT_POS)
#define USB_MF15_OUT_INT_UMSK       (~(((1U << USB_MF15_OUT_INT_LEN) - 1) << USB_MF15_OUT_INT_POS))
#define USB_MF15_SPK_INT            USB_MF15_SPK_INT
#define USB_MF15_SPK_INT_POS        (31U)
#define USB_MF15_SPK_INT_LEN        (1U)
#define USB_MF15_SPK_INT_MSK        (((1U << USB_MF15_SPK_INT_LEN) - 1) << USB_MF15_SPK_INT_POS)
#define USB_MF15_SPK_INT_UMSK       (~(((1U << USB_MF15_SPK_INT_LEN) - 1) << USB_MF15_SPK_INT_POS))

/* 0x140 : DEV_IGR */
#define USB_DEV_IGR_OFFSET  (0x140)
#define USB_INT_G0          USB_INT_G0
#define USB_INT_G0_POS      (0U)
#define USB_INT_G0_LEN      (1U)
#define USB_INT_G0_MSK      (((1U << USB_INT_G0_LEN) - 1) << USB_INT_G0_POS)
#define USB_INT_G0_UMSK     (~(((1U << USB_INT_G0_LEN) - 1) << USB_INT_G0_POS))
#define USB_INT_G1          USB_INT_G1
#define USB_INT_G1_POS      (1U)
#define USB_INT_G1_LEN      (1U)
#define USB_INT_G1_MSK      (((1U << USB_INT_G1_LEN) - 1) << USB_INT_G1_POS)
#define USB_INT_G1_UMSK     (~(((1U << USB_INT_G1_LEN) - 1) << USB_INT_G1_POS))
#define USB_INT_G2_HOV      USB_INT_G2_HOV
#define USB_INT_G2_HOV_POS  (2U)
#define USB_INT_G2_HOV_LEN  (1U)
#define USB_INT_G2_HOV_MSK  (((1U << USB_INT_G2_HOV_LEN) - 1) << USB_INT_G2_HOV_POS)
#define USB_INT_G2_HOV_UMSK (~(((1U << USB_INT_G2_HOV_LEN) - 1) << USB_INT_G2_HOV_POS))
#define USB_INT_G3          USB_INT_G3
#define USB_INT_G3_POS      (3U)
#define USB_INT_G3_LEN      (1U)
#define USB_INT_G3_MSK      (((1U << USB_INT_G3_LEN) - 1) << USB_INT_G3_POS)
#define USB_INT_G3_UMSK     (~(((1U << USB_INT_G3_LEN) - 1) << USB_INT_G3_POS))
#define USB_INT_G4          USB_INT_G4
#define USB_INT_G4_POS      (4U)
#define USB_INT_G4_LEN      (1U)
#define USB_INT_G4_MSK      (((1U << USB_INT_G4_LEN) - 1) << USB_INT_G4_POS)
#define USB_INT_G4_UMSK     (~(((1U << USB_INT_G4_LEN) - 1) << USB_INT_G4_POS))

/* 0x144 : DEV_ISG0 */
#define USB_DEV_ISG0_OFFSET     (0x144)
#define USB_CX_SETUP_INT        USB_CX_SETUP_INT
#define USB_CX_SETUP_INT_POS    (0U)
#define USB_CX_SETUP_INT_LEN    (1U)
#define USB_CX_SETUP_INT_MSK    (((1U << USB_CX_SETUP_INT_LEN) - 1) << USB_CX_SETUP_INT_POS)
#define USB_CX_SETUP_INT_UMSK   (~(((1U << USB_CX_SETUP_INT_LEN) - 1) << USB_CX_SETUP_INT_POS))
#define USB_CX_IN_INT           USB_CX_IN_INT
#define USB_CX_IN_INT_POS       (1U)
#define USB_CX_IN_INT_LEN       (1U)
#define USB_CX_IN_INT_MSK       (((1U << USB_CX_IN_INT_LEN) - 1) << USB_CX_IN_INT_POS)
#define USB_CX_IN_INT_UMSK      (~(((1U << USB_CX_IN_INT_LEN) - 1) << USB_CX_IN_INT_POS))
#define USB_CX_OUT_INT          USB_CX_OUT_INT
#define USB_CX_OUT_INT_POS      (2U)
#define USB_CX_OUT_INT_LEN      (1U)
#define USB_CX_OUT_INT_MSK      (((1U << USB_CX_OUT_INT_LEN) - 1) << USB_CX_OUT_INT_POS)
#define USB_CX_OUT_INT_UMSK     (~(((1U << USB_CX_OUT_INT_LEN) - 1) << USB_CX_OUT_INT_POS))
#define USB_CX_COMFAIL_INT      USB_CX_COMFAIL_INT
#define USB_CX_COMFAIL_INT_POS  (4U)
#define USB_CX_COMFAIL_INT_LEN  (1U)
#define USB_CX_COMFAIL_INT_MSK  (((1U << USB_CX_COMFAIL_INT_LEN) - 1) << USB_CX_COMFAIL_INT_POS)
#define USB_CX_COMFAIL_INT_UMSK (~(((1U << USB_CX_COMFAIL_INT_LEN) - 1) << USB_CX_COMFAIL_INT_POS))
#define USB_CX_COMABT_INT       USB_CX_COMABT_INT
#define USB_CX_COMABT_INT_POS   (5U)
#define USB_CX_COMABT_INT_LEN   (1U)
#define USB_CX_COMABT_INT_MSK   (((1U << USB_CX_COMABT_INT_LEN) - 1) << USB_CX_COMABT_INT_POS)
#define USB_CX_COMABT_INT_UMSK  (~(((1U << USB_CX_COMABT_INT_LEN) - 1) << USB_CX_COMABT_INT_POS))

/* 0x148 : DEV_ISG1 */
#define USB_DEV_ISG1_OFFSET (0x148)
#define USB_F0_OUT_INT      USB_F0_OUT_INT
#define USB_F0_OUT_INT_POS  (0U)
#define USB_F0_OUT_INT_LEN  (1U)
#define USB_F0_OUT_INT_MSK  (((1U << USB_F0_OUT_INT_LEN) - 1) << USB_F0_OUT_INT_POS)
#define USB_F0_OUT_INT_UMSK (~(((1U << USB_F0_OUT_INT_LEN) - 1) << USB_F0_OUT_INT_POS))
#define USB_F0_SPK_INT      USB_F0_SPK_INT
#define USB_F0_SPK_INT_POS  (1U)
#define USB_F0_SPK_INT_LEN  (1U)
#define USB_F0_SPK_INT_MSK  (((1U << USB_F0_SPK_INT_LEN) - 1) << USB_F0_SPK_INT_POS)
#define USB_F0_SPK_INT_UMSK (~(((1U << USB_F0_SPK_INT_LEN) - 1) << USB_F0_SPK_INT_POS))
#define USB_F1_OUT_INT      USB_F1_OUT_INT
#define USB_F1_OUT_INT_POS  (2U)
#define USB_F1_OUT_INT_LEN  (1U)
#define USB_F1_OUT_INT_MSK  (((1U << USB_F1_OUT_INT_LEN) - 1) << USB_F1_OUT_INT_POS)
#define USB_F1_OUT_INT_UMSK (~(((1U << USB_F1_OUT_INT_LEN) - 1) << USB_F1_OUT_INT_POS))
#define USB_F1_SPK_INT      USB_F1_SPK_INT
#define USB_F1_SPK_INT_POS  (3U)
#define USB_F1_SPK_INT_LEN  (1U)
#define USB_F1_SPK_INT_MSK  (((1U << USB_F1_SPK_INT_LEN) - 1) << USB_F1_SPK_INT_POS)
#define USB_F1_SPK_INT_UMSK (~(((1U << USB_F1_SPK_INT_LEN) - 1) << USB_F1_SPK_INT_POS))
#define USB_F2_OUT_INT      USB_F2_OUT_INT
#define USB_F2_OUT_INT_POS  (4U)
#define USB_F2_OUT_INT_LEN  (1U)
#define USB_F2_OUT_INT_MSK  (((1U << USB_F2_OUT_INT_LEN) - 1) << USB_F2_OUT_INT_POS)
#define USB_F2_OUT_INT_UMSK (~(((1U << USB_F2_OUT_INT_LEN) - 1) << USB_F2_OUT_INT_POS))
#define USB_F2_SPK_INT      USB_F2_SPK_INT
#define USB_F2_SPK_INT_POS  (5U)
#define USB_F2_SPK_INT_LEN  (1U)
#define USB_F2_SPK_INT_MSK  (((1U << USB_F2_SPK_INT_LEN) - 1) << USB_F2_SPK_INT_POS)
#define USB_F2_SPK_INT_UMSK (~(((1U << USB_F2_SPK_INT_LEN) - 1) << USB_F2_SPK_INT_POS))
#define USB_F3_OUT_INT      USB_F3_OUT_INT
#define USB_F3_OUT_INT_POS  (6U)
#define USB_F3_OUT_INT_LEN  (1U)
#define USB_F3_OUT_INT_MSK  (((1U << USB_F3_OUT_INT_LEN) - 1) << USB_F3_OUT_INT_POS)
#define USB_F3_OUT_INT_UMSK (~(((1U << USB_F3_OUT_INT_LEN) - 1) << USB_F3_OUT_INT_POS))
#define USB_F3_SPK_INT      USB_F3_SPK_INT
#define USB_F3_SPK_INT_POS  (7U)
#define USB_F3_SPK_INT_LEN  (1U)
#define USB_F3_SPK_INT_MSK  (((1U << USB_F3_SPK_INT_LEN) - 1) << USB_F3_SPK_INT_POS)
#define USB_F3_SPK_INT_UMSK (~(((1U << USB_F3_SPK_INT_LEN) - 1) << USB_F3_SPK_INT_POS))
#define USB_F4_OUT_INT      USB_F4_OUT_INT
#define USB_F4_OUT_INT_POS  (8U)
#define USB_F4_OUT_INT_LEN  (1U)
#define USB_F4_OUT_INT_MSK  (((1U << USB_F4_OUT_INT_LEN) - 1) << USB_F4_OUT_INT_POS)
#define USB_F4_OUT_INT_UMSK (~(((1U << USB_F4_OUT_INT_LEN) - 1) << USB_F4_OUT_INT_POS))
#define USB_F4_SPK_INT      USB_F4_SPK_INT
#define USB_F4_SPK_INT_POS  (9U)
#define USB_F4_SPK_INT_LEN  (1U)
#define USB_F4_SPK_INT_MSK  (((1U << USB_F4_SPK_INT_LEN) - 1) << USB_F4_SPK_INT_POS)
#define USB_F4_SPK_INT_UMSK (~(((1U << USB_F4_SPK_INT_LEN) - 1) << USB_F4_SPK_INT_POS))
#define USB_F5_OUT_INT      USB_F5_OUT_INT
#define USB_F5_OUT_INT_POS  (10U)
#define USB_F5_OUT_INT_LEN  (1U)
#define USB_F5_OUT_INT_MSK  (((1U << USB_F5_OUT_INT_LEN) - 1) << USB_F5_OUT_INT_POS)
#define USB_F5_OUT_INT_UMSK (~(((1U << USB_F5_OUT_INT_LEN) - 1) << USB_F5_OUT_INT_POS))
#define USB_F5_SPK_INT      USB_F5_SPK_INT
#define USB_F5_SPK_INT_POS  (11U)
#define USB_F5_SPK_INT_LEN  (1U)
#define USB_F5_SPK_INT_MSK  (((1U << USB_F5_SPK_INT_LEN) - 1) << USB_F5_SPK_INT_POS)
#define USB_F5_SPK_INT_UMSK (~(((1U << USB_F5_SPK_INT_LEN) - 1) << USB_F5_SPK_INT_POS))
#define USB_F6_OUT_INT      USB_F6_OUT_INT
#define USB_F6_OUT_INT_POS  (12U)
#define USB_F6_OUT_INT_LEN  (1U)
#define USB_F6_OUT_INT_MSK  (((1U << USB_F6_OUT_INT_LEN) - 1) << USB_F6_OUT_INT_POS)
#define USB_F6_OUT_INT_UMSK (~(((1U << USB_F6_OUT_INT_LEN) - 1) << USB_F6_OUT_INT_POS))
#define USB_F6_SPK_INT      USB_F6_SPK_INT
#define USB_F6_SPK_INT_POS  (13U)
#define USB_F6_SPK_INT_LEN  (1U)
#define USB_F6_SPK_INT_MSK  (((1U << USB_F6_SPK_INT_LEN) - 1) << USB_F6_SPK_INT_POS)
#define USB_F6_SPK_INT_UMSK (~(((1U << USB_F6_SPK_INT_LEN) - 1) << USB_F6_SPK_INT_POS))
#define USB_F7_OUT_INT      USB_F7_OUT_INT
#define USB_F7_OUT_INT_POS  (14U)
#define USB_F7_OUT_INT_LEN  (1U)
#define USB_F7_OUT_INT_MSK  (((1U << USB_F7_OUT_INT_LEN) - 1) << USB_F7_OUT_INT_POS)
#define USB_F7_OUT_INT_UMSK (~(((1U << USB_F7_OUT_INT_LEN) - 1) << USB_F7_OUT_INT_POS))
#define USB_F7_SPK_INT      USB_F7_SPK_INT
#define USB_F7_SPK_INT_POS  (15U)
#define USB_F7_SPK_INT_LEN  (1U)
#define USB_F7_SPK_INT_MSK  (((1U << USB_F7_SPK_INT_LEN) - 1) << USB_F7_SPK_INT_POS)
#define USB_F7_SPK_INT_UMSK (~(((1U << USB_F7_SPK_INT_LEN) - 1) << USB_F7_SPK_INT_POS))
#define USB_F0_IN_INT       USB_F0_IN_INT
#define USB_F0_IN_INT_POS   (16U)
#define USB_F0_IN_INT_LEN   (1U)
#define USB_F0_IN_INT_MSK   (((1U << USB_F0_IN_INT_LEN) - 1) << USB_F0_IN_INT_POS)
#define USB_F0_IN_INT_UMSK  (~(((1U << USB_F0_IN_INT_LEN) - 1) << USB_F0_IN_INT_POS))
#define USB_F1_IN_INT       USB_F1_IN_INT
#define USB_F1_IN_INT_POS   (17U)
#define USB_F1_IN_INT_LEN   (1U)
#define USB_F1_IN_INT_MSK   (((1U << USB_F1_IN_INT_LEN) - 1) << USB_F1_IN_INT_POS)
#define USB_F1_IN_INT_UMSK  (~(((1U << USB_F1_IN_INT_LEN) - 1) << USB_F1_IN_INT_POS))
#define USB_F2_IN_INT       USB_F2_IN_INT
#define USB_F2_IN_INT_POS   (18U)
#define USB_F2_IN_INT_LEN   (1U)
#define USB_F2_IN_INT_MSK   (((1U << USB_F2_IN_INT_LEN) - 1) << USB_F2_IN_INT_POS)
#define USB_F2_IN_INT_UMSK  (~(((1U << USB_F2_IN_INT_LEN) - 1) << USB_F2_IN_INT_POS))
#define USB_F3_IN_INT       USB_F3_IN_INT
#define USB_F3_IN_INT_POS   (19U)
#define USB_F3_IN_INT_LEN   (1U)
#define USB_F3_IN_INT_MSK   (((1U << USB_F3_IN_INT_LEN) - 1) << USB_F3_IN_INT_POS)
#define USB_F3_IN_INT_UMSK  (~(((1U << USB_F3_IN_INT_LEN) - 1) << USB_F3_IN_INT_POS))
#define USB_F4_IN_INT       USB_F4_IN_INT
#define USB_F4_IN_INT_POS   (20U)
#define USB_F4_IN_INT_LEN   (1U)
#define USB_F4_IN_INT_MSK   (((1U << USB_F4_IN_INT_LEN) - 1) << USB_F4_IN_INT_POS)
#define USB_F4_IN_INT_UMSK  (~(((1U << USB_F4_IN_INT_LEN) - 1) << USB_F4_IN_INT_POS))
#define USB_F5_IN_INT       USB_F5_IN_INT
#define USB_F5_IN_INT_POS   (21U)
#define USB_F5_IN_INT_LEN   (1U)
#define USB_F5_IN_INT_MSK   (((1U << USB_F5_IN_INT_LEN) - 1) << USB_F5_IN_INT_POS)
#define USB_F5_IN_INT_UMSK  (~(((1U << USB_F5_IN_INT_LEN) - 1) << USB_F5_IN_INT_POS))
#define USB_F6_IN_INT       USB_F6_IN_INT
#define USB_F6_IN_INT_POS   (22U)
#define USB_F6_IN_INT_LEN   (1U)
#define USB_F6_IN_INT_MSK   (((1U << USB_F6_IN_INT_LEN) - 1) << USB_F6_IN_INT_POS)
#define USB_F6_IN_INT_UMSK  (~(((1U << USB_F6_IN_INT_LEN) - 1) << USB_F6_IN_INT_POS))
#define USB_F7_IN_INT       USB_F7_IN_INT
#define USB_F7_IN_INT_POS   (23U)
#define USB_F7_IN_INT_LEN   (1U)
#define USB_F7_IN_INT_MSK   (((1U << USB_F7_IN_INT_LEN) - 1) << USB_F7_IN_INT_POS)
#define USB_F7_IN_INT_UMSK  (~(((1U << USB_F7_IN_INT_LEN) - 1) << USB_F7_IN_INT_POS))
#define USB_F8_IN_INT       USB_F8_IN_INT
#define USB_F8_IN_INT_POS   (24U)
#define USB_F8_IN_INT_LEN   (1U)
#define USB_F8_IN_INT_MSK   (((1U << USB_F8_IN_INT_LEN) - 1) << USB_F8_IN_INT_POS)
#define USB_F8_IN_INT_UMSK  (~(((1U << USB_F8_IN_INT_LEN) - 1) << USB_F8_IN_INT_POS))
#define USB_F9_IN_INT       USB_F9_IN_INT
#define USB_F9_IN_INT_POS   (25U)
#define USB_F9_IN_INT_LEN   (1U)
#define USB_F9_IN_INT_MSK   (((1U << USB_F9_IN_INT_LEN) - 1) << USB_F9_IN_INT_POS)
#define USB_F9_IN_INT_UMSK  (~(((1U << USB_F9_IN_INT_LEN) - 1) << USB_F9_IN_INT_POS))
#define USB_F10_IN_INT      USB_F10_IN_INT
#define USB_F10_IN_INT_POS  (26U)
#define USB_F10_IN_INT_LEN  (1U)
#define USB_F10_IN_INT_MSK  (((1U << USB_F10_IN_INT_LEN) - 1) << USB_F10_IN_INT_POS)
#define USB_F10_IN_INT_UMSK (~(((1U << USB_F10_IN_INT_LEN) - 1) << USB_F10_IN_INT_POS))
#define USB_F11_IN_INT      USB_F11_IN_INT
#define USB_F11_IN_INT_POS  (27U)
#define USB_F11_IN_INT_LEN  (1U)
#define USB_F11_IN_INT_MSK  (((1U << USB_F11_IN_INT_LEN) - 1) << USB_F11_IN_INT_POS)
#define USB_F11_IN_INT_UMSK (~(((1U << USB_F11_IN_INT_LEN) - 1) << USB_F11_IN_INT_POS))
#define USB_F12_IN_INT      USB_F12_IN_INT
#define USB_F12_IN_INT_POS  (28U)
#define USB_F12_IN_INT_LEN  (1U)
#define USB_F12_IN_INT_MSK  (((1U << USB_F12_IN_INT_LEN) - 1) << USB_F12_IN_INT_POS)
#define USB_F12_IN_INT_UMSK (~(((1U << USB_F12_IN_INT_LEN) - 1) << USB_F12_IN_INT_POS))
#define USB_F13_IN_INT      USB_F13_IN_INT
#define USB_F13_IN_INT_POS  (29U)
#define USB_F13_IN_INT_LEN  (1U)
#define USB_F13_IN_INT_MSK  (((1U << USB_F13_IN_INT_LEN) - 1) << USB_F13_IN_INT_POS)
#define USB_F13_IN_INT_UMSK (~(((1U << USB_F13_IN_INT_LEN) - 1) << USB_F13_IN_INT_POS))
#define USB_F14_IN_INT      USB_F14_IN_INT
#define USB_F14_IN_INT_POS  (30U)
#define USB_F14_IN_INT_LEN  (1U)
#define USB_F14_IN_INT_MSK  (((1U << USB_F14_IN_INT_LEN) - 1) << USB_F14_IN_INT_POS)
#define USB_F14_IN_INT_UMSK (~(((1U << USB_F14_IN_INT_LEN) - 1) << USB_F14_IN_INT_POS))
#define USB_F15_IN_INT      USB_F15_IN_INT
#define USB_F15_IN_INT_POS  (31U)
#define USB_F15_IN_INT_LEN  (1U)
#define USB_F15_IN_INT_MSK  (((1U << USB_F15_IN_INT_LEN) - 1) << USB_F15_IN_INT_POS)
#define USB_F15_IN_INT_UMSK (~(((1U << USB_F15_IN_INT_LEN) - 1) << USB_F15_IN_INT_POS))

/* 0x14C : DEV_ISG2 */
#define USB_DEV_ISG2_OFFSET        (0x14C)
#define USBRST_INT                 USBRST_INT
#define USBRST_INT_POS             (0U)
#define USBRST_INT_LEN             (1U)
#define USBRST_INT_MSK             (((1U << USBRST_INT_LEN) - 1) << USBRST_INT_POS)
#define USBRST_INT_UMSK            (~(((1U << USBRST_INT_LEN) - 1) << USBRST_INT_POS))
#define USB_SUSP_INT               USB_SUSP_INT
#define USB_SUSP_INT_POS           (1U)
#define USB_SUSP_INT_LEN           (1U)
#define USB_SUSP_INT_MSK           (((1U << USB_SUSP_INT_LEN) - 1) << USB_SUSP_INT_POS)
#define USB_SUSP_INT_UMSK          (~(((1U << USB_SUSP_INT_LEN) - 1) << USB_SUSP_INT_POS))
#define USB_RESM_INT               USB_RESM_INT
#define USB_RESM_INT_POS           (2U)
#define USB_RESM_INT_LEN           (1U)
#define USB_RESM_INT_MSK           (((1U << USB_RESM_INT_LEN) - 1) << USB_RESM_INT_POS)
#define USB_RESM_INT_UMSK          (~(((1U << USB_RESM_INT_LEN) - 1) << USB_RESM_INT_POS))
#define USB_ISO_SEQ_ERR_INT        USB_ISO_SEQ_ERR_INT
#define USB_ISO_SEQ_ERR_INT_POS    (3U)
#define USB_ISO_SEQ_ERR_INT_LEN    (1U)
#define USB_ISO_SEQ_ERR_INT_MSK    (((1U << USB_ISO_SEQ_ERR_INT_LEN) - 1) << USB_ISO_SEQ_ERR_INT_POS)
#define USB_ISO_SEQ_ERR_INT_UMSK   (~(((1U << USB_ISO_SEQ_ERR_INT_LEN) - 1) << USB_ISO_SEQ_ERR_INT_POS))
#define USB_ISO_SEQ_ABORT_INT      USB_ISO_SEQ_ABORT_INT
#define USB_ISO_SEQ_ABORT_INT_POS  (4U)
#define USB_ISO_SEQ_ABORT_INT_LEN  (1U)
#define USB_ISO_SEQ_ABORT_INT_MSK  (((1U << USB_ISO_SEQ_ABORT_INT_LEN) - 1) << USB_ISO_SEQ_ABORT_INT_POS)
#define USB_ISO_SEQ_ABORT_INT_UMSK (~(((1U << USB_ISO_SEQ_ABORT_INT_LEN) - 1) << USB_ISO_SEQ_ABORT_INT_POS))
#define USB_TX0BYTE_INT            USB_TX0BYTE_INT
#define USB_TX0BYTE_INT_POS        (5U)
#define USB_TX0BYTE_INT_LEN        (1U)
#define USB_TX0BYTE_INT_MSK        (((1U << USB_TX0BYTE_INT_LEN) - 1) << USB_TX0BYTE_INT_POS)
#define USB_TX0BYTE_INT_UMSK       (~(((1U << USB_TX0BYTE_INT_LEN) - 1) << USB_TX0BYTE_INT_POS))
#define USB_RX0BYTE_INT            USB_RX0BYTE_INT
#define USB_RX0BYTE_INT_POS        (6U)
#define USB_RX0BYTE_INT_LEN        (1U)
#define USB_RX0BYTE_INT_MSK        (((1U << USB_RX0BYTE_INT_LEN) - 1) << USB_RX0BYTE_INT_POS)
#define USB_RX0BYTE_INT_UMSK       (~(((1U << USB_RX0BYTE_INT_LEN) - 1) << USB_RX0BYTE_INT_POS))
#define USB_DMA_CMPLT_HOV          USB_DMA_CMPLT_HOV
#define USB_DMA_CMPLT_HOV_POS      (7U)
#define USB_DMA_CMPLT_HOV_LEN      (1U)
#define USB_DMA_CMPLT_HOV_MSK      (((1U << USB_DMA_CMPLT_HOV_LEN) - 1) << USB_DMA_CMPLT_HOV_POS)
#define USB_DMA_CMPLT_HOV_UMSK     (~(((1U << USB_DMA_CMPLT_HOV_LEN) - 1) << USB_DMA_CMPLT_HOV_POS))
#define USB_DMA_ERROR_HOV          USB_DMA_ERROR_HOV
#define USB_DMA_ERROR_HOV_POS      (8U)
#define USB_DMA_ERROR_HOV_LEN      (1U)
#define USB_DMA_ERROR_HOV_MSK      (((1U << USB_DMA_ERROR_HOV_LEN) - 1) << USB_DMA_ERROR_HOV_POS)
#define USB_DMA_ERROR_HOV_UMSK     (~(((1U << USB_DMA_ERROR_HOV_LEN) - 1) << USB_DMA_ERROR_HOV_POS))
#define USB_DEV_IDLE_HOV           USB_DEV_IDLE_HOV
#define USB_DEV_IDLE_HOV_POS       (9U)
#define USB_DEV_IDLE_HOV_LEN       (1U)
#define USB_DEV_IDLE_HOV_MSK       (((1U << USB_DEV_IDLE_HOV_LEN) - 1) << USB_DEV_IDLE_HOV_POS)
#define USB_DEV_IDLE_HOV_UMSK      (~(((1U << USB_DEV_IDLE_HOV_LEN) - 1) << USB_DEV_IDLE_HOV_POS))
#define USB_DEV_WAKEUP_BYVBUS      USB_DEV_WAKEUP_BYVBUS
#define USB_DEV_WAKEUP_BYVBUS_POS  (10U)
#define USB_DEV_WAKEUP_BYVBUS_LEN  (1U)
#define USB_DEV_WAKEUP_BYVBUS_MSK  (((1U << USB_DEV_WAKEUP_BYVBUS_LEN) - 1) << USB_DEV_WAKEUP_BYVBUS_POS)
#define USB_DEV_WAKEUP_BYVBUS_UMSK (~(((1U << USB_DEV_WAKEUP_BYVBUS_LEN) - 1) << USB_DEV_WAKEUP_BYVBUS_POS))
#define USB_F8_OUT_INT             USB_F8_OUT_INT
#define USB_F8_OUT_INT_POS         (16U)
#define USB_F8_OUT_INT_LEN         (1U)
#define USB_F8_OUT_INT_MSK         (((1U << USB_F8_OUT_INT_LEN) - 1) << USB_F8_OUT_INT_POS)
#define USB_F8_OUT_INT_UMSK        (~(((1U << USB_F8_OUT_INT_LEN) - 1) << USB_F8_OUT_INT_POS))
#define USB_F8_SPK_INT             USB_F8_SPK_INT
#define USB_F8_SPK_INT_POS         (17U)
#define USB_F8_SPK_INT_LEN         (1U)
#define USB_F8_SPK_INT_MSK         (((1U << USB_F8_SPK_INT_LEN) - 1) << USB_F8_SPK_INT_POS)
#define USB_F8_SPK_INT_UMSK        (~(((1U << USB_F8_SPK_INT_LEN) - 1) << USB_F8_SPK_INT_POS))
#define USB_F9_OUT_INT             USB_F9_OUT_INT
#define USB_F9_OUT_INT_POS         (18U)
#define USB_F9_OUT_INT_LEN         (1U)
#define USB_F9_OUT_INT_MSK         (((1U << USB_F9_OUT_INT_LEN) - 1) << USB_F9_OUT_INT_POS)
#define USB_F9_OUT_INT_UMSK        (~(((1U << USB_F9_OUT_INT_LEN) - 1) << USB_F9_OUT_INT_POS))
#define USB_F9_SPK_INT             USB_F9_SPK_INT
#define USB_F9_SPK_INT_POS         (19U)
#define USB_F9_SPK_INT_LEN         (1U)
#define USB_F9_SPK_INT_MSK         (((1U << USB_F9_SPK_INT_LEN) - 1) << USB_F9_SPK_INT_POS)
#define USB_F9_SPK_INT_UMSK        (~(((1U << USB_F9_SPK_INT_LEN) - 1) << USB_F9_SPK_INT_POS))
#define USB_F10_OUT_INT            USB_F10_OUT_INT
#define USB_F10_OUT_INT_POS        (20U)
#define USB_F10_OUT_INT_LEN        (1U)
#define USB_F10_OUT_INT_MSK        (((1U << USB_F10_OUT_INT_LEN) - 1) << USB_F10_OUT_INT_POS)
#define USB_F10_OUT_INT_UMSK       (~(((1U << USB_F10_OUT_INT_LEN) - 1) << USB_F10_OUT_INT_POS))
#define USB_F10_SPK_INT            USB_F10_SPK_INT
#define USB_F10_SPK_INT_POS        (21U)
#define USB_F10_SPK_INT_LEN        (1U)
#define USB_F10_SPK_INT_MSK        (((1U << USB_F10_SPK_INT_LEN) - 1) << USB_F10_SPK_INT_POS)
#define USB_F10_SPK_INT_UMSK       (~(((1U << USB_F10_SPK_INT_LEN) - 1) << USB_F10_SPK_INT_POS))
#define USB_F11_OUT_INT            USB_F11_OUT_INT
#define USB_F11_OUT_INT_POS        (22U)
#define USB_F11_OUT_INT_LEN        (1U)
#define USB_F11_OUT_INT_MSK        (((1U << USB_F11_OUT_INT_LEN) - 1) << USB_F11_OUT_INT_POS)
#define USB_F11_OUT_INT_UMSK       (~(((1U << USB_F11_OUT_INT_LEN) - 1) << USB_F11_OUT_INT_POS))
#define USB_F11_SPK_INT            USB_F11_SPK_INT
#define USB_F11_SPK_INT_POS        (23U)
#define USB_F11_SPK_INT_LEN        (1U)
#define USB_F11_SPK_INT_MSK        (((1U << USB_F11_SPK_INT_LEN) - 1) << USB_F11_SPK_INT_POS)
#define USB_F11_SPK_INT_UMSK       (~(((1U << USB_F11_SPK_INT_LEN) - 1) << USB_F11_SPK_INT_POS))
#define USB_F12_OUT_INT            USB_F12_OUT_INT
#define USB_F12_OUT_INT_POS        (24U)
#define USB_F12_OUT_INT_LEN        (1U)
#define USB_F12_OUT_INT_MSK        (((1U << USB_F12_OUT_INT_LEN) - 1) << USB_F12_OUT_INT_POS)
#define USB_F12_OUT_INT_UMSK       (~(((1U << USB_F12_OUT_INT_LEN) - 1) << USB_F12_OUT_INT_POS))
#define USB_F12_SPK_INT            USB_F12_SPK_INT
#define USB_F12_SPK_INT_POS        (25U)
#define USB_F12_SPK_INT_LEN        (1U)
#define USB_F12_SPK_INT_MSK        (((1U << USB_F12_SPK_INT_LEN) - 1) << USB_F12_SPK_INT_POS)
#define USB_F12_SPK_INT_UMSK       (~(((1U << USB_F12_SPK_INT_LEN) - 1) << USB_F12_SPK_INT_POS))
#define USB_F13_OUT_INT            USB_F13_OUT_INT
#define USB_F13_OUT_INT_POS        (26U)
#define USB_F13_OUT_INT_LEN        (1U)
#define USB_F13_OUT_INT_MSK        (((1U << USB_F13_OUT_INT_LEN) - 1) << USB_F13_OUT_INT_POS)
#define USB_F13_OUT_INT_UMSK       (~(((1U << USB_F13_OUT_INT_LEN) - 1) << USB_F13_OUT_INT_POS))
#define USB_F13_SPK_INT            USB_F13_SPK_INT
#define USB_F13_SPK_INT_POS        (27U)
#define USB_F13_SPK_INT_LEN        (1U)
#define USB_F13_SPK_INT_MSK        (((1U << USB_F13_SPK_INT_LEN) - 1) << USB_F13_SPK_INT_POS)
#define USB_F13_SPK_INT_UMSK       (~(((1U << USB_F13_SPK_INT_LEN) - 1) << USB_F13_SPK_INT_POS))
#define USB_F14_OUT_INT            USB_F14_OUT_INT
#define USB_F14_OUT_INT_POS        (28U)
#define USB_F14_OUT_INT_LEN        (1U)
#define USB_F14_OUT_INT_MSK        (((1U << USB_F14_OUT_INT_LEN) - 1) << USB_F14_OUT_INT_POS)
#define USB_F14_OUT_INT_UMSK       (~(((1U << USB_F14_OUT_INT_LEN) - 1) << USB_F14_OUT_INT_POS))
#define USB_F14_SPK_INT            USB_F14_SPK_INT
#define USB_F14_SPK_INT_POS        (29U)
#define USB_F14_SPK_INT_LEN        (1U)
#define USB_F14_SPK_INT_MSK        (((1U << USB_F14_SPK_INT_LEN) - 1) << USB_F14_SPK_INT_POS)
#define USB_F14_SPK_INT_UMSK       (~(((1U << USB_F14_SPK_INT_LEN) - 1) << USB_F14_SPK_INT_POS))
#define USB_F15_OUT_INT            USB_F15_OUT_INT
#define USB_F15_OUT_INT_POS        (30U)
#define USB_F15_OUT_INT_LEN        (1U)
#define USB_F15_OUT_INT_MSK        (((1U << USB_F15_OUT_INT_LEN) - 1) << USB_F15_OUT_INT_POS)
#define USB_F15_OUT_INT_UMSK       (~(((1U << USB_F15_OUT_INT_LEN) - 1) << USB_F15_OUT_INT_POS))
#define USB_F15_SPK_INT            USB_F15_SPK_INT
#define USB_F15_SPK_INT_POS        (31U)
#define USB_F15_SPK_INT_LEN        (1U)
#define USB_F15_SPK_INT_MSK        (((1U << USB_F15_SPK_INT_LEN) - 1) << USB_F15_SPK_INT_POS)
#define USB_F15_SPK_INT_UMSK       (~(((1U << USB_F15_SPK_INT_LEN) - 1) << USB_F15_SPK_INT_POS))

/* 0x150 : DEV_RXZ */
#define USB_DEV_RXZ_OFFSET   (0x150)
#define USB_RX0BYTE_EP1      USB_RX0BYTE_EP1
#define USB_RX0BYTE_EP1_POS  (0U)
#define USB_RX0BYTE_EP1_LEN  (1U)
#define USB_RX0BYTE_EP1_MSK  (((1U << USB_RX0BYTE_EP1_LEN) - 1) << USB_RX0BYTE_EP1_POS)
#define USB_RX0BYTE_EP1_UMSK (~(((1U << USB_RX0BYTE_EP1_LEN) - 1) << USB_RX0BYTE_EP1_POS))
#define USB_RX0BYTE_EP2      USB_RX0BYTE_EP2
#define USB_RX0BYTE_EP2_POS  (1U)
#define USB_RX0BYTE_EP2_LEN  (1U)
#define USB_RX0BYTE_EP2_MSK  (((1U << USB_RX0BYTE_EP2_LEN) - 1) << USB_RX0BYTE_EP2_POS)
#define USB_RX0BYTE_EP2_UMSK (~(((1U << USB_RX0BYTE_EP2_LEN) - 1) << USB_RX0BYTE_EP2_POS))
#define USB_RX0BYTE_EP3      USB_RX0BYTE_EP3
#define USB_RX0BYTE_EP3_POS  (2U)
#define USB_RX0BYTE_EP3_LEN  (1U)
#define USB_RX0BYTE_EP3_MSK  (((1U << USB_RX0BYTE_EP3_LEN) - 1) << USB_RX0BYTE_EP3_POS)
#define USB_RX0BYTE_EP3_UMSK (~(((1U << USB_RX0BYTE_EP3_LEN) - 1) << USB_RX0BYTE_EP3_POS))
#define USB_RX0BYTE_EP4      USB_RX0BYTE_EP4
#define USB_RX0BYTE_EP4_POS  (3U)
#define USB_RX0BYTE_EP4_LEN  (1U)
#define USB_RX0BYTE_EP4_MSK  (((1U << USB_RX0BYTE_EP4_LEN) - 1) << USB_RX0BYTE_EP4_POS)
#define USB_RX0BYTE_EP4_UMSK (~(((1U << USB_RX0BYTE_EP4_LEN) - 1) << USB_RX0BYTE_EP4_POS))
#define USB_RX0BYTE_EP5      USB_RX0BYTE_EP5
#define USB_RX0BYTE_EP5_POS  (4U)
#define USB_RX0BYTE_EP5_LEN  (1U)
#define USB_RX0BYTE_EP5_MSK  (((1U << USB_RX0BYTE_EP5_LEN) - 1) << USB_RX0BYTE_EP5_POS)
#define USB_RX0BYTE_EP5_UMSK (~(((1U << USB_RX0BYTE_EP5_LEN) - 1) << USB_RX0BYTE_EP5_POS))
#define USB_RX0BYTE_EP6      USB_RX0BYTE_EP6
#define USB_RX0BYTE_EP6_POS  (5U)
#define USB_RX0BYTE_EP6_LEN  (1U)
#define USB_RX0BYTE_EP6_MSK  (((1U << USB_RX0BYTE_EP6_LEN) - 1) << USB_RX0BYTE_EP6_POS)
#define USB_RX0BYTE_EP6_UMSK (~(((1U << USB_RX0BYTE_EP6_LEN) - 1) << USB_RX0BYTE_EP6_POS))
#define USB_RX0BYTE_EP7      USB_RX0BYTE_EP7
#define USB_RX0BYTE_EP7_POS  (6U)
#define USB_RX0BYTE_EP7_LEN  (1U)
#define USB_RX0BYTE_EP7_MSK  (((1U << USB_RX0BYTE_EP7_LEN) - 1) << USB_RX0BYTE_EP7_POS)
#define USB_RX0BYTE_EP7_UMSK (~(((1U << USB_RX0BYTE_EP7_LEN) - 1) << USB_RX0BYTE_EP7_POS))
#define USB_RX0BYTE_EP8      USB_RX0BYTE_EP8
#define USB_RX0BYTE_EP8_POS  (7U)
#define USB_RX0BYTE_EP8_LEN  (1U)
#define USB_RX0BYTE_EP8_MSK  (((1U << USB_RX0BYTE_EP8_LEN) - 1) << USB_RX0BYTE_EP8_POS)
#define USB_RX0BYTE_EP8_UMSK (~(((1U << USB_RX0BYTE_EP8_LEN) - 1) << USB_RX0BYTE_EP8_POS))

/* 0x154 : DEV_TXZ */
#define USB_DEV_TXZ_OFFSET   (0x154)
#define USB_TX0BYTE_EP1      USB_TX0BYTE_EP1
#define USB_TX0BYTE_EP1_POS  (0U)
#define USB_TX0BYTE_EP1_LEN  (1U)
#define USB_TX0BYTE_EP1_MSK  (((1U << USB_TX0BYTE_EP1_LEN) - 1) << USB_TX0BYTE_EP1_POS)
#define USB_TX0BYTE_EP1_UMSK (~(((1U << USB_TX0BYTE_EP1_LEN) - 1) << USB_TX0BYTE_EP1_POS))
#define USB_TX0BYTE_EP2      USB_TX0BYTE_EP2
#define USB_TX0BYTE_EP2_POS  (1U)
#define USB_TX0BYTE_EP2_LEN  (1U)
#define USB_TX0BYTE_EP2_MSK  (((1U << USB_TX0BYTE_EP2_LEN) - 1) << USB_TX0BYTE_EP2_POS)
#define USB_TX0BYTE_EP2_UMSK (~(((1U << USB_TX0BYTE_EP2_LEN) - 1) << USB_TX0BYTE_EP2_POS))
#define USB_TX0BYTE_EP3      USB_TX0BYTE_EP3
#define USB_TX0BYTE_EP3_POS  (2U)
#define USB_TX0BYTE_EP3_LEN  (1U)
#define USB_TX0BYTE_EP3_MSK  (((1U << USB_TX0BYTE_EP3_LEN) - 1) << USB_TX0BYTE_EP3_POS)
#define USB_TX0BYTE_EP3_UMSK (~(((1U << USB_TX0BYTE_EP3_LEN) - 1) << USB_TX0BYTE_EP3_POS))
#define USB_TX0BYTE_EP4      USB_TX0BYTE_EP4
#define USB_TX0BYTE_EP4_POS  (3U)
#define USB_TX0BYTE_EP4_LEN  (1U)
#define USB_TX0BYTE_EP4_MSK  (((1U << USB_TX0BYTE_EP4_LEN) - 1) << USB_TX0BYTE_EP4_POS)
#define USB_TX0BYTE_EP4_UMSK (~(((1U << USB_TX0BYTE_EP4_LEN) - 1) << USB_TX0BYTE_EP4_POS))
#define USB_TX0BYTE_EP5      USB_TX0BYTE_EP5
#define USB_TX0BYTE_EP5_POS  (4U)
#define USB_TX0BYTE_EP5_LEN  (1U)
#define USB_TX0BYTE_EP5_MSK  (((1U << USB_TX0BYTE_EP5_LEN) - 1) << USB_TX0BYTE_EP5_POS)
#define USB_TX0BYTE_EP5_UMSK (~(((1U << USB_TX0BYTE_EP5_LEN) - 1) << USB_TX0BYTE_EP5_POS))
#define USB_TX0BYTE_EP6      USB_TX0BYTE_EP6
#define USB_TX0BYTE_EP6_POS  (5U)
#define USB_TX0BYTE_EP6_LEN  (1U)
#define USB_TX0BYTE_EP6_MSK  (((1U << USB_TX0BYTE_EP6_LEN) - 1) << USB_TX0BYTE_EP6_POS)
#define USB_TX0BYTE_EP6_UMSK (~(((1U << USB_TX0BYTE_EP6_LEN) - 1) << USB_TX0BYTE_EP6_POS))
#define USB_TX0BYTE_EP7      USB_TX0BYTE_EP7
#define USB_TX0BYTE_EP7_POS  (6U)
#define USB_TX0BYTE_EP7_LEN  (1U)
#define USB_TX0BYTE_EP7_MSK  (((1U << USB_TX0BYTE_EP7_LEN) - 1) << USB_TX0BYTE_EP7_POS)
#define USB_TX0BYTE_EP7_UMSK (~(((1U << USB_TX0BYTE_EP7_LEN) - 1) << USB_TX0BYTE_EP7_POS))
#define USB_TX0BYTE_EP8      USB_TX0BYTE_EP8
#define USB_TX0BYTE_EP8_POS  (7U)
#define USB_TX0BYTE_EP8_LEN  (1U)
#define USB_TX0BYTE_EP8_MSK  (((1U << USB_TX0BYTE_EP8_LEN) - 1) << USB_TX0BYTE_EP8_POS)
#define USB_TX0BYTE_EP8_UMSK (~(((1U << USB_TX0BYTE_EP8_LEN) - 1) << USB_TX0BYTE_EP8_POS))

/* 0x158 : DEV_ISE */
#define USB_DEV_ISE_OFFSET       (0x158)
#define USB_ISO_ABT_ERR_EP1      USB_ISO_ABT_ERR_EP1
#define USB_ISO_ABT_ERR_EP1_POS  (0U)
#define USB_ISO_ABT_ERR_EP1_LEN  (1U)
#define USB_ISO_ABT_ERR_EP1_MSK  (((1U << USB_ISO_ABT_ERR_EP1_LEN) - 1) << USB_ISO_ABT_ERR_EP1_POS)
#define USB_ISO_ABT_ERR_EP1_UMSK (~(((1U << USB_ISO_ABT_ERR_EP1_LEN) - 1) << USB_ISO_ABT_ERR_EP1_POS))
#define USB_ISO_ABT_ERR_EP2      USB_ISO_ABT_ERR_EP2
#define USB_ISO_ABT_ERR_EP2_POS  (1U)
#define USB_ISO_ABT_ERR_EP2_LEN  (1U)
#define USB_ISO_ABT_ERR_EP2_MSK  (((1U << USB_ISO_ABT_ERR_EP2_LEN) - 1) << USB_ISO_ABT_ERR_EP2_POS)
#define USB_ISO_ABT_ERR_EP2_UMSK (~(((1U << USB_ISO_ABT_ERR_EP2_LEN) - 1) << USB_ISO_ABT_ERR_EP2_POS))
#define USB_ISO_ABT_ERR_EP3      USB_ISO_ABT_ERR_EP3
#define USB_ISO_ABT_ERR_EP3_POS  (2U)
#define USB_ISO_ABT_ERR_EP3_LEN  (1U)
#define USB_ISO_ABT_ERR_EP3_MSK  (((1U << USB_ISO_ABT_ERR_EP3_LEN) - 1) << USB_ISO_ABT_ERR_EP3_POS)
#define USB_ISO_ABT_ERR_EP3_UMSK (~(((1U << USB_ISO_ABT_ERR_EP3_LEN) - 1) << USB_ISO_ABT_ERR_EP3_POS))
#define USB_ISO_ABT_ERR_EP4      USB_ISO_ABT_ERR_EP4
#define USB_ISO_ABT_ERR_EP4_POS  (3U)
#define USB_ISO_ABT_ERR_EP4_LEN  (1U)
#define USB_ISO_ABT_ERR_EP4_MSK  (((1U << USB_ISO_ABT_ERR_EP4_LEN) - 1) << USB_ISO_ABT_ERR_EP4_POS)
#define USB_ISO_ABT_ERR_EP4_UMSK (~(((1U << USB_ISO_ABT_ERR_EP4_LEN) - 1) << USB_ISO_ABT_ERR_EP4_POS))
#define USB_ISO_ABT_ERR_EP5      USB_ISO_ABT_ERR_EP5
#define USB_ISO_ABT_ERR_EP5_POS  (4U)
#define USB_ISO_ABT_ERR_EP5_LEN  (1U)
#define USB_ISO_ABT_ERR_EP5_MSK  (((1U << USB_ISO_ABT_ERR_EP5_LEN) - 1) << USB_ISO_ABT_ERR_EP5_POS)
#define USB_ISO_ABT_ERR_EP5_UMSK (~(((1U << USB_ISO_ABT_ERR_EP5_LEN) - 1) << USB_ISO_ABT_ERR_EP5_POS))
#define USB_ISO_ABT_ERR_EP6      USB_ISO_ABT_ERR_EP6
#define USB_ISO_ABT_ERR_EP6_POS  (5U)
#define USB_ISO_ABT_ERR_EP6_LEN  (1U)
#define USB_ISO_ABT_ERR_EP6_MSK  (((1U << USB_ISO_ABT_ERR_EP6_LEN) - 1) << USB_ISO_ABT_ERR_EP6_POS)
#define USB_ISO_ABT_ERR_EP6_UMSK (~(((1U << USB_ISO_ABT_ERR_EP6_LEN) - 1) << USB_ISO_ABT_ERR_EP6_POS))
#define USB_ISO_ABT_ERR_EP7      USB_ISO_ABT_ERR_EP7
#define USB_ISO_ABT_ERR_EP7_POS  (6U)
#define USB_ISO_ABT_ERR_EP7_LEN  (1U)
#define USB_ISO_ABT_ERR_EP7_MSK  (((1U << USB_ISO_ABT_ERR_EP7_LEN) - 1) << USB_ISO_ABT_ERR_EP7_POS)
#define USB_ISO_ABT_ERR_EP7_UMSK (~(((1U << USB_ISO_ABT_ERR_EP7_LEN) - 1) << USB_ISO_ABT_ERR_EP7_POS))
#define USB_ISO_ABT_ERR_EP8      USB_ISO_ABT_ERR_EP8
#define USB_ISO_ABT_ERR_EP8_POS  (7U)
#define USB_ISO_ABT_ERR_EP8_LEN  (1U)
#define USB_ISO_ABT_ERR_EP8_MSK  (((1U << USB_ISO_ABT_ERR_EP8_LEN) - 1) << USB_ISO_ABT_ERR_EP8_POS)
#define USB_ISO_ABT_ERR_EP8_UMSK (~(((1U << USB_ISO_ABT_ERR_EP8_LEN) - 1) << USB_ISO_ABT_ERR_EP8_POS))
#define USB_ISO_SEQ_ERR_EP1      USB_ISO_SEQ_ERR_EP1
#define USB_ISO_SEQ_ERR_EP1_POS  (16U)
#define USB_ISO_SEQ_ERR_EP1_LEN  (1U)
#define USB_ISO_SEQ_ERR_EP1_MSK  (((1U << USB_ISO_SEQ_ERR_EP1_LEN) - 1) << USB_ISO_SEQ_ERR_EP1_POS)
#define USB_ISO_SEQ_ERR_EP1_UMSK (~(((1U << USB_ISO_SEQ_ERR_EP1_LEN) - 1) << USB_ISO_SEQ_ERR_EP1_POS))
#define USB_ISO_SEQ_ERR_EP2      USB_ISO_SEQ_ERR_EP2
#define USB_ISO_SEQ_ERR_EP2_POS  (17U)
#define USB_ISO_SEQ_ERR_EP2_LEN  (1U)
#define USB_ISO_SEQ_ERR_EP2_MSK  (((1U << USB_ISO_SEQ_ERR_EP2_LEN) - 1) << USB_ISO_SEQ_ERR_EP2_POS)
#define USB_ISO_SEQ_ERR_EP2_UMSK (~(((1U << USB_ISO_SEQ_ERR_EP2_LEN) - 1) << USB_ISO_SEQ_ERR_EP2_POS))
#define USB_ISO_SEQ_ERR_EP3      USB_ISO_SEQ_ERR_EP3
#define USB_ISO_SEQ_ERR_EP3_POS  (18U)
#define USB_ISO_SEQ_ERR_EP3_LEN  (1U)
#define USB_ISO_SEQ_ERR_EP3_MSK  (((1U << USB_ISO_SEQ_ERR_EP3_LEN) - 1) << USB_ISO_SEQ_ERR_EP3_POS)
#define USB_ISO_SEQ_ERR_EP3_UMSK (~(((1U << USB_ISO_SEQ_ERR_EP3_LEN) - 1) << USB_ISO_SEQ_ERR_EP3_POS))
#define USB_ISO_SEQ_ERR_EP4      USB_ISO_SEQ_ERR_EP4
#define USB_ISO_SEQ_ERR_EP4_POS  (19U)
#define USB_ISO_SEQ_ERR_EP4_LEN  (1U)
#define USB_ISO_SEQ_ERR_EP4_MSK  (((1U << USB_ISO_SEQ_ERR_EP4_LEN) - 1) << USB_ISO_SEQ_ERR_EP4_POS)
#define USB_ISO_SEQ_ERR_EP4_UMSK (~(((1U << USB_ISO_SEQ_ERR_EP4_LEN) - 1) << USB_ISO_SEQ_ERR_EP4_POS))
#define USB_ISO_SEQ_ERR_EP5      USB_ISO_SEQ_ERR_EP5
#define USB_ISO_SEQ_ERR_EP5_POS  (20U)
#define USB_ISO_SEQ_ERR_EP5_LEN  (1U)
#define USB_ISO_SEQ_ERR_EP5_MSK  (((1U << USB_ISO_SEQ_ERR_EP5_LEN) - 1) << USB_ISO_SEQ_ERR_EP5_POS)
#define USB_ISO_SEQ_ERR_EP5_UMSK (~(((1U << USB_ISO_SEQ_ERR_EP5_LEN) - 1) << USB_ISO_SEQ_ERR_EP5_POS))
#define USB_ISO_SEQ_ERR_EP6      USB_ISO_SEQ_ERR_EP6
#define USB_ISO_SEQ_ERR_EP6_POS  (21U)
#define USB_ISO_SEQ_ERR_EP6_LEN  (1U)
#define USB_ISO_SEQ_ERR_EP6_MSK  (((1U << USB_ISO_SEQ_ERR_EP6_LEN) - 1) << USB_ISO_SEQ_ERR_EP6_POS)
#define USB_ISO_SEQ_ERR_EP6_UMSK (~(((1U << USB_ISO_SEQ_ERR_EP6_LEN) - 1) << USB_ISO_SEQ_ERR_EP6_POS))
#define USB_ISO_SEQ_ERR_EP7      USB_ISO_SEQ_ERR_EP7
#define USB_ISO_SEQ_ERR_EP7_POS  (22U)
#define USB_ISO_SEQ_ERR_EP7_LEN  (1U)
#define USB_ISO_SEQ_ERR_EP7_MSK  (((1U << USB_ISO_SEQ_ERR_EP7_LEN) - 1) << USB_ISO_SEQ_ERR_EP7_POS)
#define USB_ISO_SEQ_ERR_EP7_UMSK (~(((1U << USB_ISO_SEQ_ERR_EP7_LEN) - 1) << USB_ISO_SEQ_ERR_EP7_POS))
#define USB_ISO_SEQ_ERR_EP8      USB_ISO_SEQ_ERR_EP8
#define USB_ISO_SEQ_ERR_EP8_POS  (23U)
#define USB_ISO_SEQ_ERR_EP8_LEN  (1U)
#define USB_ISO_SEQ_ERR_EP8_MSK  (((1U << USB_ISO_SEQ_ERR_EP8_LEN) - 1) << USB_ISO_SEQ_ERR_EP8_POS)
#define USB_ISO_SEQ_ERR_EP8_UMSK (~(((1U << USB_ISO_SEQ_ERR_EP8_LEN) - 1) << USB_ISO_SEQ_ERR_EP8_POS))

/* 0x160 : DEV_INMPS1 */
#define USB_DEV_INMPS1_OFFSET    (0x160)
#define USB_MAXPS_IEP1           USB_MAXPS_IEP1
#define USB_MAXPS_IEP1_POS       (0U)
#define USB_MAXPS_IEP1_LEN       (11U)
#define USB_MAXPS_IEP1_MSK       (((1U << USB_MAXPS_IEP1_LEN) - 1) << USB_MAXPS_IEP1_POS)
#define USB_MAXPS_IEP1_UMSK      (~(((1U << USB_MAXPS_IEP1_LEN) - 1) << USB_MAXPS_IEP1_POS))
#define USB_STL_IEP1             USB_STL_IEP1
#define USB_STL_IEP1_POS         (11U)
#define USB_STL_IEP1_LEN         (1U)
#define USB_STL_IEP1_MSK         (((1U << USB_STL_IEP1_LEN) - 1) << USB_STL_IEP1_POS)
#define USB_STL_IEP1_UMSK        (~(((1U << USB_STL_IEP1_LEN) - 1) << USB_STL_IEP1_POS))
#define USB_RSTG_IEP1            USB_RSTG_IEP1
#define USB_RSTG_IEP1_POS        (12U)
#define USB_RSTG_IEP1_LEN        (1U)
#define USB_RSTG_IEP1_MSK        (((1U << USB_RSTG_IEP1_LEN) - 1) << USB_RSTG_IEP1_POS)
#define USB_RSTG_IEP1_UMSK       (~(((1U << USB_RSTG_IEP1_LEN) - 1) << USB_RSTG_IEP1_POS))
#define USB_TX_NUM_HBW_IEP1      USB_TX_NUM_HBW_IEP1
#define USB_TX_NUM_HBW_IEP1_POS  (13U)
#define USB_TX_NUM_HBW_IEP1_LEN  (2U)
#define USB_TX_NUM_HBW_IEP1_MSK  (((1U << USB_TX_NUM_HBW_IEP1_LEN) - 1) << USB_TX_NUM_HBW_IEP1_POS)
#define USB_TX_NUM_HBW_IEP1_UMSK (~(((1U << USB_TX_NUM_HBW_IEP1_LEN) - 1) << USB_TX_NUM_HBW_IEP1_POS))
#define USB_TX0BYTE_IEP1         USB_TX0BYTE_IEP1
#define USB_TX0BYTE_IEP1_POS     (15U)
#define USB_TX0BYTE_IEP1_LEN     (1U)
#define USB_TX0BYTE_IEP1_MSK     (((1U << USB_TX0BYTE_IEP1_LEN) - 1) << USB_TX0BYTE_IEP1_POS)
#define USB_TX0BYTE_IEP1_UMSK    (~(((1U << USB_TX0BYTE_IEP1_LEN) - 1) << USB_TX0BYTE_IEP1_POS))

/* 0x164 : DEV_INMPS2 */
#define USB_DEV_INMPS2_OFFSET    (0x164)
#define USB_MAXPS_IEP2           USB_MAXPS_IEP2
#define USB_MAXPS_IEP2_POS       (0U)
#define USB_MAXPS_IEP2_LEN       (11U)
#define USB_MAXPS_IEP2_MSK       (((1U << USB_MAXPS_IEP2_LEN) - 1) << USB_MAXPS_IEP2_POS)
#define USB_MAXPS_IEP2_UMSK      (~(((1U << USB_MAXPS_IEP2_LEN) - 1) << USB_MAXPS_IEP2_POS))
#define USB_STL_IEP2             USB_STL_IEP2
#define USB_STL_IEP2_POS         (11U)
#define USB_STL_IEP2_LEN         (1U)
#define USB_STL_IEP2_MSK         (((1U << USB_STL_IEP2_LEN) - 1) << USB_STL_IEP2_POS)
#define USB_STL_IEP2_UMSK        (~(((1U << USB_STL_IEP2_LEN) - 1) << USB_STL_IEP2_POS))
#define USB_RSTG_IEP2            USB_RSTG_IEP2
#define USB_RSTG_IEP2_POS        (12U)
#define USB_RSTG_IEP2_LEN        (1U)
#define USB_RSTG_IEP2_MSK        (((1U << USB_RSTG_IEP2_LEN) - 1) << USB_RSTG_IEP2_POS)
#define USB_RSTG_IEP2_UMSK       (~(((1U << USB_RSTG_IEP2_LEN) - 1) << USB_RSTG_IEP2_POS))
#define USB_TX_NUM_HBW_IEP2      USB_TX_NUM_HBW_IEP2
#define USB_TX_NUM_HBW_IEP2_POS  (13U)
#define USB_TX_NUM_HBW_IEP2_LEN  (2U)
#define USB_TX_NUM_HBW_IEP2_MSK  (((1U << USB_TX_NUM_HBW_IEP2_LEN) - 1) << USB_TX_NUM_HBW_IEP2_POS)
#define USB_TX_NUM_HBW_IEP2_UMSK (~(((1U << USB_TX_NUM_HBW_IEP2_LEN) - 1) << USB_TX_NUM_HBW_IEP2_POS))
#define USB_TX0BYTE_IEP2         USB_TX0BYTE_IEP2
#define USB_TX0BYTE_IEP2_POS     (15U)
#define USB_TX0BYTE_IEP2_LEN     (1U)
#define USB_TX0BYTE_IEP2_MSK     (((1U << USB_TX0BYTE_IEP2_LEN) - 1) << USB_TX0BYTE_IEP2_POS)
#define USB_TX0BYTE_IEP2_UMSK    (~(((1U << USB_TX0BYTE_IEP2_LEN) - 1) << USB_TX0BYTE_IEP2_POS))

/* 0x168 : DEV_INMPS3 */
#define USB_DEV_INMPS3_OFFSET    (0x168)
#define USB_MAXPS_IEP3           USB_MAXPS_IEP3
#define USB_MAXPS_IEP3_POS       (0U)
#define USB_MAXPS_IEP3_LEN       (11U)
#define USB_MAXPS_IEP3_MSK       (((1U << USB_MAXPS_IEP3_LEN) - 1) << USB_MAXPS_IEP3_POS)
#define USB_MAXPS_IEP3_UMSK      (~(((1U << USB_MAXPS_IEP3_LEN) - 1) << USB_MAXPS_IEP3_POS))
#define USB_STL_IEP3             USB_STL_IEP3
#define USB_STL_IEP3_POS         (11U)
#define USB_STL_IEP3_LEN         (1U)
#define USB_STL_IEP3_MSK         (((1U << USB_STL_IEP3_LEN) - 1) << USB_STL_IEP3_POS)
#define USB_STL_IEP3_UMSK        (~(((1U << USB_STL_IEP3_LEN) - 1) << USB_STL_IEP3_POS))
#define USB_RSTG_IEP3            USB_RSTG_IEP3
#define USB_RSTG_IEP3_POS        (12U)
#define USB_RSTG_IEP3_LEN        (1U)
#define USB_RSTG_IEP3_MSK        (((1U << USB_RSTG_IEP3_LEN) - 1) << USB_RSTG_IEP3_POS)
#define USB_RSTG_IEP3_UMSK       (~(((1U << USB_RSTG_IEP3_LEN) - 1) << USB_RSTG_IEP3_POS))
#define USB_TX_NUM_HBW_IEP3      USB_TX_NUM_HBW_IEP3
#define USB_TX_NUM_HBW_IEP3_POS  (13U)
#define USB_TX_NUM_HBW_IEP3_LEN  (2U)
#define USB_TX_NUM_HBW_IEP3_MSK  (((1U << USB_TX_NUM_HBW_IEP3_LEN) - 1) << USB_TX_NUM_HBW_IEP3_POS)
#define USB_TX_NUM_HBW_IEP3_UMSK (~(((1U << USB_TX_NUM_HBW_IEP3_LEN) - 1) << USB_TX_NUM_HBW_IEP3_POS))
#define USB_TX0BYTE_IEP3         USB_TX0BYTE_IEP3
#define USB_TX0BYTE_IEP3_POS     (15U)
#define USB_TX0BYTE_IEP3_LEN     (1U)
#define USB_TX0BYTE_IEP3_MSK     (((1U << USB_TX0BYTE_IEP3_LEN) - 1) << USB_TX0BYTE_IEP3_POS)
#define USB_TX0BYTE_IEP3_UMSK    (~(((1U << USB_TX0BYTE_IEP3_LEN) - 1) << USB_TX0BYTE_IEP3_POS))

/* 0x16C : DEV_INMPS4 */
#define USB_DEV_INMPS4_OFFSET    (0x16C)
#define USB_MAXPS_IEP4           USB_MAXPS_IEP4
#define USB_MAXPS_IEP4_POS       (0U)
#define USB_MAXPS_IEP4_LEN       (11U)
#define USB_MAXPS_IEP4_MSK       (((1U << USB_MAXPS_IEP4_LEN) - 1) << USB_MAXPS_IEP4_POS)
#define USB_MAXPS_IEP4_UMSK      (~(((1U << USB_MAXPS_IEP4_LEN) - 1) << USB_MAXPS_IEP4_POS))
#define USB_STL_IEP4             USB_STL_IEP4
#define USB_STL_IEP4_POS         (11U)
#define USB_STL_IEP4_LEN         (1U)
#define USB_STL_IEP4_MSK         (((1U << USB_STL_IEP4_LEN) - 1) << USB_STL_IEP4_POS)
#define USB_STL_IEP4_UMSK        (~(((1U << USB_STL_IEP4_LEN) - 1) << USB_STL_IEP4_POS))
#define USB_RSTG_IEP4            USB_RSTG_IEP4
#define USB_RSTG_IEP4_POS        (12U)
#define USB_RSTG_IEP4_LEN        (1U)
#define USB_RSTG_IEP4_MSK        (((1U << USB_RSTG_IEP4_LEN) - 1) << USB_RSTG_IEP4_POS)
#define USB_RSTG_IEP4_UMSK       (~(((1U << USB_RSTG_IEP4_LEN) - 1) << USB_RSTG_IEP4_POS))
#define USB_TX_NUM_HBW_IEP4      USB_TX_NUM_HBW_IEP4
#define USB_TX_NUM_HBW_IEP4_POS  (13U)
#define USB_TX_NUM_HBW_IEP4_LEN  (2U)
#define USB_TX_NUM_HBW_IEP4_MSK  (((1U << USB_TX_NUM_HBW_IEP4_LEN) - 1) << USB_TX_NUM_HBW_IEP4_POS)
#define USB_TX_NUM_HBW_IEP4_UMSK (~(((1U << USB_TX_NUM_HBW_IEP4_LEN) - 1) << USB_TX_NUM_HBW_IEP4_POS))
#define USB_TX0BYTE_IEP4         USB_TX0BYTE_IEP4
#define USB_TX0BYTE_IEP4_POS     (15U)
#define USB_TX0BYTE_IEP4_LEN     (1U)
#define USB_TX0BYTE_IEP4_MSK     (((1U << USB_TX0BYTE_IEP4_LEN) - 1) << USB_TX0BYTE_IEP4_POS)
#define USB_TX0BYTE_IEP4_UMSK    (~(((1U << USB_TX0BYTE_IEP4_LEN) - 1) << USB_TX0BYTE_IEP4_POS))

/* 0x170 : DEV_INMPS5 */
#define USB_DEV_INMPS5_OFFSET    (0x170)
#define USB_MAXPS_IEP5           USB_MAXPS_IEP5
#define USB_MAXPS_IEP5_POS       (0U)
#define USB_MAXPS_IEP5_LEN       (11U)
#define USB_MAXPS_IEP5_MSK       (((1U << USB_MAXPS_IEP5_LEN) - 1) << USB_MAXPS_IEP5_POS)
#define USB_MAXPS_IEP5_UMSK      (~(((1U << USB_MAXPS_IEP5_LEN) - 1) << USB_MAXPS_IEP5_POS))
#define USB_STL_IEP5             USB_STL_IEP5
#define USB_STL_IEP5_POS         (11U)
#define USB_STL_IEP5_LEN         (1U)
#define USB_STL_IEP5_MSK         (((1U << USB_STL_IEP5_LEN) - 1) << USB_STL_IEP5_POS)
#define USB_STL_IEP5_UMSK        (~(((1U << USB_STL_IEP5_LEN) - 1) << USB_STL_IEP5_POS))
#define USB_RSTG_IEP5            USB_RSTG_IEP5
#define USB_RSTG_IEP5_POS        (12U)
#define USB_RSTG_IEP5_LEN        (1U)
#define USB_RSTG_IEP5_MSK        (((1U << USB_RSTG_IEP5_LEN) - 1) << USB_RSTG_IEP5_POS)
#define USB_RSTG_IEP5_UMSK       (~(((1U << USB_RSTG_IEP5_LEN) - 1) << USB_RSTG_IEP5_POS))
#define USB_TX_NUM_HBW_IEP5      USB_TX_NUM_HBW_IEP5
#define USB_TX_NUM_HBW_IEP5_POS  (13U)
#define USB_TX_NUM_HBW_IEP5_LEN  (2U)
#define USB_TX_NUM_HBW_IEP5_MSK  (((1U << USB_TX_NUM_HBW_IEP5_LEN) - 1) << USB_TX_NUM_HBW_IEP5_POS)
#define USB_TX_NUM_HBW_IEP5_UMSK (~(((1U << USB_TX_NUM_HBW_IEP5_LEN) - 1) << USB_TX_NUM_HBW_IEP5_POS))
#define USB_TX0BYTE_IEP5         USB_TX0BYTE_IEP5
#define USB_TX0BYTE_IEP5_POS     (15U)
#define USB_TX0BYTE_IEP5_LEN     (1U)
#define USB_TX0BYTE_IEP5_MSK     (((1U << USB_TX0BYTE_IEP5_LEN) - 1) << USB_TX0BYTE_IEP5_POS)
#define USB_TX0BYTE_IEP5_UMSK    (~(((1U << USB_TX0BYTE_IEP5_LEN) - 1) << USB_TX0BYTE_IEP5_POS))

/* 0x174 : DEV_INMPS6 */
#define USB_DEV_INMPS6_OFFSET    (0x174)
#define USB_MAXPS_IEP6           USB_MAXPS_IEP6
#define USB_MAXPS_IEP6_POS       (0U)
#define USB_MAXPS_IEP6_LEN       (11U)
#define USB_MAXPS_IEP6_MSK       (((1U << USB_MAXPS_IEP6_LEN) - 1) << USB_MAXPS_IEP6_POS)
#define USB_MAXPS_IEP6_UMSK      (~(((1U << USB_MAXPS_IEP6_LEN) - 1) << USB_MAXPS_IEP6_POS))
#define USB_STL_IEP6             USB_STL_IEP6
#define USB_STL_IEP6_POS         (11U)
#define USB_STL_IEP6_LEN         (1U)
#define USB_STL_IEP6_MSK         (((1U << USB_STL_IEP6_LEN) - 1) << USB_STL_IEP6_POS)
#define USB_STL_IEP6_UMSK        (~(((1U << USB_STL_IEP6_LEN) - 1) << USB_STL_IEP6_POS))
#define USB_RSTG_IEP6            USB_RSTG_IEP6
#define USB_RSTG_IEP6_POS        (12U)
#define USB_RSTG_IEP6_LEN        (1U)
#define USB_RSTG_IEP6_MSK        (((1U << USB_RSTG_IEP6_LEN) - 1) << USB_RSTG_IEP6_POS)
#define USB_RSTG_IEP6_UMSK       (~(((1U << USB_RSTG_IEP6_LEN) - 1) << USB_RSTG_IEP6_POS))
#define USB_TX_NUM_HBW_IEP6      USB_TX_NUM_HBW_IEP6
#define USB_TX_NUM_HBW_IEP6_POS  (13U)
#define USB_TX_NUM_HBW_IEP6_LEN  (2U)
#define USB_TX_NUM_HBW_IEP6_MSK  (((1U << USB_TX_NUM_HBW_IEP6_LEN) - 1) << USB_TX_NUM_HBW_IEP6_POS)
#define USB_TX_NUM_HBW_IEP6_UMSK (~(((1U << USB_TX_NUM_HBW_IEP6_LEN) - 1) << USB_TX_NUM_HBW_IEP6_POS))
#define USB_TX0BYTE_IEP6         USB_TX0BYTE_IEP6
#define USB_TX0BYTE_IEP6_POS     (15U)
#define USB_TX0BYTE_IEP6_LEN     (1U)
#define USB_TX0BYTE_IEP6_MSK     (((1U << USB_TX0BYTE_IEP6_LEN) - 1) << USB_TX0BYTE_IEP6_POS)
#define USB_TX0BYTE_IEP6_UMSK    (~(((1U << USB_TX0BYTE_IEP6_LEN) - 1) << USB_TX0BYTE_IEP6_POS))

/* 0x178 : DEV_INMPS7 */
#define USB_DEV_INMPS7_OFFSET    (0x178)
#define USB_MAXPS_IEP7           USB_MAXPS_IEP7
#define USB_MAXPS_IEP7_POS       (0U)
#define USB_MAXPS_IEP7_LEN       (11U)
#define USB_MAXPS_IEP7_MSK       (((1U << USB_MAXPS_IEP7_LEN) - 1) << USB_MAXPS_IEP7_POS)
#define USB_MAXPS_IEP7_UMSK      (~(((1U << USB_MAXPS_IEP7_LEN) - 1) << USB_MAXPS_IEP7_POS))
#define USB_STL_IEP7             USB_STL_IEP7
#define USB_STL_IEP7_POS         (11U)
#define USB_STL_IEP7_LEN         (1U)
#define USB_STL_IEP7_MSK         (((1U << USB_STL_IEP7_LEN) - 1) << USB_STL_IEP7_POS)
#define USB_STL_IEP7_UMSK        (~(((1U << USB_STL_IEP7_LEN) - 1) << USB_STL_IEP7_POS))
#define USB_RSTG_IEP7            USB_RSTG_IEP7
#define USB_RSTG_IEP7_POS        (12U)
#define USB_RSTG_IEP7_LEN        (1U)
#define USB_RSTG_IEP7_MSK        (((1U << USB_RSTG_IEP7_LEN) - 1) << USB_RSTG_IEP7_POS)
#define USB_RSTG_IEP7_UMSK       (~(((1U << USB_RSTG_IEP7_LEN) - 1) << USB_RSTG_IEP7_POS))
#define USB_TX_NUM_HBW_IEP7      USB_TX_NUM_HBW_IEP7
#define USB_TX_NUM_HBW_IEP7_POS  (13U)
#define USB_TX_NUM_HBW_IEP7_LEN  (2U)
#define USB_TX_NUM_HBW_IEP7_MSK  (((1U << USB_TX_NUM_HBW_IEP7_LEN) - 1) << USB_TX_NUM_HBW_IEP7_POS)
#define USB_TX_NUM_HBW_IEP7_UMSK (~(((1U << USB_TX_NUM_HBW_IEP7_LEN) - 1) << USB_TX_NUM_HBW_IEP7_POS))
#define USB_TX0BYTE_IEP7         USB_TX0BYTE_IEP7
#define USB_TX0BYTE_IEP7_POS     (15U)
#define USB_TX0BYTE_IEP7_LEN     (1U)
#define USB_TX0BYTE_IEP7_MSK     (((1U << USB_TX0BYTE_IEP7_LEN) - 1) << USB_TX0BYTE_IEP7_POS)
#define USB_TX0BYTE_IEP7_UMSK    (~(((1U << USB_TX0BYTE_IEP7_LEN) - 1) << USB_TX0BYTE_IEP7_POS))

/* 0x17C : DEV_INMPS8 */
#define USB_DEV_INMPS8_OFFSET    (0x17C)
#define USB_MAXPS_IEP8           USB_MAXPS_IEP8
#define USB_MAXPS_IEP8_POS       (0U)
#define USB_MAXPS_IEP8_LEN       (11U)
#define USB_MAXPS_IEP8_MSK       (((1U << USB_MAXPS_IEP8_LEN) - 1) << USB_MAXPS_IEP8_POS)
#define USB_MAXPS_IEP8_UMSK      (~(((1U << USB_MAXPS_IEP8_LEN) - 1) << USB_MAXPS_IEP8_POS))
#define USB_STL_IEP8             USB_STL_IEP8
#define USB_STL_IEP8_POS         (11U)
#define USB_STL_IEP8_LEN         (1U)
#define USB_STL_IEP8_MSK         (((1U << USB_STL_IEP8_LEN) - 1) << USB_STL_IEP8_POS)
#define USB_STL_IEP8_UMSK        (~(((1U << USB_STL_IEP8_LEN) - 1) << USB_STL_IEP8_POS))
#define USB_RSTG_IEP8            USB_RSTG_IEP8
#define USB_RSTG_IEP8_POS        (12U)
#define USB_RSTG_IEP8_LEN        (1U)
#define USB_RSTG_IEP8_MSK        (((1U << USB_RSTG_IEP8_LEN) - 1) << USB_RSTG_IEP8_POS)
#define USB_RSTG_IEP8_UMSK       (~(((1U << USB_RSTG_IEP8_LEN) - 1) << USB_RSTG_IEP8_POS))
#define USB_TX_NUM_HBW_IEP8      USB_TX_NUM_HBW_IEP8
#define USB_TX_NUM_HBW_IEP8_POS  (13U)
#define USB_TX_NUM_HBW_IEP8_LEN  (2U)
#define USB_TX_NUM_HBW_IEP8_MSK  (((1U << USB_TX_NUM_HBW_IEP8_LEN) - 1) << USB_TX_NUM_HBW_IEP8_POS)
#define USB_TX_NUM_HBW_IEP8_UMSK (~(((1U << USB_TX_NUM_HBW_IEP8_LEN) - 1) << USB_TX_NUM_HBW_IEP8_POS))
#define USB_TX0BYTE_IEP8         USB_TX0BYTE_IEP8
#define USB_TX0BYTE_IEP8_POS     (15U)
#define USB_TX0BYTE_IEP8_LEN     (1U)
#define USB_TX0BYTE_IEP8_MSK     (((1U << USB_TX0BYTE_IEP8_LEN) - 1) << USB_TX0BYTE_IEP8_POS)
#define USB_TX0BYTE_IEP8_UMSK    (~(((1U << USB_TX0BYTE_IEP8_LEN) - 1) << USB_TX0BYTE_IEP8_POS))

/* 0x180 : DEV_OUTMPS1 */
#define USB_DEV_OUTMPS1_OFFSET (0x180)
#define USB_MAXPS_OEP1         USB_MAXPS_OEP1
#define USB_MAXPS_OEP1_POS     (0U)
#define USB_MAXPS_OEP1_LEN     (11U)
#define USB_MAXPS_OEP1_MSK     (((1U << USB_MAXPS_OEP1_LEN) - 1) << USB_MAXPS_OEP1_POS)
#define USB_MAXPS_OEP1_UMSK    (~(((1U << USB_MAXPS_OEP1_LEN) - 1) << USB_MAXPS_OEP1_POS))
#define USB_STL_OEP1           USB_STL_OEP1
#define USB_STL_OEP1_POS       (11U)
#define USB_STL_OEP1_LEN       (1U)
#define USB_STL_OEP1_MSK       (((1U << USB_STL_OEP1_LEN) - 1) << USB_STL_OEP1_POS)
#define USB_STL_OEP1_UMSK      (~(((1U << USB_STL_OEP1_LEN) - 1) << USB_STL_OEP1_POS))
#define USB_RSTG_OEP1          USB_RSTG_OEP1
#define USB_RSTG_OEP1_POS      (12U)
#define USB_RSTG_OEP1_LEN      (1U)
#define USB_RSTG_OEP1_MSK      (((1U << USB_RSTG_OEP1_LEN) - 1) << USB_RSTG_OEP1_POS)
#define USB_RSTG_OEP1_UMSK     (~(((1U << USB_RSTG_OEP1_LEN) - 1) << USB_RSTG_OEP1_POS))

/* 0x184 : DEV_OUTMPS2 */
#define USB_DEV_OUTMPS2_OFFSET (0x184)
#define USB_MAXPS_OEP2         USB_MAXPS_OEP2
#define USB_MAXPS_OEP2_POS     (0U)
#define USB_MAXPS_OEP2_LEN     (11U)
#define USB_MAXPS_OEP2_MSK     (((1U << USB_MAXPS_OEP2_LEN) - 1) << USB_MAXPS_OEP2_POS)
#define USB_MAXPS_OEP2_UMSK    (~(((1U << USB_MAXPS_OEP2_LEN) - 1) << USB_MAXPS_OEP2_POS))
#define USB_STL_OEP2           USB_STL_OEP2
#define USB_STL_OEP2_POS       (11U)
#define USB_STL_OEP2_LEN       (1U)
#define USB_STL_OEP2_MSK       (((1U << USB_STL_OEP2_LEN) - 1) << USB_STL_OEP2_POS)
#define USB_STL_OEP2_UMSK      (~(((1U << USB_STL_OEP2_LEN) - 1) << USB_STL_OEP2_POS))
#define USB_RSTG_OEP2          USB_RSTG_OEP2
#define USB_RSTG_OEP2_POS      (12U)
#define USB_RSTG_OEP2_LEN      (1U)
#define USB_RSTG_OEP2_MSK      (((1U << USB_RSTG_OEP2_LEN) - 1) << USB_RSTG_OEP2_POS)
#define USB_RSTG_OEP2_UMSK     (~(((1U << USB_RSTG_OEP2_LEN) - 1) << USB_RSTG_OEP2_POS))

/* 0x188 : DEV_OUTMPS3 */
#define USB_DEV_OUTMPS3_OFFSET (0x188)
#define USB_MAXPS_OEP3         USB_MAXPS_OEP3
#define USB_MAXPS_OEP3_POS     (0U)
#define USB_MAXPS_OEP3_LEN     (11U)
#define USB_MAXPS_OEP3_MSK     (((1U << USB_MAXPS_OEP3_LEN) - 1) << USB_MAXPS_OEP3_POS)
#define USB_MAXPS_OEP3_UMSK    (~(((1U << USB_MAXPS_OEP3_LEN) - 1) << USB_MAXPS_OEP3_POS))
#define USB_STL_OEP3           USB_STL_OEP3
#define USB_STL_OEP3_POS       (11U)
#define USB_STL_OEP3_LEN       (1U)
#define USB_STL_OEP3_MSK       (((1U << USB_STL_OEP3_LEN) - 1) << USB_STL_OEP3_POS)
#define USB_STL_OEP3_UMSK      (~(((1U << USB_STL_OEP3_LEN) - 1) << USB_STL_OEP3_POS))
#define USB_RSTG_OEP3          USB_RSTG_OEP3
#define USB_RSTG_OEP3_POS      (12U)
#define USB_RSTG_OEP3_LEN      (1U)
#define USB_RSTG_OEP3_MSK      (((1U << USB_RSTG_OEP3_LEN) - 1) << USB_RSTG_OEP3_POS)
#define USB_RSTG_OEP3_UMSK     (~(((1U << USB_RSTG_OEP3_LEN) - 1) << USB_RSTG_OEP3_POS))

/* 0x18C : DEV_OUTMPS4 */
#define USB_DEV_OUTMPS4_OFFSET (0x18C)
#define USB_MAXPS_OEP4         USB_MAXPS_OEP4
#define USB_MAXPS_OEP4_POS     (0U)
#define USB_MAXPS_OEP4_LEN     (11U)
#define USB_MAXPS_OEP4_MSK     (((1U << USB_MAXPS_OEP4_LEN) - 1) << USB_MAXPS_OEP4_POS)
#define USB_MAXPS_OEP4_UMSK    (~(((1U << USB_MAXPS_OEP4_LEN) - 1) << USB_MAXPS_OEP4_POS))
#define USB_STL_OEP4           USB_STL_OEP4
#define USB_STL_OEP4_POS       (11U)
#define USB_STL_OEP4_LEN       (1U)
#define USB_STL_OEP4_MSK       (((1U << USB_STL_OEP4_LEN) - 1) << USB_STL_OEP4_POS)
#define USB_STL_OEP4_UMSK      (~(((1U << USB_STL_OEP4_LEN) - 1) << USB_STL_OEP4_POS))
#define USB_RSTG_OEP4          USB_RSTG_OEP4
#define USB_RSTG_OEP4_POS      (12U)
#define USB_RSTG_OEP4_LEN      (1U)
#define USB_RSTG_OEP4_MSK      (((1U << USB_RSTG_OEP4_LEN) - 1) << USB_RSTG_OEP4_POS)
#define USB_RSTG_OEP4_UMSK     (~(((1U << USB_RSTG_OEP4_LEN) - 1) << USB_RSTG_OEP4_POS))

/* 0x190 : DEV_OUTMPS5 */
#define USB_DEV_OUTMPS5_OFFSET (0x190)
#define USB_MAXPS_OEP5         USB_MAXPS_OEP5
#define USB_MAXPS_OEP5_POS     (0U)
#define USB_MAXPS_OEP5_LEN     (11U)
#define USB_MAXPS_OEP5_MSK     (((1U << USB_MAXPS_OEP5_LEN) - 1) << USB_MAXPS_OEP5_POS)
#define USB_MAXPS_OEP5_UMSK    (~(((1U << USB_MAXPS_OEP5_LEN) - 1) << USB_MAXPS_OEP5_POS))
#define USB_STL_OEP5           USB_STL_OEP5
#define USB_STL_OEP5_POS       (11U)
#define USB_STL_OEP5_LEN       (1U)
#define USB_STL_OEP5_MSK       (((1U << USB_STL_OEP5_LEN) - 1) << USB_STL_OEP5_POS)
#define USB_STL_OEP5_UMSK      (~(((1U << USB_STL_OEP5_LEN) - 1) << USB_STL_OEP5_POS))
#define USB_RSTG_OEP5          USB_RSTG_OEP5
#define USB_RSTG_OEP5_POS      (12U)
#define USB_RSTG_OEP5_LEN      (1U)
#define USB_RSTG_OEP5_MSK      (((1U << USB_RSTG_OEP5_LEN) - 1) << USB_RSTG_OEP5_POS)
#define USB_RSTG_OEP5_UMSK     (~(((1U << USB_RSTG_OEP5_LEN) - 1) << USB_RSTG_OEP5_POS))

/* 0x194 : DEV_OUTMPS6 */
#define USB_DEV_OUTMPS6_OFFSET (0x194)
#define USB_MAXPS_OEP6         USB_MAXPS_OEP6
#define USB_MAXPS_OEP6_POS     (0U)
#define USB_MAXPS_OEP6_LEN     (11U)
#define USB_MAXPS_OEP6_MSK     (((1U << USB_MAXPS_OEP6_LEN) - 1) << USB_MAXPS_OEP6_POS)
#define USB_MAXPS_OEP6_UMSK    (~(((1U << USB_MAXPS_OEP6_LEN) - 1) << USB_MAXPS_OEP6_POS))
#define USB_STL_OEP6           USB_STL_OEP6
#define USB_STL_OEP6_POS       (11U)
#define USB_STL_OEP6_LEN       (1U)
#define USB_STL_OEP6_MSK       (((1U << USB_STL_OEP6_LEN) - 1) << USB_STL_OEP6_POS)
#define USB_STL_OEP6_UMSK      (~(((1U << USB_STL_OEP6_LEN) - 1) << USB_STL_OEP6_POS))
#define USB_RSTG_OEP6          USB_RSTG_OEP6
#define USB_RSTG_OEP6_POS      (12U)
#define USB_RSTG_OEP6_LEN      (1U)
#define USB_RSTG_OEP6_MSK      (((1U << USB_RSTG_OEP6_LEN) - 1) << USB_RSTG_OEP6_POS)
#define USB_RSTG_OEP6_UMSK     (~(((1U << USB_RSTG_OEP6_LEN) - 1) << USB_RSTG_OEP6_POS))

/* 0x198 : DEV_OUTMPS7 */
#define USB_DEV_OUTMPS7_OFFSET (0x198)
#define USB_MAXPS_OEP7         USB_MAXPS_OEP7
#define USB_MAXPS_OEP7_POS     (0U)
#define USB_MAXPS_OEP7_LEN     (11U)
#define USB_MAXPS_OEP7_MSK     (((1U << USB_MAXPS_OEP7_LEN) - 1) << USB_MAXPS_OEP7_POS)
#define USB_MAXPS_OEP7_UMSK    (~(((1U << USB_MAXPS_OEP7_LEN) - 1) << USB_MAXPS_OEP7_POS))
#define USB_STL_OEP7           USB_STL_OEP7
#define USB_STL_OEP7_POS       (11U)
#define USB_STL_OEP7_LEN       (1U)
#define USB_STL_OEP7_MSK       (((1U << USB_STL_OEP7_LEN) - 1) << USB_STL_OEP7_POS)
#define USB_STL_OEP7_UMSK      (~(((1U << USB_STL_OEP7_LEN) - 1) << USB_STL_OEP7_POS))
#define USB_RSTG_OEP7          USB_RSTG_OEP7
#define USB_RSTG_OEP7_POS      (12U)
#define USB_RSTG_OEP7_LEN      (1U)
#define USB_RSTG_OEP7_MSK      (((1U << USB_RSTG_OEP7_LEN) - 1) << USB_RSTG_OEP7_POS)
#define USB_RSTG_OEP7_UMSK     (~(((1U << USB_RSTG_OEP7_LEN) - 1) << USB_RSTG_OEP7_POS))

/* 0x19C : DEV_OUTMPS8 */
#define USB_DEV_OUTMPS8_OFFSET (0x19C)
#define USB_MAXPS_OEP8         USB_MAXPS_OEP8
#define USB_MAXPS_OEP8_POS     (0U)
#define USB_MAXPS_OEP8_LEN     (11U)
#define USB_MAXPS_OEP8_MSK     (((1U << USB_MAXPS_OEP8_LEN) - 1) << USB_MAXPS_OEP8_POS)
#define USB_MAXPS_OEP8_UMSK    (~(((1U << USB_MAXPS_OEP8_LEN) - 1) << USB_MAXPS_OEP8_POS))
#define USB_STL_OEP8           USB_STL_OEP8
#define USB_STL_OEP8_POS       (11U)
#define USB_STL_OEP8_LEN       (1U)
#define USB_STL_OEP8_MSK       (((1U << USB_STL_OEP8_LEN) - 1) << USB_STL_OEP8_POS)
#define USB_STL_OEP8_UMSK      (~(((1U << USB_STL_OEP8_LEN) - 1) << USB_STL_OEP8_POS))
#define USB_RSTG_OEP8          USB_RSTG_OEP8
#define USB_RSTG_OEP8_POS      (12U)
#define USB_RSTG_OEP8_LEN      (1U)
#define USB_RSTG_OEP8_MSK      (((1U << USB_RSTG_OEP8_LEN) - 1) << USB_RSTG_OEP8_POS)
#define USB_RSTG_OEP8_UMSK     (~(((1U << USB_RSTG_OEP8_LEN) - 1) << USB_RSTG_OEP8_POS))

/* 0x1A0 : DEV_EPMAP0 */
#define USB_DEV_EPMAP0_OFFSET (0x1A0)
#define USB_FNO_IEP1          USB_FNO_IEP1
#define USB_FNO_IEP1_POS      (0U)
#define USB_FNO_IEP1_LEN      (4U)
#define USB_FNO_IEP1_MSK      (((1U << USB_FNO_IEP1_LEN) - 1) << USB_FNO_IEP1_POS)
#define USB_FNO_IEP1_UMSK     (~(((1U << USB_FNO_IEP1_LEN) - 1) << USB_FNO_IEP1_POS))
#define USB_FNO_OEP1          USB_FNO_OEP1
#define USB_FNO_OEP1_POS      (4U)
#define USB_FNO_OEP1_LEN      (4U)
#define USB_FNO_OEP1_MSK      (((1U << USB_FNO_OEP1_LEN) - 1) << USB_FNO_OEP1_POS)
#define USB_FNO_OEP1_UMSK     (~(((1U << USB_FNO_OEP1_LEN) - 1) << USB_FNO_OEP1_POS))
#define USB_FNO_IEP2          USB_FNO_IEP2
#define USB_FNO_IEP2_POS      (8U)
#define USB_FNO_IEP2_LEN      (4U)
#define USB_FNO_IEP2_MSK      (((1U << USB_FNO_IEP2_LEN) - 1) << USB_FNO_IEP2_POS)
#define USB_FNO_IEP2_UMSK     (~(((1U << USB_FNO_IEP2_LEN) - 1) << USB_FNO_IEP2_POS))
#define USB_FNO_OEP2          USB_FNO_OEP2
#define USB_FNO_OEP2_POS      (12U)
#define USB_FNO_OEP2_LEN      (4U)
#define USB_FNO_OEP2_MSK      (((1U << USB_FNO_OEP2_LEN) - 1) << USB_FNO_OEP2_POS)
#define USB_FNO_OEP2_UMSK     (~(((1U << USB_FNO_OEP2_LEN) - 1) << USB_FNO_OEP2_POS))
#define USB_FNO_IEP3          USB_FNO_IEP3
#define USB_FNO_IEP3_POS      (16U)
#define USB_FNO_IEP3_LEN      (4U)
#define USB_FNO_IEP3_MSK      (((1U << USB_FNO_IEP3_LEN) - 1) << USB_FNO_IEP3_POS)
#define USB_FNO_IEP3_UMSK     (~(((1U << USB_FNO_IEP3_LEN) - 1) << USB_FNO_IEP3_POS))
#define USB_FNO_OEP3          USB_FNO_OEP3
#define USB_FNO_OEP3_POS      (20U)
#define USB_FNO_OEP3_LEN      (4U)
#define USB_FNO_OEP3_MSK      (((1U << USB_FNO_OEP3_LEN) - 1) << USB_FNO_OEP3_POS)
#define USB_FNO_OEP3_UMSK     (~(((1U << USB_FNO_OEP3_LEN) - 1) << USB_FNO_OEP3_POS))
#define USB_FNO_IEP4          USB_FNO_IEP4
#define USB_FNO_IEP4_POS      (24U)
#define USB_FNO_IEP4_LEN      (4U)
#define USB_FNO_IEP4_MSK      (((1U << USB_FNO_IEP4_LEN) - 1) << USB_FNO_IEP4_POS)
#define USB_FNO_IEP4_UMSK     (~(((1U << USB_FNO_IEP4_LEN) - 1) << USB_FNO_IEP4_POS))
#define USB_FNO_OEP4          USB_FNO_OEP4
#define USB_FNO_OEP4_POS      (28U)
#define USB_FNO_OEP4_LEN      (4U)
#define USB_FNO_OEP4_MSK      (((1U << USB_FNO_OEP4_LEN) - 1) << USB_FNO_OEP4_POS)
#define USB_FNO_OEP4_UMSK     (~(((1U << USB_FNO_OEP4_LEN) - 1) << USB_FNO_OEP4_POS))

/* 0x1A4 : DEV_EPMAP1 */
#define USB_DEV_EPMAP1_OFFSET (0x1A4)
#define USB_FNO_IEP5          USB_FNO_IEP5
#define USB_FNO_IEP5_POS      (0U)
#define USB_FNO_IEP5_LEN      (4U)
#define USB_FNO_IEP5_MSK      (((1U << USB_FNO_IEP5_LEN) - 1) << USB_FNO_IEP5_POS)
#define USB_FNO_IEP5_UMSK     (~(((1U << USB_FNO_IEP5_LEN) - 1) << USB_FNO_IEP5_POS))
#define USB_FNO_OEP5          USB_FNO_OEP5
#define USB_FNO_OEP5_POS      (4U)
#define USB_FNO_OEP5_LEN      (4U)
#define USB_FNO_OEP5_MSK      (((1U << USB_FNO_OEP5_LEN) - 1) << USB_FNO_OEP5_POS)
#define USB_FNO_OEP5_UMSK     (~(((1U << USB_FNO_OEP5_LEN) - 1) << USB_FNO_OEP5_POS))
#define USB_FNO_IEP6          USB_FNO_IEP6
#define USB_FNO_IEP6_POS      (8U)
#define USB_FNO_IEP6_LEN      (4U)
#define USB_FNO_IEP6_MSK      (((1U << USB_FNO_IEP6_LEN) - 1) << USB_FNO_IEP6_POS)
#define USB_FNO_IEP6_UMSK     (~(((1U << USB_FNO_IEP6_LEN) - 1) << USB_FNO_IEP6_POS))
#define USB_FNO_OEP6          USB_FNO_OEP6
#define USB_FNO_OEP6_POS      (12U)
#define USB_FNO_OEP6_LEN      (4U)
#define USB_FNO_OEP6_MSK      (((1U << USB_FNO_OEP6_LEN) - 1) << USB_FNO_OEP6_POS)
#define USB_FNO_OEP6_UMSK     (~(((1U << USB_FNO_OEP6_LEN) - 1) << USB_FNO_OEP6_POS))
#define USB_FNO_IEP7          USB_FNO_IEP7
#define USB_FNO_IEP7_POS      (16U)
#define USB_FNO_IEP7_LEN      (4U)
#define USB_FNO_IEP7_MSK      (((1U << USB_FNO_IEP7_LEN) - 1) << USB_FNO_IEP7_POS)
#define USB_FNO_IEP7_UMSK     (~(((1U << USB_FNO_IEP7_LEN) - 1) << USB_FNO_IEP7_POS))
#define USB_FNO_OEP7          USB_FNO_OEP7
#define USB_FNO_OEP7_POS      (20U)
#define USB_FNO_OEP7_LEN      (4U)
#define USB_FNO_OEP7_MSK      (((1U << USB_FNO_OEP7_LEN) - 1) << USB_FNO_OEP7_POS)
#define USB_FNO_OEP7_UMSK     (~(((1U << USB_FNO_OEP7_LEN) - 1) << USB_FNO_OEP7_POS))
#define USB_FNO_IEP8          USB_FNO_IEP8
#define USB_FNO_IEP8_POS      (24U)
#define USB_FNO_IEP8_LEN      (4U)
#define USB_FNO_IEP8_MSK      (((1U << USB_FNO_IEP8_LEN) - 1) << USB_FNO_IEP8_POS)
#define USB_FNO_IEP8_UMSK     (~(((1U << USB_FNO_IEP8_LEN) - 1) << USB_FNO_IEP8_POS))
#define USB_FNO_OEP8          USB_FNO_OEP8
#define USB_FNO_OEP8_POS      (28U)
#define USB_FNO_OEP8_LEN      (4U)
#define USB_FNO_OEP8_MSK      (((1U << USB_FNO_OEP8_LEN) - 1) << USB_FNO_OEP8_POS)
#define USB_FNO_OEP8_UMSK     (~(((1U << USB_FNO_OEP8_LEN) - 1) << USB_FNO_OEP8_POS))

/* 0x1A8 : DEV_FMAP */
#define USB_DEV_FMAP_OFFSET (0x1A8)
#define USB_EPNO_FIFO0      USB_EPNO_FIFO0
#define USB_EPNO_FIFO0_POS  (0U)
#define USB_EPNO_FIFO0_LEN  (4U)
#define USB_EPNO_FIFO0_MSK  (((1U << USB_EPNO_FIFO0_LEN) - 1) << USB_EPNO_FIFO0_POS)
#define USB_EPNO_FIFO0_UMSK (~(((1U << USB_EPNO_FIFO0_LEN) - 1) << USB_EPNO_FIFO0_POS))
#define USB_DIR_FIFO0       USB_DIR_FIFO0
#define USB_DIR_FIFO0_POS   (4U)
#define USB_DIR_FIFO0_LEN   (2U)
#define USB_DIR_FIFO0_MSK   (((1U << USB_DIR_FIFO0_LEN) - 1) << USB_DIR_FIFO0_POS)
#define USB_DIR_FIFO0_UMSK  (~(((1U << USB_DIR_FIFO0_LEN) - 1) << USB_DIR_FIFO0_POS))
#define USB_EPNO_FIFO1      USB_EPNO_FIFO1
#define USB_EPNO_FIFO1_POS  (8U)
#define USB_EPNO_FIFO1_LEN  (4U)
#define USB_EPNO_FIFO1_MSK  (((1U << USB_EPNO_FIFO1_LEN) - 1) << USB_EPNO_FIFO1_POS)
#define USB_EPNO_FIFO1_UMSK (~(((1U << USB_EPNO_FIFO1_LEN) - 1) << USB_EPNO_FIFO1_POS))
#define USB_DIR_FIFO1       USB_DIR_FIFO1
#define USB_DIR_FIFO1_POS   (12U)
#define USB_DIR_FIFO1_LEN   (2U)
#define USB_DIR_FIFO1_MSK   (((1U << USB_DIR_FIFO1_LEN) - 1) << USB_DIR_FIFO1_POS)
#define USB_DIR_FIFO1_UMSK  (~(((1U << USB_DIR_FIFO1_LEN) - 1) << USB_DIR_FIFO1_POS))
#define USB_EPNO_FIFO2      USB_EPNO_FIFO2
#define USB_EPNO_FIFO2_POS  (16U)
#define USB_EPNO_FIFO2_LEN  (4U)
#define USB_EPNO_FIFO2_MSK  (((1U << USB_EPNO_FIFO2_LEN) - 1) << USB_EPNO_FIFO2_POS)
#define USB_EPNO_FIFO2_UMSK (~(((1U << USB_EPNO_FIFO2_LEN) - 1) << USB_EPNO_FIFO2_POS))
#define USB_DIR_FIFO2       USB_DIR_FIFO2
#define USB_DIR_FIFO2_POS   (20U)
#define USB_DIR_FIFO2_LEN   (2U)
#define USB_DIR_FIFO2_MSK   (((1U << USB_DIR_FIFO2_LEN) - 1) << USB_DIR_FIFO2_POS)
#define USB_DIR_FIFO2_UMSK  (~(((1U << USB_DIR_FIFO2_LEN) - 1) << USB_DIR_FIFO2_POS))
#define USB_EPNO_FIFO3      USB_EPNO_FIFO3
#define USB_EPNO_FIFO3_POS  (24U)
#define USB_EPNO_FIFO3_LEN  (4U)
#define USB_EPNO_FIFO3_MSK  (((1U << USB_EPNO_FIFO3_LEN) - 1) << USB_EPNO_FIFO3_POS)
#define USB_EPNO_FIFO3_UMSK (~(((1U << USB_EPNO_FIFO3_LEN) - 1) << USB_EPNO_FIFO3_POS))
#define USB_DIR_FIFO3       USB_DIR_FIFO3
#define USB_DIR_FIFO3_POS   (28U)
#define USB_DIR_FIFO3_LEN   (2U)
#define USB_DIR_FIFO3_MSK   (((1U << USB_DIR_FIFO3_LEN) - 1) << USB_DIR_FIFO3_POS)
#define USB_DIR_FIFO3_UMSK  (~(((1U << USB_DIR_FIFO3_LEN) - 1) << USB_DIR_FIFO3_POS))

/* 0x1AC : DEV_FCFG */
#define USB_DEV_FCFG_OFFSET (0x1AC)
#define USB_BLK_TYP_F0      USB_BLK_TYP_F0
#define USB_BLK_TYP_F0_POS  (0U)
#define USB_BLK_TYP_F0_LEN  (2U)
#define USB_BLK_TYP_F0_MSK  (((1U << USB_BLK_TYP_F0_LEN) - 1) << USB_BLK_TYP_F0_POS)
#define USB_BLK_TYP_F0_UMSK (~(((1U << USB_BLK_TYP_F0_LEN) - 1) << USB_BLK_TYP_F0_POS))
#define USB_BLKNO_F0        USB_BLKNO_F0
#define USB_BLKNO_F0_POS    (2U)
#define USB_BLKNO_F0_LEN    (2U)
#define USB_BLKNO_F0_MSK    (((1U << USB_BLKNO_F0_LEN) - 1) << USB_BLKNO_F0_POS)
#define USB_BLKNO_F0_UMSK   (~(((1U << USB_BLKNO_F0_LEN) - 1) << USB_BLKNO_F0_POS))
#define USB_BLKSZ_F0        USB_BLKSZ_F0
#define USB_BLKSZ_F0_POS    (4U)
#define USB_BLKSZ_F0_LEN    (1U)
#define USB_BLKSZ_F0_MSK    (((1U << USB_BLKSZ_F0_LEN) - 1) << USB_BLKSZ_F0_POS)
#define USB_BLKSZ_F0_UMSK   (~(((1U << USB_BLKSZ_F0_LEN) - 1) << USB_BLKSZ_F0_POS))
#define USB_EN_F0           USB_EN_F0
#define USB_EN_F0_POS       (5U)
#define USB_EN_F0_LEN       (1U)
#define USB_EN_F0_MSK       (((1U << USB_EN_F0_LEN) - 1) << USB_EN_F0_POS)
#define USB_EN_F0_UMSK      (~(((1U << USB_EN_F0_LEN) - 1) << USB_EN_F0_POS))
#define USB_BLK_TYP_F1      USB_BLK_TYP_F1
#define USB_BLK_TYP_F1_POS  (8U)
#define USB_BLK_TYP_F1_LEN  (2U)
#define USB_BLK_TYP_F1_MSK  (((1U << USB_BLK_TYP_F1_LEN) - 1) << USB_BLK_TYP_F1_POS)
#define USB_BLK_TYP_F1_UMSK (~(((1U << USB_BLK_TYP_F1_LEN) - 1) << USB_BLK_TYP_F1_POS))
#define USB_BLKNO_F1        USB_BLKNO_F1
#define USB_BLKNO_F1_POS    (10U)
#define USB_BLKNO_F1_LEN    (2U)
#define USB_BLKNO_F1_MSK    (((1U << USB_BLKNO_F1_LEN) - 1) << USB_BLKNO_F1_POS)
#define USB_BLKNO_F1_UMSK   (~(((1U << USB_BLKNO_F1_LEN) - 1) << USB_BLKNO_F1_POS))
#define USB_BLKSZ_F1        USB_BLKSZ_F1
#define USB_BLKSZ_F1_POS    (12U)
#define USB_BLKSZ_F1_LEN    (1U)
#define USB_BLKSZ_F1_MSK    (((1U << USB_BLKSZ_F1_LEN) - 1) << USB_BLKSZ_F1_POS)
#define USB_BLKSZ_F1_UMSK   (~(((1U << USB_BLKSZ_F1_LEN) - 1) << USB_BLKSZ_F1_POS))
#define USB_EN_F1           USB_EN_F1
#define USB_EN_F1_POS       (13U)
#define USB_EN_F1_LEN       (1U)
#define USB_EN_F1_MSK       (((1U << USB_EN_F1_LEN) - 1) << USB_EN_F1_POS)
#define USB_EN_F1_UMSK      (~(((1U << USB_EN_F1_LEN) - 1) << USB_EN_F1_POS))
#define USB_BLK_TYP_F2      USB_BLK_TYP_F2
#define USB_BLK_TYP_F2_POS  (16U)
#define USB_BLK_TYP_F2_LEN  (2U)
#define USB_BLK_TYP_F2_MSK  (((1U << USB_BLK_TYP_F2_LEN) - 1) << USB_BLK_TYP_F2_POS)
#define USB_BLK_TYP_F2_UMSK (~(((1U << USB_BLK_TYP_F2_LEN) - 1) << USB_BLK_TYP_F2_POS))
#define USB_BLKNO_F2        USB_BLKNO_F2
#define USB_BLKNO_F2_POS    (18U)
#define USB_BLKNO_F2_LEN    (2U)
#define USB_BLKNO_F2_MSK    (((1U << USB_BLKNO_F2_LEN) - 1) << USB_BLKNO_F2_POS)
#define USB_BLKNO_F2_UMSK   (~(((1U << USB_BLKNO_F2_LEN) - 1) << USB_BLKNO_F2_POS))
#define USB_BLKSZ_F2        USB_BLKSZ_F2
#define USB_BLKSZ_F2_POS    (20U)
#define USB_BLKSZ_F2_LEN    (1U)
#define USB_BLKSZ_F2_MSK    (((1U << USB_BLKSZ_F2_LEN) - 1) << USB_BLKSZ_F2_POS)
#define USB_BLKSZ_F2_UMSK   (~(((1U << USB_BLKSZ_F2_LEN) - 1) << USB_BLKSZ_F2_POS))
#define USB_EN_F2           USB_EN_F2
#define USB_EN_F2_POS       (21U)
#define USB_EN_F2_LEN       (1U)
#define USB_EN_F2_MSK       (((1U << USB_EN_F2_LEN) - 1) << USB_EN_F2_POS)
#define USB_EN_F2_UMSK      (~(((1U << USB_EN_F2_LEN) - 1) << USB_EN_F2_POS))
#define USB_BLK_TYP_F3      USB_BLK_TYP_F3
#define USB_BLK_TYP_F3_POS  (24U)
#define USB_BLK_TYP_F3_LEN  (2U)
#define USB_BLK_TYP_F3_MSK  (((1U << USB_BLK_TYP_F3_LEN) - 1) << USB_BLK_TYP_F3_POS)
#define USB_BLK_TYP_F3_UMSK (~(((1U << USB_BLK_TYP_F3_LEN) - 1) << USB_BLK_TYP_F3_POS))
#define USB_BLKNO_F3        USB_BLKNO_F3
#define USB_BLKNO_F3_POS    (26U)
#define USB_BLKNO_F3_LEN    (2U)
#define USB_BLKNO_F3_MSK    (((1U << USB_BLKNO_F3_LEN) - 1) << USB_BLKNO_F3_POS)
#define USB_BLKNO_F3_UMSK   (~(((1U << USB_BLKNO_F3_LEN) - 1) << USB_BLKNO_F3_POS))
#define USB_BLKSZ_F3        USB_BLKSZ_F3
#define USB_BLKSZ_F3_POS    (28U)
#define USB_BLKSZ_F3_LEN    (1U)
#define USB_BLKSZ_F3_MSK    (((1U << USB_BLKSZ_F3_LEN) - 1) << USB_BLKSZ_F3_POS)
#define USB_BLKSZ_F3_UMSK   (~(((1U << USB_BLKSZ_F3_LEN) - 1) << USB_BLKSZ_F3_POS))
#define USB_EN_F3           USB_EN_F3
#define USB_EN_F3_POS       (29U)
#define USB_EN_F3_LEN       (1U)
#define USB_EN_F3_MSK       (((1U << USB_EN_F3_LEN) - 1) << USB_EN_F3_POS)
#define USB_EN_F3_UMSK      (~(((1U << USB_EN_F3_LEN) - 1) << USB_EN_F3_POS))

/* 0x1B0 : DEV_FIBC0 */
#define USB_DEV_FIBC0_OFFSET (0x1B0)
#define USB_BC_F0            USB_BC_F0
#define USB_BC_F0_POS        (0U)
#define USB_BC_F0_LEN        (11U)
#define USB_BC_F0_MSK        (((1U << USB_BC_F0_LEN) - 1) << USB_BC_F0_POS)
#define USB_BC_F0_UMSK       (~(((1U << USB_BC_F0_LEN) - 1) << USB_BC_F0_POS))
#define USB_FFRST0_HOV       USB_FFRST0_HOV
#define USB_FFRST0_HOV_POS   (12U)
#define USB_FFRST0_HOV_LEN   (1U)
#define USB_FFRST0_HOV_MSK   (((1U << USB_FFRST0_HOV_LEN) - 1) << USB_FFRST0_HOV_POS)
#define USB_FFRST0_HOV_UMSK  (~(((1U << USB_FFRST0_HOV_LEN) - 1) << USB_FFRST0_HOV_POS))

/* 0x1B4 : DEV_FIBC1 */
#define USB_DEV_FIBC1_OFFSET (0x1B4)
#define USB_BC_F1            USB_BC_F1
#define USB_BC_F1_POS        (0U)
#define USB_BC_F1_LEN        (11U)
#define USB_BC_F1_MSK        (((1U << USB_BC_F1_LEN) - 1) << USB_BC_F1_POS)
#define USB_BC_F1_UMSK       (~(((1U << USB_BC_F1_LEN) - 1) << USB_BC_F1_POS))
#define USB_FFRST1_HOV       USB_FFRST1_HOV
#define USB_FFRST1_HOV_POS   (12U)
#define USB_FFRST1_HOV_LEN   (1U)
#define USB_FFRST1_HOV_MSK   (((1U << USB_FFRST1_HOV_LEN) - 1) << USB_FFRST1_HOV_POS)
#define USB_FFRST1_HOV_UMSK  (~(((1U << USB_FFRST1_HOV_LEN) - 1) << USB_FFRST1_HOV_POS))

/* 0x1B8 : DEV_FIBC2 */
#define USB_DEV_FIBC2_OFFSET (0x1B8)
#define USB_BC_F2            USB_BC_F2
#define USB_BC_F2_POS        (0U)
#define USB_BC_F2_LEN        (11U)
#define USB_BC_F2_MSK        (((1U << USB_BC_F2_LEN) - 1) << USB_BC_F2_POS)
#define USB_BC_F2_UMSK       (~(((1U << USB_BC_F2_LEN) - 1) << USB_BC_F2_POS))
#define USB_FFRST2_HOV       USB_FFRST2_HOV
#define USB_FFRST2_HOV_POS   (12U)
#define USB_FFRST2_HOV_LEN   (1U)
#define USB_FFRST2_HOV_MSK   (((1U << USB_FFRST2_HOV_LEN) - 1) << USB_FFRST2_HOV_POS)
#define USB_FFRST2_HOV_UMSK  (~(((1U << USB_FFRST2_HOV_LEN) - 1) << USB_FFRST2_HOV_POS))

/* 0x1BC : DEV_FIBC3 */
#define USB_DEV_FIBC3_OFFSET (0x1BC)
#define USB_BC_F3            USB_BC_F3
#define USB_BC_F3_POS        (0U)
#define USB_BC_F3_LEN        (11U)
#define USB_BC_F3_MSK        (((1U << USB_BC_F3_LEN) - 1) << USB_BC_F3_POS)
#define USB_BC_F3_UMSK       (~(((1U << USB_BC_F3_LEN) - 1) << USB_BC_F3_POS))
#define USB_FFRST3_HOV       USB_FFRST3_HOV
#define USB_FFRST3_HOV_POS   (12U)
#define USB_FFRST3_HOV_LEN   (1U)
#define USB_FFRST3_HOV_MSK   (((1U << USB_FFRST3_HOV_LEN) - 1) << USB_FFRST3_HOV_POS)
#define USB_FFRST3_HOV_UMSK  (~(((1U << USB_FFRST3_HOV_LEN) - 1) << USB_FFRST3_HOV_POS))

/* 0x1C0 : DMA_TFN */
#define USB_DMA_TFN_OFFSET   (0x1C0)
#define USB_ACC_F0_HOV       USB_ACC_F0_HOV
#define USB_ACC_F0_HOV_POS   (0U)
#define USB_ACC_F0_HOV_LEN   (1U)
#define USB_ACC_F0_HOV_MSK   (((1U << USB_ACC_F0_HOV_LEN) - 1) << USB_ACC_F0_HOV_POS)
#define USB_ACC_F0_HOV_UMSK  (~(((1U << USB_ACC_F0_HOV_LEN) - 1) << USB_ACC_F0_HOV_POS))
#define USB_ACC_F1_HOV       USB_ACC_F1_HOV
#define USB_ACC_F1_HOV_POS   (1U)
#define USB_ACC_F1_HOV_LEN   (1U)
#define USB_ACC_F1_HOV_MSK   (((1U << USB_ACC_F1_HOV_LEN) - 1) << USB_ACC_F1_HOV_POS)
#define USB_ACC_F1_HOV_UMSK  (~(((1U << USB_ACC_F1_HOV_LEN) - 1) << USB_ACC_F1_HOV_POS))
#define USB_ACC_F2_HOV       USB_ACC_F2_HOV
#define USB_ACC_F2_HOV_POS   (2U)
#define USB_ACC_F2_HOV_LEN   (1U)
#define USB_ACC_F2_HOV_MSK   (((1U << USB_ACC_F2_HOV_LEN) - 1) << USB_ACC_F2_HOV_POS)
#define USB_ACC_F2_HOV_UMSK  (~(((1U << USB_ACC_F2_HOV_LEN) - 1) << USB_ACC_F2_HOV_POS))
#define USB_ACC_F3_HOV       USB_ACC_F3_HOV
#define USB_ACC_F3_HOV_POS   (3U)
#define USB_ACC_F3_HOV_LEN   (1U)
#define USB_ACC_F3_HOV_MSK   (((1U << USB_ACC_F3_HOV_LEN) - 1) << USB_ACC_F3_HOV_POS)
#define USB_ACC_F3_HOV_UMSK  (~(((1U << USB_ACC_F3_HOV_LEN) - 1) << USB_ACC_F3_HOV_POS))
#define USB_ACC_CXF_HOV      USB_ACC_CXF_HOV
#define USB_ACC_CXF_HOV_POS  (4U)
#define USB_ACC_CXF_HOV_LEN  (1U)
#define USB_ACC_CXF_HOV_MSK  (((1U << USB_ACC_CXF_HOV_LEN) - 1) << USB_ACC_CXF_HOV_POS)
#define USB_ACC_CXF_HOV_UMSK (~(((1U << USB_ACC_CXF_HOV_LEN) - 1) << USB_ACC_CXF_HOV_POS))
#define USB_ACC_F4_HOV       USB_ACC_F4_HOV
#define USB_ACC_F4_HOV_POS   (5U)
#define USB_ACC_F4_HOV_LEN   (1U)
#define USB_ACC_F4_HOV_MSK   (((1U << USB_ACC_F4_HOV_LEN) - 1) << USB_ACC_F4_HOV_POS)
#define USB_ACC_F4_HOV_UMSK  (~(((1U << USB_ACC_F4_HOV_LEN) - 1) << USB_ACC_F4_HOV_POS))
#define USB_ACC_F5_HOV       USB_ACC_F5_HOV
#define USB_ACC_F5_HOV_POS   (6U)
#define USB_ACC_F5_HOV_LEN   (1U)
#define USB_ACC_F5_HOV_MSK   (((1U << USB_ACC_F5_HOV_LEN) - 1) << USB_ACC_F5_HOV_POS)
#define USB_ACC_F5_HOV_UMSK  (~(((1U << USB_ACC_F5_HOV_LEN) - 1) << USB_ACC_F5_HOV_POS))
#define USB_ACC_F6_HOV       USB_ACC_F6_HOV
#define USB_ACC_F6_HOV_POS   (7U)
#define USB_ACC_F6_HOV_LEN   (1U)
#define USB_ACC_F6_HOV_MSK   (((1U << USB_ACC_F6_HOV_LEN) - 1) << USB_ACC_F6_HOV_POS)
#define USB_ACC_F6_HOV_UMSK  (~(((1U << USB_ACC_F6_HOV_LEN) - 1) << USB_ACC_F6_HOV_POS))
#define USB_ACC_F7_HOV       USB_ACC_F7_HOV
#define USB_ACC_F7_HOV_POS   (8U)
#define USB_ACC_F7_HOV_LEN   (1U)
#define USB_ACC_F7_HOV_MSK   (((1U << USB_ACC_F7_HOV_LEN) - 1) << USB_ACC_F7_HOV_POS)
#define USB_ACC_F7_HOV_UMSK  (~(((1U << USB_ACC_F7_HOV_LEN) - 1) << USB_ACC_F7_HOV_POS))
#define USB_ACC_F8_HOV       USB_ACC_F8_HOV
#define USB_ACC_F8_HOV_POS   (9U)
#define USB_ACC_F8_HOV_LEN   (1U)
#define USB_ACC_F8_HOV_MSK   (((1U << USB_ACC_F8_HOV_LEN) - 1) << USB_ACC_F8_HOV_POS)
#define USB_ACC_F8_HOV_UMSK  (~(((1U << USB_ACC_F8_HOV_LEN) - 1) << USB_ACC_F8_HOV_POS))
#define USB_ACC_F9_HOV       USB_ACC_F9_HOV
#define USB_ACC_F9_HOV_POS   (10U)
#define USB_ACC_F9_HOV_LEN   (1U)
#define USB_ACC_F9_HOV_MSK   (((1U << USB_ACC_F9_HOV_LEN) - 1) << USB_ACC_F9_HOV_POS)
#define USB_ACC_F9_HOV_UMSK  (~(((1U << USB_ACC_F9_HOV_LEN) - 1) << USB_ACC_F9_HOV_POS))
#define USB_ACC_F10_HOV      USB_ACC_F10_HOV
#define USB_ACC_F10_HOV_POS  (11U)
#define USB_ACC_F10_HOV_LEN  (1U)
#define USB_ACC_F10_HOV_MSK  (((1U << USB_ACC_F10_HOV_LEN) - 1) << USB_ACC_F10_HOV_POS)
#define USB_ACC_F10_HOV_UMSK (~(((1U << USB_ACC_F10_HOV_LEN) - 1) << USB_ACC_F10_HOV_POS))
#define USB_ACC_F11_HOV      USB_ACC_F11_HOV
#define USB_ACC_F11_HOV_POS  (12U)
#define USB_ACC_F11_HOV_LEN  (1U)
#define USB_ACC_F11_HOV_MSK  (((1U << USB_ACC_F11_HOV_LEN) - 1) << USB_ACC_F11_HOV_POS)
#define USB_ACC_F11_HOV_UMSK (~(((1U << USB_ACC_F11_HOV_LEN) - 1) << USB_ACC_F11_HOV_POS))
#define USB_ACC_F12_HOV      USB_ACC_F12_HOV
#define USB_ACC_F12_HOV_POS  (13U)
#define USB_ACC_F12_HOV_LEN  (1U)
#define USB_ACC_F12_HOV_MSK  (((1U << USB_ACC_F12_HOV_LEN) - 1) << USB_ACC_F12_HOV_POS)
#define USB_ACC_F12_HOV_UMSK (~(((1U << USB_ACC_F12_HOV_LEN) - 1) << USB_ACC_F12_HOV_POS))
#define USB_ACC_F13_HOV      USB_ACC_F13_HOV
#define USB_ACC_F13_HOV_POS  (14U)
#define USB_ACC_F13_HOV_LEN  (1U)
#define USB_ACC_F13_HOV_MSK  (((1U << USB_ACC_F13_HOV_LEN) - 1) << USB_ACC_F13_HOV_POS)
#define USB_ACC_F13_HOV_UMSK (~(((1U << USB_ACC_F13_HOV_LEN) - 1) << USB_ACC_F13_HOV_POS))
#define USB_ACC_F14_HOV      USB_ACC_F14_HOV
#define USB_ACC_F14_HOV_POS  (15U)
#define USB_ACC_F14_HOV_LEN  (1U)
#define USB_ACC_F14_HOV_MSK  (((1U << USB_ACC_F14_HOV_LEN) - 1) << USB_ACC_F14_HOV_POS)
#define USB_ACC_F14_HOV_UMSK (~(((1U << USB_ACC_F14_HOV_LEN) - 1) << USB_ACC_F14_HOV_POS))
#define USB_ACC_F15_HOV      USB_ACC_F15_HOV
#define USB_ACC_F15_HOV_POS  (16U)
#define USB_ACC_F15_HOV_LEN  (1U)
#define USB_ACC_F15_HOV_MSK  (((1U << USB_ACC_F15_HOV_LEN) - 1) << USB_ACC_F15_HOV_POS)
#define USB_ACC_F15_HOV_UMSK (~(((1U << USB_ACC_F15_HOV_LEN) - 1) << USB_ACC_F15_HOV_POS))

/* 0x1C4 : DMA_CPS0 */
#define USB_DMA_CPS0_OFFSET    (0x1C4)
#define USB_AWCHACHE_HOV       USB_AWCHACHE_HOV
#define USB_AWCHACHE_HOV_POS   (0U)
#define USB_AWCHACHE_HOV_LEN   (4U)
#define USB_AWCHACHE_HOV_MSK   (((1U << USB_AWCHACHE_HOV_LEN) - 1) << USB_AWCHACHE_HOV_POS)
#define USB_AWCHACHE_HOV_UMSK  (~(((1U << USB_AWCHACHE_HOV_LEN) - 1) << USB_AWCHACHE_HOV_POS))
#define USB_AWPORT_HOV         USB_AWPORT_HOV
#define USB_AWPORT_HOV_POS     (4U)
#define USB_AWPORT_HOV_LEN     (3U)
#define USB_AWPORT_HOV_MSK     (((1U << USB_AWPORT_HOV_LEN) - 1) << USB_AWPORT_HOV_POS)
#define USB_AWPORT_HOV_UMSK    (~(((1U << USB_AWPORT_HOV_LEN) - 1) << USB_AWPORT_HOV_POS))
#define USB_AWLOCK_HOV         USB_AWLOCK_HOV
#define USB_AWLOCK_HOV_POS     (7U)
#define USB_AWLOCK_HOV_LEN     (2U)
#define USB_AWLOCK_HOV_MSK     (((1U << USB_AWLOCK_HOV_LEN) - 1) << USB_AWLOCK_HOV_POS)
#define USB_AWLOCK_HOV_UMSK    (~(((1U << USB_AWLOCK_HOV_LEN) - 1) << USB_AWLOCK_HOV_POS))
#define USB_ARCACHE_HOV        USB_ARCACHE_HOV
#define USB_ARCACHE_HOV_POS    (9U)
#define USB_ARCACHE_HOV_LEN    (4U)
#define USB_ARCACHE_HOV_MSK    (((1U << USB_ARCACHE_HOV_LEN) - 1) << USB_ARCACHE_HOV_POS)
#define USB_ARCACHE_HOV_UMSK   (~(((1U << USB_ARCACHE_HOV_LEN) - 1) << USB_ARCACHE_HOV_POS))
#define USB_ARPORT_HOV         USB_ARPORT_HOV
#define USB_ARPORT_HOV_POS     (13U)
#define USB_ARPORT_HOV_LEN     (3U)
#define USB_ARPORT_HOV_MSK     (((1U << USB_ARPORT_HOV_LEN) - 1) << USB_ARPORT_HOV_POS)
#define USB_ARPORT_HOV_UMSK    (~(((1U << USB_ARPORT_HOV_LEN) - 1) << USB_ARPORT_HOV_POS))
#define USB_ARLOCK_HOV         USB_ARLOCK_HOV
#define USB_ARLOCK_HOV_POS     (16U)
#define USB_ARLOCK_HOV_LEN     (2U)
#define USB_ARLOCK_HOV_MSK     (((1U << USB_ARLOCK_HOV_LEN) - 1) << USB_ARLOCK_HOV_POS)
#define USB_ARLOCK_HOV_UMSK    (~(((1U << USB_ARLOCK_HOV_LEN) - 1) << USB_ARLOCK_HOV_POS))
#define USB_BUF_LD_EN_HOV      USB_BUF_LD_EN_HOV
#define USB_BUF_LD_EN_HOV_POS  (18U)
#define USB_BUF_LD_EN_HOV_LEN  (1U)
#define USB_BUF_LD_EN_HOV_MSK  (((1U << USB_BUF_LD_EN_HOV_LEN) - 1) << USB_BUF_LD_EN_HOV_POS)
#define USB_BUF_LD_EN_HOV_UMSK (~(((1U << USB_BUF_LD_EN_HOV_LEN) - 1) << USB_BUF_LD_EN_HOV_POS))
#define USB_DST_WD_HOV         USB_DST_WD_HOV
#define USB_DST_WD_HOV_POS     (19U)
#define USB_DST_WD_HOV_LEN     (1U)
#define USB_DST_WD_HOV_MSK     (((1U << USB_DST_WD_HOV_LEN) - 1) << USB_DST_WD_HOV_POS)
#define USB_DST_WD_HOV_UMSK    (~(((1U << USB_DST_WD_HOV_LEN) - 1) << USB_DST_WD_HOV_POS))

/* 0x1C8 : DMA_CPS1 */
#define USB_DMA_CPS1_OFFSET           (0x1C8)
#define USB_DMA_START_HOV             USB_DMA_START_HOV
#define USB_DMA_START_HOV_POS         (0U)
#define USB_DMA_START_HOV_LEN         (1U)
#define USB_DMA_START_HOV_MSK         (((1U << USB_DMA_START_HOV_LEN) - 1) << USB_DMA_START_HOV_POS)
#define USB_DMA_START_HOV_UMSK        (~(((1U << USB_DMA_START_HOV_LEN) - 1) << USB_DMA_START_HOV_POS))
#define USB_DMA_TYPE_HOV              USB_DMA_TYPE_HOV
#define USB_DMA_TYPE_HOV_POS          (1U)
#define USB_DMA_TYPE_HOV_LEN          (1U)
#define USB_DMA_TYPE_HOV_MSK          (((1U << USB_DMA_TYPE_HOV_LEN) - 1) << USB_DMA_TYPE_HOV_POS)
#define USB_DMA_TYPE_HOV_UMSK         (~(((1U << USB_DMA_TYPE_HOV_LEN) - 1) << USB_DMA_TYPE_HOV_POS))
#define USB_DMA_IO_HOV                USB_DMA_IO_HOV
#define USB_DMA_IO_HOV_POS            (2U)
#define USB_DMA_IO_HOV_LEN            (1U)
#define USB_DMA_IO_HOV_MSK            (((1U << USB_DMA_IO_HOV_LEN) - 1) << USB_DMA_IO_HOV_POS)
#define USB_DMA_IO_HOV_UMSK           (~(((1U << USB_DMA_IO_HOV_LEN) - 1) << USB_DMA_IO_HOV_POS))
#define USB_DMA_ABORT_HOV             USB_DMA_ABORT_HOV
#define USB_DMA_ABORT_HOV_POS         (3U)
#define USB_DMA_ABORT_HOV_LEN         (1U)
#define USB_DMA_ABORT_HOV_MSK         (((1U << USB_DMA_ABORT_HOV_LEN) - 1) << USB_DMA_ABORT_HOV_POS)
#define USB_DMA_ABORT_HOV_UMSK        (~(((1U << USB_DMA_ABORT_HOV_LEN) - 1) << USB_DMA_ABORT_HOV_POS))
#define USB_CLRFIFO_DMAABORT_HOV      USB_CLRFIFO_DMAABORT_HOV
#define USB_CLRFIFO_DMAABORT_HOV_POS  (4U)
#define USB_CLRFIFO_DMAABORT_HOV_LEN  (1U)
#define USB_CLRFIFO_DMAABORT_HOV_MSK  (((1U << USB_CLRFIFO_DMAABORT_HOV_LEN) - 1) << USB_CLRFIFO_DMAABORT_HOV_POS)
#define USB_CLRFIFO_DMAABORT_HOV_UMSK (~(((1U << USB_CLRFIFO_DMAABORT_HOV_LEN) - 1) << USB_CLRFIFO_DMAABORT_HOV_POS))
#define USB_DMA_LEN_HOV               USB_DMA_LEN_HOV
#define USB_DMA_LEN_HOV_POS           (8U)
#define USB_DMA_LEN_HOV_LEN           (17U)
#define USB_DMA_LEN_HOV_MSK           (((1U << USB_DMA_LEN_HOV_LEN) - 1) << USB_DMA_LEN_HOV_POS)
#define USB_DMA_LEN_HOV_UMSK          (~(((1U << USB_DMA_LEN_HOV_LEN) - 1) << USB_DMA_LEN_HOV_POS))
#define USB_R_HPORT_HOV               USB_R_HPORT_HOV
#define USB_R_HPORT_HOV_POS           (25U)
#define USB_R_HPORT_HOV_LEN           (4U)
#define USB_R_HPORT_HOV_MSK           (((1U << USB_R_HPORT_HOV_LEN) - 1) << USB_R_HPORT_HOV_POS)
#define USB_R_HPORT_HOV_UMSK          (~(((1U << USB_R_HPORT_HOV_LEN) - 1) << USB_R_HPORT_HOV_POS))
#define USB_UNDEF_LEN_BURST_HOV       USB_UNDEF_LEN_BURST_HOV
#define USB_UNDEF_LEN_BURST_HOV_POS   (29U)
#define USB_UNDEF_LEN_BURST_HOV_LEN   (1U)
#define USB_UNDEF_LEN_BURST_HOV_MSK   (((1U << USB_UNDEF_LEN_BURST_HOV_LEN) - 1) << USB_UNDEF_LEN_BURST_HOV_POS)
#define USB_UNDEF_LEN_BURST_HOV_UMSK  (~(((1U << USB_UNDEF_LEN_BURST_HOV_LEN) - 1) << USB_UNDEF_LEN_BURST_HOV_POS))
#define USB_L1_WAKEUP                 USB_L1_WAKEUP
#define USB_L1_WAKEUP_POS             (30U)
#define USB_L1_WAKEUP_LEN             (1U)
#define USB_L1_WAKEUP_MSK             (((1U << USB_L1_WAKEUP_LEN) - 1) << USB_L1_WAKEUP_POS)
#define USB_L1_WAKEUP_UMSK            (~(((1U << USB_L1_WAKEUP_LEN) - 1) << USB_L1_WAKEUP_POS))
#define USB_DEVPHY_SUSPEND_HOV        USB_DEVPHY_SUSPEND_HOV
#define USB_DEVPHY_SUSPEND_HOV_POS    (31U)
#define USB_DEVPHY_SUSPEND_HOV_LEN    (1U)
#define USB_DEVPHY_SUSPEND_HOV_MSK    (((1U << USB_DEVPHY_SUSPEND_HOV_LEN) - 1) << USB_DEVPHY_SUSPEND_HOV_POS)
#define USB_DEVPHY_SUSPEND_HOV_UMSK   (~(((1U << USB_DEVPHY_SUSPEND_HOV_LEN) - 1) << USB_DEVPHY_SUSPEND_HOV_POS))

/* 0x1CC : DMA_CPS2 */
#define USB_DMA_CPS2_OFFSET    (0x1CC)
#define USB_DMA_MADDR_HOV      USB_DMA_MADDR_HOV
#define USB_DMA_MADDR_HOV_POS  (0U)
#define USB_DMA_MADDR_HOV_LEN  (32U)
#define USB_DMA_MADDR_HOV_MSK  (((1U << USB_DMA_MADDR_HOV_LEN) - 1) << USB_DMA_MADDR_HOV_POS)
#define USB_DMA_MADDR_HOV_UMSK (~(((1U << USB_DMA_MADDR_HOV_LEN) - 1) << USB_DMA_MADDR_HOV_POS))

/* 0x1D0 : DMA_CPS3 */
#define USB_DMA_CPS3_OFFSET      (0x1D0)
#define USB_SETUP_CMD_RPORT      USB_SETUP_CMD_RPORT
#define USB_SETUP_CMD_RPORT_POS  (0U)
#define USB_SETUP_CMD_RPORT_LEN  (32U)
#define USB_SETUP_CMD_RPORT_MSK  (((1U << USB_SETUP_CMD_RPORT_LEN) - 1) << USB_SETUP_CMD_RPORT_POS)
#define USB_SETUP_CMD_RPORT_UMSK (~(((1U << USB_SETUP_CMD_RPORT_LEN) - 1) << USB_SETUP_CMD_RPORT_POS))

/* 0x1D4 : DMA_CPS4 */
#define USB_DMA_CPS4_OFFSET (0x1D4)

/* 0x1D8 : DEV_FMAP2 */
#define USB_DEV_FMAP2_OFFSET (0x1D8)
#define USB_EPNO_FIFO4       USB_EPNO_FIFO4
#define USB_EPNO_FIFO4_POS   (0U)
#define USB_EPNO_FIFO4_LEN   (4U)
#define USB_EPNO_FIFO4_MSK   (((1U << USB_EPNO_FIFO4_LEN) - 1) << USB_EPNO_FIFO4_POS)
#define USB_EPNO_FIFO4_UMSK  (~(((1U << USB_EPNO_FIFO4_LEN) - 1) << USB_EPNO_FIFO4_POS))
#define USB_DIR_FIFO4        USB_DIR_FIFO4
#define USB_DIR_FIFO4_POS    (4U)
#define USB_DIR_FIFO4_LEN    (2U)
#define USB_DIR_FIFO4_MSK    (((1U << USB_DIR_FIFO4_LEN) - 1) << USB_DIR_FIFO4_POS)
#define USB_DIR_FIFO4_UMSK   (~(((1U << USB_DIR_FIFO4_LEN) - 1) << USB_DIR_FIFO4_POS))
#define USB_EPNO_FIFO5       USB_EPNO_FIFO5
#define USB_EPNO_FIFO5_POS   (8U)
#define USB_EPNO_FIFO5_LEN   (4U)
#define USB_EPNO_FIFO5_MSK   (((1U << USB_EPNO_FIFO5_LEN) - 1) << USB_EPNO_FIFO5_POS)
#define USB_EPNO_FIFO5_UMSK  (~(((1U << USB_EPNO_FIFO5_LEN) - 1) << USB_EPNO_FIFO5_POS))
#define USB_DIR_FIFO5        USB_DIR_FIFO5
#define USB_DIR_FIFO5_POS    (12U)
#define USB_DIR_FIFO5_LEN    (2U)
#define USB_DIR_FIFO5_MSK    (((1U << USB_DIR_FIFO5_LEN) - 1) << USB_DIR_FIFO5_POS)
#define USB_DIR_FIFO5_UMSK   (~(((1U << USB_DIR_FIFO5_LEN) - 1) << USB_DIR_FIFO5_POS))
#define USB_EPNO_FIFO6       USB_EPNO_FIFO6
#define USB_EPNO_FIFO6_POS   (16U)
#define USB_EPNO_FIFO6_LEN   (4U)
#define USB_EPNO_FIFO6_MSK   (((1U << USB_EPNO_FIFO6_LEN) - 1) << USB_EPNO_FIFO6_POS)
#define USB_EPNO_FIFO6_UMSK  (~(((1U << USB_EPNO_FIFO6_LEN) - 1) << USB_EPNO_FIFO6_POS))
#define USB_DIR_FIFO6        USB_DIR_FIFO6
#define USB_DIR_FIFO6_POS    (20U)
#define USB_DIR_FIFO6_LEN    (2U)
#define USB_DIR_FIFO6_MSK    (((1U << USB_DIR_FIFO6_LEN) - 1) << USB_DIR_FIFO6_POS)
#define USB_DIR_FIFO6_UMSK   (~(((1U << USB_DIR_FIFO6_LEN) - 1) << USB_DIR_FIFO6_POS))
#define USB_EPNO_FIFO7       USB_EPNO_FIFO7
#define USB_EPNO_FIFO7_POS   (24U)
#define USB_EPNO_FIFO7_LEN   (4U)
#define USB_EPNO_FIFO7_MSK   (((1U << USB_EPNO_FIFO7_LEN) - 1) << USB_EPNO_FIFO7_POS)
#define USB_EPNO_FIFO7_UMSK  (~(((1U << USB_EPNO_FIFO7_LEN) - 1) << USB_EPNO_FIFO7_POS))
#define USB_DIR_FIFO7        USB_DIR_FIFO7
#define USB_DIR_FIFO7_POS    (28U)
#define USB_DIR_FIFO7_LEN    (2U)
#define USB_DIR_FIFO7_MSK    (((1U << USB_DIR_FIFO7_LEN) - 1) << USB_DIR_FIFO7_POS)
#define USB_DIR_FIFO7_UMSK   (~(((1U << USB_DIR_FIFO7_LEN) - 1) << USB_DIR_FIFO7_POS))

/* 0x1DC : DEV_FCFG2 */
#define USB_DEV_FCFG2_OFFSET (0x1DC)
#define USB_BLK_TYP_F4       USB_BLK_TYP_F4
#define USB_BLK_TYP_F4_POS   (0U)
#define USB_BLK_TYP_F4_LEN   (2U)
#define USB_BLK_TYP_F4_MSK   (((1U << USB_BLK_TYP_F4_LEN) - 1) << USB_BLK_TYP_F4_POS)
#define USB_BLK_TYP_F4_UMSK  (~(((1U << USB_BLK_TYP_F4_LEN) - 1) << USB_BLK_TYP_F4_POS))
#define USB_BLKNO_F4         USB_BLKNO_F4
#define USB_BLKNO_F4_POS     (2U)
#define USB_BLKNO_F4_LEN     (2U)
#define USB_BLKNO_F4_MSK     (((1U << USB_BLKNO_F4_LEN) - 1) << USB_BLKNO_F4_POS)
#define USB_BLKNO_F4_UMSK    (~(((1U << USB_BLKNO_F4_LEN) - 1) << USB_BLKNO_F4_POS))
#define USB_BLKSZ_F4         USB_BLKSZ_F4
#define USB_BLKSZ_F4_POS     (4U)
#define USB_BLKSZ_F4_LEN     (1U)
#define USB_BLKSZ_F4_MSK     (((1U << USB_BLKSZ_F4_LEN) - 1) << USB_BLKSZ_F4_POS)
#define USB_BLKSZ_F4_UMSK    (~(((1U << USB_BLKSZ_F4_LEN) - 1) << USB_BLKSZ_F4_POS))
#define USB_EN_F4            USB_EN_F4
#define USB_EN_F4_POS        (5U)
#define USB_EN_F4_LEN        (1U)
#define USB_EN_F4_MSK        (((1U << USB_EN_F4_LEN) - 1) << USB_EN_F4_POS)
#define USB_EN_F4_UMSK       (~(((1U << USB_EN_F4_LEN) - 1) << USB_EN_F4_POS))
#define USB_BLK_TYP_F5       USB_BLK_TYP_F5
#define USB_BLK_TYP_F5_POS   (8U)
#define USB_BLK_TYP_F5_LEN   (2U)
#define USB_BLK_TYP_F5_MSK   (((1U << USB_BLK_TYP_F5_LEN) - 1) << USB_BLK_TYP_F5_POS)
#define USB_BLK_TYP_F5_UMSK  (~(((1U << USB_BLK_TYP_F5_LEN) - 1) << USB_BLK_TYP_F5_POS))
#define USB_BLKNO_F5         USB_BLKNO_F5
#define USB_BLKNO_F5_POS     (10U)
#define USB_BLKNO_F5_LEN     (2U)
#define USB_BLKNO_F5_MSK     (((1U << USB_BLKNO_F5_LEN) - 1) << USB_BLKNO_F5_POS)
#define USB_BLKNO_F5_UMSK    (~(((1U << USB_BLKNO_F5_LEN) - 1) << USB_BLKNO_F5_POS))
#define USB_BLKSZ_F5         USB_BLKSZ_F5
#define USB_BLKSZ_F5_POS     (12U)
#define USB_BLKSZ_F5_LEN     (1U)
#define USB_BLKSZ_F5_MSK     (((1U << USB_BLKSZ_F5_LEN) - 1) << USB_BLKSZ_F5_POS)
#define USB_BLKSZ_F5_UMSK    (~(((1U << USB_BLKSZ_F5_LEN) - 1) << USB_BLKSZ_F5_POS))
#define USB_EN_F5            USB_EN_F5
#define USB_EN_F5_POS        (13U)
#define USB_EN_F5_LEN        (1U)
#define USB_EN_F5_MSK        (((1U << USB_EN_F5_LEN) - 1) << USB_EN_F5_POS)
#define USB_EN_F5_UMSK       (~(((1U << USB_EN_F5_LEN) - 1) << USB_EN_F5_POS))
#define USB_BLK_TYP_F6       USB_BLK_TYP_F6
#define USB_BLK_TYP_F6_POS   (16U)
#define USB_BLK_TYP_F6_LEN   (2U)
#define USB_BLK_TYP_F6_MSK   (((1U << USB_BLK_TYP_F6_LEN) - 1) << USB_BLK_TYP_F6_POS)
#define USB_BLK_TYP_F6_UMSK  (~(((1U << USB_BLK_TYP_F6_LEN) - 1) << USB_BLK_TYP_F6_POS))
#define USB_BLKNO_F6         USB_BLKNO_F6
#define USB_BLKNO_F6_POS     (18U)
#define USB_BLKNO_F6_LEN     (2U)
#define USB_BLKNO_F6_MSK     (((1U << USB_BLKNO_F6_LEN) - 1) << USB_BLKNO_F6_POS)
#define USB_BLKNO_F6_UMSK    (~(((1U << USB_BLKNO_F6_LEN) - 1) << USB_BLKNO_F6_POS))
#define USB_BLKSZ_F6         USB_BLKSZ_F6
#define USB_BLKSZ_F6_POS     (20U)
#define USB_BLKSZ_F6_LEN     (1U)
#define USB_BLKSZ_F6_MSK     (((1U << USB_BLKSZ_F6_LEN) - 1) << USB_BLKSZ_F6_POS)
#define USB_BLKSZ_F6_UMSK    (~(((1U << USB_BLKSZ_F6_LEN) - 1) << USB_BLKSZ_F6_POS))
#define USB_EN_F6            USB_EN_F6
#define USB_EN_F6_POS        (21U)
#define USB_EN_F6_LEN        (1U)
#define USB_EN_F6_MSK        (((1U << USB_EN_F6_LEN) - 1) << USB_EN_F6_POS)
#define USB_EN_F6_UMSK       (~(((1U << USB_EN_F6_LEN) - 1) << USB_EN_F6_POS))
#define USB_BLK_TYP_F7       USB_BLK_TYP_F7
#define USB_BLK_TYP_F7_POS   (24U)
#define USB_BLK_TYP_F7_LEN   (2U)
#define USB_BLK_TYP_F7_MSK   (((1U << USB_BLK_TYP_F7_LEN) - 1) << USB_BLK_TYP_F7_POS)
#define USB_BLK_TYP_F7_UMSK  (~(((1U << USB_BLK_TYP_F7_LEN) - 1) << USB_BLK_TYP_F7_POS))
#define USB_BLKNO_F7         USB_BLKNO_F7
#define USB_BLKNO_F7_POS     (26U)
#define USB_BLKNO_F7_LEN     (2U)
#define USB_BLKNO_F7_MSK     (((1U << USB_BLKNO_F7_LEN) - 1) << USB_BLKNO_F7_POS)
#define USB_BLKNO_F7_UMSK    (~(((1U << USB_BLKNO_F7_LEN) - 1) << USB_BLKNO_F7_POS))
#define USB_BLKSZ_F7         USB_BLKSZ_F7
#define USB_BLKSZ_F7_POS     (28U)
#define USB_BLKSZ_F7_LEN     (1U)
#define USB_BLKSZ_F7_MSK     (((1U << USB_BLKSZ_F7_LEN) - 1) << USB_BLKSZ_F7_POS)
#define USB_BLKSZ_F7_UMSK    (~(((1U << USB_BLKSZ_F7_LEN) - 1) << USB_BLKSZ_F7_POS))
#define USB_EN_F7            USB_EN_F7
#define USB_EN_F7_POS        (29U)
#define USB_EN_F7_LEN        (1U)
#define USB_EN_F7_MSK        (((1U << USB_EN_F7_LEN) - 1) << USB_EN_F7_POS)
#define USB_EN_F7_UMSK       (~(((1U << USB_EN_F7_LEN) - 1) << USB_EN_F7_POS))

/* 0x1E0 : DEV_FMAP3 */
#define USB_DEV_FMAP3_OFFSET (0x1E0)
#define USB_EPNO_FIFO8       USB_EPNO_FIFO8
#define USB_EPNO_FIFO8_POS   (0U)
#define USB_EPNO_FIFO8_LEN   (4U)
#define USB_EPNO_FIFO8_MSK   (((1U << USB_EPNO_FIFO8_LEN) - 1) << USB_EPNO_FIFO8_POS)
#define USB_EPNO_FIFO8_UMSK  (~(((1U << USB_EPNO_FIFO8_LEN) - 1) << USB_EPNO_FIFO8_POS))
#define USB_DIR_FIFO8        USB_DIR_FIFO8
#define USB_DIR_FIFO8_POS    (4U)
#define USB_DIR_FIFO8_LEN    (2U)
#define USB_DIR_FIFO8_MSK    (((1U << USB_DIR_FIFO8_LEN) - 1) << USB_DIR_FIFO8_POS)
#define USB_DIR_FIFO8_UMSK   (~(((1U << USB_DIR_FIFO8_LEN) - 1) << USB_DIR_FIFO8_POS))
#define USB_EPNO_FIFO9       USB_EPNO_FIFO9
#define USB_EPNO_FIFO9_POS   (8U)
#define USB_EPNO_FIFO9_LEN   (4U)
#define USB_EPNO_FIFO9_MSK   (((1U << USB_EPNO_FIFO9_LEN) - 1) << USB_EPNO_FIFO9_POS)
#define USB_EPNO_FIFO9_UMSK  (~(((1U << USB_EPNO_FIFO9_LEN) - 1) << USB_EPNO_FIFO9_POS))
#define USB_DIR_FIFO9        USB_DIR_FIFO9
#define USB_DIR_FIFO9_POS    (12U)
#define USB_DIR_FIFO9_LEN    (2U)
#define USB_DIR_FIFO9_MSK    (((1U << USB_DIR_FIFO9_LEN) - 1) << USB_DIR_FIFO9_POS)
#define USB_DIR_FIFO9_UMSK   (~(((1U << USB_DIR_FIFO9_LEN) - 1) << USB_DIR_FIFO9_POS))
#define USB_EPNO_FIFO10      USB_EPNO_FIFO10
#define USB_EPNO_FIFO10_POS  (16U)
#define USB_EPNO_FIFO10_LEN  (4U)
#define USB_EPNO_FIFO10_MSK  (((1U << USB_EPNO_FIFO10_LEN) - 1) << USB_EPNO_FIFO10_POS)
#define USB_EPNO_FIFO10_UMSK (~(((1U << USB_EPNO_FIFO10_LEN) - 1) << USB_EPNO_FIFO10_POS))
#define USB_DIR_FIFO10       USB_DIR_FIFO10
#define USB_DIR_FIFO10_POS   (20U)
#define USB_DIR_FIFO10_LEN   (2U)
#define USB_DIR_FIFO10_MSK   (((1U << USB_DIR_FIFO10_LEN) - 1) << USB_DIR_FIFO10_POS)
#define USB_DIR_FIFO10_UMSK  (~(((1U << USB_DIR_FIFO10_LEN) - 1) << USB_DIR_FIFO10_POS))
#define USB_EPNO_FIFO11      USB_EPNO_FIFO11
#define USB_EPNO_FIFO11_POS  (24U)
#define USB_EPNO_FIFO11_LEN  (4U)
#define USB_EPNO_FIFO11_MSK  (((1U << USB_EPNO_FIFO11_LEN) - 1) << USB_EPNO_FIFO11_POS)
#define USB_EPNO_FIFO11_UMSK (~(((1U << USB_EPNO_FIFO11_LEN) - 1) << USB_EPNO_FIFO11_POS))
#define USB_DIR_FIFO11       USB_DIR_FIFO11
#define USB_DIR_FIFO11_POS   (28U)
#define USB_DIR_FIFO11_LEN   (2U)
#define USB_DIR_FIFO11_MSK   (((1U << USB_DIR_FIFO11_LEN) - 1) << USB_DIR_FIFO11_POS)
#define USB_DIR_FIFO11_UMSK  (~(((1U << USB_DIR_FIFO11_LEN) - 1) << USB_DIR_FIFO11_POS))

/* 0x1E4 : DEV_FCFG3 */
#define USB_DEV_FCFG3_OFFSET (0x1E4)
#define USB_BLK_TYP_F8       USB_BLK_TYP_F8
#define USB_BLK_TYP_F8_POS   (0U)
#define USB_BLK_TYP_F8_LEN   (2U)
#define USB_BLK_TYP_F8_MSK   (((1U << USB_BLK_TYP_F8_LEN) - 1) << USB_BLK_TYP_F8_POS)
#define USB_BLK_TYP_F8_UMSK  (~(((1U << USB_BLK_TYP_F8_LEN) - 1) << USB_BLK_TYP_F8_POS))
#define USB_BLKNO_F8         USB_BLKNO_F8
#define USB_BLKNO_F8_POS     (2U)
#define USB_BLKNO_F8_LEN     (2U)
#define USB_BLKNO_F8_MSK     (((1U << USB_BLKNO_F8_LEN) - 1) << USB_BLKNO_F8_POS)
#define USB_BLKNO_F8_UMSK    (~(((1U << USB_BLKNO_F8_LEN) - 1) << USB_BLKNO_F8_POS))
#define USB_BLKSZ_F8         USB_BLKSZ_F8
#define USB_BLKSZ_F8_POS     (4U)
#define USB_BLKSZ_F8_LEN     (1U)
#define USB_BLKSZ_F8_MSK     (((1U << USB_BLKSZ_F8_LEN) - 1) << USB_BLKSZ_F8_POS)
#define USB_BLKSZ_F8_UMSK    (~(((1U << USB_BLKSZ_F8_LEN) - 1) << USB_BLKSZ_F8_POS))
#define USB_EN_F8            USB_EN_F8
#define USB_EN_F8_POS        (5U)
#define USB_EN_F8_LEN        (1U)
#define USB_EN_F8_MSK        (((1U << USB_EN_F8_LEN) - 1) << USB_EN_F8_POS)
#define USB_EN_F8_UMSK       (~(((1U << USB_EN_F8_LEN) - 1) << USB_EN_F8_POS))
#define USB_BLK_TYP_F9       USB_BLK_TYP_F9
#define USB_BLK_TYP_F9_POS   (8U)
#define USB_BLK_TYP_F9_LEN   (2U)
#define USB_BLK_TYP_F9_MSK   (((1U << USB_BLK_TYP_F9_LEN) - 1) << USB_BLK_TYP_F9_POS)
#define USB_BLK_TYP_F9_UMSK  (~(((1U << USB_BLK_TYP_F9_LEN) - 1) << USB_BLK_TYP_F9_POS))
#define USB_BLKNO_F9         USB_BLKNO_F9
#define USB_BLKNO_F9_POS     (10U)
#define USB_BLKNO_F9_LEN     (2U)
#define USB_BLKNO_F9_MSK     (((1U << USB_BLKNO_F9_LEN) - 1) << USB_BLKNO_F9_POS)
#define USB_BLKNO_F9_UMSK    (~(((1U << USB_BLKNO_F9_LEN) - 1) << USB_BLKNO_F9_POS))
#define USB_BLKSZ_F9         USB_BLKSZ_F9
#define USB_BLKSZ_F9_POS     (12U)
#define USB_BLKSZ_F9_LEN     (1U)
#define USB_BLKSZ_F9_MSK     (((1U << USB_BLKSZ_F9_LEN) - 1) << USB_BLKSZ_F9_POS)
#define USB_BLKSZ_F9_UMSK    (~(((1U << USB_BLKSZ_F9_LEN) - 1) << USB_BLKSZ_F9_POS))
#define USB_EN_F9            USB_EN_F9
#define USB_EN_F9_POS        (13U)
#define USB_EN_F9_LEN        (1U)
#define USB_EN_F9_MSK        (((1U << USB_EN_F9_LEN) - 1) << USB_EN_F9_POS)
#define USB_EN_F9_UMSK       (~(((1U << USB_EN_F9_LEN) - 1) << USB_EN_F9_POS))
#define USB_BLK_TYP_F10      USB_BLK_TYP_F10
#define USB_BLK_TYP_F10_POS  (16U)
#define USB_BLK_TYP_F10_LEN  (2U)
#define USB_BLK_TYP_F10_MSK  (((1U << USB_BLK_TYP_F10_LEN) - 1) << USB_BLK_TYP_F10_POS)
#define USB_BLK_TYP_F10_UMSK (~(((1U << USB_BLK_TYP_F10_LEN) - 1) << USB_BLK_TYP_F10_POS))
#define USB_BLKNO_F10        USB_BLKNO_F10
#define USB_BLKNO_F10_POS    (18U)
#define USB_BLKNO_F10_LEN    (2U)
#define USB_BLKNO_F10_MSK    (((1U << USB_BLKNO_F10_LEN) - 1) << USB_BLKNO_F10_POS)
#define USB_BLKNO_F10_UMSK   (~(((1U << USB_BLKNO_F10_LEN) - 1) << USB_BLKNO_F10_POS))
#define USB_BLKSZ_F10        USB_BLKSZ_F10
#define USB_BLKSZ_F10_POS    (20U)
#define USB_BLKSZ_F10_LEN    (1U)
#define USB_BLKSZ_F10_MSK    (((1U << USB_BLKSZ_F10_LEN) - 1) << USB_BLKSZ_F10_POS)
#define USB_BLKSZ_F10_UMSK   (~(((1U << USB_BLKSZ_F10_LEN) - 1) << USB_BLKSZ_F10_POS))
#define USB_EN_F10           USB_EN_F10
#define USB_EN_F10_POS       (21U)
#define USB_EN_F10_LEN       (1U)
#define USB_EN_F10_MSK       (((1U << USB_EN_F10_LEN) - 1) << USB_EN_F10_POS)
#define USB_EN_F10_UMSK      (~(((1U << USB_EN_F10_LEN) - 1) << USB_EN_F10_POS))
#define USB_BLK_TYP_F11      USB_BLK_TYP_F11
#define USB_BLK_TYP_F11_POS  (24U)
#define USB_BLK_TYP_F11_LEN  (2U)
#define USB_BLK_TYP_F11_MSK  (((1U << USB_BLK_TYP_F11_LEN) - 1) << USB_BLK_TYP_F11_POS)
#define USB_BLK_TYP_F11_UMSK (~(((1U << USB_BLK_TYP_F11_LEN) - 1) << USB_BLK_TYP_F11_POS))
#define USB_BLKNO_F11        USB_BLKNO_F11
#define USB_BLKNO_F11_POS    (26U)
#define USB_BLKNO_F11_LEN    (2U)
#define USB_BLKNO_F11_MSK    (((1U << USB_BLKNO_F11_LEN) - 1) << USB_BLKNO_F11_POS)
#define USB_BLKNO_F11_UMSK   (~(((1U << USB_BLKNO_F11_LEN) - 1) << USB_BLKNO_F11_POS))
#define USB_BLKSZ_F11        USB_BLKSZ_F11
#define USB_BLKSZ_F11_POS    (28U)
#define USB_BLKSZ_F11_LEN    (1U)
#define USB_BLKSZ_F11_MSK    (((1U << USB_BLKSZ_F11_LEN) - 1) << USB_BLKSZ_F11_POS)
#define USB_BLKSZ_F11_UMSK   (~(((1U << USB_BLKSZ_F11_LEN) - 1) << USB_BLKSZ_F11_POS))
#define USB_EN_F11           USB_EN_F11
#define USB_EN_F11_POS       (29U)
#define USB_EN_F11_LEN       (1U)
#define USB_EN_F11_MSK       (((1U << USB_EN_F11_LEN) - 1) << USB_EN_F11_POS)
#define USB_EN_F11_UMSK      (~(((1U << USB_EN_F11_LEN) - 1) << USB_EN_F11_POS))

/* 0x1E8 : DEV_FMAP4 */
#define USB_DEV_FMAP4_OFFSET (0x1E8)
#define USB_EPNO_FIFO12      USB_EPNO_FIFO12
#define USB_EPNO_FIFO12_POS  (0U)
#define USB_EPNO_FIFO12_LEN  (4U)
#define USB_EPNO_FIFO12_MSK  (((1U << USB_EPNO_FIFO12_LEN) - 1) << USB_EPNO_FIFO12_POS)
#define USB_EPNO_FIFO12_UMSK (~(((1U << USB_EPNO_FIFO12_LEN) - 1) << USB_EPNO_FIFO12_POS))
#define USB_DIR_FIFO12       USB_DIR_FIFO12
#define USB_DIR_FIFO12_POS   (4U)
#define USB_DIR_FIFO12_LEN   (2U)
#define USB_DIR_FIFO12_MSK   (((1U << USB_DIR_FIFO12_LEN) - 1) << USB_DIR_FIFO12_POS)
#define USB_DIR_FIFO12_UMSK  (~(((1U << USB_DIR_FIFO12_LEN) - 1) << USB_DIR_FIFO12_POS))
#define USB_EPNO_FIFO13      USB_EPNO_FIFO13
#define USB_EPNO_FIFO13_POS  (8U)
#define USB_EPNO_FIFO13_LEN  (4U)
#define USB_EPNO_FIFO13_MSK  (((1U << USB_EPNO_FIFO13_LEN) - 1) << USB_EPNO_FIFO13_POS)
#define USB_EPNO_FIFO13_UMSK (~(((1U << USB_EPNO_FIFO13_LEN) - 1) << USB_EPNO_FIFO13_POS))
#define USB_DIR_FIFO13       USB_DIR_FIFO13
#define USB_DIR_FIFO13_POS   (12U)
#define USB_DIR_FIFO13_LEN   (2U)
#define USB_DIR_FIFO13_MSK   (((1U << USB_DIR_FIFO13_LEN) - 1) << USB_DIR_FIFO13_POS)
#define USB_DIR_FIFO13_UMSK  (~(((1U << USB_DIR_FIFO13_LEN) - 1) << USB_DIR_FIFO13_POS))
#define USB_EPNO_FIFO14      USB_EPNO_FIFO14
#define USB_EPNO_FIFO14_POS  (16U)
#define USB_EPNO_FIFO14_LEN  (4U)
#define USB_EPNO_FIFO14_MSK  (((1U << USB_EPNO_FIFO14_LEN) - 1) << USB_EPNO_FIFO14_POS)
#define USB_EPNO_FIFO14_UMSK (~(((1U << USB_EPNO_FIFO14_LEN) - 1) << USB_EPNO_FIFO14_POS))
#define USB_DIR_FIFO14       USB_DIR_FIFO14
#define USB_DIR_FIFO14_POS   (20U)
#define USB_DIR_FIFO14_LEN   (2U)
#define USB_DIR_FIFO14_MSK   (((1U << USB_DIR_FIFO14_LEN) - 1) << USB_DIR_FIFO14_POS)
#define USB_DIR_FIFO14_UMSK  (~(((1U << USB_DIR_FIFO14_LEN) - 1) << USB_DIR_FIFO14_POS))
#define USB_EPNO_FIFO15      USB_EPNO_FIFO15
#define USB_EPNO_FIFO15_POS  (24U)
#define USB_EPNO_FIFO15_LEN  (4U)
#define USB_EPNO_FIFO15_MSK  (((1U << USB_EPNO_FIFO15_LEN) - 1) << USB_EPNO_FIFO15_POS)
#define USB_EPNO_FIFO15_UMSK (~(((1U << USB_EPNO_FIFO15_LEN) - 1) << USB_EPNO_FIFO15_POS))
#define USB_DIR_FIFO15       USB_DIR_FIFO15
#define USB_DIR_FIFO15_POS   (28U)
#define USB_DIR_FIFO15_LEN   (2U)
#define USB_DIR_FIFO15_MSK   (((1U << USB_DIR_FIFO15_LEN) - 1) << USB_DIR_FIFO15_POS)
#define USB_DIR_FIFO15_UMSK  (~(((1U << USB_DIR_FIFO15_LEN) - 1) << USB_DIR_FIFO15_POS))

/* 0x1EC : DEV_FCFG4 */
#define USB_DEV_FCFG4_OFFSET (0x1EC)
#define USB_BLK_TYP_F12      USB_BLK_TYP_F12
#define USB_BLK_TYP_F12_POS  (0U)
#define USB_BLK_TYP_F12_LEN  (2U)
#define USB_BLK_TYP_F12_MSK  (((1U << USB_BLK_TYP_F12_LEN) - 1) << USB_BLK_TYP_F12_POS)
#define USB_BLK_TYP_F12_UMSK (~(((1U << USB_BLK_TYP_F12_LEN) - 1) << USB_BLK_TYP_F12_POS))
#define USB_BLKNO_F12        USB_BLKNO_F12
#define USB_BLKNO_F12_POS    (2U)
#define USB_BLKNO_F12_LEN    (2U)
#define USB_BLKNO_F12_MSK    (((1U << USB_BLKNO_F12_LEN) - 1) << USB_BLKNO_F12_POS)
#define USB_BLKNO_F12_UMSK   (~(((1U << USB_BLKNO_F12_LEN) - 1) << USB_BLKNO_F12_POS))
#define USB_BLKSZ_F12        USB_BLKSZ_F12
#define USB_BLKSZ_F12_POS    (4U)
#define USB_BLKSZ_F12_LEN    (1U)
#define USB_BLKSZ_F12_MSK    (((1U << USB_BLKSZ_F12_LEN) - 1) << USB_BLKSZ_F12_POS)
#define USB_BLKSZ_F12_UMSK   (~(((1U << USB_BLKSZ_F12_LEN) - 1) << USB_BLKSZ_F12_POS))
#define USB_EN_F12           USB_EN_F12
#define USB_EN_F12_POS       (5U)
#define USB_EN_F12_LEN       (1U)
#define USB_EN_F12_MSK       (((1U << USB_EN_F12_LEN) - 1) << USB_EN_F12_POS)
#define USB_EN_F12_UMSK      (~(((1U << USB_EN_F12_LEN) - 1) << USB_EN_F12_POS))
#define USB_BLK_TYP_F13      USB_BLK_TYP_F13
#define USB_BLK_TYP_F13_POS  (8U)
#define USB_BLK_TYP_F13_LEN  (2U)
#define USB_BLK_TYP_F13_MSK  (((1U << USB_BLK_TYP_F13_LEN) - 1) << USB_BLK_TYP_F13_POS)
#define USB_BLK_TYP_F13_UMSK (~(((1U << USB_BLK_TYP_F13_LEN) - 1) << USB_BLK_TYP_F13_POS))
#define USB_BLKNO_F13        USB_BLKNO_F13
#define USB_BLKNO_F13_POS    (10U)
#define USB_BLKNO_F13_LEN    (2U)
#define USB_BLKNO_F13_MSK    (((1U << USB_BLKNO_F13_LEN) - 1) << USB_BLKNO_F13_POS)
#define USB_BLKNO_F13_UMSK   (~(((1U << USB_BLKNO_F13_LEN) - 1) << USB_BLKNO_F13_POS))
#define USB_BLKSZ_F13        USB_BLKSZ_F13
#define USB_BLKSZ_F13_POS    (12U)
#define USB_BLKSZ_F13_LEN    (1U)
#define USB_BLKSZ_F13_MSK    (((1U << USB_BLKSZ_F13_LEN) - 1) << USB_BLKSZ_F13_POS)
#define USB_BLKSZ_F13_UMSK   (~(((1U << USB_BLKSZ_F13_LEN) - 1) << USB_BLKSZ_F13_POS))
#define USB_EN_F13           USB_EN_F13
#define USB_EN_F13_POS       (13U)
#define USB_EN_F13_LEN       (1U)
#define USB_EN_F13_MSK       (((1U << USB_EN_F13_LEN) - 1) << USB_EN_F13_POS)
#define USB_EN_F13_UMSK      (~(((1U << USB_EN_F13_LEN) - 1) << USB_EN_F13_POS))
#define USB_BLK_TYP_F14      USB_BLK_TYP_F14
#define USB_BLK_TYP_F14_POS  (16U)
#define USB_BLK_TYP_F14_LEN  (2U)
#define USB_BLK_TYP_F14_MSK  (((1U << USB_BLK_TYP_F14_LEN) - 1) << USB_BLK_TYP_F14_POS)
#define USB_BLK_TYP_F14_UMSK (~(((1U << USB_BLK_TYP_F14_LEN) - 1) << USB_BLK_TYP_F14_POS))
#define USB_BLKNO_F14        USB_BLKNO_F14
#define USB_BLKNO_F14_POS    (18U)
#define USB_BLKNO_F14_LEN    (2U)
#define USB_BLKNO_F14_MSK    (((1U << USB_BLKNO_F14_LEN) - 1) << USB_BLKNO_F14_POS)
#define USB_BLKNO_F14_UMSK   (~(((1U << USB_BLKNO_F14_LEN) - 1) << USB_BLKNO_F14_POS))
#define USB_BLKSZ_F14        USB_BLKSZ_F14
#define USB_BLKSZ_F14_POS    (20U)
#define USB_BLKSZ_F14_LEN    (1U)
#define USB_BLKSZ_F14_MSK    (((1U << USB_BLKSZ_F14_LEN) - 1) << USB_BLKSZ_F14_POS)
#define USB_BLKSZ_F14_UMSK   (~(((1U << USB_BLKSZ_F14_LEN) - 1) << USB_BLKSZ_F14_POS))
#define USB_EN_F14           USB_EN_F14
#define USB_EN_F14_POS       (21U)
#define USB_EN_F14_LEN       (1U)
#define USB_EN_F14_MSK       (((1U << USB_EN_F14_LEN) - 1) << USB_EN_F14_POS)
#define USB_EN_F14_UMSK      (~(((1U << USB_EN_F14_LEN) - 1) << USB_EN_F14_POS))
#define USB_BLK_TYP_F15      USB_BLK_TYP_F15
#define USB_BLK_TYP_F15_POS  (24U)
#define USB_BLK_TYP_F15_LEN  (2U)
#define USB_BLK_TYP_F15_MSK  (((1U << USB_BLK_TYP_F15_LEN) - 1) << USB_BLK_TYP_F15_POS)
#define USB_BLK_TYP_F15_UMSK (~(((1U << USB_BLK_TYP_F15_LEN) - 1) << USB_BLK_TYP_F15_POS))
#define USB_BLKNO_F15        USB_BLKNO_F15
#define USB_BLKNO_F15_POS    (26U)
#define USB_BLKNO_F15_LEN    (2U)
#define USB_BLKNO_F15_MSK    (((1U << USB_BLKNO_F15_LEN) - 1) << USB_BLKNO_F15_POS)
#define USB_BLKNO_F15_UMSK   (~(((1U << USB_BLKNO_F15_LEN) - 1) << USB_BLKNO_F15_POS))
#define USB_BLKSZ_F15        USB_BLKSZ_F15
#define USB_BLKSZ_F15_POS    (28U)
#define USB_BLKSZ_F15_LEN    (1U)
#define USB_BLKSZ_F15_MSK    (((1U << USB_BLKSZ_F15_LEN) - 1) << USB_BLKSZ_F15_POS)
#define USB_BLKSZ_F15_UMSK   (~(((1U << USB_BLKSZ_F15_LEN) - 1) << USB_BLKSZ_F15_POS))
#define USB_EN_F15           USB_EN_F15
#define USB_EN_F15_POS       (29U)
#define USB_EN_F15_LEN       (1U)
#define USB_EN_F15_MSK       (((1U << USB_EN_F15_LEN) - 1) << USB_EN_F15_POS)
#define USB_EN_F15_UMSK      (~(((1U << USB_EN_F15_LEN) - 1) << USB_EN_F15_POS))

/* 0x1F0 : DEV_FIBC4 */
#define USB_DEV_FIBC4_OFFSET (0x1F0)
#define USB_BC_F4            USB_BC_F4
#define USB_BC_F4_POS        (0U)
#define USB_BC_F4_LEN        (11U)
#define USB_BC_F4_MSK        (((1U << USB_BC_F4_LEN) - 1) << USB_BC_F4_POS)
#define USB_BC_F4_UMSK       (~(((1U << USB_BC_F4_LEN) - 1) << USB_BC_F4_POS))
#define USB_FFRST4_HOV       USB_FFRST4_HOV
#define USB_FFRST4_HOV_POS   (12U)
#define USB_FFRST4_HOV_LEN   (1U)
#define USB_FFRST4_HOV_MSK   (((1U << USB_FFRST4_HOV_LEN) - 1) << USB_FFRST4_HOV_POS)
#define USB_FFRST4_HOV_UMSK  (~(((1U << USB_FFRST4_HOV_LEN) - 1) << USB_FFRST4_HOV_POS))

/* 0x1F4 : DEV_FIBC5 */
#define USB_DEV_FIBC5_OFFSET (0x1F4)
#define USB_BC_F5            USB_BC_F5
#define USB_BC_F5_POS        (0U)
#define USB_BC_F5_LEN        (11U)
#define USB_BC_F5_MSK        (((1U << USB_BC_F5_LEN) - 1) << USB_BC_F5_POS)
#define USB_BC_F5_UMSK       (~(((1U << USB_BC_F5_LEN) - 1) << USB_BC_F5_POS))
#define USB_FFRST5_HOV       USB_FFRST5_HOV
#define USB_FFRST5_HOV_POS   (12U)
#define USB_FFRST5_HOV_LEN   (1U)
#define USB_FFRST5_HOV_MSK   (((1U << USB_FFRST5_HOV_LEN) - 1) << USB_FFRST5_HOV_POS)
#define USB_FFRST5_HOV_UMSK  (~(((1U << USB_FFRST5_HOV_LEN) - 1) << USB_FFRST5_HOV_POS))

/* 0x1F8 : DEV_FIBC6 */
#define USB_DEV_FIBC6_OFFSET (0x1F8)
#define USB_BC_F6            USB_BC_F6
#define USB_BC_F6_POS        (0U)
#define USB_BC_F6_LEN        (11U)
#define USB_BC_F6_MSK        (((1U << USB_BC_F6_LEN) - 1) << USB_BC_F6_POS)
#define USB_BC_F6_UMSK       (~(((1U << USB_BC_F6_LEN) - 1) << USB_BC_F6_POS))
#define USB_FFRST6_HOV       USB_FFRST6_HOV
#define USB_FFRST6_HOV_POS   (12U)
#define USB_FFRST6_HOV_LEN   (1U)
#define USB_FFRST6_HOV_MSK   (((1U << USB_FFRST6_HOV_LEN) - 1) << USB_FFRST6_HOV_POS)
#define USB_FFRST6_HOV_UMSK  (~(((1U << USB_FFRST6_HOV_LEN) - 1) << USB_FFRST6_HOV_POS))

/* 0x1FC : DEV_FIBC7 */
#define USB_DEV_FIBC7_OFFSET (0x1FC)
#define USB_BC_F7            USB_BC_F7
#define USB_BC_F7_POS        (0U)
#define USB_BC_F7_LEN        (11U)
#define USB_BC_F7_MSK        (((1U << USB_BC_F7_LEN) - 1) << USB_BC_F7_POS)
#define USB_BC_F7_UMSK       (~(((1U << USB_BC_F7_LEN) - 1) << USB_BC_F7_POS))
#define USB_FFRST7_HOV       USB_FFRST7_HOV
#define USB_FFRST7_HOV_POS   (12U)
#define USB_FFRST7_HOV_LEN   (1U)
#define USB_FFRST7_HOV_MSK   (((1U << USB_FFRST7_HOV_LEN) - 1) << USB_FFRST7_HOV_POS)
#define USB_FFRST7_HOV_UMSK  (~(((1U << USB_FFRST7_HOV_LEN) - 1) << USB_FFRST7_HOV_POS))

/* 0x300 : VDMA_CXFPS1 */
#define USB_VDMA_CXFPS1_OFFSET  (0x300)
#define USB_VDMA_START_CXF      USB_VDMA_START_CXF
#define USB_VDMA_START_CXF_POS  (0U)
#define USB_VDMA_START_CXF_LEN  (1U)
#define USB_VDMA_START_CXF_MSK  (((1U << USB_VDMA_START_CXF_LEN) - 1) << USB_VDMA_START_CXF_POS)
#define USB_VDMA_START_CXF_UMSK (~(((1U << USB_VDMA_START_CXF_LEN) - 1) << USB_VDMA_START_CXF_POS))
#define USB_VDMA_TYPE_CXF       USB_VDMA_TYPE_CXF
#define USB_VDMA_TYPE_CXF_POS   (1U)
#define USB_VDMA_TYPE_CXF_LEN   (1U)
#define USB_VDMA_TYPE_CXF_MSK   (((1U << USB_VDMA_TYPE_CXF_LEN) - 1) << USB_VDMA_TYPE_CXF_POS)
#define USB_VDMA_TYPE_CXF_UMSK  (~(((1U << USB_VDMA_TYPE_CXF_LEN) - 1) << USB_VDMA_TYPE_CXF_POS))
#define USB_VDMA_IO_CXF         USB_VDMA_IO_CXF
#define USB_VDMA_IO_CXF_POS     (2U)
#define USB_VDMA_IO_CXF_LEN     (1U)
#define USB_VDMA_IO_CXF_MSK     (((1U << USB_VDMA_IO_CXF_LEN) - 1) << USB_VDMA_IO_CXF_POS)
#define USB_VDMA_IO_CXF_UMSK    (~(((1U << USB_VDMA_IO_CXF_LEN) - 1) << USB_VDMA_IO_CXF_POS))
#define USB_VDMA_LEN_CXF        USB_VDMA_LEN_CXF
#define USB_VDMA_LEN_CXF_POS    (8U)
#define USB_VDMA_LEN_CXF_LEN    (17U)
#define USB_VDMA_LEN_CXF_MSK    (((1U << USB_VDMA_LEN_CXF_LEN) - 1) << USB_VDMA_LEN_CXF_POS)
#define USB_VDMA_LEN_CXF_UMSK   (~(((1U << USB_VDMA_LEN_CXF_LEN) - 1) << USB_VDMA_LEN_CXF_POS))

/* 0x304 : None */
#define USB_VDMA_CXFPS2_OFFSET  (0x304)
#define USB_VDMA_MADDR_CXF      USB_VDMA_MADDR_CXF
#define USB_VDMA_MADDR_CXF_POS  (0U)
#define USB_VDMA_MADDR_CXF_LEN  (32U)
#define USB_VDMA_MADDR_CXF_MSK  (((1U << USB_VDMA_MADDR_CXF_LEN) - 1) << USB_VDMA_MADDR_CXF_POS)
#define USB_VDMA_MADDR_CXF_UMSK (~(((1U << USB_VDMA_MADDR_CXF_LEN) - 1) << USB_VDMA_MADDR_CXF_POS))

/* 0x308 : None */
#define USB_VDMA_F0PS1_OFFSET  (0x308)
#define USB_VDMA_START_F0      USB_VDMA_START_F0
#define USB_VDMA_START_F0_POS  (0U)
#define USB_VDMA_START_F0_LEN  (1U)
#define USB_VDMA_START_F0_MSK  (((1U << USB_VDMA_START_F0_LEN) - 1) << USB_VDMA_START_F0_POS)
#define USB_VDMA_START_F0_UMSK (~(((1U << USB_VDMA_START_F0_LEN) - 1) << USB_VDMA_START_F0_POS))
#define USB_VDMA_TYPE_F0       USB_VDMA_TYPE_F0
#define USB_VDMA_TYPE_F0_POS   (1U)
#define USB_VDMA_TYPE_F0_LEN   (1U)
#define USB_VDMA_TYPE_F0_MSK   (((1U << USB_VDMA_TYPE_F0_LEN) - 1) << USB_VDMA_TYPE_F0_POS)
#define USB_VDMA_TYPE_F0_UMSK  (~(((1U << USB_VDMA_TYPE_F0_LEN) - 1) << USB_VDMA_TYPE_F0_POS))
#define USB_VDMA_IO_F0         USB_VDMA_IO_F0
#define USB_VDMA_IO_F0_POS     (2U)
#define USB_VDMA_IO_F0_LEN     (1U)
#define USB_VDMA_IO_F0_MSK     (((1U << USB_VDMA_IO_F0_LEN) - 1) << USB_VDMA_IO_F0_POS)
#define USB_VDMA_IO_F0_UMSK    (~(((1U << USB_VDMA_IO_F0_LEN) - 1) << USB_VDMA_IO_F0_POS))
#define USB_VDMA_LEN_F0        USB_VDMA_LEN_F0
#define USB_VDMA_LEN_F0_POS    (8U)
#define USB_VDMA_LEN_F0_LEN    (17U)
#define USB_VDMA_LEN_F0_MSK    (((1U << USB_VDMA_LEN_F0_LEN) - 1) << USB_VDMA_LEN_F0_POS)
#define USB_VDMA_LEN_F0_UMSK   (~(((1U << USB_VDMA_LEN_F0_LEN) - 1) << USB_VDMA_LEN_F0_POS))

/* 0x30C : VDMA_F0PS2 */
#define USB_VDMA_F0PS2_OFFSET  (0x30C)
#define USB_VDMA_MADDR_F0      USB_VDMA_MADDR_F0
#define USB_VDMA_MADDR_F0_POS  (0U)
#define USB_VDMA_MADDR_F0_LEN  (32U)
#define USB_VDMA_MADDR_F0_MSK  (((1U << USB_VDMA_MADDR_F0_LEN) - 1) << USB_VDMA_MADDR_F0_POS)
#define USB_VDMA_MADDR_F0_UMSK (~(((1U << USB_VDMA_MADDR_F0_LEN) - 1) << USB_VDMA_MADDR_F0_POS))

/* 0x310 : VDMA_F1PS1 */
#define USB_VDMA_F1PS1_OFFSET  (0x310)
#define USB_VDMA_START_F1      USB_VDMA_START_F1
#define USB_VDMA_START_F1_POS  (0U)
#define USB_VDMA_START_F1_LEN  (1U)
#define USB_VDMA_START_F1_MSK  (((1U << USB_VDMA_START_F1_LEN) - 1) << USB_VDMA_START_F1_POS)
#define USB_VDMA_START_F1_UMSK (~(((1U << USB_VDMA_START_F1_LEN) - 1) << USB_VDMA_START_F1_POS))
#define USB_VDMA_TYPE_F1       USB_VDMA_TYPE_F1
#define USB_VDMA_TYPE_F1_POS   (1U)
#define USB_VDMA_TYPE_F1_LEN   (1U)
#define USB_VDMA_TYPE_F1_MSK   (((1U << USB_VDMA_TYPE_F1_LEN) - 1) << USB_VDMA_TYPE_F1_POS)
#define USB_VDMA_TYPE_F1_UMSK  (~(((1U << USB_VDMA_TYPE_F1_LEN) - 1) << USB_VDMA_TYPE_F1_POS))
#define USB_VDMA_IO_F1         USB_VDMA_IO_F1
#define USB_VDMA_IO_F1_POS     (2U)
#define USB_VDMA_IO_F1_LEN     (1U)
#define USB_VDMA_IO_F1_MSK     (((1U << USB_VDMA_IO_F1_LEN) - 1) << USB_VDMA_IO_F1_POS)
#define USB_VDMA_IO_F1_UMSK    (~(((1U << USB_VDMA_IO_F1_LEN) - 1) << USB_VDMA_IO_F1_POS))
#define USB_VDMA_LEN_F1        USB_VDMA_LEN_F1
#define USB_VDMA_LEN_F1_POS    (8U)
#define USB_VDMA_LEN_F1_LEN    (17U)
#define USB_VDMA_LEN_F1_MSK    (((1U << USB_VDMA_LEN_F1_LEN) - 1) << USB_VDMA_LEN_F1_POS)
#define USB_VDMA_LEN_F1_UMSK   (~(((1U << USB_VDMA_LEN_F1_LEN) - 1) << USB_VDMA_LEN_F1_POS))

/* 0x314 : VDMA_F1PS2 */
#define USB_VDMA_F1PS2_OFFSET  (0x314)
#define USB_VDMA_MADDR_F1      USB_VDMA_MADDR_F1
#define USB_VDMA_MADDR_F1_POS  (0U)
#define USB_VDMA_MADDR_F1_LEN  (32U)
#define USB_VDMA_MADDR_F1_MSK  (((1U << USB_VDMA_MADDR_F1_LEN) - 1) << USB_VDMA_MADDR_F1_POS)
#define USB_VDMA_MADDR_F1_UMSK (~(((1U << USB_VDMA_MADDR_F1_LEN) - 1) << USB_VDMA_MADDR_F1_POS))

/* 0x318 : VDMA_F2PS1 */
#define USB_VDMA_F2PS1_OFFSET  (0x318)
#define USB_VDMA_START_F2      USB_VDMA_START_F2
#define USB_VDMA_START_F2_POS  (0U)
#define USB_VDMA_START_F2_LEN  (1U)
#define USB_VDMA_START_F2_MSK  (((1U << USB_VDMA_START_F2_LEN) - 1) << USB_VDMA_START_F2_POS)
#define USB_VDMA_START_F2_UMSK (~(((1U << USB_VDMA_START_F2_LEN) - 1) << USB_VDMA_START_F2_POS))
#define USB_VDMA_TYPE_F2       USB_VDMA_TYPE_F2
#define USB_VDMA_TYPE_F2_POS   (1U)
#define USB_VDMA_TYPE_F2_LEN   (1U)
#define USB_VDMA_TYPE_F2_MSK   (((1U << USB_VDMA_TYPE_F2_LEN) - 1) << USB_VDMA_TYPE_F2_POS)
#define USB_VDMA_TYPE_F2_UMSK  (~(((1U << USB_VDMA_TYPE_F2_LEN) - 1) << USB_VDMA_TYPE_F2_POS))
#define USB_VDMA_IO_F2         USB_VDMA_IO_F2
#define USB_VDMA_IO_F2_POS     (2U)
#define USB_VDMA_IO_F2_LEN     (1U)
#define USB_VDMA_IO_F2_MSK     (((1U << USB_VDMA_IO_F2_LEN) - 1) << USB_VDMA_IO_F2_POS)
#define USB_VDMA_IO_F2_UMSK    (~(((1U << USB_VDMA_IO_F2_LEN) - 1) << USB_VDMA_IO_F2_POS))
#define USB_VDMA_LEN_F2        USB_VDMA_LEN_F2
#define USB_VDMA_LEN_F2_POS    (8U)
#define USB_VDMA_LEN_F2_LEN    (17U)
#define USB_VDMA_LEN_F2_MSK    (((1U << USB_VDMA_LEN_F2_LEN) - 1) << USB_VDMA_LEN_F2_POS)
#define USB_VDMA_LEN_F2_UMSK   (~(((1U << USB_VDMA_LEN_F2_LEN) - 1) << USB_VDMA_LEN_F2_POS))

/* 0x31C : VDMA_F2PS2 */
#define USB_VDMA_F2PS2_OFFSET  (0x31C)
#define USB_VDMA_MADDR_F2      USB_VDMA_MADDR_F2
#define USB_VDMA_MADDR_F2_POS  (0U)
#define USB_VDMA_MADDR_F2_LEN  (32U)
#define USB_VDMA_MADDR_F2_MSK  (((1U << USB_VDMA_MADDR_F2_LEN) - 1) << USB_VDMA_MADDR_F2_POS)
#define USB_VDMA_MADDR_F2_UMSK (~(((1U << USB_VDMA_MADDR_F2_LEN) - 1) << USB_VDMA_MADDR_F2_POS))

/* 0x320 : VDMA_F3PS1 */
#define USB_VDMA_F3PS1_OFFSET  (0x320)
#define USB_VDMA_START_F3      USB_VDMA_START_F3
#define USB_VDMA_START_F3_POS  (0U)
#define USB_VDMA_START_F3_LEN  (1U)
#define USB_VDMA_START_F3_MSK  (((1U << USB_VDMA_START_F3_LEN) - 1) << USB_VDMA_START_F3_POS)
#define USB_VDMA_START_F3_UMSK (~(((1U << USB_VDMA_START_F3_LEN) - 1) << USB_VDMA_START_F3_POS))
#define USB_VDMA_TYPE_F3       USB_VDMA_TYPE_F3
#define USB_VDMA_TYPE_F3_POS   (1U)
#define USB_VDMA_TYPE_F3_LEN   (1U)
#define USB_VDMA_TYPE_F3_MSK   (((1U << USB_VDMA_TYPE_F3_LEN) - 1) << USB_VDMA_TYPE_F3_POS)
#define USB_VDMA_TYPE_F3_UMSK  (~(((1U << USB_VDMA_TYPE_F3_LEN) - 1) << USB_VDMA_TYPE_F3_POS))
#define USB_VDMA_IO_F3         USB_VDMA_IO_F3
#define USB_VDMA_IO_F3_POS     (2U)
#define USB_VDMA_IO_F3_LEN     (1U)
#define USB_VDMA_IO_F3_MSK     (((1U << USB_VDMA_IO_F3_LEN) - 1) << USB_VDMA_IO_F3_POS)
#define USB_VDMA_IO_F3_UMSK    (~(((1U << USB_VDMA_IO_F3_LEN) - 1) << USB_VDMA_IO_F3_POS))
#define USB_VDMA_LEN_F3        USB_VDMA_LEN_F3
#define USB_VDMA_LEN_F3_POS    (8U)
#define USB_VDMA_LEN_F3_LEN    (17U)
#define USB_VDMA_LEN_F3_MSK    (((1U << USB_VDMA_LEN_F3_LEN) - 1) << USB_VDMA_LEN_F3_POS)
#define USB_VDMA_LEN_F3_UMSK   (~(((1U << USB_VDMA_LEN_F3_LEN) - 1) << USB_VDMA_LEN_F3_POS))

/* 0x324 : VDMA_F3PS2 */
#define USB_VDMA_F3PS2_OFFSET  (0x324)
#define USB_VDMA_MADDR_F3      USB_VDMA_MADDR_F3
#define USB_VDMA_MADDR_F3_POS  (0U)
#define USB_VDMA_MADDR_F3_LEN  (32U)
#define USB_VDMA_MADDR_F3_MSK  (((1U << USB_VDMA_MADDR_F3_LEN) - 1) << USB_VDMA_MADDR_F3_POS)
#define USB_VDMA_MADDR_F3_UMSK (~(((1U << USB_VDMA_MADDR_F3_LEN) - 1) << USB_VDMA_MADDR_F3_POS))

/* 0x328 : DEV_ISG3 */
#define USB_DEV_ISG3_OFFSET     (0x328)
#define USB_VDMA_CMPLT_CXF      USB_VDMA_CMPLT_CXF
#define USB_VDMA_CMPLT_CXF_POS  (0U)
#define USB_VDMA_CMPLT_CXF_LEN  (1U)
#define USB_VDMA_CMPLT_CXF_MSK  (((1U << USB_VDMA_CMPLT_CXF_LEN) - 1) << USB_VDMA_CMPLT_CXF_POS)
#define USB_VDMA_CMPLT_CXF_UMSK (~(((1U << USB_VDMA_CMPLT_CXF_LEN) - 1) << USB_VDMA_CMPLT_CXF_POS))
#define USB_VDMA_CMPLT_F0       USB_VDMA_CMPLT_F0
#define USB_VDMA_CMPLT_F0_POS   (1U)
#define USB_VDMA_CMPLT_F0_LEN   (1U)
#define USB_VDMA_CMPLT_F0_MSK   (((1U << USB_VDMA_CMPLT_F0_LEN) - 1) << USB_VDMA_CMPLT_F0_POS)
#define USB_VDMA_CMPLT_F0_UMSK  (~(((1U << USB_VDMA_CMPLT_F0_LEN) - 1) << USB_VDMA_CMPLT_F0_POS))
#define USB_VDMA_CMPLT_F1       USB_VDMA_CMPLT_F1
#define USB_VDMA_CMPLT_F1_POS   (2U)
#define USB_VDMA_CMPLT_F1_LEN   (1U)
#define USB_VDMA_CMPLT_F1_MSK   (((1U << USB_VDMA_CMPLT_F1_LEN) - 1) << USB_VDMA_CMPLT_F1_POS)
#define USB_VDMA_CMPLT_F1_UMSK  (~(((1U << USB_VDMA_CMPLT_F1_LEN) - 1) << USB_VDMA_CMPLT_F1_POS))
#define USB_VDMA_CMPLT_F2       USB_VDMA_CMPLT_F2
#define USB_VDMA_CMPLT_F2_POS   (3U)
#define USB_VDMA_CMPLT_F2_LEN   (1U)
#define USB_VDMA_CMPLT_F2_MSK   (((1U << USB_VDMA_CMPLT_F2_LEN) - 1) << USB_VDMA_CMPLT_F2_POS)
#define USB_VDMA_CMPLT_F2_UMSK  (~(((1U << USB_VDMA_CMPLT_F2_LEN) - 1) << USB_VDMA_CMPLT_F2_POS))
#define USB_VDMA_CMPLT_F3       USB_VDMA_CMPLT_F3
#define USB_VDMA_CMPLT_F3_POS   (4U)
#define USB_VDMA_CMPLT_F3_LEN   (1U)
#define USB_VDMA_CMPLT_F3_MSK   (((1U << USB_VDMA_CMPLT_F3_LEN) - 1) << USB_VDMA_CMPLT_F3_POS)
#define USB_VDMA_CMPLT_F3_UMSK  (~(((1U << USB_VDMA_CMPLT_F3_LEN) - 1) << USB_VDMA_CMPLT_F3_POS))
#define USB_VDMA_CMPLT_F4       USB_VDMA_CMPLT_F4
#define USB_VDMA_CMPLT_F4_POS   (5U)
#define USB_VDMA_CMPLT_F4_LEN   (1U)
#define USB_VDMA_CMPLT_F4_MSK   (((1U << USB_VDMA_CMPLT_F4_LEN) - 1) << USB_VDMA_CMPLT_F4_POS)
#define USB_VDMA_CMPLT_F4_UMSK  (~(((1U << USB_VDMA_CMPLT_F4_LEN) - 1) << USB_VDMA_CMPLT_F4_POS))
#define USB_VDMA_CMPLT_F5       USB_VDMA_CMPLT_F5
#define USB_VDMA_CMPLT_F5_POS   (6U)
#define USB_VDMA_CMPLT_F5_LEN   (1U)
#define USB_VDMA_CMPLT_F5_MSK   (((1U << USB_VDMA_CMPLT_F5_LEN) - 1) << USB_VDMA_CMPLT_F5_POS)
#define USB_VDMA_CMPLT_F5_UMSK  (~(((1U << USB_VDMA_CMPLT_F5_LEN) - 1) << USB_VDMA_CMPLT_F5_POS))
#define USB_VDMA_CMPLT_F6       USB_VDMA_CMPLT_F6
#define USB_VDMA_CMPLT_F6_POS   (7U)
#define USB_VDMA_CMPLT_F6_LEN   (1U)
#define USB_VDMA_CMPLT_F6_MSK   (((1U << USB_VDMA_CMPLT_F6_LEN) - 1) << USB_VDMA_CMPLT_F6_POS)
#define USB_VDMA_CMPLT_F6_UMSK  (~(((1U << USB_VDMA_CMPLT_F6_LEN) - 1) << USB_VDMA_CMPLT_F6_POS))
#define USB_VDMA_CMPLT_F7       USB_VDMA_CMPLT_F7
#define USB_VDMA_CMPLT_F7_POS   (8U)
#define USB_VDMA_CMPLT_F7_LEN   (1U)
#define USB_VDMA_CMPLT_F7_MSK   (((1U << USB_VDMA_CMPLT_F7_LEN) - 1) << USB_VDMA_CMPLT_F7_POS)
#define USB_VDMA_CMPLT_F7_UMSK  (~(((1U << USB_VDMA_CMPLT_F7_LEN) - 1) << USB_VDMA_CMPLT_F7_POS))
#define USB_VDMA_CMPLT_F8       USB_VDMA_CMPLT_F8
#define USB_VDMA_CMPLT_F8_POS   (9U)
#define USB_VDMA_CMPLT_F8_LEN   (1U)
#define USB_VDMA_CMPLT_F8_MSK   (((1U << USB_VDMA_CMPLT_F8_LEN) - 1) << USB_VDMA_CMPLT_F8_POS)
#define USB_VDMA_CMPLT_F8_UMSK  (~(((1U << USB_VDMA_CMPLT_F8_LEN) - 1) << USB_VDMA_CMPLT_F8_POS))
#define USB_VDMA_CMPLT_F9       USB_VDMA_CMPLT_F9
#define USB_VDMA_CMPLT_F9_POS   (10U)
#define USB_VDMA_CMPLT_F9_LEN   (1U)
#define USB_VDMA_CMPLT_F9_MSK   (((1U << USB_VDMA_CMPLT_F9_LEN) - 1) << USB_VDMA_CMPLT_F9_POS)
#define USB_VDMA_CMPLT_F9_UMSK  (~(((1U << USB_VDMA_CMPLT_F9_LEN) - 1) << USB_VDMA_CMPLT_F9_POS))
#define USB_VDMA_CMPLT_F10      USB_VDMA_CMPLT_F10
#define USB_VDMA_CMPLT_F10_POS  (11U)
#define USB_VDMA_CMPLT_F10_LEN  (1U)
#define USB_VDMA_CMPLT_F10_MSK  (((1U << USB_VDMA_CMPLT_F10_LEN) - 1) << USB_VDMA_CMPLT_F10_POS)
#define USB_VDMA_CMPLT_F10_UMSK (~(((1U << USB_VDMA_CMPLT_F10_LEN) - 1) << USB_VDMA_CMPLT_F10_POS))
#define USB_VDMA_CMPLT_F11      USB_VDMA_CMPLT_F11
#define USB_VDMA_CMPLT_F11_POS  (12U)
#define USB_VDMA_CMPLT_F11_LEN  (1U)
#define USB_VDMA_CMPLT_F11_MSK  (((1U << USB_VDMA_CMPLT_F11_LEN) - 1) << USB_VDMA_CMPLT_F11_POS)
#define USB_VDMA_CMPLT_F11_UMSK (~(((1U << USB_VDMA_CMPLT_F11_LEN) - 1) << USB_VDMA_CMPLT_F11_POS))
#define USB_VDMA_CMPLT_F12      USB_VDMA_CMPLT_F12
#define USB_VDMA_CMPLT_F12_POS  (13U)
#define USB_VDMA_CMPLT_F12_LEN  (1U)
#define USB_VDMA_CMPLT_F12_MSK  (((1U << USB_VDMA_CMPLT_F12_LEN) - 1) << USB_VDMA_CMPLT_F12_POS)
#define USB_VDMA_CMPLT_F12_UMSK (~(((1U << USB_VDMA_CMPLT_F12_LEN) - 1) << USB_VDMA_CMPLT_F12_POS))
#define USB_VDMA_CMPLT_F13      USB_VDMA_CMPLT_F13
#define USB_VDMA_CMPLT_F13_POS  (14U)
#define USB_VDMA_CMPLT_F13_LEN  (1U)
#define USB_VDMA_CMPLT_F13_MSK  (((1U << USB_VDMA_CMPLT_F13_LEN) - 1) << USB_VDMA_CMPLT_F13_POS)
#define USB_VDMA_CMPLT_F13_UMSK (~(((1U << USB_VDMA_CMPLT_F13_LEN) - 1) << USB_VDMA_CMPLT_F13_POS))
#define USB_VDMA_CMPLT_F14      USB_VDMA_CMPLT_F14
#define USB_VDMA_CMPLT_F14_POS  (15U)
#define USB_VDMA_CMPLT_F14_LEN  (1U)
#define USB_VDMA_CMPLT_F14_MSK  (((1U << USB_VDMA_CMPLT_F14_LEN) - 1) << USB_VDMA_CMPLT_F14_POS)
#define USB_VDMA_CMPLT_F14_UMSK (~(((1U << USB_VDMA_CMPLT_F14_LEN) - 1) << USB_VDMA_CMPLT_F14_POS))
#define USB_VDMA_ERROR_CXF      USB_VDMA_ERROR_CXF
#define USB_VDMA_ERROR_CXF_POS  (16U)
#define USB_VDMA_ERROR_CXF_LEN  (1U)
#define USB_VDMA_ERROR_CXF_MSK  (((1U << USB_VDMA_ERROR_CXF_LEN) - 1) << USB_VDMA_ERROR_CXF_POS)
#define USB_VDMA_ERROR_CXF_UMSK (~(((1U << USB_VDMA_ERROR_CXF_LEN) - 1) << USB_VDMA_ERROR_CXF_POS))
#define USB_VDMA_ERROR_F0       USB_VDMA_ERROR_F0
#define USB_VDMA_ERROR_F0_POS   (17U)
#define USB_VDMA_ERROR_F0_LEN   (1U)
#define USB_VDMA_ERROR_F0_MSK   (((1U << USB_VDMA_ERROR_F0_LEN) - 1) << USB_VDMA_ERROR_F0_POS)
#define USB_VDMA_ERROR_F0_UMSK  (~(((1U << USB_VDMA_ERROR_F0_LEN) - 1) << USB_VDMA_ERROR_F0_POS))
#define USB_VDMA_ERROR_F1       USB_VDMA_ERROR_F1
#define USB_VDMA_ERROR_F1_POS   (18U)
#define USB_VDMA_ERROR_F1_LEN   (1U)
#define USB_VDMA_ERROR_F1_MSK   (((1U << USB_VDMA_ERROR_F1_LEN) - 1) << USB_VDMA_ERROR_F1_POS)
#define USB_VDMA_ERROR_F1_UMSK  (~(((1U << USB_VDMA_ERROR_F1_LEN) - 1) << USB_VDMA_ERROR_F1_POS))
#define USB_VDMA_ERROR_F2       USB_VDMA_ERROR_F2
#define USB_VDMA_ERROR_F2_POS   (19U)
#define USB_VDMA_ERROR_F2_LEN   (1U)
#define USB_VDMA_ERROR_F2_MSK   (((1U << USB_VDMA_ERROR_F2_LEN) - 1) << USB_VDMA_ERROR_F2_POS)
#define USB_VDMA_ERROR_F2_UMSK  (~(((1U << USB_VDMA_ERROR_F2_LEN) - 1) << USB_VDMA_ERROR_F2_POS))
#define USB_VDMA_ERROR_F3       USB_VDMA_ERROR_F3
#define USB_VDMA_ERROR_F3_POS   (20U)
#define USB_VDMA_ERROR_F3_LEN   (1U)
#define USB_VDMA_ERROR_F3_MSK   (((1U << USB_VDMA_ERROR_F3_LEN) - 1) << USB_VDMA_ERROR_F3_POS)
#define USB_VDMA_ERROR_F3_UMSK  (~(((1U << USB_VDMA_ERROR_F3_LEN) - 1) << USB_VDMA_ERROR_F3_POS))
#define USB_VDMA_ERROR_F4       USB_VDMA_ERROR_F4
#define USB_VDMA_ERROR_F4_POS   (21U)
#define USB_VDMA_ERROR_F4_LEN   (1U)
#define USB_VDMA_ERROR_F4_MSK   (((1U << USB_VDMA_ERROR_F4_LEN) - 1) << USB_VDMA_ERROR_F4_POS)
#define USB_VDMA_ERROR_F4_UMSK  (~(((1U << USB_VDMA_ERROR_F4_LEN) - 1) << USB_VDMA_ERROR_F4_POS))
#define USB_VDMA_ERROR_F5       USB_VDMA_ERROR_F5
#define USB_VDMA_ERROR_F5_POS   (22U)
#define USB_VDMA_ERROR_F5_LEN   (1U)
#define USB_VDMA_ERROR_F5_MSK   (((1U << USB_VDMA_ERROR_F5_LEN) - 1) << USB_VDMA_ERROR_F5_POS)
#define USB_VDMA_ERROR_F5_UMSK  (~(((1U << USB_VDMA_ERROR_F5_LEN) - 1) << USB_VDMA_ERROR_F5_POS))
#define USB_VDMA_ERROR_F6       USB_VDMA_ERROR_F6
#define USB_VDMA_ERROR_F6_POS   (23U)
#define USB_VDMA_ERROR_F6_LEN   (1U)
#define USB_VDMA_ERROR_F6_MSK   (((1U << USB_VDMA_ERROR_F6_LEN) - 1) << USB_VDMA_ERROR_F6_POS)
#define USB_VDMA_ERROR_F6_UMSK  (~(((1U << USB_VDMA_ERROR_F6_LEN) - 1) << USB_VDMA_ERROR_F6_POS))
#define USB_VDMA_ERROR_F7       USB_VDMA_ERROR_F7
#define USB_VDMA_ERROR_F7_POS   (24U)
#define USB_VDMA_ERROR_F7_LEN   (1U)
#define USB_VDMA_ERROR_F7_MSK   (((1U << USB_VDMA_ERROR_F7_LEN) - 1) << USB_VDMA_ERROR_F7_POS)
#define USB_VDMA_ERROR_F7_UMSK  (~(((1U << USB_VDMA_ERROR_F7_LEN) - 1) << USB_VDMA_ERROR_F7_POS))
#define USB_VDMA_ERROR_F8       USB_VDMA_ERROR_F8
#define USB_VDMA_ERROR_F8_POS   (25U)
#define USB_VDMA_ERROR_F8_LEN   (1U)
#define USB_VDMA_ERROR_F8_MSK   (((1U << USB_VDMA_ERROR_F8_LEN) - 1) << USB_VDMA_ERROR_F8_POS)
#define USB_VDMA_ERROR_F8_UMSK  (~(((1U << USB_VDMA_ERROR_F8_LEN) - 1) << USB_VDMA_ERROR_F8_POS))
#define USB_VDMA_ERROR_F9       USB_VDMA_ERROR_F9
#define USB_VDMA_ERROR_F9_POS   (26U)
#define USB_VDMA_ERROR_F9_LEN   (1U)
#define USB_VDMA_ERROR_F9_MSK   (((1U << USB_VDMA_ERROR_F9_LEN) - 1) << USB_VDMA_ERROR_F9_POS)
#define USB_VDMA_ERROR_F9_UMSK  (~(((1U << USB_VDMA_ERROR_F9_LEN) - 1) << USB_VDMA_ERROR_F9_POS))
#define USB_VDMA_ERROR_F10      USB_VDMA_ERROR_F10
#define USB_VDMA_ERROR_F10_POS  (27U)
#define USB_VDMA_ERROR_F10_LEN  (1U)
#define USB_VDMA_ERROR_F10_MSK  (((1U << USB_VDMA_ERROR_F10_LEN) - 1) << USB_VDMA_ERROR_F10_POS)
#define USB_VDMA_ERROR_F10_UMSK (~(((1U << USB_VDMA_ERROR_F10_LEN) - 1) << USB_VDMA_ERROR_F10_POS))
#define USB_VDMA_ERROR_F11      USB_VDMA_ERROR_F11
#define USB_VDMA_ERROR_F11_POS  (28U)
#define USB_VDMA_ERROR_F11_LEN  (1U)
#define USB_VDMA_ERROR_F11_MSK  (((1U << USB_VDMA_ERROR_F11_LEN) - 1) << USB_VDMA_ERROR_F11_POS)
#define USB_VDMA_ERROR_F11_UMSK (~(((1U << USB_VDMA_ERROR_F11_LEN) - 1) << USB_VDMA_ERROR_F11_POS))
#define USB_VDMA_ERROR_F12      USB_VDMA_ERROR_F12
#define USB_VDMA_ERROR_F12_POS  (29U)
#define USB_VDMA_ERROR_F12_LEN  (1U)
#define USB_VDMA_ERROR_F12_MSK  (((1U << USB_VDMA_ERROR_F12_LEN) - 1) << USB_VDMA_ERROR_F12_POS)
#define USB_VDMA_ERROR_F12_UMSK (~(((1U << USB_VDMA_ERROR_F12_LEN) - 1) << USB_VDMA_ERROR_F12_POS))
#define USB_VDMA_ERROR_F13      USB_VDMA_ERROR_F13
#define USB_VDMA_ERROR_F13_POS  (30U)
#define USB_VDMA_ERROR_F13_LEN  (1U)
#define USB_VDMA_ERROR_F13_MSK  (((1U << USB_VDMA_ERROR_F13_LEN) - 1) << USB_VDMA_ERROR_F13_POS)
#define USB_VDMA_ERROR_F13_UMSK (~(((1U << USB_VDMA_ERROR_F13_LEN) - 1) << USB_VDMA_ERROR_F13_POS))
#define USB_VDMA_ERROR_F14      USB_VDMA_ERROR_F14
#define USB_VDMA_ERROR_F14_POS  (31U)
#define USB_VDMA_ERROR_F14_LEN  (1U)
#define USB_VDMA_ERROR_F14_MSK  (((1U << USB_VDMA_ERROR_F14_LEN) - 1) << USB_VDMA_ERROR_F14_POS)
#define USB_VDMA_ERROR_F14_UMSK (~(((1U << USB_VDMA_ERROR_F14_LEN) - 1) << USB_VDMA_ERROR_F14_POS))

/* 0x32C : DEV_MISG3 */
#define USB_DEV_MISG3_OFFSET     (0x32C)
#define USB_MVDMA_CMPLT_CXF      USB_MVDMA_CMPLT_CXF
#define USB_MVDMA_CMPLT_CXF_POS  (0U)
#define USB_MVDMA_CMPLT_CXF_LEN  (1U)
#define USB_MVDMA_CMPLT_CXF_MSK  (((1U << USB_MVDMA_CMPLT_CXF_LEN) - 1) << USB_MVDMA_CMPLT_CXF_POS)
#define USB_MVDMA_CMPLT_CXF_UMSK (~(((1U << USB_MVDMA_CMPLT_CXF_LEN) - 1) << USB_MVDMA_CMPLT_CXF_POS))
#define USB_MVDMA_CMPLT_F0       USB_MVDMA_CMPLT_F0
#define USB_MVDMA_CMPLT_F0_POS   (1U)
#define USB_MVDMA_CMPLT_F0_LEN   (1U)
#define USB_MVDMA_CMPLT_F0_MSK   (((1U << USB_MVDMA_CMPLT_F0_LEN) - 1) << USB_MVDMA_CMPLT_F0_POS)
#define USB_MVDMA_CMPLT_F0_UMSK  (~(((1U << USB_MVDMA_CMPLT_F0_LEN) - 1) << USB_MVDMA_CMPLT_F0_POS))
#define USB_MVDMA_CMPLT_F1       USB_MVDMA_CMPLT_F1
#define USB_MVDMA_CMPLT_F1_POS   (2U)
#define USB_MVDMA_CMPLT_F1_LEN   (1U)
#define USB_MVDMA_CMPLT_F1_MSK   (((1U << USB_MVDMA_CMPLT_F1_LEN) - 1) << USB_MVDMA_CMPLT_F1_POS)
#define USB_MVDMA_CMPLT_F1_UMSK  (~(((1U << USB_MVDMA_CMPLT_F1_LEN) - 1) << USB_MVDMA_CMPLT_F1_POS))
#define USB_MVDMA_CMPLT_F2       USB_MVDMA_CMPLT_F2
#define USB_MVDMA_CMPLT_F2_POS   (3U)
#define USB_MVDMA_CMPLT_F2_LEN   (1U)
#define USB_MVDMA_CMPLT_F2_MSK   (((1U << USB_MVDMA_CMPLT_F2_LEN) - 1) << USB_MVDMA_CMPLT_F2_POS)
#define USB_MVDMA_CMPLT_F2_UMSK  (~(((1U << USB_MVDMA_CMPLT_F2_LEN) - 1) << USB_MVDMA_CMPLT_F2_POS))
#define USB_MVDMA_CMPLT_F3       USB_MVDMA_CMPLT_F3
#define USB_MVDMA_CMPLT_F3_POS   (4U)
#define USB_MVDMA_CMPLT_F3_LEN   (1U)
#define USB_MVDMA_CMPLT_F3_MSK   (((1U << USB_MVDMA_CMPLT_F3_LEN) - 1) << USB_MVDMA_CMPLT_F3_POS)
#define USB_MVDMA_CMPLT_F3_UMSK  (~(((1U << USB_MVDMA_CMPLT_F3_LEN) - 1) << USB_MVDMA_CMPLT_F3_POS))
#define USB_MVDMA_CMPLT_F4       USB_MVDMA_CMPLT_F4
#define USB_MVDMA_CMPLT_F4_POS   (5U)
#define USB_MVDMA_CMPLT_F4_LEN   (1U)
#define USB_MVDMA_CMPLT_F4_MSK   (((1U << USB_MVDMA_CMPLT_F4_LEN) - 1) << USB_MVDMA_CMPLT_F4_POS)
#define USB_MVDMA_CMPLT_F4_UMSK  (~(((1U << USB_MVDMA_CMPLT_F4_LEN) - 1) << USB_MVDMA_CMPLT_F4_POS))
#define USB_MVDMA_CMPLT_F5       USB_MVDMA_CMPLT_F5
#define USB_MVDMA_CMPLT_F5_POS   (6U)
#define USB_MVDMA_CMPLT_F5_LEN   (1U)
#define USB_MVDMA_CMPLT_F5_MSK   (((1U << USB_MVDMA_CMPLT_F5_LEN) - 1) << USB_MVDMA_CMPLT_F5_POS)
#define USB_MVDMA_CMPLT_F5_UMSK  (~(((1U << USB_MVDMA_CMPLT_F5_LEN) - 1) << USB_MVDMA_CMPLT_F5_POS))
#define USB_MVDMA_CMPLT_F6       USB_MVDMA_CMPLT_F6
#define USB_MVDMA_CMPLT_F6_POS   (7U)
#define USB_MVDMA_CMPLT_F6_LEN   (1U)
#define USB_MVDMA_CMPLT_F6_MSK   (((1U << USB_MVDMA_CMPLT_F6_LEN) - 1) << USB_MVDMA_CMPLT_F6_POS)
#define USB_MVDMA_CMPLT_F6_UMSK  (~(((1U << USB_MVDMA_CMPLT_F6_LEN) - 1) << USB_MVDMA_CMPLT_F6_POS))
#define USB_MVDMA_CMPLT_F7       USB_MVDMA_CMPLT_F7
#define USB_MVDMA_CMPLT_F7_POS   (8U)
#define USB_MVDMA_CMPLT_F7_LEN   (1U)
#define USB_MVDMA_CMPLT_F7_MSK   (((1U << USB_MVDMA_CMPLT_F7_LEN) - 1) << USB_MVDMA_CMPLT_F7_POS)
#define USB_MVDMA_CMPLT_F7_UMSK  (~(((1U << USB_MVDMA_CMPLT_F7_LEN) - 1) << USB_MVDMA_CMPLT_F7_POS))
#define USB_MVDMA_CMPLT_F8       USB_MVDMA_CMPLT_F8
#define USB_MVDMA_CMPLT_F8_POS   (9U)
#define USB_MVDMA_CMPLT_F8_LEN   (1U)
#define USB_MVDMA_CMPLT_F8_MSK   (((1U << USB_MVDMA_CMPLT_F8_LEN) - 1) << USB_MVDMA_CMPLT_F8_POS)
#define USB_MVDMA_CMPLT_F8_UMSK  (~(((1U << USB_MVDMA_CMPLT_F8_LEN) - 1) << USB_MVDMA_CMPLT_F8_POS))
#define USB_MVDMA_CMPLT_F9       USB_MVDMA_CMPLT_F9
#define USB_MVDMA_CMPLT_F9_POS   (10U)
#define USB_MVDMA_CMPLT_F9_LEN   (1U)
#define USB_MVDMA_CMPLT_F9_MSK   (((1U << USB_MVDMA_CMPLT_F9_LEN) - 1) << USB_MVDMA_CMPLT_F9_POS)
#define USB_MVDMA_CMPLT_F9_UMSK  (~(((1U << USB_MVDMA_CMPLT_F9_LEN) - 1) << USB_MVDMA_CMPLT_F9_POS))
#define USB_MVDMA_CMPLT_F10      USB_MVDMA_CMPLT_F10
#define USB_MVDMA_CMPLT_F10_POS  (11U)
#define USB_MVDMA_CMPLT_F10_LEN  (1U)
#define USB_MVDMA_CMPLT_F10_MSK  (((1U << USB_MVDMA_CMPLT_F10_LEN) - 1) << USB_MVDMA_CMPLT_F10_POS)
#define USB_MVDMA_CMPLT_F10_UMSK (~(((1U << USB_MVDMA_CMPLT_F10_LEN) - 1) << USB_MVDMA_CMPLT_F10_POS))
#define USB_MVDMA_CMPLT_F11      USB_MVDMA_CMPLT_F11
#define USB_MVDMA_CMPLT_F11_POS  (12U)
#define USB_MVDMA_CMPLT_F11_LEN  (1U)
#define USB_MVDMA_CMPLT_F11_MSK  (((1U << USB_MVDMA_CMPLT_F11_LEN) - 1) << USB_MVDMA_CMPLT_F11_POS)
#define USB_MVDMA_CMPLT_F11_UMSK (~(((1U << USB_MVDMA_CMPLT_F11_LEN) - 1) << USB_MVDMA_CMPLT_F11_POS))
#define USB_MVDMA_CMPLT_F12      USB_MVDMA_CMPLT_F12
#define USB_MVDMA_CMPLT_F12_POS  (13U)
#define USB_MVDMA_CMPLT_F12_LEN  (1U)
#define USB_MVDMA_CMPLT_F12_MSK  (((1U << USB_MVDMA_CMPLT_F12_LEN) - 1) << USB_MVDMA_CMPLT_F12_POS)
#define USB_MVDMA_CMPLT_F12_UMSK (~(((1U << USB_MVDMA_CMPLT_F12_LEN) - 1) << USB_MVDMA_CMPLT_F12_POS))
#define USB_MVDMA_CMPLT_F13      USB_MVDMA_CMPLT_F13
#define USB_MVDMA_CMPLT_F13_POS  (14U)
#define USB_MVDMA_CMPLT_F13_LEN  (1U)
#define USB_MVDMA_CMPLT_F13_MSK  (((1U << USB_MVDMA_CMPLT_F13_LEN) - 1) << USB_MVDMA_CMPLT_F13_POS)
#define USB_MVDMA_CMPLT_F13_UMSK (~(((1U << USB_MVDMA_CMPLT_F13_LEN) - 1) << USB_MVDMA_CMPLT_F13_POS))
#define USB_MVDMA_CMPLT_F14      USB_MVDMA_CMPLT_F14
#define USB_MVDMA_CMPLT_F14_POS  (15U)
#define USB_MVDMA_CMPLT_F14_LEN  (1U)
#define USB_MVDMA_CMPLT_F14_MSK  (((1U << USB_MVDMA_CMPLT_F14_LEN) - 1) << USB_MVDMA_CMPLT_F14_POS)
#define USB_MVDMA_CMPLT_F14_UMSK (~(((1U << USB_MVDMA_CMPLT_F14_LEN) - 1) << USB_MVDMA_CMPLT_F14_POS))
#define USB_MVDMA_ERROR_CXF      USB_MVDMA_ERROR_CXF
#define USB_MVDMA_ERROR_CXF_POS  (16U)
#define USB_MVDMA_ERROR_CXF_LEN  (1U)
#define USB_MVDMA_ERROR_CXF_MSK  (((1U << USB_MVDMA_ERROR_CXF_LEN) - 1) << USB_MVDMA_ERROR_CXF_POS)
#define USB_MVDMA_ERROR_CXF_UMSK (~(((1U << USB_MVDMA_ERROR_CXF_LEN) - 1) << USB_MVDMA_ERROR_CXF_POS))
#define USB_MVDMA_ERROR_F0       USB_MVDMA_ERROR_F0
#define USB_MVDMA_ERROR_F0_POS   (17U)
#define USB_MVDMA_ERROR_F0_LEN   (1U)
#define USB_MVDMA_ERROR_F0_MSK   (((1U << USB_MVDMA_ERROR_F0_LEN) - 1) << USB_MVDMA_ERROR_F0_POS)
#define USB_MVDMA_ERROR_F0_UMSK  (~(((1U << USB_MVDMA_ERROR_F0_LEN) - 1) << USB_MVDMA_ERROR_F0_POS))
#define USB_MVDMA_ERROR_F1       USB_MVDMA_ERROR_F1
#define USB_MVDMA_ERROR_F1_POS   (18U)
#define USB_MVDMA_ERROR_F1_LEN   (1U)
#define USB_MVDMA_ERROR_F1_MSK   (((1U << USB_MVDMA_ERROR_F1_LEN) - 1) << USB_MVDMA_ERROR_F1_POS)
#define USB_MVDMA_ERROR_F1_UMSK  (~(((1U << USB_MVDMA_ERROR_F1_LEN) - 1) << USB_MVDMA_ERROR_F1_POS))
#define USB_MVDMA_ERROR_F2       USB_MVDMA_ERROR_F2
#define USB_MVDMA_ERROR_F2_POS   (19U)
#define USB_MVDMA_ERROR_F2_LEN   (1U)
#define USB_MVDMA_ERROR_F2_MSK   (((1U << USB_MVDMA_ERROR_F2_LEN) - 1) << USB_MVDMA_ERROR_F2_POS)
#define USB_MVDMA_ERROR_F2_UMSK  (~(((1U << USB_MVDMA_ERROR_F2_LEN) - 1) << USB_MVDMA_ERROR_F2_POS))
#define USB_MVDMA_ERROR_F3       USB_MVDMA_ERROR_F3
#define USB_MVDMA_ERROR_F3_POS   (20U)
#define USB_MVDMA_ERROR_F3_LEN   (1U)
#define USB_MVDMA_ERROR_F3_MSK   (((1U << USB_MVDMA_ERROR_F3_LEN) - 1) << USB_MVDMA_ERROR_F3_POS)
#define USB_MVDMA_ERROR_F3_UMSK  (~(((1U << USB_MVDMA_ERROR_F3_LEN) - 1) << USB_MVDMA_ERROR_F3_POS))
#define USB_MVDMA_ERROR_F4       USB_MVDMA_ERROR_F4
#define USB_MVDMA_ERROR_F4_POS   (21U)
#define USB_MVDMA_ERROR_F4_LEN   (1U)
#define USB_MVDMA_ERROR_F4_MSK   (((1U << USB_MVDMA_ERROR_F4_LEN) - 1) << USB_MVDMA_ERROR_F4_POS)
#define USB_MVDMA_ERROR_F4_UMSK  (~(((1U << USB_MVDMA_ERROR_F4_LEN) - 1) << USB_MVDMA_ERROR_F4_POS))
#define USB_MVDMA_ERROR_F5       USB_MVDMA_ERROR_F5
#define USB_MVDMA_ERROR_F5_POS   (22U)
#define USB_MVDMA_ERROR_F5_LEN   (1U)
#define USB_MVDMA_ERROR_F5_MSK   (((1U << USB_MVDMA_ERROR_F5_LEN) - 1) << USB_MVDMA_ERROR_F5_POS)
#define USB_MVDMA_ERROR_F5_UMSK  (~(((1U << USB_MVDMA_ERROR_F5_LEN) - 1) << USB_MVDMA_ERROR_F5_POS))
#define USB_MVDMA_ERROR_F6       USB_MVDMA_ERROR_F6
#define USB_MVDMA_ERROR_F6_POS   (23U)
#define USB_MVDMA_ERROR_F6_LEN   (1U)
#define USB_MVDMA_ERROR_F6_MSK   (((1U << USB_MVDMA_ERROR_F6_LEN) - 1) << USB_MVDMA_ERROR_F6_POS)
#define USB_MVDMA_ERROR_F6_UMSK  (~(((1U << USB_MVDMA_ERROR_F6_LEN) - 1) << USB_MVDMA_ERROR_F6_POS))
#define USB_MVDMA_ERROR_F7       USB_MVDMA_ERROR_F7
#define USB_MVDMA_ERROR_F7_POS   (24U)
#define USB_MVDMA_ERROR_F7_LEN   (1U)
#define USB_MVDMA_ERROR_F7_MSK   (((1U << USB_MVDMA_ERROR_F7_LEN) - 1) << USB_MVDMA_ERROR_F7_POS)
#define USB_MVDMA_ERROR_F7_UMSK  (~(((1U << USB_MVDMA_ERROR_F7_LEN) - 1) << USB_MVDMA_ERROR_F7_POS))
#define USB_MVDMA_ERROR_F8       USB_MVDMA_ERROR_F8
#define USB_MVDMA_ERROR_F8_POS   (25U)
#define USB_MVDMA_ERROR_F8_LEN   (1U)
#define USB_MVDMA_ERROR_F8_MSK   (((1U << USB_MVDMA_ERROR_F8_LEN) - 1) << USB_MVDMA_ERROR_F8_POS)
#define USB_MVDMA_ERROR_F8_UMSK  (~(((1U << USB_MVDMA_ERROR_F8_LEN) - 1) << USB_MVDMA_ERROR_F8_POS))
#define USB_MVDMA_ERROR_F9       USB_MVDMA_ERROR_F9
#define USB_MVDMA_ERROR_F9_POS   (26U)
#define USB_MVDMA_ERROR_F9_LEN   (1U)
#define USB_MVDMA_ERROR_F9_MSK   (((1U << USB_MVDMA_ERROR_F9_LEN) - 1) << USB_MVDMA_ERROR_F9_POS)
#define USB_MVDMA_ERROR_F9_UMSK  (~(((1U << USB_MVDMA_ERROR_F9_LEN) - 1) << USB_MVDMA_ERROR_F9_POS))
#define USB_MVDMA_ERROR_F10      USB_MVDMA_ERROR_F10
#define USB_MVDMA_ERROR_F10_POS  (27U)
#define USB_MVDMA_ERROR_F10_LEN  (1U)
#define USB_MVDMA_ERROR_F10_MSK  (((1U << USB_MVDMA_ERROR_F10_LEN) - 1) << USB_MVDMA_ERROR_F10_POS)
#define USB_MVDMA_ERROR_F10_UMSK (~(((1U << USB_MVDMA_ERROR_F10_LEN) - 1) << USB_MVDMA_ERROR_F10_POS))
#define USB_MVDMA_ERROR_F11      USB_MVDMA_ERROR_F11
#define USB_MVDMA_ERROR_F11_POS  (28U)
#define USB_MVDMA_ERROR_F11_LEN  (1U)
#define USB_MVDMA_ERROR_F11_MSK  (((1U << USB_MVDMA_ERROR_F11_LEN) - 1) << USB_MVDMA_ERROR_F11_POS)
#define USB_MVDMA_ERROR_F11_UMSK (~(((1U << USB_MVDMA_ERROR_F11_LEN) - 1) << USB_MVDMA_ERROR_F11_POS))
#define USB_MVDMA_ERROR_F12      USB_MVDMA_ERROR_F12
#define USB_MVDMA_ERROR_F12_POS  (29U)
#define USB_MVDMA_ERROR_F12_LEN  (1U)
#define USB_MVDMA_ERROR_F12_MSK  (((1U << USB_MVDMA_ERROR_F12_LEN) - 1) << USB_MVDMA_ERROR_F12_POS)
#define USB_MVDMA_ERROR_F12_UMSK (~(((1U << USB_MVDMA_ERROR_F12_LEN) - 1) << USB_MVDMA_ERROR_F12_POS))
#define USB_MVDMA_ERROR_F13      USB_MVDMA_ERROR_F13
#define USB_MVDMA_ERROR_F13_POS  (30U)
#define USB_MVDMA_ERROR_F13_LEN  (1U)
#define USB_MVDMA_ERROR_F13_MSK  (((1U << USB_MVDMA_ERROR_F13_LEN) - 1) << USB_MVDMA_ERROR_F13_POS)
#define USB_MVDMA_ERROR_F13_UMSK (~(((1U << USB_MVDMA_ERROR_F13_LEN) - 1) << USB_MVDMA_ERROR_F13_POS))
#define USB_MVDMA_ERROR_F14      USB_MVDMA_ERROR_F14
#define USB_MVDMA_ERROR_F14_POS  (31U)
#define USB_MVDMA_ERROR_F14_LEN  (1U)
#define USB_MVDMA_ERROR_F14_MSK  (((1U << USB_MVDMA_ERROR_F14_LEN) - 1) << USB_MVDMA_ERROR_F14_POS)
#define USB_MVDMA_ERROR_F14_UMSK (~(((1U << USB_MVDMA_ERROR_F14_LEN) - 1) << USB_MVDMA_ERROR_F14_POS))

/* 0x330 : VDMA_CTRL */
#define USB_VDMA_CTRL_OFFSET (0x330)
#define USB_VDMA_EN          USB_VDMA_EN
#define USB_VDMA_EN_POS      (0U)
#define USB_VDMA_EN_LEN      (1U)
#define USB_VDMA_EN_MSK      (((1U << USB_VDMA_EN_LEN) - 1) << USB_VDMA_EN_POS)
#define USB_VDMA_EN_UMSK     (~(((1U << USB_VDMA_EN_LEN) - 1) << USB_VDMA_EN_POS))

/* 0x334 : LPM_CAP */
#define USB_LPM_CAP_OFFSET     (0x334)
#define USB_LPM_WAKEUP_EN      USB_LPM_WAKEUP_EN
#define USB_LPM_WAKEUP_EN_POS  (0U)
#define USB_LPM_WAKEUP_EN_LEN  (1U)
#define USB_LPM_WAKEUP_EN_MSK  (((1U << USB_LPM_WAKEUP_EN_LEN) - 1) << USB_LPM_WAKEUP_EN_POS)
#define USB_LPM_WAKEUP_EN_UMSK (~(((1U << USB_LPM_WAKEUP_EN_LEN) - 1) << USB_LPM_WAKEUP_EN_POS))

/* 0x338 : DEV_ISG4 */
#define USB_DEV_ISG4_OFFSET     (0x338)
#define USB_L1_INT              USB_L1_INT
#define USB_L1_INT_POS          (0U)
#define USB_L1_INT_LEN          (1U)
#define USB_L1_INT_MSK          (((1U << USB_L1_INT_LEN) - 1) << USB_L1_INT_POS)
#define USB_L1_INT_UMSK         (~(((1U << USB_L1_INT_LEN) - 1) << USB_L1_INT_POS))
#define USB_VDMA_CMPLT_F15      USB_VDMA_CMPLT_F15
#define USB_VDMA_CMPLT_F15_POS  (16U)
#define USB_VDMA_CMPLT_F15_LEN  (1U)
#define USB_VDMA_CMPLT_F15_MSK  (((1U << USB_VDMA_CMPLT_F15_LEN) - 1) << USB_VDMA_CMPLT_F15_POS)
#define USB_VDMA_CMPLT_F15_UMSK (~(((1U << USB_VDMA_CMPLT_F15_LEN) - 1) << USB_VDMA_CMPLT_F15_POS))
#define USB_VDMA_ERROR_F15      USB_VDMA_ERROR_F15
#define USB_VDMA_ERROR_F15_POS  (24U)
#define USB_VDMA_ERROR_F15_LEN  (1U)
#define USB_VDMA_ERROR_F15_MSK  (((1U << USB_VDMA_ERROR_F15_LEN) - 1) << USB_VDMA_ERROR_F15_POS)
#define USB_VDMA_ERROR_F15_UMSK (~(((1U << USB_VDMA_ERROR_F15_LEN) - 1) << USB_VDMA_ERROR_F15_POS))

/* 0x33C : DEV_MISG4 */
#define USB_DEV_MISG4_OFFSET     (0x33C)
#define USB_ML1_INT              USB_ML1_INT
#define USB_ML1_INT_POS          (0U)
#define USB_ML1_INT_LEN          (1U)
#define USB_ML1_INT_MSK          (((1U << USB_ML1_INT_LEN) - 1) << USB_ML1_INT_POS)
#define USB_ML1_INT_UMSK         (~(((1U << USB_ML1_INT_LEN) - 1) << USB_ML1_INT_POS))
#define USB_MVDMA_CMPLT_F15      USB_MVDMA_CMPLT_F15
#define USB_MVDMA_CMPLT_F15_POS  (16U)
#define USB_MVDMA_CMPLT_F15_LEN  (1U)
#define USB_MVDMA_CMPLT_F15_MSK  (((1U << USB_MVDMA_CMPLT_F15_LEN) - 1) << USB_MVDMA_CMPLT_F15_POS)
#define USB_MVDMA_CMPLT_F15_UMSK (~(((1U << USB_MVDMA_CMPLT_F15_LEN) - 1) << USB_MVDMA_CMPLT_F15_POS))
#define USB_MVDMA_ERROR_F15      USB_MVDMA_ERROR_F15
#define USB_MVDMA_ERROR_F15_POS  (24U)
#define USB_MVDMA_ERROR_F15_LEN  (1U)
#define USB_MVDMA_ERROR_F15_MSK  (((1U << USB_MVDMA_ERROR_F15_LEN) - 1) << USB_MVDMA_ERROR_F15_POS)
#define USB_MVDMA_ERROR_F15_UMSK (~(((1U << USB_MVDMA_ERROR_F15_LEN) - 1) << USB_MVDMA_ERROR_F15_POS))

/* 0x350 : VDMA_FnPS1 */
#define USB_VDMA_FNPS1_OFFSET  (0x350)
#define USB_VDMA_START_FN      USB_VDMA_START_FN
#define USB_VDMA_START_FN_POS  (0U)
#define USB_VDMA_START_FN_LEN  (1U)
#define USB_VDMA_START_FN_MSK  (((1U << USB_VDMA_START_FN_LEN) - 1) << USB_VDMA_START_FN_POS)
#define USB_VDMA_START_FN_UMSK (~(((1U << USB_VDMA_START_FN_LEN) - 1) << USB_VDMA_START_FN_POS))
#define USB_VDMA_TYPE_FN       USB_VDMA_TYPE_FN
#define USB_VDMA_TYPE_FN_POS   (1U)
#define USB_VDMA_TYPE_FN_LEN   (1U)
#define USB_VDMA_TYPE_FN_MSK   (((1U << USB_VDMA_TYPE_FN_LEN) - 1) << USB_VDMA_TYPE_FN_POS)
#define USB_VDMA_TYPE_FN_UMSK  (~(((1U << USB_VDMA_TYPE_FN_LEN) - 1) << USB_VDMA_TYPE_FN_POS))
#define USB_VDMA_IO_FN         USB_VDMA_IO_FN
#define USB_VDMA_IO_FN_POS     (2U)
#define USB_VDMA_IO_FN_LEN     (1U)
#define USB_VDMA_IO_FN_MSK     (((1U << USB_VDMA_IO_FN_LEN) - 1) << USB_VDMA_IO_FN_POS)
#define USB_VDMA_IO_FN_UMSK    (~(((1U << USB_VDMA_IO_FN_LEN) - 1) << USB_VDMA_IO_FN_POS))
#define USB_VDMA_LEN_FN        USB_VDMA_LEN_FN
#define USB_VDMA_LEN_FN_POS    (8U)
#define USB_VDMA_LEN_FN_LEN    (17U)
#define USB_VDMA_LEN_FN_MSK    (((1U << USB_VDMA_LEN_FN_LEN) - 1) << USB_VDMA_LEN_FN_POS)
#define USB_VDMA_LEN_FN_UMSK   (~(((1U << USB_VDMA_LEN_FN_LEN) - 1) << USB_VDMA_LEN_FN_POS))

/* 0x354 : VDMA_FnPS2 */
#define USB_VDMA_FNPS2_OFFSET  (0x354)
#define USB_VDMA_MADDR_FN      USB_VDMA_MADDR_FN
#define USB_VDMA_MADDR_FN_POS  (0U)
#define USB_VDMA_MADDR_FN_LEN  (32U)
#define USB_VDMA_MADDR_FN_MSK  (((1U << USB_VDMA_MADDR_FN_LEN) - 1) << USB_VDMA_MADDR_FN_POS)
#define USB_VDMA_MADDR_FN_UMSK (~(((1U << USB_VDMA_MADDR_FN_LEN) - 1) << USB_VDMA_MADDR_FN_POS))

struct usb_reg {
    /* 0x000 : HCCAP */
    union {
        struct
        {
            uint32_t CAPLENGTH     : 8;  /* [ 7: 0],       None,        0x0 */
            uint32_t reserved_8_15 : 8;  /* [15: 8],       rsvd,        0x0 */
            uint32_t HCIVERSION    : 16; /* [31:16],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } HCCAP;

    /* 0x004 : HCSPARAMS */
    union {
        struct
        {
            uint32_t N_PORTS       : 4;  /* [ 3: 0],       None,        0x0 */
            uint32_t reserved_4_31 : 28; /* [31: 4],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } HCSPARAMS;

    /* 0x008 : HCCPARAMS */
    union {
        struct
        {
            uint32_t reserved_0        : 1;  /* [    0],       rsvd,        0x0 */
            uint32_t PROG_FR_LIST_FLAG : 1;  /* [    1],       None,        0x0 */
            uint32_t ASYN_SCH_PARK_CAP : 1;  /* [    2],       None,        0x0 */
            uint32_t reserved_3_31     : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } HCCPARAMS;

    /* 0xc  reserved */
    uint8_t RESERVED0xc[4];

    /* 0x010 : USBCMD */
    union {
        struct
        {
            uint32_t RS             : 1; /* [    0],       None,        0x0 */
            uint32_t HC_RESET       : 1; /* [    1],       None,        0x0 */
            uint32_t FRL_SIZE       : 2; /* [ 3: 2],       None,        0x0 */
            uint32_t PSCH_EN        : 1; /* [    4],       None,        0x0 */
            uint32_t ASCH_EN        : 1; /* [    5],       None,        0x0 */
            uint32_t INT_OAAD       : 1; /* [    6],       None,        0x0 */
            uint32_t reserved_7     : 1; /* [    7],       rsvd,        0x0 */
            uint32_t ASYN_PK_CNT    : 2; /* [ 9: 8],       None,        0x0 */
            uint32_t reserved_10    : 1; /* [   10],       rsvd,        0x0 */
            uint32_t ASYN_PK_EN     : 1; /* [   11],       None,        0x0 */
            uint32_t reserved_12_15 : 4; /* [15:12],       rsvd,        0x0 */
            uint32_t INT_THRC       : 8; /* [23:16],       None,        0x0 */
            uint32_t reserved_24_31 : 8; /* [31:24],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } USBCMD;

    /* 0x014 : USBSTS */
    union {
        struct
        {
            uint32_t USB_INT        : 1;  /* [    0],       None,        0x0 */
            uint32_t USBERR_INT     : 1;  /* [    1],       None,        0x0 */
            uint32_t PO_CHG_DET     : 1;  /* [    2],       None,        0x0 */
            uint32_t FRL_ROL        : 1;  /* [    3],       None,        0x0 */
            uint32_t H_SYSERR       : 1;  /* [    4],       None,        0x0 */
            uint32_t INT_OAA        : 1;  /* [    5],       None,        0x0 */
            uint32_t reserved_6_11  : 6;  /* [11: 6],       rsvd,        0x0 */
            uint32_t HCHalted       : 1;  /* [   12],       None,        0x0 */
            uint32_t Reclamation    : 1;  /* [   13],       None,        0x0 */
            uint32_t PSCH_STS       : 1;  /* [   14],       None,        0x0 */
            uint32_t ASCH_STS       : 1;  /* [   15],       None,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } USBSTS;

    /* 0x018 : USBINTR */
    union {
        struct
        {
            uint32_t USB_INT_EN    : 1;  /* [    0],       None,        0x0 */
            uint32_t USBERR_INT_EN : 1;  /* [    1],       None,        0x0 */
            uint32_t PO_CHG_INT_EN : 1;  /* [    2],       None,        0x0 */
            uint32_t FRL_ROL_EN    : 1;  /* [    3],       None,        0x0 */
            uint32_t H_SYSERR_EN   : 1;  /* [    4],       None,        0x0 */
            uint32_t INT_OAA_EN    : 1;  /* [    5],       None,        0x0 */
            uint32_t reserved_6_31 : 26; /* [31: 6],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } USBINTR;

    /* 0x01C : FRINDEX */
    union {
        struct
        {
            uint32_t FRINDEX        : 14; /* [13: 0],       None,        0x0 */
            uint32_t reserved_14_31 : 18; /* [31:14],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } FRINDEX;

    /* 0x20  reserved */
    uint8_t RESERVED0x20[4];

    /* 0x024 : PERIODICLISTBASE */
    union {
        struct
        {
            uint32_t reserved_0_11 : 12; /* [11: 0],       rsvd,        0x0 */
            uint32_t PERI_BASADR   : 20; /* [31:12],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } PERIODICLISTBASE;

    /* 0x028 : ASYNCLISTADDR */
    union {
        struct
        {
            uint32_t reserved_0_4 : 5;  /* [ 4: 0],       rsvd,        0x0 */
            uint32_t Async_ladr   : 27; /* [31: 5],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } ASYNCLISTADDR;

    /* 0x2c  reserved */
    uint8_t RESERVED0x2c[4];

    /* 0x030 : PORTSC */
    union {
        struct
        {
            uint32_t CONN_STS       : 1;  /* [    0],       None,        0x0 */
            uint32_t CONN_CHG       : 1;  /* [    1],       None,        0x0 */
            uint32_t PO_EN          : 1;  /* [    2],       None,        0x0 */
            uint32_t PO_EN_CHG      : 1;  /* [    3],       None,        0x0 */
            uint32_t reserved_4_5   : 2;  /* [ 5: 4],       rsvd,        0x0 */
            uint32_t F_PO_RESM      : 1;  /* [    6],       None,        0x0 */
            uint32_t PO_SUSP        : 1;  /* [    7],       None,        0x0 */
            uint32_t PO_RESET       : 1;  /* [    8],       None,        0x0 */
            uint32_t reserved_9     : 1;  /* [    9],       rsvd,        0x0 */
            uint32_t LINE_STS       : 2;  /* [11:10],       None,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t PORT_TEST      : 4;  /* [19:16],       None,        0x0 */
            uint32_t HC_TST_PKDONE  : 1;  /* [   20],       None,        0x0 */
            uint32_t reserved_21_31 : 11; /* [31:21],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } PORTSC;

    /* 0x34  reserved */
    uint8_t RESERVED0x34[12];

    /* 0x040 : HCMISC */
    union {
        struct
        {
            uint32_t ASYN_SCH_SLPT   : 2;  /* [ 1: 0],       None,        0x0 */
            uint32_t EOF1_Time       : 2;  /* [ 3: 2],       None,        0x0 */
            uint32_t EOF2_Time       : 2;  /* [ 5: 4],       None,        0x0 */
            uint32_t HostPhy_Suspend : 1;  /* [    6],       None,        0x0 */
            uint32_t reserved_7      : 1;  /* [    7],       rsvd,        0x0 */
            uint32_t HC_WKP_DET_EN   : 1;  /* [    8],       None,        0x0 */
            uint32_t HC_CONN_DET_EN  : 1;  /* [    9],       None,        0x0 */
            uint32_t reserved_10_31  : 22; /* [31:10],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } HCMISC;

    /* 0x044 : FS_EOF */
    union {
        struct
        {
            uint32_t FS_EOF1_Time       : 12; /* [11: 0],       None,        0x0 */
            uint32_t FS_EOF1_Time_125us : 3;  /* [14:12],       None,        0x0 */
            uint32_t reserved_15        : 1;  /* [   15],       rsvd,        0x0 */
            uint32_t iTDdmaSM           : 4;  /* [19:16],       None,        0x0 */
            uint32_t iTDTravSM          : 2;  /* [21:20],       None,        0x0 */
            uint32_t DMAdmSM            : 4;  /* [25:22],       None,        0x0 */
            uint32_t QHTtrSM            : 3;  /* [28:26],       None,        0x0 */
            uint32_t QHTravSM           : 3;  /* [31:29],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } FS_EOF;

    /* 0x048 : HS_EOF */
    union {
        struct
        {
            uint32_t HS_EOF1_Time   : 12; /* [11: 0],       None,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t siTDdmaSM      : 4;  /* [19:16],       None,        0x0 */
            uint32_t siTDTravSM     : 2;  /* [21:20],       None,        0x0 */
            uint32_t reserved_22_31 : 10; /* [31:22],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } HS_EOF;

    /* 0x4c  reserved */
    uint8_t RESERVED0x4c[52];

    /* 0x080 : OTG_CSR */
    union {
        struct
        {
            uint32_t B_BUS_REQ            : 1; /* [    0],       None,        0x0 */
            uint32_t B_HNP_EN             : 1; /* [    1],       None,        0x0 */
            uint32_t B_DSCHRG_VBUS        : 1; /* [    2],       None,        0x0 */
            uint32_t reserved_3           : 1; /* [    3],       rsvd,        0x0 */
            uint32_t A_BUS_REQ_HOV        : 1; /* [    4],       None,        0x0 */
            uint32_t A_BUS_DROP_HOV       : 1; /* [    5],       None,        0x0 */
            uint32_t A_SET_B_HNP_EN       : 1; /* [    6],       None,        0x0 */
            uint32_t A_SRP_DET_EN         : 1; /* [    7],       None,        0x0 */
            uint32_t A_SRP_RESP_TYP       : 1; /* [    8],       None,        0x0 */
            uint32_t ID_FLT_SEL           : 1; /* [    9],       None,        0x0 */
            uint32_t VBUS_FLT_SEL_HOV_POV : 1; /* [   10],       None,        0x0 */
            uint32_t HDISCON_FLT_SEL_HOV  : 1; /* [   11],       None,        0x0 */
            uint32_t reserved_12          : 1; /* [   12],       rsvd,        0x0 */
            uint32_t IDPULUP_HOV_POV      : 1; /* [   13],       None,        0x0 */
            uint32_t reserved_14_15       : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t B_SESS_END_POV       : 1; /* [   16],       None,        0x0 */
            uint32_t B_SESS_VLD_POV       : 1; /* [   17],       None,        0x0 */
            uint32_t A_SESS_VLD           : 1; /* [   18],       None,        0x0 */
            uint32_t VBUS_VLD_HOV         : 1; /* [   19],       None,        0x0 */
            uint32_t CROLE_HOV_POV        : 1; /* [   20],       None,        0x0 */
            uint32_t ID_HOV_POV           : 1; /* [   21],       None,        0x0 */
            uint32_t SPD_TYP_HOV_POV      : 2; /* [23:22],       None,        0x0 */
            uint32_t reserved_24_31       : 8; /* [31:24],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } OTG_CSR;

    /* 0x084 : OTG_ISR */
    union {
        struct
        {
            uint32_t B_SRP_DN       : 1;  /* [    0],       None,        0x0 */
            uint32_t reserved_1_3   : 3;  /* [ 3: 1],       rsvd,        0x0 */
            uint32_t A_SRP_DET      : 1;  /* [    4],       None,        0x0 */
            uint32_t A_VBUS_ERR_HOV : 1;  /* [    5],       None,        0x0 */
            uint32_t B_SESS_END_POV : 1;  /* [    6],       None,        0x0 */
            uint32_t reserved_7     : 1;  /* [    7],       rsvd,        0x0 */
            uint32_t RLCHG          : 1;  /* [    8],       None,        0x0 */
            uint32_t IDCHG          : 1;  /* [    9],       None,        0x0 */
            uint32_t OVC_HOV        : 1;  /* [   10],       None,        0x0 */
            uint32_t A_WAIT_CON_HOV : 1;  /* [   11],       None,        0x0 */
            uint32_t APLGRMV        : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } OTG_ISR;

    /* 0x088 : OTG_IER */
    union {
        struct
        {
            uint32_t B_SRP_DN_EN       : 1;  /* [    0],       None,        0x0 */
            uint32_t reserved_1_3      : 3;  /* [ 3: 1],       rsvd,        0x0 */
            uint32_t A_SRP_DET_EN      : 1;  /* [    4],       None,        0x0 */
            uint32_t A_VBUS_ERR_EN_HOV : 1;  /* [    5],       None,        0x0 */
            uint32_t B_SESS_END_EN_POV : 1;  /* [    6],       None,        0x0 */
            uint32_t reserved_7        : 1;  /* [    7],       rsvd,        0x0 */
            uint32_t RLCHG_EN          : 1;  /* [    8],       None,        0x0 */
            uint32_t IDCHG_EN          : 1;  /* [    9],       None,        0x0 */
            uint32_t OVC_EN_HOV        : 1;  /* [   10],       None,        0x0 */
            uint32_t A_WAIT_CON_EN_HOV : 1;  /* [   11],       None,        0x0 */
            uint32_t APLGRMV_EN        : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31    : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } OTG_IER;

    /* 0x8c  reserved */
    uint8_t RESERVED0x8c[52];

    /* 0x0C0 : GLB_ISR */
    union {
        struct
        {
            uint32_t DEV_INT       : 1;  /* [    0],       None,        0x0 */
            uint32_t OTG_INT       : 1;  /* [    1],       None,        0x0 */
            uint32_t HC_INT        : 1;  /* [    2],       None,        0x0 */
            uint32_t reserved_3_31 : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } GLB_ISR;

    /* 0x0C4 : GLB_INT */
    union {
        struct
        {
            uint32_t MDEV_INT      : 1;  /* [    0],       None,        0x0 */
            uint32_t MOTG_INT      : 1;  /* [    1],       None,        0x0 */
            uint32_t MHC_INT       : 1;  /* [    2],       None,        0x0 */
            uint32_t INT_POLARITY  : 1;  /* [    3],       None,        0x0 */
            uint32_t reserved_4_31 : 28; /* [31: 4],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } GLB_INT;

    /* 0xc8  reserved */
    uint8_t RESERVED0xc8[24];

    /* 0x0E0 : REVISION */
    union {
        struct
        {
            uint32_t REVISION : 32; /* [31: 0],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } REVISION;

    /* 0x0E4 : FEATURE */
    union {
        struct
        {
            uint32_t DMABUFSIZE     : 5;  /* [ 4: 0],       None,        0x0 */
            uint32_t FIFO_NUM       : 5;  /* [ 9: 5],       None,        0x0 */
            uint32_t EP_NUM         : 5;  /* [14:10],       None,        0x0 */
            uint32_t DEV_ONLY       : 1;  /* [   15],       None,        0x0 */
            uint32_t HOST_ONLY      : 1;  /* [   16],       None,        0x0 */
            uint32_t reserved_17_31 : 15; /* [31:17],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } FEATURE;

    /* 0x0E8 : AXI_CR */
    union {
        struct
        {
            uint32_t AXI_SGLBST    : 1;  /* [    0],       None,        0x0 */
            uint32_t reserved_1_31 : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } AXI_CR;

    /* 0xec  reserved */
    uint8_t RESERVED0xec[20];

    /* 0x100 : DEV_CTL */
    union {
        struct
        {
            uint32_t CAP_RMWAKUP       : 1; /* [    0],       None,        0x0 */
            uint32_t HALF_SPEED_HOV    : 1; /* [    1],       None,        0x0 */
            uint32_t GLINT_EN_HOV      : 1; /* [    2],       None,        0x0 */
            uint32_t GOSUSP            : 1; /* [    3],       None,        0x0 */
            uint32_t SFRST_HOV         : 1; /* [    4],       None,        0x0 */
            uint32_t CHIP_EN_HOV       : 1; /* [    5],       None,        0x0 */
            uint32_t HS_EN_HOV         : 1; /* [    6],       None,        0x0 */
            uint32_t SYSBUS_WIDTH_HOV  : 1; /* [    7],       None,        0x0 */
            uint32_t reserved_8        : 1; /* [    8],       rsvd,        0x0 */
            uint32_t FORCE_FS          : 1; /* [    9],       None,        0x0 */
            uint32_t IDLE_DEGLITCH_HOV : 2; /* [11:10],       None,        0x0 */
            uint32_t LPM_BESL_MAX      : 4; /* [15:12],       None,        0x0 */
            uint32_t LPM_BESL_MIN      : 4; /* [19:16],       None,        0x0 */
            uint32_t LPM_BESL          : 4; /* [23:20],       None,        0x0 */
            uint32_t reserved_24       : 1; /* [   24],       rsvd,        0x0 */
            uint32_t LPM_EN            : 1; /* [   25],       None,        0x0 */
            uint32_t LPM_ACCEPT        : 1; /* [   26],       None,        0x0 */
            uint32_t reserved_27_31    : 5; /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_CTL;

    /* 0x104 : DEV_ADR */
    union {
        struct
        {
            uint32_t DEVADR        : 7;  /* [ 6: 0],       None,        0x0 */
            uint32_t AFT_CONF      : 1;  /* [    7],       None,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_ADR;

    /* 0x108 : DEV_TST */
    union {
        struct
        {
            uint32_t TST_CLRFF_HOV   : 1;  /* [    0],       None,        0x0 */
            uint32_t TST_LPCX        : 1;  /* [    1],       None,        0x0 */
            uint32_t TST_CLREA       : 1;  /* [    2],       None,        0x0 */
            uint32_t rsvd_3          : 1;  /* [    3],       None,        0x0 */
            uint32_t TST_DISTO_HOV   : 1;  /* [    4],       None,        0x0 */
            uint32_t TST_MOD_HOV     : 1;  /* [    5],       None,        0x0 */
            uint32_t DISGENSOF       : 1;  /* [    6],       None,        0x0 */
            uint32_t TST_MOD_TYP_HOV : 1;  /* [    7],       None,        0x0 */
            uint32_t reserved_8_31   : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_TST;

    /* 0x10C : DEV_SFN */
    union {
        struct
        {
            uint32_t SOFN           : 11; /* [10: 0],       None,        0x0 */
            uint32_t USOFN          : 3;  /* [13:11],       None,        0x0 */
            uint32_t reserved_14_31 : 18; /* [31:14],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_SFN;

    /* 0x110 : DEV_SMT */
    union {
        struct
        {
            uint32_t SOFMT          : 16; /* [15: 0],       None,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_SMT;

    /* 0x114 : PHY_TST */
    union {
        struct
        {
            uint32_t UNPLUG        : 1;  /* [    0],       None,        0x0 */
            uint32_t TST_JSTA      : 1;  /* [    1],       None,        0x0 */
            uint32_t TST_KSTA      : 1;  /* [    2],       None,        0x0 */
            uint32_t TST_SE0NAK    : 1;  /* [    3],       None,        0x0 */
            uint32_t TST_PKT       : 1;  /* [    4],       None,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } PHY_TST;

    /* 0x118 : DEV_VCTL */
    union {
        struct
        {
            uint32_t VCTL_HOV      : 5;  /* [ 4: 0],       None,        0x0 */
            uint32_t VCTLOAD_N_HOV : 1;  /* [    5],       None,        0x0 */
            uint32_t reserved_6_31 : 26; /* [31: 6],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_VCTL;

    /* 0x11C : DEV_CXCFG */
    union {
        struct
        {
            uint32_t VSTA_HOV      : 8;  /* [ 7: 0],       None,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_CXCFG;

    /* 0x120 : DEV_CXCFE */
    union {
        struct
        {
            uint32_t CX_DONE      : 1; /* [    0],       None,        0x0 */
            uint32_t TST_PKDONE   : 1; /* [    1],       None,        0x0 */
            uint32_t CX_STL       : 1; /* [    2],       None,        0x0 */
            uint32_t CX_CLR       : 1; /* [    3],       None,        0x0 */
            uint32_t CX_FUL       : 1; /* [    4],       None,        0x0 */
            uint32_t CX_EMP       : 1; /* [    5],       None,        0x0 */
            uint32_t reserved_6_7 : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t F0_EMP       : 1; /* [    8],       None,        0x0 */
            uint32_t F1_EMP       : 1; /* [    9],       None,        0x0 */
            uint32_t F2_EMP       : 1; /* [   10],       None,        0x0 */
            uint32_t F3_EMP       : 1; /* [   11],       None,        0x0 */
            uint32_t F4_EMP       : 1; /* [   12],       None,        0x0 */
            uint32_t F5_EMP       : 1; /* [   13],       None,        0x0 */
            uint32_t F6_EMP       : 1; /* [   14],       None,        0x0 */
            uint32_t F7_EMP       : 1; /* [   15],       None,        0x0 */
            uint32_t F8_EMP       : 1; /* [   16],       None,        0x0 */
            uint32_t F9_EMP       : 1; /* [   17],       None,        0x0 */
            uint32_t F10_EMP      : 1; /* [   18],       None,        0x0 */
            uint32_t F11_EMP      : 1; /* [   19],       None,        0x0 */
            uint32_t F12_EMP      : 1; /* [   20],       None,        0x0 */
            uint32_t F13_EMP      : 1; /* [   21],       None,        0x0 */
            uint32_t F14_EMP      : 1; /* [   22],       None,        0x0 */
            uint32_t F15_EMP      : 1; /* [   23],       None,        0x0 */
            uint32_t CX_FNT       : 7; /* [30:24],       None,        0x0 */
            uint32_t reserved_31  : 1; /* [   31],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_CXCFE;

    /* 0x124 : DEV_ICR */
    union {
        struct
        {
            uint32_t IDLE_CNT      : 3;  /* [ 2: 0],       None,        0x0 */
            uint32_t reserved_3_31 : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_ICR;

    /* 0x128  reserved */
    uint8_t RESERVED0x128[8];

    /* 0x130 : DEV_MIGR */
    union {
        struct
        {
            uint32_t MINT_G0       : 1;  /* [    0],       None,        0x0 */
            uint32_t MINT_G1       : 1;  /* [    1],       None,        0x0 */
            uint32_t MINT_G2       : 1;  /* [    2],       None,        0x0 */
            uint32_t MINT_G3       : 1;  /* [    3],       None,        0x0 */
            uint32_t MINT_G4       : 1;  /* [    4],       None,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_MIGR;

    /* 0x134 : DEV_MISG0 */
    union {
        struct
        {
            uint32_t MCX_SETUP_INT    : 1;  /* [    0],       None,        0x0 */
            uint32_t MCX_IN_INT       : 1;  /* [    1],       None,        0x0 */
            uint32_t MCX_OUT_INT      : 1;  /* [    2],       None,        0x0 */
            uint32_t reserved_3       : 1;  /* [    3],       rsvd,        0x0 */
            uint32_t MCX_COMFAIL_INT  : 1;  /* [    4],       None,        0x0 */
            uint32_t MCX_COMABORT_INT : 1;  /* [    5],       None,        0x0 */
            uint32_t reserved_6_31    : 26; /* [31: 6],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_MISG0;

    /* 0x138 : DEV_MISG1 */
    union {
        struct
        {
            uint32_t MF0_OUT_INT : 1; /* [    0],       None,        0x0 */
            uint32_t MF0_SPK_INT : 1; /* [    1],       None,        0x0 */
            uint32_t MF1_OUT_INT : 1; /* [    2],       None,        0x0 */
            uint32_t MF1_SPK_INT : 1; /* [    3],       None,        0x0 */
            uint32_t MF2_OUT_INT : 1; /* [    4],       None,        0x0 */
            uint32_t MF2_SPK_INT : 1; /* [    5],       None,        0x0 */
            uint32_t MF3_OUT_INT : 1; /* [    6],       None,        0x0 */
            uint32_t MF3_SPK_INT : 1; /* [    7],       None,        0x0 */
            uint32_t MF4_OUT_INT : 1; /* [    8],       None,        0x0 */
            uint32_t MF4_SPK_INT : 1; /* [    9],       None,        0x0 */
            uint32_t MF5_OUT_INT : 1; /* [   10],       None,        0x0 */
            uint32_t MF5_SPK_INT : 1; /* [   11],       None,        0x0 */
            uint32_t MF6_OUT_INT : 1; /* [   12],       None,        0x0 */
            uint32_t MF6_SPK_INT : 1; /* [   13],       None,        0x0 */
            uint32_t MF7_OUT_INT : 1; /* [   14],       None,        0x0 */
            uint32_t MF7_SPK_INT : 1; /* [   15],       None,        0x0 */
            uint32_t MF0_IN_INT  : 1; /* [   16],       None,        0x0 */
            uint32_t MF1_IN_INT  : 1; /* [   17],       None,        0x0 */
            uint32_t MF2_IN_INT  : 1; /* [   18],       None,        0x0 */
            uint32_t MF3_IN_INT  : 1; /* [   19],       None,        0x0 */
            uint32_t MF4_IN_INT  : 1; /* [   20],       None,        0x0 */
            uint32_t MF5_IN_INT  : 1; /* [   21],       None,        0x0 */
            uint32_t MF6_IN_INT  : 1; /* [   22],       None,        0x0 */
            uint32_t MF7_IN_INT  : 1; /* [   23],       None,        0x0 */
            uint32_t MF8_IN_INT  : 1; /* [   24],       None,        0x0 */
            uint32_t MF9_IN_INT  : 1; /* [   25],       None,        0x0 */
            uint32_t MF10_IN_INT : 1; /* [   26],       None,        0x0 */
            uint32_t MF11_IN_INT : 1; /* [   27],       None,        0x0 */
            uint32_t MF12_IN_INT : 1; /* [   28],       None,        0x0 */
            uint32_t MF13_IN_INT : 1; /* [   29],       None,        0x0 */
            uint32_t MF14_IN_INT : 1; /* [   30],       None,        0x0 */
            uint32_t MF15_IN_INT : 1; /* [   31],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_MISG1;

    /* 0x13C : DEV_MISG2 */
    union {
        struct
        {
            uint32_t MUSBRST_INT        : 1; /* [    0],       None,        0x0 */
            uint32_t MSUSP_INT          : 1; /* [    1],       None,        0x0 */
            uint32_t MRESM_INT          : 1; /* [    2],       None,        0x0 */
            uint32_t MSEQ_ERR_INT       : 1; /* [    3],       None,        0x0 */
            uint32_t MSEQ_ABORT_INT     : 1; /* [    4],       None,        0x0 */
            uint32_t MTX0BYTE_INT       : 1; /* [    5],       None,        0x0 */
            uint32_t MRX0BYTE_INT       : 1; /* [    6],       None,        0x0 */
            uint32_t MDMA_CMPLT_HOV     : 1; /* [    7],       None,        0x0 */
            uint32_t MDMA_ERROR_HOV     : 1; /* [    8],       None,        0x0 */
            uint32_t MDev_Idle_HOV      : 1; /* [    9],       None,        0x0 */
            uint32_t MDev_Wakeup_byVBUS : 1; /* [   10],       None,        0x0 */
            uint32_t reserved_11_15     : 5; /* [15:11],       rsvd,        0x0 */
            uint32_t MF8_OUT_INT        : 1; /* [   16],       None,        0x0 */
            uint32_t MF8_SPK_INT        : 1; /* [   17],       None,        0x0 */
            uint32_t MF9_OUT_INT        : 1; /* [   18],       None,        0x0 */
            uint32_t MF9_SPK_INT        : 1; /* [   19],       None,        0x0 */
            uint32_t MF10_OUT_INT       : 1; /* [   20],       None,        0x0 */
            uint32_t MF10_SPK_INT       : 1; /* [   21],       None,        0x0 */
            uint32_t MF11_OUT_INT       : 1; /* [   22],       None,        0x0 */
            uint32_t MF11_SPK_INT       : 1; /* [   23],       None,        0x0 */
            uint32_t MF12_OUT_INT       : 1; /* [   24],       None,        0x0 */
            uint32_t MF12_SPK_INT       : 1; /* [   25],       None,        0x0 */
            uint32_t MF13_OUT_INT       : 1; /* [   26],       None,        0x0 */
            uint32_t MF13_SPK_INT       : 1; /* [   27],       None,        0x0 */
            uint32_t MF14_OUT_INT       : 1; /* [   28],       None,        0x0 */
            uint32_t MF14_SPK_INT       : 1; /* [   29],       None,        0x0 */
            uint32_t MF15_OUT_INT       : 1; /* [   30],       None,        0x0 */
            uint32_t MF15_SPK_INT       : 1; /* [   31],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_MISG2;

    /* 0x140 : DEV_IGR */
    union {
        struct
        {
            uint32_t INT_G0        : 1;  /* [    0],       None,        0x0 */
            uint32_t INT_G1        : 1;  /* [    1],       None,        0x0 */
            uint32_t INT_G2_HOV    : 1;  /* [    2],       None,        0x0 */
            uint32_t INT_G3        : 1;  /* [    3],       None,        0x0 */
            uint32_t INT_G4        : 1;  /* [    4],       None,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_IGR;

    /* 0x144 : DEV_ISG0 */
    union {
        struct
        {
            uint32_t CX_SETUP_INT   : 1;  /* [    0],       None,        0x0 */
            uint32_t CX_IN_INT      : 1;  /* [    1],       None,        0x0 */
            uint32_t CX_OUT_INT     : 1;  /* [    2],       None,        0x0 */
            uint32_t reserved_3     : 1;  /* [    3],       rsvd,        0x0 */
            uint32_t CX_COMFAIL_INT : 1;  /* [    4],       None,        0x0 */
            uint32_t CX_COMABT_INT  : 1;  /* [    5],       None,        0x0 */
            uint32_t reserved_6_31  : 26; /* [31: 6],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_ISG0;

    /* 0x148 : DEV_ISG1 */
    union {
        struct
        {
            uint32_t F0_OUT_INT : 1; /* [    0],       None,        0x0 */
            uint32_t F0_SPK_INT : 1; /* [    1],       None,        0x0 */
            uint32_t F1_OUT_INT : 1; /* [    2],       None,        0x0 */
            uint32_t F1_SPK_INT : 1; /* [    3],       None,        0x0 */
            uint32_t F2_OUT_INT : 1; /* [    4],       None,        0x0 */
            uint32_t F2_SPK_INT : 1; /* [    5],       None,        0x0 */
            uint32_t F3_OUT_INT : 1; /* [    6],       None,        0x0 */
            uint32_t F3_SPK_INT : 1; /* [    7],       None,        0x0 */
            uint32_t F4_OUT_INT : 1; /* [    8],       None,        0x0 */
            uint32_t F4_SPK_INT : 1; /* [    9],       None,        0x0 */
            uint32_t F5_OUT_INT : 1; /* [   10],       None,        0x0 */
            uint32_t F5_SPK_INT : 1; /* [   11],       None,        0x0 */
            uint32_t F6_OUT_INT : 1; /* [   12],       None,        0x0 */
            uint32_t F6_SPK_INT : 1; /* [   13],       None,        0x0 */
            uint32_t F7_OUT_INT : 1; /* [   14],       None,        0x0 */
            uint32_t F7_SPK_INT : 1; /* [   15],       None,        0x0 */
            uint32_t F0_IN_INT  : 1; /* [   16],       None,        0x0 */
            uint32_t F1_IN_INT  : 1; /* [   17],       None,        0x0 */
            uint32_t F2_IN_INT  : 1; /* [   18],       None,        0x0 */
            uint32_t F3_IN_INT  : 1; /* [   19],       None,        0x0 */
            uint32_t F4_IN_INT  : 1; /* [   20],       None,        0x0 */
            uint32_t F5_IN_INT  : 1; /* [   21],       None,        0x0 */
            uint32_t F6_IN_INT  : 1; /* [   22],       None,        0x0 */
            uint32_t F7_IN_INT  : 1; /* [   23],       None,        0x0 */
            uint32_t F8_IN_INT  : 1; /* [   24],       None,        0x0 */
            uint32_t F9_IN_INT  : 1; /* [   25],       None,        0x0 */
            uint32_t F10_IN_INT : 1; /* [   26],       None,        0x0 */
            uint32_t F11_IN_INT : 1; /* [   27],       None,        0x0 */
            uint32_t F12_IN_INT : 1; /* [   28],       None,        0x0 */
            uint32_t F13_IN_INT : 1; /* [   29],       None,        0x0 */
            uint32_t F14_IN_INT : 1; /* [   30],       None,        0x0 */
            uint32_t F15_IN_INT : 1; /* [   31],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_ISG1;

    /* 0x14C : DEV_ISG2 */
    union {
        struct
        {
            uint32_t USBRST_INT        : 1; /* [    0],       None,        0x0 */
            uint32_t SUSP_INT          : 1; /* [    1],       None,        0x0 */
            uint32_t RESM_INT          : 1; /* [    2],       None,        0x0 */
            uint32_t ISO_SEQ_ERR_INT   : 1; /* [    3],       None,        0x0 */
            uint32_t ISO_SEQ_ABORT_INT : 1; /* [    4],       None,        0x0 */
            uint32_t TX0BYTE_INT       : 1; /* [    5],       None,        0x0 */
            uint32_t RX0BYTE_INT       : 1; /* [    6],       None,        0x0 */
            uint32_t DMA_CMPLT_HOV     : 1; /* [    7],       None,        0x0 */
            uint32_t DMA_ERROR_HOV     : 1; /* [    8],       None,        0x0 */
            uint32_t Dev_Idle_HOV      : 1; /* [    9],       None,        0x0 */
            uint32_t Dev_Wakeup_byVBUS : 1; /* [   10],       None,        0x0 */
            uint32_t reserved_11_15    : 5; /* [15:11],       rsvd,        0x0 */
            uint32_t F8_OUT_INT        : 1; /* [   16],       None,        0x0 */
            uint32_t F8_SPK_INT        : 1; /* [   17],       None,        0x0 */
            uint32_t F9_OUT_INT        : 1; /* [   18],       None,        0x0 */
            uint32_t F9_SPK_INT        : 1; /* [   19],       None,        0x0 */
            uint32_t F10_OUT_INT       : 1; /* [   20],       None,        0x0 */
            uint32_t F10_SPK_INT       : 1; /* [   21],       None,        0x0 */
            uint32_t F11_OUT_INT       : 1; /* [   22],       None,        0x0 */
            uint32_t F11_SPK_INT       : 1; /* [   23],       None,        0x0 */
            uint32_t F12_OUT_INT       : 1; /* [   24],       None,        0x0 */
            uint32_t F12_SPK_INT       : 1; /* [   25],       None,        0x0 */
            uint32_t F13_OUT_INT       : 1; /* [   26],       None,        0x0 */
            uint32_t F13_SPK_INT       : 1; /* [   27],       None,        0x0 */
            uint32_t F14_OUT_INT       : 1; /* [   28],       None,        0x0 */
            uint32_t F14_SPK_INT       : 1; /* [   29],       None,        0x0 */
            uint32_t F15_OUT_INT       : 1; /* [   30],       None,        0x0 */
            uint32_t F15_SPK_INT       : 1; /* [   31],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_ISG2;

    /* 0x150 : DEV_RXZ */
    union {
        struct
        {
            uint32_t RX0BYTE_EP1   : 1;  /* [    0],       None,        0x0 */
            uint32_t RX0BYTE_EP2   : 1;  /* [    1],       None,        0x0 */
            uint32_t RX0BYTE_EP3   : 1;  /* [    2],       None,        0x0 */
            uint32_t RX0BYTE_EP4   : 1;  /* [    3],       None,        0x0 */
            uint32_t RX0BYTE_EP5   : 1;  /* [    4],       None,        0x0 */
            uint32_t RX0BYTE_EP6   : 1;  /* [    5],       None,        0x0 */
            uint32_t RX0BYTE_EP7   : 1;  /* [    6],       None,        0x0 */
            uint32_t RX0BYTE_EP8   : 1;  /* [    7],       None,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_RXZ;

    /* 0x154 : DEV_TXZ */
    union {
        struct
        {
            uint32_t TX0BYTE_EP1   : 1;  /* [    0],       None,        0x0 */
            uint32_t TX0BYTE_EP2   : 1;  /* [    1],       None,        0x0 */
            uint32_t TX0BYTE_EP3   : 1;  /* [    2],       None,        0x0 */
            uint32_t TX0BYTE_EP4   : 1;  /* [    3],       None,        0x0 */
            uint32_t TX0BYTE_EP5   : 1;  /* [    4],       None,        0x0 */
            uint32_t TX0BYTE_EP6   : 1;  /* [    5],       None,        0x0 */
            uint32_t TX0BYTE_EP7   : 1;  /* [    6],       None,        0x0 */
            uint32_t TX0BYTE_EP8   : 1;  /* [    7],       None,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_TXZ;

    /* 0x158 : DEV_ISE */
    union {
        struct
        {
            uint32_t ISO_ABT_ERR_EP1 : 1; /* [    0],       None,        0x0 */
            uint32_t ISO_ABT_ERR_EP2 : 1; /* [    1],       None,        0x0 */
            uint32_t ISO_ABT_ERR_EP3 : 1; /* [    2],       None,        0x0 */
            uint32_t ISO_ABT_ERR_EP4 : 1; /* [    3],       None,        0x0 */
            uint32_t ISO_ABT_ERR_EP5 : 1; /* [    4],       None,        0x0 */
            uint32_t ISO_ABT_ERR_EP6 : 1; /* [    5],       None,        0x0 */
            uint32_t ISO_ABT_ERR_EP7 : 1; /* [    6],       None,        0x0 */
            uint32_t ISO_ABT_ERR_EP8 : 1; /* [    7],       None,        0x0 */
            uint32_t reserved_8_15   : 8; /* [15: 8],       rsvd,        0x0 */
            uint32_t ISO_SEQ_ERR_EP1 : 1; /* [   16],       None,        0x0 */
            uint32_t ISO_SEQ_ERR_EP2 : 1; /* [   17],       None,        0x0 */
            uint32_t ISO_SEQ_ERR_EP3 : 1; /* [   18],       None,        0x0 */
            uint32_t ISO_SEQ_ERR_EP4 : 1; /* [   19],       None,        0x0 */
            uint32_t ISO_SEQ_ERR_EP5 : 1; /* [   20],       None,        0x0 */
            uint32_t ISO_SEQ_ERR_EP6 : 1; /* [   21],       None,        0x0 */
            uint32_t ISO_SEQ_ERR_EP7 : 1; /* [   22],       None,        0x0 */
            uint32_t ISO_SEQ_ERR_EP8 : 1; /* [   23],       None,        0x0 */
            uint32_t reserved_24_31  : 8; /* [31:24],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_ISE;

    /* 0x15c  reserved */
    uint8_t RESERVED0x15c[4];

    /* 0x160 : DEV_INMPS1 */
    union {
        struct
        {
            uint32_t MAXPS_IEP1      : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_IEP1        : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_IEP1       : 1;  /* [   12],       None,        0x0 */
            uint32_t TX_NUM_HBW_IEP1 : 2;  /* [14:13],       None,        0x0 */
            uint32_t TX0BYTE_IEP1    : 1;  /* [   15],       None,        0x0 */
            uint32_t reserved_16_31  : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_INMPS1;

    /* 0x164 : DEV_INMPS2 */
    union {
        struct
        {
            uint32_t MAXPS_IEP2      : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_IEP2        : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_IEP2       : 1;  /* [   12],       None,        0x0 */
            uint32_t TX_NUM_HBW_IEP2 : 2;  /* [14:13],       None,        0x0 */
            uint32_t TX0BYTE_IEP2    : 1;  /* [   15],       None,        0x0 */
            uint32_t reserved_16_31  : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_INMPS2;

    /* 0x168 : DEV_INMPS3 */
    union {
        struct
        {
            uint32_t MAXPS_IEP3      : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_IEP3        : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_IEP3       : 1;  /* [   12],       None,        0x0 */
            uint32_t TX_NUM_HBW_IEP3 : 2;  /* [14:13],       None,        0x0 */
            uint32_t TX0BYTE_IEP3    : 1;  /* [   15],       None,        0x0 */
            uint32_t reserved_16_31  : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_INMPS3;

    /* 0x16C : DEV_INMPS4 */
    union {
        struct
        {
            uint32_t MAXPS_IEP4      : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_IEP4        : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_IEP4       : 1;  /* [   12],       None,        0x0 */
            uint32_t TX_NUM_HBW_IEP4 : 2;  /* [14:13],       None,        0x0 */
            uint32_t TX0BYTE_IEP4    : 1;  /* [   15],       None,        0x0 */
            uint32_t reserved_16_31  : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_INMPS4;

    /* 0x170 : DEV_INMPS5 */
    union {
        struct
        {
            uint32_t MAXPS_IEP5      : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_IEP5        : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_IEP5       : 1;  /* [   12],       None,        0x0 */
            uint32_t TX_NUM_HBW_IEP5 : 2;  /* [14:13],       None,        0x0 */
            uint32_t TX0BYTE_IEP5    : 1;  /* [   15],       None,        0x0 */
            uint32_t reserved_16_31  : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_INMPS5;

    /* 0x174 : DEV_INMPS6 */
    union {
        struct
        {
            uint32_t MAXPS_IEP6      : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_IEP6        : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_IEP6       : 1;  /* [   12],       None,        0x0 */
            uint32_t TX_NUM_HBW_IEP6 : 2;  /* [14:13],       None,        0x0 */
            uint32_t TX0BYTE_IEP6    : 1;  /* [   15],       None,        0x0 */
            uint32_t reserved_16_31  : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_INMPS6;

    /* 0x178 : DEV_INMPS7 */
    union {
        struct
        {
            uint32_t MAXPS_IEP7      : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_IEP7        : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_IEP7       : 1;  /* [   12],       None,        0x0 */
            uint32_t TX_NUM_HBW_IEP7 : 2;  /* [14:13],       None,        0x0 */
            uint32_t TX0BYTE_IEP7    : 1;  /* [   15],       None,        0x0 */
            uint32_t reserved_16_31  : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_INMPS7;

    /* 0x17C : DEV_INMPS8 */
    union {
        struct
        {
            uint32_t MAXPS_IEP8      : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_IEP8        : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_IEP8       : 1;  /* [   12],       None,        0x0 */
            uint32_t TX_NUM_HBW_IEP8 : 2;  /* [14:13],       None,        0x0 */
            uint32_t TX0BYTE_IEP8    : 1;  /* [   15],       None,        0x0 */
            uint32_t reserved_16_31  : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_INMPS8;

    /* 0x180 : DEV_OUTMPS1 */
    union {
        struct
        {
            uint32_t MAXPS_OEP1     : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_OEP1       : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_OEP1      : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_OUTMPS1;

    /* 0x184 : DEV_OUTMPS2 */
    union {
        struct
        {
            uint32_t MAXPS_OEP2     : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_OEP2       : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_OEP2      : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_OUTMPS2;

    /* 0x188 : DEV_OUTMPS3 */
    union {
        struct
        {
            uint32_t MAXPS_OEP3     : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_OEP3       : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_OEP3      : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_OUTMPS3;

    /* 0x18C : DEV_OUTMPS4 */
    union {
        struct
        {
            uint32_t MAXPS_OEP4     : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_OEP4       : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_OEP4      : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_OUTMPS4;

    /* 0x190 : DEV_OUTMPS5 */
    union {
        struct
        {
            uint32_t MAXPS_OEP5     : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_OEP5       : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_OEP5      : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_OUTMPS5;

    /* 0x194 : DEV_OUTMPS6 */
    union {
        struct
        {
            uint32_t MAXPS_OEP6     : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_OEP6       : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_OEP6      : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_OUTMPS6;

    /* 0x198 : DEV_OUTMPS7 */
    union {
        struct
        {
            uint32_t MAXPS_OEP7     : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_OEP7       : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_OEP7      : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_OUTMPS7;

    /* 0x19C : DEV_OUTMPS8 */
    union {
        struct
        {
            uint32_t MAXPS_OEP8     : 11; /* [10: 0],       None,        0x0 */
            uint32_t STL_OEP8       : 1;  /* [   11],       None,        0x0 */
            uint32_t RSTG_OEP8      : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_OUTMPS8;

    /* 0x1A0 : DEV_EPMAP08 */
    union {
        struct
        {
            uint32_t FNO_IEP1 : 4; /* [ 3: 0],       None,        0x0 */
            uint32_t FNO_OEP1 : 4; /* [ 7: 4],       None,        0x0 */
            uint32_t FNO_IEP2 : 4; /* [11: 8],       None,        0x0 */
            uint32_t FNO_OEP2 : 4; /* [15:12],       None,        0x0 */
            uint32_t FNO_IEP3 : 4; /* [19:16],       None,        0x0 */
            uint32_t FNO_OEP3 : 4; /* [23:20],       None,        0x0 */
            uint32_t FNO_IEP4 : 4; /* [27:24],       None,        0x0 */
            uint32_t FNO_OEP4 : 4; /* [31:28],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_EPMAP08;

    /* 0x1A4 : DEV_EPMAP1 */
    union {
        struct
        {
            uint32_t FNO_IEP5 : 4; /* [ 3: 0],       None,        0x0 */
            uint32_t FNO_OEP5 : 4; /* [ 7: 4],       None,        0x0 */
            uint32_t FNO_IEP6 : 4; /* [11: 8],       None,        0x0 */
            uint32_t FNO_OEP6 : 4; /* [15:12],       None,        0x0 */
            uint32_t FNO_IEP7 : 4; /* [19:16],       None,        0x0 */
            uint32_t FNO_OEP7 : 4; /* [23:20],       None,        0x0 */
            uint32_t FNO_IEP8 : 4; /* [27:24],       None,        0x0 */
            uint32_t FNO_OEP8 : 4; /* [31:28],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_EPMAP1;

    /* 0x1A8 : DEV_FMAP */
    union {
        struct
        {
            uint32_t EPNO_FIFO0     : 4; /* [ 3: 0],       None,        0x0 */
            uint32_t Dir_FIFO0      : 2; /* [ 5: 4],       None,        0x0 */
            uint32_t reserved_6_7   : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t EPNO_FIFO1     : 4; /* [11: 8],       None,        0x0 */
            uint32_t Dir_FIFO1      : 2; /* [13:12],       None,        0x0 */
            uint32_t reserved_14_15 : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t EPNO_FIFO2     : 4; /* [19:16],       None,        0x0 */
            uint32_t Dir_FIFO2      : 2; /* [21:20],       None,        0x0 */
            uint32_t reserved_22_23 : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t EPNO_FIFO3     : 4; /* [27:24],       None,        0x0 */
            uint32_t Dir_FIFO3      : 2; /* [29:28],       None,        0x0 */
            uint32_t reserved_30_31 : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FMAP;

    /* 0x1AC : DEV_FCFG */
    union {
        struct
        {
            uint32_t BLK_TYP_F0     : 2; /* [ 1: 0],       None,        0x0 */
            uint32_t BLKNO_F0       : 2; /* [ 3: 2],       None,        0x0 */
            uint32_t BLKSZ_F0       : 1; /* [    4],       None,        0x0 */
            uint32_t EN_F0          : 1; /* [    5],       None,        0x0 */
            uint32_t reserved_6_7   : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t BLK_TYP_F1     : 2; /* [ 9: 8],       None,        0x0 */
            uint32_t BLKNO_F1       : 2; /* [11:10],       None,        0x0 */
            uint32_t BLKSZ_F1       : 1; /* [   12],       None,        0x0 */
            uint32_t EN_F1          : 1; /* [   13],       None,        0x0 */
            uint32_t reserved_14_15 : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t BLK_TYP_F2     : 2; /* [17:16],       None,        0x0 */
            uint32_t BLKNO_F2       : 2; /* [19:18],       None,        0x0 */
            uint32_t BLKSZ_F2       : 1; /* [   20],       None,        0x0 */
            uint32_t EN_F2          : 1; /* [   21],       None,        0x0 */
            uint32_t reserved_22_23 : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t BLK_TYP_F3     : 2; /* [25:24],       None,        0x0 */
            uint32_t BLKNO_F3       : 2; /* [27:26],       None,        0x0 */
            uint32_t BLKSZ_F3       : 1; /* [   28],       None,        0x0 */
            uint32_t EN_F3          : 1; /* [   29],       None,        0x0 */
            uint32_t reserved_30_31 : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FCFG;

    /* 0x1B0 : DEV_FIBC0 */
    union {
        struct
        {
            uint32_t BC_F0          : 11; /* [10: 0],       None,        0x0 */
            uint32_t rsvdp          : 1;  /* [   11],       None,        0x0 */
            uint32_t FFRST0_HOV     : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FIBC0;

    /* 0x1B4 : DEV_FIBC1 */
    union {
        struct
        {
            uint32_t BC_F1          : 11; /* [10: 0],       None,        0x0 */
            uint32_t reserved_11    : 1;  /* [   11],       rsvd,        0x0 */
            uint32_t FFRST1_HOV     : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FIBC1;

    /* 0x1B8 : DEV_FIBC2 */
    union {
        struct
        {
            uint32_t BC_F2          : 11; /* [10: 0],       None,        0x0 */
            uint32_t reserved_11    : 1;  /* [   11],       rsvd,        0x0 */
            uint32_t FFRST2_HOV     : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FIBC2;

    /* 0x1BC : DEV_FIBC3 */
    union {
        struct
        {
            uint32_t BC_F3      : 11; /* [10: 0],       None,        0x0 */
            uint32_t rsvdp      : 1;  /* [   11],       None,        0x0 */
            uint32_t FFRST3_HOV : 1;  /* [   12],       None,        0x0 */
            uint32_t rsvd_31_13 : 19; /* [31:13],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FIBC3;

    /* 0x1C0 : DMA_TFN */
    union {
        struct
        {
            uint32_t ACC_F0_HOV     : 1;  /* [    0],       None,        0x0 */
            uint32_t ACC_F1_HOV     : 1;  /* [    1],       None,        0x0 */
            uint32_t ACC_F2_HOV     : 1;  /* [    2],       None,        0x0 */
            uint32_t ACC_F3_HOV     : 1;  /* [    3],       None,        0x0 */
            uint32_t ACC_CXF_HOV    : 1;  /* [    4],       None,        0x0 */
            uint32_t ACC_F4_HOV     : 1;  /* [    5],       None,        0x0 */
            uint32_t ACC_F5_HOV     : 1;  /* [    6],       None,        0x0 */
            uint32_t ACC_F6_HOV     : 1;  /* [    7],       None,        0x0 */
            uint32_t ACC_F7_HOV     : 1;  /* [    8],       None,        0x0 */
            uint32_t ACC_F8_HOV     : 1;  /* [    9],       None,        0x0 */
            uint32_t ACC_F9_HOV     : 1;  /* [   10],       None,        0x0 */
            uint32_t ACC_F10_HOV    : 1;  /* [   11],       None,        0x0 */
            uint32_t ACC_F11_HOV    : 1;  /* [   12],       None,        0x0 */
            uint32_t ACC_F12_HOV    : 1;  /* [   13],       None,        0x0 */
            uint32_t ACC_F13_HOV    : 1;  /* [   14],       None,        0x0 */
            uint32_t ACC_F14_HOV    : 1;  /* [   15],       None,        0x0 */
            uint32_t ACC_F15_HOV    : 1;  /* [   16],       None,        0x0 */
            uint32_t reserved_17_31 : 15; /* [31:17],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_TFN;

    /* 0x1C4 : DMA_CPS0 */
    union {
        struct
        {
            uint32_t AWCHACHE_HOV   : 4;  /* [ 3: 0],       None,        0x0 */
            uint32_t AWPORT_HOV     : 3;  /* [ 6: 4],       None,        0x0 */
            uint32_t AWLOCK_HOV     : 2;  /* [ 8: 7],       None,        0x0 */
            uint32_t ARCACHE_HOV    : 4;  /* [12: 9],       None,        0x0 */
            uint32_t ARPORT_HOV     : 3;  /* [15:13],       None,        0x0 */
            uint32_t ARLOCK_HOV     : 2;  /* [17:16],       None,        0x0 */
            uint32_t BUF_LD_EN_HOV  : 1;  /* [   18],       None,        0x0 */
            uint32_t DST_WD_HOV     : 1;  /* [   19],       None,        0x0 */
            uint32_t reserved_20_31 : 12; /* [31:20],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_CPS0;

    /* 0x1C8 : DMA_CPS1 */
    union {
        struct
        {
            uint32_t DMA_START_HOV        : 1;  /* [    0],       None,        0x0 */
            uint32_t DMA_TYPE_HOV         : 1;  /* [    1],       None,        0x0 */
            uint32_t DMA_IO_HOV           : 1;  /* [    2],       None,        0x0 */
            uint32_t DMA_ABORT_HOV        : 1;  /* [    3],       None,        0x0 */
            uint32_t CLRFIFO_DMAABORT_HOV : 1;  /* [    4],       None,        0x0 */
            uint32_t reserved_5_7         : 3;  /* [ 7: 5],       rsvd,        0x0 */
            uint32_t DMA_LEN_HOV          : 17; /* [24: 8],       None,        0x0 */
            uint32_t R_HPORT_HOV          : 4;  /* [28:25],       None,        0x0 */
            uint32_t UNDEF_LEN_BURST_HOV  : 1;  /* [   29],       None,        0x0 */
            uint32_t L1_WAKEUP            : 1;  /* [   30],       None,        0x0 */
            uint32_t DevPhy_Suspend_HOV   : 1;  /* [   31],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_CPS1;

    /* 0x1CC : DMA_CPS2 */
    union {
        struct
        {
            uint32_t DMA_MADDR_HOV : 32; /* [31: 0],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_CPS2;

    /* 0x1D0 : DMA_CPS3 */
    union {
        struct
        {
            uint32_t SETUP_CMD_RPORT : 32; /* [31: 0],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_CPS3;

    /* 0x1D4 : DMA_CPS4 */
    union {
        struct
        {
            uint32_t reserved_0_31 : 32; /* [31: 0],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_CPS4;

    /* 0x1D8 : DEV_FMAP2 */
    union {
        struct
        {
            uint32_t EPNO_FIFO4     : 4; /* [ 3: 0],       None,        0x0 */
            uint32_t Dir_FIFO4      : 2; /* [ 5: 4],       None,        0x0 */
            uint32_t reserved_6_7   : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t EPNO_FIFO5     : 4; /* [11: 8],       None,        0x0 */
            uint32_t Dir_FIFO5      : 2; /* [13:12],       None,        0x0 */
            uint32_t reserved_14_15 : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t EPNO_FIFO6     : 4; /* [19:16],       None,        0x0 */
            uint32_t Dir_FIFO6      : 2; /* [21:20],       None,        0x0 */
            uint32_t reserved_22_23 : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t EPNO_FIFO7     : 4; /* [27:24],       None,        0x0 */
            uint32_t Dir_FIFO7      : 2; /* [29:28],       None,        0x0 */
            uint32_t reserved_30_31 : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FMAP2;

    /* 0x1DC : DEV_FCFG2 */
    union {
        struct
        {
            uint32_t BLK_TYP_F4     : 2; /* [ 1: 0],       None,        0x0 */
            uint32_t BLKNO_F4       : 2; /* [ 3: 2],       None,        0x0 */
            uint32_t BLKSZ_F4       : 1; /* [    4],       None,        0x0 */
            uint32_t EN_F4          : 1; /* [    5],       None,        0x0 */
            uint32_t reserved_6_7   : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t BLK_TYP_F5     : 2; /* [ 9: 8],       None,        0x0 */
            uint32_t BLKNO_F5       : 2; /* [11:10],       None,        0x0 */
            uint32_t BLKSZ_F5       : 1; /* [   12],       None,        0x0 */
            uint32_t EN_F5          : 1; /* [   13],       None,        0x0 */
            uint32_t reserved_14_15 : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t BLK_TYP_F6     : 2; /* [17:16],       None,        0x0 */
            uint32_t BLKNO_F6       : 2; /* [19:18],       None,        0x0 */
            uint32_t BLKSZ_F6       : 1; /* [   20],       None,        0x0 */
            uint32_t EN_F6          : 1; /* [   21],       None,        0x0 */
            uint32_t reserved_22_23 : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t BLK_TYP_F7     : 2; /* [25:24],       None,        0x0 */
            uint32_t BLKNO_F7       : 2; /* [27:26],       None,        0x0 */
            uint32_t BLKSZ_F7       : 1; /* [   28],       None,        0x0 */
            uint32_t EN_F7          : 1; /* [   29],       None,        0x0 */
            uint32_t reserved_30_31 : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FCFG2;

    /* 0x1E0 : DEV_FMAP3 */
    union {
        struct
        {
            uint32_t EPNO_FIFO8     : 4; /* [ 3: 0],       None,        0x0 */
            uint32_t Dir_FIFO8      : 2; /* [ 5: 4],       None,        0x0 */
            uint32_t reserved_6_7   : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t EPNO_FIFO9     : 4; /* [11: 8],       None,        0x0 */
            uint32_t Dir_FIFO9      : 2; /* [13:12],       None,        0x0 */
            uint32_t reserved_14_15 : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t EPNO_FIFO10    : 4; /* [19:16],       None,        0x0 */
            uint32_t Dir_FIFO10     : 2; /* [21:20],       None,        0x0 */
            uint32_t reserved_22_23 : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t EPNO_FIFO11    : 4; /* [27:24],       None,        0x0 */
            uint32_t Dir_FIFO11     : 2; /* [29:28],       None,        0x0 */
            uint32_t reserved_30_31 : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FMAP3;

    /* 0x1E4 : DEV_FCFG3 */
    union {
        struct
        {
            uint32_t BLK_TYP_F8     : 2; /* [ 1: 0],       None,        0x0 */
            uint32_t BLKNO_F8       : 2; /* [ 3: 2],       None,        0x0 */
            uint32_t BLKSZ_F8       : 1; /* [    4],       None,        0x0 */
            uint32_t EN_F8          : 1; /* [    5],       None,        0x0 */
            uint32_t reserved_6_7   : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t BLK_TYP_F9     : 2; /* [ 9: 8],       None,        0x0 */
            uint32_t BLKNO_F9       : 2; /* [11:10],       None,        0x0 */
            uint32_t BLKSZ_F9       : 1; /* [   12],       None,        0x0 */
            uint32_t EN_F9          : 1; /* [   13],       None,        0x0 */
            uint32_t reserved_14_15 : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t BLK_TYP_F10    : 2; /* [17:16],       None,        0x0 */
            uint32_t BLKNO_F10      : 2; /* [19:18],       None,        0x0 */
            uint32_t BLKSZ_F10      : 1; /* [   20],       None,        0x0 */
            uint32_t EN_F10         : 1; /* [   21],       None,        0x0 */
            uint32_t reserved_22_23 : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t BLK_TYP_F11    : 2; /* [25:24],       None,        0x0 */
            uint32_t BLKNO_F11      : 2; /* [27:26],       None,        0x0 */
            uint32_t BLKSZ_F11      : 1; /* [   28],       None,        0x0 */
            uint32_t EN_F11         : 1; /* [   29],       None,        0x0 */
            uint32_t reserved_30_31 : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FCFG3;

    /* 0x1E8 : DEV_FMAP4 */
    union {
        struct
        {
            uint32_t EPNO_FIFO12    : 4; /* [ 3: 0],       None,        0x0 */
            uint32_t Dir_FIFO12     : 2; /* [ 5: 4],       None,        0x0 */
            uint32_t reserved_6_7   : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t EPNO_FIFO13    : 4; /* [11: 8],       None,        0x0 */
            uint32_t Dir_FIFO13     : 2; /* [13:12],       None,        0x0 */
            uint32_t reserved_14_15 : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t EPNO_FIFO14    : 4; /* [19:16],       None,        0x0 */
            uint32_t Dir_FIFO14     : 2; /* [21:20],       None,        0x0 */
            uint32_t reserved_22_23 : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t EPNO_FIFO15    : 4; /* [27:24],       None,        0x0 */
            uint32_t Dir_FIFO15     : 2; /* [29:28],       None,        0x0 */
            uint32_t reserved_30_31 : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FMAP4;

    /* 0x1EC : DEV_FCFG4 */
    union {
        struct
        {
            uint32_t BLK_TYP_F12    : 2; /* [ 1: 0],       None,        0x0 */
            uint32_t BLKNO_F12      : 2; /* [ 3: 2],       None,        0x0 */
            uint32_t BLKSZ_F12      : 1; /* [    4],       None,        0x0 */
            uint32_t EN_F12         : 1; /* [    5],       None,        0x0 */
            uint32_t reserved_6_7   : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t BLK_TYP_F13    : 2; /* [ 9: 8],       None,        0x0 */
            uint32_t BLKNO_F13      : 2; /* [11:10],       None,        0x0 */
            uint32_t BLKSZ_F13      : 1; /* [   12],       None,        0x0 */
            uint32_t EN_F13         : 1; /* [   13],       None,        0x0 */
            uint32_t reserved_14_15 : 2; /* [15:14],       rsvd,        0x0 */
            uint32_t BLK_TYP_F14    : 2; /* [17:16],       None,        0x0 */
            uint32_t BLKNO_F14      : 2; /* [19:18],       None,        0x0 */
            uint32_t BLKSZ_F14      : 1; /* [   20],       None,        0x0 */
            uint32_t EN_F14         : 1; /* [   21],       None,        0x0 */
            uint32_t reserved_22_23 : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t BLK_TYP_F15    : 2; /* [25:24],       None,        0x0 */
            uint32_t BLKNO_F15      : 2; /* [27:26],       None,        0x0 */
            uint32_t BLKSZ_F15      : 1; /* [   28],       None,        0x0 */
            uint32_t EN_F15         : 1; /* [   29],       None,        0x0 */
            uint32_t reserved_30_31 : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FCFG4;

    /* 0x1F0 : DEV_FIBC4 */
    union {
        struct
        {
            uint32_t BC_F4          : 11; /* [10: 0],       None,        0x0 */
            uint32_t reserved_11    : 1;  /* [   11],       rsvd,        0x0 */
            uint32_t FFRST4_HOV     : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FIBC4;

    /* 0x1F4 : DEV_FIBC5 */
    union {
        struct
        {
            uint32_t BC_F5          : 11; /* [10: 0],       None,        0x0 */
            uint32_t reserved_11    : 1;  /* [   11],       rsvd,        0x0 */
            uint32_t FFRST5_HOV     : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FIBC5;

    /* 0x1F8 : DEV_FIBC6 */
    union {
        struct
        {
            uint32_t BC_F6          : 11; /* [10: 0],       None,        0x0 */
            uint32_t reserved_11    : 1;  /* [   11],       rsvd,        0x0 */
            uint32_t FFRST6_HOV     : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FIBC6;

    /* 0x1FC : DEV_FIBC7 */
    union {
        struct
        {
            uint32_t BC_F7          : 11; /* [10: 0],       None,        0x0 */
            uint32_t reserved_11    : 1;  /* [   11],       rsvd,        0x0 */
            uint32_t FFRST7_HOV     : 1;  /* [   12],       None,        0x0 */
            uint32_t reserved_13_31 : 19; /* [31:13],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_FIBC7;

    /* 0x200  reserved */
    uint8_t RESERVED0x200[256];

    /* 0x300 : VDMA_CXFPS1 */
    union {
        struct
        {
            uint32_t VDMA_START_CXF : 1;  /* [    0],       None,        0x0 */
            uint32_t VDMA_TYPE_CXF  : 1;  /* [    1],       None,        0x0 */
            uint32_t VDMA_IO_CXF    : 1;  /* [    2],       None,        0x0 */
            uint32_t reserved_3_7   : 5;  /* [ 7: 3],       rsvd,        0x0 */
            uint32_t VDMA_LEN_CXF   : 17; /* [24: 8],       None,        0x0 */
            uint32_t reserved_25_31 : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_CXFPS1;

    /* 0x304 : None */
    union {
        struct
        {
            uint32_t VDMA_MADDR_CXF : 32; /* [31: 0],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_CXFPS2;

    /* 0x308 : None */
    union {
        struct
        {
            uint32_t VDMA_START_F0  : 1;  /* [    0],       None,        0x0 */
            uint32_t VDMA_TYPE_F0   : 1;  /* [    1],       None,        0x0 */
            uint32_t VDMA_IO_F0     : 1;  /* [    2],       None,        0x0 */
            uint32_t reserved_3_7   : 5;  /* [ 7: 3],       rsvd,        0x0 */
            uint32_t VDMA_LEN_F0    : 17; /* [24: 8],       None,        0x0 */
            uint32_t reserved_25_31 : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_F0PS1;

    /* 0x30C : VDMA_F0PS2 */
    union {
        struct
        {
            uint32_t VDMA_MADDR_F0 : 32; /* [31: 0],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_F0PS2;

    /* 0x310 : VDMA_F1PS1 */
    union {
        struct
        {
            uint32_t VDMA_START_F1  : 1;  /* [    0],       None,        0x0 */
            uint32_t VDMA_TYPE_F1   : 1;  /* [    1],       None,        0x0 */
            uint32_t VDMA_IO_F1     : 1;  /* [    2],       None,        0x0 */
            uint32_t reserved_3_7   : 5;  /* [ 7: 3],       rsvd,        0x0 */
            uint32_t VDMA_LEN_F1    : 17; /* [24: 8],       None,        0x0 */
            uint32_t reserved_25_31 : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_F1PS1;

    /* 0x314 : VDMA_F1PS2 */
    union {
        struct
        {
            uint32_t VDMA_MADDR_F1 : 32; /* [31: 0],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_F1PS2;

    /* 0x318 : VDMA_F2PS1 */
    union {
        struct
        {
            uint32_t VDMA_START_F2  : 1;  /* [    0],       None,        0x0 */
            uint32_t VDMA_TYPE_F2   : 1;  /* [    1],       None,        0x0 */
            uint32_t VDMA_IO_F2     : 1;  /* [    2],       None,        0x0 */
            uint32_t reserved_3_7   : 5;  /* [ 7: 3],       rsvd,        0x0 */
            uint32_t VDMA_LEN_F2    : 17; /* [24: 8],       None,        0x0 */
            uint32_t reserved_25_31 : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_F2PS1;

    /* 0x31C : VDMA_F2PS2 */
    union {
        struct
        {
            uint32_t VDMA_MADDR_F2 : 32; /* [31: 0],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_F2PS2;

    /* 0x320 : VDMA_F3PS1 */
    union {
        struct
        {
            uint32_t VDMA_START_F3  : 1;  /* [    0],       None,        0x0 */
            uint32_t VDMA_TYPE_F3   : 1;  /* [    1],       None,        0x0 */
            uint32_t VDMA_IO_F3     : 1;  /* [    2],       None,        0x0 */
            uint32_t reserved_3_7   : 5;  /* [ 7: 3],       rsvd,        0x0 */
            uint32_t VDMA_LEN_F3    : 17; /* [24: 8],       None,        0x0 */
            uint32_t reserved_25_31 : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_F3PS1;

    /* 0x324 : VDMA_F3PS2 */
    union {
        struct
        {
            uint32_t VDMA_MADDR_F3 : 32; /* [31: 0],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_F3PS2;

    /* 0x328 : DEV_ISG3 */
    union {
        struct
        {
            uint32_t VDMA_CMPLT_CXF : 1; /* [    0],       None,        0x0 */
            uint32_t VDMA_CMPLT_F0  : 1; /* [    1],       None,        0x0 */
            uint32_t VDMA_CMPLT_F1  : 1; /* [    2],       None,        0x0 */
            uint32_t VDMA_CMPLT_F2  : 1; /* [    3],       None,        0x0 */
            uint32_t VDMA_CMPLT_F3  : 1; /* [    4],       None,        0x0 */
            uint32_t VDMA_CMPLT_F4  : 1; /* [    5],       None,        0x0 */
            uint32_t VDMA_CMPLT_F5  : 1; /* [    6],       None,        0x0 */
            uint32_t VDMA_CMPLT_F6  : 1; /* [    7],       None,        0x0 */
            uint32_t VDMA_CMPLT_F7  : 1; /* [    8],       None,        0x0 */
            uint32_t VDMA_CMPLT_F8  : 1; /* [    9],       None,        0x0 */
            uint32_t VDMA_CMPLT_F9  : 1; /* [   10],       None,        0x0 */
            uint32_t VDMA_CMPLT_F10 : 1; /* [   11],       None,        0x0 */
            uint32_t VDMA_CMPLT_F11 : 1; /* [   12],       None,        0x0 */
            uint32_t VDMA_CMPLT_F12 : 1; /* [   13],       None,        0x0 */
            uint32_t VDMA_CMPLT_F13 : 1; /* [   14],       None,        0x0 */
            uint32_t VDMA_CMPLT_F14 : 1; /* [   15],       None,        0x0 */
            uint32_t VDMA_ERROR_CXF : 1; /* [   16],       None,        0x0 */
            uint32_t VDMA_ERROR_F0  : 1; /* [   17],       None,        0x0 */
            uint32_t VDMA_ERROR_F1  : 1; /* [   18],       None,        0x0 */
            uint32_t VDMA_ERROR_F2  : 1; /* [   19],       None,        0x0 */
            uint32_t VDMA_ERROR_F3  : 1; /* [   20],       None,        0x0 */
            uint32_t VDMA_ERROR_F4  : 1; /* [   21],       None,        0x0 */
            uint32_t VDMA_ERROR_F5  : 1; /* [   22],       None,        0x0 */
            uint32_t VDMA_ERROR_F6  : 1; /* [   23],       None,        0x0 */
            uint32_t VDMA_ERROR_F7  : 1; /* [   24],       None,        0x0 */
            uint32_t VDMA_ERROR_F8  : 1; /* [   25],       None,        0x0 */
            uint32_t VDMA_ERROR_F9  : 1; /* [   26],       None,        0x0 */
            uint32_t VDMA_ERROR_F10 : 1; /* [   27],       None,        0x0 */
            uint32_t VDMA_ERROR_F11 : 1; /* [   28],       None,        0x0 */
            uint32_t VDMA_ERROR_F12 : 1; /* [   29],       None,        0x0 */
            uint32_t VDMA_ERROR_F13 : 1; /* [   30],       None,        0x0 */
            uint32_t VDMA_ERROR_F14 : 1; /* [   31],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_ISG3;

    /* 0x32C : DEV_MISG3 */
    union {
        struct
        {
            uint32_t MVDMA_CMPLT_CXF : 1; /* [    0],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F0  : 1; /* [    1],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F1  : 1; /* [    2],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F2  : 1; /* [    3],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F3  : 1; /* [    4],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F4  : 1; /* [    5],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F5  : 1; /* [    6],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F6  : 1; /* [    7],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F7  : 1; /* [    8],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F8  : 1; /* [    9],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F9  : 1; /* [   10],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F10 : 1; /* [   11],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F11 : 1; /* [   12],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F12 : 1; /* [   13],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F13 : 1; /* [   14],       None,        0x0 */
            uint32_t MVDMA_CMPLT_F14 : 1; /* [   15],       None,        0x0 */
            uint32_t MVDMA_ERROR_CXF : 1; /* [   16],       None,        0x0 */
            uint32_t MVDMA_ERROR_F0  : 1; /* [   17],       None,        0x0 */
            uint32_t MVDMA_ERROR_F1  : 1; /* [   18],       None,        0x0 */
            uint32_t MVDMA_ERROR_F2  : 1; /* [   19],       None,        0x0 */
            uint32_t MVDMA_ERROR_F3  : 1; /* [   20],       None,        0x0 */
            uint32_t MVDMA_ERROR_F4  : 1; /* [   21],       None,        0x0 */
            uint32_t MVDMA_ERROR_F5  : 1; /* [   22],       None,        0x0 */
            uint32_t MVDMA_ERROR_F6  : 1; /* [   23],       None,        0x0 */
            uint32_t MVDMA_ERROR_F7  : 1; /* [   24],       None,        0x0 */
            uint32_t MVDMA_ERROR_F8  : 1; /* [   25],       None,        0x0 */
            uint32_t MVDMA_ERROR_F9  : 1; /* [   26],       None,        0x0 */
            uint32_t MVDMA_ERROR_F10 : 1; /* [   27],       None,        0x0 */
            uint32_t MVDMA_ERROR_F11 : 1; /* [   28],       None,        0x0 */
            uint32_t MVDMA_ERROR_F12 : 1; /* [   29],       None,        0x0 */
            uint32_t MVDMA_ERROR_F13 : 1; /* [   30],       None,        0x0 */
            uint32_t MVDMA_ERROR_F14 : 1; /* [   31],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_MISG3;

    /* 0x330 : VDMA_CTRL */
    union {
        struct
        {
            uint32_t VDMA_EN       : 1;  /* [    0],       None,        0x0 */
            uint32_t reserved_1_31 : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_CTRL;

    /* 0x334 : LPM_CAP */
    union {
        struct
        {
            uint32_t LPM_WAKEUP_EN : 1;  /* [    0],       None,        0x0 */
            uint32_t reserved_1_31 : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } LPM_CAP;

    /* 0x338 : DEV_ISG4 */
    union {
        struct
        {
            uint32_t L1_INT         : 1;  /* [    0],       None,        0x0 */
            uint32_t reserved_1_15  : 15; /* [15: 1],       rsvd,        0x0 */
            uint32_t VDMA_CMPLT_F15 : 1;  /* [   16],       None,        0x0 */
            uint32_t reserved_17_23 : 7;  /* [23:17],       rsvd,        0x0 */
            uint32_t VDMA_ERROR_F15 : 1;  /* [   24],       None,        0x0 */
            uint32_t reserved_25_31 : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_ISG4;

    /* 0x33C : DEV_MISG4 */
    union {
        struct
        {
            uint32_t ML1_INT         : 1;  /* [    0],       None,        0x0 */
            uint32_t reserved_1_15   : 15; /* [15: 1],       rsvd,        0x0 */
            uint32_t MVDMA_CMPLT_F15 : 1;  /* [   16],       None,        0x0 */
            uint32_t reserved_17_23  : 7;  /* [23:17],       rsvd,        0x0 */
            uint32_t MVDMA_ERROR_F15 : 1;  /* [   24],       None,        0x0 */
            uint32_t reserved_25_31  : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DEV_MISG4;

    /* 0x340  reserved */
    uint8_t RESERVED0x340[16];

    /* 0x350 : VDMA_FnPS1 */
    union {
        struct
        {
            uint32_t VDMA_START_Fn  : 1;  /* [    0],       None,        0x0 */
            uint32_t VDMA_TYPE_Fn   : 1;  /* [    1],       None,        0x0 */
            uint32_t VDMA_IO_Fn     : 1;  /* [    2],       None,        0x0 */
            uint32_t reserved_3_7   : 5;  /* [ 7: 3],       rsvd,        0x0 */
            uint32_t VDMA_LEN_Fn    : 17; /* [24: 8],       None,        0x0 */
            uint32_t reserved_25_31 : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_FnPS1;

    /* 0x354 : VDMA_FnPS2 */
    union {
        struct
        {
            uint32_t VDMA_MADDR_Fn : 32; /* [31: 0],       None,        0x0 */
        } BF;
        uint32_t WORD;
    } VDMA_FnPS2;
};

typedef volatile struct usb_reg usb_reg_t;

#endif /* __USB_REG_H__ */
