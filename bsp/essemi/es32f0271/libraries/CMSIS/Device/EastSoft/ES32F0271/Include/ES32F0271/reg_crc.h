/**
  **************************************************************************************
  * @file    REG_CRC.h
  * @brief   CRC Head File
  *
  * @version V0.01
  * @data    11/16/2018
  * @author  Eastsoft MCU Software Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#ifndef __CRC_H__
#define __CRC_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
/* #pragma anon_unions */

/****************** Bit definition for CRC_INIT register ************************/

#define  CRC_INIT_INIT_POSS  0U 
#define  CRC_INIT_INIT_POSE  31U 
#define  CRC_INIT_INIT_MSK  BITS(CRC_INIT_INIT_POSS,CRC_INIT_INIT_POSE)

/****************** Bit definition for CRC_POLY register ************************/

#define  CRC_POLY_POLY_POSS  0U 
#define  CRC_POLY_POLY_POSE  31U 
#define  CRC_POLY_POLY_MSK  BITS(CRC_POLY_POLY_POSS,CRC_POLY_POLY_POSE)

/****************** Bit definition for CRC_DATA register ************************/

#define  CRC_DATA_DATA_POSS  0U 
#define  CRC_DATA_DATA_POSE  31U 
#define  CRC_DATA_DATA_MSK  BITS(CRC_DATA_DATA_POSS,CRC_DATA_DATA_POSE)

/****************** Bit definition for CRC_COMP register ************************/

#define  CRC_COMP_COMP_POSS  0U 
#define  CRC_COMP_COMP_POSE  31U 
#define  CRC_COMP_COMP_MSK  BITS(CRC_COMP_COMP_POSS,CRC_COMP_COMP_POSE)

/****************** Bit definition for CRC_REMA register ************************/

#define  CRC_REMA_REMA_POSS  0U 
#define  CRC_REMA_REMA_POSE  31U 
#define  CRC_REMA_REMA_MSK  BITS(CRC_REMA_REMA_POSS,CRC_REMA_REMA_POSE)

/****************** Bit definition for CRC_CON register ************************/

#define  CRC_CON_DMA_POS  16U 
#define  CRC_CON_DMA_MSK  BIT(CRC_CON_DMA_POS)

#define  CRC_CON_MSB_POS  12U 
#define  CRC_CON_MSB_MSK  BIT(CRC_CON_MSB_POS)

#define  CRC_CON_REOUT_POS  10U 
#define  CRC_CON_REOUT_MSK  BIT(CRC_CON_REOUT_POS)

#define  CRC_CON_REIN_POS  8U 
#define  CRC_CON_REIN_MSK  BIT(CRC_CON_REIN_POS)

#define  CRC_CON_SIZE_POSS  4U 
#define  CRC_CON_SIZE_POSE  5U 
#define  CRC_CON_SIZE_MSK  BITS(CRC_CON_SIZE_POSS,CRC_CON_SIZE_POSE)

#define  CRC_CON_MODE_POSS  2U 
#define  CRC_CON_MODE_POSE  3U 
#define  CRC_CON_MODE_MSK  BITS(CRC_CON_MODE_POSS,CRC_CON_MODE_POSE)

#define  CRC_CON_RESET_POS  0U 
#define  CRC_CON_RESET_MSK  BIT(CRC_CON_RESET_POS)

/****************** Bit definition for CRC_DOUT register ************************/

#define  CRC_DOUT_DOUT_POSS  0U 
#define  CRC_DOUT_DOUT_POSE  31U 
#define  CRC_DOUT_DOUT_MSK  BITS(CRC_DOUT_DOUT_POSS,CRC_DOUT_DOUT_POSE)

/****************** Bit definition for CRC_DOUT_XOR register ************************/

#define  CRC_DOUT_XOR_DOUT_XOR_POSS  0U 
#define  CRC_DOUT_XOR_DOUT_XOR_POSE  31U 
#define  CRC_DOUT_XOR_DOUT_XOR_MSK  BITS(CRC_DOUT_XOR_DOUT_XOR_POSS,CRC_DOUT_XOR_DOUT_XOR_POSE)

/****************** Bit definition for CRC_STAT register ************************/

#define  CRC_STAT_FAIL_POS  8U 
#define  CRC_STAT_FAIL_MSK  BIT(CRC_STAT_FAIL_POS)

#define  CRC_STAT_EMPTY_POS  2U 
#define  CRC_STAT_EMPTY_MSK  BIT(CRC_STAT_EMPTY_POS)

#define  CRC_STAT_BUSY_POS  1U 
#define  CRC_STAT_BUSY_MSK  BIT(CRC_STAT_BUSY_POS)

#define  CRC_STAT_DONE_POS  0U 
#define  CRC_STAT_DONE_MSK  BIT(CRC_STAT_DONE_POS)

typedef struct
{
    __IO uint32_t   INIT;       /* 0x000 CRC_INIT       CRC Iintial Value Register  */
    __IO uint32_t   POLY;       /* 0x004 CRC_POLY       CRC Polynomial Register     */
    __IO uint32_t   DATA;       /* 0x008 CRC_DATA       CRC Input Data Register     */
    __IO uint32_t   COMP;       /* 0x00C CRC_COMP       CRC Compare Data Register   */
    __IO uint32_t   REMA;       /* 0x010 CRC_REMA       CRC Remainder Register      */
    __IO uint32_t   CON;        /* 0x014 CRC_CTRL       CRC Control Register        */
    __I  uint32_t   DOUT;       /* 0x018 CRC_DOUT       CRC Output Data Register    */
    __I  uint32_t   DOUT_XOR;   /* 0x01C CRC_DOUT_XOR   CRC Output Data Register    */
    __I  uint32_t   STAT;       /* 0x020 CRC_STA        CRC Status Register         */
} CRC_TypeDef;





#endif
