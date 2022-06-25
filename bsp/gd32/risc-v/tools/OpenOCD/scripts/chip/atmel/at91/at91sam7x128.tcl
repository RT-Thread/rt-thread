source [find bitsbytes.tcl]
source [find cpu/arm/arm7tdmi.tcl]
source [find memory.tcl]
source [find mmr_helpers.tcl]

set CHIP_MAKER  atmel
set CHIP_FAMILY at91sam7
set CHIP_NAME   at91sam7x128
# how many flash regions.
set N_FLASH                1
set FLASH(0,CHIPSELECT)    -1
set FLASH(0,BASE)          0x00100000
set FLASH(0,LEN)           $__128K
set FLASH(0,HUMAN)         "internal flash"
set FLASH(0,TYPE)          "flash"
set FLASH(0,RWX)           $RWX_R_X
set FLASH(0,ACCESS_WIDTH)  $ACCESS_WIDTH_ANY
# how many ram regions.
set N_RAM                  1
set RAM(0,CHIPSELECT)      -1
set RAM(0,BASE)            0x00200000
set RAM(0,LEN)             $__32K
set RAM(0,HUMAN)           "internal ram"
set RAM(0,TYPE)            "ram"
set RAM(0,RWX)             $RWX_RWX
set RAM(0,ACCESS_WIDTH)    $ACCESS_WIDTH_ANY

# I AM LAZY... I create 1 region for all MMRs.
set N_MMREGS    1
set MMREGS(0,CHIPSELECT)      -1
set MMREGS(0,BASE)            0xfff00000
set MMREGS(0,LEN)             0x000fffff
set MMREGS(0,HUMAN)           "mm-regs"
set MMREGS(0,TYPE)            "mmr"
set MMREGS(0,RWX)             $RWX_RW
set MMREGS(0,ACCESS_WIDTH)    $ACCESS_WIDTH_ANY

# no external memory
set N_XMEM 0




set AT91C_BASE_SYS       0xFFFFF000
set AT91C_BASE_AIC       0xFFFFF000
set AT91C_BASE_PDC_DBGU  0xFFFFF300
set AT91C_BASE_DBGU      0xFFFFF200
set AT91C_BASE_PIOA      0xFFFFF400
set AT91C_BASE_PIOB      0xFFFFF600
set AT91C_BASE_CKGR      0xFFFFFC20
set AT91C_BASE_PMC       0xFFFFFC00
set AT91C_BASE_RSTC      0xFFFFFD00
set AT91C_BASE_RTTC      0xFFFFFD20
set AT91C_BASE_PITC      0xFFFFFD30
set AT91C_BASE_WDTC      0xFFFFFD40
set AT91C_BASE_VREG      0xFFFFFD60
set AT91C_BASE_MC        0xFFFFFF00
set AT91C_BASE_PDC_SPI1  0xFFFE4100
set AT91C_BASE_SPI1      0xFFFE4000
set AT91C_BASE_PDC_SPI0  0xFFFE0100
set AT91C_BASE_SPI0      0xFFFE0000
set AT91C_BASE_PDC_US1   0xFFFC4100
set AT91C_BASE_US1       0xFFFC4000
set AT91C_BASE_PDC_US0   0xFFFC0100
set AT91C_BASE_US0       0xFFFC0000
set AT91C_BASE_PDC_SSC   0xFFFD4100
set AT91C_BASE_SSC       0xFFFD4000
set AT91C_BASE_TWI       0xFFFB8000
set AT91C_BASE_PWMC_CH3  0xFFFCC260
set AT91C_BASE_PWMC_CH2  0xFFFCC240
set AT91C_BASE_PWMC_CH1  0xFFFCC220
set AT91C_BASE_PWMC_CH0  0xFFFCC200
set AT91C_BASE_PWMC      0xFFFCC000
set AT91C_BASE_UDP       0xFFFB0000
set AT91C_BASE_TC0       0xFFFA0000
set AT91C_BASE_TC1       0xFFFA0040
set AT91C_BASE_TC2       0xFFFA0080
set AT91C_BASE_TCB       0xFFFA0000
set AT91C_BASE_CAN_MB0   0xFFFD0200
set AT91C_BASE_CAN_MB1   0xFFFD0220
set AT91C_BASE_CAN_MB2   0xFFFD0240
set AT91C_BASE_CAN_MB3   0xFFFD0260
set AT91C_BASE_CAN_MB4   0xFFFD0280
set AT91C_BASE_CAN_MB5   0xFFFD02A0
set AT91C_BASE_CAN_MB6   0xFFFD02C0
set AT91C_BASE_CAN_MB7   0xFFFD02E0
set AT91C_BASE_CAN       0xFFFD0000
set AT91C_BASE_EMAC      0xFFFDC000
set AT91C_BASE_PDC_ADC   0xFFFD8100
set AT91C_BASE_ADC       0xFFFD8000

set AT91C_ID(0) FIQ
set AT91C_ID(1) SYS
set AT91C_ID(2) PIOA
set AT91C_ID(3) PIOB
set AT91C_ID(4) SPI0
set AT91C_ID(5) SPI1
set AT91C_ID(6) US0
set AT91C_ID(7) US1
set AT91C_ID(8) SSC
set AT91C_ID(9) TWI
set AT91C_ID(10) PWMC
set AT91C_ID(11) UDP
set AT91C_ID(12) TC0
set AT91C_ID(13) TC1
set AT91C_ID(14) TC2
set AT91C_ID(15) CAN
set AT91C_ID(16) EMAC
set AT91C_ID(17) ADC
set AT91C_ID(18) ""
set AT91C_ID(19) ""
set AT91C_ID(20) ""
set AT91C_ID(21) ""
set AT91C_ID(22) ""
set AT91C_ID(23) ""
set AT91C_ID(24) ""
set AT91C_ID(25) ""
set AT91C_ID(26) ""
set AT91C_ID(27) ""
set AT91C_ID(28) ""
set AT91C_ID(29) ""
set AT91C_ID(30) IRQ0
set AT91C_ID(31) IRQ1

source [find chip/atmel/at91/aic.tcl]
source [find chip/atmel/at91/usarts.tcl]
source [find chip/atmel/at91/pmc.tcl]
source [find chip/atmel/at91/rtt.tcl]
