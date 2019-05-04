# many thanks go to Philippe Poilbarbe for writing the code this file is based on
#  http://www.cmake.org/pipermail/cmake/2006-August/010794.html
#
# much later i also found this:
#  http://tobias.rautenkranz.ch/cmake/doxygen/
# but it is hard to understand...
  
find_package(Doxygen)

if(DOXYGEN_FOUND)
	set(DOXYGEN_LANGUAGE "English" CACHE STRING "Language used by doxygen")
	mark_as_advanced(DOXYGEN_LANGUAGE)

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
	set( CMAKE_DOXYGEN_IMAGE_PATH
	"${CMAKE_CURRENT_SOURCE_DIR}/img"
	)

	# doxygen searches for source code (defined in FILE_PATTERNS, for example: *.cpp *.h)
	# with DOXYGEN_SOURCE_DIR we fill a list of directories and later we write it into
	# the Doxyfile with a REGEX REPLACE (see below)
	set( DOXYGEN_SOURCE_DIR
	"${CMAKE_SOURCE_DIR}/src"
	)

	set(DOXYGEN_OUTPUT_DIR html)
	string(REGEX REPLACE ";" " " CMAKE_DOXYGEN_INPUT_LIST "${DOXYGEN_SOURCE_DIR}")

	configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
	set(HTML_TARGET "html" )

	add_custom_target(${HTML_TARGET} ALL
	${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	install( DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/" DESTINATION "/usr/share/doc/libnoise-${LIBNOISE_VERSION}" )

else(DOXYGEN_FOUND)
	message (FATAL_ERROR "doxygen binary couldn't be found")
endif(DOXYGEN_FOUND)