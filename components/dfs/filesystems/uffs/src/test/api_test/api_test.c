/*
This file is part of UFFS, the Ultra-low-cost Flash File System.

Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

UFFS is free software; you can redistribute it and/or modify it under
the GNU Library General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any
later version.

UFFS is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
or GNU Library General Public License, as applicable, for more details.

You should have received a copy of the GNU General Public License
and GNU Library General Public License along with UFFS; if not, write
to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA  02110-1301, USA.

As a special exception, if other files instantiate templates or use
macros or inline functions from this file, or you compile this file
and link it with other works to produce a work based on this file,
this file does not by itself cause the resulting work to be covered
by the GNU General Public License. However the source code for this
file must still be made available in accordance with section (3) of
the GNU General Public License v2.

This exception does not invalidate any other reasons why a work based
on this file might be covered by the GNU General Public License.
*/

/**
* \file api_test.c
* \brief API test server public functions 
* \author Ricky Zheng, created in 16 Dec, 2011 
*/

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "uffs/uffs_crc.h"
#include "api_test.h"

#define DEBUG

#ifdef DEBUG
#define DBG printf
#else
#define DBG(...)
#endif

static struct uffs_ApiSrvIoSt *m_io = NULL;
static int m_api_stat[UFFS_API_CMD_LAST + 1] = {0};

int apisrv_setup_io(struct uffs_ApiSrvIoSt *io)
{
	m_io = io;
	return 0;
}

//
// unload parameters from message.
// parameters list:
//  param1, size1, param2, size2, ..., NULL
// size: maximum size of parameter.
//
static int apisrv_unload_params(struct uffs_ApiSrvMsgSt *msg, ...)
{
    int ret = 0;
    int len, size;
	u32 n;
    u8 *p;
    u8 *data;
    struct uffs_ApiSrvHeaderSt *header = &msg->header;

    va_list args;

    va_start(args, msg);

    for (n = 0, data = msg->data; n < header->n_params; n++) {
        p = va_arg(args, void *);
        if (p == NULL)
            break;
		len = va_arg(args, int);
		size = header->param_size[n];
		if (size > len) {
			printf("cmd %d unload param %d overflow (max %d but %d)\n",
					header->cmd, n, len, size);
			ret = -1;
			break;
		}
        memcpy(p, data, size);
        data += size;
    }

    if (n != header->n_params) {
        printf("cmd %d unload params failed!\n", header->cmd);
        ret = -1;
    }

    if (data - msg->data != header->data_len) {
        printf("cmd %d unload params failed! data len mismatched.\n", header->cmd);
        ret = -1;
    }

    va_end(args);

    return ret;
}

// load response data. the parameter list: (&param1, size1, &param2, size2, .... NULL)
static int apisrv_make_message(struct uffs_ApiSrvMsgSt *msg, ...)
{
    int ret = 0;
    u32 n;
    u32 len, size;
    struct uffs_ApiSrvHeaderSt *header = &msg->header;
    u8 *p;
    u8 * params[UFFS_API_MAX_PARAMS];

    va_list args;

    va_start(args, msg);

    for (n = 0, len = 0; n < UFFS_API_MAX_PARAMS; n++) {
        p = va_arg(args, u8 *);
        if (p == NULL)  // terminator
            break;
        params[n] = p;
		size = va_arg(args, size_t);
		if (size > header->return_size[n]) {
			printf("WARNING: cmd %d make message param %d expect %d but %d, truncated.\n", header->cmd, n, header->return_size[n], size);
			size = header->return_size[n];
		}
	    header->param_size[n] = size;
        len += header->param_size[n];
    }
    header->n_params = n;

    va_end(args);

	// free buffer if already allocated.
	if (msg->data)
		free(msg->data);

	msg->data = (u8 *)malloc(len);
	if (msg->data == NULL) {
		printf("Fail to malloc %d bytes\n", len);
		ret = -1;
		goto ext;
	}
	header->data_len = len;

    for (n = 0, p = msg->data; n < header->n_params; n++) {
        memcpy(p, params[n], header->param_size[n]);
        p += header->param_size[n];
    }

ext:

    return ret;
}


