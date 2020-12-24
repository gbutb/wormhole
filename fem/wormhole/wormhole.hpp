/**
 * wormhole.hpp
 * ------------
 * 
 * Contains T, S matrices for the wormhole.
 */

#ifndef FEM_WORMHOLE_WORMHOLE_HPP_
#define FEM_WORMHOLE_WORMHOLE_HPP_

#include <Eigen/Core>
#include <math.h>

typedef Eigen::MatrixXd Matrix;

class Wormhole {
 private:
    static float integralQii_minus1(double xi, double x, double a, double deltaX) {
        double A = pow(a, 3) * (x - 2 * xi + deltaX) + a * x * xi * (-xi + deltaX) - (pow(a,2) + pow(x,2))*(pow(a,2) + xi*(xi - deltaX))*atan(x/a);
        double B = 2 * a * (pow(a, 2) + pow(x, 2)) * pow(deltaX, 2);
        return a != 0 ? A / B : 0;
    }

    static float integralQii0(double xi, double x, double a, double deltaX) {
        double A = a * x * pow(xi - deltaX, 2) - pow(a, 3) * (x - 2 * xi + 2 * deltaX) + (pow(a, 2) + pow(x, 2)) * (pow(a, 2) + pow(xi - deltaX, 2))*atan(x/a);
        double B = 2 * a * (pow(a, 2) + pow(x, 2)) * pow(deltaX, 2);
        return a != 0 ? A / B : 0;
    }

    static float integralQii1(double xi, double x, double a, double deltaX) {
        double A = a * x * pow(xi + deltaX, 2) + pow(a, 3) * (-x + 2 * (xi + deltaX)) + (pow(a, 2) + pow(x, 2)) * (pow(a, 2) + pow(xi + deltaX, 2))*atan(x/a);
        double B = 2 * a * (pow(a, 2) + pow(x, 2)) * pow(deltaX, 2);
        return a != 0 ? A / B : 0;
    }

 public:
    static Matrix getT(double stepSize, int N) {
        Matrix T = Matrix::Zero(N, N);
        T(0, 0) = 1.0;
        T(N - 1, N - 1) = 1.0;

        for (int i = 1; i < N - 1; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j)
                    T(i, j) = (2.0/3.0)*stepSize;
                if (i - j == 1 || i - j == -1)
                    T(i, j) = (1.0/6.0)*stepSize;
            }
        }

        return T;
    }

    static Matrix getQ(double r_radius, double a_radius, double stepSize, int N) {
        Matrix Q = Matrix::Zero(N, N);

        for (int i = 1; i < N - 1; ++i) {
            for (int j = 0; j < N - 1; ++j) {
                if (i == j) {
                    double xi = -r_radius + i * stepSize;
                    double xi_minus1 = xi - stepSize;
                    double xi_plus1 = xi + stepSize;

                    double B0 = integralQii0(xi, xi, a_radius, stepSize);
                    double A0 = integralQii0(xi, xi_minus1, a_radius, stepSize);

                    double B1 = integralQii1(xi, xi_plus1, a_radius, stepSize);
                    double A1 = integralQii1(xi, xi, a_radius, stepSize);
                    Q(i, j) = (B0 - A0) + (B1 - A1);
                } if (i - j == 1) {
                    double xi = -r_radius + i * stepSize;
                    double xi_minus1 = xi - stepSize;
                    double xi_plus1 = xi + stepSize;

                    double at_xi = integralQii_minus1(xi, xi, a_radius, stepSize);
                    double at_xi_minus1 = integralQii_minus1(xi, xi_minus1, a_radius, stepSize);
                    Q(i, j) = at_xi - at_xi_minus1;
                } if (j - i == 1) {
                    double xi = -r_radius + j * stepSize;
                    double xi_minus1 = xi - stepSize;
                    double xi_plus1 = xi + stepSize;

                    double at_xi = integralQii_minus1(xi, xi, a_radius, stepSize);
                    double at_xi1 = integralQii_minus1(xi, xi_minus1, a_radius, stepSize);
                    Q(i, j) = at_xi - at_xi1;
                }
            }
        }
        return Q;
    }

    // TODO use any a.
    static Matrix getS(double stepSize, int N) {
        Matrix S = Matrix::Zero(N, N);

        for (int i = 1; i < N - 1; ++i) {
            for (int j = 0; j < N - 1; ++j) {
                if (i == j)
                    S(i, j) = 2.0/stepSize;
                if (i - j == 1 || i - j == -1)
                    S(i, j) = -1.0/stepSize;
            }
        }
        return S;
    }
};

#endif  // FEM_WORMHOLE_WORMHOLE_HPP_
