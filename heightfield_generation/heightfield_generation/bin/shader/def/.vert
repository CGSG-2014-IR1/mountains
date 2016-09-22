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
  Pos = InPos;
  Norm = InNorm;
  Col = InCol;
  Tex = InTex;

  gl_Position = (VP) * vec4(InPos.x, InPos.y, InPos.z, 1); 
  //  gl_Position = vec4(sin(Time), cos(Time), 0.5, 1);
} // End of 'main' function