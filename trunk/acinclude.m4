
AC_DEFUN([SSE2_EXAMPLE],[
#include <emmintrin.h>
__v2di x;
int main() {}
])

# Check whether we need some flag such as -msse2 in order to enable sse-2
# support
AC_DEFUN([CHECK_SSE2_SUPPORT],[
 ac_save_CFLAGS=$CFLAGS
 AC_CACHE_CHECK([whether $CC can compile sse-2 code], [gf2x_cv_cc_supports_sse2],[
  gf2x_cv_cc_supports_sse2=no
  if test "x${enable_sse2}" = xno ; then
   echo $ECHO_N "explicitly disabled, "
  else
   AC_COMPILE_IFELSE([SSE2_EXAMPLE()],[
    gf2x_cv_cc_supports_sse2=yes
   ],[
    CFLAGS="$ac_save_CFLAGS -msse2"
    AC_COMPILE_IFELSE([SSE2_EXAMPLE()],[
     gf2x_cv_cc_supports_sse2="requires -msse2"
    ],[
     gf2x_cv_cc_supports_sse2=no
    ])
   ])
  fi
 ])
 ac_save_CPPFLAGS=$CPPFLAGS
 if test "$gf2x_cv_cc_supports_sse2" = "requires -msse2" ;then
  # Tweaking CFLAGS is often not enough.
  AC_CACHE_CHECK([whether -msse2 is also needed by the preprocessor],
   [gf2x_cv_cpp_requires_msse2_flag],[
   AC_PREPROC_IFELSE([SSE2_EXAMPLE()],[
    gf2x_cv_cpp_requires_msse2_flag=no
   ],[
    CPPFLAGS="$ac_save_CPPFLAGS -msse2"
    AC_PREPROC_IFELSE([SSE2_EXAMPLE()],[
    gf2x_cv_cpp_requires_msse2_flag=yes
    ],[
     AC_MSG_ERROR([Sorry, the preprocessor can't parse sse-2 !])
    ])
   ])
  ])
 fi
 CFLAGS=$ac_save_CFLAGS
 CPPFLAGS=$ac_save_CPPFLAGS
 if test "$gf2x_cv_cc_supports_sse2" = "requires -msse2" ;then
  CFLAGS="$CFLAGS -msse2"
 fi
 if test "$gf2x_cv_cpp_requires_msse2_flag" = "yes" ; then
  CPPFLAGS="$CPPFLAGS -msse2"
 fi
 if test "$gf2x_cv_cc_supports_sse2" != "no" ;then
  AC_DEFINE([HAVE_SSE2_SUPPORT],[1],[Define if sse-2 code as present in the source tree is supported by the compiler])
 fi
])# CHECK_SSE2_SUPPORT



AC_DEFUN([AC_COMPILE_WARNINGS], [
AC_MSG_CHECKING([warning verbosity option])
  AC_REQUIRE([AC_PROG_CC])
  AC_REQUIRE([AC_PROG_CXX])

  AC_ARG_WITH([compile-warnings],
              AS_HELP_STRING([--without-compile-warnings],
                             [Disable warning verbosity]),
              [ac_compile_warnings_on="$withval"],
              [ac_compile_warnings_on=""])

  if test x"$ac_compile_warnings_on" = xno
  then
    ac_compile_warnings_msg=no
  else
    if test -n "$CXX"
    then
      if test "$GXX" = "yes"
      then
        ac_compile_warnings_opt='-Wall -W'
      fi
      CXXFLAGS="$CXXFLAGS $ac_compile_warnings_opt"
      ac_compile_warnings_msg="$ac_compile_warnings_opt for C++"
    fi

  if test -n "$CC"
  then
    if test "$GCC" = "yes"
    then
      ac_compile_warnings_opt='-Wall -W'
    fi
    CFLAGS="$CFLAGS $ac_compile_warnings_opt"
    ac_compile_warnings_msg="$ac_compile_warnings_msg $ac_compile_warnings_opt for C"
  fi
  fi
  AC_MSG_RESULT([$ac_compile_warnings_msg])
  unset ac_compile_warnings_msg
  unset ac_compile_warnings_opt
])

