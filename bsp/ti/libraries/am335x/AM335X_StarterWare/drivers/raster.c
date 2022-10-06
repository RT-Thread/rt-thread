/**
 *  \file   raster.c
 *
 *  \brief  Raster LCD APIs.
 *
 *   This file contains the device abstraction layer APIs for Raster LCD.
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

#include "hw_lcdc.h"
#include "hw_types.h"
#include "raster.h"

/*******************************************************************************
*                       INTERNAL API DEFINITIONS
*******************************************************************************/
/**
* \brief  This function configures clkdiv to generate required frequency of 
*         of pixel clock and selects the raster control.\n
*
* \param  baseAddr   is the Memory address of LCD.\n
* \param  pClk       is the required Pixel Clock frequency.\n
* \param  modulck    is the input clk to LCD module from PLL.\n
* 
* \return none.
**/
void RasterClkConfig(unsigned int baseAddr, unsigned int pClk,
                     unsigned int moduleClk)
{
    unsigned int clkDiv;

    clkDiv = moduleClk / pClk ;

    HWREG(baseAddr + LCDC_LCD_CTRL) = LCDC_LCD_CTRL_MODESEL;
   
    HWREG(baseAddr + LCDC_LCD_CTRL) |= (clkDiv <<  LCDC_LCD_CTRL_CLKDIV_SHIFT);
}

/**
* \brief  This function returns the Reversion Id of LCD controller.
*  
* \param  baseAddr   is the Memory address of LCD.
*
**/
unsigned int RasterIdGet(unsigned int baseAddr)
{
    return(HWREG(baseAddr + LCDC_PID));
}

/**
* \brief  This function enables auto under flow feature.
*
* \param  baseAddr   is the Memory address of LCD.\n
* 
* \return none.
**/
void RasterAutoUnderFlowEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_LCD_CTRL) |= LCDC_LCD_CTRL_AUTO_UFLOW_RESTART;
}

/**
* \brief  This function disables auto under flow feature.
*
* \param  baseAddr   is the Memory address of LCD.\n
* 
* \return none.
**/
void RasterAutoUnderFlowDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_LCD_CTRL) &= ~LCDC_LCD_CTRL_AUTO_UFLOW_RESTART;
}

/**
* \brief  This function will Enable Raster Control.\n
*
* \param baseAddr is the Memory address of the LCD.\n
*
* \return none.
**/
void RasterEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_RASTER_EN;
}

/**
* \brief  This function will Disable Raster Control.\n
*
* \param baseAddr is the Memory address of the LCD.\n
*
* \return none.
**/
void RasterDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_RASTER_EN;
}

/**
* \brief  This function will configures LCD to MonoChrome or color mode,
*         TFT or STN mode and palette loading mode.\n
*
* \param baseAddr    is the Memory address of the LCD.\n
* \param displayMode is the vlaue to select either TFT or STN mode.\n
*
*         displayMode can take following value.\n
*
*         RASTER_DISPLAY_MODE_TFT  -  TFT mode is selected.\n
*         RASTER_DISPLAY_MODE_STN  -  STN mode is selected.\n
*
*         Below mentioned macros are only applicable to AM335x.
*
*         RASTER_DISPLAY_MODE_TFT_PACKED   - TFT mode is selected with
*                                            24 bit packed data support.  
*         RASTER_DISPLAY_MODE_TFT_UNPACKED - TFT mode is selected with
*                                            24 bit unpacked data support.  
*
* \param displayType is the value to select either color or monochrome mode.\n
*
*         displayType can take following value.\n
*
*         RASTER_MONOCHROME  - monochrome mode is selected.\n
*         RASTER_COLOR       - color mode is selected.\n
*         
* \param paletteMode is the value to select type of palette loading.\n
* 
*        paletteMode can take following values.\n
*         
*        RASTER_PALETTE_DATA   - palette and  data is loaded.\n
*        RASTER_PALETTE        - only palette is loaded.\n
*        RASTER_DATA           - only data is loaded.\n
*
* \param flag  Optional argument depending on the display mode and type
* 
*        flag can take following values.\n
*
*        RASTER_RIGHT_ALIGNED - Right aligned output pixel data
*        RASTER_EXTRAPOLATE   - Extrapolated (to RGB565) output pixel data
*        RASTER_MONO8B        - Output 8 bit mono pixel data
*        RASTER_MONO4B        - Output 4 bit mono pixel data
* 
* \return none.
**/
void RasterModeConfig(unsigned int baseAddr, unsigned int displayMode,
                      unsigned int paletteMode, unsigned int displayType,
                      unsigned flag)
{
    /* Configures raster to TFT or STN Mode */
    HWREG(baseAddr + LCDC_RASTER_CTRL) = displayMode | paletteMode | displayType;

    if(displayMode ==  RASTER_DISPLAY_MODE_TFT)
    {
         if(flag == RASTER_RIGHT_ALIGNED)
         {
              /* Output pixel data for 1,2,4 and 8 bpp is converted to 565 format */
              HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~(LCDC_RASTER_CTRL_TFT_ALT_MAP);
         }
         else
         {
              /* Output pixel data for 1,2,4 and 8 bpp will be right aligned */
             HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_TFT_ALT_MAP;
         }
    }
    else
    {
         if(flag ==  RASTER_MONO8B)
         {
              HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_MONO8B;
         }
         else
         {
              HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_MONO8B;
         }
    }
}

