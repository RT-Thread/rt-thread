/*
********************************************************************************
*                                USB UVC Driver
*
*                (c) Copyright 2010-2015, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  usbvideo.h
*
* Author        :  Kingvan.Tong
*
* Date          :  2013.03.26
*
* Description   :  USB Webcam
*
* Others        :  NULL
*
* History:
*       <time>      <version >      <author>            <desc>
*      2013.03.26      1.0           Kingvan.Tong       build this file
*
********************************************************************************
*/

#ifndef _USB_VIDEO_H_
#define _USB_VIDEO_H_
#include "usb_host_common.h"
#include "videodev2.h"


/* --------------------------------------------------------------------------
 * UVC constants
 */

#define UVC_TERM_INPUT          0x0000
#define UVC_TERM_OUTPUT         0x8000
#define UVC_TERM_DIRECTION(term)    ((term)->type & 0x8000)

#define UVC_ENTITY_TYPE(entity)     ((entity)->type & 0x7fff)
#define UVC_ENTITY_IS_UNIT(entity)  (((entity)->type & 0xff00) == 0)
#define UVC_ENTITY_IS_TERM(entity)  (((entity)->type & 0xff00) != 0)
#define UVC_ENTITY_IS_ITERM(entity) \
    (UVC_ENTITY_IS_TERM(entity) && \
    ((entity)->type & 0x8000) == UVC_TERM_INPUT)
#define UVC_ENTITY_IS_OTERM(entity) \
    (UVC_ENTITY_IS_TERM(entity) && \
    ((entity)->type & 0x8000) == UVC_TERM_OUTPUT)

/* ------------------------------------------------------------------------
 * GUIDs
 */
#define UVC_GUID_UVC_CAMERA \
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}
#define UVC_GUID_UVC_OUTPUT \
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02}
#define UVC_GUID_UVC_MEDIA_TRANSPORT_INPUT \
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03}
#define UVC_GUID_UVC_PROCESSING \
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01}
#define UVC_GUID_UVC_SELECTOR \
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02}

