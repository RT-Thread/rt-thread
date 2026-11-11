/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __DFS_9PFS_H__
#define __DFS_9PFS_H__

#include <rtdef.h>

#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <bitmap.h>

#define P9_ERROR                    -1
#define P9_UNKNOWN_VERSION          -2
#define P9_R_ERROR                  -3
#define P9_MSG_TOO_LONG             -4
#define P9_UNEXPECTED_MSG           -5
#define P9_UNEXPECTED_TAG           -6
#define P9_TRANSPORT_ERROR          -7
#define P9_NO_TRANSPORT             -8
#define P9_NULL_PATH                -9
#define P9_PATH_ELEMENT_TOO_LONG    -10
#define P9_READ_UNEXPECTED_DATA     -11
#define P9_NO_BUFFER                -12
#define P9_MSG_SIZE_TOO_BIG         -13

#define P9_PARTIAL_WALK             1

#define P9_VERSION                  "9P2000.u"
#define P9_VERSION_UNKNOWN          "unknown"

#define P9_MSG_F_TYPE               7
#define P9_MSG_F_BSIZE              11
#define P9_MSG_F_BLOCKS             15
#define P9_MSG_F_BFREE              23
#define P9_MSG_F_BAVAIL             31
#define P9_MSG_F_FILES              39
#define P9_MSG_F_FFREE              47
#define P9_MSG_FSID_VAL             55
#define P9_MSG_F_NAMELEN            63
#define P9_MSG_SIZE                 0
#define P9_MSG_ID                   4
#define P9_MSG_ERR                  0x6b
#define P9_MSG_ERR_STR              9
#define P9_MSG_ERR_STR_LEN          7
#define P9_MSG_TAG                  5
#define P9_MSG_VER_MSIZE            7
#define P9_MSG_VER_STR_LEN          11
#define P9_MSG_VER_STR              13
#define P9_MSG_WALK_TX_ELMT         15
#define P9_MSG_WALK_RX_ELMT         7
#define P9_MSG_WALK_MAX_ELMT        16
#define P9_MSG_QID_SIZE             13
#define P9_MSG_WALK_RX_HDR_SIZE     9
#define P9_MSG_OPEN_IOUNIT          20
#define P9_MSG_OPEN_MODE_MASK       0x5f
#define P9_MSG_CREATE_IOUNIT        20
#define P9_MSG_READ_COUNT           7
#define P9_MSG_READ_DATA            11
#define P9_MSG_WRITE_COUNT          7
#define P9_MSG_WRITE_DATA           23
#define P9_MSG_RENAME_DATA          15
#define P9_MSG_STAT_SIZE            9
#define P9_MSG_STAT_TYPE            11
#define P9_MSG_STAT_DEV             13
#define P9_MSG_STAT_QID_TYPE        17
#define P9_MSG_STAT_QID_VERSION     18
#define P9_MSG_STAT_QID_PATH        22
#define P9_MSG_STAT_MODE            30
#define P9_MSG_STAT_ATIME           34
#define P9_MSG_STAT_MTIME           38
#define P9_MSG_STAT_LEN             42
#define P9_MSG_STAT_NAME_LEN        50
#define P9_MSG_STAT_NAME            52

#define P9_HD_TSTATFS               8
#define P9_HD_RSTATFS               (P9_HD_TSTATFS + 1)
#define P9_HD_TRENAME               20
#define P9_HD_RRENAME               (P9_HD_TRENAME + 1)
#define P9_HD_TFSYNC                50
#define P9_HD_RFSYNC                (P9_HD_TFSYNC + 1)
#define P9_HD_TVERSION              100
#define P9_HD_RVERSION              (P9_HD_TVERSION + 1)
#define P9_HD_TAUTH                 102
#define P9_HD_RAUTH                 (P9_HD_TAUTH + 1)
#define P9_HD_TATTACH               104
#define P9_HD_RATTACH               (P9_HD_TATTACH + 1)
#define P9_HD_TERROR                106
#define P9_HD_RERROR                (P9_HD_TERROR + 1)
#define P9_HD_TFLUSH                108
#define P9_HD_RFLUSH                (P9_HD_TFLUSH + 1)
#define P9_HD_TWALK                 110
#define P9_HD_RWALK                 (P9_HD_TWALK + 1)
#define P9_HD_TOPEN                 112
#define P9_HD_ROPEN                 (P9_HD_TOPEN + 1)
#define P9_HD_TCREATE               114
#define P9_HD_RCREATE               (P9_HD_TCREATE + 1)
#define P9_HD_TREAD                 116
#define P9_HD_RREAD                 (P9_HD_TREAD + 1)
#define P9_HD_TWRITE                118
#define P9_HD_RWRITE                (P9_HD_TWRITE + 1)
#define P9_HD_TCLUNK                120
#define P9_HD_RCLUNK                (P9_HD_TCLUNK + 1)
#define P9_HD_TREMOVE               122
#define P9_HD_RREMOVE               (P9_HD_TREMOVE + 1)
#define P9_HD_TSTAT                 124
#define P9_HD_RSTAT                 (P9_HD_TSTAT + 1)

