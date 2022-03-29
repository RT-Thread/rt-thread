/**
  ******************************************************************************
  * @file    lib_lcd.c 
  * @author  Application Team
  * @version V4.5.0
  * @date    2019-05-14
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
const LCD_SEGIO lcd_comio[] = 
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

/* SEGx IO */
const LCD_SEGIO lcd_segio[] = 
{                             /**************************/
                              /*  SEG  |  GPIO  |  Pin  */
  {&GPIOD->OEN, GPIO_Pin_4},  /*   0        D       4   */
  {&GPIOD->OEN, GPIO_Pin_5},  /*   1        D       5   */
  {&GPIOD->OEN, GPIO_Pin_6},  /*   2        D       6   */
  {&GPIOD->OEN, GPIO_Pin_7},  /*   3        D       7   */
  {&GPIOD->OEN, GPIO_Pin_8},  /*   4        D       8   */
  {&GPIOD->OEN, GPIO_Pin_9},  /*   5        D       9   */
  {&GPIOD->OEN, GPIO_Pin_10}, /*   6        D       10  */
  {&GPIOD->OEN, GPIO_Pin_11}, /*   7        D       11  */
  {&GPIOD->OEN, GPIO_Pin_12}, /*   8        D       12  */
  {&GPIOD->OEN, GPIO_Pin_13}, /*   9        D       13  */
  {&GPIOD->OEN, GPIO_Pin_14}, /*   10       D       14  */
  {&GPIOD->OEN, GPIO_Pin_15}, /*   11       D       15  */
  {&GPIOB->OEN, GPIO_Pin_4},  /*   12       B       4   */
  {&GPIOA->OEN, GPIO_Pin_14}, /*   13       A       14  */
  {&GPIOB->OEN, GPIO_Pin_5},  /*   14       B       5   */
  {&GPIOA->OEN, GPIO_Pin_15}, /*   15       A       15  */
  {&GPIOC->OEN, GPIO_Pin_0},  /*   16       C       0   */
  {&GPIOC->OEN, GPIO_Pin_1},  /*   17       C       1   */
  {&GPIOC->OEN, GPIO_Pin_2},  /*   18       C       2   */
  {&GPIOC->OEN, GPIO_Pin_3},  /*   19       C       3   */
  {&GPIOC->OEN, GPIO_Pin_4},  /*   20       C       4   */
  {&GPIOC->OEN, GPIO_Pin_5},  /*   21       C       5   */
  {&GPIOC->OEN, GPIO_Pin_6},  /*   22       C       6   */
  {&GPIOC->OEN, GPIO_Pin_7},  /*   23       C       7   */
  {&GPIOC->OEN, GPIO_Pin_8},  /*   24       C       8   */
  {&GPIOC->OEN, GPIO_Pin_9},  /*   25       C       9   */
  {&GPIOC->OEN, GPIO_Pin_10}, /*   26       C       10  */
  {&GPIOC->OEN, GPIO_Pin_11}, /*   27       C       11  */
  {&GPIOC->OEN, GPIO_Pin_12}, /*   28       C       12  */
  {&GPIOC->OEN, GPIO_Pin_13}, /*   29       C       13  */
  {&GPIOC->OEN, GPIO_Pin_14}, /*   30       C       14  */
  {&GPIOC->OEN, GPIO_Pin_15}, /*   31       C       15  */
  {&GPIOE->OEN, GPIO_Pin_10}, /*   32       E       10  */
  {&GPIOE->OEN, GPIO_Pin_11}, /*   33       E       11  */
  {&GPIOE->OEN, GPIO_Pin_12}, /*   34       E       12  */
  {&GPIOB->OEN, GPIO_Pin_8},  /*   35       B       8   */
  {&GPIOB->OEN, GPIO_Pin_9},  /*   36       B       9   */
  {&GPIOB->OEN, GPIO_Pin_10}, /*   37       B       10  */
  {&GPIOB->OEN, GPIO_Pin_11}, /*   38       B       11  */
  {&GPIOB->OEN, GPIO_Pin_12}, /*   39       B       12  */
  {&GPIOB->OEN, GPIO_Pin_13}, /*   40       B       13  */
  {&GPIOB->OEN, GPIO_Pin_14}, /*   41       B       14  */
  {&GPIOB->OEN, GPIO_Pin_15}, /*   42       B       15  */
  {&GPIOB->OEN, GPIO_Pin_0},  /*   43       B       0   */
  {&GPIOB->OEN, GPIO_Pin_6},  /*   44       B       6   */
  {&GPIOB->OEN, GPIO_Pin_1},  /*   45       B       1   */
  {&GPIOB->OEN, GPIO_Pin_7},  /*   46       B       7   */
  {&GPIOA->OEN, GPIO_Pin_11}, /*   47       A       11  */
  {&GPIOA->OEN, GPIO_Pin_10}, /*   48       A       10  */
  {&GPIOA->OEN, GPIO_Pin_9},  /*   49       A       9   */
  {&GPIOA->OEN, GPIO_Pin_8},  /*   50       A       8   */
  {&GPIOA->OEN, GPIO_Pin_3},  /*   51       A       3   */
  {&GPIOA->OEN, GPIO_Pin_2},  /*   52       A       2   */
  {&GPIOA->OEN, GPIO_Pin_1},  /*   53       A       1   */
  {&GPIOA->OEN, GPIO_Pin_0},  /*   54       A       0   */
  {&GPIOE->OEN, GPIO_Pin_13}, /*   55       E       13  */
  {&GPIOE->OEN, GPIO_Pin_14}, /*   56       E       14  */
  {&GPIOE->OEN, GPIO_Pin_15}, /*   57       E       15  */
  {&GPIOE->OEN, GPIO_Pin_9},  /*   58       E       9   */
  {&GPIOE->OEN, GPIO_Pin_8},  /*   59       E       8   */
  {&GPIOE->OEN, GPIO_Pin_7},  /*   60       E       7   */
  {&GPIOE->OEN, GPIO_Pin_6},  /*   61       E       6   */
  {&GPIOE->OEN, GPIO_Pin_5},  /*   62       E       5   */
  {&GPIOE->OEN, GPIO_Pin_4},  /*   63       E       4   */
  {&GPIOE->OEN, 0},           /*   64       NC      NC  */
  {&GPIOE->OEN, 0},           /*   65       NC      NC  */
  {&GPIOA->OEN, GPIO_Pin_4},  /*   66       A       4   */
  {&GPIOA->OEN, GPIO_Pin_5},  /*   67       A       5   */
  {&GPIOA->OEN, GPIO_Pin_6},  /*   68       A       6   */
  {&GPIOA->OEN, GPIO_Pin_7},  /*   69       A       7   */
  {&GPIOB->OEN, GPIO_Pin_2},  /*   70       B       2   */
  {&GPIOA->OEN, GPIO_Pin_12}, /*   71       A       12  */
  {&GPIOB->OEN, GPIO_Pin_3},  /*   72       B       3   */
  {&GPIOA->OEN, GPIO_Pin_13}, /*   73       A       13  */
  {&GPIOE->OEN, GPIO_Pin_0},  /*   74       E       0   */
  {&GPIOE->OEN, GPIO_Pin_1},  /*   75       E       1   */
  {&GPIOE->OEN, GPIO_Pin_2},  /*   76       E       2   */
  {&GPIOE->OEN, GPIO_Pin_3},  /*   77       E       3   */
  {&GPIOE->OEN, 0},           /*   78       NC      NC  */
  {&GPIOE->OEN, 0}            /*   79       NC      NC  */
};

