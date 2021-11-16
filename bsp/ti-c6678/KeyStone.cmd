/****************************************************************************/
/*                                                                          */
/*                               M6678.cmd                                  */
/*                         Copyright (c): NUDT                              */
/*                                                                          */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an M6678              */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific C6xxx    */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

-heap  0x800
-stack 0x1000

MEMORY
{
	VECTORS:		o = 0x00800000  l = 0x00000200
	LL2_CODE:		o = 0x00800200  l = 0x0001FE00
	LL2_RW_DATA: 	o = 0x00820000  l = 0x00020000   /*set memory protection attribitue as read/write*/
}

SECTIONS
{
	.vecs       	>    VECTORS

	.text           >    LL2_CODE
	.cinit          >    LL2_CODE
	.const          >    LL2_CODE
	.switch         >    LL2_CODE
	.stack          >    LL2_RW_DATA
	GROUP
	{
		.neardata
		.rodata
		.bss
	} 		>    LL2_RW_DATA
	.far            >    LL2_RW_DATA
	.fardata        >    LL2_RW_DATA
	.cio            >    LL2_RW_DATA
	.sysmem         >    LL2_RW_DATA
}
