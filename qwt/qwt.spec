#-*- rpm-spec -*- ###############################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
#################################################################

# rpm spec file template for Qwt.  
#
# Qwt doesn't distribute binary packages as there are too many 
# distributions and Qt options. If you would like to have Qwt rpm
# packages, this spec file template will help you to build them.
# It was tested on:
#    Mandrake- 8.2/9.1/10.0
#    Red Hat- 8.0
#    SuSE- 9.0
#
# 1) Set QTDIR to point to the Qt release you want to build Qwt for.
#
# 2) The spec file tries to autodetect if a threaded Qt-library is installed.
#    If a threaded version is not available, it tries to build against the
#    non-threaded Qt-library.
#    If you need C++-exceptions, %define use_exceptions 1
#    If you need the man pages, %define use_man 1
#    If you need to change any other option in the pro-files un-tar the Qwt
#    package, edit the pro files and tar it again.
#
# 3) The spec file builds a qwt and a qwt-devel package. The qwt-devel
#    package includes qwt-examples. If you don't like to install the
#    examples remove the line '%doc examples' in the %files section. 
#
# 4) Each distribution has a default RPM-BUILD-TREE. 
#
#       - On Mandrake, it is /usr/src/RPM
#       - On SuSE, it is /usr/src/packages
#       - On Red Hat, it is /usr/src/redhat
#
#    You need write access to the RPM-BUILD-TREE. However, a regular user
#    can specify their own build area with the topdir variable in
#    ~/.rpmmacros. Please see:
#
#        http://www-106.ibm.com/developerworks/library/l-rpm2/
#
#    At this point, you have two choices:
#
#    a) Make sure the correct version of the spec file is in the
#       tar file, then run:
#
#               rpm -ta qwt-4.2.0.tar.bz2
#
#       or:
#
#               rpmbuild -ta qwt-4.2.0.tar.bz2
#
#       Note: You may just want to try this option to see if it works
#       "out of the box." If it doesn't, you may need to change the spec
#       file and/or try the next option.
#
#    b) Copy the spec file to RPM-BUILD-TREE/SPECS and the source file
#       qwt-4.2.0.tar.bz2 to RPM-BUILD-TREE/SOURCES, then run:
#
#              rpm -ba --clean RPM-BUILD-TREE/SPECS/qwt.spec
#
#       or:
#
#              rpmbuild -ba --clean RPM-BUILD-TREE/SPECS/qwt.spec
#
#
# 7) You find the following packages:
#	RPM-BUILD-TREE/RPMS/*/qwt-4.2.0-1.*.rpm
#       RPM-BUILD-TREE/RPMS/*/qwt-devel-4.2.0-1.*.rpm
#       RPM-BUILD-TREE/SRPMS/qwt-4.2.0-1.src.rpm
#    where * depends on your processor and distribution.


#define use_exceptions	1, if you want to enable exceptions
%define use_exceptions  0
#define use_man		1, if want to install the man pages
%define use_man		0

%define name    qwt
%define version 5.0.0rc0
%define release 1
%define qtdir   %(echo $QTDIR)

%{expand:%define buildForSuSE %(if [ -e /etc/SuSE-release ]; then echo 1; else echo 0; fi)}

Summary:	Qt Widgets for Technical applications (Qwt)
Name:		%{name}
Version:	%{version}
Release:	%{release}
License:	Qwt (LGPL, but allowing static linking to proprietary programs)
URL:		http://sourceforge.net/projects/qwt
Group:		System/Libraries
Source:		%{name}-%{version}.tar.bz2
BuildRoot:	%{_tmppath}/%{name}-buildroot

%description
Qwt is an extension to the Qt GUI library from Troll Tech AS.  The Qwt library
contains widgets and components which are primarily useful for technical and
scientifical purposes.  It includes a 2-D plotting widget, different kinds of
sliders, and much more.

%package devel
Summary:	Qt Widgets for Technical applications (Qwt)
Group:		Development/C++

%description devel
Qwt is an extension to the Qt GUI library from Troll Tech AS.  The Qwt library
contains widgets and components which are primarily useful for technical and
scientifical purposes.  It includes a 2-D plotting widget, different kinds of
sliders, and much more.  This package contains the header files, HTML and MAN
documentation and all examples.

The Qwt license is based on the LGPL, with exceptions to allow static linking
to closed source programs. Modifications of the Qwt library fall under the
LGPL and use of the Qwt library has to be acknowledged.

%prep
%setup -n %{name}-%{version}
# zap CVS stuff, in case of a snapshot
find . -name CVS -o -name .cvsignore | xargs rm -Rf

