/***************************************************************************//**
 * @file
 * @brief Liquid Crystal Display (LCD) peripheral API implementation for
 *   EFM32
 * @author Energy Micro AS
 * @version 1.3.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#include "efm32_lcd.h"
#if defined(LCD_COUNT) && (LCD_COUNT > 0)
#include "efm32_assert.h"
#include "efm32_bitband.h"

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup LCD
 * @brief LCD Liquid Crystal Display Peripheral API
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Initalize Liquid Crystal Display (LCD) controller
 *
 * @details
 *   This function call will only configure the LCD controller. You must enable
 *   it afterwards, potentially configuring Frame Control and interrupts first
 *   according to requirements.
 *
 * @param[in] lcdInit
 *   Pointer to initialization structure which configures LCD controller.
 *
 ******************************************************************************/
void LCD_Init(const LCD_Init_TypeDef *lcdInit)
{
  uint32_t dispCtrl = LCD->DISPCTRL;

  /* Disable controller before reconfiguration */
  LCD_Enable(false);

  /* Make sure we don't touch other bit fields (i.e. voltage boost) */
  dispCtrl &= ~(
    _LCD_DISPCTRL_MUX_MASK |
    _LCD_DISPCTRL_BIAS_MASK |
    _LCD_DISPCTRL_WAVE_MASK |
    _LCD_DISPCTRL_VLCDSEL_MASK |
    _LCD_DISPCTRL_CONCONF_MASK);

  /* Configure controller according to initialization structure */
  dispCtrl |= lcdInit->mux;
  dispCtrl |= lcdInit->bias;
  dispCtrl |= lcdInit->wave;
  dispCtrl |= lcdInit->vlcd;
  dispCtrl |= lcdInit->contrast;

  /* Update display controller */
  LCD->DISPCTRL = dispCtrl;

  /* Enable controller if wanted */
  if (lcdInit->enable)
  {
    LCD_Enable(true);
  }
}


/***************************************************************************//**
 * @brief
 *   Select source for VLCD
 *
 * @param[in] vlcd
 *   Select source for VLD voltage
 ******************************************************************************/
void LCD_VLCDSelect(LCD_VLCDSel_TypeDef vlcd)
{
  uint32_t dispctrl = LCD->DISPCTRL;

  /* Select VEXT or VDD */
  dispctrl &= ~(_LCD_DISPCTRL_VLCDSEL_MASK);
  switch (vlcd)
  {
  case lcdVLCDSelVExtBoost:
    dispctrl |= LCD_DISPCTRL_VLCDSEL_VEXTBOOST;
    break;
  case lcdVLCDSelVDD:
    dispctrl |= LCD_DISPCTRL_VLCDSEL_VDD;
    break;
  default:
    break;
  }

  LCD->DISPCTRL = dispctrl;
}


/***************************************************************************//**
 * @brief
 *   Configure Update Control
 *
 * @param[in] ud
 *   Configures LCD update method
 ******************************************************************************/
void LCD_UpdateCtrl(LCD_UpdateCtrl_TypeDef ud)
{
  LCD->CTRL = (LCD->CTRL & ~_LCD_CTRL_UDCTRL_MASK) | ud;
}


/***************************************************************************//**
 * @brief
 *   Initialize LCD Frame Counter
 *
 * @param[in] fcInit
 *   Pointer to Frame Counter initialization structure
 ******************************************************************************/
void LCD_FrameCountInit(const LCD_FrameCountInit_TypeDef *fcInit)
{
  uint32_t bactrl = LCD->BACTRL;

  /* Verify FC Top Counter to be within limits */
  EFM_ASSERT(fcInit->top < 64);

  /* Reconfigure frame count configuration */
  bactrl &= ~(_LCD_BACTRL_FCTOP_MASK |
              _LCD_BACTRL_FCPRESC_MASK);
  bactrl |= (fcInit->top << _LCD_BACTRL_FCTOP_SHIFT);
  bactrl |= fcInit->prescale;

  /* Set Blink and Animation Control Register */
  LCD->BACTRL = bactrl;

  LCD_FrameCountEnable(fcInit->enable);
}


/***************************************************************************//**
 * @brief
 *   Configures LCD controller Animation feature
 *
 * @param[in] animInit
 *   Pointer to LCD Animation initialization structure
 ******************************************************************************/
void LCD_AnimInit(const LCD_AnimInit_TypeDef *animInit)
{
  uint32_t bactrl = LCD->BACTRL;

  /* Set Animation Register Values */
  LCD->AREGA = animInit->AReg;
  LCD->AREGB = animInit->BReg;

  /* Configure Animation Shift and Logic */
  bactrl &= ~(_LCD_BACTRL_AREGASC_MASK |
              _LCD_BACTRL_AREGBSC_MASK |
              _LCD_BACTRL_ALOGSEL_MASK);

  bactrl |= (animInit->AShift << _LCD_BACTRL_AREGASC_SHIFT);
  bactrl |= (animInit->BShift << _LCD_BACTRL_AREGBSC_SHIFT);
  bactrl |= animInit->animLogic;

  /* Reconfigure */
  LCD->BACTRL = bactrl;

  /* Enable */
  LCD_AnimEnable(animInit->enable);
}


/***************************************************************************//**
 * @brief
 *   Enables update of this range of LCD segment lines
 *
 * @param[in] segmentRange
 *   Range of 4 LCD segments lines to enable or disable, for all enabled COM
 *   lines
 *
 * @param[in] enable
 *   Bool true to enable segment updates, false to disable updates
 ******************************************************************************/
void LCD_SegmentRangeEnable(LCD_SegmentRange_TypeDef segmentRange, bool enable)
{
  if (enable)
  {
    LCD->SEGEN |= segmentRange;
  }
  else
  {
    LCD->SEGEN &= ~(segmentRange);
  }
}


