/*!
    \file    gd32h7xx_exmc.c
    \brief   EXMC driver

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include <stdlib.h>
#include "gd32h7xx_exmc.h"

/* EXMC bank0 register reset value */
#define BANK0_SNCTL_RESET                 ((uint32_t)0x000030DAU)  /* SNCTL register reset value */
#define BANK0_SNTCFG_RESET                ((uint32_t)0x0FFFFFFFU)  /* SNTCFG register reset value */
#define BANK0_SNWTCFG_RESET               ((uint32_t)0x0FFFFFFFU)  /* SNWTCFG register reset value */

/* EXMC bank2 register reset value */
#define BANK2_NCTL_RESET                  ((uint32_t)0x00000008U)  /* NCTL register reset value */
#define BANK2_NINTEN_RESET                ((uint32_t)0x00000042U)  /* NINTEN register reset value */
#define BANK2_NCTCFG_RESET                ((uint32_t)0xFFFFFFFFU)  /* NCTCFG register reset value */
#define BANK2_NATCFG_RESET                ((uint32_t)0xFFFFFFFFU)  /* NATCFG register reset value */

/* EXMC SDRAM device register reset value */
#define SDRAM_DEVICE_SDCTL_RESET          ((uint32_t)0x000002D0U)  /* SDCTL register reset value */
#define SDRAM_DEVICE_SDTCFG_RESET         ((uint32_t)0x0FFFFFFFU)  /* SDTCFG register reset value */
#define SDRAM_DEVICE_SDCMD_RESET          ((uint32_t)0x00000000U)  /* SDCMD register reset value */
#define SDRAM_DEVICE_SDARI_RESET          ((uint32_t)0x00000000U)  /* SDARI register reset value */
#define SDRAM_DEVICE_SDSTAT_RESET         ((uint32_t)0x00000000U)  /* SDSTAT register reset value */
#define SDRAM_DEVICE_SDRSCTL_RESET        ((uint32_t)0x00000000U)  /* SDRSCTL register reset value */

/* EXMC register bit offset */
/* EXMC_SNCTL register bit offset */
#define SNCTL_NRMUX_OFFSET                ((uint32_t)0x00000001U)  /* bit offset of NRMUX */
#define SNCTL_NREN_OFFSET                 ((uint32_t)0x00000006U)  /* bit offset of NREN */
#define SNCTL_SBRSTEN_OFFSET              ((uint32_t)0x00000008U)  /* bit offset of SBRSTEN */
#define SNCTL_WREN_OFFSET                 ((uint32_t)0x0000000CU)  /* bit offset of WREN */
#define SNCTL_NRWTEN_OFFSET               ((uint32_t)0x0000000DU)  /* bit offset of NRWTEN */
#define SNCTL_EXMODEN_OFFSET              ((uint32_t)0x0000000EU)  /* bit offset of EXMODEN */
#define SNCTL_ASYNCWAITEN_OFFSET          ((uint32_t)0x0000000FU)  /* bit offset of ASYNCWAITEN */
#define SNCTL_BKREMAP_OFFSET              ((uint32_t)0x00000018U)  /* bit offset of BKREMAP */

/* EXMC_SNTCFG register bit offset */
#define SNTCFG_AHLD_OFFSET                ((uint32_t)0x00000004U)  /* bit offset of AHLD */
#define SNTCFG_DSET_OFFSET                ((uint32_t)0x00000008U)  /* bit offset of DSET */
#define SNTCFG_BUSLAT_OFFSET              ((uint32_t)0x00000010U)  /* bit offset of BUSLAT */

/* EXMC_NCTL register bit offset */
#define NCTL_NDWTEN_OFFSET                ((uint32_t)0x00000001U)  /* bit offset of NDWTEN */
#define NCTL_ECCEN_OFFSET                 ((uint32_t)0x00000006U)  /* bit offset of ECCEN */

/* EXMC_NCTCFG register bit offset */
#define NCTCFG_COMWAIT_OFFSET             ((uint32_t)0x00000008U)  /* bit offset of COMWAIT */
#define NCTCFG_COMHLD_OFFSET              ((uint32_t)0x00000010U)  /* bit offset of COMHLD */
#define NCTCFG_COMHIZ_OFFSET              ((uint32_t)0x00000018U)  /* bit offset of COMHIZ */

/* EXMC_NATCFG register bit offset */
#define NATCFG_ATTWAIT_OFFSET             ((uint32_t)0x00000008U)  /* bit offset of ATTWAIT */
#define NATCFG_ATTHLD_OFFSET              ((uint32_t)0x00000010U)  /* bit offset of ATTHLD */
#define NATCFG_ATTHIZ_OFFSET              ((uint32_t)0x00000018U)  /* bit offset of ATTHIZ */

/* EXMC_SDCTL register bit offset */
#define SDCTL_WPEN_OFFSET                 ((uint32_t)0x00000009U)  /* bit offset of WPEN */
#define SDCTL_BRSTRD_OFFSET               ((uint32_t)0x0000000CU)  /* bit offset of BRSTRD */

/* EXMC_SDTCFG register bit offset */
#define SDTCFG_XSRD_OFFSET                ((uint32_t)0x00000004U)  /* bit offset of XSRD */
#define SDTCFG_RASD_OFFSET                ((uint32_t)0x00000008U)  /* bit offset of RASD */
#define SDTCFG_ARFD_OFFSET                ((uint32_t)0x0000000CU)  /* bit offset of ARFD */
#define SDTCFG_WRD_OFFSET                 ((uint32_t)0x00000010U)  /* bit offset of WRD */
#define SDTCFG_RPD_OFFSET                 ((uint32_t)0x00000014U)  /* bit offset of RPD */
#define SDTCFG_RCD_OFFSET                 ((uint32_t)0x00000018U)  /* bit offset of RCD */

/* EXMC_SDCMD register bit offset */
#define SDCMD_NARF_OFFSET                 ((uint32_t)0x00000005U)  /* bit offset of NARF */
#define SDCMD_MRC_OFFSET                  ((uint32_t)0x00000009U)  /* bit offset of MRC */

/* EXMC_SDCMD register bit offset */
#define SDARI_ARINTV_OFFSET               ((uint32_t)0x00000001U)  /* bit offset of ARINTV */

