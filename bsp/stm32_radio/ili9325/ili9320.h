#ifndef ILI9320_H_INCLUDED
#define ILI9320_H_INCLUDED

extern void ili9320_Initializtion(void);
extern void ili9320_SetCursor(u16 x,u16 y);
extern void ili9320_Clear(u16 Color);

extern u16 ili9320_BGR2RGB(u16 c);

extern void LCD_WriteRAM_Prepare(void);
extern void LCD_WriteRAM(u16 RGB_Code);
extern u16 LCD_ReadRAM(void);
extern void LCD_WriteReg(u8 LCD_Reg,u16 LCD_RegValue);

#endif
