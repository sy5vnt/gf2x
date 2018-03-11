. "`dirname $0`"/common.sh
autoreconf -i
src="$PWD"
TMP=`mktemp -d /tmp/${BUILD_TAG}-XXXXXXX`
cleanup() { rm -rf "$TMP" ; }
trap cleanup EXIT

if ! (cd "$TMP" ; $src/configure $configure_extra && make dist) ; then
   echo "FAILED"
   exit 1
fi
version=$(grep AC_INIT configure.ac | perl -ne '/(\d+(?:\.\d+)+)/ && print "$1\n";')
cd "$TMP"
tar xzf gf2x-$version.tar.gz
cd gf2x-$version
if ! (./configure $configure_extra && make && make check) ; then
   echo "FAILED"
   cd "$src"
   exit 1
fi
cd "$src"
