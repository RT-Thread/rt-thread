#include "FMT0371.h"
#include "stm32f10x.h"

#define FSMC_GPIO_CONFIG

static void delay_ms(unsigned int dt)
{
    volatile unsigned int u;
    for (u=0;u<dt*30;u++);
}

static void FSMC_Init(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  p;

#ifdef FSMC_GPIO_CONFIG
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOE |
                           RCC_APB2Periph_GPIOF, ENABLE);

    /*-- GPIO Configuration ------------------------------------------------------*/
    /* SRAM Data lines configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 |
                                  GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
                                  GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /* SRAM Address lines configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
                                  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 |
                                  GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
                                  GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* NOE and NWE configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* NE2 configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    /* NBL0, NBL1 configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
#endif

    /*-- FSMC Configuration ------------------------------------------------------*/
    p.FSMC_AddressSetupTime = 2; // safe value 2
    p.FSMC_AddressHoldTime = 1;  // safe value 2
    p.FSMC_DataSetupTime = 3;    // safe value 5
    p.FSMC_BusTurnAroundDuration = 0;
    p.FSMC_CLKDivision = 0;
    p.FSMC_DataLatency = 0;
    p.FSMC_AccessMode = FSMC_AccessMode_A;

    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM2;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    /* Enable FSMC Bank1_SRAM Bank */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM2, ENABLE);
}

void ftm0371_port_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(LCD_RST_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = LCD_RST_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(LCD_RST_PORT, &GPIO_InitStructure);
    LCD_RST_0; // reset the lcd

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    FSMC_Init();
}

//初始化函数
void ftm0371_init(void)
{
    LCD_RST_1;
	delay_ms(1000);

    //initializing funciton 1
    LCD_WR_REG(0xA1);
    LCD_WR_DATA8(0x00);
    LCD_WR_REG(0xA0);
    LCD_WR_DATA8(0x00);
    LCD_WR_CMD(0,0x70,0xC8);

    LCD_WR_CMD(0,0x72,0xA3);
    LCD_WR_CMD(0,0x73,0x04);
    LCD_WR_CMD(0,0x75,0x45);
    LCD_WR_CMD(0,0x76,0x23);
    LCD_WR_CMD(0,0x77,0x08);
    LCD_WR_CMD(0,0x78,0x08);
    LCD_WR_CMD(0,0x79,0x00);
    LCD_WR_CMD(0,0x7F,0xF0);
    LCD_WR_CMD(0,0x71,0x81);	//

    LCD_WR_CMD(0,0x0D,0x23);
    LCD_WR_CMD(0,0x11,0x00);
    LCD_WR_CMD(0,0x12,0x00);
    LCD_WR_CMD(0,0x21,0x37);
    LCD_WR_CMD(0,0x22,0x02);
    LCD_WR_CMD(0,0x23,0x24);
    LCD_WR_CMD(0,0x24,0x13);
    LCD_WR_CMD(0,0x25,0x0A);
    LCD_WR_CMD(0,0x26,0x82);
    LCD_WR_CMD(0,0x27,0x01);
    LCD_WR_CMD(0,0x1E,0x25);
    LCD_WR_CMD(0,0x1F,0x59);

    //GAMMA设置
    LCD_WR_CMD(1,0x30,0x0777);
    LCD_WR_CMD(1,0x31,0x0444);
    LCD_WR_CMD(1,0x32,0x0555);
    LCD_WR_CMD(1,0x33,0x0444);
    LCD_WR_CMD(1,0x34,0x0333);
    LCD_WR_CMD(1,0x35,0x0333);
    LCD_WR_CMD(1,0x36,0x0333);
    LCD_WR_CMD(1,0x37,0x0333);
    LCD_WR_CMD(1,0x38,0x0444);
    LCD_WR_CMD(1,0x39,0x0555);
    LCD_WR_CMD(1,0x3A,0x0666);
    LCD_WR_CMD(1,0x3B,0x0666);
    LCD_WR_CMD(1,0x3C,0x0777);
    LCD_WR_CMD(1,0x3D,0x0777);
    LCD_WR_CMD(1,0x3E,0x0777);
    LCD_WR_CMD(1,0x3F,0x0777);
    LCD_WR_CMD(1,0x40,0x0777);
    LCD_WR_CMD(1,0x41,0x0777);
    LCD_WR_CMD(1,0x42,0x0777);
    LCD_WR_CMD(1,0x43,0x0777);
    LCD_WR_CMD(1,0x44,0x0777);
    LCD_WR_CMD(1,0x45,0x0777);
    LCD_WR_CMD(1,0x46,0x0777);
    LCD_WR_CMD(1,0x47,0x0777);
    LCD_WR_CMD(1,0x48,0x0777);
    LCD_WR_CMD(1,0x49,0x0777);
    LCD_WR_CMD(1,0x4A,0x0777);
    LCD_WR_CMD(1,0x4B,0x0777);
    LCD_WR_CMD(1,0x4C,0x0777);
    LCD_WR_CMD(1,0x4D,0x0666);
    LCD_WR_CMD(1,0x4E,0x0666);
    LCD_WR_CMD(1,0x4F,0x0666);

    LCD_WR_CMD(0,0x00,0x04);	//扫描方向控制
    LCD_WR_CMD(0,0x01,0x07);	//扫描方向控制

    LCD_WR_CMD(0,0x02,0x00);	//X
    LCD_WR_CMD(1,0x03,0x0000);	//Y

    //面板大小设置
    LCD_WR_CMD(0,0x04,0xEF);	//结束列数(0~239)
    LCD_WR_CMD(1,0x05,0x013F);	//结束行数(0~319)

    //窗口设置
    LCD_WR_CMD(0,0x06,0x00);	//水平起始位置
    LCD_WR_CMD(1,0x07,0x0000);	//垂直起始位置
    LCD_WR_CMD(0,0x08,0xEF);	//水平结束位置
    LCD_WR_CMD(1,0x09,0x013F);	//垂直结束位置

    LCD_WR_CMD(0,0x0A,0x00);
    LCD_WR_CMD(0,0x0B,0x00);
    LCD_WR_CMD(0,0x0C,0x00);
    LCD_WR_CMD(0,0x14,0x00);
    LCD_WR_CMD(0,0x15,0x00);
    LCD_WR_CMD(0,0x16,0x00);
    LCD_WR_CMD(1,0x17,0x01FF);
    LCD_WR_CMD(1,0x18,0x01FF);
    LCD_WR_CMD(0,0x13,0x00);
    LCD_WR_CMD(1,0x19,0x01FF);
    LCD_WR_CMD(1,0x1B,0x01FF);
    LCD_WR_CMD(1,0x1C,0x01FF);
    LCD_WR_CMD(1,0x1A,0x01FF);
    LCD_WR_CMD(0,0x1D,0x0E);
    LCD_WR_CMD(0,0x10,0x06);		//开显示
    LCD_WR_REG(0x0E);
}
