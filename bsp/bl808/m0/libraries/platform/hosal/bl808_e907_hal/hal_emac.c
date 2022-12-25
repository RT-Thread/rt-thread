/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "bl808_emac.h"
#include "bl_irq.h"
#include "bl808_glb.h"
#include "hal_emac.h"
#include "bl808_l1c.h"
#if CTX_TYPE
#include <FreeRTOS.h>
#include <task.h>
#endif

#define EMAC_USE_INSIDE_CLOCK   (0)
#define TAG                     "EMAC_BD: "
#define EMAC_USED_ID            EMAC0_ID

static const uint32_t emacAddr[EMAC_ID_MAX] = { EMAC_BASE };

#ifdef EMAC_DBG
#define MSG                     printf
#else
#define MSG(...)                ((void)0)
#endif
#define EMAC_DO_FLUSH_DATA      1

#if CTX_TYPE
extern TaskHandle_t DequeueTaskHandle;
#endif
static EMAC_Handle_Type ethHandle;
EMAC_Handle_Type *thiz = NULL;

/**
 * @brief
 *
 */
static void emac_gpio_init(void)
{
    uint8_t emacPins[] = { GLB_GPIO_PIN_24, GLB_GPIO_PIN_25, GLB_GPIO_PIN_26,
                           GLB_GPIO_PIN_27, GLB_GPIO_PIN_28, GLB_GPIO_PIN_29,
                           GLB_GPIO_PIN_30, GLB_GPIO_PIN_31, GLB_GPIO_PIN_32,
                           GLB_GPIO_PIN_33 };

    GLB_GPIO_Func_Init(GPIO_FUN_ETHER_MAC, (GLB_GPIO_Type *)emacPins, sizeof(emacPins));
}

/**
 * @brief
 *
 * @param bdt
 * @return int
 */
static uint32_t emac_bd_get_cur_active(EMAC_BD_TYPE_e bdt)
{
    uint32_t bd = 0;

    EMAC_GetBD(EMAC_USED_ID, &bd);

    if (bdt == EMAC_BD_TYPE_TX) {
        bd &= EMAC_TXBDPTR_MSK;
        bd >>= EMAC_TXBDPTR_POS;
    }

    if (bdt == EMAC_BD_TYPE_RX) {
        bd &= EMAC_RXBDPTR_MSK;
        bd >>= EMAC_RXBDPTR_POS;
    }

    return bd;
}

/**
 * @brief
 *
 * @param index
 * @return int
 */
static int emac_bd_rx_enqueue(uint32_t index)
{
    BL_Err_Type err = SUCCESS;

    thiz->rxIndexEMAC = index;

    return err;
}

/**
 * @brief
 *
 * @param index
 * @return int
 */
