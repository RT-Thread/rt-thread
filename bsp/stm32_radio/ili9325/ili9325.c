#include "stm32f10x.h"
#include "ili9325.h"

/* LCD Registers */
#define       R0             0x00
#define       R1             0x01
#define       R2             0x02
#define       R3             0x03
#define       R4             0x04
#define       R5             0x05
#define       R6             0x06
#define       R7             0x07
#define       R8             0x08
#define       R9             0x09
#define       R10            0x0A
#define       R12            0x0C
#define       R13            0x0D
#define       R14            0x0E
#define       R15            0x0F
#define       R16            0x10
#define       R17            0x11
#define       R18            0x12
#define       R19            0x13
#define       R20            0x14
#define       R21            0x15
#define       R22            0x16
#define       R23            0x17
#define       R24            0x18
#define       R25            0x19
#define       R26            0x1A
#define       R27            0x1B
#define       R28            0x1C
#define       R29            0x1D
#define       R30            0x1E
#define       R31            0x1F
#define       R32            0x20
#define       R33            0x21
#define       R34            0x22
#define       R36            0x24
#define       R37            0x25
#define       R40            0x28
#define       R41            0x29
#define       R43            0x2B
#define       R45            0x2D
#define       R48            0x30
#define       R49            0x31
#define       R50            0x32
#define       R51            0x33
#define       R52            0x34
#define       R53            0x35
#define       R54            0x36
#define       R55            0x37
#define       R56            0x38
#define       R57            0x39
#define       R59            0x3B
#define       R60            0x3C
#define       R61            0x3D
#define       R62            0x3E
#define       R63            0x3F
#define       R64            0x40
#define       R65            0x41
#define       R66            0x42
#define       R67            0x43
#define       R68            0x44
#define       R69            0x45
#define       R70            0x46
#define       R71            0x47
#define       R72            0x48
#define       R73            0x49
#define       R74            0x4A
#define       R75            0x4B
#define       R76            0x4C
#define       R77            0x4D
#define       R78            0x4E
#define       R79            0x4F
#define       R80            0x50
#define       R81            0x51
#define       R82            0x52
#define       R83            0x53
#define       R96            0x60
#define       R97            0x61
#define       R106           0x6A
#define       R118           0x76
#define       R128           0x80
#define       R129           0x81
#define       R130           0x82
#define       R131           0x83
#define       R132           0x84
#define       R133           0x85
#define       R134           0x86
#define       R135           0x87
#define       R136           0x88
#define       R137           0x89
#define       R139           0x8B
#define       R140           0x8C
#define       R141           0x8D
#define       R143           0x8F
#define       R144           0x90
#define       R145           0x91
#define       R146           0x92
#define       R147           0x93
#define       R148           0x94
#define       R149           0x95
#define       R150           0x96
#define       R151           0x97
#define       R152           0x98
#define       R153           0x99
#define       R154           0x9A
#define       R157           0x9D
#define       R192           0xC0
#define       R193           0xC1
#define       R229           0xE5

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0


static u16 DeviceCode;

static void LCD_CtrlLinesConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |
                           RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG |
                           RCC_APB2Periph_AFIO, ENABLE);

    /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
       PD.10(D15), PD.14(D0), PD.15(D1) as alternate
       function push pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 |
                                  GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
       PE.14(D11), PE.15(D12) as alternate function push pull */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                   GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
                                   GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_WriteBit(GPIOE, GPIO_Pin_6, Bit_SET);
    /* Set PF.00(A0 (RS)) as alternate function push pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    /* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : LCD_FSMCConfig
* Description    : Configures the Parallel interface (FSMC) for LCD(Parallel mode)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_FSMCConfig(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  p;

    /*-- FSMC Configuration ------------------------------------------------------*/
    /*----------------------- SRAM Bank 4 ----------------------------------------*/
    /* FSMC_Bank1_NORSRAM4 configuration */
    p.FSMC_AddressSetupTime = 0;
    p.FSMC_AddressHoldTime = 0;
    p.FSMC_DataSetupTime = 2;
    p.FSMC_BusTurnAroundDuration = 0;
    p.FSMC_CLKDivision = 0;
    p.FSMC_DataLatency = 0;
    p.FSMC_AccessMode = FSMC_AccessMode_A;

    /* Color LCD configuration ------------------------------------
       LCD configured as follow:
          - Data/Address MUX = Disable
          - Memory Type = SRAM
          - Data Width = 16bit
          - Write Operation = Enable
          - Extended Mode = Enable
          - Asynchronous Wait = Disable */
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM2;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
//  FSMC_NORSRAMInitStructure.FSMC_AsyncWait = FSMC_AsyncWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    /* BANK 4 (of NOR/SRAM Bank 1~4) is enabled */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM2, ENABLE);
}


