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
 * @file n32h76x_78x_jpeg.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76x_78x_JPEG_H__
#define __N32H76x_78x_JPEG_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

#include "n32h76x_78x.h"

typedef enum
{
    BITEQ0 = 0U,
    BITEQ1  = 1U
} BitValue;

/***** JPEG CTRL module ****/
#define    JPEG_DECODE    ((uint32_t)0x00000000U)    /* JPEG operation Decode */
#define    JPEG_ENCODE    JPEG_CTRL_TYPE             /* JPEG operation Encode */

#define    JPEG_NOSWAP    ((uint32_t)0x00000000U)    /* No Swap Data for YCbCr 4:2:2 Format in BRC */
#define    JPEG_SWAP      JPEG_CTRL_SWAP             /* Swap Data for YCbCr 4:2:2 Format in BRC */


/* JPEG SGDMA Module */

/* Descriptor flag */
#define    SGDMA_DESCF_LINKDISABLE    ((uint32_t)0x00000000U)         /* Link Disable */
#define    SGDMA_DESCF_LINKENABLE     JPEGDMA_DESCF_LINKE             /* Link Enable */

#define    SGDMA_DESCF_STARTDISABLE   ((uint32_t)0x00000000U)         /* Non Start of Frame */
#define    SGDMA_DESCF_STARTENABLE    JPEGDMA_DESCF_LINKE             /* Start of Frame */

#define    SGDMA_DESCF_ENDDISABLE     ((uint32_t)0x00000000U)         /* Non End of Frame */
#define    SGDMA_DESCF_ENDENABLE      JPEGDMA_DESCF_LINKE             /* End of Frame */

#define    SGDMA_DESCF_DESCCONDISABLE ((uint32_t)0x00000000U)         /* The descriptor is not consumed */
#define    SGDMA_DESCF_DESCCONENABLE  JPEGDMA_DESCF_LINKE             /* Descriptor Consumed */

/** Scatter-Gather Descriptor **/
typedef struct{
    uint32_t  linkenable              : 1;  // bit 0 - Link Enable.
    uint32_t  startframe              : 1;  // bit 1 - Start of Frame.
    uint32_t  endframe                : 1;  // bit 2 - End of Frame.
    uint32_t  desccons                : 1;  // bit 3 - Descriptor Consumed.
    uint32_t  reserved                : 28; // bit 31:4 - Reserved.
} SGx_desc_flags_bits;

typedef union{
   uint32_t value;
   SGx_desc_flags_bits bits;
}SGx_desc_flags;

/** Scatter-Gather Descriptor type - 32-bit **/
typedef struct
{
   SGx_desc_flags  desc_flags; //Descriptor flag bits: 0: Link Enable, 1: Start of Frame, 2: End of Frame, 3: Descriptor Consumed. 4-31: Reserved
   uint32_t  blk_size;         //[15:0] Block_Size [31:16] Block_Used
   uint32_t  blk_addr;         // The starting address of the data block
   uint32_t  link_addr;        // Link to the next descriptor. Used when Link Enable = 1.
} SGx_DESC32;

/** Scatter-Gather Descriptor type - 64-bit **/
typedef struct
{
   SGx_desc_flags  desc_flags; // Descriptor flag bits: 0: Link Enable, 1: Start of Frame, 2: End of Frame, 3: Descriptor Consumed. 4-31: Reserved
   uint32_t  blk_size;         // Block_Size
   uint32_t  blk_used;         // Block_Used
   uint32_t  blk_addr_low;     // The starting address of the data block [31:0]
   uint32_t  blk_addr_high;    // The starting address of the data block [63:32]
   uint32_t  reserved;         // Reserved field; not used in current implementation
   uint32_t  link_addr_low;    // Link to the next descriptor. Used when Link Enable = 1.
   uint32_t  link_addr_high;   // Link to the next descriptor. Used when Link Enable = 1.
} SGx_DESC64;


/** SGDMA Descriptor Memory Mode  **/
#define    SGDMA_DESCLIST_LIST    ((uint32_t)0x00000000U)    /* The descriptor list structure is a simple List */
#define    SGDMA_DESCLIST_RING    JPEGDMA_CTRL_MMODE_1       /* The descriptor list structure is a Ring Buffer */

#define    SGDMA_DESC_MEMORY      ((uint32_t)0x00000000U)    /* Descriptors stored in memory */
#define    SGDMA_DESC_CSR         JPEGDMA_CTRL_MMODE_0       /* Descriptors programmed through CSR */

