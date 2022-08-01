/*!
    \file    gd32f10x_exmc.c
    \brief   EXMC driver

    \version 2014-12-26, V1.0.0, firmware for GD32F10x
    \version 2017-06-20, V2.0.0, firmware for GD32F10x
    \version 2018-07-31, V2.1.0, firmware for GD32F10x
    \version 2020-09-30, V2.2.0, firmware for GD32F10x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

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

#include "gd32f10x_exmc.h"

/* EXMC bank0 register reset value */
#define BANK0_SNCTL0_REGION_RESET         ((uint32_t)0x000030DBU)
#define BANK0_SNCTL1_2_3_REGION_RESET     ((uint32_t)0x000030D2U)
#define BANK0_SNTCFG_RESET                ((uint32_t)0x0FFFFFFFU)
#define BANK0_SNWTCFG_RESET               ((uint32_t)0x0FFFFFFFU)

/* EXMC bank1/2 register reset mask*/
#define BANK1_2_NPCTL_RESET               ((uint32_t)0x00000018U)
#define BANK1_2_NPINTEN_RESET             ((uint32_t)0x00000040U)
#define BANK1_2_NPCTCFG_RESET             ((uint32_t)0xFCFCFCFCU)
#define BANK1_2_NPATCFG_RESET             ((uint32_t)0xFCFCFCFCU)

/* EXMC bank3 register reset mask*/
#define BANK3_NPCTL_RESET                 ((uint32_t)0x00000018U)
#define BANK3_NPINTEN_RESET               ((uint32_t)0x00000040U)
#define BANK3_NPCTCFG_RESET               ((uint32_t)0xFCFCFCFCU)
#define BANK3_NPATCFG_RESET               ((uint32_t)0xFCFCFCFCU)
#define BANK3_PIOTCFG3_RESET              ((uint32_t)0xFCFCFCFCU)

/* EXMC register bit offset */
#define SNCTL_NRMUX_OFFSET                ((uint32_t)1U)
#define SNCTL_SBRSTEN_OFFSET              ((uint32_t)8U)
#define SNCTL_WRAPEN_OFFSET               ((uint32_t)10U)
#define SNCTL_WREN_OFFSET                 ((uint32_t)12U)
#define SNCTL_NRWTEN_OFFSET               ((uint32_t)13U)
#define SNCTL_EXMODEN_OFFSET              ((uint32_t)14U)
#define SNCTL_ASYNCWAIT_OFFSET            ((uint32_t)15U)

#define SNTCFG_AHLD_OFFSET                ((uint32_t)4U)
#define SNTCFG_DSET_OFFSET                ((uint32_t)8U)
#define SNTCFG_BUSLAT_OFFSET              ((uint32_t)16U)

#define SNWTCFG_WAHLD_OFFSET              ((uint32_t)4U)
#define SNWTCFG_WDSET_OFFSET              ((uint32_t)8U)
#define SNWTCFG_WBUSLAT_OFFSET            ((uint32_t)16U)

#define NPCTL_NDWTEN_OFFSET               ((uint32_t)1U)
#define NPCTL_ECCEN_OFFSET                ((uint32_t)6U)

#define NPCTCFG_COMWAIT_OFFSET            ((uint32_t)8U)
#define NPCTCFG_COMHLD_OFFSET             ((uint32_t)16U)
#define NPCTCFG_COMHIZ_OFFSET             ((uint32_t)24U)

#define NPATCFG_ATTWAIT_OFFSET            ((uint32_t)8U)
#define NPATCFG_ATTHLD_OFFSET             ((uint32_t)16U)
#define NPATCFG_ATTHIZ_OFFSET             ((uint32_t)24U)

#define PIOTCFG_IOWAIT_OFFSET             ((uint32_t)8U)
#define PIOTCFG_IOHLD_OFFSET              ((uint32_t)16U)
#define PIOTCFG_IOHIZ_OFFSET              ((uint32_t)24U)

#define INTEN_INTS_OFFSET                 ((uint32_t)3U)