/* EXMC_SDRSCTL register bit offset */
#define SDRSCTL_SSCR_OFFSET               ((uint32_t)0x00000001U)  /* bit offset of SSCR */
#define SDRSCTL_SDSC_OFFSET               ((uint32_t)0x00000004U)  /* bit offset of SDSC */

/* EXMC_SDSTAT register bit offset */
#define SDSTAT_STA0_OFFSET                ((uint32_t)0x00000001U)  /* bit offset of STA0 */
#define SDSTAT_STA1_OFFSET                ((uint32_t)0x00000003U)  /* bit offset of STA1 */

/* EXMC_NINTEN register interrupt enable bit and interrupt status bit interval */
#define NINTEN_INTEN_INTS_INTERVAL        ((uint32_t)0x00000003U)  /* bit offset of INTEN_INTS */

/*!
    \brief      deinitialize EXMC NOR/SRAM region
    \param[in]  exmc_norsram_region: select the region of bank0
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK0_NORSRAM_REGIONx(x=0..3): EXMC BANK0 REGIONx
    \param[out] none
    \retval     none
*/
void exmc_norsram_deinit(uint32_t exmc_norsram_region)
{
    /* reset the registers */
    EXMC_SNCTL(exmc_norsram_region) = BANK0_SNCTL_RESET;
    EXMC_SNTCFG(exmc_norsram_region) = BANK0_SNTCFG_RESET;
    EXMC_SNWTCFG(exmc_norsram_region) = BANK0_SNWTCFG_RESET;
}

/*!
    \brief      initialize exmc_norsram_parameter_struct with the default values
    \param[in]  none
    \param[out] exmc_norsram_init_struct: the initialized struct exmc_norsram_parameter_struct pointer
    \retval     none
*/
void exmc_norsram_struct_para_init(exmc_norsram_parameter_struct *exmc_norsram_init_struct)
{
    /* configure control variables with default values */
    exmc_norsram_init_struct->norsram_region = EXMC_BANK0_NORSRAM_REGION0;
    exmc_norsram_init_struct->address_data_mux = ENABLE;
    exmc_norsram_init_struct->memory_type = EXMC_MEMORY_TYPE_SRAM;
    exmc_norsram_init_struct->databus_width = EXMC_NOR_DATABUS_WIDTH_8B;
    exmc_norsram_init_struct->burst_mode = DISABLE;
    exmc_norsram_init_struct->nwait_polarity = EXMC_NWAIT_POLARITY_LOW;
    exmc_norsram_init_struct->nwait_config = EXMC_NWAIT_CONFIG_BEFORE;
    exmc_norsram_init_struct->memory_write = ENABLE;
    exmc_norsram_init_struct->nwait_signal = ENABLE;
    exmc_norsram_init_struct->extended_mode = DISABLE;
    exmc_norsram_init_struct->asyn_wait = DISABLE;
    exmc_norsram_init_struct->cram_page_size = EXMC_CRAM_AUTO_SPLIT;
    exmc_norsram_init_struct->write_mode = EXMC_ASYN_WRITE;

    /* configure read/write timing */
    exmc_norsram_init_struct->read_write_timing = NULL;

    /* configure write timing when extended mode is used */
    exmc_norsram_init_struct->write_timing = NULL;
}

