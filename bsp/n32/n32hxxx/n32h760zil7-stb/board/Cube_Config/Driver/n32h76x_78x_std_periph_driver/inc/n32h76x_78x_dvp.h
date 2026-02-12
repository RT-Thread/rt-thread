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
 * @file n32h76x_78x_dvp.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76x_78x_DVP_H
#define __N32H76x_78x_DVP_H


#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"

/*** DVP Structure Definition Start ***/

/** DVP Init structure definition **/
typedef struct
{
    
    uint32_t CaptureMode;      /* Specifies the capture mode. */    
                                  
    uint32_t CropMode;         /* Specifies the crop mode. */
    
    uint32_t SynchroMode;      /*!< Specifies the Synchronization Mode: Hardware or Embedded.*/
    
    uint16_t CropStartX;       /* Specifies the start point x. */ 
                                  
    uint16_t CropStartY;       /* Specifies the start point y. */ 
                                  
    uint16_t CropEndX;         /* Specifies the end point x. */ 
                                  
    uint16_t CropEndY;         /* Specifies the end point y. */ 
                                  
    uint8_t VBFilter;          /* Specifies the VSYNC blanking glitch filtering. */ 
                                  
    uint32_t PixelClkPolarity; /* Specifies the pixel clock polarity */
                                  
    uint32_t HsyncPolarity;    /* Specifies the Horizontal synchronization polarity  */
                                  
    uint32_t VsyncPolarity;    /* Specifies the vertical synchronization polarity */
                                  
    uint32_t DataInvert;       /* Specifies the data invert. */
                                  
    uint32_t DataReverse;      /* Specifies the data reverse. */
                                  
    uint32_t DataMode;         /* Specifies the data port mode. */ 
                                  
    uint32_t PixelByte;        /* Specifies pixel byte. */                   

}DVP_InitType;


/** DVP DMA init structure definition **/
typedef struct
{
    
    uint8_t FrameBufferNum;      /* Specifies Frame Buffer number. */ 
    
    uint32_t FrameBufferAddress1;      /* Specifies Frame Buffer 1 Address. */   
    
    uint32_t FrameBufferAddress2;      /* Specifies Frame Buffer 2 Address. */    
                                  
    uint32_t DisplayStatus;           /* Specifies Display buffer status. */
        
    uint32_t FifoThreshold;       /* Specifies FIFO transmit threshold. */
    
    uint32_t BurstSize;           /* Specifies Frame Buffer size. */

    uint32_t FrameBufferSize;     /* Specifies Frame Buffer size. */
             
}DVP_DMAInitType;

/*** DVP Structure Definition End ***/

/*** DVP Macro Definition Start ***/
/** DVP register bit field mask definition **/
#define DVP_REG_BIT_FIELD_MASK      ((uint32_t)0x00000000U)

/** DVP enable definition**/
#define DVP_ENABLE                  (DVP_CTRL_DVPEN)
#define DVP_DISABLE                 (DVP_INTSTS_DVPDIS) 

/** DVP Capture Mode definition**/
#define DVP_CAPTURE_MODE_MASK       (~DVP_CTRL_CM)
#define DVP_CAPTURE_MODE_CONTINUE   (DVP_REG_BIT_FIELD_MASK)
#define DVP_CAPTURE_MODE_SINGLE     (DVP_CTRL_CM)

/** DVP Cropping Feature definition**/
#define DVP_CROP_MODE_MASK          (~DVP_CTRL_CROPEN)
#define DVP_NORMAL_MODE             (DVP_REG_BIT_FIELD_MASK)
#define DVP_CROP_MODE               (DVP_CTRL_CROPEN)

/** DVP VSYNC blanking glitch filtering control definition**/
#define DVP_VBFLT_MASK              (~((uint32_t)DVP_CTRL_VBFLT))

/** DVP interrupts definition **/
#define DVP_INT_M1S                 (DVP_INTEN_M1SIE  ) 
#define DVP_INT_M2S                 (DVP_INTEN_M2SIE  ) 
#define DVP_INT_M1TC                (DVP_INTEN_M1TCIE ) 
#define DVP_INT_M2TC                (DVP_INTEN_M2TCIE ) 
#define DVP_INT_FO                  (DVP_INTEN_FOIE   ) 
#define DVP_INT_AHBERR              (DVP_INTEN_AHBERR ) 
#define DVP_INT_MO                  (DVP_INTEN_MOIE   ) 
#define DVP_INT_SKIP                (DVP_INTEN_SKIPIE ) 
#define DVP_INT_CERR                (DVP_INTEN_CERRIE ) 
#define DVP_INT_SERR                (DVP_INTEN_SERRIE ) 
#define DVP_INT_FMS                 (DVP_INTEN_FMSIE  ) 

