/***************************************************************************
                          Node.h  -  description
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

#include "PreProcessor.h"

/**
 * @file Node.h
 * @class Node
 * @brief An object Node is an element of a graded tree structure, used for
 * multiresolution computations. Its contains
 * the following informations:
 *
 * * A pointer to the root node <i>*Root</i> ;<br> * * The corresponding cell <i>ThisCell</i> ;<br>
 * * An array of pointers to the children nodes <i>**Child</i>. Each parent has <i>2**Dimension</i>
 *   children nodes ; <br>
 * * The position of the node <i>Nl, Ni, Nj, Nk</i> into the tree structure (Nl = level) ;<br>
 * * A <i>Flag</i> giving the kind of node :
   0 = not a leaf, 1 = leaf, 2 = leaf with virtual children, 3 = virtual leaf.
 *
 * A leaf is a node without children, a virtual leaf is an artificial leaf created
 * only for the flux computations. No time evolution is made on virtual leaves.
 * 
 */
class Node
{
/*
______________________________________________________________________________________________

PUBLIC METHODS

	Constructor and distructor
______________________________________________________________________________________________

*/

public:

  /**
   * @brief Constructor of Node class.
   * Generates a new node at the position (<i>l, i, j, k</i>) in the tree structure.
 *  A new node is always a leaf. The array of pointers to the children is
 *  allocated, together with the informations on the corresponding cell: cell-center
 *  position and cell size.
 * 
   * @param l Level
   * @param i Position x
   * @param j Position y
   * @param k Position z
   */
  Node(const int l=0, const int i=0, const int j=0, const int k=0);

 /**
  * @brief Distructor of Node class.
  * Removes the node from the tree structure. If the node is not a leaf, all
  * the children are also removed.
  * 
  */
 ~Node();
/*
______________________________________________________________________________________________

	Get procedures
______________________________________________________________________________________________

*/

 /**
  * @brief Returns the number of cells in the tree.
  * 
  * @return int
  */
 inline int		cells() const;

 /**
  * @brief Returns the number of leaves in the tree.
  * 
  * @return int
  */
 inline int		leaves() const;

/*
______________________________________________________________________________________________

	Multiresolution procedures
______________________________________________________________________________________________

*/

 /**
  * @brief Computes the details in the leaves and its parent nodes and, in function
 * of the threshold <i>Tolerance</i>, adapt the tree structure.
  * 
  * @return int
  */
 int		adapt();

 /**
  * @brief Checks if the tree is graded. If not, an error is emitted. Only for
 * debugging.
  * 
  * @return void
  */
 void checkGradedTree();


 /**
  * @brief Computes the initial value.
  * 
  * @return void
  */
 void		initValue();
 
 /**
  * @brief Adds levels when needed.
  * 
  * @return void
  */
 void		addLevel();

 /**
  * @brief Computes the cell-average values of all nodes that are not leaves by projection from
 * the cell-averages values of the leaves. This procedure is required after a time evolution
 * to refresh the internal nodes of the tree.
  * 
  * @return Cell*
  */
 Cell* 	project();