/*!
    \brief      initialize EXMC NOR/SRAM region
    \param[in]  exmc_norsram_init_struct: configure the EXMC NOR/SRAM parameter
                  norsram_region: EXMC_BANK0_NORSRAM_REGIONx, x=0~3
                  write_mode: EXMC_ASYN_WRITE, EXMC_SYN_WRITE
                  extended_mode: ENABLE or DISABLE
                  asyn_wait: ENABLE or DISABLE
                  nwait_signal: ENABLE or DISABLE
                  memory_write: ENABLE or DISABLE
                  nwait_config: EXMC_NWAIT_CONFIG_BEFORE, EXMC_NWAIT_CONFIG_DURING
                  nwait_polarity: EXMC_NWAIT_POLARITY_LOW, EXMC_NWAIT_POLARITY_HIGH
                  burst_mode: ENABLE or DISABLE
                  databus_width: EXMC_NOR_DATABUS_WIDTH_8B, EXMC_NOR_DATABUS_WIDTH_16B
                  memory_type: EXMC_MEMORY_TYPE_SRAM, EXMC_MEMORY_TYPE_PSRAM, EXMC_MEMORY_TYPE_NOR
                  address_data_mux: ENABLE or DISABLE
                  cram_page_size: EXMC_CRAM_AUTO_SPLIT, EXMC_CRAM_PAGE_SIZE_128_BYTES, EXMC_CRAM_PAGE_SIZE_256_BYTES,
                    EXMC_CRAM_PAGE_SIZE_512_BYTES, EXMC_CRAM_PAGE_SIZE_1024_BYTES
                  read_write_timing: struct exmc_norsram_timing_parameter_struct set the time
                    asyn_access_mode: EXMC_ACCESS_MODE_A, EXMC_ACCESS_MODE_B, EXMC_ACCESS_MODE_C, EXMC_ACCESS_MODE_D
                    syn_data_latency: EXMC_DATALAT_x_CLK, x=2~17
                    syn_clk_division: EXMC_SYN_CLOCK_RATIO_x_CLK, x=2~16
                    bus_latency: 0x0U~0xFU
                    asyn_data_setuptime: 1~255
                    asyn_address_holdtime: 1~15
                    asyn_address_setuptime: 0~15
                  write_timing: struct exmc_norsram_timing_parameter_struct set the time
                    asyn_access_mode: EXMC_ACCESS_MODE_A, EXMC_ACCESS_MODE_B, EXMC_ACCESS_MODE_C, EXMC_ACCESS_MODE_D
                    syn_data_latency: EXMC_DATALAT_x_CLK, x=2~17
                    syn_clk_division: EXMC_SYN_CLOCK_RATIO_x_CLK, x=2~16
                    bus_latency: 0~15
                    asyn_data_setuptime: 1~255
                    asyn_address_holdtime: 1~15
                    asyn_address_setuptime: 0~15
    \param[out] none
    \retval     none
*/
void exmc_norsram_init(exmc_norsram_parameter_struct *exmc_norsram_init_struct)
{
    uint32_t snctl = 0x00000000U, sntcfg = 0x00000000U, snwtcfg = 0x00000000U;

    /* get value of register EXMC_SNCTL */
    snctl = EXMC_SNCTL(exmc_norsram_init_struct->norsram_region);

    /* clear control bits */
    snctl &= (uint32_t)(~(EXMC_SNCTL_NREN | EXMC_SNCTL_NRTP | EXMC_SNCTL_NRW | EXMC_SNCTL_SBRSTEN |
                          EXMC_SNCTL_NRWTPOL | EXMC_SNCTL_NRWTCFG | EXMC_SNCTL_WEN |
                          EXMC_SNCTL_NRWTEN | EXMC_SNCTL_EXMODEN | EXMC_SNCTL_ASYNCWTEN | EXMC_SNCTL_SYNCWR |
                          EXMC_SNCTL_NRMUX | EXMC_SNCTL_BKREMAP | EXMC_SNCTL_CCK | EXMC_SNCTL_CPS));

    /* configure control bits */
    snctl |= (uint32_t)((exmc_norsram_init_struct->address_data_mux << SNCTL_NRMUX_OFFSET) |
                        exmc_norsram_init_struct->memory_type |
                        exmc_norsram_init_struct->databus_width |
                        (exmc_norsram_init_struct->burst_mode << SNCTL_SBRSTEN_OFFSET) |
                        exmc_norsram_init_struct->nwait_polarity |
                        exmc_norsram_init_struct->nwait_config |
                        (exmc_norsram_init_struct->memory_write << SNCTL_WREN_OFFSET) |
                        (exmc_norsram_init_struct->nwait_signal << SNCTL_NRWTEN_OFFSET) |
                        (exmc_norsram_init_struct->extended_mode << SNCTL_EXMODEN_OFFSET) |
                        (exmc_norsram_init_struct->asyn_wait << SNCTL_ASYNCWAITEN_OFFSET) |
                        exmc_norsram_init_struct->write_mode |
                        exmc_norsram_init_struct->cram_page_size);

    /* nor flash access enable */
    if(EXMC_MEMORY_TYPE_NOR == exmc_norsram_init_struct->memory_type)
    {
        snctl |= (uint32_t)EXMC_SNCTL_NREN;
    }

    /* configure timing */
    sntcfg = (uint32_t)(exmc_norsram_init_struct->read_write_timing->asyn_address_setuptime |
                        (exmc_norsram_init_struct->read_write_timing->asyn_address_holdtime << SNTCFG_AHLD_OFFSET) |
                        (exmc_norsram_init_struct->read_write_timing->asyn_data_setuptime << SNTCFG_DSET_OFFSET) |
                        (exmc_norsram_init_struct->read_write_timing->bus_latency << SNTCFG_BUSLAT_OFFSET) |
                        exmc_norsram_init_struct->read_write_timing->syn_clk_division |
                        exmc_norsram_init_struct->read_write_timing->syn_data_latency |
                        exmc_norsram_init_struct->read_write_timing->asyn_access_mode);

    if(ENABLE == exmc_norsram_init_struct->extended_mode)
    {
        /* for extended mode, configure write timing */
        snwtcfg = (uint32_t)(exmc_norsram_init_struct->write_timing->asyn_address_setuptime |
                             (exmc_norsram_init_struct->write_timing->asyn_address_holdtime << SNTCFG_AHLD_OFFSET) |
                             (exmc_norsram_init_struct->write_timing->asyn_data_setuptime << SNTCFG_DSET_OFFSET) |
                             (exmc_norsram_init_struct->write_timing->bus_latency << SNTCFG_BUSLAT_OFFSET) |
                             exmc_norsram_init_struct->write_timing->asyn_access_mode);
    } else {
        snwtcfg = BANK0_SNWTCFG_RESET;
    }

    /* configure the registers */
    EXMC_SNCTL(exmc_norsram_init_struct->norsram_region) = snctl;
    EXMC_SNTCFG(exmc_norsram_init_struct->norsram_region) = sntcfg;
    EXMC_SNWTCFG(exmc_norsram_init_struct->norsram_region) = snwtcfg;
}

/*!
    \brief      enable EXMC NOR/PSRAM bank region
    \param[in]  exmc_norsram_region: specify the region of NOR/PSRAM bank
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK0_NORSRAM_REGIONx(x=0..3): EXMC BANK0 REGIONx
    \param[out] none
    \retval     none
*/
void exmc_norsram_enable(uint32_t exmc_norsram_region)
{
    EXMC_SNCTL(exmc_norsram_region) |= (uint32_t)EXMC_SNCTL_NRBKEN;
}

/*!
    \brief      disable EXMC NOR/PSRAM bank region
    \param[in]  exmc_norsram_region: specify the region of NOR/PSRAM Bank
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK0_NORSRAM_REGIONx(x=0..3): EXMC BANK0 REGIONx
    \param[out] none
    \retval     none
*/
void exmc_norsram_disable(uint32_t exmc_norsram_region)
{
    EXMC_SNCTL(exmc_norsram_region) &= ~(uint32_t)EXMC_SNCTL_NRBKEN;
}

/*!
    \brief      deinitialize EXMC NAND bank
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_nand_deinit(void)
{
    /* deinitialize EXMC_BANK2_NAND */
    EXMC_NCTL = BANK2_NCTL_RESET;
    EXMC_NINTEN = BANK2_NINTEN_RESET;
    EXMC_NCTCFG = BANK2_NCTCFG_RESET;
    EXMC_NATCFG = BANK2_NATCFG_RESET;
}

/*!
    \brief      initialize exmc_nand_parameter_struct with the default values
    \param[in]  none
    \param[out] the initialized struct exmc_nand_parameter_struct pointer
    \retval     none
*/
void exmc_nand_struct_para_init(exmc_nand_parameter_struct *exmc_nand_init_struct)
{
    /* configure the structure with default values */
    exmc_nand_init_struct->wait_feature = DISABLE;
    exmc_nand_init_struct->databus_width = EXMC_NAND_DATABUS_WIDTH_8B;
    exmc_nand_init_struct->ecc_logic = DISABLE;
    exmc_nand_init_struct->ecc_size = EXMC_ECC_SIZE_256BYTES;
    exmc_nand_init_struct->ctr_latency = 0x00U;
    exmc_nand_init_struct->atr_latency = 0x00U;
    exmc_nand_init_struct->common_space_timing = NULL;
    exmc_nand_init_struct->attribute_space_timing = NULL;
}

