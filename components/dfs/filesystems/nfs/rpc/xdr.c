/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
/* @(#)xdr.c	2.1 88/07/29 4.0 RPCSRC */
/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 * 
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 * 
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 * 
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 * 
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 * 
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */
#if !defined(lint) && defined(SCCSIDS)
static char sccsid[] = "@(#)xdr.c 1.35 87/08/12";
#endif

/*
 * xdr.c, Generic XDR routines implementation.
 *
 * Copyright (C) 1986, Sun Microsystems, Inc.
 *
 * These are the "generic" xdr routines used to serialize and de-serialize
 * most common data items.  See xdr.h for more info on the interface to
 * xdr.
 */

#include <stdio.h>
#include <stdlib.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <string.h>

/*
 * constants specific to the xdr "protocol"
 */
#define XDR_FALSE		((long) 0)
#define XDR_TRUE		((long) 1)
#define LASTUNSIGNED	((unsigned int) 0-1)

/*
 * for unit alignment
 */
static char xdr_zero[BYTES_PER_XDR_UNIT] = { 0, 0, 0, 0 };

/*
 * Free a data structure using XDR
 * Not a filter, but a convenient utility nonetheless
 */
void xdr_free(xdrproc_t proc, char* objp)
{
	XDR x;

	x.x_op = XDR_FREE;
	(*proc) (&x, objp);
}

/*
 * XDR nothing
 */
bool_t xdr_void( /* xdrs, addr */ )
	/* XDR *xdrs; */
	/* char* addr; */
{

	return (TRUE);
}

/*
 * XDR integers
 */
bool_t xdr_int(XDR* xdrs, int* ip)
{
	if (sizeof(int) == sizeof(long)) {
		return (xdr_long(xdrs, (long *) ip));
	} else if (sizeof(int) < sizeof(long)) {
	  long l;
	  switch (xdrs->x_op) {
	  case XDR_ENCODE:
		l = (long) *ip;
		return XDR_PUTLONG(xdrs, &l);
	  case XDR_DECODE:
		if (!XDR_GETLONG(xdrs, &l))
		  return FALSE;
		*ip = (int) l;
	  case XDR_FREE:
		return TRUE;
	  }
	  return FALSE;
	} else {
		return (xdr_short(xdrs, (short *) ip));
	}
}

/*
 * XDR unsigned integers
 */
bool_t xdr_u_int(XDR* xdrs, unsigned int* up)
{
	if (sizeof(unsigned int) == sizeof(unsigned long)) {
		return (xdr_u_long(xdrs, (unsigned long *) up));
	} else if (sizeof(unsigned int) < sizeof(unsigned long)) {
	  unsigned long l;
	  switch (xdrs->x_op) {
	  case XDR_ENCODE:
		l = (unsigned long) *up;
		return XDR_PUTLONG(xdrs, (long*)&l);
	  case XDR_DECODE:
		if (!XDR_GETLONG(xdrs, (long*)&l))
		  return FALSE;
		*up = (unsigned int) l;
	  case XDR_FREE:
		return TRUE;
	  }
	  return FALSE;
	} else {
		return (xdr_short(xdrs, (short *) up));
	}
}

/*
 * XDR long integers
 * same as xdr_u_long - open coded to save a proc call!
 */
bool_t xdr_long(XDR* xdrs, long* lp)
{

	if (xdrs->x_op == XDR_ENCODE
		&& (sizeof(int32_t) == sizeof(long)
			|| (int32_t) *lp == *lp))
		return (XDR_PUTLONG(xdrs, lp));

	if (xdrs->x_op == XDR_DECODE)
		return (XDR_GETLONG(xdrs, lp));

	if (xdrs->x_op == XDR_FREE)
		return (TRUE);

	return (FALSE);
}

/*
 * XDR unsigned long integers
 * same as xdr_long - open coded to save a proc call!
 */
