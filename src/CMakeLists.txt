# http://www.linux-magazin.de/Heft-Abo/Ausgaben/2007/02/Mal-ausspannen

cmake_minimum_required(VERSION 2.6)

set(libSrcs ${libSrcs}
    noisegen.cpp
    latlon.cpp

    model/line.cpp
    model/plane.cpp
    model/sphere.cpp
    model/cylinder.cpp

    module/abs.cpp
    module/add.cpp
    module/billow.cpp
    module/blend.cpp
    module/cache.cpp
    module/checkerboard.cpp
    module/clamp.cpp
    module/const.cpp
    module/curve.cpp
    module/cylinders.cpp
    module/displace.cpp
    module/exponent.cpp
    module/invert.cpp
    module/max.cpp
    module/min.cpp
    module/modulebase.cpp
    module/multiply.cpp
    module/perlin.cpp
    module/power.cpp
    module/ridgedmulti.cpp
    module/rotatepoint.cpp
    module/scalebias.cpp
    module/scalepoint.cpp
    module/select.cpp
    module/spheres.cpp
    module/terrace.cpp
    module/translatepoint.cpp
    module/turbulence.cpp
    module/voronoi.cpp

#     win32/dllmain.cpp
)

add_library( noise SHARED ${libSrcs})
add_library( noise-static STATIC ${libSrcs})

INCLUDE_DIRECTORIES (noise)

SET_TARGET_PROPERTIES( noise-static PROPERTIES OUTPUT_NAME "noise")

install(TARGETS noise DESTINATION lib)
SET_TARGET_PROPERTIES( noise PROPERTIES VERSION 1.0.0 )



