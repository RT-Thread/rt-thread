#------------------------------------------------
# SDRAM initialization script for the AT91SAM9260
#------------------------------------------------

#----------------------------------------------------------------------------
# _InitRSTC()
# Function description
#   Initializes the RSTC (Reset controller).
#   This makes sense since the default is to not allow user resets, which makes it impossible to
#   apply a second RESET via J-Link
#----------------------------------------------------------------------------

define _InitRSTC
	# Allow user reset
    set *0xFFFFFD08=0xA5000001    
end

#----------------------------------------------------------------------------
# _MapRAMAt0()
# Function description: Maps RAM at 0.
#----------------------------------------------------------------------------
define _MapRAMAt0
    echo "---------- SRAM remapped to 0 --------" \n
    # Test and set Remap
    set $__mac_i = *0xFFFFEF00
    if ( (($__mac_i & 0x01) == 0) || (($__mac_i & 0x02) == 0))
		#toggle remap bits
		set *0xFFFFEF00 = 0x03 
    else
        echo "---------- The Remap is done ---------" \n
	end
end

#----------------------------------------------------------------------------
#
#  _PllSetting()
#  Function description
#  Initializes the PMC.
#  1. Enable the Main Oscillator
#  2. Configure PLL
#  3. Switch Master
#----------------------------------------------------------------------------

define __PllSetting
    if ((*(0xFFFFFC30)&0x3) != 0 ) 
		# Disable all PMC interrupt ( $$ JPP)
		# AT91C_PMC_IDR   ((AT91_REG *) 0xFFFFFC64) #(PMC) Interrupt Disable Register
		# pPmc->PMC_IDR = 0xFFFFFFFF;
	    set *0xFFFFFC64 = 0xFFFFFFFF
		# AT91C_PMC_PCDR  ((AT91_REG *) 0xFFFFFC14) #(PMC) Peripheral Clock Disable Register
	    set *0xFFFFFC14 = 0xFFFFFFFF
		# Disable all clock only Processor clock is enabled.
	    set *0xFFFFFC04 = 0xFFFFFFFE
		# AT91C_PMC_MCKR  ((AT91_REG *) 	0xFFFFFC30) # (PMC) Master Clock Register
	    set *0xFFFFFC30 = 0x00000001

		while ((*0xFFFFFC68 & 0x8) == 0)
		end

	    
		# write reset value to PLLA and PLLB
	    # AT91C_PMC_PLLAR ((AT91_REG *) 	0xFFFFFC28) # (PMC) PLL A Register
	    set *0xFFFFFC28 = 0x00003F00
	
	    # AT91C_PMC_PLLBR ((AT91_REG *) 	0xFFFFFC2C) # (PMC) PLL B Register
	    set *0xFFFFFC2C 0x00003F00
	    while ((*0xFFFFFC68 & 0x2) == 0)
		end
		while ((*0xFFFFFC68 & 0x4) == 0)
		end
	
	    echo "---------- PLL  Enable ---------------" \n
    
    else 
   		echo "---------- Core in SLOW CLOCK mode ---" \n
	end
end


#----------------------------------------------------------------------------
#
#      __PllSetting100MHz()
# Function description
#  Set core at 200 MHz and MCK at 100 MHz 
#----------------------------------------------------------------------------

define __PllSetting100MHz
	echo "---------- PLL Set at 100 MHz --------" \n

	#* pPmc->PMC_MOR = (( AT91C_CKGR_OSCOUNT & (0x40 <<8) | AT91C_CKGR_MOSCEN ));
    set *0xFFFFFC20=0x00004001
	    while ((*0xFFFFFC68 & 0x1) == 0)
		end
	# AT91C_PMC_MCKR  ((AT91_REG *) 	0xFFFFFC30) # (PMC) Master Clock Register
    set *0xFFFFFC30=0x00000001
	    while ((*0xFFFFFC68 & 0x8) == 0)
		end
	#*   AT91C_BASE_CKGR->CKGR_PLLAR = (AT91C_CKGR_SRCA | ((96 << 16) & AT91C_CKGR_MULA) | 
	#    (AT91C_CKGR_PLLACOUNT | (AT91C_CKGR_OUTA_0 | (9);
    set *0xFFFFFC28=0x2060BF09
	    while ((*0xFFFFFC68 & 0x2) == 0)
		end
    # Configure PLLB
    set *0xFFFFFC2C=0x207C3F0C
	    while ((*0xFFFFFC68 & 0x4) == 0)
		end
	#*   AT91C_BASE_PMC->PMC_MCKR =  AT91C_PMC_CSS_PLLA_CLK | AT91C_PMC_PRES_CLK | AT91C_PMC_MDIV_2;;
    set *0xFFFFFC30=0x00000102
     	while ((*0xFFFFFC68 & 0x8) == 0)
		end
end


#----------------------------------------------------------------------------
#      __initSDRAM()
#  Function description
#  Set SDRAM for works at 100 MHz
#----------------------------------------------------------------------------

