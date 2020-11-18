/**
  **************************************************************************************
  * @file    REG_CMP.h
  * @brief   CMP Head File
  *
  * @version V0.01
  * @data    12/3/2018
  * @author  Eastsoft MCU Software Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#ifndef __CMP_H__
#define __CMP_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
/* #pragma anon_unions */

/****************** Bit definition for CMP_CON register ************************/

#define  CMP_CON_REFON_POS  4U 
#define  CMP_CON_REFON_MSK  BIT(CMP_CON_REFON_POS)

#define  CMP_CON_CMPON2_POS  1U 
#define  CMP_CON_CMPON2_MSK  BIT(CMP_CON_CMPON2_POS)

#define  CMP_CON_CMPON1_POS  0U 
#define  CMP_CON_CMPON1_MSK  BIT(CMP_CON_CMPON1_POS)

/****************** Bit definition for CMP_CFG1 register ************************/

#define  CMP_CFG1_RS_POSS  4U 
#define  CMP_CFG1_RS_POSE  5U 
#define  CMP_CFG1_RS_MSK  BITS(CMP_CFG1_RS_POSS,CMP_CFG1_RS_POSE)

#define  CMP_CFG1_FEN_POS  3U 
#define  CMP_CFG1_FEN_MSK  BIT(CMP_CFG1_FEN_POS)

#define  CMP_CFG1_PSEN_POS  2U 
#define  CMP_CFG1_PSEN_MSK  BIT(CMP_CFG1_PSEN_POS)

#define  CMP_CFG1_INSEL_POS  1U 
#define  CMP_CFG1_INSEL_MSK  BIT(CMP_CFG1_INSEL_POS)

#define  CMP_CFG1_IPSEL_POS  0U 
#define  CMP_CFG1_IPSEL_MSK  BIT(CMP_CFG1_IPSEL_POS)

/****************** Bit definition for CMP_CFG2 register ************************/

#define  CMP_CFG2_RS_POSS  4U 
#define  CMP_CFG2_RS_POSE  5U 
#define  CMP_CFG2_RS_MSK  BITS(CMP_CFG2_RS_POSS,CMP_CFG2_RS_POSE)

#define  CMP_CFG2_FEN_POS  3U 
#define  CMP_CFG2_FEN_MSK  BIT(CMP_CFG1_FEN_POS)

#define  CMP_CFG2_PSEN_POS  2U 
#define  CMP_CFG2_PSEN_MSK  BIT(CMP_CFG1_PSEN_POS)

#define  CMP_CFG2_INSEL_POS  1U 
#define  CMP_CFG2_INSEL_MSK  BIT(CMP_CFG1_INSEL_POS)

#define  CMP_CFG2_IPSEL_POS  0U 
#define  CMP_CFG2_IPSEL_MSK  BIT(CMP_CFG1_IPSEL_POS)

/****************** Bit definition for CMP_RULT register ************************/

#define  CMP_RULT_CMPO2_POS  1U 
#define  CMP_RULT_CMPO2_MSK  BIT(CMP_RULT_CMPO2_POS)

#define  CMP_RULT_CMPO1_POS  0U 
#define  CMP_RULT_CMPO1_MSK  BIT(CMP_RULT_CMPO1_POS)

typedef struct
{
  __IO uint32_t CON;
  __IO uint32_t CFG1;
  __IO uint32_t CFG2;
  uint32_t RESERVED0[2] ;
  __I uint32_t RULT;
} CMP_TypeDef;





#endif
