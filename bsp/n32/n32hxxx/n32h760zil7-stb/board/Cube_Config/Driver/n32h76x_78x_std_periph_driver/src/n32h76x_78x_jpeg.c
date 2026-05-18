/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_jpeg.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */

#include "n32h76x_78x_jpeg.h"

/***** JPEG CTRL module ****/

/**
*\*\name    JPEG_ConfigType.
*\*\fun     Choose JPEG operation type.
*\*\param   Type
*\*\            - JPEG_ENCODE
*\*\            - JPEG_DECODE
*\*\return  none.
**/
void JPEG_ConfigType(uint32_t Type)
{
    if(Type == JPEG_DECODE)
    {
        JPEG_CTRL->CTRL &= (~(JPEG_ENCODE));
    }
    else
    {
        JPEG_CTRL->CTRL |= JPEG_ENCODE;
    }
}

/**
*\*\name    JPEG_ConfigSwap.
*\*\fun     Swap Data for YCbCr 4:2:2 Format in BRC.
*\*\param   Type
*\*\            - JPEG_SWAP
*\*\            - JPEG_NOSWAP
*\*\return  none.
**/
void JPEG_ConfigSwap(uint32_t Type)
{
    if(Type == JPEG_NOSWAP)
    {
        JPEG_CTRL->CTRL &= (~(JPEG_SWAP));
    }
    else
    {
        JPEG_CTRL->CTRL |= JPEG_SWAP;
    }
}


/***** JPEG SGDMA module ****/

/**
*\*\name   SGDMA_Reset.
*\*\fun    Reset the SGDMA P2H/H2P module.
*\*\param  SGDMAx :
*\*\          - JPEG_SGDMA_P2H
*\*\          - JPEG_SGDMA_H2P
*\*\return none
**/
void SGDMA_Reset(JPEG_SGDMA_Module *SGDMAx)
{
    /* Module soft reset */
    if((SGDMAx->STS & JPEGDMA_STS_BUSY) == JPEGDMA_STS_BUSY)
    {
        SGDMAx->CTRL |= JPEGDMA_CTRL_HARDRST;
    }
    else
    {
        SGDMAx->CTRL |= JPEGDMA_CTRL_CLR;
    }
}

/**
*\*\name    SGDMA_H2P_Init.
*\*\fun     Initializes the SGDMA_H2P peripheral according to SGDMA_H2P_InitStruct.
*\*\param   SGDMA_H2P_InitStruct
*\*\            - h2p_desc
*\*\                - desc_flags : Descriptor flag bits
*\*\                    - linkenable: Link Enable 
*\*\                        - BITEQ0 : 0
*\*\                        - BITEQ1 : 1
*\*\                    - startframe: Start of Frame 
*\*\                        - BITEQ0 : 0
*\*\                        - BITEQ1 : 1
*\*\                    - endframe: End of Frame
*\*\                        - BITEQ0 : 0
*\*\                        - BITEQ1 : 1
*\*\                    - desccons: Descriptor Consumed 
*\*\                        - BITEQ0 : 0
*\*\                        - BITEQ1 : 1
*\*\                - blk_size : Block_Size
*\*\                    - 0x00000000 ~ 0xFFFFFFFF
*\*\                - blk_used : Block_Used
*\*\                    - 0x00000000 ~ 0xFFFFFFFF
*\*\                - blk_addr_low : The starting address of the data block [31:0]
*\*\                    - 0x00000000 ~ 0xFFFFFFFF
*\*\                - blk_addr_high : The starting address of the data block [63:32]
*\*\                    - 0x00000000
*\*\                - link_addr_low : Link to the next descriptor. Used when Link Enable = 1
*\*\                    - 0x00000000 ~ 0xFFFFFFFF
*\*\                - link_addr_high : Link to the next descriptor. Used when Link Enable = 1
*\*\                    - 0x00000000
*\*\            - max_burstsize : Maximum allowed size for an AXI4 MM burst
*\*\                - 0x00000000 ~ 0x00000100
*\*\            - SGlist_size : Scatter-Gather List Size
*\*\                - 0x00000000 ~ 0xFFFFFFFF
*\*\            - SGlist_Head : Scatter-Gather List Head index pointer
*\*\                - 0x00000000 ~ 0xFFFFFFFF
*\*\            - SGlist_Tail : Scatter-Gather List Tail index pointer
*\*\                - 0x00000000 ~ 0xFFFFFFFF
*\*\            - SGlist_Threshold : Almost Out Of Descriptors Threshold
*\*\                - 0x00000000 ~ 0xFFFFFFFF
*\*\            - desclist_type : The descriptor list structure type
*\*\                - SGDMA_DESCLIST_LIST
*\*\                - SGDMA_DESCLIST_RING
*\*\            - descstored_type : The descriptor storage location
*\*\                - SGDMA_DESC_CSR
*\*\                - SGDMA_DESC_MEMORY
*\*\            - DMA_EOF_type : DMA operation mode on EOF
*\*\                - SGDMA_EOF_PAUSEDMA
*\*\                - SGDMA_EOF_RESUMEDMA
*\*\            - DMA_burst_type : DMA burst type
*\*\                - SGDMA_BURST_FIXED
*\*\                - SGDMA_BURST_INCR
*\*\return  none.
**/
void SGDMA_H2P_Init(SGDMA_H2P_InitType* SGDMA_H2P_InitStruct)
{
    uint32_t resg_temp;
    
    SGDMA_Reset(JPEG_SGDMA_H2P);
    /* Module enable */
    JPEG_SGDMA_H2P->CTRL |= JPEGDMA_CTRL_EN;
    
    /* Maximum allowed size for an AXI4 MM burst */
    JPEG_SGDMA_H2P->MBSIZE = SGDMA_H2P_InitStruct->max_burstsize;
    
    /* H2P DMA initial configuration */
    resg_temp = JPEG_SGDMA_H2P->CTRL;
    resg_temp &= (~(JPEGDMA_CTRL_MMODE | JPEGDMA_CTRL_OPMODE));
    resg_temp |= SGDMA_H2P_InitStruct->desclist_type;
    resg_temp |= SGDMA_H2P_InitStruct->descstored_type;
    resg_temp |= SGDMA_H2P_InitStruct->DMA_burst_type;
    resg_temp |= SGDMA_H2P_InitStruct->DMA_EOF_type;
    JPEG_SGDMA_H2P->CTRL = resg_temp;
    
    /* Determine descriptor location */
    if(SGDMA_H2P_InitStruct->descstored_type == SGDMA_DESC_MEMORY)
    {
        /* Set base address of the SG List */
        JPEG_SGDMA_H2P->SGLPL = (uint32_t)&SGDMA_H2P_InitStruct->h2p_desc;
    }
    else
    {
        JPEG_SGDMA_H2P->DESCF = *(uint32_t*)(&SGDMA_H2P_InitStruct->h2p_desc);
        JPEG_SGDMA_H2P->DESC_MBADDL = SGDMA_H2P_InitStruct->h2p_desc.blk_addr_low;
        JPEG_SGDMA_H2P->DESC_MBADDH = SGDMA_H2P_InitStruct->h2p_desc.blk_addr_high;
        JPEG_SGDMA_H2P->DESC_MBSIZE = SGDMA_H2P_InitStruct->h2p_desc.blk_size;
        JPEG_SGDMA_H2P->DESC_MUS = SGDMA_H2P_InitStruct->h2p_desc.blk_used;
        /* Determine if linkenable is enabled */
        if(SGDMA_H2P_InitStruct->h2p_desc.desc_flags.bits.linkenable != DISABLE)
        {
            JPEG_SGDMA_H2P->DESC_LINKL = SGDMA_H2P_InitStruct->h2p_desc.link_addr_low;
            JPEG_SGDMA_H2P->DESC_LINKH = SGDMA_H2P_InitStruct->h2p_desc.link_addr_high;
        }
        else
        {
            /* no process */
        }
    }
    
    /* Set size of the SG List */
    JPEG_SGDMA_H2P->SGL_SIZE = SGDMA_H2P_InitStruct->SGlist_size;
    JPEG_SGDMA_H2P->SGL_HEAD = SGDMA_H2P_InitStruct->SGlist_Head;
    JPEG_SGDMA_H2P->SGL_TAIL = SGDMA_H2P_InitStruct->SGlist_Tail;
    JPEG_SGDMA_H2P->AOODT    = SGDMA_H2P_InitStruct->SGlist_Threshold;
}


