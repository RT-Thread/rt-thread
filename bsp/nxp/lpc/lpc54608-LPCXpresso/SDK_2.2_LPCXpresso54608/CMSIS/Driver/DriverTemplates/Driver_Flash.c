#include "Driver_Flash.h"

#define ARM_FLASH_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */

/* Sector Information */
#ifdef FLASH_SECTORS
static ARM_FLASH_SECTOR FLASH_SECTOR_INFO[FLASH_SECTOR_COUNT] = {
    FLASH_SECTORS
};
#else
#define FLASH_SECTOR_INFO    NULL
#endif

/* Flash Information */
static ARM_FLASH_INFO FlashInfo = {
    0, /* FLASH_SECTOR_INFO  */
    0, /* FLASH_SECTOR_COUNT */
    0, /* FLASH_SECTOR_SIZE  */
    0, /* FLASH_PAGE_SIZE    */
    0, /* FLASH_PROGRAM_UNIT */
    0  /* FLASH_ERASED_VALUE */
};

/* Flash Status */
static ARM_FLASH_STATUS FlashStatus;

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_FLASH_API_VERSION,
    ARM_FLASH_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_FLASH_CAPABILITIES DriverCapabilities = {
    0, /* event_ready */
    0, /* data_width = 0:8-bit, 1:16-bit, 2:32-bit */
    0  /* erase_chip */
};

//
// Functions
//

ARM_DRIVER_VERSION ARM_Flash_GetVersion(void)
{
}

ARM_FLASH_CAPABILITIES ARM_Flash_GetCapabilities(void)
{
}

int32_t ARM_Flash_Initialize(ARM_Flash_SignalEvent_t cb_event)
{
}

int32_t ARM_Flash_Uninitialize(void)
{
}

int32_t ARM_Flash_PowerControl(ARM_POWER_STATE state)
{
    switch (state)
    {
    case ARM_POWER_OFF:
        break;

    case ARM_POWER_LOW:
        break;

    case ARM_POWER_FULL:
        break;

    default:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

int32_t ARM_Flash_ReadData(uint32_t addr, void *data, uint32_t cnt)
{
}

int32_t ARM_Flash_ProgramData(uint32_t addr, const void *data, uint32_t cnt)
{
}

int32_t ARM_Flash_EraseSector(uint32_t addr)
{
}

int32_t ARM_Flash_EraseChip(void)
{
}

ARM_FLASH_STATUS ARM_Flash_GetStatus(void)
{
}

ARM_FLASH_INFO * ARM_Flash_GetInfo(void)
{
}

void ARM_Flash_SignalEvent(uint32_t event)
{
}