 /**
  * @brief Fills the cell-average values of every virtual leaf with values predicted from its parent and
 * uncles. This procedure is required after a time evolution
 * to refresh the virtual leaves of the tree.
  * 
  * @return void
  */
 void fillVirtualChildren();
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
 * @return void
 */
void computeDivergence();

/**
 * @brief Computes one Runge-Kutta step.
 * 
 * @return void
 */
void RungeKutta();

/**
 * @brief Computes integral values like e.g. flame velocity, global error, etc.
 * 
 * @return void
 */
void computeIntegral();

/**
 * @brief Computes velocity gradient (only for Navier-Stokes).
 * 
 * @return void
 */
void computeGradient();

/**
 * @brief Computes velocity gradient (only for Navier-Stokes).
 * 
 * @return void
 */
void computeCorrection();

/**
 * @brief Checks if the computation is numerically unstable, i.e. if one of the
 * cell-averages is overflow. In case of numerical instability, the computation is
 * stopped and a message appears.
 * 
 * @return void
 */
void checkStability();
/*
______________________________________________________________________________________________

	Output procedures
______________________________________________________________________________________________

*/

/**
 * @brief Writes tree structure into file <i>FileName</i>. Only for debugging.
 * 
 * @param FileName Name of the file.
 * @return void
 */
void writeTree(const char* FileName) const;

/**
 * @brief Writes cell-average values in multiresolution representation and the
 * corresponding mesh into file <i>FileName</i>.
 * 
 * @param FileName Name of the file.
 * @return void
 */
void writeAverage(const char* FileName);

/**
 * @brief Writes mesh data for Gnuplot into file <i>FileName</i>.
 * 
 * @param FileName Name of the file.
 * @return void
 */
void writeMesh(const char* FileName) const;

/**
 * @brief Writes header for Data Explorer into file <i>FileName</i>.
 * 
 * @param FileName Name of the file.
 * @return void
 */
void writeHeader(const char* FileName) const;

/**
 * @brief Writes cell-average values on a regular grid of level <i>L</i> into file <i>FileName</i>.
 * 
 * @param FileName Name of the file
 * @param L Maximum level.
 * @return void
 */
void writeFineGrid(const char* FileName, const int L=ScaleNb) const;

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

/**
 * @brief Restores the tree structure and the cell-averages from the file <i>carmen.bak</i>
 * in FineMesh format.
 * 
 * @return void
 */
void restoreFineMesh();

/**
 * @brief Deletes the details in the highest level.
 * 
 * @return void
 */
void	smooth();

/*
______________________________________________________________________________________________

PRIVATE METHODS
______________________________________________________________________________________________

	Multiresolution procedures
______________________________________________________________________________________________

*/

private:
  /**
   * @brief Splits node with respect to the graded tree structure.
 * If <i>init</i> is true, the new value is computed from the initial condition. Elsewhere
 * it is computed by prediction.
   * 
   * @param init Boolean variable.
   * @return void
   */
  void split(const bool init=false);

/**
 * @brief Splits the complete tree until the smallest scale.
 * 
 * @return void
 */
void splitAll();

/**
 * @brief Combines node, ie remove it if the graded tree structure can be maintained without it.
 * 
 * @return void
 */
void combine();

/**
 * @brief Returns the cell-average value of the current node predicted from the parent node and its nearest neigbours (uncles)
 * 
 * @return Vector
 */
Vector 	predict() const;

/**
 * @brief Returns the cell resistivity value of the current node predicted from the parent node and its nearest neigbours (uncles)
 *
 * @return real
 */
real 	predictRes() const;


/**
 * @brief Returns the temporary cell-average value of the current node predicted from the parent node and its nearest neigbours (uncles).
 * Only for time adaptivity.
 * 
 * @return Vector
 */
Vector 	predictTempAverage() const;

/**
 * @brief Returns the gradient of the current node predicted from the parent node and its nearest neigbours (uncles).
 * 
 * @return Matrix
 */
Matrix 	predictGradient() const;

/**
 * @brief Computes the interpolation in time in the current node. Only for time adaptivity.
 * 
 * @return void
 */
inline void computeTimeInterpolation();

/**
 * @brief Computes the extrapolation in time in the current node. Only for time adaptivity.
 * 
 * @return void
 */
inline void computeTimeExtrapolation();

/**
 * @brief Stores the result of the time evolution into temporary cell-average values. Only for time adaptivity.
 * 
 * @return void
 */
inline void storeTimeEvolution();

/**
 * @brief Sets the current node to an internal node.
 * 
 * @return void
 */
inline void setInternalNode();

/**
 * @brief Sets the current node to a simple leaf
 * 
 * @return void
 */
inline void setSimpleLeaf();

/**
 * @brief Sets the current node to a leaf with virtual children.
 * 
 * @return void
 */
inline void setLeafWithVirtualChildren();

/**
 * @brief Sets the current node to a virtual leaf.
 * 
 * @return void
 */
inline void setVirtualLeaf();

/**
 * @brief Returns true if the current node is an internal node.
 * 
 * @return bool
 */
inline bool isInternalNode() const;

/**
 * @brief Returns true if the current node is a leaf (with or without virtual children).
 * 
 * @return bool
 */
inline bool isLeaf() const;

/**
 * @brief Returns true if the current node is a simple leaf (no virtual children).
 * 
 * @return bool
 */
inline bool isSimpleLeaf() const;

/**
 * @brief Returns true if the current node is a simple leaf with virtual children.
 * 
 * @return bool
 */
inline bool isLeafWithVirtualChildren() const;

/**
 * @brief Returns true if the current node is a virtual.
 * 
 * @return bool
 */
inline bool isVirtualLeaf() const;

/**
 * @brief Returns true if the current node has children (real or virtual).
 * 
 * @return bool
 */
inline bool hasChildren() const;

/**
 * @brief Returns true if the current node or one of its children is a leaf.
 * 
 * @return bool
 */
inline bool isParentOfLeaf() const;

/**
 * @brief Returns true if the current node is inside a boundary region.
 * 
 * @return bool
 */
bool isInsideBoundary() const;

/**
 * @brief Returns true if the current node is inside the fluid region.
 * 
 * @return bool
 */
bool isInFluid() const;

/**
 * @brief Returns true if the current node is on a limit of boundary region.
 * 
 * @return bool
 */
bool isOnBoundary() const;

/**
 * @brief Returns true if the current leaf is at the begining of a time cycle.
 * Only useful when TimeAdaptivity = true
 * 
 * @return bool
 */
inline bool isBeginTimeCycle() const;

/**
 * @brief Returns true if the current leaf is at the end of a time cycle.
 * Only useful when TimeAdaptivity = true
 * 
 * @return bool
 */
inline bool isEndTimeCycle() const;

/**
 * @brief Returns true if a time evolution is required for this node.
 * 
 * @return bool
 */
inline bool requiresTimeEvolution() const;

/**
 * @brief Returns true if an interpolation in time is required for this node.
 * 
 * @return bool
 */
inline bool requiresTimeInterpolation() const;

/**
 * @brief Returns true if the divergence computation is required for this node.
 * 
 * @return bool
 */
inline bool requiresDivergenceComputation() const;

/**
 * @brief Returns true if the detail in the current node is smaller than the required tolerance.
 * 
 * @return bool
 */
inline bool detailIsSmall() const;
/*
______________________________________________________________________________________________

	Get procedures
______________________________________________________________________________________________

*/

/**
 * @brief Returns the pointer to the node located at (<i>l, i, j, k</i>). The
 * boundary conditions are not taken into account. If this node does not
 * exist, 0 is returned.
 * 
 * @param l Level
 * @param i Position x
 * @param j Position y
 * @param k Position z
 * @return Node*
 */
Node* node(int l, int i, int j = 0, int k = 0) const;

/**
 * @brief Returns the pointer to the cell located at (<i>l, i, j, k</i>), with respect to boundary conditions.
 * 
 * @param l Level
 * @param i Position x
 * @param j Position y
 * @param k POsition z
 * @return Cell*
 */
Cell* cell(int l, int i, int j = 0, int k = 0) const;

/**
 * @brief Returns the pointer to the parent node
 * 
 * @return Node*
 */
inline Node* parent() const;

/**
 * @brief Returns the pointer to the parent cell
 * 
 * @return Cell*
 */
inline Cell* parentCell() const;

/**
 * @brief Returns the pointer to the uncle node with relative position (<i>i, j, k</i>)
 * 
 * @param i Position x
 * @param j Position y
 * @param k POsition z
 * @return Node*
 */
inline Node* uncle(const int i, const int j=0, const int k=0) const;

/**
 * @brief Returns the pointer to the uncle cell with relative position (<i>i, j, k</i>)
 * 
 * @param i Position x
 * @param j Position y
 * @param k POsition z
 * @return Cell*
 */
inline Cell* uncleCell(const int i, const int j=0, const int k=0) const;

/**
 * @brief Returns the pointer to the cousin node with relative position (<i>i, j, k</i>)
 * 
 * @param i Position x
 * @param j Position y
 * @param k POsition z
 * @return Node*
 */
inline Node* cousin(const int i, const int j=0, const int k=0) const;

/**
 * @brief Returns the pointer to the cousin cell with relative position (<i>i, j, k</i>)
 * 
 * @param i Position x
 * @param j Position y
 * @param k POsition z
 * @return Cell*
 */
inline Cell* cousinCell(const int i, const int j=0, const int k=0) const;

/**
 * @brief Returns the pointer to the child cell with relative position (<i>i, j, k</i>)
 * 
 * @param i Position x
 * @param j Position y
 * @param k POsition z
 * @return Node*
 */
inline Node* child(const int i, const int j=0, const int k=0) const;

/**
 * @brief Returns the pointer to the child cell with relative position (<i>i, j, k</i>)
 * 
 * @param i Position x
 * @param j Position y
 * @param k POsition z
 * @return Cell*
 */
inline Cell* childCell(const int i, const int j=0, const int k=0) const;

/*
______________________________________________________________________________________________

	Procedures on virtual children
______________________________________________________________________________________________

*/

/**
 * @brief Tests and, if possible, deletes the virtual children of the current node.
 * 
 * @return void
 */
void deleteVirtualChildren();

/**
 * @brief Generates virtual children for the current node. If <i>init</i> is true,
 * the cell-average value in the virtual child is computed from the initial
 * condition. Elsewhere, it is computed by prediction from parent and uncles.
 * 
 * @param init Boolean value
 * @return void
 */
void makeVirtualChildren(bool init=false);

/*
______________________________________________________________________________________________

PRIVATE VARIABLES
______________________________________________________________________________________________

*/
	static Node *Root;	/*!< Pointer on root node*/
//	static Node Boundary; 	/*!< Boundary cell*/

