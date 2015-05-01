#  This file is part of the gf2x library.
#
#  Copyright 2007, 2008, 2009, 2010, 2013
#  Richard Brent, Pierrick Gaudry, Emmanuel Thome', Paul Zimmermann
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of either:
#   - If the archive contains a file named toom-gpl.c, the GNU General
#     Public License as published by the Free Software Foundation; either
#     version 3 of the License, or (at your option) any later version.
#   - If the archive contains no file named toom-gpl.c, the GNU Lesser
#     General Public License as published by the Free Software
#     Foundation; either version 2.1 of the License, or (at your option)
#     any later version.
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


# Be aware that ``make check'' from here cannot ensure that the
# upper-level library is up-to-date.

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir)

check_PROGRAMS=check-mul check-addmul
check_mul_SOURCES=check-mul.c
check_addmul_SOURCES=check-addmul.c
check_mul_LDADD=$(top_builddir)/libgf2x.la
check_addmul_LDADD=$(top_builddir)/libgf2x.la

# LOG_COMPILER=$(SHELL) 2>/dev/null

SYNTHESIZED_TESTS = \
    check_1_1_71194aa9_76540123.mul		\
    check_2_2_b0a25e22_76540123.mul		\
    check_3_3_d0821e1e_76540123.mul		\
    check_4_4_cbcec8a9_76540123.mul		\
    check_5_5_ef506fd3_76540123.mul		\
    check_6_6_5e201456_76540123.mul		\
    check_7_7_d492afae_76540123.mul		\
    check_8_8_1068cb97_76540123.mul		\
    check_9_9_2e2e13e3_76540123.mul		\
    check_20_20_8b5a3c69_76540123.mul		\
    check_100_20_a8d1adaa_76540123.mul		\
    check_100_100_2269c4fa_76540123.mul		\
    check_1000_20_a419864d_76540123.mul		\
    check_1000_100_fc4a566b_76540123.mul	\
    check_1000_1000_a12a7e03_76540123.mul	\
    check_5437_20_87588c37_76540123.mul		\
    check_5437_100_9397839a_76540123.mul	\
    check_5437_1000_ce4d6e43_76540123.mul	\
    check_5437_5437_9e364ad1_76540123.mul	\
    check_10000_20_11bbc400_76540123.mul	\
    check_10000_100_cc43341e_76540123.mul	\
    check_10000_1000_d51f2fa8_76540123.mul	\
    check_10000_5437_64751d23_76540123.mul	\
    check_10000_10000_c2f4746f_76540123.mul	\
    check_832040_1346269_6fd76898_76540123.mul	\
    check_785672_1271244_23c9bb24_76540123.mul

$(SYNTHESIZED_TESTS) : ; @touch $@

TESTS = check-addmul $(SYNTHESIZED_TESTS)

TEST_EXTENSIONS = .mul
# We'll run the *.mul tests above as:
# 	./do-check-mul.sh -m check_10000_5437_64751d23_76540123.mul
MUL_LOG_COMPILER = $(srcdir)/do-check-mul.sh
AM_MUL_LOG_FLAGS = -m

EXTRA_DIST=do-check-mul.sh
