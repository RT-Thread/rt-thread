/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright 2020 NXP
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
#ifndef _vg_lite_text_h_
#define _vg_lite_text_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "vg_lite.h"

/* Macros *********************************************************************/

#define MAX_FONT_NAME_LEN               (64)
#define VG_LITE_INVALID_FONT            (-1)
#define INVALID_FONT_PROPERTY_IDX       (-1)

/* Types **********************************************************************/

    /*!
     @abstract Font Type enumeration

     @discussion
     This enumeration defines supported high level font type type.
     */
    typedef enum eFontType {
      eFontTypeVector,
      eFontTypeRaster
    } eFontType_t;

    /*!
     @abstract Font weight enumeration

     @discussion
     This enumeration defines font weight that maps to css specification
     */
    typedef enum eFontWeight {
        eFontWeightThin     = 100, /*! Thin, Hairline, Ultra-light, Extra-light */
        eFontWeightLight    = 200, /*! Light */
        eFontWeightBook     = 300, /*! Book */
        eFontWeightRegular  = 400, /*! Regular, Normal, Plain, Roman, Standard */
        eFontWeightMedium   = 500, /*! Medium */
        eFontWeightSemiBold = 600, /*! Semi-bold, Demi-bold */
        eFontWeightBold     = 700, /*! Bold */
        eFontWeightHeavy    = 800, /*! Heavy, Black, Extra-bold */
        eFontUltraBlack     = 900, /*! Ultra-black, Extra-black, Ultra-bold,
                                      Heavy-black, Fat, Poster */
    } eFontWeight_t;

    /*!
     @abstract Font stretch enumeration

     @discussion
     This enumeration defines font stretch that maps to css specification
     */
    typedef enum eFontStretch {
        eFontStretchUltraCondensed  = 1, /*! ultra-condensed */
        eFontStretchExtraCondensed  = 2, /*! extra-condensed */
        eFontStretchCondensed       = 3, /*! condensed */
        eFontStretchSemiCondensed   = 4, /*! semi-condensed */
        eFontStretchNormal          = 5, /*! normal */
        eFontStretchSemiExpanded    = 6, /*! semi-expanded */
        eFontStretchExpanded        = 7, /*! expanded */
        eFontStretchExtraExpanded   = 8, /*! extra-expanded */
        eFontStretchUltraExpanded   = 9, /*! ultra-expanded */
    } eFontStretch_t;

    /*!
     @abstract Font style enumeration

     @discussion
     This enumeration defines font style that maps to css specification
     */
    typedef enum eFontStyle {
        eFontStyleNormal  = 1, /*! normal */
        eFontStyleItalic  = 2, /*! italic, oblique */
    } eFontStyle_t;

    /*!
     @abstract Text alignment enumeration

     @discussion
     This enumeration defines text alignment that maps to css specification
     */
    typedef enum eTextAlign {
      eTextAlignLeft,
      eTextAlignCenter,
      eTextAlignRight,
      eTextAlignJustify,
    } eTextAlign_t;

