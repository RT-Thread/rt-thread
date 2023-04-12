#include "bl616_sdu.h"

volatile pHidSdio_RegMap_t SdioFuncReg[] =
{
    (pHidSdio_RegMap_t)(BL_SDIO_CCR_BASE),
#if NUM_FUNC == 2
    (pHidSdio_RegMap_t)(BL_SDIO_CCR_BASE+BL_SDIO_CCR_FUNC_OFFSET)
#elif NUM_FUNC == 3
    (pHidSdio_RegMap_t)(BL_SDIO_CCR_BASE+BL_SDIO_CCR_FUNC_OFFSET),
    (pHidSdio_RegMap_t)(BL_SDIO_CCR_BASE+(2 * BL_SDIO_CCR_FUNC_OFFSET))
#endif
};

/* if flag_mport = 0, then it supports mport
 *    flag_mport = 1, then mport disabled
 */
uint8_t flag_mport[NUM_FUNC] = 
{
    0,
#if NUM_FUNC == 2
    1
#elif NUM_FUNC == 3
    1,1
#endif
};

void sdio_GEN_CARD2HOST_INT(uint32_t port_id, uint16_t value)
{
    /* We do not want to generate Download rdy for command port
     * only. Currently there is a condition where if we generate
     * download ready for command, followed by a download
     * ready for data, the download ready for data would be gated
     * by the SDIO controller. To avoid this we do not generate
     * a download ready for command. Download ready is only generated for data.
     */
    /*
    if (!flag_mport[port_id] &&
        (value & SDIO_CCR_CS_DnLdRdy) && (prev_WrBitMap[port_id] == 0x01))
    {
        value &= ~SDIO_CCR_CS_DnLdRdy;
        if (!value)
        {
            return;
        }
    }
    */
    SdioFuncReg[port_id]->CardToHostEvent = value;
}


uint32_t sdio_ioctl(uint32_t port_id, SDIO_CMD_TYPE cmd, void *arg)
{
    switch(cmd)
    {
    case IOCTL_HID_GET_BLOCK_SIZE:
	{
        if (port_id == FUNC_WIFI)
        {
            uint32_t blockSize = BL_REGS8(SDIO_FN1_BLK_SIZE_0);

            blockSize |= ((BL_REGS8(SDIO_FN1_BLK_SIZE_1) & 
                           SDIO_FN1_BLK_SIZE_1_MASK ) << 8);

            if(blockSize == 0)
            {
                blockSize = 512;
            }
            return(blockSize);
        }
        break;
	}
    default:
        break;
    }
    return 0;
}
