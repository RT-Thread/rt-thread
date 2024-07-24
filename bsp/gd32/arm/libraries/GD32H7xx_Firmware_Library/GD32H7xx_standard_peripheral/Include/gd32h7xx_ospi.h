/*!
    \file    gd32h7xx_ospi.h
    \brief   definitions for the OSPI

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

#ifndef GD32H7XX_OSPI_H
#define GD32H7XX_OSPI_H

#include "gd32h7xx.h"

/* OSPI definitions */
#define OSPI0                             OSPI_BASE
#define OSPI1                             (OSPI_BASE + 0x00005000U)

/* registers definitions */
#define OSPI_CTL(ospix)                   REG32((ospix) + 0x00000000U)         /*!< OSPI control register */
#define OSPI_DCFG0(ospix)                 REG32((ospix) + 0x00000008U)         /*!< OSPI device configuration register */
#define OSPI_DCFG1(ospix)                 REG32((ospix) + 0x0000000CU)         /*!< OSPI device configuration register */
#define OSPI_STAT(ospix)                  REG32((ospix) + 0x00000020U)         /*!< OSPI status register */
#define OSPI_STATC(ospix)                 REG32((ospix) + 0x00000024U)         /*!< OSPI status clear register */
#define OSPI_DTLEN(ospix)                 REG32((ospix) + 0x00000040U)         /*!< OSPI data length register */
#define OSPI_ADDR(ospix)                  REG32((ospix) + 0x00000048U)         /*!< OSPI address register */
#define OSPI_DATA(ospix)                  REG32((ospix) + 0x00000050U)         /*!< OSPI data register */
#define OSPI_STATMK(ospix)                REG32((ospix) + 0x00000080U)         /*!< OSPI status mask register */
#define OSPI_STATMATCH(ospix)             REG32((ospix) + 0x00000088U)         /*!< OSPI status match register */
#define OSPI_INTERVAL(ospix)              REG32((ospix) + 0x00000090U)         /*!< OSPI interval register */
#define OSPI_TCFG(ospix)                  REG32((ospix) + 0x00000100U)         /*!< OSPI transfer configuration register */
#define OSPI_TIMCFG(ospix)                REG32((ospix) + 0x00000108U)         /*!< OSPI timing configuration register */
#define OSPI_INS(ospix)                   REG32((ospix) + 0x00000110U)         /*!< OSPI instruction register */
#define OSPI_ALTE(ospix)                  REG32((ospix) + 0x00000120U)         /*!< OSPI alternate bytes register */
#define OSPI_WPTCFG(ospix)                REG32((ospix) + 0x00000140U)         /*!< OSPI wrap transfer configuration register */
#define OSPI_WPTIMCFG(ospix)              REG32((ospix) + 0x00000148U)         /*!< OSPI wrap timing configuration register */
#define OSPI_WPINS(ospix)                 REG32((ospix) + 0x00000150U)         /*!< OSPI wrap instruction register */
#define OSPI_WPALTE(ospix)                REG32((ospix) + 0x00000160U)         /*!< OSPI wrap alternate bytes register */
#define OSPI_WTCFG(ospix)                 REG32((ospix) + 0x00000180U)         /*!< OSPI write transfer configuration register */
#define OSPI_WTIMCFG(ospix)               REG32((ospix) + 0x00000188U)         /*!< OSPI write timing configuration register */
#define OSPI_WINS(ospix)                  REG32((ospix) + 0x00000190U)         /*!< OSPI write instruction register */
#define OSPI_WALTE(ospix)                 REG32((ospix) + 0x000001A0U)         /*!< OSPI write alternate bytes register */

/* bits definitions */
/* OSPI_CTL */
#define OSPI_CTL_OSPIEN                   BIT(0)                               /*!< enable the quadspi */

#define OSPI_CTL_DMAEN                    BIT(2)                               /*!< dma enable */
#define OSPI_CTL_FTL                      BITS(8,12)                           /*!< fifo threshold level */
#define OSPI_CTL_TERRIE                   BIT(16)                              /*!< transfer error interrupt enable */
#define OSPI_CTL_TCIE                     BIT(17)                              /*!< transfer complete interrupt enable */
#define OSPI_CTL_FTIE                     BIT(18)                              /*!< fifo threshold interrupt enable */
#define OSPI_CTL_SMIE                     BIT(19)                              /*!< status match interrupt enable */
#define OSPI_CTL_SPS                      BIT(22)                              /*!< status polling mode stop */
#define OSPI_CTL_SPMOD                    BIT(23)                              /*!< status polling match mode */
#define OSPI_CTL_FMOD                     BITS(28,29)                          /*!< functional mode select */

/* OSPI_DCFG0 */
#define OSPI_DCFG0_CSHC                   BITS(8,13)                           /*!< chip select high cycle */
#define OSPI_DCFG0_MESZ                   BITS(16,20)                          /*!< memory size */
#define OSPI_DCFG0_DTYSEL                 BITS(24,26)                          /*!< select device type */

/* OSPI_DCFG1 */
#define OSPI_DCFG1_PSC                    BITS(0,7)                            /*!< prescaler set */
#define OSPI_DCFG1_WPSZ                   BITS(16,18)                          /*!< wrap size */

/* OSPI_STAT */
#define OSPI_STAT_TERR                    BIT(0)                               /*!< transfer error flag */
#define OSPI_STAT_TC                      BIT(1)                               /*!< transfer complete flag */
#define OSPI_STAT_FT                      BIT(2)                               /*!< fifo threshold flag */
#define OSPI_STAT_SM                      BIT(3)                               /*!< status match flag */
#define OSPI_STAT_BUSY                    BIT(5)                               /*!< busy flag */
#define OSPI_STAT_FL                      BITS(8,13)                           /*!< fifo level */

/* OSPI_STATC */
#define OSPI_STATC_TERRC                  BIT(0)                               /*!< clear transfer error flag */
#define OSPI_STATC_TCC                    BIT(1)                               /*!< clear transfer complete flag */
#define OSPI_STATC_SMC                    BIT(3)                               /*!< clear status match flag */

/* OSPI_DTLEN */
#define OSPI_DTLEN_DTLEN                  BITS(0,31)                           /*!< data length */

/* OSPI_ADDR */
#define OSPI_ADDR_ADDR                    BITS(0,31)                           /*!< address to be send to the external flash memory */

/* OSPI_DATA */
#define OSPI_DATA_DATA                    BITS(0,31)                           /*!< data to be transferred through the flash memory */

/* OSPI_STATMK */
#define OSPI_STATMK_MASK                  BITS(0,31)                           /*!< status mask */

/* OSPI_STATMATCH */
#define OSPI_STATMATCH_MATCH              BITS(0,31)                           /*!< status match */

/* OSPI_INTERVAL */
#define OSPI_INTERVAL_INTERVAL            BITS(0,15)                           /*!< interval cycle */

/* OSPI_TCFG */
#define OSPI_TCFG_IMOD                    BITS(0,2)                            /*!< instruction mode */
#define OSPI_TCFG_INSSZ                   BITS(4,5)                            /*!< instruction size */
#define OSPI_TCFG_ADDRMOD                 BITS(8,10)                           /*!< address mode */
#define OSPI_TCFG_ADDRDTR                 BIT(11)                              /*!< address double transfer rate */
#define OSPI_TCFG_ADDRSZ                  BITS(12,13)                          /*!< address size */
#define OSPI_TCFG_ALTEMOD                 BITS(16,18)                          /*!< alternate bytes mode */
#define OSPI_TCFG_ABDTR                   BIT(19)                              /*!< alternate bytes double transfer rate */
#define OSPI_TCFG_ALTESZ                  BITS(20,21)                          /*!< alternate bytes size */
#define OSPI_TCFG_DATAMOD                 BITS(24,26)                          /*!< data mode */
#define OSPI_TCFG_DADTR                   BIT(27)                              /*!< data double transfer rate */

