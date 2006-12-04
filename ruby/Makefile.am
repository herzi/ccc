NULL=
ccc_so_SOURCES=\
	ccc.c \
	$(NULL)
ccc_so_OBJECTS=$(ccc_so_SOURCES:.c=.o)

RUBY_MODULES=

if WITH_RUBY
RUBY_MODULES+=ccc.so

module_SCRIPTS=ccc.rb
moduledir=$(RUBY_LIBDIR)
endif

AM_CPPFLAGS=\
	$(RUBY_CFLAGS) \
	$(CCC_CFLAGS) \
	-I$(top_srcdir) \
	-I$(top_srcdir)/ccc \
	$(NULL)

all: $(RUBY_MODULES)

ccc.so: $(ccc_so_OBJECTS)
	$(CC) -shared -o $@ $^ $(AM_CPPFLAGS)

%.o: %.c
	$(CC) -c -fPIC -o $@ $(AM_CPPFLAGS) $<

EXTRA_DIST=ccc.rb \
	   $(ccc_so_SOURCES) \
	   $(NULL)
CLEANFILES=\
	ccc.so \
	$(ccc_so_OBJECTS) \
	$(NULL)
