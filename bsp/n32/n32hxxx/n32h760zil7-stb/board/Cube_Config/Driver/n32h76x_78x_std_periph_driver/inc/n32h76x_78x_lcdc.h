/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_lcdc.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76x_78x_LCDC_H
#define __N32H76x_78x_LCDC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"

/*** LCDC Structure Definition Start ***/

/** LCDC Init structure definition is used with LCDC. **/
typedef struct
{
    uint32_t LCDC_HSPolarity;                /* configures the horizontal synchronization polarity. */

    uint32_t LCDC_VSPolarity;                /* configures the vertical synchronization polarity. */

    uint32_t LCDC_DEPolarity;                /* configures the data enable polarity. */

    uint32_t LCDC_PCPolarity;                /* configures the pixel clock polarity.  */

    uint32_t LCDC_HorizontalSync;            /* configures the number of Horizontal synchronization width. */

    uint32_t LCDC_VerticalSync;              /* configures the number of Vertical synchronization height. */

    uint32_t LCDC_AccumulatedHBP;            /* configures the accumulated horizontal back porch width. */

    uint32_t LCDC_AccumulatedVBP;            /* configures the accumulated vertical back porch height. */

    uint32_t LCDC_AccumulatedActiveW;        /* configures the accumulated active width. */

    uint32_t LCDC_AccumulatedActiveH;        /* configures the accumulated active height. */

    uint32_t LCDC_TotalWidth;                /* configures the total width. */

    uint32_t LCDC_TotalHeight;               /* configures the total height. */

    uint32_t LCDC_BackgroundRedValue;        /* configures the background red value. */

    uint32_t LCDC_BackgroundGreenValue;      /* configures the background green value. */ 

    uint32_t LCDC_BackgroundBlueValue;       /* configures the background blue value. */
} LCDC_InitType;

typedef struct
{
    uint32_t LCDC_HorizontalStart;            /* Configures the window horizontal start Position. */
    
    uint32_t LCDC_HorizontalStop;             /* Configures the window horizontal stop Position. */
    
    uint32_t LCDC_HorizontalScalerStop;       /* Configures the scaler window horizontal stop Position. */    

    uint32_t LCDC_VerticalStart;              /* Configures the window vertical start Position. */

    uint32_t LCDC_VerticalStop;               /* Configures the window vertical stop Position. */
 
    uint32_t LCDC_VerticalScalerStop;         /* Configures the scaler window vertical stop Position. */      
    
    uint32_t LCDC_PixelFormat;                /* Specifies the pixel format. */
    
    uint32_t LCDC_ConstantAlpha;              /* Specifies the constant alpha used for blending. */

    uint32_t LCDC_DefaultAlpha;               /* Configures the default alpha value. */

    uint32_t LCDC_BlendingFactor1;            /* Select the blending factor 1. */

    uint32_t LCDC_BlendingFactor2;            /* Select the blending factor 2. */

    uint32_t LCDC_CFBStartAdress;             /* Configures the color frame buffer address. */

    uint32_t LCDC_AFB0StartAdress;            /* Configures the Auxiliary frame buffer 0 address. */

    uint32_t LCDC_AFB1StartAdress;            /* Configures the Auxiliary frame buffer 1 address. */
    
    uint32_t LCDC_CFBLineLength;              /* Configures the color frame buffer line length. */    
    
    uint32_t LCDC_CFBLineNumber;              /* Configures the number of line in frame buffer. */      

    uint32_t LCDC_CFBPitch;                   /* Configures the color frame buffer pitch in bytes. */ 
    
    uint32_t LCDC_DefaultColorBlue;           /* Configures the default blue value. */     

    uint32_t LCDC_DefaultColorGreen;          /* Configures the default green value. */   
    
    uint32_t LCDC_DefaultColorRed;            /* Configures the default red value. */   
} LCDC_Layer_InitType;

typedef struct
{
    uint32_t LCDC_Blue;                        /* Blue width */
    
    uint32_t LCDC_Green;                       /* Green width */
    
    uint32_t LCDC_Red;                         /* Red width */
}LCDC_RGBType;

typedef struct
{
  uint32_t LCDC_POSX;                           /*  Current X Position */
  uint32_t LCDC_POSY;                           /*  Current Y Position */
} LCDC_PosType;

typedef struct
{
  uint32_t LCDC_ColorKeyBlue;               	/* Configures the color key blue value. 
													This parameter must range from 0x00 to 0xFF. */

  uint32_t LCDC_ColorKeyGreen;              	/* Configures the color key green value. 
													This parameter must range from 0x00 to 0xFF. */
            
  uint32_t LCDC_ColorKeyRed;                	/* Configures the color key red value. 
													This parameter must range from 0x00 to 0xFF. */
} LCDC_ColorKeying_InitType;


