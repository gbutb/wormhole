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
    int N = 51;
    double stepSize = 1.0/(N - 1);
    Eigen::MatrixXd T = Wormhole::getT(stepSize, N);
    Eigen::MatrixXd S = Wormhole::getS(stepSize, N);
    FEMSolver solver(T, S);

    Vector u = Vector::Zero(N);
    for (int i = 0; i < N; ++i) {
        u(i) = pow(sin(M_PI * i * stepSize), 2);
        printf("%f\n", pow(sin(M_PI * i * stepSize), 2));
    }

    solver.setInitialConditions(u, u);

    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%f%s", solver.getCurrentU()(j), j < N - 1 ? "," : "");
        }
        solver.singleStep();
        printf("\n");
    }

    return EXIT_SUCCESS;
}