bool_t xdr_u_long(XDR* xdrs, unsigned long* ulp)
{

  if (xdrs->x_op == XDR_DECODE) {
	long l;
	if (XDR_GETLONG(xdrs, &l) == FALSE)
	  return FALSE;
	*ulp = (uint32_t) l;
	return TRUE;
  }

  if (xdrs->x_op == XDR_ENCODE) {
	if (sizeof(uint32_t) != sizeof(unsigned long)
		&& (uint32_t) *ulp != *ulp)
	  return FALSE;

		return (XDR_PUTLONG(xdrs, (long *) ulp));
  }

	if (xdrs->x_op == XDR_FREE)
		return (TRUE);

	return (FALSE);
}


/*
 * XDR long long integers
 */
bool_t xdr_longlong_t (XDR * xdrs, long long* llp)
{
  int32_t t1, t2;

  switch (xdrs->x_op)
    {
    case XDR_ENCODE:
      t1 = (int32_t) ((*llp) >> 32);
      t2 = (int32_t) (*llp);
      return (XDR_PUTLONG (xdrs, &t1) && XDR_PUTLONG (xdrs, &t2));

    case XDR_DECODE:
      if (!XDR_GETLONG (xdrs, &t1) || !XDR_GETLONG (xdrs, &t2))
        return FALSE;
      *llp = ((int64_t) t1) << 32;
      *llp |= (uint32_t) t2;
      return TRUE;

    case XDR_FREE:
      return TRUE;
    }
  return FALSE;
}

/*
 * XDR unsigned long long integers
 */
bool_t xdr_u_longlong_t (XDR * xdrs, unsigned long long* ullp)
{
  uint32_t t1, t2;

  switch (xdrs->x_op)
    {
    case XDR_ENCODE:
      t1 = (uint32_t) ((*ullp) >> 32);
      t2 = (uint32_t) (*ullp);
      return (XDR_PUTLONG (xdrs, (int32_t *)&t1) &&
              XDR_PUTLONG (xdrs, (int32_t *)&t2));

    case XDR_DECODE:
      if (!XDR_GETLONG (xdrs, (int32_t *)&t1) ||
          !XDR_GETLONG (xdrs, (int32_t *)&t2))
        return FALSE;
      *ullp = ((uint64_t) t1) << 32;
      *ullp |= t2;
      return TRUE;

    case XDR_FREE:
      return TRUE;
    }
  return FALSE;
}

/*
 * XDR short integers
 */
bool_t xdr_short(XDR* xdrs, short* sp)
{
	long l;

	switch (xdrs->x_op) {

	case XDR_ENCODE:
		l = (long) *sp;
		return (XDR_PUTLONG(xdrs, &l));

	case XDR_DECODE:
		if (!XDR_GETLONG(xdrs, &l)) {
			return (FALSE);
		}
		*sp = (short) l;
		return (TRUE);

	case XDR_FREE:
		return (TRUE);
	}
	return (FALSE);
}

/*
 * XDR unsigned short integers
 */
bool_t xdr_u_short(XDR* xdrs, unsigned short* usp)
{
	unsigned long l;

	switch (xdrs->x_op) {

	case XDR_ENCODE:
		l = (unsigned long) * usp;
		return (XDR_PUTLONG(xdrs, (long*)&l));

	case XDR_DECODE:
		if (!XDR_GETLONG(xdrs, (long*)&l)) {
			return (FALSE);
		}
		*usp = (unsigned short) l;
		return (TRUE);

	case XDR_FREE:
		return (TRUE);
	}
	return (FALSE);
}


/*
 * XDR a char
 */
bool_t xdr_char(XDR* xdrs, char* cp)
{
	int i;

	i = (*cp);
	if (!xdr_int(xdrs, &i)) {
		return (FALSE);
	}
	*cp = i;
	return (TRUE);
}

/*
 * XDR an unsigned char
 */
bool_t xdr_u_char(XDR* xdrs, unsigned char* cp)
{
	unsigned int u;

	u = (*cp);
	if (!xdr_u_int(xdrs, &u)) {
		return (FALSE);
	}
	*cp = u;
	return (TRUE);
}

/*
 * XDR booleans
 */
