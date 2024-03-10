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

#ifndef elm_precom_h
#define elm_precom_h

/* System headers. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* VGLite hdaders. */
#include "vg_lite.h"

/* Project headers. */
#include "Elm.h"
#include "velm.h"
#include "elm_os.h"

#define JUMP_IF_NON_ZERO_VALUE(x, label) { int ret = x; if ( (ret) != 1 ) { goto label; }  }
#define JUMP_IF_NULL(x, label) { if (x == NULL) { goto label;} }
#define JUMP_IF_LOWER(x, y, label) {if (x < y) {goto label;} }
#define JUMP_IF_GREATER(x, y, label) {if (x > y) {goto label;} }
#define JUMP_IF_EQUAL(x, y, label) {if (x == y) {goto label;} }
#define JUMP_IF_LOWER_OR_EQUAL(x, y, label) {if (x <= y) {goto label;} }
#define JUMP_IF_GREATER_OR_EQUAL(x, y, label) {if (x => y) {goto label;} }

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#endif /* elm_precom_h */