// calculate crc, send message.
static int apisrv_send_message(int fd, struct uffs_ApiSrvMsgSt *msg)
{
    int ret;

    msg->header.data_crc = uffs_crc16sum(msg->data, msg->header.data_len);
    msg->header.header_crc = uffs_crc16sum(&msg->header, sizeof(struct uffs_ApiSrvHeaderSt));

    ret = m_io->write(fd, &msg->header, sizeof(struct uffs_ApiSrvHeaderSt));
    if (ret < 0) {
        perror("Sending header failed");
    }
    else {
        ret = m_io->write(fd, msg->data, msg->header.data_len);
        if (ret < 0) {
            perror("Sending data failed");
        }
    }

    return ret;
}

static int check_apisrv_header(struct uffs_ApiSrvHeaderSt *header)
{
    return 0;
}

static int check_apisrv_msg(struct uffs_ApiSrvMsgSt *msg)
{
    return 0;
}

static int apisrv_read_message(int fd, struct uffs_ApiSrvMsgSt *msg)
{
	int ret = -1;
	struct uffs_ApiSrvHeaderSt *header = &msg->header;
	u8 *data = NULL;

	memset(msg, 0, sizeof(struct uffs_ApiSrvMsgSt));
	ret = m_io->read(fd, header, sizeof(struct uffs_ApiSrvHeaderSt));
	if (ret < 0) {
		printf("Read header failed!\n");
		goto ext;
	}

	ret = check_apisrv_header(header);
	if (ret < 0)
		goto ext;

	if (header->data_len > 0) {
		data = (u8 *)malloc(header->data_len);
		if (data == NULL) {
			printf("malloc %d bytes failed\n", header->data_len);
			goto ext;
		}

		msg->data = data;
		ret = m_io->read(fd, data, header->data_len);
		if (ret < 0) {
			printf("read data failed\n");
			goto ext;
		}
	}

	ret = check_apisrv_msg(msg);
	if (ret < 0) {
		printf("check data CRC failed!\n");
		goto ext;
	}

ext:
	return ret;	
}

static int apisrv_free_message(struct uffs_ApiSrvMsgSt *msg)
{
	if (msg && msg->data) {
		free(msg->data);
		msg->data = NULL;
	}

	return 0;
}

