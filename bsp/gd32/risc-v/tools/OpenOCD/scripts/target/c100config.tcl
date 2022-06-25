
# board(-config) specific parameters file.

# set CFG_REFCLKFREQ [configC100 CFG_REFCLKFREQ]
proc config {label} {
    return [dict get [configC100] $label ]
}

# show the value for the param. with label
proc showconfig {label} {
    echo [format "0x%x" [dict get [configC100] $label ]]
}

# Telo board config
# when there are more then one board config
# use soft links to c100board-config.tcl
# so that only the right board-config gets
# included (just like include/configs/board-configs.h
# in u-boot.
proc configC100 {} {
    # xtal freq. 24MHz
    dict set configC100 CFG_REFCLKFREQ	         24000000

    # Amba Clk 165MHz
    dict set configC100 CONFIG_SYS_HZ_CLOCK      165000000
    dict set configC100 w_amba 1
    dict set configC100 x_amba 1
    # y = amba_clk * (w+1)*(x+1)*2/xtal_clk
    dict set configC100 y_amba [expr ([dict get $configC100 CONFIG_SYS_HZ_CLOCK] * ( ([dict get $configC100 w_amba]+1 ) * ([dict get $configC100 x_amba]+1 ) *2 ) / [dict get $configC100 CFG_REFCLKFREQ]) ]

    # Arm Clk 450MHz, must be a multiple of 25 MHz
    dict set configC100 CFG_ARM_CLOCK      450000000
    dict set configC100 w_arm 0
    dict set configC100 x_arm 1
    # y = arm_clk * (w+1)*(x+1)*2/xtal_clk
    dict set configC100 y_arm [expr ([dict get $configC100 CFG_ARM_CLOCK] * ( ([dict get $configC100 w_arm]+1 ) * ([dict get $configC100 x_arm]+1 ) *2 ) / [dict get $configC100 CFG_REFCLKFREQ]) ]


}

# This should be called for reset init event handler
proc setupTelo {} {

    # setup GPIO used as control signals for C100
    setupGPIO
    # This will allow acces to lower 8MB or NOR
    lowGPIO5
    # setup NOR size,timing,etc.
    setupNOR
    # setup internals + PLL + DDR2
    initC100
}


proc setupNOR {} {
    echo "Setting up NOR: 16MB, 16-bit wide bus, CS0"
    # this is taken from u-boot/boards/mindspeed/ooma-darwin/board.c:nor_hw_init()
    set EX_CSEN_REG	    [regs EX_CSEN_REG ]
    set EX_CS0_SEG_REG	    [regs EX_CS0_SEG_REG ]
    set EX_CS0_CFG_REG	    [regs EX_CS0_CFG_REG ]
    set EX_CS0_TMG1_REG	    [regs EX_CS0_TMG1_REG ]
    set EX_CS0_TMG2_REG	    [regs EX_CS0_TMG2_REG ]
    set EX_CS0_TMG3_REG	    [regs EX_CS0_TMG3_REG ]
    set EX_CLOCK_DIV_REG    [regs EX_CLOCK_DIV_REG ]
    set EX_MFSM_REG	    [regs EX_MFSM_REG ]
    set EX_CSFSM_REG	    [regs EX_CSFSM_REG ]
    set EX_WRFSM_REG	    [regs EX_WRFSM_REG ]
    set EX_RDFSM_REG	    [regs EX_RDFSM_REG ]

    # enable Expansion Bus Clock + CS0 (NOR)
    mww $EX_CSEN_REG 0x3
    # set the address space for CS0=16MB
    mww $EX_CS0_SEG_REG 0x7ff
    # set the CS0 bus width to 16-bit
    mww $EX_CS0_CFG_REG 0x202
    # set timings to NOR
    mww $EX_CS0_TMG1_REG 0x03034006
    mww $EX_CS0_TMG2_REG 0x04040002
    #mww $EX_CS0_TMG3_REG
    # set EBUS clock 165/5=33MHz
    mww $EX_CLOCK_DIV_REG 0x5
    # everthing else is OK with default
}

