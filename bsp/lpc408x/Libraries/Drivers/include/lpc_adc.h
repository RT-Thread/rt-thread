/**********************************************************************
* $Id$      lpc_adc.h           2011-06-02
*//**
* @file     lpc_adc.h
* @brief    Contains all macro definitions and function prototypes
*           support for ADC firmware library on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup ADC ADC (Analog-to-Digital Converter)
 * @ingroup LPC_CMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC_ADC_H_
#define __LPC_ADC_H_

/* Includes ------------------------------------------------------------------- */
#include "LPC407x_8x_177x_8x.h"
#include "lpc_types.h"


#ifdef __cplusplus
extern "C"
{
#endif

/* Private macros ------------------------------------------------------------- */
/** @defgroup ADC_Private_Macros ADC Private Macros
 * @{
 */

/* -------------------------- BIT DEFINITIONS ----------------------------------- */
/*********************************************************************//**
 * Macro defines for ADC  control register
 **********************************************************************/

/**  Selects which of the AD0.0:7 pins (channels) is (are) to be sampled and converted */
#define ADC_CR_CH_SEL(n)    ((1UL << n))

/**  The APB clock (PCLK) is divided by (this value plus one)
* to produce the clock for the A/D */
#define ADC_CR_CLKDIV(n)    ((n<<8))

/**  Repeated conversions A/D enable bit */
#define ADC_CR_BURST        ((1UL<<16))

/**  ADC convert in power down mode; if 0, it's in power down mode; if 1, it's in normal
* operation mode */
#define ADC_CR_PDN          ((1UL<<21))

/**  Start mask bits */
#define ADC_CR_START_MASK   ((7UL<<24))

/**  Select Start Mode controll the AD Converter in case the Burst bit is 0 (zero) */
#define ADC_CR_START_MODE_SEL(SEL)  ((SEL<<24))

/**  Start conversion now */
#define ADC_CR_START_NOW    ((1UL<<24))

/**  Start conversion when the edge selected by bit 27 occurs on P2.10/EINT0 */
#define ADC_CR_START_EINT0  ((2UL<<24))

/** Start conversion when the edge selected by bit 27 occurs on P1.27/CAP0.1 */
#define ADC_CR_START_CAP01  ((3UL<<24))

/**  Start conversion when the edge selected by bit 27 occurs on MAT0.1 */
#define ADC_CR_START_MAT01  ((4UL<<24))

/**  Start conversion when the edge selected by bit 27 occurs on MAT0.3 */
#define ADC_CR_START_MAT03  ((5UL<<24))

/**  Start conversion when the edge selected by bit 27 occurs on MAT1.0 */
#define ADC_CR_START_MAT10  ((6UL<<24))

/**  Start conversion when the edge selected by bit 27 occurs on MAT1.1 */
#define ADC_CR_START_MAT11  ((7UL<<24))

/**  Start conversion on a falling edge on the selected CAP/MAT signal */
#define ADC_CR_EDGE         ((1UL<<27))

/*********************************************************************//**
 * Macro defines for ADC Global Data register
 **********************************************************************/

/** When DONE is 1, this field contains result value of ADC conversion
* (in 12-bit value) */
#define ADC_GDR_RESULT(n)       (((n>>4)&0xFFF))

/** These bits contain the channel from which the LS bits were converted */
#define ADC_GDR_CH(n)           (((n>>24)&0x7))

/** This bits is used to mask for Channel */
#define ADC_GDR_CH_MASK         ((7UL<<24))

/** This bit is 1 in burst mode if the results of one or
 * more conversions was (were) lost */
#define ADC_GDR_OVERRUN_FLAG    ((1UL<<30))

/** This bit is set to 1 when an A/D conversion completes */
#define ADC_GDR_DONE_FLAG       ((1UL<<31))

/*********************************************************************//**
 * Macro defines for ADC Interrupt register
 **********************************************************************/

/** These bits allow control over which A/D channels generate
 * interrupts for conversion completion */
#define ADC_INTEN_CH(n)         ((1UL<<n))

/** When 1, enables the global DONE flag in ADDR to generate an interrupt */
#define ADC_INTEN_GLOBAL        ((1UL<<8))

/*********************************************************************//**
 * Macro defines for ADC Data register
 **********************************************************************/

/** When DONE is 1, this field contains result value of ADC conversion */
#define ADC_DR_RESULT(n)        (((n>>4)&0xFFF))

/** These bits mirror the OVERRRUN status flags that appear in the
 * result register for each A/D channel */
#define ADC_DR_OVERRUN_FLAG     ((1UL<<30))

/** This bit is set to 1 when an A/D conversion completes. It is cleared
 * when this register is read */
#define ADC_DR_DONE_FLAG        ((1UL<<31))

/*********************************************************************//**
 * Macro defines for ADC Status register
**********************************************************************/

/** These bits mirror the DONE status flags that appear in the result
 * register for each A/D channel */
#define ADC_STAT_CH_DONE_FLAG(n)        ((n&0xFF))

/** These bits mirror the OVERRRUN status flags that appear in the
 * result register for each A/D channel */
#define ADC_STAT_CH_OVERRUN_FLAG(n)     (((n>>8)&0xFF))

/** This bit is the A/D interrupt flag */
#define ADC_STAT_INT_FLAG               ((1UL<<16))

/*********************************************************************//**
 * Macro defines for ADC Trim register
**********************************************************************/

/** Offset trim bits for ADC operation */
#define ADC_ADCOFFS(n)      (((n&0xF)<<4))

/** Written to boot code*/
#define ADC_TRIM(n)         (((n&0xF)<<8))

/**
 * @}
 */


/* Public Types --------------------------------------------------------------- */
/** @defgroup ADC_Public_Types ADC Public Types
 * @{
 */

/*********************************************************************//**
 * @brief ADC enumeration
 **********************************************************************/

/** @brief Channel Selection */
typedef enum
{
    ADC_CHANNEL_0  = 0, /*!<  Channel 0 */
    ADC_CHANNEL_1,      /*!<  Channel 1 */
    ADC_CHANNEL_2,      /*!<  Channel 2 */
    ADC_CHANNEL_3,      /*!<  Channel 3 */
    ADC_CHANNEL_4,      /*!<  Channel 4 */
    ADC_CHANNEL_5,      /*!<  Channel 5 */
    ADC_CHANNEL_6,      /*!<  Channel 6 */
    ADC_CHANNEL_7       /*!<  Channel 7 */
}ADC_CHANNEL_SELECTION;

/** @brief Type of start option */
typedef enum
{
    ADC_START_CONTINUOUS = 0,   /*!< Continuous mode */

    ADC_START_NOW,              /*!< Start conversion now */

    ADC_START_ON_EINT0,         /*!< Start conversion when the edge selected
                                 * by bit 27 occurs on P2.10/EINT0 */
    ADC_START_ON_CAP01,         /*!< Start conversion when the edge selected
                                 * by bit 27 occurs on P1.27/CAP0.1 */
    ADC_START_ON_MAT01,         /*!< Start conversion when the edge selected
                                 * by bit 27 occurs on MAT0.1 */
    ADC_START_ON_MAT03,         /*!< Start conversion when the edge selected
                                 * by bit 27 occurs on MAT0.3 */
    ADC_START_ON_MAT10,         /*!< Start conversion when the edge selected
                                  * by bit 27 occurs on MAT1.0 */
    ADC_START_ON_MAT11          /*!< Start conversion when the edge selected
                                  * by bit 27 occurs on MAT1.1 */
} ADC_START_OPT;


/** @brief Type of edge when start conversion on the selected CAP/MAT signal */
typedef enum
{
    ADC_START_ON_RISING = 0,    /*!< Start conversion on a rising edge
                                *on the selected CAP/MAT signal */
    ADC_START_ON_FALLING        /*!< Start conversion on a falling edge
                                *on the selected CAP/MAT signal */
} ADC_START_ON_EDGE_OPT;

/** @brief* ADC type interrupt enum */
typedef enum
{
    ADC_ADINTEN0 = 0,       /*!< Interrupt channel 0 */
    ADC_ADINTEN1,           /*!< Interrupt channel 1 */
    ADC_ADINTEN2,           /*!< Interrupt channel 2 */
    ADC_ADINTEN3,           /*!< Interrupt channel 3 */
    ADC_ADINTEN4,           /*!< Interrupt channel 4 */
    ADC_ADINTEN5,           /*!< Interrupt channel 5 */
    ADC_ADINTEN6,           /*!< Interrupt channel 6 */
    ADC_ADINTEN7,           /*!< Interrupt channel 7 */
    ADC_ADGINTEN            /*!< Individual channel/global flag done generate an interrupt */
}ADC_TYPE_INT_OPT;

/** @brief ADC Data  status */
typedef enum
{
    ADC_DATA_BURST = 0,     /*Burst bit*/
    ADC_DATA_DONE           /*Done bit*/
}ADC_DATA_STATUS;

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @defgroup ADC_Public_Functions ADC Public Functions
 * @{
 */
 
/* Init/DeInit ADC peripheral ----------------*/
void ADC_Init(LPC_ADC_TypeDef *ADCx, uint32_t rate);
void ADC_DeInit(LPC_ADC_TypeDef *ADCx);

/* Enable/Disable ADC functions --------------*/
void ADC_BurstCmd(LPC_ADC_TypeDef *ADCx, FunctionalState NewState);
void ADC_PowerdownCmd(LPC_ADC_TypeDef *ADCx, FunctionalState NewState);
void ADC_StartCmd(LPC_ADC_TypeDef *ADCx, uint8_t start_mode);
void ADC_ChannelCmd (LPC_ADC_TypeDef *ADCx, uint8_t Channel, FunctionalState NewState);

/* Configure ADC functions -------------------*/
void ADC_EdgeStartConfig(LPC_ADC_TypeDef *ADCx, uint8_t EdgeOption);
void ADC_IntConfig (LPC_ADC_TypeDef *ADCx, ADC_TYPE_INT_OPT IntType, FunctionalState NewState);

/* Get ADC information functions -------------------*/
uint16_t ADC_ChannelGetData(LPC_ADC_TypeDef *ADCx, uint8_t channel);
FlagStatus ADC_ChannelGetStatus(LPC_ADC_TypeDef *ADCx, uint8_t channel, uint32_t StatusType);
uint32_t ADC_GlobalGetData(LPC_ADC_TypeDef *ADCx);
FlagStatus  ADC_GlobalGetStatus(LPC_ADC_TypeDef *ADCx, uint32_t StatusType);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif


#endif /* LPC_ADC_H_ */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
