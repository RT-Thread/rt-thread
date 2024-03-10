/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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
#ifndef _FSL_EMC_H_
#define _FSL_EMC_H_

#include "fsl_common.h"

/*!
 * @addtogroup emc
 * @{
 */


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief EMC driver version 2.0.0. */
#define FSL_EMC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*! @brief Define the chip numbers for dynamic and static memory devices. */
#define EMC_STATIC_MEMDEV_NUM        (4U)
#define EMC_DYNAMIC_MEMDEV_NUM       (4U)
#define EMC_ADDRMAP_SHIFT        EMC_DYNAMIC_DYNAMICCONFIG_AM0_SHIFT
#define EMC_ADDRMAP_MASK         (EMC_DYNAMIC_DYNAMICCONFIG_AM0_MASK |EMC_DYNAMIC_DYNAMICCONFIG_AM1_MASK)
#define EMC_ADDRMAP(x)    (((uint32_t)(((uint32_t)(x)) << EMC_ADDRMAP_SHIFT)) & EMC_ADDRMAP_MASK)     
#define EMC_HZ_ONEMHZ   (1000000U)
#define EMC_MILLISECS_ONESEC   (1000U)
#define EMC_SDRAM_MODE_CL_SHIFT   (4U)
#define EMC_SDRAM_MODE_CL_MASK   (0x70U)

/*!
 * @brief Define EMC memory width for static memory device.
 */
typedef enum _emc_static_memwidth
{
    kEMC_8BitWidth = 0x0U, /*!< 8 bit memory width. */
    kEMC_16BitWidth,       /*!< 16 bit memory width. */
    kEMC_32BitWidth        /*!< 32 bit memory width. */
} emc_static_memwidth_t;

/*!
 * @brief Define EMC static configuration.
 */
typedef enum _emc_static_special_config
{ 
    kEMC_AsynchronosPageEnable = 0x0008U,/*!< Enable the asynchronous page mode. page length four. */
    kEMC_ActiveHighChipSelect = 0x0040U, /*!< Chip select active high. */
    kEMC_ByteLaneStateAllLow = 0x0080U,  /*!< Reads/writes the respective valuie bits in BLS3:0 are low. */
    kEMC_ExtWaitEnable = 0x0100U,        /*!< Extended wait enable. */
    kEMC_BufferEnable = 0x80000U         /*!< Buffer enable. */
} emc_static_special_config_t;

/*! @brief EMC dynamic memory device. */
typedef enum _emc_dynamic_device
{
    kEMC_Sdram = 0x0U,   /*!< Dynamic memory device: SDRAM. */
    kEMC_Lpsdram,        /*!< Dynamic memory device: Low-power SDRAM. */
} emc_dynamic_device_t;

/*! @brief EMC dynamic read strategy. */
typedef enum _emc_dynamic_read
{
    kEMC_NoDelay = 0x0U,        /*!< No delay. */ 
    kEMC_Cmddelay,              /*!< Command delayed strategy, using EMCCLKDELAY. */
    kEMC_CmdDelayPulseOneclk,   /*!< Command delayed strategy pluse one clock cycle using EMCCLKDELAY. */
    kEMC_CmddelayPulsetwoclk,   /*!< Command delayed strategy pulse two clock cycle using EMCCLKDELAY. */
} emc_dynamic_read_t;

/*! @brief EMC endian mode. */
typedef enum _emc_endian_mode
{
    kEMC_LittleEndian = 0x0U, /*!< Little endian mode. */
    kEMC_BigEndian,           /*!< Big endian mode. */
} emc_endian_mode_t;

/*! @brief EMC Feedback clock input source select. */
typedef enum _emc_fbclk_src
{
    kEMC_IntloopbackEmcclk = 0U, /*!< Use the internal loop back from EMC_CLK output. */
    kEMC_EMCFbclkInput    /*!< Use the external EMC_FBCLK input. */
} emc_fbclk_src_t;

/*! @brief EMC dynamic timing/delay configure structure. */
typedef struct _emc_dynamic_timing_config
{
    emc_dynamic_read_t readConfig;   /* Dynamic read strategy. */
    uint32_t refreshPeriod_Nanosec;  /*!< The refresh period in unit of nanosecond. */
    uint32_t tRp_Ns;      /*!< Precharge command period in unit of nanosecond. */
    uint32_t tRas_Ns;     /*!< Active to precharge command period in unit of nanosecond. */
    uint32_t tSrex_Ns;    /*!< Self-refresh exit time in unit of nanosecond. */
    uint32_t tApr_Ns;     /*!< Last data out to active command time in unit of nanosecond. */
    uint32_t tDal_Ns;     /*!< Data-in to active command in unit of nanosecond. */
    uint32_t tWr_Ns;      /*!< Write recovery time in unit of nanosecond. */
    uint32_t tRc_Ns;      /*!< Active to active command period in unit of nanosecond. */       
    uint32_t tRfc_Ns;     /*!< Auto-refresh period and auto-refresh to active command period in unit of nanosecond. */
    uint32_t tXsr_Ns;     /*!< Exit self-refresh to active command time in unit of nanosecond. */
    uint32_t tRrd_Ns;     /*!< Active bank A to active bank B latency in unit of nanosecond. */
    uint8_t tMrd_Nclk;     /*!< Load mode register to active command time in unit of EMCCLK cycles.*/
} emc_dynamic_timing_config_t;

