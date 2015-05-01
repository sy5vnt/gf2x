export LANG=C
export AUTOCONF_VERSION=2.69
export AUTOMAKE_VERSION=1.13
autoreconf -i
src="$PWD"
TMP=`mktemp -d /tmp/${BUILD_TAG}-XXXXXXX`
cd "$TMP"
if ! ($src/configure &amp;&amp; make &amp;&amp; make check) ; then
   echo "FAILED"
   cd "$src"
   rm -rf "$TMP"
   exit 1
fi
cd "$src"
rm -rf "$TMP"
