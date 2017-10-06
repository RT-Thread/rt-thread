/*****************************************************************************
 *
 *            Copyright Andes Technology Corporation 2007-2008
 *                         All Rights Reserved.
 *
 *  Revision History:
 *
 *    Sep.26.2007     Created.
 ****************************************************************************/

/*****************************************************************************
 *
 * FILE NAME                                         VERSION
 *
 *   sdd_sd.h
 *
 * DESCRIPTION
 *
 *   Secure digital card specification 2.0 definition.
 *
 *   Currently only Secure Digital Memory standards are well-defined.
 *   Remaining spec mostly are left for future developers.
 *
 * DATA STRUCTURES
 *
 *   None
 *
 * DEPENDENCIES
 *
 *   None
 *
 ****************************************************************************/
#ifndef __SDD_SD_H__
#define __SDD_SD_H__

#include <hal.h>

/*****************************************************************************
 * Secure Digital Memory Card Register Definitions
 *
 * Summary:
 *                    read                                            program
 *   ---- --------    ----------------------------------------------  ---------------------
 *   OCR   32 bits    CMD8_SEND_IF_COND/R7 ACMD41_SD_SEND_OP_COND/R3
 *   CID  128 bits    CMD2_ALL_SEND_CIS/R2  CMD10_SEND_CID/R2
 *   CSD  128 bits    CMD9_SEND_CSD/R2                                CMD27_PROGRAM_CSD/R1
 *   SCR   64 bits    ACMD51_SEND_SCR/R1
 *   RCA   16 bits    CMD3_SEND_RELATIVE_ADDR/R6
 *   DSR   16 bits                                                    CMD4_SET_DSR
 *   CSR   32 bits    CMD13_SEND_STATUS/R1
 *   SSR  512 bits    ACMD13_SD_STATUS/R1
 *
 * Responses:
 *   R1    48 bits (cmd) (normal response reg)
 *           [45:40] cmd_idx [39:08] CSR [7:1] CRC
 *   R1b   48 bits (cmd) busy signal (dat)
 *           [45:40] cmd_idx [39:08] CSR [7:1] CRC
 *   R2    136 bits (cmd) (CID, CSD reg)
 *           [127:1] CID/CSD (CRC included)
 *   R3    48 bits (cmd) (OCR reg))
 *           [39:8] OCR
 *   R6    48 bits (cmd) (RCA reg)
 *           [45:40] cmd_idx (0x03 CMD3) [39:24] New published RCA [23:8] CSR 23,22,19,12-0
 *   R7    48 bits (cmd) (card interface condition reg)
 *           [45:40] cmd_idx [19:16] voltage (0x01: 2.7~3.6V) [15:8] check-echo [7:1] CRC
 *
 ****************************************************************************/

/* General Form 32-bit Response */
typedef struct _SD_R32 {
	/*
	 * Note: The bitfields definition was not applied due to that the
	 *       core architecture may be switched between big-endian
	 *       and little endian.  We don't want to define two structures
	 *       to switch between the two endain architectures.  Users
	 *       could use following macros to extract the target member.
	 */
	union {
		uint32_t r[1];
		uint8_t b[4];
	};
} SD_R32;

/* General Form 128-bit Response */
typedef struct _SD_R128 {
	/*
	 * Note: The bitfields definition was not applied due to that the
	 *       core architecture may be switched between big-endian
	 *       and little endian.  We don't want to define two structures
	 *       to switch between the two endain architectures.  Users
	 *       could use following macros to extract the target member.
	 */
	union {
		uint32_t r[4];
		uint8_t b[16];
	};
} SD_R128;

/* R6 Response Fields (Width: 32 bits) */
#define SD_R6_GET_RCA(r32)      ((uint32_t)((r32).r[0]) & 0xffff0000)
#define SD_R6_GET_CSR(r32)      ((uint32_t)((r32).r[0]) & 0x0000ffff)
#define SD_R6_GET_CSR_ERR(r32)  ((uint32_t)((r32).r[0]) & 0x0000e000)

/* R7 Response Fields (Width: 32 bits) */
#define SD_R7_GET_VHS(r32)      (((uint32_t)((r32).r[0]) >> 8) & 0x0f)
#define SD_R7_GET_PTN(r32)      ((uint32_t)((r32).r[0]) & 0xff)

/* OCR - Operation Condition Register (Width: 32 bits */
/* Readback: ACMD41_SD_SEND_OP_COND/R3 */
typedef SD_R32 SD_OCR;

#define SD_OCR_VDD_MASK                 0x00ffffff	/* VDD voltage window */
#define SD_OCR_VDD_SHIFT                0
#define SD_OCR_VDD_2_7                  0x00008000	/* VDD 2.7 ~ 2.8 */
#define SD_OCR_VDD_2_8                  0x00010000	/* VDD 2.8 ~ 2.9 */
#define SD_OCR_VDD_2_9                  0x00020000	/* VDD 2.9 ~ 3.0 */
#define SD_OCR_VDD_3_0                  0x00040000	/* VDD 3.0 ~ 3.1 */
#define SD_OCR_VDD_3_1                  0x00080000	/* VDD 3.1 ~ 3.2 */
#define SD_OCR_VDD_3_2                  0x00100000	/* VDD 3.2 ~ 3.3 */
#define SD_OCR_VDD_3_3                  0x00200000	/* VDD 3.3 ~ 3.4 */
#define SD_OCR_VDD_3_4                  0x00400000	/* VDD 3.4 ~ 3.5 */
#define SD_OCR_VDD_3_5                  0x00800000	/* VDD 3.5 ~ 3.6 */
#define SD_OCR_VDD_2_7V_3_6V            (SD_OCR_VDD_2_7 | SD_OCR_VDD_2_8 | SD_OCR_VDD_2_9 | SD_OCR_VDD_3_0 | \
                                         SD_OCR_VDD_3_1 | SD_OCR_VDD_3_2 | SD_OCR_VDD_3_3 | SD_OCR_VDD_3_4 | SD_OCR_VDD_3_5)

#define SD_OCR_CCS_MASK                 0x40000000	/* Card capacity status */
#define SD_OCR_CCS_SHIFT                30
#define SD_CCS_SD                            0
#define SD_CCS_SDHC                          1

#define SD_OCR_BUSY_MASK                0x80000000	/* Card power up status bit */
#define SD_OCR_BUSY_SHIFT               31
#define SD_BUSY                              0
#define SD_POWERUP                           1

#define SD_OCR_GET_VDD(ocr)             (((uint32_t)((ocr).r[0]) & SD_OCR_VDD_MASK) >> SD_OCR_VDD_SHIFT)
#define SD_OCR_GET_CCS(ocr)             (((uint32_t)((ocr).r[0]) & SD_OCR_CCS_MASK) >> SD_OCR_CCS_SHIFT)
#define SD_OCR_GET_BUSY(ocr)            (((uint32_t)((ocr).r[0]) & SD_OCR_BUSY_MASK) >> SD_OCR_BUSY_SHIFT)

/* CID - Card Identification Register (Width: 128 bits) */
/* Readback: CMD10_SEND_CID/R2 */
typedef SD_R128 SD_CID;

/* Manufacture ID */
#define SD_CID_GET_MID(cid)                 ((uint32_t)((cid).r[3]) >> 24)
#define SD_CID_GET_MID_FROM_R3(r)           ((uint32_t)(r) >> 24)

/* OEM/Application ID */
#define SD_CID_GET_OID_PTR(cid)             ((uint8_t*)&((cid).b[13]))

