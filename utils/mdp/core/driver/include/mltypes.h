/*
 $License:
    Copyright (C) 2011 InvenSense Corporation, All Rights Reserved.
 $
 */

/**
 *  @defgroup MLERROR
 *  @brief  Motion Library - Error definitions.
 *          Definition of the error codes used within the MPL and
 *          returned to the user.
 *          Every function tries to return a meaningful error code basing
 *          on the occuring error condition. The error code is numeric.
 *
 *          The available error codes and their associated values are:
 *          - (0)               INV_SUCCESS
 *          - (32)              INV_ERROR
 *          - (22 / EINVAL)     INV_ERROR_INVALID_PARAMETER
 *          - (1  / EPERM)      INV_ERROR_FEATURE_NOT_ENABLED
 *          - (36)              INV_ERROR_FEATURE_NOT_IMPLEMENTED
 *          - (38)              INV_ERROR_DMP_NOT_STARTED
 *          - (39)              INV_ERROR_DMP_STARTED
 *          - (40)              INV_ERROR_NOT_OPENED
 *          - (41)              INV_ERROR_OPENED
 *          - (19 / ENODEV)     INV_ERROR_INVALID_MODULE
 *          - (12 / ENOMEM)     INV_ERROR_MEMORY_EXAUSTED
 *          - (44)              INV_ERROR_DIVIDE_BY_ZERO
 *          - (45)              INV_ERROR_ASSERTION_FAILURE
 *          - (46)              INV_ERROR_FILE_OPEN
 *          - (47)              INV_ERROR_FILE_READ
 *          - (48)              INV_ERROR_FILE_WRITE
 *          - (49)              INV_ERROR_INVALID_CONFIGURATION
 *          - (52)              INV_ERROR_SERIAL_CLOSED
 *          - (53)              INV_ERROR_SERIAL_OPEN_ERROR
 *          - (54)              INV_ERROR_SERIAL_READ
 *          - (55)              INV_ERROR_SERIAL_WRITE
 *          - (56)              INV_ERROR_SERIAL_DEVICE_NOT_RECOGNIZED
 *          - (57)              INV_ERROR_SM_TRANSITION
 *          - (58)              INV_ERROR_SM_IMPROPER_STATE
 *          - (62)              INV_ERROR_FIFO_OVERFLOW
 *          - (63)              INV_ERROR_FIFO_FOOTER
 *          - (64)              INV_ERROR_FIFO_READ_COUNT
 *          - (65)              INV_ERROR_FIFO_READ_DATA
 *          - (72)              INV_ERROR_MEMORY_SET
 *          - (82)              INV_ERROR_LOG_MEMORY_ERROR
 *          - (83)              INV_ERROR_LOG_OUTPUT_ERROR
 *          - (92)              INV_ERROR_OS_BAD_PTR
 *          - (93)              INV_ERROR_OS_BAD_HANDLE
 *          - (94)              INV_ERROR_OS_CREATE_FAILED
 *          - (95)              INV_ERROR_OS_LOCK_FAILED
 *          - (102)             INV_ERROR_COMPASS_DATA_OVERFLOW
 *          - (103)             INV_ERROR_COMPASS_DATA_UNDERFLOW
 *          - (104)             INV_ERROR_COMPASS_DATA_NOT_READY
 *          - (105)             INV_ERROR_COMPASS_DATA_ERROR
 *          - (107)             INV_ERROR_CALIBRATION_LOAD
 *          - (108)             INV_ERROR_CALIBRATION_STORE
 *          - (109)             INV_ERROR_CALIBRATION_LEN
 *          - (110)             INV_ERROR_CALIBRATION_CHECKSUM
 *          - (111)             INV_ERROR_ACCEL_DATA_OVERFLOW
 *          - (112)             INV_ERROR_ACCEL_DATA_UNDERFLOW
 *          - (113)             INV_ERROR_ACCEL_DATA_NOT_READY
 *          - (114)             INV_ERROR_ACCEL_DATA_ERROR
 *
 *          The available warning codes and their associated values are:
 *          - (115)             INV_WARNING_MOTION_RACE
 *          - (116)             INV_WARNING_QUAT_TRASHED
 *
 *  @{
 *      @file mltypes.h
 *  @}
 */

