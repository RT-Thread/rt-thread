/*
* @brief SPIFI registers and control functions
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

#ifndef __SPIFI_001_H_
#define __SPIFI_001_H_

#include "sys_config.h"
#include "cmsis.h"
#include "spifi_rom_api.h"

#ifdef __cplusplus
extern "C" {
#endif 

// FIXME this file needs work and better explanations

/** @defgroup IP_SPIFI_001 IP: SPIFI register block and driver
 * @ingroup IP_Drivers
 * @{
 */

extern void cancel_mem_mode(SPIFIobj *obj);
extern void (*set_mem_mode)   (SPIFIobj *obj);

  /* mid level functions */
extern int32_t checkAd(SPIFIobj *obj, SPIFIopers *opers);
extern int32_t setProt(SPIFIobj *obj, SPIFIopers *opers, char *change, 
                        char *saveProt);
extern int32_t check_block(SPIFIobj *obj, char *source, SPIFIopers *opers, 
                        uint32_t check_program);
extern int32_t send_erase_cmd(SPIFIobj *obj, uint8_t op, uint32_t addr);
extern uint32_t ck_erase(SPIFIobj *obj, uint32_t *addr, uint32_t length);
extern int32_t prog_block(SPIFIobj *obj, char *source, SPIFIopers *opers, 
                        uint32_t *left_in_page);
extern uint32_t ck_prog(SPIFIobj *obj, char *source, char *dest, uint32_t length);

  /* low level functions */
extern void setSize(SPIFIobj *obj, int32_t value);
extern int32_t setDev(SPIFIobj *obj, uint32_t opts, uint32_t mem_cmd, 
                        uint32_t prog_cmd);
extern uint32_t cmd(uc op, uc addrLen, uc intLen, uint16_t len);
extern uint32_t readAd(SPIFIobj *obj, uint32_t cmd, uint32_t addr);
extern void send04(SPIFIobj *obj, uc op, uc len, uint32_t value);
extern void wren_sendAd(SPIFIobj *obj, uint32_t cmd, uint32_t addr, uint32_t value);
extern int32_t write_stat(SPIFIobj *obj, uc len, uint16_t value);
extern int32_t wait_busy(SPIFIobj *obj, uc prog_or_erase);

/** 
 * @brief 	This call sends the standardized Read JEDEC ID command to the
 *			attached serial Flash device.  If it responds, it is set up for reading
 *			in ARM memory space.
 * @param 	obj		: Pointer to uninitialized SPIFIobj structure
 * @param 	csHigh	: Value that is one less than the minimum number of clock
 *						cycles with the CS pin high, that the SPIFI should maintain between
 *						commands. Compute this from the SPIFI clock period and the minimum high
 *						time of CS from the serial flash data sheet:
 *						csHigh = ceiling( min CS high / SPIFI clock period) - 1
 * @param	options	: contains bits controlling the SPIFI behavior.	See @ref IP_SPIFI_OPTIONS
 * @param	mhz		: should be the serial clock divided by 1000000.
 * @return	A return value of zero indicates success. Non-zero error codes indicate various error states.
 */
STATIC INLINE int32_t IP_SPIFI_Init(SPIFIobj *obj, uint32_t csHigh, uint32_t options, uint32_t mhz)
{
	return spifi_init(obj, csHigh, options, mhz);
}

/** 
 * @brief	This call programs opers.length bytes in the serial flash. An
 *			IP_SPIFI_Program call with source equal to opers.dest and opers.options
 *			not including S_FORCE_ERASE can be used to protect or unprotect sectors
 *			depending on the value of opers.protect.
 * @param	obj		: Pointer to initialized SPIFIobj structure (from IP_SPIFI_Init)
 * @param	source	: is the address of the data to be programmed
 * @param	opers	: specifies programming and erasing options
 * @return	A return value of zero indicates success. Non-zero error codes
 *			indicate various error states.
 */
STATIC INLINE int32_t IP_SPIFI_Program(SPIFIobj *obj, char *source, SPIFIopers *opers)
{
	return spifi_program(obj, source, opers);
}

