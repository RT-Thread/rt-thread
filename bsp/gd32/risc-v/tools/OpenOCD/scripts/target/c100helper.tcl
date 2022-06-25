
proc helpC100 {} {
    echo "List of useful functions for C100 processor:"
    echo "1)  reset init:        will set up your Telo board"
    echo "2)  setupNOR:          will setup NOR access"
    echo "3)  showNOR:           will show current NOR config registers for 16-bit, 16MB NOR"
    echo "4)  setupGPIO:         will setup GPIOs for Telo board"
    echo "5)  showGPIO:          will show current GPIO config registers"
    echo "6)  highGPIO5:         will set GPIO5=NOR_addr22=1 to access upper 8MB"
    echo "7)  lowGPIO5:          will set GPIO5=NOR_addr22=0 to access lower 8MB"
    echo "8)  showAmbaClk:       will show current config registers for Amba Bus Clock"
    echo "9)  setupAmbaClk:      will setup Amba Bus Clock=165MHz"
    echo "10) showArmClk:        will show current config registers for Arm Bus Clock"
    echo "11) setupArmClk:       will setup Amba Bus Clock=450MHz"
    echo "12) ooma_board_detect: will show which version of Telo you have"
    echo "13) setupDDR2:         will configure DDR2 controller, you must have PLLs configureg"
    echo "14) showDDR2:          will show DDR2 config registers"
    echo "15) showWatchdog:      will show current register config for watchdog"
    echo "16) reboot:            will trigger watchdog and reboot Telo (hw reset)"
    echo "17) bootNOR:           will boot Telo from NOR"
    echo "18) setupUART0:        will configure UART0 for 115200 8N1, PLLs have to be confiured"
    echo "19) putcUART0:         will print a character on UART0"
    echo "20) putsUART0:         will print a string on UART0"
    echo "21) trainDDR2:          will run DDR2 training program"
    echo "22) flashUBOOT:        will prgram NOR sectors 0-3 with u-boot.bin"
}

source [find mem_helper.tcl]

# read a 64-bit register (memory mapped)
proc mr64bit {reg} {
    set value ""
    mem2array value 32 $reg 2
    return $value
}


# write a 64-bit register (memory mapped)
proc mw64bit {reg value} {
    set high [expr $value >> 32]
    set low  [expr $value & 0xffffffff]
    #echo [format "mw64bit(0x%x): 0x%08x%08x" $reg $high $low]
    mww $reg $low
    mww [expr $reg+4] $high
}


proc showNOR {} {
    echo "This is the current NOR setup"
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

    echo [format "EX_CSEN_REG      (0x%x): 0x%x" $EX_CSEN_REG [mrw $EX_CSEN_REG]]
    echo [format "EX_CS0_SEG_REG   (0x%x): 0x%x" $EX_CS0_SEG_REG [mrw $EX_CS0_SEG_REG]]
    echo [format "EX_CS0_CFG_REG   (0x%x): 0x%x" $EX_CS0_CFG_REG [mrw $EX_CS0_CFG_REG]]
    echo [format "EX_CS0_TMG1_REG  (0x%x): 0x%x" $EX_CS0_TMG1_REG [mrw $EX_CS0_TMG1_REG]]
    echo [format "EX_CS0_TMG2_REG  (0x%x): 0x%x" $EX_CS0_TMG2_REG [mrw $EX_CS0_TMG2_REG]]
    echo [format "EX_CS0_TMG3_REG  (0x%x): 0x%x" $EX_CS0_TMG3_REG [mrw $EX_CS0_TMG3_REG]]
    echo [format "EX_CLOCK_DIV_REG (0x%x): 0x%x" $EX_CLOCK_DIV_REG [mrw $EX_CLOCK_DIV_REG]]
    echo [format "EX_MFSM_REG      (0x%x): 0x%x" $EX_MFSM_REG [mrw $EX_MFSM_REG]]
    echo [format "EX_CSFSM_REG     (0x%x): 0x%x" $EX_CSFSM_REG [mrw $EX_CSFSM_REG]]
    echo [format "EX_WRFSM_REG     (0x%x): 0x%x" $EX_WRFSM_REG [mrw $EX_WRFSM_REG]]
    echo [format "EX_RDFSM_REG     (0x%x): 0x%x" $EX_RDFSM_REG [mrw $EX_RDFSM_REG]]
}



