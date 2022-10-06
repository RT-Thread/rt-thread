/**
 *  \file   raster.h
 *
 *  \brief  Definitions used for raster LCD
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef _RASTER_H_
#define _RASTER_H_

#include "hw_lcdc.h"
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*                           MACRO DEFINITIONS
*******************************************************************************/
/*****************************************************************************/
/*
** Values that can be passed to RasterModeConfig API as displayType to select 
** type of display
*/

 /* Configure display type to TFT */
#define RASTER_DISPLAY_MODE_TFT          (1 << LCDC_RASTER_CTRL_TFT_STN_SHIFT)

 /* Configure display type to STN */
#define RASTER_DISPLAY_MODE_STN           0

/* Configure display type to TFT with 24 bit data packed mode */
#define RASTER_DISPLAY_MODE_TFT_PACKED    (1 << LCDC_RASTER_CTRL_TFT_STN_SHIFT)|\
                                          (1 << LCDC_RASTER_CTRL_TFT24_SHIFT) 

/* Configure display type to TFT with 24 bit data packed mode */
#define RASTER_DISPLAY_MODE_TFT_UNPACKED  (1 << LCDC_RASTER_CTRL_TFT_STN_SHIFT)|\
                                          (1 << LCDC_RASTER_CTRL_TFT24_SHIFT) |\
                                          (1 << LCDC_RASTER_CTRL_TFT24UNPACKED_SHIFT)

/******************************************************************************/
/*
** Values that can be passed to RasterModeConfig API as paletteMode to select 
** mode of palette loading.
*/
 /* Both palette and data will be loaded */
#define RASTER_PALETTE_DATA                0

 /* Only palette will be loaded */  
#define RASTER_PALETTE                    (1 << LCDC_RASTER_CTRL_PLM_SHIFT)

 /* Only data will be loaded */
#define RASTER_DATA                       (2 << LCDC_RASTER_CTRL_PLM_SHIFT)

/*********************************************************************************/
/*
** Values that can be passed to RasterModeConfig API as displayMode to select 
** mode of display as either color or monochrome.
*/

 /* Select displayMode as COLOR */
#define RASTER_COLOR                       0

 /* Select displayMode as monochrome */
#define RASTER_MONOCHROME                 (1 << LCDC_RASTER_CTRL_MONO_COLOR_SHIFT)
/*********************************************************************************/
/*
** Values that can be passed to RasterModeConfig API as flag for signal mappping
** if out pixel data is of 1,2,4 or 8 bits per pixel
*/
  /* Out put pixel data will be right aligned */
#define RASTER_RIGHT_ALIGNED                0
 
 /* Out put pixel data will be mapped to 565 format */
#define RASTER_EXTRAPOLATE                (1 << LCDC_RASTER_CTRL_TFT_ALT_MAP_SHIFT)

/*******************************************************************************/
/*
** Values that can be passed to RasterModeConfig API as flag to select how many
** bits to output each pixel clock when momochrome displayMode is used
*/
  
 /* Eight bits are output each pClk */  
#define RASTER_MONO8B                     (1 << LCDC_RASTER_CTRL_MONO8B_SHIFT)

 /* Four bits are output each pClk */  
#define RASTER_MONO4B                       0
/******************************************************************************/
/*
** Values that can be passed to RasterDMAConfig API as frmMode to select either 
** to signle frame buffer or double frmae buffer(ping pong)
*/

 /* Selects single frmae buffer */
#define RASTER_SINGLE_FRAME_BUFFER          0

 /* Selects double frmae buffer */
#define RASTER_DOUBLE_FRAME_BUFFER         LCDC_LCDDMA_CTRL_FRAME_MODE
/*****************************************************************************/
/*
** Values that can be passed to RasterDMAConfig API as endian  to enable or
** disable bigendian for data reordering 
*/
 
 /* Enable bigendian for data reordering */
#define RASTER_BIG_ENDIAN_ENABLE           (1 << LCDC_LCDDMA_CTRL_BIGENDIAN_SHIFT)

 /* Disable bigendian for data reordering */
#define RASTER_BIG_ENDIAN_DISABLE           0
/*****************************************************************************/
/*
** Values that can be passed to RasterDMAConfig API as bustSz  to select burst 
** size for DMA transfer
*/

 /* Select burst size as one */ 
#define RASTER_BURST_SIZE_1                 0

 /* Select burst size as two */ 
#define RASTER_BURST_SIZE_2                 (1 <<  LCDC_LCDDMA_CTRL_BURST_SIZE_SHIFT)

 /* Select burst size as four */ 
#define RASTER_BURST_SIZE_4                 (2 <<  LCDC_LCDDMA_CTRL_BURST_SIZE_SHIFT)

 /* Select burst size as eight*/ 
#define RASTER_BURST_SIZE_8                 (3 <<  LCDC_LCDDMA_CTRL_BURST_SIZE_SHIFT)

 /* Select burst size as sixteen */ 
