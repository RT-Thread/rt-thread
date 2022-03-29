/**
  ******************************************************************************
  * @file    lib_lcd.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   LCD library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_lcd.h"
#include "lib_LoadNVR.h"

//registers default reset values
#define LCD_CTRL_RSTValue           0
#define LCD_CTRL2_RSTValue          0
#define LCD_SEGCTRL0_RSTValue       0
#define LCD_SEGCTRL1_RSTValue       0
#define LCD_SEGCTRL2_RSTValue       0

/* COMx IO */
const LCD_COMIO lcd_comio[] = 
{
  {&GPIOD->OEN, GPIO_Pin_0}, 
  {&GPIOD->OEN, GPIO_Pin_1}, 
  {&GPIOD->OEN, GPIO_Pin_2}, 
  {&GPIOD->OEN, GPIO_Pin_3}, 
  {&GPIOD->OEN, GPIO_Pin_4}, 
  {&GPIOD->OEN, GPIO_Pin_5}, 
  {&GPIOD->OEN, GPIO_Pin_6}, 
  {&GPIOD->OEN, GPIO_Pin_7}, 
};

/**
  * @brief  Initializes LCD.
  * @param  InitStruct: LCD configuration.
                Type:
                    LCD_TYPE_4COM
                    LCD_TYPE_6COM
                    LCD_TYPE_8COM
                Drv:
                    LCD_DRV_300
                    LCD_DRV_600
                    LCD_DRV_150
                    LCD_DRV_200
                FRQ:
                    LCD_FRQ_64H
                    LCD_FRQ_128H
                    LCD_FRQ_256H
                    LCD_FRQ_512H
                SWPR: Frame buffer switch period(0.5 sec * (SWPR + 1)).
                FBMODE:
                    LCD_FBMODE_BUFA
                    LCD_FBMODE_BUFAB
                    LCD_FBMODE_BUFABLANK
                BKFILL:
                    LCD_BKFILL_1
                    LCD_BKFILL_0
  * @retval None
  */
void LCD_Init(LCD_InitType *InitStruct)
{
  uint32_t tmp_reg1, tmp_reg2;

  /* Check parameters */
  assert_parameters(IS_LCD_TYPE(InitStruct->Type));
  assert_parameters(IS_LCD_DRV(InitStruct->Drv));
  assert_parameters(IS_LCD_FRQ(InitStruct->FRQ));
  assert_parameters(IS_LCD_SWPR(InitStruct->SWPR));
  assert_parameters(IS_LCD_FBMODE(InitStruct->FBMODE));
  assert_parameters(IS_LCD_BKFILL(InitStruct->BKFILL));
  
  tmp_reg1 = LCD->CTRL;
  tmp_reg2 = LCD->CTRL2;
  tmp_reg1 &= ~(LCD_CTRL_TYPE\
               |LCD_CTRL_DRV\
               |LCD_CTRL_FRQ);
  tmp_reg1 |= (InitStruct->Type\
              |InitStruct->Drv\
              |InitStruct->FRQ);
  tmp_reg2 &= ~(LCD_CTRL2_SWPR\
               |LCD_CTRL2_FBMODE\
               |LCD_CTRL2_BKFILL);
  tmp_reg2 |= ((InitStruct->SWPR << 8)\
               |InitStruct->FBMODE\
               |InitStruct->BKFILL);
  LCD->CTRL = tmp_reg1;
  LCD->CTRL2 = tmp_reg2;
}

/**
  * @brief  Fills each LCD_InitStruct member with its default value.
  * @param  LCD_InitStruct: pointer to an LCD_InitType structure which will be initialized.
  * @retval None
  */
void LCD_StructInit(LCD_InitType *LCD_InitStruct)
{
  /*--------------- Reset LCD init structure parameters values ---------------*/
  /* Initialize the BKFILL member */  
  LCD_InitStruct->BKFILL = LCD_BKFILL_0;
  /* Initialize the Drv member */  
  LCD_InitStruct->Drv = LCD_DRV_300;
  /* Initialize the FBMODE member */  
  LCD_InitStruct->FBMODE = LCD_FBMODE_BUFA;
  /* Initialize the FRQ member */  
  LCD_InitStruct->FRQ = LCD_FRQ_64H;
  /* Initialize the SWPR member */  
  LCD_InitStruct->SWPR = 0;
  /* Initialize the Type member */  
  LCD_InitStruct->Type = LCD_TYPE_4COM;
}

/**
  * @brief  Initializes the LCD registers to their default reset values.
  * @param  None
  * @retval None
  */
void LCD_DeInit(void)
{
  LCD->CTRL &= ~LCD_CTRL_EN;
    
  LCD->CTRL = LCD_CTRL_RSTValue;
  LCD->CTRL2 = LCD_CTRL2_RSTValue;
  LCD->SEGCTRL0 = LCD_SEGCTRL0_RSTValue;
  LCD->SEGCTRL1 = LCD_SEGCTRL1_RSTValue;
  LCD->SEGCTRL2 = LCD_SEGCTRL2_RSTValue;
}

