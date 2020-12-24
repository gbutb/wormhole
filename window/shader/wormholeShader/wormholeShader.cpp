/**
 * wormholeShader.cpp
 * ------------------
 * 
 * Implements WormholeShader.
 */

#include "wormholeShader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


WormholeShader::WormholeShader(
        int num_points_r, int num_points_theta, double r_radius, double a_radius) :
            num_points_r(num_points_r), num_points_theta(num_points_theta), r_radius(r_radius), a_radius(a_radius), Shader::Shader(
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
    float value;
};


void WormholeShader::loadMatrix(const cv::Mat& matrix) {
    CV_Assert(matrix.type() == CV_32FC1 || matrix.type() == CV_64FC1);
    CV_Assert(matrix.rows == num_points_r);
    use();

    Point* points = (Point*)malloc(sizeof(Point)*num_points_r*num_points_theta);

    for (int r_id = 0; r_id < num_points_r; ++r_id) {
        double r = -r_radius + (r_id * r_radius * 2.0) / (num_points_r - 1);
        for (int theta_id = 0; theta_id < num_points_theta; ++theta_id) {
            double theta = (2.0 * M_PI * theta_id) / (num_points_theta - 1);

            double offset = pow(matrix.at<double>(r_id), 2);
            points[theta_id + r_id*num_points_theta] = Point({
                .x = static_cast<float>(sqrt(pow(a_radius, 2) + pow(r, 2) + offset)*cos(theta)),
                .y = static_cast<float>(sqrt(pow(a_radius, 2) + pow(r, 2) + offset)*sin(theta)),
                .z = static_cast<float>(a_radius * acosh(sqrt(pow(r,2) + pow(a_radius, 2)) / a_radius)) * (r > 0 ? 1 : -1),
                .value = static_cast<float>(offset)
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
                glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Point), (void*) (r_id * num_points_theta * sizeof(Point)));
                glDrawArrays(GL_LINE_STRIP, 0, num_points_theta);
            }
            for (int theta_id = 0; theta_id < num_points_theta; ++theta_id) {
                glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, num_points_theta*sizeof(Point), (void*) (theta_id * sizeof(Point)));
                glDrawArrays(GL_LINE_STRIP, 0, num_points_r);
            }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
