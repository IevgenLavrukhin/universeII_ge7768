MODNAME  := universeII
SPECFILE := universeII-kmod.spec
SOURCES  := 99-universeII.rules gpl-2.0.txt kmodtool-universeII.sh
SRC      := $(addprefix ../driver/,universeII.c universeII.h vmeioctl.h vmic.h Makefile)

VERSION  := $(shell cat $(SPECFILE) | grep "^Version: " | sed 's/^Version: //')

rpm: SOURCES rpmbuild/SPECS/$(SPECFILE)
	cd rpmbuild; \
	rpmbuild --define "_topdir $$PWD" -bb --target=`uname -m` SPECS/$(SPECFILE)

clean:
	rm -rf rpmbuild


.PHONY: rpm clean rpmbuild SOURCES

#create the dirctory structure for rpmbuild
rpmbuild:
	mkdir -p rpmbuild/{BUILD,RPMS,SOURCES,SPECS,SRPMS}


#rules to collect all files in rpmbuild/SOURCES:
SOURCES: $(addprefix rpmbuild/SOURCES/,$(MODNAME)-$(VERSION).tar.bz2 $(SOURCES))

#create a tarball with the actual source code of the module
rpmbuild/SOURCES/$(MODNAME)-$(VERSION).tar.bz2 : $(SRC) | rpmbuild
	tar -cvf "$@" --transform="s&driver/&$(MODNAME)-$(VERSION)/&" $^

#copy all the other files from here
rpmbuild/SOURCES/% : % | rpmbuild
	cp $< $@


#create specfile to rpmbuild/SPECS
rpmbuild/SPECS/$(SPECFILE) : $(SPECFILE) | rpmbuild
	cp $< $@


