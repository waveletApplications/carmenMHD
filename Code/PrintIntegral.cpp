/***************************************************************************
                          PrintIntegral.cpp  -  description
                             -------------------
    begin                : Wed Jun 27 2001
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
/** @file PrintIntegral.cpp
  * @brief Print integral values into file "FileName"
  */

#include "Carmen.h"
/*
______________________________________________________________________________________________

Print integral values into file "FileName"
______________________________________________________________________________________________

*/

void PrintIntegral(const char* FileName)
{
	// --- Local variables ---

	real 	t;				// time
	FILE	*output;  // output file
	int i;					// counter
	real Volume=1.;	// Total volume

	// --- Open file ---

	if ( (IterationNo == 0) ? (output = fopen(FileName,"w")) : (output = fopen(FileName,"a")) )
	{
	// HEADER

		if (IterationNo == 0)
		{

			fprintf(output, "#");
			fprintf(output, TXTFORMAT, " Time");
			fprintf(output, TXTFORMAT, "CFL");
			fprintf(output, TXTFORMAT, "Energy");
			fprintf(output, TXTFORMAT, "Div B Max");
			fprintf(output, TXTFORMAT, "ch");
            fprintf(output, TXTFORMAT, "Helicity");
            fprintf(output, TXTFORMAT, "DivB Max norm");
/*
			if (Multiresolution)
			{
				fprintf(output, TXTFORMAT, "Memory comp.");
				fprintf(output, TXTFORMAT, "CPU comp.");
				if (ExpectedCompression != 0. || CVS)
					fprintf(output, TXTFORMAT, "Tolerance");
			//	if (CVS)
			//		fprintf(output, TXTFORMAT, "Av. Pressure");

			}
*/
			if (!ConstantTimeStep)
			{
				if (StepNb == 3) fprintf(output, TXTFORMAT, "RKF Error");
				fprintf(output, TXTFORMAT,"Next time step");
				fprintf(output, "%13s  ", "IterationNo");
				fprintf(output, "%13s  ", "IterationNb");
			}

			fprintf(output,"\n");

		}

		if (ConstantTimeStep)
			t=IterationNo*TimeStep;
		else
			t = ElapsedTime;

		fprintf(output, FORMAT, t);

		// --- Compute total volume ---

		for (i=1; i<= Dimension; i++)
			Volume *= fabs(XMax[i]-XMin[i]);

		// Print CFL
		fprintf(output, FORMAT,Eigenvalue*TimeStep/SpaceStep);

		// Print momentum and energy
		//fprintf(output, FORMAT, GlobalMomentum);
		fprintf(output, FORMAT, GlobalEnergy);
		fprintf(output, FORMAT, DIVBMax);
        fprintf(output, FORMAT, ch);
		fprintf(output, FORMAT, Helicity);
		fprintf(output, FORMAT, DIVB);


/*
		if (Multiresolution)
		{
			fprintf(output, FORMAT, (1.*CellNb)/(1<<(ScaleNb*Dimension)));
			fprintf(output, FORMAT, CPUTime.CPUTime()/(IterationNo*FVTimeRef));

			if (ExpectedCompression != 0.)
				fprintf(output, FORMAT, Tolerance);

    		//	if (CVS)
			//{
		//		fprintf(output, FORMAT, ComputedTolerance(ScaleNb));
			//	fprintf(output, FORMAT, QuantityAverage.value(1));
			//}
    	}
*/
		if (!ConstantTimeStep)
		{
			if (StepNb == 3) fprintf(output, FORMAT, RKFError);
			fprintf(output, FORMAT, TimeStep);
			fprintf(output, "%13i  ", IterationNo);
			fprintf(output, "%13i  ", IterationNb);
		}

		fprintf(output, "\n");
		fclose(output);
	}
	else
	{
		cout << "PrintIntegral.cpp: In method `void PrintIntegral(Node*, char*)´:\n";
		cout << "PrintIntegral.cpp: cannot open file " << FileName << '\n';
		cout << "carmen: *** [PrintIntegral.o] Execution error\n";
		cout << "carmen: abort execution.\n";
		exit(1);
	}
}
