EXTRA_DIST = README echo-introspect.xml

AM_CPPFLAGS = -I$(top_srcdir)/include

noinst_PROGRAMS = echo-server

echo_server_SOURCES = echo-server-glue.h echo-server.h echo-server.cpp
echo_server_LDADD = $(top_builddir)/src/libdbusmm-1.0.la

echo-server-glue.h: echo-introspect.xml
	$(top_builddir)/tools/dbusmm-xml2cpp $^ --adaptor=$@

if HAVE_PTHREAD
noinst_PROGRAMS += echo-client-mt
endif

echo_client_mt_SOURCES = echo-client-glue.h echo-client.h echo-client.cpp
echo_client_mt_LDADD = $(top_builddir)/src/libdbusmm-1.0.la -lpthread

echo-client-glue.h: echo-introspect.xml
	$(top_builddir)/tools/dbusmm-xml2cpp $^ --proxy=$@

BUILT_SOURCES = echo-server-glue.h echo-client-glue.h
CLEANFILES = $(BUILT_SOURCES)

dist-hook:
	cd $(distdir); rm -f $(BUILT_SOURCES)

MAINTAINERCLEANFILES = \
	Makefile.in
