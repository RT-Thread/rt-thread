/********************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
**************************************************************************//*!
 *
 * @file flash_FTFL.c
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
#include "flash_FTFL.h" /* include flash driver header file */
#include "string.h"
/*********************************** Macros ************************************/

/*********************************** Defines ***********************************/
#define PROG_WORD_SIZE 30       /* adequate space for the small program */

/********************************** Constant ***********************************/

/*********************************** Variables *********************************/

/*********************************** Prototype *********************************/

/*********************************** Function **********************************/
/* With Keil, ram functions are configured in project setting */
#ifndef __CC_ARM
    #ifdef __IAR_SYSTEMS_ICC__ /* IAR compiler */
        __ramfunc static void SpSub(void);
    #else 
        /* CodeWarrior 10x & codeSourcery compilers */
        static void SpSub(void);
        static void SpSubEnd(void);
    #endif
#endif

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
	UNUSED(FlashClockDiv)	
#ifndef MCU_MK70F12	
	#ifdef MCU_MKL25Z4
			/* checking access error */
			if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
			{
				/* clear error flag */
				FTFA_FSTAT |= FTFA_FSTAT_ACCERR_MASK;
			}
		/* checking protection error */
			else if (FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK)
			{
				/* clear error flag */
				FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK;
			}
			else if (FTFA_FSTAT & FTFA_FSTAT_RDCOLERR_MASK)
			{
				/* clear error flag */
				FTFA_FSTAT |= FTFA_FSTAT_RDCOLERR_MASK;
			}
	#else
    /* checking access error */
    if (FTFL_FSTAT & FTFL_FSTAT_ACCERR_MASK)
    {
        /* clear error flag */
    	FTFL_FSTAT |= FTFL_FSTAT_ACCERR_MASK;
    }
    /* checking protection error */
    else if (FTFL_FSTAT & FTFL_FSTAT_FPVIOL_MASK)
    {
    	/* clear error flag */
    	FTFL_FSTAT |= FTFL_FSTAT_FPVIOL_MASK;
    }
    else if (FTFL_FSTAT & FTFL_FSTAT_RDCOLERR_MASK)
     {
        	/* clear error flag */
        	FTFL_FSTAT |= FTFL_FSTAT_RDCOLERR_MASK;
     }
    /* Disable Data Cache in Flash memory Controller Module  */
#if (defined (__MK_xxx_H__))
    FMC_PFB0CR &= ~FMC_PFB0CR_B0DCE_MASK;
	#ifndef MCU_MK20D5
    	FMC_PFB1CR &= ~FMC_PFB1CR_B1DCE_MASK;
		#endif
	#endif
#endif
#else    	
    /* checking access error */
    if (FTFE_FSTAT & FTFE_FSTAT_ACCERR_MASK)
    {
    	/* clear error flag */
    	FTFE_FSTAT |= FTFE_FSTAT_ACCERR_MASK;
    }
    /* checking protection error */
    else if (FTFE_FSTAT & FTFE_FSTAT_FPVIOL_MASK)
    {
    	/* clear error flag */
    	FTFE_FSTAT |= FTFE_FSTAT_FPVIOL_MASK;
    }
    else if (FTFE_FSTAT & FTFE_FSTAT_RDCOLERR_MASK)
    {
    	/* clear error flag */
    	FTFE_FSTAT |= FTFE_FSTAT_RDCOLERR_MASK;
    }
    /* Disable Data Cache in Flash memory Controller Module  */
#if (defined (__MK_xxx_H__))
    FMC_PFB01CR &= ~FMC_PFB01CR_B01DCE_MASK;
    FMC_PFB01CR &= ~FMC_PFB01CR_B01DCE_MASK;
