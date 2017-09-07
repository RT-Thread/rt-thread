#------------------------------------------------
# SDRAM initialization script for the ASM9260T
#------------------------------------------------

define __setup_PLL
	echo "Enabling PLL for CPU" \n
	
	# outl(1<<2, REG_SET(HW_AHBCLKCTRL0));
	set *0x80040024 = 0x00000004
	# outl(1<<8, REG_SET(HW_AHBCLKCTRL1));
	set *0x80040034 = 0x00000100
	# outl(3<<9, REG_SET(HW_AHBCLKCTRL0));
	set *0x80040024 = 0x00000600
	# outl(inl(HW_PDRUNCFG)&0xFFFFFFFA, HW_PDRUNCFG);
	set *0x80040238 = 0x00000770
	# outl(2, HW_CPUCLKDIV);
	set *0x8004017C = 0x00000002
	# outl(2, HW_SYSAHBCLKDIV);
	set *0x80040180 = 0x00000002
	# outl(480, HW_SYSPLLCTRL);
	set *0x80040100 = 0x000001E0
	# __delay(50)
	set $i = 0
	while $i != 500
		set $i += 1
	end
	# outl(1, HW_MAINCLKSEL);
	set *0x80040120 = 0x00000001
	# outl(0, HW_MAINCLKUEN);
	set *0x80040124 = 0x00000000
	# outl(1, HW_MAINCLKUEN);
	set *0x80040124 = 0x00000001
end

define __setup_SDRAM
  echo "Enabling on-chip SDRAM" \n

  # outl((1<<6), REG_SET(HW_AHBCLKCTRL0));
  set *0x80040024 = 0x00000040
  # outl(0x00001188, HW_EMI_SCONR);
  set *0x80700000 = 0x00001188
  # outl(0x000a0500, HW_EMI_CTRL);
  set *0x8004034c = 0x000a0500
  # outl(0x20000000, HW_EMI_SCSLR2_LOW);
  set *0x8070001c = 0x20000000
  # outl(0x0000000c, HW_EMI_SMSKR2);
  set *0x8070005c = 0x0000000c
  # outl(0x024996d9, HW_EMI_STMG0R);
  set *0x80700004 = 0x024996d9
  # outl(0x00542b4f, HW_EMI_SMTMGR_SET0);
  set *0x80700094 = 0x00542b4f
  # outl(0x00003288, HW_EMI_SCTLR);
  set *0x8070000c = 0x00003288
end

# Step1: Connect to the J-Link gdb server
define reset
	#target remote localhost:2331
	monitor reset

	# Step2: Reset peripheral  (RSTC_CR)
	echo "------- Prepare for debug ASM9260T -------" \n
	__setup_PLL
	__setup_SDRAM

	# Step3: Load file(eg. getting-started project)
	load

	mon reg pc=0x20000000
	#info reg
end