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

#include <opencv2/opencv.hpp>

int main(void) {
    ptr_Camera camera(new Camera(1280, 720));
    Window window("main", 1280, 720);
    window.attachCamera(camera);

    cv::Mat mat = cv::Mat::ones(cv::Size(100, 1), CV_32FC1);

    for (int i = 0; i < 100; ++i) {
        mat.at<float>(i) = sin(i / 100.0 * M_PI * 5.0);
    }

    MapShader mapShader(100, 100);
    WormholeShader wormholeShader;
    mapShader.loadMatrix(mat);

    int i = 0;
    while (window) {
        wormholeShader.loadMatrix(mat);
        wormholeShader.setMatrix("model", glm::value_ptr(window.getCamera()->getModel()));
        wormholeShader.setMatrix("projection", glm::value_ptr(window.getCamera()->getProjection()));
        wormholeShader.render();

        mapShader.setMatrix("model", glm::value_ptr(window.getCamera()->getModel()));
        mapShader.setMatrix("projection", glm::value_ptr(window.getCamera()->getProjection()));
        // mapShader.render();
    }
    return EXIT_SUCCESS;
}
