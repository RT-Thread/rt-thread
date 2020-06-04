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
 * @file n32g45x_dvp.c
 * @author Nations Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_dvp.h"
#include "n32g45x_rcc.h"

/**
 * @brief  Deinitializes the DVPx peripheral registers to their default reset values.
 * @param DVPx Select the DVP peripheral.
 *   This parameter can be one of the following values:
 *      DVP
 */
void DVP_DeInit(DVP_Module* DVPx)
{
    /* Check the parameters */
    assert_param(IS_DVP_ALL_PERIPH(DVPx));

    if (DVPx == DVP)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_DVP, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_DVP, DISABLE);
    }
}

/**
 * @brief  Checks whether the specified DVP flag is set or not.
 * @param DVPx Select the DVP peripheral.
 *   This parameter can be one of the following values:
 *   DVP
 * @param DVP_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg DVP_FLAG_HERR	Hsync error interrupt flag
 *     @arg DVP_FLAG_VERR	Vsync error interrupt flag
 *     @arg DVP_FLAG_FO	DATFIFO overflow intterrupt flag
 *     @arg DVP_FLAG_FW	DATFIFO watermark interrupt flag
 *     @arg DVP_FLAG_FF	DATFIFO full interrupt flag
 *     @arg DVP_FLAG_FE	DATFIFO empty interrupt flag
 *     @arg DVP_FLAG_LE	Line end interrupt flag
 *     @arg DVP_FLAG_LS	Line start interrupt flag
 *     @arg DVP_FLAG_FME	Frame end interrupt flag
 *     @arg DVP_FLAG_FMS	Frame start interrupt flag
 * @return The new state of DVP_FLAG (SET or RESET).
 */
FlagStatus DVP_GetFlagStatus(DVP_Module* DVPx, uint16_t DVP_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_DVP_ALL_PERIPH(DVPx));
    assert_param(IS_DVP_FLAG(DVP_FLAG));

    if ((DVPx->INTSTS & DVP_FLAG) != (uint16_t)RESET)
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
 * @brief  Clears the DVPx's pending flags.
 * @param DVPx Select the DVP peripheral.
 *   This parameter can be one of the following values:
 *   DVP
 * @param DVP_FLAG specifies the flag to clear.
 *   This parameter can be any combination of the following values:
 *     @arg DVP_FLAG_HERR	Hsync error interrupt flag
 *     @arg DVP_FLAG_VERR	Vsync error interrupt flag
 *     @arg DVP_FLAG_FO	DATFIFO overflow intterrupt flag
 *     @arg DVP_FLAG_FE	DATFIFO empty interrupt flag
 *     @arg DVP_FLAG_LE	Line end interrupt flag
 *     @arg DVP_FLAG_LS	Line start interrupt flag
 *     @arg DVP_FLAG_FME	Frame end interrupt flag
 *     @arg DVP_FLAG_FMS	Frame start interrupt flag
 */
void DVP_ClrFlag(DVP_Module* DVPx, uint16_t DVP_FLAG)
{
    /* Check the parameters */
    assert_param(IS_DVP_ALL_PERIPH(DVPx));
    assert_param(IS_DVP_CLEAR_FLAG(DVP_FLAG));

    DVPx->INTSTS = (uint16_t)~DVP_FLAG;
}

/**
 * @brief  Checks whether the specified DVP interrupt has occurred or not.
 * @param DVPx Select the DVP peripheral.
 *   This parameter can be one of the following values:
 *   DVP
 * @param DVP_IT specifies the DVP interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg DVP_INT_HERR	Hsync error interrupt
 *     @arg DVP_INT_VERR	Vsync error interrupt
 *     @arg DVP_INT_FO		DATFIFO overflow intterrupt
 *     @arg DVP_INT_FW		DATFIFO watermark interrupt
 *     @arg DVP_INT_FF		DATFIFO full interrupt
 *     @arg DVP_INT_FE		DATFIFO empty interrupt
 *     @arg DVP_INT_LE		Line end interrupt
 *     @arg DVP_INT_LS		Line start interrupt
 *     @arg DVP_INT_FME		Frame end interrupt
 *     @arg DVP_INT_FMS		Frame start interrupt
 * @return The new state of DVP_IT (SET or RESET).
 */
