#version 330 core
out vec4 myColor;
in vec3 color;
in vec2 TextureCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform float val;
uniform float alpha;
void main()
{
       //myColor=mix(texture(texture1,vec2(TextureCoord.x,-TextureCoord.y)),texture(texture2,vec2(TextureCoord.x,-TextureCoord.y)),alpha);
        myColor=texture(texture1,vec2(TextureCoord.x,-TextureCoord.y))+texture(texture2,vec2(TextureCoord.x,-TextureCoord.y))+texture(texture3,vec2(TextureCoord.x,-TextureCoord.y));
}