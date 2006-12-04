# herzi-gprof.m4
#
# File that contains autoconf macros that add --enable-gprof and
# --disable-gprof

dnl HERZI_PROG_GPROF
AC_DEFUN([HERZI_PROG_GPROF],[
		AC_MSG_CHECKING(if using gprof)
		AC_ARG_ENABLE(gprof,[  --enable-gprof          Enable gprof (default=off)],
			      ENABLE_GPROF="$enableval",
			      ENABLE_GPROF="no")
		if test "x$ENABLE_GPROF" = "xyes"; then
			CFLAGS="-g -pg $CFLAGS"
			LDFLAGS="-pg $LDFLAGS"
		fi
		AC_MSG_RESULT($ENABLE_GPROF)
		AC_SUBST(ENABLE_GPROF)
])