/* Product name */
#define SD_CID_GET_PNM_PTR(cid)             ((uint8_t*)&((cid).b[8]))

/* Product revision (BCD coding) */
#define SD_CID_GET_PRV(cid)                 ((uint32_t)((cid).r[1]) >> 24)
#define SD_CID_GET_PRV_FROM_R1(r)           ((uint32_t)(r) >> 24)

/* Product serial number */
#define SD_CID_GET_PSN(cid)                 (((uint32_t)((cid).r[1]) << 8) | ((uint32_t)((cid).r[0]) >> 24))
#define SD_CID_GET_PSN_FROM_R0R1(r0, r1)    (((uint32_t)(r1) << 8) | ((uint32_t)(r0) >> 24))

/* Manufacturing date (0x0yym, year = 2000 + yy, month = m) */
#define SD_CID_GET_MDT(cid)                 (((uint32_t)((cid).r[0]) >> 8) & 0x0fff)
#define SD_CID_GET_MDT_FROM_R0(r)           (((uint32_t)(r) >> 8) & 0x0fff)

/* CRC7 checksum */
#define SD_CID_GET_CRC(cid)                 (((uint32_t)((cid).r[0]) >> 1) & 0x007f)
#define SD_CID_GET_CRC_FROM_R0(r)           (((uint32_t)(r) >> 1) & 0x007f)

/*
 * CSD - Card-Specific Data Register (Width: 128 bits)
 * Readback: CMD9_SEND_CSD/R2
 * Program : CMD27_PROGRAM_CSD/R1
 */
typedef SD_R128 SD_CSD;

/* -------------------------- */
/* CSD v1.0 definitions */
/* CRC (R/W) */
#define SD_CSD_GET_CRC(csd)                     (((uint32_t)((csd).r[0]) >> 1) & 0x0000007f)
#define SD_CSD_GET_CRC_FROM_R0(r)               (((uint32_t)(r) >> 1) & 0x0000007f)
#define SD_CSD_SET_CRC(csd,v)                   ((uint32_t)((csd).r[0]) |= (((uint32_t)(v) & 0x7f) << 1))
#define SD_CSD_SET_CRC_TO_R0(r,v)               ((uint32_t)(r) |= (((uint32_t)(v) & 0x7f) << 1))

/* File format (R/W1, fixed to 0x00 in 2.0) */
#define SD_CSD_GET_FILE_FORMAT(csd)             (((uint32_t)((csd).r[0]) >> 10) & 0x00000003)
#define SD_CSD_GET_FILE_FORMAT_FROM_R0(r)       (((uint32_t)(r) >> 10) & 0x00000003)
#define SD_CSD_SET_FILE_FORMAT(csd,v)           ((uint32_t)((csd).r[0]) |= (((uint32_t)(v) & 0x03) << 10))
#define SD_CSD_SET_FILE_FORMAT_TO_R0(r,v)       ((uint32_t)(r) |= (((uint32_t)(v) & 0x03) << 10))

#define SD_FILE_FORMAT_HDD              0	/* Hard disk like file system with partition table */
#define SD_FILE_FORMAT_FLOPPY           1	/* DOS FAT (floppy like) with boot sector only (no partition table) */
#define SD_FILE_FORMAT_UNIVERSAL        2	/* Universal file format */
#define SD_FILE_FORMAT_OTHERS           3	/* Others/Unknown */

/* Temporary write protection (R/W) */
#define SD_CSD_GET_TMP_WRITE_PROTECT(csd)           (((uint32_t)((csd).r[0]) >> 12) & 0x00000001)
#define SD_CSD_GET_TMP_WRITE_PROTECT_FROM_R0(r)     (((uint32_t)(r) >> 12) & 0x00000001)
#define SD_CSD_SET_TMP_WRITE_PROTECT(csd,v)         ((uint32_t)((csd).r[0]) |= (((uint32_t)(v) & 0x01) << 12))
#define SD_CSD_SET_TMP_WRITE_PROTECT_TO_R0(r,v)     ((uint32_t)(r) |= (((uint32_t)(v) & 0x01) << 12))

/* Permanent write protection (R/W1) */
#define SD_CSD_GET_PERM_WRITE_PROTECT(csd)          (((uint32_t)((csd).r[0]) >> 13) & 0x00000001)
#define SD_CSD_GET_PERM_WRITE_PROTECT_FROM_R0(r)    (((uint32_t)(r) >> 13) & 0x00000001)
#define SD_CSD_SET_PERM_WRITE_PROTECT(csd,v)        ((uint32_t)((csd).r[0]) |= (((uint32_t)(v) & 0x01) << 13))
#define SD_CSD_SET_PERM_WRITE_PROTECT_TO_R0(r,v)    ((uint32_t)(r) |= (((uint32_t)(v) & 0x01) << 13))

/* Copy flag (R/W1) */
#define SD_CSD_GET_COPY(csd)                    (((uint32_t)((csd).r[0]) >> 14) & 0x00000001)
#define SD_CSD_GET_COPY_FROM_R0(r)              (((uint32_t)(r) >> 14) & 0x00000001)
#define SD_CSD_SET_COPY(csd,v)                  ((uint32_t)((csd).r[0]) |= (((uint32_t)(v) & 0x01) << 14))
#define SD_CSD_SET_COPY_TO_R0(r,v)              ((uint32_t)(r) |= (((uint32_t)(v) & 0x01) << 14))

/* File format group (R/W1, fixed to 0x00 in 2.0) */
#define SD_CSD_GET_FILE_FORMAT_GRP(csd)         (((uint32_t)((csd).r[0]) >> 15) & 0x00000001)
#define SD_CSD_GET_FILE_FORMAT_GRP_FROM_R0(r)   (((uint32_t)(r) >> 15) & 0x00000001)
#define SD_CSD_SET_FILE_FORMAT_GRP(csd,v)       ((uint32_t)((csd).r[0]) |= (((uint32_t)(v) & 0x01) << 15))
#define SD_CSD_SET_FILE_FORMAT_GRP_TO_R0(r,v)   ((uint32_t)(r) |= (((uint32_t)(v) & 0x01) << 15))

/* Partial blocks for write allowed (R, fixed to 0x00 in 2.0) */
#define SD_CSD_GET_WRITE_BL_PARTIAL(csd)        (((uint32_t)((csd).r[0]) >> 21) & 0x00000001)
#define SD_CSD_GET_WRITE_BL_PARTIAL_FROM_R0(r)  (((uint32_t)(r) >> 21) & 0x00000001)

/* Max write data block length (R, fixed to 9 in 2.0) */
#define SD_CSD_GET_WRITE_BL_LEN(csd)            (((uint32_t)((csd).r[0]) >> 22) & 0x0000000f)
#define SD_CSD_GET_WRITE_BL_LEN_FROM_R0(r)      (((uint32_t)(r) >> 22) & 0x0000000f)

/* Write speed factor (R, fixed to 0x02 in 2.0) */
#define SD_CSD_GET_R2W_FACTOR(csd)              (((uint32_t)((csd).r[0]) >> 26) & 0x00000007)
#define SD_CSD_GET_R2W_FACTOR_FROM_R0(r)        (((uint32_t)(r) >> 26) & 0x00000007)

/* Write protect group enable (R, fixed to 0x00 in 2.0) */
#define SD_CSD_GET_WP_GRP_ENABLE(csd)           ((uint32_t)((csd).r[0]) >> 31)
#define SD_CSD_GET_WP_GRP_ENABLE_FROM_R0(r)     ((uint32_t)(r) >> 31)

