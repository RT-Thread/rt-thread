/******************************************************************************************************************************************
* 文件名称: SWM341_sfc.c
* 功能说明: SWM341单片机的SFC（Serial Flash Controller）模块驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.1.0      2017年10月25日
* 升级记录:
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/
#include "SWM341.h"
#include "SWM341_sfc.h"


/******************************************************************************************************************************************
* 函数名称: SFC_Init()
* 功能说明: SFC（Serial Flash Controller）初始化
* 输    入: SFC_InitStructure * initStruct    SFC初始化配置值
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SFC_Init(SFC_InitStructure * initStruct)
{
    SYS->CLKEN1 |= (1 << SYS_CLKEN1_SFC_Pos);

    *((__IO uint32_t *)((uint32_t )&SFC->CFG + 0x3F4)) = 7;

    SFC->CFG &= ~(SFC_CFG_CLKDIV_Msk | SFC_CFG_DATA4L_RD_Msk | SFC_CFG_DATA4L_PP_Msk);
    SFC->CFG |= (initStruct->ClkDiv << SFC_CFG_CLKDIV_Pos) |
                (initStruct->Width_Read << SFC_CFG_DATA4L_RD_Pos) |
                (initStruct->Width_PageProgram << SFC_CFG_DATA4L_PP_Pos);

    SFC->CFG |= (1 << SFC_CFG_CMDWREN_Pos);
    SFC->CMDAHB &= ~(SFC_CMDAHB_READ_Msk | SFC_CMDAHB_PP_Msk);
    SFC->CMDAHB |= (initStruct->Cmd_Read << SFC_CMDAHB_READ_Pos) |
                   (initStruct->Cmd_PageProgram << SFC_CMDAHB_PP_Pos);
    SFC->CFG &= ~(1 << SFC_CFG_CMDWREN_Pos);

    SFC->TIM &= ~(SFC_TIM_WIP_CHK_ITV_Msk | SFC_TIM_WIP_CHK_LMT_Msk);
    SFC->TIM |= ((CyclesPerUs / 10) << SFC_TIM_WIP_CHK_ITV_Pos) |   //2048 * (CyclesPerUs / 10) / CyclesPerUs us = 0.2 ms
                (255 << SFC_TIM_WIP_CHK_LMT_Pos);

    if((initStruct->Width_Read == SFC_RDWIDTH_4) || (initStruct->Width_PageProgram == SFC_PPWIDTH_4))
    {
        if(SFC_QuadState() == 0)
            SFC_QuadSwitch(1);
    }
}

/******************************************************************************************************************************************
* 函数名称: SFC_ReadJEDEC()
* 功能说明: 读取 JEDEC ID
* 输    入: 无
* 输    出: uint32_t          JEDEC ID
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SFC_ReadJEDEC(void)
{
    SFC->CFG &= ~SFC_CFG_CMDTYPE_Msk;
    SFC->CFG |= (1 << SFC_CFG_CMDWREN_Pos) |
                (2 << SFC_CFG_CMDTYPE_Pos);
    SFC->CMD = SFC_CMD_READ_JEDEC;

    SFC->GO = 1;
    __DSB(); __ISB();
    while(SFC->GO) __NOP();

    return SFC->DATA;
}

/******************************************************************************************************************************************
* 函数名称: SFC_Erase()
* 功能说明: SPI Flash扇区擦除，每个扇区4K字节
* 输    入: uint32_t addr     要擦除扇区的地址，必须4K对齐，即addr%4096 == 0
*           uint8_t wait        1 等待 Flash 完成擦除操作后再返回   0 发出擦除命令后立即返回
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SFC_Erase(uint32_t addr, uint8_t wait)
{
    SFC_EraseEx(addr, SFC_CMD_ERASE_SECTOR, wait);
}

/******************************************************************************************************************************************
* 函数名称: SFC_EraseEx()
* 功能说明: SPI Flash擦除，通过提供不同的命令码支持片擦、块擦、扇区擦
* 输    入: uint32_t addr     要擦除的块的地址，当 addr == 0xFFFFFFFF 时，执行片擦
*           uint8_t cmd         擦除命令码，有些SPI Flash支持多种大小的块的擦除，不同块大大小使用不同命令码
*           uint8_t wait        1 等待 Flash 完成擦除操作后再返回   0 发出擦除命令后立即返回
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SFC_EraseEx(uint32_t addr, uint8_t cmd, uint8_t wait)
{
    uint8_t type = (addr == 0xFFFFFFFF) ? 5 : 7;

    SFC->ADDR = addr;

    SFC->CFG &= ~SFC_CFG_CMDTYPE_Msk;
    SFC->CFG |= (1 << SFC_CFG_WREN_Pos) |
                (1 << SFC_CFG_CMDWREN_Pos) |
                (type << SFC_CFG_CMDTYPE_Pos);
    SFC->CMD = cmd;

    SFC->GO = 1;
    __DSB(); __ISB();
    while(SFC->GO) __NOP();

    SFC->CFG &= ~SFC_CFG_WREN_Msk;

    if(wait)
        while(SFC_FlashBusy()) __NOP();
}

/******************************************************************************************************************************************
* 函数名称: SFC_Write()
* 功能说明: SPI Flash数据写入
* 输    入: uint32_t addr     数据要写入到Flash中的地址，字对齐
*           uint32_t buff[]     要写入Flash中的数据
*           uint32_t cnt        要写的数据的个数，以字为单位，最大64
* 输    出: 无
* 注意事项: 要写入的数据必须全部在同一页内，即addr/256 == (addr+(cnt-1)*4)/256
*           当 cnt > 4 时，LCD_DCLK 输出可能出现间断（|__|￣|__|￣|__|￣￣￣￣￣￣￣￣|__|￣|__|￣|__|），这种情况下有些屏幕会显示异常，遇
*           到这种情况，可通过以 cnt = 4 多次调用 SFC_Write() 解决
******************************************************************************************************************************************/
void SFC_Write(uint32_t addr, uint32_t buff[], uint32_t cnt)
{
    SFC->CFG |= (1 << SFC_CFG_WREN_Pos);
    for(int i = 0; i < cnt; i++)
        *((volatile unsigned int *)(0x70000000+addr+i*4)) = buff[i];

    while(SFC->SR & SFC_SR_BUSY_Msk) __NOP();
    SFC->CFG &= ~SFC_CFG_WREN_Msk;
}


