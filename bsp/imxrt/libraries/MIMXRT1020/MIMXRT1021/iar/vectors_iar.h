/*******************************************************************************
*
* Copyright 2013 - 2016, Freescale Semiconductor, Inc.
* Copyright 2016-2019 NXP
*
* This software is owned or controlled by NXP and may only be used
* strictly in accordance with the applicable license terms.  By expressly
* accepting such terms or by downloading, installing, activating and/or
* otherwise using the software, you are agreeing that you have read, and
* that you agree to comply with and are bound by, such license terms.  If
* you do not agree to be bound by the applicable license terms, then you
* may not retain, install, activate or otherwise use the software.
*
*
*******************************************************************************/

#ifndef _VECTORS_H_
#define _VECTORS_H_

#include "safety_config.h"  /* for device definition */

/*******************************************************************************
* API
******************************************************************************/

void default_isr(void); /* function prototype for default_isr in vectors.c */
extern void start(void);
void NMI_isr(void); /* included in vector.c */
void hard_fault_handler_c(unsigned int * hardfault_args);
typedef void pointer(void); /* Interrupt Vector Table Function Pointers */
extern void __startup(void);
extern unsigned long __BOOT_STACK_ADDRESS[];


/*******************************************************************************
* Definitions
******************************************************************************/
//          Address          Vector IRQ      Source module     Source description
#define VECTOR_000       (pointer*)__BOOT_STACK_ADDRESS    // Initial SP
#define VECTOR_001       start                             // Initial PC
#ifndef VECTOR_002
  #define VECTOR_002      NMI_isr        // 2 - ARM core   Non-maskable Interrupt (NMI)
#endif
#ifndef VECTOR_003
  #define VECTOR_003      default_isr    // 3 - ARM core   Hard Fault Interrupt
#endif
#ifndef VECTOR_004
  #define VECTOR_004      default_isr    // 4 - ARM core   Memory Management Interrupt
#endif
#ifndef VECTOR_005
  #define VECTOR_005      default_isr    // 5 - ARM core   Bus Fault Interrupt
#endif
#ifndef VECTOR_006
  #define VECTOR_006      default_isr    // 6 - ARM core   Usage Fault Interrupt
#endif
#ifndef VECTOR_007
  #define VECTOR_007      default_isr    // 7 - ARM core
#endif
#ifndef VECTOR_008
  #define VECTOR_008      default_isr    // 8 - ARM core
#endif
#ifndef VECTOR_009
  #define VECTOR_009      default_isr    // 9 - ARM core
#endif
#ifndef VECTOR_010
  #define VECTOR_010      default_isr    // 10 - ARM core
#endif
#ifndef VECTOR_011
  #define VECTOR_011      default_isr    // 11 - ARM core  SV Call Interrupt
#endif
#ifndef VECTOR_0012
  #define VECTOR_012      default_isr    // 12 - ARM core  Debug Monitor Interrupt
#endif
#ifndef VECTOR_013
  #define VECTOR_013      default_isr    // 13 - ARM core
#endif
#ifndef VECTOR_014
  #define VECTOR_014      default_isr    // 14 - ARM core  Pendable request for system service (PendableSrvReq)
#endif
#ifndef VECTOR_015
  #define VECTOR_015      default_isr    // 15 - ARM core  System Tick Interrupt (SysTick)
#endif
#ifndef VECTOR_016
  #define VECTOR_016      default_isr    // 16 -
#endif
#ifndef VECTOR_017
  #define VECTOR_017      default_isr    // 17 -
#endif
#ifndef VECTOR_018
  #define VECTOR_018      default_isr    // 18 -
#endif
#ifndef VECTOR_019
  #define VECTOR_019      default_isr    // 19 -
#endif
#ifndef VECTOR_020
  #define VECTOR_020      default_isr    // 20 -
#endif
#ifndef VECTOR_021
  #define VECTOR_021      default_isr    // 21 -
#endif
#ifndef VECTOR_022
  #define VECTOR_022      default_isr    // 22 -
#endif
#ifndef VECTOR_023
  #define VECTOR_023      default_isr    // 23 -
#endif
#ifndef VECTOR_024
  #define VECTOR_024      default_isr    // 24 -
#endif
#ifndef VECTOR_025
  #define VECTOR_025      default_isr    // 25 -
