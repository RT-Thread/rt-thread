/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */

/*******************************************************************************
 *
 * $Id:$
 *
 ******************************************************************************/

/**
 *   @defgroup  ML_MATH_FUNC ml_math_func
 *   @brief     Motion Library - Math Functions
 *              Common math functions the Motion Library
 *
 *   @{
 *       @file ml_math_func.c
 *       @brief Math Functions.
 */

#include "mlmath.h"
#include "ml_math_func.h"
#include "mlinclude.h"
#include <string.h>

#ifdef EMPL
#define TABLE_SIZE (256)

/* TODO: If memory becomes a big issue, we can just store the data for a single
 * quadrant and transform the inputs and outputs of the lookup functions.
 */
const float sin_lookup[TABLE_SIZE] = {
    0.000000f, 0.024541f, 0.049068f, 0.073565f, 0.098017f, 0.122411f, 0.146730f, 0.170962f,
    0.195090f, 0.219101f, 0.242980f, 0.266713f, 0.290285f, 0.313682f, 0.336890f, 0.359895f,
    0.382683f, 0.405241f, 0.427555f, 0.449611f, 0.471397f, 0.492898f, 0.514103f, 0.534998f,
    0.555570f, 0.575808f, 0.595699f, 0.615232f, 0.634393f, 0.653173f, 0.671559f, 0.689541f,
    0.707107f, 0.724247f, 0.740951f, 0.757209f, 0.773010f, 0.788346f, 0.803208f, 0.817585f,
    0.831470f, 0.844854f, 0.857729f, 0.870087f, 0.881921f, 0.893224f, 0.903989f, 0.914210f,
    0.923880f, 0.932993f, 0.941544f, 0.949528f, 0.956940f, 0.963776f, 0.970031f, 0.975702f,
    0.980785f, 0.985278f, 0.989177f, 0.992480f, 0.995185f, 0.997290f, 0.998795f, 0.999699f,
    1.000000f, 0.999699f, 0.998795f, 0.997290f, 0.995185f, 0.992480f, 0.989177f, 0.985278f,
    0.980785f, 0.975702f, 0.970031f, 0.963776f, 0.956940f, 0.949528f, 0.941544f, 0.932993f,
    0.923880f, 0.914210f, 0.903989f, 0.893224f, 0.881921f, 0.870087f, 0.857729f, 0.844854f,
    0.831470f, 0.817585f, 0.803208f, 0.788346f, 0.773010f, 0.757209f, 0.740951f, 0.724247f,
    0.707107f, 0.689541f, 0.671559f, 0.653173f, 0.634393f, 0.615232f, 0.595699f, 0.575808f,
    0.555570f, 0.534998f, 0.514103f, 0.492898f, 0.471397f, 0.449611f, 0.427555f, 0.405241f,
    0.382683f, 0.359895f, 0.336890f, 0.313682f, 0.290285f, 0.266713f, 0.242980f, 0.219101f,
    0.195091f, 0.170962f, 0.146731f, 0.122411f, 0.098017f, 0.073565f, 0.049068f, 0.024541f,
    0.000000f, -0.024541f, -0.049067f, -0.073564f, -0.098017f, -0.122411f, -0.146730f, -0.170962f,
    -0.195090f, -0.219101f, -0.242980f, -0.266713f, -0.290284f, -0.313682f, -0.336890f, -0.359895f,
    -0.382683f, -0.405241f, -0.427555f, -0.449611f, -0.471397f, -0.492898f, -0.514103f, -0.534997f,
    -0.555570f, -0.575808f, -0.595699f, -0.615231f, -0.634393f, -0.653173f, -0.671559f, -0.689540f,
    -0.707107f, -0.724247f, -0.740951f, -0.757209f, -0.773010f, -0.788346f, -0.803207f, -0.817585f,
    -0.831469f, -0.844853f, -0.857729f, -0.870087f, -0.881921f, -0.893224f, -0.903989f, -0.914210f,
    -0.923880f, -0.932993f, -0.941544f, -0.949528f, -0.956940f, -0.963776f, -0.970031f, -0.975702f,
    -0.980785f, -0.985278f, -0.989176f, -0.992480f, -0.995185f, -0.997290f, -0.998795f, -0.999699f,
    -1.000000f, -0.999699f, -0.998795f, -0.997290f, -0.995185f, -0.992480f, -0.989177f, -0.985278f,
    -0.980785f, -0.975702f, -0.970031f, -0.963776f, -0.956940f, -0.949528f, -0.941544f, -0.932993f,
    -0.923880f, -0.914210f, -0.903989f, -0.893224f, -0.881921f, -0.870087f, -0.857729f, -0.844854f,
    -0.831470f, -0.817585f, -0.803208f, -0.788347f, -0.773011f, -0.757209f, -0.740951f, -0.724247f,
    -0.707107f, -0.689541f, -0.671559f, -0.653173f, -0.634394f, -0.615232f, -0.595699f, -0.575808f,
    -0.555570f, -0.534998f, -0.514103f, -0.492898f, -0.471397f, -0.449612f, -0.427555f, -0.405241f,
    -0.382684f, -0.359895f, -0.336890f, -0.313682f, -0.290285f, -0.266713f, -0.242981f, -0.219102f,
    -0.195091f, -0.170962f, -0.146731f, -0.122411f, -0.098017f, -0.073565f, -0.049068f, -0.024542f
};

