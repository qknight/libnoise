# http://www.linux-magazin.de/Heft-Abo/Ausgaben/2007/02/Mal-ausspannen

cmake_minimum_required(VERSION 2.6)

SET ( LIBNOISE_VERSION "1.0.0-cmake" )

OPTION(BUILD_LIBNOISE_DOCUMENTATION "Create doxygen documentation for developers" OFF)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(doc)

#ADD_SUBDIRECTORY(samples)
