if DBUS_DOXYGEN_DOCS_ENABLED

DOXYGEN_CONFIGFILE = Doxyfile
DOXYGEN_CONFIGFILE_SOURCE = Doxyfile.in
HTML_TEMPLATE_FILES = dbusmm.css dbusmm-header.html

EXTRA_DIST = $(DOXYGEN_CONFIGFILE_SOURCE) \
	     $(HTML_TEMPLATE_FILES) \
	     cairomm_doxygen_tags

dbusmm_doxygen_tags : $(index_html)

index_html = html/index.html

$(index_html): $(DOXYGEN_CONFIGFILE) #// $(HTML_TEMPLATE_FILES) $(wildcard $(top_srcdir)/include/*.h) $(wildcard $(top_srcdir)/src/*.cpp)
	-rm -rf html
	doxygen $(DOXYGEN_CONFIGFILE) 2> doxygen-warnings.txt \
	  | tee doxygen-output.txt && cat doxygen-warnings.txt

DBUSMM_DOC_TARNAME=$(PACKAGE)-doc.tar.gz

doc-tarball : $(DBUSMM_DOC_TARNAME)

$(DBUSMM_DOC_TARNAME): $(index_html)
	tar cf - html | gzip -c --best > $@

referencedir = $(datadir)/doc/libdbusmm-1.0/reference/html

#$(<D) -> Automatic variable
#The directory part and the file-within-directory part of the first prerequisite.
#Automake complains about no-posix variable so substituion is done by hand
install-reference: $(index_html)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(referencedir)
#	@dir='$(<D)'; for p in `ls $$dir/*.html $$dir/*.css $$dir/*.png $$dir/*.jpg $$dir/*.map $$dir/*.md5 $$dir/*.dot` ; do \
#
	for p in `ls html/*.html html/*.css html/*.png html/*.map html/*.md5 html/*.dot` ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$p $(DESTDIR)$(referencedir)/$$f"; \
	  $(INSTALL_DATA) $$p $(DESTDIR)$(referencedir)/$$f; \
	done

uninstall-reference: $(index_html)
	@$(NORMAL_UNINSTALL)
#	@dir='$(<D)'; for p in `ls $$dir/*.html $$dir/*.css $$dir/*.png $$dir/*.jpg $$dir/*.map $$dir/*.md5 $$dir/*.dot` ; do \
#
	for p in `ls html/*.html html/*.css html/*.png html/*.map html/*.md5 html/*.dot` ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(referencedir)/$$f"; \
	  rm -f $(DESTDIR)$(referencedir)/$$f; \
	done

DOXYGEN_REPORTS = doxygen-output.txt doxygen-warnings.txt undocumented.txt

doc-clean:
	-rm -rf html
	-rm -f dbusmm_doxygen_tags
	-rm -f $(DOXYGEN_REPORTS)

install-data-local: install-reference

uninstall-local: uninstall-reference

all-local: $(index_html)

maintainer-clean-local: doc-clean
distclean-local: doc-clean

dist-hook: $(index_html)
	cp -R html $(distdir)

CLEANFILES = html/*.html html/*.css html/*.png html/*.gif
DISTCLEANFILES = $(DOXYGEN_CONFIGFILE) $(DOXYGEN_REPORTS)

.PHONY: doc-clean install-reference uninstall-reference

endif

MAINTAINERCLEANFILES = \
	Makefile.in