#define IOSPI_CS_Low()      GPIO_ClrBit(GPIOD, PIN6); __NOP(); __NOP(); __NOP(); __NOP()
#define IOSPI_CS_High()     __NOP(); __NOP(); __NOP(); __NOP(); GPIO_SetBit(GPIOD, PIN6)
#define IOSPI_CLK_Low()     GPIO_ClrBit(GPIOD, PIN5); __NOP(); __NOP()
#define IOSPI_CLK_High()    __NOP(); __NOP(); GPIO_SetBit(GPIOD, PIN5)
#define IOSPI_MOSI_Low()    GPIO_ClrBit(GPIOD, PIN8)
#define IOSPI_MOSI_High()   GPIO_SetBit(GPIOD, PIN8)
#define IOSPI_MISO_Value()  GPIO_GetBit(GPIOD, PIN7)

static uint8_t IOSPI_ReadWrite(uint8_t data)
{
    uint8_t val = 0;

    for(int i = 0; i < 8; i++)
    {
        IOSPI_CLK_Low();

        if(data & (1 << (7 - i)))
            IOSPI_MOSI_High();
        else
            IOSPI_MOSI_Low();

        IOSPI_CLK_High();

        val = (val << 1) | IOSPI_MISO_Value();
    }

    return val;
}

/******************************************************************************************************************************************
* 函数名称: SFC_GPIOWrite()
* 功能说明: SFC 写入较慢，大量写入时，建议用 GPIO 模拟 SPI 写入
* 输    入: uint32_t addr     数据要写入到Flash中的地址，字对齐
*           uint32_t buff[]     要写入Flash中的数据
*           uint32_t cnt        要写的数据的个数，以字为单位，最大64
* 输    出: 无
* 注意事项: 执行此函数前需要将相应引脚切到 GPIO 功能，使用完后再次将相应引脚切换回 SFC 功能，以便使用 SFC 擦除、读取功能
******************************************************************************************************************************************/
void SFC_GPIOWrite(uint32_t addr, uint32_t buff[], uint32_t cnt)
{
    IOSPI_CS_Low();
    IOSPI_ReadWrite(SFC_CMD_WRITE_ENABLE);
    IOSPI_CS_High();

    IOSPI_CS_Low();
    IOSPI_ReadWrite(SFC_CMD_PAGE_PROGRAM);
    IOSPI_ReadWrite(addr >> 16);
    IOSPI_ReadWrite(addr >>  8);
    IOSPI_ReadWrite(addr);

    for(int i = 0; i < cnt * 4; i++)
    {
        IOSPI_ReadWrite(((uint8_t *)buff)[i]);
    }
    IOSPI_CS_High();

    int busy;
    do {
        IOSPI_CS_Low();
        IOSPI_ReadWrite(SFC_CMD_READ_STATUS_REG1);
        busy = IOSPI_ReadWrite(0xFF) & (1 << SFC_STATUS_REG_BUSY_Pos);
        IOSPI_CS_High();
    } while(busy);
}


