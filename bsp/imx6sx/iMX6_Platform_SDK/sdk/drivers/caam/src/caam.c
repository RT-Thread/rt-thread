/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "sdk.h"
#include "core/ccm_pll.h"
#include "caam_internal.h"
#include "caam/caam.h"

/*---------- Global variables ----------*/
/* Input job ring - single entry input ring */
uint32_t g_input_ring[JOB_RING_ENTRIES] = {0};

/* Output job ring - single entry output ring (consists of two words) */    
uint32_t g_output_ring[2*JOB_RING_ENTRIES] = {0, 0};

uint32_t decap_dsc[] = 
{
    DECAP_BLOB_DESC1,
    DECAP_BLOB_DESC2,
    DECAP_BLOB_DESC3,
    DECAP_BLOB_DESC4,
    DECAP_BLOB_DESC5,
    DECAP_BLOB_DESC6,
    DECAP_BLOB_DESC7,
    DECAP_BLOB_DESC8,
    DECAP_BLOB_DESC9
};

uint32_t encap_dsc[] = 
{
    ENCAP_BLOB_DESC1,
    ENCAP_BLOB_DESC2,
    ENCAP_BLOB_DESC3,
    ENCAP_BLOB_DESC4,
    ENCAP_BLOB_DESC5,
    ENCAP_BLOB_DESC6,
    ENCAP_BLOB_DESC7,
    ENCAP_BLOB_DESC8,
    ENCAP_BLOB_DESC9
};

uint32_t rng_inst_dsc[] = 
{
    RNG_INST_DESC1,
    RNG_INST_DESC2,
    RNG_INST_DESC3,
    RNG_INST_DESC4,
    RNG_INST_DESC5,
    RNG_INST_DESC6,
    RNG_INST_DESC7,
    RNG_INST_DESC8,
    RNG_INST_DESC9
};

uint32_t encrypt_dsc[] = 
{
    ENCRYPT_DESC1,
    ENCRYPT_DESC2,
    ENCRYPT_DESC3,
    ENCRYPT_DESC4,
    ENCRYPT_DESC5,
    ENCRYPT_DESC6,
    ENCRYPT_DESC7,
    ENCRYPT_DESC8
};

/*!
 * CAAM interrupt routine.
 */
void caam_interrupt_routine(void)
{
    /* no interrupt handling for that driver */
}

/*!
 * Setup CAAM interrupt. It enables or disables the related HW module
 * interrupt, and attached the related sub-routine into the vector table.
 *
 * @param   irq_id  ID of the interrupt. 
 * @param   state  ENABLE or DISABLE the interrupt.
 */
void caam_setup_interrupt(uint32_t irq_id, uint8_t state)
{
    if (state == TRUE) {
        /* register the IRQ sub-routine */
        register_interrupt_routine(irq_id, &caam_interrupt_routine);
        /* enable the IRQ */
        enable_interrupt(irq_id, CPU_0, 0);
    } else
        /* disable the IRQ */
        disable_interrupt(irq_id, CPU_0);
}

/*!
 * Secure memory run command.
 *
 * @param   sec_mem_cmd  Secure memory command register
 * @return  cmd_status  Secure memory command status register
 */
uint32_t secmem_set_cmd(uint32_t sec_mem_cmd)
{
    uint32_t temp_reg;
    reg32_write(CAAM_SMCJR0, sec_mem_cmd);
    do {
        temp_reg = reg32_read(CAAM_SMCSJR0);
    } while(temp_reg & CMD_COMPLETE);

    return temp_reg;
}

/*!
 * CAAM page allocation.
 *
 * @param   page  Number of the page to allocate.
 * @param   partition  Number of the partition to allocate.
 */
