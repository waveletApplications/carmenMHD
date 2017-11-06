/***************************************************************************
                          Vector.h  -  description
                             -------------------
    begin                : Thu Jun 7 2001
    copyright            : (C) 2001 by Olivier Roussel & Alexei Tsigulin
    email                : roussel@ict.uni-karlsruhe.de, lpsoft@mail.ru
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


/**
 * @file Vector.h
 * @class Vector
 * @brief Standard class for every vector in Carmen.
 *
 * It contains the following data:<br>
 * * the dimension of the vector <i>Columns</i> ;<br>
 * * the array of reals <i>*U</i>.
 * 
 */
class Vector
{

/*
______________________________________________________________________________________________

	Constructor and distructor
______________________________________________________________________________________________

*/


public:
  /**
   * @brief Generates a 1D vector equal to zero.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V;
   * 
   */
  Vector();

/**
 * @brief Generates a vector of dimension <i>n</i>, each component being equal to zero.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(4);
 * 
 * @param n 
 */
Vector(const int n);

/**
 * @brief Generates the 2D vector (<i>x,y</i>).
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(0.,1.);
 * 
 * @param x Real value
 * @param y Real value
 */
Vector(const real x, const real y);

/**
 * @brief Generates the 3D vector (<i>x,y,z</i>).
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(0.,1.,0.);
 * 
 * @param x Real value
 * @param y Real value
 * @param z Real value
 */
Vector(const real x, const real y, const real z);

/**
 * @brief .Generates a copy of the vector <i>V</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(0.,1.,0.);<br>
 * Vector W(V);
 * 
 * @param V Vector
 */
Vector(const Vector& V);

/**
 * @brief Destructor of Vector Class.
 * 
 */
~Vector();   /*!<Deallocate memory of the vector. */
/*
______________________________________________________________________________________________

	Set and get
______________________________________________________________________________________________

*/


/**
 * @brief Sets the component <i>n</i> to value <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(2);<br>
 * real x = 3.;<br>
 * real y = 1.;<br>
 * V.setValue(1,x);<br>
 * V.setValue(2,y);
 * 
 * @param n Variable number
 * @param a Real value
 * @return void
 */
inline void setValue(const int n, const real a);

/**
 * @brief Sets all the components to zero.
 * 
 * @return void
 */
void setZero();

/**
 * @brief Sets the dimension of the vector to <i>n</i> and reset values to zero.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V;<br>
 * ...    <br>
 * V.setDimension(3); <br>
 * 
 * @param n Dimension
 * @return void
 */
void setDimension(const int n);

/**
 * @brief Returns the value of the component <i>n</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(2);<br>
 * real x;<br>
 * real y;<br>
 * ...    <br>
 * x = V.value(1); <br>
 * y = V.value(2); <br>
 * 
 * @param n Integer
 * @return real
 */
inline real value(const int n) const;

/**
 * @brief Returns the dimension of the vector.
 * 
 * @return int
 */
inline int dimension() const;


/*
______________________________________________________________________________________________

	Operators
______________________________________________________________________________________________

*/

/**
 * @brief Compares the current vector to a vector <i>V</i> and returns true if they are equal.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(2);<br>
 * Vector W(2);<br>
 * real x; <br>
 * ...    <br>
 * if (V == W) <br>
 *    x = V.value(1); <br>
 * 
 * @param V Vector
 * @return bool
 */
bool operator== (const Vector& V ) const;

/**
 * @brief Set the current vector to the dimension and the value of <i>V</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * Vector W; <br>
 * ...    <br>
 * W = V; <br>
 * 
 * @param V Vector
 * @return void
 */
void operator= (const Vector& V );

/**
 * @brief Adds <i>V</i> to the current vector.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * Vector W(0.,-1.,2.); <br>
 * ...    <br>
 * W += V; <br>
 * 
 * @param V Vector
 * @return void
 */
void operator+=(const Vector& V );

/**
 * @brief Returns the addition of the current vector and <i>V</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * Vector W(0.,-1.,2.); <br>
 * Vector U; <br>
 * ...    <br>
 * U = V + W;
 * 
 * @param V Vector
 * @return Vector
 */
Vector operator+ (const Vector& V ) const;

/**
 * @brief Subtracts <i>V</i> to the current vector.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * Vector W(0.,-1.,2.); <br>
 * ...    <br>
 * W -= V; <br>
 * 
 * @param V Vector
 * @return void
 */
void operator-=(const Vector& V );

/**
 * @brief Returns the difference between the current vector and <i>V</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * Vector W(0.,-1.,2.); <br>
 * Vector U; <br>
 * ...    <br>
 * U = V - W; <br>
 * 
 * @param V Vector
 * @return Vector
 */
Vector operator- (const Vector& V ) const;

/**
 * @brief Returns the opposite of the current vector.
 *
 * Example 
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * Vector W; <br>
 * ...    <br>
 * W = -V; <br>
 * 
 * @return Vector
 */
Vector operator- () const;

/**
 * @brief Multiplies the current vector by a real <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * real x = 2.; <br>
 * ...    <br>
 * V *= x; <br>
 * 
 * @param a Real value
 * @return void
 */
void operator*=(const real a );

/**
 * @brief Returns the product of the current vector and a real <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * Vector W;  <br>
 * real x = 2.; <br>
 * ...    <br>
 * W = V*x; <br>
 *
 * The operation W = x*V can also be done. See <b>operator*(const real a, const Vector& V)</b>.
 * 
 * @param a Real value
 * @return Vector
 */
Vector operator* (const real a ) const;

/**
 * @brief Divides the current vector by a real <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * real x = 2.; <br>
 * ...    <br>
 * V /= x; <br>
 * 
 * @param a Real value
 * @return void
 */
void operator/=(const real a );

/**
 * @brief Returns the division of the current vector by a real <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * Vector W; <br>
 * real x = 2.; <br>
 * ...    <br>
 * W = V / x; <br>
 * 
 * @param a Real value
 * @return Vector
 */
Vector operator/ (const real a ) const;

/**
 * @brief Returns the dot product of the current vector and <i>V</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * Vector W(1., 2., 1.);<br>
 * real x; <br>
 * ...    <br>
 * x = V*W; <br>
 * 
 * @param V Vector
 * @return real
 */
real operator* (const Vector& V ) const;
	
/**
 * @brief Returns the term-by-term product of the current vector and <i>V</i>.
 * 
 * @param V Vector
 * @return Vector
 */
Vector operator| (const Vector& V) const;

/**
 * @brief Returns the vectorial product of the current vector and <i>V<i>.
 * 
 * @param V Vector
 * @return Vector
 */
Vector operator^ (const Vector& V) const;

/**
 * @brief Returns true if one of the components of the current vector is not a number.
 * 
 * @return bool
 */
bool isNaN() const;

/*
______________________________________________________________________________________________

PRIVATE VARIABLES
______________________________________________________________________________________________

*/
//parallel modification
//private:
public:
	int  Columns; 	/*!< Number of columns */
	/* real *U;	// Components */
	real U[9];	/*!< Components */
};
/*
______________________________________________________________________________________________

EXTERNAL FUNCTIONS
______________________________________________________________________________________________

*/

