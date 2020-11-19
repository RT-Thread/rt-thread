/*!
 *   <b> COPYRIGHT(C) & copy; 2014-2015 Honeywell Inc. All rights reserved.</b>
 *
 *   This software is a copyrighted work and/or information protected as a
 *   trade secret. Legal rights of Honeywell Inc in this software is distinct
 *   from ownership of any medium in which the software is embodied. Copyright
 *   or trade secret notices included must be reproduced in any copy autorized
 *   by Honeywell Inc.  The information in this software is subject to change
 *   without notice and should not be considered as a commitment by Honeywell.
 *
 *   \file     crc.c
 *
 *   \brief    Routine computes 16-bit CRC.
 *
 *   \author   Kantha
 *
 *   \date     10.07.2014
 *
 *   \version  \a 1.0
 *
 *      \li \a Version 1.0 - Initial version
 */

#ifndef CRC_H
#define CRC_H

/*!
 -------------------------------------------------------------------------------
   Include Files
 -------------------------------------------------------------------------------
 */

/*!
 -------------------------------------------------------------------------------
   Exported Function Declarations
 -------------------------------------------------------------------------------
 */

/*! \fn       void CrcComputeCrc16()
 *  \brief    CRC_CCITT calculation
 */
unsigned short int CrcComputeCrc16(unsigned char u8Data, unsigned short int u16CurrCrc);

#endif /* CRC_H */
