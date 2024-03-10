/****************************************************************************
*
*    Copyright 2012 - 2021 Vivante Corporation, Santa Clara, California.
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

#include "elm_precom.h"
#include "elm_os.h"
#include "vg_lite_text.h"
#include "vft_debug.h"
#include "elm_headers.h"

#if (VG_RENDER_TEXT==1)
#include "elm_text.h"
#endif /* VG_RENDER_TEXT */

#if RTOS
#define BASE_ADDRESS_ALIGNMENT 32
#else
#define BASE_ADDRESS_ALIGNMENT 4
# endif
/* #define ENABLE_ELM_CRATE_OBJECT_FROM_FILE */

/*
 * ANSI APIs are missing so application can use ElmCreateObjectFromData
 * This simplifies things since file can be from FATFS, NOR Flash buffer etc.
 */

#if (RTOS && DDRLESS) || BAREMETAL
/* Find some free objects, return the first index,
 * and mark the bits as 1 (allocated).
 * Params:
 * free_map: the map bits of the objects where 0 is free and 1 is allocated;
 * count   : the element count of free_map[];
 * obj_count:how many objects to allocate from the pool.
 *
 * Return:
 *  The free index of the object in the pool.
 * */
int get_free_objects(int32_t free_map[], int count, int obj_count)
{
    int i, j;
    int result = -1;
    int counter = 0;
    int bit_count = 0;
    int32_t bits;

    /* Find a free bit. */
    for (i = 0; i < count; i++) {
        bits = free_map[i];

        for (j = 0; j < 32; j++) {
            //Increase the bit counter.
            bit_count++;

            if ((bits & 0x80000000) == 0) {
                //Free bit is found. then count available free bits.
                counter++;
            }
            else {
                //Free bit is not found, reset the counter.
                counter = 0;
            }

            //Check to see whether enough bits are found.
            if (counter >= obj_count) {
                result = bit_count - counter;

                //Get out of the two loops.
                i = count;
                break;
            }

            //Shift to next bit.
            bits <<= 1;
        }
    }

    /* Mark the bits as allocated if OK. */
    if (result > -1) {
        int bits_set = 1;
        int bit_offset = result % 32;
        bit_count = result / 32;

        while (obj_count > 0) {
            bits_set = ~(0xffffffff << (32 - bit_offset));
            if (obj_count <= 32 - bit_offset) {
                //Done.
                bits_set = bits_set & (0xffffffff << (32 - bit_offset - obj_count));
                free_map[bit_count] |= bits_set;
                break;
            }
            free_map[bit_count] |= bits_set;

            //Go to next map element.
            obj_count -= (32 - bit_offset);
            bit_count++;
            bit_offset = 0;
        }
    }

    return result;
}

/* When an object is "freed", mark the corresponding bits to 0. */
void mark_free_object(int32_t free_map[], int object)
{
    int index, offset;

    index = object / 32;
    offset = object % 32;

    free_map[index] &= ~(1 << (31 - offset));
}

/* Check whether an object (with given index) allocated or not. */
int object_exists(int32_t free_map[], int index)
{
    int32_t bits;
    int offset = index % 32;
    index /= 32;

    bits = ~(1 << (31 - offset));

    if (free_map[index] & bits) {
        return 1;
    }
    else {
        return 0;
    }
}

/* Allocate an EVO object from pool. */
static el_Obj_EVO * alloc_evo(int count)
{
    elm_tls_t* elm_tls;
    int index;
    el_Obj_EVO *object = NULL;

    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return NULL;

    index = get_free_objects(elm_tls->gContext.objmap_evo, COUNT_OF(elm_tls->gContext.objmap_evo), count);

    if (index > -1) {
        object = &elm_tls->gContext.objpool_evo[index];
        elm_tls->gContext.objcounter_evo += count;
        for (; count > 0; count--) {
            object[count - 1].object.index = index + count - 1;
        }
    }

    return object;
}

/* Allocate an EBO object from pool. */
static el_Obj_EBO * alloc_ebo()
{
    elm_tls_t* elm_tls;
    int index;
    el_Obj_EBO *object = NULL;

    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return NULL;

    index = get_free_objects(elm_tls->gContext.objmap_ebo, COUNT_OF(elm_tls->gContext.objmap_ebo), 1);

    if (index > -1) {
        object = &elm_tls->gContext.objpool_ebo[index];
        object->object.index = index;
        elm_tls->gContext.objcounter_ebo++;
    }

    return object;
}

/* Allocate an EGO object from pool. */
static el_Obj_Group * alloc_ego()
{
    elm_tls_t* elm_tls;
    int index;
    el_Obj_Group *object = NULL;

    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return NULL;

    index = get_free_objects(elm_tls->gContext.objmap_group, COUNT_OF(elm_tls->gContext.objmap_group), 1);

    if (index > -1) {
        object = &elm_tls->gContext.objpool_group[index];
        object->object.index = index;
        elm_tls->gContext.objcounter_group++;
    }

    return object;
}

/* Mark an EGO object as free: insert it into the free list. */
static void free_ego(el_Obj_Group *object)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return NULL;

    mark_free_object(elm_tls->gContext.objmap_group, elm_tls->object->object.index);
    elm_tls->gContext.objcounter_group--;
}

/* Allocate a grad object from pool. */
static el_Obj_Grad * alloc_grad()
{
    elm_tls_t* elm_tls;
    int index;
    el_Obj_Grad *object = NULL;

    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return NULL;

    index = get_free_objects(elm_tls->gContext.objmap_grad, COUNT_OF(elm_tls->gContext.objmap_grad), 1);

    if (index > -1) {
        object = &elm_tls->gContext.objpool_grad[index];
        object->object.index = index;
        elm_tls->gContext.objcounter_grad++;
    }

    return object;
}

#endif
/* Internal Implementations *******************************/
int deref_object(el_Object *object)
{
    object->reference--;
    return object->reference;
}

int ref_object(el_Object *object)
{
    object->reference++;
    return object->reference;
}

int add_object(el_Object *object)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return 0;
#if (RTOS && DDRLESS) || BAREMETAL
    /* Assign handle. */
    object->handle = elm_tls->gContext.currentHandle++;
    return 1;
#else
    int result = 1;
    el_ObjList *list = NULL;

    /* Assign handle. */
    object->handle = elm_tls->gContext.currentHandle++;

    /* Get the list slot. */
    list = OBJECT_SLOT(object->handle);
    if (list == NULL) {
        list = (el_ObjList *) elm_alloc(1, sizeof(el_ObjList));
        if ( list == NULL ) {
            return 0; /* Memory allocation failed */
        }
#ifdef ENABLE_STRICT_DEBUG_MEMSET
        memset(list, 0, sizeof(el_ObjList));
#endif

        OBJECT_SLOT(object->handle) = list;

        list->object = object;
        list->next   = NULL;

        return 1;
    }

    /* Insert the object. */
    while (list->next != NULL) {
        list = list->next;
    }
    list->next = (el_ObjList *) elm_alloc(1, sizeof(el_ObjList));
    if ( list->next == NULL ) {
        return 0; /* Memory allocation failed */
    }
