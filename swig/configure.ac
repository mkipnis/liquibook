# Process this file with autoconf to produce a configure script.
AC_INIT([liquibook-swig], [0.0.1],
        [mike.kipnis@gmail.com],
        [liquibook-swig])
AC_PREREQ(2.50)
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([foreign])

# check target
AC_MSG_CHECKING([system])
target=`uname`
AC_MSG_RESULT([$target])

# check compiler
AC_LANG([C++])

# check for tools
AC_PATH_PROG([SWIG], [swig])
if test "x$SWIG" != x; then
	SWIG_VERSION=`swig -version 2>&1|grep Version|cut -d" " -f3`
	SWIG_MAJOR=${SWIG_VERSION%%.*}
	if test ${SWIG_MAJOR} = "2"; then
		AC_MSG_WARN([You have SWIG $SWIG_VERSION installed, but at least SWIG 3.0.1 is recommended. Some features may not work. ])
		#SWIG=
	fi
fi

AC_PATH_PROG([PYTHON], [python3 python])
AM_CONDITIONAL(HAVE_PYTHON, test "x${PYTHON}" != "x")
AC_ARG_ENABLE([python],
              AS_HELP_STRING([--disable-python],
                             [If disabled, the Python module
                              will not be built]),
              [build_python=$enableval],
              [build_python=yes])
AM_CONDITIONAL(BUILD_PYTHON, test "$build_python" != "no")

# flags

case "$target" in
Darwin)
    AC_SUBST([SHARED_LIB],[${SHARED_LIB='-dynamiclib'}])
	AC_SUBST([SHARED_LIB_EXTENSION],[${SHARED_LIB_EXTENSION='dylib'}]);;
*)
    AC_SUBST([SHARED_LIB],[${SHARED_LIB='-shared'}])
	AC_SUBST([SHARED_LIB_EXTENSION],[${SHARED_LIB_EXTENSION='so'}]);;
esac


# done, output the configured files
AC_CONFIG_FILES([
    Makefile
    python/Makefile
    python/setup.py
    ])
AC_OUTPUT
