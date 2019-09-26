//=================================================================
//
//        zlib1.c
//
//        zlib compression/decompression test 1
//
//==========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under    
// the terms of the GNU General Public License as published by the Free     
// Software Foundation; either version 2 or (at your option) any later      
// version.                                                                 
//
// eCos is distributed in the hope that it will be useful, but WITHOUT      
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
// for more details.                                                        
//
// You should have received a copy of the GNU General Public License        
// along with eCos; if not, write to the Free Software Foundation, Inc.,    
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
//
// As a special exception, if other files instantiate templates or use      
// macros or inline functions from this file, or you compile this file      
// and link it with other works to produce a work based on this file,       
// this file does not by itself cause the resulting work to be covered by   
// the GNU General Public License. However the source code for this file    
// must still be made available in accordance with section (3) of the GNU   
// General Public License v2.                                               
//
// This exception does not invalidate any other reasons why a work based    
// on this file might be covered by the GNU General Public License.         
// -------------------------------------------                              
// ####ECOSGPLCOPYRIGHTEND####                                              
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):     jskov
// Contributors:  jskov
// Date:          2001-03-09
// Description:   Tests zlib compress/decompress functionality.
//####DESCRIPTIONEND####


#include <cyg/hal/hal_arch.h>           // CYGNUM_HAL_STACK_SIZE_TYPICAL

#include <cyg/kernel/kapi.h>

#include <cyg/infra/testcase.h>
#include <cyg/infra/diag.h>

#ifdef CYGFUN_KERNEL_API_C

#include <cyg/compress/zlib.h>
#include <stdlib.h>

#define NTHREADS 1
#define STACKSIZE (CYGNUM_HAL_STACK_SIZE_TYPICAL > 8192 ? CYGNUM_HAL_STACK_SIZE_TYPICAL : 8192)

static cyg_handle_t thread[NTHREADS];

static cyg_thread thread_obj[NTHREADS];
static char stack[NTHREADS][STACKSIZE];

static char license_txt[] =
"Red Hat eCos Public License v1.1\n"
"\n"
"\n"
"1. DEFINITIONS\n"
"\n"
"1.1. \"Contributor\" means each entity that creates or\n"
"contributes to the creation of Modifications.\n"
"\n"
"1.2. \"Contributor Version\" means the combination of the\n"
"Original Code, prior Modifications used by a\n"
"Contributor, and the Modifications made by that\n"
"particular Contributor.\n"
"\n"
"1.3. \"Covered Code\" means the Original Code or\n"
"Modifications or the combination of the Original Code\n"
"and Modifications, in each case including portions\n"
"thereof.\n"
"\n"
"1.4. \"Electronic Distribution Mechanism\" means a\n"
"mechanism generally accepted in the software development\n"
"community for the electronic transfer of data.\n"
"\n"
"1.5. \"Executable\" means Covered Code in any form other\n"
"than Source Code.\n"
"1.6. \"Initial Developer\" means the individual or entity\n"
"identified as the Initial Developer in the Source Code\n"
"notice required by Exhibit A.\n"
"\n"
"1.7. \"Larger Work\" means a work which combines Covered\n"
"Code or portions thereof with code not governed by the\n"
"terms of this License.\n"
"\n"
"1.8. \"License\" means this document.\n"
"\n"
"1.9. \"Modifications\" means any addition to or deletion\n"
"from the substance or structure of either the Original\n"
"Code or any previous Modifications. When Covered Code is\n"
"released as a series of files, a Modification is:\n"
"\n"
"     A. Any addition to or deletion from the\n"
"     contents of a file containing Original Code or\n"
"     previous Modifications.\n"
"\n"
"     B. Any new file that contains any part of the\n"
"     Original Code or previous Modifications.\n"
"\n"
"1.10. \"Original Code\" means Source Code of computer\n"
"software code which is described in the Source Code\n"
"notice required by Exhibit A as Original Code, and\n"
"which, at the time of its release under this License is\n"
"not already Covered Code governed by this License.\n"
"\n"
"1.11. \"Source Code\" means the preferred form of the\n"
"Covered Code for making modifications to it, including\n"
"all modules it contains, plus any associated interface\n"
"definition files, scripts used to control compilation\n"
"and installation of an Executable, or a list of source\n"
"code differential comparisons against either the\n"
"Original Code or another well known, available Covered\n"
"Code of the Contributor's choice. The Source Code can be\n"
"in a compressed or archival form, provided the\n"
"appropriate decompression or de-archiving software is\n"
"widely available for no charge.\n"
"\n"
"1.12. \"You\" means an individual or a legal entity\n"
"exercising rights under, and complying with all of the\n"
"terms of, this License or a future version of this\n"
"License issued under Section 6.1. For legal entities,\n"
"\"You\" includes any entity which controls, is controlled\n"
"by, or is under common control with You. For purposes of\n"
"this definition, \"control\" means (a) the power, direct\n"
"or indirect, to cause the direction or management of\n"
"such entity, whether by contract or otherwise, or (b)\n"
"ownership of fifty percent (50%) or more of the\n"
"outstanding shares or beneficial ownership of such\n"
"entity.\n"
"\n"
"1.13. \"Red Hat Branded Code\" is code that Red Hat\n"
"distributes and/or permits others to distribute under\n"
"different terms than the Red Hat eCos Public License.\n"
"Red Hat's Branded Code may contain part or all of the\n"
"Covered Code.\n";

