/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-25     armink       the first version
 */

#ifndef _ULOG_DEF_H_
#define _ULOG_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/* logger level, the number is compatible for syslog */
#define LOG_LVL_ASSERT                 0
#define LOG_LVL_ERROR                  3
#define LOG_LVL_WARNING                4
#define LOG_LVL_INFO                   6
#define LOG_LVL_DBG                    7

/* the output silent level and all level for filter setting */
#ifndef ULOG_USING_SYSLOG
#define LOG_FILTER_LVL_SILENT         0
#define LOG_FILTER_LVL_ALL            7
#else
#define LOG_FILTER_LVL_SILENT         1
#define LOG_FILTER_LVL_ALL            255
#endif /* ULOG_USING_SYSLOG */

/* compatible for rtdbg */
#undef LOG_D
#undef LOG_I
#undef LOG_W
#undef LOG_E
#undef LOG_RAW
#undef DBG_ERROR
#undef DBG_WARNING
#undef DBG_INFO
#undef DBG_LOG
#undef dbg_log
#define DBG_ERROR                      LOG_LVL_ERROR
#define DBG_WARNING                    LOG_LVL_WARNING
#define DBG_INFO                       LOG_LVL_INFO
#define DBG_LOG                        LOG_LVL_DBG
#define dbg_log(level, ...)                                \
    if ((level) <= LOG_LVL)                                \
    {                                                      \
        ulog_output(level, LOG_TAG, RT_FALSE, __VA_ARGS__);\
    }

#if !defined(LOG_TAG)
    /* compatible for rtdbg */
    #if defined(DBG_TAG)
        #define LOG_TAG                DBG_TAG
    #elif defined(DBG_SECTION_NAME)
        #define LOG_TAG                DBG_SECTION_NAME
    #else
        #define LOG_TAG                "NO_TAG"
    #endif
#endif /* !defined(LOG_TAG) */

#if !defined(LOG_LVL)
    /* compatible for rtdbg */
    #if defined(DBG_LVL)
        #define LOG_LVL                DBG_LVL
    #elif defined(DBG_LEVEL)
        #define LOG_LVL                DBG_LEVEL
    #else
        #define LOG_LVL                LOG_LVL_DBG
    #endif
#endif /* !defined(LOG_LVL) */

#if (LOG_LVL >= LOG_LVL_DBG) && (ULOG_OUTPUT_LVL >= LOG_LVL_DBG)
    #define ulog_d(TAG, ...)           ulog_output(LOG_LVL_DBG, TAG, RT_TRUE, __VA_ARGS__)
#else
    #define ulog_d(TAG, ...)
#endif /* (LOG_LVL >= LOG_LVL_DBG) && (ULOG_OUTPUT_LVL >= LOG_LVL_DBG) */

#if (LOG_LVL >= LOG_LVL_INFO) && (ULOG_OUTPUT_LVL >= LOG_LVL_INFO)
    #define ulog_i(TAG, ...)           ulog_output(LOG_LVL_INFO, TAG, RT_TRUE, __VA_ARGS__)
#else
    #define ulog_i(TAG, ...)
#endif /* (LOG_LVL >= LOG_LVL_INFO) && (ULOG_OUTPUT_LVL >= LOG_LVL_INFO) */

#if (LOG_LVL >= LOG_LVL_WARNING) && (ULOG_OUTPUT_LVL >= LOG_LVL_WARNING)
    #define ulog_w(TAG, ...)           ulog_output(LOG_LVL_WARNING, TAG, RT_TRUE, __VA_ARGS__)
#else
    #define ulog_w(TAG, ...)
#endif /* (LOG_LVL >= LOG_LVL_WARNING) && (ULOG_OUTPUT_LVL >= LOG_LVL_WARNING) */

#if (LOG_LVL >= LOG_LVL_ERROR) && (ULOG_OUTPUT_LVL >= LOG_LVL_ERROR)
    #define ulog_e(TAG, ...)           ulog_output(LOG_LVL_ERROR, TAG, RT_TRUE, __VA_ARGS__)
#else
    #define ulog_e(TAG, ...)
#endif /* (LOG_LVL >= LOG_LVL_ERROR) && (ULOG_OUTPUT_LVL >= LOG_LVL_ERROR) */

