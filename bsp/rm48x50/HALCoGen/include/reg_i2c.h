/** @file reg_i2c.h
*   @brief I2C Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the I2C driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_I2C_H__
#define __REG_I2C_H__

#include "sys_common.h"
#include "gio.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* I2c Register Frame Definition */
/** @struct i2cBase
*   @brief I2C Base Register Definition
*
*   This structure is used to access the I2C module registers.
*/
/** @typedef i2cBASE_t
*   @brief I2C Register Frame Type Definition
*
*   This type is used to access the I2C Registers.
*/
typedef volatile struct i2cBase
{

    uint32 OAR;           /**<  0x0000 I2C Own Address register               */
    uint32 IMR;           /**<  0x0004 I2C Interrupt Mask/Status register     */
    uint32 STR;           /**<  0x0008 I2C Interrupt Status register          */
    uint32 CLKL;          /**<  0x000C I2C Clock Divider Low register         */
    uint32 CLKH;          /**<  0x0010 I2C Clock Divider High register        */
    uint32 CNT;           /**<  0x0014 I2C Data Count register                */
    uint32 DRR;           /**<  0x0018 I2C Data Receive register              */
    uint32 SAR;           /**<  0x001C I2C Slave Address register             */
    uint32 DXR;           /**<  0x0020 I2C Data Transmit register             */
    uint32 MDR;           /**<  0x0024 I2C Mode register                      */
    uint32 IVR;           /**<  0x0028 I2C Interrupt Vector register          */
    uint32 EMDR;          /**<  0x002C I2C Extended Mode register             */
    uint32 PSC;           /**<  0x0030 I2C Prescaler register                 */
    uint32 PID11;         /**<  0x0034 I2C Peripheral ID register 1           */
    uint32 PID12;         /**<  0x0038 I2C Peripheral ID register 2           */
    uint32 DMAC;          /**<  0x003C I2C DMA Control Register               */
    uint32   rsvd1;       /**<  0x0040 Reserved                               */
    uint32   rsvd2;       /**<  0x0044 Reserved                               */
    uint32 FUN;           /**<  0x0048 Pin Function Register                  */
    uint32 DIR;           /**<  0x004C Pin Direction Register                 */
    uint32 DIN;           /**<  0x0050 Pin Data In Register                   */
    uint32 DOUT;          /**<  0x0054 Pin Data Out Register                  */
    uint32 SET;           /**<  0x0058 Pin Data Set Register                  */
    uint32 CLR;           /**<  0x005C Pin Data Clr Register                  */
    uint32 ODR;           /**<  0x0060 Pin Open Drain Output Enable Register  */
    uint32 PD;            /**<  0x0064 Pin Pullup/Pulldown Disable Register   */
    uint32 PSL;           /**<  0x0068 Pin Pullup/Pulldown Selection Register */
} i2cBASE_t;


/** @def i2cREG1
*   @brief I2C Register Frame Pointer
*
*   This pointer is used by the I2C driver to access the I2C module registers.
*/
#define i2cREG1 ((i2cBASE_t *)0xFFF7D400U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @def i2cPORT1
*   @brief I2C GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of I2C
*   (use the GIO drivers to access the port pins).
*/
#define i2cPORT1 ((gioPORT_t *)0xFFF7D44CU)

/* USER CODE BEGIN (2) */
/* USER CODE END */


#endif
