/* Vitaly Galinsky & Ivan Reshetnyak */

#ifndef __noise_h_
#define __noise_h_

#include <cstdlib>

#include "../def.h"
#include "math.h"

#include <string>

namespace tcg
{
  namespace math
  {
    /* Perlin's noise representation class. */
    class noise
    {
    private:
      static const int BITS = 14;          // Noise table size in bits
      static const int SIZE = (1 << BITS); // Noise table size
      static const int MASK = (SIZE - 1);  // Mask for computing with module
      int RandSeed;                        // Current random value

      double Table[SIZE];                  // Noise table: random values for interpolation
      int Perm[SIZE];                      // Permutations table: noise table elements indices

      /* Permutated 1D index obtain function.
       * ARGUMENTS:
       *   - array index:
       *       int IndX;
       * RETURNS:
       *   (int) permutated index value.
       */
      int Index(int IndX)
      {
        return Perm[IndX & MASK];
      } /* End of 'Index1' function */

      /* Permutated 2D index obtain function.
       * ARGUMENTS:
       *   - array indices:
       *       int IndX, IndY;
       * RETURNS:
       *   (int) permutated index value.
       */
      int Index(int IndX, int IndY)
      {
        return Perm[(IndX + Perm[IndY & MASK]) & MASK];
      } /* End of 'Index2' function */

      /* Permutated 3D index obtain function.
       * ARGUMENTS:
       *   - array indices:
       *       int IndX, IndY, IndZ;
       * RETURNS:
       *   (int) permutated index value.
       */
      int Index(int IndX, int IndY, int IndZ)
      {
        return Perm[(IndX + Perm[(IndY + Perm[IndZ & MASK]) & MASK]) & MASK];
      } /* End of 'Index3' function */

      /* Permutated 4D index obtain function.
       * ARGUMENTS:
       *   - array indices:
       *       int IndX, IndY, IndZ, IndW;
       * RETURNS:
       *   (int) permutated index value.
       */
      int Index(int IndX, int IndY, int IndZ, int IndW)
      {
        return Perm[(IndX + Perm[(IndY + Perm[(IndZ + Perm[IndW & MASK]) & MASK]) & MASK]) & MASK];
      } /* End of 'Index4' function */

    public:
      /* Obtain noise table size.
       * ARGUMENTS: None.
       * RETURNS:
       *   (int) noise table size.
       */
      static int GetSize(VOID)
      {
        return SIZE;
      } /* End of 'GetSize' function */

      /* Obtain noise table value.
       * ARGUMENTS:
       *   - element index:
       *       int Index;
       * RETURNS:
       *   (double) noise table value.
       */
      double GetTable(int Index) const
      {
        return Table[Index];
      } /* End of 'GetTable' function */

      /* Obtain permutations table value.
       * ARGUMENTS:
       *   - element index:
       *       int Index;
       * RETURNS:
       *   (int) permutations table value.
       */
      int GetPerm(int Index)
      {
        return Perm[Index];
      } /* End of 'GetPerm' function */

      /* Constructor (noise and permision tables initialisation).
       * ARGUMENTS:
       *   - random seed start value:
       *       int RandomSeed;
       */
      noise(int RandomSeed = 30 * 59)
      {
        int Test = 0;

        srand(RandomSeed);
        for (int i = 0; i < SIZE; i++)
          Table[i] = rand0();
        for (int i = 0; i < SIZE; i++)
          Perm[i] = i;
        for (int i = 0; i < 30 * SIZE; i++)
        {
          int tmp, t1 = ::rand() & MASK, t2 = ::rand() & MASK;

          tmp = Perm[t1];
          Perm[t1] = Perm[t2];
          Perm[t2] = tmp;
        }
      } /* End of 'noise' constructor */

