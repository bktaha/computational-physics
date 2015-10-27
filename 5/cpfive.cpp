#include<cmath>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

float func(float x, float az, float ao) {return az*(1-exp(-ao*x));}
float dfuncaz(float x, float az, float ao) {return 1-exp(-ao*x);}
float dfuncao(float x, float az, float ao) {return az*x*exp(-ao*x);}

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

float* traM(float* a, int r, int c){
		float *p = (float *)malloc(c*r*sizeof(float));
		for (int i = 0; i<c; i++){
			for (int j = 0; j<r; j++){
				*(p + i*r + j) = *(a + j*c + i);
			}		
		}
		return p;
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

int main(int argc, char* argv[])	
{
	float az, ao, tol, errz, erro, err;		
	if(argc!=4) {cout<<"Bahut Bhokal!"<<endl; return 1;}
	else{
		az = atof(argv[1]);	
		ao = atof(argv[2]);
		tol = atof(argv[3]);
	}
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

	float *y = (float *)malloc(r*1*sizeof(float));
	float *z = (float *)malloc(r*2*sizeof(float));
	float *ztrans = (float *)malloc(r*2*sizeof(float));
	float *ztemp = (float *)malloc(2*2*sizeof(float));
	float *zinv = (float *)malloc(2*2*sizeof(float));
	float *sol = (float *)malloc(2*1*sizeof(float));
	do{
		for (i = 0; i<r; i++){*(y+i) = *(a + i*c + 1) - func(*(a + i*c + 0), az, ao);}
		for (i = 0; i <  r; i++){
			*(z + i*2 + 0) = dfuncaz(*(a + i*c + 0),az,ao);	
			*(z + i*2 + 1) = dfuncao(*(a + i*c + 0),az,ao);		
		}
		ztrans = traM(z, r, 2);
		ztemp = prodM(ztrans,2,r, z,r,2);
		zinv = invM(ztemp, 2, 2);
		sol = prodM(prodM(zinv, 2, 2, ztrans,2,r), r,r, y,r,1);
		az = (*(sol + 0)) + az;			ao = (*(sol + 1)) + ao;
		errz = abs((*(sol + 0)) / az);	erro = abs((*(sol + 1)) / ao);
		if (errz>=erro) err = errz;		else err=erro;
	}while(err>tol);
	cout<<"Take ya coeffs, bruh : "<<az<<" "<<ao<<endl;	
}
