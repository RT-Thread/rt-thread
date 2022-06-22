/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_hash.h
 **
 ** A detailed description is available at
 ** @link HashGroup Hash description @endlink
 **
 **   - 2018-10-18  CDT First version for Device Driver Library of Hash.
 **
 ******************************************************************************/
#ifndef __HC32F460_HASH_H__
#define __HC32F460_HASH_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_HASH_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup HashGroup Hash(HASH)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
void HASH_Init(void);
void HASH_DeInit(void);
en_result_t HASH_Start(const uint8_t *pu8SrcData,
                       uint32_t u32SrcDataSize,
                       uint8_t *pu8MsgDigest,
                       uint32_t u32Timeout);

//@} // HashGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_HASH_ENABLE */

#endif /* __HC32F460_HASH_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
