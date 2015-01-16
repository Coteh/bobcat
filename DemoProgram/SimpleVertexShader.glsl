#version 330 core

uniform mat4 MVP;
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormals;
layout(location = 2) in vec2 vTexture;
layout(location = 3) in vec3 vColor;

// Output data will be sent to the fragment shader.
out vec4 v2f_color;



void main() {
    gl_Position = MVP * vec4(vPosition, 1);

    // The color of each vertex will be interpolated to produce the color of each fragment.
    v2f_color = vec4(vColor, 1);
}