/**
*\*\name    SGDMA_P2H_Init.
*\*\fun     Initializes the SGDMA_H2P peripheral according to SGDMA_H2P_InitStruct.
*\*\param   SGDMA_P2H_InitStruct
*\*\            - p2h_desc
*\*\                - desc_flags : Descriptor flag bits
*\*\                    - linkenable: Link Enable 
*\*\                        - 0 : DISABLE
*\*\                        - 1 : ENABLE
*\*\                    - startframe: Start of Frame 
*\*\                        - 0 : DISABLE
*\*\                        - 1 : ENABLE
*\*\                    - endframe: End of Frame 
*\*\                        - 0 : DISABLE
*\*\                        - 1 : ENABLE
*\*\                    - desccons: Descriptor Consumed 
*\*\                        - 0 : DISABLE
*\*\                        - 1 : ENABLE
*\*\                - blk_size : Block_Size
*\*\                    - 0x00000000 ~ 0xFFFFFFFF
*\*\                - blk_used : Block_Used
*\*\                    - 0x00000000 ~ 0xFFFFFFFF
*\*\                - blk_addr_low : The starting address of the data block [31:0]
*\*\                    - 0x00000000 ~ 0xFFFFFFFF
*\*\                - blk_addr_high : The starting address of the data block [63:32]
*\*\                    - 0x00000000
*\*\                - link_addr_low : Link to the next descriptor. Used when Link Enable = 1
*\*\                    - 0x00000000 ~ 0xFFFFFFFF
*\*\                - link_addr_high : Link to the next descriptor. Used when Link Enable = 1
*\*\                    - 0x00000000
*\*\            - max_burstsize : Maximum allowed size for an AXI4 MM burst
*\*\                - 0x00000000 ~ 0x00000100
*\*\            - SGlist_size : Scatter-Gather List Size
*\*\                - 0x00000000 ~ 0x0000FFFF
*\*\            - desclist_type : The descriptor list structure type
*\*\                - SGDMA_DESCLIST_LIST
*\*\                - SGDMA_DESCLIST_RING
*\*\            - descstored_type : The descriptor storage location
*\*\                - SGDMA_DESC_CSR
*\*\                - SGDMA_DESC_MEMORY
*\*\            - DMA_EOF_type : DMA operation mode on EOF
*\*\                - SGDMA_EOF_PAUSEDMA
*\*\                - SGDMA_EOF_RESUMEDMA
*\*\            - DMA_burst_type : DMA burst type
*\*\                - SGDMA_BURST_FIXED
*\*\                - SGDMA_BURST_INCR
*\*\return  none.
**/
void SGDMA_P2H_Init(SGDMA_P2H_InitType* SGDMA_P2H_InitStruct)
{
    uint32_t resg_temp;
    
    SGDMA_Reset(JPEG_SGDMA_P2H);
    /* Module enable */
    JPEG_SGDMA_P2H->CTRL |= JPEGDMA_CTRL_EN;
    
    /* Maximum allowed size for an AXI4 MM burst */
    JPEG_SGDMA_P2H->MBSIZE = SGDMA_P2H_InitStruct->max_burstsize;
    
    /* H2P DMA initial configuration */
    resg_temp = JPEG_SGDMA_P2H->CTRL;
    resg_temp &= (~(JPEGDMA_CTRL_MMODE | JPEGDMA_CTRL_OPMODE));
    resg_temp |= SGDMA_P2H_InitStruct->desclist_type;
    resg_temp |= SGDMA_P2H_InitStruct->descstored_type;
    resg_temp |= SGDMA_P2H_InitStruct->DMA_burst_type;
    resg_temp |= SGDMA_P2H_InitStruct->DMA_EOF_type;
    JPEG_SGDMA_P2H->CTRL = resg_temp;
    
    /* Determine descriptor location */
    if(SGDMA_P2H_InitStruct->descstored_type == SGDMA_DESC_MEMORY)
    {
        /* Set base address of the SG List */
        JPEG_SGDMA_P2H->SGLPL = (uint32_t)&SGDMA_P2H_InitStruct->p2h_desc;
    }
    else
    {
        JPEG_SGDMA_P2H->DESCF = *(uint32_t*)(&SGDMA_P2H_InitStruct->p2h_desc);
        JPEG_SGDMA_P2H->DESC_MBADDL = SGDMA_P2H_InitStruct->p2h_desc.blk_addr_low;
        JPEG_SGDMA_P2H->DESC_MBADDH = SGDMA_P2H_InitStruct->p2h_desc.blk_addr_high;
        JPEG_SGDMA_P2H->DESC_MBSIZE = SGDMA_P2H_InitStruct->p2h_desc.blk_size;
        JPEG_SGDMA_P2H->DESC_MUS = SGDMA_P2H_InitStruct->p2h_desc.blk_used;
        /* Determine if linkenable is enabled */
        if(SGDMA_P2H_InitStruct->p2h_desc.desc_flags.bits.linkenable != DISABLE)
        {
            JPEG_SGDMA_P2H->DESC_LINKL = SGDMA_P2H_InitStruct->p2h_desc.link_addr_low;
            JPEG_SGDMA_P2H->DESC_LINKH = SGDMA_P2H_InitStruct->p2h_desc.link_addr_high;
        }
        else
        {
            /* no process */
        }
    }
    
    /* Set size of the SG List */
    JPEG_SGDMA_P2H->SGL_SIZE = SGDMA_P2H_InitStruct->SGlist_size;
    JPEG_SGDMA_P2H->SGL_HEAD = SGDMA_P2H_InitStruct->SGlist_Head;
    JPEG_SGDMA_P2H->SGL_TAIL = SGDMA_P2H_InitStruct->SGlist_Tail;
    JPEG_SGDMA_P2H->AOODT    = SGDMA_P2H_InitStruct->SGlist_Threshold;
}

/**
*\*\name   SGDMA_Start.
*\*\fun    Start the SGDMA P2H/H2P module.
*\*\param  SGDMAx :
*\*\          - JPEG_SGDMA_P2H
*\*\          - JPEG_SGDMA_H2P
*\*\return none
**/
void SGDMA_Start(JPEG_SGDMA_Module *SGDMAx)
{
    /* DMA start */
    SGDMAx->CTRL |= JPEGDMA_CTRL_START;
}

