/***************************************************************************//**
 * @file    mma7455l.c
 * @brief   Header file of Freescale MMA7455L 3 axis Low-g digital output
 *  accelerometer
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2011-08-02   onelife     Initial creation
 ******************************************************************************/
#ifndef __MMA7455L_H__
#define __MMA7455L_H__

#define XOUTL       0x00    //00  10 bits output value X LSB (Read only)
#define XOUTH       0x01    //01  10 bits output value X MSB (Read only)
#define YOUTL       0x02    //02  10 bits output value Y LSB (Read only)
#define YOUTH       0x03    //03  10 bits output value Y MSB (Read only)
#define ZOUTL       0x04    //04  10 bits output value Z LSB (Read only)
#define ZOUTH       0x05    //05  10 bits output value Z MSB (Read only)
#define XOUT8       0x06    //06   8 bits Output value X (Read only)
#define YOUT8       0x07    //07   8 bits Output value Y (Read only)
#define ZOUT8       0x08    //08   8 bits Output value Z (Read only)
#define STATUS      0x09    //09  Status registers (Read only)
#define DETSRC      0x0A    //10  Detection source registers (Read only)
#define TOUT        0x0B    //11  Temperature output value (Optional)
#define RESERVED1   0x0C    //12  Reserved
#define I2CAD       0x0D    //13  I2C device address (Bit[6:0]: Read only, Bit[7]: Read/Write)
#define USRINF      0x0E    //14  User information  (Optional, Read only)
#define WHOAMI      0x0F    //15  Who am I value (Optional, Read only)
#define XOFFL       0x10    //16  Offset drift X value (LSB) (Read/Write)
#define XOFFH       0x11    //17  Offset drift X value (MSB) (Read/Write)
#define YOFFL       0x12    //18  Offset drift Y value (LSB) (Read/Write)
#define YOFFH       0x13    //19  Offset drift Y value (MSB) (Read/Write)
#define ZOFFL       0x14    //20  Offset drift Z value (LSB) (Read/Write)
#define ZOFFH       0x15    //21  Offset drift Z value (MSB) (Read/Write)
#define MCTL        0x16    //22  Mode control (Read/Write)
#define INTRST      0x17    //23  Interrupt latch reset (Read/Write)
#define CTL1        0x18    //24  Control 1 (Read/Write)
#define CTL2        0x19    //25  Control 2 (Read/Write)
#define LDTH        0x1A    //26  Level detection threshold limit value (Read/Write)
#define PDTH        0x1B    //27  Pulse detection threshold limit value (Read/Write)
#define PW          0x1C    //28  Pulse duration value (Read/Write)
#define LT          0x1D    //29  Latency time value  (Read/Write)
#define TW          0x1E    //30  Time window for second pulse value(Read/Write)
#define RESERVED2   0x1F    //31 Reserved

/* For DETSRC */
#define DETSRC_INT_1                (0x01 << 0)
#define DETSRC_INT_2                (0x01 << 1)
#define DETSRC_PULSE_Z              (0x01 << 2)
#define DETSRC_PULSE_Y              (0x01 << 3)
#define DETSRC_PULSE_X              (0x01 << 4)
#define DETSRC_LEVEL_Z              (0x01 << 5)
#define DETSRC_LEVEL_Y              (0x01 << 6)
#define DETSRC_LEVEL_X              (0x01 << 7)

/* For MCTL */
#define MCTL_SHIFT_MODE             (0)
#define MCTL_SHIFT_G                (2)
#define MCTL_MASK_MODE              (0x03)
#define MCTL_MASK_G                 (0x0c)
#define MCTL_MODE_STANDBY           (0x00 << MCTL_SHIFT_MODE)
#define MCTL_MODE_MEASUREMENT       (0x01 << MCTL_SHIFT_MODE)
#define MCTL_MODE_LEVEL             (0x02 << MCTL_SHIFT_MODE)
#define MCTL_MODE_PULSE             (0x03 << MCTL_SHIFT_MODE)
#define MCTL_RANGE_8G               (0x00 << MCTL_SHIFT_G)
#define MCTL_RANGE_4G               (0x02 << MCTL_SHIFT_G)
#define MCTL_RANGE_2G               (0x01 << MCTL_SHIFT_G)
#define MCTL_PIN_INT1               (0x01 << 6)

/* For INTRST */
#define INTRST_INT_1                (0x01 << 0)
#define INTRST_INT_2                (0x01 << 1)

/* For CTL1 */
#define CTL1_SHIFT_INTPIN           (0)
#define CTL1_SHIFT_INT              (1)
#define CTL1_SHIFT_AXES             (3)
#define CTL1_SHIFT_THRESHOLD        (6)
#define CTL1_SHIFT_BANDWIDTH        (7)
#define CTL1_MASK_AXES              (0x38)
#define CTL1_INTPIN_INVERSE         (0x01 << CTL1_SHIFT_INTPIN)
#define CTL1_INT_LEVEL_PULSE        (0x00 << CTL1_SHIFT_INT)
#define CTL1_INT_PULSE_LEVEL        (0x01 << CTL1_SHIFT_INT)
#define CTL1_INT_SINGLE_DOUBLE      (0x02 << CTL1_SHIFT_INT)
#define CTL1_X_DISABLE              (0x01 << CTL1_SHIFT_AXES)
#define CTL1_Y_DISABLE              (0x02 << CTL1_SHIFT_AXES)
#define CTL1_Z_DISABLE              (0x04 << CTL1_SHIFT_AXES)
#define CTL1_THRESHOLD_ABSOLUTE     (0x00 << CTL1_SHIFT_THRESHOLD)
#define CTL1_THRESHOLD_INTEGER      (0x01 << CTL1_SHIFT_THRESHOLD)
#define CTL1_BANDWIDTH_62_5HZ       (0x00 << CTL1_SHIFT_BANDWIDTH)
#define CTL1_BANDWIDTH_125HZ        (0x01 << CTL1_SHIFT_BANDWIDTH)

/* For CTL2 */
#define CTL1_SHIFT_LEVEL            (0)
#define CTL1_SHIFT_PULSE            (1)
#define CTL1_SHIFT_DRIVE            (2)
#define CTL2_LEVEL_OR               (0x00 << CTL1_SHIFT_LEVEL)
#define CTL2_LEVEL_AND              (0x01 << CTL1_SHIFT_LEVEL)
#define CTL2_PULSE_OR               (0x00 << CTL1_SHIFT_PULSE)
#define CTL2_PULSE_AND              (0x01 << CTL1_SHIFT_PULSE)
#define CTL2_DRIVE_STANDARD         (0x00 << CTL1_SHIFT_DRIVE)
#define CTL2_DRIVE_STRONG           (0x01 << CTL1_SHIFT_DRIVE)

#endif /* __MMA7455L_H__ */
