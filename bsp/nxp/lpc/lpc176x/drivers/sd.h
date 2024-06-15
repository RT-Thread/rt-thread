#ifndef __SD_H__
#define __SD_H__

#include <stdint.h>

/* SD/MMC Commands */
#define GO_IDLE_STATE           (0x40 + 0)      // CMD0
#define SEND_OP_COND            (0x40 + 1)
#define CMD8                    (0x40 + 8)      // CMD8
#define SEND_CSD                (0x40 + 9)
#define SEND_CID                (0x40 + 10)     // CMD10
#define STOP_TRAN               (0x40 + 12)     // CMD12
#define SET_BLOCKLEN            (0x40 + 16)     // CMD16
#define READ_BLOCK              (0x40 + 17)
#define READ_MULT_BLOCK         (0x40 + 18)
#define WRITE_BLOCK             (0x40 + 24)
#define WRITE_MULT_BLOCK        (0x40 + 25)
#define APP_CMD                 (0x40 + 55)     // CMD55
#define READ_OCR                (0x40 + 58)     // CMD58
#define CRC_ON_OFF              (0x40 + 59)
#define SD_SEND_OP_COND         (0xC0 + 41)     // ACMD41
#define SD_STATUS               (0xC0 + 13)     // ACMD13, SD_STATUS (SDC)
#define SET_WR_BLK_ERASE_COUNT  (0xC0 + 23)     // ACMD23 (SDC)

/* Card type flags (CardType) */
#define CT_NONE             0x00
#define CT_MMC              0x01
#define CT_SD1              0x02
#define CT_SD2              0x04
#define CT_SDC              (CT_SD1|CT_SD2)
#define CT_BLOCK            0x08

/* MMC device configuration */
typedef struct tagSDCFG
{
    uint32_t sernum;        // serial number
    uint32_t size;          // size=sectorsize*sectorcnt
    uint32_t sectorcnt;     //
    uint32_t sectorsize;    // 512
    uint32_t blocksize;     // erase block size
    uint8_t ocr[4];         // OCR
    uint8_t cid[16];        // CID
    uint8_t csd[16];        // CSD
} SDCFG;

void rt_hw_sdcard_init(void);

#endif
