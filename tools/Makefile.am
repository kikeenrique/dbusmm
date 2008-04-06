# hacky, but ...

CXX = $(CXX_FOR_BUILD)

AM_CPPFLAGS = \
	$(dbus_CFLAGS) \
	$(xml_CFLAGS) \
	-I$(top_srcdir)/include

if CROSS_COMPILING
        libdbusmm_1_0_la = $(BUILD_LIBDBUSMM_DIR)/src/libdbusmm-1.0.la
else
        libdbusmm_1_0_la = $(top_builddir)/src/libdbusmm-1.0.la
endif

bin_PROGRAMS = dbusmm-xml2cpp dbusmm-introspect

dbusmm_xml2cpp_SOURCES = xml.h xml.cpp xml2cpp.h xml2cpp.cpp
dbusmm_xml2cpp_LDADD = $(libdbusmm_1_0_la) $(xml_LIBS)

dbusmm_introspect_SOURCES = introspect.h introspect.cpp
dbusmm_introspect_LDADD = $(libdbusmm_1_0_la)

MAINTAINERCLEANFILES = \
	Makefile.in
