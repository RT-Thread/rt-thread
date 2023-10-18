
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

#include <math.h>

#include "vg_lite_flat.h"

/*
 * Stop IAR compiler from warning about implicit conversions from float to
 * double
 */
#if (defined(__ICCARM__))
#pragma diag_suppress = Pa205
#endif

#ifndef VG_CURVE_FLATTENING_TOLERANCE
#define VG_CURVE_FLATTENING_TOLERANCE           0.25
#endif /* defined(VG_CURVE_FLATTENING_TOLERANCE) */

#define FABSF(x)                                ((vg_lite_float_t) fabs(x))
#define SQRTF(x)                                ((vg_lite_float_t) sqrt(x))
#define CEILF(x)                                ((vg_lite_float_t) ceil(x))

#define VG_LITE_ERROR_HANDLER(func) \
if ((error = func) != VG_LITE_SUCCESS) \
goto ErrorHandler

/* Point flatten type for flattened line segments. */
#define vgcFLATTEN_NO                           0
#define vgcFLATTEN_START                        1
#define vgcFLATTEN_MIDDLE                       2
#define vgcFLATTEN_END                          3

/*
 * Algorithm originally created by Raph Levien:
 * https://raphlinus.github.io/graphics/curves/2019/12/23/flatten-quadbez.html
 */

#define FHYPOTF(x, y) ((vg_lite_float_t) hypotf(x, y))
#define FPOWF(x, y) ((vg_lite_float_t) powf(x, y))

/*
 * Contains the fields that are used to represent the quadratic Bezier curve
 * as a 'y = x^2' parabola.
 */
typedef struct parabola_approx {
    vg_lite_float_t x0;
    vg_lite_float_t x2;
    vg_lite_float_t scale;
    vg_lite_float_t cross;
} parabola_approx_t;

/*
 * Keeps the quadratic Bezier's control points. This makes life easier when
 * passing quadratics as parameters, so we don't have to give 6 floats every
 * time.
 */
typedef struct quad_bezier {
    vg_lite_float_t X0;
    vg_lite_float_t Y0;
    vg_lite_float_t X1;
    vg_lite_float_t Y1;
    vg_lite_float_t X2;
    vg_lite_float_t Y2;
} quad_bezier_t;

/*
 * Parameters which are used by the flattening algorithm.
 */
typedef struct quad_bezier_flatten_params {
    vg_lite_float_t a0;
    vg_lite_float_t a2;
    int num_points;
    vg_lite_float_t u0;
    vg_lite_float_t u2;
} quad_bezier_flatten_params_t;

/*
 * Keeps the cubic Bezier's control points.
 */
typedef struct cubic_bezier {
    vg_lite_float_t X0;
    vg_lite_float_t Y0;
    vg_lite_float_t X1;
    vg_lite_float_t Y1;
    vg_lite_float_t X2;
    vg_lite_float_t Y2;
    vg_lite_float_t X3;
    vg_lite_float_t Y3;
} cubic_bezier_t;


vg_lite_error_t _add_point_to_point_list(
                                vg_lite_stroke_conversion_t * stroke_conversion,
                                vg_lite_float_t X,
                                vg_lite_float_t Y,
                                uint8_t flatten_flag);

vg_lite_error_t _add_point_to_point_list_wdelta(
                                vg_lite_stroke_conversion_t * stroke_conversion,
                                vg_lite_float_t X,
                                vg_lite_float_t Y,
                                vg_lite_float_t DX,
                                vg_lite_float_t DY,
                                uint8_t flatten_flag);


/*
 * Evaluates the Bernstein polynomial that represents the curve, at 't'.
 * 't' should be a value between 0.0 and 1.0 (though it can be any float, but
 *      the relevant values are between 0 and 1).
 * 'x' and 'y' will contain the coordinates of the evaluated point.
 */
