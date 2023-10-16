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

#include "elm_precom.h"

#if (VG_RENDER_TEXT==1)
#include "elm_text.h"
#endif /* VG_RENDER_TEXT */

static void multiply(vg_lite_matrix_t * matrix, vg_lite_matrix_t * mult)
{
    vg_lite_matrix_t temp;
    int row, column;

    /* Process all rows. */
    for (row = 0; row < 3; row++) {
        /* Process all columns. */
        for (column = 0; column < 3; column++) {
            /* Compute matrix entry. */
            temp.m[row][column] =  (matrix->m[row][0] * mult->m[0][column])
            + (matrix->m[row][1] * mult->m[1][column])
            + (matrix->m[row][2] * mult->m[2][column]);
        }
    }

    memcpy(matrix, &temp, sizeof(temp));

}

static vg_lite_filter_t quality_to_filter(ELM_QUALITY quality)
{
    switch (quality) {
        case ELM_QULIATY_HI:
            return VG_LITE_FILTER_BI_LINEAR;
            break;

        case ELM_QUALITY_MED:
            return VG_LITE_FILTER_LINEAR;
            break;

        case ELM_QUALITY_LOW:
        default:
            return VG_LITE_FILTER_POINT;
            break;
    }
}

static vg_lite_pattern_mode_t pat_to_pad(ELM_PATTERN_MODE mode)
{
    switch (mode) {
        case ELM_PATTERN_MODE_PAD:
            return VG_LITE_PATTERN_PAD;
            break;

        default:
            return VG_LITE_PATTERN_COLOR;
            break;
    }
}
static vg_lite_error_t draw_evo_pattern(el_Obj_Buffer *buff, el_Obj_Group *ego,int * index)
{
    el_Obj_EVO *evo;
    vg_lite_error_t error = VG_LITE_INVALID_ARGUMENT;
    vg_lite_color_t color;
    vg_lite_filter_t filter;
    vg_lite_blend_t blend;
    vg_lite_fill_t rule;
    vg_lite_buffer_t *buffer;
    vg_lite_matrix_t mat;
    vg_lite_pattern_mode_t pat_mode;
    int width = 0;
    int height = 0;

    int start = *index;
    int i = start;
    evo = &ego->group.objects[i];
    width  = (int)(evo->data.path.bounding_box[2] - evo->data.path.bounding_box[0]);
    height = (int)(evo->data.path.bounding_box[3] - evo->data.path.bounding_box[1]);
    buffer = (vg_lite_buffer_t *)malloc(sizeof(vg_lite_buffer_t));
    memset(buffer,0,sizeof(vg_lite_buffer_t));
    buffer->width = width;
    buffer->height = height;
    buffer->format = VG_LITE_RGBA8888;
    error = vg_lite_allocate(buffer);
    vg_lite_clear(buffer,NULL,0xffffffff);
    i++;
    evo = &ego->group.objects[i];
    while(evo->is_pattern)
    {
        blend = (vg_lite_blend_t)evo->attribute.blend;
        rule = (vg_lite_fill_t)evo->attribute.fill_rule;
        color = (vg_lite_color_t)evo->attribute.paint.color;
        memcpy(&mat, &(evo->attribute.transform.matrix), sizeof(mat));
        error = vg_lite_draw(buffer, &evo->data.path,
                                rule,
                                &mat,
                                blend,
                                color);
        if(error)
            return error;
        i++;
        evo = &ego->group.objects[i];
    }
    *index = i - 1;
    evo = &ego->group.objects[start];
    blend = (vg_lite_blend_t)evo->attribute.blend;
    rule = (vg_lite_fill_t)evo->attribute.fill_rule;
    color = (vg_lite_color_t)evo->attribute.paint.color;
    memcpy(&mat, &(evo->attribute.transform.matrix), sizeof(mat));
    filter = VG_LITE_FILTER_POINT;
    pat_mode = VG_LITE_PATTERN_COLOR;
    error = vg_lite_draw_pattern(&buff->buffer, &evo->data.path,
                            rule,
                            &mat,
                            buffer,
                            &mat,
                            blend,
                            pat_mode,
                            color,
                            filter);
    vg_lite_finish();
    vg_lite_free(buffer);
    free(buffer);
    return error;
}