#ifdef ENABLE_STRICT_DEBUG_MEMSET
    memset(list->next, 0, sizeof(el_ObjList));
#endif
    list = list->next;
    list->object = object;
    list->next = NULL;

    return result;
#endif
}

int remove_object(el_Object *object)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return 0;

    int result = 0;
#if (!(RTOS && DDRLESS)) && (!BAREMETAL)
    el_ObjList *list = NULL, *node = NULL;

    // Get the list slot.
    list = OBJECT_SLOT(object->handle);

    // Invalid.
    if (list == NULL)
        return 0;

    // Find the object.
    if (list->object == object) {
        OBJECT_SLOT(object->handle) = list->next;
        elm_free(list);
        return 1;
    }

    while (list->next != NULL) {
        if (list->next->object == object) {
            node = list->next;
            list->next = list->next->next;
            elm_free(node);
            return 1;
        }
        list = list->next;
    }
#endif

    return result;
}

el_Object *get_object(ElmHandle handle)
{
    elm_tls_t* elm_tls;
    el_Object *object = NULL;

    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return NULL;

#if (RTOS && DDRLESS) || BAREMETAL
    int i;
    for (i = 0; i < OBJCOUNT_EVO; i++) {
        if (object_exists(elm_tls->gContext.objmap_evo, i)) {
            if (elm_tls->gContext.objpool_evo[i].object.handle == handle) {
                object = (el_Object *)&elm_tls->gContext.objpool_evo[i];
                return object;
            }
        }
    }
    for (i = 0; i < OBJCOUNT_EBO; i++) {
        if (object_exists(elm_tls->gContext.objmap_ebo, i)) {
            if (elm_tls->gContext.objpool_ebo[i].object.handle == handle) {
                object = (el_Object *)&elm_tls->gContext.objpool_ebo[i];
                return object;
            }
        }
    }
    for (i = 0; i < OBJCOUNT_GRAD; i++) {
        if (object_exists(elm_tls->gContext.objmap_grad, i)) {
            if (elm_tls->gContext.objpool_grad[i].object.handle == handle) {
                object = (el_Object *)&elm_tls->gContext.objpool_grad[i];
                return object;
            }
        }
    }
    for (i = 0; i < OBJCOUNT_GROUP; i++) {
        if (object_exists(elm_tls->gContext.objmap_group, i)) {
            if (elm_tls->gContext.objpool_group[i].object.handle == handle) {
                object = (el_Object *)&elm_tls->gContext.objpool_group[i];
                return object;
            }
        }
    }
#else
    el_ObjList *list = NULL;

    // Get the slot.
    list = OBJECT_SLOT(handle);

    // Find the object.
    while (list != NULL) {
        if ((list->object != NULL) &&
            (list->object->handle == handle)) {
            object = list->object;
            return object;
        }
        list = list->next;
    }
#endif

    DEBUG_ASSERT(0, "Unknown object");
    return NULL;
}

#if (RTOS && DDRLESS) || BAREMETAL
static void free_grad(el_Obj_Grad *object)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls != NULL) {
        mark_free_object(elm_tls->gContext.objmap_grad, object->object.index);
        elm_tls->gContext.objcounter_grad--;
    }
}
#endif

/* Destroy an evo object data. */
int destroy_evo(el_Obj_EVO *evo)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return 0;

#if (RTOS && DDRLESS) || BAREMETAL
    mark_free_object(elm_tls->gContext.objmap_evo, evo->object.index);
    elm_tls->gContext.objcounter_evo--;
    free_grad(evo->defaultAttrib.paint.grad);
#else

    if ( evo->defaultAttrib.paint.type == ELM_PAINT_TEXT ) {
#if (VG_RENDER_TEXT==1)
        _unload_text(evo);
#else
       ;
#endif /* VG_RENDER_TEXT */
    } else {
    /* TODO: EVO destroy not done yet. */
    if (evo->defaultAttrib.paint.grad != NULL) {
        vg_lite_clear_grad(&evo->defaultAttrib.paint.grad->data.grad);
        elm_free(evo->defaultAttrib.paint.grad);
        evo->defaultAttrib.paint.grad = NULL;
    }

    if (evo->data.path.path != NULL) {
        vg_lite_clear_path(&evo->data.path);
        elm_free(evo->data.path.path);
        evo->data.path.path = NULL;
    }
    }

    remove_object(&evo->object);
#endif

#if (VG_RENDER_TEXT==1)
    destroy_font_data();
#endif /* VG_RENDER_TEXT */
    return 1;
}

/* Destroy an ego object data. */
int destroy_ego(el_Obj_Group *ego)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if(elm_tls == NULL)
        return 0;

#if (RTOS && DDRLESS) || BAREMETAL
    mark_free_object(elm_tls->gContext.objmap_group, ego->object.index);
    elm_tls->gContext.objcounter_group--;
#else
    int i;
    for (i = 0; i < ego->group.count; i++)
    {
        destroy_evo(&ego->group.objects[i]);
    }
    elm_free(ego->group.objects);
    elm_free(ego);
#endif

#if (VG_RENDER_TEXT==1)
    destroy_font_data();
#endif /* VG_RENDER_TEXT */
    return 1;
}

/* Destroy an ebo object data. */
int destroy_ebo(el_Obj_EBO *ebo)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if(elm_tls == NULL)
        return 0;

#if (RTOS && DDRLESS) || BAREMETAL
    mark_free_object(elm_tls->gContext.objmap_ebo, ebo->object.index);
    elm_tls->gContext.objcounter_ebo--;
#else
    if ( ebo != NULL && ebo->data.buffer.handle != NULL) {
        vg_lite_free(&ebo->data.buffer);
    }
    elm_free(ebo);
#endif
    return 1;
}

/* Destroy an object.
 return:
 -1: any error;
  0: destroyed when reference count is 0;
  1: decreased reference count but still > 0.
 */
int destroy_object(ElmHandle handle)
{
    el_Object *object = NULL;
    int ref_count = 0;

    object = get_object(handle);

    // No such object.
    if (object == NULL) {
        DEBUG_ASSERT(0, "No such object");
        return -1;
    }

    // Dereference object, and destroy if it's no more referred.
    ref_count = deref_object(object);
    if (ref_count == 0) {
        remove_object(object);

        switch (object->type) {
            case ELM_OBJECT_TYPE_EVO:
                destroy_evo((el_Obj_EVO *)object);
                elm_free(object);
                break;

            case ELM_OBJECT_TYPE_EGO:
                destroy_ego((el_Obj_Group *) object);
                break;

            case ELM_OBJECT_TYPE_EBO:
                destroy_ebo((el_Obj_EBO *) object);
                break;

            default:
                DEBUG_ASSERT(0, "Unknow object type");
                break;
        }
    }

    return 1;
}

void _init_transform(el_Transform *transform)
{
    int i = 0;
    transform->rotate = 0.0f;
    for (i = 0;i < 2; i++)
    {
        transform->scale[i] = 1.0f;
        transform->translate[i] = 0.0f;
    }
    vg_lite_identity(&transform->matrix);
}

