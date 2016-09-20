#version 330

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec3 InNormal;
layout(location = 2) in vec4 InColor;
layout(location = 3) in vec2 InTexCoord;
layout(location = 4) in vec2 InHeight;
layout(location = 5) in int  InID;
layout(location = 6) in vec2 InP0;
layout(location = 7) in vec2 InP1;
layout(location = 8) in vec2 InH0;
layout(location = 9) in vec2 InH1;

uniform sampler2D height;

uniform mat4 MatrWVP;

out vec4 color;
out vec3 normal;
out vec2 texCoordRoad;
out vec2 texCoordMountain;

void main( void )
{
  float h = texture2D(height, InHeight).y * 4;
  if (h > 1.5)
    h *= 0.95;
  gl_Position = MatrWVP * vec4(InPosition.x, h, InPosition.z, 1);
  vec3
    n0 = normalize(vec3(InP0.x - InPosition.x,
                        texture2D(height, InH0).y * 4 - texture2D(height, InHeight).y * 4,
                        InP0.y - InPosition.z)),
    n1 = normalize(vec3(InP1.x - InPosition.x,
                        texture2D(height, InH1).y * 4 - texture2D(height, InHeight).y * 4,
                        InP1.y - InPosition.z));
  float sqrt0 = sqrt(n0.x * n0.x + n0.z * n0.z), sqrt1 = sqrt(n1.x * n1.x + n1.z * n1.z);
  n0 = vec3(-n0.x * n0.y / sqrt0, sqrt0, -n0.y * n0.z / sqrt0);
  n1 = vec3(-n1.x * n1.y / sqrt1, sqrt1, -n1.y * n1.z / sqrt1);
  normal = normalize(n0 + n1);
  texCoordRoad = InTexCoord;
  texCoordMountain = vec2(InPosition.x / 60, InPosition.z / 60);
}