static void emac_bd_rx_on_err(uint32_t index)
{
    /* handle error */
    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(RX_OR)) {
        MSG("EMAC RX OR Error at %s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(RX_RE)) {
        MSG("MAC RX RE Error at %s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(RX_DN)) {
        MSG("MAC RX DN Error at %s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(RX_TL)) {
        MSG("MAC RX TL Error at %s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(RX_CRC)) {
        MSG("MAC RX CRC Error at %s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(RX_LC)) {
        MSG("MAC RX LC Error at %s:%d\r\n", __func__, __LINE__);
    }

    thiz->bd[index].C_S_L &= ~0xff;
    /* RX BD is ready for RX */
    thiz->bd[index].C_S_L |= EMAC_BD_FIELD_MSK(RX_E);
}

/**
 * @brief this func will be called in ISR
 *
 * @param index
 * @return int
 */
static int emac_bd_tx_dequeue(uint32_t index)
{
    BL_Err_Type err = SUCCESS;
    EMAC_BD_Desc_Type *DMADesc;

    thiz->txIndexEMAC = index;
    DMADesc = &thiz->bd[thiz->txIndexEMAC];
    /* release this tx BD to SW (HW will do this) */
    DMADesc->C_S_L &= EMAC_BD_FIELD_UMSK(TX_RD);

    return err;
}

/**
 * @brief
 *
 * @param index
 * @return int
 */
static void emac_bd_tx_on_err(uint32_t index)
{
    /* handle error */
    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(TX_UR)) {
        MSG("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(TX_RTRY)) {
        MSG("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(TX_RL)) {
        MSG("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(TX_LC)) {
        MSG("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(TX_DF)) {
        MSG("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & EMAC_BD_FIELD_MSK(TX_CS)) {
        MSG("%s:%d\r\n", __func__, __LINE__);
    }

    thiz->bd[index].C_S_L &= ~0xff;
}

/**
 * @brief
 *
 */
__WEAK void emac_tx_done_callback_app(void)
{
}

/**
 * @brief
 *
 */
static void emac_tx_done_callback(void)
{
#if CTX_TYPE
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTaskNotifyFromISR(DequeueTaskHandle, 0x01, eSetBits, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#else
    uint32_t index = 0;
    index = emac_bd_get_cur_active(EMAC_BD_TYPE_TX);

    emac_bd_tx_dequeue(index);

    emac_tx_done_callback_app();
#endif
}

/**
 * @brief
 *
 */
__WEAK void emac_tx_error_callback_app(void)
{
    puts("Tx error\r\n");
}

/**
 * @brief
 *
 */
static void emac_tx_error_callback(void)
{
    uint32_t index = 0;

    index = emac_bd_get_cur_active(EMAC_BD_TYPE_TX);
    emac_bd_tx_on_err(index);
    emac_tx_error_callback_app();
}

/**
 * @brief
 *
 */
__WEAK void emac_rx_done_callback_app(void)
{
}

/**
 * @brief
 *
 */
static void emac_rx_done_callback(void)
{
#if CTX_TYPE
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTaskNotifyFromISR(DequeueTaskHandle, 0x02, eSetBits, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#else
    uint32_t index = 0;

    index = emac_bd_get_cur_active(EMAC_BD_TYPE_RX);

    emac_bd_rx_enqueue(index);

    emac_rx_done_callback_app();
#endif
}

/**
 * @brief
 *
 */
__WEAK void emac_rx_error_callback_app(void)
{
    puts("Rx error\r\n");
}

/**
 * @brief
 *
 */
static void emac_rx_error_callback(void)
{
    uint32_t index;

    index = emac_bd_get_cur_active(EMAC_BD_TYPE_RX);

    emac_bd_rx_on_err(index);

    emac_rx_error_callback_app();
}

/**
 * @brief
 *
 */
__WEAK void emac_rx_busy_callback_app(void)
{
}

/**
 * @brief
 *
 */
static void emac_rx_busy_callback(void)
{
    MSG("EMAC Rx busy at %s:%d\r\n", __func__, __LINE__);
    emac_rx_busy_callback_app();
}

void emac_irq_process(void)
{
    EMAC_ID_Type emacId = EMAC_USED_ID;
    uint32_t tmpVal;
    uint32_t EMACx = emacAddr[emacId];
    
    tmpVal = BL_RD_REG(EMACx,EMAC_INT_MASK);
    
    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_TX_DONE) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_TXB_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_TX_DONE);
        EMAC_IntMask(emacId, EMAC_INT_TX_DONE, MASK);
        emac_tx_done_callback();
    }

    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_TX_ERROR) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_TXE_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_TX_ERROR);
        emac_tx_error_callback();
    }

    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_RX_DONE) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_RXB_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_RX_DONE);
        EMAC_IntMask(emacId, EMAC_INT_RX_DONE, MASK);
        emac_rx_done_callback();
    }

    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_RX_ERROR) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_RXE_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_RX_ERROR);
        emac_rx_error_callback();
    }

    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_RX_BUSY) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_BUSY_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_RX_BUSY);
        emac_rx_busy_callback();
    }

    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_TX_CTRL) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_TXC_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_TX_CTRL);
    }

    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_RX_CTRL) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_RXC_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_RX_CTRL);
    }
}

void EMAC_Interrupt_Init(void)
{
    MSG("EMAC_Interrupt_Init.\r\n");
    bl_irq_register(EMAC_IRQn, emac_irq_process);
    bl_irq_enable(EMAC_IRQn);

    EMAC_ClrIntStatus(EMAC_USED_ID,EMAC_INT_ALL);
    EMAC_IntMask(EMAC_USED_ID,EMAC_INT_ALL, UNMASK);
    MSG("emac_intmask.\r\n");
}
/**
 * @brief
 *
 * @param emac_cfg
 * @return int
 */