/**
*\*\name    SGDMA_ConfigInt
*\*\fun     Enables or disables the specified SGDMA interrupts.
*\*\param   SGDMAx (The input parameters must be the following values):
*\*\          - JPEG_SGDMA_P2H
*\*\          - JPEG_SGDMA_H2P
*\*\param   SGDMA_INT (The input parameters must be the following values):
*\*\            - SGDMA_INTSTS_WDATAERREN    AXI MM Write Error when writing data
*\*\            - SGDMA_INTSTS_RDATAERR      AXI MM Read Error when reading data
*\*\            - SGDMA_INTSTS_WDESCERR      AXI MM Write Error when writing a descriptor
*\*\            - SGDMA_INTSTS_RDESCERR      AXI MM Read Error when reading a descriptor
*\*\            - SGDMA_INTSTS_EOD           End-Of-Descriptor
*\*\            - SGDMA_INTSTS_AOOD          Channel is Almost Out of Descriptors
*\*\            - SGDMA_INTSTS_OOD           Out Of Descriptors
*\*\            - SGDMA_INTSTS_EOFIN         End-Of-Frame sampled at the input of the channel
*\*\            - SGDMA_INTSTS_EOFOUT        End-Of-Frame sampled at the output of the channel
*\*\            - SGDMA_INTSTS_GINT          Global interrupt status bit for the Channel
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void SGDMA_ConfigInt(JPEG_SGDMA_Module* SGDMAx, uint32_t SGDMA_INT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SGDMAx->IE |= SGDMA_INT;
    }
    else
    {
        SGDMAx->IE &= (~SGDMA_INT);
    }
}


/**
*\*\name   SGDMAx_GetFlagStatus.
*\*\fun    Check whether the specified SGDMA flag is set or not.
*\*\param  SGDMAx :
*\*\          - JPEG_SGDMA_P2H
*\*\          - JPEG_SGDMA_H2P
*\*\param  Flag :
*\*\          - SGDMA_INTSTS_WDATAERREN    AXI MM Write Error when writing data
*\*\          - SGDMA_INTSTS_RDATAERR      AXI MM Read Error when reading data
*\*\          - SGDMA_INTSTS_WDESCERR      AXI MM Write Error when writing a descriptor
*\*\          - SGDMA_INTSTS_RDESCERR      AXI MM Read Error when reading a descriptor
*\*\          - SGDMA_INTSTS_EOD           End-Of-Descriptor
*\*\          - SGDMA_INTSTS_AOOD          Channel is Almost Out of Descriptors
*\*\          - SGDMA_INTSTS_OOD           Out Of Descriptors
*\*\          - SGDMA_INTSTS_EOFIN         End-Of-Frame sampled at the input of the channel
*\*\          - SGDMA_INTSTS_EOFOUT        End-Of-Frame sampled at the output of the channel
*\*\          - SGDMA_INTSTS_GINT          Global interrupt status bit for the Channel
*\*\          - SGDMA_INTSTS_BUSY          H2P/P2H is processing a transfer
*\*\return FlagStatus
*\*\          - RESET
*\*\          - SET
**/
FlagStatus SGDMAx_GetFlagStatus(JPEG_SGDMA_Module* SGDMAx, uint32_t Flag)
{
    FlagStatus status_value;
    if((SGDMAx->STS & Flag) == Flag )
    {
        status_value = SET;
    }
    else
    {
        status_value = RESET;
    }
    return status_value;
}


/**
*\*\name   SGDMAx_GetIntStatus.
*\*\fun    Check whether the specified SGDMA interrupt is set or not.
*\*\param  SGDMAx :
*\*\          - JPEG_SGDMA_P2H
*\*\          - JPEG_SGDMA_H2P
*\*\param  Flag :
*\*\          - SGDMA_INTSTS_WDATAERREN    AXI MM Write Error when writing data
*\*\          - SGDMA_INTSTS_RDATAERR      AXI MM Read Error when reading data
*\*\          - SGDMA_INTSTS_WDESCERR      AXI MM Write Error when writing a descriptor
*\*\          - SGDMA_INTSTS_RDESCERR      AXI MM Read Error when reading a descriptor
*\*\          - SGDMA_INTSTS_EOD           End-Of-Descriptor
*\*\          - SGDMA_INTSTS_AOOD          Channel is Almost Out of Descriptors
*\*\          - SGDMA_INTSTS_OOD           Out Of Descriptors
*\*\          - SGDMA_INTSTS_EOFIN         End-Of-Frame sampled at the input of the channel
*\*\          - SGDMA_INTSTS_EOFOUT        End-Of-Frame sampled at the output of the channel
*\*\          - SGDMA_INTSTS_GINT          Global interrupt status bit for the Channel 
*\*\return FlagStatus
*\*\          - RESET
*\*\          - SET
**/
FlagStatus SGDMAx_GetIntStatus(JPEG_SGDMA_Module* SGDMAx, uint32_t Flag)
{
    FlagStatus status_value;
    if((SGDMAx->INTSTS & Flag) == Flag )
    {
        status_value = SET;
    }
    else
    {
        status_value = RESET;
    }
    return status_value;
}

/**
*\*\name   SGDMAx_GetFlagStatus.
*\*\fun    Clears the SGDMAx's pending flags..
*\*\param  SGDMAx :
*\*\          - JPEG_SGDMA_P2H
*\*\          - JPEG_SGDMA_H2P
*\*\param  Flag :
*\*\          - SGDMA_INTSTS_EOD           End-Of-Descriptor
*\*\          - SGDMA_INTSTS_AOOD          Channel is Almost Out of Descriptors
*\*\          - SGDMA_INTSTS_OOD           Out Of Descriptors
*\*\          - SGDMA_INTSTS_EOFIN         End-Of-Frame sampled at the input of the channel
*\*\          - SGDMA_INTSTS_EOFOUT        End-Of-Frame sampled at the output of the channel
*\*\return none
**/
void SGDMAx_ClrFlag(JPEG_SGDMA_Module* SGDMAx, uint32_t Flag)
{
    SGDMAx->STS = Flag;
}


/***** JPEG BRC module ****/
/**
*\*\name    JPEGBRC_Init.
*\*\fun     Initializes the JPEG BRC peripheral according to JPEGBRC_InitStruct.
*\*\param   JPEGBRC_InitStruct
*\*\            - buffer_addr
*\*\                - 0x00000000 ~ 0xFFFFFFFF
*\*\            - buffer_size
*\*\                - 0x0000 ~ 0xFFFF
*\*\            - upsample_mode
*\*\                - 0x00 ~ 0x03
*\*\return FlagStatus
*\*\            - ERROR
*\*\            - SUCCESS
**/
ErrorStatus JPEGBRC_Init(JPEGBRC_InitType* JPEGBRC_InitStruct)
{
    ErrorStatus status_value;
    uint32_t timeout_value = 0x10000;
    
    /* BRC module init*/
    JPEG_BRC->INIT |= JPEGBRC_INIT_INIT;
    while(timeout_value--)
    {
        if((JPEG_BRC->INIT & JPEGBRC_INIT_INITF) == JPEGBRC_INIT_INITF)
        {
            JPEG_BRC->INIT &= (~JPEGBRC_INIT_INIT);
            break;
        }
    }
    
    if(timeout_value == 0)
    {
        status_value = ERROR;
    }
    else
    {
        status_value = SUCCESS;
    }
    
    if(status_value == SUCCESS)
    {
        JPEG_BRC->BUFBADDR = JPEGBRC_InitStruct->buffer_addr;
        JPEG_BRC->BUFSIZE  = JPEGBRC_InitStruct->buffer_size;
        JPEG_BRC->USMODE   = JPEGBRC_InitStruct->upsample_mode;
    }
    return status_value;
}

/**
*\*\name    JPEGBRC_Enable
*\*\fun     Enables or disables the specified JPEGBRC peripheral.
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void JPEGBRC_Enable(FunctionalState Cmd)
{
   if (Cmd != DISABLE)
    {
        /* Enable JPEGBRC modelu */
        JPEG_BRC->EN |= JPEGBRC_EN_EN;
    }
    else
    {
        /* Disable JPEGBRC modelu */
        JPEG_BRC->EN &= (~JPEGBRC_EN_EN);
    }
}


