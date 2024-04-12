/*********************************************************************************************************//**
 * @file    ht32f5xxxx_tm.h
 * @version $Rev:: 7319         $
 * @date    $Date:: 2023-10-28 #$
 * @brief   The header file of the TM library.
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
#ifndef __HT32F5XXXX_TM_H
#define __HT32F5XXXX_TM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup TM
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup TM_Exported_Types TM exported types
  * @{
  */
/**
 * @brief Enumeration of TM counter mode.
 */
typedef enum
{
  TM_CNT_MODE_UP   = 0x00000000,  /*!< Edge up-counting mode                                                */
  TM_CNT_MODE_CA1  = 0x00010000,  /*!< Center-align mode 1                                                  */
  TM_CNT_MODE_CA2  = 0x00020000,  /*!< Center-align mode 2                                                  */
  TM_CNT_MODE_CA3  = 0x00030000,  /*!< Center-align mode 3                                                  */
  TM_CNT_MODE_DOWN = 0x01000000   /*!< Edge down-counting mode                                              */
} TM_CNT_MODE_Enum;
/**
 * @brief Enumeration of  TM prescaler reload time.
 */
typedef enum
{
  TM_PSC_RLD_UPDATE    = 0x0000,  /*!< Reload prescaler at next update event                                */
  TM_PSC_RLD_IMMEDIATE = 0x0100   /*!< Reload prescaler immediately                                         */
} TM_PSC_RLD_Enum;
/**
 * @brief Enumeration of TM channel output mode.
 */
typedef enum
{
  TM_OM_MATCH_NOCHANGE  = 0x0000, /*!< TM channel output no change on match                                 */
  TM_OM_MATCH_INACTIVE  = 0x0001, /*!< TM channel output inactive level on match                            */
  TM_OM_MATCH_ACTIVE    = 0x0002, /*!< TM channel output active level on match                              */
  TM_OM_MATCH_TOGGLE    = 0x0003, /*!< TM channel output toggle on match                                    */
  TM_OM_FORCED_INACTIVE = 0x0004, /*!< TM channel output forced inactive level                              */
  TM_OM_FORCED_ACTIVE   = 0x0005, /*!< TM channel output forced active level                                */
  TM_OM_PWM1            = 0x0006, /*!< TM channel pwm1 output mode                                          */
  TM_OM_PWM2            = 0x0007, /*!< TM channel pwm2 output mode                                          */
  TM_OM_ASYMMETRIC_PWM1 = 0x0106, /*!< TM channel asymmetric pwm1 output mode                               */
  TM_OM_ASYMMETRIC_PWM2 = 0x0107  /*!< TM channel asymmetric pwm2 output mode                               */
} TM_OM_Enum;
/**
 * @brief Enumeration of TM channel capture source selection.
 */
typedef enum
{
  TM_CHCCS_DIRECT   = 0x00010000,  /*!< TM channel capture selection direct input                           */
  TM_CHCCS_INDIRECT = 0x00020000,  /*!< TM channel capture selection indirect input                         */
  TM_CHCCS_TRCED    = 0x00030000   /*!< TM channel capture selection TRCED of trigger control block         */
} TM_CHCCS_Enum;
/**
 * @brief Enumeration of TM channel capture prescaler.
 */
typedef enum
{
  TM_CHPSC_OFF = 0x00000000,     /*!< TM channel capture no prescaler, capture is done each event           */
  TM_CHPSC_2   = 0x00040000,     /*!< TM channel capture is done once every 2 event                         */
  TM_CHPSC_4   = 0x00080000,     /*!< TM channel capture is done once every 4 event                         */
  TM_CHPSC_8   = 0x000C0000      /*!< TM channel capture is done once every 8 event                         */
} TM_CHPSC_Enum;
#if (LIBCFG_TM_652XX_V1)
/**
 * @brief Enumeration of TM channel Filter (Fsampling) Clock Divider.
 */
typedef enum
{
  TM_CHFDIV_1   = 0x00000000,     /*!< TM channel Filter Fsampling = Fdts                                   */
  TM_CHFDIV_2   = 0x00000001,     /*!< TM channel Filter Fsampling = Fdts/2                                 */
  TM_CHFDIV_4   = 0x00000002,     /*!< TM channel Filter Fsampling = Fdts/4                                 */
  TM_CHFDIV_8   = 0x00000003,     /*!< TM channel Filter Fsampling = Fdts/8                                 */
  TM_CHFDIV_16  = 0x00000004,     /*!< TM channel Filter Fsampling = Fdts/16                                */
  TM_CHFDIV_32  = 0x00000005,     /*!< TM channel Filter Fsampling = Fdts/32                                */
  TM_CHFDIV_64  = 0x00000006      /*!< TM channel Filter Fsampling = Fdts/64                                */
} TM_CHFDIV_Enum;
/**
 * @brief Enumeration of TM channel Filter N-event counter
 */
#if (LIBCFG_TM_TIFN_5BIT)
typedef enum
{
  TM_CHFEV_OFF = 0,               /*!< TM channel Filter off                                                */
  TM_CHFEV_1,                     /*!< TM channel Filter n event counter Setting                            */
  TM_CHFEV_2,
  TM_CHFEV_3,
  TM_CHFEV_4,
  TM_CHFEV_5,
  TM_CHFEV_6,
  TM_CHFEV_7,
  TM_CHFEV_8,
  TM_CHFEV_9,
  TM_CHFEV_10,
  TM_CHFEV_11,
  TM_CHFEV_12,
  TM_CHFEV_13,
  TM_CHFEV_14,
  TM_CHFEV_15,
  TM_CHFEV_16,
  TM_CHFEV_17,
  TM_CHFEV_18,
  TM_CHFEV_19,
  TM_CHFEV_20,
  TM_CHFEV_21,
  TM_CHFEV_22,
  TM_CHFEV_23,
  TM_CHFEV_24,
  TM_CHFEV_25,
  TM_CHFEV_26,
  TM_CHFEV_27,
  TM_CHFEV_28,
  TM_CHFEV_29,
  TM_CHFEV_30,
  TM_CHFEV_31,
} TM_CHFEV_Enum;
#else
typedef enum
{
  TM_CHFEV_OFF = 0x00000000,     /*!< TM channel Filter off                                                 */
  TM_CHFEV_2   = 0x00000001,     /*!< TM channel Filter 2 event counter Setting                             */
  TM_CHFEV_4   = 0x00000002,     /*!< TM channel Filter 4 event counter Setting                             */
  TM_CHFEV_8   = 0x00000003,     /*!< TM channel Filter 8 event counter Setting                             */
  TM_CHFEV_12  = 0x00000004,     /*!< TM channel Filter 12 event counter Setting                            */
  TM_CHFEV_16  = 0x00000005      /*!< TM channel Filter 16 event counter Setting                            */
} TM_CHFEV_Enum;
#endif
#endif
/**
 * @brief Enumeration of TM fDTS clock divider.
 */