#endif
#endif
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
unsigned char Flash_SectorErase(uint_32 FlashPtr)
{
    unsigned char Return = Flash_OK;

#if (defined(__CWCC__)||defined(__GNUC__))   
    static void (*fnRAM_code)(void) = 0;
    int i = 0;
    unsigned char *ptrThumb2 = (unsigned char *)SpSub;
    /* Make space for the routine on stack (this will have an even boundary) */
    static unsigned short usProgSpace[PROG_WORD_SIZE];               	

    /* Thumb 2 address */
    ptrThumb2 =  (unsigned char *)(((unsigned long)ptrThumb2) & ~0x1);  
    while (i < PROG_WORD_SIZE) 
    {                                
    	/* Copy program to SRAM */
        usProgSpace[i++] = *(unsigned short *)ptrThumb2;
        ptrThumb2 += sizeof (usProgSpace[0]);
    }
    ptrThumb2 = (unsigned char *)usProgSpace;
    /* Create a thumb 2 call */
    ptrThumb2++;                                                     
    fnRAM_code = (void(*)(void))(ptrThumb2);
#endif    

#ifndef MCU_MK70F12
	#ifdef MCU_MKL25Z4
		/* Allocate space on stack to run flash command out of SRAM */
    	/* wait till CCIF is set*/
    	while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)){};
    	/* Write command to FCCOB registers */
    	FTFA_FCCOB0 = FlashCmd_SectorErase;
    	FTFA_FCCOB1 = (uint_8)(FlashPtr >> 16);
    	FTFA_FCCOB2 = (uint_8)((FlashPtr >> 8) & 0xFF);
    	FTFA_FCCOB3 = (uint_8)(FlashPtr & 0xFF);

	#if (defined(__CWCC__)||defined(__GNUC__))      
    	fnRAM_code();
	#elif (defined (__IAR_SYSTEMS_ICC__)) 
    	SpSub();
	#elif (defined(__CC_ARM))
    	/* Launch command */
    	FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;    
    	/* wait for command completion */
    	while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {};
	#endif   
    	/* Checking access error */
    	if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
    	{
    		/* clear error flag */
    		FTFA_FSTAT |= FTFA_FSTAT_ACCERR_MASK;

    		/* update return value*/
    		Return |= Flash_FACCERR;
        }
    	/* checking protection error */
    	else if (FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK)
    	{
    		/* clear error flag */
    		FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK;

    		/* update return value*/
    		Return |= Flash_FPVIOL;
    	}
    	else if (FTFA_FSTAT & FTFA_FSTAT_RDCOLERR_MASK)
    	{
    		/* clear error flag */
    		FTFA_FSTAT |= FTFA_FSTAT_RDCOLERR_MASK;

    		/* update return value*/
    		Return |= Flash_RDCOLERR;
    	}
    /* checking MGSTAT0 non-correctable error */
    else if (FTFA_FSTAT & FTFA_FSTAT_MGSTAT0_MASK)
    {
    	Return |= Flash_MGSTAT0;
    }
#else
    /* Allocate space on stack to run flash command out of SRAM */
    /* wait till CCIF is set*/
    while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK)){};
    /* Write command to FCCOB registers */
    FTFL_FCCOB0 = FlashCmd_SectorErase;
    FTFL_FCCOB1 = (uint_8)(FlashPtr >> 16);
    FTFL_FCCOB2 = (uint_8)((FlashPtr >> 8) & 0xFF);
    FTFL_FCCOB3 = (uint_8)(FlashPtr & 0xFF);

#if (defined(__CWCC__)||defined(__GNUC__))      
    fnRAM_code();
#elif (defined (__IAR_SYSTEMS_ICC__)) 
    SpSub();
#elif (defined(__CC_ARM))
    /* Launch command */
    FTFL_FSTAT |= FTFL_FSTAT_CCIF_MASK;    
    /* wait for command completion */
    while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK)) {};
#endif   
    /* Checking access error */
    if (FTFL_FSTAT & FTFL_FSTAT_ACCERR_MASK)
    {
        /* clear error flag */
    	FTFL_FSTAT |= FTFL_FSTAT_ACCERR_MASK;

        /* update return value*/
        Return |= Flash_FACCERR;
        }
    /* checking protection error */
    else if (FTFL_FSTAT & FTFL_FSTAT_FPVIOL_MASK)
    {
    	/* clear error flag */
    	FTFL_FSTAT |= FTFL_FSTAT_FPVIOL_MASK;

        /* update return value*/
        Return |= Flash_FPVIOL;
    }
    else if (FTFL_FSTAT & FTFL_FSTAT_RDCOLERR_MASK)
    {
       	/* clear error flag */
       	FTFL_FSTAT |= FTFL_FSTAT_RDCOLERR_MASK;

           /* update return value*/
           Return |= Flash_RDCOLERR;
    }
    /* checking MGSTAT0 non-correctable error */
    else if (FTFL_FSTAT & FTFL_FSTAT_MGSTAT0_MASK)
    {
    	Return |= Flash_MGSTAT0;
    }
