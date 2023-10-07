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

#ifndef VELM_H_
#define VELM_H_

#ifdef __cplusplus
extern "C" {
#endif
    /*
     */
#define VERSION     0x00000001
#define SLOT_COUNT  256/*16*/
#define OBJECT_SLOT(id) \
    elm_tls->gContext.object_slots[id % SLOT_COUNT]

    /*
     VGLite releated configurations.
     */
#define TS_WIDTH    64
#define TS_HEIGHT   64
#define RTOS 1
#define APP_BUFFER_COUNT 2
#if (RTOS && DDRLESS) || BAREMETAL
#define OBJCOUNT_GRAD    16
#define    OBJCOUNT_EVO    128
#define OBJCOUNT_EBO    64
#define OBJCOUNT_GROUP    16
#endif

#if RTOS

#include "rtthread.h"

#define elm_alloc(num_objects, object_size) rt_malloc(num_objects * object_size)
#define elm_free  rt_free
#else
#define elm_alloc calloc
#define elm_free  free
#endif

typedef enum {
    ELEMENT_LINEARGRADIENT      = 0,        /*! linear gradient element */
    ELEMENT_PATH                = 1,        /*! path element */
    ELEMENT_GROUP               = 2,        /*! group element */
    ELEMENT_TEXT                = 3,        /*! text element */
    ELEMENT_TSPAN               = 4,        /*! tspan element */
    ELEMENT_FONT                = 5,        /*! font element */
    ELEMENT_TTF_FONT            = 6,        /*! ttf-type font */
    ELEMENT_VECTOR_FONT         = 7,        /*! vector fonts */
    ELEMENT_TEXT_FONT           = 8,        /*! text fonts */
} ELM_ELEMENT_TYPE;

#define COUNT_OF(array) (sizeof(array) / sizeof(array[0]))
    /*
     System definitions.
     */
#define DEBUG_ASSERT(a, message) \
    if (!a)             \
        printf("%s: ASSERT failed @ %s, %d.\n", message, __FILE__, __LINE__)

    /*!
     @typedef el_Object
     common object type definition shared by all EVO object to identify its handle,
     object type, and ELM version info.
     for reference purpose, handle = 0 is reserved.
     */
    typedef struct {
        ElmHandle           handle;
        ELM_OBJECT_TYPE     type;
        unsigned int        reference;  // Reference count by other objects.
#if (RTOS && DDRLESS) || BAREMETAL
        int                 index;        /* The index of the object in pool. */
#endif
    } el_Object;

    /*!
     @typedef el_Transform
     The transformation attribute for an EVO/EBO/Group object.
     */
    typedef struct {
        float               rotate;
        float               translate[2];
        float               scale[2];
        BOOL                dirty;
        BOOL                identity;
        vg_lite_matrix_t    matrix;
    } el_Transform;

    /*!
     @typedef el_GradData
     Linear gradient definition.
     !grad  the native vg_lite gradient data;
     !gransform the grad's transformation. matrix is synced to grad's.
     */
    typedef struct {
        vg_lite_linear_gradient_t   grad;
        el_Transform                transform;
    } el_GradData;

    /*!
     @typedef el_RadgradData
     Radial gradient definition.
     !rad_grad  the native vg_lite_radial_gradient data;
     !gransform the grad's transformation. matrix is synced to grad's.
     */
    typedef struct {
        vg_lite_radial_gradient_t   rad_grad;
        el_Transform                transform;
    } el_RadgradData;

    /*!
     @typedef el_Obj_Grad
     The linear gradient object definition.
     */
    typedef struct {
        el_Object           object;
        el_GradData         data;
    } el_Obj_Grad;

    /*!
     @typedef el_Obj_Radgrad
     The radial gradient object definition.
     */
    typedef struct {
        el_Object           object;
        el_RadgradData         data;
    } el_Obj_Radgrad;

    /*!
     @typedef el_Obj_Pattern
     The pattern paint object definition.
     pattern:   it should be an pointer to an el_Obj_EVO;
     mode:      the pattern fill mode.
     color:     the color value if pattern mode is COLOR
     */
    typedef struct {
        void               *pattern;
        ELM_PATTERN_MODE    mode;
        uint32_t            color;
    } el_Obj_Pattern;

    /*!
     @typedef el_Paint
     The paint object definition.
     color:   for solid fill;
     grad:    for linear gradient fill;
     pattern: for image fill.
     */
    typedef struct {
        ELM_PAINT_TYPE      type;
        uint32_t            color;
        el_Obj_Grad *       grad;
        el_Obj_Radgrad *    radgrad;
        el_Obj_Pattern      pattern;
    } el_Paint;

    /*!
     @typedef el_Attribute
     The rendering attribute definition.
     */
    typedef struct {
        ELM_QUALITY         quality;
        ELM_BLEND           blend;
        ELM_EVO_FILL        fill_rule;
        el_Paint            paint;
        el_Transform        transform;
    } el_Attribute;

    /*!
     @typedef el_EVOData
     The data definition for EVO (vector object).
     */
    typedef struct {
        vg_lite_path_t      path;
    } el_EVOData;

    /*!
     @typedef el_Obj_EVO
     EVO (Elementry Vector Object) type definition.
     */
    typedef struct {
        el_Object           object;
        el_Attribute        attribute;
        el_Attribute        defaultAttrib;
        el_EVOData          data;
        uint32_t            has_pattern;
        uint32_t            is_pattern;
        uint32_t            is_image;
        char                eboname[20];
        uint32_t            img_width;
        uint32_t            img_height;
    } el_Obj_EVO;

    /*!
     @typedef el_EBOData
     The data definition for EBO (bitmap object).
     */
    typedef struct {
        vg_lite_buffer_t    buffer;
    } el_EBOData;

    /*!
     @typedef el_Obj_EBO
     EBO (Elementry Buffer Object) type definition.
     */
    typedef struct {
        el_Object           object;
        el_Attribute        attribute;
        el_Attribute        defaultAttrib;
        el_EBOData          data;
        uint32_t            clut_count;
        uint32_t            clut[256];
    } el_Obj_EBO;

    /*!
     @typedef el_GroupData
     The group object data definition.
     */
    typedef struct {
        unsigned int        count;
        el_Obj_EVO *        objects;
    } el_GroupData;

    /*!
     @typedef el_Obj_Group
     Group object type definition.
     */
    typedef struct {
        el_Object           object;
        el_Transform        transform;
        el_Transform        defaultTrans;
        el_GroupData        group;
    } el_Obj_Group;

    /*!
     @typedef el_Obj_Buffer
     The render buffer object definition.
     */
    typedef struct {
        el_Object           object;
        vg_lite_buffer_t    buffer;
    } el_Obj_Buffer;

    /*!
     @typedef el_ObjList
     List to organize objects.
     */
    typedef struct _object_list{
        el_Object           *object;
        struct _object_list *next;
    } el_ObjList;

    /*!
     @typedef ElmRenderBuffer
     The ElmRenderBuffer definition.
     */
    typedef struct elm_render_buffer {
        ElmBuffer        handle;
        vg_lite_buffer_t *buffer;
    } ElmRenderBuffer;

    /*!
     @typedef el_Context
     The context object for global data management.
     !version           UXDK version
     !currentHandle     The current handle for new object
     !objectCount       Count of all objects
     !object_slots      List array to manage objects
     */
    typedef struct {
        uint32_t            version;
        int                 reference;
        ElmHandle           currentHandle;
        unsigned int        objectCount;
        el_ObjList         *object_slots[SLOT_COUNT];
        ElmRenderBuffer     elmFB[APP_BUFFER_COUNT];
        /* VGLite related states. */
        uint32_t            tessellation_width;
        uint32_t            tessellation_height;

        /* The current vector index (within a group). */
        int32_t             vector_id;

#if (RTOS && DDRLESS) || BAREMETAL
        /* Static object pools. */
        el_Obj_Grad        objpool_grad[OBJCOUNT_GRAD];
        el_Obj_EVO        objpool_evo[OBJCOUNT_EVO];
        el_Obj_EBO        objpool_ebo[OBJCOUNT_EBO];
        el_Obj_Group    objpool_group[OBJCOUNT_GROUP];

        /* The allocation map table.
         * Each bit in the element maps to the usage of the object.
         * 0 means free, 1 means allocated.
         * The mapping order is 01234567...31 (hi -> low) in big endian systems.
         * */
        int32_t        objmap_grad[(OBJCOUNT_GRAD + 31) / 32];
        int32_t        objmap_evo[(OBJCOUNT_EVO + 31) / 32];
        int32_t        objmap_ebo[(OBJCOUNT_EBO + 31) / 32];
        int32_t        objmap_group[(OBJCOUNT_GROUP + 31) / 32];

        int        objcounter_grad;
        int        objcounter_evo;
        int        objcounter_ebo;
        int        objcounter_group;
#endif
    } el_Context;

    /*!
     @typedef elm_tls_t
     The elm_tls_t definition.
     */
    typedef struct vglite_elm_tls {
        el_Context gContext;
    } elm_tls_t;

    /*
     API function prototypes.
     */
    int         add_object      (el_Object     *object);
    int         remove_object   (el_Object     *object);
    el_Object  *get_object      (ElmHandle      handle);

#ifdef __cplusplus
}
#endif
#endif /* VELM_H_ */