/******************************************************************************************************************************************
* 函数名称: SFC_Read()
* 功能说明: SPI Flash数据读取
* 输    入: uint32_t addr     要读取的数据在Flash中的地址，字对齐
*           uint32_t buff[]     读取到的数据存入buff指向的内存
*           uint32_t cnt        要读取的数据的个数，以字为单位
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SFC_Read(uint32_t addr, uint32_t buff[], uint32_t cnt)
{
    for(int i = 0; i < cnt; i++)
        buff[i] = *((volatile unsigned int *)(0x70000000+addr+i*4));
}


/******************************************************************************************************************************************
* 函数名称: SFC_ReadStatusReg()
* 功能说明: SPI Flash读取状态寄存器
* 输    入: uint8_t cmd           读取使用的命令码
* 输    出: uint8_t               读到的状态寄存器值
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t SFC_ReadStatusReg(uint8_t cmd)
{
    SFC->CFG &= ~SFC_CFG_CMDTYPE_Msk;
    SFC->CFG |= (1 << SFC_CFG_CMDWREN_Pos) |
                (1 << SFC_CFG_CMDTYPE_Pos);
    SFC->CMD = cmd;

    SFC->GO = 1;
    __DSB(); __ISB();
    while(SFC->GO) __NOP();

    return SFC->DATA;
}


/******************************************************************************************************************************************
* 函数名称: SFC_WriteStatusReg()
* 功能说明: SPI Flash写入状态寄存器
* 输    入: uint8_t cmd           写入使用的命令码
*           uint16_t reg        要写入的状态寄存器值
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SFC_WriteStatusReg(uint8_t cmd, uint16_t reg)
{
    SFC->CFG &= ~SFC_CFG_CMDTYPE_Msk;
    SFC->CFG |= (1 << SFC_CFG_WREN_Pos) |
                (1 << SFC_CFG_CMDWREN_Pos) |
                (6 << SFC_CFG_CMDTYPE_Pos);
    SFC->CMD = cmd;

    SFC->DATA = reg;

    SFC->GO = 1;
    __DSB(); __ISB();
    while(SFC->GO) __NOP();
}


/******************************************************************************************************************************************
* 函数名称: SFC_QuadSwitch()
* 功能说明: SPI Flash Quad模式开关
* 输    入: uint8_t on            1 开启 Quad 模式   0 关闭 Quad 模式
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SFC_QuadSwitch(uint8_t on)
{
    uint16_t reg = (SFC_ReadStatusReg(SFC_CMD_READ_STATUS_REG2) << 8) |
                   (SFC_ReadStatusReg(SFC_CMD_READ_STATUS_REG1) << 0);

    if(on)
        reg |= (1 << SFC_STATUS_REG_QUAD_Pos);
    else
        reg &=~(1 << SFC_STATUS_REG_QUAD_Pos);

    SFC_WriteStatusReg(SFC_CMD_WRITE_STATUS_REG1, reg);
}


/******************************************************************************************************************************************
* 函数名称: SFC_QuadState()
* 功能说明: SPI Flash Quad模式开关状态查询
* 输    入: 无
* 输    出:                   1 Quad 模式开启    0 Quad 模式关闭
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t SFC_QuadState(void)
{
    uint8_t reg = SFC_ReadStatusReg(SFC_CMD_READ_STATUS_REG2);

    if(reg & (1 << (SFC_STATUS_REG_QUAD_Pos - 8)))
        return 1;
    else
        return 0;
}

/******************************************************************************************************************************************
* 函数名称: SFC_FlashBusy()
* 功能说明: SPI Flash Page Program、Sector Erase、Block Erase、Chip Erase 忙查询
* 输    入: 无
* 输    出:                   1 Flash 正在执行 Erase/Write 操作   0 Flash 已完成 Erase/Write 操作
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t SFC_FlashBusy(void)
{
    uint8_t reg = SFC_ReadStatusReg(SFC_CMD_READ_STATUS_REG1);

    if(reg & (1 << SFC_STATUS_REG_BUSY_Pos))
        return 1;
    else
        return 0;
}