/* OSPI_TIMCFG */
#define OSPI_TIMCFG_DUMYC                 BITS(0,4)                            /*!< number of dummy cycles */
#define OSPI_TIMCFG_DEHQC                 BIT(27)                              /*!< delay hold quarter cycle */
#define OSPI_TIMCFG_SSAMPLE               BIT(30)                              /*!< sample shift */

/* OSPI_INS */
#define OSPI_INS_INSTRUCTION              BITS(0,31)                           /*!< command information to be send to the flash memory */

/* OSPI_ALTE */
#define OSPI_ALTE_ALTE                    BITS(0,31)                           /*!< alternate bytes to be send to the flash memory */

/* OSPI_WPTCFG */
#define OSPI_WPTCFG_IMOD                  BITS(0,2)                            /*!< instruction mode */
#define OSPI_WPTCFG_INSSZ                 BITS(4,5)                            /*!< instruction size */
#define OSPI_WPTCFG_ADDRMOD               BITS(8,10)                           /*!< address mode */
#define OSPI_WPTCFG_ADDRDTR               BIT(11)                              /*!< address double transfer rate */
#define OSPI_WPTCFG_ADDRSZ                BITS(12,13)                          /*!< address size */
#define OSPI_WPTCFG_ALTEMOD               BITS(16,18)                          /*!< alternate bytes mode */
#define OSPI_WPTCFG_ABDTR                 BIT(19)                              /*!< alternate bytes double transfer rate */
#define OSPI_WPTCFG_ALTESZ                BITS(20,21)                          /*!< alternate bytes size */
#define OSPI_WPTCFG_DATAMOD               BITS(24,26)                          /*!< data mode */
#define OSPI_WPTCFG_DADTR                 BIT(27)                              /*!< data double transfer rate */

/* OSPI_WPTIMCFG */
#define OSPI_WPTIMCFG_DUMYC               BITS(0,4)                            /*!< number of dummy cycles */
#define OSPI_WPTIMCFG_DEHQC               BIT(28)                              /*!< delay hold quarter cycle */
#define OSPI_WPTIMCFG_SSAMPLE             BIT(30)                              /*!< sample shift */

/* OSPI_WPINS */
#define OSPI_WPINS_INSTRUCTION            BITS(0,31)                           /*!< command information to be send to the flash memory */

/* OSPI_WPALTE */
#define OSPI_WPALTE_ALTE                  BITS(0,31)                           /*!< optional data to be send to the flash memory */

/* OSPI_WTCFG */
#define OSPI_WTCFG_IMOD                   BITS(0,2)                            /*!< instruction mode */
#define OSPI_WTCFG_INSSZ                  BITS(4,5)                            /*!< instruction size */
#define OSPI_WTCFG_ADDRMOD                BITS(8,10)                           /*!< address mode */
#define OSPI_WTCFG_ADDRDTR                BIT(11)                              /*!< address double transfer rate */
#define OSPI_WTCFG_ADDRSZ                 BITS(12,13)                          /*!< address size */
#define OSPI_WTCFG_ALTEMOD                BITS(16,18)                          /*!< alternate bytes mode */
#define OSPI_WTCFG_ABDTR                  BIT(19)                              /*!< alternate bytes double transfer rate */
#define OSPI_WTCFG_ALTESZ                 BITS(20,21)                          /*!< alternate bytes size */
#define OSPI_WTCFG_DATAMOD                BITS(24,26)                          /*!< data mode */
#define OSPI_WTCFG_DADTR                  BIT(27)                              /*!< data double transfer rate */

/* OSPI_WTIMCFG */
#define OSPI_WTIMCFG_DUMYC                BITS(0,4)                            /*!< number of dummy cycles */

/* OSPI_WINS */
#define OSPI_WINS_INSTRUCTION             BITS(0,31)                           /*!< command information to be send to the flash memory */

/* OSPI_WALTE */
#define OSPI_WALTE_ALTE                   BITS(0,31)                           /*!< optional data to be send to the flash memory */

/* OSPI_HBLCFG */
#define OSPI_HBLCFG_LMOD                  BIT(0)                               /*!< latency mode */
#define OSPI_HBLCFG_WZLAT                 BIT(1)                               /*!< write zero latency */
#define OSPI_HBLCFG_ACCTM                 BITS(8,15)                           /*!< access time */
#define OSPI_HBLCFG_RWRTM                 BITS(16,23)                          /*!< read write recovery time */

/* constants definitions */
/* ospi init struct definitions */
typedef struct {
    uint32_t prescaler;                                                        /*! specifies the prescaler factor for generating clock based on the kernel clock.
                                                                                this parameter can be a number between 0 and 255 */
    uint32_t fifo_threshold;                                                   /*! specifies the threshold number of bytes in the FIFO (used only in indirect mode)
                                                                                this parameter can be a value between 1 and 31 */
    uint32_t sample_shift;                                                     /*! specifies the sample shift. The data is sampled 1/2 clock cycle delay later to
                                                                                take in account external signal delays. (it should be OSPI_SAMPLE_SHIFTING_NONE in DTR mode) */
    uint32_t device_size;                                                      /*! specifies the device size. FlashSize+1 is effectively the number of address bits
                                                                                required to address the flash memory. The flash capacity can be up to 4GB
                                                                                (addressed using 32 bits) in indirect mode, but the addressable space in
                                                                                memory-mapped mode is limited to 256MB
                                                                                this parameter can be a number between 0 and 31 */
    uint32_t cs_hightime;                                                      /*! specifies the chip select high time. chipselecthightime+1 defines the minimum number
                                                                                of clock cycles which the chip select must remain high between commands. */
    uint32_t memory_type;                                                      /*! it indicates the external device type connected to the OSPI. */

    uint32_t wrap_size;                                                        /*! it indicates the wrap-size corresponding the external device configuration. */

    uint32_t delay_hold_cycle;                                                 /*! it allows to hold to 1/4 cycle the data. */
} ospi_parameter_struct;

/* ospi regular command struct definitions */
typedef struct {
    uint32_t operation_type;                                                   /*! it indicates if the configuration applies to the common regsiters or
                                                                                to the registers for the write operation (these registers are only
                                                                                used for memory-mapped mode). */
    uint32_t instruction;                                                      /*! it contains the instruction to be sent to the device.
                                                                                this parameter can be a value between 0 and 0xFFFFFFFF */
    uint32_t ins_mode;                                                         /*! it indicates the mode of the instruction */

    uint32_t ins_size;                                                         /*! it indicates the size of the instruction */

    uint32_t address;                                                          /*! it contains the address to be sent to the device.
                                                                                this parameter can be a value between 0 and 0xFFFFFFFF */
    uint32_t addr_mode;                                                        /*! it indicates the mode of the address */

    uint32_t addr_size;                                                        /*! it indicates the size of the address */

    uint32_t addr_dtr_mode;                                                    /*! it enables or not the DTR mode for the address phase */

    uint32_t alter_bytes;                                                      /*! it contains the alternate bytes to be sent to the device.
                                                                                this parameter can be a value between 0 and 0xFFFFFFFF */
    uint32_t alter_bytes_mode;                                                 /*! it indicates the mode of the alternate bytes */

    uint32_t alter_bytes_size;                                                 /*! it indicates the size of the alternate bytes */

    uint32_t alter_bytes_dtr_mode;                                             /*! it enables or not the DTR mode for the alternate bytes phase */

    uint32_t data_mode;                                                        /*! it indicates the mode of the data */

    uint32_t nbdata;                                                           /*! it indicates the number of data transferred with this command.
                                                                                this field is only used for indirect mode.
                                                                                this parameter can be a value between 1 and 0xFFFFFFFF */
    uint32_t data_dtr_mode;                                                    /*! it enables or not the DTR mode for the data phase */

    uint32_t dummy_cycles;                                                     /*! it indicates the number of dummy cycles inserted before data phase.
                                                                                this parameter can be a value between 0 and 31 */
} ospi_regular_cmd_struct;