typedef enum
{
  TM_CKDIV_OFF = 0x0000,          /*!< fDTS = fCLKIN                                                        */
  TM_CKDIV_2   = 0x0100,          /*!< fDTS = fCLKIN / 2                                                    */
  TM_CKDIV_4   = 0x0200,          /*!< fDTS = fCLKIN / 4                                                    */
  #if (LIBCFG_TM_652XX_V1 || LIBCFG_TM_CKDIV_8)
  TM_CKDIV_8   = 0x0300,          /*!< fDTS = fCLKIN / 8                                                    */
  #endif
} TM_CKDIV_Enum;
#if 0
/**
 * @brief Enumeration of TM ETI input prescaler.
 */
typedef enum
{
  TM_ETIPSC_OFF = 0x00000000,     /*!< ETI prescaler off                                                    */
  TM_ETIPSC_2   = 0x00001000,     /*!< ETIP frequency divided by 2                                          */
  TM_ETIPSC_4   = 0x00002000,     /*!< ETIP frequency divided by 4                                          */
  TM_ETIPSC_8   = 0x00003000      /*!< ETIP frequency divided by 8                                          */
} TM_ETIPSC_Enum;
/**
 * @brief Enumeration of TM ETI input polarity.
 */
typedef enum
{
  TM_ETIPOL_NONINVERTED = 0x00000000, /*!< TM ETI polarity is active high or rising edge                    */
  TM_ETIPOL_INVERTED    = 0x00010000  /*!< TM ETI polarity is active low or falling edge                    */
} TM_ETIPOL_Enum;
#endif
/**
 * @brief Enumeration of TM slave trigger input selection.
 */
typedef enum
{
  TM_TRSEL_UEVG   = 0x0,         /*!< Software trigger by setting UEVG bit                                  */
  TM_TRSEL_TI0S0  = 0x1,         /*!< Filtered channel 0 input                                              */
  TM_TRSEL_TI1S1  = 0x2,         /*!< Filtered channel 1 input                                              */
  TM_TRSEL_ETIF   = 0x3,         /*!< External Trigger input                                                */
  TM_TRSEL_TI0BED = 0x8,         /*!< Trigger input 0 both edge detector                                    */
#if (LIBCFG_TM_NO_ITI == 1)
  #define IS_TRSEL_ITI0(x)   (0)
  #define IS_TRSEL_ITI1(x)   (0)
  #define IS_TRSEL_ITI2(x)   (0)
#else
  TM_TRSEL_ITI0   = 0x9,         /*!< Internal trigger input 0                                              */
  TM_TRSEL_ITI1   = 0xA,         /*!< Internal trigger input 1                                              */
  TM_TRSEL_ITI2   = 0xB          /*!< Internal trigger input 2                                              */
  #define IS_TRSEL_ITI0(x)   (x == TM_TRSEL_ITI0)
  #define IS_TRSEL_ITI1(x)   (x == TM_TRSEL_ITI1)
  #define IS_TRSEL_ITI2(x)   (x == TM_TRSEL_ITI2)
#endif
} TM_TRSEL_Enum;
/**
 * @brief Enumeration of TM slave mode selection.
 */
typedef enum
{
  TM_SMSEL_DISABLE  = 0x0000,     /*!< The prescaler is clocked directly by the internal clock              */
  TM_SMSEL_DECODER1 = 0x0100,     /*!< Counter counts up/down on CH0 edge depending on CH1 level            */
  TM_SMSEL_DECODER2 = 0x0200,     /*!< Counter counts up/down on CH1 edge depending on CH0 level            */
  TM_SMSEL_DECODER3 = 0x0300,     /*!< Counter counts up/down on both CH0 & CH1 edges depending on the
                                       level of the other input */
  TM_SMSEL_RESTART  = 0x0400,     /*!< Slave restart mode                                                   */
  TM_SMSEL_PAUSE    = 0x0500,     /*!< Slave pause mode                                                     */
  TM_SMSEL_TRIGGER  = 0x0600,     /*!< Slave trigger mode                                                   */
  TM_SMSEL_STIED    = 0x0700,     /*!< Rising edge of the selected trigger(STI) clock the counter           */
  #if (LIBCFG_TM_652XX_V1)
  TM_SMSEL_DECODER4 = 0x0800,     /*!< Pluse/Direction mode(Counter counts on Ch0, Count up/down on Ch1     */
  #endif
} TM_SMSEL_Enum;
/**
 * @brief  Enumeration of TM master mode selection.
 */
typedef enum
{
  TM_MMSEL_RESET   = 0x00000000,  /*!< Send trigger signal when S/W setting UEVG or slave restart           */
  TM_MMSEL_ENABLE  = 0x00010000,  /*!< The counter enable signal is used as trigger output.                 */
  TM_MMSEL_UPDATE  = 0x00020000,  /*!< The update event is used as trigger output.                          */
  TM_MMSEL_CH0CC   = 0x00030000,  /*!< Channel 0 capture or compare match occurred as trigger output.       */
  TM_MMSEL_CH0OREF = 0x00040000,  /*!< The CH0OREF signal is used as trigger output.                        */
  TM_MMSEL_CH1OREF = 0x00050000,  /*!< The CH1OREF signal is used as trigger output.                        */
  TM_MMSEL_CH2OREF = 0x00060000,  /*!< The CH2OREF signal is used as trigger output.                        */
  TM_MMSEL_CH3OREF = 0x00070000,  /*!< The CH3OREF signal is used as trigger output.                        */
  #if (LIBCFG_TM_652XX_V1)
  TM_MMSEL_VCLK    = 0x000C0000   /*!< The VCLK signal is used as trigger output.                           */
  #endif
  #if (LIBCFG_PWM_8_CHANNEL)
  TM_MMSEL_CH4OREF = 0x00080000,   /*!< The CH4OREF signal is used as trigger output.                       */
  TM_MMSEL_CH5OREF = 0x00090000,   /*!< The CH5OREF signal is used as trigger output.                       */
  TM_MMSEL_CH6OREF = 0x000A0000,   /*!< The CH6OREF signal is used as trigger output.                       */
  TM_MMSEL_CH7OREF = 0x000B0000    /*!< The CH7OREF signal is used as trigger output.                       */
  #endif
} TM_MMSEL_Enum;
#if (LIBCFG_PDMA)
/**
 * @brief Enumeration of TM channel Capture / Compare PDMA selection.
 */
