
set RCC_CR            [expr $RCC_BASE + 0x00]
set RCC_CFGR          [expr $RCC_BASE + 0x04]
set RCC_CIR           [expr $RCC_BASE + 0x08]
set RCC_APB2RSTR      [expr $RCC_BASE + 0x0c]
set RCC_APB1RSTR      [expr $RCC_BASE + 0x10]
set RCC_AHBENR        [expr $RCC_BASE + 0x14]
set RCC_APB2ENR       [expr $RCC_BASE + 0x18]
set RCC_APB1ENR       [expr $RCC_BASE + 0x1c]
set RCC_BDCR          [expr $RCC_BASE + 0x20]
set RCC_CSR           [expr $RCC_BASE + 0x24]


proc show_RCC_CR { } {
    if [ catch { set val [show_mmr32_reg RCC_CR] } msg ] {
	error $msg
    }

    show_mmr_bitfield  0  0 $val HSI      { OFF ON }
    show_mmr_bitfield  1  1 $val HSIRDY   { NOTRDY RDY  }
    show_mmr_bitfield  7  3 $val HSITRIM  { _NUMBER_ }
    show_mmr_bitfield 15  8 $val HSICAL   { _NUMBER_ }
    show_mmr_bitfield 16 16 $val HSEON    { OFF ON }
    show_mmr_bitfield 17 17 $val HSERDY   { NOTRDY RDY  }
    show_mmr_bitfield 18 18 $val HSEBYP   { NOTBYPASSED BYPASSED }
    show_mmr_bitfield 19 19 $val CSSON    { OFF ON }
    show_mmr_bitfield 24 24 $val PLLON    { OFF ON }
    show_mmr_bitfield 25 25 $val PLLRDY   { NOTRDY RDY }
}

proc show_RCC_CFGR { } {
    if [ catch { set val [show_mmr32_reg RCC_CFGR] } msg ] {
	error $msg
    }


    show_mmr_bitfield  1  0 $val  SW     { HSI HSE PLL ILLEGAL }
    show_mmr_bitfield  3  2 $val  SWS    { HSI HSE PLL ILLEGAL }
    show_mmr_bitfield  7  4 $val  HPRE   { sysclk_div_1 sysclk_div_1 sysclk_div_1 sysclk_div_1 sysclk_div_1 sysclk_div_1 sysclk_div_1 sysclk_div_1 sysclk_div_2 sysclk_div_4 sysclk_div_8 sysclk_div_16 sysclk_div_64 sysclk_div_128 sysclk_div_256 sysclk_div_512 }
    show_mmr_bitfield 10  8 $val  PPRE1  { hclk_div1 hclk_div1 hclk_div1 hclk_div1 hclk_div2 hclk_div4 hclk_div8 hclk_div16 }
    show_mmr_bitfield 13 11 $val  PPRE2  { hclk_div1 hclk_div1 hclk_div1 hclk_div1 hclk_div2 hclk_div4 hclk_div8 hclk_div16 }
    show_mmr_bitfield 15 14 $val  ADCPRE { pclk2_div1 pclk2_div1 pclk2_div1 pclk2_div1 pclk2_div2 pclk2_div4 pclk2_div8 pclk2_div16 }
    show_mmr_bitfield 16 16 $val  PLLSRC { HSI_div_2 HSE }
    show_mmr_bitfield 17 17 $val  PLLXTPRE { hse_div1 hse_div2 }
    show_mmr_bitfield 21 18 $val  PLLMUL { x2 x3 x4 x5 x6 x7 x8 x9 x10 x11 x12 x13 x14 x15 x16 x16 }
    show_mmr_bitfield 22 22 $val  USBPRE { div1 div1_5 }
    show_mmr_bitfield 26 24 $val  MCO    { none none none none SysClk HSI HSE PLL_div2 }
}


proc show_RCC_CIR { } {
    if [ catch { set val [show_mmr32_reg RCC_CIR] } msg ] {
	error $msg
    }

}

proc show_RCC_APB2RSTR { } {
    if [ catch { set val [ show_mmr32_reg RCC_APB2RSTR] } msg ] {
	error $msg
    }
    for { set x 0 } { $x < 32 } { incr x } {
	set bits($x) xxx
    }
    set bits(15) adc3
    set bits(14) usart1
    set bits(13) tim8
    set bits(12) spi1
    set bits(11) tim1
    set bits(10) adc2
    set bits(9) adc1
    set bits(8) iopg
    set bits(7) iopf
    set bits(6) iope
    set bits(5) iopd
    set bits(4) iopc
    set bits(3) iopb
    set bits(2) iopa
    set bits(1) xxx
    set bits(0) afio
    show_mmr32_bits bits $val
}