bool_t xdr_bool(XDR *xdrs, bool_t *bp)
{
	long lb;

	switch (xdrs->x_op) {

	case XDR_ENCODE:
		lb = *bp ? XDR_TRUE : XDR_FALSE;
		return (XDR_PUTLONG(xdrs, &lb));

	case XDR_DECODE:
		if (!XDR_GETLONG(xdrs, &lb)) {
			return (FALSE);
		}
		*bp = (lb == XDR_FALSE) ? FALSE : TRUE;
		return (TRUE);

	case XDR_FREE:
		return (TRUE);
	}
	return (FALSE);
}

/*
 * XDR enumerations
 */
bool_t xdr_enum(XDR *xdrs, enum_t *ep)
{
	/*
	 * enums are treated as ints
	 */
	return (xdr_long(xdrs, (long *) ep));
}

/*
 * XDR opaque data
 * Allows the specification of a fixed size sequence of opaque bytes.
 * cp points to the opaque object and cnt gives the byte length.
 */
bool_t xdr_opaque(XDR *xdrs, char* cp, unsigned int cnt)
{
	register unsigned int rndup;
	static char crud[BYTES_PER_XDR_UNIT];

	/*
	 * if no data we are done
	 */
	if (cnt == 0)
		return (TRUE);

	/*
	 * round byte count to full xdr units
	 */
	rndup = cnt % BYTES_PER_XDR_UNIT;
	if (rndup > 0)
		rndup = BYTES_PER_XDR_UNIT - rndup;

	if (xdrs->x_op == XDR_DECODE) {
		if (!XDR_GETBYTES(xdrs, cp, cnt)) {
			return (FALSE);
		}
		if (rndup == 0)
			return (TRUE);
		return (XDR_GETBYTES(xdrs, crud, rndup));
	}

	if (xdrs->x_op == XDR_ENCODE) {
		if (!XDR_PUTBYTES(xdrs, cp, cnt)) {
			return (FALSE);
		}
		if (rndup == 0)
			return (TRUE);
		return (XDR_PUTBYTES(xdrs, xdr_zero, rndup));
	}

	if (xdrs->x_op == XDR_FREE) {
		return (TRUE);
	}

	return (FALSE);
}

/*
 * XDR counted bytes
 * *cpp is a pointer to the bytes, *sizep is the count.
 * If *cpp is NULL maxsize bytes are allocated
 */
bool_t xdr_bytes(XDR *xdrs, char** cpp, unsigned int *sizep, unsigned int maxsize)
{
	register char *sp = *cpp;	/* sp is the actual string pointer */
	register unsigned int nodesize;

	/*
	 * first deal with the length since xdr bytes are counted
	 */
	if (!xdr_u_int(xdrs, sizep)) {
		return (FALSE);
	}
	nodesize = *sizep;
	if ((nodesize > maxsize) && (xdrs->x_op != XDR_FREE)) {
		return (FALSE);
	}

	/*
	 * now deal with the actual bytes
	 */
	switch (xdrs->x_op) {

	case XDR_DECODE:
		if (nodesize == 0) {
			return (TRUE);
		}
		if (sp == NULL) {
			*cpp = sp = (char *) rt_malloc(nodesize);
		}
		if (sp == NULL) {
			rt_kprintf("xdr_bytes: out of memory\n");
			return (FALSE);
		}
		/* fall into ... */

	case XDR_ENCODE:
		return (xdr_opaque(xdrs, sp, nodesize));

	case XDR_FREE:
		if (sp != NULL) {
			rt_free(sp);
			*cpp = NULL;
		}
		return (TRUE);
	}
	return (FALSE);
}

/*
 * Implemented here due to commonality of the object.
 */
bool_t xdr_netobj(XDR *xdrs, struct netobj *np)
{
	return (xdr_bytes(xdrs, &np->n_bytes, &np->n_len, MAX_NETOBJ_SZ));
}

/*
 * XDR a descriminated union
 * Support routine for discriminated unions.
 * You create an array of xdrdiscrim structures, terminated with
 * an entry with a null procedure pointer.  The routine gets
 * the discriminant value and then searches the array of xdrdiscrims
 * looking for that value.  It calls the procedure given in the xdrdiscrim
 * to handle the discriminant.  If there is no specific routine a default
 * routine may be called.
 * If there is no specific or default routine an error is returned.
 */
