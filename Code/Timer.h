/***************************************************************************
                          Timer.h  -  description
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

#ifndef TIMER_H
#define TIMER_H
#include <time.h>
#include <sys/times.h>
#include "PreProcessor.h"


/**
 * @file Timer.h
 * @class Timer
 * @brief An object Timer gives information on the CPU time of long-time computations.
 * 
 */
class Timer
{
/*
______________________________________________________________________________________________

PUBLIC METHODS
______________________________________________________________________________________________

*/

public:
  /**
   * @brief Constructor of Timer class. Initialize timer.
   * 
   */
  Timer();
								
/**
 * @brief Resets time and start.
 * 
 * @return void
 */
void   resetStart();

/**
 * @brief Adds CPU time and real time to their buffers and resets. For long
 * computations, it is recommended to do this operation at least once per
 * iteration.
 * 
 * @return void
 */
void	 check();

/**
 * @brief Starts timer.
 * 
 * @return void
 */
void start();

/**
 * @brief Stop timer and, if asked, returns CPU time from previous start in seconds.
 * 
 * @return double
 */
double stop();

/**
 * @brief Returns CPU time from previous start in seconds.
 * 
 * @return double
 */
double CPUTime();

/**
 * @brief Returns real time from previous start in seconds.
 * 
 * @return double
 */
double realTime();

/**
 * @brief Adds time to buffer (only when a computation is restarted).
 * 
 * @param cpuTime CPU time
 * @param realTime Real time
 * @return void
 */
void add(double cpuTime, double realTime);


/*
______________________________________________________________________________________________

PRIVATE VARIABLES
______________________________________________________________________________________________

*/
private:

  clock_t 	StartCPUTime;  			/*!< CPU time */
  time_t 		StartRealTime;      /*!< real time */
  double 		sumCPUtime;         /*!< elapsed CPU time in seconds */
  double 		sumRealtime;    		/*!< elapsed real time in seconds */

  bool 			TimerOn;            /*!< true if timer is running, false elswhere */
};

#endif
