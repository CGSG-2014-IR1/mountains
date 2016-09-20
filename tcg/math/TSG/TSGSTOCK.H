/***************************************************************
 * Copyright (C) 2011
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TSGSTOCK.H
 * PURPOSE     : Tough space graphics sub-library.
 *               Stock collector class module.
 * PROGRAMMER  : CGSG'2005-2006-2010-2011.
 *               Andrew Churinov,
 *               Dmitry Churinov,
 *               Grigoryev Konstantin,
 *               Ekimov Leonid.
 * LAST UPDATE : 05.04.2011 (from 09.01.2010, 25.02.2007)
 * NOTE        : Templates namespace 'tsg'.
 *               Based on
 *                 Tatyana Marchukova (stock) &
 *                 Valeriya Nikolaenko (stock) code.
 *                 (last updates 03.04.2005) 
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef _TSGSTOCK_H_
#define _TSGSTOCK_H_

#include <stdio.h>

/* Addition to 'tsg' namespace */
namespace tsg
{
  /* Container class declaration */
  template<class TYPE, UINT R = 1> class TStock
  {
  public:
    TYPE *Elements;        /* Pointer to first element */
    UINT NumOfElements;    /* Amount of filling elements */ 
    UINT MaxNumOfElements; /* Maximum of allocated element */

    /* Constructor */
    TStock( VOID ) : Elements(NULL), NumOfElements(0), MaxNumOfElements(0)
    {
    } /* End of 'TStock' constructor */

    /* Destructor */
    ~TStock( VOID )
    {
      delete[] Elements;
      Elements = NULL, NumOfElements = 0, MaxNumOfElements = 0;
    } /* End of '~TStock' destructor */

    /* Deleting allocated element in stock function.
     * ARGUMENTS:
     *   - pointer to deleting element:
     *       TYPE *DelEl; 
     * RETURNS: None.
     */
    VOID DeleteElement( TYPE *DelEl )
    {
      TYPE *NewMass = new TYPE[MaxNumOfElements - 1];
      INT i;

      for (i = 0; i < MaxNumOfElements - 1 && &Elements[i] != DelEl; i++)
        NewMass[i] = Elements[i];
      for (i = i; i < MaxNumOfElements - 1; i++)
        NewMass[i] = Elements[i + 1];
      MaxNumOfElements--;
      NumOfElements--;
      /* Freeing old data */
      if (Elements != NULL)
        delete Elements;

      Elements = NewMass;
    } /* End of 'DeleteElement' function */

    /* Deleting last allocated element in stock function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID DeleteLastElement( VOID )
    {
      DeleteElement(&Elements[NumOfElements - 1]);
      /*
      TYPE *LastEl;

      LastEl = Elements[MaxNumOfElements - 1];
      if (NumOfElements == MaxNumOfElements)
        NumOfElements--;
      MaxNumOfElements--;
      /* Freeing old data *
      if (LastEl != NULL)
        delete LastEl;
      */
    } /* End of 'DeleteLastElement' function */

    /* Deleting all allocated element in stock function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID DeleteAllElements( VOID )
    {
      if (Elements != NULL)
      {    
        delete[] Elements;
        NumOfElements = 0;
        MaxNumOfElements = 0;
        Elements = NULL;
      }
    } /* End of 'DeleteAllElements' function */

    /* Add a new element to stock function.
     * ARGUMENTS: 
     *   - new element:
     *       TYPE &NewElement;
     * RETURNS:
     *   (INT) Elements number.
     */
    INT Add( TYPE &NewElement )
    {
      /* If we need to have more memory */
      if (NumOfElements >= MaxNumOfElements)
      {
        TYPE *NewEl;
        INT i;

        NewEl = new TYPE[MaxNumOfElements + R];

        /* If not enough memory */
        if (NewEl == NULL)
          return -1;

        /* Copying data */
        for (i = 0; i < NumOfElements; i++)
          NewEl[i] = Elements[i];

        /* Freeing old data */
        if (Elements != NULL)
          delete[] Elements;

        Elements = NewEl;
        MaxNumOfElements += R;
      }
      Elements[NumOfElements] = NewElement;
      return NumOfElements++;
    } /* End of 'Add' function */

