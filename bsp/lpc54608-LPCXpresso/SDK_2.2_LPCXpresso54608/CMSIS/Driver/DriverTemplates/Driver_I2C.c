#include "Driver_I2C.h"

#define ARM_I2C_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0) /* driver version */

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_I2C_API_VERSION,
    ARM_I2C_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_I2C_CAPABILITIES DriverCapabilities = {
    0  /* supports 10-bit addressing */
};

//
//  Functions
//

ARM_DRIVER_VERSION ARM_I2C_GetVersion(void)
{
}

ARM_I2C_CAPABILITIES ARM_I2C_GetCapabilities(void)
{
}

int32_t ARM_I2C_Initialize(ARM_I2C_SignalEvent_t cb_event)
{
}

int32_t ARM_I2C_Uninitialize(void)
{
}

int32_t ARM_I2C_PowerControl(ARM_POWER_STATE state)
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

int32_t ARM_I2C_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
}

int32_t ARM_I2C_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
}

int32_t ARM_I2C_SlaveTransmit(const uint8_t *data, uint32_t num)
{
}

int32_t ARM_I2C_SlaveReceive(uint8_t *data, uint32_t num)
{
}

int32_t ARM_I2C_GetDataCount(void)
{
}

int32_t ARM_I2C_Control(uint32_t control, uint32_t arg)
{
    switch (control)
    {
    case ARM_I2C_OWN_ADDRESS:
        break;

    case ARM_I2C_BUS_SPEED:
        switch (arg)
        {
        case ARM_I2C_BUS_SPEED_STANDARD:
            break;
        case ARM_I2C_BUS_SPEED_FAST:
            break;
        case ARM_I2C_BUS_SPEED_FAST_PLUS:
            break;
        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }
        break;

    case ARM_I2C_BUS_CLEAR:
        break;

    case ARM_I2C_ABORT_TRANSFER:
        break;

    default:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

ARM_I2C_STATUS ARM_I2C_GetStatus(void)
{
}

void ARM_I2C_SignalEvent(uint32_t event)
{
    // function body
}

// End I2C Interface

ARM_DRIVER_I2C Driver_I2C = {
    ARM_I2C_GetVersion,
    ARM_I2C_GetCapabilities,
    ARM_I2C_Initialize,
    ARM_I2C_Uninitialize,
    ARM_I2C_PowerControl,
    ARM_I2C_MasterTransmit,
    ARM_I2C_MasterReceive,
    ARM_I2C_SlaveTransmit,
    ARM_I2C_SlaveReceive,
    ARM_I2C_GetDataCount,
    ARM_I2C_Control,
    ARM_I2C_GetStatus
};
