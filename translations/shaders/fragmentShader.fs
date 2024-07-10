#version 330 core

in vec3 ourColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D obama;
uniform float textureChanger;

void main() {

    FragColor = texture(obama, TexCoord);
    //
}