/* Static functions. *************************************************/

/* Get the specified vector object in a group. */
static el_Obj_EVO* _get_evo(el_Obj_Group *group, int32_t id)
{
    if ((id >= group->group.count) ||
        (id < 0)){
        return (el_Obj_EVO*)NULL;
    }
    else {
        return (el_Obj_EVO*)(group->group.objects + id);
    }
}

#if (VG_RENDER_TEXT==1)
static int _load_font(uint8_t *data,
                      unsigned size)
{
    ElmHandle ret = ELM_NULL_HANDLE;
    el_Font_Header *font_header = (el_Font_Header *)data;


    if (font_header->size_font_block != size)
        return ret;

    return _load_font_data(data);
}

static ElmHandle _load_text(uint8_t *data,
                            unsigned size,
                            el_Obj_EVO *evo)
{
    ElmHandle ret = ELM_NULL_HANDLE;
    el_Text_Header *text_header = (el_Text_Header *)data;


    if (text_header->size_text_block != size)
        return ret;

    return _load_text_data(data, evo);
}
#endif /* VG_RENDER_TEXT */

#if (defined(__ICCARM__))
/*
 * Disable the unaligned structure attribute warning. Due to the packed data
 * structures used to interpret ELM objects data the IAR compiler issues a
 * number of warnings that certain attributes of the headers might be unaligned.
 * This is not true, however, as all atributes are manually aligned to 4 bytes.
 */
#pragma diag_suppress = Pa039
#endif

static ElmHandle _load_evo(const uint8_t *data, unsigned size, el_Obj_EVO *evo)
{
    int i = 0;
#if (RTOS && DDRLESS) || BAREMETAL
    uint32_t colors[VLC_MAX_GRAD];
    void *path_data;
#else
    uint32_t *colors = NULL;
    uint8_t *path_data = NULL;
#endif
    el_Obj_EVO *local_evo = NULL;
    el_EVO_Header *evo_header = (el_EVO_Header *) data;

    if (evo == NULL) {
#if (RTOS && DDRLESS) || BAREMETAL
        local_evo = alloc_evo(1);
#else
        local_evo = (el_Obj_EVO *)elm_alloc(1, sizeof(el_Obj_EVO));
#endif
        evo = local_evo;
    }
    JUMP_IF_NULL(evo, error_exit);
    memset(evo, 0, sizeof(el_Obj_EVO));

    /*
     * Check if object size is valid. The size parameter
     * needs to be a value greater or equal to the
     * size of the current object to be loaded.
     * This check needs to be done in order to ensure
     * that the is_image field is correctly read and
     * we do not read from invalid memory.
     */
    JUMP_IF_LOWER(size,
                  MIN(sizeof(el_EVO_Polygon), sizeof(el_EVO_Image)),
                  error_exit);

    if(evo_header->polygon.paint_type.is_image)
    {
        /*
         * Check if object size is valid
         * (greater or equal to el_EVO_Image size).
         */
        JUMP_IF_LOWER(size,
                      sizeof(el_EVO_Image),
                      error_exit);
        memcpy(evo->eboname,
               evo_header->image.eboname,
               evo_header->image.namelength);
        evo->is_image = evo_header->image.paint_type.is_image;
        _init_transform(&evo->defaultAttrib.transform);
        memcpy(&evo->defaultAttrib.transform.matrix,
               &(evo_header->image.matrix),
               sizeof(vg_lite_matrix_t));
        evo->img_width = evo_header->image.width;
        evo->img_height = evo_header->image.height;
    }
    else
    {
        /*
         * Check if object size is valid
         * (greater or equal to el_EVO_Polygon size).
         */
        JUMP_IF_LOWER(size,
                      sizeof(el_EVO_Polygon),
                      error_exit);
        el_Transform *transform = NULL;
        el_Transform *grad_transform = NULL;
        el_EVO_Polygon *object_data = (el_EVO_Polygon *) &(evo_header->polygon);
        el_EVO_GradData *grad_data = (el_EVO_GradData *) &(evo_header->polygon.grad);

        /* Get path data from the object. */
#if (RTOS && DDRLESS) || BAREMETAL
        path_data = (void *) (data + object_data->offset);
#else
        path_data = (uint8_t *)elm_alloc(1, object_data->length);
        JUMP_IF_NULL(path_data, error_exit);

#ifdef ENABLE_STRICT_DEBUG_MEMSET
        memset(path_data, 0, object_data->length);
#endif
        JUMP_IF_LOWER(size,
                      object_data->offset + object_data->length,
                      error_exit);
        /* Get path data. */
        memcpy(path_data, (void *)(data + object_data->offset),
               object_data->length);
#endif

        if(object_data->paint_type.has_pattern)
            evo->has_pattern = 1;
        if(object_data->paint_type.is_pattern)
            evo->is_pattern = 1;

        _init_transform(&evo->defaultAttrib.transform);
        transform = &evo->defaultAttrib.transform;

        evo->object.type = ELM_OBJECT_TYPE_EVO;
        evo->object.reference = 0;

        if ((object_data->paint_type.paint == ELM_PAINT_RADIAL_GRADIENT) ||
            (object_data->paint_type.paint == ELM_PAINT_GRADIENT)) {
#if (RTOS && DDRLESS) || BAREMETAL
            evo->defaultAttrib.paint.grad = alloc_grad();
#else
            evo->defaultAttrib.paint.grad = (el_Obj_Grad*)elm_alloc(1, sizeof(el_Obj_Grad));
#endif
            JUMP_IF_NULL(evo->defaultAttrib.paint.grad, error_exit);
#ifdef ENABLE_STRICT_DEBUG_MEMSET
            memset(evo->defaultAttrib.paint.grad, 0, sizeof(el_Obj_Grad));
#endif
            evo->defaultAttrib.paint.grad->data.grad.image.width = 0;
            evo->defaultAttrib.paint.grad->data.grad.image.height = 0;
            evo->defaultAttrib.paint.grad->data.grad.image.stride = 0;
            evo->defaultAttrib.paint.grad->data.grad.image.tiled = VG_LITE_LINEAR;

            _init_transform(&evo->defaultAttrib.paint.grad->data.transform);
            grad_transform = &evo->defaultAttrib.paint.grad->data.transform;
            memcpy(&grad_transform->matrix, &(grad_data->matrix),
                   sizeof(vg_lite_matrix_t));
            colors = (uint32_t *)elm_alloc(grad_data->stop_count, sizeof(uint32_t));
            JUMP_IF_NULL(colors, error_exit);
            memcpy(colors,
                   data + grad_data->color_offset,
                   grad_data->stop_count * sizeof(uint32_t));
        }

        if (object_data->arc_flag)
           vg_lite_init_arc_path(&evo->data.path,
                                 (vg_lite_format_t) object_data->format,
                                 (vg_lite_quality_t) object_data->quality,
                                 object_data->length,
                                 path_data,
                                 object_data->min_x,
                                 object_data->min_y,
                                 object_data->max_x,
                                 object_data->max_y);
        else
          vg_lite_init_path(&evo->data.path,
                            (vg_lite_format_t) object_data->format,
                            (vg_lite_quality_t) object_data->quality,
                            object_data->length,
                            path_data,
                            object_data->min_x,
                            object_data->min_y,
                            object_data->max_x,
                            object_data->max_y);

        memcpy(&transform->matrix, &(object_data->matrix), sizeof(vg_lite_matrix_t));

        evo->defaultAttrib.quality      = ELM_QUALITY_LOW;
        evo->defaultAttrib.fill_rule    = (ELM_EVO_FILL) object_data->fill_rule;
        evo->defaultAttrib.blend        = (ELM_BLEND) object_data->blend;
        evo->defaultAttrib.paint.type   = (ELM_PAINT_TYPE) object_data->paint_type.paint;

        switch (object_data->paint_type.paint) {
        case ELM_PAINT_GRADIENT:
        {
#if (RTOS && DDRLESS) || BAREMETAL
            uint32_t stops[VLC_MAX_GRAD];
#else
            uint32_t *stops = NULL;

            stops = (uint32_t *)elm_alloc(sizeof(uint32_t), grad_data->stop_count);
            JUMP_IF_NULL(stops, error_exit);
#endif
            for (i = 0 ;i < grad_data->stop_count; i++)
            {
                stops[i] = (uint32_t)((*(float *) (data +
                           grad_data->stop_offset + i * 4)) * 255);
            }

            vg_lite_init_grad(&evo->defaultAttrib.paint.grad->data.grad);
            vg_lite_set_grad(&evo->defaultAttrib.paint.grad->data.grad,
                             grad_data->stop_count, colors, stops);
            if (grad_data->stop_count > 0)
            {
                vg_lite_update_grad(&evo->defaultAttrib.paint.grad->data.grad);
            }
#if (RTOS && DDRLESS) || BAREMETAL
#else
            elm_free(stops);
#endif
            break;
        }
        case ELM_PAINT_RADIAL_GRADIENT:
        {
            float *stops;
            vg_lite_color_ramp_t *vgColorRamp;
            el_EVO_RadGradDataExt *rad_grad = (el_EVO_RadGradDataExt *) (data + sizeof(el_EVO_Header));

            JUMP_IF_LOWER(size,
                          sizeof(el_EVO_Polygon) + sizeof(el_EVO_RadGradDataExt),
                          error_exit);

            stops = (float *)elm_alloc(grad_data->stop_count, sizeof(float));
            JUMP_IF_NULL(stops, error_exit);
            memset(stops, 0, grad_data->stop_count * sizeof(float));
            vgColorRamp = (vg_lite_color_ramp_t *) elm_alloc(grad_data->stop_count,
                           sizeof(vg_lite_color_ramp_t));
            if (vgColorRamp == NULL) {
                elm_free(stops);
                goto error_exit;
            }
            memset(vgColorRamp, 0,
                   sizeof(vg_lite_color_ramp_t) * grad_data->stop_count);
            for (i = 0; i < grad_data->stop_count; i++)
            {
                stops[i] = (*(float *) (data + grad_data->stop_offset + i * 4));
                vgColorRamp[i].alpha = (float)(colors[i] >> 24) / 255.0f;
                vgColorRamp[i].red = (float)(colors[i] >> 16 & 0xFF) / 255.0f;
                vgColorRamp[i].green = (float)(colors[i] >> 8 & 0xFF) / 255.0f;
                vgColorRamp[i].blue = (float)(colors[i] & 0xFF) / 255.0f;
                vgColorRamp[i].stop = stops[i];
            }

            memset(&evo->defaultAttrib.paint.radgrad->data.rad_grad, 0, sizeof(evo->defaultAttrib.paint.radgrad->data.rad_grad));
            vg_lite_set_rad_grad(&evo->defaultAttrib.paint.radgrad->data.rad_grad,
                                 grad_data->stop_count,
                                 vgColorRamp,
                                 rad_grad->params,
                                 rad_grad->spread_mode,
                                 0);
            vg_lite_update_rad_grad(&evo->defaultAttrib.paint.radgrad->data.rad_grad);

            elm_free(stops);
            elm_free(vgColorRamp);
            break;
        }
        default:
            /* Do nothing */
            break;
        }

        evo->defaultAttrib.paint.color = object_data->color;
        evo->attribute = evo->defaultAttrib;
        ref_object(&evo->object);
        JUMP_IF_NON_ZERO_VALUE(add_object(&evo->object), error_exit);

#if (RTOS && DDRLESS) || BAREMETAL
#else
        elm_free(colors);
#endif
    }

    return evo->object.handle;

error_exit:
#if (RTOS && DDRLESS) || BAREMETAL
#else
    if ( colors != NULL )
        elm_free(colors);
    if ( path_data != NULL)
        elm_free(path_data);
#endif

    if ( (evo != NULL) && (evo->defaultAttrib.paint.grad != NULL) )
        elm_free(evo->defaultAttrib.paint.grad);
    if ( (evo != NULL) && (evo->defaultAttrib.paint.radgrad != NULL) )
        elm_free(evo->defaultAttrib.paint.radgrad);
    if ( local_evo != NULL )
        elm_free(local_evo);

    return ELM_NULL_HANDLE;
}

