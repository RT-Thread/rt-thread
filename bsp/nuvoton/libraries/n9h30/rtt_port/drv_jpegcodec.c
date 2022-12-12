/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-4-16       Wayne            First version
*
******************************************************************************/

#include "rtthread.h"

#include "NuMicro.h"
#include "nu_jpeg.h"
#include "drv_sys.h"

struct nu_jpeg
{
    struct rt_device  dev;
    char              *name;
    IRQn_Type         irqn;
    E_SYS_IPRST       rstidx;
    E_SYS_IPCLK       clkidx;

    struct rt_mutex   lock;
};
typedef struct nu_jpeg *nu_jpeg_t;

static BOOL volatile g_bWait = FALSE, g_jpegError = FALSE, g_bScale = FALSE, g_OutputWait = FALSE, g_InputWait = FALSE, g_u32WindowDec = FALSE, g_bEncThumbnailDownScale = FALSE, g_bEncPrimaryDownScale = FALSE;
static UINT32 volatile g_u32Stride, g_u32ScaleWidth, g_u32ScaleHeight, g_u32OpMode, g_u32EncRotate = 0;
static UINT32 volatile g_u32BufferCount, g_u32DecInputWaitAddr;
static UINT16 volatile g_u16BufferSize, g_u16ReserveSize;
static UINT32 volatile g_u32OutputFormat, g_u32windowSizeX, g_u32windowSizeY;


static PFN_JPEG_CALLBACK pfnJpegDecodeComplete = NULL;
static PFN_JPEG_CALLBACK pfnJpegDecodeError = NULL;
static PFN_JPEG_CALLBACK pfnJpegEncodeComplete = NULL;
static PFN_JPEG_HEADERDECODE_CALLBACK pfnJpegHeaderDecode = NULL;
static PFN_JPEG_DECWAIT_CALLBACK pfnJpegDecInputWait = NULL;
static PFN_JPEG_DECWAIT_CALLBACK pfnJpegDecOutputWait = NULL;

static JPEG_INFO_T jpegInfo;

/* Default Quantization-Table 0 ~ 2 */
static UINT8 g_au8QTable0[64] = { 0x06, 0x04, 0x04, 0x05, 0x04, 0x04, 0x06, 0x05,
                                  0x05, 0x05, 0x06, 0x06, 0x06, 0x07, 0x08, 0x0E,
                                  0x09, 0x08, 0x08, 0x08, 0x08, 0x11, 0x0C, 0x0D,
                                  0x0A, 0x0E, 0x14, 0x11, 0x15, 0x14, 0x13, 0x11,
                                  0x13, 0x13, 0x16, 0x18, 0x1F, 0x1A, 0x16, 0x17,
                                  0x1D, 0x17, 0x13, 0x13, 0x1B, 0x25, 0x1B, 0x1D,
                                  0x20, 0x21, 0x23, 0x23, 0x23, 0x15, 0x1A, 0x26,
                                  0x29, 0x26, 0x22, 0x28, 0x1F, 0x22, 0x23, 0x21
                                },
                                g_au8QTable1[64] = { 0x06, 0x06, 0x06, 0x08, 0x07, 0x08, 0x10, 0x09,
                                                     0x09, 0x10, 0x21, 0x16, 0x13, 0x16, 0x21, 0x21,
                                                     0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                                                     0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                                                     0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                                                     0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                                                     0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                                                     0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21
                                                   };


static struct nu_jpeg g_sNuJpeg =
{
    .name = "jpegcodec",
    .irqn = JPEG_IRQn,
    .rstidx = JPEGRST,
    .clkidx = JPEGCKEN
};

