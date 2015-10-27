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
	printM(a,r,c);
	ifstream file_td("d");
	string line_td; int rd=0, cd=0;
	while(getline(file_td,line_td)){
		istringstream issd(line_td);
		float val_td;
		if (rd==0)			
			while (issd >> val_td){
				cd++;		
			}
		rd++;
	}

	if (cd!=1) {cout<<"Single Column, bro!"<<endl; return 1;}
	
	float *d = (float *)malloc(rd*cd*sizeof(float)); 
	i=0;
	ifstream filed("d");	string lined;
	while(getline(filed,lined)){
		istringstream issd(lined);
		float vald;
		for (int j = 0; j<cd; j++)
				if (issd >> vald)
					 *(d + i*cd + j) = vald;
		i++;
	}
	printM(d,rd,cd);
	float *x0 = (float *)malloc(rd*cd*sizeof(float)); 
	if (r!=rd) {cout<<"Single Column, bro!"<<endl; return 1;}

	for (int inp = 0; inp<rd; inp++){
		cout<<"Guess, yo! : "<<endl;
		cin>>*(x0 + inp);
	}
	printM(x0,rd,cd);
	float *l = (float *)malloc(r*c*sizeof(float));
	for (i=0; i<r; i++){
		for(int j=0; j<c; j++){
			if (i<j) *(l + i*c +j) = 0;
			else *(l + i*c +j) = *(a + i*c +j);
		}	
	}
	printM(l,r,c);
	float *u = (float *)malloc(r*c*sizeof(float));
	for (i=0; i<r; i++){
		for(int j=0; j<c; j++){
			if (i>=j) *(u + i*c +j) = 0;
			else *(u + i*c +j) = *(a + i*c +j);
		}	
	}
	printM(u,r,c);
	float *id = (float *)malloc(r*c*sizeof(float));
	for (i = 0; i <  r; i++){
		for (int j = 0; j < c; j++){
		    if (i==j) *(id + i*c + j) = 1;
			else *(id + i*c + j) = 0;
		}
	}

	// Gauss - Elimination & Stuff
	float coeff; int k;
	for (k=0; k<r; k++){
		for(i = k+1; i<r; i++){
			coeff = (*(l + i*c + k))/(*(l + k*c + k));
			for(int j=0; j<r; j++){
				*(l + i*c +j) = *(l + i*c +j) - (*(l + k*c + j))*coeff;
				*(id + i*c +j) = *(id + i*c +j) - (*(id + k*c + j))*coeff;
			}
		}
	}
	roundM(l,r,c);	roundM(id,r,c);
	cout<<endl;
	for (k=r-1; k>=0; k--){
		for(i = k-1; i>=0; i--){
			coeff = (*(l + i*c + k))/(*(l + k*c + k));
			for(int j=0; j<r; j++){
				*(l + i*c +j) = *(l + i*c +j) - (*(l + k*c + j))*coeff;
				*(id + i*c +j) = *(id + i*c +j) - (*(id + k*c + j))*coeff;
			}
		}
	}
	roundM(l,r,c);	roundM(id,r,c);
	for(i = 0; i<r; i++){
		coeff = 1/(*(l + i*c + i));
		for(int j=0; j<r; j++){
			*(l + i*c +j) = (*(l + i*c + j))*coeff;
			*(id + i*c +j) = (*(id + i*c + j))*coeff;
		}
	}
	roundM(l,r,c);	roundM(id,r,c); 
	printM(id,r,c);
	
	float *t = (float *)malloc(r*c*sizeof(float));
	t = prodM(id, r, c, u,r,c); 
	printM(t,r,c);
	for (i = 0; i <  r; i++){
		for (int j = 0; j < c; j++)
		        *(t + i*r + c) = (-1)*(*(t + i*r + c));
	}

	float *cm = (float *)malloc(rd*cd*sizeof(float));
	cm = prodM(id, r, c, d,rd,cd);
	printM(cm,rd,cd);
	int maxit; cout<<"Maximum Iterations, yo! : "<<endl; 	
	cin>>maxit;
	
	float *x1 = (float *)malloc(rd*cd*sizeof(float)); 
	for(int itc = 0; itc<maxit; itc++){
		x1 = prodM(t,r,c, x0,rd,cd);
		for (i = 0; i <  rd; i++){
			for (int j = 0; j < cd; j++)
			        *(x1 + i*cd + j) += *(cm + i*cd + j);
		}
		
		for (i = 0; i <  rd; i++){
			for (int j = 0; j < cd; j++)
			        *(x0 + i*cd + j) = *(x1 + i*cd + j);
		}
		 printM(x1,rd,cd);
	}
	printM(x1,rd,cd);
}