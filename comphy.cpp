#include "Comphy.h"

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

#define TOL 1e-5
#define MAXITER 30

void Comphy::roundM(float* a, int r, int c){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++)
            if(abs(*(a + i*c + j)) < 0.0001) *(a + i*c + j) = 0;
        else {(*(a + i*c + j))*=100000;
            *(a + i*c + j) = round(*(a + i*c + j));
            *(a + i*c + j)/=100000;
        }
    }
}

float* Comphy::traM(float* a, int r, int c){
    float *p = (float *)malloc(c*r*sizeof(float));
    for (int i = 0; i<c; i++){
        for (int j = 0; j<r; j++){
            *(p + i*r + j) = *(a + j*c + i);
        }
    }
    return p;
}

float* Comphy::invM(float* matrix, int n){
    // Gauss-Jordan Elimination;
    int i=0, j=0;
    float *id = (float *)malloc(n*n*sizeof(float));
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (i==j) *(id + i*n + j) = 1;
            else *(id + i*n + j) = 0;
        }
    }
    float coeff;
    int k;
    for (k=0; k<n; k++){
        for(i = k+1; i<n; i++){
            coeff = (*(matrix + i*n + k))/(*(matrix + k*n + k));
            for(j=0; j<n; j++){
                    *(matrix + i*n +j) = *(matrix + i*n +j) - (*(matrix + k*n + j))*coeff;
                    *(id + i*n +j) = *(id + i*n +j) - (*(id + k*n + j))*coeff;
            }
        }
    }
    roundM(matrix,n,n);  roundM(id,n,n);
    cout<<endl;
    for (k=n-1; k>=0; k--){
        for(i = k-1; i>=0; i--){
            coeff = (*(matrix + i*n + k))/(*(matrix + k*n + k));
            for(j=0; j<n; j++){
                *(matrix + i*n +j) = *(matrix + i*n +j) - (*(matrix + k*n + j))*coeff;
                *(id + i*n +j) = *(id + i*n +j) - (*(id + k*n + j))*coeff;
            }
        }
    }
    roundM(matrix,n,n);  roundM(id,n,n);
    for(i = 0; i<n; i++){
        coeff = 1/(*(matrix + i*n + i));
        for(j=0; j<n; j++){
            *(matrix + i*n +j) = (*(matrix + i*n + j))*coeff;
            *(id + i*n +j) = (*(id + i*n + j))*coeff;
        }
    }
    roundM(matrix,n,n);  roundM(id,n,n);
    return id;
}

void Comphy::printM(float* id, int r, int c){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++)
            cout<<*(id + i*c + j)<<" ";
        cout<<endl;
    } cout<<endl;
}

float* Comphy::prodM(float* a, int ra, int ca, float* b, int rb, int cb){
    if (ca!=rb){
        cout<<"No Multiply, bro!"<<endl;
        return NULL;
    }
    else{
        float *p = (float *)malloc(ra*cb*sizeof(float));
        int pi, pj, aj, bi;
        for (pi = 0; pi < ra; pi++){
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

float* Comphy::solveM(float* m, int r){
    int c = r+1, i;
    for (int k=0; k<r; k++){
        int imax=k;
        double elmax=abs((*(m + k*c + k)));
        for (int im=k+1;im<r;im++){
            if (abs((*(m + im*c + k))) > elmax){
                elmax = abs((*(m + im*c + k)));
                imax=im;
            }
        }
        if (*(m + imax*c + k) == 0) {
            cout<<"Matrix singular!"<<endl;
            break;
        }
        for (i=0;i<c;i++) {
            double temp;
            temp = *(m + k*c + i);
            *(m + k*c + i) = *(m + imax*c + i);
            *(m + imax*c + i) = temp;
        }
        for (i=k+1;i<r;i++) {
            for (int j=k+1;j<c;j++) {
                *(m + i*c + j) = (*(m + i*c + j)) - (*(m + k*c + j))*((*(m + i*c + k))/(*(m + k*c + k)));
            }
            *(m + i*c + k) = 0;
        }
    }
    float *x = new float[r];
    for (i=0;i<r;i++){
        *(x+i) = 0;
    }
    for (i=r-1;i>=0;i--){
        double sub=0;
        for (int ix=0;ix<=r;ix++){
            sub+=((*(m + i*c + ix))*(*(x + ix)));
        }
        *(x+i) = (*(m + i*c + c -1) - sub) / *(m + i*c + i);
    }
    return x;
}

int Comphy::sizeMatrix(char* filename){
    int r=0, c=0;
    ifstream file_t(filename);
    string line_t;
    while(getline(file_t,line_t)){
        istringstream iss(line_t);
        float val_t;
        if (r==0)           
            while (iss >> val_t){
                c++;        
            }
        r++;
    }
    return r;
}

void Comphy::retrieveMatrix(char* filename, float* matrix, int n){
    int ctr=0, ctrb=0;
    ifstream file(filename);    
    string line;
    while(getline(file,line)){
        istringstream iss(line);
        float val;
        for (ctrb = 0; ctrb<n; ctrb++)
                if (iss >> val)
                     *(matrix + ctr*n + ctrb) = val;
        ctr++;
    }
}

int Comphy::infnorm(float* ar, int arlen, float* armax){
    int ctr, arindex=0;
    armax[0]=ar[0];
    for(ctr=1; ctr<arlen; ctr++){
        if(ar[ctr]>armax[0]){
            armax[0]=ar[ctr];
            arindex=ctr;
        }
    }
    return arindex;
}

void Comphy::mScale(float* ar, int arlen, float scalefactor){
    int ctr;
    for(ctr=0; ctr<arlen; ctr++){
        ar[ctr]/=scalefactor;
    }
}

float* Comphy::diffAr(float* arone, float* artwo, int arlen){
    int ctr;
    float* diffar = new float[arlen];
    for(ctr=0; ctr<arlen; ctr++){
        diffar[ctr]=(arone[ctr] - artwo[ctr]);
    }   
    return diffar;
}

void Comphy::pourAr(float* jug, float* mug, int arlen){
    int ctr;
    for(ctr=0; ctr<arlen; ctr++){
        mug[ctr] = jug[ctr];
    }
}

float Comphy::eigen(float* matrix, int n, float* eigenv){
    int itercount=1, ctr=0;
    float* y = new float[n];
    float mu;   // Approximate Eigenvalue
    float errval;
    float* diff;

    for (ctr=0; ctr<n; ctr++){
        eigenv[ctr]=1;
    }

    float maxval[1];
    int arindex, errindex;
    arindex = infnorm(eigenv, n, maxval);
    mScale(eigenv, n, maxval[0]);

    while(itercount<MAXITER){
        y = prodM(matrix, n, n, eigenv, n, 1);
        mu = y[arindex];
        arindex = infnorm(y, n, maxval);
        if(y[arindex]==0){
            return 0;
        }
        mScale(y, n, maxval[0]);
        errindex = infnorm(diffAr(eigenv, y, n), n, maxval);
        errval = maxval[0];
        pourAr(y, eigenv, n);
        if(errval<TOL){
            return mu;   
        }
        itercount++;
    }
    cout<<"Iteration Count Exceed."<<endl;
}