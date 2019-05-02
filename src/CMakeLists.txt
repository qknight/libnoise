# http://www.linux-magazin.de/Heft-Abo/Ausgaben/2007/02/Mal-ausspannen

set(PROJECT_NAME libnoise)

include_directories (noise)

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
		message(STATUS "build - shared for win32 (x86)")
		add_library( noise SHARED ${libSrcs} win32/dllmain.cpp)
    ELSE()
		message(STATUS "build - shared for others")
		add_library( noise SHARED ${libSrcs} )
    ENDIF()
ENDIF()

add_library( noise-static STATIC ${libSrcs} )

# this value is set in the root CMakeLists.txt
set_target_properties( noise PROPERTIES LIBNOISE_VERSION ${LIBNOISE_VERSION} )
set_target_properties( noise-static PROPERTIES LIBNOISE_VERSION ${LIBNOISE_VERSION} )

target_compile_definitions( noise PRIVATE NOISE_BUILD_DLL)
target_compile_definitions( noise-static PUBLIC NOISE_STATIC)

set_target_properties( noise-static PROPERTIES OUTPUT_NAME "noise" )

# I would like to see more projects using these defaults
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	message(STATUS "noiseutils - using optimized compile settings with all warnings enabled")
	add_compile_options(-Wall -ansi -pedantic -O3)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	message(STATUS "noiseutils - using optimized compile settings with all warnings enabled")
	add_compile_options(/Wall /Ox)
endif()

# install include files into /include
install( DIRECTORY "${PROJECT_SOURCE_DIR}/src/noise" 
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include" )

# install dynamic libraries (.dll or .so) into /bin
install( TARGETS noise DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" )

# install static libraries (.lib) into /lib
install( TARGETS noise-static DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" )