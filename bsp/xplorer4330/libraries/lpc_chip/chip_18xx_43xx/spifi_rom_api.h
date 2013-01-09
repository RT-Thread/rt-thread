/*
 * @brief	SPIFI ROM driver functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __SPIFI_ROM_API_H_
#define __SPIFI_ROM_API_H_

#include "chip.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* define the symbol TESTING in the environment	if test output desired */

/** @ingroup IP_SPIFI_001
 * @{
 */

/* maintain LONGEST_PROT >= the length (in bytes) of the largest
    protection block of any serial flash that this driver handles */
#define LONGEST_PROT 68

typedef uint8_t uc;

#ifndef NULL
#define NULL ((void *) 0)
#endif

/** Protection/sector descriptors */
typedef struct {
	uint32_t base;
	uc flags;
	int8_t log2;
	uint16_t rept;
} protEnt;
/* bits in the flags byte */
enum {RWPROT = 1};

#if 0

/* overall data structure includes # sectors, length of protection reg,
   array of descriptors */
typedef struct {
	uint16_t sectors;
	uint16_t protBytes;
	protEnt *entries;
} protDesc;
#endif

typedef union {
	uint16_t hw;
	uc byte[2];
} stat_t;
/** The object that spifi_init returns, and other routines use as an operand */
typedef struct {
	uint32_t base, regbase, devSize, memSize;
	uc mfger, devType, devID, busy;
	stat_t stat;
	uint16_t reserved;
	uint16_t set_prot, write_prot;
	uint32_t mem_cmd, prog_cmd;
	uint16_t sectors, protBytes;
	uint32_t opts, errCheck;
	uc erase_shifts[4], erase_ops[4];
	protEnt *protEnts;
	char prot[LONGEST_PROT];
} SPIFIobj;

/** operands of program and erase */
typedef struct {
	char *dest;
	uint32_t length;
	char *scratch;
	int32_t protect;
	uint32_t options;
} SPIFIopers;

/** instruction classes for wait_busy */
typedef enum {stat_inst, block_erase, prog_inst, chip_erase} inst_type;

/** @defgroup IP_SPIFI_OPTIONS IP: SPIFI configuration options
 * @ingroup IP_SPIFI_001
 * Options used to configure SPIFI
 * @{
 */

/** The SCL output is high when a frame/command is not in progress.
    Note that S_MODE3+S_FULLCLK+S_RCVCLK will not work. Use S_MODE0
    or S_INTCLK. */
#define S_MODE3 1

/** SCL is low when a frame/command is not in progress. (default) */
#define S_MODE0 0

/** SPI mode and the slowest, most basic/compatible read operation will be used. */
#define S_MINIMAL 2

/** The fastest read operation provided by the device will be used. (default) */
#define S_MAXIMAL 0

/** Data is sampled using the SCL clock fed back from the pin. This allows
    more time for the serial flash to present each bit or group of bits,
    but when used with S_FULLCLK can endanger hold time for data from the
    flash. */
#define S_RCVCLK 0x80

/** Data is sampled using the internal clock from which the SCL pin is driven. (default) */
#define S_INTCLK 0

/** Data from the serial flash is sampled on falling edges on the SCL
    output, allowing a full clock period for the serial flash to present
    each bit or group of bits. */
#define S_FULLCLK 0x40

/** Data from the serial flash is sampled on rising edges of the SCL
    output, as in classic SPI applications. Suitable for slower clock rates. (default) */
#define S_HALFCLK 0

/** If the connected device can operate in dual mode (2 bits per clock),
    dual mode will be used, else SPI mode. */
#define S_DUAL 0x100

/**
 * @}
 */

/** @defgroup IP_SPIFI_OPTIONS_PROGRAM IP: SPIFI programming options
 * @ingroup IP_SPIFI_001
 * Options used to configure SPIFI programming
 * @{
 */

/** All sectors in dest to dest+length will be erased */
#define S_FORCE_ERASE 4

/** Erasing is handled by the caller not by the driver */
#define S_ERASE_NOT_REQD 8

/** Erasing is handled by the caller not by the driver */
#define S_CALLER_ERASE 8

/** Erasing is done when necessary. (default) */
#define S_ERASE_AS_REQD 0

