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

	win32/dllmain.cpp
)

add_library( noise SHARED ${libSrcs} )

target_compile_definitions( noise PRIVATE "-DNOISE_BUILD_DLL")

set_target_properties( noise PROPERTIES
	LIBNOISE_VERSION ${LIBNOISE_VERSION}
)

# install include files into /usr/include
INSTALL( DIRECTORY "${PROJECT_SOURCE_DIR}/src/noise" DESTINATION
  "${CMAKE_INSTALL_PREFIX}/include" )

# install libraries into /lib
INSTALL( TARGETS noise DESTINATION "${CMAKE_INSTALL_PREFIX}/Plugins" )



