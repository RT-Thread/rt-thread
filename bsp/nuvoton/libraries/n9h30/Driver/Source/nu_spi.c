/**************************************************************************//**
* @file     spi.c
* @brief    N9H30 SPI driver source file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
/* Header files */
#include <stdio.h>
#include <string.h>

#include "N9H30.h"
#include "nu_sys.h"
#include "nu_spi.h"
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

#define spi_out(dev, byte, addr)        outpw((dev)->base + addr, byte)
#define spi_in(dev, addr)               inpw((dev)->base + addr)

typedef struct
{
    uint32_t base;      /* spi bus number */
    uint8_t openflag;
    uint8_t intflag;
} spi_dev;

/// @endcond HIDDEN_SYMBOLS
/*@}*/ /* end of group N9H30_EMAC_EXPORTED_CONSTANTS */

/** @addtogroup N9H30_SPI_EXPORTED_FUNCTIONS SPI Exported Functions
  @{
*/
/// @cond HIDDEN_SYMBOLS

static spi_dev spi_device[SPI_NUMBER];

#if 0
/**
  * @brief  SPI-0 Interrupt handler
  * @param None
  * @return None
  */
static void spi0ISR(void)
{
    // clear interrupt flag
    outpw(REG_SPI0_CNTRL, spi_in((spi_dev *)((uint32_t)&spi_device[0]), CNTRL) | 0x1 << 16);
    spi_device[0].intflag = 1;
}

/**
  * @brief  SPI-1 Interrupt handler
  * @param None
  * @return None
  */
static void spi1ISR(void)
{
    // clear interrupt flag
    outpw(REG_SPI1_CNTRL, spi_in((spi_dev *)((uint32_t)&spi_device[1]), CNTRL) | 0x1 << 16);
    spi_device[1].intflag = 1;
}
#endif

/**
  * @brief  Set SPI divider
  * @param[in] dev pointer to spi interface structure
  * @param[in] speed desire spi speed
  * @return speed set actually
  */
static uint32_t spiSetSpeed(spi_dev *dev, uint32_t speed)
{
    uint16_t div = (uint16_t)(SPI_INPUT_CLOCK / (2 * speed)) - 1;

    spi_out(dev, div, DIVIDER);
    return (SPI_INPUT_CLOCK / (2 * (div + 1)));
}

/// @endcond /* HIDDEN_SYMBOLS */

/**
  * @brief Initialize spi interface and install interrupt callback function
  * @return always 0.
  * @retval 0 Success.
  */
int32_t  spiInit(int32_t fd)
{
#if 0
    if (fd == 0)
    {
        sysInstallISR(IRQ_LEVEL_1, SPI0_IRQn, (PVOID)spi0ISR);
        sysEnableInterrupt(SPI0_IRQn);
        memset((void *)&spi_device[0], 0, sizeof(spi_dev));
    }
    else
    {
        sysInstallISR(IRQ_LEVEL_1, SPI1_IRQn, (PVOID)spi1ISR);
        sysEnableInterrupt(SPI1_IRQn);
        memset((void *)&spi_device[1], 0, sizeof(spi_dev));
    }

    sysSetLocalInterrupt(ENABLE_IRQ);
#endif

    return (0);
}

/**
  * @brief Support some spi driver commands for application.
  * @param[in] fd is interface number.
  * @param[in] cmd is command.
  * @param[in] arg0 is the first argument of command.
  * @param[in] arg1 is the second argument of command.
  * @return command status.
  * @retval 0 Success otherwise fail. Fail value could be
  *                                    - \ref SPI_ERR_NODEV
  *                                    - \ref SPI_ERR_IO
  *                                    - \ref SPI_ERR_ARG
  */
