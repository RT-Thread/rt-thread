/**
  ******************************************************************************
  * @file    stm32f4xx_dma2d.c
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    08-November-2013
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the DMA2D controller (DMA2D) peripheral:
  *           + Initialization and configuration
  *           + Interrupts and flags management
  *           
  @verbatim  
 ===============================================================================
                      ##### How to use this driver #####
 ===============================================================================
    [..]
        (#) Enable DMA2D clock using 
            RCC_APB2PeriphResetCmd(RCC_APB2Periph_DMA2D, ENABLE) function.
            
        (#) Configures DMA2D
          (++) transfer mode 
          (++) pixel format, line_number, pixel_per_line
          (++) output memory address
          (++) alpha value
          (++) output offset
          (++) Default color (RGB)
           
        (#) Configures Foreground or/and background
          (++) memory address
          (++) alpha value
          (++) offset and default color
  
        (#) Call the DMA2D_Start() to enable the DMA2D controller.
        
    @endverbatim
  
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_dma2d.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup DMA2D 
  * @brief DMA2D driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#define CR_MASK                     ((uint32_t)0xFFFCE0FC)  /* DMA2D CR Mask */
#define PFCCR_MASK                  ((uint32_t)0x00FC00C0)  /* DMA2D FGPFCCR Mask */
#define DEAD_MASK                   ((uint32_t)0xFFFF00FE)  /* DMA2D DEAD Mask */

/** @defgroup DMA2D_Private_Functions
  * @{
  */

/** @defgroup DMA2D_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the DMA2D
      (+) Start/Abort/Suspend Transfer
      (+) Initialize, configure and set Foreground and background
      (+) configure and enable DeadTime
      (+) configure lineWatermark
    
    
@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the DMA2D peripheral registers to their default reset
  *         values.
  * @param  None
  * @retval None
  */

void DMA2D_DeInit(void)
{
  /* Enable DMA2D reset state */
  RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_DMA2D, ENABLE);
  /* Release DMA2D from reset state */
  RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_DMA2D, DISABLE);
}


/**
  * @brief  Initializes the DMA2D peripheral according to the specified parameters
  *         in the DMA2D_InitStruct.
  * @note   This function can be used only when the DMA2D is disabled.
  * @param  DMA2D_InitStruct: pointer to a DMA2D_InitTypeDef structure that contains
  *         the configuration information for the specified DMA2D peripheral.
  * @retval None
  */
