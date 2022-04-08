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
#ifndef __ARM_COMPUTE_NEMATH_H__
#define __ARM_COMPUTE_NEMATH_H__


#if defined(ARM_MATH_NEON)
/** Calculate floor of a vector.
 *
 * @param[in] val Input vector value in F32 format.
 *
 * @return The calculated floor vector.
 */
static inline float32x4_t vfloorq_f32(float32x4_t val);

/** Calculate inverse square root.
 *
 * @param[in] x Input value.
 *
 * @return The calculated inverse square root.
 */
static inline float32x2_t vinvsqrt_f32(float32x2_t x);

/** Calculate inverse square root.
 *
 * @param[in] x Input value.
 *
 * @return The calculated inverse square root.
 */
static inline float32x4_t vinvsqrtq_f32(float32x4_t x);

/** Calculate reciprocal.
 *
 * @param[in] x Input value.
 *
 * @return The calculated reciprocal.
 */
static inline float32x2_t vinv_f32(float32x2_t x);

/** Calculate reciprocal.
 *
 * @param[in] x Input value.
 *
 * @return The calculated reciprocal.
 */
static inline float32x4_t vinvq_f32(float32x4_t x);

/** Perform a 7th degree polynomial approximation using Estrin's method.
 *
 * @param[in] x      Input vector value in F32 format.
 * @param[in] coeffs Polynomial coefficients table. (array of flattened float32x4_t vectors)
 *
 * @return The calculated approximation.
 */
static inline float32x4_t vtaylor_polyq_f32(float32x4_t x, const float32_t *coeffs);

/** Calculate exponential
 *
 * @param[in] x Input vector value in F32 format.
 *
 * @return The calculated exponent.
 */
static inline float32x4_t vexpq_f32(float32x4_t x);

/** Calculate logarithm
 *
 * @param[in] x Input vector value in F32 format.
 *
 * @return The calculated logarithm.
 */
static inline float32x4_t vlogq_f32(float32x4_t x);

/** Calculate hyperbolic tangent.
 *
 * tanh(x) = (e^2x - 1)/(e^2x + 1)
 *
 * @note We clamp x to [-5,5] to avoid overflowing issues.
 *
 * @param[in] val Input vector value in F32 format.
 *
 * @return The calculated Hyperbolic Tangent.
 */
static inline float32x4_t vtanhq_f32(float32x4_t val);

/** Calculate n power of a number.
 *
 * pow(x,n) = e^(n*log(x))
 *
 * @param[in] val Input vector value in F32 format.
 * @param[in] n   Powers to raise the input to.
 *
 * @return The calculated power.
 */
static inline float32x4_t vpowq_f32(float32x4_t val, float32x4_t n);

#ifdef __ARM_FEATURE_FP16_VECTOR_ARITHMETIC
/** Calculate hyperbolic tangent.
 *
 * tanh(x) = (e^2x - 1)/(e^2x + 1)
 *
 * @note We clamp x to [-5,5] to avoid overflowing issues.
 *
 * @param[in] val Input vector value in F32 format.
 *
 * @return The calculated Hyperbolic Tangent.
 */
static inline float16x8_t vtanhq_f16(float16x8_t val);

/** Calculate reciprocal.
 *
 * @param[in] x Input value.
 *
 * @return The calculated reciprocal.
 */
static inline float16x4_t vinv_f16(float16x4_t x);

/** Calculate reciprocal.
 *
 * @param[in] x Input value.
 *
 * @return The calculated reciprocal.
 */
static inline float16x8_t vinvq_f16(float16x8_t x);

/** Calculate inverse square root.
 *
 * @param[in] x Input value.
 *
 * @return The calculated inverse square root.
 */
static inline float16x4_t vinvsqrt_f16(float16x4_t x);

/** Calculate inverse square root.
 *
 * @param[in] x Input value.
 *
 * @return The calculated inverse square root.
 */
static inline float16x8_t vinvsqrtq_f16(float16x8_t x);

/** Calculate exponential
 *
 * @param[in] x Input vector value in F16 format.
 *
 * @return The calculated exponent.
 */
static inline float16x8_t vexpq_f16(float16x8_t x);

/** Calculate n power of a number.
 *
 * pow(x,n) = e^(n*log(x))
 *
 * @param[in] val Input vector value in F16 format.
 * @param[in] n   Powers to raise the input to.
 *
 * @return The calculated power.
 */
static inline float16x8_t vpowq_f16(float16x8_t val, float16x8_t n);
#endif /* __ARM_FEATURE_FP16_VECTOR_ARITHMETIC */