void LCD_X_Init(void)
{
    /* Configure the LCD Control pins --------------------------------------------*/
    LCD_CtrlLinesConfig();

    /* Configure the FSMC Parallel interface -------------------------------------*/
    LCD_FSMCConfig();
}


/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg,u16 LCD_RegValue)
{
    /* Write 16-bit Index, then Write Reg */
    LCD->LCD_REG = LCD_Reg;
    /* Write 16-bit Reg */
    LCD->LCD_RAM = LCD_RegValue;
}

/*******************************************************************************
* Function Name  : LCD_ReadReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
*******************************************************************************/
u16 LCD_ReadReg(u8 LCD_Reg)
{
    /* Write 16-bit Index (then Read Reg) */
    LCD->LCD_REG = LCD_Reg;
    /* Read 16-bit Reg */
    return (LCD->LCD_RAM);
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM_Prepare
* Description    : Prepare to write to the LCD RAM.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
    LCD->LCD_REG = R34;
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM
* Description    : Writes to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM(u16 RGB_Code)
{
    /* Write 16-bit GRAM Reg */
    LCD->LCD_RAM = RGB_Code;
}

/*******************************************************************************
* Function Name  : LCD_ReadRAM
* Description    : Reads the LCD RAM.
* Input          : None
* Output         : None
* Return         : LCD RAM Value.
*******************************************************************************/
u16 LCD_ReadRAM(void)
{
    //u16 dummy;
    /* Write 16-bit Index (then Read Reg) */
    LCD->LCD_REG = R34; /* Select GRAM Reg */
    /* Read 16-bit Reg */
    //dummy = LCD->LCD_RAM;
    return LCD->LCD_RAM;
}


/* 读取指定地址的GRAM */
unsigned short ili9325_ReadGRAM(unsigned short x,unsigned short y)
{
    unsigned short temp;
    ili9325_SetCursor(x,y);
    LCD->LCD_REG = R34;
    /* dummy read */
    temp = LCD->LCD_RAM;
    temp = LCD->LCD_RAM;
    return temp;
}
/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : Sets the cursor position.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
* Output         : None
* Return         : None
*******************************************************************************/


//void LCD_SetCursor(u16 Xpos, u16 Ypos)
//{
//    LCD_WriteReg(0x06,Ypos>>8);
//    LCD_WriteReg(0x07,Ypos);
//
//    LCD_WriteReg(0x02,Xpos>>8);
//    LCD_WriteReg(0x03,Xpos);
//}


void Delay(u32 nCount)
{
    u32 TimingDelay;
    while (nCount--)
    {
        for (TimingDelay=0; TimingDelay<10000; TimingDelay++);
    }
}

void ili9325_Initializtion(void)
{
    /*****************************
    **    硬件连接说明          **
    ** STM32         ili9320    **
    ** PE0~15 <----> DB0~15     **
    ** PD15   <----> nRD        **
    ** PD14   <----> RS         **
    ** PD13   <----> nWR        **
    ** PD12   <----> nCS        **
    ** PD11   <----> nReset     **
    ** PC0    <----> BK_LED     **
    ******************************/
    u16 i;
    LCD_X_Init();

    {
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);

        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_Init(GPIOF,&GPIO_InitStructure);
    }
    GPIO_ResetBits(GPIOF, GPIO_Pin_10);
    Delay(5);
    GPIO_SetBits(GPIOF, GPIO_Pin_10);
    Delay(5);

    DeviceCode = LCD_ReadReg(0x0000);
    if (DeviceCode==0x9325||DeviceCode==0x9328)
    {
        LCD_WriteReg(0x00e7,0x0010);
        LCD_WriteReg(0x0000,0x0001);  			        //start internal osc
        LCD_WriteReg(0x0001,0x0100);
        LCD_WriteReg(0x0002,0x0700); 				    //power on sequence
        /* [5:4]-ID1~ID0 [3]-AM-1垂直-0水平 */
        LCD_WriteReg(0x0003,(1<<12)|(1<<5)|(0<<4) | (1<<3) );
        LCD_WriteReg(0x0004,0x0000);
        LCD_WriteReg(0x0008,0x0207);
        LCD_WriteReg(0x0009,0x0000);
        LCD_WriteReg(0x000a,0x0000); 				//display setting
        LCD_WriteReg(0x000c,0x0001);				//display setting
        LCD_WriteReg(0x000d,0x0000); 				//0f3c
        LCD_WriteReg(0x000f,0x0000);
        //Power On sequence //
        LCD_WriteReg(0x0010,0x0000);
        LCD_WriteReg(0x0011,0x0007);
        LCD_WriteReg(0x0012,0x0000);
        LCD_WriteReg(0x0013,0x0000);
        for (i=50000; i>0; i--);
        for (i=50000; i>0; i--);
        LCD_WriteReg(0x0010,0x1590);
        LCD_WriteReg(0x0011,0x0227);
        for (i=50000; i>0; i--);
        for (i=50000; i>0; i--);
        LCD_WriteReg(0x0012,0x009c);
        for (i=50000; i>0; i--);
        for (i=50000; i>0; i--);
        LCD_WriteReg(0x0013,0x1900);
        LCD_WriteReg(0x0029,0x0023);
        LCD_WriteReg(0x002b,0x000e);
        for (i=50000; i>0; i--);
        for (i=50000; i>0; i--);
        LCD_WriteReg(0x0020,0x0000);
        LCD_WriteReg(0x0021,0x0000);
///////////////////////////////////////////////////////
        for (i=50000; i>0; i--);
        for (i=50000; i>0; i--);
        LCD_WriteReg(0x0030,0x0007);
        LCD_WriteReg(0x0031,0x0707);
        LCD_WriteReg(0x0032,0x0006);
        LCD_WriteReg(0x0035,0x0704);
        LCD_WriteReg(0x0036,0x1f04);
        LCD_WriteReg(0x0037,0x0004);
        LCD_WriteReg(0x0038,0x0000);
        LCD_WriteReg(0x0039,0x0706);
        LCD_WriteReg(0x003c,0x0701);
        LCD_WriteReg(0x003d,0x000f);
        for (i=50000; i>0; i--);
        for (i=50000; i>0; i--);
        LCD_WriteReg(0x0050,0x0000);
        LCD_WriteReg(0x0051,0x00ef);
        LCD_WriteReg(0x0052,0x0000);
        LCD_WriteReg(0x0053,0x013f);
        LCD_WriteReg(0x0060,0xa700);
        LCD_WriteReg(0x0061,0x0001);
        LCD_WriteReg(0x006a,0x0000);
        LCD_WriteReg(0x0080,0x0000);
        LCD_WriteReg(0x0081,0x0000);
        LCD_WriteReg(0x0082,0x0000);
        LCD_WriteReg(0x0083,0x0000);
        LCD_WriteReg(0x0084,0x0000);
        LCD_WriteReg(0x0085,0x0000);

        LCD_WriteReg(0x0090,0x0010);
        LCD_WriteReg(0x0092,0x0000);
        LCD_WriteReg(0x0093,0x0003);
        LCD_WriteReg(0x0095,0x0110);
        LCD_WriteReg(0x0097,0x0000);
        LCD_WriteReg(0x0098,0x0000);
        //display on sequence
        LCD_WriteReg(0x0007,0x0133);

        LCD_WriteReg(0x0020,0x0000);
        LCD_WriteReg(0x0021,0x0000);
    }
    ili9325_Clear( Blue );
}

