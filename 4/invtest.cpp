#include<cmath>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
using namespace std;


void roundM(float* a, int r, int c){
	for (int i = 0; i <  r; i++){
		for (int j = 0; j < c; j++)
		        if(abs(*(a + i*c + j)) < 0.0001) *(a + i*c + j) = 0;
			else {(*(a + i*c + j))*=100000; *(a + i*c + j) = round(*(a + i*c + j)); *(a + i*c + j)/=100000;}
	}
}

void printM(float* id, int r, int c){
	for (int i = 0; i <  r; i++){
		for (int j = 0; j < c; j++)
		         cout<<*(id + i*c + j)<<"  ";
		cout<<endl;
	} cout<<endl;
}

float* invM(float* a, int r, int c){
	// Gauss-Jordan Elimination; now available on Blu-Ray	
	if (r!=c) {cout<<"Gimme Square, bro!"<<endl; return NULL;}
	int i=0, j=0;
	float *id = (float *)malloc(r*c*sizeof(float));
	for (i = 0; i <  r; i++){
		for (j = 0; j < c; j++){
		    if (i==j) *(id + i*c + j) = 1;
			else *(id + i*c + j) = 0;
		}
	}

	// Gauss - Elimination & Stuff
	float coeff; int k;
	for (k=0; k<r; k++){
		for(i = k+1; i<r; i++){
			coeff = (*(a + i*c + k))/(*(a + k*c + k));
			for(j=0; j<r; j++){
				*(a + i*c +j) = *(a + i*c +j) - (*(a + k*c + j))*coeff;
				*(id + i*c +j) = *(id + i*c +j) - (*(id + k*c + j))*coeff;
			}
		}
	}
	roundM(a,r,c);	roundM(id,r,c);
	cout<<endl;
	for (k=r-1; k>=0; k--){
		for(i = k-1; i>=0; i--){
			coeff = (*(a + i*c + k))/(*(a + k*c + k));
			for(j=0; j<r; j++){
				*(a + i*c +j) = *(a + i*c +j) - (*(a + k*c + j))*coeff;
				*(id + i*c +j) = *(id + i*c +j) - (*(id + k*c + j))*coeff;
			}
		}
	}
	roundM(a,r,c);	roundM(id,r,c);
	for(i = 0; i<r; i++){
		coeff = 1/(*(a + i*c + i));
		for(j=0; j<r; j++){
			*(a + i*c +j) = (*(a + i*c + j))*coeff;
			*(id + i*c +j) = (*(id + i*c + j))*coeff;
		}
	}
	roundM(a,r,c);	roundM(id,r,c);

	return id;
}

int main()	
{
	ifstream file_t("a");
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

	if (r!=c) {cout<<"Gimme Square, bro!"<<endl; return 1;}
	
	float *a = (float *)malloc(r*c*sizeof(float)); 
	int i=0;
	ifstream file("a");	string line;
	while(getline(file,line)){
		istringstream iss(line);
		float val;
		for (int j = 0; j<c; j++)
				if (iss >> val)
					 *(a + i*c + j) = val;
		i++;
	}
	float *id = (float *)malloc(r*c*sizeof(float));
	printM(a,r,c);
	id = invM(a, r, c);
	printM(id, r, c);
}