void DMA2D_Init(DMA2D_InitTypeDef* DMA2D_InitStruct)
{

  uint32_t outgreen = 0;
  uint32_t outred   = 0;
  uint32_t outalpha = 0;
  uint32_t pixline  = 0;

  /* Check the parameters */
  assert_param(IS_DMA2D_MODE(DMA2D_InitStruct->DMA2D_Mode));
  assert_param(IS_DMA2D_CMODE(DMA2D_InitStruct->DMA2D_CMode));
  assert_param(IS_DMA2D_OGREEN(DMA2D_InitStruct->DMA2D_OutputGreen));
  assert_param(IS_DMA2D_ORED(DMA2D_InitStruct->DMA2D_OutputRed));
  assert_param(IS_DMA2D_OBLUE(DMA2D_InitStruct->DMA2D_OutputBlue));
  assert_param(IS_DMA2D_OALPHA(DMA2D_InitStruct->DMA2D_OutputAlpha));
  assert_param(IS_DMA2D_OUTPUT_OFFSET(DMA2D_InitStruct->DMA2D_OutputOffset));
  assert_param(IS_DMA2D_LINE(DMA2D_InitStruct->DMA2D_NumberOfLine));
  assert_param(IS_DMA2D_PIXEL(DMA2D_InitStruct->DMA2D_PixelPerLine));

  /* Configures the DMA2D operation mode */
  DMA2D->CR &= (uint32_t)CR_MASK;
  DMA2D->CR |= (DMA2D_InitStruct->DMA2D_Mode);

  /* Configures the color mode of the output image */
  DMA2D->OPFCCR &= ~(uint32_t)DMA2D_OPFCCR_CM;
  DMA2D->OPFCCR |= (DMA2D_InitStruct->DMA2D_CMode);

  /* Configures the output color */

  if (DMA2D_InitStruct->DMA2D_CMode == DMA2D_ARGB8888)
  {
    outgreen = DMA2D_InitStruct->DMA2D_OutputGreen << 8;
    outred = DMA2D_InitStruct->DMA2D_OutputRed << 16;
    outalpha = DMA2D_InitStruct->DMA2D_OutputAlpha << 24;
  }
  else
  
    if (DMA2D_InitStruct->DMA2D_CMode == DMA2D_RGB888)
    {
      outgreen = DMA2D_InitStruct->DMA2D_OutputGreen << 8;
      outred = DMA2D_InitStruct->DMA2D_OutputRed << 16;
      outalpha = (uint32_t)0x00000000;
    }
     
  else

    if (DMA2D_InitStruct->DMA2D_CMode == DMA2D_RGB565)
    {
      outgreen = DMA2D_InitStruct->DMA2D_OutputGreen << 5;
      outred = DMA2D_InitStruct->DMA2D_OutputRed << 11;
      outalpha = (uint32_t)0x00000000;
    }

  else

    if (DMA2D_InitStruct->DMA2D_CMode == DMA2D_ARGB1555)
    {  
      outgreen = DMA2D_InitStruct->DMA2D_OutputGreen << 5;
      outred = DMA2D_InitStruct->DMA2D_OutputRed << 10;
      outalpha = DMA2D_InitStruct->DMA2D_OutputAlpha << 15;
    }

  else /* DMA2D_CMode = DMA2D_ARGB4444 */
  {
    outgreen = DMA2D_InitStruct->DMA2D_OutputGreen << 4;
    outred = DMA2D_InitStruct->DMA2D_OutputRed << 8;
    outalpha = DMA2D_InitStruct->DMA2D_OutputAlpha << 12;
  }  
  DMA2D->OCOLR |= ((outgreen) | (outred) | (DMA2D_InitStruct->DMA2D_OutputBlue) | (outalpha));

  /* Configures the output memory address */
  DMA2D->OMAR = (DMA2D_InitStruct->DMA2D_OutputMemoryAdd);

  /* Configure  the line Offset */
  DMA2D->OOR &= ~(uint32_t)DMA2D_OOR_LO;
  DMA2D->OOR |= (DMA2D_InitStruct->DMA2D_OutputOffset);

  /* Configure the number of line and pixel per line */
  pixline = DMA2D_InitStruct->DMA2D_PixelPerLine << 16; 
  DMA2D->NLR &= ~(DMA2D_NLR_NL | DMA2D_NLR_PL);
  DMA2D->NLR |= ((DMA2D_InitStruct->DMA2D_NumberOfLine) | (pixline));

/**
  * @brief  Fills each DMA2D_InitStruct member with its default value.
  * @param  DMA2D_InitStruct: pointer to a DMA2D_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
}
void DMA2D_StructInit(DMA2D_InitTypeDef* DMA2D_InitStruct)
{
  /* Initialize the transfer mode member */
  DMA2D_InitStruct->DMA2D_Mode = DMA2D_M2M;

  /* Initialize the output color mode members */
  DMA2D_InitStruct->DMA2D_CMode = DMA2D_ARGB8888;

  /* Initialize the alpha and RGB values */
  DMA2D_InitStruct->DMA2D_OutputGreen = 0x00;
  DMA2D_InitStruct->DMA2D_OutputBlue = 0x00;
  DMA2D_InitStruct->DMA2D_OutputRed = 0x00;
  DMA2D_InitStruct->DMA2D_OutputAlpha = 0x00;

  /* Initialize the output memory address */
  DMA2D_InitStruct->DMA2D_OutputMemoryAdd = 0x00;

  /* Initialize the output offset */
  DMA2D_InitStruct->DMA2D_OutputOffset = 0x00;

  /* Initialize the number of line and the number of pixel per line */
  DMA2D_InitStruct->DMA2D_NumberOfLine = 0x00;
  DMA2D_InitStruct->DMA2D_PixelPerLine = 0x00;
}

/**
  * @brief  Start the DMA2D transfer.
  * @param 
  * @retval None
  */

void DMA2D_StartTransfer(void)
{
    /* Start DMA2D transfer by setting START bit */
    DMA2D->CR |= (uint32_t)DMA2D_CR_START;
}

/**
  * @brief  Aboart the DMA2D transfer.
  * @param
  * @retval None
  */

void DMA2D_AbortTransfer(void)
{
    /* Start DMA2D transfer by setting START bit */
    DMA2D->CR |= (uint32_t)DMA2D_CR_ABORT;

}

