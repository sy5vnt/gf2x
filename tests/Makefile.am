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
check_mul_LDADD=../libgf2x.la
check_addmul_LDADD=../libgf2x.la

LOG_COMPILER=$(SHELL) 2>/dev/null
TESTS=do-check-mul.sh

EXTRA_DIST=$(TESTS) check-mul.res
