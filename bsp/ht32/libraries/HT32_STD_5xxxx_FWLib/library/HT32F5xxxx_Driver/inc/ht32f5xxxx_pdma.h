/*********************************************************************************************************//**
 * @file    ht32f5xxxx_pdma.h
 * @version $Rev:: 7319         $
 * @date    $Date:: 2023-10-28 #$
 * @brief   The header file of the PDMA library.
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
#ifndef __HT32F5XXXX_PDMA_H
#define __HT32F5XXXX_PDMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup PDMA
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup PDMA_Exported_Types PDMA exported types
  * @{
  */

/**
 * @brief Definition of PDMA channel Init Structure
 */
typedef struct
{
  u32 PDMACH_SrcAddr;         /*!< source address                                                           */
  u32 PDMACH_DstAddr;         /*!< destination address                                                      */
  u16 PDMACH_BlkCnt;          /*!< number of blocks for a PDMA transfer (1 ~ 65,535)                        */
  u8  PDMACH_BlkLen;          /*!< number of data for a block (1 ~ 255)                                     */
  u8  PDMACH_DataSize;        /*!< number of bits for a data (8-bit/16-bit/32-bit)                          */
  u16 PDMACH_Priority;        /*!< software priority for a PDMA transfer (L/M/H/VH)                         */
  u16 PDMACH_AdrMod;          /*!< address mode (LIN_INC/LIN_DEC/CIR_INC/CIR_DEC/FIX/AUTO_RELOAD)           */
} PDMACH_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup PDMA_Exported_Constants PDMA exported constants
  * @{
  */
/* priority                                                                                                 */
#define L_PRIO                    (0)                           /*!< low priority                           */
#define M_PRIO                    (1UL << 8)                    /*!< medium priority                        */
#define H_PRIO                    (2UL << 8)                    /*!< high priority                          */
#define VH_PRIO                   (3UL << 8)                    /*!< very high priority                     */

#define IS_PDMA_PRIO(PRIO)        ((PRIO >> 8) < 4)             /*!< check channel priority parameter       */

/* address mode                                                                                             */
#define AUTO_RELOAD               (1UL << 11)                   /*!< enable auto reload                     */
#define ADR_FIX                   (1UL << 10)                   /*!< enable address fix                     */

#define SRC_ADR_LIN_INC           (0)                           /*!< source address linear increment        */
#define SRC_ADR_LIN_DEC           (1UL << 6)                    /*!< source address linear decrement        */
#define SRC_ADR_CIR_INC           (2UL << 6)                    /*!< source address circular increment      */
#define SRC_ADR_CIR_DEC           (3UL << 6)                    /*!< source address circular decrement      */
#define SRC_ADR_FIX               (ADR_FIX | SRC_ADR_CIR_INC)   /*!< source address fix                     */

#define DST_ADR_LIN_INC           (0)                           /*!< destination address linear increment   */
#define DST_ADR_LIN_DEC           (1UL << 4)                    /*!< destination address linear decrement   */
#define DST_ADR_CIR_INC           (2UL << 4)                    /*!< destination address circular increment */
#define DST_ADR_CIR_DEC           (3UL << 4)                    /*!< destination address circular decrement */
#define DST_ADR_FIX               (ADR_FIX | DST_ADR_CIR_INC)   /*!< destination address fix                */

#define IS_PDMA_ADR_MOD(MOD)      ((MOD & 0xFFFFF30F) == 0)     /*!< check address mode parameters          */

/* transfer size                                                                                            */
#define IS_PDMA_BLK_CNT(CNT)      ((CNT > 0) && (CNT <= 65535))  /*!< block count per transfer               */
#define IS_PDMA_BLK_LEN(LEN)      ((LEN > 0) && (LEN <= 255))    /*!< block size per block count             */

/* transfer width                                                                                           */
#define WIDTH_8BIT                (0)                           /*!< 8-bit transfer width                   */
#define WIDTH_16BIT               (1UL << 2)                    /*!< 16-bit transfer width                  */
#define WIDTH_32BIT               (2UL << 2)                    /*!< 32-bit transfer width                  */

#define IS_PDMA_WIDTH(WIDTH)      ((WIDTH >> 2) < 3)            /*!< check transfer width parameter         */

/* channel number                                                                                           */
#define PDMA_CH0                  (0)                           /*!< channel 0 number                       */
#define PDMA_CH1                  (1UL)                         /*!< channel 1 number                       */
#define PDMA_CH2                  (2UL)                         /*!< channel 2 number                       */
#define PDMA_CH3                  (3UL)                         /*!< channel 3 number                       */
#define PDMA_CH4                  (4UL)                         /*!< channel 4 number                       */
#define PDMA_CH5                  (5UL)                         /*!< channel 5 number                       */

#define IS_PDMA_CH(CH)            (CH < 6)                      /*!< check channel number parameter         */

#define PDMA_ADC0                 PDMA_CH0                      /*!< ADC PDMA channel number                */
#if (LIBCFG_ADC1)
#define PDMA_ADC1                 PDMA_CH1                      /*!< ADC PDMA channel number                */
#endif
#define PDMA_ADC                  PDMA_ADC0

#if(LIBCFG_DAC0)
#define PDMA_DAC0_CH0             PDMA_CH1                      /*!< DAC0 CH0 PDMA channel number           */
#define PDMA_DAC0_CH1             PDMA_CH3                      /*!< DAC0 CH1 PDMA channel number           */
#endif

#if(LIBCFG_DAC1)
#define PDMA_DAC1_CH0             PDMA_CH4                      /*!< DAC1 CH0 PDMA channel number           */
#define PDMA_DAC1_CH1             PDMA_CH5                      /*!< DAC1 CH1 PDMA channel number           */
#endif

#if defined(USE_HT32F65230_40) || defined(USE_HT32F65232) || defined(USE_HT32F0006) || defined(USE_HT32F61244_45)
#define PDMA_SPI0_RX              PDMA_CH4                      /*!< SPI0_RX PDMA channel number            */
#define PDMA_SPI0_TX              PDMA_CH5                      /*!< SPI0_TX PDMA channel number            */
#elif defined(USE_HT32F57342_52) || defined(USE_HT32F52357_67) || defined(USE_HT32F67041_51) || defined(USE_HT32F52234_44)
#define PDMA_SPI0_RX              PDMA_CH2                      /*!< SPI0_RX PDMA channel number            */
#define PDMA_SPI0_TX              PDMA_CH3                      /*!< SPI0_TX PDMA channel number            */
#else
#define PDMA_SPI0_RX              PDMA_CH0                      /*!< SPI0_RX PDMA channel number            */
#define PDMA_SPI0_TX              PDMA_CH1                      /*!< SPI0_TX PDMA channel number            */
#endif

#if (LIBCFG_SPI1)
#define PDMA_SPI1_RX              PDMA_CH4                      /*!< SPI1_RX PDMA channel number            */
#define PDMA_SPI1_TX              PDMA_CH5                      /*!< SPI1_TX PDMA channel number            */
#endif

#if (LIBCFG_QSPI)
#define PDMA_QSPI_TX              PDMA_CH1                      /*!< QSPI_TX PDMA channel number            */
#define PDMA_QSPI_RX              PDMA_CH0                      /*!< QSPI_RX PDMA channel number            */
#endif

#define PDMA_USART0_RX            PDMA_CH0                      /*!< USART0_RX PDMA channel number          */
#define PDMA_USART0_TX            PDMA_CH1                      /*!< USART0_TX PDMA channel number          */
#if (LIBCFG_USART1)
#define PDMA_USART1_RX            PDMA_CH2                      /*!< USART1_RX PDMA channel number          */
#define PDMA_USART1_TX            PDMA_CH3                      /*!< USART1_TX PDMA channel number          */
#endif

#if defined(USE_HT32F52243_53) || defined(USE_HT32F52357_67) || defined(USE_HT32F54243_53)
#define PDMA_UART2_RX             PDMA_CH0                      /*!< UART2_RX PDMA channel number           */
#define PDMA_UART2_TX             PDMA_CH1                      /*!< UART2_TX PDMA channel number           */
#define PDMA_UART3_RX             PDMA_CH4                      /*!< UART3_RX PDMA channel number           */
#define PDMA_UART3_TX             PDMA_CH5                      /*!< UART3_TX PDMA channel number           */
#endif

#define PDMA_UART0_RX             PDMA_CH2                      /*!< UART0_RX PDMA channel number           */
#define PDMA_UART0_TX             PDMA_CH3                      /*!< UART0_TX PDMA channel number           */
#if (LIBCFG_UART1)
#define PDMA_UART1_RX             PDMA_CH4                      /*!< UART1_RX PDMA channel number           */
#define PDMA_UART1_TX             PDMA_CH5                      /*!< UART1_TX PDMA channel number           */
#endif

#if defined(USE_HT32F65230_40) || defined(USE_HT32F65232)
#define PDMA_I2C0_RX              PDMA_CH2                      /*!< I2C0_RX PDMA channel number            */
#define PDMA_I2C0_TX              PDMA_CH3                      /*!< I2C0_TX PDMA channel number            */
#elif defined(USE_HT32F52234_44)
#define PDMA_I2C0_RX              PDMA_CH2                      /*!< I2C0_RX PDMA channel number            */
#define PDMA_I2C0_TX              PDMA_CH0                      /*!< I2C0_TX PDMA channel number            */
#else
#define PDMA_I2C0_RX              PDMA_CH2                      /*!< I2C0_RX PDMA channel number            */
#define PDMA_I2C0_TX              PDMA_CH4                      /*!< I2C0_TX PDMA channel number            */
#endif
#if (LIBCFG_I2C1)
#if defined(USE_HT32F52234_44)
#define PDMA_I2C1_RX              PDMA_CH3                      /*!< I2C1_RX PDMA channel number            */
#define PDMA_I2C1_TX              PDMA_CH1                      /*!< I2C1_TX PDMA channel number            */
#else
#define PDMA_I2C1_RX              PDMA_CH3                      /*!< I2C1_RX PDMA channel number            */
#define PDMA_I2C1_TX              PDMA_CH5                      /*!< I2C1_TX PDMA channel number            */
#endif
#endif

#if defined(USE_HT32F52243_53) || defined(USE_HT32F54243_53)
#define PDMA_I2C2_RX              PDMA_CH0                      /*!< I2C2_RX PDMA channel number            */
#define PDMA_I2C2_TX              PDMA_CH1                      /*!< I2C2_TX PDMA channel number            */
#elif defined(USE_HT32F52234_44)
#define PDMA_I2C2_RX              PDMA_CH4                      /*!< I2C2_RX PDMA channel number            */
#define PDMA_I2C2_TX              PDMA_CH5                      /*!< I2C2_TX PDMA channel number            */
#endif

#if defined(USE_HT32F52342_52) || defined(USE_HT32F5826) || defined(USE_HT32F57342_52) || defined(USE_HT32F52357_67)
#define PDMA_SCI0_TX              PDMA_CH5                      /*!< SCI0_TX PDMA channel number            */
#define PDMA_SCI0_RX              PDMA_CH4                      /*!< SCI0_RX PDMA channel number            */
#define PDMA_SCI1_TX              PDMA_CH3                      /*!< SCI1_TX PDMA channel number            */
#define PDMA_SCI1_RX              PDMA_CH2                      /*!< SCI1_RX PDMA channel number            */
#endif

#if (LIBCFG_I2S)
#define PDMA_I2S_TX               PDMA_CH2                      /*!< I2S_TX PDMA channel number             */
#define PDMA_I2S_RX               PDMA_CH1                      /*!< I2S_RX PDMA channel number             */
#endif

#if (LIBCFG_MCTM0)
#define PDMA_MCTM0_CH0            PDMA_CH0                      /*!< MCTM0_CH0 PDMA channel number          */
#define PDMA_MCTM0_TRIG           PDMA_CH1                      /*!< MCTM0_TRIG PDMA channel number         */
#define PDMA_MCTM0_CH1            PDMA_CH2                      /*!< MCTM0_CH1 PDMA channel number          */
#define PDMA_MCTM0_CH2            PDMA_CH3                      /*!< MCTM0_CH2 PDMA channel number          */
#define PDMA_MCTM0_CH3            PDMA_CH4                      /*!< MCTM0_CH3 PDMA channel number          */
#define PDMA_MCTM0_UEV2           PDMA_CH4                      /*!< MCTM0_UEV2 PDMA channel number         */
#define PDMA_MCTM0_UEV1           PDMA_CH5                      /*!< MCTM0_UEV1 PDMA channel number         */
#endif

#if (LIBCFG_NO_GPTM0)
#else
#if defined(USE_HT32F65230_40) || defined(USE_HT32F65232)
#define PDMA_GPTM0_CH1            PDMA_CH0                      /*!< GPTM0_CH1 PDMA channel number          */
#define PDMA_GPTM0_CH2            PDMA_CH1                      /*!< GPTM0_CH2 PDMA channel number          */
#define PDMA_GPTM0_CH0            PDMA_CH2                      /*!< GPTM0_CH0 PDMA channel number          */
#define PDMA_GPTM0_CH3            PDMA_CH3                      /*!< GPTM0_CH3 PDMA channel number          */
#define PDMA_GPTM0_UEV            PDMA_CH4                      /*!< GPTM0_UEV PDMA channel number          */
#define PDMA_GPTM0_TRIG           PDMA_CH5                      /*!< GPTM0_TRIG PDMA channel number         */
#else
#define PDMA_GPTM0_CH1            PDMA_CH0                      /*!< GPTM0_CH1 PDMA channel number          */
#define PDMA_GPTM0_CH3            PDMA_CH0                      /*!< GPTM0_CH3 PDMA channel number          */
#define PDMA_GPTM0_CH2            PDMA_CH1                      /*!< GPTM0_CH2 PDMA channel number          */
#define PDMA_GPTM0_UEV            PDMA_CH1                      /*!< GPTM0_UEV PDMA channel number          */
#define PDMA_GPTM0_CH0            PDMA_CH2                      /*!< GPTM0_CH0 PDMA channel number          */
#define PDMA_GPTM0_TRIG           PDMA_CH2                      /*!< GPTM0_TRIG PDMA channel number         */
#endif
#endif

#if (LIBCFG_GPTM1)
#define PDMA_GPTM1_CH0            PDMA_CH3                      /*!< GPTM1_CH0 PDMA channel number          */
#define PDMA_GPTM1_CH3            PDMA_CH3                      /*!< GPTM1_CH3 PDMA channel number          */
#define PDMA_GPTM1_CH1            PDMA_CH4                      /*!< GPTM1_CH1 PDMA channel number          */
#define PDMA_GPTM1_UEV            PDMA_CH4                      /*!< GPTM1_UEV PDMA channel number          */
#define PDMA_GPTM1_CH2            PDMA_CH5                      /*!< GPTM1_CH2 PDMA channel number          */
#define PDMA_GPTM1_TRIG           PDMA_CH5                      /*!< GPTM1_TRIG PDMA channel number         */
#endif

#if defined(USE_HT32F65230_40) || defined(USE_HT32F65232)
#define PDMA_SCTM0_CH0            PDMA_CH0                      /*!< SCTM0_CH0 PDMA channel number          */
#define PDMA_SCTM0_CH1            PDMA_CH1                      /*!< SCTM0_CH1 PDMA channel number          */
#define PDMA_SCTM1_CH0            PDMA_CH2                      /*!< SCTM1_CH0 PDMA channel number          */
#define PDMA_SCTM1_CH1            PDMA_CH3                      /*!< SCTM1_CH1 PDMA channel number          */
#define PDMA_SCTM2_CH0            PDMA_CH4                      /*!< SCTM2_CH0 PDMA channel number          */
#define PDMA_SCTM2_CH1            PDMA_CH5                      /*!< SCTM2_CH1 PDMA channel number          */
#define PDMA_SCTM3_CH0            PDMA_CH4                      /*!< SCTM3_CH0 PDMA channel number          */
#define PDMA_SCTM3_CH1            PDMA_CH5                      /*!< SCTM3_CH1 PDMA channel number          */
#endif

#if (LIBCFG_PWM0)
#if defined(USE_HT32F52234_44)
#define PDMA_PWM0_CH0             PDMA_CH5                      /*!< PWM0_CH0 PDMA channel number           */
#define PDMA_PWM0_CH1             PDMA_CH3                      /*!< PWM0_CH1 PDMA channel number           */
#define PDMA_PWM0_CH2             PDMA_CH4                      /*!< PWM0_CH2 PDMA channel number           */
#define PDMA_PWM0_CH3             PDMA_CH3                      /*!< PWM0_CH3 PDMA channel number           */
#define PDMA_PWM0_TRIG            PDMA_CH5                      /*!< PWM0_TRIG PDMA channel number          */
#define PDMA_PWM0_UEV             PDMA_CH4                      /*!< PWM0_UEV PDMA channel number           */
#else
#define PDMA_PWM0_CH0             PDMA_CH2                      /*!< PWM0_CH0 PDMA channel number           */
#define PDMA_PWM0_CH1             PDMA_CH0                      /*!< PWM0_CH1 PDMA channel number           */
#define PDMA_PWM0_CH2             PDMA_CH1                      /*!< PWM0_CH2 PDMA channel number           */
#define PDMA_PWM0_CH3             PDMA_CH0                      /*!< PWM0_CH3 PDMA channel number           */
#define PDMA_PWM0_TRIG            PDMA_CH2                      /*!< PWM0_TRIG PDMA channel number          */
#define PDMA_PWM0_UEV             PDMA_CH1                      /*!< PWM0_UEV PDMA channel number           */
#endif
#endif

#if (LIBCFG_PWM1)
#define PDMA_PWM1_CH0             PDMA_CH5                      /*!< PWM1_CH0 PDMA channel number           */
#define PDMA_PWM1_CH1             PDMA_CH3                      /*!< PWM1_CH1 PDMA channel number           */
#define PDMA_PWM1_CH2             PDMA_CH4                      /*!< PWM1_CH2 PDMA channel number           */
#define PDMA_PWM1_CH3             PDMA_CH3                      /*!< PWM1_CH3 PDMA channel number           */
#define PDMA_PWM1_TRIG            PDMA_CH5                      /*!< PWM1_TRIG PDMA channel number          */
#define PDMA_PWM1_UEV             PDMA_CH4                      /*!< PWM1_UEV PDMA channel number           */
#endif

#if (LIBCFG_PWM2)
#define PDMA_PWM2_CH0             PDMA_CH5                      /*!< PWM2_CH0 PDMA channel number           */
#define PDMA_PWM2_CH1             PDMA_CH3                      /*!< PWM2_CH1 PDMA channel number           */
#define PDMA_PWM2_CH2             PDMA_CH4                      /*!< PWM2_CH2 PDMA channel number           */
#define PDMA_PWM2_CH3             PDMA_CH3                      /*!< PWM2_CH3 PDMA channel number           */
#define PDMA_PWM2_TRIG            PDMA_CH5                      /*!< PWM2_TRIG PDMA channel number          */
#define PDMA_PWM2_UEV             PDMA_CH4                      /*!< PWM2_UEV PDMA channel number           */
#endif

#if (LIBCFG_SLED0)
#define PDMA_SLED0                PDMA_CH0                      /*!< SLED0 PDMA channel number              */
#endif
#if (LIBCFG_SLED1)
#define PDMA_SLED1                PDMA_CH1                      /*!< SLED1 PDMA channel number              */
#endif

#if (LIBCFG_AES)
#define PDMA_AES_OUT              PDMA_CH4                      /*!< AES_OUT PDMA channel number            */
#define PDMA_AES_IN               PDMA_CH5                      /*!< AES_IN PDMA channel number             */
#endif

#if (LIBCFG_MIDI)
#define PDMA_MIDI_IN              PDMA_CH3                      /*!< MIDI_IN PDMA channel number            */
#define PDMA_MIDI_OUT             PDMA_CH4                      /*!< MIDI_OUT PDMA channel number           */
#endif

/* flag                                                                                                     */
#define PDMA_FLAG_GE              (1UL << 0)                    /*!< PDMA channel global event flag         */
#define PDMA_FLAG_BE              (1UL << 1)                    /*!< PDMA channel block end flag            */
#define PDMA_FLAG_HT              (1UL << 2)                    /*!< PDMA channel half transfer flag        */
#define PDMA_FLAG_TC              (1UL << 3)                    /*!< PDMA channel transfer complete flag    */
#define PDMA_FLAG_TE              (1UL << 4)                    /*!< PDMA channel transfer error flag       */

#define IS_PDMA_FLAG(FLAG)        (((FLAG & 0xFFFFFFE0) == 0) && (FLAG != 0))
#define IS_PDMA_CLEAR_FLAG(FLAG)  (((FLAG & 0xFFFFFFE0) == 0) && (FLAG != 0))

/* interrupt                                                                                                */
#define PDMA_INT_GE               (1UL << 0)                  /*!< PDMA channel global event interrupt      */
#define PDMA_INT_BE               (1UL << 1)                  /*!< PDMA channel block end interrupt         */
#define PDMA_INT_HT               (1UL << 2)                  /*!< PDMA channel half transfer interrupt     */
#define PDMA_INT_TC               (1UL << 3)                  /*!< PDMA channel transfer complete interrupt */
#define PDMA_INT_TE               (1UL << 4)                  /*!< PDMA channel transfer error interrupt    */

#define IS_PDMA_INT(INT)          (((INT & 0xFFFFFFE0) == 0) && (INT != 0))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup PDMA_Exported_Functions PDMA exported functions
  * @{
  */
void PDMA_DeInit(void);
void PDMA_Config(u32 PDMA_CHn, PDMACH_InitTypeDef *PDMACH_InitStruct);
void PDMA_AddrConfig(u32 PDMA_CHn, u32 SrcAddr, u32 DstAddr);
void PDMA_SrcAddrConfig(u32 PDMA_CHn, u32 SrcAddr);
void PDMA_DstAddrConfig(u32 PDMA_CHn, u32 DstAddr);
void PDMA_TranSizeConfig(u32 PDMA_CHn, u16 BlkCnt, u16 BlkLen);
void PDMA_EnaCmd(u32 PDMA_CHn, ControlStatus NewState);
void PDMA_SwTrigCmd(u32 PDMA_CHn, ControlStatus NewState);

void PDMA_IntConfig(u32 PDMA_CHn, u32 PDMA_INT_x, ControlStatus NewState);
FlagStatus PDMA_GetFlagStatus(u32 PDMA_CHn, u32 PDMA_FLAG_x);
void PDMA_ClearFlag(u32 PDMA_CHn, u32 PDMA_FLAG_x);
u16 PDMA_GetRemainBlkCnt(u32 PDMA_CHn);
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
