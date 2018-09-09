/*
 * File      : vector_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-09     liruncong    the first version
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