/**
* \brief  This function orders the frame buffer data from
*         least to most significant bit bit/nibble/byte/word/
*
* \param baseAddr is the Memory address of the LCD module.\n
*
* \return None.   
**/
void RasterLSBDataOrderSelect(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_RD_ORDER; 
}

/**
* \brief  This function orders the frame buffer data from
*         most to least significant bit bit/nibble/byte/word/
*
* \param baseAddr is the Memory address of the LCD module.\n
*
* \return None.
**/
void RasterMSBDataOrderSelect(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_RD_ORDER;
}

/**
* \brief This function enables interrupts in LCD controller.\n
*
* \param baseAddr is the Memory address of the LCD module.
*
* \param flag is the value specifies the which interrupts to be
*        enabled.\n
*     
*         flag can take following values.\n
*
*         Below mentioned macros are only applicable to AM1808.
*
*         RASTER_ACBIAS_COUNT_INT       -  ACBias Count interrupt.\n
*         RASTER_FRAME_DONE_INT         -  Frame done interrupt.\n
*         RASTER_PALETTE_LOADED_INT     -  Palette loaded interrupt.\n
*         RASTER_SYNC_LOST_INT          -  Sync lost interrupt.\n
*         RASTER_FIFO_UNDRFLOW_INT      -  FIFO underflow interrupt.\n
*
*         Below mentioned API are only for AM335x raster.\n
*
*         RASTER_DONE_INT               -  Raster Done interrupt \n.                
*         RASTER_END_OF_FRAME0_INT      -  End of frame0 interrupt \n.
*         RASTER_END_OF_FRAME1_INT      -  End of frame1 interrupt \n.
*
* \return None.
**/
void RasterIntEnable(unsigned int baseAddr, unsigned int flag)
{
    unsigned int version = 0;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {
         HWREG(baseAddr + LCDC_IRQENABLE_SET) |= flag;
    }
    else if(RASTER_REV_AM1808 == version)
    {
         HWREG(baseAddr + LCDC_RASTER_CTRL) |= flag;
    }
    else
    {
         ;/* Do nothing */
    }
}

/**
* \brief This function disables interrupts in LCD controller.\n
*
* \param baseAddr is the Memory address of the LCD module.\n
*
* \param flag is the value specifies the which interrupts to be
*        enabled.\n
*
*         flag can take following values.\n
*
*         RASTER_ACBIAS_COUNT_INT       -  ACBias Count interrupt.\n
*         RASTER_FRAME_DONE_INT         -  Frame done interrupt.\n
*         RASTER_PALETTE_LOADED_INT     -  Palette loaded interrupt.\n
*         RASTER_SYNC_LOST_INT          -  Sync lost interrupt.\n
*         RASTER_FIFO_UNDRFLOW_INT      -  FIFO underflow interrupt.\n
*
*         Below mentioned API are only for AM335x raster.\n
*
*         RASTER_DONE_INT               -  Raster Done interrupt \n.                
*         RASTER_END_OF_FRAME0_INT      -  End of frame0 interrupt \n.
*         RASTER_END_OF_FRAME1_INT      -  End of frame1 interrupt \n.
*
* \return None.
**/
void RasterIntDisable(unsigned int baseAddr, unsigned int flag)
{
    unsigned int version;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {
         HWREG(baseAddr + LCDC_IRQENABLE_CLEAR) = flag;
    }
    else if(RASTER_REV_AM1808 == version)
    {
         HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~flag;
    }
    else
    {
         ;/* Do nothing */
    }
}

/**
* \brief This function enable nibble mode.
*
* \param baseAddr is the Memory Address of the LCD module
*
* \return None.
**/
void RasterNibbleModeEnable(unsigned int  baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) |=  LCDC_RASTER_CTRL_NIB_MODE;
}

/**
* \brief This function disable nibble mode.
*
* \param baseAddr is the Memory Address of the LCD module.
*
* \return None.
**/
void RasterNibbleModeDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_NIB_MODE;
}

