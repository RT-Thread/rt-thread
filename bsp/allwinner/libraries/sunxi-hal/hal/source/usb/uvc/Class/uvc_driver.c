/*
********************************************************************************
*                                USB UVC Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  uvc_driver.c
*
* Author        :  Kingvan
*
* Date          :  2013/03/26
*
* Description   :  USB VIDEO CONTROL Driver中对USB接口设备的处理
*
* Others        :  NULL
*
* History:
*       <time>          <author>     <version >     <desc>
*      2013.03.26       Kingvan         1.0         build this file
*
********************************************************************************
*/
//#include  "usb_host_config.h"
//#include  "usb_host_base_types.h"
#include  "usb_os_platform.h"
#include  "error.h"

#include  "usb_utils_find_zero_bit.h"
#include  "usb_list.h"
#include  "list_head_ext.h"

#include  "usb_host_common.h"
#include  "usb_gen_dev_mod.h"
#include  "urb.h"
#include  "usb_core_interface.h"
#include  "usb_msg.h"

//#include  "usbh_disk_info.h"
//#include  "usbh_buff_manager.h"
//#include  "usbh_disk_remove_time.h"

#include "video.h"
#include "uvcvideo.h"
#include "uvc_driver.h"

extern struct usb_interface *usb_ifnum_to_if(struct usb_host_virt_dev *dev, u32  ifnum);

static struct uvc_format_desc uvc_fmts[] = {
    {
    "YUV 4:2:2 (YUYV)",
    UVC_GUID_FORMAT_YUY2,
    V4L2_PIX_FMT_YUYV,
    },
    {
    "YUV 4:2:2 (YUYV)",
    UVC_GUID_FORMAT_YUY2_ISIGHT,
    V4L2_PIX_FMT_YUYV,
    },
    {
    "YUV 4:2:0 (NV12)",
    UVC_GUID_FORMAT_NV12,
    V4L2_PIX_FMT_NV12,
    },
    {
    "MJPEG",
    UVC_GUID_FORMAT_MJPEG,
    V4L2_PIX_FMT_MJPEG,
    },
    {
    "YVU 4:2:0 (YV12)",
    UVC_GUID_FORMAT_YV12,
    V4L2_PIX_FMT_YVU420,
    },
    {
    "YUV 4:2:0 (I420)",
    UVC_GUID_FORMAT_I420,
    V4L2_PIX_FMT_YUV420,
    },
    {
    "YUV 4:2:0 (M420)",
    UVC_GUID_FORMAT_M420,
    V4L2_PIX_FMT_M420,
    },
    {
    "YUV 4:2:2 (UYVY)",
    UVC_GUID_FORMAT_UYVY,
    V4L2_PIX_FMT_UYVY,
    },
    {
    "Greyscale (8-bit)",
    UVC_GUID_FORMAT_Y800,
    V4L2_PIX_FMT_GREY,
    },
    {
    "Greyscale (16-bit)",
    UVC_GUID_FORMAT_Y16,
    V4L2_PIX_FMT_Y16,
    },
    {
    "RGB Bayer",
    UVC_GUID_FORMAT_BY8,
    V4L2_PIX_FMT_SBGGR8,
    },
    {
    "RGB565",
    UVC_GUID_FORMAT_RGBP,
    V4L2_PIX_FMT_RGB565,
    },
};

static void uvc_set_entity(struct uvc_entity *entity, __u16 type, __u8 id,  __u32 num_pads, __u32 extra_size)
{
    __u32 num_inputs;
    __u32 size;
    __u32 i;

    if( entity == NULL )
        return;

    num_inputs = (type & UVC_TERM_OUTPUT) ? num_pads : num_pads - 1;

    entity->id = id;
    entity->type = type;

    entity->bNrInPins = num_inputs;

    return;
}

struct usb_host_virt_endpoint *uvc_find_endpoint(struct usb_host_virt_interface *alts, __u8 epaddr)
{
    struct usb_host_virt_endpoint *ep;
    unsigned int i;

    for (i = 0; i < alts->desc.bNumEndpoints; ++i) {
        ep = &alts->endpoint[i];
        if (ep->desc.bEndpointAddress == epaddr)
            return ep;
    }

    return NULL;
}

static struct uvc_format_desc *uvc_format_by_guid(const __u8 guid[16])
{
    unsigned int len = sizeof(uvc_fmts) / sizeof((uvc_fmts)[0]);//ARRAY_SIZE(uvc_fmts);
    unsigned int i;

    for (i = 0; i < len; ++i) {
        if (memcmp(guid, uvc_fmts[i].guid, 16) == EPDK_TRUE)
            return &uvc_fmts[i];
    }

    return NULL;
}

static __u32 uvc_colorspace(const __u8 primaries)
{
    static const __u8 colorprimaries[] = {
        0,
        V4L2_COLORSPACE_SRGB,
        V4L2_COLORSPACE_470_SYSTEM_M,
        V4L2_COLORSPACE_470_SYSTEM_BG,
        V4L2_COLORSPACE_SMPTE170M,
        V4L2_COLORSPACE_SMPTE240M,
    };

    if ( primaries < (sizeof(colorprimaries) / sizeof((colorprimaries)[0])) )
        return colorprimaries[primaries];

    return 0;
}

