set(PROJECT_NAME libnoiseutils)
set(LIB_NAME noiseutils)
message(STATUS "\n\n#############################################")
message(STATUS "# building project ${PROJECT_NAME}")

endif()

# Where to look for noise headers
target_include_directories( noiseutils PRIVATE ${PROJECT_SOURCE_DIR}/src )
target_include_directories( noiseutils-static PRIVATE ${PROJECT_SOURCE_DIR}/src )

# install include files into /include
install( FILES "${PROJECT_SOURCE_DIR}/noiseutils/noiseutils.h" 
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/noise" )

# install dynamic libraries (.dll or .so) into /bin
install( TARGETS noiseutils DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" )

# install static libraries (.lib) into /lib
install( TARGETS noiseutils-static DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" )