proc show_RCC_APB1RSTR { } {
    if [ catch { set val [ show_mmr32_reg RCC_APB1RSTR] } msg ] {
	error $msg
    }
    set bits(31) xxx
    set bits(30) xxx
    set bits(29) dac
    set bits(28) pwr
    set bits(27) bkp
    set bits(26) xxx
    set bits(25) can
    set bits(24) xxx
    set bits(23) usb
    set bits(22) i2c2
    set bits(21) i2c1
    set bits(20) uart5
    set bits(19) uart4
    set bits(18) uart3
    set bits(17) uart2
    set bits(16) xxx
    set bits(15) spi3
    set bits(14) spi2
    set bits(13) xxx
    set bits(12) xxx
    set bits(11) wwdg
    set bits(10) xxx
    set bits(9) xxx
    set bits(8) xxx
    set bits(7) xxx
    set bits(6) xxx
    set bits(5) tim7
    set bits(4) tim6
    set bits(3) tim5
    set bits(2) tim4
    set bits(1) tim3
    set bits(0) tim2
    show_mmr32_bits bits $val

}

proc show_RCC_AHBENR   { } {
    if [ catch { set val [ show_mmr32_reg RCC_AHBENR  ] } msg ] {
	error $msg
    }
    set bits(31) xxx
    set bits(30) xxx
    set bits(29) xxx
    set bits(28) xxx
    set bits(27) xxx
    set bits(26) xxx
    set bits(25) xxx
    set bits(24) xxx
    set bits(23) xxx
    set bits(22) xxx
    set bits(21) xxx
    set bits(20) xxx
    set bits(19) xxx
    set bits(18) xxx
    set bits(17) xxx
    set bits(16) xxx
    set bits(15) xxx
    set bits(14) xxx
    set bits(13) xxx
    set bits(12) xxx
    set bits(11) xxx
    set bits(10) sdio
    set bits(9) xxx
    set bits(8) fsmc
    set bits(7) xxx
    set bits(6) crce
    set bits(5) xxx
    set bits(4) flitf
    set bits(3) xxx
    set bits(2) sram
    set bits(1) dma2
    set bits(0) dma1
    show_mmr32_bits bits $val
}

proc show_RCC_APB2ENR  { } {
    if [ catch { set val [ show_mmr32_reg RCC_APB2ENR ] } msg ] {
	error $msg
    }
    set bits(31) xxx
    set bits(30) xxx
    set bits(29) xxx
    set bits(28) xxx
    set bits(27) xxx
    set bits(26) xxx
    set bits(25) xxx
    set bits(24) xxx
    set bits(23) xxx
    set bits(22) xxx
    set bits(21) xxx
    set bits(20) xxx
    set bits(19) xxx
    set bits(18) xxx
    set bits(17) xxx
    set bits(16) xxx
    set bits(15) adc3
    set bits(14) usart1
    set bits(13) tim8
    set bits(12) spi1
    set bits(11) tim1
    set bits(10) adc2
    set bits(9) adc1
    set bits(8) iopg
    set bits(7) iopf
    set bits(6) iope
    set bits(5) iopd
    set bits(4) iopc
    set bits(3) iopb
    set bits(2) iopa
    set bits(1) xxx
    set bits(0) afio
    show_mmr32_bits bits $val

}

proc show_RCC_APB1ENR  { } {
    if [ catch { set val [ show_mmr32_reg RCC_APB1ENR ] } msg ] {
	error $msg
    }
    set bits(31) xxx
    set bits(30) xxx
    set bits(29) dac
    set bits(28) pwr
    set bits(27) bkp
    set bits(26) xxx
    set bits(25) can
    set bits(24) xxx
    set bits(23) usb
    set bits(22) i2c2
    set bits(21) i2c1
    set bits(20) usart5
    set bits(19) usart4
    set bits(18) usart3
    set bits(17) usart2
    set bits(16) xxx
    set bits(15) spi3
    set bits(14) spi2
    set bits(13) xxx
    set bits(12) xxx
    set bits(11) wwdg
    set bits(10) xxx
    set bits(9) xxx
    set bits(8) xxx
    set bits(7) xxx
    set bits(6) xxx
    set bits(5) tim7
    set bits(4) tim6
    set bits(3) tim5
    set bits(2) tim4
    set bits(1) tim3
    set bits(0) tim2
    show_mmr32_bits bits $val
}

proc show_RCC_BDCR     { } {
    if [ catch { set val [ show_mmr32_reg RCC_BDCR    ] } msg ] {
	error $msg
    }
    for { set x 0 } { $x < 32 } { incr x } {
	set bits($x) xxx
    }
    set bits(0) lseon
    set bits(1) lserdy
    set bits(2) lsebyp
    set bits(8) rtcsel0
    set bits(9) rtcsel1
    set bits(15) rtcen
    set bits(16) bdrst
    show_mmr32_bits bits $val
}

proc show_RCC_CSR      { } {
    if [ catch { set val [ show_mmr32_reg RCC_CSR     ] } msg ] {
	error $msg
    }
    for { set x 0 } { $x < 32 } { incr x } {
	set bits($x) xxx
    }
    set bits(0) lsion
    set bits(1) lsirdy
    set bits(24) rmvf
    set bits(26) pin
    set bits(27) por
    set bits(28) sft
    set bits(29) iwdg
    set bits(30) wwdg
    set bits(31) lpwr
    show_mmr32_bits bits $val
}

proc show_RCC { } {

    show_RCC_CR
    show_RCC_CFGR
    show_RCC_CIR
    show_RCC_APB2RSTR
    show_RCC_APB1RSTR
    show_RCC_AHBENR
    show_RCC_APB2ENR
    show_RCC_APB1ENR
    show_RCC_BDCR
    show_RCC_CSR
}
