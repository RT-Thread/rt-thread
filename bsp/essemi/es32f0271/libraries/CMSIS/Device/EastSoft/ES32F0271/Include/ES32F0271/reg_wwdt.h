/**
  **************************************************************************************
  * @file    REG_WWDT.h
  * @brief   WWDT Head File
  *
  * @version V0.01
  * @date    4/12/2018
  * @author  Eastsoft MCU Software Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#ifndef __REG_WWDT_H__
#define __REG_WWDT_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
/* #pragma anon_unions */

/****************** Bit definition for WWDT_CON register ************************/

#define  WWDT_CON_WDGA_POS  7U 
#define  WWDT_CON_WDGA_MSK  BIT(WWDT_CON_WDGA_POS)

#define  WWDT_CON_T_POSS  0U 
#define  WWDT_CON_T_POSE  6U 
#define  WWDT_CON_T_MSK  BITS(WWDT_CON_T_POSS,WWDT_CON_T_POSE)

/****************** Bit definition for WWDT_CFG register ************************/

#define  WWDT_CFG_WDGTB_POSS  7U 
#define  WWDT_CFG_WDGTB_POSE  8U 
#define  WWDT_CFG_WDGTB_MSK  BITS(WWDT_CFG_WDGTB_POSS,WWDT_CFG_WDGTB_POSE)

#define  WWDT_CFG_W_POSS  0U 
#define  WWDT_CFG_W_POSE  6U 
#define  WWDT_CFG_W_MSK  BITS(WWDT_CFG_W_POSS,WWDT_CFG_W_POSE)

/****************** Bit definition for WWDT_IER register ************************/

#define  WWDT_IER_EWIS_POS  0U 
#define  WWDT_IER_EWIS_MSK  BIT(WWDT_IER_EWIS_POS)

/****************** Bit definition for WWDT_IDR register ************************/

#define  WWDT_IDR_EWIS_POS  0U 
#define  WWDT_IDR_EWIS_MSK  BIT(WWDT_IDR_EWIS_POS)

/****************** Bit definition for WWDT_IVS register ************************/

#define  WWDT_IVS_EWIS_POS  0U 
#define  WWDT_IVS_EWIS_MSK  BIT(WWDT_IVS_EWIS_POS)

/****************** Bit definition for WWDT_RIF register ************************/

#define  WWDT_RIF_EWIF_POS  0U 
#define  WWDT_RIF_EWIF_MSK  BIT(WWDT_RIF_EWIF_POS)

/****************** Bit definition for WWDT_IFM register ************************/

#define  WWDT_IFM_EWIM_POS  0U 
#define  WWDT_IFM_EWIM_MSK  BIT(WWDT_IFM_EWIM_POS)

/****************** Bit definition for WWDT_ICR register ************************/

#define  WWDT_ICR_EWIC_POS  0U 
#define  WWDT_ICR_EWIC_MSK  BIT(WWDT_ICR_EWIC_POS)

typedef struct
{
  __IO uint32_t CON;
  __IO uint32_t CFG;
  __O uint32_t IER;
  __O uint32_t IDR;
  __I uint32_t IVS;
  __I uint32_t RIF;
  __I uint32_t IFM;
  __O uint32_t ICR;
} WWDT_TypeDef;





#endif
