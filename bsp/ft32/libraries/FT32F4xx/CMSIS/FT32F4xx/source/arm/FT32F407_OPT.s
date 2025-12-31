;/*******************************************************************************/
;/* Copyright (c) 2014 Arm Limited (or its affiliates). All                     */
;/* rights reserved.                                                            */
;/*                                                                             */
;/* SPDX-License-Identifier: BSD-3-Clause                                       */
;/*                                                                             */
;/* Redistribution and use in source and binary forms, with or without          */
;/* modification, are permitted provided that the following conditions are met: */
;/*   1.Redistributions of source code must retain the above copyright          */
;/*     notice, this list of conditions and the following disclaimer.           */
;/*   2.Redistributions in binary form must reproduce the above copyright       */
;/*     notice, this list of conditions and the following disclaimer in the     */
;/*     documentation and/or other materials provided with the distribution.    */
;/*   3.Neither the name of Arm nor the names of its contributors may be used   */
;/*     to endorse or promote products derived from this software without       */
;/*     specific prior written permission.                                      */
;/*                                                                             */
;/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" */
;/* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   */
;/* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  */
;/* ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE     */
;/* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         */
;/* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        */
;/* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    */
;/* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     */
;/* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     */
;/* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  */
;/* POSSIBILITY OF SUCH DAMAGE.                                                 */
;/*******************************************************************************/
;/* FT32F407_OPT.s: FT32F407      Flash Option Bytes                         	 */
;/*******************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                            */
;/*******************************************************************************/


;// <e> Flash Option Bytes
FLASH_OPT       EQU     1

;// <h> Flash Read Protection
;//     <i> Read protection is used to protect the software code stored in Flash memory
;//   <o0.8..15> Read Protection Level
;//     <i> Level 0: No Protection 
;//     <i> Level 1: Read Protection of Memories (debug features limited)
;//     <i> Level 2: Chip Protection (debug and boot in RAM features disabled)
;//          <0xAA=> Level 0 (No Protection) 
;//          <0x00=> Level 1 (Read Protection of Memories)
;//          <0xCC=> Level 2 (Chip Protection)
;// </h>

;// <h> User Configuration
;//   <o0.16> BOR_EN 
;//   <o0.17..18> BORF_LEV
;//          <0=> BOR falling edge voltage 1: threshold value is approximately 2.0 V
;//          <1=> BOR falling edge voltage 2: threshold value is approximately 2.2 V
;//          <2=> BOR falling edge voltage 3: threshold value is approximately 2.5 V
;//          <3=> BOR falling edge voltage 4: threshold value is approximately 2.8 V
;//   <o0.19..20> BORR_LEV
;//          <0=> BOR rising edge voltage 1: threshold value is approximately 2.1 V
;//          <1=> BOR rising edge voltage 2: threshold value is approximately 2.3 V
;//          <2=> BOR rising edge voltage 3: threshold value is approximately 2.6 V
;//          <3=> BOR rising edge voltage 4: threshold value is approximately 2.9 V
;//   <o0.5> WDG_SW     
;//          <0=> HW Watchdog
;//          <1=> SW Watchdog
;//   <o0.6> nRST_STOP
;//     <i> Generate Reset when entering STOP Mode
;//          <0=> Enabled
;//          <1=> Disabled
;//   <o0.7> nRST_STDBY
;//     <i> Generate Reset when entering Standby Mode
;//          <0=> Enabled
;//          <1=> Disabled
;// </h>

;// <h> Flash Write Protection
;//     <i> Flash write-protection setting, with 16KB as the unit, low effective
;//   <h> nWRP Page 0 to 1023
;//       <i> Not write protect Page 0 to 1023
;//     <o1.0> Page 0 to 31
;//     <o1.1> Page 32 to 63
;//     <o1.2> Page 64 to 95
;//     <o1.3> Page 96 to 127
;//     <o1.4> Page 128 to 159
;//     <o1.5> Page 160 to 191
;//     <o1.6> Page 192 to 223
;//     <o1.7> Page 224 to 255
;//     <o1.8> Page 256 to 287
;//     <o1.9> Page 288 to 319
;//     <o1.10> Page 320 to 351
;//     <o1.11> Page 352 to 383
;//     <o1.12> Page 384 to 415
;//     <o1.13> Page 416 to 447
;//     <o1.14> Page 448 to 479
;//     <o1.15> Page 480 to 511
;//     <o1.16> Page 512 to 543
;//     <o1.17> Page 544 to 575
;//     <o1.18> Page 576 to 607
;//     <o1.19> Page 608 to 639
;//     <o1.20> Page 640 to 671
;//     <o1.21> Page 672 to 703
;//     <o1.22> Page 704 to 735
;//     <o1.23> Page 736 to 767
;//     <o1.24> Page 768 to 799
;//     <o1.25> Page 800 to 831
;//     <o1.26> Page 832 to 863
;//     <o1.27> Page 864 to 895
;//     <o1.28> Page 896 to 927
;//     <o1.29> Page 928 to 959
;//     <o1.30> Page 960 to 991
;//     <o1.31> Page 992 to 1023
;//   </h>
;// </h>


FLASH_OPBC    EQU     0x001EAAE0
FLASH_TEMP	  EQU     ~FLASH_OPBC
FLASH_WRPR    EQU     0xFFFFFFFF
;// </e>


                IF      FLASH_OPT <> 0
                AREA    |.ARM.__AT_0x1FFF0800|, CODE, READONLY
                DCD     FLASH_OPBC
                DCD     FLASH_TEMP
                DCD     FLASH_WRPR					
                ENDIF

                END