/*!
    \brief      initialize EXMC NAND bank
    \param[in]  exmc_nand_init_struct: configure the EXMC NAND parameter
                  ecc_size: EXMC_ECC_SIZE_xBYTES,x=256,512,1024,2048,4096
                  atr_latency: EXMC_ALE_RE_DELAY_x_CK_EXMC,x=1~16
                  ctr_latency: EXMC_CLE_RE_DELAY_x_CK_EXMC,x=1~16
                  ecc_logic: ENABLE or DISABLE
                  databus_width: EXMC_NAND_DATABUS_WIDTH_8B,EXMC_NAND_DATABUS_WIDTH_16B
                  wait_function: ENABLE or DISABLE
                  common_space_timing: struct exmc_nand_timing_parameter_struct set the time
                    databus_hiztime: 1~255
                    holdtime: 1~254
                    waittime: 2~255
                    setuptime: 1~255
                  attribute_space_timing: struct exmc_nand_timing_parameter_struct set the time
                    databus_hiztime: 0~254
                    holdtime: 1~254
                    waittime: 2~255
                    setuptime: 1~255
    \param[out] none
    \retval     none
*/
void exmc_nand_init(exmc_nand_parameter_struct *exmc_nand_init_struct)
{
    uint32_t nctl = 0x00000000U, nctcfg = 0x00000000U, natcfg = 0x00000000U;

    /* configure nctl for EXMC_NCTL */
    nctl = (uint32_t)((exmc_nand_init_struct->wait_feature << NCTL_NDWTEN_OFFSET) |
                      exmc_nand_init_struct->databus_width |
                      (exmc_nand_init_struct->ecc_logic << NCTL_ECCEN_OFFSET) |
                      exmc_nand_init_struct->ecc_size |
                      exmc_nand_init_struct->ctr_latency |
                      exmc_nand_init_struct->atr_latency);

    /* configure nctcfg for EXMC_NCTCFG */
    nctcfg = (uint32_t)(((exmc_nand_init_struct->common_space_timing->setuptime - 1U) & EXMC_NCTCFG_COMSET) |
                        (((exmc_nand_init_struct->common_space_timing->waittime - 1U) << NCTCFG_COMWAIT_OFFSET) & EXMC_NCTCFG_COMWAIT) |
                        ((exmc_nand_init_struct->common_space_timing->holdtime << NCTCFG_COMHLD_OFFSET) & EXMC_NCTCFG_COMHLD) |
                        (((exmc_nand_init_struct->common_space_timing->databus_hiztime - 1U) << NCTCFG_COMHIZ_OFFSET) & EXMC_NCTCFG_COMHIZ));

    /* configure natcfg for EXMC_NATCFG */
    natcfg = (uint32_t)(((exmc_nand_init_struct->attribute_space_timing->setuptime - 1U) & EXMC_NATCFG_ATTSET) |
                        (((exmc_nand_init_struct->attribute_space_timing->waittime - 1U) << NATCFG_ATTWAIT_OFFSET) & EXMC_NATCFG_ATTWAIT) |
                        ((exmc_nand_init_struct->attribute_space_timing->holdtime << NATCFG_ATTHLD_OFFSET) & EXMC_NATCFG_ATTHLD) |
                        ((exmc_nand_init_struct->attribute_space_timing->databus_hiztime << NATCFG_ATTHIZ_OFFSET) & EXMC_NATCFG_ATTHIZ));

    /* initialize EXMC_BANK2_NAND */
    EXMC_NCTL = nctl;
    EXMC_NCTCFG = nctcfg;
    EXMC_NATCFG = natcfg;
}

/*!
    \brief      enable NAND bank
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_nand_enable(void)
{
    EXMC_NCTL |= EXMC_NCTL_NDBKEN;
}

/*!
    \brief      disable NAND bank
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_nand_disable(void)
{
    EXMC_NCTL &= ~EXMC_NCTL_NDBKEN;
}

/*!
    \brief      deinitialize EXMC SDRAM device
   \param[in]   exmc_sdram_device: select the SRAM device
                only one parameter can be selected which is shown as below:
      \arg        EXMC_SDRAM_DEVICEx(x=0, 1)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_sdram_deinit(uint32_t exmc_sdram_device)
{
    /* reset SDRAM registers */
    EXMC_SDCTL(exmc_sdram_device) = SDRAM_DEVICE_SDCTL_RESET;
    EXMC_SDTCFG(exmc_sdram_device) = SDRAM_DEVICE_SDTCFG_RESET;
    EXMC_SDCMD = SDRAM_DEVICE_SDCMD_RESET;
    EXMC_SDARI = SDRAM_DEVICE_SDARI_RESET;
    EXMC_SDRSCTL = SDRAM_DEVICE_SDRSCTL_RESET;
}

/*!
    \brief      initialize exmc_sdram_parameter_struct with the default values
    \param[in]  none
    \param[out] the initialized struct exmc_parameter_struct pointer
    \retval     none
*/
void exmc_sdram_struct_para_init(exmc_sdram_parameter_struct *exmc_sdram_init_struct)
{
    /* configure the structure with default values */
    exmc_sdram_init_struct->sdram_device = EXMC_SDRAM_DEVICE0;
    exmc_sdram_init_struct->column_address_width = EXMC_SDRAM_COW_ADDRESS_8;
    exmc_sdram_init_struct->row_address_width = EXMC_SDRAM_ROW_ADDRESS_11;
    exmc_sdram_init_struct->data_width = EXMC_SDRAM_DATABUS_WIDTH_16B;
    exmc_sdram_init_struct->internal_bank_number = EXMC_SDRAM_4_INTER_BANK;
    exmc_sdram_init_struct->cas_latency = EXMC_CAS_LATENCY_1_SDCLK;
    exmc_sdram_init_struct->write_protection = ENABLE;
    exmc_sdram_init_struct->sdclock_config = EXMC_SDCLK_DISABLE;
    exmc_sdram_init_struct->burst_read_switch = DISABLE;
    exmc_sdram_init_struct->pipeline_read_delay = EXMC_PIPELINE_DELAY_0_CK_EXMC;

    exmc_sdram_init_struct->timing = NULL;
}

