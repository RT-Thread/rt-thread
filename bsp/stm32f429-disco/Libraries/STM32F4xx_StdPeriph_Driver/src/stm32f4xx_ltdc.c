/**
  ******************************************************************************
  * @file    stm32f4xx_ltdc.c
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    08-November-2013
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the LTDC controller (LTDC) peripheral:
  *           + Initialization and configuration
  *           + Interrupts and flags management
  *           
  *  @verbatim
  
 ===============================================================================
                      ##### How to use this driver #####
 ===============================================================================
    [..]
        (#) Enable LTDC clock using 
            RCC_APB2PeriphResetCmd(RCC_APB2Periph_LTDC, ENABLE) function.
        (#) Configures LTDC
          (++) Configure the required Pixel clock following the panel datasheet
          (++) Configure the Synchronous timings: VSYNC, HSYNC, Vertical and 
              Horizontal back proch, active data area and the front proch 
              timings 
          (++) Configure the synchronous signals and clock polarity in the 
              LTDC_GCR register
        (#) Configures Layer1/2 parameters
          (++) The Layer window horizontal and vertical position in the LTDC_LxWHPCR and 
               LTDC_WVPCR registers. The layer window must be in the active data area.
          (++) The pixel input format in the LTDC_LxPFCR register
          (++) The color frame buffer start address in the LTDC_LxCFBAR register
          (++) The line length and pitch of the color frame buffer in the 
               LTDC_LxCFBLR register
          (++) The number of lines of the color frame buffer in 
               the LTDC_LxCFBLNR register
          (++) if needed, load the CLUT with the RGB values and the address 
               in the LTDC_LxCLUTWR register
          (++) If needed, configure the default color and the blending factors 
               respectively in the LTDC_LxDCCR and LTDC_LxBFCR registers 

          (++) If needed, Dithering and color keying can be be enabled respectively 
               in the LTDC_GCR and LTDC_LxCKCR registers. It can be also enabled 
               on the fly.    
        (#) Enable Layer1/2 and if needed the CLUT in the LTDC_LxCR register 
  
        (#) Reload the shadow registers to active register through 
            the LTDC_SRCR register.
          -@- All layer parameters can be be modified on the fly except the CLUT. 
              The new configuration has to be either reloaded immediately 
              or during vertical blanking period by configuring the LTDC_SRCR register.              
        (#) Call the LTDC_Cmd() to enable the LTDC controller.

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
#include "stm32f4xx_ltdc.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup LTDC 
  * @brief LTDC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#define GCR_MASK                     ((uint32_t)0x0FFE888F)  /* LTDC GCR Mask */


/** @defgroup LTDC_Private_Functions
  * @{
  */

/** @defgroup LTDC_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the LTDC
      (+) Enable or Disable Dither
      (+) Define the position of the line interrupt
      (+) reload layers registers with new parameters
      (+) Initialize and configure layer1 and layer2
      (+) Set and configure the color keying functionality
      (+) Configure and Enables or disables CLUT 
      
@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the LTDC peripheral registers to their default reset
  *         values.
  * @param  None
  * @retval None
  */

void LTDC_DeInit(void)
{
  /* Enable LTDC reset state */
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_LTDC, ENABLE);
  /* Release LTDC from reset state */
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_LTDC, DISABLE);
}

/**
  * @brief  Initializes the LTDC peripheral according to the specified parameters
  *         in the LTDC_InitStruct.
  * @note   This function can be used only when the LTDC is disabled.
  * @param  LTDC_InitStruct: pointer to a LTDC_InitTypeDef structure that contains
  *         the configuration information for the specified LTDC peripheral.
  * @retval None
  */

