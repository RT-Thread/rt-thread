/**
  ******************************************************************************
  * @file    stm32u5xx_ll_spi.c
  * @author  MCD Application Team
  * @brief   SPI LL module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_ll_spi.h"
#include "stm32u5xx_ll_bus.h"
#include "stm32u5xx_ll_rcc.h"
#ifdef GENERATOR_I2S_PRESENT
#include "stm32u5xx_ll_rcc.h"
#endif /* GENERATOR_I2S_PRESENT*/
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined(SPI1) || defined(SPI2) || defined(SPI3)

/** @addtogroup SPI_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup SPI_LL_Private_Macros
  * @{
  */

#define IS_LL_SPI_MODE(__VALUE__)                   (((__VALUE__) == LL_SPI_MODE_MASTER)         || \
                                                     ((__VALUE__) == LL_SPI_MODE_SLAVE))

#define IS_LL_SPI_SS_IDLENESS(__VALUE__)            (((__VALUE__) == LL_SPI_SS_IDLENESS_00CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_01CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_02CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_03CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_04CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_05CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_06CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_07CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_08CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_09CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_10CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_11CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_12CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_13CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_14CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_SS_IDLENESS_15CYCLE))

#define IS_LL_SPI_ID_IDLENESS(__VALUE__)            (((__VALUE__) == LL_SPI_ID_IDLENESS_00CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_01CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_02CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_03CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_04CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_05CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_06CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_07CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_08CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_09CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_10CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_11CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_12CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_13CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_14CYCLE) || \
                                                     ((__VALUE__) == LL_SPI_ID_IDLENESS_15CYCLE))

#define IS_LL_SPI_TXCRCINIT_PATTERN(__VALUE__)      (((__VALUE__) == LL_SPI_TXCRCINIT_ALL_ZERO_PATTERN) || \
                                                     ((__VALUE__) == LL_SPI_TXCRCINIT_ALL_ONES_PATTERN))

#define IS_LL_SPI_RXCRCINIT_PATTERN(__VALUE__)      (((__VALUE__) == LL_SPI_RXCRCINIT_ALL_ZERO_PATTERN) || \
                                                     ((__VALUE__) == LL_SPI_RXCRCINIT_ALL_ONES_PATTERN))

#define IS_LL_SPI_UDR_CONFIG_REGISTER(__VALUE__)    (((__VALUE__) == LL_SPI_UDR_CONFIG_REGISTER_PATTERN) || \
                                                     ((__VALUE__) == LL_SPI_UDR_CONFIG_LAST_RECEIVED)    || \
                                                     ((__VALUE__) == LL_SPI_UDR_CONFIG_LAST_TRANSMITTED))

#define IS_LL_SPI_UDR_DETECT_BEGIN_DATA(__VALUE__)  (((__VALUE__) == LL_SPI_UDR_DETECT_BEGIN_DATA_FRAME) || \
                                                     ((__VALUE__) == LL_SPI_UDR_DETECT_END_DATA_FRAME)   || \
                                                     ((__VALUE__) == LL_SPI_UDR_DETECT_BEGIN_ACTIVE_NSS))

#define IS_LL_SPI_PROTOCOL(__VALUE__)               (((__VALUE__) == LL_SPI_PROTOCOL_MOTOROLA)           || \
                                                     ((__VALUE__) == LL_SPI_PROTOCOL_TI))

#define IS_LL_SPI_PHASE(__VALUE__)                  (((__VALUE__) == LL_SPI_PHASE_1EDGE)                 || \
                                                     ((__VALUE__) == LL_SPI_PHASE_2EDGE))

#define IS_LL_SPI_POLARITY(__VALUE__)               (((__VALUE__) == LL_SPI_POLARITY_LOW)                || \
                                                     ((__VALUE__) == LL_SPI_POLARITY_HIGH))

#define IS_LL_SPI_BAUDRATEPRESCALER(__VALUE__)      (((__VALUE__) == LL_SPI_BAUDRATEPRESCALER_BYPASS)    || \
                                                     ((__VALUE__) == LL_SPI_BAUDRATEPRESCALER_DIV2)      || \
                                                     ((__VALUE__) == LL_SPI_BAUDRATEPRESCALER_DIV4)      || \
                                                     ((__VALUE__) == LL_SPI_BAUDRATEPRESCALER_DIV8)      || \
                                                     ((__VALUE__) == LL_SPI_BAUDRATEPRESCALER_DIV16)     || \
                                                     ((__VALUE__) == LL_SPI_BAUDRATEPRESCALER_DIV32)     || \
                                                     ((__VALUE__) == LL_SPI_BAUDRATEPRESCALER_DIV64)     || \
                                                     ((__VALUE__) == LL_SPI_BAUDRATEPRESCALER_DIV128)    || \
                                                     ((__VALUE__) == LL_SPI_BAUDRATEPRESCALER_DIV256))