proc showGPIO {} {
    echo "This is the current GPIO register setup"
    # GPIO outputs register
    set GPIO_OUTPUT_REG		    [regs GPIO_OUTPUT_REG]
    # GPIO Output Enable register
    set GPIO_OE_REG		    [regs GPIO_OE_REG]
    set GPIO_HI_INT_ENABLE_REG	    [regs GPIO_HI_INT_ENABLE_REG]
    set GPIO_LO_INT_ENABLE_REG	    [regs GPIO_LO_INT_ENABLE_REG]
    # GPIO input register
    set GPIO_INPUT_REG		    [regs GPIO_INPUT_REG]
    set APB_ACCESS_WS_REG	    [regs APB_ACCESS_WS_REG]
    set MUX_CONF_REG		    [regs MUX_CONF_REG]
    set SYSCONF_REG		    [regs SYSCONF_REG]
    set GPIO_ARM_ID_REG		    [regs GPIO_ARM_ID_REG]
    set GPIO_BOOTSTRAP_REG	    [regs GPIO_BOOTSTRAP_REG]
    set GPIO_LOCK_REG		    [regs GPIO_LOCK_REG]
    set GPIO_IOCTRL_REG		    [regs GPIO_IOCTRL_REG]
    set GPIO_DEVID_REG		    [regs GPIO_DEVID_REG]

    echo [format "GPIO_OUTPUT_REG       (0x%x): 0x%x" $GPIO_OUTPUT_REG [mrw $GPIO_OUTPUT_REG]]
    echo [format "GPIO_OE_REG           (0x%x): 0x%x" $GPIO_OE_REG [mrw $GPIO_OE_REG]]
    echo [format "GPIO_HI_INT_ENABLE_REG(0x%x): 0x%x" $GPIO_HI_INT_ENABLE_REG [mrw $GPIO_HI_INT_ENABLE_REG]]
    echo [format "GPIO_LO_INT_ENABLE_REG(0x%x): 0x%x" $GPIO_LO_INT_ENABLE_REG [mrw $GPIO_LO_INT_ENABLE_REG]]
    echo [format "GPIO_INPUT_REG        (0x%x): 0x%x" $GPIO_INPUT_REG [mrw $GPIO_INPUT_REG]]
    echo [format "APB_ACCESS_WS_REG     (0x%x): 0x%x" $APB_ACCESS_WS_REG [mrw $APB_ACCESS_WS_REG]]
    echo [format "MUX_CONF_REG          (0x%x): 0x%x" $MUX_CONF_REG [mrw $MUX_CONF_REG]]
    echo [format "SYSCONF_REG           (0x%x): 0x%x" $SYSCONF_REG [mrw $SYSCONF_REG]]
    echo [format "GPIO_ARM_ID_REG       (0x%x): 0x%x" $GPIO_ARM_ID_REG [mrw $GPIO_ARM_ID_REG]]
    echo [format "GPIO_BOOTSTRAP_REG    (0x%x): 0x%x" $GPIO_BOOTSTRAP_REG [mrw $GPIO_BOOTSTRAP_REG]]
    echo [format "GPIO_LOCK_REG         (0x%x): 0x%x" $GPIO_LOCK_REG [mrw $GPIO_LOCK_REG]]
    echo [format "GPIO_IOCTRL_REG       (0x%x): 0x%x" $GPIO_IOCTRL_REG [mrw $GPIO_IOCTRL_REG]]
    echo [format "GPIO_DEVID_REG        (0x%x): 0x%x" $GPIO_DEVID_REG [mrw $GPIO_DEVID_REG]]
}