/**
  * @brief  LCD initialization.
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
  * @brief  LCD controller enable.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void LCD_Cmd(uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    LCD->CTRL |= LCD_CTRL_EN;
  }
  else
  {
    LCD->CTRL &= ~LCD_CTRL_EN;
  }
}

/**
  * @brief  Configure LCD COMs'/SEGs' IOs.
  * @param  ComMode:
                LCD_COMMOD_4COM : Control the COM0~3 IO configuration
                LCD_COMMOD_6COM : Control the COM0~5 IO configuration
                LCD_COMMOD_8COM : Control the COM0~7 IO configuration
  * @param  SEGVal0 SEGVal1 SEGVal2 : Each bit control the SEGs' IO configuration
  * @param  NewState:
                ENABLE  : The corresponded IOs be set to forbidden mode(disable output/disable input), enable SEGs' output and LCD function.
                DISABLE : LCD be disabled and the corresponded IOs be set to output(low) mode.
  * @retval None
  */
void LCD_IOConfig(uint32_t ComMode, uint32_t SEGVal0, uint32_t SEGVal1, uint16_t SEGVal2, uint32_t NewState)
{
  uint32_t position, segcurrent;
  
  /* Check parameters */
  assert_parameters(IS_LCD_COMMOD(ComMode));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState == DISABLE)
  {
    /* Disable LCD */
    LCD->CTRL &= ~LCD_CTRL_EN;

    /* COMs' IO configuration : ouput low */
    *(lcd_comio[0].GPIO+2) &= ~lcd_comio[0].Pin;
    *lcd_comio[0].GPIO &= ~lcd_comio[0].Pin;
    *(lcd_comio[1].GPIO+2) &= ~lcd_comio[1].Pin;
    *lcd_comio[1].GPIO &= ~lcd_comio[1].Pin;
    *(lcd_comio[2].GPIO+2) &= ~lcd_comio[2].Pin;
    *lcd_comio[2].GPIO &= ~lcd_comio[2].Pin;
    *(lcd_comio[3].GPIO+2) &= ~lcd_comio[3].Pin;
    *lcd_comio[3].GPIO &= ~lcd_comio[3].Pin;
    if (ComMode & 2UL)
    {
      *(lcd_comio[4].GPIO+2) &= ~lcd_comio[4].Pin;
      *lcd_comio[4].GPIO &= ~lcd_comio[4].Pin;
      *(lcd_comio[5].GPIO+2) &= ~lcd_comio[5].Pin;
      *lcd_comio[5].GPIO &= ~lcd_comio[5].Pin;
    }
    if (ComMode & 4UL)
    {
      *(lcd_comio[6].GPIO+2) &= ~lcd_comio[6].Pin;
      *lcd_comio[6].GPIO &= ~lcd_comio[6].Pin;
      *(lcd_comio[7].GPIO+2) &= ~lcd_comio[7].Pin;
      *lcd_comio[7].GPIO &= ~lcd_comio[7].Pin;
    }

    /* SEG0~31 IO Configuration : ouput low */
    position = 0;
    while ((SEGVal0 >> position) != 0UL)
    {
      segcurrent = SEGVal0 & (1U << position);
      if (segcurrent)
      {
        *(lcd_segio[position].GPIO + 2) &= ~lcd_segio[position].Pin; 
        *lcd_segio[position].GPIO &= ~lcd_segio[position].Pin;
      }
      position++;
    }
    /* SEG32~63 IO Configuration : ouput low */
    position = 0;
    while ((SEGVal1 >> position) != 0UL)
    {
      segcurrent = SEGVal1 & (1U << position);
      if (segcurrent)
      {
        *(lcd_segio[position + 32].GPIO + 2) &= ~lcd_segio[position + 32].Pin; 
        *lcd_segio[position + 32].GPIO &= ~lcd_segio[position + 32].Pin;
      }
      position++;
    }
    /* SEG64~79 IO Configuration : ouput low  */
    position = 0;
    while ((SEGVal2 >> position) != 0UL)
    {
      segcurrent = SEGVal2 & (1U << position);
      if (segcurrent)
      {
        *(lcd_segio[position + 64].GPIO + 2) &= ~lcd_segio[position + 64].Pin; 
        *lcd_segio[position + 64].GPIO &= ~lcd_segio[position + 64].Pin;
      }
      position++;
    }    
  }
  else
  {
    /* COMs' IO configuration : forbidden */
    *lcd_comio[0].GPIO |= lcd_comio[0].Pin;
    *(lcd_comio[0].GPIO+1) &= ~lcd_comio[0].Pin;
    *lcd_comio[1].GPIO |= lcd_comio[1].Pin;
    *(lcd_comio[1].GPIO+1) &= ~lcd_comio[1].Pin;
    *lcd_comio[2].GPIO |= lcd_comio[2].Pin;
    *(lcd_comio[2].GPIO+1) &= ~lcd_comio[2].Pin;
    *lcd_comio[3].GPIO |= lcd_comio[3].Pin;
    *(lcd_comio[3].GPIO+1) &= ~lcd_comio[3].Pin;
    if (ComMode & 2UL)
    {
      *lcd_comio[4].GPIO |= lcd_comio[4].Pin;
      *(lcd_comio[4].GPIO+1) &= ~lcd_comio[4].Pin;
      *lcd_comio[5].GPIO |= lcd_comio[5].Pin;
      *(lcd_comio[5].GPIO+1) &= ~lcd_comio[5].Pin;
    }
    if (ComMode & 4UL)
    {
      *lcd_comio[6].GPIO |= lcd_comio[6].Pin;
      *(lcd_comio[6].GPIO+1) &= ~lcd_comio[6].Pin;
      *lcd_comio[7].GPIO |= lcd_comio[7].Pin;
      *(lcd_comio[7].GPIO+1) &= ~lcd_comio[7].Pin;
    }

    /* SEG0~31 IO Configuration */
    position = 0;
    while ((SEGVal0 >> position) != 0UL)
    {
      segcurrent = SEGVal0 & (1U << position);
      if (segcurrent)
      {
        /* Disable output */
        *lcd_segio[position].GPIO |= lcd_segio[position].Pin;
        /* Disable input */
        *(lcd_segio[position].GPIO + 1) &= ~lcd_segio[position].Pin; 
      }
      position++;
    }
    /* SEG32~63 IO Configuration */
    position = 0;
    while ((SEGVal1 >> position) != 0UL)
    {
      segcurrent = SEGVal1 & (1U << position);
      if (segcurrent)
      {
        /* Disable output */
        *lcd_segio[position + 32].GPIO |= lcd_segio[position + 32].Pin;
        /* Disable input */
        *(lcd_segio[position + 32].GPIO + 1) &= ~lcd_segio[position + 32].Pin; 
      }
      position++;
    }
    /* SEG64~79 IO Configuration */
    position = 0;
    while ((SEGVal2 >> position) != 0UL)
    {
      segcurrent = SEGVal2 & (1U << position);
      if (segcurrent)
      {
        /* Disable output */
        *lcd_segio[position + 64].GPIO |= lcd_segio[position + 64].Pin;
        /* Disable input */
        *(lcd_segio[position + 64].GPIO + 1) &= ~lcd_segio[position + 64].Pin; 
      }
      position++;
    }

    /* Enable SEGs' function of IOs */
    LCD->SEGCTRL0 = SEGVal0;
    LCD->SEGCTRL1 = SEGVal1;
    LCD->SEGCTRL2 = SEGVal2 & 0xFFFE;

    /* Enable LCD */
    LCD->CTRL |= LCD_CTRL_EN;
  }
}

