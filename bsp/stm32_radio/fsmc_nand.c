/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : fsmc_nand.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides a set of functions needed to drive the
*                      NAND512W3A2 memory mounted on STM3210E-EVAL board.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "fsmc_nand.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define FSMC_Bank_NAND     FSMC_Bank2_NAND
#define Bank_NAND_ADDR     Bank2_NAND_ADDR
#define Bank2_NAND_ADDR    ((u32)0x70000000)

/* Private macro -------------------------------------------------------------*/
#define ROW_ADDRESS (Address.Page + (Address.Block + (Address.Zone * NAND_ZONE_SIZE)) * NAND_BLOCK_SIZE)

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : FSMC_NAND_Init
* Description    : Configures the FSMC and GPIOs to interface with the NAND memory.
*                  This function must be called before any write/read operation
*                  on the NAND.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FSMC_NAND_Init(void)
{
    FSMC_NANDInitTypeDef FSMC_NANDInitStructure;
    FSMC_NAND_PCCARDTimingInitTypeDef  p;

    /*-- FSMC Configuration ------------------------------------------------------*/
    p.FSMC_SetupTime = 0x1;
    p.FSMC_WaitSetupTime = 0x3;
    p.FSMC_HoldSetupTime = 0x2;
    p.FSMC_HiZSetupTime = 0x1;

    FSMC_NANDInitStructure.FSMC_Bank = FSMC_Bank2_NAND;
    FSMC_NANDInitStructure.FSMC_Waitfeature = FSMC_Waitfeature_Enable;
    FSMC_NANDInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
    FSMC_NANDInitStructure.FSMC_ECC = FSMC_ECC_Enable;
    FSMC_NANDInitStructure.FSMC_ECCPageSize = FSMC_ECCPageSize_512Bytes;
//  FSMC_NANDInitStructure.FSMC_AddressLowMapping = FSMC_AddressLowMapping_Direct;
    FSMC_NANDInitStructure.FSMC_TCLRSetupTime = 0x00;
    FSMC_NANDInitStructure.FSMC_TARSetupTime = 0x00;
    FSMC_NANDInitStructure.FSMC_CommonSpaceTimingStruct = &p;
    FSMC_NANDInitStructure.FSMC_AttributeSpaceTimingStruct = &p;

    FSMC_NANDInit(&FSMC_NANDInitStructure);

    /* FSMC NAND Bank Cmd Test */
    FSMC_NANDCmd(FSMC_Bank2_NAND, ENABLE);
}

/******************************************************************************
* Function Name  : FSMC_NAND_ReadID
* Description    : Reads NAND memory's ID.
* Input          : - NAND_ID: pointer to a NAND_IDTypeDef structure which will hold
*                    the Manufacturer and Device ID.
* Output         : None
* Return         : None
*******************************************************************************/
void FSMC_NAND_ReadID(NAND_IDTypeDef* NAND_ID)
{
    u32 data = 0;

    /* Send Command to the command area */
    *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = 0x90;
    *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = 0x00;

    /* Sequence to read ID from NAND flash */
    data = *(vu32 *)(Bank_NAND_ADDR | DATA_AREA);

    NAND_ID->Maker_ID   = ADDR_1st_CYCLE (data);
    NAND_ID->Device_ID  = ADDR_2nd_CYCLE (data);
    NAND_ID->Third_ID   = ADDR_3rd_CYCLE (data);
    NAND_ID->Fourth_ID  = ADDR_4th_CYCLE (data);
}