# converted from u-boot/cpu/arm1136/comcerto/bsp100.c (HAL_get_amba_clk())
proc showAmbaClk {} {
    set CFG_REFCLKFREQ		     [config CFG_REFCLKFREQ]
    set CLKCORE_AHB_CLK_CNTRL	     [regs CLKCORE_AHB_CLK_CNTRL]
    set PLL_CLK_BYPASS	             [regs PLL_CLK_BYPASS]

    echo [format "CLKCORE_AHB_CLK_CNTRL       (0x%x): 0x%x" $CLKCORE_AHB_CLK_CNTRL [mrw $CLKCORE_AHB_CLK_CNTRL]]
    mem2array value 32 $CLKCORE_AHB_CLK_CNTRL 1
    # see if the PLL is in bypass mode
    set bypass [expr ($value(0) & $PLL_CLK_BYPASS) >> 24 ]
    echo [format "PLL bypass bit: %d" $bypass]
    if {$bypass == 1} {
	echo [format "Amba Clk is set to REFCLK: %d (MHz)" [expr $CFG_REFCLKFREQ/1000000]]
    } else {
	# nope, extract x,y,w and compute the PLL output freq.
	set x [expr ($value(0) & 0x0001F0000) >> 16]
	echo [format "x: %d" $x]
	set y [expr ($value(0) & 0x00000007F)]
	echo [format "y: %d" $y]
	set w [expr ($value(0) & 0x000000300) >> 8]
	echo [format "w: %d" $w]
	echo [format "Amba PLL Clk: %d (MHz)" [expr ($CFG_REFCLKFREQ * $y / (($w + 1) * ($x + 1) * 2))/1000000]]
    }
}


# converted from u-boot/cpu/arm1136/comcerto/bsp100.c (HAL_set_amba_clk())
# this clock is useb by all peripherals (DDR2, ethernet, ebus, etc)
proc setupAmbaClk {} {
    set CLKCORE_PLL_STATUS           [regs CLKCORE_PLL_STATUS]
    set CLKCORE_AHB_CLK_CNTRL	     [regs CLKCORE_AHB_CLK_CNTRL]
    set ARM_PLL_BY_CTRL	    [regs ARM_PLL_BY_CTRL]
    set ARM_AHB_BYP	    [regs ARM_AHB_BYP]
    set PLL_DISABLE	    [regs PLL_DISABLE]
    set PLL_CLK_BYPASS	    [regs PLL_CLK_BYPASS]
    set AHB_PLL_BY_CTRL	    [regs AHB_PLL_BY_CTRL]
    set DIV_BYPASS	    [regs DIV_BYPASS]
    set AHBCLK_PLL_LOCK	    [regs AHBCLK_PLL_LOCK]
    set CFG_REFCLKFREQ		 [config CFG_REFCLKFREQ]
    set CONFIG_SYS_HZ_CLOCK      [config CONFIG_SYS_HZ_CLOCK]
    set w    [config w_amba]
    set x    [config x_amba]
    set y    [config y_amba]

    echo [format "Setting Amba PLL to lock to %d MHz" [expr $CONFIG_SYS_HZ_CLOCK/1000000]]
    #echo [format "setupAmbaClk: w= %d" $w]
    #echo [format "setupAmbaClk: x= %d" $x]
    #echo [format "setupAmbaClk: y= %d" $y]
    # set PLL into BYPASS mode using MUX
    mmw $CLKCORE_AHB_CLK_CNTRL $PLL_CLK_BYPASS 0x0
    # do an internal PLL bypass
    mmw $CLKCORE_AHB_CLK_CNTRL $AHB_PLL_BY_CTRL 0x0
    # wait 500us (ARM running @24Mhz -> 12000 cycles => 500us)
    # openocd smallest resolution is 1ms so, wait 1ms
    sleep 1
    # disable the PLL
    mmw $CLKCORE_AHB_CLK_CNTRL $PLL_DISABLE 0x0
    # wait 1ms
    sleep 1
    # enable the PLL
    mmw $CLKCORE_AHB_CLK_CNTRL 0x0 $PLL_DISABLE
    sleep 1
    # set X, W and X
    mmw $CLKCORE_AHB_CLK_CNTRL 0x0 0xFFFFFF
    mmw $CLKCORE_AHB_CLK_CNTRL [expr (($x << 16) + ($w << 8) + $y)] 0x0
    # wait for PLL to lock
    echo "Waiting for Amba PLL to lock"
    while {[expr [mrw $CLKCORE_PLL_STATUS] & $AHBCLK_PLL_LOCK] == 0} { sleep 1 }
    # remove the internal PLL bypass
    mmw $CLKCORE_AHB_CLK_CNTRL 0x0 $AHB_PLL_BY_CTRL
    # remove PLL from BYPASS mode using MUX
    mmw $CLKCORE_AHB_CLK_CNTRL 0x0 $PLL_CLK_BYPASS
}


