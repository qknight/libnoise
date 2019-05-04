set(PROJECT_NAME libnoise)
set(LIB_NAME noise)
message(STATUS "\n\n#############################################")
message(STATUS "# building project ${PROJECT_NAME}")

include_directories(noise)

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

# Users of your library should be able to choose static library or shared library to build. 
# Do not specify a library type explicitly unless necessary.
if(BUILD_SHARED_LIBS)
	#----------------------------------------
	# build dynamic lib
	set(TARGET_NAME "${LIB_NAME}")
    if (WIN32)
		message(STATUS "build ${TARGET_NAME}: shared | platform: win32 (x86) & win64 (x64)")
		add_library(${TARGET_NAME} SHARED ${libSrcs} win32/dllmain.cpp)
		set_target_properties(${TARGET_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1)
    else()
		message(STATUS "build ${TARGET_NAME}: shared | platform: others")
		add_library(${TARGET_NAME} SHARED ${libSrcs})
    endif()
	set_target_properties(${TARGET_NAME} PROPERTIES VERSION ${LIBNOISE_VERSION})
	target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
	target_compile_definitions(${TARGET_NAME} PRIVATE NOISE_BUILD_DLL)
	install(TARGETS ${TARGET_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif()

#----------------------------------------
# build static lib (it's good practice to include a lib file for the dll)
set(TARGET_NAME "${LIB_NAME}-static")
message(STATUS "build ${TARGET_NAME}")
add_library(${TARGET_NAME} STATIC ${libSrcs})
set_target_properties(${TARGET_NAME} PROPERTIES VERSION ${LIBNOISE_VERSION})
target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_compile_definitions(${TARGET_NAME} PUBLIC NOISE_STATIC)
# install static libraries (.lib) into /lib
install(TARGETS ${TARGET_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
#----------------------------------------

# install include files into /include
install( DIRECTORY   "${PROJECT_SOURCE_DIR}/src/noise" 
		 DESTINATION "${CMAKE_INSTALL_PREFIX}/include" )