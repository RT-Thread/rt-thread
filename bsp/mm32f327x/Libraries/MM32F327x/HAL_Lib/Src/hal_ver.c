////////////////////////////////////////////////////////////////////////////////
/// @file     hal_ver.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE LIB AND THE CHIPSET INFORMATION.
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
#define _HAL_VER_C_

// Files includes
#include "hal_ver.h"


// MM32 Library version is 0.90

#define __MM32_LIB_VERSION_MAIN         (0x0U)                                  //!< [31:24] main version 
#define __MM32_LIB_VERSION_SUB1         (0x9U)                                  //!< [23:16] sub1 version
#define __MM32_LIB_VERSION_SUB2         (0x0U)                                  //!< [15:8]  sub2 version
#define __MM32_LIB_VERSION_RC           (0x00U)                                 //!< [7:0]  release candidate
#define __MM32_LIB_VERSION              ((__MM32_LIB_VERSION_MAIN << 24U)\
                                         |(__MM32_LIB_VERSION_SUB1 << 16U)\
                                         |(__MM32_LIB_VERSION_SUB2 << 8U )\
                                         |(__MM32_LIB_VERSION_RC))

// MM32 Library release date is 2021-05-10 (YYYY-MM-DD)
#define __MM32_LIB_RELESE_YEARH         (0x20U)                                  //!< [31:24] release year high 
#define __MM32_LIB_RELESE_YEARL         (0x21U)                                  //!< [23:16] release year low
#define __MM32_LIB_RELESE_MONTH         (0x05U)                                  //!< [15:8]  release month
#define __MM32_LIB_RELESE_DAY           (0x10U)                                //!< [7:0]   release day
#define __MM32_LIB_RELESE_DATE          ((__MM32_LIB_RELESE_YEARH << 24U)\
                                         |(__MM32_LIB_RELESE_YEARL << 16U)\
                                         |(__MM32_LIB_RELESE_MONTH << 8U )\
                                         |(__MM32_LIB_RELESE_DAY))
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
///@addtogroup VER_HAL
///@{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Lib and chipset_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  This method returns the Lib revision.
/// @param  None.
/// @retval return the Lib version.
////////////////////////////////////////////////////////////////////////////////
u32 Get_MM32LibVersion(void)
{
    return __MM32_LIB_VERSION;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  This method returns the Lib release date.
/// @param  None.
/// @retval return the Lib release date.
////////////////////////////////////////////////////////////////////////////////
u32 Get_MM32LibReleaseDate(void)
{
    return __MM32_LIB_RELESE_DATE;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the device revision identifier.
/// @param  None.
/// @retval return the device revision identifier.
////////////////////////////////////////////////////////////////////////////////
u32 Get_ChipsetREVID(void)
{
    return((DBGMCU->IDCODE) & 0xF );
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the device identifier..
/// @param  None.
/// @retval return the device Device identifier.
////////////////////////////////////////////////////////////////////////////////
u32 Get_ChipsetDEVID(void)
{
    return((DBGMCU->IDCODE) );
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns first word of the unique device identifier (UID based on 96 bits)
/// @param  None.
/// @retval Device identifier
////////////////////////////////////////////////////////////////////////////////
u32 Get_ChipsetUIDw0(void)
{
    return(READ_REG(*((vu32*)UID_BASE)));
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns second word of the unique device identifier (UID based on 96 bits)
/// @param  None.
/// @retval Device identifier
////////////////////////////////////////////////////////////////////////////////
u32 Get_ChipsetUIDw1(void)
{
    return(READ_REG(*((vu32*)(UID_BASE + 4U))));
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns third word of the unique device identifier (UID based on 96 bits)
/// @param  None.
/// @retval Device identifier
////////////////////////////////////////////////////////////////////////////////
u32 Get_ChipsetUIDw2(void)
{
    return(READ_REG(*((vu32*)(UID_BASE + 8U))));
}





/// @}

/// @}

/// @}