/**
* \brief This function configures input FIFO delay.
*
* \param baseAddr is the Memory address of LCD module.
*
* \return None
**/
void RasterFIFODMADelayConfig(unsigned int baseAddr, unsigned int delay)
{

    HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_FIFO_DMA_DELAY;
    HWREG(baseAddr + LCDC_RASTER_CTRL) |= (delay <<                  \
                                          LCDC_RASTER_CTRL_FIFO_DMA_DELAY_SHIFT);
}
/**
* \brief This function configuers horizontal timing parametes and number of 
*        pixel per line.
*
* \param baseAddr is the Memory address of the LCD module
*
* \param numOfppl is a value which determine no of pixel required per line.
*
* \param hsw      is a value which detemines the width of HSYNC.
*
* \param hfp      horizontal front porch.
*
* \para  hbp      horizontal back porch.
**/
void RasterHparamConfig(unsigned int baseAddr, unsigned int numOfppl,
                        unsigned int hsw, unsigned int hfp,
                        unsigned hbp)
{
    unsigned int ppl;
    unsigned int version;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {
         ppl = numOfppl - 1;

         ppl = (ppl & 0x000003f0) | ((ppl & 0x00000400) >> 7);

         HWREG(baseAddr + LCDC_RASTER_TIMING_0) = ppl; 
    }
    else if(RASTER_REV_AM1808 == version)
    {
   
         ppl = (numOfppl / 16) - 1;

         HWREG(baseAddr + LCDC_RASTER_TIMING_0) =  (ppl <<                       
                                                LCDC_RASTER_TIMING_0_PPL_SHIFT);
    }
    else
    {
         ;/* Do nothing */
    }
    
    HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= ((hsw - 1) <<                   
                                               LCDC_RASTER_TIMING_0_HSW_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= ((hfp - 1) <<                   
                                               LCDC_RASTER_TIMING_0_HFP_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= ((hbp - 1) <<
                                               LCDC_RASTER_TIMING_0_HBP_SHIFT);
}

/**
* \brief This function configuers vertical timing parameters and number of
*        lines per panel.
*
* \param baseAddr is the Memory address of the LCD module
*
* \param lpp      is a value which determine the lines per panel.
*
* \param vsw      is a value which detemines the width of VSYNC.
*
* \param vfp      vertical front porch.
*
* \para  vbp      vertical back porch.
**/
void RasterVparamConfig(unsigned int baseAddr, unsigned int lpp,
                        unsigned int vsw, unsigned int vfp,
                        unsigned vbp)
{
    unsigned int version;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {

         HWREG(baseAddr + LCDC_RASTER_TIMING_1) = ((lpp - 1) & 0x3ff);

         HWREG(baseAddr + LCDC_RASTER_TIMING_2) &=  0xfbffffff;
  
         HWREG(baseAddr + LCDC_RASTER_TIMING_2) |=  (((lpp - 1) & 0x400) >> 10) 
                                                    << LCDC_RASTER_TIMING_2_LPP_B10_SHIFT;           
    }
    else if(RASTER_REV_AM1808 == version)
    {
 
         HWREG(baseAddr + LCDC_RASTER_TIMING_1) =  ((lpp - 1) <<             
                                              LCDC_RASTER_TIMING_1_LPP_SHIFT);
    }
    else
    {
         ;/* Do nothing */
    }

    HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= ((vsw - 1) <<                  
                                               LCDC_RASTER_TIMING_1_VSW_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= (vfp <<                       
                                               LCDC_RASTER_TIMING_1_VFP_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= (vbp <<
                                               LCDC_RASTER_TIMING_1_VBP_SHIFT);
}
/** 
* \brief This function configures the polartiy of various timing parameters of
*        LCD Controller.
*
* \param baseAddr  is the Memory Address of the LCD Module.
*
* \param flag      is the value which detemines polarity of various timing 
*                  parameter of LCD controller.\n
*
*                  flag can take following values.\n 
*
*                   RASTER_FRAME_CLOCK_HIGH - active high frame clock.\n                
*                   RASTER_FRAME_CLOCK_LOW  - active low frame clock.\n
*                   RASTER_LINE_CLOCK_HIGH  - active high line clock.\n
*                   RASTER_LINE_CLOCK_LOW   - active low line clock.\n
*                   RASTER_PIXEL_CLOCK_HIGH - active high pixel clock.\n               
*                   RASTER_PIXEL_CLOCK_LOW  - active low pixel clock.\n               
*                   RASTER_AC_BIAS_HIGH     - active high ac bias.\n           
*                   RASTER_AC_BIAS_LOW      - active low ac bias.\n          
*                   RASTER_SYNC_EDGE_RISING - rising sync edge.\n
*                   RASTER_SYNC_EDGE_FALLING- falling sync edge.\n
*                   RASTER_SYNC_CTRL_ACTIVE - active sync control.\n
*                   RASTER_SYNC_CTRL_INACTIVE-inactive sync control.\n
*
* \param acb_i      is the value which specify the number of AC Bias
*                   (LCD_AC_ENB_CS) output transition counts before 
*                   setting the AC bias interrupt bit in register LCD_STAT.
*
* \param acb        is value which defines the number of Line Clock
*                   (LCD_HSYNC) cycles to count before transitioning
*                    signal LCD_AC_ENB_CS.
*
* \return None.
*
**/
void RasterTiming2Configure(unsigned int baseAddr, unsigned int flag,
                            unsigned int acb_i, unsigned int acb)
{
    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= flag;

    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= (acb_i <<                    \
                                              LCDC_RASTER_TIMING_2_ACB_I_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= (acb <<                      \
                                             LCDC_RASTER_TIMING_2_ACB_SHIFT);

}
/**
* \brief This function configures DMA present inside LCD controller.
*
* \param  baseAddr is the Memory address of LCD module.
*
* \param  frmMode  is the value which detemines either to use single frame 
*                  or double frame buffer.\n
*
*                 frmMode can take following values.\n
*
*                 RASTER_SINGLE_FRAME_BUFFER - single frame buffer.\n     
*                 RASTER_DOUBLE_FRAME_BUFFER - double frame buffer.\n
*          
* \param bustSz   is the value which detemines burst size of DMA.\n
* 
*                 bustSz can take following values.\n
* 
*                 RASTER_BURST_SIZE_1   -  burst size of DMA is one.\n                
*                 RASTER_BURST_SIZE_2   -  burst size of DMA is two.\n            
*                 RASTER_BURST_SIZE_4   -  burst size of DMA is four.\n              
*                 RASTER_BURST_SIZE_16  -  burst size of DMA is sixteen.\n
*
* \param fifoTh   is the value which detemines when the input FIFO can be 
*                 read by raster controller.\n
*
*                 fifoTh can take following values.\n
*
*                 RASTER_FIFO_THRESHOLD_8    -   DMA FIFO Threshold is eight.\n             
*                 RASTER_FIFO_THRESHOLD_16   -   DMA FIFO Threshold is sixteen.\n          
*                 RASTER_FIFO_THRESHOLD_32   -   DMA FIFO Threshold is thirtytwo.\n       
*                 RASTER_FIFO_THRESHOLD_64   -   DMA FIFO Threshold is sixtyfour.\n     
*                 RASTER_FIFO_THRESHOLD_128  -   DMA FIFO Threshold is one twenty 
*                                                eight.\n
*                 RASTER_FIFO_THRESHOLD_256  -   DMA FIFO Threshold is two 
*                                                fifty six.\n     
*                 RASTER_FIFO_THRESHOLD_512  -   DMA FIFO Threshold is five 
*                                                twelve.\n    
*
* \param endian   is value determines whether to use big endian for data 
*                 reordering or not.\n
*
*                 endian can take following values.\n
*
*                 RASTER_BIG_ENDIAN_ENABLE - big endian enabled.\n
*                 RASTER_BIG_ENDIAN_ENABLE - big endian disabled.\n
*
* \return None
**/          
void RasterDMAConfig(unsigned int baseAddr, unsigned int frmMode,
                     unsigned int bustSz, unsigned int fifoTh,
                     unsigned int endian)
{
    HWREG(baseAddr + LCDC_LCDDMA_CTRL) = frmMode | bustSz | fifoTh | endian;
}

/**
* \brief  This function enables byte swap with in a half word of the dma transfer.
*
* \param baseAddr is the Memory address of the LCD module.
*
* \return None.
*
* This API is only supported for AM335x raster.
**/
void RasterByteSwapEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_LCDDMA_CTRL) |= LCDC_LCDDMA_CTRL_BYTE_SWAP;
}

/**
* \brief  This function disables byte swap with in a half word of the dma transfer.
*
* \param baseAddr is the Memory address of the LCD module.
*
* \return None.
*
* This API is only supported for AM335x raster.
**/
void RasterByteSwapDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_LCDDMA_CTRL) &= ~LCDC_LCDDMA_CTRL_BYTE_SWAP;
}

/**
* \brief  This function enables the end of frame interrupt.
*
* \param baseAddr is the Memory address of the LCD module.
*
* \return None.
*
* This API is valid only for am1808 raster.It should not be used
* for programing of am33xx raster.To Enable End of frame 0/1 interrupt
* in AM335x raster one can use "RasterIntEnable()".
*
**/
void RasterEndOfFrameIntEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_LCDDMA_CTRL) |= LCDC_LCDDMA_CTRL_EOF_INTEN;
}
/**
* \brief This function disables the end of frame interrupt.
*
* \param baseAddr is the Memory address of the LCD module.
*
* \return None.
*
* This API is valid only for am1808 raster.It should not be used
* for  programing of am33xx raster.To Disable End of frame 0/1 interrupt
* in AM335x raster one can use "RasterIntDisable API"
*
**/
void RasterEndOfFrameIntDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_LCDDMA_CTRL) &= ~LCDC_LCDDMA_CTRL_EOF_INTEN;
}

