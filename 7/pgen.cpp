#include <cmath>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]) {
	float a, b, n;
	a = atof(argv[1]);	b = atof(argv[2]);	n = atof(argv[3]);
	
	float h = (b-a)/n, x=a;
	do{
		cout<<x<<"\t"<<x*exp(-x)<<endl;
		x+=h;
	}while(x<=b);
	return 1;
}
