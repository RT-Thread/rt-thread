#ifndef __SWM341_DMA2D_H__
#define __SWM341_DMA2D_H__

#include <stdint.h>


typedef struct {
    uint16_t Interval;          // 每传输一块数据（64个字），等待指定个系统周期后再传输下一个块，防止DMA2D占用过多SDRAM带宽，影响LCD读取显示数据；取值1--1023
    uint8_t  IntEOTEn;          // End of Transter（传输完成）中断使能
} DMA2D_InitStructure;


typedef struct {
    uint32_t Address;
    uint32_t LineOffset;        // added at the end of each line to determine the starting address of the next line
    uint8_t  ColorMode;         // DMA2D_FMT_ARGB888、DMA2D_FMT_RGB888、DMA2D_FMT_RGB565、...
    uint8_t  AlphaMode;         // DMA2D_AMODE_PIXEL、DMA2D_AMODE_ALPHA、DMA2D_AMODE_PMULA、...
    uint8_t  Alpha;

    /* 只有输出层需要设置这两个域，前景层和背景层不需设置 */
    uint16_t LineCount;         // 显示数据行数
    uint16_t LinePixel;         // 每行像素个数
} DMA2D_LayerSetting;


#define DMA2D_LAYER_FG      0   // Foreground layer
#define DMA2D_LAYER_BG      1   // Background layer
#define DMA2D_LAYER_OUT     2   // Output layer

/* Color Format */
#define DMA2D_FMT_ARGB888   (0 | (0 << 4))
#define DMA2D_FMT_RGB888    (1 | (0 << 4))
#define DMA2D_FMT_RGB565    (2 | (0 << 4))
#define DMA2D_FMT_ABGR888   (0 | (1 << 4))
#define DMA2D_FMT_BGR888    (1 | (1 << 4))
#define DMA2D_FMT_BGR565    (2 | (1 << 4))

/* Alpha Mode */
#define DMA2D_AMODE_PIXEL   (0 | (0 << 5))  // 使用像素点自带Alpha值
#define DMA2D_AMODE_ALPHA   (0 | (1 << 5))  // 使用软件指定的Alpha值
#define DMA2D_AMODE_PMULA   (0 | (2 << 5))  // 使用像素点自带Alpha值与软件指定的Alpha值的乘积


void DMA2D_Init(DMA2D_InitStructure * initStruct);
void DMA2D_PixelFill(DMA2D_LayerSetting * outLayer, uint32_t color);
void DMA2D_PixelMove(DMA2D_LayerSetting * fgLayer, DMA2D_LayerSetting * outLayer);
void DMA2D_PixelConvert(DMA2D_LayerSetting * fgLayer, DMA2D_LayerSetting * outLayer);
void DMA2D_PixelBlend(DMA2D_LayerSetting * fgLayer, DMA2D_LayerSetting * bgLayer, DMA2D_LayerSetting * outLayer);
uint32_t DMA2D_IsBusy(void);

void DMA2D_INTEn(void);
void DMA2D_INTDis(void);
void DMA2D_INTClr(void);
uint32_t DMA2D_INTStat(void);


#endif // __SWM341_DMA2D_H__
