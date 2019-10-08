#!/usr/bin/env python2.7

# apply the patch

from os import environ
from os.path import abspath, dirname, join
import sys
from distutils import dir_util
from distutils.sysconfig import get_python_lib
import glob

#  ---------------------------------------------------------------------
# fixme: the notes below are taken from the original pygist/setup.py
#        the script itself is based on xplt
#
#  NAME:    setup.py
#
#  PURPOSE:  Faciliate installation of pygist module.
#
#  EXECUTE LINE:
#    python setup.py build             (optional)
#    python setup.py build -g install  (build a debug version and install)
#    python setup.py install           (does both build and install)
#    python setup.py sdist             (make a distribution version)
#    python setup.py bdist_rpm         (make an rpm version)
#
#  CHANGES:
#  10/28/01 llc Originated.
#  12/06/01 llc Replace hardwired path for Numeric include directory.
#  02/21/02 llc Add additional libraries to load on AIX (readline and cur).
#  09/02/02 llc Additional path for lx cluster.
#  09/16/02 llc Add path for IRIX and Solaris.
#  09/18/02 llc Consolidate all platform-specific differences here.
#            Add cygwin.
#  11/01/02 llc Remove readline and cur (curses) libraries.
#  11/04/02 llc For sdist, omit making libpyg.a.
#  11/11/02 mdh This script was completely rewritten by Michiel de Hoon
#            to ensure dependency of gistCmodule.so on libpyg.a.
#         llc No need to remove pscom.ps (similar to ps.ps).
#            List gfiles rather than use listdir.
#            No need to include X11 library directories.
#  11/13/02 llc Add option to use USE_RL_GETC, but do not use it.
#            /usr/local/include needed on aix5.
#  11/15/02 llc Use a third implementation approach by default.
#            PyOS_InputHook/u_waiter approach is enabled by defining
#            USE_U_WAITER.
#  12/27/02 mdh Rework to include config option, which works on Cygwin,
#            Windows, and Mac OS X, and will work on Unix/Linux when
#            python distutils is fixed.
#  04/07/03 mdh Add src/gist/style.c and set log verbosity.
#  04/08/03 llc Add extra compile option -nodtk for osf1V5; needed on
#            some of these platforms.
#  11/08/04 mdh Add support for Mac OSX.
#
#  ---------------------------------------------------------------------

def get_special_dirs(plat):
   if plat in ['aix4', 'aix5','sunos5']:
      return ['/usr/local/lib']
   elif plat in ['linux2','cygwin']:
      return ['/usr/lib64']
   return []


cygwin = 0
if sys.platform=='cygwin':
   cygwin = 1

# mdcb: doubtful the cocoa framework .. works
# get rid of macosx entirely
macosx = 0
if sys.platform=='darwin':
   macosx = 1
macosx = 0

for keyword in sys.argv:
   if keyword=='--x11':
      sys.argv.remove(keyword)
      cygwin = 0
      macosx = 0

windows = 0
if sys.platform=='win32':
   windows = 1

x11 = 0
if not (windows or cygwin or macosx):
   x11 = 1
if 'NO_XLIB' in environ:
   x11 = 0


gistsource = glob.glob('src/gist/*.c')
gistsource.append('plugin/plugin-hlevel.c')
gistsource.pop(gistsource.index('src/gist/browser.c'))
gistsource.pop(gistsource.index('src/gist/bench.c'))
gistsource.pop(gistsource.index('src/gist/cgmin.c'))

if cygwin:
   unixsource = ["src/play/unix/dir.c",
              "src/play/unix/files.c",
              "src/play/unix/pathnm.c",
              "src/play/unix/slinks.c",
              "src/play/unix/stdinit.c",
              "src/play/unix/uevent.c",
              "src/play/unix/uinbg.c",
              "src/play/unix/usernm.c"]
elif macosx:
   unixsource = ["src/play/unix/dir.c",
              "src/play/unix/files.c",
              "src/play/unix/pathnm.c",
              "src/play/unix/timew.c",
              "src/play/unix/slinks.c",
              "src/play/unix/stdinit.c",
              "src/play/unix/uevent.c",
              "src/play/unix/uinbg.c",
              "src/play/unix/usernm.c"]
elif not (windows):
   unixsource = [
              "src/play/unix/dir.c",
              "src/play/unix/files.c",
              "src/play/unix/fpuset.c",
              "src/play/unix/handler.c",
              "src/play/unix/pathnm.c",
              "src/play/unix/pmain.c",
              "src/play/unix/slinks.c",
              "src/play/unix/stdinit.c",
              "src/play/unix/timeu.c",
              "src/play/unix/timew.c",
              "src/play/unix/udl.c",
              "src/play/unix/uevent.c",
              "src/play/unix/ugetc.c",
              "src/play/unix/uinbg.c",
              "src/play/unix/umain.c",
              "src/play/unix/usernm.c",
              "src/play/unix/uspawn.c",
              ]

