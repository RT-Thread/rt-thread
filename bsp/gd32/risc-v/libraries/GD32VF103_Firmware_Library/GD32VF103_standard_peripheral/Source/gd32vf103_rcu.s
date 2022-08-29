	.file	"gd32vf103_rcu.c"
	.option nopic
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.align	1
	.globl	rcu_deinit
	.type	rcu_deinit, @function
rcu_deinit:
.LFB2:
	.file 1 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Source\\gd32vf103_rcu.c"
	.loc 1 54 1
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	ra,12(sp)
	sw	s0,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 56 89
	li	a5,1073876992
	lw	a4,0(a5)
	li	a5,1073876992
	ori	a4,a4,1
	sw	a4,0(a5)
	.loc 1 57 5
	li	a0,0
	call	rcu_osci_stab_wait
	.loc 1 59 89
	li	a5,1073876992
	lw	a3,0(a5)
	li	a5,1073876992
	li	a4,-17367040
	addi	a4,a4,-1
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 60 89
	li	a5,1073876992
	lw	a3,0(a5)
	li	a5,1073876992
	li	a4,-262144
	addi	a4,a4,-1
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 61 89
	li	a5,1073876992
	lw	a3,0(a5)
	li	a5,1073876992
	li	a4,-335544320
	addi	a4,a4,-1
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 63 89
	li	a5,1073876992
	addi	a5,a5,4
	lw	a3,0(a5)
	li	a5,1073876992
	addi	a5,a5,4
	li	a4,-1073741824
	addi	a4,a4,12
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 67 6
	li	a5,1073876992
	addi	a5,a5,8
	.loc 1 67 89
	li	a4,16711680
	sw	a4,0(a5)
	.loc 1 68 89
	li	a5,1073876992
	addi	a5,a5,44
	lw	a3,0(a5)
	li	a5,1073876992
	addi	a5,a5,44
	li	a4,-524288
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 70 1
	nop
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE2:
	.size	rcu_deinit, .-rcu_deinit
	.align	1
	.globl	rcu_periph_clock_enable
	.type	rcu_periph_clock_enable, @function
rcu_periph_clock_enable:
.LFB3:
	.loc 1 98 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 99 111
	lw	a5,-20(s0)
	srli	a4,a5,6
	li	a5,1073876992
	add	a5,a4,a5
	lw	a4,0(a5)
	.loc 1 99 164
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 99 115
	li	a3,1
	sll	a5,a3,a5
	.loc 1 99 111
	lw	a3,-20(s0)
	srli	a2,a3,6
	li	a3,1073876992
	add	a3,a2,a3
	or	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 100 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE3:
	.size	rcu_periph_clock_enable, .-rcu_periph_clock_enable
	.align	1
	.globl	rcu_periph_clock_disable
	.type	rcu_periph_clock_disable, @function
rcu_periph_clock_disable:
.LFB4:
	.loc 1 128 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 129 111
	lw	a5,-20(s0)
	srli	a4,a5,6
	li	a5,1073876992
	add	a5,a4,a5
	lw	a4,0(a5)
	.loc 1 129 165
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 129 116
	li	a3,1
	sll	a5,a3,a5
	.loc 1 129 114
	not	a5,a5
	.loc 1 129 111
	lw	a3,-20(s0)
	srli	a2,a3,6
	li	a3,1073876992
	add	a3,a2,a3
	and	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 130 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE4:
	.size	rcu_periph_clock_disable, .-rcu_periph_clock_disable
	.align	1
	.globl	rcu_periph_clock_sleep_enable
	.type	rcu_periph_clock_sleep_enable, @function
rcu_periph_clock_sleep_enable:
.LFB5:
	.loc 1 142 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 143 111
	lw	a5,-20(s0)
	srli	a4,a5,6
	li	a5,1073876992
	add	a5,a4,a5
	lw	a4,0(a5)
	.loc 1 143 164
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 143 115
	li	a3,1
	sll	a5,a3,a5
	.loc 1 143 111
	lw	a3,-20(s0)
	srli	a2,a3,6
	li	a3,1073876992
	add	a3,a2,a3
	or	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 144 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE5:
	.size	rcu_periph_clock_sleep_enable, .-rcu_periph_clock_sleep_enable
	.align	1
	.globl	rcu_periph_clock_sleep_disable
	.type	rcu_periph_clock_sleep_disable, @function
rcu_periph_clock_sleep_disable:
.LFB6:
	.loc 1 156 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 157 111
	lw	a5,-20(s0)
	srli	a4,a5,6
	li	a5,1073876992
	add	a5,a4,a5
	lw	a4,0(a5)
	.loc 1 157 165
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 157 116
	li	a3,1
	sll	a5,a3,a5
	.loc 1 157 114
	not	a5,a5
	.loc 1 157 111
	lw	a3,-20(s0)
	srli	a2,a3,6
	li	a3,1073876992
	add	a3,a2,a3
	and	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 158 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE6:
	.size	rcu_periph_clock_sleep_disable, .-rcu_periph_clock_sleep_disable
	.align	1
	.globl	rcu_periph_reset_enable
	.type	rcu_periph_reset_enable, @function
rcu_periph_reset_enable:
.LFB7:
	.loc 1 182 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 183 117
	lw	a5,-20(s0)
	srli	a4,a5,6
	li	a5,1073876992
	add	a5,a4,a5
	lw	a4,0(a5)
	.loc 1 183 176
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 183 121
	li	a3,1
	sll	a5,a3,a5
	.loc 1 183 117
	lw	a3,-20(s0)
	srli	a2,a3,6
	li	a3,1073876992
	add	a3,a2,a3
	or	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 184 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE7:
	.size	rcu_periph_reset_enable, .-rcu_periph_reset_enable
	.align	1
	.globl	rcu_periph_reset_disable
	.type	rcu_periph_reset_disable, @function
rcu_periph_reset_disable:
.LFB8:
	.loc 1 208 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 209 117
	lw	a5,-20(s0)
	srli	a4,a5,6
	li	a5,1073876992
	add	a5,a4,a5
	lw	a4,0(a5)
	.loc 1 209 177
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 209 122
	li	a3,1
	sll	a5,a3,a5
	.loc 1 209 120
	not	a5,a5
	.loc 1 209 117
	lw	a3,-20(s0)
	srli	a2,a3,6
	li	a3,1073876992
	add	a3,a2,a3
	and	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 210 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE8:
	.size	rcu_periph_reset_disable, .-rcu_periph_reset_disable
	.align	1
	.globl	rcu_bkp_reset_enable
	.type	rcu_bkp_reset_enable, @function
rcu_bkp_reset_enable:
.LFB9:
	.loc 1 219 1
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,12(sp)
	.cfi_offset 8, -4
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 220 89
	li	a5,1073876992
	addi	a5,a5,32
	lw	a3,0(a5)
	li	a5,1073876992
	addi	a5,a5,32
	li	a4,65536
	or	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 221 1
	nop
	lw	s0,12(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE9:
	.size	rcu_bkp_reset_enable, .-rcu_bkp_reset_enable
	.align	1
	.globl	rcu_bkp_reset_disable
	.type	rcu_bkp_reset_disable, @function
rcu_bkp_reset_disable:
.LFB10:
	.loc 1 230 1
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,12(sp)
	.cfi_offset 8, -4
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 231 89
	li	a5,1073876992
	addi	a5,a5,32
	lw	a3,0(a5)
	li	a5,1073876992
	addi	a5,a5,32
	li	a4,-65536
	addi	a4,a4,-1
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 232 1
	nop
	lw	s0,12(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE10:
	.size	rcu_bkp_reset_disable, .-rcu_bkp_reset_disable
	.align	1
	.globl	rcu_system_clock_source_config
	.type	rcu_system_clock_source_config, @function
rcu_system_clock_source_config:
.LFB11:
	.loc 1 245 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 248 12
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 248 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 250 9
	lw	a5,-20(s0)
	andi	a5,a5,-4
	sw	a5,-20(s0)
	.loc 1 251 6
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 251 96
	lw	a3,-20(s0)
	lw	a4,-36(s0)
	or	a4,a3,a4
	.loc 1 251 89
	sw	a4,0(a5)
	.loc 1 252 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE11:
	.size	rcu_system_clock_source_config, .-rcu_system_clock_source_config
	.align	1
	.globl	rcu_system_clock_source_get
	.type	rcu_system_clock_source_get, @function
rcu_system_clock_source_get:
.LFB12:
	.loc 1 264 1
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,12(sp)
	.cfi_offset 8, -4
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 265 97
	li	a5,1073876992
	addi	a5,a5,4
	lw	a5,0(a5)
	andi	a5,a5,12
	.loc 1 266 1
	mv	a0,a5
	lw	s0,12(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE12:
	.size	rcu_system_clock_source_get, .-rcu_system_clock_source_get
	.align	1
	.globl	rcu_ahb_clock_config
	.type	rcu_ahb_clock_config, @function
rcu_ahb_clock_config:
.LFB13:
	.loc 1 277 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 280 12
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 280 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 283 9
	lw	a5,-20(s0)
	andi	a5,a5,-241
	sw	a5,-20(s0)
	.loc 1 284 6
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 284 96
	lw	a3,-20(s0)
	lw	a4,-36(s0)
	or	a4,a3,a4
	.loc 1 284 89
	sw	a4,0(a5)
	.loc 1 285 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE13:
	.size	rcu_ahb_clock_config, .-rcu_ahb_clock_config
	.align	1
	.globl	rcu_apb1_clock_config
	.type	rcu_apb1_clock_config, @function
rcu_apb1_clock_config:
.LFB14:
	.loc 1 300 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 303 12
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 303 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 306 9
	lw	a5,-20(s0)
	andi	a5,a5,-1793
	sw	a5,-20(s0)
	.loc 1 307 6
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 307 96
	lw	a3,-20(s0)
	lw	a4,-36(s0)
	or	a4,a3,a4
	.loc 1 307 89
	sw	a4,0(a5)
	.loc 1 308 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE14:
	.size	rcu_apb1_clock_config, .-rcu_apb1_clock_config
	.align	1
	.globl	rcu_apb2_clock_config
	.type	rcu_apb2_clock_config, @function
rcu_apb2_clock_config:
.LFB15:
	.loc 1 323 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 326 12
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 326 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 329 9
	lw	a4,-20(s0)
	li	a5,-16384
	addi	a5,a5,2047
	and	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 330 6
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 330 96
	lw	a3,-20(s0)
	lw	a4,-36(s0)
	or	a4,a3,a4
	.loc 1 330 89
	sw	a4,0(a5)
	.loc 1 331 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE15:
	.size	rcu_apb2_clock_config, .-rcu_apb2_clock_config
	.align	1
	.globl	rcu_ckout0_config
	.type	rcu_ckout0_config, @function
rcu_ckout0_config:
.LFB16:
	.loc 1 350 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 353 12
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 353 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 356 9
	lw	a4,-20(s0)
	li	a5,-251658240
	addi	a5,a5,-1
	and	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 357 6
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 357 96
	lw	a3,-20(s0)
	lw	a4,-36(s0)
	or	a4,a3,a4
	.loc 1 357 89
	sw	a4,0(a5)
	.loc 1 358 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE16:
	.size	rcu_ckout0_config, .-rcu_ckout0_config
	.align	1
	.globl	rcu_pll_config
	.type	rcu_pll_config, @function
rcu_pll_config:
.LFB17:
	.loc 1 373 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	.loc 1 374 14
	sw	zero,-20(s0)
	.loc 1 376 12
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 376 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 379 9
	lw	a4,-20(s0)
	li	a5,-540868608
	addi	a5,a5,-1
	and	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 380 21
	lw	a4,-36(s0)
	lw	a5,-40(s0)
	or	a5,a4,a5
	.loc 1 380 9
	lw	a4,-20(s0)
	or	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 382 6
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 382 89
	lw	a4,-20(s0)
	sw	a4,0(a5)
	.loc 1 383 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE17:
	.size	rcu_pll_config, .-rcu_pll_config
	.align	1
	.globl	rcu_predv0_config
	.type	rcu_predv0_config, @function
rcu_predv0_config:
.LFB18:
	.loc 1 398 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	.loc 1 399 14
	sw	zero,-20(s0)
	.loc 1 401 12
	li	a5,1073876992
	addi	a5,a5,44
	.loc 1 401 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 403 9
	lw	a4,-20(s0)
	li	a5,-65536
	addi	a5,a5,-16
	and	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 405 27
	lw	a4,-36(s0)
	lw	a5,-40(s0)
	or	a5,a4,a5
	.loc 1 405 9
	lw	a4,-20(s0)
	or	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 407 6
	li	a5,1073876992
	addi	a5,a5,44
	.loc 1 407 89
	lw	a4,-20(s0)
	sw	a4,0(a5)
	.loc 1 408 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE18:
	.size	rcu_predv0_config, .-rcu_predv0_config
	.align	1
	.globl	rcu_predv1_config
	.type	rcu_predv1_config, @function
rcu_predv1_config:
.LFB19:
	.loc 1 419 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 420 14
	sw	zero,-20(s0)
	.loc 1 422 12
	li	a5,1073876992
	addi	a5,a5,44
	.loc 1 422 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 424 9
	lw	a5,-20(s0)
	andi	a5,a5,-241
	sw	a5,-20(s0)
	.loc 1 426 9
	lw	a4,-20(s0)
	lw	a5,-36(s0)
	or	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 428 6
	li	a5,1073876992
	addi	a5,a5,44
	.loc 1 428 89
	lw	a4,-20(s0)
	sw	a4,0(a5)
	.loc 1 429 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE19:
	.size	rcu_predv1_config, .-rcu_predv1_config
	.align	1
	.globl	rcu_pll1_config
	.type	rcu_pll1_config, @function
rcu_pll1_config:
.LFB20:
	.loc 1 440 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 441 89
	li	a5,1073876992
	addi	a5,a5,44
	lw	a3,0(a5)
	li	a5,1073876992
	addi	a5,a5,44
	li	a4,-4096
	addi	a4,a4,255
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 442 89
	li	a5,1073876992
	addi	a5,a5,44
	lw	a3,0(a5)
	li	a5,1073876992
	addi	a5,a5,44
	lw	a4,-20(s0)
	or	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 443 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE20:
	.size	rcu_pll1_config, .-rcu_pll1_config
	.align	1
	.globl	rcu_pll2_config
	.type	rcu_pll2_config, @function
rcu_pll2_config:
.LFB21:
	.loc 1 454 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 455 89
	li	a5,1073876992
	addi	a5,a5,44
	lw	a3,0(a5)
	li	a5,1073876992
	addi	a5,a5,44
	li	a4,-61440
	addi	a4,a4,-1
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 456 89
	li	a5,1073876992
	addi	a5,a5,44
	lw	a3,0(a5)
	li	a5,1073876992
	addi	a5,a5,44
	lw	a4,-20(s0)
	or	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 457 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE21:
	.size	rcu_pll2_config, .-rcu_pll2_config
	.align	1
	.globl	rcu_adc_clock_config
	.type	rcu_adc_clock_config, @function
rcu_adc_clock_config:
.LFB22:
	.loc 1 473 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 477 13
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 477 10
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 478 10
	lw	a4,-20(s0)
	li	a5,-268484608
	addi	a5,a5,-1
	and	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 481 5
	lw	a4,-36(s0)
	li	a5,7
	beq	a4,a5,.L23
	lw	a4,-36(s0)
	li	a5,7
	bgtu	a4,a5,.L27
	lw	a4,-36(s0)
	li	a5,3
	bleu	a4,a5,.L25
	lw	a4,-36(s0)
	li	a5,5
	beq	a4,a5,.L23
	.loc 1 496 13
	j	.L27
.L25:
	.loc 1 486 30
	lw	a5,-36(s0)
	slli	a5,a5,14
	.loc 1 486 18
	lw	a4,-20(s0)
	or	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 487 13
	j	.L26
.L23:
	.loc 1 491 21
	lw	a5,-36(s0)
	andi	a5,a5,-5
	sw	a5,-36(s0)
	.loc 1 492 30
	lw	a5,-36(s0)
	slli	a4,a5,14
	.loc 1 492 18
	lw	a5,-20(s0)
	or	a4,a4,a5
	li	a5,268435456
	or	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 493 13
	j	.L26
.L27:
	.loc 1 496 13
	nop
.L26:
	.loc 1 500 6
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 500 89
	lw	a4,-20(s0)
	sw	a4,0(a5)
	.loc 1 501 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE22:
	.size	rcu_adc_clock_config, .-rcu_adc_clock_config
	.align	1
	.globl	rcu_usb_clock_config
	.type	rcu_usb_clock_config, @function
rcu_usb_clock_config:
.LFB23:
	.loc 1 515 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 518 12
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 518 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 521 9
	lw	a4,-20(s0)
	li	a5,-12582912
	addi	a5,a5,-1
	and	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 522 6
	li	a5,1073876992
	addi	a5,a5,4
	.loc 1 522 96
	lw	a3,-20(s0)
	lw	a4,-36(s0)
	or	a4,a3,a4
	.loc 1 522 89
	sw	a4,0(a5)
	.loc 1 523 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE23:
	.size	rcu_usb_clock_config, .-rcu_usb_clock_config
	.align	1
	.globl	rcu_rtc_clock_config
	.type	rcu_rtc_clock_config, @function
rcu_rtc_clock_config:
.LFB24:
	.loc 1 537 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 540 12
	li	a5,1073876992
	addi	a5,a5,32
	.loc 1 540 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 542 9
	lw	a5,-20(s0)
	andi	a5,a5,-769
	sw	a5,-20(s0)
	.loc 1 543 6
	li	a5,1073876992
	addi	a5,a5,32
	.loc 1 543 96
	lw	a3,-20(s0)
	lw	a4,-36(s0)
	or	a4,a3,a4
	.loc 1 543 89
	sw	a4,0(a5)
	.loc 1 544 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE24:
	.size	rcu_rtc_clock_config, .-rcu_rtc_clock_config
	.align	1
	.globl	rcu_i2s1_clock_config
	.type	rcu_i2s1_clock_config, @function
rcu_i2s1_clock_config:
.LFB25:
	.loc 1 556 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 559 12
	li	a5,1073876992
	addi	a5,a5,44
	.loc 1 559 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 561 9
	lw	a4,-20(s0)
	li	a5,-131072
	addi	a5,a5,-1
	and	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 562 6
	li	a5,1073876992
	addi	a5,a5,44
	.loc 1 562 96
	lw	a3,-20(s0)
	lw	a4,-36(s0)
	or	a4,a3,a4
	.loc 1 562 89
	sw	a4,0(a5)
	.loc 1 563 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE25:
	.size	rcu_i2s1_clock_config, .-rcu_i2s1_clock_config
	.align	1
	.globl	rcu_i2s2_clock_config
	.type	rcu_i2s2_clock_config, @function
rcu_i2s2_clock_config:
.LFB26:
	.loc 1 575 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 578 12
	li	a5,1073876992
	addi	a5,a5,44
	.loc 1 578 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 580 9
	lw	a4,-20(s0)
	li	a5,-262144
	addi	a5,a5,-1
	and	a5,a4,a5
	sw	a5,-20(s0)
	.loc 1 581 6
	li	a5,1073876992
	addi	a5,a5,44
	.loc 1 581 96
	lw	a3,-20(s0)
	lw	a4,-36(s0)
	or	a4,a3,a4
	.loc 1 581 89
	sw	a4,0(a5)
	.loc 1 582 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE26:
	.size	rcu_i2s2_clock_config, .-rcu_i2s2_clock_config
	.align	1
	.globl	rcu_flag_get
	.type	rcu_flag_get, @function
rcu_flag_get:
.LFB27:
	.loc 1 605 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 607 113
	lw	a5,-20(s0)
	srli	a4,a5,6
	.loc 1 607 42
	li	a5,1073876992
	add	a5,a4,a5
	.loc 1 607 20
	lw	a4,0(a5)
	.loc 1 607 172
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 607 14
	srl	a5,a4,a5
	andi	a5,a5,1
	.loc 1 607 7
	beq	a5,zero,.L33
	.loc 1 608 16
	li	a5,1
	j	.L34
.L33:
	.loc 1 610 16
	li	a5,0
.L34:
	.loc 1 612 1
	mv	a0,a5
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE27:
	.size	rcu_flag_get, .-rcu_flag_get
	.align	1
	.globl	rcu_all_reset_flag_clear
	.type	rcu_all_reset_flag_clear, @function
rcu_all_reset_flag_clear:
.LFB28:
	.loc 1 621 1
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,12(sp)
	.cfi_offset 8, -4
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 622 89
	li	a5,1073876992
	addi	a5,a5,36
	lw	a3,0(a5)
	li	a5,1073876992
	addi	a5,a5,36
	li	a4,16777216
	or	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 623 1
	nop
	lw	s0,12(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE28:
	.size	rcu_all_reset_flag_clear, .-rcu_all_reset_flag_clear
	.align	1
	.globl	rcu_interrupt_flag_get
	.type	rcu_interrupt_flag_get, @function
rcu_interrupt_flag_get:
.LFB29:
	.loc 1 641 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 643 117
	lw	a5,-20(s0)
	srli	a4,a5,6
	.loc 1 643 42
	li	a5,1073876992
	add	a5,a4,a5
	.loc 1 643 20
	lw	a4,0(a5)
	.loc 1 643 180
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 643 14
	srl	a5,a4,a5
	andi	a5,a5,1
	.loc 1 643 7
	beq	a5,zero,.L37
	.loc 1 644 16
	li	a5,1
	j	.L38
.L37:
	.loc 1 646 16
	li	a5,0
.L38:
	.loc 1 648 1
	mv	a0,a5
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE29:
	.size	rcu_interrupt_flag_get, .-rcu_interrupt_flag_get
	.align	1
	.globl	rcu_interrupt_flag_clear
	.type	rcu_interrupt_flag_clear, @function
rcu_interrupt_flag_clear:
.LFB30:
	.loc 1 666 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 667 119
	lw	a5,-20(s0)
	srli	a4,a5,6
	li	a5,1073876992
	add	a5,a4,a5
	lw	a4,0(a5)
	.loc 1 667 180
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 667 123
	li	a3,1
	sll	a5,a3,a5
	.loc 1 667 119
	lw	a3,-20(s0)
	srli	a2,a3,6
	li	a3,1073876992
	add	a3,a2,a3
	or	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 668 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE30:
	.size	rcu_interrupt_flag_clear, .-rcu_interrupt_flag_clear
	.align	1
	.globl	rcu_interrupt_enable
	.type	rcu_interrupt_enable, @function
rcu_interrupt_enable:
.LFB31:
	.loc 1 685 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 686 113
	lw	a5,-20(s0)
	srli	a4,a5,6
	li	a5,1073876992
	add	a5,a4,a5
	lw	a4,0(a5)
	.loc 1 686 168
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 686 117
	li	a3,1
	sll	a5,a3,a5
	.loc 1 686 113
	lw	a3,-20(s0)
	srli	a2,a3,6
	li	a3,1073876992
	add	a3,a2,a3
	or	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 687 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE31:
	.size	rcu_interrupt_enable, .-rcu_interrupt_enable
	.align	1
	.globl	rcu_interrupt_disable
	.type	rcu_interrupt_disable, @function
rcu_interrupt_disable:
.LFB32:
	.loc 1 704 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 705 113
	lw	a5,-20(s0)
	srli	a4,a5,6
	li	a5,1073876992
	add	a5,a4,a5
	lw	a4,0(a5)
	.loc 1 705 169
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 705 118
	li	a3,1
	sll	a5,a3,a5
	.loc 1 705 116
	not	a5,a5
	.loc 1 705 113
	lw	a3,-20(s0)
	srli	a2,a3,6
	li	a3,1073876992
	add	a3,a2,a3
	and	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 706 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE32:
	.size	rcu_interrupt_disable, .-rcu_interrupt_disable
	.align	1
	.globl	rcu_osci_stab_wait
	.type	rcu_osci_stab_wait, @function
rcu_osci_stab_wait:
.LFB33:
	.loc 1 723 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	ra,44(sp)
	sw	s0,40(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 724 14
	sw	zero,-20(s0)
	.loc 1 725 15
	sw	zero,-24(s0)
	.loc 1 726 16
	sw	zero,-28(s0)
	.loc 1 728 5
	lw	a4,-36(s0)
	li	a5,4096
	addi	a5,a5,-1792
	beq	a4,a5,.L66
	lw	a4,-36(s0)
	li	a5,4096
	addi	a5,a5,-1792
	bgtu	a4,a5,.L83
	lw	a4,-36(s0)
	li	a5,28
	bgtu	a4,a5,.L45
	lw	a4,-36(s0)
	li	a5,28
	bgtu	a4,a5,.L83
	lw	a5,-36(s0)
	slli	a4,a5,2
	lla	a5,.L47
	add	a5,a4,a5
	lw	a4,0(a5)
	lla	a5,.L47
	add	a5,a4,a5
	jr	a5
	.section	.rodata
	.align	2
	.align	2
.L47:
	.word	.L62-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L53-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L83-.L47
	.word	.L70-.L47
	.word	.L83-.L47
	.word	.L74-.L47
	.word	.L83-.L47
	.word	.L78-.L47
	.text
.L45:
	lw	a5,-36(s0)
	addi	a5,a5,-2048
	beq	a5,zero,.L58
	.loc 1 819 9
	j	.L83
.L55:
	.loc 1 732 25
	li	a0,17
	call	rcu_flag_get
	sw	a0,-28(s0)
	.loc 1 733 20
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L53:
	.loc 1 731 14
	lw	a5,-28(s0)
	bne	a5,zero,.L54
	.loc 1 731 36 discriminator 1
	lw	a4,-20(s0)
	li	a5,65536
	addi	a5,a5,-1
	bne	a4,a5,.L55
.L54:
	.loc 1 737 21
	li	a0,17
	call	rcu_flag_get
	mv	a5,a0
	.loc 1 737 11
	beq	a5,zero,.L84
	.loc 1 738 19
	li	a5,1
	sw	a5,-24(s0)
	.loc 1 740 9
	j	.L84
.L60:
	.loc 1 745 25
	li	a5,4096
	addi	a0,a5,-2047
	call	rcu_flag_get
	sw	a0,-28(s0)
	.loc 1 746 20
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L58:
	.loc 1 744 14
	lw	a5,-28(s0)
	bne	a5,zero,.L59
	.loc 1 744 36 discriminator 1
	lw	a4,-20(s0)
	li	a5,67108864
	addi	a5,a5,-1
	bne	a4,a5,.L60
.L59:
	.loc 1 750 21
	li	a5,4096
	addi	a0,a5,-2047
	call	rcu_flag_get
	mv	a5,a0
	.loc 1 750 11
	beq	a5,zero,.L85
	.loc 1 751 19
	li	a5,1
	sw	a5,-24(s0)
	.loc 1 753 9
	j	.L85
.L64:
	.loc 1 758 25
	li	a0,1
	call	rcu_flag_get
	sw	a0,-28(s0)
	.loc 1 759 20
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L62:
	.loc 1 757 14
	lw	a5,-28(s0)
	bne	a5,zero,.L63
	.loc 1 757 36 discriminator 1
	lw	a4,-20(s0)
	li	a5,1280
	bne	a4,a5,.L64
.L63:
	.loc 1 763 21
	li	a0,1
	call	rcu_flag_get
	mv	a5,a0
	.loc 1 763 11
	beq	a5,zero,.L86
	.loc 1 764 19
	li	a5,1
	sw	a5,-24(s0)
	.loc 1 766 9
	j	.L86
.L68:
	.loc 1 771 25
	li	a5,4096
	addi	a0,a5,-1791
	call	rcu_flag_get
	sw	a0,-28(s0)
	.loc 1 772 20
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L66:
	.loc 1 770 14
	lw	a5,-28(s0)
	bne	a5,zero,.L67
	.loc 1 770 36 discriminator 1
	lw	a4,-20(s0)
	li	a5,1048576
	addi	a5,a5,-1
	bne	a4,a5,.L68
.L67:
	.loc 1 776 21
	li	a5,4096
	addi	a0,a5,-1791
	call	rcu_flag_get
	mv	a5,a0
	.loc 1 776 11
	beq	a5,zero,.L87
	.loc 1 777 19
	li	a5,1
	sw	a5,-24(s0)
	.loc 1 779 9
	j	.L87
.L72:
	.loc 1 784 25
	li	a0,25
	call	rcu_flag_get
	sw	a0,-28(s0)
	.loc 1 785 20
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L70:
	.loc 1 783 14
	lw	a5,-28(s0)
	bne	a5,zero,.L71
	.loc 1 783 36 discriminator 1
	lw	a4,-20(s0)
	li	a5,1048576
	addi	a5,a5,-1
	bne	a4,a5,.L72
.L71:
	.loc 1 789 21
	li	a0,25
	call	rcu_flag_get
	mv	a5,a0
	.loc 1 789 11
	beq	a5,zero,.L88
	.loc 1 790 19
	li	a5,1
	sw	a5,-24(s0)
	.loc 1 792 9
	j	.L88
.L76:
	.loc 1 796 25
	li	a0,27
	call	rcu_flag_get
	sw	a0,-28(s0)
	.loc 1 797 20
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L74:
	.loc 1 795 14
	lw	a5,-28(s0)
	bne	a5,zero,.L75
	.loc 1 795 36 discriminator 1
	lw	a4,-20(s0)
	li	a5,1048576
	addi	a5,a5,-1
	bne	a4,a5,.L76
.L75:
	.loc 1 801 21
	li	a0,27
	call	rcu_flag_get
	mv	a5,a0
	.loc 1 801 11
	beq	a5,zero,.L89
	.loc 1 802 19
	li	a5,1
	sw	a5,-24(s0)
	.loc 1 804 9
	j	.L89
.L80:
	.loc 1 808 25
	li	a0,29
	call	rcu_flag_get
	sw	a0,-28(s0)
	.loc 1 809 20
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L78:
	.loc 1 807 14
	lw	a5,-28(s0)
	bne	a5,zero,.L79
	.loc 1 807 36 discriminator 1
	lw	a4,-20(s0)
	li	a5,1048576
	addi	a5,a5,-1
	bne	a4,a5,.L80
.L79:
	.loc 1 813 21
	li	a0,29
	call	rcu_flag_get
	mv	a5,a0
	.loc 1 813 11
	beq	a5,zero,.L90
	.loc 1 814 19
	li	a5,1
	sw	a5,-24(s0)
	.loc 1 816 9
	j	.L90
.L83:
	.loc 1 819 9
	nop
	j	.L57
.L84:
	.loc 1 740 9
	nop
	j	.L57
.L85:
	.loc 1 753 9
	nop
	j	.L57
.L86:
	.loc 1 766 9
	nop
	j	.L57
.L87:
	.loc 1 779 9
	nop
	j	.L57
.L88:
	.loc 1 792 9
	nop
	j	.L57
.L89:
	.loc 1 804 9
	nop
	j	.L57
.L90:
	.loc 1 816 9
	nop
.L57:
	.loc 1 823 12
	lw	a5,-24(s0)
	.loc 1 824 1
	mv	a0,a5
	lw	ra,44(sp)
	.cfi_restore 1
	lw	s0,40(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE33:
	.size	rcu_osci_stab_wait, .-rcu_osci_stab_wait
	.align	1
	.globl	rcu_osci_on
	.type	rcu_osci_on, @function
rcu_osci_on:
.LFB34:
	.loc 1 841 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 842 109
	lw	a5,-20(s0)
	srli	a4,a5,6
	li	a5,1073876992
	add	a5,a4,a5
	lw	a4,0(a5)
	.loc 1 842 160
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 842 113
	li	a3,1
	sll	a5,a3,a5
	.loc 1 842 109
	lw	a3,-20(s0)
	srli	a2,a3,6
	li	a3,1073876992
	add	a3,a2,a3
	or	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 843 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE34:
	.size	rcu_osci_on, .-rcu_osci_on
	.align	1
	.globl	rcu_osci_off
	.type	rcu_osci_off, @function
rcu_osci_off:
.LFB35:
	.loc 1 860 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 861 109
	lw	a5,-20(s0)
	srli	a4,a5,6
	li	a5,1073876992
	add	a5,a4,a5
	lw	a4,0(a5)
	.loc 1 861 161
	lw	a5,-20(s0)
	andi	a5,a5,31
	.loc 1 861 114
	li	a3,1
	sll	a5,a3,a5
	.loc 1 861 112
	not	a5,a5
	.loc 1 861 109
	lw	a3,-20(s0)
	srli	a2,a3,6
	li	a3,1073876992
	add	a3,a2,a3
	and	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 862 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE35:
	.size	rcu_osci_off, .-rcu_osci_off
	.align	1
	.globl	rcu_osci_bypass_mode_enable
	.type	rcu_osci_bypass_mode_enable, @function
rcu_osci_bypass_mode_enable:
.LFB36:
	.loc 1 874 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 877 5
	lw	a4,-36(s0)
	li	a5,4096
	addi	a5,a5,-1792
	beq	a4,a5,.L101
	lw	a4,-36(s0)
	li	a5,4096
	addi	a5,a5,-1792
	bgtu	a4,a5,.L102
	lw	a4,-36(s0)
	li	a5,28
	bgtu	a4,a5,.L96
	lw	a4,-36(s0)
	li	a5,28
	bgtu	a4,a5,.L102
	lw	a5,-36(s0)
	slli	a4,a5,2
	lla	a5,.L97
	add	a5,a4,a5
	lw	a4,0(a5)
	lla	a5,.L97
	add	a5,a4,a5
	jr	a5
	.section	.rodata
	.align	2
	.align	2
.L97:
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L98-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.word	.L102-.L97
	.text
.L96:
	lw	a5,-36(s0)
	addi	a5,a5,-2048
	beq	a5,zero,.L99
	.loc 1 897 9
	j	.L102
.L98:
	.loc 1 880 16
	li	a5,1073876992
	.loc 1 880 13
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 881 93
	li	a5,1073876992
	lw	a3,0(a5)
	li	a5,1073876992
	li	a4,-65536
	addi	a4,a4,-1
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 882 10
	li	a5,1073876992
	.loc 1 882 100
	lw	a3,-20(s0)
	li	a4,262144
	or	a4,a3,a4
	.loc 1 882 93
	sw	a4,0(a5)
	.loc 1 883 9
	j	.L100
.L99:
	.loc 1 886 16
	li	a5,1073876992
	addi	a5,a5,32
	.loc 1 886 13
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 887 93
	li	a5,1073876992
	addi	a5,a5,32
	lw	a4,0(a5)
	li	a5,1073876992
	addi	a5,a5,32
	andi	a4,a4,-2
	sw	a4,0(a5)
	.loc 1 888 10
	li	a5,1073876992
	addi	a5,a5,32
	.loc 1 888 100
	lw	a4,-20(s0)
	ori	a4,a4,4
	.loc 1 888 93
	sw	a4,0(a5)
	.loc 1 889 9
	j	.L100
.L101:
	.loc 1 895 9
	nop
	j	.L103
.L102:
	.loc 1 897 9
	nop
.L100:
.L103:
	.loc 1 899 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE36:
	.size	rcu_osci_bypass_mode_enable, .-rcu_osci_bypass_mode_enable
	.align	1
	.globl	rcu_osci_bypass_mode_disable
	.type	rcu_osci_bypass_mode_disable, @function
rcu_osci_bypass_mode_disable:
.LFB37:
	.loc 1 911 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 914 5
	lw	a4,-36(s0)
	li	a5,4096
	addi	a5,a5,-1792
	beq	a4,a5,.L112
	lw	a4,-36(s0)
	li	a5,4096
	addi	a5,a5,-1792
	bgtu	a4,a5,.L113
	lw	a4,-36(s0)
	li	a5,28
	bgtu	a4,a5,.L107
	lw	a4,-36(s0)
	li	a5,28
	bgtu	a4,a5,.L113
	lw	a5,-36(s0)
	slli	a4,a5,2
	lla	a5,.L108
	add	a5,a4,a5
	lw	a4,0(a5)
	lla	a5,.L108
	add	a5,a4,a5
	jr	a5
	.section	.rodata
	.align	2
	.align	2
.L108:
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L109-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.word	.L113-.L108
	.text
.L107:
	lw	a5,-36(s0)
	addi	a5,a5,-2048
	beq	a5,zero,.L110
	.loc 1 934 9
	j	.L113
.L109:
	.loc 1 917 16
	li	a5,1073876992
	.loc 1 917 13
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 918 93
	li	a5,1073876992
	lw	a3,0(a5)
	li	a5,1073876992
	li	a4,-65536
	addi	a4,a4,-1
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 919 10
	li	a5,1073876992
	.loc 1 919 100
	lw	a3,-20(s0)
	li	a4,-262144
	addi	a4,a4,-1
	and	a4,a3,a4
	.loc 1 919 93
	sw	a4,0(a5)
	.loc 1 920 9
	j	.L111
.L110:
	.loc 1 923 16
	li	a5,1073876992
	addi	a5,a5,32
	.loc 1 923 13
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 924 93
	li	a5,1073876992
	addi	a5,a5,32
	lw	a4,0(a5)
	li	a5,1073876992
	addi	a5,a5,32
	andi	a4,a4,-2
	sw	a4,0(a5)
	.loc 1 925 10
	li	a5,1073876992
	addi	a5,a5,32
	.loc 1 925 100
	lw	a4,-20(s0)
	andi	a4,a4,-5
	.loc 1 925 93
	sw	a4,0(a5)
	.loc 1 926 9
	j	.L111
.L112:
	.loc 1 932 9
	nop
	j	.L114
.L113:
	.loc 1 934 9
	nop
.L111:
.L114:
	.loc 1 936 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE37:
	.size	rcu_osci_bypass_mode_disable, .-rcu_osci_bypass_mode_disable
	.align	1
	.globl	rcu_hxtal_clock_monitor_enable
	.type	rcu_hxtal_clock_monitor_enable, @function
rcu_hxtal_clock_monitor_enable:
.LFB38:
	.loc 1 946 1
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,12(sp)
	.cfi_offset 8, -4
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 947 89
	li	a5,1073876992
	lw	a3,0(a5)
	li	a5,1073876992
	li	a4,524288
	or	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 948 1
	nop
	lw	s0,12(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE38:
	.size	rcu_hxtal_clock_monitor_enable, .-rcu_hxtal_clock_monitor_enable
	.align	1
	.globl	rcu_hxtal_clock_monitor_disable
	.type	rcu_hxtal_clock_monitor_disable, @function
rcu_hxtal_clock_monitor_disable:
.LFB39:
	.loc 1 957 1
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,12(sp)
	.cfi_offset 8, -4
	addi	s0,sp,16
	.cfi_def_cfa 8, 0
	.loc 1 958 89
	li	a5,1073876992
	lw	a3,0(a5)
	li	a5,1073876992
	li	a4,-524288
	addi	a4,a4,-1
	and	a4,a3,a4
	sw	a4,0(a5)
	.loc 1 959 1
	nop
	lw	s0,12(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE39:
	.size	rcu_hxtal_clock_monitor_disable, .-rcu_hxtal_clock_monitor_disable
	.align	1
	.globl	rcu_irc8m_adjust_value_set
	.type	rcu_irc8m_adjust_value_set, @function
rcu_irc8m_adjust_value_set:
.LFB40:
	.loc 1 968 1
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	s0,44(sp)
	.cfi_offset 8, -4
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	sw	a0,-36(s0)
	.loc 1 971 12
	li	a5,1073876992
	.loc 1 971 9
	lw	a5,0(a5)
	sw	a5,-20(s0)
	.loc 1 973 9
	lw	a5,-20(s0)
	andi	a5,a5,-249
	sw	a5,-20(s0)
	.loc 1 974 122
	lw	a5,-36(s0)
	slli	a5,a5,3
	andi	a3,a5,255
	.loc 1 974 6
	li	a5,1073876992
	.loc 1 974 96
	lw	a4,-20(s0)
	or	a4,a3,a4
	.loc 1 974 89
	sw	a4,0(a5)
	.loc 1 975 1
	nop
	lw	s0,44(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 48
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE40:
	.size	rcu_irc8m_adjust_value_set, .-rcu_irc8m_adjust_value_set
	.align	1
	.globl	rcu_deepsleep_voltage_set
	.type	rcu_deepsleep_voltage_set, @function
rcu_deepsleep_voltage_set:
.LFB41:
	.loc 1 989 1
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,28(sp)
	.cfi_offset 8, -4
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	a0,-20(s0)
	.loc 1 990 11
	lw	a5,-20(s0)
	andi	a5,a5,3
	sw	a5,-20(s0)
	.loc 1 991 6
	li	a5,1073876992
	addi	a5,a5,52
	.loc 1 991 89
	lw	a4,-20(s0)
	sw	a4,0(a5)
	.loc 1 992 1
	nop
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE41:
	.size	rcu_deepsleep_voltage_set, .-rcu_deepsleep_voltage_set
	.section	.rodata
	.align	2
.LC0:
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.ascii	"\001\002\003\004\006\007\b\t"
	.text
	.align	1
	.globl	rcu_clock_freq_get
	.type	rcu_clock_freq_get, @function
rcu_clock_freq_get:
.LFB42:
	.loc 1 1006 1
	.cfi_startproc
	addi	sp,sp,-128
	.cfi_def_cfa_offset 128
	sw	s0,124(sp)
	.cfi_offset 8, -4
	addi	s0,sp,128
	.cfi_def_cfa 8, 0
	sw	a0,-116(s0)
	.loc 1 1007 19
	sw	zero,-20(s0)
	.loc 1 1013 13
	lla	a5,.LC0
	lw	a2,0(a5)
	lw	a3,4(a5)
	lw	a4,8(a5)
	lw	a5,12(a5)
	sw	a2,-92(s0)
	sw	a3,-88(s0)
	sw	a4,-84(s0)
	sw	a5,-80(s0)
	.loc 1 1014 13
	sw	zero,-100(s0)
	li	a5,67305472
	addi	a5,a5,513
	sw	a5,-96(s0)
	.loc 1 1015 13
	sw	zero,-108(s0)
	li	a5,67305472
	addi	a5,a5,513
	sw	a5,-104(s0)
	.loc 1 1017 15
	li	a5,1073876992
	addi	a5,a5,4
	lw	a5,0(a5)
	.loc 1 1017 172
	srli	a5,a5,2
	.loc 1 1017 9
	andi	a5,a5,3
	sw	a5,-40(s0)
	.loc 1 1018 5
	lw	a4,-40(s0)
	li	a5,2
	beq	a4,a5,.L120
	lw	a4,-40(s0)
	li	a5,2
	bgtu	a4,a5,.L121
	lw	a5,-40(s0)
	beq	a5,zero,.L122
	lw	a4,-40(s0)
	li	a5,1
	beq	a4,a5,.L123
	j	.L121
.L122:
	.loc 1 1021 20
	li	a5,7999488
	addi	a5,a5,512
	sw	a5,-24(s0)
	.loc 1 1022 9
	j	.L124
.L123:
	.loc 1 1025 20
	li	a5,7999488
	addi	a5,a5,512
	sw	a5,-24(s0)
	.loc 1 1026 9
	j	.L124
.L120:
	.loc 1 1030 20
	li	a5,1073876992
	addi	a5,a5,4
	lw	a4,0(a5)
	.loc 1 1030 16
	li	a5,65536
	and	a5,a4,a5
	sw	a5,-44(s0)
	.loc 1 1032 11
	lw	a4,-44(s0)
	li	a5,65536
	bne	a4,a5,.L125
	.loc 1 1034 20
	li	a5,7999488
	addi	a5,a5,512
	sw	a5,-32(s0)
	.loc 1 1036 27
	li	a5,1073876992
	addi	a5,a5,44
	lw	a4,0(a5)
	.loc 1 1036 23
	li	a5,65536
	and	a5,a4,a5
	sw	a5,-48(s0)
	.loc 1 1038 15
	lw	a4,-48(s0)
	li	a5,65536
	bne	a4,a5,.L126
	.loc 1 1039 39
	li	a5,1073876992
	addi	a5,a5,44
	lw	a5,0(a5)
	.loc 1 1039 26
	srli	a5,a5,4
	andi	a5,a5,15
	.loc 1 1039 24
	addi	a5,a5,1
	sw	a5,-52(s0)
	.loc 1 1040 39
	li	a5,1073876992
	addi	a5,a5,44
	lw	a5,0(a5)
	.loc 1 1040 26
	srli	a5,a5,8
	andi	a5,a5,15
	.loc 1 1040 24
	addi	a5,a5,2
	sw	a5,-36(s0)
	.loc 1 1041 19
	lw	a4,-36(s0)
	li	a5,17
	bne	a4,a5,.L127
	.loc 1 1042 28
	li	a5,20
	sw	a5,-36(s0)
.L127:
	.loc 1 1044 34
	lw	a4,-32(s0)
	lw	a5,-52(s0)
	divu	a5,a4,a5
	.loc 1 1044 24
	lw	a4,-36(s0)
	mul	a5,a4,a5
	sw	a5,-32(s0)
.L126:
	.loc 1 1046 24
	li	a5,1073876992
	addi	a5,a5,44
	lw	a5,0(a5)
	.loc 1 1046 107
	andi	a5,a5,15
	.loc 1 1046 20
	addi	a5,a5,1
	sw	a5,-56(s0)
	.loc 1 1047 20
	lw	a4,-32(s0)
	lw	a5,-56(s0)
	divu	a5,a4,a5
	sw	a5,-32(s0)
	j	.L128
.L125:
	.loc 1 1050 20
	li	a5,4001792
	addi	a5,a5,-1792
	sw	a5,-32(s0)
.L128:
	.loc 1 1054 21
	li	a5,1073876992
	addi	a5,a5,4
	lw	a5,0(a5)
	.loc 1 1054 180
	srli	a5,a5,18
	.loc 1 1054 15
	andi	a5,a5,15
	sw	a5,-28(s0)
	.loc 1 1055 14
	li	a5,1073876992
	addi	a5,a5,4
	lw	a4,0(a5)
	.loc 1 1055 97
	li	a5,536870912
	and	a5,a4,a5
	.loc 1 1055 11
	beq	a5,zero,.L129
	.loc 1 1056 19
	lw	a5,-28(s0)
	ori	a5,a5,16
	sw	a5,-28(s0)
.L129:
	.loc 1 1058 11
	lw	a4,-28(s0)
	li	a5,14
	bgtu	a4,a5,.L130
	.loc 1 1059 19
	lw	a5,-28(s0)
	addi	a5,a5,2
	sw	a5,-28(s0)
	j	.L131
.L130:
	.loc 1 1061 19
	lw	a5,-28(s0)
	addi	a5,a5,1
	sw	a5,-28(s0)
.L131:
	.loc 1 1064 20
	lw	a4,-32(s0)
	lw	a5,-28(s0)
	mul	a5,a4,a5
	sw	a5,-24(s0)
	.loc 1 1066 11
	lw	a4,-28(s0)
	li	a5,15
	bne	a4,a5,.L140
	.loc 1 1068 33
	lw	a4,-32(s0)
	mv	a5,a4
	slli	a5,a5,1
	add	a5,a5,a4
	slli	a5,a5,1
	mv	a4,a5
	.loc 1 1068 47
	lw	a5,-32(s0)
	srli	a5,a5,1
	.loc 1 1068 24
	add	a5,a4,a5
	sw	a5,-24(s0)
	.loc 1 1071 9
	j	.L140
.L121:
	.loc 1 1074 20
	li	a5,7999488
	addi	a5,a5,512
	sw	a5,-24(s0)
	.loc 1 1075 9
	j	.L124
.L140:
	.loc 1 1071 9
	nop
.L124:
	.loc 1 1079 15
	li	a5,1073876992
	addi	a5,a5,4
	lw	a5,0(a5)
	.loc 1 1079 172
	srli	a5,a5,4
	.loc 1 1079 9
	andi	a5,a5,15
	sw	a5,-60(s0)
	.loc 1 1080 22
	lw	a5,-60(s0)
	addi	a4,s0,-16
	add	a5,a4,a5
	lbu	a5,-76(a5)
	.loc 1 1080 13
	sw	a5,-64(s0)
	.loc 1 1081 14
	lw	a5,-64(s0)
	lw	a4,-24(s0)
	srl	a5,a4,a5
	sw	a5,-68(s0)
	.loc 1 1084 15
	li	a5,1073876992
	addi	a5,a5,4
	lw	a5,0(a5)
	.loc 1 1084 173
	srli	a5,a5,8
	.loc 1 1084 9
	andi	a5,a5,7
	sw	a5,-60(s0)
	.loc 1 1085 23
	lw	a5,-60(s0)
	addi	a4,s0,-16
	add	a5,a4,a5
	lbu	a5,-84(a5)
	.loc 1 1085 13
	sw	a5,-64(s0)
	.loc 1 1086 15
	lw	a5,-64(s0)
	lw	a4,-68(s0)
	srl	a5,a4,a5
	sw	a5,-72(s0)
	.loc 1 1089 15
	li	a5,1073876992
	addi	a5,a5,4
	lw	a5,0(a5)
	.loc 1 1089 174
	srli	a5,a5,11
	.loc 1 1089 9
	andi	a5,a5,7
	sw	a5,-60(s0)
	.loc 1 1090 23
	lw	a5,-60(s0)
	addi	a4,s0,-16
	add	a5,a4,a5
	lbu	a5,-92(a5)
	.loc 1 1090 13
	sw	a5,-64(s0)
	.loc 1 1091 15
	lw	a5,-64(s0)
	lw	a4,-68(s0)
	srl	a5,a4,a5
	sw	a5,-76(s0)
	.loc 1 1094 5
	lw	a4,-116(s0)
	li	a5,3
	beq	a4,a5,.L133
	lw	a4,-116(s0)
	li	a5,3
	bgtu	a4,a5,.L141
	lw	a4,-116(s0)
	li	a5,2
	beq	a4,a5,.L135
	lw	a4,-116(s0)
	li	a5,2
	bgtu	a4,a5,.L141
	lw	a5,-116(s0)
	beq	a5,zero,.L136
	lw	a4,-116(s0)
	li	a5,1
	beq	a4,a5,.L137
	.loc 1 1108 9
	j	.L141
.L136:
	.loc 1 1096 17
	lw	a5,-24(s0)
	sw	a5,-20(s0)
	.loc 1 1097 9
	j	.L138
.L137:
	.loc 1 1099 17
	lw	a5,-68(s0)
	sw	a5,-20(s0)
	.loc 1 1100 9
	j	.L138
.L135:
	.loc 1 1102 17
	lw	a5,-72(s0)
	sw	a5,-20(s0)
	.loc 1 1103 9
	j	.L138
.L133:
	.loc 1 1105 17
	lw	a5,-76(s0)
	sw	a5,-20(s0)
	.loc 1 1106 9
	j	.L138
.L141:
	.loc 1 1108 9
	nop
.L138:
	.loc 1 1110 12
	lw	a5,-20(s0)
	.loc 1 1111 1
	mv	a0,a5
	lw	s0,124(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 128
	addi	sp,sp,128
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE42:
	.size	rcu_clock_freq_get, .-rcu_clock_freq_get
.Letext0:
	.file 2 "d:\\gcc\\xpack-riscv-none-embed-gcc-10.2.0-1.2\\riscv-none-embed\\include\\machine\\_default_types.h"
	.file 3 "d:\\gcc\\xpack-riscv-none-embed-gcc-10.2.0-1.2\\riscv-none-embed\\include\\sys\\_stdint.h"
	.file 4 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral/gd32vf103.h"
	.file 5 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_rcu.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xda8
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.byte	0x1
	.4byte	.LASF3406
	.byte	0xc
	.4byte	.LASF3407
	.4byte	.LASF3408
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.4byte	.Ldebug_macro0
	.byte	0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3174
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF3175
	.byte	0x3
	.4byte	.LASF3178
	.byte	0x2
	.byte	0x2b
	.byte	0x17
	.4byte	0x43
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3176
	.byte	0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF3177
	.byte	0x3
	.4byte	.LASF3179
	.byte	0x2
	.byte	0x39
	.byte	0x1c
	.4byte	0x5d
	.byte	0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3180
	.byte	0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF3181
	.byte	0x3
	.4byte	.LASF3182
	.byte	0x2
	.byte	0x4f
	.byte	0x1b
	.4byte	0x77
	.byte	0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3183
	.byte	0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF3184
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF3185
	.byte	0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0x3
	.4byte	.LASF3186
	.byte	0x3
	.byte	0x18
	.byte	0x13
	.4byte	0x37
	.byte	0x3
	.4byte	.LASF3187
	.byte	0x3
	.byte	0x24
	.byte	0x14
	.4byte	0x51
	.byte	0x3
	.4byte	.LASF3188
	.byte	0x3
	.byte	0x30
	.byte	0x14
	.4byte	0x6b
	.byte	0x5
	.byte	0x7
	.byte	0x4
	.4byte	0x29
	.byte	0x4
	.byte	0xb5
	.byte	0xe
	.4byte	0xd2
	.byte	0x6
	.4byte	.LASF3189
	.byte	0
	.byte	0x7
	.string	"SET"
	.byte	0x1
	.byte	0
	.byte	0x3
	.4byte	.LASF3190
	.byte	0x4
	.byte	0xb5
	.byte	0x28
	.4byte	0xb7
	.byte	0x5
	.byte	0x7
	.byte	0x4
	.4byte	0x29
	.byte	0x4
	.byte	0xb6
	.byte	0xe
	.4byte	0xf9
	.byte	0x6
	.4byte	.LASF3191
	.byte	0
	.byte	0x6
	.4byte	.LASF3192
	.byte	0x1
	.byte	0
	.byte	0x3
	.4byte	.LASF3193
	.byte	0x4
	.byte	0xb6
	.byte	0x2c
	.4byte	0xde
	.byte	0x8
	.4byte	0x93
	.4byte	0x115
	.byte	0x9
	.4byte	0x29
	.byte	0x7
	.byte	0
	.byte	0x2
	.byte	0x10
	.byte	0x4
	.4byte	.LASF3194
	.byte	0xa
	.byte	0x7
	.byte	0x4
	.4byte	0x29
	.byte	0x5
	.2byte	0x106
	.byte	0xe
	.4byte	0x22f
	.byte	0xb
	.4byte	.LASF3195
	.2byte	0x500
	.byte	0xb
	.4byte	.LASF3196
	.2byte	0x501
	.byte	0xb
	.4byte	.LASF3197
	.2byte	0x506
	.byte	0xb
	.4byte	.LASF3198
	.2byte	0x508
	.byte	0xb
	.4byte	.LASF3199
	.2byte	0x50c
	.byte	0xb
	.4byte	.LASF3200
	.2byte	0x700
	.byte	0xb
	.4byte	.LASF3201
	.2byte	0x701
	.byte	0xb
	.4byte	.LASF3202
	.2byte	0x702
	.byte	0xb
	.4byte	.LASF3203
	.2byte	0x703
	.byte	0xb
	.4byte	.LASF3204
	.2byte	0x704
	.byte	0xb
	.4byte	.LASF3205
	.2byte	0x705
	.byte	0xb
	.4byte	.LASF3206
	.2byte	0x70b
	.byte	0xb
	.4byte	.LASF3207
	.2byte	0x70e
	.byte	0xb
	.4byte	.LASF3208
	.2byte	0x70f
	.byte	0xb
	.4byte	.LASF3209
	.2byte	0x711
	.byte	0xb
	.4byte	.LASF3210
	.2byte	0x712
	.byte	0xb
	.4byte	.LASF3211
	.2byte	0x713
	.byte	0xb
	.4byte	.LASF3212
	.2byte	0x714
	.byte	0xb
	.4byte	.LASF3213
	.2byte	0x715
	.byte	0xb
	.4byte	.LASF3214
	.2byte	0x716
	.byte	0xb
	.4byte	.LASF3215
	.2byte	0x719
	.byte	0xb
	.4byte	.LASF3216
	.2byte	0x71a
	.byte	0xb
	.4byte	.LASF3217
	.2byte	0x71b
	.byte	0xb
	.4byte	.LASF3218
	.2byte	0x71c
	.byte	0xb
	.4byte	.LASF3219
	.2byte	0x71d
	.byte	0xb
	.4byte	.LASF3220
	.2byte	0x80f
	.byte	0xb
	.4byte	.LASF3221
	.2byte	0x600
	.byte	0xb
	.4byte	.LASF3222
	.2byte	0x602
	.byte	0xb
	.4byte	.LASF3223
	.2byte	0x603
	.byte	0xb
	.4byte	.LASF3224
	.2byte	0x604
	.byte	0xb
	.4byte	.LASF3225
	.2byte	0x605
	.byte	0xb
	.4byte	.LASF3226
	.2byte	0x606
	.byte	0xb
	.4byte	.LASF3227
	.2byte	0x609
	.byte	0xb
	.4byte	.LASF3228
	.2byte	0x60a
	.byte	0xb
	.4byte	.LASF3229
	.2byte	0x60b
	.byte	0xb
	.4byte	.LASF3230
	.2byte	0x60c
	.byte	0xb
	.4byte	.LASF3231
	.2byte	0x60e
	.byte	0
	.byte	0xc
	.4byte	.LASF3232
	.byte	0x5
	.2byte	0x12f
	.byte	0x3
	.4byte	0x11c
	.byte	0xa
	.byte	0x7
	.byte	0x4
	.4byte	0x29
	.byte	0x5
	.2byte	0x132
	.byte	0xe
	.4byte	0x25a
	.byte	0xb
	.4byte	.LASF3233
	.2byte	0x502
	.byte	0xb
	.4byte	.LASF3234
	.2byte	0x504
	.byte	0
	.byte	0xc
	.4byte	.LASF3235
	.byte	0x5
	.2byte	0x136
	.byte	0x3
	.4byte	0x23c
	.byte	0xa
	.byte	0x7
	.byte	0x4
	.4byte	0x29
	.byte	0x5
	.2byte	0x139
	.byte	0xe
	.4byte	0x357
	.byte	0xb
	.4byte	.LASF3236
	.2byte	0xa0c
	.byte	0xb
	.4byte	.LASF3237
	.2byte	0x400
	.byte	0xb
	.4byte	.LASF3238
	.2byte	0x401
	.byte	0xb
	.4byte	.LASF3239
	.2byte	0x402
	.byte	0xb
	.4byte	.LASF3240
	.2byte	0x403
	.byte	0xb
	.4byte	.LASF3241
	.2byte	0x404
	.byte	0xb
	.4byte	.LASF3242
	.2byte	0x405
	.byte	0xb
	.4byte	.LASF3243
	.2byte	0x40b
	.byte	0xb
	.4byte	.LASF3244
	.2byte	0x40e
	.byte	0xb
	.4byte	.LASF3245
	.2byte	0x40f
	.byte	0xb
	.4byte	.LASF3246
	.2byte	0x411
	.byte	0xb
	.4byte	.LASF3247
	.2byte	0x412
	.byte	0xb
	.4byte	.LASF3248
	.2byte	0x413
	.byte	0xb
	.4byte	.LASF3249
	.2byte	0x414
	.byte	0xb
	.4byte	.LASF3250
	.2byte	0x415
	.byte	0xb
	.4byte	.LASF3251
	.2byte	0x416
	.byte	0xb
	.4byte	.LASF3252
	.2byte	0x419
	.byte	0xb
	.4byte	.LASF3253
	.2byte	0x41a
	.byte	0xb
	.4byte	.LASF3254
	.2byte	0x41b
	.byte	0xb
	.4byte	.LASF3255
	.2byte	0x41c
	.byte	0xb
	.4byte	.LASF3256
	.2byte	0x41d
	.byte	0xb
	.4byte	.LASF3257
	.2byte	0x300
	.byte	0xb
	.4byte	.LASF3258
	.2byte	0x302
	.byte	0xb
	.4byte	.LASF3259
	.2byte	0x303
	.byte	0xb
	.4byte	.LASF3260
	.2byte	0x304
	.byte	0xb
	.4byte	.LASF3261
	.2byte	0x305
	.byte	0xb
	.4byte	.LASF3262
	.2byte	0x306
	.byte	0xb
	.4byte	.LASF3263
	.2byte	0x309
	.byte	0xb
	.4byte	.LASF3264
	.2byte	0x30a
	.byte	0xb
	.4byte	.LASF3265
	.2byte	0x30b
	.byte	0xb
	.4byte	.LASF3266
	.2byte	0x30c
	.byte	0xb
	.4byte	.LASF3267
	.2byte	0x30e
	.byte	0
	.byte	0xc
	.4byte	.LASF3268
	.byte	0x5
	.2byte	0x15d
	.byte	0x3
	.4byte	0x267
	.byte	0xa
	.byte	0x7
	.byte	0x4
	.4byte	0x29
	.byte	0x5
	.2byte	0x160
	.byte	0xe
	.4byte	0x3ca
	.byte	0x6
	.4byte	.LASF3269
	.byte	0x1
	.byte	0x6
	.4byte	.LASF3270
	.byte	0x11
	.byte	0x6
	.4byte	.LASF3271
	.byte	0x19
	.byte	0x6
	.4byte	.LASF3272
	.byte	0x1b
	.byte	0x6
	.4byte	.LASF3273
	.byte	0x1d
	.byte	0xb
	.4byte	.LASF3274
	.2byte	0x801
	.byte	0xb
	.4byte	.LASF3275
	.2byte	0x901
	.byte	0xb
	.4byte	.LASF3276
	.2byte	0x91a
	.byte	0xb
	.4byte	.LASF3277
	.2byte	0x91b
	.byte	0xb
	.4byte	.LASF3278
	.2byte	0x91c
	.byte	0xb
	.4byte	.LASF3279
	.2byte	0x91d
	.byte	0xb
	.4byte	.LASF3280
	.2byte	0x91e
	.byte	0xb
	.4byte	.LASF3281
	.2byte	0x91f
	.byte	0
	.byte	0xc
	.4byte	.LASF3282
	.byte	0x5
	.2byte	0x170
	.byte	0x3
	.4byte	0x364
	.byte	0xa
	.byte	0x7
	.byte	0x4
	.4byte	0x29
	.byte	0x5
	.2byte	0x173
	.byte	0xe
	.4byte	0x41f
	.byte	0xb
	.4byte	.LASF3283
	.2byte	0x200
	.byte	0xb
	.4byte	.LASF3284
	.2byte	0x201
	.byte	0xb
	.4byte	.LASF3285
	.2byte	0x202
	.byte	0xb
	.4byte	.LASF3286
	.2byte	0x203
	.byte	0xb
	.4byte	.LASF3287
	.2byte	0x204
	.byte	0xb
	.4byte	.LASF3288
	.2byte	0x205
	.byte	0xb
	.4byte	.LASF3289
	.2byte	0x206
	.byte	0xb
	.4byte	.LASF3290
	.2byte	0x207
	.byte	0
	.byte	0xc
	.4byte	.LASF3291
	.byte	0x5
	.2byte	0x17c
	.byte	0x3
	.4byte	0x3d7
	.byte	0xa
	.byte	0x7
	.byte	0x4
	.4byte	0x29
	.byte	0x5
	.2byte	0x17f
	.byte	0xe
	.4byte	0x474
	.byte	0xb
	.4byte	.LASF3292
	.2byte	0x210
	.byte	0xb
	.4byte	.LASF3293
	.2byte	0x211
	.byte	0xb
	.4byte	.LASF3294
	.2byte	0x212
	.byte	0xb
	.4byte	.LASF3295
	.2byte	0x213
	.byte	0xb
	.4byte	.LASF3296
	.2byte	0x214
	.byte	0xb
	.4byte	.LASF3297
	.2byte	0x215
	.byte	0xb
	.4byte	.LASF3298
	.2byte	0x216
	.byte	0xb
	.4byte	.LASF3299
	.2byte	0x217
	.byte	0
	.byte	0xc
	.4byte	.LASF3300
	.byte	0x5
	.2byte	0x188
	.byte	0x3
	.4byte	0x42c
	.byte	0xa
	.byte	0x7
	.byte	0x4
	.4byte	0x29
	.byte	0x5
	.2byte	0x18b
	.byte	0xe
	.4byte	0x4c2
	.byte	0xb
	.4byte	.LASF3301
	.2byte	0x208
	.byte	0xb
	.4byte	.LASF3302
	.2byte	0x209
	.byte	0xb
	.4byte	.LASF3303
	.2byte	0x20a
	.byte	0xb
	.4byte	.LASF3304
	.2byte	0x20b
	.byte	0xb
	.4byte	.LASF3305
	.2byte	0x20c
	.byte	0xb
	.4byte	.LASF3306
	.2byte	0x20d
	.byte	0xb
	.4byte	.LASF3307
	.2byte	0x20e
	.byte	0
	.byte	0xc
	.4byte	.LASF3308
	.byte	0x5
	.2byte	0x193
	.byte	0x3
	.4byte	0x481
	.byte	0xa
	.byte	0x7
	.byte	0x4
	.4byte	0x29
	.byte	0x5
	.2byte	0x196
	.byte	0xe
	.4byte	0x50b
	.byte	0x6
	.4byte	.LASF3309
	.byte	0x10
	.byte	0xb
	.4byte	.LASF3310
	.2byte	0x800
	.byte	0x6
	.4byte	.LASF3311
	.byte	0
	.byte	0xb
	.4byte	.LASF3312
	.2byte	0x900
	.byte	0x6
	.4byte	.LASF3313
	.byte	0x18
	.byte	0x6
	.4byte	.LASF3314
	.byte	0x1a
	.byte	0x6
	.4byte	.LASF3315
	.byte	0x1c
	.byte	0
	.byte	0xc
	.4byte	.LASF3316
	.byte	0x5
	.2byte	0x19e
	.byte	0x3
	.4byte	0x4cf
	.byte	0xa
	.byte	0x7
	.byte	0x4
	.4byte	0x29
	.byte	0x5
	.2byte	0x1a1
	.byte	0xe
	.4byte	0x540
	.byte	0x6
	.4byte	.LASF3317
	.byte	0
	.byte	0x6
	.4byte	.LASF3318
	.byte	0x1
	.byte	0x6
	.4byte	.LASF3319
	.byte	0x2
	.byte	0x6
	.4byte	.LASF3320
	.byte	0x3
	.byte	0
	.byte	0xc
	.4byte	.LASF3321
	.byte	0x5
	.2byte	0x1a6
	.byte	0x3
	.4byte	0x518
	.byte	0xd
	.4byte	.LASF3350
	.byte	0x1
	.2byte	0x3ed
	.byte	0xa
	.4byte	0xab
	.4byte	.LFB42
	.4byte	.LFE42-.LFB42
	.byte	0x1
	.byte	0x9c
	.4byte	0x6a0
	.byte	0xe
	.4byte	.LASF3338
	.byte	0x1
	.2byte	0x3ed
	.byte	0x31
	.4byte	0x540
	.byte	0x3
	.byte	0x91
	.byte	0x8c,0x7f
	.byte	0xf
	.string	"sws"
	.byte	0x1
	.2byte	0x3ef
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x58
	.byte	0x10
	.4byte	.LASF3322
	.byte	0x1
	.2byte	0x3ef
	.byte	0x13
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0x10
	.4byte	.LASF3323
	.byte	0x1
	.2byte	0x3f0
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0x10
	.4byte	.LASF3324
	.byte	0x1
	.2byte	0x3f0
	.byte	0x1a
	.4byte	0xab
	.byte	0x3
	.byte	0x91
	.byte	0xbc,0x7f
	.byte	0x10
	.4byte	.LASF3325
	.byte	0x1
	.2byte	0x3f0
	.byte	0x24
	.4byte	0xab
	.byte	0x3
	.byte	0x91
	.byte	0xb8,0x7f
	.byte	0x10
	.4byte	.LASF3326
	.byte	0x1
	.2byte	0x3f0
	.byte	0x2f
	.4byte	0xab
	.byte	0x3
	.byte	0x91
	.byte	0xb4,0x7f
	.byte	0x10
	.4byte	.LASF3327
	.byte	0x1
	.2byte	0x3f1
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x54
	.byte	0x10
	.4byte	.LASF3328
	.byte	0x1
	.2byte	0x3f1
	.byte	0x16
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x50
	.byte	0x10
	.4byte	.LASF3329
	.byte	0x1
	.2byte	0x3f1
	.byte	0x21
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x64
	.byte	0x10
	.4byte	.LASF3330
	.byte	0x1
	.2byte	0x3f1
	.byte	0x27
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x60
	.byte	0xf
	.string	"idx"
	.byte	0x1
	.2byte	0x3f1
	.byte	0x2f
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x44
	.byte	0x10
	.4byte	.LASF3331
	.byte	0x1
	.2byte	0x3f1
	.byte	0x34
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x40
	.byte	0x10
	.4byte	.LASF3332
	.byte	0x1
	.2byte	0x3f2
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x48
	.byte	0x10
	.4byte	.LASF3333
	.byte	0x1
	.2byte	0x3f2
	.byte	0x16
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x4c
	.byte	0x10
	.4byte	.LASF3334
	.byte	0x1
	.2byte	0x3f2
	.byte	0x1e
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0x10
	.4byte	.LASF3335
	.byte	0x1
	.2byte	0x3f5
	.byte	0xd
	.4byte	0x6a0
	.byte	0x3
	.byte	0x91
	.byte	0xa4,0x7f
	.byte	0x10
	.4byte	.LASF3336
	.byte	0x1
	.2byte	0x3f6
	.byte	0xd
	.4byte	0x105
	.byte	0x3
	.byte	0x91
	.byte	0x9c,0x7f
	.byte	0x10
	.4byte	.LASF3337
	.byte	0x1
	.2byte	0x3f7
	.byte	0xd
	.4byte	0x105
	.byte	0x3
	.byte	0x91
	.byte	0x94,0x7f
	.byte	0
	.byte	0x8
	.4byte	0x93
	.4byte	0x6b0
	.byte	0x9
	.4byte	0x29
	.byte	0xf
	.byte	0
	.byte	0x11
	.4byte	.LASF3340
	.byte	0x1
	.2byte	0x3dc
	.byte	0x6
	.4byte	.LFB41
	.4byte	.LFE41-.LFB41
	.byte	0x1
	.byte	0x9c
	.4byte	0x6d8
	.byte	0xe
	.4byte	.LASF3339
	.byte	0x1
	.2byte	0x3dc
	.byte	0x29
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3341
	.byte	0x1
	.2byte	0x3c7
	.byte	0x6
	.4byte	.LFB40
	.4byte	.LFE40-.LFB40
	.byte	0x1
	.byte	0x9c
	.4byte	0x710
	.byte	0xe
	.4byte	.LASF3342
	.byte	0x1
	.2byte	0x3c7
	.byte	0x2a
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x3c9
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x12
	.4byte	.LASF3343
	.byte	0x1
	.2byte	0x3bc
	.byte	0x6
	.4byte	.LFB39
	.4byte	.LFE39-.LFB39
	.byte	0x1
	.byte	0x9c
	.byte	0x12
	.4byte	.LASF3344
	.byte	0x1
	.2byte	0x3b1
	.byte	0x6
	.4byte	.LFB38
	.4byte	.LFE38-.LFB38
	.byte	0x1
	.byte	0x9c
	.byte	0x11
	.4byte	.LASF3345
	.byte	0x1
	.2byte	0x38e
	.byte	0x6
	.4byte	.LFB37
	.4byte	.LFE37-.LFB37
	.byte	0x1
	.byte	0x9c
	.4byte	0x76e
	.byte	0xe
	.4byte	.LASF3346
	.byte	0x1
	.2byte	0x38e
	.byte	0x36
	.4byte	0x50b
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x390
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3347
	.byte	0x1
	.2byte	0x369
	.byte	0x6
	.4byte	.LFB36
	.4byte	.LFE36-.LFB36
	.byte	0x1
	.byte	0x9c
	.4byte	0x7a6
	.byte	0xe
	.4byte	.LASF3346
	.byte	0x1
	.2byte	0x369
	.byte	0x35
	.4byte	0x50b
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x36b
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3348
	.byte	0x1
	.2byte	0x35b
	.byte	0x6
	.4byte	.LFB35
	.4byte	.LFE35-.LFB35
	.byte	0x1
	.byte	0x9c
	.4byte	0x7ce
	.byte	0xe
	.4byte	.LASF3346
	.byte	0x1
	.2byte	0x35b
	.byte	0x26
	.4byte	0x50b
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3349
	.byte	0x1
	.2byte	0x348
	.byte	0x6
	.4byte	.LFB34
	.4byte	.LFE34-.LFB34
	.byte	0x1
	.byte	0x9c
	.4byte	0x7f6
	.byte	0xe
	.4byte	.LASF3346
	.byte	0x1
	.2byte	0x348
	.byte	0x25
	.4byte	0x50b
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x13
	.4byte	.LASF3351
	.byte	0x1
	.2byte	0x2d2
	.byte	0xb
	.4byte	0xf9
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.byte	0x1
	.byte	0x9c
	.4byte	0x852
	.byte	0xe
	.4byte	.LASF3346
	.byte	0x1
	.2byte	0x2d2
	.byte	0x31
	.4byte	0x50b
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0x10
	.4byte	.LASF3352
	.byte	0x1
	.2byte	0x2d4
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0x10
	.4byte	.LASF3353
	.byte	0x1
	.2byte	0x2d5
	.byte	0xf
	.4byte	0xf9
	.byte	0x2
	.byte	0x91
	.byte	0x68
	.byte	0x10
	.4byte	.LASF3354
	.byte	0x1
	.2byte	0x2d6
	.byte	0x10
	.4byte	0xd2
	.byte	0x2
	.byte	0x91
	.byte	0x64
	.byte	0
	.byte	0x11
	.4byte	.LASF3355
	.byte	0x1
	.2byte	0x2bf
	.byte	0x6
	.4byte	.LFB32
	.4byte	.LFE32-.LFB32
	.byte	0x1
	.byte	0x9c
	.4byte	0x87a
	.byte	0xe
	.4byte	.LASF3356
	.byte	0x1
	.2byte	0x2bf
	.byte	0x29
	.4byte	0x4c2
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3357
	.byte	0x1
	.2byte	0x2ac
	.byte	0x6
	.4byte	.LFB31
	.4byte	.LFE31-.LFB31
	.byte	0x1
	.byte	0x9c
	.4byte	0x8a2
	.byte	0xe
	.4byte	.LASF3356
	.byte	0x1
	.2byte	0x2ac
	.byte	0x28
	.4byte	0x4c2
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3358
	.byte	0x1
	.2byte	0x299
	.byte	0x6
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.byte	0x1
	.byte	0x9c
	.4byte	0x8ca
	.byte	0xe
	.4byte	.LASF3359
	.byte	0x1
	.2byte	0x299
	.byte	0x37
	.4byte	0x474
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0xd
	.4byte	.LASF3360
	.byte	0x1
	.2byte	0x280
	.byte	0xc
	.4byte	0xd2
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.byte	0x1
	.byte	0x9c
	.4byte	0x8f6
	.byte	0xe
	.4byte	.LASF3361
	.byte	0x1
	.2byte	0x280
	.byte	0x35
	.4byte	0x41f
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x12
	.4byte	.LASF3362
	.byte	0x1
	.2byte	0x26c
	.byte	0x6
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.byte	0x1
	.byte	0x9c
	.byte	0xd
	.4byte	.LASF3363
	.byte	0x1
	.2byte	0x25c
	.byte	0xc
	.4byte	0xd2
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.byte	0x1
	.byte	0x9c
	.4byte	0x935
	.byte	0xe
	.4byte	.LASF3364
	.byte	0x1
	.2byte	0x25c
	.byte	0x27
	.4byte	0x3ca
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3365
	.byte	0x1
	.2byte	0x23e
	.byte	0x6
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.byte	0x1
	.byte	0x9c
	.4byte	0x96d
	.byte	0xe
	.4byte	.LASF3366
	.byte	0x1
	.2byte	0x23e
	.byte	0x25
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x240
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3367
	.byte	0x1
	.2byte	0x22b
	.byte	0x6
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.byte	0x1
	.byte	0x9c
	.4byte	0x9a5
	.byte	0xe
	.4byte	.LASF3366
	.byte	0x1
	.2byte	0x22b
	.byte	0x25
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x22d
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3368
	.byte	0x1
	.2byte	0x218
	.byte	0x6
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.byte	0x1
	.byte	0x9c
	.4byte	0x9dd
	.byte	0xe
	.4byte	.LASF3369
	.byte	0x1
	.2byte	0x218
	.byte	0x24
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x21a
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3370
	.byte	0x1
	.2byte	0x202
	.byte	0x6
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.byte	0x1
	.byte	0x9c
	.4byte	0xa15
	.byte	0xe
	.4byte	.LASF3371
	.byte	0x1
	.2byte	0x202
	.byte	0x24
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x204
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3372
	.byte	0x1
	.2byte	0x1d8
	.byte	0x6
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.byte	0x1
	.byte	0x9c
	.4byte	0xa4d
	.byte	0xe
	.4byte	.LASF3373
	.byte	0x1
	.2byte	0x1d8
	.byte	0x24
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0x10
	.4byte	.LASF3374
	.byte	0x1
	.2byte	0x1da
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3375
	.byte	0x1
	.2byte	0x1c5
	.byte	0x6
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.byte	0x1
	.byte	0x9c
	.4byte	0xa75
	.byte	0xe
	.4byte	.LASF3376
	.byte	0x1
	.2byte	0x1c5
	.byte	0x1f
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3377
	.byte	0x1
	.2byte	0x1b7
	.byte	0x6
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.byte	0x1
	.byte	0x9c
	.4byte	0xa9d
	.byte	0xe
	.4byte	.LASF3376
	.byte	0x1
	.2byte	0x1b7
	.byte	0x1f
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3378
	.byte	0x1
	.2byte	0x1a2
	.byte	0x6
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.byte	0x1
	.byte	0x9c
	.4byte	0xad5
	.byte	0xe
	.4byte	.LASF3379
	.byte	0x1
	.2byte	0x1a2
	.byte	0x21
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x1a4
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3380
	.byte	0x1
	.2byte	0x18d
	.byte	0x6
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.byte	0x1
	.byte	0x9c
	.4byte	0xb1d
	.byte	0xe
	.4byte	.LASF3381
	.byte	0x1
	.2byte	0x18d
	.byte	0x21
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xe
	.4byte	.LASF3382
	.byte	0x1
	.2byte	0x18d
	.byte	0x39
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x58
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x18f
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3383
	.byte	0x1
	.2byte	0x174
	.byte	0x6
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.byte	0x1
	.byte	0x9c
	.4byte	0xb65
	.byte	0xe
	.4byte	.LASF3384
	.byte	0x1
	.2byte	0x174
	.byte	0x1e
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xe
	.4byte	.LASF3376
	.byte	0x1
	.2byte	0x174
	.byte	0x30
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x58
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x176
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3385
	.byte	0x1
	.2byte	0x15d
	.byte	0x6
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.byte	0x1
	.byte	0x9c
	.4byte	0xb9d
	.byte	0xe
	.4byte	.LASF3386
	.byte	0x1
	.2byte	0x15d
	.byte	0x21
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x15f
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3387
	.byte	0x1
	.2byte	0x142
	.byte	0x6
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.byte	0x1
	.byte	0x9c
	.4byte	0xbd5
	.byte	0xe
	.4byte	.LASF3388
	.byte	0x1
	.2byte	0x142
	.byte	0x25
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x144
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3389
	.byte	0x1
	.2byte	0x12b
	.byte	0x6
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.byte	0x1
	.byte	0x9c
	.4byte	0xc0d
	.byte	0xe
	.4byte	.LASF3390
	.byte	0x1
	.2byte	0x12b
	.byte	0x25
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x12d
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x11
	.4byte	.LASF3391
	.byte	0x1
	.2byte	0x114
	.byte	0x6
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.byte	0x1
	.byte	0x9c
	.4byte	0xc45
	.byte	0xe
	.4byte	.LASF3392
	.byte	0x1
	.2byte	0x114
	.byte	0x24
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0xf
	.string	"reg"
	.byte	0x1
	.2byte	0x116
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x14
	.4byte	.LASF3409
	.byte	0x1
	.2byte	0x107
	.byte	0xa
	.4byte	0xab
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.byte	0x1
	.byte	0x9c
	.byte	0x15
	.4byte	.LASF3393
	.byte	0x1
	.byte	0xf4
	.byte	0x6
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.byte	0x1
	.byte	0x9c
	.4byte	0xc91
	.byte	0x16
	.4byte	.LASF3394
	.byte	0x1
	.byte	0xf4
	.byte	0x2e
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x5c
	.byte	0x17
	.string	"reg"
	.byte	0x1
	.byte	0xf6
	.byte	0xe
	.4byte	0xab
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x18
	.4byte	.LASF3395
	.byte	0x1
	.byte	0xe5
	.byte	0x6
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.byte	0x1
	.byte	0x9c
	.byte	0x18
	.4byte	.LASF3396
	.byte	0x1
	.byte	0xda
	.byte	0x6
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.byte	0x1
	.byte	0x9c
	.byte	0x15
	.4byte	.LASF3397
	.byte	0x1
	.byte	0xcf
	.byte	0x6
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.byte	0x1
	.byte	0x9c
	.4byte	0xcdb
	.byte	0x16
	.4byte	.LASF3398
	.byte	0x1
	.byte	0xcf
	.byte	0x35
	.4byte	0x357
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x15
	.4byte	.LASF3399
	.byte	0x1
	.byte	0xb5
	.byte	0x6
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.byte	0x1
	.byte	0x9c
	.4byte	0xd01
	.byte	0x16
	.4byte	.LASF3398
	.byte	0x1
	.byte	0xb5
	.byte	0x34
	.4byte	0x357
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x15
	.4byte	.LASF3400
	.byte	0x1
	.byte	0x9b
	.byte	0x6
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.byte	0x1
	.byte	0x9c
	.4byte	0xd27
	.byte	0x16
	.4byte	.LASF3401
	.byte	0x1
	.byte	0x9b
	.byte	0x3b
	.4byte	0x25a
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x15
	.4byte	.LASF3402
	.byte	0x1
	.byte	0x8d
	.byte	0x6
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.byte	0x1
	.byte	0x9c
	.4byte	0xd4d
	.byte	0x16
	.4byte	.LASF3401
	.byte	0x1
	.byte	0x8d
	.byte	0x3a
	.4byte	0x25a
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x15
	.4byte	.LASF3403
	.byte	0x1
	.byte	0x7f
	.byte	0x6
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.byte	0x1
	.byte	0x9c
	.4byte	0xd73
	.byte	0x16
	.4byte	.LASF3401
	.byte	0x1
	.byte	0x7f
	.byte	0x2f
	.4byte	0x22f
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x15
	.4byte	.LASF3404
	.byte	0x1
	.byte	0x61
	.byte	0x6
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.byte	0x1
	.byte	0x9c
	.4byte	0xd99
	.byte	0x16
	.4byte	.LASF3401
	.byte	0x1
	.byte	0x61
	.byte	0x2e
	.4byte	0x22f
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x19
	.4byte	.LASF3405
	.byte	0x1
	.byte	0x35
	.byte	0x6
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.byte	0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.byte	0xe
	.byte	0x13
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0x1b
	.byte	0xe
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x10
	.byte	0x17
	.byte	0x99,0x42
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0x2
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0
	.byte	0
	.byte	0x3
	.byte	0x16
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x4
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0x8
	.byte	0
	.byte	0
	.byte	0x5
	.byte	0x4
	.byte	0x1
	.byte	0x3e
	.byte	0xb
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x6
	.byte	0x28
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x1c
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0x7
	.byte	0x28
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x1c
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0x8
	.byte	0x1
	.byte	0x1
	.byte	0x49
	.byte	0x13
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0xa
	.byte	0x4
	.byte	0x1
	.byte	0x3e
	.byte	0xb
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xb
	.byte	0x28
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x1c
	.byte	0x5
	.byte	0
	.byte	0
	.byte	0xc
	.byte	0x16
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xd
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x49
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xe
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0xf
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x10
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x11
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x12
	.byte	0x2e
	.byte	0
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0x13
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x49
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x96,0x42
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x14
	.byte	0x2e
	.byte	0
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x49
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0x15
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x16
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x17
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x18
	.byte	0x2e
	.byte	0
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0x19
	.byte	0x2e
	.byte	0
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x96,0x42
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_macro,"",@progbits
.Ldebug_macro0:
	.2byte	0x4
	.byte	0x2
	.4byte	.Ldebug_line0
	.byte	0x3
	.byte	0
	.byte	0x1
	.byte	0x5
	.byte	0x1
	.4byte	.LASF0
	.byte	0x5
	.byte	0x2
	.4byte	.LASF1
	.byte	0x5
	.byte	0x3
	.4byte	.LASF2
	.byte	0x5
	.byte	0x4
	.4byte	.LASF3
	.byte	0x5
	.byte	0x5
	.4byte	.LASF4
	.byte	0x5
	.byte	0x6
	.4byte	.LASF5
	.byte	0x5
	.byte	0x7
	.4byte	.LASF6
	.byte	0x5
	.byte	0x8
	.4byte	.LASF7
	.byte	0x5
	.byte	0x9
	.4byte	.LASF8
	.byte	0x5
	.byte	0xa
	.4byte	.LASF9
	.byte	0x5
	.byte	0xb
	.4byte	.LASF10
	.byte	0x5
	.byte	0xc
	.4byte	.LASF11
	.byte	0x5
	.byte	0xd
	.4byte	.LASF12
	.byte	0x5
	.byte	0xe
	.4byte	.LASF13
	.byte	0x5
	.byte	0xf
	.4byte	.LASF14
	.byte	0x5
	.byte	0x10
	.4byte	.LASF15
	.byte	0x5
	.byte	0x11
	.4byte	.LASF16
	.byte	0x5
	.byte	0x12
	.4byte	.LASF17
	.byte	0x5
	.byte	0x13
	.4byte	.LASF18
	.byte	0x5
	.byte	0x14
	.4byte	.LASF19
	.byte	0x5
	.byte	0x15
	.4byte	.LASF20
	.byte	0x5
	.byte	0x16
	.4byte	.LASF21
	.byte	0x5
	.byte	0x17
	.4byte	.LASF22
	.byte	0x5
	.byte	0x18
	.4byte	.LASF23
	.byte	0x5
	.byte	0x19
	.4byte	.LASF24
	.byte	0x5
	.byte	0x1a
	.4byte	.LASF25
	.byte	0x5
	.byte	0x1b
	.4byte	.LASF26
	.byte	0x5
	.byte	0x1c
	.4byte	.LASF27
	.byte	0x5
	.byte	0x1d
	.4byte	.LASF28
	.byte	0x5
	.byte	0x1e
	.4byte	.LASF29
	.byte	0x5
	.byte	0x1f
	.4byte	.LASF30
	.byte	0x5
	.byte	0x20
	.4byte	.LASF31
	.byte	0x5
	.byte	0x21
	.4byte	.LASF32
	.byte	0x5
	.byte	0x22
	.4byte	.LASF33
	.byte	0x5
	.byte	0x23
	.4byte	.LASF34
	.byte	0x5
	.byte	0x24
	.4byte	.LASF35
	.byte	0x5
	.byte	0x25
	.4byte	.LASF36
	.byte	0x5
	.byte	0x26
	.4byte	.LASF37
	.byte	0x5
	.byte	0x27
	.4byte	.LASF38
	.byte	0x5
	.byte	0x28
	.4byte	.LASF39
	.byte	0x5
	.byte	0x29
	.4byte	.LASF40
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF41
	.byte	0x5
	.byte	0x2b
	.4byte	.LASF42
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF43
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF44
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF45
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF46
	.byte	0x5
	.byte	0x30
	.4byte	.LASF47
	.byte	0x5
	.byte	0x31
	.4byte	.LASF48
	.byte	0x5
	.byte	0x32
	.4byte	.LASF49
	.byte	0x5
	.byte	0x33
	.4byte	.LASF50
	.byte	0x5
	.byte	0x34
	.4byte	.LASF51
	.byte	0x5
	.byte	0x35
	.4byte	.LASF52
	.byte	0x5
	.byte	0x36
	.4byte	.LASF53
	.byte	0x5
	.byte	0x37
	.4byte	.LASF54
	.byte	0x5
	.byte	0x38
	.4byte	.LASF55
	.byte	0x5
	.byte	0x39
	.4byte	.LASF56
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF57
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF58
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF59
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF60
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF61
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF62
	.byte	0x5
	.byte	0x40
	.4byte	.LASF63
	.byte	0x5
	.byte	0x41
	.4byte	.LASF64
	.byte	0x5
	.byte	0x42
	.4byte	.LASF65
	.byte	0x5
	.byte	0x43
	.4byte	.LASF66
	.byte	0x5
	.byte	0x44
	.4byte	.LASF67
	.byte	0x5
	.byte	0x45
	.4byte	.LASF68
	.byte	0x5
	.byte	0x46
	.4byte	.LASF69
	.byte	0x5
	.byte	0x47
	.4byte	.LASF70
	.byte	0x5
	.byte	0x48
	.4byte	.LASF71
	.byte	0x5
	.byte	0x49
	.4byte	.LASF72
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF73
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF74
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF75
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF76
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF77
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF78
	.byte	0x5
	.byte	0x50
	.4byte	.LASF79
	.byte	0x5
	.byte	0x51
	.4byte	.LASF80
	.byte	0x5
	.byte	0x52
	.4byte	.LASF81
	.byte	0x5
	.byte	0x53
	.4byte	.LASF82
	.byte	0x5
	.byte	0x54
	.4byte	.LASF83
	.byte	0x5
	.byte	0x55
	.4byte	.LASF84
	.byte	0x5
	.byte	0x56
	.4byte	.LASF85
	.byte	0x5
	.byte	0x57
	.4byte	.LASF86
	.byte	0x5
	.byte	0x58
	.4byte	.LASF87
	.byte	0x5
	.byte	0x59
	.4byte	.LASF88
	.byte	0x5
	.byte	0x5a
	.4byte	.LASF89
	.byte	0x5
	.byte	0x5b
	.4byte	.LASF90
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF91
	.byte	0x5
	.byte	0x5d
	.4byte	.LASF92
	.byte	0x5
	.byte	0x5e
	.4byte	.LASF93
	.byte	0x5
	.byte	0x5f
	.4byte	.LASF94
	.byte	0x5
	.byte	0x60
	.4byte	.LASF95
	.byte	0x5
	.byte	0x61
	.4byte	.LASF96
	.byte	0x5
	.byte	0x62
	.4byte	.LASF97
	.byte	0x5
	.byte	0x63
	.4byte	.LASF98
	.byte	0x5
	.byte	0x64
	.4byte	.LASF99
	.byte	0x5
	.byte	0x65
	.4byte	.LASF100
	.byte	0x5
	.byte	0x66
	.4byte	.LASF101
	.byte	0x5
	.byte	0x67
	.4byte	.LASF102
	.byte	0x5
	.byte	0x68
	.4byte	.LASF103
	.byte	0x5
	.byte	0x69
	.4byte	.LASF104
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF105
	.byte	0x5
	.byte	0x6b
	.4byte	.LASF106
	.byte	0x5
	.byte	0x6c
	.4byte	.LASF107
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF108
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF109
	.byte	0x5
	.byte	0x6f
	.4byte	.LASF110
	.byte	0x5
	.byte	0x70
	.4byte	.LASF111
	.byte	0x5
	.byte	0x71
	.4byte	.LASF112
	.byte	0x5
	.byte	0x72
	.4byte	.LASF113
	.byte	0x5
	.byte	0x73
	.4byte	.LASF114
	.byte	0x5
	.byte	0x74
	.4byte	.LASF115
	.byte	0x5
	.byte	0x75
	.4byte	.LASF116
	.byte	0x5
	.byte	0x76
	.4byte	.LASF117
	.byte	0x5
	.byte	0x77
	.4byte	.LASF118
	.byte	0x5
	.byte	0x78
	.4byte	.LASF119
	.byte	0x5
	.byte	0x79
	.4byte	.LASF120
	.byte	0x5
	.byte	0x7a
	.4byte	.LASF121
	.byte	0x5
	.byte	0x7b
	.4byte	.LASF122
	.byte	0x5
	.byte	0x7c
	.4byte	.LASF123
	.byte	0x5
	.byte	0x7d
	.4byte	.LASF124
	.byte	0x5
	.byte	0x7e
	.4byte	.LASF125
	.byte	0x5
	.byte	0x7f
	.4byte	.LASF126
	.byte	0x5
	.byte	0x80,0x1
	.4byte	.LASF127
	.byte	0x5
	.byte	0x81,0x1
	.4byte	.LASF128
	.byte	0x5
	.byte	0x82,0x1
	.4byte	.LASF129
	.byte	0x5
	.byte	0x83,0x1
	.4byte	.LASF130
	.byte	0x5
	.byte	0x84,0x1
	.4byte	.LASF131
	.byte	0x5
	.byte	0x85,0x1
	.4byte	.LASF132
	.byte	0x5
	.byte	0x86,0x1
	.4byte	.LASF133
	.byte	0x5
	.byte	0x87,0x1
	.4byte	.LASF134
	.byte	0x5
	.byte	0x88,0x1
	.4byte	.LASF135
	.byte	0x5
	.byte	0x89,0x1
	.4byte	.LASF136
	.byte	0x5
	.byte	0x8a,0x1
	.4byte	.LASF137
	.byte	0x5
	.byte	0x8b,0x1
	.4byte	.LASF138
	.byte	0x5
	.byte	0x8c,0x1
	.4byte	.LASF139
	.byte	0x5
	.byte	0x8d,0x1
	.4byte	.LASF140
	.byte	0x5
	.byte	0x8e,0x1
	.4byte	.LASF141
	.byte	0x5
	.byte	0x8f,0x1
	.4byte	.LASF142
	.byte	0x5
	.byte	0x90,0x1
	.4byte	.LASF143
	.byte	0x5
	.byte	0x91,0x1
	.4byte	.LASF144
	.byte	0x5
	.byte	0x92,0x1
	.4byte	.LASF145
	.byte	0x5
	.byte	0x93,0x1
	.4byte	.LASF146
	.byte	0x5
	.byte	0x94,0x1
	.4byte	.LASF147
	.byte	0x5
	.byte	0x95,0x1
	.4byte	.LASF148
	.byte	0x5
	.byte	0x96,0x1
	.4byte	.LASF149
	.byte	0x5
	.byte	0x97,0x1
	.4byte	.LASF150
	.byte	0x5
	.byte	0x98,0x1
	.4byte	.LASF151
	.byte	0x5
	.byte	0x99,0x1
	.4byte	.LASF152
	.byte	0x5
	.byte	0x9a,0x1
	.4byte	.LASF153
	.byte	0x5
	.byte	0x9b,0x1
	.4byte	.LASF154
	.byte	0x5
	.byte	0x9c,0x1
	.4byte	.LASF155
	.byte	0x5
	.byte	0x9d,0x1
	.4byte	.LASF156
	.byte	0x5
	.byte	0x9e,0x1
	.4byte	.LASF157
	.byte	0x5
	.byte	0x9f,0x1
	.4byte	.LASF158
	.byte	0x5
	.byte	0xa0,0x1
	.4byte	.LASF159
	.byte	0x5
	.byte	0xa1,0x1
	.4byte	.LASF160
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF161
	.byte	0x5
	.byte	0xa3,0x1
	.4byte	.LASF162
	.byte	0x5
	.byte	0xa4,0x1
	.4byte	.LASF163
	.byte	0x5
	.byte	0xa5,0x1
	.4byte	.LASF164
	.byte	0x5
	.byte	0xa6,0x1
	.4byte	.LASF165
	.byte	0x5
	.byte	0xa7,0x1
	.4byte	.LASF166
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF167
	.byte	0x5
	.byte	0xa9,0x1
	.4byte	.LASF168
	.byte	0x5
	.byte	0xaa,0x1
	.4byte	.LASF169
	.byte	0x5
	.byte	0xab,0x1
	.4byte	.LASF170
	.byte	0x5
	.byte	0xac,0x1
	.4byte	.LASF171
	.byte	0x5
	.byte	0xad,0x1
	.4byte	.LASF172
	.byte	0x5
	.byte	0xae,0x1
	.4byte	.LASF173
	.byte	0x5
	.byte	0xaf,0x1
	.4byte	.LASF174
	.byte	0x5
	.byte	0xb0,0x1
	.4byte	.LASF175
	.byte	0x5
	.byte	0xb1,0x1
	.4byte	.LASF176
	.byte	0x5
	.byte	0xb2,0x1
	.4byte	.LASF177
	.byte	0x5
	.byte	0xb3,0x1
	.4byte	.LASF178
	.byte	0x5
	.byte	0xb4,0x1
	.4byte	.LASF179
	.byte	0x5
	.byte	0xb5,0x1
	.4byte	.LASF180
	.byte	0x5
	.byte	0xb6,0x1
	.4byte	.LASF181
	.byte	0x5
	.byte	0xb7,0x1
	.4byte	.LASF182
	.byte	0x5
	.byte	0xb8,0x1
	.4byte	.LASF183
	.byte	0x5
	.byte	0xb9,0x1
	.4byte	.LASF184
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF185
	.byte	0x5
	.byte	0xbb,0x1
	.4byte	.LASF186
	.byte	0x5
	.byte	0xbc,0x1
	.4byte	.LASF187
	.byte	0x5
	.byte	0xbd,0x1
	.4byte	.LASF188
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF189
	.byte	0x5
	.byte	0xbf,0x1
	.4byte	.LASF190
	.byte	0x5
	.byte	0xc0,0x1
	.4byte	.LASF191
	.byte	0x5
	.byte	0xc1,0x1
	.4byte	.LASF192
	.byte	0x5
	.byte	0xc2,0x1
	.4byte	.LASF193
	.byte	0x5
	.byte	0xc3,0x1
	.4byte	.LASF194
	.byte	0x5
	.byte	0xc4,0x1
	.4byte	.LASF195
	.byte	0x5
	.byte	0xc5,0x1
	.4byte	.LASF196
	.byte	0x5
	.byte	0xc6,0x1
	.4byte	.LASF197
	.byte	0x5
	.byte	0xc7,0x1
	.4byte	.LASF198
	.byte	0x5
	.byte	0xc8,0x1
	.4byte	.LASF199
	.byte	0x5
	.byte	0xc9,0x1
	.4byte	.LASF200
	.byte	0x5
	.byte	0xca,0x1
	.4byte	.LASF201
	.byte	0x5
	.byte	0xcb,0x1
	.4byte	.LASF202
	.byte	0x5
	.byte	0xcc,0x1
	.4byte	.LASF203
	.byte	0x5
	.byte	0xcd,0x1
	.4byte	.LASF204
	.byte	0x5
	.byte	0xce,0x1
	.4byte	.LASF205
	.byte	0x5
	.byte	0xcf,0x1
	.4byte	.LASF206
	.byte	0x5
	.byte	0xd0,0x1
	.4byte	.LASF207
	.byte	0x5
	.byte	0xd1,0x1
	.4byte	.LASF208
	.byte	0x5
	.byte	0xd2,0x1
	.4byte	.LASF209
	.byte	0x5
	.byte	0xd3,0x1
	.4byte	.LASF210
	.byte	0x5
	.byte	0xd4,0x1
	.4byte	.LASF211
	.byte	0x5
	.byte	0xd5,0x1
	.4byte	.LASF212
	.byte	0x5
	.byte	0xd6,0x1
	.4byte	.LASF213
	.byte	0x5
	.byte	0xd7,0x1
	.4byte	.LASF214
	.byte	0x5
	.byte	0xd8,0x1
	.4byte	.LASF215
	.byte	0x5
	.byte	0xd9,0x1
	.4byte	.LASF216
	.byte	0x5
	.byte	0xda,0x1
	.4byte	.LASF217
	.byte	0x5
	.byte	0xdb,0x1
	.4byte	.LASF218
	.byte	0x5
	.byte	0xdc,0x1
	.4byte	.LASF219
	.byte	0x5
	.byte	0xdd,0x1
	.4byte	.LASF220
	.byte	0x5
	.byte	0xde,0x1
	.4byte	.LASF221
	.byte	0x5
	.byte	0xdf,0x1
	.4byte	.LASF222
	.byte	0x5
	.byte	0xe0,0x1
	.4byte	.LASF223
	.byte	0x5
	.byte	0xe1,0x1
	.4byte	.LASF224
	.byte	0x5
	.byte	0xe2,0x1
	.4byte	.LASF225
	.byte	0x5
	.byte	0xe3,0x1
	.4byte	.LASF226
	.byte	0x5
	.byte	0xe4,0x1
	.4byte	.LASF227
	.byte	0x5
	.byte	0xe5,0x1
	.4byte	.LASF228
	.byte	0x5
	.byte	0xe6,0x1
	.4byte	.LASF229
	.byte	0x5
	.byte	0xe7,0x1
	.4byte	.LASF230
	.byte	0x5
	.byte	0xe8,0x1
	.4byte	.LASF231
	.byte	0x5
	.byte	0xe9,0x1
	.4byte	.LASF232
	.byte	0x5
	.byte	0xea,0x1
	.4byte	.LASF233
	.byte	0x5
	.byte	0xeb,0x1
	.4byte	.LASF234
	.byte	0x5
	.byte	0xec,0x1
	.4byte	.LASF235
	.byte	0x5
	.byte	0xed,0x1
	.4byte	.LASF236
	.byte	0x5
	.byte	0xee,0x1
	.4byte	.LASF237
	.byte	0x5
	.byte	0xef,0x1
	.4byte	.LASF238
	.byte	0x5
	.byte	0xf0,0x1
	.4byte	.LASF239
	.byte	0x5
	.byte	0xf1,0x1
	.4byte	.LASF240
	.byte	0x5
	.byte	0xf2,0x1
	.4byte	.LASF241
	.byte	0x5
	.byte	0xf3,0x1
	.4byte	.LASF242
	.byte	0x5
	.byte	0xf4,0x1
	.4byte	.LASF243
	.byte	0x5
	.byte	0xf5,0x1
	.4byte	.LASF244
	.byte	0x5
	.byte	0xf6,0x1
	.4byte	.LASF245
	.byte	0x5
	.byte	0xf7,0x1
	.4byte	.LASF246
	.byte	0x5
	.byte	0xf8,0x1
	.4byte	.LASF247
	.byte	0x5
	.byte	0xf9,0x1
	.4byte	.LASF248
	.byte	0x5
	.byte	0xfa,0x1
	.4byte	.LASF249
	.byte	0x5
	.byte	0xfb,0x1
	.4byte	.LASF250
	.byte	0x5
	.byte	0xfc,0x1
	.4byte	.LASF251
	.byte	0x5
	.byte	0xfd,0x1
	.4byte	.LASF252
	.byte	0x5
	.byte	0xfe,0x1
	.4byte	.LASF253
	.byte	0x5
	.byte	0xff,0x1
	.4byte	.LASF254
	.byte	0x5
	.byte	0x80,0x2
	.4byte	.LASF255
	.byte	0x5
	.byte	0x81,0x2
	.4byte	.LASF256
	.byte	0x5
	.byte	0x82,0x2
	.4byte	.LASF257
	.byte	0x5
	.byte	0x83,0x2
	.4byte	.LASF258
	.byte	0x5
	.byte	0x84,0x2
	.4byte	.LASF259
	.byte	0x5
	.byte	0x85,0x2
	.4byte	.LASF260
	.byte	0x5
	.byte	0x86,0x2
	.4byte	.LASF261
	.byte	0x5
	.byte	0x87,0x2
	.4byte	.LASF262
	.byte	0x5
	.byte	0x88,0x2
	.4byte	.LASF263
	.byte	0x5
	.byte	0x89,0x2
	.4byte	.LASF264
	.byte	0x5
	.byte	0x8a,0x2
	.4byte	.LASF265
	.byte	0x5
	.byte	0x8b,0x2
	.4byte	.LASF266
	.byte	0x5
	.byte	0x8c,0x2
	.4byte	.LASF267
	.byte	0x5
	.byte	0x8d,0x2
	.4byte	.LASF268
	.byte	0x5
	.byte	0x8e,0x2
	.4byte	.LASF269
	.byte	0x5
	.byte	0x8f,0x2
	.4byte	.LASF270
	.byte	0x5
	.byte	0x90,0x2
	.4byte	.LASF271
	.byte	0x5
	.byte	0x91,0x2
	.4byte	.LASF272
	.byte	0x5
	.byte	0x92,0x2
	.4byte	.LASF273
	.byte	0x5
	.byte	0x93,0x2
	.4byte	.LASF274
	.byte	0x5
	.byte	0x94,0x2
	.4byte	.LASF275
	.byte	0x5
	.byte	0x95,0x2
	.4byte	.LASF276
	.byte	0x5
	.byte	0x96,0x2
	.4byte	.LASF277
	.byte	0x5
	.byte	0x97,0x2
	.4byte	.LASF278
	.byte	0x5
	.byte	0x98,0x2
	.4byte	.LASF279
	.byte	0x5
	.byte	0x99,0x2
	.4byte	.LASF280
	.byte	0x5
	.byte	0x9a,0x2
	.4byte	.LASF281
	.byte	0x5
	.byte	0x9b,0x2
	.4byte	.LASF282
	.byte	0x5
	.byte	0x9c,0x2
	.4byte	.LASF283
	.byte	0x5
	.byte	0x9d,0x2
	.4byte	.LASF284
	.byte	0x5
	.byte	0x9e,0x2
	.4byte	.LASF285
	.byte	0x5
	.byte	0x9f,0x2
	.4byte	.LASF286
	.byte	0x5
	.byte	0xa0,0x2
	.4byte	.LASF287
	.byte	0x5
	.byte	0xa1,0x2
	.4byte	.LASF288
	.byte	0x5
	.byte	0xa2,0x2
	.4byte	.LASF289
	.byte	0x5
	.byte	0xa3,0x2
	.4byte	.LASF290
	.byte	0x5
	.byte	0xa4,0x2
	.4byte	.LASF291
	.byte	0x5
	.byte	0xa5,0x2
	.4byte	.LASF292
	.byte	0x5
	.byte	0xa6,0x2
	.4byte	.LASF293
	.byte	0x5
	.byte	0xa7,0x2
	.4byte	.LASF294
	.byte	0x5
	.byte	0xa8,0x2
	.4byte	.LASF295
	.byte	0x5
	.byte	0xa9,0x2
	.4byte	.LASF296
	.byte	0x5
	.byte	0xaa,0x2
	.4byte	.LASF297
	.byte	0x5
	.byte	0xab,0x2
	.4byte	.LASF298
	.byte	0x5
	.byte	0xac,0x2
	.4byte	.LASF299
	.byte	0x5
	.byte	0xad,0x2
	.4byte	.LASF300
	.byte	0x5
	.byte	0xae,0x2
	.4byte	.LASF301
	.byte	0x5
	.byte	0xaf,0x2
	.4byte	.LASF302
	.byte	0x5
	.byte	0xb0,0x2
	.4byte	.LASF303
	.byte	0x5
	.byte	0xb1,0x2
	.4byte	.LASF304
	.byte	0x5
	.byte	0xb2,0x2
	.4byte	.LASF305
	.byte	0x5
	.byte	0xb3,0x2
	.4byte	.LASF306
	.byte	0x5
	.byte	0xb4,0x2
	.4byte	.LASF307
	.byte	0x5
	.byte	0xb5,0x2
	.4byte	.LASF308
	.byte	0x5
	.byte	0xb6,0x2
	.4byte	.LASF309
	.byte	0x5
	.byte	0xb7,0x2
	.4byte	.LASF310
	.byte	0x5
	.byte	0xb8,0x2
	.4byte	.LASF311
	.byte	0x5
	.byte	0xb9,0x2
	.4byte	.LASF312
	.byte	0x5
	.byte	0xba,0x2
	.4byte	.LASF313
	.byte	0x5
	.byte	0xbb,0x2
	.4byte	.LASF314
	.byte	0x5
	.byte	0xbc,0x2
	.4byte	.LASF315
	.byte	0x5
	.byte	0xbd,0x2
	.4byte	.LASF316
	.byte	0x5
	.byte	0xbe,0x2
	.4byte	.LASF317
	.byte	0x5
	.byte	0xbf,0x2
	.4byte	.LASF318
	.byte	0x5
	.byte	0xc0,0x2
	.4byte	.LASF319
	.byte	0x5
	.byte	0x1
	.4byte	.LASF320
	.byte	0x5
	.byte	0x2
	.4byte	.LASF321
	.byte	0x5
	.byte	0x3
	.4byte	.LASF322
	.byte	0x5
	.byte	0x4
	.4byte	.LASF323
	.byte	0x5
	.byte	0x5
	.4byte	.LASF324
	.byte	0x5
	.byte	0x6
	.4byte	.LASF325
	.byte	0x5
	.byte	0x7
	.4byte	.LASF326
	.byte	0x5
	.byte	0x8
	.4byte	.LASF327
	.byte	0x5
	.byte	0x9
	.4byte	.LASF328
	.byte	0x3
	.byte	0x24
	.byte	0x5
	.byte	0x5
	.byte	0x25
	.4byte	.LASF329
	.byte	0x3
	.byte	0x27
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro2
	.file 6 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral/system_gd32vf103.h"
	.byte	0x3
	.byte	0xaf,0x1
	.byte	0x6
	.byte	0x5
	.byte	0x28
	.4byte	.LASF341
	.file 7 "d:\\gcc\\xpack-riscv-none-embed-gcc-10.2.0-1.2\\riscv-none-embed\\include\\stdint.h"
	.byte	0x3
	.byte	0x2e
	.byte	0x7
	.byte	0x5
	.byte	0xa
	.4byte	.LASF342
	.byte	0x3
	.byte	0xc
	.byte	0x2
	.byte	0x5
	.byte	0x6
	.4byte	.LASF343
	.file 8 "d:\\gcc\\xpack-riscv-none-embed-gcc-10.2.0-1.2\\riscv-none-embed\\include\\sys\\features.h"
	.byte	0x3
	.byte	0x8
	.byte	0x8
	.byte	0x5
	.byte	0x16
	.4byte	.LASF344
	.file 9 "d:\\gcc\\xpack-riscv-none-embed-gcc-10.2.0-1.2\\riscv-none-embed\\include\\_newlib_version.h"
	.byte	0x3
	.byte	0x1c
	.byte	0x9
	.byte	0x7
	.4byte	.Ldebug_macro3
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro4
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro5
	.byte	0x4
	.file 10 "d:\\gcc\\xpack-riscv-none-embed-gcc-10.2.0-1.2\\riscv-none-embed\\include\\sys\\_intsup.h"
	.byte	0x3
	.byte	0xd
	.byte	0xa
	.byte	0x7
	.4byte	.Ldebug_macro6
	.byte	0x4
	.byte	0x3
	.byte	0xe
	.byte	0x3
	.byte	0x7
	.4byte	.Ldebug_macro7
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro8
	.byte	0x4
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro9
	.file 11 "board/gd32vf103_libopt.h"
	.byte	0x3
	.byte	0xec,0x1
	.byte	0xb
	.byte	0x5
	.byte	0x25
	.4byte	.LASF527
	.file 12 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_adc.h"
	.byte	0x3
	.byte	0x27
	.byte	0xc
	.byte	0x5
	.byte	0x25
	.4byte	.LASF528
	.byte	0x3
	.byte	0x27
	.byte	0x4
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro10
	.byte	0x4
	.file 13 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_bkp.h"
	.byte	0x3
	.byte	0x28
	.byte	0xd
	.byte	0x7
	.4byte	.Ldebug_macro11
	.byte	0x4
	.file 14 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_can.h"
	.byte	0x3
	.byte	0x29
	.byte	0xe
	.byte	0x7
	.4byte	.Ldebug_macro12
	.byte	0x4
	.file 15 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_crc.h"
	.byte	0x3
	.byte	0x2a
	.byte	0xf
	.byte	0x7
	.4byte	.Ldebug_macro13
	.byte	0x4
	.file 16 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_dac.h"
	.byte	0x3
	.byte	0x2b
	.byte	0x10
	.byte	0x7
	.4byte	.Ldebug_macro14
	.byte	0x4
	.file 17 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_dma.h"
	.byte	0x3
	.byte	0x2c
	.byte	0x11
	.byte	0x7
	.4byte	.Ldebug_macro15
	.byte	0x4
	.file 18 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_eclic.h"
	.byte	0x3
	.byte	0x2d
	.byte	0x12
	.byte	0x7
	.4byte	.Ldebug_macro16
	.byte	0x4
	.file 19 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_exmc.h"
	.byte	0x3
	.byte	0x2e
	.byte	0x13
	.byte	0x7
	.4byte	.Ldebug_macro17
	.byte	0x4
	.file 20 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_exti.h"
	.byte	0x3
	.byte	0x2f
	.byte	0x14
	.byte	0x7
	.4byte	.Ldebug_macro18
	.byte	0x4
	.file 21 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_fmc.h"
	.byte	0x3
	.byte	0x30
	.byte	0x15
	.byte	0x7
	.4byte	.Ldebug_macro19
	.byte	0x4
	.file 22 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_gpio.h"
	.byte	0x3
	.byte	0x31
	.byte	0x16
	.byte	0x7
	.4byte	.Ldebug_macro20
	.byte	0x4
	.file 23 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_i2c.h"
	.byte	0x3
	.byte	0x32
	.byte	0x17
	.byte	0x7
	.4byte	.Ldebug_macro21
	.byte	0x4
	.file 24 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_fwdgt.h"
	.byte	0x3
	.byte	0x33
	.byte	0x18
	.byte	0x7
	.4byte	.Ldebug_macro22
	.byte	0x4
	.file 25 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_dbg.h"
	.byte	0x3
	.byte	0x34
	.byte	0x19
	.byte	0x7
	.4byte	.Ldebug_macro23
	.byte	0x4
	.file 26 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_pmu.h"
	.byte	0x3
	.byte	0x35
	.byte	0x1a
	.byte	0x7
	.4byte	.Ldebug_macro24
	.byte	0x4
	.byte	0x3
	.byte	0x36
	.byte	0x5
	.byte	0x4
	.file 27 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_rtc.h"
	.byte	0x3
	.byte	0x37
	.byte	0x1b
	.byte	0x7
	.4byte	.Ldebug_macro25
	.byte	0x4
	.file 28 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_spi.h"
	.byte	0x3
	.byte	0x38
	.byte	0x1c
	.byte	0x7
	.4byte	.Ldebug_macro26
	.byte	0x4
	.file 29 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_timer.h"
	.byte	0x3
	.byte	0x39
	.byte	0x1d
	.byte	0x7
	.4byte	.Ldebug_macro27
	.byte	0x4
	.file 30 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_usart.h"
	.byte	0x3
	.byte	0x3a
	.byte	0x1e
	.byte	0x7
	.4byte	.Ldebug_macro28
	.byte	0x4
	.file 31 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Include/gd32vf103_wwdgt.h"
	.byte	0x3
	.byte	0x3b
	.byte	0x1f
	.byte	0x7
	.4byte	.Ldebug_macro29
	.byte	0x4
	.file 32 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\RISCV\\drivers/n200_func.h"
	.byte	0x3
	.byte	0x3c
	.byte	0x20
	.byte	0x5
	.byte	0x4
	.4byte	.LASF2744
	.file 33 "d:\\gcc\\xpack-riscv-none-embed-gcc-10.2.0-1.2\\lib\\gcc\\riscv-none-embed\\10.2.0\\include\\stddef.h"
	.byte	0x3
	.byte	0x7
	.byte	0x21
	.byte	0x7
	.4byte	.Ldebug_macro30
	.byte	0x4
	.file 34 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\RISCV\\drivers/n200_timer.h"
	.byte	0x3
	.byte	0x8
	.byte	0x22
	.byte	0x7
	.4byte	.Ldebug_macro31
	.byte	0x4
	.file 35 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\RISCV\\drivers/n200_eclic.h"
	.byte	0x3
	.byte	0x9
	.byte	0x23
	.byte	0x5
	.byte	0x4
	.4byte	.LASF2808
	.file 36 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\RISCV\\drivers/riscv_const.h"
	.byte	0x3
	.byte	0x6
	.byte	0x24
	.byte	0x7
	.4byte	.Ldebug_macro32
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro33
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro34
	.byte	0x4
	.byte	0x4
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro35
	.byte	0x4
	.byte	0x5
	.byte	0x27
	.4byte	.LASF3169
	.byte	0x5
	.byte	0x28
	.4byte	.LASF3170
	.byte	0x5
	.byte	0x29
	.4byte	.LASF3171
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF3172
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF3173
	.byte	0x4
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103.h.37.6b141d903229e2235d36f2860fb69b6b,comdat
.Ldebug_macro2:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF330
	.byte	0x5
	.byte	0x35
	.4byte	.LASF331
	.byte	0x5
	.byte	0x37
	.4byte	.LASF332
	.byte	0x5
	.byte	0x38
	.4byte	.LASF333
	.byte	0x5
	.byte	0x40
	.4byte	.LASF334
	.byte	0x5
	.byte	0x41
	.4byte	.LASF335
	.byte	0x5
	.byte	0x49
	.4byte	.LASF336
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF337
	.byte	0x5
	.byte	0x53
	.4byte	.LASF338
	.byte	0x5
	.byte	0x58
	.4byte	.LASF339
	.byte	0x5
	.byte	0x5d
	.4byte	.LASF340
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4._newlib_version.h.4.bfdf54b0af045d4a71376ae00f63a22c,comdat
.Ldebug_macro3:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x4
	.4byte	.LASF345
	.byte	0x5
	.byte	0x6
	.4byte	.LASF346
	.byte	0x5
	.byte	0x7
	.4byte	.LASF347
	.byte	0x5
	.byte	0x8
	.4byte	.LASF348
	.byte	0x5
	.byte	0x9
	.4byte	.LASF349
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.features.h.33.4ac7543a40bbf4e11e60e29e36a3b28e,comdat
.Ldebug_macro4:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x21
	.4byte	.LASF350
	.byte	0x5
	.byte	0x28
	.4byte	.LASF351
	.byte	0x5
	.byte	0xf9,0x1
	.4byte	.LASF352
	.byte	0x5
	.byte	0xff,0x1
	.4byte	.LASF353
	.byte	0x5
	.byte	0x85,0x2
	.4byte	.LASF354
	.byte	0x5
	.byte	0x8a,0x2
	.4byte	.LASF355
	.byte	0x5
	.byte	0x95,0x2
	.4byte	.LASF356
	.byte	0x5
	.byte	0x9b,0x2
	.4byte	.LASF357
	.byte	0x5
	.byte	0xa9,0x2
	.4byte	.LASF358
	.byte	0x5
	.byte	0xb1,0x2
	.4byte	.LASF359
	.byte	0x5
	.byte	0xbf,0x2
	.4byte	.LASF360
	.byte	0x5
	.byte	0xca,0x2
	.4byte	.LASF361
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4._default_types.h.15.247e5cd201eca3442cbf5404108c4935,comdat
.Ldebug_macro5:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0xf
	.4byte	.LASF362
	.byte	0x5
	.byte	0x1a
	.4byte	.LASF363
	.byte	0x5
	.byte	0x21
	.4byte	.LASF364
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF365
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF366
	.byte	0x5
	.byte	0x53
	.4byte	.LASF367
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF368
	.byte	0x5
	.byte	0x8c,0x1
	.4byte	.LASF369
	.byte	0x5
	.byte	0xa6,0x1
	.4byte	.LASF370
	.byte	0x5
	.byte	0xbc,0x1
	.4byte	.LASF371
	.byte	0x5
	.byte	0xce,0x1
	.4byte	.LASF372
	.byte	0x6
	.byte	0xf4,0x1
	.4byte	.LASF373
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4._intsup.h.10.48bafbb683905c4daa4565a85aeeb264,comdat
.Ldebug_macro6:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0xa
	.4byte	.LASF374
	.byte	0x5
	.byte	0x10
	.4byte	.LASF375
	.byte	0x6
	.byte	0x2b
	.4byte	.LASF376
	.byte	0x6
	.byte	0x2c
	.4byte	.LASF377
	.byte	0x6
	.byte	0x2d
	.4byte	.LASF378
	.byte	0x6
	.byte	0x2e
	.4byte	.LASF379
	.byte	0x2
	.byte	0x2f
	.string	"int"
	.byte	0x6
	.byte	0x30
	.4byte	.LASF380
	.byte	0x6
	.byte	0x31
	.4byte	.LASF381
	.byte	0x6
	.byte	0x32
	.4byte	.LASF382
	.byte	0x5
	.byte	0x33
	.4byte	.LASF383
	.byte	0x5
	.byte	0x34
	.4byte	.LASF384
	.byte	0x5
	.byte	0x35
	.4byte	.LASF385
	.byte	0x5
	.byte	0x36
	.4byte	.LASF386
	.byte	0x5
	.byte	0x37
	.4byte	.LASF387
	.byte	0x5
	.byte	0x38
	.4byte	.LASF388
	.byte	0x5
	.byte	0x39
	.4byte	.LASF389
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF390
	.byte	0x5
	.byte	0x43
	.4byte	.LASF391
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF392
	.byte	0x5
	.byte	0x52
	.4byte	.LASF393
	.byte	0x5
	.byte	0x5d
	.4byte	.LASF394
	.byte	0x5
	.byte	0x68
	.4byte	.LASF395
	.byte	0x5
	.byte	0x71
	.4byte	.LASF396
	.byte	0x5
	.byte	0x78
	.4byte	.LASF397
	.byte	0x5
	.byte	0x81,0x1
	.4byte	.LASF398
	.byte	0x5
	.byte	0x88,0x1
	.4byte	.LASF399
	.byte	0x5
	.byte	0x93,0x1
	.4byte	.LASF400
	.byte	0x5
	.byte	0x97,0x1
	.4byte	.LASF401
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF402
	.byte	0x5
	.byte	0xad,0x1
	.4byte	.LASF403
	.byte	0x5
	.byte	0xb6,0x1
	.4byte	.LASF404
	.byte	0x6
	.byte	0xb8,0x1
	.4byte	.LASF376
	.byte	0x6
	.byte	0xb9,0x1
	.4byte	.LASF377
	.byte	0x6
	.byte	0xba,0x1
	.4byte	.LASF378
	.byte	0x6
	.byte	0xbb,0x1
	.4byte	.LASF379
	.byte	0x2
	.byte	0xbc,0x1
	.string	"int"
	.byte	0x6
	.byte	0xbd,0x1
	.4byte	.LASF382
	.byte	0x6
	.byte	0xc2,0x1
	.4byte	.LASF380
	.byte	0x6
	.byte	0xc3,0x1
	.4byte	.LASF381
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4._stdint.h.10.c24fa3af3bc1706662bb5593a907e841,comdat
.Ldebug_macro7:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0xa
	.4byte	.LASF405
	.byte	0x5
	.byte	0x15
	.4byte	.LASF406
	.byte	0x5
	.byte	0x19
	.4byte	.LASF407
	.byte	0x5
	.byte	0x1b
	.4byte	.LASF408
	.byte	0x5
	.byte	0x21
	.4byte	.LASF409
	.byte	0x5
	.byte	0x25
	.4byte	.LASF410
	.byte	0x5
	.byte	0x27
	.4byte	.LASF411
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF412
	.byte	0x5
	.byte	0x31
	.4byte	.LASF413
	.byte	0x5
	.byte	0x33
	.4byte	.LASF414
	.byte	0x5
	.byte	0x39
	.4byte	.LASF415
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF416
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF417
	.byte	0x5
	.byte	0x44
	.4byte	.LASF418
	.byte	0x5
	.byte	0x49
	.4byte	.LASF419
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF420
	.byte	0x5
	.byte	0x53
	.4byte	.LASF421
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdint.h.23.d53047a68f4a85177f80b422d52785ed,comdat
.Ldebug_macro8:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x17
	.4byte	.LASF422
	.byte	0x5
	.byte	0x1d
	.4byte	.LASF423
	.byte	0x5
	.byte	0x23
	.4byte	.LASF424
	.byte	0x5
	.byte	0x29
	.4byte	.LASF425
	.byte	0x5
	.byte	0x35
	.4byte	.LASF426
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF427
	.byte	0x5
	.byte	0x49
	.4byte	.LASF428
	.byte	0x5
	.byte	0x53
	.4byte	.LASF429
	.byte	0x5
	.byte	0x80,0x1
	.4byte	.LASF430
	.byte	0x5
	.byte	0x81,0x1
	.4byte	.LASF431
	.byte	0x5
	.byte	0x82,0x1
	.4byte	.LASF432
	.byte	0x5
	.byte	0x98,0x1
	.4byte	.LASF433
	.byte	0x5
	.byte	0x99,0x1
	.4byte	.LASF434
	.byte	0x5
	.byte	0x9a,0x1
	.4byte	.LASF435
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF436
	.byte	0x5
	.byte	0xa3,0x1
	.4byte	.LASF437
	.byte	0x5
	.byte	0xa4,0x1
	.4byte	.LASF438
	.byte	0x5
	.byte	0xae,0x1
	.4byte	.LASF439
	.byte	0x5
	.byte	0xaf,0x1
	.4byte	.LASF440
	.byte	0x5
	.byte	0xb0,0x1
	.4byte	.LASF441
	.byte	0x5
	.byte	0xb8,0x1
	.4byte	.LASF442
	.byte	0x5
	.byte	0xb9,0x1
	.4byte	.LASF443
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF444
	.byte	0x5
	.byte	0xc4,0x1
	.4byte	.LASF445
	.byte	0x5
	.byte	0xc5,0x1
	.4byte	.LASF446
	.byte	0x5
	.byte	0xc6,0x1
	.4byte	.LASF447
	.byte	0x5
	.byte	0xd4,0x1
	.4byte	.LASF448
	.byte	0x5
	.byte	0xd5,0x1
	.4byte	.LASF449
	.byte	0x5
	.byte	0xd6,0x1
	.4byte	.LASF450
	.byte	0x5
	.byte	0xe6,0x1
	.4byte	.LASF451
	.byte	0x5
	.byte	0xe7,0x1
	.4byte	.LASF452
	.byte	0x5
	.byte	0xe8,0x1
	.4byte	.LASF453
	.byte	0x5
	.byte	0xf6,0x1
	.4byte	.LASF454
	.byte	0x5
	.byte	0xf7,0x1
	.4byte	.LASF455
	.byte	0x5
	.byte	0xf8,0x1
	.4byte	.LASF456
	.byte	0x5
	.byte	0x86,0x2
	.4byte	.LASF457
	.byte	0x5
	.byte	0x87,0x2
	.4byte	.LASF458
	.byte	0x5
	.byte	0x88,0x2
	.4byte	.LASF459
	.byte	0x5
	.byte	0x96,0x2
	.4byte	.LASF460
	.byte	0x5
	.byte	0x97,0x2
	.4byte	.LASF461
	.byte	0x5
	.byte	0x98,0x2
	.4byte	.LASF462
	.byte	0x5
	.byte	0xa6,0x2
	.4byte	.LASF463
	.byte	0x5
	.byte	0xa7,0x2
	.4byte	.LASF464
	.byte	0x5
	.byte	0xa8,0x2
	.4byte	.LASF465
	.byte	0x5
	.byte	0xb6,0x2
	.4byte	.LASF466
	.byte	0x5
	.byte	0xb7,0x2
	.4byte	.LASF467
	.byte	0x5
	.byte	0xb8,0x2
	.4byte	.LASF468
	.byte	0x5
	.byte	0xc6,0x2
	.4byte	.LASF469
	.byte	0x5
	.byte	0xc7,0x2
	.4byte	.LASF470
	.byte	0x5
	.byte	0xcf,0x2
	.4byte	.LASF471
	.byte	0x5
	.byte	0xd7,0x2
	.4byte	.LASF472
	.byte	0x5
	.byte	0xdd,0x2
	.4byte	.LASF473
	.byte	0x5
	.byte	0xde,0x2
	.4byte	.LASF474
	.byte	0x5
	.byte	0xe2,0x2
	.4byte	.LASF475
	.byte	0x5
	.byte	0xe6,0x2
	.4byte	.LASF476
	.byte	0x5
	.byte	0xeb,0x2
	.4byte	.LASF477
	.byte	0x5
	.byte	0xf6,0x2
	.4byte	.LASF478
	.byte	0x5
	.byte	0x80,0x3
	.4byte	.LASF479
	.byte	0x5
	.byte	0x85,0x3
	.4byte	.LASF480
	.byte	0x5
	.byte	0x8c,0x3
	.4byte	.LASF481
	.byte	0x5
	.byte	0x8d,0x3
	.4byte	.LASF482
	.byte	0x5
	.byte	0x98,0x3
	.4byte	.LASF483
	.byte	0x5
	.byte	0x99,0x3
	.4byte	.LASF484
	.byte	0x5
	.byte	0xa4,0x3
	.4byte	.LASF485
	.byte	0x5
	.byte	0xa5,0x3
	.4byte	.LASF486
	.byte	0x5
	.byte	0xb1,0x3
	.4byte	.LASF487
	.byte	0x5
	.byte	0xb2,0x3
	.4byte	.LASF488
	.byte	0x5
	.byte	0xc1,0x3
	.4byte	.LASF489
	.byte	0x5
	.byte	0xc2,0x3
	.4byte	.LASF490
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103.h.185.cffba7180870c0512d04c724c6463ab0,comdat
.Ldebug_macro9:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0xb9,0x1
	.4byte	.LASF491
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF492
	.byte	0x5
	.byte	0xbb,0x1
	.4byte	.LASF493
	.byte	0x5
	.byte	0xbc,0x1
	.4byte	.LASF494
	.byte	0x5
	.byte	0xbd,0x1
	.4byte	.LASF495
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF496
	.byte	0x5
	.byte	0xc1,0x1
	.4byte	.LASF497
	.byte	0x5
	.byte	0xc2,0x1
	.4byte	.LASF498
	.byte	0x5
	.byte	0xc3,0x1
	.4byte	.LASF499
	.byte	0x5
	.byte	0xc4,0x1
	.4byte	.LASF500
	.byte	0x5
	.byte	0xc5,0x1
	.4byte	.LASF501
	.byte	0x5
	.byte	0xc8,0x1
	.4byte	.LASF502
	.byte	0x5
	.byte	0xc9,0x1
	.4byte	.LASF503
	.byte	0x5
	.byte	0xca,0x1
	.4byte	.LASF504
	.byte	0x5
	.byte	0xcb,0x1
	.4byte	.LASF505
	.byte	0x5
	.byte	0xce,0x1
	.4byte	.LASF506
	.byte	0x5
	.byte	0xcf,0x1
	.4byte	.LASF507
	.byte	0x5
	.byte	0xd0,0x1
	.4byte	.LASF508
	.byte	0x5
	.byte	0xd1,0x1
	.4byte	.LASF509
	.byte	0x5
	.byte	0xd2,0x1
	.4byte	.LASF510
	.byte	0x5
	.byte	0xd3,0x1
	.4byte	.LASF511
	.byte	0x5
	.byte	0xd4,0x1
	.4byte	.LASF512
	.byte	0x5
	.byte	0xd5,0x1
	.4byte	.LASF513
	.byte	0x5
	.byte	0xd6,0x1
	.4byte	.LASF514
	.byte	0x5
	.byte	0xd7,0x1
	.4byte	.LASF515
	.byte	0x5
	.byte	0xd8,0x1
	.4byte	.LASF516
	.byte	0x5
	.byte	0xdb,0x1
	.4byte	.LASF517
	.byte	0x5
	.byte	0xdc,0x1
	.4byte	.LASF518
	.byte	0x5
	.byte	0xdd,0x1
	.4byte	.LASF519
	.byte	0x5
	.byte	0xde,0x1
	.4byte	.LASF520
	.byte	0x5
	.byte	0xe1,0x1
	.4byte	.LASF521
	.byte	0x5
	.byte	0xe2,0x1
	.4byte	.LASF522
	.byte	0x5
	.byte	0xe3,0x1
	.4byte	.LASF523
	.byte	0x5
	.byte	0xe4,0x1
	.4byte	.LASF524
	.byte	0x5
	.byte	0xe5,0x1
	.4byte	.LASF525
	.byte	0x5
	.byte	0xe9,0x1
	.4byte	.LASF526
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_adc.h.42.14cb8f90e4b5922f8a25d63c78535a21,comdat
.Ldebug_macro10:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF529
	.byte	0x5
	.byte	0x2b
	.4byte	.LASF530
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF531
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF532
	.byte	0x5
	.byte	0x30
	.4byte	.LASF533
	.byte	0x5
	.byte	0x31
	.4byte	.LASF534
	.byte	0x5
	.byte	0x32
	.4byte	.LASF535
	.byte	0x5
	.byte	0x33
	.4byte	.LASF536
	.byte	0x5
	.byte	0x34
	.4byte	.LASF537
	.byte	0x5
	.byte	0x35
	.4byte	.LASF538
	.byte	0x5
	.byte	0x36
	.4byte	.LASF539
	.byte	0x5
	.byte	0x37
	.4byte	.LASF540
	.byte	0x5
	.byte	0x38
	.4byte	.LASF541
	.byte	0x5
	.byte	0x39
	.4byte	.LASF542
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF543
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF544
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF545
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF546
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF547
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF548
	.byte	0x5
	.byte	0x40
	.4byte	.LASF549
	.byte	0x5
	.byte	0x41
	.4byte	.LASF550
	.byte	0x5
	.byte	0x42
	.4byte	.LASF551
	.byte	0x5
	.byte	0x46
	.4byte	.LASF552
	.byte	0x5
	.byte	0x47
	.4byte	.LASF553
	.byte	0x5
	.byte	0x48
	.4byte	.LASF554
	.byte	0x5
	.byte	0x49
	.4byte	.LASF555
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF556
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF557
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF558
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF559
	.byte	0x5
	.byte	0x50
	.4byte	.LASF560
	.byte	0x5
	.byte	0x51
	.4byte	.LASF561
	.byte	0x5
	.byte	0x52
	.4byte	.LASF562
	.byte	0x5
	.byte	0x53
	.4byte	.LASF563
	.byte	0x5
	.byte	0x54
	.4byte	.LASF564
	.byte	0x5
	.byte	0x55
	.4byte	.LASF565
	.byte	0x5
	.byte	0x56
	.4byte	.LASF566
	.byte	0x5
	.byte	0x57
	.4byte	.LASF567
	.byte	0x5
	.byte	0x58
	.4byte	.LASF568
	.byte	0x5
	.byte	0x59
	.4byte	.LASF569
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF570
	.byte	0x5
	.byte	0x5d
	.4byte	.LASF571
	.byte	0x5
	.byte	0x5e
	.4byte	.LASF572
	.byte	0x5
	.byte	0x5f
	.4byte	.LASF573
	.byte	0x5
	.byte	0x60
	.4byte	.LASF574
	.byte	0x5
	.byte	0x61
	.4byte	.LASF575
	.byte	0x5
	.byte	0x62
	.4byte	.LASF576
	.byte	0x5
	.byte	0x63
	.4byte	.LASF577
	.byte	0x5
	.byte	0x64
	.4byte	.LASF578
	.byte	0x5
	.byte	0x65
	.4byte	.LASF579
	.byte	0x5
	.byte	0x66
	.4byte	.LASF580
	.byte	0x5
	.byte	0x67
	.4byte	.LASF581
	.byte	0x5
	.byte	0x68
	.4byte	.LASF582
	.byte	0x5
	.byte	0x6b
	.4byte	.LASF583
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF584
	.byte	0x5
	.byte	0x71
	.4byte	.LASF585
	.byte	0x5
	.byte	0x74
	.4byte	.LASF586
	.byte	0x5
	.byte	0x77
	.4byte	.LASF587
	.byte	0x5
	.byte	0x78
	.4byte	.LASF588
	.byte	0x5
	.byte	0x7b
	.4byte	.LASF589
	.byte	0x5
	.byte	0x7c
	.4byte	.LASF590
	.byte	0x5
	.byte	0x7f
	.4byte	.LASF591
	.byte	0x5
	.byte	0x82,0x1
	.4byte	.LASF592
	.byte	0x5
	.byte	0x83,0x1
	.4byte	.LASF593
	.byte	0x5
	.byte	0x86,0x1
	.4byte	.LASF594
	.byte	0x5
	.byte	0x87,0x1
	.4byte	.LASF595
	.byte	0x5
	.byte	0x88,0x1
	.4byte	.LASF596
	.byte	0x5
	.byte	0x89,0x1
	.4byte	.LASF597
	.byte	0x5
	.byte	0x8a,0x1
	.4byte	.LASF598
	.byte	0x5
	.byte	0x8e,0x1
	.4byte	.LASF599
	.byte	0x5
	.byte	0x8f,0x1
	.4byte	.LASF600
	.byte	0x5
	.byte	0x90,0x1
	.4byte	.LASF601
	.byte	0x5
	.byte	0x91,0x1
	.4byte	.LASF602
	.byte	0x5
	.byte	0x92,0x1
	.4byte	.LASF603
	.byte	0x5
	.byte	0x95,0x1
	.4byte	.LASF604
	.byte	0x5
	.byte	0x98,0x1
	.4byte	.LASF605
	.byte	0x5
	.byte	0x9b,0x1
	.4byte	.LASF606
	.byte	0x5
	.byte	0x9e,0x1
	.4byte	.LASF607
	.byte	0x5
	.byte	0x9f,0x1
	.4byte	.LASF608
	.byte	0x5
	.byte	0xa0,0x1
	.4byte	.LASF609
	.byte	0x5
	.byte	0xa1,0x1
	.4byte	.LASF610
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF611
	.byte	0x5
	.byte	0xa3,0x1
	.4byte	.LASF612
	.byte	0x5
	.byte	0xa4,0x1
	.4byte	.LASF613
	.byte	0x5
	.byte	0xa5,0x1
	.4byte	.LASF614
	.byte	0x5
	.byte	0xa6,0x1
	.4byte	.LASF615
	.byte	0x5
	.byte	0xa7,0x1
	.4byte	.LASF616
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF617
	.byte	0x5
	.byte	0xab,0x1
	.4byte	.LASF618
	.byte	0x5
	.byte	0xac,0x1
	.4byte	.LASF619
	.byte	0x5
	.byte	0xaf,0x1
	.4byte	.LASF620
	.byte	0x5
	.byte	0xb2,0x1
	.4byte	.LASF621
	.byte	0x5
	.byte	0xb4,0x1
	.4byte	.LASF622
	.byte	0x5
	.byte	0xb5,0x1
	.4byte	.LASF623
	.byte	0x5
	.byte	0xb6,0x1
	.4byte	.LASF624
	.byte	0x5
	.byte	0xb7,0x1
	.4byte	.LASF625
	.byte	0x5
	.byte	0xb8,0x1
	.4byte	.LASF626
	.byte	0x5
	.byte	0xb9,0x1
	.4byte	.LASF627
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF628
	.byte	0x5
	.byte	0xbb,0x1
	.4byte	.LASF629
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF630
	.byte	0x5
	.byte	0xc0,0x1
	.4byte	.LASF631
	.byte	0x5
	.byte	0xc1,0x1
	.4byte	.LASF632
	.byte	0x5
	.byte	0xc2,0x1
	.4byte	.LASF633
	.byte	0x5
	.byte	0xc3,0x1
	.4byte	.LASF634
	.byte	0x5
	.byte	0xc4,0x1
	.4byte	.LASF635
	.byte	0x5
	.byte	0xc5,0x1
	.4byte	.LASF636
	.byte	0x5
	.byte	0xc6,0x1
	.4byte	.LASF637
	.byte	0x5
	.byte	0xc7,0x1
	.4byte	.LASF638
	.byte	0x5
	.byte	0xca,0x1
	.4byte	.LASF639
	.byte	0x5
	.byte	0xcb,0x1
	.4byte	.LASF640
	.byte	0x5
	.byte	0xcc,0x1
	.4byte	.LASF641
	.byte	0x5
	.byte	0xcd,0x1
	.4byte	.LASF642
	.byte	0x5
	.byte	0xce,0x1
	.4byte	.LASF643
	.byte	0x5
	.byte	0xcf,0x1
	.4byte	.LASF644
	.byte	0x5
	.byte	0xd0,0x1
	.4byte	.LASF645
	.byte	0x5
	.byte	0xd1,0x1
	.4byte	.LASF646
	.byte	0x5
	.byte	0xd2,0x1
	.4byte	.LASF647
	.byte	0x5
	.byte	0xd5,0x1
	.4byte	.LASF648
	.byte	0x5
	.byte	0xd8,0x1
	.4byte	.LASF649
	.byte	0x5
	.byte	0xdb,0x1
	.4byte	.LASF650
	.byte	0x5
	.byte	0xde,0x1
	.4byte	.LASF651
	.byte	0x5
	.byte	0xe1,0x1
	.4byte	.LASF652
	.byte	0x5
	.byte	0xe4,0x1
	.4byte	.LASF653
	.byte	0x5
	.byte	0xe5,0x1
	.4byte	.LASF654
	.byte	0x5
	.byte	0xe6,0x1
	.4byte	.LASF655
	.byte	0x5
	.byte	0xe8,0x1
	.4byte	.LASF656
	.byte	0x5
	.byte	0xeb,0x1
	.4byte	.LASF657
	.byte	0x5
	.byte	0xec,0x1
	.4byte	.LASF658
	.byte	0x5
	.byte	0xed,0x1
	.4byte	.LASF659
	.byte	0x5
	.byte	0xee,0x1
	.4byte	.LASF660
	.byte	0x5
	.byte	0xf1,0x1
	.4byte	.LASF661
	.byte	0x5
	.byte	0xf2,0x1
	.4byte	.LASF662
	.byte	0x5
	.byte	0xf3,0x1
	.4byte	.LASF663
	.byte	0x5
	.byte	0xf4,0x1
	.4byte	.LASF664
	.byte	0x5
	.byte	0xf5,0x1
	.4byte	.LASF665
	.byte	0x5
	.byte	0xf6,0x1
	.4byte	.LASF666
	.byte	0x5
	.byte	0xf7,0x1
	.4byte	.LASF667
	.byte	0x5
	.byte	0xf8,0x1
	.4byte	.LASF668
	.byte	0x5
	.byte	0xf9,0x1
	.4byte	.LASF669
	.byte	0x5
	.byte	0xfa,0x1
	.4byte	.LASF670
	.byte	0x5
	.byte	0xfb,0x1
	.4byte	.LASF671
	.byte	0x5
	.byte	0xfc,0x1
	.4byte	.LASF672
	.byte	0x5
	.byte	0xfd,0x1
	.4byte	.LASF673
	.byte	0x5
	.byte	0xfe,0x1
	.4byte	.LASF674
	.byte	0x5
	.byte	0xff,0x1
	.4byte	.LASF675
	.byte	0x5
	.byte	0x80,0x2
	.4byte	.LASF676
	.byte	0x5
	.byte	0x81,0x2
	.4byte	.LASF677
	.byte	0x5
	.byte	0x82,0x2
	.4byte	.LASF678
	.byte	0x5
	.byte	0x85,0x2
	.4byte	.LASF679
	.byte	0x5
	.byte	0x86,0x2
	.4byte	.LASF680
	.byte	0x5
	.byte	0x87,0x2
	.4byte	.LASF681
	.byte	0x5
	.byte	0x8a,0x2
	.4byte	.LASF682
	.byte	0x5
	.byte	0x8b,0x2
	.4byte	.LASF683
	.byte	0x5
	.byte	0x8c,0x2
	.4byte	.LASF684
	.byte	0x5
	.byte	0x8f,0x2
	.4byte	.LASF685
	.byte	0x5
	.byte	0x90,0x2
	.4byte	.LASF686
	.byte	0x5
	.byte	0x91,0x2
	.4byte	.LASF687
	.byte	0x5
	.byte	0x92,0x2
	.4byte	.LASF688
	.byte	0x5
	.byte	0x93,0x2
	.4byte	.LASF689
	.byte	0x5
	.byte	0x96,0x2
	.4byte	.LASF690
	.byte	0x5
	.byte	0x97,0x2
	.4byte	.LASF691
	.byte	0x5
	.byte	0x9a,0x2
	.4byte	.LASF692
	.byte	0x5
	.byte	0x9b,0x2
	.4byte	.LASF693
	.byte	0x5
	.byte	0x9c,0x2
	.4byte	.LASF694
	.byte	0x5
	.byte	0x9d,0x2
	.4byte	.LASF695
	.byte	0x5
	.byte	0x9e,0x2
	.4byte	.LASF696
	.byte	0x5
	.byte	0x9f,0x2
	.4byte	.LASF697
	.byte	0x5
	.byte	0xa0,0x2
	.4byte	.LASF698
	.byte	0x5
	.byte	0xa1,0x2
	.4byte	.LASF699
	.byte	0x5
	.byte	0xa2,0x2
	.4byte	.LASF700
	.byte	0x5
	.byte	0xa3,0x2
	.4byte	.LASF701
	.byte	0x5
	.byte	0xa6,0x2
	.4byte	.LASF702
	.byte	0x5
	.byte	0xa7,0x2
	.4byte	.LASF703
	.byte	0x5
	.byte	0xa8,0x2
	.4byte	.LASF704
	.byte	0x5
	.byte	0xa9,0x2
	.4byte	.LASF705
	.byte	0x5
	.byte	0xaa,0x2
	.4byte	.LASF706
	.byte	0x5
	.byte	0xab,0x2
	.4byte	.LASF707
	.byte	0x5
	.byte	0xac,0x2
	.4byte	.LASF708
	.byte	0x5
	.byte	0xad,0x2
	.4byte	.LASF709
	.byte	0x5
	.byte	0xae,0x2
	.4byte	.LASF710
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_bkp.h.37.565cdaf530a41cd40ed21e5fda39a6ed,comdat
.Ldebug_macro11:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF711
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF712
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF713
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF714
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF715
	.byte	0x5
	.byte	0x30
	.4byte	.LASF716
	.byte	0x5
	.byte	0x31
	.4byte	.LASF717
	.byte	0x5
	.byte	0x32
	.4byte	.LASF718
	.byte	0x5
	.byte	0x33
	.4byte	.LASF719
	.byte	0x5
	.byte	0x34
	.4byte	.LASF720
	.byte	0x5
	.byte	0x35
	.4byte	.LASF721
	.byte	0x5
	.byte	0x36
	.4byte	.LASF722
	.byte	0x5
	.byte	0x37
	.4byte	.LASF723
	.byte	0x5
	.byte	0x38
	.4byte	.LASF724
	.byte	0x5
	.byte	0x39
	.4byte	.LASF725
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF726
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF727
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF728
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF729
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF730
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF731
	.byte	0x5
	.byte	0x40
	.4byte	.LASF732
	.byte	0x5
	.byte	0x41
	.4byte	.LASF733
	.byte	0x5
	.byte	0x42
	.4byte	.LASF734
	.byte	0x5
	.byte	0x43
	.4byte	.LASF735
	.byte	0x5
	.byte	0x44
	.4byte	.LASF736
	.byte	0x5
	.byte	0x45
	.4byte	.LASF737
	.byte	0x5
	.byte	0x46
	.4byte	.LASF738
	.byte	0x5
	.byte	0x47
	.4byte	.LASF739
	.byte	0x5
	.byte	0x48
	.4byte	.LASF740
	.byte	0x5
	.byte	0x49
	.4byte	.LASF741
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF742
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF743
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF744
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF745
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF746
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF747
	.byte	0x5
	.byte	0x50
	.4byte	.LASF748
	.byte	0x5
	.byte	0x51
	.4byte	.LASF749
	.byte	0x5
	.byte	0x52
	.4byte	.LASF750
	.byte	0x5
	.byte	0x53
	.4byte	.LASF751
	.byte	0x5
	.byte	0x54
	.4byte	.LASF752
	.byte	0x5
	.byte	0x55
	.4byte	.LASF753
	.byte	0x5
	.byte	0x56
	.4byte	.LASF754
	.byte	0x5
	.byte	0x57
	.4byte	.LASF755
	.byte	0x5
	.byte	0x58
	.4byte	.LASF756
	.byte	0x5
	.byte	0x59
	.4byte	.LASF757
	.byte	0x5
	.byte	0x5d
	.4byte	.LASF758
	.byte	0x5
	.byte	0x60
	.4byte	.LASF759
	.byte	0x5
	.byte	0x61
	.4byte	.LASF760
	.byte	0x5
	.byte	0x62
	.4byte	.LASF761
	.byte	0x5
	.byte	0x63
	.4byte	.LASF762
	.byte	0x5
	.byte	0x66
	.4byte	.LASF763
	.byte	0x5
	.byte	0x67
	.4byte	.LASF764
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF765
	.byte	0x5
	.byte	0x6b
	.4byte	.LASF766
	.byte	0x5
	.byte	0x6c
	.4byte	.LASF767
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF768
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF769
	.byte	0x5
	.byte	0xa1,0x1
	.4byte	.LASF770
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF771
	.byte	0x5
	.byte	0xa5,0x1
	.4byte	.LASF772
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF773
	.byte	0x5
	.byte	0xab,0x1
	.4byte	.LASF774
	.byte	0x5
	.byte	0xac,0x1
	.4byte	.LASF775
	.byte	0x5
	.byte	0xaf,0x1
	.4byte	.LASF776
	.byte	0x5
	.byte	0xb0,0x1
	.4byte	.LASF777
	.byte	0x5
	.byte	0xb3,0x1
	.4byte	.LASF778
	.byte	0x5
	.byte	0xb6,0x1
	.4byte	.LASF779
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_can.h.39.9380e444d8240972fa3c91ce629786a4,comdat
.Ldebug_macro12:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x27
	.4byte	.LASF780
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF781
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF782
	.byte	0x5
	.byte	0x30
	.4byte	.LASF783
	.byte	0x5
	.byte	0x31
	.4byte	.LASF784
	.byte	0x5
	.byte	0x32
	.4byte	.LASF785
	.byte	0x5
	.byte	0x33
	.4byte	.LASF786
	.byte	0x5
	.byte	0x34
	.4byte	.LASF787
	.byte	0x5
	.byte	0x35
	.4byte	.LASF788
	.byte	0x5
	.byte	0x36
	.4byte	.LASF789
	.byte	0x5
	.byte	0x37
	.4byte	.LASF790
	.byte	0x5
	.byte	0x38
	.4byte	.LASF791
	.byte	0x5
	.byte	0x39
	.4byte	.LASF792
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF793
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF794
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF795
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF796
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF797
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF798
	.byte	0x5
	.byte	0x40
	.4byte	.LASF799
	.byte	0x5
	.byte	0x41
	.4byte	.LASF800
	.byte	0x5
	.byte	0x42
	.4byte	.LASF801
	.byte	0x5
	.byte	0x43
	.4byte	.LASF802
	.byte	0x5
	.byte	0x44
	.4byte	.LASF803
	.byte	0x5
	.byte	0x45
	.4byte	.LASF804
	.byte	0x5
	.byte	0x46
	.4byte	.LASF805
	.byte	0x5
	.byte	0x47
	.4byte	.LASF806
	.byte	0x5
	.byte	0x48
	.4byte	.LASF807
	.byte	0x5
	.byte	0x49
	.4byte	.LASF808
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF809
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF810
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF811
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF812
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF813
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF814
	.byte	0x5
	.byte	0x50
	.4byte	.LASF815
	.byte	0x5
	.byte	0x51
	.4byte	.LASF816
	.byte	0x5
	.byte	0x52
	.4byte	.LASF817
	.byte	0x5
	.byte	0x53
	.4byte	.LASF818
	.byte	0x5
	.byte	0x54
	.4byte	.LASF819
	.byte	0x5
	.byte	0x55
	.4byte	.LASF820
	.byte	0x5
	.byte	0x56
	.4byte	.LASF821
	.byte	0x5
	.byte	0x57
	.4byte	.LASF822
	.byte	0x5
	.byte	0x58
	.4byte	.LASF823
	.byte	0x5
	.byte	0x59
	.4byte	.LASF824
	.byte	0x5
	.byte	0x5a
	.4byte	.LASF825
	.byte	0x5
	.byte	0x5b
	.4byte	.LASF826
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF827
	.byte	0x5
	.byte	0x5d
	.4byte	.LASF828
	.byte	0x5
	.byte	0x5e
	.4byte	.LASF829
	.byte	0x5
	.byte	0x5f
	.4byte	.LASF830
	.byte	0x5
	.byte	0x60
	.4byte	.LASF831
	.byte	0x5
	.byte	0x61
	.4byte	.LASF832
	.byte	0x5
	.byte	0x62
	.4byte	.LASF833
	.byte	0x5
	.byte	0x63
	.4byte	.LASF834
	.byte	0x5
	.byte	0x64
	.4byte	.LASF835
	.byte	0x5
	.byte	0x65
	.4byte	.LASF836
	.byte	0x5
	.byte	0x66
	.4byte	.LASF837
	.byte	0x5
	.byte	0x67
	.4byte	.LASF838
	.byte	0x5
	.byte	0x68
	.4byte	.LASF839
	.byte	0x5
	.byte	0x69
	.4byte	.LASF840
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF841
	.byte	0x5
	.byte	0x6b
	.4byte	.LASF842
	.byte	0x5
	.byte	0x6c
	.4byte	.LASF843
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF844
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF845
	.byte	0x5
	.byte	0x6f
	.4byte	.LASF846
	.byte	0x5
	.byte	0x70
	.4byte	.LASF847
	.byte	0x5
	.byte	0x71
	.4byte	.LASF848
	.byte	0x5
	.byte	0x72
	.4byte	.LASF849
	.byte	0x5
	.byte	0x73
	.4byte	.LASF850
	.byte	0x5
	.byte	0x74
	.4byte	.LASF851
	.byte	0x5
	.byte	0x75
	.4byte	.LASF852
	.byte	0x5
	.byte	0x76
	.4byte	.LASF853
	.byte	0x5
	.byte	0x77
	.4byte	.LASF854
	.byte	0x5
	.byte	0x78
	.4byte	.LASF855
	.byte	0x5
	.byte	0x79
	.4byte	.LASF856
	.byte	0x5
	.byte	0x7a
	.4byte	.LASF857
	.byte	0x5
	.byte	0x7b
	.4byte	.LASF858
	.byte	0x5
	.byte	0x7c
	.4byte	.LASF859
	.byte	0x5
	.byte	0x7d
	.4byte	.LASF860
	.byte	0x5
	.byte	0x7e
	.4byte	.LASF861
	.byte	0x5
	.byte	0x7f
	.4byte	.LASF862
	.byte	0x5
	.byte	0x80,0x1
	.4byte	.LASF863
	.byte	0x5
	.byte	0x81,0x1
	.4byte	.LASF864
	.byte	0x5
	.byte	0x82,0x1
	.4byte	.LASF865
	.byte	0x5
	.byte	0x83,0x1
	.4byte	.LASF866
	.byte	0x5
	.byte	0x84,0x1
	.4byte	.LASF867
	.byte	0x5
	.byte	0x85,0x1
	.4byte	.LASF868
	.byte	0x5
	.byte	0x86,0x1
	.4byte	.LASF869
	.byte	0x5
	.byte	0x87,0x1
	.4byte	.LASF870
	.byte	0x5
	.byte	0x88,0x1
	.4byte	.LASF871
	.byte	0x5
	.byte	0x8b,0x1
	.4byte	.LASF872
	.byte	0x5
	.byte	0x8c,0x1
	.4byte	.LASF873
	.byte	0x5
	.byte	0x8d,0x1
	.4byte	.LASF874
	.byte	0x5
	.byte	0x8e,0x1
	.4byte	.LASF875
	.byte	0x5
	.byte	0x91,0x1
	.4byte	.LASF876
	.byte	0x5
	.byte	0x92,0x1
	.4byte	.LASF877
	.byte	0x5
	.byte	0x95,0x1
	.4byte	.LASF878
	.byte	0x5
	.byte	0x96,0x1
	.4byte	.LASF879
	.byte	0x5
	.byte	0x97,0x1
	.4byte	.LASF880
	.byte	0x5
	.byte	0x98,0x1
	.4byte	.LASF881
	.byte	0x5
	.byte	0x9c,0x1
	.4byte	.LASF882
	.byte	0x5
	.byte	0x9d,0x1
	.4byte	.LASF883
	.byte	0x5
	.byte	0x9e,0x1
	.4byte	.LASF884
	.byte	0x5
	.byte	0x9f,0x1
	.4byte	.LASF885
	.byte	0x5
	.byte	0xa0,0x1
	.4byte	.LASF886
	.byte	0x5
	.byte	0xa1,0x1
	.4byte	.LASF887
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF888
	.byte	0x5
	.byte	0xa3,0x1
	.4byte	.LASF889
	.byte	0x5
	.byte	0xa4,0x1
	.4byte	.LASF890
	.byte	0x5
	.byte	0xa5,0x1
	.4byte	.LASF891
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF892
	.byte	0x5
	.byte	0xa9,0x1
	.4byte	.LASF893
	.byte	0x5
	.byte	0xaa,0x1
	.4byte	.LASF894
	.byte	0x5
	.byte	0xab,0x1
	.4byte	.LASF895
	.byte	0x5
	.byte	0xac,0x1
	.4byte	.LASF896
	.byte	0x5
	.byte	0xad,0x1
	.4byte	.LASF897
	.byte	0x5
	.byte	0xae,0x1
	.4byte	.LASF898
	.byte	0x5
	.byte	0xaf,0x1
	.4byte	.LASF899
	.byte	0x5
	.byte	0xb0,0x1
	.4byte	.LASF900
	.byte	0x5
	.byte	0xb3,0x1
	.4byte	.LASF901
	.byte	0x5
	.byte	0xb4,0x1
	.4byte	.LASF902
	.byte	0x5
	.byte	0xb5,0x1
	.4byte	.LASF903
	.byte	0x5
	.byte	0xb6,0x1
	.4byte	.LASF904
	.byte	0x5
	.byte	0xb7,0x1
	.4byte	.LASF905
	.byte	0x5
	.byte	0xb8,0x1
	.4byte	.LASF906
	.byte	0x5
	.byte	0xb9,0x1
	.4byte	.LASF907
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF908
	.byte	0x5
	.byte	0xbb,0x1
	.4byte	.LASF909
	.byte	0x5
	.byte	0xbc,0x1
	.4byte	.LASF910
	.byte	0x5
	.byte	0xbd,0x1
	.4byte	.LASF911
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF912
	.byte	0x5
	.byte	0xbf,0x1
	.4byte	.LASF913
	.byte	0x5
	.byte	0xc0,0x1
	.4byte	.LASF914
	.byte	0x5
	.byte	0xc1,0x1
	.4byte	.LASF915
	.byte	0x5
	.byte	0xc2,0x1
	.4byte	.LASF916
	.byte	0x5
	.byte	0xc3,0x1
	.4byte	.LASF917
	.byte	0x5
	.byte	0xc4,0x1
	.4byte	.LASF918
	.byte	0x5
	.byte	0xc5,0x1
	.4byte	.LASF919
	.byte	0x5
	.byte	0xc6,0x1
	.4byte	.LASF920
	.byte	0x5
	.byte	0xc7,0x1
	.4byte	.LASF921
	.byte	0x5
	.byte	0xc8,0x1
	.4byte	.LASF922
	.byte	0x5
	.byte	0xcb,0x1
	.4byte	.LASF923
	.byte	0x5
	.byte	0xcc,0x1
	.4byte	.LASF924
	.byte	0x5
	.byte	0xcd,0x1
	.4byte	.LASF925
	.byte	0x5
	.byte	0xce,0x1
	.4byte	.LASF926
	.byte	0x5
	.byte	0xd1,0x1
	.4byte	.LASF927
	.byte	0x5
	.byte	0xd2,0x1
	.4byte	.LASF928
	.byte	0x5
	.byte	0xd3,0x1
	.4byte	.LASF929
	.byte	0x5
	.byte	0xd4,0x1
	.4byte	.LASF930
	.byte	0x5
	.byte	0xd7,0x1
	.4byte	.LASF931
	.byte	0x5
	.byte	0xd8,0x1
	.4byte	.LASF932
	.byte	0x5
	.byte	0xd9,0x1
	.4byte	.LASF933
	.byte	0x5
	.byte	0xda,0x1
	.4byte	.LASF934
	.byte	0x5
	.byte	0xdb,0x1
	.4byte	.LASF935
	.byte	0x5
	.byte	0xdc,0x1
	.4byte	.LASF936
	.byte	0x5
	.byte	0xdd,0x1
	.4byte	.LASF937
	.byte	0x5
	.byte	0xde,0x1
	.4byte	.LASF938
	.byte	0x5
	.byte	0xdf,0x1
	.4byte	.LASF939
	.byte	0x5
	.byte	0xe0,0x1
	.4byte	.LASF940
	.byte	0x5
	.byte	0xe1,0x1
	.4byte	.LASF941
	.byte	0x5
	.byte	0xe2,0x1
	.4byte	.LASF942
	.byte	0x5
	.byte	0xe3,0x1
	.4byte	.LASF943
	.byte	0x5
	.byte	0xe4,0x1
	.4byte	.LASF944
	.byte	0x5
	.byte	0xe7,0x1
	.4byte	.LASF945
	.byte	0x5
	.byte	0xe8,0x1
	.4byte	.LASF946
	.byte	0x5
	.byte	0xe9,0x1
	.4byte	.LASF947
	.byte	0x5
	.byte	0xea,0x1
	.4byte	.LASF948
	.byte	0x5
	.byte	0xeb,0x1
	.4byte	.LASF949
	.byte	0x5
	.byte	0xec,0x1
	.4byte	.LASF950
	.byte	0x5
	.byte	0xef,0x1
	.4byte	.LASF951
	.byte	0x5
	.byte	0xf0,0x1
	.4byte	.LASF952
	.byte	0x5
	.byte	0xf1,0x1
	.4byte	.LASF953
	.byte	0x5
	.byte	0xf2,0x1
	.4byte	.LASF954
	.byte	0x5
	.byte	0xf3,0x1
	.4byte	.LASF955
	.byte	0x5
	.byte	0xf4,0x1
	.4byte	.LASF956
	.byte	0x5
	.byte	0xf7,0x1
	.4byte	.LASF957
	.byte	0x5
	.byte	0xf8,0x1
	.4byte	.LASF958
	.byte	0x5
	.byte	0xf9,0x1
	.4byte	.LASF959
	.byte	0x5
	.byte	0xfa,0x1
	.4byte	.LASF960
	.byte	0x5
	.byte	0xfb,0x1
	.4byte	.LASF961
	.byte	0x5
	.byte	0xfe,0x1
	.4byte	.LASF962
	.byte	0x5
	.byte	0xff,0x1
	.4byte	.LASF963
	.byte	0x5
	.byte	0x80,0x2
	.4byte	.LASF964
	.byte	0x5
	.byte	0x83,0x2
	.4byte	.LASF965
	.byte	0x5
	.byte	0x84,0x2
	.4byte	.LASF966
	.byte	0x5
	.byte	0x85,0x2
	.4byte	.LASF967
	.byte	0x5
	.byte	0x86,0x2
	.4byte	.LASF968
	.byte	0x5
	.byte	0x89,0x2
	.4byte	.LASF969
	.byte	0x5
	.byte	0x8a,0x2
	.4byte	.LASF970
	.byte	0x5
	.byte	0x8b,0x2
	.4byte	.LASF971
	.byte	0x5
	.byte	0x8c,0x2
	.4byte	.LASF972
	.byte	0x5
	.byte	0x8f,0x2
	.4byte	.LASF973
	.byte	0x5
	.byte	0x90,0x2
	.4byte	.LASF974
	.byte	0x5
	.byte	0x91,0x2
	.4byte	.LASF975
	.byte	0x5
	.byte	0x92,0x2
	.4byte	.LASF976
	.byte	0x5
	.byte	0x95,0x2
	.4byte	.LASF977
	.byte	0x5
	.byte	0x96,0x2
	.4byte	.LASF978
	.byte	0x5
	.byte	0x97,0x2
	.4byte	.LASF979
	.byte	0x5
	.byte	0x9a,0x2
	.4byte	.LASF980
	.byte	0x5
	.byte	0x9b,0x2
	.4byte	.LASF981
	.byte	0x5
	.byte	0x9c,0x2
	.4byte	.LASF982
	.byte	0x5
	.byte	0x9d,0x2
	.4byte	.LASF983
	.byte	0x5
	.byte	0xa0,0x2
	.4byte	.LASF984
	.byte	0x5
	.byte	0xa1,0x2
	.4byte	.LASF985
	.byte	0x5
	.byte	0xa2,0x2
	.4byte	.LASF986
	.byte	0x5
	.byte	0xa3,0x2
	.4byte	.LASF987
	.byte	0x5
	.byte	0xa6,0x2
	.4byte	.LASF988
	.byte	0x5
	.byte	0xa7,0x2
	.4byte	.LASF989
	.byte	0x5
	.byte	0xaa,0x2
	.4byte	.LASF990
	.byte	0x5
	.byte	0xad,0x2
	.4byte	.LASF991
	.byte	0x5
	.byte	0xb0,0x2
	.4byte	.LASF992
	.byte	0x5
	.byte	0xb3,0x2
	.4byte	.LASF993
	.byte	0x5
	.byte	0xb6,0x2
	.4byte	.LASF994
	.byte	0x5
	.byte	0xba,0x2
	.4byte	.LASF995
	.byte	0x5
	.byte	0xbb,0x2
	.4byte	.LASF996
	.byte	0x5
	.byte	0xbc,0x2
	.4byte	.LASF997
	.byte	0x5
	.byte	0xbe,0x2
	.4byte	.LASF998
	.byte	0x5
	.byte	0xbf,0x2
	.4byte	.LASF999
	.byte	0x5
	.byte	0xc0,0x2
	.4byte	.LASF1000
	.byte	0x5
	.byte	0xc1,0x2
	.4byte	.LASF1001
	.byte	0x5
	.byte	0xc4,0x2
	.4byte	.LASF1002
	.byte	0x5
	.byte	0xc5,0x2
	.4byte	.LASF1003
	.byte	0x5
	.byte	0xc6,0x2
	.4byte	.LASF1004
	.byte	0x5
	.byte	0xc7,0x2
	.4byte	.LASF1005
	.byte	0x5
	.byte	0xc8,0x2
	.4byte	.LASF1006
	.byte	0x5
	.byte	0xe4,0x3
	.4byte	.LASF1007
	.byte	0x5
	.byte	0xe7,0x3
	.4byte	.LASF1008
	.byte	0x5
	.byte	0xea,0x3
	.4byte	.LASF1009
	.byte	0x5
	.byte	0xed,0x3
	.4byte	.LASF1010
	.byte	0x5
	.byte	0xf0,0x3
	.4byte	.LASF1011
	.byte	0x5
	.byte	0xf3,0x3
	.4byte	.LASF1012
	.byte	0x5
	.byte	0xf6,0x3
	.4byte	.LASF1013
	.byte	0x5
	.byte	0xf9,0x3
	.4byte	.LASF1014
	.byte	0x5
	.byte	0xfc,0x3
	.4byte	.LASF1015
	.byte	0x5
	.byte	0xff,0x3
	.4byte	.LASF1016
	.byte	0x5
	.byte	0x82,0x4
	.4byte	.LASF1017
	.byte	0x5
	.byte	0x85,0x4
	.4byte	.LASF1018
	.byte	0x5
	.byte	0x88,0x4
	.4byte	.LASF1019
	.byte	0x5
	.byte	0x8b,0x4
	.4byte	.LASF1020
	.byte	0x5
	.byte	0x8e,0x4
	.4byte	.LASF1021
	.byte	0x5
	.byte	0x91,0x4
	.4byte	.LASF1022
	.byte	0x5
	.byte	0x94,0x4
	.4byte	.LASF1023
	.byte	0x5
	.byte	0x97,0x4
	.4byte	.LASF1024
	.byte	0x5
	.byte	0x9a,0x4
	.4byte	.LASF1025
	.byte	0x5
	.byte	0x9d,0x4
	.4byte	.LASF1026
	.byte	0x5
	.byte	0xa0,0x4
	.4byte	.LASF1027
	.byte	0x5
	.byte	0xa3,0x4
	.4byte	.LASF1028
	.byte	0x5
	.byte	0xa6,0x4
	.4byte	.LASF1029
	.byte	0x5
	.byte	0xa9,0x4
	.4byte	.LASF1030
	.byte	0x5
	.byte	0xac,0x4
	.4byte	.LASF1031
	.byte	0x5
	.byte	0xaf,0x4
	.4byte	.LASF1032
	.byte	0x5
	.byte	0xb2,0x4
	.4byte	.LASF1033
	.byte	0x5
	.byte	0xb5,0x4
	.4byte	.LASF1034
	.byte	0x5
	.byte	0xb8,0x4
	.4byte	.LASF1035
	.byte	0x5
	.byte	0xbb,0x4
	.4byte	.LASF1036
	.byte	0x5
	.byte	0xbe,0x4
	.4byte	.LASF1037
	.byte	0x5
	.byte	0xc1,0x4
	.4byte	.LASF1038
	.byte	0x5
	.byte	0xc4,0x4
	.4byte	.LASF1039
	.byte	0x5
	.byte	0xc7,0x4
	.4byte	.LASF1040
	.byte	0x5
	.byte	0xc8,0x4
	.4byte	.LASF1041
	.byte	0x5
	.byte	0xc9,0x4
	.4byte	.LASF1042
	.byte	0x5
	.byte	0xca,0x4
	.4byte	.LASF1043
	.byte	0x5
	.byte	0xcb,0x4
	.4byte	.LASF1044
	.byte	0x5
	.byte	0xcc,0x4
	.4byte	.LASF1045
	.byte	0x5
	.byte	0xcd,0x4
	.4byte	.LASF1046
	.byte	0x5
	.byte	0xce,0x4
	.4byte	.LASF1047
	.byte	0x5
	.byte	0xcf,0x4
	.4byte	.LASF1048
	.byte	0x5
	.byte	0xd1,0x4
	.4byte	.LASF1049
	.byte	0x5
	.byte	0xd4,0x4
	.4byte	.LASF1050
	.byte	0x5
	.byte	0xd5,0x4
	.4byte	.LASF1051
	.byte	0x5
	.byte	0xd6,0x4
	.4byte	.LASF1052
	.byte	0x5
	.byte	0xd7,0x4
	.4byte	.LASF1053
	.byte	0x5
	.byte	0xda,0x4
	.4byte	.LASF1054
	.byte	0x5
	.byte	0xdb,0x4
	.4byte	.LASF1055
	.byte	0x5
	.byte	0xdc,0x4
	.4byte	.LASF1056
	.byte	0x5
	.byte	0xdd,0x4
	.4byte	.LASF1057
	.byte	0x5
	.byte	0xe0,0x4
	.4byte	.LASF1058
	.byte	0x5
	.byte	0xe1,0x4
	.4byte	.LASF1059
	.byte	0x5
	.byte	0xe2,0x4
	.4byte	.LASF1060
	.byte	0x5
	.byte	0xe3,0x4
	.4byte	.LASF1061
	.byte	0x5
	.byte	0xe4,0x4
	.4byte	.LASF1062
	.byte	0x5
	.byte	0xe5,0x4
	.4byte	.LASF1063
	.byte	0x5
	.byte	0xe6,0x4
	.4byte	.LASF1064
	.byte	0x5
	.byte	0xe7,0x4
	.4byte	.LASF1065
	.byte	0x5
	.byte	0xe8,0x4
	.4byte	.LASF1066
	.byte	0x5
	.byte	0xe9,0x4
	.4byte	.LASF1067
	.byte	0x5
	.byte	0xea,0x4
	.4byte	.LASF1068
	.byte	0x5
	.byte	0xeb,0x4
	.4byte	.LASF1069
	.byte	0x5
	.byte	0xec,0x4
	.4byte	.LASF1070
	.byte	0x5
	.byte	0xed,0x4
	.4byte	.LASF1071
	.byte	0x5
	.byte	0xee,0x4
	.4byte	.LASF1072
	.byte	0x5
	.byte	0xef,0x4
	.4byte	.LASF1073
	.byte	0x5
	.byte	0xf2,0x4
	.4byte	.LASF1074
	.byte	0x5
	.byte	0xf3,0x4
	.4byte	.LASF1075
	.byte	0x5
	.byte	0xf4,0x4
	.4byte	.LASF1076
	.byte	0x5
	.byte	0xf5,0x4
	.4byte	.LASF1077
	.byte	0x5
	.byte	0xf6,0x4
	.4byte	.LASF1078
	.byte	0x5
	.byte	0xf7,0x4
	.4byte	.LASF1079
	.byte	0x5
	.byte	0xf8,0x4
	.4byte	.LASF1080
	.byte	0x5
	.byte	0xf9,0x4
	.4byte	.LASF1081
	.byte	0x5
	.byte	0xfc,0x4
	.4byte	.LASF1082
	.byte	0x5
	.byte	0xfd,0x4
	.4byte	.LASF1083
	.byte	0x5
	.byte	0xfe,0x4
	.4byte	.LASF1084
	.byte	0x5
	.byte	0xff,0x4
	.4byte	.LASF1085
	.byte	0x5
	.byte	0x82,0x5
	.4byte	.LASF1086
	.byte	0x5
	.byte	0x83,0x5
	.4byte	.LASF1087
	.byte	0x5
	.byte	0x86,0x5
	.4byte	.LASF1088
	.byte	0x5
	.byte	0x87,0x5
	.4byte	.LASF1089
	.byte	0x5
	.byte	0x8a,0x5
	.4byte	.LASF1090
	.byte	0x5
	.byte	0x8c,0x5
	.4byte	.LASF1091
	.byte	0x5
	.byte	0x8d,0x5
	.4byte	.LASF1092
	.byte	0x5
	.byte	0x90,0x5
	.4byte	.LASF1093
	.byte	0x5
	.byte	0x91,0x5
	.4byte	.LASF1094
	.byte	0x5
	.byte	0x92,0x5
	.4byte	.LASF1095
	.byte	0x5
	.byte	0x95,0x5
	.4byte	.LASF1096
	.byte	0x5
	.byte	0x96,0x5
	.4byte	.LASF1097
	.byte	0x5
	.byte	0x99,0x5
	.4byte	.LASF1098
	.byte	0x5
	.byte	0x9a,0x5
	.4byte	.LASF1099
	.byte	0x5
	.byte	0x9d,0x5
	.4byte	.LASF1100
	.byte	0x5
	.byte	0xa0,0x5
	.4byte	.LASF1101
	.byte	0x5
	.byte	0xa1,0x5
	.4byte	.LASF1102
	.byte	0x5
	.byte	0xa4,0x5
	.4byte	.LASF1103
	.byte	0x5
	.byte	0xa7,0x5
	.4byte	.LASF1104
	.byte	0x5
	.byte	0xa8,0x5
	.4byte	.LASF1105
	.byte	0x5
	.byte	0xa9,0x5
	.4byte	.LASF1106
	.byte	0x5
	.byte	0xaa,0x5
	.4byte	.LASF1107
	.byte	0x5
	.byte	0xab,0x5
	.4byte	.LASF1108
	.byte	0x5
	.byte	0xac,0x5
	.4byte	.LASF1109
	.byte	0x5
	.byte	0xad,0x5
	.4byte	.LASF1110
	.byte	0x5
	.byte	0xae,0x5
	.4byte	.LASF1111
	.byte	0x5
	.byte	0xaf,0x5
	.4byte	.LASF1112
	.byte	0x5
	.byte	0xb0,0x5
	.4byte	.LASF1113
	.byte	0x5
	.byte	0xb1,0x5
	.4byte	.LASF1114
	.byte	0x5
	.byte	0xb2,0x5
	.4byte	.LASF1115
	.byte	0x5
	.byte	0xb3,0x5
	.4byte	.LASF1116
	.byte	0x5
	.byte	0xb4,0x5
	.4byte	.LASF1117
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_crc.h.37.f77f53f1516fc65e49eac544ab82df8c,comdat
.Ldebug_macro13:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF1118
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF1119
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF1120
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF1121
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF1122
	.byte	0x5
	.byte	0x33
	.4byte	.LASF1123
	.byte	0x5
	.byte	0x36
	.4byte	.LASF1124
	.byte	0x5
	.byte	0x39
	.4byte	.LASF1125
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_dac.h.37.c64e29f692c863eb577e59c8c0ad940a,comdat
.Ldebug_macro14:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF1126
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF1127
	.byte	0x5
	.byte	0x2b
	.4byte	.LASF1128
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF1129
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF1130
	.byte	0x5
	.byte	0x30
	.4byte	.LASF1131
	.byte	0x5
	.byte	0x31
	.4byte	.LASF1132
	.byte	0x5
	.byte	0x32
	.4byte	.LASF1133
	.byte	0x5
	.byte	0x33
	.4byte	.LASF1134
	.byte	0x5
	.byte	0x34
	.4byte	.LASF1135
	.byte	0x5
	.byte	0x35
	.4byte	.LASF1136
	.byte	0x5
	.byte	0x36
	.4byte	.LASF1137
	.byte	0x5
	.byte	0x37
	.4byte	.LASF1138
	.byte	0x5
	.byte	0x38
	.4byte	.LASF1139
	.byte	0x5
	.byte	0x39
	.4byte	.LASF1140
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF1141
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF1142
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF1143
	.byte	0x5
	.byte	0x40
	.4byte	.LASF1144
	.byte	0x5
	.byte	0x41
	.4byte	.LASF1145
	.byte	0x5
	.byte	0x42
	.4byte	.LASF1146
	.byte	0x5
	.byte	0x43
	.4byte	.LASF1147
	.byte	0x5
	.byte	0x44
	.4byte	.LASF1148
	.byte	0x5
	.byte	0x45
	.4byte	.LASF1149
	.byte	0x5
	.byte	0x46
	.4byte	.LASF1150
	.byte	0x5
	.byte	0x47
	.4byte	.LASF1151
	.byte	0x5
	.byte	0x48
	.4byte	.LASF1152
	.byte	0x5
	.byte	0x49
	.4byte	.LASF1153
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF1154
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF1155
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF1156
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF1157
	.byte	0x5
	.byte	0x50
	.4byte	.LASF1158
	.byte	0x5
	.byte	0x53
	.4byte	.LASF1159
	.byte	0x5
	.byte	0x56
	.4byte	.LASF1160
	.byte	0x5
	.byte	0x59
	.4byte	.LASF1161
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF1162
	.byte	0x5
	.byte	0x5f
	.4byte	.LASF1163
	.byte	0x5
	.byte	0x62
	.4byte	.LASF1164
	.byte	0x5
	.byte	0x65
	.4byte	.LASF1165
	.byte	0x5
	.byte	0x66
	.4byte	.LASF1166
	.byte	0x5
	.byte	0x69
	.4byte	.LASF1167
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF1168
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF1169
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF1170
	.byte	0x5
	.byte	0x71
	.4byte	.LASF1171
	.byte	0x5
	.byte	0x74
	.4byte	.LASF1172
	.byte	0x5
	.byte	0x78
	.4byte	.LASF1173
	.byte	0x5
	.byte	0x79
	.4byte	.LASF1174
	.byte	0x5
	.byte	0x7a
	.4byte	.LASF1175
	.byte	0x5
	.byte	0x7b
	.4byte	.LASF1176
	.byte	0x5
	.byte	0x7c
	.4byte	.LASF1177
	.byte	0x5
	.byte	0x7d
	.4byte	.LASF1178
	.byte	0x5
	.byte	0x7e
	.4byte	.LASF1179
	.byte	0x5
	.byte	0x7f
	.4byte	.LASF1180
	.byte	0x5
	.byte	0x80,0x1
	.4byte	.LASF1181
	.byte	0x5
	.byte	0x83,0x1
	.4byte	.LASF1182
	.byte	0x5
	.byte	0x84,0x1
	.4byte	.LASF1183
	.byte	0x5
	.byte	0x85,0x1
	.4byte	.LASF1184
	.byte	0x5
	.byte	0x86,0x1
	.4byte	.LASF1185
	.byte	0x5
	.byte	0x89,0x1
	.4byte	.LASF1186
	.byte	0x5
	.byte	0x8a,0x1
	.4byte	.LASF1187
	.byte	0x5
	.byte	0x8b,0x1
	.4byte	.LASF1188
	.byte	0x5
	.byte	0x8c,0x1
	.4byte	.LASF1189
	.byte	0x5
	.byte	0x8d,0x1
	.4byte	.LASF1190
	.byte	0x5
	.byte	0x8e,0x1
	.4byte	.LASF1191
	.byte	0x5
	.byte	0x8f,0x1
	.4byte	.LASF1192
	.byte	0x5
	.byte	0x90,0x1
	.4byte	.LASF1193
	.byte	0x5
	.byte	0x91,0x1
	.4byte	.LASF1194
	.byte	0x5
	.byte	0x92,0x1
	.4byte	.LASF1195
	.byte	0x5
	.byte	0x93,0x1
	.4byte	.LASF1196
	.byte	0x5
	.byte	0x94,0x1
	.4byte	.LASF1197
	.byte	0x5
	.byte	0x95,0x1
	.4byte	.LASF1198
	.byte	0x5
	.byte	0x98,0x1
	.4byte	.LASF1199
	.byte	0x5
	.byte	0x99,0x1
	.4byte	.LASF1200
	.byte	0x5
	.byte	0x9a,0x1
	.4byte	.LASF1201
	.byte	0x5
	.byte	0x9b,0x1
	.4byte	.LASF1202
	.byte	0x5
	.byte	0x9c,0x1
	.4byte	.LASF1203
	.byte	0x5
	.byte	0x9d,0x1
	.4byte	.LASF1204
	.byte	0x5
	.byte	0x9e,0x1
	.4byte	.LASF1205
	.byte	0x5
	.byte	0x9f,0x1
	.4byte	.LASF1206
	.byte	0x5
	.byte	0xa0,0x1
	.4byte	.LASF1207
	.byte	0x5
	.byte	0xa1,0x1
	.4byte	.LASF1208
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF1209
	.byte	0x5
	.byte	0xa3,0x1
	.4byte	.LASF1210
	.byte	0x5
	.byte	0xa6,0x1
	.4byte	.LASF1211
	.byte	0x5
	.byte	0xa7,0x1
	.4byte	.LASF1212
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF1213
	.byte	0x5
	.byte	0xa9,0x1
	.4byte	.LASF1214
	.byte	0x5
	.byte	0xab,0x1
	.4byte	.LASF1215
	.byte	0x5
	.byte	0xac,0x1
	.4byte	.LASF1216
	.byte	0x5
	.byte	0xad,0x1
	.4byte	.LASF1217
	.byte	0x5
	.byte	0xae,0x1
	.4byte	.LASF1218
	.byte	0x5
	.byte	0xaf,0x1
	.4byte	.LASF1219
	.byte	0x5
	.byte	0xb0,0x1
	.4byte	.LASF1220
	.byte	0x5
	.byte	0xb1,0x1
	.4byte	.LASF1221
	.byte	0x5
	.byte	0xb2,0x1
	.4byte	.LASF1222
	.byte	0x5
	.byte	0xb3,0x1
	.4byte	.LASF1223
	.byte	0x5
	.byte	0xb4,0x1
	.4byte	.LASF1224
	.byte	0x5
	.byte	0xb5,0x1
	.4byte	.LASF1225
	.byte	0x5
	.byte	0xb6,0x1
	.4byte	.LASF1226
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_dma.h.38.2c314170096cba83b58f6eccfc84a5f7,comdat
.Ldebug_macro15:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x26
	.4byte	.LASF1227
	.byte	0x5
	.byte	0x2b
	.4byte	.LASF1228
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF1229
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF1230
	.byte	0x5
	.byte	0x30
	.4byte	.LASF1231
	.byte	0x5
	.byte	0x32
	.4byte	.LASF1232
	.byte	0x5
	.byte	0x33
	.4byte	.LASF1233
	.byte	0x5
	.byte	0x34
	.4byte	.LASF1234
	.byte	0x5
	.byte	0x35
	.4byte	.LASF1235
	.byte	0x5
	.byte	0x37
	.4byte	.LASF1236
	.byte	0x5
	.byte	0x38
	.4byte	.LASF1237
	.byte	0x5
	.byte	0x39
	.4byte	.LASF1238
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF1239
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF1240
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF1241
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF1242
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF1243
	.byte	0x5
	.byte	0x41
	.4byte	.LASF1244
	.byte	0x5
	.byte	0x42
	.4byte	.LASF1245
	.byte	0x5
	.byte	0x43
	.4byte	.LASF1246
	.byte	0x5
	.byte	0x44
	.4byte	.LASF1247
	.byte	0x5
	.byte	0x46
	.4byte	.LASF1248
	.byte	0x5
	.byte	0x47
	.4byte	.LASF1249
	.byte	0x5
	.byte	0x48
	.4byte	.LASF1250
	.byte	0x5
	.byte	0x49
	.4byte	.LASF1251
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF1252
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF1253
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF1254
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF1255
	.byte	0x5
	.byte	0x50
	.4byte	.LASF1256
	.byte	0x5
	.byte	0x51
	.4byte	.LASF1257
	.byte	0x5
	.byte	0x52
	.4byte	.LASF1258
	.byte	0x5
	.byte	0x53
	.4byte	.LASF1259
	.byte	0x5
	.byte	0x57
	.4byte	.LASF1260
	.byte	0x5
	.byte	0x58
	.4byte	.LASF1261
	.byte	0x5
	.byte	0x59
	.4byte	.LASF1262
	.byte	0x5
	.byte	0x5a
	.4byte	.LASF1263
	.byte	0x5
	.byte	0x5d
	.4byte	.LASF1264
	.byte	0x5
	.byte	0x5e
	.4byte	.LASF1265
	.byte	0x5
	.byte	0x5f
	.4byte	.LASF1266
	.byte	0x5
	.byte	0x60
	.4byte	.LASF1267
	.byte	0x5
	.byte	0x63
	.4byte	.LASF1268
	.byte	0x5
	.byte	0x64
	.4byte	.LASF1269
	.byte	0x5
	.byte	0x65
	.4byte	.LASF1270
	.byte	0x5
	.byte	0x66
	.4byte	.LASF1271
	.byte	0x5
	.byte	0x67
	.4byte	.LASF1272
	.byte	0x5
	.byte	0x68
	.4byte	.LASF1273
	.byte	0x5
	.byte	0x69
	.4byte	.LASF1274
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF1275
	.byte	0x5
	.byte	0x6b
	.4byte	.LASF1276
	.byte	0x5
	.byte	0x6c
	.4byte	.LASF1277
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF1278
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF1279
	.byte	0x5
	.byte	0x71
	.4byte	.LASF1280
	.byte	0x5
	.byte	0x74
	.4byte	.LASF1281
	.byte	0x5
	.byte	0x77
	.4byte	.LASF1282
	.byte	0x5
	.byte	0x95,0x1
	.4byte	.LASF1283
	.byte	0x5
	.byte	0x98,0x1
	.4byte	.LASF1284
	.byte	0x5
	.byte	0x99,0x1
	.4byte	.LASF1285
	.byte	0x5
	.byte	0x9a,0x1
	.4byte	.LASF1286
	.byte	0x5
	.byte	0x9b,0x1
	.4byte	.LASF1287
	.byte	0x5
	.byte	0x9e,0x1
	.4byte	.LASF1288
	.byte	0x5
	.byte	0x9f,0x1
	.4byte	.LASF1289
	.byte	0x5
	.byte	0xa0,0x1
	.4byte	.LASF1290
	.byte	0x5
	.byte	0xa1,0x1
	.4byte	.LASF1291
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF1292
	.byte	0x5
	.byte	0xa7,0x1
	.4byte	.LASF1293
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF1294
	.byte	0x5
	.byte	0xa9,0x1
	.4byte	.LASF1295
	.byte	0x5
	.byte	0xaa,0x1
	.4byte	.LASF1296
	.byte	0x5
	.byte	0xad,0x1
	.4byte	.LASF1297
	.byte	0x5
	.byte	0xae,0x1
	.4byte	.LASF1298
	.byte	0x5
	.byte	0xaf,0x1
	.4byte	.LASF1299
	.byte	0x5
	.byte	0xb0,0x1
	.4byte	.LASF1300
	.byte	0x5
	.byte	0xb4,0x1
	.4byte	.LASF1301
	.byte	0x5
	.byte	0xb5,0x1
	.4byte	.LASF1302
	.byte	0x5
	.byte	0xb6,0x1
	.4byte	.LASF1303
	.byte	0x5
	.byte	0xb9,0x1
	.4byte	.LASF1304
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF1305
	.byte	0x5
	.byte	0xbd,0x1
	.4byte	.LASF1306
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF1307
	.byte	0x5
	.byte	0xc1,0x1
	.4byte	.LASF1308
	.byte	0x5
	.byte	0xc2,0x1
	.4byte	.LASF1309
	.byte	0x5
	.byte	0xc5,0x1
	.4byte	.LASF1310
	.byte	0x5
	.byte	0xc6,0x1
	.4byte	.LASF1311
	.byte	0x5
	.byte	0xc7,0x1
	.4byte	.LASF1312
	.byte	0x5
	.byte	0xc8,0x1
	.4byte	.LASF1313
	.byte	0x5
	.byte	0xcb,0x1
	.4byte	.LASF1314
	.byte	0x5
	.byte	0xcc,0x1
	.4byte	.LASF1315
	.byte	0x5
	.byte	0xcd,0x1
	.4byte	.LASF1316
	.byte	0x5
	.byte	0xce,0x1
	.4byte	.LASF1317
	.byte	0x5
	.byte	0xd1,0x1
	.4byte	.LASF1318
	.byte	0x5
	.byte	0xd2,0x1
	.4byte	.LASF1319
	.byte	0x5
	.byte	0xd3,0x1
	.4byte	.LASF1320
	.byte	0x5
	.byte	0xd4,0x1
	.4byte	.LASF1321
	.byte	0x5
	.byte	0xd5,0x1
	.4byte	.LASF1322
	.byte	0x5
	.byte	0xd8,0x1
	.4byte	.LASF1323
	.byte	0x5
	.byte	0xd9,0x1
	.4byte	.LASF1324
	.byte	0x5
	.byte	0xdd,0x1
	.4byte	.LASF1325
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_eclic.h.37.7db9f8893169694757dea82a4b9eed61,comdat
.Ldebug_macro16:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF1326
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF1327
	.byte	0x5
	.byte	0x2b
	.4byte	.LASF1328
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF1329
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF1330
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF1331
	.byte	0x5
	.byte	0x30
	.4byte	.LASF1332
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_exmc.h.37.96699be4b910beb81cdfd35650becbf1,comdat
.Ldebug_macro17:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF1333
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF1334
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF1335
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF1336
	.byte	0x5
	.byte	0x30
	.4byte	.LASF1337
	.byte	0x5
	.byte	0x35
	.4byte	.LASF1338
	.byte	0x5
	.byte	0x36
	.4byte	.LASF1339
	.byte	0x5
	.byte	0x37
	.4byte	.LASF1340
	.byte	0x5
	.byte	0x38
	.4byte	.LASF1341
	.byte	0x5
	.byte	0x39
	.4byte	.LASF1342
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF1343
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF1344
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF1345
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF1346
	.byte	0x5
	.byte	0x40
	.4byte	.LASF1347
	.byte	0x5
	.byte	0x41
	.4byte	.LASF1348
	.byte	0x5
	.byte	0x42
	.4byte	.LASF1349
	.byte	0x5
	.byte	0x43
	.4byte	.LASF1350
	.byte	0x5
	.byte	0x5e
	.4byte	.LASF1351
	.byte	0x5
	.byte	0x5f
	.4byte	.LASF1352
	.byte	0x5
	.byte	0x62
	.4byte	.LASF1353
	.byte	0x5
	.byte	0x63
	.4byte	.LASF1354
	.byte	0x5
	.byte	0x64
	.4byte	.LASF1355
	.byte	0x5
	.byte	0x67
	.4byte	.LASF1356
	.byte	0x5
	.byte	0x68
	.4byte	.LASF1357
	.byte	0x5
	.byte	0x69
	.4byte	.LASF1358
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF1359
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF1360
	.byte	0x5
	.byte	0x70
	.4byte	.LASF1361
	.byte	0x5
	.byte	0x71
	.4byte	.LASF1362
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_exti.h.37.a48547bbdeb43685ea30e1aa7e1bc0e9,comdat
.Ldebug_macro18:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF1363
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF1364
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF1365
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF1366
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF1367
	.byte	0x5
	.byte	0x30
	.4byte	.LASF1368
	.byte	0x5
	.byte	0x31
	.4byte	.LASF1369
	.byte	0x5
	.byte	0x32
	.4byte	.LASF1370
	.byte	0x5
	.byte	0x36
	.4byte	.LASF1371
	.byte	0x5
	.byte	0x37
	.4byte	.LASF1372
	.byte	0x5
	.byte	0x38
	.4byte	.LASF1373
	.byte	0x5
	.byte	0x39
	.4byte	.LASF1374
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF1375
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF1376
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF1377
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF1378
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF1379
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF1380
	.byte	0x5
	.byte	0x40
	.4byte	.LASF1381
	.byte	0x5
	.byte	0x41
	.4byte	.LASF1382
	.byte	0x5
	.byte	0x42
	.4byte	.LASF1383
	.byte	0x5
	.byte	0x43
	.4byte	.LASF1384
	.byte	0x5
	.byte	0x44
	.4byte	.LASF1385
	.byte	0x5
	.byte	0x45
	.4byte	.LASF1386
	.byte	0x5
	.byte	0x46
	.4byte	.LASF1387
	.byte	0x5
	.byte	0x47
	.4byte	.LASF1388
	.byte	0x5
	.byte	0x48
	.4byte	.LASF1389
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF1390
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF1391
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF1392
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF1393
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF1394
	.byte	0x5
	.byte	0x50
	.4byte	.LASF1395
	.byte	0x5
	.byte	0x51
	.4byte	.LASF1396
	.byte	0x5
	.byte	0x52
	.4byte	.LASF1397
	.byte	0x5
	.byte	0x53
	.4byte	.LASF1398
	.byte	0x5
	.byte	0x54
	.4byte	.LASF1399
	.byte	0x5
	.byte	0x55
	.4byte	.LASF1400
	.byte	0x5
	.byte	0x56
	.4byte	.LASF1401
	.byte	0x5
	.byte	0x57
	.4byte	.LASF1402
	.byte	0x5
	.byte	0x58
	.4byte	.LASF1403
	.byte	0x5
	.byte	0x59
	.4byte	.LASF1404
	.byte	0x5
	.byte	0x5a
	.4byte	.LASF1405
	.byte	0x5
	.byte	0x5b
	.4byte	.LASF1406
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF1407
	.byte	0x5
	.byte	0x5d
	.4byte	.LASF1408
	.byte	0x5
	.byte	0x60
	.4byte	.LASF1409
	.byte	0x5
	.byte	0x61
	.4byte	.LASF1410
	.byte	0x5
	.byte	0x62
	.4byte	.LASF1411
	.byte	0x5
	.byte	0x63
	.4byte	.LASF1412
	.byte	0x5
	.byte	0x64
	.4byte	.LASF1413
	.byte	0x5
	.byte	0x65
	.4byte	.LASF1414
	.byte	0x5
	.byte	0x66
	.4byte	.LASF1415
	.byte	0x5
	.byte	0x67
	.4byte	.LASF1416
	.byte	0x5
	.byte	0x68
	.4byte	.LASF1417
	.byte	0x5
	.byte	0x69
	.4byte	.LASF1418
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF1419
	.byte	0x5
	.byte	0x6b
	.4byte	.LASF1420
	.byte	0x5
	.byte	0x6c
	.4byte	.LASF1421
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF1422
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF1423
	.byte	0x5
	.byte	0x6f
	.4byte	.LASF1424
	.byte	0x5
	.byte	0x70
	.4byte	.LASF1425
	.byte	0x5
	.byte	0x71
	.4byte	.LASF1426
	.byte	0x5
	.byte	0x72
	.4byte	.LASF1427
	.byte	0x5
	.byte	0x75
	.4byte	.LASF1428
	.byte	0x5
	.byte	0x76
	.4byte	.LASF1429
	.byte	0x5
	.byte	0x77
	.4byte	.LASF1430
	.byte	0x5
	.byte	0x78
	.4byte	.LASF1431
	.byte	0x5
	.byte	0x79
	.4byte	.LASF1432
	.byte	0x5
	.byte	0x7a
	.4byte	.LASF1433
	.byte	0x5
	.byte	0x7b
	.4byte	.LASF1434
	.byte	0x5
	.byte	0x7c
	.4byte	.LASF1435
	.byte	0x5
	.byte	0x7d
	.4byte	.LASF1436
	.byte	0x5
	.byte	0x7e
	.4byte	.LASF1437
	.byte	0x5
	.byte	0x7f
	.4byte	.LASF1438
	.byte	0x5
	.byte	0x80,0x1
	.4byte	.LASF1439
	.byte	0x5
	.byte	0x81,0x1
	.4byte	.LASF1440
	.byte	0x5
	.byte	0x82,0x1
	.4byte	.LASF1441
	.byte	0x5
	.byte	0x83,0x1
	.4byte	.LASF1442
	.byte	0x5
	.byte	0x84,0x1
	.4byte	.LASF1443
	.byte	0x5
	.byte	0x85,0x1
	.4byte	.LASF1444
	.byte	0x5
	.byte	0x86,0x1
	.4byte	.LASF1445
	.byte	0x5
	.byte	0x87,0x1
	.4byte	.LASF1446
	.byte	0x5
	.byte	0x8a,0x1
	.4byte	.LASF1447
	.byte	0x5
	.byte	0x8b,0x1
	.4byte	.LASF1448
	.byte	0x5
	.byte	0x8c,0x1
	.4byte	.LASF1449
	.byte	0x5
	.byte	0x8d,0x1
	.4byte	.LASF1450
	.byte	0x5
	.byte	0x8e,0x1
	.4byte	.LASF1451
	.byte	0x5
	.byte	0x8f,0x1
	.4byte	.LASF1452
	.byte	0x5
	.byte	0x90,0x1
	.4byte	.LASF1453
	.byte	0x5
	.byte	0x91,0x1
	.4byte	.LASF1454
	.byte	0x5
	.byte	0x92,0x1
	.4byte	.LASF1455
	.byte	0x5
	.byte	0x93,0x1
	.4byte	.LASF1456
	.byte	0x5
	.byte	0x94,0x1
	.4byte	.LASF1457
	.byte	0x5
	.byte	0x95,0x1
	.4byte	.LASF1458
	.byte	0x5
	.byte	0x96,0x1
	.4byte	.LASF1459
	.byte	0x5
	.byte	0x97,0x1
	.4byte	.LASF1460
	.byte	0x5
	.byte	0x98,0x1
	.4byte	.LASF1461
	.byte	0x5
	.byte	0x99,0x1
	.4byte	.LASF1462
	.byte	0x5
	.byte	0x9a,0x1
	.4byte	.LASF1463
	.byte	0x5
	.byte	0x9b,0x1
	.4byte	.LASF1464
	.byte	0x5
	.byte	0x9c,0x1
	.4byte	.LASF1465
	.byte	0x5
	.byte	0x9f,0x1
	.4byte	.LASF1466
	.byte	0x5
	.byte	0xa0,0x1
	.4byte	.LASF1467
	.byte	0x5
	.byte	0xa1,0x1
	.4byte	.LASF1468
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF1469
	.byte	0x5
	.byte	0xa3,0x1
	.4byte	.LASF1470
	.byte	0x5
	.byte	0xa4,0x1
	.4byte	.LASF1471
	.byte	0x5
	.byte	0xa5,0x1
	.4byte	.LASF1472
	.byte	0x5
	.byte	0xa6,0x1
	.4byte	.LASF1473
	.byte	0x5
	.byte	0xa7,0x1
	.4byte	.LASF1474
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF1475
	.byte	0x5
	.byte	0xa9,0x1
	.4byte	.LASF1476
	.byte	0x5
	.byte	0xaa,0x1
	.4byte	.LASF1477
	.byte	0x5
	.byte	0xab,0x1
	.4byte	.LASF1478
	.byte	0x5
	.byte	0xac,0x1
	.4byte	.LASF1479
	.byte	0x5
	.byte	0xad,0x1
	.4byte	.LASF1480
	.byte	0x5
	.byte	0xae,0x1
	.4byte	.LASF1481
	.byte	0x5
	.byte	0xaf,0x1
	.4byte	.LASF1482
	.byte	0x5
	.byte	0xb0,0x1
	.4byte	.LASF1483
	.byte	0x5
	.byte	0xb1,0x1
	.4byte	.LASF1484
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_fmc.h.39.cad093dc97f9756dd7521b8e6602cd12,comdat
.Ldebug_macro19:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x27
	.4byte	.LASF1485
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF1486
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF1487
	.byte	0x5
	.byte	0x30
	.4byte	.LASF1488
	.byte	0x5
	.byte	0x31
	.4byte	.LASF1489
	.byte	0x5
	.byte	0x32
	.4byte	.LASF1490
	.byte	0x5
	.byte	0x33
	.4byte	.LASF1491
	.byte	0x5
	.byte	0x34
	.4byte	.LASF1492
	.byte	0x5
	.byte	0x35
	.4byte	.LASF1493
	.byte	0x5
	.byte	0x36
	.4byte	.LASF1494
	.byte	0x5
	.byte	0x37
	.4byte	.LASF1495
	.byte	0x5
	.byte	0x38
	.4byte	.LASF1496
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF1497
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF1498
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF1499
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF1500
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF1501
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF1502
	.byte	0x5
	.byte	0x43
	.4byte	.LASF1503
	.byte	0x5
	.byte	0x46
	.4byte	.LASF1504
	.byte	0x5
	.byte	0x49
	.4byte	.LASF1505
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF1506
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF1507
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF1508
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF1509
	.byte	0x5
	.byte	0x52
	.4byte	.LASF1510
	.byte	0x5
	.byte	0x53
	.4byte	.LASF1511
	.byte	0x5
	.byte	0x54
	.4byte	.LASF1512
	.byte	0x5
	.byte	0x55
	.4byte	.LASF1513
	.byte	0x5
	.byte	0x56
	.4byte	.LASF1514
	.byte	0x5
	.byte	0x57
	.4byte	.LASF1515
	.byte	0x5
	.byte	0x58
	.4byte	.LASF1516
	.byte	0x5
	.byte	0x59
	.4byte	.LASF1517
	.byte	0x5
	.byte	0x5a
	.4byte	.LASF1518
	.byte	0x5
	.byte	0x5b
	.4byte	.LASF1519
	.byte	0x5
	.byte	0x5e
	.4byte	.LASF1520
	.byte	0x5
	.byte	0x61
	.4byte	.LASF1521
	.byte	0x5
	.byte	0x62
	.4byte	.LASF1522
	.byte	0x5
	.byte	0x63
	.4byte	.LASF1523
	.byte	0x5
	.byte	0x64
	.4byte	.LASF1524
	.byte	0x5
	.byte	0x67
	.4byte	.LASF1525
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF1526
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF1527
	.byte	0x5
	.byte	0x71
	.4byte	.LASF1528
	.byte	0x5
	.byte	0x72
	.4byte	.LASF1529
	.byte	0x5
	.byte	0x73
	.4byte	.LASF1530
	.byte	0x5
	.byte	0x74
	.4byte	.LASF1531
	.byte	0x5
	.byte	0x75
	.4byte	.LASF1532
	.byte	0x5
	.byte	0x76
	.4byte	.LASF1533
	.byte	0x5
	.byte	0x77
	.4byte	.LASF1534
	.byte	0x5
	.byte	0x78
	.4byte	.LASF1535
	.byte	0x5
	.byte	0x7b
	.4byte	.LASF1536
	.byte	0x5
	.byte	0x7c
	.4byte	.LASF1537
	.byte	0x5
	.byte	0x7d
	.4byte	.LASF1538
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF1539
	.byte	0x5
	.byte	0xa3,0x1
	.4byte	.LASF1540
	.byte	0x5
	.byte	0xa6,0x1
	.4byte	.LASF1541
	.byte	0x5
	.byte	0xa7,0x1
	.4byte	.LASF1542
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF1543
	.byte	0x5
	.byte	0xa9,0x1
	.4byte	.LASF1544
	.byte	0x5
	.byte	0xac,0x1
	.4byte	.LASF1545
	.byte	0x5
	.byte	0xad,0x1
	.4byte	.LASF1546
	.byte	0x5
	.byte	0xb0,0x1
	.4byte	.LASF1547
	.byte	0x5
	.byte	0xb1,0x1
	.4byte	.LASF1548
	.byte	0x5
	.byte	0xb4,0x1
	.4byte	.LASF1549
	.byte	0x5
	.byte	0xb5,0x1
	.4byte	.LASF1550
	.byte	0x5
	.byte	0xb8,0x1
	.4byte	.LASF1551
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF1552
	.byte	0x5
	.byte	0xbd,0x1
	.4byte	.LASF1553
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF1554
	.byte	0x5
	.byte	0xc1,0x1
	.4byte	.LASF1555
	.byte	0x5
	.byte	0xc2,0x1
	.4byte	.LASF1556
	.byte	0x5
	.byte	0xc5,0x1
	.4byte	.LASF1557
	.byte	0x5
	.byte	0xc6,0x1
	.4byte	.LASF1558
	.byte	0x5
	.byte	0xc9,0x1
	.4byte	.LASF1559
	.byte	0x5
	.byte	0xcc,0x1
	.4byte	.LASF1560
	.byte	0x5
	.byte	0xcf,0x1
	.4byte	.LASF1561
	.byte	0x5
	.byte	0xd2,0x1
	.4byte	.LASF1562
	.byte	0x5
	.byte	0xd5,0x1
	.4byte	.LASF1563
	.byte	0x5
	.byte	0xd6,0x1
	.4byte	.LASF1564
	.byte	0x5
	.byte	0xd7,0x1
	.4byte	.LASF1565
	.byte	0x5
	.byte	0xd8,0x1
	.4byte	.LASF1566
	.byte	0x5
	.byte	0xd9,0x1
	.4byte	.LASF1567
	.byte	0x5
	.byte	0xda,0x1
	.4byte	.LASF1568
	.byte	0x5
	.byte	0xdb,0x1
	.4byte	.LASF1569
	.byte	0x5
	.byte	0xdc,0x1
	.4byte	.LASF1570
	.byte	0x5
	.byte	0xdd,0x1
	.4byte	.LASF1571
	.byte	0x5
	.byte	0xde,0x1
	.4byte	.LASF1572
	.byte	0x5
	.byte	0xdf,0x1
	.4byte	.LASF1573
	.byte	0x5
	.byte	0xe0,0x1
	.4byte	.LASF1574
	.byte	0x5
	.byte	0xe1,0x1
	.4byte	.LASF1575
	.byte	0x5
	.byte	0xe2,0x1
	.4byte	.LASF1576
	.byte	0x5
	.byte	0xe3,0x1
	.4byte	.LASF1577
	.byte	0x5
	.byte	0xe4,0x1
	.4byte	.LASF1578
	.byte	0x5
	.byte	0xe5,0x1
	.4byte	.LASF1579
	.byte	0x5
	.byte	0xe6,0x1
	.4byte	.LASF1580
	.byte	0x5
	.byte	0xe7,0x1
	.4byte	.LASF1581
	.byte	0x5
	.byte	0xe8,0x1
	.4byte	.LASF1582
	.byte	0x5
	.byte	0xe9,0x1
	.4byte	.LASF1583
	.byte	0x5
	.byte	0xea,0x1
	.4byte	.LASF1584
	.byte	0x5
	.byte	0xeb,0x1
	.4byte	.LASF1585
	.byte	0x5
	.byte	0xec,0x1
	.4byte	.LASF1586
	.byte	0x5
	.byte	0xed,0x1
	.4byte	.LASF1587
	.byte	0x5
	.byte	0xee,0x1
	.4byte	.LASF1588
	.byte	0x5
	.byte	0xef,0x1
	.4byte	.LASF1589
	.byte	0x5
	.byte	0xf0,0x1
	.4byte	.LASF1590
	.byte	0x5
	.byte	0xf1,0x1
	.4byte	.LASF1591
	.byte	0x5
	.byte	0xf2,0x1
	.4byte	.LASF1592
	.byte	0x5
	.byte	0xf3,0x1
	.4byte	.LASF1593
	.byte	0x5
	.byte	0xf4,0x1
	.4byte	.LASF1594
	.byte	0x5
	.byte	0xf5,0x1
	.4byte	.LASF1595
	.byte	0x5
	.byte	0xf8,0x1
	.4byte	.LASF1596
	.byte	0x5
	.byte	0xfb,0x1
	.4byte	.LASF1597
	.byte	0x5
	.byte	0xfc,0x1
	.4byte	.LASF1598
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_gpio.h.37.1c15e50fe61c140e18cbdcae4553472f,comdat
.Ldebug_macro20:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF1599
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF1600
	.byte	0x5
	.byte	0x2b
	.4byte	.LASF1601
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF1602
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF1603
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF1604
	.byte	0x5
	.byte	0x31
	.4byte	.LASF1605
	.byte	0x5
	.byte	0x36
	.4byte	.LASF1606
	.byte	0x5
	.byte	0x37
	.4byte	.LASF1607
	.byte	0x5
	.byte	0x38
	.4byte	.LASF1608
	.byte	0x5
	.byte	0x39
	.4byte	.LASF1609
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF1610
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF1611
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF1612
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF1613
	.byte	0x5
	.byte	0x40
	.4byte	.LASF1614
	.byte	0x5
	.byte	0x41
	.4byte	.LASF1615
	.byte	0x5
	.byte	0x42
	.4byte	.LASF1616
	.byte	0x5
	.byte	0x43
	.4byte	.LASF1617
	.byte	0x5
	.byte	0x44
	.4byte	.LASF1618
	.byte	0x5
	.byte	0x45
	.4byte	.LASF1619
	.byte	0x5
	.byte	0x49
	.4byte	.LASF1620
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF1621
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF1622
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF1623
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF1624
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF1625
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF1626
	.byte	0x5
	.byte	0x50
	.4byte	.LASF1627
	.byte	0x5
	.byte	0x51
	.4byte	.LASF1628
	.byte	0x5
	.byte	0x52
	.4byte	.LASF1629
	.byte	0x5
	.byte	0x53
	.4byte	.LASF1630
	.byte	0x5
	.byte	0x54
	.4byte	.LASF1631
	.byte	0x5
	.byte	0x55
	.4byte	.LASF1632
	.byte	0x5
	.byte	0x56
	.4byte	.LASF1633
	.byte	0x5
	.byte	0x57
	.4byte	.LASF1634
	.byte	0x5
	.byte	0x58
	.4byte	.LASF1635
	.byte	0x5
	.byte	0x5b
	.4byte	.LASF1636
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF1637
	.byte	0x5
	.byte	0x5d
	.4byte	.LASF1638
	.byte	0x5
	.byte	0x5e
	.4byte	.LASF1639
	.byte	0x5
	.byte	0x5f
	.4byte	.LASF1640
	.byte	0x5
	.byte	0x60
	.4byte	.LASF1641
	.byte	0x5
	.byte	0x61
	.4byte	.LASF1642
	.byte	0x5
	.byte	0x62
	.4byte	.LASF1643
	.byte	0x5
	.byte	0x63
	.4byte	.LASF1644
	.byte	0x5
	.byte	0x64
	.4byte	.LASF1645
	.byte	0x5
	.byte	0x65
	.4byte	.LASF1646
	.byte	0x5
	.byte	0x66
	.4byte	.LASF1647
	.byte	0x5
	.byte	0x67
	.4byte	.LASF1648
	.byte	0x5
	.byte	0x68
	.4byte	.LASF1649
	.byte	0x5
	.byte	0x69
	.4byte	.LASF1650
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF1651
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF1652
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF1653
	.byte	0x5
	.byte	0x6f
	.4byte	.LASF1654
	.byte	0x5
	.byte	0x70
	.4byte	.LASF1655
	.byte	0x5
	.byte	0x71
	.4byte	.LASF1656
	.byte	0x5
	.byte	0x72
	.4byte	.LASF1657
	.byte	0x5
	.byte	0x73
	.4byte	.LASF1658
	.byte	0x5
	.byte	0x74
	.4byte	.LASF1659
	.byte	0x5
	.byte	0x75
	.4byte	.LASF1660
	.byte	0x5
	.byte	0x76
	.4byte	.LASF1661
	.byte	0x5
	.byte	0x77
	.4byte	.LASF1662
	.byte	0x5
	.byte	0x78
	.4byte	.LASF1663
	.byte	0x5
	.byte	0x79
	.4byte	.LASF1664
	.byte	0x5
	.byte	0x7a
	.4byte	.LASF1665
	.byte	0x5
	.byte	0x7b
	.4byte	.LASF1666
	.byte	0x5
	.byte	0x7c
	.4byte	.LASF1667
	.byte	0x5
	.byte	0x7f
	.4byte	.LASF1668
	.byte	0x5
	.byte	0x80,0x1
	.4byte	.LASF1669
	.byte	0x5
	.byte	0x81,0x1
	.4byte	.LASF1670
	.byte	0x5
	.byte	0x82,0x1
	.4byte	.LASF1671
	.byte	0x5
	.byte	0x83,0x1
	.4byte	.LASF1672
	.byte	0x5
	.byte	0x84,0x1
	.4byte	.LASF1673
	.byte	0x5
	.byte	0x85,0x1
	.4byte	.LASF1674
	.byte	0x5
	.byte	0x86,0x1
	.4byte	.LASF1675
	.byte	0x5
	.byte	0x87,0x1
	.4byte	.LASF1676
	.byte	0x5
	.byte	0x88,0x1
	.4byte	.LASF1677
	.byte	0x5
	.byte	0x89,0x1
	.4byte	.LASF1678
	.byte	0x5
	.byte	0x8a,0x1
	.4byte	.LASF1679
	.byte	0x5
	.byte	0x8b,0x1
	.4byte	.LASF1680
	.byte	0x5
	.byte	0x8c,0x1
	.4byte	.LASF1681
	.byte	0x5
	.byte	0x8d,0x1
	.4byte	.LASF1682
	.byte	0x5
	.byte	0x8e,0x1
	.4byte	.LASF1683
	.byte	0x5
	.byte	0x91,0x1
	.4byte	.LASF1684
	.byte	0x5
	.byte	0x92,0x1
	.4byte	.LASF1685
	.byte	0x5
	.byte	0x93,0x1
	.4byte	.LASF1686
	.byte	0x5
	.byte	0x94,0x1
	.4byte	.LASF1687
	.byte	0x5
	.byte	0x95,0x1
	.4byte	.LASF1688
	.byte	0x5
	.byte	0x96,0x1
	.4byte	.LASF1689
	.byte	0x5
	.byte	0x97,0x1
	.4byte	.LASF1690
	.byte	0x5
	.byte	0x98,0x1
	.4byte	.LASF1691
	.byte	0x5
	.byte	0x99,0x1
	.4byte	.LASF1692
	.byte	0x5
	.byte	0x9a,0x1
	.4byte	.LASF1693
	.byte	0x5
	.byte	0x9b,0x1
	.4byte	.LASF1694
	.byte	0x5
	.byte	0x9c,0x1
	.4byte	.LASF1695
	.byte	0x5
	.byte	0x9d,0x1
	.4byte	.LASF1696
	.byte	0x5
	.byte	0x9e,0x1
	.4byte	.LASF1697
	.byte	0x5
	.byte	0x9f,0x1
	.4byte	.LASF1698
	.byte	0x5
	.byte	0xa0,0x1
	.4byte	.LASF1699
	.byte	0x5
	.byte	0xa1,0x1
	.4byte	.LASF1700
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF1701
	.byte	0x5
	.byte	0xa3,0x1
	.4byte	.LASF1702
	.byte	0x5
	.byte	0xa4,0x1
	.4byte	.LASF1703
	.byte	0x5
	.byte	0xa5,0x1
	.4byte	.LASF1704
	.byte	0x5
	.byte	0xa6,0x1
	.4byte	.LASF1705
	.byte	0x5
	.byte	0xa7,0x1
	.4byte	.LASF1706
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF1707
	.byte	0x5
	.byte	0xa9,0x1
	.4byte	.LASF1708
	.byte	0x5
	.byte	0xaa,0x1
	.4byte	.LASF1709
	.byte	0x5
	.byte	0xab,0x1
	.4byte	.LASF1710
	.byte	0x5
	.byte	0xac,0x1
	.4byte	.LASF1711
	.byte	0x5
	.byte	0xad,0x1
	.4byte	.LASF1712
	.byte	0x5
	.byte	0xae,0x1
	.4byte	.LASF1713
	.byte	0x5
	.byte	0xaf,0x1
	.4byte	.LASF1714
	.byte	0x5
	.byte	0xb0,0x1
	.4byte	.LASF1715
	.byte	0x5
	.byte	0xb3,0x1
	.4byte	.LASF1716
	.byte	0x5
	.byte	0xb4,0x1
	.4byte	.LASF1717
	.byte	0x5
	.byte	0xb5,0x1
	.4byte	.LASF1718
	.byte	0x5
	.byte	0xb6,0x1
	.4byte	.LASF1719
	.byte	0x5
	.byte	0xb7,0x1
	.4byte	.LASF1720
	.byte	0x5
	.byte	0xb8,0x1
	.4byte	.LASF1721
	.byte	0x5
	.byte	0xb9,0x1
	.4byte	.LASF1722
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF1723
	.byte	0x5
	.byte	0xbb,0x1
	.4byte	.LASF1724
	.byte	0x5
	.byte	0xbc,0x1
	.4byte	.LASF1725
	.byte	0x5
	.byte	0xbd,0x1
	.4byte	.LASF1726
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF1727
	.byte	0x5
	.byte	0xbf,0x1
	.4byte	.LASF1728
	.byte	0x5
	.byte	0xc0,0x1
	.4byte	.LASF1729
	.byte	0x5
	.byte	0xc1,0x1
	.4byte	.LASF1730
	.byte	0x5
	.byte	0xc2,0x1
	.4byte	.LASF1731
	.byte	0x5
	.byte	0xc5,0x1
	.4byte	.LASF1732
	.byte	0x5
	.byte	0xc6,0x1
	.4byte	.LASF1733
	.byte	0x5
	.byte	0xc7,0x1
	.4byte	.LASF1734
	.byte	0x5
	.byte	0xc8,0x1
	.4byte	.LASF1735
	.byte	0x5
	.byte	0xc9,0x1
	.4byte	.LASF1736
	.byte	0x5
	.byte	0xca,0x1
	.4byte	.LASF1737
	.byte	0x5
	.byte	0xcb,0x1
	.4byte	.LASF1738
	.byte	0x5
	.byte	0xcc,0x1
	.4byte	.LASF1739
	.byte	0x5
	.byte	0xcd,0x1
	.4byte	.LASF1740
	.byte	0x5
	.byte	0xce,0x1
	.4byte	.LASF1741
	.byte	0x5
	.byte	0xcf,0x1
	.4byte	.LASF1742
	.byte	0x5
	.byte	0xd0,0x1
	.4byte	.LASF1743
	.byte	0x5
	.byte	0xd1,0x1
	.4byte	.LASF1744
	.byte	0x5
	.byte	0xd2,0x1
	.4byte	.LASF1745
	.byte	0x5
	.byte	0xd3,0x1
	.4byte	.LASF1746
	.byte	0x5
	.byte	0xd4,0x1
	.4byte	.LASF1747
	.byte	0x5
	.byte	0xd5,0x1
	.4byte	.LASF1748
	.byte	0x5
	.byte	0xd8,0x1
	.4byte	.LASF1749
	.byte	0x5
	.byte	0xd9,0x1
	.4byte	.LASF1750
	.byte	0x5
	.byte	0xda,0x1
	.4byte	.LASF1751
	.byte	0x5
	.byte	0xdd,0x1
	.4byte	.LASF1752
	.byte	0x5
	.byte	0xde,0x1
	.4byte	.LASF1753
	.byte	0x5
	.byte	0xdf,0x1
	.4byte	.LASF1754
	.byte	0x5
	.byte	0xe0,0x1
	.4byte	.LASF1755
	.byte	0x5
	.byte	0xe1,0x1
	.4byte	.LASF1756
	.byte	0x5
	.byte	0xe2,0x1
	.4byte	.LASF1757
	.byte	0x5
	.byte	0xe3,0x1
	.4byte	.LASF1758
	.byte	0x5
	.byte	0xe4,0x1
	.4byte	.LASF1759
	.byte	0x5
	.byte	0xe5,0x1
	.4byte	.LASF1760
	.byte	0x5
	.byte	0xe6,0x1
	.4byte	.LASF1761
	.byte	0x5
	.byte	0xe7,0x1
	.4byte	.LASF1762
	.byte	0x5
	.byte	0xe8,0x1
	.4byte	.LASF1763
	.byte	0x5
	.byte	0xe9,0x1
	.4byte	.LASF1764
	.byte	0x5
	.byte	0xea,0x1
	.4byte	.LASF1765
	.byte	0x5
	.byte	0xeb,0x1
	.4byte	.LASF1766
	.byte	0x5
	.byte	0xee,0x1
	.4byte	.LASF1767
	.byte	0x5
	.byte	0xef,0x1
	.4byte	.LASF1768
	.byte	0x5
	.byte	0xf0,0x1
	.4byte	.LASF1769
	.byte	0x5
	.byte	0xf1,0x1
	.4byte	.LASF1770
	.byte	0x5
	.byte	0xf4,0x1
	.4byte	.LASF1771
	.byte	0x5
	.byte	0xf5,0x1
	.4byte	.LASF1772
	.byte	0x5
	.byte	0xf6,0x1
	.4byte	.LASF1773
	.byte	0x5
	.byte	0xf7,0x1
	.4byte	.LASF1774
	.byte	0x5
	.byte	0xfa,0x1
	.4byte	.LASF1775
	.byte	0x5
	.byte	0xfb,0x1
	.4byte	.LASF1776
	.byte	0x5
	.byte	0xfc,0x1
	.4byte	.LASF1777
	.byte	0x5
	.byte	0xfd,0x1
	.4byte	.LASF1778
	.byte	0x5
	.byte	0x80,0x2
	.4byte	.LASF1779
	.byte	0x5
	.byte	0x81,0x2
	.4byte	.LASF1780
	.byte	0x5
	.byte	0x82,0x2
	.4byte	.LASF1781
	.byte	0x5
	.byte	0x83,0x2
	.4byte	.LASF1782
	.byte	0x5
	.byte	0x86,0x2
	.4byte	.LASF1783
	.byte	0x5
	.byte	0x8c,0x2
	.4byte	.LASF1784
	.byte	0x5
	.byte	0x8d,0x2
	.4byte	.LASF1785
	.byte	0x5
	.byte	0x90,0x2
	.4byte	.LASF1786
	.byte	0x5
	.byte	0x91,0x2
	.4byte	.LASF1787
	.byte	0x5
	.byte	0x92,0x2
	.4byte	.LASF1788
	.byte	0x5
	.byte	0x93,0x2
	.4byte	.LASF1789
	.byte	0x5
	.byte	0x94,0x2
	.4byte	.LASF1790
	.byte	0x5
	.byte	0x95,0x2
	.4byte	.LASF1791
	.byte	0x5
	.byte	0x96,0x2
	.4byte	.LASF1792
	.byte	0x5
	.byte	0x97,0x2
	.4byte	.LASF1793
	.byte	0x5
	.byte	0x9a,0x2
	.4byte	.LASF1794
	.byte	0x5
	.byte	0x9b,0x2
	.4byte	.LASF1795
	.byte	0x5
	.byte	0x9c,0x2
	.4byte	.LASF1796
	.byte	0x5
	.byte	0x9f,0x2
	.4byte	.LASF1797
	.byte	0x5
	.byte	0xa0,0x2
	.4byte	.LASF1798
	.byte	0x5
	.byte	0xa1,0x2
	.4byte	.LASF1799
	.byte	0x5
	.byte	0xa2,0x2
	.4byte	.LASF1800
	.byte	0x5
	.byte	0xa3,0x2
	.4byte	.LASF1801
	.byte	0x5
	.byte	0xa6,0x2
	.4byte	.LASF1802
	.byte	0x5
	.byte	0xa7,0x2
	.4byte	.LASF1803
	.byte	0x5
	.byte	0xa8,0x2
	.4byte	.LASF1804
	.byte	0x5
	.byte	0xa9,0x2
	.4byte	.LASF1805
	.byte	0x5
	.byte	0xaa,0x2
	.4byte	.LASF1806
	.byte	0x5
	.byte	0xad,0x2
	.4byte	.LASF1807
	.byte	0x5
	.byte	0xae,0x2
	.4byte	.LASF1808
	.byte	0x5
	.byte	0xaf,0x2
	.4byte	.LASF1809
	.byte	0x5
	.byte	0xb0,0x2
	.4byte	.LASF1810
	.byte	0x5
	.byte	0xb1,0x2
	.4byte	.LASF1811
	.byte	0x5
	.byte	0xb2,0x2
	.4byte	.LASF1812
	.byte	0x5
	.byte	0xb3,0x2
	.4byte	.LASF1813
	.byte	0x5
	.byte	0xb4,0x2
	.4byte	.LASF1814
	.byte	0x5
	.byte	0xb5,0x2
	.4byte	.LASF1815
	.byte	0x5
	.byte	0xb6,0x2
	.4byte	.LASF1816
	.byte	0x5
	.byte	0xb7,0x2
	.4byte	.LASF1817
	.byte	0x5
	.byte	0xb8,0x2
	.4byte	.LASF1818
	.byte	0x5
	.byte	0xb9,0x2
	.4byte	.LASF1819
	.byte	0x5
	.byte	0xba,0x2
	.4byte	.LASF1820
	.byte	0x5
	.byte	0xbb,0x2
	.4byte	.LASF1821
	.byte	0x5
	.byte	0xbc,0x2
	.4byte	.LASF1822
	.byte	0x5
	.byte	0xbf,0x2
	.4byte	.LASF1823
	.byte	0x5
	.byte	0xc0,0x2
	.4byte	.LASF1824
	.byte	0x5
	.byte	0xc1,0x2
	.4byte	.LASF1825
	.byte	0x5
	.byte	0xc2,0x2
	.4byte	.LASF1826
	.byte	0x5
	.byte	0xc3,0x2
	.4byte	.LASF1827
	.byte	0x5
	.byte	0xc4,0x2
	.4byte	.LASF1828
	.byte	0x5
	.byte	0xc5,0x2
	.4byte	.LASF1829
	.byte	0x5
	.byte	0xc6,0x2
	.4byte	.LASF1830
	.byte	0x5
	.byte	0xc7,0x2
	.4byte	.LASF1831
	.byte	0x5
	.byte	0xc8,0x2
	.4byte	.LASF1832
	.byte	0x5
	.byte	0xc9,0x2
	.4byte	.LASF1833
	.byte	0x5
	.byte	0xca,0x2
	.4byte	.LASF1834
	.byte	0x5
	.byte	0xcb,0x2
	.4byte	.LASF1835
	.byte	0x5
	.byte	0xcc,0x2
	.4byte	.LASF1836
	.byte	0x5
	.byte	0xcd,0x2
	.4byte	.LASF1837
	.byte	0x5
	.byte	0xce,0x2
	.4byte	.LASF1838
	.byte	0x5
	.byte	0xd1,0x2
	.4byte	.LASF1839
	.byte	0x5
	.byte	0xd2,0x2
	.4byte	.LASF1840
	.byte	0x5
	.byte	0xd3,0x2
	.4byte	.LASF1841
	.byte	0x5
	.byte	0xd4,0x2
	.4byte	.LASF1842
	.byte	0x5
	.byte	0xd5,0x2
	.4byte	.LASF1843
	.byte	0x5
	.byte	0xd6,0x2
	.4byte	.LASF1844
	.byte	0x5
	.byte	0xd7,0x2
	.4byte	.LASF1845
	.byte	0x5
	.byte	0xd8,0x2
	.4byte	.LASF1846
	.byte	0x5
	.byte	0xd9,0x2
	.4byte	.LASF1847
	.byte	0x5
	.byte	0xda,0x2
	.4byte	.LASF1848
	.byte	0x5
	.byte	0xdb,0x2
	.4byte	.LASF1849
	.byte	0x5
	.byte	0xdc,0x2
	.4byte	.LASF1850
	.byte	0x5
	.byte	0xdd,0x2
	.4byte	.LASF1851
	.byte	0x5
	.byte	0xde,0x2
	.4byte	.LASF1852
	.byte	0x5
	.byte	0xdf,0x2
	.4byte	.LASF1853
	.byte	0x5
	.byte	0xe0,0x2
	.4byte	.LASF1854
	.byte	0x5
	.byte	0xe1,0x2
	.4byte	.LASF1855
	.byte	0x5
	.byte	0xe4,0x2
	.4byte	.LASF1856
	.byte	0x5
	.byte	0xe5,0x2
	.4byte	.LASF1857
	.byte	0x5
	.byte	0xe6,0x2
	.4byte	.LASF1858
	.byte	0x5
	.byte	0xe7,0x2
	.4byte	.LASF1859
	.byte	0x5
	.byte	0xe8,0x2
	.4byte	.LASF1860
	.byte	0x5
	.byte	0xe9,0x2
	.4byte	.LASF1861
	.byte	0x5
	.byte	0xea,0x2
	.4byte	.LASF1862
	.byte	0x5
	.byte	0xeb,0x2
	.4byte	.LASF1863
	.byte	0x5
	.byte	0xec,0x2
	.4byte	.LASF1864
	.byte	0x5
	.byte	0xed,0x2
	.4byte	.LASF1865
	.byte	0x5
	.byte	0xee,0x2
	.4byte	.LASF1866
	.byte	0x5
	.byte	0xef,0x2
	.4byte	.LASF1867
	.byte	0x5
	.byte	0xf0,0x2
	.4byte	.LASF1868
	.byte	0x5
	.byte	0xf1,0x2
	.4byte	.LASF1869
	.byte	0x5
	.byte	0xf2,0x2
	.4byte	.LASF1870
	.byte	0x5
	.byte	0xf3,0x2
	.4byte	.LASF1871
	.byte	0x5
	.byte	0xf4,0x2
	.4byte	.LASF1872
	.byte	0x5
	.byte	0xf5,0x2
	.4byte	.LASF1873
	.byte	0x5
	.byte	0xf6,0x2
	.4byte	.LASF1874
	.byte	0x5
	.byte	0xf7,0x2
	.4byte	.LASF1875
	.byte	0x5
	.byte	0xf8,0x2
	.4byte	.LASF1876
	.byte	0x5
	.byte	0xf9,0x2
	.4byte	.LASF1877
	.byte	0x5
	.byte	0xfa,0x2
	.4byte	.LASF1878
	.byte	0x5
	.byte	0xfb,0x2
	.4byte	.LASF1879
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_i2c.h.37.9d7fb50529db8c5d4a0b10c3b5a1de79,comdat
.Ldebug_macro21:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF1880
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF1881
	.byte	0x5
	.byte	0x2b
	.4byte	.LASF1882
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF1883
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF1884
	.byte	0x5
	.byte	0x30
	.4byte	.LASF1885
	.byte	0x5
	.byte	0x31
	.4byte	.LASF1886
	.byte	0x5
	.byte	0x32
	.4byte	.LASF1887
	.byte	0x5
	.byte	0x33
	.4byte	.LASF1888
	.byte	0x5
	.byte	0x34
	.4byte	.LASF1889
	.byte	0x5
	.byte	0x35
	.4byte	.LASF1890
	.byte	0x5
	.byte	0x36
	.4byte	.LASF1891
	.byte	0x5
	.byte	0x37
	.4byte	.LASF1892
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF1893
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF1894
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF1895
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF1896
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF1897
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF1898
	.byte	0x5
	.byte	0x40
	.4byte	.LASF1899
	.byte	0x5
	.byte	0x41
	.4byte	.LASF1900
	.byte	0x5
	.byte	0x42
	.4byte	.LASF1901
	.byte	0x5
	.byte	0x43
	.4byte	.LASF1902
	.byte	0x5
	.byte	0x44
	.4byte	.LASF1903
	.byte	0x5
	.byte	0x45
	.4byte	.LASF1904
	.byte	0x5
	.byte	0x46
	.4byte	.LASF1905
	.byte	0x5
	.byte	0x47
	.4byte	.LASF1906
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF1907
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF1908
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF1909
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF1910
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF1911
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF1912
	.byte	0x5
	.byte	0x52
	.4byte	.LASF1913
	.byte	0x5
	.byte	0x53
	.4byte	.LASF1914
	.byte	0x5
	.byte	0x54
	.4byte	.LASF1915
	.byte	0x5
	.byte	0x55
	.4byte	.LASF1916
	.byte	0x5
	.byte	0x58
	.4byte	.LASF1917
	.byte	0x5
	.byte	0x59
	.4byte	.LASF1918
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF1919
	.byte	0x5
	.byte	0x5f
	.4byte	.LASF1920
	.byte	0x5
	.byte	0x60
	.4byte	.LASF1921
	.byte	0x5
	.byte	0x61
	.4byte	.LASF1922
	.byte	0x5
	.byte	0x62
	.4byte	.LASF1923
	.byte	0x5
	.byte	0x63
	.4byte	.LASF1924
	.byte	0x5
	.byte	0x64
	.4byte	.LASF1925
	.byte	0x5
	.byte	0x65
	.4byte	.LASF1926
	.byte	0x5
	.byte	0x66
	.4byte	.LASF1927
	.byte	0x5
	.byte	0x67
	.4byte	.LASF1928
	.byte	0x5
	.byte	0x68
	.4byte	.LASF1929
	.byte	0x5
	.byte	0x69
	.4byte	.LASF1930
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF1931
	.byte	0x5
	.byte	0x6b
	.4byte	.LASF1932
	.byte	0x5
	.byte	0x6c
	.4byte	.LASF1933
	.byte	0x5
	.byte	0x6f
	.4byte	.LASF1934
	.byte	0x5
	.byte	0x70
	.4byte	.LASF1935
	.byte	0x5
	.byte	0x71
	.4byte	.LASF1936
	.byte	0x5
	.byte	0x72
	.4byte	.LASF1937
	.byte	0x5
	.byte	0x73
	.4byte	.LASF1938
	.byte	0x5
	.byte	0x74
	.4byte	.LASF1939
	.byte	0x5
	.byte	0x75
	.4byte	.LASF1940
	.byte	0x5
	.byte	0x76
	.4byte	.LASF1941
	.byte	0x5
	.byte	0x79
	.4byte	.LASF1942
	.byte	0x5
	.byte	0x7a
	.4byte	.LASF1943
	.byte	0x5
	.byte	0x7b
	.4byte	.LASF1944
	.byte	0x5
	.byte	0x7e
	.4byte	.LASF1945
	.byte	0x5
	.byte	0x81,0x1
	.4byte	.LASF1946
	.byte	0x5
	.byte	0x85,0x1
	.4byte	.LASF1947
	.byte	0x5
	.byte	0x86,0x1
	.4byte	.LASF1948
	.byte	0x5
	.byte	0x87,0x1
	.4byte	.LASF1949
	.byte	0x5
	.byte	0x88,0x1
	.4byte	.LASF1950
	.byte	0x5
	.byte	0x8a,0x1
	.4byte	.LASF1951
	.byte	0x5
	.byte	0x8b,0x1
	.4byte	.LASF1952
	.byte	0x5
	.byte	0x8e,0x1
	.4byte	.LASF1953
	.byte	0x5
	.byte	0x8f,0x1
	.4byte	.LASF1954
	.byte	0x5
	.byte	0x90,0x1
	.4byte	.LASF1955
	.byte	0x5
	.byte	0xc9,0x1
	.4byte	.LASF1956
	.byte	0x5
	.byte	0xca,0x1
	.4byte	.LASF1957
	.byte	0x5
	.byte	0xcd,0x1
	.4byte	.LASF1958
	.byte	0x5
	.byte	0xce,0x1
	.4byte	.LASF1959
	.byte	0x5
	.byte	0xd1,0x1
	.4byte	.LASF1960
	.byte	0x5
	.byte	0xd2,0x1
	.4byte	.LASF1961
	.byte	0x5
	.byte	0xd5,0x1
	.4byte	.LASF1962
	.byte	0x5
	.byte	0xd6,0x1
	.4byte	.LASF1963
	.byte	0x5
	.byte	0xd9,0x1
	.4byte	.LASF1964
	.byte	0x5
	.byte	0xda,0x1
	.4byte	.LASF1965
	.byte	0x5
	.byte	0xdd,0x1
	.4byte	.LASF1966
	.byte	0x5
	.byte	0xde,0x1
	.4byte	.LASF1967
	.byte	0x5
	.byte	0xe1,0x1
	.4byte	.LASF1968
	.byte	0x5
	.byte	0xe2,0x1
	.4byte	.LASF1969
	.byte	0x5
	.byte	0xe5,0x1
	.4byte	.LASF1970
	.byte	0x5
	.byte	0xe6,0x1
	.4byte	.LASF1971
	.byte	0x5
	.byte	0xe9,0x1
	.4byte	.LASF1972
	.byte	0x5
	.byte	0xea,0x1
	.4byte	.LASF1973
	.byte	0x5
	.byte	0xee,0x1
	.4byte	.LASF1974
	.byte	0x5
	.byte	0xef,0x1
	.4byte	.LASF1975
	.byte	0x5
	.byte	0xf2,0x1
	.4byte	.LASF1976
	.byte	0x5
	.byte	0xf3,0x1
	.4byte	.LASF1977
	.byte	0x5
	.byte	0xf7,0x1
	.4byte	.LASF1978
	.byte	0x5
	.byte	0xf8,0x1
	.4byte	.LASF1979
	.byte	0x5
	.byte	0xfb,0x1
	.4byte	.LASF1980
	.byte	0x5
	.byte	0xfc,0x1
	.4byte	.LASF1981
	.byte	0x5
	.byte	0x80,0x2
	.4byte	.LASF1982
	.byte	0x5
	.byte	0x81,0x2
	.4byte	.LASF1983
	.byte	0x5
	.byte	0x84,0x2
	.4byte	.LASF1984
	.byte	0x5
	.byte	0x85,0x2
	.4byte	.LASF1985
	.byte	0x5
	.byte	0x88,0x2
	.4byte	.LASF1986
	.byte	0x5
	.byte	0x8b,0x2
	.4byte	.LASF1987
	.byte	0x5
	.byte	0x8e,0x2
	.4byte	.LASF1988
	.byte	0x5
	.byte	0x8f,0x2
	.4byte	.LASF1989
	.byte	0x5
	.byte	0x92,0x2
	.4byte	.LASF1990
	.byte	0x5
	.byte	0x93,0x2
	.4byte	.LASF1991
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_fwdgt.h.37.ec91e2ec679929e46ec494cd499250b4,comdat
.Ldebug_macro22:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF1992
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF1993
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF1994
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF1995
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF1996
	.byte	0x5
	.byte	0x30
	.4byte	.LASF1997
	.byte	0x5
	.byte	0x34
	.4byte	.LASF1998
	.byte	0x5
	.byte	0x37
	.4byte	.LASF1999
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF2000
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF2001
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF2002
	.byte	0x5
	.byte	0x42
	.4byte	.LASF2003
	.byte	0x5
	.byte	0x43
	.4byte	.LASF2004
	.byte	0x5
	.byte	0x44
	.4byte	.LASF2005
	.byte	0x5
	.byte	0x45
	.4byte	.LASF2006
	.byte	0x5
	.byte	0x46
	.4byte	.LASF2007
	.byte	0x5
	.byte	0x47
	.4byte	.LASF2008
	.byte	0x5
	.byte	0x48
	.4byte	.LASF2009
	.byte	0x5
	.byte	0x49
	.4byte	.LASF2010
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF2011
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF2012
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF2013
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF2014
	.byte	0x5
	.byte	0x52
	.4byte	.LASF2015
	.byte	0x5
	.byte	0x53
	.4byte	.LASF2016
	.byte	0x5
	.byte	0x56
	.4byte	.LASF2017
	.byte	0x5
	.byte	0x57
	.4byte	.LASF2018
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_dbg.h.37.c757ea48294705efe800a8cbb43f6f24,comdat
.Ldebug_macro23:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF2019
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF2020
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF2021
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF2022
	.byte	0x5
	.byte	0x32
	.4byte	.LASF2023
	.byte	0x5
	.byte	0x35
	.4byte	.LASF2024
	.byte	0x5
	.byte	0x36
	.4byte	.LASF2025
	.byte	0x5
	.byte	0x37
	.4byte	.LASF2026
	.byte	0x5
	.byte	0x38
	.4byte	.LASF2027
	.byte	0x5
	.byte	0x39
	.4byte	.LASF2028
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF2029
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF2030
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF2031
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF2032
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF2033
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF2034
	.byte	0x5
	.byte	0x40
	.4byte	.LASF2035
	.byte	0x5
	.byte	0x41
	.4byte	.LASF2036
	.byte	0x5
	.byte	0x42
	.4byte	.LASF2037
	.byte	0x5
	.byte	0x43
	.4byte	.LASF2038
	.byte	0x5
	.byte	0x44
	.4byte	.LASF2039
	.byte	0x5
	.byte	0x5a
	.4byte	.LASF2040
	.byte	0x5
	.byte	0x5b
	.4byte	.LASF2041
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF2042
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_pmu.h.37.edf842f53f3092f282c7bccaf9512833,comdat
.Ldebug_macro24:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF2043
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF2044
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF2045
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF2046
	.byte	0x5
	.byte	0x32
	.4byte	.LASF2047
	.byte	0x5
	.byte	0x33
	.4byte	.LASF2048
	.byte	0x5
	.byte	0x34
	.4byte	.LASF2049
	.byte	0x5
	.byte	0x35
	.4byte	.LASF2050
	.byte	0x5
	.byte	0x36
	.4byte	.LASF2051
	.byte	0x5
	.byte	0x37
	.4byte	.LASF2052
	.byte	0x5
	.byte	0x38
	.4byte	.LASF2053
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF2054
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF2055
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF2056
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF2057
	.byte	0x5
	.byte	0x42
	.4byte	.LASF2058
	.byte	0x5
	.byte	0x43
	.4byte	.LASF2059
	.byte	0x5
	.byte	0x44
	.4byte	.LASF2060
	.byte	0x5
	.byte	0x45
	.4byte	.LASF2061
	.byte	0x5
	.byte	0x46
	.4byte	.LASF2062
	.byte	0x5
	.byte	0x47
	.4byte	.LASF2063
	.byte	0x5
	.byte	0x48
	.4byte	.LASF2064
	.byte	0x5
	.byte	0x49
	.4byte	.LASF2065
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF2066
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF2067
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF2068
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF2069
	.byte	0x5
	.byte	0x52
	.4byte	.LASF2070
	.byte	0x5
	.byte	0x53
	.4byte	.LASF2071
	.byte	0x5
	.byte	0x56
	.4byte	.LASF2072
	.byte	0x5
	.byte	0x57
	.4byte	.LASF2073
	.byte	0x5
	.byte	0x5a
	.4byte	.LASF2074
	.byte	0x5
	.byte	0x5b
	.4byte	.LASF2075
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_rtc.h.37.3521dc979060c1ebaf2d43fd52b94dac,comdat
.Ldebug_macro25:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF2076
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF2077
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF2078
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF2079
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF2080
	.byte	0x5
	.byte	0x30
	.4byte	.LASF2081
	.byte	0x5
	.byte	0x31
	.4byte	.LASF2082
	.byte	0x5
	.byte	0x32
	.4byte	.LASF2083
	.byte	0x5
	.byte	0x33
	.4byte	.LASF2084
	.byte	0x5
	.byte	0x34
	.4byte	.LASF2085
	.byte	0x5
	.byte	0x35
	.4byte	.LASF2086
	.byte	0x5
	.byte	0x36
	.4byte	.LASF2087
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF2088
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF2089
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF2090
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF2091
	.byte	0x5
	.byte	0x40
	.4byte	.LASF2092
	.byte	0x5
	.byte	0x41
	.4byte	.LASF2093
	.byte	0x5
	.byte	0x42
	.4byte	.LASF2094
	.byte	0x5
	.byte	0x43
	.4byte	.LASF2095
	.byte	0x5
	.byte	0x44
	.4byte	.LASF2096
	.byte	0x5
	.byte	0x47
	.4byte	.LASF2097
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF2098
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF2099
	.byte	0x5
	.byte	0x50
	.4byte	.LASF2100
	.byte	0x5
	.byte	0x53
	.4byte	.LASF2101
	.byte	0x5
	.byte	0x56
	.4byte	.LASF2102
	.byte	0x5
	.byte	0x59
	.4byte	.LASF2103
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF2104
	.byte	0x5
	.byte	0x60
	.4byte	.LASF2105
	.byte	0x5
	.byte	0x61
	.4byte	.LASF2106
	.byte	0x5
	.byte	0x62
	.4byte	.LASF2107
	.byte	0x5
	.byte	0x65
	.4byte	.LASF2108
	.byte	0x5
	.byte	0x66
	.4byte	.LASF2109
	.byte	0x5
	.byte	0x67
	.4byte	.LASF2110
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF2111
	.byte	0x5
	.byte	0x6b
	.4byte	.LASF2112
	.byte	0x5
	.byte	0x6c
	.4byte	.LASF2113
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF2114
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF2115
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_spi.h.37.5b2da83109360bb35c1791b7dcc5009b,comdat
.Ldebug_macro26:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF2116
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF2117
	.byte	0x5
	.byte	0x2b
	.4byte	.LASF2118
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF2119
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF2120
	.byte	0x5
	.byte	0x30
	.4byte	.LASF2121
	.byte	0x5
	.byte	0x31
	.4byte	.LASF2122
	.byte	0x5
	.byte	0x32
	.4byte	.LASF2123
	.byte	0x5
	.byte	0x33
	.4byte	.LASF2124
	.byte	0x5
	.byte	0x34
	.4byte	.LASF2125
	.byte	0x5
	.byte	0x35
	.4byte	.LASF2126
	.byte	0x5
	.byte	0x36
	.4byte	.LASF2127
	.byte	0x5
	.byte	0x37
	.4byte	.LASF2128
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF2129
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF2130
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF2131
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF2132
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF2133
	.byte	0x5
	.byte	0x40
	.4byte	.LASF2134
	.byte	0x5
	.byte	0x41
	.4byte	.LASF2135
	.byte	0x5
	.byte	0x42
	.4byte	.LASF2136
	.byte	0x5
	.byte	0x43
	.4byte	.LASF2137
	.byte	0x5
	.byte	0x44
	.4byte	.LASF2138
	.byte	0x5
	.byte	0x45
	.4byte	.LASF2139
	.byte	0x5
	.byte	0x46
	.4byte	.LASF2140
	.byte	0x5
	.byte	0x47
	.4byte	.LASF2141
	.byte	0x5
	.byte	0x48
	.4byte	.LASF2142
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF2143
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF2144
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF2145
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF2146
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF2147
	.byte	0x5
	.byte	0x50
	.4byte	.LASF2148
	.byte	0x5
	.byte	0x51
	.4byte	.LASF2149
	.byte	0x5
	.byte	0x52
	.4byte	.LASF2150
	.byte	0x5
	.byte	0x55
	.4byte	.LASF2151
	.byte	0x5
	.byte	0x56
	.4byte	.LASF2152
	.byte	0x5
	.byte	0x57
	.4byte	.LASF2153
	.byte	0x5
	.byte	0x58
	.4byte	.LASF2154
	.byte	0x5
	.byte	0x59
	.4byte	.LASF2155
	.byte	0x5
	.byte	0x5a
	.4byte	.LASF2156
	.byte	0x5
	.byte	0x5b
	.4byte	.LASF2157
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF2158
	.byte	0x5
	.byte	0x5d
	.4byte	.LASF2159
	.byte	0x5
	.byte	0x60
	.4byte	.LASF2160
	.byte	0x5
	.byte	0x63
	.4byte	.LASF2161
	.byte	0x5
	.byte	0x66
	.4byte	.LASF2162
	.byte	0x5
	.byte	0x69
	.4byte	.LASF2163
	.byte	0x5
	.byte	0x6c
	.4byte	.LASF2164
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF2165
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF2166
	.byte	0x5
	.byte	0x6f
	.4byte	.LASF2167
	.byte	0x5
	.byte	0x70
	.4byte	.LASF2168
	.byte	0x5
	.byte	0x71
	.4byte	.LASF2169
	.byte	0x5
	.byte	0x72
	.4byte	.LASF2170
	.byte	0x5
	.byte	0x73
	.4byte	.LASF2171
	.byte	0x5
	.byte	0x76
	.4byte	.LASF2172
	.byte	0x5
	.byte	0x77
	.4byte	.LASF2173
	.byte	0x5
	.byte	0x78
	.4byte	.LASF2174
	.byte	0x5
	.byte	0x88,0x1
	.4byte	.LASF2175
	.byte	0x5
	.byte	0x89,0x1
	.4byte	.LASF2176
	.byte	0x5
	.byte	0x8c,0x1
	.4byte	.LASF2177
	.byte	0x5
	.byte	0x8d,0x1
	.4byte	.LASF2178
	.byte	0x5
	.byte	0x90,0x1
	.4byte	.LASF2179
	.byte	0x5
	.byte	0x91,0x1
	.4byte	.LASF2180
	.byte	0x5
	.byte	0x92,0x1
	.4byte	.LASF2181
	.byte	0x5
	.byte	0x93,0x1
	.4byte	.LASF2182
	.byte	0x5
	.byte	0x96,0x1
	.4byte	.LASF2183
	.byte	0x5
	.byte	0x97,0x1
	.4byte	.LASF2184
	.byte	0x5
	.byte	0x9a,0x1
	.4byte	.LASF2185
	.byte	0x5
	.byte	0x9b,0x1
	.4byte	.LASF2186
	.byte	0x5
	.byte	0x9e,0x1
	.4byte	.LASF2187
	.byte	0x5
	.byte	0x9f,0x1
	.4byte	.LASF2188
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF2189
	.byte	0x5
	.byte	0xa3,0x1
	.4byte	.LASF2190
	.byte	0x5
	.byte	0xa4,0x1
	.4byte	.LASF2191
	.byte	0x5
	.byte	0xa5,0x1
	.4byte	.LASF2192
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF2193
	.byte	0x5
	.byte	0xa9,0x1
	.4byte	.LASF2194
	.byte	0x5
	.byte	0xaa,0x1
	.4byte	.LASF2195
	.byte	0x5
	.byte	0xab,0x1
	.4byte	.LASF2196
	.byte	0x5
	.byte	0xac,0x1
	.4byte	.LASF2197
	.byte	0x5
	.byte	0xad,0x1
	.4byte	.LASF2198
	.byte	0x5
	.byte	0xae,0x1
	.4byte	.LASF2199
	.byte	0x5
	.byte	0xaf,0x1
	.4byte	.LASF2200
	.byte	0x5
	.byte	0xb0,0x1
	.4byte	.LASF2201
	.byte	0x5
	.byte	0xb3,0x1
	.4byte	.LASF2202
	.byte	0x5
	.byte	0xb4,0x1
	.4byte	.LASF2203
	.byte	0x5
	.byte	0xb5,0x1
	.4byte	.LASF2204
	.byte	0x5
	.byte	0xb6,0x1
	.4byte	.LASF2205
	.byte	0x5
	.byte	0xb7,0x1
	.4byte	.LASF2206
	.byte	0x5
	.byte	0xb8,0x1
	.4byte	.LASF2207
	.byte	0x5
	.byte	0xb9,0x1
	.4byte	.LASF2208
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF2209
	.byte	0x5
	.byte	0xbb,0x1
	.4byte	.LASF2210
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF2211
	.byte	0x5
	.byte	0xbf,0x1
	.4byte	.LASF2212
	.byte	0x5
	.byte	0xc0,0x1
	.4byte	.LASF2213
	.byte	0x5
	.byte	0xc1,0x1
	.4byte	.LASF2214
	.byte	0x5
	.byte	0xc2,0x1
	.4byte	.LASF2215
	.byte	0x5
	.byte	0xc5,0x1
	.4byte	.LASF2216
	.byte	0x5
	.byte	0xc6,0x1
	.4byte	.LASF2217
	.byte	0x5
	.byte	0xc9,0x1
	.4byte	.LASF2218
	.byte	0x5
	.byte	0xca,0x1
	.4byte	.LASF2219
	.byte	0x5
	.byte	0xcb,0x1
	.4byte	.LASF2220
	.byte	0x5
	.byte	0xcc,0x1
	.4byte	.LASF2221
	.byte	0x5
	.byte	0xcd,0x1
	.4byte	.LASF2222
	.byte	0x5
	.byte	0xd0,0x1
	.4byte	.LASF2223
	.byte	0x5
	.byte	0xd1,0x1
	.4byte	.LASF2224
	.byte	0x5
	.byte	0xd2,0x1
	.4byte	.LASF2225
	.byte	0x5
	.byte	0xd3,0x1
	.4byte	.LASF2226
	.byte	0x5
	.byte	0xd4,0x1
	.4byte	.LASF2227
	.byte	0x5
	.byte	0xd5,0x1
	.4byte	.LASF2228
	.byte	0x5
	.byte	0xd8,0x1
	.4byte	.LASF2229
	.byte	0x5
	.byte	0xd9,0x1
	.4byte	.LASF2230
	.byte	0x5
	.byte	0xdc,0x1
	.4byte	.LASF2231
	.byte	0x5
	.byte	0xdd,0x1
	.4byte	.LASF2232
	.byte	0x5
	.byte	0xe0,0x1
	.4byte	.LASF2233
	.byte	0x5
	.byte	0xe1,0x1
	.4byte	.LASF2234
	.byte	0x5
	.byte	0xe4,0x1
	.4byte	.LASF2235
	.byte	0x5
	.byte	0xe5,0x1
	.4byte	.LASF2236
	.byte	0x5
	.byte	0xe6,0x1
	.4byte	.LASF2237
	.byte	0x5
	.byte	0xe9,0x1
	.4byte	.LASF2238
	.byte	0x5
	.byte	0xea,0x1
	.4byte	.LASF2239
	.byte	0x5
	.byte	0xeb,0x1
	.4byte	.LASF2240
	.byte	0x5
	.byte	0xec,0x1
	.4byte	.LASF2241
	.byte	0x5
	.byte	0xed,0x1
	.4byte	.LASF2242
	.byte	0x5
	.byte	0xee,0x1
	.4byte	.LASF2243
	.byte	0x5
	.byte	0xef,0x1
	.4byte	.LASF2244
	.byte	0x5
	.byte	0xf2,0x1
	.4byte	.LASF2245
	.byte	0x5
	.byte	0xf3,0x1
	.4byte	.LASF2246
	.byte	0x5
	.byte	0xf4,0x1
	.4byte	.LASF2247
	.byte	0x5
	.byte	0xf5,0x1
	.4byte	.LASF2248
	.byte	0x5
	.byte	0xf6,0x1
	.4byte	.LASF2249
	.byte	0x5
	.byte	0xf7,0x1
	.4byte	.LASF2250
	.byte	0x5
	.byte	0xf8,0x1
	.4byte	.LASF2251
	.byte	0x5
	.byte	0xf9,0x1
	.4byte	.LASF2252
	.byte	0x5
	.byte	0xfa,0x1
	.4byte	.LASF2253
	.byte	0x5
	.byte	0xfb,0x1
	.4byte	.LASF2254
	.byte	0x5
	.byte	0xfc,0x1
	.4byte	.LASF2255
	.byte	0x5
	.byte	0xfd,0x1
	.4byte	.LASF2256
	.byte	0x5
	.byte	0xfe,0x1
	.4byte	.LASF2257
	.byte	0x5
	.byte	0xff,0x1
	.4byte	.LASF2258
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_timer.h.37.41e31e3c41519d549a8819d7a508d7a5,comdat
.Ldebug_macro27:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF2259
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF2260
	.byte	0x5
	.byte	0x2b
	.4byte	.LASF2261
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF2262
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF2263
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF2264
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF2265
	.byte	0x5
	.byte	0x30
	.4byte	.LASF2266
	.byte	0x5
	.byte	0x33
	.4byte	.LASF2267
	.byte	0x5
	.byte	0x34
	.4byte	.LASF2268
	.byte	0x5
	.byte	0x35
	.4byte	.LASF2269
	.byte	0x5
	.byte	0x36
	.4byte	.LASF2270
	.byte	0x5
	.byte	0x37
	.4byte	.LASF2271
	.byte	0x5
	.byte	0x38
	.4byte	.LASF2272
	.byte	0x5
	.byte	0x39
	.4byte	.LASF2273
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF2274
	.byte	0x5
	.byte	0x3b
	.4byte	.LASF2275
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF2276
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF2277
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF2278
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF2279
	.byte	0x5
	.byte	0x40
	.4byte	.LASF2280
	.byte	0x5
	.byte	0x41
	.4byte	.LASF2281
	.byte	0x5
	.byte	0x42
	.4byte	.LASF2282
	.byte	0x5
	.byte	0x43
	.4byte	.LASF2283
	.byte	0x5
	.byte	0x44
	.4byte	.LASF2284
	.byte	0x5
	.byte	0x45
	.4byte	.LASF2285
	.byte	0x5
	.byte	0x46
	.4byte	.LASF2286
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF2287
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF2288
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF2289
	.byte	0x5
	.byte	0x4d
	.4byte	.LASF2290
	.byte	0x5
	.byte	0x4e
	.4byte	.LASF2291
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF2292
	.byte	0x5
	.byte	0x50
	.4byte	.LASF2293
	.byte	0x5
	.byte	0x51
	.4byte	.LASF2294
	.byte	0x5
	.byte	0x54
	.4byte	.LASF2295
	.byte	0x5
	.byte	0x55
	.4byte	.LASF2296
	.byte	0x5
	.byte	0x56
	.4byte	.LASF2297
	.byte	0x5
	.byte	0x57
	.4byte	.LASF2298
	.byte	0x5
	.byte	0x58
	.4byte	.LASF2299
	.byte	0x5
	.byte	0x59
	.4byte	.LASF2300
	.byte	0x5
	.byte	0x5a
	.4byte	.LASF2301
	.byte	0x5
	.byte	0x5b
	.4byte	.LASF2302
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF2303
	.byte	0x5
	.byte	0x5d
	.4byte	.LASF2304
	.byte	0x5
	.byte	0x5e
	.4byte	.LASF2305
	.byte	0x5
	.byte	0x5f
	.4byte	.LASF2306
	.byte	0x5
	.byte	0x62
	.4byte	.LASF2307
	.byte	0x5
	.byte	0x63
	.4byte	.LASF2308
	.byte	0x5
	.byte	0x64
	.4byte	.LASF2309
	.byte	0x5
	.byte	0x65
	.4byte	.LASF2310
	.byte	0x5
	.byte	0x66
	.4byte	.LASF2311
	.byte	0x5
	.byte	0x67
	.4byte	.LASF2312
	.byte	0x5
	.byte	0x68
	.4byte	.LASF2313
	.byte	0x5
	.byte	0x6b
	.4byte	.LASF2314
	.byte	0x5
	.byte	0x6c
	.4byte	.LASF2315
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF2316
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF2317
	.byte	0x5
	.byte	0x6f
	.4byte	.LASF2318
	.byte	0x5
	.byte	0x70
	.4byte	.LASF2319
	.byte	0x5
	.byte	0x71
	.4byte	.LASF2320
	.byte	0x5
	.byte	0x72
	.4byte	.LASF2321
	.byte	0x5
	.byte	0x73
	.4byte	.LASF2322
	.byte	0x5
	.byte	0x74
	.4byte	.LASF2323
	.byte	0x5
	.byte	0x75
	.4byte	.LASF2324
	.byte	0x5
	.byte	0x76
	.4byte	.LASF2325
	.byte	0x5
	.byte	0x77
	.4byte	.LASF2326
	.byte	0x5
	.byte	0x78
	.4byte	.LASF2327
	.byte	0x5
	.byte	0x79
	.4byte	.LASF2328
	.byte	0x5
	.byte	0x7c
	.4byte	.LASF2329
	.byte	0x5
	.byte	0x7d
	.4byte	.LASF2330
	.byte	0x5
	.byte	0x7e
	.4byte	.LASF2331
	.byte	0x5
	.byte	0x7f
	.4byte	.LASF2332
	.byte	0x5
	.byte	0x80,0x1
	.4byte	.LASF2333
	.byte	0x5
	.byte	0x81,0x1
	.4byte	.LASF2334
	.byte	0x5
	.byte	0x82,0x1
	.4byte	.LASF2335
	.byte	0x5
	.byte	0x83,0x1
	.4byte	.LASF2336
	.byte	0x5
	.byte	0x84,0x1
	.4byte	.LASF2337
	.byte	0x5
	.byte	0x85,0x1
	.4byte	.LASF2338
	.byte	0x5
	.byte	0x86,0x1
	.4byte	.LASF2339
	.byte	0x5
	.byte	0x87,0x1
	.4byte	.LASF2340
	.byte	0x5
	.byte	0x8a,0x1
	.4byte	.LASF2341
	.byte	0x5
	.byte	0x8b,0x1
	.4byte	.LASF2342
	.byte	0x5
	.byte	0x8c,0x1
	.4byte	.LASF2343
	.byte	0x5
	.byte	0x8d,0x1
	.4byte	.LASF2344
	.byte	0x5
	.byte	0x8e,0x1
	.4byte	.LASF2345
	.byte	0x5
	.byte	0x8f,0x1
	.4byte	.LASF2346
	.byte	0x5
	.byte	0x90,0x1
	.4byte	.LASF2347
	.byte	0x5
	.byte	0x91,0x1
	.4byte	.LASF2348
	.byte	0x5
	.byte	0x95,0x1
	.4byte	.LASF2349
	.byte	0x5
	.byte	0x96,0x1
	.4byte	.LASF2350
	.byte	0x5
	.byte	0x97,0x1
	.4byte	.LASF2351
	.byte	0x5
	.byte	0x98,0x1
	.4byte	.LASF2352
	.byte	0x5
	.byte	0x99,0x1
	.4byte	.LASF2353
	.byte	0x5
	.byte	0x9a,0x1
	.4byte	.LASF2354
	.byte	0x5
	.byte	0x9b,0x1
	.4byte	.LASF2355
	.byte	0x5
	.byte	0x9c,0x1
	.4byte	.LASF2356
	.byte	0x5
	.byte	0x9d,0x1
	.4byte	.LASF2357
	.byte	0x5
	.byte	0x9e,0x1
	.4byte	.LASF2358
	.byte	0x5
	.byte	0xa0,0x1
	.4byte	.LASF2359
	.byte	0x5
	.byte	0xa1,0x1
	.4byte	.LASF2360
	.byte	0x5
	.byte	0xa2,0x1
	.4byte	.LASF2361
	.byte	0x5
	.byte	0xa3,0x1
	.4byte	.LASF2362
	.byte	0x5
	.byte	0xa7,0x1
	.4byte	.LASF2363
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF2364
	.byte	0x5
	.byte	0xa9,0x1
	.4byte	.LASF2365
	.byte	0x5
	.byte	0xaa,0x1
	.4byte	.LASF2366
	.byte	0x5
	.byte	0xab,0x1
	.4byte	.LASF2367
	.byte	0x5
	.byte	0xac,0x1
	.4byte	.LASF2368
	.byte	0x5
	.byte	0xad,0x1
	.4byte	.LASF2369
	.byte	0x5
	.byte	0xae,0x1
	.4byte	.LASF2370
	.byte	0x5
	.byte	0xaf,0x1
	.4byte	.LASF2371
	.byte	0x5
	.byte	0xb0,0x1
	.4byte	.LASF2372
	.byte	0x5
	.byte	0xb2,0x1
	.4byte	.LASF2373
	.byte	0x5
	.byte	0xb3,0x1
	.4byte	.LASF2374
	.byte	0x5
	.byte	0xb4,0x1
	.4byte	.LASF2375
	.byte	0x5
	.byte	0xb5,0x1
	.4byte	.LASF2376
	.byte	0x5
	.byte	0xb8,0x1
	.4byte	.LASF2377
	.byte	0x5
	.byte	0xb9,0x1
	.4byte	.LASF2378
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF2379
	.byte	0x5
	.byte	0xbb,0x1
	.4byte	.LASF2380
	.byte	0x5
	.byte	0xbc,0x1
	.4byte	.LASF2381
	.byte	0x5
	.byte	0xbd,0x1
	.4byte	.LASF2382
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF2383
	.byte	0x5
	.byte	0xbf,0x1
	.4byte	.LASF2384
	.byte	0x5
	.byte	0xc0,0x1
	.4byte	.LASF2385
	.byte	0x5
	.byte	0xc1,0x1
	.4byte	.LASF2386
	.byte	0x5
	.byte	0xc2,0x1
	.4byte	.LASF2387
	.byte	0x5
	.byte	0xc3,0x1
	.4byte	.LASF2388
	.byte	0x5
	.byte	0xc4,0x1
	.4byte	.LASF2389
	.byte	0x5
	.byte	0xc5,0x1
	.4byte	.LASF2390
	.byte	0x5
	.byte	0xc8,0x1
	.4byte	.LASF2391
	.byte	0x5
	.byte	0xcb,0x1
	.4byte	.LASF2392
	.byte	0x5
	.byte	0xce,0x1
	.4byte	.LASF2393
	.byte	0x5
	.byte	0xd1,0x1
	.4byte	.LASF2394
	.byte	0x5
	.byte	0xd4,0x1
	.4byte	.LASF2395
	.byte	0x5
	.byte	0xd7,0x1
	.4byte	.LASF2396
	.byte	0x5
	.byte	0xda,0x1
	.4byte	.LASF2397
	.byte	0x5
	.byte	0xdd,0x1
	.4byte	.LASF2398
	.byte	0x5
	.byte	0xe0,0x1
	.4byte	.LASF2399
	.byte	0x5
	.byte	0xe1,0x1
	.4byte	.LASF2400
	.byte	0x5
	.byte	0xe2,0x1
	.4byte	.LASF2401
	.byte	0x5
	.byte	0xe3,0x1
	.4byte	.LASF2402
	.byte	0x5
	.byte	0xe4,0x1
	.4byte	.LASF2403
	.byte	0x5
	.byte	0xe5,0x1
	.4byte	.LASF2404
	.byte	0x5
	.byte	0xe6,0x1
	.4byte	.LASF2405
	.byte	0x5
	.byte	0xe7,0x1
	.4byte	.LASF2406
	.byte	0x5
	.byte	0xea,0x1
	.4byte	.LASF2407
	.byte	0x5
	.byte	0xeb,0x1
	.4byte	.LASF2408
	.byte	0x5
	.byte	0xee,0x1
	.4byte	.LASF2409
	.byte	0x5
	.byte	0x9d,0x2
	.4byte	.LASF2410
	.byte	0x5
	.byte	0x9e,0x2
	.4byte	.LASF2411
	.byte	0x5
	.byte	0x9f,0x2
	.4byte	.LASF2412
	.byte	0x5
	.byte	0xa0,0x2
	.4byte	.LASF2413
	.byte	0x5
	.byte	0xa1,0x2
	.4byte	.LASF2414
	.byte	0x5
	.byte	0xa2,0x2
	.4byte	.LASF2415
	.byte	0x5
	.byte	0xa3,0x2
	.4byte	.LASF2416
	.byte	0x5
	.byte	0xa4,0x2
	.4byte	.LASF2417
	.byte	0x5
	.byte	0xa7,0x2
	.4byte	.LASF2418
	.byte	0x5
	.byte	0xa8,0x2
	.4byte	.LASF2419
	.byte	0x5
	.byte	0xa9,0x2
	.4byte	.LASF2420
	.byte	0x5
	.byte	0xaa,0x2
	.4byte	.LASF2421
	.byte	0x5
	.byte	0xab,0x2
	.4byte	.LASF2422
	.byte	0x5
	.byte	0xac,0x2
	.4byte	.LASF2423
	.byte	0x5
	.byte	0xad,0x2
	.4byte	.LASF2424
	.byte	0x5
	.byte	0xae,0x2
	.4byte	.LASF2425
	.byte	0x5
	.byte	0xb1,0x2
	.4byte	.LASF2426
	.byte	0x5
	.byte	0xb2,0x2
	.4byte	.LASF2427
	.byte	0x5
	.byte	0xb3,0x2
	.4byte	.LASF2428
	.byte	0x5
	.byte	0xb4,0x2
	.4byte	.LASF2429
	.byte	0x5
	.byte	0xb5,0x2
	.4byte	.LASF2430
	.byte	0x5
	.byte	0xb6,0x2
	.4byte	.LASF2431
	.byte	0x5
	.byte	0xb7,0x2
	.4byte	.LASF2432
	.byte	0x5
	.byte	0xb8,0x2
	.4byte	.LASF2433
	.byte	0x5
	.byte	0xb9,0x2
	.4byte	.LASF2434
	.byte	0x5
	.byte	0xba,0x2
	.4byte	.LASF2435
	.byte	0x5
	.byte	0xbb,0x2
	.4byte	.LASF2436
	.byte	0x5
	.byte	0xbc,0x2
	.4byte	.LASF2437
	.byte	0x5
	.byte	0xbf,0x2
	.4byte	.LASF2438
	.byte	0x5
	.byte	0xc0,0x2
	.4byte	.LASF2439
	.byte	0x5
	.byte	0xc1,0x2
	.4byte	.LASF2440
	.byte	0x5
	.byte	0xc2,0x2
	.4byte	.LASF2441
	.byte	0x5
	.byte	0xc3,0x2
	.4byte	.LASF2442
	.byte	0x5
	.byte	0xc4,0x2
	.4byte	.LASF2443
	.byte	0x5
	.byte	0xc5,0x2
	.4byte	.LASF2444
	.byte	0x5
	.byte	0xc8,0x2
	.4byte	.LASF2445
	.byte	0x5
	.byte	0xc9,0x2
	.4byte	.LASF2446
	.byte	0x5
	.byte	0xcc,0x2
	.4byte	.LASF2447
	.byte	0x5
	.byte	0xcd,0x2
	.4byte	.LASF2448
	.byte	0x5
	.byte	0xce,0x2
	.4byte	.LASF2449
	.byte	0x5
	.byte	0xcf,0x2
	.4byte	.LASF2450
	.byte	0x5
	.byte	0xd0,0x2
	.4byte	.LASF2451
	.byte	0x5
	.byte	0xd1,0x2
	.4byte	.LASF2452
	.byte	0x5
	.byte	0xd2,0x2
	.4byte	.LASF2453
	.byte	0x5
	.byte	0xd3,0x2
	.4byte	.LASF2454
	.byte	0x5
	.byte	0xd4,0x2
	.4byte	.LASF2455
	.byte	0x5
	.byte	0xd5,0x2
	.4byte	.LASF2456
	.byte	0x5
	.byte	0xd6,0x2
	.4byte	.LASF2457
	.byte	0x5
	.byte	0xd7,0x2
	.4byte	.LASF2458
	.byte	0x5
	.byte	0xd8,0x2
	.4byte	.LASF2459
	.byte	0x5
	.byte	0xd9,0x2
	.4byte	.LASF2460
	.byte	0x5
	.byte	0xda,0x2
	.4byte	.LASF2461
	.byte	0x5
	.byte	0xdb,0x2
	.4byte	.LASF2462
	.byte	0x5
	.byte	0xdc,0x2
	.4byte	.LASF2463
	.byte	0x5
	.byte	0xdd,0x2
	.4byte	.LASF2464
	.byte	0x5
	.byte	0xde,0x2
	.4byte	.LASF2465
	.byte	0x5
	.byte	0xdf,0x2
	.4byte	.LASF2466
	.byte	0x5
	.byte	0xe2,0x2
	.4byte	.LASF2467
	.byte	0x5
	.byte	0xe3,0x2
	.4byte	.LASF2468
	.byte	0x5
	.byte	0xe4,0x2
	.4byte	.LASF2469
	.byte	0x5
	.byte	0xe5,0x2
	.4byte	.LASF2470
	.byte	0x5
	.byte	0xe6,0x2
	.4byte	.LASF2471
	.byte	0x5
	.byte	0xe7,0x2
	.4byte	.LASF2472
	.byte	0x5
	.byte	0xe8,0x2
	.4byte	.LASF2473
	.byte	0x5
	.byte	0xe9,0x2
	.4byte	.LASF2474
	.byte	0x5
	.byte	0xea,0x2
	.4byte	.LASF2475
	.byte	0x5
	.byte	0xeb,0x2
	.4byte	.LASF2476
	.byte	0x5
	.byte	0xec,0x2
	.4byte	.LASF2477
	.byte	0x5
	.byte	0xed,0x2
	.4byte	.LASF2478
	.byte	0x5
	.byte	0xee,0x2
	.4byte	.LASF2479
	.byte	0x5
	.byte	0xef,0x2
	.4byte	.LASF2480
	.byte	0x5
	.byte	0xf0,0x2
	.4byte	.LASF2481
	.byte	0x5
	.byte	0xf1,0x2
	.4byte	.LASF2482
	.byte	0x5
	.byte	0xf2,0x2
	.4byte	.LASF2483
	.byte	0x5
	.byte	0xf3,0x2
	.4byte	.LASF2484
	.byte	0x5
	.byte	0xf4,0x2
	.4byte	.LASF2485
	.byte	0x5
	.byte	0xf7,0x2
	.4byte	.LASF2486
	.byte	0x5
	.byte	0xf8,0x2
	.4byte	.LASF2487
	.byte	0x5
	.byte	0xf9,0x2
	.4byte	.LASF2488
	.byte	0x5
	.byte	0xfa,0x2
	.4byte	.LASF2489
	.byte	0x5
	.byte	0xfb,0x2
	.4byte	.LASF2490
	.byte	0x5
	.byte	0xfc,0x2
	.4byte	.LASF2491
	.byte	0x5
	.byte	0xfd,0x2
	.4byte	.LASF2492
	.byte	0x5
	.byte	0xfe,0x2
	.4byte	.LASF2493
	.byte	0x5
	.byte	0x81,0x3
	.4byte	.LASF2494
	.byte	0x5
	.byte	0x82,0x3
	.4byte	.LASF2495
	.byte	0x5
	.byte	0x83,0x3
	.4byte	.LASF2496
	.byte	0x5
	.byte	0x84,0x3
	.4byte	.LASF2497
	.byte	0x5
	.byte	0x85,0x3
	.4byte	.LASF2498
	.byte	0x5
	.byte	0x88,0x3
	.4byte	.LASF2499
	.byte	0x5
	.byte	0x89,0x3
	.4byte	.LASF2500
	.byte	0x5
	.byte	0x8c,0x3
	.4byte	.LASF2501
	.byte	0x5
	.byte	0x8d,0x3
	.4byte	.LASF2502
	.byte	0x5
	.byte	0x90,0x3
	.4byte	.LASF2503
	.byte	0x5
	.byte	0x91,0x3
	.4byte	.LASF2504
	.byte	0x5
	.byte	0x92,0x3
	.4byte	.LASF2505
	.byte	0x5
	.byte	0x93,0x3
	.4byte	.LASF2506
	.byte	0x5
	.byte	0x96,0x3
	.4byte	.LASF2507
	.byte	0x5
	.byte	0x97,0x3
	.4byte	.LASF2508
	.byte	0x5
	.byte	0x9a,0x3
	.4byte	.LASF2509
	.byte	0x5
	.byte	0x9b,0x3
	.4byte	.LASF2510
	.byte	0x5
	.byte	0x9e,0x3
	.4byte	.LASF2511
	.byte	0x5
	.byte	0x9f,0x3
	.4byte	.LASF2512
	.byte	0x5
	.byte	0xa3,0x3
	.4byte	.LASF2513
	.byte	0x5
	.byte	0xa4,0x3
	.4byte	.LASF2514
	.byte	0x5
	.byte	0xa7,0x3
	.4byte	.LASF2515
	.byte	0x5
	.byte	0xa8,0x3
	.4byte	.LASF2516
	.byte	0x5
	.byte	0xab,0x3
	.4byte	.LASF2517
	.byte	0x5
	.byte	0xac,0x3
	.4byte	.LASF2518
	.byte	0x5
	.byte	0xaf,0x3
	.4byte	.LASF2519
	.byte	0x5
	.byte	0xb0,0x3
	.4byte	.LASF2520
	.byte	0x5
	.byte	0xb1,0x3
	.4byte	.LASF2521
	.byte	0x5
	.byte	0xb2,0x3
	.4byte	.LASF2522
	.byte	0x5
	.byte	0xb3,0x3
	.4byte	.LASF2523
	.byte	0x5
	.byte	0xb6,0x3
	.4byte	.LASF2524
	.byte	0x5
	.byte	0xb7,0x3
	.4byte	.LASF2525
	.byte	0x5
	.byte	0xba,0x3
	.4byte	.LASF2526
	.byte	0x5
	.byte	0xbb,0x3
	.4byte	.LASF2527
	.byte	0x5
	.byte	0xbc,0x3
	.4byte	.LASF2528
	.byte	0x5
	.byte	0xbd,0x3
	.4byte	.LASF2529
	.byte	0x5
	.byte	0xc0,0x3
	.4byte	.LASF2530
	.byte	0x5
	.byte	0xc1,0x3
	.4byte	.LASF2531
	.byte	0x5
	.byte	0xc4,0x3
	.4byte	.LASF2532
	.byte	0x5
	.byte	0xc5,0x3
	.4byte	.LASF2533
	.byte	0x5
	.byte	0xc8,0x3
	.4byte	.LASF2534
	.byte	0x5
	.byte	0xc9,0x3
	.4byte	.LASF2535
	.byte	0x5
	.byte	0xcc,0x3
	.4byte	.LASF2536
	.byte	0x5
	.byte	0xcd,0x3
	.4byte	.LASF2537
	.byte	0x5
	.byte	0xd0,0x3
	.4byte	.LASF2538
	.byte	0x5
	.byte	0xd1,0x3
	.4byte	.LASF2539
	.byte	0x5
	.byte	0xd4,0x3
	.4byte	.LASF2540
	.byte	0x5
	.byte	0xd5,0x3
	.4byte	.LASF2541
	.byte	0x5
	.byte	0xd8,0x3
	.4byte	.LASF2542
	.byte	0x5
	.byte	0xd9,0x3
	.4byte	.LASF2543
	.byte	0x5
	.byte	0xda,0x3
	.4byte	.LASF2544
	.byte	0x5
	.byte	0xdb,0x3
	.4byte	.LASF2545
	.byte	0x5
	.byte	0xdc,0x3
	.4byte	.LASF2546
	.byte	0x5
	.byte	0xdd,0x3
	.4byte	.LASF2547
	.byte	0x5
	.byte	0xde,0x3
	.4byte	.LASF2548
	.byte	0x5
	.byte	0xdf,0x3
	.4byte	.LASF2549
	.byte	0x5
	.byte	0xe2,0x3
	.4byte	.LASF2550
	.byte	0x5
	.byte	0xe3,0x3
	.4byte	.LASF2551
	.byte	0x5
	.byte	0xe6,0x3
	.4byte	.LASF2552
	.byte	0x5
	.byte	0xe7,0x3
	.4byte	.LASF2553
	.byte	0x5
	.byte	0xea,0x3
	.4byte	.LASF2554
	.byte	0x5
	.byte	0xeb,0x3
	.4byte	.LASF2555
	.byte	0x5
	.byte	0xee,0x3
	.4byte	.LASF2556
	.byte	0x5
	.byte	0xef,0x3
	.4byte	.LASF2557
	.byte	0x5
	.byte	0xf2,0x3
	.4byte	.LASF2558
	.byte	0x5
	.byte	0xf3,0x3
	.4byte	.LASF2559
	.byte	0x5
	.byte	0xf4,0x3
	.4byte	.LASF2560
	.byte	0x5
	.byte	0xf7,0x3
	.4byte	.LASF2561
	.byte	0x5
	.byte	0xf8,0x3
	.4byte	.LASF2562
	.byte	0x5
	.byte	0xf9,0x3
	.4byte	.LASF2563
	.byte	0x5
	.byte	0xfc,0x3
	.4byte	.LASF2564
	.byte	0x5
	.byte	0xfd,0x3
	.4byte	.LASF2565
	.byte	0x5
	.byte	0xfe,0x3
	.4byte	.LASF2566
	.byte	0x5
	.byte	0xff,0x3
	.4byte	.LASF2567
	.byte	0x5
	.byte	0x82,0x4
	.4byte	.LASF2568
	.byte	0x5
	.byte	0x83,0x4
	.4byte	.LASF2569
	.byte	0x5
	.byte	0x84,0x4
	.4byte	.LASF2570
	.byte	0x5
	.byte	0x85,0x4
	.4byte	.LASF2571
	.byte	0x5
	.byte	0x86,0x4
	.4byte	.LASF2572
	.byte	0x5
	.byte	0x87,0x4
	.4byte	.LASF2573
	.byte	0x5
	.byte	0x88,0x4
	.4byte	.LASF2574
	.byte	0x5
	.byte	0x89,0x4
	.4byte	.LASF2575
	.byte	0x5
	.byte	0x8a,0x4
	.4byte	.LASF2576
	.byte	0x5
	.byte	0x8d,0x4
	.4byte	.LASF2577
	.byte	0x5
	.byte	0x8e,0x4
	.4byte	.LASF2578
	.byte	0x5
	.byte	0x8f,0x4
	.4byte	.LASF2579
	.byte	0x5
	.byte	0x90,0x4
	.4byte	.LASF2580
	.byte	0x5
	.byte	0x91,0x4
	.4byte	.LASF2581
	.byte	0x5
	.byte	0x92,0x4
	.4byte	.LASF2582
	.byte	0x5
	.byte	0x93,0x4
	.4byte	.LASF2583
	.byte	0x5
	.byte	0x94,0x4
	.4byte	.LASF2584
	.byte	0x5
	.byte	0x95,0x4
	.4byte	.LASF2585
	.byte	0x5
	.byte	0x98,0x4
	.4byte	.LASF2586
	.byte	0x5
	.byte	0x99,0x4
	.4byte	.LASF2587
	.byte	0x5
	.byte	0x9a,0x4
	.4byte	.LASF2588
	.byte	0x5
	.byte	0x9b,0x4
	.4byte	.LASF2589
	.byte	0x5
	.byte	0x9c,0x4
	.4byte	.LASF2590
	.byte	0x5
	.byte	0x9d,0x4
	.4byte	.LASF2591
	.byte	0x5
	.byte	0x9e,0x4
	.4byte	.LASF2592
	.byte	0x5
	.byte	0x9f,0x4
	.4byte	.LASF2593
	.byte	0x5
	.byte	0xa0,0x4
	.4byte	.LASF2594
	.byte	0x5
	.byte	0xa3,0x4
	.4byte	.LASF2595
	.byte	0x5
	.byte	0xa4,0x4
	.4byte	.LASF2596
	.byte	0x5
	.byte	0xa7,0x4
	.4byte	.LASF2597
	.byte	0x5
	.byte	0xa8,0x4
	.4byte	.LASF2598
	.byte	0x5
	.byte	0xa9,0x4
	.4byte	.LASF2599
	.byte	0x5
	.byte	0xaa,0x4
	.4byte	.LASF2600
	.byte	0x5
	.byte	0xab,0x4
	.4byte	.LASF2601
	.byte	0x5
	.byte	0xae,0x4
	.4byte	.LASF2602
	.byte	0x5
	.byte	0xaf,0x4
	.4byte	.LASF2603
	.byte	0x5
	.byte	0xb2,0x4
	.4byte	.LASF2604
	.byte	0x5
	.byte	0xb3,0x4
	.4byte	.LASF2605
	.byte	0x5
	.byte	0xb6,0x4
	.4byte	.LASF2606
	.byte	0x5
	.byte	0xb7,0x4
	.4byte	.LASF2607
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_usart.h.38.bd493dc3b9236603b2fca39bcddb0020,comdat
.Ldebug_macro28:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x26
	.4byte	.LASF2608
	.byte	0x5
	.byte	0x2b
	.4byte	.LASF2609
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF2610
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF2611
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF2612
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF2613
	.byte	0x5
	.byte	0x32
	.4byte	.LASF2614
	.byte	0x5
	.byte	0x33
	.4byte	.LASF2615
	.byte	0x5
	.byte	0x34
	.4byte	.LASF2616
	.byte	0x5
	.byte	0x35
	.4byte	.LASF2617
	.byte	0x5
	.byte	0x36
	.4byte	.LASF2618
	.byte	0x5
	.byte	0x37
	.4byte	.LASF2619
	.byte	0x5
	.byte	0x38
	.4byte	.LASF2620
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF2621
	.byte	0x5
	.byte	0x3d
	.4byte	.LASF2622
	.byte	0x5
	.byte	0x3e
	.4byte	.LASF2623
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF2624
	.byte	0x5
	.byte	0x40
	.4byte	.LASF2625
	.byte	0x5
	.byte	0x41
	.4byte	.LASF2626
	.byte	0x5
	.byte	0x42
	.4byte	.LASF2627
	.byte	0x5
	.byte	0x43
	.4byte	.LASF2628
	.byte	0x5
	.byte	0x44
	.4byte	.LASF2629
	.byte	0x5
	.byte	0x45
	.4byte	.LASF2630
	.byte	0x5
	.byte	0x48
	.4byte	.LASF2631
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF2632
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF2633
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF2634
	.byte	0x5
	.byte	0x50
	.4byte	.LASF2635
	.byte	0x5
	.byte	0x51
	.4byte	.LASF2636
	.byte	0x5
	.byte	0x52
	.4byte	.LASF2637
	.byte	0x5
	.byte	0x53
	.4byte	.LASF2638
	.byte	0x5
	.byte	0x54
	.4byte	.LASF2639
	.byte	0x5
	.byte	0x55
	.4byte	.LASF2640
	.byte	0x5
	.byte	0x56
	.4byte	.LASF2641
	.byte	0x5
	.byte	0x57
	.4byte	.LASF2642
	.byte	0x5
	.byte	0x58
	.4byte	.LASF2643
	.byte	0x5
	.byte	0x59
	.4byte	.LASF2644
	.byte	0x5
	.byte	0x5a
	.4byte	.LASF2645
	.byte	0x5
	.byte	0x5b
	.4byte	.LASF2646
	.byte	0x5
	.byte	0x5c
	.4byte	.LASF2647
	.byte	0x5
	.byte	0x5f
	.4byte	.LASF2648
	.byte	0x5
	.byte	0x60
	.4byte	.LASF2649
	.byte	0x5
	.byte	0x61
	.4byte	.LASF2650
	.byte	0x5
	.byte	0x62
	.4byte	.LASF2651
	.byte	0x5
	.byte	0x63
	.4byte	.LASF2652
	.byte	0x5
	.byte	0x64
	.4byte	.LASF2653
	.byte	0x5
	.byte	0x65
	.4byte	.LASF2654
	.byte	0x5
	.byte	0x66
	.4byte	.LASF2655
	.byte	0x5
	.byte	0x67
	.4byte	.LASF2656
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF2657
	.byte	0x5
	.byte	0x6b
	.4byte	.LASF2658
	.byte	0x5
	.byte	0x6c
	.4byte	.LASF2659
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF2660
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF2661
	.byte	0x5
	.byte	0x6f
	.4byte	.LASF2662
	.byte	0x5
	.byte	0x70
	.4byte	.LASF2663
	.byte	0x5
	.byte	0x71
	.4byte	.LASF2664
	.byte	0x5
	.byte	0x72
	.4byte	.LASF2665
	.byte	0x5
	.byte	0x73
	.4byte	.LASF2666
	.byte	0x5
	.byte	0x74
	.4byte	.LASF2667
	.byte	0x5
	.byte	0x77
	.4byte	.LASF2668
	.byte	0x5
	.byte	0x78
	.4byte	.LASF2669
	.byte	0x5
	.byte	0x7c
	.4byte	.LASF2670
	.byte	0x5
	.byte	0x7d
	.4byte	.LASF2671
	.byte	0x5
	.byte	0x7e
	.4byte	.LASF2672
	.byte	0x5
	.byte	0x7f
	.4byte	.LASF2673
	.byte	0x5
	.byte	0x81,0x1
	.4byte	.LASF2674
	.byte	0x5
	.byte	0x82,0x1
	.4byte	.LASF2675
	.byte	0x5
	.byte	0x85,0x1
	.4byte	.LASF2676
	.byte	0x5
	.byte	0x86,0x1
	.4byte	.LASF2677
	.byte	0x5
	.byte	0x87,0x1
	.4byte	.LASF2678
	.byte	0x5
	.byte	0x88,0x1
	.4byte	.LASF2679
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF2680
	.byte	0x5
	.byte	0xbf,0x1
	.4byte	.LASF2681
	.byte	0x5
	.byte	0xc0,0x1
	.4byte	.LASF2682
	.byte	0x5
	.byte	0xc3,0x1
	.4byte	.LASF2683
	.byte	0x5
	.byte	0xc4,0x1
	.4byte	.LASF2684
	.byte	0x5
	.byte	0xc5,0x1
	.4byte	.LASF2685
	.byte	0x5
	.byte	0xc8,0x1
	.4byte	.LASF2686
	.byte	0x5
	.byte	0xc9,0x1
	.4byte	.LASF2687
	.byte	0x5
	.byte	0xca,0x1
	.4byte	.LASF2688
	.byte	0x5
	.byte	0xcb,0x1
	.4byte	.LASF2689
	.byte	0x5
	.byte	0xce,0x1
	.4byte	.LASF2690
	.byte	0x5
	.byte	0xcf,0x1
	.4byte	.LASF2691
	.byte	0x5
	.byte	0xd0,0x1
	.4byte	.LASF2692
	.byte	0x5
	.byte	0xd3,0x1
	.4byte	.LASF2693
	.byte	0x5
	.byte	0xd4,0x1
	.4byte	.LASF2694
	.byte	0x5
	.byte	0xd5,0x1
	.4byte	.LASF2695
	.byte	0x5
	.byte	0xd8,0x1
	.4byte	.LASF2696
	.byte	0x5
	.byte	0xd9,0x1
	.4byte	.LASF2697
	.byte	0x5
	.byte	0xda,0x1
	.4byte	.LASF2698
	.byte	0x5
	.byte	0xdb,0x1
	.4byte	.LASF2699
	.byte	0x5
	.byte	0xdc,0x1
	.4byte	.LASF2700
	.byte	0x5
	.byte	0xdf,0x1
	.4byte	.LASF2701
	.byte	0x5
	.byte	0xe0,0x1
	.4byte	.LASF2702
	.byte	0x5
	.byte	0xe1,0x1
	.4byte	.LASF2703
	.byte	0x5
	.byte	0xe4,0x1
	.4byte	.LASF2704
	.byte	0x5
	.byte	0xe5,0x1
	.4byte	.LASF2705
	.byte	0x5
	.byte	0xe6,0x1
	.4byte	.LASF2706
	.byte	0x5
	.byte	0xe9,0x1
	.4byte	.LASF2707
	.byte	0x5
	.byte	0xea,0x1
	.4byte	.LASF2708
	.byte	0x5
	.byte	0xeb,0x1
	.4byte	.LASF2709
	.byte	0x5
	.byte	0xee,0x1
	.4byte	.LASF2710
	.byte	0x5
	.byte	0xef,0x1
	.4byte	.LASF2711
	.byte	0x5
	.byte	0xf0,0x1
	.4byte	.LASF2712
	.byte	0x5
	.byte	0xf3,0x1
	.4byte	.LASF2713
	.byte	0x5
	.byte	0xf4,0x1
	.4byte	.LASF2714
	.byte	0x5
	.byte	0xf5,0x1
	.4byte	.LASF2715
	.byte	0x5
	.byte	0xf8,0x1
	.4byte	.LASF2716
	.byte	0x5
	.byte	0xf9,0x1
	.4byte	.LASF2717
	.byte	0x5
	.byte	0xfa,0x1
	.4byte	.LASF2718
	.byte	0x5
	.byte	0xfd,0x1
	.4byte	.LASF2719
	.byte	0x5
	.byte	0xfe,0x1
	.4byte	.LASF2720
	.byte	0x5
	.byte	0xff,0x1
	.4byte	.LASF2721
	.byte	0x5
	.byte	0x82,0x2
	.4byte	.LASF2722
	.byte	0x5
	.byte	0x83,0x2
	.4byte	.LASF2723
	.byte	0x5
	.byte	0x84,0x2
	.4byte	.LASF2724
	.byte	0x5
	.byte	0x87,0x2
	.4byte	.LASF2725
	.byte	0x5
	.byte	0x88,0x2
	.4byte	.LASF2726
	.byte	0x5
	.byte	0x89,0x2
	.4byte	.LASF2727
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_wwdgt.h.37.3e64b838fd471007da900965463a8419,comdat
.Ldebug_macro29:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x25
	.4byte	.LASF2728
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF2729
	.byte	0x5
	.byte	0x2d
	.4byte	.LASF2730
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF2731
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF2732
	.byte	0x5
	.byte	0x33
	.4byte	.LASF2733
	.byte	0x5
	.byte	0x34
	.4byte	.LASF2734
	.byte	0x5
	.byte	0x37
	.4byte	.LASF2735
	.byte	0x5
	.byte	0x38
	.4byte	.LASF2736
	.byte	0x5
	.byte	0x39
	.4byte	.LASF2737
	.byte	0x5
	.byte	0x3c
	.4byte	.LASF2738
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF2739
	.byte	0x5
	.byte	0x40
	.4byte	.LASF2740
	.byte	0x5
	.byte	0x41
	.4byte	.LASF2741
	.byte	0x5
	.byte	0x42
	.4byte	.LASF2742
	.byte	0x5
	.byte	0x43
	.4byte	.LASF2743
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stddef.h.39.144cf5ddcd53cbfdac30259dc1a6c87f,comdat
.Ldebug_macro30:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x27
	.4byte	.LASF2745
	.byte	0x5
	.byte	0x28
	.4byte	.LASF2746
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF2747
	.byte	0x5
	.byte	0x83,0x1
	.4byte	.LASF2748
	.byte	0x5
	.byte	0x84,0x1
	.4byte	.LASF2749
	.byte	0x5
	.byte	0x85,0x1
	.4byte	.LASF2750
	.byte	0x5
	.byte	0x86,0x1
	.4byte	.LASF2751
	.byte	0x5
	.byte	0x87,0x1
	.4byte	.LASF2752
	.byte	0x5
	.byte	0x88,0x1
	.4byte	.LASF2753
	.byte	0x5
	.byte	0x89,0x1
	.4byte	.LASF2754
	.byte	0x5
	.byte	0x8a,0x1
	.4byte	.LASF2755
	.byte	0x5
	.byte	0x8b,0x1
	.4byte	.LASF2756
	.byte	0x6
	.byte	0x9b,0x1
	.4byte	.LASF2757
	.byte	0x5
	.byte	0xb5,0x1
	.4byte	.LASF2758
	.byte	0x5
	.byte	0xb6,0x1
	.4byte	.LASF2759
	.byte	0x5
	.byte	0xb7,0x1
	.4byte	.LASF2760
	.byte	0x5
	.byte	0xb8,0x1
	.4byte	.LASF2761
	.byte	0x5
	.byte	0xb9,0x1
	.4byte	.LASF2762
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF2763
	.byte	0x5
	.byte	0xbb,0x1
	.4byte	.LASF2764
	.byte	0x5
	.byte	0xbc,0x1
	.4byte	.LASF2765
	.byte	0x5
	.byte	0xbd,0x1
	.4byte	.LASF2766
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF2767
	.byte	0x5
	.byte	0xbf,0x1
	.4byte	.LASF2768
	.byte	0x5
	.byte	0xc0,0x1
	.4byte	.LASF2769
	.byte	0x5
	.byte	0xc1,0x1
	.4byte	.LASF2770
	.byte	0x5
	.byte	0xc2,0x1
	.4byte	.LASF2771
	.byte	0x5
	.byte	0xc3,0x1
	.4byte	.LASF2772
	.byte	0x5
	.byte	0xc4,0x1
	.4byte	.LASF2773
	.byte	0x5
	.byte	0xcb,0x1
	.4byte	.LASF2774
	.byte	0x6
	.byte	0xe7,0x1
	.4byte	.LASF2775
	.byte	0x5
	.byte	0x84,0x2
	.4byte	.LASF2776
	.byte	0x5
	.byte	0x85,0x2
	.4byte	.LASF2777
	.byte	0x5
	.byte	0x86,0x2
	.4byte	.LASF2778
	.byte	0x5
	.byte	0x87,0x2
	.4byte	.LASF2779
	.byte	0x5
	.byte	0x88,0x2
	.4byte	.LASF2780
	.byte	0x5
	.byte	0x89,0x2
	.4byte	.LASF2781
	.byte	0x5
	.byte	0x8a,0x2
	.4byte	.LASF2782
	.byte	0x5
	.byte	0x8b,0x2
	.4byte	.LASF2783
	.byte	0x5
	.byte	0x8c,0x2
	.4byte	.LASF2784
	.byte	0x5
	.byte	0x8d,0x2
	.4byte	.LASF2785
	.byte	0x5
	.byte	0x8e,0x2
	.4byte	.LASF2786
	.byte	0x5
	.byte	0x8f,0x2
	.4byte	.LASF2787
	.byte	0x5
	.byte	0x90,0x2
	.4byte	.LASF2788
	.byte	0x5
	.byte	0x91,0x2
	.4byte	.LASF2789
	.byte	0x5
	.byte	0x92,0x2
	.4byte	.LASF2790
	.byte	0x6
	.byte	0x9f,0x2
	.4byte	.LASF2791
	.byte	0x6
	.byte	0xd4,0x2
	.4byte	.LASF2792
	.byte	0x6
	.byte	0x86,0x3
	.4byte	.LASF2793
	.byte	0x5
	.byte	0x8b,0x3
	.4byte	.LASF2794
	.byte	0x6
	.byte	0x91,0x3
	.4byte	.LASF2795
	.byte	0x5
	.byte	0x96,0x3
	.4byte	.LASF2796
	.byte	0x5
	.byte	0x9b,0x3
	.4byte	.LASF2797
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.n200_timer.h.4.7cbfcb0f457964ecd81bc2aaf47d8b32,comdat
.Ldebug_macro31:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x4
	.4byte	.LASF2798
	.byte	0x5
	.byte	0x6
	.4byte	.LASF2799
	.byte	0x5
	.byte	0x7
	.4byte	.LASF2800
	.byte	0x5
	.byte	0x8
	.4byte	.LASF2801
	.byte	0x5
	.byte	0x9
	.4byte	.LASF2802
	.byte	0x5
	.byte	0xa
	.4byte	.LASF2803
	.byte	0x5
	.byte	0xb
	.4byte	.LASF2804
	.byte	0x5
	.byte	0xd
	.4byte	.LASF2805
	.byte	0x5
	.byte	0xe
	.4byte	.LASF2806
	.byte	0x5
	.byte	0xf
	.4byte	.LASF2807
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.riscv_const.h.5.95ac0744d59bfc0d17f4e8adf85ccb42,comdat
.Ldebug_macro32:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x5
	.4byte	.LASF2809
	.byte	0x5
	.byte	0xb
	.4byte	.LASF2810
	.byte	0x5
	.byte	0xc
	.4byte	.LASF2811
	.byte	0x5
	.byte	0xf
	.4byte	.LASF2812
	.byte	0x5
	.byte	0x10
	.4byte	.LASF2813
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.n200_eclic.h.8.88844f0cdf4d8e1ef4e06c0cb5147462,comdat
.Ldebug_macro33:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x8
	.4byte	.LASF2814
	.byte	0x5
	.byte	0xd
	.4byte	.LASF2815
	.byte	0x5
	.byte	0xf
	.4byte	.LASF2816
	.byte	0x5
	.byte	0x11
	.4byte	.LASF2817
	.byte	0x5
	.byte	0x14
	.4byte	.LASF2818
	.byte	0x5
	.byte	0x16
	.4byte	.LASF2819
	.byte	0x5
	.byte	0x18
	.4byte	.LASF2820
	.byte	0x5
	.byte	0x1a
	.4byte	.LASF2821
	.byte	0x5
	.byte	0x1b
	.4byte	.LASF2822
	.byte	0x5
	.byte	0x1c
	.4byte	.LASF2823
	.byte	0x5
	.byte	0x1d
	.4byte	.LASF2824
	.byte	0x5
	.byte	0x1e
	.4byte	.LASF2825
	.byte	0x5
	.byte	0x21
	.4byte	.LASF2826
	.byte	0x5
	.byte	0x23
	.4byte	.LASF2827
	.byte	0x5
	.byte	0x26
	.4byte	.LASF2828
	.byte	0x5
	.byte	0x27
	.4byte	.LASF2829
	.byte	0x5
	.byte	0x29
	.4byte	.LASF2830
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF2831
	.byte	0x5
	.byte	0x2b
	.4byte	.LASF2832
	.byte	0x5
	.byte	0x2c
	.4byte	.LASF2833
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.n200_func.h.11.5e6cb65336aea242ab47b239a06795e1,comdat
.Ldebug_macro34:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0xb
	.4byte	.LASF2834
	.byte	0x5
	.byte	0xc
	.4byte	.LASF2835
	.byte	0x5
	.byte	0xd
	.4byte	.LASF2836
	.byte	0x5
	.byte	0xe
	.4byte	.LASF2837
	.byte	0x5
	.byte	0xf
	.4byte	.LASF2838
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.gd32vf103_rcu.h.42.bd9ae9b75aa7104f9af29b88d3470990,comdat
.Ldebug_macro35:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x2a
	.4byte	.LASF2839
	.byte	0x5
	.byte	0x2e
	.4byte	.LASF2840
	.byte	0x5
	.byte	0x2f
	.4byte	.LASF2841
	.byte	0x5
	.byte	0x30
	.4byte	.LASF2842
	.byte	0x5
	.byte	0x31
	.4byte	.LASF2843
	.byte	0x5
	.byte	0x32
	.4byte	.LASF2844
	.byte	0x5
	.byte	0x33
	.4byte	.LASF2845
	.byte	0x5
	.byte	0x34
	.4byte	.LASF2846
	.byte	0x5
	.byte	0x35
	.4byte	.LASF2847
	.byte	0x5
	.byte	0x36
	.4byte	.LASF2848
	.byte	0x5
	.byte	0x37
	.4byte	.LASF2849
	.byte	0x5
	.byte	0x38
	.4byte	.LASF2850
	.byte	0x5
	.byte	0x39
	.4byte	.LASF2851
	.byte	0x5
	.byte	0x3a
	.4byte	.LASF2852
	.byte	0x5
	.byte	0x3f
	.4byte	.LASF2853
	.byte	0x5
	.byte	0x40
	.4byte	.LASF2854
	.byte	0x5
	.byte	0x41
	.4byte	.LASF2855
	.byte	0x5
	.byte	0x42
	.4byte	.LASF2856
	.byte	0x5
	.byte	0x43
	.4byte	.LASF2857
	.byte	0x5
	.byte	0x44
	.4byte	.LASF2858
	.byte	0x5
	.byte	0x45
	.4byte	.LASF2859
	.byte	0x5
	.byte	0x46
	.4byte	.LASF2860
	.byte	0x5
	.byte	0x47
	.4byte	.LASF2861
	.byte	0x5
	.byte	0x48
	.4byte	.LASF2862
	.byte	0x5
	.byte	0x49
	.4byte	.LASF2863
	.byte	0x5
	.byte	0x4a
	.4byte	.LASF2864
	.byte	0x5
	.byte	0x4b
	.4byte	.LASF2865
	.byte	0x5
	.byte	0x4c
	.4byte	.LASF2866
	.byte	0x5
	.byte	0x4f
	.4byte	.LASF2867
	.byte	0x5
	.byte	0x50
	.4byte	.LASF2868
	.byte	0x5
	.byte	0x51
	.4byte	.LASF2869
	.byte	0x5
	.byte	0x52
	.4byte	.LASF2870
	.byte	0x5
	.byte	0x53
	.4byte	.LASF2871
	.byte	0x5
	.byte	0x54
	.4byte	.LASF2872
	.byte	0x5
	.byte	0x55
	.4byte	.LASF2873
	.byte	0x5
	.byte	0x56
	.4byte	.LASF2874
	.byte	0x5
	.byte	0x57
	.4byte	.LASF2875
	.byte	0x5
	.byte	0x58
	.4byte	.LASF2876
	.byte	0x5
	.byte	0x59
	.4byte	.LASF2877
	.byte	0x5
	.byte	0x5a
	.4byte	.LASF2878
	.byte	0x5
	.byte	0x5b
	.4byte	.LASF2879
	.byte	0x5
	.byte	0x5e
	.4byte	.LASF2880
	.byte	0x5
	.byte	0x5f
	.4byte	.LASF2881
	.byte	0x5
	.byte	0x60
	.4byte	.LASF2882
	.byte	0x5
	.byte	0x61
	.4byte	.LASF2883
	.byte	0x5
	.byte	0x62
	.4byte	.LASF2884
	.byte	0x5
	.byte	0x63
	.4byte	.LASF2885
	.byte	0x5
	.byte	0x64
	.4byte	.LASF2886
	.byte	0x5
	.byte	0x65
	.4byte	.LASF2887
	.byte	0x5
	.byte	0x66
	.4byte	.LASF2888
	.byte	0x5
	.byte	0x67
	.4byte	.LASF2889
	.byte	0x5
	.byte	0x68
	.4byte	.LASF2890
	.byte	0x5
	.byte	0x69
	.4byte	.LASF2891
	.byte	0x5
	.byte	0x6a
	.4byte	.LASF2892
	.byte	0x5
	.byte	0x6b
	.4byte	.LASF2893
	.byte	0x5
	.byte	0x6c
	.4byte	.LASF2894
	.byte	0x5
	.byte	0x6d
	.4byte	.LASF2895
	.byte	0x5
	.byte	0x6e
	.4byte	.LASF2896
	.byte	0x5
	.byte	0x6f
	.4byte	.LASF2897
	.byte	0x5
	.byte	0x70
	.4byte	.LASF2898
	.byte	0x5
	.byte	0x71
	.4byte	.LASF2899
	.byte	0x5
	.byte	0x72
	.4byte	.LASF2900
	.byte	0x5
	.byte	0x73
	.4byte	.LASF2901
	.byte	0x5
	.byte	0x74
	.4byte	.LASF2902
	.byte	0x5
	.byte	0x77
	.4byte	.LASF2903
	.byte	0x5
	.byte	0x78
	.4byte	.LASF2904
	.byte	0x5
	.byte	0x79
	.4byte	.LASF2905
	.byte	0x5
	.byte	0x7a
	.4byte	.LASF2906
	.byte	0x5
	.byte	0x7b
	.4byte	.LASF2907
	.byte	0x5
	.byte	0x7c
	.4byte	.LASF2908
	.byte	0x5
	.byte	0x7d
	.4byte	.LASF2909
	.byte	0x5
	.byte	0x7e
	.4byte	.LASF2910
	.byte	0x5
	.byte	0x7f
	.4byte	.LASF2911
	.byte	0x5
	.byte	0x80,0x1
	.4byte	.LASF2912
	.byte	0x5
	.byte	0x81,0x1
	.4byte	.LASF2913
	.byte	0x5
	.byte	0x84,0x1
	.4byte	.LASF2914
	.byte	0x5
	.byte	0x85,0x1
	.4byte	.LASF2915
	.byte	0x5
	.byte	0x86,0x1
	.4byte	.LASF2916
	.byte	0x5
	.byte	0x87,0x1
	.4byte	.LASF2917
	.byte	0x5
	.byte	0x88,0x1
	.4byte	.LASF2918
	.byte	0x5
	.byte	0x89,0x1
	.4byte	.LASF2919
	.byte	0x5
	.byte	0x8b,0x1
	.4byte	.LASF2920
	.byte	0x5
	.byte	0x8c,0x1
	.4byte	.LASF2921
	.byte	0x5
	.byte	0x8d,0x1
	.4byte	.LASF2922
	.byte	0x5
	.byte	0x8e,0x1
	.4byte	.LASF2923
	.byte	0x5
	.byte	0x8f,0x1
	.4byte	.LASF2924
	.byte	0x5
	.byte	0x90,0x1
	.4byte	.LASF2925
	.byte	0x5
	.byte	0x91,0x1
	.4byte	.LASF2926
	.byte	0x5
	.byte	0x92,0x1
	.4byte	.LASF2927
	.byte	0x5
	.byte	0x93,0x1
	.4byte	.LASF2928
	.byte	0x5
	.byte	0x94,0x1
	.4byte	.LASF2929
	.byte	0x5
	.byte	0x95,0x1
	.4byte	.LASF2930
	.byte	0x5
	.byte	0x96,0x1
	.4byte	.LASF2931
	.byte	0x5
	.byte	0x97,0x1
	.4byte	.LASF2932
	.byte	0x5
	.byte	0x98,0x1
	.4byte	.LASF2933
	.byte	0x5
	.byte	0x9b,0x1
	.4byte	.LASF2934
	.byte	0x5
	.byte	0x9c,0x1
	.4byte	.LASF2935
	.byte	0x5
	.byte	0x9d,0x1
	.4byte	.LASF2936
	.byte	0x5
	.byte	0x9e,0x1
	.4byte	.LASF2937
	.byte	0x5
	.byte	0x9f,0x1
	.4byte	.LASF2938
	.byte	0x5
	.byte	0xa0,0x1
	.4byte	.LASF2939
	.byte	0x5
	.byte	0xa1,0x1
	.4byte	.LASF2940
	.byte	0x5
	.byte	0xa4,0x1
	.4byte	.LASF2941
	.byte	0x5
	.byte	0xa5,0x1
	.4byte	.LASF2942
	.byte	0x5
	.byte	0xa6,0x1
	.4byte	.LASF2943
	.byte	0x5
	.byte	0xa7,0x1
	.4byte	.LASF2944
	.byte	0x5
	.byte	0xa8,0x1
	.4byte	.LASF2945
	.byte	0x5
	.byte	0xa9,0x1
	.4byte	.LASF2946
	.byte	0x5
	.byte	0xaa,0x1
	.4byte	.LASF2947
	.byte	0x5
	.byte	0xab,0x1
	.4byte	.LASF2948
	.byte	0x5
	.byte	0xac,0x1
	.4byte	.LASF2949
	.byte	0x5
	.byte	0xad,0x1
	.4byte	.LASF2950
	.byte	0x5
	.byte	0xae,0x1
	.4byte	.LASF2951
	.byte	0x5
	.byte	0xb1,0x1
	.4byte	.LASF2952
	.byte	0x5
	.byte	0xb2,0x1
	.4byte	.LASF2953
	.byte	0x5
	.byte	0xb3,0x1
	.4byte	.LASF2954
	.byte	0x5
	.byte	0xb4,0x1
	.4byte	.LASF2955
	.byte	0x5
	.byte	0xb5,0x1
	.4byte	.LASF2956
	.byte	0x5
	.byte	0xb6,0x1
	.4byte	.LASF2957
	.byte	0x5
	.byte	0xb7,0x1
	.4byte	.LASF2958
	.byte	0x5
	.byte	0xb8,0x1
	.4byte	.LASF2959
	.byte	0x5
	.byte	0xb9,0x1
	.4byte	.LASF2960
	.byte	0x5
	.byte	0xba,0x1
	.4byte	.LASF2961
	.byte	0x5
	.byte	0xbb,0x1
	.4byte	.LASF2962
	.byte	0x5
	.byte	0xbc,0x1
	.4byte	.LASF2963
	.byte	0x5
	.byte	0xbd,0x1
	.4byte	.LASF2964
	.byte	0x5
	.byte	0xbe,0x1
	.4byte	.LASF2965
	.byte	0x5
	.byte	0xbf,0x1
	.4byte	.LASF2966
	.byte	0x5
	.byte	0xc0,0x1
	.4byte	.LASF2967
	.byte	0x5
	.byte	0xc1,0x1
	.4byte	.LASF2968
	.byte	0x5
	.byte	0xc2,0x1
	.4byte	.LASF2969
	.byte	0x5
	.byte	0xc3,0x1
	.4byte	.LASF2970
	.byte	0x5
	.byte	0xc4,0x1
	.4byte	.LASF2971
	.byte	0x5
	.byte	0xc7,0x1
	.4byte	.LASF2972
	.byte	0x5
	.byte	0xc8,0x1
	.4byte	.LASF2973
	.byte	0x5
	.byte	0xc9,0x1
	.4byte	.LASF2974
	.byte	0x5
	.byte	0xca,0x1
	.4byte	.LASF2975
	.byte	0x5
	.byte	0xcb,0x1
	.4byte	.LASF2976
	.byte	0x5
	.byte	0xcc,0x1
	.4byte	.LASF2977
	.byte	0x5
	.byte	0xcf,0x1
	.4byte	.LASF2978
	.byte	0x5
	.byte	0xd0,0x1
	.4byte	.LASF2979
	.byte	0x5
	.byte	0xd1,0x1
	.4byte	.LASF2980
	.byte	0x5
	.byte	0xd2,0x1
	.4byte	.LASF2981
	.byte	0x5
	.byte	0xd3,0x1
	.4byte	.LASF2982
	.byte	0x5
	.byte	0xd4,0x1
	.4byte	.LASF2983
	.byte	0x5
	.byte	0xd5,0x1
	.4byte	.LASF2984
	.byte	0x5
	.byte	0xd6,0x1
	.4byte	.LASF2985
	.byte	0x5
	.byte	0xd7,0x1
	.4byte	.LASF2986
	.byte	0x5
	.byte	0xda,0x1
	.4byte	.LASF2987
	.byte	0x5
	.byte	0xdd,0x1
	.4byte	.LASF2988
	.byte	0x5
	.byte	0xde,0x1
	.4byte	.LASF2989
	.byte	0x5
	.byte	0xdf,0x1
	.4byte	.LASF2990
	.byte	0x5
	.byte	0xe0,0x1
	.4byte	.LASF2991
	.byte	0x5
	.byte	0xe1,0x1
	.4byte	.LASF2992
	.byte	0x5
	.byte	0xe2,0x1
	.4byte	.LASF2993
	.byte	0x5
	.byte	0xe3,0x1
	.4byte	.LASF2994
	.byte	0x5
	.byte	0xe6,0x1
	.4byte	.LASF2995
	.byte	0x5
	.byte	0xea,0x1
	.4byte	.LASF2996
	.byte	0x5
	.byte	0xeb,0x1
	.4byte	.LASF2997
	.byte	0x5
	.byte	0xec,0x1
	.4byte	.LASF2998
	.byte	0x5
	.byte	0xf0,0x1
	.4byte	.LASF2999
	.byte	0x5
	.byte	0xf1,0x1
	.4byte	.LASF3000
	.byte	0x5
	.byte	0xf2,0x1
	.4byte	.LASF3001
	.byte	0x5
	.byte	0xf5,0x1
	.4byte	.LASF3002
	.byte	0x5
	.byte	0xf6,0x1
	.4byte	.LASF3003
	.byte	0x5
	.byte	0xf7,0x1
	.4byte	.LASF3004
	.byte	0x5
	.byte	0xf8,0x1
	.4byte	.LASF3005
	.byte	0x5
	.byte	0xfb,0x1
	.4byte	.LASF3006
	.byte	0x5
	.byte	0xfc,0x1
	.4byte	.LASF3007
	.byte	0x5
	.byte	0xff,0x1
	.4byte	.LASF3008
	.byte	0x5
	.byte	0x82,0x2
	.4byte	.LASF3009
	.byte	0x5
	.byte	0x83,0x2
	.4byte	.LASF3010
	.byte	0x5
	.byte	0xaa,0x3
	.4byte	.LASF3011
	.byte	0x5
	.byte	0xab,0x3
	.4byte	.LASF3012
	.byte	0x5
	.byte	0xac,0x3
	.4byte	.LASF3013
	.byte	0x5
	.byte	0xad,0x3
	.4byte	.LASF3014
	.byte	0x5
	.byte	0xb0,0x3
	.4byte	.LASF3015
	.byte	0x5
	.byte	0xb1,0x3
	.4byte	.LASF3016
	.byte	0x5
	.byte	0xb2,0x3
	.4byte	.LASF3017
	.byte	0x5
	.byte	0xb3,0x3
	.4byte	.LASF3018
	.byte	0x5
	.byte	0xb6,0x3
	.4byte	.LASF3019
	.byte	0x5
	.byte	0xb7,0x3
	.4byte	.LASF3020
	.byte	0x5
	.byte	0xb8,0x3
	.4byte	.LASF3021
	.byte	0x5
	.byte	0xb9,0x3
	.4byte	.LASF3022
	.byte	0x5
	.byte	0xba,0x3
	.4byte	.LASF3023
	.byte	0x5
	.byte	0xbb,0x3
	.4byte	.LASF3024
	.byte	0x5
	.byte	0xbc,0x3
	.4byte	.LASF3025
	.byte	0x5
	.byte	0xbd,0x3
	.4byte	.LASF3026
	.byte	0x5
	.byte	0xbe,0x3
	.4byte	.LASF3027
	.byte	0x5
	.byte	0xbf,0x3
	.4byte	.LASF3028
	.byte	0x5
	.byte	0xc2,0x3
	.4byte	.LASF3029
	.byte	0x5
	.byte	0xc3,0x3
	.4byte	.LASF3030
	.byte	0x5
	.byte	0xc4,0x3
	.4byte	.LASF3031
	.byte	0x5
	.byte	0xc5,0x3
	.4byte	.LASF3032
	.byte	0x5
	.byte	0xc6,0x3
	.4byte	.LASF3033
	.byte	0x5
	.byte	0xc7,0x3
	.4byte	.LASF3034
	.byte	0x5
	.byte	0xca,0x3
	.4byte	.LASF3035
	.byte	0x5
	.byte	0xcb,0x3
	.4byte	.LASF3036
	.byte	0x5
	.byte	0xcc,0x3
	.4byte	.LASF3037
	.byte	0x5
	.byte	0xcd,0x3
	.4byte	.LASF3038
	.byte	0x5
	.byte	0xce,0x3
	.4byte	.LASF3039
	.byte	0x5
	.byte	0xcf,0x3
	.4byte	.LASF3040
	.byte	0x5
	.byte	0xd2,0x3
	.4byte	.LASF3041
	.byte	0x5
	.byte	0xd3,0x3
	.4byte	.LASF3042
	.byte	0x5
	.byte	0xd4,0x3
	.4byte	.LASF3043
	.byte	0x5
	.byte	0xd5,0x3
	.4byte	.LASF3044
	.byte	0x5
	.byte	0xd6,0x3
	.4byte	.LASF3045
	.byte	0x5
	.byte	0xd7,0x3
	.4byte	.LASF3046
	.byte	0x5
	.byte	0xda,0x3
	.4byte	.LASF3047
	.byte	0x5
	.byte	0xdb,0x3
	.4byte	.LASF3048
	.byte	0x5
	.byte	0xde,0x3
	.4byte	.LASF3049
	.byte	0x5
	.byte	0xe0,0x3
	.4byte	.LASF3050
	.byte	0x5
	.byte	0xe1,0x3
	.4byte	.LASF3051
	.byte	0x5
	.byte	0xe2,0x3
	.4byte	.LASF3052
	.byte	0x5
	.byte	0xe3,0x3
	.4byte	.LASF3053
	.byte	0x5
	.byte	0xe4,0x3
	.4byte	.LASF3054
	.byte	0x5
	.byte	0xe5,0x3
	.4byte	.LASF3055
	.byte	0x5
	.byte	0xe6,0x3
	.4byte	.LASF3056
	.byte	0x5
	.byte	0xe7,0x3
	.4byte	.LASF3057
	.byte	0x5
	.byte	0xe8,0x3
	.4byte	.LASF3058
	.byte	0x5
	.byte	0xe9,0x3
	.4byte	.LASF3059
	.byte	0x5
	.byte	0xea,0x3
	.4byte	.LASF3060
	.byte	0x5
	.byte	0xeb,0x3
	.4byte	.LASF3061
	.byte	0x5
	.byte	0xec,0x3
	.4byte	.LASF3062
	.byte	0x5
	.byte	0xed,0x3
	.4byte	.LASF3063
	.byte	0x5
	.byte	0xee,0x3
	.4byte	.LASF3064
	.byte	0x5
	.byte	0xef,0x3
	.4byte	.LASF3065
	.byte	0x5
	.byte	0xf0,0x3
	.4byte	.LASF3066
	.byte	0x5
	.byte	0xf1,0x3
	.4byte	.LASF3067
	.byte	0x5
	.byte	0xf2,0x3
	.4byte	.LASF3068
	.byte	0x5
	.byte	0xf3,0x3
	.4byte	.LASF3069
	.byte	0x5
	.byte	0xf4,0x3
	.4byte	.LASF3070
	.byte	0x5
	.byte	0xf5,0x3
	.4byte	.LASF3071
	.byte	0x5
	.byte	0xf6,0x3
	.4byte	.LASF3072
	.byte	0x5
	.byte	0xf7,0x3
	.4byte	.LASF3073
	.byte	0x5
	.byte	0xf8,0x3
	.4byte	.LASF3074
	.byte	0x5
	.byte	0xf9,0x3
	.4byte	.LASF3075
	.byte	0x5
	.byte	0xfa,0x3
	.4byte	.LASF3076
	.byte	0x5
	.byte	0xfb,0x3
	.4byte	.LASF3077
	.byte	0x5
	.byte	0xfc,0x3
	.4byte	.LASF3078
	.byte	0x5
	.byte	0xfd,0x3
	.4byte	.LASF3079
	.byte	0x5
	.byte	0xfe,0x3
	.4byte	.LASF3080
	.byte	0x5
	.byte	0xff,0x3
	.4byte	.LASF3081
	.byte	0x5
	.byte	0x82,0x4
	.4byte	.LASF3082
	.byte	0x5
	.byte	0x83,0x4
	.4byte	.LASF3083
	.byte	0x5
	.byte	0x84,0x4
	.4byte	.LASF3084
	.byte	0x5
	.byte	0x85,0x4
	.4byte	.LASF3085
	.byte	0x5
	.byte	0x86,0x4
	.4byte	.LASF3086
	.byte	0x5
	.byte	0x89,0x4
	.4byte	.LASF3087
	.byte	0x5
	.byte	0x8a,0x4
	.4byte	.LASF3088
	.byte	0x5
	.byte	0x8b,0x4
	.4byte	.LASF3089
	.byte	0x5
	.byte	0x8c,0x4
	.4byte	.LASF3090
	.byte	0x5
	.byte	0x8d,0x4
	.4byte	.LASF3091
	.byte	0x5
	.byte	0x8e,0x4
	.4byte	.LASF3092
	.byte	0x5
	.byte	0x8f,0x4
	.4byte	.LASF3093
	.byte	0x5
	.byte	0x90,0x4
	.4byte	.LASF3094
	.byte	0x5
	.byte	0x91,0x4
	.4byte	.LASF3095
	.byte	0x5
	.byte	0x92,0x4
	.4byte	.LASF3096
	.byte	0x5
	.byte	0x95,0x4
	.4byte	.LASF3097
	.byte	0x5
	.byte	0x96,0x4
	.4byte	.LASF3098
	.byte	0x5
	.byte	0x97,0x4
	.4byte	.LASF3099
	.byte	0x5
	.byte	0x98,0x4
	.4byte	.LASF3100
	.byte	0x5
	.byte	0x99,0x4
	.4byte	.LASF3101
	.byte	0x5
	.byte	0x9c,0x4
	.4byte	.LASF3102
	.byte	0x5
	.byte	0x9d,0x4
	.4byte	.LASF3103
	.byte	0x5
	.byte	0x9e,0x4
	.4byte	.LASF3104
	.byte	0x5
	.byte	0x9f,0x4
	.4byte	.LASF3105
	.byte	0x5
	.byte	0xa0,0x4
	.4byte	.LASF3106
	.byte	0x5
	.byte	0xa1,0x4
	.4byte	.LASF3107
	.byte	0x5
	.byte	0xa2,0x4
	.4byte	.LASF3108
	.byte	0x5
	.byte	0xa3,0x4
	.4byte	.LASF3109
	.byte	0x5
	.byte	0xa4,0x4
	.4byte	.LASF3110
	.byte	0x5
	.byte	0xa5,0x4
	.4byte	.LASF3111
	.byte	0x5
	.byte	0xa6,0x4
	.4byte	.LASF3112
	.byte	0x5
	.byte	0xa7,0x4
	.4byte	.LASF3113
	.byte	0x5
	.byte	0xa8,0x4
	.4byte	.LASF3114
	.byte	0x5
	.byte	0xa9,0x4
	.4byte	.LASF3115
	.byte	0x5
	.byte	0xaa,0x4
	.4byte	.LASF3116
	.byte	0x5
	.byte	0xab,0x4
	.4byte	.LASF3117
	.byte	0x5
	.byte	0xac,0x4
	.4byte	.LASF3118
	.byte	0x5
	.byte	0xaf,0x4
	.4byte	.LASF3119
	.byte	0x5
	.byte	0xb0,0x4
	.4byte	.LASF3120
	.byte	0x5
	.byte	0xb1,0x4
	.4byte	.LASF3121
	.byte	0x5
	.byte	0xb2,0x4
	.4byte	.LASF3122
	.byte	0x5
	.byte	0xb3,0x4
	.4byte	.LASF3123
	.byte	0x5
	.byte	0xb4,0x4
	.4byte	.LASF3124
	.byte	0x5
	.byte	0xb5,0x4
	.4byte	.LASF3125
	.byte	0x5
	.byte	0xb6,0x4
	.4byte	.LASF3126
	.byte	0x5
	.byte	0xb7,0x4
	.4byte	.LASF3127
	.byte	0x5
	.byte	0xb8,0x4
	.4byte	.LASF3128
	.byte	0x5
	.byte	0xb9,0x4
	.4byte	.LASF3129
	.byte	0x5
	.byte	0xba,0x4
	.4byte	.LASF3130
	.byte	0x5
	.byte	0xbb,0x4
	.4byte	.LASF3131
	.byte	0x5
	.byte	0xbc,0x4
	.4byte	.LASF3132
	.byte	0x5
	.byte	0xbd,0x4
	.4byte	.LASF3133
	.byte	0x5
	.byte	0xbe,0x4
	.4byte	.LASF3134
	.byte	0x5
	.byte	0xbf,0x4
	.4byte	.LASF3135
	.byte	0x5
	.byte	0xc2,0x4
	.4byte	.LASF3136
	.byte	0x5
	.byte	0xc3,0x4
	.4byte	.LASF3137
	.byte	0x5
	.byte	0xc4,0x4
	.4byte	.LASF3138
	.byte	0x5
	.byte	0xc5,0x4
	.4byte	.LASF3139
	.byte	0x5
	.byte	0xc6,0x4
	.4byte	.LASF3140
	.byte	0x5
	.byte	0xc7,0x4
	.4byte	.LASF3141
	.byte	0x5
	.byte	0xc8,0x4
	.4byte	.LASF3142
	.byte	0x5
	.byte	0xc9,0x4
	.4byte	.LASF3143
	.byte	0x5
	.byte	0xca,0x4
	.4byte	.LASF3144
	.byte	0x5
	.byte	0xcb,0x4
	.4byte	.LASF3145
	.byte	0x5
	.byte	0xcc,0x4
	.4byte	.LASF3146
	.byte	0x5
	.byte	0xcf,0x4
	.4byte	.LASF3147
	.byte	0x5
	.byte	0xd0,0x4
	.4byte	.LASF3148
	.byte	0x5
	.byte	0xd1,0x4
	.4byte	.LASF3149
	.byte	0x5
	.byte	0xd2,0x4
	.4byte	.LASF3150
	.byte	0x5
	.byte	0xd3,0x4
	.4byte	.LASF3151
	.byte	0x5
	.byte	0xd4,0x4
	.4byte	.LASF3152
	.byte	0x5
	.byte	0xd5,0x4
	.4byte	.LASF3153
	.byte	0x5
	.byte	0xd6,0x4
	.4byte	.LASF3154
	.byte	0x5
	.byte	0xd7,0x4
	.4byte	.LASF3155
	.byte	0x5
	.byte	0xd8,0x4
	.4byte	.LASF3156
	.byte	0x5
	.byte	0xd9,0x4
	.4byte	.LASF3157
	.byte	0x5
	.byte	0xdd,0x4
	.4byte	.LASF3158
	.byte	0x5
	.byte	0xde,0x4
	.4byte	.LASF3159
	.byte	0x5
	.byte	0xe1,0x4
	.4byte	.LASF3160
	.byte	0x5
	.byte	0xe2,0x4
	.4byte	.LASF3161
	.byte	0x5
	.byte	0xe5,0x4
	.4byte	.LASF3162
	.byte	0x5
	.byte	0xe6,0x4
	.4byte	.LASF3163
	.byte	0x5
	.byte	0xea,0x4
	.4byte	.LASF3164
	.byte	0x5
	.byte	0xeb,0x4
	.4byte	.LASF3165
	.byte	0x5
	.byte	0xec,0x4
	.4byte	.LASF3166
	.byte	0x5
	.byte	0xed,0x4
	.4byte	.LASF3167
	.byte	0x5
	.byte	0xee,0x4
	.4byte	.LASF3168
	.byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF1190:
	.string	"DAC_WAVE_BIT_WIDTH_4 DWBW(3)"
.LASF328:
	.string	"_POSIX_C_SOURCE 1"
.LASF2169:
	.string	"SPI_I2SCTL_I2SOPMOD BITS(8,9)"
.LASF1588:
	.string	"OB_WP_25 ((uint32_t)0x02000000U)"
.LASF2681:
	.string	"USART_RECEIVE_ENABLE CTL0_REN(1)"
.LASF366:
	.string	"___int16_t_defined 1"
.LASF3023:
	.string	"RCU_AHB_CKSYS_DIV8 CFG0_AHBPSC(10)"
.LASF758:
	.string	"BKP_DATA BITS(0,15)"
.LASF885:
	.string	"CAN_CTL_RFOD BIT(3)"
.LASF1937:
	.string	"I2C_STAT1_RXGC BIT(4)"
.LASF3366:
	.string	"i2s_clock_source"
.LASF1718:
	.string	"GPIO_BC_CR2 BIT(2)"
.LASF3352:
	.string	"stb_cnt"
.LASF2628:
	.string	"USART_STAT_TBE BIT(7)"
.LASF1401:
	.string	"EXTI_EVEN_EVEN11 BIT(11)"
.LASF835:
	.string	"CAN_F19DATA0(canx) REG32((canx) + 0x2D8U)"
.LASF1277:
	.string	"DMA_CHXCTL_MWIDTH BITS(10,11)"
.LASF2131:
	.string	"SPI_CTL0_MSTMOD BIT(2)"
.LASF2932:
	.string	"RCU_APB1RST_PMURST BIT(28)"
.LASF2902:
	.string	"RCU_INT_CKMIC BIT(23)"
.LASF2100:
	.string	"RTC_DIVL_DIV BITS(0,15)"
.LASF2780:
	.string	"_T_WCHAR "
.LASF2002:
	.string	"FWDGT_STAT_RUD BIT(1)"
.LASF537:
	.string	"ADC_IOFF1(adcx) REG32((adcx) + 0x18U)"
.LASF1975:
	.string	"I2C_DMA_OFF ((uint32_t)0x00000000U)"
.LASF3343:
	.string	"rcu_hxtal_clock_monitor_disable"
.LASF2558:
	.string	"TIMER_IC_POLARITY_RISING ((uint16_t)0x0000U)"
.LASF2166:
	.string	"SPI_I2SCTL_CKPL BIT(3)"
.LASF2480:
	.string	"TIMER_DMACFG_DMATC_13TRANSFER DMACFG_DMATC(12)"
.LASF150:
	.string	"__FLT_MAX_10_EXP__ 38"
.LASF2143:
	.string	"SPI_CTL1_DMAREN BIT(0)"
.LASF510:
	.string	"SPI_BASE (APB1_BUS_BASE + 0x00003800U)"
.LASF824:
	.string	"CAN_F8DATA0(canx) REG32((canx) + 0x280U)"
.LASF981:
	.string	"CAN_RFIFOMDATA0_DB1 BITS(8,15)"
.LASF2385:
	.string	"TIMER_CHCTL2_CH2EN BIT(8)"
.LASF914:
	.string	"CAN_TSTAT_MTE2 BIT(19)"
.LASF2230:
	.string	"I2S_CKPL_HIGH SPI_I2SCTL_CKPL"
.LASF2965:
	.string	"RCU_APB1EN_I2C0EN BIT(21)"
.LASF2120:
	.string	"SPI_CTL0(spix) REG32((spix) + 0x00U)"
.LASF2545:
	.string	"TIMER_OC_MODE_TOGGLE ((uint16_t)0x0030U)"
.LASF2427:
	.string	"TIMER_FLAG_CH0 TIMER_INTF_CH0IF"
.LASF1472:
	.string	"EXTI_PD_PD6 BIT(6)"
.LASF1096:
	.string	"CAN_FILTERBITS_16BIT ((uint8_t)0x00U)"
.LASF3286:
	.string	"RCU_INT_FLAG_HXTALSTB"
.LASF3183:
	.string	"long unsigned int"
.LASF727:
	.string	"BKP_DATA14 REG16((BKP) + 0x50U)"
.LASF1769:
	.string	"AFIO_EXTI2_SS BITS(8, 11)"
.LASF2600:
	.string	"TIMER_EXT_TRI_PSC_DIV4 SMCFG_ETPSC(2)"
.LASF2080:
	.string	"RTC_PSCH REG32(RTC + 0x08U)"
.LASF1777:
	.string	"AFIO_EXTI10_SS BITS(8, 11)"
.LASF300:
	.string	"__SIZEOF_WCHAR_T__ 4"
.LASF501:
	.string	"EXMC_BASE ((uint32_t)0xA0000000U)"
.LASF1671:
	.string	"GPIO_OCTL_OCTL3 BIT(3)"
.LASF1340:
	.string	"EXMC_SNCTL_NRTP BITS(2,3)"
.LASF307:
	.string	"__riscv_div 1"
.LASF755:
	.string	"BKP_OCTL REG16((BKP) + 0x2CU)"
.LASF2444:
	.string	"TIMER_DMA_TRGD ((uint16_t)TIMER_DMAINTEN_TRGDEN)"
.LASF2083:
	.string	"RTC_DIVL REG32(RTC + 0x14U)"
.LASF478:
	.string	"WCHAR_MAX (__WCHAR_MAX__)"
.LASF2005:
	.string	"FWDGT_PSC_DIV8 ((uint8_t)PSC_PSC(1))"
.LASF1037:
	.string	"GET_ERR_ERRN(regval) GET_BITS((uint32_t)(regval), 4U, 6U)"
.LASF2221:
	.string	"I2S_MODE_MASTERTX I2SCTL_I2SOPMOD(2)"
.LASF2773:
	.string	"_SIZET_ "
.LASF1329:
	.string	"ECLIC_PRIGROUP_LEVEL2_PRIO2 2"
.LASF2576:
	.string	"TIMER_SMCFG_TRGSEL_ETIFP SMCFG_TRGSEL(7)"
.LASF1116:
	.string	"CAN_INT_WAKEUP CAN_INTEN_WIE"
.LASF439:
	.string	"INT16_MIN (-__INT16_MAX__ - 1)"
.LASF1610:
	.string	"GPIO_BOP(gpiox) REG32((gpiox) + 0x10U)"
.LASF1721:
	.string	"GPIO_BC_CR5 BIT(5)"
.LASF3061:
	.string	"RCU_PLL_MUL12 CFG0_PLLMF(10)"
.LASF581:
	.string	"ADC_CTL1_SWRCST BIT(22)"
.LASF2625:
	.string	"USART_STAT_IDLEF BIT(4)"
.LASF1226:
	.string	"DAC_TRIANGLE_AMPLITUDE_4095 DAC_WAVE_BIT_WIDTH_12"
.LASF2833:
	.string	"PMOVI_HANDLER eclic_pmovi_handler"
.LASF2226:
	.string	"I2S_STD_LSB I2SCTL_I2SSTD(2)"
.LASF3142:
	.string	"RCU_PLL1_MUL13 CFG1_PLL1MF(11)"
.LASF2067:
	.string	"PMU_FLAG_WAKEUP PMU_CS_WUF"
.LASF1739:
	.string	"GPIO_LOCK_LK7 BIT(7)"
.LASF2064:
	.string	"PMU_LVDT_5 CTL_LVDT(5)"
.LASF341:
	.string	"SYSTEM_GD32VF103_H "
.LASF1516:
	.string	"FMC_CTL_LK BIT(7)"
.LASF623:
	.string	"ADC0_1_EXTTRIG_REGULAR_T0_CH1 CTL1_ETSRC(1)"
.LASF459:
	.string	"UINT_FAST8_MAX (__UINT_FAST8_MAX__)"
.LASF1048:
	.string	"CAN_ERRN_7 ERR_ERRN(7U)"
.LASF182:
	.string	"__LDBL_DECIMAL_DIG__ 36"
.LASF3217:
	.string	"RCU_BKPI"
.LASF452:
	.string	"INT64_MAX (__INT64_MAX__)"
.LASF1369:
	.string	"EXTI_SWIEV REG32(EXTI + 0x10U)"
.LASF1773:
	.string	"AFIO_EXTI6_SS BITS(8, 11)"
.LASF2729:
	.string	"WWDGT WWDGT_BASE"
.LASF413:
	.string	"_UINT32_T_DECLARED "
.LASF1278:
	.string	"DMA_CHXCTL_PRIO BITS(12,13)"
.LASF784:
	.string	"CAN_STAT(canx) REG32((canx) + 0x04U)"
.LASF1781:
	.string	"AFIO_EXTI14_SS BITS(8, 11)"
.LASF674:
	.string	"ADC_CHANNEL_13 ((uint8_t)0x0DU)"
.LASF1807:
	.string	"GPIO_EVENT_PIN_0 ((uint8_t)0x00U)"
.LASF1580:
	.string	"OB_WP_17 ((uint32_t)0x00020000U)"
.LASF2737:
	.string	"WWDGT_CFG_EWIE BIT(9)"
.LASF2646:
	.string	"USART_CTL0_WL BIT(12)"
.LASF435:
	.string	"UINT8_MAX (__UINT8_MAX__)"
.LASF1115:
	.string	"CAN_INT_ERR CAN_INTEN_ERRIE"
.LASF1553:
	.string	"FMC_NSPC ((uint8_t)0xA5U)"
.LASF1017:
	.string	"TMDATA0_DB0(regval) (BITS(0,7) & ((uint32_t)(regval) << 0))"
.LASF993:
	.string	"CAN_FW_FW(regval) BIT(regval)"
.LASF1900:
	.string	"I2C_CTL0_START BIT(8)"
.LASF2593:
	.string	"TIMER_SLAVE_MODE_EVENT SMCFG_SMC(6)"
.LASF1726:
	.string	"GPIO_BC_CR10 BIT(10)"
.LASF386:
	.string	"short +1"
.LASF1873:
	.string	"GPIO_TIMER4CH3_IREMAP ((uint32_t)0x00200001U)"
.LASF1602:
	.string	"GPIOC (GPIO_BASE + 0x00000800U)"
.LASF2477:
	.string	"TIMER_DMACFG_DMATC_10TRANSFER DMACFG_DMATC(9)"
.LASF702:
	.string	"OVSCR_OVSR(regval) (BITS(2,4) & ((uint32_t)(regval) << 2))"
.LASF2673:
	.string	"USART_REGIDX_BIT2(regidx,bitpos,regidx2,bitpos2) (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16) | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))"
.LASF2654:
	.string	"USART_CTL1_CKEN BIT(11)"
.LASF1014:
	.string	"FCTL_HBC1F(regval) (BITS(8,13) & ((uint32_t)(regval) << 8))"
.LASF625:
	.string	"ADC0_1_EXTTRIG_REGULAR_T1_CH1 CTL1_ETSRC(3)"
.LASF678:
	.string	"ADC_CHANNEL_17 ((uint8_t)0x11U)"
.LASF2403:
	.string	"TIMER_CCHP_BRKEN BIT(12)"
.LASF2246:
	.string	"SPI_FLAG_TBE SPI_STAT_TBE"
.LASF2601:
	.string	"TIMER_EXT_TRI_PSC_DIV8 SMCFG_ETPSC(3)"
.LASF467:
	.string	"INT_FAST64_MAX (__INT_FAST64_MAX__)"
.LASF1823:
	.string	"GPIO_PIN_SOURCE_0 ((uint8_t)0x00U)"
.LASF3306:
	.string	"RCU_INT_PLL1STB"
.LASF512:
	.string	"I2C_BASE (APB1_BUS_BASE + 0x00005400U)"
.LASF2659:
	.string	"USART_CTL2_IRLP BIT(2)"
.LASF2459:
	.string	"TIMER_DMACFG_DMATA_CAR DMACFG_DMATA(11)"
.LASF2453:
	.string	"TIMER_DMACFG_DMATA_SWEVG DMACFG_DMATA(5)"
.LASF2042:
	.string	"DBG_LOW_POWER_STANDBY DBG_CTL_STB_HOLD"
.LASF2509:
	.string	"TIMER_UPDATE_SRC_REGULAR TIMER_CTL0_UPS"
.LASF1764:
	.string	"AFIO_PCF0_SWJ_CFG BITS(24, 26)"
.LASF1555:
	.string	"OB_SPC_SPC ((uint32_t)0x000000FFU)"
.LASF2203:
	.string	"I2S_AUDIOSAMPLE_11K ((uint32_t)11025U)"
.LASF1030:
	.string	"GET_RFIFOMDATA0_DB1(regval) GET_BITS((uint32_t)(regval), 8U, 15U)"
.LASF1000:
	.string	"CAN_BIT_POS0(val) (((uint32_t)(val) >> 6) & 0x1FU)"
.LASF2227:
	.string	"I2S_STD_PCMSHORT I2SCTL_I2SSTD(3)"
.LASF3383:
	.string	"rcu_pll_config"
.LASF2876:
	.string	"RCU_CFG0_USBFSPSC BITS(22,23)"
.LASF1144:
	.string	"DAC_CTL_DBOFF0 BIT(1)"
.LASF3409:
	.string	"rcu_system_clock_source_get"
.LASF3006:
	.string	"CTL_REG_OFFSET 0x00U"
.LASF2652:
	.string	"USART_CTL1_CPH BIT(9)"
.LASF1381:
	.string	"EXTI_INTEN_INTEN10 BIT(10)"
.LASF1513:
	.string	"FMC_CTL_OBPG BIT(4)"
.LASF421:
	.string	"_UINTPTR_T_DECLARED "
.LASF1705:
	.string	"GPIO_BOP_CR5 BIT(21)"
.LASF1754:
	.string	"AFIO_PCF0_USART0_REMAP BIT(2)"
.LASF3063:
	.string	"RCU_PLL_MUL14 CFG0_PLLMF(12)"
.LASF1732:
	.string	"GPIO_LOCK_LK0 BIT(0)"
.LASF2809:
	.string	"_RISCV_CONST_H "
.LASF2094:
	.string	"RTC_CTL_RSYNF BIT(3)"
.LASF1176:
	.string	"DAC_TRIGGER_T6_TRGO CTL_DTSEL(2)"
.LASF2753:
	.string	"_BSD_PTRDIFF_T_ "
.LASF1042:
	.string	"CAN_ERRN_1 ERR_ERRN(1U)"
.LASF2277:
	.string	"TIMER_PSC(timerx) REG32((timerx) + 0x28U)"
.LASF1908:
	.string	"I2C_CTL1_ERRIE BIT(8)"
.LASF2995:
	.string	"RCU_DSV_DSLPVS BITS(0,1)"
.LASF2214:
	.string	"I2S_FRAMEFORMAT_DT24B_CH32B (I2SCTL_DTLEN(1) | SPI_I2SCTL_CHLEN)"
.LASF2909:
	.string	"RCU_APB2RST_ADC0RST BIT(9)"
.LASF3338:
	.string	"clock"
.LASF2201:
	.string	"SPI_PSC_256 CTL0_PSC(7)"
.LASF50:
	.string	"__INT_LEAST16_TYPE__ short int"
.LASF303:
	.string	"__riscv 1"
.LASF2856:
	.string	"RCU_CTL_IRC8MCALIB BITS(8,15)"
.LASF2107:
	.string	"RTC_INT_OVERFLOW RTC_INTEN_OVIE"
.LASF1850:
	.string	"GPIO_PIN_11 BIT(11)"
.LASF1131:
	.string	"DAC_SWT REG32(DAC + 0x04U)"
.LASF3113:
	.string	"RCU_PREDV0_DIV11 CFG1_PREDV0(10)"
.LASF2859:
	.string	"RCU_CTL_HXTALBPS BIT(18)"
.LASF669:
	.string	"ADC_CHANNEL_8 ((uint8_t)0x08U)"
.LASF2225:
	.string	"I2S_STD_MSB I2SCTL_I2SSTD(1)"
.LASF305:
	.string	"__riscv_atomic 1"
.LASF3177:
	.string	"short int"
.LASF1857:
	.string	"GPIO_I2C0_REMAP ((uint32_t)0x00000002U)"
.LASF551:
	.string	"ADC_OVSCR(adcx) REG32((adcx) + 0x80U)"
.LASF1230:
	.string	"DMA_INTF(dmax) REG32((dmax) + 0x00U)"
.LASF2894:
	.string	"RCU_INT_PLL2STBIE BIT(14)"
.LASF1891:
	.string	"I2C_RT(i2cx) REG32((i2cx) + 0x20U)"
.LASF3374:
	.string	"reg0"
.LASF3090:
	.string	"RCU_CKOUT0SRC_IRC8M CFG0_CKOUT0SEL(5)"
.LASF2248:
	.string	"SPI_FLAG_CONFERR SPI_STAT_CONFERR"
.LASF1342:
	.string	"EXMC_SNCTL_NREN BIT(6)"
.LASF1441:
	.string	"EXTI_FTEN_FTEN13 BIT(13)"
.LASF1642:
	.string	"GPIO_CTL1_MD11 BITS(12, 13)"
.LASF548:
	.string	"ADC_IDATA2(adcx) REG32((adcx) + 0x44U)"
.LASF350:
	.string	"__GNUC_PREREQ(maj,min) ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))"
.LASF2325:
	.string	"TIMER_DMAINTEN_CH2DEN BIT(11)"
.LASF1923:
	.string	"I2C_STAT0_ADD10SEND BIT(3)"
.LASF70:
	.string	"__INT_MAX__ 0x7fffffff"
.LASF2171:
	.string	"SPI_I2SCTL_I2SSEL BIT(11)"
.LASF2879:
	.string	"RCU_CFG0_PLLMF_4 BIT(29)"
.LASF227:
	.string	"__FLT64_DECIMAL_DIG__ 17"
.LASF864:
	.string	"CAN_F20DATA1(canx) REG32((canx) + 0x2E4U)"
.LASF274:
	.string	"__FLT64X_NORM_MAX__ 1.18973149535723176508575932662800702e+4932F64x"
.LASF2665:
	.string	"USART_CTL2_RTSEN BIT(8)"
.LASF1324:
	.string	"DMA_MEMORY_TO_MEMORY_ENABLE ((uint32_t)0x00000001U)"
.LASF1034:
	.string	"GET_RFIFOMDATA1_DB5(regval) GET_BITS((uint32_t)(regval), 8U, 15U)"
.LASF2164:
	.string	"SPI_I2SCTL_CHLEN BIT(0)"
.LASF2562:
	.string	"TIMER_IC_SELECTION_INDIRECTTI ((uint16_t)0x0002U)"
.LASF1258:
	.string	"DMA_CH6PADDR(dmax) REG32((dmax) + 0x88U)"
.LASF762:
	.string	"BKP_OCTL_ROSEL BIT(9)"
.LASF1968:
	.string	"I2C_SCLSTRETCH_ENABLE ((uint32_t)0x00000000U)"
.LASF795:
	.string	"CAN_TMI1(canx) REG32((canx) + 0x190U)"
.LASF465:
	.string	"UINT_FAST32_MAX (__UINT_FAST32_MAX__)"
.LASF666:
	.string	"ADC_CHANNEL_5 ((uint8_t)0x05U)"
.LASF532:
	.string	"ADC_CTL0(adcx) REG32((adcx) + 0x04U)"
.LASF1237:
	.string	"DMA_CH1CNT(dmax) REG32((dmax) + 0x20U)"
.LASF946:
	.string	"CAN_ERR_PERR BIT(1)"
.LASF3138:
	.string	"RCU_PLL1_MUL9 CFG1_PLL1MF(7)"
.LASF40:
	.string	"__SIG_ATOMIC_TYPE__ int"
.LASF3268:
	.string	"rcu_periph_reset_enum"
.LASF958:
	.string	"CAN_TMI_FT BIT(1)"
.LASF1139:
	.string	"DACC_L12DH REG32(DAC + 0x24U)"
.LASF1056:
	.string	"CAN_BT_SJW_3TQ ((uint8_t)0x02U)"
.LASF3119:
	.string	"CFG1_PREDV1(regval) (BITS(4,7) & ((uint32_t)(regval) << 4))"
.LASF1617:
	.string	"AFIO_EXTISS2 REG32(AFIO + 0x10U)"
.LASF2438:
	.string	"TIMER_DMA_UPD ((uint16_t)TIMER_DMAINTEN_UPDEN)"
.LASF451:
	.string	"INT64_MIN (-__INT64_MAX__ - 1)"
.LASF3276:
	.string	"RCU_FLAG_EPRST"
.LASF642:
	.string	"ADC_SAMPLETIME_13POINT5 SAMPTX_SPT(2)"
.LASF1216:
	.string	"DAC_TRIANGLE_AMPLITUDE_3 DAC_WAVE_BIT_WIDTH_2"
.LASF2974:
	.string	"RCU_BDCTL_LXTALBPS BIT(2)"
.LASF813:
	.string	"CAN_FSCFG(canx) REG32((canx) + 0x20CU)"
.LASF2145:
	.string	"SPI_CTL1_NSSDRV BIT(2)"
.LASF2825:
	.string	"ECLIC_INT_ATTR_TRIG_NEG 0x04"
.LASF3064:
	.string	"RCU_PLL_MUL6_5 CFG0_PLLMF(13)"
.LASF44:
	.string	"__INT64_TYPE__ long long int"
.LASF904:
	.string	"CAN_TSTAT_MTE0 BIT(3)"
.LASF639:
	.string	"SAMPTX_SPT(regval) (BITS(0,2) & ((uint32_t)(regval) << 0))"
.LASF2079:
	.string	"RTC_CTL REG32(RTC + 0x04U)"
.LASF1262:
	.string	"DMA_INTF_HTFIF BIT(2)"
.LASF2245:
	.string	"SPI_FLAG_RBNE SPI_STAT_RBNE"
.LASF2582:
	.string	"TIMER_TRI_OUT_SRC_O0CPRE CTL1_MMC(4)"
.LASF62:
	.string	"__UINT_FAST16_TYPE__ unsigned int"
.LASF2475:
	.string	"TIMER_DMACFG_DMATC_8TRANSFER DMACFG_DMATC(7)"
.LASF2804:
	.string	"TIMER_MTIME_size 0x8"
.LASF1957:
	.string	"I2C_SMBUSMODE_ENABLE I2C_CTL0_SMBEN"
.LASF364:
	.string	"__have_long32 1"
.LASF2769:
	.string	"_BSD_SIZE_T_DEFINED_ "
.LASF1100:
	.string	"CAN_FILTER_MASK_16BITS ((uint32_t)0x0000FFFFU)"
.LASF801:
	.string	"CAN_TMDATA02(canx) REG32((canx) + 0x1A8U)"
.LASF2944:
	.string	"RCU_APB2EN_PCEN BIT(4)"
.LASF1856:
	.string	"GPIO_SPI0_REMAP ((uint32_t)0x00000001U)"
.LASF2840:
	.string	"RCU_CTL REG32(RCU + 0x00U)"
.LASF1964:
	.string	"I2C_ACKPOS_NEXT ((uint32_t)0x00000000U)"
.LASF948:
	.string	"CAN_ERR_ERRN BITS(4,6)"
.LASF3375:
	.string	"rcu_pll2_config"
.LASF3188:
	.string	"uint32_t"
.LASF195:
	.string	"__FLT16_MAX_EXP__ 16"
.LASF2244:
	.string	"SPI_I2S_INT_FLAG_FERR ((uint8_t)0x06U)"
.LASF1977:
	.string	"I2C_DMALST_OFF ((uint32_t)0x00000000U)"
.LASF401:
	.string	"__LEAST8 \"hh\""
.LASF1568:
	.string	"OB_WP_5 ((uint32_t)0x00000020U)"
.LASF204:
	.string	"__FLT16_HAS_INFINITY__ 1"
.LASF1263:
	.string	"DMA_INTF_ERRIF BIT(3)"
.LASF1149:
	.string	"DAC_CTL_DDMAEN0 BIT(12)"
.LASF2895:
	.string	"RCU_INT_IRC40KSTBIC BIT(16)"
.LASF1195:
	.string	"DAC_WAVE_BIT_WIDTH_9 DWBW(8)"
.LASF124:
	.string	"__INT_FAST8_MAX__ 0x7fffffff"
.LASF327:
	.string	"RT_USING_LIBC 1"
.LASF1339:
	.string	"EXMC_SNCTL_NRMUX BIT(1)"
.LASF2435:
	.string	"TIMER_FLAG_CH1O TIMER_INTF_CH1OF"
.LASF814:
	.string	"CAN_FAFIFO(canx) REG32((canx) + 0x214U)"
.LASF2262:
	.string	"TIMER2 (TIMER_BASE + 0x00000400U)"
.LASF1751:
	.string	"AFIO_EC_EOE BIT(7)"
.LASF2442:
	.string	"TIMER_DMA_CH3D ((uint16_t)TIMER_DMAINTEN_CH3DEN)"
.LASF39:
	.string	"__CHAR32_TYPE__ long unsigned int"
.LASF2240:
	.string	"SPI_I2S_INT_FLAG_RXORERR ((uint8_t)0x02U)"
.LASF1156:
	.string	"DAC_CTL_DDMAEN1 BIT(28)"
.LASF1406:
	.string	"EXTI_EVEN_EVEN16 BIT(16)"
.LASF1394:
	.string	"EXTI_EVEN_EVEN4 BIT(4)"
.LASF3019:
	.string	"CFG0_AHBPSC(regval) (BITS(4,7) & ((uint32_t)(regval) << 4))"
.LASF1063:
	.string	"CAN_BT_BS1_6TQ ((uint8_t)0x05U)"
.LASF2502:
	.string	"TIMER_COUNTER_DOWN ((uint16_t)TIMER_CTL0_DIR)"
.LASF294:
	.string	"__GCC_ATOMIC_LONG_LOCK_FREE 2"
.LASF2567:
	.string	"TIMER_IC_PSC_DIV8 ((uint16_t)0x000CU)"
.LASF25:
	.string	"__BIGGEST_ALIGNMENT__ 16"
.LASF1412:
	.string	"EXTI_RTEN_RTEN3 BIT(3)"
.LASF2574:
	.string	"TIMER_SMCFG_TRGSEL_CI0FE0 SMCFG_TRGSEL(5)"
.LASF860:
	.string	"CAN_F16DATA1(canx) REG32((canx) + 0x2C4U)"
.LASF2335:
	.string	"TIMER_INTF_TRGIF BIT(6)"
.LASF1170:
	.string	"DACC_R8DH_DAC1_DH BITS(8,15)"
.LASF1834:
	.string	"GPIO_PIN_SOURCE_11 ((uint8_t)0x0BU)"
.LASF2119:
	.string	"SPI2 (SPI_BASE + 0x00000400U)"
.LASF2443:
	.string	"TIMER_DMA_CMTD ((uint16_t)TIMER_DMAINTEN_CMTDEN)"
.LASF1320:
	.string	"DMA_PRIORITY_MEDIUM CHCTL_PRIO(1U)"
.LASF1696:
	.string	"GPIO_BOP_BOP12 BIT(12)"
.LASF2010:
	.string	"FWDGT_PSC_DIV256 ((uint8_t)PSC_PSC(6))"
.LASF3342:
	.string	"irc8m_adjval"
.LASF3231:
	.string	"RCU_USART0"
.LASF3209:
	.string	"RCU_USART1"
.LASF3210:
	.string	"RCU_USART2"
.LASF1712:
	.string	"GPIO_BOP_CR12 BIT(28)"
.LASF1656:
	.string	"GPIO_ISTAT_ISTAT4 BIT(4)"
.LASF1461:
	.string	"EXTI_SWIEV_SWIEV14 BIT(14)"
.LASF2185:
	.string	"SPI_NSS_SOFT SPI_CTL0_SWNSSEN"
.LASF177:
	.string	"__LDBL_MIN_EXP__ (-16381)"
.LASF312:
	.string	"__riscv_arch_test 1"
.LASF2218:
	.string	"I2SCTL_I2SOPMOD(regval) (BITS(8,9) & ((uint32_t)(regval) << 8))"
.LASF1083:
	.string	"CAN_MAILBOX1 ((uint8_t)0x01U)"
.LASF829:
	.string	"CAN_F13DATA0(canx) REG32((canx) + 0x2A8U)"
.LASF2208:
	.string	"I2S_AUDIOSAMPLE_48K ((uint32_t)48000U)"
.LASF1534:
	.string	"FMC_BIT_POS1(val) ((uint32_t)(val) & 0x1FU)"
.LASF387:
	.string	"__int20 +2"
.LASF343:
	.string	"_MACHINE__DEFAULT_TYPES_H "
.LASF1914:
	.string	"I2C_SADDR0_ADDRESS BITS(1,7)"
.LASF2188:
	.string	"SPI_ENDIAN_LSB SPI_CTL0_LF"
.LASF1663:
	.string	"GPIO_ISTAT_ISTAT11 BIT(11)"
.LASF2150:
	.string	"SPI_CTL1_TBEIE BIT(7)"
.LASF3316:
	.string	"rcu_osci_type_enum"
.LASF1830:
	.string	"GPIO_PIN_SOURCE_7 ((uint8_t)0x07U)"
.LASF1491:
	.string	"FMC_STAT REG32((FMC) + 0x0CU)"
.LASF2121:
	.string	"SPI_CTL1(spix) REG32((spix) + 0x04U)"
.LASF2307:
	.string	"TIMER_SMCFG_SMC BITS(0,2)"
.LASF627:
	.string	"ADC0_1_EXTTRIG_REGULAR_T3_CH3 CTL1_ETSRC(5)"
.LASF1358:
	.string	"EXMC_MEMORY_TYPE_PSRAM SNCTL_NRTP(1)"
.LASF2210:
	.string	"I2S_AUDIOSAMPLE_192K ((uint32_t)192000U)"
.LASF1812:
	.string	"GPIO_EVENT_PIN_5 ((uint8_t)0x05U)"
.LASF800:
	.string	"CAN_TMP2(canx) REG32((canx) + 0x1A4U)"
.LASF930:
	.string	"CAN_RFIFO1_RFD1 BIT(5)"
.LASF880:
	.string	"CAN_RFIFOMDATA0(canx,bank) REG32((canx) + 0x1B8U + ((bank) * 0x10U))"
.LASF2961:
	.string	"RCU_APB1EN_USART1EN BIT(17)"
.LASF2636:
	.string	"USART_CTL0_REN BIT(2)"
.LASF1297:
	.string	"DMA_FLAG_G DMA_INTF_GIF"
.LASF1842:
	.string	"GPIO_PIN_3 BIT(3)"
.LASF806:
	.string	"CAN_RFIFOMDATA10(canx) REG32((canx) + 0x1BCU)"
.LASF1020:
	.string	"TMDATA0_DB3(regval) (BITS(24,31) & ((uint32_t)(regval) << 24))"
.LASF3165:
	.string	"RCU_DEEPSLEEP_V_1_2 DSV_DSLPVS(0)"
.LASF2281:
	.string	"TIMER_CH1CV(timerx) REG32((timerx) + 0x38U)"
.LASF1875:
	.string	"GPIO_SWJ_NONJTRST_REMAP ((uint32_t)0x00300100U)"
.LASF1927:
	.string	"I2C_STAT0_BERR BIT(8)"
.LASF3097:
	.string	"BDCTL_RTCSRC(regval) (BITS(8,9) & ((uint32_t)(regval) << 8))"
.LASF1416:
	.string	"EXTI_RTEN_RTEN7 BIT(7)"
.LASF1183:
	.string	"DAC_WAVE_DISABLE CTL_DWM(0)"
.LASF2483:
	.string	"TIMER_DMACFG_DMATC_16TRANSFER DMACFG_DMATC(15)"
.LASF1837:
	.string	"GPIO_PIN_SOURCE_14 ((uint8_t)0x0EU)"
.LASF1638:
	.string	"GPIO_CTL1_MD9 BITS(4, 5)"
.LASF2207:
	.string	"I2S_AUDIOSAMPLE_44K ((uint32_t)44100U)"
.LASF1761:
	.string	"AFIO_PCF0_CAN_REMAP BITS(13, 14)"
.LASF2235:
	.string	"SPI_I2S_INT_TBE ((uint8_t)0x00U)"
.LASF1646:
	.string	"GPIO_CTL1_MD13 BITS(20, 21)"
.LASF3267:
	.string	"RCU_USART0RST"
.LASF323:
	.string	"HAVE_CCONFIG_H 1"
.LASF46:
	.string	"__UINT16_TYPE__ short unsigned int"
.LASF942:
	.string	"CAN_INTEN_ERRIE BIT(15)"
.LASF431:
	.string	"INTPTR_MAX (__INTPTR_MAX__)"
.LASF2832:
	.string	"BWEI_HANDLER eclic_bwei_handler"
.LASF2648:
	.string	"USART_CTL1_ADDR BITS(0,3)"
.LASF71:
	.string	"__LONG_MAX__ 0x7fffffffL"
.LASF2228:
	.string	"I2S_STD_PCMLONG (I2SCTL_I2SSTD(3) | SPI_I2SCTL_PCMSMOD)"
.LASF2399:
	.string	"TIMER_CCHP_DTCFG BITS(0,7)"
.LASF970:
	.string	"CAN_TMDATA1_DB5 BITS(8,15)"
.LASF488:
	.string	"UINT64_C(x) __UINT64_C(x)"
.LASF3103:
	.string	"RCU_PREDV0_DIV1 CFG1_PREDV0(0)"
.LASF296:
	.string	"__GCC_ATOMIC_TEST_AND_SET_TRUEVAL 1"
.LASF2467:
	.string	"DMACFG_DMATC(regval) (BITS(8, 12) & ((uint32_t)(regval) << 8U))"
.LASF2309:
	.string	"TIMER_SMCFG_MSM BIT(7)"
.LASF106:
	.string	"__INT_LEAST8_WIDTH__ 8"
.LASF2955:
	.string	"RCU_APB1EN_TIMER4EN BIT(3)"
.LASF55:
	.string	"__UINT_LEAST32_TYPE__ long unsigned int"
.LASF2029:
	.string	"DBG_CTL_TIMER0_HOLD BIT(10)"
.LASF1095:
	.string	"CAN_MODE_SLEEP ((uint8_t)0x04U)"
.LASF962:
	.string	"CAN_TMP_DLENC BITS(0,3)"
.LASF1085:
	.string	"CAN_NOMAILBOX ((uint8_t)0x03U)"
.LASF1345:
	.string	"EXMC_SNCTL_NRWTEN BIT(13)"
.LASF1795:
	.string	"GPIO_OSPEED_2MHZ ((uint8_t)0x02U)"
.LASF1133:
	.string	"DAC0_L12DH REG32(DAC + 0x0CU)"
.LASF2416:
	.string	"TIMER_INT_TRG TIMER_DMAINTEN_TRGIE"
.LASF362:
	.string	"__EXP(x) __ ##x ##__"
.LASF1522:
	.string	"FMC_OBSTAT_SPC BIT(1)"
.LASF437:
	.string	"INT_LEAST8_MAX (__INT_LEAST8_MAX__)"
.LASF2511:
	.string	"TIMER_ROS_STATE_ENABLE ((uint16_t)TIMER_CCHP_ROS)"
.LASF3136:
	.string	"CFG1_PLL1MF(regval) (BITS(8,11) & ((uint32_t)(regval) << 8))"
.LASF283:
	.string	"__GNUC_STDC_INLINE__ 1"
.LASF427:
	.string	"__int_fast16_t_defined 1"
.LASF1611:
	.string	"GPIO_BC(gpiox) REG32((gpiox) + 0x14U)"
.LASF2350:
	.string	"TIMER_CHCTL0_CH0COMFEN BIT(2)"
.LASF284:
	.string	"__NO_INLINE__ 1"
.LASF3284:
	.string	"RCU_INT_FLAG_LXTALSTB"
.LASF2904:
	.string	"RCU_APB2RST_PARST BIT(2)"
.LASF1952:
	.string	"I2C_BIT_POS2(val) (((uint32_t)(val) & 0x1F0000U) >> 16)"
.LASF2490:
	.string	"TIMER_EVENT_SRC_CH3G ((uint16_t)0x0010U)"
.LASF567:
	.string	"ADC_CTL0_SYNCM BITS(16,19)"
.LASF1955:
	.string	"I2C_STAT1_REG_OFFSET 0x18U"
.LASF869:
	.string	"CAN_F25DATA1(canx) REG32((canx) + 0x30CU)"
.LASF2304:
	.string	"TIMER_CTL1_ISO2 BIT(12)"
.LASF2653:
	.string	"USART_CTL1_CPL BIT(10)"
.LASF2146:
	.string	"SPI_CTL1_NSSP BIT(3)"
.LASF539:
	.string	"ADC_IOFF3(adcx) REG32((adcx) + 0x20U)"
.LASF2405:
	.string	"TIMER_CCHP_OAEN BIT(14)"
.LASF1433:
	.string	"EXTI_FTEN_FTEN5 BIT(5)"
.LASF3262:
	.string	"RCU_GPIOERST"
.LASF198:
	.string	"__FLT16_MAX__ 6.55040000000000000000000000000000000e+4F16"
.LASF852:
	.string	"CAN_F8DATA1(canx) REG32((canx) + 0x284U)"
.LASF1808:
	.string	"GPIO_EVENT_PIN_1 ((uint8_t)0x01U)"
.LASF895:
	.string	"CAN_STAT_WUIF BIT(3)"
.LASF2657:
	.string	"USART_CTL2_ERRIE BIT(0)"
.LASF3273:
	.string	"RCU_FLAG_PLL2STB"
.LASF1948:
	.string	"I2C_REG_VAL(i2cx,offset) (REG32((i2cx) + (((uint32_t)(offset) & 0xFFFFU) >> 6)))"
.LASF1641:
	.string	"GPIO_CTL1_CTL10 BITS(10, 11)"
.LASF1059:
	.string	"CAN_BT_BS1_2TQ ((uint8_t)0x01U)"
.LASF1184:
	.string	"DAC_WAVE_MODE_LFSR CTL_DWM(1)"
.LASF2117:
	.string	"SPI0 (SPI_BASE + 0x0000F800U)"
.LASF1147:
	.string	"DAC_CTL_DWM0 BITS(6,7)"
.LASF2113:
	.string	"RTC_FLAG_OVERFLOW RTC_CTL_OVIF"
.LASF3308:
	.string	"rcu_int_enum"
.LASF2634:
	.string	"USART_CTL0_SBKCMD BIT(0)"
.LASF704:
	.string	"ADC_OVERSAMPLING_RATIO_MUL4 OVSCR_OVSR(1)"
.LASF1316:
	.string	"DMA_MEMORY_WIDTH_16BIT CHCTL_MWIDTH(1U)"
.LASF2009:
	.string	"FWDGT_PSC_DIV128 ((uint8_t)PSC_PSC(5))"
.LASF3376:
	.string	"pll_mul"
.LASF2740:
	.string	"WWDGT_CFG_PSC_DIV1 CFG_PSC(0)"
.LASF1503:
	.string	"FMC_WS_WSCNT BITS(0,2)"
.LASF2610:
	.string	"USART2 (USART_BASE+(0x00000400U))"
.LASF185:
	.string	"__LDBL_MIN__ 3.36210314311209350626267781732175260e-4932L"
.LASF1175:
	.string	"DAC_TRIGGER_T2_TRGO CTL_DTSEL(1)"
.LASF3009:
	.string	"CFG0_REG_OFFSET 0x04U"
.LASF1690:
	.string	"GPIO_BOP_BOP6 BIT(6)"
.LASF2392:
	.string	"TIMER_PSC_PSC BITS(0,15)"
.LASF1108:
	.string	"CAN_INT_RFNE1 CAN_INTEN_RFNEIE1"
.LASF821:
	.string	"CAN_F5DATA0(canx) REG32((canx) + 0x268U)"
.LASF2523:
	.string	"TIMER_CCHP_PROT_2 CCHP_PROT(3)"
.LASF2046:
	.string	"PMU_CS REG32((PMU) + 0x04U)"
.LASF388:
	.string	"__int20__ +2"
.LASF3398:
	.string	"periph_reset"
.LASF1310:
	.string	"CHCTL_PWIDTH(regval) (BITS(8,9) & ((uint32_t)(regval) << 8))"
.LASF1905:
	.string	"I2C_CTL0_SALT BIT(13)"
.LASF1921:
	.string	"I2C_STAT0_ADDSEND BIT(1)"
.LASF859:
	.string	"CAN_F15DATA1(canx) REG32((canx) + 0x2BCU)"
.LASF1211:
	.string	"DATA_ALIGN(regval) (BITS(0,1) & ((uint32_t)(regval) << 0))"
.LASF322:
	.string	"NO_INIT 1"
.LASF1521:
	.string	"FMC_OBSTAT_OBERR BIT(0)"
.LASF3068:
	.string	"RCU_PLL_MUL19 (PLLMF_4 | CFG0_PLLMF(2))"
.LASF1570:
	.string	"OB_WP_7 ((uint32_t)0x00000080U)"
.LASF618:
	.string	"ADC_DATAALIGN_RIGHT ((uint32_t)0x00000000U)"
.LASF3303:
	.string	"RCU_INT_IRC8MSTB"
.LASF3223:
	.string	"RCU_GPIOB"
.LASF3224:
	.string	"RCU_GPIOC"
.LASF3225:
	.string	"RCU_GPIOD"
.LASF1722:
	.string	"GPIO_BC_CR6 BIT(6)"
.LASF1446:
	.string	"EXTI_FTEN_FTEN18 BIT(18)"
.LASF3332:
	.string	"predv0"
.LASF3333:
	.string	"predv1"
.LASF1595:
	.string	"OB_WP_ALL ((uint32_t)0xFFFFFFFFU)"
.LASF1498:
	.string	"OB_USER REG16((OB) + 0x02U)"
.LASF2204:
	.string	"I2S_AUDIOSAMPLE_16K ((uint32_t)16000U)"
.LASF1122:
	.string	"CRC_CTL REG32(CRC + 0x08U)"
.LASF3105:
	.string	"RCU_PREDV0_DIV3 CFG1_PREDV0(2)"
.LASF194:
	.string	"__FLT16_MIN_10_EXP__ (-4)"
.LASF605:
	.string	"ADC_SCAN_MODE ADC_CTL0_SM"
.LASF1902:
	.string	"I2C_CTL0_ACKEN BIT(10)"
.LASF2910:
	.string	"RCU_APB2RST_ADC1RST BIT(10)"
.LASF2897:
	.string	"RCU_INT_IRC8MSTBIC BIT(18)"
.LASF2935:
	.string	"RCU_AHBEN_DMA1EN BIT(1)"
.LASF2085:
	.string	"RTC_CNTL REG32(RTC + 0x1CU)"
.LASF3380:
	.string	"rcu_predv0_config"
.LASF1767:
	.string	"AFIO_EXTI0_SS BITS(0, 3)"
.LASF2679:
	.string	"USART_CTL2_REG_OFFSET (0x00000014U)"
.LASF414:
	.string	"__int32_t_defined 1"
.LASF11:
	.string	"__ATOMIC_ACQUIRE 2"
.LASF2923:
	.string	"RCU_APB1RST_USART1RST BIT(17)"
.LASF540:
	.string	"ADC_WDHT(adcx) REG32((adcx) + 0x24U)"
.LASF2705:
	.string	"USART_CLEN_NONE CTL1_CLEN(0)"
.LASF175:
	.string	"__LDBL_MANT_DIG__ 113"
.LASF2219:
	.string	"I2S_MODE_SLAVETX I2SCTL_I2SOPMOD(0)"
.LASF2296:
	.string	"TIMER_CTL1_CCUC BIT(2)"
.LASF2232:
	.string	"SPI_DMA_RECEIVE ((uint8_t)0x01U)"
.LASF223:
	.string	"__FLT64_MIN_EXP__ (-1021)"
.LASF3353:
	.string	"reval"
.LASF128:
	.string	"__INT_FAST32_MAX__ 0x7fffffff"
.LASF357:
	.string	"__MISC_VISIBLE 0"
.LASF18:
	.string	"__SIZEOF_LONG_LONG__ 8"
.LASF549:
	.string	"ADC_IDATA3(adcx) REG32((adcx) + 0x48U)"
.LASF905:
	.string	"CAN_TSTAT_MST0 BIT(7)"
.LASF961:
	.string	"CAN_TMI_SFID BITS(21,31)"
.LASF3059:
	.string	"RCU_PLL_MUL10 CFG0_PLLMF(8)"
.LASF1479:
	.string	"EXTI_PD_PD13 BIT(13)"
.LASF1557:
	.string	"OB_USER_USER ((uint32_t)0x00FF0000U)"
.LASF214:
	.string	"__FLT32_NORM_MAX__ 3.40282346638528859811704183484516925e+38F32"
.LASF923:
	.string	"CAN_RFIFO0_RFL0 BITS(0,1)"
.LASF1308:
	.string	"DMA_MEMORY_INCREASE_DISABLE ((uint8_t)0x00U)"
.LASF232:
	.string	"__FLT64_DENORM_MIN__ 4.94065645841246544176568792868221372e-324F64"
.LASF3053:
	.string	"RCU_PLL_MUL4 CFG0_PLLMF(2)"
.LASF3117:
	.string	"RCU_PREDV0_DIV15 CFG1_PREDV0(14)"
.LASF872:
	.string	"CAN_TMI(canx,bank) REG32((canx) + 0x180U + ((bank) * 0x10U))"
.LASF1804:
	.string	"GPIO_PORT_SOURCE_GPIOC ((uint8_t)0x02U)"
.LASF2983:
	.string	"RCU_RSTSCK_SWRSTF BIT(28)"
.LASF2024:
	.string	"DBG_CTL_SLP_HOLD BIT(0)"
.LASF2340:
	.string	"TIMER_INTF_CH3OF BIT(12)"
.LASF854:
	.string	"CAN_F10DATA1(canx) REG32((canx) + 0x294U)"
.LASF3281:
	.string	"RCU_FLAG_LPRST"
.LASF1904:
	.string	"I2C_CTL0_PECTRANS BIT(12)"
.LASF2382:
	.string	"TIMER_CHCTL2_CH1P BIT(5)"
.LASF2693:
	.string	"CTL0_WL(regval) (BIT(12) & ((uint32_t)(regval) << 12))"
.LASF3341:
	.string	"rcu_irc8m_adjust_value_set"
.LASF282:
	.string	"__USER_LABEL_PREFIX__ "
.LASF1422:
	.string	"EXTI_RTEN_RTEN13 BIT(13)"
.LASF1208:
	.string	"DAC_LFSR_BITS9_0 DAC_WAVE_BIT_WIDTH_10"
.LASF533:
	.string	"ADC_CTL1(adcx) REG32((adcx) + 0x08U)"
.LASF1682:
	.string	"GPIO_OCTL_OCTL14 BIT(14)"
.LASF565:
	.string	"ADC_CTL0_DISIC BIT(12)"
.LASF1800:
	.string	"GPIO_EVENT_PORT_GPIOD ((uint8_t)0x03U)"
.LASF1067:
	.string	"CAN_BT_BS1_10TQ ((uint8_t)0x09U)"
.LASF1866:
	.string	"GPIO_TIMER1_FULL_REMAP ((uint32_t)0x00180300U)"
.LASF3011:
	.string	"CFG0_SCS(regval) (BITS(0,1) & ((uint32_t)(regval) << 0))"
.LASF3081:
	.string	"RCU_PLL_MUL32 (PLLMF_4 | CFG0_PLLMF(15))"
.LASF1255:
	.string	"DMA_CH5MADDR(dmax) REG32((dmax) + 0x78U)"
.LASF2249:
	.string	"SPI_FLAG_RXORERR SPI_STAT_RXORERR"
.LASF3241:
	.string	"RCU_TIMER5RST"
.LASF1150:
	.string	"DAC_CTL_DEN1 BIT(16)"
.LASF2663:
	.string	"USART_CTL2_DENR BIT(6)"
.LASF1500:
	.string	"OB_WP1 REG16((OB) + 0x0AU)"
.LASF995:
	.string	"CAN_REGIDX_BIT(regidx,bitpos) (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))"
.LASF180:
	.string	"__LDBL_MAX_10_EXP__ 4932"
.LASF2783:
	.string	"_BSD_WCHAR_T_ "
.LASF85:
	.string	"__WINT_WIDTH__ 32"
.LASF1240:
	.string	"DMA_CH2CTL(dmax) REG32((dmax) + 0x30U)"
.LASF2795:
	.string	"__need_NULL"
.LASF2462:
	.string	"TIMER_DMACFG_DMATA_CH1CV DMACFG_DMATA(14)"
.LASF1538:
	.string	"FMC_OBSTAT_REG_OFFSET 0x1CU"
.LASF2389:
	.string	"TIMER_CHCTL2_CH3EN BIT(12)"
.LASF1675:
	.string	"GPIO_OCTL_OCTL7 BIT(7)"
.LASF2329:
	.string	"TIMER_INTF_UPIF BIT(0)"
.LASF2845:
	.string	"RCU_AHBEN REG32(RCU + 0x14U)"
.LASF2929:
	.string	"RCU_APB1RST_CAN0RST BIT(25)"
.LASF542:
	.string	"ADC_RSQ0(adcx) REG32((adcx) + 0x2CU)"
.LASF2524:
	.string	"TIMER_BREAK_ENABLE ((uint16_t)TIMER_CCHP_BRKEN)"
.LASF2979:
	.string	"RCU_RSTSCK_IRC40KSTB BIT(1)"
.LASF2559:
	.string	"TIMER_IC_POLARITY_FALLING ((uint16_t)0x0002U)"
.LASF360:
	.string	"__XSI_VISIBLE 0"
.LASF2076:
	.string	"GD32VF103_RTC_H "
.LASF273:
	.string	"__FLT64X_MAX__ 1.18973149535723176508575932662800702e+4932F64x"
.LASF2486:
	.string	"TIMER_EVENT_SRC_UPG ((uint16_t)0x0001U)"
.LASF2167:
	.string	"SPI_I2SCTL_I2SSTD BITS(4,5)"
.LASF526:
	.string	"USE_STDPERIPH_DRIVER "
.LASF2967:
	.string	"RCU_APB1EN_CAN0EN BIT(25)"
.LASF3066:
	.string	"RCU_PLL_MUL17 (PLLMF_4 | CFG0_PLLMF(0))"
.LASF925:
	.string	"CAN_RFIFO0_RFO0 BIT(4)"
.LASF1625:
	.string	"GPIO_CTL0_CTL2 BITS(10, 11)"
.LASF2613:
	.string	"USART0 (USART_BASE+(0x0000F400U))"
.LASF2869:
	.string	"RCU_CFG0_AHBPSC BITS(4,7)"
.LASF3048:
	.string	"RCU_PLLSRC_HXTAL RCU_CFG0_PLLSEL"
.LASF665:
	.string	"ADC_CHANNEL_4 ((uint8_t)0x04U)"
.LASF3130:
	.string	"RCU_PREDV1_DIV11 CFG1_PREDV1(10)"
.LASF1448:
	.string	"EXTI_SWIEV_SWIEV1 BIT(1)"
.LASF1220:
	.string	"DAC_TRIANGLE_AMPLITUDE_63 DAC_WAVE_BIT_WIDTH_6"
.LASF102:
	.string	"__UINT32_MAX__ 0xffffffffUL"
.LASF2561:
	.string	"TIMER_IC_SELECTION_DIRECTTI ((uint16_t)0x0001U)"
.LASF1375:
	.string	"EXTI_INTEN_INTEN4 BIT(4)"
.LASF2915:
	.string	"RCU_APB1RST_TIMER2RST BIT(1)"
.LASF3359:
	.string	"int_flag_clear"
.LASF3056:
	.string	"RCU_PLL_MUL7 CFG0_PLLMF(5)"
.LASF606:
	.string	"ADC_INSERTED_CHANNEL_AUTO ADC_CTL0_ICA"
.LASF834:
	.string	"CAN_F18DATA0(canx) REG32((canx) + 0x2D0U)"
.LASF1165:
	.string	"DACC_R12DH_DAC0_DH BITS(0,11)"
.LASF1328:
	.string	"ECLIC_PRIGROUP_LEVEL1_PRIO3 1"
.LASF2441:
	.string	"TIMER_DMA_CH2D ((uint16_t)TIMER_DMAINTEN_CH2DEN)"
.LASF3036:
	.string	"RCU_APB2_CKAHB_DIV1 CFG0_APB2PSC(0)"
.LASF1132:
	.string	"DAC0_R12DH REG32(DAC + 0x08U)"
.LASF2349:
	.string	"TIMER_CHCTL0_CH0MS BITS(0,1)"
.LASF1911:
	.string	"I2C_CTL1_DMAON BIT(11)"
.LASF318:
	.string	"__riscv_zifencei 2000000"
.LASF275:
	.string	"__FLT64X_MIN__ 3.36210314311209350626267781732175260e-4932F64x"
.LASF529:
	.string	"ADC0 ADC_BASE"
.LASF1515:
	.string	"FMC_CTL_START BIT(6)"
.LASF3086:
	.string	"RCU_CKUSB_CKPLL_DIV2 CFG0_USBPSC(3)"
.LASF1076:
	.string	"CAN_BT_BS2_3TQ ((uint8_t)0x02U)"
.LASF1362:
	.string	"EXMC_NWAIT_POLARITY_HIGH ((uint32_t)0x00000200U)"
.LASF187:
	.string	"__LDBL_DENORM_MIN__ 6.47517511943802511092443895822764655e-4966L"
.LASF1080:
	.string	"CAN_BT_BS2_7TQ ((uint8_t)0x06U)"
.LASF2028:
	.string	"DBG_CTL_WWDGT_HOLD BIT(9)"
.LASF165:
	.string	"__DBL_MAX_10_EXP__ 308"
.LASF37:
	.string	"__UINTMAX_TYPE__ long long unsigned int"
.LASF2288:
	.string	"TIMER_CTL0_UPDIS BIT(1)"
.LASF573:
	.string	"ADC_CTL1_RSTCLB BIT(3)"
.LASF3120:
	.string	"RCU_PREDV1_DIV1 CFG1_PREDV1(0)"
.LASF1894:
	.string	"I2C_CTL0_SMBEN BIT(1)"
.LASF416:
	.string	"_UINT64_T_DECLARED "
.LASF504:
	.string	"AHB1_BUS_BASE ((uint32_t)0x40018000U)"
.LASF2690:
	.string	"CTL0_WM(regval) (BIT(11) & ((uint32_t)(regval) << 11))"
.LASF1337:
	.string	"EXMC_SNWTCFG0 REG32(EXMC + 0x104U)"
.LASF2971:
	.string	"RCU_APB1EN_DACEN BIT(29)"
.LASF508:
	.string	"WWDGT_BASE (APB1_BUS_BASE + 0x00002C00U)"
.LASF1469:
	.string	"EXTI_PD_PD3 BIT(3)"
.LASF1455:
	.string	"EXTI_SWIEV_SWIEV8 BIT(8)"
.LASF1630:
	.string	"GPIO_CTL0_MD5 BITS(20, 21)"
.LASF1798:
	.string	"GPIO_EVENT_PORT_GPIOB ((uint8_t)0x01U)"
.LASF3401:
	.string	"periph"
.LASF966:
	.string	"CAN_TMDATA0_DB1 BITS(8,15)"
.LASF1615:
	.string	"AFIO_EXTISS0 REG32(AFIO + 0x08U)"
.LASF430:
	.string	"INTPTR_MIN (-__INTPTR_MAX__ - 1)"
.LASF1668:
	.string	"GPIO_OCTL_OCTL0 BIT(0)"
.LASF2602:
	.string	"TIMER_ETP_FALLING TIMER_SMCFG_ETP"
.LASF2026:
	.string	"DBG_CTL_STB_HOLD BIT(2)"
.LASF2493:
	.string	"TIMER_EVENT_SRC_BRKG ((uint16_t)0x0080U)"
.LASF1978:
	.string	"I2C_PEC_ENABLE I2C_CTL0_PECEN"
.LASF1966:
	.string	"I2C_DUADEN_DISABLE ((uint32_t)0x00000000U)"
.LASF2541:
	.string	"TIMER_OCN_IDLE_STATE_LOW ((uint16_t)0x0000U)"
.LASF56:
	.string	"__UINT_LEAST64_TYPE__ long long unsigned int"
.LASF1585:
	.string	"OB_WP_22 ((uint32_t)0x00400000U)"
.LASF1123:
	.string	"CRC_DATA_DATA BITS(0, 31)"
.LASF1960:
	.string	"I2C_RECEIVER ((uint32_t)0x00000001U)"
.LASF2863:
	.string	"RCU_CTL_PLL1EN BIT(26)"
.LASF241:
	.string	"__FLT128_MAX_10_EXP__ 4932"
.LASF1368:
	.string	"EXTI_FTEN REG32(EXTI + 0x0CU)"
.LASF2802:
	.string	"TIMER_MTIMECMP_size 0x8"
.LASF2797:
	.string	"_GCC_MAX_ALIGN_T "
.LASF1542:
	.string	"WS_WSCNT_0 WS_WSCNT(0)"
.LASF1283:
	.string	"DMA_FLAG_ADD(flag,shift) ((flag) << ((shift) * 4U))"
.LASF683:
	.string	"ADC_INT_FLAG_EOC ADC_STAT_EOC"
.LASF2269:
	.string	"TIMER_SMCFG(timerx) REG32((timerx) + 0x08U)"
.LASF51:
	.string	"__INT_LEAST32_TYPE__ long int"
.LASF866:
	.string	"CAN_F22DATA1(canx) REG32((canx) + 0x2F4U)"
.LASF2639:
	.string	"USART_CTL0_RBNEIE BIT(5)"
.LASF1907:
	.string	"I2C_CTL1_I2CCLK BITS(0,5)"
.LASF374:
	.string	"_SYS__INTSUP_H "
.LASF913:
	.string	"CAN_TSTAT_MAL2 BIT(18)"
.LASF2239:
	.string	"SPI_I2S_INT_FLAG_RBNE ((uint8_t)0x01U)"
.LASF2470:
	.string	"TIMER_DMACFG_DMATC_3TRANSFER DMACFG_DMATC(2)"
.LASF3109:
	.string	"RCU_PREDV0_DIV7 CFG1_PREDV0(6)"
.LASF2181:
	.string	"SPI_TRANSMODE_BDRECEIVE SPI_CTL0_BDEN"
.LASF2668:
	.string	"USART_GP_PSC BITS(0,7)"
.LASF799:
	.string	"CAN_TMI2(canx) REG32((canx) + 0x1A0U)"
.LASF2898:
	.string	"RCU_INT_HXTALSTBIC BIT(19)"
.LASF2380:
	.string	"TIMER_CHCTL2_CH0NP BIT(3)"
.LASF810:
	.string	"CAN_RFIFOMDATA11(canx) REG32((canx) + 0x1CCU)"
.LASF2843:
	.string	"RCU_APB2RST REG32(RCU + 0x0CU)"
.LASF1589:
	.string	"OB_WP_26 ((uint32_t)0x04000000U)"
.LASF2872:
	.string	"RCU_CFG0_ADCPSC BITS(14,15)"
.LASF1197:
	.string	"DAC_WAVE_BIT_WIDTH_11 DWBW(10)"
.LASF2255:
	.string	"I2S_FLAG_TXURERR SPI_STAT_TXURERR"
.LASF390:
	.string	"long +4"
.LASF1266:
	.string	"DMA_INTC_HTFIFC BIT(2)"
.LASF3397:
	.string	"rcu_periph_reset_disable"
.LASF1072:
	.string	"CAN_BT_BS1_15TQ ((uint8_t)0x0EU)"
.LASF2676:
	.string	"USART_STAT_REG_OFFSET (0x00000000U)"
.LASF2707:
	.string	"CTL1_CPH(regval) (BIT(9) & ((uint32_t)(regval) << 9))"
.LASF3229:
	.string	"RCU_TIMER0"
.LASF3014:
	.string	"RCU_CKSYSSRC_PLL CFG0_SCS(2)"
.LASF1897:
	.string	"I2C_CTL0_PECEN BIT(5)"
.LASF159:
	.string	"__FLT_HAS_QUIET_NAN__ 1"
.LASF631:
	.string	"ADC0_1_EXTTRIG_INSERTED_T0_TRGO CTL1_ETSIC(0)"
.LASF2985:
	.string	"RCU_RSTSCK_WWDGTRSTF BIT(30)"
.LASF2611:
	.string	"UART3 (USART_BASE+(0x00000800U))"
.LASF2040:
	.string	"DBG_LOW_POWER_SLEEP DBG_CTL_SLP_HOLD"
.LASF590:
	.string	"ADC_ISQ_IL BITS(20,21)"
.LASF446:
	.string	"INT32_MAX (__INT32_MAX__)"
.LASF404:
	.string	"__LEAST64 \"ll\""
.LASF681:
	.string	"ADC_INT_EOIC ADC_STAT_EOIC"
.LASF2514:
	.string	"TIMER_IOS_STATE_DISABLE ((uint16_t)0x0000U)"
.LASF1:
	.string	"__STDC_VERSION__ 201710L"
.LASF233:
	.string	"__FLT64_HAS_DENORM__ 1"
.LASF2433:
	.string	"TIMER_FLAG_BRK TIMER_INTF_BRKIF"
.LASF912:
	.string	"CAN_TSTAT_MTFNERR2 BIT(17)"
.LASF3122:
	.string	"RCU_PREDV1_DIV3 CFG1_PREDV1(2)"
.LASF2520:
	.string	"TIMER_CCHP_PROT_OFF CCHP_PROT(0)"
.LASF3334:
	.string	"pll1mf"
.LASF658:
	.string	"ADC_INSERTED_CHANNEL_1 ((uint8_t)0x01U)"
.LASF3314:
	.string	"RCU_PLL1_CK"
.LASF136:
	.string	"__INTPTR_MAX__ 0x7fffffff"
.LASF889:
	.string	"CAN_CTL_TTC BIT(7)"
.LASF1296:
	.string	"DMA_INT_FLAG_ERR DMA_INTF_ERRIF"
.LASF1289:
	.string	"DMA_CHCNT_RESET_VALUE ((uint32_t)0x00000000U)"
.LASF2058:
	.string	"CTL_LVDT(regval) (BITS(5,7)&((uint32_t)(regval) << 5))"
.LASF224:
	.string	"__FLT64_MIN_10_EXP__ (-307)"
.LASF1746:
	.string	"GPIO_LOCK_LK14 BIT(14)"
.LASF2319:
	.string	"TIMER_DMAINTEN_CMTIE BIT(5)"
.LASF2870:
	.string	"RCU_CFG0_APB1PSC BITS(8,10)"
.LASF607:
	.string	"CTL0_SYNCM(regval) (BITS(16,19) & ((uint32_t)(regval) << 16))"
.LASF1531:
	.string	"FMC_REGIDX_BITS(regidx,bitpos0,bitpos1) (((uint32_t)(regidx) << 12) | ((uint32_t)(bitpos0) << 6) | (uint32_t)(bitpos1))"
.LASF1755:
	.string	"AFIO_PCF0_USART1_REMAP BIT(3)"
.LASF2180:
	.string	"SPI_TRANSMODE_RECEIVEONLY SPI_CTL0_RO"
.LASF558:
	.string	"ADC_CTL0_EOCIE BIT(5)"
.LASF1821:
	.string	"GPIO_EVENT_PIN_14 ((uint8_t)0x0EU)"
.LASF1370:
	.string	"EXTI_PD REG32(EXTI + 0x14U)"
.LASF2519:
	.string	"CCHP_PROT(regval) ((uint16_t)(BITS(8, 9) & ((uint32_t)(regval) << 8U)))"
.LASF2677:
	.string	"USART_CTL0_REG_OFFSET (0x0000000CU)"
.LASF394:
	.string	"__INT16 \"h\""
.LASF2424:
	.string	"TIMER_INT_FLAG_TRG TIMER_INT_TRG"
.LASF3088:
	.string	"RCU_CKOUT0SRC_NONE CFG0_CKOUT0SEL(0)"
.LASF3236:
	.string	"RCU_USBFSRST"
.LASF2052:
	.string	"PMU_CTL_LVDT BITS(5,7)"
.LASF2922:
	.string	"RCU_APB1RST_SPI2RST BIT(15)"
.LASF3178:
	.string	"__uint8_t"
.LASF167:
	.string	"__DBL_MAX__ ((double)1.79769313486231570814527423731704357e+308L)"
.LASF2134:
	.string	"SPI_CTL0_LF BIT(7)"
.LASF2964:
	.string	"RCU_APB1EN_UART4EN BIT(20)"
.LASF601:
	.string	"ADC_FLAG_EOIC ADC_STAT_EOIC"
.LASF1129:
	.string	"DAC1 (1U)"
.LASF680:
	.string	"ADC_INT_EOC ADC_STAT_EOC"
.LASF2799:
	.string	"TIMER_MSIP 0xFFC"
.LASF2793:
	.string	"NULL"
.LASF782:
	.string	"CAN1 (CAN0 + 0x00000400U)"
.LASF3154:
	.string	"RCU_PLL2_MUL14 CFG1_PLL2MF(12)"
.LASF3370:
	.string	"rcu_usb_clock_config"
.LASF1347:
	.string	"EXMC_SNTCFG_ASET BITS(0,3)"
.LASF117:
	.string	"__UINT8_C(c) c"
.LASF2242:
	.string	"SPI_INT_FLAG_CRCERR ((uint8_t)0x04U)"
.LASF2986:
	.string	"RCU_RSTSCK_LPRSTF BIT(31)"
.LASF331:
	.string	"__I volatile const"
.LASF1892:
	.string	"I2C_FMPCFG(i2cx) REG32((i2cx) + 0x90U)"
.LASF1003:
	.string	"TSTAT_REG_OFFSET ((uint8_t)0x08U)"
.LASF2517:
	.string	"TIMER_OUTAUTO_ENABLE ((uint16_t)TIMER_CCHP_OAEN)"
.LASF936:
	.string	"CAN_INTEN_RFFIE1 BIT(5)"
.LASF2827:
	.string	"ECLIC_ADDR_BASE 0xd2000000"
.LASF1714:
	.string	"GPIO_BOP_CR14 BIT(30)"
.LASF649:
	.string	"WDHT_WDHT(regval) (BITS(0,11) & ((uint32_t)(regval) << 0))"
.LASF2776:
	.string	"__wchar_t__ "
.LASF228:
	.string	"__FLT64_MAX__ 1.79769313486231570814527423731704357e+308F64"
.LASF3016:
	.string	"RCU_SCSS_IRC8M CFG0_SCSS(0)"
.LASF176:
	.string	"__LDBL_DIG__ 33"
.LASF1093:
	.string	"CAN_MODE_INITIALIZE ((uint8_t)0x01U)"
.LASF2656:
	.string	"USART_CTL1_LMEN BIT(14)"
.LASF3280:
	.string	"RCU_FLAG_WWDGTRST"
.LASF34:
	.string	"__WCHAR_TYPE__ int"
.LASF978:
	.string	"CAN_RFIFOMP_FI BITS(8,15)"
.LASF1883:
	.string	"I2C_CTL0(i2cx) REG32((i2cx) + 0x00U)"
.LASF846:
	.string	"CAN_F2DATA1(canx) REG32((canx) + 0x254U)"
.LASF1637:
	.string	"GPIO_CTL1_CTL8 BITS(2, 3)"
.LASF1364:
	.string	"EXTI EXTI_BASE"
.LASF2039:
	.string	"DBG_CTL_CAN1_HOLD BIT(21)"
.LASF2003:
	.string	"PSC_PSC(regval) (BITS(0,2) & ((uint32_t)(regval) << 0))"
.LASF1780:
	.string	"AFIO_EXTI13_SS BITS(4, 7)"
.LASF1398:
	.string	"EXTI_EVEN_EVEN8 BIT(8)"
.LASF324:
	.string	"GD32VF103V_EVAL 1"
.LASF1338:
	.string	"EXMC_SNCTL_NRBKEN BIT(0)"
.LASF2025:
	.string	"DBG_CTL_DSLP_HOLD BIT(1)"
.LASF643:
	.string	"ADC_SAMPLETIME_28POINT5 SAMPTX_SPT(3)"
.LASF2886:
	.string	"RCU_INT_PLL2STBIF BIT(6)"
.LASF84:
	.string	"__WCHAR_WIDTH__ 32"
.LASF3318:
	.string	"CK_AHB"
.LASF3015:
	.string	"CFG0_SCSS(regval) (BITS(2,3) & ((uint32_t)(regval) << 2))"
.LASF688:
	.string	"ADC_RESOLUTION_8B OVSCR_DRES(2)"
.LASF514:
	.string	"BKP_BASE (APB1_BUS_BASE + 0x00006C00U)"
.LASF3083:
	.string	"RCU_CKUSB_CKPLL_DIV1_5 CFG0_USBPSC(0)"
.LASF689:
	.string	"ADC_RESOLUTION_6B OVSCR_DRES(3)"
.LASF3102:
	.string	"CFG1_PREDV0(regval) (BITS(0,3) & ((uint32_t)(regval) << 0))"
.LASF773:
	.string	"OCTL_RCCV(regval) (BITS(0,6) & ((uint32_t)(regval) << 0))"
.LASF2579:
	.string	"TIMER_TRI_OUT_SRC_ENABLE CTL1_MMC(1)"
.LASF3124:
	.string	"RCU_PREDV1_DIV5 CFG1_PREDV1(4)"
.LASF968:
	.string	"CAN_TMDATA0_DB3 BITS(24,31)"
.LASF2110:
	.string	"RTC_INT_FLAG_OVERFLOW RTC_CTL_OVIF"
.LASF2065:
	.string	"PMU_LVDT_6 CTL_LVDT(6)"
.LASF1915:
	.string	"I2C_SADDR0_ADDRESS_H BITS(8,9)"
.LASF1103:
	.string	"CAN_TIMEOUT ((uint32_t)0x0000FFFFU)"
.LASF1106:
	.string	"CAN_INT_RFF0 CAN_INTEN_RFFIE0"
.LASF2373:
	.string	"TIMER_CHCTL1_CH2CAPPSC BITS(2,3)"
.LASF1574:
	.string	"OB_WP_11 ((uint32_t)0x00000800U)"
.LASF381:
	.string	"__int20__"
.LASF81:
	.string	"__INT_WIDTH__ 32"
.LASF766:
	.string	"BKP_TPCS_TIR BIT(1)"
.LASF1484:
	.string	"EXTI_PD_PD18 BIT(18)"
.LASF3317:
	.string	"CK_SYS"
.LASF613:
	.string	"ADC_DAUL_INSERTED_PARALLEL CTL0_SYNCM(5)"
.LASF438:
	.string	"UINT_LEAST8_MAX (__UINT_LEAST8_MAX__)"
.LASF1660:
	.string	"GPIO_ISTAT_ISTAT8 BIT(8)"
.LASF3357:
	.string	"rcu_interrupt_enable"
.LASF400:
	.string	"__FAST64 \"ll\""
.LASF1134:
	.string	"DAC0_R8DH REG32(DAC + 0x10U)"
.LASF3114:
	.string	"RCU_PREDV0_DIV12 CFG1_PREDV0(11)"
.LASF1587:
	.string	"OB_WP_24 ((uint32_t)0x01000000U)"
.LASF865:
	.string	"CAN_F21DATA1(canx) REG32((canx) + 0x2ECU)"
.LASF1054:
	.string	"CAN_BT_SJW_1TQ ((uint8_t)0x00U)"
.LASF142:
	.string	"__FLT_EVAL_METHOD_TS_18661_3__ 0"
.LASF30:
	.string	"__FLOAT_WORD_ORDER__ __ORDER_LITTLE_ENDIAN__"
.LASF1922:
	.string	"I2C_STAT0_BTC BIT(2)"
.LASF33:
	.string	"__PTRDIFF_TYPE__ int"
.LASF988:
	.string	"CAN_FCTL_FLD BIT(0)"
.LASF1427:
	.string	"EXTI_RTEN_RTEN18 BIT(18)"
.LASF2678:
	.string	"USART_CTL1_REG_OFFSET (0x00000010U)"
.LASF1439:
	.string	"EXTI_FTEN_FTEN11 BIT(11)"
.LASF113:
	.string	"__INT_LEAST64_MAX__ 0x7fffffffffffffffLL"
.LASF93:
	.string	"__SIG_ATOMIC_MAX__ 0x7fffffff"
.LASF1898:
	.string	"I2C_CTL0_GCEN BIT(6)"
.LASF1040:
	.string	"ERR_ERRN(regval) (BITS(4,6) & ((uint32_t)(regval) << 4))"
.LASF1996:
	.string	"FWDGT_RLD REG32((FWDGT) + 0x00000008U)"
.LASF2437:
	.string	"TIMER_FLAG_CH3O TIMER_INTF_CH3OF"
.LASF1799:
	.string	"GPIO_EVENT_PORT_GPIOC ((uint8_t)0x02U)"
.LASF1004:
	.string	"RFIFO0_REG_OFFSET ((uint8_t)0x0CU)"
.LASF624:
	.string	"ADC0_1_EXTTRIG_REGULAR_T0_CH2 CTL1_ETSRC(2)"
.LASF3131:
	.string	"RCU_PREDV1_DIV12 CFG1_PREDV1(11)"
.LASF1846:
	.string	"GPIO_PIN_7 BIT(7)"
.LASF959:
	.string	"CAN_TMI_FF BIT(2)"
.LASF2020:
	.string	"DBG DBG_BASE"
.LASF1606:
	.string	"GPIO_CTL0(gpiox) REG32((gpiox) + 0x00U)"
.LASF2457:
	.string	"TIMER_DMACFG_DMATA_CNT DMACFG_DMATA(9)"
.LASF2430:
	.string	"TIMER_FLAG_CH3 TIMER_INTF_CH3IF"
.LASF3364:
	.string	"flag"
.LASF1391:
	.string	"EXTI_EVEN_EVEN1 BIT(1)"
.LASF977:
	.string	"CAN_RFIFOMP_DLENC BITS(0,3)"
.LASF3190:
	.string	"FlagStatus"
.LASF1435:
	.string	"EXTI_FTEN_FTEN7 BIT(7)"
.LASF2768:
	.string	"_SIZE_T_DEFINED "
.LASF2449:
	.string	"TIMER_DMACFG_DMATA_CTL1 DMACFG_DMATA(1)"
.LASF2030:
	.string	"DBG_CTL_TIMER1_HOLD BIT(11)"
.LASF3385:
	.string	"rcu_ckout0_config"
.LASF3043:
	.string	"RCU_CKADC_CKAPB2_DIV6 ((uint32_t)0x00000002U)"
.LASF1573:
	.string	"OB_WP_10 ((uint32_t)0x00000400U)"
.LASF3040:
	.string	"RCU_APB2_CKAHB_DIV16 CFG0_APB2PSC(7)"
.LASF2021:
	.string	"DBG_ID REG32(DBG + 0x00U)"
.LASF17:
	.string	"__SIZEOF_LONG__ 4"
.LASF2007:
	.string	"FWDGT_PSC_DIV32 ((uint8_t)PSC_PSC(3))"
.LASF2596:
	.string	"TIMER_MASTER_SLAVE_MODE_DISABLE ((uint32_t)0x00000000U)"
.LASF1592:
	.string	"OB_WP_29 ((uint32_t)0x20000000U)"
.LASF395:
	.string	"__INT32 \"l\""
.LASF761:
	.string	"BKP_OCTL_ASOEN BIT(8)"
.LASF1293:
	.string	"DMA_INT_FLAG_G DMA_INTF_GIF"
.LASF1562:
	.string	"OB_WP3_WP3 ((uint32_t)0xFF000000U)"
.LASF3038:
	.string	"RCU_APB2_CKAHB_DIV4 CFG0_APB2PSC(5)"
.LASF492:
	.string	"REG16(addr) (*(volatile uint16_t *)(uint32_t)(addr))"
.LASF347:
	.string	"__NEWLIB__ 4"
.LASF1653:
	.string	"GPIO_ISTAT_ISTAT1 BIT(1)"
.LASF2393:
	.string	"TIMER_CAR_CARL BITS(0,15)"
.LASF2789:
	.string	"_GCC_WCHAR_T "
.LASF1267:
	.string	"DMA_INTC_ERRIFC BIT(3)"
.LASF1409:
	.string	"EXTI_RTEN_RTEN0 BIT(0)"
.LASF2947:
	.string	"RCU_APB2EN_ADC0EN BIT(9)"
.LASF2844:
	.string	"RCU_APB1RST REG32(RCU + 0x10U)"
.LASF1750:
	.string	"AFIO_EC_PORT BITS(4, 6)"
.LASF351:
	.string	"__GNUC_PREREQ__(ma,mi) __GNUC_PREREQ(ma, mi)"
.LASF1507:
	.string	"FMC_STAT_PGERR BIT(2)"
.LASF259:
	.string	"__FLT32X_NORM_MAX__ 1.79769313486231570814527423731704357e+308F32x"
.LASF2388:
	.string	"TIMER_CHCTL2_CH2NP BIT(11)"
.LASF2440:
	.string	"TIMER_DMA_CH1D ((uint16_t)TIMER_DMAINTEN_CH1DEN)"
.LASF3235:
	.string	"rcu_periph_sleep_enum"
.LASF2631:
	.string	"USART_DATA_DATA BITS(0,8)"
.LASF365:
	.string	"___int8_t_defined 1"
.LASF1460:
	.string	"EXTI_SWIEV_SWIEV13 BIT(13)"
.LASF2338:
	.string	"TIMER_INTF_CH1OF BIT(10)"
.LASF3258:
	.string	"RCU_GPIOARST"
.LASF460:
	.string	"INT_FAST16_MIN (-__INT_FAST16_MAX__ - 1)"
.LASF2977:
	.string	"RCU_BDCTL_BKPRST BIT(16)"
.LASF932:
	.string	"CAN_INTEN_RFNEIE0 BIT(1)"
.LASF2315:
	.string	"TIMER_DMAINTEN_CH0IE BIT(1)"
.LASF954:
	.string	"CAN_BT_SJW BITS(24,25)"
.LASF2425:
	.string	"TIMER_INT_FLAG_BRK TIMER_INT_BRK"
.LASF2019:
	.string	"GD32VF103_DBG_H "
.LASF440:
	.string	"INT16_MAX (__INT16_MAX__)"
.LASF112:
	.string	"__INT_LEAST32_WIDTH__ 32"
.LASF2125:
	.string	"SPI_RCRC(spix) REG32((spix) + 0x14U)"
.LASF1437:
	.string	"EXTI_FTEN_FTEN9 BIT(9)"
.LASF1193:
	.string	"DAC_WAVE_BIT_WIDTH_7 DWBW(6)"
.LASF267:
	.string	"__FLT64X_DIG__ 33"
.LASF3216:
	.string	"RCU_CAN1"
.LASF2703:
	.string	"USART_LBLEN_11B CTL1_LBLEN(1)"
.LASF1374:
	.string	"EXTI_INTEN_INTEN3 BIT(3)"
.LASF1839:
	.string	"GPIO_PIN_0 BIT(0)"
.LASF1097:
	.string	"CAN_FILTERBITS_32BIT ((uint8_t)0x01U)"
.LASF3213:
	.string	"RCU_I2C0"
.LASF3214:
	.string	"RCU_I2C1"
.LASF828:
	.string	"CAN_F12DATA0(canx) REG32((canx) + 0x2A0U)"
.LASF2001:
	.string	"FWDGT_STAT_PUD BIT(0)"
.LASF637:
	.string	"ADC0_1_EXTTRIG_INSERTED_EXTI_15 CTL1_ETSIC(6)"
.LASF2623:
	.string	"USART_STAT_NERR BIT(2)"
.LASF947:
	.string	"CAN_ERR_BOERR BIT(2)"
.LASF1945:
	.string	"I2C_RT_RISETIME BITS(0,5)"
.LASF2366:
	.string	"TIMER_CHCTL1_CH2COMCTL BITS(4,6)"
.LASF3347:
	.string	"rcu_osci_bypass_mode_enable"
.LASF261:
	.string	"__FLT32X_EPSILON__ 2.22044604925031308084726333618164062e-16F32x"
.LASF3278:
	.string	"RCU_FLAG_SWRST"
.LASF2987:
	.string	"RCU_AHBRST_USBFSRST BIT(12)"
.LASF3194:
	.string	"long double"
.LASF2754:
	.string	"___int_ptrdiff_t_h "
.LASF1499:
	.string	"OB_WP0 REG16((OB) + 0x08U)"
.LASF1582:
	.string	"OB_WP_19 ((uint32_t)0x00080000U)"
.LASF2749:
	.string	"_T_PTRDIFF_ "
.LASF2050:
	.string	"PMU_CTL_STBRST BIT(3)"
.LASF1930:
	.string	"I2C_STAT0_OUERR BIT(11)"
.LASF2247:
	.string	"SPI_FLAG_CRCERR SPI_STAT_CRCERR"
.LASF2292:
	.string	"TIMER_CTL0_CAM BITS(5,6)"
.LASF1504:
	.string	"FMC_KEY_KEY BITS(0,31)"
.LASF1584:
	.string	"OB_WP_21 ((uint32_t)0x00200000U)"
.LASF2919:
	.string	"RCU_APB1RST_TIMER6RST BIT(5)"
.LASF3150:
	.string	"RCU_PLL2_MUL10 CFG1_PLL2MF(8)"
.LASF3289:
	.string	"RCU_INT_FLAG_PLL2STB"
.LASF481:
	.string	"INT8_C(x) __INT8_C(x)"
.LASF3282:
	.string	"rcu_flag_enum"
.LASF1171:
	.string	"DAC0_DO_DAC0_DO BITS(0,11)"
.LASF2744:
	.string	"N200_FUNC_H "
.LASF1694:
	.string	"GPIO_BOP_BOP10 BIT(10)"
.LASF788:
	.string	"CAN_INTEN(canx) REG32((canx) + 0x14U)"
.LASF1627:
	.string	"GPIO_CTL0_CTL3 BITS(14, 15)"
.LASF2551:
	.string	"TIMER_OC_SHADOW_DISABLE ((uint16_t)0x0000U)"
.LASF309:
	.string	"__riscv_xlen 32"
.LASF1710:
	.string	"GPIO_BOP_CR10 BIT(26)"
.LASF2122:
	.string	"SPI_STAT(spix) REG32((spix) + 0x08U)"
.LASF2771:
	.string	"___int_size_t_h "
.LASF2374:
	.string	"TIMER_CHCTL1_CH2CAPFLT BITS(4,7)"
.LASF1459:
	.string	"EXTI_SWIEV_SWIEV12 BIT(12)"
.LASF2505:
	.string	"TIMER_CKDIV_DIV2 CTL0_CKDIV(1)"
.LASF2381:
	.string	"TIMER_CHCTL2_CH1EN BIT(4)"
.LASF3331:
	.string	"clk_exp"
.LASF2111:
	.string	"RTC_FLAG_SECOND RTC_CTL_SCIF"
.LASF1564:
	.string	"OB_WP_1 ((uint32_t)0x00000002U)"
.LASF231:
	.string	"__FLT64_EPSILON__ 2.22044604925031308084726333618164062e-16F64"
.LASF1125:
	.string	"CRC_CTL_RST BIT(0)"
.LASF3313:
	.string	"RCU_PLL_CK"
.LASF2436:
	.string	"TIMER_FLAG_CH2O TIMER_INTF_CH2OF"
.LASF1815:
	.string	"GPIO_EVENT_PIN_8 ((uint8_t)0x08U)"
.LASF3302:
	.string	"RCU_INT_LXTALSTB"
.LASF1196:
	.string	"DAC_WAVE_BIT_WIDTH_10 DWBW(9)"
.LASF809:
	.string	"CAN_RFIFOMDATA01(canx) REG32((canx) + 0x1C8U)"
.LASF277:
	.string	"__FLT64X_DENORM_MIN__ 6.47517511943802511092443895822764655e-4966F64x"
.LASF2290:
	.string	"TIMER_CTL0_SPM BIT(3)"
.LASF2049:
	.string	"PMU_CTL_WURST BIT(2)"
.LASF874:
	.string	"CAN_TMDATA0(canx,bank) REG32((canx) + 0x188U + ((bank) * 0x10U))"
.LASF158:
	.string	"__FLT_HAS_INFINITY__ 1"
.LASF2012:
	.string	"FWDGT_WRITEACCESS_DISABLE ((uint16_t)0x0000U)"
.LASF3156:
	.string	"RCU_PLL2_MUL16 CFG1_PLL2MF(14)"
.LASF2233:
	.string	"SPI_CRC_TX ((uint8_t)0x00U)"
.LASF73:
	.string	"__WCHAR_MAX__ 0x7fffffff"
.LASF3128:
	.string	"RCU_PREDV1_DIV9 CFG1_PREDV1(8)"
.LASF3232:
	.string	"rcu_periph_enum"
.LASF2711:
	.string	"USART_CPL_LOW CTL1_CPL(0)"
.LASF2536:
	.string	"TIMER_OCN_POLARITY_HIGH ((uint16_t)0x0000U)"
.LASF3126:
	.string	"RCU_PREDV1_DIV7 CFG1_PREDV1(6)"
.LASF1219:
	.string	"DAC_TRIANGLE_AMPLITUDE_31 DAC_WAVE_BIT_WIDTH_5"
.LASF2855:
	.string	"RCU_CTL_IRC8MADJ BITS(3,7)"
.LASF525:
	.string	"USBFS_BASE (AHB1_BUS_BASE + 0x0FFE8000U)"
.LASF2577:
	.string	"CTL1_MMC(regval) (BITS(4, 6) & ((uint32_t)(regval) << 4U))"
.LASF2975:
	.string	"RCU_BDCTL_RTCSRC BITS(8,9)"
.LASF661:
	.string	"ADC_CHANNEL_0 ((uint8_t)0x00U)"
.LASF209:
	.string	"__FLT32_MIN_10_EXP__ (-37)"
.LASF122:
	.string	"__UINT_LEAST64_MAX__ 0xffffffffffffffffULL"
.LASF3222:
	.string	"RCU_GPIOA"
.LASF2595:
	.string	"TIMER_MASTER_SLAVE_MODE_ENABLE TIMER_SMCFG_MSM"
.LASF3226:
	.string	"RCU_GPIOE"
.LASF3237:
	.string	"RCU_TIMER1RST"
.LASF1951:
	.string	"I2C_REG_VAL2(i2cx,offset) (REG32((i2cx) + ((uint32_t)(offset) >> 22)))"
.LASF269:
	.string	"__FLT64X_MIN_10_EXP__ (-4931)"
.LASF602:
	.string	"ADC_FLAG_STIC ADC_STAT_STIC"
.LASF2835:
	.string	"ECLIC_GROUP_LEVEL1_PRIO3 1"
.LASF306:
	.string	"__riscv_mul 1"
.LASF2414:
	.string	"TIMER_INT_CH3 TIMER_DMAINTEN_CH3IE"
.LASF2728:
	.string	"GD32VF103_WWDGT_H "
.LASF64:
	.string	"__UINT_FAST64_TYPE__ long long unsigned int"
.LASF2674:
	.string	"USART_REG_VAL2(usartx,offset) (REG32((usartx) + ((uint32_t)(offset) >> 22)))"
.LASF922:
	.string	"CAN_TSTAT_TMLS2 BIT(31)"
.LASF2328:
	.string	"TIMER_DMAINTEN_TRGDEN BIT(14)"
.LASF3169:
	.string	"SEL_IRC8M ((uint16_t)0U)"
.LASF146:
	.string	"__FLT_DIG__ 6"
.LASF933:
	.string	"CAN_INTEN_RFFIE0 BIT(2)"
.LASF455:
	.string	"INT_LEAST64_MAX (__INT_LEAST64_MAX__)"
.LASF276:
	.string	"__FLT64X_EPSILON__ 1.92592994438723585305597794258492732e-34F64x"
.LASF1597:
	.string	"FMC_SIZE (*(uint16_t *)0x1FFFF7E0U)"
.LASF2253:
	.string	"I2S_FLAG_TBE SPI_STAT_TBE"
.LASF1756:
	.string	"AFIO_PCF0_USART2_REMAP BITS(4, 5)"
.LASF1871:
	.string	"GPIO_CAN0_FULL_REMAP ((uint32_t)0x001D6000U)"
.LASF2191:
	.string	"SPI_CK_PL_LOW_PH_2EDGE SPI_CTL0_CKPH"
.LASF3045:
	.string	"RCU_CKADC_CKAPB2_DIV12 ((uint32_t)0x00000005U)"
.LASF911:
	.string	"CAN_TSTAT_MTF2 BIT(16)"
.LASF1566:
	.string	"OB_WP_3 ((uint32_t)0x00000008U)"
.LASF1309:
	.string	"DMA_MEMORY_INCREASE_ENABLE ((uint8_t)0x01U)"
.LASF918:
	.string	"CAN_TSTAT_TME1 BIT(27)"
.LASF820:
	.string	"CAN_F4DATA0(canx) REG32((canx) + 0x260U)"
.LASF2877:
	.string	"RCU_CFG0_CKOUT0SEL BITS(24,27)"
.LASF3198:
	.string	"RCU_EXMC"
.LASF2069:
	.string	"PMU_FLAG_LVD PMU_CS_LVDF"
.LASF490:
	.string	"UINTMAX_C(x) __UINTMAX_C(x)"
.LASF1359:
	.string	"EXMC_MEMORY_TYPE_NOR SNCTL_NRTP(2)"
.LASF2999:
	.string	"AHBEN_REG_OFFSET 0x14U"
.LASF596:
	.string	"ADC_OVSCR_OVSS BITS(5,8)"
.LASF1956:
	.string	"I2C_I2CMODE_ENABLE ((uint32_t)0x00000000U)"
.LASF2560:
	.string	"TIMER_IC_POLARITY_BOTH_EDGE ((uint16_t)0x000AU)"
.LASF314:
	.string	"__riscv_m 2000000"
.LASF1959:
	.string	"I2C_SMBUS_HOST I2C_CTL0_SMBSEL"
.LASF1962:
	.string	"I2C_ACK_DISABLE ((uint32_t)0x00000000U)"
.LASF179:
	.string	"__LDBL_MAX_EXP__ 16384"
.LASF1560:
	.string	"OB_WP1_WP1 ((uint32_t)0x0000FF00U)"
.LASF23:
	.string	"__SIZEOF_SIZE_T__ 4"
.LASF338:
	.string	"IRC8M_STARTUP_TIMEOUT ((uint16_t)0x0500)"
.LASF1719:
	.string	"GPIO_BC_CR3 BIT(3)"
.LASF3052:
	.string	"RCU_PLL_MUL3 CFG0_PLLMF(1)"
.LASF1543:
	.string	"WS_WSCNT_1 WS_WSCNT(1)"
.LASF1102:
	.string	"CAN_FT_REMOTE ((uint32_t)0x00000002U)"
.LASF1242:
	.string	"DMA_CH2PADDR(dmax) REG32((dmax) + 0x38U)"
.LASF1512:
	.string	"FMC_CTL_MER BIT(2)"
.LASF1958:
	.string	"I2C_SMBUS_DEVICE ((uint32_t)0x00000000U)"
.LASF1318:
	.string	"CHCTL_PRIO(regval) (BITS(12,13) & ((uint32_t)(regval) << 12))"
.LASF2614:
	.string	"USART_STAT(usartx) REG32((usartx) + (0x00000000U))"
.LASF2925:
	.string	"RCU_APB1RST_UART3RST BIT(19)"
.LASF2445:
	.string	"TIMER_DMAREQUEST_UPDATEEVENT TIMER_CTL1_DMAS"
.LASF255:
	.string	"__FLT32X_MAX_EXP__ 1024"
.LASF629:
	.string	"ADC0_1_EXTTRIG_REGULAR_NONE CTL1_ETSRC(7)"
.LASF2812:
	.string	"_BITUL(x) (_AC(1,UL) << (x))"
.LASF3253:
	.string	"RCU_CAN1RST"
.LASF1708:
	.string	"GPIO_BOP_CR8 BIT(24)"
.LASF108:
	.string	"__INT16_C(c) c"
.LASF1731:
	.string	"GPIO_BC_CR15 BIT(15)"
.LASF104:
	.string	"__INT_LEAST8_MAX__ 0x7f"
.LASF3325:
	.string	"apb1_freq"
.LASF2034:
	.string	"DBG_CTL_I2C0_HOLD BIT(15)"
.LASF382:
	.string	"long"
.LASF2805:
	.string	"TIMER_CTRL_ADDR 0xd1000000"
.LASF2491:
	.string	"TIMER_EVENT_SRC_CMTG ((uint16_t)0x0020U)"
.LASF2907:
	.string	"RCU_APB2RST_PDRST BIT(5)"
.LASF1482:
	.string	"EXTI_PD_PD16 BIT(16)"
.LASF1274:
	.string	"DMA_CHXCTL_PNAGA BIT(6)"
.LASF2353:
	.string	"TIMER_CHCTL0_CH0COMCEN BIT(7)"
.LASF63:
	.string	"__UINT_FAST32_TYPE__ unsigned int"
.LASF2720:
	.string	"USART_RTS_ENABLE CLT2_RTSEN(1)"
.LASF356:
	.string	"__LARGEFILE_VISIBLE 0"
.LASF1853:
	.string	"GPIO_PIN_14 BIT(14)"
.LASF1174:
	.string	"DAC_TRIGGER_T5_TRGO CTL_DTSEL(0)"
.LASF2077:
	.string	"RTC RTC_BASE"
.LASF952:
	.string	"CAN_BT_BS1 BITS(16,19)"
.LASF1473:
	.string	"EXTI_PD_PD7 BIT(7)"
.LASF1121:
	.string	"CRC_FDATA REG32(CRC + 0x04U)"
.LASF2882:
	.string	"RCU_INT_IRC8MSTBIF BIT(2)"
.LASF1546:
	.string	"OB_FWDGT_HW ((uint8_t)0x00U)"
.LASF1969:
	.string	"I2C_SCLSTRETCH_DISABLE I2C_CTL0_SS"
.LASF1012:
	.string	"FDATA_MASK_HIGH(regval) (BITS(16,31) & ((uint32_t)(regval) << 16))"
.LASF2980:
	.string	"RCU_RSTSCK_RSTFC BIT(24)"
.LASF999:
	.string	"CAN_REG_VALS(canx,offset) (REG32((canx) + ((uint32_t)(offset) >> 12)))"
.LASF1672:
	.string	"GPIO_OCTL_OCTL4 BIT(4)"
.LASF49:
	.string	"__INT_LEAST8_TYPE__ signed char"
.LASF1444:
	.string	"EXTI_FTEN_FTEN16 BIT(16)"
.LASF1288:
	.string	"DMA_CHCTL_RESET_VALUE ((uint32_t)0x00000000U)"
.LASF786:
	.string	"CAN_RFIFO0(canx) REG32((canx) + 0x0CU)"
.LASF1327:
	.string	"ECLIC_PRIGROUP_LEVEL0_PRIO4 0"
.LASF2660:
	.string	"USART_CTL2_HDEN BIT(3)"
.LASF1209:
	.string	"DAC_LFSR_BITS10_0 DAC_WAVE_BIT_WIDTH_11"
.LASF2988:
	.string	"RCU_CFG1_PREDV0 BITS(0,3)"
.LASF1453:
	.string	"EXTI_SWIEV_SWIEV6 BIT(6)"
.LASF1361:
	.string	"EXMC_NWAIT_POLARITY_LOW ((uint32_t)0x00000000U)"
.LASF253:
	.string	"__FLT32X_MIN_EXP__ (-1021)"
.LASF3350:
	.string	"rcu_clock_freq_get"
.LASF368:
	.string	"___int64_t_defined 1"
.LASF2200:
	.string	"SPI_PSC_128 CTL0_PSC(6)"
.LASF196:
	.string	"__FLT16_MAX_10_EXP__ 4"
.LASF1057:
	.string	"CAN_BT_SJW_4TQ ((uint8_t)0x03U)"
.LASF3321:
	.string	"rcu_clock_freq_enum"
.LASF3008:
	.string	"INT_REG_OFFSET 0x08U"
.LASF229:
	.string	"__FLT64_NORM_MAX__ 1.79769313486231570814527423731704357e+308F64"
.LASF2059:
	.string	"PMU_LVDT_0 CTL_LVDT(0)"
.LASF3404:
	.string	"rcu_periph_clock_enable"
.LASF358:
	.string	"__POSIX_VISIBLE 199009"
.LASF1260:
	.string	"DMA_INTF_GIF BIT(0)"
.LASF1286:
	.string	"DMA_CHPADDR(dma,channel) REG32(((dma) + 0x10U) + 0x14U * (uint32_t)(channel))"
.LASF29:
	.string	"__BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__"
.LASF456:
	.string	"UINT_LEAST64_MAX (__UINT_LEAST64_MAX__)"
.LASF2890:
	.string	"RCU_INT_IRC8MSTBIE BIT(10)"
.LASF1367:
	.string	"EXTI_RTEN REG32(EXTI + 0x08U)"
.LASF640:
	.string	"ADC_SAMPLETIME_1POINT5 SAMPTX_SPT(0)"
.LASF1740:
	.string	"GPIO_LOCK_LK8 BIT(8)"
.LASF1477:
	.string	"EXTI_PD_PD11 BIT(11)"
.LASF2193:
	.string	"CTL0_PSC(regval) (BITS(3,5) & ((uint32_t)(regval) << 3))"
.LASF677:
	.string	"ADC_CHANNEL_16 ((uint8_t)0x10U)"
.LASF953:
	.string	"CAN_BT_BS2 BITS(20,22)"
.LASF1559:
	.string	"OB_WP0_WP0 ((uint32_t)0x000000FFU)"
.LASF226:
	.string	"__FLT64_MAX_10_EXP__ 308"
.LASF311:
	.string	"__riscv_cmodel_medany 1"
.LASF2066:
	.string	"PMU_LVDT_7 CTL_LVDT(7)"
.LASF3135:
	.string	"RCU_PREDV1_DIV16 CFG1_PREDV1(15)"
.LASF2451:
	.string	"TIMER_DMACFG_DMATA_DMAINTEN DMACFG_DMATA(3)"
.LASF3013:
	.string	"RCU_CKSYSSRC_HXTAL CFG0_SCS(1)"
.LASF1333:
	.string	"GD32VF103_EXMC_H "
.LASF257:
	.string	"__FLT32X_DECIMAL_DIG__ 17"
.LASF2473:
	.string	"TIMER_DMACFG_DMATC_6TRANSFER DMACFG_DMATC(5)"
.LASF2580:
	.string	"TIMER_TRI_OUT_SRC_UPDATE CTL1_MMC(2)"
.LASF2716:
	.string	"CLT2_DENT(regval) (BIT(7) & ((uint32_t)(regval) << 7))"
.LASF3157:
	.string	"RCU_PLL2_MUL20 CFG1_PLL2MF(15)"
.LASF3304:
	.string	"RCU_INT_HXTALSTB"
.LASF2190:
	.string	"SPI_CK_PL_HIGH_PH_1EDGE SPI_CTL0_CKPL"
.LASF1454:
	.string	"EXTI_SWIEV_SWIEV7 BIT(7)"
.LASF1420:
	.string	"EXTI_RTEN_RTEN11 BIT(11)"
.LASF1244:
	.string	"DMA_CH3CTL(dmax) REG32((dmax) + 0x44U)"
.LASF2187:
	.string	"SPI_ENDIAN_MSB ((uint32_t)0x00000000U)"
.LASF1217:
	.string	"DAC_TRIANGLE_AMPLITUDE_7 DAC_WAVE_BIT_WIDTH_3"
.LASF1680:
	.string	"GPIO_OCTL_OCTL12 BIT(12)"
.LASF781:
	.string	"CAN0 CAN_BASE"
.LASF2448:
	.string	"TIMER_DMACFG_DMATA_CTL0 DMACFG_DMATA(0)"
.LASF3179:
	.string	"__uint16_t"
.LASF133:
	.string	"__UINT_FAST16_MAX__ 0xffffffffU"
.LASF1868:
	.string	"GPIO_TIMER2_FULL_REMAP ((uint32_t)0x001A0C00U)"
.LASF2014:
	.string	"FWDGT_KEY_ENABLE ((uint16_t)0xCCCCU)"
.LASF2431:
	.string	"TIMER_FLAG_CMT TIMER_INTF_CMTIF"
.LASF2147:
	.string	"SPI_CTL1_TMOD BIT(4)"
.LASF2439:
	.string	"TIMER_DMA_CH0D ((uint16_t)TIMER_DMAINTEN_CH0DEN)"
.LASF1466:
	.string	"EXTI_PD_PD0 BIT(0)"
.LASF120:
	.string	"__UINT_LEAST32_MAX__ 0xffffffffUL"
.LASF1228:
	.string	"DMA0 (DMA_BASE)"
.LASF2336:
	.string	"TIMER_INTF_BRKIF BIT(7)"
.LASF556:
	.string	"ADC_STAT_STRC BIT(4)"
.LASF3022:
	.string	"RCU_AHB_CKSYS_DIV4 CFG0_AHBPSC(9)"
.LASF3297:
	.string	"RCU_INT_FLAG_PLL1STB_CLR"
.LASF1917:
	.string	"I2C_SADDR1_DUADEN BIT(0)"
.LASF3067:
	.string	"RCU_PLL_MUL18 (PLLMF_4 | CFG0_PLLMF(1))"
.LASF448:
	.string	"INT_LEAST32_MIN (-__INT_LEAST32_MAX__ - 1)"
.LASF1820:
	.string	"GPIO_EVENT_PIN_13 ((uint8_t)0x0DU)"
.LASF432:
	.string	"UINTPTR_MAX (__UINTPTR_MAX__)"
.LASF19:
	.string	"__SIZEOF_SHORT__ 2"
.LASF1280:
	.string	"DMA_CHXCNT_CNT BITS(0,15)"
.LASF1064:
	.string	"CAN_BT_BS1_7TQ ((uint8_t)0x06U)"
.LASF408:
	.string	"__int8_t_defined 1"
.LASF1254:
	.string	"DMA_CH5PADDR(dmax) REG32((dmax) + 0x74U)"
.LASF1765:
	.string	"AFIO_PCF0_SPI2_REMAP BIT(28)"
.LASF1299:
	.string	"DMA_FLAG_HTF DMA_INTF_HTFIF"
.LASF35:
	.string	"__WINT_TYPE__ unsigned int"
.LASF3319:
	.string	"CK_APB1"
.LASF3320:
	.string	"CK_APB2"
.LASF1354:
	.string	"EXMC_NOR_DATABUS_WIDTH_8B SNCTL_NRW(0)"
.LASF1112:
	.string	"CAN_INT_PERR CAN_INTEN_PERRIE"
.LASF110:
	.string	"__INT_LEAST32_MAX__ 0x7fffffffL"
.LASF1353:
	.string	"SNCTL_NRW(regval) (BITS(4,5) & ((uint32_t)(regval) << 4))"
.LASF2105:
	.string	"RTC_INT_SECOND RTC_INTEN_SCIE"
.LASF491:
	.string	"REG32(addr) (*(volatile uint32_t *)(uint32_t)(addr))"
.LASF2345:
	.string	"TIMER_SWEVG_CH3G BIT(4)"
.LASF3327:
	.string	"pllsel"
.LASF3032:
	.string	"RCU_APB1_CKAHB_DIV4 CFG0_APB1PSC(5)"
.LASF148:
	.string	"__FLT_MIN_10_EXP__ (-37)"
.LASF1733:
	.string	"GPIO_LOCK_LK1 BIT(1)"
.LASF352:
	.string	"__ATFILE_VISIBLE 0"
.LASF598:
	.string	"ADC_OVSCR_DRES BITS(12,13)"
.LASF2172:
	.string	"SPI_I2SPSC_DIV BITS(0,7)"
.LASF668:
	.string	"ADC_CHANNEL_7 ((uint8_t)0x07U)"
.LASF1335:
	.string	"EXMC_SNCTL0 REG32(EXMC + 0x00U)"
.LASF1935:
	.string	"I2C_STAT1_I2CBSY BIT(1)"
.LASF1098:
	.string	"CAN_FILTERMODE_MASK ((uint8_t)0x00U)"
.LASF1702:
	.string	"GPIO_BOP_CR2 BIT(18)"
.LASF812:
	.string	"CAN_FMCFG(canx) REG32((canx) + 0x204U)"
.LASF892:
	.string	"CAN_STAT_IWS BIT(0)"
.LASF851:
	.string	"CAN_F7DATA1(canx) REG32((canx) + 0x27CU)"
.LASF1860:
	.string	"GPIO_USART2_PARTIAL_REMAP ((uint32_t)0x00140010U)"
.LASF507:
	.string	"RTC_BASE (APB1_BUS_BASE + 0x00002800U)"
.LASF1140:
	.string	"DACC_R8DH REG32(DAC + 0x28U)"
.LASF1699:
	.string	"GPIO_BOP_BOP15 BIT(15)"
.LASF2537:
	.string	"TIMER_OCN_POLARITY_LOW ((uint16_t)0x0008U)"
.LASF979:
	.string	"CAN_RFIFOMP_TS BITS(16,31)"
.LASF574:
	.string	"ADC_CTL1_DMA BIT(8)"
.LASF2552:
	.string	"TIMER_OC_FAST_ENABLE ((uint16_t)0x0004)"
.LASF1094:
	.string	"CAN_MODE_NORMAL ((uint8_t)0x02U)"
.LASF1261:
	.string	"DMA_INTF_FTFIF BIT(1)"
.LASF767:
	.string	"BKP_TPCS_TPIE BIT(2)"
.LASF1464:
	.string	"EXTI_SWIEV_SWIEV17 BIT(17)"
.LASF950:
	.string	"CAN_ERR_RECNT BITS(24,31)"
.LASF1128:
	.string	"DAC0 (0U)"
.LASF969:
	.string	"CAN_TMDATA1_DB4 BITS(0,7)"
.LASF2084:
	.string	"RTC_CNTH REG32(RTC + 0x18U)"
.LASF886:
	.string	"CAN_CTL_ARD BIT(4)"
.LASF1563:
	.string	"OB_WP_0 ((uint32_t)0x00000001U)"
.LASF2775:
	.string	"__need_size_t"
.LASF235:
	.string	"__FLT64_HAS_QUIET_NAN__ 1"
.LASF1654:
	.string	"GPIO_ISTAT_ISTAT2 BIT(2)"
.LASF205:
	.string	"__FLT16_HAS_QUIET_NAN__ 1"
.LASF486:
	.string	"UINT32_C(x) __UINT32_C(x)"
.LASF237:
	.string	"__FLT128_DIG__ 33"
.LASF3029:
	.string	"CFG0_APB1PSC(regval) (BITS(8,10) & ((uint32_t)(regval) << 8))"
.LASF617:
	.string	"ADC_DAUL_INSERTED_TRIGGER_ROTATION CTL0_SYNCM(9)"
.LASF1666:
	.string	"GPIO_ISTAT_ISTAT14 BIT(14)"
.LASF1321:
	.string	"DMA_PRIORITY_HIGH CHCTL_PRIO(2U)"
.LASF2722:
	.string	"CLT2_CTSEN(regval) (BIT(9) & ((uint32_t)(regval) << 9))"
.LASF2578:
	.string	"TIMER_TRI_OUT_SRC_RESET CTL1_MMC(0)"
.LASF1577:
	.string	"OB_WP_14 ((uint32_t)0x00004000U)"
.LASF1404:
	.string	"EXTI_EVEN_EVEN14 BIT(14)"
.LASF2635:
	.string	"USART_CTL0_RWU BIT(1)"
.LASF768:
	.string	"BKP_TPCS_TEF BIT(8)"
.LASF2038:
	.string	"DBG_CTL_TIMER6_HOLD BIT(20)"
.LASF789:
	.string	"CAN_ERR(canx) REG32((canx) + 0x18U)"
.LASF1173:
	.string	"CTL_DTSEL(regval) (BITS(3,5) & ((uint32_t)(regval) << 3))"
.LASF2342:
	.string	"TIMER_SWEVG_CH0G BIT(1)"
.LASF334:
	.string	"HXTAL_VALUE ((uint32_t)8000000)"
.LASF242:
	.string	"__FLT128_DECIMAL_DIG__ 36"
.LASF325:
	.string	"__RTTHREAD__ 1"
.LASF2620:
	.string	"USART_GP(usartx) REG32((usartx) + (0x00000018U))"
.LASF218:
	.string	"__FLT32_HAS_DENORM__ 1"
.LASF2060:
	.string	"PMU_LVDT_1 CTL_LVDT(1)"
.LASF2492:
	.string	"TIMER_EVENT_SRC_TRGG ((uint16_t)0x0040U)"
.LASF189:
	.string	"__LDBL_HAS_INFINITY__ 1"
.LASF2318:
	.string	"TIMER_DMAINTEN_CH3IE BIT(4)"
.LASF1576:
	.string	"OB_WP_13 ((uint32_t)0x00002000U)"
.LASF2359:
	.string	"TIMER_CHCTL0_CH0CAPPSC BITS(2,3)"
.LASF2862:
	.string	"RCU_CTL_PLLSTB BIT(25)"
.LASF2135:
	.string	"SPI_CTL0_SWNSS BIT(8)"
.LASF1344:
	.string	"EXMC_SNCTL_WREN BIT(12)"
.LASF2748:
	.string	"_PTRDIFF_T "
.LASF1113:
	.string	"CAN_INT_BO CAN_INTEN_BOIE"
.LASF2091:
	.string	"RTC_CTL_SCIF BIT(0)"
.LASF1598:
	.string	"SRAM_SIZE (*(uint16_t *)0x1FFFF7E2U)"
.LASF2782:
	.string	"_WCHAR_T_ "
.LASF3080:
	.string	"RCU_PLL_MUL31 (PLLMF_4 | CFG0_PLLMF(14))"
.LASF2400:
	.string	"TIMER_CCHP_PROT BITS(8,9)"
.LASF1497:
	.string	"OB_SPC REG16((OB) + 0x00U)"
.LASF330:
	.string	"GD32VF103_H "
.LASF563:
	.string	"ADC_CTL0_ICA BIT(10)"
.LASF497:
	.string	"FLASH_BASE ((uint32_t)0x08000000U)"
.LASF2529:
	.string	"TIMER_CH_3 ((uint16_t)0x0003U)"
.LASF68:
	.string	"__SCHAR_MAX__ 0x7f"
.LASF293:
	.string	"__GCC_ATOMIC_INT_LOCK_FREE 2"
.LASF258:
	.string	"__FLT32X_MAX__ 1.79769313486231570814527423731704357e+308F32x"
.LASF2900:
	.string	"RCU_INT_PLL1STBIC BIT(21)"
.LASF3372:
	.string	"rcu_adc_clock_config"
.LASF38:
	.string	"__CHAR16_TYPE__ short unsigned int"
.LASF2:
	.string	"__STDC_UTF_16__ 1"
.LASF2031:
	.string	"DBG_CTL_TIMER2_HOLD BIT(12)"
.LASF2831:
	.string	"MTIME_HANDLER eclic_mtip_handler"
.LASF2581:
	.string	"TIMER_TRI_OUT_SRC_CH0 CTL1_MMC(3)"
.LASF2283:
	.string	"TIMER_CH3CV(timerx) REG32((timerx) + 0x40U)"
.LASF101:
	.string	"__UINT16_MAX__ 0xffff"
.LASF2103:
	.string	"RTC_ALRMH_ALRM BITS(0,15)"
.LASF1887:
	.string	"I2C_DATA(i2cx) REG32((i2cx) + 0x10U)"
.LASF774:
	.string	"RTC_OUTPUT_ALARM_PULSE ((uint16_t)0x0000U)"
.LASF154:
	.string	"__FLT_MIN__ 1.17549435082228750796873653722224568e-38F"
.LASF1081:
	.string	"CAN_BT_BS2_8TQ ((uint8_t)0x07U)"
.LASF3260:
	.string	"RCU_GPIOCRST"
.LASF843:
	.string	"CAN_F27DATA0(canx) REG32((canx) + 0x318U)"
.LASF270:
	.string	"__FLT64X_MAX_EXP__ 16384"
.LASF278:
	.string	"__FLT64X_HAS_DENORM__ 1"
.LASF2841:
	.string	"RCU_CFG0 REG32(RCU + 0x04U)"
.LASF779:
	.string	"BKP_INT_FLAG_TAMPER BKP_TPCS_TIF"
.LASF960:
	.string	"CAN_TMI_EFID BITS(3,31)"
.LASF1790:
	.string	"GPIO_MODE_OUT_OD ((uint8_t)0x14U)"
.LASF3360:
	.string	"rcu_interrupt_flag_get"
.LASF1047:
	.string	"CAN_ERRN_6 ERR_ERRN(6U)"
.LASF3:
	.string	"__STDC_UTF_32__ 1"
.LASF1290:
	.string	"DMA_CHPADDR_RESET_VALUE ((uint32_t)0x00000000U)"
.LASF2695:
	.string	"USART_WL_9BIT CTL0_WL(1)"
.LASF1833:
	.string	"GPIO_PIN_SOURCE_10 ((uint8_t)0x0AU)"
.LASF2106:
	.string	"RTC_INT_ALARM RTC_INTEN_ALRMIE"
.LASF2978:
	.string	"RCU_RSTSCK_IRC40KEN BIT(0)"
.LASF2088:
	.string	"RTC_INTEN_SCIE BIT(0)"
.LASF1558:
	.string	"OB_USER_USER_N ((uint32_t)0xFF000000U)"
.LASF1060:
	.string	"CAN_BT_BS1_3TQ ((uint8_t)0x02U)"
.LASF616:
	.string	"ADC_DAUL_REGULAL_FOLLOWUP_SLOW CTL0_SYNCM(8)"
.LASF2873:
	.string	"RCU_CFG0_PLLSEL BIT(16)"
.LASF566:
	.string	"ADC_CTL0_DISNUM BITS(13,15)"
.LASF1744:
	.string	"GPIO_LOCK_LK12 BIT(12)"
.LASF2630:
	.string	"USART_STAT_CTSF BIT(9)"
.LASF694:
	.string	"ADC_OVERSAMPLING_SHIFT_1B OVSCR_OVSS(1)"
.LASF3227:
	.string	"RCU_ADC0"
.LASF3228:
	.string	"RCU_ADC1"
.LASF1011:
	.string	"BT_MODE(regval) (BITS(30,31) & ((uint32_t)(regval) << 30))"
.LASF3163:
	.string	"RCU_I2S2SRC_CKPLL2_MUL2 RCU_CFG1_I2S2SEL"
.LASF6:
	.string	"__GNUC_MINOR__ 2"
.LASF234:
	.string	"__FLT64_HAS_INFINITY__ 1"
.LASF3116:
	.string	"RCU_PREDV0_DIV14 CFG1_PREDV0(13)"
.LASF1082:
	.string	"CAN_MAILBOX0 ((uint8_t)0x00U)"
.LASF155:
	.string	"__FLT_EPSILON__ 1.19209289550781250000000000000000000e-7F"
.LASF593:
	.string	"ADC_RDATA_ADC1RDTR BITS(16,31)"
.LASF2276:
	.string	"TIMER_CNT(timerx) REG32((timerx) + 0x24U)"
.LASF3005:
	.string	"RSTSCK_REG_OFFSET 0x24U"
.LASF2714:
	.string	"USART_DENR_ENABLE CLT2_DENR(1)"
.LASF3288:
	.string	"RCU_INT_FLAG_PLL1STB"
.LASF833:
	.string	"CAN_F17DATA0(canx) REG32((canx) + 0x2C8U)"
.LASF371:
	.string	"___int_least32_t_defined 1"
.LASF1389:
	.string	"EXTI_INTEN_INTEN18 BIT(18)"
.LASF1536:
	.string	"FMC_STAT_REG_OFFSET 0x0CU"
.LASF2938:
	.string	"RCU_AHBEN_CRCEN BIT(6)"
.LASF2195:
	.string	"SPI_PSC_4 CTL0_PSC(1)"
.LASF1413:
	.string	"EXTI_RTEN_RTEN4 BIT(4)"
.LASF41:
	.string	"__INT8_TYPE__ signed char"
.LASF557:
	.string	"ADC_CTL0_WDCHSEL BITS(0,4)"
.LASF1525:
	.string	"FMC_WP_WP BITS(0,31)"
.LASF1201:
	.string	"DAC_LFSR_BITS2_0 DAC_WAVE_BIT_WIDTH_3"
.LASF2808:
	.string	"N200_ECLIC_H "
.LASF2312:
	.string	"TIMER_SMCFG_SMC1 BIT(14)"
.LASF2495:
	.string	"TIMER_COUNTER_EDGE CTL0_CAM(0)"
.LASF1811:
	.string	"GPIO_EVENT_PIN_4 ((uint8_t)0x04U)"
.LASF2159:
	.string	"SPI_STAT_FERR BIT(8)"
.LASF3396:
	.string	"rcu_bkp_reset_enable"
.LASF489:
	.string	"INTMAX_C(x) __INTMAX_C(x)"
.LASF1628:
	.string	"GPIO_CTL0_MD4 BITS(16, 17)"
.LASF583:
	.string	"ADC_SAMPTX_SPTN BITS(0,2)"
.LASF450:
	.string	"UINT_LEAST32_MAX (__UINT_LEAST32_MAX__)"
.LASF1657:
	.string	"GPIO_ISTAT_ISTAT5 BIT(5)"
.LASF2409:
	.string	"TIMER_DMATB_DMATB BITS(0,15)"
.LASF2830:
	.string	"MSIP_HANDLER eclic_msip_handler"
.LASF2924:
	.string	"RCU_APB1RST_USART2RST BIT(18)"
.LASF2572:
	.string	"TIMER_SMCFG_TRGSEL_ITI3 SMCFG_TRGSEL(3)"
.LASF2718:
	.string	"USART_DENT_DISABLE CLT2_DENT(0)"
.LASF1378:
	.string	"EXTI_INTEN_INTEN7 BIT(7)"
.LASF1843:
	.string	"GPIO_PIN_4 BIT(4)"
.LASF1050:
	.string	"CAN_NORMAL_MODE ((uint8_t)0x00U)"
.LASF383:
	.string	"signed +0"
.LASF1322:
	.string	"DMA_PRIORITY_ULTRA_HIGH CHCTL_PRIO(3U)"
.LASF3390:
	.string	"ck_apb1"
.LASF3388:
	.string	"ck_apb2"
.LASF685:
	.string	"OVSCR_DRES(regval) (BITS(12,13) & ((uint32_t)(regval) << 12))"
.LASF2484:
	.string	"TIMER_DMACFG_DMATC_17TRANSFER DMACFG_DMATC(16)"
.LASF1142:
	.string	"DAC1_DO REG32(DAC + 0x30U)"
.LASF3403:
	.string	"rcu_periph_clock_disable"
.LASF1163:
	.string	"DAC1_L12DH_DAC1_DH BITS(4,15)"
.LASF1748:
	.string	"GPIO_LOCK_LKK BIT(16)"
.LASF3351:
	.string	"rcu_osci_stab_wait"
.LASF107:
	.string	"__INT_LEAST16_MAX__ 0x7fff"
.LASF103:
	.string	"__UINT64_MAX__ 0xffffffffffffffffULL"
.LASF424:
	.string	"__int_least32_t_defined 1"
.LASF1249:
	.string	"DMA_CH4CNT(dmax) REG32((dmax) + 0x5CU)"
.LASF1245:
	.string	"DMA_CH3CNT(dmax) REG32((dmax) + 0x48U)"
.LASF412:
	.string	"_INT32_T_DECLARED "
.LASF1539:
	.string	"UNLOCK_KEY0 ((uint32_t)0x45670123U)"
.LASF2352:
	.string	"TIMER_CHCTL0_CH0COMCTL BITS(4,6)"
.LASF411:
	.string	"__int16_t_defined 1"
.LASF2926:
	.string	"RCU_APB1RST_UART4RST BIT(20)"
.LASF2585:
	.string	"TIMER_TRI_OUT_SRC_O3CPRE CTL1_MMC(7)"
.LASF652:
	.string	"ISQ_IL(regval) (BITS(20,21) & ((uint32_t)(regval) << 20))"
.LASF1185:
	.string	"DAC_WAVE_MODE_TRIANGLE CTL_DWM(2)"
.LASF3104:
	.string	"RCU_PREDV0_DIV2 CFG1_PREDV0(1)"
.LASF3078:
	.string	"RCU_PLL_MUL29 (PLLMF_4 | CFG0_PLLMF(12))"
.LASF2294:
	.string	"TIMER_CTL0_CKDIV BITS(8,9)"
.LASF3381:
	.string	"predv0_source"
.LASF1893:
	.string	"I2C_CTL0_I2CEN BIT(0)"
.LASF3400:
	.string	"rcu_periph_clock_sleep_disable"
.LASF1041:
	.string	"CAN_ERRN_0 ERR_ERRN(0U)"
.LASF996:
	.string	"CAN_REG_VAL(canx,offset) (REG32((canx) + ((uint32_t)(offset) >> 6)))"
.LASF522:
	.string	"RCU_BASE (AHB1_BUS_BASE + 0x00009000U)"
.LASF696:
	.string	"ADC_OVERSAMPLING_SHIFT_3B OVSCR_OVSS(3)"
.LASF1109:
	.string	"CAN_INT_RFF1 CAN_INTEN_RFFIE1"
.LASF2415:
	.string	"TIMER_INT_CMT TIMER_DMAINTEN_CMTIE"
.LASF3121:
	.string	"RCU_PREDV1_DIV2 CFG1_PREDV1(1)"
.LASF1044:
	.string	"CAN_ERRN_3 ERR_ERRN(3U)"
.LASF2791:
	.string	"_BSD_WCHAR_T_"
.LASF2945:
	.string	"RCU_APB2EN_PDEN BIT(5)"
.LASF211:
	.string	"__FLT32_MAX_10_EXP__ 38"
.LASF2670:
	.string	"USART_REGIDX_BIT(regidx,bitpos) (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))"
.LASF934:
	.string	"CAN_INTEN_RFOIE0 BIT(3)"
.LASF2701:
	.string	"CTL1_LBLEN(regval) (BIT(5) & ((uint32_t)(regval) << 5))"
.LASF1432:
	.string	"EXTI_FTEN_FTEN4 BIT(4)"
.LASF1829:
	.string	"GPIO_PIN_SOURCE_6 ((uint8_t)0x06U)"
.LASF69:
	.string	"__SHRT_MAX__ 0x7fff"
.LASF2360:
	.string	"TIMER_CHCTL0_CH0CAPFLT BITS(4,7)"
.LASF797:
	.string	"CAN_TMDATA01(canx) REG32((canx) + 0x198U)"
.LASF2128:
	.string	"SPI_I2SPSC(spix) REG32((spix) + 0x20U)"
.LASF1989:
	.string	"I2C_DTCY_16_9 I2C_CKCFG_DTCY"
.LASF1425:
	.string	"EXTI_RTEN_RTEN16 BIT(16)"
.LASF3024:
	.string	"RCU_AHB_CKSYS_DIV16 CFG0_AHBPSC(11)"
.LASF3073:
	.string	"RCU_PLL_MUL24 (PLLMF_4 | CFG0_PLLMF(7))"
.LASF1928:
	.string	"I2C_STAT0_LOSTARB BIT(9)"
.LASF2525:
	.string	"TIMER_BREAK_DISABLE ((uint16_t)0x0000U)"
.LASF2813:
	.string	"_BITULL(x) (_AC(1,ULL) << (x))"
.LASF2918:
	.string	"RCU_APB1RST_TIMER5RST BIT(4)"
.LASF72:
	.string	"__LONG_LONG_MAX__ 0x7fffffffffffffffLL"
.LASF2465:
	.string	"TIMER_DMACFG_DMATA_CCHP DMACFG_DMATA(17)"
.LASF83:
	.string	"__LONG_LONG_WIDTH__ 64"
.LASF2192:
	.string	"SPI_CK_PL_HIGH_PH_2EDGE (SPI_CTL0_CKPL | SPI_CTL0_CKPH)"
.LASF45:
	.string	"__UINT8_TYPE__ unsigned char"
.LASF3033:
	.string	"RCU_APB1_CKAHB_DIV8 CFG0_APB1PSC(6)"
.LASF105:
	.string	"__INT8_C(c) c"
.LASF398:
	.string	"__FAST16 "
.LASF1077:
	.string	"CAN_BT_BS2_4TQ ((uint8_t)0x03U)"
.LASF127:
	.string	"__INT_FAST16_WIDTH__ 32"
.LASF2650:
	.string	"USART_CTL1_LBDIE BIT(6)"
.LASF129:
	.string	"__INT_FAST32_WIDTH__ 32"
.LASF1371:
	.string	"EXTI_INTEN_INTEN0 BIT(0)"
.LASF2356:
	.string	"TIMER_CHCTL0_CH1COMSEN BIT(11)"
.LASF1912:
	.string	"I2C_CTL1_DMALST BIT(12)"
.LASF2267:
	.string	"TIMER_CTL0(timerx) REG32((timerx) + 0x00U)"
.LASF1590:
	.string	"OB_WP_27 ((uint32_t)0x08000000U)"
.LASF2940:
	.string	"RCU_AHBEN_USBFSEN BIT(12)"
.LASF315:
	.string	"__riscv_a 2000000"
.LASF1203:
	.string	"DAC_LFSR_BITS4_0 DAC_WAVE_BIT_WIDTH_5"
.LASF500:
	.string	"DBG_BASE ((uint32_t)0xE0042000U)"
.LASF1110:
	.string	"CAN_INT_RFO1 CAN_INTEN_RFOIE1"
.LASF2070:
	.string	"PMU_LDO_NORMAL ((uint32_t)0x00000000U)"
.LASF3153:
	.string	"RCU_PLL2_MUL13 CFG1_PLL2MF(11)"
.LASF260:
	.string	"__FLT32X_MIN__ 2.22507385850720138309023271733240406e-308F32x"
.LASF243:
	.string	"__FLT128_MAX__ 1.18973149535723176508575932662800702e+4932F128"
.LASF2109:
	.string	"RTC_INT_FLAG_ALARM RTC_CTL_ALRMIF"
.LASF949:
	.string	"CAN_ERR_TECNT BITS(16,23)"
.LASF75:
	.string	"__WINT_MAX__ 0xffffffffU"
.LASF534:
	.string	"ADC_SAMPT0(adcx) REG32((adcx) + 0x0CU)"
.LASF757:
	.string	"BKP_TPCS REG16((BKP) + 0x34U)"
.LASF3261:
	.string	"RCU_GPIODRST"
.LASF3311:
	.string	"RCU_IRC8M"
.LASF825:
	.string	"CAN_F9DATA0(canx) REG32((canx) + 0x288U)"
.LASF98:
	.string	"__INT32_MAX__ 0x7fffffffL"
.LASF1909:
	.string	"I2C_CTL1_EVIE BIT(9)"
.LASF1214:
	.string	"DAC_ALIGN_8B_R DATA_ALIGN(2)"
.LASF3266:
	.string	"RCU_SPI0RST"
.LASF3272:
	.string	"RCU_FLAG_PLL1STB"
.LASF1502:
	.string	"OB_WP3 REG16((OB) + 0x0EU)"
.LASF1434:
	.string	"EXTI_FTEN_FTEN6 BIT(6)"
.LASF863:
	.string	"CAN_F19DATA1(canx) REG32((canx) + 0x2DCU)"
.LASF2215:
	.string	"I2S_FRAMEFORMAT_DT32B_CH32B (I2SCTL_DTLEN(2) | SPI_I2SCTL_CHLEN)"
.LASF1635:
	.string	"GPIO_CTL0_CTL7 BITS(30, 31)"
.LASF3100:
	.string	"RCU_RTCSRC_IRC40K BDCTL_RTCSRC(2)"
.LASF2344:
	.string	"TIMER_SWEVG_CH2G BIT(3)"
.LASF2766:
	.string	"_BSD_SIZE_T_ "
.LASF2137:
	.string	"SPI_CTL0_RO BIT(10)"
.LASF1029:
	.string	"GET_RFIFOMDATA0_DB0(regval) GET_BITS((uint32_t)(regval), 0U, 7U)"
.LASF472:
	.string	"SIZE_MAX (__SIZE_MAX__)"
.LASF1311:
	.string	"DMA_PERIPHERAL_WIDTH_8BIT CHCTL_PWIDTH(0U)"
.LASF2075:
	.string	"WFE_CMD ((uint8_t)0x01U)"
.LASF42:
	.string	"__INT16_TYPE__ short int"
.LASF47:
	.string	"__UINT32_TYPE__ long unsigned int"
.LASF1533:
	.string	"FMC_BIT_POS0(val) (((uint32_t)(val) >> 6) & 0x1FU)"
.LASF2114:
	.string	"RTC_FLAG_RSYN RTC_CTL_RSYNF"
.LASF3085:
	.string	"RCU_CKUSB_CKPLL_DIV2_5 CFG0_USBPSC(2)"
.LASF76:
	.string	"__WINT_MIN__ 0U"
.LASF1946:
	.string	"I2C_FMPCFG_FMPEN BIT(0)"
.LASF308:
	.string	"__riscv_muldiv 1"
.LASF2293:
	.string	"TIMER_CTL0_ARSE BIT(7)"
.LASF429:
	.string	"__int_fast64_t_defined 1"
.LASF1938:
	.string	"I2C_STAT1_DEFSMB BIT(5)"
.LASF1691:
	.string	"GPIO_BOP_BOP7 BIT(7)"
.LASF3378:
	.string	"rcu_predv1_config"
.LASF698:
	.string	"ADC_OVERSAMPLING_SHIFT_5B OVSCR_OVSS(5)"
.LASF2788:
	.string	"__INT_WCHAR_T_H "
.LASF3362:
	.string	"rcu_all_reset_flag_clear"
.LASF2564:
	.string	"TIMER_IC_PSC_DIV1 ((uint16_t)0x0000U)"
.LASF2757:
	.string	"__need_ptrdiff_t"
.LASF577:
	.string	"ADC_CTL1_ETEIC BIT(15)"
.LASF1509:
	.string	"FMC_STAT_ENDF BIT(5)"
.LASF1287:
	.string	"DMA_CHMADDR(dma,channel) REG32(((dma) + 0x14U) + 0x14U * (uint32_t)(channel))"
.LASF2108:
	.string	"RTC_INT_FLAG_SECOND RTC_CTL_SCIF"
.LASF2535:
	.string	"TIMER_OC_POLARITY_LOW ((uint16_t)0x0002U)"
.LASF3098:
	.string	"RCU_RTCSRC_NONE BDCTL_RTCSRC(0)"
.LASF74:
	.string	"__WCHAR_MIN__ (-__WCHAR_MAX__ - 1)"
.LASF2035:
	.string	"DBG_CTL_I2C1_HOLD BIT(16)"
.LASF1336:
	.string	"EXMC_SNTCFG0 REG32(EXMC + 0x04U)"
.LASF1932:
	.string	"I2C_STAT0_SMBTO BIT(14)"
.LASF422:
	.string	"__int_least8_t_defined 1"
.LASF951:
	.string	"CAN_BT_BAUDPSC BITS(0,9)"
.LASF1723:
	.string	"GPIO_BC_CR7 BIT(7)"
.LASF2337:
	.string	"TIMER_INTF_CH0OF BIT(9)"
.LASF1417:
	.string	"EXTI_RTEN_RTEN8 BIT(8)"
.LASF1191:
	.string	"DAC_WAVE_BIT_WIDTH_5 DWBW(4)"
.LASF245:
	.string	"__FLT128_MIN__ 3.36210314311209350626267781732175260e-4932F128"
.LASF609:
	.string	"ADC_DAUL_REGULAL_PARALLEL_INSERTED_PARALLEL CTL0_SYNCM(1)"
.LASF1005:
	.string	"RFIFO1_REG_OFFSET ((uint8_t)0x10U)"
.LASF152:
	.string	"__FLT_MAX__ 3.40282346638528859811704183484516925e+38F"
.LASF138:
	.string	"__UINTPTR_MAX__ 0xffffffffU"
.LASF418:
	.string	"_INTMAX_T_DECLARED "
.LASF109:
	.string	"__INT_LEAST16_WIDTH__ 16"
.LASF2662:
	.string	"USART_CTL2_SCEN BIT(5)"
.LASF635:
	.string	"ADC0_1_EXTTRIG_INSERTED_T2_CH3 CTL1_ETSIC(4)"
.LASF2165:
	.string	"SPI_I2SCTL_DTLEN BITS(1,2)"
.LASF2202:
	.string	"I2S_AUDIOSAMPLE_8K ((uint32_t)8000U)"
.LASF955:
	.string	"CAN_BT_LCMOD BIT(30)"
.LASF1402:
	.string	"EXTI_EVEN_EVEN12 BIT(12)"
.LASF406:
	.string	"_INT8_T_DECLARED "
.LASF147:
	.string	"__FLT_MIN_EXP__ (-125)"
.LASF1137:
	.string	"DAC1_R8DH REG32(DAC + 0x1CU)"
.LASF2314:
	.string	"TIMER_DMAINTEN_UPIE BIT(0)"
.LASF1572:
	.string	"OB_WP_9 ((uint32_t)0x00000200U)"
.LASF2447:
	.string	"DMACFG_DMATA(regval) (BITS(0, 4) & ((uint32_t)(regval) << 0U))"
.LASF2287:
	.string	"TIMER_CTL0_CEN BIT(0)"
.LASF1632:
	.string	"GPIO_CTL0_MD6 BITS(24, 25)"
.LASF644:
	.string	"ADC_SAMPLETIME_41POINT5 SAMPTX_SPT(4)"
.LASF2860:
	.string	"RCU_CTL_CKMEN BIT(19)"
.LASF1178:
	.string	"DAC_TRIGGER_T1_TRGO CTL_DTSEL(4)"
.LASF1073:
	.string	"CAN_BT_BS1_16TQ ((uint8_t)0x0FU)"
.LASF883:
	.string	"CAN_CTL_SLPWMOD BIT(1)"
.LASF1239:
	.string	"DMA_CH1MADDR(dmax) REG32((dmax) + 0x28U)"
.LASF1986:
	.string	"DATA_TRANS(regval) (BITS(0,7) & ((uint32_t)(regval) << 0))"
.LASF188:
	.string	"__LDBL_HAS_DENORM__ 1"
.LASF945:
	.string	"CAN_ERR_WERR BIT(0)"
.LASF2260:
	.string	"TIMER0 (TIMER_BASE + 0x00012C00U)"
.LASF1366:
	.string	"EXTI_EVEN REG32(EXTI + 0x04U)"
.LASF1091:
	.string	"CAN_SFID_MASK ((uint32_t)0x000007FFU)"
.LASF2903:
	.string	"RCU_APB2RST_AFRST BIT(0)"
.LASF161:
	.string	"__DBL_DIG__ 15"
.LASF1695:
	.string	"GPIO_BOP_BOP11 BIT(11)"
.LASF1878:
	.string	"GPIO_TIMER1ITI1_REMAP ((uint32_t)0x00202000U)"
.LASF3393:
	.string	"rcu_system_clock_source_config"
.LASF3034:
	.string	"RCU_APB1_CKAHB_DIV16 CFG0_APB1PSC(7)"
.LASF1159:
	.string	"DAC0_R12DH_DAC0_DH BITS(0,11)"
.LASF183:
	.string	"__LDBL_MAX__ 1.18973149535723176508575932662800702e+4932L"
.LASF764:
	.string	"BKP_TPCTL_TPAL BIT(1)"
.LASF7:
	.string	"__GNUC_PATCHLEVEL__ 0"
.LASF1620:
	.string	"GPIO_CTL0_MD0 BITS(0, 1)"
.LASF2594:
	.string	"TIMER_SLAVE_MODE_EXTERNAL0 SMCFG_SMC(7)"
.LASF2645:
	.string	"USART_CTL0_WM BIT(11)"
.LASF1994:
	.string	"FWDGT_CTL REG32((FWDGT) + 0x00000000U)"
.LASF2468:
	.string	"TIMER_DMACFG_DMATC_1TRANSFER DMACFG_DMATC(0)"
.LASF419:
	.string	"_UINTMAX_T_DECLARED "
.LASF1794:
	.string	"GPIO_OSPEED_10MHZ ((uint8_t)0x01U)"
.LASF3240:
	.string	"RCU_TIMER4RST"
.LASF2456:
	.string	"TIMER_DMACFG_DMATA_CHCTL2 DMACFG_DMATA(8)"
.LASF1684:
	.string	"GPIO_BOP_BOP0 BIT(0)"
.LASF750:
	.string	"BKP_DATA37 REG16((BKP) + 0xACU)"
.LASF1941:
	.string	"I2C_STAT1_PECV BITS(8,15)"
.LASF1924:
	.string	"I2C_STAT0_STPDET BIT(4)"
.LASF3315:
	.string	"RCU_PLL2_CK"
.LASF903:
	.string	"CAN_TSTAT_MAL0 BIT(2)"
.LASF96:
	.string	"__INT8_MAX__ 0x7f"
.LASF1205:
	.string	"DAC_LFSR_BITS6_0 DAC_WAVE_BIT_WIDTH_7"
.LASF317:
	.string	"__riscv_zicsr 2000000"
.LASF2644:
	.string	"USART_CTL0_PCEN BIT(10)"
.LASF95:
	.string	"__SIG_ATOMIC_WIDTH__ 32"
.LASF700:
	.string	"ADC_OVERSAMPLING_SHIFT_7B OVSCR_OVSS(7)"
.LASF3070:
	.string	"RCU_PLL_MUL21 (PLLMF_4 | CFG0_PLLMF(4))"
.LASF2905:
	.string	"RCU_APB2RST_PBRST BIT(3)"
.LASF2324:
	.string	"TIMER_DMAINTEN_CH1DEN BIT(10)"
.LASF1676:
	.string	"GPIO_OCTL_OCTL8 BIT(8)"
.LASF998:
	.string	"CAN_REGIDX_BITS(regidx,bitpos0,bitpos1) (((uint32_t)(regidx) << 12) | ((uint32_t)(bitpos0) << 6) | (uint32_t)(bitpos1))"
.LASF1954:
	.string	"I2C_STAT0_REG_OFFSET 0x14U"
.LASF1716:
	.string	"GPIO_BC_CR0 BIT(0)"
.LASF3195:
	.string	"RCU_DMA0"
.LASF3196:
	.string	"RCU_DMA1"
.LASF2687:
	.string	"USART_PM_NONE CTL0_PM(0)"
.LASF1035:
	.string	"GET_RFIFOMDATA1_DB6(regval) GET_BITS((uint32_t)(regval), 16U, 23U)"
.LASF868:
	.string	"CAN_F24DATA1(canx) REG32((canx) + 0x304U)"
.LASF2376:
	.string	"TIMER_CHCTL1_CH3CAPFLT BITS(12,15)"
.LASF664:
	.string	"ADC_CHANNEL_3 ((uint8_t)0x03U)"
.LASF54:
	.string	"__UINT_LEAST16_TYPE__ short unsigned int"
.LASF3293:
	.string	"RCU_INT_FLAG_LXTALSTB_CLR"
.LASF1352:
	.string	"EXMC_SNTCFG(region) REG32(EXMC + 0x04U + 0x08U * (region))"
.LASF190:
	.string	"__LDBL_HAS_QUIET_NAN__ 1"
.LASF3092:
	.string	"RCU_CKOUT0SRC_CKPLL_DIV2 CFG0_CKOUT0SEL(7)"
.LASF1979:
	.string	"I2C_PEC_DISABLE ((uint32_t)0x00000000U)"
.LASF2055:
	.string	"PMU_CS_STBF BIT(1)"
.LASF2098:
	.string	"RTC_PSCL_PSC BITS(0,15)"
.LASF3166:
	.string	"RCU_DEEPSLEEP_V_1_1 DSV_DSLPVS(1)"
.LASF3018:
	.string	"RCU_SCSS_PLL CFG0_SCSS(2)"
.LASF2375:
	.string	"TIMER_CHCTL1_CH3CAPPSC BITS(10,11)"
.LASF1768:
	.string	"AFIO_EXTI1_SS BITS(4, 7)"
.LASF1775:
	.string	"AFIO_EXTI8_SS BITS(0, 3)"
.LASF3208:
	.string	"RCU_SPI2"
.LASF58:
	.string	"__INT_FAST16_TYPE__ int"
.LASF202:
	.string	"__FLT16_DENORM_MIN__ 5.96046447753906250000000000000000000e-8F16"
.LASF1803:
	.string	"GPIO_PORT_SOURCE_GPIOB ((uint8_t)0x01U)"
.LASF2756:
	.string	"_PTRDIFF_T_DECLARED "
.LASF3171:
	.string	"SEL_PLL ((uint16_t)2U)"
.LASF436:
	.string	"INT_LEAST8_MIN (-__INT_LEAST8_MAX__ - 1)"
.LASF965:
	.string	"CAN_TMDATA0_DB0 BITS(0,7)"
.LASF713:
	.string	"BKP_DATA0 REG16((BKP) + 0x04U)"
.LASF2367:
	.string	"TIMER_CHCTL1_CH2COMCEN BIT(7)"
.LASF1373:
	.string	"EXTI_INTEN_INTEN2 BIT(2)"
.LASF1207:
	.string	"DAC_LFSR_BITS8_0 DAC_WAVE_BIT_WIDTH_9"
.LASF2478:
	.string	"TIMER_DMACFG_DMATC_11TRANSFER DMACFG_DMATC(10)"
.LASF2626:
	.string	"USART_STAT_RBNE BIT(5)"
.LASF1561:
	.string	"OB_WP2_WP2 ((uint32_t)0x00FF0000U)"
.LASF215:
	.string	"__FLT32_MIN__ 1.17549435082228750796873653722224568e-38F32"
.LASF858:
	.string	"CAN_F14DATA1(canx) REG32((canx) + 0x2B4U)"
.LASF2501:
	.string	"TIMER_COUNTER_UP ((uint16_t)0x0000U)"
.LASF3180:
	.string	"short unsigned int"
.LASF742:
	.string	"BKP_DATA29 REG16((BKP) + 0x8CU)"
.LASF1323:
	.string	"DMA_MEMORY_TO_MEMORY_DISABLE ((uint32_t)0x00000000U)"
.LASF207:
	.string	"__FLT32_DIG__ 6"
.LASF901:
	.string	"CAN_TSTAT_MTF0 BIT(0)"
.LASF292:
	.string	"__GCC_ATOMIC_SHORT_LOCK_FREE 1"
.LASF1644:
	.string	"GPIO_CTL1_MD12 BITS(16, 17)"
.LASF1146:
	.string	"DAC_CTL_DTSEL0 BITS(3,5)"
.LASF2263:
	.string	"TIMER3 (TIMER_BASE + 0x00000800U)"
.LASF2461:
	.string	"TIMER_DMACFG_DMATA_CH0CV DMACFG_DMATA(13)"
.LASF2798:
	.string	"N200_TIMER_H "
.LASF1145:
	.string	"DAC_CTL_DTEN0 BIT(2)"
.LASF576:
	.string	"ADC_CTL1_ETSIC BITS(12,14)"
.LASF2800:
	.string	"TIMER_MSIP_size 0x4"
.LASF3245:
	.string	"RCU_SPI2RST"
.LASF2743:
	.string	"WWDGT_CFG_PSC_DIV8 CFG_PSC(3)"
.LASF3361:
	.string	"int_flag"
.LASF1863:
	.string	"GPIO_TIMER0_FULL_REMAP ((uint32_t)0x001600C0U)"
.LASF2418:
	.string	"TIMER_INT_FLAG_UP TIMER_INT_UP"
.LASF3348:
	.string	"rcu_osci_off"
.LASF805:
	.string	"CAN_RFIFOMDATA00(canx) REG32((canx) + 0x1B8U)"
.LASF1547:
	.string	"OB_DEEPSLEEP_NRST ((uint8_t)0x02U)"
.LASF298:
	.string	"__GCC_HAVE_DWARF2_CFI_ASM 1"
.LASF897:
	.string	"CAN_STAT_TS BIT(8)"
.LASF1864:
	.string	"GPIO_TIMER1_PARTIAL_REMAP0 ((uint32_t)0x00180100U)"
.LASF3051:
	.string	"RCU_PLL_MUL2 CFG0_PLLMF(0)"
.LASF1456:
	.string	"EXTI_SWIEV_SWIEV9 BIT(9)"
.LASF1669:
	.string	"GPIO_OCTL_OCTL1 BIT(1)"
.LASF2951:
	.string	"RCU_APB2EN_USART0EN BIT(14)"
.LASF1737:
	.string	"GPIO_LOCK_LK5 BIT(5)"
.LASF718:
	.string	"BKP_DATA5 REG16((BKP) + 0x18U)"
.LASF612:
	.string	"ADC_DAUL_INSERTED_PARALLEL_REGULAL_FOLLOWUP_SLOW CTL0_SYNCM(4)"
.LASF1275:
	.string	"DMA_CHXCTL_MNAGA BIT(7)"
.LASF2161:
	.string	"SPI_CRCPOLY_CRCPOLY BITS(0,15)"
.LASF2280:
	.string	"TIMER_CH0CV(timerx) REG32((timerx) + 0x34U)"
.LASF1901:
	.string	"I2C_CTL0_STOP BIT(9)"
.LASF399:
	.string	"__FAST32 "
.LASF1251:
	.string	"DMA_CH4MADDR(dmax) REG32((dmax) + 0x64U)"
.LASF1382:
	.string	"EXTI_INTEN_INTEN11 BIT(11)"
.LASF66:
	.string	"__UINTPTR_TYPE__ unsigned int"
.LASF730:
	.string	"BKP_DATA17 REG16((BKP) + 0x5CU)"
.LASF1706:
	.string	"GPIO_BOP_CR6 BIT(22)"
.LASF2527:
	.string	"TIMER_CH_1 ((uint16_t)0x0001U)"
.LASF3408:
	.string	"D:\\\\rt-thread\\\\bsp\\\\gd32\\\\risc-v\\\\gd32vf103v-eval"
.LASF145:
	.string	"__FLT_MANT_DIG__ 24"
.LASF3129:
	.string	"RCU_PREDV1_DIV10 CFG1_PREDV1(9)"
.LASF468:
	.string	"UINT_FAST64_MAX (__UINT_FAST64_MAX__)"
.LASF2299:
	.string	"TIMER_CTL1_TI0S BIT(7)"
.LASF2680:
	.string	"CTL0_REN(regval) (BIT(2) & ((uint32_t)(regval) << 2))"
.LASF775:
	.string	"RTC_OUTPUT_SECOND_PULSE ((uint16_t)0x0200U)"
.LASF2937:
	.string	"RCU_AHBEN_FMCSPEN BIT(4)"
.LASF3294:
	.string	"RCU_INT_FLAG_IRC8MSTB_CLR"
.LASF3252:
	.string	"RCU_CAN0RST"
.LASF2669:
	.string	"USART_GP_GUAT BITS(8,15)"
.LASF2096:
	.string	"RTC_CTL_LWOFF BIT(5)"
.LASF1752:
	.string	"AFIO_PCF0_SPI0_REMAP BIT(0)"
.LASF1069:
	.string	"CAN_BT_BS1_12TQ ((uint8_t)0x0BU)"
.LASF657:
	.string	"ADC_INSERTED_CHANNEL_0 ((uint8_t)0x00U)"
.LASF1886:
	.string	"I2C_SADDR1(i2cx) REG32((i2cx) + 0x0CU)"
.LASF578:
	.string	"ADC_CTL1_ETSRC BITS(17,19)"
.LASF2528:
	.string	"TIMER_CH_2 ((uint16_t)0x0002U)"
.LASF1052:
	.string	"CAN_SILENT_MODE ((uint8_t)0x02U)"
.LASF2238:
	.string	"SPI_I2S_INT_FLAG_TBE ((uint8_t)0x00U)"
.LASF2516:
	.string	"TIMER_BREAK_POLARITY_HIGH ((uint16_t)TIMER_CCHP_BRKP)"
.LASF2291:
	.string	"TIMER_CTL0_DIR BIT(4)"
.LASF2220:
	.string	"I2S_MODE_SLAVERX I2SCTL_I2SOPMOD(1)"
.LASF376:
	.string	"signed"
.LASF975:
	.string	"CAN_RFIFOMI_EFID BITS(3,31)"
.LASF2406:
	.string	"TIMER_CCHP_POEN BIT(15)"
.LASF2177:
	.string	"SPI_BIDIRECTIONAL_TRANSMIT SPI_CTL0_BDOEN"
.LASF553:
	.string	"ADC_STAT_EOC BIT(1)"
.LASF354:
	.string	"__GNU_VISIBLE 0"
.LASF3211:
	.string	"RCU_UART3"
.LASF3212:
	.string	"RCU_UART4"
.LASF3141:
	.string	"RCU_PLL1_MUL12 CFG1_PLL1MF(10)"
.LASF1639:
	.string	"GPIO_CTL1_CTL9 BITS(6, 7)"
.LASF1442:
	.string	"EXTI_FTEN_FTEN14 BIT(14)"
.LASF1544:
	.string	"WS_WSCNT_2 WS_WSCNT(2)"
.LASF2303:
	.string	"TIMER_CTL1_ISO1N BIT(11)"
.LASF1252:
	.string	"DMA_CH5CTL(dmax) REG32((dmax) + 0x6CU)"
.LASF3324:
	.string	"ahb_freq"
.LASF1273:
	.string	"DMA_CHXCTL_CMEN BIT(5)"
.LASF2948:
	.string	"RCU_APB2EN_ADC1EN BIT(10)"
.LASF279:
	.string	"__FLT64X_HAS_INFINITY__ 1"
.LASF1181:
	.string	"DAC_TRIGGER_SOFTWARE CTL_DTSEL(7)"
.LASF1619:
	.string	"AFIO_PCF1 REG32(AFIO + 0x1CU)"
.LASF3112:
	.string	"RCU_PREDV0_DIV10 CFG1_PREDV0(9)"
.LASF2411:
	.string	"TIMER_INT_CH0 TIMER_DMAINTEN_CH0IE"
.LASF2968:
	.string	"RCU_APB1EN_CAN1EN BIT(26)"
.LASF222:
	.string	"__FLT64_DIG__ 15"
.LASF2458:
	.string	"TIMER_DMACFG_DMATA_PSC DMACFG_DMATA(10)"
.LASF2515:
	.string	"TIMER_BREAK_POLARITY_LOW ((uint16_t)0x0000U)"
.LASF4:
	.string	"__STDC_HOSTED__ 1"
.LASF1365:
	.string	"EXTI_INTEN REG32(EXTI + 0x00U)"
.LASF676:
	.string	"ADC_CHANNEL_15 ((uint8_t)0x0FU)"
.LASF3186:
	.string	"uint8_t"
.LASF1541:
	.string	"WS_WSCNT(regval) (BITS(0,2) & ((uint32_t)(regval)))"
.LASF1449:
	.string	"EXTI_SWIEV_SWIEV2 BIT(2)"
.LASF2163:
	.string	"SPI_TCRC_TCRC BITS(0,15)"
.LASF2548:
	.string	"TIMER_OC_MODE_PWM0 ((uint16_t)0x0060U)"
.LASF2346:
	.string	"TIMER_SWEVG_CMTG BIT(5)"
.LASF2916:
	.string	"RCU_APB1RST_TIMER3RST BIT(2)"
.LASF1248:
	.string	"DMA_CH4CTL(dmax) REG32((dmax) + 0x58U)"
.LASF2692:
	.string	"USART_WM_ADDR CTL0_WM(1)"
.LASF1991:
	.string	"I2C_ADDFORMAT_10BITS I2C_SADDR0_ADDFORMAT"
.LASF1198:
	.string	"DAC_WAVE_BIT_WIDTH_12 DWBW(11)"
.LASF2828:
	.string	"ECLIC_CFG_NLBITS_MASK _AC(0x1E,UL)"
.LASF3007:
	.string	"BDCTL_REG_OFFSET 0x20U"
.LASF1215:
	.string	"DAC_TRIANGLE_AMPLITUDE_1 DAC_WAVE_BIT_WIDTH_1"
.LASF1319:
	.string	"DMA_PRIORITY_LOW CHCTL_PRIO(0U)"
.LASF2699:
	.string	"USART_STB_2BIT CTL1_STB(2)"
.LASF2723:
	.string	"USART_CTS_ENABLE CLT2_CTSEN(1)"
.LASF2632:
	.string	"USART_BAUD_FRADIV BITS(0,3)"
.LASF2289:
	.string	"TIMER_CTL0_UPS BIT(2)"
.LASF1788:
	.string	"GPIO_MODE_IPD ((uint8_t)0x28U)"
.LASF476:
	.string	"PTRDIFF_MIN (-PTRDIFF_MAX - 1)"
.LASF2942:
	.string	"RCU_APB2EN_PAEN BIT(2)"
.LASF2717:
	.string	"USART_DENT_ENABLE CLT2_DENT(1)"
.LASF924:
	.string	"CAN_RFIFO0_RFF0 BIT(3)"
.LASF2032:
	.string	"DBG_CTL_TIMER3_HOLD BIT(13)"
.LASF850:
	.string	"CAN_F6DATA1(canx) REG32((canx) + 0x274U)"
.LASF114:
	.string	"__INT64_C(c) c ## LL"
.LASF1520:
	.string	"FMC_ADDR0_ADDR BITS(0,31)"
.LASF1825:
	.string	"GPIO_PIN_SOURCE_2 ((uint8_t)0x02U)"
.LASF550:
	.string	"ADC_RDATA(adcx) REG32((adcx) + 0x4CU)"
.LASF1678:
	.string	"GPIO_OCTL_OCTL10 BIT(10)"
.LASF2268:
	.string	"TIMER_CTL1(timerx) REG32((timerx) + 0x04U)"
.LASF3055:
	.string	"RCU_PLL_MUL6 CFG0_PLLMF(4)"
.LASF1895:
	.string	"I2C_CTL0_SMBSEL BIT(3)"
.LASF2422:
	.string	"TIMER_INT_FLAG_CH3 TIMER_INT_CH3"
.LASF1313:
	.string	"DMA_PERIPHERAL_WIDTH_32BIT CHCTL_PWIDTH(2U)"
.LASF2641:
	.string	"USART_CTL0_TBEIE BIT(7)"
.LASF2417:
	.string	"TIMER_INT_BRK TIMER_DMAINTEN_BRKIE"
.LASF3329:
	.string	"pllmf"
.LASF1157:
	.string	"DAC_SWT_SWTR0 BIT(0)"
.LASF888:
	.string	"CAN_CTL_ABOR BIT(6)"
.LASF2500:
	.string	"TIMER_PSC_RELOAD_UPDATE ((uint32_t)0x00000000U)"
.LASF26:
	.string	"__ORDER_LITTLE_ENDIAN__ 1234"
.LASF2140:
	.string	"SPI_CTL0_CRCEN BIT(13)"
.LASF1124:
	.string	"CRC_FDATA_FDATA BITS(0, 7)"
.LASF3363:
	.string	"rcu_flag_get"
.LASF984:
	.string	"CAN_RFIFOMDATA1_DB4 BITS(0,7)"
.LASF819:
	.string	"CAN_F3DATA0(canx) REG32((canx) + 0x258U)"
.LASF1349:
	.string	"EXMC_SNTCFG_DSET BITS(8,15)"
.LASF3185:
	.string	"long long unsigned int"
.LASF3027:
	.string	"RCU_AHB_CKSYS_DIV256 CFG0_AHBPSC(14)"
.LASF2285:
	.string	"TIMER_DMACFG(timerx) REG32((timerx) + 0x48U)"
.LASF171:
	.string	"__DBL_DENORM_MIN__ ((double)4.94065645841246544176568792868221372e-324L)"
.LASF987:
	.string	"CAN_RFIFOMDATA1_DB7 BITS(24,31)"
.LASF1314:
	.string	"CHCTL_MWIDTH(regval) (BITS(10,11) & ((uint32_t)(regval) << 10))"
.LASF857:
	.string	"CAN_F13DATA1(canx) REG32((canx) + 0x2ACU)"
.LASF1120:
	.string	"CRC_DATA REG32(CRC + 0x00U)"
.LASF474:
	.string	"SIG_ATOMIC_MAX (__STDINT_EXP(INT_MAX))"
.LASF329:
	.string	"GD32VF103_RCU_H "
.LASF785:
	.string	"CAN_TSTAT(canx) REG32((canx) + 0x08U)"
.LASF2071:
	.string	"PMU_LDO_LOWPOWER PMU_CTL_LDOLP"
.LASF1519:
	.string	"FMC_CTL_ENDIE BIT(12)"
.LASF1399:
	.string	"EXTI_EVEN_EVEN9 BIT(9)"
.LASF1281:
	.string	"DMA_CHXPADDR_PADDR BITS(0,31)"
.LASF900:
	.string	"CAN_STAT_RXL BIT(11)"
.LASF1540:
	.string	"UNLOCK_KEY1 ((uint32_t)0xCDEF89ABU)"
.LASF1971:
	.string	"I2C_GCEN_DISABLE ((uint32_t)0x00000000U)"
.LASF2604:
	.string	"TIMER_HALLINTERFACE_ENABLE TIMER_CTL1_TI0S"
.LASF941:
	.string	"CAN_INTEN_ERRNIE BIT(11)"
.LASF725:
	.string	"BKP_DATA12 REG16((BKP) + 0x48U)"
.LASF3176:
	.string	"unsigned char"
.LASF1407:
	.string	"EXTI_EVEN_EVEN17 BIT(17)"
.LASF2698:
	.string	"USART_STB_0_5BIT CTL1_STB(1)"
.LASF3076:
	.string	"RCU_PLL_MUL27 (PLLMF_4 | CFG0_PLLMF(10))"
.LASF2332:
	.string	"TIMER_INTF_CH2IF BIT(3)"
.LASF2184:
	.string	"SPI_FRAMESIZE_8BIT ((uint32_t)0x00000000U)"
.LASF248:
	.string	"__FLT128_HAS_DENORM__ 1"
.LASF2839:
	.string	"RCU RCU_BASE"
.LASF1089:
	.string	"CAN_FIFO1 ((uint8_t)0x01U)"
.LASF332:
	.string	"__O volatile"
.LASF2507:
	.string	"TIMER_SP_MODE_SINGLE TIMER_CTL0_SPM"
.LASF787:
	.string	"CAN_RFIFO1(canx) REG32((canx) + 0x10U)"
.LASF1973:
	.string	"I2C_SRESET_RESET ((uint32_t)0x00000000U)"
.LASF2858:
	.string	"RCU_CTL_HXTALSTB BIT(17)"
.LASF1700:
	.string	"GPIO_BOP_CR0 BIT(16)"
.LASF1648:
	.string	"GPIO_CTL1_MD14 BITS(24, 25)"
.LASF2384:
	.string	"TIMER_CHCTL2_CH1NP BIT(7)"
.LASF1661:
	.string	"GPIO_ISTAT_ISTAT9 BIT(9)"
.LASF1953:
	.string	"I2C_CTL1_REG_OFFSET 0x04U"
.LASF2429:
	.string	"TIMER_FLAG_CH2 TIMER_INTF_CH2IF"
.LASF2591:
	.string	"TIMER_SLAVE_MODE_RESTART SMCFG_SMC(4)"
.LASF192:
	.string	"__FLT16_DIG__ 3"
.LASF3058:
	.string	"RCU_PLL_MUL9 CFG0_PLLMF(7)"
.LASF706:
	.string	"ADC_OVERSAMPLING_RATIO_MUL16 OVSCR_OVSR(3)"
.LASF2824:
	.string	"ECLIC_INT_ATTR_TRIG_POS 0x00"
.LASF1697:
	.string	"GPIO_BOP_BOP13 BIT(13)"
.LASF1225:
	.string	"DAC_TRIANGLE_AMPLITUDE_2047 DAC_WAVE_BIT_WIDTH_11"
.LASF2534:
	.string	"TIMER_OC_POLARITY_HIGH ((uint16_t)0x0000U)"
.LASF3291:
	.string	"rcu_int_flag_enum"
.LASF1713:
	.string	"GPIO_BOP_CR13 BIT(29)"
.LASF2888:
	.string	"RCU_INT_IRC40KSTBIE BIT(8)"
.LASF1462:
	.string	"EXTI_SWIEV_SWIEV15 BIT(15)"
.LASF3368:
	.string	"rcu_rtc_clock_config"
.LASF1817:
	.string	"GPIO_EVENT_PIN_10 ((uint8_t)0x0AU)"
.LASF464:
	.string	"INT_FAST32_MAX (__INT_FAST32_MAX__)"
.LASF2379:
	.string	"TIMER_CHCTL2_CH0NEN BIT(2)"
.LASF1999:
	.string	"FWDGT_PSC_PSC BITS(0,2)"
.LASF2256:
	.string	"I2S_FLAG_RXORERR SPI_STAT_RXORERR"
.LASF2363:
	.string	"TIMER_CHCTL1_CH2MS BITS(0,1)"
.LASF3371:
	.string	"usb_psc"
.LASF1982:
	.string	"I2C_SALTSEND_ENABLE I2C_CTL0_SALT"
.LASF1027:
	.string	"GET_RFIFOMP_DLENC(regval) GET_BITS((uint32_t)(regval), 0U, 3U)"
.LASF2213:
	.string	"I2S_FRAMEFORMAT_DT16B_CH32B (I2SCTL_DTLEN(0) | SPI_I2SCTL_CHLEN)"
.LASF2139:
	.string	"SPI_CTL0_CRCNT BIT(12)"
.LASF3389:
	.string	"rcu_apb1_clock_config"
.LASF1847:
	.string	"GPIO_PIN_8 BIT(8)"
.LASF2573:
	.string	"TIMER_SMCFG_TRGSEL_CI0F_ED SMCFG_TRGSEL(4)"
.LASF265:
	.string	"__FLT32X_HAS_QUIET_NAN__ 1"
.LASF842:
	.string	"CAN_F26DATA0(canx) REG32((canx) + 0x310U)"
.LASF348:
	.string	"__NEWLIB_MINOR__ 1"
.LASF1285:
	.string	"DMA_CHCNT(dma,channel) REG32(((dma) + 0x0CU) + 0x14U * (uint32_t)(channel))"
.LASF982:
	.string	"CAN_RFIFOMDATA0_DB2 BITS(16,23)"
.LASF3095:
	.string	"RCU_CKOUT0SRC_EXT1 CFG0_CKOUT0SEL(10)"
.LASF1392:
	.string	"EXTI_EVEN_EVEN2 BIT(2)"
.LASF340:
	.string	"LXTAL_VALUE ((uint32_t)32768)"
.LASF471:
	.string	"UINTMAX_MAX (__UINTMAX_MAX__)"
.LASF579:
	.string	"ADC_CTL1_ETERC BIT(20)"
.LASF403:
	.string	"__LEAST32 \"l\""
.LASF582:
	.string	"ADC_CTL1_TSVREN BIT(23)"
.LASF1508:
	.string	"FMC_STAT_WPERR BIT(4)"
.LASF271:
	.string	"__FLT64X_MAX_10_EXP__ 4932"
.LASF2550:
	.string	"TIMER_OC_SHADOW_ENABLE ((uint16_t)0x0008U)"
.LASF1510:
	.string	"FMC_CTL_PG BIT(0)"
.LASF2432:
	.string	"TIMER_FLAG_TRG TIMER_INTF_TRGIF"
.LASF2261:
	.string	"TIMER1 (TIMER_BASE + 0x00000000U)"
.LASF3283:
	.string	"RCU_INT_FLAG_IRC40KSTB"
.LASF1410:
	.string	"EXTI_RTEN_RTEN1 BIT(1)"
.LASF1039:
	.string	"GET_ERR_RECNT(regval) GET_BITS((uint32_t)(regval), 24U, 31U)"
.LASF2183:
	.string	"SPI_FRAMESIZE_16BIT SPI_CTL0_FF16"
.LASF2790:
	.string	"_WCHAR_T_DECLARED "
.LASF597:
	.string	"ADC_OVSCR_TOVS BIT(9)"
.LASF2402:
	.string	"TIMER_CCHP_ROS BIT(11)"
.LASF1643:
	.string	"GPIO_CTL1_CTL11 BITS(14, 15)"
.LASF3379:
	.string	"predv1_div"
.LASF894:
	.string	"CAN_STAT_ERRIF BIT(2)"
.LASF1350:
	.string	"EXMC_SNTCFG_BUSLAT BITS(16,19)"
.LASF1315:
	.string	"DMA_MEMORY_WIDTH_8BIT CHCTL_MWIDTH(0U)"
.LASF2989:
	.string	"RCU_CFG1_PREDV1 BITS(4,7)"
.LASF123:
	.string	"__UINT64_C(c) c ## ULL"
.LASF3107:
	.string	"RCU_PREDV0_DIV5 CFG1_PREDV0(4)"
.LASF2364:
	.string	"TIMER_CHCTL1_CH2COMFEN BIT(2)"
.LASF2803:
	.string	"TIMER_MTIME 0x0"
.LASF1683:
	.string	"GPIO_OCTL_OCTL15 BIT(15)"
.LASF1608:
	.string	"GPIO_ISTAT(gpiox) REG32((gpiox) + 0x08U)"
.LASF487:
	.string	"INT64_C(x) __INT64_C(x)"
.LASF972:
	.string	"CAN_TMDATA1_DB7 BITS(24,31)"
.LASF169:
	.string	"__DBL_MIN__ ((double)2.22507385850720138309023271733240406e-308L)"
.LASF2543:
	.string	"TIMER_OC_MODE_ACTIVE ((uint16_t)0x0010U)"
.LASF1295:
	.string	"DMA_INT_FLAG_HTF DMA_INTF_HTFIF"
.LASF832:
	.string	"CAN_F16DATA0(canx) REG32((canx) + 0x2C0U)"
.LASF299:
	.string	"__PRAGMA_REDEFINE_EXTNAME 1"
.LASF656:
	.string	"ADC_CHANNEL_DISCON_DISABLE ((uint8_t)0x04U)"
.LASF521:
	.string	"DMA_BASE (AHB1_BUS_BASE + 0x00008000U)"
.LASF1119:
	.string	"CRC CRC_BASE"
.LASF1395:
	.string	"EXTI_EVEN_EVEN5 BIT(5)"
.LASF849:
	.string	"CAN_F5DATA1(canx) REG32((canx) + 0x26CU)"
.LASF2643:
	.string	"USART_CTL0_PM BIT(9)"
.LASF363:
	.string	"__have_longlong64 1"
.LASF560:
	.string	"ADC_CTL0_EOICIE BIT(7)"
.LASF3199:
	.string	"RCU_USBFS"
.LASF876:
	.string	"CAN_FDATA0(canx,bank) REG32((canx) + 0x240U + ((bank) * 0x8U) + 0x0U)"
.LASF3301:
	.string	"RCU_INT_IRC40KSTB"
.LASF915:
	.string	"CAN_TSTAT_MST2 BIT(23)"
.LASF2764:
	.string	"__SIZE_T "
.LASF2156:
	.string	"SPI_STAT_CONFERR BIT(5)"
.LASF1874:
	.string	"GPIO_CAN1_REMAP ((uint32_t)0x00200040U)"
.LASF3079:
	.string	"RCU_PLL_MUL30 (PLLMF_4 | CFG0_PLLMF(13))"
.LASF349:
	.string	"__NEWLIB_PATCHLEVEL__ 0"
.LASF1742:
	.string	"GPIO_LOCK_LK10 BIT(10)"
.LASF1840:
	.string	"GPIO_PIN_1 BIT(1)"
.LASF345:
	.string	"_NEWLIB_VERSION_H__ 1"
.LASF1346:
	.string	"EXMC_SNCTL_ASYNCWAIT BIT(15)"
.LASF1621:
	.string	"GPIO_CTL0_CTL0 BITS(2, 3)"
.LASF1101:
	.string	"CAN_FT_DATA ((uint32_t)0x00000000U)"
.LASF1836:
	.string	"GPIO_PIN_SOURCE_13 ((uint8_t)0x0DU)"
.LASF494:
	.string	"BIT(x) ((uint32_t)((uint32_t)0x01U<<(x)))"
.LASF291:
	.string	"__GCC_ATOMIC_WCHAR_T_LOCK_FREE 2"
.LASF2341:
	.string	"TIMER_SWEVG_UPG BIT(0)"
.LASF760:
	.string	"BKP_OCTL_COEN BIT(7)"
.LASF2265:
	.string	"TIMER5 (TIMER_BASE + 0x00001000U)"
.LASF2627:
	.string	"USART_STAT_TC BIT(6)"
.LASF1488:
	.string	"FMC_WS REG32((FMC) + 0x00U)"
.LASF2410:
	.string	"TIMER_INT_UP TIMER_DMAINTEN_UPIE"
.LASF2721:
	.string	"USART_RTS_DISABLE CLT2_RTSEN(0)"
.LASF1387:
	.string	"EXTI_INTEN_INTEN16 BIT(16)"
.LASF3279:
	.string	"RCU_FLAG_FWDGTRST"
.LASF173:
	.string	"__DBL_HAS_INFINITY__ 1"
.LASF1136:
	.string	"DAC1_L12DH REG32(DAC + 0x18U)"
.LASF3234:
	.string	"RCU_FMC_SLP"
.LASF3062:
	.string	"RCU_PLL_MUL13 CFG0_PLLMF(11)"
.LASF60:
	.string	"__INT_FAST64_TYPE__ long long int"
.LASF2801:
	.string	"TIMER_MTIMECMP 0x8"
.LASF2321:
	.string	"TIMER_DMAINTEN_BRKIE BIT(7)"
.LASF2148:
	.string	"SPI_CTL1_ERRIE BIT(5)"
.LASF2603:
	.string	"TIMER_ETP_RISING ((uint32_t)0x00000000U)"
.LASF909:
	.string	"CAN_TSTAT_MTE1 BIT(11)"
.LASF197:
	.string	"__FLT16_DECIMAL_DIG__ 5"
.LASF499:
	.string	"OB_BASE ((uint32_t)0x1FFFF800U)"
.LASF1548:
	.string	"OB_DEEPSLEEP_RST ((uint8_t)0x00U)"
.LASF1616:
	.string	"AFIO_EXTISS1 REG32(AFIO + 0x0CU)"
.LASF1879:
	.string	"GPIO_EXMC_NADV_REMAP ((uint32_t)0x80000400U)"
.LASF247:
	.string	"__FLT128_DENORM_MIN__ 6.47517511943802511092443895822764655e-4966F128"
.LASF2124:
	.string	"SPI_CRCPOLY(spix) REG32((spix) + 0x10U)"
.LASF2649:
	.string	"USART_CTL1_LBLEN BIT(5)"
.LASF2074:
	.string	"WFI_CMD ((uint8_t)0x00U)"
.LASF2868:
	.string	"RCU_CFG0_SCSS BITS(2,3)"
.LASF2719:
	.string	"CLT2_RTSEN(regval) (BIT(8) & ((uint32_t)(regval) << 8))"
.LASF21:
	.string	"__SIZEOF_DOUBLE__ 8"
.LASF149:
	.string	"__FLT_MAX_EXP__ 128"
.LASF816:
	.string	"CAN_F0DATA0(canx) REG32((canx) + 0x240U)"
.LASF2306:
	.string	"TIMER_CTL1_ISO3 BIT(14)"
.LASF620:
	.string	"ADC_CONTINUOUS_MODE ADC_CTL1_CTN"
.LASF320:
	.string	"USE_PLIC 1"
.LASF1918:
	.string	"I2C_SADDR1_ADDRESS2 BITS(1,7)"
.LASF2174:
	.string	"SPI_I2SPSC_MCKOEN BIT(9)"
.LASF144:
	.string	"__FLT_RADIX__ 2"
.LASF1832:
	.string	"GPIO_PIN_SOURCE_9 ((uint8_t)0x09U)"
.LASF1659:
	.string	"GPIO_ISTAT_ISTAT7 BIT(7)"
.LASF2554:
	.string	"TIMER_OC_CLEAR_ENABLE ((uint16_t)0x0080U)"
.LASF1814:
	.string	"GPIO_EVENT_PIN_7 ((uint8_t)0x07U)"
.LASF2956:
	.string	"RCU_APB1EN_TIMER5EN BIT(4)"
.LASF967:
	.string	"CAN_TMDATA0_DB2 BITS(16,23)"
.LASF732:
	.string	"BKP_DATA19 REG16((BKP) + 0x64U)"
.LASF111:
	.string	"__INT32_C(c) c ## L"
.LASF935:
	.string	"CAN_INTEN_RFNEIE1 BIT(4)"
.LASF2861:
	.string	"RCU_CTL_PLLEN BIT(24)"
.LASF2931:
	.string	"RCU_APB1RST_BKPIRST BIT(27)"
.LASF1343:
	.string	"EXMC_SNCTL_NRWTPOL BIT(9)"
.LASF1947:
	.string	"I2C_REGIDX_BIT(regidx,bitpos) (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))"
.LASF1270:
	.string	"DMA_CHXCTL_HTFIE BIT(2)"
.LASF2460:
	.string	"TIMER_DMACFG_DMATA_CREP DMACFG_DMATA(12)"
.LASF519:
	.string	"GPIO_BASE (APB2_BUS_BASE + 0x00000800U)"
.LASF2575:
	.string	"TIMER_SMCFG_TRGSEL_CI1FE1 SMCFG_TRGSEL(6)"
.LASF3355:
	.string	"rcu_interrupt_disable"
.LASF1529:
	.string	"FMC_REG_VAL(offset) (REG32(FMC + ((uint32_t)(offset) >> 6)))"
.LASF3168:
	.string	"RCU_DEEPSLEEP_V_0_9 DSV_DSLPVS(3)"
.LASF82:
	.string	"__LONG_WIDTH__ 32"
.LASF2533:
	.string	"TIMER_CCXN_DISABLE ((uint16_t)0x0000U)"
.LASF738:
	.string	"BKP_DATA25 REG16((BKP) + 0x7CU)"
.LASF2316:
	.string	"TIMER_DMAINTEN_CH1IE BIT(2)"
.LASF2996:
	.string	"RCU_REGIDX_BIT(regidx,bitpos) (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))"
.LASF870:
	.string	"CAN_F26DATA1(canx) REG32((canx) + 0x314U)"
.LASF14:
	.string	"__ATOMIC_CONSUME 1"
.LASF3193:
	.string	"ErrStatus"
.LASF2820:
	.string	"ECLIC_INT_ATTR_OFFSET _AC(0x1002,UL)"
.LASF216:
	.string	"__FLT32_EPSILON__ 1.19209289550781250000000000000000000e-7F32"
.LASF3369:
	.string	"rtc_clock_source"
.LASF2464:
	.string	"TIMER_DMACFG_DMATA_CH3CV DMACFG_DMATA(16)"
.LASF3346:
	.string	"osci"
.LASF1431:
	.string	"EXTI_FTEN_FTEN3 BIT(3)"
.LASF420:
	.string	"_INTPTR_T_DECLARED "
.LASF1126:
	.string	"GD32VF103_DAC_H "
.LASF2513:
	.string	"TIMER_IOS_STATE_ENABLE ((uint16_t)TIMER_CCHP_IOS)"
.LASF1885:
	.string	"I2C_SADDR0(i2cx) REG32((i2cx) + 0x08U)"
.LASF1025:
	.string	"GET_RFIFOMI_EFID(regval) GET_BITS((uint32_t)(regval), 3U, 31U)"
.LASF2874:
	.string	"RCU_CFG0_PREDV0_LSB BIT(17)"
.LASF355:
	.string	"__ISO_C_VISIBLE 2011"
.LASF1965:
	.string	"I2C_ACKPOS_CURRENT ((uint32_t)0x00000001U)"
.LASF1033:
	.string	"GET_RFIFOMDATA1_DB4(regval) GET_BITS((uint32_t)(regval), 0U, 7U)"
.LASF2471:
	.string	"TIMER_DMACFG_DMATC_4TRANSFER DMACFG_DMATC(3)"
.LASF3137:
	.string	"RCU_PLL1_MUL8 CFG1_PLL1MF(6)"
.LASF2696:
	.string	"CTL1_STB(regval) (BITS(12,13) & ((uint32_t)(regval) << 12))"
.LASF2450:
	.string	"TIMER_DMACFG_DMATA_SMCFG DMACFG_DMATA(2)"
.LASF1480:
	.string	"EXTI_PD_PD14 BIT(14)"
.LASF3265:
	.string	"RCU_TIMER0RST"
.LASF2950:
	.string	"RCU_APB2EN_SPI0EN BIT(12)"
.LASF2638:
	.string	"USART_CTL0_IDLEIE BIT(4)"
.LASF2086:
	.string	"RTC_ALRMH REG32(RTC + 0x20U)"
.LASF1168:
	.string	"DACC_L12DH_DAC1_DH BITS(20,31)"
.LASF2997:
	.string	"RCU_REG_VAL(periph) (REG32(RCU + ((uint32_t)(periph) >> 6)))"
.LASF963:
	.string	"CAN_TMP_TSEN BIT(8)"
.LASF178:
	.string	"__LDBL_MIN_10_EXP__ (-4931)"
.LASF2710:
	.string	"CTL1_CPL(regval) (BIT(10) & ((uint32_t)(regval) << 10))"
.LASF1983:
	.string	"I2C_SALTSEND_DISABLE ((uint32_t)0x00000000U)"
.LASF2189:
	.string	"SPI_CK_PL_LOW_PH_1EDGE ((uint32_t)0x00000000U)"
.LASF213:
	.string	"__FLT32_MAX__ 3.40282346638528859811704183484516925e+38F32"
.LASF3140:
	.string	"RCU_PLL1_MUL11 CFG1_PLL1MF(9)"
.LASF726:
	.string	"BKP_DATA13 REG16((BKP) + 0x4CU)"
.LASF731:
	.string	"BKP_DATA18 REG16((BKP) + 0x60U)"
.LASF1009:
	.string	"BT_BS2(regval) (BITS(20,22) & ((uint32_t)(regval) << 20))"
.LASF2485:
	.string	"TIMER_DMACFG_DMATC_18TRANSFER DMACFG_DMATC(17)"
.LASF693:
	.string	"ADC_OVERSAMPLING_SHIFT_NONE OVSCR_OVSS(0)"
.LASF1993:
	.string	"FWDGT FWDGT_BASE"
.LASF1423:
	.string	"EXTI_RTEN_RTEN14 BIT(14)"
.LASF3182:
	.string	"__uint32_t"
.LASF116:
	.string	"__UINT_LEAST8_MAX__ 0xff"
.LASF899:
	.string	"CAN_STAT_LASTRX BIT(10)"
.LASF1934:
	.string	"I2C_STAT1_MASTER BIT(0)"
.LASF2671:
	.string	"USART_REG_VAL(usartx,offset) (REG32((usartx) + (((uint32_t)(offset) & (0x0000FFFFU)) >> 6)))"
.LASF1065:
	.string	"CAN_BT_BS1_8TQ ((uint8_t)0x07U)"
.LASF475:
	.string	"PTRDIFF_MAX (__PTRDIFF_MAX__)"
.LASF931:
	.string	"CAN_INTEN_TMEIE BIT(0)"
.LASF1271:
	.string	"DMA_CHXCTL_ERRIE BIT(3)"
.LASF2089:
	.string	"RTC_INTEN_ALRMIE BIT(1)"
.LASF3101:
	.string	"RCU_RTCSRC_HXTAL_DIV_128 BDCTL_RTCSRC(3)"
.LASF2908:
	.string	"RCU_APB2RST_PERST BIT(6)"
.LASF256:
	.string	"__FLT32X_MAX_10_EXP__ 308"
.LASF3310:
	.string	"RCU_LXTAL"
.LASF1849:
	.string	"GPIO_PIN_10 BIT(10)"
.LASF877:
	.string	"CAN_FDATA1(canx,bank) REG32((canx) + 0x240U + ((bank) * 0x8U) + 0x4U)"
.LASF2847:
	.string	"RCU_APB1EN REG32(RCU + 0x1CU)"
.LASF804:
	.string	"CAN_RFIFOMP0(canx) REG32((canx) + 0x1B4U)"
.LASF2930:
	.string	"RCU_APB1RST_CAN1RST BIT(26)"
.LASF3251:
	.string	"RCU_I2C1RST"
.LASF794:
	.string	"CAN_TMDATA10(canx) REG32((canx) + 0x18CU)"
.LASF162:
	.string	"__DBL_MIN_EXP__ (-1021)"
.LASF483:
	.string	"INT16_C(x) __INT16_C(x)"
.LASF10:
	.string	"__ATOMIC_SEQ_CST 5"
.LASF1647:
	.string	"GPIO_CTL1_CTL13 BITS(22, 23)"
.LASF2850:
	.string	"RCU_AHBRST REG32(RCU + 0x28U)"
.LASF929:
	.string	"CAN_RFIFO1_RFO1 BIT(4)"
.LASF1605:
	.string	"AFIO AFIO_BASE"
.LASF1356:
	.string	"SNCTL_NRTP(regval) (BITS(2,3) & ((uint32_t)(regval) << 2))"
.LASF844:
	.string	"CAN_F0DATA1(canx) REG32((canx) + 0x244U)"
.LASF1720:
	.string	"GPIO_BC_CR4 BIT(4)"
.LASF1222:
	.string	"DAC_TRIANGLE_AMPLITUDE_255 DAC_WAVE_BIT_WIDTH_8"
.LASF2300:
	.string	"TIMER_CTL1_ISO0 BIT(8)"
.LASF2786:
	.string	"_WCHAR_T_H "
.LASF2419:
	.string	"TIMER_INT_FLAG_CH0 TIMER_INT_CH0"
.LASF2033:
	.string	"DBG_CTL_CAN0_HOLD BIT(14)"
.LASF2589:
	.string	"TIMER_ENCODER_MODE1 SMCFG_SMC(2)"
.LASF250:
	.string	"__FLT128_HAS_QUIET_NAN__ 1"
.LASF545:
	.string	"ADC_ISQ(adcx) REG32((adcx) + 0x38U)"
.LASF2132:
	.string	"SPI_CTL0_PSC BITS(3,5)"
.LASF964:
	.string	"CAN_TMP_TS BITS(16,31)"
.LASF585:
	.string	"ADC_WDHT_WDHT BITS(0,11)"
.LASF3344:
	.string	"rcu_hxtal_clock_monitor_enable"
.LASF989:
	.string	"CAN_FCTL_HBC1F BITS(8,13)"
.LASF3271:
	.string	"RCU_FLAG_PLLSTB"
.LASF2688:
	.string	"USART_PM_EVEN CTL0_PM(2)"
.LASF2763:
	.string	"_T_SIZE "
.LASF482:
	.string	"UINT8_C(x) __UINT8_C(x)"
.LASF780:
	.string	"GD32VF103_CAN_H "
.LASF65:
	.string	"__INTPTR_TYPE__ int"
.LASF1970:
	.string	"I2C_GCEN_ENABLE I2C_CTL0_GCEN"
.LASF1772:
	.string	"AFIO_EXTI5_SS BITS(4, 7)"
.LASF2198:
	.string	"SPI_PSC_32 CTL0_PSC(4)"
.LASF3147:
	.string	"CFG1_PLL2MF(regval) (BITS(12,15) & ((uint32_t)(regval) << 12))"
.LASF509:
	.string	"FWDGT_BASE (APB1_BUS_BASE + 0x00003000U)"
.LASF3395:
	.string	"rcu_bkp_reset_disable"
.LASF1306:
	.string	"DMA_PERIPH_INCREASE_DISABLE ((uint8_t)0x00U)"
.LASF1784:
	.string	"GPIO_MODE_SET(n,mode) ((uint32_t)((uint32_t)(mode) << (4U * (n))))"
.LASF2751:
	.string	"__PTRDIFF_T "
.LASF36:
	.string	"__INTMAX_TYPE__ long long int"
.LASF3197:
	.string	"RCU_CRC"
.LASF1304:
	.string	"DMA_PERIPHERAL_TO_MEMORY ((uint8_t)0x00U)"
.LASF765:
	.string	"BKP_TPCS_TER BIT(0)"
.LASF2592:
	.string	"TIMER_SLAVE_MODE_PAUSE SMCFG_SMC(5)"
.LASF2297:
	.string	"TIMER_CTL1_DMAS BIT(3)"
.LASF496:
	.string	"GET_BITS(regval,start,end) (((regval) & BITS((start),(end))) >> (start))"
.LASF3250:
	.string	"RCU_I2C0RST"
.LASF2624:
	.string	"USART_STAT_ORERR BIT(3)"
.LASF826:
	.string	"CAN_F10DATA0(canx) REG32((canx) + 0x290U)"
.LASF2018:
	.string	"FWDGT_FLAG_RUD FWDGT_STAT_RUD"
.LASF2078:
	.string	"RTC_INTEN REG32(RTC + 0x00U)"
.LASF462:
	.string	"UINT_FAST16_MAX (__UINT_FAST16_MAX__)"
.LASF1591:
	.string	"OB_WP_28 ((uint32_t)0x10000000U)"
.LASF3146:
	.string	"RCU_PLL1_MUL20 CFG1_PLL1MF(15)"
.LASF1997:
	.string	"FWDGT_STAT REG32((FWDGT) + 0x0000000CU)"
.LASF672:
	.string	"ADC_CHANNEL_11 ((uint8_t)0x0BU)"
.LASF1673:
	.string	"GPIO_OCTL_OCTL5 BIT(5)"
.LASF2386:
	.string	"TIMER_CHCTL2_CH2P BIT(9)"
.LASF811:
	.string	"CAN_FCTL(canx) REG32((canx) + 0x200U)"
.LASF1130:
	.string	"DAC_CTL REG32(DAC + 0x00U)"
.LASF1231:
	.string	"DMA_INTC(dmax) REG32((dmax) + 0x04U)"
.LASF2412:
	.string	"TIMER_INT_CH1 TIMER_DMAINTEN_CH1IE"
.LASF2504:
	.string	"TIMER_CKDIV_DIV1 CTL0_CKDIV(0)"
.LASF2607:
	.string	"TIMER_CHVSEL_DISABLE ((uint16_t)0x0000U)"
.LASF1495:
	.string	"FMC_WP REG32((FMC) + 0x20U)"
.LASF89:
	.string	"__INTMAX_C(c) c ## LL"
.LASF2047:
	.string	"PMU_CTL_LDOLP BIT(0)"
.LASF3077:
	.string	"RCU_PLL_MUL28 (PLLMF_4 | CFG0_PLLMF(11))"
.LASF3161:
	.string	"RCU_I2S1SRC_CKPLL2_MUL2 RCU_CFG1_I2S1SEL"
.LASF302:
	.string	"__SIZEOF_PTRDIFF_T__ 4"
.LASF2497:
	.string	"TIMER_COUNTER_CENTER_UP CTL0_CAM(2)"
.LASF1517:
	.string	"FMC_CTL_OBWEN BIT(9)"
.LASF891:
	.string	"CAN_CTL_DFZ BIT(16)"
.LASF1400:
	.string	"EXTI_EVEN_EVEN10 BIT(10)"
.LASF980:
	.string	"CAN_RFIFOMDATA0_DB0 BITS(0,7)"
.LASF1677:
	.string	"GPIO_OCTL_OCTL9 BIT(9)"
.LASF910:
	.string	"CAN_TSTAT_MST1 BIT(15)"
.LASF2750:
	.string	"_T_PTRDIFF "
.LASF1861:
	.string	"GPIO_USART2_FULL_REMAP ((uint32_t)0x00140030U)"
.LASF645:
	.string	"ADC_SAMPLETIME_55POINT5 SAMPTX_SPT(5)"
.LASF503:
	.string	"APB2_BUS_BASE ((uint32_t)0x40010000U)"
.LASF535:
	.string	"ADC_SAMPT1(adcx) REG32((adcx) + 0x10U)"
.LASF2061:
	.string	"PMU_LVDT_2 CTL_LVDT(2)"
.LASF2476:
	.string	"TIMER_DMACFG_DMATC_9TRANSFER DMACFG_DMATC(8)"
.LASF1741:
	.string	"GPIO_LOCK_LK9 BIT(9)"
.LASF2770:
	.string	"_SIZE_T_DECLARED "
.LASF2144:
	.string	"SPI_CTL1_DMATEN BIT(1)"
.LASF608:
	.string	"ADC_MODE_FREE CTL0_SYNCM(0)"
.LASF86:
	.string	"__PTRDIFF_WIDTH__ 32"
.LASF763:
	.string	"BKP_TPCTL_TPEN BIT(0)"
.LASF3111:
	.string	"RCU_PREDV0_DIV9 CFG1_PREDV0(8)"
.LASF827:
	.string	"CAN_F11DATA0(canx) REG32((canx) + 0x298U)"
.LASF2758:
	.string	"__size_t__ "
.LASF2258:
	.string	"I2S_FLAG_FERR SPI_STAT_FERR"
.LASF604:
	.string	"CTL0_DISNUM(regval) (BITS(13,15) & ((uint32_t)(regval) << 13))"
.LASF3298:
	.string	"RCU_INT_FLAG_PLL2STB_CLR"
.LASF2506:
	.string	"TIMER_CKDIV_DIV4 CTL0_CKDIV(2)"
.LASF3115:
	.string	"RCU_PREDV0_DIV13 CFG1_PREDV0(12)"
.LASF1925:
	.string	"I2C_STAT0_RBNE BIT(6)"
.LASF776:
	.string	"TAMPER_PIN_ACTIVE_HIGH ((uint16_t)0x0000U)"
.LASF3290:
	.string	"RCU_INT_FLAG_CKM"
.LASF691:
	.string	"ADC_OVERSAMPLING_ONE_CONVERT 1"
.LASF2618:
	.string	"USART_CTL1(usartx) REG32((usartx) + (0x00000010U))"
.LASF1282:
	.string	"DMA_CHXMADDR_MADDR BITS(0,31)"
.LASF1238:
	.string	"DMA_CH1PADDR(dmax) REG32((dmax) + 0x24U)"
.LASF3326:
	.string	"apb2_freq"
.LASF1972:
	.string	"I2C_SRESET_SET I2C_CTL0_SRESET"
.LASF506:
	.string	"TIMER_BASE (APB1_BUS_BASE + 0x00000000U)"
.LASF943:
	.string	"CAN_INTEN_WIE BIT(16)"
.LASF1384:
	.string	"EXTI_INTEN_INTEN13 BIT(13)"
.LASF1819:
	.string	"GPIO_EVENT_PIN_12 ((uint8_t)0x0CU)"
.LASF2510:
	.string	"TIMER_UPDATE_SRC_GLOBAL ((uint32_t)0x00000000U)"
.LASF1452:
	.string	"EXTI_SWIEV_SWIEV5 BIT(5)"
.LASF466:
	.string	"INT_FAST64_MIN (-__INT_FAST64_MAX__ - 1)"
.LASF1467:
	.string	"EXTI_PD_PD1 BIT(1)"
.LASF1061:
	.string	"CAN_BT_BS1_4TQ ((uint8_t)0x03U)"
.LASF3264:
	.string	"RCU_ADC1RST"
.LASF1631:
	.string	"GPIO_CTL0_CTL5 BITS(22, 23)"
.LASF1906:
	.string	"I2C_CTL0_SRESET BIT(15)"
.LASF160:
	.string	"__DBL_MANT_DIG__ 53"
.LASF2963:
	.string	"RCU_APB1EN_UART3EN BIT(19)"
.LASF667:
	.string	"ADC_CHANNEL_6 ((uint8_t)0x06U)"
.LASF916:
	.string	"CAN_TSTAT_NUM BITS(24,25)"
.LASF790:
	.string	"CAN_BT(canx) REG32((canx) + 0x1CU)"
.LASF1992:
	.string	"GD32VF103_FWDGT_H "
.LASF3339:
	.string	"dsvol"
.LASF3249:
	.string	"RCU_UART4RST"
.LASF1148:
	.string	"DAC_CTL_DWBW0 BITS(8,11)"
.LASF426:
	.string	"__int_fast8_t_defined 1"
.LASF621:
	.string	"CTL1_ETSRC(regval) (BITS(17,19) & ((uint32_t)(regval) << 17))"
.LASF2571:
	.string	"TIMER_SMCFG_TRGSEL_ITI2 SMCFG_TRGSEL(2)"
.LASF342:
	.string	"_STDINT_H "
.LASF2846:
	.string	"RCU_APB2EN REG32(RCU + 0x18U)"
.LASF2479:
	.string	"TIMER_DMACFG_DMATC_12TRANSFER DMACFG_DMATC(11)"
.LASF626:
	.string	"ADC0_1_EXTTRIG_REGULAR_T2_TRGO CTL1_ETSRC(4)"
.LASF1284:
	.string	"DMA_CHCTL(dma,channel) REG32(((dma) + 0x08U) + 0x14U * (uint32_t)(channel))"
.LASF118:
	.string	"__UINT_LEAST16_MAX__ 0xffff"
.LASF1612:
	.string	"GPIO_LOCK(gpiox) REG32((gpiox) + 0x18U)"
.LASF2257:
	.string	"I2S_FLAG_TRANS SPI_STAT_TRANS"
.LASF1026:
	.string	"GET_RFIFOMI_SFID(regval) GET_BITS((uint32_t)(regval), 21U, 31U)"
.LASF2747:
	.string	"_ANSI_STDDEF_H "
.LASF1747:
	.string	"GPIO_LOCK_LK15 BIT(15)"
.LASF2998:
	.string	"RCU_BIT_POS(val) ((uint32_t)(val) & 0x1FU)"
.LASF441:
	.string	"UINT16_MAX (__UINT16_MAX__)"
.LASF61:
	.string	"__UINT_FAST8_TYPE__ unsigned int"
.LASF1511:
	.string	"FMC_CTL_PER BIT(1)"
.LASF2778:
	.string	"_WCHAR_T "
.LASF2093:
	.string	"RTC_CTL_OVIF BIT(2)"
.LASF839:
	.string	"CAN_F23DATA0(canx) REG32((canx) + 0x3F8U)"
.LASF2817:
	.string	"ECLIC_MTH_OFFSET 0xB"
.LASF1859:
	.string	"GPIO_USART1_REMAP ((uint32_t)0x00000008U)"
.LASF2864:
	.string	"RCU_CTL_PLL1STB BIT(27)"
.LASF1734:
	.string	"GPIO_LOCK_LK2 BIT(2)"
.LASF2224:
	.string	"I2S_STD_PHILLIPS I2SCTL_I2SSTD(0)"
.LASF1583:
	.string	"OB_WP_20 ((uint32_t)0x00100000U)"
.LASF1332:
	.string	"__SEV eclic_send_event"
.LASF1135:
	.string	"DAC1_R12DH REG32(DAC + 0x14U)"
.LASF838:
	.string	"CAN_F22DATA0(canx) REG32((canx) + 0x2F0U)"
.LASF2640:
	.string	"USART_CTL0_TCIE BIT(6)"
.LASF1021:
	.string	"TMDATA1_DB4(regval) (BITS(0,7) & ((uint32_t)(regval) << 0))"
.LASF1880:
	.string	"GD32VF103_I2C_H "
.LASF2090:
	.string	"RTC_INTEN_OVIE BIT(2)"
.LASF2512:
	.string	"TIMER_ROS_STATE_DISABLE ((uint16_t)0x0000U)"
.LASF1351:
	.string	"EXMC_SNCTL(region) REG32(EXMC + 0x08U * (region))"
.LASF3010:
	.string	"CFG1_REG_OFFSET 0x2CU"
.LASF141:
	.string	"__FLT_EVAL_METHOD__ 0"
.LASF1727:
	.string	"GPIO_BC_CR11 BIT(11)"
.LASF3233:
	.string	"RCU_SRAM_SLP"
.LASF3145:
	.string	"RCU_PLL1_MUL16 CFG1_PLL1MF(14)"
.LASF1806:
	.string	"GPIO_PORT_SOURCE_GPIOE ((uint8_t)0x04U)"
.LASF3159:
	.string	"RCU_PREDV0SRC_CKPLL1 RCU_CFG1_PREDV0SEL"
.LASF3075:
	.string	"RCU_PLL_MUL26 (PLLMF_4 | CFG0_PLLMF(9))"
.LASF2901:
	.string	"RCU_INT_PLL2STBIC BIT(22)"
.LASF485:
	.string	"INT32_C(x) __INT32_C(x)"
.LASF264:
	.string	"__FLT32X_HAS_INFINITY__ 1"
.LASF1651:
	.string	"GPIO_CTL1_CTL15 BITS(30, 31)"
.LASF2199:
	.string	"SPI_PSC_64 CTL0_PSC(5)"
.LASF2588:
	.string	"TIMER_ENCODER_MODE0 SMCFG_SMC(1)"
.LASF711:
	.string	"GD32VF103_BKP_H "
.LASF3354:
	.string	"osci_stat"
.LASF3021:
	.string	"RCU_AHB_CKSYS_DIV2 CFG0_AHBPSC(8)"
.LASF2149:
	.string	"SPI_CTL1_RBNEIE BIT(6)"
.LASF78:
	.string	"__SIZE_MAX__ 0xffffffffU"
.LASF1687:
	.string	"GPIO_BOP_BOP3 BIT(3)"
.LASF2871:
	.string	"RCU_CFG0_APB2PSC BITS(11,13)"
.LASF2767:
	.string	"_SIZE_T_DEFINED_ "
.LASF737:
	.string	"BKP_DATA24 REG16((BKP) + 0x78U)"
.LASF1730:
	.string	"GPIO_BC_CR14 BIT(14)"
.LASF690:
	.string	"ADC_OVERSAMPLING_ALL_CONVERT 0"
.LASF3387:
	.string	"rcu_apb2_clock_config"
.LASF251:
	.string	"__FLT32X_MANT_DIG__ 53"
.LASF3017:
	.string	"RCU_SCSS_HXTAL CFG0_SCSS(1)"
.LASF2279:
	.string	"TIMER_CREP(timerx) REG32((timerx) + 0x30U)"
.LASF2045:
	.string	"PMU_CTL REG32((PMU) + 0x00U)"
.LASF289:
	.string	"__GCC_ATOMIC_CHAR16_T_LOCK_FREE 1"
.LASF1250:
	.string	"DMA_CH4PADDR(dmax) REG32((dmax) + 0x60U)"
.LASF2885:
	.string	"RCU_INT_PLL1STBIF BIT(5)"
.LASF2327:
	.string	"TIMER_DMAINTEN_CMTDEN BIT(13)"
.LASF1066:
	.string	"CAN_BT_BS1_9TQ ((uint8_t)0x08U)"
.LASF353:
	.string	"__BSD_VISIBLE 0"
.LASF741:
	.string	"BKP_DATA28 REG16((BKP) + 0x88U)"
.LASF100:
	.string	"__UINT8_MAX__ 0xff"
.LASF2647:
	.string	"USART_CTL0_UEN BIT(13)"
.LASF2689:
	.string	"USART_PM_ODD CTL0_PM(3)"
.LASF9:
	.string	"__ATOMIC_RELAXED 0"
.LASF3044:
	.string	"RCU_CKADC_CKAPB2_DIV8 ((uint32_t)0x00000003U)"
.LASF653:
	.string	"ADC_REGULAR_CHANNEL ((uint8_t)0x01U)"
.LASF172:
	.string	"__DBL_HAS_DENORM__ 1"
.LASF2658:
	.string	"USART_CTL2_IREN BIT(1)"
.LASF2727:
	.string	"USART_IRLP_NORMAL CTL2_IRLP(0)"
.LASF1180:
	.string	"DAC_TRIGGER_EXTI_9 CTL_DTSEL(6)"
.LASF1704:
	.string	"GPIO_BOP_CR4 BIT(20)"
.LASF1291:
	.string	"DMA_CHMADDR_RESET_VALUE ((uint32_t)0x00000000U)"
.LASF1107:
	.string	"CAN_INT_RFO0 CAN_INTEN_RFOIE0"
.LASF1872:
	.string	"GPIO_PD01_REMAP ((uint32_t)0x00008000U)"
.LASF2274:
	.string	"TIMER_CHCTL1(timerx) REG32((timerx) + 0x1CU)"
.LASF2991:
	.string	"RCU_CFG1_PLL2MF BITS(12,15)"
.LASF396:
	.string	"__INT64 \"ll\""
.LASF1980:
	.string	"I2C_PECTRANS_ENABLE I2C_CTL0_PECTRANS"
.LASF2818:
	.string	"ECLIC_INT_IP_OFFSET _AC(0x1000,UL)"
.LASF1127:
	.string	"DAC DAC_BASE"
.LASF1474:
	.string	"EXTI_PD_PD8 BIT(8)"
.LASF976:
	.string	"CAN_RFIFOMI_SFID BITS(21,31)"
.LASF407:
	.string	"_UINT8_T_DECLARED "
.LASF994:
	.string	"CAN_FDATA_FD(regval) BIT(regval)"
.LASF2162:
	.string	"SPI_RCRC_RCRC BITS(0,15)"
.LASF2732:
	.string	"WWDGT_STAT REG32((WWDGT) + 0x00000008U)"
.LASF1078:
	.string	"CAN_BT_BS2_5TQ ((uint8_t)0x04U)"
.LASF1264:
	.string	"DMA_INTC_GIFC BIT(0)"
.LASF2241:
	.string	"SPI_INT_FLAG_CONFERR ((uint8_t)0x03U)"
.LASF2036:
	.string	"DBG_CTL_TIMER4_HOLD BIT(18)"
.LASF2178:
	.string	"SPI_BIDIRECTIONAL_RECEIVE (~SPI_CTL0_BDOEN)"
.LASF1550:
	.string	"OB_STDBY_RST ((uint8_t)0x00U)"
.LASF156:
	.string	"__FLT_DENORM_MIN__ 1.40129846432481707092372958328991613e-45F"
.LASF249:
	.string	"__FLT128_HAS_INFINITY__ 1"
.LASF729:
	.string	"BKP_DATA16 REG16((BKP) + 0x58U)"
.LASF660:
	.string	"ADC_INSERTED_CHANNEL_3 ((uint8_t)0x03U)"
.LASF2394:
	.string	"TIMER_CREP_CREP BITS(0,7)"
.LASF1440:
	.string	"EXTI_FTEN_FTEN12 BIT(12)"
.LASF719:
	.string	"BKP_DATA6 REG16((BKP) + 0x1CU)"
.LASF1015:
	.string	"TMI_EFID(regval) (BITS(3,31) & ((uint32_t)(regval) << 3))"
.LASF584:
	.string	"ADC_IOFFX_IOFF BITS(0,11)"
.LASF2586:
	.string	"SMCFG_SMC(regval) (BITS(0, 2) & ((uint32_t)(regval) << 0U))"
.LASF2481:
	.string	"TIMER_DMACFG_DMATC_14TRANSFER DMACFG_DMATC(13)"
.LASF803:
	.string	"CAN_RFIFOMI0(canx) REG32((canx) + 0x1B0U)"
.LASF447:
	.string	"UINT32_MAX (__UINT32_MAX__)"
.LASF1307:
	.string	"DMA_PERIPH_INCREASE_ENABLE ((uint8_t)0x01U)"
.LASF1006:
	.string	"ERR_REG_OFFSET ((uint8_t)0x18U)"
.LASF1998:
	.string	"FWDGT_CTL_CMD BITS(0,15)"
.LASF3259:
	.string	"RCU_GPIOBRST"
.LASF610:
	.string	"ADC_DAUL_REGULAL_PARALLEL_INSERTED_ROTATION CTL0_SYNCM(2)"
.LASF740:
	.string	"BKP_DATA27 REG16((BKP) + 0x84U)"
.LASF301:
	.string	"__SIZEOF_WINT_T__ 4"
.LASF2549:
	.string	"TIMER_OC_MODE_PWM1 ((uint16_t)0x0070U)"
.LASF1990:
	.string	"I2C_ADDFORMAT_7BITS ((uint32_t)0x00000000U)"
.LASF991:
	.string	"CAN_FSCFG_FS(regval) BIT(regval)"
.LASF1586:
	.string	"OB_WP_23 ((uint32_t)0x00800000U)"
.LASF559:
	.string	"ADC_CTL0_WDEIE BIT(6)"
.LASF2266:
	.string	"TIMER6 (TIMER_BASE + 0x00001400U)"
.LASF561:
	.string	"ADC_CTL0_SM BIT(8)"
.LASF1010:
	.string	"BT_SJW(regval) (BITS(24,25) & ((uint32_t)(regval) << 24))"
.LASF728:
	.string	"BKP_DATA15 REG16((BKP) + 0x54U)"
.LASF1841:
	.string	"GPIO_PIN_2 BIT(2)"
.LASF555:
	.string	"ADC_STAT_STIC BIT(3)"
.LASF2115:
	.string	"RTC_FLAG_LWOF RTC_CTL_LWOFF"
.LASF746:
	.string	"BKP_DATA33 REG16((BKP) + 0x9CU)"
.LASF818:
	.string	"CAN_F2DATA0(canx) REG32((canx) + 0x250U)"
.LASF2912:
	.string	"RCU_APB2RST_SPI0RST BIT(12)"
.LASF2826:
	.string	"ECLIC_INT_CTRL_OFFSET _AC(0x1003,UL)"
.LASF335:
	.string	"HXTAL_VALUE_25M HXTAL_VALUE"
.LASF1858:
	.string	"GPIO_USART0_REMAP ((uint32_t)0x00000004U)"
.LASF2099:
	.string	"RTC_DIVH_DIV BITS(0,3)"
.LASF599:
	.string	"ADC_FLAG_WDE ADC_STAT_WDE"
.LASF157:
	.string	"__FLT_HAS_DENORM__ 1"
.LASF1916:
	.string	"I2C_SADDR0_ADDFORMAT BIT(15)"
.LASF3356:
	.string	"stab_int"
.LASF391:
	.string	"_INTPTR_EQ_INT "
.LASF2408:
	.string	"TIMER_DMACFG_DMATC BITS(8,12)"
.LASF201:
	.string	"__FLT16_EPSILON__ 9.76562500000000000000000000000000000e-4F16"
.LASF3106:
	.string	"RCU_PREDV0_DIV4 CFG1_PREDV0(3)"
.LASF3089:
	.string	"RCU_CKOUT0SRC_CKSYS CFG0_CKOUT0SEL(4)"
.LASF1241:
	.string	"DMA_CH2CNT(dmax) REG32((dmax) + 0x34U)"
.LASF898:
	.string	"CAN_STAT_RS BIT(9)"
.LASF1599:
	.string	"GD32VF103_GPIO_H "
.LASF1396:
	.string	"EXTI_EVEN_EVEN6 BIT(6)"
.LASF1828:
	.string	"GPIO_PIN_SOURCE_5 ((uint8_t)0x05U)"
.LASF2784:
	.string	"_WCHAR_T_DEFINED_ "
.LASF3094:
	.string	"RCU_CKOUT0SRC_CKPLL2_DIV2 CFG0_CKOUT0SEL(9)"
.LASF1153:
	.string	"DAC_CTL_DTSEL1 BITS(19,21)"
.LASF22:
	.string	"__SIZEOF_LONG_DOUBLE__ 16"
.LASF2941:
	.string	"RCU_APB2EN_AFEN BIT(0)"
.LASF1810:
	.string	"GPIO_EVENT_PIN_3 ((uint8_t)0x03U)"
.LASF2006:
	.string	"FWDGT_PSC_DIV16 ((uint8_t)PSC_PSC(2))"
.LASF692:
	.string	"OVSCR_OVSS(regval) (BITS(5,8) & ((uint32_t)(regval) << 5))"
.LASF316:
	.string	"__riscv_c 2000000"
.LASF3189:
	.string	"RESET"
.LASF2958:
	.string	"RCU_APB1EN_WWDGTEN BIT(11)"
.LASF2455:
	.string	"TIMER_DMACFG_DMATA_CHCTL1 DMACFG_DMATA(7)"
.LASF1186:
	.string	"DWBW(regval) (BITS(8,11) & ((uint32_t)(regval) << 8))"
.LASF2667:
	.string	"USART_CTL2_CTSIE BIT(10)"
.LASF2482:
	.string	"TIMER_DMACFG_DMATC_15TRANSFER DMACFG_DMATC(14)"
.LASF380:
	.string	"__int20"
.LASF2568:
	.string	"SMCFG_TRGSEL(regval) (BITS(4, 6) & ((uint32_t)(regval) << 4U))"
.LASF2063:
	.string	"PMU_LVDT_4 CTL_LVDT(4)"
.LASF734:
	.string	"BKP_DATA21 REG16((BKP) + 0x6CU)"
.LASF739:
	.string	"BKP_DATA26 REG16((BKP) + 0x80U)"
.LASF313:
	.string	"__riscv_i 2000000"
.LASF1763:
	.string	"AFIO_PCF0_TIMER4CH3_IREMAP BIT(16)"
.LASF3158:
	.string	"RCU_PREDV0SRC_HXTAL ((uint32_t)0x00000000U)"
.LASF798:
	.string	"CAN_TMDATA11(canx) REG32((canx) + 0x19CU)"
.LASF1325:
	.string	"DMA_CHANNEL_CNT_MASK DMA_CHXCNT_CNT"
.LASF2953:
	.string	"RCU_APB1EN_TIMER2EN BIT(1)"
.LASF2686:
	.string	"CTL0_PM(regval) (BITS(9,10) & ((uint32_t)(regval) << 9))"
.LASF1086:
	.string	"CAN_FF_STANDARD ((uint32_t)0x00000000U)"
.LASF1658:
	.string	"GPIO_ISTAT_ISTAT6 BIT(6)"
.LASF2068:
	.string	"PMU_FLAG_STANDBY PMU_CS_STBF"
.LASF1253:
	.string	"DMA_CH5CNT(dmax) REG32((dmax) + 0x70U)"
.LASF79:
	.string	"__SCHAR_WIDTH__ 8"
.LASF2133:
	.string	"SPI_CTL0_SPIEN BIT(6)"
.LASF591:
	.string	"ADC_IDATAX_IDATAN BITS(0,15)"
.LASF2387:
	.string	"TIMER_CHCTL2_CH2NEN BIT(10)"
.LASF2365:
	.string	"TIMER_CHCTL1_CH2COMSEN BIT(3)"
.LASF1379:
	.string	"EXTI_INTEN_INTEN8 BIT(8)"
.LASF1844:
	.string	"GPIO_PIN_5 BIT(5)"
.LASF2371:
	.string	"TIMER_CHCTL1_CH3COMCTL BITS(12,14)"
.LASF2684:
	.string	"USART_TRANSMIT_ENABLE CTL0_TEN(1)"
.LASF523:
	.string	"FMC_BASE (AHB1_BUS_BASE + 0x0000A000U)"
.LASF2158:
	.string	"SPI_STAT_TRANS BIT(7)"
.LASF2683:
	.string	"CTL0_TEN(regval) (BIT(3) & ((uint32_t)(regval) << 3))"
.LASF2116:
	.string	"GD32VF103_SPI_H "
.LASF333:
	.string	"__IO volatile"
.LASF2887:
	.string	"RCU_INT_CKMIF BIT(7)"
.LASF1118:
	.string	"GD32VF103_CRC_H "
.LASF752:
	.string	"BKP_DATA39 REG16((BKP) + 0xB4U)"
.LASF1581:
	.string	"OB_WP_18 ((uint32_t)0x00040000U)"
.LASF1194:
	.string	"DAC_WAVE_BIT_WIDTH_8 DWBW(7)"
.LASF1279:
	.string	"DMA_CHXCTL_M2M BIT(14)"
.LASF957:
	.string	"CAN_TMI_TEN BIT(0)"
.LASF2685:
	.string	"USART_TRANSMIT_DISABLE CTL0_TEN(0)"
.LASF2250:
	.string	"SPI_FLAG_TRANS SPI_STAT_TRANS"
.LASF3218:
	.string	"RCU_PMU"
.LASF1298:
	.string	"DMA_FLAG_FTF DMA_INTF_FTFIF"
.LASF1926:
	.string	"I2C_STAT0_TBE BIT(7)"
.LASF1031:
	.string	"GET_RFIFOMDATA0_DB2(regval) GET_BITS((uint32_t)(regval), 16U, 23U)"
.LASF1575:
	.string	"OB_WP_12 ((uint32_t)0x00001000U)"
.LASF1405:
	.string	"EXTI_EVEN_EVEN15 BIT(15)"
.LASF3367:
	.string	"rcu_i2s1_clock_config"
.LASF2857:
	.string	"RCU_CTL_HXTALEN BIT(16)"
.LASF3084:
	.string	"RCU_CKUSB_CKPLL_DIV1 CFG0_USBPSC(1)"
.LASF2949:
	.string	"RCU_APB2EN_TIMER0EN BIT(11)"
.LASF3134:
	.string	"RCU_PREDV1_DIV15 CFG1_PREDV1(14)"
.LASF208:
	.string	"__FLT32_MIN_EXP__ (-125)"
.LASF1210:
	.string	"DAC_LFSR_BITS11_0 DAC_WAVE_BIT_WIDTH_12"
.LASF2759:
	.string	"__SIZE_T__ "
.LASF1984:
	.string	"I2C_ARP_ENABLE I2C_CTL0_ARPEN"
.LASF2000:
	.string	"FWDGT_RLD_RLD BITS(0,11)"
.LASF1867:
	.string	"GPIO_TIMER2_PARTIAL_REMAP ((uint32_t)0x001A0800U)"
.LASF2972:
	.string	"RCU_BDCTL_LXTALEN BIT(0)"
.LASF2921:
	.string	"RCU_APB1RST_SPI1RST BIT(14)"
.LASF3108:
	.string	"RCU_PREDV0_DIV6 CFG1_PREDV0(5)"
.LASF2946:
	.string	"RCU_APB2EN_PEEN BIT(6)"
.LASF1801:
	.string	"GPIO_EVENT_PORT_GPIOE ((uint8_t)0x04U)"
.LASF2154:
	.string	"SPI_STAT_TXURERR BIT(3)"
.LASF1334:
	.string	"EXMC (EXMC_BASE)"
.LASF1051:
	.string	"CAN_LOOPBACK_MODE ((uint8_t)0x01U)"
.LASF385:
	.string	"char +0"
.LASF1711:
	.string	"GPIO_BOP_CR11 BIT(27)"
.LASF1155:
	.string	"DAC_CTL_DWBW1 BITS(24,27)"
.LASF1008:
	.string	"BT_BS1(regval) (BITS(16,19) & ((uint32_t)(regval) << 16))"
.LASF445:
	.string	"INT32_MIN (-__INT32_MAX__ - 1)"
.LASF2326:
	.string	"TIMER_DMAINTEN_CH3DEN BIT(12)"
.LASF3246:
	.string	"RCU_USART1RST"
.LASF751:
	.string	"BKP_DATA38 REG16((BKP) + 0xB0U)"
.LASF513:
	.string	"CAN_BASE (APB1_BUS_BASE + 0x00006400U)"
.LASF2073:
	.string	"PMU_FLAG_RESET_STANDBY ((uint8_t)0x01U)"
.LASF3123:
	.string	"RCU_PREDV1_DIV4 CFG1_PREDV1(3)"
.LASF2142:
	.string	"SPI_CTL0_BDEN BIT(15)"
.LASF1430:
	.string	"EXTI_FTEN_FTEN2 BIT(2)"
.LASF2733:
	.string	"WWDGT_CTL_CNT BITS(0,6)"
.LASF1758:
	.string	"AFIO_PCF0_TIMER1_REMAP BITS(8, 9)"
.LASF2993:
	.string	"RCU_CFG1_I2S1SEL BIT(17)"
.LASF1494:
	.string	"FMC_OBSTAT REG32((FMC) + 0x1CU)"
.LASF1785:
	.string	"GPIO_MODE_MASK(n) (0xFU << (4U * (n)))"
.LASF2530:
	.string	"TIMER_CCX_ENABLE ((uint16_t)0x0001U)"
.LASF1662:
	.string	"GPIO_ISTAT_ISTAT10 BIT(10)"
.LASF568:
	.string	"ADC_CTL0_IWDEN BIT(22)"
.LASF2531:
	.string	"TIMER_CCX_DISABLE ((uint16_t)0x0000U)"
.LASF1372:
	.string	"EXTI_INTEN_INTEN1 BIT(1)"
.LASF370:
	.string	"___int_least16_t_defined 1"
.LASF2538:
	.string	"TIMER_OC_IDLE_STATE_HIGH ((uint16_t)0x0100)"
.LASF703:
	.string	"ADC_OVERSAMPLING_RATIO_MUL2 OVSCR_OVSR(0)"
.LASF15:
	.string	"__FINITE_MATH_ONLY__ 0"
.LASF1259:
	.string	"DMA_CH6MADDR(dmax) REG32((dmax) + 0x8CU)"
.LASF2637:
	.string	"USART_CTL0_TEN BIT(3)"
.LASF469:
	.string	"INTMAX_MAX (__INTMAX_MAX__)"
.LASF2822:
	.string	"ECLIC_INT_ATTR_TRIG_LEVEL 0x00"
.LASF3191:
	.string	"ERROR"
.LASF2544:
	.string	"TIMER_OC_MODE_INACTIVE ((uint16_t)0x0020U)"
.LASF1514:
	.string	"FMC_CTL_OBER BIT(5)"
.LASF1074:
	.string	"CAN_BT_BS2_1TQ ((uint8_t)0x00U)"
.LASF808:
	.string	"CAN_RFIFOMP1(canx) REG32((canx) + 0x1C4U)"
.LASF2056:
	.string	"PMU_CS_LVDF BIT(2)"
.LASF926:
	.string	"CAN_RFIFO0_RFD0 BIT(5)"
.LASF2694:
	.string	"USART_WL_8BIT CTL0_WL(0)"
.LASF2821:
	.string	"ECLIC_INT_ATTR_SHV 0x01"
.LASF2700:
	.string	"USART_STB_1_5BIT CTL1_STB(3)"
.LASF3287:
	.string	"RCU_INT_FLAG_PLLSTB"
.LASF212:
	.string	"__FLT32_DECIMAL_DIG__ 9"
.LASF1936:
	.string	"I2C_STAT1_TR BIT(2)"
.LASF2474:
	.string	"TIMER_DMACFG_DMATC_7TRANSFER DMACFG_DMATC(6)"
.LASF3254:
	.string	"RCU_BKPIRST"
.LASF562:
	.string	"ADC_CTL0_WDSC BIT(9)"
.LASF705:
	.string	"ADC_OVERSAMPLING_RATIO_MUL8 OVSCR_OVSR(2)"
.LASF367:
	.string	"___int32_t_defined 1"
.LASF3269:
	.string	"RCU_FLAG_IRC8MSTB"
.LASF2853:
	.string	"RCU_CTL_IRC8MEN BIT(0)"
.LASF1182:
	.string	"CTL_DWM(regval) (BITS(6,7) & ((uint32_t)(regval) << 6))"
.LASF168:
	.string	"__DBL_NORM_MAX__ ((double)1.79769313486231570814527423731704357e+308L)"
.LASF2320:
	.string	"TIMER_DMAINTEN_TRGIE BIT(6)"
.LASF230:
	.string	"__FLT64_MIN__ 2.22507385850720138309023271733240406e-308F64"
.LASF634:
	.string	"ADC0_1_EXTTRIG_INSERTED_T1_CH0 CTL1_ETSIC(3)"
.LASF1622:
	.string	"GPIO_CTL0_MD1 BITS(4, 5)"
.LASF2633:
	.string	"USART_BAUD_INTDIV BITS(4,15)"
.LASF246:
	.string	"__FLT128_EPSILON__ 1.92592994438723585305597794258492732e-34F128"
.LASF2526:
	.string	"TIMER_CH_0 ((uint16_t)0x0000U)"
.LASF2927:
	.string	"RCU_APB1RST_I2C0RST BIT(21)"
.LASF3046:
	.string	"RCU_CKADC_CKAPB2_DIV16 ((uint32_t)0x00000007U)"
.LASF1489:
	.string	"FMC_KEY REG32((FMC) + 0x04U)"
.LASF3373:
	.string	"adc_psc"
.LASF2899:
	.string	"RCU_INT_PLLSTBIC BIT(20)"
.LASF1770:
	.string	"AFIO_EXTI3_SS BITS(12, 15)"
.LASF2563:
	.string	"TIMER_IC_SELECTION_ITS ((uint16_t)0x0003U)"
.LASF1614:
	.string	"AFIO_PCF0 REG32(AFIO + 0x04U)"
.LASF633:
	.string	"ADC0_1_EXTTRIG_INSERTED_T1_TRGO CTL1_ETSIC(2)"
.LASF2962:
	.string	"RCU_APB1EN_USART2EN BIT(18)"
.LASF3099:
	.string	"RCU_RTCSRC_LXTAL BDCTL_RTCSRC(1)"
.LASF2027:
	.string	"DBG_CTL_FWDGT_HOLD BIT(8)"
.LASF1490:
	.string	"FMC_OBKEY REG32((FMC) + 0x08U)"
.LASF493:
	.string	"REG8(addr) (*(volatile uint8_t *)(uint32_t)(addr))"
.LASF2726:
	.string	"USART_IRLP_LOW CTL2_IRLP(1)"
.LASF2013:
	.string	"FWDGT_KEY_RELOAD ((uint16_t)0xAAAAU)"
.LASF1692:
	.string	"GPIO_BOP_BOP8 BIT(8)"
.LASF2179:
	.string	"SPI_TRANSMODE_FULLDUPLEX ((uint32_t)0x00000000U)"
.LASF2302:
	.string	"TIMER_CTL1_ISO1 BIT(10)"
.LASF2590:
	.string	"TIMER_ENCODER_MODE2 SMCFG_SMC(3)"
.LASF423:
	.string	"__int_least16_t_defined 1"
.LASF1169:
	.string	"DACC_R8DH_DAC0_DH BITS(0,7)"
.LASF3110:
	.string	"RCU_PREDV0_DIV8 CFG1_PREDV0(7)"
.LASF2781:
	.string	"__WCHAR_T "
.LASF409:
	.string	"_INT16_T_DECLARED "
.LASF88:
	.string	"__INTMAX_MAX__ 0x7fffffffffffffffLL"
.LASF1189:
	.string	"DAC_WAVE_BIT_WIDTH_3 DWBW(2)"
.LASF1046:
	.string	"CAN_ERRN_5 ERR_ERRN(5U)"
.LASF2138:
	.string	"SPI_CTL0_FF16 BIT(11)"
.LASF919:
	.string	"CAN_TSTAT_TME2 BIT(28)"
.LASF1724:
	.string	"GPIO_BC_CR8 BIT(8)"
.LASF938:
	.string	"CAN_INTEN_WERRIE BIT(8)"
.LASF2712:
	.string	"USART_CPL_HIGH CTL1_CPL(1)"
.LASF90:
	.string	"__UINTMAX_MAX__ 0xffffffffffffffffULL"
.LASF3322:
	.string	"ck_freq"
.LASF3181:
	.string	"long int"
.LASF615:
	.string	"ADC_DAUL_REGULAL_FOLLOWUP_FAST CTL0_SYNCM(7)"
.LASF3000:
	.string	"APB1EN_REG_OFFSET 0x1CU"
.LASF1890:
	.string	"I2C_CKCFG(i2cx) REG32((i2cx) + 0x1CU)"
.LASF2252:
	.string	"I2S_FLAG_RBNE SPI_STAT_RBNE"
.LASF3060:
	.string	"RCU_PLL_MUL11 CFG0_PLLMF(9)"
.LASF3336:
	.string	"apb1_exp"
.LASF1363:
	.string	"GD32VF103_EXTI_H "
.LASF378:
	.string	"char"
.LASF1757:
	.string	"AFIO_PCF0_TIMER0_REMAP BITS(6, 7)"
.LASF1341:
	.string	"EXMC_SNCTL_NRW BITS(4,5)"
.LASF32:
	.string	"__SIZE_TYPE__ unsigned int"
.LASF3247:
	.string	"RCU_USART2RST"
.LASF2959:
	.string	"RCU_APB1EN_SPI1EN BIT(14)"
.LASF881:
	.string	"CAN_RFIFOMDATA1(canx,bank) REG32((canx) + 0x1BCU + ((bank) * 0x10U))"
.LASF2378:
	.string	"TIMER_CHCTL2_CH0P BIT(1)"
.LASF392:
	.string	"_INT32_EQ_LONG "
.LASF1070:
	.string	"CAN_BT_BS1_13TQ ((uint8_t)0x0CU)"
.LASF1929:
	.string	"I2C_STAT0_AERR BIT(10)"
.LASF3082:
	.string	"CFG0_USBPSC(regval) (BITS(22,23) & ((uint32_t)(regval) << 22))"
.LASF2539:
	.string	"TIMER_OC_IDLE_STATE_LOW ((uint16_t)0x0000)"
.LASF1385:
	.string	"EXTI_INTEN_INTEN14 BIT(14)"
.LASF908:
	.string	"CAN_TSTAT_MAL1 BIT(10)"
.LASF31:
	.string	"__SIZEOF_POINTER__ 4"
.LASF1709:
	.string	"GPIO_BOP_CR9 BIT(25)"
.LASF3139:
	.string	"RCU_PLL1_MUL10 CFG1_PLL1MF(8)"
.LASF217:
	.string	"__FLT32_DENORM_MIN__ 1.40129846432481707092372958328991613e-45F32"
.LASF2851:
	.string	"RCU_CFG1 REG32(RCU + 0x2CU)"
.LASF1312:
	.string	"DMA_PERIPHERAL_WIDTH_16BIT CHCTL_PWIDTH(1U)"
.LASF2547:
	.string	"TIMER_OC_MODE_HIGH ((uint16_t)0x0050U)"
.LASF1428:
	.string	"EXTI_FTEN_FTEN0 BIT(0)"
.LASF2553:
	.string	"TIMER_OC_FAST_DISABLE ((uint16_t)0x0000)"
.LASF1796:
	.string	"GPIO_OSPEED_50MHZ ((uint8_t)0x03U)"
.LASF3330:
	.string	"ck_src"
.LASF687:
	.string	"ADC_RESOLUTION_10B OVSCR_DRES(1)"
.LASF3004:
	.string	"APB2RST_REG_OFFSET 0x0CU"
.LASF2664:
	.string	"USART_CTL2_DENT BIT(7)"
.LASF2466:
	.string	"TIMER_DMACFG_DMATA_DMACFG DMACFG_DMATA(18)"
.LASF2153:
	.string	"SPI_STAT_I2SCH BIT(2)"
.LASF2682:
	.string	"USART_RECEIVE_DISABLE CTL0_REN(0)"
.LASF2301:
	.string	"TIMER_CTL1_ISO0N BIT(9)"
.LASF2355:
	.string	"TIMER_CHCTL0_CH1COMFEN BIT(10)"
.LASF2487:
	.string	"TIMER_EVENT_SRC_CH0G ((uint16_t)0x0002U)"
.LASF663:
	.string	"ADC_CHANNEL_2 ((uint8_t)0x02U)"
.LASF1854:
	.string	"GPIO_PIN_15 BIT(15)"
.LASF3239:
	.string	"RCU_TIMER3RST"
.LASF1528:
	.string	"FMC_REGIDX_BIT(regidx,bitpos) (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))"
.LASF1104:
	.string	"CAN_INT_TME CAN_INTEN_TMEIE"
.LASF1152:
	.string	"DAC_CTL_DTEN1 BIT(18)"
.LASF1896:
	.string	"I2C_CTL0_ARPEN BIT(4)"
.LASF3125:
	.string	"RCU_PREDV1_DIV6 CFG1_PREDV1(5)"
.LASF2666:
	.string	"USART_CTL2_CTSEN BIT(9)"
.LASF2777:
	.string	"__WCHAR_T__ "
.LASF552:
	.string	"ADC_STAT_WDE BIT(0)"
.LASF1685:
	.string	"GPIO_BOP_BOP1 BIT(1)"
.LASF2434:
	.string	"TIMER_FLAG_CH0O TIMER_INTF_CH0OF"
.LASF708:
	.string	"ADC_OVERSAMPLING_RATIO_MUL64 OVSCR_OVSR(5)"
.LASF1043:
	.string	"CAN_ERRN_2 ERR_ERRN(2U)"
.LASF1618:
	.string	"AFIO_EXTISS3 REG32(AFIO + 0x14U)"
.LASF1445:
	.string	"EXTI_FTEN_FTEN17 BIT(17)"
.LASF3050:
	.string	"CFG0_PLLMF(regval) (BITS(18,21) & ((uint32_t)(regval) << 18))"
.LASF3149:
	.string	"RCU_PLL2_MUL9 CFG1_PLL2MF(7)"
.LASF2880:
	.string	"RCU_INT_IRC40KSTBIF BIT(0)"
.LASF2259:
	.string	"GD32VF103_TIMER_H "
.LASF1018:
	.string	"TMDATA0_DB1(regval) (BITS(8,15) & ((uint32_t)(regval) << 8))"
.LASF2037:
	.string	"DBG_CTL_TIMER5_HOLD BIT(19)"
.LASF2746:
	.string	"_STDDEF_H_ "
.LASF722:
	.string	"BKP_DATA9 REG16((BKP) + 0x28U)"
.LASF2834:
	.string	"ECLIC_GROUP_LEVEL0_PRIO4 0"
.LASF3299:
	.string	"RCU_INT_FLAG_CKM_CLR"
.LASF841:
	.string	"CAN_F25DATA0(canx) REG32((canx) + 0x308U)"
.LASF1717:
	.string	"GPIO_BC_CR1 BIT(1)"
.LASF2848:
	.string	"RCU_BDCTL REG32(RCU + 0x20U)"
.LASF990:
	.string	"CAN_FMCFG_FMOD(regval) BIT(regval)"
.LASF2842:
	.string	"RCU_INT REG32(RCU + 0x08U)"
.LASF2254:
	.string	"I2S_FLAG_CH SPI_STAT_I2SCH"
.LASF2960:
	.string	"RCU_APB1EN_SPI2EN BIT(15)"
.LASF921:
	.string	"CAN_TSTAT_TMLS1 BIT(30)"
.LASF479:
	.string	"WINT_MAX (__WINT_MAX__)"
.LASF856:
	.string	"CAN_F12DATA1(canx) REG32((canx) + 0x2A4U)"
.LASF1016:
	.string	"TMI_SFID(regval) (BITS(21,31) & ((uint32_t)(regval) << 21))"
.LASF862:
	.string	"CAN_F18DATA1(canx) REG32((canx) + 0x2D4U)"
.LASF1565:
	.string	"OB_WP_2 ((uint32_t)0x00000004U)"
.LASF2738:
	.string	"WWDGT_STAT_EWIF BIT(0)"
.LASF1783:
	.string	"AFIO_PCF1_EXMC_NADV BIT(10)"
.LASF2984:
	.string	"RCU_RSTSCK_FWDGTRSTF BIT(29)"
.LASF1478:
	.string	"EXTI_PD_PD12 BIT(12)"
.LASF1023:
	.string	"TMDATA1_DB6(regval) (BITS(16,23) & ((uint32_t)(regval) << 16))"
.LASF1802:
	.string	"GPIO_PORT_SOURCE_GPIOA ((uint8_t)0x00U)"
.LASF200:
	.string	"__FLT16_MIN__ 6.10351562500000000000000000000000000e-5F16"
.LASF2891:
	.string	"RCU_INT_HXTALSTBIE BIT(11)"
.LASF564:
	.string	"ADC_CTL0_DISRC BIT(11)"
.LASF3200:
	.string	"RCU_TIMER1"
.LASF3201:
	.string	"RCU_TIMER2"
.LASF3202:
	.string	"RCU_TIMER3"
.LASF3203:
	.string	"RCU_TIMER4"
.LASF3204:
	.string	"RCU_TIMER5"
.LASF3205:
	.string	"RCU_TIMER6"
.LASF815:
	.string	"CAN_FW(canx) REG32((canx) + 0x21CU)"
.LASF1753:
	.string	"AFIO_PCF0_I2C0_REMAP BIT(1)"
.LASF2275:
	.string	"TIMER_CHCTL2(timerx) REG32((timerx) + 0x20U)"
.LASF2606:
	.string	"TIMER_CHVSEL_ENABLE ((uint16_t)TIMER_CFG_OUTSEL)"
.LASF3093:
	.string	"RCU_CKOUT0SRC_CKPLL1 CFG0_CKOUT0SEL(8)"
.LASF2237:
	.string	"SPI_I2S_INT_ERR ((uint8_t)0x02U)"
.LASF807:
	.string	"CAN_RFIFOMI1(canx) REG32((canx) + 0x1C0U)"
.LASF1471:
	.string	"EXTI_PD_PD5 BIT(5)"
.LASF1421:
	.string	"EXTI_RTEN_RTEN12 BIT(12)"
.LASF831:
	.string	"CAN_F15DATA0(canx) REG32((canx) + 0x2B8U)"
.LASF1681:
	.string	"GPIO_OCTL_OCTL13 BIT(13)"
.LASF1940:
	.string	"I2C_STAT1_DUMODF BIT(7)"
.LASF531:
	.string	"ADC_STAT(adcx) REG32((adcx) + 0x00U)"
.LASF721:
	.string	"BKP_DATA8 REG16((BKP) + 0x24U)"
.LASF2702:
	.string	"USART_LBLEN_10B CTL1_LBLEN(0)"
.LASF1670:
	.string	"GPIO_OCTL_OCTL2 BIT(2)"
.LASF57:
	.string	"__INT_FAST8_TYPE__ int"
.LASF1594:
	.string	"OB_WP_31 ((uint32_t)0x80000000U)"
.LASF1167:
	.string	"DACC_L12DH_DAC0_DH BITS(4,15)"
.LASF3244:
	.string	"RCU_SPI1RST"
.LASF1470:
	.string	"EXTI_PD_PD4 BIT(4)"
.LASF1045:
	.string	"CAN_ERRN_4 ERR_ERRN(4U)"
.LASF956:
	.string	"CAN_BT_SCMOD BIT(31)"
.LASF3386:
	.string	"ckout0_src"
.LASF2361:
	.string	"TIMER_CHCTL0_CH1CAPPSC BITS(10,11)"
.LASF2023:
	.string	"DBG_ID_ID_CODE BITS(0,31)"
.LASF650:
	.string	"WDLT_WDLT(regval) (BITS(0,11) & ((uint32_t)(regval) << 0))"
.LASF1141:
	.string	"DAC0_DO REG32(DAC + 0x2CU)"
.LASF2097:
	.string	"RTC_PSCH_PSC BITS(0,3)"
.LASF1172:
	.string	"DAC1_DO_DAC1_DO BITS(0,11)"
.LASF1418:
	.string	"EXTI_RTEN_RTEN9 BIT(9)"
.LASF720:
	.string	"BKP_DATA7 REG16((BKP) + 0x20U)"
.LASF3020:
	.string	"RCU_AHB_CKSYS_DIV1 CFG0_AHBPSC(0)"
.LASF2062:
	.string	"PMU_LVDT_3 CTL_LVDT(3)"
.LASF1545:
	.string	"OB_FWDGT_SW ((uint8_t)0x01U)"
.LASF1331:
	.string	"ECLIC_PRIGROUP_LEVEL4_PRIO0 4"
.LASF2311:
	.string	"TIMER_SMCFG_ETPSC BITS(12,13)"
.LASF453:
	.string	"UINT64_MAX (__UINT64_MAX__)"
.LASF1919:
	.string	"I2C_DATA_TRB BITS(0,7)"
.LASF3358:
	.string	"rcu_interrupt_flag_clear"
.LASF1988:
	.string	"I2C_DTCY_2 ((uint32_t)0x00000000U)"
.LASF1579:
	.string	"OB_WP_16 ((uint32_t)0x00010000U)"
.LASF1738:
	.string	"GPIO_LOCK_LK6 BIT(6)"
.LASF736:
	.string	"BKP_DATA23 REG16((BKP) + 0x74U)"
.LASF2816:
	.string	"ECLIC_INFO_OFFSET 0x4"
.LASF884:
	.string	"CAN_CTL_TFO BIT(2)"
.LASF3025:
	.string	"RCU_AHB_CKSYS_DIV64 CFG0_AHBPSC(12)"
.LASF2401:
	.string	"TIMER_CCHP_IOS BIT(10)"
.LASF2810:
	.string	"_AC(X,Y) (X ##Y)"
.LASF1774:
	.string	"AFIO_EXTI7_SS BITS(12, 15)"
.LASF2194:
	.string	"SPI_PSC_2 CTL0_PSC(0)"
.LASF896:
	.string	"CAN_STAT_SLPIF BIT(4)"
.LASF2617:
	.string	"USART_CTL0(usartx) REG32((usartx) + (0x0000000CU))"
.LASF710:
	.string	"ADC_OVERSAMPLING_RATIO_MUL256 OVSCR_OVSR(7)"
.LASF753:
	.string	"BKP_DATA40 REG16((BKP) + 0xB8U)"
.LASF1451:
	.string	"EXTI_SWIEV_SWIEV4 BIT(4)"
.LASF2734:
	.string	"WWDGT_CTL_WDGTEN BIT(7)"
.LASF1554:
	.string	"FMC_USPC ((uint8_t)0xBBU)"
.LASF973:
	.string	"CAN_RFIFOMI_FT BIT(1)"
.LASF715:
	.string	"BKP_DATA2 REG16((BKP) + 0x0CU)"
.LASF1224:
	.string	"DAC_TRIANGLE_AMPLITUDE_1023 DAC_WAVE_BIT_WIDTH_10"
.LASF16:
	.string	"__SIZEOF_INT__ 4"
.LASF1609:
	.string	"GPIO_OCTL(gpiox) REG32((gpiox) + 0x0CU)"
.LASF1049:
	.string	"CAN_STATE_PENDING ((uint32_t)0x00000000U)"
.LASF384:
	.string	"unsigned +0"
.LASF28:
	.string	"__ORDER_PDP_ENDIAN__ 3412"
.LASF151:
	.string	"__FLT_DECIMAL_DIG__ 9"
.LASF3382:
	.string	"predv0_div"
.LASF2642:
	.string	"USART_CTL0_PERRIE BIT(8)"
.LASF1703:
	.string	"GPIO_BOP_CR3 BIT(19)"
.LASF2155:
	.string	"SPI_STAT_CRCERR BIT(4)"
.LASF99:
	.string	"__INT64_MAX__ 0x7fffffffffffffffLL"
.LASF2889:
	.string	"RCU_INT_LXTALSTBIE BIT(9)"
.LASF3162:
	.string	"RCU_I2S2SRC_CKSYS ((uint32_t)0x00000000U)"
.LASF2675:
	.string	"USART_BIT_POS2(val) (((uint32_t)(val) & (0x001F0000U)) >> 16)"
.LASF879:
	.string	"CAN_RFIFOMP(canx,bank) REG32((canx) + 0x1B4U + ((bank) * 0x10U))"
.LASF675:
	.string	"ADC_CHANNEL_14 ((uint8_t)0x0EU)"
.LASF2936:
	.string	"RCU_AHBEN_SRAMSPEN BIT(2)"
.LASF594:
	.string	"ADC_OVSCR_OVSEN BIT(0)"
.LASF2503:
	.string	"CTL0_CKDIV(regval) ((uint16_t)(BITS(8, 9) & ((uint32_t)(regval) << 8U)))"
.LASF1202:
	.string	"DAC_LFSR_BITS3_0 DAC_WAVE_BIT_WIDTH_4"
.LASF2270:
	.string	"TIMER_DMAINTEN(timerx) REG32((timerx) + 0x0CU)"
.LASF417:
	.string	"__int64_t_defined 1"
.LASF724:
	.string	"BKP_DATA11 REG16((BKP) + 0x44U)"
.LASF2866:
	.string	"RCU_CTL_PLL2STB BIT(29)"
.LASF2555:
	.string	"TIMER_OC_CLEAR_DISABLE ((uint16_t)0x0000U)"
.LASF3292:
	.string	"RCU_INT_FLAG_IRC40KSTB_CLR"
.LASF379:
	.string	"short"
.LASF1357:
	.string	"EXMC_MEMORY_TYPE_SRAM SNCTL_NRTP(0)"
.LASF1465:
	.string	"EXTI_SWIEV_SWIEV18 BIT(18)"
.LASF1524:
	.string	"FMC_OBSTAT_DATA BITS(10,25)"
.LASF772:
	.string	"BKP_DATA_GET(regval) GET_BITS((uint32_t)(regval), 0, 15)"
.LASF2598:
	.string	"TIMER_EXT_TRI_PSC_OFF SMCFG_ETPSC(0)"
.LASF3127:
	.string	"RCU_PREDV1_DIV8 CFG1_PREDV1(7)"
.LASF992:
	.string	"CAN_FAFIFOR_FAF(regval) BIT(regval)"
.LASF2741:
	.string	"WWDGT_CFG_PSC_DIV2 CFG_PSC(1)"
.LASF3406:
	.string	"GNU C17 10.2.0 -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit= 8 -march=rv32imac -g3 -O0"
.LASF1187:
	.string	"DAC_WAVE_BIT_WIDTH_1 DWBW(0)"
.LASF1518:
	.string	"FMC_CTL_ERRIE BIT(10)"
.LASF749:
	.string	"BKP_DATA36 REG16((BKP) + 0xA8U)"
.LASF871:
	.string	"CAN_F27DATA1(canx) REG32((canx) + 0x31CU)"
.LASF735:
	.string	"BKP_DATA22 REG16((BKP) + 0x70U)"
.LASF1013:
	.string	"FDATA_MASK_LOW(regval) (BITS(0,15) & ((uint32_t)(regval) << 0))"
.LASF193:
	.string	"__FLT16_MIN_EXP__ (-13)"
.LASF2022:
	.string	"DBG_CTL REG32(DBG + 0x04U)"
.LASF3307:
	.string	"RCU_INT_PLL2STB"
.LASF1824:
	.string	"GPIO_PIN_SOURCE_1 ((uint8_t)0x01U)"
.LASF1667:
	.string	"GPIO_ISTAT_ISTAT15 BIT(15)"
.LASF3173:
	.string	"LXTAL_STARTUP_TIMEOUT ((uint32_t)0x3FFFFFFU)"
.LASF2136:
	.string	"SPI_CTL0_SWNSSEN BIT(9)"
.LASF2216:
	.string	"I2S_MCKOUT_DISABLE ((uint32_t)0x00000000U)"
.LASF592:
	.string	"ADC_RDATA_RDATA BITS(0,15)"
.LASF939:
	.string	"CAN_INTEN_PERRIE BIT(9)"
.LASF1776:
	.string	"AFIO_EXTI9_SS BITS(4, 7)"
.LASF2883:
	.string	"RCU_INT_HXTALSTBIF BIT(3)"
.LASF359:
	.string	"__SVID_VISIBLE 0"
.LASF2867:
	.string	"RCU_CFG0_SCS BITS(0,1)"
.LASF2343:
	.string	"TIMER_SWEVG_CH1G BIT(2)"
.LASF1450:
	.string	"EXTI_SWIEV_SWIEV3 BIT(3)"
.LASF1664:
	.string	"GPIO_ISTAT_ISTAT12 BIT(12)"
.LASF748:
	.string	"BKP_DATA35 REG16((BKP) + 0xA4U)"
.LASF1247:
	.string	"DMA_CH3MADDR(dmax) REG32((dmax) + 0x50U)"
.LASF1099:
	.string	"CAN_FILTERMODE_LIST ((uint8_t)0x01U)"
.LASF1188:
	.string	"DAC_WAVE_BIT_WIDTH_2 DWBW(1)"
.LASF3003:
	.string	"APB1RST_REG_OFFSET 0x10U"
.LASF53:
	.string	"__UINT_LEAST8_TYPE__ unsigned char"
.LASF2969:
	.string	"RCU_APB1EN_BKPIEN BIT(27)"
.LASF1888:
	.string	"I2C_STAT0(i2cx) REG32((i2cx) + 0x14U)"
.LASF2369:
	.string	"TIMER_CHCTL1_CH3COMFEN BIT(10)"
.LASF3026:
	.string	"RCU_AHB_CKSYS_DIV128 CFG0_AHBPSC(13)"
.LASF823:
	.string	"CAN_F7DATA0(canx) REG32((canx) + 0x278U)"
.LASF2990:
	.string	"RCU_CFG1_PLL1MF BITS(8,11)"
.LASF723:
	.string	"BKP_DATA10 REG16((BKP) + 0x40U)"
.LASF940:
	.string	"CAN_INTEN_BOIE BIT(10)"
.LASF1822:
	.string	"GPIO_EVENT_PIN_15 ((uint8_t)0x0FU)"
.LASF2546:
	.string	"TIMER_OC_MODE_LOW ((uint16_t)0x0040U)"
.LASF1256:
	.string	"DMA_CH6CTL(dmax) REG32((dmax) + 0x80U)"
.LASF0:
	.string	"__STDC__ 1"
.LASF1227:
	.string	"GD32VF103_DMA_H "
.LASF221:
	.string	"__FLT64_MANT_DIG__ 53"
.LASF2966:
	.string	"RCU_APB1EN_I2C1EN BIT(22)"
.LASF1158:
	.string	"DAC_SWT_SWTR1 BIT(1)"
.LASF2015:
	.string	"FWDGT_PSC_TIMEOUT ((uint32_t)0x000FFFFFU)"
.LASF2272:
	.string	"TIMER_SWEVG(timerx) REG32((timerx) + 0x14U)"
.LASF1088:
	.string	"CAN_FIFO0 ((uint8_t)0x00U)"
.LASF2011:
	.string	"FWDGT_WRITEACCESS_ENABLE ((uint16_t)0x5555U)"
.LASF2370:
	.string	"TIMER_CHCTL1_CH3COMSEN BIT(11)"
.LASF94:
	.string	"__SIG_ATOMIC_MIN__ (-__SIG_ATOMIC_MAX__ - 1)"
.LASF1950:
	.string	"I2C_REGIDX_BIT2(regidx,bitpos,regidx2,bitpos2) (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16) | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))"
.LASF754:
	.string	"BKP_DATA41 REG16((BKP) + 0xBCU)"
.LASF3133:
	.string	"RCU_PREDV1_DIV14 CFG1_PREDV1(13)"
.LASF27:
	.string	"__ORDER_BIG_ENDIAN__ 4321"
.LASF2420:
	.string	"TIMER_INT_FLAG_CH1 TIMER_INT_CH1"
.LASF252:
	.string	"__FLT32X_DIG__ 15"
.LASF2305:
	.string	"TIMER_CTL1_ISO2N BIT(13)"
.LASF2494:
	.string	"CTL0_CAM(regval) ((uint16_t)(BITS(5, 6) & ((uint32_t)(regval) << 5U)))"
.LASF2044:
	.string	"PMU PMU_BASE"
.LASF747:
	.string	"BKP_DATA34 REG16((BKP) + 0xA0U)"
.LASF2286:
	.string	"TIMER_DMATB(timerx) REG32((timerx) + 0x4CU)"
.LASF2217:
	.string	"I2S_MCKOUT_ENABLE SPI_I2SPSC_MCKOEN"
.LASF619:
	.string	"ADC_DATAALIGN_LEFT ADC_CTL1_DAL"
.LASF369:
	.string	"___int_least8_t_defined 1"
.LASF3041:
	.string	"RCU_CKADC_CKAPB2_DIV2 ((uint32_t)0x00000000U)"
.LASF2943:
	.string	"RCU_APB2EN_PBEN BIT(3)"
.LASF802:
	.string	"CAN_TMDATA12(canx) REG32((canx) + 0x1ACU)"
.LASF670:
	.string	"ADC_CHANNEL_9 ((uint8_t)0x09U)"
.LASF1903:
	.string	"I2C_CTL0_POAP BIT(11)"
.LASF2231:
	.string	"SPI_DMA_TRANSMIT ((uint8_t)0x00U)"
.LASF174:
	.string	"__DBL_HAS_QUIET_NAN__ 1"
.LASF1745:
	.string	"GPIO_LOCK_LK13 BIT(13)"
.LASF2054:
	.string	"PMU_CS_WUF BIT(0)"
.LASF648:
	.string	"IOFFX_IOFF(regval) (BITS(0,11) & ((uint32_t)(regval) << 0))"
.LASF1797:
	.string	"GPIO_EVENT_PORT_GPIOA ((uint8_t)0x00U)"
.LASF3365:
	.string	"rcu_i2s2_clock_config"
.LASF572:
	.string	"ADC_CTL1_CLB BIT(2)"
.LASF630:
	.string	"CTL1_ETSIC(regval) (BITS(12,14) & ((uint32_t)(regval) << 12))"
.LASF1760:
	.string	"AFIO_PCF0_TIMER3_REMAP BIT(12)"
.LASF236:
	.string	"__FLT128_MANT_DIG__ 113"
.LASF1486:
	.string	"FMC FMC_BASE"
.LASF530:
	.string	"ADC1 (ADC_BASE + 0x400U)"
.LASF2157:
	.string	"SPI_STAT_RXORERR BIT(6)"
.LASF1164:
	.string	"DAC1_R8DH_DAC1_DH BITS(0,7)"
.LASF3167:
	.string	"RCU_DEEPSLEEP_V_1_0 DSV_DSLPVS(2)"
.LASF3164:
	.string	"DSV_DSLPVS(regval) (BITS(0,1) & ((uint32_t)(regval) << 0))"
.LASF2428:
	.string	"TIMER_FLAG_CH1 TIMER_INTF_CH1IF"
.LASF1114:
	.string	"CAN_INT_ERRN CAN_INTEN_ERRNIE"
.LASF310:
	.string	"__riscv_float_abi_soft 1"
.LASF3144:
	.string	"RCU_PLL1_MUL15 CFG1_PLL1MF(13)"
.LASF759:
	.string	"BKP_OCTL_RCCV BITS(0,6)"
.LASF1233:
	.string	"DMA_CH0CNT(dmax) REG32((dmax) + 0x0CU)"
.LASF2622:
	.string	"USART_STAT_FERR BIT(1)"
.LASF2584:
	.string	"TIMER_TRI_OUT_SRC_O2CPRE CTL1_MMC(6)"
.LASF1593:
	.string	"OB_WP_30 ((uint32_t)0x40000000U)"
.LASF3091:
	.string	"RCU_CKOUT0SRC_HXTAL CFG0_CKOUT0SEL(6)"
.LASF239:
	.string	"__FLT128_MIN_10_EXP__ (-4931)"
.LASF3407:
	.string	"D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\GD32VF103_standard_peripheral\\Source\\gd32vf103_rcu.c"
.LASF1759:
	.string	"AFIO_PCF0_TIMER2_REMAP BITS(10, 11)"
.LASF1961:
	.string	"I2C_TRANSMITTER ((uint32_t)0xFFFFFFFEU)"
.LASF709:
	.string	"ADC_OVERSAMPLING_RATIO_MUL128 OVSCR_OVSR(6)"
.LASF2569:
	.string	"TIMER_SMCFG_TRGSEL_ITI0 SMCFG_TRGSEL(0)"
.LASF1778:
	.string	"AFIO_EXTI11_SS BITS(12, 15)"
.LASF520:
	.string	"ADC_BASE (APB2_BUS_BASE + 0x00002400U)"
.LASF2104:
	.string	"RTC_ALRML_ALRM BITS(0,15)"
.LASF546:
	.string	"ADC_IDATA0(adcx) REG32((adcx) + 0x3CU)"
.LASF2127:
	.string	"SPI_I2SCTL(spix) REG32((spix) + 0x1CU)"
.LASF1771:
	.string	"AFIO_EXTI4_SS BITS(0, 3)"
.LASF3323:
	.string	"cksys_freq"
.LASF1793:
	.string	"GPIO_MODE_AF_PP ((uint8_t)0x18U)"
.LASF3031:
	.string	"RCU_APB1_CKAHB_DIV2 CFG0_APB1PSC(4)"
.LASF906:
	.string	"CAN_TSTAT_MTF1 BIT(8)"
.LASF1786:
	.string	"GPIO_MODE_AIN ((uint8_t)0x00U)"
.LASF518:
	.string	"EXTI_BASE (APB2_BUS_BASE + 0x00000400U)"
.LASF2212:
	.string	"I2S_FRAMEFORMAT_DT16B_CH16B I2SCTL_DTLEN(0)"
.LASF2906:
	.string	"RCU_APB2RST_PCRST BIT(4)"
.LASF1506:
	.string	"FMC_STAT_BUSY BIT(0)"
.LASF2087:
	.string	"RTC_ALRML REG32(RTC + 0x24U)"
.LASF428:
	.string	"__int_fast32_t_defined 1"
.LASF1377:
	.string	"EXTI_INTEN_INTEN6 BIT(6)"
.LASF595:
	.string	"ADC_OVSCR_OVSR BITS(2,4)"
.LASF1623:
	.string	"GPIO_CTL0_CTL1 BITS(6, 7)"
.LASF3335:
	.string	"ahb_exp"
.LASF3175:
	.string	"signed char"
.LASF163:
	.string	"__DBL_MIN_10_EXP__ (-307)"
.LASF2391:
	.string	"TIMER_CNT_CNT BITS(0,15)"
.LASF611:
	.string	"ADC_DAUL_INSERTED_PARALLEL_REGULAL_FOLLOWUP_FAST CTL0_SYNCM(3)"
.LASF1848:
	.string	"GPIO_PIN_9 BIT(9)"
.LASF134:
	.string	"__UINT_FAST32_MAX__ 0xffffffffU"
.LASF3277:
	.string	"RCU_FLAG_PORRST"
.LASF2917:
	.string	"RCU_APB1RST_TIMER4RST BIT(3)"
.LASF628:
	.string	"ADC0_1_EXTTRIG_REGULAR_EXTI_11 CTL1_ETSRC(6)"
.LASF2852:
	.string	"RCU_DSV REG32(RCU + 0x34U)"
.LASF1001:
	.string	"CAN_BIT_POS1(val) ((uint32_t)(val) & 0x1FU)"
.LASF43:
	.string	"__INT32_TYPE__ long int"
.LASF2331:
	.string	"TIMER_INTF_CH1IF BIT(2)"
.LASF393:
	.string	"__INT8 \"hh\""
.LASF1393:
	.string	"EXTI_EVEN_EVEN3 BIT(3)"
.LASF2814:
	.string	"ECLICINTCTLBITS 4"
.LASF1487:
	.string	"OB OB_BASE"
.LASF498:
	.string	"SRAM_BASE ((uint32_t)0x20000000U)"
.LASF244:
	.string	"__FLT128_NORM_MAX__ 1.18973149535723176508575932662800702e+4932F128"
.LASF2704:
	.string	"CTL1_CLEN(regval) (BIT(8) & ((uint32_t)(regval) << 8))"
.LASF853:
	.string	"CAN_F9DATA1(canx) REG32((canx) + 0x28CU)"
.LASF1143:
	.string	"DAC_CTL_DEN0 BIT(0)"
.LASF2209:
	.string	"I2S_AUDIOSAMPLE_96K ((uint32_t)96000U)"
.LASF434:
	.string	"INT8_MAX (__INT8_MAX__)"
.LASF1483:
	.string	"EXTI_PD_PD17 BIT(17)"
.LASF541:
	.string	"ADC_WDLT(adcx) REG32((adcx) + 0x28U)"
.LASF3402:
	.string	"rcu_periph_clock_sleep_enable"
.LASF1715:
	.string	"GPIO_BOP_CR15 BIT(31)"
.LASF121:
	.string	"__UINT32_C(c) c ## UL"
.LASF1613:
	.string	"AFIO_EC REG32(AFIO + 0x00U)"
.LASF2243:
	.string	"I2S_INT_FLAG_TXURERR ((uint8_t)0x05U)"
.LASF1749:
	.string	"AFIO_EC_PIN BITS(0, 3)"
.LASF1976:
	.string	"I2C_DMALST_ON I2C_CTL1_DMALST"
.LASF2051:
	.string	"PMU_CTL_LVDEN BIT(4)"
.LASF77:
	.string	"__PTRDIFF_MAX__ 0x7fffffff"
.LASF2469:
	.string	"TIMER_DMACFG_DMATC_2TRANSFER DMACFG_DMATC(1)"
.LASF1688:
	.string	"GPIO_BOP_BOP4 BIT(4)"
.LASF3399:
	.string	"rcu_periph_reset_enable"
.LASF2597:
	.string	"SMCFG_ETPSC(regval) (BITS(12, 13) & ((uint32_t)(regval) << 12U))"
.LASF1655:
	.string	"GPIO_ISTAT_ISTAT3 BIT(3)"
.LASF1426:
	.string	"EXTI_RTEN_RTEN17 BIT(17)"
.LASF2152:
	.string	"SPI_STAT_TBE BIT(1)"
.LASF1438:
	.string	"EXTI_FTEN_FTEN10 BIT(10)"
.LASF389:
	.string	"int +2"
.LASF13:
	.string	"__ATOMIC_ACQ_REL 4"
.LASF3151:
	.string	"RCU_PLL2_MUL11 CFG1_PLL2MF(9)"
.LASF3047:
	.string	"RCU_PLLSRC_IRC8M_DIV2 ((uint32_t)0x00000000U)"
.LASF2176:
	.string	"SPI_SLAVE ((uint32_t)0x00000000U)"
.LASF2273:
	.string	"TIMER_CHCTL0(timerx) REG32((timerx) + 0x18U)"
.LASF2081:
	.string	"RTC_PSCL REG32(RTC + 0x0CU)"
.LASF220:
	.string	"__FLT32_HAS_QUIET_NAN__ 1"
.LASF1084:
	.string	"CAN_MAILBOX2 ((uint8_t)0x02U)"
.LASF8:
	.string	"__VERSION__ \"10.2.0\""
.LASF48:
	.string	"__UINT64_TYPE__ long long unsigned int"
.LASF1062:
	.string	"CAN_BT_BS1_5TQ ((uint8_t)0x04U)"
.LASF875:
	.string	"CAN_TMDATA1(canx,bank) REG32((canx) + 0x18CU + ((bank) * 0x10U))"
.LASF461:
	.string	"INT_FAST16_MAX (__INT_FAST16_MAX__)"
.LASF997:
	.string	"CAN_BIT_POS(val) ((uint32_t)(val) & 0x1FU)"
.LASF3206:
	.string	"RCU_WWDGT"
.LASF2339:
	.string	"TIMER_INTF_CH2OF BIT(11)"
.LASF1537:
	.string	"FMC_CTL_REG_OFFSET 0x10U"
.LASF2498:
	.string	"TIMER_COUNTER_CENTER_BOTH CTL0_CAM(3)"
.LASF1779:
	.string	"AFIO_EXTI12_SS BITS(0, 3)"
.LASF1162:
	.string	"DAC1_R12DH_DAC1_DH BITS(0,11)"
.LASF1496:
	.string	"FMC_PID REG32((FMC) + 0x100U)"
.LASF2837:
	.string	"ECLIC_GROUP_LEVEL3_PRIO1 3"
.LASF1436:
	.string	"EXTI_FTEN_FTEN8 BIT(8)"
.LASF3220:
	.string	"RCU_RTC"
.LASF515:
	.string	"PMU_BASE (APB1_BUS_BASE + 0x00007000U)"
.LASF1376:
	.string	"EXTI_INTEN_INTEN5 BIT(5)"
.LASF744:
	.string	"BKP_DATA31 REG16((BKP) + 0x94U)"
.LASF3160:
	.string	"RCU_I2S1SRC_CKSYS ((uint32_t)0x00000000U)"
.LASF983:
	.string	"CAN_RFIFOMDATA0_DB3 BITS(24,31)"
.LASF2878:
	.string	"RCU_CFG0_ADCPSC_2 BIT(28)"
.LASF454:
	.string	"INT_LEAST64_MIN (-__INT_LEAST64_MAX__ - 1)"
.LASF286:
	.string	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1"
.LASF1813:
	.string	"GPIO_EVENT_PIN_6 ((uint8_t)0x06U)"
.LASF756:
	.string	"BKP_TPCTL REG16((BKP) + 0x30U)"
.LASF2008:
	.string	"FWDGT_PSC_DIV64 ((uint8_t)PSC_PSC(4))"
.LASF443:
	.string	"INT_LEAST16_MAX (__INT_LEAST16_MAX__)"
.LASF2182:
	.string	"SPI_TRANSMODE_BDTRANSMIT (SPI_CTL0_BDEN | SPI_CTL0_BDOEN)"
.LASF3391:
	.string	"rcu_ahb_clock_config"
.LASF2205:
	.string	"I2S_AUDIOSAMPLE_22K ((uint32_t)22050U)"
.LASF281:
	.string	"__REGISTER_PREFIX__ "
.LASF1634:
	.string	"GPIO_CTL0_MD7 BITS(28, 29)"
.LASF20:
	.string	"__SIZEOF_FLOAT__ 4"
.LASF2619:
	.string	"USART_CTL2(usartx) REG32((usartx) + (0x00000014U))"
.LASF646:
	.string	"ADC_SAMPLETIME_71POINT5 SAMPTX_SPT(6)"
.LASF837:
	.string	"CAN_F21DATA0(canx) REG32((canx) + 0x2E8U)"
.LASF1429:
	.string	"EXTI_FTEN_FTEN1 BIT(1)"
.LASF2566:
	.string	"TIMER_IC_PSC_DIV4 ((uint16_t)0x0008U)"
.LASF986:
	.string	"CAN_RFIFOMDATA1_DB6 BITS(16,23)"
.LASF1269:
	.string	"DMA_CHXCTL_FTFIE BIT(1)"
.LASF1246:
	.string	"DMA_CH3PADDR(dmax) REG32((dmax) + 0x4CU)"
.LASF1411:
	.string	"EXTI_RTEN_RTEN2 BIT(2)"
.LASF1257:
	.string	"DMA_CH6CNT(dmax) REG32((dmax) + 0x84U)"
.LASF2629:
	.string	"USART_STAT_LBDF BIT(8)"
.LASF586:
	.string	"ADC_WDLT_WDLT BITS(0,11)"
.LASF855:
	.string	"CAN_F11DATA1(canx) REG32((canx) + 0x29CU)"
.LASF745:
	.string	"BKP_DATA32 REG16((BKP) + 0x98U)"
.LASF1831:
	.string	"GPIO_PIN_SOURCE_8 ((uint8_t)0x08U)"
.LASF1055:
	.string	"CAN_BT_SJW_2TQ ((uint8_t)0x01U)"
.LASF517:
	.string	"AFIO_BASE (APB2_BUS_BASE + 0x00000000U)"
.LASF377:
	.string	"unsigned"
.LASF477:
	.string	"WCHAR_MIN (__WCHAR_MIN__)"
.LASF1920:
	.string	"I2C_STAT0_SBSEND BIT(0)"
.LASF524:
	.string	"CRC_BASE (AHB1_BUS_BASE + 0x0000B000U)"
.LASF2234:
	.string	"SPI_CRC_RX ((uint8_t)0x01U)"
.LASF2421:
	.string	"TIMER_INT_FLAG_CH2 TIMER_INT_CH2"
.LASF2278:
	.string	"TIMER_CAR(timerx) REG32((timerx) + 0x2CU)"
.LASF2709:
	.string	"USART_CPH_2CK CTL1_CPH(1)"
.LASF2271:
	.string	"TIMER_INTF(timerx) REG32((timerx) + 0x10U)"
.LASF1527:
	.string	"FMC_PID_PID BITS(0,31)"
.LASF140:
	.string	"__GCC_IEC_559_COMPLEX 0"
.LASF153:
	.string	"__FLT_NORM_MAX__ 3.40282346638528859811704183484516925e+38F"
.LASF219:
	.string	"__FLT32_HAS_INFINITY__ 1"
.LASF3057:
	.string	"RCU_PLL_MUL8 CFG0_PLLMF(6)"
.LASF1485:
	.string	"GD32VF103_FMC_H "
.LASF2358:
	.string	"TIMER_CHCTL0_CH1COMCEN BIT(15)"
.LASF2608:
	.string	"GD32VF103_USART_H "
.LASF24:
	.string	"__CHAR_BIT__ 8"
.LASF3187:
	.string	"uint16_t"
.LASF2570:
	.string	"TIMER_SMCFG_TRGSEL_ITI1 SMCFG_TRGSEL(1)"
.LASF2556:
	.string	"TIMER_UPDATECTL_CCU ((uint32_t)0x00000000U)"
.LASF3285:
	.string	"RCU_INT_FLAG_IRC8MSTB"
.LASF717:
	.string	"BKP_DATA4 REG16((BKP) + 0x14U)"
.LASF203:
	.string	"__FLT16_HAS_DENORM__ 1"
.LASF1192:
	.string	"DAC_WAVE_BIT_WIDTH_6 DWBW(5)"
.LASF2095:
	.string	"RTC_CTL_CMF BIT(4)"
.LASF2785:
	.string	"_WCHAR_T_DEFINED "
.LASF480:
	.string	"WINT_MIN (__WINT_MIN__)"
.LASF733:
	.string	"BKP_DATA20 REG16((BKP) + 0x68U)"
.LASF2048:
	.string	"PMU_CTL_STBMOD BIT(1)"
.LASF1826:
	.string	"GPIO_PIN_SOURCE_3 ((uint8_t)0x03U)"
.LASF1931:
	.string	"I2C_STAT0_PECERR BIT(12)"
.LASF336:
	.string	"HXTAL_STARTUP_TIMEOUT ((uint16_t)0xFFFF)"
.LASF254:
	.string	"__FLT32X_MIN_10_EXP__ (-307)"
.LASF1355:
	.string	"EXMC_NOR_DATABUS_WIDTH_16B SNCTL_NRW(1)"
.LASF1403:
	.string	"EXTI_EVEN_EVEN13 BIT(13)"
.LASF2557:
	.string	"TIMER_UPDATECTL_CCUTRI TIMER_CTL1_CCUC"
.LASF638:
	.string	"ADC0_1_EXTTRIG_INSERTED_NONE CTL1_ETSIC(7)"
.LASF3152:
	.string	"RCU_PLL2_MUL12 CFG1_PLL2MF(10)"
.LASF1535:
	.string	"FMC_REG_OFFSET_GET(flag) ((uint32_t)(flag) >> 12)"
.LASF543:
	.string	"ADC_RSQ1(adcx) REG32((adcx) + 0x30U)"
.LASF59:
	.string	"__INT_FAST32_TYPE__ int"
.LASF2583:
	.string	"TIMER_TRI_OUT_SRC_O1CPRE CTL1_MMC(5)"
.LASF92:
	.string	"__INTMAX_WIDTH__ 64"
.LASF2160:
	.string	"SPI_DATA_DATA BITS(0,15)"
.LASF3039:
	.string	"RCU_APB2_CKAHB_DIV8 CFG0_APB2PSC(6)"
.LASF2934:
	.string	"RCU_AHBEN_DMA0EN BIT(0)"
.LASF287:
	.string	"__GCC_ATOMIC_BOOL_LOCK_FREE 1"
.LASF636:
	.string	"ADC0_1_EXTTRIG_INSERTED_T3_TRGO CTL1_ETSIC(5)"
.LASF184:
	.string	"__LDBL_NORM_MAX__ 1.18973149535723176508575932662800702e+4932L"
.LASF1889:
	.string	"I2C_STAT1(i2cx) REG32((i2cx) + 0x18U)"
.LASF339:
	.string	"IRC40K_VALUE ((uint32_t)40000)"
.LASF1736:
	.string	"GPIO_LOCK_LK4 BIT(4)"
.LASF2957:
	.string	"RCU_APB1EN_TIMER6EN BIT(5)"
.LASF907:
	.string	"CAN_TSTAT_MTFNERR1 BIT(9)"
.LASF671:
	.string	"ADC_CHANNEL_10 ((uint8_t)0x0AU)"
.LASF1022:
	.string	"TMDATA1_DB5(regval) (BITS(8,15) & ((uint32_t)(regval) << 8))"
.LASF3065:
	.string	"RCU_PLL_MUL16 CFG0_PLLMF(14)"
.LASF3035:
	.string	"CFG0_APB2PSC(regval) (BITS(11,13) & ((uint32_t)(regval) << 11))"
.LASF1689:
	.string	"GPIO_BOP_BOP5 BIT(5)"
.LASF2752:
	.string	"_PTRDIFF_T_ "
.LASF2713:
	.string	"CLT2_DENR(regval) (BIT(6) & ((uint32_t)(regval) << 6))"
.LASF484:
	.string	"UINT16_C(x) __UINT16_C(x)"
.LASF3296:
	.string	"RCU_INT_FLAG_PLLSTB_CLR"
.LASF1636:
	.string	"GPIO_CTL1_MD8 BITS(0, 1)"
.LASF651:
	.string	"RSQ0_RL(regval) (BITS(20,23) & ((uint32_t)(regval) << 20))"
.LASF3170:
	.string	"SEL_HXTAL ((uint16_t)1U)"
.LASF2317:
	.string	"TIMER_DMAINTEN_CH2IE BIT(3)"
.LASF716:
	.string	"BKP_DATA3 REG16((BKP) + 0x10U)"
.LASF848:
	.string	"CAN_F4DATA1(canx) REG32((canx) + 0x264U)"
.LASF1884:
	.string	"I2C_CTL1(i2cx) REG32((i2cx) + 0x04U)"
.LASF1523:
	.string	"FMC_OBSTAT_USER BITS(2,9)"
.LASF319:
	.string	"__ELF__ 1"
.LASF1782:
	.string	"AFIO_EXTI15_SS BITS(12, 15)"
.LASF238:
	.string	"__FLT128_MIN_EXP__ (-16381)"
.LASF130:
	.string	"__INT_FAST64_MAX__ 0x7fffffffffffffffLL"
.LASF2334:
	.string	"TIMER_INTF_CMTIF BIT(5)"
.LASF2129:
	.string	"SPI_CTL0_CKPH BIT(0)"
.LASF2914:
	.string	"RCU_APB1RST_TIMER1RST BIT(0)"
.LASF2661:
	.string	"USART_CTL2_NKEN BIT(4)"
.LASF2295:
	.string	"TIMER_CTL1_CCSE BIT(0)"
.LASF571:
	.string	"ADC_CTL1_CTN BIT(1)"
.LASF3300:
	.string	"rcu_int_flag_clear_enum"
.LASF2532:
	.string	"TIMER_CCXN_ENABLE ((uint16_t)0x0004U)"
.LASF2383:
	.string	"TIMER_CHCTL2_CH1NEN BIT(6)"
.LASF2463:
	.string	"TIMER_DMACFG_DMATA_CH2CV DMACFG_DMATA(15)"
.LASF743:
	.string	"BKP_DATA30 REG16((BKP) + 0x90U)"
.LASF817:
	.string	"CAN_F1DATA0(canx) REG32((canx) + 0x248U)"
.LASF2017:
	.string	"FWDGT_FLAG_PUD FWDGT_STAT_PUD"
.LASF2849:
	.string	"RCU_RSTSCK REG32(RCU + 0x24U)"
.LASF971:
	.string	"CAN_TMDATA1_DB6 BITS(16,23)"
.LASF1229:
	.string	"DMA1 (DMA_BASE + 0x0400U)"
.LASF2123:
	.string	"SPI_DATA(spix) REG32((spix) + 0x0CU)"
.LASF2313:
	.string	"TIMER_SMCFG_ETP BIT(15)"
.LASF2621:
	.string	"USART_STAT_PERR BIT(0)"
.LASF1038:
	.string	"GET_ERR_TECNT(regval) GET_BITS((uint32_t)(regval), 16U, 23U)"
.LASF2053:
	.string	"PMU_CTL_BKPWEN BIT(8)"
.LASF3002:
	.string	"AHBRST_REG_OFFSET 0x28U"
.LASF433:
	.string	"INT8_MIN (-__INT8_MAX__ - 1)"
.LASF2298:
	.string	"TIMER_CTL1_MMC BITS(4,6)"
.LASF3337:
	.string	"apb2_exp"
.LASF2112:
	.string	"RTC_FLAG_ALARM RTC_CTL_ALRMIF"
.LASF1200:
	.string	"DAC_LFSR_BITS1_0 DAC_WAVE_BIT_WIDTH_2"
.LASF3345:
	.string	"rcu_osci_bypass_mode_disable"
.LASF272:
	.string	"__FLT64X_DECIMAL_DIG__ 36"
.LASF654:
	.string	"ADC_INSERTED_CHANNEL ((uint8_t)0x02U)"
.LASF1272:
	.string	"DMA_CHXCTL_DIR BIT(4)"
.LASF1457:
	.string	"EXTI_SWIEV_SWIEV10 BIT(10)"
.LASF867:
	.string	"CAN_F23DATA1(canx) REG32((canx) + 0x2FCU)"
.LASF3221:
	.string	"RCU_AF"
.LASF587:
	.string	"ADC_RSQX_RSQN BITS(0,4)"
.LASF132:
	.string	"__UINT_FAST8_MAX__ 0xffffffffU"
.LASF3087:
	.string	"CFG0_CKOUT0SEL(regval) (BITS(24,27) & ((uint32_t)(regval) << 24))"
.LASF463:
	.string	"INT_FAST32_MIN (-__INT_FAST32_MAX__ - 1)"
.LASF1981:
	.string	"I2C_PECTRANS_DISABLE ((uint32_t)0x00000000U)"
.LASF3012:
	.string	"RCU_CKSYSSRC_IRC8M CFG0_SCS(0)"
.LASF1360:
	.string	"EXMC_BANK0_NORSRAM_REGION0 ((uint32_t)0x00000000U)"
.LASF1002:
	.string	"STAT_REG_OFFSET ((uint8_t)0x04U)"
.LASF2731:
	.string	"WWDGT_CFG REG32((WWDGT) + 0x00000004U)"
.LASF2760:
	.string	"_SIZE_T "
.LASF397:
	.string	"__FAST8 "
.LASF3069:
	.string	"RCU_PLL_MUL20 (PLLMF_4 | CFG0_PLLMF(3))"
.LASF2875:
	.string	"RCU_CFG0_PLLMF BITS(18,21)"
.LASF3405:
	.string	"rcu_deinit"
.LASF575:
	.string	"ADC_CTL1_DAL BIT(11)"
.LASF2168:
	.string	"SPI_I2SCTL_PCMSMOD BIT(7)"
.LASF2605:
	.string	"TIMER_HALLINTERFACE_DISABLE ((uint32_t)0x00000000U)"
.LASF3377:
	.string	"rcu_pll1_config"
.LASF673:
	.string	"ADC_CHANNEL_12 ((uint8_t)0x0CU)"
.LASF3143:
	.string	"RCU_PLL1_MUL14 CFG1_PLL1MF(12)"
.LASF170:
	.string	"__DBL_EPSILON__ ((double)2.22044604925031308084726333618164062e-16L)"
.LASF346:
	.string	"_NEWLIB_VERSION \"4.1.0\""
.LASF1949:
	.string	"I2C_BIT_POS(val) ((uint32_t)(val) & 0x1FU)"
.LASF793:
	.string	"CAN_TMDATA00(canx) REG32((canx) + 0x188U)"
.LASF882:
	.string	"CAN_CTL_IWMOD BIT(0)"
.LASF1787:
	.string	"GPIO_MODE_IN_FLOATING ((uint8_t)0x04U)"
.LASF1939:
	.string	"I2C_STAT1_HSTSMB BIT(6)"
.LASF1728:
	.string	"GPIO_BC_CR12 BIT(12)"
.LASF1475:
	.string	"EXTI_PD_PD9 BIT(9)"
.LASF707:
	.string	"ADC_OVERSAMPLING_RATIO_MUL32 OVSCR_OVSR(4)"
.LASF410:
	.string	"_UINT16_T_DECLARED "
.LASF2896:
	.string	"RCU_INT_LXTALSTBIC BIT(17)"
.LASF887:
	.string	"CAN_CTL_AWU BIT(5)"
.LASF2423:
	.string	"TIMER_INT_FLAG_CMT TIMER_INT_CMT"
.LASF1674:
	.string	"GPIO_OCTL_OCTL6 BIT(6)"
.LASF1414:
	.string	"EXTI_RTEN_RTEN5 BIT(5)"
.LASF3242:
	.string	"RCU_TIMER6RST"
.LASF295:
	.string	"__GCC_ATOMIC_LLONG_LOCK_FREE 1"
.LASF326:
	.string	"RT_USING_NEWLIB 1"
.LASF2351:
	.string	"TIMER_CHCTL0_CH0COMSEN BIT(3)"
.LASF902:
	.string	"CAN_TSTAT_MTFNERR0 BIT(1)"
.LASF2913:
	.string	"RCU_APB2RST_USART0RST BIT(14)"
.LASF3270:
	.string	"RCU_FLAG_HXTALSTB"
.LASF125:
	.string	"__INT_FAST8_WIDTH__ 32"
.LASF457:
	.string	"INT_FAST8_MIN (-__INT_FAST8_MAX__ - 1)"
.LASF695:
	.string	"ADC_OVERSAMPLING_SHIFT_2B OVSCR_OVSS(2)"
.LASF1607:
	.string	"GPIO_CTL1(gpiox) REG32((gpiox) + 0x04U)"
.LASF944:
	.string	"CAN_INTEN_SLPWIE BIT(17)"
.LASF1236:
	.string	"DMA_CH1CTL(dmax) REG32((dmax) + 0x1CU)"
.LASF1818:
	.string	"GPIO_EVENT_PIN_11 ((uint8_t)0x0BU)"
.LASF3054:
	.string	"RCU_PLL_MUL5 CFG0_PLLMF(3)"
.LASF131:
	.string	"__INT_FAST64_WIDTH__ 64"
.LASF1383:
	.string	"EXTI_INTEN_INTEN12 BIT(12)"
.LASF2612:
	.string	"UART4 (USART_BASE+(0x00000C00U))"
.LASF2706:
	.string	"USART_CLEN_EN CTL1_CLEN(1)"
.LASF2881:
	.string	"RCU_INT_LXTALSTBIF BIT(1)"
.LASF344:
	.string	"_SYS_FEATURES_H "
.LASF840:
	.string	"CAN_F24DATA0(canx) REG32((canx) + 0x300U)"
.LASF1707:
	.string	"GPIO_BOP_CR7 BIT(23)"
.LASF1079:
	.string	"CAN_BT_BS2_6TQ ((uint8_t)0x05U)"
.LASF600:
	.string	"ADC_FLAG_EOC ADC_STAT_EOC"
.LASF655:
	.string	"ADC_REGULAR_INSERTED_CHANNEL ((uint8_t)0x03U)"
.LASF2407:
	.string	"TIMER_DMACFG_DMATA BITS(0,4)"
.LASF2521:
	.string	"TIMER_CCHP_PROT_0 CCHP_PROT(1)"
.LASF3192:
	.string	"SUCCESS"
.LASF449:
	.string	"INT_LEAST32_MAX (__INT_LEAST32_MAX__)"
.LASF2724:
	.string	"USART_CTS_DISABLE CLT2_CTSEN(0)"
.LASF2787:
	.string	"___int_wchar_t_h "
.LASF1876:
	.string	"GPIO_SWJ_DISABLE_REMAP ((uint32_t)0x00300200U)"
.LASF1330:
	.string	"ECLIC_PRIGROUP_LEVEL3_PRIO1 3"
.LASF1569:
	.string	"OB_WP_6 ((uint32_t)0x00000040U)"
.LASF1852:
	.string	"GPIO_PIN_13 BIT(13)"
.LASF2806:
	.string	"TIMER_REG(offset) _REG32(TIMER_CTRL_ADDR, offset)"
.LASF712:
	.string	"BKP BKP_BASE"
.LASF1232:
	.string	"DMA_CH0CTL(dmax) REG32((dmax) + 0x08U)"
.LASF686:
	.string	"ADC_RESOLUTION_12B OVSCR_DRES(0)"
.LASF1166:
	.string	"DACC_R12DH_DAC1_DH BITS(16,27)"
.LASF1177:
	.string	"DAC_TRIGGER_T4_TRGO CTL_DTSEL(3)"
.LASF1058:
	.string	"CAN_BT_BS1_1TQ ((uint8_t)0x00U)"
.LASF2372:
	.string	"TIMER_CHCTL1_CH3COMCEN BIT(15)"
.LASF2197:
	.string	"SPI_PSC_16 CTL0_PSC(3)"
.LASF2829:
	.string	"ECLIC_CFG_NLBITS_LSB (1u)"
.LASF2092:
	.string	"RTC_CTL_ALRMIF BIT(1)"
.LASF622:
	.string	"ADC0_1_EXTTRIG_REGULAR_T0_CH0 CTL1_ETSRC(0)"
.LASF2952:
	.string	"RCU_APB1EN_TIMER1EN BIT(0)"
.LASF3263:
	.string	"RCU_ADC0RST"
.LASF126:
	.string	"__INT_FAST16_MAX__ 0x7fffffff"
.LASF603:
	.string	"ADC_FLAG_STRC ADC_STAT_STRC"
.LASF2454:
	.string	"TIMER_DMACFG_DMATA_CHCTL0 DMACFG_DMATA(6)"
.LASF1443:
	.string	"EXTI_FTEN_FTEN15 BIT(15)"
.LASF2072:
	.string	"PMU_FLAG_RESET_WAKEUP ((uint8_t)0x00U)"
.LASF528:
	.string	"GD32VF103_ADC_H "
.LASF262:
	.string	"__FLT32X_DENORM_MIN__ 4.94065645841246544176568792868221372e-324F32x"
.LASF1468:
	.string	"EXTI_PD_PD2 BIT(2)"
.LASF1532:
	.string	"FMC_REG_VALS(offset) (REG32(FMC + ((uint32_t)(offset) >> 12)))"
.LASF830:
	.string	"CAN_F14DATA0(canx) REG32((canx) + 0x2B0U)"
.LASF3248:
	.string	"RCU_UART3RST"
.LASF1024:
	.string	"TMDATA1_DB7(regval) (BITS(24,31) & ((uint32_t)(regval) << 24))"
.LASF2739:
	.string	"CFG_PSC(regval) (BITS(7,8) & ((uint32_t)(regval) << 7))"
.LASF199:
	.string	"__FLT16_NORM_MAX__ 6.55040000000000000000000000000000000e+4F16"
.LASF2043:
	.string	"GD32VF103_PMU_H "
.LASF3328:
	.string	"predv0sel"
.LASF847:
	.string	"CAN_F3DATA1(canx) REG32((canx) + 0x25CU)"
.LASF2004:
	.string	"FWDGT_PSC_DIV4 ((uint8_t)PSC_PSC(0))"
.LASF2691:
	.string	"USART_WM_IDLE CTL0_WM(0)"
.LASF502:
	.string	"APB1_BUS_BASE ((uint32_t)0x40000000U)"
.LASF511:
	.string	"USART_BASE (APB1_BUS_BASE + 0x00004400U)"
.LASF554:
	.string	"ADC_STAT_EOIC BIT(2)"
.LASF1877:
	.string	"GPIO_SPI2_REMAP ((uint32_t)0x00201100U)"
.LASF1995:
	.string	"FWDGT_PSC REG32((FWDGT) + 0x00000004U)"
.LASF1805:
	.string	"GPIO_PORT_SOURCE_GPIOD ((uint8_t)0x03U)"
.LASF1053:
	.string	"CAN_SILENT_LOOPBACK_MODE ((uint8_t)0x03U)"
.LASF2282:
	.string	"TIMER_CH2CV(timerx) REG32((timerx) + 0x3CU)"
.LASF1789:
	.string	"GPIO_MODE_IPU ((uint8_t)0x48U)"
.LASF1087:
	.string	"CAN_FF_EXTENDED ((uint32_t)0x00000004U)"
.LASF2794:
	.string	"NULL ((void *)0)"
.LASF444:
	.string	"UINT_LEAST16_MAX (__UINT_LEAST16_MAX__)"
.LASF1942:
	.string	"I2C_CKCFG_CLKC BITS(0,11)"
.LASF1476:
	.string	"EXTI_PD_PD10 BIT(10)"
.LASF1111:
	.string	"CAN_INT_WERR CAN_INTEN_WERRIE"
.LASF2854:
	.string	"RCU_CTL_IRC8MSTB BIT(1)"
.LASF1596:
	.string	"FMC_TIMEOUT_COUNT ((uint32_t)0x000F0000U)"
.LASF2141:
	.string	"SPI_CTL0_BDOEN BIT(14)"
.LASF2310:
	.string	"TIMER_SMCFG_ETFC BITS(8,11)"
.LASF1317:
	.string	"DMA_MEMORY_WIDTH_32BIT CHCTL_MWIDTH(2U)"
.LASF697:
	.string	"ADC_OVERSAMPLING_SHIFT_4B OVSCR_OVSS(4)"
.LASF1199:
	.string	"DAC_LFSR_BIT0 DAC_WAVE_BIT_WIDTH_1"
.LASF614:
	.string	"ADC_DAUL_REGULAL_PARALLEL CTL0_SYNCM(6)"
.LASF2264:
	.string	"TIMER4 (TIMER_BASE + 0x00000C00U)"
.LASF3312:
	.string	"RCU_IRC40K"
.LASF845:
	.string	"CAN_F1DATA1(canx) REG32((canx) + 0x24CU)"
.LASF285:
	.string	"__CHAR_UNSIGNED__ 1"
.LASF928:
	.string	"CAN_RFIFO1_RFF1 BIT(3)"
.LASF1735:
	.string	"GPIO_LOCK_LK3 BIT(3)"
.LASF792:
	.string	"CAN_TMP0(canx) REG32((canx) + 0x184U)"
.LASF1650:
	.string	"GPIO_CTL1_MD15 BITS(28, 29)"
.LASF1105:
	.string	"CAN_INT_RFNE0 CAN_INTEN_RFNEIE0"
.LASF1305:
	.string	"DMA_MEMORY_TO_PERIPHERAL ((uint8_t)0x01U)"
.LASF1265:
	.string	"DMA_INTC_FTFIFC BIT(1)"
.LASF2322:
	.string	"TIMER_DMAINTEN_UPDEN BIT(8)"
.LASF1151:
	.string	"DAC_CTL_DBOFF1 BIT(17)"
.LASF1419:
	.string	"EXTI_RTEN_RTEN10 BIT(10)"
.LASF505:
	.string	"AHB3_BUS_BASE ((uint32_t)0x60000000U)"
.LASF2772:
	.string	"_GCC_SIZE_T "
.LASF1679:
	.string	"GPIO_OCTL_OCTL11 BIT(11)"
.LASF2615:
	.string	"USART_DATA(usartx) REG32((usartx) + (0x00000004U))"
.LASF1571:
	.string	"OB_WP_8 ((uint32_t)0x00000100U)"
.LASF778:
	.string	"BKP_FLAG_TAMPER BKP_TPCS_TEF"
.LASF375:
	.string	"__STDINT_EXP(x) __ ##x ##__"
.LASF777:
	.string	"TAMPER_PIN_ACTIVE_LOW ((uint16_t)0x0002U)"
.LASF1234:
	.string	"DMA_CH0PADDR(dmax) REG32((dmax) + 0x10U)"
.LASF2792:
	.string	"__need_wchar_t"
.LASF1766:
	.string	"AFIO_PCF0_TIMER1_ITI1_REMAP BIT(29)"
.LASF974:
	.string	"CAN_RFIFOMI_FF BIT(2)"
.LASF139:
	.string	"__GCC_IEC_559 0"
.LASF1851:
	.string	"GPIO_PIN_12 BIT(12)"
.LASF206:
	.string	"__FLT32_MANT_DIG__ 24"
.LASF3243:
	.string	"RCU_WWDGTRST"
.LASF1870:
	.string	"GPIO_CAN0_PARTIAL_REMAP ((uint32_t)0x001D4000U)"
.LASF1505:
	.string	"FMC_OBKEY_OBKEY BITS(0,31)"
.LASF321:
	.string	"USE_M_TIME 1"
.LASF1221:
	.string	"DAC_TRIANGLE_AMPLITUDE_127 DAC_WAVE_BIT_WIDTH_7"
.LASF2330:
	.string	"TIMER_INTF_CH0IF BIT(1)"
.LASF2655:
	.string	"USART_CTL1_STB BITS(12,13)"
.LASF1493:
	.string	"FMC_ADDR REG32((FMC) + 0x14U)"
.LASF2404:
	.string	"TIMER_CCHP_BRKP BIT(13)"
.LASF2745:
	.string	"_STDDEF_H "
.LASF1303:
	.string	"DMA_INT_ERR DMA_CHXCTL_ERRIE"
.LASF1967:
	.string	"I2C_DUADEN_ENABLE ((uint32_t)0x00000001U)"
.LASF1458:
	.string	"EXTI_SWIEV_SWIEV11 BIT(11)"
.LASF2761:
	.string	"_SYS_SIZE_T_H "
.LASF80:
	.string	"__SHRT_WIDTH__ 16"
.LASF2229:
	.string	"I2S_CKPL_LOW ((uint32_t)0x00000000U)"
.LASF1869:
	.string	"GPIO_TIMER3_REMAP ((uint32_t)0x00001000U)"
.LASF67:
	.string	"__GXX_ABI_VERSION 1014"
.LASF1492:
	.string	"FMC_CTL REG32((FMC) + 0x10U)"
.LASF1447:
	.string	"EXTI_SWIEV_SWIEV0 BIT(0)"
.LASF2970:
	.string	"RCU_APB1EN_PMUEN BIT(28)"
.LASF684:
	.string	"ADC_INT_FLAG_EOIC ADC_STAT_EOIC"
.LASF1019:
	.string	"TMDATA0_DB2(regval) (BITS(16,23) & ((uint32_t)(regval) << 16))"
.LASF361:
	.string	"__SSP_FORTIFY_LEVEL 0"
.LASF2118:
	.string	"SPI1 SPI_BASE"
.LASF2082:
	.string	"RTC_DIVH REG32(RTC + 0x10U)"
.LASF2765:
	.string	"_SIZE_T_ "
.LASF3118:
	.string	"RCU_PREDV0_DIV16 CFG1_PREDV0(15)"
.LASF659:
	.string	"ADC_INSERTED_CHANNEL_2 ((uint8_t)0x02U)"
.LASF2222:
	.string	"I2S_MODE_MASTERRX I2SCTL_I2SOPMOD(3)"
.LASF166:
	.string	"__DBL_DECIMAL_DIG__ 17"
.LASF288:
	.string	"__GCC_ATOMIC_CHAR_LOCK_FREE 1"
.LASF115:
	.string	"__INT_LEAST64_WIDTH__ 64"
.LASF1204:
	.string	"DAC_LFSR_BITS5_0 DAC_WAVE_BIT_WIDTH_6"
.LASF1408:
	.string	"EXTI_EVEN_EVEN18 BIT(18)"
.LASF3132:
	.string	"RCU_PREDV1_DIV13 CFG1_PREDV1(12)"
.LASF783:
	.string	"CAN_CTL(canx) REG32((canx) + 0x00U)"
.LASF3155:
	.string	"RCU_PLL2_MUL15 CFG1_PLL2MF(13)"
.LASF280:
	.string	"__FLT64X_HAS_QUIET_NAN__ 1"
.LASF569:
	.string	"ADC_CTL0_RWDEN BIT(23)"
.LASF1645:
	.string	"GPIO_CTL1_CTL12 BITS(18, 19)"
.LASF2354:
	.string	"TIMER_CHCTL0_CH1MS BITS(8,9)"
.LASF2499:
	.string	"TIMER_PSC_RELOAD_NOW TIMER_SWEVG_UPG"
.LASF2542:
	.string	"TIMER_OC_MODE_TIMING ((uint16_t)0x0000U)"
.LASF1701:
	.string	"GPIO_BOP_CR1 BIT(17)"
.LASF890:
	.string	"CAN_CTL_SWRST BIT(15)"
.LASF2508:
	.string	"TIMER_SP_MODE_REPETITIVE ((uint32_t)0x00000000U)"
.LASF699:
	.string	"ADC_OVERSAMPLING_SHIFT_6B OVSCR_OVSS(6)"
.LASF641:
	.string	"ADC_SAMPLETIME_7POINT5 SAMPTX_SPT(1)"
.LASF3001:
	.string	"APB2EN_REG_OFFSET 0x18U"
.LASF268:
	.string	"__FLT64X_MIN_EXP__ (-16381)"
.LASF1913:
	.string	"I2C_SADDR0_ADDRESS0 BIT(0)"
.LASF2186:
	.string	"SPI_NSS_HARD ((uint32_t)0x00000000U)"
.LASF1698:
	.string	"GPIO_BOP_BOP14 BIT(14)"
.LASF2973:
	.string	"RCU_BDCTL_LXTALSTB BIT(1)"
.LASF3074:
	.string	"RCU_PLL_MUL25 (PLLMF_4 | CFG0_PLLMF(8))"
.LASF822:
	.string	"CAN_F6DATA0(canx) REG32((canx) + 0x270U)"
.LASF544:
	.string	"ADC_RSQ2(adcx) REG32((adcx) + 0x34U)"
.LASF337:
	.string	"IRC8M_VALUE ((uint32_t)8000000)"
.LASF1463:
	.string	"EXTI_SWIEV_SWIEV16 BIT(16)"
.LASF87:
	.string	"__SIZE_WIDTH__ 32"
.LASF3275:
	.string	"RCU_FLAG_IRC40KSTB"
.LASF1075:
	.string	"CAN_BT_BS2_2TQ ((uint8_t)0x01U)"
.LASF714:
	.string	"BKP_DATA1 REG16((BKP) + 0x08U)"
.LASF3384:
	.string	"pll_src"
.LASF2762:
	.string	"_T_SIZE_ "
.LASF2196:
	.string	"SPI_PSC_8 CTL0_PSC(2)"
.LASF1809:
	.string	"GPIO_EVENT_PIN_2 ((uint8_t)0x02U)"
.LASF1600:
	.string	"GPIOA (GPIO_BASE + 0x00000000U)"
.LASF3028:
	.string	"RCU_AHB_CKSYS_DIV512 CFG0_AHBPSC(15)"
.LASF2928:
	.string	"RCU_APB1RST_I2C1RST BIT(22)"
.LASF473:
	.string	"SIG_ATOMIC_MIN (-__STDINT_EXP(INT_MAX) - 1)"
.LASF2413:
	.string	"TIMER_INT_CH2 TIMER_DMAINTEN_CH2IE"
.LASF1603:
	.string	"GPIOD (GPIO_BASE + 0x00000C00U)"
.LASF402:
	.string	"__LEAST16 \"h\""
.LASF2609:
	.string	"USART1 USART_BASE"
.LASF3207:
	.string	"RCU_SPI1"
.LASF1665:
	.string	"GPIO_ISTAT_ISTAT13 BIT(13)"
.LASF442:
	.string	"INT_LEAST16_MIN (-__INT_LEAST16_MAX__ - 1)"
.LASF1855:
	.string	"GPIO_PIN_ALL BITS(0, 15)"
.LASF1212:
	.string	"DAC_ALIGN_12B_R DATA_ALIGN(0)"
.LASF538:
	.string	"ADC_IOFF2(adcx) REG32((adcx) + 0x1CU)"
.LASF2323:
	.string	"TIMER_DMAINTEN_CH0DEN BIT(9)"
.LASF52:
	.string	"__INT_LEAST64_TYPE__ long long int"
.LASF3392:
	.string	"ck_ahb"
.LASF1827:
	.string	"GPIO_PIN_SOURCE_4 ((uint8_t)0x04U)"
.LASF191:
	.string	"__FLT16_MANT_DIG__ 11"
.LASF1090:
	.string	"CAN_RFIF_RFL_MASK ((uint32_t)0x00000003U)"
.LASF1235:
	.string	"DMA_CH0MADDR(dmax) REG32((dmax) + 0x14U)"
.LASF2893:
	.string	"RCU_INT_PLL1STBIE BIT(13)"
.LASF536:
	.string	"ADC_IOFF0(adcx) REG32((adcx) + 0x14U)"
.LASF3148:
	.string	"RCU_PLL2_MUL8 CFG1_PLL2MF(6)"
.LASF1530:
	.string	"FMC_BIT_POS(val) ((uint32_t)(val) & 0x1FU)"
.LASF2333:
	.string	"TIMER_INTF_CH3IF BIT(4)"
.LASF1068:
	.string	"CAN_BT_BS1_11TQ ((uint8_t)0x0AU)"
.LASF770:
	.string	"BKP_DATA0_9(number) REG16((BKP) + 0x04U + (number) * 0x04U)"
.LASF1206:
	.string	"DAC_LFSR_BITS7_0 DAC_WAVE_BIT_WIDTH_8"
.LASF1397:
	.string	"EXTI_EVEN_EVEN7 BIT(7)"
.LASF1899:
	.string	"I2C_CTL0_SS BIT(7)"
.LASF632:
	.string	"ADC0_1_EXTTRIG_INSERTED_T0_CH3 CTL1_ETSIC(1)"
.LASF2807:
	.string	"TIMER_FREQ ((uint32_t)SystemCoreClock/4)"
.LASF2206:
	.string	"I2S_AUDIOSAMPLE_32K ((uint32_t)32000U)"
.LASF2347:
	.string	"TIMER_SWEVG_TRGG BIT(6)"
.LASF240:
	.string	"__FLT128_MAX_EXP__ 16384"
.LASF1910:
	.string	"I2C_CTL1_BUFIE BIT(10)"
.LASF2151:
	.string	"SPI_STAT_RBNE BIT(0)"
.LASF3394:
	.string	"ck_sys"
.LASF1974:
	.string	"I2C_DMA_ON I2C_CTL1_DMAON"
.LASF1415:
	.string	"EXTI_RTEN_RTEN6 BIT(6)"
.LASF2725:
	.string	"CTL2_IRLP(regval) (BIT(2) & ((uint32_t)(regval) << 2))"
.LASF2472:
	.string	"TIMER_DMACFG_DMATC_5TRANSFER DMACFG_DMATC(4)"
.LASF1386:
	.string	"EXTI_INTEN_INTEN15 BIT(15)"
.LASF1179:
	.string	"DAC_TRIGGER_T3_TRGO CTL_DTSEL(5)"
.LASF2982:
	.string	"RCU_RSTSCK_PORRSTF BIT(27)"
.LASF2170:
	.string	"SPI_I2SCTL_I2SEN BIT(10)"
.LASF1881:
	.string	"I2C0 I2C_BASE"
.LASF405:
	.string	"_SYS__STDINT_H "
.LASF3215:
	.string	"RCU_CAN0"
.LASF3184:
	.string	"long long int"
.LASF164:
	.string	"__DBL_MAX_EXP__ 1024"
.LASF2981:
	.string	"RCU_RSTSCK_EPRSTF BIT(26)"
.LASF2377:
	.string	"TIMER_CHCTL2_CH0EN BIT(0)"
.LASF91:
	.string	"__UINTMAX_C(c) c ## ULL"
.LASF1987:
	.string	"DATA_RECV(regval) GET_BITS((uint32_t)(regval), 0, 7)"
.LASF3340:
	.string	"rcu_deepsleep_voltage_set"
.LASF2126:
	.string	"SPI_TCRC(spix) REG32((spix) + 0x18U)"
.LASF701:
	.string	"ADC_OVERSAMPLING_SHIFT_8B OVSCR_OVSS(8)"
.LASF2565:
	.string	"TIMER_IC_PSC_DIV2 ((uint16_t)0x0004U)"
.LASF297:
	.string	"__GCC_ATOMIC_POINTER_LOCK_FREE 2"
.LASF1380:
	.string	"EXTI_INTEN_INTEN9 BIT(9)"
.LASF1845:
	.string	"GPIO_PIN_6 BIT(6)"
.LASF2838:
	.string	"ECLIC_GROUP_LEVEL4_PRIO0 4"
.LASF1071:
	.string	"CAN_BT_BS1_14TQ ((uint8_t)0x0DU)"
.LASF2992:
	.string	"RCU_CFG1_PREDV0SEL BIT(16)"
.LASF3096:
	.string	"RCU_CKOUT0SRC_CKPLL2 CFG0_CKOUT0SEL(11)"
.LASF516:
	.string	"DAC_BASE (APB1_BUS_BASE + 0x00007400U)"
.LASF1526:
	.string	"FMC_WSEN_WSEN BIT(0)"
.LASF570:
	.string	"ADC_CTL1_ADCON BIT(0)"
.LASF2368:
	.string	"TIMER_CHCTL1_CH3MS BITS(8,9)"
.LASF873:
	.string	"CAN_TMP(canx,bank) REG32((canx) + 0x184U + ((bank) * 0x10U))"
.LASF3256:
	.string	"RCU_DACRST"
.LASF1792:
	.string	"GPIO_MODE_AF_OD ((uint8_t)0x1CU)"
.LASF1390:
	.string	"EXTI_EVEN_EVEN0 BIT(0)"
.LASF878:
	.string	"CAN_RFIFOMI(canx,bank) REG32((canx) + 0x1B0U + ((bank) * 0x10U))"
.LASF1223:
	.string	"DAC_TRIANGLE_AMPLITUDE_511 DAC_WAVE_BIT_WIDTH_9"
.LASF682:
	.string	"ADC_INT_FLAG_WDE ADC_STAT_WDE"
.LASF2715:
	.string	"USART_DENR_DISABLE CLT2_DENR(0)"
.LASF1743:
	.string	"GPIO_LOCK_LK11 BIT(11)"
.LASF137:
	.string	"__INTPTR_WIDTH__ 32"
.LASF2173:
	.string	"SPI_I2SPSC_OF BIT(8)"
.LASF12:
	.string	"__ATOMIC_RELEASE 3"
.LASF1138:
	.string	"DACC_R12DH REG32(DAC + 0x20U)"
.LASF1629:
	.string	"GPIO_CTL0_CTL4 BITS(18, 19)"
.LASF458:
	.string	"INT_FAST8_MAX (__INT_FAST8_MAX__)"
.LASF1294:
	.string	"DMA_INT_FLAG_FTF DMA_INTF_FTFIF"
.LASF3049:
	.string	"PLLMF_4 RCU_CFG0_PLLMF_4"
.LASF2362:
	.string	"TIMER_CHCTL0_CH1CAPFLT BITS(12,15)"
.LASF589:
	.string	"ADC_ISQ_ISQN BITS(0,4)"
.LASF1762:
	.string	"AFIO_PCF0_PD01_REMAP BIT(15)"
.LASF3309:
	.string	"RCU_HXTAL"
.LASF2390:
	.string	"TIMER_CHCTL2_CH3P BIT(13)"
.LASF2101:
	.string	"RTC_CNTH_CNT BITS(0,15)"
.LASF927:
	.string	"CAN_RFIFO1_RFL1 BITS(0,1)"
.LASF2823:
	.string	"ECLIC_INT_ATTR_TRIG_EDGE 0x02"
.LASF1556:
	.string	"OB_SPC_SPC_N ((uint32_t)0x0000FF00U)"
.LASF1624:
	.string	"GPIO_CTL0_MD2 BITS(8, 9)"
.LASF1292:
	.string	"DMA_CHINTF_RESET_VALUE (DMA_INTF_GIF | DMA_INTF_FTFIF | DMA_INTF_HTFIF | DMA_INTF_ERRIF)"
.LASF1388:
	.string	"EXTI_INTEN_INTEN17 BIT(17)"
.LASF186:
	.string	"__LDBL_EPSILON__ 1.92592994438723585305597794258492732e-34L"
.LASF1933:
	.string	"I2C_STAT0_SMBALT BIT(15)"
.LASF2236:
	.string	"SPI_I2S_INT_RBNE ((uint8_t)0x01U)"
.LASF1218:
	.string	"DAC_TRIANGLE_AMPLITUDE_15 DAC_WAVE_BIT_WIDTH_4"
.LASF2954:
	.string	"RCU_APB1EN_TIMER3EN BIT(2)"
.LASF2735:
	.string	"WWDGT_CFG_WIN BITS(0,6)"
.LASF3072:
	.string	"RCU_PLL_MUL23 (PLLMF_4 | CFG0_PLLMF(6))"
.LASF143:
	.string	"__DEC_EVAL_METHOD__ 2"
.LASF2518:
	.string	"TIMER_OUTAUTO_DISABLE ((uint16_t)0x0000U)"
.LASF1729:
	.string	"GPIO_BC_CR13 BIT(13)"
.LASF225:
	.string	"__FLT64_MAX_EXP__ 1024"
.LASF2939:
	.string	"RCU_AHBEN_EXMCEN BIT(8)"
.LASF1213:
	.string	"DAC_ALIGN_12B_L DATA_ALIGN(1)"
.LASF1652:
	.string	"GPIO_ISTAT_ISTAT0 BIT(0)"
.LASF2697:
	.string	"USART_STB_1BIT CTL1_STB(0)"
.LASF2933:
	.string	"RCU_APB1RST_DACRST BIT(29)"
.LASF2836:
	.string	"ECLIC_GROUP_LEVEL2_PRIO2 2"
.LASF1944:
	.string	"I2C_CKCFG_FAST BIT(15)"
.LASF2736:
	.string	"WWDGT_CFG_PSC BITS(7,8)"
.LASF893:
	.string	"CAN_STAT_SLPWS BIT(1)"
.LASF2708:
	.string	"USART_CPH_1CK CTL1_CPH(0)"
.LASF1243:
	.string	"DMA_CH2MADDR(dmax) REG32((dmax) + 0x3CU)"
.LASF1036:
	.string	"GET_RFIFOMDATA1_DB7(regval) GET_BITS((uint32_t)(regval), 24U, 31U)"
.LASF2130:
	.string	"SPI_CTL0_CKPL BIT(1)"
.LASF2540:
	.string	"TIMER_OCN_IDLE_STATE_HIGH ((uint16_t)0x0200U)"
.LASF1862:
	.string	"GPIO_TIMER0_PARTIAL_REMAP ((uint32_t)0x00160040U)"
.LASF1007:
	.string	"BT_BAUDPSC(regval) (BITS(0,9) & ((uint32_t)(regval) << 0))"
.LASF3230:
	.string	"RCU_SPI0"
.LASF1501:
	.string	"OB_WP2 REG16((OB) + 0x0CU)"
.LASF1578:
	.string	"OB_WP_15 ((uint32_t)0x00008000U)"
.LASF2175:
	.string	"SPI_MASTER (SPI_CTL0_MSTMOD | SPI_CTL0_SWNSS)"
.LASF1032:
	.string	"GET_RFIFOMDATA0_DB3(regval) GET_BITS((uint32_t)(regval), 24U, 31U)"
.LASF588:
	.string	"ADC_RSQ0_RL BITS(20,23)"
.LASF5:
	.string	"__GNUC__ 10"
.LASF2357:
	.string	"TIMER_CHCTL0_CH1COMCTL BITS(12,14)"
.LASF2446:
	.string	"TIMER_DMAREQUEST_CHANNELEVENT ((uint32_t)0x00000000U)"
.LASF2251:
	.string	"SPI_FLAG_FERR SPI_STAT_FERR"
.LASF2730:
	.string	"WWDGT_CTL REG32((WWDGT) + 0x00000000U)"
.LASF647:
	.string	"ADC_SAMPLETIME_239POINT5 SAMPTX_SPT(7)"
.LASF3037:
	.string	"RCU_APB2_CKAHB_DIV2 CFG0_APB2PSC(4)"
.LASF679:
	.string	"ADC_INT_WDE ADC_STAT_WDE"
.LASF1835:
	.string	"GPIO_PIN_SOURCE_12 ((uint8_t)0x0CU)"
.LASF1028:
	.string	"GET_RFIFOMP_FI(regval) GET_BITS((uint32_t)(regval), 8U, 15U)"
.LASF2348:
	.string	"TIMER_SWEVG_BRKG BIT(7)"
.LASF1301:
	.string	"DMA_INT_FTF DMA_CHXCTL_FTFIE"
.LASF2223:
	.string	"I2SCTL_I2SSTD(regval) (BITS(4,5) & ((uint32_t)(regval) << 4))"
.LASF2102:
	.string	"RTC_CNTL_CNT BITS(0,15)"
.LASF181:
	.string	"__DECIMAL_DIG__ 36"
.LASF97:
	.string	"__INT16_MAX__ 0x7fff"
.LASF1649:
	.string	"GPIO_CTL1_CTL14 BITS(26, 27)"
.LASF2779:
	.string	"_T_WCHAR_ "
.LASF2041:
	.string	"DBG_LOW_POWER_DEEPSLEEP DBG_CTL_DSLP_HOLD"
.LASF3071:
	.string	"RCU_PLL_MUL22 (PLLMF_4 | CFG0_PLLMF(5))"
.LASF985:
	.string	"CAN_RFIFOMDATA1_DB5 BITS(8,15)"
.LASF2976:
	.string	"RCU_BDCTL_RTCEN BIT(15)"
.LASF135:
	.string	"__UINT_FAST64_MAX__ 0xffffffffffffffffULL"
.LASF1640:
	.string	"GPIO_CTL1_MD10 BITS(8, 9)"
.LASF1326:
	.string	"GD32VF103_ECLIC_H "
.LASF1985:
	.string	"I2C_ARP_DISABLE ((uint32_t)0x00000000U)"
.LASF495:
	.string	"BITS(start,end) ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end))))"
.LASF470:
	.string	"INTMAX_MIN (-INTMAX_MAX - 1)"
.LASF1481:
	.string	"EXTI_PD_PD15 BIT(15)"
.LASF3042:
	.string	"RCU_CKADC_CKAPB2_DIV4 ((uint32_t)0x00000001U)"
.LASF2057:
	.string	"PMU_CS_WUPEN BIT(8)"
.LASF791:
	.string	"CAN_TMI0(canx) REG32((canx) + 0x180U)"
.LASF2865:
	.string	"RCU_CTL_PLL2EN BIT(28)"
.LASF2884:
	.string	"RCU_INT_PLLSTBIF BIT(4)"
.LASF2796:
	.string	"offsetof(TYPE,MEMBER) __builtin_offsetof (TYPE, MEMBER)"
.LASF1161:
	.string	"DAC0_R8DH_DAC0_DH BITS(0,7)"
.LASF2774:
	.string	"__size_t "
.LASF2211:
	.string	"I2SCTL_DTLEN(regval) (BITS(1,2) & ((uint32_t)(regval) << 1))"
.LASF3349:
	.string	"rcu_osci_on"
.LASF3274:
	.string	"RCU_FLAG_LXTALSTB"
.LASF2892:
	.string	"RCU_INT_PLLSTBIE BIT(12)"
.LASF2755:
	.string	"_GCC_PTRDIFF_T "
.LASF2994:
	.string	"RCU_CFG1_I2S2SEL BIT(18)"
.LASF119:
	.string	"__UINT16_C(c) c"
.LASF1865:
	.string	"GPIO_TIMER1_PARTIAL_REMAP1 ((uint32_t)0x00180200U)"
.LASF1424:
	.string	"EXTI_RTEN_RTEN15 BIT(15)"
.LASF2819:
	.string	"ECLIC_INT_IE_OFFSET _AC(0x1001,UL)"
.LASF2395:
	.string	"TIMER_CH0CV_CH0VAL BITS(0,15)"
.LASF1626:
	.string	"GPIO_CTL0_MD3 BITS(12, 13)"
.LASF2651:
	.string	"USART_CTL1_CLEN BIT(8)"
.LASF836:
	.string	"CAN_F20DATA0(canx) REG32((canx) + 0x2E0U)"
.LASF1693:
	.string	"GPIO_BOP_BOP9 BIT(9)"
.LASF373:
	.string	"__EXP"
.LASF290:
	.string	"__GCC_ATOMIC_CHAR32_T_LOCK_FREE 2"
.LASF1882:
	.string	"I2C1 (I2C_BASE + 0x00000400U)"
.LASF796:
	.string	"CAN_TMP1(canx) REG32((canx) + 0x194U)"
.LASF3255:
	.string	"RCU_PMURST"
.LASF547:
	.string	"ADC_IDATA1(adcx) REG32((adcx) + 0x40U)"
.LASF2920:
	.string	"RCU_APB1RST_WWDGTRST BIT(11)"
.LASF263:
	.string	"__FLT32X_HAS_DENORM__ 1"
.LASF1601:
	.string	"GPIOB (GPIO_BASE + 0x00000400U)"
.LASF2587:
	.string	"TIMER_SLAVE_MODE_DISABLE SMCFG_SMC(0)"
.LASF937:
	.string	"CAN_INTEN_RFOIE1 BIT(6)"
.LASF920:
	.string	"CAN_TSTAT_TMLS0 BIT(29)"
.LASF1838:
	.string	"GPIO_PIN_SOURCE_15 ((uint8_t)0x0FU)"
.LASF2672:
	.string	"USART_BIT_POS(val) ((uint32_t)(val) & (0x0000001FU))"
.LASF3295:
	.string	"RCU_INT_FLAG_HXTALSTB_CLR"
.LASF1276:
	.string	"DMA_CHXCTL_PWIDTH BITS(8,9)"
.LASF2452:
	.string	"TIMER_DMACFG_DMATA_INTF DMACFG_DMATA(4)"
.LASF769:
	.string	"BKP_TPCS_TIF BIT(9)"
.LASF527:
	.string	"GD32VF103_LIBOPT_H "
.LASF2308:
	.string	"TIMER_SMCFG_TRGS BITS(4,6)"
.LASF1725:
	.string	"GPIO_BC_CR9 BIT(9)"
.LASF2396:
	.string	"TIMER_CH1CV_CH1VAL BITS(0,15)"
.LASF372:
	.string	"___int_least64_t_defined 1"
.LASF2616:
	.string	"USART_BAUD(usartx) REG32((usartx) + (0x00000008U))"
.LASF210:
	.string	"__FLT32_MAX_EXP__ 128"
.LASF861:
	.string	"CAN_F17DATA1(canx) REG32((canx) + 0x24CU)"
.LASF1348:
	.string	"EXMC_SNTCFG_AHLD BITS(4,7)"
.LASF1791:
	.string	"GPIO_MODE_OUT_PP ((uint8_t)0x10U)"
.LASF2742:
	.string	"WWDGT_CFG_PSC_DIV4 CFG_PSC(2)"
.LASF3305:
	.string	"RCU_INT_PLLSTB"
.LASF1604:
	.string	"GPIOE (GPIO_BASE + 0x00001000U)"
.LASF3257:
	.string	"RCU_AFRST"
.LASF2815:
	.string	"ECLIC_CFG_OFFSET 0x0"
.LASF3219:
	.string	"RCU_DAC"
.LASF2398:
	.string	"TIMER_CH3CV_CH3VAL BITS(0,15)"
.LASF2489:
	.string	"TIMER_EVENT_SRC_CH2G ((uint16_t)0x0008U)"
.LASF1092:
	.string	"CAN_EFID_MASK ((uint32_t)0x1FFFFFFFU)"
.LASF1117:
	.string	"CAN_INT_SLPW CAN_INTEN_SLPWIE"
.LASF2397:
	.string	"TIMER_CH2CV_CH2VAL BITS(0,15)"
.LASF304:
	.string	"__riscv_compressed 1"
.LASF266:
	.string	"__FLT64X_MANT_DIG__ 113"
.LASF1154:
	.string	"DAC_CTL_DWM1 BITS(22,23)"
.LASF2016:
	.string	"FWDGT_RLD_TIMEOUT ((uint32_t)0x000FFFFFU)"
.LASF1816:
	.string	"GPIO_EVENT_PIN_9 ((uint8_t)0x09U)"
.LASF1567:
	.string	"OB_WP_4 ((uint32_t)0x00000010U)"
.LASF1963:
	.string	"I2C_ACK_ENABLE ((uint32_t)0x00000001U)"
.LASF917:
	.string	"CAN_TSTAT_TME0 BIT(26)"
.LASF662:
	.string	"ADC_CHANNEL_1 ((uint8_t)0x01U)"
.LASF580:
	.string	"ADC_CTL1_SWICST BIT(21)"
.LASF1268:
	.string	"DMA_CHXCTL_CHEN BIT(0)"
.LASF1551:
	.string	"OB_BOOT_B0 ((uint8_t)0x08U)"
.LASF3238:
	.string	"RCU_TIMER2RST"
.LASF1302:
	.string	"DMA_INT_HTF DMA_CHXCTL_HTFIE"
.LASF1552:
	.string	"OB_USER_MASK ((uint8_t)0xF0U)"
.LASF2488:
	.string	"TIMER_EVENT_SRC_CH1G ((uint16_t)0x0004U)"
.LASF2911:
	.string	"RCU_APB2RST_TIMER0RST BIT(11)"
.LASF2811:
	.string	"_AT(T,X) ((T)(X))"
.LASF3174:
	.string	"unsigned int"
.LASF1943:
	.string	"I2C_CKCFG_DTCY BIT(14)"
.LASF3030:
	.string	"RCU_APB1_CKAHB_DIV1 CFG0_APB1PSC(0)"
.LASF425:
	.string	"__int_least64_t_defined 1"
.LASF2496:
	.string	"TIMER_COUNTER_CENTER_DOWN CTL0_CAM(1)"
.LASF771:
	.string	"BKP_DATA10_41(number) REG16((BKP) + 0x40U + ((number)-10U) * 0x04U)"
.LASF2284:
	.string	"TIMER_CCHP(timerx) REG32((timerx) + 0x44U)"
.LASF415:
	.string	"_INT64_T_DECLARED "
.LASF2426:
	.string	"TIMER_FLAG_UP TIMER_INTF_UPIF"
.LASF3172:
	.string	"OSC_STARTUP_TIMEOUT ((uint32_t)0xFFFFFU)"
.LASF1686:
	.string	"GPIO_BOP_BOP2 BIT(2)"
.LASF2522:
	.string	"TIMER_CCHP_PROT_1 CCHP_PROT(2)"
.LASF2599:
	.string	"TIMER_EXT_TRI_PSC_DIV2 SMCFG_ETPSC(1)"
.LASF1160:
	.string	"DAC0_L12DH_DAC0_DH BITS(4,15)"
.LASF1633:
	.string	"GPIO_CTL0_CTL6 BITS(26, 27)"
.LASF1549:
	.string	"OB_STDBY_NRST ((uint8_t)0x04U)"
.LASF1300:
	.string	"DMA_FLAG_ERR DMA_INTF_ERRIF"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 10.2.0"
