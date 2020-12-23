/**
 * wormhole.hpp
 * ------------
 * 
 * Contains T, S matrices for the wormhole.
 */

#ifndef FEM_WORMHOLE_WORMHOLE_HPP_
#define FEM_WORMHOLE_WORMHOLE_HPP_

#include <Eigen/Core>

typedef Eigen::MatrixXd Matrix;

class Wormhole {
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