#endif
#else
    /* Allocate space on stack to run flash command out of SRAM */
    /* wait till CCIF is set*/
    while (!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK)){};
    /* Write command to FCCOB registers */
    FTFE_FCCOB0 = FlashCmd_SectorErase;
    FTFE_FCCOB1 = (uint_8)(FlashPtr >> 16);
    FTFE_FCCOB2 = (uint_8)((FlashPtr >> 8) & 0xFF);
    FTFE_FCCOB3 = (uint_8)(FlashPtr & 0xFF);

    /* Launch command */
    FTFE_FSTAT |= FTFE_FSTAT_CCIF_MASK;    
    /* wait for command completion */
    while (!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK)) {};
    /* checking access error */
    if (FTFE_FSTAT & FTFE_FSTAT_ACCERR_MASK)
    {
    	/* clear error flag */
    	FTFE_FSTAT |= FTFE_FSTAT_ACCERR_MASK;

    	/* update return value*/
    	Return |= Flash_FACCERR;
    }
    /* checking protection error */
    else if (FTFE_FSTAT & FTFE_FSTAT_FPVIOL_MASK)
    {
    	/* clear error flag */
    	FTFE_FSTAT |= FTFE_FSTAT_FPVIOL_MASK;

    	/* update return value*/
    	Return |= Flash_FPVIOL;
    }
    else if (FTFE_FSTAT & FTFE_FSTAT_RDCOLERR_MASK)
    {
    	/* clear error flag */
    	FTFE_FSTAT |= FTFE_FSTAT_RDCOLERR_MASK;

    	/* update return value*/
    	Return |= Flash_RDCOLERR;
    }
    /* checking MGSTAT0 non-correctable error */
    else if (FTFE_FSTAT & FTFE_FSTAT_MGSTAT0_MASK)
    {
    	Return |= Flash_MGSTAT0;
    }