/*!
    \brief      initialize EXMC SDRAM device
    \param[in]  exmc_sdram_init_struct: configure the EXMC SDRAM parameter
                  sdram_device: EXMC_SDRAM_DEVICE0,EXMC_SDRAM_DEVICE1
                  pipeline_read_delay: EXMC_PIPELINE_DELAY_x_CK_EXMC,x=0~2
                  burst_read_switch: ENABLE or DISABLE
                  sdclock_config: EXMC_SDCLK_DISABLE,EXMC_SDCLK_PERIODS_2_CK_EXMC,EXMC_SDCLK_PERIODS_3_CK_EXMC,EXMC_SDCLK_PERIODS_4_CK_EXMC,EXMC_SDCLK_PERIODS_5_CK_EXMC
                  write_protection: ENABLE or DISABLE
                  cas_latency: EXMC_CAS_LATENCY_x_SDCLK,x=1~3
                  internal_bank_number: EXMC_SDRAM_2_INTER_BANK,EXMC_SDRAM_4_INTER_BANK
                  data_width: EXMC_SDRAM_DATABUS_WIDTH_8B,EXMC_SDRAM_DATABUS_WIDTH_16B,EXMC_SDRAM_DATABUS_WIDTH_32B
                  row_address_width: EXMC_SDRAM_ROW_ADDRESS_x,x=11~13
                  column_address_width: EXMC_SDRAM_COW_ADDRESS_x,x=8~11
                  timing: exmc_sdram_timing_parameter_struct set the time
                    row_to_column_delay: 1~16
                    row_precharge_delay: 1~16
                    write_recovery_delay: 1~16
                    auto_refresh_delay: 1~16
                    row_address_select_delay: 1~16
                    exit_selfrefresh_delay: 1~16
                    load_mode_register_delay: 1~16
    \param[out] none
    \retval     none
*/
void exmc_sdram_init(exmc_sdram_parameter_struct *exmc_sdram_init_struct)
{
    uint32_t sdctl0, sdctl1, sdtcfg0, sdtcfg1;

    /* configure EXMC_SDCTL0 or EXMC_SDCTL1 */
    if(EXMC_SDRAM_DEVICE0 == exmc_sdram_init_struct->sdram_device)
    {
        /* configure EXMC_SDCTL0 */
        EXMC_SDCTL(EXMC_SDRAM_DEVICE0)  = (uint32_t)(exmc_sdram_init_struct->column_address_width |
                                          exmc_sdram_init_struct->row_address_width |
                                          exmc_sdram_init_struct->data_width |
                                          exmc_sdram_init_struct->internal_bank_number |
                                          exmc_sdram_init_struct->cas_latency |
                                          (exmc_sdram_init_struct->write_protection << SDCTL_WPEN_OFFSET) |
                                          exmc_sdram_init_struct->sdclock_config |
                                          (exmc_sdram_init_struct->burst_read_switch << SDCTL_BRSTRD_OFFSET) |
                                          exmc_sdram_init_struct->pipeline_read_delay);

        /* configure EXMC_SDTCFG0 */
        EXMC_SDTCFG(EXMC_SDRAM_DEVICE0) = (uint32_t)((exmc_sdram_init_struct->timing->load_mode_register_delay) - 1U) |
                                          (((exmc_sdram_init_struct->timing->exit_selfrefresh_delay) - 1U) << SDTCFG_XSRD_OFFSET) |
                                          (((exmc_sdram_init_struct->timing->row_address_select_delay) - 1U) << SDTCFG_RASD_OFFSET) |
                                          (((exmc_sdram_init_struct->timing->auto_refresh_delay) - 1U) << SDTCFG_ARFD_OFFSET) |
                                          (((exmc_sdram_init_struct->timing->write_recovery_delay) - 1U) << SDTCFG_WRD_OFFSET) |
                                          (((exmc_sdram_init_struct->timing->row_precharge_delay) - 1U) << SDTCFG_RPD_OFFSET) |
                                          (((exmc_sdram_init_struct->timing->row_to_column_delay) - 1U) << SDTCFG_RCD_OFFSET);
    } else {
        /* configure EXMC_SDCTL0 and EXMC_SDCTL1 */
        /* some bits in the EXMC_SDCTL1 register are reserved */
        sdctl0 = EXMC_SDCTL(EXMC_SDRAM_DEVICE0) & (~(EXMC_SDCTL_PIPED | EXMC_SDCTL_BRSTRD | EXMC_SDCTL_SDCLK | EXMC_SDCTL_SDCLK_2));

        sdctl0 |= (uint32_t)(exmc_sdram_init_struct->sdclock_config |
                             (exmc_sdram_init_struct->burst_read_switch << SDCTL_BRSTRD_OFFSET) |
                             exmc_sdram_init_struct->pipeline_read_delay);

        sdctl1 = (uint32_t)(exmc_sdram_init_struct->column_address_width |
                            exmc_sdram_init_struct->row_address_width |
                            exmc_sdram_init_struct->data_width |
                            exmc_sdram_init_struct->internal_bank_number |
                            exmc_sdram_init_struct->cas_latency |
                            (exmc_sdram_init_struct->write_protection << SDCTL_WPEN_OFFSET));

        EXMC_SDCTL(EXMC_SDRAM_DEVICE0) = sdctl0;
        EXMC_SDCTL(EXMC_SDRAM_DEVICE1) = sdctl1;

        /* configure EXMC_SDTCFG0 and EXMC_SDTCFG1 */
        /* some bits in the EXMC_SDTCFG1 register are reserved */
        sdtcfg0 = EXMC_SDTCFG(EXMC_SDRAM_DEVICE0) & (~(EXMC_SDTCFG_RPD | EXMC_SDTCFG_WRD | EXMC_SDTCFG_ARFD));

        sdtcfg0 |= (uint32_t)((((exmc_sdram_init_struct->timing->auto_refresh_delay) - 1U) << SDTCFG_ARFD_OFFSET) |
                              (((exmc_sdram_init_struct->timing->row_precharge_delay) - 1U) << SDTCFG_RPD_OFFSET) |
                              (((exmc_sdram_init_struct->timing->write_recovery_delay) - 1U) << SDTCFG_WRD_OFFSET));

        sdtcfg1 = (uint32_t)(((exmc_sdram_init_struct->timing->load_mode_register_delay) - 1U) |
                             (((exmc_sdram_init_struct->timing->exit_selfrefresh_delay) - 1U) << SDTCFG_XSRD_OFFSET) |
                             (((exmc_sdram_init_struct->timing->row_address_select_delay) - 1U) << SDTCFG_RASD_OFFSET) |
                             (((exmc_sdram_init_struct->timing->row_to_column_delay) - 1U) << SDTCFG_RCD_OFFSET));

        EXMC_SDTCFG(EXMC_SDRAM_DEVICE0) = sdtcfg0;
        EXMC_SDTCFG(EXMC_SDRAM_DEVICE1) = sdtcfg1;
    }
}