      /* Noise (one-dimensional) random value generation function.
       * ARGUMENTS:
       *   - noise function argument:
       *       double X;
       * RETURNS:
       *   (double) noise random value.
       */
      double Noise(double X)
      {
        int ix, ix1;
        double fx;

        if (X < 0)
          X = fmod(SIZE - X, SIZE);

        ix = (int)X & MASK;
        ix1 = (ix + 1) & MASK;
        fx = X - (int)X;
        fx = fx * fx * (3 - 2 * fx);

        return Table[Index(ix)] * (1 - fx) + Table[Index(ix1)] * fx;
      } /* End of 'Noise' function */

      /* Noise (two-dimensional) random value generation function.
       * ARGUMENTS:
       *   - noise function arguments:
       *       double X, Y;
       * RETURNS:
       *   (double) noise random value.
       */
      double Noise(double X, double Y)
      {
        int ix, ix1, iy, iy1;
        double fx, fy;

        if (X < 0)
          X = fmod(SIZE - X, SIZE);
        if (Y < 0)
          Y = fmod(SIZE - Y, SIZE);

        ix = (int)X & MASK;
        ix1 = (ix + 1) & MASK;
        fx = X - (int)X;
        fx = fx * fx * (3 - 2 * fx);

        iy = (int)Y & MASK;
        iy1 = (iy + 1) & MASK;
        fy = Y - (int)Y;
        fy = fy * fy * (3 - 2 * fy);

        return
          Table[Index(ix, iy)] * (1 - fx) * (1 - fy) +
          Table[Index(ix1, iy)] * fx * (1 - fy) +
          Table[Index(ix, iy1)] * (1 - fx) * fy +
          Table[Index(ix1, iy1)] * fx * fy;
      } /* End of 'Noise' function */

      /* Noise (three-dimensional) random value generation function.
       * ARGUMENTS:
       *   - noise function arguments:
       *       double X, Y, Z;
       * RETURNS:
       *   (double) noise random value.
       */
      double Noise(double X, double Y, double Z)
      {
        int ix, ix1, iy, iy1, iz, iz1;
        double fx, fy, fz;

        if (X < 0)
          X = fmod(SIZE - X, SIZE);
        if (Y < 0)
          Y = fmod(SIZE - Y, SIZE);
        if (Z < 0)
          Z = fmod(SIZE - Z, SIZE);

        ix = (int)X & MASK;
        ix1 = (ix + 1) & MASK;
        fx = X - (int)X;
        fx = fx * fx * (3 - 2 * fx);

        iy = (int)Y & MASK;
        iy1 = (iy + 1) & MASK;
        fy = Y - (int)Y;
        fy = fy * fy * (3 - 2 * fy);

        iz = (int)Z & MASK;
        iz1 = (iz + 1) & MASK;
        fz = Z - (int)Z;
        fz = fz * fz * (3 - 2 * fz);

        return
          Table[Index(ix, iy, iz)] * (1 - fx) * (1 - fy) * (1 - fz) +
          Table[Index(ix1, iy, iz)] * fx * (1 - fy) * (1 - fz) +
          Table[Index(ix, iy1, iz)] * (1 - fx) * fy * (1 - fz) +
          Table[Index(ix1, iy1, iz)] * fx * fy * (1 - fz) +
          Table[Index(ix, iy, iz1)] * (1 - fx) * (1 - fy) * fz +
          Table[Index(ix1, iy, iz1)] * fx * (1 - fy) * fz +
          Table[Index(ix, iy1, iz1)] * (1 - fx) * fy * fz +
          Table[Index(ix1, iy1, iz1)] * fx * fy * fz;
      } /* End of 'Noise' function */

