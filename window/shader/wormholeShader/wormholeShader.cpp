/**
 * wormholeShader.cpp
 * ------------------
 * 
 * Implements WormholeShader.
 */

#include "wormholeShader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


WormholeShader::WormholeShader() : Shader::Shader(
    #include "vertex.vs"
    ,
    #include "fragment.fs"
) {
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
}

WormholeShader::~WormholeShader() {
    Shader::~Shader();
    glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
}

struct Point {
    float x, y, z;
};

#define num_points_r 100
#define num_points_theta 100
#define r_radius 1.0
#define a_radius 0.1


void WormholeShader::loadMatrix(const cv::Mat& matrix) {
    CV_Assert(matrix.type() == CV_32FC1);
    use();

    Point* points = (Point*)malloc(sizeof(Point)*num_points_r*num_points_theta);

    for (int r_id = 0; r_id < num_points_r; ++r_id) {
        double r = -r_radius + (r_id * r_radius * 2.0) / num_points_r;
        for (int theta_id = 0; theta_id < num_points_theta; ++theta_id) {
            double theta = (2.0 * M_PI * theta_id) / (num_points_theta - 1);

            points[theta_id + r_id*num_points_theta] = Point({
                .x = static_cast<float>(sqrt(pow(a_radius, 2) + pow(r, 2))*cos(theta)),
                .y = static_cast<float>(sqrt(pow(a_radius, 2) + pow(r, 2))*sin(theta)),
                .z = static_cast<float>(a_radius * acosh(sqrt(pow(r,2) + pow(a_radius, 2)) / a_radius)) * (r > 0 ? 1 : -1)
            });
        }
    }

    glBindVertexArray(_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Point)*num_points_r*num_points_theta, points, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    free(points);
}


void WormholeShader::render() {
    use();

    // Focus to current buffers
    glBindVertexArray(_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
            glEnableVertexAttribArray(0);
            for (int r_id = 0; r_id < num_points_r; ++r_id) {
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*) (r_id * num_points_theta * sizeof(Point)));
                glDrawArrays(GL_LINE_STRIP, 0, num_points_theta);
            }
            for (int theta_id = 0; theta_id < num_points_theta; ++theta_id) {
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, num_points_theta*sizeof(Point), (void*) (theta_id * sizeof(Point)));
                glDrawArrays(GL_LINE_STRIP, 0, num_points_r);
            }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