#define RASTER_BURST_SIZE_16                (4 <<  LCDC_LCDDMA_CTRL_BURST_SIZE_SHIFT)
/*****************************************************************************/
/*
** Values that can be passed to RasterDMAConfig API as fifoTh  to select DMA
** fifo threshold
*/

#define RASTER_FIFO_THRESHOLD_8          (0 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_16         (1 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_32         (2 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_64         (3 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_128        (4 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_256        (5 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
#define RASTER_FIFO_THRESHOLD_512        (6 << LCDC_LCDDMA_CTRL_TH_FIFO_READY_SHIFT)
 
/*********************************************************************************/
/*
** Values that can be passed to RasterTiming2Configure API as flag  to select the
** polarity of timing parameters of LCD controller.
*/

 /* Selects active high frame clock */
#define RASTER_FRAME_CLOCK_HIGH             0

 /* Selects active low frame clock */
#define RASTER_FRAME_CLOCK_LOW              LCDC_RASTER_TIMING_2_IVS

 /* Selects active high line clock */
#define RASTER_LINE_CLOCK_HIGH              0

 /* Selects active low line clock */
#define RASTER_LINE_CLOCK_LOW               LCDC_RASTER_TIMING_2_IHS

 /* Selects active high pixel clock */
#define RASTER_PIXEL_CLOCK_HIGH             0

 /* Selects active low pixel clock */
#define RASTER_PIXEL_CLOCK_LOW              LCDC_RASTER_TIMING_2_IPC

 /* Selects acbias as active high*/
#define RASTER_AC_BIAS_HIGH                  0

 /* Selects acbias as active low*/
#define RASTER_AC_BIAS_LOW                  LCDC_RASTER_TIMING_2_BIAS

 /* Selects horizontal and vertical sync edge as rising edge*/
#define RASTER_SYNC_EDGE_RISING              0

 /* Selects horizontal and vertical sync edge as falling edge*/
#define RASTER_SYNC_EDGE_FALLING            LCDC_RASTER_TIMING_2_SYNC_EDGE

 /* Selects horizontal and vertical sync control as active */
#define RASTER_SYNC_CTRL_ACTIVE             LCDC_RASTER_TIMING_2_SYNC_CTRL

 /* Selects horizontal and vertical sync control as active */
#define RASTER_SYNC_CTRL_INACTIVE           0
/**************************************************************************/
/*
** Values that can be passed to RasterIntEnable or RasterIntDisable API 
** as flag  to select the interrupt to be enabled or disabled
*/

#ifdef am1808

#define RASTER_ACBIAS_COUNT_INT             LCDC_RASTER_CTRL_AC_EN

#define RASTER_FRAME_DONE_INT               LCDC_RASTER_CTRL_DONE_EN

#define RASTER_PALETTE_LOADED_INT           LCDC_RASTER_CTRL_PL_EN

#define RASTER_SYNC_LOST_INT                LCDC_RASTER_CTRL_SL_EN

#define RASTER_FIFO_UNDRFLOW_INT            LCDC_RASTER_CTRL_FUF_EN

#endif


#if defined(am335x) || defined(am335x_13x13) || defined(am335x_15x15)

#define RASTER_ACBIAS_COUNT_INT             LCDC_IRQENABLE_SET_ACB

#define RASTER_FRAME_DONE_INT               LCDC_IRQENABLE_SET_DONE

#define RASTER_PALETTE_LOADED_INT           LCDC_IRQENABLE_SET_PL

#define RASTER_SYNC_LOST_INT                LCDC_IRQENABLE_SET_SYNC

#define RASTER_FIFO_UNDRFLOW_INT            LCDC_IRQENABLE_SET_FUF

#endif

#define RASTER_DONE_INT                     LCDC_IRQENABLE_SET_RECURRENT_RASTER

#define RASTER_END_OF_FRAME0_INT            LCDC_IRQENABLE_SET_EOF0

#define RASTER_END_OF_FRAME1_INT            LCDC_IRQENABLE_SET_EOF1

/***************************************************************************/
/*
** Values that can be passed to RasterIntSatus API as flag
** to get interrupt status of rquired interrupt.
*/

#if defined(am1808) || defined(omapl138) || defined(c6748)

#define RASTER_FRAME_DONE_INT_STAT          LCDC_LCD_STAT_DONE

#define RASTER_SYNC_LOST_INT_STAT           LCDC_LCD_STAT_SYNC

#define RASTER_ACBIAS_COUNT_INT_STAT        LCDC_LCD_STAT_ABC

#define RASTER_FIFO_UNDERFLOW_INT_STAT      LCDC_LCD_STAT_FUF

#define RASTER_PALETTE_LOADED_INT_STAT      LCDC_LCD_STAT_PL

#define RASTER_END_OF_FRAME0_INT_STAT       LCDC_LCD_STAT_EOF0

#define RASTER_END_OF_FRAME1_INT_STAT       LCDC_LCD_STAT_EOF1

#endif

