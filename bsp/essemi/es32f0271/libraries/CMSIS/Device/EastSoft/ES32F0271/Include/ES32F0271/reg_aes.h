/**
  **************************************************************************************
  * @file    REG_AES.h
  * @brief   AES Head File
  *
  * @version V0.01
  * @data    11/16/2018
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#ifndef __AES_H__
#define __AES_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
/* #pragma anon_unions */

/****************** Bit definition for AES_CON register ************************/

#define  AES_CON_READY_POS  22U 
#define  AES_CON_READY_MSK  BIT(AES_CON_READY_POS)

#define  AES_CON_OT_DMA_ST_POS  21U 
#define  AES_CON_OT_DMA_ST_MSK  BIT(AES_CON_OT_DMA_ST_POS)

#define  AES_CON_IT_DMA_ST_POS  20U 
#define  AES_CON_IT_DMA_ST_MSK  BIT(AES_CON_IT_DMA_ST_POS)

#define  AES_CON_OT_DEPTH_POSS  18U 
#define  AES_CON_OT_DEPTH_POSE  19U 
#define  AES_CON_OT_DEPTH_MSK  BITS(AES_CON_OT_DEPTH_POSS,AES_CON_OT_DEPTH_POSE)

#define  AES_CON_IT_DEPTH_POSS  16U 
#define  AES_CON_IT_DEPTH_POSE  17U 
#define  AES_CON_IT_DEPTH_MSK  BITS(AES_CON_IT_DEPTH_POSS,AES_CON_IT_DEPTH_POSE)

#define  AES_CON_RE_INIT_POS  8U 
#define  AES_CON_RE_INIT_MSK  BIT(AES_CON_RE_INIT_POS)

#define  AES_CON_DMA_EN_POSS  6U 
#define  AES_CON_DMA_EN_POSE  7U 
#define  AES_CON_DMA_EN_MSK  BITS(AES_CON_DMA_EN_POSS,AES_CON_DMA_EN_POSE)

#define  AES_CON_BL_POSS  3U 
#define  AES_CON_BL_POSE  5U 
#define  AES_CON_BL_MSK  BITS(AES_CON_BL_POSS,AES_CON_BL_POSE)

#define  AES_CON_REV_POS  2U 
#define  AES_CON_REV_MSK  BIT(AES_CON_REV_POS)

#define  AES_CON_MODE_POS  1U 
#define  AES_CON_MODE_MSK  BIT(AES_CON_MODE_POS)

#define  AES_CON_START_POS  0U 
#define  AES_CON_START_MSK  BIT(AES_CON_START_POS)

/****************** Bit definition for AES_IER register ************************/

#define  AES_IER_DECIE_POS  1U 
#define  AES_IER_DECIE_MSK  BIT(AES_IER_DECIE_POS)

#define  AES_IER_ENCIE_POS  0U 
#define  AES_IER_ENCIE_MSK  BIT(AES_IER_ENCIE_POS)

/****************** Bit definition for AES_IDR register ************************/

#define  AES_IDR_DECID_POS  1U 
#define  AES_IDR_DECID_MSK  BIT(AES_IDR_DECID_POS)

#define  AES_IDR_ENCID_POS  0U 
#define  AES_IDR_ENCID_MSK  BIT(AES_IDR_ENCID_POS)

/****************** Bit definition for AES_IVS register ************************/

#define  AES_IVS_DECIVS_POS  1U 
#define  AES_IVS_DECIVS_MSK  BIT(AES_IVS_DECIVS_POS)

#define  AES_IVS_ENCIVS_POS  0U 
#define  AES_IVS_ENCIVS_MSK  BIT(AES_IVS_ENCIVS_POS)

/****************** Bit definition for AES_RIF register ************************/

#define  AES_RIF_DECRIF_POS  1U 
#define  AES_RIF_DECRIF_MSK  BIT(AES_RIF_DECRIF_POS)

#define  AES_RIF_ENCRIF_POS  0U 
#define  AES_RIF_ENCRIF_MSK  BIT(AES_RIF_ENCRIF_POS)

/****************** Bit definition for AES_IFM register ************************/

#define  AES_IFM_DECIFM_POS  1U 
#define  AES_IFM_DECIFM_MSK  BIT(AES_IFM_DECIFM_POS)

#define  AES_IFM_ENCIFM_POS  0U 
#define  AES_IFM_ENCIFM_MSK  BIT(AES_IFM_ENCIFM_POS)

/****************** Bit definition for AES_ICR register ************************/

#define  AES_ICR_DECICR_POS  1U 
#define  AES_ICR_DECICR_MSK  BIT(AES_ICR_DECICR_POS)

#define  AES_ICR_ENCICR_POS  0U 
#define  AES_ICR_ENCICR_MSK  BIT(AES_ICR_ENCICR_POS)