#endif
#ifndef VECTOR_026
  #define VECTOR_026      default_isr    // 26 -
#endif
#ifndef VECTOR_027
  #define VECTOR_027      default_isr    // 27 -
#endif
#ifndef VECTOR_028
  #define VECTOR_028      default_isr    // 28 -
#endif
#ifndef VECTOR_029
  #define VECTOR_029      default_isr    // 29 -
#endif
#ifndef VECTOR_030
  #define VECTOR_030      default_isr    // 30 -
#endif
#ifndef VECTOR_031
  #define VECTOR_031      default_isr    // 31 -
#endif
#ifndef VECTOR_032
  #define VECTOR_032      default_isr    // 32 -
#endif
#ifndef VECTOR_033
  #define VECTOR_033      default_isr    // 33 -
#endif
#ifndef VECTOR_034
  #define VECTOR_034      default_isr    // 34 -
#endif
#ifndef VECTOR_035
  #define VECTOR_035      default_isr    // 35 -
#endif
#ifndef VECTOR_036
  #define VECTOR_036      default_isr    // 36 -
#endif
#ifndef VECTOR_037
  #define VECTOR_037      default_isr    // 37 -
#endif
#ifndef VECTOR_038
  #define VECTOR_038      default_isr    // 38 -
#endif
#ifndef VECTOR_039
  #define VECTOR_039      default_isr    // 39 -
#endif
#ifndef VECTOR_040
  #define VECTOR_040      default_isr    // 40 -
#endif
#ifndef VECTOR_041
  #define VECTOR_041      default_isr    // 41 -
#endif
#ifndef VECTOR_042
  #define VECTOR_042      default_isr    // 42 -
#endif
#ifndef VECTOR_043
  #define VECTOR_043      default_isr    // 43 -
#endif
#ifndef VECTOR_044
  #define VECTOR_044      default_isr    // 44 -
#endif
#ifndef VECTOR_045
  #define VECTOR_045      default_isr    // 45 -
#endif
#ifndef VECTOR_046
  #define VECTOR_046      default_isr    // 46 -
#endif
#ifndef VECTOR_047
  #define VECTOR_047      default_isr    // 47 -
#endif
#ifndef VECTOR_048
  #define VECTOR_048      default_isr    // 48 -
#endif
#ifndef VECTOR_049
  #define VECTOR_049      default_isr    // 49 -
#endif
#ifndef VECTOR_050
  #define VECTOR_050      default_isr    // 50 -
#endif
#ifndef VECTOR_051
  #define VECTOR_051      default_isr    // 51 -
#endif
#ifndef VECTOR_052
  #define VECTOR_052      default_isr    // 52 -
#endif
#ifndef VECTOR_053
  #define VECTOR_053      default_isr    // 53 -
#endif
#ifndef VECTOR_054
  #define VECTOR_054      default_isr    // 54 -
#endif
#ifndef VECTOR_055
  #define VECTOR_055      default_isr    // 55 -
#endif
#ifndef VECTOR_056
  #define VECTOR_056      default_isr    // 56 -
#endif
#ifndef VECTOR_057
  #define VECTOR_057      default_isr    // 57 -
#endif
#ifndef VECTOR_058
  #define VECTOR_058      default_isr    // 58 -
#endif
#ifndef VECTOR_059
  #define VECTOR_059      default_isr    // 59 -
#endif
#ifndef VECTOR_060
  #define VECTOR_060      default_isr    // 60 -
#endif
#ifndef VECTOR_061
  #define VECTOR_061      default_isr    // 61 -
#endif
#ifndef VECTOR_062
  #define VECTOR_062      default_isr    // 62 -
#endif
#ifndef VECTOR_063
  #define VECTOR_063      default_isr    // 63 -
#endif
#ifndef VECTOR_064
  #define VECTOR_064      default_isr    // 64 -
#endif
#ifndef VECTOR_065
  #define VECTOR_065      default_isr    // 65 -
#endif
#ifndef VECTOR_066
  #define VECTOR_066      default_isr    // 66 -
#endif
#ifndef VECTOR_067
  #define VECTOR_067      default_isr    // 67 -
#endif
#ifndef VECTOR_068
  #define VECTOR_068      default_isr    // 68 -
#endif
#ifndef VECTOR_069
  #define VECTOR_069      default_isr    // 69 -
