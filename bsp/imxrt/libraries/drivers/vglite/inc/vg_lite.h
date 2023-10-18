/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright 2012 - 2020 Vivante Corporation, Santa Clara, California.
*    All Rights Reserved.
*
*    Permission is hereby granted, free of charge, to any person obtaining
*    a copy of this software and associated documentation files (the
*    'Software'), to deal in the Software without restriction, including
*    without limitation the rights to use, copy, modify, merge, publish,
*    distribute, sub license, and/or sell copies of the Software, and to
*    permit persons to whom the Software is furnished to do so, subject
*    to the following conditions:
*
*    The above copyright notice and this permission notice (including the
*    next paragraph) shall be included in all copies or substantial
*    portions of the Software.
*
*    THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
*    IN NO EVENT SHALL VIVANTE AND/OR ITS SUPPLIERS BE LIABLE FOR ANY
*    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
*    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
*    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#ifndef _vg_lite_h_
#define _vg_lite_h_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
#define inline __inline
#endif

#include <stddef.h>
#include <stdint.h>

#define VGLITE_RELEASE_VERSION   0x03000f

#define VGLITE_HEADER_VERSION    6

#ifndef VGLITE_VERSION_2_0
#define VGLITE_VERSION_2_0    1

#define VGLITE_MAKE_VERSION(major, minor, patch) (((major) << 16) | ((minor) << 8) | (patch))

#define VGLITE_VERSION_MAJOR(version) (((uint32_t)(version) >> 16) & 0xff)
#define VGLITE_VERSION_MINOR(version) (((uint32_t)(version) >> 8) & 0xff)
#define VGLITE_VERSION_PATCH(version) ((uint32_t)(version) & 0xff)

#define VGLITE_API_VERSION_2_0    VGLITE_MAKE_VERSION(2, 0, 0)


#/* Macros *********************************************************************************************************************/

/* Path command (op code). */
#define VLC_OP_END          0x00
#define VLC_OP_CLOSE        0x01
#define VLC_OP_MOVE         0x02
#define VLC_OP_MOVE_REL     0x03
#define VLC_OP_LINE         0x04
#define VLC_OP_LINE_REL     0x05
#define VLC_OP_QUAD         0x06
#define VLC_OP_QUAD_REL     0x07
#define VLC_OP_CUBIC        0x08
#define VLC_OP_CUBIC_REL    0x09
#define VLC_OP_SCCWARC      0x0A
#define VLC_OP_SCCWARC_REL  0x0B
#define VLC_OP_SCWARC       0x0C
#define VLC_OP_SCWARC_REL   0x0D
#define VLC_OP_LCCWARC      0x0E
#define VLC_OP_LCCWARC_REL  0x0F
#define VLC_OP_LCWARC       0x10
#define VLC_OP_LCWARC_REL   0x11

/* Macros for path manipulating: See path definitions. "VLM" means "VGLite Macros" */
#define VLM_PATH_ENABLE_UPLOAD(path)    (path).uploaded.property |= 1
#define VLM_PATH_DISABLE_UPLOAD(path)   (path).uploaded.property &= (~1)
#define VLM_PATH_GET_UPLOAD_BIT(path)   ((path).uploaded.property & 1)

/* Types ***********************************************************************************************************************/

#ifndef VG_LITE_ERROR
#define VG_LITE_ERROR  1
    /*!
     @abstract Error codes that the vg_lite functions can return.

     @discussion
     All API functions return a status code. On success, <code>VG_LITE_SUCCESS</code> will be returned when a function is
     successful. This value is set to zero, so if any function returns a non-zero value, an error has occured.
     */
    typedef enum vg_lite_error
    {
        VG_LITE_SUCCESS = 0,        /*! Success. */
        VG_LITE_INVALID_ARGUMENT,   /*! An invalid argument was specified. */
        VG_LITE_OUT_OF_MEMORY,      /*! Out of memory. */
        VG_LITE_NO_CONTEXT,         /*! No context or an unintialized context specified. */
        VG_LITE_TIMEOUT,            /*! A timeout has occured during a wait. */
        VG_LITE_OUT_OF_RESOURCES,   /*! Out of system resources. */
        VG_LITE_GENERIC_IO,         /*! Cannot communicate with the kernel driver. */
        VG_LITE_NOT_SUPPORT,        /*! Function call not supported. */
        VG_LITE_MULTI_THREAD_FAIL,  /*! Multi-thread/tasks fail. */
        VG_LITE_ALREADY_EXISTS,     /*! Object already exists */
        VG_LITE_NOT_ALIGNED,        /*! Data alignment error */
    }
    vg_lite_error_t;
#endif

    /*!
     @abstract The floating point type used by the VGLite API.
     */
    typedef float vg_lite_float_t;

    /*!
     @abstract A 32-bit color value used by the VGLite API.

     @discussion
     The color value specifies the color used in various functions. The color is formed using 8-bit RGBA channels. The red channel
     is in the lower 8-bit of the color value, followed by the green and blue channels. The alpha channel is in the upper 8-bit of
     the color value.

     For L8 target formats, the RGB color is converted to L8 by using the default ITU-R BT.709 conversion rules.
     */
    typedef uint32_t vg_lite_color_t;