#define IS_LL_SPI_BITORDER(__VALUE__)               (((__VALUE__) == LL_SPI_LSB_FIRST)                   || \
                                                     ((__VALUE__) == LL_SPI_MSB_FIRST))

#define IS_LL_SPI_TRANSFER_DIRECTION(__VALUE__)     (((__VALUE__) == LL_SPI_FULL_DUPLEX)                 || \
                                                     ((__VALUE__) == LL_SPI_SIMPLEX_TX)                  || \
                                                     ((__VALUE__) == LL_SPI_SIMPLEX_RX)                  || \
                                                     ((__VALUE__) == LL_SPI_HALF_DUPLEX_RX)              || \
                                                     ((__VALUE__) == LL_SPI_HALF_DUPLEX_TX))

#define IS_LL_SPI_DATAWIDTH(__VALUE__)              (((__VALUE__) == LL_SPI_DATAWIDTH_4BIT)              || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_5BIT)              || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_6BIT)              || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_7BIT)              || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_8BIT)              || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_9BIT)              || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_10BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_11BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_12BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_13BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_14BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_15BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_16BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_17BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_18BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_19BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_20BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_21BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_22BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_23BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_24BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_25BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_26BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_27BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_28BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_29BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_30BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_31BIT)             || \
                                                     ((__VALUE__) == LL_SPI_DATAWIDTH_32BIT))

#define IS_LL_SPI_FIFO_TH(__VALUE__)                (((__VALUE__) == LL_SPI_FIFO_TH_01DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_02DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_03DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_04DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_05DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_06DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_07DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_08DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_09DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_10DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_11DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_12DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_13DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_14DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_15DATA)              || \
                                                     ((__VALUE__) == LL_SPI_FIFO_TH_16DATA))

#define IS_LL_SPI_CRC(__VALUE__)                    (((__VALUE__) == LL_SPI_CRC_4BIT)                    || \
                                                     ((__VALUE__) == LL_SPI_CRC_5BIT)                    || \
                                                     ((__VALUE__) == LL_SPI_CRC_6BIT)                    || \
                                                     ((__VALUE__) == LL_SPI_CRC_7BIT)                    || \
                                                     ((__VALUE__) == LL_SPI_CRC_8BIT)                    || \
                                                     ((__VALUE__) == LL_SPI_CRC_9BIT)                    || \
                                                     ((__VALUE__) == LL_SPI_CRC_10BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_11BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_12BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_13BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_14BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_15BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_16BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_17BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_18BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_19BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_20BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_21BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_22BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_23BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_24BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_25BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_26BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_27BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_28BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_29BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_30BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_31BIT)                   || \
                                                     ((__VALUE__) == LL_SPI_CRC_32BIT))

#define IS_LL_SPI_NSS(__VALUE__)                    (((__VALUE__) == LL_SPI_NSS_SOFT)                    || \
                                                     ((__VALUE__) == LL_SPI_NSS_HARD_INPUT)              || \
                                                     ((__VALUE__) == LL_SPI_NSS_HARD_OUTPUT))

#define IS_LL_SPI_RX_FIFO(__VALUE__)                (((__VALUE__) == LL_SPI_RX_FIFO_0PACKET)             || \
                                                     ((__VALUE__) == LL_SPI_RX_FIFO_1PACKET)             || \
                                                     ((__VALUE__) == LL_SPI_RX_FIFO_2PACKET)             || \
                                                     ((__VALUE__) == LL_SPI_RX_FIFO_3PACKET))

#define IS_LL_SPI_CRCCALCULATION(__VALUE__)         (((__VALUE__) == LL_SPI_CRCCALCULATION_ENABLE)       || \
                                                     ((__VALUE__) == LL_SPI_CRCCALCULATION_DISABLE))