/*!
    \brief      deinitialize EXMC NOR/SRAM region
    \param[in]  norsram_region: select the region of bank0
      \arg        EXMC_BANK0_NORSRAM_REGIONx(x=0..3)
    \param[out] none
    \retval     none
*/
void exmc_norsram_deinit(uint32_t norsram_region)
{
    /* reset the registers */
    if(EXMC_BANK0_NORSRAM_REGION0 == norsram_region){
        EXMC_SNCTL(norsram_region) = BANK0_SNCTL0_REGION_RESET;
    }else{
        EXMC_SNCTL(norsram_region) = BANK0_SNCTL1_2_3_REGION_RESET;
    }

    EXMC_SNTCFG(norsram_region) = BANK0_SNTCFG_RESET;
    EXMC_SNWTCFG(norsram_region) = BANK0_SNWTCFG_RESET;
}

/*!
    \brief      initialize EXMC NOR/SRAM region
    \param[in]  exmc_norsram_parameter_struct: configure the EXMC NOR/SRAM parameter
                  norsram_region: EXMC_BANK0_NORSRAM_REGIONx,x=0..3
                  write_mode: EXMC_ASYN_WRITE,EXMC_SYN_WRITE
                  extended_mode: ENABLE or DISABLE
                  asyn_wait: ENABLE or DISABLE
                  nwait_signal: ENABLE or DISABLE
                  memory_write: ENABLE or DISABLE
                  nwait_config: EXMC_NWAIT_CONFIG_BEFORE,EXMC_NWAIT_CONFIG_DURING
                  wrap_burst_mode: ENABLE or DISABLE
                  nwait_polarity: EXMC_NWAIT_POLARITY_LOW,EXMC_NWAIT_POLARITY_HIGH
                  burst_mode: ENABLE or DISABLE
                  databus_width: EXMC_NOR_DATABUS_WIDTH_8B,EXMC_NOR_DATABUS_WIDTH_16B
                  memory_type: EXMC_MEMORY_TYPE_SRAM,EXMC_MEMORY_TYPE_PSRAM,EXMC_MEMORY_TYPE_NOR
                  address_data_mux: ENABLE or DISABLE
                  read_write_timing: struct exmc_norsram_timing_parameter_struct set the time
                  write_timing: struct exmc_norsram_timing_parameter_struct set the time
    \param[out] none
    \retval     none
*/
void exmc_norsram_init(exmc_norsram_parameter_struct* exmc_norsram_init_struct)
{
    uint32_t snctl = 0x00000000U, sntcfg = 0x00000000U, snwtcfg = 0x00000000U;

    /* get the register value */
    snctl = EXMC_SNCTL(exmc_norsram_init_struct->norsram_region);

    /* clear relative bits */
    snctl &= ((uint32_t)~(EXMC_SNCTL_NREN | EXMC_SNCTL_NRTP | EXMC_SNCTL_NRW | EXMC_SNCTL_SBRSTEN |
                          EXMC_SNCTL_NRWTPOL | EXMC_SNCTL_WRAPEN | EXMC_SNCTL_NRWTCFG | EXMC_SNCTL_WREN |
                          EXMC_SNCTL_NRWTEN | EXMC_SNCTL_EXMODEN | EXMC_SNCTL_ASYNCWAIT | EXMC_SNCTL_SYNCWR |
                          EXMC_SNCTL_NRMUX ));

    snctl |= (uint32_t)(exmc_norsram_init_struct->address_data_mux << SNCTL_NRMUX_OFFSET) |
                        exmc_norsram_init_struct->memory_type |
                        exmc_norsram_init_struct->databus_width |
                       (exmc_norsram_init_struct->burst_mode << SNCTL_SBRSTEN_OFFSET) |
                        exmc_norsram_init_struct->nwait_polarity |
                       (exmc_norsram_init_struct->wrap_burst_mode << SNCTL_WRAPEN_OFFSET) |
                        exmc_norsram_init_struct->nwait_config |
                       (exmc_norsram_init_struct->memory_write << SNCTL_WREN_OFFSET) |
                       (exmc_norsram_init_struct->nwait_signal << SNCTL_NRWTEN_OFFSET) |
                       (exmc_norsram_init_struct->extended_mode << SNCTL_EXMODEN_OFFSET) |
                       (exmc_norsram_init_struct->asyn_wait << SNCTL_ASYNCWAIT_OFFSET) |
                        exmc_norsram_init_struct->write_mode;

    sntcfg = (uint32_t)((exmc_norsram_init_struct->read_write_timing->asyn_address_setuptime - 1U ) & EXMC_SNTCFG_ASET )|
                       (((exmc_norsram_init_struct->read_write_timing->asyn_address_holdtime - 1U ) << SNTCFG_AHLD_OFFSET ) & EXMC_SNTCFG_AHLD ) |
                       (((exmc_norsram_init_struct->read_write_timing->asyn_data_setuptime - 1U ) << SNTCFG_DSET_OFFSET ) & EXMC_SNTCFG_DSET ) |
                       (((exmc_norsram_init_struct->read_write_timing->bus_latency - 1U ) << SNTCFG_BUSLAT_OFFSET ) & EXMC_SNTCFG_BUSLAT )|
                       exmc_norsram_init_struct->read_write_timing->syn_clk_division |
                       exmc_norsram_init_struct->read_write_timing->syn_data_latency |
                       exmc_norsram_init_struct->read_write_timing->asyn_access_mode;

    /* nor flash access enable */
    if(EXMC_MEMORY_TYPE_NOR == exmc_norsram_init_struct->memory_type){
        snctl |= (uint32_t)EXMC_SNCTL_NREN;
    }

    /* extended mode configure */
    if(ENABLE == exmc_norsram_init_struct->extended_mode){
        snwtcfg = (uint32_t)(((exmc_norsram_init_struct->write_timing->asyn_address_setuptime - 1U) & EXMC_SNWTCFG_WASET) |
                             (((exmc_norsram_init_struct->write_timing->asyn_address_holdtime - 1U) << SNTCFG_AHLD_OFFSET ) & EXMC_SNWTCFG_WAHLD)|
                             (((exmc_norsram_init_struct->write_timing->asyn_data_setuptime - 1U) << SNTCFG_DSET_OFFSET) & EXMC_SNWTCFG_WDSET) |
                              exmc_norsram_init_struct->write_timing->asyn_access_mode);
    }else{
        snwtcfg = BANK0_SNWTCFG_RESET;
    }

    /* configure the registers */
    EXMC_SNCTL(exmc_norsram_init_struct->norsram_region) = snctl;
    EXMC_SNTCFG(exmc_norsram_init_struct->norsram_region) = sntcfg;
    EXMC_SNWTCFG(exmc_norsram_init_struct->norsram_region) = snwtcfg;
}

