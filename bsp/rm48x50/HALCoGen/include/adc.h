/** @file adc.h
*   @brief ADC Driver Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the ADC driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __ADC_H__
#define __ADC_H__

#include "reg_adc.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* ADC General Definitions */

/** @def adcGROUP0
*   @brief Alias name for ADC event group
*
*   @note This value should be used for API argument @a group
*/
#define adcGROUP0 0U

/** @def adcGROUP1
*   @brief Alias name for ADC group 1
*
*   @note This value should be used for API argument @a group
*/
#define adcGROUP1 1U

/** @def adcGROUP2
*   @brief Alias name for ADC group 2
*
*   @note This value should be used for API argument @a group
*/
#define adcGROUP2 2U

/** @enum adcResolution
*   @brief Alias names for data resolution
*   This enumeration is used to provide alias names for the data resolution:
*     - 12 bit resolution
*     - 10 bit resolution
*     - 8  bit resolution
*/

enum adcResolution
{
    ADC_12_BIT = 0x00000000U, /**< Alias for 12 bit data resolution */
    ADC_10_BIT = 0x00000100U, /**< Alias for 10 bit data resolution */
    ADC_8_BIT  = 0x00000200U  /**< Alias for 8 bit data resolution  */
};

/** @enum adcFiFoStatus
*   @brief Alias names for FiFo status
*   This enumeration is used to provide alias names for the current FiFo states:
*     - FiFo is not full
*     - FiFo is full
*     - FiFo overflow occurred
*/

enum adcFiFoStatus
{
    ADC_FIFO_IS_NOT_FULL = 0U, /**< Alias for FiFo is not full       */
    ADC_FIFO_IS_FULL     = 1U, /**< Alias for FiFo is full           */
    ADC_FIFO_OVERFLOW    = 3U  /**< Alias for FiFo overflow occurred  */
};

/** @enum adcConversionStatus
*   @brief Alias names for conversion status
*   This enumeration is used to provide alias names for the current conversion states:
*     - Conversion is not finished
*     - Conversion is finished
*/

enum adcConversionStatus
{
    ADC_CONVERSION_IS_NOT_FINISHED = 0U, /**< Alias for current conversion is not finished */
    ADC_CONVERSION_IS_FINISHED     = 8U  /**< Alias for current conversion is  finished    */
};

/** @enum adc1HwTriggerSource
*   @brief Alias names for hardware trigger source
*   This enumeration is used to provide alias names for the hardware trigger sources:
*/

enum adc1HwTriggerSource
{
	ADC1_EVENT = 0U,       /**< Alias for event pin             */
	ADC1_HET1_8 = 1U,      /**< Alias for HET1 pin 8            */
	ADC1_HET1_10 = 2U,     /**< Alias for HET1 pin 10           */
	ADC1_RTI_COMP0 = 3U,   /**< Alias for RTI compare 0 match   */
	ADC1_HET1_12 = 4U,     /**< Alias for HET1 pin 12           */
	ADC1_HET1_14 = 5U,     /**< Alias for HET1 pin 14           */
	ADC1_GIOB0 = 6U,       /**< Alias for GIO port b pin 0      */
	ADC1_GIOB1 = 7U,       /**< Alias for GIO port b pin 1      */

	ADC1_HET2_5 = 1U,      /**< Alias for HET2 pin 5            */
	ADC1_HET1_27 = 2U,     /**< Alias for HET1 pin 27           */
	ADC1_HET1_17 = 4U,     /**< Alias for HET1 pin 17           */
	ADC1_HET1_19 = 5U,     /**< Alias for HET1 pin 19           */
	ADC1_HET1_11 = 6U,     /**< Alias for HET1 pin 11           */
	ADC1_HET2_13 = 7U,     /**< Alias for HET2 pin 13           */

	ADC1_EPWM_B = 1U,      /**< Alias for B Signal EPWM         */
	ADC1_EPWM_A1 = 3U,     /**< Alias for A1 Signal EPWM        */	
	ADC1_HET2_1 = 5U,      /**< Alias for HET2 pin 1            */
	ADC1_EPWM_A2 = 6U,     /**< Alias for A2 Signal EPWM        */
	ADC1_EPWM_AB = 7U      /**< Alias for AB Signal EPWM        */	

};

