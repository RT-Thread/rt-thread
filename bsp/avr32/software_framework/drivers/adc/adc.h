/*****************************************************************************
*
* \file
*
* \brief ADC header for AVR UC3 UC3.
*
* This file defines a useful set of functions for ADC on AVR UC3 devices.
*
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
*
* \asf_license_start
*
* \page License
*
* Subject to your compliance with these terms, you may use Microchip
* software and any derivatives exclusively with Microchip products.
* It is your responsibility to comply with third party license terms applicable
* to your use of third party software (including open source software) that
* may accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
* INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
* AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
* LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
* LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
* SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
* ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
* RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*
* \asf_license_stop
*
*****************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _ADC_H_
#define _ADC_H_

/**
 * \defgroup group_avr32_drivers_adc ADC - Analog to Digital Converter
 *
 * Analog to Digital Converter is able to capture analog signals and transform
 * them
 * into digital format with 10-bit resolution.
 *
 * \{
 */

#include <avr32/io.h>
#include "compiler.h"

/* if using 8 bits for ADC, define this flag in your compiler options */
/** Max value for ADC resolution */
#ifdef USE_ADC_8_BITS
#  define ADC_MAX_VALUE    0xFF
#else
#  define ADC_MAX_VALUE    0x3FF
#endif

void adc_configure(volatile avr32_adc_t *adc);

void adc_start(volatile avr32_adc_t *adc);

void adc_enable(volatile avr32_adc_t *adc, uint16_t channel);

void adc_disable(volatile avr32_adc_t *adc, uint16_t channel);

bool adc_get_status(volatile avr32_adc_t *adc, uint16_t channel);

bool adc_check_eoc(volatile avr32_adc_t *adc, uint16_t channel);

bool adc_check_ovr(volatile avr32_adc_t *adc, uint16_t channel);

uint32_t adc_get_value(volatile avr32_adc_t *adc,
		uint16_t channel);

uint32_t adc_get_latest_value(volatile avr32_adc_t *adc);

/**
 * \}
 */

#endif  /* _ADC_H_ */