/*!
    \brief      initialize the struct exmc_norsram_parameter_struct
    \param[in]  none
    \param[out] exmc_norsram_init_struct: the initialized struct exmc_norsram_parameter_struct pointer
    \retval     none
*/
void exmc_norsram_struct_para_init(exmc_norsram_parameter_struct* exmc_norsram_init_struct)
{
    /* configure the structure with default value */
    exmc_norsram_init_struct->norsram_region = EXMC_BANK0_NORSRAM_REGION0;
    exmc_norsram_init_struct->address_data_mux = ENABLE;
    exmc_norsram_init_struct->memory_type = EXMC_MEMORY_TYPE_SRAM;
    exmc_norsram_init_struct->databus_width = EXMC_NOR_DATABUS_WIDTH_8B;
    exmc_norsram_init_struct->burst_mode = DISABLE;
    exmc_norsram_init_struct->nwait_polarity = EXMC_NWAIT_POLARITY_LOW;
    exmc_norsram_init_struct->wrap_burst_mode = DISABLE;
    exmc_norsram_init_struct->nwait_config = EXMC_NWAIT_CONFIG_BEFORE;
    exmc_norsram_init_struct->memory_write = ENABLE;
    exmc_norsram_init_struct->nwait_signal = ENABLE;
    exmc_norsram_init_struct->extended_mode = DISABLE;
    exmc_norsram_init_struct->asyn_wait = DISABLE;
    exmc_norsram_init_struct->write_mode = EXMC_ASYN_WRITE;

    /* read/write timing configure */
    exmc_norsram_init_struct->read_write_timing->asyn_address_setuptime = 0xFU;
    exmc_norsram_init_struct->read_write_timing->asyn_address_holdtime = 0xFU;
    exmc_norsram_init_struct->read_write_timing->asyn_data_setuptime = 0xFFU;
    exmc_norsram_init_struct->read_write_timing->bus_latency = 0xFU;
    exmc_norsram_init_struct->read_write_timing->syn_clk_division = EXMC_SYN_CLOCK_RATIO_16_CLK;
    exmc_norsram_init_struct->read_write_timing->syn_data_latency = EXMC_DATALAT_17_CLK;
    exmc_norsram_init_struct->read_write_timing->asyn_access_mode = EXMC_ACCESS_MODE_A;

    /* write timing configure, when extended mode is used */
    exmc_norsram_init_struct->write_timing->asyn_address_setuptime = 0xFU;
    exmc_norsram_init_struct->write_timing->asyn_address_holdtime = 0xFU;
    exmc_norsram_init_struct->write_timing->asyn_data_setuptime = 0xFFU;
    exmc_norsram_init_struct->write_timing->bus_latency = 0xFU;
    exmc_norsram_init_struct->write_timing->asyn_access_mode = EXMC_ACCESS_MODE_A;
}