/** Exponent polynomial coefficients */
extern const float32_t exp_tab[4*8];


/** Logarithm polynomial coefficients */
extern const float32_t log_tab[4*8];

#ifndef DOXYGEN_SKIP_THIS
inline float32x4_t vfloorq_f32(float32x4_t val)
{
    static const float32_t CONST_1[4] = {1.f,1.f,1.f,1.f};

    const int32x4_t   z = vcvtq_s32_f32(val);
    const float32x4_t r = vcvtq_f32_s32(z);

    return vbslq_f32(vcgtq_f32(r, val), vsubq_f32(r, vld1q_f32(CONST_1)), r);
}

inline float32x2_t vinvsqrt_f32(float32x2_t x)
{
    float32x2_t sqrt_reciprocal = vrsqrte_f32(x);
    sqrt_reciprocal             = vmul_f32(vrsqrts_f32(vmul_f32(x, sqrt_reciprocal), sqrt_reciprocal), sqrt_reciprocal);
    sqrt_reciprocal             = vmul_f32(vrsqrts_f32(vmul_f32(x, sqrt_reciprocal), sqrt_reciprocal), sqrt_reciprocal);

    return sqrt_reciprocal;
}

inline float32x4_t vinvsqrtq_f32(float32x4_t x)
{
    float32x4_t sqrt_reciprocal = vrsqrteq_f32(x);
    sqrt_reciprocal             = vmulq_f32(vrsqrtsq_f32(vmulq_f32(x, sqrt_reciprocal), sqrt_reciprocal), sqrt_reciprocal);
    sqrt_reciprocal             = vmulq_f32(vrsqrtsq_f32(vmulq_f32(x, sqrt_reciprocal), sqrt_reciprocal), sqrt_reciprocal);

    return sqrt_reciprocal;
}

inline float32x2_t vinv_f32(float32x2_t x)
{
    float32x2_t recip = vrecpe_f32(x);
    recip             = vmul_f32(vrecps_f32(x, recip), recip);
    recip             = vmul_f32(vrecps_f32(x, recip), recip);
    return recip;
}

inline float32x4_t vinvq_f32(float32x4_t x)
{
    float32x4_t recip = vrecpeq_f32(x);
    recip             = vmulq_f32(vrecpsq_f32(x, recip), recip);
    recip             = vmulq_f32(vrecpsq_f32(x, recip), recip);
    return recip;
}

inline float32x4_t vtaylor_polyq_f32(float32x4_t x, const float32_t *coeffs)
{
    float32x4_t A   = vmlaq_f32(vld1q_f32(&coeffs[4*0]), vld1q_f32(&coeffs[4*4]), x);
    float32x4_t B   = vmlaq_f32(vld1q_f32(&coeffs[4*2]), vld1q_f32(&coeffs[4*6]), x);
    float32x4_t C   = vmlaq_f32(vld1q_f32(&coeffs[4*1]), vld1q_f32(&coeffs[4*5]), x);
    float32x4_t D   = vmlaq_f32(vld1q_f32(&coeffs[4*3]), vld1q_f32(&coeffs[4*7]), x);
    float32x4_t x2  = vmulq_f32(x, x);
    float32x4_t x4  = vmulq_f32(x2, x2);
    float32x4_t res = vmlaq_f32(vmlaq_f32(A, B, x2), vmlaq_f32(C, D, x2), x4);
    return res;
}

inline float32x4_t vexpq_f32(float32x4_t x)
{
    static const float32_t CONST_LN2[4]          = {0.6931471805f,0.6931471805f,0.6931471805f,0.6931471805f}; // ln(2)
    static const float32_t CONST_INV_LN2[4]      = {1.4426950408f,1.4426950408f,1.4426950408f,1.4426950408f}; // 1/ln(2)
    static const float32_t CONST_0[4]            = {0.f,0.f,0.f,0.f};
    static const int32_t   CONST_NEGATIVE_126[4] = {-126,-126,-126,-126};

    // Perform range reduction [-log(2),log(2)]
    int32x4_t   m   = vcvtq_s32_f32(vmulq_f32(x, vld1q_f32(CONST_INV_LN2)));
    float32x4_t val = vmlsq_f32(x, vcvtq_f32_s32(m), vld1q_f32(CONST_LN2));

    // Polynomial Approximation
    float32x4_t poly = vtaylor_polyq_f32(val, exp_tab);

    // Reconstruct
    poly = vreinterpretq_f32_s32(vqaddq_s32(vreinterpretq_s32_f32(poly), vqshlq_n_s32(m, 23)));
    poly = vbslq_f32(vcltq_s32(m, vld1q_s32(CONST_NEGATIVE_126)), vld1q_f32(CONST_0), poly);

    return poly;
}

