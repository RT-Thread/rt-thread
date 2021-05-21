/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-08 11:50:53
 * @LastEditTime: 2021-04-16 13:29:24
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef _FT_SDMMC_H_
#define _FT_SDMMC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"
#include "ft_trace.h"
#include "ft_error_code.h"
#include "ft_sdmmc_defs.h"

/**
 * Decoded values from SD card Card Specific Data register
 */
typedef struct {
    int csdVer;                /*!< CSD structure format */
    int mmcVer;                /*!< MMC version (for CID format) */
    int capacity;               /*!< total number of sectors */
    int sectorSize;            /*!< sector size in bytes */
    int readBlkLen;         /*!< block length for reads */
    int cardCmdClass;     /*!< Card Command Class for SD */
    int transSpeed;               /*!< Max transfer speed */
} Sdmmc_CSD_t;

/**
 * Decoded values from SD card Card IDentification register
 */
typedef struct {
    int mfgId;     /*!< manufacturer identification number */
    int oemId;     /*!< OEM/product identification number */
    char name[8];   /*!< product name (MMC v1 has the longest) */
    int revision;   /*!< product revision */
    int serial;     /*!< product serial number */
    int date;       /*!< manufacturing date */
} Sdmmc_CID_t;

/**
 * Decoded values from SD Configuration Register
 */
typedef struct {
    int sdSpec;    /*!< SD Physical layer specification version, reported by card */
    int bus_width;  /*!< bus widths supported by card: BIT(0) — 1-bit bus, BIT(2) — 4-bit bus */
} Sdmmc_SCR_t;

/**
 * Decoded values of Extended Card Specific Data
 */
typedef struct {
    u8 power_class;    /*!< Power class used by the card */
} Sdmmc_ExtCSD_t;

/**
 * SD/MMC command response buffer
 */
typedef u32 Sdmmc_Resp_t[4];

/**
 * SD SWITCH_FUNC response buffer
 */
typedef struct {
    u32 data[512 / 8 / sizeof(u32)];  /*!< response data */
} Sdmmc_SwitchFuncRsp_t;

/**
 * SD/MMC command information
 */
typedef struct {
        u32 opcode;            /*!< SD or MMC command index */
        u32 arg;               /*!< SD/MMC command argument */
        Sdmmc_Resp_t response;  /*!< response buffer */
        //u32 response[4];
        void* data;                 /*!< buffer to send or read into */
        size_t datalen;             /*!< length of data buffer */
        size_t blklen;              /*!< block length */
        int flags;                  /*!< see below */
/** @cond */
#define SCF_ITSDONE      0x0001     /*!< command is complete */
#define SCF_CMD(flags)   ((flags) & 0x00f0)
#define SCF_CMD_AC       0x0000
#define SCF_CMD_ADTC     0x0010
#define SCF_CMD_BC       0x0020
#define SCF_CMD_BCR      0x0030
#define SCF_CMD_READ     0x0040     /*!< read command (data expected) */
#define SCF_RSP_BSY      0x0100
#define SCF_RSP_136      0x0200
#define SCF_RSP_CRC      0x0400
#define SCF_RSP_IDX      0x0800
#define SCF_RSP_PRESENT  0x1000
/* response types */
#define SCF_RSP_R0       0 /*!< none */
#define SCF_RSP_R1       (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX)
#define SCF_RSP_R1B      (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX|SCF_RSP_BSY)
#define SCF_RSP_R2       (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_136)
#define SCF_RSP_R3       (SCF_RSP_PRESENT)
#define SCF_RSP_R4       (SCF_RSP_PRESENT)
#define SCF_RSP_R5       (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX)
#define SCF_RSP_R5B      (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX|SCF_RSP_BSY)
#define SCF_RSP_R6       (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX)
#define SCF_RSP_R7       (SCF_RSP_PRESENT|SCF_RSP_CRC|SCF_RSP_IDX)
/* special flags */
#define SCF_WAIT_BUSY    0x2000     /*!< Wait for completion of card busy signal before returning */
/** @endcond */
        u32 cmd_resp_type;     /*!< command respones type */
#define SCT_RESP_NONE    0x01
#define SCT_RESP_LONG    0x02
#define SCT_RESP_SHORT   0x04
        ft_error_t error; /*!< error returned from transfer */
        int timeout_ms;   /*!< response timeout, in milliseconds */
} Sdmmc_Cmd_t;

/**
 * SD/MMC Host description
 *
 * This structure defines properties of SD/MMC host and functions
 * of SD/MMC host which can be used by upper layers.
 */