int32_t spiIoctl(int32_t fd, uint32_t cmd, uint32_t arg0, uint32_t arg1)
{
    spi_dev *dev;

    if (fd != 0 && fd != 1)
        return (SPI_ERR_NODEV);

    dev = (spi_dev *)((uint32_t)&spi_device[fd]);
    if (dev->openflag == 0)
        return (SPI_ERR_IO);

    switch (cmd)
    {
    case SPI_IOC_TRIGGER:
        dev->intflag = 0;
        spi_out(dev, spi_in(dev, CNTRL) | 0x1, CNTRL);
        break;

#if 0
    case SPI_IOC_SET_INTERRUPT:
        if (arg0 == SPI_ENABLE_INTERRUPT)
            spi_out(dev, spi_in(dev, CNTRL) | (0x1 << 17), CNTRL);
        else
            spi_out(dev, spi_in(dev, CNTRL) & ~(0x1 << 17), CNTRL);
        break;
#endif

    case SPI_IOC_SET_SPEED:
        return spiSetSpeed(dev, (uint32_t)arg0);

    case SPI_IOC_SET_DUAL_QUAD_MODE:
        if (arg0 == SPI_DISABLE_DUAL_QUAD)
        {
            spi_out(dev, (spi_in(dev, CNTRL) & ~(0x3 << 21)), CNTRL);
            break;
        }

        if (arg0 == SPI_DUAL_MODE)
            spi_out(dev, (spi_in(dev, CNTRL) & ~(0x3 << 21)) | (0x1 << 22), CNTRL);
        else
            spi_out(dev, (spi_in(dev, CNTRL) & ~(0x3 << 21)) | (0x1 << 21), CNTRL);
        break;

    case SPI_IOC_SET_DUAL_QUAD_DIR:
        if (arg0 == SPI_DUAL_QUAD_INPUT)
            spi_out(dev, spi_in(dev, CNTRL) & ~(0x1 << 20), CNTRL);
        else
            spi_out(dev, spi_in(dev, CNTRL) | (0x1 << 20), CNTRL);
        break;

    case SPI_IOC_SET_LSB_MSB:
        if (arg0 == SPI_MSB)
            spi_out(dev, spi_in(dev, CNTRL) & ~(0x1 << 10), CNTRL);
        else
            spi_out(dev, spi_in(dev, CNTRL) | (0x1 << 10), CNTRL);
        break;

    case SPI_IOC_SET_TX_NUM:
        if (arg0 < 4)
            spi_out(dev, (spi_in(dev, CNTRL) & ~(0x3 << 8)) | (arg0 << 8), CNTRL);
        else
            return SPI_ERR_ARG;
        break;

    case SPI_IOC_SET_TX_BITLEN:
        if (arg0 < 32)
            spi_out(dev, (spi_in(dev, CNTRL) & ~(0x1f << 3)) | (arg0 << 3), CNTRL);
        else
            return SPI_ERR_ARG;
        break;

    case SPI_IOC_SET_MODE:
        if (arg0 > SPI_MODE_3)
            return SPI_ERR_ARG;

        if (arg0 == SPI_MODE_0)
            spi_out(dev, (spi_in(dev, CNTRL) & ~((0x3 << 1) | (1UL << 31))) | (1 << 2), CNTRL);
        else if (arg0 == SPI_MODE_1)
            spi_out(dev, (spi_in(dev, CNTRL) & ~((0x3 << 1) | (1UL << 31))) | (1 << 1), CNTRL);
        else if (arg0 == SPI_MODE_2)
            spi_out(dev, (spi_in(dev, CNTRL) & ~((0x3 << 1) | (1UL << 31))) | ((1UL << 31) | (1 << 2)), CNTRL);
        else
            spi_out(dev, (spi_in(dev, CNTRL) & ~((0x3 << 1) | (1UL << 31))) | ((1UL << 31) | (1 << 1)), CNTRL);
        break;

    case SPI_IOC_ENABLE_SS:
        if (arg0 == SPI_SS_SS0)
            spi_out(dev, (spi_in(dev, SSR) & ~(0x3)) | 0x1, SSR);
        else if (arg0 == SPI_SS_SS1)
            spi_out(dev, (spi_in(dev, SSR) & ~(0x3)) | 0x2, SSR);
        else if (arg0 == SPI_SS_BOTH)
            spi_out(dev, (spi_in(dev, SSR) & ~(0x3)) | 0x3, SSR);
        else
            return SPI_ERR_ARG;
        break;

    case SPI_IOC_DISABLE_SS:
        if (arg0 == SPI_SS_SS0)
            spi_out(dev, (spi_in(dev, SSR) & ~(0x1)), SSR);
        else if (arg0 == SPI_SS_SS1)
            spi_out(dev, (spi_in(dev, SSR) & ~(0x2)), SSR);
        else if (arg0 == SPI_SS_BOTH)
            spi_out(dev, (spi_in(dev, SSR) & ~(0x3)), SSR);
        else
            return SPI_ERR_ARG;
        break;

    case SPI_IOC_SET_AUTOSS:
        if (arg0 == SPI_DISABLE_AUTOSS)
            spi_out(dev, spi_in(dev, SSR) & ~(0x1 << 3), SSR);
        else
            spi_out(dev, spi_in(dev, SSR) | (0x1 << 3), SSR);
        break;

    case SPI_IOC_SET_SS_ACTIVE_LEVEL:
        if (arg0 == SPI_SS_ACTIVE_LOW)
            spi_out(dev, spi_in(dev, SSR) & ~(0x1 << 2), SSR);
        else
            spi_out(dev, spi_in(dev, SSR) | (0x1 << 2), SSR);
    default:
        break;
    }

    return 0;
}