/*!
 * @brief EMC dynamic memory controller independent chip configuration structure.
 * Please take refer to the address mapping table in the RM in EMC chapter when you 
 * set the "devAddrMap". Choose the right Bit 14 Bit12 ~ Bit 7 group in the table
 * according to the bus width/banks/row/colum length for you device.
 * Set devAddrMap with the value make up with the seven bits (bit14 bit12 ~ bit 7) 
 * and inset the bit 13 with 0.
 * for example, if the bit 14 and bit12 ~ bit7 is 1000001 is choosen according to the
 * 32bit high-performance bus width with 2 banks, 11 row lwngth, 8 column length. 
 * Set devAddrMap with 0x81.
 */
typedef struct _emc_dynamic_chip_config
{
    uint8_t chipIndex;    /*!< Chip Index, range from 0 ~ EMC_DYNAMIC_MEMDEV_NUM - 1. */
    emc_dynamic_device_t dynamicDevice; /*!< All chips shall use the same device setting. mixed use are not supported. */
    uint8_t rAS_Nclk;    /*!< Active to read/write delay tRCD. */
    uint16_t sdramModeReg;   /*!< Sdram mode register setting. */
    uint16_t sdramExtModeReg; /*!< Used for low-power sdram device. The extended mode register. */
    uint8_t devAddrMap;  /*!< dynamic device address mapping, choose the address mapping for your specific device. */
} emc_dynamic_chip_config_t;

/*!
 * @brief EMC static memory controller independent chip configuration structure.
 */
typedef struct _emc_static_chip_config
{
    uint8_t chipIndex;
    emc_static_memwidth_t memWidth; /*!< Memory width. */
    uint32_t specailConfig;     /*!< Static configuration,a logical OR of "emc_static_special_config_t". */
    uint32_t tWaitWriteEn_Ns;/*!< The delay form chip select to write enable in unit of nanosecond. */
    uint32_t tWaitOutEn_Ns;  /*!< The delay from chip selcet to output enable in unit of nanosecond. */
    uint32_t tWaitReadNoPage_Ns;/*!< In No-page mode, the delay from chip select to read access in unit of nanosecond. */
    uint32_t tWaitReadPage_Ns;  /*!< In page mode, the read after the first read wait states in unit of nanosecond. */ 
    uint32_t tWaitWrite_Ns;     /*!< The delay from chip select to write access in unit of nanosecond. */
    uint32_t tWaitTurn_Ns;      /*!< The Bus turn-around time in unit of nanosecond. */
} emc_static_chip_config_t;

/*!
 * @brief EMC module basic configuration structure.
 *
 * Defines the static memory controller configure structure and 
 * uses the EMC_Init() function to make necessary initializations.
 *
 */