float inv_sinf(float x)
{
    int index = (unsigned int)((x * (TABLE_SIZE>>1)) / 3.14159f) % TABLE_SIZE;
    return sin_lookup[index];
}

float inv_cosf(float x)
{
    int index = ((unsigned int)((x * (TABLE_SIZE>>1)) / 3.14159f) + (TABLE_SIZE>>2)) % TABLE_SIZE;
    return sin_lookup[index];
}
#endif

/** @internal
 * Does the cross product of compass by gravity, then converts that
 * to the world frame using the quaternion, then computes the angle that
 * is made.
 *
 * @param[in] compass Compass Vector (Body Frame), length 3
 * @param[in] grav Gravity Vector (Body Frame), length 3
 * @param[in] quat Quaternion, Length 4
 * @return Angle Cross Product makes after quaternion rotation.
 */
float inv_compass_angle(const long *compass, const long *grav, const long *quat)
{
    long cgcross[4], q1[4], q2[4], qi[4];
    float angW;

    // Compass cross Gravity
    cgcross[0] = 0L;
    cgcross[1] = inv_q30_mult(compass[1], grav[2]) - inv_q30_mult(compass[2], grav[1]);
    cgcross[2] = inv_q30_mult(compass[2], grav[0]) - inv_q30_mult(compass[0], grav[2]);
    cgcross[3] = inv_q30_mult(compass[0], grav[1]) - inv_q30_mult(compass[1], grav[0]);

    // Now convert cross product into world frame
    inv_q_mult(quat, cgcross, q1);
    inv_q_invert(quat, qi);
    inv_q_mult(q1, qi, q2);

    // Protect against atan2 of 0,0
    if ((q2[2] == 0L) && (q2[1] == 0L))
        return 0.f;

    // This is the unfiltered heading correction
    angW = -atan2f(inv_q30_to_float(q2[2]), inv_q30_to_float(q2[1]));
    return angW;
}

/**
 *  @brief  The gyro data magnitude squared :
 *          (1 degree per second)^2 = 2^6 = 2^GYRO_MAG_SQR_SHIFT.
 * @param[in] gyro Gyro data scaled with 1 dps = 2^16
 *  @return the computed magnitude squared output of the gyroscope.
 */
unsigned long inv_get_gyro_sum_of_sqr(const long *gyro)
{
    unsigned long gmag = 0;
    long temp;
    int kk;

    for (kk = 0; kk < 3; ++kk) {
        temp = gyro[kk] >> (16 - (GYRO_MAG_SQR_SHIFT / 2));
        gmag += temp * temp;
    }

    return gmag;
}

/** Performs a multiply and shift by 29. These are good functions to write in assembly on
 * with devices with small memory where you want to get rid of the long long which some
 * assemblers don't handle well
 * @param[in] a
 * @param[in] b
 * @return ((long long)a*b)>>29
*/
long inv_q29_mult(long a, long b)
{
#ifdef EMPL_NO_64BIT
    long result;
    result = (long)((float)a * b / (1L << 29));
    return result;
#else
    long long temp;
    long result;
    temp = (long long)a * b;
    result = (long)(temp >> 29);
    return result;
#endif
}

