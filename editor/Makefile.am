NULL=
noinst_PROGRAMS=\
	ccc-editor \
	$(NULL)

ccc_editor_SOURCES=\
	ce-canvas-tree-model.c \
	ce-canvas-tree-model.h \
	ce-main.c \
	ce-window.c \
	ce-window.h \
	config.h \
	demo-canvas.c \
	demo-canvas.h \
	gtk-helpers.c \
	gtk-helpers.h \
	herzi-main-window.c \
	herzi-main-window.h \
	$(NULL)
ccc_editor_LDADD=\
	$(CCC_LIBS) \
	../ccc/libccc-$(MILESTONE).la \
	$(NULL)

AM_CPPFLAGS=\
	$(CCC_CFLAGS) \
	-I$(top_srcdir) \
	-I$(top_srcdir)/ccc \
	$(NULL)
