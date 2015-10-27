#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void printM(float* id, int r, int c){
	for (int i = 0; i <  r; i++){
		for (int j = 0; j < c; j++)
		         cout<<*(id + i*c + j)<<"  ";
		cout<<endl;
	} cout<<endl;
}

float* prodM(float* a, int ra, int ca, float* b, int rb, int cb){
	if (ca!=rb){ cout<<"No Multiply, bro!"<<endl;	return NULL;}
	else{
		float *p = (float *)malloc(ra*cb*sizeof(float));
		int pi, pj, aj, bi;
		for (pi = 0; pi <  ra; pi++){
			for (pj = 0; pj < cb; pj++)
			        *(p + pi*cb + pj) = 0;
		}
		for(pi = 0; pi<ra; pi++){
			for(pj=0; pj<cb; pj++){
				for(aj = 0; aj<ca; aj++){*(p + pi*cb + pj) += (*(a + pi*ca + aj))*(*(b + aj*cb + pj));}
			}
		}
		return p;
	}
}

float* solveM(float* m, int r){
	// Solve a Matrix system
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
	ifstream file_t("xy");
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
	if (c!=2) {cout<<"Two Column, bro!"<<endl; return 1;}
	
	float *a = (float *)malloc(r*c*sizeof(float)); 
	int i=0,n;
	ifstream file("xy");	string line;
	while(getline(file,line)){
		istringstream iss(line);
		float val;
		for (int j = 0; j<c; j++)
				if (iss >> val)
					 *(a + i*c + j) = val;
		i++;
	}

	float *x = new float[r];	for (i = 0; i<r; i++){*(x+i) = *(a + i*c + 0);}
	float *y = new float[r];	for (i = 0; i<r; i++){*(y+i) = *(a + i*c + 1);}
	cout<<"Degree of Polynomial : "<<endl;	cin>>n;	n++;
	
	float *z = (float *)malloc((n+1)*n*sizeof(float));
	float avgel;	int ct;
	for (i = 0; i <  n; i++){
		for (int j = 0; j < n; j++){
			avgel = 0;
			for (ct=0; ct<r; ct++) avgel+= pow(*(x+ct) , i+j);
			*(z + i*(n+1) + j) = avgel/r;		
		}
	}
	for (i = 0; i < n; i++){
		avgel = 0;
		for (ct=0; ct<r; ct++) avgel+= pow(*(x+ct) , i)*(*(y+ct));
		*(z + i*(n+1) + n) = avgel/r;
	}

	float *sol = new float[n];	sol = solveM(z,n);
	printM(sol,n,1);	
}