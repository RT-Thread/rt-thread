/**
  ******************************************************************************
  * @file    system_target.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   system source file.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "target.h"



/**
  * @brief  Setup the microcontroller system
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
  volatile uint32_t i;
  uint32_t tmp[3];

  ANA->REG0 = 0x30;
  ANA->REG4 = 0x04;
  ANA->REG7 = 0x84;
  ANA->REGA = 0x02;
  while (ANA->ADCCTRL0 & ANA_ADCCTRL0_MTRIG);
  ANA->ADCCTRL0 = 0x300000;
  ANA->ADCCTRL1 = 0xC2;
  ANA->ADCCTRL2 = 0x8014;
  LCD->CTRL = 0x84;

  tmp[0] = 0x599A599A;
  tmp[1] = 0x78000000;
  tmp[2] = 0x80000000;
  RTC_WriteRegisters((uint32_t)&RTC->ADCUCALK, tmp, 3);
}

/**
  * @brief  Initializes registers.
  * @param  None
  * @retval None
  */
void SystemUpdate(void)
{
  uint32_t tmp[3];
  
  ANA->REG0 &= ~0xCE;
  ANA->REG0 |= 0x30;
  ANA->REG1 &= ~0x7F;
  ANA->REG2 &= ~0xC0;
  ANA->REG3 &= ~0x01;
  ANA->REG4 |= 0x04;
  ANA->REG4 &= ~0xFB;
  ANA->REG5 &= ~0xB0;
  ANA->REG6 &= ~0x3E;
  ANA->REG7 |= 0x84;
  ANA->REG7 &= ~0x7B;
  ANA->REG8 &= ~0x0C;
  ANA->REGA |= 0x02;
  ANA->REGA &= ~0x7D;
  
  tmp[0] = 0x599A599A;
  tmp[1] = RTC->ADCMACTL;
  tmp[1] &= ~0XFF080000;
  tmp[1] |= 0x78000000;
  tmp[2] = 0x80000000;
  RTC_WriteRegisters((uint32_t)&RTC->ADCUCALK, tmp, 3);
}

/*********************************** END OF FILE ******************************/
