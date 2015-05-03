unset `locale | cut -d= -f1`
export LANG=C
export AUTOCONF_VERSION=2.69
export AUTOMAKE_VERSION=1.13
autoreconf -i
./configure
make
make check