typedef enum
{
  TM_CHCCDS_CHCCEV = 0,       /*!< Send CHx PDMA request when channel capture/compare event occurs          */
  TM_CHCCDS_UEV               /*!< Send CHx PDMA request when update event occurs                           */
} TM_CHCCDS_Enum;
#endif
/**
 * @brief Definition of TM timebase init structure.
 */
typedef struct
{
  u16              CounterReload;         /*!< Period (Value for CRR register)                              */
#if(LIBCFG_TM_PRESCALER_8BIT)
  u8               Prescaler;             /*!< Prescaler (Value for PSCR register)                          */
#else
  u16              Prescaler;             /*!< Prescaler (Value for PSCR register)                          */
#endif
  u8               RepetitionCounter;     /*!< Repetition counter                                           */
  TM_CNT_MODE_Enum CounterMode;           /*!< Counter mode refer to \ref TM_CNT_MODE_Enum                  */
  TM_PSC_RLD_Enum  PSCReloadTime;         /*!< Prescaler reload mode refer to \ref TM_PSC_RLD_Enum          */
} TM_TimeBaseInitTypeDef;
/**
 * @brief Definition of TM channel output init structure.
 */
typedef struct
{
  TM_CH_Enum      Channel;              /*!< Channel selection refer to \ref TM_CH_Enum                     */
  TM_OM_Enum      OutputMode;           /*!< Channel output mode selection refer to \ref TM_OM_Enum         */
  TM_CHCTL_Enum   Control;              /*!< CHxO output state refer to \ref TM_CHCTL_Enum                  */
  TM_CHCTL_Enum   ControlN;             /*!< CHxO output state refer to \ref TM_CHCTL_Enum                  */
  TM_CHP_Enum     Polarity;             /*!< CHxO polarity refer to \ref TM_CHP_Enum                        */
  TM_CHP_Enum     PolarityN;            /*!< CHxO polarity refer to \ref TM_CHP_Enum                        */
  MCTM_OIS_Enum   IdleState;            /*!< CHxO polarity refer to \ref TM_CHP_Enum                        */
  MCTM_OIS_Enum   IdleStateN;           /*!< CHxO polarity refer to \ref TM_CHP_Enum                        */
  u16             Compare;              /*!< Value for CHxCCR register                                      */
  u16             AsymmetricCompare;    /*!< Value for CHxACR register                                      */
} TM_OutputInitTypeDef;
/**
 * @brief Definition of TM channel input init structure.
 */
