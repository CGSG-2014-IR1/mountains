#version 420

/* Input */
in vec3 Pos;

/* Output */
out vec4 OutCol;

/* Textures */
uniform sampler2D ExponentArray;
uniform sampler2D NoiseTex;

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

uniform int ISN;

void main( void )
{
  vec3 point = Pos;
  float step = 1.0 / 2048.0;
  float H = fBm(point);
  if (ISN == 0)
    gl_FragColor = vec4(H, H, H, 1);
  else
  {
    vec3 b1 = vec3(point.x + step, point.y, fBm(point + vec3(step, 0, 0)));
    vec3 b2 = vec3(point.x, point.y + step, fBm(point + vec3(0, step, 0)));
    point.z = fBm(point);
    vec3 N = normalize(cross(normalize(b1 - point), normalize(b2 - point)));
    //N *= sign(N.y);
    
    float c = dot(N, normalize(vec3(1, 1, 1)));
    gl_FragColor = vec4(c, c, c, 1);
    gl_FragColor = vec4(N, 1);
  }
  //gl_FragColor = vec4(0.6, 0.1, 0.1, 1);
} // End of 'main' function