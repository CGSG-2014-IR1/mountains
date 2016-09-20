#version 330

out vec4 OutColor;

in vec2 texCoord;
in float id;

uniform sampler2D light;

void main( void )
{
  OutColor = vec4(texture2D(light, texCoord).rgb, 1.0);
}
