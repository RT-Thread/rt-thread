/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __ECAT_HW___H__
#define __ECAT_HW___H__

#include "ecat_def.h"
#include "fsl_ecat.h"

#ifdef ECAT
/**< \brief Returns the first 16Bit of the AL Event register (0x220)*/
#define HW_GetALEventRegister()     ECAT_GetALEventRegister(ECAT)
#define HW_GetALEventRegister_Isr() ECAT_GetALEventRegister(ECAT)

/**< \brief Generic ESC (register and DPRAM) read access.*/
#define HW_EscRead(pData, Address, Len)    ECAT_EscRead(ECAT, pData, Address, Len)
#define HW_EscReadIsr(pData, Address, Len) ECAT_EscRead(ECAT, pData, Address, Len)

/**< \brief 32Bit specific ESC (register and DPRAM) read access.*/
#define HW_EscReadDWord(DWordValue, Address)    ECAT_EscReadDWord(ECAT, DWordValue, Address)
#define HW_EscReadDWordIsr(DWordValue, Address) ECAT_EscReadDWord(ECAT, DWordValue, Address)

/**< \brief Macro to copy data from the application mailbox memory(not the ESC memory, this access is handled by
 * HW_EscRead).*/
#define HW_EscReadMbxMem(pData, Address, Len) ECAT_EscRead(ECAT, pData, Address, Len)

/**< \brief Generic ESC (register and DPRAM) write access.*/
#define HW_EscWrite(pData, Address, Len)    ECAT_EscWrite(ECAT, pData, Address, Len)
#define HW_EscWriteIsr(pData, Address, Len) ECAT_EscWrite(ECAT, pData, Address, Len)

/**< \brief 32Bit specific ESC (register and DPRAM) write access.*/
#define HW_EscWriteDWord(DWordValue, Address)    ECAT_EscWriteDWord(ECAT, DWordValue, Address)
#define HW_EscWriteDWordIsr(DWordValue, Address) ECAT_EscWriteDWord(ECAT, DWordValue, Address)

/**< \brief Macro to copy data from the application mailbox memory (not the ESC memory, this access is handled by
 * HW_EscWrite).*/
#define HW_EscWriteMbxMem(pData, Address, Len) ECAT_EscWrite(ECAT, pData, Address, Len)

#else
/**< \brief Returns the first 16Bit of the AL Event register (0x220)*/
#define HW_GetALEventRegister()     ECAT_GetALEventRegister(ETHERCAT)
#define HW_GetALEventRegister_Isr() ECAT_GetALEventRegister(ETHERCAT)

/**< \brief Generic ESC (register and DPRAM) read access.*/
#define HW_EscRead(pData, Address, Len)    ECAT_EscRead(ETHERCAT, pData, Address, Len)
#define HW_EscReadIsr(pData, Address, Len) ECAT_EscRead(ETHERCAT, pData, Address, Len)

/**< \brief 32Bit specific ESC (register and DPRAM) read access.*/
#define HW_EscReadDWord(DWordValue, Address)    ECAT_EscReadDWord(ETHERCAT, DWordValue, Address)
#define HW_EscReadDWordIsr(DWordValue, Address) ECAT_EscReadDWord(ETHERCAT, DWordValue, Address)

/**< \brief Macro to copy data from the application mailbox memory(not the ESC memory, this access is handled by
 * HW_EscRead).*/
#define HW_EscReadMbxMem(pData, Address, Len) ECAT_EscRead(ETHERCAT, pData, Address, Len)

/**< \brief Generic ESC (register and DPRAM) write access.*/
#define HW_EscWrite(pData, Address, Len)    ECAT_EscWrite(ETHERCAT, pData, Address, Len)
#define HW_EscWriteIsr(pData, Address, Len) ECAT_EscWrite(ETHERCAT, pData, Address, Len)

/**< \brief 32Bit specific ESC (register and DPRAM) write access.*/
#define HW_EscWriteDWord(DWordValue, Address)    ECAT_EscWriteDWord(ETHERCAT, DWordValue, Address)
#define HW_EscWriteDWordIsr(DWordValue, Address) ECAT_EscWriteDWord(ETHERCAT, DWordValue, Address)

/**< \brief Macro to copy data from the application mailbox memory (not the ESC memory, this access is handled by
 * HW_EscWrite).*/
#define HW_EscWriteMbxMem(pData, Address, Len) ECAT_EscWrite(ETHERCAT, pData, Address, Len)
#endif

#define ECAT_TIMER_INC_P_MS 0x01

UINT16 HW_Init(void);
void HW_Release(void);

UINT16 HW_GetTimer(void);
void HW_ClearTimer(void);
void ENABLE_ESC_INT(void);
void DISABLE_ESC_INT(void);
void HW_SetLed(UINT8 RunLed, UINT8 ErrorLed);

#endif /* __ECAT_HW___H__ */