static ElmHandle _load_ebo(const uint8_t *data, int size, uint32_t version)
{
    vg_lite_error_t error;
    vg_lite_buffer_t *buffer;
    uint32_t *colors, bytes = 0;

    el_EBO_Header *ebo_header = (el_EBO_Header *) data;

#if (RTOS && DDRLESS) || BAREMETAL
    el_Obj_EBO *ebo = alloc_ebo();
#else
    el_Obj_EBO *ebo = (el_Obj_EBO *)elm_alloc(1, (sizeof(el_Obj_EBO)));
#endif
    JUMP_IF_NULL(ebo, error_exit);
#ifdef ENABLE_STRICT_DEBUG_MEMSET
    memset(ebo, 0, sizeof(el_Obj_EBO));
#endif
    buffer = &ebo->data.buffer;

    /*
     * Check if object size is valid. "size" needs to be a value greater than or
     * equal to the size of the current object header.
     */
    JUMP_IF_LOWER(size, sizeof(el_EBO_Header), error_exit);
    bytes += sizeof(el_EBO_Header);

    if(version == 1)
    {
        el_EBO_Palette *clut_header = (el_EBO_Palette *) (data + sizeof(el_EBO_Header));

        /* Make sure object size includes the CLUT header */
        bytes += sizeof(el_EBO_Palette);
        JUMP_IF_LOWER(size, bytes, error_exit);

        ebo->object.type = (ELM_OBJECT_TYPE) ebo_header->type;
        ebo->object.reference = 0;

        buffer->width  = ebo_header->width;
        buffer->height = ebo_header->height;
        buffer->format = (vg_lite_buffer_format_t) ebo_header->format;
        buffer->stride = 0;

        error = vg_lite_allocate(buffer);
        if (error != VG_LITE_SUCCESS)
        {
            destroy_ebo(ebo);
            return 0;
        }

        buffer->stride = ebo_header->stride;
        buffer->tiled  = (vg_lite_buffer_layout_t) ebo_header->tiled;
        colors = (uint32_t *)(data + clut_header->clut_data_offset);

        /* Make sure the object size includes image data */
        JUMP_IF_LOWER(size,
                      ebo_header->data_offset +
                          (buffer->stride * buffer->height),
                      error_exit);

        memcpy(buffer->memory,
               data + ebo_header->data_offset,
               buffer->stride * buffer->height);

        /* Save CLUT infomation. */
        ebo->clut_count = clut_header->clut_count;

        /* Make sure object size includes CLUT data */
        JUMP_IF_LOWER(size,
                      clut_header->clut_data_offset +
                          (sizeof(uint32_t) * clut_header->clut_count),
                      error_exit);

        memcpy(ebo->clut, colors, sizeof(uint32_t) * clut_header->clut_count);
    }
    else if(version == 2)
    {
        ebo->object.type = (ELM_OBJECT_TYPE) ebo_header->type;
        ebo->object.reference = 0;

        buffer->width  = ebo_header->width;
        buffer->height = ebo_header->height;
        buffer->format = (vg_lite_buffer_format_t) ebo_header->format;
        buffer->stride = 0;

        error = vg_lite_allocate(buffer);
        if (error != VG_LITE_SUCCESS)
        {
            destroy_ebo(ebo);
            return 0;
        }

        buffer->stride = ebo_header->stride;
        buffer->tiled  = (vg_lite_buffer_layout_t) ebo_header->tiled;

        /* Make sure the object size includes image data */
        JUMP_IF_LOWER(size,
                      ebo_header->data_offset +
                          (buffer->stride * buffer->height),
                      error_exit);

        memcpy(buffer->memory,
               data + ebo_header->data_offset,
               buffer->stride * buffer->height);
    }
    /* Set transformation to identity. */
    ebo->defaultAttrib.transform.dirty    = 1;
    ebo->defaultAttrib.transform.identity = 1;

    _init_transform(&ebo->defaultAttrib.transform);
    ebo->attribute = ebo->defaultAttrib;

    ref_object(&ebo->object);
    JUMP_IF_NON_ZERO_VALUE(add_object(&ebo->object), error_exit);

    return ebo->object.handle;

error_exit:
    if (ebo != NULL ) {
        elm_free(ebo);
    }

    return ELM_NULL_HANDLE;
}