/***************************************************************************//**
 * @brief
 *   Turn on or clear a segment
 *
 * @param[in] com
 *   COM line to change
 *
 * @param[in] bit
 *   Bit index of which field to change
 *
 * @param[in] enable
 *   When true will set segment, when false will clear segment
 ******************************************************************************/
void LCD_SegmentSet(int com, int bit, bool enable)
{
  /* Maximum 40 segments per COM line */
  EFM_ASSERT(com < 4);
  EFM_ASSERT(bit < 40);

  /* Use bitband access for atomic bit set/clear of segment */
  switch (com)
  {
  case 0:
    if (bit < 32)
    {
      BITBAND_Peripheral(&(LCD->SEGD0L), bit, (unsigned int) enable);
    }
    else
    {
      bit -= 32;
      BITBAND_Peripheral(&(LCD->SEGD0H), bit, (unsigned int) enable);
    }
    break;
  case 1:
    if (bit < 32)
    {
      BITBAND_Peripheral(&(LCD->SEGD1L), bit, (unsigned int) enable);
    }
    else
    {
      bit -= 32;
      BITBAND_Peripheral(&(LCD->SEGD1H), bit, (unsigned int) enable);
    }
    break;
  case 2:
    if (bit < 32)
    {
      BITBAND_Peripheral(&(LCD->SEGD2L), bit, (unsigned int) enable);
    }
    else
    {
      bit -= 32;
      BITBAND_Peripheral(&(LCD->SEGD2H), bit, (unsigned int) enable);
    }
    break;
  case 3:
    if (bit < 32)
    {
      BITBAND_Peripheral(&(LCD->SEGD3L), bit, (unsigned int) enable);
    }
    else
    {
      bit -= 32;
      BITBAND_Peripheral(&(LCD->SEGD3H), bit, (unsigned int) enable);
    }
    break;
  default:
    break;
  }
}


/***************************************************************************//**
 * @brief
 *   Updates the 0-31 lowest segments on a given COM-line in one operation,
 *   according to bit mask
 *
 * @param[in] com
 *   Which COM line to update
 *
 * @param[in] mask
 *   Bit mask for segments 0-31
 *
 * @param[in] bits
 *   Bit pattern for segments 0-31
 ******************************************************************************/
void LCD_SegmentSetLow(int com, uint32_t mask, uint32_t bits)
{
  uint32_t segData;

  /* Maximum number of com lines */
  EFM_ASSERT(com < 4);

  switch (com)
  {
  case 0:
    segData     = LCD->SEGD0L;
    segData    &= ~(mask);
    segData    |= (mask & bits);
    LCD->SEGD0L = segData;
    break;
  case 1:
    segData     = LCD->SEGD1L;
    segData    &= ~(mask);
    segData    |= (mask & bits);
    LCD->SEGD1L = segData;
    break;
  case 2:
    segData     = LCD->SEGD2L;
    segData    &= ~(mask);
    segData    |= (mask & bits);
    LCD->SEGD2L = segData;
    break;
  case 3:
    segData     = LCD->SEGD3L;
    segData    &= ~(mask);
    segData    |= (mask & bits);
    LCD->SEGD3L = segData;
    break;
  default:
    break;
  }
}


/***************************************************************************//**
 * @brief
 *   Updated the high (32-39) segments on a given COM-line in one operation
 *
 * @param[in] com
 *   Which COM line to update
 *
 * @param[in] mask
 *   Bit mask for segments 32-39
 *
 * @param[in] bits
 *   Bit pattern for segments 32-39
 ******************************************************************************/
void LCD_SegmentSetHigh(int com, uint32_t mask, uint32_t bits)
{
  uint32_t segData;


  /* Maximum number of com lines */
  EFM_ASSERT(com < 4);

  switch (com)
  {
  case 0:
    segData     = LCD->SEGD0H;
    segData    &= ~(mask);
    segData    |= (mask & bits);
    LCD->SEGD0H = segData;
    break;
  case 1:
    segData     = LCD->SEGD1H;
    segData    &= ~(mask);
    segData    |= (mask & bits);
    LCD->SEGD1H = segData;
    break;
  case 2:
    segData     = LCD->SEGD2H;
    segData    &= ~(mask);
    segData    |= (mask & bits);
    LCD->SEGD2H = segData;
    break;
  case 3:
    segData     = LCD->SEGD3H;
    segData    &= ~(mask);
    segData    |= (mask & bits);
    LCD->SEGD3H = segData;
    break;
  default:
    break;
  }
}


/***************************************************************************//**
 * @brief
 *   Configure contrast level on LCD panel
 *
 * @param[in] level
 *   Contrast level in the range 0-31
 ******************************************************************************/
void LCD_ContrastSet(int level)
{
  EFM_ASSERT(level < 32);

  LCD->DISPCTRL = (LCD->DISPCTRL & ~_LCD_DISPCTRL_CONLEV_MASK)
                  | (level << _LCD_DISPCTRL_CONLEV_SHIFT);
}


/***************************************************************************//**
 * @brief
 *   Configure voltage booster
 *
 * The resulting voltage level is described in each part number's data sheet
 *
 * @param[in] vboost
 *   Voltage boost level
 ******************************************************************************/
void LCD_VBoostSet(LCD_VBoostLevel_TypeDef vboost)
{
  /* Reconfigure Voltage Boost */
  LCD->DISPCTRL = (LCD->DISPCTRL & ~_LCD_DISPCTRL_VBLEV_MASK) | vboost;
}


/** @} (end addtogroup LCD) */
/** @} (end addtogroup EFM32_Library) */

#endif /* defined(LCD_COUNT) && (LCD_COUNT > 0) */
