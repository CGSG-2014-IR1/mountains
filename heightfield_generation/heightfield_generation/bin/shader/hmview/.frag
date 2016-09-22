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
uniform sampler2D Texture4;

uniform float
  H, lacunarity, octaves, offset, gain;

const int BITS = 14;
const int SIZE = (1 << BITS);
const int MASK = (SIZE - 1);

float fmod( float a, float b )
{
  float r = int(a / b);
  return a - (b * r);
}

float Table( int i )
{
  return texelFetch(Texture1, ivec2(i, 0), 0).a;
}

int Perm( int i )
{
  return int(texelFetch(Texture1, ivec2(i, 1), 0).a);
}

float Fade( float x )
{
  return x * x * (3.0 - 2.0 * x);
}

int Index( int IndX, int IndY, int IndZ )
{
  return Perm((IndX + Perm((IndY + Perm(IndZ & MASK)) & MASK)) & MASK);
}

float Noise( float X, float Y, float Z )
{
  int ix, ix1, iy, iy1, iz, iz1;
  float fx, fy, fz;

  X = abs(X);
  Y = abs(Y);
  Z = abs(Z);

  ix = int(X) & MASK;
  ix1 = (ix + 1) & MASK;
  fx = Fade(fract(X));

  iy = int(Y) & MASK;
  iy1 = (iy + 1) & MASK;
  fy = Fade(fract(Y));

  iz = int(Z) & MASK;
  iz1 = (iz + 1) & MASK;
  fz = Fade(fract(Z));

  float
   ox = 1 - fx,
   oy = 1 - fy,
   oz = 1 - fz;
  return
    Table(Index( ix,  iy,  iz)) * ox * oy * oz +
    Table(Index(ix1,  iy,  iz)) * fx * oy * oz +
    Table(Index( ix, iy1,  iz)) * ox * fy * oz +
    Table(Index(ix1, iy1,  iz)) * fx * fy * oz +
    Table(Index( ix,  iy, iz1)) * ox * oy * fz +
    Table(Index(ix1,  iy, iz1)) * fx * oy * fz +
    Table(Index( ix, iy1, iz1)) * ox * fy * fz +
    Table(Index(ix1, iy1, iz1)) * fx * fy * fz;
}

float Exponent( int i )
{
  return texelFetch(Texture4, ivec2(i, 0), 0).a;
}

vec3 HColor( float t )
{
  t = max(0.0, min(t, 1));
  return texture2D(Texture2, vec2(t, 0)).rgb;
}

float fBm( vec3 point )
{
  float result, signal, weight;

  int i;

  signal = abs(Noise(point.x, point.y, point.z));
  signal = offset - signal;
  signal = signal * signal;
  result = signal;
  weight = 1.0;

  for (i = 1; i < octaves; i++)
  {
    point *= lacunarity;

    weight = max(0.0, min(1.0, signal * gain));

    signal = abs(Noise(point.x, point.y, point.z));
    signal = offset - signal;
    signal = signal * signal;
    signal *= weight;
    result += signal * Exponent(i);
  }
  return (result);
}

uniform float Time;

vec3 Fog( vec3 c )
{
  return mix(c, vec3(0.8, 0.8, 0.8), min(1.0, (Pos.x * Pos.x / 20 + Pos.z * Pos.z / 20)));
}

void main( void )
{
  vec3 c = HColor(Pos.y + 0.3 * Pos.y * (fBm(vec3(Pos.x * 90, Pos.y, Pos.z * 90))));
  vec3 N = texture2D(Texture3, Tex).rgb;
  c *= abs(dot(N, normalize(vec3(-1, -1, -1))));
  gl_FragColor = vec4(Fog(c), 1);
  //gl_FragColor = vec4(N, 1);
} // End of 'main' function