/* Write protect group size (R, fixed to 0x00 in 2.0) */
#define SD_CSD_GET_WP_GRP_SIZE(csd)             (((uint32_t)((csd).r[1]) >> 0) & 0x0000007f)
#define SD_CSD_GET_WP_GRP_SIZE_FROM_R1(r)       (((uint32_t)(r) >> 0) & 0x0000007f)

/* Erase sector size (R, fixed to 0x7f in 2.0) */
#define SD_CSD_GET_SECTOR_SIZE(csd)             (((uint32_t)((csd).r[1]) >> 7) & 0x0000007f)
#define SD_CSD_GET_SECTOR_SIZE_FROM_R1(r)       (((uint32_t)(r) >> 7) & 0x0000007f)

/* Erase single block enable (R, fixed to 0x01 in 2.0) */
#define SD_CSD_GET_ERASE_BLK_EN(csd)            (((uint32_t)((csd).r[1]) >> 14) & 0x00000001)
#define SD_CSD_GET_ERASE_BLK_EN_FROM_R1(r)      (((uint32_t)(r) >> 14) & 0x00000001)

/* Device size multiplier (R, obsolete in 2.0) */
#define SD_CSD1_GET_C_SIZE_MULT(csd)            (((uint32_t)((csd).r[1]) >> 15) & 0x00000007)
#define SD_CSD1_GET_C_SIZE_MULT_FROM_R1(r)      (((uint32_t)(r) >> 15) & 0x00000007)

/* Max write current at VDD max (R, obsolete in 2.0) */
#define SD_CSD1_GET_VDD_W_CURR_MAX(csd)         (((uint32_t)((csd).r[1]) >> 18) & 0x00000007)
#define SD_CSD1_GET_VDD_W_CURR_MAX_FROM_R1(r)   (((uint32_t)(r) >> 18) & 0x00000007)

/* Max write current at VDD min (R, obsolete in 2.0) */
#define SD_CSD1_GET_VDD_W_CURR_MIN(csd)         (((uint32_t)((csd).r[1]) >> 21) & 0x00000007)
#define SD_CSD1_GET_VDD_W_CURR_MIN_FROM_R1(r)   (((uint32_t)(r) >> 21) & 0x00000007)

/* Max read current at VDD max (R, obsolete in 2.0) */
#define SD_CSD1_GET_VDD_R_CURR_MAX(csd)         (((uint32_t)((csd).r[1]) >> 24) & 0x00000007)
#define SD_CSD1_GET_VDD_R_CURR_MAX_FROM_R1(r)   (((uint32_t)(r) >> 24) & 0x00000007)

/* Max read current at VDD min (R, obsolete in 2.0) */
#define SD_CSD1_GET_VDD_R_CURR_MIN(csd)         (((uint32_t)((csd).r[1]) >> 27) & 0x00000007)
#define SD_CSD1_GET_VDD_R_CURR_MIN_FROM_R1(r)   (((uint32_t)(r) >> 27) & 0x00000007)

#define SD_VDD_CURR_MIN_0P5MA           0
#define SD_VDD_CURR_MIN_1MA             1
#define SD_VDD_CURR_MIN_5MA             2
#define SD_VDD_CURR_MIN_10MA            3
#define SD_VDD_CURR_MIN_25MA            4
#define SD_VDD_CURR_MIN_35MA            5
#define SD_VDD_CURR_MIN_60MA            6
#define SD_VDD_CURR_MIN_100MA           7

#define SD_VDD_CURR_MAX_1MA             0
#define SD_VDD_CURR_MAX_5MA             1
#define SD_VDD_CURR_MAX_10MA            2
#define SD_VDD_CURR_MAX_25MA            3
#define SD_VDD_CURR_MAX_35MA            4
#define SD_VDD_CURR_MAX_45MA            5
#define SD_VDD_CURR_MAX_80MA            6
#define SD_VDD_CURR_MAX_200MA           7

/* Device size (R) */
#define SD_CSD1_GET_C_SIZE(csd)                 ((((uint32_t)((csd).r[2]) << 2) & 0x00000fff) | (((uint32_t)((csd).r[1]) >> 30) & 0x00000003))
#define SD_CSD1_GET_C_SIZE_FROM_R1R2(r1, r2)    ((((uint32_t)(r2) << 2) & 0x00000fff) | (((uint32_t)(r1) >> 30) & 0x00000003))

/* DSR implemented (R) */
#define SD_CSD_GET_DSR_IMP(csd)                 (((uint32_t)((csd).r[2]) >> 12) & 0x00000001)
#define SD_CSD_GET_DSR_IMP_FROM_R2(r)           (((uint32_t)(r) >> 12) & 0x00000001)

/* Read block misaligned (R, fixed to 0x00 in 2.0) */
#define SD_CSD_GET_READ_BLK_MISALIGN(csd)           (((uint32_t)((csd).r[2]) >> 13) & 0x00000001)
#define SD_CSD_GET_READ_BLK_MISALIGN_FROM_R2(r)     (((uint32_t)(r) >> 13) & 0x00000001)

/* Write block misaligned (R, fixed to 0x00 in 2.0) */
#define SD_CSD_GET_WRITE_BLK_MISALIGN(csd)          (((uint32_t)((csd).r[2]) >> 14) & 0x00000001)
#define SD_CSD_GET_WRITE_BLK_MISALIGN_FROM_R2(r)    (((uint32_t)(r) >> 14) & 0x00000001)

/* Partial blocks for read allowed (R, fixed to 0x00 in 2.0) */
#define SD_CSD_GET_READ_BL_PARTIAL(csd)         (((uint32_t)((csd).r[2]) >> 15) & 0x00000001)
#define SD_CSD_GET_READ_BL_PARTIAL_FROM_R2(r)   (((uint32_t)(r) >> 15) & 0x00000001)

/* Max read data block length (R, fixed to 9 in 2.0) */
#define SD_CSD_GET_READ_BL_LEN(csd)         (((uint32_t)((csd).r[2]) >> 16) & 0x0000000f)
#define SD_CSD_GET_READ_BL_LEN_FROM_R2(r)   (((uint32_t)(r) >> 16) & 0x0000000f)

#define SD_BL_LEN_512               9	/* 2^9 */
#define SD_BL_LEN_1024              10	/* 2^10 */
#define SD_BL_LEN_2048              11	/* 2^11 */

/* Card command classes (R) */
#define SD_CSD_GET_CCC(csd)                 (((uint32_t)((csd).r[2]) >> 20) & 0x00000fff)
#define SD_CSD_GET_CCC_FROM_R2(r)           (((uint32_t)(r) >> 20) & 0x00000fff)

#define SD_CCC_CLASS0               0
#define SD_CCC_CLASS1               1
#define SD_CCC_CLASS2               2
#define SD_CCC_CLASS3               3
#define SD_CCC_CLASS4               4
#define SD_CCC_CLASS5               5
#define SD_CCC_CLASS6               6
#define SD_CCC_CLASS7               7
#define SD_CCC_CLASS8               8
#define SD_CCC_CLASS9               9
#define SD_CCC_CLASS10              10
#define SD_CCC_CLASS11              11

/* Max data transfer rate (R, fixed to 0x32 or 0x5a in 2.0) */
#define SD_CSD_GET_TRAN_SPEED(csd)          ((uint32_t)((csd).r[3]) & 0x000000ff)
#define SD_CSD_GET_TRAN_SPEED_FROM_R3(r)    ((uint32_t)(r) & 0x000000ff)