#define IS_LL_SPI_CRC_POLYNOMIAL(__VALUE__)          ((__VALUE__) >= 0x1UL)

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SPI_LL_Exported_Functions
  * @{
  */

/** @addtogroup SPI_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the SPI registers to their default reset values.
  * @param  SPIx SPI Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: SPI registers are de-initialized
  *          - ERROR: SPI registers are not de-initialized
  */
ErrorStatus LL_SPI_DeInit(SPI_TypeDef *SPIx)
{
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_INSTANCE(SPIx));

#if defined(SPI1)
  if (SPIx == SPI1)
  {
    /* Force reset of SPI clock */
    LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI1);

    /* Release reset of SPI clock */
    LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI1);

    /* Update the return status */
    status = SUCCESS;
  }
#endif /* SPI1 */
#if defined(SPI2)
  if (SPIx == SPI2)
  {
    /* Force reset of SPI clock */
    LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI2);

    /* Release reset of SPI clock */
    LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI2);

    /* Update the return status */
    status = SUCCESS;
  }
#endif /* SPI2 */
#if defined(SPI3)
  if (SPIx == SPI3)
  {
    /* Force reset of SPI clock */
    LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_SPI3);

    /* Release reset of SPI clock */
    LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_SPI3);

    /* Update the return status */
    status = SUCCESS;
  }
#endif /* SPI3 */
#if defined(SPI4)
  if (SPIx == SPI4)
  {
    /* Force reset of SPI clock */
    LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI4);

    /* Release reset of SPI clock */
    LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI4);

    /* Update the return status */
    status = SUCCESS;
  }
#endif /* SPI4 */
#if defined(SPI5)
  if (SPIx == SPI5)
  {
    /* Force reset of SPI clock */
    LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI5);

    /* Release reset of SPI clock */
    LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI5);

    /* Update the return status */
    status = SUCCESS;
  }
#endif /* SPI5 */
#if defined(SPI6)
  if (SPIx == SPI6)
  {
    /* Force reset of SPI clock */
    LL_APB5_GRP1_ForceReset(LL_APB5_GRP1_PERIPH_SPI6);

    /* Release reset of SPI clock */
    LL_APB5_GRP1_ReleaseReset(LL_APB5_GRP1_PERIPH_SPI6);

    /* Update the return status */
    status = SUCCESS;
  }
#endif /* SPI6 */

  return status;
}

/**
  * @brief  Initialize the SPI registers according to the specified parameters in SPI_InitStruct.
  * @note   As some bits in SPI configuration registers can only be written when the SPI is disabled
  *         (SPI_CR1_SPE bit =0), SPI IP should be in disabled state prior calling this function.
  *         Otherwise, ERROR result will be returned.
  * @param  SPIx SPI Instance
  * @param  SPI_InitStruct pointer to a @ref LL_SPI_InitTypeDef structure
  * @retval An ErrorStatus enumeration value. (Return always SUCCESS)
  */
