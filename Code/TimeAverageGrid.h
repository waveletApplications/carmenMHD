/***************************************************************************
                          TimeAverageGrid.h  -  description
                             -------------------
    begin                : ven déc 3 2004
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

/**
 * @file TimeAverageGrid.h
 * @class TimeAverageGrid
 * @brief Time Average Grid
 * 
 */
class TimeAverageGrid
{
/*
______________________________________________________________________________________________

PUBLIC METHODS
______________________________________________________________________________________________

*/
	public:
	  /**
	   * @brief Constructor of TimeAverageGrid class.
	   * For a given variable number.
	   * 
	   * @param UserScaleNb Level
	   * @param UserQuantityNb Variable number
	   */
	  TimeAverageGrid(const int UserScaleNb, const int UserQuantityNb);
	  /**
	   * @brief Constructor of TimeAverageGrid class.
	   * 
	   * @param UserScaleNb Level
	   */
	  TimeAverageGrid(const int UserScaleNb);
	  /**
	   * @brief Destructor of TimeAverageGrid clas.
	   * 
	   */
	  ~TimeAverageGrid();

	  /**
	   * @brief Update Values.
	   * For a given element.
	   * 
	   * @param ElementNo Element number
	   * @param QuantityNo Variable number
	   * @param UserValue Real value
	   * @return void
	   */
	  void updateValue(const int ElementNo, const int QuantityNo, const real UserValue);
	  /**
	   * @brief Update Values.
	   * At position i,j,k
	   * 
	   * @param i Position x
	   * @param j Position y
	   * @param k Position z
	   * @param QuantityNo Variable number
	   * @param UserValue Real value
	   * @return void
	   */
	  void updateValue(const int i, const int j, const int k, const int QuantityNo, const real UserValue);
	  /**
	   * @brief Update values.
	   * 
	   * @param i Position x
	   * @param j Position y
	   * @param k Position z
	   * @param arg Vector
	   * @return void
	   */
	  void updateValue(const int i, const int j, const int k, const Vector arg);

	  /**
          * @brief Update number of samples
          * 
          * @return void
          */
	  inline void updateSample();

	  /**
          * @brief Get value at the position ElementNo
          *  
          * @param ElementNo Element number
          * @param QuantityNo Variable number
          * @return real
          */
	  inline real value(const int ElementNo, const int QuantityNo) const;
	  /**
          * @brief Get value at the position i,j,k
          * 
          * @param i Position x
          * @param j Position y
          * @param k Position z
          * @param QuantityNo Variable number
          * @return real
          */
	  inline real value(const int i, const int j, const int k, const int QuantityNo) const;

          /**
          * @brief Get density at the position i,j,k
          * 
          * @param i Position x
          * @param j Position y
          * @param k Position z
          * @return real
          */
	  inline real density(const int i, const int j, const int k) const;
	  /**
          * @brief Get velocity at the position i,j,k
          * 
          * @param i Position x
          * @param j Position y
          * @param k Position z
          * @param AxisNo Axis of interest
          * @return real
          */
	  inline real velocity(const int i, const int j, const int k, const int AxisNo) const;
		real stress(const int i, const int j, const int k, const int No) const;

/*
______________________________________________________________________________________________

PRIVATE VARIABLES
______________________________________________________________________________________________

*/
	private:
		int	LocalQuantityNb;		/*!< Number of time-average quantities (ex: u, v, w, u'u', u'v', etc ...)*/
		int LocalScaleNb; 			/*!< Number of scales for this grid*/
		int ElementNb;				/*!< 2^(Dimension*LocalScaleNb)*/
		int SampleNb;				/*!< Number of samples for the time-averaging procedure*/
		Vector *Q;    				/*!< Vector containing the time-average quantities*/
};

/*
______________________________________________________________________________________________

INLINE FUNCTIONS
______________________________________________________________________________________________

Get density at the position i,j,k
______________________________________________________________________________________________

*/
inline real TimeAverageGrid::density(const int i, const int j, const int k) const
{
	return value(i,j,k,1);
}

/*
______________________________________________________________________________________________

Update number of samples
______________________________________________________________________________________________

*/
inline void TimeAverageGrid::updateSample()
{
	SampleNb++;
}

/*
______________________________________________________________________________________________

Get velocity at the position i,j,k
______________________________________________________________________________________________

*/
inline real TimeAverageGrid::velocity(const int i, const int j, const int k, const int AxisNo) const
{
	return value(i,j,k,AxisNo+1)/value(i,j,k,1);
}

/*
______________________________________________________________________________________________

Get value at the position ElementNo
______________________________________________________________________________________________

*/

inline real TimeAverageGrid::value(const int ElementNo, const int QuantityNo) const
{
	return (Q+ElementNo)->value(QuantityNo);
}

/*
______________________________________________________________________________________________

Get value at the position i,j,k
______________________________________________________________________________________________

*/
inline real TimeAverageGrid::value(const int i, const int j, const int k, const int QuantityNo) const
{
	return value(i + (1<<LocalScaleNb)*(j +(1<<LocalScaleNb)*k), QuantityNo);
}