#define SD_TRAN_SPEED_TU(ts)        ((uint32_t)(ts) & 0x07)
#define SD_TRAN_SPEED_TV(ts)        (((uint32_t)(ts) >> 3) & 0x0f)

#define SD_TS_TU_100KBPS            0
#define SD_TS_TU_1MBPS              1
#define SD_TS_TU_10MBPS             2
#define SD_TS_TU_100MBPS            3

#define SD_TS_TV_1P0                1
#define SD_TS_TV_1P2                2
#define SD_TS_TV_1P3                3
#define SD_TS_TV_1P5                4
#define SD_TS_TV_2P0                5
#define SD_TS_TV_2P5                6
#define SD_TS_TV_3P0                7
#define SD_TS_TV_3P5                8
#define SD_TS_TV_4P0                9
#define SD_TS_TV_4P5                10
#define SD_TS_TV_5P0                11
#define SD_TS_TV_5P5                12
#define SD_TS_TV_6P0                13
#define SD_TS_TV_7P0                14
#define SD_TS_TV_8P0                15

/* Data read access-time-2 in CLK cycles (NSAC * 100) (R, fixed to 0x00 in 2.0) */
#define SD_CSD_GET_NSAC(csd)            (((uint32_t)((csd).r[3]) >> 8) & 0x000000ff)
#define SD_CSD_GET_NSAC_FROM_R3(r)      (((uint32_t)(r) >> 8) & 0x000000ff)

/* Data read access-time-1 (R, fixed to 0x0e in 2.0) */
#define SD_CSD_GET_TAAC(csd)            (((uint32_t)((csd).r[3]) >> 16) & 0x0000ffff)
#define SD_CSD_GET_TAAC_FROM_R3(r)      (((uint32_t)(r) >> 16) & 0x0000ffff)

#define SD_TAAC_TU(ac)              ((uint32_t)(ac) & 0x07)
#define SD_TAAC_TV(ac)              (((uint32_t)(ac) >> 3) & 0x0f)

#define SD_TAAC_TU_1NS              0
#define SD_TAAC_TU_10NS             1
#define SD_TAAC_TU_100NS            2
#define SD_TAAC_TU_1US              3
#define SD_TAAC_TU_10US             4
#define SD_TAAC_TU_100US            5
#define SD_TAAC_TU_1MS              6
#define SD_TAAC_TU_10MS             7

#define SD_TAAC_TV_1P0              1
#define SD_TAAC_TV_1P2              2
#define SD_TAAC_TV_1P3              3
#define SD_TAAC_TV_1P5              4
#define SD_TAAC_TV_2P0              5
#define SD_TAAC_TV_2P5              6
#define SD_TAAC_TV_3P0              7
#define SD_TAAC_TV_3P5              8
#define SD_TAAC_TV_4P0              9
#define SD_TAAC_TV_4P5              10
#define SD_TAAC_TV_5P0              11
#define SD_TAAC_TV_5P5              12
#define SD_TAAC_TV_6P0              13
#define SD_TAAC_TV_7P0              14
#define SD_TAAC_TV_8P0              15

/* CSD structure (R) */
#define SD_CSD_GET_CSD_STRUCTURE(csd)       ((uint32_t)((csd).r[3]) >> 30)
#define SD_CSD_GET_CSD_STRUCTURE_FROM_R3(r) ((uint32_t)(r) >> 30)

/* Get user data size (card memory capacity, not include security protected area) */
#if 0
#define SD_CSD1_GET_CAPACITY(csd)           (SD_CSD1_GET_C_SIZE(csd) + 1) *             \
                                            (1 << (SD_CSD1_GET_C_SIZE_MULT(csd) + 2)) * \
                                            (1 << SD_CSD_GET_READ_BL_LEN(csd))

#define SD_CSD1_GET_CAPACITY_R1R2(r1,r2)    (SD_CSD1_GET_C_SIZE_FROM_R1R2(r1,r2) + 1) *             \
                                            (1 << (SD_CSD1_GET_C_SIZE_MULT_FROM_R1(r1) + 2)) * \
                                            (1 << SD_CSD_GET_READ_BL_LEN_FROM_R2(r2))
#endif

/* -------------------------- */
/* CSD v2.0 definitions */
/* */
/* Device size (R) */
#define SD_CSD2_GET_C_SIZE(csd)                 ((((uint32_t)((csd).r[2]) << 16) & 0x003f0000) | ((uint32_t)((csd).r[1]) >> 16))
#define SD_CSD2_GET_C_SIZE_FROM_R1R2(r1,r2)     ((((uint32_t)(r2) << 16) & 0x003f0000) | ((uint32_t)(r1) >> 16))

/* Get user data size (card memory capacity, not include security protected area) */
// #define SD_CSD2_GET_CAPACITY_KB(csd)        ((SD_CSD2_GET_C_SIZE(csd) + 1) * 512)
// #define SD_CSD2_GET_CAPACITY_KB_R1R2(r1,r2) ((SD_CSD2_GET_C_SIZE_FROM_R1R2(csd) + 1) * 512)

/*
 * SCR - SD Card Configuration Register
 * Width: 64 bits
 * Readback: ACMD51_SEND_SCR/R1
 */
typedef struct _SD_SCR {
	/* Note: The bitfields definition was not applied due to that the */
	/*       core architecture may be switched between big-endian */
	/*       and little endian.  We don't want to define two structures */
	/*       to switch between the two endain architectures.  Users */
	/*       could use following macros to extract the target member. */
	union {
		uint32_t r[2];
		uint8_t b[8];
	};
} SD_SCR;

/* DAT bus widths supported */
#define SD_SCR_GET_SD_BUS_WIDTHS(scr)           (((uint32_t)((scr).r[1]) >> 16) & 0x0000000f)
#define SD_SCR_GET_SD_BUS_WIDTHS_FROM_R1(r)     (((uint32_t)(r) >> 16) & 0x0000000f)

#define SD_BUS_WIDTH_1BIT           1	/* DAT0 */
#define SD_BUS_WIDTH_4BIT           4	/* DAT0 ~ DAT3 */

/* SD security support */
#define SD_SCR_GET_SD_SECURITY(scr)             (((uint32_t)((scr).r[1]) >> 20) & 0x00000007)
#define SD_SCR_GET_SD_SECURITY_FROM_R1(r)       (((uint32_t)(r) >> 20) & 0x00000007)

#define SD_SECURITY_NONE            0	/* no security */
#define SD_SECURITY_1_01            2	/* version 1.01 */
#define SD_SECURITY_2_0             3	/* version 2.00 */

/* Data status after erases */
#define SD_SCR_GET_DATA_STAT_AFTER_ERASE(scr)       (((uint32_t)((scr).r[1]) >> 23) & 0x00000001)
#define SD_SCR_GET_DATA_STAT_AFTER_ERASE_FROM_R1(r) (((uint32_t)(r) >> 23) & 0x00000001)

/* SD memory card spec version */
#define SD_SCR_GET_SD_SPEC(scr)                 (((uint32_t)((scr).r[1]) >> 24) & 0x0000000f)
#define SD_SCR_GET_SD_SPEC_FROM_R1(r)           (((uint32_t)(r) >> 24) & 0x0000000f)

#define SD_SPEC_1_0                 0	/* version 1.0 ~ 1.01 */
#define SD_SPEC_1_1                 1	/* version 1.10 */
#define SD_SPEC_2_0                 2	/* version 2.00 */

