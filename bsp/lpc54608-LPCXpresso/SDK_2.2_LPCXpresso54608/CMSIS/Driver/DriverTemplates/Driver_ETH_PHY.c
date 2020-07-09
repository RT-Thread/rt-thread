#include "Driver_ETH_PHY.h"

#define ARM_ETH_PHY_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0) /* driver version */

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_ETH_PHY_API_VERSION,
    ARM_ETH_PHY_DRV_VERSION
};

//
// Functions
//

ARM_DRIVER_VERSION ARM_ETH_PHY_GetVersion(void)
{
}

int32_t ARM_ETH_PHY_Initialize(ARM_ETH_PHY_Read_t fn_read, ARM_ETH_PHY_Write_t fn_write)
{
}

int32_t ARM_ETH_PHY_Uninitialize(void)
{
}

int32_t ARM_ETH_PHY_PowerControl(ARM_POWER_STATE state)
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

int32_t ARM_ETH_PHY_SetInterface(uint32_t interface)
{
    switch (interface)
    {
    case ARM_ETH_INTERFACE_MII:
        break;
    case ARM_ETH_INTERFACE_RMII:
        break;
    default:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

int32_t ARM_ETH_PHY_SetMode(uint32_t mode)
{
    switch (mode & ARM_ETH_PHY_SPEED_Msk)
    {
    case ARM_ETH_PHY_SPEED_10M:
        break;
    case ARM_ETH_PHY_SPEED_100M:
        break;
    default:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    switch (mode & ARM_ETH_PHY_DUPLEX_Msk)
    {
    case ARM_ETH_PHY_DUPLEX_HALF:
        break;
    case ARM_ETH_PHY_DUPLEX_FULL:
        break;
    }

    if (mode & ARM_ETH_PHY_AUTO_NEGOTIATE)
    {
    }

    if (mode & ARM_ETH_PHY_LOOPBACK)
    {
    }

    if (mode & ARM_ETH_PHY_ISOLATE)
    {
    }
}

ARM_ETH_LINK_STATE ARM_ETH_PHY_GetLinkState(void)
{
}

ARM_ETH_LINK_INFO ARM_ETH_PHY_GetLinkInfo(void)
{
}

ARM_DRIVER_ETH_PHY ARM_Driver_ETH_PHY_(ETH_PHY_NUM) =
{
    ARM_ETH_PHY_GetVersion,
    ARM_ETH_PHY_Initialize,
    ARM_ETH_PHY_Uninitialize,
    ARM_ETH_PHY_PowerControl,
    ARM_ETH_PHY_SetInterface,
    ARM_ETH_PHY_SetMode,
    ARM_ETH_PHY_GetLinkState,
    ARM_ETH_PHY_GetLinkInfo,
};