int emac_init(emac_device_t *emac_cfg)
{
    EMAC_CFG_Type emacCfg = {
        .recvSmallFrame = ENABLE,           /*!< Receive small frmae or not */
        .recvHugeFrame = DISABLE,           /*!< Receive huge frmae(>64K bytes) or not */
        .padEnable = ENABLE,                /*!< Enable padding for frame which is less than MINFL or not */
        .crcEnable = ENABLE,                /*!< Enable hardware CRC or not */
        .noPreamble = DISABLE,              /*!< Enable preamble or not */
        .recvBroadCast = ENABLE,            /*!< Receive broadcast frame or not */
        .interFrameGapCheck = ENABLE,       /*!< Check inter frame gap or not */
        .miiNoPreamble = ENABLE,            /*!< Enable MII interface preamble or not */
        .miiClkDiv = 49,                    /*!< MII interface clock divider from bus clock */
        .maxTxRetry = 16,                   /*!< Maximum tx retry count */
        .interFrameGapValue = 24,           /*!< Inter frame gap vaule in clock cycles(default 24)*/
        .minFrameLen = 64,                  /*!< Minimum frame length */
        .maxFrameLen = ETH_MAX_PACKET_SIZE, /*!< Maximum frame length */
        .collisionValid = 16,               /*!< Collision valid value */
        .macAddr[0] = 0x18,                 /*!< MAC Address */
        .macAddr[1] = 0xB0,
        .macAddr[2] = 0x09,
        .macAddr[3] = 0x00,
        .macAddr[4] = 0x12,
        .macAddr[5] = 0x34,
    };
    BL_Err_Type err = SUCCESS;

    /* init emac giio */
    emac_gpio_init();

    memcpy(emacCfg.macAddr, emac_cfg->mac_addr, 6);
    GLB_PER_Clock_UnGate(1<<12);
#if EMAC_USE_INSIDE_CLOCK
    /* 50MHZ clock is from uhs pll */
    GLB_Set_ETH_REF_O_CLK_Sel(GLB_ETH_REF_CLK_OUT_INSIDE_50M);
#else
    GLB_Set_ETH_REF_O_CLK_Sel(GLB_ETH_REF_CLK_OUT_OUTSIDE_50M);
#endif
    //GLB_AHB_Slave1_Clock_Gate(DISABLE, BL_AHB_SLAVE1_EMAC);
    GLB_PER_Clock_UnGate(1<<12);
    //GLB_Invert_ETH_RX_CLK(0);
    //GLB_Invert_ETH_TX_CLK(0);
    EMAC_Init(EMAC_USED_ID,&emacCfg);

    EMAC_Interrupt_Init();
    return err;
}

/**
 * @brief
 *
 * @param eth_tx_buff
 * @param tx_buf_count
 * @param eth_rx_buff
 * @param rx_buf_count
 * @return int
 */
int emac_bd_init(uint8_t *eth_tx_buff, uint8_t tx_buf_count, uint8_t *eth_rx_buff, uint8_t rx_buf_count)
{
    BL_Err_Type err = SUCCESS;
    thiz = &ethHandle;

    /* init the BDs in emac with buffer address */
    err = EMAC_DMADescListInit(EMAC_USED_ID,thiz, (uint8_t *)eth_tx_buff, tx_buf_count,
                               (uint8_t *)eth_rx_buff, rx_buf_count);
    return err;
}

/**
 * @brief
 *
 * @param none
 * @return int
 */
int emac_bd_fragment_support(void){
    return 1;
}

/**
 * @brief
 *
 * @param flags
 * @param len
 * @param data_in
 * @return int
 */
//uint32_t tmpbuf[400];
int emac_bd_tx_enqueue(uint32_t flags, uint32_t len, const uint8_t *data_in)
{
    BL_Err_Type err = SUCCESS;
    EMAC_BD_Desc_Type *DMADesc;
    uint32_t tx_flags=EMAC_TX_COMMON_FLAGS;
    DMADesc = &thiz->bd[thiz->txIndexCPU];

    if (flags&EMAC_FRAGMENT_PACKET) {
        /* Fragment packet, clear EOF */
        tx_flags &= EMAC_BD_FIELD_UMSK(TX_EOF);
    }

    if (DMADesc->C_S_L & EMAC_BD_FIELD_MSK(TX_RD)) {
        /* no free BD, lost sync with DMA TX? */
        err = NORESC;
        //MSG(TAG"%s:%d\n", __func__, __LINE__);
    } else {
        __DSB();
        // MSG("tx q flags:%d,len:%d,data:0x%x\r\n", flags, len, data_in);
        if (flags&EMAC_NOCOPY_PACKET) {
            DMADesc->Buffer = (uint32_t)data_in;
        }else{
            ARCH_MemCpy_Fast((void *)DMADesc->Buffer, data_in, len);
        }

        /* following two lines is for cache test since tmpbuf is in cache range */
        //ARCH_MemCpy_Fast(tmpbuf, data_in, len);        
        //DMADesc->Buffer = (uint32_t)tmpbuf;
#ifdef EMAC_DO_FLUSH_DATA
        if(L1C_Is_DCache_Range((uintptr_t)DMADesc->Buffer)){
            L1C_DCache_Clean_By_Addr((uintptr_t)DMADesc->Buffer,len);
        }
#endif
        DMADesc->C_S_L = tx_flags | (len << BD_TX_LEN_POS);

        /* move to next TX BD */
        if ((++thiz->txIndexCPU) > thiz->txBuffLimit) {
            /* the last BD */
            DMADesc->C_S_L |= EMAC_BD_FIELD_MSK(TX_WR);
            /* wrap back */
            thiz->txIndexCPU = 0;
        }
    }

    return err;
}

