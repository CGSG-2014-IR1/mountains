/***************************************************************
 * Copyright (C) 2011
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TSGCOLOR.H
 * PURPOSE     : Tough Space Graphics library.
 *               Color class template declaration module.
 * PROGRAMMER  : CGSG'2004-2005-2006-2011.
 *               Bob Rutsky,
 *               Artemiy Sergeev (HSV color model support),
 *               Andrey Bazhenov.
 * LAST UPDATE : 22.10.2015 (from 05.04.2011)
 * NOTE        : Templates namespace 'tsg'.
 *               Based on
 *                 Tatyana Marchukova (vector & matrices) &
 *                 Valeriya Nikolaenko (camera) code.
 *                 (last updates 25.03.2005 & 20.05.2005) 
 *               Based on TSGRAPH project from 'C' library.
 *                 (last updates 2004/2003/1999, original 1998)
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef _TSGCOLOR_H_
#define _TSGCOLOR_H_

namespace tsg
{
  /* Red, green, blue and transparent components color class */
  template <class TYPE> class TColor
  {
  public: 
    /* Red, green, blue and transparent components */
    TYPE R, G, B, A;

    /* Empty class constructor */
    explicit TColor( VOID ) : R(0), G(0), B(0), A(1)
    {
    } /* End of 'TColor' constructor */

    /* Main color class constructor.
     * ARGUMENTS:
     *   - red, green, blue and alpha components:
     *       TYPE NewR, NewG, NewB, NewA;
     */
    explicit TColor( TYPE NewR, TYPE NewG, TYPE NewB, TYPE NewA = 1 ) :
      R(NewR), G(NewG), B(NewB), A(NewA)
    {
    } /* End of 'TColor' constructor */

    /* Color class constructor.
     * ARGUMENTS:
     *   - components, that will be red, green and blue:
     *       TYPE Value;
     */
    explicit TColor( TYPE Value ) : R(Value), G(Value), B(Value), A(1)
    {
    } /* End of 'TColor' constructor */

    /* Class constructor.
     * ARGUMENTS:
     *   - components link to DWORD type (0-255 range):
     *       DWORD Value;
     */
    explicit TColor( DWORD Value ) :
      R(((Value >> 16) & 0xFF) / 255.0), G(((Value >> 8) & 0xFF) / 255.0),
      B((Value & 0xFF) / 255.0), A(((Value >> 24) & 0xFF) / 255.0)
    {
    } /* End of 'TColor' constructor */

    /* Addition colors function.
     * ARGUMENTS: 
     *   - color which will be added:
     *       const TColor & Color;
     * RETURNS:
     *   (TColor) result color.
     */
    TColor operator+( const TColor &Color ) const
    {
      return TColor(R + Color.R, G + Color.G, B + Color.B, A + Color.A);
    } /* End of 'operator+' function */

    /* Addition colors with assignment function.
     * ARGUMENTS:
     *   - color to add:
     *       const TColor &Color;
     * RETURNS: 
     *   (TColor &) self-reference to color.
     */
    TColor & operator+=( const TColor &Color )
    {
      R += Color.R;
      G += Color.G;
      B += Color.B;
      A += Color.A;
      return *this;
    } /* End of 'operator+=' function */

    /* Subtraction colors function.
     * ARGUMENTS: 
     *   - color which will be subtracted:
     *       const TColor &Color;
     * RETURNS:
     *   (TColor) result color.
     */
    TColor operator-( const TColor &Color ) const
    {
      return TColor(R - Color.R, G - Color.G, B - Color.B, A - Color.A);
    } /* End of 'operator-' function */

    /* Subtraction colors with assignment function.
     * ARGUMENTS:
     *   - color to subtract:
     *       const TColor &Color;
     * RETURNS: 
     *   (TColor &) result color.
     */
    TColor & operator-=( const TColor &Color )
    {
      R -= Color.R;
      G -= Color.G;
      B -= Color.B;
      A -= Color.A;
      return *this;
    } /* End of 'operator-=' function */

    /* Multiply color by number function.
     * ARGUMENTS: 
     *   - number to multiply on:
     *       TYPE n;
     * RETURNS:
     *   (TColor) result color.
     */
    TColor operator*( TYPE n ) const
    {
      return TColor(R * n, G * n, B * n, A * n);
    } /* End of 'operator*' function */

    /* Multiply color by number with assignment function.
     * ARGUMENTS:
     *   - number to multiply on:
     *       TYPE Value;
     * RETURNS: 
     *   (TColor &) self-reference to color.
     */
    TColor & operator*=( TYPE Value )
    {
      R *= Value;
      G *= Value;
      B *= Value;
      A *= Value;
      return *this;
    } /* End of 'operator*=' function */

    /* Multiply color by color function.
     * ARGUMENTS: 
     *   - color to multiply on:
     *       const TColor &Color;
     * RETURNS:
     *   (TColor) result color.
     */
    TColor operator*( const TColor &Color ) const
    {
      return TColor(R * Color.R, G * Color.G, B * Color.B, A * Color.A);
    } /* End of 'operator*' function */

    /* Multiply color by color with assignment function.
     * ARGUMENTS:
     *   - color to multiply on:
     *       const TColor &Color;
     * RETURNS: 
     *   (TColor &) self-reference to color.
     */         
    TColor & operator*=( const TColor &Color )
    {
      R *= Color.R;
      G *= Color.G;
      B *= Color.B;
      A *= Color.A;
      return *this;
    } /* End of 'operator*=' function */

    /* Divide color by coefficient function.
     * ARGUMENTS: 
     *   - coefficient to divide on:
     *       TYPE Value;
     * RETURNS:
     *   (TColor) result color.
     */
    TColor operator/( TYPE Value ) const
    {
      return TColor(R / Value, G / Value, B / Value, A / Value);
    } /* End of 'operator/' function */

    /* Divide color by coefficient with assignment function.
     * ARGUMENTS:
     *   - coefficient to divide on:
     *       TYPE Value;             
     * RETURNS: 
     *   (TColor &) self-reference to color.
     */
    TColor & operator/=( TYPE Value )
    {
      R /= Value;
      G /= Value;
      B /= Value;
      A /= Value;
      return *this;
    } /* End of 'operator/=' function */    

    /* Determine maximum component function.
     * ARGUMENTS: None.
     * RETURNS: 
     *   (TYPE) maximum component value.
     */
    TYPE Max( VOID ) const
    {
      if (R > G)
        if (B > R)
          return B;
        else
          return R;
      else
        if (B > G)
          return B;
        else
          return G;
    } /* End of 'Max' function */

    /* Setting color function.
     * ARGUMENTS:
     *   - red, green, blue and alpha components:
     *       TYPE NewR, NewG, NewB, NewA;
     * RETURNS: None.
     */
    VOID SetColor( TYPE NewR, TYPE NewG, TYPE NewB, TYPE NewA = 1 )
    {
      R = NewR;
      G = NewG;
      B = NewB;
      A = NewA;
    } /* End of 'SetColor' function */

    /* Clamp color function.
     *   - minimal vector value:
     *       TYPE Min;
     *   - maximum vector value:
     *       TYPE Max;
     * RETURNS:
     *   (TColor &) self-reference to color.
     */
    TColor & Clamp( TYPE Min = 0, TYPE Max = 1 )
    {
      if (R < Min)
        R = Min;
      else
        if (R > Max)
          R = Max;
      if (G < Min)
        G = Min;
      else
        if (G > Max)
          G = Max;
      if (B < Min)
        B = Min;
      else
        if (B > Max)
          B = Max;
      return *this;
    } /* End of 'Clamp' function */

    /* Clamp color function.
     *   - minimal vector value:
     *       TYPE Min;
     *   - maximum vector value:
     *       TYPE Max;
     * RETURNS:
     *   (TColor) clamped color.
     */
    TColor Clamping( TYPE Min = 0, TYPE Max = 1 ) const
    {
      return Vec(R < Min ? Min : R > Max ? Max : R,
                 G < Min ? Min : G > Max ? Max : G,
                 B < Min ? Min : B > Max ? Max : B);
    } /* End of 'Clamping' function */

    /* Converting color to DWORD type function
     * ARGUMENTS: None.
     * RETURNS:
     *   (DWORD) DWORD color.
     */
    DWORD ToDWORD( VOID ) const
    {
      DBL
        v0 = B * 255, v1 = G * 255, v2 = R * 255, v3 = A * 255;
      BYTE
        B0 = v0 > 255 ? 255 : v0 < 0 ? 0 : v0,
        B1 = v1 > 255 ? 255 : v1 < 0 ? 0 : v1,
        B2 = v2 > 255 ? 255 : v2 < 0 ? 0 : v2,
        B3 = v3 > 255 ? 255 : v3 < 0 ? 0 : v3;

      return COM_MAKELONG0123(B0, B1, B2, B3);
    } /* End of 'ToDWORD' function */

    /* Converting color to DWORD type function
     * ARGUMENTS: None.
     * RETURNS:
     *   (DWORD) DWORD color.
     */
    operator DWORD( VOID ) const
    {
      return ToDWORD();
    } /* End of 'operator DWORD' function */

    /* Type conversion to HSV model function.
     * ARGUMENTS: None
     * RETURNS: 
     *   (TColor &) self-reference to result color (in HSV color mode).
     * NOTE: new components interpretation:
     *   R - Hue degree between 0.0 and 360.0, 
     *   G - Saturation between 0.0 (gray) and 1.0, 
     *   B - Value between 0.0 (black) and 1.0, 
     */
    TColor & ToHSV( VOID )
    {
      TYPE Max, Min;
      TYPE OldR, OldG, OldB;

      /* Normalisation color */
      while (R > 1)
        R /= 255.0;
      while (G > 1)
        G /= 255.0;
      while (B > 1)
        B /= 255.0;

      OldR = R, OldG = G, OldB = B;

      /* Minimum and maximum components search */
      Max = COM_MAX(R, COM_MAX(G, B));
      Min = COM_MIN(R, COM_MIN(G, B));

      /* Calculate value */
      B = Max;
      if (B == 0) 
      {
        R = G = 0;
        return *this;
      }   

      /* Caluculate saturation */
      G = 1 - Min / Max;

      /* Calculate hue angle in degree */
      if (Max == OldR) 
      {         
        R = 0.0 + 60.0 * (OldG - OldB) / (Max - Min);
        if (R < 0.0) 
        {
          R += 360.0;
        }
      }
      else if (Max  == OldG) 
      {
        R = 120.0 + 60.0 * (OldB - OldR) / (Max - Min);
      }
      else /* Max == OldB */ 
      {
        R = 240.0 + 60.0 * (R - G) / (Max - Min);
      }
      return *this;
    } /* End of 'ToHSV' function */

    /* Type conversion to RGB model function.
     * ARGUMENTS:
     *   - hue angle in degree [0; 360]:
     *       TYPE Hue;
     * RETURNS: 
     *   (TColor) result color (in RGB color mode).
     */
    static TColor ToRGB( TYPE Hue )
    {
      TYPE t;
      TColor Result;
      
      if (Hue < 61)
      {
        Result.R = 255;
        Result.G = 255 * Hue / 60;
        Result.B = 0;
      }
      else if (Hue >= 61 && Hue < 120)
      {
        t = (Hue - 60) / 60.0;
        Result.R = 255 * (1 - t);
        Result.G = 255;
        Result.B = 0;
      }
      else if (Hue >= 120 && Hue < 180)
      {
        t = (Hue - 120) / 60.0;
        Result.R = 0;
        Result.G = 255;
        Result.B = 255 * t;
      }
      else if (Hue >= 180 && Hue < 240)
      {
        t = (Hue - 180) / 60.0;
        Result.R = 0;
        Result.G = 255 * (1 - t);
        Result.B = 255;
      }
      else if (Hue >= 240 && Hue < 300)
      {
        t = (Hue - 240) / 60.0;
        Result.R = 255 * t;
        Result.G = 0;
        Result.B = 255;
      }
      else 
      {
        t = (Hue - 300) / 60.0;
        Result.R = 255;
        Result.G = 0;                
        Result.B = 255 * (1 - t);
      }

      while (Result.R > 1)
        Result.R /= 255.0;
      while (Result.G > 1)
        Result.G /= 255.0;
      while (Result.B > 1)
        Result.B /= 255.0;
      return Result;
    } /* End of 'ToRGB' function */

    TYPE & operator[]( INT Index )
    {
      return *(&B + Index);
    }

    TYPE operator[]( INT Index ) const
    {
      return *(&R + Index);
    }
  }; /* End of 'TColor' class */

  /* Red, green and blue components color class */
  template <class TYPE> class TColor3
  {
  public: 
    /* Red, green and blue components */
    TYPE R, G, B;

    /* Empty class constructor */
    explicit TColor3( VOID ) : R(0), G(0), B(0)
    {
    } /* End of 'TColor3' constructor */

    /* Main color class constructor.
     * ARGUMENTS:
     *   - red, green and blue components:
     *       TYPE NewR, NewG, NewB;
     */
    explicit TColor3( TYPE NewR, TYPE NewG, TYPE NewB ) :
      R(NewR), G(NewG), B(NewB)
    {
    } /* End of 'TColor3' constructor */

    /* Color class constructor.
     * ARGUMENTS:
     *   - components, that will be red, green and blue:
     *       TYPE Value;
     */
    explicit TColor3( TYPE Value ) : R(Value), G(Value), B(Value)
    {
    } /* End of 'TColor3' constructor */

    /* Addition colors function.
     * ARGUMENTS: 
     *   - color which will be added:
     *       const TColor3 & Color;
     * RETURNS:
     *   (TColor3) result color.
     */
    TColor3 operator+( const TColor3 &Color ) const
    {
      return TColor3(R + Color.R, G + Color.G, B + Color.B);
    } /* End of 'operator+' function */

    /* Addition colors with assignment function.
     * ARGUMENTS:
     *   - color to add:
     *       const TColor3 &Color;             
     * RETURNS: 
     *   (TColor3 &) self-reference to color.
     */
    TColor3 & operator+=( const TColor3 &Color )
    {
      R += Color.R;
      G += Color.G;
      B += Color.B;
      return *this;
    } /* End of 'operator+=' function */

    /* Subtraction colors function.
     * ARGUMENTS: 
     *   - color which will be subtracted:
     *       const TColor3 &Color;
     * RETURNS:
     *   (TColor3) result color.
     */
    TColor3 operator-( const TColor3 &Color ) const
    {
      return TColor3(R - Color.R, G - Color.G, B - Color.B);
    } /* End of 'operator-' function */

    /* Subtraction colors with assignment function.
     * ARGUMENTS:
     *   - color to subtract:
     *       const TColor3 &Color;             
     * RETURNS: 
     *   (TColor3 &) result color.
     */
    TColor3 & operator-=( const TColor3 &Color )
    {
      R -= Color.R;
      G -= Color.G;
      B -= Color.B;
      return *this;
    } /* End of 'operator-=' function */

    /* Multiply color by number function.
     * ARGUMENTS: 
     *   - number to multiply on:
     *       TYPE n;
     * RETURNS:
     *   (TColor3) result color.
     */
    TColor3 operator*( TYPE n ) const
    {
      return TColor3(R * n, G * n, B * n);
    } /* End of 'operator*' function */

    /* Multiply color by number with assignment function.
     * ARGUMENTS:
     *   - number to multiply on:
     *       TYPE Value;             
     * RETURNS: 
     *   (TColor3 &) self-reference to color.
     */
    TColor3 & operator*=( TYPE Value )
    {
      R *= Value;
      G *= Value;
      B *= Value;
      return *this;
    } /* End of 'operator*=' function */

    /* Multiply color by color function.
     * ARGUMENTS: 
     *   - color to multiply on:
     *       const TColor3 &Color;
     * RETURNS:
     *   (TColor3) result color.
     */
    TColor3 operator*( const TColor3 &Color ) const
    {
      return TColor3(R * Color.R, G * Color.G, B * Color.B);
    } /* End of 'operator*' function */

    /* Multiply color by color with assignment function.
     * ARGUMENTS:
     *   - color to multiply on:
     *       const TColor3 &Color;             
     * RETURNS: 
     *   (TColor3 &) self-reference to color.
     */         
    TColor3 & operator*=( const TColor3 &Color )
    {
      R *= Color.R;
      G *= Color.G;
      B *= Color.B;
      return *this;
    } /* End of 'operator*=' function */

    /* Divide color by coefficient function.
     * ARGUMENTS: 
     *   - coefficient to divide on:
     *       TYPE Value;
     * RETURNS:
     *   (TColor3) result color.
     */
    TColor3 operator/( TYPE Value ) const
    {
      return TColor3(R / Value, G / Value, B / Value);
    } /* End of 'operator/' function */

    /* Divide color by coefficient with assignment function.
     * ARGUMENTS:
     *   - coefficient to divide on:
     *       TYPE Value;             
     * RETURNS: 
     *   (TColor3 &) self-reference to color.
     */
    TColor3 & operator/=( TYPE Value )
    {
      R /= Value;
      G /= Value;
      B /= Value;
      return *this;
    } /* End of 'operator/=' function */

    /* Determine maximum component function.
     * ARGUMENTS: None.
     * RETURNS: 
     *   (TYPE) maximum component value.
     */
    TYPE Max( VOID ) const
    {
      if (R > G)
        if (B > R)
          return B;
        else
          return R;
      else
        if (B > G)
          return B;
        else
          return G;
    } /* End of 'Max' function */

    /* Setting color function.
     * ARGUMENTS:
     *   - red, green, blue and alpha components:
     *       TYPE NewR, NewG, NewB;
     * RETURNS: None.
     */
    VOID SetColor( TYPE NewR, TYPE NewG, TYPE NewB )
    {
      R = NewR;
      G = NewG;
      B = NewB;
    } /* End of 'SetColor' function */

    /* Clamp color function.
     *   - minimal vector value:
     *       TYPE Min;
     *   - maximum vector value:
     *       TYPE Max;
     * RETURNS:
     *   (TColor3 &) self-reference to color.
     */
    TColor3 & Clamp( TYPE Min = 0, TYPE Max = 1 )
    {
      if (R < Min)
        R = Min;
      else
        if (R > Max)
          R = Max;
      if (G < Min)
        G = Min;
      else
        if (G > Max)
          G = Max;
      if (B < Min)
        B = Min;
      else
        if (B > Max)
          B = Max;
      return *this;
    } /* End of 'Clamp' function */

    /* Clamp color function.
     *   - minimal vector value:
     *       TYPE Min;
     *   - maximum vector value:
     *       TYPE Max;
     * RETURNS:
     *   (TColor3) clamped color.
     */
    TColor3 Clamping( TYPE Min = 0, TYPE Max = 1 ) const
    {
      return Vec(R < Min ? Min : R > Max ? Max : R,
                 G < Min ? Min : G > Max ? Max : G,
                 B < Min ? Min : B > Max ? Max : B);
    } /* End of 'Clamping' function */

    /* Converting color to DWORD type function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (DWORD) DWORD color.
     */
    DWORD ToDWORD( VOID ) const
    {
      DBL
        v0 = B * 255, v1 = G * 255, v2 = R * 255;
      BYTE
        B0 = v0 > 255 ? 255 : v0 < 0 ? 0 : v0,
        B1 = v1 > 255 ? 255 : v1 < 0 ? 0 : v1,
        B2 = v2 > 255 ? 255 : v2 < 0 ? 0 : v2;

      return COM_MAKELONG0123(B2, B1, B0, 255);
    } /* End of 'ToDWORD' function */

    /* Converting color to DWORD type function
     * ARGUMENTS: None.
     * RETURNS:
     *   (DWORD) DWORD color.
     */
    operator DWORD( VOID ) const
    {
      return ToDWORD();
    } /* End of 'operator DWORD' function */

    /* Type conversion to HSV model function.
     * ARGUMENTS: None
     * RETURNS: 
     *   (TColor3 &) self-reference to result color (in HSV color mode).
     * NOTE: new components interpretation:
     *   R - Hue degree between 0.0 and 360.0, 
     *   G - Saturation between 0.0 (gray) and 1.0, 
     *   B - Value between 0.0 (black) and 1.0, 
     */
    TColor3 & ToHSV( VOID )
    {
      TYPE Max, Min;
      TYPE OldR, OldG, OldB;

      /* Normalisation color */
      while (R > 1)
        R /= 255.0;
      while (G > 1)
        G /= 255.0;
      while (B > 1)
        B /= 255.0;

      OldR = R, OldG = G, OldB = B;

      /* Minimum and maximum components search */
      Max = COM_MAX(R, COM_MAX(G, B));
      Min = COM_MIN(R, COM_MIN(G, B));

      /* Calculate value */
      B = Max;
      if (B == 0) 
      {
        B = Result.V = 0;
        return Result;
      }   

      /* Caluculate saturation */
      G = 1 - Min / Max;

      /* Calculate hue angle in degree */
      if (Max == OldR) 
      {         
        R = 0.0 + 60.0 * (OldG - OldB) / (Max - Min);
        if (Result.H < 0.0) 
        {
          Result.H += 360.0;
        }
      }
      else if (Max  == OldG) 
      {
        R = 120.0 + 60.0 * (OldB - OldR) / (Max - Min);
      }
      else /* Max == OldB */ 
      {
        R = 240.0 + 60.0 * (R - G) / (Max - Min);
      }
      return *this;
    } /* End of 'ToHSV' function */

    /* Type conversion to RGB model function.
     * ARGUMENTS:
     *   - hue angle in degree [0; 360]:
     *       TYPE Hue;
     * RETURNS: 
     *   (TColor3 ) result color (in RGB color mode).
     */
    static TColor3 ToRGB( TYPE Hue )
    {
      TYPE t;
      TColor3 Result;      
      
      if (Hue < 61)
      {
        Result.R = 255;
        Result.G = 255 * Hue / 60;
        Result.B = 0;
      }
      else if (Hue >= 61 && Hue < 120)
      {
        t = (Hue - 60) / 60.0;
        Result.R = 255 * (1 - t);
        Result.G = 255;
        Result.B = 0;
      }
      else if (Hue >= 120 && Hue < 180)
      {
        t = (Hue - 120) / 60.0;
        Result.R = 0;
        Result.G = 255;
        Result.B = 255 * t;
      }
      else if (Hue >= 180 && Hue < 240)
      {
        t = (Hue - 180) / 60.0;
        Result.R = 0;
        Result.G = 255 * (1 - t);
        Result.B = 255;
      }
      else if (Hue >= 240 && Hue < 300)
      {
        t = (Hue - 240) / 60.0;
        Result.R = 255 * t;
        Result.G = 0;
        Result.B = 255;
      }
      else 
      {
        t = (Hue - 300) / 60.0;
        Result.R = 255;
        Result.G = 0;                
        Result.B = 255 * (1 - t);
      }

      while (Result.R > 1)
        Result.R /= 255.0;
      while (Result.G > 1)
        Result.G /= 255.0;
      while (Result.B > 1)
        Result.B /= 255.0;
      return Result;
    }
  }; /* End of 'TColor3' class */  
} /* End of 'tsg' namespace */

#endif /* _TSGCOLOR_H_ */

/* END OF 'TSGCOLOR.H' FILE */