/* SCR structure */
#define SD_SCR_GET_SCR_STRUCTURE(scr)           (((uint32_t)((scr).r[1]) >> 28) & 0x0000000f)
#define SD_SCR_GET_SCR_STRUCTURE_FROM_R1(r)     (((uint32_t)(r) >> 28) & 0x0000000f)

#define SD_SCR_VERSION_1_0          0

/*
 * CSR - Card Status Register
 * Width: 32 bits
 * Readback: CMD13_SEND_STATUS/R1
 */
typedef SD_R32 SD_CSR;

/* Bit field defines of CSR */
#define SD_CSR_AKE_SEQ_ERROR            0x00000008	/* error in the sequence of authentication */
#define SD_CSR_APP_CMD                  0x00000020	/* card expects ACMD or the command has been interpreted as ACMD */
#define SD_CSR_READY_FOR_DATA           0x00000100	/* buffer empty signaling on the bus */
#define SD_CSR_CURRENT_STATE_MASK       0x00001e00	/* the state of the card when receiving the command */
#define SD_CSR_CURRENT_STATE_SHIFT      9
#define SD_CSR_ERASE_RESET              0x00002000	/* a erase sequence was cleared before execution due to out of erase sequence commands */
#define SD_CSR_CARD_ECC_DISABLE         0x00004000	/* command was executed without using internal ECC */
#define SD_CSR_WP_ERASE_SKIP            0x00008000	/* attempt to partial erase of write protected blocks */
#define SD_CSR_CSD_OVERWRITE            0x00010000	/* attempt to 1) CSD ro fields mismatch, 2) reverse copy or perm wp bits */
#define SD_CSR_ERROR                    0x00080000	/* general error */
#define SD_CSR_CC_ERROR                 0x00100000	/* internal card controller error */
#define SD_CSR_CARD_ECC_FAILED          0x00200000	/* card internal ECC was applied but failed to correct the data */
#define SD_CSR_ILLEGAL_COMMAND          0x00400000	/* command illegal for the card state */
#define SD_CSR_COM_CRC_ERROR            0x00800000	/* command crc check failed */
#define SD_CSR_LOCK_UNLOCK_FAILED       0x01000000	/* password error in lock/unlock command */
#define SD_CSR_CARD_IS_LOCKED           0x02000000	/* card is locked by the host */
#define SD_CSR_WP_VIOLATION             0x04000000	/* attempts to write a protected block */
#define SD_CSR_ERASE_PARAM              0x08000000	/* invlaid selection of write blocks for erase */
#define SD_CSR_ERASE_SEQ_ERROR          0x10000000	/* error in erase command sequence */
#define SD_CSR_BLOCK_LEN_ERROR          0x20000000	/* transferred block length is not allowed or transferred bytes mismatch the block length */
#define SD_CSR_ADDRESS_ERROR            0x40000000	/* misaligned address which did not match the block length */
#define SD_CSR_OUT_OF_RANGE             0x80000000	/* command argument was out of allowed range */

/* Error in the sequence of the authentication process */
#define SD_CSR_GET_AKE_SEQ_ERROR(csr)           (((uint32_t)((csr).r[0]) >> 3) & 0x00000001)
#define SD_CSR_GET_AKE_SEQ_ERROR_FROM_R(r)      (((uint32_t)(r) >> 3) & 0x00000001)

/* Card is now expect ACMD, or the command has been interpreted as ACMD */
#define SD_CSR_GET_APP_CMD(csr)                 (((uint32_t)((csr).r[0]) >> 5) & 0x00000001)
#define SD_CSR_GET_APP_CMD_FROM_R(r)            (((uint32_t)(r) >> 5) & 0x00000001)

/* Corresponds to buffer empty signaling on the bus */
#define SD_CSR_GET_READY_FOR_DATA(csr)          (((uint32_t)((csr).r[0]) >> 8) & 0x00000001)
#define SD_CSR_GET_READY_FOR_DATA_FROM_R(r)     (((uint32_t)(r) >> 8) & 0x00000001)

/*
 * The state of the card when receiving the the command
 * (visible in the response of the next command)
 */
#define SD_CSR_GET_CURRENT_STATE(csr)           (((uint32_t)((csr).r[0]) >> 9) & 0x0000000f)
#define SD_CSR_GET_CURRENT_STATE_FROM_R(r)      (((uint32_t)(r) >> 9) & 0x0000000f)

#define SD_STATE_IDLE               0
#define SD_STATE_READY              1
#define SD_STATE_IDENT              2
#define SD_STATE_STBY               3
#define SD_STATE_TRAN               4
#define SD_STATE_DATA               5
#define SD_STATE_RCV                6
#define SD_STATE_PRG                7
#define SD_STATE_DIS                8

/* An erase sequence was cleared due to out of erase sequence command */
#define SD_CSR_GET_ERASE_RESET(csr)             (((uint32_t)((csr).r[0]) >> 13) & 0x00000001)
#define SD_CSR_GET_ERASE_RESET_FROM_R(r)        (((uint32_t)(r) >> 13) & 0x00000001)

/* The command has been executed without using internal ECC */
#define SD_CSR_GET_CARD_ECC_DISABLED(csr)       (((uint32_t)((csr).r[0]) >> 14) & 0x00000001)
#define SD_CSR_GET_CARD_ECC_DISABLED_FROM_R(r)  (((uint32_t)(r) >> 14) & 0x00000001)

/* Set only when partial address erase was erased due to write protected (tmp/perm) blocks */
#define SD_CSR_GET_WP_ERASE_SKIP(csr)           (((uint32_t)((csr).r[0]) >> 15) & 0x00000001)
#define SD_CSR_GET_WP_ERASE_SKIP_FROM_R(r)      (((uint32_t)(r) >> 15) & 0x00000001)

/* Set when 1) read-only section of the CSD mismatch, 2) attempt to reverse copy or permanent WP bits */
#define SD_CSR_GET_CSD_OVERWRITE(csr)           (((uint32_t)((csr).r[0]) >> 16) & 0x00000001)
#define SD_CSR_GET_CSD_OVERWRITE_FROM_R(r)      (((uint32_t)(r) >> 16) & 0x00000001)

/* General error or unknown error */
#define SD_CSR_GET_ERROR(csr)                   (((uint32_t)((csr).r[0]) >> 19) & 0x00000001)
#define SD_CSR_GET_ERROR_FROM_R(r)              (((uint32_t)(r) >> 19) & 0x00000001)

/* Internal card controller error */
#define SD_CSR_GET_CC_ERROR(csr)                (((uint32_t)((csr).r[0]) >> 20) & 0x00000001)
#define SD_CSR_GET_CC_ERROR_FROM_R(r)           (((uint32_t)(r) >> 20) & 0x00000001)

/* Card internal ECC was applied but failed to correct the data */
#define SD_CSR_GET_CARD_ECC_FAILED(csr)         (((uint32_t)((csr).r[0]) >> 21) & 0x00000001)
#define SD_CSR_GET_CARD_ECC_FAILED_FROM_R(r)    (((uint32_t)(r) >> 21) & 0x00000001)

/* Command not legalfor the card state */
#define SD_CSR_GET_ILLEGAL_COMMAND(csr)         (((uint32_t)((csr).r[0]) >> 22) & 0x00000001)
#define SD_CSR_GET_ILLEGAL_COMMAND_FROM_R(r)    (((uint32_t)(r) >> 22) & 0x00000001)

/* The CRC check of previous command failed */
#define SD_CSR_GET_COM_CRC_ERROR(csr)           (((uint32_t)((csr).r[0]) >> 23) & 0x00000001)
#define SD_CSR_GET_COM_CRC_ERROR_FROM_R(r)      (((uint32_t)(r) >> 23) & 0x00000001)