/* Interrupt Service Routine for H/W JPEG CODEC */
static void nu_jpeg_isr(int vector, void *param)
{
    UINT32 u32interruptStatus;

    /* Get the interrupt status */
    u32interruptStatus = JPEG_GET_INT_STATUS();

    /* It's Header Decode Complete Interrupt */
    if (u32interruptStatus & DHE_INTS)
    {
        UINT32 u32YuvFormat;
        UINT16 u16Height, u16Width, UVHeight, UVWidth;
        UINT16 u16WidthTmp, u16HeightTmp;
        /* Get the JPEG format */
        u32YuvFormat = JPEG_DEC_GET_DECODED_IMAGE_FORMAT();

        /* Get the decoded image dimension */
        jpegGetDecodedDimension(&u16Height, &u16Width);

        jpegInfo.jpeg_width = u16Width;
        jpegInfo.jpeg_height = u16Height;
        jpegInfo.yuvformat = u32YuvFormat;

        if (pfnJpegHeaderDecode != NULL)
        {
            if (!pfnJpegHeaderDecode())
            {
                jpegInit();
                g_bWait = FALSE;
                return;
            }
        }

        if (g_bScale)
        {
            UINT16 u16RatioH, u16RatioW;

            if (jpegCalScalingFactor(
                        g_u32OpMode,         //Up / Down Scaling
                        u16Height,               //Original Height
                        u16Width,                //Original Width
                        g_u32ScaleHeight,            //Scaled Height
                        g_u32ScaleWidth,         //Scaled Width
                        &u16RatioH,              //Horizontal Ratio
                        &u16RatioW               //Vertical Ratio
                    ) != E_SUCCESS)
            {
                g_bWait = FALSE;
                g_jpegError = TRUE;
            }
            else
            {
                jpegSetScalingFactor(g_u32OpMode, u16RatioH, u16RatioW);
                u16Width =  g_u32ScaleWidth;
                u16Height = g_u32ScaleHeight;
            }
        }
        else
        {

            if (u32YuvFormat == JPEG_DEC_YUV411)
            {
                /* 32-pixel alignment for YUV411 raw data */
                if (u16Width % 32)
                    u16Width = (u16Width & 0xFFFFFFE0) + 32;
            }
            else if ((u32YuvFormat == JPEG_DEC_YUV444) || (u32YuvFormat == JPEG_DEC_YUV422T))
            {
                /* 8-pixel alignment for YUV444 raw data */
                if (u16Width % 8)
                    u16Width = (u16Width & 0xFFFFFFF8) + 8;
            }
            else
            {
                /* 16-pixel alignment for YUV422 or YUV420 raw data */
                if (u16Width % 16)
                    u16Width = (u16Width & 0xFFFFFFF0) + 16;
            }
        }

        if (g_u32Stride >= u16Width)
        {
            jpegInfo.stride = g_u32Stride;
            g_u32Stride = g_u32Stride - u16Width;
            JPEG_SET_YSTRIDE(g_u32Stride);
            u16Width = jpegInfo.stride;
        }
        else
        {
            g_u32Stride = 0;
            JPEG_SET_YSTRIDE(0);
            jpegInfo.stride = 0;
        }

        if (g_u32OutputFormat == JPEG_DEC_PRIMARY_PLANAR_YUV || g_u32OutputFormat == JPEG_DEC_THUMBNAIL_PLANAR_YUV)
        {
            if (g_u32WindowDec)
            {
                u16WidthTmp = u16Width;
                u16HeightTmp = u16Height;

                u16Width = g_u32windowSizeX;
                u16Height = g_u32windowSizeY;
            }

            if (u32YuvFormat == JPEG_DEC_YUV411)
            {
                /* For YUV411 raw data */
                UVWidth = u16Width / 4;
            }
            else if ((u32YuvFormat == JPEG_DEC_YUV444) || (u32YuvFormat == JPEG_DEC_YUV422T))
            {
                /* For YUV444 raw data */
                UVWidth = u16Width;
            }
            /* Set the U-component and V-componente width for YUV422 or YUV420 raw data */
            else if (u16Width % 2)
                UVWidth = u16Width / 2 + 1;
            else
                UVWidth = u16Width / 2;


            /* Sets the height of U and V for YUV420 image */
            if (u32YuvFormat == JPEG_DEC_YUV420)
            {
                /* 16-pixel alignment for YUV422 or YUV420 raw data */
                if (u16Height % 16)
                    u16Height = (u16Height & 0xFFFFFFF0) + 16;
                UVHeight = u16Height / 2;
            }
            else if (u32YuvFormat == JPEG_DEC_YUV422)
            {
                /* 8-pixel alignment for YUV444 raw data */
                if (u16Height % 8)
                    u16Height = (u16Height & 0xFFFFFFF8) + 8;
                UVHeight = u16Height;
            }
            else if (u32YuvFormat == JPEG_DEC_YUV444)
            {
                /* 8-pixel alignment for YUV444 raw data */
                if (u16Height % 8)
                    u16Height = (u16Height & 0xFFFFFFF8) + 8;
                UVHeight = u16Height;
            }
            else if (u32YuvFormat == JPEG_DEC_YUV411)
            {
                /* 8-pixel alignment for YUV411 raw data */
                if (u16Height % 8)
                    u16Height = (u16Height & 0xFFFFFFF8) + 8;
                UVHeight = u16Height;
            }
            else if (u32YuvFormat == JPEG_DEC_YUV422T)
            {
                /* 16-pixel alignment for YUV422 or YUV420 raw data */
                if (u16Height % 16)
                    u16Height = (u16Height & 0xFFFFFFF0) + 16;
                UVHeight = u16Height / 2;
            }
            else
            {
                /* 8-pixel alignment for raw data */
                if (u16Height % 8)
                    u16Height = (u16Height & 0xFFFFFFF8) + 8;
                UVHeight = u16Height;
            }

            JPEG_SET_UADDR(JPEG_GET_YADDR() + u16Width * u16Height);
            JPEG_SET_VADDR(JPEG_GET_UADDR() + UVWidth * UVHeight);

            if (u32YuvFormat == JPEG_DEC_GRAY)
                jpegInfo.image_size[0] = u16Width * u16Height;
            else
                jpegInfo.image_size[0] = u16Width * u16Height + 2 * UVWidth * UVHeight;

            if (g_u32WindowDec)
            {
                u16Width = u16WidthTmp;
                u16Height = u16HeightTmp;
            }
        }
        else
        {
            if (g_u32WindowDec)
            {
                u16WidthTmp = u16Width;
                u16HeightTmp = u16Height;

                u16Width = g_u32windowSizeX;
                u16Height = g_u32windowSizeY;
            }

            if (jpegInfo.stride)
                jpegInfo.image_size[0] = jpegInfo.stride * u16Height;
            else
                jpegInfo.image_size[0] =  u16Width * u16Height;

            if (g_u32OutputFormat == JPEG_DEC_PRIMARY_PACKET_RGB888)
                jpegInfo.image_size[0] = 4 * jpegInfo.image_size[0];
            else
                jpegInfo.image_size[0] = 2 * jpegInfo.image_size[0];

            if (g_u32WindowDec)
            {
                u16Width = u16WidthTmp;
                u16Height = u16HeightTmp;
            }

        }

        /* Set the image dimension */
        jpegSetDimension(u16Height, u16Width);


        outp32(JITCR, inp32(JITCR) | Dec_Scatter_Gather);

        /* Clear interrupt status */
        JPEG_CLEAR_INT(DHE_INTS);
    }
    /* It's Decode Output Wait Interrupt */
    else if (u32interruptStatus & JPG_DOW_INTS)
    {
        if (pfnJpegDecOutputWait != NULL)
        {
            pfnJpegDecOutputWait(inp32(JYADDR0), inp32(JDOWFBS));
        }
        JPEG_CLEAR_INT(JPG_DOW_INTS);

        outp32(JITCR, inp32(JITCR) | Dec_Scatter_Gather);

    }
    /* It's Encode Complete Interrupt */
    else if (u32interruptStatus & ENC_INTS)
    {
        /* Get the Encode Bit stream length */
        jpegInfo.image_size[0] = JPEG_GET_ENC_PRIMARY_BITSTREAM_SIZE();
        jpegInfo.image_size[1] = JPEG_GET_ENC_THUMBNAIL_BITSTREAM_SIZE();
        /* Clear interrupt status */
        JPEG_CLEAR_INT(ENC_INTS);

        g_bWait = FALSE;

        if (pfnJpegEncodeComplete != NULL)
            pfnJpegEncodeComplete();
    }
    /* It's Decode Complete Interrupt */
    else if (u32interruptStatus & DEC_INTS)
    {
        UINT16 imageWidth, imageHeight;

        /* Get the image dimension */
        jpegGetDimension(&imageHeight, &imageWidth);

        if (g_u32Stride != 0)
        {
            imageWidth = imageWidth - g_u32Stride;
        }

        jpegInfo.width = imageWidth;
        jpegInfo.height = imageHeight;

        /* Clear interrupt status */
        JPEG_CLEAR_INT(DEC_INTS);
        JPEG_CLEAR_INT(JPG_DOW_INTS);

        g_bWait = FALSE;

        if (pfnJpegDecodeComplete != NULL)
            pfnJpegDecodeComplete();
    }
    /* It's Decode Error Interrupt */
    else if (u32interruptStatus & DER_INTS)
    {
        /* Clear interrupt status */
        JPEG_CLEAR_INT(DER_INTS);

        g_bWait = FALSE;
        g_jpegError = TRUE;

        if (pfnJpegDecodeError != NULL)
            pfnJpegDecodeError();
    }
    else if (u32interruptStatus & IPW_INTS)
    {
        /* Clear interrupt status */
        JPEG_CLEAR_INT(IPW_INTS);

        JPEG_DEC_RESUME_INPUT_WAIT();

        if (pfnJpegDecInputWait != NULL)
        {
            if (!pfnJpegDecInputWait((g_u32DecInputWaitAddr + (g_u32BufferCount % 2) * g_u16BufferSize), g_u16BufferSize))
            {
                jpegInit();
                g_bWait = FALSE;
                return;
            }
            g_u32BufferCount++;
        }
        else
            while (1);

    }

}

static INT jpegAdjustQTAB(UINT8 u8Mode, UINT8 u8Qadjust, UINT8 u8Qscaling)
{
    UINT32 u32Addr;
    if (u8Mode == JPEG_ENC_PRIMARY)
        u32Addr = REG_JPRIQC;
    else if (u8Mode == JPEG_ENC_THUMBNAIL)
        u32Addr = REG_JTHBQC;
    else
        return E_JPEG_INVALID_PARAM;

    outp32(u32Addr, ((u8Qadjust & 0xF) << 4) | (u8Qscaling & 0xF));
    return E_SUCCESS;
}