proc bootNOR {} {
    set EXP_CS0_BASEADDR       [regs EXP_CS0_BASEADDR]
    set BLOCK_RESET_REG	       [regs BLOCK_RESET_REG]
    set DDR_RST		       [regs DDR_RST]

    # put DDR controller in reset (so that it comes reset in u-boot)
    mmw $BLOCK_RESET_REG 0x0 $DDR_RST
    # setup CS0 controller for NOR
    setupNOR
    # make sure we are accessing the lower part of NOR
    lowGPIO5
    # set PC to start of NOR (at boot 0x20000000 = 0x0)
    reg pc $EXP_CS0_BASEADDR
    # run
    resume
}
proc setupGPIO {} {
    echo "Setting up GPIO block for Telo"
    # This is current setup for Telo (see sch. for details):
    #GPIO0 reset for FXS-FXO IC, leave as input, the IC has internal pullup
    #GPIO1 irq line for FXS-FXO
    #GPIO5 addr22 for NOR flash (access to upper 8MB)
    #GPIO17 reset for DECT module.
    #GPIO29 CS_n for NAND

    set GPIO_OUTPUT_REG		    [regs GPIO_OUTPUT_REG]
    set GPIO_OE_REG		    [regs GPIO_OE_REG]

    # set GPIO29=GPIO17=1, GPIO5=0
    mww $GPIO_OUTPUT_REG [expr 1<<29 | 1<<17]
    # enable [as output] GPIO29,GPIO17,GPIO5
    mww $GPIO_OE_REG [expr  1<<29 | 1<<17 | 1<<5]
}

proc highGPIO5 {} {
    echo "GPIO5 high"
    set GPIO_OUTPUT_REG		    [regs GPIO_OUTPUT_REG]
    # set GPIO5=1
    mmw $GPIO_OUTPUT_REG [expr 1 << 5] 0x0
}

proc lowGPIO5 {} {
    echo "GPIO5 low"
    set GPIO_OUTPUT_REG		    [regs GPIO_OUTPUT_REG]
    # set GPIO5=0
    mmw $GPIO_OUTPUT_REG 0x0 [expr 1 << 5]
}

proc boardID {id} {
    # so far built:
    # 4'b1111
    dict set boardID 15 name "EVT1"
    dict set boardID 15 ddr2size 128M
    # dict set boardID 15 nandsize 1G
    # dict set boardID 15 norsize 16M
    # 4'b0000
    dict set boardID 0 name "EVT2"
    dict set boardID 0 ddr2size 128M
    # 4'b0001
    dict set boardID 1 name "EVT3"
    dict set boardID 1 ddr2size 256M
    # 4'b1110
    dict set boardID 14 name "EVT3_old"
    dict set boardID 14 ddr2size 128M
    # 4'b0010
    dict set boardID 2 name "EVT4"
    dict set boardID 2 ddr2size 256M

    return $boardID
}


# converted from u-boot/boards/mindspeed/ooma-darwin/board.c:ooma_board_detect()
# figure out what board revision this is, uses BOOTSTRAP register to read stuffed resistors
proc ooma_board_detect {} {
    set GPIO_BOOTSTRAP_REG	[regs GPIO_BOOTSTRAP_REG]

    # read the current value of the BOOTSRAP pins
    set tmp [mrw $GPIO_BOOTSTRAP_REG]
    echo [format "GPIO_BOOTSTRAP_REG  (0x%x): 0x%x" $GPIO_BOOTSTRAP_REG $tmp]
    # extract the GPBP bits
    set gpbt [expr ($tmp &0x1C00) >> 10 | ($tmp & 0x40) >>3]

    # display board ID
    echo [format "This is %s (0x%x)" [dict get [boardID $gpbt] $gpbt name] $gpbt]
    # show it on serial console
    putsUART0 [format "This is %s (0x%x)\n" [dict get [boardID $gpbt] $gpbt name] $gpbt]
    # return the ddr2 size, used to configure DDR2 on a given board.
    return [dict get [boardID $gpbt] $gpbt ddr2size]
}

