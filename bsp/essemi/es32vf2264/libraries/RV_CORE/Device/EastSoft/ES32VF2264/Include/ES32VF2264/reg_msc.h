/**********************************************************************************
 *
 * @file    reg_msc.h
 * @brief   MSC Head File
 *
 * @date    27 Dec. 2022
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          27 Dec. 2022    Lisq            the first version
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **********************************************************************************
 */

#ifndef __REG_MSC_H__
#define __REG_MSC_H__

/****************** Bit definition for MSC_FLASHKEY register ************************/

#define MSC_FLASHKEY_STATUS_POSS    0U
#define MSC_FLASHKEY_STATUS_POSE    1U
#define MSC_FLASHKEY_STATUS_MSK BITS(MSC_FLASHKEY_STATUS_POSS,MSC_FLASHKEY_STATUS_POSE)

/****************** Bit definition for MSC_INFOKEY register ************************/

#define MSC_INFOKEY_STATUS_POSS 0U
#define MSC_INFOKEY_STATUS_POSE 1U
#define MSC_INFOKEY_STATUS_MSK  BITS(MSC_INFOKEY_STATUS_POSS,MSC_INFOKEY_STATUS_POSE)

/****************** Bit definition for MSC_FLASHADDR register ************************/

#define MSC_FLASHADDR_IFREN_POS 18U
#define MSC_FLASHADDR_IFREN_MSK BIT(MSC_FLASHADDR_IFREN_POS)

#define MSC_FLASHADDR_ADDR_POSS 0U
#define MSC_FLASHADDR_ADDR_POSE 17U
#define MSC_FLASHADDR_ADDR_MSK  BITS(MSC_FLASHADDR_ADDR_POSS,MSC_FLASHADDR_ADDR_POSE)

/****************** Bit definition for MSC_FLASHFIFO register ************************/

#define MSC_FLASHFIFO_FIFO_POSS 0U
#define MSC_FLASHFIFO_FIFO_POSE 31U
#define MSC_FLASHFIFO_FIFO_MSK  BITS(MSC_FLASHFIFO_FIFO_POSS,MSC_FLASHFIFO_FIFO_POSE)

/****************** Bit definition for MSC_FLASHDR register ************************/

#define MSC_FLASHDR_DATA_POSS   0U
#define MSC_FLASHDR_DATA_POSE   31U
#define MSC_FLASHDR_DATA_MSK    BITS(MSC_FLASHDR_DATA_POSS,MSC_FLASHDR_DATA_POSE)

/****************** Bit definition for MSC_FLASHCMD register ************************/

#define MSC_FLASHCMD_CMD_POSS   0U
#define MSC_FLASHCMD_CMD_POSE   31U
#define MSC_FLASHCMD_CMD_MSK    BITS(MSC_FLASHCMD_CMD_POSS,MSC_FLASHCMD_CMD_POSE)

/****************** Bit definition for MSC_FLASHCR register ************************/

#define MSC_FLASHCR_PGSZ_POS    8U
#define MSC_FLASHCR_PGSZ_MSK    BIT(MSC_FLASHCR_PGSZ_POS)

#define MSC_FLASHCR_FIFODF_POS  7U
#define MSC_FLASHCR_FIFODF_MSK  BIT(MSC_FLASHCR_FIFODF_POS)

#define MSC_FLASHCR_FIFOEN_POS  5U
#define MSC_FLASHCR_FIFOEN_MSK  BIT(MSC_FLASHCR_FIFOEN_POS)

#define MSC_FLASHCR_FLASHREQ_POS    4U
#define MSC_FLASHCR_FLASHREQ_MSK    BIT(MSC_FLASHCR_FLASHREQ_POS)

#define MSC_FLASHCR_OTFEN_POS   2U
#define MSC_FLASHCR_OTFEN_MSK   BIT(MSC_FLASHCR_OTFEN_POS)

#define MSC_FLASHCR_IAPRST_POS  1U
#define MSC_FLASHCR_IAPRST_MSK  BIT(MSC_FLASHCR_IAPRST_POS)

#define MSC_FLASHCR_IAPEN_POS   0U
#define MSC_FLASHCR_IAPEN_MSK   BIT(MSC_FLASHCR_IAPEN_POS)

