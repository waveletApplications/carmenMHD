/***************************************************************************
                          Matrix.h  -  description
                             -------------------
    begin                : mer fév 11 2004
    copyright            : (C) 2004 by Olivier Roussel and Alexei Tsigulin
    email                : roussel@ict.uni-karlsruhe.de; lpsoft@mail.ru
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/** @file Matrix.h
 * \class Matrix
 * \brief Standard class for every matrix in Carmen.
 *
 * It contains the following data:<br>
 * the number of lines <i>Lines</i> ;<br>
 * the number of columns <i>Columns</i> ;<br>
 * the array of reals <i>*U</i>.
 * 
 */
class Matrix
{

/*
______________________________________________________________________________________________

	Constructor and distructor
______________________________________________________________________________________________

*/

public:
  /**
   * @brief Constructor of matrix class.
   * Generates a 1,1 matrix equal to zero.
   *
   * Example :
   *
   * <tt>#include "Matrix.h"
   *
   * <tt>Matrix M;
   * 
   * 
   */
  Matrix();

/**
 * @brief Generates a matrix with <i>i</i> lines and <i>j</i> columns, each component being equal to zero.
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(4,5);
 * @param i 
 * @param j 
 */
Matrix(const int i, const int j);

/**
 * @brief Generates a square matrix with <i>i</i> lines and <i>i</i> columns, each component being equal to zero.
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(4);
 * 
 * @param i 
 */
Matrix(const int i);

/**
 * @brief Generates a copy of the matrix <i>M</i>.
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,3);<br>
 * Matrix P(M)
 * 
 * @param M Matrix
 */
Matrix(const Matrix& M);

/**
 * @brief Generates a vector-matrix identical to <i>V</i>.
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix V(3);<br>
 * Matrix P(V);
 * 
 * @param V 
 */
Matrix(const Vector& V);

/**
 * @brief Distructor of matrix class.
 * Deallocate memory of the matrix
 * 
 */
~Matrix();
/*
______________________________________________________________________________________________

	Set and get
______________________________________________________________________________________________

*/

/**
 * @brief Sets the component <i>i, j</i> to value <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * real x = 3.;<br>
 * real y = 1.;<br>
 * M.setValue(1,1,x);<br>
 * M.setValue(2,1,y);
 * 
 * @param i Position
 * @param j Position
 * @param a Value
 * @return void
 */
inline void setValue(const int i, const int j, const real a);

/**
 * @brief Sets all the components to zero.
 * 
 * @return void
 */
void setZero();

/**
 * @brief Returns the value of the component <i>i, j</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * real x;<br>
 * real y;<br>
 * ...    <br>
 * x = M.value(1,1); <br>
 * y = M.value(2,1); <br>
 * 
 * @param i 
 * @param j 
 * @return real
 */
inline real value(const int i, const int j) const;

/**
 * @brief Returns the number of lines of the matrix.
 * 
 * @return int
 */
inline int lines() const;

/**
 * @brief Returns the number of columns of the matrix.
 * 
 * @return int
 */
inline int columns() const;
/*
______________________________________________________________________________________________

	Operators
______________________________________________________________________________________________

*/

/**
 * @brief Compares the current matrix to a matrix <i>M</i> and returns true if they are equal.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * Matrix P(2,2);<br>
 * real x; <br>
 * ...    <br>
 * if (M == P) <br>
 *    x = M.value(1,1); <br>
 * 
 * @param M Matrix
 * @return bool
 */
bool operator== (const Matrix& M ) const;

/**
 * @brief Set the current matrix to the dimension and the value of <i>M</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * Matrix P; <br>
 * ...    <br>
 * P = M; <br>
 * 
 * @param M Matrix
 * @return void
 */
void operator= (const Matrix& M );

/**
 * @brief Adds <i>M</i> to the current matrix.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * Matrix P(2,2); <br>
 * ...    <br>
 * P += M; <br>
 * 
 * @param M Matrix
 * @return void
 */
void operator+=(const Matrix& M );

/**
 * @brief Returns the addition of the current matrix and <i>M</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * Matrix P(2,2); <br>
 * Matrix U; <br>
 * ...    <br>
 * U = M + P;
 * 
 * @param M Matrix
 * @return Matrix
 */
Matrix operator+ (const Matrix& M ) const;

/**
 * @brief Subtracts <i>M</i> to the current matrix.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * Matrix P(2,2); <br>
 * ...    <br>
 * P -= M; <br>
 * 
 * @param M Matrix
 * @return void
 */
void operator-=(const Matrix& M );

/**
 * @brief Returns the difference between the current matrix and <i>M</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * Matrix P(2,2); <br>
 * Matrix U; <br>
 * ...    <br>
 * U = M - P; <br>
 * 
 * @param M Matrix
 * @return Matrix
 */
Matrix operator- (const Matrix& M ) const;

/**
 * @brief Returns the opposite of the current matrix.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * Matrix P; <br>
 * ...    <br>
 * P = -M; <br>
 * 
 * @return Matrix
 */
Matrix operator- () const;

/**
 * @brief Multiplies the current matrix by a real <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * real x = 2.; <br>
 * ...    <br>
 * M *= x; <br>
 * 
 * @param a Real value
 * @return void
 */
void operator*=(const real a );

/**
 * @brief Returns the product of the current matrix and a real <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * Matrix P;  <br>
 * real x = 2.; <br>
 * ...    <br>
 * P = M*x; <br>
 *
 * The operation P = x*M can also be done. See <b>operator*(const real a, const Matrix& M)</b>.
 * 
 * @param a Real value
 * @return Matrix
 */
Matrix operator* (const real a ) const;

/**
 * @brief Divides the current matrix by a real <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * real x = 2.; <br>
 * ...    <br>
 * M /= x; <br>
 * 
 * @param a Real value
 * @return void
 */
void operator/=(const real a );

/**
 * @brief Returns the division of the current matrix by a real <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,2);<br>
 * Matrix P; <br>
 * real x = 2.; <br>
 * ...    <br>
 * P = M / x; <br>
 * 
 * @param a Real value
 * @return Matrix
 */
Matrix operator/ (const real a ) const;

/**
 * @brief Returns the product of the current matrix and a matrix <i>M</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,3);<br>
 * Matrix P(3,1);<br>
 * Matrix Q; <br>
 * ...    <br>
 * Q = M*P; <br>
 * 
 * @param M Matrix
 * @return Matrix
 */
Matrix operator* (const Matrix& M ) const;

/**
 * @brief Returns the product of the current matrix and a vector<i>V</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(2,3);<br>
 * Vector V(3);<br>
 * Vector P; <br>
 * ...    <br>
 * P = M*V; <br>
 * 
 * @param V Vector
 * @return Vector
 */
Vector operator* (const Vector& V) const;

/**
 * @brief Sets matrix as eigenmatrix.
 * 
 * @param isLeft Boolean variable. True if location is on the left.
 * @param AxisNo Axis of interest.
 * @param V Vector
 * @param c Real value
 * @param h Real value
 * @return void
 */
void setEigenMatrix(const bool isLeft, const int AxisNo, const Vector V, const real c, const real h=0.);
/*
______________________________________________________________________________________________

PRIVATE VARIABLES
______________________________________________________________________________________________

*/
//parallel modification
//private:
public:
  int  Lines, Columns; 	/*!<Lines and columns of the matrix*/
	real *U;	/*!< Components */
};