typedef struct
{
  uint32_t LCDC_CLUTAdress;                 	/* Configures the CLUT address.
													This parameter must range from 0x00 to 0xFF. */

  uint32_t LCDC_RedValue;                  	  	/* Configures the red value.
													This parameter must range from 0x00 to 0xFF. */
	
  uint32_t LCDC_GreenValue;                 	/* Configures the green value. 
													This parameter must range from 0x00 to 0xFF. */

  uint32_t LCDC_BlueValue;                  	/* Configures the blue value. 
													This parameter must range from 0x00 to 0xFF. */
} LCDC_CLUT_InitType;

/*** LCDC Structure Definition End ***/

/*** LCDC Macro Definition Start ***/

/** LCDC register bit mask definition **/
#define LCDC_REG_BIT_MASK                     ((uint32_t)0x00000000)

/** Horizontal Synchronization Polarity **/
#define LCDC_HSPolarity_LOW                   (LCDC_REG_BIT_MASK)              
#define LCDC_HSPolarity_HIGH                  (LCDC_GCTRL_HSPOL)

/** Vertical Synchronization Polarity **/
#define LCDC_VSPolarity_LOW                   (LCDC_REG_BIT_MASK)              
#define LCDC_VSPolarity_HIGH                  (LCDC_GCTRL_VSPOL)

/** Data enable Polarity **/
#define LCDC_DEPolarity_LOW                   (LCDC_GCTRL_DEPOL)              
#define LCDC_DEPolarity_HIGH                  (LCDC_REG_BIT_MASK)

/** Pixel clock Polarity **/
#define LCDC_PCPolarity_IPC                   (LCDC_REG_BIT_MASK)              
#define LCDC_PCPolarity_IIPC                  (LCDC_GCTRL_PCLKPOL)

/** LCDC reload **/
#define LCDC_IMReload                         (LCDC_SRCTRL_IMR)
#define LCDC_VBReload                         (LCDC_SRCTRL_VBR)

/** LCDC reload **/
#define LCDC_LayerIMReload                    (LCDC_LSRCTRL_IMR)
#define LCDC_LayerVBReload                    (LCDC_LSRCTRL_VBR)
#define LCDC_LayerMGReload                    (LCDC_LSRCTRL_MGR)

/** LCDC Pixel format **/
#define LCDC_Pixel_Format_ARGB8888            (LCDC_REG_BIT_MASK)
#define LCDC_Pixel_Format_ABGR8888            (LCDC_PFCTRL_PF_0)
#define LCDC_Pixel_Format_RGBA8888            (LCDC_PFCTRL_PF_1)
#define LCDC_Pixel_Format_BGRA8888            (LCDC_PFCTRL_PF_0 | LCDC_PFCTRL_PF_1)
#define LCDC_Pixel_Format_RGB565              (LCDC_PFCTRL_PF_2)
#define LCDC_Pixel_Format_BGR565              (LCDC_PFCTRL_PF_0 | LCDC_PFCTRL_PF_2)
#define LCDC_Pixel_Format_RGB888              (LCDC_PFCTRL_PF_1 | LCDC_PFCTRL_PF_2)
#define LCDC_Pixel_Format_Custom              (LCDC_PFCTRL_PF_0 | LCDC_PFCTRL_PF_1 | LCDC_PFCTRL_PF_2)

/** LCDC blending factor1 **/
#define LCDC_BlendingFactor1_CA               (LCDC_BFCTRL_BF1_2)
#define LCDC_BlendingFactor1_PAxCA            (LCDC_BFCTRL_BF1_1 | LCDC_BFCTRL_BF1_2)

/** LCDC blending factor2 **/
#define LCDC_BlendingFactor2_CA               (LCDC_BFCTRL_BF2_0 | LCDC_BFCTRL_BF2_2)
#define LCDC_BlendingFactor2_PAxCA            (LCDC_BFCTRL_BF2_0 | LCDC_BFCTRL_BF2_1 | LCDC_BFCTRL_BF2_2)

/** LCDC interrupt sources **/
#define LCDC_INT_LIEN                         (LCDC_INTEN_LIEN)
#define LCDC_INT_FUIEN                        (LCDC_INTEN_FUIEN)
#define LCDC_INT_BEIEN                        (LCDC_INTEN_BEIEN)
#define LCDC_INT_RRIEN                        (LCDC_INTEN_RRIEN)
#define LCDC_INT_STNSIGIEN                    (LCDC_INTEN_STNSIGIEN)
#define LCDC_INT_STNSYNCIEN                   (LCDC_INTEN_STNSYNCIEN)
#define LCDC_INT_FUKIEN                       (LCDC_INTEN_FUKIEN)
#define LCDC_INT_CRCIEN                       (LCDC_INTEN_CRCIEN)
#define LCDC_INT_RFEIEN                       (LCDC_INTEN_RFEIEN)