#if defined(am335x) || defined(am335x_13x13) || defined(am335x_15x15)

#define RASTER_FRAME_DONE_INT_STAT          LCDC_IRQSTATUS_DONE

#define RASTER_SYNC_LOST_INT_STAT           LCDC_IRQSTATUS_SYNC

#define RASTER_ACBIAS_COUNT_INT_STAT        LCDC_IRQSTATUS_ACB

#define RASTER_FIFO_UNDERFLOW_INT_STAT      LCDC_IRQSTATUS_FUF

#define RASTER_PALETTE_LOADED_INT_STAT      LCDC_IRQSTATUS_PL

#define RASTER_END_OF_FRAME0_INT_STAT       LCDC_IRQSTATUS_EOF0

#define RASTER_END_OF_FRAME1_INT_STAT       LCDC_IRQSTATUS_EOF1

#endif


/***************************************************************************/
/*
** Values that can be passed to RasterSoftawreResetControl API as flag
** to Reset required module(i.e Raster or DMA or LCD).
*/

#define RASTER_CORE_RESET                   LCDC_CLKC_RESET_CORE
#define RASTER_DMA_RESET                    LCDC_CLKC_RESET_DMA
#define RASTER_LCD_MODULE_RESET             LCDC_CLKC_RESET_MAIN


#define RASTER_REV_AM335X                    2u
#define RASTER_REV_AM1808                    1u
/***************************************************************************/

typedef struct rasterContext {
    unsigned int clkcEnable;
    unsigned int lcdCtrl;
    unsigned int lcddmaCtrl;
    unsigned int rasterTiming0;
    unsigned int rasterTiming1;
    unsigned int rasterTiming2;
    unsigned int rasterCtrl;
    unsigned int irqEnableSet;
    unsigned int lcddmaFb0Base;
    unsigned int lcddmaFb0Ceiling;
    unsigned int lcddmaFb1Base;
    unsigned int lcddmaFb1Ceiling;
}RASTERCONTEXT;


/*
** Function Prototypes
*/
extern void RasterEnable(unsigned int baseAddr);
extern void RasterDisable(unsigned int baseAddr);
extern void RasterNibbleModeEnable(unsigned int  baseAddr);
extern void RasterNibbleModeDisable(unsigned int baseAddr);
extern void RasterMSBDataOrderSelect(unsigned int baseAddr);
extern void RasterLSBDataOrderSelect(unsigned int baseAddr);
extern void RasterEndOfFrameIntEnable(unsigned int baseAddr);
extern void RasterEndOfFrameIntDisable(unsigned int baseAddr);
extern void RasterIntEnable(unsigned int baseAddr, unsigned int flag);
extern void RasterDMAFBConfig(unsigned int baseAddr, unsigned int base,
                              unsigned int  ceiling, unsigned int flag);
extern void RasterDMAConfig(unsigned int baseAddr, unsigned int frmMode,
                            unsigned int bustSz, unsigned int fifoTh,
                            unsigned int endian);
extern void RasterIntDisable(unsigned int baseAddr, unsigned int flag);
extern void RasterClkConfig(unsigned int baseAddr, unsigned int pClk,
                            unsigned int moduleClk);
extern void RasterModeConfig(unsigned int baseAddr, unsigned int displayMode,
                             unsigned int paletteMode, unsigned int displayType,
                             unsigned int flag);

extern unsigned int RasterIntStatus(unsigned int baseAddr, unsigned int flag);
extern void RasterVparamConfig(unsigned int baseAddr, unsigned int Lpp,
                               unsigned int vsw, unsigned int vfp,
                               unsigned vbp);

extern void RasterHparamConfig(unsigned int baseAddr, unsigned int numOfppl,
                               unsigned int hsw, unsigned int hfp,
                               unsigned hbp);

extern void RasterTiming2Configure(unsigned int baseAddr, unsigned int flag,
                                   unsigned int acb_i, unsigned int acb);

extern void RasterFIFODMADelayConfig(unsigned int baseAddr, unsigned int delay);

extern void RasterSubPanelEnable(unsigned int baseAddr);

extern void RasterSubPanelDisable(unsigned int baseAddr);

extern void RasterSubPanelConfig(unsigned int baseAddr, unsigned int hols,
                                 unsigned int lppt, unsigned int dpd);
extern unsigned int  RasterClearGetIntStatus(unsigned int baseAddr,
                                             unsigned int flag);



extern void RasterClocksEnable(unsigned int baseAddr);
extern unsigned int LCDVersionGet(void);
extern void RasterContextSave(unsigned int baseAddr, RASTERCONTEXT *contextPtr);
extern void RasterContextRestore(unsigned int baseAddr, RASTERCONTEXT *contextPtr);

extern void RasterStandbyModeConfig(unsigned int baseAddr, unsigned int flag);
extern void RasterIdleModeConfig(unsigned int baseAddr, unsigned int flag);

#ifdef __cplusplus
}
#endif
#endif
