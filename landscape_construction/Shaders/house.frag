#version 330

out vec4 OutColor;

in vec3 normal;
in vec2 texCoord;
flat in int id;

uniform sampler2D roof;
uniform sampler2D flat_roof;
uniform sampler2D wall;
uniform sampler2D window;
uniform sampler2D concrete;
uniform sampler2D concrete_panels;

void main( void )
{
  vec3 color;
  if (id == 0)
    color = texture2D(flat_roof, texCoord).rgb;
  else if (id == 1)
    color = texture2D(roof, texCoord).rgb;
  else if (id == 2)
    color = texture2D(wall, texCoord).rgb;
  else if (id == 3)
    color = texture2D(window, texCoord).rgb;
  else if (id == 4)
    color = texture2D(concrete_panels, texCoord).rgb;
  else if (id == 5)
    color = texture2D(concrete, texCoord).rgb;
  else
    color = vec3(0.0, 0.0, 1.0);
  OutColor = vec4(color * (vec3(0.1, 0.1, 0.1) + vec3(max(dot(normal, normalize(vec3(-1.0, 0.5, 0.0))), 0.0))), 1.0);
}