#if (LOG_LVL >= LOG_LVL_DBG) && (ULOG_OUTPUT_LVL >= LOG_LVL_DBG)
    #define ulog_hex(TAG, width, buf, size)     ulog_hexdump(TAG, width, buf, size)
#else
    #define ulog_hex(TAG, width, buf, size)
#endif /* (LOG_LVL >= LOG_LVL_DBG) && (ULOG_OUTPUT_LVL >= LOG_LVL_DBG) */

/* assert for developer. */
#ifdef ULOG_ASSERT_ENABLE
    #define ULOG_ASSERT(EXPR)                                                 \
    if (!(EXPR))                                                              \
    {                                                                         \
        ulog_output(LOG_LVL_ASSERT, LOG_TAG, RT_TRUE, "(%s) has assert failed at %s:%ld.", #EXPR, __FUNCTION__, __LINE__); \
        ulog_flush();                                                         \
        while (1);                                                            \
    }
#else
    #define ULOG_ASSERT(EXPR)
#endif

/* ASSERT API definition */
#if !defined(ASSERT)
    #define ASSERT           ULOG_ASSERT
#endif

/* compatible for elog */
#undef assert
#undef log_e
#undef log_w
#undef log_i
#undef log_d
#undef log_v
#undef ELOG_LVL_ASSERT
#undef ELOG_LVL_ERROR
#undef ELOG_LVL_WARN
#undef ELOG_LVL_INFO
#undef ELOG_LVL_DEBUG
#undef ELOG_LVL_VERBOSE
#define assert                         ASSERT
#define log_e                          LOG_E
#define log_w                          LOG_W
#define log_i                          LOG_I
#define log_d                          LOG_D
#define log_v                          LOG_D
#define log_raw                        LOG_RAW
#define log_hex                        LOG_HEX
#define ELOG_LVL_ASSERT                LOG_LVL_ASSERT
#define ELOG_LVL_ERROR                 LOG_LVL_ERROR
#define ELOG_LVL_WARN                  LOG_LVL_WARNING
#define ELOG_LVL_INFO                  LOG_LVL_INFO
#define ELOG_LVL_DEBUG                 LOG_LVL_DBG
#define ELOG_LVL_VERBOSE               LOG_LVL_DBG

/* setting static output log level */
#ifndef ULOG_OUTPUT_LVL
#define ULOG_OUTPUT_LVL                LOG_LVL_DBG
#endif

/* buffer size for every line's log */
#ifndef ULOG_LINE_BUF_SIZE
#define ULOG_LINE_BUF_SIZE             128
#endif

/* output filter's tag max length */
#ifndef ULOG_FILTER_TAG_MAX_LEN
#define ULOG_FILTER_TAG_MAX_LEN        23
#endif

/* output filter's keyword max length */
#ifndef ULOG_FILTER_KW_MAX_LEN
#define ULOG_FILTER_KW_MAX_LEN         15
#endif

#ifndef ULOG_NEWLINE_SIGN
#define ULOG_NEWLINE_SIGN              "\r\n"
#endif

#define ULOG_FRAME_MAGIC               0x10

/* tag's level filter */
struct ulog_tag_lvl_filter
{
    char tag[ULOG_FILTER_TAG_MAX_LEN + 1];
    rt_uint32_t level;
    rt_slist_t list;
};
typedef struct ulog_tag_lvl_filter *ulog_tag_lvl_filter_t;

struct ulog_frame
{
    /* magic word is 0x10 ('lo') */
    rt_uint32_t magic:8;
    rt_uint32_t is_raw:1;
    rt_uint32_t log_len:23;
    rt_uint32_t level;
    const char *log;
    const char *tag;
};
typedef struct ulog_frame *ulog_frame_t;

struct ulog_backend
{
    char name[RT_NAME_MAX];
    rt_bool_t support_color;
    rt_uint32_t out_level;
    void (*init)  (struct ulog_backend *backend);
    void (*output)(struct ulog_backend *backend, rt_uint32_t level, const char *tag, rt_bool_t is_raw, const char *log, size_t len);
    void (*flush) (struct ulog_backend *backend);
    void (*deinit)(struct ulog_backend *backend);
    rt_slist_t list;
};
typedef struct ulog_backend *ulog_backend_t;

#ifdef __cplusplus
}
#endif

#endif /* _ULOG_DEF_H_ */
