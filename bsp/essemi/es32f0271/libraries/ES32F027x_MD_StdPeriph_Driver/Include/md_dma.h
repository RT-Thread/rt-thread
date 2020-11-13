/**
  ******************************************************************************
  * @file    md_DMA.h
  * @brief   ES32F0271 DMA HEAD File.
  *
  * @version V1.00.02
  * @date    30/11/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_DMA_H__
#define __MD_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/
#include "es32f0271.h"
#include "reg_dma.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (DMA1)

/** @defgroup DMA DMA
  * @brief DMA micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Public types ---------------------------------------------------------------*/
/** @defgroup MD_DMA_PT_INIT DMA Public Init structures
  * @{
  */

/**
  * @brief MD DMA Init Structure definition
  */


/**
  * @} MD_DMA_PT_INIT
  */

/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_DMA_Public_Constants DMA Public Constants
  * @{
  */

/** @defgroup MD_DMA_DINCOS Destination Increment Offset Size
  * @{
  */
#define MD_DMA_DINCOS_LINKED_DWSEL    (0x00000000UL)    /** @brief The offset size for the peripheral address calculation is
                                                                   linked to the DWSEL */
#define MD_DMA_DINCOS_FIXED_TO_4      (0X00000001UL)    /** @brief The offset size for the peripheral address calculation is
                                                                   fixed to 4 (32-bit alignment). */
/**
  * @} MD_DMA_DINCOS
  */

/** @defgroup MD_DMA_DBUSEL Destination Transfer Burst Selection
  * @{
  */
#define MD_DMA_DBUSEL_SINGLE          (0x00000000U)
#define MD_DMA_DBUSEL_WRAP4           (0x00000002U)
#define MD_DMA_DBUSEL_INCR4           (0x00000003U)
#define MD_DMA_DBUSEL_WRAP8           (0x00000004U)
#define MD_DMA_DBUSEL_INCR8           (0x00000005U)
#define MD_DMA_DBUSEL_WRAP16          (0x00000006U)
#define MD_DMA_DBUSEL_INCR16          (0x00000007U)
/**
  * @} MD_DMA_DBUSEL
  */

/** @defgroup MD_DMA_DDWSEL Destination Transfer Data Width Selection.
  * @{
  */
#define MD_DMA_DDWSEL_ONE_BYTE        (0x00000000UL) /** @brief One byte (8-bit) is transferred for every DMA operation. */
#define MD_DMA_DDWSEL_ONE_HALF_WORD   (0x00000001UL) /** @brief One half-word (16-bit) is transferred for every DMA operation. */
#define MD_DMA_DDWSEL_ONE_WORD        (0x00000002UL) /** @brief One word (32-bit) is transferred for every DMA operation. */
/**
  * @} MD_DMA_DDWSEL
  */

/** @defgroup MD_DMA_SINCOS Source Increment Offset Size
  * @{
  */
#define MD_DMA_SINCOS_LINKED_SWSEL    (0x00000000UL)    /** @brief The offset size for the peripheral address calculation is
                                                                   linked to the SWSEL */
#define MD_DMA_SINCOS_FIXED_TO_4      (0X00000001UL)    /** @brief The offset size for the peripheral address calculation is
                                                                   fixed to 4 (32-bit alignment). */
/**
  * @} MD_DMA_SINCOS
  */

/** @defgroup MD_DMA_SBUSEL Source Transfer Burst Selection.
  * @{
  */
#define MD_DMA_SBUSEL_SINGLE          (0x00000000U)
#define MD_DMA_SBUSEL_WRAP4           (0x00000002U)
#define MD_DMA_SBUSEL_INCR4           (0x00000003U)
#define MD_DMA_SBUSEL_WRAP8           (0x00000004U)
#define MD_DMA_SBUSEL_INCR8           (0x00000005U)
#define MD_DMA_SBUSEL_WRAP16          (0x00000006U)
#define MD_DMA_SBUSEL_INCR16          (0x00000007U)
/**
  * @} MD_DMA_SBUSEL
  */

/** @defgroup MD_DMA_SDWSEL Source Transfer Data Width Selection.
  * @{
  */
#define MD_DMA_SDWSEL_ONE_BYTE        (0x00000000UL)  /** @brief One byte (8-bit) is transferred for every DMA operation. */
#define MD_DMA_SDWSEL_ONE_HALF_WORD   (0x00000001UL)  /** @brief One half-word (16-bit) is transferred for every DMA operation. */
#define MD_DMA_SDWSEL_ONE_WORD        (0x00000002UL)  /** @brief One word (32-bit) is transferred for every DMA operation. */
/**
  * @} MD_DMA_SDWSEL
  */

/** @defgroup MD_DMA_CHPRI DMA Channel Priority.
  * @{
  */
#define MD_DMA_CHPRI_LV0          (0x00000000U)
#define MD_DMA_CHPRI_LV1          (0x00000001U)
#define MD_DMA_CHPRI_LV2          (0x00000002U)
#define MD_DMA_CHPRI_LV3          (0x00000003U)
#define MD_DMA_CHPRI_LV4          (0x00000004U)
#define MD_DMA_CHPRI_LV5          (0x00000005U)
/**
  * @} MD_DMA_CHPRI
  */

/** @defgroup MD_DMA_MODESEL DMA Mode Select.
  * @{
  */
#define MD_DMA_MODESEL_MEM_TO_MEM     (0x0000000UL)   /** @brief Memory to Memory mode (Memory-to-Memory). */
#define MD_DMA_MODESEL_PER_TO_MEM     (0x0000001UL)   /** @brief Peripheral to Memory mode (Peripheral-to-Memory). */
#define MD_DMA_MODESEL_MEM_TO_PER     (0x0000002UL)   /** @brief Memory to Peripheral mode (Memory-to-Peripheral). */
/**
  * @} MD_DMA_MODESEL
  */

/** @defgroup MD_DMA_PFCTRL Peripheral flow controller
  * @{
  */
#define MD_DMA_PFCTRL_DMA_CTRL        (0x0000000UL)   /** @brief The DMA is the flow controller */
#define MD_DMA_PFCTRL_PER_CTRL        (0x0000001UL)   /** @brief The peripheral is the flow controller */
/**
  * @} MD_DMA_PFCTRL
  */

/** @defgroup MD_DMA_PHSS Peripheral Handshake Software Select
  * @{
  */
#define MD_DMA_PHSS_UART1_TX        (0x0000000UL)
#define MD_DMA_PHSS_UART2_TX        (0x0000001UL)
#define MD_DMA_PHSS_UART3_TX        (0x0000002UL)
#define MD_DMA_PHSS_SUART1_TX       (0x0000003UL)
#define MD_DMA_PHSS_SUART2_TX       (0x0000004UL)
#define MD_DMA_PHSS_SPI1_TX         (0x0000005UL)
#define MD_DMA_PHSS_SPI2_TX         (0x0000006UL)
#define MD_DMA_PHSS_I2C1_TX         (0x0000007UL)
#define MD_DMA_PHSS_I2C2_TX         (0x0000008UL)
#define MD_DMA_PHSS_AES_IN          (0x0000009UL)
#define MD_DMA_PHSS_DAC             (0x000000AUL)
#define MD_DMA_PHSS_CRC             (0x000000BUL)
#define MD_DMA_PHSS_UART1_RX        (0x000000FUL)
#define MD_DMA_PHSS_UART2_RX        (0x0000010UL)
#define MD_DMA_PHSS_UART3_RX        (0x0000011UL)
#define MD_DMA_PHSS_SUART1_RX       (0x0000012UL)
#define MD_DMA_PHSS_SUART2_RX       (0x0000013UL)
#define MD_DMA_PHSS_SPI1_RTX        (0x0000014UL)
#define MD_DMA_PHSS_SPI2_RX         (0x0000015UL)
#define MD_DMA_PHSS_I2C1_RX         (0x0000016UL)
#define MD_DMA_PHSS_I2C2_RX         (0x0000017UL)
#define MD_DMA_PHSS_AES_OUT         (0x0000018UL)
#define MD_DMA_PHSS_ADCSS0          (0x0000019UL)
#define MD_DMA_PHSS_ADCSS1          (0x000001AUL)
#define MD_DMA_PHSS_ADCSS2          (0x000001BUL)
#define MD_DMA_PHSS_ADCSS3          (0x000001CUL)
#define MD_DMA_PHSS_BS16T1_UP       (0x0000020UL)
#define MD_DMA_PHSS_AD16C4T1_CH1    (0x0000021UL)
#define MD_DMA_PHSS_AD16C4T1_CH2    (0x0000022UL)
#define MD_DMA_PHSS_AD16C4T1_CH3    (0x0000023UL)
#define MD_DMA_PHSS_AD16C4T1_CH4    (0x0000024UL)
#define MD_DMA_PHSS_AD16C4T1_UP     (0x0000025UL)
#define MD_DMA_PHSS_AD16C4T1_TRIG   (0x0000026UL)
#define MD_DMA_PHSS_AD16C4T1_COM    (0x0000027UL)
#define MD_DMA_PHSS_GP32C4T1_CH1    (0x0000028UL)
#define MD_DMA_PHSS_GP32C4T1_CH2    (0x0000029UL)
#define MD_DMA_PHSS_GP32C4T1_CH3    (0x000002AUL)
#define MD_DMA_PHSS_GP32C4T1_CH4    (0x000002BUL)
#define MD_DMA_PHSS_GP32C4T1_UP     (0x000002CUL)
#define MD_DMA_PHSS_GP32C4T1_TRIG   (0x000002DUL)
#define MD_DMA_PHSS_GP16C4T1_CH1    (0x000002EUL)
#define MD_DMA_PHSS_GP16C4T1_CH2    (0x000002FUL)
#define MD_DMA_PHSS_GP16C4T1_CH3    (0x0000030UL)
#define MD_DMA_PHSS_GP16C4T1_CH4    (0x0000031UL)
#define MD_DMA_PHSS_GP16C4T1_UP     (0x0000032UL)
#define MD_DMA_PHSS_GP16C4T1_TRIG   (0x0000033UL)
#define MD_DMA_PHSS_GP16C4T2_CH1    (0x0000034UL)
#define MD_DMA_PHSS_GP16C4T2_CH2    (0x0000035UL)
#define MD_DMA_PHSS_GP16C4T2_CH3    (0x0000036UL)
#define MD_DMA_PHSS_GP16C4T2_CH4    (0x0000037UL)
#define MD_DMA_PHSS_GP16C4T2_UP     (0x0000038UL)
#define MD_DMA_PHSS_GP16C4T2_TRIG   (0x0000039UL)
#define MD_DMA_PHSS_GP16C4T3_CH1    (0x000003AUL)
#define MD_DMA_PHSS_GP16C4T3_CH2    (0x000003BUL)
#define MD_DMA_PHSS_GP16C4T3_CH3    (0x000003CUL)
#define MD_DMA_PHSS_GP16C4T3_CH4    (0x000003DUL)
#define MD_DMA_PHSS_GP16C4T3_UP     (0x000003EUL)
#define MD_DMA_PHSS_GP16C4T3_TRIG   (0x000003FUL)
#define MD_DMA_PHSS_GP16C2T1_CH1    (0x0000040UL)
#define MD_DMA_PHSS_GP16C2T1_CH2    (0x0000041UL)
#define MD_DMA_PHSS_GP16C2T1_UP     (0x0000042UL)
#define MD_DMA_PHSS_GP16C2T1_TRIG   (0x0000043UL)
#define MD_DMA_PHSS_GP16C2T1_COM    (0x0000044UL)
#define MD_DMA_PHSS_GP16C2T2_CH1    (0x0000046UL)
#define MD_DMA_PHSS_GP16C2T2_CH2    (0x0000047UL)
#define MD_DMA_PHSS_GP16C2T2_UP     (0x0000048UL)
#define MD_DMA_PHSS_GP16C2T2_TRIG   (0x0000049UL)
#define MD_DMA_PHSS_GP16C2T2_COM    (0x000004AUL)
#define MD_DMA_PHSS_GP16C2T3_CH1    (0x000004CUL)
#define MD_DMA_PHSS_GP16C2T3_CH2    (0x000004DUL)
#define MD_DMA_PHSS_GP16C2T3_UP     (0x000004EUL)
#define MD_DMA_PHSS_GP16C2T3_TRIG   (0x000004FUL)
#define MD_DMA_PHSS_GP16C2T3_COM    (0x0000050UL)
#define MD_DMA_PHSS_GP16C2T4_CH1    (0x0000052UL)
#define MD_DMA_PHSS_GP16C2T4_CH2    (0x0000053UL)
#define MD_DMA_PHSS_GP16C2T4_UP     (0x0000054UL)
#define MD_DMA_PHSS_GP16C2T4_TRIG   (0x0000055UL)
#define MD_DMA_PHSS_GP16C2T4_COM    (0x0000056UL)
/**
  * @} MD_DMA_PHSS
  */

/**
  * @} MD_DMA_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_DMA_Public_Macros DMA Public Macros
  * @{
  */

/**
  * @brief  DMA Channel 5 TABORT Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch5tabie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH5TABIE_MSK);
}
/**
  * @brief  DMA Channel 5 Block Transmit Done Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch5btdie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH5BTDIE_MSK);
}
/**
  * @brief  DMA Channel 4 TABORT Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch4tabie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH4TABIE_MSK);
}
/**
  * @brief  DMA Channel 4 Block Transmit Done Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch4btdie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH4BTDIE_MSK);
}
/**
  * @brief  DMA Channel 3 TABORT Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch3tabie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH3TABIE_MSK);
}
/**
  * @brief  DMA Channel 3 Block Transmit Done Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch3btdie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH3BTDIE_MSK);
}
/**
  * @brief  DMA Channel 2 TABORT Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch2tabie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH2TABIE_MSK);
}
/**
  * @brief  DMA Channel 2 Block Transmit Done Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch2btdie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH2BTDIE_MSK);
}
/**
  * @brief  DMA Channel 1 TABORT Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch1tabie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH1TABIE_MSK);
}
/**
  * @brief  DMA Channel 1 Block Transmit Done Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch1btdie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH1BTDIE_MSK);
}
/**
  * @brief  DMA Channel 0 TABORT Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch0tabie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH0TABIE_MSK);
}
/**
  * @brief  DMA Channel 0 Block Transmit Done Interrupt Enable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_ier_ch0btdie(DMA_TypeDef *dma)
{
  SET_BIT(dma->IER, DMA_IER_CH0BTDIE_MSK);
}

/** @defgroup MD_DMA_IER_CH5TABIE CH5TABIE
  * @brief  Set DMA Channel 5 TABORT Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch5tabie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch5tabie_fun(ch5tabie)  (ch5tabie<<DMA_IER_CH5TABIE_POS)
/**
  * @} MD_DMA_IER_CH5TABIE
  */
/** @defgroup MD_DMA_IER_CH5BTDIE CH5BTDIE
  * @brief  Set DMA Channel 5 Block Transmit Done Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch5btdie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch5btdie_fun(ch5btdie)  (ch5btdie<<DMA_IER_CH5BTDIE_POS)
/**
  * @} MD_DMA_IER_CH5BTDIE
  */
/** @defgroup MD_DMA_IER_CH4TABIE CH4TABIE
  * @brief  Set DMA Channel 4 TABORT Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch4tabie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch4tabie_fun(ch4tabie)  (ch4tabie<<DMA_IER_CH4TABIE_POS)
/**
  * @} MD_DMA_IER_CH4TABIE
  */
/** @defgroup MD_DMA_IER_CH4BTDIE CH4BTDIE
  * @brief  Set DMA Channel 4 Block Transmit Done Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch4btdie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch4btdie_fun(ch4btdie)  (ch4btdie<<DMA_IER_CH4BTDIE_POS)
/**
  * @} MD_DMA_IER_CH4BTDIE
  */
/** @defgroup MD_DMA_IER_CH3TABIE CH3TABIE
  * @brief  Set DMA Channel 3 TABORT Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch3tabie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch3tabie_fun(ch3tabie)  (ch3tabie<<DMA_IER_CH3TABIE_POS)
/**
  * @} MD_DMA_IER_CH3TABIE
  */
/** @defgroup MD_DMA_IER_CH3BTDIE CH3BTDIE
  * @brief  Set DMA Channel 3 Block Transmit Done Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch3btdie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch3btdie_fun(ch3btdie)  (ch3btdie<<DMA_IER_CH3BTDIE_POS)
/**
  * @} MD_DMA_IER_CH3BTDIE
  */
/** @defgroup MD_DMA_IER_CH2TABIE CH2TABIE
  * @brief  Set DMA Channel 2 TABORT Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch2tabie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch2tabie_fun(ch2tabie)  (ch2tabie<<DMA_IER_CH2TABIE_POS)
/**
  * @} MD_DMA_IER_CH2TABIE
  */
/** @defgroup MD_DMA_IER_CH2BTDIE CH2BTDIE
  * @brief  Set DMA Channel 2 Block Transmit Done Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch2btdie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch2btdie_fun(ch2btdie)  (ch2btdie<<DMA_IER_CH2BTDIE_POS)
/**
  * @} MD_DMA_IER_CH2BTDIE
  */
/** @defgroup MD_DMA_IER_CH1TABIE CH1TABIE
  * @brief  Set DMA Channel 1 TABORT Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch1tabie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch1tabie_fun(ch1tabie)  (ch1tabie<<DMA_IER_CH1TABIE_POS)
/**
  * @} MD_DMA_IER_CH1TABIE
  */
/** @defgroup MD_DMA_IER_CH1BTDIE CH1BTDIE
  * @brief  Set DMA Channel 1 Block Transmit Done Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch1btdie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch1btdie_fun(ch1btdie)  (ch1btdie<<DMA_IER_CH1BTDIE_POS)
/**
  * @} MD_DMA_IER_CH1BTDIE
  */
/** @defgroup MD_DMA_IER_CH0TABIE CH0TABIE
  * @brief  Set DMA Channel 0 TABORT Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch0tabie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch0tabie_fun(ch0tabie)  (ch0tabie<<DMA_IER_CH0TABIE_POS)
/**
  * @} MD_DMA_IER_CH0TABIE
  */
/** @defgroup MD_DMA_IER_CH0BTDIE CH0BTDIE
  * @brief  Set DMA Channel 0 Block Transmit Done Interrupt Enable bit for md_dma_set_ier() function used
  * @param  ch0btdie This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_ier_ch0btdie_fun(ch0btdie)  (ch0btdie<<DMA_IER_CH0BTDIE_POS)
/**
  * @} MD_DMA_IER_CH0BTDIE
  */
/**
  * @brief  Set DMA interrupt enable register
  * @param  dma DMA Instance
  * @param  ch5tabie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch5tabie_fun(ch5tabie)
  * @param  ch5btdie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch5btdie_fun(ch5btdie)
  * @param  ch4tabie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch4tabie_fun(ch4tabie)
  * @param  ch4btdie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch4btdie_fun(ch4btdie)
  * @param  ch3tabie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch3tabie_fun(ch3tabie)
  * @param  ch3btdie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch3btdie_fun(ch3btdie)
  * @param  ch2tabie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch2tabie_fun(ch2tabie)
  * @param  ch2btdie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch2btdie_fun(ch2btdie)
  * @param  ch1tabie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch1tabie_fun(ch1tabie)
  * @param  ch1btdie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch1btdie_fun(ch1btdie)
  * @param  ch0tabie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch0tabie_fun(ch0tabie)
  * @param  ch0btdie can be one of the following values:
  *         @arg @ref md_dma_set_ier_ch0btdie_fun(ch0btdie)
  * @retval None
  */
__STATIC_INLINE void md_dma_set_ier(DMA_TypeDef *dma, uint32_t ch5tabie,  uint32_t ch5btdie,
                                                      uint32_t ch4tabie,  uint32_t ch4btdie,
                                                      uint32_t ch3tabie,  uint32_t ch3btdie,
                                                      uint32_t ch2tabie,  uint32_t ch2btdie,
                                                      uint32_t ch1tabie,  uint32_t ch1btdie,
                                                      uint32_t ch0tabie,  uint32_t ch0btdie)
{
  WRITE_REG(dma->IER, (ch5tabie|ch5btdie|ch4tabie|ch4btdie|ch3tabie|ch3btdie|ch2tabie|ch2btdie|ch1tabie|ch1btdie|ch0tabie|ch0btdie));
}

/**
  * @brief  DMA Channel 5 TABORT Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch5tabid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH5TABID_MSK);
}
/**
  * @brief  DMA Channel 5 Block Transmit Done Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch5btdid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH5BTDID_MSK);
}
/**
  * @brief  DMA Channel 4 TABORT Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch4tabid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH4TABID_MSK);
}
/**
  * @brief  DMA Channel 4 Block Transmit Done Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch4btdid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH4BTDID_MSK);
}
/**
  * @brief  DMA Channel 3 TABORT Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch3tabid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH3TABID_MSK);
}
/**
  * @brief  DMA Channel 3 Block Transmit Done Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch3btdid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH3BTDID_MSK);
}
/**
  * @brief  DMA Channel 2 TABORT Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch2tabid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH2TABID_MSK);
}
/**
  * @brief  DMA Channel 2 Block Transmit Done Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch2btdid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH2BTDID_MSK);
}
/**
  * @brief  DMA Channel 1 TABORT Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch1tabid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH1TABID_MSK);
}
/**
  * @brief  DMA Channel 1 Block Transmit Done Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch1btdid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH1BTDID_MSK);
}
/**
  * @brief  DMA Channel 0 TABORT Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch0tabid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH0TABID_MSK);
}
/**
  * @brief  DMA Channel 0 Block Transmit Done Interrupt Disable bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_enable_idr_ch0btdid(DMA_TypeDef *dma)
{
  SET_BIT(dma->IDR, DMA_IDR_CH0BTDID_MSK);
}


/**
  * @brief  DMA Channel 5 TABORT Interrupt Valid Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch5tabivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH5TABIVS_MSK)>>DMA_IVS_CH5TABIVS_POS);
}
/**
  * @brief  DMA Channel 5 Block Transmit Done Interrupt Valid Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch5btdivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH5BTDIVS_MSK)>>DMA_IVS_CH5BTDIVS_POS);
}
/**
  * @brief  DMA Channel 4 TABORT Interrupt Valid Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch4tabivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH4TABIVS_MSK)>>DMA_IVS_CH4TABIVS_POS);
}
/**
  * @brief  DMA Channel 4 Block Transmit Done Interrupt Valid Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch4btdivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH4BTDIVS_MSK)>>DMA_IVS_CH4BTDIVS_POS);
}
/**
  * @brief  DMA Channel 3 TABORT Interrupt Valid Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch3tabivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH3TABIVS_MSK)>>DMA_IVS_CH3TABIVS_POS);
}
/**
  * @brief  DMA Channel 3 Block Transmit Done Interrupt Valid Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch3btdivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH3BTDIVS_MSK)>>DMA_IVS_CH3BTDIVS_POS);
}
/**
  * @brief  DMA Channel 2 TABORT Interrupt Valid Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch2tabivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH2TABIVS_MSK)>>DMA_IVS_CH2TABIVS_POS);
}
/**
  * @brief  DMA Channel 2 Block Transmit Done Interrupt Valid Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch2btdivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH2BTDIVS_MSK)>>DMA_IVS_CH2BTDIVS_POS);
}
/**
  * @brief  DMA Channel 1 TABORT Interrupt Valid Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch1tabivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH1TABIVS_MSK)>>DMA_IVS_CH1TABIVS_POS);
}
/**
  * @brief  DMA Channel 1 Block Transmit Done Interrupt Valid Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch1btdivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH1BTDIVS_MSK)>>DMA_IVS_CH1BTDIVS_POS);
}
/**
  * @brief  DMA Channel 0 TABORT Interrupt Valid Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch0tabivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH0TABIVS_MSK)>>DMA_IVS_CH0TABIVS_POS);
}
/**
  * @brief  DMA Channel 0 Block Transmit Done Interrupt Valid Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch0btdivs(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IVS, DMA_IVS_CH0BTDIVS_MSK)>>DMA_IVS_CH0BTDIVS_POS);
}
/**
  * @brief  Get DMA interrupt valid status register
  * @param  dma DMA Instance
  * @retval DMA channel interrupt valid status
  */
__STATIC_INLINE uint32_t md_dma_get_ivs(DMA_TypeDef *dma)
{
  return (READ_REG(dma->IVS));
}

/**
  * @brief  DMA Channel 5 TABORT Raw Interrupt Flag Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch5tabrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH5TABRIF_MSK)>>DMA_RIF_CH5TABRIF_POS);
}
/**
  * @brief  DMA Channel 5 Block Transmit Done Raw Interrupt Flag Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch5btdrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH5BTDRIF_MSK)>>DMA_RIF_CH5BTDRIF_POS);
}
/**
  * @brief  DMA Channel 4 TABORT Raw Interrupt Flag Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch4tabrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH4TABRIF_MSK)>>DMA_RIF_CH4TABRIF_POS);
}
/**
  * @brief  DMA Channel 4 Block Transmit Done Raw Interrupt Flag Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch4btdrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH4BTDRIF_MSK)>>DMA_RIF_CH4BTDRIF_POS);
}
/**
  * @brief  DMA Channel 3 TABORT Raw Interrupt Flag Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch3tabrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH3TABRIF_MSK)>>DMA_RIF_CH3TABRIF_POS);
}
/**
  * @brief  DMA Channel 3 Block Transmit Done Raw Interrupt Flag Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch3btdrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH3BTDRIF_MSK)>>DMA_RIF_CH3BTDRIF_POS);
}
/**
  * @brief  DMA Channel 2 TABORT Raw Interrupt Flag Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch2tabrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH2TABRIF_MSK)>>DMA_RIF_CH2TABRIF_POS);
}
/**
  * @brief  DMA Channel 2 Block Transmit Done Raw Interrupt Flag Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch2btdrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH2BTDRIF_MSK)>>DMA_RIF_CH2BTDRIF_POS);
}
/**
  * @brief  DMA Channel 1 TABORT Raw Interrupt Flag Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch1tabrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH1TABRIF_MSK)>>DMA_RIF_CH1TABRIF_POS);
}
/**
  * @brief  DMA Channel 1 Block Transmit Done Raw Interrupt Flag Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch1btdrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH1BTDRIF_MSK)>>DMA_RIF_CH1BTDRIF_POS);
}
/**
  * @brief  DMA Channel 0 TABORT Raw Interrupt Flag Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch0tabrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH0TABRIF_MSK)>>DMA_RIF_CH0TABRIF_POS);
}
/**
  * @brief  DMA Channel 0 Block Transmit Done Raw Interrupt Flag Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ivs_ch0btdrif(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->RIF, DMA_RIF_CH0BTDRIF_MSK)>>DMA_RIF_CH0BTDRIF_POS);
}
/**
  * @brief  Get DMA raw interrupt flag status register
  * @param  dma DMA Instance
  * @retval DMA channel raw interrupt flag status
  */
__STATIC_INLINE uint32_t md_dma_get_rif(DMA_TypeDef *dma)
{
  return (READ_REG(dma->RIF));
}

/**
  * @brief  DMA Channel 5 TABORT Interrupt Flag Masked Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch5tabifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH5TABIFM_MSK)>>DMA_IFM_CH5TABIFM_POS);
}
/**
  * @brief  DMA Channel 5 Block Transmit Done Interrupt Flag Masked Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch5btdifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH5BTDIFM_MSK)>>DMA_IFM_CH5BTDIFM_POS);
}
/**
  * @brief  DMA Channel 4 TABORT Interrupt Flag Masked Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch4tabifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH4TABIFM_MSK)>>DMA_IFM_CH4TABIFM_POS);
}
/**
  * @brief  DMA Channel 4 Block Transmit Done Interrupt Flag Masked Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch4btdifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH4BTDIFM_MSK)>>DMA_IFM_CH4BTDIFM_POS);
}
/**
  * @brief  DMA Channel 3 TABORT Interrupt Flag Masked Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch3tabifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH3TABIFM_MSK)>>DMA_IFM_CH3TABIFM_POS);
}
/**
  * @brief  DMA Channel 3 Block Transmit Done Interrupt Flag Masked Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch3btdifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH3BTDIFM_MSK)>>DMA_IFM_CH3BTDIFM_POS);
}
/**
  * @brief  DMA Channel 2 TABORT Interrupt Flag Masked Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch2tabifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH2TABIFM_MSK)>>DMA_IFM_CH2TABIFM_POS);
}
/**
  * @brief  DMA Channel 2 Block Transmit Done Interrupt Flag Masked Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch2btdifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH2BTDIFM_MSK)>>DMA_IFM_CH2BTDIFM_POS);
}
/**
  * @brief  DMA Channel 1 TABORT Interrupt Flag Masked Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch1tabifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH1TABIFM_MSK)>>DMA_IFM_CH1TABIFM_POS);
}
/**
  * @brief  DMA Channel 1 Block Transmit Done Interrupt Flag Masked Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch1btdifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH1BTDIFM_MSK)>>DMA_IFM_CH1BTDIFM_POS);
}
/**
  * @brief  DMA Channel 0 TABORT Interrupt Flag Masked Status bit
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch0tabifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH0TABIFM_MSK)>>DMA_IFM_CH0TABIFM_POS);
}
/**
  * @brief  DMA Channel 0 Block Transmit Done Interrupt Flag Masked Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_ifm_ch0btdifm(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->IFM, DMA_IFM_CH0BTDIFM_MSK)>>DMA_IFM_CH0BTDIFM_POS);
}
/**
  * @brief  Get DMA interrupt flag masked status register
  * @param  dma DMA Instance
  * @retval DMA channel interrupt flag masked status
  */
__STATIC_INLINE uint32_t md_dma_get_ifm(DMA_TypeDef *dma)
{
  return (READ_REG(dma->IFM));
}


/**
  * @brief  DMA Channel 5 TABORT Interrupt Clear bit
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch5tabicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH5TABICR_MSK);
}
/**
  * @brief  DMA Channel 5 Block Transmit Done Interrupt Clear bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch5btdicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH5BTDICR_MSK);
}
/**
  * @brief  DMA Channel 4 TABORT Interrupt Clear bit
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch4tabicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH4TABICR_MSK);
}
/**
  * @brief  DMA Channel 4 Block Transmit Done Interrupt Clear bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch4btdicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH4BTDICR_MSK);
}
/**
  * @brief  DMA Channel 3 TABORT Interrupt Clear bit
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch3tabicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH3TABICR_MSK);
}
/**
  * @brief  DMA Channel 3 Block Transmit Done Interrupt Clear bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch3btdicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH3BTDICR_MSK);
}
/**
  * @brief  DMA Channel 2 TABORT Interrupt Clear bit
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch2tabicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH2TABICR_MSK);
}
/**
  * @brief  DMA Channel 2 Block Transmit Done Interrupt Clear bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch2btdicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH2BTDICR_MSK);
}
/**
  * @brief  DMA Channel 1 TABORT Interrupt Clear bit
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch1tabicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH1TABICR_MSK);
}
/**
  * @brief  DMA Channel 1 Block Transmit Done Interrupt Clear bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch1btdicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH1BTDICR_MSK);
}
/**
  * @brief  DMA Channel 0 TABORT Interrupt Clear bit
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch0tabicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH0TABICR_MSK);
}
/**
  * @brief  DMA Channel 0 Block Transmit Done Interrupt Clear bit.
  * @param  dma DMA Instance
  * @retval None
  */
__STATIC_INLINE void md_dma_clear_icr_ch0btdicr(DMA_TypeDef *dma)
{
  SET_BIT(dma->ICR, DMA_ICR_CH0BTDICR_MSK);
}

/** @defgroup MD_DMA_ICR_CH5TABICR CH5TABICR
  * @brief  Set DMA Channel 5 TABORT Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch5tabicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch5tabicr_fun(ch5tabicr)  (ch5tabicr<<DMA_ICR_CH5TABICR_POS)
/**
  * @} MD_DMA_ICR_CH5TABICR
  */
/** @defgroup MD_DMA_ICR_CH5BTDICR CH5BTDICR
  * @brief  Set DMA Channel 5 Block Transmit Done Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch5btdicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch5btdicr_fun(ch5btdicr)  (ch5btdicr<<DMA_ICR_CH5BTDICR_POS)
/**
  * @} MD_DMA_ICR_CH5BTDICR
  */
/** @defgroup MD_DMA_ICR_CH4TABICR CH4TABICR
  * @brief  Set DMA Channel 4 TABORT Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch4tabicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch4tabicr_fun(ch4tabicr)  (ch4tabicr<<DMA_ICR_CH4TABICR_POS)
/**
  * @} MD_DMA_ICR_CH4TABICR
  */
/** @defgroup MD_DMA_ICR_CH4BTDICR CH4BTDICR
  * @brief  Set DMA Channel 4 Block Transmit Done Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch4btdicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch4btdicr_fun(ch4btdicr)  (ch4btdicr<<DMA_ICR_CH4BTDICR_POS)
/**
  * @} MD_DMA_ICR_CH4BTDICR
  */
/** @defgroup MD_DMA_ICR_CH3TABICR CH3TABICR
  * @brief  Set DMA Channel 3 TABORT Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch3tabicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch3tabicr_fun(ch3tabicr)  (ch3tabicr<<DMA_ICR_CH3TABICR_POS)
/**
  * @} MD_DMA_ICR_CH3TABICR
  */
/** @defgroup MD_DMA_ICR_CH3BTDICR CH3BTDICR
  * @brief  Set DMA Channel 3 Block Transmit Done Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch3btdicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch3btdicr_fun(ch3btdicr)  (ch3btdicr<<DMA_ICR_CH3BTDICR_POS)
/**
  * @} MD_DMA_ICR_CH3BTDICR
  */
/** @defgroup MD_DMA_ICR_CH2TABICR CH2TABICR
  * @brief  Set DMA Channel 2 TABORT Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch2tabicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch2tabicr_fun(ch2tabicr)  (ch2tabicr<<DMA_ICR_CH2TABICR_POS)
/**
  * @} MD_DMA_ICR_CH2TABICR
  */
/** @defgroup MD_DMA_ICR_CH2BTDICR CH2BTDICR
  * @brief  Set DMA Channel 2 Block Transmit Done Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch2btdicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch2btdicr_fun(ch2btdicr)  (ch2btdicr<<DMA_ICR_CH2BTDICR_POS)
/**
  * @} MD_DMA_ICR_CH2BTDICR
  */
/** @defgroup MD_DMA_ICR_CH1TABICR CH1TABICR
  * @brief  Set DMA Channel 1 TABORT Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch1tabicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch1tabicr_fun(ch1tabicr)  (ch1tabicr<<DMA_ICR_CH1TABICR_POS)
/**
  * @} MD_DMA_ICR_CH1TABICR
  */
/** @defgroup MD_DMA_ICR_CH1BTDICR CH1BTDICR
  * @brief  Set DMA Channel 1 Block Transmit Done Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch1btdicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch1btdicr_fun(ch1btdicr)  (ch1btdicr<<DMA_ICR_CH1BTDICR_POS)
/**
  * @} MD_DMA_ICR_CH1BTDICR
  */
/** @defgroup MD_DMA_ICR_CH0TABICR CH0TABICR
  * @brief  Set DMA Channel 0 TABORT Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch0tabicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch0tabicr_fun(ch0tabicr)  (ch0tabicr<<DMA_ICR_CH0TABICR_POS)
/**
  * @} MD_DMA_ICR_CH0TABICR
  */
/** @defgroup MD_DMA_ICR_CH0BTDICR CH0BTDICR
  * @brief  Set DMA Channel 0 Block Transmit Done Interrupt Clear bit for md_dma_set_icr() function used
  * @param  ch0btdicr This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @{
  */
#define md_dma_set_icr_ch0btdicr_fun(ch0btdicr)  (ch0btdicr<<DMA_ICR_CH0BTDICR_POS)
/**
  * @} MD_DMA_ICR_CH0BTDICR
  */
/**
  * @brief  Set DMA interrupt clear register(1)
  * @param  dma DMA Instance
  * @param  ch5tabicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch5tabicr_fun(ch5tabicr)
  * @param  ch5btdicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch5btdicr_fun(ch5btdicr)
  * @param  ch4tabicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch4tabicr_fun(ch4tabicr)
  * @param  ch4btdicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch4btdicr_fun(ch4btdicr)
  * @param  ch3tabicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch3tabicr_fun(ch3tabicr)
  * @param  ch3btdicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch3btdicr_fun(ch3btdicr)
  * @param  ch2tabicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch2tabicr_fun(ch2tabicr)
  * @param  ch2btdicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch2btdicr_fun(ch2btdicr)
  * @param  ch1tabicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch1tabicr_fun(ch1tabicr)
  * @param  ch1btdicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch1btdicr_fun(ch1btdicr)
  * @param  ch0tabicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch0tabicr_fun(ch0tabicr)
  * @param  ch0btdicr can be one of the following values:
  *         @arg @ref md_dma_set_icr_ch0btdicr_fun(ch0btdicr)
  * @retval None
  */
__STATIC_INLINE void md_dma_set_icr(DMA_TypeDef *dma, uint32_t ch5tabicr,  uint32_t ch5btdicr,
                                                      uint32_t ch4tabicr,  uint32_t ch4btdicr,
                                                      uint32_t ch3tabicr,  uint32_t ch3btdicr,
                                                      uint32_t ch2tabicr,  uint32_t ch2btdicr,
                                                      uint32_t ch1tabicr,  uint32_t ch1btdicr,
                                                      uint32_t ch0tabicr,  uint32_t ch0btdicr)
{
  WRITE_REG(dma->ICR, ( ch5tabicr|ch5btdicr|ch4tabicr|ch4btdicr|ch3tabicr|ch3btdicr|ch2tabicr|ch2btdicr|
                        ch1tabicr|ch1btdicr|ch0tabicr|ch0btdicr));
}
/**
  * @brief  Set DMA interrupt clear register(2)
  * @param  dma DMA Instance
  * @param  icr is interrupt clear register
  * @retval None
  */
__STATIC_INLINE void md_dma_set_icr_icr(DMA_TypeDef *dma, uint32_t icr)
{
  WRITE_REG(dma->ICR, icr);
}


/**
  * @brief  DMA Channel 5 PFCTRL Size not match,last data have error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch5pfser(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH5PFSER_MSK)>>DMA_EMSG_CH5PFSER_POS);
}
/**
  * @brief  DMA Channel 5 PFCTRL Over run Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch5pfov(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH5PFOV_MSK)>>DMA_EMSG_CH5PFOV_POS);
}
/**
  * @brief  DMA Channel 5 Setting Burst Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch5setbuer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH5SETBUER_MSK)>>DMA_EMSG_CH5SETBUER_POS);
}
/**
  * @brief  DMA Channel 5 Setting BCR Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch5setbcer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH5SETBCER_MSK)>>DMA_EMSG_CH5SETBCER_POS);
}
/**
  * @brief  DMA Channel 4 PFCTRL Size not match,last data have error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch4pfser(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH4PFSER_MSK)>>DMA_EMSG_CH4PFSER_POS);
}
/**
  * @brief  DMA Channel 4 PFCTRL Over run Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch4pfov(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH4PFOV_MSK)>>DMA_EMSG_CH4PFOV_POS);
}
/**
  * @brief  DMA Channel 4 Setting Burst Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch4setbuer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH4SETBUER_MSK)>>DMA_EMSG_CH4SETBUER_POS);
}
/**
  * @brief  DMA Channel 4 Setting BCR Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch4setbcer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH4SETBCER_MSK)>>DMA_EMSG_CH4SETBCER_POS);
}
/**
  * @brief  DMA Channel 3 PFCTRL Size not match,last data have error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch3pfser(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH3PFSER_MSK)>>DMA_EMSG_CH3PFSER_POS);
}
/**
  * @brief  DMA Channel 3 PFCTRL Over run Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch3pfov(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH3PFOV_MSK)>>DMA_EMSG_CH3PFOV_POS);
}
/**
  * @brief  DMA Channel 3 Setting Burst Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch3setbuer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH3SETBUER_MSK)>>DMA_EMSG_CH3SETBUER_POS);
}
/**
  * @brief  DMA Channel 3 Setting BCR Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch3setbcer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH3SETBCER_MSK)>>DMA_EMSG_CH3SETBCER_POS);
}
/**
  * @brief  DMA Channel 2 PFCTRL Size not match,last data have error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch2pfser(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH2PFSER_MSK)>>DMA_EMSG_CH2PFSER_POS);
}
/**
  * @brief  DMA Channel 2 PFCTRL Over run Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch2pfov(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH2PFOV_MSK)>>DMA_EMSG_CH2PFOV_POS);
}
/**
  * @brief  DMA Channel 2 Setting Burst Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch2setbuer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH2SETBUER_MSK)>>DMA_EMSG_CH2SETBUER_POS);
}
/**
  * @brief  DMA Channel 2 Setting BCR Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch2setbcer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH2SETBCER_MSK)>>DMA_EMSG_CH2SETBCER_POS);
}
/**
  * @brief  DMA Channel 1 PFCTRL Size not match,last data have error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch1pfser(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH1PFSER_MSK)>>DMA_EMSG_CH1PFSER_POS);
}
/**
  * @brief  DMA Channel 1 PFCTRL Over run Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch1pfov(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH1PFOV_MSK)>>DMA_EMSG_CH1PFOV_POS);
}
/**
  * @brief  DMA Channel 1 Setting Burst Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch1setbuer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH1SETBUER_MSK)>>DMA_EMSG_CH1SETBUER_POS);
}
/**
  * @brief  DMA Channel 1 Setting BCR Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch1setbcer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH1SETBCER_MSK)>>DMA_EMSG_CH1SETBCER_POS);
}
/**
  * @brief  DMA Channel 0 PFCTRL Size not match,last data have error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch0pfser(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH0PFSER_MSK)>>DMA_EMSG_CH0PFSER_POS);
}
/**
  * @brief  DMA Channel 0 PFCTRL Over run Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch0pfov(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH0PFOV_MSK)>>DMA_EMSG_CH0PFOV_POS);
}
/**
  * @brief  DMA Channel 0 Setting Burst Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch0setbuer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH0SETBUER_MSK)>>DMA_EMSG_CH0SETBUER_POS);
}
/**
  * @brief  DMA Channel 0 Setting BCR Error Status bit.
  * @param  dma DMA Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dma_get_emsg_ch0setbcer(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->EMSG, DMA_EMSG_CH0SETBCER_MSK)>>DMA_EMSG_CH0SETBCER_POS);
}
/**
  * @brief  Get DMA error message register
  * @param  dma DMA Instance
  * @retval DMA channel error message status
  */
__STATIC_INLINE uint32_t md_dma_get_emsg(DMA_TypeDef *dma)
{
  return (READ_REG(dma->EMSG));
}

/**
  * @brief  Set Destination Increment Offset Size bit.
  * @note   This bit has no meaning if bit DINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if DBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  dincos can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_dincos(DMA_TypeDef *dma, uint32_t dincos)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_DINCOS_MSK, (dincos<<DMA_CSR0_DINCOS_POS));
}
/**
  * @brief  Get Destination Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_dincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_DINCOS_MSK)>>DMA_CSR0_DINCOS_POS);
}
/**
  * @brief  Set Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  dbusel can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_dbusel(DMA_TypeDef *dma, uint32_t dbusel)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_DBUSEL_MSK, (dbusel<<DMA_CSR0_DBUSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_dbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_DBUSEL_MSK)>>DMA_CSR0_DBUSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  ddwsel can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_ddwsel(DMA_TypeDef *dma, uint32_t ddwsel)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_DDWSEL_MSK, (ddwsel<<DMA_CSR0_DDWSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_ddwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_DDWSEL_MSK)>>DMA_CSR0_DDWSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  dinc can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_dinc(DMA_TypeDef *dma, uint32_t dinc)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_DINC_MSK, (dinc<<DMA_CSR0_DINC_POS));
}
/**
  * @brief  Get Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_dinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_DINC_MSK)>>DMA_CSR0_DINC_POS);
}
/**
  * @brief  Set Source Increment Offset Size bit.
  * @note   This bit has no meaning if bit SINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if SBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  sincos can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_sincos(DMA_TypeDef *dma, uint32_t sincos)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_SINCOS_MSK, (sincos<<DMA_CSR0_SINCOS_POS));
}
/**
  * @brief  Get Source Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_sincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_SINCOS_MSK)>>DMA_CSR0_SINCOS_POS);
}
/**
  * @brief  Set Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  sbusel can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_sbusel(DMA_TypeDef *dma, uint32_t sbusel)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_SBUSEL_MSK, (sbusel<<DMA_CSR0_SBUSEL_POSS));
}
/**
  * @brief  Get Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_sbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_SBUSEL_MSK)>>DMA_CSR0_SBUSEL_POSS);
}
/**
  * @brief  Set Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  sdwsel can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_sdwsel(DMA_TypeDef *dma, uint32_t sdwsel)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_SDWSEL_MSK, (sdwsel<<DMA_CSR0_SDWSEL_POSS));
}
/**
  * @brief  Get Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_sdwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_SDWSEL_MSK)>>DMA_CSR0_SDWSEL_POSS);
}
/**
  * @brief  Set Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  sinc can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_sinc(DMA_TypeDef *dma, uint32_t sinc)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_SINC_MSK, (sinc<<DMA_CSR0_SINC_POS));
}
/**
  * @brief  Get Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_sinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_SINC_MSK)>>DMA_CSR0_SINC_POS);
}
/**
  * @brief  Set Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @param  phss can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_phss(DMA_TypeDef *dma, uint32_t phss)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_PHSS_MSK, (phss<<DMA_CSR0_PHSS_POSS));
}
/**
  * @brief  Get Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_phss(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_PHSS_MSK)>>DMA_CSR0_PHSS_POSS);
}
/**
  * @brief  Set DMA Channel Priority.
  * @param  dma DMA Instance
  * @param  chpri can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_chpri(DMA_TypeDef *dma, uint32_t chpri)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_CHPRI_MSK, (chpri<<DMA_CSR0_CHPRI_POSS));
}
/**
  * @brief  Get DMA Channel Priority.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_chpri(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_CHPRI_MSK)>>DMA_CSR0_CHPRI_POSS);
}
/**
  * @brief  Set DMA Mode Select.
  * @param  dma DMA Instance
  * @param  modesel can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_modesel(DMA_TypeDef *dma, uint32_t modesel)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_MODESEL_MSK, (modesel<<DMA_CSR0_MODESEL_POSS));
}
/**
  * @brief  Get DMA Mode Select.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_modesel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_MODESEL_MSK)>>DMA_CSR0_MODESEL_POSS);
}
/**
  * @brief  Set Direct Mode Enable.
  * @param  dma DMA Instance
  * @param  dirmden can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_dirmden(DMA_TypeDef *dma, uint32_t dirmden)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_DIRMDEN_MSK, (dirmden<<DMA_CSR0_DIRMDEN_POS));
}
/**
  * @brief  Get Direct Mode Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_dirmden(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_DIRMDEN_MSK)>>DMA_CSR0_DIRMDEN_POS);
}
/**
  * @brief  Set Peripheral flow controller
  * @param  dma DMA Instance
  * @param  pfctrl can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_pfctrl(DMA_TypeDef *dma, uint32_t pfctrl)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_PFCTRL_MSK, (pfctrl<<DMA_CSR0_PFCTRL_POS));
}
/**
  * @brief  Get Peripheral flow controller
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_pfctrl(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_PFCTRL_MSK)>>DMA_CSR0_PFCTRL_POS);
}
/**
  * @brief  Set Circular mode
  * @param  dma DMA Instance
  * @param  circ can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_circ(DMA_TypeDef *dma, uint32_t circ)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_CIRC_MSK, (circ<<DMA_CSR0_CIRC_POS));
}
/**
  * @brief  Get Circular mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_circ(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_CIRC_MSK)>>DMA_CSR0_CIRC_POS);
}
/**
  * @brief  Set DMA Channel Enable.
  * @param  dma DMA Instance
  * @param  chen can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0_chen(DMA_TypeDef *dma, uint32_t chen)
{
  MODIFY_REG(dma->CSR0, DMA_CSR0_CHEN_MSK, (chen<<DMA_CSR0_CHEN_POS));
}
/**
  * @brief  Get DMA Channel Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr0_chen(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR0, DMA_CSR0_CHEN_MSK)>>DMA_CSR0_CHEN_POS);
}

/** @defgroup MD_DMA_CSR0_DINCOS DINCOS
  * @brief  Set Destination Increment Offset Size bit for md_dma_set_cs0() function used
  * @param  dincos This parameter can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  * @{
  */
#define md_dma_set_csr0_dincos_fun(dincos)  (dincos<<DMA_CSR0_DINCOS_POS)
/**
  * @} MD_DMA_CSR0_DINCOS
  */
/** @defgroup MD_DMA_CSR0_DBUSEL DBUSEL
  * @brief  Set Destination Transfer Burst Selection bit for md_dma_set_cs0() function used
  * @param  dbusel This parameter can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  * @{
  */
#define md_dma_set_csr0_dbusel_fun(dbusel)  (dbusel<<DMA_CSR0_DBUSEL_POSS)
/**
  * @} MD_DMA_CSR0_DBUSEL
  */
/** @defgroup MD_DMA_CSR0_DDWSEL DDWSEL
  * @brief  Set Destination Transfer Data Width Selection bit for md_dma_set_cs0() function used
  * @param  ddwsel This parameter can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  * @{
  */
#define md_dma_set_csr0_ddwsel_fun(ddwsel)  (ddwsel<<DMA_CSR0_DDWSEL_POSS)
/**
  * @} MD_DMA_CSR0_DDWSEL
  */
/** @defgroup MD_DMA_CSR0_DINC DINC
  * @brief  Set Destination Transfer Increment Mode bit for md_dma_set_cs0() function used
  * @param  dinc This parameter can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @{
  */
#define md_dma_set_csr0_dinc_fun(dinc)  (dinc<<DMA_CSR0_DINC_POS)
/**
  * @} MD_DMA_CSR0_DINC
  */
/** @defgroup MD_DMA_CSR0_SINCOS SINCOS
  * @brief  Set Source Increment Offset Size bit for md_dma_set_cs0() function used
  * @param  sincos This parameter can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  * @{
  */
#define md_dma_set_csr0_sincos_fun(sincos)  (sincos<<DMA_CSR0_SINCOS_POS)
/**
  * @} MD_DMA_CSR0_SINCOS
  */
/** @defgroup MD_DMA_CSR0_SBUSEL SBUSEL
  * @brief  Set Source Transfer Burst Selection bit for md_dma_set_cs0() function used
  * @param  sbusel This parameter can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  * @{
  */
#define md_dma_set_csr0_sbusel_fun(sbusel)  (sbusel<<DMA_CSR0_SBUSEL_POSS)
/**
  * @} MD_DMA_CSR0_SBUSEL
  */
/** @defgroup MD_DMA_CSR0_SDWSEL SDWSEL
  * @brief  Set Source Transfer Data Width Selection bit for md_dma_set_cs0() function used
  * @param  sdwsel This parameter can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  * @{
  */
#define md_dma_set_csr0_sdwsel_fun(sdwsel)  (sdwsel<<DMA_CSR0_SDWSEL_POSS)
/**
  * @} MD_DMA_CSR0_SDWSEL
  */
/** @defgroup MD_DMA_CSR0_SINC SINC
  * @brief  Set Source Transfer Increment Mode bit for md_dma_set_cs0() function used
  * @param  sinc This parameter can be one of the following values:
  *         @arg DISABLE
  *         @arg ENABLE
  * @{
  */
#define md_dma_set_csr0_sinc_fun(sinc)  (sinc<<DMA_CSR0_SINC_POS)
/**
  * @} MD_DMA_CSR0_SINC
  */
/** @defgroup MD_DMA_CSR0_PHSS PHSS
  * @brief  Set Peripheral Handshake Software Select bit for md_dma_set_cs0() function used
  * @param  phss This parameter can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  * @{
  */
#define md_dma_set_csr0_phss_fun(phss)  (phss<<DMA_CSR0_PHSS_POSS)
/**
  * @} MD_DMA_CSR0_PHSS
  */
/** @defgroup MD_DMA_CSR0_CHPRI CHPRI
  * @brief  Set DMA Channel Priority bit for md_dma_set_cs0() function used
  * @param  chpri This parameter can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  * @{
  */
#define md_dma_set_csr0_chpri_fun(chpri)  (chpri<<DMA_CSR0_CHPRI_POSS)
/**
  * @} MD_DMA_CSR0_CHPRI
  */
/** @defgroup MD_DMA_CSR0_MODESEL MODESEL
  * @brief  Set DMA Mode Select bit for md_dma_set_cs0() function used
  * @param  modesel This parameter can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  * @{
  */
#define md_dma_set_csr0_modesel_fun(modesel)  (modesel<<DMA_CSR0_MODESEL_POSS)
/**
  * @} MD_DMA_CSR0_MODESEL
  */
/** @defgroup MD_DMA_CSR0_DIRMDEN DIRMDEN
  * @brief  Set Direct Mode Enable bit for md_dma_set_cs0() function used
  * @param  dirmden This parameter can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @{
  */
#define md_dma_set_csr0_dirmden_fun(dirmden)  (dirmden<<DMA_CSR0_DIRMDEN_POS)
/**
  * @} MD_DMA_CSR0_DIRMDEN
  */
/** @defgroup MD_DMA_CSR0_PFCTRL PFCTRL
  * @brief  Set Peripheral flow controller bit for md_dma_set_cs0() function used
  * @param  pfctrl This parameter can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  * @{
  */
#define md_dma_set_csr0_pfctrl_fun(pfctrl)  (pfctrl<<DMA_CSR0_PFCTRL_POS)
/**
  * @} MD_DMA_CSR0_PFCTRL
  */
/** @defgroup MD_DMA_CSR0_CIRC CIRC
  * @brief  Set Circular mode bit for md_dma_set_cs0() function used
  * @param  circ This parameter can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @{
  */
#define md_dma_set_csr0_circ_fun(circ)  (circ<<DMA_CSR0_CIRC_POS)
/**
  * @} MD_DMA_CSR0_CIRC
  */
/** @defgroup MD_DMA_CSR0_CHEN CHEN
  * @brief  Set DMA Channel Enable bit for md_dma_set_cs0() function used
  * @param  chen This parameter can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @{
  */
#define md_dma_set_csr0_chen_fun(chen)  (chen<<DMA_CSR0_CHEN_POS)
/**
  * @} MD_DMA_CSR0_CHEN
  */
/**
  * @brief  Set DMA interrupt clear register(1)
  * @param  dma DMA Instance
  * @param  dincos can be one of the following values:
  *         @arg @ref md_dma_set_csr0_dincos_fun(dincos)
  * @param  dbusel can be one of the following values:
  *         @arg @ref md_dma_set_csr0_dbusel_fun(dbusel)
  * @param  ddwsel can be one of the following values:
  *         @arg @ref md_dma_set_csr0_ddwsel_fun(ddwsel)
  * @param  dinc can be one of the following values:
  *         @arg @ref md_dma_set_csr0_dinc_fun(dinc)
  * @param  sincos can be one of the following values:
  *         @arg @ref md_dma_set_csr0_sincos_fun(sincos)
  * @param  sbusel can be one of the following values:
  *         @arg @ref md_dma_set_csr0_sbusel_fun(sbusel)
  * @param  sdwsel can be one of the following values:
  *         @arg @ref md_dma_set_csr0_sdwsel_fun(sdwsel)
  * @param  sinc can be one of the following values:
  *         @arg @ref md_dma_set_csr0_sinc_fun(sinc)
  * @param  phss can be one of the following values:
  *         @arg @ref md_dma_set_csr0_phss_fun(phss)
  * @param  chpri can be one of the following values:
  *         @arg @ref md_dma_set_csr0_chpri_fun(chpri)
  * @param  modesel can be one of the following values:
  *         @arg @ref md_dma_set_csr0_modesel_fun(modesel)
  * @param  dirmden can be one of the following values:
  *         @arg @ref md_dma_set_csr0_dirmden_fun(dirmden)
  * @param  pfctrl can be one of the following values:
  *         @arg @ref md_dma_set_csr0_pfctrl_fun(pfctrl)
  * @param  circ can be one of the following values:
  *         @arg @ref md_dma_set_csr0_circ_fun(circ)
  * @param  chen can be one of the following values:
  *         @arg @ref md_dma_set_csr0_chen_fun(chen)
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr0(DMA_TypeDef *dma,  uint32_t dincos,  uint32_t dbusel,  uint32_t ddwsel,
                                                        uint32_t dinc,    uint32_t sincos,  uint32_t sbusel,
                                                        uint32_t sdwsel,  uint32_t sinc,    uint32_t phss,
                                                        uint32_t chpri,   uint32_t modesel, uint32_t dirmden,
                                                        uint32_t pfctrl,  uint32_t circ,    uint32_t chen)
{
  WRITE_REG(dma->CSR0, (dincos|dbusel|ddwsel|dinc|sincos|sbusel|sdwsel|sinc|
                        phss|chpri|modesel|dirmden|pfctrl|circ|chen));
}


/**
  * @brief  Set DMA Transfer Source Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  sar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_sar0_sar(DMA_TypeDef *dma, uint32_t sar)
{
  MODIFY_REG(dma->SAR0, DMA_SAR0_SAR_MSK, (sar<<DMA_SAR0_SAR_POSS));
}
/**
  * @brief  Get DMA Transfer Source Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_sar0_sar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->SAR0, DMA_SAR0_SAR_MSK)>>DMA_SAR0_SAR_POSS);
}

/**
  * @brief  Set DMA Transfer Destination Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  dar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_dar0_dar(DMA_TypeDef *dma, uint32_t dar)
{
  MODIFY_REG(dma->DAR0, DMA_DAR0_DAR_MSK, (dar<<DMA_DAR0_DAR_POSS));
}
/**
  * @brief  Get DMA Transfer Destination Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_dar0_dar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->DAR0, DMA_DAR0_DAR_MSK)>>DMA_DAR0_DAR_POSS);
}

/**
  * @brief  Get DMA Current Transfer Byte Count
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr0_cbcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR0, DMA_BCR0_CBCR_MSK)>>DMA_BCR0_CBCR_POSS);
}
/**
  * @brief  Set DMA Transfer Byte Count Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  bcr This field indicates a 16-bit transfer byte count of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_bcr0_bcr(DMA_TypeDef *dma, uint32_t bcr)
{
  MODIFY_REG(dma->BCR0, DMA_BCR0_BCR_MSK, (bcr<<DMA_BCR0_BCR_POSS));
}
/**
  * @brief  Get DMA Transfer Byte Count Register
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr0_bcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR0, DMA_BCR0_BCR_MSK)>>DMA_BCR0_BCR_POSS);
}

/**
  * @brief  Set Destination Increment Offset Size bit.
  * @note   This bit has no meaning if bit DINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if DBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  dincos can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_dincos(DMA_TypeDef *dma, uint32_t dincos)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_DINCOS_MSK, (dincos<<DMA_CSR1_DINCOS_POS));
}
/**
  * @brief  Get Destination Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_dincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_DINCOS_MSK)>>DMA_CSR1_DINCOS_POS);
}
/**
  * @brief  Set Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  dbusel can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_dbusel(DMA_TypeDef *dma, uint32_t dbusel)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_DBUSEL_MSK, (dbusel<<DMA_CSR1_DBUSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_dbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_DBUSEL_MSK)>>DMA_CSR1_DBUSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  ddwsel can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_ddwsel(DMA_TypeDef *dma, uint32_t ddwsel)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_DDWSEL_MSK, (ddwsel<<DMA_CSR1_DDWSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_ddwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_DDWSEL_MSK)>>DMA_CSR1_DDWSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  dinc can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_dinc(DMA_TypeDef *dma, uint32_t dinc)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_DINC_MSK, (dinc<<DMA_CSR1_DINC_POS));
}
/**
  * @brief  Get Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_dinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_DINC_MSK)>>DMA_CSR1_DINC_POS);
}
/**
  * @brief  Set Source Increment Offset Size bit.
  * @note   This bit has no meaning if bit SINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if SBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  sincos can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_sincos(DMA_TypeDef *dma, uint32_t sincos)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_SINCOS_MSK, (sincos<<DMA_CSR1_SINCOS_POS));
}
/**
  * @brief  Get Source Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_sincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_SINCOS_MSK)>>DMA_CSR1_SINCOS_POS);
}
/**
  * @brief  Set Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  sbusel can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_sbusel(DMA_TypeDef *dma, uint32_t sbusel)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_SBUSEL_MSK, (sbusel<<DMA_CSR1_SBUSEL_POSS));
}
/**
  * @brief  Get Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_sbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_SBUSEL_MSK)>>DMA_CSR1_SBUSEL_POSS);
}
/**
  * @brief  Set Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  sdwsel can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_sdwsel(DMA_TypeDef *dma, uint32_t sdwsel)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_SDWSEL_MSK, (sdwsel<<DMA_CSR1_SDWSEL_POSS));
}
/**
  * @brief  Get Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_sdwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_SDWSEL_MSK)>>DMA_CSR1_SDWSEL_POSS);
}
/**
  * @brief  Set Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  dinc can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_sinc(DMA_TypeDef *dma, uint32_t dinc)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_SINC_MSK, (dinc<<DMA_CSR1_SINC_POS));
}
/**
  * @brief  Get Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_sinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_SINC_MSK)>>DMA_CSR1_SINC_POS);
}
/**
  * @brief  Set Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @param  phss can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_phss(DMA_TypeDef *dma, uint32_t phss)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_PHSS_MSK, (phss<<DMA_CSR1_PHSS_POSS));
}
/**
  * @brief  Get Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_phss(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_PHSS_MSK)>>DMA_CSR1_PHSS_POSS);
}
/**
  * @brief  Set DMA Channel Priority.
  * @param  dma DMA Instance
  * @param  chpri can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_chpri(DMA_TypeDef *dma, uint32_t chpri)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_CHPRI_MSK, (chpri<<DMA_CSR1_CHPRI_POSS));
}
/**
  * @brief  Get DMA Channel Priority.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_chpri(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_CHPRI_MSK)>>DMA_CSR1_CHPRI_POSS);
}
/**
  * @brief  Set DMA Mode Select.
  * @param  dma DMA Instance
  * @param  modesel can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_modesel(DMA_TypeDef *dma, uint32_t modesel)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_MODESEL_MSK, (modesel<<DMA_CSR1_MODESEL_POSS));
}
/**
  * @brief  Get DMA Mode Select.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_modesel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_MODESEL_MSK)>>DMA_CSR1_MODESEL_POSS);
}
/**
  * @brief  Set Direct Mode Enable.
  * @param  dma DMA Instance
  * @param  dirmden can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_dirmden(DMA_TypeDef *dma, uint32_t dirmden)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_DIRMDEN_MSK, (dirmden<<DMA_CSR1_DIRMDEN_POS));
}
/**
  * @brief  Get Direct Mode Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_dirmden(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_DIRMDEN_MSK)>>DMA_CSR1_DIRMDEN_POS);
}
/**
  * @brief  Set Peripheral flow controller
  * @param  dma DMA Instance
  * @param  pfctrl can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_pfctrl(DMA_TypeDef *dma, uint32_t pfctrl)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_PFCTRL_MSK, (pfctrl<<DMA_CSR1_PFCTRL_POS));
}
/**
  * @brief  Get Peripheral flow controller
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_pfctrl(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_PFCTRL_MSK)>>DMA_CSR1_PFCTRL_POS);
}
/**
  * @brief  Set Circular mode
  * @param  dma DMA Instance
  * @param  circ can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_circ(DMA_TypeDef *dma, uint32_t circ)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_CIRC_MSK, (circ<<DMA_CSR1_CIRC_POS));
}
/**
  * @brief  Get Circular mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_circ(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_CIRC_MSK)>>DMA_CSR1_CIRC_POS);
}
/**
  * @brief  Set DMA Channel Enable.
  * @param  dma DMA Instance
  * @param  chen can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr1_chen(DMA_TypeDef *dma, uint32_t chen)
{
  MODIFY_REG(dma->CSR1, DMA_CSR1_CHEN_MSK, (chen<<DMA_CSR1_CHEN_POS));
}
/**
  * @brief  Get DMA Channel Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr1_chen(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR1, DMA_CSR1_CHEN_MSK)>>DMA_CSR1_CHEN_POS);
}

/**
  * @brief  Set DMA Transfer Source Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  sar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_sar1_sar(DMA_TypeDef *dma, uint32_t sar)
{
  MODIFY_REG(dma->SAR1, DMA_SAR1_SAR_MSK, (sar<<DMA_SAR1_SAR_POSS));
}
/**
  * @brief  Get DMA Transfer Source Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_sar1_sar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->SAR1, DMA_SAR1_SAR_MSK)>>DMA_SAR1_SAR_POSS);
}

/**
  * @brief  Set DMA Transfer Destination Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  dar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_dar1_dar(DMA_TypeDef *dma, uint32_t dar)
{
  MODIFY_REG(dma->DAR1, DMA_DAR1_DAR_MSK, (dar<<DMA_DAR1_DAR_POSS));
}
/**
  * @brief  Get DMA Transfer Destination Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_dar1_dar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->DAR1, DMA_DAR1_DAR_MSK)>>DMA_DAR1_DAR_POSS);
}

/**
  * @brief  Get DMA Current Transfer Byte Count
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr1_cbcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR1, DMA_BCR1_CBCR_MSK)>>DMA_BCR1_CBCR_POSS);
}
/**
  * @brief  Set DMA Transfer Byte Count Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  bcr This field indicates a 16-bit transfer byte count of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_bcr1_bcr(DMA_TypeDef *dma, uint32_t bcr)
{
  MODIFY_REG(dma->BCR1, DMA_BCR1_BCR_MSK, (bcr<<DMA_BCR1_BCR_POSS));
}
/**
  * @brief  Get DMA Transfer Byte Count Register
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr1_bcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR1, DMA_BCR1_BCR_MSK)>>DMA_BCR1_BCR_POSS);
}

/**
  * @brief  Set Destination Increment Offset Size bit.
  * @note   This bit has no meaning if bit DINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if DBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  dincos can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_dincos(DMA_TypeDef *dma, uint32_t dincos)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_DINCOS_MSK, (dincos<<DMA_CSR2_DINCOS_POS));
}
/**
  * @brief  Get Destination Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_dincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_DINCOS_MSK)>>DMA_CSR2_DINCOS_POS);
}
/**
  * @brief  Set Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  dbusel can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_dbusel(DMA_TypeDef *dma, uint32_t dbusel)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_DBUSEL_MSK, (dbusel<<DMA_CSR2_DBUSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_dbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_DBUSEL_MSK)>>DMA_CSR2_DBUSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  ddwsel can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_ddwsel(DMA_TypeDef *dma, uint32_t ddwsel)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_DDWSEL_MSK, (ddwsel<<DMA_CSR2_DDWSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_ddwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_DDWSEL_MSK)>>DMA_CSR2_DDWSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  dinc can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_dinc(DMA_TypeDef *dma, uint32_t dinc)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_DINC_MSK, (dinc<<DMA_CSR2_DINC_POS));
}
/**
  * @brief  Get Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_dinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_DINC_MSK)>>DMA_CSR2_DINC_POS);
}
/**
  * @brief  Set Source Increment Offset Size bit.
  * @note   This bit has no meaning if bit SINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if SBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  sincos can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_sincos(DMA_TypeDef *dma, uint32_t sincos)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_SINCOS_MSK, (sincos<<DMA_CSR2_SINCOS_POS));
}
/**
  * @brief  Get Source Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_sincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_SINCOS_MSK)>>DMA_CSR2_SINCOS_POS);
}
/**
  * @brief  Set Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  sbusel can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_sbusel(DMA_TypeDef *dma, uint32_t sbusel)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_SBUSEL_MSK, (sbusel<<DMA_CSR2_SBUSEL_POSS));
}
/**
  * @brief  Get Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_sbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_SBUSEL_MSK)>>DMA_CSR2_SBUSEL_POSS);
}
/**
  * @brief  Set Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  sdwsel can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_sdwsel(DMA_TypeDef *dma, uint32_t sdwsel)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_SDWSEL_MSK, (sdwsel<<DMA_CSR2_SDWSEL_POSS));
}
/**
  * @brief  Get Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_sdwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_SDWSEL_MSK)>>DMA_CSR2_SDWSEL_POSS);
}
/**
  * @brief  Set Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  dinc can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_sinc(DMA_TypeDef *dma, uint32_t dinc)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_SINC_MSK, (dinc<<DMA_CSR2_SINC_POS));
}
/**
  * @brief  Get Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_sinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_SINC_MSK)>>DMA_CSR2_SINC_POS);
}
/**
  * @brief  Set Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @param  phss can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_phss(DMA_TypeDef *dma, uint32_t phss)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_PHSS_MSK, (phss<<DMA_CSR2_PHSS_POSS));
}
/**
  * @brief  Get Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_phss(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_PHSS_MSK)>>DMA_CSR2_PHSS_POSS);
}
/**
  * @brief  Set DMA Channel Priority.
  * @param  dma DMA Instance
  * @param  chpri can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_chpri(DMA_TypeDef *dma, uint32_t chpri)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_CHPRI_MSK, (chpri<<DMA_CSR2_CHPRI_POSS));
}
/**
  * @brief  Get DMA Channel Priority.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_chpri(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_CHPRI_MSK)>>DMA_CSR2_CHPRI_POSS);
}
/**
  * @brief  Set DMA Mode Select.
  * @param  dma DMA Instance
  * @param  modesel can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_modesel(DMA_TypeDef *dma, uint32_t modesel)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_MODESEL_MSK, (modesel<<DMA_CSR2_MODESEL_POSS));
}
/**
  * @brief  Get DMA Mode Select.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_modesel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_MODESEL_MSK)>>DMA_CSR2_MODESEL_POSS);
}
/**
  * @brief  Set Direct Mode Enable.
  * @param  dma DMA Instance
  * @param  dirmden can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_dirmden(DMA_TypeDef *dma, uint32_t dirmden)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_DIRMDEN_MSK, (dirmden<<DMA_CSR2_DIRMDEN_POS));
}
/**
  * @brief  Get Direct Mode Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_dirmden(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_DIRMDEN_MSK)>>DMA_CSR2_DIRMDEN_POS);
}
/**
  * @brief  Set Peripheral flow controller
  * @param  dma DMA Instance
  * @param  pfctrl can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_pfctrl(DMA_TypeDef *dma, uint32_t pfctrl)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_PFCTRL_MSK, (pfctrl<<DMA_CSR2_PFCTRL_POS));
}
/**
  * @brief  Get Peripheral flow controller
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_pfctrl(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_PFCTRL_MSK)>>DMA_CSR2_PFCTRL_POS);
}
/**
  * @brief  Set Circular mode
  * @param  dma DMA Instance
  * @param  circ can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_circ(DMA_TypeDef *dma, uint32_t circ)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_CIRC_MSK, (circ<<DMA_CSR2_CIRC_POS));
}
/**
  * @brief  Get Circular mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_circ(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_CIRC_MSK)>>DMA_CSR2_CIRC_POS);
}
/**
  * @brief  Set DMA Channel Enable.
  * @param  dma DMA Instance
  * @param  chen can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr2_chen(DMA_TypeDef *dma, uint32_t chen)
{
  MODIFY_REG(dma->CSR2, DMA_CSR2_CHEN_MSK, (chen<<DMA_CSR2_CHEN_POS));
}
/**
  * @brief  Get DMA Channel Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr2_chen(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR2, DMA_CSR2_CHEN_MSK)>>DMA_CSR2_CHEN_POS);
}

/**
  * @brief  Set DMA Transfer Source Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  sar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_sar2_sar(DMA_TypeDef *dma, uint32_t sar)
{
  MODIFY_REG(dma->SAR2, DMA_SAR2_SAR_MSK, (sar<<DMA_SAR2_SAR_POSS));
}
/**
  * @brief  Get DMA Transfer Source Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_sar2_sar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->SAR2, DMA_SAR2_SAR_MSK)>>DMA_SAR2_SAR_POSS);
}

/**
  * @brief  Set DMA Transfer Destination Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  dar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_dar2_dar(DMA_TypeDef *dma, uint32_t dar)
{
  MODIFY_REG(dma->DAR2, DMA_DAR2_DAR_MSK, (dar<<DMA_DAR2_DAR_POSS));
}
/**
  * @brief  Get DMA Transfer Destination Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_dar2_dar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->DAR2, DMA_DAR2_DAR_MSK)>>DMA_DAR2_DAR_POSS);
}

/**
  * @brief  Get DMA Current Transfer Byte Count
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr2_cbcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR2, DMA_BCR2_CBCR_MSK)>>DMA_BCR2_CBCR_POSS);
}
/**
  * @brief  Set DMA Transfer Byte Count Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  bcr This field indicates a 16-bit transfer byte count of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_bcr2_bcr(DMA_TypeDef *dma, uint32_t bcr)
{
  MODIFY_REG(dma->BCR2, DMA_BCR2_BCR_MSK, (bcr<<DMA_BCR2_BCR_POSS));
}
/**
  * @brief  Get DMA Transfer Byte Count Register
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr2_bcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR2, DMA_BCR2_BCR_MSK)>>DMA_BCR2_BCR_POSS);
}

/**
  * @brief  Set Destination Increment Offset Size bit.
  * @note   This bit has no meaning if bit DINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if DBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  dincos can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_dincos(DMA_TypeDef *dma, uint32_t dincos)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_DINCOS_MSK, (dincos<<DMA_CSR3_DINCOS_POS));
}
/**
  * @brief  Get Destination Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_dincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_DINCOS_MSK)>>DMA_CSR3_DINCOS_POS);
}
/**
  * @brief  Set Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  dbusel can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_dbusel(DMA_TypeDef *dma, uint32_t dbusel)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_DBUSEL_MSK, (dbusel<<DMA_CSR3_DBUSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_dbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_DBUSEL_MSK)>>DMA_CSR3_DBUSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  ddwsel can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_ddwsel(DMA_TypeDef *dma, uint32_t ddwsel)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_DDWSEL_MSK, (ddwsel<<DMA_CSR3_DDWSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_ddwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_DDWSEL_MSK)>>DMA_CSR3_DDWSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  dinc can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_dinc(DMA_TypeDef *dma, uint32_t dinc)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_DINC_MSK, (dinc<<DMA_CSR3_DINC_POS));
}
/**
  * @brief  Get Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_dinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_DINC_MSK)>>DMA_CSR3_DINC_POS);
}
/**
  * @brief  Set Source Increment Offset Size bit.
  * @note   This bit has no meaning if bit SINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if SBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  sincos can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_sincos(DMA_TypeDef *dma, uint32_t sincos)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_SINCOS_MSK, (sincos<<DMA_CSR3_SINCOS_POS));
}
/**
  * @brief  Get Source Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_sincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_SINCOS_MSK)>>DMA_CSR3_SINCOS_POS);
}
/**
  * @brief  Set Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  sbusel can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_sbusel(DMA_TypeDef *dma, uint32_t sbusel)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_SBUSEL_MSK, (sbusel<<DMA_CSR3_SBUSEL_POSS));
}
/**
  * @brief  Get Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_sbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_SBUSEL_MSK)>>DMA_CSR3_SBUSEL_POSS);
}
/**
  * @brief  Set Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  sdwsel can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_sdwsel(DMA_TypeDef *dma, uint32_t sdwsel)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_SDWSEL_MSK, (sdwsel<<DMA_CSR3_SDWSEL_POSS));
}
/**
  * @brief  Get Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_sdwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_SDWSEL_MSK)>>DMA_CSR3_SDWSEL_POSS);
}
/**
  * @brief  Set Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  dinc can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_sinc(DMA_TypeDef *dma, uint32_t dinc)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_SINC_MSK, (dinc<<DMA_CSR3_SINC_POS));
}
/**
  * @brief  Get Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_sinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_SINC_MSK)>>DMA_CSR3_SINC_POS);
}
/**
  * @brief  Set Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @param  phss can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_phss(DMA_TypeDef *dma, uint32_t phss)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_PHSS_MSK, (phss<<DMA_CSR3_PHSS_POSS));
}
/**
  * @brief  Get Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_phss(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_PHSS_MSK)>>DMA_CSR3_PHSS_POSS);
}
/**
  * @brief  Set DMA Channel Priority.
  * @param  dma DMA Instance
  * @param  chpri can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_chpri(DMA_TypeDef *dma, uint32_t chpri)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_CHPRI_MSK, (chpri<<DMA_CSR3_CHPRI_POSS));
}
/**
  * @brief  Get DMA Channel Priority.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_chpri(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_CHPRI_MSK)>>DMA_CSR3_CHPRI_POSS);
}
/**
  * @brief  Set DMA Mode Select.
  * @param  dma DMA Instance
  * @param  modesel can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_modesel(DMA_TypeDef *dma, uint32_t modesel)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_MODESEL_MSK, (modesel<<DMA_CSR3_MODESEL_POSS));
}
/**
  * @brief  Get DMA Mode Select.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_modesel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_MODESEL_MSK)>>DMA_CSR3_MODESEL_POSS);
}
/**
  * @brief  Set Direct Mode Enable.
  * @param  dma DMA Instance
  * @param  dirmden can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_dirmden(DMA_TypeDef *dma, uint32_t dirmden)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_DIRMDEN_MSK, (dirmden<<DMA_CSR3_DIRMDEN_POS));
}
/**
  * @brief  Get Direct Mode Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_dirmden(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_DIRMDEN_MSK)>>DMA_CSR3_DIRMDEN_POS);
}
/**
  * @brief  Set Peripheral flow controller
  * @param  dma DMA Instance
  * @param  pfctrl can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_pfctrl(DMA_TypeDef *dma, uint32_t pfctrl)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_PFCTRL_MSK, (pfctrl<<DMA_CSR3_PFCTRL_POS));
}
/**
  * @brief  Get Peripheral flow controller
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_pfctrl(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_PFCTRL_MSK)>>DMA_CSR3_PFCTRL_POS);
}
/**
  * @brief  Set Circular mode
  * @param  dma DMA Instance
  * @param  circ can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_circ(DMA_TypeDef *dma, uint32_t circ)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_CIRC_MSK, (circ<<DMA_CSR3_CIRC_POS));
}
/**
  * @brief  Get Circular mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_circ(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_CIRC_MSK)>>DMA_CSR3_CIRC_POS);
}
/**
  * @brief  Set DMA Channel Enable.
  * @param  dma DMA Instance
  * @param  chen can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr3_chen(DMA_TypeDef *dma, uint32_t chen)
{
  MODIFY_REG(dma->CSR3, DMA_CSR3_CHEN_MSK, (chen<<DMA_CSR3_CHEN_POS));
}
/**
  * @brief  Get DMA Channel Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr3_chen(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR3, DMA_CSR3_CHEN_MSK)>>DMA_CSR3_CHEN_POS);
}

/**
  * @brief  Set DMA Transfer Source Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  sar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_sar3_sar(DMA_TypeDef *dma, uint32_t sar)
{
  MODIFY_REG(dma->SAR3, DMA_SAR3_SAR_MSK, (sar<<DMA_SAR3_SAR_POSS));
}
/**
  * @brief  Get DMA Transfer Source Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_sar3_sar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->SAR3, DMA_SAR3_SAR_MSK)>>DMA_SAR3_SAR_POSS);
}

/**
  * @brief  Set DMA Transfer Destination Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  dar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_dar3_dar(DMA_TypeDef *dma, uint32_t dar)
{
  MODIFY_REG(dma->DAR3, DMA_DAR3_DAR_MSK, (dar<<DMA_DAR3_DAR_POSS));
}
/**
  * @brief  Get DMA Transfer Destination Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_dar3_dar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->DAR3, DMA_DAR3_DAR_MSK)>>DMA_DAR3_DAR_POSS);
}

/**
  * @brief  Get DMA Current Transfer Byte Count
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr3_cbcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR3, DMA_BCR3_CBCR_MSK)>>DMA_BCR3_CBCR_POSS);
}
/**
  * @brief  Set DMA Transfer Byte Count Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  bcr This field indicates a 16-bit transfer byte count of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_bcr3_bcr(DMA_TypeDef *dma, uint32_t bcr)
{
  MODIFY_REG(dma->BCR3, DMA_BCR3_BCR_MSK, (bcr<<DMA_BCR3_BCR_POSS));
}
/**
  * @brief  Get DMA Transfer Byte Count Register
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr3_bcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR3, DMA_BCR3_BCR_MSK)>>DMA_BCR3_BCR_POSS);
}

/**
  * @brief  Set Destination Increment Offset Size bit.
  * @note   This bit has no meaning if bit DINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if DBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  dincos can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_dincos(DMA_TypeDef *dma, uint32_t dincos)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_DINCOS_MSK, (dincos<<DMA_CSR4_DINCOS_POS));
}
/**
  * @brief  Get Destination Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_dincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_DINCOS_MSK)>>DMA_CSR4_DINCOS_POS);
}
/**
  * @brief  Set Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  dbusel can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_dbusel(DMA_TypeDef *dma, uint32_t dbusel)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_DBUSEL_MSK, (dbusel<<DMA_CSR4_DBUSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_dbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_DBUSEL_MSK)>>DMA_CSR4_DBUSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  ddwsel can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_ddwsel(DMA_TypeDef *dma, uint32_t ddwsel)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_DDWSEL_MSK, (ddwsel<<DMA_CSR4_DDWSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_ddwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_DDWSEL_MSK)>>DMA_CSR4_DDWSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  dinc can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_dinc(DMA_TypeDef *dma, uint32_t dinc)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_DINC_MSK, (dinc<<DMA_CSR4_DINC_POS));
}
/**
  * @brief  Get Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_dinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_DINC_MSK)>>DMA_CSR4_DINC_POS);
}
/**
  * @brief  Set Source Increment Offset Size bit.
  * @note   This bit has no meaning if bit SINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if SBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  sincos can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_sincos(DMA_TypeDef *dma, uint32_t sincos)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_SINCOS_MSK, (sincos<<DMA_CSR4_SINCOS_POS));
}
/**
  * @brief  Get Source Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_sincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_SINCOS_MSK)>>DMA_CSR4_SINCOS_POS);
}
/**
  * @brief  Set Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  sbusel can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_sbusel(DMA_TypeDef *dma, uint32_t sbusel)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_SBUSEL_MSK, (sbusel<<DMA_CSR4_SBUSEL_POSS));
}
/**
  * @brief  Get Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_sbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_SBUSEL_MSK)>>DMA_CSR4_SBUSEL_POSS);
}
/**
  * @brief  Set Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  sdwsel can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_sdwsel(DMA_TypeDef *dma, uint32_t sdwsel)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_SDWSEL_MSK, (sdwsel<<DMA_CSR4_SDWSEL_POSS));
}
/**
  * @brief  Get Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_sdwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_SDWSEL_MSK)>>DMA_CSR4_SDWSEL_POSS);
}
/**
  * @brief  Set Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  dinc can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_sinc(DMA_TypeDef *dma, uint32_t dinc)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_SINC_MSK, (dinc<<DMA_CSR4_SINC_POS));
}
/**
  * @brief  Get Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_sinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_SINC_MSK)>>DMA_CSR4_SINC_POS);
}
/**
  * @brief  Set Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @param  phss can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_phss(DMA_TypeDef *dma, uint32_t phss)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_PHSS_MSK, (phss<<DMA_CSR4_PHSS_POSS));
}
/**
  * @brief  Get Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_phss(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_PHSS_MSK)>>DMA_CSR4_PHSS_POSS);
}
/**
  * @brief  Set DMA Channel Priority.
  * @param  dma DMA Instance
  * @param  chpri can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_chpri(DMA_TypeDef *dma, uint32_t chpri)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_CHPRI_MSK, (chpri<<DMA_CSR4_CHPRI_POSS));
}
/**
  * @brief  Get DMA Channel Priority.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_chpri(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_CHPRI_MSK)>>DMA_CSR4_CHPRI_POSS);
}
/**
  * @brief  Set DMA Mode Select.
  * @param  dma DMA Instance
  * @param  modesel can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_modesel(DMA_TypeDef *dma, uint32_t modesel)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_MODESEL_MSK, (modesel<<DMA_CSR4_MODESEL_POSS));
}
/**
  * @brief  Get DMA Mode Select.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_modesel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_MODESEL_MSK)>>DMA_CSR4_MODESEL_POSS);
}
/**
  * @brief  Set Direct Mode Enable.
  * @param  dma DMA Instance
  * @param  dirmden can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_dirmden(DMA_TypeDef *dma, uint32_t dirmden)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_DIRMDEN_MSK, (dirmden<<DMA_CSR4_DIRMDEN_POS));
}
/**
  * @brief  Get Direct Mode Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_dirmden(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_DIRMDEN_MSK)>>DMA_CSR4_DIRMDEN_POS);
}
/**
  * @brief  Set Peripheral flow controller
  * @param  dma DMA Instance
  * @param  pfctrl can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_pfctrl(DMA_TypeDef *dma, uint32_t pfctrl)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_PFCTRL_MSK, (pfctrl<<DMA_CSR4_PFCTRL_POS));
}
/**
  * @brief  Get Peripheral flow controller
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_pfctrl(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_PFCTRL_MSK)>>DMA_CSR4_PFCTRL_POS);
}
/**
  * @brief  Set Circular mode
  * @param  dma DMA Instance
  * @param  circ can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_circ(DMA_TypeDef *dma, uint32_t circ)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_CIRC_MSK, (circ<<DMA_CSR4_CIRC_POS));
}
/**
  * @brief  Get Circular mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_circ(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_CIRC_MSK)>>DMA_CSR4_CIRC_POS);
}
/**
  * @brief  Set DMA Channel Enable.
  * @param  dma DMA Instance
  * @param  chen can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr4_chen(DMA_TypeDef *dma, uint32_t chen)
{
  MODIFY_REG(dma->CSR4, DMA_CSR4_CHEN_MSK, (chen<<DMA_CSR4_CHEN_POS));
}
/**
  * @brief  Get DMA Channel Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr4_chen(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR4, DMA_CSR4_CHEN_MSK)>>DMA_CSR4_CHEN_POS);
}

/**
  * @brief  Set DMA Transfer Source Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  sar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_sar4_sar(DMA_TypeDef *dma, uint32_t sar)
{
  MODIFY_REG(dma->SAR4, DMA_SAR4_SAR_MSK, (sar<<DMA_SAR4_SAR_POSS));
}
/**
  * @brief  Get DMA Transfer Source Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_sar4_sar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->SAR4, DMA_SAR4_SAR_MSK)>>DMA_SAR4_SAR_POSS);
}

/**
  * @brief  Set DMA Transfer Destination Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  dar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_dar4_dar(DMA_TypeDef *dma, uint32_t dar)
{
  MODIFY_REG(dma->DAR4, DMA_DAR4_DAR_MSK, (dar<<DMA_DAR4_DAR_POSS));
}
/**
  * @brief  Get DMA Transfer Destination Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_dar4_dar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->DAR4, DMA_DAR4_DAR_MSK)>>DMA_DAR4_DAR_POSS);
}

/**
  * @brief  Get DMA Current Transfer Byte Count
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr4_cbcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR4, DMA_BCR4_CBCR_MSK)>>DMA_BCR4_CBCR_POSS);
}
/**
  * @brief  Set DMA Transfer Byte Count Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  bcr This field indicates a 16-bit transfer byte count of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_bcr4_bcr(DMA_TypeDef *dma, uint32_t bcr)
{
  MODIFY_REG(dma->BCR4, DMA_BCR4_BCR_MSK, (bcr<<DMA_BCR4_BCR_POSS));
}
/**
  * @brief  Get DMA Transfer Byte Count Register
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr4_bcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR4, DMA_BCR4_BCR_MSK)>>DMA_BCR4_BCR_POSS);
}

/**
  * @brief  Set Destination Increment Offset Size bit.
  * @note   This bit has no meaning if bit DINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if DBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  dincos can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_dincos(DMA_TypeDef *dma, uint32_t dincos)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_DINCOS_MSK, (dincos<<DMA_CSR5_DINCOS_POS));
}
/**
  * @brief  Get Destination Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DINCOS_LINKED_DWSEL
  *         @arg @ref MD_DMA_DINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_dincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_DINCOS_MSK)>>DMA_CSR5_DINCOS_POS);
}
/**
  * @brief  Set Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  dbusel can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_dbusel(DMA_TypeDef *dma, uint32_t dbusel)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_DBUSEL_MSK, (dbusel<<DMA_CSR5_DBUSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DBUSEL_SINGLE
  *         @arg @ref MD_DMA_DBUSEL_WRAP4
  *         @arg @ref MD_DMA_DBUSEL_INCR4
  *         @arg @ref MD_DMA_DBUSEL_WRAP8
  *         @arg @ref MD_DMA_DBUSEL_INCR8
  *         @arg @ref MD_DMA_DBUSEL_WRAP16
  *         @arg @ref MD_DMA_DBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_dbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_DBUSEL_MSK)>>DMA_CSR5_DBUSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  ddwsel can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_ddwsel(DMA_TypeDef *dma, uint32_t ddwsel)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_DDWSEL_MSK, (ddwsel<<DMA_CSR5_DDWSEL_POSS));
}
/**
  * @brief  Get Destination Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_DDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_DDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_DDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_ddwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_DDWSEL_MSK)>>DMA_CSR5_DDWSEL_POSS);
}
/**
  * @brief  Set Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  dinc can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_dinc(DMA_TypeDef *dma, uint32_t dinc)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_DINC_MSK, (dinc<<DMA_CSR5_DINC_POS));
}
/**
  * @brief  Get Destination Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_dinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_DINC_MSK)>>DMA_CSR5_DINC_POS);
}
/**
  * @brief  Set Source Increment Offset Size bit.
  * @note   This bit has no meaning if bit SINC = '0'.
  *         This bit is protected and can be written only if EN = '0'.
  *         This bit is forced low by hardware when the stream is enabled (bit EN = '1') if the direct mode is selected or
  *         if SBUSEL are different from ¡§00¡¨.
  * @param  dma DMA Instance
  * @param  sincos can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_sincos(DMA_TypeDef *dma, uint32_t sincos)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_SINCOS_MSK, (sincos<<DMA_CSR5_SINCOS_POS));
}
/**
  * @brief  Get Source Increment Offset Size bit.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SINCOS_LINKED_SWSEL
  *         @arg @ref MD_DMA_SINCOS_FIXED_TO_4
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_sincos(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_SINCOS_MSK)>>DMA_CSR5_SINCOS_POS);
}
/**
  * @brief  Set Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @param  sbusel can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_sbusel(DMA_TypeDef *dma, uint32_t sbusel)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_SBUSEL_MSK, (sbusel<<DMA_CSR5_SBUSEL_POSS));
}
/**
  * @brief  Get Source Transfer Burst Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SBUSEL_SINGLE
  *         @arg @ref MD_DMA_SBUSEL_WRAP4
  *         @arg @ref MD_DMA_SBUSEL_INCR4
  *         @arg @ref MD_DMA_SBUSEL_WRAP8
  *         @arg @ref MD_DMA_SBUSEL_INCR8
  *         @arg @ref MD_DMA_SBUSEL_WRAP16
  *         @arg @ref MD_DMA_SBUSEL_INCR16
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_sbusel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_SBUSEL_MSK)>>DMA_CSR5_SBUSEL_POSS);
}
/**
  * @brief  Set Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @param  sdwsel can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_sdwsel(DMA_TypeDef *dma, uint32_t sdwsel)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_SDWSEL_MSK, (sdwsel<<DMA_CSR5_SDWSEL_POSS));
}
/**
  * @brief  Get Source Transfer Data Width Selection.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_SDWSEL_ONE_BYTE
  *         @arg @ref MD_DMA_SDWSEL_ONE_HALF_WORD
  *         @arg @ref MD_DMA_SDWSEL_ONE_WORD
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_sdwsel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_SDWSEL_MSK)>>DMA_CSR5_SDWSEL_POSS);
}
/**
  * @brief  Set Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @param  dinc can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_sinc(DMA_TypeDef *dma, uint32_t dinc)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_SINC_MSK, (dinc<<DMA_CSR5_SINC_POS));
}
/**
  * @brief  Get Source Transfer Increment Mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_sinc(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_SINC_MSK)>>DMA_CSR5_SINC_POS);
}
/**
  * @brief  Set Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @param  phss can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_phss(DMA_TypeDef *dma, uint32_t phss)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_PHSS_MSK, (phss<<DMA_CSR5_PHSS_POSS));
}
/**
  * @brief  Get Peripheral Handshake Software Select
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PHSS_UART1_TX
  *         @arg @ref MD_DMA_PHSS_UART2_TX
  *         @arg @ref MD_DMA_PHSS_UART3_TX
  *         @arg @ref MD_DMA_PHSS_SUART1_TX
  *         @arg @ref MD_DMA_PHSS_SUART2_TX
  *         @arg @ref MD_DMA_PHSS_SPI1_TX
  *         @arg @ref MD_DMA_PHSS_SPI2_TX
  *         @arg @ref MD_DMA_PHSS_I2C1_TX
  *         @arg @ref MD_DMA_PHSS_I2C2_TX
  *         @arg @ref MD_DMA_PHSS_AES_IN
  *         @arg @ref MD_DMA_PHSS_DAC
  *         @arg @ref MD_DMA_PHSS_CRC
  *         @arg @ref MD_DMA_PHSS_UART1_RX
  *         @arg @ref MD_DMA_PHSS_UART2_RX
  *         @arg @ref MD_DMA_PHSS_UART3_RX
  *         @arg @ref MD_DMA_PHSS_SUART1_RX
  *         @arg @ref MD_DMA_PHSS_SUART2_RX
  *         @arg @ref MD_DMA_PHSS_SPI1_RTX
  *         @arg @ref MD_DMA_PHSS_SPI2_RX
  *         @arg @ref MD_DMA_PHSS_I2C1_RX
  *         @arg @ref MD_DMA_PHSS_I2C2_RX
  *         @arg @ref MD_DMA_PHSS_AES_OUT
  *         @arg @ref MD_DMA_PHSS_ADCSS0
  *         @arg @ref MD_DMA_PHSS_ADCSS1
  *         @arg @ref MD_DMA_PHSS_ADCSS2
  *         @arg @ref MD_DMA_PHSS_ADCSS3
  *         @arg @ref MD_DMA_PHSS_BS16T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_AD16C4T1_COM
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP32C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH3
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_CH4
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C4T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T1_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T2_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T3_COM
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH1
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_CH2
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_UP
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_TRIG
  *         @arg @ref MD_DMA_PHSS_GP16C2T4_COM
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_phss(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_PHSS_MSK)>>DMA_CSR5_PHSS_POSS);
}
/**
  * @brief  Set DMA Channel Priority.
  * @param  dma DMA Instance
  * @param  chpri can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_chpri(DMA_TypeDef *dma, uint32_t chpri)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_CHPRI_MSK, (chpri<<DMA_CSR5_CHPRI_POSS));
}
/**
  * @brief  Get DMA Channel Priority.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_CHPRI_LV0
  *         @arg @ref MD_DMA_CHPRI_LV1
  *         @arg @ref MD_DMA_CHPRI_LV2
  *         @arg @ref MD_DMA_CHPRI_LV3
  *         @arg @ref MD_DMA_CHPRI_LV4
  *         @arg @ref MD_DMA_CHPRI_LV5
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_chpri(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_CHPRI_MSK)>>DMA_CSR5_CHPRI_POSS);
}
/**
  * @brief  Set DMA Mode Select.
  * @param  dma DMA Instance
  * @param  modesel can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_modesel(DMA_TypeDef *dma, uint32_t modesel)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_MODESEL_MSK, (modesel<<DMA_CSR5_MODESEL_POSS));
}
/**
  * @brief  Get DMA Mode Select.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_PER_TO_MEM
  *         @arg @ref MD_DMA_MODESEL_MEM_TO_PER
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_modesel(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_MODESEL_MSK)>>DMA_CSR5_MODESEL_POSS);
}
/**
  * @brief  Set Direct Mode Enable.
  * @param  dma DMA Instance
  * @param  dirmden can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_dirmden(DMA_TypeDef *dma, uint32_t dirmden)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_DIRMDEN_MSK, (dirmden<<DMA_CSR5_DIRMDEN_POS));
}
/**
  * @brief  Get Direct Mode Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_dirmden(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_DIRMDEN_MSK)>>DMA_CSR5_DIRMDEN_POS);
}
/**
  * @brief  Set Peripheral flow controller
  * @param  dma DMA Instance
  * @param  pfctrl can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_pfctrl(DMA_TypeDef *dma, uint32_t pfctrl)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_PFCTRL_MSK, (pfctrl<<DMA_CSR5_PFCTRL_POS));
}
/**
  * @brief  Get Peripheral flow controller
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_DMA_PFCTRL_DMA_CTRL
  *         @arg @ref MD_DMA_PFCTRL_PER_CTRL
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_pfctrl(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_PFCTRL_MSK)>>DMA_CSR5_PFCTRL_POS);
}
/**
  * @brief  Set Circular mode
  * @param  dma DMA Instance
  * @param  circ can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_circ(DMA_TypeDef *dma, uint32_t circ)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_CIRC_MSK, (circ<<DMA_CSR5_CIRC_POS));
}
/**
  * @brief  Get Circular mode
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_circ(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_CIRC_MSK)>>DMA_CSR5_CIRC_POS);
}
/**
  * @brief  Set DMA Channel Enable.
  * @param  dma DMA Instance
  * @param  chen can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  * @retval None
  */
__STATIC_INLINE void md_dma_set_csr5_chen(DMA_TypeDef *dma, uint32_t chen)
{
  MODIFY_REG(dma->CSR5, DMA_CSR5_CHEN_MSK, (chen<<DMA_CSR5_CHEN_POS));
}
/**
  * @brief  Get DMA Channel Enable.
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Disable
  *         @arg Enable
  */
__STATIC_INLINE uint32_t md_dma_get_csr5_chen(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->CSR5, DMA_CSR5_CHEN_MSK)>>DMA_CSR5_CHEN_POS);
}