	int	Nl;		/*!< Scale number*/
	int Ni, Nj, Nk;		/*!< Position number in x, y, z directions*/

	Node **Child;		/*!< Array of pointers to children (whatever they exist or not)*/
  	Cell ThisCell;		/*!< Cell corresponding to this node*/

	byte Flag;		/*!< Flag (0 = internal node, 1 = simple leaf, 2 = leaf with virtual children, 3 = virtual leaf*/
};

/*
______________________________________________________________________________________________

	INLINE FUNCTION
______________________________________________________________________________________________

	Returns the number of cells
______________________________________________________________________________________________

*/
inline int Node::cells() const
{
	return CellNb;
}
/*
______________________________________________________________________________________________

	Get number of leaves
______________________________________________________________________________________________

*/
inline int Node::leaves() const
{
	return LeafNb;
}

/*
______________________________________________________________________________________________

	Returns pointer to child cell using relative position
______________________________________________________________________________________________

*/

inline Cell* Node::childCell(const int i, const int j, const int k) const
{
	return cell(Nl+1, 2*Ni+i, 2*Nj+j, 2*Nk+k);
}

/*
______________________________________________________________________________________________

	Returns pointer to child node using relative position
______________________________________________________________________________________________

*/

inline Node* Node::child(const int i, const int j, const int k) const
{
	return node(Nl+1, 2*Ni+i, 2*Nj+j, 2*Nk+k);
}
/*
______________________________________________________________________________________________

	This function computes the interpolation in time in the node
______________________________________________________________________________________________

*/