/*
______________________________________________________________________________________________

EXTERNAL FUNCTIONS
______________________________________________________________________________________________

*/

/**
 * @brief Returns the product of the current matrix and a real <i>a</i>.
 *
 * Example :
 *
 * <tt>#include "Matrix.h"
 *
 * <tt>Matrix M(5,3);<br>
 * Matrix P;  <br>
 * real b = 2.; <br>
 * ...    <br>
 * P = b*M; <br>
 *
 * The operation P = M*b can also be done. See <b>Matrix Matrix::operator*(const real a) const</b>.
 * 
 * @param a Real value
 * @param M Matrix
 * @return Matrix
 */
Matrix operator* (const real a, const Matrix& M);

/**
 * @brief Writes the components of the matrix <i>M</i> on screen.
 * 
 * @param out 
 * @param M Matrix
 * @return ostream&
 */
ostream& operator<<(ostream& out, const  Matrix& M);

/*
______________________________________________________________________________________________

INLINE FUNCTIONS
______________________________________________________________________________________________
*/

inline int Matrix::lines() const
{
	return Lines;
}
/*
______________________________________________________________________________________________

*/

inline int Matrix::columns() const
{
	return Columns;
}

/*
______________________________________________________________________________________________

*/

inline void Matrix::setValue(const int i, const int j, const real a)
{
		*( U + (i-1)*Columns + (j-1) ) = a;
}

/*
______________________________________________________________________________________________

*/

inline real Matrix::value(const int i, const int j) const
{
		return *(U+(i-1)*Columns+(j-1));
}

