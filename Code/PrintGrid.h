/***************************************************************************
                          PrintGrid.h  -  description
                             -------------------
    begin                : Tue Mar 19 2002
    copyright            : (C) 2002 by Olivier Roussel & Alexei Tsigulin
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

/** @file PrintGrid.h
 * \class PrintGrid
 * \brief An object PrintGrid is a special regular grid created to write
 * tree-structured data into an output file.
 *
 * It contains the following data: <br>
 * * the scale number of the grid <i>LocalScaleNb</i> ;<br>
 * * the current number of elements used in the grid <i>ElementNb</i> ;<br>
 * * the array of cell-average values <i>*Q</i> ;<br>
 * * an array of temporary cell-average values <i>*Qt</i>.<br>
 *
 * To write tree-structured data into a regular fine grid, one starts
 * with the grid of level 0 and one stops at the level <i>L</i>.
 * For a given grid of level <i>l</i> and a given element <i>i, j, k</i> of this grid, if the node
 * of the tree corresponding to the element is
 * a leaf, the value is replaced by the one of the node, else it is predicted from parents.
 *
 * Such grid does not contain any cell information, in order to reduce memory requirements.
 *
 */
class PrintGrid
{
/*
______________________________________________________________________________________________

DESCRIPTION

	This is a grid of level L used to print data into file.

______________________________________________________________________________________________

PUBLIC METHODS

	Constructor and distructor
______________________________________________________________________________________________

*/

public:
	PrintGrid(int L); /*!< Constructor of PrintGrid class. Generates a grid of 2**(<i>Dimension*L</i>) elements. */

	~PrintGrid();	/*!<Distructor of the PrintGrid class. Removes the grid. */

/*
______________________________________________________________________________________________

	Set and get procedures
______________________________________________________________________________________________

*/

/**
 * @brief Sets the cell-average vector located at <i>i, j, k</i> to <i>UserAverage</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @param UserAverage Vector of averages
 * @return void
 */
void   setValue(const int i, const int j, const int k, const Vector& UserAverage);

/**
 * @brief Returns the cell-average vector located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return Vector
 */
Vector value(const int i, const int j, const int k) const;

/**
 * @brief Returns the quantity <i>QuantityNo</i> of the cell-average vector located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @param QuantityNo Number of MHD variables.
 * @return real
 */
real value(const int i, const int j, const int k, const int QuantityNo) const;

/**
 * @brief Returns the quantity <i>QuantityNo</i> of the cell-average vector located at <i>i, j, k</i>,
 * taking into account boundary conditions.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @param QuantityNo Number of MHD variables.
 * @return real
 */
real cellValue(const int i, const int j, const int k, const int QuantityNo) const;

/**
 * @brief Returns the cell-average density located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return real
 */
inline real density(const int i, const int j, const int k) const;

/**
 * @brief Returns the cell-average density located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return real
 */
inline real psi(const int i, const int j, const int k) const;

/**
 * @brief Returns the cell-average pressure located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return real
 */
real pressure(const int i, const int j, const int k) const;

/**
 * @brief Returns the cell-average temperature located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return real
 */
real temperature(const int i, const int j, const int k) const;

/**
 * @brief Returns the cell-average concentration of the limiting reactant, located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return real
 */
real concentration(const int i, const int j, const int k) const;

/**
 * @brief Returns the cell-average energy per unit of volume located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return real
 */
inline real energy(const int i, const int j, const int k) const;

/**
 * @brief Returns the <i>AxisNo</i>-th component of the cell-average velocity located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @param AxisNo Axis of interest.
 * @return real
 */
inline real velocity(const int i, const int j, const int k, const int AxisNo) const;

/**
 * @brief Returns the cell-average velocity located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return Vector
 */
Vector	velocity(const int i, const int j, const int k) const;

/**
 * @brief Returns the divergence of magnetic field B located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return real
 */
real divergenceB(const int i, const int j, const int k) const;

/**
 * @brief Returns 0 in 1D, the scalar vorticity in 2D, the norm of the cell-average vorticity in 3D, located at <i>i, j, k</i>.
 * Does not work for MHD!
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return real
 */
real vorticity(const int i, const int j, const int k) const;

/**
 * @brief Returns the <i>AxisNo</i>-th component of the cell-average velocity located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @param AxisNo Axis of interest
 * @return real
 */
inline real magField(const int i, const int j, const int k, const int AxisNo) const;

/**
 * @brief Returns the cell-average velocity located at <i>i, j, k</i>.
 *
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return Vector
 */
Vector	magField(const int i, const int j, const int k) const;

/*
______________________________________________________________________________________________

	Refresh and predict procedure
______________________________________________________________________________________________

*/

/**
 * @brief Stores the cell-average values of the current grid into temporary values,
 * in order to compute cell-averages in the next finer grid.
 *
 * @return void
 */
void refresh();

/**
 * @brief Predicts the cell-average values of the current grid from the values stored in the
 * temporary ones.
 *
 * @param l Level
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return void
 */
void predict(const int l, const int i, const int j, const int k);

/**
 * @brief Transform cell-average values into point values.
 *
 * @return void
 */
void computePointValue();
/*
______________________________________________________________________________________________

PRIVATE VARIABLES AND METHODS
______________________________________________________________________________________________

*/

private:
  /**
   * @brief Returns temporary cell-average values at the level <i>l</i> and at
   * the position <i>i, j, k</i>.
   *
   * @param l level
   * @param i Position x
   * @param j Position y
   * @param k Position z
   * @return Vector
   */
  Vector tempValue(const int l, const int i, const int j, const int k) const;

	int localScaleNb;	/*!< Scale number for the printed grid */
	int elementNb;		/*!< Number of elements */
	Vector *Q;		/*!< Quantities vector */
	Vector *Qt;		/*!< Temporary quantities vector */
};


/*
______________________________________________________________________________________________

INLINE FUNCTIONS
______________________________________________________________________________________________

*/

inline real PrintGrid::density(const int i, const int j, const int k) const
{
	return value(i,j,k,1);
}

/*
______________________________________________________________________________________________

*/

inline real PrintGrid::psi(const int i, const int j, const int k) const
{
	return value(i,j,k,6);
}

/*
______________________________________________________________________________________________

*/

inline real PrintGrid::energy(const int i, const int j, const int k) const
{
	return value(i,j,k,5);
}


/*
______________________________________________________________________________________________

*/

inline real PrintGrid::velocity(const int i, const int j, const int k, const int AxisNo) const
{
	return cellValue(i,j,k,AxisNo+1)/cellValue(i,j,k,1);
}

/*
______________________________________________________________________________________________

*/

inline real PrintGrid::magField(const int i, const int j, const int k, const int AxisNo) const
{
	return cellValue(i,j,k,AxisNo+6);
}