void LTDC_Init(LTDC_InitTypeDef* LTDC_InitStruct)
{
  uint32_t horizontalsync = 0;
  uint32_t accumulatedHBP = 0;
  uint32_t accumulatedactiveW = 0;
  uint32_t totalwidth = 0;
  uint32_t backgreen = 0;
  uint32_t backred = 0;

  /* Check function parameters */
  assert_param(IS_LTDC_HSYNC(LTDC_InitStruct->LTDC_HorizontalSync));
  assert_param(IS_LTDC_VSYNC(LTDC_InitStruct->LTDC_VerticalSync));
  assert_param(IS_LTDC_AHBP(LTDC_InitStruct->LTDC_AccumulatedHBP));
  assert_param(IS_LTDC_AVBP(LTDC_InitStruct->LTDC_AccumulatedVBP));
  assert_param(IS_LTDC_AAH(LTDC_InitStruct->LTDC_AccumulatedActiveH));
  assert_param(IS_LTDC_AAW(LTDC_InitStruct->LTDC_AccumulatedActiveW));
  assert_param(IS_LTDC_TOTALH(LTDC_InitStruct->LTDC_TotalHeigh));
  assert_param(IS_LTDC_TOTALW(LTDC_InitStruct->LTDC_TotalWidth));
  assert_param(IS_LTDC_HSPOL(LTDC_InitStruct->LTDC_HSPolarity));
  assert_param(IS_LTDC_VSPOL(LTDC_InitStruct->LTDC_VSPolarity));
  assert_param(IS_LTDC_DEPOL(LTDC_InitStruct->LTDC_DEPolarity));
  assert_param(IS_LTDC_PCPOL(LTDC_InitStruct->LTDC_PCPolarity));
  assert_param(IS_LTDC_BackBlueValue(LTDC_InitStruct->LTDC_BackgroundBlueValue));
  assert_param(IS_LTDC_BackGreenValue(LTDC_InitStruct->LTDC_BackgroundGreenValue));
  assert_param(IS_LTDC_BackRedValue(LTDC_InitStruct->LTDC_BackgroundRedValue));

  /* Sets Synchronization size */
  LTDC->SSCR &= ~(LTDC_SSCR_VSH | LTDC_SSCR_HSW);
  horizontalsync = (LTDC_InitStruct->LTDC_HorizontalSync << 16);
  LTDC->SSCR |= (horizontalsync | LTDC_InitStruct->LTDC_VerticalSync);

  /* Sets Accumulated Back porch */
  LTDC->BPCR &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
  accumulatedHBP = (LTDC_InitStruct->LTDC_AccumulatedHBP << 16);
  LTDC->BPCR |= (accumulatedHBP | LTDC_InitStruct->LTDC_AccumulatedVBP);

  /* Sets Accumulated Active Width */
  LTDC->AWCR &= ~(LTDC_AWCR_AAH | LTDC_AWCR_AAW);
  accumulatedactiveW = (LTDC_InitStruct->LTDC_AccumulatedActiveW << 16);
  LTDC->AWCR |= (accumulatedactiveW | LTDC_InitStruct->LTDC_AccumulatedActiveH);

  /* Sets Total Width */
  LTDC->TWCR &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
  totalwidth = (LTDC_InitStruct->LTDC_TotalWidth << 16);
  LTDC->TWCR |= (totalwidth | LTDC_InitStruct->LTDC_TotalHeigh);

  LTDC->GCR &= (uint32_t)GCR_MASK;
  LTDC->GCR |=  (uint32_t)(LTDC_InitStruct->LTDC_HSPolarity | LTDC_InitStruct->LTDC_VSPolarity | \
                           LTDC_InitStruct->LTDC_DEPolarity | LTDC_InitStruct->LTDC_PCPolarity);

  /* sets the background color value */
  backgreen = (LTDC_InitStruct->LTDC_BackgroundGreenValue << 8);
  backred = (LTDC_InitStruct->LTDC_BackgroundRedValue << 16);

  LTDC->BCCR &= ~(LTDC_BCCR_BCBLUE | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCRED);
  LTDC->BCCR |= (backred | backgreen | LTDC_InitStruct->LTDC_BackgroundBlueValue);
}

/**
  * @brief  Fills each LTDC_InitStruct member with its default value.
  * @param  LTDC_InitStruct: pointer to a LTDC_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */

void LTDC_StructInit(LTDC_InitTypeDef* LTDC_InitStruct)
{
  /*--------------- Reset LTDC init structure parameters values ----------------*/
  LTDC_InitStruct->LTDC_HSPolarity = LTDC_HSPolarity_AL;      /*!< Initialize the LTDC_HSPolarity member */ 
  LTDC_InitStruct->LTDC_VSPolarity = LTDC_VSPolarity_AL;      /*!< Initialize the LTDC_VSPolarity member */
  LTDC_InitStruct->LTDC_DEPolarity = LTDC_DEPolarity_AL;      /*!< Initialize the LTDC_DEPolarity member */
  LTDC_InitStruct->LTDC_PCPolarity = LTDC_PCPolarity_IPC;     /*!< Initialize the LTDC_PCPolarity member */
  LTDC_InitStruct->LTDC_HorizontalSync = 0x00;                /*!< Initialize the LTDC_HorizontalSync member */
  LTDC_InitStruct->LTDC_VerticalSync = 0x00;                  /*!< Initialize the LTDC_VerticalSync member */
  LTDC_InitStruct->LTDC_AccumulatedHBP = 0x00;                /*!< Initialize the LTDC_AccumulatedHBP member */
  LTDC_InitStruct->LTDC_AccumulatedVBP = 0x00;                /*!< Initialize the LTDC_AccumulatedVBP member */
  LTDC_InitStruct->LTDC_AccumulatedActiveW = 0x00;            /*!< Initialize the LTDC_AccumulatedActiveW member */
  LTDC_InitStruct->LTDC_AccumulatedActiveH = 0x00;            /*!< Initialize the LTDC_AccumulatedActiveH member */
  LTDC_InitStruct->LTDC_TotalWidth = 0x00;                    /*!< Initialize the LTDC_TotalWidth member */
  LTDC_InitStruct->LTDC_TotalHeigh = 0x00;                    /*!< Initialize the LTDC_TotalHeigh member */
  LTDC_InitStruct->LTDC_BackgroundRedValue = 0x00;            /*!< Initialize the LTDC_BackgroundRedValue member */
  LTDC_InitStruct->LTDC_BackgroundGreenValue = 0x00;          /*!< Initialize the LTDC_BackgroundGreenValue member */
  LTDC_InitStruct->LTDC_BackgroundBlueValue = 0x00;           /*!< Initialize the LTDC_BackgroundBlueValue member */
}

/**
  * @brief  Enables or disables the LTDC Controller.
  * @param  NewState: new state of the LTDC peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void LTDC_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable LTDC by setting LTDCEN bit */
    LTDC->GCR |= (uint32_t)LTDC_GCR_LTDCEN;
  }
  else
  {
    /* Disable LTDC by clearing LTDCEN bit */
    LTDC->GCR &= ~(uint32_t)LTDC_GCR_LTDCEN;
  }
}

