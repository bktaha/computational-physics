class Comphy{
	public:
		void roundM(float* a, int r, int c);
		float* traM(float* a, int r, int c);
		float* invM(float* matrix, int n);
		void printM(float* id, int r, int c);
		float* prodM(float* a, int ra, int ca, float* b, int rb, int cb);
		float* solveM(float* m, int r);
		int sizeMatrix(char* filename);
		void retrieveMatrix(char* filename, float* matrix, int n);
		int infnorm(float* ar, int arlen, float* armax);
		void mScale(float* ar, int arlen, float scalefactor);
		float* diffAr(float* arone, float* artwo, int arlen);
		void pourAr(float* jug, float* mug, int arlen);
		float eigen(float* matrix, int n, float* eigenv);
};