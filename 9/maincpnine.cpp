// ----------------
// @tomatotorpedo
// October 26, 2015

// INPUT 1 -- filename
// ----------------

#include "comphy.h"

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

main(int argc, char* argv[]){
	Comphy librix;

	char* filename = argv[1];
	int n = librix.sizeMatrix(filename);
	float* matrix = new float[n*n];
	librix.retrieveMatrix(filename, matrix, n);
	float* eigenv = new float[n];   // Guess Eigenvector

	float l_eigenval = librix.eigen(matrix,n,eigenv);
	cout<<"Largest Eigenvalue:\t"<<l_eigenval<<endl<<"Eigenvector:"<<endl;
	librix.printM(eigenv,n,1);
	
	float s_eigenval = 1/(librix.eigen(librix.invM(matrix, n), n, eigenv));
	cout<<"Smallest Eigenvalue:\t"<<s_eigenval<<endl<<"Eigenvector:"<<endl;
	librix.printM(eigenv,n,1);

	return 1;
}