static void quad_bezier_eval(
    const quad_bezier_t *q,
    vg_lite_float_t t,
    vg_lite_float_t *x,
    vg_lite_float_t *y
    )
{
    const vg_lite_float_t omt = 1.0 - t;
    *x = q->X0 * omt * omt + 2.0 * q->X1 * t * omt + q->X2 * t * t;
    *y = q->Y0 * omt * omt + 2.0 * q->Y1 * t * omt + q->Y2 * t * t;
}

/*
 * Approximates the integral which uses the arclength and curvature of the
 * parabola.
 */
static vg_lite_float_t approx_integral(vg_lite_float_t x)
{
    const vg_lite_float_t D = 0.67;
    return x / (1.0 - D + FPOWF(FPOWF(D, 4) + 0.25 * x * x, 0.25));
}

/*
 * Approximates the inverse of the previous integral.
 */
static vg_lite_float_t approx_inverse_integral(vg_lite_float_t x)
{
    const vg_lite_float_t B = 0.39;
    return x * (1.0 - B + SQRTF(B * B + 0.25 * x * x));
}

/*
 * Represents a quadratic Bezier curve as a parabola.
 */
static parabola_approx_t map_to_parabola(const quad_bezier_t *q)
{
    const vg_lite_float_t ddx = 2 * q->X1 - q->X0 - q->X2;
    const vg_lite_float_t ddy = 2 * q->Y1 - q->Y0 - q->Y2;
    const vg_lite_float_t u0 = (q->X1 - q->X0) * ddx + (q->Y1 - q->Y0) * ddy;
    const vg_lite_float_t u2 = (q->X2 - q->X1) * ddx + (q->Y2 - q->Y1) * ddy;
    const vg_lite_float_t cross = (q->X2 - q->X0) * ddy - (q->Y2 - q->Y0) * ddx;
    const vg_lite_float_t x0 = u0 / cross;
    const vg_lite_float_t x2 = u2 / cross;
    const vg_lite_float_t scale = FABSF(cross) / (FHYPOTF(ddx, ddy) * FABSF(x2 - x0));

    return (parabola_approx_t) {
        .x0 = x0,
        .x2 = x2,
        .scale = scale,
        .cross = cross
    };
}

/*
 * Tolerance influences the number of lines generated. The lower the tolerance,
 * the more lines it generates, thus the flattening will have a higher quality,
 * but it will also consume more memory. The bigger the tolerance, the less lines
 * will be generated, so the quality will be worse, but the memory consumption
 * will be better.
 *
 * A good default value could be 0.25.
 */
static quad_bezier_flatten_params_t quad_bezier_flatten_params_init(
    const quad_bezier_t *q,
    vg_lite_float_t tolerance
    )
{
    const parabola_approx_t params = map_to_parabola(q);
    const vg_lite_float_t a0 = approx_integral(params.x0);
    const vg_lite_float_t a2 = approx_integral(params.x2);
    const vg_lite_float_t count = 0.5 * FABSF(a2 - a0) * SQRTF(params.scale / tolerance);
    const int num_points = (int)CEILF(count);
    const vg_lite_float_t u0 = approx_inverse_integral(a0);
    const vg_lite_float_t u2 = approx_inverse_integral(a2);

    return (quad_bezier_flatten_params_t) {
        .a0 = a0,
        .a2 = a2,
        .num_points = num_points,
        .u0 = u0,
        .u2 = u2
    };
}

/*
 * Puts into (x, y) the coordinate to which a line should be drawn given the step.
 * This should be used in a loop to flatten a curve, like this:
 * ```
 * params = quad_bezier_flatten_params_init(&q, tolerance);
 * for (int i = 1; i < params.num_points; ++i) {
 *  vg_lite_float_t x, y;
 *  quad_bezier_flatten_at(&q, &params, i, &x, &y);
 *  draw_line_to(x, y);
 * }
 * ```
 */
static void quad_bezier_flatten_at(
    const quad_bezier_t *q,
    const quad_bezier_flatten_params_t *params,
    int step,
    vg_lite_float_t *x,
    vg_lite_float_t *y
    )
{
    const vg_lite_float_t a0 = params->a0, a2 = params->a2, u0 = params->u0, u2 = params->u2;
    const int num_points = params->num_points;
    const vg_lite_float_t u = approx_inverse_integral(a0 + ((a2 - a0) * step) / num_points);
    const vg_lite_float_t t = (u - u0) / (u2 - u0);

    quad_bezier_eval(q, t, x, y);
}