/** LCDC Flags **/
#define LCDC_FLAG_L                           (LCDC_INTEN_LIEN)
#define LCDC_FLAG_FU                          (LCDC_INTEN_FUIEN)
#define LCDC_FLAG_BE                          (LCDC_INTEN_BEIEN)
#define LCDC_FLAG_RR                          (LCDC_INTEN_RRIEN)
#define LCDC_FLAG_STNSIG                      (LCDC_INTEN_STNSIGIEN)
#define LCDC_FLAG_STNSYNC                     (LCDC_INTEN_STNSYNCIEN)
#define LCDC_FLAG_FUK                         (LCDC_INTEN_FUKIEN)
#define LCDC_FLAG_CRC                         (LCDC_INTEN_CRCIEN)
#define LCDC_FLAG_RFE                         (LCDC_INTEN_RFEIEN)


void LCDC_DeInit(void);
void LCDC_Init(LCDC_InitType* LCDC_InitStruct);
void LCDC_StructInit(LCDC_InitType* LCDC_InitStruct);
void LCDC_StructInit(LCDC_InitType* LCDC_InitStruct);
void LCDC_Enable(FunctionalState Cmd);
void LCDC_DitherEnable(FunctionalState Cmd);
LCDC_RGBType LCDC_GetDitherWidth(void);
void LCDC_DitherStructInit(LCDC_RGBType* LCDC_RGB_DitherStruct);
void LCDC_LINTPConfig(uint32_t LCDC_LINTPosition);
void LCDC_LayerInit(LCDC_Layer_Module* LCDC_Layerx , LCDC_Layer_InitType* LCDC_Layer_InitStruct);
void LCDC_LayerStructInit(LCDC_Layer_InitType* LCDC_Layer_InitStruct);
void LCDC_LayerEnable(LCDC_Layer_Module* LCDC_Layerx , FunctionalState Cmd);
LCDC_PosType LCDC_GetPosStatus(void);
void LCDC_PosStructInit(LCDC_PosType* LCDC_Pos_InitStruct);
FlagStatus LCDC_GetCDStatus(uint32_t LCDC_CD);
void LCDC_ReloadConfig(uint32_t LCDC_Reload);
void LCDC_LayerReloadConfig(LCDC_Layer_Module* LCDC_Layerx , uint32_t LCDC_LayerReload);
void LCDC_ColorKeyingConfig(LCDC_Layer_Module* LCDC_Layerx, LCDC_ColorKeying_InitType* LCDC_ColorKeying_InitStruct, FunctionalState Cmd);
void LCDC_ColorKeyingStructInit(LCDC_ColorKeying_InitType* LCDC_ColorKeying_InitStruct);
void LCDC_CLUTEnable(LCDC_Layer_Module* LCDC_Layerx, FunctionalState Cmd);
void LCDC_CLUTInit(LCDC_Layer_Module* LCDC_Layerx, LCDC_CLUT_InitType* LCDC_CLUT_InitStruct);
void LCDC_CLUTStructInit(LCDC_CLUT_InitType* LCDC_CLUT_InitStruct);
void LCDC_LayerPosition(LCDC_Layer_Module* LCDC_Layerx, uint16_t OffsetX, uint16_t OffsetY);
void LCDC_LayerAlpha(LCDC_Layer_Module* LCDC_Layerx, uint8_t ConstantAlpha);
void LCDC_LayerAddress(LCDC_Layer_Module* LCDC_Layerx, uint32_t Address);
void LCDC_LayerSize(LCDC_Layer_Module* LCDC_Layerx, uint32_t Width, uint32_t Height);
void LCDC_LayerPixelFormat(LCDC_Layer_Module* LCDC_Layerx, uint32_t PixelFormat);
void LCDC_ConfigInt(uint32_t LCDC_IT, FunctionalState Cmd);
FlagStatus LCDC_GetFlagStatus(uint32_t LCDC_FLAG);
FlagStatus LCDC_GetFlagStatus(uint32_t LCDC_FLAG);
void LCDC_ClearFlag(uint32_t LCDC_FLAG);
INTStatus LCDC_GetIntStatus(uint32_t LCDC_IT);
void LCDC_ClrIntPendingBit(uint32_t LCDC_IT);




/** LCDC_Exported_Functions End **/

#ifdef __cplusplus
}

#endif

#endif /*__N32H76x_78x_LCDC_H */
