INTStatus DVP_GetIntStatus(DVP_Module* DVPx, uint16_t DVP_IT)
{
    uint32_t bitpos = 0x00, itmask = 0x00;
    INTStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_DVP_ALL_PERIPH(DVPx));
    assert_param(IS_DVP_INT(DVP_IT));

    /* Get the interrupt position */
    itmask = DVP_IT & DVPx->INTEN;
    bitpos = DVP_IT & DVPx->INTSTS;
    if ((itmask != (uint16_t)RESET) && (bitpos != (uint16_t)RESET))
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
 * @brief  Checks whether the specified DVP interrupt has occurred or not.
 * @param DVPx Select the DVP peripheral.
 *   This parameter can be one of the following values:
 *   DVP
 * @param DVP_IT specifies the DVP interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg DVP_MINT_HERR	Hsync error interrupt
 *     @arg DVP_MINT_VERR	Vsync error interrupt
 *     @arg DVP_MINT_FO		DATFIFO overflow intterrupt
 *     @arg DVP_MINT_FW		DATFIFO watermark interrupt
 *     @arg DVP_MINT_FF		DATFIFO full interrupt
 *     @arg DVP_MINT_FE		DATFIFO empty interrupt
 *     @arg DVP_MINT_LE		Line end interrupt
 *     @arg DVP_MINT_LS		Line start interrupt
 *     @arg DVP_MINT_FME	Frame end interrupt
 *     @arg DVP_MINT_FMS	Frame start interrupt
 * @return The new state of DVP_IT (SET or RESET).
 */
INTStatus DVP_GetITMarkedStatus(DVP_Module* DVPx, uint16_t DVP_IT)
{
    uint32_t itmask     = 0x00;
    INTStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_DVP_ALL_PERIPH(DVPx));
    assert_param(IS_DVP_INT(DVP_IT));

    /* Get the interrupt position */
    itmask = DVP_IT & DVPx->MINTSTS;
    if (itmask != (uint16_t)RESET)
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
 * @brief  Initializes the DVPx peripheral according to the specified
 *         parameters in the DVP_InitStruct .
 * @param DVPx Select the DVP or the UART peripheral.
 *   This parameter can be one of the following values:
 *   DVP, DVP2, DVP3, UART4 or UART5.
 * @param DVP_InitStruct pointer to a DVP_InitType structure
 *         that contains the configuration information for the specified DVP
 *         peripheral.
 */
void DVP_Init(DVP_Module* DVPx, DVP_InitType* DVP_InitStruct)
{
    uint32_t tmpregister = 0x00;

    /* Check the parameters */
    assert_param(IS_DVP_ALL_PERIPH(DVPx));
    assert_param(IS_DVP_ROW_CAPTURE(DVP_InitStruct->LineCapture));
    assert_param(IS_DVP_COLUMN_CAPTURE(DVP_InitStruct->ByteCapture));
    assert_param(IS_DVP_DATA_INVERT(DVP_InitStruct->DataInvert));
    assert_param(IS_DVP_PIXEL_POLARITY(DVP_InitStruct->PixelClkPolarity));
    assert_param(IS_DVP_VSYNC_POLARITY(DVP_InitStruct->VsyncPolarity));
    assert_param(IS_DVP_HSYNC_POLARITY(DVP_InitStruct->HsyncPolarity));
    assert_param(IS_DVP_CAPTURE_MODE(DVP_InitStruct->CaptureMode));
    assert_param(IS_DVP_FIFOWATERMARK(DVP_InitStruct->FifoWatermark));

    /*---------------------------- DVP CTRL Configuration -----------------------*/
    tmpregister = DVPx->CTRL;
    tmpregister &= 0x0FFE;

    tmpregister |= DVP_InitStruct->LineCapture | DVP_InitStruct->ByteCapture | DVP_InitStruct->DataInvert
                   | DVP_InitStruct->PixelClkPolarity | DVP_InitStruct->VsyncPolarity | DVP_InitStruct->HsyncPolarity
                   | DVP_InitStruct->CaptureMode | (DVP_InitStruct->FifoWatermark << DVP_WATER_MARK_POS);
    DVPx->CTRL = tmpregister;

    /*---------------------------- DVP WST Configuration -----------------------*/
    if (DVP_InitStruct->RowStart == 0x0000)
        DVP_InitStruct->RowStart = 0x0001;
    if (DVP_InitStruct->ColumnStart == 0x0000)
        DVP_InitStruct->ColumnStart = 0x0001;
    DVPx->WST = ((DVP_InitStruct->RowStart - 1) << 13) | (DVP_InitStruct->ColumnStart - 1);

    /*---------------------------- DVP WSIZE Configuration -----------------------*/

    DVPx->WSIZE = ((DVP_InitStruct->ImageHeight - 1) << 13) | (DVP_InitStruct->ImageWidth - 1);
}

/**
 * @brief  Fills each DVP_InitStruct member with its default value.
 * @param DVP_InitStruct pointer to a DVP_InitType structure
 *         which will be initialized.
 */