# check for a threaded qt library and if not found,
# modify the *.pro files to fall back on a non-threaded 
# Qt library, if found.
if [ ! -e $QTDIR/lib/libqt-mt.so -a -e $QTDIR/lib/libqt.so ]; then
    perl -e "s|thread||g" -pi  `find . -name "*.pro"`
fi

%if %use_exceptions
find . -name "*.pro" | perl -e "s|-fno-exceptions||g" -pi
perl -e "s|-fno-exceptions||g" -pi `find . -name "*.pro"`
%endif

$QTDIR/bin/qmake qwt.pro -o Makefile
(cd examples; $QTDIR/bin/qmake examples.pro -o Makefile)
(cd designer; $QTDIR/bin/qmake qwtplugin.pro -o Makefile)

%build

# build the library
make "CXX=`which ccache` g++"

# build the designer plugin
if [ -e $QTDIR/bin/qmake ]; then
    (cd designer; make "CXX=`which ccache` g++")
fi

# building the examples is a useful check 
(cd examples; make"CXX=`which ccache` g++")
 
%install

rm -rf %{buildroot}
mkdir -p %{buildroot}%{qtdir}/include/qwt
mkdir -p %{buildroot}%{qtdir}/lib
%if %use_man
mkdir -p %{buildroot}/%{_mandir}/man3
%endif

for n in include/*.h ; do
    install -m 644 $n %{buildroot}%{qtdir}/include/qwt
done

# install, preserving links
chmod 644 lib/libqwt.so*
for n in lib/libqwt.so* ; do
    cp -d $n %{buildroot}%{qtdir}/lib
done

# SuSE-9.0 has the policy of linking from /usr/lib to $(QTDIR)/lib
%if %buildForSuSE
mkdir -p %{buildroot}%{_libdir}
(cd %{buildroot}%{_libdir}; ln -sf $(basename %{qtdir})/lib/libqwt.so.4)
%endif

# build the designer plugin
if [ -e $QTDIR/bin/qmake ]; then
    (cd designer; make install INSTALL_ROOT=%{buildroot})
    echo "%{qtdir}/plugins/designer/libqwtplugin.so" > plugin.list
else
    echo >plugin.list
fi

%if %use_man
for n in doc/man/man3/*.3 ; do
    install -m 644 $n %{buildroot}/%{_mandir}/man3
done
%endif

# clean up the example tree
(cd examples; make distclean)
(cd examples; rm -f .*.cache */.*.cache */*/.*.cache)
(cd examples; rm -rf Makefile */moc */obj */*/moc */*/obj)

# the %%post and %%postun directives are superfluous on SuSE, but harmless
%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%clean
rm -rf %{buildroot}

%files
%defattr(-, root, root)
%doc CHANGES COPYING README
%{qtdir}/lib/libqwt.so*
%if %buildForSuSE
%{_libdir}/libqwt.so*
%endif

%files devel -f plugin.list
%defattr(-, root, root)
%doc COPYING doc/html/*.css doc/html/*.html doc/html/*.gif doc/html/*.png
%doc examples
%dir %{qtdir}/include/qwt
%{qtdir}/include/qwt/*
%if %use_man
%{_mandir}/man3/*
%endif


%changelog
* Mon Jun 13 2004 Gerard Vermeulen <gerard.vermeul@grenoble.cnrs.fr> 5.0.0rc0-1
- make qwt.spec from qwt.spec.in
- replaced %{version} by * in libqwt.so.%{version}
- added ccache
- install Qwt in %qtdir and adapt to the SuSE /etc/ld.so.conf policy

* Mon Oct 13 2003 Uwe Rathmann <uwe.rathmann@epost.de> 4.2.0-1
- rename 0.4.2 to 4.2.0

* Wed Apr 09 2003 Gerard Vermeulen <gvermeul@grenoble.cnrs.fr> 0.4.2-1
- changed license from LGPL to Qwt
- add designer plugin to qwt-devel
- remove example binaries & other files made when building the examples

* Tue Apr 08 2003 John Cummings <jcummings2@users.sourceforge.net>
- properly ordered changelog
- changed copyright tag to license
- improved instructions

* Tue Aug 06 2002 Uwe Rathmann 
- update for Qwt-0.4.2

* Wed Apr 24 2002 Gerard Vermeulen <gvermeul@polycnrs-gre.fr> 0.4.1-1
- spec file for Qwt-0.4.1 with Qt-2.X, Qt-3.X on Mandrake, Suse, ...

# EOF
