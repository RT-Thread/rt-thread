/**
  ******************************************************************************
  * @file    stm32f4xx_dma2d.h
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    08-November-2013
  * @brief   This file contains all the functions prototypes for the DMA2D firmware 
  *          library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_DMA2D_H
#define __STM32F4xx_DMA2D_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA2D
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
 
/** 
  * @brief  DMA2D Init structure definition  
  */

typedef struct
{
  uint32_t DMA2D_Mode;                           /*!< configures the DMA2D transfer mode.
                                                 This parameter can be one value of @ref DMA2D_MODE */
  
  uint32_t DMA2D_CMode;                          /*!< configures the color format of the output image.
                                                 This parameter can be one value of @ref DMA2D_CMODE */

  uint32_t DMA2D_OutputBlue;                     /*!< configures the blue value of the output image. 
                                                 This parameter must range:
                                                 - from 0x00 to 0xFF if ARGB8888 color mode is slected
                                                 - from 0x00 to 0xFF if RGB888 color mode is slected
                                                 - from 0x00 to 0x1F if RGB565 color mode is slected
                                                 - from 0x00 to 0x1F if ARGB1555 color mode is slected
                                                 - from 0x00 to 0x0F if ARGB4444 color mode is slected  */

  uint32_t DMA2D_OutputGreen;                    /*!< configures the green value of the output image. 
                                                 This parameter must range:
                                                 - from 0x00 to 0xFF if ARGB8888 color mode is slected
                                                 - from 0x00 to 0xFF if RGB888 color mode is slected
                                                 - from 0x00 to 0x2F if RGB565 color mode is slected
                                                 - from 0x00 to 0x1F if ARGB1555 color mode is slected
                                                 - from 0x00 to 0x0F if ARGB4444 color mode is slected  */
            
  uint32_t DMA2D_OutputRed;                      /*!< configures the red value of the output image. 
                                                 This parameter must range:
                                                 - from 0x00 to 0xFF if ARGB8888 color mode is slected
                                                 - from 0x00 to 0xFF if RGB888 color mode is slected
                                                 - from 0x00 to 0x1F if RGB565 color mode is slected
                                                 - from 0x00 to 0x1F if ARGB1555 color mode is slected
                                                 - from 0x00 to 0x0F if ARGB4444 color mode is slected  */
  
  uint32_t DMA2D_OutputAlpha;                    /*!< configures the alpha channel of the output color. 
                                                 This parameter must range:
                                                 - from 0x00 to 0xFF if ARGB8888 color mode is slected
                                                 - from 0x00 to 0x01 if ARGB1555 color mode is slected
                                                 - from 0x00 to 0x0F if ARGB4444 color mode is slected  */

  uint32_t DMA2D_OutputMemoryAdd;                /*!< Specifies the memory address. This parameter 
                                                 must be range from 0x00000000 to 0xFFFFFFFF. */

  uint32_t DMA2D_OutputOffset;                   /*!< Specifies the Offset value. This parameter must be range from
                                                 0x0000 to 0x3FFF. */

  uint32_t DMA2D_NumberOfLine;                   /*!< Configures the number of line of the area to be transfered.
                                                 This parameter must range from 0x0000 to 0xFFFF */
            
  uint32_t DMA2D_PixelPerLine;                   /*!< Configures the number pixel per line of the area to be transfered.
                                                 This parameter must range from 0x0000 to 0x3FFF */
} DMA2D_InitTypeDef;