/***** JPEG RBC module ****/
/**
*\*\name    JPEGRBC_Init.
*\*\fun     Initializes the JPEG BRC peripheral according to JPEGRBC_InitStruct.
*\*\param   JPEGRBC_InitStruct
*\*\            - pixel_format
*\*\                - JPEGRBC_4_4_4_NONINTERLEAVED
*\*\                - JPEGRBC_4_2_2_NONINTERLEAVED
*\*\                - JPEGRBC_4_2_0_NONINTERLEAVED
*\*\                - JPEGRBC_MONOCHROME
*\*\                - JPEGRBC_4_4_4_INTERLEAVED
*\*\                - JPEGRBC_4_2_2_INTERLEAVED
*\*\                - JPEGRBC_4_2_0_INTERLEAVED
*\*\            - sample_order
*\*\                - JPEGRBC_MSBSAMPLE
*\*\                - JPEGRBC_LSBSAMPLE
*\*\            - frame_width
*\*\                - 0x0000 ~ 0xFFFF
*\*\            - frame_height
*\*\                - 0x0001 ~ 0x10000
*\*\            - component0names
*\*\                - 0x00 ~ 0xFF
*\*\            - component1names
*\*\                - 0x00 ~ 0xFF
*\*\            - component2names
*\*\                - 0x00 ~ 0xFF
*\*\            - C0startaddress
*\*\                - 0x00000000 ~ 0xFFFFFFFF
*\*\            - C0buffersize
*\*\                - 0x001 ~ 0x400
*\*\return FlagStatus
*\*\            - ERROR
*\*\            - SUCCESS
**/
ErrorStatus JPEGRBC_Init(JPEGRBC_InitType* JPEGRBC_InitStruct)
{
    ErrorStatus status_value = SUCCESS;
    uint32_t timeout_value = 0x10000;
    uint32_t width_mcus;
    uint32_t height_mcus;
    
    JPEG_RBC->PFORM = JPEGRBC_InitStruct->pixel_format;
    JPEG_RBC->CNAME = (JPEGRBC_InitStruct->component0names | \
                      (JPEGRBC_InitStruct->component1names << REG_BIT8_OFFSET) | \
                      (JPEGRBC_InitStruct->component2names << REG_BIT16_OFFSET));
    JPEG_RBC->C0SADD = JPEGRBC_InitStruct->C0startaddress;
    JPEG_RBC->C0EADD = JPEGRBC_InitStruct->C0buffersize;
    JPEG_RBC->FRMH   = JPEGRBC_InitStruct->frame_height - 1;
    JPEG_RBC->HHALF  = ((JPEGRBC_InitStruct->frame_height + 1U) >> REG_BIT1_OFFSET) - 1;
    
    if(JPEGRBC_InitStruct->pixel_format == JPEGRBC_4_4_4_NONINTERLEAVED)
    {
        JPEG_RBC->FRMW   = JPEGRBC_InitStruct->frame_width;
        /* Round up by multiples of 8 */
        width_mcus = (JPEGRBC_InitStruct->frame_width + 7U) >> (REG_BIT3_OFFSET);
        /* Round up by multiples of 8 */
        height_mcus = (JPEGRBC_InitStruct->frame_height + 7U) >> (REG_BIT3_OFFSET);
        JPEG_RBC->BPS0 = (width_mcus * height_mcus - 1U);
        JPEG_RBC->BPS12 = (width_mcus * height_mcus - 1U);
        
        JPEG_RBC->ROWS0 = height_mcus - 1U;
        JPEG_RBC->ROWS12 = height_mcus - 1U;
        
        JPEG_RBC->BLSS0  = width_mcus * 8U;
        JPEG_RBC->BLSS12  = width_mcus * 8U;
        
        JPEG_RBC->BPRS0 = (width_mcus - 1U);
        JPEG_RBC->BPRS12 = (width_mcus - 1U);
        
    }
    else if(JPEGRBC_InitStruct->pixel_format == JPEGRBC_4_2_2_NONINTERLEAVED)
    {
        JPEG_RBC->FRMW   = JPEGRBC_InitStruct->frame_width;
        /* Round up by multiples of 8 */
        width_mcus = (JPEGRBC_InitStruct->frame_width + 7U) >> (REG_BIT3_OFFSET);
        /* Round up by multiples of 8 */
        height_mcus = (JPEGRBC_InitStruct->frame_height + 7U) >> (REG_BIT3_OFFSET);
        JPEG_RBC->BPS0 = (width_mcus * height_mcus - 1U);
        
        JPEG_RBC->BLSS0  = width_mcus * 8U;
        
        JPEG_RBC->BPRS0 = (width_mcus - 1U);
        /* Round up by multiples of 16 */
        width_mcus = (JPEGRBC_InitStruct->frame_width + 15U) >> (REG_BIT4_OFFSET);
        JPEG_RBC->BPS12 = (width_mcus * height_mcus - 1U);
        
        JPEG_RBC->ROWS0 = height_mcus - 1U;
        JPEG_RBC->ROWS12 = height_mcus - 1U;
        
        JPEG_RBC->BLSS12  = width_mcus * 8U;
        
        JPEG_RBC->BPRS12 = (width_mcus - 1U);
    }
    else if(JPEGRBC_InitStruct->pixel_format == JPEGRBC_4_2_0_NONINTERLEAVED)
    {
        JPEG_RBC->FRMW   = JPEGRBC_InitStruct->frame_width;
        /* Round up by multiples of 8 */
        width_mcus = (JPEGRBC_InitStruct->frame_width + 7U) >> (REG_BIT3_OFFSET);
        /* Round up by multiples of 8 */
        height_mcus = (JPEGRBC_InitStruct->frame_height + 7U) >> (REG_BIT3_OFFSET);
        JPEG_RBC->BPS0 = (width_mcus * height_mcus - 1U);
        
        JPEG_RBC->ROWS0 = height_mcus - 1U;
        
        JPEG_RBC->BLSS0  = width_mcus * 8U;
        
        JPEG_RBC->BPRS0 = (width_mcus - 1U);

        /* Round up by multiples of 16 */
        width_mcus = (JPEGRBC_InitStruct->frame_width + 15U) >> (REG_BIT4_OFFSET);
        /* Round up by multiples of 16 */
        height_mcus = (JPEGRBC_InitStruct->frame_height + 15U) >> (REG_BIT4_OFFSET);
        JPEG_RBC->BPS12 = (width_mcus * height_mcus - 1U);
        
        JPEG_RBC->ROWS12 = height_mcus - 1U;
        
        JPEG_RBC->BLSS12  = width_mcus * 8U;
        
        JPEG_RBC->BPRS12 = (width_mcus - 1U);
    }
    else if(JPEGRBC_InitStruct->pixel_format == JPEGRBC_MONOCHROME)
    {
        JPEG_RBC->FRMW   = JPEGRBC_InitStruct->frame_width;
        /* Round up by multiples of 8 */
        width_mcus = (JPEGRBC_InitStruct->frame_width + 7U) >> (REG_BIT3_OFFSET);
        /* Round up by multiples of 8 */
        height_mcus = (JPEGRBC_InitStruct->frame_height + 7U) >> (REG_BIT3_OFFSET);
        JPEG_RBC->BPS0 = (width_mcus * height_mcus - 1U);
        JPEG_RBC->BPS12 = (width_mcus * height_mcus - 1U);
        
        JPEG_RBC->ROWS0 = height_mcus - 1U;
        JPEG_RBC->ROWS12 = height_mcus - 1U;
        
        JPEG_RBC->BPRS0 = (width_mcus - 1U);
        JPEG_RBC->BPRS12 = (width_mcus - 1U);
        
        JPEG_RBC->BLSS0  = width_mcus * 8U;
        JPEG_RBC->BLSS12  = width_mcus * 8U;
    }
    else if(JPEGRBC_InitStruct->pixel_format == JPEGRBC_4_4_4_INTERLEAVED)
    {
        JPEG_RBC->FRMW   = JPEGRBC_InitStruct->frame_width * 3U;
        /* Round up by multiples of 8 */
        width_mcus = (JPEGRBC_InitStruct->frame_width + 7U) >> (REG_BIT3_OFFSET);
        /* Round up by multiples of 8 */
        height_mcus = (JPEGRBC_InitStruct->frame_height + 7U) >> (REG_BIT3_OFFSET);
        JPEG_RBC->BPS0 = (width_mcus * height_mcus *3U - 1U);
        JPEG_RBC->BPS12 = (width_mcus * height_mcus *3U - 1U);
        
        JPEG_RBC->ROWS0 = height_mcus - 1U;
        JPEG_RBC->ROWS12 = height_mcus - 1U;
        
        JPEG_RBC->BLSS0  = width_mcus * 8U * 3U;
        JPEG_RBC->BLSS12  = width_mcus * 8U * 3U;
        
        JPEG_RBC->BPRS0 = (width_mcus * 3U - 1U);
        JPEG_RBC->BPRS12 = (width_mcus * 3U - 1U);
    }
    else if(JPEGRBC_InitStruct->pixel_format == JPEGRBC_4_2_2_INTERLEAVED)
    {
        JPEG_RBC->FRMW   = JPEGRBC_InitStruct->frame_width * 2U;
        /* Round up by multiples of 16 */
        width_mcus = (JPEGRBC_InitStruct->frame_width + 15U) >> (REG_BIT4_OFFSET);
        /* Round up by multiples of 8 */
        height_mcus = (JPEGRBC_InitStruct->frame_height + 7U) >> (REG_BIT3_OFFSET);
        JPEG_RBC->BPS0 = (width_mcus * height_mcus *4U - 1U);
        JPEG_RBC->BPS12 = (width_mcus * height_mcus *4U - 1U);
        
        JPEG_RBC->ROWS0 = height_mcus - 1U;
        JPEG_RBC->ROWS12 = height_mcus - 1U;
        
        JPEG_RBC->BLSS0  = width_mcus * 8 * 4U;
        JPEG_RBC->BLSS12  = width_mcus * 8 * 4U;
        
        JPEG_RBC->BPRS0 = (width_mcus * 4U - 1U);
        JPEG_RBC->BPRS12 = (width_mcus * 4U - 1U);
    }
    else if(JPEGRBC_InitStruct->pixel_format == JPEGRBC_4_2_0_INTERLEAVED)
    {
        JPEG_RBC->FRMW   = JPEGRBC_InitStruct->frame_width * 3U;
        /* Round up by multiples of 16 */
        width_mcus = (JPEGRBC_InitStruct->frame_width + 15U) >> (REG_BIT4_OFFSET);
        /* Round up by multiples of 16 */
        height_mcus = (JPEGRBC_InitStruct->frame_height + 15U) >> (REG_BIT4_OFFSET);
        JPEG_RBC->BPS0 = (width_mcus * height_mcus *6U - 1U);
        JPEG_RBC->BPS12 = (width_mcus * height_mcus *6U - 1U);
        
        JPEG_RBC->ROWS0 = height_mcus - 1U;
        JPEG_RBC->ROWS12 = height_mcus - 1U;
        
        JPEG_RBC->BLSS0  = width_mcus * 8U * 6U;
        JPEG_RBC->BLSS12  = width_mcus * 8U * 6U;
        
        JPEG_RBC->BPRS0 = (width_mcus * 6U - 1U);
        JPEG_RBC->BPRS12 = (width_mcus * 6U - 1U);
    }
    else
    {
        /* no process */
    }
    
    /* RBC module init*/
    JPEG_RBC->INIT |= JPEGRBC_INIT_INIT;
    while((JPEG_RBC->INIT & JPEGRBC_INIT_INITF) != JPEGRBC_INIT_INITF)
    {
        timeout_value--;
        if(timeout_value == 0U)
        {
            status_value = ERROR;
            break;
        }
    }
    JPEG_RBC->INIT &= (~JPEGRBC_INIT_INIT);
    
    return status_value;
}