typedef struct
{
  TM_CH_Enum    Channel;         /*!< Channel selection refer to \ref TM_CH_Enum                            */
  TM_CHP_Enum   Polarity;        /*!< Channel input polarity refer to \ref TM_CHP_Enum                      */
  TM_CHCCS_Enum Selection;       /*!< Channel capture source selection refer to \ref TM_CHCCS_Enum          */
  TM_CHPSC_Enum Prescaler;       /*!< Channel Capture prescaler refer to \ref TM_CHPSC_Enum                 */
  #if (LIBCFG_TM_652XX_V1)
  TM_CHFDIV_Enum  Fsampling;     /*!< Digital filter Fsampling Frequency, it must fDTS/1 ~ fDTS/64          */
  #if (LIBCFG_TM_TIFN_5BIT)
  u8              Event;         /*!< Digital filter N-event counter Setting, it must be 0 ~ 31             */
  #else
  TM_CHFEV_Enum   Event;         /*!< Digital filter N-event counter Setting, it must be 0, 2, 4, 8, 12, 16 */
  #endif
  #else
  u8            Filter;          /*!< Digital filter Configuration, it must between 0x0 ~ 0xF.              */
  #endif
} TM_CaptureInitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup TM_Exported_Constants TM exported constants
  * @{
  */

/** @defgroup TM_INT Definitions of TM_INT
  * @{
  */
#define TM_INT_CH0CC        0x0001  /*!< Channel 0 capture/compare interrupt                                */
#define TM_INT_CH1CC        0x0002  /*!< Channel 1 capture/compare interrupt                                */
#define TM_INT_CH2CC        0x0004  /*!< Channel 2 capture/compare interrupt                                */
#define TM_INT_CH3CC        0x0008  /*!< Channel 3 capture/compare interrupt                                */
#if (LIBCFG_PWM_8_CHANNEL)
#define TM_INT_CH4CC        0x10000000ul      /*!< Channel 4 compare interrupt                              */
#define TM_INT_CH5CC        0x20000000ul      /*!< Channel 5 compare interrupt                              */
#define TM_INT_CH6CC        0x40000000ul      /*!< Channel 6 compare interrupt                              */
#define TM_INT_CH7CC        0x80000000ul      /*!< Channel 7 compare interrupt                              */
#endif
#define TM_INT_UEV          0x0100  /*!< Update interrupt                                                   */
#define TM_INT_UEV2         0x0200  /*!< Update interrupt 2                                                 */
#define TM_INT_TEV          0x0400  /*!< Trigger interrupt                                                  */
#define TM_INT_BRKEV        0x0800  /*!< Break interrupt                                                    */

#if (LIBCFG_TM_652XX_V1)
#define MCTM_INT_CH0CD      0x100000  /*!< Channel 0 Count-Down compare interrupt                           */
#define MCTM_INT_CH1CD      0x200000  /*!< Channel 1 Count-Down compare interrupt                           */
#define MCTM_INT_CH2CD      0x400000  /*!< Channel 2 Count-Down compare interrupt                           */
#define MCTM_INT_CH3CD      0x800000  /*!< Channel 3 Count-Down compare interrupt                           */

#define TM_INT_VC           0x1000  /*!< Quadrature Decoder VCLK interrupt                                  */
#define TM_INT_QC           0x2000  /*!< Quadrature Decoder CLKPULSE interrupt                              */
#define TM_INT_PE           0x4000  /*!< Quadrature Decoder Phase Error interrupt                           */
#define TM_INT_DC           0x8000  /*!< Quadrature Decoder Direction Change interrupt                      */

#define MCTM_INT_OVER       0x2000  /*!< Counter overflow interrupt                                         */
#define MCTM_INT_UNDER      0x4000  /*!< Counter underflow Interrupt                                        */
#if (LIBCFG_TM_65232)
#define MCTM_INT_RECCDIF    0x8000  /*!< CCIF or CDIF Interrupt flag control by REPR                        */
#endif

#endif
/**
  * @}
  */

#if (LIBCFG_PDMA)
/** @defgroup TM_PDMA Definitions of TM_PDMA
  * @{
  */
#define TM_PDMA_CH0CC        0x00010000  /*!< Channel 0 capture/compare PDMA request                        */
#define TM_PDMA_CH1CC        0x00020000  /*!< Channel 1 capture/compare PDMA request                        */
#define TM_PDMA_CH2CC        0x00040000  /*!< Channel 2 capture/compare PDMA request                        */
#define TM_PDMA_CH3CC        0x00080000  /*!< Channel 3 capture/compare PDMA request                        */
#define TM_PDMA_UEV          0x01000000  /*!< Update PDMA request                                           */
#define TM_PDMA_UEV2         0x02000000  /*!< Update 2 PDMA request                                         */
#define TM_PDMA_TEV          0x04000000  /*!< Trigger PDMA request                                          */
/**
  * @}
  */
#endif

/** @defgroup TM_EVENT Definitions of TM_EVENT
  * @{
  */
#define TM_EVENT_CH0CC      0x0001  /*!< Channel 0 capture/compare event                                    */
#define TM_EVENT_CH1CC      0x0002  /*!< Channel 1 capture/compare event                                    */
#define TM_EVENT_CH2CC      0x0004  /*!< Channel 2 capture/compare event                                    */
#define TM_EVENT_CH3CC      0x0008  /*!< Channel 3 capture/compare event                                    */
#if (LIBCFG_PWM_8_CHANNEL)
#define TM_EVENT_CH4CC      0x10000000ul  /*!< Channel 4 compare event                                      */
#define TM_EVENT_CH5CC      0x20000000ul  /*!< Channel 5 compare event                                      */
#define TM_EVENT_CH6CC      0x40000000ul  /*!< Channel 6 compare event                                      */
#define TM_EVENT_CH7CC      0x80000000ul  /*!< Channel 7 compare event                                      */
#endif
#define TM_EVENT_UEV        0x0100  /*!< Update event                                                       */
#define TM_EVENT_UEV2       0x0200  /*!< Update event 2                                                     */
#define TM_EVENT_TEV        0x0400  /*!< Trigger event                                                      */
#define TM_EVENT_BRKEV      0x0800  /*!< Break event                                                        */
/**
  * @}
  */

/** @defgroup TM_FLAG Definitions of TM_FLAG
  * @{
  */
#define TM_FLAG_CH0CC       0x0001  /*!< Channel 0 capture/compare flag                                     */
#define TM_FLAG_CH1CC       0x0002  /*!< Channel 1 capture/compare flag                                     */
#define TM_FLAG_CH2CC       0x0004  /*!< Channel 2 capture/compare flag                                     */
#define TM_FLAG_CH3CC       0x0008  /*!< Channel 3 capture/compare flag                                     */
#if (LIBCFG_PWM_8_CHANNEL)
#define TM_FLAG_CH4CC       0x10000000ul  /*!< Channel 4 compare flag                                       */
#define TM_FLAG_CH5CC       0x20000000ul  /*!< Channel 5 compare flag                                       */
#define TM_FLAG_CH6CC       0x40000000ul  /*!< Channel 6 compare flag                                       */
#define TM_FLAG_CH7CC       0x80000000ul  /*!< Channel 7 compare flag                                       */
#endif
#define TM_FLAG_CH0OC       0x0010  /*!< Channel 0 over capture flag                                        */
#define TM_FLAG_CH1OC       0x0020  /*!< Channel 1 over capture flag                                        */
#define TM_FLAG_CH2OC       0x0040  /*!< Channel 2 over capture flag                                        */
#define TM_FLAG_CH3OC       0x0080  /*!< Channel 3 over capture flag                                        */
#define TM_FLAG_UEV         0x0100  /*!< Update flag                                                        */
#define TM_FLAG_UEV2        0x0200  /*!< Update 2 flag                                                      */
#define TM_FLAG_TEV         0x0400  /*!< Trigger flag                                                       */
#define TM_FLAG_BRK0        0x0800  /*!< Break 0 flag                                                       */
#define TM_FLAG_BRK1        0x1000  /*!< Break 1 flag                                                       */
/**
  * @}
  */

/** @defgroup TM_Check_Parameter Check parameter
  * @{
  */

/**
 * @brief Used to check parameter of the TMx.
 */
#define IS_TM(x)            (IS_GPTM0(x) || IS_GPTM1(x) || IS_MCTM0(x) || IS_PWM0(x) || IS_PWM1(x) || IS_PWM2(x) || IS_SCTM(x))
#if (!LIBCFG_NO_GPTM0)
#define IS_GPTM0(x)         (x == HT_GPTM0)
#else
#define IS_GPTM0(x)         (0)
#endif

#if (LIBCFG_GPTM1)
#define IS_GPTM1(x)         (x == HT_GPTM1)
#else
#define IS_GPTM1(x)         (0)
#endif

#if (LIBCFG_MCTM0)
#define IS_MCTM0(x)         (x == HT_MCTM0)
#else
#define IS_MCTM0(x)         (0)
#endif

#if (LIBCFG_PWM0)
#define IS_PWM0(x)          (x == HT_PWM0)
#else
#define IS_PWM0(x)          (0)
#endif

#if (LIBCFG_PWM1)
#define IS_PWM1(x)          (x == HT_PWM1)
#else
#define IS_PWM1(x)          (0)
#endif

#if (LIBCFG_PWM2)
#define IS_PWM2(x)          (x == HT_PWM2)
#else
#define IS_PWM2(x)          (0)
#endif

#define IS_SCTM(x)          (IS_SCTM0(x) || IS_SCTM1(x) || IS_SCTM2(x) || IS_SCTM3(x))

#define IS_SCTM0(x)         (0)
#define IS_SCTM1(x)         (0)
#define IS_SCTM2(x)         (0)
#define IS_SCTM3(x)         (0)

#if (LIBCFG_SCTM0)
#undef IS_SCTM0
#define IS_SCTM0(x)         (x == HT_SCTM0)
#endif

#if (LIBCFG_SCTM1)
#undef IS_SCTM1
#define IS_SCTM1(x)         (x == HT_SCTM1)
#endif

#if (LIBCFG_SCTM2)
#undef IS_SCTM2
#define IS_SCTM2(x)         (x == HT_SCTM2)
#endif

#if (LIBCFG_SCTM3)
#undef IS_SCTM3
#define IS_SCTM3(x)         (x == HT_SCTM3)
#endif

/**
 * @brief Used to check parameter of the output compare mode.
 */
#define IS_TM_OM_CMP(x) (((x) == TM_OM_MATCH_NOCHANGE) || \
                           ((x) == TM_OM_MATCH_INACTIVE) || \
                           ((x) == TM_OM_MATCH_ACTIVE) || \
                           ((x) == TM_OM_MATCH_TOGGLE) || \
                           ((x) == TM_OM_PWM1) || \
                           ((x) == TM_OM_PWM2))