/**
  * @brief  Enables or disables Dither.
  * @param  NewState: new state of the Dither.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void LTDC_DitherCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable Dither by setting DTEN bit */
    LTDC->GCR |= (uint32_t)LTDC_GCR_DTEN;
  }
  else
  {
    /* Disable Dither by clearing DTEN bit */
    LTDC->GCR &= ~(uint32_t)LTDC_GCR_DTEN;
  }
}

/**
  * @brief  Get the dither RGB width.
  * @param  LTDC_RGB_InitStruct: pointer to a LTDC_RGBTypeDef structure that contains
  *         the Dither RGB width.
  * @retval None
  */

LTDC_RGBTypeDef LTDC_GetRGBWidth(void)
{
  LTDC_RGBTypeDef LTDC_RGB_InitStruct;

  LTDC->GCR &= (uint32_t)GCR_MASK;

  LTDC_RGB_InitStruct.LTDC_BlueWidth = (uint32_t)((LTDC->GCR >> 4) & 0x7);
  LTDC_RGB_InitStruct.LTDC_GreenWidth = (uint32_t)((LTDC->GCR >> 8) & 0x7);
  LTDC_RGB_InitStruct.LTDC_RedWidth = (uint32_t)((LTDC->GCR >> 12) & 0x7);

  return LTDC_RGB_InitStruct;
}

/**
  * @brief  Fills each LTDC_RGBStruct member with its default value.
  * @param  LTDC_RGB_InitStruct: pointer to a LTDC_RGBTypeDef structure which will
  *         be initialized.
  * @retval None
  */

void LTDC_RGBStructInit(LTDC_RGBTypeDef* LTDC_RGB_InitStruct)
{
  LTDC_RGB_InitStruct->LTDC_BlueWidth = 0x02;
  LTDC_RGB_InitStruct->LTDC_GreenWidth = 0x02;
  LTDC_RGB_InitStruct->LTDC_RedWidth = 0x02;
}


/**
  * @brief  Define the position of the line interrupt .
  * @param  LTDC_LIPositionConfig: Line Interrupt Position.
  * @retval None
  */

void LTDC_LIPConfig(uint32_t LTDC_LIPositionConfig)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LIPOS(LTDC_LIPositionConfig));

  /* Sets the Line Interrupt position */
  LTDC->LIPCR = (uint32_t)LTDC_LIPositionConfig;
}

/**
  * @brief  reload layers registers with new parameters 
  * @param  LTDC_Reload: specifies the type of reload.
  *   This parameter can be one of the following values:
  *     @arg LTDC_IMReload: Vertical blanking reload.
  *     @arg LTDC_VBReload: Immediate reload.  
  * @retval None
  */

void LTDC_ReloadConfig(uint32_t LTDC_Reload)
{
  /* Check the parameters */
  assert_param(IS_LTDC_RELOAD(LTDC_Reload));

  /* Sets the Reload type */
  LTDC->SRCR = (uint32_t)LTDC_Reload;
}


/**
  * @brief  Initializes the LTDC Layer according to the specified parameters
  *         in the LTDC_LayerStruct.
  * @note   This function can be used only when the LTDC is disabled.
  * @param  LTDC_layerx: Select the layer to be configured, this parameter can be 
  *         one of the following values: LTDC_Layer1, LTDC_Layer2    
  * @param  LTDC_LayerStruct: pointer to a LTDC_LayerTypeDef structure that contains
  *         the configuration information for the specified LTDC peripheral.
  * @retval None
  */

