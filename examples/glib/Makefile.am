EXTRA_DIST = 

AM_CPPFLAGS = -I$(top_srcdir)/include $(gtkmm_CFLAGS) -I$(top_srcdir)/tools

if HAVE_GTKMM
noinst_PROGRAMS = dbus-browser
endif

dbus_browser_SOURCES = dbus-glue.h dbus-browser.h dbus-browser.cpp $(top_srcdir)/tools/xml.cpp
dbus_browser_LDADD = $(top_builddir)/src/libdbusmm-1.0.la $(gtkmm_LIBS) 
##$(top_builddir)/tools/xml.o

dbus-glue.h: $(top_srcdir)/data/org.freedesktop.DBus.xml
	$(top_builddir)/tools/dbusmm-xml2cpp $^ --proxy=$@

BUILT_SOURCES = dbus-glue.h
CLEANFILES = $(BUILT_SOURCES)

dist-hook:
	cd $(distdir); rm -f $(BUILT_SOURCES)

MAINTAINERCLEANFILES = \
	Makefile.in
