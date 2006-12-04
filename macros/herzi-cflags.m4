# herzi-cflags.m4
#
# File that contains autoconf macros that perfom checks with modified CFLAGS
# and CPPFLAGS

dnl HERZI_CHECK_HEADER([header.h],[action if succ],[action if fail],[include],[extra_flags])
AC_DEFUN([HERZI_CHECK_HEADER],[
	HERZI_SAVE_CFLAGS="$CFLAGS"
	HERZI_SAVE_CPPFLAGS="$CFLAGS"
	CFLAGS="$CFLAGS $5"
	CPPFLAGS="$CPPFLAGS $5"

	AC_CHECK_HEADER([$1],[$2],[$3],[$4])
	
	CFLAGS="$HERZI_SAVE_CFLAGS"
	CPPFLAGS="$HERZI_SAVE_CPPFLAGS"
])

dnl HERZI_TRY_COMPILE([header.h],[action if succ],[action if fail],[include],[extra_flags])
AC_DEFUN([HERZI_TRY_COMPILE],[
	HERZI_SAVE_CFLAGS="$CFLAGS"
	HERZI_SAVE_CPPFLAGS="$CFLAGS"
	CFLAGS="$CFLAGS $6"
	CPPFLAGS="$CPPFLAGS $6"

	AC_TRY_COMPILE([$1],[$2],[$3],[$4],[$5])
	
	CFLAGS="$HERZI_SAVE_CFLAGS"
	CPPFLAGS="$HERZI_SAVE_CPPFLAGS"
])

dnl HERZI_CHECK_CFLAGS("new cflags to try")
AC_DEFUN([HERZI_CHECK_CFLAGS],[
	HERZI_CFLAGS=""

	AC_CHECK_PROGS(XARGS,[xargs],no)
	if test $XARGS = no; then
		AC_MSG_ERROR([Couldn't find xargs, please install xargs])
	fi

	for option in `echo $1 | $XARGS echo`; do
		AC_MSG_CHECKING([whether $CC understands $option])
		HERZI_TRY_COMPILE([],[],has_option=yes,has_option=no,[],[$option])
		
		if test $has_option = yes; then
		    HERZI_CFLAGS="$HERZI_CFLAGS $option"
		fi
		AC_MSG_RESULT($has_option)
	done

	CFLAGS="$CFLAGS $HERZI_CFLAGS"
])

dnl HERZI_CHECK_DEVELOP_CFLAGS
AC_DEFUN([HERZI_CHECK_DEVELOP_CFLAGS],[
	HERZI_CHECK_CFLAGS("-Wall -Wno-uninitialized \
			    -Wchar-subscripts -Wmissing-declarations -Wmissing-prototypes \
			    -Wnested-externs -Wpointer-arith \
			    -Wcast-align -Wsign-compare \
			    -Wno-strict-aliasing -Wnested-externs -Wpointer-arith \
			    -Werror-implicit-function-declaration -Wswitch -g")
])