static ElmHandle _load_ego(const uint8_t *data, int size)
{
    int i;
    unsigned int invalid_count = 0;
    uint32_t *obj_size, *obj_offset, *obj_type;
    void *obj_data;
    el_EGO_Header *ego_header = (el_EGO_Header *) data;

#if (RTOS && DDRLESS) || BAREMETAL
    el_Obj_Group *ego = alloc_ego();
#else
    el_Obj_Group *ego = (el_Obj_Group *)elm_alloc(1, sizeof(el_Obj_Group));
#endif
    JUMP_IF_NULL(ego, error_exit);
#ifdef ENABLE_STRICT_DEBUG_MEMSET
    memset(ego, 0, sizeof(el_Obj_Group));
#endif

    ego->object.type = (ELM_OBJECT_TYPE) ego_header->type;
    ego->object.reference = 0;

    _init_transform(&ego->defaultTrans);
    memcpy(&(ego->defaultTrans.matrix.m),
           &(ego_header->matrix),
           sizeof(vg_lite_matrix_t));
    ego->group.count = ego_header->count;
#if (RTOS && DDRLESS) || BAREMETAL
    ego->group.objects = alloc_evo(ego->group.count);
#else
    ego->group.objects = (el_Obj_EVO *)elm_alloc(1, ego->group.count * sizeof(el_Obj_EVO));
#endif
    JUMP_IF_NULL(ego->group.objects, error_exit);
#ifdef ENABLE_STRICT_DEBUG_MEMSET
    memset(ego->group.objects, 0, ego->group.count * sizeof(el_Obj_EVO));
#endif

    obj_size = (uint32_t *)((unsigned)data + sizeof(el_EGO_Header));
    obj_offset = (uint32_t *)((unsigned)obj_size + \
                              (ego_header->count * sizeof(uint32_t)));

    for (i = 0; i < ego->group.count && obj_offset[i] < size; i++)
    {
        if (obj_size[i] == 0) {
            invalid_count++;
            continue;
        }

        /* Check whether EVO object is truncated */
        JUMP_IF_GREATER(obj_offset[i] + obj_size[i], size, error_exit);

        /* Call appropriate object loader according to object type */
        obj_data = (void*)((unsigned)data + obj_offset[i]);
        obj_type = obj_data;
        switch (*obj_type) {
            case ELM_OBJECT_TYPE_EVO:
                ego->group.objects[i].object.handle = _load_evo(obj_data,
                        obj_size[i],
                        &ego->group.objects[i]);
                break;
#if (VG_RENDER_TEXT==1)
            case ELM_OBJECT_TYPE_FONT:
                _load_font(obj_data, obj_size[i]);
                break;
            case ELM_OBJECT_TYPE_TEXT:
                ego->group.objects[i].object.handle = _load_text(obj_data,
                        obj_size[i],
                        &ego->group.objects[i]);
                break;
#endif /* VG_RENDER_TEXT */
            default:
                break;
        }
    }

    ego->group.count -= invalid_count;
    ego->transform = ego->defaultTrans;

    ref_object(&ego->object);
    JUMP_IF_NON_ZERO_VALUE(add_object(&ego->object), error_exit);

    return ego->object.handle;

error_exit:
    if (ego != NULL ) {
        if ( ego->group.objects != NULL ) {
            elm_free(ego->group.objects);
        }
        elm_free(ego);
    }

    return ELM_NULL_HANDLE;
}

#if (defined(__ICCARM__))
/* Restore the unaligned data structure attribute warning */
#pragma diag_default = Pa039
#endif

static BOOL _scale(ElmHandle obj, float x, float y)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Object *object = get_object(obj);
    el_Obj_EBO *ebo = NULL;
    el_Obj_EVO *evo = NULL;
    el_Obj_Group *ego = NULL;
    el_Transform *transform = NULL;

    switch (object->type) {
        case ELM_OBJECT_TYPE_EBO:
            ebo = (el_Obj_EBO *)object;
            transform = &ebo->attribute.transform;
            break;

        case ELM_OBJECT_TYPE_EGO:
            ego = (el_Obj_Group *)object;
            if (elm_tls->gContext.vector_id < 0) {
                transform = &ego->transform;
            }
            else {
                evo = _get_evo(ego, elm_tls->gContext.vector_id);
                if (evo != NULL) {
                    transform = &evo->attribute.transform;
                }
                else {  /* No such vector object to set. */
                    return FALSE;
                }
            }
            break;

        case ELM_OBJECT_TYPE_EVO:
            evo = (el_Obj_EVO *)object;
            transform = &evo->attribute.transform;
            break;

        default:
            DEBUG_ASSERT(0, "Bad object type");
            break;
    }

    // Update the transformation params.
    transform->scale[0] *= x;
    transform->scale[1] *= y;

    vg_lite_scale(x, y, &transform->matrix);

    // Clean dirty.
    transform->dirty = FALSE;

    return TRUE;
}

