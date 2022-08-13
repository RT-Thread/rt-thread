	.file	"your_printf.c"
	.option nopic
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.align	1
	.globl	__wrap_printf
	.type	__wrap_printf, @function
__wrap_printf:
.LFB0:
	.file 1 "D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\RISCV\\env_Eclipse\\your_printf.c"
	.loc 1 2 1
	.cfi_startproc
	addi	sp,sp,-64
	.cfi_def_cfa_offset 64
	sw	s0,28(sp)
	.cfi_offset 8, -36
	addi	s0,sp,32
	.cfi_def_cfa 8, 32
	sw	a0,-20(s0)
	sw	a1,4(s0)
	sw	a2,8(s0)
	sw	a3,12(s0)
	sw	a4,16(s0)
	sw	a5,20(s0)
	sw	a6,24(s0)
	sw	a7,28(s0)
	.loc 1 4 1
	nop
	mv	a0,a5
	lw	s0,28(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 64
	addi	sp,sp,64
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE0:
	.size	__wrap_printf, .-__wrap_printf
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x6a
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.byte	0x1
	.4byte	.LASF330
	.byte	0xc
	.4byte	.LASF331
	.4byte	.LASF332
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.4byte	.Ldebug_macro0
	.byte	0x2
	.4byte	.LASF333
	.byte	0x1
	.byte	0x1
	.byte	0x5
	.4byte	0x54
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.byte	0x1
	.byte	0x9c
	.4byte	0x54
	.byte	0x3
	.string	"fmt"
	.byte	0x1
	.byte	0x1
	.byte	0x1f
	.4byte	0x5b
	.byte	0x2
	.byte	0x91
	.byte	0x4c
	.byte	0x4
	.byte	0
	.byte	0x5
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0x6
	.byte	0x4
	.4byte	0x68
	.byte	0x7
	.byte	0x1
	.byte	0x8
	.4byte	.LASF329
	.byte	0x8
	.4byte	0x61
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
	.byte	0x3
	.byte	0x5
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
	.byte	0x4
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0
	.byte	0x5
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
	.byte	0x6
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x7
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
	.byte	0x8
	.byte	0x26
	.byte	0
	.byte	0x49
	.byte	0x13
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
	.byte	0x4
	.byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF132:
	.string	"__UINT_FAST8_MAX__ 0xffffffffU"
.LASF233:
	.string	"__FLT64_HAS_DENORM__ 1"
.LASF129:
	.string	"__INT_FAST32_WIDTH__ 32"
.LASF202:
	.string	"__FLT16_DENORM_MIN__ 5.96046447753906250000000000000000000e-8F16"
.LASF231:
	.string	"__FLT64_EPSILON__ 2.22044604925031308084726333618164062e-16F64"
.LASF207:
	.string	"__FLT32_DIG__ 6"
.LASF23:
	.string	"__SIZEOF_SIZE_T__ 4"
.LASF44:
	.string	"__INT64_TYPE__ long long int"
.LASF246:
	.string	"__FLT128_EPSILON__ 1.92592994438723585305597794258492732e-34F128"
.LASF155:
	.string	"__FLT_EPSILON__ 1.19209289550781250000000000000000000e-7F"
.LASF114:
	.string	"__INT64_C(c) c ## LL"
.LASF31:
	.string	"__SIZEOF_POINTER__ 4"
.LASF55:
	.string	"__UINT_LEAST32_TYPE__ long unsigned int"
.LASF308:
	.string	"__riscv_muldiv 1"
.LASF84:
	.string	"__WCHAR_WIDTH__ 32"
.LASF73:
	.string	"__WCHAR_MAX__ 0x7fffffff"
.LASF91:
	.string	"__UINTMAX_C(c) c ## ULL"
.LASF124:
	.string	"__INT_FAST8_MAX__ 0x7fffffff"
.LASF48:
	.string	"__UINT64_TYPE__ long long unsigned int"
.LASF230:
	.string	"__FLT64_MIN__ 2.22507385850720138309023271733240406e-308F64"
.LASF314:
	.string	"__riscv_m 2000000"
.LASF255:
	.string	"__FLT32X_MAX_EXP__ 1024"
.LASF180:
	.string	"__LDBL_MAX_10_EXP__ 4932"
.LASF192:
	.string	"__FLT16_DIG__ 3"
.LASF10:
	.string	"__ATOMIC_SEQ_CST 5"
.LASF313:
	.string	"__riscv_i 2000000"
.LASF228:
	.string	"__FLT64_MAX__ 1.79769313486231570814527423731704357e+308F64"
.LASF301:
	.string	"__SIZEOF_WINT_T__ 4"
.LASF204:
	.string	"__FLT16_HAS_INFINITY__ 1"
.LASF185:
	.string	"__LDBL_MIN__ 3.36210314311209350626267781732175260e-4932L"
.LASF112:
	.string	"__INT_LEAST32_WIDTH__ 32"
.LASF39:
	.string	"__CHAR32_TYPE__ long unsigned int"
.LASF175:
	.string	"__LDBL_MANT_DIG__ 113"
.LASF274:
	.string	"__FLT64X_NORM_MAX__ 1.18973149535723176508575932662800702e+4932F64x"
.LASF24:
	.string	"__CHAR_BIT__ 8"
.LASF173:
	.string	"__DBL_HAS_INFINITY__ 1"
.LASF1:
	.string	"__STDC_VERSION__ 201710L"
.LASF259:
	.string	"__FLT32X_NORM_MAX__ 1.79769313486231570814527423731704357e+308F32x"
.LASF254:
	.string	"__FLT32X_MIN_10_EXP__ (-307)"
.LASF261:
	.string	"__FLT32X_EPSILON__ 2.22044604925031308084726333618164062e-16F32x"
.LASF278:
	.string	"__FLT64X_HAS_DENORM__ 1"
.LASF305:
	.string	"__riscv_atomic 1"
.LASF4:
	.string	"__STDC_HOSTED__ 1"
.LASF142:
	.string	"__FLT_EVAL_METHOD_TS_18661_3__ 0"
.LASF226:
	.string	"__FLT64_MAX_10_EXP__ 308"
.LASF170:
	.string	"__DBL_EPSILON__ ((double)2.22044604925031308084726333618164062e-16L)"
.LASF269:
	.string	"__FLT64X_MIN_10_EXP__ (-4931)"
.LASF332:
	.string	"D:\\\\rt-thread\\\\bsp\\\\gd32\\\\risc-v\\\\gd32vf103v-eval"
.LASF272:
	.string	"__FLT64X_DECIMAL_DIG__ 36"
.LASF75:
	.string	"__WINT_MAX__ 0xffffffffU"
.LASF32:
	.string	"__SIZE_TYPE__ unsigned int"
.LASF235:
	.string	"__FLT64_HAS_QUIET_NAN__ 1"
.LASF218:
	.string	"__FLT32_HAS_DENORM__ 1"
.LASF79:
	.string	"__SCHAR_WIDTH__ 8"
.LASF160:
	.string	"__DBL_MANT_DIG__ 53"
.LASF56:
	.string	"__UINT_LEAST64_TYPE__ long long unsigned int"
.LASF169:
	.string	"__DBL_MIN__ ((double)2.22507385850720138309023271733240406e-308L)"
.LASF65:
	.string	"__INTPTR_TYPE__ int"
.LASF113:
	.string	"__INT_LEAST64_MAX__ 0x7fffffffffffffffLL"
.LASF80:
	.string	"__SHRT_WIDTH__ 16"
.LASF194:
	.string	"__FLT16_MIN_10_EXP__ (-4)"
.LASF45:
	.string	"__UINT8_TYPE__ unsigned char"
.LASF40:
	.string	"__SIG_ATOMIC_TYPE__ int"
.LASF214:
	.string	"__FLT32_NORM_MAX__ 3.40282346638528859811704183484516925e+38F32"
.LASF162:
	.string	"__DBL_MIN_EXP__ (-1021)"
.LASF299:
	.string	"__PRAGMA_REDEFINE_EXTNAME 1"
.LASF109:
	.string	"__INT_LEAST16_WIDTH__ 16"
.LASF183:
	.string	"__LDBL_MAX__ 1.18973149535723176508575932662800702e+4932L"
.LASF326:
	.string	"RT_USING_NEWLIB 1"
.LASF189:
	.string	"__LDBL_HAS_INFINITY__ 1"
.LASF157:
	.string	"__FLT_HAS_DENORM__ 1"
.LASF238:
	.string	"__FLT128_MIN_EXP__ (-16381)"
.LASF133:
	.string	"__UINT_FAST16_MAX__ 0xffffffffU"
.LASF136:
	.string	"__INTPTR_MAX__ 0x7fffffff"
.LASF101:
	.string	"__UINT16_MAX__ 0xffff"
.LASF291:
	.string	"__GCC_ATOMIC_WCHAR_T_LOCK_FREE 2"
.LASF41:
	.string	"__INT8_TYPE__ signed char"
.LASF29:
	.string	"__BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__"
.LASF82:
	.string	"__LONG_WIDTH__ 32"
.LASF168:
	.string	"__DBL_NORM_MAX__ ((double)1.79769313486231570814527423731704357e+308L)"
.LASF30:
	.string	"__FLOAT_WORD_ORDER__ __ORDER_LITTLE_ENDIAN__"
.LASF118:
	.string	"__UINT_LEAST16_MAX__ 0xffff"
.LASF43:
	.string	"__INT32_TYPE__ long int"
.LASF50:
	.string	"__INT_LEAST16_TYPE__ short int"
.LASF58:
	.string	"__INT_FAST16_TYPE__ int"
.LASF88:
	.string	"__INTMAX_MAX__ 0x7fffffffffffffffLL"
.LASF156:
	.string	"__FLT_DENORM_MIN__ 1.40129846432481707092372958328991613e-45F"
.LASF187:
	.string	"__LDBL_DENORM_MIN__ 6.47517511943802511092443895822764655e-4966L"
.LASF21:
	.string	"__SIZEOF_DOUBLE__ 8"
.LASF315:
	.string	"__riscv_a 2000000"
.LASF319:
	.string	"__ELF__ 1"
.LASF100:
	.string	"__UINT8_MAX__ 0xff"
.LASF78:
	.string	"__SIZE_MAX__ 0xffffffffU"
.LASF298:
	.string	"__GCC_HAVE_DWARF2_CFI_ASM 1"
.LASF210:
	.string	"__FLT32_MAX_EXP__ 128"
.LASF111:
	.string	"__INT32_C(c) c ## L"
.LASF225:
	.string	"__FLT64_MAX_EXP__ 1024"
.LASF137:
	.string	"__INTPTR_WIDTH__ 32"
.LASF87:
	.string	"__SIZE_WIDTH__ 32"
.LASF216:
	.string	"__FLT32_EPSILON__ 1.19209289550781250000000000000000000e-7F32"
.LASF290:
	.string	"__GCC_ATOMIC_CHAR32_T_LOCK_FREE 2"
.LASF37:
	.string	"__UINTMAX_TYPE__ long long unsigned int"
.LASF95:
	.string	"__SIG_ATOMIC_WIDTH__ 32"
.LASF135:
	.string	"__UINT_FAST64_MAX__ 0xffffffffffffffffULL"
.LASF177:
	.string	"__LDBL_MIN_EXP__ (-16381)"
.LASF18:
	.string	"__SIZEOF_LONG_LONG__ 8"
.LASF146:
	.string	"__FLT_DIG__ 6"
.LASF171:
	.string	"__DBL_DENORM_MIN__ ((double)4.94065645841246544176568792868221372e-324L)"
.LASF12:
	.string	"__ATOMIC_RELEASE 3"
.LASF150:
	.string	"__FLT_MAX_10_EXP__ 38"
.LASF284:
	.string	"__NO_INLINE__ 1"
.LASF322:
	.string	"NO_INIT 1"
.LASF76:
	.string	"__WINT_MIN__ 0U"
.LASF22:
	.string	"__SIZEOF_LONG_DOUBLE__ 16"
.LASF105:
	.string	"__INT8_C(c) c"
.LASF215:
	.string	"__FLT32_MIN__ 1.17549435082228750796873653722224568e-38F32"
.LASF6:
	.string	"__GNUC_MINOR__ 2"
.LASF219:
	.string	"__FLT32_HAS_INFINITY__ 1"
.LASF275:
	.string	"__FLT64X_MIN__ 3.36210314311209350626267781732175260e-4932F64x"
.LASF143:
	.string	"__DEC_EVAL_METHOD__ 2"
.LASF72:
	.string	"__LONG_LONG_MAX__ 0x7fffffffffffffffLL"
.LASF5:
	.string	"__GNUC__ 10"
.LASF205:
	.string	"__FLT16_HAS_QUIET_NAN__ 1"
.LASF159:
	.string	"__FLT_HAS_QUIET_NAN__ 1"
.LASF127:
	.string	"__INT_FAST16_WIDTH__ 32"
.LASF206:
	.string	"__FLT32_MANT_DIG__ 24"
.LASF125:
	.string	"__INT_FAST8_WIDTH__ 32"
.LASF99:
	.string	"__INT64_MAX__ 0x7fffffffffffffffLL"
.LASF147:
	.string	"__FLT_MIN_EXP__ (-125)"
.LASF260:
	.string	"__FLT32X_MIN__ 2.22507385850720138309023271733240406e-308F32x"
.LASF312:
	.string	"__riscv_arch_test 1"
.LASF181:
	.string	"__DECIMAL_DIG__ 36"
.LASF310:
	.string	"__riscv_float_abi_soft 1"
.LASF27:
	.string	"__ORDER_BIG_ENDIAN__ 4321"
.LASF38:
	.string	"__CHAR16_TYPE__ short unsigned int"
.LASF178:
	.string	"__LDBL_MIN_10_EXP__ (-4931)"
.LASF297:
	.string	"__GCC_ATOMIC_POINTER_LOCK_FREE 2"
.LASF36:
	.string	"__INTMAX_TYPE__ long long int"
.LASF249:
	.string	"__FLT128_HAS_INFINITY__ 1"
.LASF19:
	.string	"__SIZEOF_SHORT__ 2"
.LASF154:
	.string	"__FLT_MIN__ 1.17549435082228750796873653722224568e-38F"
.LASF234:
	.string	"__FLT64_HAS_INFINITY__ 1"
.LASF295:
	.string	"__GCC_ATOMIC_LLONG_LOCK_FREE 1"
.LASF108:
	.string	"__INT16_C(c) c"
.LASF279:
	.string	"__FLT64X_HAS_INFINITY__ 1"
.LASF149:
	.string	"__FLT_MAX_EXP__ 128"
.LASF331:
	.string	"D:\\rt-thread\\bsp\\gd32\\risc-v\\libraries\\GD32VF103_Firmware_Library\\RISCV\\env_Eclipse\\your_printf.c"
.LASF318:
	.string	"__riscv_zifencei 2000000"
.LASF172:
	.string	"__DBL_HAS_DENORM__ 1"
.LASF277:
	.string	"__FLT64X_DENORM_MIN__ 6.47517511943802511092443895822764655e-4966F64x"
.LASF239:
	.string	"__FLT128_MIN_10_EXP__ (-4931)"
.LASF70:
	.string	"__INT_MAX__ 0x7fffffff"
.LASF248:
	.string	"__FLT128_HAS_DENORM__ 1"
.LASF68:
	.string	"__SCHAR_MAX__ 0x7f"
.LASF7:
	.string	"__GNUC_PATCHLEVEL__ 0"
.LASF209:
	.string	"__FLT32_MIN_10_EXP__ (-37)"
.LASF316:
	.string	"__riscv_c 2000000"
.LASF166:
	.string	"__DBL_DECIMAL_DIG__ 17"
.LASF161:
	.string	"__DBL_DIG__ 15"
.LASF151:
	.string	"__FLT_DECIMAL_DIG__ 9"
.LASF60:
	.string	"__INT_FAST64_TYPE__ long long int"
.LASF25:
	.string	"__BIGGEST_ALIGNMENT__ 16"
.LASF16:
	.string	"__SIZEOF_INT__ 4"
.LASF116:
	.string	"__UINT_LEAST8_MAX__ 0xff"
.LASF256:
	.string	"__FLT32X_MAX_10_EXP__ 308"
.LASF304:
	.string	"__riscv_compressed 1"
.LASF97:
	.string	"__INT16_MAX__ 0x7fff"
.LASF286:
	.string	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1"
.LASF201:
	.string	"__FLT16_EPSILON__ 9.76562500000000000000000000000000000e-4F16"
.LASF240:
	.string	"__FLT128_MAX_EXP__ 16384"
.LASF323:
	.string	"HAVE_CCONFIG_H 1"
.LASF273:
	.string	"__FLT64X_MAX__ 1.18973149535723176508575932662800702e+4932F64x"
.LASF81:
	.string	"__INT_WIDTH__ 32"
.LASF197:
	.string	"__FLT16_DECIMAL_DIG__ 5"
.LASF145:
	.string	"__FLT_MANT_DIG__ 24"
.LASF92:
	.string	"__INTMAX_WIDTH__ 64"
.LASF285:
	.string	"__CHAR_UNSIGNED__ 1"
.LASF57:
	.string	"__INT_FAST8_TYPE__ int"
.LASF211:
	.string	"__FLT32_MAX_10_EXP__ 38"
.LASF292:
	.string	"__GCC_ATOMIC_SHORT_LOCK_FREE 1"
.LASF102:
	.string	"__UINT32_MAX__ 0xffffffffUL"
.LASF130:
	.string	"__INT_FAST64_MAX__ 0x7fffffffffffffffLL"
.LASF251:
	.string	"__FLT32X_MANT_DIG__ 53"
.LASF106:
	.string	"__INT_LEAST8_WIDTH__ 8"
.LASF54:
	.string	"__UINT_LEAST16_TYPE__ short unsigned int"
.LASF164:
	.string	"__DBL_MAX_EXP__ 1024"
.LASF138:
	.string	"__UINTPTR_MAX__ 0xffffffffU"
.LASF191:
	.string	"__FLT16_MANT_DIG__ 11"
.LASF140:
	.string	"__GCC_IEC_559_COMPLEX 0"
.LASF258:
	.string	"__FLT32X_MAX__ 1.79769313486231570814527423731704357e+308F32x"
.LASF11:
	.string	"__ATOMIC_ACQUIRE 2"
.LASF212:
	.string	"__FLT32_DECIMAL_DIG__ 9"
.LASF320:
	.string	"USE_PLIC 1"
.LASF90:
	.string	"__UINTMAX_MAX__ 0xffffffffffffffffULL"
.LASF293:
	.string	"__GCC_ATOMIC_INT_LOCK_FREE 2"
.LASF152:
	.string	"__FLT_MAX__ 3.40282346638528859811704183484516925e+38F"
.LASF300:
	.string	"__SIZEOF_WCHAR_T__ 4"
.LASF257:
	.string	"__FLT32X_DECIMAL_DIG__ 17"
.LASF288:
	.string	"__GCC_ATOMIC_CHAR_LOCK_FREE 1"
.LASF63:
	.string	"__UINT_FAST32_TYPE__ unsigned int"
.LASF307:
	.string	"__riscv_div 1"
.LASF224:
	.string	"__FLT64_MIN_10_EXP__ (-307)"
.LASF324:
	.string	"GD32VF103V_EVAL 1"
.LASF144:
	.string	"__FLT_RADIX__ 2"
.LASF47:
	.string	"__UINT32_TYPE__ long unsigned int"
.LASF121:
	.string	"__UINT32_C(c) c ## UL"
.LASF203:
	.string	"__FLT16_HAS_DENORM__ 1"
.LASF120:
	.string	"__UINT_LEAST32_MAX__ 0xffffffffUL"
.LASF107:
	.string	"__INT_LEAST16_MAX__ 0x7fff"
.LASF250:
	.string	"__FLT128_HAS_QUIET_NAN__ 1"
.LASF85:
	.string	"__WINT_WIDTH__ 32"
.LASF242:
	.string	"__FLT128_DECIMAL_DIG__ 36"
.LASF74:
	.string	"__WCHAR_MIN__ (-__WCHAR_MAX__ - 1)"
.LASF289:
	.string	"__GCC_ATOMIC_CHAR16_T_LOCK_FREE 1"
.LASF311:
	.string	"__riscv_cmodel_medany 1"
.LASF179:
	.string	"__LDBL_MAX_EXP__ 16384"
.LASF252:
	.string	"__FLT32X_DIG__ 15"
.LASF263:
	.string	"__FLT32X_HAS_DENORM__ 1"
.LASF89:
	.string	"__INTMAX_C(c) c ## LL"
.LASF153:
	.string	"__FLT_NORM_MAX__ 3.40282346638528859811704183484516925e+38F"
.LASF77:
	.string	"__PTRDIFF_MAX__ 0x7fffffff"
.LASF317:
	.string	"__riscv_zicsr 2000000"
.LASF141:
	.string	"__FLT_EVAL_METHOD__ 0"
.LASF49:
	.string	"__INT_LEAST8_TYPE__ signed char"
.LASF119:
	.string	"__UINT16_C(c) c"
.LASF69:
	.string	"__SHRT_MAX__ 0x7fff"
.LASF20:
	.string	"__SIZEOF_FLOAT__ 4"
.LASF165:
	.string	"__DBL_MAX_10_EXP__ 308"
.LASF247:
	.string	"__FLT128_DENORM_MIN__ 6.47517511943802511092443895822764655e-4966F128"
.LASF0:
	.string	"__STDC__ 1"
.LASF28:
	.string	"__ORDER_PDP_ENDIAN__ 3412"
.LASF229:
	.string	"__FLT64_NORM_MAX__ 1.79769313486231570814527423731704357e+308F64"
.LASF26:
	.string	"__ORDER_LITTLE_ENDIAN__ 1234"
.LASF35:
	.string	"__WINT_TYPE__ unsigned int"
.LASF333:
	.string	"__wrap_printf"
.LASF52:
	.string	"__INT_LEAST64_TYPE__ long long int"
.LASF9:
	.string	"__ATOMIC_RELAXED 0"
.LASF328:
	.string	"_POSIX_C_SOURCE 1"
.LASF196:
	.string	"__FLT16_MAX_10_EXP__ 4"
.LASF193:
	.string	"__FLT16_MIN_EXP__ (-13)"
.LASF110:
	.string	"__INT_LEAST32_MAX__ 0x7fffffffL"
.LASF139:
	.string	"__GCC_IEC_559 0"
.LASF51:
	.string	"__INT_LEAST32_TYPE__ long int"
.LASF262:
	.string	"__FLT32X_DENORM_MIN__ 4.94065645841246544176568792868221372e-324F32x"
.LASF266:
	.string	"__FLT64X_MANT_DIG__ 113"
.LASF306:
	.string	"__riscv_mul 1"
.LASF200:
	.string	"__FLT16_MIN__ 6.10351562500000000000000000000000000e-5F16"
.LASF321:
	.string	"USE_M_TIME 1"
.LASF280:
	.string	"__FLT64X_HAS_QUIET_NAN__ 1"
.LASF190:
	.string	"__LDBL_HAS_QUIET_NAN__ 1"
.LASF93:
	.string	"__SIG_ATOMIC_MAX__ 0x7fffffff"
.LASF199:
	.string	"__FLT16_NORM_MAX__ 6.55040000000000000000000000000000000e+4F16"
.LASF329:
	.string	"char"
.LASF264:
	.string	"__FLT32X_HAS_INFINITY__ 1"
.LASF236:
	.string	"__FLT128_MANT_DIG__ 113"
.LASF66:
	.string	"__UINTPTR_TYPE__ unsigned int"
.LASF184:
	.string	"__LDBL_NORM_MAX__ 1.18973149535723176508575932662800702e+4932L"
.LASF123:
	.string	"__UINT64_C(c) c ## ULL"
.LASF221:
	.string	"__FLT64_MANT_DIG__ 53"
.LASF158:
	.string	"__FLT_HAS_INFINITY__ 1"
.LASF325:
	.string	"__RTTHREAD__ 1"
.LASF227:
	.string	"__FLT64_DECIMAL_DIG__ 17"
.LASF327:
	.string	"RT_USING_LIBC 1"
.LASF83:
	.string	"__LONG_LONG_WIDTH__ 64"
.LASF232:
	.string	"__FLT64_DENORM_MIN__ 4.94065645841246544176568792868221372e-324F64"
.LASF42:
	.string	"__INT16_TYPE__ short int"
.LASF17:
	.string	"__SIZEOF_LONG__ 4"
.LASF134:
	.string	"__UINT_FAST32_MAX__ 0xffffffffU"
.LASF2:
	.string	"__STDC_UTF_16__ 1"
.LASF186:
	.string	"__LDBL_EPSILON__ 1.92592994438723585305597794258492732e-34L"
.LASF61:
	.string	"__UINT_FAST8_TYPE__ unsigned int"
.LASF33:
	.string	"__PTRDIFF_TYPE__ int"
.LASF188:
	.string	"__LDBL_HAS_DENORM__ 1"
.LASF265:
	.string	"__FLT32X_HAS_QUIET_NAN__ 1"
.LASF276:
	.string	"__FLT64X_EPSILON__ 1.92592994438723585305597794258492732e-34F64x"
.LASF128:
	.string	"__INT_FAST32_MAX__ 0x7fffffff"
.LASF281:
	.string	"__REGISTER_PREFIX__ "
.LASF14:
	.string	"__ATOMIC_CONSUME 1"
.LASF182:
	.string	"__LDBL_DECIMAL_DIG__ 36"
.LASF3:
	.string	"__STDC_UTF_32__ 1"
.LASF46:
	.string	"__UINT16_TYPE__ short unsigned int"
.LASF271:
	.string	"__FLT64X_MAX_10_EXP__ 4932"
.LASF176:
	.string	"__LDBL_DIG__ 33"
.LASF268:
	.string	"__FLT64X_MIN_EXP__ (-16381)"
.LASF220:
	.string	"__FLT32_HAS_QUIET_NAN__ 1"
.LASF195:
	.string	"__FLT16_MAX_EXP__ 16"
.LASF302:
	.string	"__SIZEOF_PTRDIFF_T__ 4"
.LASF243:
	.string	"__FLT128_MAX__ 1.18973149535723176508575932662800702e+4932F128"
.LASF67:
	.string	"__GXX_ABI_VERSION 1014"
.LASF126:
	.string	"__INT_FAST16_MAX__ 0x7fffffff"
.LASF94:
	.string	"__SIG_ATOMIC_MIN__ (-__SIG_ATOMIC_MAX__ - 1)"
.LASF131:
	.string	"__INT_FAST64_WIDTH__ 64"
.LASF245:
	.string	"__FLT128_MIN__ 3.36210314311209350626267781732175260e-4932F128"
.LASF59:
	.string	"__INT_FAST32_TYPE__ int"
.LASF217:
	.string	"__FLT32_DENORM_MIN__ 1.40129846432481707092372958328991613e-45F32"
.LASF62:
	.string	"__UINT_FAST16_TYPE__ unsigned int"
.LASF222:
	.string	"__FLT64_DIG__ 15"
.LASF303:
	.string	"__riscv 1"
.LASF241:
	.string	"__FLT128_MAX_10_EXP__ 4932"
.LASF294:
	.string	"__GCC_ATOMIC_LONG_LOCK_FREE 2"
.LASF167:
	.string	"__DBL_MAX__ ((double)1.79769313486231570814527423731704357e+308L)"
.LASF267:
	.string	"__FLT64X_DIG__ 33"
.LASF96:
	.string	"__INT8_MAX__ 0x7f"
.LASF174:
	.string	"__DBL_HAS_QUIET_NAN__ 1"
.LASF148:
	.string	"__FLT_MIN_10_EXP__ (-37)"
.LASF296:
	.string	"__GCC_ATOMIC_TEST_AND_SET_TRUEVAL 1"
.LASF198:
	.string	"__FLT16_MAX__ 6.55040000000000000000000000000000000e+4F16"
.LASF13:
	.string	"__ATOMIC_ACQ_REL 4"
.LASF34:
	.string	"__WCHAR_TYPE__ int"
.LASF244:
	.string	"__FLT128_NORM_MAX__ 1.18973149535723176508575932662800702e+4932F128"
.LASF309:
	.string	"__riscv_xlen 32"
.LASF15:
	.string	"__FINITE_MATH_ONLY__ 0"
.LASF71:
	.string	"__LONG_MAX__ 0x7fffffffL"
.LASF103:
	.string	"__UINT64_MAX__ 0xffffffffffffffffULL"
.LASF86:
	.string	"__PTRDIFF_WIDTH__ 32"
.LASF282:
	.string	"__USER_LABEL_PREFIX__ "
.LASF270:
	.string	"__FLT64X_MAX_EXP__ 16384"
.LASF208:
	.string	"__FLT32_MIN_EXP__ (-125)"
.LASF213:
	.string	"__FLT32_MAX__ 3.40282346638528859811704183484516925e+38F32"
.LASF64:
	.string	"__UINT_FAST64_TYPE__ long long unsigned int"
.LASF117:
	.string	"__UINT8_C(c) c"
.LASF237:
	.string	"__FLT128_DIG__ 33"
.LASF53:
	.string	"__UINT_LEAST8_TYPE__ unsigned char"
.LASF115:
	.string	"__INT_LEAST64_WIDTH__ 64"
.LASF98:
	.string	"__INT32_MAX__ 0x7fffffffL"
.LASF253:
	.string	"__FLT32X_MIN_EXP__ (-1021)"
.LASF104:
	.string	"__INT_LEAST8_MAX__ 0x7f"
.LASF287:
	.string	"__GCC_ATOMIC_BOOL_LOCK_FREE 1"
.LASF122:
	.string	"__UINT_LEAST64_MAX__ 0xffffffffffffffffULL"
.LASF163:
	.string	"__DBL_MIN_10_EXP__ (-307)"
.LASF8:
	.string	"__VERSION__ \"10.2.0\""
.LASF283:
	.string	"__GNUC_STDC_INLINE__ 1"
.LASF330:
	.string	"GNU C17 10.2.0 -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit= 8 -march=rv32imac -g3 -O0"
.LASF223:
	.string	"__FLT64_MIN_EXP__ (-1021)"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 10.2.0"