/* ospi autopolling struct definitions */
typedef struct {
    uint32_t match;                                                            /*! specifies the value to be compared with the masked status register to get a match.
                                                                                this parameter can be any value between 0 and 0xFFFFFFFF */
    uint32_t mask;                                                             /*! specifies the mask to be applied to the status bytes received.
                                                                                this parameter can be any value between 0 and 0xFFFFFFFF */
    uint32_t interval;                                                         /*! specifies the number of clock cycles between two read during automatic polling phases.
                                                                                this parameter can be any value between 0 and 0xFFFF */
    uint32_t match_mode;                                                       /*! specifies the method used for determining a match */

    uint32_t automatic_stop;                                                   /*! specifies if automatic polling is stopped after a match */

} ospi_autopolling_struct;

/* OSPI configuration */
/* OSPI automatic stop */
#define OSPI_AUTOMATIC_STOP_MATCH         OSPI_CTL_SPS                         /*!< status polling mode stop in match */

/* OSPI match mode */
#define OSPI_MATCH_MODE_AND               0x00000000U                          /*!< OSPI status polling match mode and */
#define OSPI_MATCH_MODE_OR                OSPI_CTL_SPMOD                       /*!< OSPI status polling match mode or */

/* OSPI functional mode */
#define OSPI_FMOD(regval)                 (BITS(28,29) & ((uint32_t)(regval) << 28U))
#define OSPI_INDIRECT_WRITE               OSPI_FMOD(0)                         /*!< OSPI indirect write mode */
#define OSPI_INDIRECT_READ                OSPI_FMOD(1)                         /*!< OSPI indirect read mode */
#define OSPI_STATUS_POLLING               OSPI_FMOD(2)                         /*!< OSPI status polling mode */
#define OSPI_MEMORY_MAPPED                OSPI_FMOD(3)                         /*!< OSPI memory mapped mode */

/* OSPI FIFO threshold level set */
#define OSPI_FTL(regval)                  (BITS(8,12) & ((uint32_t)(regval) << 8U))
#define OSPI_FIFO_THRESHOLD_1             OSPI_FTL(0)                          /*!< in indirect write mode, there are 1 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 1 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_2             OSPI_FTL(1)                          /*!< in indirect write mode, there are 2 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 2 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_3             OSPI_FTL(2)                          /*!< in indirect write mode, there are 3 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 3 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_4             OSPI_FTL(3)                          /*!< in indirect write mode, there are 4 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 4 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_5             OSPI_FTL(4)                          /*!< in indirect write mode, there are 5 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 5 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_6             OSPI_FTL(5)                          /*!< in indirect write mode, there are 6 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 6 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_7             OSPI_FTL(6)                          /*!< in indirect write mode, there are 7 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 7 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_8             OSPI_FTL(7)                          /*!< in indirect write mode, there are 8 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 8 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_9             OSPI_FTL(8)                          /*!< in indirect write mode, there are 9 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 9 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_10            OSPI_FTL(9)                          /*!< in indirect write mode, there are 10 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 10 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_11            OSPI_FTL(10)                         /*!< in indirect write mode, there are 11 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 11 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_12            OSPI_FTL(11)                         /*!< in indirect write mode, there are 12 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 12 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_13            OSPI_FTL(12)                         /*!< in indirect write mode, there are 13 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 13 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_14            OSPI_FTL(13)                         /*!< in indirect write mode, there are 14 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 14 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_15            OSPI_FTL(14)                         /*!< in indirect write mode, there are 15 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 15 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_16            OSPI_FTL(15)                         /*!< in indirect write mode, there are 16 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 16 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_17            OSPI_FTL(16)                         /*!< in indirect write mode, there are 17 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 17 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_18            OSPI_FTL(17)                         /*!< in indirect write mode, there are 18 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 18 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_19            OSPI_FTL(18)                         /*!< in indirect write mode, there are 19 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 19 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_20            OSPI_FTL(19)                         /*!< in indirect write mode, there are 20 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 20 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_21            OSPI_FTL(20)                         /*!< in indirect write mode, there are 21 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 21 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_22            OSPI_FTL(21)                         /*!< in indirect write mode, there are 22 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 22 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_23            OSPI_FTL(22)                         /*!< in indirect write mode, there are 23 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 23 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_24            OSPI_FTL(23)                         /*!< in indirect write mode, there are 24 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 24 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_25            OSPI_FTL(24)                         /*!< in indirect write mode, there are 25 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 25 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_26            OSPI_FTL(25)                         /*!< in indirect write mode, there are 26 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 26 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_27            OSPI_FTL(26)                         /*!< in indirect write mode, there are 27 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 27 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_28            OSPI_FTL(27)                         /*!< in indirect write mode, there are 28 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 28 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_29            OSPI_FTL(28)                         /*!< in indirect write mode, there are 29 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 29 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_30            OSPI_FTL(29)                         /*!< in indirect write mode, there are 30 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 30 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_31            OSPI_FTL(30)                         /*!< in indirect write mode, there are 31 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 31 or more free bytes available to be read from the FIFO */
#define OSPI_FIFO_THRESHOLD_32            OSPI_FTL(31)                         /*!< in indirect write mode, there are 32 or more free bytes available to be written to the FIFO,
                                                                                in indirect read mode, there are 32 or more free bytes available to be read from the FIFO */