/**
  * @brief  Stop or continue the DMA2D transfer.
  * @param  NewState: new state of the DMA2D peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA2D_Suspend(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Suspend DMA2D transfer by setting STOP bit */
    DMA2D->CR |= (uint32_t)DMA2D_CR_SUSP;
  }
  else
  {
    /* Continue DMA2D transfer by clearing STOP bit */
    DMA2D->CR &= ~(uint32_t)DMA2D_CR_SUSP;
  }
}

/**
  * @brief  Configures the Foreground according to the specified parameters
  *         in the DMA2D_FGStruct.
  * @note   This function can be used only when the transfer is disabled.
  * @param  DMA2D_FGStruct: pointer to a DMA2D_FGTypeDef structure that contains
  *         the configuration information for the specified Background.
  * @retval None
  */
void DMA2D_FGConfig(DMA2D_FG_InitTypeDef* DMA2D_FG_InitStruct)
{

  uint32_t fg_clutcolormode = 0;
  uint32_t fg_clutsize = 0;
  uint32_t fg_alpha_mode = 0;
  uint32_t fg_alphavalue = 0;
  uint32_t fg_colorgreen = 0;
  uint32_t fg_colorred = 0;

  assert_param(IS_DMA2D_FGO(DMA2D_FG_InitStruct->DMA2D_FGO));
  assert_param(IS_DMA2D_FGCM(DMA2D_FG_InitStruct->DMA2D_FGCM));
  assert_param(IS_DMA2D_FG_CLUT_CM(DMA2D_FG_InitStruct->DMA2D_FG_CLUT_CM));
  assert_param(IS_DMA2D_FG_CLUT_SIZE(DMA2D_FG_InitStruct->DMA2D_FG_CLUT_SIZE));
  assert_param(IS_DMA2D_FG_ALPHA_MODE(DMA2D_FG_InitStruct->DMA2D_FGPFC_ALPHA_MODE));
  assert_param(IS_DMA2D_FG_ALPHA_VALUE(DMA2D_FG_InitStruct->DMA2D_FGPFC_ALPHA_VALUE));
  assert_param(IS_DMA2D_FGC_BLUE(DMA2D_FG_InitStruct->DMA2D_FGC_BLUE));
  assert_param(IS_DMA2D_FGC_GREEN(DMA2D_FG_InitStruct->DMA2D_FGC_GREEN));
  assert_param(IS_DMA2D_FGC_RED(DMA2D_FG_InitStruct->DMA2D_FGC_RED));

  /* Configures the FG memory address */
  DMA2D->FGMAR = (DMA2D_FG_InitStruct->DMA2D_FGMA);

  /* Configures the FG offset */
  DMA2D->FGOR &= ~(uint32_t)DMA2D_FGOR_LO;
  DMA2D->FGOR |= (DMA2D_FG_InitStruct->DMA2D_FGO);

  /* Configures foreground Pixel Format Convertor */
  DMA2D->FGPFCCR &= (uint32_t)PFCCR_MASK;
  fg_clutcolormode = DMA2D_FG_InitStruct->DMA2D_FG_CLUT_CM << 4;
  fg_clutsize = DMA2D_FG_InitStruct->DMA2D_FG_CLUT_SIZE << 8;
  fg_alpha_mode = DMA2D_FG_InitStruct->DMA2D_FGPFC_ALPHA_MODE << 16;
  fg_alphavalue = DMA2D_FG_InitStruct->DMA2D_FGPFC_ALPHA_VALUE << 24;
  DMA2D->FGPFCCR |= (DMA2D_FG_InitStruct->DMA2D_FGCM | fg_clutcolormode | fg_clutsize | \
                    fg_alpha_mode | fg_alphavalue);

  /* Configures foreground color */
  DMA2D->FGCOLR &= ~(DMA2D_FGCOLR_BLUE | DMA2D_FGCOLR_GREEN | DMA2D_FGCOLR_RED);
  fg_colorgreen = DMA2D_FG_InitStruct->DMA2D_FGC_GREEN << 8;
  fg_colorred = DMA2D_FG_InitStruct->DMA2D_FGC_RED << 16;
  DMA2D->FGCOLR |= (DMA2D_FG_InitStruct->DMA2D_FGC_BLUE | fg_colorgreen | fg_colorred);

  /* Configures foreground CLUT memory address */
  DMA2D->FGCMAR = DMA2D_FG_InitStruct->DMA2D_FGCMAR;
}

