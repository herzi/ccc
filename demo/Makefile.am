NULL=
noinst_PROGRAMS=ccc-demo

ccc_demo_SOURCES=\
	camera.c \
	credits.c \
	crossing.c \
	crossing.h \
	demo-canvas.c \
	demo-canvas.h \
	demo-page.c \
	demo-page.h \
	demo-polygon.c \
	demo-polygon.h \
	demo-window.c \
	demo-window.h \
	fifteen.c \
	fifteen.h \
	fifteen-grid.c \
	fifteen-grid.h \
	fifteen-item.c \
	fifteen-item.h \
	herzi-enum-combo.c \
	herzi-enum-combo.h \
	herzi-enum-model.c \
	herzi-enum-model.h \
	herzi-properties.c \
	herzi-properties.h \
	herzi-properties-group.c \
	herzi-properties-group.h \
	line.c \
	line.h \
	main.c \
	main.h \
	pixbuf-demo.c \
	printer-demo.c \
	planets.c \
	planets.h \
	text-demo.c \
	tree-integration.c \
	zoom-and-scroll.c \
	zoom-and-scroll.h \
	$(NULL)
ccc_demo_LDADD=\
	$(CCC_LIBS) \
	$(DEMO_LIBS) \
	$(top_builddir)/ccc/libccc-0.1.la \
	$(NULL)

AM_CPPFLAGS=\
	$(CCC_CFLAGS) \
	$(DEMO_CFLAGS) \
	-I$(top_srcdir) \
	-I$(top_srcdir)/ccc \
	$(NULL)

