/**
 * mainFEM.cpp
 * -----------
 * 
 * Main script for the FEM solver.
 */

#include <stdio.h>
#include <stdlib.h>

#include <fem/FEMSolver.hpp>
#include <fem/wormhole/wormhole.hpp>

#include <iostream>
using namespace std;

int main(void) {
    int N = 100;
    double r_radius = 1.0;
    double a_radius = 0.9;
    double stepSize = 2*r_radius/(N - 1);

    // Construct wormhole system
    Eigen::MatrixXd T = Wormhole::getT(stepSize, N);
    Eigen::MatrixXd S = Wormhole::getS(stepSize, N) + Wormhole::getQ(r_radius, a_radius, stepSize, N);
    FEMSolver solver(T, S);

    // Construct initial condition
    Vector u = Vector::Zero(N);
    for (int i = 0; i < N; ++i) {
        u(i) = pow(sin(M_PI * i * stepSize), 2);
    }

    solver.setInitialConditions(u, u);

    // Save solution
    for (int i = 0; i < 200; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%f%s", solver.getCurrentU()(j), j < N - 1 ? "," : "");
        }
        solver.singleStep();
        printf("\n");
    }

    return EXIT_SUCCESS;
}
