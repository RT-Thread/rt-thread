/**
  **************************************************************************************
  * @file    reg_IWDG.h
  * @brief   IWDG Head File
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

#ifndef __IWDG_H__
#define __IWDG_H__

typedef struct
{
    __O  uint32_t   KR  ;  /* 0x00 IWDG_KR   - Key register         */
    __IO uint32_t   PR  ;  /* 0x04 IWDG_PR   - Prescaler register   */
    __IO uint32_t   RLR ;  /* 0x08 IWDG_RLR  - Reload register      */
    __I  uint32_t   FR  ;  /* 0x0C IWDG_SR   - Status register      */
    __IO uint32_t   WINR;  /* 0x10 IWDG_WINR - Window register      */
} IWDG_TypeDef;

/******************************************************************************/
/*                              暫存器內部位元定義                            */
/******************************************************************************/

/* #pragma anon_unions */

/****************** Bit definition for IWDG_KR register ************************/

#define IWDG_KR_KEY_POSS 0U
#define IWDG_KR_KEY_POSE 15U
#define IWDG_KR_KEY_MSK BITS(IWDG_KR_KEY_POSS,IWDG_KR_KEY_POSE)

/****************** Bit definition for IWDG_PR register ************************/

#define IWDG_PR_PR_POSS 0U
#define IWDG_PR_PR_POSE 2U
#define IWDG_PR_PR_MSK BITS(IWDG_PR_PR_POSS,IWDG_PR_PR_POSE)

/****************** Bit definition for IWDG_RLR register ************************/

#define IWDG_RLR_RL_POSS 0U
#define IWDG_RLR_RL_POSE 12U
#define IWDG_RLR_RL_MSK BITS(IWDG_RLR_RL_POSS,IWDG_RLR_RL_POSE)

/****************** Bit definition for IWDG_FR register ************************/

#define IWDG_FR_BUSY_POS 15U
#define IWDG_FR_BUSY_MSK BIT(IWDG_FR_BUSY_POS)

#define IWDG_FR_STR_POS 12U
#define IWDG_FR_STR_MSK BIT(IWDG_FR_STR_POS)

#define IWDG_FR_CNT_POSS 0U
#define IWDG_FR_CNT_POSE 11U
#define IWDG_FR_CNT_MSK BITS(IWDG_FR_CNT_POSS,IWDG_FR_CNT_POSE)

/****************** Bit definition for IWDG_WINR register ************************/

#define IWDG_WINR_WIN_POSS 0U
#define IWDG_WINR_WIN_POSE 31U
#define IWDG_WINR_WIN_MSK BITS(IWDG_WINR_WIN_POSS,IWDG_WINR_WIN_POSE)


#else
/* */
#endif