/**
*\*\name    JPEGRBC_Enable
*\*\fun     Enables or disables the specified JPEGRBC peripheral.
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void JPEGRBC_Enable(FunctionalState Cmd)
{
   if (Cmd != DISABLE)
    {
        /* Enable JPEGRBC module */
        JPEG_RBC->EN |= JPEGRBC_EN_EN;
    }
    else
    {
        /* Disable JPEGRBC module */
        JPEG_RBC->EN &= (~JPEGRBC_EN_EN);
    }
}

/***** JPEG DEC module ****/

/**
*\*\name    JPEGDEC_Enable
*\*\fun     Enables or disables the specified JPEGDEC peripheral.
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void JPEGDEC_Enable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable JPEGDEC modelu */
        JPEG_DEC->MODE |= JPEGDEC_MODE_EN;
    }
    else
    {
        /* Disable JPEGDEC modelu */
        JPEG_DEC->MODE &= (~JPEGDEC_MODE_EN);
    }
}


/**
*\*\name   JPEGDEC_GetFlagStatus.
*\*\fun    Check whether the specified JPEGDEC flag is set or not.
*\*\param  Flag :
*\*\          - JPEGDEC_ERROR_HTERR    A Huffman table referenced in a scan (SOS header) is invalid
*\*\          - JPEGDEC_ERROR_QTERR    A Quantisation table referenced in a component referenced in a scan (SOS header) selected an invalid Quantisation table
*\*\          - JPEGDEC_ERROR_CERR     A component referenced in the scan header (SOS) was not defined in the previous frame header (SOF)
*\*\          - JPEGDEC_ERROR_HUF      Huffman decode error detected
*\*\          - JPEGDEC_ERROR_UNEXP    Unexpected marker detected
*\*\          - JPEGDEC_ERROR_UNK      Unknown marker detected 
*\*\return FlagStatus
*\*\          - RESET
*\*\          - SET
**/
FlagStatus JPEGDEC_GetFlagStatus(uint32_t Flag)
{
    FlagStatus status_value;
    if((JPEG_DEC->ERROR & Flag) == Flag )
    {
        status_value = SET;
    }
    else
    {
        status_value = RESET;
    }
    return status_value;
}


/**
*\*\name   JPEGDEC_GetUNKErrorAddress.
*\*\fun    Get Unknown marker error address.
*\*\param  none
*\*\return address
*\*\          - 0x00000000~0xFFFFFFFF
**/
uint32_t JPEGDEC_GetUNKErrorAddress(void)
{
    return JPEG_DEC->UNLOC;
}

/**
*\*\name   JPEGDEC_GetUNEXPErrorAddress.
*\*\fun    Get Unexpected marker error address.
*\*\param  none
*\*\return address
*\*\          - 0x00000000~0xFFFFFFFF
**/
uint32_t JPEGDEC_GetUNEXPErrorAddress(void)
{
    return JPEG_DEC->UELOC;
}

/**
*\*\name   JPEGDEC_GetHESYMErrorAddress.
*\*\fun    Get the Huffman symbol that is in error.
*\*\param  none
*\*\return address
*\*\          - 0x0000~0xFFFF
**/
uint16_t JPEGDEC_GetHESYMErrorAddress(void)
{
    return ((uint16_t)JPEG_DEC->HESYM & JPEGDEC_HESYM_HESYM);
}

/**
*\*\name   JPEGDEC_GetHESYMECSErrorAddress.
*\*\fun    Get Huffman ECS Number Symbol.
*\*\param  none
*\*\return address
*\*\          - 0x00000000~0xFFFFFFFF
**/
uint32_t JPEGDEC_GetHESYMECSErrorAddress(void)
{
    return JPEG_DEC->HESYMECS;
}

