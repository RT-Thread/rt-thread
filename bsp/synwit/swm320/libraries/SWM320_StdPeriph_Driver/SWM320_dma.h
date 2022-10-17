#ifndef __SWM320_DMA_H__
#define __SWM320_DMA_H__


#define DMA_CH0     0
#define DMA_CH1     1
#define DMA_CH2     2


void DMA_CHM_Config(uint32_t chn, uint32_t src_addr, uint32_t src_addr_incr, uint32_t dst_addr, uint32_t dst_addr_incr, uint32_t num_word, uint32_t int_en);    //DMA通道配置，用于存储器间（如Flash和RAM间）搬运数据
void DMA_CH_Open(uint32_t chn);                 //DMA通道打开
void DMA_CH_Close(uint32_t chn);                //DMA通道关闭

void DMA_CH_INTEn(uint32_t chn);                //DMA中断使能，数据搬运完成后触发中断
void DMA_CH_INTDis(uint32_t chn);               //DMA中断禁止，数据搬运完成后不触发中断
void DMA_CH_INTClr(uint32_t chn);               //DMA中断标志清除
uint32_t DMA_CH_INTStat(uint32_t chn);          //DMA中断状态查询，1 数据搬运完成    0 数据搬运未完成


#endif //__SWM320_DMA_H__
