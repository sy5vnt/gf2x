/* This file is part of the gf2x library.

   Copyright 2007, 2008, 2009, 2010, 2013, 2015
   Richard Brent, Pierrick Gaudry, Emmanuel Thome', Paul Zimmermann

   This program is free software; you can redistribute it and/or modify it
   under the terms of either:
    - If the archive contains a file named toom-gpl.c, the GNU General
      Public License as published by the Free Software Foundation; either
      version 3 of the License, or (at your option) any later version.
    - If the archive contains no file named toom-gpl.c, the GNU Lesser
      General Public License as published by the Free Software
      Foundation; either version 2.1 of the License, or (at your option)
      any later version.
   
   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the license text for more details.
   
   You should have received a copy of the GNU General Public License as
   well as the GNU Lesser General Public License along with this program;
   see the files COPYING and COPYING.LIB.  If not, write to the Free
   Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

#ifndef GF2X_IMPL_H_
#define GF2X_IMPL_H_

#include "gf2x.h"
#include "gf2x/gf2x-config.h"
#include "gf2x/gf2x-thresholds.h"

/**********************************************************************/
/* Some support macros */

#include <assert.h>
#ifndef ASSERT
#define ASSERT(x)	assert(x)
#endif

#ifndef GF2X_WORDSIZE
#define GF2X_WORDSIZE  (8 * SIZEOF_UNSIGNED_LONG)
#endif

#ifndef	MAYBE_UNUSED
#if defined(__GNUC__)
#define MAYBE_UNUSED __attribute__ ((unused))
#else
#define MAYBE_UNUSED
#endif
#endif

/* These flags are for internal use */
#define	GF2X_SELECT_KARA	0	/* do not change ! */
#define	GF2X_SELECT_TC3		1
#define	GF2X_SELECT_TC3W	2
#define	GF2X_SELECT_TC4		3
#define	GF2X_SELECT_UNB_DFLT	0
#define	GF2X_SELECT_UNB_TC3U	1	/* do not change ! */

#ifdef __cplusplus
extern "C" {
#endif

extern long gf2x_toomspace(long n);
extern long gf2x_toomuspace(long n);
extern void gf2x_mul_basecase(unsigned long * c, const unsigned long * a,
			 long na, const unsigned long * b, long nb);


extern void gf2x_mul_toom(unsigned long *c, const unsigned long *a,
			const unsigned long *b, long n, unsigned long *stk);
extern void gf2x_mul_kara(unsigned long *c, const unsigned long *a, const unsigned long *b,
			long n, unsigned long *stk);
#if GPL_CODE_PRESENT
extern void gf2x_mul_tc3(unsigned long *c, const unsigned long *a, const unsigned long *b,
		 	long n, unsigned long *stk);
extern void gf2x_mul_tc3w(unsigned long *c, const unsigned long *a, const unsigned long *b,
		        long n, unsigned long *stk);
extern void gf2x_mul_tc4(unsigned long *c, const unsigned long *a, const unsigned long *b,
			long n, unsigned long *stk);
extern void gf2x_mul_tc3u(unsigned long * c, const unsigned long * a, long sa,
	      const unsigned long * b, unsigned long * stk);
#endif /* GPL_CODE_PRESENT */

extern short gf2x_best_toom(unsigned long);
extern long gf2x_toomspace(long);

extern short gf2x_best_utoom(unsigned long);
extern long gf2x_toomuspace(long);


extern void gf2x_mul_fft(unsigned long *c, const unsigned long *a, size_t an,
		            const unsigned long *b, size_t bn, long K);


/* tunetoom.c need to poke into toom.c's tables ; that's very ugly. So
 * please don't use for anything else.
 * */
extern short best_tab[GF2X_TOOM_TUNING_LIMIT];
extern short best_utab[GF2X_TOOM_TUNING_LIMIT];

#ifdef  GF2X_HAVE_SSE2_SUPPORT
#include <emmintrin.h>
#include <stdint.h>
#if defined(__GNUC__) && __GNUC__ == 4 &&__GNUC_MINOR__ == 1
#define _gf2x_mm_cvtsi64_m64(u) _mm_cvtsi64x_m64((u))
#else
#define _gf2x_mm_cvtsi64_m64(u) _mm_cvtsi64_m64((u))
#endif
/* _m128i from 2 int64_t's */
#define _gf2x_mm_setr_epi64(lo, hi)                      		\
    _mm_setr_epi64(                                      		\
            _gf2x_mm_cvtsi64_m64((int64_t) (lo)),       		\
            _gf2x_mm_cvtsi64_m64((int64_t) (hi))        		\
        )
/* _m128i from 1 int64_t's */
#define _gf2x_mm_set1_epi64(u) _mm_set1_epi64( _gf2x_mm_cvtsi64_m64((int64_t) (u)))
/* _m128i from 2 int64_t CONSTANTS (and try to get suffix right) */
#define _gf2x_mm_setr_epi64_c(lo, hi)                    		\
    _mm_setr_epi64(                                      		\
            _gf2x_mm_cvtsi64_m64(INT64_C(lo)),          		\
            _gf2x_mm_cvtsi64_m64(INT64_C(hi))           		\
        )
/* _m128i from 1 int64_t CONSTANT (and try to get suffix right) */
#define _gf2x_mm_set1_epi64_c(u) _mm_set1_epi64( _gf2x_mm_cvtsi64_m64(INT64_C(u)))
/* and same for 32-bits (which, for some, have SSE-2) */
#define _gf2x_mm_setr_epi32(a0, a1, a2, a3)				\
    _mm_setr_epi32(                                      		\
            (int32_t) (a0),						\
            (int32_t) (a1),						\
            (int32_t) (a2),						\
            (int32_t) (a3)						\
            )
#define _gf2x_mm_set1_epi32(u) _mm_set1_epi32( (int32_t) (u))
#define _gf2x_mm_setr_epi32_c(a0, a1, a2, a3)				\
    _mm_setr_epi32(                                      		\
            (INT32_C(a0)),          					\
            (INT32_C(a1)),           					\
            (INT32_C(a2)),          					\
            (INT32_C(a3))           					\
        )
#define _gf2x_mm_set1_epi32_c(u) _mm_set1_epi32(INT32_C(u))
#endif

#ifdef __cplusplus
}
#endif

#endif	/* GF2X_IMPL_H_ */