/** Performs a multiply and shift by 30. These are good functions to write in assembly on
 * with devices with small memory where you want to get rid of the long long which some
 * assemblers don't handle well
 * @param[in] a
 * @param[in] b
 * @return ((long long)a*b)>>30
*/
long inv_q30_mult(long a, long b)
{
#ifdef EMPL_NO_64BIT
    long result;
    result = (long)((float)a * b / (1L << 30));
    return result;
#else
    long long temp;
    long result;
    temp = (long long)a * b;
    result = (long)(temp >> 30);
    return result;
#endif
}

#ifndef EMPL_NO_64BIT
long inv_q30_div(long a, long b)
{
    long long temp;
    long result;
    temp = (((long long)a) << 30) / b;
    result = (long)temp;
    return result;
}
#endif

/** Performs a multiply and shift by shift. These are good functions to write
 * in assembly on with devices with small memory where you want to get rid of
 * the long long which some assemblers don't handle well
 * @param[in] a First multicand
 * @param[in] b Second multicand
 * @param[in] shift Shift amount after multiplying
 * @return ((long long)a*b)<<shift
*/
#ifndef EMPL_NO_64BIT
long inv_q_shift_mult(long a, long b, int shift)
{
    long result;
    result = (long)(((long long)a * b) >> shift);
    return result;
}
#endif

/** Performs a fixed point quaternion multiply.
* @param[in] q1 First Quaternion Multicand, length 4. 1.0 scaled
*            to 2^30
* @param[in] q2 Second Quaternion Multicand, length 4. 1.0 scaled
*            to 2^30
* @param[out] qProd Product after quaternion multiply. Length 4.
*             1.0 scaled to 2^30.
*/
void inv_q_mult(const long *q1, const long *q2, long *qProd)
{
    INVENSENSE_FUNC_START;
    qProd[0] = inv_q30_mult(q1[0], q2[0]) - inv_q30_mult(q1[1], q2[1]) -
               inv_q30_mult(q1[2], q2[2]) - inv_q30_mult(q1[3], q2[3]);

    qProd[1] = inv_q30_mult(q1[0], q2[1]) + inv_q30_mult(q1[1], q2[0]) +
               inv_q30_mult(q1[2], q2[3]) - inv_q30_mult(q1[3], q2[2]);

    qProd[2] = inv_q30_mult(q1[0], q2[2]) - inv_q30_mult(q1[1], q2[3]) +
               inv_q30_mult(q1[2], q2[0]) + inv_q30_mult(q1[3], q2[1]);

    qProd[3] = inv_q30_mult(q1[0], q2[3]) + inv_q30_mult(q1[1], q2[2]) -
               inv_q30_mult(q1[2], q2[1]) + inv_q30_mult(q1[3], q2[0]);
}

/** Performs a fixed point quaternion addition.
* @param[in] q1 First Quaternion term, length 4. 1.0 scaled
*            to 2^30
* @param[in] q2 Second Quaternion term, length 4. 1.0 scaled
*            to 2^30
* @param[out] qSum Sum after quaternion summation. Length 4.
*             1.0 scaled to 2^30.
*/
void inv_q_add(long *q1, long *q2, long *qSum)
{
    INVENSENSE_FUNC_START;
    qSum[0] = q1[0] + q2[0];
    qSum[1] = q1[1] + q2[1];
    qSum[2] = q1[2] + q2[2];
    qSum[3] = q1[3] + q2[3];
}

void inv_vector_normalize(long *vec, int length)
{
    INVENSENSE_FUNC_START;
    double normSF = 0;
    int ii;
    for (ii = 0; ii < length; ii++) {
        normSF +=
            inv_q30_to_double(vec[ii]) * inv_q30_to_double(vec[ii]);
    }
    if (normSF > 0) {
        normSF = 1 / sqrt(normSF);
        for (ii = 0; ii < length; ii++) {
            vec[ii] = (int)((double)vec[ii] * normSF);
        }
    } else {
        vec[0] = 1073741824L;
        for (ii = 1; ii < length; ii++) {
            vec[ii] = 0;
        }
    }
}

