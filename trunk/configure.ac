dnl   
dnl	configure.ac
dnl   
dnl	Copyright (C) Enrique García Álvarez 2008 <kike + glkm @ eldemonionegro.com>
dnl	Copyright (C) Paolo Durante 	<shackan @ gmail.com>
dnl
dnl	configure.ac is free software
dnl   
dnl	You may redistribute it and/or modify it under the terms of the
dnl	GNU General Public License, as published by the Free Software
dnl	Foundation; either version 2 of the License, or (at your option)
dnl	any later version.
dnl
dnl	configure.ac is distributed in the hope that it will be useful,
dnl	but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
dnl	See the GNU General Public License for more details.
dnl
dnl	You should have received a copy of the GNU General Public License
dnl	along with configure.ac .  If not, write to:
dnl		The Free Software Foundation, Inc.,
dnl		51 Franklin Street, Fifth Floor
dnl		Boston, MA  02110-1301, USA.
dnl   

dnl Process this file with autoconf to produce a configure script.
################################################################################
#		Prelude.
################################################################################

AC_PREREQ(2.61)

#release versioning
AC_DEFUN([GENERIC_MAJOR_VERSION], [0])
AC_DEFUN([GENERIC_MINOR_VERSION], [5])
AC_DEFUN([GENERIC_MICRO_VERSION], [0])
AC_DEFUN([GENERIC_VERSION], [GENERIC_MAJOR_VERSION.GENERIC_MINOR_VERSION.GENERIC_MICRO_VERSION])

AC_INIT([dbusmm], [GENERIC_VERSION], [shackan@gmail.com])

#shared library versioning
GENERIC_LIBRARY_VERSION=1:0:0
#                        | | |
#                 +------+ | +---+
#                 |        |     |
#              current:revision:age
#                 |        |     |
#                 |        |     +- increment if interfaces have been added
#                 |        |        set to zero if interfaces have been removed
#                 |        |        or changed
#                 |        +- increment if source code has changed
#                 |           set to zero if current is incremented
#                 +- increment if interfaces have been added, removed or changed
AC_SUBST(GENERIC_LIBRARY_VERSION)

DBUS_REQUIRED_VERSION=0.60
DBUS_API_STABLE_VERSION=1.0.0
DBUS_THREADS_INIT_DEFAULT_VERSION=0.93
DBUS_RECURSIVE_MUTEX_VERSION=0.95

################################################################################
#		Checks for programs.
################################################################################

# DEPRECATED since autoconf 2.50 
# AM_INIT_AUTOMAKE([AC_PACKAGE_NAME], [AC_PACKAGE_VERSION])
AM_INIT_AUTOMAKE([gnu dist-bzip2 -Wall -Werror])

AC_CANONICAL_HOST
AC_SUBST(PACKAGE_VERSION)

AC_PROG_CC
AC_PROG_CXX
AC_LANG_CPLUSPLUS


CXX_FOR_BUILD=${CXX_FOR_BUILD-${CXX}}
AC_SUBST(CXX_FOR_BUILD)

PKG_PROG_PKG_CONFIG

# Doxygen Documentation
AC_ARG_ENABLE([doxygen-docs],
	      AS_HELP_STRING([--enable-doxygen-docs],
			     [build DOXYGEN documentation (requires Doxygen)]),
              [enable_doxygen_docs=$enableval],
	      [enable_doxygen_docs=no])
AC_PATH_PROG(DOXYGEN, doxygen, no)

AC_MSG_CHECKING([whether to build Doxygen documentation])
if test "$enable_doxygen_docs" = "auto" ; then
	enable_doxygen_docs=no
	AC_MSG_RESULT(no)
fi
if test "$enable_doxygen_docs" = "yes" ; then
	if test "$DOXYGEN" = "no"; then
		AC_MSG_ERROR([Building Doxygen docs explicitly required, but Doxygen not found])
	fi
	AC_MSG_RESULT(yes)
	dnl check if graphviz / dot is installed (used by doxygen)
	AC_CHECK_PROGS([DOT], [dot], [no])
	if test x$DOT = xno; then
	   	AC_MSG_WARN([graphviz / dot not found, documentation graphs will not be rebuilt])
	fi
fi
AM_CONDITIONAL(DBUS_DOXYGEN_DOCS_ENABLED, test "$enable_doxygen_docs" = "yes")

################################################################################
#		Checks for Internatinalization.
################################################################################


################################################################################
#		Checks for libraries.
################################################################################

