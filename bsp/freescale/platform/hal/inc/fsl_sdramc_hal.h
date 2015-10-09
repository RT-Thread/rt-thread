/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_SDRAMC_HAL_H__
#define __FSL_SDRAMC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_SDRAM_COUNT

/*!
 * @addtogroup sdramc_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Define SDRAM one second with nanosecond*/
#define SDRAM_ONESEC_NANOSECOND        1000000000U

/*! @brief SDRAM auto-refresh timing*/
typedef enum _sdram_refresh_time {
    kSDRAMRefreshThreeClocks = 0x0U,    /*!< The refresh timing with three bus clocks. */
    kSDRAMRefreshSixClocks   = 0x1U,    /*!< The refresh timing with six bus clocks. */
    kSDRAMRefreshNineClocks  = 0x2U     /*!< The refresh timing with nine bus clocks. */
} sdram_refresh_time_t;

/*!
 * @brief Setting latency for SDRAM timing specifications.
 *
 * The latency setting will affects the following SDRAM timing specifications:       
 *       - trcd: SRAS assertion to SCAS assertion \n
 *       - tcasl: SCAS assertion to data out \n
 *       - tras: ACTV command to Precharge command \n
 *       - trp: Precharge command to ACTV command \n
 *       - trwl, trdl: Last data input to Precharge command \n
 *       - tep: Last data out to Precharge command \n
 * the details of the latency setting and timing specifications are shown on the following table list: \n
 *   latency      trcd:          tcasl         tras           trp        trwl,trdl        tep   \n
 *    0       1 bus clock    1 bus clock   2 bus clocks   1 bus clock   1 bus clock   1 bus clock  \n
 *    1       2 bus clock    2 bus clock   4 bus clocks   2 bus clock   1 bus clock   1 bus clock  \n
 *    2       3 bus clock    3 bus clock   6 bus clocks   3 bus clock   1 bus clock   1 bus clock  \n
 *    3       3 bus clock    3 bus clock   6 bus clocks   3 bus clock   1 bus clock   1 bus clock  \n
 */
typedef enum _sdram_latency {
    kSDRAMLatencyZero  = 0x0U,     /*! Latency  0. */
    kSDRAMLatencyOne   = 0x1U,     /*! Latency  1. */
    kSDRAMLatencyTwo   = 0x2U,     /*! Latency  2. */
    kSDRAMLatencyThree = 0x3U      /*! Latency  3. */
} sdram_latency_t;

/*! @brief SDRAM command bit location */
typedef enum _sdram_command_bit_location {
    kSDRAMCommandbit17 = 0x0U,        /*!< Command bit location is bit 17. */
    kSDRAMCommandbit18 = 0x1U,        /*!< Command bit location is bit 18. */
    kSDRAMCommandbit19 = 0x2U,        /*!< Command bit location is bit 19. */
    kSDRAMCommandbit20 = 0x3U,        /*!< Command bit location is bit 20. */
    kSDRAMCommandbit21 = 0x4U,        /*!< Command bit location is bit 21. */
    kSDRAMCommandbit22 = 0x5U,        /*!< Command bit location is bit 22. */
    kSDRAMCommandbit23 = 0x6U,        /*!< Command bit location is bit 23. */
    kSDRAMCommandbit24 = 0x7U         /*!< Command bit location is bit 24. */
} sdram_command_bit_location_t;

/*! @brief SDRAM command */
typedef enum _sdram_command {
    kSDRAMMrsCommand             = 0x0U,   /*!< Initiate mrs command. */
    kSDRAMPrechargeCommand       = 0x1U   /*!< Initiate precharge command.  */
} sdram_command_t;

/*! @brief SDRAM port size */
typedef enum _sdram_port_size {
    kSDRAM32BitPortSize = 0x0U,    /*!< 32-BIT port size. */
    kSDRAM8BitPortSize  = 0x1U,     /*!< 8-Bit port size. */
    kSDRAM16BitPortSize = 0x2U     /*!< 16-Bit port size. */
} sdram_port_size_t;

/*! @brief SDRAM block selection */
typedef enum _sdram_block_selection {
    kSDRAMBlock0   =  0x0U,  /*!< Select SDRAM block 0. */
    kSDRAMBlock1   =  0x1U   /*!< Select SDRAM block 1.  */
} sdram_block_selection_t;

/*!
 * @brief SDRAM control configuration structure for each SDRAM block.
 *
 * Defines a control configuration structure for each SDRAM block.
 *
 * 
 */