/**
 * @brief Used to check parameter of the output mode.
 */
#define IS_TM_OM(x) (((x) == TM_OM_MATCH_NOCHANGE)  || \
                     ((x) == TM_OM_MATCH_INACTIVE)  || \
                     ((x) == TM_OM_MATCH_ACTIVE)    || \
                     ((x) == TM_OM_MATCH_TOGGLE)    || \
                     ((x) == TM_OM_PWM1)            || \
                     ((x) == TM_OM_PWM2)            || \
                     ((x) == TM_OM_FORCED_INACTIVE) || \
                     ((x) == TM_OM_FORCED_ACTIVE)   || \
                     ((x) == TM_OM_ASYMMETRIC_PWM1) || \
                     ((x) == TM_OM_ASYMMETRIC_PWM2))

#define IS_TM_OM_NOASYM(x) (((x) == TM_OM_MATCH_NOCHANGE)  || \
                            ((x) == TM_OM_MATCH_INACTIVE)  || \
                            ((x) == TM_OM_MATCH_ACTIVE)    || \
                            ((x) == TM_OM_MATCH_TOGGLE)    || \
                            ((x) == TM_OM_PWM1)            || \
                            ((x) == TM_OM_PWM2)            || \
                            ((x) == TM_OM_FORCED_INACTIVE) || \
                            ((x) == TM_OM_FORCED_ACTIVE))
/**
 * @brief Used to check parameter of the channel.
 */
#define IS_TM_CH_0(x)     (x == TM_CH_0)
#define IS_TM_CH_1(x)     (x == TM_CH_1)
#define IS_TM_CH_2(x)     (x == TM_CH_2)
#define IS_TM_CH_3(x)     (x == TM_CH_3)
#if (LIBCFG_PWM_8_CHANNEL)
#define IS_TM_CH_4(x)     (x == TM_CH_4)
#define IS_TM_CH_5(x)     (x == TM_CH_5)
#define IS_TM_CH_6(x)     (x == TM_CH_6)
#define IS_TM_CH_7(x)     (x == TM_CH_7)
#else
#define IS_TM_CH_4(x)     (0)
#define IS_TM_CH_5(x)     (0)
#define IS_TM_CH_6(x)     (0)
#define IS_TM_CH_7(x)     (0)
#endif
#define IS_TM_CH(x)  (IS_TM_CH_0(x) || IS_TM_CH_1(x) || \
                      IS_TM_CH_2(x) || IS_TM_CH_3(x) || \
                      IS_TM_CH_4(x) || IS_TM_CH_5(x) || \
                      IS_TM_CH_6(x) || IS_TM_CH_7(x) )

/**
 * @brief Used to check parameter of the channel for PWM input function.
 */
#define IS_TM_CH_PWMI(x) (((x) == TM_CH_0) || ((x) == TM_CH_1))
/**
 * @brief Used to check parameter of the clock divider.
 */
#define IS_TM_CKDIV_OFF(x) (x == TM_CKDIV_OFF)
#define IS_TM_CKDIV_2(x)   (x == TM_CKDIV_2)
#define IS_TM_CKDIV_4(x)   (x == TM_CKDIV_4)

#if (LIBCFG_TM_CKDIV_8)
#define IS_TM_CKDIV_8(x)   (x == TM_CKDIV_8)
#else
#define IS_TM_CKDIV_8(x)   (0)
#endif

#define IS_TM_CKDIV(x)  (IS_TM_CKDIV_OFF(x) || \
                         IS_TM_CKDIV_2(x)   || \
                         IS_TM_CKDIV_4(x)   || \
                         IS_TM_CKDIV_8(x))
/**
 * @brief Used to check parameter of the counter mode.
 */
#define IS_TM_CNT_MODE(x)   ((x == TM_CNT_MODE_UP) ||  \
                             (x == TM_CNT_MODE_CA1) || \
                             (x == TM_CNT_MODE_CA2) || \
                             (x == TM_CNT_MODE_CA3) || \
                             (x == TM_CNT_MODE_DOWN))
/**
 * @brief Used to check parameter of the channel polarity.
 */
#define IS_TM_CHP(x)    ((x == TM_CHP_NONINVERTED) || (x == TM_CHP_INVERTED))
/**
 * @brief Used to check parameter of the channel control.
 */
#define IS_TM_CHCTL(x)  ((x == TM_CHCTL_DISABLE) || (x == TM_CHCTL_ENABLE))
/**
 * @brief Used to check parameter of the channel capture / compare PDMA selection.
 */
#define IS_TM_CHCCDS(x) ((x == TM_CHCCDS_CHCCEV) || (x == TM_CHCCDS_UEV))
/**
 * @brief Used to check parameter of the channel input selection.
 */
#define IS_TM_CHCCS(x)  ((x == TM_CHCCS_DIRECT) || \
                           (x == TM_CHCCS_INDIRECT) || \
                           (x == TM_CHCCS_TRCED))
/**
 * @brief Used to check parameter of the channel capture prescaler.
 */
#define IS_TM_CHPSC(x)  ((x == TM_CHPSC_OFF) || \
                           (x == TM_CHPSC_2) || \
                           (x == TM_CHPSC_4) || \
                           (x == TM_CHPSC_8))
#if 0
/**
 * @brief Used to check parameter of the ETI prescaler.
 */
#define IS_TM_ETIPSC(x) ((x == TM_ETIPSC_OFF) || \
                           (x == TM_ETIPSC_2) || \
                           (x == TM_ETIPSC_4) || \
                           (x == TM_ETIPSC_8))
#endif
/**
 * @brief Used to check parameter of the TM interrupt.
 */
#define IS_TM_INT(x) (((x & 0xFF0F10F0) == 0x0) && (x != 0))
/**
 * @brief Used to check parameter of the TM PDMA request.
 */
#define IS_TM_PDMA(x) (((x & 0xFAF0FFFF) == 0x0) && (x != 0))
/**
 * @brief Used to check parameter of the TM interrupt for \ref TM_GetIntStatus function.
 */
