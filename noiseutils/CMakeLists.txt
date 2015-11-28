SET(PROJECT_NAME libnoiseutils)

add_library(noiseutils SHARED noiseutils.cpp )
add_library(noiseutils-static STATIC noiseutils.cpp )

SET_TARGET_PROPERTIES( noiseutils PROPERTIES LIBNOISE_VERSION ${LIBNOISE_VERSION} )
SET_TARGET_PROPERTIES( noiseutils-static PROPERTIES LIBNOISE_VERSION ${LIBNOISE_VERSION} )

# i would like to see more projects using these defaults
ADD_DEFINITIONS( "-Wall -ansi -pedantic -O3" )

# install include files into /usr/include
INSTALL( FILES "${PROJECT_SOURCE_DIR}/noiseutils/noiseutils.h" DESTINATION
  "${CMAKE_INSTALL_PREFIX}/include/noise" )

# install libraries into /lib
INSTALL( TARGETS noiseutils DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" )
INSTALL( TARGETS noiseutils-static DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" )
