/*********************************************************************************************************//**
 * @file    ht32f66xxx_cordic.h
 * @version $Rev:: 8260         $
 * @date    $Date:: 2024-11-05 #$
 * @brief   The header file of the CORDIC library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F66XXX_CORDIC_H
#define __HT32F66XXX_CORDIC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup CORDIC
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup CORDIC_Exported_Types CORDIC exported types
  * @{
  */
typedef struct
{
  u32 Function;
  u32 Scale;
  u32 InSize;
  u32 OutSize;
  u32 NbWrite;
  u32 NbRead;
  u32 Precision;
} CORDIC_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup CORDIC_Exported_Constants CORDIC exported constants
  * @{
  */
/************************  Bit definition for CORDIC_CSR register  **********************/
#define CORDIC_CSR_FUNC_POS                (0U)
#define CORDIC_CSR_FUNC_MASK               (0xFUL << CORDIC_CSR_FUNC_POS)                /*!< 0x0000000F */
#define CORDIC_CSR_FUNC                    CORDIC_CSR_FUNC_MASK                          /*!< Function */
#define CORDIC_CSR_FUNC_0                  (0x1UL << CORDIC_CSR_FUNC_POS)                /*!< 0x00000001 */
#define CORDIC_CSR_FUNC_1                  (0x2UL << CORDIC_CSR_FUNC_POS)                /*!< 0x00000002 */
#define CORDIC_CSR_FUNC_2                  (0x4UL << CORDIC_CSR_FUNC_POS)                /*!< 0x00000004 */
#define CORDIC_CSR_FUNC_3                  (0x8UL << CORDIC_CSR_FUNC_POS)                /*!< 0x00000008 */
#define CORDIC_CSR_PRECISION_POS           (4U)
#define CORDIC_CSR_PRECISION_MASK          (0xFUL << CORDIC_CSR_PRECISION_POS)           /*!< 0x000000F0 */
#define CORDIC_CSR_PRECISION               CORDIC_CSR_PRECISION_MASK                     /*!< Precision */
#define CORDIC_CSR_PRECISION_0             (0x1UL << CORDIC_CSR_PRECISION_POS)           /*!< 0x00000010 */
#define CORDIC_CSR_PRECISION_1             (0x2UL << CORDIC_CSR_PRECISION_POS)           /*!< 0x00000020 */
#define CORDIC_CSR_PRECISION_2             (0x4UL << CORDIC_CSR_PRECISION_POS)           /*!< 0x00000040 */
#define CORDIC_CSR_PRECISION_3             (0x8UL << CORDIC_CSR_PRECISION_POS)           /*!< 0x00000080 */
#define CORDIC_CSR_SCALE_POS               (8U)
#define CORDIC_CSR_SCALE_MASK              (0x7UL << CORDIC_CSR_SCALE_POS)               /*!< 0x00000700 */
#define CORDIC_CSR_SCALE                   CORDIC_CSR_SCALE_MASK                         /*!< Scaling factor */
#define CORDIC_CSR_SCALE_0                 (0x1UL << CORDIC_CSR_SCALE_POS)               /*!< 0x00000100 */
#define CORDIC_CSR_SCALE_1                 (0x2UL << CORDIC_CSR_SCALE_POS)               /*!< 0x00000200 */
#define CORDIC_CSR_SCALE_2                 (0x4UL << CORDIC_CSR_SCALE_POS)               /*!< 0x00000400 */
#define CORDIC_CSR_IEN_POS                 (16U)
#define CORDIC_CSR_IEN_MASK                (0x1UL << CORDIC_CSR_IEN_POS)                 /*!< 0x00010000 */
#define CORDIC_CSR_IEN                     CORDIC_CSR_IEN_MASK                           /*!< Interrupt Enable */
#define CORDIC_CSR_DMAREN_POS              (17U)
#define CORDIC_CSR_DMAREN_MASK             (0x1UL << CORDIC_CSR_DMAREN_POS)              /*!< 0x00020000 */
#define CORDIC_CSR_DMAREN                  CORDIC_CSR_DMAREN_MASK                        /*!< DMA Read channel Enable */
#define CORDIC_CSR_DMAWEN_POS              (18U)
#define CORDIC_CSR_DMAWEN_MASK             (0x1UL << CORDIC_CSR_DMAWEN_POS)              /*!< 0x00040000 */
#define CORDIC_CSR_DMAWEN                  CORDIC_CSR_DMAWEN_MASK                        /*!< DMA Write channel Enable */
#define CORDIC_CSR_NRES_POS                (19U)
#define CORDIC_CSR_NRES_MASK               (0x1UL << CORDIC_CSR_NRES_POS)                /*!< 0x00080000 */
#define CORDIC_CSR_NRES                    CORDIC_CSR_NRES_MASK                          /*!< Number of results in WDATA register */
#define CORDIC_CSR_NARGS_POS               (20U)
#define CORDIC_CSR_NARGS_MASK              (0x3UL << CORDIC_CSR_NARGS_POS)               /*!< 0x00300000 */
#define CORDIC_CSR_NARGS                   CORDIC_CSR_NARGS_MASK                         /*!< Number of arguments in RDATA register */
#define CORDIC_CSR_NARGS_0                 (0x1UL << CORDIC_CSR_NARGS_POS)               /*!< 0x00100000 */
#define CORDIC_CSR_NARGS_1                 (0x2UL << CORDIC_CSR_NARGS_POS)               /*!< 0x00200000 */
#define CORDIC_CSR_RESSIZE_POS             (22U)
#define CORDIC_CSR_RESSIZE_MASK            (0x1UL << CORDIC_CSR_RESSIZE_POS)             /*!< 0x00400000 */
#define CORDIC_CSR_RESSIZE                 CORDIC_CSR_RESSIZE_MASK                       /*!< Width of output data */
#define CORDIC_CSR_ARGSIZE_POS             (23U)
#define CORDIC_CSR_ARGSIZE_MASK            (0x1UL << CORDIC_CSR_ARGSIZE_POS)             /*!< 0x00800000 */
#define CORDIC_CSR_ARGSIZE                 CORDIC_CSR_ARGSIZE_MASK                       /*!< Width of input data */
#define CORDIC_CSR_RRDY_POS                (31U)
#define CORDIC_CSR_RRDY_MASK               (0x1UL << CORDIC_CSR_RRDY_POS)                /*!< 0x80000000 */
#define CORDIC_CSR_RRDY                    CORDIC_CSR_RRDY_MASK                          /*!< Result Ready Flag */

/************************  Bit definition for CORDIC_WDATA register  ********************/
#define CORDIC_WDATA_ARG_POS               (0U)
#define CORDIC_WDATA_ARG_MASK              (0xFFFFFFFFUL << CORDIC_WDATA_ARG_POS)        /*!< 0xFFFFFFFF */
#define CORDIC_WDATA_ARG                   CORDIC_WDATA_ARG_MASK                         /*!< Input Argument */

/************************  Bit definition for CORDIC_RDATA register  ********************/
#define CORDIC_RDATA_RES_POS               (0U)
#define CORDIC_RDATA_RES_MASK              (0xFFFFFFFFUL << CORDIC_RDATA_RES_POS)        /*!< 0xFFFFFFFF */
#define CORDIC_RDATA_RES                   CORDIC_RDATA_RES_MASK                         /*!< Output Result */

/** @defgroup CORDIC_Function CORDIC Function
  * @{
  */
#define CORDIC_FUNCTION_COSINE             (0x00000000U)                                                     /*!< Cosine */
#define CORDIC_FUNCTION_SINE               ((u32)(CORDIC_CSR_FUNC_0))                                        /*!< Sine */
#define CORDIC_FUNCTION_PHASE              ((u32)(CORDIC_CSR_FUNC_1))                                        /*!< Phase */
#define CORDIC_FUNCTION_MODULUS            ((u32)(CORDIC_CSR_FUNC_1 | CORDIC_CSR_FUNC_0))                    /*!< Modulus */
#define CORDIC_FUNCTION_ARCTANGENT         ((u32)(CORDIC_CSR_FUNC_2))                                        /*!< Arctangent */
#define CORDIC_FUNCTION_HCOSINE            ((u32)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_0))                    /*!< Hyperbolic Cosine */
#define CORDIC_FUNCTION_HSINE              ((u32)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_1))                    /*!< Hyperbolic Sine */
#define CORDIC_FUNCTION_HARCTANGENT        ((u32)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_1 | CORDIC_CSR_FUNC_0))/*!< Hyperbolic Arctangent */
#define CORDIC_FUNCTION_NATURALLOG         ((u32)(CORDIC_CSR_FUNC_3))                                        /*!< Natural Logarithm */
#define CORDIC_FUNCTION_SQUAREROOT         ((u32)(CORDIC_CSR_FUNC_3 | CORDIC_CSR_FUNC_0))                    /*!< Square Root */
#define CORDIC_FUNCTION_ROTATIONMATRIX     ((u32)(CORDIC_CSR_FUNC_3 | CORDIC_CSR_FUNC_1))                    /*!< Rotation Matrix */
#define CORDIC_FUNCTION_INTEGERMODULUS     ((u32)(CORDIC_CSR_FUNC_3 | CORDIC_CSR_FUNC_1 | CORDIC_CSR_FUNC_0))/*!< Integer Modulus */
#define CORDIC_FUNCTION_INTEGERSQUAREROOT  ((u32)(CORDIC_CSR_FUNC_3 | CORDIC_CSR_FUNC_2))                    /*!< Integer Square Root */
/**
  * @}
  */

/** @defgroup CORDIC_Precision_In_Cycles_Number CORDIC Precision in Cycles Number
  * @{
  */
/* Note: 1 cycle corresponds to 4 algorithm iterations */
#define CORDIC_PRECISION_1CYCLE            ((u32)(CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_2CYCLES           ((u32)(CORDIC_CSR_PRECISION_1))
#define CORDIC_PRECISION_3CYCLES           ((u32)(CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_4CYCLES           ((u32)(CORDIC_CSR_PRECISION_2))
#define CORDIC_PRECISION_5CYCLES           ((u32)(CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_6CYCLES           ((u32)(CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1))
#define CORDIC_PRECISION_7CYCLES           ((u32)(CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_8CYCLES           ((u32)(CORDIC_CSR_PRECISION_3))
#define CORDIC_PRECISION_9CYCLES           ((u32)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_10CYCLES          ((u32)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_1))
#define CORDIC_PRECISION_11CYCLES          ((u32)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_12CYCLES          ((u32)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_2))
#define CORDIC_PRECISION_13CYCLES          ((u32)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_14CYCLES          ((u32)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1))
#define CORDIC_PRECISION_15CYCLES          ((u32)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1 |CORDIC_CSR_PRECISION_0))
/**
  * @}
  */

/** @defgroup CORDIC_Scale CORDIC Scaling factor
  * @{
  */
/* Scale factor value 'n' implies that the input data have been multiplied
   by a factor 2exp(-n), and/or the output data need to be multiplied by 2exp(n). */
#define CORDIC_SCALE_0                     (0x00000000U)
#define CORDIC_SCALE_1                     ((u32)(CORDIC_CSR_SCALE_0))
#define CORDIC_SCALE_2                     ((u32)(CORDIC_CSR_SCALE_1))
#define CORDIC_SCALE_3                     ((u32)(CORDIC_CSR_SCALE_1 | CORDIC_CSR_SCALE_0))
#define CORDIC_SCALE_4                     ((u32)(CORDIC_CSR_SCALE_2))
#define CORDIC_SCALE_5                     ((u32)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_0))
#define CORDIC_SCALE_6                     ((u32)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_1))
#define CORDIC_SCALE_7                     ((u32)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_1 | CORDIC_CSR_SCALE_0))
/**
  * @}
  */

/** @defgroup CORDIC_Interrupts_Enable CORDIC Interrupts Enable bit
  * @{
  */
#define CORDIC_IT_IEN                      CORDIC_CSR_IEN                   /*!< Result ready interrupt enable */
/**
  * @}
  */

/** @defgroup CORDIC_DMAR DMA Read Request Enable bit
  * @{
  */
#define CORDIC_DMA_REN                     CORDIC_CSR_DMAREN                /*!< DMA Read requests enable */
/**
  * @}
  */

/** @defgroup CORDIC_DMAW DMA Write Request Enable bit
  * @{
  */
#define CORDIC_DMA_WEN                     CORDIC_CSR_DMAWEN                /*!< DMA Write channel enable */
/**
  * @}
  */

/** @defgroup CORDIC_Nb_Write CORDIC Number of 32-bit write required for one calculation
  * @{
  */
#define CORDIC_NBWRITE_1                   (0x00000000U)                    /*!< One 32-bits write containing either only one
                                                                                 32-bit data input (Q1.31 format), or two 16-bit
                                                                                 data input (Q1.15 format) packed in one 32 bits
                                                                                 Data */
#define CORDIC_NBWRITE_2                   ((u32)(CORDIC_CSR_NARGS_0))      /*!< Two 32-bit write containing two 32-bits data input
                                                                                 (Q1.31 format) */
#define CORDIC_NBWRITE_3                   ((u32)(CORDIC_CSR_NARGS_1))      /*!< Three 32-bit write containing three 32-bits data input
                                                                                 (Q1.31 format) */
/**
  * @}
  */

/** @defgroup CORDIC_Nb_Read CORDIC Number of 32-bit read required after one calculation
  * @{
  */
#define CORDIC_NBREAD_1                    (0x00000000U)                    /*!< One 32-bits read containing either only one
                                                                                 32-bit data output (Q1.31 format), or two 16-bit
                                                                                 data output (Q1.15 format) packed in one 32 bits
                                                                                 Data */
#define CORDIC_NBREAD_2                    CORDIC_CSR_NRES                  /*!< Two 32-bit Data containing two 32-bits data output
                                                                                 (Q1.31 format) */
/**
  * @}
  */

/** @defgroup CORDIC_In_Size CORDIC input data size
  * @{
  */
#define CORDIC_INSIZE_32BITS               (0x00000000U)                    /*!< 32 bits input data size (Q1.31 format) */
#define CORDIC_INSIZE_16BITS               CORDIC_CSR_ARGSIZE               /*!< 16 bits input data size (Q1.15 format) */
/**
  * @}
  */

/** @defgroup CORDIC_Out_Size CORDIC Results Size
  * @{
  */
#define CORDIC_OUTSIZE_32BITS              (0x00000000U)                    /*!< 32 bits output data size (Q1.31 format) */
#define CORDIC_OUTSIZE_16BITS              CORDIC_CSR_RESSIZE               /*!< 16 bits output data size (Q1.15 format) */
/**
  * @}
  */

/** @defgroup CORDIC_Flags  CORDIC status flags
  * @{
  */
#define CORDIC_FLAG_RRDY                   CORDIC_CSR_RRDY                  /*!< Result Ready Flag */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup CORDIC_Exported_Functions CORDIC exported functions
  * @{
  */
void CORDIC_DeInit(void);
void CORDIC_Init(CORDIC_InitTypeDef *CORDIC_InitStruct);
void CORDIC_IntCmd(ControlStatus NewState);
void CORDIC_PDMACmd(u32 CORDIC_DMA, ControlStatus NewState);
FlagStatus CORDIC_GetFlagStatus_RRDY(void);
void CORDIC_WriteData(u32 InData);
u32 CORDIC_ReadData(void);

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