#define IS_TM_INT_CH0CC(x) (x == TM_INT_CH0CC)
#define IS_TM_INT_CH1CC(x) (x == TM_INT_CH1CC)
#define IS_TM_INT_CH2CC(x) (x == TM_INT_CH2CC)
#define IS_TM_INT_CH3CC(x) (x == TM_INT_CH3CC)
#if (LIBCFG_PWM_8_CHANNEL)
#define IS_TM_INT_CH4CC(x) (x == TM_INT_CH4CC)
#define IS_TM_INT_CH5CC(x) (x == TM_INT_CH5CC)
#define IS_TM_INT_CH6CC(x) (x == TM_INT_CH6CC)
#define IS_TM_INT_CH7CC(x) (x == TM_INT_CH7CC)
#else
#define IS_TM_INT_CH4CC(x) (0)
#define IS_TM_INT_CH5CC(x) (0)
#define IS_TM_INT_CH6CC(x) (0)
#define IS_TM_INT_CH7CC(x) (0)
#endif
#define IS_TM_INT_UEV(x)   (x == TM_INT_UEV)
#define IS_TM_INT_UEV2(x)  (x == TM_INT_UEV2)
#define IS_TM_INT_TEV(x)   (x == TM_INT_TEV)
#define IS_TM_INT_BRKEV(x) (x == TM_INT_BRKEV)
#define IS_TM_GET_INT(x)   (IS_TM_INT_CH0CC(x) || \
                            IS_TM_INT_CH1CC(x) || \
                            IS_TM_INT_CH2CC(x) || \
                            IS_TM_INT_CH3CC(x) || \
                            IS_TM_INT_CH4CC(x) || \
                            IS_TM_INT_CH5CC(x) || \
                            IS_TM_INT_CH6CC(x) || \
                            IS_TM_INT_CH7CC(x) || \
                            IS_TM_INT_UEV(x)   || \
                            IS_TM_INT_UEV2(x)  || \
                            IS_TM_INT_TEV(x)   || \
                            IS_TM_INT_BRKEV(x))

/**
 * @brief Used to check parameter of the TM STI selection.
 */
#define IS_TM_TRSEL(x)     ((x == TM_TRSEL_UEVG)   || \
                            (x == TM_TRSEL_TI0S0)  || \
                            (x == TM_TRSEL_TI1S1)  || \
                            (x == TM_TRSEL_ETIF)   || \
                            (x == TM_TRSEL_TI0BED) || \
                            IS_TRSEL_ITI0(x)       || \
                            IS_TRSEL_ITI1(x)       || \
                            IS_TRSEL_ITI2(x))
/**
 * @brief Used to check parameter of the ITI.
 */
#if (LIBCFG_TM_NO_ITI == 1)
#else
#define IS_TM_ITI(x)  ((x == TM_TRSEL_ITI0) || (x == TM_TRSEL_ITI1) || (x == TM_TRSEL_ITI2))
#endif
/**
 * @brief Used to check parameter of the TM_TRSEL for \ref TM_ChExternalClockConfig function.
 */
#define IS_TM_TRSEL_CH(x)  ((x == TM_TRSEL_TI0S0) || (x == TM_TRSEL_TI1S1) || \
                              (x == TM_TRSEL_TI0BED))
/**
 * @brief Used to check parameter of the TM ETI polarity.
 */
#define IS_TM_ETIPOL(x) ((x == TM_ETIPOL_NONINVERTED) || (x == TM_ETIPOL_INVERTED))
/**
 * @brief Used to check parameter of the TM prescaler reload time.
 */
#define IS_TM_PSC_RLD(x) ((x == TM_PSC_RLD_UPDATE) || (x == TM_PSC_RLD_IMMEDIATE))
/**
 * @brief Used to check parameter of the forced action.
 */
#define IS_TM_OM_FORCED(x) ((x == TM_OM_FORCED_ACTIVE) || (x == TM_OM_FORCED_INACTIVE))
/**
 * @brief Used to check parameter of the decoder mode.
 */
#define IS_TM_SMSEL_DECODER(x)  ((x == TM_SMSEL_DECODER1) || (x == TM_SMSEL_DECODER2) || \
                                   (x == TM_SMSEL_DECODER3))
/**
 * @brief Used to check parameter of the event.
 */
#define IS_TM_EVENT(x)  (((x & 0xFFFFFAF0) == 0x0000) && (x != 0x0000))
/**
 * @brief Used to check parameter of the TM master mode selection.
 */
#define IS_TM_MMSEL_RESET(x)   (x == TM_MMSEL_RESET)
#define IS_TM_MMSEL_ENABLE(x)  (x == TM_MMSEL_ENABLE)
#define IS_TM_MMSEL_UPDATE(x)  (x == TM_MMSEL_UPDATE)
#define IS_TM_MMSEL_CH0CC(x)   (x == TM_MMSEL_CH0CC)
#define IS_TM_MMSEL_CH0OREF(x) (x == TM_MMSEL_CH0OREF)
#define IS_TM_MMSEL_CH1OREF(x) (x == TM_MMSEL_CH1OREF)
#define IS_TM_MMSEL_CH2OREF(x) (x == TM_MMSEL_CH2OREF)
#define IS_TM_MMSEL_CH3OREF(x) (x == TM_MMSEL_CH3OREF)
#if (LIBCFG_PWM_8_CHANNEL)
#define IS_TM_MMSEL_CH4OREF(x) (x == TM_MMSEL_CH4OREF)
#define IS_TM_MMSEL_CH5OREF(x) (x == TM_MMSEL_CH5OREF)
#define IS_TM_MMSEL_CH6OREF(x) (x == TM_MMSEL_CH6OREF)
#define IS_TM_MMSEL_CH7OREF(x) (x == TM_MMSEL_CH7OREF)
#else
#define IS_TM_MMSEL_CH4OREF(x) (0)
#define IS_TM_MMSEL_CH5OREF(x) (0)
#define IS_TM_MMSEL_CH6OREF(x) (0)
#define IS_TM_MMSEL_CH7OREF(x) (0)
#endif
#define IS_TM_MMSEL(x)  (IS_TM_MMSEL_RESET(x)   || \
                         IS_TM_MMSEL_ENABLE(x)  || \
                         IS_TM_MMSEL_UPDATE(x)  || \
                         IS_TM_MMSEL_CH0CC(x)   || \
                         IS_TM_MMSEL_CH0OREF(x) || \
                         IS_TM_MMSEL_CH1OREF(x) || \
                         IS_TM_MMSEL_CH2OREF(x) || \
                         IS_TM_MMSEL_CH3OREF(x) || \
                         IS_TM_MMSEL_CH4OREF(x) || \
                         IS_TM_MMSEL_CH5OREF(x) || \
                         IS_TM_MMSEL_CH6OREF(x) || \
                         IS_TM_MMSEL_CH7OREF(x))

/**
 * @brief Used to check parameter of the TM slave mode.
 */
#define IS_TM_SLAVE_MODE(x) ((x == TM_SMSEL_RESTART) || (x == TM_SMSEL_PAUSE) || \
                               (x == TM_SMSEL_TRIGGER) || (x == TM_SMSEL_STIED))
