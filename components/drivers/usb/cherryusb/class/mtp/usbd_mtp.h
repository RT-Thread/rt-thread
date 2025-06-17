/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_MTP_H
#define USBD_MTP_H

#include "usb_mtp.h"
#include <sys/stat.h>
#include <fcntl.h>

/* gcc toolchain does not implement dirent.h, so we define our own MTP_DIR and mtp_dirent */

typedef void MTP_DIR;

struct mtp_statfs {
    size_t f_bsize;  /* block size */
    size_t f_blocks; /* total data blocks in file system */
    size_t f_bfree;  /* free blocks in file system */
};

struct mtp_dirent {
    uint8_t d_type;                              /* The type of the file */
    uint8_t d_namlen;                            /* The length of the not including the terminating null file name */
    uint16_t d_reclen;                           /* length of this record */
    char d_name[CONFIG_USBDEV_MTP_MAX_PATHNAME]; /* The null-terminated file name */
};

#ifdef __cplusplus
extern "C" {
#endif

struct usbd_interface *usbd_mtp_init_intf(struct usbd_interface *intf,
                                          const uint8_t out_ep,
                                          const uint8_t in_ep,
                                          const uint8_t int_ep);

const char *usbd_mtp_fs_root_path(void);
const char *usbd_mtp_fs_description(void);

int usbd_mtp_mkdir(const char *path);
int usbd_mtp_rmdir(const char *path);
MTP_DIR *usbd_mtp_opendir(const char *name);
int usbd_mtp_closedir(MTP_DIR *d);
struct mtp_dirent *usbd_mtp_readdir(MTP_DIR *d);

int usbd_mtp_statfs(const char *path, struct mtp_statfs *buf);
int usbd_mtp_stat(const char *file, struct stat *buf);

int usbd_mtp_open(const char *path, uint8_t mode);
int usbd_mtp_close(int fd);
int usbd_mtp_read(int fd, void *buf, size_t len);
int usbd_mtp_write(int fd, const void *buf, size_t len);

int usbd_mtp_unlink(const char *path);

#ifdef __cplusplus
}
#endif

#endif /* USBD_MTP_H */