/** SGDMA Operation Mode  **/
#define    SGDMA_EOF_PAUSEDMA     ((uint32_t)0x00000000U)    /* Pause DMA operation on EOF and wait for driver action */
#define    SGDMA_EOF_RESUMEDMA    JPEGDMA_CTRL_OPMODE_0      /* Resume operation of the DMA normally after the EOF */

#define    SGDMA_BURST_FIXED      ((uint32_t)0x00000000U)    /* AXI4 MM FIXED burst (aligned addresses only) */
#define    SGDMA_BURST_INCR       JPEGDMA_CTRL_OPMODE_1      /* AXI4 MM INCR burst */

/** SGDMA H2P Init Structure definition **/
typedef struct
{
    SGx_DESC64  h2p_desc;           /* 64bit Descriptor */
    uint32_t    max_burstsize;      /* Maximum allowed size for an AXI4 MM burst */
    uint32_t    SGlist_size;        /* Scatter-Gather List Size */
    uint32_t    SGlist_Head;        /* Scatter-Gather List Head index pointer */
    uint32_t    SGlist_Tail;        /* Scatter-Gather List Tail index pointer */
    uint32_t    SGlist_Threshold;   /* Almost Out Of Descriptors Threshold */
    uint32_t    desclist_type;      /* The descriptor list structure type */
    uint32_t    descstored_type;    /* The descriptor storage location */
    uint32_t    DMA_EOF_type;       /* DMA operation mode on EOF */
    uint32_t    DMA_burst_type;     /* DMA burst type */
} SGDMA_H2P_InitType;

/** SGDMA P2H Init Structure definition **/
typedef struct
{
    SGx_DESC64  p2h_desc;           /* 64bit Descriptor */
    uint32_t    max_burstsize;      /* Maximum allowed size for an AXI4 MM burst */
    uint32_t    SGlist_size;        /* Scatter-Gather List Size */
    uint32_t    SGlist_Head;        /* Scatter-Gather List Head index pointer */
    uint32_t    SGlist_Tail;        /* Scatter-Gather List Tail index pointer */
    uint32_t    SGlist_Threshold;   /* Almost Out Of Descriptors Threshold */
    uint32_t    desclist_type;      /* The descriptor list structure type */
    uint32_t    descstored_type;    /* The descriptor storage location */
    uint32_t    DMA_EOF_type;       /* DMA operation mode on EOF */
    uint32_t    DMA_burst_type;     /* DMA burst type */
} SGDMA_P2H_InitType;

/* SGDMA interrupt */
#define    SGDMA_INTSTS_WDATAERREN    JPEGDMA_INTSTS_WDATAERR       /* AXI MM Write Error when writing data */
#define    SGDMA_INTSTS_RDATAERR      JPEGDMA_INTSTS_RDATAERR       /* AXI MM Read Error when reading data */
#define    SGDMA_INTSTS_WDESCERR      JPEGDMA_INTSTS_WDESCERR       /* AXI MM Write Error when writing a descriptor */
#define    SGDMA_INTSTS_RDESCERR      JPEGDMA_INTSTS_RDESCERR       /* AXI MM Read Error when reading a descriptor */
#define    SGDMA_INTSTS_EOD           JPEGDMA_INTSTS_EOD            /* End-Of-Descriptor */
#define    SGDMA_INTSTS_AOOD          JPEGDMA_INTSTS_AOOD           /* Channel is Almost Out of Descriptors */
#define    SGDMA_INTSTS_OOD           JPEGDMA_INTSTS_OOD            /* Out Of Descriptors */
#define    SGDMA_INTSTS_EOFIN         JPEGDMA_INTSTS_EOFIN          /* End-Of-Frame sampled at the input of the channel */
#define    SGDMA_INTSTS_EOFOUT        JPEGDMA_INTSTS_EOFOUT         /* End-Of-Frame sampled at the output of the channel */
#define    SGDMA_INTSTS_GINT          JPEGDMA_INTSTS_GINT           /* Global interrupt status bit for the Channel */
#define    SGDMA_INTSTS_BUSY          JPEGDMA_STS_BUSY              /* H2P/P2H is processing a transfer */

/* JPEG BRC Module */