#endif
#ifndef VECTOR_070
  #define VECTOR_070      default_isr    // 70 -
#endif
#ifndef VECTOR_071
  #define VECTOR_071      default_isr    // 71 -
#endif
#ifndef VECTOR_072
  #define VECTOR_072      default_isr    // 72 -
#endif
#ifndef VECTOR_073
  #define VECTOR_073      default_isr    // 73 -
#endif
#ifndef VECTOR_074
  #define VECTOR_074      default_isr    // 74 -
#endif
#ifndef VECTOR_075
  #define VECTOR_075      default_isr    // 75 -
#endif
#ifndef VECTOR_076
  #define VECTOR_076      default_isr    // 76 -
#endif
#ifndef VECTOR_077
  #define VECTOR_077      default_isr    // 77 -
#endif
#ifndef VECTOR_078
  #define VECTOR_078      default_isr    // 78 -
#endif
#ifndef VECTOR_079
  #define VECTOR_079      default_isr    // 79 -
#endif
#ifndef VECTOR_080
  #define VECTOR_080      default_isr    // 80 -
#endif
#ifndef VECTOR_081
  #define VECTOR_081      default_isr    // 81 -
#endif
#ifndef VECTOR_082
  #define VECTOR_082      default_isr    // 82 -
#endif
#ifndef VECTOR_083
  #define VECTOR_083      default_isr    // 83 -
#endif
#ifndef VECTOR_084
  #define VECTOR_084      default_isr    // 84 -
#endif
#ifndef VECTOR_085
  #define VECTOR_085      default_isr    // 85 -
#endif
#ifndef VECTOR_086
  #define VECTOR_086      default_isr    // 86 -
#endif
#ifndef VECTOR_087
  #define VECTOR_087      default_isr    // 87 -
#endif
#ifndef VECTOR_088
  #define VECTOR_088      default_isr    // 88 -
#endif
#ifndef VECTOR_089
  #define VECTOR_089      default_isr    // 89 -
#endif
#ifndef VECTOR_090
  #define VECTOR_090      default_isr    // 90 -
#endif
#ifndef VECTOR_091
  #define VECTOR_091      default_isr    // 91 -
#endif
#ifndef VECTOR_092
  #define VECTOR_092      default_isr    // 92 -
#endif
#ifndef VECTOR_093
  #define VECTOR_093      default_isr    // 93 -
#endif
#ifndef VECTOR_094
  #define VECTOR_094      default_isr    // 94 -
#endif
#ifndef VECTOR_095
  #define VECTOR_095      default_isr    // 95 -
#endif
#ifndef VECTOR_096
  #define VECTOR_096      default_isr    // 96 -
#endif
#ifndef VECTOR_097
  #define VECTOR_097      default_isr    // 97 -
#endif
#ifndef VECTOR_098
  #define VECTOR_098      default_isr    // 98 -
#endif
#ifndef VECTOR_099
  #define VECTOR_099      default_isr    // 99 -
#endif
#ifndef VECTOR_100
  #define VECTOR_100      default_isr    // 100 -
#endif
#ifndef VECTOR_101
  #define VECTOR_101      default_isr    // 101 -
#endif
#ifndef VECTOR_102
  #define VECTOR_102      default_isr    // 102 -
#endif
#ifndef VECTOR_103
  #define VECTOR_103      default_isr    // 103 -
#endif
#ifndef VECTOR_104
  #define VECTOR_104      default_isr    // 104 -
#endif
#ifndef VECTOR_105
  #define VECTOR_105      default_isr    // 105 -
#endif
#ifndef VECTOR_106
  #define VECTOR_106      default_isr    // 106 -
#endif
#ifndef VECTOR_107
  #define VECTOR_107      default_isr    // 107 -
#endif
#ifndef VECTOR_108
  #define VECTOR_108      default_isr    // 108 -
#endif
#ifndef VECTOR_109
  #define VECTOR_109      default_isr    // 109 -
#endif
#ifndef VECTOR_110
  #define VECTOR_110      default_isr    // 110 -
#endif
#ifndef VECTOR_111
  #define VECTOR_111      default_isr    // 111 -
#endif
#ifndef VECTOR_112
  #define VECTOR_112      default_isr    // 112 -