typedef struct
{
  uint32_t DMA2D_FGMA;                           /*!< configures the DMA2D foreground memory address.
                                                 This parameter must be range from 0x00000000 to 0xFFFFFFFF. */
  
  uint32_t DMA2D_FGO;                            /*!< configures the DMA2D foreground offset.
                                                 This parameter must be range from 0x0000 to 0x3FFF. */

  uint32_t DMA2D_FGCM;                           /*!< configures the DMA2D foreground color mode . 
                                                 This parameter can be one value of @ref DMA2D_FGCM */

  uint32_t DMA2D_FG_CLUT_CM;                     /*!< configures the DMA2D foreground CLUT color mode. 
                                                 This parameter can be one value of @ref DMA2D_FG_CLUT_CM */
            
  uint32_t DMA2D_FG_CLUT_SIZE;                   /*!< configures the DMA2D foreground CLUT size. 
                                                 This parameter must range from 0x00 to 0xFF. */
  
  uint32_t DMA2D_FGPFC_ALPHA_MODE;               /*!< configures the DMA2D foreground alpha mode. 
                                                 This parameter can be one value of @ref DMA2D_FGPFC_ALPHA_MODE */

  uint32_t DMA2D_FGPFC_ALPHA_VALUE;              /*!< Specifies the DMA2D foreground alpha value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_FGC_BLUE;                       /*!< Specifies the DMA2D foreground blue value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_FGC_GREEN;                      /*!< Specifies the DMA2D foreground green value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_FGC_RED;                        /*!< Specifies the DMA2D foreground red value 
                                                 must be range from 0x00 to 0xFF. */
            
  uint32_t DMA2D_FGCMAR;                         /*!< Configures the DMA2D foreground CLUT memory address.
                                                 This parameter must range from 0x00000000 to 0xFFFFFFFF. */
} DMA2D_FG_InitTypeDef;


typedef struct
{
  uint32_t DMA2D_BGMA;                           /*!< configures the DMA2D background memory address.
                                                 This parameter must be range from 0x00000000 to 0xFFFFFFFF. */
  
  uint32_t DMA2D_BGO;                            /*!< configures the DMA2D background offset.
                                                 This parameter must be range from 0x0000 to 0x3FFF. */

  uint32_t DMA2D_BGCM;                           /*!< configures the DMA2D background color mode . 
                                                 This parameter can be one value of @ref DMA2D_FGCM */

  uint32_t DMA2D_BG_CLUT_CM;                     /*!< configures the DMA2D background CLUT color mode. 
                                                 This parameter can be one value of @ref DMA2D_FG_CLUT_CM */
            
  uint32_t DMA2D_BG_CLUT_SIZE;                   /*!< configures the DMA2D background CLUT size. 
                                                 This parameter must range from 0x00 to 0xFF. */
  
  uint32_t DMA2D_BGPFC_ALPHA_MODE;               /*!< configures the DMA2D background alpha mode. 
                                                 This parameter can be one value of @ref DMA2D_FGPFC_ALPHA_MODE */

  uint32_t DMA2D_BGPFC_ALPHA_VALUE;              /*!< Specifies the DMA2D background alpha value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_BGC_BLUE;                       /*!< Specifies the DMA2D background blue value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_BGC_GREEN;                      /*!< Specifies the DMA2D background green value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_BGC_RED;                        /*!< Specifies the DMA2D background red value 
                                                 must be range from 0x00 to 0xFF. */
            
  uint32_t DMA2D_BGCMAR;                         /*!< Configures the DMA2D background CLUT memory address.
                                                 This parameter must range from 0x00000000 to 0xFFFFFFFF. */
} DMA2D_BG_InitTypeDef;



/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA2D_Exported_Constants
  * @{
  */  

/** @defgroup DMA2D_MODE 
  * @{
  */


#define DMA2D_M2M                            ((uint32_t)0x00000000)
#define DMA2D_M2M_PFC                        ((uint32_t)0x00010000)
#define DMA2D_M2M_BLEND                      ((uint32_t)0x00020000)
#define DMA2D_R2M                            ((uint32_t)0x00030000)

#define IS_DMA2D_MODE(MODE) (((MODE) == DMA2D_M2M) || ((MODE) == DMA2D_M2M_PFC) || \
                             ((MODE) == DMA2D_M2M_BLEND) || ((MODE) == DMA2D_R2M))


/**
  * @}
  */  

/** @defgroup DMA2D_CMODE 
  * @{
  */