/* OSPI chip select high cycle */
#define OSPI_CSHC(regval)                 (BITS(8,13) & ((uint32_t)(regval) << 8U))
#define OSPI_CS_HIGH_TIME_1_CYCLE         OSPI_CSHC(0)                         /*!< OSPI csn stays high for at least 1 cycle */
#define OSPI_CS_HIGH_TIME_2_CYCLE         OSPI_CSHC(1)                         /*!< OSPI csn stays high for at least 2 cycle */
#define OSPI_CS_HIGH_TIME_3_CYCLE         OSPI_CSHC(2)                         /*!< OSPI csn stays high for at least 3 cycle */
#define OSPI_CS_HIGH_TIME_4_CYCLE         OSPI_CSHC(3)                         /*!< OSPI csn stays high for at least 4 cycle */
#define OSPI_CS_HIGH_TIME_5_CYCLE         OSPI_CSHC(4)                         /*!< OSPI csn stays high for at least 5 cycle */
#define OSPI_CS_HIGH_TIME_6_CYCLE         OSPI_CSHC(5)                         /*!< OSPI csn stays high for at least 6 cycle */
#define OSPI_CS_HIGH_TIME_7_CYCLE         OSPI_CSHC(6)                         /*!< OSPI csn stays high for at least 7 cycle */
#define OSPI_CS_HIGH_TIME_8_CYCLE         OSPI_CSHC(7)                         /*!< OSPI csn stays high for at least 8 cycle */
#define OSPI_CS_HIGH_TIME_9_CYCLE         OSPI_CSHC(8)                         /*!< OSPI csn stays high for at least 9 cycle */
#define OSPI_CS_HIGH_TIME_10_CYCLE        OSPI_CSHC(9)                         /*!< OSPI csn stays high for at least 10 cycle */
#define OSPI_CS_HIGH_TIME_11_CYCLE        OSPI_CSHC(10)                        /*!< OSPI csn stays high for at least 11 cycle */
#define OSPI_CS_HIGH_TIME_12_CYCLE        OSPI_CSHC(11)                        /*!< OSPI csn stays high for at least 12 cycle */
#define OSPI_CS_HIGH_TIME_13_CYCLE        OSPI_CSHC(12)                        /*!< OSPI csn stays high for at least 13 cycle */
#define OSPI_CS_HIGH_TIME_14_CYCLE        OSPI_CSHC(13)                        /*!< OSPI csn stays high for at least 14 cycle */
#define OSPI_CS_HIGH_TIME_15_CYCLE        OSPI_CSHC(14)                        /*!< OSPI csn stays high for at least 15 cycle */
#define OSPI_CS_HIGH_TIME_16_CYCLE        OSPI_CSHC(15)                        /*!< OSPI csn stays high for at least 16 cycle */
#define OSPI_CS_HIGH_TIME_17_CYCLE        OSPI_CSHC(16)                        /*!< OSPI csn stays high for at least 17 cycle */
#define OSPI_CS_HIGH_TIME_18_CYCLE        OSPI_CSHC(17)                        /*!< OSPI csn stays high for at least 18 cycle */
#define OSPI_CS_HIGH_TIME_19_CYCLE        OSPI_CSHC(18)                        /*!< OSPI csn stays high for at least 19 cycle */
#define OSPI_CS_HIGH_TIME_20_CYCLE        OSPI_CSHC(19)                        /*!< OSPI csn stays high for at least 20 cycle */
#define OSPI_CS_HIGH_TIME_21_CYCLE        OSPI_CSHC(20)                        /*!< OSPI csn stays high for at least 21 cycle */
#define OSPI_CS_HIGH_TIME_22_CYCLE        OSPI_CSHC(21)                        /*!< OSPI csn stays high for at least 22 cycle */
#define OSPI_CS_HIGH_TIME_23_CYCLE        OSPI_CSHC(22)                        /*!< OSPI csn stays high for at least 23 cycle */
#define OSPI_CS_HIGH_TIME_24_CYCLE        OSPI_CSHC(23)                        /*!< OSPI csn stays high for at least 24 cycle */
#define OSPI_CS_HIGH_TIME_25_CYCLE        OSPI_CSHC(24)                        /*!< OSPI csn stays high for at least 25 cycle */
#define OSPI_CS_HIGH_TIME_26_CYCLE        OSPI_CSHC(25)                        /*!< OSPI csn stays high for at least 26 cycle */
#define OSPI_CS_HIGH_TIME_27_CYCLE        OSPI_CSHC(26)                        /*!< OSPI csn stays high for at least 27 cycle */
#define OSPI_CS_HIGH_TIME_28_CYCLE        OSPI_CSHC(27)                        /*!< OSPI csn stays high for at least 28 cycle */
#define OSPI_CS_HIGH_TIME_29_CYCLE        OSPI_CSHC(28)                        /*!< OSPI csn stays high for at least 29 cycle */
#define OSPI_CS_HIGH_TIME_30_CYCLE        OSPI_CSHC(29)                        /*!< OSPI csn stays high for at least 30 cycle */
#define OSPI_CS_HIGH_TIME_31_CYCLE        OSPI_CSHC(30)                        /*!< OSPI csn stays high for at least 31 cycle */
#define OSPI_CS_HIGH_TIME_32_CYCLE        OSPI_CSHC(31)                        /*!< OSPI csn stays high for at least 32 cycle */
#define OSPI_CS_HIGH_TIME_33_CYCLE        OSPI_CSHC(32)                        /*!< OSPI csn stays high for at least 33 cycle */
#define OSPI_CS_HIGH_TIME_34_CYCLE        OSPI_CSHC(33)                        /*!< OSPI csn stays high for at least 34 cycle */
#define OSPI_CS_HIGH_TIME_35_CYCLE        OSPI_CSHC(34)                        /*!< OSPI csn stays high for at least 35 cycle */
#define OSPI_CS_HIGH_TIME_36_CYCLE        OSPI_CSHC(35)                        /*!< OSPI csn stays high for at least 36 cycle */
#define OSPI_CS_HIGH_TIME_37_CYCLE        OSPI_CSHC(36)                        /*!< OSPI csn stays high for at least 37 cycle */
#define OSPI_CS_HIGH_TIME_38_CYCLE        OSPI_CSHC(37)                        /*!< OSPI csn stays high for at least 38 cycle */
#define OSPI_CS_HIGH_TIME_39_CYCLE        OSPI_CSHC(38)                        /*!< OSPI csn stays high for at least 39 cycle */
#define OSPI_CS_HIGH_TIME_40_CYCLE        OSPI_CSHC(39)                        /*!< OSPI csn stays high for at least 40 cycle */
#define OSPI_CS_HIGH_TIME_41_CYCLE        OSPI_CSHC(40)                        /*!< OSPI csn stays high for at least 41 cycle */
#define OSPI_CS_HIGH_TIME_42_CYCLE        OSPI_CSHC(41)                        /*!< OSPI csn stays high for at least 42 cycle */
#define OSPI_CS_HIGH_TIME_43_CYCLE        OSPI_CSHC(42)                        /*!< OSPI csn stays high for at least 43 cycle */
#define OSPI_CS_HIGH_TIME_44_CYCLE        OSPI_CSHC(43)                        /*!< OSPI csn stays high for at least 44 cycle */
#define OSPI_CS_HIGH_TIME_45_CYCLE        OSPI_CSHC(44)                        /*!< OSPI csn stays high for at least 45 cycle */
#define OSPI_CS_HIGH_TIME_46_CYCLE        OSPI_CSHC(45)                        /*!< OSPI csn stays high for at least 46 cycle */
#define OSPI_CS_HIGH_TIME_47_CYCLE        OSPI_CSHC(46)                        /*!< OSPI csn stays high for at least 47 cycle */
#define OSPI_CS_HIGH_TIME_48_CYCLE        OSPI_CSHC(47)                        /*!< OSPI csn stays high for at least 48 cycle */
#define OSPI_CS_HIGH_TIME_49_CYCLE        OSPI_CSHC(48)                        /*!< OSPI csn stays high for at least 49 cycle */
#define OSPI_CS_HIGH_TIME_50_CYCLE        OSPI_CSHC(49)                        /*!< OSPI csn stays high for at least 50 cycle */
#define OSPI_CS_HIGH_TIME_51_CYCLE        OSPI_CSHC(50)                        /*!< OSPI csn stays high for at least 51 cycle */
#define OSPI_CS_HIGH_TIME_52_CYCLE        OSPI_CSHC(51)                        /*!< OSPI csn stays high for at least 52 cycle */
#define OSPI_CS_HIGH_TIME_53_CYCLE        OSPI_CSHC(52)                        /*!< OSPI csn stays high for at least 53 cycle */
#define OSPI_CS_HIGH_TIME_54_CYCLE        OSPI_CSHC(53)                        /*!< OSPI csn stays high for at least 54 cycle */
#define OSPI_CS_HIGH_TIME_55_CYCLE        OSPI_CSHC(54)                        /*!< OSPI csn stays high for at least 55 cycle */
#define OSPI_CS_HIGH_TIME_56_CYCLE        OSPI_CSHC(55)                        /*!< OSPI csn stays high for at least 56 cycle */
#define OSPI_CS_HIGH_TIME_57_CYCLE        OSPI_CSHC(56)                        /*!< OSPI csn stays high for at least 57 cycle */
#define OSPI_CS_HIGH_TIME_58_CYCLE        OSPI_CSHC(57)                        /*!< OSPI csn stays high for at least 58 cycle */
#define OSPI_CS_HIGH_TIME_59_CYCLE        OSPI_CSHC(58)                        /*!< OSPI csn stays high for at least 59 cycle */
#define OSPI_CS_HIGH_TIME_60_CYCLE        OSPI_CSHC(59)                        /*!< OSPI csn stays high for at least 60 cycle */
#define OSPI_CS_HIGH_TIME_61_CYCLE        OSPI_CSHC(60)                        /*!< OSPI csn stays high for at least 61 cycle */
#define OSPI_CS_HIGH_TIME_62_CYCLE        OSPI_CSHC(61)                        /*!< OSPI csn stays high for at least 62 cycle */
#define OSPI_CS_HIGH_TIME_63_CYCLE        OSPI_CSHC(62)                        /*!< OSPI csn stays high for at least 63 cycle */
#define OSPI_CS_HIGH_TIME_64_CYCLE        OSPI_CSHC(63)                        /*!< OSPI csn stays high for at least 64 cycle */

