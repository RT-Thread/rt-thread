#ifndef __SWM341_LCD_H__
#define __SWM341_LCD_H__


typedef struct {
    uint8_t  ClkDiv;        //取值范围2--65
    uint8_t  Format;        //LCD_FMT_RGB565、LCD_FMT_RGB888、LCD_FMT_SRGB565、LCD_FMT_SRGB888
    uint16_t HnPixel;       //水平方向像素个数，最大取值1024
    uint16_t VnPixel;       //垂直方向像素个数，最大取值1024
    uint8_t  Hfp;           //horizonal front porch，最大取值64
    uint16_t Hbp;           //horizonal back porch， 最大取值256
    uint8_t  Vfp;           //vertical front porch， 最大取值64
    uint16_t Vbp;           //vertical back porch，  最大取值256
    uint16_t HsyncWidth;    //HSYNC低电平持续多少个DOTCLK，最大取值256
    uint16_t VsyncWidth;    //VSYNC低电平持续多少个行时间，最大取值256

    uint32_t DataSource;    //显示数据地址
    uint32_t Background;    //背景颜色
    uint8_t  SampleEdge;    //屏幕在DOTCLK的哪个边沿采样数据：LCD_SAMPLE_RISE、LCD_SAMPLE_FALL

    uint8_t  IntEOTEn;      //End of Transter（传输完成）中断使能
} LCD_InitStructure;


typedef struct {
    uint8_t  Alpha;
    uint16_t HStart;        //水平方向起始位置，取值范围0 ~ HnPixel-1
    uint16_t HStop;         //水平方向终止位置（包含），不得小于HStart，且 HStop - HStart 结果必须为奇数
    uint16_t VStart;
    uint16_t VStop;
    uint32_t DataSource;    //显示数据地址
} LCD_LayerInitStructure;


#define LCD_FMT_RGB565  0
#define LCD_FMT_RGB888  1
#define LCD_FMT_SRGB565 2   //Serial RGB
#define LCD_FMT_SRGB888 3

#define LCD_SAMPLE_RISE 0   //屏幕在DOTCLK的上升沿采样数据
#define LCD_SAMPLE_FALL 1   //屏幕在DOTCLK的下降沿采样数据

#define LCD_LAYER_1     0
#define LCD_LAYER_2     1


void LCD_Init(LCD_TypeDef * LCDx, LCD_InitStructure * initStruct);
void LCD_LayerInit(LCD_TypeDef * LCDx, uint32_t layerx, LCD_LayerInitStructure * initStruct);
void LCD_SetLayerPos(LCD_TypeDef * LCDx, uint32_t layerx, uint16_t hstart, uint16_t hstop, uint16_t vstart, uint16_t vstop);
void LCD_Start(LCD_TypeDef * LCDx);
uint32_t LCD_IsBusy(LCD_TypeDef * LCDx);

void LCD_INTEn(LCD_TypeDef * LCDx);
void LCD_INTDis(LCD_TypeDef * LCDx);
void LCD_INTClr(LCD_TypeDef * LCDx);
uint32_t LCD_INTStat(LCD_TypeDef * LCDx);



typedef struct {
    uint8_t  RDHoldTime;    //LCD_RD低电平保持时间,取值1--32
    uint8_t  WRHoldTime;    //LCD_WR低电平保持时间,取值1--16
    uint8_t  CSFall_WRFall; //LCD_CS下降沿到LCD_WR下降沿延时，取值1--4
    uint8_t  WRRise_CSRise; //LCD_WR上升沿到LCD_CS上升沿延时，取值1--4
    uint8_t  RDCSRise_Fall; //读操作时，LCD_CS上升沿到下降沿延时，取值1--32
    uint8_t  WRCSRise_Fall; //写操作时，LCD_CS上升沿到下降沿延时，取值1--16
} MPULCD_InitStructure;


void MPULCD_Init(LCD_TypeDef * LCDx, MPULCD_InitStructure * initStruct);

void LCD_WR_REG(LCD_TypeDef * LCDx, uint16_t reg);
void LCD_WR_DATA(LCD_TypeDef * LCDx, uint16_t val);
void LCD_WriteReg(LCD_TypeDef * LCDx, uint16_t reg, uint16_t val);
uint16_t LCD_ReadReg(LCD_TypeDef * LCDx, uint16_t reg);

void MPULCD_DMAStart(LCD_TypeDef * LCDx, uint32_t * buff, uint16_t hpix, uint16_t vpix);
uint32_t MPULCD_DMABusy(LCD_TypeDef * LCDx);


#endif //__SWM341_LCD_H__
