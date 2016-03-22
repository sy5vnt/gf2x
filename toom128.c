/* This file is part of the gf2x library.

   Copyright 2007-2016
   Richard Brent, Pierrick Gaudry, Emmanuel Thome', Paul Zimmermann

   This program is free software; you can redistribute it and/or modify it
   under the terms of either:
    - If the archive contains a file named toom-gpl.c (not a trivial
    placeholder), the GNU General Public License as published by the Free
    Software Foundation; either version 3 of the License, or (at your
    option) any later version.
    - If the archive contains a file named toom-gpl.c which is a trivial
    placeholder, the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
   
   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the license text for more details.
   
   You should have received a copy of the GNU General Public License as
   well as the GNU Lesser General Public License along with this program;
   see the files COPYING and COPYING.LIB.  If not, write to the Free
   Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

/* Variants of Toom-Cook using __uint128_t, copied from toom.c.
   Those routines assume that "unsigned long" is a 64-bit type. */

#include <stdio.h>
#include <string.h> /* for memcpy() */

#include "gf2x.h"
#include "gf2x/gf2x-impl.h"

static inline unsigned long*
aligned128 (unsigned long *x)
{
  return (unsigned long*) (((long) x % 16 == 0) ? x : x + 1);
}

static void
gf2x_mul_karax_internal (__uint128_t * c, const __uint128_t * a,
                           const __uint128_t * b, long n, __uint128_t * stk)
{
    __uint128_t t;
    __uint128_t *aa, *bb, *cc;
    long j, d, n2;

    if (2 * n < GF2X_MUL_KARAX_THRESHOLD) {
      gf2x_mul_kara ((unsigned long*) c, (unsigned long*) a,
                     (unsigned long*) b, 2 * n, (unsigned long*) stk);
      return;
    }

    n2 = (n + 1) / 2;		/* ceil(n/2) */
    d = n & 1;			/* 2*n2 - n = 1 if n odd, 0 if n even */
    aa = stk;			/* Size n2   */
    bb = aa + n2;		/* Size n2   */
    cc = bb + n2;		/* Size n2   */

    stk = cc + n2;		/* sp(n) = 3*ceil(n/2)) + sp(ceil(n/2)) */

    const __uint128_t *a1 = a + n2;	/* a[n2] */
    const __uint128_t *b1 = b + n2;	/* b[n2] */
    __uint128_t *c1 = c + n2;		/* c[n2]   */
    __uint128_t *c2 = c1 + n2;	/* c[2*n2] */
    __uint128_t *c3 = c2 + n2;	/* c[3*n2] */

    gf2x_mul_karax_internal (c, a, b, n2, stk);	/* Low */

    gf2x_mul_karax_internal (c2, a1, b1, n2 - d, stk);	/* High */

    for (j = 0; j < n2 - d; j++) {
	aa[j] = a[j] ^ a1[j];
	bb[j] = b[j] ^ b1[j];
	cc[j] = c1[j] ^ c2[j];
    }
    for (; j < n2; j++) {	/* Only when n odd */
	aa[j] = a[j];
	bb[j] = b[j];
	cc[j] = c1[j] ^ c2[j];
    }

    gf2x_mul_karax_internal (c1, aa, bb, n2, stk);	/* Middle */

    for (j = 0; j < n2 - 2 * d; j++) {
	t = cc[j];
	c1[j] ^= t ^ c[j];
	c2[j] ^= t ^ c3[j];
    }
    for (; j < n2; j++) {	/* Only when n odd */
	c1[j] ^= cc[j] ^ c[j];
	c2[j] ^= cc[j];
    }
}

void
gf2x_mul_karax (unsigned long *c, const unsigned long *a,
                const unsigned long *b, long n, unsigned long *stk)
{
    unsigned long *cc, *aa, *bb;

    //    printf ("gf2x_mul_karax, n=%ld\n", n);
    // fflush (stdout);

    if ((n & 1) == 0) /* n is even */
      {
        /* check if c is 16-byte aligned */
        if ((long) c % 16 == 0)
          cc = c;
        else
          cc = aligned128 (alloca ((n + 1) * sizeof (unsigned long)));

        /* check if a is 16-byte aligned */
        if ((long) a % 16 == 0)
          aa = (unsigned long*) a;
        else
          {
            aa = aligned128 (alloca ((n + 1) * sizeof (unsigned long)));
            memcpy (aa, a, n * sizeof (unsigned long));
          }

        /* check if b is 16-byte aligned */
        if ((long) b % 16 == 0)
          bb = (unsigned long*) b;
        else
          {
            bb = aligned128 (alloca ((n + 1) * sizeof (unsigned long)));
            memcpy (bb, b, n * sizeof (unsigned long));
          }
        
        gf2x_mul_karax_internal ((__uint128_t*) cc, (__uint128_t*) aa,
                                   (__uint128_t*) bb, n >> 1,
                                   (__uint128_t*) aligned128 (stk));

        if (cc != c)
          memcpy (c, cc, 2 * n * sizeof (unsigned long));
      }
    else /* n is odd */
      {
        cc = aligned128 (alloca ((2 * n + 3) * sizeof (unsigned long)));

        aa = aligned128 (alloca ((n + 2) * sizeof (unsigned long)));
        memcpy (aa, a, n * sizeof (unsigned long));
        aa[n] = 0;

        bb = aligned128 (alloca ((n + 2) * sizeof (unsigned long)));
        memcpy (bb, b, n * sizeof (unsigned long));
        bb[n] = 0;
        
        gf2x_mul_karax_internal ((__uint128_t*) cc, (__uint128_t*) aa,
                                 (__uint128_t*) bb, (n + 1) >> 1,
                                   (__uint128_t*) aligned128 (stk));

        memcpy (c, cc, 2 * n * sizeof (unsigned long));
      }
}