inline void Node::computeTimeInterpolation()
{
	ThisCell.setAverage(ThisCell.tempAverage() + ThisCell.average());
}

/*
______________________________________________________________________________________________

	Returns pointer to uncle cell using relative position
______________________________________________________________________________________________

*/

inline Cell* Node::cousinCell(const int i, const int j, const int k) const
{
	return cell(Nl, Ni+i, Nj+j, Nk+k);
}

/*
______________________________________________________________________________________________

	Returns pointer to uncle cell using relative position
______________________________________________________________________________________________

*/

inline Node* Node::cousin(const int i, const int j, const int k) const
{
	return node(Nl, Ni+i, Nj+j, Nk+k);
}

/*
______________________________________________________________________________________________

	Return true if node is has children (real or virtual)
______________________________________________________________________________________________

*/
inline bool Node::hasChildren() const
{
	return (Flag==0 || Flag==2);
}

/*
______________________________________________________________________________________________

	Sets the current node to internal node
______________________________________________________________________________________________

*/
inline void Node::setInternalNode()
{
	Flag = 0;
	return;
}

/*
______________________________________________________________________________________________

	Sets the current node to simple leaf
______________________________________________________________________________________________

*/
inline void Node::setSimpleLeaf()
{
	Flag = 1;
	return;
}
/*
______________________________________________________________________________________________

	Sets the current node to leaf with virtual children
______________________________________________________________________________________________

*/
inline void Node::setLeafWithVirtualChildren()
{
	Flag = 2;
	return;
}
/*
______________________________________________________________________________________________

	Sets the current node to virtual leaf
______________________________________________________________________________________________

*/
inline void Node::setVirtualLeaf()
{
	Flag = 3;
	return;
}
/*
______________________________________________________________________________________________

Returns true if the leaf is at the begining of a time cycle.
Only useful when TimeAdaptivity = true
______________________________________________________________________________________________

*/
inline bool Node::isBeginTimeCycle() const
{
	return ((IterationNo-1)%(1<<(TimeAdaptivityFactor*(ScaleNb-Nl))) == 0);
}

/*
______________________________________________________________________________________________

Returns true if the leaf is at the end of a time cycle.
Only useful when TimeAdaptivity = true
______________________________________________________________________________________________

*/
inline bool Node::isEndTimeCycle() const
{
	return (IterationNo%(1<<(TimeAdaptivityFactor*(ScaleNb-Nl))) == 0);
}

/*
______________________________________________________________________________________________

	Returns pointer to parent node
______________________________________________________________________________________________

*/
inline Node* Node::parent() const
{
	return node(Nl-1, (Ni+4)/2-2, (Nj+4)/2-2, (Nk+4)/2-2);
}