/* Simplify a fraction using a simple continued fraction decomposition. The
 * idea here is to convert fractions such as 333333/10000000 to 1/30 using
 * 32 bit arithmetic only. The algorithm is not perfect and relies upon two
 * arbitrary parameters to remove non-significative terms from the simple
 * continued fraction decomposition. Using 8 and 333 for n_terms and threshold
 * respectively seems to give nice results.
 */
void uvc_simplify_fraction(__u32 *numerator, __u32 *denominator,
        __u32 n_terms, __u32 threshold)
{
    __u32 *an;
    __u32 x, y, r;
    __u32 i, n;

    an = hal_malloc(n_terms * sizeof(*an));
    if (an == NULL)
    {
        hal_log_err("esMEMS_Malloc fail\n");
        return;
    }

    /* Convert the fraction to a simple continued fraction. See
     * http://mathforum.org/dr.math/faq/faq.fractions.html
     * Stop if the current term is bigger than or equal to the given
     * threshold.
     */
    x = *numerator;
    y = *denominator;

    for (n = 0; n < n_terms && y != 0; ++n) {
        an[n] = x / y;
        if (an[n] >= threshold) {
            if (n < 2)
                n++;
            break;
        }

        r = x - an[n] * y;
        x = y;
        y = r;
    }

    /* Expand the simple continued fraction back to an integer fraction. */
    x = 0;
    y = 1;

    for (i = n; i > 0; --i) {
        r = y;
        y = an[i-1] * y + x;
        x = r;
    }

    *numerator = y;
    *denominator = x;
    hal_free(an);
}

/* Convert a fraction to a frame interval in 100ns multiples. The idea here is
 * to compute numerator / denominator * 10000000 using 32 bit fixed point
 * arithmetic only.
 */
__u32 uvc_fraction_to_interval(__u32 numerator, __u32 denominator)
{
    __u32 multiplier;

    /* Saturate the result if the operation would overflow. */
    if (denominator == 0 ||
        numerator/denominator >= ((__u32)-1)/10000000)
        return (__u32)-1;

    /* Divide both the denominator and the multiplier by two until
     * numerator * multiplier doesn't overflow. If anyone knows a better
     * algorithm please let me know.
     */
    multiplier = 10000000;
    while (numerator > ((__u32)-1)/multiplier) {
        multiplier /= 2;
        denominator /= 2;
    }

    return denominator ? numerator * multiplier / denominator : 0;
}

