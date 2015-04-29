ACLOCAL_AMFLAGS=-I config --install
AM_CFLAGS = -I$(top_srcdir) -I$(top_srcdir)/mpfq
AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/mpfq

# The ones that we do build on all occasions.
lib_LTLIBRARIES = libcantor128.la

COMMON_cantor64_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=64
COMMON_cantor128_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=128
COMMON_cantor64cl_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=64 -DHAVE_PCLMUL
COMMON_cantor128cl_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=128 -DHAVE_PCLMUL
COMMON_cantor128clnt_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=128 -DHAVE_PCLMUL -DWITHOUT_CANTOR_TRUNCATION
COMMON_cantor64gm_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=64 -DCANTOR_GM
COMMON_cantor128gm_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=128 -DCANTOR_GM
COMMON_cantor64clgm_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=64 -DHAVE_PCLMUL -DCANTOR_GM
COMMON_cantor128clgm_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=128 -DHAVE_PCLMUL -DCANTOR_GM
COMMON_cantor64gmt_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=64 -DCANTOR_GM -DCANTOR_GM_TRUNCATE
COMMON_cantor128gmt_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=128 -DCANTOR_GM -DCANTOR_GM_TRUNCATE
COMMON_cantor64clgmt_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=64 -DHAVE_PCLMUL -DCANTOR_GM -DCANTOR_GM_TRUNCATE
COMMON_cantor128clgmt_CFLAGS=-DCANTOR_BASE_FIELD_SIZE=128 -DHAVE_PCLMUL -DCANTOR_GM -DCANTOR_GM_TRUNCATE

# Some other variants, only barely tested.

# cat > /tmp/b <<EOF
# check_LTLIBRARIES += lib__VARIANT__.la
# lib__VARIANT___la_SOURCES = cantor.c
# lib__VARIANT___la_CFLAGS = $(AM_CFLAGS) $(COMMON___VARIANT___CFLAGS)
# check_PROGRAMS += __VARIANT__bench
# __VARIANT__bench_SOURCES=bench.c
# __VARIANT__bench_CFLAGS= $(AM_CFLAGS) $(COMMON___VARIANT___CFLAGS) -DENGINE_CANTOR
# __VARIANT__bench_LDADD=lib__VARIANT__.la -lgmp
# EOF
# for VARIANT in cantor{64,128}{,cl}{,gm,gmt} ; do sed -e s,__VARIANT__,$VARIANT,g /tmp/b ; done
# 

check_LTLIBRARIES=
check_PROGRAMS=

if GF2XFFT_HAVE_GF2X
lib_LTLIBRARIES += libgf2x-fft.la
libgf2x_fft_la_SOURCES = fake_fft.c

check_PROGRAMS += gf2x_tfftbench
gf2x_tfftbench_SOURCES=bench.c
gf2x_tfftbench_CFLAGS= $(AM_CFLAGS) -DENGINE_GF2X_TFFT
gf2x_tfftbench_LDADD=-lgf2x -lgmp

check_PROGRAMS += gf2x_tfftansbench
gf2x_tfftansbench_SOURCES=bench.c
gf2x_tfftansbench_CFLAGS= $(AM_CFLAGS) -DENGINE_GF2X_TFFT -DARTIFICIAL_NON_SPLIT_VERSION
gf2x_tfftansbench_LDADD=-lgf2x -lgmp
endif

check_LTLIBRARIES += libcantor64.la
libcantor64_la_SOURCES = cantor.c
libcantor64_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor64_CFLAGS)
check_PROGRAMS += cantor64bench
cantor64bench_SOURCES=bench.c
cantor64bench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor64_CFLAGS) -DENGINE_CANTOR
cantor64bench_LDADD=libcantor64.la -lgmp
check_LTLIBRARIES += libcantor64gm.la
libcantor64gm_la_SOURCES = cantor.c
libcantor64gm_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor64gm_CFLAGS)
check_PROGRAMS += cantor64gmbench
cantor64gmbench_SOURCES=bench.c
cantor64gmbench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor64gm_CFLAGS) -DENGINE_CANTOR
cantor64gmbench_LDADD=libcantor64gm.la -lgmp
check_LTLIBRARIES += libcantor64gmt.la
libcantor64gmt_la_SOURCES = cantor.c
libcantor64gmt_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor64gmt_CFLAGS)
check_PROGRAMS += cantor64gmtbench
cantor64gmtbench_SOURCES=bench.c
cantor64gmtbench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor64gmt_CFLAGS) -DENGINE_CANTOR
cantor64gmtbench_LDADD=libcantor64gmt.la -lgmp

