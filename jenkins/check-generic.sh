. "`dirname $0`"/common.sh
autoreconf -i
./configure $configure_extra
make
make check
if [ -f "`dirname $0`"/extra-"`basename $0`" ] ; then
    . "`dirname $0`"/extra-"`basename $0`"
fi