PKG_CHECK_MODULES([dbus],
	          [dbus-1 >= $DBUS_REQUIRED_VERSION],
		  [],
		  [AC_MSG_ERROR([You need the DBus libraries (version 0.6 or better)]
		   	       [http://www.freedesktop.org/wiki/Software_2fdbus])] )
AC_SUBST(dbus_CFLAGS)
AC_SUBST(dbus_LIBS)


PKG_CHECK_EXISTS([dbus-1 < $DBUS_API_STABLE_VERSION],
	         [AC_DEFINE(DBUS_API_SUBJECT_TO_CHANGE,
		            [],
			    [unstable DBus])])

PKG_CHECK_EXISTS([dbus-1 >= $DBUS_THREADS_INIT_DEFAULT_VERSION],
	         [AC_DEFINE(DBUS_HAS_THREADS_INIT_DEFAULT,
			    [],
			    [dbus_threads_init_default (needs DBus >= 0.93)])])

PKG_CHECK_EXISTS([dbus-1 >= $DBUS_RECURSIVE_MUTEX_VERSION],
		 [AC_DEFINE(DBUS_HAS_RECURSIVE_MUTEX,
			    [],
			    [DBus supports recursive mutexes (needs DBus >= 0.95)])])


AC_ARG_ENABLE([glib],
	      AC_HELP_STRING([--enable-glib],
			     [enable glib integration]),
	      [enable_glib=$enableval],
	      [enable_glib=no]
)
if test "$enable_glib" = "yes" ; then
   	PKG_CHECK_MODULES([glib], [glib-2.0])
	AC_SUBST(glib_CFLAGS)
	AC_SUBST(glib_LIBS)
	AM_CONDITIONAL(ENABLE_GLIB, test 1 = 1)
else
	AM_CONDITIONAL(ENABLE_GLIB, test 0 = 1)
fi

#glib examples uses gtkmm to build a gui application. Althought 
AC_ARG_ENABLE([examples],
	      AC_HELP_STRING([--enable-examples],
			     [Building examples explicitly required, but gtkmm-2.4-dev not found (only glib example needs it)]),
	      [enable_examples=$enableval],
	      [enable_examples=no]
)
if test "$enable_examples" = "yes" ; then
	PKG_CHECK_MODULES([gtkmm], 
			  [gtkmm-2.4],
			  [AM_CONDITIONAL(HAVE_GTKMM, test 1 = 1)],
			  [AM_CONDITIONAL(HAVE_GTKMM, test 0 = 1)])
	AC_SUBST(gtkmm_CFLAGS)
	AC_SUBST(gtkmm_LIBS)
else
	AM_CONDITIONAL(HAVE_GTKMM, test 0 = 1)
fi

# xml needed by tools/xml2cpp and glib example.
AC_CHECK_LIB([expat],
	     [XML_ParserCreate_MM],
	     [AC_CHECK_HEADERS(expat.h, have_expat=true, have_expat=false)],
	     [have_expat=false])
if ! $have_expat; then
	AC_MSG_ERROR([You need the eXpat xml parser]
		     [http://expat.sourceforge.net/])
fi
xml_CFLAGS=
xml_LIBS=-lexpat
AC_SUBST(xml_CFLAGS)
AC_SUBST(xml_LIBS)


AC_CHECK_LIB([pthread], 
	     [pthread_create],
	     [AC_CHECK_HEADERS(pthread.h, have_pthread=true, have_pthread=false)],
	     [have_pthread=false])
AM_CONDITIONAL(HAVE_PTHREAD, test "$have_pthread" = "true")


################################################################################
#		Checks for header files.
################################################################################


################################################################################
#		Checks for typedefs, structures, and compiler characteristics.
################################################################################

AC_CONFIG_HEADERS([include/dbusmm/dbusmm_config.h])

AM_PROG_LIBTOOL

AC_ARG_ENABLE([debug],
	      AC_HELP_STRING([--enable-debug],
			     [enable debugging support]),
	      [enable_debug=$enableval],
	      [enable_debug=no]
)
if test "$enable_debug" = "yes" ; then
	CXXFLAGS="$CXXFLAGS -Wall -ggdb -O0 -DDEBUG"
else
	CXXFLAGS="$CXXFLAGS -Wall -O3"
fi


AC_MSG_CHECKING([whether $CXX supports symbol visibility])
vtest=`$CXX --help --verbose 2>&1 | grep fvisibility`
if test -n "$vtest"; then
	AC_MSG_RESULT(yes)
	AC_DEFINE(GCC_HASCLASSVISIBILITY, 1, [to enable hidden symbols])
	CXXFLAGS="-fvisibility=hidden"
else
	AC_MSG_RESULT(no)
fi 


# For the tools/, we need libdbusmm for the "build" architecture as well
AM_CONDITIONAL(CROSS_COMPILING, test "$cross_compiling" = "yes")
AC_ARG_WITH([build-libdbusmm],
	    AS_HELP_STRING([--with-build-libdbusmm],
			   [For cross compilation: path to libdbusmm which was compiled for the 'build' system.]),
           [BUILD_LIBDBUSMM_DIR=${withval}],
	   [BUILD_LIBDBUSMM_DIR="\$(top_builddir)"])
AC_SUBST(BUILD_LIBDBUSMM_DIR)


################################################################################
#		Checks for library functions.
################################################################################


################################################################################
#		Output files
################################################################################


AC_CONFIG_FILES([
	Makefile
	src/Makefile
	tools/Makefile
	data/Makefile
	docs/Makefile
	docs/reference/Doxyfile
	docs/reference/Makefile
	examples/Makefile
	examples/properties/Makefile
	examples/echo/Makefile
	examples/hal/Makefile
	examples/glib/Makefile
	dbusmm-1.0.pc
])

AC_OUTPUT