static BOOL _reset_attrib(ElmHandle obj, ELM_EVO_PROP_BIT mask)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Object *object = get_object(obj);
    el_Obj_EBO *ebo = NULL;
    el_Obj_EVO *evo = NULL;
    el_Obj_Group *ego = NULL;
    el_Attribute *attrib = NULL;
    el_Attribute *defaultAttr = NULL;
    el_Transform *transform = NULL;
    el_Transform *defaultTrans = NULL;

    switch (object->type) {
        case ELM_OBJECT_TYPE_EBO:
            ebo = (el_Obj_EBO *)object;
            attrib = &ebo->attribute;
            defaultAttr = &ebo->defaultAttrib;
            transform = &attrib->transform;
            defaultTrans = &defaultAttr->transform;
            break;

        case ELM_OBJECT_TYPE_EGO:
            ego = (el_Obj_Group *)object;
            if (elm_tls->gContext.vector_id < 0) {
                transform = &ego->transform;
                defaultTrans = &ego->defaultTrans;
            }
            else {
                evo = _get_evo((el_Obj_Group*)obj, elm_tls->gContext.vector_id);
                if (evo != NULL) {
                    attrib = &evo->attribute;
                    defaultAttr = &evo->defaultAttrib;
                    transform = &attrib->transform;
                    defaultTrans = &defaultAttr->transform;
                }
                else {
                    return FALSE;
                }
            }
            break;

        case ELM_OBJECT_TYPE_EVO:
            evo = (el_Obj_EVO *)object;
            attrib = &evo->attribute;
            defaultAttr = &evo->defaultAttrib;
            transform = &attrib->transform;
            defaultTrans = &defaultAttr->transform;
            break;

        default:
            DEBUG_ASSERT(0, "Bad object type");
            return FALSE;
            break;
    }

    // Update the attribute value. When transform is modified, update the matrix.
    if (mask & ELM_PROP_ROTATE_BIT) {
        transform->rotate = defaultTrans->rotate;
    }

    if (mask & ELM_PROP_TRANSFER_BIT) {
        transform->translate[0] = defaultTrans->translate[0];
        transform->translate[1] = defaultTrans->translate[1];
    }

    if (mask & ELM_PROP_SCALE_BIT) {
        transform->scale[0] = defaultTrans->scale[0];
        transform->scale[1] = defaultTrans->scale[1];
    }

    /* On any bit reset, reset the whole matrix to the default one. */
    if (mask & (ELM_PROP_ROTATE_BIT | ELM_PROP_TRANSFER_BIT | ELM_PROP_SCALE_BIT)) {
        memcpy(&(transform->matrix), &(defaultTrans->matrix), sizeof(defaultTrans->matrix));
        transform->dirty = FALSE;
    }

    /* Update other rendering attributes. */
    if (mask & ELM_PROP_BLEND_BIT) {
        attrib->blend = defaultAttr->blend;
    }

    if (mask & ELM_PROP_QUALITY_BIT) {
        attrib->quality = defaultAttr->quality;
    }

    if (mask & ELM_PROP_FILL_BIT) {
        attrib->fill_rule = defaultAttr->fill_rule;
    }

    if (mask & ELM_PROP_COLOR_BIT) {
        attrib->paint.color = defaultAttr->paint.color;
    }

    if (mask & ELM_PROP_PAINT_BIT) {
        attrib->paint.type = defaultAttr->paint.type;
    }

    return TRUE;
}

static BOOL _set_quality(ElmHandle obj, ELM_QUALITY quality)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Object *object = get_object(obj);
    el_Obj_EBO *ebo = NULL;
    el_Obj_EVO *evo = NULL;
    el_Obj_Group *group = NULL;
    el_Attribute *attrib = NULL;

    switch (object->type) {
        case ELM_OBJECT_TYPE_EBO:
            ebo = (el_Obj_EBO *)object;
            attrib = &ebo->attribute;
            break;

        case ELM_OBJECT_TYPE_EVO:
            evo = (el_Obj_EVO *)object;
            attrib = &evo->attribute;
            break;

        case ELM_OBJECT_TYPE_EGO:
            group = (el_Obj_Group *)object;
            evo = _get_evo(group, elm_tls->gContext.vector_id);
            if (evo != NULL) {
                attrib = &evo->attribute;
            }
            else {
                return FALSE;
            }
            break;
        default:
            DEBUG_ASSERT(0, "Bad object type");
            return FALSE;
            break;
    }

    attrib->quality = quality;

    return TRUE;
}

static BOOL _set_fill(ElmVecObj evo, ELM_EVO_FILL fill)
{
    el_Obj_EVO *object = (el_Obj_EVO *)get_object(evo);

    if (object == NULL) {
        DEBUG_ASSERT(0, "Bad object handle");
        return FALSE;
    }

    object->attribute.fill_rule = fill;

    return TRUE;
}

static BOOL _set_blend(ElmHandle obj, ELM_BLEND blend)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Object *object = get_object(obj);
    el_Obj_EBO *ebo = NULL;
    el_Obj_EVO *evo = NULL;
    el_Obj_Group *group = NULL;
    el_Attribute *attrib = NULL;

    switch (object->type) {
        case ELM_OBJECT_TYPE_EBO:
            ebo = (el_Obj_EBO *)object;
            attrib = &ebo->attribute;
            break;

        case ELM_OBJECT_TYPE_EVO:
            evo = (el_Obj_EVO *)object;
            attrib = &evo->attribute;
            break;

        case ELM_OBJECT_TYPE_EGO:
            group = (el_Obj_Group *)object;
            evo = _get_evo(group, elm_tls->gContext.vector_id);
            if (evo != NULL) {
                attrib = &evo->attribute;
            }
            else {
                return FALSE;
            }
            break;
        default:
            DEBUG_ASSERT(0, "Bad object type");
            return FALSE;
            break;
    }

    attrib->blend = blend;

    return TRUE;
}

static BOOL _set_color(ElmVecObj evo, uint32_t color)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Obj_EVO *object = (el_Obj_EVO *)get_object(evo);
    el_Obj_Group *group = NULL;

    if (object == NULL) {
        DEBUG_ASSERT(0, "Bad object handle");
        return FALSE;
    }

    switch (object->object.type) {
        case ELM_OBJECT_TYPE_EVO:
            break;

        case ELM_OBJECT_TYPE_EGO:
            group = (el_Obj_Group *)object;
            object = _get_evo(group, elm_tls->gContext.vector_id);
            if (object == NULL) {
                return FALSE;
            }
            break;
        case ELM_OBJECT_TYPE_EBO:
        default:
            DEBUG_ASSERT(0, "Bad object type");
            return FALSE;
            break;
    }

    object->attribute.paint.color = color;

    return TRUE;
}