typedef struct {
    u32 flags;             /*!< flags defining host properties */
#define SDMMC_HOST_FLAG_1BIT    BIT(0)      /*!< host supports 1-line SD and MMC protocol */
#define SDMMC_HOST_FLAG_4BIT    BIT(1)      /*!< host supports 4-line SD and MMC protocol */
#define SDMMC_HOST_FLAG_8BIT    BIT(2)      /*!< host supports 8-line MMC protocol */
#define SDMMC_HOST_FLAG_SPI     BIT(3)      /*!< host supports SPI protocol */
#define SDMMC_HOST_FLAG_DDR     BIT(4)      /*!< host supports DDR mode for SD/MMC */
    int slot;                   /*!< slot number, to be passed to host functions */
    int max_freq_khz;           /*!< max frequency supported by the host */
#define SDMMC_FREQ_DEFAULT      20000       /*!< SD/MMC Default speed (limited by clock divider) */
#define SDMMC_FREQ_HIGHSPEED    40000       /*!< SD High speed (limited by clock divider) */
#define SDMMC_FREQ_PROBING      400         /*!< SD/MMC probing speed */
#define SDMMC_FREQ_52M          52000       /*!< MMC 52MHz speed */
#define SDMMC_FREQ_26M          26000       /*!< MMC 26MHz speed */
    float io_voltage;           /*!< I/O voltage used by the controller (voltage switching is not supported) */
    ft_error_t (*init)(void);    /*!< Host function to initialize the driver */
    ft_error_t (*set_bus_width)(int slot, size_t width);    /*!< host function to set bus width */
    size_t (*get_bus_width)(int slot); /*!< host function to get bus width */
    ft_error_t (*set_bus_ddr_mode)(int slot, bool_t ddr_enable); /*!< host function to set DDR mode */
    ft_error_t (*set_card_clk)(int slot, u32 freq_khz); /*!< host function to set card clock frequency */
    ft_error_t (*do_transaction)(int slot, Sdmmc_Cmd_t* cmdinfo);    /*!< host function to do a transaction */
    ft_error_t (*deinit)(void);  /*!< host function to deinitialize the driver */
    ft_error_t (*io_int_enable)(int slot); /*!< Host function to enable SDIO interrupt line */
    ft_error_t (*io_int_wait)(int slot, u32 timeout_ticks); /*!< Host function to wait for SDIO interrupt line to be active */
    int command_timeout_ms;     /*!< timeout, in milliseconds, of a single command. Set to 0 to use the default value. */
} Sdmmc_Host_t;

/**
 * SD/MMC card information structure
 */
typedef struct {
    Sdmmc_Host_t host;          /*!< Host with which the card is associated */
    u32 ocr;               /*!< OCR (Operation Conditions Register) value */
    union {
        Sdmmc_CID_t cid;            /*!< decoded CID (Card IDentification) register value */
        Sdmmc_Resp_t raw_cid;   /*!< raw CID of MMC card to be decoded
                                         after the CSD is fetched in the data transfer mode*/
    };
    Sdmmc_CSD_t csd;            /*!< decoded CSD (Card-Specific Data) register value */
    Sdmmc_SCR_t scr;            /*!< decoded SCR (SD card Configuration Register) value */
    Sdmmc_ExtCSD_t ext_csd;    /*!< decoded EXT_CSD (Extended Card Specific Data) register value */
    u16 rca;               /*!< RCA (Relative Card Address) */
    u16 max_freq_khz;      /*!< Maximum frequency, in kHz, supported by the card */
    u32 is_mem : 1;        /*!< Bit indicates if the card is a memory card */
    u32 is_sdio : 1;       /*!< Bit indicates if the card is an IO card */
    u32 is_mmc : 1;        /*!< Bit indicates if the card is MMC */
    u32 num_io_functions : 3;  /*!< If is_sdio is 1, contains the number of IO functions on the card */
    u32 log_bus_width : 2; /*!< log2(bus width supported by card) */
    u32 is_ddr : 1;        /*!< Card supports DDR mode */
    u32 reserved : 23;     /*!< Reserved for future expansion */
} Sdmmc_Card_t;

/*
* Platform configuration for SDMMC
*/
typedef struct
{
    void (*task_delay)(u32 ticks_to_delay);  /* os-depends tick time delay method */
    void *(*heap_alloc)(size_t size);        /* os-depends heap allocate method */
    void (*heap_free)(void *ptr);            /* os-depends heap free method */
    bool_t (*check_dma_capable)(const void *ptr);  /* os-depends memory allign check before dma */
    void (*printf)(const char *fmt, ...);    /* os-depends printf method */
    u32 tick_period;                         /* os-depends tick time period */
    void *event_queue;                       /* os-depends event queue */
    void *io_intr_event;                     /* os-depends event semphere */
} Sdmmc_OSImpl_t;
const Sdmmc_OSImpl_t *get_sdmmc_os_impl();
static inline void Sdmmc_Printf(const char *fmt, ...)
{
    get_sdmmc_os_impl()->printf(fmt);
}

static inline void *Sdmmc_HeapMalloc(size_t size)
{
    //FT_MEM_TRACE("size %d", size);
    Sdmmc_TraceHeapAlloc("BEF-MALLOC");
    void *pMen = get_sdmmc_os_impl()->heap_alloc(size);
    //FT_MEM_TRACE("malloc 0x%p size %d", pMen);
    return pMen;
}

static inline void Sdmmc_HeapFree(void *ptr)
{
    if (NULL != ptr)
    {
        //FT_MEM_TRACE("free 0x%p", ptr);
        Sdmmc_TraceHeapAlloc("BEF-FREE");
        get_sdmmc_os_impl()->heap_free(ptr);
    }
    return;
}

static inline void Sdmmc_Delay(u32 tick)
{
    get_sdmmc_os_impl()->task_delay(tick);
}

static inline bool_t Sdmmc_DMACapable(const void *ptr)
{
    get_sdmmc_os_impl()->check_dma_capable(ptr);
}

#ifdef __cplusplus
}
#endif

#endif