/* OSPI flash memory size */
#define OSPI_MESZ(regval)                 (BITS(16,20) & ((uint32_t)(regval) << 16U))
#define OSPI_MESZ_2_BYTES                 OSPI_MESZ(0)                         /*!< the size of external memory is 2 bytes */
#define OSPI_MESZ_4_BYTES                 OSPI_MESZ(1)                         /*!< the size of external memory is 4 bytes */
#define OSPI_MESZ_8_BYTES                 OSPI_MESZ(2)                         /*!< the size of external memory is 8 bytes */
#define OSPI_MESZ_16_BYTES                OSPI_MESZ(3)                         /*!< the size of external memory is 16 bytes */
#define OSPI_MESZ_32_BYTES                OSPI_MESZ(4)                         /*!< the size of external memory is 32 bytes */
#define OSPI_MESZ_64_BYTES                OSPI_MESZ(5)                         /*!< the size of external memory is 64 bytes */
#define OSPI_MESZ_128_BYTES               OSPI_MESZ(6)                         /*!< the size of external memory is 128 bytes */
#define OSPI_MESZ_256_BYTES               OSPI_MESZ(7)                         /*!< the size of external memory is 256 bytes */
#define OSPI_MESZ_512_BYTES               OSPI_MESZ(8)                         /*!< the size of external memory is 512 bytes */
#define OSPI_MESZ_1024_BYTES              OSPI_MESZ(9)                         /*!< the size of external memory is 1024 bytes */
#define OSPI_MESZ_2_KBS                   OSPI_MESZ(10)                        /*!< the size of external memory is 2 KB */
#define OSPI_MESZ_4_KBS                   OSPI_MESZ(11)                        /*!< the size of external memory is 4 KB */
#define OSPI_MESZ_8_KBS                   OSPI_MESZ(12)                        /*!< the size of external memory is 8 KB */
#define OSPI_MESZ_16_KBS                  OSPI_MESZ(13)                        /*!< the size of external memory is 16 KB */
#define OSPI_MESZ_32_KBS                  OSPI_MESZ(14)                        /*!< the size of external memory is 32 KB */
#define OSPI_MESZ_64_KBS                  OSPI_MESZ(15)                        /*!< the size of external memory is 64 KB */
#define OSPI_MESZ_128_KBS                 OSPI_MESZ(16)                        /*!< the size of external memory is 128 KB */
#define OSPI_MESZ_256_KBS                 OSPI_MESZ(17)                        /*!< the size of external memory is 256 KB */
#define OSPI_MESZ_512_KBS                 OSPI_MESZ(18)                        /*!< the size of external memory is 512 KB */
#define OSPI_MESZ_1024_KBS                OSPI_MESZ(19)                        /*!< the size of external memory is 1024 KBS */
#define OSPI_MESZ_2_MBS                   OSPI_MESZ(20)                        /*!< the size of external memory is 2 MB */
#define OSPI_MESZ_4_MBS                   OSPI_MESZ(21)                        /*!< the size of external memory is 4 MB */
#define OSPI_MESZ_8_MBS                   OSPI_MESZ(22)                        /*!< the size of external memory is 8 MB */
#define OSPI_MESZ_16_MBS                  OSPI_MESZ(23)                        /*!< the size of external memory is 16 MB */
#define OSPI_MESZ_32_MBS                  OSPI_MESZ(24)                        /*!< the size of external memory is 32 MB */
#define OSPI_MESZ_64_MBS                  OSPI_MESZ(25)                        /*!< the size of external memory is 64 MB */
#define OSPI_MESZ_128_MBS                 OSPI_MESZ(26)                        /*!< the size of external memory is 128 MB */
#define OSPI_MESZ_256_MBS                 OSPI_MESZ(27)                        /*!< the size of external memory is 256 MB */
#define OSPI_MESZ_512_MBS                 OSPI_MESZ(28)                        /*!< the size of external memory is 512 MB */
#define OSPI_MESZ_1024_MBS                OSPI_MESZ(29)                        /*!< the size of external memory is 1024 MB */
#define OSPI_MESZ_2048_MBS                OSPI_MESZ(30)                        /*!< the size of external memory is 2048 MB */
#define OSPI_MESZ_4096_MBS                OSPI_MESZ(31)                        /*!< the size of external memory is 4096 MB */

/* OSPI device type select */
#define OSPI_DTYSEL(regval)               (BITS(24,26) & ((uint32_t)(regval) << 24U))
#define OSPI_MICRON_MODE                  OSPI_DTYSEL(0)                       /*!< device type select micron mode */
#define OSPI_MACRONIX_MODE                OSPI_DTYSEL(1)                       /*!< device type select micronix mode */
#define OSPI_STANDARD_MODE                OSPI_DTYSEL(2)                       /*!< device type select standard mode */
#define OSPI_MACRONIX_RAM_MODE            OSPI_DTYSEL(3)                       /*!< device type select micronix ram mode */
#define OSPI_RESERVE_MODE                 OSPI_DTYSEL(7)                       /*!< reserve mode, not use */

/* OSPI prescaler set */
#define OSPI_PSC(regval)                  (BITS(0,7) & ((uint32_t)(regval) << 0U))

/* OSPI wrap size set */
#define OSPI_WPSZ(regval)                 (BITS(16,18) & ((uint32_t)(regval) << 16U))
#define OSPI_DIRECT                       OSPI_WPSZ(0)                         /*!< external memory indirect device does not support wrap read */
#define OSPI_WRAP_16BYTES                 OSPI_WPSZ(2)                         /*!< external memory device supports wrap size of 16 bytes */
#define OSPI_WRAP_32BYTES                 OSPI_WPSZ(3)                         /*!< external memory device supports wrap size of 32 bytes */
#define OSPI_WRAP_64BYTES                 OSPI_WPSZ(4)                         /*!< external memory device supports wrap size of 64 bytes */
#define OSPI_WRAP_128BYTES                OSPI_WPSZ(5)                         /*!< external memory device supports wrap size of 128 bytes */

/* OSPI transmit configuration */
/* OSPI operation type */
#define OSPI_OPTYPE_COMMON_CFG           ((uint32_t)0x00000000U)               /*!< common configuration (indirect or auto-polling mode) */
#define OSPI_OPTYPE_READ_CFG             ((uint32_t)0x00000001U)               /*!< read configuration (memory-mapped mode) */
#define OSPI_OPTYPE_WRITE_CFG            ((uint32_t)0x00000002U)               /*!< write configuration (memory-mapped mode) */
#define OSPI_OPTYPE_WRAP_CFG             ((uint32_t)0x00000003U)               /*!< wrap configuration (memory-mapped mode) */

/* OSPI instruction mode */
#define OSPI_IMOD(regval)                 (BITS(0,2) & ((uint32_t)(regval) << 0U))
#define OSPI_INSTRUCTION_NONE             OSPI_IMOD(0)                         /*!< no instruction mode */
#define OSPI_INSTRUCTION_1_LINE           OSPI_IMOD(1)                         /*!< instruction mode on a single line */
#define OSPI_INSTRUCTION_2_LINES          OSPI_IMOD(2)                         /*!< instruction mode on two lines */
#define OSPI_INSTRUCTION_4_LINES          OSPI_IMOD(3)                         /*!< instruction mode on four lines */
#define OSPI_INSTRUCTION_8_LINES          OSPI_IMOD(4)                         /*!< instruction mode on eight lines */

/* OSPI instruction size */
#define OSPI_INSSZ(regval)                (BITS(4,5) & ((uint32_t)(regval) << 4U))
#define OSPI_INSTRUCTION_8_BITS           OSPI_INSSZ(0)                        /*!< instruction size on 8-bit address */
#define OSPI_INSTRUCTION_16_BITS          OSPI_INSSZ(1)                        /*!< instruction size on 16-bit address */
#define OSPI_INSTRUCTION_24_BITS          OSPI_INSSZ(2)                        /*!< instruction size on 24-bit address */
#define OSPI_INSTRUCTION_32_BITS          OSPI_INSSZ(3)                        /*!< instruction size on 32-bit address */