/** JPEG BRC Init Structure definition **/
typedef struct
{
    uint32_t    buffer_addr;    /* buffer memory address */
    uint32_t    buffer_size;    /* buffer memory size, in byte */
    uint32_t    upsample_mode;  /* Up sampling mode */
} JPEGBRC_InitType;

/* JPEG RBC Module */

/** JPEG BRC Init Structure definition **/
typedef struct
{
    uint32_t    pixel_format;    /* Pixel format */
    uint32_t    sample_order;    /* Switch input sample order */
    uint32_t    frame_width;     /* Frame width */
    uint32_t    frame_height;    /* Frame height */
    uint32_t    component0names; /* Component 0 names */
    uint32_t    component1names; /* Component 1 names */
    uint32_t    component2names; /* Component 2 names */
    uint32_t    C0startaddress;  /* Component 0 Start Address */
    uint32_t    C0buffersize;    /* Size of buffer in the AXI memory */
} JPEGRBC_InitType;

/* Pixel format */
#define    JPEGRBC_4_4_4_NONINTERLEAVED          ((uint32_t)0x00000000U)              /* 4:4:4 non-interleaved format */
#define    JPEGRBC_4_2_2_NONINTERLEAVED          ((uint32_t)0x00000001U)              /* 4:2:2 non-interleaved format */
#define    JPEGRBC_4_2_0_NONINTERLEAVED          ((uint32_t)0x00000002U)              /* 4:2:0 non-interleaved format */
#define    JPEGRBC_MONOCHROME                    ((uint32_t)0x00000003U)              /* monochrome format */
#define    JPEGRBC_4_4_4_INTERLEAVED             ((uint32_t)0x00000004U)              /* 4:4:4 interleaved format */
#define    JPEGRBC_4_2_2_INTERLEAVED             ((uint32_t)0x00000005U)              /* 4:2:2 interleaved format */
#define    JPEGRBC_4_2_0_INTERLEAVED             ((uint32_t)0x00000006U)              /* 4:2:0 interleaved format */

/* sample_order */
#define    JPEGRBC_MSBSAMPLE          ((uint32_t)0x00000000U)              /* Switch input sample order MSB */
#define    JPEGRBC_LSBSAMPLE          (JPEGRBC_SWITCH_SWITCH)              /* Switch input sample order LSB */


/* JPEG DEC Module */

/** JPEG DEC Init Structure definition **/
typedef struct
{
    uint32_t    buffer_addr;    /* buffer memory address */
    uint32_t    buffer_size;    /* buffer memory size, in byte */
    uint32_t    upsample_mode;  /* Up sampling mode */
} JPEGDEC_InitType;

#define    JPEGDEC_EOB0_ADDRESS       ((uint32_t)0x20U)           /* JPEGDEC_HUFTAB0_EOB offset address */
#define    JPEGDEC_EOB1_ADDRESS       ((uint32_t)0x24U)           /* JPEGDEC_HUFTAB1_EOB offset address */
#define    JPEGDEC_EOB2_ADDRESS       ((uint32_t)0x28U)           /* JPEGDEC_HUFTAB2_EOB offset address */
#define    JPEGDEC_EOB3_ADDRESS       ((uint32_t)0x2CU)           /* JPEGDEC_HUFTAB3_EOB offset address */

#define    JPEGDEC_HUFFTABLE          ((uint32_t)0x00000000U)     /* Huffman decoder table */
#define    JPEGDEC_DVECTORTABLE       (JPEGDEC_HUF_ADDR_TABLE_0)  /* D vector table */
#define    JPEGDEC_IVECTORTABLE       (JPEGDEC_HUF_ADDR_TABLE_1)  /* I vector table */
#define    JPEGDEC_HUFFACCTABLE       (JPEGDEC_HUF_ADDR_TABLE)    /* Huffman decoder accelerator tables */

#define    JPEGDEC_DCTABLE            ((uint32_t)0x00000000U)     /* DC table */
#define    JPEGDEC_ACTABLE            (JPEGDEC_HUF_ADDR_ACDC)     /* AC table */

#define    JPEGDEC_HUFFTABLE_0        ((uint32_t)0x00000000U)     /* table 0 */
#define    JPEGDEC_HUFFTABLE_1        (JPEGDEC_HUF_ADDR_HNUM_0)   /* table 1 */
#define    JPEGDEC_HUFFTABLE_2        (JPEGDEC_HUF_ADDR_HNUM_1)   /* table 2 */
#define    JPEGDEC_HUFFTABLE_3        (JPEGDEC_HUF_ADDR_HNUM)     /* table 3 */

