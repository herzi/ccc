if HAVE_CHECK
TESTS=\
	dummy-test \
	m-ccc
noinst_PROGRAMS=\
	$(TESTS)

m_ccc_SOURCES=\
	m-ccc.c \
	m-ccc.h \
	s-text.c \
	t-text-utf8-editing.c \
	glib-helpers.h \
	gtk-helpers.c \
	gtk-helpers.h \
	$(NULL)
m_ccc_LDADD=\
	$(CCC_LIBS) \
	$(CHECK_LIBS) \
	../ccc/libccc-0.1.la
AM_CPPFLAGS=\
	$(CCC_CFLAGS) \
	$(NULL)
endif