/****************************************************************************
* 名    称：void ili9325_SetCursor(u16 x,u16 y)
* 功    能：设置屏幕座标
* 入口参数：x      行座标
*           y      列座标
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetCursor(10,10);
****************************************************************************/
void ili9325_SetCursor(u16 x,u16 y)
{
    LCD_WriteReg(R32,x); /* 0-239 */
    LCD_WriteReg(R33,y); /* 0-319 */
}

/****************************************************************************
* 名    称：void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
* 功    能：设置窗口区域
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetWindows(0,0,100,100)；
****************************************************************************/
void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
{
    ili9325_SetCursor(StartX,StartY);
    LCD_WriteReg(0x0050, StartX);
    LCD_WriteReg(0x0052, StartY);
    LCD_WriteReg(0x0051, EndX);
    LCD_WriteReg(0x0053, EndY);
}

/****************************************************************************
* 名    称：void ili9320_Clear(u16 dat)
* 功    能：将屏幕填充成指定的颜色，如清屏，则填充 0xffff
* 入口参数：dat      填充值
* 出口参数：无
* 说    明：
* 调用方法：ili9320_Clear(0xffff);
****************************************************************************/
void ili9325_Clear(u16 Color)
{
    u32 index=0;
    ili9325_SetCursor(0,0);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    for (index=0; index<76800; index++)
    {
        LCD->LCD_RAM=Color;
    }
}