#endif
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
unsigned char Flash_ByteProgram(uint_32 FlashStartAdd,uint_32 *DataSrcPtr,uint_32 NumberOfBytes)
{
    unsigned char Return = Flash_OK;
    /* Allocate space on stack to run flash command out of SRAM */
    uint_32 size_buffer;
#if((defined __CWCC__)|| (defined __GNUC__))   
    static void (*fnRAM_code)(void) = 0;
    /* Adequate space for the small program */
    #define PROG_WORD_SIZE 30                                        
    int i = 0;
    unsigned char *ptrThumb2 = (unsigned char *)SpSub;
    /* Make space for the routine on stack (this will have an even boundary) */
    static unsigned short usProgSpace[PROG_WORD_SIZE];               

    /* Thumb 2 address */
    ptrThumb2 =  (unsigned char *)(((unsigned long)ptrThumb2) & ~0x1);  
    /* Copy program to SRAM */
    while (i < PROG_WORD_SIZE) 
    {                                     
        usProgSpace[i++] = *(unsigned short *)ptrThumb2;
        ptrThumb2 += sizeof (usProgSpace[0]);
    }
    ptrThumb2 = (unsigned char *)usProgSpace;
    /* Create a thumb 2 call */
    ptrThumb2++;                                                     
    fnRAM_code = (void(*)(void))(ptrThumb2);
#endif
    if (NumberOfBytes == 0)
    {
    	return Flash_CONTENTERR;
    }
    else
    {
    	size_buffer = (NumberOfBytes - 1)/4 + 1;	
    }
#ifndef MCU_MK70F12
#ifdef MCU_MKL25Z4
    /* wait till CCIF is set*/
    while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)){};
        
	while ((size_buffer) && (Return == Flash_OK))
	{
		/* Write command to FCCOB registers */
		FTFA_FCCOB0 = FlashCmd_ProgramLongWord;
		FTFA_FCCOB1 = (uint_8)(FlashStartAdd >> 16);
		FTFA_FCCOB2 = (uint_8)((FlashStartAdd >> 8) & 0xFF);
		FTFA_FCCOB3 = (uint_8)(FlashStartAdd & 0xFF);
#ifdef __MK_xxx_H__ /*little endian*/
		FTFA_FCCOB4 = (uint_8)(*((uint_8*)DataSrcPtr+3));
		FTFA_FCCOB5 = (uint_8)(*((uint_8*)DataSrcPtr+2));
		FTFA_FCCOB6 = (uint_8)(*((uint_8*)DataSrcPtr+1));
		FTFA_FCCOB7 = (uint_8)(*((uint_8*)DataSrcPtr+0));
#else /* Big endian */
		
		FTFA_FCCOB4 = (uint_8)(*((uint_8*)DataSrcPtr+0));
		FTFA_FCCOB5 = (uint_8)(*((uint_8*)DataSrcPtr+1));
		FTFA_FCCOB6 = (uint_8)(*((uint_8*)DataSrcPtr+2));
		FTFA_FCCOB7 = (uint_8)(*((uint_8*)DataSrcPtr+3));
#endif		
		/* Launch command */
		FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;    
		/* wait for command completion */
	    while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {};
		
		//fnRAM_code();
	
	    /* checking access error */
	    if (FTFA_FSTAT & FTFA_FSTAT_ACCERR_MASK)
	    {
	        /* clear error flag */
	    	FTFA_FSTAT |= FTFA_FSTAT_ACCERR_MASK;

	        /* update return value*/
	        Return |= Flash_FACCERR;
	        }
	    /* checking protection error */
	    else if (FTFA_FSTAT & FTFA_FSTAT_FPVIOL_MASK)
	    {
	    	/* clear error flag */
	    	FTFA_FSTAT |= FTFA_FSTAT_FPVIOL_MASK;

	        /* update return value*/
	        Return |= Flash_FPVIOL;
	    }
	    else if (FTFA_FSTAT & FTFA_FSTAT_RDCOLERR_MASK)
	     {
	        	/* clear error flag */
	        	FTFA_FSTAT |= FTFA_FSTAT_RDCOLERR_MASK;

	            /* update return value*/
	            Return |= Flash_RDCOLERR;
	     }
	    /* checking MGSTAT0 non-correctable error */
	    else if (FTFA_FSTAT & FTFA_FSTAT_MGSTAT0_MASK)
	    {
	    	Return |= Flash_MGSTAT0;
	    }
#else
    /* wait till CCIF is set*/
    while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK)){};
        
	while ((size_buffer) && (Return == Flash_OK))
	{
		/* Write command to FCCOB registers */
		FTFL_FCCOB0 = FlashCmd_ProgramLongWord;
		FTFL_FCCOB1 = (uint_8)(FlashStartAdd >> 16);
		FTFL_FCCOB2 = (uint_8)((FlashStartAdd >> 8) & 0xFF);
		FTFL_FCCOB3 = (uint_8)(FlashStartAdd & 0xFF);
#ifdef __MK_xxx_H__ /*little endian*/
		FTFL_FCCOB4 = (uint_8)(*((uint_8*)DataSrcPtr+3));
		FTFL_FCCOB5 = (uint_8)(*((uint_8*)DataSrcPtr+2));
		FTFL_FCCOB6 = (uint_8)(*((uint_8*)DataSrcPtr+1));
		FTFL_FCCOB7 = (uint_8)(*((uint_8*)DataSrcPtr+0));
#else /* Big endian */
		
		FTFL_FCCOB4 = (uint_8)(*((uint_8*)DataSrcPtr+0));
		FTFL_FCCOB5 = (uint_8)(*((uint_8*)DataSrcPtr+1));
		FTFL_FCCOB6 = (uint_8)(*((uint_8*)DataSrcPtr+2));
		FTFL_FCCOB7 = (uint_8)(*((uint_8*)DataSrcPtr+3));
#endif		
		
#if (defined(__CWCC__)||defined(__GNUC__))      
        fnRAM_code();
#elif (defined (__IAR_SYSTEMS_ICC__)) 
        SpSub();
#elif (defined(__CC_ARM))
        /* Launch command */
        FTFL_FSTAT |= FTFL_FSTAT_CCIF_MASK;    
        /* wait for command completion */
        while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK)) {};
#endif   
	
	    /* checking access error */
	    if (FTFL_FSTAT & FTFL_FSTAT_ACCERR_MASK)
	    {
	        /* clear error flag */
	    	FTFL_FSTAT |= FTFL_FSTAT_ACCERR_MASK;

	        /* update return value*/
	        Return |= Flash_FACCERR;
	        }
	    /* checking protection error */
	    else if (FTFL_FSTAT & FTFL_FSTAT_FPVIOL_MASK)
	    {
	    	/* clear error flag */
	    	FTFL_FSTAT |= FTFL_FSTAT_FPVIOL_MASK;

	        /* update return value*/
	        Return |= Flash_FPVIOL;
	    }
	    else if (FTFL_FSTAT & FTFL_FSTAT_RDCOLERR_MASK)
	     {
	        	/* clear error flag */
	        	FTFL_FSTAT |= FTFL_FSTAT_RDCOLERR_MASK;

	            /* update return value*/
	            Return |= Flash_RDCOLERR;
	     }
	    /* checking MGSTAT0 non-correctable error */
	    else if (FTFL_FSTAT & FTFL_FSTAT_MGSTAT0_MASK)
	    {
	    	Return |= Flash_MGSTAT0;
	    }