/**
  * @brief  Fills each DMA2D_FGStruct member with its default value.
  * @param  DMA2D_FGStruct: pointer to a DMA2D_FGTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void DMA2D_FG_StructInit(DMA2D_FG_InitTypeDef* DMA2D_FG_InitStruct)
{
  /*!< Initialize the DMA2D foreground memory address */
  DMA2D_FG_InitStruct->DMA2D_FGMA = 0x00;

  /*!< Initialize the DMA2D foreground offset */
  DMA2D_FG_InitStruct->DMA2D_FGO = 0x00;

  /*!< Initialize the DMA2D foreground color mode */
  DMA2D_FG_InitStruct->DMA2D_FGCM = CM_ARGB8888;

  /*!< Initialize the DMA2D foreground CLUT color mode */
  DMA2D_FG_InitStruct->DMA2D_FG_CLUT_CM = CLUT_CM_ARGB8888;

  /*!< Initialize the DMA2D foreground CLUT size */
  DMA2D_FG_InitStruct->DMA2D_FG_CLUT_SIZE = 0x00;

  /*!< Initialize the DMA2D foreground alpha mode */
  DMA2D_FG_InitStruct->DMA2D_FGPFC_ALPHA_MODE = NO_MODIF_ALPHA_VALUE;

  /*!< Initialize the DMA2D foreground alpha value */
  DMA2D_FG_InitStruct->DMA2D_FGPFC_ALPHA_VALUE = 0x00;

  /*!< Initialize the DMA2D foreground blue value */
  DMA2D_FG_InitStruct->DMA2D_FGC_BLUE = 0x00;

  /*!< Initialize the DMA2D foreground green value */
  DMA2D_FG_InitStruct->DMA2D_FGC_GREEN = 0x00;

  /*!< Initialize the DMA2D foreground red value */
  DMA2D_FG_InitStruct->DMA2D_FGC_RED = 0x00;

  /*!< Initialize the DMA2D foreground CLUT memory address */
  DMA2D_FG_InitStruct->DMA2D_FGCMAR = 0x00;
}


/**
  * @brief  Configures the Background according to the specified parameters
  *         in the DMA2D_BGStruct.
  * @note   This function can be used only when the transfer is disabled.
  * @param  DMA2D_BGStruct: pointer to a DMA2D_BGTypeDef structure that contains
  *         the configuration information for the specified Background.
  * @retval None
  */
void DMA2D_BGConfig(DMA2D_BG_InitTypeDef* DMA2D_BG_InitStruct)
{

  uint32_t bg_clutcolormode = 0;
  uint32_t bg_clutsize = 0;
  uint32_t bg_alpha_mode = 0;
  uint32_t bg_alphavalue = 0;
  uint32_t bg_colorgreen = 0;
  uint32_t bg_colorred = 0;

  assert_param(IS_DMA2D_BGO(DMA2D_BG_InitStruct->DMA2D_BGO));
  assert_param(IS_DMA2D_BGCM(DMA2D_BG_InitStruct->DMA2D_BGCM));
  assert_param(IS_DMA2D_BG_CLUT_CM(DMA2D_BG_InitStruct->DMA2D_BG_CLUT_CM));
  assert_param(IS_DMA2D_BG_CLUT_SIZE(DMA2D_BG_InitStruct->DMA2D_BG_CLUT_SIZE));
  assert_param(IS_DMA2D_BG_ALPHA_MODE(DMA2D_BG_InitStruct->DMA2D_BGPFC_ALPHA_MODE));
  assert_param(IS_DMA2D_BG_ALPHA_VALUE(DMA2D_BG_InitStruct->DMA2D_BGPFC_ALPHA_VALUE));
  assert_param(IS_DMA2D_BGC_BLUE(DMA2D_BG_InitStruct->DMA2D_BGC_BLUE));
  assert_param(IS_DMA2D_BGC_GREEN(DMA2D_BG_InitStruct->DMA2D_BGC_GREEN));
  assert_param(IS_DMA2D_BGC_RED(DMA2D_BG_InitStruct->DMA2D_BGC_RED));

  /* Configures the BG memory address */
  DMA2D->BGMAR = (DMA2D_BG_InitStruct->DMA2D_BGMA);

  /* Configures the BG offset */
  DMA2D->BGOR &= ~(uint32_t)DMA2D_BGOR_LO;
  DMA2D->BGOR |= (DMA2D_BG_InitStruct->DMA2D_BGO);

  /* Configures background Pixel Format Convertor */
  DMA2D->BGPFCCR &= (uint32_t)PFCCR_MASK;
  bg_clutcolormode = DMA2D_BG_InitStruct->DMA2D_BG_CLUT_CM << 4;
  bg_clutsize = DMA2D_BG_InitStruct->DMA2D_BG_CLUT_SIZE << 8;
  bg_alpha_mode = DMA2D_BG_InitStruct->DMA2D_BGPFC_ALPHA_MODE << 16;
  bg_alphavalue = DMA2D_BG_InitStruct->DMA2D_BGPFC_ALPHA_VALUE << 24;
  DMA2D->BGPFCCR |= (DMA2D_BG_InitStruct->DMA2D_BGCM | bg_clutcolormode | bg_clutsize | \
                    bg_alpha_mode | bg_alphavalue);

  /* Configures background color */
  DMA2D->BGCOLR &= ~(DMA2D_BGCOLR_BLUE | DMA2D_BGCOLR_GREEN | DMA2D_BGCOLR_RED);
  bg_colorgreen = DMA2D_BG_InitStruct->DMA2D_BGC_GREEN << 8;
  bg_colorred = DMA2D_BG_InitStruct->DMA2D_BGC_RED << 16;
  DMA2D->BGCOLR |= (DMA2D_BG_InitStruct->DMA2D_BGC_BLUE | bg_colorgreen | bg_colorred);
  
  /* Configures background CLUT memory address */
  DMA2D->BGCMAR = DMA2D_BG_InitStruct->DMA2D_BGCMAR;

}