inline float32x4_t vlogq_f32(float32x4_t x)
{
    static const int32_t   CONST_127[4] = {127,127,127,127};           // 127
    static const float32_t CONST_LN2[4] = {0.6931471805f,0.6931471805f,0.6931471805f,0.6931471805f}; // ln(2)

    // Extract exponent
    int32x4_t   m   = vsubq_s32(vreinterpretq_s32_u32(vshrq_n_u32(vreinterpretq_u32_f32(x), 23)), vld1q_s32(CONST_127));
    float32x4_t val = vreinterpretq_f32_s32(vsubq_s32(vreinterpretq_s32_f32(x), vshlq_n_s32(m, 23)));

    // Polynomial Approximation
    float32x4_t poly = vtaylor_polyq_f32(val, log_tab);

    // Reconstruct
    poly = vmlaq_f32(poly, vcvtq_f32_s32(m), vld1q_f32(CONST_LN2));

    return poly;
}

inline float32x4_t vtanhq_f32(float32x4_t val)
{
    static const float32_t CONST_1[4]        = {1.f,1.f,1.f,1.f};
    static const float32_t CONST_2[4]        = {2.f,2.f,2.f,2.f};
    static const float32_t CONST_MIN_TANH[4] = {-10.f,-10.f,-10.f,-10.f};
    static const float32_t CONST_MAX_TANH[4] = {10.f,10.f,10.f,10.f};

    float32x4_t x     = vminq_f32(vmaxq_f32(val, vld1q_f32(CONST_MIN_TANH)), vld1q_f32(CONST_MAX_TANH));
    float32x4_t exp2x = vexpq_f32(vmulq_f32(vld1q_f32(CONST_2), x));
    float32x4_t num   = vsubq_f32(exp2x, vld1q_f32(CONST_1));
    float32x4_t den   = vaddq_f32(exp2x, vld1q_f32(CONST_1));
    float32x4_t tanh  = vmulq_f32(num, vinvq_f32(den));
    return tanh;
}

inline float32x4_t vpowq_f32(float32x4_t val, float32x4_t n)
{
    return vexpq_f32(vmulq_f32(n, vlogq_f32(val)));
}
#endif /* DOXYGEN_SKIP_THIS */

#ifdef __ARM_FEATURE_FP16_VECTOR_ARITHMETIC
/** Exponent polynomial coefficients */
/** Logarithm polynomial coefficients */
#ifndef DOXYGEN_SKIP_THIS
inline float16x8_t vfloorq_f16(float16x8_t val)
{
    static const float16_t CONST_1[8] = {1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f};

    const int16x8_t   z = vcvtq_s16_f16(val);
    const float16x8_t r = vcvtq_f16_s16(z);

    return vbslq_f16(vcgtq_f16(r, val), vsubq_f16(r, vld1q_f16(CONST_1)), r);
}
inline float16x4_t vinvsqrt_f16(float16x4_t x)
{
    float16x4_t sqrt_reciprocal = vrsqrte_f16(x);
    sqrt_reciprocal             = vmul_f16(vrsqrts_f16(vmul_f16(x, sqrt_reciprocal), sqrt_reciprocal), sqrt_reciprocal);
    sqrt_reciprocal             = vmul_f16(vrsqrts_f16(vmul_f16(x, sqrt_reciprocal), sqrt_reciprocal), sqrt_reciprocal);
    return sqrt_reciprocal;
}

inline float16x8_t vinvsqrtq_f16(float16x8_t x)
{
    float16x8_t sqrt_reciprocal = vrsqrteq_f16(x);
    sqrt_reciprocal             = vmulq_f16(vrsqrtsq_f16(vmulq_f16(x, sqrt_reciprocal), sqrt_reciprocal), sqrt_reciprocal);
    sqrt_reciprocal             = vmulq_f16(vrsqrtsq_f16(vmulq_f16(x, sqrt_reciprocal), sqrt_reciprocal), sqrt_reciprocal);
    return sqrt_reciprocal;
}

inline float16x4_t vinv_f16(float16x4_t x)
{
    float16x4_t recip = vrecpe_f16(x);
    recip             = vmul_f16(vrecps_f16(x, recip), recip);
    recip             = vmul_f16(vrecps_f16(x, recip), recip);
    return recip;
}