#if 0
//Poll the interrupt status and get if the interrupt is generated
static BOOL jpegPollInt(UINT32 u32Intflag)
{
    if (JPEG_GET_INT_STATUS() & u32Intflag)
        return 1;
    else
        return 0;
}


static UINT32 jpegPower(UINT32 u32Index, UINT32 u32Exp)
{
    if (u32Exp == 0)
        return 1;
    else
    {
        UINT32 u32Idx;
        for (u32Idx = 1; u32Idx < u32Exp; u32Idx = u32Idx + 1)
        {
            u32Index = 2 * u32Index;
        }
    }
    return u32Index;
}

static VOID jpegGetScalingFactor(
    UINT8   u8Mode,             //Up / Down Scaling
    PUINT16 pu16FactorH,        //Vertical Scaling Factor
    PUINT16 pu16FactorW         //Horizontal Scaling Factor
)
{
    if (u8Mode == JPEG_DEC_PLANAR_DOWNSCALE_MODE)
    {
        *pu16FactorH = inp32(REG_JPSCALD) & 0x3F;
        *pu16FactorW = (inp32(REG_JPSCALD) >> 8) & 0x1F;
    }
    else
    {
        *pu16FactorH = (inp32(REG_JUPRAT) >> 16) & 0x3FFF;
        *pu16FactorW = inp32(REG_JUPRAT) & 0x3FFF;
    }
}
#endif

static INT jpegSetEncodeMode(UINT8 u8SourceFormat, UINT16 u16JpegFormat)
{
    UINT8 u8Gray = 0;
    switch (u16JpegFormat)
    {
    case JPEG_ENC_PRIMARY_YUV420:
    case JPEG_ENC_PRIMARY_YUV422:
    case JPEG_ENC_THUMBNAIL_YUV420:
    case JPEG_ENC_THUMBNAIL_YUV422:
    case (JPEG_ENC_PRIMARY_YUV420 | JPEG_ENC_THUMBNAIL_YUV420):
    case (JPEG_ENC_PRIMARY_YUV422 | JPEG_ENC_THUMBNAIL_YUV422):
        outp32(REG_JMCR, (inp32(REG_JMCR) & WIN_DEC) | u16JpegFormat);
        u8Gray = 0;
        break;
    case JPEG_ENC_PRIMARY_GRAY:
    case JPEG_ENC_THUMBNAIL_GRAY:
    case (JPEG_ENC_PRIMARY_GRAY | JPEG_ENC_THUMBNAIL_GRAY):
        if (u8SourceFormat == JPEG_ENC_SOURCE_PACKET)
            return E_JPEG_INVALID_PARAM;
        else
        {
            if (u16JpegFormat == (JPEG_ENC_PRIMARY_GRAY | JPEG_ENC_THUMBNAIL_GRAY))
                outp32(REG_JMCR, 0xB0);
            else
                outp32(REG_JMCR, 0xA0);
        }
        u8Gray = EY_ONLY;
        break;
    default:
        return E_JPEG_INVALID_PARAM;
    }
    g_u32OpMode = JPEG_ENC_UPSCALE_MODE;

    if (g_bEncPrimaryDownScale)
        g_u32OpMode = JPEG_ENC_PLANAR_PRIMARY_DOWNSCALE_MODE;

    if (g_bEncThumbnailDownScale)
        g_u32OpMode = JPEG_ENC_PLANAR_THUMBNAIL_DOWNSCALE_MODE;

    if (u8SourceFormat == JPEG_ENC_SOURCE_PLANAR)
        outp32(REG_JITCR, (inp32(REG_JITCR) & (0x8 | ROTATE)) | PLANAR_ON | u8Gray);
    else if (u8SourceFormat == JPEG_ENC_SOURCE_PACKET)
        outp32(REG_JITCR, inp32(REG_JITCR) & ~(PLANAR_ON | ROTATE));
    else
        return E_JPEG_INVALID_PARAM;

    return E_SUCCESS;
}

static INT jpegSetDecodeMode(UINT32 u32OutputFormat)
{
    switch (u32OutputFormat)
    {
    case JPEG_DEC_PRIMARY_PLANAR_YUV:
    case JPEG_DEC_PRIMARY_PACKET_YUV422:
    case JPEG_DEC_PRIMARY_PACKET_RGB555:
    case JPEG_DEC_PRIMARY_PACKET_RGB555R1:
    case JPEG_DEC_PRIMARY_PACKET_RGB555R2:
    case JPEG_DEC_THUMBNAIL_PLANAR_YUV:
    case JPEG_DEC_THUMBNAIL_PACKET_YUV422:
    case JPEG_DEC_THUMBNAIL_PACKET_RGB555:
    case JPEG_DEC_PRIMARY_PACKET_RGB565:
    case JPEG_DEC_PRIMARY_PACKET_RGB565R1:
    case JPEG_DEC_PRIMARY_PACKET_RGB565R2:
    case JPEG_DEC_PRIMARY_PACKET_RGB888:
        outp32(REG_JITCR, u32OutputFormat);
        outp32(REG_JMCR, inp32(REG_JMCR) & ~ENC_DEC);
        g_u32OpMode = JPEG_DEC_PACKET_DOWNSCALE_MODE;
        g_u32OutputFormat = u32OutputFormat;
        if (u32OutputFormat == JPEG_DEC_PRIMARY_PLANAR_YUV || u32OutputFormat == JPEG_DEC_THUMBNAIL_PLANAR_YUV)
            g_u32OpMode = JPEG_DEC_PLANAR_DOWNSCALE_MODE;
        break;
    default:
        return E_JPEG_INVALID_PARAM;
    }
    return E_SUCCESS;
}

static VOID jpegDecodeTrigger(void)
{
    g_bWait = TRUE;
    g_jpegError = FALSE;

    rt_memset(&jpegInfo, 0, sizeof(jpegInfo));

    /* Decode Complete /Decode Header End/Decode Error Interrupt Enable and clear the Decode Complete /Decode Header End/Decode Error Interrupt */
    if (g_InputWait)
    {
        g_u32BufferCount = 0;
        g_u32DecInputWaitAddr = JPEG_GET_BITSTREAM_ADDR();
        if (g_OutputWait)
            JPEG_INT_ENABLE(DEC_INTE | DER_INTE | DHE_INTE | IPW_INTE | JPG_DOW_INTE);
        else
            JPEG_INT_ENABLE(DEC_INTE | DER_INTE | DHE_INTE | IPW_INTE);
    }
    else if (g_OutputWait)
    {
        JPEG_INT_ENABLE(DEC_INTE | DER_INTE | DHE_INTE | JPG_DOW_INTE);
    }
    else
        JPEG_INT_ENABLE(DEC_INTE | DER_INTE | DHE_INTE);



    JPEG_CLEAR_INT(DEC_INTS | JPEG_DER_INTS | JPEG_DHE_INTS | JPEG_IPW_INTS | JPG_DOW_INTS);

    outp32(REG_JMCR, JPG_EN | inp32(REG_JMCR));
    outp32(REG_JMCR, ~JPG_EN & inp32(REG_JMCR));
}

