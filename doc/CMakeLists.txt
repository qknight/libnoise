# many thanks go to Philippe Poilbarbe for writing the code this file is based on
# http://www.cmake.org/pipermail/cmake/2006-August/010794.html
  
# OPTION(MYPROJECT_DOC_WITH_STATIC "Create documentation for static members" ON)
# OPTION(MYPROJECT_DOC_WITH_PRIVATE "Create documentation for private members" OFF)
# OPTION(MYPROJECT_DOC_WITH_LOCAL "Create documentation for local members" OFF)
# OPTION(MYPROJECT_DOC_WITH_INTERNAL "Create documentation for internal features" OFF)
# MARK_AS_ADVANCED(
#     MYPROJECT_DOC_WITH_PRIVATE
#     MYPROJECT_DOC_WITH_STATIC
#     MYPROJECT_DOC_WITH_LOCAL
#     MYPROJECT_DOC_WITH_INTERNAL
# )
# FIND_PACKAGE(HTMLHelp)
# IF (HTML_HELP_COMPILER)
#   SET(DOXYGEN_HTMLHELP YES)
# ELSE (HTML_HELP_COMPILER)
#   SET(DOXYGEN_HTMLHELP NO)
# ENDIF (HTML_HELP_COMPILER)
# 
# SET(DOXYGEN_LATEX NO)
# SET(DOXYGEN_PDFLATEX NO)
# SET(DOXYGEN_PDF_HYPERLINKS NO)
# 
# IF (MYPROJECT_DOC_WITH_PRIVATE)
#   SET(DOXYGEN_EXTRACT_PRIVATE YES)
# ELSE (MYPROJECT_DOC_WITH_PRIVATE)
#   SET(DOXYGEN_EXTRACT_PRIVATE NO)
# ENDIF (MYPROJECT_DOC_WITH_PRIVATE)
# 
# IF (MYPROJECT_DOC_WITH_STATIC)
#   SET(DOXYGEN_EXTRACT_STATIC YES)
# ELSE (MYPROJECT_DOC_WITH_STATIC)
#   SET(DOXYGEN_EXTRACT_STATIC NO)
# ENDIF (MYPROJECT_DOC_WITH_STATIC)
# 
# IF (MYPROJECT_DOC_WITH_LOCAL)
#   SET(DOXYGEN_EXTRACT_LOCAL YES)
# ELSE (MYPROJECT_DOC_WITH_LOCAL)
#   SET(DOXYGEN_EXTRACT_LOCAL NO)
# ENDIF (MYPROJECT_DOC_WITH_LOCAL)
# 
# IF (MYPROJECT_DOC_WITH_INTERNAL)
#   SET(DOXYGEN_EXTRACT_INTERNAL YES)
# ELSE (MYPROJECT_DOC_WITH_INTERNAL)
#   SET(DOXYGEN_EXTRACT_INTERNAL NO)
# ENDIF (MYPROJECT_DOC_WITH_INTERNAL)
# 
# IF (DOT)
#   SET(HAVE_DOT YES)
# ELSE (DOT)
#   SET(HAVE_DOT NO)
# ENDIF (DOT)

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
  /home/joachim/Desktop/projects/springrts.com-random-map-generator/noise/src
)

SET(DOXYGEN_OUTPUT_DIR html)
STRING(REGEX REPLACE ";" " " CMAKE_DOXYGEN_INPUT_LIST "${DOXYGEN_SOURCE_DIR}")

CONFIGURE_FILE(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
SET(HTML_TARGET "html" )

ADD_CUSTOM_TARGET(${HTML_TARGET} ALL
	      /usr/bin/doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
              DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

INSTALL( DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/" DESTINATION "/usr/share/noise" )