static uint32_t caam_page_alloc(uint8_t page_num, uint8_t partition_num)
{
    uint32_t temp_reg;

    /* 
     * De-Allocate partition_num if already allocated to ARM core
     */
    if(reg32_read(CAAM_SMPO_0) & PARTITION_OWNER(partition_num))
    {
        temp_reg = secmem_set_cmd(PARTITION(partition_num) | CMD_PART_DEALLOC);
        if(temp_reg & SMCSJR_AERR)
        {
            printf("Error: De-allocation status 0x%X\n",temp_reg);
            return ERROR_IN_PAGE_ALLOC;
        }
    }

    /* set the access rights to allow full access */ 
    reg32_write(CAAM_SMAG1JR0(partition_num), 0xF);
    reg32_write(CAAM_SMAG2JR0(partition_num), 0xF);
    reg32_write(CAAM_SMAPJR0(partition_num), 0xFF);

    /* Now need to allocate partition_num of secure RAM. */    
    /* De-Allocate page_num by starting with a page inquiry command */
    temp_reg = secmem_set_cmd(PAGE(page_num) | CMD_INQUIRY);
    /* if the page is owned, de-allocate it */
    if((temp_reg & SMCSJR_PO) == PAGE_OWNED)
    {
        temp_reg = secmem_set_cmd(PAGE(page_num) | CMD_PAGE_DEALLOC);
        if(temp_reg & SMCSJR_AERR)
        {
            printf("Error: Allocation status 0x%X\n",temp_reg);
            return ERROR_IN_PAGE_ALLOC;
        }
    }

    /* Allocate page_num to partition_num */
    temp_reg = secmem_set_cmd(PAGE(page_num) | PARTITION(partition_num)
                                             | CMD_PAGE_ALLOC);
    if(temp_reg & SMCSJR_AERR)
    {
        printf("Error: Allocation status 0x%X\n",temp_reg);
        return ERROR_IN_PAGE_ALLOC;
    }
    /* page inquiry command to ensure that the page was allocated */
    temp_reg = secmem_set_cmd(PAGE(page_num) | CMD_INQUIRY);
    /* if the page is not owned => problem */
    if((temp_reg & SMCSJR_PO) != PAGE_OWNED)
    {
        printf("Error: Allocation of page %d in partition %d failed 0x%X\n"
                ,temp_reg, page_num, partition_num);

        return ERROR_IN_PAGE_ALLOC;
    }

    return SUCCESS;
}

/*!
 * Use CAAM to encrypt a data with a key obtained from a DEK blob.
 *
 * @param   plain_text_addr  Location address of the plain text data.
 * @param   cipher_text_addr  Location address of the cipher text.
 * @param   key_addr  Location address of the encryption key (ignored for now).
 *
 * @return  SUCCESS or ERROR_XXX 
 */
uint32_t caam_enc_data(uint32_t plain_text_addr, uint32_t cipher_text_addr,
                   uint32_t key_addr)
{
    uint32_t ret = SUCCESS;

    /* Buffer to hold the resulting cipher text */
    uint8_t *cipher_text = (uint8_t *)cipher_text_addr;

    /* initialize the cipher text array */
    memset(cipher_text,0,100);

    /**** Prepare partition and page, and start the job to create the blob ***/
    ret = caam_page_alloc(PAGE_2, PARTITION_2);
    if(ret != SUCCESS)
        return ret;

    /* Write the plain text data to the partition. */
    memcpy((uint32_t*)SEC_MEM_PAGE2, (uint32_t*)plain_text_addr, 16);

    /* Now configure the access rights of the partition */
    reg32_write(CAAM_SMAG1JR0(PARTITION_2), KS_G1); // set group 1
    reg32_write(CAAM_SMAG2JR0(PARTITION_2), 0);     // clear group 2
    reg32_write(CAAM_SMAPJR0(PARTITION_2), PERM);   // set permissions & locks

    /* Fill in the address of the key to encrypt the data */
    encrypt_dsc[2] = (uint32_t)SEC_MEM_PAGE1;
    /* Fill in the address of the plain text data */
    encrypt_dsc[5] = (uint32_t)plain_text_addr;
    /* Fill in the address of the cipher text */
    encrypt_dsc[7] = (uint32_t)cipher_text_addr;

    /* Run descriptor with result written to ciphered data buffer */
    /* Add job to input ring */
    g_input_ring[0] = (uint32_t)encrypt_dsc;
    /* Increment jobs added */
    reg32_write(CAAM_IRJAR0, 1);

    /* Wait for job ring to complete the job: 1 completed job expected */
    while(reg32_read(CAAM_ORSFR0) != 1);
    /* check that descriptor address is the one expected in the output ring */
    if(g_output_ring[0] == (uint32_t)encrypt_dsc)
    {
        /* check if any error is reported in the output ring */
        if ((g_output_ring[1] & JOB_RING_STS) != 0)
        {
            printf("Error: encryption job completed with errors 0x%X\n",
                    g_output_ring[1]);
        }
    }
    else
    {
        printf("Error: encryption job output ring descriptor address does" \
                    " not match\n");
    }

    /* Remove job from Job Ring Output Queue */
    reg32_write(CAAM_ORJRR0, 1);

	return ret;
}