proc configureDDR2regs_256M {} {

    set DENALI_CTL_00_DATA    [regs DENALI_CTL_00_DATA]
    set DENALI_CTL_01_DATA    [regs DENALI_CTL_01_DATA]
    set DENALI_CTL_02_DATA    [regs DENALI_CTL_02_DATA]
    set DENALI_CTL_03_DATA    [regs DENALI_CTL_03_DATA]
    set DENALI_CTL_04_DATA    [regs DENALI_CTL_04_DATA]
    set DENALI_CTL_05_DATA    [regs DENALI_CTL_05_DATA]
    set DENALI_CTL_06_DATA    [regs DENALI_CTL_06_DATA]
    set DENALI_CTL_07_DATA    [regs DENALI_CTL_07_DATA]
    set DENALI_CTL_08_DATA    [regs DENALI_CTL_08_DATA]
    set DENALI_CTL_09_DATA    [regs DENALI_CTL_09_DATA]
    set DENALI_CTL_10_DATA    [regs DENALI_CTL_10_DATA]
    set DENALI_CTL_11_DATA    [regs DENALI_CTL_11_DATA]
    set DENALI_CTL_12_DATA    [regs DENALI_CTL_12_DATA]
    set DENALI_CTL_13_DATA    [regs DENALI_CTL_13_DATA]
    set DENALI_CTL_14_DATA    [regs DENALI_CTL_14_DATA]
    set DENALI_CTL_15_DATA    [regs DENALI_CTL_15_DATA]
    set DENALI_CTL_16_DATA    [regs DENALI_CTL_16_DATA]
    set DENALI_CTL_17_DATA    [regs DENALI_CTL_17_DATA]
    set DENALI_CTL_18_DATA    [regs DENALI_CTL_18_DATA]
    set DENALI_CTL_19_DATA    [regs DENALI_CTL_19_DATA]
    set DENALI_CTL_20_DATA    [regs DENALI_CTL_20_DATA]

    set DENALI_CTL_02_VAL 0x0100000000010100
    set DENALI_CTL_11_VAL 0x433a32164a560a00

    mw64bit $DENALI_CTL_00_DATA  0x0100000101010101
    # 01_DATA mod [40]=1, enable BA2
    mw64bit $DENALI_CTL_01_DATA  0x0100010100000001
    mw64bit $DENALI_CTL_02_DATA  $DENALI_CTL_02_VAL
    mw64bit $DENALI_CTL_03_DATA  0x0102020202020201
    mw64bit $DENALI_CTL_04_DATA  0x0000010100000001
    mw64bit $DENALI_CTL_05_DATA  0x0203010300010101
    mw64bit $DENALI_CTL_06_DATA  0x060a020200020202
    mw64bit $DENALI_CTL_07_DATA  0x0000000300000206
    mw64bit $DENALI_CTL_08_DATA  0x6400003f3f0a0209
    mw64bit $DENALI_CTL_09_DATA  0x1a000000001a1a1a
    mw64bit $DENALI_CTL_10_DATA  0x0120202020191a18
    # 11_DATA mod [39-32]=16,more refresh
    mw64bit $DENALI_CTL_11_DATA  $DENALI_CTL_11_VAL
    mw64bit $DENALI_CTL_12_DATA  0x0000000000000800
    mw64bit $DENALI_CTL_13_DATA  0x0010002000100040
    mw64bit $DENALI_CTL_14_DATA  0x0010004000100040
    mw64bit $DENALI_CTL_15_DATA  0x04f8000000000000
    mw64bit $DENALI_CTL_16_DATA  0x000000002cca0000
    mw64bit $DENALI_CTL_17_DATA  0x0000000000000000
    mw64bit $DENALI_CTL_18_DATA  0x0302000000000000
    mw64bit $DENALI_CTL_19_DATA  0x00001300c8030600
    mw64bit $DENALI_CTL_20_DATA  0x0000000081fe00c8

    set wr_dqs_shift 0x40
    # start DDRC
    mw64bit $DENALI_CTL_02_DATA [expr $DENALI_CTL_02_VAL | (1 << 32)]
    # wait int_status[2] (DRAM init complete)
    echo -n "Waiting for DDR2 controller to init..."
    set tmp [mrw [expr $DENALI_CTL_08_DATA + 4]]
    while { [expr $tmp & 0x040000] == 0 } {
	sleep 1
	set tmp [mrw [expr $DENALI_CTL_08_DATA + 4]]
    }
    echo "done."

    # do ddr2 training sequence
    # TBD (for now, if you need it, run trainDDR command)
}

