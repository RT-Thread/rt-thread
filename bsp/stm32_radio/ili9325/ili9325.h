#ifndef ILI9325_H_INCLUDED
#define ILI9325_H_INCLUDED

extern void ili9325_Initializtion(void);
extern void ili9325_SetCursor(u16 x,u16 y);
extern void ili9325_Clear(u16 Color);

extern unsigned short ili9325_BGR2RGB(unsigned short c);

extern void LCD_WriteRAM_Prepare(void);
extern void LCD_WriteRAM(u16 RGB_Code);
extern unsigned short ili9325_ReadGRAM(unsigned short x,unsigned short y);
extern void LCD_WriteReg(u8 LCD_Reg,u16 LCD_RegValue);

typedef struct
{
    vu16 LCD_REG;  /* 0x00 */
    vu16 reserve1; /* 0x02 */
    vu16 reserve2; /* 0x04 */
    vu16 reserve3; /* 0x06 */
    vu16 LCD_RAM;  /* 0x08 */
} LCD_ili9325_TypeDef;

/* LCD is connected to the FSMC_Bank1_NOR/SRAM2 and NE2 is used as ship select signal */
#define LCD_ili9325_BASE    ((u32)(0x60000000 | 0x04000000))
#define LCD                 ((LCD_ili9325_TypeDef *) LCD_ili9325_BASE)

#endif