/**
 * @brief Used to check parameter of the TM flag.
 */
#define IS_TM_FLAG_CH0CC(x) (x == TM_FLAG_CH0CC)
#define IS_TM_FLAG_CH1CC(x) (x == TM_FLAG_CH1CC)
#define IS_TM_FLAG_CH2CC(x) (x == TM_FLAG_CH2CC)
#define IS_TM_FLAG_CH3CC(x) (x == TM_FLAG_CH3CC)
#if (LIBCFG_PWM_8_CHANNEL)
#define IS_TM_FLAG_CH4CC(x) (x == TM_FLAG_CH4CC)
#define IS_TM_FLAG_CH5CC(x) (x == TM_FLAG_CH5CC)
#define IS_TM_FLAG_CH6CC(x) (x == TM_FLAG_CH6CC)
#define IS_TM_FLAG_CH7CC(x) (x == TM_FLAG_CH7CC)
#else
#define IS_TM_FLAG_CH4CC(x) (0)
#define IS_TM_FLAG_CH5CC(x) (0)
#define IS_TM_FLAG_CH6CC(x) (0)
#define IS_TM_FLAG_CH7CC(x) (0)
#endif
#define IS_TM_FLAG_CH0OC(x) (x == TM_FLAG_CH0OC)
#define IS_TM_FLAG_CH1OC(x) (x == TM_FLAG_CH1OC)
#define IS_TM_FLAG_CH2OC(x) (x == TM_FLAG_CH2OC)
#define IS_TM_FLAG_CH3OC(x) (x == TM_FLAG_CH3OC)
#define IS_TM_FLAG_UEV(x)   (x == TM_FLAG_UEV)
#define IS_TM_FLAG_UEV2(x)  (x == TM_FLAG_UEV2)
#define IS_TM_FLAG_TEV(x)   (x == TM_FLAG_TEV)
#define IS_TM_FLAG_BRK0(x)  (x == TM_FLAG_BRK0)
#define IS_TM_FLAG_BRK1(x)  (x == TM_FLAG_BRK1)
#define IS_TM_FLAG(x) (IS_TM_FLAG_CH0CC(x) || \
                       IS_TM_FLAG_CH1CC(x) || \
                       IS_TM_FLAG_CH2CC(x) || \
                       IS_TM_FLAG_CH3CC(x) || \
                       IS_TM_FLAG_CH4CC(x) || \
                       IS_TM_FLAG_CH5CC(x) || \
                       IS_TM_FLAG_CH6CC(x) || \
                       IS_TM_FLAG_CH7CC(x) || \
                       IS_TM_FLAG_CH0OC(x) || \
                       IS_TM_FLAG_CH1OC(x) || \
                       IS_TM_FLAG_CH2OC(x) || \
                       IS_TM_FLAG_CH3OC(x) || \
                       IS_TM_FLAG_UEV(x)   || \
                       IS_TM_FLAG_UEV2(x)  || \
                       IS_TM_FLAG_TEV(x)   || \
                       IS_TM_FLAG_BRK0(x)  || \
                       IS_TM_FLAG_BRK1(x))

/**
 * @brief Used to check parameter of the TM flag for \ref TM_ClearFlag function.
 */
#define IS_TM_FLAG_CLR(x) (((x & 0xFFFFFA00) == 0) && (x != 0))
/**
 * @brief Used to check value of TM digital filter.
 */