static int process_cmd(int sock, struct uffs_ApiSrvMsgSt *msg, struct uffs_ApiSt *api)
{
    struct uffs_ApiSrvHeaderSt *header = &msg->header;
    int ret = 0;
    char name[256];

    //DBG("Received cmd = %d, params %d, data_len = %d\n", UFFS_API_CMD(header), header->n_params, header->data_len);

    switch(UFFS_API_CMD(header)) {
    case UFFS_API_GET_VER_CMD:
    {
        int val;
        val = api->uffs_version();
		DBG("uffs_version() = 0x%08x\n", val);
        ret = apisrv_make_message(msg, &val, sizeof(val), NULL);
        break;
    }
    case UFFS_API_OPEN_CMD:
    {
        int open_mode;
		int fd;
        ret = apisrv_unload_params(msg, -1, 0, name, sizeof(name), &open_mode, sizeof(open_mode), NULL);
		if (ret == 0) {
			fd = api->uffs_open(name, open_mode);
			DBG("uffs_open(name = \"%s\", open_mode = 0x%x) = %d\n", name, open_mode, fd);
			ret = apisrv_make_message(msg, &fd, sizeof(fd), -1, 0, -1, 0, NULL);
		}
        break;
    }
    case UFFS_API_CLOSE_CMD:
	{
		int fd, r;
		ret = apisrv_unload_params(msg, -1, 0, &fd, sizeof(fd), NULL);
		if (ret == 0) {
			r = api->uffs_close(fd);
			DBG("uffs_close(fd = %d) = %d\n", fd, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_READ_CMD:
	{
		int fd, r, len;
		void *buf = NULL;

		ret = apisrv_unload_params(msg, -1, 0, &fd, sizeof(fd), -1, 0, &len, sizeof(len), NULL);
		if (ret == 0) {
			if (len > 0) {
				buf = malloc(len);
				if (buf == NULL) {
					printf("malloc %d bytes failed.\n", len);
					ret = -1;
				}
			}

			if (ret == 0) {
				r = api->uffs_read(fd, buf, len);
				DBG("uffs_read(fd = %d, buf = {...}, len = %d) = %d\n", fd, len, r);
				ret = apisrv_make_message(msg, &r, sizeof(r),
											-1, 0,	/* fd */
											buf ? buf : (void *)-1, buf ? len : 0,	/* buf */
											-1, 0,	/* len */
											NULL);
			}
		}

		if (buf)
			free(buf);

        break;
	}
    case UFFS_API_WRITE_CMD:
	{
		int fd, r, len;
		void *buf = NULL;

		buf = malloc(header->data_len);
		if (buf == NULL) {
			printf("malloc %d failed.\n", header->data_len);
			ret = -1;
		}
		else {
			ret = apisrv_unload_params(msg, -1, 0, &fd, sizeof(fd), buf, header->data_len, &len, sizeof(len), NULL);
			if (ret == 0) {
				r = api->uffs_write(fd, buf, len);
				DBG("uffs_write(fd = %d, buf = {...}, len = %d) = %d\n", fd, len, r);
				ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, -1, 0, -1, 0, NULL);
			}
			free(buf);
		}

        break;
	}
    case UFFS_API_FLUSH_CMD:
	{
		int fd, r;

		ret = apisrv_unload_params(msg, -1, 0, &fd, sizeof(fd), NULL);
		if (ret == 0) {
			r = api->uffs_flush(fd);
			DBG("uffs_flush(fd = %d) = %d\n", fd, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}

        break;
	}
    case UFFS_API_SEEK_CMD:
	{
		int fd, origin;
		i32 r, offset;

		ret = apisrv_unload_params(msg, -1, 0, &fd, sizeof(fd), &offset, sizeof(offset), &origin, sizeof(origin), NULL);
		if (ret == 0) {
			r = (i32) api->uffs_seek(fd, (long)offset, origin);
			DBG("uffs_seek(fd = %d, offset = %d, origin = %d) = %d\n", fd, offset, origin, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, -1, 0, -1, 0, NULL);
		}

        break;
	}
    case UFFS_API_TELL_CMD:
	{
		int fd;
		i32 r;

		ret = apisrv_unload_params(msg, -1, 0, &fd, sizeof(fd), NULL);
		if (ret == 0) {
			r = (i32) api->uffs_tell(fd);
			DBG("uffs_tell(fd = %d) = %d\n", fd, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_EOF_CMD:
	{
		int fd, r;

		ret = apisrv_unload_params(msg, -1, 0, &fd, sizeof(fd), NULL);
		if (ret == 0) {
			r = api->uffs_eof(fd);
			DBG("uffs_eof(fd = %d) = %d\n", fd, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_RENAME_CMD:
	{
		int r;
		char *oldname = NULL;
		char *newname = NULL;

		oldname = (char *)malloc(header->data_len);
		newname = (char *)malloc(header->data_len);

		if (oldname && newname) {
			ret = apisrv_unload_params(msg, -1, 0, oldname, header->data_len, newname, header->data_len, NULL);
			if (ret == 0) {
				r = api->uffs_rename(oldname, newname);
				DBG("uffs_rename(old = \"%s\", new = \"%s\") = %d\n", oldname, newname, r);
				ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, -1, 0, NULL);
			}
		}
		else {
			printf("malloc %d bytes failed.\n", header->data_len);
			ret = -1;
		}

		if (oldname)
			free(oldname);
		if (newname)
			free(newname);

        break;
	}
    case UFFS_API_REMOVE_CMD:
	{
		int r;

		ret = apisrv_unload_params(msg, -1, 0, name, sizeof(name), NULL);
		if (ret == 0) {
			r = api->uffs_remove(name);
			DBG("uffs_remove(name = \"%s\") = %d\n", name, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_FTRUNCATE_CMD:
	{
		int fd, r;
		i32 remain;

		ret = apisrv_unload_params(msg, -1, 0, &fd, sizeof(fd), &remain, sizeof(remain), NULL);
		if (ret == 0) {
			r = api->uffs_ftruncate(fd, (long)remain);
			DBG("uffs_ftruncate(fd = %d, remain = %d) = %d\n", fd, remain, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_MKDIR_CMD:
	{
		int r;

		ret = apisrv_unload_params(msg, -1, 0, name, sizeof(name), NULL);
		if (ret == 0) {
			r = api->uffs_mkdir(name);
			DBG("uffs_mkdir(name = \"%s\") = %d\n", name, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_RMDIR_CMD:
	{
		int r;

		ret = apisrv_unload_params(msg, -1, 0, name, sizeof(name), NULL);
		if (ret == 0) {
			r = api->uffs_rmdir(name);
			DBG("uffs_rmdir(name= \"%s\") = %d\n", name, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_STAT_CMD:
    case UFFS_API_LSTAT_CMD:
	{
		struct uffs_stat buf;
		int r;

		ret = apisrv_unload_params(msg, -1, 0, name, sizeof(name), -1, 0, NULL);
		if (ret == 0) {
			r = api->uffs_stat(name, &buf);
			DBG("uffs_stat(name = \"%s\", buf = {...}) = %d\n", name, r); 
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, &buf, sizeof(struct uffs_stat), NULL);
		}
        break;
	}
    case UFFS_API_FSTAT_CMD:
	{
		int fd, r;
		struct uffs_stat buf;

		ret = apisrv_unload_params(msg, -1, 0, &fd, sizeof(fd), -1, 0, NULL);
		if (ret == 0) {
			r = api->uffs_fstat(fd, &buf);
			DBG("uffs_fstat(fd = %d, buf = {...}) = %d\n", fd, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, &buf, sizeof(struct uffs_stat), NULL);
		}
        break;
	}
    case UFFS_API_OPEN_DIR_CMD:
	{
		uffs_DIR *dirp;
		
		ret = apisrv_unload_params(msg, -1, 0, name, sizeof(name), NULL);
		if (ret == 0) {
			dirp = api->uffs_opendir(name);
			DBG("uffs_opendir(name = \"%s\") = %p\n", name, dirp);
			ret = apisrv_make_message(msg, &dirp, sizeof(uffs_DIR *), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_CLOSE_DIR_CMD:
	{
		uffs_DIR *dirp;
		int r;

		ret = apisrv_unload_params(msg, -1, 0, &dirp, sizeof(uffs_DIR *), NULL);
		if (ret == 0) {
			r = api->uffs_closedir(dirp);
			DBG("uffs_closedir(dirp = %p) = %d\n", dirp, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_READ_DIR_CMD:
	{
		uffs_DIR *dirp;
		struct uffs_dirent *dent;

		ret = apisrv_unload_params(msg, -1, 0, &dirp, sizeof(uffs_DIR *), NULL);
		if (ret == 0) {
			dent = api->uffs_readdir(dirp);
			DBG("uffs_readdir(dirp = %p) = %s\n", dirp, dent ? "{...}" : "NULL");
			ret = apisrv_make_message(msg, dent, sizeof(struct uffs_dirent), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_REWIND_DIR_CMD:
	{
		uffs_DIR *dirp;

		ret = apisrv_unload_params(msg, -1, 0, &dirp, sizeof(uffs_DIR *), NULL);
		if (ret == 0) {
			api->uffs_rewinddir(dirp);
			DBG("uffs_rewinddir(dirp = %p)\n", dirp);
			ret = apisrv_make_message(msg, 0, -1, 0, -1, NULL);
		}
        break;
	}
    case UFFS_API_GET_ERR_CMD:
	{
		int r;

		r = api->uffs_get_error();
		DBG("uffs_get_error() = %d\n", r);
		ret = apisrv_make_message(msg, &r, sizeof(r), NULL);

        break;
	}
    case UFFS_API_SET_ERR_CMD:
	{
		int err, r;

		ret = apisrv_unload_params(msg, -1, 0, &err, sizeof(err), NULL);
		if (ret == 0) {
			r = api->uffs_set_error(err);
			DBG("uffs_set_error(err = %d) = %d\n", err, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_FORMAT_CMD:
	{
		int r;

		ret = apisrv_unload_params(msg, -1, 0, name, sizeof(name), NULL);
		if (ret == 0) {
			r = api->uffs_format(name);
			DBG("uffs_format(mount = \"%s\") = %d\n", name, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_SPACE_TOTAL_CMD:
	{
		i32 r;

		ret = apisrv_unload_params(msg, -1, 0, name, sizeof(name), NULL);
		if (ret == 0) {
			r = (i32) api->uffs_space_total(name);
			DBG("uffs_space_total(mount = \"%s\") = %d\n", name, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_SPACE_FREE_CMD:
	{
		i32 r;

		ret = apisrv_unload_params(msg, -1, 0, name, sizeof(name), NULL);
		if (ret == 0) {
			r = (i32) api->uffs_space_free(name);
			DBG("uffs_space_free(mount = \"%s\") = %d\n", name, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
    case UFFS_API_SPACE_USED_CMD:
	{
		i32 r;

		ret = apisrv_unload_params(msg, -1, 0, name, sizeof(name), NULL);
		if (ret == 0) {
			r = (i32) api->uffs_space_used(name);
			DBG("uffs_space_used(mount = \"%s\") = %d\n", name, r);
			ret = apisrv_make_message(msg, &r, sizeof(r), -1, 0, NULL);
		}
        break;
	}
	case UFFS_API_FLUSH_ALL_CMD:
	{
		ret = apisrv_unload_params(msg, -1, 0, name, sizeof(name), NULL);
		if (ret == 0) {
			api->uffs_flush_all(name);
			DBG("uffs_flush_all(mount = \"%s\")\n", name);
			ret = apisrv_make_message(msg, -1, 0, -1, 0, NULL);
		}
		break;
	}
    default:
        printf("Unknown command %x\n", header->cmd);
        ret = -1;
        break;
    }

	if (ret == 0) {
		// we might need a mutex here if we using multi-thread server,
		// but this probably ok since it just for statistic purpose.
		m_api_stat[UFFS_API_CMD(header)]++;
	}

	if (ret == 0)
		ret = apisrv_send_message(sock, msg);

    return ret;
}

int apisrv_serve(int fd, struct uffs_ApiSt *api)
{
    int ret = 0;
    struct uffs_ApiSrvMsgSt msg;

	ret = apisrv_read_message(fd, &msg);

    if (ret == 0)
        ret = process_cmd(fd, &msg, api);

	apisrv_free_message(&msg);

    return ret;
}

void apisrv_print_stat(void)
{
	int i;
	printf("--- API call stat ---\n");
	for (i = 0; i <= UFFS_API_CMD_LAST; i++) {
		printf("API %2d: %d\n", i, m_api_stat[i]);
	}
	printf("--- END ---\n");
}

/**
 * variable parameters list:
 *  &ret, size_ret, return_size_ret, &param1, size_param1, return_size_param1, &param2, size_param2, return_size_param2... NULL
 **/
static int call_remote(int cmd, ...)
{
	struct uffs_ApiSrvMsgSt msg;
	struct uffs_ApiSrvHeaderSt *header = &msg.header;
	int ret = -1, fd = -1;
	u32 n = 0;
	u8 *p;
	u32 len, size;
	u8 * params[UFFS_API_MAX_PARAMS];
	u32 return_size[UFFS_API_MAX_PARAMS];
	u32 n_params = 0;
	va_list args;

	memset(&msg, 0, sizeof(struct uffs_ApiSrvMsgSt));

	fd = m_io->open(m_io->addr);
	if (fd < 0) 
		goto ext;

	header->cmd = cmd;

	// parse tparameter list
	va_start(args, cmd);
	for (n = 0, len = 0; n < UFFS_API_MAX_PARAMS; n++) {
		p = va_arg(args, u8 *);
		if (p == NULL)
			break;
		params[n] = p;
		size = va_arg(args, int);
		header->param_size[n] = size;
		header->return_size[n] = va_arg(args, int);
		return_size[n] = header->return_size[n];
		len += size;
	}
	va_end(args);

	n_params = n;
	header->n_params = n;
	//DBG("C: cmd %d, params %d, data_len %d\n", cmd, n, len);

	msg.data = (u8 *) malloc(len);
	if (msg.data == NULL) {
		printf("Fail to malloc %d bytes\n", len);
		goto ext;
	}
	header->data_len = len;

	// now, load parameters
	for (n = 0, len = 0; n < n_params; n++) {
		if (header->param_size[n] > 0) {
			memcpy(msg.data + len, params[n], header->param_size[n]);
			len += header->param_size[n];
		}
	}

	// send
	ret = apisrv_send_message(fd, &msg);
	if (ret < 0)
		goto ext;

	// free data pointer
	apisrv_free_message(&msg);

	// receive response
	ret = apisrv_read_message(fd, &msg);
	if (ret < 0)
		goto ext;

	if (header->n_params != n_params) {
		printf("Response %d parameters but expect %d\n", header->n_params, n_params);
		ret = -1;
		goto ext;
	}

	// now, unload return parameters
	for (n = 0, p = msg.data; n < header->n_params; n++) {
		size = header->param_size[n];
		if (return_size[n] != header->return_size[n]) {
			printf("WARNING: cmd %d param %d return size not kept ? expect %d but %d\n", header->cmd, n, return_size[n], header->return_size[n]);
		}
		memcpy(params[n], p, size > return_size[n] ? return_size[n] : size);
		if (size > return_size[n]) {
			printf("WARNING: cmd %d return param %d overflow, expect %d but %d\n", header->cmd, n, return_size[n], size);
		}
		p += size;
	}
	
ext:
	apisrv_free_message(&msg);
	if (fd >= 0)
		m_io->close(fd);

	return ret;

}

static int _uffs_version(void)
{
	int version = 0;
	int ret = -1;

	ret = call_remote(UFFS_API_GET_VER_CMD, &version, 0, sizeof(version), NULL);

	return ret < 0 ? 0 : version;
}

static int _uffs_open(const char *name, int oflag, ...)
{
	int fd = -1;
	int ret = -1;

	ret = call_remote(UFFS_API_OPEN_CMD, &fd, 0, sizeof(fd), 
						name, strlen(name) + 1, 0, 
						&oflag, sizeof(oflag), 0, 
						NULL);

	return ret < 0 ? ret : fd;
}

static int _uffs_close(int fd)
{
	int r = -1;
	int ret = -1;

	ret = call_remote(UFFS_API_CLOSE_CMD, &r, 0, sizeof(r), &fd, sizeof(fd), 0, NULL);

	return ret < 0 ? ret : r;
}

static int _uffs_read(int fd, void *buf, int len)
{
	int r = -1, ret = -1;

	if (buf) {
		ret = call_remote(UFFS_API_READ_CMD, &r, 0, sizeof(r), 
						&fd, sizeof(fd), 0, 
						buf, 0, len, 
						&len, sizeof(len), 0,
						NULL);
	}

	return ret < 0 ? ret : r;
}

static int _uffs_write(int fd, const void *buf, int len)
{
	int r = -1, ret = -1;

	if (buf) {
		ret = call_remote(UFFS_API_WRITE_CMD, &r, 0, sizeof(r),
						&fd, sizeof(fd), 0,
						buf, len, 0,
						&len, sizeof(len), 0,
						NULL);
	}

	return ret < 0 ? ret : r;
}

static int _uffs_flush(int fd)
{
	int r = -1, ret = -1;

	ret = call_remote(UFFS_API_FLUSH_CMD, &r, 0, sizeof(r),
						&fd, sizeof(fd), 0,
						NULL);

	return ret < 0 ? ret : r;
}

static long _uffs_seek(int fd, long offset, int origin)
{
	i32 r_32bit = -1;
	int ret = -1;

	i32 offset_32bit = (i32)offset;

	ret = call_remote(UFFS_API_SEEK_CMD, &r_32bit, 0, sizeof(r_32bit),
						&fd, sizeof(fd), 0,
						&offset_32bit, sizeof(offset_32bit), 0,	// only send 32bit over the network
						&origin, sizeof(origin), 0,
						NULL);

	return ret < 0 ? -1L : (long)r_32bit;
}

static long _uffs_tell(int fd)
{
	int ret = -1;
	i32 r_32bit = -1;

	ret = call_remote(UFFS_API_TELL_CMD, &r_32bit, 0, sizeof(r_32bit),
						&fd, sizeof(fd), 0,
						NULL);

	return ret < 0 ? -1L : (long)r_32bit;
}

static int _uffs_eof(int fd)
{
	int r = -1, ret = -1;

	ret = call_remote(UFFS_API_EOF_CMD, &r, 0, sizeof(r),
						&fd, sizeof(fd), 0,
						NULL);

	return ret < 0 ? ret : r;
}

static int _uffs_rename(const char *oldname, const char *newname)
{
	int r = -1, ret = -1;

	if (oldname && newname) {
		ret = call_remote(UFFS_API_RENAME_CMD, &r, 0, sizeof(r),
							oldname, strlen(oldname) + 1, 0,
							newname, strlen(newname) + 1, 0,
							NULL);
	}

	return ret < 0 ? ret : r;
}

static int _uffs_remove(const char *name)
{
	int ret = -1, r = -1;

	if (name) {
		ret = call_remote(UFFS_API_REMOVE_CMD, &r, 0, sizeof(r),
							name, strlen(name) + 1, 0,
							NULL);
	}

	return ret < 0 ? ret : r;
}

static int _uffs_ftruncate(int fd, long remain)
{
	int r = -1, ret = -1;
	i32 remain_32bit = (i32)remain;

	ret = call_remote(UFFS_API_FTRUNCATE_CMD, &r, 0, sizeof(r),
						&fd, sizeof(fd), 0,
						&remain_32bit, sizeof(remain_32bit), 0,
						NULL);

	return ret < 0 ? ret : r;
}

static int _uffs_mkdir(const char *name, ...)
{
	int r = -1, ret = -1;

	if (name) {
		ret = call_remote(UFFS_API_MKDIR_CMD, &r, 0, sizeof(r),
							name, strlen(name) + 1, 0,
							NULL);
	}

	return ret < 0 ? ret : r;
}

static int _uffs_rmdir(const char *name)
{
	int r = -1, ret = -1;

	if (name) {
		ret = call_remote(UFFS_API_RMDIR_CMD, &r, 0, sizeof(r),
							name, strlen(name) + 1, 0,
							NULL);
	}

	return ret < 0 ? ret : r;
}

static int _uffs_stat(const char *name, struct uffs_stat *buf)
{
	int r = -1, ret = -1;

	if (name && buf) {
		ret = call_remote(UFFS_API_STAT_CMD, &r, 0, sizeof(r),
							name, strlen(name) + 1, 0,
							buf, 0, sizeof(struct uffs_stat),
							NULL);
	}

	return ret < 0 ? ret : r;
}

static int _uffs_lstat(const char *name, struct uffs_stat *buf)
{
	int r = -1, ret = -1;

	if (name && buf) {
		ret = call_remote(UFFS_API_LSTAT_CMD, &r, 0, sizeof(r),
							name, strlen(name) + 1, 0,
							buf, 0, sizeof(struct uffs_stat),
							NULL);
	}

	return ret < 0 ? ret : r;
}

static int _uffs_fstat(int fd, struct uffs_stat *buf)
{
	int r = -1, ret = -1;

	if (buf) {
		ret = call_remote(UFFS_API_FSTAT_CMD, &r, 0, sizeof(r),
							&fd, sizeof(fd), 0,
							buf, 0, sizeof(struct uffs_stat),
							NULL);
	}

	return ret < 0 ? ret : r;
}

static uffs_DIR * _uffs_opendir(const char *path)
{
	uffs_DIR *dirp = NULL;
	int ret = -1;

	if (path) {
		ret = call_remote(UFFS_API_OPEN_DIR_CMD, &dirp, 0, sizeof(uffs_DIR *),
							path, strlen(path) + 1, 0,
							NULL);
	}

	return ret < 0 ? NULL : dirp;
}

static int _uffs_closedir(uffs_DIR *dirp)
{
	int r = -1, ret = -1;

	if (dirp) {
		ret = call_remote(UFFS_API_CLOSE_DIR_CMD, &r, 0, sizeof(r),
							&dirp, sizeof(uffs_DIR *), 0,
							NULL);
	}

	return ret < 0 ? ret : r;
}

/**
 * Note: this is not a thread-safe but we have advantage of not calling 'free' after ...
 */
static struct uffs_dirent * _uffs_readdir(uffs_DIR *dirp)
{
	static struct uffs_dirent dirent_cache[256];
	static unsigned char pos = 0;

	int ret = -1;
	struct uffs_dirent *dent = NULL;

	if (dirp) {
		dent = &dirent_cache[pos++]; // change 'pos++' to atomic can make this function thread-safe... 
		ret = call_remote(UFFS_API_READ_DIR_CMD, dent, 0, sizeof(struct uffs_dirent),
							&dirp, sizeof(uffs_DIR *), 0,
							NULL);
	}

	return ret < 0 ? NULL : dent;
}

static void _uffs_rewinddir(uffs_DIR *dirp)
{
	if (dirp) {
		call_remote(UFFS_API_REWIND_DIR_CMD, -1, 0, 0,
						&dirp, sizeof(uffs_DIR *), 0,
						NULL);
	}
}

static int _uffs_get_error(void)
{
	int r = -1, ret = -1;

	ret = call_remote(UFFS_API_GET_ERR_CMD, &r, 0, sizeof(r), NULL);

	return ret < 0 ? ret : r;
}

static int _uffs_set_error(int err)
{
	int r = -1, ret = -1;

	ret = call_remote(UFFS_API_SET_ERR_CMD, &r, 0, sizeof(r),
						&err, sizeof(err), 0,
						NULL);

	return ret < 0 ? ret : r;
}

static int _uffs_format(const char *mount)
{
	int r = -1, ret = -1;

	if (mount)
		ret = call_remote(UFFS_API_FORMAT_CMD, &r, 0, sizeof(r),
						mount, strlen(mount) + 1, 0,
						NULL);

	return ret < 0 ? ret : r;
}

static long _uffs_space_total(const char *mount)
{
	i32 r_32bit = -1;
	int ret = -1;

	if (mount)
		ret = call_remote(UFFS_API_SPACE_TOTAL_CMD, &r_32bit, 0, sizeof(r_32bit),
							mount, strlen(mount) + 1, 0,
							NULL);

	return ret < 0 ? -1L : (long)r_32bit;
}

static long _uffs_space_used(const char *mount)
{
	i32 r_32bit = -1;
	int ret = -1;

	if (mount)
		ret = call_remote(UFFS_API_SPACE_USED_CMD, &r_32bit, 0, sizeof(r_32bit),
							mount, strlen(mount) + 1, 0,
							NULL);

	return ret < 0 ? -1L : (long)r_32bit;
}

static long _uffs_space_free(const char *mount)
{
	i32 r_32bit = -1;
	int ret = -1;

	if (mount)
		ret = call_remote(UFFS_API_SPACE_FREE_CMD, &r_32bit, 0, sizeof(r_32bit),
							mount, strlen(mount) + 1, 0,
							NULL);

	return ret < 0 ? -1L : (long)r_32bit;
}

static void _uffs_flush_all(const char *mount)
{
	if (mount) {
		call_remote(UFFS_API_FLUSH_ALL_CMD, -1, 0, 0,
							mount, strlen(mount) + 1, 0,
							NULL);
	}
}


static struct uffs_ApiSt m_client_api = {
	_uffs_version,
	_uffs_open,
	_uffs_close,
	_uffs_read,
	_uffs_write,
	_uffs_flush,
	_uffs_seek,
	_uffs_tell,
	_uffs_eof,
	_uffs_rename,
	_uffs_remove,
	_uffs_ftruncate,
	_uffs_mkdir,
	_uffs_rmdir,
	_uffs_stat,
	_uffs_lstat,
	_uffs_fstat,
	_uffs_opendir,
	_uffs_closedir,
	_uffs_readdir,
	_uffs_rewinddir,
	_uffs_get_error,
	_uffs_set_error,
	_uffs_format,
	_uffs_space_total,
	_uffs_space_used,
	_uffs_space_free,
	_uffs_flush_all,
};

struct uffs_ApiSt * apisrv_get_client(void)
{
	return &m_client_api;
}