/**
*\*\name   JPEGDEC_GetHUFSErrorAddress.
*\*\fun    Get Unexpected marker error address.
*\*\param  none
*\*\return address
*\*\          - 0x00000000~0xFFFFFFFF
**/
uint32_t JPEGDEC_GetHUFSErrorAddress(void)
{
    return JPEG_DEC->HUF_SELOC;
}


/**
*\*\name   JPEGDEC_TableAccessRequest.
*\*\fun    JPEG DEC Table Access Request.
*\*\param  Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return status
*\*\          - ERROR
*\*\          - SUCCESS
**/
ErrorStatus JPEGDEC_TableAccessRequest(FunctionalState Cmd)
{
    ErrorStatus status = SUCCESS;
    uint32_t count_value = 0;
    
    if(Cmd == DISABLE)
    {
        JPEG_DEC->TAB_ACCREQ &= (~JPEGDEC_TAB_ACCREQ_AQEQ);
    }
    else
    {
        JPEG_DEC->TAB_ACCREQ |= JPEGDEC_TAB_ACCREQ_AQEQ;
    
        while((JPEG_DEC->TAB_ACCREQ & JPEGDEC_TAB_ACCREQ_AOK) != JPEGDEC_TAB_ACCREQ_AOK)
        {
            count_value++;
            if(count_value > 0x1000)
            {
                status = ERROR;
                break;
            }
        }
    }
    
    return status;
}

/**
*\*\name   JPEGDEC_GetHUFSErrorAddress.
*\*\fun    Get Unexpected marker error address.
*\*\param  TableAddress
*\*\          - JPEGDEC_EOB0_ADDRESS
*\*\          - JPEGDEC_EOB1_ADDRESS
*\*\          - JPEGDEC_EOB2_ADDRESS
*\*\          - JPEGDEC_EOB3_ADDRESS
*\*\param  EOBSymbol
*\*\          - 0x0000~0xFFFF
*\*\param  EOBSymbolMask
*\*\          - 0x0000~0xFFFF
*\*\return none
**/
void JPEGDEC_SetHUFTable_EOB(uint32_t TableAddress,uint32_t EOBSymbol,uint32_t EOBSymbolMask)
{
    *(uint32_t*)(JPEG_DEC_BASE + TableAddress) = (EOBSymbol | (EOBSymbolMask << REG_BIT16_OFFSET));
}


/**
*\*\name   JPEGDEC_SetHuffTable.
*\*\fun    Set Huffman table parameters.
*\*\param  TableType
*\*\          - JPEGDEC_HUFFTABLE
*\*\          - JPEGDEC_DVECTORTABLE
*\*\          - JPEGDEC_IVECTORTABLE
*\*\          - JPEGDEC_HUFFACCTABLE
*\*\param  Tableselector
*\*\          - JPEGDEC_DCTABLE
*\*\          - JPEGDEC_ACTABLE
*\*\param  TableNum
*\*\          - JPEGDEC_HUFFTABLE_0
*\*\          - JPEGDEC_HUFFTABLE_1
*\*\          - JPEGDEC_HUFFTABLE_2
*\*\          - JPEGDEC_HUFFTABLE_3
*\*\param  &Value
*\*\          - 0x00000000~0xFFFFFFFF
*\*\param  Count
*\*\          - 0x00000000~0xFFFFFFFF
*\*\return status
*\*\          - ERROR
*\*\          - SUCCESS
**/
ErrorStatus JPEGDEC_SetHuffTable(uint32_t TableType,uint32_t Tableselector,uint32_t TableNum,uint32_t* Value,uint32_t Count)
{
    ErrorStatus status = SUCCESS;
    uint32_t regtemp = 0U;
    
    regtemp = (TableType | Tableselector | TableNum);
    JPEG_DEC->HUF_ADDR = regtemp;
    
    if(Count > JPEG_DEC->HUF_REM)
    {
        status = ERROR;
    }
    else
    {
        /* no process */
    }
    
    for(regtemp = 0;regtemp<Count;regtemp++)
    {
        JPEG_DEC->HUF_DATA = Value[regtemp];
    }
    
    return status;
}


/**
*\*\name   JPEGDEC_SetQuantiTable.
*\*\fun    Set Quantisation table parameters.
*\*\param  TableAddress
*\*\          - JPEGDEC_QT0_ADDRESS
*\*\          - JPEGDEC_QT1_ADDRESS
*\*\          - JPEGDEC_QT2_ADDRESS
*\*\          - JPEGDEC_QT3_ADDRESS
*\*\param  &Value
*\*\          - 0x00000000~0xFFFFFFFF
*\*\param  Count
*\*\          - 0x00~0x40
*\*\return none
**/
void JPEGDEC_SetQuantiTable(uint32_t TableAddress,uint8_t* Value,uint32_t Count)
{
    uint32_t num;
    
    for(num = 0;num<Count;num++)
    {
        *(uint32_t*)(JPEG_DEC_BASE + TableAddress + num*4U) = Value[num];
    }
}