/** DVP flags definition **/
#define DVP_FLAG_M1S                (DVP_INTSTS_M1SF     ) 
#define DVP_FLAG_M2S                (DVP_INTSTS_M2SF     ) 
#define DVP_FLAG_M1TC               (DVP_INTSTS_M1TCF    ) 
#define DVP_FLAG_M2TC               (DVP_INTSTS_M2TCF    ) 
#define DVP_FLAG_M1FO               (DVP_INTSTS_M1FOF    ) 
#define DVP_FLAG_M2FO               (DVP_INTSTS_M2FOF    ) 
#define DVP_FLAG_AHBERR1            (DVP_INTSTS_AHBERR1F ) 
#define DVP_FLAG_AHBERR2            (DVP_INTSTS_AHBERR2F ) 
#define DVP_FLAG_M1O                (DVP_INTSTS_M1OF     ) 
#define DVP_FLAG_M2O                (DVP_INTSTS_M2OF     ) 
#define DVP_FLAG_SKIP               (DVP_INTSTS_SKIPF    )
#define DVP_FLAG_CERR               (DVP_INTSTS_CERRF    ) 
#define DVP_FLAG_SERR               (DVP_INTSTS_SERRF    ) 
#define DVP_FLAG_FMS                (DVP_INTSTS_FMSF     ) 

/** DVP pixel clock polarity definition **/
#define DVP_PIXEL_POLARITY_MASK     (~DVP_PORTCFG_PCLKPOL) 
#define DVP_PIXEL_POLARITY_RISING   (DVP_REG_BIT_FIELD_MASK) /* if the data from the sensor is expected to be latched at the rising edge of the pixel clock. */
#define DVP_PIXEL_POLARITY_FALLING  (DVP_PORTCFG_PCLKPOL) /* if the data from the sensor is expected to be latched at the falling edge of the pixel clock. */

/** DVP horizontal polarity definition **/
#define DVP_HSYNC_POLARITY_MASK     (~DVP_PORTCFG_HSPOL) 
#define DVP_HSYNC_POLARITY_HIGH     (DVP_REG_BIT_FIELD_MASK) /* when HSYNC=0 is high active. */
#define DVP_HSYNC_POLARITY_LOW      (DVP_PORTCFG_HSPOL) /* when HSYNC=1 is low active. */

/** DVP vertical polarity definition **/
#define DVP_VSYNC_POLARITY_MASK     (~DVP_PORTCFG_VSPOL) 
#define DVP_VSYNC_POLARITY_HIGH     (DVP_PORTCFG_VSPOL) /* when VSYNC=1 is high active. */
#define DVP_VSYNC_POLARITY_LOW      (DVP_REG_BIT_FIELD_MASK) /* when VSYNC=0 islow active. */

/** DVP Data bit inversion definition **/
#define DVP_DATA_INVERT_MASK        (~DVP_PORTCFG_DATINV) 
#define DVP_DATA_INVERT             (DVP_PORTCFG_DATINV) /* enable data bit inversion on the DVP port data. */
#define DVP_DATA_NOTINVERT          (DVP_REG_BIT_FIELD_MASK) /* data bit inversion is not enabled. */

/** DVP Data bit reverse definition **/
#define DVP_DATA_REVERSE_MASK       (~DVP_PORTCFG_DATRVS) 
#define DVP_DATA_REVERSE            (DVP_PORTCFG_DATRVS) /* enable to reverse data bit order on the DVP port data. */
#define DVP_DATA_NOTREVERSE         (DVP_REG_BIT_FIELD_MASK) /* remain original data bit order. */


/** DVP Embedded Synchronization Code Position definition **/
#define DVP_EMBSYNC_POS_MASK        (~DVP_PORTCFG_SLC) 
#define DVP_EMBSYNC_LSB             (DVP_PORTCFG_SLC) /* the sync code is aligned to the least significant bit of the data lines. */
#define DVP_EMBSYNC_MSB             (DVP_REG_BIT_FIELD_MASK) /* the sync code is aligned to the most significant bit of the data lines. */

/** DVP Embedded Synchronization Code mode definition **/
#define DVP_EMBSYNC_MASK            (~DVP_PORTCFG_EMBSEN) 
#define DVP_SYNC_MODE_SOFTWARE      (DVP_PORTCFG_EMBSEN) /* embedded synchronization mode. */
#define DVP_SYNC_MODE_HARDWARE      (DVP_REG_BIT_FIELD_MASK) /* use VSYNC and HSYNC to do synchronization. */

