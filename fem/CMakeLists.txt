# Load includes
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${EIGEN3_INCLUDE_DIR})

add_library(
    femSolver
    femSolver.cpp)
