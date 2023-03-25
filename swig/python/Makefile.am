CLEANFILES = liquibook/liquibook_wrap.cpp liquibook/liquibook.py .build-stamp

BUILT_SOURCES = liquibook/liquibook_wrap.cpp liquibook/liquibook.py 

if HAVE_PYTHON
if BUILD_PYTHON

all-local: .build-stamp

.build-stamp: liquibook/liquibook_wrap.cpp liquibook/liquibook.py  setup.py
	CXXFLAGS="$(CXXFLAGS) $(CXXWARNINGFLAGS)" CC="$(CC)" CXX="$(CXX)" $(PYTHON) setup.py build
	touch .build-stamp

check-local: .build-stamp
	$(PYTHON) setup.py test

install-exec-local: .build-stamp
	$(PYTHON) setup.py install

wheel: .build-stamp
	$(PYTHON) setup.py bdist_wheel

clean-local:
	rm -rf build

endif
endif

liquibook/liquibook_wrap.cpp liquibook/liquibook.py: ../*.i
	$(SWIG) -python -c++ -modern -outdir liquibook \
            -o liquibook/liquibook_wrap.cpp ../liquibook.i

dist-hook:
	mkdir -p $(distdir)/examples
	cp ./examples/*.py $(distdir)/examples

EXTRA_DIST = README.txt setup.py liquibook/__init__.py $(BUILT_SOURCES)