/** DVP data port mode definition **/
#define DVP_DATA_MODE_MASK          (~DVP_PORTCFG_DBIT) 
#define DVP_DATA_MODE1              (DVP_REG_BIT_FIELD_MASK)             /* 8-bit physical data port, and data is captured on all data lines. */
#define DVP_DATA_MODE2              (DVP_PORTCFG_DBIT0)                    /* 10-bit physical data port, and data is captured on all data lines. */
#define DVP_DATA_MODE3              (DVP_PORTCFG_DBIT1)                    /* 12-bit physical data port, and data is captured on all data lines. */
#define DVP_DATA_MODE4              (DVP_PORTCFG_DBIT0 | DVP_PORTCFG_DBIT1) /* 14-bit physical data port, and data is captured on all data lines. */
#define DVP_DATA_MODE5              (DVP_PORTCFG_DBIT2)                    /* 16-bit physical data port, and data is captured on all data lines. */
#define DVP_DATA_MODE6              (DVP_PORTCFG_DBIT0 | DVP_PORTCFG_DBIT2) /* 10-bit physical data port, and data is captured on 8 data lines [9:2] only. */
#define DVP_DATA_MODE7              (DVP_PORTCFG_DBIT1 | DVP_PORTCFG_DBIT2) /* 12-bit physical data port, and data is captured on 10 data lines [11:2] only. */
#define DVP_DATA_MODE8              (DVP_PORTCFG_DBIT)                     /* 12-bit physical data port, and data is captured on 8 data lines [11:4] only. */

/** DVP pixel bytes definition **/
#define DVP_PIXEL_BYTE_MASK         (~DVP_PORTCFG_PIXELDB) 
#define DVP_PIXEL_BYTE1             (DVP_REG_BIT_FIELD_MASK) /* one byte per pixel */
#define DVP_PIXEL_BYTE2             (DVP_PORTCFG_PIXELDB) /* two byte per pixel */

/** DVP bytes mapping definition **/
#define DVP_BYTE_ORDER_MASK         (~DVP_PORTCFG_BMAP)
 
#define DVP_BYTE0_ORDER1            (DVP_REG_BIT_FIELD_MASK) 
#define DVP_BYTE0_ORDER2            (DVP_PORTCFG_BMAP0) 
#define DVP_BYTE0_ORDER3            (DVP_PORTCFG_BMAP1) 
#define DVP_BYTE0_ORDER4            (DVP_PORTCFG_BMAP0 | DVP_PORTCFG_BMAP1) 

#define DVP_BYTE1_ORDER1            (DVP_REG_BIT_FIELD_MASK) 
#define DVP_BYTE1_ORDER2            (DVP_PORTCFG_BMAP2) 
#define DVP_BYTE1_ORDER3            (DVP_PORTCFG_BMAP3) 
#define DVP_BYTE1_ORDER4            (DVP_PORTCFG_BMAP2 | DVP_PORTCFG_BMAP3) 

#define DVP_BYTE2_ORDER1            (DVP_REG_BIT_FIELD_MASK) 
#define DVP_BYTE2_ORDER2            (DVP_PORTCFG_BMAP4) 
#define DVP_BYTE2_ORDER3            (DVP_PORTCFG_BMAP5) 
#define DVP_BYTE2_ORDER4            (DVP_PORTCFG_BMAP4 | DVP_PORTCFG_BMAP5) 

#define DVP_BYTE3_ORDER1            (DVP_REG_BIT_FIELD_MASK) 
#define DVP_BYTE3_ORDER2            (DVP_PORTCFG_BMAP6) 
#define DVP_BYTE3_ORDER3            (DVP_PORTCFG_BMAP7) 
#define DVP_BYTE3_ORDER4            (DVP_PORTCFG_BMAP6 | DVP_PORTCFG_BMAP7) 

/** DVP Frame Line Skip definition **/
#define DVP_SKIP_LINE1              ((uint32_t)0x00000001U)
#define DVP_SKIP_LINE2              ((uint32_t)0x00000002U)
#define DVP_SKIP_LINE3              ((uint32_t)0x00000003U)
#define DVP_SKIP_LINE4              ((uint32_t)0x00000004U)
#define DVP_SKIP_LINE5              ((uint32_t)0x00000005U)
#define DVP_SKIP_LINE6              ((uint32_t)0x00000006U)
#define DVP_SKIP_LINE7              ((uint32_t)0x00000007U)
#define DVP_SKIP_LINE8              ((uint32_t)0x00000008U)
#define DVP_SKIP_LINE9              ((uint32_t)0x00000009U)
#define DVP_SKIP_LINE10             ((uint32_t)0x0000000AU)
#define DVP_SKIP_LINE11             ((uint32_t)0x0000000BU)
#define DVP_SKIP_LINE12             ((uint32_t)0x0000000CU)
#define DVP_SKIP_LINE13             ((uint32_t)0x0000000DU)
#define DVP_SKIP_LINE14             ((uint32_t)0x0000000EU)
#define DVP_SKIP_LINE15             ((uint32_t)0x0000000FU)

