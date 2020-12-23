/**
 * wormholeShader.hpp
 * ------------------
 * 
 * Renders wormhole.
 */

#ifndef WINDOW_SHADER_WORMHOLESHADER_WORMHOLESHADER_HPP_
#define WINDOW_SHADER_WORMHOLESHADER_WORMHOLESHADER_HPP_


#include <math.h>
#include <opencv2/opencv.hpp>
#include "window/shader/shader.hpp"

class WormholeShader : public Shader {
 private:
    // Buffers
    unsigned int _VBO, _VAO;

    int num_points_r;
    int num_points_theta;
    double r_radius;
    double a_radius;

 public:
    WormholeShader(int num_points_r = 100, int num_points_theta = 100, double r_radius = 1.0, double a_radius = 0.1);
    ~WormholeShader();

    /**
     *
     */
    void loadMatrix(const cv::Mat& matrix);

    void render();
};


#endif  // WINDOW_SHADER_WORMHOLESHADER_WORMHOLESHADER_HPP_