/*!
 * Use CAAM to decapsulate a blob to secure memory.
 * Such blob of secret key cannot be read once decrypted,
 * but can still be used for enc/dec operation of user's data.
 *
 * @param   blob_addr  Location address of the blob.
 *
 * @return  SUCCESS or ERROR_XXX
 */
uint32_t caam_decap_blob(uint32_t blob_addr)
{
    uint32_t ret = SUCCESS;

    /* Buffer that holds blob */
    uint8_t *blob = (uint8_t *)blob_addr;

    /**** Prepare partition and page, and start the job to create the blob ***/
    caam_page_alloc(PAGE_1, PARTITION_1);
    if(ret != SUCCESS)
        return ret;

    /* Now configure the access rights of the partition */
    reg32_write(CAAM_SMAG1JR0(PARTITION_1), KS_G1); // set group 1
    reg32_write(CAAM_SMAG2JR0(PARTITION_1), 0);     // clear group 2
    reg32_write(CAAM_SMAPJR0(PARTITION_1), PERM);   // set permissions & locks

    /* Fill in input blob addr in decap_dsc */
    decap_dsc[5] = (uint32_t)blob;
    /* Fill in the address where to decrypt the blob */
    decap_dsc[7] = (uint32_t)SEC_MEM_PAGE1;

    /* Run descriptor with result written to blob buffer */
    /* Add job to input ring */
    g_input_ring[0] = (uint32_t)decap_dsc;
    /* Increment jobs added */
    reg32_write(CAAM_IRJAR0, 1);

    /* Wait for job ring to complete the job: 1 completed job expected */
    while(reg32_read(CAAM_ORSFR0) != 1);
    /* check that descriptor address is the one expected in the output ring */
    if(g_output_ring[0] == (uint32_t)decap_dsc)
    {
        /* check if any error is reported in the output ring */
        if ((g_output_ring[1] & JOB_RING_STS) != 0)
        {
            printf("Error: blob decap job completed with errors 0x%X\n",
                    g_output_ring[1]);
        }
    }
    else
    {
        printf("Error: blob decap job output ring descriptor address does" \
                    " not match\n");
    }

    /* Remove job from Job Ring Output Queue */
    reg32_write(CAAM_ORJRR0, 1);

	return ret;
}

/*!
 * Use CAAM to generate a blob.
 *
 * @param   plain_data_addr  Location address of the plain data.
 * @param   blob_addr  Location address of the blob.
 *
 * @return  SUCCESS or ERROR_XXX
 */
uint32_t caam_gen_blob(uint32_t plain_data_addr, uint32_t blob_addr)
{
    uint32_t ret = SUCCESS;

    /* Buffer to hold the resulting blob */
    uint8_t *blob = (uint8_t *)blob_addr;

    /* initialize the blob array */
    memset(blob,0,100);

    /**** Prepare partition and page, and start the job to create the blob ***/
    caam_page_alloc(PAGE_1, PARTITION_1);
    if(ret != SUCCESS)
        return ret;

    /* Write the DEK to the partition. */
    memcpy((uint32_t*)SEC_MEM_PAGE1, (uint32_t*)plain_data_addr, 64);

    /* Now configure the access rights of the partition */
    reg32_write(CAAM_SMAG1JR0(PARTITION_1), KS_G1); // set group 1
    reg32_write(CAAM_SMAG2JR0(PARTITION_1), 0);     // clear group 2
    reg32_write(CAAM_SMAPJR0(PARTITION_1), PERM);   // set permissions & locks

    /* Fill in the address where the DEK resides */
    encap_dsc[5] = (uint32_t)SEC_MEM_PAGE1;
    /* Fill in output blob addr in encap_dsc */
    encap_dsc[7] = (uint32_t)blob;

    /* Run descriptor with result written to blob buffer */
    /* Add job to input ring */
    g_input_ring[0] = (uint32_t)encap_dsc;
    /* Increment jobs added */
    reg32_write(CAAM_IRJAR0, 1);

    /* Wait for job ring to complete the job: 1 completed job expected */
    while(reg32_read(CAAM_ORSFR0) != 1);
    /* check that descriptor address is the one expected in the output ring */
    if(g_output_ring[0] == (uint32_t)encap_dsc)
    {
        /* check if any error is reported in the output ring */
        if ((g_output_ring[1] & JOB_RING_STS) != 0)
        {
            printf("Error: blob encap job completed with errors 0x%X\n",
                    g_output_ring[1]);
        }
    }
    else
    {
        printf("Error: blob encap job output ring descriptor address does" \
                    " not match\n");
    }

    /* Remove job from Job Ring Output Queue */
    reg32_write(CAAM_ORJRR0, 1);

	return ret;
}

