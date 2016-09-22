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

out vec3 normal;
out vec2 texCoord;
flat out int id;

void main( void )
{
  if (InID == 6)
  {
    float h = texture2D(height, vec2(InPosition.x / 60, InPosition.z / 60)).y * 4;
    gl_Position = MatrWVP * vec4(InPosition.x, h, InPosition.z, 1);
    texCoord = vec2(InTexCoord.x, (0.4 + texture2D(height, InHeight).y * 4 - h) * 5 / 2);
    id = 5;
  }
  else
  {
    gl_Position = MatrWVP * vec4(InPosition.x, InPosition.y + texture2D(height, InHeight).y * 4, InPosition.z, 1);
    texCoord = vec2(InTexCoord.x, -InTexCoord.y);
    id = InID;
  }
  normal = InNormal;
}
