#include <iostream>
#include <array>
#include <vector>

#define DEPTH 512

typedef struct {
	// B field vector
	double B[3]; 
	// E field vector
	double E[3];
} EmVector;

void CreateField(std::vector<EmVector>& arr, double b[3], double e[3],unsigned L) {
	for (int i = 0; i < L; ++i)
	{
		EmVector a;
		for (int k = 0; k < 3; ++k)
		{
			a.B[k] = b[k];
			a.E[k] = e[k];
		}
		arr.push_back(a);
	}
}

int main()
{
	std::vector<EmVector> EMF;

	double b[3] = {0,0,1};
	double e[3] = {0,2,2};

	int L = DEPTH*DEPTH*DEPTH;

	char c;
	
	CreateField(EMF,b,e,L);

	std::cout << "Created 3D EM field of DEPTH " << DEPTH << " using " << L << " elements.\n";

	return 0;
}