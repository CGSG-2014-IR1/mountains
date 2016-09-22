#version 420

flat in vec3 Pos;

void main( void )
{
  gl_FragColor = mix(vec4(0.5, 0.5, 0.5, 1), vec4(1, 1, 1, 1), Pos.y);
  //gl_FragColor = vec4(N, 1);
} // End of 'main' function