/* Enumerations ***********************************************************************************************************************/

    /*!
     @abstract Quality enumeration for a given path.

     @discussion
     Each path should specify a quality hint for the hardware. The path generation tool will generate the quality hint based on the
     complexity of the path.
     */
    typedef enum vg_lite_quality {
        VG_LITE_HIGH,   /*! High quality 16x anti-aliasing path. */
        VG_LITE_UPPER,  /*! Upper quality 8x anti-aliasing path. */
        VG_LITE_MEDIUM, /*! Medium quality 4x anti-aliasing path. */
        VG_LITE_LOW,    /*! Low quality pat without any anti-aliasing. */
    } vg_lite_quality_t;

    /*!
     @abstract Format of path coordinates.

     @discussion
     Each path can have a separate coordinate system. The path generation tool will find the most optimal coordinate system for any
     given path based on its dimensions and input coordinates.
     */
    typedef enum vg_lite_format {
        VG_LITE_S8,     /*! Signed 8-bit coordinates. */
        VG_LITE_S16,    /*! Signed 16-bit coordinates. */
        VG_LITE_S32,    /*! Signed 32-bit coordinates. */
        VG_LITE_FP32,   /*! 32-bit floating point coordinates. */
    } vg_lite_format_t;

    /*!
     @abstract Format of a buffer.

     @discussion
     The pixel type for a <code>vg_lite_buffer_t</code> structure.
     */
    typedef enum vg_lite_buffer_format {
        VG_LITE_RGBA8888,   /*! 32-bit RGBA format with 8 bits per color channel. Red is in bits 7:0, green in bits 15:8, blue in
                             bits 23:16, and the alpha channel is in bits 31:24. */
        VG_LITE_BGRA8888,   /*! 32-bit RGBA format with 8 bits per color channel. Red is in bits 23:16, green in bits 15:8, blue in
                             bits 7:0, and the alpha channel is in bits 31:24. */
        VG_LITE_RGBX8888,   /*! 32-bit RGBX format with 8 bits per color channel. Red is in bits 7:0, green in bits 15:8, blue in
                             bits 23:16, and the x channel is in bits 31:24. */
        VG_LITE_BGRX8888,   /*! 32-bit RGBX format with 8 bits per color channel. Red is in bits 23:16, green in bits 15:8, blue in
                             bits 7:0, and the x channel is in bits 31:24. */
        VG_LITE_RGB565,     /*! 16-bit RGB format with 5 and 6 bits per color channel. Red is in bits 4:0, green in bits 10:5, and
                             the blue color channel is in bits 15:11. */
        VG_LITE_BGR565,     /*! 16-bit RGB format with 5 and 6 bits per color channel. Red is in bits 15:11, green in bits 10:5,
                             and the blue color channel is in bits 4:0. */
        VG_LITE_RGBA4444,   /*! 16-bit RGBA format with 4 bits per color channel. Red is in bits 3:0, green in bits 7:4, blue in
                             bits 11:8 and the alpha channel is in bits 15:12. */
        VG_LITE_BGRA4444,   /*! 16-bit RGBA format with 4 bits per color channel. Red is in bits 11:8, green in bits 7:4, blue in
                             bits 3:0 and the alpha channel is in bits 15:12. */
        VG_LITE_BGRA5551,   /*! 16-bit RGBA format with 4 bits per color channel. Red is in bits 14:10, green in bits 9:5, blue in
                             bits 4:0 and the alpha channel is in bit 15:15. */
        VG_LITE_A4,         /*! 4-bit alpha format. There are no RGB values. */
        VG_LITE_A8,         /*! 8-bit alpha format. There are no RGB values. */
        VG_LITE_L8,         /*! 8-bit luminance value. There is no alpha value. */
        VG_LITE_YUYV,       /*! Packed YUV format, 32-bit for 2 pixels. Y0 is in bits 7:0 and V is in bits 31:23. */

        VG_LITE_YUY2,       /*! New formats. */
        VG_LITE_NV12,
        VG_LITE_ANV12,
        VG_LITE_AYUY2,

        VG_LITE_YV12,
        VG_LITE_YV24,
        VG_LITE_YV16,
        VG_LITE_NV16,

        VG_LITE_YUY2_TILED,  /*! Tiled YUV formats. */
        VG_LITE_NV12_TILED,
        VG_LITE_ANV12_TILED,
        VG_LITE_AYUY2_TILED,

        VG_LITE_INDEX_1 = 100,    /*! Indexed format. */
        VG_LITE_INDEX_2,
        VG_LITE_INDEX_4,
        VG_LITE_INDEX_8,

        VG_LITE_RGBA2222,      /*! 8-bit RGBA format with 2 bits per color channel.Red is in bits 1:0,green in bits 3:2,blue in
                               bits 5:4 and the alpha channel is in bits 7:6*/
        VG_LITE_BGRA2222,      /*! 8-bit RGBA format with 2 bits per color channel.Blue is in bits 1:0,green in bits 3:2,red in
                               bits 5:4 and the alpha channel is in bits 7:6*/
        VG_LITE_ABGR2222,      /*! 8-bit RGBA format with 2 bits per color channel.Alpha is in bits 1:0,blue in bits 3:2,green in
                               bits 5:4 and the red channel is in bits 7:6*/
        VG_LITE_ARGB2222,      /*! 8-bit RGBA format with 2 bits per color channel.Alpha is in bits 1:0,red in bits 3:2,green in
                               bits 5:4 and the blue channel is in bits 7:6*/
        VG_LITE_ABGR4444,      /*! 16-bit RGBA format with 4 bits per color channel. Alpha is in bits 3:0, blue in bits 7:4, green in
                               bits 11:8 and the red channel is in bits 15:12. */
        VG_LITE_ARGB4444,      /*! 16-bit RGBA format with 4 bits per color channel. Alpha is in bits 3:0, red in bits 7:4, green in
                               bits 11:8 and the blue channel is in bits 15:12. */
        VG_LITE_ABGR8888,      /*! 32-bit RGBA format with 8 bits per color channel. Alpha is in bits 7:0, blue in bits 15:8, green in
                               bits 23:16, and the red channel is in bits 31:24. */
        VG_LITE_ARGB8888,      /*! 32-bit RGBA format with 8 bits per color channel. Alpha is in bits 7:0, red in bits 15:8, green in
                               bits 23:16, and the blue channel is in bits 31:24. */
        VG_LITE_ABGR1555,      /*! 16-bit RGBA format with 4 bits per color channel. Red is in bits 15:11, green in bits 10:6, blue in
                               bits 5:1 and the alpha channel is in bit 0:0. */
        VG_LITE_RGBA5551,      /*! 16-bit RGBA format with 4 bits per color channel. Blue is in bits 14:10, green in bits 9:5, red in
                               bits 4:0 and the alpha channel is in bit 15:15. */
        VG_LITE_ARGB1555,      /*! 16-bit RGBA format with 4 bits per color channel. Blue is in bits 15:11, green in bits 10:6, red in
                               bits 5:1 and the alpha channel is in bit 0:0. */
        VG_LITE_XBGR8888,      /*! 32-bit RGBX format with 8 bits per color channel. X channel is in bits 7:0, blue in bits 15:8, green in
                               bits 23:16, and the red is in bits 31:24. */
        VG_LITE_XRGB8888       /*! 32-bit RGBX format with 8 bits per color channel. X channel is in bits 7:0, red in bits 15:8, green in
                               bits 23:16, and the blue is in bits 31:24. */
    } vg_lite_buffer_format_t;

    /*!
     @abstract Swizzle of packed YUV format UV channels.

     @discussion
     The swizzle of packed YUV format UV channels.
     */
    typedef enum vg_lite_swizzle {
        VG_LITE_SWIZZLE_UV,
        VG_LITE_SWIZZLE_VU,
    } vg_lite_swizzle_t;

    /*!
     @abstract The YUV<->RGB conversion rule.

     @discussion
     Indicate the rule how to convert rgb and yuv colors.
     */
    typedef enum vg_lite_yuv2rgb {
        VG_LITE_YUV601,
        VG_LITE_YUV709,
    } vg_lite_yuv2rgb_t;

    /*!
     @abstract The pixel layout in a buffer.

     @discussion
     Pixels in a buffer may be tiled  or linear.
     */
    typedef enum vg_lite_buffer_layout {
        VG_LITE_LINEAR,
        VG_LITE_TILED,
    } vg_lite_buffer_layout_t;

    /*!
     @abstract The image (buffer) rendering mode.

     @discussion
     This defines how an image are rendered onto a buffer. There are 3 modes.
     */
    typedef enum vg_lite_buffer_image_mode {
        VG_LITE_NORMAL_IMAGE_MODE,
        VG_LITE_NONE_IMAGE_MODE,
        VG_LITE_MULTIPLY_IMAGE_MODE
    } vg_lite_buffer_image_mode_t;

    /*!
     @abstract The image (buffer) transparency mode.
     OPAQUE, All image pixels are copied to the VGPE for rasterization;
     TRANSPARENT,Only the non-transparent image pixels are copied to the VGPE.
     Note: This mode is valid when IMAGE_MODE(vg_lite_buffer_image_mode_t) isn't NONE.
     */
    typedef enum vg_lite_buffer_transparency_mode {
        VG_LITE_IMAGE_OPAQUE,
        VG_LITE_IMAGE_TRANSPARENT
    } vg_lite_buffer_transparency_mode_t;

    typedef struct vg_lite_yuvinfo {
        vg_lite_swizzle_t   swizzle;        /* UV swizzle. */
        vg_lite_yuv2rgb_t   yuv2rgb;        /* 601 or 709 conversion standard. */
        uint32_t            uv_planar;      /* UV(U) planar address. */
        uint32_t            v_planar;       /* V planar address. */
        uint32_t            alpha_planar;   /* Alpha planar address. */
        uint32_t            uv_stride;      /* UV(U) stride. */
        uint32_t            v_stride;       /* V stride. */
        uint32_t            alpha_stride;   /* Alpha stride. */
        uint32_t            uv_height;      /* UV(U) height. */
        uint32_t            v_height;       /* V height. */
        void *              uv_memory;      /* The logical pointer to the UV(U) planar memory. */
        void *              v_memory;       /* The logical pointer to the V planar memory. */
        void *              uv_handle;      /* The memory handle of the UV(U) planar. */
        void *              v_handle;       /* The memory handle of the V planar. */
    } vg_lite_yuvinfo_t;

    /*!
     @abstract Blending modes.

     @discussion
     Some of the VGLite API functions calls support blending. S and D represent source and destination color channels and Sa and Da
     represent the source and destination alpha channels.
     */
    typedef enum vg_lite_blend {
        VG_LITE_BLEND_NONE,     /*! S, i.e. no blending. */
        VG_LITE_BLEND_SRC_OVER, /*! S + (1 - Sa) * D */
        VG_LITE_BLEND_DST_OVER, /*! (1 - Da) * S + D */
        VG_LITE_BLEND_SRC_IN,   /*! Da * S */
        VG_LITE_BLEND_DST_IN,   /*! Sa * D */
        VG_LITE_BLEND_SCREEN,   /*! S + D - S * D */
        VG_LITE_BLEND_MULTIPLY, /*! S * (1 - Da) + D * (1 - Sa) + S * D */
        VG_LITE_BLEND_ADDITIVE, /*! S + D */
        VG_LITE_BLEND_SUBTRACT, /*! D * (1 - S) */
    } vg_lite_blend_t;

    /*!
     @abstract Fill rules.

     @discussion
     For drawing any path, the hardware supports both non-zero and odd-even fill rules.

     To determine whether any point is contained inside an object, imagine drawing a line from that point out to infinity in any
     direction such that the line does not cross any vertex of the path. For each edge that is crossed by the line, add 1 to the
     counter if the edge crosses from left to right, as seen by an observer walking across the line towards infinity, and subtract 1
     if the edge crosses from right to left. In this way, each region of the plane will receive an integer value.

     The non-zero fill rule says that a point is inside the shape if the resulting sum is not equal to zero. The even/odd rule says
     that a point is inside the shape if the resulting sum is odd, regardless of sign.
     */
    typedef enum vg_lite_fill {
        VG_LITE_FILL_NON_ZERO,  /*! Non-zero fill rule. A pixel is drawn if it crosses at least one path pixel. */
        VG_LITE_FILL_EVEN_ODD,  /*! Even-odd fill rule. A pixel is drawn it it crosses an odd number of path pixels. */
    } vg_lite_fill_t;

    /* Chip features. */
    typedef enum vg_lite_feature
    {
        gcFEATURE_BIT_VG_IM_INDEX_FORMAT,
        gcFEATURE_BIT_VG_PE_PREMULTIPLY,
        gcFEATURE_BIT_VG_BORDER_CULLING,
        gcFEATURE_BIT_VG_RGBA2_FORMAT,
        gcFEATURE_BIT_VG_QUALITY_8X,
        gcFEATURE_BIT_VG_RADIAL_GRADIENT,
        gcFEATURE_BIT_VG_LINEAR_GRADIENT_EXT,
        gcFEATURE_BIT_VG_COLOR_KEY,
        gcFEATURE_BIT_VG_DITHER,
        /* Insert features above this comment only. */
        gcFEATURE_COUNT         /* Not a feature. */
    }
    vg_lite_feature_t;

    /* Filter modes. */
    typedef enum vg_lite_filter
    {
        VG_LITE_FILTER_POINT     = 0,       /* Only the nearest image pixel is fetched. */
        VG_LITE_FILTER_LINEAR    = 0x10000, /* Used for linear paint. */
        VG_LITE_FILTER_BI_LINEAR = 0x20000, /* Use a 2x2 box around the image pixel and perform an interpolation. */
    } vg_lite_filter_t;

    /* Pattern padding mode. */
    typedef enum vg_lite_pattern_mode
    {
        VG_LITE_PATTERN_COLOR = 0,
        VG_LITE_PATTERN_PAD,
    } vg_lite_pattern_mode_t;

    /* radial gradient padding mode. */
    typedef enum {
      VG_LITE_RADIAL_GRADIENT_SPREAD_FILL = 0,
      VG_LITE_RADIAL_GRADIENT_SPREAD_PAD,
      VG_LITE_RADIAL_GRADIENT_SPREAD_REPEAT,
      VG_LITE_RADIAL_GRADIENT_SPREAD_REFLECT,
    } vg_lite_radial_gradient_spreadmode_t;

    /* draw path type. */
    typedef enum vg_lite_draw_path_type{
      VG_LITE_DRAW_FILL_PATH = 0, /*! draw fill path. */
      VG_LITE_DRAW_STROKE_PATH,   /*! draw stroke path. */
      VG_LITE_DRAW_FILL_STROKE_PATH, /*! draw both fill and stroke path. */
    } vg_lite_draw_path_type_t;

    /* End cap style. */
    typedef enum vg_lite_cap_style
    {
        VG_LITE_CAP_BUTT,  /*! The Butt end cap style terminates each segment with a line perpendicular to the tangent at each endpoint. */
        VG_LITE_CAP_ROUND, /*! The Round end cap style appends a semicircle with a diameter equal to the line width centered around each endpoint. */
        VG_LITE_CAP_SQUARE /*! The Square end cap style appends a rectangle with two sides of length equal to the line width
                               perpendicular to the tangent, and two sides of length equal to half the line width parallel
                               to the tangent, at each endpoint. */
    }
    vg_lite_cap_style_t;

    /* Line join styles. */
    typedef enum vg_lite_join_style
    {
        VG_LITE_JOIN_MITER,/*! The Miter join style appends a trapezoid with one vertex at the intersection point of the two original
                           lines, two adjacent vertices at the outer endpoints of the two “fattened” lines and a fourth vertex at
                           the extrapolated intersection point of the outer perimeters of the two “fattened” lines. */
        VG_LITE_JOIN_ROUND,/*! The Round join style appends a wedge-shaped portion of a circle,centered at the intersection point
                           of the two original lines, having a radius equal to half the line width. */
        VG_LITE_JOIN_BEVEL /*! The Bevel join style appends a triangle with two vertices at the outer endpoints of the two "fattened"
                           lines and a third vertex at the intersection point of the two original lines. */
    }
    vg_lite_join_style_t;