# converted from u-boot/cpu/arm1136/comcerto/bsp100.c (HAL_get_arm_clk())
proc showArmClk {} {
    set CFG_REFCLKFREQ		[config CFG_REFCLKFREQ]
    set CLKCORE_ARM_CLK_CNTRL	[regs CLKCORE_ARM_CLK_CNTRL]
    set PLL_CLK_BYPASS	        [regs PLL_CLK_BYPASS]

    echo [format "CLKCORE_ARM_CLK_CNTRL       (0x%x): 0x%x" $CLKCORE_ARM_CLK_CNTRL [mrw $CLKCORE_ARM_CLK_CNTRL]]
    mem2array value 32 $CLKCORE_ARM_CLK_CNTRL 1
    # see if the PLL is in bypass mode
    set bypass [expr ($value(0) & $PLL_CLK_BYPASS) >> 24 ]
    echo [format "PLL bypass bit: %d" $bypass]
    if {$bypass == 1} {
	echo [format "Amba Clk is set to REFCLK: %d (MHz)" [expr $CFG_REFCLKFREQ/1000000]]
    } else {
	# nope, extract x,y,w and compute the PLL output freq.
	set x [expr ($value(0) & 0x0001F0000) >> 16]
	echo [format "x: %d" $x]
	set y [expr ($value(0) & 0x00000007F)]
	echo [format "y: %d" $y]
	set w [expr ($value(0) & 0x000000300) >> 8]
	echo [format "w: %d" $w]
	echo [format "Arm PLL Clk: %d (MHz)" [expr ($CFG_REFCLKFREQ * $y / (($w + 1) * ($x + 1) * 2))/1000000]]
    }
}

# converted from u-boot/cpu/arm1136/comcerto/bsp100.c (HAL_set_arm_clk())
# Arm Clock is used by two ARM1136 cores
proc setupArmClk {} {
    set CLKCORE_PLL_STATUS        [regs CLKCORE_PLL_STATUS]
    set CLKCORE_ARM_CLK_CNTRL	  [regs CLKCORE_ARM_CLK_CNTRL]
    set ARM_PLL_BY_CTRL	          [regs ARM_PLL_BY_CTRL]
    set ARM_AHB_BYP	          [regs ARM_AHB_BYP]
    set PLL_DISABLE	          [regs PLL_DISABLE]
    set PLL_CLK_BYPASS	          [regs PLL_CLK_BYPASS]
    set AHB_PLL_BY_CTRL	          [regs AHB_PLL_BY_CTRL]
    set DIV_BYPASS	          [regs DIV_BYPASS]
    set FCLK_PLL_LOCK	          [regs FCLK_PLL_LOCK]
    set CFG_REFCLKFREQ		[config CFG_REFCLKFREQ]
    set CFG_ARM_CLOCK		[config CFG_ARM_CLOCK]
    set w    [config w_arm]
    set x    [config x_arm]
    set y    [config y_arm]

    echo [format "Setting Arm PLL to lock to %d MHz" [expr $CFG_ARM_CLOCK/1000000]]
    #echo [format "setupArmClk: w= %d" $w]
    #echo [format "setupArmaClk: x= %d" $x]
    #echo [format "setupArmaClk: y= %d" $y]
    # set PLL into BYPASS mode using MUX
    mmw $CLKCORE_ARM_CLK_CNTRL $PLL_CLK_BYPASS 0x0
    # do an internal PLL bypass
    mmw $CLKCORE_ARM_CLK_CNTRL $ARM_PLL_BY_CTRL 0x0
    # wait 500us (ARM running @24Mhz -> 12000 cycles => 500us)
    # openocd smallest resolution is 1ms so, wait 1ms
    sleep 1
    # disable the PLL
    mmw $CLKCORE_ARM_CLK_CNTRL $PLL_DISABLE 0x0
    # wait 1ms
    sleep 1
    # enable the PLL
    mmw $CLKCORE_ARM_CLK_CNTRL 0x0 $PLL_DISABLE
    sleep 1
    # set X, W and X
    mmw $CLKCORE_ARM_CLK_CNTRL 0x0 0xFFFFFF
    mmw $CLKCORE_ARM_CLK_CNTRL [expr (($x << 16) + ($w << 8) + $y)] 0x0
    # wait for PLL to lock
    echo "Waiting for Amba PLL to lock"
    while {[expr [mrw $CLKCORE_PLL_STATUS] & $FCLK_PLL_LOCK] == 0} { sleep 1 }
    # remove the internal PLL bypass
    mmw $CLKCORE_ARM_CLK_CNTRL 0x0 $ARM_PLL_BY_CTRL
    # remove PLL from BYPASS mode using MUX
    mmw $CLKCORE_ARM_CLK_CNTRL 0x0 $PLL_CLK_BYPASS
}



