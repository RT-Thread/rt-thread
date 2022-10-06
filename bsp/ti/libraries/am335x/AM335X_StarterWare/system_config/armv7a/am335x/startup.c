/**
 * \file startup.c
 *
 * \brief  Configures the PLL registers to achieve the required Operating 
 *         frequency. Power and sleep controller is activated for UART and
 *         Interuppt controller. Interrupt vector is copied to the shared Ram.
 *         After doing all the above, controller is given to the application. 
 *  
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include "soc_AM335x.h"
#include "hw_types.h"
#include "cp15.h"

/***********************************************************************
**                            MACRO DEFINITIONS
***********************************************************************/
#define E_PASS                         (0)
#define E_FAIL                         (-1)


/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/
extern void Entry(void);
extern void UndefInstHandler(void);
extern void SVC_Handler(void);
extern void AbortHandler(void);
extern void IRQHandler(void);
extern void FIQHandler(void);

/**********************************************************************
*                   INTERNAL FUNCTION PROTOTYPES
**********************************************************************/

unsigned int PLL0Init(unsigned char clk_src, unsigned char pllm,
                      unsigned char prediv, unsigned char postdiv,
                      unsigned char div1, unsigned char div3,
                      unsigned char div7);
unsigned int PLL1Init(unsigned char pllm, unsigned char postdiv,
                      unsigned char div1, unsigned char div2,
                      unsigned char div3);
unsigned int DDR_Init ( unsigned int freq );
static void CopyVectorTable(void);
int main(void);

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
const unsigned int AM335X_VECTOR_BASE = 0x4030FC00;

static unsigned int const vecTbl[14]=
{
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF014,    /* Opcode for loading PC with the contents of [PC + 0x14] */
    0xE24FF008,    /* Opcode for loading PC with (PC - 8) (eq. to while(1)) */
    0xE59FF010,    /* Opcode for loading PC with the contents of [PC + 0x10] */
    0xE59FF010,    /* Opcode for loading PC with the contents of [PC + 0x10] */
    (unsigned int)Entry,
    (unsigned int)UndefInstHandler,
    (unsigned int)SVC_Handler,
    (unsigned int)AbortHandler,
    (unsigned int)IRQHandler,
    (unsigned int)FIQHandler
};


/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * \brief   This function does two operations:\n
 *          1> Copies an array which contains vector table values to the
 *             processor's vector table space.\n
 *          2> Then it calls the main() function.\n
 *
 * \param   None.
 *
 * \return  None.
 * 
 * \note    This function is the first function that needs to be called in a
 *          system. This should be set as the entry point in the linker script
 *          file if the ELF executable is to loaded via a debugger on the
 *          target. This function never returns, but gives control to the
 *          application entry point.
 **/
unsigned int start_boot(void) 
{
    /*
    ** Copy the vector table to desired location. This is needed if the vector
    ** table is to be relocated to OCMC RAM. The default vector table base is in
    ** OCMC RAM, but we can move it to the end of OCMC RAM, to make some more
    ** space in OCMC RAM for relocating any other code, if desired. 
    ** The vector table can be placed anywhere in the memory map. If the entire
    ** code is intended to be run from DDR, it can be placed in DDR also. In this
    ** case, only vector base address register need to be set with the base
    ** address of the vector table.
    */
    CopyVectorTable();

   /* Calling the main */
    main();

    while(1);
}

/**
 * \brief   This function copies the vector table to a location in OCMC
 *          RAM and sets the vector base address register.
 *
 * \param   None.
 *
 * \return  None.
 * 
 **/
static void CopyVectorTable(void)
{
    unsigned int *dest = (unsigned int *)AM335X_VECTOR_BASE;
    unsigned int *src =  (unsigned int *)vecTbl;
    unsigned int count;
  
    CP15VectorBaseAddrSet(AM335X_VECTOR_BASE);

    for(count = 0; count < sizeof(vecTbl)/sizeof(vecTbl[0]); count++)
    {
        dest[count] = src[count];
    }
}

/***************************** End Of File ***********************************/
