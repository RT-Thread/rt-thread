/********************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
**************************************************************************//*!
 *
 * @file flash.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file includes flash routines
 *
 *****************************************************************************/

/*********************************** Includes ***********************************/
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "flash.h" /* include flash driver header file */
#include "string.h"
/*********************************** Macros ************************************/

/*********************************** Defines ***********************************/
#if ((defined _MCF51MM256_H) || (defined _MCF51JE256_H))
#define		FCDIV			F2CDIV
#define 	FCDIV_FDIVLD 	F2CDIV_FDIVLD
#define		FSTAT_FCBEF		F2STAT_FCBEF
#define   FSTAT_FCCF    F2STAT_FCCF
#define		FSTAT_FACCERR	F2STAT_FACCERR
#define		FSTAT			F2STAT
#define		FCMD			F2CMD
#define		FSTAT_FPVIOL	F2STAT_FPVIOL
#endif
/********************************** Constant ***********************************/

/*********************************** Variables *********************************/

/*********************************** Prototype *********************************/

/*********************************** Function **********************************/


/*******************************************************************************
 * Function:        Flash_Init
 *
 * Description:     Set the flash clock
 *
 * Returns:         never return
 *
 * Notes:
 *
 *******************************************************************************/
void Flash_Init(unsigned char FlashClockDiv)
{
    /* Flash clock between 150-200kHz - > 8MHz/(39+1)=200kHz*/
    FCDIV = FlashClockDiv;
}


/*******************************************************************************
 * Function:        Flash_SectorErase
 *
 * Description:     erase a sector of the flash
 *
 * Returns:         Error Code
 *
 * Notes:
 *
 *******************************************************************************/
unsigned char Flash_SectorErase(unsigned long *FlashPtr)
{
    unsigned char Return = Flash_OK;


    /* Allocate space on stack to run flash command out of SRAM */
    char localbuf[100];
    int (*RunOnStack)(void) = (int(*)(void))localbuf;
    memcpy(localbuf, (void*)SpSub, (char*)SpSubEnd - (char*)SpSub);

    if (FCDIV_FDIVLD == 1)
    {
        /* flash is init */

        /* wait until FCBEF is set in FSTAT */
        while (FSTAT_FCBEF == 0) {}

        /* check for errors */
        if (FSTAT_FACCERR == 1)
        {
            /* clear error flag */
            FSTAT = 0x10;
        }

        if (FSTAT_FPVIOL == 1)
        {
            /* clear error flag */
            FSTAT = 0x20;
        }

        /* dummy write to flash */
        *FlashPtr = (unsigned long)0xFFFFFFFF;

        /* write command */
        FCMD = FlashCmd_SectorErase;
        RunOnStack();
        
        /* check for errors */
        if (FSTAT_FACCERR == 1)
        {
            /* clear error flag */
            FSTAT = 0x10;

            /* update return value*/
            Return |= Flash_FACCERR;
        }

        if (FSTAT_FPVIOL == 1)
        {
            /* clear error flag */
            FSTAT = 0x20;

            /* update return value*/
            Return |= Flash_FPVIOL;
        }
    }
    else
    {
        /* flash is not init */
        Return = Flash_NOT_INIT;
    }

    /* function return */
    return  Return;
}


/*******************************************************************************
 * Function:        Flash_ByteProgram
 *
 * Description:     byte program the flash
 *
 * Returns:         Error Code
 *
 * Notes:
 *
 *******************************************************************************/
unsigned char Flash_ByteProgram(unsigned long *FlashStartAdd,unsigned long *DataSrcPtr,unsigned long NumberOfBytes)
{
    unsigned char Return = Flash_OK;
    /* Allocate space on stack to run flash command out of SRAM */
    char localbuf[100];
    unsigned long size_buffer;
    int (*RunOnStack)(void) = (int(*)(void))localbuf;
    memcpy(localbuf, (void*)SpSub, (char*)SpSubEnd - (char*)SpSub);
    if (NumberOfBytes == 0)
    {
    	return Flash_CONTENTERR;
    }
    else
    {
    	size_buffer = (NumberOfBytes - 1)/4 + 1;	
    }

    if (FCDIV_FDIVLD == 1)
    {
        /* flash is init */

        /* wait until FCBEF is set in FSTAT */
        while (FSTAT_FCBEF == 0) {}

        /* check for errors */
        if (FSTAT_FACCERR == 1)
        {
            /* clear error flag */
            FSTAT = 0x10;
        }

        if (FSTAT_FPVIOL == 1)
        {
            /* clear error flag */
            FSTAT = 0x20;
        }

        while ((size_buffer) && (Return == Flash_OK))
        {


            /* write data to flash and increase pointers by 1 */
            *FlashStartAdd++ = *DataSrcPtr++;

            /* write command */
            FCMD = FlashCmd_Program;

            RunOnStack();

            /* check for errors */
            if (FSTAT_FACCERR == 1)
            {
                /* clear error flag */
                FSTAT = 0x10;

                /* update return value*/
                Return |= Flash_FACCERR;
            }

            if (FSTAT_FPVIOL == 1)
            {
                /* clear error flag */
                FSTAT = 0x20;

                /* update return value*/
                Return |= Flash_FPVIOL;
            }

            /* decrement byte count */
             size_buffer --;
        }
    }
    else
    {
        /* flash is not init */
        Return = Flash_NOT_INIT;
    }

    /* function return */
    return  Return;
}

/*******************************************************************************
 * Function:        SpSub
 *
 * Description:     Execute the Flash write while running out of SRAM
 *
 * Returns:
 *
 * Notes:
 *
 *******************************************************************************/
void SpSub(void)
{
    /* launch command */
    FSTAT_FCBEF = 1;
    /* wait for command completion */
    while (!(FSTAT_FCBEF & FSTAT_FCCF)) {};
}
/* Leave this immediately after SpSub */
void SpSubEnd(void) {}