/*!
    \brief      configure NOR/PSRAM and SDRAM remap
    \param[in]  bank_remap: NOR/PSRAM and SDRAM map address
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK_REMAP_DEFAULT: default mapping
      \arg        EXMC_BANK_NORPSRAM_SDRAM_SWAP: NOR/PSRAM bank and SDRAM device 0 swapped
    \param[out] none
    \retval     none
*/
void exmc_norsram_sdram_remap_config(uint32_t bank_remap)
{
    /* reset BKREMAP bits */
    EXMC_SNCTL(EXMC_BANK0_NORSRAM_REGION0) &= (uint32_t)(~EXMC_SNCTL_BKREMAP);

    EXMC_SNCTL(EXMC_BANK0_NORSRAM_REGION0) |= bank_remap;
}

/*!
    \brief      get NOR/PSRAM and SDRAM remap configuration
    \param[in]  none
    \param[out] none
    \retval     bank remap value
      \arg        EXMC_BANK_REMAP_DEFAULT: default mapping
      \arg        EXMC_BANK_NORPSRAM_SDRAM_SWAP: NOR/PSRAM bank and SDRAM device 0 swapped
*/
uint32_t exmc_norsram_sdram_remap_get(void)
{
    uint32_t bank_remap;

    bank_remap = EXMC_SNCTL(EXMC_BANK0_NORSRAM_REGION0) & EXMC_SNCTL_BKREMAP;

    return bank_remap;
}

/*!
    \brief      configure consecutive clock mode (consecutive clock is only supported in EXMC BANK0 REGION0)
    \param[in]  clock_mode: specify when the clock is generated
                only one parameter can be selected which is shown as below:
      \arg        EXMC_CLOCK_SYN_MODE: the clock is generated only during synchronous access
      \arg        EXMC_CLOCK_UNCONDITIONALLY: the clock is generated unconditionally
    \param[out] none
    \retval     none
*/
void exmc_norsram_consecutive_clock_config(uint32_t clock_mode)
{
    if(EXMC_CLOCK_UNCONDITIONALLY == clock_mode)
    {
        EXMC_SNCTL(EXMC_BANK0_NORSRAM_REGION0) |= EXMC_CLOCK_UNCONDITIONALLY;
    } else {
        EXMC_SNCTL(EXMC_BANK0_NORSRAM_REGION0) &= ~EXMC_CLOCK_UNCONDITIONALLY;
    }
}

/*!
    \brief      configure CRAM page size
    \param[in]  exmc_norsram_region: select the region of bank0
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK0_NORSRAM_REGIONx(x=0..3)
    \param[in]  page_size: CRAM page size
                only one parameter can be selected which is shown as below:
      \arg        EXMC_CRAM_AUTO_SPLIT: the clock is generated only during synchronous access
      \arg        EXMC_CRAM_PAGE_SIZE_128_BYTES: page size is 128 bytes
      \arg        EXMC_CRAM_PAGE_SIZE_256_BYTES: page size is 256 bytes
      \arg        EXMC_CRAM_PAGE_SIZE_512_BYTES: page size is 512 bytes
      \arg        EXMC_CRAM_PAGE_SIZE_1024_BYTES: page size is 1024 bytes
    \param[out] none
    \retval     none
*/
void exmc_norsram_page_size_config(uint32_t exmc_norsram_region, uint32_t page_size)
{
    /* reset the bits */
    EXMC_SNCTL(exmc_norsram_region) &= ~EXMC_SNCTL_CPS;

    EXMC_SNCTL(exmc_norsram_region) |= page_size;
}

/*!
    \brief      enable or disable the EXMC NAND ECC function
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void exmc_nand_ecc_config(ControlStatus newvalue)
{
    if(ENABLE == newvalue)
    {
        /* enable NAND bank ECC function */
        EXMC_NCTL |= EXMC_NCTL_ECCEN;
    } else {
        /* disable NAND bank ECC function */
        EXMC_NCTL &= ~EXMC_NCTL_ECCEN;
    }
}

/*!
    \brief      get the EXMC ECC value
    \param[in]  none
    \param[out] none
    \retval     the error correction code(ECC) value
*/
uint32_t exmc_ecc_get(void)
{
    return(EXMC_NECC);
}

/*!
    \brief      enable read sample function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_sdram_readsample_enable(void)
{
    EXMC_SDRSCTL |=  EXMC_SDRSCTL_RSEN;
}

/*!
    \brief      disable read sample function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_sdram_readsample_disable(void)
{
    EXMC_SDRSCTL &= (uint32_t)(~EXMC_SDRSCTL_RSEN);
}

/*!
    \brief      configure the delayed sample clock of read data
    \param[in]  delay_cell: SDRAM the delayed sample clock of read data
                only one parameter can be selected which is shown as below:
      \arg        EXMC_SDRAM_x_DELAY_CELL(x=0..15)
    \param[in]  extra_clk: sample cycle of read data
                only one parameter can be selected which is shown as below:
      \arg        EXMC_SDRAM_READSAMPLE_0_EXTRACK: add 0 extra CK_EXMC cycle to the read data sample clock besides the delay chain
      \arg        EXMC_SDRAM_READSAMPLE_1_EXTRACK: add 1 extra CK_EXMC cycle to the read data sample clock besides the delay chain
    \param[out] none
    \retval     none
*/
void exmc_sdram_readsample_config(uint32_t delay_cell, uint32_t extra_clk)
{
    uint32_t sdrsctl = 0U;

    /* reset the bits */
    sdrsctl = EXMC_SDRSCTL & (~(EXMC_SDRSCTL_SDSC | EXMC_SDRSCTL_SSCR));
    /* set the bits */
    sdrsctl |= (uint32_t)(delay_cell | extra_clk);
    EXMC_SDRSCTL = sdrsctl;
}