static void entry0( cyg_addrword_t data )
{
    int i;
    unsigned long len;
    int err;
    int buf_size = sizeof(license_txt)+512;
    unsigned char* packed = malloc(buf_size);
    unsigned char* unpacked = malloc(buf_size);
    
    if (NULL == packed || NULL == unpacked)
        CYG_TEST_NA("Not enough memory for buffers");

    CYG_TEST_INFO("Compressing");

    len = buf_size;
    err = compress(packed, &len, license_txt, sizeof(license_txt));
    diag_printf("len = %d", len);
    diag_dump_buf(packed, len);

    if (Z_OK != err)
        CYG_TEST_NA("Not enough memory for compression");


    CYG_TEST_INFO("Decompressing");
    err = uncompress(unpacked, &buf_size, packed, len);

    switch (err) {
    case Z_OK:
        break;
    case Z_MEM_ERROR:
        CYG_TEST_NA("Not enough memory for decompression");
        break;
    case Z_BUF_ERROR:
        CYG_TEST_FAIL_FINISH("Decompressed data larger than original");
        break;
    case Z_DATA_ERROR:
        CYG_TEST_FAIL_FINISH("Decompression failed");
        break;
    default:
        CYG_TEST_FAIL_FINISH("Unknown decompression error");
        break;
    }

    for (i = 0; i < sizeof(license_txt)-1; i++) {
        if (license_txt[i] != unpacked[i])
            CYG_TEST_FAIL_FINISH("Verify failed");
    }

    CYG_TEST_PASS_FINISH("zlib1 OK");
}

void zlib1_main( void )
{
    CYG_TEST_INIT();

    cyg_thread_create(4, entry0 , (cyg_addrword_t)0, "zlib1",
        (void *)stack[0], STACKSIZE,&thread[0], &thread_obj[0]);
    cyg_thread_resume(thread[0]);

    cyg_scheduler_start();

    CYG_TEST_FAIL_FINISH("Not reached");
}

externC void
cyg_start( void )
{ 
    zlib1_main();
}

#else /* def CYGFUN_KERNEL_API_C */
externC void
cyg_start( void )
{
    CYG_TEST_INIT();
    CYG_TEST_NA("Kernel C API layer disabled");
}
#endif /* def CYGFUN_KERNEL_API_C */

// EOF zlib1.c
