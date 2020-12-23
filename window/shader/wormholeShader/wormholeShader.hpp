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

 public:
    WormholeShader();
    ~WormholeShader();

    /**
     *
     */
    void loadMatrix(const cv::Mat& matrix);

    void render();
};


#endif  // WINDOW_SHADER_WORMHOLESHADER_WORMHOLESHADER_HPP_
