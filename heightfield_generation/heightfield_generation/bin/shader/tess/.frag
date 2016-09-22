#version 420

/* Input */
in vec3 Pos;
in vec2 Tex;
flat in float Road;

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
uniform vec3 CameraPos;
           	
uniform float Time;

void main( void )
{
  vec3 Norm = normalize(cross(dFdy(Pos), dFdx(Pos)));
  Norm *= sign(dot(Norm, Pos - CameraPos));

  if (Road == 1)
    OutCol = texture2D(Texture1, Tex);
  else
    OutCol = 
      vec4((texture2D(Texture0, Pos.xz).rgb * abs(Norm.y) +
           texture2D(Texture0, Pos.xy).rgb * abs(Norm.z) +
           texture2D(Texture0, Pos.yz).rgb * abs(Norm.x)) / 3.0, 1);
    
} // End of 'main' function