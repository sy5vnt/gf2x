source "`dirname $0`"/common.sh
autoreconf -i
./configure
make
make tune-lowlevel
make tune-toom