/** DVP Initial Frame Line Skip definition **/
#define DVP_ISKIP_MASK              (~DVP_PORTCFG_HISKIP)

/** DVP Repeat Frame Line Skip definition **/
#define DVP_RSKIP_MASK              (~DVP_PORTCFG_HRSKIP)
#define DVP_ODD_LINE                ((uint32_t)0x0000000EU)
#define DVP_EVEN_LINE               ((uint32_t)0x0000000FU)

/** DVP Frame Buffer 1 enable control definition **/
#define DVP_BUFFER1_MASK            ((uint32_t)~DVP_FIFOCFG_M1ADDREN) 
#define DVP_BUFFER1                 ((uint32_t)DVP_FIFOCFG_M1ADDREN) 

/** DVP Frame Buffer 2 enable control definition **/
#define DVP_BUFFER2_MASK            (~DVP_FIFOCFG_M2ADDREN) 
#define DVP_BUFFER2                 (DVP_FIFOCFG_M2ADDREN) 

/** DVP bursting across 1K boundary control definition **/
#define DVP_1K_BOUNDARY_MASK        (~DVP_FIFOCFG_EN1KBD) 
#define DVP_1K_BOUNDARY_ENABLE      (DVP_FIFOCFG_EN1KBD)
#define DVP_1K_BOUNDARY_DISABLE     (DVP_REG_BIT_FIELD_MASK) 

/** DVP show current frame buffer status definition **/
#define DVP_DISPLAY_STATUS_MASK     (~DVP_FIFOCFG_DISPMODE) 
#define DVP_DISPLAY_ADDRESS         (DVP_FIFOCFG_DISPMODE) 
#define DVP_DISPLAY_NUMBER          (DVP_REG_BIT_FIELD_MASK) 

/** DVP transmit threshold definition **/
#define DVP_FIFO_THRSEHOLD_MASK      (~DVP_FIFOCFG_TXFTH) 
#define DVP_FIFO_THRSEHOLD_BYTE_8    (DVP_REG_BIT_FIELD_MASK) 
#define DVP_FIFO_THRSEHOLD_BYTE_16   (DVP_FIFOCFG_TXFTH0) 
#define DVP_FIFO_THRSEHOLD_BYTE_32   (DVP_FIFOCFG_TXFTH1) 
#define DVP_FIFO_THRSEHOLD_BYTE_64   (DVP_FIFOCFG_TXFTH0 | DVP_FIFOCFG_TXFTH1) 
#define DVP_FIFO_THRSEHOLD_BYTE_128  (DVP_FIFOCFG_TXFTH2) 
#define DVP_FIFO_THRSEHOLD_BYTE_256  (DVP_FIFOCFG_TXFTH2 | DVP_FIFOCFG_TXFTH0) 
#define DVP_FIFO_THRSEHOLD_BYTE_512  (DVP_FIFOCFG_TXFTH2 | DVP_FIFOCFG_TXFTH1) 
#define DVP_FIFO_THRSEHOLD_BYTE_1024 (DVP_FIFOCFG_TXFTH2 | DVP_FIFOCFG_TXFTH1 | DVP_FIFOCFG_TXFTH0) 

/** DVP data burst definition **/
#define DVP_BURST_SIZE_MASK         (~DVP_FIFOCFG_TXBURSZ) 
#define DVP_BURST_SIZE_BYTE_8       (DVP_REG_BIT_FIELD_MASK) 
#define DVP_BURST_SIZE_BYTE_16      (DVP_FIFOCFG_TXBURSZ0) 
#define DVP_BURST_SIZE_BYTE_24      (DVP_FIFOCFG_TXBURSZ1) 
#define DVP_BURST_SIZE_BYTE_32      (DVP_FIFOCFG_TXBURSZ0 | DVP_FIFOCFG_TXBURSZ1) 
#define DVP_BURST_SIZE_BYTE_40      (DVP_FIFOCFG_TXBURSZ2) 
#define DVP_BURST_SIZE_BYTE_48      (DVP_FIFOCFG_TXBURSZ2 | DVP_FIFOCFG_TXBURSZ0) 
#define DVP_BURST_SIZE_BYTE_56      (DVP_FIFOCFG_TXBURSZ2 | DVP_FIFOCFG_TXBURSZ1) 
#define DVP_BURST_SIZE_BYTE_64      (DVP_FIFOCFG_TXBURSZ) 
/*** DVP Private Definition End ***/

