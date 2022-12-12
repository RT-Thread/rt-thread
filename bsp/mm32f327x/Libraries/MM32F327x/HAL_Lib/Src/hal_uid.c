////////////////////////////////////////////////////////////////////////////////
/// @file     hal_uid.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE UID FIRMWARE FUNCTIONS.
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
#define _HAL_UID_C_

// Files includes
#include "hal_uid.h"
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
///@addtogroup UID_HAL
///@{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup UID_Exported_Functions
/// @{

u8 device_id_data[12] = {0};

////////////////////////////////////////////////////////////////////////////////
/// @brief  Get device ID.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GetChipUID(void)
{
    u8 i;

    for (i = 0; i < 12; i++) {
        device_id_data[i] = *((vu8*)(UID_BASE + i));
    }
}

/// @}

/// @}

/// @}
