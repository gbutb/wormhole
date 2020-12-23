/**
 * FEMSolver.hpp
 * -------------
 * 
 * Given T and S matrices, computes finite element solution.
 * 
 * Solves:
 * TU'' + SU = 0
 */

#ifndef WORMHOLE_FEMSOLVER_HPP_
#define WORMHOLE_FEMSOLVER_HPP_

#include <Eigen/Core>

typedef Eigen::MatrixXd Matrix;
typedef Eigen::VectorXd Vector;

// TODO: Handle general boundary conditions.

class FEMSolver {
 private:
    Matrix _T, _S;
    float _timeStep;

    Vector u_previous;
    Vector u_current; 

    bool initial_conditions_set = false;
 public:
    FEMSolver(Matrix T, Matrix S, float timeStep = 0.0001);

    void setInitialConditions(Vector u_current, Vector u_previous);

    bool singleStep();

    inline Vector& getCurrentU() {
        return u_current;
    }
};


#endif  // WORMHOLE_FEMSOLVER_HPP_