#ifndef MLTYPES_H
#define MLTYPES_H

#ifdef __KERNEL__
#include <linux/types.h>
#include <asm-generic/errno-base.h>
#else
#include "stdint_invensense.h"
#include <errno.h>
#endif
#include <limits.h>

#ifndef REMOVE_INV_ERROR_T
/*---------------------------
 *    ML Types
 *--------------------------*/

/**
 *  @struct inv_error_t mltypes.h "mltypes"
 *  @brief  The MPL Error Code return type.
 *
 *  @code
 *      typedef unsigned char inv_error_t;
 *  @endcode
 */
//typedef unsigned char inv_error_t;
typedef int inv_error_t;
#endif

#if defined EMPL
typedef unsigned long inv_time_t;
#else
typedef unsigned long long inv_time_t;
#endif

#if defined EMPL || (!defined __GNUC__ && !defined __KERNEL__)
typedef int8_t   __s8;
typedef int16_t  __s16;
typedef int32_t  __s32;

typedef uint8_t   __u8;
typedef uint16_t  __u16;
typedef uint32_t  __u32;

#ifndef EMPL_NO_64BIT
typedef int64_t  __s64;
typedef uint64_t  __u64;
#endif
#elif !defined __KERNEL__
#include <sys/types.h>
#endif

#if defined EMPL_TARGET_MSP430
#include <USB_Common/types.h>
#endif

#ifndef __cplusplus
#ifndef __KERNEL__
#ifndef EMPL_TARGET_UC3L0
//typedef int_fast8_t bool;
#endif

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

#endif
#endif

/*---------------------------
 *    ML Defines
 *--------------------------*/

#ifndef NULL
#define NULL 0
#endif

#ifndef __KERNEL__
#ifndef ARRAY_SIZE
/* Dimension of an array */
#define ARRAY_SIZE(array) (sizeof(array)/sizeof((array)[0]))
#endif
#endif
/* - ML Errors. - */
#define ERROR_NAME(x)   (#x)
#define ERROR_CHECK_FIRST(first, x) \
	{ if (INV_SUCCESS == first) first = x; }

#define INV_SUCCESS                       (0)
/* Generic Error code.  Proprietary Error Codes only */
#define INV_ERROR_BASE                    (0x20)
#define INV_ERROR                         (INV_ERROR_BASE)

#ifndef EINVAL
#define EINVAL  (22)
#endif

#ifndef ENOMEM
#define ENOMEM  (12)
#endif

#ifndef EPERM
#define EPERM   (1)
#endif



/* Compatibility and other generic error codes */
#define INV_ERROR_INVALID_PARAMETER             (EINVAL)
#define INV_ERROR_FEATURE_NOT_ENABLED           (EPERM)
#define INV_ERROR_FEATURE_NOT_IMPLEMENTED       (INV_ERROR_BASE + 4)
#define INV_ERROR_DMP_NOT_STARTED               (INV_ERROR_BASE + 6)
#define INV_ERROR_DMP_STARTED                   (INV_ERROR_BASE + 7)
#define INV_ERROR_NOT_OPENED                    (INV_ERROR_BASE + 8)
#define INV_ERROR_OPENED                        (INV_ERROR_BASE + 9)
#define INV_ERROR_INVALID_MODULE                (ENODEV)
#define INV_ERROR_MEMORY_EXAUSTED               (ENOMEM)
#define INV_ERROR_DIVIDE_BY_ZERO                (INV_ERROR_BASE + 12)
#define INV_ERROR_ASSERTION_FAILURE             (INV_ERROR_BASE + 13)
#define INV_ERROR_FILE_OPEN                     (INV_ERROR_BASE + 14)
#define INV_ERROR_FILE_READ                     (INV_ERROR_BASE + 15)
#define INV_ERROR_FILE_WRITE                    (INV_ERROR_BASE + 16)
#define INV_ERROR_INVALID_CONFIGURATION         (INV_ERROR_BASE + 17)
#define INV_ERROR_NOT_AUTHORIZED                (INV_ERROR_BASE + 18)

