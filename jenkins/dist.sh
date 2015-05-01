export LANG=C
export AUTOCONF_VERSION=2.69
export AUTOMAKE_VERSION=1.13
autoreconf -i
src="$PWD"
TMP=`mktemp -d /tmp/${BUILD_TAG}-XXXXXXX`
if ! (cd "$TMP" ; $src/configure && make dist) ; then
   echo "FAILED"
   rm -rf "$TMP"
   exit 1
fi
version=$(grep AC_INIT configure.ac | perl -ne '/(\d+(?:\.\d+)+)/ && print "$1\n";')
cd "$TMP"
tar xzf gf2x-$version.tar.gz
cd gf2x-$version
if ! (./configure && make && make check) ; then
   echo "FAILED"
   cd "$src"
   rm -rf "$TMP"
   exit 1
fi
cd "$src"
rm -rf "$TMP"
