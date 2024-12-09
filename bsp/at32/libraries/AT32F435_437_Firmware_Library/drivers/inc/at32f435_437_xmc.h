/**
  **************************************************************************
  * @file     at32f435_437_xmc.h
  * @brief    at32f435_437 xmc header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F435_437_XMC_H
#define __AT32F435_437_XMC_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_periph_driver
  * @{
  */

/** @addtogroup XMC
  * @{
  */

/** @defgroup XMC_exported_types
  * @{
  */

/**
  * @brief xmc data address bus multiplexing type
  */
typedef enum
{
  XMC_DATA_ADDR_MUX_DISABLE              = 0x00000000, /*!< xmc address/data multiplexing disable */
  XMC_DATA_ADDR_MUX_ENABLE               = 0x00000002  /*!< xmc address/data multiplexing enable */
} xmc_data_addr_mux_type;

/**
  * @brief xmc burst access mode type
  */
typedef enum
{
  XMC_BURST_MODE_DISABLE                 = 0x00000000, /*!< xmc burst mode disable */
  XMC_BURST_MODE_ENABLE                  = 0x00000100  /*!< xmc burst mode enable */
} xmc_burst_access_mode_type;

/**
  * @brief xmc asynchronous wait type
  */
typedef enum
{
  XMC_ASYN_WAIT_DISABLE                  = 0x00000000, /*!< xmc wait signal during asynchronous transfers disbale */
  XMC_ASYN_WAIT_ENABLE                   = 0x00008000  /*!< xmc wait signal during asynchronous transfers enable */
} xmc_asyn_wait_type;

/**
  * @brief xmc wrapped mode type
  */
typedef enum
{
  XMC_WRAPPED_MODE_DISABLE               = 0x00000000, /*!< xmc direct wrapped burst is disbale */
  XMC_WRAPPED_MODE_ENABLE                = 0x00000400  /*!< xmc direct wrapped burst is enable */
} xmc_wrap_mode_type;

/**
  * @brief xmc write operation type
  */
typedef enum
{
  XMC_WRITE_OPERATION_DISABLE            = 0x00000000, /*!< xmc write operations is disable */
  XMC_WRITE_OPERATION_ENABLE             = 0x00001000  /*!< xmc write operations is enable */
} xmc_write_operation_type;

/**
  * @brief xmc wait signal type
  */
typedef enum
{
  XMC_WAIT_SIGNAL_DISABLE                = 0x00000000, /*!< xmc nwait signal is disable */
  XMC_WAIT_SIGNAL_ENABLE                 = 0x00002000  /*!< xmc nwait signal is enable */
} xmc_wait_signal_type;

/**
  * @brief xmc write burst type
  */
typedef enum
{
  XMC_WRITE_BURST_SYN_DISABLE            = 0x00000000, /*!< xmc write operations are always performed in asynchronous mode */
  XMC_WRITE_BURST_SYN_ENABLE             = 0x00080000  /*!< xmc write operations are performed in synchronous mode */
} xmc_write_burst_type;

/**
  * @brief xmc extended mode type
  */
typedef enum
{
  XMC_WRITE_TIMING_DISABLE               = 0x00000000, /*!< xmc write timing disable */
  XMC_WRITE_TIMING_ENABLE                = 0x00004000  /*!< xmc write timing enable */
} xmc_extended_mode_type;

/**
  * @brief xmc pccard wait type
  */
typedef enum
{
  XMC_WAIT_OPERATION_DISABLE             = 0x00000000, /*!< xmc wait operation for the pc card/nand flash memory bank disable */
  XMC_WAIT_OPERATION_ENABLE              = 0x00000002  /*!< xmc wait operation for the pc card/nand flash memory bank enable */
} xmc_nand_pccard_wait_type;

/**
  * @brief xmc ecc enable type
  */
typedef enum
{
  XMC_ECC_OPERATION_DISABLE              = 0x00000000, /*!< xmc ecc module disable */
  XMC_ECC_OPERATION_ENABLE               = 0x00000040  /*!< xmc ecc module enable */
} xmc_ecc_enable_type;

/**
  * @brief xmc nor/sram subbank type
  */
typedef enum
{
  XMC_BANK1_NOR_SRAM1                    = 0x00000000, /*!< xmc nor/sram subbank1 */
  XMC_BANK1_NOR_SRAM2                    = 0x00000001, /*!< xmc nor/sram subbank2 */
  XMC_BANK1_NOR_SRAM3                    = 0x00000002, /*!< xmc nor/sram subbank3 */
  XMC_BANK1_NOR_SRAM4                    = 0x00000003  /*!< xmc nor/sram subbank4 */
} xmc_nor_sram_subbank_type;

/**
  * @brief xmc class bank type
  */
typedef enum
{
  XMC_BANK2_NAND                         = 0x00000000, /*!< xmc nand flash bank2 */
  XMC_BANK3_NAND                         = 0x00000001, /*!< xmc nand flash bank3 */
  XMC_BANK4_PCCARD                       = 0x00000002, /*!< xmc pc card bank4 */
  XMC_BANK5_6_SDRAM                      = 0x00000003  /*!< xmc sdram bank5/6 */
} xmc_class_bank_type;

/**
  * @brief xmc memory type
  */
typedef enum
{
  XMC_DEVICE_SRAM                        = 0x00000000, /*!< xmc device choice sram */
  XMC_DEVICE_PSRAM                       = 0x00000004, /*!< xmc device choice psram */
  XMC_DEVICE_NOR                         = 0x00000008  /*!< xmc device choice nor flash */
} xmc_memory_type;

