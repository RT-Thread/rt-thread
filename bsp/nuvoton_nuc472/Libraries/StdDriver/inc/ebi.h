/****************************************************************************//**
 * @file     ebi.h
 * @version  V0.10
 * $Revision: 6 $
 * $Date: 14/09/30 1:12p $
 * @brief    NUC472/NUC442 EBI driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __EBI_H__
#define __EBI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_EBI_Driver EBI Driver
  @{
*/

/** @addtogroup NUC472_442_EBI_EXPORTED_CONSTANTS EBI Exported Constants
  @{
*/

/* Bank-0 constants */
#define EBI0_BASE_ADDR              0x60000000  ///<EBI bank 0 base address , 0x60000000 ~ 0x63FFFFFF  \hideinitializer 
#define EBI0_MAX_SIZE               0x400000    ///<EBI bank 0 max. size  \hideinitializer 

#define EBI0_READ_DATA8(Addr)               *((volatile unsigned char *)(EBI0_BASE_ADDR+Addr))             ///< Read 8-bit data from EBI bank 0  \hideinitializer 
#define EBI0_WRITE_DATA8(Addr, Data)        *((volatile unsigned char *)(EBI0_BASE_ADDR+Addr))=Data        ///< Write 8-bit data to EBI bank 0  \hideinitializer 
#define EBI0_READ_DATA16(Addr)              *((volatile unsigned short *)(EBI0_BASE_ADDR+Addr))            ///< Read 16-bit data from EBI bank 0  \hideinitializer 
#define EBI0_WRITE_DATA16(Addr, Data)       *((volatile unsigned short *)(EBI0_BASE_ADDR+Addr))=Data       ///< Write 16-bit data to EBI bank 0  \hideinitializer 
#define EBI0_READ_DATA32(Addr)              *((volatile unsigned int *)(EBI0_BASE_ADDR+Addr))              ///< Read 32-bit data from EBI bank 0  \hideinitializer 
#define EBI0_WRITE_DATA32(Addr, Data)       *((volatile unsigned int *)(EBI0_BASE_ADDR+Addr))=Data         ///< Write 32-bit data to EBI bank 0  \hideinitializer 

/* Bank-1 constants */
#define EBI1_BASE_ADDR              0x64000000  ///<EBI bank 1 base address , 0x64000000 ~ 0x67FFFFFF    \hideinitializer 
#define EBI1_MAX_SIZE               0x400000    ///<EBI bank 1 max. size                                \hideinitializer 

#define EBI1_READ_DATA8(Addr)               *((volatile unsigned char *)(EBI1_BASE_ADDR+Addr))              ///< Read 8-bit data from EBI bank 0  \hideinitializer 
#define EBI1_WRITE_DATA8(Addr, Data)        *((volatile unsigned char *)(EBI1_BASE_ADDR+Addr))=Data         ///< Write 8-bit data to EBI bank 0   \hideinitializer 
#define EBI1_READ_DATA16(Addr)              *((volatile unsigned short *)(EBI1_BASE_ADDR+Addr))             ///< Read 16-bit data from EBI bank 0  \hideinitializer 
#define EBI1_WRITE_DATA16(Addr, Data)       *((volatile unsigned short *)(EBI1_BASE_ADDR+Addr))=Data        ///< Write 16-bit data to EBI bank 0  \hideinitializer 
#define EBI1_READ_DATA32(Addr)              *((volatile unsigned int *)(EBI1_BASE_ADDR+Addr))               ///< Read 32-bit data from EBI bank 0  \hideinitializer 
#define EBI1_WRITE_DATA32(Addr, Data)       *((volatile unsigned int *)(EBI1_BASE_ADDR+Addr))=Data          ///< Write 32-bit data to EBI bank 0  \hideinitializer 

/* Bank-2 constants */
#define EBI2_BASE_ADDR              0x68000000  ///<EBI bank 2 base address , 0x68000000 ~ 0x6BFFFFFF  
#define EBI2_MAX_SIZE               0x400000    ///<EBI bank 2 max. size                               

#define EBI2_READ_DATA8(Addr)               *((volatile unsigned char *)(EBI2_BASE_ADDR+Addr))              ///< Read 8-bit data from EBI bank 0  \hideinitializer 
#define EBI2_WRITE_DATA8(Addr, Data)        *((volatile unsigned char *)(EBI2_BASE_ADDR+Addr))=Data         ///< Write 8-bit data to EBI bank 0   \hideinitializer 
#define EBI2_READ_DATA16(Addr)              *((volatile unsigned short *)(EBI2_BASE_ADDR+Addr))             ///< Read 16-bit data from EBI bank 0 \hideinitializer 
#define EBI2_WRITE_DATA16(Addr, Data)       *((volatile unsigned short *)(EBI2_BASE_ADDR+Addr))=Data        ///< Write 16-bit data to EBI bank 0  \hideinitializer 
#define EBI2_READ_DATA32(Addr)              *((volatile unsigned int *)(EBI2_BASE_ADDR+Addr))               ///< Read 32-bit data from EBI bank 0 \hideinitializer 
#define EBI2_WRITE_DATA32(Addr, Data)       *((volatile unsigned int *)(EBI2_BASE_ADDR+Addr))=Data          ///< Write 32-bit data to EBI bank 0  \hideinitializer 

