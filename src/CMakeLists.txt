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
)

IF(BUILD_SHARED_LIBS)
    IF (WIN32)
    add_library( noise SHARED ${libSrcs} win32/dllmain.cpp)
    ELSE()
    add_library( noise SHARED ${libSrcs} )
    ENDIF()
ENDIF()

add_library( noise-static STATIC ${libSrcs} )

# this value is set in the root CMakeLists.txt
SET_TARGET_PROPERTIES( noise PROPERTIES LIBNOISE_VERSION ${LIBNOISE_VERSION} )
SET_TARGET_PROPERTIES( noise-static PROPERTIES LIBNOISE_VERSION ${LIBNOISE_VERSION} )

target_compile_definitions( noise PRIVATE NOISE_BUILD_DLL)
target_compile_definitions( noise-static PUBLIC NOISE_STATIC)

SET_TARGET_PROPERTIES( noise-static PROPERTIES OUTPUT_NAME "noise" )

# i would like to see more projects using these defaults
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  ADD_DEFINITIONS( "-Wall -ansi -pedantic -O3" )
endif()

# install include files into /usr/include
INSTALL( DIRECTORY "${PROJECT_SOURCE_DIR}/src/noise" DESTINATION
  "${CMAKE_INSTALL_PREFIX}/include" )

# install libraries into /lib
INSTALL( TARGETS noise DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" )
INSTALL( TARGETS noise-static DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" )



