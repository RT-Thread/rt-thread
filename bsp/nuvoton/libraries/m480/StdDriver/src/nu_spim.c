/**************************************************************************//**
 * @file    spim.c
 * @version V1.00
 * @brief   M480 series SPIM driver
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SPIM_Driver SPIM Driver
  @{
*/

/** @addtogroup SPIM_EXPORTED_FUNCTIONS SPIM Exported Functions
  @{
*/


/** @cond HIDDEN_SYMBOLS */


#define ENABLE_DEBUG    0

#if ENABLE_DEBUG
#define SPIM_DBGMSG   printf
#else
#define SPIM_DBGMSG(...)   do { } while (0)      /* disable debug */
#endif

static volatile uint8_t  g_Supported_List[] =
{
    MFGID_WINBOND,
    MFGID_MXIC,
    MFGID_EON,
    MFGID_ISSI,
    MFGID_SPANSION
};

static void  N_delay(int n);
static void SwitchNBitOutput(uint32_t u32NBit);
static void SwitchNBitInput(uint32_t u32NBit);
static void spim_write(uint8_t pu8TxBuf[], uint32_t u32NTx);
static void spim_read(uint8_t pu8RxBuf[], uint32_t u32NRx);
static void SPIM_WriteStatusRegister(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit);
static void SPIM_ReadStatusRegister(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit);
static void SPIM_ReadStatusRegister2(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit);
static void SPIM_WriteStatusRegister2(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit);
static void SPIM_ReadStatusRegister3(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit);
static void SPIM_ReadSecurityRegister(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit);
static int spim_is_write_done(uint32_t u32NBit);
static int spim_wait_write_done(uint32_t u32NBit);
static void spim_set_write_enable(int isEn, uint32_t u32NBit);
static void spim_enable_spansion_quad_mode(int isEn);
static void spim_eon_set_qpi_mode(int isEn);
static void SPIM_SPANSION_4Bytes_Enable(int isEn, uint32_t u32NBit);
static void SPIM_WriteInPageDataByIo(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NTx, uint8_t pu8TxBuf[], uint8_t wrCmd,
                                     uint32_t u32NBitCmd, uint32_t u32NBitAddr, uint32_t u32NBitDat, int isSync);
static void SPIM_WriteInPageDataByPageWrite(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NTx,
        uint8_t pu8TxBuf[], uint32_t wrCmd, int isSync);


static void  N_delay(int n)
{
    while (n-- > 0)
    {
        __NOP();
    }
}

static void SwitchNBitOutput(uint32_t u32NBit)
{
    switch (u32NBit)
    {
    case 1UL:
        SPIM_ENABLE_SING_OUTPUT_MODE();     /* 1-bit, Output. */
        break;

    case 2UL:
        SPIM_ENABLE_DUAL_OUTPUT_MODE();     /* 2-bit, Output. */
        break;

    case 4UL:
        SPIM_ENABLE_QUAD_OUTPUT_MODE();     /* 4-bit, Output. */
        break;

    default:
        break;
    }
}

static void SwitchNBitInput(uint32_t u32NBit)
{
    switch (u32NBit)
    {
    case 1UL:
        SPIM_ENABLE_SING_INPUT_MODE();      /* 1-bit, Input.  */
        break;

    case 2UL:
        SPIM_ENABLE_DUAL_INPUT_MODE();      /* 2-bit, Input.  */
        break;

    case 4UL:
        SPIM_ENABLE_QUAD_INPUT_MODE();      /* 4-bit, Input.  */
        break;

    default:
        break;
    }
}


/**
  * @brief      Write data to SPI slave.
  * @param      pu8TxBuf    Transmit buffer.
  * @param      u32NTx      Number of bytes to transmit.
  * @return     None.
  */
static void spim_write(uint8_t pu8TxBuf[], uint32_t u32NTx)
{
    uint32_t  buf_idx = 0UL;

    while (u32NTx)
    {
        uint32_t dataNum = 0UL, dataNum2;

        if (u32NTx >= 16UL)
        {
            dataNum = 4UL;
        }
        else if (u32NTx >= 12UL)
        {
            dataNum = 3UL;
        }
        else if (u32NTx >= 8UL)
        {
            dataNum = 2UL;
        }
        else if (u32NTx >= 4UL)
        {
            dataNum = 1UL;
        }

        dataNum2 = dataNum;
        while (dataNum2)
        {
            uint32_t tmp;

            memcpy(&tmp, &pu8TxBuf[buf_idx], 4U);
            buf_idx += 4UL;
            u32NTx -= 4UL;

            dataNum2 --;
            /*  *((__O uint32_t *) &SPIM->TX0 + dataNum2) = tmp; */
            SPIM->TX[dataNum2] = tmp;
        }

        if (dataNum)
        {
            SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_IO);    /* Switch to Normal mode. */
            SPIM_SET_DATA_WIDTH(32UL);
            SPIM_SET_DATA_NUM(dataNum);
            SPIM_SET_GO();
            SPIM_WAIT_FREE();
        }

        if (u32NTx && (u32NTx < 4UL))
        {
            uint32_t  rnm, tmp;

            rnm = u32NTx;
            memcpy(&tmp, &pu8TxBuf[buf_idx], u32NTx);
            buf_idx += u32NTx;
            u32NTx = 0UL;
            SPIM->TX[0] = tmp;

            SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_IO);    /* Switch to Normal mode. */
            SPIM_SET_DATA_WIDTH(rnm * 8UL);
            SPIM_SET_DATA_NUM(1UL);
            SPIM_SET_GO();
            SPIM_WAIT_FREE();
        }
    }
}