static vg_lite_error_t draw_evo(el_Obj_Buffer *buff, el_Obj_EVO *evo, vg_lite_matrix_t *mat)
{
    el_Obj_EBO *pattern;
    vg_lite_error_t error = VG_LITE_INVALID_ARGUMENT;
    vg_lite_color_t color;
    vg_lite_filter_t filter;
    vg_lite_matrix_t mat_pattern;
    ELM_PAINT_TYPE paint_type = evo->attribute.paint.type;
    vg_lite_blend_t blend = (vg_lite_blend_t)evo->attribute.blend;
    vg_lite_fill_t rule = (vg_lite_fill_t)evo->attribute.fill_rule;
    vg_lite_pattern_mode_t pat_mode = pat_to_pad(evo->attribute.paint.pattern.mode);

    switch (paint_type) {
    case ELM_PAINT_GRADIENT:
        memcpy(&evo->attribute.paint.grad->data.grad.matrix,
               &evo->attribute.paint.grad->data.transform.matrix,
               sizeof(evo->attribute.paint.grad->data.transform.matrix));
#if !DDRLESS
        error = vg_lite_draw_gradient(&buff->buffer, &evo->data.path,
                                      rule,
                                      mat,
                                      &evo->attribute.paint.grad->data.grad,
                                      blend);
#else
        error = vg_lite_draw_gradient(NULL, &evo->data.path,
                                      rule,
                                      mat,
                                      &evo->attribute.paint.grad->data.grad,
                                      blend);
#endif
        break;
    case ELM_PAINT_RADIAL_GRADIENT:
        memcpy(&evo->attribute.paint.radgrad->data.rad_grad.matrix,
               &evo->attribute.paint.radgrad->data.transform.matrix,
               sizeof(evo->attribute.paint.radgrad->data.transform.matrix));

        error = vg_lite_draw_radial_gradient(&buff->buffer, &evo->data.path,
                                      rule,
                                      mat,
                                      &evo->attribute.paint.radgrad->data.rad_grad,
                                      0,
                                      blend,
                                      VG_LITE_FILTER_LINEAR);
        break;
    case ELM_PAINT_COLOR:
        color = (vg_lite_color_t)evo->attribute.paint.color;

#if !DDRLESS
        error = vg_lite_draw(&buff->buffer, &evo->data.path,
                             rule,
                             mat,
                             blend,
                             color);
#else
        error = vg_lite_draw(NULL, &evo->data.path,
                             rule,
                             mat,
                             blend,
                             color);
#endif
        break;
    case ELM_PAINT_PATTERN:
        pattern = (el_Obj_EBO *)(evo->attribute.paint.pattern.pattern);
        blend = (vg_lite_blend_t)(pattern->attribute.blend);
        filter = quality_to_filter(evo->attribute.quality);
        color = (vg_lite_color_t)pattern->attribute.paint.color;
        memcpy(&mat_pattern, &pattern->attribute.transform.matrix,
               sizeof(pattern->attribute.transform.matrix));

#if !DDRLESS
        error = vg_lite_draw_pattern(&buff->buffer, &evo->data.path, rule, mat,
                                     &pattern->data.buffer, &mat_pattern, blend,
                                     pat_mode, color, filter);
#else
        error = vg_lite_draw_pattern(NULL, &evo->data.path, rule, mat,
                                     &pattern->data.buffer, &mat_pattern, blend,
                                     pat_mode, color, filter);
#endif
        break;
    case ELM_PAINT_TEXT:
#if (VG_RENDER_TEXT==1)
        error = draw_text(buff, evo, mat);
#endif /* VG_RENDER_TEXT */
        break;
    }

    return error;
}

static vg_lite_error_t draw_ebo(el_Obj_Buffer *buff, el_Obj_EBO *ebo, vg_lite_matrix_t *mat)
{
    vg_lite_error_t error;
    vg_lite_buffer_t *image_buffer = &ebo->data.buffer;
    vg_lite_blend_t   blend = (vg_lite_blend_t)ebo->attribute.blend;
    vg_lite_color_t   color = ebo->attribute.paint.color;
    vg_lite_filter_t filter = quality_to_filter(ebo->attribute.quality);

    if (image_buffer->format >= VG_LITE_INDEX_1 && image_buffer->format <= VG_LITE_INDEX_8)
    {
        vg_lite_set_CLUT(ebo->clut_count, ebo->clut);
    }

    image_buffer->image_mode = VG_LITE_NORMAL_IMAGE_MODE;
#if !DDRLESS
    error = vg_lite_blit(&buff->buffer, image_buffer, mat, blend, color, filter);
#else
    error = vg_lite_blit(NULL, image_buffer, mat, blend, color, filter);
#endif
    return error;
}
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
BOOL ElmClear(ElmBuffer buffer, uint32_t color, uint32_t x, uint32_t y, uint32_t width, uint32_t height, BOOL full)
{
#if !DDRLESS
    vg_lite_error_t error = VG_LITE_SUCCESS;
    el_Obj_Buffer *buff = (el_Obj_Buffer *)get_object(buffer);
    vg_lite_rectangle_t rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.width = width;
    rectangle.height = height;

    if (full == 1)
    {
        error = vg_lite_clear(&buff->buffer, NULL, color);
    }
    else
    {
        error = vg_lite_clear(&buff->buffer, &rectangle, color);
    }
    return ((error == VG_LITE_SUCCESS) ? TRUE : FALSE);
#else
    return TRUE;
#endif
}

