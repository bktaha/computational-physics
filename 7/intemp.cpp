#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

float trapaze (float h, int n, float* y){
	float intrap = (*(y+0)) + (*(y+n));
	for (int i=1; i<n-1; i++){
		intrap += 2*(*(y+i));
	}
	intrap *= (0.5*h);
	return intrap;
}

float simpsage (float h, int n, float* y){
	float intsimp = (*(y+0)) + (*(y+n));
	for (int i=1; i<n-1; i++){
		if (i%2 == 0) intsimp += 2*(*(y+i));
		else intsimp += 4*(*(y+i));
	}
	intsimp *= (h/3.0);
	return intsimp;
}

int main(int argc, char* argv[]){
	int k = atof(argv[1]);
	float (*intf)(float, int, float*);
	switch (k){
		case 1: intf = &trapaze; break;
		case 2: intf = &simpsage; break;
		default: cout<<"Invalid"<<endl; 
	}
	// -------------------------------- % Reading ze file % --------------------------------
	ifstream file_t("OutPut7a");
	string line_t; int i=0, r=0, c=0;
	while(getline(file_t,line_t)){
		istringstream iss(line_t);
		float val_t;
		if (r==0)			
			while (iss >> val_t){
				c++;		
			}
		r++;
	}
	if (c!=2) {cout<<"Two Column, bro!"<<endl; return 1;}
	
	float *dt = (float *)malloc(r*c*sizeof(float)); 
	ifstream file("OutPut7a");	string line;
	while(getline(file,line)){
		istringstream iss(line);
		float val;
		for (int j = 0; j<c; j++)
				if (iss >> val)
					 *(dt + i*c + j) = val;
		i++;
	}

	float *x = new float[r];	float *y = new float[r];
	for (i = 0; i<r; i++){
		*(x+i) = *(dt + i*c + 0);	*(y+i) = *(dt + i*c + 1);
	}
	
	float a=x[0];	float b=x[r-1];	float h=x[1]-x[0];
	float trueval = ((a+1)*exp(-a)) - ((b+1)*exp(-b));
	float intval = intf(h, r-1, y);
	float errval = abs((trueval-intval)/trueval)*100;
	cout<<"--------= % Result % =--------"<<endl;
	cout<<"Analytical Integral Value:\t"<<trueval<<endl;
	cout<<"Numerical Integral Value:\t"<<intval<<endl;
	cout<<"Error:\t"<<errval<<" %"<<endl;
}