/**
  * @brief      Read data from SPI slave.
  * @param      pu8TxBuf    Receive buffer.
  * @param      u32NRx      Size of receive buffer in bytes.
  * @return     None.
  */
static void spim_read(uint8_t pu8RxBuf[], uint32_t u32NRx)
{
    uint32_t  buf_idx = 0UL;

    while (u32NRx)
    {
        uint32_t dataNum = 0UL;   /* number of words */

        if (u32NRx >= 16UL)
        {
            dataNum = 4UL;
        }
        else if (u32NRx >= 12UL)
        {
            dataNum = 3UL;
        }
        else if (u32NRx >= 8UL)
        {
            dataNum = 2UL;
        }
        else if (u32NRx >= 4UL)
        {
            dataNum = 1UL;
        }

        if (dataNum)
        {
            SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_IO);    /* Switch to Normal mode. */
            SPIM_SET_DATA_WIDTH(32UL);
            SPIM_SET_DATA_NUM(dataNum);
            SPIM_SET_GO();
            SPIM_WAIT_FREE();
        }

        while (dataNum)
        {
            uint32_t tmp;

            tmp = SPIM->RX[dataNum-1UL];
            memcpy(&pu8RxBuf[buf_idx], &tmp, 4U);
            buf_idx += 4UL;
            dataNum --;
            u32NRx -= 4UL;
        }

        if (u32NRx && (u32NRx < 4UL))
        {
            uint32_t tmp;

            SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_IO);    /* Switch to Normal mode. */
            SPIM_SET_DATA_WIDTH(u32NRx * 8UL);
            SPIM_SET_DATA_NUM(1UL);
            SPIM_SET_GO();
            SPIM_WAIT_FREE();

            tmp = SPIM->RX[0];
            memcpy(&pu8RxBuf[buf_idx], &tmp, u32NRx);
            buf_idx += u32NRx;
            u32NRx = 0UL;
        }
    }
}

/**
  * @brief      Issue Read Status Register #1 command.
  * @param      dataBuf     Receive buffer.
  * @param      u32NRx      Size of receive buffer.
 * @param       u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_ReadStatusRegister(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_RDSR};            /* 1-byte Read Status Register #1 command. */

    SPIM_SET_SS_EN(1);                          /* CS activated. */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SwitchNBitInput(u32NBit);
    spim_read(dataBuf, u32NRx);
    SPIM_SET_SS_EN(0);                          /* CS deactivated. */
}

/**
  * @brief      Issue Write Status Register #1 command.
  * @param      dataBuf     Transmit buffer.
  * @param      u32NTx      Size of transmit buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_WriteStatusRegister(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_WRSR, 0x00U};     /* 1-byte Write Status Register #1 command + 1-byte data. */

    cmdBuf[1] = dataBuf[0];
    SPIM_SET_SS_EN(1);                          /* CS activated. */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated. */
}

/**
  * @brief      Issue Read Status Register #2 command.
  * @param      dataBuf     Receive buffer.
  * @param      u32NRx      Size of receive buffer.
 * @param       u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_ReadStatusRegister2(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_RDSR2};           /* 1-byte Read Status Register #1 command. */

    SPIM_SET_SS_EN(1);                          /* CS activated.  */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SwitchNBitInput(u32NBit);
    spim_read(dataBuf, u32NRx);
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */
}

/**
  * @brief      Issue Winbond Write Status Register command. This command write both Status Register-1
  *             and Status Register-2.
  * @param      dataBuf     Transmit buffer.
  * @param      u32NTx      Size of transmit buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_WriteStatusRegister2(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit)
{
    uint8_t cmdBuf[3] = {OPCODE_WRSR, 0U, 0U};

    cmdBuf[1] = dataBuf[0];
    cmdBuf[2] = dataBuf[1];

    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */
}

#if 0  /* not used */
/**
  * @brief      Issue Write Status Register #3 command.
  * @param      dataBuf     Transmit buffer.
  * @param      u32NTx      Size of transmit buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_WriteStatusRegister3(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_WRSR3, 0x00U};    /* 1-byte Write Status Register #2 command + 1-byte data. */
    cmdBuf[1] = dataBuf[0];

    SPIM_SET_SS_EN(1);                          /* CS activated. */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated. */
}
#endif

/**
  * @brief      Issue Read Status Register #3 command.
  * @param      dataBuf     Receive buffer.
  * @param      u32NRx      Size of receive buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_ReadStatusRegister3(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_RDSR3};           /* 1-byte Read Status Register #1 command. */

    SPIM_SET_SS_EN(1);                          /* CS activated. */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SwitchNBitInput(u32NBit);
    spim_read(dataBuf, u32NRx);
    SPIM_SET_SS_EN(0);                          /* CS deactivated. */
}

