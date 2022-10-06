/**
 * \file   board.h
 *
 * \brief  This file contains the prototypes of the functions present in
 *         utils/board.c .It also has structure declaration
 *         which is used to interpret the data read from EEPROM.
 *
 */

/*
* Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                    MACRO DEFINITIONS
****************************************************************************/

#define EEPROM_SIZE_HEADER         (4)
#define EEPROM_SIZE_BOARD_NAME     (8)
#define EEPROM_SIZE_VERSION        (5)
#define EEPROM_SIZE_SERIAL_NUMBER  (12)
#define MAX_DATA                   (EEPROM_SIZE_HEADER + \
		                    EEPROM_SIZE_BOARD_NAME + \
		                    EEPROM_SIZE_VERSION + \
		                    EEPROM_SIZE_SERIAL_NUMBER)

#define BOARD_UNKNOWN              (0xFF)
#define BOARD_VER_UNKNOWN          (0xFE)

/****************************************************************************
**                  STRUCTURE DECLARATION
****************************************************************************/

struct EEPROMData {
                 unsigned char header[EEPROM_SIZE_HEADER];
                 unsigned char boardName[EEPROM_SIZE_BOARD_NAME];
                 unsigned char version[EEPROM_SIZE_VERSION];
                 unsigned char serialNumber[EEPROM_SIZE_SERIAL_NUMBER];
            };

typedef struct EEPROMData BOARDINFO;
extern unsigned char boardVersion[];
extern unsigned char boardName[];
extern unsigned int boardId;

/****************************************************************************
**                    FUNCTION PROTOTYPES
****************************************************************************/

extern unsigned int BoardInfoCheck(unsigned char *boardId,
                                   unsigned char *boardVer);
extern unsigned int BoardInfoInit(void);
extern unsigned int BoardIdGet(void);
extern unsigned char *BoardNameGet(void);
extern void BoardInfoRead(unsigned char *);
extern unsigned char *BoardVersionGet(void);

#ifdef __cplusplus
}
#endif
#endif