/**
  * @brief  Fills each DMA2D_BGStruct member with its default value.
  * @param  DMA2D_BGStruct: pointer to a DMA2D_BGTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void DMA2D_BG_StructInit(DMA2D_BG_InitTypeDef* DMA2D_BG_InitStruct)
{
  /*!< Initialize the DMA2D background memory address */
  DMA2D_BG_InitStruct->DMA2D_BGMA = 0x00;

  /*!< Initialize the DMA2D background offset */
  DMA2D_BG_InitStruct->DMA2D_BGO = 0x00;

  /*!< Initialize the DMA2D background color mode */
  DMA2D_BG_InitStruct->DMA2D_BGCM = CM_ARGB8888;

  /*!< Initialize the DMA2D background CLUT color mode */
  DMA2D_BG_InitStruct->DMA2D_BG_CLUT_CM = CLUT_CM_ARGB8888;

  /*!< Initialize the DMA2D background CLUT size */
  DMA2D_BG_InitStruct->DMA2D_BG_CLUT_SIZE = 0x00;

  /*!< Initialize the DMA2D background alpha mode */
  DMA2D_BG_InitStruct->DMA2D_BGPFC_ALPHA_MODE = NO_MODIF_ALPHA_VALUE;

  /*!< Initialize the DMA2D background alpha value */
  DMA2D_BG_InitStruct->DMA2D_BGPFC_ALPHA_VALUE = 0x00;

  /*!< Initialize the DMA2D background blue value */
  DMA2D_BG_InitStruct->DMA2D_BGC_BLUE = 0x00;

  /*!< Initialize the DMA2D background green value */
  DMA2D_BG_InitStruct->DMA2D_BGC_GREEN = 0x00;

  /*!< Initialize the DMA2D background red value */
  DMA2D_BG_InitStruct->DMA2D_BGC_RED = 0x00;

  /*!< Initialize the DMA2D background CLUT memory address */
  DMA2D_BG_InitStruct->DMA2D_BGCMAR = 0x00;
}

/**
  * @brief  Start the automatic loading of the CLUT or abort the transfer.
  * @param  NewState: new state of the DMA2D peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void DMA2D_FGStart(FunctionalState NewState) 
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Start the automatic loading of the CLUT */
    DMA2D->FGPFCCR |= DMA2D_FGPFCCR_START;
  }
  else
  {
    /* abort the transfer */
    DMA2D->FGPFCCR &= (uint32_t)~DMA2D_FGPFCCR_START;
  }
}