/* Structures *******************************************************************************************************************/

    typedef struct vg_lite_path_point *        vg_lite_path_point_ptr;
    typedef struct vg_lite_path_point
    {
        /* X coordinate. */
        vg_lite_float_t                      x;

        /* Y coordinate. */
        vg_lite_float_t                      y;

        /* Flatten flag for flattened path. */
        uint8_t                              flatten_flag;

        /* Curve type for stroke path. */
        uint8_t                              curve_type;

        /* X tangent. */
        vg_lite_float_t                      tangentX;

        /* Y tangent. */
        vg_lite_float_t                      tangentY;

        /* Length of the line. */
        vg_lite_float_t                      length;

        /* Pointer to next point node. */
        vg_lite_path_point_ptr               next;

        /* Pointer to previous point node. */
        vg_lite_path_point_ptr               prev;

    }vg_lite_path_point_t;

    typedef struct vg_lite_sub_path *    vg_lite_sub_path_ptr;
    typedef struct vg_lite_sub_path
    {
        /* Pointer to next sub path. */
        vg_lite_sub_path_ptr             next;

        /* Number of points. */
        uint32_t                         point_count;

        /* Point list. */
        vg_lite_path_point_ptr           point_list;

        /* Last point. */
        vg_lite_path_point_ptr           last_point;

        /* Whether is path is closed. */
        uint8_t                          closed;

        /* Sub path length. */
        vg_lite_float_t                  length;
    }
    vg_lite_sub_path_t;

    typedef struct vg_lite_stroke_conversion
    {
        /* Stroke parameters */
        vg_lite_cap_style_t                stroke_cap_style;
        vg_lite_join_style_t               stroke_join_style;
        vg_lite_float_t                    stroke_line_width;
        vg_lite_float_t                    stroke_miter_limit;
        vg_lite_float_t *                  stroke_dash_pattern;
        uint32_t                           stroke_dash_pattern_count;
        vg_lite_float_t                    stroke_dash_phase;
        vg_lite_float_t                    stroke_dash_initial_length;
        uint32_t                           stroke_dash_initial_index;

        vg_lite_float_t                    half_line_width;

        /* Total length of stroke dash patterns. */
        vg_lite_float_t                    stroke_dash_pattern_length;

        /* For fast checking. */
        vg_lite_float_t                    stroke_miter_limit_square;

        /* Temp storage of stroke subPath. */
        vg_lite_path_point_ptr             path_point_list;
        vg_lite_path_point_ptr             path_last_point;
        uint32_t                           point_count;
        vg_lite_path_point_ptr             left_stroke_point;
        vg_lite_path_point_ptr             last_right_stroke_point;
        vg_lite_path_point_ptr             stroke_point_list;
        vg_lite_path_point_ptr             stroke_last_point;
        uint32_t                           stroke_point_count;

        /* Sub path list. */
        vg_lite_sub_path_ptr               stroke_sub_path_list;

        /* Last sub path. */
        vg_lite_sub_path_ptr               last_stroke_sub_path;

        /* Swing area handling. */
        uint8_t                            swing_need_to_handle;
        uint32_t                           swing_handling;
        uint8_t                            swing_counter_clockwise;
        vg_lite_float_t                    swing_stroke_deltax;
        vg_lite_float_t                    swing_stroke_deltay;
        vg_lite_path_point_ptr             swing_start_point;
        vg_lite_path_point_ptr             swing_start_stroke_point;
        vg_lite_float_t                    swing_accu_length;
        vg_lite_float_t                    swing_center_length;
        uint32_t                           swing_count;

        vg_lite_float_t                    stroke_path_length;
        uint32_t                           stroke_path_size;
        /* The stroke line is fat line. */
        uint8_t                            is_fat;
        uint8_t                            closed;
    }
    vg_lite_stroke_conversion_t;

    /* A 2D Point definition. */
    typedef struct vg_lite_point {
        int x;
        int y;
    }
    vg_lite_point_t;

    /* Four 2D Point that form a polygon */
    typedef vg_lite_point_t vg_lite_point4_t[4];

    /* This structure is used to query VGLite driver information */
    typedef struct vg_lite_info {
        uint32_t  api_version;          /*! VGLite API version. */
        uint32_t  header_version;       /*! VGLite API header version. */
        uint32_t  release_version;      /*! VGLite release version. */
        uint32_t  reserved;             /*! Reserved for future use. */
    } vg_lite_info_t;

    /*!
     @abstract A 3x3 matrix.

     @discussion
     For those functions that need a matrix, this is the structure that defines it. The contents are a simple 3x3 matrix
     consisting of floating pointer numbers.
     */
    typedef struct vg_lite_matrix {
        vg_lite_float_t m[3][3];    /*! The 3x3 matrix itself, in [row][column] order. */
    } vg_lite_matrix_t;

    /*!
     @abstract A wrapper structure for any image or render target.

     @discussion
     Each piece of memory, whether it is an image used as a source or a buffer used as a target, requires a structure to define it.
     This structure contains all the information the VGLite API requires to access the buffer's memory by the hardware.
     */
    typedef struct vg_lite_buffer {
        int32_t width;                  /*! Width of the buffer in pixels. */
        int32_t height;                 /*! Height of the buffer in pixels. */
        int32_t stride;                 /*! The number of bytes to move from one line in the buffer to the next line. */
        vg_lite_buffer_layout_t tiled;  /*! Indicating the buffer memory layout is linear or tiled. */
        vg_lite_buffer_format_t format; /*! The pixel format of the buffer. */
        void * handle;                  /*! The memory handle of the buffer's memory as allocated by the VGLite kernel. */
        void * memory;                  /*! The logical pointer to the buffer's memory for the CPU. */
        uint32_t address;               /*! The address to the buffer's memory for the hardware. */
        vg_lite_yuvinfo_t       yuv;    /*! The yuv format details. */
        vg_lite_buffer_image_mode_t image_mode;             /*! The blit image mode. */
        vg_lite_buffer_transparency_mode_t transparency_mode;  /*image transparency mode*/
    } vg_lite_buffer_t;

    /* This structure simply records the memory allocation info by kernel. */
    typedef struct vg_lite_hw_memory {
        void    * handle;               /*! gpu memory object handle. */
        void    * memory;               /*! logical memory address. */
        uint32_t  address;              /*! GPU memory address. */
        uint32_t  bytes;                /*! Size of memory. */
        uint32_t  property;             /*! Currently bit0 is used for path upload:
                                         1 to enable auto path data uploading;
                                         0 to disable path data uploading (always embedded into command buffer).
                                         */
    } vg_lite_hw_memory_t;

    /*!
     @abstract A path used by the drawing command.

     @discussion
     Each path needs a few parameters. This structure defines those parameters, so the VGLite driver knows the detail of a path.
     */
    typedef struct vg_lite_path {
        vg_lite_float_t bounding_box[4];    /*! Bounding box specified as left, top, right, and bottom. */
        vg_lite_quality_t quality;          /*! Quality hint for the path. */
        vg_lite_format_t format;            /*! Coordinate format. */
        vg_lite_hw_memory_t uploaded;       /*! Path data that has been upload into GPU addressable memory. */
        int32_t path_length;                /*! Number of bytes in the path data. */
        void *path;                         /*! Pointer to the physical description of the path. */
        int8_t path_changed;               /* Indicate whether path data is synced with command buffer (uploaded) or not. */
        int8_t pdata_internal;             /*! Indicate whether path data memory is allocated by driver. */
        vg_lite_stroke_conversion_t *stroke_conversion; /*! Refer to the definition by <code>vg_lite_stroke_conversion_t</code>.*/
        vg_lite_draw_path_type_t path_type;            /*! Refer to the definition by <code>vg_lite_draw_path_type_t</code>. */
        void *stroke_path_data;            /*! Pointer to the physical description of the stroke path. */
        int32_t stroke_path_size;          /*! Number of bytes in the stroke path data. */
        vg_lite_color_t stroke_color;      /*! The stroke path fill color.Refer to the definition by <code>vg_lite_color_t</code>.*/
    } vg_lite_path_t;

    /*!
     @abstract A rectangle.

     @discussion
     A rectangle defines a rectangular definition of the screen.
     */
    typedef struct vg_lite_rectangle {
        int32_t x;      /*! Left coordinate of the rectangle. */
        int32_t y;      /*! Top coordinate of the rectangle. */
        int32_t width;  /*! Width of the rectangle. */
        int32_t height; /*! Height of the rectangle. */
    } vg_lite_rectangle_t;

    /*!
     @abstract Tessellation buffer information.

     @discussion
     The tessellation buffer information for access.
     */
    typedef struct vg_lite_tsbuffer_info {
        uint32_t tessellation_buffer_gpu[3];        /*! HW physical address. */
        uint8_t *tessellation_buffer_logic[3];      /*! Logical address. */
        uint32_t tessellation_buffer_size[3];       /*! Buffer size for tessellation buffer, l1, l2. */
        uint32_t tessellation_stride;               /*! Buffer stride. */
        uint32_t tessellation_width_height;         /*! Combination of buffer width and height. */
        uint32_t tessellation_shift;                /*! Tessellation config: shift. */
        uint32_t tessellation_origin[2];
    } vg_lite_tsbuffer_info_t;

    /* Linear Gradient definitions. */
