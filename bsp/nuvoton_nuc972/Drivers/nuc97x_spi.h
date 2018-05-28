/*
 * File      : nuc970_spi.h
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */
#ifndef _NUC970_SPI_H_
#define _NUC970_SPI_H_

#include <stdint.h>

#include "nuc97x.h"
#include "nuc97x_gpio.h"
#include "nuc97x_interrupt.h"


/** @addtogroup NUC970_SPI_EXPORTED_CONSTANTS SPI Exported Constants
  @{
*/
/// @cond HIDDEN_SYMBOLS

#define SPI_REG_CNTRL   0x00    /*!< Control Register Address */
#define SPI_REG_DIVIDER 0x04    /*!< Divider Register Address */
#define SPI_REG_SSR     0x08    /*!< Slave Select Register Address */
#define SPI_REG_RX0     0x10    /*!< Receive Register 0 Address */
#define SPI_REG_RX1     0x14    /*!< Receive Register 1 Address */
#define SPI_REG_RX2     0x18    /*!< Receive Register 2 Address */
#define SPI_REG_RX3     0x1C    /*!< Receive Register 3 Address */
#define SPI_REG_TX0     0x10    /*!< Transfer Register 0 Address */
#define SPI_REG_TX1     0x14    /*!< Transfer Register 1 Address */
#define SPI_REG_TX2     0x18    /*!< Transfer Register 2 Address */
#define SPI_REG_TX3     0x1C    /*!< Transfer Register 3 Address */

#define SPI_NO_ERR      0   /*!< No error  */

#define SPI_ERR_NODEV   -1  /*!< Wrong device id  */
#define SPI_ERR_BUSY    -2  /*!< Interface is busy  */
#define SPI_ERR_IO      -3  /*!< IO control error for not opened interface  */
#define SPI_ERR_ARG     -4  /*!< Wrong argument in IO control  */

#define SPI_IOC_TRIGGER                 0   /*!< Trigger SPI interface */
#define SPI_IOC_SET_INTERRUPT           1   /*!< Enable/disable interrupt ,arguments could be \ref SPI_DISABLE_INTERRUPT and \ref SPI_ENABLE_INTERRUPT */
#define SPI_IOC_SET_SPEED               2   /*!< Set SPI clock speed */
#define SPI_IOC_SET_DUAL_QUAD_MODE      3   /*!< Enable/disable Quad/Dual mode ,arguments could be \ref SPI_DISABLE_DUAL_QUAD, \ref SPI_DUAL_MODE, \ref SPI_QUAD_MODE*/
#define SPI_IOC_SET_DUAL_QUAD_DIR       4   /*!< Set Quad/Dual mode direction ,arguments could be \ref SPI_DUAL_QUAD_INPUT, \ref SPI_DUAL_QUAD_OUTPUT */
#define SPI_IOC_SET_LSB_MSB             5   /*!< Set MSB/LSB ,arguments could be \ref SPI_MSB, \ref SPI_LSB */
#define SPI_IOC_SET_TX_NUM              6   /*!< Set transfer number */
#define SPI_IOC_SET_TX_BITLEN           7   /*!< Set transfer bit number */
#define SPI_IOC_SET_MODE                8   /*!< Set SPI mode ,arguments could be \ref SPI_MODE_0, \ref SPI_MODE_1, \ref SPI_MODE_2, \ref SPI_MODE_3 */
#define SPI_IOC_ENABLE_SS               9   /*!< Enable slave select pin */
#define SPI_IOC_DISABLE_SS              10  /*!< Disable slave select pin */
#define SPI_IOC_SET_AUTOSS              11  /*!< Enable/disable auto slave select function ,arguments could be \ref SPI_DISABLE_AUTOSS, \ref SPI_ENABLE_AUTOSS */
#define SPI_IOC_SET_SS_ACTIVE_LEVEL     12  /*!< Set slave select active level ,arguments could be \ref SPI_SS_ACTIVE_LOW, \ref SPI_SS_ACTIVE_HIGH */
#define SPI_IOC_CLR_INTERRUPT           13  /* Clear intrrupt flag */

#define SPI_DISABLE_INTERRUPT   0   /*!< Disable interrupt */
#define SPI_ENABLE_INTERRUPT    1   /*!< Enable interrupt */

#define SPI_DISABLE_DUAL_QUAD   0   /*!< Disable quad and dual mode */
#define SPI_DUAL_MODE           1   /*!< Enable dual mode */
#define SPI_QUAD_MODE           2   /*!< Enable quad mode */

#define SPI_DUAL_QUAD_INPUT     0   /*!< Set dual/quad mode io direction to input */
#define SPI_DUAL_QUAD_OUTPUT    1   /*!< Set dual/quad mode io direction to output */

#define SPI_MSB                 0   /*!< Enable MSB */
#define SPI_LSB                 1   /*!< Enable LSB */

#define SPI_MODE_0              0   /*!< Set to SPI mode 0 */
#define SPI_MODE_1              1   /*!< Set to SPI mode 1 */
#define SPI_MODE_2              2   /*!< Set to SPI mode 2 */
#define SPI_MODE_3              3   /*!< Set to SPI mode 3 */

#define SPI_SS_SS0              0   /*!< Select SS0 */
#define SPI_SS_SS1              1   /*!< Select SS1 */
#define SPI_SS_BOTH             2   /*!< Select both SS0/SS1 */

#define SPI_DISABLE_AUTOSS      0   /*!< Disable auto slave select function */
#define SPI_ENABLE_AUTOSS       1   /*!< Enable auto slave select function */

#define SPI_SS_ACTIVE_LOW       0   /*!< Set active level of slave select to low */
#define SPI_SS_ACTIVE_HIGH      1   /*!< Set active level of slave select to high */

#define SPI_INPUT_CLOCK         75000000        /* 75 000 KHz */


typedef struct
{
    __IO UINT32 CNTRL   ;    /*!< Control Register Address */
    __IO UINT32 DIVIDER ;    /*!< Divider Register Address */
    __IO UINT32 SSR     ;    /*!< Slave Select Register Address */
    __IO UINT32 RESV[1];
    __IO UINT32 TX0_RX0     ;    /*!< Receive Register 0 Address */
    __IO UINT32 TX1_RX1     ;    /*!< Receive Register 1 Address */
    __IO UINT32 TX2_RX2     ;    /*!< Receive Register 2 Address */
    __IO UINT32 TX3_RX3     ;    /*!< Receive Register 3 Address */
} SPI_TypeDef;

#define SPI0    ((SPI_TypeDef *)SPI0_BA)
#define SPI1    ((SPI_TypeDef *)SPI1_BA)

#define IS_SPI_ALL_PERIPH(PERIPH)  (((PERIPH) == SPI0) || \
                                      ((PERIPH) == SPI1)  )

struct nuc970_spi_cs
{
    GPIO_PORT  GPIOx;
    UINT32  PINx;
};

/*
 * Functions
 */
VOID    SPI_Init        (SPI_TypeDef* SPIx);
INT32   SPI_Control     (SPI_TypeDef* SPIx,UINT32 cmd, UINT32 arg);
INT32   SPI_GetBusy     (SPI_TypeDef* SPIx);
UINT32  SPI_Read        (SPI_TypeDef* SPIx,UINT8 buff_id);
VOID    SPI_Write       (SPI_TypeDef* SPIx,UINT8 buff_id,UINT32 dat);

#endif /* PLATFORM_NUC970_SPI_H_ */
