# http://www.linux-magazin.de/Heft-Abo/Ausgaben/2007/02/Mal-ausspannen

SET(PROJECT_NAME libnoise)

INCLUDE_DIRECTORIES (noise)

set(libSrcs ${libSrcs}
    noisegen.cpp
    latlon.cpp

    model/line.cpp
    model/plane.cpp
    model/sphere.cpp
    model/cylinder.cpp

    module/abs.cpp
    module/add.cpp
    module/billow.cpp
    module/blend.cpp
    module/cache.cpp
    module/checkerboard.cpp
    module/clamp.cpp
    module/const.cpp
    module/curve.cpp
    module/cylinders.cpp
    module/displace.cpp
    module/exponent.cpp
    module/invert.cpp
    module/max.cpp
    module/min.cpp
    module/modulebase.cpp
    module/multiply.cpp
    module/perlin.cpp
    module/power.cpp
    module/ridgedmulti.cpp
    module/rotatepoint.cpp
    module/scalebias.cpp
    module/scalepoint.cpp
    module/select.cpp
    module/spheres.cpp
    module/terrace.cpp
    module/translatepoint.cpp
    module/turbulence.cpp
    module/voronoi.cpp

#     win32/dllmain.cpp
)

add_library( noise SHARED ${libSrcs} )
add_library( noise-static STATIC ${libSrcs} )

SET_TARGET_PROPERTIES( noise PROPERTIES LIBNOISE_VERSION 1.0.0 )
SET_TARGET_PROPERTIES( noise-static PROPERTIES OUTPUT_NAME "noise" )

# i would to see more projects using these defaults
ADD_DEFINITIONS( "-Wall -ansi -pedantic" )

# project options
OPTION( BUILD_WITH_DEBUG "Set to OFF to build the library targets without -g" OFF )
OPTION( BUILD_WITH_OPTIMIZATION "Set to OFF to build the library targets without -O3" ON )

IF (BUILD_WITH_OPTIMIZATION)
  ADD_DEFINITIONS( "-O3" )
ENDIF(BUILD_WITH_OPTIMIZATION)

IF (BUILD_WITH_DEBUG)
  IF (BUILD_WITH_OPTIMIZATION)
    MESSAGE( FATAL_ERROR "ERROR: BUILD_WITH_OPTIMIZATION AND BUILD_WITH_DEBUG is enabled! Disable BUILD_WITH_OPTIMIZATION when you want to debug the library. In general -O3 can't be used with -g because debuggers fail to display propper values.")
  ENDIF(BUILD_WITH_OPTIMIZATION)
  ADD_DEFINITIONS( "-g" )
ENDIF(BUILD_WITH_DEBUG)

# install include files into /usr/include
INSTALL( DIRECTORY "${PROJECT_SOURCE_DIR}/src/noise" DESTINATION "/usr/include" )

# install libraries into /lib
INSTALL( TARGETS noise DESTINATION "/lib" )
INSTALL( TARGETS noise-static DESTINATION "/lib" )



