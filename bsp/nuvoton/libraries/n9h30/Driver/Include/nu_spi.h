/**************************************************************************//**
* @file     spi.h
* @brief    N9H30 SPI driver header file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NU_SPI_H__
#define __NU_SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_SPI_Driver SPI Driver
  @{
*/

/** @addtogroup N9H30_SPI_EXPORTED_CONSTANTS SPI Exported Constants
  @{
*/
/// @cond HIDDEN_SYMBOLS

#define CNTRL   0x00    /*!< Control Register Address */
#define DIVIDER 0x04    /*!< Divider Register Address */
#define SSR     0x08    /*!< Slave Select Register Address */
#define RX0     0x10    /*!< Receive Register 0 Address */
#define RX1     0x14    /*!< Receive Register 1 Address */
#define RX2     0x18    /*!< Receive Register 2 Address */
#define RX3     0x1C    /*!< Receive Register 3 Address */
#define TX0     0x10    /*!< Transfer Register 0 Address */
#define TX1     0x14    /*!< Transfer Register 1 Address */
#define TX2     0x18    /*!< Transfer Register 2 Address */
#define TX3     0x1C    /*!< Transfer Register 3 Address */

#define SPI_INPUT_CLOCK         (sysGetClock(SYS_PCLK)*1000000)        /* Unit: Hz */
/// @endcond HIDDEN_SYMBOLS

#define SPI_NUMBER  2       /*!< 2 spi interfaces  */

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

/*@}*/ /* end of group N9H30_SPI_EXPORTED_CONSTANTS */

/** @addtogroup N9H30_SPI_EXPORTED_FUNCTIONS SPI Exported Functions
  @{
*/

int32_t  spiInit(int32_t fd);
int32_t spiIoctl(int32_t fd, uint32_t cmd, uint32_t arg0, uint32_t arg1);
int spiOpen(int32_t fd);
uint8_t spiGetBusyStatus(int32_t fd);
uint32_t spiRead(int32_t fd, uint8_t buff_id);
void spiWrite(int32_t fd, uint8_t buff_id, uint32_t data);
/*@}*/ /* end of group N9H30_SPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_SPI_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_SPI_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