void LTDC_LayerInit(LTDC_Layer_TypeDef* LTDC_Layerx, LTDC_Layer_InitTypeDef* LTDC_Layer_InitStruct)
{

  uint32_t whsppos = 0;
  uint32_t wvsppos = 0;
  uint32_t dcgreen = 0;
  uint32_t dcred = 0;
  uint32_t dcalpha = 0;
  uint32_t cfbp = 0;

/* Check the parameters */
  assert_param(IS_LTDC_Pixelformat(LTDC_Layer_InitStruct->LTDC_PixelFormat));
  assert_param(IS_LTDC_BlendingFactor1(LTDC_Layer_InitStruct->LTDC_BlendingFactor_1));
  assert_param(IS_LTDC_BlendingFactor2(LTDC_Layer_InitStruct->LTDC_BlendingFactor_2));
  assert_param(IS_LTDC_HCONFIGST(LTDC_Layer_InitStruct->LTDC_HorizontalStart));
  assert_param(IS_LTDC_HCONFIGSP(LTDC_Layer_InitStruct->LTDC_HorizontalStop));
  assert_param(IS_LTDC_VCONFIGST(LTDC_Layer_InitStruct->LTDC_VerticalStart));
  assert_param(IS_LTDC_VCONFIGSP(LTDC_Layer_InitStruct->LTDC_VerticalStop));  
  assert_param(IS_LTDC_DEFAULTCOLOR(LTDC_Layer_InitStruct->LTDC_DefaultColorBlue));
  assert_param(IS_LTDC_DEFAULTCOLOR(LTDC_Layer_InitStruct->LTDC_DefaultColorGreen));
  assert_param(IS_LTDC_DEFAULTCOLOR(LTDC_Layer_InitStruct->LTDC_DefaultColorRed));
  assert_param(IS_LTDC_DEFAULTCOLOR(LTDC_Layer_InitStruct->LTDC_DefaultColorAlpha));
  assert_param(IS_LTDC_CFBP(LTDC_Layer_InitStruct->LTDC_CFBPitch));
  assert_param(IS_LTDC_CFBLL(LTDC_Layer_InitStruct->LTDC_CFBLineLength));
  assert_param(IS_LTDC_CFBLNBR(LTDC_Layer_InitStruct->LTDC_CFBLineNumber));

  /* Configures the horizontal start and stop position */
  whsppos = LTDC_Layer_InitStruct->LTDC_HorizontalStop << 16;
  LTDC_Layerx->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
  LTDC_Layerx->WHPCR = (LTDC_Layer_InitStruct->LTDC_HorizontalStart | whsppos);

  /* Configures the vertical start and stop position */
  wvsppos = LTDC_Layer_InitStruct->LTDC_VerticalStop << 16;
  LTDC_Layerx->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
  LTDC_Layerx->WVPCR  = (LTDC_Layer_InitStruct->LTDC_VerticalStart | wvsppos);

  /* Specifies the pixel format */
  LTDC_Layerx->PFCR &= ~(LTDC_LxPFCR_PF);
  LTDC_Layerx->PFCR = (LTDC_Layer_InitStruct->LTDC_PixelFormat);

  /* Configures the default color values */
  dcgreen = (LTDC_Layer_InitStruct->LTDC_DefaultColorGreen << 8);
  dcred = (LTDC_Layer_InitStruct->LTDC_DefaultColorRed << 16);
  dcalpha = (LTDC_Layer_InitStruct->LTDC_DefaultColorAlpha << 24);
  LTDC_Layerx->DCCR &=  ~(LTDC_LxDCCR_DCBLUE | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCALPHA);
  LTDC_Layerx->DCCR = (LTDC_Layer_InitStruct->LTDC_DefaultColorBlue | dcgreen | \
                        dcred | dcalpha);

  /* Specifies the constant alpha value */      
  LTDC_Layerx->CACR &= ~(LTDC_LxCACR_CONSTA);
  LTDC_Layerx->CACR = (LTDC_Layer_InitStruct->LTDC_ConstantAlpha);

  /* Specifies the blending factors */
  LTDC_Layerx->BFCR &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
  LTDC_Layerx->BFCR = (LTDC_Layer_InitStruct->LTDC_BlendingFactor_1 | LTDC_Layer_InitStruct->LTDC_BlendingFactor_2);

  /* Configures the color frame buffer start address */
  LTDC_Layerx->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
  LTDC_Layerx->CFBAR = (LTDC_Layer_InitStruct->LTDC_CFBStartAdress);

  /* Configures the color frame buffer pitch in byte */
  cfbp = (LTDC_Layer_InitStruct->LTDC_CFBPitch << 16);
  LTDC_Layerx->CFBLR  &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
  LTDC_Layerx->CFBLR  = (LTDC_Layer_InitStruct->LTDC_CFBLineLength | cfbp);

  /* Configures the frame buffer line number */
  LTDC_Layerx->CFBLNR  &= ~(LTDC_LxCFBLNR_CFBLNBR);
  LTDC_Layerx->CFBLNR  = (LTDC_Layer_InitStruct->LTDC_CFBLineNumber);

}

/**
  * @brief  Fills each LTDC_Layer_InitStruct member with its default value.
  * @param  LTDC_Layer_InitStruct: pointer to a LTDC_LayerTypeDef structure which will
  *         be initialized.
  * @retval None
  */

void LTDC_LayerStructInit(LTDC_Layer_InitTypeDef * LTDC_Layer_InitStruct)
{
  /*--------------- Reset Layer structure parameters values -------------------*/

  /*!< Initialize the horizontal limit member */
  LTDC_Layer_InitStruct->LTDC_HorizontalStart = 0x00;
  LTDC_Layer_InitStruct->LTDC_HorizontalStop = 0x00;

  /*!< Initialize the vertical limit member */
  LTDC_Layer_InitStruct->LTDC_VerticalStart = 0x00;
  LTDC_Layer_InitStruct->LTDC_VerticalStop = 0x00;

  /*!< Initialize the pixel format member */
  LTDC_Layer_InitStruct->LTDC_PixelFormat = LTDC_Pixelformat_ARGB8888;

  /*!< Initialize the constant alpha value */
  LTDC_Layer_InitStruct->LTDC_ConstantAlpha = 0xFF;

  /*!< Initialize the default color values */
  LTDC_Layer_InitStruct->LTDC_DefaultColorBlue = 0x00;
  LTDC_Layer_InitStruct->LTDC_DefaultColorGreen = 0x00;
  LTDC_Layer_InitStruct->LTDC_DefaultColorRed = 0x00;
  LTDC_Layer_InitStruct->LTDC_DefaultColorAlpha = 0x00;

  /*!< Initialize the blending factors */
  LTDC_Layer_InitStruct->LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_PAxCA;
  LTDC_Layer_InitStruct->LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_PAxCA;

  /*!< Initialize the frame buffer start address */
  LTDC_Layer_InitStruct->LTDC_CFBStartAdress = 0x00;

  /*!< Initialize the frame buffer pitch and line length */
  LTDC_Layer_InitStruct->LTDC_CFBLineLength = 0x00;
  LTDC_Layer_InitStruct->LTDC_CFBPitch = 0x00;

  /*!< Initialize the frame buffer line number */
  LTDC_Layer_InitStruct->LTDC_CFBLineNumber = 0x00;
}


