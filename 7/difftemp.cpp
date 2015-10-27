#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

float diffval(int i, float* y){
	return -3*y[i] + 4*y[i+1] - y[i+2];
}

int main(){
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
	
	float h=x[1]-x[0];
	cout<<"--------= % Result % =--------"<<endl;
	for (i=0; i<r-2; i++){
		cout<<"Differential at "<<x[i]<<" :\t"<<diffval(i,y)/(2*h)<<endl;
	}
}