#define DMA2D_ARGB8888                       ((uint32_t)0x00000000)
#define DMA2D_RGB888                         ((uint32_t)0x00000001)
#define DMA2D_RGB565                         ((uint32_t)0x00000002)
#define DMA2D_ARGB1555                       ((uint32_t)0x00000003)
#define DMA2D_ARGB4444                       ((uint32_t)0x00000004)

#define IS_DMA2D_CMODE(MODE_ARGB) (((MODE_ARGB) == DMA2D_ARGB8888) || ((MODE_ARGB) == DMA2D_RGB888) || \
                                   ((MODE_ARGB) == DMA2D_RGB565) || ((MODE_ARGB) == DMA2D_ARGB1555) || \
                                   ((MODE_ARGB) == DMA2D_ARGB4444))


/**
  * @}
  */  

/** @defgroup DMA2D_OUTPUT_COLOR 
  * @{
  */
#define DMA2D_Output_Color                 ((uint32_t)0x000000FF)

#define IS_DMA2D_OGREEN(OGREEN) ((OGREEN) <= DMA2D_Output_Color)
#define IS_DMA2D_ORED(ORED)     ((ORED) <= DMA2D_Output_Color)
#define IS_DMA2D_OBLUE(OBLUE)   ((OBLUE) <= DMA2D_Output_Color)
#define IS_DMA2D_OALPHA(OALPHA) ((OALPHA) <= DMA2D_Output_Color)

/**
  * @}
  */  

/** @defgroup DMA2D_OUTPUT_OFFSET 
  * @{
  */
#define DMA2D_OUTPUT_OFFSET      ((uint32_t)0x00003FFF)

#define IS_DMA2D_OUTPUT_OFFSET(OOFFSET) ((OOFFSET) <= DMA2D_OUTPUT_OFFSET)


/**
  * @}
  */  

/** @defgroup DMA2D_SIZE 
  * @{
  */

#define DMA2D_pixel          ((uint32_t)0x00003FFF)
#define DMA2D_Line           ((uint32_t)0x0000FFFF)

#define IS_DMA2D_LINE(LINE)  ((LINE) <= DMA2D_Line)
#define IS_DMA2D_PIXEL(PIXEL) ((PIXEL) <= DMA2D_pixel)


/**
  * @}
  */  

/** @defgroup DMA2D_OFFSET
  * @{
  */
#define OFFSET               ((uint32_t)0x00003FFF)

#define IS_DMA2D_FGO(FGO)  ((FGO) <= OFFSET)

#define IS_DMA2D_BGO(BGO)  ((BGO) <= OFFSET) 

/**
  * @}
  */  


/** @defgroup DMA2D_FGCM
  * @{
  */

#define CM_ARGB8888        ((uint32_t)0x00000000)
#define CM_RGB888          ((uint32_t)0x00000001)
#define CM_RGB565          ((uint32_t)0x00000002)
#define CM_ARGB1555        ((uint32_t)0x00000003)
#define CM_ARGB4444        ((uint32_t)0x00000004)
#define CM_L8              ((uint32_t)0x00000005)
#define CM_AL44            ((uint32_t)0x00000006)
#define CM_AL88            ((uint32_t)0x00000007)
#define CM_L4              ((uint32_t)0x00000008)
#define CM_A8              ((uint32_t)0x00000009)
#define CM_A4              ((uint32_t)0x0000000A)

#define IS_DMA2D_FGCM(FGCM) (((FGCM) == CM_ARGB8888) || ((FGCM) == CM_RGB888) || \
                             ((FGCM) == CM_RGB565) || ((FGCM) == CM_ARGB1555) || \
                             ((FGCM) == CM_ARGB4444) || ((FGCM) == CM_L8) || \
                             ((FGCM) == CM_AL44) || ((FGCM) == CM_AL88) || \
                             ((FGCM) == CM_L4) || ((FGCM) == CM_A8) || \
                             ((FGCM) == CM_A4))

