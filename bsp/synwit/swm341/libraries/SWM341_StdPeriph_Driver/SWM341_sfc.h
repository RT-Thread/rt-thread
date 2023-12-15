#ifndef __SWM341_SFC_H__
#define __SWM341_SFC_H__


typedef struct {
    uint8_t ClkDiv;             //SPI_SCLK是系统时钟的几分频，取值：SFC_CLKDIV_1、SFC_CLKDIV_2、SFC_CLKDIV_4、SFC_CLKDIV_8
    uint8_t Cmd_Read;           //读取SPI Flash用的指令码
    uint8_t Width_Read;         //读取SPI Flash时数据线位数，取值SFC_RDWIDTH_1、SFC_RDWIDTH_2、SFC_RDWIDTH_4
    uint8_t Cmd_PageProgram;    //页编程SPI Flash用的指令码
    uint8_t Width_PageProgram;  //页编程SPI Flash时数据线位数，取值SFC_PPWIDTH_1、SFC_PPWIDTH_4
} SFC_InitStructure;


#define SFC_CLKDIV_1    0
#define SFC_CLKDIV_2    1
#define SFC_CLKDIV_4    2
#define SFC_CLKDIV_8    3

#define SFC_RDWIDTH_1   0
#define SFC_RDWIDTH_2   1
#define SFC_RDWIDTH_4   2

#define SFC_PPWIDTH_1   0
#define SFC_PPWIDTH_4   1


#define SFC_CMD_READ_JEDEC          0x9F
#define SFC_CMD_ERASE_CHIP          0x60
#define SFC_CMD_WRITE_ENABLE        0x06
#define SFC_CMD_PAGE_PROGRAM        0x02
#define SFC_CMD_ERASE_SECTOR        0x20
#define SFC_CMD_ERASE_BLOCK32KB     0x52
#define SFC_CMD_ERASE_BLOCK64KB     0xD8    //W25Q32
#define SFC_CMD_READ_STATUS_REG1    0x05
#define SFC_CMD_READ_STATUS_REG2    0x35
#define SFC_CMD_READ_STATUS_REG3    0x15
#define SFC_CMD_WRITE_STATUS_REG1   0x01
#define SFC_CMD_WRITE_STATUS_REG2   0x31
#define SFC_CMD_WRITE_STATUS_REG3   0x11


#define SFC_STATUS_REG_BUSY_Pos     0
#define SFC_STATUS_REG_QUAD_Pos     9


void SFC_Init(SFC_InitStructure * initStruct);
uint32_t SFC_ReadJEDEC(void);
void SFC_Erase(uint32_t addr, uint8_t wait);
void SFC_EraseEx(uint32_t addr, uint8_t cmd, uint8_t wait);
void SFC_Write(uint32_t addr, uint32_t buff[], uint32_t cnt);
void SFC_GPIOWrite(uint32_t addr, uint32_t buff[], uint32_t cnt);
void SFC_Read(uint32_t addr, uint32_t buff[], uint32_t cnt);


uint8_t SFC_ReadStatusReg(uint8_t cmd);
void SFC_WriteStatusReg(uint8_t cmd, uint16_t reg);
void SFC_QuadSwitch(uint8_t on);
uint8_t SFC_QuadState(void);
uint8_t SFC_FlashBusy(void);


#endif //__SWM341_SFC_H__
