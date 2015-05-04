#  This file is part of the gf2x library.
#
#  Copyright 2007, 2008, 2009, 2010, 2013, 2014, 2015
#  Richard Brent, Pierrick Gaudry, Emmanuel Thome', Paul Zimmermann
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of either:
#   - If the archive contains a file named toom-gpl.c (not a trivial
#     placeholder), the GNU General Public License as published by the
#     Free Software Foundation; either version 3 of the License, or (at
#     your option) any later version.
#   - If the archive contains a file named toom-gpl.c which is a trivial
#     placeholder, the GNU Lesser General Public License as published by
#     the Free Software Foundation; either version 2.1 of the License, or
#     (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful, but WITHOUT
#  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#  FITNESS FOR A PARTICULAR PURPOSE.  See the license text for more details.
#  
#  You should have received a copy of the GNU General Public License as
#  well as the GNU Lesser General Public License along with this program;
#  see the files COPYING and COPYING.LIB.  If not, write to the Free
#  Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
#  02110-1301, USA.

ACLOCAL_AMFLAGS=-I config --install
AM_CFLAGS = -I$(top_srcdir) -I$(top_srcdir)/mpfq
AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/mpfq

# We want to stress-test the cantor implementation with the following
# extra features (compile-time flags)

CCOMMON=-DENGINE_CANTOR -DESCAPE_CANTOR_SYMBOLS
C64=$(CCOMMON) -DCANTOR_BASE_FIELD_SIZE=64
C64nt=$(C64) -DWITHOUT_CANTOR_TRUNCATION
C64gm=$(C64) -DCANTOR_GM
C64gmt=$(C64gm) -DCANTOR_GM_TRUNCATE
C128=$(CCOMMON) -DCANTOR_BASE_FIELD_SIZE=128
C128nt=$(C128) -DWITHOUT_CANTOR_TRUNCATION
C128gm=$(C128) -DCANTOR_GM
C128gmt=$(C128gm) -DCANTOR_GM_TRUNCATE

check_PROGRAMS=

# ternary fft is included by default in gf2x.
check_PROGRAMS += ternary
ternary_SOURCES=bench.c
ternary_CFLAGS= $(AM_CFLAGS) -DENGINE_TERNARY
ternary_LDADD=../libgf2x.la -lgmp

check_PROGRAMS += ternary_ns
ternary_ns_SOURCES=bench.c
ternary_ns_CFLAGS= $(AM_CFLAGS) -DENGINE_TERNARY -DARTIFICIAL_NON_SPLIT_VERSION
ternary_ns_LDADD=../libgf2x.la -lgmp

check_PROGRAMS += cantor64
cantor64_SOURCES=bench.c gf2x-cantor-fft.c
cantor64_CFLAGS= $(AM_CFLAGS) $(C64)
cantor64_LDADD=../libgf2x.la -lgmp

check_PROGRAMS += cantor64nt
cantor64nt_SOURCES=bench.c gf2x-cantor-fft.c
cantor64nt_CFLAGS= $(AM_CFLAGS) $(C64nt)
cantor64nt_LDADD=../libgf2x.la -lgmp

check_PROGRAMS += cantor64gm
cantor64gm_SOURCES=bench.c gf2x-cantor-fft.c
cantor64gm_CFLAGS= $(AM_CFLAGS) $(C64gm)
cantor64gm_LDADD=../libgf2x.la -lgmp

check_PROGRAMS += cantor64gmt
cantor64gmt_SOURCES=bench.c gf2x-cantor-fft.c
cantor64gmt_CFLAGS= $(AM_CFLAGS) $(C64gmt)
cantor64gmt_LDADD=../libgf2x.la -lgmp

check_PROGRAMS += cantor128
cantor128_SOURCES=bench.c gf2x-cantor-fft.c
cantor128_CFLAGS= $(AM_CFLAGS) $(C128)
cantor128_LDADD=../libgf2x.la -lgmp

check_PROGRAMS += cantor128nt
cantor128nt_SOURCES=bench.c gf2x-cantor-fft.c
cantor128nt_CFLAGS= $(AM_CFLAGS) $(C128nt)
cantor128nt_LDADD=../libgf2x.la -lgmp

check_PROGRAMS += cantor128gm
cantor128gm_SOURCES=bench.c gf2x-cantor-fft.c
cantor128gm_CFLAGS= $(AM_CFLAGS) $(C128gm)
cantor128gm_LDADD=../libgf2x.la -lgmp

check_PROGRAMS += cantor128gmt
cantor128gmt_SOURCES=bench.c gf2x-cantor-fft.c
cantor128gmt_CFLAGS= $(AM_CFLAGS) $(C128gmt)
cantor128gmt_LDADD=../libgf2x.la -lgmp

AM_TESTS_ENVIRONMENT = \
    all_programs="$(check_PROGRAMS)"; export all_programs;	\
    all_sizes="10 100 1000 10000 100000"; export all_sizes;	\
    tests_location="$(builddir)"; export tests_location;

TESTS=./debug/check_cantor.sh
EXTRA_DIST=$(TESTS)