      /* Noise (four-dimensional) random value generation function.
       * ARGUMENTS:
       *   - noise function arguments:
       *       double X, Y, Z, W;
       * RETURNS:
       *   (double) noise random value.
       */
      double Noise(double X, double Y, double Z, double W)
      {
        int ix, ix1, iy, iy1, iz, iz1, iw, iw1;
        double fx, fy, fz, fw;

        if (X < 0)
          X = fmod(SIZE - X, SIZE);
        if (Y < 0)
          Y = fmod(SIZE - Y, SIZE);
        if (Z < 0)
          Z = fmod(SIZE - Z, SIZE);
        if (W < 0)
          W = fmod(SIZE - W, SIZE);

        ix = (int)X & MASK;
        ix1 = (ix + 1) & MASK;
        fx = X - (int)X;
        fx = fx * fx * (3 - 2 * fx);

        iy = (int)Y & MASK;
        iy1 = (iy + 1) & MASK;
        fy = Y - (int)Y;
        fy = fy * fy * (3 - 2 * fy);

        iz = (int)Z & MASK;
        iz1 = (iz + 1) & MASK;
        fz = Z - (int)Z;
        fz = fz * fz * (3 - 2 * fz);

        iw = (int)W & MASK;
        iw1 = (iw + 1) & MASK;
        fw = W - (int)W;
        fw = fw * fw * (3 - 2 * fw);

        return
          Table[Index(ix, iy, iz, iw)] * (1 - fx) * (1 - fy) * (1 - fz) * (1 - fw) +
          Table[Index(ix1, iy, iz, iw)] * fx * (1 - fy) * (1 - fz) * (1 - fw) +
          Table[Index(ix, iy1, iz, iw)] * (1 - fx) * fy * (1 - fz) * (1 - fw) +
          Table[Index(ix1, iy1, iz, iw)] * fx * fy * (1 - fz) * (1 - fw) +
          Table[Index(ix, iy, iz1, iw)] * (1 - fx) * (1 - fy) * (1 - fw) * fz +
          Table[Index(ix1, iy, iz1, iw)] * fx * (1 - fy) * fz * (1 - fw) +
          Table[Index(ix, iy1, iz1, iw)] * (1 - fx) * fy * fz * (1 - fw) +
          Table[Index(ix1, iy1, iz1, iw)] * fx * fy * fz * (1 - fw) +
          Table[Index(ix, iy, iz, iw1)] * (1 - fx) * (1 - fy) * (1 - fz) * fw +
          Table[Index(ix1, iy, iz, iw1)] * fx * (1 - fy) * (1 - fz) * fw +
          Table[Index(ix, iy1, iz, iw1)] * (1 - fx) * fy * (1 - fz) * fw +
          Table[Index(ix1, iy1, iz, iw1)] * fx * fy * (1 - fz) * fw +
          Table[Index(ix, iy, iz1, iw1)] * (1 - fx) * (1 - fy) * fz * fw +
          Table[Index(ix1, iy, iz1, iw1)] * fx * (1 - fy) * fz * fw +
          Table[Index(ix, iy1, iz1, iw1)] * (1 - fx) * fy * fz * fw +
          Table[Index(ix1, iy1, iz1, iw1)] * fx * fy * fz * fw;
      } /* End of 'Noise' function */

      /* Noise (one-dimensional) random value (with turbulence) generation function.
       * ARGUMENTS:
       *   - noise function argument:
       *       double X;
       *   - number of turbulence steps (octaves)
       *       int Oct;
       * RETURNS:
       *   (double) noise random value.
       */
      double Turb(double X, int Oct)
      {
        double sum = 0, coef = 1, denum = 0;

        for (int i = 0; i < Oct; i++)
        {
          sum += Noise(X) / coef;
          denum += 1 / coef;
          X *= 2;
          coef *= 2;
        }
        return sum / denum;
      } /* End of 'Turb' function */

      /* Noise (two-dimensional) random value (with turbulence) generation function.
       * ARGUMENTS:
       *   - noise function arguments:
       *       double X, Y;
       *   - number of turbulence steps (octaves)
       *       int Oct;
       * RETURNS:
       *   (double) noise random value.
       */
      double Turb(double X, double Y, int Oct)
      {
        double sum = 0, coef = 1, denum = 0;

        for (int i = 0; i < Oct; i++)
        {
          sum += Noise(X, Y) / coef;
          denum += 1 / coef;
          X *= 2;
          Y *= 2;
          coef *= 2;
        }
        return sum / denum;
      } /* End of 'Turb' function */