/* OSPI address mode */
#define OSPI_ADDRMOD(regval)              (BITS(8,10) & ((uint32_t)(regval) << 8U))
#define OSPI_ADDRESS_NONE                 OSPI_ADDRMOD(0)                      /*!< no address mode */
#define OSPI_ADDRESS_1_LINE               OSPI_ADDRMOD(1)                      /*!< address mode on a single line */
#define OSPI_ADDRESS_2_LINES              OSPI_ADDRMOD(2)                      /*!< address mode on two lines */
#define OSPI_ADDRESS_4_LINES              OSPI_ADDRMOD(3)                      /*!< address mode on four lines */
#define OSPI_ADDRESS_8_LINES              OSPI_ADDRMOD(4)                      /*!< address mode on eight lines */

/* OSPI address size */
#define OSPI_ADDRSZ(regval)               (BITS(12,13) & ((uint32_t)(regval) << 12U))
#define OSPI_ADDRESS_8_BITS               OSPI_ADDRSZ(0)                       /*!< address size on 8-bit address */
#define OSPI_ADDRESS_16_BITS              OSPI_ADDRSZ(1)                       /*!< address size on 16-bit address */
#define OSPI_ADDRESS_24_BITS              OSPI_ADDRSZ(2)                       /*!< address size on 24-bit address */
#define OSPI_ADDRESS_32_BITS              OSPI_ADDRSZ(3)                       /*!< address size on 32-bit address */

/* OSPI address double transfer rate */
#define OSPI_ADDRDTR_MODE_DISABLE         0x00000000U                          /*!< address double transfer rate mode disable */
#define OSPI_ADDRDTR_MODE_ENABLE          OSPI_TCFG_ADDRDTR                    /*!< address double transfer rate mode disable */

/* OSPI alternate bytes mode */
#define OSPI_ALTEMOD(regval)              (BITS(16,18) & ((uint32_t)(regval) << 16U))
#define OSPI_ALTERNATE_BYTES_NONE         OSPI_ALTEMOD(0)                      /*!< no alternate bytes mode */
#define OSPI_ALTERNATE_BYTES_1_LINE       OSPI_ALTEMOD(1)                      /*!< alternate bytes mode on a single line */
#define OSPI_ALTERNATE_BYTES_2_LINES      OSPI_ALTEMOD(2)                      /*!< alternate bytes mode on two lines */
#define OSPI_ALTERNATE_BYTES_4_LINES      OSPI_ALTEMOD(3)                      /*!< alternate bytes mode on four lines */
#define OSPI_ALTERNATE_BYTES_8_LINES      OSPI_ALTEMOD(4)                      /*!< alternate bytes mode on eight lines */

/* OSPI alternate bytes size */
#define OSPI_ALTESZ(regval)               (BITS(20,21) & ((uint32_t)(regval) << 20U))
#define OSPI_ALTERNATE_BYTES_8_BITS       OSPI_ALTESZ(0)                       /*!< alternate bytes size on 8-bit address */
#define OSPI_ALTERNATE_BYTES_16_BITS      OSPI_ALTESZ(1)                       /*!< alternate bytes size on 16-bit address */
#define OSPI_ALTERNATE_BYTES_24_BITS      OSPI_ALTESZ(2)                       /*!< alternate bytes size on 24-bit address */
#define OSPI_ALTERNATE_BYTES_32_BITS      OSPI_ALTESZ(3)                       /*!< alternate bytes size on 32-bit address */

/* OSPI alternate bytes double transfer rate */
#define OSPI_ABDTR_MODE_DISABLE           0x00000000U                          /*!< alternate bytes double transfer rate mode disable */
#define OSPI_ABDTR_MODE_ENABLE            OSPI_TCFG_ABDTR                      /*!< alternate bytes double transfer rate mode enable */

/* OSPI data mode */
#define OSPI_DATAMOD(regval)              (BITS(24,26) & ((uint32_t)(regval) << 24U))
#define OSPI_DATA_NONE                    OSPI_DATAMOD(0)                      /*!< no data mode */
#define OSPI_DATA_1_LINE                  OSPI_DATAMOD(1)                      /*!< data mode on a single line */
#define OSPI_DATA_2_LINES                 OSPI_DATAMOD(2)                      /*!< data mode on two lines */
#define OSPI_DATA_4_LINES                 OSPI_DATAMOD(3)                      /*!< data mode on four lines */
#define OSPI_DATA_8_LINES                 OSPI_DATAMOD(4)                      /*!< data mode on eight lines */

/* OSPI data double transfer rate */
#define OSPI_DADTR_MODE_DISABLE           0x00000000U                          /*!< data double transfer rate mode disable */
#define OSPI_DADTR_MODE_ENABLE            OSPI_TCFG_DADTR                      /*!< data double transfer rate mode enable */

/* OSPI dummy cycles */
#define OSPI_DUMYC(regval)                (BITS(0,4) & ((uint32_t)(regval) << 0U))
#define OSPI_DUMYC_CYCLES_0               OSPI_DUMYC(0)                        /*!< duration of the dummy instruction phase is 0 cycle */
#define OSPI_DUMYC_CYCLES_1               OSPI_DUMYC(1)                        /*!< duration of the dummy instruction phase is 1 cycle */
#define OSPI_DUMYC_CYCLES_2               OSPI_DUMYC(2)                        /*!< duration of the dummy instruction phase is 2 cycle */
#define OSPI_DUMYC_CYCLES_3               OSPI_DUMYC(3)                        /*!< duration of the dummy instruction phase is 3 cycle */
#define OSPI_DUMYC_CYCLES_4               OSPI_DUMYC(4)                        /*!< duration of the dummy instruction phase is 4 cycle */
#define OSPI_DUMYC_CYCLES_5               OSPI_DUMYC(5)                        /*!< duration of the dummy instruction phase is 5 cycle */
#define OSPI_DUMYC_CYCLES_6               OSPI_DUMYC(6)                        /*!< duration of the dummy instruction phase is 6 cycle */
#define OSPI_DUMYC_CYCLES_7               OSPI_DUMYC(7)                        /*!< duration of the dummy instruction phase is 7 cycle */
#define OSPI_DUMYC_CYCLES_8               OSPI_DUMYC(8)                        /*!< duration of the dummy instruction phase is 8 cycle */
#define OSPI_DUMYC_CYCLES_9               OSPI_DUMYC(9)                        /*!< duration of the dummy instruction phase is 9 cycle */
#define OSPI_DUMYC_CYCLES_10              OSPI_DUMYC(10)                       /*!< duration of the dummy instruction phase is 10 cycle */
#define OSPI_DUMYC_CYCLES_11              OSPI_DUMYC(11)                       /*!< duration of the dummy instruction phase is 11 cycle */
#define OSPI_DUMYC_CYCLES_12              OSPI_DUMYC(12)                       /*!< duration of the dummy instruction phase is 12 cycle */
#define OSPI_DUMYC_CYCLES_13              OSPI_DUMYC(13)                       /*!< duration of the dummy instruction phase is 13 cycle */
#define OSPI_DUMYC_CYCLES_14              OSPI_DUMYC(14)                       /*!< duration of the dummy instruction phase is 14 cycle */
#define OSPI_DUMYC_CYCLES_15              OSPI_DUMYC(15)                       /*!< duration of the dummy instruction phase is 15 cycle */
#define OSPI_DUMYC_CYCLES_16              OSPI_DUMYC(16)                       /*!< duration of the dummy instruction phase is 16 cycle */
#define OSPI_DUMYC_CYCLES_17              OSPI_DUMYC(17)                       /*!< duration of the dummy instruction phase is 17 cycle */
#define OSPI_DUMYC_CYCLES_18              OSPI_DUMYC(18)                       /*!< duration of the dummy instruction phase is 18 cycle */
#define OSPI_DUMYC_CYCLES_19              OSPI_DUMYC(19)                       /*!< duration of the dummy instruction phase is 19 cycle */
#define OSPI_DUMYC_CYCLES_20              OSPI_DUMYC(20)                       /*!< duration of the dummy instruction phase is 20 cycle */
#define OSPI_DUMYC_CYCLES_21              OSPI_DUMYC(21)                       /*!< duration of the dummy instruction phase is 21 cycle */
#define OSPI_DUMYC_CYCLES_22              OSPI_DUMYC(22)                       /*!< duration of the dummy instruction phase is 22 cycle */
#define OSPI_DUMYC_CYCLES_23              OSPI_DUMYC(23)                       /*!< duration of the dummy instruction phase is 23 cycle */
#define OSPI_DUMYC_CYCLES_24              OSPI_DUMYC(24)                       /*!< duration of the dummy instruction phase is 24 cycle */
#define OSPI_DUMYC_CYCLES_25              OSPI_DUMYC(25)                       /*!< duration of the dummy instruction phase is 25 cycle */
#define OSPI_DUMYC_CYCLES_26              OSPI_DUMYC(26)                       /*!< duration of the dummy instruction phase is 26 cycle */
#define OSPI_DUMYC_CYCLES_27              OSPI_DUMYC(27)                       /*!< duration of the dummy instruction phase is 27 cycle */
#define OSPI_DUMYC_CYCLES_28              OSPI_DUMYC(28)                       /*!< duration of the dummy instruction phase is 28 cycle */
#define OSPI_DUMYC_CYCLES_29              OSPI_DUMYC(29)                       /*!< duration of the dummy instruction phase is 29 cycle */
#define OSPI_DUMYC_CYCLES_30              OSPI_DUMYC(30)                       /*!< duration of the dummy instruction phase is 30 cycle */
#define OSPI_DUMYC_CYCLES_31              OSPI_DUMYC(31)                       /*!< duration of the dummy instruction phase is 31 cycle */