void inv_q_normalize(long *q)
{
    INVENSENSE_FUNC_START;
    inv_vector_normalize(q, 4);
}

void inv_q_invert(const long *q, long *qInverted)
{
    INVENSENSE_FUNC_START;
    qInverted[0] = q[0];
    qInverted[1] = -q[1];
    qInverted[2] = -q[2];
    qInverted[3] = -q[3];
}

double quaternion_to_rotation_angle(const long *quat) {
    double quat0 = (double )quat[0] / 1073741824;
    if (quat0 > 1.0f) {
        quat0 = 1.0;
    } else if (quat0 < -1.0f) {
        quat0 = -1.0;
    }

    return acos(quat0)*2*180/M_PI;
}

/** Rotates a 3-element vector by Rotation defined by Q
*/
void inv_q_rotate(const long *q, const long *in, long *out)
{
    long q_temp1[4], q_temp2[4];
    long in4[4], out4[4];

    // Fixme optimize
    in4[0] = 0;
    memcpy(&in4[1], in, 3 * sizeof(long));
    inv_q_mult(q, in4, q_temp1);
    inv_q_invert(q, q_temp2);
    inv_q_mult(q_temp1, q_temp2, out4);
    memcpy(out, &out4[1], 3 * sizeof(long));
}

void inv_q_multf(const float *q1, const float *q2, float *qProd)
{
    INVENSENSE_FUNC_START;
    qProd[0] =
        (q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2] - q1[3] * q2[3]);
    qProd[1] =
        (q1[0] * q2[1] + q1[1] * q2[0] + q1[2] * q2[3] - q1[3] * q2[2]);
    qProd[2] =
        (q1[0] * q2[2] - q1[1] * q2[3] + q1[2] * q2[0] + q1[3] * q2[1]);
    qProd[3] =
        (q1[0] * q2[3] + q1[1] * q2[2] - q1[2] * q2[1] + q1[3] * q2[0]);
}

void inv_q_addf(const float *q1, const float *q2, float *qSum)
{
    INVENSENSE_FUNC_START;
    qSum[0] = q1[0] + q2[0];
    qSum[1] = q1[1] + q2[1];
    qSum[2] = q1[2] + q2[2];
    qSum[3] = q1[3] + q2[3];
}

