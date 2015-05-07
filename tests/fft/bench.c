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

#include "gf2x-config.h"
#include "gf2x-thresholds.h"
#include "check-and-bench-common.h"

#ifdef  MULCOUNT
extern int mulcount;
#else
static const int mulcount = 0;
#endif


void usage_and_die(char **argv)
{
    fprintf(stderr, "usage: %s nmin nmax [-s step|-f factor] [-o order]\n", argv[0]);
    fprintf(stderr, "  where nmin and nmax are numbers of 64-words\n");
    exit(1);
}

/* usage:
 *   ./bench nmin nmax [step]
 */

int main(int argc, char **argv)
{
    int nmin = 0, nmax = 0, n;
    int step = 1;
    double factor = 1.0;
    int additive = 1;
    unsigned long *f, *g, *h;
    int i;

    for(i = 1 ; i < argc ; i++) {
        if (strcmp(argv[i], "-h") == 0) usage_and_die(argv);
        if (strcmp(argv[i], "-") == 0) usage_and_die(argv);
        if (strcmp(argv[i], "--help") == 0) usage_and_die(argv);

        if (i < argc - 1 && strcmp(argv[i], "-f") == 0) {
	    additive = 0;
	    factor = atof(argv[++i]);
            continue;
        }
        if (i < argc - 1 && strcmp(argv[i], "-s") == 0) {
	    additive = 1;
	    step = atoi(argv[++i]);
            continue;
        }
        if (i < argc - 1 && strcmp(argv[i], "-o") == 0) {
            init_extra_arg = atoi(argv[++i]);
            continue;
        }
        if (!nmin) {
            nmin = atoi(argv[i]);
            if (!nmin) usage_and_die(argv);
            continue;
        }
        if (!nmax) {
            nmax = atoi(argv[i]);
            if (!nmax) usage_and_die(argv);
            continue;
        }
        usage_and_die(argv);
    }


    if (nmin < 33) {
	fprintf(stderr,
		"Warning: nmin adjusted to the minimal value allowed: 33.\n");
	nmin = 33;
    }
    if (nmin > nmax) {
	fprintf(stderr, "Error: nmin should be less or equal to nmax\n");
	usage_and_die(argv);
    }

    f = (unsigned long *) malloc(nmax * sizeof(unsigned long));
    g = (unsigned long *) malloc(nmax * sizeof(unsigned long));
    h = (unsigned long *) malloc(2 * nmax * sizeof(unsigned long));

    uint32_t start=0x32104567UL;
    uint32_t ratio=0x76540123UL;
    uint32_t v = start;

    /* we really care about the number of words here, not about how
     * consistent this is depending on whether we're talking 32- or
     * 64- bits.
     */
    size_t n32 = nmax;
#if GF2X_WORDSIZE == 64
    n32 *= 2;
#endif

    uint32_t v = start;

    v = fill(f, n32, v, ratio);
    v = fill(g, n32, v, ratio);

#ifdef ENGINE_TERNARY
    int automatic_tuning = (init_extra_arg == 0);
#endif

    n = nmin;
    while (n <= nmax) {
	int rep;
#ifdef  MULCOUNT
        mulcount=0;
#endif

        time_total = 0;
        time_dft = 0;
        time_ift = 0;
        time_conv = 0;

#ifdef ENGINE_TERNARY
        if (automatic_tuning) {
#ifdef ARTIFICIAL_NON_SPLIT_VERSION
            int64_t T_FFT_TAB[][2] = {
                { 1, 1 },
                { 7572, 243 },
                { 29064, 729 },
                { 82703, 2187 },
                { 275719, 6561 },
                { 806528, 19683 }, };
#else
            int64_t T_FFT_TAB[][2] = GF2X_MUL_FFT_TABLE;
#endif
            long ix, K;
            long max_ix = sizeof(T_FFT_TAB)/sizeof(T_FFT_TAB[0]);
            for (ix = 0; T_FFT_TAB[ix + 1][0] <= n && ix + 1 < max_ix; ix++);
            /* now T_FFT_TAB[ix][0] <= n < T_FFT_TAB[ix+1][0] */
            K = T_FFT_TAB[ix][1];
            init_extra_arg = K;
        }
#endif

	long order = ENGINE_mul(h, f, n, g, n);

	if (time_total == 0)
	    rep = 1000;
	else {
	    rep = 200 / time_total;	// to make about 0.2 sec.
	    if (rep < 2)
		rep = 2;
	}

	//printf("benching n = %d, repeating %d\n", n, rep);
        if (time_total < 0.5) {
            for (i = 0; i < rep; ++i)
                ENGINE_mul(h, f, n, g, n);
        } else {
            rep = 1; // be content with our first timing.
        }
        printf("%d %f %f %f %f %ld %d\n",
                n,
                (double) time_total / rep,
                (double) time_dft / 2.0 / rep,
                (double) time_ift / rep,
                (double) time_conv/ rep,
                order,
                mulcount
                );
        fprintf(stderr, "%d %f %f %f %f %ld %d\n",
                n,
                (double) time_total / rep,
                (double) time_dft / 2.0 / rep,
                (double) time_ift / rep,
                (double) time_conv/ rep,
                order,
                mulcount
                );
	fflush(stdout);
	fflush(stderr);
	if (additive)
	    n += step;
	else {
	    int new_n = (int) (((double) n) * factor);
	    if (new_n <= n)
		n++;
	    else
		n = new_n;
	}
    }

    return 0;
}