/*!
    \brief      enable EXMC NOR/PSRAM bank region
    \param[in]  norsram_region: specifie the region of NOR/PSRAM bank
      \arg        EXMC_BANK0_NORSRAM_REGIONx(x=0..3)
    \param[out] none
    \retval     none
*/
void exmc_norsram_enable(uint32_t norsram_region)
{
    EXMC_SNCTL(norsram_region) |= (uint32_t)EXMC_SNCTL_NRBKEN;
}

/*!
    \brief      disable EXMC NOR/PSRAM bank region
    \param[in]  norsram_region: specifie the region of NOR/PSRAM Bank
      \arg        EXMC_BANK0_NORSRAM_REGIONx(x=0..3)
    \param[out] none
    \retval     none
*/
void exmc_norsram_disable(uint32_t norsram_region)
{
    EXMC_SNCTL(norsram_region) &= ~(uint32_t)EXMC_SNCTL_NRBKEN;
}

/*!
    \brief      deinitialize EXMC NAND bank
    \param[in]  nand_bank: select the bank of NAND
      \arg        EXMC_BANKx_NAND(x=1..2)
    \param[out] none
    \retval     none
*/
void exmc_nand_deinit(uint32_t nand_bank)
{
    /* EXMC_BANK1_NAND or EXMC_BANK2_NAND */
    EXMC_NPCTL(nand_bank) = BANK1_2_NPCTL_RESET;
    EXMC_NPINTEN(nand_bank) = BANK1_2_NPINTEN_RESET;
    EXMC_NPCTCFG(nand_bank) = BANK1_2_NPCTCFG_RESET;
    EXMC_NPATCFG(nand_bank) = BANK1_2_NPATCFG_RESET;
}

/*!
    \brief      initialize EXMC NAND bank
    \param[in]  exmc_nand_parameter_struct: configure the EXMC NAND parameter
                  nand_bank: EXMC_BANK1_NAND,EXMC_BANK2_NAND
                  ecc_size: EXMC_ECC_SIZE_xBYTES,x=256,512,1024,2048,4096
                  atr_latency: EXMC_ALE_RE_DELAY_x_HCLK,x=1..16
                  ctr_latency: EXMC_CLE_RE_DELAY_x_HCLK,x=1..16
                  ecc_logic: ENABLE or DISABLE
                  databus_width: EXMC_NAND_DATABUS_WIDTH_8B,EXMC_NAND_DATABUS_WIDTH_16B
                  wait_feature: ENABLE or DISABLE
                  common_space_timing: struct exmc_nand_pccard_timing_parameter_struct set the time
                  attribute_space_timing: struct exmc_nand_pccard_timing_parameter_struct set the time
    \param[out] none
    \retval     none
*/
void exmc_nand_init(exmc_nand_parameter_struct* exmc_nand_init_struct)
{
    uint32_t npctl = 0x00000000U, npctcfg = 0x00000000U, npatcfg = 0x00000000U;

    npctl = (uint32_t)(exmc_nand_init_struct->wait_feature << NPCTL_NDWTEN_OFFSET)|
                       EXMC_NPCTL_NDTP |
                       exmc_nand_init_struct->databus_width |
                      (exmc_nand_init_struct->ecc_logic << NPCTL_ECCEN_OFFSET)|
                       exmc_nand_init_struct->ecc_size |
                       exmc_nand_init_struct->ctr_latency |
                       exmc_nand_init_struct->atr_latency;

    npctcfg = (uint32_t)((exmc_nand_init_struct->common_space_timing->setuptime - 1U) & EXMC_NPCTCFG_COMSET ) |
                        (((exmc_nand_init_struct->common_space_timing->waittime - 1U) << NPCTCFG_COMWAIT_OFFSET) & EXMC_NPCTCFG_COMWAIT ) |
                        ((exmc_nand_init_struct->common_space_timing->holdtime << NPCTCFG_COMHLD_OFFSET) & EXMC_NPCTCFG_COMHLD ) |
                        (((exmc_nand_init_struct->common_space_timing->databus_hiztime - 1U) << NPCTCFG_COMHIZ_OFFSET) & EXMC_NPCTCFG_COMHIZ );

    npatcfg = (uint32_t)((exmc_nand_init_struct->attribute_space_timing->setuptime - 1U) & EXMC_NPATCFG_ATTSET ) |
                        (((exmc_nand_init_struct->attribute_space_timing->waittime - 1U) << NPATCFG_ATTWAIT_OFFSET) & EXMC_NPATCFG_ATTWAIT ) |
                        ((exmc_nand_init_struct->attribute_space_timing->holdtime << NPATCFG_ATTHLD_OFFSET) & EXMC_NPATCFG_ATTHLD ) |
                        (((exmc_nand_init_struct->attribute_space_timing->databus_hiztime -1U) << NPATCFG_ATTHIZ_OFFSET) & EXMC_NPATCFG_ATTHIZ );

    /* EXMC_BANK1_NAND or EXMC_BANK2_NAND initialize */
    EXMC_NPCTL(exmc_nand_init_struct->nand_bank) = npctl;
    EXMC_NPCTCFG(exmc_nand_init_struct->nand_bank) = npctcfg;
    EXMC_NPATCFG(exmc_nand_init_struct->nand_bank) = npatcfg;
}

