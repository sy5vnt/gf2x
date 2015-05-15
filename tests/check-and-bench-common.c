/* This file is part of the gf2x library.

   Copyright 2007, 2008, 2009, 2010, 2013, 2014, 2015
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <gmp.h>		// for random

#include "gf2x/gf2x-config.h"
#include "gf2x/gf2x-impl.h"
#include "gf2x/gf2x-thresholds.h"

#include "test-tools.h"
#include "check-and-bench-common.h"

long init_extra_arg = ENGINE_EXTRA_ARG_DEFAULT;

// cputime in millisec.
static int cputime()
{
    struct rusage rus;
    getrusage(0, &rus);
    return rus.ru_utime.tv_sec * 1000 + rus.ru_utime.tv_usec / 1000;
}


int time_total;
int time_dft;
int time_conv;
int time_ift;

/* using the selected FFT engine, multiply two n by n matrices of
 * polynomials with Fl and Gl words in each entry, respectively */
long ENGINE_mul(unsigned long ** H, unsigned long ** F, size_t Fl, unsigned long ** G, size_t Gl, int n)
{
    int t;
    ENGINE_info_t order;

    t=cputime(); time_total -= t;
    ENGINE_init(order, Fl * GF2X_WORDSIZE, Gl * GF2X_WORDSIZE, init_extra_arg);

    ENGINE_ptr f = ENGINE_alloc(order, n*n);

    t=cputime(); time_dft -= t;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
            ENGINE_dft(order, ENGINE_get(order, f, i*n+j), F[i*n+j], Fl * GF2X_WORDSIZE);
    t=cputime(); time_dft += t;

    ENGINE_ptr g = ENGINE_alloc(order, n*n);

    t=cputime(); time_dft -= t;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
            ENGINE_dft(order, ENGINE_get(order, g, i*n+j), G[i*n+j], Gl * GF2X_WORDSIZE);
    t=cputime(); time_dft += t;

    ENGINE_ptr h = ENGINE_alloc(order, n*n);

    t=cputime(); time_conv -= t;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++) {
            ENGINE_compose(order, 
                    ENGINE_get(order, h, i*n+j),
                    ENGINE_get_const(order, (ENGINE_srcptr) f, i*n/*+k*/),
                    ENGINE_get_const(order, (ENGINE_srcptr) g, /*k*n+*/j));
            for(int k = 1 ; k < n ; k++)
                ENGINE_addcompose(order, 
                        ENGINE_get(order, h, i*n+j),
                        ENGINE_get_const(order, (ENGINE_srcptr) f, i*n+k),
                        ENGINE_get_const(order, (ENGINE_srcptr) g, k*n+j));
        }
    t=cputime(); time_conv += t;

    ENGINE_free(order, g, n*n);
    ENGINE_free(order, f, n*n);

    t=cputime(); time_ift -= t;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
            ENGINE_ift(order, H[i*n+j], (Fl+Gl) * GF2X_WORDSIZE - 1,  ENGINE_get(order, h, i*n+j));
    t=cputime(); time_ift += t;

    long res = ENGINE_recoverorder(order);

    ENGINE_free(order, h, n*n);
    ENGINE_clear(order);

    t=cputime(); time_total += t;

    return res;
}