#if 0  /* not used */
/**
  * @brief      Issue Write Security Register command.
  * @param      dataBuf     Transmit buffer.
  * @param      u32NTx      Size of transmit buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_WriteSecurityRegister(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_WRSCUR, 0x00U};   /* 1-byte Write Status Register #2 command + 1-byte data. */
    cmdBuf[1] = dataBuf[0];

    SPIM_SET_SS_EN(1);                          /* CS activated. */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated. */
}
#endif

/**
  * @brief      Issue Read Security Register command.
  * @param      dataBuf     Receive buffer.
  * @param      u32NRx      Size of receive buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_ReadSecurityRegister(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_RDSCUR};          /* 1-byte Read Status Register #1 command. */

    SPIM_SET_SS_EN(1);                          /* CS activated. */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SwitchNBitInput(u32NBit);
    spim_read(dataBuf, u32NRx);
    SPIM_SET_SS_EN(0);                          /* CS deactivated. */
}

/**
  * @brief      Check if Erase/Write is done.
  * @return     0: Not done. 1: Done.
  */
static int spim_is_write_done(uint32_t u32NBit)
{
    uint8_t status[1];
    SPIM_ReadStatusRegister(status, sizeof (status), u32NBit);
    return ! (status[0] & SR_WIP);
}

/**
  * @brief      Wait until Erase/Write done.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     0           SPIM write done.
  */
static int spim_wait_write_done(uint32_t u32NBit)
{
    uint32_t   count;
    int        ret = -1;

    for (count = 0UL; count < SystemCoreClock/1000UL; count++)
    {
        if (spim_is_write_done(u32NBit))
        {
            ret = 0;
            break;
        }
    }
    if (ret != 0)
    {
        SPIM_DBGMSG("spim_wait_write_done time-out!!\n");
    }
    return ret;
}

/**
  * @brief      Issue Write Enable/disable command.
  * @param      isEn        Enable/disable.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void spim_set_write_enable(int isEn, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {0U};                     /* 1-byte Write Enable command. */
    cmdBuf[0] = isEn ? OPCODE_WREN : OPCODE_WRDI;

    SPIM_SET_SS_EN(1);                          /* CS activated.   */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */
}

/** @endcond HIDDEN_SYMBOLS */

/**
  * @brief      Get SPIM serial clock.
  * @return     SPI serial clock.
  * @details    This function calculates the serial clock of SPI in Hz.
  */
uint32_t SPIM_GetSClkFreq(void)
{
    uint32_t clkDiv = SPIM_GET_CLOCK_DIVIDER();

    return clkDiv ? SystemCoreClock / (clkDiv * 2U) : SystemCoreClock;
}

/**
  * @brief      Initialize SPIM flash.
  * @param      clrWP       Clear Write Protect or not.
  * @return     0    Success.
  * @return     -1   Unrecognized manufacture ID or failed on reading manufacture ID.
  */
int SPIM_InitFlash(int clrWP)
{
    uint8_t   idBuf[3];
    uint8_t   cmdBuf[1];
    uint32_t  i;
    int32_t   ret = -1;

    SPIM_SET_SS_ACTLVL(0);

    /*
     * Because not sure in SPI or QPI mode, do QPI reset and then SPI reset.
     */
    /* QPI Reset Enable */
    cmdBuf[0] = OPCODE_RSTEN;
    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SPIM_ENABLE_QUAD_OUTPUT_MODE();             /* 1-bit, Output.   */
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    /* QPI Reset */
    cmdBuf[0] = OPCODE_RST;
    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SPIM_ENABLE_QUAD_OUTPUT_MODE();             /* 1-bit, Output.   */
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    /* SPI ResetEnable */
    cmdBuf[0] = OPCODE_RSTEN;
    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SPIM_ENABLE_SING_OUTPUT_MODE();             /* 1-bit, Output.   */
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    /* SPI Reset */
    cmdBuf[0] = OPCODE_RST;
    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SPIM_ENABLE_SING_OUTPUT_MODE();             /* 1-bit, Output.   */
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    if (clrWP)
    {
        uint8_t dataBuf[] = {0x00U};

        spim_set_write_enable(1, 1UL);           /* Clear Block Protect. */
        SPIM_WriteStatusRegister(dataBuf, sizeof (dataBuf), 1U);
        spim_wait_write_done(1UL);
    }

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), 1UL);

    /* printf("ID: 0x%x, 0x%x, px%x\n", idBuf[0], idBuf[1], idBuf[2]); */

    for (i = 0UL; i < sizeof(g_Supported_List)/sizeof(g_Supported_List[0]); i++)
    {
        if (idBuf[0] == g_Supported_List[i])
        {
            ret = 0;
        }
    }
    if (ret != 0)
    {
        SPIM_DBGMSG("Flash initialize failed!! 0x%x\n", idBuf[0]);
    }
    return ret;
}

/**
  * @brief      Issue JEDEC ID command.
  * @param      idBuf       ID buffer.
  * @param      u32NRx      Size of ID buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
void SPIM_ReadJedecId(uint8_t idBuf[], uint32_t u32NRx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = { OPCODE_RDID };          /* 1-byte JEDEC ID command.  */

    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SwitchNBitInput(u32NBit);
    spim_read(idBuf, u32NRx);
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */
}

