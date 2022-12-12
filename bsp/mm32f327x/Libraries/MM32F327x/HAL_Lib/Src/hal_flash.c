////////////////////////////////////////////////////////////////////////////////
/// @file     hal_flash.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE FLASH FIRMWARE FUNCTIONS.
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
#define _HAL_FLASH_C_

// Files includes
#include "hal_flash.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup FLASH_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup FLASH_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the code latency value.
/// @note   This function can be used for all MM32 devices.
/// @param  latency: specifies the FLASH Latency value.
///         This parameter can be one of the following values:
/// @arg    FLASH_Latency_0: FLASH Zero Latency cycle
/// @arg    FLASH_Latency_1: FLASH One Latency cycle
/// @arg    FLASH_Latency_2: FLASH Two Latency cycles
/// @arg    FLASH_Latency_3: FLASH Three Latency cycles
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void FLASH_SetLatency(FLASH_Latency_TypeDef latency)
{
    FLASH->ACR = (FLASH->ACR & (~FLASH_ACR_LATENCY)) | latency;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the Half cycle flash access.
/// @note   This function can be used for all MM32 devices.
/// @param  half_cycle_access: specifies the FLASH Half cycle Access mode.
///         This parameter can be one of the following values:
/// @arg    FLASH_HalfCycleAccess_Enable: FLASH Half Cycle Enable
/// @arg    FLASH_HalfCycleAccess_Disable: FLASH Half Cycle Disable
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void FLASH_HalfCycleAccessCmd(FLASH_HalfCycleAccess_TypeDef half_cycle_access)
{
    FLASH->ACR &= ~FLASH_ACR_HLFCYA;
    FLASH->ACR |= half_cycle_access;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the Prefetch Buffer.
/// @note   This function can be used for all MM32 devices.
/// @param  prefetch_buffer: specifies the Prefetch buffer status.
///         This parameter can be one of the following values:
/// @arg    FLASH_PrefetchBuffer_Enable: FLASH Prefetch Buffer Enable
/// @arg    FLASH_PrefetchBuffer_Disable: FLASH Prefetch Buffer Disable
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_TypeDef prefetch_buffer)
{
    FLASH->ACR &= ~FLASH_ACR_PRFTBE;
    FLASH->ACR |= prefetch_buffer;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Locks the FLASH Program Erase Controller.
/// @note   This function can be used for all MM32 devices.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void FLASH_Lock(void)
{
    FLASH->CR |= FLASH_CR_LOCK;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Unlocks the FLASH Program Erase Controller.
/// @note   This function can be used for all MM32 devices.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void FLASH_Unlock()
{
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enable to program the FLASH Option Byte.
/// @note   This function can be used for all MM32 devices.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void FLASH_OPTB_Enable(void)
{
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Erases a specified FLASH page.
/// @note   This function can be used for all MM32 devices.
/// @param  page_address: The page address to be erased.
/// @retval FLASH Status: The returned value can be: FLASH_BUSY,
///         FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_ErasePage(u32 page_address)
{
    FLASH->CR |= FLASH_CR_PER;
    FLASH->AR = page_address;
    FLASH->CR |= FLASH_CR_STRT;
    return FLASH_WaitForLastOperation(EraseTimeout);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Erases all FLASH pages.
/// @note   This function can be used for all MM32 devices.
/// @param  None.
/// @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
///         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_EraseAllPages()
{
    FLASH->AR = FLASH_BASE;
    FLASH->CR |= (FLASH_CR_MER | FLASH_CR_STRT);
    return FLASH_WaitForLastOperation(EraseTimeout);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Erases the FLASH option bytes.
/// @note   This function can be used for all MM32 devices.
/// @param  None.
/// @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
///         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_EraseOptionBytes()
{
    FLASH_OPTB_Enable();
    FLASH->AR = OB_BASE;
    FLASH->CR |= (FLASH_CR_OPTER | FLASH_CR_STRT);
    return FLASH_WaitForLastOperation(EraseTimeout);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Programs a half word at a specified address.
/// @note   This function can be used for all MM32 devices.
/// @param  address: specifies the address to be programmed.
/// @param  data: specifies the data to be programmed.
/// @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
///         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_ProgramHalfWord(u32 address, u16 data)
{
    FLASH->CR |= FLASH_CR_PG;

    *(vu16*)address = data;


    return FLASH_WaitForLastOperation(ProgramTimeout);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Programs a word at a specified address.
/// @note   This function can be used for all MM32 devices.
/// @param  address: specifies the address to be programmed.
/// @param  data: specifies the data to be programmed.
/// @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
///         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_ProgramWord(u32 address, u32 data)
{
    FLASH_Status ret = FLASH_ProgramHalfWord(address, data);
    if (ret == FLASH_COMPLETE) {
        ret = FLASH_ProgramHalfWord(address + 2, data >> 16);
    }
    return ret;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Programs a byte at a specified Option Byte Data address.
/// @note   This function can be used for all MM32 devices.
/// @param  address: specifies the address to be programmed.
///         This parameter can be 0x1FFFF804 or 0x1FFFF806.
/// @param  data: specifies the data to be programmed.
/// @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
///         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_ProgramOptionByteData(u32 address, u8 data)
{
    FLASH_Status ret;
    __IO u16 temp;
    FLASH_OPTB_Enable();
    FLASH->CR |= FLASH_CR_OPTPG;
    temp = (u16)(~data);
    temp = (temp << 8) & 0xFF00;
    temp = temp | (u16)data;
    address = address & (~0x1);
    *(vu16*)address = temp;
    ret = FLASH_WaitForLastOperation(ProgramTimeout);

    return ret;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Programs a half word at a specified Option Byte Data address.
/// @note   This function can be used for all MM32 devices.
/// @param  address: specifies the address to be programmed.
///         This parameter can be 0x1FFFF804 or 0x1FFFF806.
/// @param  data: specifies the data to be programmed.
/// @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
///         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_ProgramOptionHalfWord(u32 address, u16 data)
{
    FLASH_Status ret;
    FLASH_OPTB_Enable();
    FLASH->CR |= FLASH_CR_OPTPG;
    *(vu16*)address = data;
    ret = FLASH_WaitForLastOperation(ProgramTimeout);

    return ret;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Read protection for the specified address
/// @note   This function can be used for all MM32 devices.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_ProgramProtect(u32 address, u16 data)
{
    return FLASH_ProgramOptionHalfWord(address, data);

//    FLASH_Status ret;
//  ret = FLASH_ProgramOptionHalfWord(address, 0x7F80);
//
//  if (ret == FLASH_COMPLETE) {
//      ret = FLASH_ProgramOptionHalfWord(address + 2, 0xFF00);
//    }
//    return ret;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Write protection for the specified address
/// @note   This function can be used for all MM32 devices.
/// @param  page: specifies the address of the pages to be write
///         protected.
///         This parameter is (0x01 << ((Absolute address - 0x08000000)/0x1000))
/// @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
///         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_EnableWriteProtection(u32 page)
{
    FLASH_Status ret;
    u8           i;
    for (i = 0; i < 4; i++) {
        ret = FLASH_ProgramOptionHalfWord((OB_BASE + 8 + i * 2), ~(page >> (i * 8)));
        if (ret != FLASH_COMPLETE) {
            break;
        }
    }
    return ret;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
/// @note   This function can be used for all MM32 devices.
/// @param  ob_iwdg: Selects the IWDG mode
/// @param  ob_stop: Reset event when entering STOP mode.
/// @param  standby: Reset event when entering Standby mode.
/// @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
///         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_UserOptionByteConfig(OB_IWDG_TypeDef ob_iwdg, OB_STOP_TypeDef ob_stop, OB_STDBY_TypeDef standby)
{
    FLASH_OPTB_Enable();
    FLASH->CR |= FLASH_CR_OPTPG;
    OB->USER = ob_iwdg;
    OB->USER |= ob_stop;
    OB->USER |= standby;
    OB->USER |= 0xF8;
    //    OB->USER = iwdg | stop | stdby | 0xF8;
    return FLASH_WaitForLastOperation(ProgramTimeout);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the FLASH User Option Bytes values.
/// @note   This function can be used for all MM32 devices.
/// @param  None.
/// @retval The FLASH User Option Bytes values:IWDG_SW(Bit0), RST_STOP(Bit1)
///         and RST_STDBY(Bit2).
////////////////////////////////////////////////////////////////////////////////
u32 FLASH_GetUserOptionByte()
{
    return (FLASH->OBR >> 2);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the FLASH Write Protection Option Bytes Register value.
/// @note   This function can be used for all MM32 devices.
/// @param  None.
/// @retval The FLASH Write Protection  Option Bytes Register value.
////////////////////////////////////////////////////////////////////////////////
u32 FLASH_GetWriteProtectionOptionByte()
{
    return (FLASH->WRPR);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the FLASH Prefetch Buffer status is set or not.
/// @note   This function can be used for all MM32 devices.
/// @param  None.
/// @retval FLASH Prefetch Buffer Status (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus FLASH_GetPrefetchBufferStatus(void)
{
    return (FLASH->ACR & FLASH_ACR_PRFTBS) ? SET : RESET;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified FLASH interrupts.
/// @note   This function can be used for all MM32 devices.
/// @param  interrupt: specifies the FLASH interrupt sources to be enabled or
///         disabled.
/// @param  state: new state of the specified Flash interrupts.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void FLASH_ITConfig(FLASH_IT_TypeDef interrupt, FunctionalState state)
{
    (state) ? (FLASH->CR |= interrupt) : (FLASH->CR &= ~interrupt);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified FLASH flag is set or not.
/// @note   This function can be used for all MM32 devices.
/// @param  flag: specifies the FLASH flags to clear.
///         This parameter can be one of the following values:
/// @arg    FLASH_FLAG_BSY: FLASH Busy flag
/// @arg    FLASH_FLAG_PGERR: FLASH Program error flag
/// @arg    FLASH_FLAG_WRPRTERR: FLASH Write protected error flag
/// @arg    FLASH_FLAG_EOP: FLASH End of Operation flag
/// @arg    FLASH_FLAG_OPTERR:  FLASH Option Byte error flag
/// @retval The new state of FLASH_FLAG (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus FLASH_GetFlagStatus(u16 flag)
{
    return ((flag == FLASH_FLAG_OPTERR) ? (FLASH->OBR & FLASH_FLAG_OPTERR) : (FLASH->SR & flag)) ? SET : RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the FLASH's pending flags.
/// @note   This function can be used for all MM32 devices.
/// @param  flag: specifies the FLASH flags to clear.
///         This parameter can be any combination of the following values:
/// @arg    FLASH_FLAG_PGERR: FLASH Program error flag
/// @arg    FLASH_FLAG_WRPRTERR: FLASH Write protected error flag
/// @arg    FLASH_FLAG_EOP: FLASH End of Operation flag
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void FLASH_ClearFlag(u16 flag)
{
    FLASH->SR = flag;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the FLASH Status.
/// @note   This function can be used for all MM32 devices.
/// @param  None.
/// @retval FLASH Status: The returned value can be: FLASH_BUSY,
///         FLASH_ERROR_PG, FLASH_ERROR_WRP or FLASH_COMPLETE.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_GetStatus()
{
    return (FLASH_Status)((FLASH->SR & FLASH_FLAG_BSY))
           ? FLASH_BUSY
           : ((FLASH->SR & FLASH_FLAG_PGERR) ? FLASH_ERROR_PG
              : ((FLASH->SR & FLASH_FLAG_WRPRTERR) ? FLASH_ERROR_WRP : FLASH_COMPLETE));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Waits for a Flash operation to complete or a TIMEOUT to occur.
/// @note   This function can be used for all MM32 devices
/// @param  time_out: FLASH programming time_out
/// @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
///         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
////////////////////////////////////////////////////////////////////////////////
FLASH_Status FLASH_WaitForLastOperation(u32 time_out)
{
    u32          i;
    FLASH_Status ret;
    do {
        ret = FLASH_GetStatus();
        time_out--;
        for (i = 0xFF; i != 0; i--)
            ;
    } while ((ret == FLASH_BUSY) && (time_out != 0x00));

    FLASH->CR = 0;
    FLASH->SR = FLASH_SR_EOP | FLASH_SR_WRPRTERR | FLASH_SR_PGERR;
    return (FLASH_Status)((time_out == 0x00) ? FLASH_TIMEOUT : ret);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Erases a specified FLASH page.
/// @note   This function can be used for all MM32 devices.
/// @param  Page_Address: The page address to be erased.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exFLASH_EraseEE(u32 page_address)
{
    FLASH_Unlock();
    FLASH_ErasePage(page_address);
    FLASH_Lock();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Programs a buffer at a specified address.
/// @note   This function can be used for all MM32 devices.
/// @param *buf: the pointer of the buffer to be programmed.
/// @param  addr: specifies the address to be programmed.
/// @param  len: the number of bytes in the buffer.
///         This parameter can only be even.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exFLASH_ProgramEE(u16* buf, u32 addr, u16 len)
{
    u16 i;
    FLASH_Unlock();
    for (i = 0; i < len / 2; i++) {
        FLASH_ProgramHalfWord(addr, *buf);
        addr += 2;
        buf++;
    }
    FLASH_Lock();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Determine if the data that at the ptr address with the length is len
///         is empty.
/// @note   This function can be used for all MM32 devices.
/// @param *ptr: the pointer of the starting address.
/// @param  len: the number of bytes.
///         This parameter can only be even.
/// @retval 1 presents the data is empty,
///         0 presents the data has been written.
////////////////////////////////////////////////////////////////////////////////
u8 exFLASH_FindEmpty(u16* ptr, u16 len)
{
    u16 i;
    for (i = 0; i < (len / 2); i++) {
        if (*(ptr + i) != 0xffff)
            return 0;
    }
    return 1;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Locate the writable area on the specified address.
/// @note   This function can be used for all MM32 devices.
/// @param  page_address: specifies the beginning of the EEprom.
///         The EEprom can be some continuously pages in the flash.
/// @param  len: the number of bytes to be written.
///         This parameter can only be even.
/// @retval the pointer of the starting address.
////////////////////////////////////////////////////////////////////////////////
void* exFLASH_Locate(u32 page_address, u16 len)
{
    u16 i;
    u16* ptr = (u16*)page_address;
    for (i = 0; i < (0x0800 / len); i++) {
        if (exFLASH_FindEmpty(ptr, len)) {
            if (i == 0)
                return 0;
            break;
        }
        ptr += len / 2;
    }
    return ptr;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Programs a buffer at a specified address.
/// @note   This function can be used for all MM32 devices.
/// @param *buf: the pointer of the buffer to be programmed.
/// @param  page_address: specifies the beginning of the EEprom.
///         The EEprom can be some continuously pages in the flash.
/// @param  len: the number of bytes in the buffer.
///         This parameter can only be even.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exFLASH_WriteEE(u16* buf, u32 page_address, u16 len)
{
    u16* ptr = exFLASH_Locate(page_address, len);
    if (ptr == 0) {
        exFLASH_EraseEE(page_address + 0x000);
        exFLASH_EraseEE(page_address + 0x400);
        exFLASH_ProgramEE(buf, page_address, len);
    }
    else {
        if (ptr == (u16*)(page_address + ((0x0400 / len) - 1) * len)) {
            exFLASH_EraseEE(page_address + 0x400);
            exFLASH_ProgramEE(buf, (u32)ptr, len);
        }
        else if (ptr == (u16*)(page_address + 0x0800)) {
            exFLASH_EraseEE(page_address + 0x000);
            exFLASH_ProgramEE(buf, (u32)page_address, len);
        }
        else {
            exFLASH_ProgramEE(buf, (u32)ptr, len);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Read the beginning address of the last written data.
/// @note   This function can be used for all MM32 devices.
/// @param  page_address: specifies the beginning of the EEprom.
///         The EEprom can be some continuously pages in the flash.
/// @param  len: the number of bytes have been written.
///         This parameter can only be even.
/// @retval the beginning address of the last written data.
///         0 presents that this is the first time to use this as EEprom.
////////////////////////////////////////////////////////////////////////////////
void* exFLASH_ReadEE(u32 page_address, u16 len)
{
    u16* ptr = exFLASH_Locate(page_address, len);
    return (ptr == 0) ? 0 : (ptr - len / 2);
}

/// @}

/// @}

/// @}