static int uvc_parse_format(UVCDev_t *UVCDev,
    struct uvc_streaming *streaming, struct uvc_format *format,
    __u32 **intervals, unsigned char *buffer, int buflen)
{
    struct usb_interface *intf = streaming->intf;
    struct usb_host_virt_interface *alts = intf->cur_altsetting;
    struct uvc_format_desc *fmtdesc;
    struct uvc_frame *frame;
    const __u8 *start = buffer;
    __u32 interval;
    __u32 i, n;
    __u8 ftype;

    format->type = buffer[2];
    format->index = buffer[3];


    switch (buffer[2]) {
    case UVC_VS_FORMAT_UNCOMPRESSED:
    case UVC_VS_FORMAT_FRAME_BASED:
        n = buffer[2] == UVC_VS_FORMAT_UNCOMPRESSED ? 27 : 28;
        if (buflen < n) {
            hal_log_err("device %d videostreaming interface %d FORMAT error\n",
                        UVCDev->pusb_dev->devnum,
                        alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        /* Find the format descriptor from its GUID. */
        fmtdesc = uvc_format_by_guid(&buffer[5]);

        if (fmtdesc != NULL) {
            uvc_strlcpy(format->name, fmtdesc->name, sizeof format->name);
            format->fcc = fmtdesc->fcc;
        } else {
            hal_log_err("Unknown video format %pUl\n", &buffer[5]);
            snprintf(format->name, sizeof(format->name), "%pUl\n", &buffer[5]);
            format->fcc = 0;
        }

        format->bpp = buffer[21];
        if (buffer[2] == UVC_VS_FORMAT_UNCOMPRESSED) {
            ftype = UVC_VS_FRAME_UNCOMPRESSED;
        } else {
            ftype = UVC_VS_FRAME_FRAME_BASED;
            if (buffer[27])
                format->flags = UVC_FMT_FLAG_COMPRESSED;
        }
        break;

    case UVC_VS_FORMAT_MJPEG:
        if (buflen < 11) {
            hal_log_err("device %d videostreaming interface %d FORMAT error\n",
                    UVCDev->pusb_dev->devnum,
                   alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        uvc_strlcpy(format->name, "MJPEG", sizeof format->name);
        format->fcc = V4L2_PIX_FMT_MJPEG;
        format->flags = UVC_FMT_FLAG_COMPRESSED;
        format->bpp = 0;
        ftype = UVC_VS_FRAME_MJPEG;
        break;

    case UVC_VS_FORMAT_DV:
        if (buflen < 9) {
            hal_log_err("device %d videostreaming interface %d FORMAT error\n",
                    UVCDev->pusb_dev->devnum,
                   alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        switch (buffer[8] & 0x7f) {
        case 0:
            uvc_strlcpy(format->name, "SD-DV", sizeof format->name);
            break;
        case 1:
            uvc_strlcpy(format->name, "SDL-DV", sizeof format->name);
            break;
        case 2:
            uvc_strlcpy(format->name, "HD-DV", sizeof format->name);
            break;
        default:
            hal_log_err("device %d videostreaming interface %d: unknown DV format %u\n",
                    UVCDev->pusb_dev->devnum,
                   alts->desc.bInterfaceNumber, buffer[8]);
            return -EINVAL;
        }

        uvc_strlcat(format->name, buffer[8] & (1 << 7) ? " 60Hz" : " 50Hz", sizeof format->name);

        format->fcc = V4L2_PIX_FMT_DV;
        format->flags = UVC_FMT_FLAG_COMPRESSED | UVC_FMT_FLAG_STREAM;
        format->bpp = 0;
        ftype = 0;

        /* Create a dummy frame descriptor. */
        frame = &format->frame[0];
        memset(&format->frame[0], 0, sizeof format->frame[0]);
        frame->bFrameIntervalType = 1;
        frame->dwDefaultFrameInterval = 1;
        frame->dwFrameInterval = *intervals;
        *(*intervals)++ = 1;
        format->nframes = 1;
        break;

    case UVC_VS_FORMAT_MPEG2TS:
    case UVC_VS_FORMAT_STREAM_BASED:
        /* Not supported yet. */
    default:
        hal_log_err("device %d videostreaming interface %d unsupported format %u\n",
                UVCDev->pusb_dev->devnum, alts->desc.bInterfaceNumber,
               buffer[2]);
        return -EINVAL;
    }

    hal_log_err("Found format %s.\n", format->name);

    buflen -= buffer[0];
    buffer += buffer[0];


    /* Parse the frame descriptors. Only uncompressed, MJPEG and frame
     * based formats have frame descriptors.
     */
    while (buflen > 2 && buffer[1] == USB_DT_CS_INTERFACE &&
           buffer[2] == ftype) {
        frame = &format->frame[format->nframes];
        if (ftype != UVC_VS_FRAME_FRAME_BASED)
            n = buflen > 25 ? buffer[25] : 0;
        else
            n = buflen > 21 ? buffer[21] : 0;

        n = n ? n : 3;

        if (buflen < 26 + 4*n) {
            hal_log_err("device %d videostreaming interface %d FRAME error\n", UVCDev->pusb_dev->devnum,
                   alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        frame->bFrameIndex = buffer[3];
        frame->bmCapabilities = buffer[4];
        frame->wWidth = get_unaligned_le16(&buffer[5]);
        frame->wHeight = get_unaligned_le16(&buffer[7]);
        frame->dwMinBitRate = get_unaligned_le32(&buffer[9]);
        frame->dwMaxBitRate = get_unaligned_le32(&buffer[13]);
        if (ftype != UVC_VS_FRAME_FRAME_BASED) {
            frame->dwMaxVideoFrameBufferSize =
                get_unaligned_le32(&buffer[17]);
            frame->dwDefaultFrameInterval =
                get_unaligned_le32(&buffer[21]);
            frame->bFrameIntervalType = buffer[25];
        } else {
            frame->dwMaxVideoFrameBufferSize = 0;
            frame->dwDefaultFrameInterval =
                get_unaligned_le32(&buffer[17]);
            frame->bFrameIntervalType = buffer[21];
        }
        frame->dwFrameInterval = *intervals;

        /* Several UVC chipsets screw up dwMaxVideoFrameBufferSize
         * completely. Observed behaviours range from setting the
         * value to 1.1x the actual frame size to hardwiring the
         * 16 low bits to 0. This results in a higher than necessary
         * memory usage as well as a wrong image size information. For
         * uncompressed formats this can be fixed by computing the
         * value from the frame size.
         */
        if (!(format->flags & UVC_FMT_FLAG_COMPRESSED))
            frame->dwMaxVideoFrameBufferSize = format->bpp
                * frame->wWidth * frame->wHeight / 8;

        /* Some bogus devices report dwMinFrameInterval equal to
         * dwMaxFrameInterval and have dwFrameIntervalStep set to
         * zero. Setting all null intervals to 1 fixes the problem and
         * some other divisions by zero that could happen.
         */
        for (i = 0; i < n; ++i) {
            interval = get_unaligned_le32(&buffer[26+4*i]);
            *(*intervals)++ = interval ? interval : 1;
        }

        /* Make sure that the default frame interval stays between
         * the boundaries.
         */
        n -= frame->bFrameIntervalType ? 1 : 2;
        frame->dwDefaultFrameInterval =
            min(frame->dwFrameInterval[n],
                max(frame->dwFrameInterval[0],
                frame->dwDefaultFrameInterval));

        if (UVCDev->quirks & UVC_QUIRK_RESTRICT_FRAME_RATE) {
            frame->bFrameIntervalType = 1;
            frame->dwFrameInterval[0] =
                frame->dwDefaultFrameInterval;
        }

        hal_log_err("- %ux%u (%u.%u fps)\n",
            frame->wWidth, frame->wHeight,
            10000000/frame->dwDefaultFrameInterval,
            (100000000/frame->dwDefaultFrameInterval)%10);

        format->nframes++;
        buflen -= buffer[0];
        buffer += buffer[0];
    }

    if (buflen > 2 && buffer[1] == USB_DT_CS_INTERFACE &&
        buffer[2] == UVC_VS_STILL_IMAGE_FRAME) {
        buflen -= buffer[0];
        buffer += buffer[0];
    }

    if (buflen > 2 && buffer[1] == USB_DT_CS_INTERFACE &&
        buffer[2] == UVC_VS_COLORFORMAT) {
        if (buflen < 6) {
            hal_log_err("device %d videostreaming interface %d COLORFORMAT error\n",
                    UVCDev->pusb_dev->devnum,
                   alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        format->colorspace = uvc_colorspace(buffer[3]);

        buflen -= buffer[0];
        buffer += buffer[0];
    }

    return buffer - start;
}

static int uvc_parse_streaming(UVCDev_t *UVCDev, struct usb_interface *intf)
{
    struct uvc_streaming *streaming = NULL;
    struct uvc_format *format;
    struct uvc_frame *frame;
    struct usb_host_virt_interface *alts = &intf->altsetting[0];
    __u8 *_buffer, *buffer = alts->extra;
    __s32 _buflen, buflen = alts->extralen;
    __u32 nformats = 0, nframes = 0, nintervals = 0;
    __u32 size, i, n, p;
    __u32 *interval;
    __u16 psize;
    __s32 ret = -EINVAL;

    if (intf->cur_altsetting->desc.bInterfaceSubClass != UVC_SC_VIDEOSTREAMING) {
        hal_log_err("device %d interface %d isn't a video streaming interface\n", UVCDev->pusb_dev->devnum,
            intf->altsetting[0].desc.bInterfaceNumber);
        return -EINVAL;
    }


//  if (usb_driver_claim_interface(&uvc_driver.driver, intf, dev)) {
//      hal_log_err("device %d interface %d is already claimed\n", dev->udev->devnum,
//          intf->altsetting[0].desc.bInterfaceNumber);
//      return -EINVAL;
//  }

    streaming = hal_malloc(sizeof(*streaming));
    if (streaming == NULL) {
        hal_log_err("esMEMS_Malloc fail\n");
//      usb_driver_release_interface(&uvc_driver.driver, intf);
        return -EINVAL;
    } else {
        memset(streaming, 0, sizeof *streaming);
    }

//  mutex_init(&streaming->mutex);
    streaming->dev = UVCDev;
    streaming->intf = intf;//usb_get_intf(intf);
    streaming->intfnum = intf->cur_altsetting->desc.bInterfaceNumber;

    /* The Pico iMage webcam has its class-specific interface descriptors
     * after the endpoint descriptors.
     */
    if (buflen == 0) {
        for (i = 0; i < alts->desc.bNumEndpoints; ++i) {
            struct usb_host_virt_endpoint *ep = &alts->endpoint[i];

            if (ep->extralen == 0)
                continue;

            if (ep->extralen > 2 &&
                ep->extra[1] == USB_DT_CS_INTERFACE) {
                hal_log_err("trying extra data from endpoint %u.\n", i);
                buffer = alts->endpoint[i].extra;
                buflen = alts->endpoint[i].extralen;
                break;
            }
        }
    }


    /* Skip the standard interface descriptors. */
    while (buflen > 2 && buffer[1] != USB_DT_CS_INTERFACE) {
        buflen -= buffer[0];
        buffer += buffer[0];
    }

    if (buflen <= 2) {
        hal_log_err("no class-specific streaming interface descriptors found.\n");
        goto error;
    }

    /* Parse the header descriptor. */
    switch (buffer[2]) {
    case UVC_VS_OUTPUT_HEADER:
        streaming->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
        size = 9;
        break;

    case UVC_VS_INPUT_HEADER:
        streaming->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        size = 13;
        break;

    default:
        hal_log_err("device %d videostreaming interface %d HEADER descriptor not found.\n", UVCDev->pusb_dev->devnum,
            alts->desc.bInterfaceNumber);
        goto error;
    }

    p = buflen >= 4 ? buffer[3] : 0;
    n = buflen >= size ? buffer[size-1] : 0;

    if (buflen < size + p*n) {
        hal_log_err("device %d videostreaming interface %d HEADER descriptor is invalid.\n",
                UVCDev->pusb_dev->devnum, alts->desc.bInterfaceNumber);
        goto error;
    }

    streaming->header.bNumFormats = p;
    streaming->header.bEndpointAddress = buffer[6];
    if (buffer[2] == UVC_VS_INPUT_HEADER) {
        streaming->header.bmInfo = buffer[7];
        streaming->header.bTerminalLink = buffer[8];
        streaming->header.bStillCaptureMethod = buffer[9];
        streaming->header.bTriggerSupport = buffer[10];
        streaming->header.bTriggerUsage = buffer[11];
    } else {
        streaming->header.bTerminalLink = buffer[7];
    }
    streaming->header.bControlSize = n;

//  streaming->header.bmaControls = kmemdup(&buffer[size], p * n, GFP_KERNEL);
//  if (streaming->header.bmaControls == NULL) {
//      ret = -ENOMEM;
//      goto error;
//  }

    buflen -= buffer[0];
    buffer += buffer[0];

    _buffer = buffer;
    _buflen = buflen;

    /* Count the format and frame descriptors. */
    while (_buflen > 2 && _buffer[1] == USB_DT_CS_INTERFACE) {
        switch (_buffer[2]) {
        case UVC_VS_FORMAT_UNCOMPRESSED:
        case UVC_VS_FORMAT_MJPEG:
        case UVC_VS_FORMAT_FRAME_BASED:
            nformats++;
            break;

        case UVC_VS_FORMAT_DV:
            /* DV format has no frame descriptor. We will create a
             * dummy frame descriptor with a dummy frame interval.
             */
            nformats++;
            nframes++;
            nintervals++;
            break;

        case UVC_VS_FORMAT_MPEG2TS:
        case UVC_VS_FORMAT_STREAM_BASED:
            hal_log_err("device %d videostreaming interface %d FORMAT %u is not supported.\n",
                    UVCDev->pusb_dev->devnum,
                    alts->desc.bInterfaceNumber, _buffer[2]);
            break;

        case UVC_VS_FRAME_UNCOMPRESSED:
        case UVC_VS_FRAME_MJPEG:
            nframes++;
            if (_buflen > 25)
                nintervals += _buffer[25] ? _buffer[25] : 3;
            break;

        case UVC_VS_FRAME_FRAME_BASED:
            nframes++;
            if (_buflen > 21)
                nintervals += _buffer[21] ? _buffer[21] : 3;
            break;
        }

        _buflen -= _buffer[0];
        _buffer += _buffer[0];
    }

    if (nformats == 0) {
        hal_log_err("device %d videostreaming interface %d has no supported formats defined.\n",
                UVCDev->pusb_dev->devnum, alts->desc.bInterfaceNumber);
        goto error;
    }

    size = nformats * sizeof *format + nframes * sizeof *frame
         + nintervals * sizeof *interval;
    format = hal_malloc(size);//注意释放
    if (format == NULL) {
        hal_log_err("esMEMS_Malloc fail\n");
        ret = -ENOMEM;
        goto error;
    }
    else {
        memset(format, 0, size);
    }

    frame = (struct uvc_frame *)&format[nformats];
    interval = (__u32 *)&frame[nframes];//?????????

    streaming->format = format;
    streaming->nformats = nformats;

    /* Parse the format descriptors. */
    while (buflen > 2 && buffer[1] == USB_DT_CS_INTERFACE) {
        switch (buffer[2]) {
        case UVC_VS_FORMAT_UNCOMPRESSED:
        case UVC_VS_FORMAT_MJPEG:
        case UVC_VS_FORMAT_DV:
        case UVC_VS_FORMAT_FRAME_BASED:
            format->frame = frame;
            ret = uvc_parse_format(UVCDev, streaming, format, &interval, buffer, buflen);//???????
            if (ret < 0)
                goto error;

            frame += format->nframes;
            format++;


            buflen -= ret;
            buffer += ret;
            continue;

        default:
            break;
        }

        buflen -= buffer[0];
        buffer += buffer[0];
    }

    if (buflen)
        hal_log_err("device %d videostreaming interface %d has %u bytes of trailing descriptor garbage.\n",
                UVCDev->pusb_dev->devnum, alts->desc.bInterfaceNumber, buflen);

    /* Parse the alternate settings to find the maximum bandwidth. */
    for (i = 0; i < intf->num_altsetting; ++i) {
        struct usb_host_virt_endpoint *ep;
        alts = &intf->altsetting[i];
        ep = uvc_find_endpoint(alts, streaming->header.bEndpointAddress);
        if (ep == NULL)
            continue;

        psize = ep->desc.wMaxPacketSize;
        psize = (psize & 0x07ff) * (1 + ((psize >> 11) & 3));
        if (psize > streaming->maxpsize)
            streaming->maxpsize = psize;
    }

    UVCDev->streams = streaming;

    return 0;

error:
//  usb_driver_release_interface(&uvc_driver.driver, intf);
//  usb_put_intf(intf);
    hal_free(streaming->format);
//  kfree(streaming->header.bmaControls);
    hal_free(streaming);
    return ret;
}

/* Parse vendor-specific extensions. */
static int uvc_parse_vendor_control(UVCDev_t *UVCDev, const __u8 *buffer, __s32 buflen)
{
    struct usb_host_virt_dev *udev = UVCDev->pusb_dev;
    struct usb_host_virt_interface *alts = UVCDev->pusb_intf->cur_altsetting;
    struct uvc_entity *unit;
    __u32 n, p;
    __s32 handled = 0;

    switch (le16_to_cpu(UVCDev->pusb_dev->descriptor.idVendor)) {
    case 0x046d:        /* Logitech */
        if (buffer[1] != 0x41 || buffer[2] != 0x01)
            break;

        /* Logitech implements several vendor specific functions
         * through vendor specific extension units (LXU).
         *
         * The LXU descriptors are similar to XU descriptors
         * (see "USB Device Video Class for Video Devices", section
         * 3.7.2.6 "Extension Unit Descriptor") with the following
         * differences:
         *
         * ----------------------------------------------------------
         * 0        bLength     1    Number
         *  Size of this descriptor, in bytes: 24+p+n*2
         * ----------------------------------------------------------
         * 23+p+n   bmControlsType  N   Bitmap
         *  Individual bits in the set are defined:
         *  0: Absolute
         *  1: Relative
         *
         *  This bitset is mapped exactly the same as bmControls.
         * ----------------------------------------------------------
         * 23+p+n*2 bReserved   1   Boolean
         * ----------------------------------------------------------
         * 24+p+n*2 iExtension  1   Index
         *  Index of a string descriptor that describes this
         *  extension unit.
         * ----------------------------------------------------------
         */
        p = buflen >= 22 ? buffer[21] : 0;
        n = buflen >= 25 + p ? buffer[22+p] : 0;

        if (buflen < 25 + p + 2*n) {
            hal_log_err("device %d videocontrol interface %d EXTENSION_UNIT error\n",
                udev->devnum, alts->desc.bInterfaceNumber);
            break;
        }


        unit = &UVCDev->entities[0];
        uvc_set_entity(unit, buffer[2], buffer[3], p + 1, n);

        uvc_set_entity(unit, UVC_VC_EXTENSION_UNIT, buffer[3], p + 1, 2*n);

        memcpy(unit->un.extension.guidExtensionCode, &buffer[4], 16);
        unit->un.extension.bNumControls = buffer[20];
//      memcpy(unit->baSourceID, &buffer[22], p);
        unit->un.extension.bControlSize = buffer[22+p];
        unit->un.extension.bmControls = (__u8 *)unit + sizeof(*unit);
        unit->un.extension.bmControlsType = (__u8 *)unit + sizeof(*unit)
                           + n;
        memcpy(unit->un.extension.bmControls, &buffer[23+p], 2*n);

        if (buffer[24+p+2*n] != 0)
            usb_string(udev, buffer[24+p+2*n], unit->name,
                   sizeof unit->name);
        else
            sprintf(unit->name, "Extension %u", buffer[3]);

        handled = 1;
        break;
    }

    return handled;
}

static int uvc_parse_standard_control(UVCDev_t *UVCDev, const __u8 *buffer, __s32 buflen)
{
    struct usb_host_virt_dev        *udev = UVCDev->pusb_dev;
    struct usb_interface            *intf = NULL;
    struct usb_host_virt_interface  *alts = UVCDev->pusb_intf->cur_altsetting;
    unsigned int i, n, p, len;
    __u16 type;
    struct uvc_entity *unit, *term;

    switch (buffer[2]) {
    case UVC_VC_HEADER:
        n = buflen >= 12 ? buffer[11] : 0;

        if (buflen < 12 || buflen < 12 + n) {
            hal_log_err("device %d videocontrol interface %d HEADER error\n", udev->devnum, alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        UVCDev->uvc_version = get_unaligned_le16(&buffer[3]);
        UVCDev->clock_frequency = get_unaligned_le32(&buffer[7]);

        /* Parse all USB Video Streaming interfaces. */
        if( n > 1 )
            __err("uvc_parse_standard_control %d > 1\n", n);
        for (i = 0; i < n; ++i) {
            intf = usb_ifnum_to_if(udev, buffer[12+i]);
            if (intf == NULL) {
                hal_log_err("device %d interface %d doesn't exists\n", udev->devnum, i);
                continue;
            }

            uvc_parse_streaming(UVCDev, intf);
        }
        break;

    case UVC_VC_INPUT_TERMINAL:
        if (buflen < 8) {
            hal_log_err("device %d videocontrol interface %d INPUT_TERMINAL error\n", udev->devnum, alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        /* Make sure the terminal type MSB is not null, otherwise it
         * could be confused with a unit.
         */
        type = get_unaligned_le16(&buffer[4]);
        if ((type & 0xff00) == 0) {
            hal_log_err("device %d videocontrol interface %d INPUT_TERMINAL %d has invalid type 0x%04x, skipping\n",
                    udev->devnum,
                    alts->desc.bInterfaceNumber,
                    buffer[3], type);
            return 0;
        }

        n = 0;
        p = 0;
        len = 8;

        if (type == UVC_ITT_CAMERA) {
            n = buflen >= 15 ? buffer[14] : 0;
            len = 15;

        } else if (type == UVC_ITT_MEDIA_TRANSPORT_INPUT) {
            n = buflen >= 9 ? buffer[8] : 0;
            p = buflen >= 10 + n ? buffer[9+n] : 0;
            len = 10;
        }

        if (buflen < len + n + p) {
            hal_log_err("device %d videocontrol interface %d INPUT_TERMINAL error\n",
                udev->devnum, alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        term = &UVCDev->entities[UVC_VC_INPUT_TERMINAL];
        uvc_set_entity(term, type | UVC_TERM_INPUT, buffer[3], 1, n + p);

        if (UVC_ENTITY_TYPE(term) == UVC_ITT_CAMERA) {
            term->un.camera.bControlSize = n;
            term->un.camera.bmControls = (__u8 *)term + sizeof *term;
            term->un.camera.wObjectiveFocalLengthMin =
                get_unaligned_le16(&buffer[8]);
            term->un.camera.wObjectiveFocalLengthMax =
                get_unaligned_le16(&buffer[10]);
            term->un.camera.wOcularFocalLength =
                get_unaligned_le16(&buffer[12]);
            memcpy(term->un.camera.bmControls, &buffer[15], n);
        } else if (UVC_ENTITY_TYPE(term) ==
               UVC_ITT_MEDIA_TRANSPORT_INPUT) {
            term->un.media.bControlSize = n;
            term->un.media.bmControls = (__u8 *)term + sizeof *term;
            term->un.media.bTransportModeSize = p;
            term->un.media.bmTransportModes = (__u8 *)term
                             + sizeof *term + n;
            memcpy(term->un.media.bmControls, &buffer[9], n);
            memcpy(term->un.media.bmTransportModes, &buffer[10+n], p);
        }

        if (buffer[7] != 0)
            usb_string(udev, buffer[7], term->name,
                   sizeof term->name);
        else if (UVC_ENTITY_TYPE(term) == UVC_ITT_CAMERA)
            sprintf(term->name, "Camera %u", buffer[3]);
        else if (UVC_ENTITY_TYPE(term) == UVC_ITT_MEDIA_TRANSPORT_INPUT)
            sprintf(term->name, "Media %u", buffer[3]);
        else
            sprintf(term->name, "Input %u", buffer[3]);

        break;

    case UVC_VC_OUTPUT_TERMINAL:
        if (buflen < 9) {
            hal_log_err("device %d videocontrol interface %d OUTPUT_TERMINAL error\n",
                udev->devnum, alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        /* Make sure the terminal type MSB is not null, otherwise it
         * could be confused with a unit.
         */
        type = get_unaligned_le16(&buffer[4]);
        if ((type & 0xff00) == 0) {
            hal_log_err("device %d videocontrol interface %d OUTPUT_TERMINAL %d has invalid type 0x%04x, skipping\n",
                    udev->devnum,
                    alts->desc.bInterfaceNumber, buffer[3], type);
            return 0;
        }

        term = &UVCDev->entities[UVC_VC_OUTPUT_TERMINAL];
        uvc_set_entity(term, type | UVC_TERM_OUTPUT, buffer[3], 1, 0);

        //memcpy(term->baSourceID, &buffer[7], 1);

        if (buffer[8] != 0)
            usb_string(udev, buffer[8], term->name, sizeof term->name);
        else
            sprintf(term->name, "Output %u", buffer[3]);

        break;

    case UVC_VC_SELECTOR_UNIT:
        p = buflen >= 5 ? buffer[4] : 0;

        if (buflen < 5 || buflen < 6 + p) {
            hal_log_err("device %d videocontrol interface %d SELECTOR_UNIT error\n",
                udev->devnum, alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        unit = &UVCDev->entities[UVC_VC_SELECTOR_UNIT];
        uvc_set_entity(unit, buffer[2], buffer[3], p + 1, 0);

        //memcpy(unit->baSourceID, &buffer[5], p);

        if (buffer[5+p] != 0)
            usb_string(udev, buffer[5+p], unit->name,
                   sizeof unit->name);
        else
            sprintf(unit->name, "Selector %u", buffer[3]);

        break;

    case UVC_VC_PROCESSING_UNIT:
        n = buflen >= 8 ? buffer[7] : 0;
        p = UVCDev->uvc_version >= 0x0110 ? 10 : 9;

        if (buflen < p + n) {
            hal_log_err("device %d videocontrol interface %d PROCESSING_UNIT error\n",
                udev->devnum, alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        unit = &UVCDev->entities[UVC_VC_PROCESSING_UNIT];
        uvc_set_entity(unit, buffer[2], buffer[3], 2, n);

        //memcpy(unit->baSourceID, &buffer[4], 1);
        unit->un.processing.wMaxMultiplier = get_unaligned_le16(&buffer[5]);
        unit->un.processing.bControlSize = buffer[7];
        unit->un.processing.bmControls = (__u8 *)unit + sizeof *unit;
        memcpy(unit->un.processing.bmControls, &buffer[8], n);
        if (UVCDev->uvc_version >= 0x0110)
            unit->un.processing.bmVideoStandards = buffer[9+n];

        if (buffer[8+n] != 0)
            usb_string(udev, buffer[8+n], unit->name,
                   sizeof unit->name);
        else
            sprintf(unit->name, "Processing %u", buffer[3]);

        break;

    case UVC_VC_EXTENSION_UNIT:
        p = buflen >= 22 ? buffer[21] : 0;
        n = buflen >= 24 + p ? buffer[22+p] : 0;

        if (buflen < 24 + p + n) {
            hal_log_err("device %d videocontrol interface %d EXTENSION_UNIT error\n",
                udev->devnum, alts->desc.bInterfaceNumber);
            return -EINVAL;
        }

        unit = &UVCDev->entities[UVC_VC_EXTENSION_UNIT];
        uvc_set_entity(unit, buffer[2], buffer[3], p + 1, n);

        memcpy(unit->un.extension.guidExtensionCode, &buffer[4], 16);
        unit->un.extension.bNumControls = buffer[20];
        //memcpy(unit->baSourceID, &buffer[22], p);
        unit->un.extension.bControlSize = buffer[22+p];
        unit->un.extension.bmControls = (__u8 *)unit + sizeof *unit;
        memcpy(unit->un.extension.bmControls, &buffer[23+p], n);

        if (buffer[23+p+n] != 0)
            usb_string(udev, buffer[23+p+n], unit->name,
                   sizeof unit->name);
        else
            sprintf(unit->name, "Extension %u", buffer[3]);

        break;

    default:
        hal_log_err("Found an unknown CS_INTERFACE descriptor (%u)\n", buffer[2]);
        break;
    }

    return 0;
}


static int uvc_parse_control_entry(UVCDev_t *UVCDev)
{
    struct usb_host_virt_interface *alts = UVCDev->pusb_intf->cur_altsetting;
    __u8 *buffer = alts->extra;
    __s32 buflen = alts->extralen;
    __s32 ret;

    /* Parse the default alternate setting only, as the UVC specification
     * defines a single alternate setting, the default alternate setting
     * zero.
     */
    while (buflen > 2) {
        if (uvc_parse_vendor_control(UVCDev, buffer, buflen) ||
            buffer[1] != USB_DT_CS_INTERFACE)
            goto next_descriptor;

        if ((ret = uvc_parse_standard_control(UVCDev, buffer, buflen)) < 0)
            return ret;

next_descriptor:
        buflen -= buffer[0];
        buffer += buffer[0];
    }


    return 0;
}

static int uvc_parse_control_exit(UVCDev_t *UVCDev)
{
    if( UVCDev->streams != NULL )
    {
        if( UVCDev->streams->format != NULL )
        {
            hal_free(UVCDev->streams->format);
            UVCDev->streams->format = NULL;
        }
        hal_free(UVCDev->streams);
        UVCDev->streams = NULL;
    }
    return 0;
}

/* ------------------------------------------------------------------------
 * USB probe, disconnect, suspend and resume
 */
__s32 uvc_probe(UVCDev_t *UVCDev, const struct usb_drv_dev_match_table *id)
{
    int ret;

    if (id->idVendor && id->idProduct)
        hal_log_err("Probing known UVC device (%04x:%04x)\n",
                    id->idVendor, id->idProduct);
    else
        hal_log_err("Probing generic UVC device\n");

    UVCDev->quirks = (1) ? id->driver_info : -1;
    hal_log_err("device quirks 0x%x\n", UVCDev->quirks);

    /* Parse the Video Class control descriptor. */
    if (uvc_parse_control_entry(UVCDev) < 0) {
        hal_log_err("Unable to parse UVC descriptors.\n");
        return -ENODEV;
    }

    hal_log_err("Found UVC %u.%02x device %s (%04x:%04x)\n",
            UVCDev->uvc_version >> 8, UVCDev->uvc_version & 0xff,
            UVCDev->pusb_dev->product ? UVCDev->pusb_dev->product : "<unnamed>",
            le16_to_cpu(UVCDev->pusb_dev->descriptor.idVendor),
            le16_to_cpu(UVCDev->pusb_dev->descriptor.idProduct));

    if (UVCDev->quirks != id->driver_info) {
        hal_log_err("Forcing device quirks to 0x%x by module parameter for testing purpose.\n", UVCDev->quirks);
        hal_log_err("Please report required quirks to the linux-uvc-devel mailing list.\n");
    }

    if (uvc_video_init(UVCDev->streams)) {
        hal_log_err("uvc_video_init failed.\n");
        return -ENODEV;
    }


    hal_log_err("UVC device initialized.\n");
    return 0;

}

void uvc_disconnect(UVCDev_t *UVCDev)
{
    uvc_parse_control_exit(UVCDev);
}

