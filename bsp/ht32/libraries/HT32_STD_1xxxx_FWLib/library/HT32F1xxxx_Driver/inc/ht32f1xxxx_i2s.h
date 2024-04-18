/*********************************************************************************************************//**
 * @file    ht32f1xxxx_i2s.h
 * @version $Rev:: 1364         $
 * @date    $Date:: 2018-08-02 #$
 * @brief   The header file of the I2S library.
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
#ifndef __HT32F1XXXX_I2S_H
#define __HT32F1XXXX_I2S_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup I2S
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup I2S_Exported_Types I2S exported types
  * @{
  */
typedef struct
{
  u32 I2S_Mode;
  u32 I2S_Format;
  u32 I2S_WordWidth;
  u32 I2S_MclkOut;
  u32 I2S_MclkInv;
  u32 I2S_BclkInv;
  u32 I2S_X_Div;
  u32 I2S_Y_Div;
  u32 I2S_N_Div;
} I2S_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup I2S_Exported_Constants I2S exported constants
  * @{
  */
/* mode                                                                                                     */
#define I2S_MASTER_TX                             (1UL << 1)
#define I2S_MASTER_RX                             (1UL << 2)
#define I2S_MASTER_TX_RX                          ((1UL << 1) | (1UL << 2))

#define I2S_SLAVE_TX                              ((1UL << 3) | (1UL << 1))
#define I2S_SLAVE_RX                              ((1UL << 3) | (1UL << 2))
#define I2S_SLAVE_TX_RX                           ((1UL << 3) | (1UL << 1) | (1UL << 2))

#define IS_I2S_MODE(MOD)                          ((MOD == I2S_MASTER_TX) || \
                                                   (MOD == I2S_MASTER_RX) || \
                                                   (MOD == I2S_MASTER_TX_RX) || \
                                                   (MOD == I2S_SLAVE_TX) || \
                                                   (MOD == I2S_SLAVE_RX) || \
                                                   (MOD == I2S_SLAVE_TX_RX))


/* format                                                                                                   */
#define I2S_JUSTIFIED_STEREO                      (0)
#define LEFT_JUSTIFIED_STEREO                     (1UL << 6)
#define RIGHT_JUSTIFIED_STEREO                    (2UL << 6)
#define I2S_JUSTIFIED_REPEAT                      (1UL << 10)

#define I2S_JUSTIFIED_STEREO_EXT                  (1UL << 8)
#define LEFT_JUSTIFIED_STEREO_EXT                 ((1UL << 8) | (1UL << 6))
#define RIGHT_JUSTIFIED_STEREO_EXT                ((1UL << 8) | (2UL << 6))
#define I2S_JUSTIFIED_REPEAT_EXT                  ((1UL << 8) | (1UL << 10))

#define I2S_JUSTIFIED_MONO                        (1UL << 11)
#define LEFT_JUSTIFIED_MONO                       ((1UL << 11) | (1UL << 6))
#define RIGHT_JUSTIFIED_MONO                      ((1UL << 11) | (2UL << 6))

#define I2S_JUSTIFIED_MONO_EXT                    ((1UL << 8) | (1UL << 11))
#define LEFT_JUSTIFIED_MONO_EXT                   ((1UL << 8) | (1UL << 11) | (1UL << 6))
#define RIGHT_JUSTIFIED_MONO_EXT                  ((1UL << 8) | (1UL << 11) | (2UL << 6))

#define IS_I2S_FORMAT(FMT)                        ((FMT == I2S_JUSTIFIED_STEREO) || \
                                                   (FMT == LEFT_JUSTIFIED_STEREO) || \
                                                   (FMT == RIGHT_JUSTIFIED_STEREO) || \
                                                   (FMT == I2S_JUSTIFIED_REPEAT) || \
                                                   (FMT == I2S_JUSTIFIED_STEREO_EXT) || \
                                                   (FMT == LEFT_JUSTIFIED_STEREO_EXT) || \
                                                   (FMT == RIGHT_JUSTIFIED_STEREO_EXT) || \
                                                   (FMT == I2S_JUSTIFIED_REPEAT_EXT) || \
                                                   (FMT == I2S_JUSTIFIED_MONO) || \
                                                   (FMT == LEFT_JUSTIFIED_MONO) || \
                                                   (FMT == RIGHT_JUSTIFIED_MONO) || \
                                                   (FMT == I2S_JUSTIFIED_MONO_EXT) || \
                                                   (FMT == LEFT_JUSTIFIED_MONO_EXT) || \
                                                   (FMT == RIGHT_JUSTIFIED_MONO_EXT))


/* word width                                                                                               */
#define I2S_WORDWIDTH_8                           (0)
#define I2S_WORDWIDTH_16                          (1UL << 4)
#define I2S_WORDWIDTH_24                          (2UL << 4)
#define I2S_WORDWIDTH_32                          (3UL << 4)

#define IS_I2S_WORD_WIDTH(WIDTH)                  ((WIDTH == I2S_WORDWIDTH_8) || \
                                                   (WIDTH == I2S_WORDWIDTH_16) || \
                                                   (WIDTH == I2S_WORDWIDTH_24) || \
                                                   (WIDTH == I2S_WORDWIDTH_32))