    /* Allocation memory for new elements function.
     * ARGUMENTS: 
     *   - number of new elements to be allocated:
     *       INT NumOfAllocation;
     * RETURNS:
     *   (INT) Number of elements for which memory allocated.
     */
    INT AllocAdd( INT NumOfAllocation )
    {
      INT NewMaxNum = NumOfElements + NumOfAllocation;

      /* If we need to have more memory */
      if (NewMaxNum > MaxNumOfElements)
      {
        TYPE *NewEl = new TYPE[NewMaxNum];

        /* If not enough memory */
        if (NewEl == NULL)
          return -1;

        if (Elements != NULL)
        {
          /* Copying old data */
          for (INT i = 0; i < NumOfElements; i++)
            NewEl[i] = Elements[i];

          /* Freeing old data */
          delete[] Elements;
        }

        Elements = NewEl;
        MaxNumOfElements = NewMaxNum;
      }

      return MaxNumOfElements;
    } /* End of 'Alloc' function */

    /* Clearing stock with reallocation memory function.
     * ARGUMENTS:
     *   - number of available elements after allocation:
     *       INT NumOfAllocation;
     * RETURNS:
     *   (INT) Number of elements for which memory allocated.
     */
    INT AllocNew( INT NumOfAllocation )
    {
      /* If we need to have more memory */
      if (NumOfAllocation > MaxNumOfElements)
      {
        /* Delete old memory */
        if (Elements != NULL)
          delete[] Elements;

        /* Allocating new memory */
        Elements = new TYPE[NumOfAllocation];

        /* If not enough memory */
        if (Elements == NULL)
          return -1;

        MaxNumOfElements = NumOfAllocation;
      }
      NumOfElements = 0;

      return MaxNumOfElements;
    } /* End of 'MemAlloc' function */

    /* Get element by index
     * ARGUMENTS: 
     *   - number stock element:
     *       const INT i;
     * RETURNS:
     *   (TYPE) Pointer to element.
     */
    TYPE & operator[]( const INT i )
    {
      return Elements[i];
    } /* End of 'operator[]' operator */

    /* Adding new element
     * ARGUMENTS: 
     *   - addition element:
     *       TYPE NewEl;
     */
    TStock & operator<<( TYPE NewEl )
    {
      Add(NewEl);
      return *this;
    } /* End of 'operator<<' operator */ 

    /* Stock sorting subfunction.
     * ARGUMENTS: 
     *   - left and right sort bound values:
     *       INT Left, Right;
     * RETURNS: None.
     */
    VOID SortLocal( INT Left, INT Right )
    {
      INT i, j;
      TYPE x;

      if (Left >= Right)
        return;
      i = Left;
      j = Right;
      x = Elements[(Left + Right) / 2];
     
      while (Left <= Right)
      {
        while (Elements[Left] < x)
          Left++;
        while (x < Elements[Right])
          Right--;
        if (Left <= Right)
        {
          if (Left != Right)
            Swap(Elements[Left], Elements[Right]);
          Left++;
          Right--;
        }
      }
      SortLocal(i, Right);
      SortLocal(Left, j);
    } /* End of 'SortLocal' function */

    /* Stock sorting function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Sort( VOID )
    {
      SortLocal(0, NumOfElements - 1);
    } /* End of 'Sort' function */

    /* Write stock in file function.
     * ARGUMENTS:
     *   - file to write:
     *       FILE *F;
     * RETURNS: None.
     */
    VOID Write( FILE *F )
    {
      fwrite(&NumOfElements, sizeof(UINT), 1, F);

      for (INT i = 0; i < NumOfElements; i++)
        Elements[i].Write(F);
    } /* End of 'Write' function */

    /* Read stock from file function.
     * ARGUMENTS:
     *   - file to read from:
     *       FILE *F;
     * RETURNS: None.
     */
    TStock & Read( FILE *F )
    {
      TYPE NewEl;
      UINT NumOfElem;

      fread(&NumOfElem, sizeof(UINT), 1, F);

      for (INT i = 0; i < NumOfElem; i++)
      {
        NewEl.Read(F);
        Add(NewEl);
      }
      return *this;
    } /* End of 'Read' function */
  }; /* End of 'TStock' class */
} /* End of 'tsg' namespace */

#endif /* _TSGSTOCK_H_ */

/* END OF 'TSGSTOCK.H' FILE */
