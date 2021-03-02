/**
    *****************************************************************************
    * @file     cmem7_efuse.h
    *
    * @brief    CMEM7 EFUSE header file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_EFUSE_H
#define __CMEM7_EFUSE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

/** @defgroup EFUSE_TMRF_R
  * @{
  */
#define EFUSE_TMRF_R_3000                0
#define EFUSE_TMRF_R_1200                1
#define EFUSE_TMRF_R_750                 2

#define IS_EFUSE_TMRF(R)                 (((R) == EFUSE_TMRF_R_3000) || \
                                          ((R) == EFUSE_TMRF_R_1200) || \
                                          ((R) == EFUSE_TMRF_R_750))
/**
  * @}
  */

/**
  * @brief  EFUSE timing structure
    */
typedef struct
{
    uint32_t EFUSE_Tpwph;                  /*!< Nano second                                    */
  uint32_t EFUSE_Trac;                   /*!< Nano second                                    */
    uint32_t EFUSE_Trah;                   /*!< Nano second                                    */
    uint32_t EFUSE_Trpw;                   /*!< Nano second                                    */
    uint32_t EFUSE_Trc;                    /*!< Nano second                                    */
    uint32_t EFUSE_Tesr;                   /*!< Nano second                                    */
    uint32_t EFUSE_Tprs;                   /*!< Nano second                                    */
    uint32_t EFUSE_Tpi;                    /*!< Nano second                                    */
    uint32_t EFUSE_Tpp;                    /*!< Nano second                                    */
    uint32_t EFUSE_Teps;                   /*!< Nano second                                    */
    uint32_t EFUSE_Tpwps;                  /*!< Nano second                                    */
} EFUSE_Timing;

/**
  * @brief  EFUSE initialization structure
    */
typedef struct
{
    uint8_t EFUSE_ClockDividor;              /*!< EFUSE clock dividor, 2 in n times */
    uint8_t EFUSE_TMRF;                    /*!< EFUSE reference resistor select, @ref EFUSE_TMRF_R */
  EFUSE_Timing* timing;                  /*!< Timing configuration, null if default           */
} EFUSE_InitTypeDef;

/**
  * @brief  EFUSE key structure
    */
typedef struct
{
    uint32_t key0;                         /*!< EFUSE AES key [31:0]                            */
  uint32_t key1;                         /*!< EFUSE AES key [63:32]                           */
    uint32_t key2;                         /*!< EFUSE AES key [95:64]                           */
    uint32_t key3;                         /*!< EFUSE AES key [127:96]                          */
    uint32_t key4;                         /*!< EFUSE AES key [159:128]                         */
  uint32_t key5;                         /*!< EFUSE AES key [191:160]                         */
    uint32_t key6;                         /*!< EFUSE AES key [223:192]                         */
    uint32_t key7;                         /*!< EFUSE AES key [255:224]                         */
} EFUSE_AesKey;

/**
  * @brief  EFUSE initialization
  * @note   This function should be called at first before any other interfaces.
    * @param[in] init A pointer to structure EFUSE_InitTypeDef
  * @retval None
    */
void EFUSE_Init(EFUSE_InitTypeDef* init);

/**
  * @brief  EFUSE initialization
  * @param[in] key A pointer to EFUSE_AesKey to be compared
  * @retval BOOL True if equal, or false if different
    */
BOOL EFUSE_Compare(EFUSE_AesKey* key);

#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_EFUSE_H */