#define P9_STAT_MODE_DIR            0x80000000
#define P9_STAT_MODE_APPEND         0x40000000
#define P9_STAT_MODE_EXCL           0x20000000
#define P9_STAT_MODE_MOUNT          0x10000000
#define P9_STAT_MODE_AUTH           0x08000000
#define P9_STAT_MODE_TMP            0x04000000
#define P9_STAT_MODE_SYMLINK        0x02000000
#define P9_STAT_MODE_LINK           0x01000000
#define P9_STAT_MODE_DEVICE         0x00800000
#define P9_STAT_MODE_NAMED_PIPE     0x00200000
#define P9_STAT_MODE_SOCKET         0x00100000
#define P9_STAT_MODE_SETUID         0x00080000
#define P9_STAT_MODE_SETGID         0x00040000
#define P9_STAT_MODE_SETVTX         0x00010000

struct p9_protocol
{
    rt_list_t list;
    char *name;

    const char *tag;
    rt_err_t (*transport)(struct p9_protocol *p9p,
            rt_uint8_t *tx_data, rt_uint32_t tx_size,
            rt_uint8_t *rx_data, rt_uint32_t *ref_rx_size);
};

struct p9_connection
{
    char *uname;            /* User name */
    char *aname;            /* Tree/mount name/path */
    rt_uint32_t fid;        /* Represents mount point */
    rt_uint32_t msg_size;

    char error[200];
    rt_uint8_t *rx_buffer;
    rt_uint8_t *tx_buffer;
    struct rt_mutex lock;

    struct p9_protocol *protocol;
    RT_BITMAP_DECLARE(fid_map, DFS_FD_MAX);
};

struct p9_file
{
#define P9_ROOT_FID     1
#define P9_FILE_FID     2
    rt_uint32_t fid;        /* Identifies the file to P9 server */
    rt_uint32_t iounit;     /* Maximum read size in bytes */

    struct p9_connection *connection;
};

/**
 * @brief Allocate a new 9P connection.
 *
 * @param p9p Pointer to the 9P protocol structure.
 * @param aname Mount name/path.
 * @param buffer_size Size of the buffer to allocate.
 * @return Pointer to the allocated p9_connection structure, or RT_NULL on failure.
 */
struct p9_connection *p9_connection_alloc(struct p9_protocol *p9p,
        const char *aname, rt_uint32_t buffer_size);

/**
 * @brief Free a 9P connection and release its resources.
 *
 * @param conn Pointer to the p9_connection to free.
 * @return RT_EOK on success, error code otherwise.
 */
rt_err_t p9_connection_free(struct p9_connection *conn);

/**
 * @brief Perform a 9P transaction.
 *
 * @param conn Pointer to the p9_connection.
 * @param tx_size Size of the transmit buffer.
 * @param out_rx_size Pointer to store the received buffer size.
 * @return 0 on success, negative error code otherwise.
 */
int p9_transaction(struct p9_connection *conn,
        rt_uint32_t tx_size, rt_uint32_t *out_rx_size);

/**
 * @brief Negotiate 9P protocol version with the server.
 *
 * @param conn Pointer to the p9_connection.
 * @return 0 on success, negative error code otherwise.
 */
int p9_version(struct p9_connection *conn);

/**
 * @brief Attach to the 9P server.
 *
 * @param conn Pointer to the p9_connection.
 * @return 0 on success, negative error code otherwise.
 */
int p9_attach(struct p9_connection *conn);

/**
 * @brief Clunk (close) a file identifier (fid) on the 9P server.
 *
 * @param conn Pointer to the p9_connection.
 * @param fid File identifier to clunk.
 * @return 0 on success, negative error code otherwise.
 */
int p9_clunk(struct p9_connection *conn, rt_uint32_t fid);

/**
 * @brief Register a 9P protocol tag.
 *
 * @param p9p Pointer to the p9_protocol structure.
 * @return RT_EOK on success, error code otherwise.
 */
rt_err_t dfs_9pfs_add_tag(struct p9_protocol *p9p);

/**
 * @brief Unregister a 9P protocol tag.
 *
 * @param p9p Pointer to the p9_protocol structure.
 * @return RT_EOK on success, error code otherwise.
 */
rt_err_t dfs_9pfs_del_tag(struct p9_protocol *p9p);

/**
 * @brief Initialize the 9P filesystem.
 *
 * @return 0 on success, negative error code otherwise.
 */
int dfs_9pfs_init(void);

#endif /* __DFS_9PFS_H__ */
