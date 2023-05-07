/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-15     Rbb666       the first version
 */
#include <rtthread.h>
#include "rthw.h"

#include "drv_g2d.h"
#include "drv_jpeg.h"

#ifdef BSP_USING_JPEG

#define DCODE_BUFFER_SIZE           (35 * 1024)
#define JPEG_TIMEOUT                (100)

static rt_sem_t _SemaphoreJPEG = RT_NULL;
volatile static jpeg_status_t g_jpeg_status = JPEG_STATUS_NONE;

static int32_t _WaitForCallbackTimed(uint32_t TimeOut)
{
    return rt_sem_take(_SemaphoreJPEG, TimeOut) ? RT_ETIMEOUT : RT_EOK;
}

static void _decode_read(decode_drv_t *decode, int32_t x, int32_t y, void *pInBuffer, int32_t xSize, int32_t ySize)
{
    decode->decode_read(x, y, pInBuffer, xSize, ySize);
}

int JPEG_Draw_frame(decode_drv_t *decode, void *pbuffer, int32_t x0, int32_t y0)
{
    int32_t x;
    int32_t y;
    int32_t Error;
    int32_t xSize;
    int32_t ySize;
    int32_t OutBufferSize;
    uint32_t LinesDecoded;
    jpeg_color_space_t ColorSpace;

    void *pOutBuffer;
    void *_aInBuffer;

    Error = 0;
    xSize = 0;
    ySize = 0;
    x = x0;
    y = y0;

    g_jpeg_status = JPEG_STATUS_NONE;

    fsp_err_t err = FSP_SUCCESS;
    /* Initialize JPEG Codec Driver */
    err = R_JPEG_Open(&g_jpeg0_ctrl, &g_jpeg0_cfg);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        /* JPEG Codec initialization failed  */
        rt_kprintf("JPEG Codec driver initialization FAILED\n");
    }

    _aInBuffer = (uint8_t *)pbuffer;

    while (!(g_jpeg_status & JPEG_STATUS_ERROR))
    {
        /* Set in-buffer to get some information about the JPEG */
        if (R_JPEG_InputBufferSet(&g_jpeg0_ctrl, _aInBuffer,
                                  DCODE_BUFFER_SIZE) != FSP_SUCCESS)
        {
            Error = 2;
            break;
        }

        /* Wait for callback */
        if (_WaitForCallbackTimed(JPEG_TIMEOUT) == RT_ETIMEOUT)
        {
            Error = 3;
            break;
        }

        if (g_jpeg_status & JPEG_STATUS_IMAGE_SIZE_READY)
        {
            break;
        }

        /* Move pointer to next block of input data (if needed) */
        // _aInBuffer = (uint8_t *)((uint32_t) _aInBuffer + DCODE_BUFFER_SIZE);
    }

    if (!Error)
    {
        /* Get image dimensions */
        if (R_JPEG_DecodeImageSizeGet(&g_jpeg0_ctrl, (uint16_t *) &xSize,
                                      (uint16_t *) &ySize) != FSP_SUCCESS)
        {
            Error = 4;
        }
    }

    if (!Error)
    {
        /* Get color space and check dimensions accordingly */
        R_JPEG_DecodePixelFormatGet(&g_jpeg0_ctrl, &ColorSpace);
        if (g_jpeg_status & JPEG_STATUS_ERROR)
        {
            /* Image dimensions incompatible with JPEG Codec */
            Error = 5;
        }
    }

    if (!Error)
    {
        /* Set up out buffer */
        // xSize * 16 * 2
        OutBufferSize = xSize * 16 * 2;
        pOutBuffer    = (void *) decode->jpeg_out_buf;

        /* Set stride value */
        if (R_JPEG_DecodeHorizontalStrideSet(&g_jpeg0_ctrl, (uint32_t) xSize) != FSP_SUCCESS)
        {
            Error = 6;
        }
    }

    if (!Error)
    {
        /* Start decoding process by setting out-buffer */
        if (R_JPEG_OutputBufferSet(&g_jpeg0_ctrl, pOutBuffer, (uint32_t) OutBufferSize) != FSP_SUCCESS)
        {
            Error = 7;
        }
    }

    if (!Error)
    {
        while (!(g_jpeg_status & JPEG_STATUS_ERROR))
        {
            if (_WaitForCallbackTimed(JPEG_TIMEOUT) == RT_ETIMEOUT)
            {
                Error = 8;
                break;
            }

            if ((g_jpeg_status & JPEG_STATUS_OUTPUT_PAUSE) || (g_jpeg_status & JPEG_STATUS_OPERATION_COMPLETE))
            {
                /* Draw the JPEG work buffer to the framebuffer */
                R_JPEG_DecodeLinesDecodedGet(&g_jpeg0_ctrl, &LinesDecoded);

                _decode_read(decode, x, y, (void *) pOutBuffer, xSize, (int32_t)LinesDecoded);

                y = y + (int32_t)LinesDecoded;

                if (!(g_jpeg_status & JPEG_STATUS_OPERATION_COMPLETE))
                {
                    /* Set the output buffer to the next 16-line block */
                    if (R_JPEG_OutputBufferSet(&g_jpeg0_ctrl, pOutBuffer,
                                               (uint32_t) OutBufferSize) != FSP_SUCCESS)
                    {
                        Error = 10;
                        break;
                    }
                }
            }

            if (g_jpeg_status & JPEG_STATUS_INPUT_PAUSE)
            {
                /* Get next block of input data */
                /* Set the new input buffer pointer */
                if (R_JPEG_InputBufferSet(&g_jpeg0_ctrl, (void *) _aInBuffer,
                                          DCODE_BUFFER_SIZE) != FSP_SUCCESS)
                {
                    Error = 9;
                    break;
                }
            }

            if (g_jpeg_status & JPEG_STATUS_OPERATION_COMPLETE)
            {
                break;
            }
        }
    }

    if ((g_jpeg_status & JPEG_STATUS_ERROR) && (!Error))
    {
        Error = 1;
    }

    R_JPEG_Close(&g_jpeg0_ctrl);

    return Error;
}

int rt_hw_jpeg_init(void)
{
    _SemaphoreJPEG = rt_sem_create("jpeg_sem", 0, RT_IPC_FLAG_PRIO);
    if (_SemaphoreJPEG == RT_NULL)
    {
        rt_kprintf("create jpeg decode semphr failed.\n");
        return RT_ERROR;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_jpeg_init);

/*******************************************************************************************************************//**
 * @brief Decode callback function.
 * @param[in]  p_args
 * @retval     None
 **********************************************************************************************************************/
void decode_callback(jpeg_callback_args_t *p_args)
{
    rt_interrupt_enter();

    g_jpeg_status = p_args->status;

    rt_sem_release(_SemaphoreJPEG);

    rt_interrupt_leave();
}
#endif