/**
 * @brief Returns the product of the current vector and a real <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Vector.h"
 *
 * <tt>Vector V(1.,0.,0.);<br>
 * Vector W;  <br>
 * real x = 2.; <br>
 * ...    <br>
 * W = x*V; <br>
 *
 * The operation W = V*x can also be done. See <b>Vector Vector::operator*(const real a) const</b>.
 * 
 * @param a Real value
 * @param V Vector
 * @return Vector
 */
Vector operator* (const real a, const Vector& V);

/**
 * @brief Returns the absolute value term by term of the vector.
 * 
 * @param V Vector
 * @return Vector
 */
Vector abs (const Vector& V);

/**
 * @brief Returns the dimension of the vector. Similar to <b>int Vector::dimension()</b>.
 * 
 * @param V Vector
 * @return int
 */
int dim (const Vector& V);

/**
 * @brief Returns the L1-norm of the vector.
 * 
 * @param V Vector
 * @return real
 */
real N1(const Vector& V);

/**
 * @brief Returns the L2-norm of the vector.
 * 
 * @param V Vector
 * @return real
 */
real N2(const Vector& V);

/**
 * @brief Returns the Max-norm of the vector.
 * 
 * @param V Vector
 * @return real
 */
real NMax(const Vector& V);

/**
 * @brief Writes the components of the vector <i>V</i> on screen.
 * 
 * @param out 
 * @param V Vector
 * @return ostream&
 */
ostream& operator<<(ostream& out, const Vector& V);

/*
______________________________________________________________________________________________

INLINE FUNCTIONS
______________________________________________________________________________________________

*/
inline int Vector::dimension() const
{
	return Columns;
}

/*
______________________________________________________________________________________________

*/

inline void Vector::setValue(const int n, const real a)
{

#ifdef DEBUG
	if ( n <= 0 || n > Columns)
	{
		cout << "Vector.cpp: In method `void Vector::setValue(int, real)':\n";
		cout << "Vector.cpp: first argument out of range\n";
		cout << "carmen: *** [Vector.o] Execution error\n";
		cout << "carmen: abort execution.\n";
		exit(1);
	}
#endif

		*(U+n-1) = a;
}
/*
______________________________________________________________________________________________

*/
inline real Vector::value(const int n) const
{

#ifdef DEBUG

	if ( n <= 0 || n > Columns)
	{
		cout << "Vector.cpp: In method `void Vector::value(int)':\n";
		cout << "Vector.cpp: argument out of range\n";
		cout << "carmen: *** [Vector.o] Execution error\n";
		cout << "carmen: abort execution.\n";
		exit(1);
	}
#endif

	return *(U+n-1);
}