vg_lite_error_t
_flatten_quad_bezier(
    vg_lite_stroke_conversion_t *stroke_conversion,
    vg_lite_float_t X0,
    vg_lite_float_t Y0,
    vg_lite_float_t X1,
    vg_lite_float_t Y1,
    vg_lite_float_t X2,
    vg_lite_float_t Y2
    )
{
    vg_lite_error_t error = VG_LITE_SUCCESS;
    vg_lite_path_point_ptr point0, point1;
    vg_lite_float_t x, y;

    const vg_lite_float_t tolerance = VG_CURVE_FLATTENING_TOLERANCE;
    const quad_bezier_t q = {
        .X0 = X0,
        .Y0 = Y0,
        .X1 = X1,
        .Y1 = Y1,
        .X2 = X2,
        .Y2 = Y2
    };
    const quad_bezier_flatten_params_t params = quad_bezier_flatten_params_init(&q, tolerance);

    if(!stroke_conversion)
        return VG_LITE_INVALID_ARGUMENT;

    /* Add extra P0 for incoming tangent. */
    point0 = stroke_conversion->path_last_point;
    /* First add P1 to calculate incoming tangent, which is saved in P0. */
    VG_LITE_ERROR_HANDLER(_add_point_to_point_list(stroke_conversion, X1, Y1, vgcFLATTEN_START));

    point1 = stroke_conversion->path_last_point;
    /* Change the point1's coordinates back to P0. */
    point1->x = X0;
    point1->y = Y0;
    point0->length = 0.0f;

    for (int i = 1; i < params.num_points; ++i) {
        quad_bezier_flatten_at(&q, &params, i, &x, &y);
        _add_point_to_point_list(stroke_conversion, x, y, vgcFLATTEN_MIDDLE);
    }

    /* Add point 2 separately to avoid cumulative errors. */
    VG_LITE_ERROR_HANDLER(_add_point_to_point_list(stroke_conversion, X2, Y2, vgcFLATTEN_END));

    /* Add extra P2 for outgoing tangent. */
    /* First change P2(point0)'s coordinates to P1. */
    point0 = stroke_conversion->path_last_point;
    point0->x = X1;
    point0->y = Y1;

    /* Add P2 to calculate outgoing tangent. */
    VG_LITE_ERROR_HANDLER(_add_point_to_point_list(stroke_conversion, X2, Y2, vgcFLATTEN_NO));

    point1 = stroke_conversion->path_last_point;

    /* Change point0's coordinates back to P2. */
    point0->x = X2;
    point0->y = Y2;
    point0->length = 0.0f;

ErrorHandler:
    return error;
}

/*
 * Like eval_quad_bezier, computes the coordinates of the point which resides at
 * `t` for the cubic.
 */
static void cubic_bezier_eval(
    const cubic_bezier_t *c,
    vg_lite_float_t t,
    vg_lite_float_t *x,
    vg_lite_float_t *y
    )
{
    const vg_lite_float_t omt = 1.0 - t;
    const vg_lite_float_t omt2 = omt * omt;
    const vg_lite_float_t omt3 = omt * omt2;
    const vg_lite_float_t t2 = t * t;
    const vg_lite_float_t t3 = t * t2;

    *x = omt3 * c->X0 + 3.0 * t * omt2 * c->X1 + 3.0 * t2 * omt * c->X2 + t3 * c->X3;
    *y = omt3 * c->Y0 + 3.0 * t * omt2 * c->Y1 + 3.0 * t2 * omt * c->Y2 + t3 * c->Y3;
}

