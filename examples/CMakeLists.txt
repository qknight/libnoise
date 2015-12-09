SET(PROJECT_NAME examples)

add_executable(complexplanet complexplanet.cpp)
ADD_DEFINITIONS( "-I${PROJECT_SOURCE_DIR}/src" )
ADD_DEFINITIONS( "-I${PROJECT_SOURCE_DIR}/noiseutils" )
target_link_libraries(complexplanet noiseutils-static noise-static)
