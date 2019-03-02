#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexture;
uniform mat4 trans;
uniform mat4 view;
uniform mat4 projection;
out vec2 TextureCoord;
out vec3 color;
void main()
{
    gl_Position=trans*vec4(aPos,1.0);
    color=aColor;
    TextureCoord=aTexture;
}