/******************************************************************************
* Function Name  : FSMC_NAND_WriteSmallPage
* Description    : This routine is for writing one or several 512 Bytes Page size.
* Input          : - pBuffer: pointer on the Buffer containing data to be written
*                  - Address: First page address
*                  - NumPageToWrite: Number of page to write
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation
*                  And the new status of the increment address operation. It can be:
*                  - NAND_VALID_ADDRESS: When the new address is valid address
*                  - NAND_INVALID_ADDRESS: When the new address is invalid address
*******************************************************************************/
u32 FSMC_NAND_WriteSmallPage(u8 *pBuffer, NAND_ADDRESS Address, u32 NumPageToWrite)
{
    u32 index = 0x00, numpagewritten = 0x00, addressstatus = NAND_VALID_ADDRESS;
    u32 status = NAND_READY, size = 2048;

    while((NumPageToWrite != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
    {
        /* Page write command and address */
        *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_A;
        *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_WRITE0;

        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_4th_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_5fh_CYCLE(ROW_ADDRESS);

        /* Calculate the size */
        size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpagewritten);


        /* Write data */
        for(; index < size; index++)
        {
            *(vu8 *)(Bank_NAND_ADDR | DATA_AREA) = pBuffer[index];
        }

        *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_WRITE_TRUE1;

        /* Check status for successful operation */
        status = FSMC_NAND_GetStatus();

        if(status == NAND_READY)
        {
            numpagewritten++;

            NumPageToWrite--;

            /* Calculate Next small page Address */
            addressstatus = FSMC_NAND_AddressIncrement(&Address);
        }
    }

    return (status | addressstatus);
}

/******************************************************************************
* Function Name  : FSMC_NAND_ReadSmallPage
* Description    : This routine is for sequential read from one or several
*                  512 Bytes Page size.
* Input          : - pBuffer: pointer on the Buffer to fill
*                  - Address: First page address
*                  - NumPageToRead: Number of page to read
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation
*                  And the new status of the increment address operation. It can be:
*                  - NAND_VALID_ADDRESS: When the new address is valid address
*                  - NAND_INVALID_ADDRESS: When the new address is invalid address
*******************************************************************************/
u32 FSMC_NAND_ReadSmallPage(u8 *pBuffer, NAND_ADDRESS Address, u32 NumPageToRead)
{
    u32 index = 0x00, numpageread = 0x00, addressstatus = NAND_VALID_ADDRESS;
    u32 status = NAND_READY, size = 2048, i = 0;

    /* Calculate the size */
    size = NAND_PAGE_SIZE + (NAND_PAGE_SIZE * numpageread);

    while((NumPageToRead != 0x0) && (addressstatus == NAND_VALID_ADDRESS))
    {
        /* Page Read command and page address */
        *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_A;

        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_4th_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_5fh_CYCLE(ROW_ADDRESS);

        *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_TRUE1;
        for(i = 0; i <= 10000; i++);

        /* Get Data into Buffer */
        for(; index < size; index++)
        {
            pBuffer[index]= *(vu8 *)(Bank_NAND_ADDR | DATA_AREA);
        }

        numpageread++;

        NumPageToRead--;

        /* Calculate page address */
        addressstatus = FSMC_NAND_AddressIncrement(&Address);
    }

    status = FSMC_NAND_GetStatus();

    return (status | addressstatus);
}

/******************************************************************************
* Function Name  : FSMC_NAND_WriteSpareArea
* Description    : This routine write the spare area information for the specified
*                  pages addresses.
* Input          : - pBuffer: pointer on the Buffer containing data to be written
*                  - Address: First page address
*                  - NumSpareAreaTowrite: Number of Spare Area to write
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation
*                  And the new status of the increment address operation. It can be:
*                  - NAND_VALID_ADDRESS: When the new address is valid address
*                  - NAND_INVALID_ADDRESS: When the new address is invalid address
*******************************************************************************/
u32 FSMC_NAND_WriteSpareArea(u8 *pBuffer, NAND_ADDRESS Address, u32 NumSpareAreaTowrite)
{
    u32 index = 0x00, numsparesreawritten = 0x00, addressstatus = NAND_VALID_ADDRESS;
    u32 status = NAND_READY, size = 0x00;

    while((NumSpareAreaTowrite != 0x00) && (addressstatus == NAND_VALID_ADDRESS) && (status == NAND_READY))
    {
        /* Page write Spare area command and address */
        *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_C;
        *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_WRITE0;

        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_4th_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_5fh_CYCLE(ROW_ADDRESS);
        /* Calculate the size */
        size = NAND_SPARE_AREA_SIZE + (NAND_SPARE_AREA_SIZE * numsparesreawritten);

        /* Write the data */
        for(; index < size; index++)
        {
            *(vu8 *)(Bank_NAND_ADDR | DATA_AREA) = pBuffer[index];
        }

        *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_WRITE_TRUE1;

        /* Check status for successful operation */
        status = FSMC_NAND_GetStatus();

        if(status == NAND_READY)
        {
            numsparesreawritten++;

            NumSpareAreaTowrite--;

            /* Calculate Next page Address */
            addressstatus = FSMC_NAND_AddressIncrement(&Address);
        }
    }

    return (status | addressstatus);
}

/******************************************************************************
* Function Name  : FSMC_NAND_ReadSpareArea
* Description    : This routine read the spare area information from the specified
*                  pages addresses.
* Input          : - pBuffer: pointer on the Buffer to fill
*                  - Address: First page address
*                  - NumSpareAreaToRead: Number of Spare Area to read
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation
*                  And the new status of the increment address operation. It can be:
*                  - NAND_VALID_ADDRESS: When the new address is valid address
*                  - NAND_INVALID_ADDRESS: When the new address is invalid address
*******************************************************************************/
u32 FSMC_NAND_ReadSpareArea(u8 *pBuffer, NAND_ADDRESS Address, u32 NumSpareAreaToRead)
{
    u32 numsparearearead = 0x00, index = 0x00, addressstatus = NAND_VALID_ADDRESS;
    u32 status = NAND_READY, size = 0x00;

    while((NumSpareAreaToRead != 0x0) && (addressstatus == NAND_VALID_ADDRESS))
    {
        /* Page Read command and page address */
        *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_C;

        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_4th_CYCLE(ROW_ADDRESS);
        *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_5fh_CYCLE(ROW_ADDRESS);

        *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_AREA_TRUE1;

        /* Data Read */
        size = NAND_SPARE_AREA_SIZE +  (NAND_SPARE_AREA_SIZE * numsparearearead);

        /* Get Data into Buffer */
        for ( ; index < size; index++)
        {
            pBuffer[index] = *(vu8 *)(Bank_NAND_ADDR | DATA_AREA);
        }

        numsparearearead++;

        NumSpareAreaToRead--;

        /* Calculate page address */
        addressstatus = FSMC_NAND_AddressIncrement(&Address);
    }

    status = FSMC_NAND_GetStatus();

    return (status | addressstatus);
}

/******************************************************************************
* Function Name  : FSMC_NAND_EraseBlock
* Description    : This routine erase complete block from NAND FLASH
* Input          : - Address: Any address into block to be erased
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation
*******************************************************************************/
u32 FSMC_NAND_EraseBlock(NAND_ADDRESS Address)
{
    *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_ERASE0;

    *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_1st_CYCLE(ROW_ADDRESS);
    *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_2nd_CYCLE(ROW_ADDRESS);
    *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_3rd_CYCLE(ROW_ADDRESS);
    *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_4th_CYCLE(ROW_ADDRESS);
    *(vu8 *)(Bank_NAND_ADDR | ADDR_AREA) = ADDR_5fh_CYCLE(ROW_ADDRESS);

    *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_ERASE1;

    return (FSMC_NAND_GetStatus());
}

/******************************************************************************
* Function Name  : FSMC_NAND_Reset
* Description    : This routine reset the NAND FLASH
* Input          : None
* Output         : None
* Return         : NAND_READY
*******************************************************************************/
u32 FSMC_NAND_Reset(void)
{
    *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_RESET;

    return (NAND_READY);
}

/******************************************************************************
* Function Name  : FSMC_NAND_GetStatus
* Description    : Get the NAND operation status
* Input          : None
* Output         : None
* Return         : New status of the NAND operation. This parameter can be:
*                   - NAND_TIMEOUT_ERROR: when the previous operation generate
*                     a Timeout error
*                   - NAND_READY: when memory is ready for the next operation
*******************************************************************************/
u32 FSMC_NAND_GetStatus(void)
{
    u32 timeout = 0x1000000, status = NAND_READY;

    status = FSMC_NAND_ReadStatus();

    /* Wait for a NAND operation to complete or a TIMEOUT to occur */
    while ((status != NAND_READY) &&( timeout != 0x00))
    {
        status = FSMC_NAND_ReadStatus();
        timeout --;
    }

    if(timeout == 0x00)
    {
        status =  NAND_TIMEOUT_ERROR;
    }

    /* Return the operation status */
    return (status);
}
/******************************************************************************
* Function Name  : FSMC_NAND_ReadStatus
* Description    : Reads the NAND memory status using the Read status command
* Input          : None
* Output         : None
* Return         : The status of the NAND memory. This parameter can be:
*                   - NAND_BUSY: when memory is busy
*                   - NAND_READY: when memory is ready for the next operation
*                   - NAND_ERROR: when the previous operation gererates error
*******************************************************************************/
u32 FSMC_NAND_ReadStatus(void)
{
    u32 data = 0x00, status = NAND_BUSY;

    /* Read status operation ------------------------------------ */
    *(vu8 *)(Bank_NAND_ADDR | CMD_AREA) = NAND_CMD_STATUS;
    data = *(vu8 *)(Bank_NAND_ADDR);

    if((data & NAND_ERROR) == NAND_ERROR)
    {
        status = NAND_ERROR;
    }
    else if((data & NAND_READY) == NAND_READY)
    {
        status = NAND_READY;
    }
    else
    {
        status = NAND_BUSY;
    }

    return (status);
}

/******************************************************************************
* Function Name  : NAND_AddressIncrement
* Description    : Increment the NAND memory address
* Input          : - Address: address to be incremented.
* Output         : None
* Return         : The new status of the increment address operation. It can be:
*                  - NAND_VALID_ADDRESS: When the new address is valid address
*                  - NAND_INVALID_ADDRESS: When the new address is invalid address
*******************************************************************************/
u32 FSMC_NAND_AddressIncrement(NAND_ADDRESS* Address)
{
    u32 status = NAND_VALID_ADDRESS;

    Address->Page++;

    if(Address->Page == NAND_BLOCK_SIZE)
    {
        Address->Page = 0;
        Address->Block++;

        if(Address->Block == NAND_ZONE_SIZE)
        {
            Address->Block = 0;
            Address->Zone++;

            if(Address->Zone == NAND_MAX_ZONE)
            {
                status = NAND_INVALID_ADDRESS;
            }
        }
    }

    return (status);
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