if GF2XFFT_PCLMUL_SOURCES
check_LTLIBRARIES += libcantor64cl.la
libcantor64cl_la_SOURCES = cantor.c
libcantor64cl_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor64cl_CFLAGS)
check_PROGRAMS += cantor64clbench
cantor64clbench_SOURCES=bench.c
cantor64clbench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor64cl_CFLAGS) -DENGINE_CANTOR
cantor64clbench_LDADD=libcantor64cl.la -lgmp
check_LTLIBRARIES += libcantor64clgm.la
libcantor64clgm_la_SOURCES = cantor.c
libcantor64clgm_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor64clgm_CFLAGS)
check_PROGRAMS += cantor64clgmbench
cantor64clgmbench_SOURCES=bench.c
cantor64clgmbench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor64clgm_CFLAGS) -DENGINE_CANTOR
cantor64clgmbench_LDADD=libcantor64clgm.la -lgmp
check_LTLIBRARIES += libcantor64clgmt.la
libcantor64clgmt_la_SOURCES = cantor.c
libcantor64clgmt_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor64clgmt_CFLAGS)
check_PROGRAMS += cantor64clgmtbench
cantor64clgmtbench_SOURCES=bench.c
cantor64clgmtbench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor64clgmt_CFLAGS) -DENGINE_CANTOR
cantor64clgmtbench_LDADD=libcantor64clgmt.la -lgmp
endif

# check_LTLIBRARIES += libcantor128.la
libcantor128_la_SOURCES = cantor.c
libcantor128_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor128_CFLAGS)
check_PROGRAMS += cantor128bench
cantor128bench_SOURCES=bench.c
cantor128bench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor128_CFLAGS) -DENGINE_CANTOR
cantor128bench_LDADD=libcantor128.la -lgmp
check_LTLIBRARIES += libcantor128gm.la
libcantor128gm_la_SOURCES = cantor.c
libcantor128gm_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor128gm_CFLAGS)
check_PROGRAMS += cantor128gmbench
cantor128gmbench_SOURCES=bench.c
cantor128gmbench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor128gm_CFLAGS) -DENGINE_CANTOR
cantor128gmbench_LDADD=libcantor128gm.la -lgmp
check_LTLIBRARIES += libcantor128gmt.la
libcantor128gmt_la_SOURCES = cantor.c
libcantor128gmt_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor128gmt_CFLAGS)
check_PROGRAMS += cantor128gmtbench
cantor128gmtbench_SOURCES=bench.c
cantor128gmtbench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor128gmt_CFLAGS) -DENGINE_CANTOR
cantor128gmtbench_LDADD=libcantor128gmt.la -lgmp

if GF2XFFT_PCLMUL_SOURCES

check_LTLIBRARIES += libcantor128cl.la
libcantor128cl_la_SOURCES = cantor.c
libcantor128cl_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor128cl_CFLAGS)
check_PROGRAMS += cantor128clbench
cantor128clbench_SOURCES=bench.c
cantor128clbench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor128cl_CFLAGS) -DENGINE_CANTOR
cantor128clbench_LDADD=libcantor128cl.la -lgmp
check_LTLIBRARIES += libcantor128clnt.la
libcantor128clnt_la_SOURCES = cantor.c
libcantor128clnt_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor128clnt_CFLAGS)
check_PROGRAMS += cantor128clntbench
cantor128clntbench_SOURCES=bench.c
cantor128clntbench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor128clnt_CFLAGS) -DENGINE_CANTOR
cantor128clntbench_LDADD=libcantor128clnt.la -lgmp
check_LTLIBRARIES += libcantor128clgm.la
libcantor128clgm_la_SOURCES = cantor.c
libcantor128clgm_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor128clgm_CFLAGS)
check_PROGRAMS += cantor128clgmbench
cantor128clgmbench_SOURCES=bench.c
cantor128clgmbench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor128clgm_CFLAGS) -DENGINE_CANTOR
cantor128clgmbench_LDADD=libcantor128clgm.la -lgmp
check_LTLIBRARIES += libcantor128clgmt.la
libcantor128clgmt_la_SOURCES = cantor.c
libcantor128clgmt_la_CFLAGS = $(AM_CFLAGS) $(COMMON_cantor128clgmt_CFLAGS)
check_PROGRAMS += cantor128clgmtbench
cantor128clgmtbench_SOURCES=bench.c
cantor128clgmtbench_CFLAGS= $(AM_CFLAGS) $(COMMON_cantor128clgmt_CFLAGS) -DENGINE_CANTOR
cantor128clgmtbench_LDADD=libcantor128clgmt.la -lgmp

endif

AM_TESTS_ENVIRONMENT = \
    all_programs="$(check_PROGRAMS)"; export all_programs;	\
    all_sizes="10 100 1000 10000 100000"; export all_sizes;	\
    tests_location="$(builddir)"; export tests_location;

TESTS=./debug/check_cantor.sh
EXTRA_DIST=$(TESTS)