/**
  * @brief  Enables or disables the LTDC_Layer Controller.
  * @param  LTDC_layerx: Select the layer to be configured, this parameter can be 
  *         one of the following values: LTDC_Layer1, LTDC_Layer2
  * @param  NewState: new state of the LTDC_Layer peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void LTDC_LayerCmd(LTDC_Layer_TypeDef* LTDC_Layerx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable LTDC_Layer by setting LEN bit */
    LTDC_Layerx->CR |= (uint32_t)LTDC_LxCR_LEN;
  }
  else
  {
    /* Disable LTDC_Layer by clearing LEN bit */
    LTDC_Layerx->CR &= ~(uint32_t)LTDC_LxCR_LEN;
  }
}


/**
  * @brief  Get the current position.
  * @param  LTDC_Pos_InitStruct: pointer to a LTDC_PosTypeDef structure that contains
  *         the current position.
  * @retval None
  */

LTDC_PosTypeDef LTDC_GetPosStatus(void)
{
  LTDC_PosTypeDef LTDC_Pos_InitStruct;

  LTDC->CPSR &= ~(LTDC_CPSR_CYPOS | LTDC_CPSR_CXPOS);

  LTDC_Pos_InitStruct.LTDC_POSX = (uint32_t)(LTDC->CPSR >> 16);
  LTDC_Pos_InitStruct.LTDC_POSY = (uint32_t)(LTDC->CPSR & 0xFFFF);

  return LTDC_Pos_InitStruct;
}

/**
  * @brief  Fills each LTDC_Pos_InitStruct member with its default value.
  * @param  LTDC_Pos_InitStruct: pointer to a LTDC_PosTypeDef structure which will
  *         be initialized.
  * @retval None
  */

void LTDC_PosStructInit(LTDC_PosTypeDef* LTDC_Pos_InitStruct)
{
  LTDC_Pos_InitStruct->LTDC_POSX = 0x00;
  LTDC_Pos_InitStruct->LTDC_POSY = 0x00;
}

/**
  * @brief  Checks whether the specified LTDC's flag is set or not.
  * @param  LTDC_CD: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg LTDC_CD_VDES: vertical data enable current status.
  *     @arg LTDC_CD_HDES: horizontal data enable current status.
  *     @arg LTDC_CD_VSYNC:  Vertical Synchronization current status.
  *     @arg LTDC_CD_HSYNC:  Horizontal Synchronization current status.
  * @retval The new state of LTDC_CD (SET or RESET).
  */

FlagStatus LTDC_GetCDStatus(uint32_t LTDC_CD)
{
  FlagStatus bitstatus;

  /* Check the parameters */
  assert_param(IS_LTDC_GET_CD(LTDC_CD));

  if ((LTDC->CDSR & LTDC_CD) != (uint32_t)RESET)
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
  * @brief  Set and configure the color keying.
  * @param  LTDC_colorkeying_InitStruct: pointer to a LTDC_ColorKeying_InitTypeDef 
  *         structure that contains the color keying configuration.
  * @param  LTDC_layerx: Select the layer to be configured, this parameter can be 
  *         one of the following values: LTDC_Layer1, LTDC_Layer2   
  * @retval None
  */

void LTDC_ColorKeyingConfig(LTDC_Layer_TypeDef* LTDC_Layerx, LTDC_ColorKeying_InitTypeDef* LTDC_colorkeying_InitStruct, FunctionalState NewState)
{ 
  uint32_t ckgreen = 0;
  uint32_t ckred = 0;

  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_LTDC_CKEYING(LTDC_colorkeying_InitStruct->LTDC_ColorKeyBlue));
  assert_param(IS_LTDC_CKEYING(LTDC_colorkeying_InitStruct->LTDC_ColorKeyGreen));
  assert_param(IS_LTDC_CKEYING(LTDC_colorkeying_InitStruct->LTDC_ColorKeyRed));
  
  if (NewState != DISABLE)
  {
    /* Enable LTDC color keying by setting COLKEN bit */
    LTDC_Layerx->CR |= (uint32_t)LTDC_LxCR_COLKEN;
    
    /* Sets the color keying values */
    ckgreen = (LTDC_colorkeying_InitStruct->LTDC_ColorKeyGreen << 8);
    ckred = (LTDC_colorkeying_InitStruct->LTDC_ColorKeyRed << 16);
    LTDC_Layerx->CKCR  &= ~(LTDC_LxCKCR_CKBLUE | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKRED);
    LTDC_Layerx->CKCR |= (LTDC_colorkeying_InitStruct->LTDC_ColorKeyBlue | ckgreen | ckred);
  }
  else
  {
    /* Disable LTDC color keying by clearing COLKEN bit */
    LTDC_Layerx->CR &= ~(uint32_t)LTDC_LxCR_COLKEN;
  }
  
  /* Reload shadow register */
  LTDC->SRCR = LTDC_IMReload;
}

/**
  * @brief  Fills each LTDC_colorkeying_InitStruct member with its default value.
  * @param  LTDC_colorkeying_InitStruct: pointer to a LTDC_ColorKeying_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */

void LTDC_ColorKeyingStructInit(LTDC_ColorKeying_InitTypeDef* LTDC_colorkeying_InitStruct)
{
  /*!< Initialize the color keying values */
  LTDC_colorkeying_InitStruct->LTDC_ColorKeyBlue = 0x00;
  LTDC_colorkeying_InitStruct->LTDC_ColorKeyGreen = 0x00;
  LTDC_colorkeying_InitStruct->LTDC_ColorKeyRed = 0x00;
}