inline float16x8_t vinvq_f16(float16x8_t x)
{
    float16x8_t recip = vrecpeq_f16(x);
    recip             = vmulq_f16(vrecpsq_f16(x, recip), recip);
    recip             = vmulq_f16(vrecpsq_f16(x, recip), recip);
    return recip;
}

inline float16x8_t vtanhq_f16(float16x8_t val)
{
    const float16_t CONST_1[8]        = {1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f};
    const float16_t CONST_2[8]        = {2.f,2.f,2.f,2.f,2.f,2.f,2.f,2.f};
    const float16_t CONST_MIN_TANH[8] = {-10.f,-10.f,-10.f,-10.f,-10.f,-10.f,-10.f,-10.f};
    const float16_t CONST_MAX_TANH[8] = {10.f,10.f,10.f,10.f,10.f,10.f,10.f,10.f};

    const float16x8_t x     = vminq_f16(vmaxq_f16(val, vld1q_f16(CONST_MIN_TANH)), vld1q_f16(CONST_MAX_TANH));
    const float16x8_t exp2x = vexpq_f16(vmulq_f16(vld1q_f16(CONST_2), x));
    const float16x8_t num   = vsubq_f16(exp2x, vld1q_f16(CONST_1));
    const float16x8_t den   = vaddq_f16(exp2x, vld1q_f16(CONST_1));
    const float16x8_t tanh  = vmulq_f16(num, vinvq_f16(den));
    return tanh;
}

inline float16x8_t vtaylor_polyq_f16(float16x8_t x, const float16_t *coeffs)
{
    const float16x8_t A   = vaddq_f16(&coeffs[8*0], vmulq_f16(&coeffs[8*4], x));
    const float16x8_t B   = vaddq_f16(&coeffs[8*2], vmulq_f16(&coeffs[8*6], x));
    const float16x8_t C   = vaddq_f16(&coeffs[8*1], vmulq_f16(&coeffs[8*5], x));
    const float16x8_t D   = vaddq_f16(&coeffs[8*3], vmulq_f16(&coeffs[8*7], x));
    const float16x8_t x2  = vmulq_f16(x, x);
    const float16x8_t x4  = vmulq_f16(x2, x2);
    const float16x8_t res = vaddq_f16(vaddq_f16(A, vmulq_f16(B, x2)), vmulq_f16(vaddq_f16(C, vmulq_f16(D, x2)), x4));
    return res;
}

inline float16x8_t vexpq_f16(float16x8_t x)
{
    // TODO (COMPMID-1535) : Revisit FP16 approximations
    const float32x4_t x_high = vcvt_f32_f16(vget_high_f16(x));
    const float32x4_t x_low  = vcvt_f32_f16(vget_low_f16(x));

    const float16x8_t res = vcvt_high_f16_f32(vcvt_f16_f32(vexpq_f32(x_low)), vexpq_f32(x_high));
    return res;
}

inline float16x8_t vlogq_f16(float16x8_t x)
{
    // TODO (COMPMID-1535) : Revisit FP16 approximations
    const float32x4_t x_high = vcvt_f32_f16(vget_high_f16(x));
    const float32x4_t x_low  = vcvt_f32_f16(vget_low_f16(x));

    const float16x8_t res = vcvt_high_f16_f32(vcvt_f16_f32(vlogq_f32(x_low)), vlogq_f32(x_high));
    return res;
}

inline float16x8_t vpowq_f16(float16x8_t val, float16x8_t n)
{
    // TODO (giaiod01) - COMPMID-1535
    float32x4_t n0_f32   = vcvt_f32_f16(vget_low_f16(n));
    float32x4_t n1_f32   = vcvt_f32_f16(vget_high_f16(n));
    float32x4_t val0_f32 = vcvt_f32_f16(vget_low_f16(val));
    float32x4_t val1_f32 = vcvt_f32_f16(vget_high_f16(val));

    float32x4_t res0_f32 = vexpq_f32(vmulq_f32(n0_f32, vlogq_f32(val0_f32)));
    float32x4_t res1_f32 = vexpq_f32(vmulq_f32(n1_f32, vlogq_f32(val1_f32)));

    return vcombine_f16(vcvt_f16_f32(res0_f32), vcvt_f16_f32(res1_f32));
}
#endif /* DOXYGEN_SKIP_THIS */
#endif /* __ARM_FEATURE_FP16_VECTOR_ARITHMETIC */
#endif
#endif /* __ARM_COMPUTE_NEMATH_H__ */
