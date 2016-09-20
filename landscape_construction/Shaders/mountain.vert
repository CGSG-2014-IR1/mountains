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
uniform mat4 MatrNWorld;

out vec2 texCoord;
out float id;

void main( void )
{
  if (InID == 0)
    gl_Position = MatrWVP *
      vec4(InPosition.x, texture2D(height, vec2(InPosition.x / 60, InPosition.z / 60)).y * 4, InPosition.z, 1);
  else
  {
    if (length(vec2(InPosition.x, InPosition.z) - InP1) == 0)
    {
      float h1 = texture2D(height, InH1).y * 4;
      if (h1 > 1.5)
        h1 *= 0.95;
      gl_Position = MatrWVP * vec4(InPosition.x, h1, InPosition.z, 1);
    }
    else
    {
      float h0 = texture2D(height, InH0).y * 4, h1 = texture2D(height, InH1).y * 4;
      if (h0 > 1.5)
        h0 *= 0.95;
      if (h1 > 1.5)
        h1 *= 0.95;
      float alpha = length(vec2(InPosition.x, InPosition.z) - InP0) / length(vec2(InPosition.x, InPosition.z) - InP1);
      gl_Position = MatrWVP * vec4(InPosition.x, (h0 + alpha * h1) / (1.0 + alpha), InPosition.z, 1);
    }
  }
  texCoord = vec2(InPosition.x / 60, InPosition.z / 60);
  id = float(InID);
}
