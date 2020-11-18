/**
  **************************************************************************************
  * @file    REG_FC.h
  * @brief   FC Head File
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

#ifndef __fc_H__
#define __fc_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
/* #pragma anon_unions */

/****************** Bit definition for FC_CMD register ************************/

#define  FC_CMD_FC_CMD_POSS  0U 
#define  FC_CMD_FC_CMD_POSE  7U 
#define  FC_CMD_FC_CMD_MSK  BITS(FC_CMD_FC_CMD_POSS,FC_CMD_FC_CMD_POSE)

/****************** Bit definition for FC_PA register ************************/

#define  FC_PA_PCNT_POSS  25U 
#define  FC_PA_PCNT_POSE  31U 
#define  FC_PA_PCNT_MSK  BITS(FC_PA_PCNT_POSS,FC_PA_PCNT_POSE)

#define  FC_PA_IFREN_POS  24U 
#define  FC_PA_IFREN_MSK  BIT(FC_PA_IFREN_POS)

#define  FC_PA_PROG_ADDR_POSS  0U 
#define  FC_PA_PROG_ADDR_POSE  23U 
#define  FC_PA_PROG_ADDR_MSK  BITS(FC_PA_PROG_ADDR_POSS,FC_PA_PROG_ADDR_POSE)

/****************** Bit definition for FC_PLD register ************************/

#define  FC_PLD_PROG_DATA_L_POSS  0U 
#define  FC_PLD_PROG_DATA_L_POSE  31U 
#define  FC_PLD_PROG_DATA_L_MSK  BITS(FC_PLD_PROG_DATA_L_POSS,FC_PLD_PROG_DATA_L_POSE)

/****************** Bit definition for FC_PHD register ************************/

#define  FC_PHD_PROG_DATA_H_POSS  0U 
#define  FC_PHD_PROG_DATA_H_POSE  31U 
#define  FC_PHD_PROG_DATA_H_MSK  BITS(FC_PHD_PROG_DATA_H_POSS,FC_PHD_PROG_DATA_H_POSE)

/****************** Bit definition for FC_CON register ************************/

#define  FC_CON_SLEEP_POS  9U 
#define  FC_CON_SLEEP_MSK  BIT(FC_CON_SLEEP_POS)

#define  FC_CON_PFEN_POS  8U 
#define  FC_CON_PFEN_MSK  BIT(FC_CON_PFEN_POS)

#define  FC_CON_WAIT_POSS  0U 
#define  FC_CON_WAIT_POSE  1U 
#define  FC_CON_WAIT_MSK  BITS(FC_CON_WAIT_POSS,FC_CON_WAIT_POSE)

/****************** Bit definition for FC_STAT register ************************/

#define  FC_STAT_OPVD_POS  2U 
#define  FC_STAT_OPVD_MSK  BIT(FC_STAT_OPVD_POS)

#define  FC_STAT_MUNP2_POS  1U 
#define  FC_STAT_MUNP2_MSK  BIT(FC_STAT_MUNP2_POS)

#define  FC_STAT_MUNP1_POS  0U 
#define  FC_STAT_MUNP1_MSK  BIT(FC_STAT_MUNP1_POS)

/****************** Bit definition for FC_UPL register ************************/

#define  FC_UPL_UPL_POSS  0U 
#define  FC_UPL_UPL_POSE  31U 
#define  FC_UPL_UPL_MSK  BITS(FC_UPL_UPL_POSS,FC_UPL_UPL_POSE)

/****************** Bit definition for FC_UPH register ************************/

#define  FC_UPH_UPH_POSS  0U 
#define  FC_UPH_UPH_POSE  31U 
#define  FC_UPH_UPH_MSK  BITS(FC_UPH_UPH_POSS,FC_UPH_UPH_POSE)

/****************** Bit definition for FC_OP_TRIM register ************************/

#define  FC_OP_TRIM_BGTRIMVD_POSS  24U 
#define  FC_OP_TRIM_BGTRIMVD_POSE  31U 
#define  FC_OP_TRIM_BGTRIMVD_MSK  BITS(FC_OP_TRIM_BGTRIMVD_POSS,FC_OP_TRIM_BGTRIMVD_POSE)

#define  FC_OP_TRIM_BGTRIM_POSS  16U 
#define  FC_OP_TRIM_BGTRIM_POSE  23U 
#define  FC_OP_TRIM_BGTRIM_MSK  BITS(FC_OP_TRIM_BGTRIM_POSS,FC_OP_TRIM_BGTRIM_POSE)

