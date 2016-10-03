#version 330

out vec4 OutColor;

in vec2 Tex;
in vec3 Pos;

uniform sampler2D Texture;
uniform sampler2D TextureHeight;
uniform sampler2D ColorMap;
uniform sampler2D NormalMap;
uniform sampler2D ExponentArray;
uniform sampler2D NoiseTex;
uniform float Height;

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
  return texelFetch(NoiseTex, ivec2(i, 0), 0).a;
}

int Perm( int i )
{
  return int(texelFetch(NoiseTex, ivec2(i, 1), 0).a);
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
  return texelFetch(ExponentArray, ivec2(i, 0), 0).a;
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

vec3 HColor( float h )
{
  h = min(1, max(0, h));
  return texture2D(ColorMap, vec2(h, 0.5)).rgb;
}

void main( void )
{
  vec3 c = HColor(Pos.y / Height + 0.3 * Pos.y / Height * fBm(Pos * 10));
  vec3 n = texture2D(NormalMap, Tex).rgb;
  vec3 d = normalize(vec3(1, 1, 1));
  c *= abs(dot(n, d));
  OutColor = vec4(c, 1.0);
}
