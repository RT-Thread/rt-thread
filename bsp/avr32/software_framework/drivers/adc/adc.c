/*****************************************************************************
*
* \file
*
* \brief ADC driver for AVR UC3.
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

#include <avr32/io.h>
#include "compiler.h"
#include "adc.h"

/** \brief Configure ADC. Mandatory to call.
 * If not called, ADC channels will have side effects
 *
 * \param *adc Base address of the ADC
 */
void adc_configure(volatile avr32_adc_t *adc)
{
	Assert( adc != NULL );

#ifdef USE_ADC_8_BITS
	adc->mr |= 1 << AVR32_ADC_LOWRES_OFFSET;
#endif

	/* Set Sample/Hold time to max so that the ADC capacitor should be
	 * loaded entirely */
	adc->mr |= 0xF << AVR32_ADC_SHTIM_OFFSET;

	/* Set Startup to max so that the ADC capacitor should be loaded
	 * entirely */
	adc->mr |= 0x1F << AVR32_ADC_STARTUP_OFFSET;
}

/** \brief Start analog to digital conversion
 * \param *adc Base address of the ADC
 */
void adc_start(volatile avr32_adc_t *adc)
{
	Assert( adc != NULL );

	/* start conversion */
	adc->cr = AVR32_ADC_START_MASK;
}

/** \brief Enable channel
 *
 * \param *adc Base address of the ADC
 * \param  channel   channel to enable (0 to 7)
 */
void adc_enable(volatile avr32_adc_t *adc, uint16_t channel)
{
	Assert( adc != NULL );
	Assert( channel <= AVR32_ADC_CHANNELS_MSB ); /* check if channel exist
	                                              **/

	/* enable channel */
	adc->cher = (1 << channel);
}

/** \brief Disable channel
 *
 * \param *adc Base address of the ADC
 * \param  channel   channel to disable (0 to 7)
 */
void adc_disable(volatile avr32_adc_t *adc, uint16_t channel)
{
	Assert( adc != NULL );
	Assert( channel <= AVR32_ADC_CHANNELS_MSB ); /* check if channel exist
	                                              **/

	if (adc_get_status(adc, channel) == true) {
		/* disable channel */
		adc->chdr |= (1 << channel);
	}
}

/** \brief Get channel 0 to 7 status
 *
 * \param *adc Base address of the ADC
 * \param  channel   channel to handle (0 to 7)
 * \return bool      true if channel is enabled
 *                   false if channel is disabled
 */
bool adc_get_status(volatile avr32_adc_t *adc, uint16_t channel)
{
	Assert( adc != NULL );
	Assert( channel <= AVR32_ADC_CHANNELS_MSB ); /* check if channel exist
	                                              **/

	return ((adc->chsr & (1 << channel)) ? true : false);
}

/** \brief Check channel conversion status
 *
 * \param *adc Base address of the ADC
 * \param  channel   channel to check (0 to 7)
 * \return bool      true if conversion not running
 *                   false if conversion running
 */
bool adc_check_eoc(volatile avr32_adc_t *adc, uint16_t channel)
{
	Assert( adc != NULL );
	Assert( channel <= AVR32_ADC_CHANNELS_MSB ); /* check if channel exist
	                                              **/

	/* get SR register : EOC bit for channel */
	return ((adc->sr & (1 << channel)) ? true : false);
}

/** \brief Check channel conversion overrun error
 *
 * \param *adc Base address of the ADC
 * \param  channel   channel to check (0 to 7)
 * \return bool      FAIL if an error occurred
 *                   PASS if no error occurred
 */
bool adc_check_ovr(volatile avr32_adc_t *adc, uint16_t channel)
{
	Assert( adc != NULL );
	Assert( channel <= AVR32_ADC_CHANNELS_MSB ); /* check if channel exist
	                                              **/

	/* get SR register : OVR bit for channel */
	return ((adc->sr & (1 << (channel + 8))) ? FAIL : PASS);
}

/** \brief Get channel value
 *
 * \param *adc Base address of the ADC
 * \param  channel   channel to handle (0 to 7)
 * \return The value acquired (unsigned long)
 */
uint32_t adc_get_value(volatile avr32_adc_t *adc, uint16_t channel)
{
	Assert( adc != NULL );
	Assert( channel <= AVR32_ADC_CHANNELS_MSB );

	/* wait for end of conversion */
	while (adc_check_eoc(adc, channel) != true) {
	}

	return *((uint32_t *)((&(adc->cdr0)) + channel));
}

/** \brief Wait for the next converted data and return its value
 *
 * \param *adc Base address of the ADC
 * \return The latest converted value (unsigned long)
 */
uint32_t adc_get_latest_value(volatile avr32_adc_t *adc)
{
	Assert( adc != NULL );

	/* Wait for the data ready flag */
	while ((adc->sr & AVR32_ADC_DRDY_MASK) != AVR32_ADC_DRDY_MASK) {
	}

	return adc->lcdr;
}