/**
  * @brief xmc data width type
  */
typedef enum
{
  XMC_BUSTYPE_8_BITS                     = 0x00000000, /*!< xmc databuss width 8bits */
  XMC_BUSTYPE_16_BITS                    = 0x00000010  /*!< xmc databuss width 16bits */
} xmc_data_width_type;

/**
  * @brief xmc wait signal polarity type
  */
typedef enum
{
  XMC_WAIT_SIGNAL_LEVEL_LOW              = 0x00000000, /*!< xmc nwait active low */
  XMC_WAIT_SIGNAL_LEVEL_HIGH             = 0x00000200  /*!< xmc nwait active high */
} xmc_wait_signal_polarity_type;

/**
  * @brief xmc wait timing type
  */
typedef enum
{
  XMC_WAIT_SIGNAL_SYN_BEFORE             = 0x00000000, /*!< xmc nwait signal is active one data cycle before wait state */
  XMC_WAIT_SIGNAL_SYN_DURING             = 0x00000800  /*!< xmc nwait signal is active during wait state */
} xmc_wait_timing_type;

/**
  * @brief xmc access mode type
  */
typedef enum
{
  XMC_ACCESS_MODE_A                      = 0x00000000, /*!< xmc access mode A */
  XMC_ACCESS_MODE_B                      = 0x10000000, /*!< xmc access mode B */
  XMC_ACCESS_MODE_C                      = 0x20000000, /*!< xmc access mode C */
  XMC_ACCESS_MODE_D                      = 0x30000000  /*!< xmc access mode D */
} xmc_access_mode_type;

/**
  * @brief xmc ecc page size type
  */
typedef enum
{
  XMC_ECC_PAGESIZE_256_BYTES             = 0x00000000, /*!< xmc ecc page size 256 bytes */
  XMC_ECC_PAGESIZE_512_BYTES             = 0x00020000, /*!< xmc ecc page size 512 bytes */
  XMC_ECC_PAGESIZE_1024_BYTES            = 0x00040000, /*!< xmc ecc page size 1024 bytes */
  XMC_ECC_PAGESIZE_2048_BYTES            = 0x00060000, /*!< xmc ecc page size 2048 bytes */
  XMC_ECC_PAGESIZE_4096_BYTES            = 0x00080000, /*!< xmc ecc page size 4096 bytes */
  XMC_ECC_PAGESIZE_8192_BYTES            = 0x000A0000  /*!< xmc ecc page size 8192 bytes */
} xmc_ecc_pagesize_type;

/**
  * @brief xmc interrupt sources type
  */
typedef enum
{
  XMC_INT_RISING_EDGE                    = 0x00000008, /*!< xmc rising edge detection interrupt enable */
  XMC_INT_LEVEL                          = 0x00000010, /*!< xmc high-level edge detection interrupt enable */
  XMC_INT_FALLING_EDGE                   = 0x00000020, /*!< xmc falling edge detection interrupt enable */
  XMC_INT_ERR                            = 0x00004000  /*!< xmc sdram error interrupt enable */
} xmc_interrupt_sources_type;

/**
  * @brief xmc interrupt flag type
  */
typedef enum
{
  XMC_RISINGEDGE_FLAG                    = 0x00000001, /*!< xmc interrupt rising edge detection flag */
  XMC_LEVEL_FLAG                         = 0x00000002, /*!< xmc interrupt high-level edge detection flag */
  XMC_FALLINGEDGE_FLAG                   = 0x00000004, /*!< xmc interrupt falling edge detection flag */
  XMC_FEMPT_FLAG                         = 0x00000040, /*!< xmc fifo empty flag */
  XMC_ERR_FLAG                           = 0x00000001, /*!< xmc sdram error flag */
  XMC_BUSY_FLAG                          = 0x00000020  /*!< xmc sdram busy flag */
} xmc_interrupt_flag_type;

/**
  * @brief xmc sdram number of column address type
  */
typedef enum
{
  XMC_COLUMN_8                           = 0x00000000, /*!< xmc sdram column address 8bit */
  XMC_COLUMN_9                           = 0x00000001, /*!< xmc sdram column address 9bit */
  XMC_COLUMN_10                          = 0x00000002, /*!< xmc sdram column address 10bit */
  XMC_COLUMN_11                          = 0x00000003  /*!< xmc sdram column address 11bit */
}xmc_sdram_column_type;

/**
  * @brief xmc sdram number of row address type
  */
typedef enum
{
  XMC_ROW_11                             = 0x00000000, /*!< xmc sdram row address 11bit */
  XMC_ROW_12                             = 0x00000001, /*!< xmc sdram row address 12bit */
  XMC_ROW_13                             = 0x00000002  /*!< xmc sdram row address 13bit */
}xmc_sdram_row_type;

/**
  * @brief xmc sdram memory data bus width type
  */
typedef enum
{
  XMC_MEM_WIDTH_8                        = 0x00000000, /*!< xmc sdram data bus width 8 */
  XMC_MEM_WIDTH_16                       = 0x00000001  /*!< xmc sdram data bus width 16 */
}xmc_sdram_width_type;

/**
  * @brief xmc sdram number of internal banks type
  */
typedef enum
{
  XMC_INBK_2                             = 0x00000000, /*!< xmc sdram 2 internal banks */
  XMC_INBK_4                             = 0x00000001  /*!< xmc sdram 4 internal banks */
}xmc_sdram_inbk_type;