/*!
    \brief      initialize the struct exmc_nand_init_struct
    \param[in]  none
    \param[out] the initialized struct exmc_nand_init_struct pointer
    \retval     none
*/
void exmc_nand_struct_para_init(exmc_nand_parameter_struct* exmc_nand_init_struct)
{
    /* configure the structure with default value */
    exmc_nand_init_struct->nand_bank = EXMC_BANK1_NAND;
    exmc_nand_init_struct->wait_feature = DISABLE;
    exmc_nand_init_struct->databus_width = EXMC_NAND_DATABUS_WIDTH_8B;
    exmc_nand_init_struct->ecc_logic = DISABLE;
    exmc_nand_init_struct->ecc_size = EXMC_ECC_SIZE_256BYTES;
    exmc_nand_init_struct->ctr_latency = 0x0U;
    exmc_nand_init_struct->atr_latency = 0x0U;
    exmc_nand_init_struct->common_space_timing->setuptime = 0xFCU;
    exmc_nand_init_struct->common_space_timing->waittime = 0xFCU;
    exmc_nand_init_struct->common_space_timing->holdtime = 0xFCU;
    exmc_nand_init_struct->common_space_timing->databus_hiztime = 0xFCU;
    exmc_nand_init_struct->attribute_space_timing->setuptime = 0xFCU;
    exmc_nand_init_struct->attribute_space_timing->waittime = 0xFCU;
    exmc_nand_init_struct->attribute_space_timing->holdtime = 0xFCU;
    exmc_nand_init_struct->attribute_space_timing->databus_hiztime = 0xFCU;
}

/*!
    \brief      enable NAND bank
    \param[in]  nand_bank: specifie the NAND bank
      \arg        EXMC_BANKx_NAND(x=1,2)
    \param[out] none
    \retval     none
*/
void exmc_nand_enable(uint32_t nand_bank)
{
    EXMC_NPCTL(nand_bank) |= EXMC_NPCTL_NDBKEN;
}

/*!
    \brief      disable NAND bank
    \param[in]  nand_bank: specifie the NAND bank
      \arg        EXMC_BANKx_NAND(x=1,2)
    \param[out] none
    \retval     none
*/
void exmc_nand_disable(uint32_t nand_bank)
{
    EXMC_NPCTL(nand_bank) &= ~EXMC_NPCTL_NDBKEN;
}

