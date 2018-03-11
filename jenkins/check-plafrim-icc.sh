
if ! type -p module && [ -f /etc/profile.d/modules.sh ] ; then
    . /etc/profile.d/modules.sh
fi

module load compiler/gcc
module load compiler/intel/64/2018.0.015

. "`dirname $0`"/dist.sh