/**
  * @brief xmc sdram cas latency type
  */
typedef enum
{
  XMC_CAS_1                              = 0x00000001, /*!< xmc sdram cas 1 */
  XMC_CAS_2                              = 0x00000002, /*!< xmc sdram cas 2 */
  XMC_CAS_3                              = 0x00000003  /*!< xmc sdram cas 3 */
}xmc_sdram_cas_type;

/**
  * @brief xmc sdram clock div type
  */
typedef enum
{
  XMC_NO_CLK                             = 0x00000000, /*!< xmc sdram disable clock */
  XMC_CLKDIV_2                           = 0x00000002, /*!< xmc sdram clock div 2 */
  XMC_CLKDIV_3                           = 0x00000003, /*!< xmc sdram clock div 3 */
  XMC_CLKDIV_4                           = 0x00000001  /*!< xmc sdram clock div 4 */
}xmc_sdram_clkdiv_type;

/**
  * @brief xmc sdram read delay
  */
typedef enum
{
  XMC_READ_DELAY_0                       = 0x00000000, /*!< xmc sdram no delay */
  XMC_READ_DELAY_1                       = 0x00000001, /*!< xmc sdram delay 1 clock*/
  XMC_READ_DELAY_2                       = 0x00000002, /*!< xmc sdram delay 2 clock */
}xmc_sdram_rd_delay_type;

/**
  * @brief xmc sdram bank type
  */
typedef enum
{
  XMC_SDRAM_BANK1                        = 0x00000000, /*!< xmc sdram bank 1 */
  XMC_SDRAM_BANK2                        = 0x00000001  /*!< xmc sdram bank 2 */
}xmc_sdram_bank_type;


/**
  * @brief xmc sdram timing delay cycle type
  */
typedef enum
{
  XMC_DELAY_CYCLE_1                      = 0x00000000, /*!< xmc sdram timming delay 1 cycle */
  XMC_DELAY_CYCLE_2                      = 0x00000001, /*!< xmc sdram timming delay 2 cycle */
  XMC_DELAY_CYCLE_3                      = 0x00000002, /*!< xmc sdram timming delay 3 cycle */
  XMC_DELAY_CYCLE_4                      = 0x00000003, /*!< xmc sdram timming delay 4 cycle */
  XMC_DELAY_CYCLE_5                      = 0x00000004, /*!< xmc sdram timming delay 5 cycle */
  XMC_DELAY_CYCLE_6                      = 0x00000005, /*!< xmc sdram timming delay 6 cycle */
  XMC_DELAY_CYCLE_7                      = 0x00000006, /*!< xmc sdram timming delay 7 cycle */
  XMC_DELAY_CYCLE_8                      = 0x00000007, /*!< xmc sdram timming delay 8 cycle */
  XMC_DELAY_CYCLE_9                      = 0x00000008, /*!< xmc sdram timming delay 9 cycle */
  XMC_DELAY_CYCLE_10                     = 0x00000009, /*!< xmc sdram timming delay 10 cycle */
  XMC_DELAY_CYCLE_11                     = 0x0000000A, /*!< xmc sdram timming delay 11 cycle */
  XMC_DELAY_CYCLE_12                     = 0x0000000B, /*!< xmc sdram timming delay 12 cycle */
  XMC_DELAY_CYCLE_13                     = 0x0000000C, /*!< xmc sdram timming delay 13 cycle */
  XMC_DELAY_CYCLE_14                     = 0x0000000D, /*!< xmc sdram timming delay 14 cycle */
  XMC_DELAY_CYCLE_15                     = 0x0000000E, /*!< xmc sdram timming delay 15 cycle */
  XMC_DELAY_CYCLE_16                     = 0x0000000F  /*!< xmc sdram timming delay 16 cycle */
}xmc_sdram_delay_type;


/**
  * @brief xmc sdram command type
  */
typedef enum
{
  XMC_CMD_NORMAL                         = 0x00000000, /*!< xmc sdram command normal */
  XMC_CMD_CLK                            = 0x00000001, /*!< xmc sdram command clock enable */
  XMC_CMD_PRECHARG_ALL                   = 0x00000002, /*!< xmc sdram command precharg all bank */
  XMC_CMD_AUTO_REFRESH                   = 0x00000003, /*!< xmc sdram command auto refresh */
  XMC_CMD_LOAD_MODE                      = 0x00000004, /*!< xmc sdram command load mode register */
  XMC_CMD_SELF_REFRESH                   = 0x00000005, /*!< xmc sdram command self refresh */
  XMC_CMD_POWER_DOWN                     = 0x00000006  /*!< xmc sdram command power down */
}xmc_command_type;

/**
  * @brief xmc sdram command bank select type
  */
typedef enum
{
  XMC_CMD_BANK1                          = 0x00000010, /*!< send xmc sdram command to bank1 */
  XMC_CMD_BANK2                          = 0x00000008, /*!< send xmc sdram command to bank2 */
  XMC_CMD_BANK1_2                        = 0x00000018  /*!< send xmc sdram command to bank1 and bank2 */
}xmc_cmd_bank1_2_type;


/**
  * @brief xmc sdram bank status type
  */
typedef enum
{
  XMC_STATUS_NORMAL                      = 0x00000000, /*!< xmc sdram status normal */
  XMC_STATUS_SELF_REFRESH                = 0x00000001, /*!< xmc sdram status self refresh */
  XMC_STATUS_POWER_DOWN                  = 0x00000002, /*!< xmc sdram power down */
  XMC_STATUS_MASK                        = 0x00000003  /*!< xmc sdram mask */
}xmc_bank_status_type;


