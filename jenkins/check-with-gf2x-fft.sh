if [ -f Makefile ] ; then make distclean ; fi
if [ -f gf2x-fft/Makefile ] ; then make -C gf2x-fft distclean ; fi
. "`dirname $0`"/check-generic.sh
[ -f gf2x-fft/Makefile ]
