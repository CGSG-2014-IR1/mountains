#version 420

/* Input */
layout (location = 0) in vec3 InPos;
layout (location = 1) in vec3 InNorm;
layout (location = 2) in vec4 InCol;
layout (location = 3) in vec2 InTex;

/* Fragment shader pass data */
out vec3 Pos;
out vec3 Norm;
out vec4 Col;
out vec2 Tex;

/* Time */
uniform float Time;
uniform mat4 View;
uniform mat4 Proj;
uniform mat4 VP;

void main( void )
{
  Pos = vec3(InPos.xy, 0) * (2 + sin(Time));
  Norm = InNorm;
  Col = InCol;
  Tex = InTex;

  gl_Position = vec4(InPos.xy, 0, 1);
  //  gl_Position = vec4(sin(Time), cos(Time), 0.5, 1);
} // End of 'main' function