/* Structures *****************************************************************/

    /*!
     @abstract Font parameters

     @discussion
     This datastructure specifies application font and its data. Application
     can register as many font as required using vg_lite_register_font
     And lateron refer them in vg_lite_draw_text API

     for raster fonts mandatory fields are:
       name,
       font_weight, font_stretch, font_style, font_height
       data, data_len
     for vector fonts mandatory fields are:
       name,
       data, data_len
     */
    typedef struct vg_lite_font_params
    {
        char name[MAX_FONT_NAME_LEN]; /*! font-family name */
        eFontType_t    font_type;     /*! Raster/Vector font */
        eFontWeight_t   font_weight;  /*! Font weight enum value */
        eFontStretch_t  font_stretch; /*! Font stretch enum value */
        eFontStyle_t    font_style;   /*! Font style enum value */
        int font_height;              /*! Font height in pixels */
        int data_len;                 /*! Font data buffer length */
        void *data; /*! the address where the actual font data is stored; it is the
                     * responsibility of the user/application to load it there */
    } vg_lite_font_params_t;

    /*!
     @abstract Opaque type for font descriptor

     @discussion
     This is an index of into font-table. Font table can have atmost
     MAX_SYSTEM_FONTS font, registering more font results in an error.
     */
    typedef uint32_t vg_lite_font_t;

    /*!
     @abstract Runtime parameter to render text using given font

     @discussion
     These parameters controls rendering of text using given font.
     */
    typedef struct {
        /* Application controllable parameters */
        int justify; /*! Equal justify given text in text display area */
        int alignment; /*! Ailgn text to left, center or right */

        int width;  /*! Internal variable computed based on active font */
        int height; /*! Internal variable computed based on active font */

        unsigned int text_color; /*! Foreground text color */
        unsigned int bg_color;   /*! Background text color */

        int tspan_has_dx_dy; /*! 0 means tspan element has x,y values
                              1 means tspan element has dx, dy values
                                so use last_x+dx for x,
                                       last_y+dy for y
                           */
        int is_vector_font; /*! 1 when active font is vector font, 0 otherwise */

        int margin; /*! Left and right margin in pixels that should be skipped
                       by text rendering engine */
        int anchor; /*! Anchor text */
        int scale;  /*! Flag that indicate if text rendering engine should
                        scale text */

        /* Internal parameters of text rendering engine.
           Application code should not modify these parameters
        */
        int font_height; /*! Font height in pixels, parameter from svg */
        int last_x;      /*! Last x position of text element */
        int last_y;      /*! Last y position of text element */
        int last_dx;     /*! Horizontal width of text in pixels, for last text */
    } vg_lite_font_attributes_t;

  /* API Function prototypes ****************************************************/

    /*!
     @abstract Registers application specific font in vg_ltie driver.

     @discussion
     Using <code>vg_lite_register_font</code> application can register active
     fonts that <code>vg_lite_draw_text</code> uses to render text.

     for raster fonts mandatory fields of <code>vg_lite_font_params_t</code> are:
       name,
       font_weight, font_stretch, font_style, font_height
       data, data_len
     for vector fonts mandatory fields of <code>vg_lite_font_params_t</code> are:
       name,
       data, data_len

     On successful registeration <code>font</code> poiter will get non-negative
     application handle.

     @param font
     Pointer to font handle

     @param params
     Pointer to font parameters that are used by <code>vg_lite_find_font</code>
     to select specific font for rendering text

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
        VG_LITE_SUCCESS when font registation is success
        VG_LITE_INVALID_ARGUMENT When parameter pointer is invalid
        VG_LITE_ALREADY_EXISTS if font name already exists
        VG_LITE_OUT_OF_RESOURCES if active font exceeds MAX_SYSTEM_FONTS
     */
    vg_lite_error_t vg_lite_register_font(
                      vg_lite_font_t *font,
                      vg_lite_font_params_t *params);

    /*!
     @abstract Un-registers application specific font in vg_ltie driver.

     @discussion
     <code>vg_lite_unregister_font</code> unregisters application speciific
     font form vg_lite driver. This font can not be used lateron by
     <code>vg_lite_draw_text</code> API.

     @param font
     Pointer to font handle

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
        VG_LITE_SUCCESS when font registation is success
        VG_LITE_INVALID_ARGUMENT if font handle is invalid
     */
    vg_lite_error_t vg_lite_unregister_font(vg_lite_font_t font);


    /*!
     @abstract Check if given font is vector/raster ?

     @discussion
     <code>vg_lite_is_vector_font</code> API lookups active fonts in
     vg_lite driver and if font it found it return 1 if it points to vector font
     otherwise it return 0;

     @param font
     Pointer to font handle

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
        VG_LITE_SUCCESS when font registation is success
        VG_LITE_INVALID_ARGUMENT if font handle is invalid
     */
    int vg_lite_is_vector_font(vg_lite_font_t font);

    /*!
     @abstract This API renders text with specified font on render target.

     @discussion
     This API can reder text using user supplied font. Text rendering can be
     controlled by <code>vg_lite_font_attributes_t</code>.

     @param target
     Pointer to render target

     @param text
     ASCII text that needs to be rendered on render

     @param font
     Pointer to font handle

     @param x
     x position in pixels in X-axis for text rendering

     @param y
     y position in pixels in Y-axis for text rendering

     @param matrix
     Translation matrix that is used while rendering text.
     @attention Scaling and rotation matrix are not supported.

     @param blend
     Specifies how text gets blened in text area. Typical value is ELM_BLEND_SRC_OVER

     @param attributes
     Font attributes that controls how text gets rendered in render buffer.

     @result
     Returns the status as defined by <code>vg_lite_error_t</code>.
        VG_LITE_SUCCESS when font registation is success
        VG_LITE_INVALID_ARGUMENT if input parameters have any issue
     */
    vg_lite_error_t vg_lite_draw_text(
                      vg_lite_buffer_t *target,
                      char *text,
                      vg_lite_font_t font,
                      int x,
                      int y,
                      vg_lite_matrix_t *matrix,
                      vg_lite_blend_t blend,
                      vg_lite_font_attributes_t *attributes);

    /*!
     @abstract This API searches registered font for given name with
     requested rendering capabilities.

     @discussion
     This API searches registered font for given name with
     requested rendering capabilities.

     for raster fonts following fields are compared
       name,
       font_weight, font_stretch, font_style, font_height

     for vector fonts following fields are compared
       name

     @param font_name
     Font name

     @param font_weight
     Font weight value from eFontWeight_t

     @param font_stretch
     Font stretch value from eFontStretch_t

     @param font_style
     Font style value from eFontStyle_t

     @param font_height
     Font height in pixels

     If during font lookup a validate font is found then it retuns its handle.

     @result
     Returns valid font handle or an error code.
        Valid font handle if input parameters matches any of registerd font.
        INVALID_FONT if input parameters don't match registered fonts.
     */
    vg_lite_font_t vg_lite_find_font(
        char *font_name,
        eFontWeight_t  font_weight,
        eFontStretch_t font_stretch,
        eFontStyle_t   font_style,
        int font_height);

    /*!
     @abstract Initializes support for text drawing.
     */
    void vg_lite_text_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _vg_lite_text_h_ */
