/**
  **************************************************************************************
  * @file    reg_WWDG.h
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

#ifndef __WWDG_H__
#define __WWDG_H__

typedef struct
{
    __IO uint32_t  CR;  /* 0x00 WWDG_CR  Control register             */
    __IO uint32_t CFR;  /* 0x04 WWDG_CFR Configuration register       */
    __O  uint32_t IER;  /* 0x08 WWDG_IER Interrupt enable register    */
    __O  uint32_t IDR;  /* 0x0C WWDG_IDR Interrupt disable register   */
    __I  uint32_t IVS;  /* 0x10 WWDG_IVS Interrupt valid status       */
    __I  uint32_t RIF;  /* 0x14 WWDG_RIF Raw interrupt flag           */
    __I  uint32_t IFM;  /* 0x18 WWDG_IFM Interrupt flag masked        */
    __O  uint32_t ICR;  /* 0x1C WWDG_ICR Interrupt clear register     */
} WWDG_TypeDef;

/******************************************************************************/
/*                              暫存器內部位元定義                            */
/******************************************************************************/

/* #pragma anon_unions */

/****************** Bit definition for WWDG_CR register ************************/

#define WWDG_CR_WDGA_POS 7U
#define WWDG_CR_WDGA_MSK BIT(WWDG_CR_WDGA_POS)

#define WWDG_CR_T_POSS 0U
#define WWDG_CR_T_POSE 6U
#define WWDG_CR_T_MSK BITS(WWDG_CR_T_POSS,WWDG_CR_T_POSE)

/****************** Bit definition for WWDG_CFR register ************************/

#define WWDG_CFR_WDGTB_POS 7U
#define WWDG_CFR_WDGTB_MSK BIT(WWDG_CFR_WDGTB_POS)

#define WWDG_CFR_W_POSS 0U
#define WWDG_CFR_W_POSE 6U
#define WWDG_CFR_W_MSK BITS(WWDG_CFR_W_POSS,WWDG_CFR_W_POSE)

/****************** Bit definition for WWDG_IER register ************************/

#define WWDG_IER_EWIS_POS 7U
#define WWDG_IER_EWIS_MSK BIT(WWDG_IER_EWIS_POS)

/****************** Bit definition for WWDG_IDR register ************************/

#define WWDG_IDR_EWIS_POS 7U
#define WWDG_IDR_EWIS_MSK BIT(WWDG_IER_EWIS_POS)

/****************** Bit definition for WWDG_IVS register ************************/

#define WWDG_IVS_EWIS_POS 7U
#define WWDG_IVS_EWIS_MSK BIT(WWDG_IER_EWIS_POS)

/****************** Bit definition for WWDG_RIF register ************************/

#define WWDG_RIF_EWIS_POS 7U
#define WWDG_RIF_EWIS_MSK BIT(WWDG_IER_EWIS_POS)

/****************** Bit definition for WWDG_IFM register ************************/

#define WWDG_IFM_EWIS_POS 7U
#define WWDG_IFM_EWIS_MSK BIT(WWDG_IER_EWIS_POS)

/****************** Bit definition for WWDG_ICR register ************************/

#define WWDG_ICR_EWIS_POS 7U
#define WWDG_ICR_EWIS_MSK BIT(WWDG_IER_EWIS_POS)


#else
/* */
#endif