#define VLC_MAX_GRAD            16              /*! The max number of gradient stops. */
#define VLC_GRADBUFFER_WIDTH    256             /*! The internal buffer width.*/

    /*!
     @abstract Linear gradient definition.

     @discussion
     Linear gradient is applied to filling a path. It will generate a 256x1 image according the settings.
     */
    typedef struct vg_lite_linear_gradient {
        uint32_t colors[VLC_MAX_GRAD];      /*! Colors for stops. */
        uint32_t count;                     /*! Count of colors, up to 16. */
        uint32_t stops[VLC_MAX_GRAD];       /*! Color stops, value from 0 to 255. */
        vg_lite_matrix_t matrix;            /*! The matrix to transform the gradient. */
        vg_lite_buffer_t image;             /*! The image for rendering as gradient pattern. */
    } vg_lite_linear_gradient_t;

    /* radial Gradient definitions. */
#define MAX_COLOR_RAMP_STOPS            256              /*! The max number of radial gradient stops. */

    /*!
     @abstract color ramp definition.

     @discussion
     This is the stop for the radial gradient.The number of parameters is 5,and give the offset and
     color of the stop.Each stop is defined by a floating-point offset value and four floating-point values
     containing the sRGBA color and alpha value associated with each stop, in the form of a non-premultiplied
     (R, G, B, alpha) quad.And the range of all parameters in it is [0,1].[0,1] of the color channel value is
     mapped to [0,255].
     */
    typedef struct vg_lite_color_ramp
    {
        vg_lite_float_t stop;        /* Value for the color stop. */
        vg_lite_float_t red;         /* Red color channel value for the color stop. */
        vg_lite_float_t green;       /* Green color channel value for the color stop. */
        vg_lite_float_t blue;        /* Blue color channel value for the color stop. */
        vg_lite_float_t alpha;       /* Alpha color channel value for the color stop. */
    }
    vg_lite_color_ramp_t, *vg_lite_color_ramp_ptr;

    typedef struct vg_lite_radial_gradient_parameter
    {
        vg_lite_float_t cx;        /* the x coordinate of the center point. */
        vg_lite_float_t cy;        /* the y coordinate of the center point. */
        vg_lite_float_t r;         /* the radius. */
        vg_lite_float_t fx;        /* the x coordinate of the focal point. */
        vg_lite_float_t fy;        /* the y coordinate of the focal point. */
    }
    vg_lite_radial_gradient_parameter_t;

    /*!
     @abstract radial gradient definition.

     @discussion
     radial gradient is applied to filling a path.
     */
    typedef struct vg_lite_radial_gradient {
        uint32_t count;                     /*! Count of colors, up to 256. */
        vg_lite_matrix_t matrix;            /*! The matrix to transform the gradient. */
        vg_lite_buffer_t image;             /*! The image for rendering as gradient pattern. */
        vg_lite_radial_gradient_parameter_t radialGradient;      /* include center point,focal point and radius.*/
        vg_lite_radial_gradient_spreadmode_t SpreadMode;    /* The tiling mode that applied to the pixels out of the image after transformed. */

        uint32_t vgColorRampLength;         /* Color ramp parameters for gradient paints provided to the driver. */
        vg_lite_color_ramp_t vgColorRamp[MAX_COLOR_RAMP_STOPS];

        uint32_t intColorRampLength;        /* Converted internal color ramp. */
        vg_lite_color_ramp_t intColorRamp[MAX_COLOR_RAMP_STOPS + 2];

        uint8_t colorRampPremultiplied;     /* if this value is set to 1,the color value of vgColorRamp will multiply by alpha value of vgColorRamp.*/
    } vg_lite_radial_gradient_t;

    /*!
     @abstract linear gradient parameter definition.

     @discussion
     The line connecting point (X0,Y0) to point (X1,Y1) is the radial direction of the linear gradient.
     This radial direction line called line0,the line perpendicular to line0 and passing through the point (X0,Y0)
     called line1,the line perpendicular to line0 and passing through the point (X1,Y1) called line2,the linear gradient
     starts form line1 and end to line2.
     */
    typedef struct vg_lite_linear_gradient_parameter
    {
        vg_lite_float_t X0;
        vg_lite_float_t Y0;
        vg_lite_float_t X1;
        vg_lite_float_t Y1;
    }
    vg_lite_linear_gradient_parameter_t;

    /*!
     @abstract linear gradient definition.

     @discussion
     linear gradient is applied to filling a path.vg_lite_linear_gradient_ext and vg_lite_linear_gradient for hardware and software implementation
     of linear gradient respectively.
     */
    typedef struct vg_lite_linear_gradient_ext {
        uint32_t count;                     /*! Count of colors, up to 256. */
        vg_lite_matrix_t matrix;            /*! The matrix to transform the gradient. */
        vg_lite_buffer_t image;             /*! The image for rendering as gradient pattern. */
        vg_lite_linear_gradient_parameter_t linear_gradient;      /* Refer to the definition by <code>vg_lite_linear_gradient_parameter_t</code>.*/

        uint32_t vg_color_ramp_length;         /* Color ramp parameters for gradient paints provided to the driver. */
        vg_lite_color_ramp_t vg_color_ramp[MAX_COLOR_RAMP_STOPS];

        uint32_t int_color_ramp_length;        /* Converted internal color ramp. */
        vg_lite_color_ramp_t int_color_ramp[MAX_COLOR_RAMP_STOPS + 2];

        uint8_t color_ramp_premultiplied;     /* if this value is set to 1,the color value of vgColorRamp will multiply by alpha value of vgColorRamp.*/
        vg_lite_radial_gradient_spreadmode_t spread_mode;    /* Use tge same spread mode enumeration type as radial gradient. */
    } vg_lite_linear_gradient_ext_t;

    /*!
     @abstract color key definition.

     @discussion
     The colorkey have two sections,each section contain R,G,B chanels.Debited as hign_rgb and low_rgb respectively.
     Can be used for blit operation or draw_pattern operation.when enable is ture,the alpha value is used to replace
     the alpha channel of destination pixel when its RGB channels in range [low_rgb,hign_rgb].After use color key this
     frame,and if the color key is not need in the next frame,disable the color key before next frame.
     */
    typedef struct vg_lite_color_key
    {
        uint8_t enable;        /* when enable is ture,this color key is effective. */
        uint8_t low_r;         /* The R chanel of low_rgb. */
        uint8_t low_g;         /* The G chanel of low_rgb. */
        uint8_t low_b;         /* The B chanel of low_rgb. */
        uint8_t alpha;         /* The alpha channel to replace destination pixel alpha channel.*/
        uint8_t hign_r;        /* The R chanel of hign_rgb. */
        uint8_t hign_g;        /* The G chanel of hign_rgb. */
        uint8_t hign_b;        /* The B chanel of hign_rgb. */
    } vg_lite_color_key_t;

    /*!
     @abstract colorkey definition.

     @discussion
     There are 4 groups of color key states.
     rgb_hi_0, rgb_lo_0, alpha_0, enable_0;
     rgb_hi_1, rgb_lo_1, alpha_1, enable_1;
     rgb_hi_2, rgb_lo_2, alpha_2, enable_2;
     rgb_hi_3, rgb_lo_3, alpha_3, enable_3;
     Priority order:color_key_0 > color_key_1 > color_key_2 > color_key_3.
    */
    typedef vg_lite_color_key_t vg_lite_color_key4_t[4];