ErrorStatus LL_SPI_Init(SPI_TypeDef *SPIx, LL_SPI_InitTypeDef *SPI_InitStruct)
{
  ErrorStatus status = ERROR;
  uint32_t tmp_nss;
  uint32_t tmp_mode;

  /* Check the SPI Instance SPIx*/
  assert_param(IS_SPI_ALL_INSTANCE(SPIx));

  /* Check the SPI parameters from SPI_InitStruct*/
  assert_param(IS_LL_SPI_TRANSFER_DIRECTION(SPI_InitStruct->TransferDirection));
  assert_param(IS_LL_SPI_MODE(SPI_InitStruct->Mode));
  assert_param(IS_LL_SPI_DATAWIDTH(SPI_InitStruct->DataWidth));
  assert_param(IS_LL_SPI_POLARITY(SPI_InitStruct->ClockPolarity));
  assert_param(IS_LL_SPI_PHASE(SPI_InitStruct->ClockPhase));
  assert_param(IS_LL_SPI_NSS(SPI_InitStruct->NSS));
  assert_param(IS_LL_SPI_BAUDRATEPRESCALER(SPI_InitStruct->BaudRate));
  assert_param(IS_LL_SPI_BITORDER(SPI_InitStruct->BitOrder));
  assert_param(IS_LL_SPI_CRCCALCULATION(SPI_InitStruct->CRCCalculation));

  /* Check the SPI instance is not enabled */
  if (LL_SPI_IsEnabled(SPIx) == 0x00000000UL)
  {
    /*---------------------------- SPIx CFG1 Configuration ------------------------
       * Configure SPIx CFG1 with parameters:
       * - Master Baud Rate       : SPI_CFG1_MBR[2:0] bits & SPI_CFG1_BPASS bit
       * - CRC Computation Enable : SPI_CFG1_CRCEN bit
       * - Length of data frame   : SPI_CFG1_DSIZE[4:0] bits
       */
    MODIFY_REG(SPIx->CFG1, SPI_CFG1_BPASS | SPI_CFG1_MBR | SPI_CFG1_CRCEN | SPI_CFG1_DSIZE,
               SPI_InitStruct->BaudRate  | SPI_InitStruct->CRCCalculation | SPI_InitStruct->DataWidth);

    tmp_nss  = SPI_InitStruct->NSS;
    tmp_mode = SPI_InitStruct->Mode;

    /* Checks to setup Internal SS signal level and avoid a MODF Error */
    if ((LL_SPI_GetNSSPolarity(SPIx) == LL_SPI_NSS_POLARITY_LOW) && (tmp_nss == LL_SPI_NSS_SOFT) &&
        (tmp_mode == LL_SPI_MODE_MASTER))
    {
      LL_SPI_SetInternalSSLevel(SPIx, LL_SPI_SS_LEVEL_HIGH);
    }

    /*---------------------------- SPIx CFG2 Configuration ------------------------
       * Configure SPIx CFG2 with parameters:
       * - NSS management         : SPI_CFG2_SSM, SPI_CFG2_SSOE bits
       * - ClockPolarity          : SPI_CFG2_CPOL bit
       * - ClockPhase             : SPI_CFG2_CPHA bit
       * - BitOrder               : SPI_CFG2_LSBFRST bit
       * - Master/Slave Mode      : SPI_CFG2_MASTER bit
       * - SPI Mode               : SPI_CFG2_COMM[1:0] bits
       */
    MODIFY_REG(SPIx->CFG2, SPI_CFG2_SSM   | SPI_CFG2_SSOE    |
               SPI_CFG2_CPOL              | SPI_CFG2_CPHA    |
               SPI_CFG2_LSBFRST           | SPI_CFG2_MASTER  | SPI_CFG2_COMM,
               SPI_InitStruct->NSS        | SPI_InitStruct->ClockPolarity                    |
               SPI_InitStruct->ClockPhase | SPI_InitStruct->BitOrder                         |
               SPI_InitStruct->Mode       | (SPI_InitStruct->TransferDirection & SPI_CFG2_COMM));

    /*---------------------------- SPIx CR1 Configuration ------------------------
       * Configure SPIx CR1 with parameter:
       * - Half Duplex Direction  : SPI_CR1_HDDIR bit
       */
    MODIFY_REG(SPIx->CR1, SPI_CR1_HDDIR, SPI_InitStruct->TransferDirection & SPI_CR1_HDDIR);

    /*---------------------------- SPIx CRCPOLY Configuration ----------------------
       * Configure SPIx CRCPOLY with parameter:
       * - CRCPoly                : CRCPOLY[31:0] bits
       */
    if (SPI_InitStruct->CRCCalculation == LL_SPI_CRCCALCULATION_ENABLE)
    {
      assert_param(IS_LL_SPI_CRC_POLYNOMIAL(SPI_InitStruct->CRCPoly));
      LL_SPI_SetCRCPolynomial(SPIx, SPI_InitStruct->CRCPoly);
    }


    status = SUCCESS;
  }

  return status;
}

/**
  * @brief  Set each @ref LL_SPI_InitTypeDef field to default value.
  * @param  SPI_InitStruct pointer to a @ref LL_SPI_InitTypeDef structure
  * whose fields will be set to default values.
  * @retval None
  */
void LL_SPI_StructInit(LL_SPI_InitTypeDef *SPI_InitStruct)
{
  /* Set SPI_InitStruct fields to default values */
  SPI_InitStruct->TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct->Mode              = LL_SPI_MODE_SLAVE;
  SPI_InitStruct->DataWidth         = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct->ClockPolarity     = LL_SPI_POLARITY_LOW;
  SPI_InitStruct->ClockPhase        = LL_SPI_PHASE_1EDGE;
  SPI_InitStruct->NSS               = LL_SPI_NSS_HARD_INPUT;
  SPI_InitStruct->BaudRate          = LL_SPI_BAUDRATEPRESCALER_DIV2;
  SPI_InitStruct->BitOrder          = LL_SPI_MSB_FIRST;
  SPI_InitStruct->CRCCalculation    = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct->CRCPoly           = 7UL;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(SPI1) || defined(SPI2) || defined(SPI3) */

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */
