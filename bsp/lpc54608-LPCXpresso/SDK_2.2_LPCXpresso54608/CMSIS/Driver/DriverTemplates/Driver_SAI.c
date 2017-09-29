#include "Driver_SAI.h"

#define ARM_SAI_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_SAI_API_VERSION,
    ARM_SAI_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_SAI_CAPABILITIES DriverCapabilities = {
    1, /* supports asynchronous Transmit/Receive */
    0, /* supports synchronous Transmit/Receive */
    0, /* supports user defined Protocol */
    1, /* supports I2S Protocol */
    0, /* supports MSB/LSB justified Protocol */
    0, /* supports PCM short/long frame Protocol */
    0, /* supports AC'97 Protocol */
    0, /* supports Mono mode */
    0, /* supports Companding */
    0, /* supports MCLK (Master Clock) pin */
    0  /* supports Frame error event: \ref ARM_SAI_EVENT_FRAME_ERROR */
};

//
//  Functions
//

ARM_DRIVER_VERSION ARM_SAI_GetVersion (void)
{
}

ARM_SAI_CAPABILITIES ARM_SAI_GetCapabilities (void)
{
}

int32_t ARM_SAI_Initialize (ARM_SAI_SignalEvent_t cb_event)
{
}

int32_t ARM_SAI_Uninitialize (void)
{
}

int32_t ARM_SAI_PowerControl (ARM_POWER_STATE state)
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

int32_t ARM_SAI_Send (const void *data, uint32_t num)
{
}

int32_t ARM_SAI_Receive (void *data, uint32_t num)
{
}

uint32_t ARM_SAI_GetTxCount (void)
{
}

uint32_t ARM_SAI_GetRxCount (void)
{
}

int32_t ARM_SAI_Control (uint32_t control, uint32_t arg1, uint32_t arg2)
{
}

ARM_SAI_STATUS ARM_SAI_GetStatus (void)
{
}

void ARM_SAI_SignalEvent(uint32_t event)
{
    // function body
}

// End SAI Interface

ARM_DRIVER_SAI Driver_SAI = {
    ARM_SAI_GetVersion,
    ARM_SAI_GetCapabilities,
    ARM_SAI_Initialize,
    ARM_SAI_Uninitialize,
    ARM_SAI_PowerControl,
    ARM_SAI_Send,
    ARM_SAI_Receive,
    ARM_SAI_GetTxCount,
    ARM_SAI_GetRxCount,
    ARM_SAI_Control,
    ARM_SAI_GetStatus
};