/*!
    \brief      enable or disable the EXMC NAND ECC function
    \param[in]  nand_bank: specifie the NAND bank
      \arg        EXMC_BANKx_NAND(x=1,2)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void exmc_nand_ecc_config(uint32_t nand_bank, ControlStatus newvalue)
{
    if (ENABLE == newvalue){
        /* enable the selected NAND bank ECC function */
        EXMC_NPCTL(nand_bank) |= EXMC_NPCTL_ECCEN;
    }else{
        /* disable the selected NAND bank ECC function */
        EXMC_NPCTL(nand_bank) &= ~EXMC_NPCTL_ECCEN;
    }
}

/*!
    \brief      get the EXMC ECC value
    \param[in]  nand_bank: specifie the NAND bank
      \arg        EXMC_BANKx_NAND(x=1,2)
    \param[out] none
    \retval     the error correction code(ECC) value
*/
uint32_t exmc_ecc_get(uint32_t nand_bank)
{
    return (EXMC_NECC(nand_bank));
}

/*!
    \brief      deinitialize EXMC PC card bank
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_pccard_deinit(void)
{
    /* EXMC_BANK3_PCCARD */
    EXMC_NPCTL3 = BANK3_NPCTL_RESET;
    EXMC_NPINTEN3 = BANK3_NPINTEN_RESET;
    EXMC_NPCTCFG3 = BANK3_NPCTCFG_RESET;
    EXMC_NPATCFG3 = BANK3_NPATCFG_RESET;
    EXMC_PIOTCFG3 = BANK3_PIOTCFG3_RESET;
}

/*!
    \brief      initialize EXMC PC card bank
    \param[in]  exmc_pccard_parameter_struct: configure the EXMC NAND parameter
                  atr_latency: EXMC_ALE_RE_DELAY_x_HCLK,x=1..16
                  ctr_latency: EXMC_CLE_RE_DELAY_x_HCLK,x=1..16
                  wait_feature: ENABLE or DISABLE
                  common_space_timing: struct exmc_nand_pccard_timing_parameter_struct set the time
                  attribute_space_timing: struct exmc_nand_pccard_timing_parameter_struct set the time
                  io_space_timing: exmc_nand_pccard_timing_parameter_struct set the time
    \param[out] none
    \retval     none
*/
void exmc_pccard_init(exmc_pccard_parameter_struct* exmc_pccard_init_struct)
{
    /* configure the EXMC bank3 PC card control register */
    EXMC_NPCTL3 = (uint32_t)(exmc_pccard_init_struct->wait_feature << NPCTL_NDWTEN_OFFSET) |
                             EXMC_NAND_DATABUS_WIDTH_16B |
                             exmc_pccard_init_struct->ctr_latency |
                             exmc_pccard_init_struct->atr_latency ;

    /* configure the EXMC bank3 PC card common space timing configuration register */
    EXMC_NPCTCFG3 = (uint32_t)((exmc_pccard_init_struct->common_space_timing->setuptime - 1U)& EXMC_NPCTCFG_COMSET ) |
                              (((exmc_pccard_init_struct->common_space_timing->waittime - 1U) << NPCTCFG_COMWAIT_OFFSET) & EXMC_NPCTCFG_COMWAIT ) |
                              ((exmc_pccard_init_struct->common_space_timing->holdtime << NPCTCFG_COMHLD_OFFSET) & EXMC_NPCTCFG_COMHLD ) |
                              (((exmc_pccard_init_struct->common_space_timing->databus_hiztime - 1U) << NPCTCFG_COMHIZ_OFFSET) & EXMC_NPCTCFG_COMHIZ );

    /* configure the EXMC bank3 PC card attribute space timing configuration register */
    EXMC_NPATCFG3 = (uint32_t)((exmc_pccard_init_struct->attribute_space_timing->setuptime - 1U) & EXMC_NPATCFG_ATTSET ) |
                              (((exmc_pccard_init_struct->attribute_space_timing->waittime - 1U) << NPATCFG_ATTWAIT_OFFSET) & EXMC_NPATCFG_ATTWAIT ) |
                              ((exmc_pccard_init_struct->attribute_space_timing->holdtime << NPATCFG_ATTHLD_OFFSET) & EXMC_NPATCFG_ATTHLD )|
                              (((exmc_pccard_init_struct->attribute_space_timing->databus_hiztime -1U) << NPATCFG_ATTHIZ_OFFSET) & EXMC_NPATCFG_ATTHIZ );

    /* configure the EXMC bank3 PC card io space timing configuration register */
    EXMC_PIOTCFG3 = (uint32_t)((exmc_pccard_init_struct->io_space_timing->setuptime - 1U) & EXMC_PIOTCFG3_IOSET ) |
                              (((exmc_pccard_init_struct->io_space_timing->waittime - 1U) << PIOTCFG_IOWAIT_OFFSET) & EXMC_PIOTCFG3_IOWAIT ) |
                              ((exmc_pccard_init_struct->io_space_timing->holdtime << PIOTCFG_IOHLD_OFFSET) & EXMC_PIOTCFG3_IOHLD )|
                              ((exmc_pccard_init_struct->io_space_timing->databus_hiztime << PIOTCFG_IOHIZ_OFFSET) & EXMC_PIOTCFG3_IOHIZ );
}

