/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32wb452_dvp.c
 * @author Nations
 * @version v1.0.2
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32wb452_dvp.h"
#include "n32wb452_rcc.h"

/**
 * @brief   Deinitializes the DVP peripheral registers to their default reset values.
 * @param   None
 * @retval  None
 */
void DVP_ResetReg(void)
{
    RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_DVP, ENABLE);
    RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_DVP, DISABLE);
}

/**
 * @brief  Initializes the DVP peripheral according to the specified
 *         parameters in the DVP_InitStruct .
 * @param  DVP_InitStruct pointer to a DVP_InitType structure
 *         that contains the configuration information for the specified DVP
 *         peripheral.
 * @retval  None
 */
void DVP_Init( DVP_InitType* DVP_InitStruct)
{
    uint32_t tmpregister = 0x00;

    /* Check the parameters */
    assert_param(IS_DVP_LINE_CAPTURE(DVP_InitStruct->LineCapture));
    assert_param(IS_DVP_BYTE_CAPTURE(DVP_InitStruct->ByteCapture));
    assert_param(IS_DVP_DATA_INVERT(DVP_InitStruct->DataInvert));
    assert_param(IS_DVP_PIXEL_POLARITY(DVP_InitStruct->PixelClkPolarity));
    assert_param(IS_DVP_VSYNC_POLARITY(DVP_InitStruct->VsyncPolarity));
    assert_param(IS_DVP_HSYNC_POLARITY(DVP_InitStruct->HsyncPolarity));
    assert_param(IS_DVP_CAPTURE_MODE(DVP_InitStruct->CaptureMode));
    assert_param(IS_DVP_FIFOWATERMARK(DVP_InitStruct->FifoWatermark));

    /*---------------------------- DVP CTRL Configuration -----------------------*/
    tmpregister  = 0;
    tmpregister |=  DVP_InitStruct->LineCapture   | DVP_InitStruct->ByteCapture
                  | DVP_InitStruct->DataInvert    | DVP_InitStruct->PixelClkPolarity
                  | DVP_InitStruct->VsyncPolarity | DVP_InitStruct->HsyncPolarity
                  | DVP_InitStruct->CaptureMode   | DVP_InitStruct->FifoWatermark;
    DVP->CTRL = tmpregister;

    /*---------------------------- DVP WST Configuration -----------------------*/
    if (DVP_InitStruct->RowStart)
        DVP_InitStruct->RowStart--;

    if (DVP_InitStruct->ColumnStart)
        DVP_InitStruct->ColumnStart--;

    DVP->WST = (  (((uint32_t)(DVP_InitStruct->RowStart))   << DVP_WST_VST_SHIFT)     \
                | (((uint32_t)(DVP_InitStruct->ColumnStart))<< DVP_WST_HST_SHIFT) );

    /*---------------------------- DVP WSIZE Configuration -----------------------*/
    DVP->WSIZE = ( (((uint32_t)(DVP_InitStruct->ImageHeight-1)) << DVP_WSIZE_VLINE_SHIFT) \
                |  (((uint32_t)(DVP_InitStruct->ImageWidth-1))   << DVP_WSIZE_HCNT_SHIFT) );
}

/**
 * @brief  Fills DVP_InitStruct member with its default value.
 * @param DVP_InitStruct pointer to a DVP_InitType structure
 *         which will be initialized.
 * @retval None
 */
void DVP_DafaultInitParam(DVP_InitType* DVP_InitStruct)
{
    /* DVP_InitStruct members default value */
    DVP_InitStruct->FifoWatermark       = DVP_WATER_MARK_1;
    DVP_InitStruct->LineCapture         = DVP_LINE_CAPTURE_ALL;
    DVP_InitStruct->ByteCapture         = DVP_BYTE_CAPTURE_ALL;
    DVP_InitStruct->DataInvert          = DVP_DATA_NOTINVERT;
    DVP_InitStruct->PixelClkPolarity    = DVP_PIXEL_POLARITY_FALLING;
    DVP_InitStruct->VsyncPolarity       = DVP_VSYNC_POLARITY_LOW;
    DVP_InitStruct->HsyncPolarity       = DVP_HSYNC_POLARITY_HIGH;
    DVP_InitStruct->CaptureMode         = DVP_CAPTURE_MODE_SINGLE;
    DVP_InitStruct->RowStart            = 0;
    DVP_InitStruct->ColumnStart         = 0;
    DVP_InitStruct->ImageHeight         = 240;
    DVP_InitStruct->ImageWidth          = 320;
}

/**
 * @brief  Enables or disables the DVP DMA interface.
 * @param Cmd   New state of the DMA Request.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void DVP_ConfigDma( FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* When DMA is enable, the FWM in CTRL1 should be set 1*/
        __DVP_SetFifoWatermark(DVP_WATER_MARK_1);

        __DVP_EnableDMA();
    }
    else
    {
        __DVP_DisableDMA();
    }
}

/**
 * @brief  Get the data length in FIFO.
 * @param  None.
 * @retval Current date length in FIFO
 */
uint32_t DVP_GetFifoCount(void)
{
    if (__FIFOIsNotEmpty())
        return ((DVP->STS & DVP_STS_FCNT_MASK)>>DVP_STS_FCNT_SHIFT);
    else
        return 0;
}

/**
 * @brief Software Reset FIFO
 * @param  None.
 * @retval None.
 */
void DVP_ResetFifo(void)
{
    __DVP_StopCapture();

    DVP->CTRL |= DVP_FIFO_SOFT_RESET;

    while (DVP->CTRL & DVP_FIFO_SOFT_RESET);
}
