/***************************************************************************
                          FineMesh.h  -  description
                             -------------------
    begin                : Wed Jun 13 2001
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

/***************************************************************************
 * An object FineMesh is a regular fine mesh, used for
 * finite volume computations.
 * It is not used for multiresolution computations.
 *
 * It contains an array of cells <i>*MeshCell</i>.
 *
 * NOTE: for reasons of simplicity, only periodic and Neuman boundary conditions have been
 * implemented.
 */

/** @file FineMesh.h
 * \class FineMesh
 * \brief An object FineMesh is a regular fine mesh, used for finite volume computations.
 * It is not used for multiresolution computations.
 *
 * It contains an array of cells <i>*MeshCell</i>.
 *
 * NOTE: for reasons of simplicity, only periodic and Neuman boundary conditions have been
 * implemented.
 * 
  */
class FineMesh
{
/*
______________________________________________________________________________________________

PUBLIC METHODS

	Constructor and distructor
______________________________________________________________________________________________

*/
public:

/**
 * @brief Constructor of FineMesh class
 * Generates a regular fine mesh containing <i>2**(Dimension*ScaleNb)</i>
 * cells. The cell-averages are initialized from the initial condition
 * contained in file <i>carmen.ini</i>.
 */
FineMesh();

/**
 * @brief Destructor the regular fine mesh.
 * 
 */
~FineMesh();
/*
______________________________________________________________________________________________

	Time evolution procedures
______________________________________________________________________________________________

*/

/**
 * @brief Stores cell-average values into temporary cell-average values.
 * 
 * @return void
 */
void store();

/**
 * @brief Stores gradient values into temporary gradient values.
 * 
 * @return void
 */
void storeGrad();

/**
 * @brief Computes the divergence vector with the space discretization scheme.
 * 
 * @param  int It can be zero or one. Associated to the time integration scheme.
 * @return void
 */
void computeDivergence(int);

/**
 * @brief Computes one Cell Divirgence
 * 
 * @param  int It can be zero or one. Associated to the time integration scheme.
 * @return void
 */
void computeDivergence_cell(int);

/**
 * @brief Computes one Runge-Kutta step.
 * 
 * @param  int It can be zero or one. Associated to the time integration scheme.
 * @return void
 */
void RungeKutta_cell(int);

	//each cells
/**
 * @brief Computes the Runge-Kutta step.
 * 
 * @param  int It can be zero or one. Associated to the time integration scheme.
 * @return void
 */
void RungeKutta(int);

/**
 * @brief Computes integral values like e.g. flame velocity, global error, etc.
 * 
 * @return void
 */
void computeIntegral();

/**
 * @brief Computes divergence cleaning source term (only for MHD).
 * 
 * @param  int It can be zero or one. Associated to the time integration scheme.
 * @return void
 */
void computeCorrection(int);

/**
 * @brief Computes divergence cleaning source term (only for MHD) at one cell.
 * 
 * @param  int It can be zero or one. Associated to the time integration scheme.
 * @return void
 */
void computeCorrection_cell(int);

/**
 * @brief Computes velocity gradient (only for Navier-Stokes).
 * one cell
 * 
 * @param  int It can be zero or one. Associated to the time integration scheme.
 * @return void
 */
void computeGradient(int);

/**
 * @brief Computes velocity gradient (only for Navier-Stokes).
 * each cells
 * 
 * @param  int It can be zero or one. Associated to the time integration scheme.
 * @return void
 */
void computeGradient_cell(int);

/**
 * @brief Computes the time-average value in every cell.
 * 
 * @return void
 */
void computeTimeAverage();

/**
 * @brief Checks if the computation is numerically unstable, i.e. if one of the
 * cell-averages is overflow. In case of numerical instability, the computation is
 * stopped and a message appears.
 * 
 * @return void
 */
void checkStability() const;

/*
______________________________________________________________________________________________

	Output procedures
______________________________________________________________________________________________

*/

/**
 * @brief Write header for GNUplot, Data Explorer, TecPLot and VTK into file <i>FileName</i>.
 * 
 * @param FileName Name of the file to write.
 * @return void
 */
void writeHeader(const char* FileName) const;

/**
 * @brief Write cell-averages for GNUplot, Data Explorer, TecPLot and VTK into file <i>FileName</i>.
 * 
 * @param FileName Name of the file to write.
 * @return void
 */
void writeAverage(const char* FileName);

/**
 * @brief Write time-averages into file <i>FileName</i>.
 * 
 * @param FileName Name of the file to write.
 * @return void
 */
void writeTimeAverage(const char* FileName) const;
/*
______________________________________________________________________________________________

	Backup-restore procedure (to restart a computation)
______________________________________________________________________________________________

*/
/**
 * @brief Backs up the tree structure and the cell-averages into a file <i>carmen.bak</i>.
 * In further computations, the data can be recovered using <b>Restore()</b>.
 * 
 * @return void
 */
void backup();

/**
 * @brief Restores the tree structure and the cell-averages from the file <i>carmen.bak</i>.
 * This file was created by the method <b>Backup()</b>.
 * 
 * @return void
 */
void restore();


//Parallel
	Cell ***Neighbour_iL,/*!< Parallel variable */
	     ***Neighbour_iU,/*!< Parallel variable */
	     ***Neighbour_jL,/*!< Parallel variable */
	     ***Neighbour_jU,/*!< Parallel variable */
	     ***Neighbour_kL,/*!< Parallel variable */
	     ***Neighbour_kU; /*!< Parallel variable */

/*
______________________________________________________________________________________________

PRIVATE METHODS AND VARIABLES
______________________________________________________________________________________________

*/

//parallel modification

/***************************************************************************
 * Returns pointer to the cell located at <i>i, j, k</i>.
 *
 */
public:
  Cell *MeshCell; /*!<Array of cells */

private:
	Cell* cell(const int i, const int j, const int k) const; /*!<Returns pointer to the cell located at <i>i, j, k</i>. */

/***************************************************************************
 * Returns pointer to the <i>n</i>-th cell.
 *
 */
	inline Cell* cell(const int n) const; /*!<Returns pointer to the <i>n</i>-th cell. */


/***************************************************************************
 * Compute coarse grid data and store fine grid data in temporary
 *
 */
	void coarsen();	/*!<Compute coarse grid data and store fine grid data in temporary */


/***************************************************************************
 * Restore fine grid data from temporary. Inverse of : coarsen()
 *
 */
	void refine();	/*!<Restore fine grid data from temporary. Inverse of : coarsen() */


/***************************************************************************
 * Array of cells
 *
 */
	TimeAverageGrid *MyTimeAverageGrid;	/*!< Array of cells*/

};


/*
______________________________________________________________________________________________

INLINE FUNCTIONS
______________________________________________________________________________________________

*/

inline Cell* FineMesh::cell(const int n) const
{
	return (MeshCell +n);
}