/** Data will be read back and checked after programming. */
#define S_VERIFY_PROG 0x10

/** Sectors will be read back and checked for 0xFF after erasing. */
#define S_VERIFY_ERASE 0x20

/** No reading or checking will be done. (default) */
#define S_NO_VERIFY 0

/** Write protection is handled by the caller not by the driver. */
#define S_CALLER_PROT 0x200

/** The driver removes protection before the operation, and sets it as specified thereafter. (default) */
#define S_DRIVER_PROT 0

/**
 * @}
 */

/* the following values in the first post-address memory command byte work
   for all known quad devices that support "no opcode" operation */
#define NO_OPCODE_FOLLOWS 0xA5
#define    OPCODE_FOLLOWS 0xFF

/* basic SPI commands for serial flash */
#define BASE_READ_CMD        (CMD_RD << OPCODE_SHIFT | 4 << FRAMEFORM_SHIFT | UNL_DATA)
#define FAST_READ_CMD (CMD_READ_FAST << OPCODE_SHIFT | 4 << FRAMEFORM_SHIFT | 1 << INTLEN_SHIFT | UNL_DATA)
#define BASE_PROG_CMD      (CMD_PROG << OPCODE_SHIFT | 4 << FRAMEFORM_SHIFT | DOUT)

/* the length of a standard	program command is 256 on all devices */
#define PROG_SIZE 256

/* options in obj->opts (mostly for setMulti) */
/* used by Winbond: send 0xA3 command so hardware can read faster */
#define OPT_SEND_A3        1
/* used by SST: send 0x38 command to enable quad and allow full command set */
#define OPT_SEND_38        2
/* used by Winbond and others: read status reg 2, check it,
    if necessary write it back with Quad Enable set */
#define OPT_35_OR02_01     4
/* used by Atmel: read Configuration register, if necessary set Quad Enable */
#define OPT_3F_OR80_3E     8
/* used by Numonyx to set all-quad mode: only for parts that include RSTQIO */
#define OPT_65_CLR_C0_61   0x10
/* used by Numonyx: send 0x81 command to write Volatile Configuration Register
   to set # dummy bytes and allow XIP mode */
#define OPT_81          0x20
/* set for devices without full device erase command (Numonyx type 0x40) */
#define OPT_NO_DEV_ERASE 0x40
/* used by Macronix: status reg 2 includes selection between write-protect
    in status reg and command-based */
#define OPT_WPSEL       0x80
/* set when protection data has been read into the SPIFI object */
#define OPT_PROT_READ  0x100
/* set if device needs 4-byte address (and maybe 0x4B command = use 4-byte address) */
#define OPT_4BAD       0x200
/* set if setMulti should set the Dual bit in Control reg */
#define OPT_DUAL       0x400
/* send "# dummy bits" in C0 command to Winbond */
#define OPT_C0         0x800
/* set QE for Chingis */
#define OPT_05_OR40_01 0x1000
/* write status does not go busy */
#define OPT_01_NO_BUSY 0x2000
/* protection mode bits moved from protMode byte to opts  Fri May 13 2011 */
#define OPT_PROT_STAT 0x4000
#define OPT_PROT_REG  0x8000
#define OPT_PROT_CMD3 0x10000
#define OPT_PROT_CMDE 0x20000
#define OPT_PROT_MASK 0x3C000

#define OPT_ALL_QUAD  0x40000

