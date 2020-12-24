R""(
#version 400

// layout (location = 0) in float value;
layout (location = 0) in vec4 aPos;

uniform mat4 model;
uniform mat4 projection;

uniform int width;
uniform int height;

out float value;
out float depth;

void main() {
    vec4 position = model * vec4(aPos.y, aPos.z, aPos.x, 1.0);
    value = aPos.w;
    depth = position.z;
	gl_Position = projection *  position;
}

)""