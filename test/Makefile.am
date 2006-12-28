if HAVE_CHECK
TESTS=\
	dummy-test \
	m-ccc
noinst_PROGRAMS=\
	$(TESTS)

m_ccc_SOURCES=\
	cc-test-view.c \
	cc-test-view.h \
	m-ccc.c \
	m-ccc.h \
	s-item.h \
	s-item.c \
	s-text.c \
	t-item-distance.c \
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