/**
* \brief This function returns status of the specified interrupts.\n
*
* \param baseAddr is the Memory address of the LCD module.\n
*
* \param flag is the value determines status of which interrupts to be
*        returned.\n
*
*        flag can take following values.\n
*
*         RASTER_ACBIAS_COUNT_INT_STAT    -  ACBias Count interrupt status.\n
*         RASTER_PALETTE_LOADED_INT_STAT  -  Palette loaded interrupt status.\n
*         RASTER_SYNC_LOST_INT_STAT       -  Sync lost interrupt status.\n
*         RASTER_FIFO_UNDRFLOW_INT_STAT   -  FIFO underflow interrupt status.\n
*         RASTER_FRAME_DONE_INT_STAT      -  frame done interrupt status.\n
*         RASTER_END_OF_FRAME0_INT_STAT   -  end of frame 0 interrupt status.\n
*         RASTER_END_OF_FRAME1_INT_STAT   -  end of frame 1 interrupt status.\n
*
*         This flag should used for Raster under AM335x 
*
*         RASTER_DONE_INT                 -  Raster Done interrupt.\n
* 
* \returns Interrupt status of Raster for AM335x or am1808 based on revid. 
**/
unsigned int RasterIntStatus(unsigned int baseAddr, unsigned int flag)
{
    unsigned int status = 0;
    unsigned int version;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {
         status = HWREG(baseAddr + LCDC_IRQSTATUS) & flag;
    }
    else if(RASTER_REV_AM1808 == version)
    {
         status = HWREG(baseAddr + LCDC_LCD_STAT) & flag;
    }
    else
    {
         ;/* Do nothing */
    }

    return status;
}