/* clock divider                                                                                            */
#define IS_I2S_MCLK_DIV(X, Y)                     ((X > 0) && (X < 256) && (Y > 0) && (Y < 256) && (X <= Y))

#define IS_I2S_BCLK_DIV(N)                        (N < 256)


/* FIFO                                                                                                     */
#define I2S_TX_FIFO                               (1UL << 8)
#define I2S_RX_FIFO                               (2UL << 8)

#define IS_I2S_ONE_FIFO(FIFO)                     ((FIFO == I2S_TX_FIFO) || (FIFO == I2S_RX_FIFO))

#define IS_I2S_TWO_FIFO(FIFO)                     (((FIFO & 0xFFFFFCFF) == 0) && (FIFO != 0))

#define IS_I2S_FIFO_LEVEL(LEVEL)                  ((LEVEL & 0x0000000F) < 9)


/* interrupt                                                                                                */
#define I2S_INT_TXFIFO_TRI                        (1UL)
#define I2S_INT_TXFIFO_UDF                        (1UL << 1)
#define I2S_INT_TXFIFO_OVF                        (1UL << 2)

#define I2S_INT_RXFIFO_TRI                        (1UL << 4)
#define I2S_INT_RXFIFO_UDF                        (1UL << 5)
#define I2S_INT_RXFIFO_OVF                        (1UL << 6)

#define IS_I2S_INT(INT)                           (((INT & 0xFFFFFF88) == 0) && (INT != 0))


/* flag                                                                                                     */
#define I2S_FLAG_TXFIFO_TRI                       (1UL)
#define I2S_FLAG_TXFIFO_UDF                       (1UL << 1)
#define I2S_FLAG_TXFIFO_OVF                       (1UL << 2)
#define I2S_FLAG_RXFIFO_TRI                       (1UL << 8)
#define I2S_FLAG_RXFIFO_UDF                       (1UL << 9)
#define I2S_FLAG_RXFIFO_OVF                       (1UL << 10)

#define I2S_FLAG_TXFIFO_EMP                       (1UL << 3)
#define I2S_FLAG_TXFIFO_FUL                       (1UL << 4)
#define I2S_FLAG_RXFIFO_EMP                       (1UL << 11)
#define I2S_FLAG_RXFIFO_FUL                       (1UL << 12)
#define I2S_FLAG_RIGHT_CH                         (1UL << 16)
#define I2S_FLAG_TX_BUSY                          (1UL << 17)
#define I2S_FLAG_CLK_RDY                          (1UL << 18)

#define IS_I2S_FLAG_CLEAR(FLAG)                   (((FLAG & 0xFFFFF8F8) == 0) && (FLAG != 0))

#define IS_I2S_FLAG(FLAG)                         ((FLAG == I2S_FLAG_TXFIFO_TRI) || \
                                                   (FLAG == I2S_FLAG_TXFIFO_UDF) || \
                                                   (FLAG == I2S_FLAG_TXFIFO_OVF) || \
                                                   (FLAG == I2S_FLAG_TXFIFO_EMP) || \
                                                   (FLAG == I2S_FLAG_TXFIFO_FUL) || \
                                                   (FLAG == I2S_FLAG_RXFIFO_TRI) || \
                                                   (FLAG == I2S_FLAG_RXFIFO_UDF) || \
                                                   (FLAG == I2S_FLAG_RXFIFO_OVF) || \
                                                   (FLAG == I2S_FLAG_RXFIFO_EMP) || \
                                                   (FLAG == I2S_FLAG_RXFIFO_FUL) || \
                                                   (FLAG == I2S_FLAG_RIGHT_CH) || \
                                                   (FLAG == I2S_FLAG_TX_BUSY) || \
                                                   (FLAG == I2S_FLAG_CLK_RDY))


/* PDMA request                                                                                             */
#define I2S_PDMAREQ_TX                            (1UL << 13)
#define I2S_PDMAREQ_RX                            (1UL << 14)

#define IS_I2S_PDMA_REQ(REQ)                      (((REQ & 0xFFFF9FFF) == 0) && (REQ != 0))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup I2S_Exported_Functions I2S exported functions
  * @{
  */
void I2S_DeInit(void);
void I2S_Init(I2S_InitTypeDef* I2S_InitStruct);
void I2S_Cmd(ControlStatus NewState);
void I2S_MclkOutputCmd(ControlStatus NewState);
void I2S_TxMuteCmd(ControlStatus NewState);
void I2S_PDMACmd(u32 I2S_PDMAREQ, ControlStatus NewState);
void I2S_FIFOReset(u32 I2S_FIFO);
void I2S_FIFOTrigLevelConfig(u32 I2S_FIFO, u32 I2S_FIFOLevel);
u8 I2S_GetFIFOStatus(u32 I2S_FIFO);
void I2S_IntConfig(u32 I2S_Int, ControlStatus NewState);
FlagStatus I2S_GetFlagStatus(u32 I2S_Flag);
void I2S_ClearFlag(u32 I2S_Flag);
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