/***** JPEG ENC module ****/
/**
*\*\name    JPEGENC_Init.
*\*\fun     Initializes the JPEG_ENC peripheral according to JPEGENC_InitStruct.
*\*\param   JPEGENC_InitStruct
*\*\            - header_address
*\*\                - NULL
*\*\                - 0x00000000~0xFFFFFFFF
*\*\            - header_size
*\*\                - 0x000~0x800
*\*\            - hufftab0_header_address
*\*\                - NULL
*\*\                - 0x00000000~0xFFFFFFFF
*\*\            - hufftab0_header_size
*\*\                - 0x000~0x800
*\*\            - hufftab1_header_address
*\*\                - NULL
*\*\                - 0x00000000~0xFFFFFFFF
*\*\            - hufftab1_header_size
*\*\                - 0x000~0x800
*\*\            - hufftab2_header_address
*\*\                - NULL
*\*\                - 0x00000000~0xFFFFFFFF
*\*\            - hufftab2_header_size
*\*\                - 0x000~0x800
*\*\            - hufftab3_header_address
*\*\                - NULL
*\*\                - 0x00000000~0xFFFFFFFF
*\*\            - hufftab3_header_size
*\*\                - 0x000~0x800
*\*\            - footer_address
*\*\                - NULL
*\*\                - 0x00000000~0xFFFFFFFF
*\*\            - footer_size
*\*\                - 0x000~0x800
*\*\            - output_select(The following parameters can be input simultaneously in the form of |:)
*\*\                - JPEGENC_OUTPUT_NOTHING
*\*\                - JPEGENC_OUTPUT_QT0
*\*\                - JPEGENC_OUTPUT_QT1
*\*\                - JPEGENC_OUTPUT_QT2
*\*\                - JPEGENC_OUTPUT_QT3
*\*\                - JPEGENC_OUTPUT_HT0
*\*\                - JPEGENC_OUTPUT_HT1
*\*\                - JPEGENC_OUTPUT_HT2
*\*\                - JPEGENC_OUTPUT_HT3
*\*\                - JPEGENC_OUTPUT_ONLY
*\*\                - JPEGENC_OUTPUT_NOECS
*\*\            - QT0_address
*\*\                - NULL
*\*\                - 0x00000000~0xFFFFFFFF
*\*\            - QT1_address
*\*\                - NULL
*\*\                - 0x00000000~0xFFFFFFFF
*\*\            - QT2_address
*\*\                - NULL
*\*\                - 0x00000000~0xFFFFFFFF
*\*\            - QT3_address
*\*\                - NULL
*\*\                - 0x00000000~0xFFFFFFFF
*\*\            - restart_interval
*\*\                - JPEGENC_RESSART_ENABLE
*\*\                - JPEGENC_RESSART_DISABLE
*\*\            - interval_num
*\*\                - 0x00000001~0x10000000
*\*\            - C0QT_select
*\*\                - 0x00~0x03
*\*\            - C1QT_select
*\*\                - 0x00~0x03
*\*\            - C2QT_select
*\*\                - 0x00~0x03
*\*\            - C3QT_select
*\*\                - 0x00~0x03
*\*\            - C0HT_select
*\*\                - 0x00~0x03
*\*\            - C1HT_select
*\*\                - 0x00~0x03
*\*\            - C2HT_select
*\*\                - 0x00~0x03
*\*\            - C3HT_select
*\*\                - 0x00~0x03
*\*\            - Corereset
*\*\                - JPEGENC_CORERST_ENABLE
*\*\                - JPEGENC_CORERST_DISABLE
*\*\return status
*\*\          - ERROR
*\*\          - SUCCESS
**/
ErrorStatus JPEGENC_Init(JPEGENC_InitType* JPEGENC_InitStruct)
{
    ErrorStatus status = SUCCESS;
    uint32_t position_temp = 0U;
    uint32_t size_word;
    uint32_t cnt_value;
    uint32_t* pbuffer;
    
    /* Calculate the combined size of all tables */
    size_word = ((JPEGENC_InitStruct->header_size + 3U)/4U) + \
                 ((JPEGENC_InitStruct->hufftab0_header_size + 3U)/4U) + \
                 ((JPEGENC_InitStruct->hufftab1_header_size + 3U)/4U) + \
                 ((JPEGENC_InitStruct->hufftab2_header_size + 3U)/4U) + \
                 ((JPEGENC_InitStruct->hufftab3_header_size + 3U)/4U) + \
                 ((JPEGENC_InitStruct->footer_size + 3U)/4U);
    
    /* Total size exceeds limit, error returned */
    if(size_word > 0x200U)
    {
        return ERROR;
    }
    
    /* Huffman tables0 */
    if(JPEGENC_InitStruct->HuffmanTable0.DCcode_offset != NULL)
    {
        for(cnt_value = 0U;cnt_value < 12U;cnt_value++)
        {
            JPEG_ENC->HT0.DCOL[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable0.DCcode_offset[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable0.ACcode_offset != NULL)
    {
        for(cnt_value = 0U;cnt_value < 160U;cnt_value++)
        {
            JPEG_ENC->HT0.ACOL[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable0.ACcode_offset[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable0.DCcode_start != NULL)
    {
        for(cnt_value = 0U;cnt_value < 16U;cnt_value++)
        {
            JPEG_ENC->HT0.DCCODE[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable0.DCcode_start[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable0.ACcode_start != NULL)
    {
        for(cnt_value = 0U;cnt_value < 16U;cnt_value++)
        {
            JPEG_ENC->HT0.ACCODE[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable0.ACcode_start[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    JPEG_ENC->HT0.EOBS = JPEGENC_InitStruct->HuffmanTable0.EOBS;
    JPEG_ENC->HT0.ZRLS = JPEGENC_InitStruct->HuffmanTable0.ZRLS;
    
    /* Huffman tables1 */
    if(JPEGENC_InitStruct->HuffmanTable1.DCcode_offset != NULL)
    {
        for(cnt_value = 0U;cnt_value < 12U;cnt_value++)
        {
            JPEG_ENC->HT1.DCOL[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable1.DCcode_offset[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable1.ACcode_offset != NULL)
    {
        for(cnt_value = 0U;cnt_value < 160U;cnt_value++)
        {
            JPEG_ENC->HT1.ACOL[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable1.ACcode_offset[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable1.DCcode_start != NULL)
    {
        for(cnt_value = 0U;cnt_value < 16U;cnt_value++)
        {
            JPEG_ENC->HT1.DCCODE[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable1.DCcode_start[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable1.ACcode_start != NULL)
    {
        for(cnt_value = 0U;cnt_value < 16U;cnt_value++)
        {
            JPEG_ENC->HT1.ACCODE[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable1.ACcode_start[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    JPEG_ENC->HT1.EOBS = JPEGENC_InitStruct->HuffmanTable1.EOBS;
    JPEG_ENC->HT1.ZRLS = JPEGENC_InitStruct->HuffmanTable1.ZRLS;
    
    /* Huffman tables2 */
    if(JPEGENC_InitStruct->HuffmanTable2.DCcode_offset != NULL)
    {
        for(cnt_value = 0U;cnt_value < 12U;cnt_value++)
        {
            JPEG_ENC->HT2.DCOL[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable2.DCcode_offset[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable2.ACcode_offset != NULL)
    {
        for(cnt_value = 0U;cnt_value < 160U;cnt_value++)
        {
            JPEG_ENC->HT2.ACOL[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable2.ACcode_offset[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable2.DCcode_start != NULL)
    {
        for(cnt_value = 0U;cnt_value < 16U;cnt_value++)
        {
            JPEG_ENC->HT2.DCCODE[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable2.DCcode_start[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable2.ACcode_start != NULL)
    {
        for(cnt_value = 0U;cnt_value < 16U;cnt_value++)
        {
            JPEG_ENC->HT2.ACCODE[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable2.ACcode_start[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    JPEG_ENC->HT2.EOBS = JPEGENC_InitStruct->HuffmanTable2.EOBS;
    JPEG_ENC->HT2.ZRLS = JPEGENC_InitStruct->HuffmanTable2.ZRLS;
    
    /* Huffman tables3 */
    if(JPEGENC_InitStruct->HuffmanTable3.DCcode_offset != NULL)
    {
        for(cnt_value = 0U;cnt_value < 12U;cnt_value++)
        {
            JPEG_ENC->HT3.DCOL[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable3.DCcode_offset[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable3.ACcode_offset != NULL)
    {
        for(cnt_value = 0U;cnt_value < 160U;cnt_value++)
        {
            JPEG_ENC->HT3.ACOL[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable3.ACcode_offset[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable3.DCcode_start != NULL)
    {
        for(cnt_value = 0U;cnt_value < 16U;cnt_value++)
        {
            JPEG_ENC->HT3.DCCODE[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable3.DCcode_start[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    if(JPEGENC_InitStruct->HuffmanTable3.ACcode_start != NULL)
    {
        for(cnt_value = 0U;cnt_value < 16U;cnt_value++)
        {
            JPEG_ENC->HT3.ACCODE[cnt_value] = (uint32_t)JPEGENC_InitStruct->HuffmanTable3.ACcode_start[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    JPEG_ENC->HT3.EOBS = JPEGENC_InitStruct->HuffmanTable3.EOBS;
    JPEG_ENC->HT3.ZRLS = JPEGENC_InitStruct->HuffmanTable3.ZRLS;
    
    /* File frame header */
    if(JPEGENC_InitStruct->header_address != NULL)
    {
        size_word = ((JPEGENC_InitStruct->header_size + 3U)/4U);
    
        pbuffer = (uint32_t*)JPEGENC_InitStruct->header_address;
        
        for(cnt_value = 0; cnt_value< size_word;cnt_value++)
        {
            JPEG_ENC->HFBUFFER[cnt_value] = pbuffer[cnt_value];
        }
        
        JPEG_ENC->HEADD = JPEGENC_InitStruct->header_size - 1;
        position_temp = size_word;
    }
    else
    {
        JPEG_ENC->HEADD = 0x00U;
    }
    
    /* Huffman table0 frame header */
    if(JPEGENC_InitStruct->hufftab0_header_address != NULL)
    {
        size_word = ((JPEGENC_InitStruct->hufftab0_header_size + 3U)/4U);
    
        pbuffer = (uint32_t*)JPEGENC_InitStruct->hufftab0_header_address;
        
        for(cnt_value = 0; cnt_value< size_word;cnt_value++)
        {
            JPEG_ENC->HFBUFFER[cnt_value + position_temp] = pbuffer[cnt_value];
        }
        
        JPEG_ENC->HUFTAB0E = position_temp * 4U + JPEGENC_InitStruct->hufftab0_header_size - 1;
        position_temp = position_temp + size_word;
    }
    else
    {
        JPEG_ENC->HUFTAB0E = 0x00U;
    }
    
    /* Huffman table1 frame header */
    if(JPEGENC_InitStruct->hufftab1_header_address != NULL)
    {
        size_word = ((JPEGENC_InitStruct->hufftab1_header_size + 3U)/4U);
    
        pbuffer = (uint32_t*)JPEGENC_InitStruct->hufftab1_header_address;
        
        for(cnt_value = 0; cnt_value< size_word;cnt_value++)
        {
            JPEG_ENC->HFBUFFER[cnt_value + position_temp] = pbuffer[cnt_value];
        }
        
        JPEG_ENC->HUFTAB1E = position_temp * 4U + JPEGENC_InitStruct->hufftab1_header_size - 1;
        position_temp = position_temp + size_word;
    }
    else
    {
        JPEG_ENC->HUFTAB1E = 0x00U;
    }
    
    /* Huffman table2 frame header */
    if(JPEGENC_InitStruct->hufftab2_header_address != NULL)
    {
        size_word = ((JPEGENC_InitStruct->hufftab2_header_size + 3U)/4U);
    
        pbuffer = (uint32_t*)JPEGENC_InitStruct->hufftab2_header_address;
        
        for(cnt_value = 0; cnt_value< size_word;cnt_value++)
        {
            JPEG_ENC->HFBUFFER[cnt_value + position_temp] = pbuffer[cnt_value];
        }
        
        JPEG_ENC->HUFTAB2E = position_temp * 4U + JPEGENC_InitStruct->hufftab2_header_size - 1;
        position_temp = position_temp + size_word;
    }
    else
    {
        JPEG_ENC->HUFTAB2E = 0x00U;
    }
    
    /* Huffman table3 frame header */
    if(JPEGENC_InitStruct->hufftab3_header_address != NULL)
    {
        size_word = ((JPEGENC_InitStruct->hufftab3_header_size + 3U)/4U);
    
        pbuffer = (uint32_t*)JPEGENC_InitStruct->hufftab3_header_address;
        
        for(cnt_value = 0; cnt_value< size_word;cnt_value++)
        {
            JPEG_ENC->HFBUFFER[cnt_value + position_temp] = pbuffer[cnt_value];
        }
        
        JPEG_ENC->HUFTAB0E = position_temp * 4U + JPEGENC_InitStruct->hufftab3_header_size - 1;
        position_temp = position_temp + size_word;
    }
    else
    {
        JPEG_ENC->HUFTAB3E = 0x00U;
    }
    
    /* File frame footer */
    if(JPEGENC_InitStruct->footer_address != NULL)
    {
        size_word = ((JPEGENC_InitStruct->footer_size + 3U)/4U);
    
        pbuffer = (uint32_t*)JPEGENC_InitStruct->footer_address;
        
        for(cnt_value = 0; cnt_value< size_word;cnt_value++)
        {
            JPEG_ENC->HFBUFFER[cnt_value + position_temp] = pbuffer[cnt_value];
        }
        
        JPEG_ENC->FEADD = position_temp * 4U + JPEGENC_InitStruct->footer_size - 1;
    }    
    else
    {
        JPEG_ENC->FEADD = 0x00U;
    }
    
    /* Header parts out select */
    JPEG_ENC->HSEL = JPEGENC_InitStruct->output_select;
    
    /* Quantisation table 0 */
    if(JPEGENC_InitStruct->QT0_address != NULL)
    {
        for(cnt_value = 0; cnt_value< 64U;cnt_value++)
        {
            JPEG_ENC->QT0[cnt_value] = (uint32_t)JPEGENC_InitStruct->QT0_address[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    /* Quantisation table 1 */
    if(JPEGENC_InitStruct->QT1_address != NULL)
    {
        for(cnt_value = 0; cnt_value< 64U;cnt_value++)
        {
            JPEG_ENC->QT1[cnt_value] = (uint32_t)JPEGENC_InitStruct->QT1_address[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    /* Quantisation table 2 */
    if(JPEGENC_InitStruct->QT2_address != NULL)
    {
        for(cnt_value = 0; cnt_value< 64U;cnt_value++)
        {
            JPEG_ENC->QT2[cnt_value] = (uint32_t)JPEGENC_InitStruct->QT2_address[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    /* Quantisation table 3 */
    if(JPEGENC_InitStruct->QT3_address != NULL)
    {
        for(cnt_value = 0; cnt_value< 64U;cnt_value++)
        {
            JPEG_ENC->QT3[cnt_value] = (uint32_t)JPEGENC_InitStruct->QT3_address[cnt_value];
        }
    }
    else
    {
        /* no process */
    }
    
    /* restart interval configure */
    JPEG_ENC->RICTRL = (JPEGENC_InitStruct->restart_interval | (JPEGENC_InitStruct->interval_num - 1U));
    
    /* JPEG ENC CTRL register */
    JPEG_ENC->CTRL = ((JPEGENC_InitStruct->Corereset  << REG_BIT1_OFFSET)   |\
                     (JPEGENC_InitStruct->C0HT_select  << REG_BIT4_OFFSET)  |\
                     (JPEGENC_InitStruct->C1HT_select  << REG_BIT6_OFFSET)  |\
                     (JPEGENC_InitStruct->C2HT_select  << REG_BIT8_OFFSET)  |\
                     (JPEGENC_InitStruct->C3HT_select  << REG_BIT10_OFFSET) |\
                     (JPEGENC_InitStruct->C0QT_select  << REG_BIT12_OFFSET) |\
                     (JPEGENC_InitStruct->C1QT_select  << REG_BIT14_OFFSET) |\
                     (JPEGENC_InitStruct->C2QT_select  << REG_BIT16_OFFSET) |\
                     (JPEGENC_InitStruct->C3QT_select  << REG_BIT18_OFFSET));
    
    return status;
}


/**
*\*\name    JPEGENC_Enable
*\*\fun     Enables or disables table output in output stream.
*\*\param   outputsel (The input parameters must be the following values):
*\*\          - JPEGENC_OUTPUT_QT0
*\*\          - JPEGENC_OUTPUT_QT1
*\*\          - JPEGENC_OUTPUT_QT2
*\*\          - JPEGENC_OUTPUT_QT3
*\*\          - JPEGENC_OUTPUT_HT0
*\*\          - JPEGENC_OUTPUT_HT1
*\*\          - JPEGENC_OUTPUT_HT2
*\*\          - JPEGENC_OUTPUT_HT3
*\*\          - JPEGENC_OUTPUT_ONLY
*\*\          - JPEGENC_OUTPUT_NOECS
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void JPEGENC_OutputEnable(uint32_t outputsel,FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        JPEG_ENC->HSEL |= outputsel;
    }
    else
    {
        JPEG_ENC->HSEL &= (~outputsel);
    }
}


/**
*\*\name    JPEGENC_Enable
*\*\fun     Enables or disables the specified JPEGENC peripheral.
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void JPEGENC_Enable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable JPEGENC module */
        JPEG_ENC->CTRL |= JPEGENC_CTRL_EN;
    }
    else
    {
        /* Disable JPEGENC module */
        JPEG_ENC->HSEL &= (~JPEGENC_CTRL_EN);
    }
}


/**
*\*\name    JPEGENC_DynamicAdjustEnable
*\*\fun     Enables or disables dynamic adjustment.
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void JPEGENC_DynamicAdjustEnable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        JPEG_ENC->DYNRCFG |= JPEGENC_DYNRCFG_DYNEN;
    }
    else
    {
        JPEG_ENC->DYNRCFG &= JPEGENC_DYNRCFG_DYNEN;
    }
}