#ifndef OMIT_ROM_TABLE
/* interface to ROM API */
typedef struct {
	int32_t (*spifi_init)(SPIFIobj *obj, uint32_t csHigh, uint32_t options,
						  uint32_t mhz);
	int32_t (*spifi_program)(SPIFIobj *obj, char *source, SPIFIopers *opers);
	int32_t (*spifi_erase)(SPIFIobj *obj, SPIFIopers *opers);
	/* mode switching */
	void (*cancel_mem_mode)(SPIFIobj *obj);
	void (*set_mem_mode)(SPIFIobj *obj);

	/* mid level functions */
	int32_t (*checkAd)(SPIFIobj *obj, SPIFIopers *opers);
	int32_t (*setProt)(SPIFIobj *obj, SPIFIopers *opers, char *change,
					   char *saveProt);
	int32_t (*check_block)(SPIFIobj *obj, char *source, SPIFIopers *opers,
						   uint32_t check_program);
	int32_t (*send_erase_cmd)(SPIFIobj *obj, uint8_t op, uint32_t addr);
	uint32_t (*ck_erase)(SPIFIobj *obj, uint32_t *addr, uint32_t length);
	int32_t (*prog_block)(SPIFIobj *obj, char *source, SPIFIopers *opers,
						  uint32_t *left_in_page);
	uint32_t (*ck_prog)(SPIFIobj *obj, char *source, char *dest, uint32_t length);

	/* low level functions */
	void (*setSize)(SPIFIobj *obj, int32_t value);
	int32_t (*setDev)(SPIFIobj *obj, uint32_t opts, uint32_t mem_cmd,
					  uint32_t prog_cmd);
	uint32_t (*cmd)(uc op, uc addrLen, uc intLen, uint16_t len);
	uint32_t (*readAd)(SPIFIobj *obj, uint32_t cmd, uint32_t addr);
	void (*send04)(SPIFIobj *obj, uc op, uc len, uint32_t value);
	void (*wren_sendAd)(SPIFIobj *obj, uint32_t cmd, uint32_t addr, uint32_t value);
	int32_t (*write_stat)(SPIFIobj *obj, uc len, uint16_t value);
	int32_t (*wait_busy)(SPIFIobj *obj, uc prog_or_erase);
} SPIFI_RTNS;

#define SPIFI_ROM_PTR  0x10400118

#define define_spifi_romPtr(name) const SPIFI_RTNS * name = *((SPIFI_RTNS * *) SPIFI_ROM_PTR)
#endif /* OMIT_ROM_TABLE */

#ifdef USE_SPIFI_LIB
extern SPIFI_RTNS spifi_table;
#endif  /* USE_SPIFI_LIB */

/* example of using this interface:
   #include "spifi_rom_api.h"
   #define CSHIGH 4
   #define SPIFI_MHZ 80
   #define source_data_ad (char *)1234

    int32_t rc;
    SPIFIopers opers;

    define_spifi_romPtr(spifi);
    SPIFIobj *obj = malloc(sizeof(SPIFIobj));
    if (!obj) { can't allocate memory }

    rc = spifi->spifi_init (obj, CSHIGH, S_FULLCLK+S_RCVCLK, SPIFI_MHZ);
    if (rc) { investigate init error rc }
    printf ("the serial flash contains %d bytes\n", obj->devSize);

    opers.dest = where_to_program;
    opers.length = how_many_bytes;
    opers.scratch = NULL;			// unprogrammed data is not saved/restored
    opers.protect = -1;				// save & restore protection
    opers.options = S_VERIFY_PROG;

    rc = spifi->spifi_program (obj, source_data_ad, &opers);
    if (rc) { investigate program error rc }
 */

/* these are for normal users, including boot code */
int32_t spifi_init (SPIFIobj *obj, uint32_t csHigh, uint32_t options, uint32_t mhz);

int32_t spifi_program (SPIFIobj *obj, char *source, SPIFIopers *opers);

int32_t spifi_erase (SPIFIobj *obj, SPIFIopers *opers);

/* these are used by the manufacturer-specific init functions */
void setSize (SPIFIobj *obj, int32_t value);

int32_t setDev (SPIFIobj *obj, uint32_t opts, uint32_t mem_cmd, uint32_t prog_cmd);

uint32_t read04(SPIFIobj *obj, uc op, uc len);

int32_t write_stat (SPIFIobj *obj, uc len, uint16_t value);

void setProtEnts(SPIFIobj *obj, const protEnt *p, uint32_t protTabLen);

/* needs to be defined for each platform */
void pullMISO(int high);

#ifdef TESTING
/* used by testing code */
unsigned short getProtBytes (SPIFIobj *obj, unsigned short *sectors);

/* predeclare a debug routine */
void wait_sample (volatile unsigned *addr, unsigned mask, unsigned value);

#endif

/**
 * @}
 */

 #ifdef __cplusplus
}
#endif

#endif /* __SPIFI_ROM_API_H_ */
