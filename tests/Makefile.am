#  This file is part of the gf2x library.
#
#  Copyright 2007, 2008, 2009, 2010, 2013
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


# Be aware that ``make check'' from here cannot ensure that the
# upper-level library is up-to-date.

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir)

check_PROGRAMS=check-mul check-addmul
check_mul_SOURCES=check-mul.c test-tools.c
check_addmul_SOURCES=check-addmul.c
check_mul_LDADD=$(top_builddir)/libgf2x.la
check_addmul_LDADD=$(top_builddir)/libgf2x.la

SYNTHESIZED_TESTS = \
	check_1_1_1_819ea234.mul		\
	check_2_2_1_928e7e94.mul		\
	check_3_3_1_14aac2f1.mul		\
	check_4_4_1_fbc8042f.mul		\
	check_5_5_1_049e6e28.mul		\
	check_6_6_1_f7fa48ac.mul		\
	check_7_7_1_39d1a8b9.mul		\
	check_8_8_1_11334230.mul		\
	check_9_9_1_a499e414.mul		\
	check_20_20_1_d40a21e3.mul		\
	check_100_20_1_6dc5ac13.mul		\
	check_100_100_1_5094c182.mul		\
	check_1000_20_1_6ce07fed.mul		\
	check_1000_100_1_08825281.mul		\
	check_1000_1000_1_c28bc2e3.mul		\
	check_5437_20_1_ad84f617.mul		\
	check_5437_100_1_8eb064ef.mul		\
	check_5437_1000_1_c546a34c.mul		\
	check_5437_5437_1_f09c5936.mul		\
	check_10000_20_1_4d3b9b2d.mul		\
	check_10000_100_1_f2e7cc20.mul		\
	check_10000_1000_1_3b8778b1.mul		\
	check_10000_5437_1_b337c8eb.mul		\
	check_10000_10000_1_2706ca53.mul	\
	check_832040_1346269_1_8513d1fb.mul	\
	check_785672_1271244_1_842e0d19.mul

$(SYNTHESIZED_TESTS) : ; @touch $@

TESTS = check-addmul $(SYNTHESIZED_TESTS)

TEST_EXTENSIONS = .mul
# We'll run the *.mul tests above as:
# 	./do-check-mul.sh -m check_10000_5437_64751d23.mul
MUL_LOG_COMPILER = $(srcdir)/do-check-mul.sh
AM_MUL_LOG_FLAGS = -m

EXTRA_DIST=do-check-mul.sh

SUBDIRS=fft