proc setupPLL {} {
    echo "PLLs setup"
    setupAmbaClk
    setupArmClk
}

# converted from u-boot/cpu/arm1136/bsp100.c:SoC_mem_init()
proc setupDDR2 {} {
    echo "Configuring DDR2"

    set MEMORY_BASE_ADDR	    [regs  MEMORY_BASE_ADDR]
    set MEMORY_MAX_ADDR	            [regs  MEMORY_MAX_ADDR]
    set MEMORY_CR 		    [regs  MEMORY_CR]
    set BLOCK_RESET_REG		    [regs  BLOCK_RESET_REG]
    set DDR_RST		            [regs  DDR_RST]

    # put DDR controller in reset (so that it is reset and correctly configured)
    # this is only necessary if DDR was previously confiured
    # and not reset.
    mmw $BLOCK_RESET_REG 0x0 $DDR_RST

    set M [expr 1024 * 1024]
    set DDR_SZ_1024M	[expr 1024 * $M]
    set DDR_SZ_256M	[expr 256 * $M]
    set DDR_SZ_128M	[expr 128 * $M]
    set DDR_SZ_64M	[expr 64 * $M]
    # ooma_board_detect returns DDR2 memory size
    set tmp [ooma_board_detect]
    if {$tmp == "128M"} {
	echo "DDR2 size 128MB"
	set ddr_size $DDR_SZ_128M
    } elseif {$tmp == "256M"} {
	echo "DDR2 size 256MB"
	set ddr_size $DDR_SZ_256M
    } else {
	echo "Don't know how to handle this DDR2 size?"
    }

    # Memory setup register
    mww $MEMORY_MAX_ADDR  [expr ($ddr_size - 1) + $MEMORY_BASE_ADDR]
    # disable ROM remap
    mww $MEMORY_CR 0x0
    # Take DDR controller out of reset
    mmw $BLOCK_RESET_REG $DDR_RST 0x0
    # min. 20 ops delay
    sleep 1

    # This will setup Denali DDR2 controller
    if {$tmp == "128M"} {
	configureDDR2regs_128M
    } elseif {$tmp == "256M"} {
	configureDDR2regs_256M
    } else {
	echo "Don't know how to configure DDR2 setup?"
    }
}