#endif
#ifndef VECTOR_113
  #define VECTOR_113      default_isr    // 113 -
#endif
#ifndef VECTOR_114
  #define VECTOR_114      default_isr    // 114 -
#endif
#ifndef VECTOR_115
  #define VECTOR_115      default_isr    // 115 -
#endif
#ifndef VECTOR_116
  #define VECTOR_116      default_isr    // 116 -
#endif
#ifndef VECTOR_117
  #define VECTOR_117      default_isr    // 117 -
#endif
#ifndef VECTOR_118
  #define VECTOR_118      default_isr    // 118 -
#endif
#ifndef VECTOR_119
  #define VECTOR_119      default_isr    // 119 -
#endif
#ifndef VECTOR_120
  #define VECTOR_120      default_isr    // 120 -
#endif
#ifndef VECTOR_121
  #define VECTOR_121      default_isr    // 121 -
#endif
#ifndef VECTOR_122
  #define VECTOR_122      default_isr    // 122 -
#endif
#ifndef VECTOR_123
  #define VECTOR_123      default_isr    // 123 -
#endif
#ifndef VECTOR_124
  #define VECTOR_124      default_isr    // 124 -
#endif
#ifndef VECTOR_125
  #define VECTOR_125      default_isr    // 125 -
#endif
#ifndef VECTOR_126
  #define VECTOR_126      default_isr    // 126 -
#endif
#ifndef VECTOR_127
  #define VECTOR_127      default_isr    // 127 -
#endif
#ifndef VECTOR_128
  #define VECTOR_128      default_isr    // 128 -
#endif
#ifndef VECTOR_129
  #define VECTOR_129      default_isr    // 129 -
#endif
#ifndef VECTOR_130
  #define VECTOR_130      default_isr    // 130 -
#endif
#ifndef VECTOR_131
  #define VECTOR_131      default_isr    // 131 -
#endif
#ifndef VECTOR_132
  #define VECTOR_132      default_isr    // 132 -
#endif
#ifndef VECTOR_133
  #define VECTOR_133      default_isr    // 133 -
#endif
#ifndef VECTOR_134
  #define VECTOR_134      default_isr    // 134 -
#endif
#ifndef VECTOR_135
  #define VECTOR_135      default_isr    // 135 -
#endif
#ifndef VECTOR_136
  #define VECTOR_136      default_isr    // 136 -
#endif
#ifndef VECTOR_137
  #define VECTOR_137      default_isr    // 137 -
#endif
#ifndef VECTOR_138
  #define VECTOR_138      default_isr    // 138 -
#endif
#ifndef VECTOR_139
  #define VECTOR_139      default_isr    // 139 -
#endif
#ifndef VECTOR_140
  #define VECTOR_140      default_isr    // 140 -
#endif
#ifndef VECTOR_141
  #define VECTOR_141      default_isr    // 141 -
#endif
#ifndef VECTOR_142
  #define VECTOR_142      default_isr    // 142 -
#endif
#ifndef VECTOR_143
  #define VECTOR_143      default_isr    // 143 -
#endif
#ifndef VECTOR_144
  #define VECTOR_144      default_isr    // 144 -
#endif
#ifndef VECTOR_145
  #define VECTOR_145      default_isr    // 145 -
#endif
#ifndef VECTOR_146
  #define VECTOR_146      default_isr    // 146 -
#endif
#ifndef VECTOR_147
  #define VECTOR_147      default_isr    // 147 -
#endif
#ifndef VECTOR_148
  #define VECTOR_148      default_isr    // 148 -
#endif
#ifndef VECTOR_149
  #define VECTOR_149      default_isr    // 149 -
#endif
#ifndef VECTOR_150
  #define VECTOR_150      default_isr    // 150 -
#endif
#ifndef VECTOR_151
  #define VECTOR_151      default_isr    // 151 -
#endif
#ifndef VECTOR_152
  #define VECTOR_152      default_isr    // 152 -
#endif
#ifndef VECTOR_153
  #define VECTOR_153      default_isr    // 153 -
#endif
#ifndef VECTOR_154
  #define VECTOR_154      default_isr    // 154 -
#endif
#ifndef VECTOR_155
  #define VECTOR_155      default_isr    // 155 -
#endif
#ifndef VECTOR_156
  #define VECTOR_156      default_isr    // 156 -