/*
______________________________________________________________________________________________

	Returns pointer to parent cell
______________________________________________________________________________________________

*/
inline Cell* Node::parentCell() const
{
	return cell(Nl-1, (Ni+4)/2-2, (Nj+4)/2-2, (Nk+4)/2-2);
}

/*
______________________________________________________________________________________________

	Returns pointer to uncle node using relative position
______________________________________________________________________________________________

*/
inline Node* Node::uncle(const int i, const int j, const int k) const
{
	return node(Nl-1, (Ni+4)/2-2 + i, (Nj+4)/2-2 + j, (Nk+4)/2-2 + k);
}

/*
______________________________________________________________________________________________

	Returns pointer to uncle cell using relative position
______________________________________________________________________________________________

*/
inline Cell* Node::uncleCell(const int i, const int j, const int k) const
{
	return cell(Nl-1, (Ni+4)/2-2 + i, (Nj+4)/2-2 + j, (Nk+4)/2-2 + k);
}

/*
______________________________________________________________________________________________

	Returns true if node is an internal node (not a leaf)
______________________________________________________________________________________________

*/
inline bool Node::isInternalNode()  const
{
	return (Flag==0);
}

/*
______________________________________________________________________________________________

	Returns true if node is a leaf (with or without virtual children)
______________________________________________________________________________________________

*/
inline bool Node::isLeaf() const
{
	return (Flag==1 || Flag==2);
}

/*
______________________________________________________________________________________________

	Returns true if node is a simple leaf (without virtual children)
______________________________________________________________________________________________

*/
inline bool Node::isSimpleLeaf() const
{
	return (Flag==1);
}

/*
______________________________________________________________________________________________

	Returns true if node is a leaf with virtual children
______________________________________________________________________________________________

*/
inline bool Node::isLeafWithVirtualChildren() const
{
	return (Flag==2);
}

/*
______________________________________________________________________________________________

	Return true if node is a virtual leaf
______________________________________________________________________________________________

*/
inline bool Node::isVirtualLeaf() const
{
	return (Flag==3);
}

/*
______________________________________________________________________________________________

	This function stores the result of the time evolution in Qlow, and interpolates
	the internediary state between [n+1] and [n], which is stored in Q.
______________________________________________________________________________________________

*/

inline void Node::storeTimeEvolution()
{

	// Qlow <- Q
	ThisCell.setLowAverage( ThisCell.average());

	// Q <- 1/2 (Q + Qs)
	ThisCell.setAverage( 0.5*(ThisCell.average() + ThisCell.tempAverage()) );
}

/*
______________________________________________________________________________________________

	Returns the extrapolation in time. Only for local time stepping
______________________________________________________________________________________________

*/

inline void Node::computeTimeExtrapolation()
{
	Vector A(QuantityNb);

	A = ThisCell.average();
	ThisCell.setAverage(ThisCell.average() + ThisCell.average() - ThisCell.tempAverage());
	ThisCell.setTempAverage(A);
}

/*
______________________________________________________________________________________________

	This function return "true" if this node requires an interpolation in time, instead of a full time evolution
______________________________________________________________________________________________

*/

inline bool Node::requiresDivergenceComputation() const
{
	if (UseBoundaryRegions)
		if (isInsideBoundary()) return false;

	if (TimeAdaptivity)
		// With time adaptivity, compute divergence at the begining and the end of time cycles
		return (isLeaf() && (isBeginTimeCycle()|| isEndTimeCycle()) );
	else
    	// Without time adaptivity, perform TimeEvolution on leaves whatever IterationNo
		return (isLeaf()) ;
}

/*
______________________________________________________________________________________________

	This function return "true" if this node requires a time evolution procedure (no interpolation)
______________________________________________________________________________________________

*/
inline bool Node::requiresTimeEvolution() const
{
	if (UseBoundaryRegions)
		if (isInsideBoundary()) return false;

	if (TimeAdaptivity)
		// With time adaptivity, perform TimeEvolution on leaves every 2^a(L-l) iterations
		return (isLeaf() && isBeginTimeCycle());
	else
    	// Without time adaptivity, perform TimeEvolution on leaves whatever IterationNo
		return (isLeaf()) ;
}

/*
______________________________________________________________________________________________

	This function return "true" if this node requires an interpolation in time, instead of a full time evolution
______________________________________________________________________________________________

*/
inline bool Node::requiresTimeInterpolation() const
{
	if (UseBoundaryRegions)
		if (isInsideBoundary()) return false;

	// When the time adaptivity is not used, never perform interpolation in time
	if (!TimeAdaptivity) return false;

	// With time adaptivity, permform interpolation on leaves where no time evolution is made
	return (isLeaf() && isEndTimeCycle());
}