/**
  * @brief  LCD SEGx enable.
  * @param  SEGVal0 SEGVal1 SEGVal2
  * @retval None
  */
void LCD_SetSEG(uint32_t SEGVal0, uint32_t SEGVal1, uint16_t SEGVal2)
{
  uint32_t position;
  uint32_t segcurrent;
    
  /* SEG0~31 IO Configuration */
  position = 0;
  while ((SEGVal0 >> position) != 0UL)
  {
    segcurrent = SEGVal0 & (1U << position);
    if (segcurrent)
    {
      /* Disable output */
      *lcd_segio[position].GPIO |= lcd_segio[position].Pin;
      /* Disable input */
      *(lcd_segio[position].GPIO + 1) &= ~lcd_segio[position].Pin; 
    }
    position++;
  }
  /* SEG32~63 IO Configuration */
  position = 0;
  while ((SEGVal1 >> position) != 0UL)
  {
    segcurrent = SEGVal1 & (1U << position);
    if (segcurrent)
    {
      /* Disable output */
      *lcd_segio[position + 32].GPIO |= lcd_segio[position + 32].Pin;
      /* Disable input */
      *(lcd_segio[position + 32].GPIO + 1) &= ~lcd_segio[position + 32].Pin; 
    }
    position++;
  }
  /* SEG64~79 IO Configuration */
  position = 0;
  while ((SEGVal2 >> position) != 0UL)
  {
    segcurrent = SEGVal2 & (1U << position);
    if (segcurrent)
    {
      /* Disable output */
      *lcd_segio[position + 64].GPIO |= lcd_segio[position + 64].Pin;
      /* Disable input */
      *(lcd_segio[position + 64].GPIO + 1) &= ~lcd_segio[position + 64].Pin; 
    }
    position++;
  }
  
  LCD->SEGCTRL0 = SEGVal0;
  LCD->SEGCTRL1 = SEGVal1;
  LCD->SEGCTRL2 = SEGVal2 & 0xFFFE;
}