if not (windows or cygwin or macosx):
   x11source = glob.glob('src/play/x11/*.c')

if windows:
   winsource = [
             "src/play/win/clips.c",
             "src/play/win/cursors.c",
               "src/play/win/files.c",
             "src/play/win/getdc.c",
             "src/play/win/pals.c",
               "src/play/win/pathnm.c",
             "src/play/win/pcell.c",
             "src/play/win/pfill.c",
             "src/play/win/plines.c",
             "src/play/win/pmin.c",
             "src/play/win/points.c",
             "src/play/win/prect.c",
             "src/play/win/pscr.c",
             "src/play/win/ptext.c",
             "src/play/win/pwin.c",
             "src/play/win/timew.c",
               "src/play/win/usernm.c",
             ]
elif cygwin:
   winsource = [
             "src/play/win/clips.c",
             "src/play/win/cursors.c",
             "src/play/win/getdc.c",
             "src/play/win/pals.c",
             "src/play/win/pcell.c",
             "src/play/win/pfill.c",
             "src/play/win/plines.c",
             "src/play/win/pmin.c",
             "src/play/win/points.c",
             "src/play/win/prect.c",
             "src/play/win/pscr.c",
             "src/play/win/ptext.c",
             "src/play/win/pwin.c",
             "src/play/win/timew.c",
             ]
elif macosx:
   macsource = []
   #??? these do not exist
   #macsource = ["src/play/mac/pscr.m",
   #             "src/play/mac/pals.m",
   #             "src/play/mac/text.m",
   #             "src/play/mac/cell.m",
   #             "src/play/mac/bitblt.m",
   #             "src/play/mac/points.m",
   #             "src/play/mac/cursors.m",
   #             "src/play/mac/pwin.m",
   #             "src/play/mac/clips.m",
   #             "src/play/mac/pen.m",
   #             "src/play/mac/color.m",
   #             "src/play/mac/font.m"]

# common allsource
allsource = glob.glob('src/play/any/*.c')
allsource.pop(allsource.index('src/play/any/hashtest.c'))
allsource.pop(allsource.index('src/play/any/test2d.c'))
allsource.pop(allsource.index('src/play/any/mmtest.c'))
allsource.extend(glob.glob('src/yorick/*.c'))
allsource.pop(allsource.index('src/yorick/fortrn.c'))
allsource.pop(allsource.index('src/yorick/codger.c'))
allsource.pop(allsource.index('src/yorick/parsre.c'))
print '#################################################################'
print allsource
print '#################################################################'
# STAND_ALONE
# allsource.pop(allsource.index('src/play/any/numfmt.c'))
allsource.extend(glob.glob('src/regexp/*.c'))
allsource.extend(glob.glob('src/matrix/*.c'))
allsource.extend(glob.glob('src/fft/*.c'))
allsource.append('plugin/plugin-ywrap.c')
allsource.append('plugin/plugin-yinit.c')