/* Serial Communication */
#define INV_ERROR_SERIAL_CLOSED                 (INV_ERROR_BASE + 20)
#define INV_ERROR_SERIAL_OPEN_ERROR             (INV_ERROR_BASE + 21)
#define INV_ERROR_SERIAL_READ                   (INV_ERROR_BASE + 22)
#define INV_ERROR_SERIAL_WRITE                  (INV_ERROR_BASE + 23)
#define INV_ERROR_SERIAL_DEVICE_NOT_RECOGNIZED  (INV_ERROR_BASE + 24)

/* SM = State Machine */
#define INV_ERROR_SM_TRANSITION                 (INV_ERROR_BASE + 25)
#define INV_ERROR_SM_IMPROPER_STATE             (INV_ERROR_BASE + 26)

/* Fifo */
#define INV_ERROR_FIFO_OVERFLOW                 (INV_ERROR_BASE + 30)
#define INV_ERROR_FIFO_FOOTER                   (INV_ERROR_BASE + 31)
#define INV_ERROR_FIFO_READ_COUNT               (INV_ERROR_BASE + 32)
#define INV_ERROR_FIFO_READ_DATA                (INV_ERROR_BASE + 33)

/* Memory & Registers, Set & Get */
#define INV_ERROR_MEMORY_SET                    (INV_ERROR_BASE + 40)

#define INV_ERROR_LOG_MEMORY_ERROR              (INV_ERROR_BASE + 50)
#define INV_ERROR_LOG_OUTPUT_ERROR              (INV_ERROR_BASE + 51)

/* OS interface errors */
#define INV_ERROR_OS_BAD_PTR                    (INV_ERROR_BASE + 60)
#define INV_ERROR_OS_BAD_HANDLE                 (INV_ERROR_BASE + 61)
#define INV_ERROR_OS_CREATE_FAILED              (INV_ERROR_BASE + 62)
#define INV_ERROR_OS_LOCK_FAILED                (INV_ERROR_BASE + 63)

/* Compass errors */
#define INV_ERROR_COMPASS_DATA_OVERFLOW         (INV_ERROR_BASE + 70)
#define INV_ERROR_COMPASS_DATA_UNDERFLOW        (INV_ERROR_BASE + 71)
#define INV_ERROR_COMPASS_DATA_NOT_READY        (INV_ERROR_BASE + 72)
#define INV_ERROR_COMPASS_DATA_ERROR            (INV_ERROR_BASE + 73)

/* Load/Store calibration */
#define INV_ERROR_CALIBRATION_LOAD              (INV_ERROR_BASE + 75)
#define INV_ERROR_CALIBRATION_STORE             (INV_ERROR_BASE + 76)
#define INV_ERROR_CALIBRATION_LEN               (INV_ERROR_BASE + 77)
#define INV_ERROR_CALIBRATION_CHECKSUM          (INV_ERROR_BASE + 78)

/* Accel errors */
#define INV_ERROR_ACCEL_DATA_OVERFLOW           (INV_ERROR_BASE + 79)
#define INV_ERROR_ACCEL_DATA_UNDERFLOW          (INV_ERROR_BASE + 80)
#define INV_ERROR_ACCEL_DATA_NOT_READY          (INV_ERROR_BASE + 81)
#define INV_ERROR_ACCEL_DATA_ERROR              (INV_ERROR_BASE + 82)

/* No Motion Warning States */
#define INV_WARNING_MOTION_RACE                 (INV_ERROR_BASE + 83)
#define INV_WARNING_QUAT_TRASHED                (INV_ERROR_BASE + 84)
#define INV_WARNING_GYRO_MAG                    (INV_ERROR_BASE + 85)

#define INV_WARNING_SEMAPHORE_TIMEOUT           (INV_ERROR_BASE + 86)


/* For Linux coding compliance */
#ifndef __KERNEL__
#define EXPORT_SYMBOL(x)
#endif

#endif				/* MLTYPES_H */