/**
* \brief This function returns raw status of the specified interrupts.\n
*
* \param baseAddr is the Memory address of the LCD module.\n
*
* \param flag is the value determines status of which interrupts to be
*        returned.\n
*
*        flag can take following values.\n
*
*         RASTER_ACBIAS_COUNT_INT_STAT    -  ACBias Count interrupt status.\n
*         RASTER_PALETTE_LOADED_INT_STAT  -  Palette loaded interrupt status.\n
*         RASTER_SYNC_LOST_INT_STAT       -  Sync lost interrupt status.\n
*         RASTER_FIFO_UNDRFLOW_INT_STAT   -  FIFO underflow interrupt status.\n
*         RASTER_FRAME_DONE_INT_STAT      -  frame done interrupt status.\n
*         RASTER_END_OF_FRAME0_INT_STAT   -  end of frame 0 interrupt status.\n
*         RASTER_END_OF_FRAME1_INT_STAT   -  end of frame 1 interrupt status.\n
*
*         This flag should used for Raster under AM335x
* 
*         RASTER_DONE_INT                 -  Frame Done interrupt.\n
*
* \return Interrupt raw status of Raster for only AM335x.
*
* If this function is used to read interrupt status of Raster for am1808,it will 
* return -1.
*
* This API is only supported for AM335x raster.
**/
int RasterIntRawStatus(unsigned int baseAddr, unsigned int flag)
{
    int status;
    unsigned int version;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {
         status = HWREG(baseAddr + LCDC_IRQSTATUS_RAW) & flag;
    }
    else
    {
         status = -1;
    }
    return status;
}

/**
* \brief This function asserts specified interrupts.\n
*
* \param baseAddr is the Memory address of the LCD module.\n
*
* \param flag is the value determines which interrupts to be
*        asserted.\n
*
*        flag can take following values.\n
*
*         RASTER_ACBIAS_COUNT_INT_STAT    -  ACBias Count interrupt status.\n
*         RASTER_PALETTE_LOADED_INT_STAT  -  Palette loaded interrupt status.\n
*         RASTER_SYNC_LOST_INT_STAT       -  Sync lost interrupt status.\n
*         RASTER_FIFO_UNDRFLOW_INT_STAT   -  FIFO underflow interrupt status.\n
*         RASTER_FRAME_DONE_INT_STAT      -  frame done interrupt status.\n
*         RASTER_END_OF_FRAME0_INT_STAT   -  end of frame 0 interrupt status.\n
*         RASTER_END_OF_FRAME1_INT_STAT   -  end of frame 1 interrupt status.\n
*
*
* This API is only supported for am33xx raster.
**/
void RasterIntRawStatusSet(unsigned int baseAddr, unsigned int flag)
{
    HWREG(baseAddr + LCDC_IRQSTATUS_RAW) |= flag;
}

/**
* \brief  This function configures base and ceiling value for
*         Frame buffer one or Frame buffer two.
*
* \param  baseAddr is the Memory Address of the LCD Module
*
* \param  base     is the base address of array which contain
*                  pixels of image to be dispalyed on lcd.
*
* \param  ceiling  is the end address of the array which contain
*                  pixels of image to be displayed on lcd.
*
* \param  flag     is the value which determines whether to write 
*                  base and ceiling to Frame Buffer one or Fram buffer two.
*
*         passing zero(i.e. 0) as argument configures base and ceiling for
*         frame buffer zero(i.e FB0).
*
*         passing one(i.e. 0) as argument configures base and ceiling for
*         frame buffer one(i.e FB1).
*
* \return None.   
*
**/
void RasterDMAFBConfig(unsigned int baseAddr, unsigned int base,
                       unsigned int  ceiling, unsigned int flag)
{
    if(flag == 0)
    {
         HWREG(baseAddr + LCDC_LCDDMA_FB0_BASE) =  base;
         HWREG(baseAddr + LCDC_LCDDMA_FB0_CEILING) = ceiling;
    }
    else
    {
         HWREG(baseAddr + LCDC_LCDDMA_FB1_BASE) =  base;
         HWREG(baseAddr + LCDC_LCDDMA_FB1_CEILING) = ceiling;
    }
}
/**
* \brief This function clear status interrupt status register.
*
* \param baseAddr is the Memory Address of the LCD Module.
*
* \param flag     is the value which detemines status of which
*                 interrupt to be cleared.\n
*  
*         flag can take following values.\n
*
*         RASTER_ACBIAS_COUNT_INT_STAT    -  ACBias Count interrupt status.\n
*         RASTER_PALETTE_LOADED_INT_STAT  -  Palette loaded interrupt status.\n
*         RASTER_SYNC_LOST_INT_STAT       -  Sync lost interrupt status.\n
*         RASTER_FIFO_UNDRFLOW_INT_STAT   -  FIFO underflow interrupt status.\n
*         RASTER_FRAME_DONE_INT_STAT      -  frame done interrupt status.\n
*         RASTER_END_OF_FRAME0_INT_STAT   -  end of frame 0 interrupt status.\n   
*         RASTER_END_OF_FRAME1_INT_STAT   -  end of frame 1 interrupt status.\n   
*         RASTER_DONE_INT                 -  Raster Done interrupt.\n    
*
* \return Interrupt status of Raster for AM335x or am1808 based on rev id.
*
**/
unsigned int  RasterClearGetIntStatus(unsigned int baseAddr,
                                      unsigned int flag)
{
    unsigned int saveStatus = 0;
    unsigned int version;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {
         saveStatus = HWREG(baseAddr + LCDC_IRQSTATUS) & flag;

         HWREG(baseAddr + LCDC_IRQSTATUS) = saveStatus;
    }
    else if(RASTER_REV_AM1808 == version)
    {
         saveStatus = HWREG(baseAddr + LCDC_LCD_STAT) & flag;

         HWREG(baseAddr + LCDC_LCD_STAT) = saveStatus;
    }
    else
    {
         ;/*Do nothing */
    }

    return (saveStatus);
}
/**
* \brief This function enables raster subpanel feature
*
* \baseAddr is the Memory Address of the LCD Module.
*
* \return none
*
**/
void RasterSubPanelEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_SUBPANEL) |= LCDC_RASTER_SUBPANEL_SPEN;
}

