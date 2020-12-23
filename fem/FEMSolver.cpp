/**
 * FEMSolver.cpp
 * -------------
 * 
 * Implements FEM solver.
 */

#include "FEMSolver.hpp"
#include <Eigen/Dense>

FEMSolver::FEMSolver(Matrix T, Matrix S, float timeStep) : _T(T), _S(S), _timeStep(timeStep) {}

void FEMSolver::setInitialConditions(Vector u_current, Vector u_previous) {
    initial_conditions_set = true;
    this->u_current = u_current;
    this->u_previous = u_previous;
}

bool FEMSolver::singleStep() {
    if (!initial_conditions_set) {
        printf("No initial conditions were set. Exiting!\n");
        return false;
    }

    // Solve the linear system
    Vector inverted = -_timeStep*_T.lu().solve(_S*u_current);

    Vector u_new = inverted + 2 * u_current - u_previous;
    u_previous = u_current;
    u_current = u_new;

    return true;
}
