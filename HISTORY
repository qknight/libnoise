2010-11-29
 * fixed some doxygen specific issue, thanks to Max Bolingbroke. now libnoise compiles in:
   - gentoo linux (according to me: 32 and 64 bit runtimes)
   - mac os x, using macports (according to Max Bolingbroke) 

2009-11-29 
 * there is some license problem: the library uses the LGPL 2.1 and the examples (on the download page use GPL v2)
   but the zip file with example sources included uses also LGPL 2.1 license?!
 * basic doxygen support is there
 * wrote 'make install' step using cmake 
 * WARNING: src/win32/ is not used at all, maybe someone has to test this with win32 ...
   and i removed thse win32 files from the distribution, maybe someone want's to have them back?
 * changed the library #include "noise.h" instead of "noise/noise.h"
   there is no /include directory anymore since one must use src/ as include path now
   which will the be searched for "noise.h" now
 * cmake: created a CMakeList.txt which builds the .so and .a file
 * removed static Makefiles and libtool but keep compatibility to existing projects working