#endif
#else
	    /* wait till CCIF is set*/
	    while (!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK)){};

	    while ((size_buffer) && (Return == Flash_OK))
	    {
	    	/* Write command to FCCOB registers */
	    	FTFE_FCCOB0 = FlashCmd_ProgramLongWord;
	    	FTFE_FCCOB1 = (uint_8)(FlashStartAdd >> 16);
	    	FTFE_FCCOB2 = (uint_8)((FlashStartAdd >> 8) & 0xFF);
	    	FTFE_FCCOB3 = (uint_8)(FlashStartAdd & 0xFF);
#ifdef __MK_xxx_H__ /*little endian*/
	    	FTFE_FCCOB4 = (uint_8)(*((uint_8*)DataSrcPtr+3));
	    	FTFE_FCCOB5 = (uint_8)(*((uint_8*)DataSrcPtr+2));
	    	FTFE_FCCOB6 = (uint_8)(*((uint_8*)DataSrcPtr+1));
	    	FTFE_FCCOB7 = (uint_8)(*((uint_8*)DataSrcPtr+0));
#else /* Big endian */

	    	FTFE_FCCOB4 = (uint_8)(*((uint_8*)DataSrcPtr+0));
	    	FTFE_FCCOB5 = (uint_8)(*((uint_8*)DataSrcPtr+1));
	    	FTFE_FCCOB6 = (uint_8)(*((uint_8*)DataSrcPtr+2));
	    	FTFE_FCCOB7 = (uint_8)(*((uint_8*)DataSrcPtr+3));
#endif		
	    	/* Launch command */
	    	FTFE_FSTAT |= FTFE_FSTAT_CCIF_MASK;    
	    	/* wait for command completion */
	    	while (!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK)) {};

	    	/* checking access error */
	    	if (FTFE_FSTAT & FTFE_FSTAT_ACCERR_MASK)
	    	{
	    		/* clear error flag */
	    		FTFE_FSTAT |= FTFE_FSTAT_ACCERR_MASK;

	    		/* update return value*/
	    		Return |= Flash_FACCERR;
	    	}
	    	/* checking protection error */
	    	else if (FTFE_FSTAT & FTFE_FSTAT_FPVIOL_MASK)
	    	{
	    		/* clear error flag */
	    		FTFE_FSTAT |= FTFE_FSTAT_FPVIOL_MASK;

	    		/* update return value*/
	    		Return |= Flash_FPVIOL;
	    	}
	    	else if (FTFE_FSTAT & FTFE_FSTAT_RDCOLERR_MASK)
	    	{
	    		/* clear error flag */
	    		FTFE_FSTAT |= FTFE_FSTAT_RDCOLERR_MASK;

	    		/* update return value*/
	    		Return |= Flash_RDCOLERR;
	    	}
	    	/* checking MGSTAT0 non-correctable error */
	    	else if (FTFE_FSTAT & FTFE_FSTAT_MGSTAT0_MASK)
	    	{
	    		Return |= Flash_MGSTAT0;
	    	}
#endif
		/* decrement byte count */
		 size_buffer --;
		 (uint_32*)DataSrcPtr++;
		 FlashStartAdd +=4;
		 
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
#ifndef __CC_ARM
	#ifdef __IAR_SYSTEMS_ICC__ /* IAR compiler */
		__ramfunc static void SpSub(void)
	#else /* CodeWarrior 10 & codeSourcery compilers */
		static void SpSub(void)
	#endif      
	{
	#ifndef MCU_MK70F12
		#ifdef MCU_MKL25Z4
			/* Launch command */
			FTFA_FSTAT |= FTFA_FSTAT_CCIF_MASK;    
			/* wait for command completion */
			while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK)) {};
		#else
			/* Launch command */
			FTFL_FSTAT |= FTFL_FSTAT_CCIF_MASK;    
			/* wait for command completion */
			while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK)) {};
		#endif
	#else
		/* Launch command */
		FTFE_FSTAT |= FTFE_FSTAT_CCIF_MASK;    
		/* wait for command completion */
		while (!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK)) {};
	#endif
	}
#endif		
		
/* Leave this immediately after SpSub */
#if ((defined __CWCC__) || (defined __GNUC__) || (defined __IAR_SYSTEMS_ICC__))  
		static void SpSubEnd(void) {}
#endif