#define    JPEGDEC_QT0_ADDRESS        ((uint32_t)0x400U)           /* QT0 offset address */
#define    JPEGDEC_QT1_ADDRESS        ((uint32_t)0x500U)           /* QT1 offset address */
#define    JPEGDEC_QT2_ADDRESS        ((uint32_t)0x600U)           /* QT2 offset address */
#define    JPEGDEC_QT3_ADDRESS        ((uint32_t)0x700U)           /* QT3 offset address */

/* JPEG ENC Module */

/* output_select */
#define    JPEGENC_OUTPUT_NOTHING     ((uint32_t)0x00000000U)/* No data Ouptut in output stream */
#define    JPEGENC_OUTPUT_QT0         (JPEGENC_HSEL_QT0)     /* Ouptut quantisation table 0 in output stream */
#define    JPEGENC_OUTPUT_QT1         (JPEGENC_HSEL_QT1)     /* Ouptut quantisation table 1 in output stream */
#define    JPEGENC_OUTPUT_QT2         (JPEGENC_HSEL_QT2)     /* Ouptut quantisation table 2 in output stream */
#define    JPEGENC_OUTPUT_QT3         (JPEGENC_HSEL_QT3)     /* Ouptut quantisation table 3 in output stream */
#define    JPEGENC_OUTPUT_HT0         (JPEGENC_HSEL_HT0)     /* Ouptut Huffman table 0 in output stream */
#define    JPEGENC_OUTPUT_HT1         (JPEGENC_HSEL_HT1)     /* Ouptut Huffman table 1 in output stream */
#define    JPEGENC_OUTPUT_HT2         (JPEGENC_HSEL_HT2)     /* Ouptut Huffman table 2 in output stream */
#define    JPEGENC_OUTPUT_HT3         (JPEGENC_HSEL_HT3)     /* Ouptut Huffman table 3 in output stream */
#define    JPEGENC_OUTPUT_ONLY        (JPEGENC_HSEL_NFD)     /* Output tables in only one frames */
#define    JPEGENC_OUTPUT_NOECS       (JPEGENC_HSEL_ATF)     /* No ouptut ECS data in only one frames in output stream */

/* output_select */
#define    JPEGENC_RESSART_DISABLE    ((uint32_t)0x00000000U)   /* Disable restart marker generation */
#define    JPEGENC_RESSART_ENABLE     (JPEGENC_RICTRL_RIEN)     /* Enable restart marker generation */

/* Corereset */
#define    JPEGENC_CORERST_ENABLE     ((uint32_t)0x00000000U)   /* no reset the core if any error occurred */
#define    JPEGENC_CORERST_DISABLE    (JPEGENC_CTRL_ERST)       /* reset the core if any error occurred */


/*** Huffman tables ***/
typedef struct
{
    uint16_t* DCcode_offset;
    uint16_t* ACcode_offset;
    uint16_t* DCcode_start;
    uint16_t* ACcode_start;
    uint32_t  EOBS;
    uint32_t  ZRLS;
} Huffmantables_InitType;

/** JPEG ENC Init Structure definition **/
typedef struct
{
    Huffmantables_InitType HuffmanTable0;   /* Huffman table0 */
    Huffmantables_InitType HuffmanTable1;   /* Huffman table0 */
    Huffmantables_InitType HuffmanTable2;   /* Huffman table0 */
    Huffmantables_InitType HuffmanTable3;   /* Huffman table0 */
    uint8_t*    header_address;   /* File frame header storage address */
    uint32_t    header_size;      /* File frame header size */
    uint8_t*    hufftab0_header_address;   /* Huffman table0 frame header storage address */
    uint32_t    hufftab0_header_size;      /* Huffman table0 frame header size */
    uint8_t*    hufftab1_header_address;   /* Huffman table1 frame header storage address */
    uint32_t    hufftab1_header_size;      /* Huffman table1 frame header size */
    uint8_t*    hufftab2_header_address;   /* Huffman table2 frame header storage address */
    uint32_t    hufftab2_header_size;      /* Huffman table2 frame header size */
    uint8_t*    hufftab3_header_address;   /* Huffman table3 frame header storage address */
    uint32_t    hufftab3_header_size;      /* Huffman table3 frame header size */
    uint8_t*    footer_address;   /* File frame footer storage address */
    uint32_t    footer_size;      /* File frame footer size */
    uint32_t    output_select;    /* Header parts out select */
    uint8_t*    QT0_address;      /* Quantisation table 0 storage address */
    uint8_t*    QT1_address;      /* Quantisation table 1 storage address */
    uint8_t*    QT2_address;      /* Quantisation table 2 storage address */
    uint8_t*    QT3_address;      /* Quantisation table 3 storage address */
    uint32_t    restart_interval; /* restart interval enable*/
    uint32_t    interval_num;     /* Number of blocks per restart interval */
    uint32_t    C0QT_select;      /* Quantisation table selector for component 0 */
    uint32_t    C1QT_select;      /* Quantisation table selector for component 1 */
    uint32_t    C2QT_select;      /* Quantisation table selector for component 2 */
    uint32_t    C3QT_select;      /* Quantisation table selector for component 3 */
    uint32_t    C0HT_select;      /* Huffman table selector for component 0 */
    uint32_t    C1HT_select;      /* Huffman table selector for component 1 */
    uint32_t    C2HT_select;      /* Huffman table selector for component 2 */
    uint32_t    C3HT_select;      /* Huffman table selector for component 3 */
    uint32_t    Corereset;        /* reset the core if any error occurred */
} JPEGENC_InitType;


