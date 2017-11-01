#include "Driver_USBD.h"

#define ARM_USBD_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0) /* driver version */

/* Driver Version */
static const ARM_DRIVER_VERSION usbd_driver_version = { 
    ARM_USBD_API_VERSION,
    ARM_USBD_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_USBD_CAPABILITIES usbd_driver_capabilities = {
    0, /* vbus_detection */
    0, /* event_vbus_on */
    0  /* event_vbus_off */
};

//
// Functions
//

ARM_DRIVER_VERSION ARM_USBD_GetVersion(void)
{
}

ARM_USBD_CAPABILITIES ARM_USBD_GetCapabilities(void)
{
}

int32_t ARM_USBD_Initialize(ARM_USBD_SignalDeviceEvent_t cb_device_event,
                            ARM_USBD_SignalEndpointEvent_t cb_endpoint_event)
{
}

int32_t ARM_USBD_Uninitialize(void)
{
}

int32_t ARM_USBD_PowerControl(ARM_POWER_STATE state)
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

int32_t ARM_USBD_DeviceConnect(void)
{
}

int32_t ARM_USBD_DeviceDisconnect(void)
{
}

ARM_USBD_STATE ARM_USBD_DeviceGetState(void)
{
}

int32_t ARM_USBD_DeviceRemoteWakeup(void)
{
}

int32_t ARM_USBD_DeviceSetAddress(uint8_t dev_addr)
{
}

int32_t ARM_USBD_ReadSetupPacket(uint8_t *setup)
{
}

int32_t ARM_USBD_EndpointConfigure(uint8_t ep_addr,
                                   uint8_t ep_type,
                                   uint16_t ep_max_packet_size)
{
}

int32_t ARM_USBD_EndpointUnconfigure(uint8_t ep_addr)
{
}

int32_t ARM_USBD_EndpointStall(uint8_t ep_addr, bool stall)
{
}

int32_t ARM_USBD_EndpointTransfer(uint8_t ep_addr, uint8_t *data, uint32_t num)
{
}

uint32_t ARM_USBD_EndpointTransferGetResult(uint8_t ep_addr)
{
}

int32_t ARM_USBD_EndpointTransferAbort(uint8_t ep_addr)
{
}

uint16_t ARM_USBD_GetFrameNumber(void)
{
}

void ARM_USBD_SignalDeviceEvent(uint32_t event)
{
    // function body
}

void ARM_USBD_SignalEndpointEvent(uint8_t ep_addr, uint32_t ep_event)
{
    // function body
}

// End USBD Interface

ARM_DRIVER_USBD Driver_USBD =
{
    ARM_USBD_GetVersion,
    ARM_USBD_GetCapabilities,
    ARM_USBD_Initialize,
    ARM_USBD_Uninitialize,
    ARM_USBD_PowerControl,
    ARM_USBD_DeviceConnect,
    ARM_USBD_DeviceDisconnect,
    ARM_USBD_DeviceGetState,
    ARM_USBD_DeviceRemoteWakeup,
    ARM_USBD_DeviceSetAddress,
    ARM_USBD_EndpointConfigure,
    ARM_USBD_EndpointUnconfigure,
    ARM_USBD_EndpointStall,
    ARM_USBD_EndpointTransfer,
    ARM_USBD_EndpointTransferGetResult,
    ARM_USBD_EndpointTransferAbort,
    ARM_USBD_GetFrameNumber
};