/** @cond HIDDEN_SYMBOLS */

static void spim_enable_spansion_quad_mode(int isEn)
{
    uint8_t cmdBuf[3];
    uint8_t dataBuf[1], status1;

    cmdBuf[0] = 0x5U;                            /* Read Status Register-1 */

    SPIM_SET_SS_EN(1);
    SwitchNBitOutput(1UL);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SwitchNBitInput(1UL);
    spim_read(dataBuf, sizeof (dataBuf));
    SPIM_SET_SS_EN(0);
    /* SPIM_DBGMSG("SR1 = 0x%x\n", dataBuf[0]); */

    status1 = dataBuf[0];

    cmdBuf[0] = 0x35U;                           /* Read Configuration Register-1 */

    SPIM_SET_SS_EN(1);
    SwitchNBitOutput(1UL);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SwitchNBitInput(1UL);
    spim_read(dataBuf, sizeof (dataBuf));
    SPIM_SET_SS_EN(0);
    /* SPIM_DBGMSG("CR1 = 0x%x\n", dataBuf[0]); */

    spim_set_write_enable(1, 1UL);

    cmdBuf[0] =  0x1U;                           /* Write register   */
    cmdBuf[1] =  status1;

    if (isEn)
    {
        cmdBuf[2] = dataBuf[0] | 0x2U;           /* set QUAD         */
    }
    else
    {
        cmdBuf[2] = dataBuf[0] & ~0x2U;          /* clear QUAD       */
    }

    SPIM_SET_SS_EN(1);
    SwitchNBitOutput(1UL);
    spim_write(cmdBuf, 3UL);
    SPIM_SET_SS_EN(0);

    spim_set_write_enable(0, 1UL);


    cmdBuf[0] = 0x35U;                           /* Read Configuration Register-1 */

    SPIM_SET_SS_EN(1);
    SwitchNBitOutput(1UL);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SwitchNBitInput(1UL);
    spim_read(dataBuf, sizeof (dataBuf));
    SPIM_SET_SS_EN(0);

    /* SPIM_DBGMSG("CR1 = 0x%x\n", dataBuf[0]); */
    N_delay(10000);
}

/** @endcond HIDDEN_SYMBOLS */

/**
  * @brief      Set Quad Enable/disable.
  * @param      isEn        Enable/disable.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
void SPIM_SetQuadEnable(int isEn, uint32_t u32NBit)
{
    uint8_t  idBuf[3];
    uint8_t  dataBuf[2];

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), u32NBit);

    SPIM_DBGMSG("SPIM_SetQuadEnable - Flash ID is 0x%x\n", idBuf[0]);

    switch (idBuf[0])
    {
    case MFGID_WINBOND:                      /* Winbond SPI flash  */
        SPIM_ReadStatusRegister(&dataBuf[0], 1UL, u32NBit);
        SPIM_ReadStatusRegister2(&dataBuf[1], 1UL, u32NBit);
        SPIM_DBGMSG("Status Register: 0x%x - 0x%x\n", dataBuf[0], dataBuf[1]);
        if (isEn)
        {
            dataBuf[1] |= SR2_QE;
        }
        else
        {
            dataBuf[1] &= ~SR2_QE;
        }

        spim_set_write_enable(1, u32NBit);   /* Write Enable.    */
        SPIM_WriteStatusRegister2(dataBuf, sizeof (dataBuf), u32NBit);
        spim_wait_write_done(u32NBit);

        SPIM_ReadStatusRegister(&dataBuf[0], 1UL, u32NBit);
        SPIM_ReadStatusRegister2(&dataBuf[1], 1UL, u32NBit);
        SPIM_DBGMSG("Status Register: 0x%x - 0x%x\n", dataBuf[0], dataBuf[1]);
        break;

    case MFGID_MXIC:                         /* MXIC SPI flash.  */
    case MFGID_EON:
    case MFGID_ISSI:                         /* ISSI SPI flash.  */
        spim_set_write_enable(1, u32NBit);   /* Write Enable.    */
        dataBuf[0] = isEn ? SR_QE : 0U;
        SPIM_WriteStatusRegister(dataBuf, sizeof (dataBuf), u32NBit);
        spim_wait_write_done(u32NBit);
        break;

    case MFGID_SPANSION:
        spim_enable_spansion_quad_mode(isEn);
        break;

    default:
        break;
    }
}

/**
  * @brief      Enter/exit QPI mode.
  * @param      isEn        Enable/disable.
  * @return     None.
  */