/**
  * @brief   nor/sram banks timing parameters
  */
typedef struct
{
  xmc_nor_sram_subbank_type              subbank;             /*!< xmc nor/sram subbank */
  xmc_extended_mode_type                 write_timing_enable; /*!< xmc nor/sram write timing enable */
  uint32_t                               addr_setup_time;     /*!< xmc nor/sram address setup time */
  uint32_t                               addr_hold_time;      /*!< xmc nor/sram address hold time */
  uint32_t                               data_setup_time;     /*!< xmc nor/sram data setup time */
  uint32_t                               bus_latency_time;    /*!< xmc nor/sram bus latency time */
  uint32_t                               clk_psc;             /*!< xmc nor/sram clock prescale */
  uint32_t                               data_latency_time;   /*!< xmc nor/sram data latency time */
  xmc_access_mode_type                   mode;                /*!< xmc nor/sram access mode */
} xmc_norsram_timing_init_type;

/**
  * @brief  xmc nor/sram init structure definition
  */
typedef struct
{
  xmc_nor_sram_subbank_type              subbank;             /*!< xmc nor/sram subbank */
  xmc_data_addr_mux_type                 data_addr_multiplex; /*!< xmc nor/sram address/data multiplexing enable */
  xmc_memory_type                        device;              /*!< xmc nor/sram memory device */
  xmc_data_width_type                    bus_type;            /*!< xmc nor/sram data bus width */
  xmc_burst_access_mode_type             burst_mode_enable;   /*!< xmc nor/sram burst mode enable */
  xmc_asyn_wait_type                     asynwait_enable;     /*!< xmc nor/sram nwait in asynchronous transfer enable */
  xmc_wait_signal_polarity_type          wait_signal_lv;      /*!< xmc nor/sram nwait polarity */
  xmc_wrap_mode_type                     wrapped_mode_enable; /*!< xmc nor/sram wrapped enable */
  xmc_wait_timing_type                   wait_signal_config;  /*!< xmc nor/sram nwait timing configuration */
  xmc_write_operation_type               write_enable;        /*!< xmc nor/sram write enable */
  xmc_wait_signal_type                   wait_signal_enable;  /*!< xmc nor/sram nwait in synchronous transfer enable */
  xmc_extended_mode_type                 write_timing_enable; /*!< xmc nor/sram read-write timing different */
  xmc_write_burst_type                   write_burst_syn;     /*!< xmc nor/sram memory write mode control */
} xmc_norsram_init_type;

/**
  * @brief  nand and pccard timing parameters xmc
  */

typedef struct
{
  xmc_class_bank_type                    class_bank;     /*!< xmc nand/pccard bank */
  uint32_t                               mem_setup_time; /*!< xmc nand/pccard memory setup time */
  uint32_t                               mem_waite_time; /*!< xmc nand/pccard memory wait time */
  uint32_t                               mem_hold_time;  /*!< xmc nand/pccard memory hold time */
  uint32_t                               mem_hiz_time;   /*!< xmc nand/pccard memory databus high resistance time */
} xmc_nand_pccard_timinginit_type;

/**
  * @brief  xmc nand init structure definition
  */

typedef struct
{
  xmc_class_bank_type                    nand_bank;        /*!< xmc nand bank */
  xmc_nand_pccard_wait_type              wait_enable;      /*!< xmc wait feature enable */
  xmc_data_width_type                    bus_type;         /*!< xmc nand bus width */
  xmc_ecc_enable_type                    ecc_enable;       /*!< xmc nand ecc enable */
  xmc_ecc_pagesize_type                  ecc_pagesize;     /*!< xmc nand ecc page size */
  uint32_t                               delay_time_cycle; /*!< xmc nand cle to re delay */
  uint32_t                               delay_time_ar;    /*!< xmc nand ale to re delay */
} xmc_nand_init_type;

/**
  * @brief  xmc pccard init structure definition
  */

typedef struct
{
  xmc_nand_pccard_wait_type              enable_wait;   /*!< xmc pccard wait feature enable */
  uint32_t                               delay_time_cr; /*!< xmc pccard cle to re delay */
  uint32_t                               delay_time_ar; /*!< xmc pccard ale to re delay */
} xmc_pccard_init_type;

/**
  * @brief  xmc sdram init structure definition
  */

typedef struct
{
  xmc_sdram_bank_type                    sdram_bank;       /*!< xmc sdram bank bype */
  xmc_sdram_inbk_type                    internel_banks;   /*!< xmc sdram internal banks */
  xmc_sdram_clkdiv_type                  clkdiv;           /*!< xmc sdram clock div */
  uint8_t                                write_protection; /*!< xmc sdram write protection */
  uint8_t                                burst_read;       /*!< xmc sdram burst read */
  uint8_t                                read_delay;       /*!< xmc sdram read delay */
  xmc_sdram_column_type                  column_address;   /*!< xmc sdram column address */
  xmc_sdram_row_type                     row_address;      /*!< xmc sdram row address */
  xmc_sdram_cas_type                     cas;              /*!< xmc sdram cas */
  xmc_sdram_width_type                   width;            /*!< xmc sdram data width */
} xmc_sdram_init_type;

/**
  * @brief  xmc sdram timing structure definition
  */

