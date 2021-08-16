////////////////////////////////////////////////////////////////////////////////
/// @file     hal_fsmc.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SDIO
///           FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#ifndef __HAL_FSMC_H
#define __HAL_FSMC_H

// Files includes
#include "types.h"
#include "reg_common.h"
#include "reg_fsmc.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup FSMC_HAL
/// @brief FSMC HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup FSMC_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief FSMC_interrupts_define
////////////////////////////////////////////////////////////////////////////////





// Timing parameter configuration register set selection register set0 register set1 register set2

#define FSMC_TimingRegSelect_0    ((u32)0x00000000)
#define FSMC_TimingRegSelect_1    ((u32)0x00000100)
#define FSMC_TimingRegSelect_2    ((u32)0x00000200)

// Capacity of external device
#define FSMC_MemSize_None   ((u32)0x00000000)
#define FSMC_MemSize_64KB   ((u32)0x00000001)
#define FSMC_MemSize_128KB  ((u32)0x00000002)
#define FSMC_MemSize_256KB  ((u32)0x00000002)
#define FSMC_MemSize_512KB  ((u32)0x00000004)
#define FSMC_MemSize_1MB    ((u32)0x00000005)
#define FSMC_MemSize_2MB    ((u32)0x00000006)
#define FSMC_MemSize_4MB    ((u32)0x00000007)
#define FSMC_MemSize_8MB    ((u32)0x00000008)
#define FSMC_MemSize_16MB   ((u32)0x00000009)
#define FSMC_MemSize_32MB   ((u32)0x0000000A)
#define FSMC_MemSize_64MB   ((u32)0x0000000B)
#define FSMC_MemSize_128MB  ((u32)0x0000000C)
#define FSMC_MemSize_256MB  ((u32)0x0000000D)
#define FSMC_MemSize_512MB  ((u32)0x0000000E)
#define FSMC_MemSize_1GB    ((u32)0x0000000F)
#define FSMC_MemSize_2GB    ((u32)0x00000010)
#define FSMC_MemSize_4GB    ((u32)0x00000011)


// Memory data bus bit width setting
typedef enum {
    FSMC_DataWidth_16bits      = (0x0000), //16bits
    FSMC_DataWidth_32bits      = (0x0001), //32bits
    FSMC_DataWidth_64bits      = (0x0002), //64bits
    FSMC_DataWidth_128bits     = (0x0003), //128bits
    FSMC_DataWidth_8bits       = (0x0004), //8bits
} FSMC_NORSRAM_DataWidth_TypeDef;

typedef enum {
    FSMC_NORSRAM_BANK0 = 0,
    FSMC_NORSRAM_BANK1 = 1,
    FSMC_NORSRAM_BANK2 = 2,
} FSMC_NORSRAM_BANK_TypeDef;

typedef struct {
    u32 FSMC_SMReadPipe;                                                        //sm_read_pipe[1:0] The cycle of latching read data, that is, the cycle when ready_resp is pulled high

    u32 FSMC_ReadyMode;                                                         //Select whether the hready_resp signal comes from the FSMC IP internal or external DEVICE, only for writing and reading external DEVICE operations.
    //0: Internal FSMC 1: External DEVICE (ie from FSMC_NWAIT)
    u32 FSMC_WritePeriod;                                                       //Write cycle

    u32 FSMC_WriteHoldTime;                                                     //Address/data hold time during write operation

    u32 FSMC_AddrSetTime;                                                       //Address establishment time

    u32 FSMC_ReadPeriod;                                                        //Read cycle

    FSMC_NORSRAM_DataWidth_TypeDef FSMC_DataWidth;

} FSMC_NORSRAM_Bank_InitTypeDef;

typedef struct {
    u32 FSMC_Mode;
    u32 FSMC_TimingRegSelect;
    u32 FSMC_MemSize;
    u32 FSMC_MemType;
    u32 FSMC_AddrDataMode;
} FSMC_InitTypeDef;


#define FSMC_MemType_SDRAM          ((u32)0x0<<5)
#define FSMC_MemType_NorSRAM        ((u32)0x1<<5)
#define FSMC_MemType_FLASH          ((u32)0x2<<5)
#define FSMC_MemType_RESERVED       ((u32)0x3<<5)
//SYSCFG_CFGR1
#define FSMC_Mode_6800              ((u32)0x40000000)
#define FSMC_Mode_8080              ((u32)0x20000000)
#define FSMC_Mode_NorFlash          ((u32)0x00000000)

#define FSMC_AddrDataMUX            ((u32)0x00000000)
#define FSMC_AddrDataDeMUX          ((u32)0x10000000)




void FSMC_NORSRAMStructInit(FSMC_InitTypeDef* init_struct);
void FSMC_NORSRAM_BankStructInit(FSMC_NORSRAM_Bank_InitTypeDef* init_struct);
void FSMC_NORSRAMInit(FSMC_InitTypeDef* init_struct);
void FSMC_NORSRAM_Bank_Init(FSMC_NORSRAM_Bank_InitTypeDef* FSMC_Bank_InitStruct, FSMC_NORSRAM_BANK_TypeDef bank);



/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_FSMC_H 
////////////////////////////////////////////////////////////////////////////////
