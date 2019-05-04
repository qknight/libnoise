# http://www.linux-magazin.de/Heft-Abo/Ausgaben/2007/02/Mal-ausspannen

cmake_minimum_required(VERSION 3.0)

set(LIBNOISE_VERSION "1.0.0-cmake")

#----------------------------------------
# Provide an option for the user to select (default given; otherwhise pass -Doption=ON to cmake)
option(BUILD_WALL "Build with all warnings enabled" OFF)
option(BUILD_OPTIMIZED "Build with optimization for speed" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries for libnoise" ON)
option(BUILD_LIBNOISE_DOCUMENTATION "Create doxygen documentation for developers" OFF)
option(BUILD_LIBNOISE_UTILS "Build utility functions for use with libnoise" ON)
option(BUILD_LIBNOISE_EXAMPLES "Build libnoise examples" ON)

#----------------------------------------
# enable all warnings
if (BUILD_WALL)
	if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
		message(STATUS "GNU - using build with all warnings enabled")
		add_compile_options(-Wall -ansi -pedantic)
	elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
		message(STATUS "MSVC - using build with all warnings enabled")
		add_compile_options(/Wall)
	endif()
endif()

#----------------------------------------
# enable optimized compile settings
if (BUILD_OPTIMIZED)
	if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
		message(STATUS "GNU - using compiler optimization for speed")
		add_compile_options(-O3)
	elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
		message(STATUS "MSVC - using compiler optimization for speed")
		add_compile_options(/Ox)
	endif()
endif()

#----------------------------------------
# src
add_subdirectory(src)

#----------------------------------------
# docs
if(BUILD_LIBNOISE_DOCUMENTATION)
	add_subdirectory(doc) 
endif()

#----------------------------------------
# noiseutils
if (BUILD_LIBNOISE_UTILS)
	add_subdirectory(noiseutils)
endif()

#----------------------------------------
# examples
if (BUILD_LIBNOISE_EXAMPLES AND BUILD_LIBNOISE_UTILS)
	add_subdirectory(examples) # examples also depend on noiseutils
elseif (BUILD_LIBNOISE_EXAMPLES)
	message(STATUS "examples depend on noiseutils - \
		fix: pass option -DBUILD_SHARED_LIBS=ON to cmake")
endif()


#----------------------------------------
# unused variables passed by vcpkg
message(STATUS "CMAKE_INSTALL_BINDIR : " ${CMAKE_INSTALL_BINDIR})
message(STATUS "CMAKE_INSTALL_LIBDIR : " ${CMAKE_INSTALL_LIBDIR})