/*!
    \brief      initialize the struct exmc_pccard_parameter_struct
    \param[in]  none
    \param[out] the initialized struct exmc_pccard_parameter_struct pointer
    \retval     none
*/
void exmc_pccard_struct_para_init(exmc_pccard_parameter_struct* exmc_pccard_init_struct)
{
    /* configure the structure with default value */
    exmc_pccard_init_struct->wait_feature = DISABLE;
    exmc_pccard_init_struct->ctr_latency = 0x0U;
    exmc_pccard_init_struct->atr_latency = 0x0U;
    exmc_pccard_init_struct->common_space_timing->setuptime = 0xFCU;
    exmc_pccard_init_struct->common_space_timing->waittime = 0xFCU;
    exmc_pccard_init_struct->common_space_timing->holdtime = 0xFCU;
    exmc_pccard_init_struct->common_space_timing->databus_hiztime = 0xFCU;
    exmc_pccard_init_struct->attribute_space_timing->setuptime = 0xFCU;
    exmc_pccard_init_struct->attribute_space_timing->waittime = 0xFCU;
    exmc_pccard_init_struct->attribute_space_timing->holdtime = 0xFCU;
    exmc_pccard_init_struct->attribute_space_timing->databus_hiztime = 0xFCU;
    exmc_pccard_init_struct->io_space_timing->setuptime = 0xFCU;
    exmc_pccard_init_struct->io_space_timing->waittime = 0xFCU;
    exmc_pccard_init_struct->io_space_timing->holdtime = 0xFCU;
    exmc_pccard_init_struct->io_space_timing->databus_hiztime = 0xFCU;
}

/*!
    \brief      enable PC Card Bank
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_pccard_enable(void)
{
    EXMC_NPCTL3 |= EXMC_NPCTL_NDBKEN;
}

/*!
    \brief      disable PC Card Bank
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_pccard_disable(void)
{
   EXMC_NPCTL3 &= ~EXMC_NPCTL_NDBKEN;
}

/*!
    \brief      enable EXMC interrupt
    \param[in]  bank: specifies the NAND bank, PC card bank
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK1_NAND: the NAND bank1
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_BANK3_PCCARD: the PC card bank
    \param[in]  interrupt_source: specify get which interrupt flag
                one or more parameters can be selected which is shown as below:
      \arg        EXMC_NAND_PCCARD_INT_RISE: interrupt source of rising edge
      \arg        EXMC_NAND_PCCARD_INT_LEVEL: interrupt source of high-level
      \arg        EXMC_NAND_PCCARD_INT_FALL: interrupt source of falling edge
    \param[out] none
    \retval     none
*/
void exmc_interrupt_enable(uint32_t bank, uint32_t interrupt_source)
{
    /* NAND bank1, bank2 or PC card bank3 */
    EXMC_NPINTEN(bank) |= interrupt_source;
}

/*!
    \brief      disable EXMC interrupt
    \param[in]  bank: specifies the NAND bank, PC card bank
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK1_NAND: the NAND bank1
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_BANK3_PCCARD: the PC card bank
    \param[in]  interrupt_source: specify get which interrupt flag
                one or more parameters can be selected which is shown as below:
      \arg        EXMC_NAND_PCCARD_INT_RISE: interrupt source of rising edge
      \arg        EXMC_NAND_PCCARD_INT_LEVEL: interrupt source of high-level
      \arg        EXMC_NAND_PCCARD_INT_FALL: interrupt source of falling edge
    \param[out] none
    \retval     none
*/
void exmc_interrupt_disable(uint32_t bank, uint32_t interrupt_source)
{
    /* NAND bank1,bank2 or PC card bank3 */
    EXMC_NPINTEN(bank) &= ~interrupt_source;
}