/*** DVP Driving Functions Declaration ***/
void DVP_DeInit(DVP_Module *DVPx);
void DVP_Init(DVP_Module *DVPx, DVP_InitType* DVP_InitParam);
void DVP_StructInit(DVP_InitType* DVP_InitParam);
void DVP_ConfigDma(DVP_Module *DVPx, DVP_DMAInitType* DVP_DMAInitParam);
void DVP_DMAStructInit(DVP_DMAInitType* DVP_DMAInitParam);
void DVP_EnablePort(DVP_Module *DVPx, FunctionalState Cmd);
void DVP_EnableCrop(DVP_Module *DVPx, FunctionalState Cmd);
void DVP_ConfigVBlankFilter(DVP_Module *DVPx, uint8_t Filt);
void DVP_ConfigInt(DVP_Module *DVPx, uint32_t DVPInt, FunctionalState Cmd);
FlagStatus DVP_GetFlagStatus(DVP_Module *DVPx, uint32_t DVP_Flag);
void DVP_ClearFlag(DVP_Module *DVPx, uint32_t DVP_Flag);
INTStatus DVP_GetIntStatus(DVP_Module *DVPx, uint32_t DVP_Int);
void DVP_ClrIntPendingBit(DVP_Module *DVPx, uint32_t DVP_Int);
void DVP_ConfigPixelClockPolarity(DVP_Module *DVPx, uint32_t PLCK_POL);
void DVP_ConfigHSyncPolarity(DVP_Module *DVPx, uint32_t HSYNC_POL);
void DVP_ConfigVSyncPolarity(DVP_Module *DVPx, uint32_t VSYNC_POL);
void DVP_EnableDataInvert(DVP_Module *DVPx, FunctionalState Cmd);
void DVP_EnableDataReverse(DVP_Module *DVPx, FunctionalState Cmd);
void DVP_ConfigEmbSyncPos(DVP_Module *DVPx, uint32_t SYNC_Pos);
void DVP_ConfigEmbSyncData(DVP_Module *DVPx, uint8_t FrameStartValue, uint8_t FrameEndValue, uint8_t LineStartValue, uint8_t LineEndValue);
void DVP_ConfigEmbSyncDataMask(DVP_Module *DVPx, uint8_t FrameStartMask, uint8_t FrameEndMask, uint8_t LineStartMask, uint8_t LineEndMask);
void DVP_EnableEmbSyncMode(DVP_Module *DVPx, FunctionalState Cmd);
void DVP_ConfigDataMode(DVP_Module *DVPx, uint32_t Mode);
void DVP_ConfigPixelByte(DVP_Module *DVPx, uint32_t Pixel_Byte);
void DVP_ConfigDATAByteOrder(DVP_Module *DVPx, uint32_t Byte0, uint32_t Byte1, uint32_t Byte2, uint32_t Byte3);
void DVP_ConfigInitSKIP(DVP_Module *DVPx, uint32_t Line);
void DVP_EnableBuffer1(DVP_Module *DVPx, FunctionalState Cmd);
void DVP_SetBuffer1Address(DVP_Module *DVPx, uint32_t Addres);
void DVP_EnableBuffer2(DVP_Module *DVPx, FunctionalState Cmd);
void DVP_SetBuffer2Address(DVP_Module *DVPx, uint32_t Addres);
void DVP_SetBufferSize(DVP_Module *DVPx, uint32_t Size);
void DVP_SetDisplayBufferStatus(DVP_Module *DVPx, uint32_t State_Mode);
uint32_t DVP_GetDisplayBufferStatus1(DVP_Module *DVPx);
uint32_t DVP_GetDisplayBufferStatus2(DVP_Module *DVPx);
void DVP_EnableAcross1KBoundary(DVP_Module *DVPx, FunctionalState Cmd);
void DVP_ConfigCROPStart(DVP_Module *DVPx, uint16_t X,uint16_t Y);
void DVP_ConfigCROPEnd(DVP_Module *DVPx, uint16_t X,uint16_t Y);

#ifdef __cplusplus
}
#endif

#endif /* __N32H76x_78x_DVP_H */









































