/**
  * @brief  Enables or disables CLUT.
  * @param  NewState: new state of CLUT.
  * @param  LTDC_layerx: Select the layer to be configured, this parameter can be 
  *         one of the following values: LTDC_Layer1, LTDC_Layer2  
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void LTDC_CLUTCmd(LTDC_Layer_TypeDef* LTDC_Layerx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable CLUT by setting CLUTEN bit */
    LTDC_Layerx->CR |= (uint32_t)LTDC_LxCR_CLUTEN;
  }
  else
  {
    /* Disable CLUT by clearing CLUTEN bit */
    LTDC_Layerx->CR &= ~(uint32_t)LTDC_LxCR_CLUTEN;
  }
  
  /* Reload shadow register */
  LTDC->SRCR = LTDC_IMReload;
}

/**
  * @brief  configure the CLUT.
  * @param  LTDC_CLUT_InitStruct: pointer to a LTDC_CLUT_InitTypeDef structure that contains
  *         the CLUT configuration.
  * @param  LTDC_layerx: Select the layer to be configured, this parameter can be 
  *         one of the following values: LTDC_Layer1, LTDC_Layer2   
  * @retval None
  */

void LTDC_CLUTInit(LTDC_Layer_TypeDef* LTDC_Layerx, LTDC_CLUT_InitTypeDef* LTDC_CLUT_InitStruct)
{  
  uint32_t green = 0;
  uint32_t red = 0;
  uint32_t clutadd = 0;

  /* Check the parameters */
  assert_param(IS_LTDC_CLUTWR(LTDC_CLUT_InitStruct->LTDC_CLUTAdress));
  assert_param(IS_LTDC_CLUTWR(LTDC_CLUT_InitStruct->LTDC_RedValue));
  assert_param(IS_LTDC_CLUTWR(LTDC_CLUT_InitStruct->LTDC_GreenValue));
  assert_param(IS_LTDC_CLUTWR(LTDC_CLUT_InitStruct->LTDC_BlueValue));
    
  /* Specifies the CLUT address and RGB value */
  green = (LTDC_CLUT_InitStruct->LTDC_GreenValue << 8);
  red = (LTDC_CLUT_InitStruct->LTDC_RedValue << 16);
  clutadd = (LTDC_CLUT_InitStruct->LTDC_CLUTAdress << 24);
  LTDC_Layerx->CLUTWR  = (clutadd | LTDC_CLUT_InitStruct->LTDC_BlueValue | \
                              green | red);
}

/**
  * @brief  Fills each LTDC_CLUT_InitStruct member with its default value.
  * @param  LTDC_CLUT_InitStruct: pointer to a LTDC_CLUT_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */

void LTDC_CLUTStructInit(LTDC_CLUT_InitTypeDef* LTDC_CLUT_InitStruct)
{
  /*!< Initialize the CLUT adress and RGB values */
  LTDC_CLUT_InitStruct->LTDC_CLUTAdress = 0x00;
  LTDC_CLUT_InitStruct->LTDC_BlueValue = 0x00;
  LTDC_CLUT_InitStruct->LTDC_GreenValue = 0x00;
  LTDC_CLUT_InitStruct->LTDC_RedValue = 0x00;
}


/**
  * @brief  reconfigure the layer position.
  * @param  OffsetX: horizontal offset from start active width .
  * @param  OffsetY: vertical offset from start active height.   
  * @param  LTDC_layerx: Select the layer to be configured, this parameter can be 
  *         one of the following values: LTDC_Layer1, LTDC_Layer2   
  * @retval Reload of the shadow registers values must be applied after layer 
  *         position reconfiguration.
  */

void LTDC_LayerPosition(LTDC_Layer_TypeDef* LTDC_Layerx, uint16_t OffsetX, uint16_t OffsetY)
{
  
  uint32_t tempreg, temp;
  uint32_t horizontal_start;
  uint32_t horizontal_stop;
  uint32_t vertical_start;
  uint32_t vertical_stop;
  
  LTDC_Layerx->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
  LTDC_Layerx->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
  
  /* Reconfigures the horizontal and vertical start position */
  tempreg = LTDC->BPCR;
  horizontal_start = (tempreg >> 16) + 1 + OffsetX;
  vertical_start = (tempreg & 0xFFFF) + 1 + OffsetY;
  
  /* Reconfigures the horizontal and vertical stop position */
  /* Get the number of byte per pixel */
  
  tempreg = LTDC_Layerx->PFCR;
  
  if (tempreg == LTDC_Pixelformat_ARGB8888)
  {
    temp = 4;
  }
  else if (tempreg == LTDC_Pixelformat_RGB888)
  {
    temp = 3;
  }
  else if ((tempreg == LTDC_Pixelformat_ARGB4444) || 
          (tempreg == LTDC_Pixelformat_RGB565)    ||  
          (tempreg == LTDC_Pixelformat_ARGB1555)  ||
          (tempreg == LTDC_Pixelformat_AL88))
  {
    temp = 2;  
  }
  else
  {
    temp = 1;
  }  
    
  tempreg = LTDC_Layerx->CFBLR;
  horizontal_stop = (((tempreg & 0x1FFF) - 3)/temp) + horizontal_start - 1;
  
  tempreg = LTDC_Layerx->CFBLNR;
  vertical_stop = (tempreg & 0x7FF) + vertical_start - 1;  
  
  LTDC_Layerx->WHPCR = horizontal_start | (horizontal_stop << 16);
  LTDC_Layerx->WVPCR = vertical_start | (vertical_stop << 16);  
}
  
