# Define the kmod package name here.
%define kmod_name universeII

# If kversion isn't defined on the rpmbuild line, define it here and use the currently running kernel.
%{!?kversion: %define kversion `uname -r`}

Name:    %{kmod_name}-kmod
Version: 0.96
Release: 1%{?dist}
Group:   System Environment/Kernel
License: GPLv2
Summary: %{kmod_name} kernel module(s)
URL:     http://universe2.sourceforge.net

BuildRequires: redhat-rpm-config
ExclusiveArch: i686 x86_64

# Sources.
Source0:  %{kmod_name}-%{version}.tar.bz2
Source1:  99-universeII.rules
Source5:  gpl-2.0.txt
Source10: kmodtool-%{kmod_name}.sh

# Magic hidden here.
%{expand:%(sh %{SOURCE10} rpmtemplate %{kmod_name} %{kversion} "")}

# Disable the building of the debug package(s).
%define debug_package %{nil}

%description
This package provides the %{kmod_name} kernel module(s).
It is built to depend upon the specific ABI provided by a range of releases
of the same variant of the Linux kernel and not on any one specific build.

It also provides a udev ruleset to make the VME devices accessible to the users
group

%prep
%setup -q -n %{kmod_name}-%{version}
echo "override %{kmod_name} * weak-updates/%{kmod_name}" > kmod-%{kmod_name}.conf

%build
KSRC=%{_usrsrc}/kernels/%{kversion}
%{__make} -C "${KSRC}" %{?_smp_mflags} modules M=$PWD

%install
export INSTALL_MOD_PATH=%{buildroot}
export INSTALL_MOD_DIR=extra/%{kmod_name}
KSRC=%{_usrsrc}/kernels/%{kversion}
%{__make} -C "${KSRC}" modules_install M=$PWD
%{__install} -d %{buildroot}%{_sysconfdir}/depmod.d/
%{__install} kmod-%{kmod_name}.conf %{buildroot}%{_sysconfdir}/depmod.d/
%{__install} -d %{buildroot}%{_defaultdocdir}/kmod-%{kmod_name}-%{version}/
%{__install} %{SOURCE5} %{buildroot}%{_defaultdocdir}/kmod-%{kmod_name}-%{version}/
%{__install} -d %{buildroot}%{_sysconfdir}/udev/rules.d/
%{__install} %{SOURCE1} %{buildroot}%{_sysconfdir}/udev/rules.d/

# Set the module(s) to be executable, so that they will be stripped when packaged.
find %{buildroot} -type f -name \*.ko -exec %{__chmod} u+x \{\} \;

# Remove the unrequired files.
%{__rm} -f %{buildroot}/lib/modules/%{kversion}/modules.*

%clean
%{__rm} -rf %{buildroot}

%changelog
* Tue Jun 14 2022 Jan Hartmann <hartmann@hiskp.uni-bonn.de> - 0.96-1
- updated universeII to work with newer Kernels

* Wed Aug 22 2012 Christian Funke <funke@hiskp.uni-bonn.de> - 0.95-1
- Initial build of package for RHEL6/CentOS6/SL6