/* Set when a sequece or password error has been detected in lock/unlock card command */
#define SD_CSR_GET_LOCK_UNLOCK_FAILED(csr)      (((uint32_t)((csr).r[0]) >> 24) & 0x00000001)
#define SD_CSR_GET_LOCK_UNLOCK_FAILED_FROM_R(r) (((uint32_t)(r) >> 24) & 0x00000001)

/* Signals that the card is locked by the host */
#define SD_CSR_GET_CARD_IS_LOCKED(csr)          (((uint32_t)((csr).r[0]) >> 25) & 0x00000001)
#define SD_CSR_GET_CARD_IS_LOCKED_FROM_R(r)     (((uint32_t)(r) >> 25) & 0x00000001)

/* Set when the host attempts to write protected block or tmp/perm protected card */
#define SD_CSR_GET_WP_VIOLATION(csr)            (((uint32_t)((csr).r[0]) >> 26) & 0x00000001)
#define SD_CSR_GET_WP_VIOLATION_FROM_R(r)       (((uint32_t)(r) >> 26) & 0x00000001)

/* An invalid selection of write-blocks for erase occured */
#define SD_CSR_GET_ERASE_PARAM(csr)             (((uint32_t)((csr).r[0]) >> 27) & 0x00000001)
#define SD_CSR_GET_ERASE_PARAM_FROM_R(r)        (((uint32_t)(r) >> 27) & 0x00000001)

/* An error in the sequence of erase commands occured */
#define SD_CSR_GET_ERASE_SEQ_ERROR(csr)         (((uint32_t)((csr).r[0]) >> 28) & 0x00000001)
#define SD_CSR_GET_ERASE_SEQ_ERROR_FROM_R(r)    (((uint32_t)(r) >> 28) & 0x00000001)

/* Transferred block length is not allowed or transferred length does not match block length */
#define SD_CSR_GET_BLOCK_LEN_ERROR(csr)         (((uint32_t)((csr).r[0]) >> 29) & 0x00000001)
#define SD_CSR_GET_BLOCK_LEN_ERROR_FROM_R(r)    (((uint32_t)(r) >> 29) & 0x00000001)

/* Misaligned address which did not match the block length was used in the command */
#define SD_CSR_GET_ADDRESS_ERROR(csr)           (((uint32_t)((csr).r[0]) >> 30) & 0x00000001)
#define SD_CSR_GET_ADDRESS_ERROR_FROM_R(r)      (((uint32_t)(r) >> 30) & 0x00000001)

/* Command argument out of range or this card */
#define SD_CSR_GET_OUT_OF_RANGE(csr)            (((uint32_t)((csr).r[0]) >> 31) & 0x00000001)
#define SD_CSR_GET_OUT_OF_RANGE_FROM_R(r)       (((uint32_t)(r) >> 31) & 0x00000001)

/* Check all data error bits at once */
#define SD_CSR_CHECK_ERROR_BITS(csr)            ((uint32_t)((csr).r[0]) & (SD_CSR_AKE_SEQ_ERROR | SD_CSR_ERASE_RESET | \
                                                SD_CSR_WP_ERASE_SKIP | SD_CSR_CSD_OVERWRITE | \
                                                SD_CSR_ERROR | SD_CSR_CC_ERROR | SD_CSR_CARD_ECC_FAILED | \
                                                /*SD_CSR_ILLEGAL_COMMAND |*/ SD_CSR_COM_CRC_ERROR | SD_CSR_LOCK_UNLOCK_FAILED | \
                                                SD_CSR_CARD_IS_LOCKED | SD_CSR_WP_VIOLATION | SD_CSR_ERASE_PARAM | \
                                                SD_CSR_ERASE_SEQ_ERROR | SD_CSR_BLOCK_LEN_ERROR | SD_CSR_ADDRESS_ERROR | \
                                                SD_CSR_OUT_OF_RANGE))
/*
 * SSR - SD Status Register
 * Width: 512 bits
 * Readback: ACMD13_SD_STATUS/DAT0
 */
#if 0
typedef struct _SD_SSR {
	/*
	 * Note: The bitfields definition was not applied due to that the
	 *       core architecture may be switched between big-endian
	 *       and little endian.  We don't want to define two structures
	 *       to switch between the two endain architectures.  Users
	 *       could use following macros to extract the target member.
	 */
	union {
		uint32_t r[16];
		uint8_t b[64];
	};
} SD_SSR;
#endif

/* Fixed offset value added to erase time */
#define SD_SSR_GET_ERASE_OFFSET(ssr)        (((uint32_t)((csr).b[50]) >> 0) & 0x00000003)

/* Timeout value for erasing areas specified by UINT_OF_ERASE_AU */
#define SD_SSR_GET_ERASE_TIMEOUT(ssr)       (((uint32_t)((csr).b[50]) >> 2) & 0x0000003f)

/* Number of AUs to be erased at a time */
#define SD_SSR_GET_ERASE_SIZE(ssr)          (((uint32_t)((csr).b[52]) << 8) | (uint32_t)((csr).b[51]))

/* Size of AU */
#define SD_SSR_GET_AU_SIZE(ssr)             ((uint32_t)((csr).b[53]) >> 4)

#define SD_AU_SIZE_NONE             0x00
#define SD_AU_SIZE_16KB             0x01
#define SD_AU_SIZE_32KB             0x02
#define SD_AU_SIZE_64KB             0x03
#define SD_AU_SIZE_128KB            0x04
#define SD_AU_SIZE_256KB            0x05
#define SD_AU_SIZE_512KB            0x06
#define SD_AU_SIZE_1MB              0x07
#define SD_AU_SIZE_2MB              0x08
#define SD_AU_SIZE_4MB              0x09

/* Performance of move indicated by 1 MB/s step */
#define SD_SSR_GET_PERFORMANCE_MOVE(ssr)    ((uint32_t)((csr).b[54]))

/* Speed class of the card */
#define SD_SSR_GET_SPEED_CLASS(ssr)         ((uint32_t)((csr).b[55]))

#define SD_SPEED_CLASS_0            0x00
#define SD_SPEED_CLASS_2            0x01
#define SD_SPEED_CLASS_4            0x02
#define SD_SPEED_CLASS_6            0x03

/* Size of protected area */
#define SD_SSR_GET_SIZE_OF_PROTECTED_AREA(ssr)  ((uint32_t)((csr).r[14]))

/* SD memory card type */
#define SD_SSR_GET_SD_CARD_TYPE(ssr)        (((uint32_t)((csr).r[15]) >> 0) & 0x0000ffff)

#define SD_CARD_TYPE_REGULAR        0x0000
#define SD_CARD_TYPE_ROM            0x0001

/* Card in secured mode operation */
#define SD_SSR_GET_SECURED_MODE(ssr)        (((uint32_t)((csr).b[63]) >> 5) & 0x00000001)

/* Shows the current defined data bus width defined by ACMD6_SET_BUS_WIDTH */
#define SD_SSR_GET_DAT_BUS_WIDTH(ssr)       (((uint32_t)((csr).b[63]) >> 6) & 0x00000003)

/*****************************************************************************
 * Secure Digital Memory Card Command Definitions
 *
 ****************************************************************************/

/*
 * Class 0 - Basic Commands
 * Responses:
 *   R1-R3, R6
 * Registers:
 *   CID, CSD, DSR
 */