/*!
    \brief      check EXMC flag is set or not
    \param[in]  bank: specifies the NAND bank, PC card bank
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK1_NAND: the NAND bank1
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_BANK3_PCCARD: the PC Card bank
    \param[in]  flag: specify get which flag
                only one parameter can be selected which is shown as below:
      \arg        EXMC_NAND_PCCARD_FLAG_RISE: interrupt rising edge status
      \arg        EXMC_NAND_PCCARD_FLAG_LEVEL: interrupt high-level status
      \arg        EXMC_NAND_PCCARD_FLAG_FALL: interrupt falling edge status
      \arg        EXMC_NAND_PCCARD_FLAG_FIFOE: FIFO empty flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus exmc_flag_get(uint32_t bank, uint32_t flag)
{
    uint32_t status = 0x00000000U;

    /* NAND bank1,bank2 or PC card bank3 */
    status = EXMC_NPINTEN(bank);

    if ((status & flag) != (uint32_t)flag ){
        /* flag is reset */
        return RESET;
    }else{
        /* flag is set */
        return SET;
    }
}

/*!
    \brief      clear EXMC flag
    \param[in]  bank: specifie the NAND bank, PCCARD bank
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK1_NAND: the NAND bank1
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_BANK3_PCCARD: the PC card bank
    \param[in]  flag: specify get which flag
                one or more parameters can be selected which is shown as below:
      \arg        EXMC_NAND_PCCARD_FLAG_RISE: interrupt rising edge status
      \arg        EXMC_NAND_PCCARD_FLAG_LEVEL: interrupt high-level status
      \arg        EXMC_NAND_PCCARD_FLAG_FALL: interrupt falling edge status
      \arg        EXMC_NAND_PCCARD_FLAG_FIFOE: FIFO empty flag
    \param[out] none
    \retval     none
*/
void exmc_flag_clear(uint32_t bank, uint32_t flag)
{
    /* NAND bank1,bank2 or PC card bank3 */
    EXMC_NPINTEN(bank) &= ~flag;
}

/*!
    \brief      check EXMC interrupt flag is set or not
    \param[in]  bank: specifies the NAND bank, PC card bank
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK1_NAND: the NAND bank1
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_BANK3_PCCARD: the PC card bank
    \param[in]  interrupt_source: specify get which interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        EXMC_NAND_PCCARD_INT_RISE: interrupt source of rising edge
      \arg        EXMC_NAND_PCCARD_INT_LEVEL: interrupt source of high-level
      \arg        EXMC_NAND_PCCARD_INT_FALL: interrupt source of falling edge
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus exmc_interrupt_flag_get(uint32_t bank, uint32_t interrupt_source)
{
    uint32_t status = 0x00000000U,interrupt_enable = 0x00000000U,interrupt_state = 0x00000000U;

    /* NAND bank1,bank2 or PC card bank3 */
    status = EXMC_NPINTEN(bank);
    interrupt_state = (status & (interrupt_source >> INTEN_INTS_OFFSET));

    interrupt_enable = (status & interrupt_source);

    if ((interrupt_enable) && (interrupt_state)){
        /* interrupt flag is set */
        return SET;
    }else{
        /* interrupt flag is reset */
        return RESET;
    }
}

/*!
    \brief      clear EXMC interrupt flag
    \param[in]  bank: specifies the NAND bank, PC card bank
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK1_NAND: the NAND bank1
      \arg        EXMC_BANK2_NAND: the NAND bank2
      \arg        EXMC_BANK3_PCCARD: the PC card bank
    \param[in]  interrupt_source: specify get which interrupt flag
                one or more parameters can be selected which is shown as below:
      \arg        EXMC_NAND_PCCARD_INT_RISE: interrupt source of rising edge
      \arg        EXMC_NAND_PCCARD_INT_LEVEL: interrupt source of high-level
      \arg        EXMC_NAND_PCCARD_INT_FALL: interrupt source of falling edge
    \param[out] none
    \retval     none
*/
void exmc_interrupt_flag_clear(uint32_t bank, uint32_t interrupt_source)
{
    /* NAND bank1, bank2 or PC card bank3 */
    EXMC_NPINTEN(bank) &= ~(interrupt_source >> INTEN_INTS_OFFSET);
}
