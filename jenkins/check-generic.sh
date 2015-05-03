unset `locale | cut -d= -f1`
export LANG=C
export AUTOCONF_VERSION=2.69
if type aclocal-1.15 > /dev/null ; then
    export AUTOMAKE_VERSION=1.15
elif type aclocal-1.14 > /dev/null ; then
    export AUTOMAKE_VERSION=1.14
elif type aclocal-1.13 > /dev/null ; then
    export AUTOMAKE_VERSION=1.13
elif type aclocal > /dev/null ; then
    :
else
    echo "automake (aclocal) not found" >&2
    exit 1
fi
autoreconf -i
./configure
make
make check
