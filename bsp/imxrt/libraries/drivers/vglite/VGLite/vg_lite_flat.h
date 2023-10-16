
/****************************************************************************
*
*  Copyright Raph Levien 2022
*  Copyright Nicolas Silva 2022
*  Copyright NXP 2022
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*****************************************************************************/

#ifndef _vg_lite_flat_h_
#define _vg_lite_flat_h_

#include "vg_lite.h"

#ifdef __cplusplus
extern "C" {
#endif

vg_lite_error_t _flatten_quad_bezier(
                        vg_lite_stroke_conversion_t *stroke_conversion,
                        vg_lite_float_t X0,
                        vg_lite_float_t Y0,
                        vg_lite_float_t X1,
                        vg_lite_float_t Y1,
                        vg_lite_float_t X2,
                        vg_lite_float_t Y2);

vg_lite_error_t _flatten_cubic_bezier(
                        vg_lite_stroke_conversion_t *  stroke_conversion,
                        vg_lite_float_t X0,
                        vg_lite_float_t Y0,
                        vg_lite_float_t X1,
                        vg_lite_float_t Y1,
                        vg_lite_float_t X2,
                        vg_lite_float_t Y2,
                        vg_lite_float_t X3,
                        vg_lite_float_t Y3);

#ifdef __cplusplus
}
#endif

#endif /* _vg_lite_flat_h_ */
