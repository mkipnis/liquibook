SUBDIRS = python

EXTRA_DIST = \
	license.txt \
	README.md \
	autogen.sh


dist-hook:
	mkdir -p $(distdir)/SWIG
	cp -p ./*.i $(distdir)/SWIG
