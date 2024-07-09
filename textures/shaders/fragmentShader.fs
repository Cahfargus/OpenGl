#version 330 core

in vec3 ourColor;
in vec2 TexCoord;
in vec2 FlagCoord;
out vec4 FragColor;

uniform sampler2D fnick;
uniform sampler2D fflag;
uniform float textureChanger;

void main() {
    vec2 mirrorNick;
    mirrorNick = vec2(1 - TexCoord.x, TexCoord.y);
    FragColor = mix(texture(fnick, mirrorNick), texture(fflag, FlagCoord), textureChanger);
}