/**
  * @brief  Start the automatic loading of the CLUT or abort the transfer.
  * @param  NewState: new state of the DMA2D peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
  
void DMA2D_BGStart(FunctionalState NewState) 
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Start the automatic loading of the CLUT */
    DMA2D->BGPFCCR |= DMA2D_BGPFCCR_START;
  }
  else
  {
    /* abort the transfer */
    DMA2D->BGPFCCR &= (uint32_t)~DMA2D_BGPFCCR_START;
  }
}

/**
  * @brief  Configures the DMA2D dead time.
  * @param  DMA2D_DeadTime: specifies the DMA2D dead time.
  *   This parameter can be one of the following values:
  * @retval None
  */
void DMA2D_DeadTimeConfig(uint32_t DMA2D_DeadTime, FunctionalState NewState)
{
   uint32_t DeadTime;

  /* Check the parameters */
  assert_param(IS_DMA2D_DEAD_TIME(DMA2D_DeadTime));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable and Configures the dead time */
    DMA2D->AMTCR &= (uint32_t)DEAD_MASK;
    DeadTime = DMA2D_DeadTime << 8;
    DMA2D->AMTCR |= (DeadTime | DMA2D_AMTCR_EN);
  }
  else
  {
     DMA2D->AMTCR &= ~(uint32_t)DMA2D_AMTCR_EN;
  }
}

/**
  * @brief  Define the configuration of the line watermark .
  * @param  DMA2D_LWatermarkConfig: Line Watermark configuration.
  * @retval None
  */

void DMA2D_LineWatermarkConfig(uint32_t DMA2D_LWatermarkConfig)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_LineWatermark(DMA2D_LWatermarkConfig));

  /* Sets the Line watermark configuration */
  DMA2D->LWR = (uint32_t)DMA2D_LWatermarkConfig;
}

/**
  * @}
  */

/** @defgroup DMA2D_Group2 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================

    [..] This section provides functions allowing to configure the DMA2D 
         Interrupts and to get the status and clear flags and Interrupts 
         pending bits.
    [..] The DMA2D provides 6 Interrupts sources and 6 Flags
    
    *** Flags ***
    =============
    [..]
      (+) DMA2D_FLAG_CE : Configuration Error Interrupt flag
      (+) DMA2D_FLAG_CAE: CLUT Access Error Interrupt flag
      (+) DMA2D_FLAG_TW:  Transfer Watermark Interrupt flag
      (+) DMA2D_FLAG_TC:  Transfer Complete interrupt flag
      (+) DMA2D_FLAG_TE:  Transfer Error interrupt flag
      (+) DMA2D_FLAG_CTC: CLUT Transfer Complete Interrupt flag
      
    *** Interrupts ***
    ==================
    [..]
      (+) DMA2D_IT_CE: Configuration Error Interrupt is generated when a wrong 
                       configuration is detected
      (+) DMA2D_IT_CAE: CLUT Access Error Interrupt
      (+) DMA2D_IT_TW: Transfer Watermark Interrupt is generated when 
                       the programmed watermark is reached 
      (+) DMA2D_IT_TE: Transfer Error interrupt is generated when the CPU trying 
                       to access the CLUT while a CLUT loading or a DMA2D1 transfer 
                       is on going       
      (+) DMA2D_IT_CTC: CLUT Transfer Complete Interrupt 
      (+) DMA2D_IT_TC: Transfer Complete interrupt         
@endverbatim
  * @{
  */
/**
  * @brief  Enables or disables the specified DMA2D's interrupts.
  * @param  DMA2D_IT: specifies the DMA2D interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg DMA2D_IT_CE:   Configuration Error Interrupt Enable.
  *     @arg DMA2D_IT_CTC:  CLUT Transfer Complete Interrupt Enable.
  *     @arg DMA2D_IT_CAE:  CLUT Access Error Interrupt Enable.
  *     @arg DMA2D_IT_TW:   Transfer Watermark Interrupt Enable.
  *     @arg DMA2D_IT_TC:   Transfer Complete interrupt enable.
  *     @arg DMA2D_IT_TE:   Transfer Error interrupt enable.
  * @param NewState: new state of the specified DMA2D interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void DMA2D_ITConfig(uint32_t DMA2D_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_IT(DMA2D_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DMA2D interrupts */
    DMA2D->CR |= DMA2D_IT;
  }
  else
  {
    /* Disable the selected DMA2D interrupts */
    DMA2D->CR &= (uint32_t)~DMA2D_IT;
  }
}

