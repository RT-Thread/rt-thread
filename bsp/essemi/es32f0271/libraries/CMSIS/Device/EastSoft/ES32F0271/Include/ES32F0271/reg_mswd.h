/**
  **************************************************************************************
  * @file    reg_MSWD.h
  * @brief   WWDG Head File
  *
  * @version V1.00.01
  * @data    19/10/2018
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#ifndef __MSWD_H__
#define __MSWD_H__

typedef struct
{
    __IO uint32_t   CFG;                // 0x00 SW_CFG                  Serial Wire Configure Register
    __IO uint32_t   JTAG2SWD;           // 0x04 SW_JTAG2SW              Serial Wire JTAG2SWD Register
    __IO uint32_t   LINERESET;          // 0x08 SW_LINERESET            Serial Wire LINERESET Resister
    __O  uint32_t   STS;                // 0x0C SW_STS                  Serial Wire STATUS Register
    __IO uint32_t   DP_IDR_ABORT;       // 0x10 SW_DP_IDR_ABORT         Serial Wire DP R-IDR W-ABORT Register
    __IO uint32_t   DP_CSR_WCR;         // 0x14 SW_DP_CSR_WCR           Serial Wire DP R-CSR W-WCR Register
    __IO uint32_t   DP_RESEND_SELECT;   // 0x18 SW_DP_RESEND_SELECT     Serial Wire DP R-RESEND W-SELECT Register
    __IO uint32_t   DP_RDBUF_ROUTESEL;  // 0x1C SW_DP_RDBUF_ROUTESEL    Serial Wire DP R-RDBUF W-ROUTESEL Register
    __IO uint32_t   AP_CSW;             // 0x20 SW_AP_CSW               Serial Wire AP CSW Register
    __IO uint32_t   AP_TAR;             // 0x24 SW_AP_TAR               Serial Wire AP TAR Register
    __IO uint32_t   AP_DRW;             // 0x28 SW_AP_DRW               Serial Wire AP DRW Register
    __IO uint32_t   AP_BD0;             // 0x2C SW_AP_BD0               Serial Wire AP BD0 Register
    __IO uint32_t   AP_BD1;             // 0x30 SW_AP_BD1               Serial Wire AP BD1 Register
    __IO uint32_t   AP_BD2;             // 0x34 SW_AP_BD2               Serial Wire AP BD2 Register
    __IO uint32_t   AP_BD3;             // 0x38 SW_AP_BD3               Serial Wire AP BD3 Register
    __IO uint32_t   AP_CFG;             // 0x3C SW_AP_CFG               Serial Wire AP CFG Register
    __IO uint32_t   AP_BASE;            // 0x40 SW_AP_BASE              Serial Wire AP BASE Register
    __IO uint32_t   AP_IDR;             // 0x44 SW_AP_IDR               Serial Wire AP IDR Register
         uint32_t   RES0;               // 0x48
         uint32_t   RES1;               // 0x4C
    __IO uint32_t   ISP_CMD;            // 0x50 SW_ISP_CMD              Serial Wire ISP Command Register
    __IO uint32_t   ISP_DAT;            // 0x54 SW_ISP_DAT              Serial Wire ISP Data Register
} MSWD_TypeDef;

/******************************************************************************/
/*                              暫存器內部位元定義                            */
/******************************************************************************/

/* #pragma anon_unions */

/****************** Bit definition for WWDG_CR register ************************/




#else
/* */
#endif