/* API Function prototypes *****************************************************************************************************/

    /*!
     @abstract Get a 3*3 homogenous transform matrix by source coordinates and target coordinates.

     @param src
     Pointer to the four 2D points that form a source polygon.

     @param dst
     Pointer to the four 2D points that form a destination polygon.

     @param mat
     Output parameter,pointer to 3*3 homogenous matrix that transform source polygon to destination polygon.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_get_transform_matrix(vg_lite_point4_t src, vg_lite_point4_t dst,vg_lite_matrix_t *mat);

    /*!
     @abstract Allocate a buffer from hardware accessible memory.

     @discussion
     In order for the hardware to access some memory, like a source image or a target buffer, it needs to be allocated first. The
     supplied <code>vg_lite_buffer_t</code> structure needs to be initialized with the size (width and height) and format of the
     requested buffer. If the stride is set to zero, this function will fill it in.

     This function will call the kernel to actually allocate the memory and the memory handle and logical and hardware addresses
     will be filled in by the kernel.

     @param buffer
     Pointer to the buffer that holds the size and format of the buffer being allocated.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_allocate(vg_lite_buffer_t *buffer);

    /*!
     @abstract Free a buffer that was previously allocated by {@link vg_lite_allocate}.

     @discussion
     Free any memory resources allocated by a previous call to {@link vg_lite_allocate}.

     @param buffer
     Pointer to a buffer structure that was filled in by {@link vg_lite_allocate}.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_free(vg_lite_buffer_t *buffer);

    /*!
     @abstract Upload the pixel data to the buffer object.

     @discussion
     The function uploads the pixel data to the buffer object. According to the
     buffer format, there are 3 planes' data at most (for YUV planars). Note that
     the format of the data (pixel) to upload must be the same as described in
     the buffer object. The input data memory pointers should be big enough to
     hold all the data needed by the buffer.

     @param buffer
     The image buffer object.

     @param data
     Pixel data. For YUV format, it may be up to 3 pointers.

     @param stride
     Stride for pixel data.

     @result
     Any error status during uploading.
     */
    vg_lite_error_t vg_lite_buffer_upload(vg_lite_buffer_t  *buffer, uint8_t *data[3], uint32_t stride[3]);

    /*!
     @abstract Map a buffer into hardware accessible address space.

     @discussion
     If you want the use a frame buffer directly as an target buffer, you need to wrap a <code>vg_lite_buffer_t</code> structure
     around it and call the kernel to map the supplied logical or physical address into hardware accessible memory.

     For example, if you know the logical address of the frame buffer, set the memory field of the vg_lite_buffer_t structure
     with that address and call this function. If you know the physical address, set the memory field to <code>NULL</code> and
     program the address field with the physical address.

     @param buffer
     Pointer to the buffer that holds the size and format of the buffer being allocated. Either the memory or address field
     needs to be set to a non-zero value to map either a logical or physical address into hardware accessible memory.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_map(vg_lite_buffer_t *buffer);

    /*!
     @abstract Unmap a buffer that was previously mapped by {@link vg_lite_map}.

     @discussion
     Free any memory resources allocated by a previous call to {@link vg_lite_map}.

     @param buffer
     Pointer to a buffer structure that was filled in by {@link vg_lite_map}.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_unmap(vg_lite_buffer_t *buffer);

    /*!
     @abstract Fill a (partial) buffer with a specified color.

     @discussion
     Either an entire buffer or a partial rectangle of a buffer will be filled with a specific color.

     This function will wait until the hardware is complete, i.e. it is synchronous.

     @param target
     Pointer to a <code>vg_lite_buffer_t</code> structure that describes the buffer to be filled.

     @param rectangle
     Pointer to a rectangle that specifies the area to be filled. If <code>rectangle</code> is <code>NULL</code>, the entire target
     buffer will be filled with the specified color.

     @param color
     The color value to use for filling the buffer. If the buffer is in L8 format, the RGBA color will be converted into a
     luminance value.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_clear(vg_lite_buffer_t *target,
                                  vg_lite_rectangle_t *rectangle,
                                  vg_lite_color_t color);

    /*!
     @abstract Copy a source image to the the destination window with a specified matrix that can include translation, rotation,
     scaling, and perspective correction.

     @discussion
     A source image is copied to the target using the specified matrix. If the specified matrix is <code>NULL</code>, an identity
     matrix is assumed, meaning the source will be copied directly on the target at 0,0 location.

     An optional blend mode can be specified that defines the blending of the source onto the target.

     Also, an optional mix color can be specified. The mix color will be multiplied by the source color. If you don't need a mix
     color, set the <code>color</code> parameter to 0.

     Note that on hardware that doesn't support border scissoring (GC355) the blend mode will be forced to
     <code>VG_LITE_BLEND_SRC_OVER</code> if rotation or perspective is involved.

     @param target
     Pointer to a <code>vg_lite_buffer_t</code> structure that describes the target of the blit.

     @param source
     Pointer to a <code>vg_lite_buffer_t</code> structure that describes the source of the blit.

     @param matrix
     Pointer to a 3x3 matrix that defines the transformation matrix of source pixels into the target. If matrix is
     <code>NULL</code>, an identity matrix is assumed.

     @param blend
     The blending mode to be applied to each image pixel. If no blending is required, set this value to
     <code>VG_LITE_BLEND_NONE</code> (0).

     @param color
     If non-zero, this color value will be used as a mix color. The mix color gets multiplied with each source pixel before
     blending happens.

     @param filter
     The filter mode to be applied. If no filter mode is required, set this value to
     <code>VG_LITE_FILTER_BI_LINEAR</code> (0x20000).

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_blit(vg_lite_buffer_t *target,
                                 vg_lite_buffer_t *source,
                                 vg_lite_matrix_t *matrix,
                                 vg_lite_blend_t blend,
                                 vg_lite_color_t color,
                                 vg_lite_filter_t filter);

    /* In additional to vg_lite_blit:
    @brief
    This API draws a porting of the image to the screen.

    @param
    rect   The source rectangle to blit. rect[0]/[1]/[2]/[3] are x, y, width and height of the source rectangle. */
    vg_lite_error_t vg_lite_blit_rect(vg_lite_buffer_t *target,
        vg_lite_buffer_t *source,
        uint32_t         *rect,
        vg_lite_matrix_t *matrix,
        vg_lite_blend_t   blend,
        vg_lite_color_t   color,
        vg_lite_filter_t  filter);

    /*!
     @abstract Initialize a vglite context.

     @discussion
     The {@link vg_lite_draw} function requires a draw context to be initialized. There is only one draw context per process, so
     this function has be called once in your application if any draw command will be used. If this would be the first context that
     accesses the hardware, the hardware will be turned on and initialized.

     The difference between a blit and draw context is that the draw context has a larger command buffer and allocates a
     tessellation buffer for the hardware. The size of the tessellation buffer can be specified, and that size will be aligned to
     the minimum required alignment of the hardware by the kernel. If you make the tessellation buffer smaller, less memory will
     be allocated, but a path might be sent down to the hardware multiple times because the hardware will walk the target with the
     provided tessellation window size, so performance might go down. It is good practice to set the tessellation buffer size to the
     most common path size. For example, if all you do is render up to 24-pt fonts, you can set the tessellation buffer to be
     24x24.

     @param tessellation_width
     The width of the tessellation window.

     @param tessellation_height
     The height of the tessellation window.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_init(int32_t tessellation_width, int32_t tessellation_height);

    /*!
     @abstract Destroy a vglite context.

     @discussion
     Destroy a draw context that was previously initialized by {@link vg_lite_draw_init}.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_close(void);

    /*!
     @abstract This api explicitly submits the command buffer to GPU and waits for it to complete.

     @param none.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_finish(void);

    /*!
     @abstract This api explicitly submits the command buffer to GPU without waiting for it to complete.

     @param none.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_flush(void);

    /*!
     @abstract Draw a path to a target buffer.

     @discussion
     The specified path will be transformed by the given matrix and drawn into the specified target buffer using the supplied color.
     Blending can be specified.

     @param target
     Pointer to a <code>vg_lite_buffer_t</code> structure that describes the target of the draw.

     @param path
     Pointer to a <code>vg_lite_path_t</code> structure that describes the path to draw.

     @param fill_rule
     Specified fill rule for the path.

     @param matrix
     Pointer to a 3x3 matrix that defines the transformation matrix of the path. If <code>matrix</code> is <code>NULL</code>, an
     identity matrix is assumed which is usually a bad idea since the path can be anything.

     @param blend
     The blending mode to be applied to each drawn pixel. If no blending is required, set this value to
     <code>VG_LITE_BLEND_NONE</code> (0).

     @param color
     The color applied to each pixel drawn by the path.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_draw(vg_lite_buffer_t *target,
                                 vg_lite_path_t   *path,
                                 vg_lite_fill_t    fill_rule,
                                 vg_lite_matrix_t *matrix,
                                 vg_lite_blend_t   blend,
                                 vg_lite_color_t   color);

    /*!
     @abstract Set stroke path's attributes.

     @discussion
     This function use the input parameters to set stroke attributes.

     @param path
     Pointer to a <code>vg_lite_path_t</code> structure that describes the path.

     @param stroke_cap_style
     The end cap style defined by <code>vg_lite_cap_style_t</code>.

     @param stroke_join_style
     The line join style defined by <code>vg_lite_join_style_t</code>.

     @param stroke_line_width
     The line width of stroke path.A line width less than or equal to 0 prevents stroking from taking place.

     @param stroke_miter_limit
     When stroking using the Miter join style, the miter length (i.e., the length between the
     intersection points of the inner and outer perimeters of the two “fattened” lines) is compared
     to the product of the user-set miter limit and the line width. If the miter length exceeds this
     product, the Miter join is not drawn and a Bevel join is substituted.Miter limit values less
     than 1 are silently clamped to 1.

     @param stroke_dash_pattern
     The dash pattern consists of a sequence of lengths of alternating "on" and "off" dash
     segments. The first value of the dash array defines the length, in user coordinates, of the
     first "on" dash segment. The second value defines the length of the following "off"
     segment. Each subsequent pair of values defines one "on" and one "off" segment.If the dash
     pattern has an odd number of elements, the final element is ignored.

     @param stroke_dash_pattern_count
     The count of dash on/off segments.

     @param stroke_dash_phase
     The dash phase defines the starting point in the dash pattern that is associated with the
     start of the first segment of the path. For example, if the dash pattern is [10 20 30 40]
     and the dash phase is 35, the path will be stroked with an "on" segment of length 25
     (skipping the first "on" segment of length 10, the following "off" segment of length 20,
     and the first 5 units of the next "on" segment), followed by an "off" segment of length
     40. The pattern will then repeat from the beginning, with an “on” segment of length 10,
     an "off" segment of length 20, an "on" segment of length 30.

     @param stroke_color
     The color fill in stroke path.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_set_stroke(vg_lite_path_t *path,
                                       vg_lite_cap_style_t stroke_cap_style,
                                       vg_lite_join_style_t stroke_join_style,
                                       vg_lite_float_t stroke_line_width,
                                       vg_lite_float_t stroke_miter_limit,
                                       vg_lite_float_t *stroke_dash_pattern,
                                       uint32_t stroke_dash_pattern_count,
                                       vg_lite_float_t stroke_dash_phase,
                                       vg_lite_color_t stroke_color);
    /*!
     @abstract Update stroke path.

     @discussion
     This function use the given path and stroke attributes given by function vg_lite_set_stroke
     to update stroke path's parameters and generate stroke path data.

     @param path
     Pointer to a <code>vg_lite_path_t</code> structure that describes the path.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_update_stroke(vg_lite_path_t *path);

    /*!
     @abstract Set path type.

     @discussion
     This function set the path type.It can be VG_LITE_DRAW_FILL_PATH ,VG_LITE_DRAW_STROKE_PATH or
     VG_LITE_DRAW_FILL_PATH | VG_LITE_DRAW_STROKE_PATH.

     @param path
     Pointer to a <code>vg_lite_path_t</code> structure that describes the path.

     @param path_type
     Pointer to a <code>vg_lite_draw_path_type_t</code> structure that describes the path.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_set_draw_path_type(vg_lite_path_t * path,vg_lite_draw_path_type_t path_type);

    /*!
     @abstract Get the value of register from register's address.

     @discussion
     This address will be the AHB Byte address of the register whose value you want to dump.
     Refer to the Vivante AHB Register Specification document for register descriptions.
     The valid range for VGLite cores is usually 0x0 to 0x1FF and 0xA00 to 0xA7F.

     @param address
     Address of register which is needed to get its value.

     @param result
     The register's value.

     */
    vg_lite_error_t vg_lite_get_register(uint32_t address, uint32_t *result);

    /*
     @abstract Get the VGLite driver information.

     @param info
     Pointer to vg_lite_info_t structure.
     */
    void vg_lite_get_info(vg_lite_info_t *info);

    /*
     @abstract Get the name of the VGLite Product.

     @param name
     Character array to store the name of the chip.

     @param chip_id
     Store the chip id.

     @param chip_rev
     Store the chip revision number.

     @return
     Length of the name string, including the ending '\0'.
     */
    uint32_t vg_lite_get_product_info(char *name, uint32_t *chip_id, uint32_t *chip_rev);

    /*!
     @abstract Queried whether the specified feature is available.

     @param feature
     Feature to be verified.

     @return
     The feature is supported (1) or not (0).
     */
    uint32_t vg_lite_query_feature(vg_lite_feature_t feature);

    /*!
     @abstract This api initializes a path object by given member values.

     @param path
     The path object.

     @param data_format
     The coordinate data format of the path. One of S8, S16, S32 and FP32.

     @param quality
     The rendering quality (AA level) of the path.

     @param path_length
     The memory length of the path data.

     @param path_data
     The path data.

     @param min_x
     The min x of the bounding box.

     @param min_y
     The min y of the bounding box.

     @param max_x
     The max x of the bounding box.

     @param max_y
     The max y of the bounding box.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_init_path(vg_lite_path_t *path,
                           vg_lite_format_t data_format,
                           vg_lite_quality_t quality,
                           uint32_t path_length,
                           void *path_data,
                           vg_lite_float_t min_x, vg_lite_float_t min_y,
                           vg_lite_float_t max_x, vg_lite_float_t max_y);

     /*!
     @abstract This api initializes a path object which include arc command by given member values.

     @param path
     The path object.

     @param data_format
     The coordinate data format of the path. Should be FP32.

     @param quality
     The rendering quality (AA level) of the path.

     @param path_length
     The memory length of the path data.

     @param path_data
     The given path data which inlcude arc command.

     @param min_x
     The min x of the bounding box.

     @param min_y
     The min y of the bounding box.

     @param max_x
     The max x of the bounding box.

     @param max_y
     The max y of the bounding box.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_init_arc_path(vg_lite_path_t * path,
                           vg_lite_format_t data_format,
                           vg_lite_quality_t quality,
                           uint32_t path_length,
                           void *   path_data,
                           vg_lite_float_t min_x, vg_lite_float_t min_y,
                           vg_lite_float_t max_x, vg_lite_float_t max_y);

    /*!
     @abstract This api clears the path member values.

     @discussion It frees the hw memory if path was ever uploaded.

     @param path
     The path object.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_clear_path(vg_lite_path_t *path);

    /*!
     @abstract Calculate the path command buffer length (in bytes).

     @discussion The app should be response for allocating a buffer according to
     the buffer length calculated by this function. Then the buffer is used by
     the path as command buffer. The driver does not do allocation for the buffer.

     @param cmd
     The opcode array to construct the path.

     @param count
     The count of opcodes.

     @param format
     The data format of the coordinate (VG_LITE_S8, S16, S32, FP32)

     @result
     Return the actual length of the path command buffer.
     */
    int32_t vg_lite_path_calc_length(uint8_t           *cmd,
                                     uint32_t           count,
                                     vg_lite_format_t   format);

    /*!
     @abstract Assemble the command buffer for the path.

     @discussion The command buffer is allocated by the application and assigned
     to the path. The function make the final GPU command buffer for the path based
     on the input opcodes (cmd) and coordinates (data). Note that the Application
     must be responsible to alloate a big enough buffer for the path.

     @param path
     The path object.

     @param cmd
     The opcode array to construct the path.

     @param data
     The coordinate data array to construct the path.

     @param seg_count
     The count of the opcodes.

     */
    vg_lite_error_t vg_lite_path_append(vg_lite_path_t *path,
                             uint8_t        *cmd,
                             void           *data,
                             uint32_t        seg_count);

    /*!
     @abstract Upload a path to GPU memory.

     @discussion
     In normal cases, the VGLite driver will copy any path data into a command buffer structure during runtime. This does take some
     time if there are many paths to be rendered. Also, in an embedded system the path data wont change - so it makes sense to
     upload the path data into GPU memory in such a form the GPU can directly access it.

     This function will allocate a buffer that will contain the path data and the required command buffer header and footer data for
     the GPU to access the data directly.

     @param path
     Pointer to a <code>vg_lite_path_t</code> structure that contains the path to be uploaded. Some fields in this structure will be
     modified to point to a command buffer instead of the native path data.

     @result
     A pointer to a <code>vg_lite_buffer_t</code> structure that contains the command buffer and path data after uploading it to GPU
     memory. <code>NULL</code> is returned if there is an error.
     */
    vg_lite_error_t vg_lite_upload_path(vg_lite_path_t *path);

    /*!
     @abstract Set the current CLUT (Color Look Up Table) for index image to use.

     @discussion
     This is a global context state. Once it's set (Not NULL), when an indexed format image is rendered, the image color will
     be got from the CLUT by the image's pixels as indecies.

     @param count
     This is the count of the colors in the look up table.
     For index 1, up to 2 colors in the table;
     For index 2, up to 4 colors in the table;
     For index 4, up to 16 colors in the table;
     For index 8, up to 256 colros in the table.
     Driver is not responsible to check the validation of the CLUT.

     @param colors
     This pointer is directly programmed to the command buffer. So it won't take effect
     unless the command buffer is submitted. The color is in ARGB format with A staying at the high bits.

     @result
     Error code. Currently always returns VG_LITE_SUCCESS since it does not do any checks.
     */
    vg_lite_error_t vg_lite_set_CLUT(uint32_t count,
                                     uint32_t *colors);

    /*!
     @abstract Fill a path with an image pattern.

     @discussion
     The specified path will be transformed by the given matrix and filled by the tranformed image pattern.

     @param path
     Pointer to a <code>vg_lite_path_t</code> structure that describes the path to draw.

     @param fill_rule
     Specified fill rule for the path.

     @param matrix0
     Pointer to a 3x3 matrix that defines the transformation matrix of the path. If <code>matrix</code> is <code>NULL</code>, an
     identity matrix is assumed which is usually a bad idea since the path can be anything.

     @param source
     Pointer to a <code>vg_lite_buffer_t</code> structure that describes the source of the image pattern.

     @param matrix1
     Pointer to a 3x3 matrix that defines the transformation matrix of source pixels into the target. If matrix is
     <code>NULL</code>, an identity matrix is assumed.

     @param blend
     The blending mode to be applied to each drawn pixel. If no blending is required, set this value to
     <code>VG_LITE_BLEND_NONE</code> (0).

     @param pattern_mode
     The tiling mode that applied to the pixels out of the image after transformed.

     @param pattern_color
     The pattern_color applied by pattern_mode VG_LITE_PATTERN_COLOR. When pixels are out of the image after transformed,
     they are applied "pattern_color".

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_draw_pattern(vg_lite_buffer_t *target,
                                         vg_lite_path_t *path,
                                         vg_lite_fill_t fill_rule,
                                         vg_lite_matrix_t *matrix0,
                                         vg_lite_buffer_t *source,
                                         vg_lite_matrix_t *matrix1,
                                         vg_lite_blend_t blend,
                                         vg_lite_pattern_mode_t pattern_mode,
                                         vg_lite_color_t  pattern_color,
                                         vg_lite_filter_t filter);

    /*!
     @abstract Init the linear gradient object.

     @discussion
     This API initialize the grad object to its default settings. Since grad has
     an internal buffer object, this API will init the buffer object for rendering use.

     @param grad
     This is the vg_lite_linear_gradient_t object to be initialized.

     @result
     Error code, in case the buffer can't be created.
     */
    vg_lite_error_t vg_lite_init_grad(vg_lite_linear_gradient_t *grad);

    /*!
     @abstract Set the linear gradient members.

     @discussion
     This API sets the values for the members of the gradient definition.

     @param grad
     This is the vg_lite_linear_gradient_t object to be set.

     @param count
     This is the count of the colors in grad.
     The maxmum color stop count is defined by VLC_MAX_GRAD, which is currently 16.

     @param colors
     This is the color array for the gradient stops. The color is in ARGB8888 format
     with alpha at the higher byte.

     @result
     Error code. VG_LITE_INVALID_ARGUMENTS to indicate the parameters are wrong.
     */
    vg_lite_error_t vg_lite_set_grad(vg_lite_linear_gradient_t *grad,
                                     uint32_t count,
                                     uint32_t *colors,
                                     uint32_t *stops);

    /*!
     @abstract Set the radial gradient members.

     @discussion
     This API sets the values for the members of the radial gradient definition.

     @param grad
     This is the vg_lite_radial_gradient_t object to be set.

     @param count
     This is the count of the colors in grad.
     The maxmum color stop count is defined by MAX_COLOR_RAMP_STOPS, which is currently 256.

     @param vgColorRamp
     This is the stop for the radial gradient.The number of parameters is 5,and give the offset and
     color of the stop.Each stop is defined by a floating-point offset value and four floating-point values
     containing the sRGBA color and alpha value associated with each stop, in the form of a non-premultiplied
     (R, G, B, alpha) quad.And the range of all parameters in it is [0,1].

     @param radialGradient
     The radial gradient parameters are supplied as a vector of 5 floats in the order {cx,cy,fx,fy,r}.
     the range of all parameters in it is [0,1].The meaning of the parameters in it is:(cx,cy) is center point,
     (fx,fy) is focal point, and r is radius.

     @param SpreadMode
     The tiling mode that applied to the pixels out of the paint after transformed.

     @param colorRampPremultiplied
     The parameter controls whether color and alpha values are interpolated in premultiplied or non-premultiplied
     form.

     @result
     Error code. VG_LITE_INVALID_ARGUMENTS to indicate the parameters are wrong.
     */
    vg_lite_error_t vg_lite_set_rad_grad(vg_lite_radial_gradient_t *grad,
                                     uint32_t count,
                                     vg_lite_color_ramp_t *vgColorRamp,
                                     vg_lite_radial_gradient_parameter_t radialGradient,
                                     vg_lite_radial_gradient_spreadmode_t SpreadMode,
                                     uint8_t colorRampPremultiplied);

    /*!
     @abstract Set the linear gradient members.

     @discussion
     This API sets the values for the members of the linear gradient definition.

     @param grad
     This is the vg_lite_linear_gradient_ext_t object to be set.

     @param count
     This is the count of the colors in grad.
     The maxmum color stop count is defined by MAX_COLOR_RAMP_STOPS, which is currently 256.

     @param vg_color_ramp
     This is the stop for the linear gradient.The number of parameters is 5,and give the offset and
     color of the stop.Each stop is defined by a floating-point offset value and four floating-point values
     containing the sRGBA color and alpha value associated with each stop, in the form of a non-premultiplied
     (R, G, B, alpha) quad.And the range of all parameters in it is [0,1].

     @param linear_gradient
     Refer to the definition by <code>vg_lite_linear_gradient_parameter_t</code>.

     @param spread_mode
     The tiling mode that applied to the pixels out of the paint after transformed.Use tge same spread mode enumeration type as radial gradient.

     @param color_ramp_premultiplied
     The parameter controls whether color and alpha values are interpolated in premultiplied or non-premultiplied
     form.

     @result
     Error code. VG_LITE_INVALID_ARGUMENTS to indicate the parameters are wrong.
     */
    vg_lite_error_t vg_lite_set_linear_grad(vg_lite_linear_gradient_ext_t *grad,
                                            uint32_t count,
                                            vg_lite_color_ramp_t *vg_color_ramp,
                                            vg_lite_linear_gradient_parameter_t linear_gradient,
                                            vg_lite_radial_gradient_spreadmode_t spread_mode,
                                            uint8_t color_ramp_premultiplied);

    /*!
     @abstract Update or generate the corresponding image object to render with.

     @discussion
     The vg_lite_linear_gradient_ext_t object has an image buffer which is used to render
     the linear gradient paint. The image buffer will be create/updated by the corresponding
     grad parameters.

     @param grad
     This is the vg_lite_linear_gradient_ext_t object to be updated from.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_update_linear_grad(vg_lite_linear_gradient_ext_t *grad);

    /*!
     @abstract Update or generate the corresponding image object to render with.

     @discussion
     The vg_lite_linear_gradient_t object has an image buffer which is used to render
     the gradient pattern. The image buffer will be create/updated by the corresponding
     grad parameters.

     @param grad
     This is the vg_lite_linear_gradient_t object to be upated from.

     @result
     Error code.
     */
    vg_lite_error_t vg_lite_update_grad(vg_lite_linear_gradient_t *grad);

    /*!
     @abstract Update or generate the corresponding image object to render with.

     @discussion
     The vg_lite_radial_gradient_t object has an image buffer which is used to render
     the radial gradient paint. The image buffer will be create/updated by the corresponding
     grad parameters.

     @param grad
     This is the vg_lite_radial_gradient_t object to be upated from.

     @result
     Error code.
     */
    vg_lite_error_t vg_lite_update_rad_grad(vg_lite_radial_gradient_t *grad);

    /*!
     @abstract Clear the gradient object.

     @discussion
     This will reset the grad members and free the image buffer's memory.

     @param grad
     This is the vg_lite_linear_gradient_t object to be cleared.

     @result
     Error code.
     */
    vg_lite_error_t vg_lite_clear_grad(vg_lite_linear_gradient_t *grad);

    /*!
     @abstract Clear the radial gradient object.

     @discussion
     This will reset the grad members and free the image buffer's memory.

     @param grad
     This is the vg_lite_radial_gradient_t object to be cleared.

     @result
     Error code.
     */
    vg_lite_error_t vg_lite_clear_rad_grad(vg_lite_radial_gradient_t *grad);

    /*!
     @abstract Clear the linear gradient object.

     @discussion
     This will reset the grad members and free the image buffer's memory.

     @param grad
     This is the vg_lite_linear_gradient_ext_t object to be cleared.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_clear_linear_grad(vg_lite_linear_gradient_ext_t *grad);

    /*!
     @abstract Get the pointer to the grad object's matrix.

     @discussion
     This function get the pointer to the gradient object's matrix. Thus the app
     can manipulate the matrix to render the gradient path correctly.

     @param grad
     This is the vg_lite_linear_gradient_t object where to get the matrix.

     @result
     The pointer to the matrix.
     */
    vg_lite_matrix_t * vg_lite_get_grad_matrix(vg_lite_linear_gradient_t *grad);

    /*!
     @abstract Get the pointer to the grad object's matrix.

     @discussion
     This function get the pointer to the gradient object's matrix. Thus the app
     can manipulate the matrix to render the gradient path correctly.

     @param grad
     This is the vg_lite_linear_gradient_ext_t object where to get the matrix.

     @result
     The pointer to the matrix.
     */
     vg_lite_matrix_t * vg_lite_get_linear_grad_matrix(vg_lite_linear_gradient_ext_t *grad);

    /*!
     @abstract Get the pointer to the grad object's matrix.

     @discussion
     This function get the pointer to the radial gradient object's matrix. Thus the app
     can manipulate the matrix to render the radial gradient path correctly.

     @param grad
     This is the vg_lite_radial_gradient_t object where to get the matrix.

     @result
     The pointer to the matrix.
     */
    vg_lite_matrix_t * vg_lite_get_rad_grad_matrix(vg_lite_radial_gradient_t *grad);

    /*!
     @abstract Fill a path with an image pattern.

     @discussion
     The specified path will be transformed by the given matrix and filled by the tranformed image pattern.

     @param path
     Pointer to a <code>vg_lite_path_t</code> structure that describes the path to draw.

     @param fill_rule
     Specified fill rule for the path.

     @param matrix0
     Pointer to a 3x3 matrix that defines the transformation matrix of the path. If <code>matrix</code> is <code>NULL</code>, an
     identity matrix is assumed which is usually a bad idea since the path can be anything.

     @param grad
     Pointer to the gradient object that will be filled the path with.

     @param blend
     The blending mode to be applied to each drawn pixel. If no blending is required, set this value to
     <code>VG_LITE_BLEND_NONE</code> (0).

     @param pattern_mode
     The tiling mode that applied to the pixels out of the image after transformed.

     @param pattern_color
     The pattern_color applied by pattern_mode VG_LITE_PATTERN_COLOR. When pixels are out of the image after transformed,
     they are applied "pattern_color".

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_draw_gradient(vg_lite_buffer_t *target,
                                          vg_lite_path_t *path,
                                          vg_lite_fill_t fill_rule,
                                          vg_lite_matrix_t *matrix,
                                          vg_lite_linear_gradient_t *grad,
                                          vg_lite_blend_t blend);

    /*!
     @abstract Fill a path with a linear gradient.

     @discussion
     The specified path will be transformed by the given matrix and filled by the tranformed linear gradient.

     @param path
     Pointer to a <code>vg_lite_path_t</code> structure that describes the path to draw.

     @param fill_rule
     Specified fill rule for the path.

     @param path_matrix
     Pointer to a 3x3 matrix that defines the transformation matrix of the path. If <code>matrix</code> is <code>NULL</code>, an
     identity matrix is assumed which is usually a bad idea since the path can be anything.

     @param grad
     This is the vg_lite_linear_gradient_ext_t object to be set.

     @param paint_color
     Specifies the paint color vg_lite_color_t RGBA value to applied by VG_LITE_RADIAL_GRADIENT_SPREAD_FILL,which set by fuction
     vg_lite_set_linear_grad. When pixels are out of the image after transformed,this paint_color is applied to them,See enum
     vg_lite_radial_gradient_spreadmode_t.

     @param blend
     The blending mode to be applied to each drawn pixel. If no blending is required, set this value to
     <code>VG_LITE_BLEND_NONE</code> (0).

     @param filter
     Specified the filter mode vg_lite_filter_t enum value to be applied to each drawn pixel.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_draw_linear_gradient(vg_lite_buffer_t * target,
                                     vg_lite_path_t * path,
                                     vg_lite_fill_t fill_rule,
                                     vg_lite_matrix_t * path_matrix,
                                     vg_lite_linear_gradient_ext_t *grad,
                                     vg_lite_color_t paint_color,
                                     vg_lite_blend_t blend,
                                     vg_lite_filter_t filter);

    /*!
     @abstract Fill a path with a radial gradient.

     @discussion
     The specified path will be transformed by the given matrix and filled by the tranformed radial gradient.

     @param path
     Pointer to a <code>vg_lite_path_t</code> structure that describes the path to draw.

     @param fill_rule
     Specified fill rule for the path.

     @param path_matrix
     Pointer to a 3x3 matrix that defines the transformation matrix of the path. If <code>matrix</code> is <code>NULL</code>, an
     identity matrix is assumed which is usually a bad idea since the path can be anything.

     @param grad
     This is the vg_lite_radial_gradient_t object to be set.

     @param paint_color
     Specifies the paint color vg_lite_color_t RGBA value to applied by VG_LITE_RADIAL_GRADIENT_SPREAD_FILL,which set by fuction
     vg_lite_set_rad_grad. When pixels are out of the image after transformed,this paint_color is applied to them,See enum
     vg_lite_radial_gradient_spreadmode_t.

     @param blend
     The blending mode to be applied to each drawn pixel. If no blending is required, set this value to
     <code>VG_LITE_BLEND_NONE</code> (0).

     @param filter
     Specified the filter mode vg_lite_filter_t enum value to be applied to each drawn pixel.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_draw_radial_gradient(vg_lite_buffer_t * target,
                                     vg_lite_path_t * path,
                                     vg_lite_fill_t fill_rule,
                                     vg_lite_matrix_t * path_matrix,
                                     vg_lite_radial_gradient_t *grad,
                                     vg_lite_color_t  paint_color,
                                     vg_lite_blend_t blend,
                                     vg_lite_filter_t filter);

    /*!
     @abstract Load an identity matrix.

     @discussion
     Load an identity matrix into a matrix variable.

     @param matrix
     Pointer to a <code>vg_lite_matrix_t</code> structure that will be loaded with an identity matrix.
     */
    void vg_lite_identity(vg_lite_matrix_t *matrix);

    /*!
     @abstract Translate a matrix.

     @discussion
     Translate a matrix to a new position.

     @param x
     X location of the transformation.

     @param y
     Y location of the transformation.

     @param matrix
     Pointer to a <code>vg_lite_matrix_t</code> structure that will be translated.
     */
    void vg_lite_translate(vg_lite_float_t x, vg_lite_float_t y, vg_lite_matrix_t *matrix);

    /*!
     @abstract Scale a matrix.

     @discussion
     Scale a matrix in both x and y directions.

     @param scale_x
     Horizontal scale.

     @param scale_y
     Vertical scale.

     @param matrix
     Pointer to a <code>vg_lite_matrix_t</code> structure that will be scaled.
     */
    void vg_lite_scale(vg_lite_float_t scale_x, vg_lite_float_t scale_y, vg_lite_matrix_t *matrix);

    /*!
     @abstract Rotate a matrix.

     @discussion
     Rotate a matrix a certain number of degrees.

     @param degrees
     Number of degrees to rotate the matrix around. Positive numbers rotate counter clock wise.

     @param matrix
     Pointer to a <code>vg_lite_matrix_t</code> structure that will be rotated.
     */
    void vg_lite_rotate(vg_lite_float_t degrees, vg_lite_matrix_t *matrix);

    /*!
     @abstract Set the command buffer size.

     @discussion
     In the rt device, the memory was limited, need to set the command buffer
     size by the chip.
     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_set_command_buffer_size(uint32_t size);

    /*!
     @abstract Set scissor used for render target's boundary.

     @discussion
      This function is used to set a scissor into render target so that the out region
      of scissor boundary is not drawn.

     @param x, y, width, height
      The scissor bounds which specifies the x, y, width, and height of the region.

     @result
      Returns the status as defined by <code>vg_lite_error_t</code>.*/
    vg_lite_error_t vg_lite_set_scissor(int32_t x, int32_t y, int32_t width, int32_t height);

    /*!
      @abstract Enable scissor.

      @result
      Returns the status as defined by <code>vg_lite_error_t</code>.*/
    vg_lite_error_t vg_lite_enable_scissor(void);

    /*!
      @abstract Disable scissor.

      @result
      Returns the status as defined by <code>vg_lite_error_t</code>.*/
    vg_lite_error_t vg_lite_disable_scissor(void);

    /*!
      @abstract query the remaining allocate contiguous video memory.

      @param size
      This is a pointer to remaining allocate contiguous video memory.

      @result
      Returns the status as defined by <code>vg_lite_error_t</code>.The result correctly returns VG_LITE_SUCCESS,
      return VG_LITE_NO_CONTEXT if not initialized.*/
    vg_lite_error_t vg_lite_mem_avail(uint32_t *size);

    /*!
      @abstract Enable premultiply.

      @result
      Returns the status as defined by <code>vg_lite_error_t</code>.*/
    vg_lite_error_t vg_lite_enable_premultiply(void);

    /*!
      @abstract Disable premultiply.

      @result
      Returns the status as defined by <code>vg_lite_error_t</code>.*/
    vg_lite_error_t vg_lite_disable_premultiply(void);

    /*!
     @abstract This api use to control dither function switch.Dither is turned off by default.

     @param enable
     0 means turn off the dither function. 1 means turn on the dither function.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
     */
    vg_lite_error_t vg_lite_set_dither(int enable);

    /*!
      @abstract use to set the colorkey.

      @param colorkey
      Defined by <code>vg_lite_color_key4_t</code>.

      @result
      Returns the status as defined by <code>vg_lite_error_t</code>.
      Possible return value in this function:
          VG_LITE_SUCCESS,the result correctly
          VG_LITE_NOT_SUPPORT, if not support colorkey.*/
    vg_lite_error_t vg_lite_set_color_key(vg_lite_color_key4_t colorkey);

