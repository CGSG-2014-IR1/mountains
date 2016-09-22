#version 330

out vec4 OutColor;

in vec2 texCoord;
in float id;

uniform sampler2D light;
uniform sampler2D height;

void main( void )
{
  OutColor = vec4(texture2D(height, texCoord).aaa, 1.0);
}