/*!
    \brief      configure the SDRAM memory command
    \param[in]  exmc_sdram_command_init_struct: initialize EXMC SDRAM command
                  mode_register_content:
                  auto_refresh_number: EXMC_SDRAM_AUTO_REFLESH_x_SDCLK, x=1~15
                  bank_select: EXMC_SDRAM_DEVICE0_SELECT, EXMC_SDRAM_DEVICE1_SELECT, EXMC_SDRAM_DEVICE0_1_SELECT
                  command: EXMC_SDRAM_NORMAL_OPERATION, EXMC_SDRAM_CLOCK_ENABLE, EXMC_SDRAM_PRECHARGE_ALL,
                           EXMC_SDRAM_AUTO_REFRESH, EXMC_SDRAM_LOAD_MODE_REGISTER, EXMC_SDRAM_SELF_REFRESH,
                           EXMC_SDRAM_POWERDOWN_ENTRY
    \param[out] none
    \retval     none
*/
void exmc_sdram_command_config(exmc_sdram_command_parameter_struct *exmc_sdram_command_init_struct)
{
    /* configure command register */
    EXMC_SDCMD = (uint32_t)((exmc_sdram_command_init_struct->command) |
                            (exmc_sdram_command_init_struct->bank_select) |
                            ((exmc_sdram_command_init_struct->auto_refresh_number)) |
                            ((exmc_sdram_command_init_struct->mode_register_content) << SDCMD_MRC_OFFSET));
}

/*!
    \brief      set auto-refresh interval
    \param[in]  exmc_count: the number SDRAM clock cycles unit between two successive auto-refresh commands, 0x00000000~0x00001FFF
    \param[out] none
    \retval     none
*/
void exmc_sdram_refresh_count_set(uint32_t exmc_count)
{
    uint32_t sdari;
    sdari = EXMC_SDARI & (~EXMC_SDARI_ARINTV);
    EXMC_SDARI = sdari | (uint32_t)((exmc_count << SDARI_ARINTV_OFFSET) & EXMC_SDARI_ARINTV);
}

/*!
    \brief      set the number of successive auto-refresh command
    \param[in]  exmc_number: the number of successive Auto-refresh cycles will be send, 1~15
    \param[out] none
    \retval     none
*/
void exmc_sdram_autorefresh_number_set(uint32_t exmc_number)
{
    uint32_t sdcmd;
    sdcmd = EXMC_SDCMD & (~EXMC_SDCMD_NARF);
    EXMC_SDCMD = sdcmd | (uint32_t)((exmc_number << SDCMD_NARF_OFFSET) & EXMC_SDCMD_NARF);
}

/*!
    \brief      configure the write protection function
    \param[in]  exmc_sdram_device: specify the SDRAM device
                only one parameter can be selected which is shown as below:
      \arg        EXMC_SDRAM_DEVICEx(x=0,1)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void exmc_sdram_write_protection_config(uint32_t exmc_sdram_device, ControlStatus newvalue)
{
    if(ENABLE == newvalue)
    {
        EXMC_SDCTL(exmc_sdram_device) |= (uint32_t)EXMC_SDCTL_WPEN;
    } else {
        EXMC_SDCTL(exmc_sdram_device) &= ~((uint32_t)EXMC_SDCTL_WPEN);
    }
}

/*!
    \brief      get the status of SDRAM device0 or device1
    \param[in]  exmc_sdram_device: specify the SDRAM device
                only one parameter can be selected which is shown as below:
      \arg        EXMC_SDRAM_DEVICEx(x=0,1)
    \param[out] none
    \retval     the status of SDRAM device
*/
uint32_t exmc_sdram_bankstatus_get(uint32_t exmc_sdram_device)
{
    uint32_t sdstat = 0U;

    if(EXMC_SDRAM_DEVICE0 == exmc_sdram_device)
    {
        sdstat = ((uint32_t)(EXMC_SDSTAT & EXMC_SDSDAT_STA0) >> SDSTAT_STA0_OFFSET);
    } else {
        sdstat = ((uint32_t)(EXMC_SDSTAT & EXMC_SDSDAT_STA1) >> SDSTAT_STA1_OFFSET);
    }

    return sdstat;
}

/*!
    \brief      get EXMC flag status
    \param[in]  exmc_bank: specify the NAND bank or SDRAM device
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_SDRAM_DEVICE0: the SDRAM device0
      \arg        EXMC_SDRAM_DEVICE1: the SDRAM device1
    \param[in]  flag: EXMC status and flag
                only one parameter can be selected which is shown as below:
      \arg        EXMC_NAND_FLAG_LEVEL: interrupt high-level status
      \arg        EXMC_NAND_FLAG_RISE: interrupt rising edge status
      \arg        EXMC_NAND_FLAG_FALL: interrupt falling edge status
      \arg        EXMC_NAND_FLAG_FIFOE: FIFO empty flag
      \arg        EXMC_SDRAM_FLAG_REFRESH: refresh error interrupt flag
      \arg        EXMC_SDRAM_FLAG_NREADY: not ready status
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus exmc_flag_get(uint32_t exmc_bank, uint32_t flag)
{
    uint32_t status = 0x00000000U;

    if(EXMC_BANK2_NAND == exmc_bank)
    {
        /* NAND bank2 */
        status = EXMC_NINTEN;
    } else {
        /* SDRAM device0 or device1 */
        status = EXMC_SDSTAT;
    }

    if((status & flag) != (uint32_t)flag)
    {
        /* flag is reset */
        return RESET;
    } else {
        /* flag is set */
        return SET;
    }
}