# converted from u-boot/cpu/arm1136/comcerto/bsp100.c:config_board99()
# The values are computed based on Mindspeed and Nanya datasheets
proc configureDDR2regs_128M {} {

    set DENALI_CTL_00_DATA    [regs DENALI_CTL_00_DATA]
    set DENALI_CTL_01_DATA    [regs DENALI_CTL_01_DATA]
    set DENALI_CTL_02_DATA    [regs DENALI_CTL_02_DATA]
    set DENALI_CTL_03_DATA    [regs DENALI_CTL_03_DATA]
    set DENALI_CTL_04_DATA    [regs DENALI_CTL_04_DATA]
    set DENALI_CTL_05_DATA    [regs DENALI_CTL_05_DATA]
    set DENALI_CTL_06_DATA    [regs DENALI_CTL_06_DATA]
    set DENALI_CTL_07_DATA    [regs DENALI_CTL_07_DATA]
    set DENALI_CTL_08_DATA    [regs DENALI_CTL_08_DATA]
    set DENALI_CTL_09_DATA    [regs DENALI_CTL_09_DATA]
    set DENALI_CTL_10_DATA    [regs DENALI_CTL_10_DATA]
    set DENALI_CTL_11_DATA    [regs DENALI_CTL_11_DATA]
    set DENALI_CTL_12_DATA    [regs DENALI_CTL_12_DATA]
    set DENALI_CTL_13_DATA    [regs DENALI_CTL_13_DATA]
    set DENALI_CTL_14_DATA    [regs DENALI_CTL_14_DATA]
    set DENALI_CTL_15_DATA    [regs DENALI_CTL_15_DATA]
    set DENALI_CTL_16_DATA    [regs DENALI_CTL_16_DATA]
    set DENALI_CTL_17_DATA    [regs DENALI_CTL_17_DATA]
    set DENALI_CTL_18_DATA    [regs DENALI_CTL_18_DATA]
    set DENALI_CTL_19_DATA    [regs DENALI_CTL_19_DATA]
    set DENALI_CTL_20_DATA    [regs DENALI_CTL_20_DATA]


    set DENALI_CTL_02_VAL 0x0100010000010100
    set DENALI_CTL_11_VAL 0x433A42124A650A37
    # set some default values
    mw64bit $DENALI_CTL_00_DATA  0x0100000101010101
    mw64bit $DENALI_CTL_01_DATA  0x0100000100000101
    mw64bit $DENALI_CTL_02_DATA  $DENALI_CTL_02_VAL
    mw64bit $DENALI_CTL_03_DATA  0x0102020202020201
    mw64bit $DENALI_CTL_04_DATA  0x0201010100000201
    mw64bit $DENALI_CTL_05_DATA  0x0203010300010101
    mw64bit $DENALI_CTL_06_DATA  0x050A020200020202
    mw64bit $DENALI_CTL_07_DATA  0x000000030E0B0205
    mw64bit $DENALI_CTL_08_DATA  0x6427003F3F0A0209
    mw64bit $DENALI_CTL_09_DATA  0x1A00002F00001A00
    mw64bit $DENALI_CTL_10_DATA  0x01202020201A1A1A
    mw64bit $DENALI_CTL_11_DATA  $DENALI_CTL_11_VAL
    mw64bit $DENALI_CTL_12_DATA  0x0000080000000800
    mw64bit $DENALI_CTL_13_DATA  0x0010002000100040
    mw64bit $DENALI_CTL_14_DATA  0x0010004000100040
    mw64bit $DENALI_CTL_15_DATA  0x0508000000000000
    mw64bit $DENALI_CTL_16_DATA  0x000020472D200000
    mw64bit $DENALI_CTL_17_DATA  0x0000000008000000
    mw64bit $DENALI_CTL_18_DATA  0x0302000000000000
    mw64bit $DENALI_CTL_19_DATA  0x00001400C8030604
    mw64bit $DENALI_CTL_20_DATA  0x00000000823600C8

    set wr_dqs_shift 0x40
    # start DDRC
    mw64bit $DENALI_CTL_02_DATA [expr $DENALI_CTL_02_VAL | (1 << 32)]
    # wait int_status[2] (DRAM init complete)
    echo -n "Waiting for DDR2 controller to init..."
    set tmp [mrw [expr $DENALI_CTL_08_DATA + 4]]
    while { [expr $tmp & 0x040000] == 0 } {
	sleep 1
	set tmp [mrw [expr $DENALI_CTL_08_DATA + 4]]
    }
    # This is not necessary
    #mw64bit $DENALI_CTL_11_DATA [expr ($DENALI_CTL_11_VAL  & ~0x00007F0000000000) | ($wr_dqs_shift << 40) ]
    echo "done."

    # do ddr2 training sequence
    # TBD (for now, if you need it, run trainDDR command)
}