/*!
 @abstract Finish all rendering on GPU issued before this call.

 @discussion
 This function tells the engine that it has finished the frame data and GPU can draw it now. It's blocked until GPU rendering done.

 @return
 If the opeartion is successfully done or not.
 */
BOOL ElmFinish()
{
    vg_lite_finish();
    return TRUE;
}

/*!
 @abstract Flush all rendering command to GPU issued before this call.

 @discussion
 This function tells the engine to start kicking off command to GPU side, it will return immediately after firing off GPU.

 @return
 If the opeartion is successfully done or not.
 */
BOOL ElmFlush()
{
    vg_lite_flush();
    return TRUE;
}



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
BOOL ElmDraw(ElmBuffer buffer, ElmHandle object)
{
    BOOL status = TRUE;
    el_Object *elm;
    el_Obj_Buffer *buff;
    vg_lite_error_t error;
    vg_lite_matrix_t mat;
    elm = get_object(object);

    if (!elm)
    {
        return FALSE;
    }

#if !DDRLESS
    buff = (el_Obj_Buffer *)get_object(buffer);
    if (buff == NULL)
    {
        return FALSE;
    }
#else
    buff = NULL;
#endif

    if (elm->type == ELM_OBJECT_TYPE_EGO)
    {
        el_Obj_EVO *evo;
        el_Obj_Group *ego = (el_Obj_Group *)elm;
        vg_lite_matrix_t mat_group, res_mat;

        if (ego->group.count > 0)
        {
            int i;
            memcpy(&mat_group, &(ego->transform.matrix), sizeof(ego->transform.matrix));
            for (i = 0; i < ego->group.count; i++)
            {
                evo = &ego->group.objects[i];

                /* Font objects may generate empty objects */
                if (evo->object.handle == ELM_NULL_HANDLE)
                    continue;

                if(evo->is_image)
                {
                    ElmHandle ebo_handle;
                    el_Object *elm_ebo;
                    el_Obj_EBO *ebo;
                    ebo_handle = ElmCreateObjectFromFile(ELM_OBJECT_TYPE_EBO, evo->eboname);
                    elm_ebo = get_object(ebo_handle);
                    ebo = (el_Obj_EBO *)elm_ebo;
                    memcpy(&mat, &evo->defaultAttrib.transform.matrix, sizeof(mat));

                    error = draw_ebo(buff, ebo, &mat);
                    if (error)
                    {
                        status = FALSE;
                    }
                    continue;
                }
                memcpy(&mat, &(evo->attribute.transform.matrix), sizeof(mat));
                memcpy(&res_mat, &mat_group, sizeof(mat_group));
                multiply(&res_mat, &mat);

                if(evo->has_pattern)
                    error = draw_evo_pattern(buff,ego,&i);
                else
                    error = draw_evo(buff, evo, &res_mat);
                if (error)
                {
                    status = FALSE;
                    break;
                }
            }
        }
    }
    else if (elm->type == ELM_OBJECT_TYPE_EVO)
    {
        el_Obj_EVO *evo = (el_Obj_EVO *)elm;
        memcpy(&mat, &(evo->attribute.transform.matrix), sizeof(mat));

        error = draw_evo(buff, evo, &mat);
        if (error)
        {
            status = FALSE;
        }
    }
    else if (elm->type == ELM_OBJECT_TYPE_EBO)
    {
        el_Obj_EBO *ebo = (el_Obj_EBO *)elm;
        memcpy(&mat, &(ebo->attribute.transform.matrix), sizeof(mat));

        error = draw_ebo(buff, ebo, &mat);
        if (error)
        {
            status = FALSE;
        }

    }
    else if (elm->type == ELM_OBJECT_TYPE_BUF)
    {
        el_Obj_Buffer *src = (el_Obj_Buffer *)elm;
        vg_lite_identity(&mat);

#if !DDRLESS
        if (VG_LITE_SUCCESS !=
            vg_lite_blit(&buff->buffer, &src->buffer, &mat, VG_LITE_BLEND_NONE, 0,
                         VG_LITE_FILTER_BI_LINEAR)
            )
#else
        if (VG_LITE_SUCCESS !=
            vg_lite_blit(NULL, &src->buffer, &mat, VG_LITE_BLEND_NONE, 0,
                         VG_LITE_FILTER_BI_LINEAR)
            )
#endif
        {
            status = FALSE;
        }
    }
    return status;
}