bool_t xdr_union(XDR* xdrs, enum_t* dscmp, char* unp, const struct xdr_discrim* choices, xdrproc_t dfault)
{
	register enum_t dscm;

	/*
	 * we deal with the discriminator;  it's an enum
	 */
	if (!xdr_enum(xdrs, dscmp)) {
		return (FALSE);
	}
	dscm = *dscmp;

	/*
	 * search choices for a value that matches the discriminator.
	 * if we find one, execute the xdr routine for that value.
	 */
	for (; choices->proc != NULL_xdrproc_t; choices++) {
		if (choices->value == dscm)
			return ((*(choices->proc)) (xdrs, unp, LASTUNSIGNED));
	}

	/*
	 * no match - execute the default xdr routine if there is one
	 */
	return ((dfault == NULL_xdrproc_t) ? FALSE :
			(*dfault) (xdrs, unp, LASTUNSIGNED));
}


/*
 * Non-portable xdr primitives.
 * Care should be taken when moving these routines to new architectures.
 */


/*
 * XDR null terminated ASCII strings
 * xdr_string deals with "C strings" - arrays of bytes that are
 * terminated by a NULL character.  The parameter cpp references a
 * pointer to storage; If the pointer is null, then the necessary
 * storage is allocated.  The last parameter is the max allowed length
 * of the string as specified by a protocol.
 */
bool_t xdr_string(XDR *xdrs, char **cpp, unsigned int maxsize)
{
	register char *sp = *cpp;	/* sp is the actual string pointer */
	unsigned int size;
	unsigned int nodesize;

	/*
	 * first deal with the length since xdr strings are counted-strings
	 */
	switch (xdrs->x_op) {
	case XDR_FREE:
		if (sp == NULL) {
			return (TRUE);		/* already free */
		}
		/* fall through... */
	case XDR_ENCODE:
		size = strlen(sp);
		break;
	}
	if (!xdr_u_int(xdrs, &size)) {
		return (FALSE);
	}
	if (size > maxsize) {
		return (FALSE);
	}
	nodesize = size + 1;

	/*
	 * now deal with the actual bytes
	 */
	switch (xdrs->x_op) {

	case XDR_DECODE:
		if (nodesize == 0) {
			return (TRUE);
		}
		if (sp == NULL)
			*cpp = sp = (char *) rt_malloc(nodesize);
		if (sp == NULL) {
			rt_kprintf("xdr_string: out of memory\n");
			return (FALSE);
		}
		sp[size] = 0;
		/* fall into ... */

	case XDR_ENCODE:
		return (xdr_opaque(xdrs, sp, size));

	case XDR_FREE:
		rt_free(sp);
		*cpp = NULL;
		return (TRUE);
	}
	return (FALSE);
}

/* 
 * Wrapper for xdr_string that can be called directly from 
 * routines like clnt_call
 */
bool_t xdr_wrapstring(XDR *xdrs, char **cpp)
{
	if (xdr_string(xdrs, cpp, LASTUNSIGNED)) {
		return (TRUE);
	}
	return (FALSE);
}

/*
 * XDR an array of arbitrary elements
 * *addrp is a pointer to the array, *sizep is the number of elements.
 * If addrp is NULL (*sizep * elsize) bytes are allocated.
 * elsize is the size (in bytes) of each element, and elproc is the
 * xdr procedure to call to handle each element of the array.
 */