#endif
#ifndef VECTOR_157
  #define VECTOR_157      default_isr    // 157 -
#endif
#ifndef VECTOR_158
  #define VECTOR_158      default_isr    // 158 -
#endif
#ifndef VECTOR_159
  #define VECTOR_159      default_isr    // 159 -
#endif
#ifndef VECTOR_160
  #define VECTOR_160      default_isr    // 160 -
#endif
#ifndef VECTOR_161
  #define VECTOR_161      default_isr    // 161 -
#endif
#ifndef VECTOR_162
  #define VECTOR_162      default_isr    // 162 -
#endif
#ifndef VECTOR_163
  #define VECTOR_163      default_isr    // 163 -
#endif
#ifndef VECTOR_164
  #define VECTOR_164      default_isr    // 164 -
#endif
#ifndef VECTOR_165
  #define VECTOR_165      default_isr    // 165 -
#endif
#ifndef VECTOR_166
  #define VECTOR_166      default_isr    // 166 -
#endif
#ifndef VECTOR_167
  #define VECTOR_167      default_isr    // 167 -
#endif
#ifndef VECTOR_168
  #define VECTOR_168      default_isr    // 168 -
#endif
#ifndef VECTOR_169
  #define VECTOR_169      default_isr    // 169 -
#endif
#ifndef VECTOR_170
  #define VECTOR_170      default_isr    // 170 -
#endif
#ifndef VECTOR_171
  #define VECTOR_171      default_isr    // 171 -
#endif
#ifndef VECTOR_172
  #define VECTOR_172      default_isr    // 172 -
#endif
#ifndef VECTOR_173
  #define VECTOR_173      default_isr    // 173 -
#endif
#ifndef VECTOR_174
  #define VECTOR_174      default_isr    // 174 -
#endif
#ifndef VECTOR_175
  #define VECTOR_175      default_isr    // 175 -
#endif
#ifndef VECTOR_176
  #define VECTOR_176      default_isr
#endif
#ifndef VECTOR_177
  #define VECTOR_177      default_isr
#endif
#ifndef VECTOR_178
  #define VECTOR_178      default_isr
#endif
#ifndef VECTOR_179
  #define VECTOR_179      default_isr
#endif
#ifndef VECTOR_180
  #define VECTOR_180      default_isr
#endif
#ifndef VECTOR_181
  #define VECTOR_181      default_isr
#endif
#ifndef VECTOR_182
  #define VECTOR_182      default_isr
#endif
#ifndef VECTOR_183
  #define VECTOR_183      default_isr
#endif
#ifndef VECTOR_184
  #define VECTOR_184      default_isr
#endif
#ifndef VECTOR_185
  #define VECTOR_185      default_isr
#endif
#ifndef VECTOR_186
  #define VECTOR_186      default_isr
#endif
#ifndef VECTOR_187
  #define VECTOR_187      default_isr
#endif
#ifndef VECTOR_188
  #define VECTOR_188      default_isr
#endif
#ifndef VECTOR_189
  #define VECTOR_189      default_isr
#endif
#ifndef VECTOR_190
  #define VECTOR_190      default_isr
#endif
#ifndef VECTOR_191
  #define VECTOR_191      default_isr
#endif
#ifndef VECTOR_192
  #define VECTOR_192      default_isr
#endif
#ifndef VECTOR_193
  #define VECTOR_193      default_isr
#endif
#ifndef VECTOR_194
  #define VECTOR_194      default_isr
#endif
#ifndef VECTOR_195
  #define VECTOR_195      default_isr
#endif
#ifndef VECTOR_196
  #define VECTOR_196      default_isr
#endif
#ifndef VECTOR_197
  #define VECTOR_197      default_isr
#endif
#ifndef VECTOR_198
  #define VECTOR_198      default_isr
#endif
#ifndef VECTOR_199
  #define VECTOR_199      default_isr
#endif
#ifndef VECTOR_200
  #define VECTOR_200      default_isr
#endif
#ifndef VECTOR_201
  #define VECTOR_201      default_isr
#endif
#ifndef VECTOR_202
  #define VECTOR_202      default_isr
#endif
#ifndef VECTOR_203
  #define VECTOR_203      default_isr
#endif
#ifndef VECTOR_204
  #define VECTOR_204      default_isr
