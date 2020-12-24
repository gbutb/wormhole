/**
 * main.cpp
 * --------
 */

#include <stdio.h>
#include <stdlib.h>

#include <window/window.hpp>
#include <window/shader/mapShader/mapShader.hpp>
#include <window/shader/wormholeShader/wormholeShader.hpp>
#include <fem/FEMSolver.hpp>
#include <fem/wormhole/wormhole.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>

int main(void) {
    // Initialize window
    ptr_Camera camera(new Camera(1280, 720));
    Window window("main", 1280, 720);
    window.attachCamera(camera);

    // Initialize shader
    int num_points_r = 100;
    double r_radius = 1.0;
    double a_radius = 1.0;
    WormholeShader wormholeShader(num_points_r, num_points_r, r_radius, a_radius);

    // Initialize solver
    double stepSize = (2.0*r_radius) / (num_points_r - 1.0);
    Eigen::MatrixXd T = Wormhole::getT(stepSize, num_points_r);
    Eigen::MatrixXd S = Wormhole::getS(stepSize, num_points_r);
    FEMSolver solver(T, S);

    // Initialize initial condition
    Vector u = Vector::Zero(num_points_r);
    for (int i = 0; i < num_points_r; ++i) {
        u(i) = pow(sin(M_PI * i * stepSize), 2);
    }
    solver.setInitialConditions(u, u);

    // Graphics
    cv::Mat mat;
    while (window) {
        cv::eigen2cv(solver.getCurrentU(), mat);
        mat *= 1.0;
        wormholeShader.loadMatrix(mat);
        wormholeShader.setMatrix("model", glm::value_ptr(window.getCamera()->getModel()));
        wormholeShader.setMatrix("projection", glm::value_ptr(window.getCamera()->getProjection()));
        solver.singleStep();
        wormholeShader.render();
    }
    return EXIT_SUCCESS;
}