/** 
 * @brief	This call erases opers.length bytes in the serial flash.
 * @param	obj		: Pointer to initialized SPIFIobj structure (from IP_SPIFI_Init)
 * @param	opers	: specifies erasing options
 * @return	A return value of zero indicates success. Non-zero error codes
 *			indicate various error states.
 */
STATIC INLINE int32_t IP_SPIFI_Erase(SPIFIobj *obj, SPIFIopers *opers)
{
	return spifi_erase(obj, opers);
}

/** 
 * @brief	: This function disables the memory mapping of the external QSPI flash.
 * @param	obj	: Pointer to initialized SPIFIobj structure (from IP_SPIFI_Init)
 * @return	No return value
 */
STATIC INLINE void IP_SPIFI_CancelMemMode(SPIFIobj *obj)
{
	cancel_mem_mode(obj);
}

STATIC INLINE void IP_SPIFI_SetMemMode(SPIFIobj *obj)
{
	set_mem_mode(obj);
}

  /* mid level functions */
STATIC INLINE int32_t IP_SPIFI_checkAd(SPIFIobj *obj, SPIFIopers *opers)
{
	return checkAd(obj, opers);
}

STATIC INLINE int32_t IP_SPIFI_setProt(SPIFIobj *obj, SPIFIopers *opers, char *change, char *saveProt)
{
	return setProt(obj, opers, change, saveProt);
}

STATIC INLINE int32_t IP_SPIFI_CheckBlock(SPIFIobj *obj, char *source, SPIFIopers *opers,
                        uint32_t check_program)
{
	return check_block(obj, source, opers, check_program);
}

STATIC INLINE int32_t IP_SPIFI_SendEraseCmd(SPIFIobj *obj, uint8_t op, uint32_t addr)
{
	return send_erase_cmd(obj, op, addr);
}

STATIC INLINE uint32_t IP_SPIFI_CkErase(SPIFIobj *obj, uint32_t *addr, uint32_t length)
{
	return ck_erase(obj, addr, length);
}

STATIC INLINE int32_t IP_SPIFI_ProgBlock(SPIFIobj *obj, char *source, SPIFIopers *opers,
                        uint32_t *left_in_page)
{
	return prog_block(obj, source, opers, left_in_page);
}

STATIC INLINE uint32_t IP_SPIFI_CkProg(SPIFIobj *obj, char *source, char *dest, uint32_t length)
{
	return ck_prog(obj, source, dest, length);
}

  /* low level functions */
STATIC INLINE void IP_SPIFI_SetSize(SPIFIobj *obj, int32_t value)
{
	setSize(obj, value);
}

STATIC INLINE int32_t IP_SPIFI_SetDev(SPIFIobj *obj, uint32_t opts, uint32_t mem_cmd,
                        uint32_t prog_cmd)
{
	return setDev(obj, opts, mem_cmd, prog_cmd);
}

STATIC INLINE uint32_t IP_SPIFI_Cmd(uc op, uc addrLen, uc intLen, uint16_t len)
{
	return cmd(op, addrLen, intLen, len);
}

STATIC INLINE uint32_t IP_SPIFI_ReadAd(SPIFIobj *obj, uint32_t cmd, uint32_t addr)
{
	return readAd(obj, cmd, addr);
}

STATIC INLINE void IP_SPIFI_Send04(SPIFIobj *obj, uc op, uc len, uint32_t value)
{
	send04(obj, op, len, value);
}

STATIC INLINE void IP_SPIFI_WrEnSendAd(SPIFIobj *obj, uint32_t cmd, uint32_t addr, uint32_t value)
{
	wren_sendAd(obj, cmd, addr, value);
}

STATIC INLINE int32_t IP_SPIFI_WriteStat(SPIFIobj *obj, uc len, uint16_t value)
{
	return write_stat(obj, len, value);
}

STATIC INLINE int32_t IP_SPIFI_WaitBusy(SPIFIobj *obj, uc prog_or_erase)
{
	return wait_busy(obj, prog_or_erase);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif 

#endif /* __SPIFI_001_H_ */
