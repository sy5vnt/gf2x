unset `locale | cut -d= -f1`
export LANG=C

for f in autoconf automake libtool ; do
    if [ -d $HOME/Packages/$m ] ; then
        export PATH=$HOME/Packages/$f/bin:$PATH
    fi
done
# Note: for libtool, we also have to add its aclocal search path to the
# automake aclocal search path (which is
# [automake_prefix]/share/aclocal/dirlist); this is done on all ci nodes.

# openbsd has wrappers which strictly require the AUTOCONF_VERSION and
# AUTOMAKE_VERSION variables be set. For most other nodes, this is
# irrelevant and ignored.
export AUTOCONF_VERSION=2.69
if type aclocal-1.15 > /dev/null 2>&1 ; then
    export AUTOMAKE_VERSION=1.15
elif type aclocal-1.14 > /dev/null 2>&1 ; then
    export AUTOMAKE_VERSION=1.14
elif type aclocal-1.13 > /dev/null 2>&1 ; then
    export AUTOMAKE_VERSION=1.13
elif type aclocal > /dev/null ; then
    :
else
    echo "automake (aclocal) not found" >&2
    exit 1
fi