/****************** Bit definition for AES_DIO register ************************/

#define  AES_DIO_DIO_POSS  0U 
#define  AES_DIO_DIO_POSE  31U 
#define  AES_DIO_DIO_MSK  BITS(AES_DIO_DIO_POSS,AES_DIO_DIO_POSE)

/****************** Bit definition for AES_KEY0 register ************************/

#define  AES_KEY0_KEY0_POSS  0U 
#define  AES_KEY0_KEY0_POSE  31U 
#define  AES_KEY0_KEY0_MSK  BITS(AES_KEY0_KEY0_POSS,AES_KEY0_KEY0_POSE)

/****************** Bit definition for AES_KEY1 register ************************/

#define  AES_KEY1_KEY1_POSS  0U 
#define  AES_KEY1_KEY1_POSE  31U 
#define  AES_KEY1_KEY1_MSK  BITS(AES_KEY1_KEY1_POSS,AES_KEY1_KEY1_POSE)

/****************** Bit definition for AES_KEY2 register ************************/

#define  AES_KEY2_KEY2_POSS  0U 
#define  AES_KEY2_KEY2_POSE  31U 
#define  AES_KEY2_KEY2_MSK  BITS(AES_KEY2_KEY2_POSS,AES_KEY2_KEY2_POSE)

/****************** Bit definition for AES_KEY3 register ************************/

#define  AES_KEY3_KEY3_POSS  0U 
#define  AES_KEY3_KEY3_POSE  31U 
#define  AES_KEY3_KEY3_MSK  BITS(AES_KEY3_KEY3_POSS,AES_KEY3_KEY3_POSE)

/****************** Bit definition for AES_IV0 register ************************/

#define  AES_IV0_IV0_POSS  0U 
#define  AES_IV0_IV0_POSE  31U 
#define  AES_IV0_IV0_MSK  BITS(AES_IV0_IV0_POSS,AES_IV0_IV0_POSE)

/****************** Bit definition for AES_IV1 register ************************/

#define  AES_IV1_IV1_POSS  0U 
#define  AES_IV1_IV1_POSE  31U 
#define  AES_IV1_IV1_MSK  BITS(AES_IV1_IV1_POSS,AES_IV1_IV1_POSE)

/****************** Bit definition for AES_IV2 register ************************/

#define  AES_IV2_IV2_POSS  0U 
#define  AES_IV2_IV2_POSE  31U 
#define  AES_IV2_IV2_MSK  BITS(AES_IV2_IV2_POSS,AES_IV2_IV2_POSE)

/****************** Bit definition for AES_IV3 register ************************/

#define  AES_IV3_IV3_POSS  0U 
#define  AES_IV3_IV3_POSE  31U 
#define  AES_IV3_IV3_MSK  BITS(AES_IV3_IV3_POSS,AES_IV3_IV3_POSE)

typedef struct
{
  __IO uint32_t      CON;   /* 0x000 AES_CON    AES Control Register                      */
  __O  uint32_t      IER;   /* 0x004 AES_IER    AES Interrupt Enable Register             */
  __O  uint32_t      IDR;   /* 0x008 AES_IDR    AES Interrupt Disable Register            */
  __I  uint32_t      IVS;   /* 0x00C AES_IVS    AES Interrupt Valid Status Register       */
  __I  uint32_t      RIF;   /* 0x010 AES_RIF    AES Raw Interrupt Flag Status Register    */
  __I  uint32_t      IFM;   /* 0x014 AES_IFM    AES Interrupt Flag Masked Register        */
  __O  uint32_t      ICR;   /* 0x018 AES_ICR    AES Interrupt Clear Register              */
  __IO uint32_t      DIO;   /* 0x01C AES_DIO    AES 128-bit Input/Output Data Register    */
  __IO uint32_t      KEY0;  /* 0x020 AES_KEY0   AES 256-bit Keyword Register 0            */
  __IO uint32_t      KEY1;  /* 0x024 AES_KEY1   AES 256-bit Keyword Register 1            */
  __IO uint32_t      KEY2;  /* 0x028 AES_KEY2   AES 256-bit Keyword Register 2            */
  __IO uint32_t      KEY3;  /* 0x02C AES_KEY3   AES 256-bit Keyword Register 3            */
  uint32_t RESERVED0[4] ;
  __IO uint32_t      IV0;   /* 0x040 AES_IV0    AES 128-bit Initial Vector Register 0     */
  __IO uint32_t      IV1;   /* 0x044 AES_IV1    AES 128-bit Initial Vector Register 1     */
  __IO uint32_t      IV2;   /* 0x048 AES_IV2    AES 128-bit Initial Vector Register 2     */
  __IO uint32_t      IV3;   /* 0x04C AES_IV3    AES 128-bit Initial Vector Register 3     */
} AES_TypeDef;





#endif