def getallparams(gistpath,local_path,config_path):
   from numpy.distutils.system_info import get_info
   x11_info = get_info('x11')
   extra_compile_args = ['-DGISTPATH="\\"' + gistpath + '\\""' ]
   extra_compile_args.append("-DSTAND_ALONE") # [src/play/any/numfmt.c]
   # extra_compile_args.append("-O2 -DHAVE_XFT")
   extra_compile_args.append("-O2")
   extra_link_args = []
   if windows or cygwin:
      extra_compile_args.append("-DWINDOWS")
      extra_compile_args.append("-mwindows")
      extra_link_args.append("-mwindows")
      libraries = []
   else:
      libraries = x11_info.get('libraries',['X11'])
   if cygwin:
      extra_compile_args.append("-DCYGWIN")
   if macosx:
      extra_compile_args.append("-DMACOSX")
      extra_link_args.append('-framework')
      extra_link_args.append('Cocoa')


   include_dirs = ['plugin','src/gist', 'src/play', 'src/play/unix', 'src/regexp', 'src/matrix', 'src/yorick' ]

   library_dirs = [join(local_path,x) for x in ['.','src']]
   library_dirs.extend(x11_info.get('library_dirs',[]))
   library_dirs.extend(get_special_dirs(sys.platform))

   include_dirs = [join(local_path,x) for x in include_dirs]
   include_dirs.extend(x11_info.get('include_dirs',[]))
   # xft_info = get_info('xft')
   # include_dirs.extend(xft_info.get('include_dirs'))
   # libraries.extend(xft_info.get('libraries'))

   print 'config_path',config_path
   inputfile = open(join(config_path,"Make.cfg"))
   lines = inputfile.readlines()
   inputfile.close()
   for line in lines:
      if line[:8]=="MATHLIB=":
         mathlib = line[8:-1] #removing the \n
         # remove the -l
         mathlib = mathlib[2:]
         libraries.append(mathlib)
      if line[:9]=="NO_EXP10=":
         no_exp10 = line[9:-1] # removing \n
         if no_exp10: extra_compile_args.append(no_exp10)
      if line[:5]=="XINC=":
         xinc = line[5:-1] # removing \n
         if xinc and sys.platform not in ['cygwin','win32']:
            # remove the -I
            xinc = xinc[2:]
            if xinc: include_dirs.append(xinc)
      if line[:5]=="XLIB=":
         xlib = line[5:-1] # removing \n
         if xlib and sys.platform not in ['cygwin','win32']:
            # remove the -L
            xlib = xlib[2:]
            library_dirs.append(xlib)
      if line.startswith('D_FPUSET='):
         fpuset=line.split('=')[1].strip()
         extra_compile_args.append(fpuset)

   extra_compile_args.append('-DYLAPACK_NOALIAS')
   extra_compile_args.append('-DYCBLAS_NOALIAS')

   return include_dirs, library_dirs, libraries, \
            extra_compile_args, extra_link_args


def configuration(parent_package='',top_path=None):
   """
      This will install *.gs and *.gp files to
      'site-packages/gist/gistdata'
   """
   from numpy.distutils.misc_util import Configuration
   from config_pygist import yorick_configure
   config = Configuration(
      package_name='gist',
      parent_name=parent_package,
      top_path=top_path,
      package_path='gist',
      version='2.2.00x',
      description='gist for python.',
      long_description='A python plugin for gist.',
      url='http://yorick.sourceforge.net',
      author='David H. Munro',
      author_email='dhmunro@pacbell.net',
      maintainer='Matthieu D.C. Bec',
      maintainer_email='mdcb808@gmail.com',
      license='GPLv3'
      )

   local_path = config.local_path

   gistdata_path = join(get_python_lib(1),config.path_in_package,"gistdata")
   gistdata_path = gistdata_path.replace("\\",r"\\\\")

   def get_playsource(extension,build_dir):
      if windows:
         playsource = winsource + allsource
      elif cygwin:
         playsource = unixsource + winsource + allsource
      elif macosx:
         playsource = unixsource + macsource + allsource
      else:
         playsource = unixsource + x11source + allsource
      sources = [join(local_path,n) for n in playsource]

      config_path = join(build_dir,'confpygist')
      dir_util.mkpath(config_path)
      conf = yorick_configure(local_path,config_path)
      # Look to see if compiler is set on command line and add it
      #   This is repeating code, but I'm not sure how to avoid it
      #   As this gets run before overall setup does.
      #   This is needed so that compiler can be over-ridden from the
      #   platform default in the configuration section of gist.
      for arg in sys.argv[1:]:
         if arg[:11] == '--compiler=':
            conf.compiler = arg[11:]
            break
         if arg[:2] == '-c':
            conf.compiler = arg[2:]
            break
      # Generate Make.cfg and config.h:
      conf.run()

      include_dirs, library_dirs, libraries, \
                 extra_compile_args, extra_link_args \
                 = getallparams(gistdata_path,local_path,config_path)
      ###include_dirs.insert(0,dirname(conf.config_h))

      extension.include_dirs.extend(include_dirs)
      extension.library_dirs.extend(library_dirs)
      extension.libraries.extend(libraries)
      extension.extra_compile_args.extend(extra_compile_args)
      extension.extra_link_args.extend(extra_link_args)
      return sources

   gistC = join(local_path,'./plugin/gistCmodule.c')
   sources = [join(local_path,n) for n in gistsource]
   sources = [gistC] + sources + [get_playsource]

   config.add_extension('gistC',sources,depends = ['src','.'])
   config.add_extension('gistfuncs',[join(local_path,'./plugin/gistfuncsmodule.c')])

   config.add_subpackage('',subpackage_path='gist')

   gist_data = [join('gistdata',x) for x in ('*.gs','*.gp')] + \
               [join('src' ,'g',x) for x in ('*.gs','*.gp')]
   config.add_data_files (('gistdata',gist_data))

   return config

if __name__ == '__main__':
   from numpy.distutils.core import setup
   setup(name='python-',configuration=configuration)