static BOOL _set_pattern(ElmVecObj evo, ElmBitmapObj pattern)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Obj_EVO *object = (el_Obj_EVO *)get_object(evo);
    el_Obj_EBO *ebo_obj = (el_Obj_EBO *) get_object(pattern);
    el_Obj_Group *group = NULL;

    if ((object == NULL) ||
        (ebo_obj == NULL)){
        DEBUG_ASSERT(0, "Bad object handle");
        return FALSE;
    }

    switch (object->object.type) {
        case ELM_OBJECT_TYPE_EVO:
            break;

        case ELM_OBJECT_TYPE_EGO:
            group = (el_Obj_Group *)object;
            object = _get_evo(group, elm_tls->gContext.vector_id);
            if (object == NULL) {
                return FALSE;
            }
            break;

        default:
            break;
    }

    object->attribute.paint.pattern.pattern = ebo_obj;
    ref_object((el_Object *)ebo_obj);

    return TRUE;
}

static BOOL _set_pattern_mode(ElmVecObj evo, ELM_PATTERN_MODE mode, uint32_t color)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Obj_EVO *object = (el_Obj_EVO *)get_object(evo);
    el_Obj_Group *group = NULL;

    if (object == NULL){
        DEBUG_ASSERT(0, "Bad object handle");
        return FALSE;
    }

    switch (object->object.type) {
        case ELM_OBJECT_TYPE_EVO:
            break;

        case ELM_OBJECT_TYPE_EGO:
            group = (el_Obj_Group *)object;
            object = _get_evo(group, elm_tls->gContext.vector_id);
            if (object == NULL) {
                return FALSE;
            }
            break;

        default:
            break;
    }

    object->attribute.paint.pattern.mode = mode;
    object->attribute.paint.pattern.color = color;

    return TRUE;
}

static BOOL _set_paintType(ElmVecObj evo, ELM_PAINT_TYPE type)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Obj_EVO *object = (el_Obj_EVO *)get_object(evo);
    el_Obj_Group *group = NULL;

    if (object == NULL) {
        DEBUG_ASSERT(0, "Bad object handle");
        return FALSE;
    }
    switch (object->object.type) {
        case ELM_OBJECT_TYPE_EVO:
            break;

        case ELM_OBJECT_TYPE_EGO:
            group = (el_Obj_Group *)object;
            object = _get_evo(group, elm_tls->gContext.vector_id);
            if (object == NULL) {
                return FALSE;
            }
            break;

        default:
            break;
    }

    object->attribute.paint.type = type;

    return TRUE;
}

static BOOL _rotate(ElmHandle obj, float angle)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Object *object = get_object(obj);
    el_Obj_EBO *ebo = NULL;
    el_Obj_EVO *evo = NULL;
    el_Obj_Group *ego = NULL;
    el_Transform *transform = NULL;

    switch (object->type) {
        case ELM_OBJECT_TYPE_EBO:
            ebo = (el_Obj_EBO *)object;
            transform = &ebo->attribute.transform;
            break;

        case ELM_OBJECT_TYPE_EGO:
            ego = (el_Obj_Group *)object;
            if (elm_tls->gContext.vector_id < 0) {
                transform = &ego->transform;
            }
            else {
                evo = _get_evo(ego, elm_tls->gContext.vector_id);
                if (evo != NULL) {
                    transform = &evo->attribute.transform;
                }
                else {
                    return FALSE;
                }
            }
            break;

        case ELM_OBJECT_TYPE_EVO:
            evo = (el_Obj_EVO *)object;
            transform = &evo->attribute.transform;
            break;

        default:
            DEBUG_ASSERT(0, "Bad object type");
            break;
    }

    // Update the transformation params.
    transform->rotate += angle;

    // Upate the matrix.
    vg_lite_rotate(angle, &transform->matrix);

    // Clean dirty.
    transform->dirty = FALSE;

    return TRUE;
}
static BOOL _translate(ElmHandle obj, float x, float y)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Object *object = get_object(obj);
    el_Obj_EBO *ebo = NULL;
    el_Obj_EVO *evo = NULL;
    el_Obj_Group *ego = NULL;
    el_Transform *transform = NULL;

    switch (object->type) {
        case ELM_OBJECT_TYPE_EBO:
            ebo = (el_Obj_EBO *)object;
            transform = &ebo->attribute.transform;
            break;

        case ELM_OBJECT_TYPE_EGO:
            ego = (el_Obj_Group *)object;
            if (elm_tls->gContext.vector_id < 0) {
                transform = &ego->transform;
            }
            else {
                evo = _get_evo(ego, elm_tls->gContext.vector_id);
                if (evo != NULL) {
                    transform = &evo->attribute.transform;
                }
                else {
                    return FALSE;
                }
            }
            break;

        case ELM_OBJECT_TYPE_EVO:
            evo = (el_Obj_EVO *)object;
            transform = &evo->attribute.transform;
            break;

        default:
            DEBUG_ASSERT(0, "Bad object type");
            break;
    }

    // Update the transformation params.
    transform->translate[0] += x;
    transform->translate[1] += y;

    // Update the matrix.
    vg_lite_translate(x, y, &transform->matrix);

    // Clean dirty.
    transform->dirty = FALSE;

    return TRUE;
}

static BOOL _verify_header(ELM_OBJECT_TYPE *type, uint32_t *version, void *data)
{
    uint32_t *p32_data = (uint32_t *)data;

    if (type != NULL) {
        *type = (ELM_OBJECT_TYPE)(*(p32_data + 1));
    }

    if (version != NULL) {
        *version = *p32_data;

        if (*version <= ELM_VERSION) {
            return TRUE;    /* Verified OK, compatible. */
        }
        else {
            return FALSE;   /* Verified Failed, API version is lower. */
        }
    }

    return TRUE;
}

/*
 Load the specified object from the data.
 */
static ElmHandle _create_object_from_data(ELM_OBJECT_TYPE type, void *data, int size)
{
    ELM_OBJECT_TYPE real_type;
    uint32_t p_data = (uint32_t)data;
    uint32_t version;

    if(p_data % BASE_ADDRESS_ALIGNMENT != 0) {
        DEBUG_ASSERT(0, "Error: data address don't align with 32 bytes!");
        return ELM_NULL_HANDLE;
    }

    if (FALSE == _verify_header(&real_type, &version, data)) {
        DEBUG_ASSERT(0, "Error: Incompatible file.");
        return ELM_NULL_HANDLE;
    }

    if (real_type != type) {
        DEBUG_ASSERT(0, "Warning: Specified type mismatched.\n");
    }

    /* Jump over the version field to get to the start of the first ELM object */
    data = (void *)((unsigned)data + sizeof(uint32_t));

    switch (real_type) {
        case ELM_OBJECT_TYPE_EVO:
            return _load_evo(data, size, NULL);
            break;

        case ELM_OBJECT_TYPE_EGO:
            return _load_ego(data, size);

        case ELM_OBJECT_TYPE_EBO:
            return _load_ebo(data, size, version);
#if (VG_RENDER_TEXT==1)
        case ELM_OBJECT_TYPE_FONT:
            return _load_font(data, size);

        case ELM_OBJECT_TYPE_TEXT:
            return _load_text(data, size, NULL);
#endif
        default:
            DEBUG_ASSERT(0, "Bad object type");
            break;
    }

    return ELM_NULL_HANDLE;
}

