#ifndef __SWM341_DAC_H__
#define __SWM341_DAC_H__


#define DAC_FORMAT_LSB12B   0   //12位数据，DHR[11:0] => DOR[11:0]
#define DAC_FORMAT_MSB12B   1   //12位数据，DHR[15:4] => DOR[11:0]
#define DAC_FORMAT_8B       3   // 8位数据，DHR[7 :0] => DOR[11:4]


void DAC_Init(DAC_TypeDef * DACx, uint32_t format);
void DAC_Open(DAC_TypeDef * DACx);
void DAC_Close(DAC_TypeDef * DACx);


#endif //__SWM341_DAC_H__