/**
  * @brief  Set DMA Transfer Source Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  sar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_sar5_sar(DMA_TypeDef *dma, uint32_t sar)
{
  MODIFY_REG(dma->SAR5, DMA_SAR5_SAR_MSK, (sar<<DMA_SAR5_SAR_POSS));
}
/**
  * @brief  Get DMA Transfer Source Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_sar5_sar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->SAR5, DMA_SAR5_SAR_MSK)>>DMA_SAR5_SAR_POSS);
}

/**
  * @brief  Set DMA Transfer Destination Address Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  dar This field indicates a 32-bit source address of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_dar5_dar(DMA_TypeDef *dma, uint32_t dar)
{
  MODIFY_REG(dma->DAR5, DMA_DAR5_DAR_MSK, (dar<<DMA_DAR5_DAR_POSS));
}
/**
  * @brief  Get DMA Transfer Destination Address Register
  * @param  dma DMA Instance
  * @retval This field indicates a 32-bit source address of DMA.
  */
__STATIC_INLINE uint32_t md_dma_get_dar5_dar(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->DAR5, DMA_DAR5_DAR_MSK)>>DMA_DAR5_DAR_POSS);
}

/**
  * @brief  Get DMA Current Transfer Byte Count
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr5_cbcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR5, DMA_BCR5_CBCR_MSK)>>DMA_BCR5_CBCR_POSS);
}
/**
  * @brief  Set DMA Transfer Byte Count Register
  * @note   These bits are write-protected and can be written only when bit EN = '0'
  * @param  dma DMA Instance
  * @param  bcr This field indicates a 16-bit transfer byte count of DMA.
  * @retval None
  */
__STATIC_INLINE void md_dma_set_bcr5_bcr(DMA_TypeDef *dma, uint32_t bcr)
{
  MODIFY_REG(dma->BCR5, DMA_BCR5_BCR_MSK, (bcr<<DMA_BCR5_BCR_POSS));
}
/**
  * @brief  Get DMA Transfer Byte Count Register
  * @param  dma DMA Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 65535
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_dma_get_bcr5_bcr(DMA_TypeDef *dma)
{
  return (READ_BIT(dma->BCR5, DMA_BCR5_BCR_MSK)>>DMA_BCR5_BCR_POSS);
}

/**
  * @} MD_DMA_Public_Macros
  */

/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_DMA_Public_Functions DMA Public Functions
  * @{
  */

/** @defgroup MD_DMA_Basic_Configuration Basic Configuration
  * @{
  */

/**
  * @} MD_DMA_Basic_Configuration
  */


/**
  * @} MD_DMA_Public_Functions
  */

#endif

/**
  * @} DMA
  */

/**
  * @} Micro_Driver
  */


#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