/**
  * @brief  reconfigure constant alpha.
  * @param  ConstantAlpha: constant alpha value.
  * @param  LTDC_layerx: Select the layer to be configured, this parameter can be 
  *         one of the following values: LTDC_Layer1, LTDC_Layer2    
  * @retval Reload of the shadow registers values must be applied after constant 
  *         alpha reconfiguration.         
  */

void LTDC_LayerAlpha(LTDC_Layer_TypeDef* LTDC_Layerx, uint8_t ConstantAlpha)
{  
  /* reconfigure the constant alpha value */      
  LTDC_Layerx->CACR = ConstantAlpha;
}

/**
  * @brief  reconfigure layer address.
  * @param  Address: The color frame buffer start address.
  * @param  LTDC_layerx: Select the layer to be configured, this parameter can be 
  *         one of the following values: LTDC_Layer1, LTDC_Layer2     
  * @retval Reload of the shadow registers values must be applied after layer 
  *         address reconfiguration.
  */

void LTDC_LayerAddress(LTDC_Layer_TypeDef* LTDC_Layerx, uint32_t Address)
{
  /* Reconfigures the color frame buffer start address */
  LTDC_Layerx->CFBAR = Address;
}
  
/**
  * @brief  reconfigure layer size.
  * @param  Width: layer window width.
  * @param  Height: layer window height.   
  * @param  LTDC_layerx: Select the layer to be configured, this parameter can be 
  *         one of the following values: LTDC_Layer1, LTDC_Layer2   
  * @retval Reload of the shadow registers values must be applied after layer 
  *         size reconfiguration.
  */

void LTDC_LayerSize(LTDC_Layer_TypeDef* LTDC_Layerx, uint32_t Width, uint32_t Height)
{

  uint8_t temp;
  uint32_t tempreg;
  uint32_t horizontal_start;
  uint32_t horizontal_stop;
  uint32_t vertical_start;
  uint32_t vertical_stop;  
  
  tempreg = LTDC_Layerx->PFCR;
  
  if (tempreg == LTDC_Pixelformat_ARGB8888)
  {
    temp = 4;
  }
  else if (tempreg == LTDC_Pixelformat_RGB888)
  {
    temp = 3;
  }
  else if ((tempreg == LTDC_Pixelformat_ARGB4444) || \
          (tempreg == LTDC_Pixelformat_RGB565)    || \
          (tempreg == LTDC_Pixelformat_ARGB1555)  || \
          (tempreg == LTDC_Pixelformat_AL88))
  {
    temp = 2;  
  }
  else
  {
    temp = 1;
  }

  /* update horizontal and vertical stop */
  tempreg = LTDC_Layerx->WHPCR;
  horizontal_start = (tempreg & 0x1FFF);
  horizontal_stop = Width + horizontal_start - 1;  

  tempreg = LTDC_Layerx->WVPCR;
  vertical_start = (tempreg & 0x1FFF);
  vertical_stop = Height + vertical_start - 1;  
  
  LTDC_Layerx->WHPCR = horizontal_start | (horizontal_stop << 16);
  LTDC_Layerx->WVPCR = vertical_start | (vertical_stop << 16);  

  /* Reconfigures the color frame buffer pitch in byte */
  LTDC_Layerx->CFBLR  = ((Width * temp) << 16) | ((Width * temp) + 3);  

  /* Reconfigures the frame buffer line number */
  LTDC_Layerx->CFBLNR  = Height;  
  
}

/**
  * @brief  reconfigure layer pixel format.
  * @param  PixelFormat: reconfigure the pixel format, this parameter can be 
  *         one of the following values:@ref LTDC_Pixelformat.   
  * @param  LTDC_layerx: Select the layer to be configured, this parameter can be 
  *         one of the following values: LTDC_Layer1, LTDC_Layer2   
  * @retval Reload of the shadow registers values must be applied after layer 
  *         pixel format reconfiguration.
  */

void LTDC_LayerPixelFormat(LTDC_Layer_TypeDef* LTDC_Layerx, uint32_t PixelFormat)
{

  uint8_t temp;
  uint32_t tempreg;
  
  tempreg = LTDC_Layerx->PFCR;
  
  if (tempreg == LTDC_Pixelformat_ARGB8888)
  {
    temp = 4;
  }
  else if (tempreg == LTDC_Pixelformat_RGB888)
  {
    temp = 3;
  }
  else if ((tempreg == LTDC_Pixelformat_ARGB4444) || \
          (tempreg == LTDC_Pixelformat_RGB565)    || \
          (tempreg == LTDC_Pixelformat_ARGB1555)  || \
          (tempreg == LTDC_Pixelformat_AL88))  
  {
    temp = 2;  
  }
  else
  {
    temp = 1;
  }
  
  tempreg = (LTDC_Layerx->CFBLR >> 16);
  tempreg = (tempreg / temp); 
  
  if (PixelFormat == LTDC_Pixelformat_ARGB8888)
  {
    temp = 4;
  }
  else if (PixelFormat == LTDC_Pixelformat_RGB888)
  {
    temp = 3;
  }
  else if ((PixelFormat == LTDC_Pixelformat_ARGB4444) || \
          (PixelFormat == LTDC_Pixelformat_RGB565)    || \
          (PixelFormat == LTDC_Pixelformat_ARGB1555)  || \
          (PixelFormat == LTDC_Pixelformat_AL88))
  {
    temp = 2;  
  }
  else
  {
    temp = 1;
  }
  
  /* Reconfigures the color frame buffer pitch in byte */
  LTDC_Layerx->CFBLR  = ((tempreg * temp) << 16) | ((tempreg * temp) + 3);  

  /* Reconfigures the color frame buffer start address */
  LTDC_Layerx->PFCR = PixelFormat;
    
}
    
