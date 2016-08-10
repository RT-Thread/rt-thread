/*
 $License:
    Copyright (C) 2011 InvenSense Corporation, All Rights Reserved.
 $
 */
/*******************************************************************************
 *
 * $Id: mlmath.h 5629 2011-06-11 03:13:08Z mcaramello $ 
 * 
 *******************************************************************************/

#ifndef _ML_MATH_H_
#define	_ML_MATH_H_

#ifndef MLMATH
// This define makes Microsoft pickup things like M_PI
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef WIN32
// Microsoft doesn't follow standards
#define  round(x)(((double)((long long)((x)>0?(x)+.5:(x)-.5))))
#define roundf(x)(((float )((long long)((x)>0?(x)+.5f:(x)-.5f))))
#endif

#else  // MLMATH

#ifdef __cplusplus 
extern "C" {
#endif
/* MPL needs below functions */
double	ml_asin(double);
double	ml_atan(double);
double	ml_atan2(double, double);
double	ml_log(double);
double	ml_sqrt(double);
double	ml_ceil(double);
double	ml_floor(double);
double  ml_cos(double);
double  ml_sin(double);
double  ml_acos(double);
#ifdef __cplusplus
} // extern "C"
#endif

/*
 * We rename functions here to provide the hook for other 
 * customized math functions.
 */
#define	sqrt(x)      ml_sqrt(x)
#define	log(x)       ml_log(x)
#define	asin(x)      ml_asin(x)
#define	atan(x)      ml_atan(x)
#define	atan2(x,y)   ml_atan2(x,y)
#define	ceil(x)      ml_ceil(x)
#define	floor(x)     ml_floor(x)
#define fabs(x)      (((x)<0)?-(x):(x))
#define round(x)     (((double)((long long)((x)>0?(x)+.5:(x)-.5))))
#define roundf(x)    (((float )((long long)((x)>0?(x)+.5f:(x)-.5f))))
#define cos(x)       ml_cos(x)
#define sin(x)       ml_sin(x)
#define acos(x)      ml_acos(x)

#define pow(x,y)     ml_pow(x,y)

#ifdef LINUX
/* stubs for float version of math functions */
#define cosf(x)      ml_cos(x)
#define sinf(x)      ml_sin(x)
#define atan2f(x,y)  ml_atan2(x,y)
#define sqrtf(x)     ml_sqrt(x)
#endif



#endif // MLMATH

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

#ifndef ABS
#define ABS(x) (((x)>=0)?(x):-(x))
#endif

#ifndef MIN
#define MIN(x,y) (((x)<(y))?(x):(y))
#endif

#ifndef MAX
#define MAX(x,y) (((x)>(y))?(x):(y))
#endif

/*---------------------------*/
#endif /* !_ML_MATH_H_ */