/**
 * @brief
 *
 * @param flags
 * @param len
 * @param data_out
 * @return int
 */
int emac_bd_rx_dequeue(uint32_t flags, uint32_t *len, uint8_t *data_out)
{
    BL_Err_Type err = SUCCESS;
    EMAC_BD_Desc_Type *DMADesc;

    DMADesc = &thiz->bd[thiz->rxIndexCPU];

    if (DMADesc->C_S_L & EMAC_BD_FIELD_MSK(RX_E)) {
        /* current RX BD is empty */
        err = NORESC;
        *len = 0;
    } else {
        *len = (thiz->bd[thiz->rxIndexCPU].C_S_L & EMAC_BD_FIELD_MSK(RX_LEN)) >> BD_RX_LEN_POS;
#ifdef EMAC_DO_FLUSH_DATA
        if(L1C_Is_DCache_Range((uintptr_t)DMADesc->Buffer)){
            L1C_DCache_Invalid_By_Addr((uintptr_t)DMADesc->Buffer, *len);
        }
#endif
        if (data_out) {
            ARCH_MemCpy_Fast(data_out, (const void *)(uintptr_t)DMADesc->Buffer, *len);
        }

        /* RX BD can be used for another receive */
        DMADesc->C_S_L |= EMAC_BD_FIELD_MSK(RX_E);

        /* move to next RX BD */
        if ((++thiz->rxIndexCPU) > thiz->rxBuffLimit) {
            /* the last BD */
            DMADesc->C_S_L |= EMAC_BD_FIELD_MSK(RX_WR);
            /* wrap back */
            thiz->rxIndexCPU = thiz->txBuffLimit + 1;
        }
    }

    return err;
}

/**
 * @brief
 *
 * @param phyAddress
 * @return int
 */
int emac_phy_set_address(uint16_t phyAddress)
{
    EMAC_Phy_SetAddress(EMAC_USED_ID,phyAddress);

    return 0;
}

/**
 * @brief
 *
 * @param fullDuplex
 * @return int
 */
int emac_phy_config_full_duplex(uint8_t fullDuplex)
{
    EMAC_Phy_Set_Full_Duplex(EMAC_USED_ID,fullDuplex);

    return 0;
}

/**
 * @brief
 *
 * @param phyReg
 * @param regValue
 * @return int
 */
int emac_phy_reg_read(uint16_t phyReg, uint16_t *regValue)
{
    if (EMAC_Phy_Read(EMAC_USED_ID,phyReg, regValue) != SUCCESS) {
        return -1;
    }

    return 0;
}

/**
 * @brief
 *
 * @param phyReg
 * @param regValue
 * @return int
 */
int emac_phy_reg_write(uint16_t phyReg, uint16_t regValue)
{
    if (EMAC_Phy_Write(EMAC_USED_ID,phyReg, regValue) != SUCCESS) {
        return -1;
    }

    return 0;
}

int emac_stop(void)
{
    return EMAC_Disable(EMAC_USED_ID);
}

int emac_start(void)
{
    EMAC_Enable(EMAC_USED_ID);
    return 0;
}

int emac_start_tx(void)
{
    return EMAC_Enable_TX(EMAC_USED_ID);
}

int emac_stop_tx(void)
{
    return EMAC_Disable_TX(EMAC_USED_ID);
}

int emac_start_rx(void)
{
    return EMAC_Enable_RX(EMAC_USED_ID);
}

int emac_stop_rx(void)
{
    return EMAC_Disable_RX(EMAC_USED_ID);
}

int emac_intmask(EMAC_INT_Type intType, BL_Mask_Type intMask)
{
    return EMAC_IntMask(EMAC_USED_ID,intType, intMask);
}

int emac_get_fram_len(uint16_t *max, uint16_t *min)
{
  return EMAC_GetFramLen(EMAC_USED_ID, max, min);
}

