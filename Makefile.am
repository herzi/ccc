NULL=
all_time_subdirs=\
	cdebug \
	ccc \
	demo \
	doc \
	test \
	po \
	editor \
	$(NULL)
SUBDIRS=\
	$(all_time_subdirs) \
	$(NULL)

if WITH_MONO
SUBDIRS+=csharp
endif

if WITH_RUBY
SUBDIRS+=ruby
endif

if WITH_PYTHON
SUBDIRS+=python
endif

DIST_SUBDIRS=\
	$(all_time_subdirs) \
	python \
	ruby \
	$(NULL)

pc_DATA=ccc-$(MILESTONE).pc
pcdir=$(libdir)/pkgconfig

%-$(MILESTONE).pc: %.pc
	cp $< $@

INTLTOOL_TEMPLATES=\
	intltool-extract.in \
	intltool-merge.in \
	intltool-update.in \
	$(NULL)

EXTRA_DIST=\
	ccc.pc.in \
	$(INTLTOOL_TEMPLATES) \
	$(NULL)
CLEANFILES=\
	$(pc_DATA) \
	$(INTLTOOL_TEMPLATES:.in=) \
	$(NULL)