static quad_bezier_t cubic_bezier_derivative(const cubic_bezier_t *c)
{
    const vg_lite_float_t x0 = 3.0 * (c->X1 - c->X0);
    const vg_lite_float_t y0 = 3.0 * (c->Y1 - c->Y0);
    const vg_lite_float_t x1 = 3.0 * (c->X2 - c->X1);
    const vg_lite_float_t y1 = 3.0 * (c->Y2 - c->Y1);
    const vg_lite_float_t x2 = 3.0 * (c->X3 - c->X2);
    const vg_lite_float_t y2 = 3.0 * (c->Y3 - c->Y2);

    return (quad_bezier_t) {
        .X0 = x0,
        .Y0 = y0,
        .X1 = x1,
        .Y1 = y1,
        .X2 = x2,
        .Y2 = y2
    };
}

/*
 * Returns the cubic bezier that is between t0 and t1 of c.
 */
static cubic_bezier_t cubic_bezier_split_at(
    const cubic_bezier_t *c,
    vg_lite_float_t t0,
    vg_lite_float_t t1
    )
{
    vg_lite_float_t p0x, p0y, p1x, p1y, p2x, p2y, p3x, p3y, d1x, d1y, d2x, d2y;
    vg_lite_float_t scale;
    quad_bezier_t derivative;

    cubic_bezier_eval(c, t0, &p0x, &p0y);
    cubic_bezier_eval(c, t1, &p3x, &p3y);
    derivative = cubic_bezier_derivative(c);
    scale = (t1 - t0) * (1.0 / 3.0);
    quad_bezier_eval(&derivative, t0, &d1x, &d1y);
    quad_bezier_eval(&derivative, t1, &d2x, &d2y);
    p1x = p0x + scale * d1x;
    p1y = p0y + scale * d1y;
    p2x = p3x - scale * d2x;
    p2y = p3y - scale * d2y;

    return (cubic_bezier_t) {
        .X0 = p0x,
        .Y0 = p0y,
        .X1 = p1x,
        .Y1 = p1y,
        .X2 = p2x,
        .Y2 = p2y,
        .X3 = p3x,
        .Y3 = p3y
    };
}

/*
 * This function returns the number of quadratic Bezier curves that are needed to
 * represent the given cubic, respecting the tolerance.
 *
 * As with the flattening of quadratics, the lower the tolerance, the better the
 * quality. The higher the tolerance, the worse the quality, but better performance
 * or memory consumption.
 *
 * The algorithm comes from:
 * https://web.archive.org/web/20210108052742/http://caffeineowl.com/graphics/2d/vectorial/cubic2quad01.html
 *
 * Implementation adapted from:
 * https://github.com/linebender/kurbo/blob/master/src/cubicbez.rs
 * and:
 * https://scholarsarchive.byu.edu/cgi/viewcontent.cgi?article=1000&context=facpub#section.10.6
 */
static int cubic_bezier_get_flatten_count(
    const cubic_bezier_t *c,
    vg_lite_float_t tolerance
    )
{
    const vg_lite_float_t x = c->X0 - 3.0 * c->X1 + 3.0 * c->X2 - c->X3;
    const vg_lite_float_t y = c->Y0 - 3.0 * c->Y1 + 3.0 * c->Y2 - c->Y3;
    const vg_lite_float_t err = x * x + y * y;
    vg_lite_float_t result;

    result = FPOWF(err / (432.0 * tolerance * tolerance), 1.0 / 6.0);
    result = CEILF(result);

    return result > 1.0 ? (int)result : 1;
}

