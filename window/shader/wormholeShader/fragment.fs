R""(
#version 400

out vec4 FragColor;

in float value;
in float depth;

void main() {
    FragColor = vec4(2*vec3(3*value, value, (1-3*value)) / (1.0 + abs(depth)/10.0), 1.0f);
}

)""