void inv_q_normalizef(float *q)
{
    INVENSENSE_FUNC_START;
    float normSF = 0;
    float xHalf = 0;
    normSF = (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
    if (normSF < 2) {
        xHalf = 0.5f * normSF;
        normSF = normSF * (1.5f - xHalf * normSF * normSF);
        normSF = normSF * (1.5f - xHalf * normSF * normSF);
        normSF = normSF * (1.5f - xHalf * normSF * normSF);
        normSF = normSF * (1.5f - xHalf * normSF * normSF);
        q[0] *= normSF;
        q[1] *= normSF;
        q[2] *= normSF;
        q[3] *= normSF;
    } else {
        q[0] = 1.0;
        q[1] = 0.0;
        q[2] = 0.0;
        q[3] = 0.0;
    }
    normSF = (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
}

/** Performs a length 4 vector normalization with a square root.
* @param[in,out] q vector to normalize. Returns [1,0,0,0] is magnitude is zero.
*/
void inv_q_norm4(float *q)
{
    float mag;
    mag = sqrtf(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
    if (mag) {
        q[0] /= mag;
        q[1] /= mag;
        q[2] /= mag;
        q[3] /= mag;
    } else {
        q[0] = 1.f;
        q[1] = 0.f;
        q[2] = 0.f;
        q[3] = 0.f;
    }
}

void inv_q_invertf(const float *q, float *qInverted)
{
    INVENSENSE_FUNC_START;
    qInverted[0] = q[0];
    qInverted[1] = -q[1];
    qInverted[2] = -q[2];
    qInverted[3] = -q[3];
}

/**
 * Converts a quaternion to a rotation matrix.
 * @param[in] quat 4-element quaternion in fixed point. One is 2^30.
 * @param[out] rot Rotation matrix in fixed point. One is 2^30. The
 *             First 3 elements of the rotation matrix, represent
 *             the first row of the matrix. Rotation matrix multiplied
 *             by a 3 element column vector transform a vector from Body
 *             to World.
 */
void inv_quaternion_to_rotation(const long *quat, long *rot)
{
    rot[0] =
        inv_q29_mult(quat[1], quat[1]) + inv_q29_mult(quat[0],
                quat[0]) -
        1073741824L;
    rot[1] =
        inv_q29_mult(quat[1], quat[2]) - inv_q29_mult(quat[3], quat[0]);
    rot[2] =
        inv_q29_mult(quat[1], quat[3]) + inv_q29_mult(quat[2], quat[0]);
    rot[3] =
        inv_q29_mult(quat[1], quat[2]) + inv_q29_mult(quat[3], quat[0]);
    rot[4] =
        inv_q29_mult(quat[2], quat[2]) + inv_q29_mult(quat[0],
                quat[0]) -
        1073741824L;
    rot[5] =
        inv_q29_mult(quat[2], quat[3]) - inv_q29_mult(quat[1], quat[0]);
    rot[6] =
        inv_q29_mult(quat[1], quat[3]) - inv_q29_mult(quat[2], quat[0]);
    rot[7] =
        inv_q29_mult(quat[2], quat[3]) + inv_q29_mult(quat[1], quat[0]);
    rot[8] =
        inv_q29_mult(quat[3], quat[3]) + inv_q29_mult(quat[0],
                quat[0]) -
        1073741824L;
}

/**
 * Converts a quaternion to a rotation vector. A rotation vector is
 * a method to represent a 4-element quaternion vector in 3-elements.
 * To get the quaternion from the 3-elements, The last 3-elements of
 * the quaternion will be the given rotation vector. The first element
 * of the quaternion will be the positive value that will be required
 * to make the magnitude of the quaternion 1.0 or 2^30 in fixed point units.
 * @param[in] quat 4-element quaternion in fixed point. One is 2^30.
 * @param[out] rot Rotation vector in fixed point. One is 2^30.
 */
void inv_quaternion_to_rotation_vector(const long *quat, long *rot)
{
    rot[0] = quat[1];
    rot[1] = quat[2];
    rot[2] = quat[3];

    if (quat[0] < 0.0) {
        rot[0] = -rot[0];
        rot[1] = -rot[1];
        rot[2] = -rot[2];
    }
}

/** Converts a 32-bit long to a big endian byte stream */
unsigned char *inv_int32_to_big8(long x, unsigned char *big8)
{
    big8[0] = (unsigned char)((x >> 24) & 0xff);
    big8[1] = (unsigned char)((x >> 16) & 0xff);
    big8[2] = (unsigned char)((x >> 8) & 0xff);
    big8[3] = (unsigned char)(x & 0xff);
    return big8;
}

/** Converts a big endian byte stream into a 32-bit long */
long inv_big8_to_int32(const unsigned char *big8)
{
    long x;
    x = ((long)big8[0] << 24) | ((long)big8[1] << 16) | ((long)big8[2] << 8)
        | ((long)big8[3]);
    return x;
}

/** Converts a big endian byte stream into a 16-bit integer (short) */
short inv_big8_to_int16(const unsigned char *big8)
{
    short x;
    x = ((short)big8[0] << 8) | ((short)big8[1]);
    return x;
}

/** Converts a little endian byte stream into a 16-bit integer (short) */
short inv_little8_to_int16(const unsigned char *little8)
{
    short x;
    x = ((short)little8[1] << 8) | ((short)little8[0]);
    return x;
}

/** Converts a 16-bit short to a big endian byte stream */
unsigned char *inv_int16_to_big8(short x, unsigned char *big8)
{
    big8[0] = (unsigned char)((x >> 8) & 0xff);
    big8[1] = (unsigned char)(x & 0xff);
    return big8;
}

void inv_matrix_det_inc(float *a, float *b, int *n, int x, int y)
{
    int k, l, i, j;
    for (i = 0, k = 0; i < *n; i++, k++) {
        for (j = 0, l = 0; j < *n; j++, l++) {
            if (i == x)
                i++;
            if (j == y)
                j++;
            *(b + 6 * k + l) = *(a + 6 * i + j);
        }
    }
    *n = *n - 1;
}

void inv_matrix_det_incd(double *a, double *b, int *n, int x, int y)
{
    int k, l, i, j;
    for (i = 0, k = 0; i < *n; i++, k++) {
        for (j = 0, l = 0; j < *n; j++, l++) {
            if (i == x)
                i++;
            if (j == y)
                j++;
            *(b + 6 * k + l) = *(a + 6 * i + j);
        }
    }
    *n = *n - 1;
}

float inv_matrix_det(float *p, int *n)
{
    float d[6][6], sum = 0;
    int i, j, m;
    m = *n;
    if (*n == 2)
        return (*p ** (p + 7) - *(p + 1) ** (p + 6));
    for (i = 0, j = 0; j < m; j++) {
        *n = m;
        inv_matrix_det_inc(p, &d[0][0], n, i, j);
        sum =
            sum + *(p + 6 * i + j) * SIGNM(i +
                                            j) *
            inv_matrix_det(&d[0][0], n);
    }

    return (sum);
}

double inv_matrix_detd(double *p, int *n)
{
    double d[6][6], sum = 0;
    int i, j, m;
    m = *n;
    if (*n == 2)
        return (*p ** (p + 7) - *(p + 1) ** (p + 6));
    for (i = 0, j = 0; j < m; j++) {
        *n = m;
        inv_matrix_det_incd(p, &d[0][0], n, i, j);
        sum =
            sum + *(p + 6 * i + j) * SIGNM(i +
                                            j) *
            inv_matrix_detd(&d[0][0], n);
    }

    return (sum);
}

/** Wraps angle from (-M_PI,M_PI]
 * @param[in] ang Angle in radians to wrap
 * @return Wrapped angle from (-M_PI,M_PI]
 */
float inv_wrap_angle(float ang)
{
    if (ang > M_PI)
        return ang - 2 * (float)M_PI;
    else if (ang <= -(float)M_PI)
        return ang + 2 * (float)M_PI;
    else
        return ang;
}

/** Finds the minimum angle difference ang1-ang2 such that difference
 * is between [-M_PI,M_PI]
 * @param[in] ang1
 * @param[in] ang2
 * @return angle difference ang1-ang2
 */
float inv_angle_diff(float ang1, float ang2)
{
    float d;
    ang1 = inv_wrap_angle(ang1);
    ang2 = inv_wrap_angle(ang2);
    d = ang1 - ang2;
    if (d > M_PI)
        d -= 2 * (float)M_PI;
    else if (d < -(float)M_PI)
        d += 2 * (float)M_PI;
    return d;
}

/** bernstein hash, derived from public domain source */
uint32_t inv_checksum(const unsigned char *str, int len)
{
    uint32_t hash = 5381;
    int i, c;

    for (i = 0; i < len; i++) {
        c = *(str + i);
        hash = ((hash << 5) + hash) + c;	/* hash * 33 + c */
    }

    return hash;
}

static unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;		// error
    return b;
}


/** Converts an orientation matrix made up of 0,+1,and -1 to a scalar representation.
* @param[in] mtx Orientation matrix to convert to a scalar.
* @return Description of orientation matrix. The lowest 2 bits (0 and 1) represent the column the one is on for the
* first row, with the bit number 2 being the sign. The next 2 bits (3 and 4) represent
* the column the one is on for the second row with bit number 5 being the sign.
* The next 2 bits (6 and 7) represent the column the one is on for the third row with
* bit number 8 being the sign. In binary the identity matrix would therefor be:
* 010_001_000 or 0x88 in hex.
*/
unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{

    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}

/** Uses the scalar orientation value to convert from chip frame to body frame
* @param[in] orientation A scalar that represent how to go from chip to body frame
* @param[in] input Input vector, length 3
* @param[out] output Output vector, length 3
*/
void inv_convert_to_body(unsigned short orientation, const long *input, long *output)
{
    output[0] = input[orientation      & 0x03] * SIGNSET(orientation & 0x004);
    output[1] = input[(orientation>>3) & 0x03] * SIGNSET(orientation & 0x020);
    output[2] = input[(orientation>>6) & 0x03] * SIGNSET(orientation & 0x100);
}

/** Uses the scalar orientation value to convert from body frame to chip frame
* @param[in] orientation A scalar that represent how to go from chip to body frame
* @param[in] input Input vector, length 3
* @param[out] output Output vector, length 3
*/
void inv_convert_to_chip(unsigned short orientation, const long *input, long *output)
{
    output[orientation & 0x03]      = input[0] * SIGNSET(orientation & 0x004);
    output[(orientation>>3) & 0x03] = input[1] * SIGNSET(orientation & 0x020);
    output[(orientation>>6) & 0x03] = input[2] * SIGNSET(orientation & 0x100);
}


/** Uses the scalar orientation value to convert from chip frame to body frame and
* apply appropriate scaling.
* @param[in] orientation A scalar that represent how to go from chip to body frame
* @param[in] sensitivity Sensitivity scale
* @param[in] input Input vector, length 3
* @param[out] output Output vector, length 3
*/
void inv_convert_to_body_with_scale(unsigned short orientation, long sensitivity, const long *input, long *output)
{
    output[0] = inv_q30_mult(input[orientation & 0x03] *
                             SIGNSET(orientation & 0x004), sensitivity);
    output[1] = inv_q30_mult(input[(orientation>>3) & 0x03] *
                             SIGNSET(orientation & 0x020), sensitivity);
    output[2] = inv_q30_mult(input[(orientation>>6) & 0x03] *
                             SIGNSET(orientation & 0x100), sensitivity);
}

/** find a norm for a vector
* @param[in] a vector [3x1]
* @param[out] output the norm of the input vector
*/
double inv_vector_norm(const float *x)
{
    return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
}

void inv_init_biquad_filter(inv_biquad_filter_t *pFilter, float *pBiquadCoeff) {
    int i;
    // initial state to zero
    pFilter->state[0] = 0;
    pFilter->state[1] = 0;

    // set up coefficients
    for (i=0; i<5; i++) {
        pFilter->c[i] = pBiquadCoeff[i];
    }
}

void inv_calc_state_to_match_output(inv_biquad_filter_t *pFilter, float input)
{
    pFilter->input = input;
    pFilter->output = input;
    pFilter->state[0] = input / (1 + pFilter->c[2] + pFilter->c[3]);
    pFilter->state[1] = pFilter->state[0];
}

float inv_biquad_filter_process(inv_biquad_filter_t *pFilter, float input)  {
    float stateZero;

    pFilter->input = input;
    // calculate the new state;
    stateZero = pFilter->input - pFilter->c[2]*pFilter->state[0]
                               - pFilter->c[3]*pFilter->state[1];

    pFilter->output = stateZero + pFilter->c[0]*pFilter->state[0]
                                + pFilter->c[1]*pFilter->state[1];

    // update the output and state
    pFilter->output = pFilter->output * pFilter->c[4];
    pFilter->state[1] = pFilter->state[0];
    pFilter->state[0] = stateZero;
    return pFilter->output;
}

void inv_get_cross_product_vec(float *cgcross, float compass[3], float grav[3])  {

    cgcross[0] = (float)compass[1] * grav[2] - (float)compass[2] * grav[1];
    cgcross[1] = (float)compass[2] * grav[0] - (float)compass[0] * grav[2];
    cgcross[2] = (float)compass[0] * grav[1] - (float)compass[1] * grav[0];
}

void mlMatrixVectorMult(long matrix[9], const long vecIn[3], long *vecOut)  {
        // matrix format
        //  [ 0  3  6;
        //    1  4  7;
        //    2  5  8]

        // vector format:  [0  1  2]^T;
        int i, j;
        long temp;

        for (i=0; i<3; i++)	{
                temp = 0;
                for (j=0; j<3; j++)  {
                        temp += inv_q30_mult(matrix[i+j*3], vecIn[j]);
                }
                vecOut[i] = temp;
        }
}


/**
 * @}
 */