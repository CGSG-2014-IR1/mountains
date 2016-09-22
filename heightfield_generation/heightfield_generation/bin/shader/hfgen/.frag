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
  return texelFetch(Texture0, ivec2(i, 0), 0).a;
}

vec3 HColor( float t )
{
  t = max(0.0, min(t, 0.99));
  vec3 cols[5] =
    {
      {0.6, 0.1, 0.1},
      {0.3, 0.1, 0.7},
      {0.8, 0.2, 0.3},
      {0.4, 0.8, 0.5},
      {0.0, 0.0, 0.0}
    };
  int size = 5;

  int it = min(int(t * size), size - 1);
  vec3
    f = cols[it],
    s = cols[min(it + 1, size - 1)];
  float r = (t * size) - int(t * size);
  return mix(f, s, r);
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

void main( void )
{
  vec3 point = Pos + vec3(Time, Time, 0);
  float H = fBm(point);
  gl_FragColor = vec4(HColor(H + 0.1 * fBm(vec3(point.x, H, point.y))), 1);
} // End of 'main' function