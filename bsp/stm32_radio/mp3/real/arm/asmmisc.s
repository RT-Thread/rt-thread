;/* ***** BEGIN LICENSE BLOCK ***** 
; * Version: RCSL 1.0/RPSL 1.0 
; *  
; * Portions Copyright (c) 1995-2002 RealNetworks, Inc. All Rights Reserved. 
; *      
; * The contents of this file, and the files included with this file, are 
; * subject to the current version of the RealNetworks Public Source License 
; * Version 1.0 (the "RPSL") available at 
; * http://www.helixcommunity.org/content/rpsl unless you have licensed 
; * the file under the RealNetworks Community Source License Version 1.0 
; * (the "RCSL") available at http://www.helixcommunity.org/content/rcsl, 
; * in which case the RCSL will apply. You may also obtain the license terms 
; * directly from RealNetworks.  You may not use this file except in 
; * compliance with the RPSL or, if you have a valid RCSL with RealNetworks 
; * applicable to this file, the RCSL.  Please see the applicable RPSL or 
; * RCSL for the rights, obligations and limitations governing use of the 
; * contents of the file.  
; *  
; * This file is part of the Helix DNA Technology. RealNetworks is the 
; * developer of the Original Code and owns the copyrights in the portions 
; * it created. 
; *  
; * This file, and the files included with this file, is distributed and made 
; * available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER 
; * EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS ALL SUCH WARRANTIES, 
; * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS 
; * FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. 
; * 
; * Technology Compatibility Kit Test Suite(s) Location: 
; *    http://www.helixcommunity.org/content/tck 
; * 
; * Contributor(s): 
; *  
; * ***** END LICENSE BLOCK ***** */ 


	AREA	|.text|, CODE, READONLY
	THUMB
	REQUIRE8
	PRESERVE8
; int xmp3_MULSHIFT32(int x, int y)
	EXPORT xmp3_MULSHIFT32
	EXPORT xmp3_FASTABS

;.cpu cortex-m3
;.fpu softvfp   
;.syntax unified 
;.thumb
;.text

    ; .global xmp3_MULSHIFT32
    ; .thumb_func
xmp3_MULSHIFT32 PROC
	smull	r2, r0, r1, r0
;	mov		pc, lr	  // KJ changed to BX for Cortex
	BX lr
	ENDP

	;.global	xmp3_FASTABS
    ;.thumb_func
xmp3_FASTABS PROC
	mov r1, r0
	mov r0, #0x0
	eor r0, r1, r1, asr # 31
	sub r0, r0, r1, asr # 31
	bx lr
	ENDP
	
	END