/**
* \brief This function disables raster subpanel feature
*
* \baseAddr is the Memory Address of the LCD Module.
*
* \return none
*
**/
void RasterSubPanelDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_SUBPANEL) &= ~LCDC_RASTER_SUBPANEL_SPEN;
}

/**
* \brief This function configures raster subpanel feature
*
* \baseAddr is the Memory Address of the LCD Module.
*
* \hols     is the value indicates the position of subpanel compared to the
*           LPPT(lines per panel threshold) value.
*
* \lppt     lines per panel threshold defines the number of lines to be 
*           refreshed
*
* \dpd      DPD(default pixel data) defines the default value of the pixel
*           data sent to the panel for the lines until LPPT is reached or
*           after passing the LPPT.
*
* \return none
*
**/
void RasterSubPanelConfig(unsigned int baseAddr, unsigned int hols,
                          unsigned int lppt, unsigned int dpd)
{
    unsigned int version;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {
         HWREG(baseAddr + LCDC_RASTER_SUBPANEL) &= 0xffff0000;

         HWREG(baseAddr + LCDC_RASTER_SUBPANEL) = ((dpd & 0xffff));
         
         HWREG(baseAddr + LCDC_RASTER_SUBPANEL2) &= 0xff00ffff;

         HWREG(baseAddr + LCDC_RASTER_SUBPANEL2) = ((dpd & 0xff0000) >> 15);

         HWREG(baseAddr + LCDC_RASTER_SUBPANEL) &= 0xfc00ffff;
                                            
         HWREG(baseAddr + LCDC_RASTER_SUBPANEL) |= ((lppt & 0x3ff) <<
                                              LCDC_RASTER_SUBPANEL_LPPT_SHIFT);

         HWREG(baseAddr + LCDC_RASTER_SUBPANEL2) &= 0xfffffeff;

         HWREG(baseAddr + LCDC_RASTER_SUBPANEL2) |= ((lppt & 0x400) >> 11) 
                                        << LCDC_RASTER_SUBPANEL_LPPT_B10_SHIFT;
                                             
    }
    else if(RASTER_REV_AM1808 == version)
    {
   
         HWREG(baseAddr + LCDC_RASTER_SUBPANEL) &= 0xfc00ffff;

         HWREG(baseAddr + LCDC_RASTER_SUBPANEL) |= (lppt <<
                                              LCDC_RASTER_SUBPANEL_LPPT_SHIFT);
    
         HWREG(baseAddr + LCDC_RASTER_SUBPANEL) &= 0xffff000f;
         HWREG(baseAddr + LCDC_RASTER_SUBPANEL) |= (dpd<<
                                              LCDC_RASTER_SUBPANEL_DPD_SHIFT);
    }
    else
    {
         ;/* Do nothing */
    }

    HWREG(baseAddr + LCDC_RASTER_SUBPANEL) &= 0xDfffffff;
    HWREG(baseAddr + LCDC_RASTER_SUBPANEL) |= (hols <<
                                              LCDC_RASTER_SUBPANEL_HOLS_SHIFT);

}

/**
* \brief This function Enables the clock for the DMA submodule,LIDD submodule and
*        for the core(which encompasses the Raster active matrix and Passive matrix).
*
* \baseAddr is the Memory Address of the LCD Module.
*
* \return none
*
* This API is only supported for AM335x raster.
**/
void RasterClocksEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_CLKC_ENABLE) =  (LCDC_CLKC_ENABLE_CORE |
                                           LCDC_CLKC_ENABLE_DMA  |
                                           LCDC_CLKC_ENABLE_LIDD);
}

