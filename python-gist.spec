%define _prefix __auto__
%define version __auto__
%define release __auto__

# you may need that ...
#cat ~/.pydistutils.cfg 
#[install]
#optimize=1

Summary: Gist for Python
Name: python-gist
Version: %{version}
Release: %{version}%{?dist}.gemini
URL: http://www.gemini.edu
Packager: Matthieu Bec <mbec@gemini.edu>
License: mbec@gemini.edu
Group: Gemini
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires: python-devel
Requires: python

Source0: %{name}-%{version}.tar.gz

##%define _prefix %(echo $GEMINI_TOP)
%define debug_package %{nil}
%define python_lib %(python -c "from  distutils import sysconfig;print sysconfig.get_python_lib()")
%define gem_lib %(python -c "from  distutils import sysconfig;print sysconfig.get_python_lib().replace(sysconfig.PREFIX,'%_prefix')")

%description
Gist wrapper for python.

%prep
%setup -q -n %name
( cd src && patch -p1 < ../patches/yorick-cvs-pwin-border.patch)
( cd src && patch -p1 < ../patches/yorick-cvs-xft.patch)


%build
PATH=$PATH:.
python setup.py build

%install
PATH=$PATH:.
python setup.py install --root $RPM_BUILD_ROOT --prefix %_prefix
touch $RPM_BUILD_ROOT%gem_lib/gist.egg-info

mkdir -p $RPM_BUILD_ROOT%python_lib
echo %gem_lib > $RPM_BUILD_ROOT%python_lib/gist.pth

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%gem_lib/gist
%gem_lib/gist*.egg-info
%python_lib/gist.pth

%changelog
* Fri Mar 12 2010 Matthieu Bec <mbec@gemini.edu> 2.05x2
- upstream cvs
* Tue Jun 30 2009 Matthieu Bec <mbec@gemini.edu> 1.5.29
- first spec file compatible with gemini-buildrpm
