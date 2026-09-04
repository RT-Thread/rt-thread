/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#include <dfs_romfs.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

static int _copy_file(const char *src, const char *dst)
{
    static char buf[2048];
    int rfd, wfd, len, ret = 0;

    rfd = open(src, O_RDONLY);
    if (rfd < 0)
    {
        return -1;
    }
    wfd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (wfd < 0)
    {
        close(rfd);
        return -1;
    }
    while ((len = read(rfd, buf, sizeof(buf))) > 0)
    {
        if (write(wfd, buf, len) != len)
        {
            ret = -1;
            break;
        }
    }
    close(rfd);
    close(wfd);
    return ret;
}

int mnt_init(void)
{
    /* FAT on ramdisk as root: the ELF loader needs mmap support */
    if (dfs_mkfs("elm", "ramdisk0") != 0)
    {
        rt_kprintf("mkfs elm on ramdisk0 failed!\n");
        return -1;
    }
    if (dfs_mount("ramdisk0", "/", "elm", 0, 0) != 0)
    {
        rt_kprintf("elmfat mounted on / failed!\n");
        return -1;
    }

    mkdir("/rom", 0777);
    mkdir("/bin", 0777);
    mkdir("/etc", 0777);
    mkdir("/dev", 0777);
    mkdir("/dev/shm", 0777);

    /* built-in romfs image holds the user applications */
    if (dfs_mount(RT_NULL, "/rom", "rom", 0, &romfs_root) != 0)
    {
        rt_kprintf("romfs mounted on /rom failed!\n");
        return -1;
    }

    /* copy user applications to the writable root so they can be mmap-ed */
    if (_copy_file("/rom/bin/hello", "/bin/hello") != 0)
    {
        rt_kprintf("no user application in the built-in romfs image\n");
    }

    rt_kprintf("file system initialization done!\n");

    return 0;
}
INIT_ENV_EXPORT(mnt_init);

#endif /* RT_USING_DFS */