#define UVC_GUID_FORMAT_MJPEG \
    { 'M',  'J',  'P',  'G', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
#define UVC_GUID_FORMAT_YUY2 \
    { 'Y',  'U',  'Y',  '2', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
#define UVC_GUID_FORMAT_YUY2_ISIGHT \
    { 'Y',  'U',  'Y',  '2', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0x00, 0x00, 0x38, 0x9b, 0x71}
#define UVC_GUID_FORMAT_NV12 \
    { 'N',  'V',  '1',  '2', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
#define UVC_GUID_FORMAT_YV12 \
    { 'Y',  'V',  '1',  '2', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
#define UVC_GUID_FORMAT_I420 \
    { 'I',  '4',  '2',  '0', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
#define UVC_GUID_FORMAT_UYVY \
    { 'U',  'Y',  'V',  'Y', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
#define UVC_GUID_FORMAT_Y800 \
    { 'Y',  '8',  '0',  '0', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
#define UVC_GUID_FORMAT_Y16 \
    { 'Y',  '1',  '6',  ' ', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
#define UVC_GUID_FORMAT_BY8 \
    { 'B',  'Y',  '8',  ' ', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
#define UVC_GUID_FORMAT_RGBP \
    { 'R',  'G',  'B',  'P', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}
#define UVC_GUID_FORMAT_M420 \
    { 'M',  '4',  '2',  '0', 0x00, 0x00, 0x10, 0x00, \
     0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}

/* ------------------------------------------------------------------------
 * Driver specific constants.
 */

#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define DRIVER_VERSION_NUMBER   KERNEL_VERSION(1, 1, 0)
#define DRIVER_VERSION      "v1.1.0"

/* Number of isochronous URBs. */
#define UVC_URBS                        3//for otg
/* Maximum number of packets per URB. */
#define UVC_MAX_PACKETS                 1024//for otg
/* Maximum number of video buffers. */
#define UVC_MAX_VIDEO_BUFFERS           32
/* Maximum status buffer size in bytes of interrupt URB. */
#define UVC_MAX_STATUS_SIZE             16

#define UVC_CTRL_CONTROL_TIMEOUT        300
#define UVC_CTRL_STREAMING_TIMEOUT      5000

/* Maximum allowed number of control mappings per device */
#define UVC_MAX_CONTROL_MAPPINGS        1024

/* Devices quirks */
#define UVC_QUIRK_STATUS_INTERVAL       0x00000001
#define UVC_QUIRK_PROBE_MINMAX          0x00000002
#define UVC_QUIRK_PROBE_EXTRAFIELDS     0x00000004
#define UVC_QUIRK_BUILTIN_ISIGHT        0x00000008
#define UVC_QUIRK_STREAM_NO_FID         0x00000010
#define UVC_QUIRK_IGNORE_SELECTOR_UNIT  0x00000020
#define UVC_QUIRK_FIX_BANDWIDTH         0x00000080
#define UVC_QUIRK_PROBE_DEF             0x00000100
#define UVC_QUIRK_RESTRICT_FRAME_RATE   0x00000200

/* Format flags */
#define UVC_FMT_FLAG_COMPRESSED         0x00000001
#define UVC_FMT_FLAG_STREAM             0x00000002

/* UVC device state */
typedef enum _UVCDev_state{
    UVC_DEV_OFFLINE= 0,         /* UVCDev已经拔出       */
    UVC_DEV_ONLINE,             /* UVCDev已经添加       */
    UVC_DEV_DIED,               /* UVCDev不可用        */
    UVC_DEV_RESET               /* UVCDev正在被reset   */
}UVCDev_State_t;

/* ------------------------------------------------------------------------
 * Structures.
 */
/* The term 'entity' refers to both UVC units and UVC terminals.
 *
 * The type field is either the terminal type (wTerminalType in the terminal
 * descriptor), or the unit type (bDescriptorSubtype in the unit descriptor).
 * As the bDescriptorSubtype field is one byte long, the type value will
 * always have a null MSB for units. All terminal types defined by the UVC
 * specification have a non-null MSB, so it is safe to use the MSB to
 * differentiate between units and terminals as long as the descriptor parsing
 * code makes sure terminal types have a non-null MSB.
 *
 * For terminals, the type's most significant bit stores the terminal
 * direction (either UVC_TERM_INPUT or UVC_TERM_OUTPUT). The type field should
 * always be accessed with the UVC_ENTITY_* macros and never directly.
 */

struct uvc_entity {
//  struct list_head list;      /* Entity as part of a UVC device. */
//  struct list_head chain;     /* Entity as part of a video device
//                   * chain. */
    __u8 id;
    __u16 type;
    char name[64];

//  /* Media controller-related fields. */
//  struct video_device *vdev;
//  struct v4l2_subdev subdev;
//  unsigned int num_pads;
//  unsigned int num_links;
//  struct media_pad *pads;

    union {
        struct {
            __u16 wObjectiveFocalLengthMin;
            __u16 wObjectiveFocalLengthMax;
            __u16 wOcularFocalLength;
            __u8  bControlSize;
            __u8  *bmControls;
        } camera;

        struct {
            __u8  bControlSize;
            __u8  *bmControls;
            __u8  bTransportModeSize;
            __u8  *bmTransportModes;
        } media;

        //struct {
        //} output;

        struct {
            __u16 wMaxMultiplier;
            __u8  bControlSize;
            __u8  *bmControls;
            __u8  bmVideoStandards;
        } processing;

        //struct {
        //} selector;

        struct {
            __u8  guidExtensionCode[16];
            __u8  bNumControls;
            __u8  bControlSize;
            __u8  *bmControls;
            __u8  *bmControlsType;
        } extension;
    }un;

    __u8 bNrInPins;
//  __u8 *baSourceID;

//  unsigned int ncontrols;
//  struct uvc_control *controls;
};

struct uvc_frame {
    __u8  bFrameIndex;
    __u8  bmCapabilities;
    __u16 wWidth;
    __u16 wHeight;
    __u32 dwMinBitRate;
    __u32 dwMaxBitRate;
    __u32 dwMaxVideoFrameBufferSize;
    __u8  bFrameIntervalType;
    __u32 dwDefaultFrameInterval;
    __u32 *dwFrameInterval;
};

struct uvc_format {
    __u8 type;
    __u8 index;
    __u8 bpp;
    __u8 colorspace;
    __u32 fcc;
    __u32 flags;

    char name[32];

    unsigned int nframes;
    struct uvc_frame *frame;
};

struct uvc_format_desc {
    char *name;
    __u8 guid[16];
    __u32 fcc;
};

struct uvc_streaming_header {
    __u8 bNumFormats;
    __u8 bEndpointAddress;
    __u8 bTerminalLink;
    __u8 bControlSize;
//  __u8 *bmaControls;
    /* The following fields are used by input headers only. */
    __u8 bmInfo;
    __u8 bStillCaptureMethod;
    __u8 bTriggerSupport;
    __u8 bTriggerUsage;
};

enum uvc_buffer_state {
    UVC_BUF_STATE_IDLE  = 0,
    UVC_BUF_STATE_QUEUED    = 1,
    UVC_BUF_STATE_ACTIVE    = 2,
    UVC_BUF_STATE_READY = 3,
    UVC_BUF_STATE_DONE  = 4,
    UVC_BUF_STATE_ERROR = 5,
};

struct v4l2_buffer {
    __u32           mem_buf;
    __u32           length;
    //__u32           offset;

    __u32           bytesused;
};

struct uvc_buffer {
    /* Touched by interrupt handler. */
    struct v4l2_buffer buf;
    enum uvc_buffer_state state;
    unsigned int error;
};
typedef __s32   (* uvc_irq_t)(__u32* addr0, __u32* addr1, __u32* addr2 );

typedef struct _UVCDev {
    struct usb_host_virt_dev *pusb_dev;     /* UVCDev 对应的Public USB Device  */
    struct usb_interface     *pusb_intf;    /* Public usb interface             */

    /* device information */
    __u8 InterfaceNo;                       /* 接口号                          */
    __u8 SubClass;                          /* 子类                           */
    __u8 Protocol;                          /* 传输协议                         */
    __u32 DevType;                          /* 设备类型                         */
    __u32 DevNo;                            /* 设备在 UVC 管理中的编号           */

    /* device manager */
    UVCDev_State_t State;                   /* Dev当前所处的连接状态             */

    /* transport */
    __u32 CtrlIn;                           /* ctrl in  pipe                    */
    __u32 CtrlOut;                          /* ctrl out pipe                    */
    __u32 IntIn;                            /* interrupt in pipe                */
    __u32 BlukIn;                           /* bulk in pipe                 */
    __u32 IsoIn;                            /* iso in pipe              */
    __u8  EpInterval;                       /* int 传输主机查询设备的周期      */
    __u32 OnceTransferLength;               /* 中断ep的最大传输包大小             */

    __u32 busy;                             /* 主机是否正在处理命令           */


    __u32                   quirks;
    __u16                   uvc_version;
    __u32                   clock_frequency;
    struct uvc_entity       entities[UVC_VC_MAX+1];
    struct uvc_streaming*   streams;                //注意要释放


    void *Extern;                           /* 对应具体的UVC设备 */

    __u32 frame_len;                //add by Kingvan
    __u32 frame_buf0;                   //add by Kingvan
    __u32 frame_buf1;                   //add by Kingvan
    __u32 frame_buf2;                   //add by Kingvan
    //void (*exchange_buf) (struct _UVCDev *UVCDev,
    //      __u32* addr0, __u32* addr1, __u32* addr2 );//add by Kingvan
    uvc_irq_t exchange_buf;//add by Kingvan
    __s32 (*active_buf) (struct uvc_streaming *stream);//add by Kingvan

    __u32 urb_mem[UVC_URBS];
}UVCDev_t;

struct uvc_streaming {
//  struct list_head list;
    UVCDev_t *dev;
//  struct video_device *vdev;
//  struct uvc_video_chain *chain;
//  atomic_t active;

    struct usb_interface *intf;
    int intfnum;
    __u16 maxpsize;

    struct uvc_streaming_header header;
    enum v4l2_buf_type type;

    unsigned int nformats;
    struct uvc_format *format;      //注意释放

    struct uvc_streaming_control ctrl;
    struct uvc_format *cur_format;
    struct uvc_frame *cur_frame;
//  /* Protect access to ctrl, cur_format, cur_frame and hardware video
//   * probe control.
//   */
//  struct mutex mutex;

//  unsigned int frozen : 1;
//  struct uvc_video_queue queue;
    void (*decode) (struct urb *urb, struct uvc_streaming *video,
            struct uvc_buffer *buf);

    /* Context data used by the bulk completion handler. */
    struct {
        __u8 header[256];
        unsigned int header_size;
        int skip_payload;
        __u32 payload_size;
        __u32 max_payload_size;
    } bulk;

    struct urb *urb[UVC_URBS];
    char *urb_buffer[UVC_URBS];
//  dma_addr_t urb_dma[UVC_URBS];
    unsigned int urb_size;

    __u32 sequence;
    __u8 last_fid;

    struct uvc_buffer buf;

};

enum uvc_handle_state {
    UVC_HANDLE_PASSIVE  = 0,
    UVC_HANDLE_ACTIVE   = 1,
};

struct uvc_fh {
    //struct uvc_video_chain *chain;
    struct uvc_streaming *stream;
    enum uvc_handle_state state;
};

/* Utility functions */
extern void uvc_simplify_fraction(__u32 *numerator, __u32 *denominator,
        __u32 n_terms, __u32 threshold);
extern __u32 uvc_fraction_to_interval(__u32 numerator,
        __u32 denominator);
extern struct usb_host_virt_endpoint *uvc_find_endpoint(
        struct usb_host_virt_interface *alts, __u8 epaddr);

/* Video */
extern int uvc_video_init(struct uvc_streaming *stream);
extern __s32 uvc_video_suspend(struct uvc_streaming *stream);
extern __s32 uvc_video_resume(struct uvc_streaming *stream);
extern int uvc_video_enable(struct uvc_streaming *stream, __s32 enable);
extern int uvc_probe_video(struct uvc_streaming *stream,
        struct uvc_streaming_control *probe);
extern int uvc_commit_video(struct uvc_streaming *stream,
        struct uvc_streaming_control *ctrl);
extern int uvc_query_ctrl(UVCDev_t *dev, __u8 query, __u8 unit,
        __u8 intfnum, __u8 cs, void *data, __u16 size);



extern void* usbWebcam_init(void);
extern __s32 usbWebcam_exit(void* arg);

extern __s32 usbWebcam_remove(UVCDev_t * UVCDev);
extern __s32 usbWebcam_probe(UVCDev_t *UVCDev);

#endif



