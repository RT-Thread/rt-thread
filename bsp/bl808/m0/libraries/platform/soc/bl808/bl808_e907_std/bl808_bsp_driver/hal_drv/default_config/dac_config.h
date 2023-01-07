#ifndef _DAC_CONFIG_H
#define _DAC_CONFIG_H

/*  | vref source | rng   | output range            |
 *  | Internal    |  0    | 0.2~1V                  |
 *  | Internal    |  1/2  | 0.224~1.425V            |
 *  | Internal    |  3    | 0.2~1.8V                |
 *  | Extern      |  0    | 0.1Vref~0.5Vref         |
 *  | Extern      |  1/2  | 0.1125Vref~0.7125Vref   |
 *  | Extern      |  3    | 0.1Vref~0.9Vref         |
 */
#define DAC_REF_RNG_DEFAULT_SELECT (0x3) /*!< ADC 1.8V select */

#endif