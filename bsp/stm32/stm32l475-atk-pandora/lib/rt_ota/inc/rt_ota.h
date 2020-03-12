/*
 * File      : rt_ota.h
 * COPYRIGHT (C) 2012-2018, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-23     armink       the first version
 */

#ifndef _RT_OTA_H_
#define _RT_OTA_H_

#include "rtconfig.h"
#include <stdint.h>
#include <stdio.h>
#include <fal.h>

#define RT_OTA_SW_VERSION              "0.1.2"

/* OTA download partition name */
#ifndef RT_OTA_DL_PART_NAME
#define RT_OTA_DL_PART_NAME            "download"
#endif

#ifndef RT_OTA_MALLOC
#define RT_OTA_MALLOC                  malloc
#endif

#ifndef RT_OTA_CALLOC
#define RT_OTA_CALLOC                  calloc
#endif

#ifndef RT_OTA_REALLOC
#define RT_OTA_REALLOC                 realloc
#endif

#ifndef RT_OTA_FREE
#define RT_OTA_FREE                    free
#endif

#if RT_OTA_DEBUG
#ifdef assert
#undef assert
#endif
#define assert(EXPR)                                                           \
if (!(EXPR))                                                                   \
{                                                                              \
    printf("(%s) has assert failed at %s.\n", #EXPR, __FUNCTION__);            \
    while (1);                                                                 \
}

/* debug level log */
#ifdef  log_d
#undef  log_d
#endif
#define log_d(...)                     printf("[D/OTA] (%s:%d) ", __FUNCTION__, __LINE__);           printf(__VA_ARGS__);printf("\n")

#else

#ifdef assert
#undef assert
#endif
#define assert(EXPR)                   ((void)0);

/* debug level log */
#ifdef  log_d
#undef  log_d
#endif
#define log_d(...)
#endif /* RT_OTA_DEBUG */

/* error level log */
#ifdef  log_e
#undef  log_e
#endif
#define log_e(...)                     printf("\033[31;22m[E/OTA] (%s:%d) ", __FUNCTION__, __LINE__);printf(__VA_ARGS__);printf("\033[0m\n")

/* info level log */
#ifdef  log_i
#undef  log_i
#endif
#define log_i(...)                     printf("\033[36;22m[I/OTA] ");                                printf(__VA_ARGS__);printf("\033[0m\n")

#ifdef __CC_ARM                         /* ARM Compiler */
    #define RT_OTA_WEAK                __weak
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
    #define RT_OTA_WEAK                __weak
#elif defined (__GNUC__)                /* GNU GCC Compiler */
    #define RT_OTA_WEAK                __attribute__((weak))
#endif /* __CC_ARM */

/**
 * OTA firmware encryption algorithm and compression algorithm
 */
enum rt_ota_algo
{
    RT_OTA_CRYPT_ALGO_NONE    = 0x0L,               /**< no encryption algorithm and no compression algorithm */
    RT_OTA_CRYPT_ALGO_XOR     = 0x1L,               /**< XOR encryption */
    RT_OTA_CRYPT_ALGO_AES256  = 0x2L,               /**< AES256 encryption */
    RT_OTA_CMPRS_ALGO_GZIP    = 0x1L << 8,          /**< Gzip: zh.wikipedia.org/wiki/Gzip */
    RT_OTA_CMPRS_ALGO_QUICKLZ = 0x2L << 8,          /**< QuickLZ: www.quicklz.com */
    RT_OTA_CMPRS_ALGO_FASTLZ  = 0x3L << 8,          /**< FastLZ: fastlz.org/ */

    RT_OTA_CRYPT_STAT_MASK    = 0xFL,
    RT_OTA_CMPRS_STAT_MASK    = 0xFL << 8,
};
typedef enum rt_ota_algo rt_ota_algo_t;

/* OTA error code */
typedef enum {
    RT_OTA_NO_ERR = 0,
    RT_OTA_GENERAL_ERR= -1,            /* general error */
    RT_OTA_CHECK_FAILED = -2,          /* check failed */
    RT_OTA_ALGO_NOT_SUPPORTED = -3,    /* firmware algorithm not supported */
    RT_OTA_COPY_FAILED = -4,           /* copy firmware to destination partition failed */
    RT_OTA_FW_VERIFY_FAILED = -5,      /* firmware verify failed */
    RT_OTA_NO_MEM_ERR = -6,            /* no memory */
    RT_OTA_PART_READ_ERR = -7,         /* partition read error */
    RT_OTA_PART_WRITE_ERR = -8,        /* partition write error */
    RT_OTA_PART_ERASE_ERR = -9,        /* partition erase error */
} rt_ota_err_t;

/* ========================== OTA API ========================= */

/**
 * OTA initialization
 *
 * @return -1: partition table not found
 *         -2: download partition not found
 *        >=0: initialize success
 */
int rt_ota_init(void);

/**
 * verify firmware on this partition
 *
 * @param part partition
 *
 * @return -1: failed, >=0: success
 */
int rt_ota_part_fw_verify(const struct fal_partition *part);

/**
 * check need to upgrade
 *
 * @note please run `rt_ota_part_fw_verify` before upgrade
 *
 * @return 1: need upgrade, 0: don't need upgrade
 */
int rt_ota_check_upgrade(void);

/**
 * erase the partition for new firmware write
 *
 * @note it will be called by rt_ota_upgrade() or before application download starting
 *
 * @param part erase partition object
 * @param new_fw_size the new firmware size
 *
 * @return result
 *
 */
int rt_ota_erase_fw(const struct fal_partition *part, size_t new_fw_size);

/**
 * get firmware version on this partition
 * @note this function is not supported reentrant
 *
 * @param part partition
 *
 * @return != NULL: version name
 *         == NULL: get failed
 */
const char *rt_ota_get_fw_version(const struct fal_partition *part);

/**
 * get firmware timestamp on this partition
 *
 * @param part partition
 *
 * @return != 0: firmware timestamp
 *         == 0: get failed
 */
uint32_t rt_ota_get_fw_timestamp(const struct fal_partition *part);

/**
 * get firmware size on this partition
 * @note This firmware size is after compression or encryption.
 *       If you want to get RAW firmware size, please using rt_ota_get_raw_fw_size().
 *
 * @param part partition
 *
 * @return != 0: firmware size
 *         == 0: get failed
 */
uint32_t rt_ota_get_fw_size(const struct fal_partition *part);

/**
 * get RAW firmware size on this partition
 *
 * @param part partition
 *
 * @return != 0: RAW firmware size
 *         == 0: get failed
 */
uint32_t rt_ota_get_raw_fw_size(const struct fal_partition *part);

/**
 * get firmware upgraded destination partition name on this partition
 * @note this function is not supported reentrant
 *
 * @param part partition
 *
 * @return != NULL: destination partition name
 *         == NULL: get failed
 */
const char *rt_ota_get_fw_dest_part_name(const struct fal_partition *part);

/**
 * get firmware firmware encryption algorithm and compression algorithm on this partition
 *
 * @param part partition
 *
 * @return != 0: algorithm
 *         == 0: no algorithm or get failed
 */
rt_ota_algo_t rt_ota_get_fw_algo(const struct fal_partition *part);

/**
 * upgrade firmware from OTA download partition
 *
 * 1. decrypt, dcmprs, copy firmware to destination partition
 * 2. hash verify on destination partition
 *
 * @note please run `rt_ota_check_upgrade` before upgrade
 *
 * @return @see rt_ota_err_t
 */
int rt_ota_upgrade(void);

/* ========================== User porting function ============================ */

/**
 * get the decryption key & iv
 *
 * @param iv_buf initialization vector
 * @param key_buf aes key
 */
void rt_ota_get_iv_key(uint8_t * iv_buf, uint8_t * key_buf);

/**
 * custom verify RAW firmware by user. It's a weak function, the user can be reimplemented it.
 *
 * @param cur_part current partition
 * @param offset RAW firmware offset
 * @param buf firmware buffer
 * @param len buffer length
 *
 * @return >=0: success
 *          <0: failed
 */
int rt_ota_custom_verify(const struct fal_partition *cur_part, long offset, const uint8_t *buf, size_t len);

#endif /* _RT_OTA_H_ */