/**
  * @brief  LCD BIAS mode configure.
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
  tmp &= ~ANA_REG6_LCD_BMODE;
  tmp |= BiasSelection;
  ANA->REG6 = tmp;
}

/**
  * @brief  LCD driving voltage configure.
  * @note   The LCD driving voltage's configuration in NVR will be load to register
  *         (ANA_REG6[4:1]) in startup_target.s file.
  *         ex:  
  *             The VLCD information in NVR[0x40D94]   10<<1(-300mV)
  *             1. When LCD_VLCD_DEC60MV is selected                 
  *                      11<<1(-360mV) will be configured to ANA_REG6[4:1], return 0
  *             2. When LCD_VLCD_DEC360MV is selected(out of range)  
  *                      15<<1(-600mV) will be configured to ANA_REG6[4:1], return 2
  * @param  VLCDSelection:
                  LCD_VLCD_0      
                  LCD_VLCD_INC60MV 
                  LCD_VLCD_INC120MV   
                  LCD_VLCD_INC180MV 
                  LCD_VLCD_INC240MV 
                  LCD_VLCD_INC300MV 
                  LCD_VLCD_DEC60MV 
                  LCD_VLCD_DEC120MV 
                  LCD_VLCD_DEC180MV
                  LCD_VLCD_DEC240MV 
                  LCD_VLCD_DEC300MV 
                  LCD_VLCD_DEC360MV
                  LCD_VLCD_DEC420MV 
                  LCD_VLCD_DEC480MV
                  LCD_VLCD_DEC540MV
                  LCD_VLCD_DEC600MV
  * @retval 0  Function successed.
            1  NVR LCD information checksum error.
            2  LCD driving voltage's configuration out of range.
  */