#endif /* VGLITE_VERSION_2_0 */


/**************************** Capture ********************************************/
#ifndef vgliteDUMP_PATH
#   define vgliteDUMP_PATH                      "./"
#endif

#ifndef vgliteDUMP_KEY
#   define vgliteDUMP_KEY                          "process"
#endif

#define DUMP_CAPTURE                            0

#if DUMP_CAPTURE
void _SetDumpFileInfo();

vg_lite_error_t
    vglitefDump(
    char * String,
    ...
    );
#  define vglitemDUMP               vglitefDump

vg_lite_error_t
    vglitefDumpBuffer(
    char* Tag,
    unsigned int Physical,
    void * Logical,
    unsigned int Offset,
    size_t Bytes
    );
#   define vglitemDUMP_BUFFER       vglitefDumpBuffer
#else
inline static void __dummy_dump(
    char * Message,
    ...
    )
{
}
#  define vglitemDUMP               __dummy_dump

inline static void
    __dummy_dump_buffer(
    char* Tag,
    unsigned int Physical,
    void * Logical,
    unsigned int Offset,
    size_t Bytes
    )
{
}
#   define vglitemDUMP_BUFFER       __dummy_dump_buffer
#endif
/**************************** Capture ********************************************/

#ifdef __cplusplus
}
#endif
#endif /* _vg_lite_h_ */