#define SD_CMD0_GO_IDLE_STATE           0	/* Resets all cards to idle state */
#define SD_CMD2_ALL_SEND_CID            2	/* Ask any card to send the CID numbers */
#define SD_CMD3_SEND_RELATIVE_ADDR      3	/* Ask the card to publish a new relative address */
#define SD_CMD4_SET_DSR                 4	/* Programs the DSR of of all cards */
#define SD_CMD7_SELECT_DESELECT_CARD    7	/* Selected (its own relative address), deselected (other address) */

#define SD_CMD8_SEND_IF_COND            8	/* Sends SD Memory Card interface condition */
#define SD_CMD8_MAKE_ARG(vhs, ptn)      ((((uint32_t)(vhs) & 0x0f) << 8) | ((uint32_t)(ptn) & 0xff))
#define SD_VHS_2_7V_3_6V            0x01
#define SD_VHS_LOW_VOLTAGE          0x02
#define SD_CMD8_DEFAULT_PTN         0xaa	/* spec 20 suggested test pattern */

#define SD_CMD9_SEND_CSD                9	/* Addressed card sends its card-specific data (CSD) on the cmd line */
#define SD_CMD10_SEND_CID               10	/* Addressed card send its card-identification (CID) on the cmd line */
#define SD_CMD12_STOP_TRANSMISSION      12	/* Forces the card to stop transmission */
#define SD_CMD13_SEND_STATUS            13	/* Addressed card sends its status register */
#define SD_CMD15_GO_INACTIVE_STATE      15	/* Sends an addressed card into the inactive state */

/*
 * Class 2 - Block-Oriented Read Commands
 * Responses:
 *   R1
 */
#define SD_CMD16_SET_BLOCKLEN           16	/* Sets the block length for all following block commands (std cap.: read/write/lock, high cap.: lock) */
#define SD_CMD17_READ_SINGLE_BLOCK      17	/* Reads a block of size (std: SET_BLOCKLEN, high: 512) */
#define SD_CMD18_READ_MULTIPLE_BLOCK    18	/* Continuously transfers data from card to host until interrupted by a STOP_TRANSMISSION command */

/*
 * Class 4 - Block-Oriented Write Commands
 * Responses:
 *   R1
 * Registers:
 *   CSD
 */
#define SD_CMD24_WRITE_BLOCK            24	/* Writes a block of the size (srd: SET_BLOCKLEN, high: 512) */
#define SD_CMD25_WRITE_MULTIPLE_BLOCK   25	/* Continuously writes block of data until interrupted by a STOP_TRANSMISSION command */
#define SD_CMD27_PROGRAM_CSD            27	/* Programming of the programmable bits of the CSD */

/*
 * Class 6 - Block-Oriented Write Protection Commands
 * Responses:
 *   R1
 */
#define SD_CMD28_SET_WRITE_PROT         28	/* Std: Sets the write protection bit of the addressed group, high: not supported */
#define SD_CMD29_CLR_WRITE_PROT         29	/* Std: clears the write protection bit of the addressed group, high: not supported */
#define SD_CMD30_SEND_WRITE_PROT        30	/* Std: ask the card to send the status of the write protection bits, high: not supported */

/*
 * Class 5 - Erase Commands
 * Responses:
 *   R1
 */
#define SD_CMD32_ERASE_WR_BLK_START     32	/* Sets the address of the first write block to be erased */
#define SD_CMD33_ERASE_WR_BLK_END       33	/* Sets the address of the last write block of the continuous range to be erased */
#define SD_CMD38_ERASE                  38	/* Erase all previously selected write blocks */

/*
 * Class 7 - Lock Card Commands
 * Responses:
 *   R1
 */
#define SD_CMD42_LOCK_UNLOCK            42	/* To set/reset the password or lock/unlock the card (SET_BLOCKLEN) */

/*
 * Class 8 - Application Specific Commands
 * Responses:
 *   R1
 * Registers:
 *   SCR
 */
#define SD_CMD55_APP_CMD                55	/* Indicates to the card that the next command is an application specific command */
#define SD_CMD56_GEN_CMD                56	/* Used to transfer/get a data block to/from the card for general purpose/application specific commands (SET_BLOCKLEN) */

#define SD_ACMD6_SET_BUS_WIDTH              6	/* Defines the data bus width to be used for data thransfer (allowed: SCR) */
#define SD_BUS_WIDTH_ARG_1BIT           0
#define SD_BUS_WIDTH_ARG_4BIT           2
#define SD_ACMD6_MAKE_ARG(bw)           ((uint32_t)(bw) & 0x00000003)

#define SD_ACMD13_SD_STATUS                 13	/* Send the SD status (table 4-37) */
#define SD_ACMD22_SEND_NUM_WR_BLOCKS        22	/* Send the number of the written write blocks */
#define SD_ACMD23_SET_WR_BLK_ERASE_COUNT    23	/* Set the number of write blocks to be preerased before writing */

#define SD_ACMD41_SD_SEND_OP_COND           41	/* Sends host capacity support information (HCS) and asks operating condition register (OCR) */
#define SD_ACMD41_MAKE_ARG(hcs)         ((((uint32_t)(hcs) << SD_OCR_CCS_SHIFT) & SD_OCR_CCS_MASK) | SD_OCR_VDD_2_7V_3_6V)
#define SD_HCS_SD                       0	/* (Host Capacity Support) Denotes not supporting SDHC */
#define SD_HCS_SDHC                     1	/* (Host Capacity Support) Denotes SDHC support */

#define SD_ACMD42_SET_CLR_CARD_DETECT       42	/* Connect/Disconnect the 50KOhm pull-up resister on CD/DAT3 of the card */
#define SD_ACMD51_SEND_SCR                  51	/* Reads the SD configuration register (SCR) */

/*
 * Class 10 - Application Specific Commands
 * Responses:
 *   R1
 */
#define SD_CMD6_SWITCH_FUNC             6	/* Checks switchable function (mode 0) and switch card function (mode 1) */

/*****************************************************************************
 * SD Internal Programming Interfaces
 *
 ****************************************************************************/

/* PIO SD command retry counts */
#define SD_CMD_MAX_RETRY_COUNT          0x10000
#define SD_ACMD41_MAX_RETRY_COUNT       0x100
#define SD_READ_MAX_RETRY_COUNT         0x1000
#define SD_WRITE_MAX_RETRY_COUNT        0x2000
#define SD_STATE_MAX_RETRY_COUNT        0x1000
#define SD_TRANSFER_MAX_RETRY_COUNT     0x1000

