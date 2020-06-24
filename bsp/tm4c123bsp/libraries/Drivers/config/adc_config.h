#ifndef _ADC_CONFIG_H_
#define _ADC_CONFIG_H_



#ifdef __cplusplus
extern "C" {
#endif


#ifdef BSP_USING_ADC0
#ifndef ADC0_CONFIG
#define ADC0_CONFIG                             \
    {                                           \
        .name                    ="adc0",       \
        .adcbase                 = ADC0_BASE,    \
        .channel                 = 0 ,           \
		.sequence                = 2 ,           \
		.trigermode              = ADC_TRIGGER_PROCESSOR,   \
        .sequencepriority        = 0             \
    }
#endif /* ADC0_CONFIG */
#endif /* BSP_USING_ADC0 */

#ifdef BSP_USING_ADC1
#ifndef ADC1_CONFIG
#define ADC1_CONFIG                             \
    {                                           \
        .name                    = "adc1",       \
        .adcbase                 = ADC1_BASE,    \
        .channel                 = 0     ,        \
		.sequence                = 3     ,        \
		.syncMode                = ADC_TRIGGER_PROCESSOR,   \
        .sequencepriority        = 0              \
    }
#endif /* ADC1_CONFIG */
#endif /* BSP_USING_ADC1 */		
				
	
#ifdef __cplusplus
}
#endif


#endif /*_ADC_CONFIG_H_*/
