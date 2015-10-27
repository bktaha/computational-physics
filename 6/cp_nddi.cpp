#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

float divdif(int u, int l, float* x, float* y){
	if (u-l == 1)	return (*(y+u) - *(y+l))/(*(x+u) - *(x+l));
	else return (divdif(u, l+1, x, y) - divdif(u - 1, l, x, y))/(*(x+u) - *(x+l));
}

void printM(float* id, int r, int c){
	for (int i = 0; i <  r; i++){
		for (int j = 0; j < c; j++)
		         cout<<*(id + i*c + j)<<"  ";
		cout<<endl;
	} cout<<endl;
}

int main(){

	// -------------------------------- % Reading ze file % --------------------------------
	ifstream file_t("xp");
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
	int i=0;
	ifstream file("xp");	string line;
	while(getline(file,line)){
		istringstream iss(line);
		float val;
		for (int j = 0; j<c; j++)
				if (iss >> val)
					 *(a + i*c + j) = val;
		i++;
	}

	float *x = new float[r];	float *y = new float[r];	
	for (i = 0; i<r; i++){
		*(x+i) = *(a + i*c + 0);
		*(y+i) = *(a + i*c + 1);
	}
	
	// -------------------------------- % Coefficients ze Interpolasio % --------------------------------
	float *b = new float[r];		*(b+0) = *(y+0);
	for (i=1; i<r; i++) {*(b+i) = divdif(i,0,x,y);}
	printM(b,r,1);

	float xn, in=0;
	cout<<"ze Interpolasio: "; cin>>xn;
	for (i=0; i<r; i++) {in += (*(b+i))*pow(xn,i);}
	cout<<"ze Valoo: "<<in<<endl;
}