/*!
 * Initialize the CAAM.
 *
 */
void caam_open(void)
{
    uint32_t temp_reg;

    /* switch on the clock */
    clock_gating_config(CAAM_BASE_ADDR, CLOCK_ON);

    /* MID for CAAM - already done by HAB in ROM during preconfigure,
     * That is JROWN for JR0/1 = 1 (TZ, Secure World, ARM)
     * JRNSMID and JRSMID for JR0/1 = 2 (TZ, Secure World, CAAM)
     *
     * However, still need to initialize Job Rings as these are torn
     * down by HAB for each command
     */    

    /* Initialize job ring addresses */
    reg32_write(CAAM_IRBAR0, (uint32_t)g_input_ring);   // input ring address
    reg32_write(CAAM_ORBAR0, (uint32_t)g_output_ring);  // output ring address

    /* Initialize job ring sizes to 1 */
    reg32_write(CAAM_IRSR0, JOB_RING_ENTRIES);
    reg32_write(CAAM_ORSR0, JOB_RING_ENTRIES);

    /* HAB disables interrupts for JR0 so do the same here */
    temp_reg = reg32_read(CAAM_JRCFGR0_LS) | JRCFG_LS_IMSK;
    reg32_write(CAAM_JRCFGR0_LS, temp_reg);    

    /********* Initialize and instantiate the RNG *******************/
    /* if RNG already instantiated then skip it */
    if ((reg32_read(CAAM_RDSTA) & RDSTA_IF0) != RDSTA_IF0)
    {
        /* Enter TRNG Program mode */
        reg32_write(CAAM_RTMCTL,RTMCTL_PGM);
    
        /* Set OSC_DIV field to TRNG */
        temp_reg = reg32_read(CAAM_RTMCTL) | (RNG_TRIM_OSC_DIV << 2);
        reg32_write(CAAM_RTMCTL,temp_reg);
    
        /* Set delay */
        reg32_write(CAAM_RTSDCTL, ((RNG_TRIM_ENT_DLY << 16) | 0x09C4));   
        reg32_write(CAAM_RTFRQMIN, (RNG_TRIM_ENT_DLY >> 1));
        reg32_write(CAAM_RTFRQMAX, (RNG_TRIM_ENT_DLY << 3));
    
        /* Resume TRNG Run mode */
        temp_reg = reg32_read(CAAM_RTMCTL) ^ RTMCTL_PGM;
        reg32_write(CAAM_RTMCTL,temp_reg);   
    
        /* Clear the ERR bit in RTMCTL if set. The TRNG error can occur when the
        * RNG clock is not within 1/2x to 8x the system clock.
        * This error is possible if ROM code does not initialize the system PLLs
        * immediately after PoR.
        */
        temp_reg = reg32_read(CAAM_RTMCTL) | RTMCTL_ERR;
        reg32_write(CAAM_RTMCTL,temp_reg);
    
        /* Run descriptor to instantiate the RNG */
        /* Add job to input ring */
        g_input_ring[0] = (uint32_t)rng_inst_dsc;
        /* Increment jobs added */
        reg32_write(CAAM_IRJAR0, 1); 
    
        /* Wait for job ring to complete the job: 1 completed job expected */
        while(reg32_read(CAAM_ORSFR0) != 1);
        /* check that descriptor address is the one expected in the out ring */
        if(g_output_ring[0] == (uint32_t)rng_inst_dsc)
        {
            /* check if any error is reported in the output ring */
            if ((g_output_ring[1] & JOB_RING_STS) != 0)
            {
            printf("Error: RNG instantiation job completed with errors 0x%X\n"
                    , g_output_ring[1]);
            }
        }
        else
        {
            printf("Error: RNG job output ring descriptor address does" \
                        "not match\n");
        }

        /* ensure that the RNG was correctly instantiated */
        temp_reg = reg32_read(CAAM_RDSTA);
        if (temp_reg != (RDSTA_IF0 | RDSTA_SKVN))
        {
    
            printf("Error: RNG instantiation failed 0x%X\n", temp_reg);
        }

        /* Remove job from Job Ring Output Queue */
        reg32_write(CAAM_ORJRR0, 1);
    }

	return;
}