#endif
#ifndef VECTOR_205
  #define VECTOR_205      default_isr
#endif
#ifndef VECTOR_206
  #define VECTOR_206      default_isr
#endif
#ifndef VECTOR_207
  #define VECTOR_207      default_isr
#endif
#ifndef VECTOR_208
  #define VECTOR_208      default_isr
#endif
#ifndef VECTOR_209
  #define VECTOR_209      default_isr
#endif
#ifndef VECTOR_210
  #define VECTOR_210      default_isr
#endif
#ifndef VECTOR_211
  #define VECTOR_211      default_isr
#endif
#ifndef VECTOR_212
  #define VECTOR_212      default_isr
#endif
#ifndef VECTOR_213
  #define VECTOR_213      default_isr
#endif
#ifndef VECTOR_214
  #define VECTOR_214      default_isr
#endif
#ifndef VECTOR_215
  #define VECTOR_215      default_isr
#endif
#ifndef VECTOR_216
  #define VECTOR_216      default_isr
#endif
#ifndef VECTOR_217
  #define VECTOR_217      default_isr
#endif
#ifndef VECTOR_218
  #define VECTOR_218      default_isr
#endif
#ifndef VECTOR_219
  #define VECTOR_219      default_isr
#endif
#ifndef VECTOR_220
  #define VECTOR_220      default_isr
#endif
#ifndef VECTOR_221
  #define VECTOR_221      default_isr
#endif
#ifndef VECTOR_222
  #define VECTOR_222      default_isr
#endif
#ifndef VECTOR_223
  #define VECTOR_223      default_isr
#endif
#ifndef VECTOR_224
  #define VECTOR_224      default_isr
#endif
#ifndef VECTOR_225
  #define VECTOR_225      default_isr
#endif
#ifndef VECTOR_226
  #define VECTOR_226      default_isr
#endif
#ifndef VECTOR_227
  #define VECTOR_227      default_isr
#endif
#ifndef VECTOR_228
  #define VECTOR_228      default_isr
#endif
#ifndef VECTOR_229
  #define VECTOR_229      default_isr
#endif
#ifndef VECTOR_230
  #define VECTOR_230      default_isr
#endif
#ifndef VECTOR_231
  #define VECTOR_231      default_isr
#endif
#ifndef VECTOR_232
  #define VECTOR_232      default_isr
#endif
#ifndef VECTOR_233
  #define VECTOR_233      default_isr
#endif
#ifndef VECTOR_234
  #define VECTOR_234      default_isr
#endif
#ifndef VECTOR_235
  #define VECTOR_235      default_isr
#endif
#ifndef VECTOR_236
  #define VECTOR_236      default_isr
#endif
#ifndef VECTOR_237
  #define VECTOR_237      default_isr
#endif
#ifndef VECTOR_238
  #define VECTOR_238      default_isr
#endif
#ifndef VECTOR_239
  #define VECTOR_239      default_isr
#endif
#ifndef VECTOR_240
  #define VECTOR_240      default_isr
#endif
#ifndef VECTOR_241
  #define VECTOR_241      default_isr
#endif
#ifndef VECTOR_242
  #define VECTOR_242      default_isr
#endif
#ifndef VECTOR_243
  #define VECTOR_243      default_isr
#endif
#ifndef VECTOR_244
  #define VECTOR_244      default_isr
#endif
#ifndef VECTOR_245
  #define VECTOR_245      default_isr
#endif
#ifndef VECTOR_246
  #define VECTOR_246      default_isr
#endif
#ifndef VECTOR_247
  #define VECTOR_247      default_isr
#endif
#ifndef VECTOR_248
  #define VECTOR_248      default_isr
#endif
#ifndef VECTOR_249
  #define VECTOR_249      default_isr
#endif
#ifndef VECTOR_250
  #define VECTOR_250      default_isr
#endif
#ifndef VECTOR_251
  #define VECTOR_251      default_isr
#endif
#ifndef VECTOR_252
  #define VECTOR_252      default_isr
#endif
#ifndef VECTOR_253
  #define VECTOR_253      default_isr
#endif
#ifndef VECTOR_254
  #define VECTOR_254      default_isr
#endif
#ifndef VECTOR_255
  #define VECTOR_255      default_isr
#endif

#endif /* _VECTORS_H_ */