/* SD command predefined to be sent to the SDC */
/* Class 0 - Basic Commands */
#define SDC_CMD0_GO_IDLE_STATE              \
    ((SD_CMD0_GO_IDLE_STATE & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK)
#define SDC_CMD2_ALL_SEND_CID               \
    ((SD_CMD2_ALL_SEND_CID & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK | SDC_LONG_RSP_MASK)
#define SDC_CMD3_SEND_RELATIVE_ADDR         \
    ((SD_CMD3_SEND_RELATIVE_ADDR & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD4_SET_DSR                    \
    ((SD_CMD4_SET_DSR & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK)
#define SDC_CMD7_SELECT_DESELECT_CARD       \
    ((SD_CMD7_SELECT_DESELECT_CARD & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD8_SEND_IF_COND               \
    ((SD_CMD8_SEND_IF_COND & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD9_SEND_CSD                   \
    ((SD_CMD9_SEND_CSD & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK | SDC_LONG_RSP_MASK)
#define SDC_CMD10_SEND_CID                  \
    ((SD_CMD10_SEND_CID & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK | SDC_LONG_RSP_MASK)
#define SDC_CMD12_STOP_TRANSMISSION         \
    ((SD_CMD12_STOP_TRANSMISSION & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD13_SEND_STATUS               \
    ((SD_CMD13_SEND_STATUS & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD15_GO_INACTIVE_STATE         \
    ((SD_CMD15_GO_INACTIVE_STATE & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK)
/* Class 2 - Block-Oriented Read Commands */
#define SDC_CMD16_SET_BLOCKLEN              \
    ((SD_CMD16_SET_BLOCKLEN & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD17_READ_SINGLE_BLOCK         \
    ((SD_CMD17_READ_SINGLE_BLOCK & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD18_READ_MULTIPLE_BLOCK       \
    ((SD_CMD18_READ_MULTIPLE_BLOCK & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
/* Class 4 - Block-Oriented Write Commands */
#define SDC_CMD24_WRITE_BLOCK               \
    ((SD_CMD24_WRITE_BLOCK & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD25_WRITE_MULTIPLE_BLOCK      \
    ((SD_CMD25_WRITE_MULTIPLE_BLOCK & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD27_PROGRAM_CSD               \
    ((SD_CMD27_PROGRAM_CSD & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
/* Class 6 - Block-Oriented Write Protection Commands */
#define SDC_CMD28_SET_WRITE_PROT            \
    ((SD_CMD28_SET_WRITE_PROT & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD29_CLR_WRITE_PROT            \
    ((SD_CMD29_CLR_WRITE_PROT & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD30_SEND_WRITE_PROT           \
    ((SD_CMD30_SEND_WRITE_PROT & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
/* Class 5 - Erase Commands */
#define SDC_CMD32_ERASE_WR_BLK_START        \
    ((SD_CMD32_ERASE_WR_BLK_START & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD33_ERASE_WR_BLK_END          \
    ((SD_CMD33_ERASE_WR_BLK_END & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD38_ERASE                     \
    ((SD_CMD38_ERASE & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
/* Class 7 - Lock Card Commands */
#define SDC_CMD42_LOCK_UNLOCK               \
    ((SD_CMD42_LOCK_UNLOCK & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
/* Class 8 - Application Specific Commands */
#define SDC_CMD55_APP_CMD                   \
    ((SD_CMD55_APP_CMD & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_CMD56_GEN_CMD                   \
    ((SD_CMD56_GEN_CMD & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)
#define SDC_ACMD6_SET_BUS_WIDTH             \
    ((SD_ACMD6_SET_BUS_WIDTH & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK | SDC_APP_CMD_MASK)
#define SDC_ACMD13_SD_STATUS                \
    ((SD_ACMD13_SD_STATUS & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK | SDC_APP_CMD_MASK)
#define SDC_ACMD22_SEND_NUM_WR_BLOCKS       \
    ((SD_ACMD22_SEND_NUM_WR_BLOCKS & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK | SDC_APP_CMD_MASK)
#define SDC_ACMD23_SET_WR_BLK_ERASE_COUNT   \
    ((SD_ACMD23_SET_WR_BLK_ERASE_COUNT & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK | SDC_APP_CMD_MASK)
#define SDC_ACMD41_SD_SEND_OP_COND          \
    ((SD_ACMD41_SD_SEND_OP_COND & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK | SDC_APP_CMD_MASK)
#define SDC_ACMD42_SET_CLR_CARD_DETECT      \
    ((SD_ACMD42_SET_CLR_CARD_DETECT & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK | SDC_APP_CMD_MASK)
#define SDC_ACMD51_SEND_SCR                 \
    ((SD_ACMD51_SEND_SCR & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK | SDC_APP_CMD_MASK)
/* Class 10 - Application Specific Commands */
#define SDC_CMD6_SWITCH_FUNC                \
    ((SD_CMD6_SWITCH_FUNC & SDC_CMD_IDX_MASK) | SDC_CMD_EN_MASK | SDC_NEED_RSP_MASK)

/* SD command interfaces */
#if (SDD_SMALL_SD_FOOTPRINT == 0)
extern uint32_t _sd_cmd0(void);
extern uint32_t _sd_cmd4(uint32_t dsr);
extern uint32_t _sd_cmd10(uint32_t rca, SD_CID * cid);
extern uint32_t _sd_cmd15(uint32_t rca);
extern uint32_t _sd_cmd17(uint32_t addr, SD_R32 * csr);
extern uint32_t _sd_cmd24(uint32_t addr, SD_R32 * csr);
extern uint32_t _sd_cmd27(SD_R32 * csr);
extern uint32_t _sd_cmd28(uint32_t addr, SD_R32 * csr);
extern uint32_t _sd_cmd29(uint32_t addr, SD_R32 * csr);
extern uint32_t _sd_cmd30(uint32_t addr, SD_R32 * csr);
extern uint32_t _sd_cmd32(uint32_t addr, SD_R32 * csr);
extern uint32_t _sd_cmd33(uint32_t addr, SD_R32 * csr);
extern uint32_t _sd_cmd38(SD_R32 * csr);
extern uint32_t _sd_cmd42(SD_R32 * csr);
extern uint32_t _sd_cmd56(uint32_t rdwr, SD_R32 * csr);
extern uint32_t _sd_acmd22(SD_R32 * csr);
extern uint32_t _sd_acmd23(uint32_t blocks, SD_R32 * csr);
extern uint32_t _sd_acmd42(uint32_t conn, SD_R32 * csr);
extern uint32_t _sd_cmd6(uint32_t mode, SD_R32 * csr);
#endif /* (SDD_SMALL_SD_FOOTPRINT == 0) */

extern uint32_t _sd_cmd2(SD_CID * cid);
extern uint32_t _sd_cmd3(SD_R32 * rca);
extern uint32_t _sd_cmd7(uint32_t rca, SD_R32 * csr);
extern uint32_t _sd_cmd8(uint32_t vhs_arg, SD_R32 * vhs_rsp);
extern uint32_t _sd_cmd9(uint32_t rca, SD_CSD * csd);
extern uint32_t _sd_cmd12(SD_R32 * csr);
extern uint32_t _sd_cmd13(uint32_t rca, SD_R32 * csr);
extern uint32_t _sd_cmd16(uint32_t blk_len, SD_R32 * csr);
extern uint32_t _sd_cmd18(uint32_t addr, SD_R32 * csr);
extern uint32_t _sd_cmd25(uint32_t addr, SD_R32 * csr);
extern uint32_t _sd_cmd55(uint32_t rca, SD_R32 * csr);
extern uint32_t _sd_acmd6(uint32_t bw, SD_R32 * csr);
extern uint32_t _sd_acmd13(SD_R32 * csr);
extern uint32_t _sd_acmd41(uint32_t hcs, SD_OCR * ocr);
extern uint32_t _sd_acmd51(SD_R32 * csr);

/* Data transfer mode state transition routines */
// extern uint32_t _sd_wait_sending_state(uint32_t rca);
// extern uint32_t _sd_wait_receiving_state(uint32_t rca);
extern uint32_t _sd_wait_programmed(uint32_t rca);
extern uint32_t _sd_wait_transferred(uint32_t rca);
extern uint32_t _sd_disconnect(uint32_t rca);
extern uint32_t _sd_connect(uint32_t rca);
extern uint32_t _sd_deselect_card(uint32_t rca);
extern uint32_t _sd_select_card(uint32_t rca);
extern uint32_t _sd_stop_transmission(uint32_t rca);

#endif /* __SDD_SD_H__ */
