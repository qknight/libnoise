# Locate libnoise.
# This module defines
# LIBNOISE_LIBRARIES
# LIBNOISE_FOUND, if false, do not try to link to libnoise
# LIBNOISE_INCLUDE_DIR, where to find the headers

FIND_PATH(LIBNOISE_INCLUDE_DIR noise.h
  $ENV{LIBNOISE_DIR}
  NO_DEFAULT_PATH
    PATH_SUFFIXES include
)

FIND_PATH(LIBNOISE_INCLUDE_DIR "noise.h"
  PATHS
  ${CMAKE_SOURCE_DIR}/include
  ~/Library/Frameworks/noise/Headers
  /Library/Frameworks/noise/Headers
  /usr/local/include/noise
  /usr/local/include/noise
  /usr/local/include
  /usr/include/noise
  /usr/include/noise
  /usr/include
  /sw/include/noise 
  /sw/include/noise 
  /sw/include # Fink
  /opt/local/include/noise
  /opt/local/include/noise
  /opt/local/include # DarwinPorts
  /opt/csw/include/noise
  /opt/csw/include/noise
  /opt/csw/include # Blastwave
  /opt/include/noise
  /opt/include/noise
  /opt/include  
    PATH_SUFFIXES noise
)

FIND_LIBRARY(LIBNOISE_LIBRARIES
  NAMES libnoise noise libnoiseutils noiseutils
  PATHS
    $ENV{LIBNOISE_DIR}
    NO_DEFAULT_PATH
    PATH_SUFFIXES lib64 lib so
)

FIND_LIBRARY(LIBNOISE_LIBRARIES
  NAMES libnoise noise libnoiseutils noiseutils
  PATHS
    ${CMAKE_SOURCE_DIR}/lib
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt
    /usr/freeware    
  PATH_SUFFIXES lib64 lib so
)

message("LIBNOISE_INCLUDE_DIR: ${LIBNOISE_INCLUDE_DIR}")

SET(LIBNOISE_FOUND "NO")
IF(LIBNOISE_LIBRARY AND LIBNOISE_INCLUDE_DIR)
  SET(LIBNOISE_FOUND "YES")
ENDIF(LIBNOISE_LIBRARY AND LIBNOISE_INCLUDE_DIR)