uint32_t LCD_VoltageConfig(uint32_t VLCDSelection)
{
  uint32_t lcd_vol;
  uint32_t lcd_vol_tmp;
  uint32_t tmp;
  NVR_LCDINFO LCD_InfoStruct;
  
  assert_parameters(IS_LCD_VLCD(VLCDSelection));
  
  /* Get NVR LCD information */
  if (NVR_GetLCDInfo(&LCD_InfoStruct))
    return (1);
  else
    lcd_vol_tmp = LCD_InfoStruct.MEALCDVol;
  
  tmp = ANA->REG6;
  tmp &= ~ANA_REG6_VLCD;
  lcd_vol = lcd_vol_tmp<<ANA_REG6_VLCD_Pos;

  /*Adjust voltage is postive*/
  if ( (lcd_vol_tmp <= 0x5U) && (VLCDSelection <= 0x5U) )
  {
    /*Adjust voltage is out of range(+300mv)*/
    if ((lcd_vol_tmp + VLCDSelection)>0x5U)
    {
      tmp |= LCD_VLCD_INC300MV << ANA_REG6_VLCD_Pos;
      ANA->REG6 = tmp;
      return (2);
    }
    else
    {
      tmp |= (lcd_vol + (VLCDSelection << ANA_REG6_VLCD_Pos));
      ANA->REG6 = tmp;
      return (0);
    }
  }
  /*Adjust voltage is negtive*/
  else if ( (lcd_vol_tmp > 0x5U) && (VLCDSelection > 0x5U) )
  {
    /*Adjust voltage is out of range(-600mv)*/
    if ((lcd_vol_tmp + VLCDSelection - 5)>0xFU)  
    {
      tmp |= LCD_VLCD_DEC600MV << ANA_REG6_VLCD_Pos;
      ANA->REG6 = tmp;
      return (2);
    }
    else
    {
      tmp |= (lcd_vol + ((VLCDSelection -0x5)<< ANA_REG6_VLCD_Pos));
      ANA->REG6 = tmp;
      return (0);
    }
  }
  else if ( (lcd_vol_tmp > 0x5U) && (VLCDSelection <= 0x5U) )
  {
    /*Adjust voltage is postive or 0*/
     if ((lcd_vol_tmp - 5) <= VLCDSelection)
     {
       tmp |= (((VLCDSelection + 0x5) << ANA_REG6_VLCD_Pos) - lcd_vol);
       ANA->REG6 = tmp;
       return (0);
     }
     /*Adjust voltage is negtive*/
     else
     {
       tmp |= (lcd_vol - ((VLCDSelection) << ANA_REG6_VLCD_Pos));
       ANA->REG6 = tmp;
       return (0);
     }
  }
  else
  {
     /*Adjust voltage is postive or 0*/
     if ((VLCDSelection - 5) <= lcd_vol_tmp)
     {
       tmp |= (lcd_vol - ((VLCDSelection - 0x5) << ANA_REG6_VLCD_Pos));
       ANA->REG6 = tmp;
       return (0);
     }
     /*Adjust voltage is negtive*/
     else
     {
       tmp |= ((VLCDSelection << ANA_REG6_VLCD_Pos) - lcd_vol);
       ANA->REG6 = tmp;
       return (0);
     }
  }
}

/*********************************** END OF FILE ******************************/