/* Bank-3 constants */
#define EBI3_BASE_ADDR              0x6C000000  ///<EBI bank 3 base address , 0x6C000000 ~ 0x6FFFFFFF   \hideinitializer 
#define EBI3_MAX_SIZE               0x400000    ///<EBI bank 3 max. size                                \hideinitializer 

#define EBI3_READ_DATA8(Addr)               *((volatile unsigned char *)(EBI3_BASE_ADDR+Addr))              ///< Read 8-bit data from EBI bank 0  \hideinitializer 
#define EBI3_WRITE_DATA8(Addr, Data)        *((volatile unsigned char *)(EBI3_BASE_ADDR+Addr))=Data         ///< Write 8-bit data to EBI bank 0   \hideinitializer 
#define EBI3_READ_DATA16(Addr)              *((volatile unsigned short *)(EBI3_BASE_ADDR+Addr))             ///< Read 16-bit data from EBI bank 0 \hideinitializer 
#define EBI3_WRITE_DATA16(Addr, Data)       *((volatile unsigned short *)(EBI3_BASE_ADDR+Addr))=Data        ///< Write 16-bit data to EBI bank 0  \hideinitializer 
#define EBI3_READ_DATA32(Addr)              *((volatile unsigned int *)(EBI3_BASE_ADDR+Addr))               ///< Read 32-bit data from EBI bank 0 \hideinitializer 
#define EBI3_WRITE_DATA32(Addr, Data)       *((volatile unsigned int *)(EBI3_BASE_ADDR+Addr))=Data          ///< Write 32-bit data to EBI bank 0  \hideinitializer 


/* Constants for EBI bank number */
#define EBI_BANK0   0                ///< EBI bank 0 \hideinitializer 
#define EBI_BANK1   0x1              ///< EBI bank 1 \hideinitializer 
#define EBI_BANK2   0x2              ///< EBI bank 2 \hideinitializer 
#define EBI_BANK3   0x3              ///< EBI bank 3 \hideinitializer 

/* Constants for EBI CS Active Level */
#define EBI_CS_ACTIVE_HIGH      1     ///< EBI CS active level is high \hideinitializer 
#define EBI_CS_ACTIVE_LOW       0     ///< EBI CS active level is low \hideinitializer 

/* Constants for EBI data bus width */
#define EBI_BUSWIDTH_8BIT       8     ///< EBI bus width is 8-bit \hideinitializer 
#define EBI_BUSWIDTH_16BIT      16    ///< EBI bus width is 16-bit \hideinitializer 

/* Constants for EBI separate mode */
#define EBI_SEPARATEMODE_ENABLE     0x1   ///< Enable EBI separate mode \hideinitializer 
#define EBI_SEPARATEMODE_DISABLE    0     ///< Disable EBI separate mode \hideinitializer 

/* Constants for EBI MCLK divider */
#define EBI_MCLKDIV_1       0            ///< EBI clock is MCLK div 1 \hideinitializer 
#define EBI_MCLKDIV_2       0x1          ///< EBI clock is MCLK div 2 \hideinitializer 
#define EBI_MCLKDIV_4       0x2          ///< EBI clock is MCLK div 4 \hideinitializer 
#define EBI_MCLKDIV_8       0x3          ///< EBI clock is MCLK div 8 \hideinitializer 
#define EBI_MCLKDIV_16      0x4          ///< EBI clock is MCLK div 16 \hideinitializer 
#define EBI_MCLKDIV_32      0x5          ///< EBI clock is MCLK div 32 \hideinitializer 

#define EBI_TIMING_FASTEST      0x0      ///< EBI timing is the fastest \hideinitializer 
#define EBI_TIMING_VERYFAST     0x1      ///< EBI timing is very fast   \hideinitializer      
#define EBI_TIMING_FAST         0x2      ///< EBI timing is fast \hideinitializer 
#define EBI_TIMING_NORMAL       0x3      ///< EBI timing is normal  \hideinitializer 
#define EBI_TIMING_SLOW         0x4      ///< EBI timing is slow \hideinitializer 
#define EBI_TIMING_VERYSLOW     0x5      ///< EBI timing is very slow \hideinitializer 
#define EBI_TIMING_SLOWEST      0x6      ///< EBI timing is the slowest \hideinitializer 

/*@}*/ /* end of group NUC472_442_EBI_EXPORTED_CONSTANTS */


/** @addtogroup NUC472_442_EBI_EXPORTED_FUNCTIONS EBI Exported Functions
  @{
*/
void EBI_Open(uint32_t u32Bank, uint32_t u32DataWidth, uint32_t u32TimingClass, uint32_t u32BusMode, uint32_t u32CSActiveLevel);
void EBI_Close(uint32_t u32Bank);
void EBI_SetBusTiming(uint32_t u32Bank, uint32_t u32TimingConfig, uint32_t u32MclkDiv);
void EBI_EnableCrypto(uint32_t u32Bank, uint32_t *u32Key);
void EBI_DisbleCrypto(uint32_t u32Bank);


/*@}*/ /* end of group NUC472_442_EBI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_EBI_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__EBI_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