void DVP_InitStruct(DVP_InitType* DVP_InitStruct)
{
    /* DVP_InitStruct members default value */
    DVP_InitStruct->LineCapture      = DVP_LINE_CAPTURE_ALL;
    DVP_InitStruct->ByteCapture      = DVP_BYTE_CAPTURE_ALL;
    DVP_InitStruct->DataInvert       = DVP_DATA_NOTINVERT;
    DVP_InitStruct->PixelClkPolarity = DVP_PIXEL_POLARITY_RISING;
    DVP_InitStruct->VsyncPolarity    = DVP_VSYNC_POLARITY_HIGH;
    DVP_InitStruct->HsyncPolarity    = DVP_HSYNC_POLARITY_HIGH;
    DVP_InitStruct->CaptureMode      = DVP_CAPTURE_MODE_SINGLE;
    DVP_InitStruct->RowStart         = 0;
    DVP_InitStruct->ColumnStart      = 0;
    DVP_InitStruct->ImageHeight      = 480;
    DVP_InitStruct->ImageWidth       = 640;
}

/**
 * @brief  Enables or disables the DVP interface.
 * @param DVPx Select the DVP peripheral.
 *   This parameter can be one of the following values:
 *   DVP
 * @param Cmd new state of the DMA Request sources.
 *   This parameter can be: ENABLE or DISABLE.
 */
void DVP_Enable(DVP_Module* DVPx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        DVPx->CTRL |= DVP_CAPTURE_ENABLE;
    }
    else
    {
        DVPx->CTRL &= (uint32_t)~DVP_CAPTURE_ENABLE;
    }
}

/**
 * @brief  Enables or disables the DVP DMA interface.
 * @param DVPx Select the DVP peripheral.
 *   This parameter can be one of the following values:
 *   DVP
 * @param Cmd new state of the DMA Request sources.
 *   This parameter can be: ENABLE or DISABLE.
 */
void DVP_EnableDma(DVP_Module* DVPx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_DVP_ALL_PERIPH(DVPx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        DVPx->INTEN |= DVP_DMA_ENABLE;

        /* When DMA is enable, the FWM in CTRL1 should be set 1*/
        DVPx->CTRL &= ~DVP_WATER_MARK_MASK;
        DVPx->CTRL |= (1 << DVP_WATER_MARK_POS);
    }
    else
    {
        DVPx->INTEN &= (uint32_t)~DVP_DMA_ENABLE;
    }
}

/**
 * @brief  Enables or disables the DVP interface.
 * @param DVPx Select the DVP peripheral.
 *   This parameter can be one of the following values:
 *   DVP
 * @param Watermark must be 1,2,3,4.
 */
void DVP_SetFifoWatermark(DVP_Module* DVPx, uint16_t Watermark)
{
    /* Check the parameters */
    assert_param(IS_DVP_ALL_PERIPH(DVPx));

    DVPx->CTRL &= ~DVP_WATER_MARK_MASK;
    DVPx->CTRL |= Watermark << DVP_WATER_MARK_POS;
}

/**
 * @brief  Enables or disables the DVP interface.
 * @param DVPx Select the DVP peripheral.
 *   This parameter can be one of the following values:
 *   DVP
 */
uint32_t DVP_GetFifoCount(DVP_Module* DVPx)
{
    uint32_t tempty = 0, tnums = 0;
    /* Check the parameters */
    assert_param(IS_DVP_ALL_PERIPH(DVPx));

    tempty = DVPx->STS & 0x0001;
    if (tempty == 0x0000)
        return 0x0000;
    else
    {
        tnums = (DVPx->STS & 0x001E) >> 1;
        return (tnums);
    }
}

/**
 * @brief  Enables or disables the DVP interface.
 * @param DVPx Select the DVP peripheral.
 *   This parameter can be one of the following values:
 *   DVP
 * @return Data in DATFIFO
 */
uint32_t DVP_ReadFifo(DVP_Module* DVPx)
{
    /* Check the parameters */
    assert_param(IS_DVP_ALL_PERIPH(DVPx));

    return DVPx->DATFIFO;
}

/**
 * @brief Software Reset DATFIFO
 *
 * @param DVPx Select the DVP peripheral.
 *   This parameter can be one of the following values:
 *   DVP
 */
void DVP_ResetFifo(DVP_Module* DVPx)
{
    /* Check the parameters */
    assert_param(IS_DVP_ALL_PERIPH(DVPx));

    DVP->CTRL |= DVP_FIFO_SOFT_RESET;
    while (DVP->CTRL & DVP_FIFO_SOFT_RESET)
        ;
}