/**
  * @brief  Checks whether the specified DMA2D's flag is set or not.
  * @param  DMA2D_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg DMA2D_FLAG_CE:   Configuration Error Interrupt flag.
  *     @arg DMA2D_FLAG_CTC:  CLUT Transfer Complete Interrupt flag.
  *     @arg DMA2D_FLAG_CAE:  CLUT Access Error Interrupt flag.
  *     @arg DMA2D_FLAG_TW:   Transfer Watermark Interrupt flag.
  *     @arg DMA2D_FLAG_TC:   Transfer Complete interrupt flag.
  *     @arg DMA2D_FLAG_TE:   Transfer Error interrupt flag.
  * @retval The new state of DMA2D_FLAG (SET or RESET).
  */

FlagStatus DMA2D_GetFlagStatus(uint32_t DMA2D_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_DMA2D_GET_FLAG(DMA2D_FLAG));
  
  /* Check the status of the specified DMA2D flag */
  if (((DMA2D->ISR) & DMA2D_FLAG) != (uint32_t)RESET)
  {
    /* DMA2D_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* DMA2D_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the DMA2D_FLAG status */
  return bitstatus;
}

/**
  * @brief  Clears the DMA2D's pending flags.
  * @param  DMA2D_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg DMA2D_FLAG_CE:   Configuration Error Interrupt flag.
  *     @arg DMA2D_FLAG_CTC:  CLUT Transfer Complete Interrupt flag.
  *     @arg DMA2D_FLAG_CAE:  CLUT Access Error Interrupt flag.
  *     @arg DMA2D_FLAG_TW:   Transfer Watermark Interrupt flag.
  *     @arg DMA2D_FLAG_TC:   Transfer Complete interrupt flag.
  *     @arg DMA2D_FLAG_TE:   Transfer Error interrupt flag.
  * @retval None
  */
void DMA2D_ClearFlag(uint32_t DMA2D_FLAG)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_GET_FLAG(DMA2D_FLAG));
    
  /* Clear the corresponding DMA2D flag */
  DMA2D->IFCR = (uint32_t)DMA2D_FLAG;
}

/**
  * @brief  Checks whether the specified DMA2D's interrupt has occurred or not.
  * @param  DMA2D_IT: specifies the DMA2D interrupts sources to check.
  *   This parameter can be one of the following values:
  *     @arg DMA2D_IT_CE:   Configuration Error Interrupt Enable.
  *     @arg DMA2D_IT_CTC:  CLUT Transfer Complete Interrupt Enable.
  *     @arg DMA2D_IT_CAE:  CLUT Access Error Interrupt Enable.
  *     @arg DMA2D_IT_TW:   Transfer Watermark Interrupt Enable.
  *     @arg DMA2D_IT_TC:   Transfer Complete interrupt enable.
  *     @arg DMA2D_IT_TE:   Transfer Error interrupt enable.
  * @retval The new state of the DMA2D_IT (SET or RESET).
  */
ITStatus DMA2D_GetITStatus(uint32_t DMA2D_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t DMA2D_IT_FLAG = DMA2D_IT >> 8;
  
  /* Check the parameters */
  assert_param(IS_DMA2D_IT(DMA2D_IT));

  if ((DMA2D->ISR & DMA2D_IT_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  
  if (((DMA2D->CR & DMA2D_IT) != (uint32_t)RESET) && (bitstatus != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the DMA2D's interrupt pending bits.
  * @param  DMA2D_IT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg DMA2D_IT_CE:   Configuration Error Interrupt.
  *     @arg DMA2D_IT_CTC:  CLUT Transfer Complete Interrupt.
  *     @arg DMA2D_IT_CAE:  CLUT Access Error Interrupt.
  *     @arg DMA2D_IT_TW:   Transfer Watermark Interrupt.
  *     @arg DMA2D_IT_TC:   Transfer Complete interrupt.
  *     @arg DMA2D_IT_TE:   Transfer Error interrupt.
  * @retval None
  */
void DMA2D_ClearITPendingBit(uint32_t DMA2D_IT)
{
  /* Check the parameters */
  assert_param(IS_DMA2D_IT(DMA2D_IT));
  DMA2D_IT = DMA2D_IT >> 8;
    
  /* Clear the corresponding DMA2D Interrupt */
  DMA2D->IFCR = (uint32_t)DMA2D_IT;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