/***** JPEG CTRL module ****/
void JPEG_ConfigType(uint32_t Type);
void JPEG_ConfigSwap(uint32_t Type);

/***** JPEG SGDMA module ****/
void SGDMA_H2P_Init(SGDMA_H2P_InitType* SGDMA_H2P_InitStruct);
void SGDMA_P2H_Init(SGDMA_P2H_InitType* SGDMA_P2H_InitStruct);
void SGDMA_Reset(JPEG_SGDMA_Module *SGDMAx);
void SGDMA_Start(JPEG_SGDMA_Module *SGDMAx);
void SGDMA_ConfigInt(JPEG_SGDMA_Module* SGDMAx, uint32_t SGDMA_INT, FunctionalState Cmd);
FlagStatus SGDMAx_GetFlagStatus(JPEG_SGDMA_Module* SGDMAx, uint32_t Flag);
FlagStatus SGDMAx_GetIntStatus(JPEG_SGDMA_Module* SGDMAx, uint32_t Flag);
void SGDMAx_ClrFlag(JPEG_SGDMA_Module* SGDMAx, uint32_t Flag);

/***** JPEG BRC module ****/
ErrorStatus JPEGBRC_Init(JPEGBRC_InitType* JPEGBRC_InitStruct);
void JPEGBRC_Enable(FunctionalState Cmd);

/***** JPEG RBC module ****/
ErrorStatus JPEGRBC_Init(JPEGRBC_InitType* JPEGRBC_InitStruct);
void JPEGRBC_Enable(FunctionalState Cmd);

/***** JPEG DEC module ****/
void JPEGDEC_Enable(FunctionalState Cmd);
FlagStatus JPEGDEC_GetFlagStatus(uint32_t Flag);
uint32_t JPEGDEC_GetUNKErrorAddress(void);
uint32_t JPEGDEC_GetUNEXPErrorAddress(void);
uint16_t JPEGDEC_GetHESYMErrorAddress(void);
uint32_t JPEGDEC_GetHESYMECSErrorAddress(void);
uint32_t JPEGDEC_GetHUFSErrorAddress(void);
ErrorStatus JPEGDEC_TableAccessRequest(FunctionalState Cmd);
void JPEGDEC_SetHUFTable_EOB(uint32_t TableAddress,uint32_t EOBSymbol,uint32_t EOBSymbolMask);
ErrorStatus JPEGDEC_SetHuffTable(uint32_t TableType,uint32_t Tableselector,uint32_t TableNum,uint32_t* Value,uint32_t Count);
void JPEGDEC_SetQuantiTable(uint32_t TableAddress,uint8_t* Value,uint32_t Count);

/***** JPEG ENC module ****/
ErrorStatus JPEGENC_Init(JPEGENC_InitType* JPEGENC_InitStruct);
void JPEGENC_OutputEnable(uint32_t outputsel,FunctionalState Cmd);
void JPEGENC_Enable(FunctionalState Cmd);
void JPEGENC_DynamicAdjustEnable(FunctionalState Cmd);


#ifdef __cplusplus
}
#endif

#endif /* __N32H76x_78x_JPEG_H__ */