static void spim_eon_set_qpi_mode(int isEn)
{
    uint8_t cmdBuf[1];                           /* 1-byte command.  */

    uint8_t status[1];
    SPIM_ReadStatusRegister(status, sizeof (status), 1UL);
    SPIM_DBGMSG("Status: 0x%x\n", status[0]);

    if (isEn)                                    /* Assume in SPI mode. */
    {
        cmdBuf[0] = OPCODE_ENQPI;

        SPIM_SET_SS_EN(1);                      /* CS activated.    */
        SwitchNBitOutput(1UL);
        spim_write(cmdBuf, sizeof (cmdBuf));
        SPIM_SET_SS_EN(0);                      /* CS deactivated.  */
    }
    else                                         /* Assume in QPI mode. */
    {
        cmdBuf[0] = OPCODE_EXQPI;

        SPIM_SET_SS_EN(1);                      /* CS activated.    */
        SwitchNBitOutput(4UL);
        spim_write(cmdBuf, sizeof (cmdBuf));
        SPIM_SET_SS_EN(0);                      /* CS deactivated.  */
    }

    SPIM_ReadStatusRegister(status, sizeof (status), 1UL);
    SPIM_DBGMSG("Status: 0x%x\n", status[0]);
}


static void SPIM_SPANSION_4Bytes_Enable(int isEn, uint32_t u32NBit)
{
    uint8_t cmdBuf[2];
    uint8_t dataBuf[1];

    cmdBuf[0] = OPCODE_BRRD;
    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, 1UL);
    SwitchNBitInput(1UL);
    spim_read(dataBuf, 1UL);
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    SPIM_DBGMSG("Bank Address register= 0x%x\n", dataBuf[0]);

    cmdBuf[0] =  OPCODE_BRWR;

    if (isEn)
    {
        cmdBuf[1] = dataBuf[0] | 0x80U;          /* set EXTADD       */
    }
    else
    {
        cmdBuf[1] = dataBuf[0] & ~0x80U;         /* clear EXTADD     */
    }

    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SwitchNBitOutput(1UL);
    spim_write(cmdBuf, 2UL);
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */
}

/** @cond HIDDEN_SYMBOLS */

/**
  * @brief      Query 4-byte address mode enabled or not.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     0: 4-byte address mode disabled. 1: 4-byte address mode enabled.
  */
int SPIM_Is4ByteModeEnable(uint32_t u32NBit)
{
    int  isEn = 0;
    int  isSupt = 0;
    uint8_t  idBuf[3];
    uint8_t  dataBuf[1];

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), u32NBit);

    /* Based on Flash size, check if 4-byte address mode is supported.  */
    switch (idBuf[0])
    {
    case MFGID_WINBOND:
    case MFGID_MXIC:
    case MFGID_EON:
        isSupt = (idBuf[2] < 0x19U) ? 0L : 1L;
        break;

    case MFGID_ISSI:
        isSupt = (idBuf[2] < 0x49U) ? 0L : 1L;
        break;

    default:
        break;
    }

    if (isSupt != 0)
    {
        if (idBuf[0] == MFGID_WINBOND)
        {
            /* Winbond SPI flash. */
            SPIM_ReadStatusRegister3(dataBuf, sizeof (dataBuf), u32NBit);
            isEn = !! (dataBuf[0] & SR3_ADR);
        }
        else if ((idBuf[0] == MFGID_MXIC) || (idBuf[0] ==MFGID_EON))
        {
            /* MXIC/EON SPI flash. */
            SPIM_ReadSecurityRegister(dataBuf, sizeof (dataBuf), u32NBit);
            isEn = !! (dataBuf[0] & SCUR_4BYTE);
        }
    }

    return isEn;
}

/** @endcond HIDDEN_SYMBOLS  */


/**
  * @brief      Enter/Exit 4-byte address mode.
  * @param      isEn        Enable/disable.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     0           success
  *             -1          failed
  */
int SPIM_Enable_4Bytes_Mode(int isEn, uint32_t u32NBit)
{
    int  isSupt = 0L, ret = -1;
    uint8_t idBuf[3];
    uint8_t cmdBuf[1];                           /* 1-byte Enter/Exit 4-Byte Mode command. */

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), u32NBit);

    /* Based on Flash size, check if 4-byte address mode is supported. */
    switch (idBuf[0])
    {
    case MFGID_WINBOND:
    case MFGID_MXIC:
    case MFGID_EON:
        isSupt = (idBuf[2] < 0x19U) ? 0L : 1L;
        break;

    case MFGID_ISSI:
        isSupt = (idBuf[2] < 0x49U) ? 0L : 1L;
        break;

    case MFGID_SPANSION:
        SPIM_SPANSION_4Bytes_Enable(isEn, u32NBit);
        isSupt = 1L;
        ret = 0L;
        break;

    default:
        break;
    }

    if ((isSupt) && (idBuf[0] != MFGID_SPANSION))
    {
        cmdBuf[0] = isEn ? OPCODE_EN4B : OPCODE_EX4B;

        SPIM_SET_SS_EN(1);                      /* CS activated.    */
        SwitchNBitOutput(u32NBit);
        spim_write(cmdBuf, sizeof (cmdBuf));
        SPIM_SET_SS_EN(0);                      /* CS deactivated.  */

        /*
         * FIXME: Per test, 4BYTE Indicator bit doesn't set after EN4B, which
         * doesn't match spec(MX25L25635E), so skip the check below.
         */
        if (idBuf[0] != MFGID_MXIC)
        {
            if (isEn)
            {
                while (! SPIM_Is4ByteModeEnable(u32NBit)) { }
            }
            else
            {
                while (SPIM_Is4ByteModeEnable(u32NBit)) { }
            }
        }
        ret = 0;
    }
    return ret;
}


