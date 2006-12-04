# herzi-ruby.m4
#
# M4 macros to support building ruby modules with autoconf

dnl HERZI_RUBY_PRIV_CONFIG([VARNAME], [variable])
dnl
dnl Get the value of the rbconfig variable $2

AC_DEFUN([HERZI_RUBY_PRIV_CONFIG],[
	AC_MSG_CHECKING([for ruby configuration parameter "$2"])
	$1=`$RUBY -rrbconfig -e 'print Config::CONFIG[["$2"]]'`
	AC_SUBST($1)
	AC_MSG_RESULT($$1)
])

dnl HERZI_PROG_RUBY([action if succ],[action if fail])
dnl
dnl Checks for several aspects necessary to build ruby modules with an autotool
dnl toolchain. Sets RUBY to the name of the interpreter as well as RUBY_CFLAGS
dnl and RUBY_LIBS (just the same way PKG_CHECK_MODULES would do)

AC_DEFUN([HERZI_PROG_RUBY],[
	AC_REQUIRE([HERZI_PACKAGE_PREFIX])
	AC_CHECK_PROGS(RUBY, [ruby ruby1.8 ruby1.6],[herzi-ruby-failed])

	if test "x$RUBY" = "xherzi-ruby-failed"; then
		ifelse([$2], , [AC_MSG_ERROR(dnl
[No ruby installation found, please install ruby from your distribution or from
http://www.ruby-lang.org/])], [$2])
	else
		ifelse([$1], , [true], [$1])

	HERZI_RUBY_PRIV_CONFIG(RUBY_ARCHDIR,archdir)
	HERZI_RUBY_PRIV_CONFIG(RUBY_VERSION,ruby_version)
	HERZI_RUBY_PRIV_CONFIG(RUBY_LIBS,LIBRUBYARG)
	
	RUBY_LIBDIR="${PACKAGE_PREFIX}/lib/ruby/$RUBY_VERSION"
	AC_SUBST(RUBY_LIBDIR)
	
	RUBY_CFLAGS="-I$RUBY_ARCHDIR"
	AC_SUBST(RUBY_CFLAGS)
	
	HERZI_CHECK_HEADER([ruby.h],
			   [ifelse([$1], , [true], [$1])],
			   [ifelse([$2], , [AC_MSG_ERROR([Please install ruby-dev])], [$2])],
			   [],[$RUBY_CFLAGS])
	fi
])

dnl HERZI_RUBY_ARCHDIR
dnl
dnl Set RUBY_TARGET_ARCHDIR to a correct value matching to the specified prefix, issue
dnl a warning if ruby won't find it. Will even work if specified after a
dnl conditional HERZI_PROG_RUBY

AC_DEFUN([HERZI_RUBY_ARCHDIR],[
	if test "x$RUBY" != "xherzi-ruby-failed"; then
		herzi_ruby_archdir=`$RUBY -rrbconfig -e 'print Config::CONFIG[[\"archdir\"]]'`
	fi
])