/**
  * @brief  Enables or disables LCD controller.
  * @param  IOInitType: LCD SEG and COM configuration.
                SegCtrl0:
                SegCtrl1:
                    0~0xFFFFFFFF
                SegCtrl2:
                    0~0xFFFF
                COMMode:
                    LCD_TYPE_4COM
                    LCD_TYPE_6COM
                    LCD_TYPE_8COM
            NewState:
                    ENABLE
                    DISABLE
  * @retval None
  */
void LCD_Cmd(LCD_IOInitType *IOInitType, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  assert_parameters(IS_LCD_COMMOD(IOInitType->COMMode));

  if (NewState == ENABLE)
  {
    LCD->SEGCTRL0 = IOInitType->SegCtrl0;
    LCD->SEGCTRL1 = IOInitType->SegCtrl1;
    LCD->SEGCTRL2 = IOInitType->SegCtrl2;
 
    /* COMs' IO configuration : forbidden */
    *lcd_comio[0].GPIO |= lcd_comio[0].Pin;
    *(lcd_comio[0].GPIO+1) &= ~lcd_comio[0].Pin;
    *lcd_comio[1].GPIO |= lcd_comio[1].Pin;
    *(lcd_comio[1].GPIO+1) &= ~lcd_comio[1].Pin;
    *lcd_comio[2].GPIO |= lcd_comio[2].Pin;
    *(lcd_comio[2].GPIO+1) &= ~lcd_comio[2].Pin;
    *lcd_comio[3].GPIO |= lcd_comio[3].Pin;
    *(lcd_comio[3].GPIO+1) &= ~lcd_comio[3].Pin;
    if (IOInitType->COMMode & 2UL)
    {
      *lcd_comio[4].GPIO |= lcd_comio[4].Pin;
      *(lcd_comio[4].GPIO+1) &= ~lcd_comio[4].Pin;
      *lcd_comio[5].GPIO |= lcd_comio[5].Pin;
      *(lcd_comio[5].GPIO+1) &= ~lcd_comio[5].Pin;
    }
    if (IOInitType->COMMode & 4UL)
    {
      *lcd_comio[6].GPIO |= lcd_comio[6].Pin;
      *(lcd_comio[6].GPIO+1) &= ~lcd_comio[6].Pin;
      *lcd_comio[7].GPIO |= lcd_comio[7].Pin;
      *(lcd_comio[7].GPIO+1) &= ~lcd_comio[7].Pin;
    }

    /* Enable LCD */
    LCD->CTRL |= LCD_CTRL_EN;
  }
  else
  {
    /* Disable LCD */
    LCD->CTRL &= ~LCD_CTRL_EN;

    LCD->SEGCTRL0 = IOInitType->SegCtrl0;
    LCD->SEGCTRL1 = IOInitType->SegCtrl1;
    LCD->SEGCTRL2 = IOInitType->SegCtrl2;

    /* COMs' IO configuration : ouput low */
    *(lcd_comio[0].GPIO+2) &= ~lcd_comio[0].Pin;
    *lcd_comio[0].GPIO &= ~lcd_comio[0].Pin;
    *(lcd_comio[1].GPIO+2) &= ~lcd_comio[1].Pin;
    *lcd_comio[1].GPIO &= ~lcd_comio[1].Pin;
    *(lcd_comio[2].GPIO+2) &= ~lcd_comio[2].Pin;
    *lcd_comio[2].GPIO &= ~lcd_comio[2].Pin;
    *(lcd_comio[3].GPIO+2) &= ~lcd_comio[3].Pin;
    *lcd_comio[3].GPIO &= ~lcd_comio[3].Pin;
    if (IOInitType->COMMode & 2UL)
    {
      *(lcd_comio[4].GPIO+2) &= ~lcd_comio[4].Pin;
      *lcd_comio[4].GPIO &= ~lcd_comio[4].Pin;
      *(lcd_comio[5].GPIO+2) &= ~lcd_comio[5].Pin;
      *lcd_comio[5].GPIO &= ~lcd_comio[5].Pin;
    }
    if (IOInitType->COMMode & 4UL)
    {
      *(lcd_comio[6].GPIO+2) &= ~lcd_comio[6].Pin;
      *lcd_comio[6].GPIO &= ~lcd_comio[6].Pin;
      *(lcd_comio[7].GPIO+2) &= ~lcd_comio[7].Pin;
      *lcd_comio[7].GPIO &= ~lcd_comio[7].Pin;
    }
  }
}

/**
  * @brief  Configures LCD BIAS mode.
  * @param  BiasSelection:
                LCD_BMODE_DIV3
                LCD_BMODE_DIV4
  * @retval None
  */
void LCD_BiasModeConfig(uint32_t BiasSelection)
{
  uint32_t tmp;
  
  assert_parameters(IS_LCD_BMODE(BiasSelection));
  
  tmp = ANA->REG6;
  tmp &= ~ANA_REG6_LCDBMODE;
  tmp |= BiasSelection;
  ANA->REG6 = tmp;
}

/*********************************** END OF FILE ******************************/