      /* Noise (three-dimensional) random value (with turbulence) generation function.
       * ARGUMENTS:
       *   - noise function arguments:
       *       double X, Y, Z;
       *   - number of turbulence steps (octaves)
       *       int Oct;
       * RETURNS:
       *   (double) noise random value.
       */
      double Turb(double X, double Y, double Z, int Oct)
      {
        double sum = 0, coef = 1, denum = 0;

        for (int i = 0; i < Oct; i++)
        {
          sum += Noise(X, Y, Z) / coef;
          denum += 1 / coef;
          X *= 2;
          Y *= 2;
          Z *= 2;
          coef *= 2;
        }
        return sum / denum;
      } /* End of 'Turb' function */

      /* Noise (three-dimensional) random value (with turbulence) generation function.
       * ARGUMENTS:
       *   - noise function arguments:
       *       double X, Y, Z;
       *   - number of turbulence steps (octaves)
       *       int Oct;
       * RETURNS:
       *   (double) noise random value.
       */
      vec TurbNorm(double X, double Z, int Oct)
      {
        vec p = vec(X, Turb(X, Z, Oct), Z);
        return ((vec(X, Turb(X, Z + math::ThresholdFloat, Oct), Z + math::ThresholdFloat) - p) %
                (vec(X + math::ThresholdFloat, Turb(X + math::ThresholdFloat, Z, Oct), Z) - p)).Normalizing();
      } /* End of 'TurbNorm' function */

      /* Noise (four-dimensional) random value (with turbulence) generation function.
       * ARGUMENTS:
       *   - noise function arguments:
       *       double X, Y, Z, W;
       *   - number of turbulence steps (octaves)
       *       int Oct;
       * RETURNS:
       *   (double) noise random value.
       */
      double Turb(double X, double Y, double Z, double W, int Oct)
      {
        double sum = 0, coef = 1, denum = 0;

        for (int i = 0; i < Oct; i++)
        {
          sum += Noise(X, Y, Z, W) / coef;
          denum += 1 / coef;
          X *= 2;
          Y *= 2;
          Z *= 2;
          W *= 2;
          coef *= 2;
        }
        return sum / denum;
      } /* End of 'Turb' function */
    }; /* End of 'noise' class */

    class fBm_multi_ridged
    {
    private:
      noise Noise;
      int Octaves;
      double *Exponents, Dimension, Lacunarity, Offset, Gain;

    public:
      fBm_multi_ridged(double Dimension, double Lacunarity,
                       double Gain, double Offset = 0,
                       int Octaves = 8, int Seed = 30 * 59) :
                       Noise(Seed), Octaves(Octaves), Lacunarity(Lacunarity), Dimension(Dimension), Offset(Offset), Gain(Gain)
      {
        double frequency = 1.0;
        Exponents = new double[Octaves];
        for (int i = 0; i < Octaves; i++)
        {
          Exponents[i] = pow(frequency, -Dimension);
          frequency *= Lacunarity;
        }
      }

      double operator()(vec Point)
      {
        float result, signal, weight;

        int i;

        signal = fabs(Noise.Noise(Point.X, Point.Y, Point.Z));
        signal = Offset - signal;
        signal = signal * signal;
        result = signal;
        weight = 1.0;

        for (i = 1; i < Octaves; i++)
        {
          Point *= Lacunarity;

          weight = Maximal({0.0, Minimal({1.0, signal * Gain})});

          signal = fabs(Noise.Noise(Point.X, Point.Y, Point.Z));
          signal = Offset - signal;
          signal = signal * signal;
          signal *= weight;
          result += signal * Exponents[i];
        }
        return (result);
      }

      ~fBm_multi_ridged(void)
      {
        delete[] Exponents;
      }
    }; /* End of 'fBm_multi_ridged' class */
  } /* End of 'math' namespace */
} /* End of 'tcg' namespace */
#endif /* __noise_h_ */

/* END OF 'noise.h' FILE */