/*!
    \brief      clear EXMC flag status
    \param[in]  exmc_bank: specify the NAND bank or SDRAM device
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_SDRAM_DEVICE0: the SDRAM device0
      \arg        EXMC_SDRAM_DEVICE1: the SDRAM device1
    \param[in]  flag: EXMC status and flag
                only one parameter can be selected which is shown as below:
      \arg        EXMC_NAND_FLAG_LEVEL: interrupt high-level status
      \arg        EXMC_NAND_FLAG_RISE: interrupt rising edge status
      \arg        EXMC_NAND_FLAG_FALL: interrupt falling edge status
      \arg        EXMC_NAND_FLAG_FIFOE: FIFO empty flag
      \arg        EXMC_SDRAM_FLAG_REFRESH: refresh error interrupt flag
    \param[out] none
    \retval     none
*/
void exmc_flag_clear(uint32_t exmc_bank, uint32_t flag)
{
    if(EXMC_BANK2_NAND == exmc_bank)
    {
        /* NAND bank2 */
        EXMC_NINTEN &= ~flag;
    } else {
        /* SDRAM device0 or device1 */
        EXMC_SDARI |= EXMC_SDARI_REC;
    }
}

/*!
    \brief      enable EXMC interrupt
    \param[in]  exmc_bank: specify the NAND bank or SDRAM device
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_SDRAM_DEVICE0: the SDRAM device0
      \arg        EXMC_SDRAM_DEVICE1: the SDRAM device1
    \param[in]  interrupt: specify get which interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        EXMC_NAND_INT_FLAG_LEVEL: high-level interrupt flag
      \arg        EXMC_NAND_INT_FLAG_RISE: rising edge interrupt flag
      \arg        EXMC_NAND_INT_FLAG_FALL: falling edge interrupt flag
      \arg        EXMC_SDRAM_INT_FLAG_REFRESH: refresh error interrupt flag
    \param[out] none
    \retval     none
*/
void exmc_interrupt_enable(uint32_t exmc_bank, uint32_t interrupt)
{
    if(EXMC_BANK2_NAND == exmc_bank)
    {
        /* NAND bank2 */
        EXMC_NINTEN |= interrupt;
    } else {
        /* SDRAM device0 or device1 */
        EXMC_SDARI |= EXMC_SDARI_REIE;
    }
}

/*!
    \brief      disable EXMC interrupt
    \param[in]  exmc_bank: specify the NAND bank or SDRAM device
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_SDRAM_DEVICE0: the SDRAM device0
      \arg        EXMC_SDRAM_DEVICE1: the SDRAM device1
    \param[in]  interrupt: specify get which interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        EXMC_NAND_INT_LEVEL: high-level interrupt
      \arg        EXMC_NAND_INT_RISE: rising edge interrupt
      \arg        EXMC_NAND_INT_FALL: falling edge interrupt
      \arg        EXMC_SDRAM_INT_REFRESH: refresh error interrupt
    \param[out] none
    \retval     none
*/
void exmc_interrupt_disable(uint32_t exmc_bank, uint32_t interrupt)
{
    if(EXMC_BANK2_NAND == exmc_bank)
    {
        /* NAND bank2 */
        EXMC_NINTEN &= ~interrupt;
    } else {
        /* SDRAM device0 or device1 */
        EXMC_SDARI &= ~EXMC_SDARI_REIE;
    }
}

/*!
    \brief      get EXMC interrupt flag
    \param[in]  exmc_bank: specify the NAND bank or SDRAM device
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_SDRAM_DEVICE0: the SDRAM device0
      \arg        EXMC_SDRAM_DEVICE1: the SDRAM device1
    \param[in]  interrupt: EXMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        EXMC_NAND_INT_FLAG_LEVEL: high-level interrupt flag
      \arg        EXMC_NAND_INT_FLAG_RISE: rising edge interrupt flag
      \arg        EXMC_NAND_INT_FLAG_FALL: falling edge interrupt flag
      \arg        EXMC_SDRAM_INT_FLAG_REFRESH: refresh error interrupt and flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus exmc_interrupt_flag_get(uint32_t exmc_bank, uint32_t interrupt)
{
    uint32_t reg_value = 0x00000000U;
    uint32_t interrupt_enable = 0x00000000U;
    uint32_t interrupt_status = 0x00000000U;

    if(EXMC_BANK2_NAND == exmc_bank)
    {
        /* NAND bank2 */
        reg_value = EXMC_NINTEN;
        interrupt_status = (reg_value & (interrupt >> NINTEN_INTEN_INTS_INTERVAL));
    } else {
        /* SDRAM device0 or device1 */
        reg_value = EXMC_SDARI;
        interrupt_status = (EXMC_SDSTAT & EXMC_SDSDAT_REIF);
    }

    interrupt_enable = (reg_value & interrupt);

    if((interrupt_enable) && (interrupt_status))
    {
        /* interrupt flag is set */
        return SET;
    } else {
        /* interrupt flag is reset */
        return RESET;
    }
}

/*!
    \brief      clear EXMC interrupt flag
    \param[in]  exmc_bank: specify the NAND bank or SDRAM device
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_SDRAM_DEVICE0: the SDRAM device0
      \arg        EXMC_SDRAM_DEVICE1: the SDRAM device1
    \param[in]  interrupt: EXMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        EXMC_NAND_INT_FLAG_LEVEL: high-level interrupt and flag
      \arg        EXMC_NAND_INT_FLAG_RISE: rising edge interrupt and flag
      \arg        EXMC_NAND_INT_FLAG_FALL: falling edge interrupt and flag
      \arg        EXMC_SDRAM_INT_FLAG_REFRESH: refresh error interrupt and flag
    \param[out] none
    \retval     none
*/
void exmc_interrupt_flag_clear(uint32_t exmc_bank, uint32_t interrupt)
{
    if(EXMC_BANK2_NAND == exmc_bank)
    {
        /* NAND bank2 */
        EXMC_NINTEN &= ~(interrupt >> NINTEN_INTEN_INTS_INTERVAL);
    } else {
        /* SDRAM device0 or device1 */
        EXMC_SDARI |= EXMC_SDARI_REC;
    }
}