#if (LIBCFG_TM_652XX_V1)
#define IS_TM_FILTER(x) (x <= 0xFF)
#else
#define IS_TM_FILTER(x) (x <= 0xF)
#endif

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup TM_Exported_Functions TM exported functions
  * @{
  */
#define TM_SetCaptureCompare0(TMx, Cmp)       TM_SetCaptureCompare(TMx, TM_CH_0, Cmp)
#define TM_SetCaptureCompare1(TMx, Cmp)       TM_SetCaptureCompare(TMx, TM_CH_1, Cmp)
#define TM_SetCaptureCompare2(TMx, Cmp)       TM_SetCaptureCompare(TMx, TM_CH_2, Cmp)
#define TM_SetCaptureCompare3(TMx, Cmp)       TM_SetCaptureCompare(TMx, TM_CH_3, Cmp)
#if (LIBCFG_PWM_8_CHANNEL)
#define TM_SetCaptureCompare4(TMx, Cmp)       TM_SetCaptureCompare(TMx, TM_CH_4, Cmp)
#define TM_SetCaptureCompare5(TMx, Cmp)       TM_SetCaptureCompare(TMx, TM_CH_5, Cmp)
#define TM_SetCaptureCompare6(TMx, Cmp)       TM_SetCaptureCompare(TMx, TM_CH_6, Cmp)
#define TM_SetCaptureCompare7(TMx, Cmp)       TM_SetCaptureCompare(TMx, TM_CH_7, Cmp)
#endif

#define TM_ForcedOREF0(TMx, ForcedAction)     TM_ForcedOREF(TMx, TM_CH_0, ForcedAction)
#define TM_ForcedOREF1(TMx, ForcedAction)     TM_ForcedOREF(TMx, TM_CH_1, ForcedAction)
#define TM_ForcedOREF2(TMx, ForcedAction)     TM_ForcedOREF(TMx, TM_CH_2, ForcedAction)
#define TM_ForcedOREF3(TMx, ForcedAction)     TM_ForcedOREF(TMx, TM_CH_3, ForcedAction)
#if (LIBCFG_PWM_8_CHANNEL)
#define TM_ForcedOREF4(TMx, ForcedAction)     TM_ForcedOREF(TMx, TM_CH_4, ForcedAction)
#define TM_ForcedOREF5(TMx, ForcedAction)     TM_ForcedOREF(TMx, TM_CH_5, ForcedAction)
#define TM_ForcedOREF6(TMx, ForcedAction)     TM_ForcedOREF(TMx, TM_CH_6, ForcedAction)
#define TM_ForcedOREF7(TMx, ForcedAction)     TM_ForcedOREF(TMx, TM_CH_7, ForcedAction)
#endif

#define TM_SetAsymmetricCompare0(TMx, Cmp)    TM_SetAsymmetricCompare(TMx, TM_CH_0, Cmp)
#define TM_SetAsymmetricCompare1(TMx, Cmp)    TM_SetAsymmetricCompare(TMx, TM_CH_1, Cmp)
#define TM_SetAsymmetricCompare2(TMx, Cmp)    TM_SetAsymmetricCompare(TMx, TM_CH_2, Cmp)
#define TM_SetAsymmetricCompare3(TMx, Cmp)    TM_SetAsymmetricCompare(TMx, TM_CH_3, Cmp)

#define TM_GetCaptureCompare0(TMx)            TM_GetCaptureCompare(TMx, TM_CH_0)
#define TM_GetCaptureCompare1(TMx)            TM_GetCaptureCompare(TMx, TM_CH_1)
#define TM_GetCaptureCompare2(TMx)            TM_GetCaptureCompare(TMx, TM_CH_2)
#define TM_GetCaptureCompare3(TMx)            TM_GetCaptureCompare(TMx, TM_CH_3)
#if (LIBCFG_PWM_8_CHANNEL)
#define TM_GetCaptureCompare4(TMx)            TM_GetCaptureCompare(TMx, TM_CH_4)
#define TM_GetCaptureCompare5(TMx)            TM_GetCaptureCompare(TMx, TM_CH_5)
#define TM_GetCaptureCompare6(TMx)            TM_GetCaptureCompare(TMx, TM_CH_6)
#define TM_GetCaptureCompare7(TMx)            TM_GetCaptureCompare(TMx, TM_CH_7)
#endif

void TM_DeInit(HT_TM_TypeDef* TMx);
void TM_TimeBaseInit(HT_TM_TypeDef* TMx, TM_TimeBaseInitTypeDef* TimeBaseInit);
void TM_OutputInit(HT_TM_TypeDef* TMx, TM_OutputInitTypeDef* OutInit);
void TM_CaptureInit(HT_TM_TypeDef* TMx, TM_CaptureInitTypeDef* CapInit);
void TM_PwmInputInit(HT_TM_TypeDef* TMx, TM_CaptureInitTypeDef* CapInit);
void TM_TimeBaseStructInit(TM_TimeBaseInitTypeDef* TimeBaseInit);
void TM_OutputStructInit(TM_OutputInitTypeDef* OutInit);
void TM_CaptureStructInit(TM_CaptureInitTypeDef* CapInit);
void TM_Cmd(HT_TM_TypeDef* TMx, ControlStatus NewState);
#if (LIBCFG_TM_NO_ITI == 1)
#else
void TM_ItiExternalClockConfig(HT_TM_TypeDef* TMx, TM_TRSEL_Enum Iti);
#endif
void TM_ChExternalClockConfig(HT_TM_TypeDef* TMx, TM_TRSEL_Enum Sel, TM_CHP_Enum Pol, u8 Filter);
#if 0 // M0+ not supported
void TM_EtiExternalClockConfig(HT_TM_TypeDef* TMx, TM_ETIPSC_Enum Psc, TM_ETIPOL_Enum Pol, u8 Filter);
void TM_EtiConfig(HT_TM_TypeDef* TMx, TM_ETIPSC_Enum Psc, TM_ETIPOL_Enum Pol, u8 Filter);
#endif
void TM_PrescalerConfig(HT_TM_TypeDef* TMx, u16 Psc, TM_PSC_RLD_Enum PscReloadTime);
void TM_CounterModeConfig(HT_TM_TypeDef* TMx, TM_CNT_MODE_Enum Mod);
void TM_StiConfig(HT_TM_TypeDef* TMx, TM_TRSEL_Enum Sel);
void TM_DecoderConfig(HT_TM_TypeDef* TMx, TM_SMSEL_Enum DecoderMod, TM_CHP_Enum CH0P, TM_CHP_Enum CH1P);

void TM_ForcedOREF(HT_TM_TypeDef* TMx, TM_CH_Enum TM_CH_n, TM_OM_Enum ForcedAction);
void TM_CRRPreloadCmd(HT_TM_TypeDef* TMx, ControlStatus NewState);
void TM_CHCCRPreloadConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, ControlStatus NewState);
void TM_ClearOREFConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, ControlStatus NewState);
void TM_ChPolarityConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, TM_CHP_Enum Pol);

void TM_ImmActiveConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, ControlStatus NewState);
void TM_ChannelConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, TM_CHCTL_Enum Control);

void TM_OutputModeConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, TM_OM_Enum Mod);
void TM_UpdateCmd(HT_TM_TypeDef* TMx, ControlStatus NewState);
void TM_UEVG_IntConfig(HT_TM_TypeDef* TMx, ControlStatus NewState);
void TM_HallInterfaceCmd(HT_TM_TypeDef* TMx, ControlStatus NewState);
void TM_SinglePulseModeCmd(HT_TM_TypeDef* TMx, ControlStatus NewState);
void TM_MMSELConfig(HT_TM_TypeDef* TMx, TM_MMSEL_Enum Sel);
void TM_SlaveModeConfig(HT_TM_TypeDef* TMx, TM_SMSEL_Enum Sel);
void TM_TimSyncCmd(HT_TM_TypeDef* TMx, ControlStatus NewState);
void TM_SetCounter(HT_TM_TypeDef* TMx, u16 Counter);
void TM_SetCounterReload(HT_TM_TypeDef* TMx, u16 Reload);
void TM_SetCaptureCompare(HT_TM_TypeDef* TMx, TM_CH_Enum TM_CH_n, u16 Cmp);
void TM_SetAsymmetricCompare(HT_TM_TypeDef* TMx, TM_CH_Enum TM_CH_n, u16 Cmp);

void TM_CHPSCConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, TM_CHPSC_Enum Psc);
void TM_CKDIVConfig(HT_TM_TypeDef* TMx, TM_CKDIV_Enum Div);
u32 TM_GetCaptureCompare(HT_TM_TypeDef* TMx, TM_CH_Enum TM_CH_n);
u32 TM_GetCounter(HT_TM_TypeDef* TMx);
u32 TM_GetPrescaler(HT_TM_TypeDef* TMx);
void TM_GenerateEvent(HT_TM_TypeDef* TMx, u32 TM_EVENT);
FlagStatus TM_GetFlagStatus(HT_TM_TypeDef* TMx, u32 TM_FLAG);
void TM_ClearFlag(HT_TM_TypeDef* TMx, u32 TM_FLAG);
void TM_IntConfig(HT_TM_TypeDef* TMx, u32 TM_INT, ControlStatus NewState);
FlagStatus TM_GetIntStatus(HT_TM_TypeDef* TMx, u32 TM_INT);
void TM_ClearIntPendingBit(HT_TM_TypeDef* TMx, u32 TM_INT);
void TM_InternalClockConfig(HT_TM_TypeDef* TMx);

#if (LIBCFG_PDMA)
void TM_CHCCDSConfig(HT_TM_TypeDef* TMx, TM_CHCCDS_Enum Selection);
void TM_PDMAConfig(HT_TM_TypeDef* TMx, u32 TM_PDMA, ControlStatus NewState);
#endif
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
