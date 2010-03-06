#ifndef ILI9325_H_INCLUDED
#define ILI9325_H_INCLUDED

extern void ili9325_Initializtion(void);
extern void ili9325_SetCursor(u16 x,u16 y);
extern void ili9325_Clear(u16 Color);

extern unsigned short ili9325_BGR2RGB(unsigned short c);

extern void ili9325_WriteRAM_Prepare(void);
extern void ili9325_WriteRAM(u16 RGB_Code);
extern unsigned short ili9325_ReadGRAM(unsigned short x,unsigned short y);
extern void ili9325_WriteReg(u8 LCD_Reg,u16 LCD_RegValue);

/* If LCD Display in wrong dirction uncomment this option*/
#define _ILI_REVERSE_DIRECTION_

/* LCD is connected to the FSMC_Bank1_NOR/SRAM2 and NE2 is used as ship select signal */
/* RS <==> A2 */
#define ili9325_REG              (*((volatile unsigned short *) 0x64000000)) /* RS = 0 */
#define ili9325_RAM              (*((volatile unsigned short *) 0x64000008)) /* RS = 1 */

#endif
