# example copied from liblasi which is using doxygen
# but i'd like to use http://www.cmake.org/pipermail/cmake/2006-August/010794.html instead...
#
# this code works now but i don't like it
#
#
# Generating documentation with doxygen
#
# if(DOXYGEN_EXECUTABLE AND UNIX)
  
  # N.B. Both the following custom rules assume the doc directory exists
  # at make time, and the following install(DIRECTORY... must have doc exist
  # at cmake time.  Therefore, create the doc directory at CMake time.
  # (Linux experimentation indicates this is a no-op if the empty or
  # non-empty directory already exists.)
#   file(MAKE_DIRECTORY doc)

  # The initial rm command gets rid of everything previously built by this
  # custom command.
  add_custom_command(
  OUTPUT ${PROJECT_SOURCE_DIR}/doc/html/index.html
  COMMAND rm -rf html
  COMMAND mkdir html
  COMMAND doxygen ${PROJECT_SOURCE_DIR}/doc/Doxyfile
  DEPENDS Doxyfile
  WORKING_DIRECTORY "."
  )

  add_custom_target(
  documentation ALL
  DEPENDS
  html/index.html
  )
  
  # Install the documentation generated at "make" time.
  install(DIRECTORY html DESTINATION html)

# endif(DOXYGEN_EXECUTABLE AND UNIX)