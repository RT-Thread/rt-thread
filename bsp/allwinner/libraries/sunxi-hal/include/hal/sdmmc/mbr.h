/*
****************************************************************************************************
*                                               MELIS
*                               the Easy Portable/Player Develop Kits
*                                           SDMMC Module
*
*                           (c) Copyright 2011-2014, All winners Co,Ld.
*                                       All Rights Reserved
*
* File    : mbr.h
* By      : james.deng
* Version : 1.0.0
* Date    : 2011-11-28
* Descript:
* Update  : <date>          <author>            <version>           <notes>
*           2011-11-28      james.deng          1.0.0               build the file.
****************************************************************************************************
*/

#ifndef __MBR_H__
#define __MBR_H__

// #include <mod_defs.h>

#define MAX_PART_COUNT                  8                                       // max part count
#define MBR_COPY_NUM                    4                                       // mbr backup count

#define MBR_START_ADDRESS               0x0                                     // mbr start address
#define MBR_SIZE                        1024                                    // mbr size
#define MBR_RESERVED                    (MBR_SIZE - 20 - (MAX_PART_COUNT * 64)) // mbr reserved space

// part information
typedef struct tag_PARTITION
{
    __u32 addrhi;                       // start address high 32 bit
    __u32 addrlo;                       // start address low 32 bit
    __u32 lenhi;                        // size high 32 bit
    __u32 lenlo;                        // size low 32 bit
    __u8  classname[12];                // major device name
    __u8  name[12];                     // minor device name
    __u8  res[24];                      // reserved
} PARTITION;                            // 64 bytes 应该使用 pack

// mbr information
typedef struct tag_MBR
{
    __u32 crc32;                        // crc, from byte 4 to mbr tail
    __u32 version;                      // version
    __u8  magic[8];                     // magic number
    __u8  copy;                         // mbr backup count
    __u8  index;                        // current part no
    __u16 PartCount;                    // part counter
    PARTITION array[MAX_PART_COUNT];    // part info
    __u8  res[MBR_RESERVED];            // reserved space
} MBR;

#define     SUNXI_MBR_SIZE              (16 * 1024)
#define     SUNXI_MBR_MAX_PART_COUNT    120
/* partition information */
typedef struct sunxi_partition_t
{
    unsigned  int       addrhi;
    unsigned  int       addrlo;
    unsigned  int       lenhi;
    unsigned  int       lenlo;
    unsigned  char      classname[16];
    unsigned  char      name[16];
    unsigned  int       user_type;
    unsigned  int       keydata;
    unsigned  int       ro;
    unsigned  int       sig_verify;
    unsigned  int       sig_erase;
    unsigned  int       sig_value[4];
    unsigned  int       sig_pubkey;
    unsigned  int       sig_pbumode;
    unsigned  char      reserved2[36];
}__attribute__ ((packed))sunxi_partition;

/* mbr information */
typedef struct sunxi_mbr
{
    unsigned  int       crc32;                      // crc 1k - 4
    unsigned  int       version;                    // 版本信息， 0x00000100
    unsigned  char      magic[8];                   //"softw311"
    unsigned  int       copy;                       //分数
    unsigned  int       index;                      //第几个MBR备份
    unsigned  int       PartCount;                  //分区个数
    unsigned  int       stamp[1];                   //对齐
    sunxi_partition     array[SUNXI_MBR_MAX_PART_COUNT];    //
    unsigned  int       lockflag;
    unsigned  char      res[(SUNXI_MBR_SIZE - 32 - 4 - (SUNXI_MBR_MAX_PART_COUNT * sizeof(sunxi_partition)))];
}__attribute__ ((packed)) sunxi_mbr_t;

#endif // __MBR_H__