/****************** Bit definition for MSC_FLASHSR register ************************/

#define MSC_FLASHSR_UPCEUL_POS  25U
#define MSC_FLASHSR_UPCEUL_MSK  BIT(MSC_FLASHSR_UPCEUL_POS)

#define MSC_FLASHSR_MASEUL_POS  24U
#define MSC_FLASHSR_MASEUL_MSK  BIT(MSC_FLASHSR_MASEUL_POS)

#define MSC_FLASHSR_ADDERR_POS  23U
#define MSC_FLASHSR_ADDERR_MSK  BIT(MSC_FLASHSR_ADDERR_POS)

#define MSC_FLASHSR_UPCEDONE_POS    17U
#define MSC_FLASHSR_UPCEDONE_MSK    BIT(MSC_FLASHSR_UPCEDONE_POS)

#define MSC_FLASHSR_UPCEBUSY_POS    16U
#define MSC_FLASHSR_UPCEBUSY_MSK    BIT(MSC_FLASHSR_UPCEBUSY_POS)

#define MSC_FLASHSR_TIMEOUT_POS 7U
#define MSC_FLASHSR_TIMEOUT_MSK BIT(MSC_FLASHSR_TIMEOUT_POS)

#define MSC_FLASHSR_PROG_POS    6U
#define MSC_FLASHSR_PROG_MSK    BIT(MSC_FLASHSR_PROG_POS)

#define MSC_FLASHSR_SERA_POS    5U
#define MSC_FLASHSR_SERA_MSK    BIT(MSC_FLASHSR_SERA_POS)

#define MSC_FLASHSR_MASE_POS    4U
#define MSC_FLASHSR_MASE_MSK    BIT(MSC_FLASHSR_MASE_POS)

#define MSC_FLASHSR_WAE_POS 3U
#define MSC_FLASHSR_WAE_MSK BIT(MSC_FLASHSR_WAE_POS)

#define MSC_FLASHSR_WPE_POS 2U
#define MSC_FLASHSR_WPE_MSK BIT(MSC_FLASHSR_WPE_POS)

#define MSC_FLASHSR_BUSY_POS    1U
#define MSC_FLASHSR_BUSY_MSK    BIT(MSC_FLASHSR_BUSY_POS)

#define MSC_FLASHSR_FLASHACK_POS    0U
#define MSC_FLASHSR_FLASHACK_MSK    BIT(MSC_FLASHSR_FLASHACK_POS)

/****************** Bit definition for MSC_MEMWAIT register ************************/

#define MSC_MEMWAIT_SRAM_W_POSS 8U
#define MSC_MEMWAIT_SRAM_W_POSE 9U
#define MSC_MEMWAIT_SRAM_W_MSK  BITS(MSC_MEMWAIT_SRAM_W_POSS,MSC_MEMWAIT_SRAM_W_POSE)

#define MSC_MEMWAIT_FLASH_W_POSS    0U
#define MSC_MEMWAIT_FLASH_W_POSE    1U
#define MSC_MEMWAIT_FLASH_W_MSK BITS(MSC_MEMWAIT_FLASH_W_POSS,MSC_MEMWAIT_FLASH_W_POSE)

/****************** Bit definition for MSC_FLASHADDINV register ************************/

#define MSC_FLASHADDINV_ADDRINV_POSS    0U
#define MSC_FLASHADDINV_ADDRINV_POSE    17U
#define MSC_FLASHADDINV_ADDRINV_MSK BITS(MSC_FLASHADDINV_ADDRINV_POSS,MSC_FLASHADDINV_ADDRINV_POSE)

typedef struct
{
    __IO uint32_t FLASHKEY;
    __I uint32_t INFOKEY;
    __IO uint32_t FLASHADDR;
    __O uint32_t FLASHFIFO;
    __IO uint32_t FLASHDR;
    uint32_t RESERVED0 ;
    __O uint32_t FLASHCMD;
    __IO uint32_t FLASHCR;
    __I uint32_t FLASHSR;
    uint32_t RESERVED1 ;
    __IO uint32_t MEMWAIT;
    __IO uint32_t FLASHADDINV;
} MSC_TypeDef;





#endif /* __REG_MSC_H__ */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