/**
* \brief This function enables software clock for the raster,which encompasses
*        the raster active matrix and passive matrix logic.
*
* \baseAddr is the Memory Address of the LCD Module.
*
* \return none
*
* This API is only supported for AM335x raster.
**/
void RasterSoftWareClkEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_CLKC_ENABLE) |= LCDC_CLKC_ENABLE_CORE;
}

/**
* \brief This function disables software clock for the raster,which encompasses
*        the raster active matrix and passive matrix logic.
*
* \baseAddr is the Memory Address of the LCD Module.
*
* \return none
*
* This API is only supported for AM335x raster.
**/
void RasterSoftWareClkDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_CLKC_ENABLE) &= ~LCDC_CLKC_ENABLE_CORE;
}

/**
* \brief This function enables software clock for the DMA submodule.
*
* \baseAddr is the Memory Address of the LCD Module.
*
* \return none
*
* This API is only supported for AM335x raster.
**/
void RasterDMASoftWareClkEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_CLKC_ENABLE) |= LCDC_CLKC_ENABLE_DMA;
}

/**
* \brief This function disables software clock for the DMA submodule.
*
* \baseAddr is the Memory Address of the LCD Module.
*
* \return none
*
* This API is only supported for AM335x raster.
**/
void RasterDMASoftWareClkDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_CLKC_ENABLE) &= ~LCDC_CLKC_ENABLE_DMA;
}

/**
* \brief This function dose Software Resets for LCD module or DMA submodule or
*        Core which encompasses Raster Active Matrix and Passive Matrix
*        logic based on the "flag"  argument passed to this function.
*
* \baseAddr is the Memory Address of the LCD Module.
* \flag     It is the value which determines which module to be software
*           reseted.\n
*
*           flag can take following macros.\n
*
*           RASTER_CORE_RESET       - Software reset for  core.\n
*           RASTER_DMA_RESET        - Software reset for DMA module.\n
*           RASTER_LCD_MODULE_RESET - Software reset for LCD module.\n
*
* \return none
*
* This API is only supported for AM335x raster.
**/
void RasterSoftWareResetControlEnable(unsigned int baseAddr, unsigned int flag)
{
    if(RASTER_CORE_RESET == flag)
    {
         HWREG(baseAddr + LCDC_CLKC_RESET) |= LCDC_CLKC_RESET_CORE;
    }
    else if(RASTER_DMA_RESET == flag)
    {
         HWREG(baseAddr + LCDC_CLKC_RESET) |= LCDC_CLKC_RESET_DMA;
    }
    else if(RASTER_LCD_MODULE_RESET == flag)
    {
         HWREG(baseAddr + LCDC_CLKC_RESET) |= LCDC_CLKC_RESET_MAIN;
    }
    else
    {
         ;/* Do nothing */
    }
}

/**
* \brief This function disables Software Resets for LCD module or DMA submodule 
*        or Core which encompasses Raster Active Matrix and Passive Matrix
*        logic based on the "flag"  argument passed to this function.
*
* \baseAddr is the Memory Address of the LCD Module.
* \flag     It is the value which determines which module to be software
*           reseted.\n
*
*           flag can take following macros.\n
*
*           RASTER_CORE_RESET       - Software reset for  core.\n
*           RASTER_DMA_RESET        - Software reset for DMA module.\n
*           RASTER_LCD_MODULE_RESET - Software reset for LCD module.\n
*
* \return none
*
* This API is only supported for AM335x raster.
**/
void RasterSoftWareResetControlDisable(unsigned int baseAddr, unsigned int flag)
{
    if(RASTER_CORE_RESET == flag)
    {
         HWREG(baseAddr + LCDC_CLKC_RESET) &= ~LCDC_CLKC_RESET_CORE;
    }
    else if(RASTER_DMA_RESET == flag)
    {
         HWREG(baseAddr + LCDC_CLKC_RESET) &= ~LCDC_CLKC_RESET_DMA;
    }
    else if(RASTER_LCD_MODULE_RESET == flag)
    {
         HWREG(baseAddr + LCDC_CLKC_RESET) &= ~LCDC_CLKC_RESET_MAIN;
    }
    else
    {
         ;/*Do nothing */
    }
}

/**
* \brief  This function sets the priority for the L3 OCP Master Bus. 
* 
* \param  baseAddr is the Memory address of the LCD instace used.
* \param  flag     is the value which sets the pritority.
*
* \returns  None
*
* This API is only supported for AM335x raster.
**/
void RasterDmaMasterPrioritySet(unsigned int baseAddr, unsigned int flag)
{
    HWREG(baseAddr + LCDC_LCDDMA_CTRL) &= ~LCDC_LCDDMA_CTRL_DMA_MASTER_PRIO;
    HWREG(baseAddr + LCDC_LCDDMA_CTRL) |= flag << LCDC_LCDDMA_CTRL_DMA_MASTER_PRIO_SHIFT ;
}

