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

#include <math.h>
#include <string.h>
#include "vg_lite.h"


void vg_lite_identity(vg_lite_matrix_t * matrix)
{
    /* Set identify matrix. */
    matrix->m[0][0] = 1.0f;
    matrix->m[0][1] = 0.0f;
    matrix->m[0][2] = 0.0f;
    matrix->m[1][0] = 0.0f;
    matrix->m[1][1] = 1.0f;
    matrix->m[1][2] = 0.0f;
    matrix->m[2][0] = 0.0f;
    matrix->m[2][1] = 0.0f;
    matrix->m[2][2] = 1.0f;
}

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

    /* Copy temporary matrix into result. */
    memcpy(matrix, &temp, sizeof(temp));
}

void vg_lite_translate(vg_lite_float_t x, vg_lite_float_t y, vg_lite_matrix_t * matrix)
{
    /* Set translation matrix. */
    vg_lite_matrix_t t = { { {1.0f, 0.0f, x},
        {0.0f, 1.0f, y},
        {0.0f, 0.0f, 1.0f}
    } };

    /* Multiply with current matrix. */
    multiply(matrix, &t);
}

void vg_lite_scale(vg_lite_float_t scale_x, vg_lite_float_t scale_y, vg_lite_matrix_t * matrix)
{
    /* Set scale matrix. */
    vg_lite_matrix_t s = { { {scale_x, 0.0f, 0.0f},
        {0.0f, scale_y, 0.0f},
        {0.0f, 0.0f, 1.0f}
    } };

    /* Multiply with current matrix. */
    multiply(matrix, &s);
}

void vg_lite_rotate(vg_lite_float_t degrees, vg_lite_matrix_t * matrix)
{
#ifndef M_PI
#define M_PI 3.1415926f
#endif
    /* Convert degrees into radians. */
    vg_lite_float_t angle = degrees / 180.0f * M_PI;

    /* Compuet cosine and sine values. */
    vg_lite_float_t cos_angle = cosf(angle);
    vg_lite_float_t sin_angle = sinf(angle);

    /* Set rotation matrix. */
    vg_lite_matrix_t r = { { {cos_angle, -sin_angle, 0.0f},
        {sin_angle, cos_angle, 0.0f},
        {0.0f, 0.0f, 1.0f}
    } };

    /* Multiply with current matrix. */
    multiply(matrix, &r);
}
