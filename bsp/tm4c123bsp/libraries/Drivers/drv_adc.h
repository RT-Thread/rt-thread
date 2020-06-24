#ifndef _DRV_ADC_H_
#define _DRV_ADC_H_

#include<stdint.h>
#include<rtthread.h>
#include<rtdevice.h>
#include<rthw.h>

struct tm4c123_adc_config
{
        const char  *name;       
        uint32_t    adcbase;   
        uint32_t    channel;           
		uint32_t    sequence;                      
		uint32_t    trigermode;               
        uint32_t    sequencepriority;                   
};


#endif /*_DRV_ADC_H_*/