/* OSPI delay hold quarter cycle */
#define OSPI_DELAY_HOLD_NONE              0x00000000U                          /*!< OSPI no delay hold cycle */
#define OSPI_DELAY_HOLD_QUARTER_CYCLE     OSPI_TIMCFG_DEHQC                    /*!< OSPI delay hold 1/4 cycle */

/* OSPI sample shift */
#define OSPI_SAMPLE_SHIFTING_NONE         0x00000000U                          /*!< OSPI no sample shift */
#define OSPI_SAMPLE_SHIFTING_HALF_CYCLE   OSPI_TIMCFG_SSAMPLE                  /*!< OSPI have 1/2 cycle sample shift */

/* OSPI interrupt constants definitions */
#define OSPI_INT_TERR                     OSPI_CTL_TERRIE                      /*!< transfer error interrupt enable */
#define OSPI_INT_TC                       OSPI_CTL_TCIE                        /*!< transfer complete interrupt enable */
#define OSPI_INT_FT                       OSPI_CTL_FTIE                        /*!< fifo threshold interrupt enable */
#define OSPI_INT_SM                       OSPI_CTL_SMIE                        /*!< status match interrupt enable */

/* OSPI flag definitions */
#define OSPI_FLAG_TERR                    OSPI_STAT_TERR                       /*!< transfer error flag */
#define OSPI_FLAG_TC                      OSPI_STAT_TC                         /*!< transfer complete flag */
#define OSPI_FLAG_FT                      OSPI_STAT_FT                         /*!< fifo threshold flag */
#define OSPI_FLAG_SM                      OSPI_STAT_SM                         /*!< status match flag */
#define OSPI_FLAG_BUSY                    OSPI_STAT_BUSY                       /*!< busy flag */

/* define the OSPI bit position and its register index offset */
#define OSPI_REGIDX_BIT(regidx, bitpos)   (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define OSPI_REG_VAL(ospix, offset)       (REG32((ospix) + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define OSPI_BIT_POS(val)                 ((uint32_t)(val) & 0x0000001FU)
#define OSPI_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
        | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define OSPI_REG_VAL2(ospix, offset)      (REG32((ospix) + ((uint32_t)(offset) >> 22)))
#define OSPI_BIT_POS2(val)                (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define OSPI_CTL_REG_OFFSET              ((uint32_t)0x00000000U)                /*!< CTL register offset */
#define OSPI_STAT_REG_OFFSET             ((uint32_t)0x00000020U)                /*!< STAT register offset */

/* OSPI interrupt flags */
typedef enum {
    OSPI_INT_FLAG_TERR      = OSPI_REGIDX_BIT2(OSPI_CTL_REG_OFFSET, 16U, OSPI_STAT_REG_OFFSET, 0U),          /*!< transfer error interrupt flag */
    OSPI_INT_FLAG_TC        = OSPI_REGIDX_BIT2(OSPI_CTL_REG_OFFSET, 17U, OSPI_STAT_REG_OFFSET, 1U),          /*!< transfer complete interrupt enable */
    OSPI_INT_FLAG_FT        = OSPI_REGIDX_BIT2(OSPI_CTL_REG_OFFSET, 18U, OSPI_STAT_REG_OFFSET, 2U),          /*!< fifo threshold interrupt flag */
    OSPI_INT_FLAG_SM        = OSPI_REGIDX_BIT2(OSPI_CTL_REG_OFFSET, 19U, OSPI_STAT_REG_OFFSET, 3U),          /*!< status match interrupt flag */
} ospi_interrupt_flag_enum;

/* function declarations */
/* deinitialization initialization functions */
/* reset OSPI */
void ospi_deinit(uint32_t ospi_periph);
/* initialize the parameters of OSPI struct with the default values */
void ospi_struct_init(ospi_parameter_struct *ospi_struct);
/* initialize OSPI parameter */
void ospi_init(uint32_t ospi_periph, ospi_parameter_struct *ospi_struct);
/* enable OSPI */
void ospi_enable(uint32_t ospi_periph);
/* disable OSPI */
void ospi_disable(uint32_t ospi_periph);

/* device configuration functions */
/* configure device memory type */
void ospi_device_memory_type_config(uint32_t ospi_periph, uint32_t dtysel);
/* configure device memory size */
void ospi_device_memory_size_config(uint32_t ospi_periph, uint32_t mesz);

/* functional mode functions */
/* select functional mode */
void ospi_functional_mode_config(uint32_t ospi_periph, uint32_t fmod);
/* configure status polling mode */
void ospi_status_polling_config(uint32_t ospi_periph, uint32_t stop, uint32_t mode);
/* configure status mask */
void ospi_status_mask_config(uint32_t ospi_periph, uint32_t mask);
/* configure status match */
void ospi_status_match_config(uint32_t ospi_periph, uint32_t match);
/* configure interval cycle */
void ospi_interval_cycle_config(uint32_t ospi_periph, uint16_t interval);

/* OSPI mode functions */
/* configure OSPI fifo threshold level */
void ospi_fifo_level_config(uint32_t ospi_periph, uint32_t ftl);
/* configure chip select high cycle */
void ospi_chip_select_high_cycle_config(uint32_t ospi_periph, uint32_t cshc);
/* configure OSPI prescaler */
void ospi_prescaler_config(uint32_t ospi_periph, uint32_t psc);
/* configure send instruction only once mode */
void ospi_send_instruction_mode_config(uint32_t ospi_periph, uint32_t sioo);
/* configure dummy cycles number */
void ospi_dummy_cycles_config(uint32_t ospi_periph, uint32_t dumyc);
/* configure delay hold 1/4 cycle */
void ospi_delay_hold_cycle_config(uint32_t ospi_periph, uint32_t dehqc);
/* configure sample shift */
void ospi_sample_shift_config(uint32_t ospi_periph, uint32_t ssample);