static VOID jpegEncodeTrigger(void)
{
    g_bWait = TRUE;
    g_jpegError = FALSE;

    g_u32OpMode = JPEG_ENC_UPSCALE_MODE;

    if (g_bEncPrimaryDownScale)
        g_u32OpMode = JPEG_ENC_PLANAR_PRIMARY_DOWNSCALE_MODE;

    if (g_bEncThumbnailDownScale)
        g_u32OpMode = JPEG_ENC_PLANAR_THUMBNAIL_DOWNSCALE_MODE;

    rt_memset(&jpegInfo, 0, sizeof(jpegInfo));

    if (g_u32EncRotate != 0)
    {
        UINT16 u16Height, u16Width;

        if (((inp32(REG_JITCR) & (PLANAR_ON | EY_ONLY)) != (PLANAR_ON)) && ((inp32(REG_JMCR) & EY422) != 0))
        {
            g_jpegError = TRUE;
            g_bWait = FALSE;
            return;
        }
        jpegGetDimension(&u16Width, &u16Height);

        if (g_u32EncRotate == JPEG_IOCTL_SET_ENCODE_PRIMARY_ROTATE_LEFT)
        {
            JPEG_SET_YADDR((JPEG_GET_YADDR() + (u16Width - 1)));
            JPEG_SET_UADDR((JPEG_GET_UADDR() + (u16Width / 2 - 1)));
            JPEG_SET_VADDR((JPEG_GET_VADDR() + (u16Width / 2 - 1)));
        }
        else
        {
            JPEG_SET_YADDR((JPEG_GET_YADDR() + ((u16Height - 1) * u16Width)));
            u16Width = JPEG_GET_USTRIDE();
            JPEG_SET_UADDR((JPEG_GET_UADDR() + ((u16Height - 2) * u16Width / 2)));
            JPEG_SET_VADDR((JPEG_GET_VADDR() + ((u16Height - 2) * u16Width / 2)));

        }
    }

    if (g_bScale)
    {
        UINT16 u16Height, u16Width, u16ratioH, u16ratioW;

        if (g_u32EncRotate != 0)
            jpegGetDimension(&u16Width, &u16Height);
        else
            jpegGetDimension(&u16Height, &u16Width);

        if (jpegCalScalingFactor(
                    g_u32OpMode, //Up / Down Scaling
                    u16Height,                   //Original Height
                    u16Width,                    //Original Width
                    g_u32ScaleHeight,        //Scaled Height
                    g_u32ScaleWidth,     //Scaled Width
                    &u16ratioH,                  //Horizontal Ratio
                    &u16ratioW                   //Vertical Ratio
                ) != E_SUCCESS)
        {
            g_jpegError = TRUE;
            g_bWait = FALSE;
            return;
        }
        else
        {
            jpegSetScalingFactor(g_u32OpMode, u16ratioH, u16ratioW);
            if (g_bEncThumbnailDownScale)
                outp32(REG_JTHBWH, ((g_u32ScaleHeight & 0x1FFF) << 16) | (g_u32ScaleWidth & 0x1FFF));
            else
            {
                if (g_u32EncRotate != 0)
                    jpegSetDimension(g_u32ScaleWidth, g_u32ScaleHeight);
                else
                    jpegSetDimension(g_u32ScaleHeight, g_u32ScaleWidth);
            }
        }
    }

    /* Encode Complete Interrupt Enable and clear the Encode Complete Interrupt */
    JPEG_INT_ENABLE(ENC_INTE);
    JPEG_CLEAR_INT(ENC_INTS);

    outp32(REG_JMCR, JPG_EN | inp32(REG_JMCR));
    outp32(REG_JMCR, ~JPG_EN & inp32(REG_JMCR));
}

static INT jpegCalScalingFactor(
    UINT8   u8Mode,             //Up / Down Scaling
    UINT16  u16Height,          //Original Height
    UINT16  u16Width,           //Original Width
    UINT16  u16ScalingHeight,   //Scaled Height
    UINT16  u16ScalingWidth,    //Scaled Width
    PUINT16 pu16RatioH,         //Horizontal Ratio
    PUINT16 pu16RatioW          //Vertical Ratio
)
{
    if (u8Mode == JPEG_ENC_UPSCALE_MODE)
    {
        if (u16ScalingHeight < u16Height || u16ScalingWidth < u16Width)
            return E_JPEG_INVALID_PARAM;

        *pu16RatioW = (UINT32)((float)(u16ScalingWidth - 1) / (float)(u16Width - 2) * 1024);
        *pu16RatioH = (UINT32)((float)(u16ScalingHeight - 1) / (float)(u16Height - 2) * 1024);

    }
    else if (u8Mode == JPEG_DEC_PACKET_DOWNSCALE_MODE)
    {
        if (u16ScalingHeight > u16Height || u16ScalingWidth > u16Width)
            return E_JPEG_INVALID_PARAM;

        *pu16RatioW = (UINT32)(((float)(u16ScalingWidth) / (u16Width - 1) * 8192));

        if (*pu16RatioW > 8192)
            *pu16RatioW = 8192;

        *pu16RatioH = (UINT32)((float)(u16ScalingHeight) / (u16Height - 1) * 8192);

        if (*pu16RatioH > 8192)
            *pu16RatioH = 8192;

    }
    else if (u8Mode == JPEG_DEC_PLANAR_DOWNSCALE_MODE || u8Mode == JPEG_ENC_PLANAR_PRIMARY_DOWNSCALE_MODE || u8Mode == JPEG_ENC_PLANAR_THUMBNAIL_DOWNSCALE_MODE)
    {
        UINT16 u16RatioW, u16RatioH;
        if (u16ScalingHeight > u16Height || u16ScalingWidth > u16Width)
            return E_JPEG_INVALID_PARAM;
        if (u16Height % u16ScalingHeight)
            return E_JPEG_INVALID_PARAM;
        if (u16Width % u16ScalingWidth)
            return E_JPEG_INVALID_PARAM;

        u16RatioW = u16Width / u16ScalingWidth;

        u16RatioW = u16RatioW / 2 - 1;

        if ((u16RatioW != 0) && (u16RatioW != 1) && (u16RatioW != 3))
            return E_JPEG_INVALID_PARAM;

        u16RatioH = u16Height / u16ScalingHeight - 1;

        if ((u16RatioH != 0) && (u16RatioH != 1) && (u16RatioH != 3) && (u16RatioH != 7))
            return E_JPEG_INVALID_PARAM;

        *pu16RatioW = u16RatioW;
        *pu16RatioH = u16RatioH;
    }
    else
        return E_JPEG_INVALID_PARAM;

    return E_SUCCESS;

}