/****************************************************************************
* 名    称：u16 ili9320_GetPoint(u16 x,u16 y)
* 功    能：获取指定座标的颜色值
* 入口参数：x      行座标
*           y      列座标
* 出口参数：当前座标颜色值
* 说    明：
* 调用方法：i=ili9320_GetPoint(10,10);
****************************************************************************/
u16 ili9320_GetPoint(u16 x,u16 y)
{
    ili9325_SetCursor(x,y);
    return (ili9325_BGR2RGB(LCD_ReadRAM()));
}
/****************************************************************************
* 名    称：void ili9320_SetPoint(u16 x,u16 y,u16 point)
* 功    能：在指定座标画点
* 入口参数：x      行座标
*           y      列座标
*           point  点的颜色
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetPoint(10,10,0x0fe0);
****************************************************************************/
void ili9320_SetPoint(u16 x,u16 y,u16 point)
{
    if ( (x>320)||(y>240) ) return;
    ili9325_SetCursor(x,y);

    LCD_WriteRAM_Prepare();
    LCD_WriteRAM(point);
}

/****************************************************************************
* 名    称：void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
* 功    能：在指定座标范围显示一副图片
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
            pic        图片头指针
* 出口参数：无
* 说    明：图片取模格式为水平扫描，16位颜色模式
* 调用方法：ili9320_DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
{
    u16  i;
    ili9320_SetWindows(StartX,StartY,EndX,EndY);
    ili9325_SetCursor(StartX,StartY);

    LCD_WriteRAM_Prepare();
    for (i=0; i<(EndX*EndY); i++)
    {
        LCD_WriteRAM(*pic++);
    }
}


/****************************************************************************
* 名    称：u16 ili9325_BGR2RGB(u16 c)
* 功    能：RRRRRGGGGGGBBBBB 改为 BBBBBGGGGGGRRRRR 格式
* 入口参数：c      BRG 颜色值
* 出口参数：RGB 颜色值
* 说    明：内部函数调用
* 调用方法：
****************************************************************************/
unsigned short ili9325_BGR2RGB(unsigned short c)
{
    u16  r, g, b, rgb;

    b = (c>>0)  & 0x1f;
    g = (c>>5)  & 0x3f;
    r = (c>>11) & 0x1f;

    rgb =  (b<<11) + (g<<5) + (r<<0);

    return( rgb );
}
