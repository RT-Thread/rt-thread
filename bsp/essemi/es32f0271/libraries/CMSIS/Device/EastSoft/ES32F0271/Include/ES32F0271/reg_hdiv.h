/**
  **************************************************************************************
  * @file    REG_HDIV.h
  * @brief   HDIV Head File
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

#ifndef __hdiv_H__
#define __hdiv_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
/* #pragma anon_unions */

/****************** Bit definition for HDIV_DIVDR register ************************/

#define  HDIV_DIVDR_DIVS_POSS  0U 
#define  HDIV_DIVDR_DIVS_POSE  31U 
#define  HDIV_DIVDR_DIVD_MSK  BITS(HDIV_DIVDR_DIVD_POSS,HDIV_DIVDR_DIVD_POSE)

/****************** Bit definition for HDIV_DIVSR register ************************/

#define  HDIV_DIVSR_DIVS_POSS  0U 
#define  HDIV_DIVSR_DIVS_POSE  31U 
#define  HDIV_DIVSR_DIVS_MSK  BITS(HDIV_DIVSR_DIVS_POSS,HDIV_DIVSR_DIVS_POSE)

/****************** Bit definition for HDIV_DIVQR register ************************/

#define  HDIV_DIVQR_DIVQ_POSS  0U 
#define  HDIV_DIVQR_DIVQ_POSE  31U 
#define  HDIV_DIVQR_DIVQ_MSK  BITS(HDIV_DIVQR_DIVQ_POSS,HDIV_DIVQR_DIVQ_POSE)

/****************** Bit definition for HDIV_DIVRR register ************************/

#define  HDIV_DIVRR_DIVR_POSS  0U 
#define  HDIV_DIVRR_DIVR_POSE  31U 
#define  HDIV_DIVRR_DIVR_MSK  BITS(HDIV_DIVRR_DIVR_POSS,HDIV_DIVRR_DIVR_POSE)

/****************** Bit definition for HDIV_DIVSTAT register ************************/

#define  HDIV_DIVSTAT_SIGN_POS  2U 
#define  HDIV_DIVSTAT_SIGN_MSK  BIT(HDIV_DIVSTAT_SIGN_POS)

#define  HDIV_DIVSTAT_DIV0_POS  1U 
#define  HDIV_DIVSTAT_DIV0_MSK  BIT(HDIV_DIVSTAT_DIV0_POS)

#define  HDIV_DIVSTAT_BUSY_POS  0U 
#define  HDIV_DIVSTAT_BUSY_MSK  BIT(HDIV_DIVSTAT_BUSY_POS)

typedef struct
{
  __IO uint32_t DIVDR;
  __IO uint32_t DIVSR;
  __I uint32_t DIVQR;
  __I uint32_t DIVRR;
  __I uint32_t DIVSTAT;
} HDIV_TypeDef;





#endif