typedef struct SDRAMBlockCtlConfigure {
    sdram_port_size_t portSize;      /* The port size of the associated SDRAM block */
    sdram_command_bit_location_t location;   /* The command bit location */
    sdram_latency_t latency;  /* The latency for some timing specifications */
    uint32_t address;         /* The base address of the SDRAM block */
    uint32_t addressMask;     /* The base address mask of the SDRAM block */
} sdram_blockctl_configure_t;
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name SDRAM HAL configuration
 * @{
 */

/*!
 * @brief Sets all registers of the SDRAM controller.
 *
 * @param base Register base address for SDRAM controller.
 */
void SDRAM_HAL_Init(SDRAM_Type * base);

/*!
 * @brief Sends the self-refresh command to SDRAM.
 *
 * @param base Register base address for SDRAM.
 */
static inline void SDRAM_HAL_SendSelfRefreshCmd(SDRAM_Type * base)
{      
    SDRAM_BWR_CTRL_IS(base, 1u);
}

/*!
 * @brief Sends the self-refresh exit command to SDRAM.
 *
 * @param base Register base address for SDRAM.
 */
static inline void SDRAM_HAL_SendSelfRefreshExitCmd(SDRAM_Type * base)
{    
    SDRAM_BWR_CTRL_IS(base, 0u);
}

/*!
 * @brief Sets the control for the SDRAM block.
 *
 * Sets the port size, specification latency, command bit, and 
 * address for the SDRAM block.

 * @param base Register base address for SDRAM.
 * @param whichBlock The block which is selected.
 * @param configure The control configuration structure for the SDRAM block.
 */
void SDRAM_HAL_SetBlockControl(SDRAM_Type *base, sdram_block_selection_t whichBlock, 
                    sdram_blockctl_configure_t *configure);

/*!
 * @brief Sets auto-refresh time and frequency.
 * 
 * The refresh time determinate numbers of bus clocks inserted between REF command
 * and the next possible ACTV command and auto refresh frequency.
 *
 * @param base Register base address for SDRAM.
 * @param refreshTime The number of bus clocks inserted between a REF command and the next ACTV command.
 *                    See to "sdram_refresh_time_t"
 * @param busClock The bus clock.
 * @param rowRefresh The refresh time of each row in SDRAM. The unit of the rowRefresh is nanosecond.
 *        For example the SDRAM with the 4096 rows/64 ms has the rowRefresh 15625.        
 */
void SDRAM_HAL_SetAutoRefresh(SDRAM_Type *base, sdram_refresh_time_t refreshTime,
                           uint32_t busClock, uint32_t rowRefresh);

/*!
 * @brief Enables/disables the refresh.
 *
 * @param base Register base address for SDRAM.
 * @param whichBlock The block which is selected.
 * @param enable Enables or disables.
 */
void SDRAM_HAL_SetRefreshCmd(SDRAM_Type * base, sdram_block_selection_t whichBlock, bool enable);

/*!
 * @brief Sets the base address mask.
 *
 * @param base Register base address for SDRAM.
 * @param whichBlock The block which is selected.
 * @param mask The mask of the address. With the "base address" determine the determines 
 *  the address range in which the associated DRAM block is located.
 */
static inline void SDRAM_HAL_SetAddressMask(SDRAM_Type * base, sdram_block_selection_t whichBlock,
                uint32_t mask)
{
    SDRAM_BWR_CM_BAM(base, whichBlock, (mask & SDRAM_CM_BAM_MASK) >> SDRAM_CM_BAM_SHIFT);
}

/*!
 * @brief Sends the command to SDRAM.
 *
 * @param base Register base address for SDRAM.
 * @param command The command send to SDRAM. See to "sdram_command_t"
 */
void SDRAM_HAL_SendCommand(SDRAM_Type *base, sdram_block_selection_t whichBlock, sdram_command_t command);

/*!
 * @brief Gets the command execute status.
 *
 * @param base Register base address for SDRAM.
 * @param command The command send to SDRAM. See to "sdram_command_t"
 * @return the execute status of command
 *              - true, the command is finished.
 *              - false, the command is on-going.
 */
bool SDRAM_HAL_IsCommandFinished(SDRAM_Type *base, sdram_block_selection_t whichBlock, sdram_command_t command);

/*!
 * @brief Enables/disables the write protection.
 *
 * @param base Register base address for SDRAM.
 * @param whichBlock The block which is selected.
 * @param enable Enables or disables.
 */
void SDRAM_HAL_SetWriteProtectCmd(SDRAM_Type * base, sdram_block_selection_t whichBlock, bool enable);

/*!
 * @brief Enables/disables the operation valid.
 *
 * @param base Register base address for SDRAM.
 * @param whichBlock The block which is selected.
 * @param enable Enables or disables. 
 */
void SDRAM_HAL_SetOperateValidCmd(SDRAM_Type * base, sdram_block_selection_t whichBlock, bool enable);


#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif /* __FSL_SDRAMC_HAL_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