/**
  * @}
  */

/** @defgroup LTDC_Group2 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================

    [..] This section provides functions allowing to configure the LTDC Interrupts 
         and to get the status and clear flags and Interrupts pending bits.
  
    [..] The LTDC provides 4 Interrupts sources and 4 Flags
    
    *** Flags ***
    =============
    [..]
      (+) LTDC_FLAG_LI:   Line Interrupt flag.
      (+) LTDC_FLAG_FU:   FIFO Underrun Interrupt flag.
      (+) LTDC_FLAG_TERR: Transfer Error Interrupt flag.
      (+) LTDC_FLAG_RR:   Register Reload interrupt flag.
      
    *** Interrupts ***
    ==================
    [..]
      (+) LTDC_IT_LI: Line Interrupt is generated when a programmed line 
                      is reached. The line interrupt position is programmed in 
                      the LTDC_LIPR register.
      (+) LTDC_IT_FU: FIFO Underrun interrupt is generated when a pixel is requested 
                      from an empty layer FIFO
      (+) LTDC_IT_TERR: Transfer Error interrupt is generated when an AHB bus 
                        error occurs during data transfer.
      (+) LTDC_IT_RR: Register Reload interrupt is generated when the shadow 
                      registers reload was performed during the vertical blanking 
                      period.
               
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified LTDC's interrupts.
  * @param  LTDC_IT: specifies the LTDC interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg LTDC_IT_LI: Line Interrupt Enable.
  *     @arg LTDC_IT_FU: FIFO Underrun Interrupt Enable.
  *     @arg LTDC_IT_TERR: Transfer Error Interrupt Enable.
  *     @arg LTDC_IT_RR: Register Reload interrupt enable.  
  * @param NewState: new state of the specified LTDC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LTDC_ITConfig(uint32_t LTDC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_LTDC_IT(LTDC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    LTDC->IER |= LTDC_IT;
  }
  else
  {
    LTDC->IER &= (uint32_t)~LTDC_IT;
  }
}

/**
  * @brief  Checks whether the specified LTDC's flag is set or not.
  * @param  LTDC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg LTDC_FLAG_LI:    Line Interrupt flag.
  *     @arg LTDC_FLAG_FU:   FIFO Underrun Interrupt flag.
  *     @arg LTDC_FLAG_TERR: Transfer Error Interrupt flag.
  *     @arg LTDC_FLAG_RR:   Register Reload interrupt flag.
  * @retval The new state of LTDC_FLAG (SET or RESET).
  */
FlagStatus LTDC_GetFlagStatus(uint32_t LTDC_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_LTDC_FLAG(LTDC_FLAG));

  if ((LTDC->ISR & LTDC_FLAG) != (uint32_t)RESET)
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
  * @brief  Clears the LTDC's pending flags.
  * @param  LTDC_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg LTDC_FLAG_LI:    Line Interrupt flag.
  *     @arg LTDC_FLAG_FU:   FIFO Underrun Interrupt flag.
  *     @arg LTDC_FLAG_TERR: Transfer Error Interrupt flag.
  *     @arg LTDC_FLAG_RR:   Register Reload interrupt flag.  
  * @retval None
  */
void LTDC_ClearFlag(uint32_t LTDC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_LTDC_FLAG(LTDC_FLAG));

  /* Clear the corresponding LTDC flag */
  LTDC->ICR = (uint32_t)LTDC_FLAG;
}

/**
  * @brief  Checks whether the specified LTDC's interrupt has occurred or not.
  * @param  LTDC_IT: specifies the LTDC interrupts sources to check.
  *   This parameter can be one of the following values:
  *     @arg LTDC_IT_LI:    Line Interrupt Enable.
  *     @arg LTDC_IT_FU:   FIFO Underrun Interrupt Enable.
  *     @arg LTDC_IT_TERR: Transfer Error Interrupt Enable.
  *     @arg LTDC_IT_RR:   Register Reload interrupt Enable.
  * @retval The new state of the LTDC_IT (SET or RESET).
  */
ITStatus LTDC_GetITStatus(uint32_t LTDC_IT)
{
  ITStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_LTDC_IT(LTDC_IT));

  if ((LTDC->ISR & LTDC_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  if (((LTDC->IER & LTDC_IT) != (uint32_t)RESET) && (bitstatus != (uint32_t)RESET))
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
  * @brief  Clears the LTDC's interrupt pending bits.
  * @param  LTDC_IT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg LTDC_IT_LIE:    Line Interrupt.
  *     @arg LTDC_IT_FUIE:   FIFO Underrun Interrupt.
  *     @arg LTDC_IT_TERRIE: Transfer Error Interrupt.
  *     @arg LTDC_IT_RRIE:   Register Reload interrupt.
  * @retval None
  */
void LTDC_ClearITPendingBit(uint32_t LTDC_IT)
{
  /* Check the parameters */
  assert_param(IS_LTDC_IT(LTDC_IT));

  /* Clear the corresponding LTDC Interrupt */
  LTDC->ICR = (uint32_t)LTDC_IT;
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