/* OSPI tansfer configuration functions */
/* configure data length */
void ospi_data_length_config(uint32_t ospi_periph, uint32_t dtlen);
/* configure OSPI instruction */
void ospi_instruction_config(uint32_t ospi_periph, uint32_t instruction);
/* configure OSPI instruction mode */
void ospi_instruction_mode_config(uint32_t ospi_periph, uint32_t imod);
/* configure OSPI instruction size */
void ospi_instruction_size_config(uint32_t ospi_periph, uint32_t inssz);
/* configure OSPI address */
void ospi_address_config(uint32_t ospi_periph, uint32_t addr);
/* configure OSPI address mode */
void ospi_address_mode_config(uint32_t ospi_periph, uint32_t addrmod);
/* configure OSPI address dtr */
void ospi_address_dtr_config(uint32_t ospi_periph, uint32_t addrdtr);
/* configure OSPI address size */
void ospi_address_size_config(uint32_t ospi_periph, uint32_t addrsz);
/* configure alternate byte */
void ospi_alternate_byte_config(uint32_t ospi_periph, uint32_t alte);
/* configure OSPI alternate byte mode */
void ospi_alternate_byte_mode_config(uint32_t ospi_periph, uint32_t atlemod);
/* configure OSPI alternate byte dtr */
void ospi_alternate_byte_dtr_config(uint32_t ospi_periph, uint32_t abdtr);
/* configure OSPI alternate byte size */
void ospi_alternate_byte_size_config(uint32_t ospi_periph, uint32_t altesz);
/* configure data mode */
void ospi_data_mode_config(uint32_t ospi_periph, uint32_t datamod);
/* configure data size */
void ospi_data_dtr_config(uint32_t ospi_periph, uint32_t dadtr);
/* OSPI transmit data */
void ospi_data_transmit(uint32_t ospi_periph, uint32_t data);
/* OSPI receive data */
uint32_t ospi_data_receive(uint32_t ospi_periph);

/* OSPI DMA functions */
/* enable OSPI DMA */
void ospi_dma_enable(uint32_t ospi_periph);
/* disable OSPI DMA */
void ospi_dma_disable(uint32_t ospi_periph);

/* OSPI wrap configuration functions */
/* configure wrap size */
void ospi_wrap_size_config(uint32_t ospi_periph, uint32_t wpsz);
/* configure wrap instruction */
void ospi_wrap_instruction_config(uint32_t ospi_periph, uint32_t instruction);
/* configure wrap instruction mode */
void ospi_wrap_instruction_mode_config(uint32_t ospi_periph, uint32_t imod);
/* configure wrap instruction size */
void ospi_wrap_instruction_size_config(uint32_t ospi_periph, uint32_t inssz);
/* configure wrap address */
void ospi_wrap_address_config(uint32_t ospi_periph, uint32_t addr);
/* configure wrap address mode */
void ospi_wrap_address_mode_config(uint32_t ospi_periph, uint32_t addrmod);
/* configure wrap address dtr */
void ospi_wrap_address_dtr_config(uint32_t ospi_periph, uint32_t addrdtr);
/* configure wrap address size */
void ospi_wrap_address_size_config(uint32_t ospi_periph, uint32_t addrsz);
/* configure wrap alternate byte */
void ospi_wrap_alternate_byte_config(uint32_t ospi_periph, uint32_t alte);
/* configure wrap alternate bytes mode */
void ospi_wrap_alternate_byte_mode_config(uint32_t ospi_periph, uint32_t atlemod);
/* configure wrap alternate bytes dtr */
void ospi_wrap_alternate_byte_dtr_config(uint32_t ospi_periph, uint32_t abdtr);
/* configure wrap alternate bytes mode */
void ospi_wrap_alternate_byte_size_config(uint32_t ospi_periph, uint32_t altesz);
/* configure wrap data mode */
void ospi_wrap_data_mode_config(uint32_t ospi_periph, uint32_t datamod);
/* configure wrap data mode */
void ospi_wrap_data_dtr_config(uint32_t ospi_periph, uint32_t dadtr);

/* configure wrap dummy cycles number */
void ospi_wrap_dummy_cycles_config(uint32_t ospi_periph, uint32_t dumyc);
/* delay hold 1/4 cycle in wrap */
void ospi_wrap_delay_hold_cycle_config(uint32_t ospi_periph, uint32_t dehqc);
/* configure sample shift in wrap */
void ospi_wrap_sample_shift_config(uint32_t ospi_periph, uint32_t ssample);

/* OSPI write configure functions */
/* configure write instruction */
void ospi_write_instruction_config(uint32_t ospi_periph, uint32_t instruction);
/* configure write instruction mode */
void ospi_write_instruction_mode_config(uint32_t ospi_periph, uint32_t imod);
/* configure write instruction size */
void ospi_write_instruction_size_config(uint32_t ospi_periph, uint32_t inssz);
/* configure write address */
void ospi_write_address_config(uint32_t ospi_periph, uint32_t addr);
/* configure write address mode */
void ospi_write_address_mode_config(uint32_t ospi_periph, uint32_t addrmod);
/* configure write address dtr */
void ospi_write_address_dtr_config(uint32_t ospi_periph, uint32_t addrdtr);
/* configure write address size */
void ospi_write_address_size_config(uint32_t ospi_periph, uint32_t addrsz);
/* configure write alternate bytes mode */
void ospi_write_alternate_byte_config(uint32_t ospi_periph, uint32_t alte);
/* configure write alternate byte mode */
void ospi_write_alternate_byte_mode_config(uint32_t ospi_periph, uint32_t atlemod);
/* configure write alternate byte dtr */
void ospi_write_alternate_byte_dtr_config(uint32_t ospi_periph, uint32_t abdtr);
/* configure write alternate byte size */
void ospi_write_alternate_byte_size_config(uint32_t ospi_periph, uint32_t altesz);
/* configure write data mode */
void ospi_write_data_mode_config(uint32_t ospi_periph, uint32_t datamod);
/* configure write data dtr */
void ospi_write_data_dtr_config(uint32_t ospi_periph, uint32_t dadtr);
/* configure write dummy cycles number */
void ospi_write_dummy_cycles_config(uint32_t ospi_periph, uint32_t dumyc);

/* configure OSPI regular command parameter */
void ospi_command_config(uint32_t ospi_periph, ospi_parameter_struct *ospi_struct, ospi_regular_cmd_struct *cmd_struct);
/* transmit data */
void ospi_transmit(uint32_t ospi_periph, uint8_t *pdata);
/* receive data */
void ospi_receive(uint32_t ospi_periph, uint8_t *pdata);
/* configure the OSPI automatic polling mode */
void ospi_autopolling_mode(uint32_t ospi_periph, ospi_parameter_struct *ospi_struct, ospi_autopolling_struct *autopl_cfg_struct);

/* flag & interrupt functions */
/* enable OSPI interrupt */
void ospi_interrupt_enable(uint32_t ospi_periph, uint32_t interrupt);
/* disable OSPI interrupt */
void ospi_interrupt_disable(uint32_t ospi_periph, uint32_t interrupt);
/* get OSPI fifo level */
uint32_t ospi_fifo_level_get(uint32_t ospi_periph);
/* get OSPI flag status */
FlagStatus ospi_flag_get(uint32_t ospi_periph, uint32_t flag);
/* clear OSPI flag status */
void ospi_flag_clear(uint32_t ospi_periph, uint32_t flag);
/* get OSPI interrupt status */
FlagStatus ospi_interrupt_flag_get(uint32_t ospi_periph, uint32_t int_flag);
/* clear OSPI interrupt flag status */
void ospi_interrupt_flag_clear(uint32_t ospi_periph, uint32_t int_flag);

#endif /* GD32H7XX_OSPI_H */