void SPIM_WinbondUnlock(uint32_t u32NBit)
{
    uint8_t   idBuf[3];
    uint8_t   dataBuf[4];

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), u32NBit);

    if ((idBuf[0] != MFGID_WINBOND) || (idBuf[1] != 0x40) || (idBuf[2] != 0x16))
    {
        SPIM_DBGMSG("SPIM_WinbondUnlock - Not W25Q32, do nothing.\n");
        return;
    }

    SPIM_ReadStatusRegister(&dataBuf[0], 1UL, u32NBit);
    SPIM_ReadStatusRegister2(&dataBuf[1], 1UL, u32NBit);
    SPIM_DBGMSG("Status Register: 0x%x - 0x%x\n", dataBuf[0], dataBuf[1]);
    dataBuf[1] &= ~0x40;    /* clear Status Register-1 SEC bit */

    spim_set_write_enable(1, u32NBit);   /* Write Enable.    */
    SPIM_WriteStatusRegister2(dataBuf, sizeof (dataBuf), u32NBit);
    spim_wait_write_done(u32NBit);

    SPIM_ReadStatusRegister(&dataBuf[0], 1UL, u32NBit);
    SPIM_ReadStatusRegister2(&dataBuf[1], 1UL, u32NBit);
    SPIM_DBGMSG("Status Register (after unlock): 0x%x - 0x%x\n", dataBuf[0], dataBuf[1]);
}

/**
  * @brief      Erase whole chip.
  * @param      u32NBit     N-bit transmit/receive.
  * @param      isSync      Block or not.
  * @return     None.
  */
void SPIM_ChipErase(uint32_t u32NBit, int isSync)
{
    uint8_t cmdBuf[] = { OPCODE_CHIP_ERASE };    /* 1-byte Chip Erase command. */

    spim_set_write_enable(1, u32NBit);           /* Write Enable.    */

    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    if (isSync)
    {
        spim_wait_write_done(u32NBit);
    }
}


/**
  * @brief      Erase one block.
  * @param      u32Addr         Block to erase which contains the u32Addr.
  * @param      is4ByteAddr     4-byte u32Address or not.
  * @param      u8ErsCmd        Erase command.
  * @param      u32NBit         N-bit transmit/receive.
  * @param      isSync      Block or not.
  * @return     None.
  */
void SPIM_EraseBlock(uint32_t u32Addr, int is4ByteAddr, uint8_t u8ErsCmd, uint32_t u32NBit, int isSync)
{
    uint8_t  cmdBuf[16];
    uint32_t  buf_idx = 0UL;

    spim_set_write_enable(1, u32NBit);           /* Write Enable.    */

    cmdBuf[buf_idx++] = u8ErsCmd;

    if (is4ByteAddr)
    {
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 24);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 16);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 8);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr & 0xFFUL);
    }
    else
    {
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 16);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 8);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr & 0xFFUL);
    }

    SPIM_SET_SS_EN(1);                      /* CS activated.    */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, buf_idx);
    SPIM_SET_SS_EN(0);                      /* CS deactivated.  */

    if (isSync)
    {
        spim_wait_write_done(u32NBit);
    }
}


/** @cond HIDDEN_SYMBOLS */

/**
  * @brief      Write data in the same page by I/O mode.
  * @param      u32Addr     Start u32Address to write.
  * @param      is4ByteAddr 4-byte u32Address or not.
  * @param      u32NTx      Number of bytes to write.
  * @param      pu8TxBuf    Transmit buffer.
  * @param      wrCmd       Write command.
  * @param      u32NBitCmd  N-bit transmit command.
  * @param      u32NBitAddr N-bit transmit u32Address.
  * @param      u32NBitDat  N-bit transmit/receive data.
  * @param      isSync      Block or not.
  * @return     None.
  */
static void SPIM_WriteInPageDataByIo(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NTx, uint8_t pu8TxBuf[], uint8_t wrCmd,
                                     uint32_t u32NBitCmd, uint32_t u32NBitAddr, uint32_t u32NBitDat, int isSync)
{
    uint8_t   cmdBuf[16];
    uint32_t  buf_idx;

    spim_set_write_enable(1, u32NBitCmd);        /* Write Enable.    */

    SPIM_SET_SS_EN(1);                          /* CS activated.    */

    SwitchNBitOutput(u32NBitCmd);
    cmdBuf[0] = wrCmd;
    spim_write(cmdBuf, 1UL);                     /* Write out command. */

    buf_idx = 0UL;
    if (is4ByteAddr)
    {
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 24);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 16);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 8);
        cmdBuf[buf_idx++] = (uint8_t) u32Addr;
    }
    else
    {
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 16);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 8);
        cmdBuf[buf_idx++] = (uint8_t) u32Addr;
    }

    SwitchNBitOutput(u32NBitAddr);
    spim_write(cmdBuf, buf_idx);                 /* Write out u32Address. */

    SwitchNBitOutput(u32NBitDat);
    spim_write(pu8TxBuf, u32NTx);                /* Write out data.  */

    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    if (isSync)
    {
        spim_wait_write_done(u32NBitCmd);
    }
}

