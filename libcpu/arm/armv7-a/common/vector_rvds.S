/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

	AREA	VECTOR, CODE, READONLY, ALIGN=5
	PRESERVE8

	EXPORT system_vectors
system_vectors
	ldr pc, _vector_reset
	ldr pc, _vector_undef
	ldr pc, _vector_swi
	ldr pc, _vector_pabt
	ldr pc, _vector_dabt
	ldr pc, _vector_resv
	ldr pc, _vector_irq
	ldr pc, _vector_fiq

	IMPORT _reset
	IMPORT vector_undef
	IMPORT vector_swi
	IMPORT vector_pabt
	IMPORT vector_dabt
	IMPORT vector_resv
	IMPORT vector_irq
	IMPORT vector_fiq

_vector_reset
	dcd _reset
_vector_undef
	dcd vector_undef
_vector_swi
	dcd vector_swi
_vector_pabt
	dcd vector_pabt
_vector_dabt
	dcd vector_dabt
_vector_resv
	dcd vector_resv
_vector_irq
	dcd vector_irq
_vector_fiq
	dcd vector_fiq

	END