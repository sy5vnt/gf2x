. "`dirname $0`"/common.sh
autoreconf -i
./configure
make
make check