/**
  * @brief      Write data in the same page by Page Write mode.
  * @param      u32Addr     Start u32Address to write.
  * @param      is4ByteAddr 4-byte u32Address or not.
  * @param      u32NTx      Number of bytes to write.
  * @param      pu8TxBuf    Transmit buffer.
  * @param      wrCmd       Write command.
  * @param      isSync      Block or not.
  * @return     None.
  */
static void SPIM_WriteInPageDataByPageWrite(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NTx,
        uint8_t pu8TxBuf[], uint32_t wrCmd, int isSync)
{
    if ((wrCmd == CMD_QUAD_PAGE_PROGRAM_WINBOND) ||
            (wrCmd == CMD_QUAD_PAGE_PROGRAM_MXIC))
    {
        SPIM_SetQuadEnable(1, 1UL);              /* Set Quad Enable. */
    }
    else if (wrCmd == CMD_QUAD_PAGE_PROGRAM_EON)
    {
        SPIM_SetQuadEnable(1, 1UL);              /* Set Quad Enable. */
        spim_eon_set_qpi_mode(1);                /* Enter QPI mode.  */
    }

    SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_PAGEWRITE);/* Switch to Page Write mode.   */
    SPIM_SET_SPIM_MODE(wrCmd);                  /* SPIM mode.       */
    SPIM_SET_4BYTE_ADDR_EN(is4ByteAddr);        /* Enable/disable 4-Byte Address.  */

    SPIM->SRAMADDR = (uint32_t) pu8TxBuf;        /* SRAM u32Address. */
    SPIM->DMACNT = u32NTx;                       /* Transfer length. */
    SPIM->FADDR = u32Addr;                       /* Flash u32Address.*/
    SPIM_SET_GO();                              /* Go.              */

    if (isSync)
    {
        SPIM_WAIT_FREE();
    }

    if (wrCmd == CMD_QUAD_PAGE_PROGRAM_EON)
    {
        spim_eon_set_qpi_mode(0);                /* Exit QPI mode.   */
    }
}

/** @endcond HIDDEN_SYMBOLS */

/**
  * @brief      Write data to SPI Flash by sending commands manually (I/O mode).
  * @param      u32Addr: Start u32Address to write.
  * @param      is4ByteAddr: 4-byte u32Address or not.
  * @param      u32NTx: Number of bytes to write.
  * @param      pu8TxBuf: Transmit buffer.
  * @param      wrCmd: Write command.
  * @param      u32NBitCmd: N-bit transmit command.
  * @param      u32NBitAddr: N-bit transmit u32Address.
  * @param      u32NBitDat: N-bit transmit/receive data.
  * @return     None.
  */
void SPIM_IO_Write(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NTx, uint8_t pu8TxBuf[], uint8_t wrCmd,
                   uint32_t u32NBitCmd, uint32_t u32NBitAddr, uint32_t u32NBitDat)
{
    uint32_t  pageOffset, toWr;
    uint32_t  buf_idx = 0UL;

    pageOffset = u32Addr % 256UL;

    if ((pageOffset + u32NTx) <= 256UL)          /* Do all the bytes fit onto one page ? */
    {
        SPIM_WriteInPageDataByIo(u32Addr, is4ByteAddr, u32NTx, &pu8TxBuf[buf_idx],
                                 wrCmd, u32NBitCmd, u32NBitAddr, u32NBitDat, 1);
    }
    else
    {
        toWr = 256UL - pageOffset;               /* Size of data remaining on the first page. */

        SPIM_WriteInPageDataByIo(u32Addr, is4ByteAddr, toWr, &pu8TxBuf[buf_idx],
                                 wrCmd, u32NBitCmd, u32NBitAddr, u32NBitDat, 1);
        u32Addr += toWr;                         /* Advance indicator.  */
        u32NTx -= toWr;
        buf_idx += toWr;

        while (u32NTx)
        {
            toWr = 256UL;
            if (toWr > u32NTx)
            {
                toWr = u32NTx;
            }

            SPIM_WriteInPageDataByIo(u32Addr, is4ByteAddr, toWr, &pu8TxBuf[buf_idx],
                                     wrCmd, u32NBitCmd, u32NBitAddr, u32NBitDat, 1);
            u32Addr += toWr;                 /* Advance indicator.  */
            u32NTx -= toWr;
            buf_idx += toWr;
        }
    }
}

/**
  * @brief      Read data from SPI Flash by sending commands manually (I/O mode).
  * @param      u32Addr     Start u32Address to read.
  * @param      is4ByteAddr 4-byte u32Address or not.
  * @param      u32NRx      Number of bytes to read.
  * @param      pu8RxBuf    Receive buffer.
  * @param      rdCmd       Read command.
  * @param      u32NBitCmd  N-bit transmit command.
  * @param      u32NBitAddr N-bit transmit u32Address.
  * @param      u32NBitDat  N-bit transmit/receive data.
  * @param      u32NDummy   Number of dummy bytes following address.
  * @return     None.
  */