define __initSDRAM

    # Configure EBI Chip select	
    # pCCFG->CCFG_EBICSA |= AT91C_EBI_CS1A_SDRAMC;
    # AT91C_CCFG_EBICSA ((AT91_REG *) 	0xFFFFEF1C) # (CCFG)  EBI Chip Select Assignement Register
    set *0xFFFFEF1C=0x0001003A
    
    # Configure PIOs
    # AT91F_PIO_CfgPeriph( AT91C_BASE_PIOC, AT91C_PC16_D16 to AT91C_PC16_D31
    # pPio->PIO_ASR = periphAEnable; AT91C_PIOC_ASR ((AT91_REG *) 0xFFFFF870) # (PIOC) Select A Register
    # pPio->PIO_BSR = periphBEnable;AT91C_PIOC_BSR  ((AT91_REG *) 0xFFFFF874) # (PIOC) Select B Register
    # pPio->PIO_PDR = (periphAEnable | periphBEnable # Set in Periph mode
    set *0xFFFFF870=0xFFFF0000
    set *0xFFFFF874=0x00000000
    set *0xFFFFF804=0xFFFF0000
    
    # psdrc->SDRAMC_CR =  AT91C_SDRAMC_NC_9  | AT91C_SDRAMC_NR_13 | AT91C_SDRAMC_CAS_2 |
    # AT91C_SDRAMC_NB_4_BANKS | AT91C_SDRAMC_DBW_32_BITS | AT91C_SDRAMC_TWR_2 | AT91C_SDRAMC_TRC_7 |
    # AT91C_SDRAMC_TRP_2 | AT91C_SDRAMC_TRCD_2 | AT91C_SDRAMC_TRAS_5 | AT91C_SDRAMC_TXSR_8 ;
    set *0xFFFFEA08=0x85227259
	set $i = 0
	while $i != 100
	  set $i += 1
	end
    # psdrc->SDRAMC_MR	= 0x00000002;		# Set PRCHG AL
    set *0xFFFFEA00=0x00000002
    # *AT91C_SDRAM	= 0x00000000;			# Perform PRCHG
    set *0x20000000=0x00000000
	set $i = 0
	while $i != 100
	  set $i += 1
	end

    # psdrc->SDRAMC_MR	= AT91C_SDRAMC_MODE_RFSH_CMD;		# Set 1st CBR
    set *0xFFFFEA00=0x00000004
    
    # *(AT91C_SDRAM+4)	= 0x00000001;	# Perform CBR
    set *0x20000010=0x00000001
    
    # psdrc->SDRAMC_MR	= 0x00000004;		# Set 2 CBR
    set *0xFFFFEA00=0x00000004
    # *(AT91C_SDRAM+8)	= 0x00000002;	# Perform CBR
    set *0x20000020=0x00000002
    
    # psdrc->SDRAMC_MR	= AT91C_SDRAMC_MODE_RFSH_CMD;		# Set 3 CBR
    set *0xFFFFEA00=0x00000004
    # *(AT91C_SDRAM+0xc)	= 0x00000003;	# Perform CBR
    set *0x20000030=0x00000003
       
    # psdrc->SDRAMC_MR	= AT91C_SDRAMC_MODE_RFSH_CMD;		# Set 4 CBR
    set *0xFFFFEA00=0x00000004
    # *(AT91C_SDRAM+0x10)	= 0x00000004;	# Perform CBR
    set *0x20000040=0x00000004
       
    # psdrc->SDRAMC_MR	= AT91C_SDRAMC_MODE_RFSH_CMD;		# Set 5 CBR
    set *0xFFFFEA00=0x00000004
    # *(AT91C_SDRAM+0x14)	= 0x00000005;	# Perform CBR
    set *0x20000050=0x00000005
       
    # psdrc->SDRAMC_MR	= AT91C_SDRAMC_MODE_RFSH_CMD;		# Set 6 CBR
    set *0xFFFFEA00=0x00000004
    # *(AT91C_SDRAM+0x18)	= 0x00000006;	# Perform CBR
    set *0x20000060=0x00000006
       
    # psdrc->SDRAMC_MR	= AT91C_SDRAMC_MODE_RFSH_CMD;		# Set 7 CBR
    set *0xFFFFEA00=0x00000004
    # *(AT91C_SDRAM+0x1c)	= 0x00000007;	# Perform CBR
    set *0x20000070=0x00000007
       
    # psdrc->SDRAMC_MR	= AT91C_SDRAMC_MODE_RFSH_CMD;		# Set 8 CBR
    set *0xFFFFEA00=0x00000004
    # *(AT91C_SDRAM+0x20)	= 0x00000008;	# Perform CBR
    set *0x20000080=0x00000008
       
    # psdrc->SDRAMC_MR	= AT91C_SDRAMC_MODE_LMR_CMD;		# Set LMR operation
    set *0xFFFFEA00=0x00000003
    # *(AT91C_SDRAM+0x24)	= 0xcafedede;		# Perform LMR burst=1, lat=2
    set *0x20000090=0xCAFEDEDE
       
    # psdrc->SDRAMC_TR	= (AT91C_MASTER_CLOCK * 7)/1000000;				# Set Refresh Timer 390 for 25MHz (TR= 15.6 * F )
    set *0xFFFFEA04=0x000002B9
    
    #*	psdrc->SDRAMC_MR	= AT91C_SDRAMC_MODE_NORMAL_CMD;		# Set Normal mode
    set *0xFFFFEA00=0x00000000
    
    #*	*AT91C_SDRAM	= 0x00000000;	# Perform Normal mode
    set *0x20000000=0x00000000
    echo "---------- SDRAM Done at 100 MHz -----" \n
end

# Step1: Connect to the J-Link gdb server
define reset
	#target remote localhost:2331
	monitor reset

	# Step2: Reset peripheral  (RSTC_CR)
	#Init PLL
	__PllSetting
	__PllSetting100MHz    
	__initSDRAM
	#* Set the RAM memory at 0x0020 0000 & 0x0000 0000
	_MapRAMAt0                     
	_InitRSTC
	
	# Step3: Load file(eg. getting-started project)
	load

	mon reg pc=0x20000000
	#info reg

end