static INT jpegSetScalingFactor(
    UINT8   u8Mode,         //Up / Down Scaling
    UINT16  u16FactorH,     //Vertical Scaling Factor
    UINT16  u16FactorW      //Horizontal Scaling Factor
)
{
    if (u8Mode == JPEG_ENC_UPSCALE_MODE)
    {
        JPEG_DEC_DISABLE_DOWNSCALING();
        JPEG_ENC_ENABLE_UPSCALING();
    }
    else if (u8Mode == JPEG_DEC_PACKET_DOWNSCALE_MODE || u8Mode == JPEG_DEC_PLANAR_DOWNSCALE_MODE || u8Mode == JPEG_ENC_PLANAR_PRIMARY_DOWNSCALE_MODE)
    {
        JPEG_DEC_ENABLE_DOWNSCALING();
        JPEG_ENC_DISABLE_UPSCALING();
    }
    else if (u8Mode == JPEG_ENC_PLANAR_THUMBNAIL_DOWNSCALE_MODE)
    {
        outp32(REG_JTSCALD, TSX_ON);
    }

    if (u8Mode == JPEG_DEC_PLANAR_DOWNSCALE_MODE || u8Mode == JPEG_ENC_PLANAR_PRIMARY_DOWNSCALE_MODE)
        outp32(REG_JPSCALD, (inp32(REG_JPSCALD) & ~(PSCALX_F | PSCALY_F)) | ((u16FactorW & 0x1F) << 8) | (u16FactorH & 0x1F));

    else if (u8Mode == JPEG_ENC_PLANAR_THUMBNAIL_DOWNSCALE_MODE)
        outp32(REG_JTSCALD, (inp32(REG_JTSCALD) & ~(TSCALX_F | TSCALY_F)) | ((u16FactorW & 0x1F) << 8) | (u16FactorH & 0x1F));
    else
    {
        outp32(REG_JPSCALD, inp32(REG_JPSCALD) & ~(PSCALX_F | PSCALY_F));
        outp32(REG_JUPRAT, ((u16FactorH & 0x3FFF) << 16) | (u16FactorW & 0x3FFF));
    }
    return E_SUCCESS;
}

static VOID jpegGetDecodedDimension(
    PUINT16 pu16Height,         //Decode/Encode Height
    PUINT16 pu16Width           //Decode/Encode Width
)
{
    *pu16Width = inp32(REG_JDECWH) & 0x0000FFFF;
    *pu16Height = inp32(REG_JDECWH) >> 16;
}


static VOID jpegSetDimension(
    UINT16 u16Height,           //Decode/Encode Height
    UINT16 u16Width             //Decode/Encode Width
)
{
    outp32(REG_JPRIWH, ((u16Height & 0x1FFF) << 16) | (u16Width & 0x1FFF));
}

static VOID jpegGetDimension(
    PUINT16 pu16Height,         //Decoded Height from bit stream
    PUINT16 pu16Width           //Decoded Width  from bit stream
)
{
    *pu16Height = inp32(REG_JPRIWH) >> 16;
    *pu16Width = inp32(REG_JPRIWH) & 0x1FFF;
}

static INT jpegSetWindowDecode(
    UINT16  u16StartMCUX,   //Start X MCU
    UINT16  u16StartMCUY,   //Horizontal Scaling Factor
    UINT16  u16EndMCUX,     //Vertical Scaling Factor
    UINT16  u16EndMCUY,     //Horizontal Scaling Factor
    UINT32  u32Stride       //Decode Output Stride
)
{
    if (u16StartMCUX >= u16EndMCUX || u16StartMCUY >= u16EndMCUY)
        return E_JPEG_INVALID_PARAM;

    outp32(REG_JWINDEC0, u16StartMCUY << 16 | u16StartMCUX);
    outp32(REG_JWINDEC1, u16EndMCUY << 16 | u16EndMCUX);
    outp32(REG_JWINDEC2, u32Stride);
    outp32(REG_JMCR, WIN_DEC);
    //sysprintf("\tJWINDEC0 0x%X\n", inp32(REG_JWINDEC0));
    //sysprintf("\tJWINDEC1 0x%X\n", inp32(REG_JWINDEC1));
    //sysprintf("\tJWINDEC2 0x%X\n", inp32(REG_JWINDEC2));
    return E_SUCCESS;
}

/**
  * @brief    The function is used to set JPEG Q Table.
  *
  * @param[in]   puQTable0:  Q Table 0
  * @param[in]   puQTable1:  Q Table 1
  * @param[in]   puQTable2:  Q Table 2
  * @param[in]   u8num: Q Table number
  *
  * @return   E_JPEG_TIMEOUT:  Time-out \n
  *           E_SUCCESS: success
  */
static INT _jpegSetQTAB(PUINT8 puQTable0, PUINT8 puQTable1, PUINT8 puQTable2, UINT8 u8num)
{
    UINT32 u32value;
    UINT32 u32TimeOut;
    int i;

    u32TimeOut = 0xFFFFFF;
    for (i = 0; i < 64; i = i + 4)
    {
        while ((inp32(REG_JMCR) & QT_BUSY) & u32TimeOut)
            u32TimeOut--;

        if (!u32TimeOut)
            return E_JPEG_TIMEOUT;

        u32value = puQTable0[i] | (puQTable0[i + 1] << 8) | (puQTable0[i + 2] << 16) | (puQTable0[i + 3] << 24);
        outp32((REG_JQTAB0 + i), u32value);
    }

    u32TimeOut = 0xFFFFFF;
    for (i = 0; i < 64; i = i + 4)
    {
        while ((inp32(REG_JMCR) & QT_BUSY) & u32TimeOut)
            u32TimeOut--;

        if (!u32TimeOut)
            return E_JPEG_TIMEOUT;

        u32value = puQTable1[i] | (puQTable1[i + 1] << 8) | (puQTable1[i + 2] << 16) | (puQTable1[i + 3] << 24);
        outp32((REG_JQTAB1 + i), u32value);
    }

    if (u8num < 3)
        return E_SUCCESS;

    outp32(JITCR, inp32(JITCR) | 0x8);

    u32TimeOut = 0xFFFFFF;

    for (i = 0; i < 64; i = i + 4)
    {
        while ((inp32(REG_JMCR) & QT_BUSY) & u32TimeOut)
            u32TimeOut--;

        if (!u32TimeOut)
            return E_JPEG_TIMEOUT;

        u32value = puQTable2[i] | (puQTable2[i + 1] << 8) | (puQTable2[i + 2] << 16) | (puQTable2[i + 3] << 24);
        outp32((REG_JQTAB2 + i), u32value);
    }

    u32TimeOut = 0xFFFFFF;
    while ((inp32(REG_JMCR) & QT_BUSY) & u32TimeOut)
        u32TimeOut--;

    if (!u32TimeOut)
        return E_JPEG_TIMEOUT;
    else
        return E_SUCCESS;

}

INT jpegSetQTAB(PUINT8 puQTable0, PUINT8 puQTable1, PUINT8 puQTable2, UINT8 u8num)
{
    INT ret = 0;
    struct nu_jpeg_ioctl  sNuJpegIoctl = {0};
    struct nu_jpeg_qtab sNuJpegQTab  = {0};

    sNuJpegQTab.puQTable0 = puQTable0;
    sNuJpegQTab.puQTable1 = puQTable1;
    sNuJpegQTab.puQTable2 = puQTable2;
    sNuJpegQTab.u8num     = u8num;

    sNuJpegIoctl.arg0 = (UINT32)&sNuJpegQTab;
    sNuJpegIoctl.arg1 = (UINT32)&ret;

    rt_device_control(&g_sNuJpeg.dev, JPEG_IOCTL_SET_QTAB, (void *)&sNuJpegIoctl);

    return ret;
}