typedef struct _emc_basic_config
{
    emc_endian_mode_t endian;   /*!< Endian mode . */
    emc_fbclk_src_t fbClkSrc;    /*!< The feedback clock source. */
    uint8_t emcClkDiv; /*!< EMC_CLK = AHB_CLK / (emc_clkDiv + 1). */
} emc_basic_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name EMC Initialize and de-initialize opeartion
 * @{
 */
/*!
 * @brief Initializes the basic for EMC.
 * This function ungates the EMC clock, initializes the emc system configure
 * and enable the EMC module. This function must be called in the first step to initialize
 * the external memory.
 *
 * @param base EMC peripheral base address.
 * @param config The EMC basic configuration.
 */
void EMC_Init(EMC_Type *base, emc_basic_config_t *config);

/*!
 * @brief Initializes the dynamic memory controller.
 * This function initializes the dynamic memory controller in external memory controller.
 * This function must be called after EMC_Init and before accessing the external dynamic memory.
 *
 * @param base EMC peripheral base address.
 * @param timing The timing and latency for dynamica memory controller setting. It shall
 *        be used for all dynamica memory chips, threfore the worst timing value for all
 *        used chips must be given.
 * @param configure The EMC dynamic memory controller chip independent configuration pointer.
 *       This configuration pointer is actually pointer to a configration array. the array number
 *       depends on the "totalChips".
 * @param totalChips The total dynamic memory chip numbers been used or the length of the 
 *        "emc_dynamic_chip_config_t" type memory.
 */
void EMC_DynamicMemInit(EMC_Type *base, emc_dynamic_timing_config_t *timing, 
        emc_dynamic_chip_config_t *config, uint32_t totalChips);

/*!
 * @brief Initializes the static memory controller.
 * This function initializes the static memory controller in external memory controller.
 * This function must be called after EMC_Init and before accessing the external static memory.
 *
 * @param base EMC peripheral base address.
 * @param extWait_Ns The extended wait timeout or the read/write transfer time.
 *        This is common for all static memory chips and set with NULL if not required.
 * @param configure The EMC static memory controller chip independent configuration pointer.
 *       This configuration pointer is actually pointer to a configration array. the array number
 *       depends on the "totalChips".
 * @param totalChips The total static memory chip numbers been used or the length of the 
 *        "emc_static_chip_config_t" type memory.
 */
void EMC_StaticMemInit(EMC_Type *base, uint32_t *extWait_Ns, emc_static_chip_config_t *config, uint32_t totalChips);

/*!
 * @brief Deinitializes the EMC module and gates the clock.
 * This function gates the EMC controller clock. As a result, the EMC
 * module doesn't work after calling this function.
 *
 * @param base EMC peripheral base address.
 */
void EMC_Deinit(EMC_Type *base);

/* @} */

/*!
 * @name EMC Basic Operation
 * @{
 */

/*!
 * @brief Enables/disables the EMC module.
 *
 * @param base EMC peripheral base address.
 * @param enable True enable EMC module, false disable.
 */
static inline void EMC_Enable(EMC_Type *base, bool enable)
{
    if (enable)
    {
        base->CONTROL |= EMC_CONTROL_E_MASK;
    }
    else
    {
        base->CONTROL &= ~EMC_CONTROL_E_MASK;
    }
}

/*!
 * @brief Enables/disables the EMC Dynaimc memory controller.
 *
 * @param base EMC peripheral base address.
 * @param enable True enable EMC dynamic memory controller, false disable.
 */
static inline void EMC_EnableDynamicMemControl(EMC_Type *base, bool enable)
{
    if (enable)
    {
        base->DYNAMICCONTROL |= (EMC_DYNAMICCONTROL_CE_MASK | EMC_DYNAMICCONTROL_CS_MASK);
    }
    else
    {
        base->DYNAMICCONTROL &= ~(EMC_DYNAMICCONTROL_CE_MASK | EMC_DYNAMICCONTROL_CS_MASK);
    }
}

/*!
 * @brief Enables/disables the EMC address mirror.
 * Enable the address mirror the EMC_CS1is mirrored to both EMC_CS0
 * and EMC_DYCS0 memory areas. Disable the address mirror enables
 * EMC_cS0 and EMC_DYCS0 memory to be accessed.
 *
 * @param base EMC peripheral base address.
 * @param enable True enable the address mirror, false disable the address mirror.
 */
static inline void EMC_MirrorChipAddr(EMC_Type *base, bool enable)
{
    if (enable) 
    {
        base->CONTROL |= EMC_CONTROL_M_MASK;
    }
    else 
    {
        base->CONTROL &= ~EMC_CONTROL_M_MASK;
    }
}

/*!
 * @brief Enter the self-refresh mode for dynamic memory controller.
 * This function provided self-refresh mode enter or exit for application. 
 *
 * @param base EMC peripheral base address.
 * @param enable   True enter the self-refresh mode, false to exit self-refresh
 *                 and enter the normal mode.
 */
static inline void EMC_EnterSelfRefreshCommand(EMC_Type *base, bool enable)
{
    if (enable)
    {
        base->DYNAMICCONTROL |= EMC_DYNAMICCONTROL_SR_MASK;
    }
    else
    {
        base->DYNAMICCONTROL &= ~EMC_DYNAMICCONTROL_SR_MASK;
    }
}

/*!
 * @brief Get the operating mode of the EMC.
 * This function can be used to get the operating mode of the EMC. 
 *
 * @param base EMC peripheral base address.
 * @return The EMC in self-refresh mode if true, else in normal mode.
 */
static inline bool EMC_IsInSelfrefreshMode(EMC_Type *base)
{
    return ((base->STATUS & EMC_STATUS_SA_MASK) ? true : false);
}

/*!
 * @brief Enter/exit the low-power mode.
 *
 * @param base EMC peripheral base address.
 * @param enable True Enter the low-power mode, false exit low-power mode
 *        and return to normal mode. 
 */
static inline void EMC_EnterLowPowerMode(EMC_Type *base, bool enable)
{
    if (enable)
    {
        base->CONTROL |= EMC_CONTROL_L_MASK;
    }
    else
    {
        base->CONTROL &= ~ EMC_CONTROL_L_MASK;
    }
}

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_EMC_H_*/