/**
* \brief  This function configures raster in different standby modes based
*         on the flag argument passed to it.
* 
* \param  baseAddr is the Memory address of the LCD instace used.
* \param  flag     is the value which determines type of standby
*                  mode.\n
*
*         flag can take following values.\n
*        
*         RASTER_FORCE_STAND_BY.\n  
*         RASTER_NO_STAND_BY.\n            
*         RASTER_SMART_STAND_BY.\n         
*         RASTER_SMART_STAND_BY_WAKE_UP.\n 
*
* \returns  None
*
* This API is only supported for AM335x raster.
**/
void RasterStandbyModeConfig(unsigned int baseAddr, unsigned int flag)
{
    HWREG(baseAddr + LCDC_SYSCONFIG) &= 0xffffffcf;
    HWREG(baseAddr + LCDC_SYSCONFIG) |= flag;
}

/**
* \brief  This function configures raster in different Idle modes based
*         on the flag argument passed to it.
* 
* \param  baseAddr is the Memory address of the LCD instace used.
* \param  flag     is the value which determines type of Idle
*                  mode.\n
*
*         flag can take following macros.\n
*
*         RASTER_FORCE_IDLE_MODE.\n
*         RASTER_NO_IDLE_MODE.\n
*         RASTER_SMART_IDLE_MODE.\n
*         RASTER_SMART_IDLE_WAKE_UP.\n
*
* \returns  None
*
* This API is only supported for AM335x raster.
**/
void RasterIdleModeConfig(unsigned int baseAddr, unsigned int flag)
{
    HWREG(baseAddr + LCDC_SYSCONFIG) &= 0xfffffff3;
    HWREG(baseAddr + LCDC_SYSCONFIG) |= flag;
}

/**
* \brief  This function saves the context of Raster registers.
*         This is useful in power management, where the power supply to raster
*         controller will be cut off.
* 
* \param  baseAddr    Memory address of the LCD instace used
* \param  contextPtr  The pointer to the structure where the context has to be 
*                     saved.
* \returns  None
**/
void RasterContextSave(unsigned int baseAddr, RASTERCONTEXT *contextPtr)
{
     contextPtr->clkcEnable = HWREG(baseAddr + LCDC_CLKC_ENABLE);
     contextPtr->lcdCtrl = HWREG(baseAddr + LCDC_LCD_CTRL);
     contextPtr->lcddmaCtrl = HWREG(baseAddr + LCDC_LCDDMA_CTRL);
     contextPtr->rasterTiming2 = HWREG(baseAddr + LCDC_RASTER_TIMING_2);
     contextPtr->rasterTiming0 = HWREG(baseAddr + LCDC_RASTER_TIMING_0);
     contextPtr->rasterTiming1 = HWREG(baseAddr + LCDC_RASTER_TIMING_1);
     contextPtr->rasterCtrl = HWREG(baseAddr + LCDC_RASTER_CTRL);
     contextPtr->irqEnableSet = HWREG(baseAddr + LCDC_IRQENABLE_SET);
     contextPtr->lcddmaFb0Base = HWREG(baseAddr + LCDC_LCDDMA_FB0_BASE);
     contextPtr->lcddmaFb0Ceiling = HWREG(baseAddr + LCDC_LCDDMA_FB0_CEILING);
     contextPtr->lcddmaFb1Base = HWREG(baseAddr + LCDC_LCDDMA_FB1_BASE);
     contextPtr->lcddmaFb1Ceiling = HWREG(baseAddr + LCDC_LCDDMA_FB1_CEILING);
}

/**
* \brief  This function restores the context of Raster registers.
*         This is useful in power management, where the power supply to raster
*         controller will be cut off.
* 
* \param  baseAddr    Memory address of the LCD instace used
* \param  contextPtr  The pointer to the structure where the context has to be 
*                     restored from
* \returns  None
**/
void RasterContextRestore(unsigned int baseAddr, RASTERCONTEXT *contextPtr)
{
    HWREG(baseAddr + LCDC_CLKC_ENABLE) = contextPtr->clkcEnable;
    HWREG(baseAddr + LCDC_LCD_CTRL) =  contextPtr->lcdCtrl;
    HWREG(baseAddr + LCDC_LCDDMA_CTRL) = contextPtr->lcddmaCtrl;
    HWREG(baseAddr + LCDC_RASTER_TIMING_2) = contextPtr->rasterTiming2;
    HWREG(baseAddr + LCDC_RASTER_TIMING_0) = contextPtr->rasterTiming0;
    HWREG(baseAddr + LCDC_RASTER_TIMING_1) = contextPtr->rasterTiming1;
    HWREG(baseAddr + LCDC_RASTER_CTRL) = contextPtr->rasterCtrl;
    HWREG(baseAddr + LCDC_IRQENABLE_SET) =  contextPtr->irqEnableSet;
    HWREG(baseAddr + LCDC_LCDDMA_FB0_BASE) = contextPtr->lcddmaFb0Base;
    HWREG(baseAddr + LCDC_LCDDMA_FB0_CEILING) = contextPtr->lcddmaFb0Ceiling;
    HWREG(baseAddr + LCDC_LCDDMA_FB1_BASE) = contextPtr->lcddmaFb1Base;
    HWREG(baseAddr + LCDC_LCDDMA_FB1_CEILING) = contextPtr->lcddmaFb1Ceiling;
}

/***************************** End Of File ***********************************/
