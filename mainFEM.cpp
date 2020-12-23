/**
 * mainFEM.cpp
 * -----------
 * 
 * Main script for the FEM solver.
 */

#include <stdio.h>
#include <stdlib.h>

#include <fem/FEMSolver.hpp>

int main(void) {
    Eigen::MatrixXd T, S;
    FEMSolver solver(T, S);
    return EXIT_SUCCESS;
}
