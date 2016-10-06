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

uniform sampler2D TextureHeight;
uniform float Height;

out vec2 Tex;
out int Id;

out vec2 P0;
out vec2 P1;
out vec2 H0;
out vec2 H1;

void main( void )
{
  Id = InID;
  P0 = InP0;
  P1 = InP1;
  H0 = InH0;
  H1 = InH1;
  Tex = vec2(InPosition.x / 60, InPosition.z / 60);
  gl_Position = vec4(vec3(InPosition.x, texture2D(TextureHeight, Tex).a, InPosition.z), 1);
}