/** @enum adc2HwTriggerSource
*   @brief Alias names for hardware trigger source
*   This enumeration is used to provide alias names for the hardware trigger sources:
*/

enum adc2HwTriggerSource
{
	ADC2_EVENT = 0U,       /**< Alias for event pin             */
	ADC2_HET1_8 = 1U,      /**< Alias for HET1 pin 8            */
	ADC2_HET1_10 = 2U,     /**< Alias for HET1 pin 10           */
	ADC2_RTI_COMP0 = 3U,   /**< Alias for RTI compare 0 match   */
	ADC2_HET1_12 = 4U,     /**< Alias for HET1 pin 12           */
	ADC2_HET1_14 = 5U,     /**< Alias for HET1 pin 14           */
	ADC2_GIOB0 = 6U,       /**< Alias for GIO port b pin 0      */
	ADC2_GIOB1 = 7U,       /**< Alias for GIO port b pin 1      */
	ADC2_HET2_5 = 1U,      /**< Alias for HET2 pin 5            */
	ADC2_HET1_27 = 2U,     /**< Alias for HET1 pin 27           */
	ADC2_HET1_17 = 4U,     /**< Alias for HET1 pin 17           */
	ADC2_HET1_19 = 5U,     /**< Alias for HET1 pin 19           */
	ADC2_HET1_11 = 6U,     /**< Alias for HET1 pin 11           */
	ADC2_HET2_13 = 7U,     /**< Alias for HET2 pin 13           */
	
	ADC2_EPWM_B = 1U,      /**< Alias for B Signal EPWM         */
	ADC2_EPWM_A1 = 3U,     /**< Alias for A1 Signal EPWM        */	
	ADC2_HET2_1 = 5U,      /**< Alias for HET2 pin 1            */
	ADC2_EPWM_A2 = 6U,     /**< Alias for A2 Signal EPWM        */
	ADC2_EPWM_AB = 7U      /**< Alias for AB Signal EPWM        */	

};

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @struct adcData
*   @brief ADC Conversion data structure
*
*   This type is used to pass adc conversion data.
*/
/** @typedef adcData_t
*   @brief ADC Data Type Definition
*/
typedef struct adcData
{
    uint32            id;     /**< Channel/Pin Id        */
    uint16 value;  /**< Conversion data value */
} adcData_t;


/* USER CODE BEGIN (2) */
/* USER CODE END */

/** 
 *  @defgroup ADC ADC
 *  @brief Analog To Digital Converter Module.
 *  
 *  The microcontroller includes two 12-bit ADC modules with selectable 10-bit or 12-bit resolution
 *
 *	Related Files
 *   - reg_adc.h
 *   - adc.h
 *   - adc.c
 *  @addtogroup ADC
 *  @{
 */
 
/* ADC Interface Functions */

void adcInit(void);
void adcStartConversion(adcBASE_t *adc, uint32 group);
void adcStopConversion(adcBASE_t *adc, uint32 group);
void adcResetFiFo(adcBASE_t *adc, uint32 group);
uint32  adcGetData(adcBASE_t *adc, uint32 group, adcData_t *data);
uint32  adcIsFifoFull(adcBASE_t *adc, uint32 group);
uint32  adcIsConversionComplete(adcBASE_t *adc, uint32 group);
void adcEnableNotification(adcBASE_t *adc, uint32 group);
void adcDisableNotification(adcBASE_t *adc, uint32 group);
void adcCalibration(adcBASE_t *adc);
uint32 adcMidPointCalibration(adcBASE_t *adc);

/** @fn void adcNotification(adcBASE_t *adc, uint32 group)
*   @brief Group notification
*   @param[in] adc Pointer to ADC node:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*   @param[in] group number of ADC node:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   @note This function has to be provide by the user.
*/
void adcNotification(adcBASE_t *adc, uint32 group);

/**@}*/
/* USER CODE BEGIN (3) */
/* USER CODE END */


#endif
