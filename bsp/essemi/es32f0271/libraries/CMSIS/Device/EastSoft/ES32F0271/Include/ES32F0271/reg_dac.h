/**
  **************************************************************************************
  * @file    REG_DAC.h
  * @brief   DAC Head File
  *
  * @version V0.01
  * @data    1/14/2019
  * @author  Eastsoft MCU Software Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#ifndef __DAC_H__
#define __DAC_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
/* #pragma anon_unions */

/****************** Bit definition for DAC_CON register ************************/

#define	DAC_CON_T_SEL_POSS	9U 
#define	DAC_CON_T_SEL_POSE	13U 
#define	DAC_CON_T_SEL_MSK	BITS(DAC_CON_T_SEL_POSS,DAC_CON_T_SEL_POSE)

#define	DAC_CON_TRIEN_POS	8U 
#define	DAC_CON_TRIEN_MSK	BIT(DAC_CON_TRIEN_POS)

#define	DAC_CON_MAMP_POSS	3U 
#define	DAC_CON_MAMP_POSE	6U 
#define	DAC_CON_MAMP_MSK	BITS(DAC_CON_MAMP_POSS,DAC_CON_MAMP_POSE)

#define	DAC_CON_WAVE_POSS	1U 
#define	DAC_CON_WAVE_POSE	2U 
#define	DAC_CON_WAVE_MSK	BITS(DAC_CON_WAVE_POSS,DAC_CON_WAVE_POSE)

#define	DAC_CON_INVREN_POS	0U 
#define	DAC_CON_INVREN_MSK	BIT(DAC_CON_INVREN_POS)

/****************** Bit definition for DAC_DIV register ************************/

#define	DAC_DIV_DIV_VALUE_POSS	0U 
#define	DAC_DIV_DIV_VALUE_POSE	15U 
#define	DAC_DIV_DIV_VALUE_MSK	BITS(DAC_DIV_DIV_VALUE_POSS,DAC_DIV_DIV_VALUE_POSE)

/****************** Bit definition for DAC_STAT register ************************/

#define	DAC_STAT_TX_FULL_POS	1U 
#define	DAC_STAT_TX_FULL_MSK	BIT(DAC_STAT_TX_FULL_POS)

#define	DAC_STAT_BUSY_POS	0U 
#define	DAC_STAT_BUSY_MSK	BIT(DAC_STAT_BUSY_POS)

/****************** Bit definition for DAC_EN register ************************/

#define	DAC_EN_DAC_EN_POS	0U 
#define	DAC_EN_DAC_EN_MSK	BIT(DAC_EN_DAC_EN_POS)

/****************** Bit definition for DAC_DMAC register ************************/

#define	DAC_DMAC_TXDMAEN_POS	0U 
#define	DAC_DMAC_TXDMAEN_MSK	BIT(DAC_DMAC_TXDMAEN_POS)

/****************** Bit definition for DAC_TRIG register ************************/

#define	DAC_TRIG_S_TRIG_POS	0U 
#define	DAC_TRIG_S_TRIG_MSK	BIT(DAC_TRIG_S_TRIG_POS)

/****************** Bit definition for DAC_DATA register ************************/

#define	DAC_DATA_TXDATA_POSS	0U 
#define	DAC_DATA_TXDATA_POSE	11U 
#define	DAC_DATA_TXDATA_MSK	BITS(DAC_DATA_TXDATA_POSS,DAC_DATA_TXDATA_POSE)

typedef struct
{
	__IO uint32_t CON;
	__IO uint32_t DIV;
	__I uint32_t STAT;
	__IO uint32_t EN;
	__IO uint32_t DMAC;
	__O uint32_t TRIG;
	__IO uint32_t DATA;
} DAC_TypeDef;





#endif
