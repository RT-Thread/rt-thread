/*
 * Copyright (c) 2016, 2019 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "arm_math.h"
#include "NEMath.h"

#if defined(ARM_MATH_NEON)

/** Exponent polynomial coefficients */
const float32_t exp_tab[4*8] =
{
        1.f,1.f,1.f,1.f,
        0.0416598916054f,0.0416598916054f,0.0416598916054f,0.0416598916054f,
        0.500000596046f,0.500000596046f,0.500000596046f,0.500000596046f,
        0.0014122662833f,0.0014122662833f,0.0014122662833f,0.0014122662833f,
        1.00000011921f,1.00000011921f,1.00000011921f,1.00000011921f,
        0.00833693705499f,0.00833693705499f,0.00833693705499f,0.00833693705499f,
        0.166665703058f,0.166665703058f,0.166665703058f,0.166665703058f,
        0.000195780929062f,0.000195780929062f,0.000195780929062f,0.000195780929062f
};

/** Logarithm polynomial coefficients */
const float32_t log_tab[4*8] =
{
        -2.29561495781f,-2.29561495781f,-2.29561495781f,-2.29561495781f,
        -2.47071170807f,-2.47071170807f,-2.47071170807f,-2.47071170807f,
        -5.68692588806f,-5.68692588806f,-5.68692588806f,-5.68692588806f,
        -0.165253549814f,-0.165253549814f,-0.165253549814f,-0.165253549814f,
        5.17591238022f,5.17591238022f,5.17591238022f,5.17591238022f,
        0.844007015228f,0.844007015228f,0.844007015228f,0.844007015228f,
        4.58445882797f,4.58445882797f,4.58445882797f,4.58445882797f,
        0.0141278216615f,0.0141278216615f,0.0141278216615f,0.0141278216615f
};

#endif
