#version 420

/* Input */
layout (location = 0) in vec3 InPos;

/* Fragment shader pass data */
out vec3 Pos;

void main( void )
{
  Pos = vec3((InPos.xy + vec2(1, 1)) / 2 * 10, 0);

  gl_Position = vec4(InPos.xy, 0, 1);
} // End of 'main' function