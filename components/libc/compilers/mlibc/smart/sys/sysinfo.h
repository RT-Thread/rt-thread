/*
 * Copyright (c) mlibc & plct lab
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/8/8   0Bitbiscuits the first version
 */
#ifndef MLIBC_SYS_SYSINFO_H__
#define MLIBC_SYS_SYSINFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#define SI_LOAD_SHIFT 16

struct sysinfo {
    unsigned long uptime;
    unsigned long loads[3];
    unsigned long totalram;
    unsigned long freeram;
    unsigned long sharedram;
    unsigned long bufferram;
    unsigned long totalswap;
    unsigned long freeswap;
    unsigned short procs, pad;
    unsigned long totalhigh;
    unsigned long freehigh;
    unsigned mem_unit;
    char __reserved[256];
};

int sysinfo (struct sysinfo *);
int get_nprocs_conf (void);
int get_nprocs (void);
long get_phys_pages (void);
long get_avphys_pages (void);

#ifdef __cplusplus
}
#endif

#endif /* MLIBC_SYS_SYSINFO_H__ */