/**
  * @brief Open spi interface and initialize some variables
  * @param[in] fd is interface number.
  * @return always 0
  * @retval 0 success.
  */
int spiOpen(int32_t fd)
{
    spi_dev *dev;

    if ((uint32_t)fd >= SPI_NUMBER)
        return SPI_ERR_NODEV;

    dev = (spi_dev *)((uint32_t)&spi_device[fd]);

    if (dev->openflag != 0)         /* a card slot can open only once */
        return (SPI_ERR_BUSY);

    memset(dev, 0, sizeof(spi_dev));
    dev->base = ((uint32_t)fd) ? SPI1_BA : SPI0_BA;
    dev->openflag = 1;
    dev->intflag = 0;

    return 0;
}

/**
  * @brief Get busy status of spi interface
  * @param[in] fd is interface number.
  * @return busy or not
  * @retval 0 not busy.
  * @retval 1 busy.
  */
uint8_t spiGetBusyStatus(int32_t fd)
{
    spi_dev *dev;

    dev = (spi_dev *)((uint32_t)&spi_device[fd]);

    if (spi_in(dev, CNTRL) & (0x1 << 17))
        return (!dev->intflag);
    else
        return ((spi_in(dev, CNTRL) & 0x1) == 0x1 ? 1 : 0);
}

/**
  * @brief Read data form spi interface
  * @param[in] fd is interface number.
  * @param[in] buff_id is buffer number. If transfer number is 4, application needs read 4 times (buff_id is from 0 to 3) from buffer.
  * @return data
  */
uint32_t spiRead(int32_t fd, uint8_t buff_id)
{
    spi_dev *dev;

    dev = (spi_dev *)((uint32_t)&spi_device[fd]);
    return spi_in(dev, (RX0 + 4 * buff_id));
}

/**
  * @brief Write data to spi interface
  * @param[in] fd is interface number.
  * @param[in] buff_id is buffer number. If transfer number is 4, application needs write 4 times (buff_id is from 0 to 3) to buffer.
  * @param[in] data is data to be written.
  * @return none
  */
void spiWrite(int32_t fd, uint8_t buff_id, uint32_t data)
{
    spi_dev *dev;

    dev = (spi_dev *)((uint32_t)&spi_device[fd]);
    spi_out(dev, data, (TX0 + 4 * buff_id));
}

/*@}*/ /* end of group N9H30_SPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_SPI_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
