/* Linker map for Soprano Shared Memory. */

MEMORY
{
PAGE 0 : /* Program memory. This is a legacy description since the C28 has a unified memory model. */

PAGE 1 : /* Data memory. This is a legacy description since the C28 has a unified memory model. */

	CPU2TOCPU1RAM   : origin = 0x03F800, length = 0x000400
    CPU1TOCPU2RAM   : origin = 0x03FC00, length = 0x000400
}

SECTIONS
{

    /* The following section definitions are required when using the IPC API Drivers */
    GROUP : > CPU2TOCPU1RAM, PAGE = 1
    {
        PUTBUFFER
        PUTWRITEIDX
        GETREADIDX
    }

    GROUP : > CPU1TOCPU2RAM, PAGE = 1
    {
        GETBUFFER :    TYPE = DSECT
        GETWRITEIDX :  TYPE = DSECT
        PUTREADIDX :   TYPE = DSECT
    }

}

/*
* ===========================================================================
* End of file.
* ===========================================================================
*/
