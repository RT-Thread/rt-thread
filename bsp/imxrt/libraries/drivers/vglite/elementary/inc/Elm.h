/****************************************************************************
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

#ifndef ELM_H_
#define ELM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define     ELM_VERSION         0x00010000      /* Current Version: 1.0. */
#define     ELM_NULL_HANDLE     0   /*! NULL object handle, represent a void object. */

    /*!
     @typedef ELM_EVO_PROP_BIT
     evo property bits to control evo manipulation.
     */
    typedef enum {
        ELM_PROP_ROTATE_BIT    = 1 << 0,     /*! rotate bit of evo/ego/ebo transformation property. */
        ELM_PROP_TRANSFER_BIT  = 1 << 1,     /*! transfer bit of evo/ego/ebo transformation property. */
        ELM_PROP_SCALE_BIT     = 1 << 2,     /*! scale bit of evo/ego/ebo transformation property. */
        ELM_PROP_BLEND_BIT     = 1 << 3,     /*! blending bit of evo/ebo rendering property. */
        ELM_PROP_QUALITY_BIT   = 1 << 4,     /*! quality bit of evo/ebo rendering property. */
        ELM_PROP_FILL_BIT      = 1 << 5,     /*! fill rule bit of evo rendering property. */
        ELM_PROP_COLOR_BIT     = 1 << 6,     /*! fill color bit of evo rendering property. */
        ELM_PROP_PAINT_BIT     = 1 << 7,     /*! paint type bit of evo. */
        ELM_PROP_ALL_BIT       = 0xFFFFFFFF, /*! all transformation property bits of evo. */
    } ELM_EVO_PROP_BIT;

    /*!
     @typedef ELM_EVO_BLEND
     The blending property of the evo object when it's drawn.
     D is Destination color, S is Source color;
     Da is Destination alpha, S is Source alpha.
     */
    typedef enum {
        ELM_BLEND_NONE = 0,    /*! D = S. */
        ELM_BLEND_SRC_OVER,    /*! D = S + (1 - Sa) * D */
        ELM_BLEND_DST_OVER,    /*! D = (1 - Da) * S + D */
        ELM_BLEND_SRC_IN,      /*! D = Da * S */
        ELM_BLEND_DST_IN,      /*! D = Sa * D */
        ELM_BLEND_SCR,         /*! D = S + D - S * D */
        ELM_BLEND_MUL,         /*! D = S * (1 - Da) + D * (1 - Sa) + S * D */
        ELM_BLEND_ADD,         /*! S + D */
        ELM_BLEND_SUB          /*! D * (1 - S) */
    } ELM_BLEND;

    /*!
     @typedef ELM_EVO_QUALITY
     The drawing quality of the evo object.
     */
    typedef enum {
        ELM_QUALITY_LOW    = 0,       /*! NOAA for evo, POINT SAMPLE for ebo. */
        ELM_QUALITY_MED = 1,       /*! 2XAA for evo, LINEAR SAMPLE for ebo. */
        ELM_QULIATY_HI  = 2,       /*! 4XAA for evo, BI-LINEAR SAMPLE for ebo. */
    } ELM_QUALITY;

    /*!
     @typedef ELM_PAINT_TYPE
     Those are types for evo fill paint.
     COLOR means solid color fill;
     PATTERN means fill with an image (evo);
     GRADIENT means fill with linear gradient.
     */
    typedef enum {
        ELM_PAINT_COLOR    = 0,     /*! Paint evo with solid color */
        ELM_PAINT_PATTERN  = 1,     /*! Paint evo with ebo */
        ELM_PAINT_GRADIENT = 2,     /*! Paint evo with a linear gradient built-in evo object */
        ELM_PAINT_RADIAL_GRADIENT = 3, /*! Paint evo with a radial gradient built-in evo object */
        ELM_PAINT_TEXT     = 4,     /*! Paint evo-text */
    } ELM_PAINT_TYPE;

    /*!
     @typedef ELM_PATTERN_MODE
     Those are enum types for pattern fill mode.
     COLOR means fill the area outside the pattern with a solid color;
     PAD means extend the border color to the area outside the pattern.
     */
    typedef enum {
        ELM_PATTERN_MODE_COLOR  = 0,
        ELM_PATTERN_MODE_PAD    = 1,
    } ELM_PATTERN_MODE;

    /*!
     @typedef ELM_EVO_FILL
     The filling rule of for an evo object.
     EO = EVEN_ODD;
     NZ = NONE_ZERO;
     */
    typedef enum {
        ELM_EVO_FILL_NZ     = 0, /*! none-zero fill rule */
        ELM_EVO_FILL_EO        = 1, /*! Even-odd fill rule */
    } ELM_EVO_FILL;

    /*!
     @typedef ELM_EVO_TYPE
     the type of an evo object. could be pathes, images, or a group which contains other EVOs.
     */
    typedef enum {
        ELM_OBJECT_TYPE_EVO = 0,    /*! elementary vector object, representing a path object. */
        ELM_OBJECT_TYPE_EGO = 1,    /*! elementary group object, containing multiple path objects. */
        ELM_OBJECT_TYPE_EBO = 2,    /*! elementary bitmap object, representing image data. */
        ELM_OBJECT_TYPE_BUF = 3,    /*! rendering buffer object, created by application. */
        ELM_OBJECT_TYPE_FONT = 4,    /*! elementary font object, representing character data. */
        ELM_OBJECT_TYPE_TEXT = 5,    /*! elementary text object, representing text data. */
    } ELM_OBJECT_TYPE;

    /*!
     @typedef ELM_BUFFER_FORMAT
     Enumeration for buffer format, all format name definiton is sequenced from LSB to MSB.
     */
    typedef enum {
        ELM_BUFFER_FORMAT_RGBA8888,   /*! 32-bit RGBA format with 8 bits per color channel. Red is in bits 7:0, green in bits 15:8, blue in
                                            bits 23:16, and the alpha channel is in bits 31:24. */
        ELM_BUFFER_FORMAT_BGRA8888,   /*! 32-bit RGBA format with 8 bits per color channel. Red is in bits 23:16, green in bits 15:8, blue in
                                            bits 7:0, and the alpha channel is in bits 31:24. */
        ELM_BUFFER_FORMAT_RGBX8888,   /*! 32-bit RGBX format with 8 bits per color channel. Red is in bits 7:0, green in bits 15:8, blue in
                                            bits 23:16, and the x channel is in bits 31:24. */
        ELM_BUFFER_FORMAT_BGRX8888,   /*! 32-bit RGBX format with 8 bits per color channel. Red is in bits 23:16, green in bits 15:8, blue in
                                            bits 7:0, and the x channel is in bits 31:24. */
        ELM_BUFFER_FORMAT_RGB565,     /*! 16-bit RGB format with 5 and 6 bits per color channel. Red is in bits 4:0, green in bits 10:5, and
                                            the blue color channel is in bits 15:11. */
        ELM_BUFFER_FORMAT_BGR565,     /*! 16-bit RGB format with 5 and 6 bits per color channel. Red is in bits 15:11, green in bits 10:5,
                                            and the blue color channel is in bits 4:0. */
        ELM_BUFFER_FORMAT_RGBA4444,   /*! 16-bit RGBA format with 4 bits per color channel. Red is in bits 3:0, green in bits 7:4, blue in
                                            bits 11:8 and the alpha channel is in bits 15:12. */
        ELM_BUFFER_FORMAT_BGRA4444,   /*! 16-bit RGBA format with 4 bits per color channel. Red is in bits 11:8, green in bits 7:4, blue in
                                            bits 3:0 and the alpha channel is in bits 15:12. */
        ELM_BUFFER_FORMAT_BGRA5551,   /*! 16-bit RGBA format with 4 bits per color channel. Red is in bits 14:10, green in bits 9:5, blue in
                                            bits 4:0 and the alpha channel is in bit 15:15. */
        ELM_BUFFER_FORMAT_INDEX_1,    /*! 1-bit indexed format. */
        ELM_BUFFER_FORMAT_INDEX_2,    /*! 2-bits indexed format. */
        ELM_BUFFER_FORMAT_INDEX_4,    /*! 4-bits indexed format. */
        ELM_BUFFER_FORMAT_INDEX_8,    /*! 8-bits indexed format. */
    } ELM_BUFFER_FORMAT;

    /*!
     @typedef ElmHandle
     common handle type for object reference.
     */
    typedef unsigned int ElmHandle;

    /*!
     @typedef ElmVecObj
     evo object handle (elemtry vector object). Created from an external binary evo file.
    */
    typedef ElmHandle ElmVecObj;

    /*!
     @typedef ElmBitmapObj
     ebo object handle (elementry image object). Created from an external ebo file.
     */
    typedef ElmHandle ElmBitmapObj;

    /*!
     @typedef ElmGroupObj
     group object handle. Create from an external ego file.
     */
    typedef ElmHandle ElmGroupObj;

    /*!
     @typedef ElmBuffer
     render buffer object handle.
     */
    typedef ElmHandle ElmBuffer;

    #define TRUE  1
    #define FALSE 0
    /*!
     @typedef BOOL
     boolean type define.
     */
    typedef unsigned int  BOOL;

    /*!
     @abstract Initialize Elementary context.

     @discussion
     It should be called as the first function of Elemenatary libary, which initializes the library. Currently
     Elementary library doesn't support context concept, neigher multi-threading. Elementary library defines
     origin of coordinate system is at top-left.

     @param none

     @return none
     */
    BOOL ElmInitialize(uint32_t width, uint32_t height);

    /*!
     @abstract Terminate Elementary context.

     @discussion
     This should be called when an app exits. It frees all the resource.

     @param none

     @return none
     */
    void ElmTerminate(void);

    /*!
     @abstract Create an elementary object from an existing binary file.

     @discussion
     This function creates an elementary object from the file whose file name is specified by param name.
     Caller must match type with the binary file, otherwise create mail fail by returning ELM_NULL_HANDLE.

     @param type
     Specify what type of object to be created.

     @param name
     The name of the binary resource file.

     @return ElmHandle
     An object handle depending on the corresponding type. If type mismatches, it
     returns ELM_NULL_HANDLE.
     */
    ElmHandle ElmCreateObjectFromFile(ELM_OBJECT_TYPE type, const char *name);

    /*!
     @abstract Create an elementary object from build-in data within the appplication.

     @discussion
     This function creates an elementar object from local data pointer, which is specially useful for environment without filesystem support.

     @param type
     Specify what type of object to be created.

     @param data
     The pointer to the binary data which has exactly same layout as external resource file.

     @return ElmHandle
     An object handle depending on the corresponding type. If type mismatches with the binary data, it
     returns ELM_NULL_HANDLE.
     */
    ElmHandle ElmCreateObjectFromData(ELM_OBJECT_TYPE type, void *data, int size);

    /*!
     @abstract Rotate a graphics object with centain degree

     @discussion
     This function sets an evo/ebo/ego object rotated with specified angle. Without reset, these setting will be
     accumulated.

     @param obj
     The graphics object will be rotated.

     @param angle
     A radian value to be applied on the evo object.

     @return bool
     Rotate is set successfully.
     */
    BOOL ElmRotate(ElmHandle obj, float angle);

    /*!
     @abstract Transfer an graphics object at different directions.

     @discussion
     This function put an evo/ebo/ego object away at different directions. Without reset, the setting will be
     accumulated.

     @param obj
     The graphics object will be transfered.

     @param x
     The units in pixel of X direction.

     @param y
     The units in pixel of Y direction.

     @return bool
     Transfer is set successfully.
     */
    BOOL ElmTransfer(ElmHandle obj, int x, int y);

    /*!
     @abstract Scale an graphics object at different directions.

     @discussion
     This function scale up or down an evo/ego/ebo object at different directions. Without reset, the setting will
     be accumateled.

     @param obj
     The graphics object which is targeted to manipulate.

     @param x
     The scale ratio in X direction.

     @param y
     The scale ratio in Y direction.

     @return bool
     Scale is set succefully.
     */
    BOOL ElmScale(ElmHandle obj, float x, float y);

    /*!
     @abstract Reset the attribute of a graphics object for specified property bit.

     @discussion
     This funcion resets specified property for an elementary object. It can be applied all types of objects.
     But some properties are only valid for centain types of objects. If the function is called to reset an invalid
     property for this type of object, it will be siliently ignored.
     After reset, the specifed property of an evo/ebo/ego object is set to the initial state. The initial states are decided
     by the binary resource file. The resource creator should set right value for all properties if they want to directly render
     the object without any adjustment in application. There is one issue, at present, application has no way to query current value
     of each property, is it required?

     @param obj
     The graphics object which is targeted to manipulate.

     @param mask
     Specify which property or properties need to reset to initial value.

     @return bool
     Reset is done successfully. If some mask is not valid for this type of object, it would return false.
     */
    BOOL ElmReset(ElmHandle obj, ELM_EVO_PROP_BIT mask);

    /*!
     @abstract Draw a graphics object onto current render target

     @discussion
     This is an enssentail function to do the real job, it takes all current setting of the elementary object and
     render into theb buffer target.

     @param buffer
     The render target that an elmentary object will be rendered into.

     @param obj
     The elmentary object will be draw into render target.

     @return bool
     The draw operation for this elmentary object is sucessful.
     */
    BOOL ElmDraw(ElmBuffer buffer, ElmHandle object);

    /*!
     @abstract Set the rendering quality of an graphics object.

     @discussion
     This function sets the rendering quality of an evo/ebo object. Avaliable quality setting contains:
     ELM_EVO_QUALITY_LOW, ELM_EVO_QUALITY_MED, ELM_EVO_QUALITY_HI. This function is only applied to an evo or an ebo.
     Group object can't be set quality. It always use the setting from its binary.

     @param obj
     The elementary object.

     @param quality
     The quality enum.

     @return bool
     The operation for this object is sucessful, for group object and invalid enum, would return false.
     */
    BOOL ElmSetQuality(ElmHandle obj, ELM_QUALITY quality);

    /*!
     @abstract Set the fill rule of an evo object.

     @discussion
     This function sets the fill rule of an elementary object. Avaliable quality setting contains:
     ELM_EVO_EO, ELM_EVO_NZ. It only applies to evo object.

     @param evo
     The evo object.

     @param fill
     The fill rule enum.

     @return bool
     The operation for this evo is sucessful. For non-evo object an ENUM is not a valid enum, would return false.
     */
    BOOL ElmSetFill(ElmVecObj evo, ELM_EVO_FILL fill);

    /*!
     @abstract Set the blending mode of an evo/ebo object.

     @discussion
     This function sets the blending mode of an evo/ebo object. It's not applied to group object.

     @param obj
     The graphics object.

     @param blend
     The blending mode enum.

     @return bool
     The operation for this evo/ebo is sucessful. If object is a group object or blend mode is not a legal one, it would return false.
     */
    BOOL ElmSetBlend(ElmHandle obj, ELM_BLEND blend);

    /*!
     @abstract Set the solid fill color of an evo object.

     @discussion
     This function sets the solid fill color of an evo object.

     @param evo
     The evo object.

     @param color
     The uint32 color value in rgba order.

     @return bool
     The operation for this evo is sucessful. If the object is not a evo object, it would return false.
     */
    BOOL ElmSetColor(ElmVecObj evo, uint32_t color);

    /*!
     @abstract Set the image paint fill of an evo.

     @discussion
     This function sets the image pattern for filling an evo. The image pattern
     is a loaded ebo. The ebo's transformation is applied when drawing the evo.

     @param evo
     The evo object.

     @param pattern
     The image pattern to be set for the evo.

     @return bool
     The operation is successful or not.
     */
    BOOL ElmSetPattern(ElmVecObj evo, ElmBitmapObj pattern);

    /*!
     @abstract Set the image paint fill of an evo.

     @discussion
     This function sets the image pattern for filling an evo. The image pattern
     is a loaded ebo. The ebo's transformation is applied when drawing the evo.

     @param evo
     The evo object.

     @param pattern
     The image pattern to be set for the evo.

     @return bool
     The operation is successful or not.
     */
    BOOL ElmSetPatternMode(ElmVecObj evo, ELM_PATTERN_MODE mode, uint32_t color);

    /*!
     @abstract Set the paint type of an evo.

     @discussion
     This function selects the paint type for evo to use. An evo may have 3 types
     of paint: COLOR, PATTERN, and LINEAR GRADIENT. The Linear graident is always
     a built-in resource, which can not be altered. If a binary resource doesn't
     have built-in gradient paint resource, it can't be selected as the paint source.
     Solid color is also a built-in attribute, but it can be changed by ElmSetColor().
     Paint with a pattern always need an external ebo object, which is impossible
     to be embedded in resource file,i.e. ebo object. Before select paint type to
     be PATTERN, ElmSetPattern() must be called to attach an EBO to an EVO.

     @param evo
     The evo object.

     @param type
     The paint type to be set for the evo.

     @return bool
     The operation is successful or not.
     If the corresponding type is not avaiable for the evo, it returns false and
     type  paint type falls back to COLOR.
     */
    BOOL ElmSetPaintType(ElmVecObj evo, ELM_PAINT_TYPE type);

    /*!
     @abstract Create internal render buffer.

     @discussion
     This functiois is to create an internal render buffer for Elementary rendering, ussually it's not for direct display.
     The buffer which is displayed on pannel is wrapped up by another API, whose address is managed by display controller side.

     @param width
     The buffer's width.

     @param height
     The buffer's height.

     @param format
     The buffer's format, check enumeration of ELM_BUFFER_FORMAT.

     @return
     The buffer handle.
     */
    ElmBuffer ElmCreateBuffer(unsigned int width, unsigned int height, ELM_BUFFER_FORMAT format);

    /*!
    @abstract Wrap a customized buffer.

    @discussion
    The application may wrap a user created buffer by giving the information of
    the buffer including the size, the memory addresses and format. E.g., the
    application can wrap a system framebuffer thus ELM can directly render onto
     the screen.

    @return
    The buffer handle.
    */
    ElmBuffer ElmWrapBuffer(int width, int height, int stride,
                            void *logical, uint32_t physical,
                            ELM_BUFFER_FORMAT format);

    /*!
    @abstract Get buffer address.

    @discussion
    The function is to get the address of ElmBuffer.

    @return
    The buffer address.
    */

    uint32_t ElmGetBufferAddress(ElmBuffer buffer);

    /*!
     @abstract Destroy a render buffer.

     @discussion
     This function is to release all internal resource inside Elementary libary belonging to this buffer.
     Applicatoin need make sure the buffer is not being used by elmentary library any more when calling this function.

     @param buffer
     The render buffer handle

     @return
     If destroying is completed successfully.
     */
    BOOL ElmDestroyBuffer(ElmBuffer buffer);

    /*!
     @abstract Save a buffer to PNG file.

     @discussion
     This function can save the buffer into a PNG file.

     @param buffer
     The render buffer handle.

     @param name
     The name of the PNG file to sve.

     @return
     Save OK or NOT.

     */
    BOOL ElmSaveBuffer(ElmBuffer buffer, const char *name);

    /*!
     @abstract Clear a render buffer with specified color and dimension.

     @discussion
     This function is called to clear full or partial of the buffer. If the rectangle is out of buffer space, the intersect portion will be cleared.

     @param buffer
     A render buffer handle.

     @param color
     Clear color value.

     @param x
     x origin of partical clear rectangle.

     @param y
     y origin of partial clear rectangle.

     @param width
     width of partical clear rectangle.

     @param height
     height of partical clear rectangle.

     @param full
     Flag to indicate a full buffer clear. If true, the dimension parameters will be ignored.

     @return bool
     Indicate the clear operation is set up correctly.
    */
    BOOL ElmClear(ElmBuffer buffer, uint32_t color, uint32_t x, uint32_t y, uint32_t width, uint32_t height, BOOL full);

    /*!
     @abstract Destroy an ELM object.

     @discussion
     This function is to release all internal resource inside Elementary libary belonging to this object.
     Applicatoin need make sure the object is not being used by elmentary library any more when calling this function.
     If an EBO is being destroyed and it's attached to one EVO, it need to guarantee that EVO is not being used by elementary library too.

     @param object
     The object handle

     @return
     If destroying is completed successfully.
     */
    BOOL ElmDestroyObject(ElmHandle object);

     /*!
     @abstract Finish all rendering on GPU issued before this call.

     @discussion
     This function tells the engine that it has finished the frame data and GPU can draw it now. It's blocked until GPU rendering done.

     @return
     If the opeartion is successfully done or not.
     */
    BOOL ElmFinish();

    /*!
     @abstract Flush all rendering command to GPU issued before this call.

     @discussion
     This function tells the engine to start kicking off command to GPU side, it will return immediately after firing off GPU.

     @return
     If the opeartion is successfully done or not.
     */
    BOOL ElmFlush();

    /*!
     @abstract Query the paint color of an evo object.
     */
    BOOL ElmGetColor(ElmVecObj evoHandle,uint32_t *color);

    /*!
     @abstract Query the vectory path count of an EGO object. If the given object
     is an evo/ebo, the count is 0.
     */
    uint32_t ElmGetVectorCount(ElmHandle handle);

    /*!
     @abstract Query the type of an object (by handle).
     */
    ELM_OBJECT_TYPE ElmGetObjectType(ElmHandle handle);

    /*!
     @abstract Set the current vectory object index to operate on.
     */
    BOOL ElmSetCurrentVector(int32_t id);

    BOOL ElmScalePaint(ElmHandle handle, float sx, float sy);
    BOOL ElmRotatePaint(ElmHandle handle, float degrees);
    BOOL ElmTranslatePaint(ElmHandle handle, float tx, float ty);

    /*!
     @abstract Get handle of the framebuffer.
     */
    ElmBuffer ElmGetBuffer(vg_lite_buffer_t *buffer);

#ifdef __cplusplus
}
#endif
#endif /* ELM_H_ */