vg_lite_error_t
_flatten_cubic_bezier(
    vg_lite_stroke_conversion_t *  stroke_conversion,
    vg_lite_float_t X0,
    vg_lite_float_t Y0,
    vg_lite_float_t X1,
    vg_lite_float_t Y1,
    vg_lite_float_t X2,
    vg_lite_float_t Y2,
    vg_lite_float_t X3,
    vg_lite_float_t Y3
    )
{
    vg_lite_error_t error = VG_LITE_SUCCESS;
    vg_lite_path_point_ptr point0, point1;
    const cubic_bezier_t c = {
        .X0 = X0,
        .Y0 = Y0,
        .X1 = X1,
        .Y1 = Y1,
        .X2 = X2,
        .Y2 = Y2,
        .X3 = X3,
        .Y3 = Y3
    };
    const vg_lite_float_t tolerance = VG_CURVE_FLATTENING_TOLERANCE;
    int num_curves = cubic_bezier_get_flatten_count(&c, tolerance);
    vg_lite_float_t fnum_curves = (vg_lite_float_t)num_curves;
    vg_lite_float_t fi, t0, t1, p1x, p1y, p2x, p2y, x, y;
    cubic_bezier_t subsegment;
    quad_bezier_t current_curve;
    quad_bezier_flatten_params_t params;

    if(!stroke_conversion)
        return VG_LITE_INVALID_ARGUMENT;

    /* Add extra P0 for incoming tangent. */
    point0 = stroke_conversion->path_last_point;
    /* First add P1/P2/P3 to calculate incoming tangent, which is saved in P0. */
    if (X0 != X1 || Y0 != Y1)
    {
        VG_LITE_ERROR_HANDLER(_add_point_to_point_list(stroke_conversion, X1, Y1, vgcFLATTEN_START));
    }
    else if (X0 != X2 || Y0 != Y2)
    {
        VG_LITE_ERROR_HANDLER(_add_point_to_point_list(stroke_conversion, X2, Y2, vgcFLATTEN_START));
    }
    else
    {
        VG_LITE_ERROR_HANDLER(_add_point_to_point_list(stroke_conversion, X3, Y3, vgcFLATTEN_START));
    }
    point1 = stroke_conversion->path_last_point;
    /* Change the point1's coordinates back to P0. */
    point1->x = X0;
    point1->y = Y0;
    point0->length = 0.0f;

    for (int i = 0; i < num_curves; ++i) {
        fi = (vg_lite_float_t)i;
        t0 = fi / fnum_curves;
        t1 = (fi + 1.0) / fnum_curves;
        subsegment = cubic_bezier_split_at(&c, t0, t1);
        p1x = 3.0 * subsegment.X1 - subsegment.X0;
        p1y = 3.0 * subsegment.Y1 - subsegment.Y0;
        p2x = 3.0 * subsegment.X2 - subsegment.X3;
        p2y = 3.0 * subsegment.Y2 - subsegment.Y3;
        current_curve = (quad_bezier_t) {
            .X0 = subsegment.X0,
            .Y0 = subsegment.Y0,
            .X1 = (p1x + p2x) / 4.0,
            .Y1 = (p1y + p2y) / 4.0,
            .X2 = subsegment.X3,
            .Y2 = subsegment.Y3
        };
        params = quad_bezier_flatten_params_init(&current_curve, tolerance);
        for (int j = 0; j < params.num_points; ++j) {
            quad_bezier_flatten_at(&current_curve, &params, j, &x, &y);
            _add_point_to_point_list(stroke_conversion, x, y, vgcFLATTEN_MIDDLE);
        }
    }

    /* Add point 3 separately to avoid cumulative errors. */
    VG_LITE_ERROR_HANDLER(_add_point_to_point_list(stroke_conversion, X3, Y3, vgcFLATTEN_END));

    /* Add extra P3 for outgoing tangent. */
    /* First change P3(point0)'s coordinates to P0/P1/P2. */
    point0 = stroke_conversion->path_last_point;
    if (X3 != X2 || Y3 != Y2)
    {
        point0->x = X2;
        point0->y = Y2;
    }
    else if (X3 != X1 || Y3 != Y1)
    {
        point0->x = X1;
        point0->y = Y1;
    }
    else
    {
        point0->x = X0;
        point0->y = Y0;
    }

    /* Add P3 to calculate outgoing tangent. */
    VG_LITE_ERROR_HANDLER(_add_point_to_point_list(stroke_conversion, X3, Y3, vgcFLATTEN_NO));

    point1 = stroke_conversion->path_last_point;

    /* Change point0's coordinates back to P3. */
    point0->x = X3;
    point0->y = Y3;
    point0->length = 0.0f;

ErrorHandler:
    return error;
}