static el_Transform *_get_paint_transform(ElmHandle handle)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Transform *transform = NULL;
    el_Obj_Group *group = NULL;
    el_Obj_EVO *evo = NULL;

    evo = (el_Obj_EVO *)get_object(handle);

    if (evo == NULL) {
        DEBUG_ASSERT(0, "Bad object handle.\n");
        return NULL;
    }

    /* Find the corresponding evo object. */
    switch (evo->object.type) {
        case ELM_OBJECT_TYPE_EVO:
            break;

        case ELM_OBJECT_TYPE_EGO:
            group = (el_Obj_Group *)evo;
            evo = _get_evo(group, elm_tls->gContext.vector_id);
            if (evo == NULL) {
                return NULL;
            }
            break;

        case ELM_OBJECT_TYPE_EBO:
        default:
            DEBUG_ASSERT(0, "Incorrect object tyoe.\n");
            return NULL;
            break;
    }

    /* Get the correct transformation based on the paint type. */
    if (evo->attribute.paint.type == ELM_PAINT_PATTERN) {
        transform = &((el_Obj_EBO*)evo->attribute.paint.pattern.pattern)->attribute.transform;
    }
    else if (evo->attribute.paint.type == ELM_PAINT_GRADIENT) {
        transform = &evo->attribute.paint.grad->data.transform;
    }

    return transform;
}

/*********************** ELM API *********************/
#if !RTOS
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
ElmHandle ElmCreateObjectFromFile(ELM_OBJECT_TYPE type, const char *name)
{
#if RTOS || BAREMETAL
    return ELM_NULL_HANDLE;
#else
    void *data = NULL;
    long size = 0;
    FILE *fp = fopen(name, "rb");
    ElmHandle handle = ELM_NULL_HANDLE;

    if (fp != NULL) {
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);

        data = elm_alloc(1, size);
        if (data != NULL) {
            fseek(fp, 0, SEEK_SET);
            fread(data, size, 1, fp);

            handle = _create_object_from_data(type, data, size);
        }
        else {
            printf("open %s failed!\n", name);
        }
        elm_free(data);
        fclose(fp);
    }

    return handle;
#endif
}
#else
ElmHandle ElmCreateObjectFromFile(ELM_OBJECT_TYPE type, const char *name)
{
    return ELM_NULL_HANDLE;
}
#endif /*!ENABLE_ELM_CRATE_OBJECT_FROM_FILE*/
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
ElmHandle ElmCreateObjectFromData(ELM_OBJECT_TYPE type, void *data, int size)
{
    return _create_object_from_data(type, data, size);
}

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
BOOL ElmDestroyObject(ElmHandle object)
{
    int result = destroy_object(object);
    return (result >= 0);
}

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
BOOL ElmRotate(ElmHandle obj, float angle)
{
    return _rotate(obj, angle);
}

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
BOOL ElmTransfer(ElmHandle obj, int x, int y)
{
    return _translate(obj, x, y);
}

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
BOOL ElmScale(ElmHandle obj, float x, float y)
{
    return _scale(obj, x, y);
}

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
BOOL ElmReset(ElmHandle obj, ELM_EVO_PROP_BIT mask)
{
    return _reset_attrib(obj, mask);
}

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
BOOL ElmSetQuality(ElmHandle obj, ELM_QUALITY quality)
{
    return _set_quality(obj, quality);
}

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
BOOL ElmSetFill(ElmVecObj evo, ELM_EVO_FILL fill)
{
    return _set_fill(evo, fill);
}

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
BOOL ElmSetBlend(ElmHandle obj, ELM_BLEND blend)
{
    return _set_blend(obj, blend);
}

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
BOOL ElmSetColor(ElmVecObj evo, uint32_t color)
{
    return _set_color(evo, color);
}

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
BOOL ElmSetPattern(ElmVecObj evo, ElmBitmapObj pattern)
{
    return _set_pattern(evo, pattern);
}

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
BOOL ElmSetPatternMode(ElmVecObj evo, ELM_PATTERN_MODE mode, uint32_t color)
{
    return _set_pattern_mode(evo, mode, color);
}

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
BOOL ElmSetPaintType(ElmVecObj evo, ELM_PAINT_TYPE type)
{
    return _set_paintType(evo, type);
}

/*!
 @abstract Get the solid fill color of an evo object.

 @discussion
 This function Get the solid fill color of an evo object.

 @param evo
 The evo object.

 @return uint32_t
 The uint32 color value in rgba order.
 */
BOOL ElmGetColor(ElmGroupObj handle,uint32_t *color)
{
    elm_tls_t* elm_tls;
    el_Obj_EVO *evo;

    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    el_Obj_Group *ego = (el_Obj_Group*) get_object(handle);
    evo = _get_evo(ego, elm_tls->gContext.vector_id);
    *color = evo->attribute.paint.color;

    return TRUE;
}

/*!
 @abstract Query the vectory path count of an EGO object. If the given object
 is an evo/ebo, the count is 0.
 */
uint32_t ElmGetVectorCount(ElmHandle handle)
{
    el_Obj_Group *ego = (el_Obj_Group*) get_object(handle);
    if (ego->object.type != ELM_OBJECT_TYPE_EGO) {
        return 0;
    }
    else {
        return ego->group.count;
    }
}

/*!
 @abstract Query the type of an object (by handle).
 */
ELM_OBJECT_TYPE ElmGetObjectType(ElmHandle handle)
{
    el_Object *object = get_object(handle);
    return object->type;
}

/*!
 @abstract Set the current vectory object index to operate on.
 */
BOOL ElmSetCurrentVector(int32_t id)
{
    elm_tls_t* elm_tls;
    elm_tls = (elm_tls_t *) elm_os_get_tls();
    if (elm_tls == NULL)
        return FALSE;

    elm_tls->gContext.vector_id = id;

    return TRUE;
}

BOOL ElmScalePaint(ElmHandle handle, float sx, float sy)
{
    el_Transform *transform = NULL;

    transform = _get_paint_transform(handle);

    if (transform != NULL) {
        vg_lite_scale(sx, sy, &transform->matrix);
        transform->dirty = FALSE;
        return TRUE;
    }
    else {
        return FALSE;
    }
}
BOOL ElmRotatePaint(ElmHandle handle, float degrees)
{
    el_Transform *transform = NULL;

    transform = _get_paint_transform(handle);

    if (transform != NULL) {
        vg_lite_rotate(degrees, &transform->matrix);
        transform->dirty = FALSE;
        return TRUE;
    }
    else {
        return FALSE;
    }
}

BOOL ElmTranslatePaint(ElmHandle handle, float tx, float ty)
{
    el_Transform *transform = NULL;

    transform = _get_paint_transform(handle);

    if (transform != NULL) {
        vg_lite_translate(tx, ty, &transform->matrix);
        transform->dirty = FALSE;
        return TRUE;
    }
    else {
        return FALSE;
    }
}
