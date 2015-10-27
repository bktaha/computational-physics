//###########################################!
// Lab #1
// Title: Root Finding Using Newton-Raphson Method
// Date: 04/08/2015
// Name: Taha Barwahwala
// Roll No: 130121039
// Email: b.taha@iitg.ernet.in
//###########################################!

#include<stdio.h>
#include<math.h>
// #include<iostream.h>

double fn (double x)
{
	// Functional Value	
	double v = 2.0*x*x*x - 11.7*x*x + 17.7*x -5.0;
	return v;
}

double fd (double x)
{
	// Differential Value
	double d = 6.0*x*x - 23.4*x + 17.7;
	return d;
}

double nr (double g, double tol)
{
	double xp, fv, di, err;	 	// Declaring Prev guess, Error, other variables
	int ni = 0;			// Number of Iterations
	printf("inputs : %f, %f\n",g,tol);
	do
	{	
		fv = fn(g);	
		di = fd(g);
		if (fv == 0.0)
		{
			printf("Ye got the root, matey! : %f\n", g);
		}
		else if (di!=0.0)
		{
			xp = g; g = g - fv/di;
			err = 100.0*abs((g - xp)/g);
			printf("New approx : %f\n",g);
		}
		else
		{printf("Balalala! Minima matey!"); break; return 1;}
		ni++;
	}while(err>tol);
	printf("Functional value at final guess : %f\n, No of iterations req : %i\n Error : %f\n", fv, ni, err);
	return g;
}

double main (int argc, char* argv[])
{
	if (argc!=4)
	{
		return 1;
	}
	else
	{
		double g1 = 1.0, g2 = 2.0, g3 = 3.0;		
		double g11 = atof(argv[1]);
		double r1 = nr(g1, 0.01);
		// double g2 = atof(argv[2]);
		double r2 = nr(g2, 0.01);
		// double g3 = atof(argv[3]);
		double r3 = nr(g3, 0.01);
		printf("%f, %s, %s\n", g11, argv[2], argv[3]);
	}
}
