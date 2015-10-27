#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

float one(float t, float x, float y){
	return 1.2*x - 0.6*x*y;
}

float two(float t, float x, float y){
	return -0.8*y + 0.3*x*y;
}

int main(int argc, char* argv[]){
	float h = atof(argv[1]);
	float ione = atof(argv[2]);	float itwo = atof(argv[3]);
	float a = atof(argv[4]);	float b = atof(argv[5]);
	float t, konex, koney, ktwox, ktwoy, kthreex, kthreey, kfourx, kfoury;
	float xinit = ione, yinit = itwo;
	for (t=a; t<b; t+=h){
		cout<<t<<"\t"<<xinit<<"\t"<<yinit<<endl;
		konex = one(t,xinit,yinit);	
		koney = two(t,xinit,yinit);
		ktwox = one(t+0.5*h, xinit+0.5*h*konex, yinit+0.5*h*koney);	
		ktwoy = two(t+0.5*h, xinit+0.5*h*konex, yinit+0.5*h*koney);
		kthreex = one(t+0.5*h, xinit+0.5*h*ktwox, yinit+0.5*h*ktwoy);	
		kthreey = two(t+0.5*h, xinit+0.5*h*ktwox, yinit+0.5*h*ktwoy);
		kfourx = one(t+h, xinit+h*kthreex, yinit+h*kthreey);	
		kfoury = two(t+h, xinit+h*kthreex, yinit+h*kthreey);
		xinit += (konex + kfourx + 2*(ktwox + kthreex))*h/6;
		yinit += (koney + kfoury + 2*(ktwoy + kthreey))*h/6;
	}
	return 1;
}