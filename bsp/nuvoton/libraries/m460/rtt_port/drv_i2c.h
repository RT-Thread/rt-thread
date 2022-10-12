/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-11-11      Wayne        First version
*
******************************************************************************/

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#define NU_I2C_MASTER_STATUS_START                   0x08UL
#define NU_I2C_MASTER_STATUS_REPEAT_START            0x10UL
#define NU_I2C_MASTER_STATUS_TRANSMIT_ADDRESS_ACK    0x18UL
#define NU_I2C_MASTER_STATUS_TRANSMIT_ADDRESS_NACK   0x20UL
#define NU_I2C_MASTER_STATUS_TRANSMIT_DATA_ACK       0x28UL
#define NU_I2C_MASTER_STATUS_TRANSMIT_DATA_NACK      0x30UL
#define NU_I2C_MASTER_STATUS_ARBITRATION_LOST        0x38UL
#define NU_I2C_MASTER_STATUS_RECEIVE_ADDRESS_ACK     0x40UL
#define NU_I2C_MASTER_STATUS_RECEIVE_ADDRESS_NACK    0x48UL
#define NU_I2C_MASTER_STATUS_RECEIVE_DATA_ACK        0x50UL
#define NU_I2C_MASTER_STATUS_RECEIVE_DATA_NACK       0x58UL
#define NU_I2C_MASTER_STATUS_BUS_ERROR               0x00UL

#define NU_I2C_SLAVE_STATUS_TRANSMIT_REPEAT_START_OR_STOP 0xA0UL
#define NU_I2C_SLAVE_STATUS_TRANSMIT_ADDRESS_ACK          0xA8UL
#define NU_I2C_SLAVE_STATUS_TRANSMIT_DATA_ACK             0xB8UL
#define NU_I2C_SLAVE_STATUS_TRANSMIT_DATA_NACK            0xC0UL
#define NU_I2C_SLAVE_STATUS_TRANSMIT_LAST_DATA_ACK        0xC8UL
#define NU_I2C_SLAVE_STATUS_RECEIVE_ADDRESS_ACK           0x60UL
#define NU_I2C_SLAVE_STATUS_RECEIVE_ARBITRATION_LOST      0x68UL
#define NU_I2C_SLAVE_STATUS_RECEIVE_DATA_ACK              0x80UL
#define NU_I2C_SLAVE_STATUS_RECEIVE_DATA_NACK             0x88UL

#define NU_I2C_SLAVE_GC_ADDRESS_ACK                             0x70UL
#define NU_I2C_SLAVE_GC_ARBITRATION_LOST                        0x78UL
#define NU_I2C_SLAVE_GC_DATA_ACK                                0x90UL
#define NU_I2C_SLAVE_GC_DATA_NACK                               0x98UL
#define NU_I2C_SLAVE_GC_ADDRESS_TRANSMIT_ARBITRATION_LOST       0xB0UL

#define NU_I2C_STATUS_BUS_RELEASED            0xF8UL
#define NU_I2C_MASTER_STATUS_BUS_RELEASED     NU_I2C_STATUS_BUS_RELEASED
#define NU_I2C_SLAVE_STATUS_BUS_RELEASED      NU_I2C_STATUS_BUS_RELEASED

#endif /* __DRV_I2C_H__ */
