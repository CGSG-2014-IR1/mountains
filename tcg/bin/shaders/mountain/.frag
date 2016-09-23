#version 330

out vec4 OutColor;

in vec2 Tex;

uniform sampler2D Texture;
uniform sampler2D TextureHeight;

void main( void )
{
  OutColor = vec4(texture2D(TextureHeight, Tex).aaa, 1.0);
}
