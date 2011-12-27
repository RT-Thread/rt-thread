/**
 * @section LICENSE
 ******************************************************************************
 *           <b>(C) Copyright 2009 Energy Micro AS, www.energymicro.com</b>
 ******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source/compiled
 * code may not be used, redistributed or modified without a written consent
 * from Energy Micro AS.
 *
 * This copyright notice may not be removed from the source code nor changed.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************
 * @file dmd_if_ssd2119_ebi.h
 * @brief Dot matrix display SSD2119 interface using EBI
 * @author Energy Micro AS
 ******************************************************************************
 */

#ifndef __DMD_IF_SSD2119_EBI_H_
#define __DMD_IF_SSD2119_EBI_H_

#include <stdint.h>

/* Module Prototypes */
EMSTATUS DMDIF_init(uint32_t cmdRegAddr, uint32_t dataRegAddr);
EMSTATUS DMDIF_writeReg(uint8_t reg, uint16_t data);
uint16_t DMDIF_readDeviceCode(void);
EMSTATUS DMDIF_prepareDataAccess(void);
EMSTATUS DMDIF_writeData(uint32_t data);
EMSTATUS DMDIF_writeDataRepeated(uint32_t data, int len);
uint32_t DMDIF_readData(void);

#endif
