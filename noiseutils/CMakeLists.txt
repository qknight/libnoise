set(PROJECT_NAME libnoiseutils)
set(LIB_NAME noiseutils)
message(STATUS "\n\n#############################################")
message(STATUS "# building project ${PROJECT_NAME}")

set(libSrcs ${libSrcs} noiseutils.cpp)


if(BUILD_SHARED_LIBS)
	#----------------------------------------
	# build dynamic lib
	set(TARGET_NAME "${LIB_NAME}")
	add_library(${TARGET_NAME} SHARED ${libSrcs})
	
	if(WIN32)
		#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")
		set_target_properties(${TARGET_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1)
	endif() 
	
	set_target_properties(${TARGET_NAME} PROPERTIES VERSION ${LIBNOISE_VERSION})
	target_link_libraries(${TARGET_NAME} noise)
	target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
	
	# install dynamic libraries (.dll or .so) into /bin
	install(TARGETS ${TARGET_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif()

#----------------------------------------
# build static lib (it's good practice to include a lib file for the dll)
set(TARGET_NAME "${LIB_NAME}-static")
add_library(${TARGET_NAME} STATIC ${libSrcs})
set_target_properties(${TARGET_NAME} PROPERTIES VERSION ${LIBNOISE_VERSION})
target_link_libraries(${TARGET_NAME} noise-static) 
target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src) 
# install static libraries (.lib) into /lib
install(TARGETS ${TARGET_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
#----------------------------------------

# install include files into /include
install( FILES "${PROJECT_SOURCE_DIR}/noiseutils/noiseutils.h" 
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/noise" )