#define  FC_OP_TRIM_HRCTRIMVD_POSS  8U 
#define  FC_OP_TRIM_HRCTRIMVD_POSE  15U 
#define  FC_OP_TRIM_HRCTRIMVD_MSK  BITS(FC_OP_TRIM_HRCTRIMVD_POSS,FC_OP_TRIM_HRCTRIMVD_POSE)

#define  FC_OP_TRIM_HRCTRIM_POSS  0U 
#define  FC_OP_TRIM_HRCTRIM_POSE  7U 
#define  FC_OP_TRIM_HRCTRIM_MSK  BITS(FC_OP_TRIM_HRCTRIM_POSS,FC_OP_TRIM_HRCTRIM_POSE)

/****************** Bit definition for FC_OP_PRT2L register ************************/

#define  FC_OP_PRT2L_PRTLV2L_POSS  0U 
#define  FC_OP_PRT2L_PRTLV2L_POSE  31U 
#define  FC_OP_PRT2L_PRTLV2L_MSK  BITS(FC_OP_PRT2L_PRTLV2L_POSS,FC_OP_PRT2L_PRTLV2L_POSE)

/****************** Bit definition for FC_OP_PRT2H register ************************/

#define  FC_OP_PRT2H_PRTLV2H_POSS  0U 
#define  FC_OP_PRT2H_PRTLV2H_POSE  31U 
#define  FC_OP_PRT2H_PRTLV2H_MSK  BITS(FC_OP_PRT2H_PRTLV2H_POSS,FC_OP_PRT2H_PRTLV2H_POSE)

/****************** Bit definition for FC_OP_PRT1L register ************************/

#define  FC_OP_PRT1L_PRTLV1L_POSS  0U 
#define  FC_OP_PRT1L_PRTLV1L_POSE  31U 
#define  FC_OP_PRT1L_PRTLV1L_MSK  BITS(FC_OP_PRT1L_PRTLV1L_POSS,FC_OP_PRT1L_PRTLV1L_POSE)

/****************** Bit definition for FC_OP_PRT1H register ************************/

#define  FC_OP_PRT1H_PRTLV1H_POSS  0U 
#define  FC_OP_PRT1H_PRTLV1H_POSE  31U 
#define  FC_OP_PRT1H_PRTLV1H_MSK  BITS(FC_OP_PRT1H_PRTLV1H_POSS,FC_OP_PRT1H_PRTLV1H_POSE)

/****************** Bit definition for FC_OP_REMAP register ************************/

#define  FC_OP_REMAP_HREMAP_POSS  8U 
#define  FC_OP_REMAP_HREMAP_POSE  15U 
#define  FC_OP_REMAP_HREMAP_MSK  BITS(FC_OP_REMAP_HREMAP_POSS,FC_OP_REMAP_HREMAP_POSE)

#define  FC_OP_REMAP_SREMAP_POSS  4U 
#define  FC_OP_REMAP_SREMAP_POSE  5U 
#define  FC_OP_REMAP_SREMAP_MSK  BITS(FC_OP_REMAP_SREMAP_POSS,FC_OP_REMAP_SREMAP_POSE)

#define  FC_OP_REMAP_SEFBASE_POSS  0U 
#define  FC_OP_REMAP_SEFBASE_POSE  3U 
#define  FC_OP_REMAP_SEFBASE_MSK  BITS(FC_OP_REMAP_SEFBASE_POSS,FC_OP_REMAP_SEFBASE_POSE)

typedef struct
{
  __IO uint32_t CMD;
  __IO uint32_t PA;
  __IO uint32_t PLD;
  __IO uint32_t PHD;
  __IO uint32_t CON;
  __I uint32_t STAT;
  uint32_t RESERVED0[2] ;
  __IO uint32_t UPL;
  __IO uint32_t UPH;
  uint32_t RESERVED1[2] ;
  __I uint32_t OP_TRIM;
  uint32_t RESERVED2[4] ;
//  uint32_t ADCTRIM_1V;
//  uint32_t ADCTRIM_2V;
//  uint32_t RESERVED3;
    
  uint32_t ADCTRIM_VDD5V_VREF5V;
  uint32_t ADCTRIM_VDD3V3_VREF3V3;
  uint32_t ADCTRIM_VDD5V_VREF2V5;
  __I uint32_t OP_PRT2L;
  __I uint32_t OP_PRT2H;
  __I uint32_t OP_PRT1L;
  __I uint32_t OP_PRT1H;
  __I uint32_t OP_REMAP;
} FC_TypeDef;





#endif
