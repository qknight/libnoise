# many thanks go to Philippe Poilbarbe for writing the code this file is based on
#  http://www.cmake.org/pipermail/cmake/2006-August/010794.html
#
# much later i also found this:
#  http://tobias.rautenkranz.ch/cmake/doxygen/
# but it is hard to understand...
  
IF (BUILD_LIBNOISE_DOCUMENTATION)

FIND_PACKAGE(Doxygen)

IF(DOXYGEN_FOUND)
  SET(DOXYGEN_LANGUAGE "English" CACHE STRING "Language used by doxygen")
  MARK_AS_ADVANCED(DOXYGEN_LANGUAGE)

  # you could also set the version with this, see Doxygen.in
  # there you will find a line like this: 
  #      PROJECT_NUMBER         = @LIBNOISE_VERSION@
  # @LIBNOISE_VERSION@ is then replaced by our global LIBNOISE_VERSION
  #
  # for instance you could uncomment the next 3 lines and change the version for testing
  # SET(LIBNOISE_VERSION
  #     "1.2.3-foo500"
  # )

  # doxygen can reference external images with IMAGE_PATH, this is how we set it dynamically
  SET( CMAKE_DOXYGEN_IMAGE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/img"
  )

  # doxygen searches for source code (defined in FILE_PATTERNS, for example: *.cpp *.h)
  # with DOXYGEN_SOURCE_DIR we fill a list of directories and later we write it into
  # the Doxyfile with a REGEX REPLACE (see below)
  SET( DOXYGEN_SOURCE_DIR
    "${CMAKE_SOURCE_DIR}/src"
  )

  SET(DOXYGEN_OUTPUT_DIR html)
  STRING(REGEX REPLACE ";" " " CMAKE_DOXYGEN_INPUT_LIST "${DOXYGEN_SOURCE_DIR}")

  CONFIGURE_FILE(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  SET(HTML_TARGET "html" )

  ADD_CUSTOM_TARGET(${HTML_TARGET} ALL
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  INSTALL( DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/" DESTINATION "/usr/share/doc/libnoise-${LIBNOISE_VERSION}" )

ELSE(DOXYGEN_FOUND)
  MESSAGE (FATAL_ERROR "doxygen binary couldn't be found")
ENDIF(DOXYGEN_FOUND)

ENDIF (BUILD_LIBNOISE_DOCUMENTATION)