proc showDDR2 {} {

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

    set tmp [mr64bit $DENALI_CTL_00_DATA]
    echo [format "DENALI_CTL_00_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_00_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_01_DATA]
    echo [format "DENALI_CTL_01_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_01_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_02_DATA]
    echo [format "DENALI_CTL_02_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_02_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_03_DATA]
    echo [format "DENALI_CTL_03_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_03_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_04_DATA]
    echo [format "DENALI_CTL_04_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_04_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_05_DATA]
    echo [format "DENALI_CTL_05_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_05_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_06_DATA]
    echo [format "DENALI_CTL_06_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_06_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_07_DATA]
    echo [format "DENALI_CTL_07_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_07_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_08_DATA]
    echo [format "DENALI_CTL_08_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_08_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_09_DATA]
    echo [format "DENALI_CTL_09_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_09_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_10_DATA]
    echo [format "DENALI_CTL_10_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_10_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_11_DATA]
    echo [format "DENALI_CTL_11_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_11_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_12_DATA]
    echo [format "DENALI_CTL_12_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_12_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_13_DATA]
    echo [format "DENALI_CTL_13_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_13_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_14_DATA]
    echo [format "DENALI_CTL_14_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_14_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_15_DATA]
    echo [format "DENALI_CTL_15_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_15_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_16_DATA]
    echo [format "DENALI_CTL_16_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_16_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_17_DATA]
    echo [format "DENALI_CTL_17_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_17_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_18_DATA]
    echo [format "DENALI_CTL_18_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_18_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_19_DATA]
    echo [format "DENALI_CTL_19_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_19_DATA $tmp(1) $tmp(0)]
    set tmp [mr64bit $DENALI_CTL_20_DATA]
    echo [format "DENALI_CTL_20_DATA   (0x%x): 0x%08x%08x" $DENALI_CTL_20_DATA $tmp(1) $tmp(0)]

}

proc initC100 {} {
    # this follows u-boot/cpu/arm1136/start.S
    set GPIO_LOCK_REG		    [regs GPIO_LOCK_REG]
    set GPIO_IOCTRL_REG		    [regs GPIO_IOCTRL_REG]
    set GPIO_IOCTRL_VAL	            [regs GPIO_IOCTRL_VAL]
    set APB_ACCESS_WS_REG           [regs APB_ACCESS_WS_REG]
    set ASA_ARAM_BASEADDR	    [regs ASA_ARAM_BASEADDR]
    set ASA_ARAM_TC_CR_REG	    [regs ASA_ARAM_TC_CR_REG]
    set ASA_EBUS_BASEADDR	    [regs ASA_EBUS_BASEADDR]
    set ASA_EBUS_TC_CR_REG	    [regs ASA_EBUS_TC_CR_REG]
    set ASA_TC_REQIDMAEN	    [regs ASA_TC_REQIDMAEN]
    set ASA_TC_REQTDMEN	            [regs ASA_TC_REQTDMEN]
    set ASA_TC_REQIPSECUSBEN        [regs ASA_TC_REQIPSECUSBEN]
    set ASA_TC_REQARM0EN	    [regs ASA_TC_REQARM0EN]
    set ASA_TC_REQARM1EN	    [regs ASA_TC_REQARM1EN]
    set ASA_TC_REQMDMAEN	    [regs ASA_TC_REQMDMAEN]
    set INTC_ARM1_CONTROL_REG       [regs INTC_ARM1_CONTROL_REG]


    # unlock writing to IOCTRL register
    mww $GPIO_LOCK_REG $GPIO_IOCTRL_VAL
    # enable address lines A15-A21
    mmw $GPIO_IOCTRL_REG 0xf 0x0
    # set ARM into supervisor mode (SVC32)
    # disable IRQ, FIQ
    # Do I need this in JTAG mode?
    # it really should be done as 'and ~0x1f | 0xd3 but
    # openocd does not support this yet
    reg cpsr 0xd3
    #	/*
    #	 * flush v4 I/D caches
    #	 */
    #	mov	r0, #0
    #	mcr	p15, 0, r0, c7, c7, 0	/* flush v3/v4 cache */
    arm mcr 15 0 7 7 0 0x0
    #	mcr	p15, 0, r0, c8, c7, 0	/* flush v4 TLB */
    arm mcr 15 0 8 7 0 0x0

    #	/*
    #	 * disable MMU stuff and caches
    #	 */
    #	mrc	p15, 0, r0, c1, c0, 0
    arm mrc 15 0 1 0 0
    #	bic	r0, r0, #0x00002300	@ clear bits 13, 9:8 (--V- --RS)
    #	bic	r0, r0, #0x00000087	@ clear bits 7, 2:0 (B--- -CAM)
    #	orr	r0, r0, #0x00000002	@ set bit 2 (A) Align
    #	orr	r0, r0, #0x00001000	@ set bit 12 (I) I-Cache
    #	orr	r0, r0, #0x00400000	@ set bit 22 (U)
    #	mcr	p15, 0, r0, c1, c0, 0
    arm mcr 15 0 1 0 0 0x401002
    # This is from bsp_init() in u-boot/boards/mindspeed/ooma-darwin/board.c
    # APB init
    #    	// Setting APB Bus Wait states to 1, set post write
    #	(*(volatile u32*)(APB_ACCESS_WS_REG)) = 0x40;
    mww [expr $APB_ACCESS_WS_REG] 0x40
    # AHB init
    #	// enable all 6 masters for ARAM
    mmw $ASA_ARAM_TC_CR_REG [expr $ASA_TC_REQIDMAEN | $ASA_TC_REQTDMEN | $ASA_TC_REQIPSECUSBEN | $ASA_TC_REQARM0EN | $ASA_TC_REQARM1EN | $ASA_TC_REQMDMAEN] 0x0
    #	// enable all 6 masters for EBUS
    mmw $ASA_EBUS_TC_CR_REG [expr $ASA_TC_REQIDMAEN | $ASA_TC_REQTDMEN | $ASA_TC_REQIPSECUSBEN | $ASA_TC_REQARM0EN | $ASA_TC_REQARM1EN | $ASA_TC_REQMDMAEN] 0x0

    # ARAM init
    #	// disable pipeline mode in ARAM
    # I don't think this is documented anywhere?
    mww $INTC_ARM1_CONTROL_REG 0x1
    # configure clocks
    setupPLL
    # setupUART0 must be run before setupDDR2 as setupDDR2 uses UART.
    setupUART0
    # enable cache
    # ? (u-boot does nothing here)
    # DDR2 memory init
    setupDDR2
    putsUART0 "C100 initialization complete.\n"
    echo "C100 initialization complete."
}

# show current state of watchdog timer
proc showWatchdog {} {
    set TIMER_WDT_HIGH_BOUND	[regs TIMER_WDT_HIGH_BOUND]
    set TIMER_WDT_CONTROL	[regs TIMER_WDT_CONTROL]
    set TIMER_WDT_CURRENT_COUNT	[regs TIMER_WDT_CURRENT_COUNT]

    echo [format "TIMER_WDT_HIGH_BOUND    (0x%x): 0x%x" $TIMER_WDT_HIGH_BOUND [mrw $TIMER_WDT_HIGH_BOUND]]
    echo [format "TIMER_WDT_CONTROL       (0x%x): 0x%x" $TIMER_WDT_CONTROL [mrw $TIMER_WDT_CONTROL]]
    echo [format "TIMER_WDT_CURRENT_COUNT (0x%x): 0x%x" $TIMER_WDT_CURRENT_COUNT [mrw $TIMER_WDT_CURRENT_COUNT]]
}

# converted from u-boot/cpu/arm1136/comcerto/intrrupts.c:void reset_cpu (ulong ignored)
# this will trigger watchdog reset
# the sw. reset does not work on C100
# watchdog reset effectively works as hw. reset
proc reboot {} {
    set TIMER_WDT_HIGH_BOUND	[regs TIMER_WDT_HIGH_BOUND]
    set TIMER_WDT_CONTROL	[regs TIMER_WDT_CONTROL]
    set TIMER_WDT_CURRENT_COUNT	[regs TIMER_WDT_CURRENT_COUNT]

    # allow the counter to count to high value  before triggering
    # this is because register writes are slow over JTAG and
    # I don't want to miss the high_bound==curr_count condition
    mww $TIMER_WDT_HIGH_BOUND  0xffffff
    mww $TIMER_WDT_CURRENT_COUNT 0x0
    echo "JTAG speed lowered to 100kHz"
    adapter speed 100
    mww $TIMER_WDT_CONTROL 0x1
    # wait until the reset
    echo -n "Waiting for watchdog to trigger..."
    #while {[mrw $TIMER_WDT_CONTROL] == 1} {
    #    echo [format "TIMER_WDT_CURRENT_COUNT (0x%x): 0x%x" $TIMER_WDT_CURRENT_COUNT [mrw $TIMER_WDT_CURRENT_COUNT]]
    #    sleep 1
    #
    #}
    while {[c100.cpu curstate] != "running"} { sleep 1}
    echo "done."
    echo [format "Note that C100 is in %s state, type halt to stop" [c100.cpu curstate]]
}
