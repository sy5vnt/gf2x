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

#ifdef  MULCOUNT
extern int mulcount;
#else
static const int mulcount = 0;
#endif

#if defined(ENGINE_CANTOR)
#include "gf2x-cantor-fft.h"

#define ENGINE_EXTRA_ARG_DEFAULT  0     /* does not make sense here (yet) */

#define ENGINE_info_t gf2x_cantor_fft_info_t
#define ENGINE_srcptr gf2x_cantor_fft_srcptr
#define ENGINE_ptr gf2x_cantor_fft_ptr
#define ENGINE_init gf2x_cantor_fft_init
#define ENGINE_alloc gf2x_cantor_fft_alloc
#define ENGINE_dft gf2x_cantor_fft_dft
#define ENGINE_compose gf2x_cantor_fft_compose
#define ENGINE_free gf2x_cantor_fft_free
#define ENGINE_ift gf2x_cantor_fft_ift
#define ENGINE_clear gf2x_cantor_fft_clear
#define ENGINE_recoverorder(o)  ((o)->k)
#elif defined(ENGINE_TERNARY)
#include "gf2x-ternary-fft.h"
#ifdef MULCOUNT
#error "MULCOUNT incompatible with gf2x_ternary_fft"
#endif

/* This is fit for 1M words */
#define ENGINE_EXTRA_ARG_DEFAULT  0

#define ENGINE_info_t gf2x_ternary_fft_info_t
#define ENGINE_srcptr gf2x_ternary_fft_srcptr
#define ENGINE_ptr gf2x_ternary_fft_ptr
#define ENGINE_init gf2x_ternary_fft_init
#define ENGINE_alloc gf2x_ternary_fft_alloc
#define ENGINE_dft gf2x_ternary_fft_dft
#define ENGINE_compose gf2x_ternary_fft_compose
#define ENGINE_free gf2x_ternary_fft_free
#define ENGINE_ift gf2x_ternary_fft_ift
#define ENGINE_clear gf2x_ternary_fft_clear
#define ENGINE_recoverorder(o)  ((o)->K * ((o)->split ? -1 : 1))
#else
#error "Please define either ENGINE_CANTOR or ENGINE_TERNARY"
#endif

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

long ENGINE_mul(unsigned long * H, unsigned long * F, size_t Fl, unsigned long * G, size_t Gl)
{
    int t;
    ENGINE_info_t order;

    t=cputime(); time_total -= t;
    ENGINE_init(order, Fl * GF2X_WORDSIZE, Gl * GF2X_WORDSIZE, init_extra_arg);

    ENGINE_ptr f = ENGINE_alloc(order, 1);

    t=cputime(); time_dft -= t;
    ENGINE_dft(order, f, F, Fl * GF2X_WORDSIZE);
    t=cputime(); time_dft += t;

    ENGINE_ptr g = ENGINE_alloc(order, 1);

    t=cputime(); time_dft -= t;
    ENGINE_dft(order, g, G, Gl * GF2X_WORDSIZE);
    t=cputime(); time_dft += t;

    t=cputime(); time_conv -= t;
    ENGINE_compose(order, f, (ENGINE_srcptr) f, (ENGINE_srcptr) g);
    t=cputime(); time_conv += t;

    ENGINE_free(order, g, 1);

    t=cputime(); time_ift -= t;
    ENGINE_ift(order, H, (Fl+Gl) * GF2X_WORDSIZE - 1, f);
    t=cputime(); time_ift += t;

    long res = ENGINE_recoverorder(order);

    ENGINE_free(order, f, 1);
    ENGINE_clear(order);

    t=cputime(); time_total += t;

    return res;
}

int test(int N)
{
    /* Be ugly */
    extern char             __gmp_rands_initialized;
    extern gmp_randstate_t  __gmp_rands;

    int i;
    unsigned long *f, *g, *h;

    f = (unsigned long *) malloc(N * sizeof(unsigned long));
    g = (unsigned long *) malloc(N * sizeof(unsigned long));
    h = (unsigned long *) malloc(2 * N * sizeof(unsigned long));

    __gmp_rands_initialized = 1;
    gmp_randinit_default (__gmp_rands);
    // gmp_randseed_ui(__gmp_rands, time(NULL));
    gmp_randseed_ui(__gmp_rands, 0); //time(NULL));

    mpn_random((mp_limb_t *) f, (sizeof(unsigned long) / sizeof(mp_limb_t)) * N);
    mpn_random((mp_limb_t *) g, (sizeof(unsigned long) / sizeof(mp_limb_t)) * N);

    printf("w := %u;\n", GMP_LIMB_BITS);
#ifdef  ENGINE_CANTOR
    printf("b := %u;\n", CANTOR_BASE_FIELD_SIZE);
#endif
    printf("f := [\n");
    for (i = 0; i < N - 1; ++i)
	printf("%lu, ", f[i]);
    printf("%lu\n];\n", f[N - 1]);
    printf("\n");
    printf("g := [\n");
    for (i = 0; i < N - 1; ++i)
	printf("%lu, ", g[i]);
    printf("%lu\n];\n", g[N - 1]);
    printf("\n");

    //for (i = 0; i < 10; ++i) 
    ENGINE_mul(h,f,N,g,N);

    printf("fg := [\n");
    for (i = 0; i < 2 * N - 1; ++i)
	printf("%lu, ", h[i]);
    printf("%lu\n];\n", h[2 * N - 1]);

    free(h);
    free(g);
    free(f);
    return 0;
}
void usage_and_die(char **argv)
{
    fprintf(stderr, "usage: %s nmin nmax [-s step|-f factor] [-o order]\n", argv[0]);
    fprintf(stderr, "  where nmin and nmax are numbers of 64-words\n");
    fprintf(stderr, "OR: %s --test <n>\n", argv[0]);
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

        if (i < argc - 1 && strcmp(argv[i], "--test") == 0) {
            if (i != 1 || argc != 3) {
                usage_and_die(argv);
            }
            int N = atoi(argv[++i]);
            test(N);
            exit(0);
        }
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

    mpn_random((mp_limb_t *) f,
	       (sizeof(unsigned long) / sizeof(mp_limb_t)) * nmax);
    mpn_random((mp_limb_t *) g,
	       (sizeof(unsigned long) / sizeof(mp_limb_t)) * nmax);


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
