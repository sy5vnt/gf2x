/* An implementation of Cantor's algorithm for multiplication of
   polynomials over GF(2).
   
   Copyright 2007 Pierrick Gaudry.
   Copyright 2008,2009,2010,2012 Emmanuel Thomé.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation; either version 2.1 of the License, or (at
   your option) any later version.
   
   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
   License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with CADO-NFS; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef CANTOR_H_
#define CANTOR_H_

#include <stdint.h>
#include <stdlib.h>

#include "macros.h"

#include "gf2x-thresholds.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mulCantor(unsigned long *H, unsigned long *F, size_t Fl, unsigned long *G, size_t Gl);



// now for the gf2x-fft interface.
//
// note that we must implement some sort of fallback on the fake_fft
// thing when the polynomials are too small, or something like this. The
// gf2x-fft interface requires that any size can be used.

struct cantor_info_struct {
    unsigned int k;
    size_t n;
};
typedef struct cantor_info_struct cantor_info_t[1];
typedef struct cantor_info_struct * cantor_info_ptr;
typedef const struct cantor_info_struct * cantor_info_srcptr;

#if !defined(GF2X_WORDSIZE) || (GF2X_WORDSIZE != 32 && GF2X_WORDSIZE != 64)
#error  "define GF2X_WORDSIZE to either 32 or 64"
#endif

#if !defined(CANTOR_BASE_FIELD_SIZE) || (CANTOR_BASE_FIELD_SIZE != 64 && CANTOR_BASE_FIELD_SIZE != 128)
#error  "Define CANTOR_BASE_FIELD_SIZE to 64 or 128"
#endif

#if CANTOR_BASE_FIELD_SIZE == 128
#if GF2X_WORDSIZE == 64
#include "mpfq/x86_64/mpfq_2_128.h"
#else
#include "mpfq/i386/mpfq_2_128.h"
#endif
#define cantor_base_field_elt mpfq_2_128_elt
#else
#if GF2X_WORDSIZE == 64
#include "mpfq/x86_64/mpfq_2_64.h"
#else
#include "mpfq/i386/mpfq_2_64.h"
#endif
#define cantor_base_field_elt mpfq_2_64_elt
#endif

extern void cantor_init(cantor_info_t p, size_t nF, size_t nG, ...);
extern void cantor_clear(cantor_info_t p MAYBE_UNUSED);
extern cantor_base_field_elt * cantor_alloc(const cantor_info_t p, size_t n);
extern void cantor_free(
        const cantor_info_t p MAYBE_UNUSED,
        cantor_base_field_elt * x,
        size_t n MAYBE_UNUSED);
extern cantor_base_field_elt * cantor_get(const cantor_info_t p, cantor_base_field_elt * x, size_t k);
extern void cantor_zero(const cantor_info_t p, cantor_base_field_elt * x, size_t n);

extern void cantor_dft(const cantor_info_t p, cantor_base_field_elt * x, unsigned long * F, size_t nF);
extern void cantor_compose(const cantor_info_t p,
		cantor_base_field_elt * y, cantor_base_field_elt * x1, cantor_base_field_elt * x2);
extern void cantor_addcompose(const cantor_info_t p,
		cantor_base_field_elt * y, cantor_base_field_elt * x1, cantor_base_field_elt * x2);
extern void cantor_add(const cantor_info_t p,
		cantor_base_field_elt * y, cantor_base_field_elt * x1, cantor_base_field_elt * x2);
extern void cantor_cpy(const cantor_info_t p, cantor_base_field_elt * y, cantor_base_field_elt * x);
extern void cantor_ift(const cantor_info_t p,
		unsigned long * H, size_t Hl, cantor_base_field_elt * h);
extern size_t cantor_size(cantor_info_srcptr p);
extern void cantor_init_similar(cantor_info_ptr o, size_t bits_a, size_t bits_b, cantor_info_srcptr other);
extern int cantor_compatible(cantor_info_srcptr o1, cantor_info_srcptr o2);

#ifdef __cplusplus
}
#endif

#endif	/* CANTOR_H_ */