void SPIM_IO_Read(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NRx, uint8_t pu8RxBuf[], uint8_t rdCmd,
                  uint32_t u32NBitCmd, uint32_t u32NBitAddr, uint32_t u32NBitDat, int u32NDummy)
{
    uint8_t   cmdBuf[16];
    uint32_t  buf_idx;

    SPIM_SET_SS_EN(1);                      /* CS activated.    */

    cmdBuf[0] = rdCmd;
    SwitchNBitOutput(u32NBitCmd);
    spim_write(cmdBuf, 1UL);                 /* Write out command. */

    buf_idx = 0UL;
    if (is4ByteAddr)
    {
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 24);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 16);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 8);
        cmdBuf[buf_idx++] = (uint8_t) u32Addr;
    }
    else
    {
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 16);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 8);
        cmdBuf[buf_idx++] = (uint8_t) u32Addr;
    }
    SwitchNBitOutput(u32NBitAddr);
    spim_write(cmdBuf, buf_idx);                 /* Write out u32Address. */

    buf_idx = 0UL;
    while (u32NDummy --)
    {
        cmdBuf[buf_idx++] = 0x00U;
    }

    /* Same bit mode as above. */
    spim_write(cmdBuf, buf_idx);                 /* Write out dummy bytes. */

    SwitchNBitInput(u32NBitDat);
    spim_read(pu8RxBuf, u32NRx);                 /* Read back data.  */

    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */
}

/**
  * @brief      Write data to SPI Flash by Page Write mode.
  * @param      u32Addr     Start address to write.
  * @param      is4ByteAddr 4-byte address or not.
  * @param      u32NTx      Number of bytes to write.
  * @param      pu8TxBuf    Transmit buffer.
  * @param      wrCmd       Write command.
  * @return     None.
  */
void SPIM_DMA_Write(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NTx, uint8_t pu8TxBuf[], uint32_t wrCmd)
{
    uint32_t   pageOffset, toWr;
    uint32_t   buf_idx = 0UL;

    pageOffset = u32Addr % 256UL;

    if ((pageOffset + u32NTx) <= 256UL)
    {
        /* Do all the bytes fit onto one page ? */
        SPIM_WriteInPageDataByPageWrite(u32Addr, is4ByteAddr, u32NTx, pu8TxBuf, wrCmd, 1);
    }
    else
    {
        toWr = 256UL - pageOffset;               /* Size of data remaining on the first page. */

        SPIM_WriteInPageDataByPageWrite(u32Addr, is4ByteAddr, toWr, &pu8TxBuf[buf_idx], wrCmd, 1);

        u32Addr += toWr;                         /* Advance indicator. */
        u32NTx -= toWr;
        buf_idx += toWr;

        while (u32NTx)
        {
            toWr = 256UL;
            if (toWr > u32NTx)
            {
                toWr = u32NTx;
            }

            SPIM_WriteInPageDataByPageWrite(u32Addr, is4ByteAddr, toWr, &pu8TxBuf[buf_idx], wrCmd, 1);

            u32Addr += toWr;                 /* Advance indicator. */
            u32NTx -= toWr;
            buf_idx += toWr;
        }
    }
}

/**
  * @brief      Read data from SPI Flash by Page Read mode.
  * @param      u32Addr     Start address to read.
  * @param      is4ByteAddr 4-byte u32Address or not.
  * @param      u32NRx      Number of bytes to read.
  * @param      pu8RxBuf    Receive buffer.
  * @param      u32RdCmd    Read command.
  * @param      isSync      Block or not.
  * @return     None.
  */
void SPIM_DMA_Read(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NRx, uint8_t pu8RxBuf[],
                   uint32_t u32RdCmd, int isSync)
{
    SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_PAGEREAD); /* Switch to Page Read mode. */
    SPIM_SET_SPIM_MODE(u32RdCmd);               /* SPIM mode.       */
    SPIM_SET_4BYTE_ADDR_EN(is4ByteAddr);        /* Enable/disable 4-Byte Address. */

    SPIM->SRAMADDR = (uint32_t) pu8RxBuf;        /* SRAM u32Address. */
    SPIM->DMACNT = u32NRx;                       /* Transfer length. */
    SPIM->FADDR = u32Addr;                       /* Flash u32Address.*/
    SPIM_SET_GO();                              /* Go.              */

    if (isSync)
    {
        SPIM_WAIT_FREE();                       /* Wait for DMA done.  */
    }
}

/**
  * @brief      Enter Direct Map mode.
  * @param      is4ByteAddr     4-byte u32Address or not.
  * @param      u32RdCmd        Read command.
  * @param      u32IdleIntvl    Idle interval.
  * @return     None.
  */
void SPIM_EnterDirectMapMode(int is4ByteAddr, uint32_t u32RdCmd, uint32_t u32IdleIntvl)
{
    SPIM_SET_4BYTE_ADDR_EN(is4ByteAddr);        /* Enable/disable 4-byte u32Address. */
    SPIM_SET_SPIM_MODE(u32RdCmd);               /* SPIM mode.       */
    SPIM_SET_IDL_INTVL(u32IdleIntvl);            /* Idle interval.   */
    SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_DIRECTMAP);   /* Switch to Direct Map mode.     */
}

/**
  * @brief      Exit Direct Map mode.
  * @return     None.
  */
void SPIM_ExitDirectMapMode(void)
{
    SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_IO);       /* Switch back to Normal mode.  */
}


/*@}*/ /* end of group SPIM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SPIM_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
