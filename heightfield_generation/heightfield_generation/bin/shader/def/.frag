#version 420

/* Input */
in vec3 Pos;
in vec3 Norm;
in vec4 Col;
in vec2 Tex;

/* Output */
out vec4 OutCol;

/* Matrixes */
uniform mat4 ViewProj;

/* Textures */
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;

/* Phong */
uniform vec4 Ka;
uniform vec4 Kd;
uniform vec4 Ks;

uniform float Time;

void main( void )
{
  float d = sqrt(dFdx(Pos.y) * dFdx(Pos.y) + dFdy(Pos.y) * dFdy(Pos.y)) +
    sqrt(dFdx(Pos.x) * dFdx(Pos.x) + dFdy(Pos.x) * dFdy(Pos.x)) +
    sqrt(dFdx(Pos.z) * dFdx(Pos.z) + dFdy(Pos.z) * dFdy(Pos.z));

  gl_FragColor = vec4(vec3(d, d, d) * 10, 1);
  gl_FragColor = vec4(Norm, 1);
} // End of 'main' function