/// @endcond HIDDEN_SYMBOLS


/** @addtogroup N9H30_JPEG_EXPORTED_FUNCTIONS JPEG Exported Functions
  @{
*/

/**
  * @brief    The function is used to initial device parameters and register.
  *
  * @return   0
  */
static VOID _jpegInit(void)
{
    /* Set the default values of the JPEG registers */
    g_bScale = FALSE;
    g_u32Stride = 0;
    g_u32BufferCount = 0;
    g_u16ReserveSize = 0;
    g_u32WindowDec = FALSE;
    g_u32windowSizeX = 0;
    g_u32windowSizeY = 0;
    g_InputWait = FALSE;
    g_bEncThumbnailDownScale = FALSE;
    g_bEncPrimaryDownScale = FALSE;
    g_OutputWait = FALSE;
    g_u32EncRotate = 0;
    pfnJpegHeaderDecode = NULL;
    pfnJpegDecInputWait = NULL;
    pfnJpegDecOutputWait = NULL;
    outp32(REG_JPRIQC, 0x000000F4);
    outp32(REG_JTHBQC, 0x000000F4);
    outp32(REG_JPRST, 0x00000004);
    outp32(REG_JTRST, 0x00000004);
    outp32(REG_JITCR, 0x00000000);
    outp32(REG_JINTCR, 0x00000000);
    outp32(JDOWFBS, 0xFFFFFFFF);

    // Disable the Primary Up-scaling & Scaling-down
    outp32(REG_JPSCALU, 0x00000000);
    outp32(REG_JPSCALD, 0x00000000);

    // Reset JUPRAT and JSRCH
    outp32(REG_JUPRAT, 0x00000000);
    outp32(REG_JSRCH, 0x00000FFF);
    //-------------------------------------------

    /* Reset JPEG (JMCR [1]) */
    outp32(REG_JMCR, 0x00000002);
    outp32(REG_JMCR, 0x00000000);
    outp32(REG_JMACR, 0x00400000);  //Can't use single buffer
}

VOID jpegInit(void)
{
    rt_device_control(&g_sNuJpeg.dev, JPEG_IOCTL_INITIAL_CODEC, (void *)RT_NULL);
}

/**
  * @brief    The function is used to check JPEG engine not busy.
  *
  * @return   TRUE: JPEG engine busy  \n
  *           FALSE: JPEG engine not busy
  */
static BOOL _jpegIsReady(void)
{
    if (g_bWait == FALSE)
        return TRUE;
    else
        return FALSE;
}

BOOL jpegIsReady(void)
{
    UINT32 u32IsReady = 0;
    struct nu_jpeg_ioctl sNuJpegIoctl = {0};

    sNuJpegIoctl.arg0 = (UINT32)&u32IsReady;

    rt_device_control(&g_sNuJpeg.dev, JPEG_IOCTL_IS_READY, (void *)&sNuJpegIoctl);

    return (BOOL)u32IsReady;
}
/**
  * @brief    The function is used to get JPEG information.
  *
  * @param[out]   *info: JPEG encode/decode information.
  *
  * @return   0
  */
static VOID _jpegGetInfo(JPEG_INFO_T *info)
{
    rt_memcpy(info, &jpegInfo, sizeof(JPEG_INFO_T));
}

VOID jpegGetInfo(JPEG_INFO_T *info)
{
    struct nu_jpeg_ioctl sNuJpegIoctl = {0};

    sNuJpegIoctl.arg0 = (UINT32)info;

    rt_device_control(&g_sNuJpeg.dev, JPEG_IOCTL_GET_INFO, (void *)&sNuJpegIoctl);
}

/**
  * @brief    The function is used to wait JPEG engine, until JPEG engine not busy.
  *
  * @return   E_SUCCESS: JPEG engine encode/decode complete \n
  *           FALSE: JPEG engine error
  */
static INT _jpegWait(void)
{
    while (1)
    {
        if (g_bWait == FALSE)
            break;
    }

    if (g_jpegError)
        return E_FAIL;

    return E_SUCCESS;
}

INT jpegWait(void)
{
    INT ret = 0;
    struct nu_jpeg_ioctl sNuJpegIoctl;

    sNuJpegIoctl.arg0 = (UINT32)&ret;
    sNuJpegIoctl.arg1 = 0;

    rt_device_control(&g_sNuJpeg.dev, JPEG_IOCTL_WAITDONE, (void *)&sNuJpegIoctl);

    return ret;
}

/**
  * @brief    The function is used to config and reset JPEG IP.
  *
  * @return   E_SUCCESS: success
  */
INT jpegOpen(void)
{
    return (rt_device_open(&g_sNuJpeg.dev, RT_DEVICE_FLAG_RDWR) == RT_EOK) ? E_SUCCESS : E_FAIL;
}

/**
  * @brief    Support some JPEG driver commands for application.
  *
  * @param[in]    cmd: Command.
  *
  * @param[in]    arg0: Arguments for the command.
  *
  * @param[in]    arg1: Arguments for the command.
  *
  * @return   0
  *
  */
VOID jpegIoctl(UINT32 cmd, UINT32 arg0, UINT32 arg1)
{
    struct nu_jpeg_ioctl sNuJpegIoctl;

    sNuJpegIoctl.arg0 = arg0;
    sNuJpegIoctl.arg1 = arg1;

    rt_device_control(&g_sNuJpeg.dev, cmd, (void *)&sNuJpegIoctl);
}

/**
  * @brief    JPEG function close.
  *
  * @return   0
  *
  */
VOID jpegClose(void)
{
    rt_device_close(&g_sNuJpeg.dev);
}

static rt_err_t nu_jpeg_init(rt_device_t dev)
{
    UINT32 u32JPGDiv = 0;
    UINT32 u32JPGSource;
    UINT32 u32HclkHz;
    nu_jpeg_t psNuJpeg = (nu_jpeg_t)dev;

    RT_ASSERT(dev != RT_NULL);

    /* Set JPEG engine clock */
    u32HclkHz = sysGetClock(SYS_HCLK234) * 1000000;
    u32JPGSource = u32HclkHz / (((inp32(REG_CLK_DIVCTL3) & 0xf0000000) >> 28) + 1);

    if (u32JPGSource > 75000000)
    {
        if (u32JPGSource % 75000000)
        {
            u32JPGDiv = (u32JPGSource / 75000000);
        }
        else
            u32JPGDiv = (u32JPGSource / 75000000) - 1;
    }
    outp32(REG_CLK_DIVCTL3, (inp32(REG_CLK_DIVCTL3) & ~(0xf0000000)) | ((u32JPGDiv & 0xf) << 28));

    rt_kprintf("JPEG Engine clock frequency is %d MHz\n", u32JPGSource / (u32JPGDiv + 1) / 1000000);

    /* Register ISR and Response JPEG Interrupt. */
    rt_hw_interrupt_install(psNuJpeg->irqn, nu_jpeg_isr, (void *)psNuJpeg, psNuJpeg->name);
    rt_hw_interrupt_umask(psNuJpeg->irqn);

    return RT_EOK;
}