#define IS_DMA2D_BGCM(BGCM) (((BGCM) == CM_ARGB8888) || ((BGCM) == CM_RGB888) || \
                             ((BGCM) == CM_RGB565) || ((BGCM) == CM_ARGB1555) || \
                             ((BGCM) == CM_ARGB4444) || ((BGCM) == CM_L8) || \
                             ((BGCM) == CM_AL44) || ((BGCM) == CM_AL88) || \
                             ((BGCM) == CM_L4) || ((BGCM) == CM_A8) || \
                             ((BGCM) == CM_A4))

/**
  * @}
  */

/** @defgroup DMA2D_FG_CLUT_CM
  * @{
  */

#define CLUT_CM_ARGB8888        ((uint32_t)0x00000000)
#define CLUT_CM_RGB888          ((uint32_t)0x00000001)

#define IS_DMA2D_FG_CLUT_CM(FG_CLUT_CM) (((FG_CLUT_CM) == CLUT_CM_ARGB8888) || ((FG_CLUT_CM) == CLUT_CM_RGB888))

#define IS_DMA2D_BG_CLUT_CM(BG_CLUT_CM) (((BG_CLUT_CM) == CLUT_CM_ARGB8888) || ((BG_CLUT_CM) == CLUT_CM_RGB888))

/**
  * @}
  */

/** @defgroup DMA2D_FG_COLOR_VALUE
  * @{
  */

#define COLOR_VALUE             ((uint32_t)0x000000FF)

#define IS_DMA2D_FG_CLUT_SIZE(FG_CLUT_SIZE) ((FG_CLUT_SIZE) <= COLOR_VALUE)

#define IS_DMA2D_FG_ALPHA_VALUE(FG_ALPHA_VALUE) ((FG_ALPHA_VALUE) <= COLOR_VALUE)
#define IS_DMA2D_FGC_BLUE(FGC_BLUE) ((FGC_BLUE) <= COLOR_VALUE)
#define IS_DMA2D_FGC_GREEN(FGC_GREEN) ((FGC_GREEN) <= COLOR_VALUE)
#define IS_DMA2D_FGC_RED(FGC_RED) ((FGC_RED) <= COLOR_VALUE)

#define IS_DMA2D_BG_CLUT_SIZE(BG_CLUT_SIZE) ((BG_CLUT_SIZE) <= COLOR_VALUE)

#define IS_DMA2D_BG_ALPHA_VALUE(BG_ALPHA_VALUE) ((BG_ALPHA_VALUE) <= COLOR_VALUE)
#define IS_DMA2D_BGC_BLUE(BGC_BLUE) ((BGC_BLUE) <= COLOR_VALUE)
#define IS_DMA2D_BGC_GREEN(BGC_GREEN) ((BGC_GREEN) <= COLOR_VALUE)
#define IS_DMA2D_BGC_RED(BGC_RED) ((BGC_RED) <= COLOR_VALUE)

/**
  * @}
  */

/** DMA2D_FGPFC_ALPHA_MODE
  * @{
  */

#define NO_MODIF_ALPHA_VALUE       ((uint32_t)0x00000000)
#define REPLACE_ALPHA_VALUE        ((uint32_t)0x00000001)
#define COMBINE_ALPHA_VALUE        ((uint32_t)0x00000002)

#define IS_DMA2D_FG_ALPHA_MODE(FG_ALPHA_MODE) (((FG_ALPHA_MODE) ==  NO_MODIF_ALPHA_VALUE) || \
                                              ((FG_ALPHA_MODE) == REPLACE_ALPHA_VALUE) || \
                                              ((FG_ALPHA_MODE) == COMBINE_ALPHA_VALUE))

#define IS_DMA2D_BG_ALPHA_MODE(BG_ALPHA_MODE) (((BG_ALPHA_MODE) ==  NO_MODIF_ALPHA_VALUE) || \
                                              ((BG_ALPHA_MODE) == REPLACE_ALPHA_VALUE) || \
                                              ((BG_ALPHA_MODE) == COMBINE_ALPHA_VALUE))

/**
  * @}
  */

/** @defgroup DMA2D_Interrupts 
  * @{
  */