typedef struct
{
  xmc_sdram_delay_type                   tmrd; /*!< mode register program to active delay  */
  xmc_sdram_delay_type                   txsr; /*!< exit self-refresh to active delay */
  xmc_sdram_delay_type                   tras; /*!< self refresh  */
  xmc_sdram_delay_type                   trc;  /*!< refresh to active delay */
  xmc_sdram_delay_type                   twr;  /*!< write recovery delay */
  xmc_sdram_delay_type                   trp;  /*!< precharge to active delay */
  xmc_sdram_delay_type                   trcd; /*!< row active to read/write delay */
} xmc_sdram_timing_type;

/**
  * @brief  xmc sdram command structure definition
  */

typedef struct
{
  xmc_command_type                       cmd;          /*!< sdram command */
  xmc_cmd_bank1_2_type                   cmd_banks;    /*!< which bank send command */
  uint32_t                               auto_refresh; /*!< auto refresh times */
  uint32_t                               data;         /*!< mode register data */
} xmc_sdram_cmd_type;

typedef struct
{
  /**
    * @brief xmc bank1 bk1ctrl register, offset:0x00+0x08*(x-1) x= 1...4
    */
  union
  {
    __IO uint32_t bk1ctrl;
    struct
    {
      __IO uint32_t en                   : 1; /* [0] */
      __IO uint32_t admuxen              : 1; /* [1] */
      __IO uint32_t dev                  : 2; /* [3:2] */
      __IO uint32_t extmdbw              : 2; /* [5:4] */
      __IO uint32_t noren                : 1; /* [6] */
      __IO uint32_t reserved1            : 1; /* [7] */
      __IO uint32_t syncben              : 1; /* [8] */
      __IO uint32_t nwpol                : 1; /* [9] */
      __IO uint32_t wrapen               : 1; /* [10] */
      __IO uint32_t nwtcfg               : 1; /* [11] */
      __IO uint32_t wen                  : 1; /* [12] */
      __IO uint32_t nwsen                : 1; /* [13] */
      __IO uint32_t rwtd                 : 1; /* [14] */
      __IO uint32_t nwasen               : 1; /* [15] */
      __IO uint32_t crpgs                : 3; /* [18:16] */
      __IO uint32_t mwmc                 : 1; /* [19] */
      __IO uint32_t reserved2            : 12;/* [31:20] */
    } bk1ctrl_bit;
  };

  /**
    * @brief xmc bank1 bk1tmg register, offset:0x04+0x08*(x-1) x= 1...4
    */
  union
  {
    __IO uint32_t bk1tmg;
    struct
    {
      __IO uint32_t addrst               : 4; /* [3:0] */
      __IO uint32_t addrht               : 4; /* [7:4] */
      __IO uint32_t dtst                 : 8; /* [15:8] */
      __IO uint32_t buslat               : 4; /* [19:16] */
      __IO uint32_t clkpsc               : 4; /* [23:20] */
      __IO uint32_t dtlat                : 4; /* [27:24] */
      __IO uint32_t asyncm               : 2; /* [29:28] */
      __IO uint32_t reserved1            : 2; /* [31:30] */
    } bk1tmg_bit;
  };

} xmc_bank1_ctrl_tmg_reg_type;

typedef struct
{
  /**
    * @brief xmc bank1 bk1tmgwr register, offset:0x104+0x08*(x-1) x= 1...4
    */
  union
  {
    __IO uint32_t bk1tmgwr;
    struct
    {
      __IO uint32_t addrst               : 4; /* [3:0] */
      __IO uint32_t addrht               : 4; /* [7:4] */
      __IO uint32_t dtst                 : 8; /* [15:8] */
      __IO uint32_t buslat               : 4; /* [19:16] */
      __IO uint32_t reserved1            : 8; /* [27:20] */
      __IO uint32_t asyncm               : 2; /* [29:28] */
      __IO uint32_t reserved2            : 2; /* [31:30] */
    } bk1tmgwr_bit;
  };

  /**
    * @brief xmc bank1 reserved register
    */
  __IO uint32_t reserved1;

} xmc_bank1_tmgwr_reg_type;

/**
  * @brief xmc bank1 registers
  */
