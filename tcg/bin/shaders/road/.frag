#version 330

out vec4 OutColor;

in vec4 color;
in vec3 normal;
in vec2 texCoordRoad;
in vec2 texCoordMountain;

uniform sampler2D road;
uniform sampler2D light;

void main( void )
{
  OutColor =
    vec4(texture2D(road, texCoordRoad).rgb *
        (vec3(0.3, 0.3, 0.3) + vec3(max(dot(normal, normalize(vec3(-1.0, 0.5, 0.0))), 0.0))), 1.0);

  if (abs(texCoordRoad.x - 0.5) * 2 > 0.75)
  {
    float c = (abs(texCoordRoad.x - 0.5) * 2 - 0.75) * 4;
    OutColor = vec4(OutColor.rgb * (1 - c) + texture2D(light, texCoordMountain).rgb * c, 1.0);
  }
}