#define DMA2D_IT_CE                      DMA2D_CR_CEIE
#define DMA2D_IT_CTC                     DMA2D_CR_CTCIE
#define DMA2D_IT_CAE                     DMA2D_CR_CAEIE
#define DMA2D_IT_TW                      DMA2D_CR_TWIE
#define DMA2D_IT_TC                      DMA2D_CR_TCIE
#define DMA2D_IT_TE                      DMA2D_CR_TEIE

#define IS_DMA2D_IT(IT) (((IT) == DMA2D_IT_CTC) || ((IT) == DMA2D_IT_CAE) || \
                        ((IT) == DMA2D_IT_TW) || ((IT) == DMA2D_IT_TC) || \
                        ((IT) == DMA2D_IT_TE) || ((IT) == DMA2D_IT_CE))

/**
  * @}
  */
      
/** @defgroup DMA2D_Flag 
  * @{
  */

#define DMA2D_FLAG_CE                      DMA2D_ISR_CEIF
#define DMA2D_FLAG_CTC                     DMA2D_ISR_CTCIF
#define DMA2D_FLAG_CAE                     DMA2D_ISR_CAEIF
#define DMA2D_FLAG_TW                      DMA2D_ISR_TWIF
#define DMA2D_FLAG_TC                      DMA2D_ISR_TCIF
#define DMA2D_FLAG_TE                      DMA2D_ISR_TEIF


#define IS_DMA2D_GET_FLAG(FLAG) (((FLAG) == DMA2D_FLAG_CTC) || ((FLAG) == DMA2D_FLAG_CAE) || \
                                ((FLAG) == DMA2D_FLAG_TW) || ((FLAG) == DMA2D_FLAG_TC) || \
                                ((FLAG) == DMA2D_FLAG_TE) || ((FLAG) == DMA2D_FLAG_CE)) 


/**
  * @}
  */
      
/** @defgroup DMA2D_DeadTime 
  * @{
  */

#define DEADTIME                  ((uint32_t)0x000000FF)
  
#define IS_DMA2D_DEAD_TIME(DEAD_TIME) ((DEAD_TIME) <= DEADTIME)


#define LINE_WATERMARK            DMA2D_LWR_LW

#define IS_DMA2D_LineWatermark(LineWatermark) ((LineWatermark) <= LINE_WATERMARK)

/**
  * @}
  */
  
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the DMA2D configuration to the default reset state *****/
void DMA2D_DeInit(void);

/* Initialization and Configuration functions *********************************/
void DMA2D_Init(DMA2D_InitTypeDef* DMA2D_InitStruct);
void DMA2D_StructInit(DMA2D_InitTypeDef* DMA2D_InitStruct);
void DMA2D_StartTransfer(void);
void DMA2D_AbortTransfer(void);
void DMA2D_Suspend(FunctionalState NewState);
void DMA2D_FGConfig(DMA2D_FG_InitTypeDef* DMA2D_FG_InitStruct);
void DMA2D_FG_StructInit(DMA2D_FG_InitTypeDef* DMA2D_FG_InitStruct);
void DMA2D_BGConfig(DMA2D_BG_InitTypeDef* DMA2D_BG_InitStruct);
void DMA2D_BG_StructInit(DMA2D_BG_InitTypeDef* DMA2D_BG_InitStruct);
void DMA2D_FGStart(FunctionalState NewState);
void DMA2D_BGStart(FunctionalState NewState);
void DMA2D_DeadTimeConfig(uint32_t DMA2D_DeadTime, FunctionalState NewState);
void DMA2D_LineWatermarkConfig(uint32_t DMA2D_LWatermarkConfig);

/* Interrupts and flags management functions **********************************/
void DMA2D_ITConfig(uint32_t DMA2D_IT, FunctionalState NewState);
FlagStatus DMA2D_GetFlagStatus(uint32_t DMA2D_FLAG);
void DMA2D_ClearFlag(uint32_t DMA2D_FLAG);
ITStatus DMA2D_GetITStatus(uint32_t DMA2D_IT);
void DMA2D_ClearITPendingBit(uint32_t DMA2D_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_DMA2D_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
