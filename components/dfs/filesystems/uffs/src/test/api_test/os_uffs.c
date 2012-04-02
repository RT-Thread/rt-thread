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
* \file os_uffs.c
* \brief This file is for interfacing UFFS to sqlite3 UNIX VFS, so that we
*        can use sqlite3's test case to test out UFFS.
* 
* \author Ricky Zheng, created at 22 Dec, 2011 
*/

#define _GNU_SOURCE
#define _XOPEN_SOURCE 500

#include "uffs/uffs_types.h"
#include "uffs/uffs_fd.h"

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "api_test.h"


#if 1
#define DBG(args...) \
	do { \
		printf(args); \
		fflush(stdout); \
	} while(0)

#else
#define DBG(...) do{}while(0)
#endif

#define ASSERT(cond, fmt, ...) \
	do { \
		if (!(cond)) { \
			printf("Assert (" #cond ") fail at %s:%s:%d: ", __FILE__, __FUNCTION__, __LINE__); \
			printf(fmt, ## __VA_ARGS__); \
			fflush(stdout); \
			exit(1); \
		} \
	} while (0)

#define MAX_OPEN_FDS 50
struct fdmap_s {
    int unix_fd;
    int uffs_fd;
	int bak_fd;
	char name[256];
    int valid;
};
static struct fdmap_s m_fdmap[MAX_OPEN_FDS];
static struct fdmap_s m_fdmap_ext[MAX_OPEN_FDS];
static pthread_mutex_t m_fdmap_mutex = PTHREAD_MUTEX_INITIALIZER;

#define LOCK() pthread_mutex_lock(&m_fdmap_mutex)
#define UNLOCK() pthread_mutex_unlock(&m_fdmap_mutex)

static const char * get_uffs_name(const char *unix_name)
{
	const char *p = NULL;
	if (unix_name) {
		p = (char *)unix_name + strlen(unix_name) - 1;
		for (; *p != '/' && p > unix_name; p--);
	}

	return p;
}

#define FOR_EACH_FD(s, map, p) \
	for (p = &map[0], s = &map[MAX_OPEN_FDS]; p < s; p++) \
		if (p->valid)


static void open_check_fd(int unix_fd, int uffs_fd, const char *unix_name)
{
	int n = 0;
	struct fdmap_s *s, *p;

	LOCK();
	FOR_EACH_FD(s, m_fdmap, p) {
		if (p->unix_fd == unix_fd &&
				strcmp(p->name, unix_name) == 0)
			n++;
	}
	FOR_EACH_FD(s, m_fdmap_ext, p) {
		if (p->unix_fd == unix_fd &&
				strcmp(p->name, unix_name) == 0)
			n++;
	}
	UNLOCK();
	ASSERT(n == 1, "unix fd %d (name= %s) have %d entries\n", unix_fd, unix_name, n);

	if (uffs_fd >= 0) {
		n = 0;
		LOCK();
		FOR_EACH_FD(s, m_fdmap, p) {
			if (p->uffs_fd == uffs_fd &&
					strcmp(get_uffs_name(p->name), get_uffs_name(unix_name)) == 0)
				n++;
		}
		UNLOCK();
		ASSERT(n == 1, "uffs fd %d (name = %s) have %d entries\n", uffs_fd, get_uffs_name(unix_name), n);
	}
}

static void unlink_check_fd(const char *unix_name)
{
	struct fdmap_s *s, *p;

	LOCK();
	FOR_EACH_FD(s, m_fdmap, p) {
		if (strcmp(p->name, unix_name) == 0) {
			// there file already open ? close it ...
			DBG("WARNING: unlink %s, but file is not closed ?\n", unix_name);
		}
	}
	FOR_EACH_FD(s, m_fdmap_ext, p) {
		if (strcmp(p->name, unix_name) == 0) {
			DBG("WARNING: unlink %s, but file is not closed ?\n", unix_name);
		}
	}
	UNLOCK();

}

// return 0 if not in skip table, else return non-zero. 
static int check_skip_tbl(const char *path)
{
	static const char *skip_tbl[] = {
		"/dev/", "/var/", "/tmp/", "/proc/", "/usr/", "/lib/", "/opt/", "/bin/", NULL /* end */
	};
	int i = 0;

	for (i = 0; skip_tbl[i] != NULL; i++) {
		if (memcmp(path, skip_tbl[i], strlen(skip_tbl[i])) == 0)
			return 1;
	}

	return 0;	
}

static int unix2uffs(int unix_fd, int *uffs_fd, int *bak_fd)
{
    int ret = -1;
    struct fdmap_s *s, *p;

    LOCK();
	FOR_EACH_FD(s, m_fdmap, p) {
        if (p->unix_fd == unix_fd) {
			if (*uffs_fd)
				*uffs_fd = p->uffs_fd;
			if (bak_fd)
				*bak_fd = p->bak_fd;
			ret = 0;
            break;
        }
    }
    UNLOCK();

    return ret;
}

static int push_newfd(const char *unix_name, int unix_fd, int uffs_fd, int bak_fd)
{
    int ret = -1;
    struct fdmap_s *p, *end;

    if (unix_fd < 0)
        return -1;

    if (uffs_fd >= 0) {
        p = &m_fdmap[0];
        end = &m_fdmap[MAX_OPEN_FDS];
    }
    else {
        p = &m_fdmap_ext[0];
        end = &m_fdmap_ext[MAX_OPEN_FDS];
    }

    LOCK();
    while (p < end) {
        if (!p->valid) {
            p->unix_fd = unix_fd;
            p->uffs_fd = uffs_fd;
			p->bak_fd = bak_fd;
			strcpy(p->name, unix_name);
            p->valid = 1;
            ret = 0;
			DBG("push_newfd(unix_fd = %d, uffs_fd = %d, bak_fd = %d)\n", unix_fd, uffs_fd, bak_fd);
            break;
        }
        p++;
    }
    UNLOCK();

    return ret;
}

static int remove_fd(int unix_fd)
{
    int ret = -1;
    struct fdmap_s *s, *p;


    LOCK();
	FOR_EACH_FD(s, m_fdmap, p) {
        if (p->unix_fd == unix_fd) {
            p->valid = 0;
            ret = 0;
			DBG("remove_fd(unix_fd = %d), uffs_fd = %d, bak_fd = %d\n", unix_fd, p->uffs_fd, p->bak_fd);
            break;
        }
    }

    if (ret != 0) {
		FOR_EACH_FD(s, m_fdmap_ext, p) {
            if (p->unix_fd == unix_fd) {
                p->valid = 0;
                ret = 0;
				DBG("remove_fd(unix_fd = %d), no uffs_fd\n", unix_fd);
                break;
            }
        }
    }

    UNLOCK();

    return ret;
}

int os_open(const char *name, int flags, int mode)
{
    int fd = -1;
    int uffs_fd = -1, uffs_flags = 0;
	int bak_fd = -1;
	const char *p;
	char bak_name[256] = {0};

    fd = open(name, flags, mode);

    if (check_skip_tbl(name) == 0 && fd >= 0) {
        uffs_flags = 0;
        if (flags & O_WRONLY) uffs_flags |= UO_WRONLY;
        if (flags & O_RDWR) uffs_flags |= UO_RDWR;
        if (flags & O_CREAT) uffs_flags |= UO_CREATE;
        if (flags & O_TRUNC) uffs_flags |= UO_TRUNC;
        if (flags & O_EXCL) uffs_flags |= UO_EXCL;
		
		p = get_uffs_name(name);
		uffs_fd = uffs_open(p, uffs_flags);
		if (uffs_fd >= 0) {
			sprintf(bak_name, "bak%s", p);
			bak_fd = open(bak_name, flags, mode);
		}

		// sqlite3 testing script might delete test.db file outside the control of sqlite lib, 
		// so we need to detect that situation.
		if ( /* strcmp(p, "/test.db") == 0 && */ uffs_fd >= 0 && (flags & O_CREAT)) {
			ASSERT(bak_fd >= 0, "bak name = %s, bak fd = %d\n", bak_name, bak_fd); 
			struct stat sbuf;
			if (fstat(fd, &sbuf) == 0 && sbuf.st_size == 0) {
				// "test.db" file just been created, we should also do that on UFFS as well
				uffs_ftruncate(uffs_fd, 0);
				ftruncate(bak_fd, 0);
			}
		}
    }

	if (fd > 0) {
	    ASSERT(!push_newfd(name, fd, uffs_fd, bak_fd), "push_newfd(fd=%d, uffs_fd=%d, bak_fd=%d)\n", fd, uffs_fd, bak_fd);
		open_check_fd(fd, uffs_fd, name);
	}

	DBG("open(name = \"%s\", flags = 0x%x, mode = 0x%x) = %d %s\n", name, flags, mode, fd, uffs_fd >= 0 ? "U" : "");

    return fd;
}

int os_unlink(const char *name)
{
	int ret = -1, uffs_ret = -1, bak_ret = -1;
	const char *p = NULL;
	char bak_name[256];

	if (name) {
		unlink_check_fd(name);
		ret = unlink(name);
		if (check_skip_tbl(name) == 0) {
			p = get_uffs_name(name);
			uffs_ret = uffs_remove(p);
			sprintf(bak_name, "bak%s", p);
			bak_ret = unlink(bak_name);
			ASSERT(uffs_ret == ret && ret == bak_ret, "unlink(\"%s\"), unix return %d, uffs return %d, bak return %d\n", name, ret, uffs_ret, bak_ret);
		}
	}
	DBG("unlink(name = \"%s\") = %d %s\n", name, ret, p ? "U" : "");

	return ret;
}

int os_close(int fd)
{
    int uffs_fd = -1, bak_fd = -1;
    int ret = -1;
	int x = -1;

    if (fd >= 0) {
        unix2uffs(fd, &uffs_fd, &bak_fd);
        if (uffs_fd >= 0) {
            uffs_close(uffs_fd);
        }
		if (bak_fd >= 0)
			close(bak_fd);

		x = remove_fd(fd);
        //ASSERT(!x, "remove_fd(%d) failed.\n", fd);
        ret = close(fd);
    }

	DBG("close(fd = %d) = %d  %s\n", fd, ret, uffs_fd >= 0 ? "U" : "");

    return ret;
}

int os_read(int fd, void *buf, int len)
{
	int uffs_fd = -1, uffs_ret = -1, bak_fd = -1, bak_ret = -1;
	int ret = -1;
	void *uffs_buf = NULL;
	void *bak_buf = NULL;
	int i;
	unsigned char a,b,c;

	if (fd >= 0) {
		unix2uffs(fd, &uffs_fd, &bak_fd);
		if (uffs_fd >= 0) {
			uffs_buf = malloc(len);
			bak_buf = malloc(len);
			ASSERT(uffs_buf != NULL || bak_buf == NULL, "malloc(%d) failed.\n", len);
			uffs_ret = uffs_read(uffs_fd, uffs_buf, len);
			bak_ret = read(bak_fd, bak_buf, len);
		}
		ret = read(fd, buf, len);
		if (uffs_fd >= 0) {
			ASSERT(ret == uffs_ret && uffs_ret == bak_ret, "read(fd=%d/%d/%d,buf,len=%d), unix return %d, uffs return %d, bak return %d\n", fd, uffs_fd, bak_fd, len, ret, uffs_ret, bak_ret);
			//assert(memcmp(buf, uffs_buf, len) == 0);	
			if (ret > 0) {
				if (memcmp(buf, uffs_buf, ret) != 0) {
					DBG("ERR: read result different! from fd = %d/%d, len = %d, ret = %d\n", fd, uffs_fd, len, ret);
						printf("\t  POS  unix  uffs  bak\n");	
					for (i = 0; i < len; i++) {
						a = *(((char *)buf) + i);
						b = *(((char *)uffs_buf) + i);
						c = *(((char *)bak_buf) + i);
						printf("\t0x%08d: 0x%02x 0x%02x 0x%02x%s\n", i, a, b, c, a == b && b == c ? "" : "  <----");
					}
					fflush(stdout);
					assert(0);
				}
			}
		}
	}

	if (uffs_buf)
		free(uffs_buf);

	if (bak_buf)
		free(bak_buf);

	DBG("read(fd = %d, buf = {...}, len = %d) = %d %s\n", fd, len, ret, uffs_fd >= 0 ? "U" : "");

	return ret;
}

int os_write(int fd, const void *buf, int len)
{
	int uffs_fd = -1, uffs_ret = -1, bak_fd = -1, bak_ret = -1;
	int ret = -1;

	if (fd >= 0) {
		unix2uffs(fd, &uffs_fd, &bak_fd);
		if (uffs_fd >= 0) {
			uffs_ret = uffs_write(uffs_fd, buf, len);
			ASSERT(bak_fd >= 0, "uffs_fd = %d, bak_fd = %d\n", uffs_fd, bak_fd);
			bak_ret = write(bak_fd, buf, len);
		}
		ret = write(fd, buf, len);
		if (uffs_fd >= 0) {
			ASSERT(ret == uffs_ret && ret == bak_ret, "write(fd=%d/%d/%d,buf,len=%d), unix return %d, uffs return %d, bak return %d\n", fd, uffs_fd, bak_fd, len, ret, uffs_ret, bak_ret);
		}
	}

	DBG("write(fd = %d, buf = {...}, len = %d) = %d  %s\n", fd, len, ret, uffs_fd >= 0 ? "U" : "");

	return ret;
}

int os_lseek(int fd, long offset, int origin)
{
	long ret = -1;
	int uffs_fd = -1, bak_fd = -1;
	long uffs_ret = -1L, bak_ret = -1L;
	int uffs_origin = 0;

	if (fd >= 0) {
		unix2uffs(fd, &uffs_fd, &bak_fd);
		if (uffs_fd >= 0) {
			if (origin == SEEK_CUR)
				uffs_origin = USEEK_CUR;
			else if (origin == SEEK_SET)
				uffs_origin = USEEK_SET;
			else if (origin == SEEK_END)
				uffs_origin = USEEK_END;

			uffs_ret = uffs_seek(uffs_fd, offset, uffs_origin);
			bak_ret = lseek(bak_fd, offset, origin);
		}

		ret = lseek(fd, offset, origin);

		if (uffs_fd >= 0) {
			ASSERT(ret == uffs_ret && ret == bak_ret, "lseek(fd=%d/%d/%d, offset=%ld, origin=%d), unix return %ld, uffs return %ld, bak return %ld\n", fd, uffs_fd, bak_fd, offset, origin, ret, uffs_ret, bak_ret);
		}
	}

	DBG("lseek(fd = %d, offset = %ld, origin = %d) = %ld  %s\n", fd, offset, origin, ret, uffs_fd >= 0 ? "U" : "");

	return ret;
}

int os_pread(int fd, void *buf, int count, long offset)
{
	DBG("pread(fd = %d, buf = {...}, count = %d, offset = %ld)\n", fd, count, offset);
	assert(0);
	return pread(fd, buf, count, offset);
}

int os_pwrite(int fd, const void *buf, int count, long offset)
{
	DBG("pwrite(fd = %d, buf = {..}, count = %d, offset = %ld)\n", fd, count, offset);
	assert(0);
	return pwrite(fd, buf, count, offset);
}

int os_ftruncate(int fd, long length)
{
	int uffs_fd = -1, uffs_ret = -1, bak_fd = -1, bak_ret = -1;
	int ret = -1;

	if (fd >= 0) {
		unix2uffs(fd, &uffs_fd, &bak_fd);
		ret = ftruncate(fd, length);
		if (uffs_fd >= 0) {
			uffs_ret = uffs_ftruncate(uffs_fd, length);
			bak_ret = ftruncate(bak_fd, length);
			ASSERT(ret == uffs_ret && ret == bak_ret,
					"ftruncate(fd=%d/%d/%d, length=%ld), unix ret %d, uffs ret %d, bak ret %d\n",
					fd, uffs_fd, bak_fd, length, ret, uffs_ret, bak_ret);
		}
	}
	DBG("ftruncate(fd = %d, length = %ld) = %d %s\n", fd, length, ret, uffs_fd >= 0 ? "U" : "");

	return ret;
}

int os_posix_fallocate(int fd, long offset, long len)
{
	assert(0);
	DBG("posix_fallocate(fd = %d, offset = %ld, len = %ld)\n", fd, offset, len);
	return posix_fallocate(fd, offset, len);
}

int os_uffs_init(void)
{
	static int inited = 0;
	const char *apisrv_addr;

	if (!inited) {
		inited = 1;
		memset(m_fdmap, 0, sizeof(m_fdmap));
		memset(m_fdmap_ext, 0, sizeof(m_fdmap_ext));

		mkdir("bak", 0777);	// for mirroring UFFS 

		apisrv_addr = getenv("UFFS_TEST_SRV_ADDR");
		if (apisrv_addr == NULL)
			apisrv_addr = "127.0.0.1";

		DBG("os_uffs_init() called, server addr: %s\n", apisrv_addr);
	
		return api_client_init(apisrv_addr);
	}
	else
		return 0;
}