proc setupUART0 {} {
    # configure UART0 to 115200, 8N1
    set GPIO_LOCK_REG      [regs GPIO_LOCK_REG]
    set GPIO_IOCTRL_REG    [regs GPIO_IOCTRL_REG]
    set GPIO_IOCTRL_VAL    [regs GPIO_IOCTRL_VAL]
    set GPIO_IOCTRL_UART0  [regs GPIO_IOCTRL_UART0]
    set UART0_LCR	            [regs UART0_LCR]
    set LCR_DLAB		    [regs LCR_DLAB]
    set UART0_DLL		    [regs UART0_DLL]
    set UART0_DLH		    [regs UART0_DLH]
    set UART0_IIR		    [regs UART0_IIR]
    set UART0_IER		    [regs UART0_IER]
    set LCR_ONE_STOP		    [regs LCR_ONE_STOP]
    set LCR_CHAR_LEN_8		    [regs LCR_CHAR_LEN_8]
    set FCR_XMITRES		    [regs FCR_XMITRES]
    set FCR_RCVRRES		    [regs FCR_RCVRRES]
    set FCR_FIFOEN		    [regs FCR_FIFOEN]
    set IER_UUE			    [regs IER_UUE]

    # unlock writing to IOCTRL register
    mww $GPIO_LOCK_REG $GPIO_IOCTRL_VAL
    # enable UART0
    mmw $GPIO_IOCTRL_REG $GPIO_IOCTRL_UART0 0x0
    # baudrate  115200
    # This should really be amba_clk/(16*115200) but amba_clk=165MHz
    set tmp 89
    # Enable Divisor Latch access
    mmw  $UART0_LCR $LCR_DLAB 0x0
    # set the divisor to $tmp
    mww $UART0_DLL [expr $tmp & 0xff]
    mww $UART0_DLH [expr $tmp >> 8]
    # Disable Divisor Latch access
    mmw  $UART0_LCR 0x0 $LCR_DLAB
    # set the UART to 8N1
    mmw  $UART0_LCR [expr $LCR_ONE_STOP | $LCR_CHAR_LEN_8 ] 0x0
    # reset FIFO
    mmw  $UART0_IIR [expr $FCR_XMITRES  | $FCR_RCVRRES | $FCR_FIFOEN ] 0x0
    #  enable FFUART
    mww $UART0_IER $IER_UUE
}

proc putcUART0 {char} {

    set UART0_LSR	    [regs UART0_LSR]
    set UART0_THR	    [regs UART0_THR]
    set LSR_TEMT	    [regs LSR_TEMT]

    # convert the 'char' to digit
    set tmp [ scan $char %c ]
    # /* wait for room in the tx FIFO on FFUART */
    while {[expr [mrw $UART0_LSR] & $LSR_TEMT] == 0} { sleep 1 }
    mww $UART0_THR $tmp
    if { $char == "\n" } { putcUART0 \r }
}

proc putsUART0 {str} {
    set index 0
    set len [string length $str]
    while { $index < $len } {
	putcUART0 [string index $str $index]
	set index [expr $index + 1]
    }
}


proc trainDDR2 {} {
    set ARAM_BASEADDR	[regs ARAM_BASEADDR]

    # you must have run 'reset init' or u-boot
    # load the training code to ARAM
    load_image ./images/ddr2train.bin $ARAM_BASEADDR bin
    # set PC to start of NOR (at boot 0x20000000 = 0x0)
    reg pc $ARAM_BASEADDR
    # run
    resume
}

proc flashUBOOT {file} {
    # this will update uboot on NOR partition
    set EXP_CS0_BASEADDR       [regs EXP_CS0_BASEADDR]

    # setup CS0 controller for NOR
    setupNOR
    # make sure we are accessing the lower part of NOR
    lowGPIO5
    flash probe 0
    echo "Erasing sectors 0-3 for uboot"
    putsUART0 "Erasing sectors 0-3 for uboot\n"
    flash erase_sector 0 0 3
    echo "Programming u-boot"
    putsUART0 "Programming u-boot..."
    arm11 memwrite burst enable
    flash write_image $file $EXP_CS0_BASEADDR
    arm11 memwrite burst disable
    putsUART0 "done.\n"
    putsUART0 "Rebooting, please wait!\n"
    reboot
}
