#include<cmath>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

void printM(float* id, int r, int c){
	for (int i = 0; i <  r; i++){
		for (int j = 0; j < c; j++)
		         cout<<*(id + i*c + j)<<"  ";
		cout<<endl;
	} cout<<endl;
}

float* solveM(float* m, int r){
	// Gauss - Elimination & Stuff
	int c = r+1, i;
	for (int k=0; k<r; k++)
	{	int imax=k; double elmax=abs((*(m + k*c + k)));
		for (int im=k+1; im<r; im++)
		{	if (abs((*(m + im*c + k))) > elmax)	{elmax = abs((*(m + im*c + k)));	imax=im;}}
	
		if (*(m + imax*c + k) == 0)	{cout<<"Matrix singular!"<<endl;	break;}

		for (i=0; i<c; i++)
		{	double temp;
			temp = *(m + k*c + i);
			*(m + k*c + i) = *(m + imax*c + i);
			*(m + imax*c + i) = temp;
		}

		for (i=k+1; i<r; i++)
		{	for (int j=k+1; j<c; j++)
			{	*(m + i*c + j) = (*(m + i*c + j)) - (*(m + k*c + j))*((*(m + i*c + k))/(*(m + k*c + k)));}
			*(m + i*c + k) = 0;
		}
	}

	float *x = new float[r];
	for (i=0; i<r; i++){ *(x+i) = 0; }
	for (i=r-1; i>=0; i--){
		double sub=0;
		for (int ix=0; ix<=r; ix++){
			sub+=((*(m + i*c + ix))*(*(x + ix)));
		}
		*(x+i) = (*(m + i*c + c -1) - sub) / *(m + i*c + i);
	}
	return x;
}

int main()	
{
	ifstream file_t("m");
	string line_t; int r=0, c=0;
	while(getline(file_t,line_t)){
		istringstream iss(line_t);
		float val_t;
		if (r==0)			
			while (iss >> val_t){
				c++;		
			}
		r++;
	}
	float *m = (float *)malloc(r*c*sizeof(float)); int i=0;
	ifstream file("m");	string line;
	while(getline(file,line)){
		istringstream iss(line);
		float val;
		for (int j = 0; j<c; j++)
				if (iss >> val)
					 *(m + i*c + j) = val;
		i++;
	}
	float *x = new float[r];
	x = solveM(m,r);
	printM(x,r,1);
}