static rt_err_t nu_jpeg_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_err_t result;
    nu_jpeg_t psNuJpeg = (nu_jpeg_t)dev;

    result = rt_mutex_take(&psNuJpeg->lock, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    /* Enable JPEG engine clock */
    nu_sys_ipclk_enable(psNuJpeg->clkidx);

    /* Reset JPEG codec and internal variables. */
    nu_sys_ip_reset(psNuJpeg->rstidx);
    jpegInit();

    result = rt_mutex_release(&psNuJpeg->lock);
    RT_ASSERT(result == RT_EOK);

    return RT_EOK;
}

static rt_err_t nu_jpeg_close(rt_device_t dev)
{
    rt_err_t result;
    nu_jpeg_t psNuJpeg = (nu_jpeg_t)dev;

    RT_ASSERT(dev != RT_NULL);

    result = rt_mutex_take(&psNuJpeg->lock, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    /* Reset JPEG (JMCR [1]) */
    outp32(REG_JMCR, 0x00000002);
    outp32(REG_JMCR, 0x00000000);

    /* Disable JPEG engine clock */
    nu_sys_ipclk_disable(psNuJpeg->clkidx);

    result = rt_mutex_release(&psNuJpeg->lock);
    RT_ASSERT(result == RT_EOK);

    return RT_EOK;
}

static rt_err_t nu_jpeg_control(rt_device_t dev, int cmd, void *args)
{
    JPEG_WINDOW_DECODE_T *winDecode;
    PUINT32 pu32Tmp;
    UINT32 arg0 = 0, arg1 = 0;
    rt_err_t result;
    nu_jpeg_t psNuJpeg = (nu_jpeg_t)dev;

    nu_jpeg_ioctl_t psNuJpegIoctl = (nu_jpeg_ioctl_t)args;

    RT_ASSERT(dev != RT_NULL);

    result = rt_mutex_take(&psNuJpeg->lock, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    if (psNuJpegIoctl != RT_NULL)
    {
        arg0 = psNuJpegIoctl->arg0;
        arg1 = psNuJpegIoctl->arg1;
    }

    switch (cmd)
    {
    case JPEG_IOCTL_SET_YADDR:
        JPEG_SET_YADDR(arg0);
        break;
    case JPEG_IOCTL_SET_UADDR:
        JPEG_SET_UADDR(arg0);
        break;
    case JPEG_IOCTL_SET_VADDR:
        JPEG_SET_VADDR(arg0);
        break;
    case JPEG_IOCTL_SET_YSTRIDE:
        JPEG_SET_YSTRIDE(arg0);
        break;
    case JPEG_IOCTL_SET_USTRIDE:
        JPEG_SET_USTRIDE(arg0);
        break;
    case JPEG_IOCTL_SET_VSTRIDE:
        JPEG_SET_VSTRIDE(arg0);
        break;
    case JPEG_IOCTL_SET_BITSTREAM_ADDR:
        JPEG_SET_BITSTREAM_ADDR(arg0);
        break;
    case JPEG_IOCTL_SET_SOURCE_IMAGE_HEIGHT:
        JPEG_SET_SOURCE_IMAGE_HEIGHT(arg0);
        break;
    case JPEG_IOCTL_ENC_SET_HEADER_CONTROL:
        JPEG_ENC_SET_HEADER_CONTROL(arg0);
        break;
    case JPEG_IOCTL_SET_DEFAULT_QTAB:
        jpegSetQTAB(g_au8QTable0, g_au8QTable1, 0, 2);
        break;
    case JPEG_IOCTL_SET_DECODE_MODE:
        jpegSetDecodeMode(arg0);
        break;
    case JPEG_IOCTL_SET_ENCODE_MODE:
        jpegSetEncodeMode(arg0, arg1);
        break;
    case JPEG_IOCTL_SET_DIMENSION:
        jpegSetDimension(arg0, arg1);
        break;
    case JPEG_IOCTL_ENCODE_TRIGGER:
        jpegEncodeTrigger();
        if (g_u16ReserveSize != 0)
        {
            UINT32 u32Addr = JPEG_GET_BITSTREAM_ADDR();
            outp8(u32Addr + 2, 0xFF);
            outp8(u32Addr + 3, 0xE0);
            outp8(u32Addr + 4, ((g_u16ReserveSize - 4) & 0xFF00) >> 8);
            outp8(u32Addr + 5, (g_u16ReserveSize - 4) & 0xFF);
        }
        break;
    case JPEG_IOCTL_DECODE_TRIGGER:
        jpegDecodeTrigger();
        break;
    case JPEG_IOCTL_WINDOW_DECODE:
        winDecode = (JPEG_WINDOW_DECODE_T *)arg0;
        jpegSetWindowDecode(winDecode->u16StartMCUX, winDecode->u16StartMCUY,
                            winDecode->u16EndMCUX, winDecode->u16EndMCUY, winDecode->u32Stride);
        g_u32WindowDec = TRUE;
        g_u32windowSizeX = winDecode->u32Stride;
        g_u32windowSizeY = 16 * (winDecode->u16EndMCUY - winDecode->u16StartMCUY + 1);

        break;
    case JPEG_IOCTL_SET_DECODE_STRIDE:
        g_u32Stride = arg0;
        break;
    case JPEG_IOCTL_SET_DECODE_DOWNSCALE:
        g_bScale = TRUE;
        g_u32ScaleWidth = arg1;
        g_u32ScaleHeight = arg0;
        break;
    case JPEG_IOCTL_SET_ENCODE_UPSCALE:
        g_bScale = TRUE;
        g_u32ScaleWidth = arg1;
        g_u32ScaleHeight = arg0;
        break;
    case JPEG_IOCTL_SET_HEADERDECODE_CALBACKFUN:
        pfnJpegHeaderDecode = (PFN_JPEG_HEADERDECODE_CALLBACK) arg0;
        break;
    case JPEG_IOCTL_SET_DECINPUTWAIT_CALBACKFUN:
        g_InputWait = TRUE;
        pfnJpegDecInputWait = (PFN_JPEG_DECWAIT_CALLBACK) arg0;
        JPEG_DEC_SET_INPUT_WAIT(((UINT16) arg1 / 2048));
        g_u16BufferSize = arg1 / 2;
        break;
    case JPEG_IOCTL_ADJUST_QTAB:
        jpegAdjustQTAB(arg0, ((arg1 & 0xFF00) >> 4), (arg1 & 0xFF));
        break;
    case JPEG_IOCTL_ENC_RESERVED_FOR_SOFTWARE:
        if (arg0 > 0)
        {
            UINT32 u32Tmp;

            u32Tmp = arg0 + 4;
            if (u32Tmp % 2)
                u32Tmp++;
            if ((u32Tmp % 4) == 0)
                u32Tmp += 2;
            if (u32Tmp >= 0xFFFF)
                u32Tmp = 65534;

            outp32(REG_JPSCALU, inp32(REG_JPSCALU) | A_JUMP);
            outp32(JRESERVE, u32Tmp);
            g_u16ReserveSize = u32Tmp;
        }
        break;
    case JPEG_IOCTL_SET_ENCODE_PRIMARY_RESTART_INTERVAL:
        outp32(REG_JPRST, arg0);
        break;
    case JPEG_IOCTL_SET_ENCODE_THUMBNAIL_RESTART_INTERVAL:
        outp32(REG_JTRST, arg0);
        break;
    case JPEG_IOCTL_GET_ENCODE_PRIMARY_RESTART_INTERVAL:
        pu32Tmp = (PUINT32) arg0;
        *pu32Tmp = inp32(REG_JPRST);
        break;
    case JPEG_IOCTL_GET_ENCODE_THUMBNAIL_RESTART_INTERVAL:
        pu32Tmp = (PUINT32) arg0;
        *pu32Tmp = inp32(REG_JTRST);
        break;

    case JPEG_IOCTL_SET_THUMBNAIL_DIMENSION:
        outp32(REG_JTHBWH, ((arg0 & 0x1FFF) << 16) | (arg1 & 0x1FFF));
        break;
    case JPEG_IOCTL_SET_ENCODE_SW_OFFSET:
        outp32(REG_JOFFSET, arg0);
        break;
    case JPEG_IOCTL_GET_THUMBNAIL_DIMENSION:
        pu32Tmp = (PUINT32) arg0;
        *pu32Tmp = inp32(REG_JTHBWH) >> 16;
        pu32Tmp = (PUINT32) arg1;
        *pu32Tmp = inp32(REG_JTHBWH) & 0x1FFF;
        break;
    case JPEG_IOCTL_GET_ENCODE_SW_OFFSET:
        pu32Tmp = (PUINT32) arg0;
        *pu32Tmp = inp32(REG_JOFFSET);
        break;
    case JPEG_IOCTL_SET_ENCODE_PRIMARY_DOWNSCALE:
        g_bScale = TRUE;
        g_bEncPrimaryDownScale = TRUE;
        g_u32ScaleWidth = arg1;
        g_u32ScaleHeight = arg0;
        break;
    case JPEG_IOCTL_SET_ENCODE_THUMBNAIL_DOWNSCALE:
        g_bScale = TRUE;
        g_bEncThumbnailDownScale = TRUE;
        g_u32ScaleWidth = arg1;
        g_u32ScaleHeight = arg0;
        break;
    case JPEG_IOCTL_SET_ENCODE_PRIMARY_ROTATE_RIGHT:
        g_u32EncRotate = JPEG_IOCTL_SET_ENCODE_PRIMARY_ROTATE_RIGHT;
        outp32(REG_JITCR, (inp32(REG_JITCR) & ~ROTATE) | ROTATE);
        break;
    case JPEG_IOCTL_SET_ENCODE_PRIMARY_ROTATE_LEFT:
        g_u32EncRotate = JPEG_IOCTL_SET_ENCODE_PRIMARY_ROTATE_LEFT;
        outp32(REG_JITCR, (inp32(REG_JITCR) & ~ROTATE) | 0x1000);
        break;
    case JPEG_IOCTL_SET_ENCODE_PRIMARY_ROTATE_NORMAL:
        g_u32EncRotate = 0;
        outp32(REG_JITCR, (inp32(REG_JITCR) & ~ROTATE));
        break;
    case JPEG_IOCTL_SET_DECOUTPUTWAIT_CALBACKFUN:
        pfnJpegDecOutputWait = (PFN_JPEG_DECWAIT_CALLBACK) arg0;
        break;
    case JPEG_IOCTL_SET_DECOUTPUTWAIT:
        outp32(JYADDR0, arg0);
        outp32(JDOWFBS, arg1);
        g_OutputWait = TRUE;
        break;
    case JPEG_IOCTL_GET_DECOUTPUTWAIT_ADDR:
        pu32Tmp = (PUINT32) arg0;
        *pu32Tmp = inp32(JYADDR0);
        break;
    case JPEG_IOCTL_GET_DECOUTPUTWAIT_SIZE:
        pu32Tmp = (PUINT32) arg0;
        *pu32Tmp = inp32(JDOWFBS);
        break;
    case JPEG_IOCTL_SET_DECODE_COMPLETE_CALBACKFUN:
        pfnJpegDecodeComplete = (PFN_JPEG_CALLBACK) arg0;
        break;
    case JPEG_IOCTL_SET_ENCODE_COMPLETE_CALBACKFUN:
        pfnJpegEncodeComplete = (PFN_JPEG_CALLBACK) arg0;
        break;
    case JPEG_IOCTL_SET_DECODE_ERROR_CALBACKFUN:
        pfnJpegDecodeError = (PFN_JPEG_CALLBACK) arg0;
        break;

    /* Extended IOCTL command */
    case JPEG_IOCTL_SET_QTAB:
    {
        nu_jpeg_qtab_t psJpegQtab = (nu_jpeg_qtab_t)arg0;
        INT *pi32ret = (INT *)arg1;
        *pi32ret = _jpegSetQTAB(psJpegQtab->puQTable0, psJpegQtab->puQTable1, psJpegQtab->puQTable2, psJpegQtab->u8num);
    }
    break;
    case JPEG_IOCTL_INITIAL_CODEC:
        _jpegInit();
        break;
    case JPEG_IOCTL_GET_INFO:
        _jpegGetInfo((JPEG_INFO_T *)arg0);
        break;
    case JPEG_IOCTL_IS_READY:
    {
        UINT32 *pu32ret = (UINT32 *)arg0;
        *pu32ret = _jpegIsReady();

    }
    break;
    case JPEG_IOCTL_WAITDONE:
    {
        INT *pi32ret = (INT *)arg0;
        *pi32ret = _jpegWait();
    }
    break;

    default:
        break;
    }

    result = rt_mutex_release(&psNuJpeg->lock);
    RT_ASSERT(result == RT_EOK);

    return RT_EOK;
}

/* Hardward JPEG codec init */
static int rt_hw_jpeg_init(void)
{
    rt_err_t ret = RT_EOK;

    /* Register sdcard device */
    g_sNuJpeg.dev.type  = RT_Device_Class_Miscellaneous;
    g_sNuJpeg.dev.init  = nu_jpeg_init;
    g_sNuJpeg.dev.open  = nu_jpeg_open;
    g_sNuJpeg.dev.close = nu_jpeg_close;
    g_sNuJpeg.dev.read  = RT_NULL;
    g_sNuJpeg.dev.write = RT_NULL;
    g_sNuJpeg.dev.control = nu_jpeg_control;

    /* Private */
    g_sNuJpeg.dev.user_data = (void *)&g_sNuJpeg;

    ret = rt_mutex_init(&g_sNuJpeg.lock, "jpeg_lock", RT_IPC_FLAG_PRIO);
    RT_ASSERT(ret == RT_EOK);

    /* Only support single opening. */
    ret = rt_device_register(&g_sNuJpeg.dev, g_sNuJpeg.name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
    RT_ASSERT(ret == RT_EOK);

    return (int)ret;
}
INIT_DEVICE_EXPORT(rt_hw_jpeg_init);
