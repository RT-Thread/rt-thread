#include "Driver_MCI.h"

#define ARM_MCI_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0) /* driver version */

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_MCI_API_VERSION,
    ARM_MCI_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_MCI_CAPABILITIES DriverCapabilities = {
    0, /* cd_state          */
    0, /* cd_event          */
    0, /* vdd               */
    0, /* vdd_1v8           */
    0, /* vccq              */
    0, /* vccq_1v8          */
    0, /* vccq_1v2          */
    1, /* data_width_4      */
    1, /* data_width_8      */
    0, /* data_width_4_ddr  */
    0, /* data_width_8_ddr  */
    0, /* high_speed        */
    0, /* uhs_signaling     */
    0, /* uhs_tuning        */
    0, /* uhs_sdr50         */
    0, /* uhs_sdr104        */
    0, /* uhs_ddr50         */
    0, /* uhs_driver_type_a */
    0, /* uhs_driver_type_c */
    0, /* uhs_driver_type_d */
    1, /* sdio_interrupt    */
    1, /* read_wait         */
    0, /* suspend_resume    */
    0, /* mmc_interrupt     */
    0, /* mmc_boot          */
    0, /* ccs               */
    0  /* ccs_timeout       */
};

//
//   Functions
//

ARM_DRIVER_VERSION ARM_MCI_GetVersion(void)
{
}

ARM_MCI_CAPABILITIES ARM_MCI_GetCapabilities(void)
{
}

int32_t ARM_MCI_Initialize(ARM_MCI_SignalEvent_t cb_event)
{
}

int32_t ARM_MCI_Uninitialize(void)
{
}

int32_t ARM_MCI_PowerControl(ARM_POWER_STATE state)
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

int32_t ARM_MCI_CardPower(uint32_t voltage)
{
    switch (voltage & ARM_MCI_POWER_VDD_Msk)
    {
    case ARM_MCI_POWER_VDD_OFF:
        return ARM_DRIVER_OK;

    case ARM_MCI_POWER_VDD_3V3:
        return ARM_DRIVER_OK;

    default:
        break;
    }
}

int32_t ARM_MCI_ReadCD(void)
{
}

int32_t ARM_MCI_ReadWP(void)
{
}

int32_t ARM_MCI_SendCommand(uint32_t cmd, uint32_t arg, uint32_t flags, uint32_t *response)
{
}

int32_t ARM_MCI_SetupTransfer(uint8_t  *data, uint32_t block_count, uint32_t block_size, uint32_t mode)
{
}

int32_t ARM_MCI_AbortTransfer(void)
{
}

int32_t ARM_MCI_Control(uint32_t control, uint32_t arg)
{
    switch (control)
    {
    case ARM_MCI_BUS_SPEED:
        break;

    case ARM_MCI_BUS_SPEED_MODE:
        break;

    case ARM_MCI_BUS_CMD_MODE:
        /* Implement external pull-up control to support MMC cards in open-drain mode */
        /* Default mode is push-pull and is configured in Driver_MCI0.Initialize()    */
        if (arg == ARM_MCI_BUS_CMD_PUSH_PULL)
        {
            /* Configure external circuit to work in push-pull mode */
        }
        else if (arg == ARM_MCI_BUS_CMD_OPEN_DRAIN)
        {
            /* Configure external circuit to work in open-drain mode */
        }
        else
        {
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }
        break;

    case ARM_MCI_BUS_DATA_WIDTH:
        switch (arg)
        {
        case ARM_MCI_BUS_DATA_WIDTH_1:
            break;
        case ARM_MCI_BUS_DATA_WIDTH_4:
            break;
        case ARM_MCI_BUS_DATA_WIDTH_8:
            break;
        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }
        break;

    case ARM_MCI_CONTROL_RESET:
        break;

    case ARM_MCI_CONTROL_CLOCK_IDLE:
        break;

    case ARM_MCI_DATA_TIMEOUT:
        break;

    case ARM_MCI_MONITOR_SDIO_INTERRUPT:
        break;

    case ARM_MCI_CONTROL_READ_WAIT:
        break;

    case ARM_MCI_DRIVER_STRENGTH:
    default: return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

ARM_MCI_STATUS ARM_MCI_GetStatus(void)
{
}

void ARM_MCI_SignalEvent(uint32_t event)
{
    // function body
}

// End MCI Interface

ARM_DRIVER_MCI Driver_MCI = {
    ARM_MCI_GetVersion,
    ARM_MCI_GetCapabilities,
    ARM_MCI_Initialize,
    ARM_MCI_Uninitialize,
    ARM_MCI_PowerControl,
    ARM_MCI_CardPower,
    ARM_MCI_ReadCD,
    ARM_MCI_ReadWP,
    ARM_MCI_SendCommand,
    ARM_MCI_SetupTransfer,
    ARM_MCI_AbortTransfer,
    ARM_MCI_Control,
    ARM_MCI_GetStatus
};