typedef struct
{
  /**
    * @brief xmc bank1 ctrl and tmg register, offset:0x00~0x1C
    */
  xmc_bank1_ctrl_tmg_reg_type ctrl_tmg_group[4];

  /**
    * @brief xmc bank1 reserved register, offset:0x20~0x100
    */
  __IO uint32_t reserved1[57];

 /**
    * @brief xmc bank1 tmgwr register, offset:0x104~0x11C
    */
  xmc_bank1_tmgwr_reg_type tmgwr_group[4];

  /**
    * @brief xmc bank1 reserved register, offset:0x120~0x220
    */
  __IO uint32_t reserved2[63];

  /**
    * @brief xmc bank1 ext register, offset:0x220~0x22C
    */
  union
  {
    __IO uint32_t ext[4];
    struct
    {
      __IO uint32_t buslatw2w            : 8; /* [7:0] */
      __IO uint32_t buslatr2r            : 8; /* [15:8] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } ext_bit[4];
  };

} xmc_bank1_type;

/**
  * @brief xmc bank2 registers
  */
typedef struct
{
  /**
    * @brief xmc bk2ctrl register, offset:0x60
    */
  union
  {
    __IO uint32_t bk2ctrl;
    struct
    {
      __IO uint32_t reserved1            : 1; /* [0] */
      __IO uint32_t nwen                 : 1; /* [1] */
      __IO uint32_t en                   : 1; /* [2] */
      __IO uint32_t dev                  : 1; /* [3] */
      __IO uint32_t extmdbw              : 2; /* [5:4] */
      __IO uint32_t eccen                : 1; /* [6] */
      __IO uint32_t reserved2            : 2; /* [8:7] */
      __IO uint32_t tcr                  : 4; /* [12:9] */
      __IO uint32_t tar                  : 4; /* [16:13] */
      __IO uint32_t eccpgs               : 3; /* [19:17] */
      __IO uint32_t reserved3            : 12;/* [31:20] */
    } bk2ctrl_bit;
  };

  /**
    * @brief xmc bk2is register, offset:0x64
    */
  union
  {
    __IO uint32_t bk2is;
    struct
    {
      __IO uint32_t res                  : 1; /* [0] */
      __IO uint32_t hls                  : 1; /* [1] */
      __IO uint32_t fes                  : 1; /* [2] */
      __IO uint32_t reien                : 1; /* [3] */
      __IO uint32_t hlien                : 1; /* [4] */
      __IO uint32_t feien                : 1; /* [5] */
      __IO uint32_t fifoe                : 1; /* [6] */
      __IO uint32_t reserved1            : 25;/* [31:7] */
    } bk2is_bit;
  };

  /**
  * @brief xmc bk2tmgmem register, offset:0x68
  */
  union
  {
    __IO uint32_t bk2tmgmem;
    struct
    {
      __IO uint32_t cmst                 : 8; /* [7:0] */
      __IO uint32_t cmwt                 : 8; /* [15:8] */
      __IO uint32_t cmht                 : 8; /* [23:16] */
      __IO uint32_t cmdhizt              : 8; /* [31:24] */
    } bk2tmgmem_bit;
  };

  /**
  * @brief xmc bk2tmgatt register, offset:0x6C
  */
  union
  {
    __IO uint32_t bk2tmgatt;
    struct
    {
      __IO uint32_t amst                 : 8; /* [7:0] */
      __IO uint32_t amwt                 : 8; /* [15:8] */
      __IO uint32_t amht                 : 8; /* [23:16] */
      __IO uint32_t amdhizt              : 8; /* [31:24] */
    } bk2tmgatt_bit;
  };

  /**
  * @brief xmc reserved register, offset:0x70
  */
  __IO uint32_t reserved1;

  /**
  * @brief xmc bk2ecc register, offset:0x74
  */
  union
  {
    __IO uint32_t bk2ecc;
    struct
    {
      __IO uint32_t ecc                  : 32; /* [31:0] */
    } bk2ecc_bit;
  };

} xmc_bank2_type;

/**
  * @brief xmc bank3 registers
  */
typedef struct
{
  /**
    * @brief xmc bk3ctrl register, offset:0x80
    */
  union
  {
    __IO uint32_t bk3ctrl;
    struct
    {
      __IO uint32_t reserved1            : 1; /* [0] */
      __IO uint32_t nwen                 : 1; /* [1] */
      __IO uint32_t en                   : 1; /* [2] */
      __IO uint32_t dev                  : 1; /* [3] */
      __IO uint32_t extmdbw              : 2; /* [5:4] */
      __IO uint32_t eccen                : 1; /* [6] */
      __IO uint32_t reserved2            : 2; /* [8:7] */
      __IO uint32_t tcr                  : 4; /* [12:9] */
      __IO uint32_t tar                  : 4; /* [16:13] */
      __IO uint32_t eccpgs               : 3; /* [19:17] */
      __IO uint32_t reserved3            : 12;/* [31:20] */
    } bk3ctrl_bit;
  };

  /**
    * @brief xmc bk3is register, offset:0x84
    */
  union
  {
    __IO uint32_t bk3is;
    struct
    {
      __IO uint32_t res                  : 1; /* [0] */
      __IO uint32_t hls                  : 1; /* [1] */
      __IO uint32_t fes                  : 1; /* [2] */
      __IO uint32_t reien                : 1; /* [3] */
      __IO uint32_t hlien                : 1; /* [4] */
      __IO uint32_t feien                : 1; /* [5] */
      __IO uint32_t fifoe                : 1; /* [6] */
      __IO uint32_t reserved1            : 25;/* [31:7] */
    } bk3is_bit;
  };

  /**
  * @brief xmc bk3tmgmem register, offset:0x88
  */
  union
  {
    __IO uint32_t bk3tmgmem;
    struct
    {
      __IO uint32_t cmst                 : 8; /* [7:0] */
      __IO uint32_t cmwt                 : 8; /* [15:8] */
      __IO uint32_t cmht                 : 8; /* [23:16] */
      __IO uint32_t cmdhizt              : 8; /* [31:24] */
    } bk3tmgmem_bit;
  };

  /**
  * @brief xmc bk3tmgatt register, offset:0x8C
  */
  union
  {
    __IO uint32_t bk3tmgatt;
    struct
    {
      __IO uint32_t amst                 : 8; /* [7:0] */
      __IO uint32_t amwt                 : 8; /* [15:8] */
      __IO uint32_t amht                 : 8; /* [23:16] */
      __IO uint32_t amdhizt              : 8; /* [31:24] */
    } bk3tmgatt_bit;
  };

  /**
  * @brief xmc reserved register, offset:0x90
  */
  __IO uint32_t reserved1;

  /**
  * @brief xmc bk3ecc register, offset:0x94
  */
  union
  {
    __IO uint32_t bk3ecc;
    struct
    {
      __IO uint32_t ecc                  : 32; /* [31:0] */
    } bk3ecc_bit;
  };
} xmc_bank3_type;

/**
  * @brief xmc bank4 registers
  */
typedef struct
{

  /**
    * @brief xmc bk4ctrl register, offset:0xA0
    */
  union
  {
    __IO uint32_t bk4ctrl;
    struct
    {
      __IO uint32_t reserved1            : 1; /* [0] */
      __IO uint32_t nwen                 : 1; /* [1] */
      __IO uint32_t en                   : 1; /* [2] */
      __IO uint32_t dev                  : 1; /* [3] */
      __IO uint32_t extmdbw              : 2; /* [5:4] */
      __IO uint32_t eccen                : 1; /* [6] */
      __IO uint32_t reserved2            : 2; /* [8:7] */
      __IO uint32_t tcr                  : 4; /* [12:9] */
      __IO uint32_t tar                  : 4; /* [16:13] */
      __IO uint32_t eccpgs               : 3; /* [19:17] */
      __IO uint32_t reserved3            : 12;/* [31:20] */
    } bk4ctrl_bit;
  };

  /**
    * @brief xmc bk4is register, offset:0xA4
    */
  union
  {
    __IO uint32_t bk4is;
    struct
    {
      __IO uint32_t res                  : 1; /* [0] */
      __IO uint32_t hls                  : 1; /* [1] */
      __IO uint32_t fes                  : 1; /* [2] */
      __IO uint32_t reien                : 1; /* [3] */
      __IO uint32_t hlien                : 1; /* [4] */
      __IO uint32_t feien                : 1; /* [5] */
      __IO uint32_t fifoe                : 1; /* [6] */
      __IO uint32_t reserved1            : 25;/* [31:7] */
    } bk4is_bit;
  };

  /**
  * @brief xmc bk4tmgmem register, offset:0xA8
  */
  union
  {
    __IO uint32_t bk4tmgmem;
    struct
    {
      __IO uint32_t cmst                 : 8; /* [7:0] */
      __IO uint32_t cmwt                 : 8; /* [15:8] */
      __IO uint32_t cmht                 : 8; /* [23:16] */
      __IO uint32_t cmdhizt              : 8; /* [31:24] */
    } bk4tmgmem_bit;
  };

  /**
  * @brief xmc bk4tmgatt register, offset:0xAC
  */
  union
  {
    __IO uint32_t bk4tmgatt;
    struct
    {
      __IO uint32_t amst                 : 8; /* [7:0] */
      __IO uint32_t amwt                 : 8; /* [15:8] */
      __IO uint32_t amht                 : 8; /* [23:16] */
      __IO uint32_t amdhizt              : 8; /* [31:24] */
    } bk4tmgatt_bit;
  };

  /**
  * @brief xmc bk4tmgio register, offset:0xB0
  */
  union
  {
    __IO uint32_t bk4tmgio;
    struct
    {
      __IO uint32_t iost                 : 8; /* [7:0] */
      __IO uint32_t iowt                 : 8; /* [15:8] */
      __IO uint32_t ioht                 : 8; /* [23:16] */
      __IO uint32_t iohizt               : 8; /* [31:24] */
    } bk4tmgio_bit;
  };
} xmc_bank4_type;

/**
  * @brief xmc sdram type
  */
typedef struct
{
  /**
    * @brief xmc sdram ctrl register, offset:0x140~0x144
    */
  union
  {
    __IO uint32_t ctrl[2];
    struct
    {
      __IO uint32_t ca                   : 2; /* [1:0] */
      __IO uint32_t ra                   : 2; /* [3:2] */
      __IO uint32_t db                   : 2; /* [5:4] */
      __IO uint32_t inbk                 : 1; /* [6] */
      __IO uint32_t cas                  : 2; /* [8:7] */
      __IO uint32_t wrp                  : 1; /* [9] */
      __IO uint32_t clkdiv               : 2; /* [11:10] */
      __IO uint32_t bstr                 : 1; /* [12] */
      __IO uint32_t rd                   : 2; /* [14:13] */
      __IO uint32_t reserved1            : 17;/* [31:15] */
    } ctrl_bit[2];
  };

  /**
    * @brief xmc sdram tm register, offset:0x148~0x14C
    */
  union
  {
    __IO uint32_t tm[2];
    struct
    {
      __IO uint32_t tmrd                 : 4; /* [3:0] */
      __IO uint32_t txsr                 : 4; /* [7:4] */
      __IO uint32_t tras                 : 4; /* [11:8] */
      __IO uint32_t trc                  : 4; /* [15:12] */
      __IO uint32_t twr                  : 4; /* [19:16] */
      __IO uint32_t trp                  : 4; /* [23:20] */
      __IO uint32_t trcd                 : 4; /* [27:24] */
      __IO uint32_t reserved1            : 4; /* [31:28] */
    } tm_bit[2];

  };

/**
    * @brief xmc sdram cmd register, offset:0x150
    */
  union
  {
    __IO uint32_t cmd;
    struct
    {
      __IO uint32_t cmd                  : 3; /* [2:0] */
      __IO uint32_t bk2                  : 1; /* [3] */
      __IO uint32_t bk1                  : 1; /* [4] */
      __IO uint32_t art                  : 4; /* [8:5] */
      __IO uint32_t mrd                  : 13;/* [21:9] */
      __IO uint32_t reserved1            : 10;/* [31:22] */
    } cmd_bit;
  };

  /**
    * @brief xmc sdram rcnt register, offset:0x154
    */
  union
  {
    __IO uint32_t rcnt;
    struct
    {
      __IO uint32_t errc                 : 1; /* [0] */
      __IO uint32_t rc                   : 13;/* [13:1] */
      __IO uint32_t erien                : 1; /* [14] */
      __IO uint32_t reserved1            : 17;/* [31:15] */
    } rcnt_bit;
  };

  /**
    * @brief xmc sdram sts register, offset:0x158
    */
  union
  {
    __IO uint32_t sts;
    struct
    {
      __IO uint32_t err                  : 1; /* [0] */
      __IO uint32_t bk1sts               : 2; /* [2:1] */
      __IO uint32_t bk2sts               : 2; /* [4:3] */
      __IO uint32_t busy                 : 1; /* [5] */
      __IO uint32_t reserved1            : 26;/* [31:6] */
    } sts_bit;
  };
}xmc_sdram_type;

/**
  * @}
  */

#define XMC_BANK1                        ((xmc_bank1_type *) XMC_BANK1_REG_BASE)
#define XMC_BANK2                        ((xmc_bank2_type *) XMC_BANK2_REG_BASE)
#define XMC_BANK3                        ((xmc_bank3_type *) XMC_BANK3_REG_BASE)
#define XMC_BANK4                        ((xmc_bank4_type *) XMC_BANK4_REG_BASE)
#define XMC_SDRAM                        ((xmc_sdram_type *) XMC_SDRAM_REG_BASE)

/** @defgroup XMC_exported_functions
  * @{
  */

void xmc_nor_sram_reset(xmc_nor_sram_subbank_type xmc_subbank);
void xmc_nor_sram_init(xmc_norsram_init_type* xmc_norsram_init_struct);
void xmc_nor_sram_timing_config(xmc_norsram_timing_init_type* xmc_rw_timing_struct,
                                xmc_norsram_timing_init_type* xmc_w_timing_struct);
void xmc_norsram_default_para_init(xmc_norsram_init_type* xmc_nor_sram_init_struct);
void xmc_norsram_timing_default_para_init(xmc_norsram_timing_init_type* xmc_rw_timing_struct,
                                          xmc_norsram_timing_init_type* xmc_w_timing_struct);
void xmc_nor_sram_enable(xmc_nor_sram_subbank_type xmc_subbank, confirm_state new_state);
void xmc_ext_timing_config(volatile xmc_nor_sram_subbank_type xmc_sub_bank, uint16_t w2w_timing, uint16_t r2r_timing);
void xmc_nand_reset(xmc_class_bank_type xmc_bank);
void xmc_nand_init(xmc_nand_init_type* xmc_nand_init_struct);
void xmc_nand_timing_config(xmc_nand_pccard_timinginit_type* xmc_common_spacetiming_struct,
                            xmc_nand_pccard_timinginit_type* xmc_attribute_spacetiming_struct);
void xmc_nand_default_para_init(xmc_nand_init_type* xmc_nand_init_struct);
void xmc_nand_timing_default_para_init(xmc_nand_pccard_timinginit_type* xmc_common_spacetiming_struct,
                                       xmc_nand_pccard_timinginit_type* xmc_attribute_spacetiming_struct);
void xmc_nand_enable(xmc_class_bank_type xmc_bank, confirm_state new_state);
void xmc_nand_ecc_enable(xmc_class_bank_type xmc_bank, confirm_state new_state);
uint32_t xmc_ecc_get(xmc_class_bank_type xmc_bank);
void xmc_interrupt_enable(xmc_class_bank_type xmc_bank, xmc_interrupt_sources_type xmc_int, confirm_state new_state);
flag_status xmc_flag_status_get(xmc_class_bank_type xmc_bank, xmc_interrupt_flag_type xmc_flag);
flag_status xmc_interrupt_flag_status_get(xmc_class_bank_type xmc_bank, xmc_interrupt_flag_type xmc_flag);
void xmc_flag_clear(xmc_class_bank_type xmc_bank, xmc_interrupt_flag_type xmc_flag);
void xmc_pccard_reset(void);
void xmc_pccard_init(xmc_pccard_init_type* xmc_pccard_init_struct);
void xmc_pccard_timing_config(xmc_nand_pccard_timinginit_type* xmc_common_spacetiming_struct,
                              xmc_nand_pccard_timinginit_type* xmc_attribute_spacetiming_struct,
                              xmc_nand_pccard_timinginit_type* xmc_iospace_timing_struct);
void xmc_pccard_default_para_init(xmc_pccard_init_type* xmc_pccard_init_struct);
void xmc_pccard_timing_default_para_init(xmc_nand_pccard_timinginit_type* xmc_common_spacetiming_struct,
                                         xmc_nand_pccard_timinginit_type* xmc_attribute_spacetiming_struct,
                                         xmc_nand_pccard_timinginit_type* xmc_iospace_timing_struct);
void xmc_pccard_enable(confirm_state new_state);
void xmc_sdram_reset(xmc_sdram_bank_type xmc_bank);
void xmc_sdram_init(xmc_sdram_init_type *xmc_sdram_init_struct, xmc_sdram_timing_type *xmc_sdram_timing_struct);
void xmc_sdram_default_para_init(xmc_sdram_init_type *xmc_sdram_init_struct, xmc_sdram_timing_type *xmc_sdram_timing_struct);
void xmc_sdram_cmd(xmc_sdram_cmd_type *xmc_sdram_cmd_struct);
uint32_t xmc_sdram_status_get(xmc_sdram_bank_type xmc_bank);
void xmc_sdram_refresh_counter_set(uint32_t counter);
void xmc_sdram_auto_refresh_set(uint32_t number);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
