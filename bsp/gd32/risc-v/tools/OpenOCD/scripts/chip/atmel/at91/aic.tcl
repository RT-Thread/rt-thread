set AIC_SMR      	[expr $AT91C_BASE_AIC + 0x00000000 ]
global AIC_SMR
set AIC_SVR      	[expr $AT91C_BASE_AIC + 0x00000080 ]
global AIC_SVR
set AIC_IVR      	[expr $AT91C_BASE_AIC + 0x00000100 ]
global AIC_IVR
set AIC_FVR      	[expr $AT91C_BASE_AIC + 0x00000104 ]
global AIC_FVR
set AIC_ISR      	[expr $AT91C_BASE_AIC + 0x00000108 ]
global AIC_ISR
set AIC_IPR      	[expr $AT91C_BASE_AIC + 0x0000010C ]
global AIC_IPR
set AIC_IMR      	[expr $AT91C_BASE_AIC + 0x00000110 ]
global AIC_IMR
set AIC_CISR     	[expr $AT91C_BASE_AIC + 0x00000114 ]
global AIC_CISR
set AIC_IECR     	[expr $AT91C_BASE_AIC + 0x00000120 ]
global AIC_IECR
set AIC_IDCR     	[expr $AT91C_BASE_AIC + 0x00000124 ]
global AIC_IDCR
set AIC_ICCR     	[expr $AT91C_BASE_AIC + 0x00000128 ]
global AIC_ICCR
set AIC_ISCR     	[expr $AT91C_BASE_AIC + 0x0000012C ]
global AIC_ISCR
set AIC_EOICR    	[expr $AT91C_BASE_AIC + 0x00000130 ]
global AIC_EOICR
set AIC_SPU      	[expr $AT91C_BASE_AIC + 0x00000134 ]
global AIC_SPU
set AIC_DCR      	[expr $AT91C_BASE_AIC + 0x00000138 ]
global AIC_DCR
set AIC_FFER     	[expr $AT91C_BASE_AIC + 0x00000140 ]
global AIC_FFER
set AIC_FFDR     	[expr $AT91C_BASE_AIC + 0x00000144 ]
global AIC_FFDR
set AIC_FFSR     	[expr $AT91C_BASE_AIC + 0x00000148 ]
global AIC_FFSR


proc aic_enable_disable_list { VAL ENAME DNAME } {
    global AT91C_ID

    show_mmr32_bits AT91C_ID $VAL

}

proc show_AIC_IPR_helper { NAME ADDR VAL } {
    aic_enable_disable_list  $VAL "IRQ PENDING" "irq not-pending"
}

proc show_AIC_IMR_helper { NAME ADDR VAL } {
    aic_enable_disable_list  $VAL "IRQ ENABLED" "irq disabled"
}


proc show_AIC { } {
    global AIC_SMR
    if [catch { mem2array aaa 32 $AIC_SMR [expr 32 * 4] } msg ] {
	error [format "%s (%s)" $msg AIC_SMR]
    }
    echo "AIC_SMR: Mode & Type"
    global AT91C_ID
    for { set x 0 } { $x < 32 } {  } {
	echo -n "   "
	echo -n [format "%2d: %5s 0x%08x | " $x $AT91C_ID($x) $aaa($x)]
	incr x
	echo -n [format "%2d: %5s 0x%08x | " $x $AT91C_ID($x) $aaa($x)]
	incr x
	echo -n [format "%2d: %5s 0x%08x | " $x $AT91C_ID($x) $aaa($x)]
	incr x
	echo  [format "%2d: %5s 0x%08x"  $x $AT91C_ID($x) $aaa($x)]
	incr x
    }
    global AIC_SVR
    if [catch { mem2array aaa 32 $AIC_SVR [expr 32 * 4] } msg ] {
	error [format "%s (%s)" $msg AIC_SVR]
    }
    echo "AIC_SVR: Vectors"
    for { set x 0 } { $x < 32 } {  } {
	echo -n "   "
	echo -n [format "%2d: %5s 0x%08x | " $x $AT91C_ID($x) $aaa($x)]
	incr x
	echo -n [format "%2d: %5s 0x%08x | " $x $AT91C_ID($x) $aaa($x)]
	incr x
	echo -n [format "%2d: %5s 0x%08x | " $x $AT91C_ID($x) $aaa($x)]
	incr x
	echo [format "%2d: %5s 0x%08x" $x $AT91C_ID($x) $aaa($x)]
	incr x
    }

    foreach REG {
	AIC_IVR   AIC_FVR  AIC_ISR
	AIC_IPR  AIC_IMR  AIC_CISR  AIC_IECR AIC_IDCR
	AIC_ICCR AIC_ISCR AIC_EOICR AIC_SPU  AIC_DCR
	AIC_FFER AIC_FFDR AIC_FFSR } {
	if [catch { show_mmr32_reg $REG } msg ] {
	    error $msg
	    break
	}
    }
}