bool_t xdr_array(XDR *xdrs, char **addrp, unsigned int *sizep, unsigned int maxsize, unsigned int elsize, xdrproc_t elproc)
{
	register unsigned int i;
	register char* target = *addrp;
	register unsigned int c;			/* the actual element count */
	register bool_t stat = TRUE;
	register unsigned int nodesize;

	/* like strings, arrays are really counted arrays */
	if (!xdr_u_int(xdrs, sizep)) {
		return (FALSE);
	}
	c = *sizep;
	if ((c > maxsize) && (xdrs->x_op != XDR_FREE)) {
		return (FALSE);
	}
	/* duh, look for integer overflow (fefe) */
	{
	  unsigned int i;
	  nodesize = 0;
	  for (i=c; i; --i) {
	    unsigned int tmp=nodesize+elsize;
	    if (tmp<nodesize)	/* overflow */
	      return FALSE;
	    nodesize=tmp;
	  }
	}

	/*
	 * if we are deserializing, we may need to allocate an array.
	 * We also save time by checking for a null array if we are freeing.
	 */
	if (target == NULL)
		switch (xdrs->x_op) {
		case XDR_DECODE:
			if (c == 0)
				return (TRUE);
			*addrp = target = rt_malloc(nodesize);
			if (target == NULL) {
				rt_kprintf("xdr_array: out of memory\n");
				return (FALSE);
			}
			memset(target, 0, nodesize);
			break;

		case XDR_FREE:
			return (TRUE);
		}

	/*
	 * now we xdr each element of array
	 */
	for (i = 0; (i < c) && stat; i++) {
		stat = (*elproc) (xdrs, target, LASTUNSIGNED);
		target += elsize;
	}

	/*
	 * the array may need freeing
	 */
	if (xdrs->x_op == XDR_FREE) {
		rt_free(*addrp);
		*addrp = NULL;
	}
	return (stat);
}

/*
 * xdr_vector():
 *
 * XDR a fixed length array. Unlike variable-length arrays,
 * the storage of fixed length arrays is static and unfreeable.
 * > basep: base of the array
 * > size: size of the array
 * > elemsize: size of each element
 * > xdr_elem: routine to XDR each element
 */
bool_t xdr_vector(XDR *xdrs, char *basep, unsigned int nelem, unsigned int elemsize, xdrproc_t xdr_elem)
{
	register unsigned int i;
	register char *elptr;

	elptr = basep;
	for (i = 0; i < nelem; i++) {
		if (!(*xdr_elem) (xdrs, elptr, LASTUNSIGNED)) {
			return (FALSE);
		}
		elptr += elemsize;
	}
	return (TRUE);
}


/*
 * XDR an indirect pointer
 * xdr_reference is for recursively translating a structure that is
 * referenced by a pointer inside the structure that is currently being
 * translated.  pp references a pointer to storage. If *pp is null
 * the  necessary storage is allocated.
 * size is the sizeof the referneced structure.
 * proc is the routine to handle the referenced structure.
 */
bool_t xdr_reference(XDR *xdrs, char **pp, unsigned int size, xdrproc_t proc)
{
	register char* loc = *pp;
	register bool_t stat;

	if (loc == NULL)
		switch (xdrs->x_op) {
		case XDR_FREE:
			return (TRUE);

		case XDR_DECODE:
			*pp = loc = (char*) rt_malloc(size);
			if (loc == NULL) {
				rt_kprintf("xdr_reference: out of memory\n");
				return (FALSE);
			}
			memset(loc, 0, (int) size);
			break;
		}

	stat = (*proc) (xdrs, loc, LASTUNSIGNED);

	if (xdrs->x_op == XDR_FREE) {
		rt_free(loc);
		*pp = NULL;
	}
	return (stat);
}


/*
 * xdr_pointer():
 *
 * XDR a pointer to a possibly recursive data structure. This
 * differs with xdr_reference in that it can serialize/deserialiaze
 * trees correctly.
 *
 *  What's sent is actually a union:
 *
 *  union object_pointer switch (boolean b) {
 *  case TRUE: object_data data;
 *  case FALSE: void nothing;
 *  }
 *
 * > objpp: Pointer to the pointer to the object.
 * > obj_size: size of the object.
 * > xdr_obj: routine to XDR an object.
 *
 */
bool_t xdr_pointer(XDR *xdrs, char **objpp, unsigned int obj_size, xdrproc_t xdr_obj)
{

	bool_t more_data;

	more_data = (*objpp != NULL);
	if (!xdr_bool(xdrs, &more_data)) {
		return (FALSE);
	}
	if (!more_data) {
		*objpp = NULL;
		return (TRUE);
	}
	return (xdr_reference(xdrs, objpp, obj_size, xdr_obj));
}
