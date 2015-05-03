export PATH=$HOME/Packages/autoconf-2.69/bin:$PATH
export PATH=$HOME/Packages/automake-1.15/bin:$PATH
# we also have to add libtool's aclocal search path to the automake
# aclocal search path (which is [automake_prefix]/share/aclocal/dirlist)
export PATH=$HOME/Packages/libtool-2.4.6/bin:$PATH
"`dirname $0`"/check-generic.sh
